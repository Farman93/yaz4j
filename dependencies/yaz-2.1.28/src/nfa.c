/*  Copyright (C) 2006, Index Data ApS
 *  See the file LICENSE for details.
 * 
 *  $Id: nfa.c,v 1.12 2006/07/14 13:06:38 heikki Exp $ 
 */

/**
 * \file nfa.c
 * \brief NFA for character set normalizing
 *
 *  This is a simple NFA-based system for character set normalizing
 *  in yaz and zebra. Unlike standard NFA's, this operates on ranges of
 *  characters at a time, so as to keep the size small.
 *
 *  All characters are internally handled as unsigned 32-bit ints, so 
 *  this works well with unicode. Translating to and from utf-8 is trivial, if
 *  need be.
 *
 *  The NFA stores a translation-thing in the terminal nodes. It does not
 *  concern itself with what that thing is, for us it is juts a void*
 *
 *  The module consists of two parts: Building the NFA, and translating
 *  strings with it.
 */


#include <stdio.h>
#include <string.h>
#include <yaz/nfa.h>
#include <yaz/nmem.h> 

/* * * * * * * * * *
 * Data structures
 * * * * * * * * * */

typedef struct yaz_nfa_backref_info yaz_backref_info;

struct yaz_nfa_backref_info {
    yaz_nfa_char *start;
    yaz_nfa_char *end;
};

struct yaz_nfa {
    NMEM nmem; 
    int nstates;   /* how many states do we have */
    int nbackrefs;  /* how many backrefs do we have */
    yaz_nfa_state *laststate; /* points to the last in the circular list */
    yaz_nfa_state *firststate; /* the initial state */
    yaz_backref_info *curr_backrefs; /* the backrefs we are matching */
    yaz_backref_info *best_backrefs; /* backrefs of the best match so far*/
    int lastmatch; /* the result of last match */
};

struct yaz_nfa_state {
    int num; /* state number. used for resoving ambiguities, and for dumping */
    void *result; /* signals a terminal state, and gives the result */
    yaz_nfa_transition *lasttrans; /* circular list of transitions */
    yaz_nfa_state *next; /* Circular linked list */
    int backref_start; /* which backreference starts here. 0 if none */
    int backref_end; /* which backreference ends here. 0 if none */
} ;

struct yaz_nfa_transition {
      yaz_nfa_state *to_state;  /* where to */
      yaz_nfa_char range_start; 
      yaz_nfa_char range_end;
      yaz_nfa_transition *next; /* a linked list of them */
} ;

/* a range from 1 down to 0 is impossible, and is used to denote an */
/* empty (epsilon) transition */
#define EMPTY_START 1
#define EMPTY_END   0

/* a limit for the number of empty transitions we can have in a row before */
/* we declare this a loop */
#define LOOP_LIMIT 100


typedef enum {
    conv_none,
    conv_string,
    conv_backref,
    conv_range
} yaz_nfa_converter_type;

struct yaz_nfa_converter {
    yaz_nfa_converter *next;
    yaz_nfa_converter_type type;
    yaz_nfa_char *string;
    size_t strlen;
    int backref_no;
    int char_diff;
};


/* * * * * * *
 * Initializing and destroying whole nfa's
 * * * * * * */

yaz_nfa *yaz_nfa_init() {
    NMEM my_nmem = nmem_create();
    yaz_nfa *n = nmem_malloc(my_nmem, sizeof(yaz_nfa));
    n->nmem = my_nmem;
    n->nbackrefs = 1;  /* we always have #0, last range match */
    n->curr_backrefs = 0;
    n->best_backrefs = 0;
    n->lastmatch = YAZ_NFA_NOMATCH;
    n->nstates = 0;
    n->laststate = 0;
    n->firststate = n->laststate ;
    return n;
}

void yaz_nfa_destroy(yaz_nfa *n) {
    if (n && n->nmem)
        nmem_destroy(n->nmem);
}


/* * * * * *
 * Low-level interface to building the NFA
 * * * * * */

yaz_nfa_state *yaz_nfa_add_state(yaz_nfa *n) {
    yaz_nfa_state *s = nmem_malloc(n->nmem, sizeof(yaz_nfa_state));
    s->num = (n->nstates)++;
    s->result = 0;
    s->lasttrans = 0;
    s->backref_start = 0;
    s->backref_end = 0;
    if (n->laststate) { 
        s->next = n->laststate->next;
        n->laststate->next = s;
        n->laststate = s;
    } else { /* first state */
        n->laststate = s;
        n->firststate = s;
        s->next = s;
    }
    return s;
}

