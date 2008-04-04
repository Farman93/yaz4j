/*
 * Copyright (C) 1995-2005, Index Data ApS
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation, in whole or in part, for any purpose, is hereby granted,
 * provided that:
 *
 * 1. This copyright and permission notice appear in all copies of the
 * software and its documentation. Notices of copyright or attribution
 * which appear at the beginning of any file must remain unchanged.
 *
 * 2. The name of Index Data or the individual authors may not be used to
 * endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS, IMPLIED, OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL INDEX DATA BE LIABLE FOR ANY SPECIAL, INCIDENTAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER OR
 * NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 *
 * $Id: comstack.h,v 1.22 2006/08/24 13:25:44 adam Exp $
 */

/** 
 * \file comstack.h
 * \brief Header for COMSTACK
 */

#ifndef COMSTACK_H
#define COMSTACK_H

#include <yaz/yconfig.h>
#include <yaz/oid.h>
#include <yaz/xmalloc.h>

YAZ_BEGIN_CDECL

#define COMSTACK_DEFAULT_TIMEOUT -1  /* not used yet */

struct comstack;
typedef struct comstack *COMSTACK;
typedef COMSTACK (*CS_TYPE)(int s, int blocking, int protocol, void *vp);

struct comstack
{
    CS_TYPE type;
    int cerrno;     /* current error code of this stack */
    char *stackerr;/* current lower-layer error string, or null if none */
    int iofile;    /* UNIX file descriptor for iochannel */
    int timeout;   /* how long to wait for trailing blocks (ignored for now) */
    void *cprivate;/* state info for lower stack */
    int max_recv_bytes;      /* max size of incoming package */
    int state;     /* current state */
#define CS_ST_UNBND      0
#define CS_ST_IDLE       1
#define CS_ST_INCON      2
#define CS_ST_OUTCON     3
#define CS_ST_DATAXFER   4
#define CS_ST_ACCEPT     5
#define CS_ST_CONNECTING 6
    int newfd;     /* storing new descriptor between listen and accept */
    int blocking;  /* is this link (supposed to be) blocking? */
    unsigned io_pending; /* flag to signal read / write op is incomplete */
    int event;     /* current event */
#define CS_NONE       0
#define CS_CONNECT    1
#define CS_DISCON     2
#define CS_LISTEN     3
#define CS_DATA       4
    enum oid_proto protocol;  /* what application protocol are we talking? */
    int (*f_put)(COMSTACK handle, char *buf, int size);
    int (*f_get)(COMSTACK handle, char **buf, int *bufsize);
    int (*f_more)(COMSTACK handle);
    int (*f_connect)(COMSTACK handle, void *address);
    int (*f_rcvconnect)(COMSTACK handle);
    int (*f_bind)(COMSTACK handle, void *address, int mode);
#define CS_CLIENT 0
#define CS_SERVER 1
    int (*f_listen)(COMSTACK h, char *raddr, int *addrlen,
                   int (*check_ip)(void *cd, const char *a, int len, int type),
                   void *cd);
    COMSTACK (*f_accept)(COMSTACK handle);
    int (*f_close)(COMSTACK handle);
    char *(*f_addrstr)(COMSTACK handle);
    void *(*f_straddr)(COMSTACK handle, const char *str);
    int (*f_set_blocking)(COMSTACK handle, int blocking);
    void *user;       /* user defined data associated with COMSTACK */
};

#define cs_put(handle, buf, size) ((*(handle)->f_put)(handle, buf, size))
#define cs_get(handle, buf, size) ((*(handle)->f_get)(handle, buf, size))
#define cs_more(handle) ((*(handle)->f_more)(handle))
#define cs_connect(handle, address) ((*(handle)->f_connect)(handle, address))
#define cs_rcvconnect(handle) ((*(handle)->f_rcvconnect)(handle))
#define cs_bind(handle, ad, mo) ((*(handle)->f_bind)(handle, ad, mo))
#define cs_listen(handle, ap, al) ((*(handle)->f_listen)(handle, ap, al, 0, 0))
#define cs_listen_check(handle, ap, al, cf, cd) ((*(handle)->f_listen)(handle, ap, al, cf, cd))
#define cs_accept(handle) ((*(handle)->f_accept)(handle))
#define cs_close(handle) ((*(handle)->f_close)(handle))
#define cs_create(type, blocking, proto) ((*type)(-1, blocking, proto, 0))
#define cs_createbysocket(sock, type, blocking, proto) \
        ((*type)(sock, blocking, proto, 0))
#define cs_type(handle) ((handle)->type)
#define cs_fileno(handle) ((handle)->iofile)
#define cs_stackerr(handle) ((handle)->stackerr)
#define cs_getstate(handle) ((handle)->getstate)
#define cs_errno(handle) ((handle)->cerrno)
#define cs_getproto(handle) ((handle)->protocol)
#define cs_addrstr(handle) ((*(handle)->f_addrstr)(handle))
#define cs_straddr(handle, str) ((*(handle)->f_straddr)(handle, str))
#define cs_want_read(handle) ((handle)->io_pending & CS_WANT_READ)
#define cs_want_write(handle) ((handle)->io_pending & CS_WANT_WRITE)
#define cs_set_blocking(handle,blocking) ((handle)->f_set_blocking(handle, blocking))
                                          
#define CS_WANT_READ 1
#define CS_WANT_WRITE 2

YAZ_EXPORT int cs_look (COMSTACK);
YAZ_EXPORT const char *cs_strerror(COMSTACK h);
YAZ_EXPORT const char *cs_errmsg(int n);
YAZ_EXPORT COMSTACK cs_create_host(const char *type_and_host, 
                                   int blocking, void **vp);
YAZ_EXPORT void cs_get_host_args(const char *type_and_host, const char **args);
YAZ_EXPORT int cs_complete_auto(const unsigned char *buf, int len);
YAZ_EXPORT void *cs_get_ssl(COMSTACK cs);
YAZ_EXPORT int cs_set_ssl_ctx(COMSTACK cs, void *ctx);
YAZ_EXPORT int cs_set_ssl_certificate_file(COMSTACK cs, const char *fname);
YAZ_EXPORT int cs_get_peer_certificate_x509(COMSTACK cs, char **buf, int *len);
YAZ_EXPORT void cs_set_max_recv_bytes(COMSTACK cs, int max_recv_bytes);
                                          
/*
 * error management.
 */
                                          
#define CSNONE     0
#define CSYSERR    1
#define CSOUTSTATE 2
#define CSNODATA   3
#define CSWRONGBUF 4
#define CSDENY     5
#define CSERRORSSL 6
#define CSBUFSIZE  7
#define CSLASTERROR CSBUFSIZE  /* must be the value of last CS error */

/* backwards compatibility */
#define CS_SR     PROTO_SR
#define CS_Z3950  PROTO_Z3950

YAZ_END_CDECL

#endif
/*
 * Local variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 * vim: shiftwidth=4 tabstop=8 expandtab
 */