int yaz_nfa_set_result(yaz_nfa *n, yaz_nfa_state *s, void *result) {
    if ((s->result)&&result)
        return YAZ_NFA_ALREADY;
    s->result = result;
    return 0;
}

void *yaz_nfa_get_result(yaz_nfa *n, yaz_nfa_state *s) {
    if (!s)
        return 0;
    return s->result;
}

int yaz_nfa_set_backref_point(yaz_nfa *n, yaz_nfa_state *s,
           int backref_number,
           int is_start ){
    if (is_start) {
        if (s->backref_start)
            return YAZ_NFA_ALREADY;
        s->backref_start = backref_number;
        if (n->nbackrefs<=backref_number) {
            n->nbackrefs = backref_number+1;
            n->curr_backrefs = 0;
            n->best_backrefs = 0;
            /* clear them just in case we have already matched on */
            /* with this nfa, and created a too small backref table */
            /* we will reallocate when matching. */
        }
    } else {
        if (s->backref_end)
            return YAZ_NFA_ALREADY;
        if (n->nbackrefs<=backref_number) 
            return YAZ_NFA_NOSTART; 
        s->backref_end = backref_number;
    }
    return 0; /* ok */
}

int yaz_nfa_get_backref_point(yaz_nfa *n, yaz_nfa_state *s,
                int is_start ) {
    if (!s) 
        return 0;
    if (is_start)
        return s->backref_start;
    else
        return s->backref_end;
}

void yaz_nfa_add_transition(yaz_nfa *n, 
        yaz_nfa_state *from_state, 
        yaz_nfa_state *to_state,
        yaz_nfa_char range_start, 
        yaz_nfa_char range_end) {
    yaz_nfa_transition *t = nmem_malloc(n->nmem, sizeof(yaz_nfa_transition));
    if (!from_state)
        from_state = n->firststate;
    t->range_start = range_start;
    t->range_end = range_end;
    t->to_state = to_state;
    if (from_state->lasttrans) {
        t->next= from_state->lasttrans->next;
        from_state->lasttrans->next = t;
        from_state->lasttrans = t;
    } else { /* first trans */
        from_state->lasttrans = t;
        t->next = t;
    }
}

void yaz_nfa_add_empty_transition( yaz_nfa *n,
        yaz_nfa_state *from_state,
        yaz_nfa_state *to_state) {
    yaz_nfa_add_transition(n, from_state, to_state,
              EMPTY_START, EMPTY_END);
}

/* * * * * * * *
 * Medium-level interface
 * * * * * * * */

/* Finds a transition from s where the range is exactly c..c */
/* There should only be one such transition */
static yaz_nfa_state *find_single_trans(
          yaz_nfa_state *s, 
          yaz_nfa_char range_start,
          yaz_nfa_char range_end) {
    yaz_nfa_transition *t = s->lasttrans;
    if (!t)
        return 0;
    do {
        t = t->next;
        if ( ( t->range_start == range_start ) && ( t->range_end == range_end) )
            return t->to_state;
    } while (t != s->lasttrans );
    return 0;
}


yaz_nfa_state *yaz_nfa_add_range(yaz_nfa *n, 
        yaz_nfa_state *s,
        yaz_nfa_char range_start, 
        yaz_nfa_char range_end) {
    yaz_nfa_state *nextstate=0;
    if (!s) /* default to top-level of the nfa */
        s = n->firststate;
    if (s)
        nextstate = find_single_trans(s, range_start, range_end);
    else
        s = yaz_nfa_add_state(n); /* create initial state */
    if (!nextstate) {
        nextstate = yaz_nfa_add_state(n);
        yaz_nfa_add_transition(n, s, nextstate, range_start, range_end);
    }
    return nextstate;
}

yaz_nfa_state *yaz_nfa_add_sequence(yaz_nfa *n, 
        yaz_nfa_state *s, 
        yaz_nfa_char *seq,
        size_t seq_len){
    yaz_nfa_state *nextstate=0;
    if (!s) /* default to top-level of the nfa */
        s = n->firststate;
    if (s) 
        nextstate = find_single_trans(s, *seq, *seq);
    if (nextstate) {
        seq++;
        seq_len--;
        if (!seq_len) /* whole sequence matched */
            return nextstate;
        else
            return yaz_nfa_add_sequence(n, nextstate, seq,seq_len);
    } else { /* no next state, build the rest */
        while (seq_len) {
            s = yaz_nfa_add_range(n, s, *seq, *seq);
            seq++;
            seq_len--;
        }
        return s;
    }
    return 0; /* compiler shut up, we return somewhere above */
}



/* * * * * * *
 * Searching the NFA 
 * * * * * * */

struct matcher {
    yaz_nfa *n; 
    yaz_nfa_char *longest;
    int bestnode; 
    void *result;
    int errorcode;
    int empties; /* count how many consecutive empty transitions */
};

/* Finds the longest match. In case of ties, chooses the one with the 
 * lowest numbered state. Keep track of the back references. Recursively
 * traverses the NFA. Keeps track of the best hit it has found. */

static void match_state(
              yaz_nfa_state *s, 
              yaz_nfa_char *prevmatch,
              yaz_nfa_char *inchar,   
              size_t incharsleft,    
              struct matcher *m ) {   
    yaz_nfa_transition *t = s->lasttrans;
    if (s->backref_start) 
        m->n->curr_backrefs[s->backref_start].start = inchar;
    if (s->backref_end) 
        m->n->curr_backrefs[s->backref_end].end = prevmatch;
    if (t) {
        if (incharsleft) {
            do {
                t = t->next;
                if ( (( t->range_start <= *inchar ) && 
                      ( t->range_end >= *inchar )) ){
                    m->empties = 0;
                    if (t->range_start!=t->range_end){
                        /* backref 0 is special: the last range operation */
                        m->n->curr_backrefs[0].start = inchar;
                        m->n->curr_backrefs[0].end = inchar;
                    }
                    match_state(t->to_state, inchar, 
                            inchar+1, incharsleft-1, m);
                } else if (( t->range_start==EMPTY_START) && 
                           (t->range_end==EMPTY_END)) {
                    if ( m->empties++ > LOOP_LIMIT ) 
                        m->errorcode= YAZ_NFA_LOOP;
                    else
                        match_state(t->to_state, prevmatch, 
                                inchar, incharsleft, m);
                }
            } while (t != s->lasttrans );
        } else {
            m->errorcode = YAZ_NFA_OVERRUN;
        }
    }
    if (s->result) { /* terminal node */
        if ( (m->longest < inchar) ||  /* longer result */
             ((m->longest == inchar)&&(m->bestnode<s->num)) ){
              /* or as long, but with lower node number. Still better */
           int i;
           m->longest = inchar;
           m->bestnode = s->num;
           m->result = s->result;
           if (m->n->curr_backrefs) 
               for (i = 0; i<m->n->nbackrefs; i++)  {
                   m->n->best_backrefs[i]=m->n->curr_backrefs[i];
               }
        }
    }
    if (s->backref_start) 
        m->n->curr_backrefs[s->backref_start].start = 0;
    if (s->backref_end) 
        m->n->curr_backrefs[s->backref_end].end = 0;
    m->n->curr_backrefs[0].start = 0;
    m->n->curr_backrefs[0].end = 0;
} /* match_state */

int yaz_nfa_match(yaz_nfa *n, 
           yaz_nfa_char **inbuff, 
           size_t *incharsleft,
           void **result ){
    struct matcher m;
    int sz;
    int i;
    if (!n->firststate) {
        n->lastmatch = YAZ_NFA_NOMATCH;
        return n->lastmatch;
    }
    m.n = n;
    m.longest=*inbuff;
    m.bestnode = n->nstates;
    m.result = 0;
    m.errorcode = YAZ_NFA_SUCCESS;
    m.empties = 0;
    sz = sizeof( struct yaz_nfa_backref_info) * n->nbackrefs;
    if (!n->curr_backrefs) {
        n->curr_backrefs = nmem_malloc( n->nmem, sz);
        n->best_backrefs = nmem_malloc( n->nmem, sz);
    }
    for (i = 0; i<n->nbackrefs; i++) {
        n->curr_backrefs[i].start = 0;
        n->curr_backrefs[i].end = 0;
        n->best_backrefs[i].start = 0;
        n->best_backrefs[i].end = 0;
    }

    match_state(n->firststate, *inbuff, *inbuff, *incharsleft, &m);
    if (m.errorcode==YAZ_NFA_SUCCESS) {
        if (!m.result)
            m.errorcode=YAZ_NFA_NOMATCH;
        else {
            *incharsleft -= (m.longest-*inbuff);
            *result = m.result;
            *inbuff = m.longest;
        }
    }
    n->lastmatch=m.errorcode;
    return m.errorcode;
}


int yaz_nfa_get_backref( yaz_nfa *n,
                int backref_no,
                yaz_nfa_char **start,
                yaz_nfa_char **end) {
    if (backref_no >= n->nbackrefs)
        return YAZ_NFA_NOSUCHBACKREF;
    if (backref_no < 0)
        return YAZ_NFA_NOSUCHBACKREF;
    if (n->lastmatch != YAZ_NFA_SUCCESS)
        return YAZ_NFA_NOMATCH;  

    *start = n->best_backrefs[backref_no].start;
    *end = n->best_backrefs[backref_no].end;
    return 0;
}

/* * * * * * * * * * * * * *
 * Converters 
 * * * * * * * * * * * * * */

static yaz_nfa_converter *create_null_converter ( yaz_nfa *n) {
    yaz_nfa_converter *c;
    c=nmem_malloc(n->nmem, sizeof(yaz_nfa_converter));
    c->next=0;
    c->type=conv_none;
    c->string=0;
    c->strlen=0;
    c->backref_no=0;
    c->char_diff=0;
    return c;
}

yaz_nfa_converter *yaz_nfa_create_string_converter (
                yaz_nfa *n,
                yaz_nfa_char *string,
                size_t length){
    yaz_nfa_converter *c;
    size_t i;
    c=create_null_converter(n);
    c->type=conv_string;
    c->string=nmem_malloc(n->nmem, length*sizeof(yaz_nfa_char));
    for (i=0;i<length;i++)
        c->string[i]=string[i];
    c->strlen=length;
    return c;
}

yaz_nfa_converter *yaz_nfa_create_backref_converter (
                   yaz_nfa *n, int backref_no ) {
    yaz_nfa_converter *c;
    c=create_null_converter(n);
    c->type=conv_backref;
    c->backref_no=backref_no;
    return c;
}

yaz_nfa_converter *yaz_nfa_create_range_converter (
                yaz_nfa *n, int backref_no,
                yaz_nfa_char from_char,
                yaz_nfa_char to_char){
    yaz_nfa_converter *c;
    c=create_null_converter(n);
    c->type=conv_range;
    c->backref_no=backref_no;
    c->char_diff=to_char - from_char;
    return c;
    
}


void yaz_nfa_append_converter (
                yaz_nfa *n,
                yaz_nfa_converter *startpoint,
                yaz_nfa_converter *newconverter) {
    while (startpoint->next)
        startpoint=startpoint->next;
    startpoint->next=newconverter;
}

static int string_convert (
                yaz_nfa *n,
                yaz_nfa_converter *c,
                yaz_nfa_char **outbuff,
                size_t *outcharsleft){
    size_t sz=c->strlen;
    yaz_nfa_char *p=c->string;
    while (sz--) {
        if ((*outcharsleft)-- <= 0)
            return YAZ_NFA_NOSPACE;
        **outbuff=*p++;
        (*outbuff)++;
    }
    return YAZ_NFA_SUCCESS;
}
static int backref_convert (
                yaz_nfa *n,
                yaz_nfa_converter *c,
                yaz_nfa_char **outbuff,
                size_t *outcharsleft){
    yaz_nfa_char *cp1,*cp2;
    int i;
    i = yaz_nfa_get_backref(n,c->backref_no, &cp1, &cp2);
    if ( i == YAZ_NFA_NOSUCHBACKREF) /* no backref, produce no output */
        return YAZ_NFA_SUCCESS; 
    if ( i == YAZ_NFA_NOMATCH ) /* no match in dfa */
        return 1; /* should not happen */
    while (cp2 >= cp1) {
        if ((*outcharsleft)-- <= 0)
            return YAZ_NFA_NOSPACE;
        **outbuff=*cp1++;
        (*outbuff)++;
    }
    return YAZ_NFA_SUCCESS;
}

static int range_convert (
                yaz_nfa *n,
                yaz_nfa_converter *c,
                yaz_nfa_char **outbuff,
                size_t *outcharsleft){
    yaz_nfa_char *cp1=0, *cp2=0;
    int i;
    i = yaz_nfa_get_backref(n,c->backref_no, &cp1, &cp2);
    if (i == YAZ_NFA_NOSUCHBACKREF) /* no backref, produce no output, not ok */
        return YAZ_NFA_NOSUCHBACKREF; /* should not happen */
    if (i == YAZ_NFA_NOMATCH) /* no match in dfa */
        return YAZ_NFA_NOMATCH; /* should not happen */
    while (cp2 >= cp1) {
        if ((*outcharsleft)-- <= 0)
            return YAZ_NFA_NOSPACE;
        **outbuff=(*cp1++) + c->char_diff ;
        (*outbuff)++;
    }
    return YAZ_NFA_SUCCESS;
}


int yaz_nfa_run_converters(
                yaz_nfa *n,
                yaz_nfa_converter *c,
                yaz_nfa_char **outbuff,
                size_t *outcharsleft){
    int rc=0;
    while (c && !rc) {
        switch(c->type) {
            case conv_string:
                rc=string_convert(n,c,outbuff,outcharsleft);
                break;
            case conv_backref:
                rc=backref_convert(n,c,outbuff,outcharsleft);
                break;
            case conv_range:
                rc=range_convert(n,c,outbuff,outcharsleft);
                break;
            default:
                rc=YAZ_NFA_INTERNAL; /* should never happen */
        }
        c=c->next;
    }
    return rc;
}

/* * * * * * * *
 * High-level interface
 * These routines build the nfa and add converters, all 
 * in one go.
 * * * * * * * */

int yaz_nfa_add_string_rule( yaz_nfa *n,
        yaz_nfa_char *from_string,
        size_t        from_length,
        yaz_nfa_char *to_string,
        size_t        to_length ) {
    yaz_nfa_state *s= 
        yaz_nfa_add_sequence(n, 0, from_string,from_length);
    yaz_nfa_converter *c=
        yaz_nfa_create_string_converter(n,to_string,to_length);
    return yaz_nfa_set_result(n,s,c);
}

int yaz_nfa_add_ascii_string_rule( yaz_nfa *n,
                        char *from_string,
                        char *to_string) {
    size_t from_len = strlen(from_string);
    size_t to_len = strlen(to_string);
    yaz_nfa_char *from_buf=
        nmem_malloc(n->nmem, from_len*sizeof(yaz_nfa_char));
    yaz_nfa_char *to_buf=
        nmem_malloc(n->nmem, to_len*sizeof(yaz_nfa_char));
    size_t i;
    for (i=0;i<from_len;i++) 
        from_buf[i]=from_string[i];
    for (i=0;i<to_len;i++) 
        to_buf[i]=to_string[i];
    return yaz_nfa_add_string_rule(n,from_buf, from_len,
            to_buf, to_len);
}

int yaz_nfa_add_char_range_rule (yaz_nfa *n,
        yaz_nfa_char range_start,
        yaz_nfa_char range_end,
        yaz_nfa_char output_range_start) {
    yaz_nfa_state *s= 
        yaz_nfa_add_range(n, 0, range_start, range_end);
    yaz_nfa_converter *c=
        yaz_nfa_create_range_converter(n,0,range_start, output_range_start);
    return yaz_nfa_set_result(n,s,c);
}

int yaz_nfa_add_char_string_rule (yaz_nfa *n,
        yaz_nfa_char range_start,
        yaz_nfa_char range_end,
        yaz_nfa_char* to_string,
        size_t to_length) {
    yaz_nfa_state *s= 
        yaz_nfa_add_range(n, 0, range_start, range_end);
    yaz_nfa_converter *c=
        yaz_nfa_create_string_converter(n,to_string,to_length);
    return yaz_nfa_set_result(n,s,c);
}


int yaz_nfa_convert_slice (yaz_nfa *n,
        yaz_nfa_char **inbuff, 
        size_t *incharsleft,
        yaz_nfa_char **outbuff,
        size_t *outcharsleft) {
    void *resptr;
    yaz_nfa_converter *conv;
    int rc;

    if (*outcharsleft==0)
        rc=YAZ_NFA_NOSPACE; /* no room in outbuff */
    else if (*incharsleft==0) 
        rc = YAZ_NFA_SUCCESS; /* all done */
    else {
        rc=yaz_nfa_match(n, inbuff, incharsleft, &resptr);
        if (rc==YAZ_NFA_SUCCESS) {
            conv= (yaz_nfa_converter *)resptr;
            rc=yaz_nfa_run_converters(n,conv,outbuff,outcharsleft);    
        } else if (rc==YAZ_NFA_NOMATCH) {
            **outbuff = **inbuff; 
            (*outbuff)++;
            (*inbuff)++;
            (*outcharsleft)--;
            (*incharsleft)--;
            rc=YAZ_NFA_SUCCESS; 
        }
        /* else just return the error code */
    }
    return rc;
}

/* * * * * * * * *
 * Debug routines
 * * * * * * */

yaz_nfa_state *yaz_nfa_get_first(yaz_nfa *n){
    if (!n)
        return 0;
    return n->firststate;
}

yaz_nfa_state *yaz_nfa_get_next(yaz_nfa *n, yaz_nfa_state *s){
    if (n && s) {
        if (s==n->laststate)
            return 0;
        return s->next;
    }
    return 0;
}


static void dump_trans(FILE *F, yaz_nfa_transition *t ) {
    char c1;
    char c2;
    char *e;
    c1 = t->range_start;
    c2 = t->range_end;
    e = "";
    if ( (t->range_start <= ' ') || (t->range_start>'z'))
        c1 = '?';
    if ( (t->range_end <= ' ') || (t->range_end>'z'))
        c2 = '?';
    if ((t->range_start==EMPTY_START) && (t->range_end==EMPTY_END)) {
        e = "(empty)";
    }
    fprintf(F, "    -> [%d]  %s '%c' %x - '%c' %x \n",
            t->to_state->num, e,
            c1, t->range_start,
            c2, t->range_end );
}

static void dump_state(FILE *F, yaz_nfa_state *s,
            char *(*strfunc)(void *) ) {
    yaz_nfa_transition *t;
    char *resultstring = "";
    if (s->result) {
        if (strfunc)  {
            resultstring = (*strfunc)(s->result);
        }
        else
            resultstring = s->result;
    }
    fprintf(F, "  state [%d] %s %s",
            s->num, s->result?"(final)":"", resultstring );
    if (s->backref_start) {
        fprintf(F, " start-%d", s->backref_start);
    }
    if (s->backref_end) {
        fprintf(F, " end-%d", s->backref_end);
    }
    fprintf(F, "\n");
    t = s->lasttrans;
    if (!t) {
        fprintf(F, "    (no transitions)\n");
    } else {
        do {
            t = t->next;
            dump_trans(F, t);
        } while (t != s->lasttrans);
    }

}

void yaz_nfa_dump(FILE *F, yaz_nfa *n,
            char *(*strfunc)(void *) ) {
    yaz_nfa_state *s;
    if (!F)   /* lazy programmers can just pass 0 for F */
        F = stdout;
    fprintf(F, "The NFA has %d states and %d backrefs\n",
            n->nstates, n->nbackrefs);
    s = n->laststate;
    if (s) {
        do {
            s = s->next;
            dump_state(F, s, strfunc);
        } while (s != n->laststate);
    }
}

static char buf[5000]="";
char *yaz_nfa_dump_converter(void *conv)
{
    char onebuf[500]="";
    yaz_nfa_converter *c=conv;
    yaz_nfa_char *cp;
    size_t len;
    *buf=0;
    while (c) {
        switch(c->type) {
            case conv_none:
                sprintf(onebuf,"(none)" );
                break;
            case conv_string:
                sprintf(onebuf,"(string '" );
                strcat(buf,onebuf);
                cp=c->string;
                len=c->strlen;
                while (len--) {
                    onebuf[0]=*cp++;
                    onebuf[1]=0;
                    strcat(buf,onebuf);
                }
                strcat(buf,"')");
                onebuf[0]=0;
                break;
            case conv_backref:
                sprintf(onebuf,"(backref %d) ",c->backref_no);
                break;
            case conv_range:
                sprintf(onebuf,"(range %d) ",c->char_diff);
                break;
        }
        strcat(buf,onebuf);
        c=c->next;
    } /* while */
    return buf;
}


/* 
 * Local variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 * vim: shiftwidth=4 tabstop=8 expandtab
 */
