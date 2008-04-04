/*
 * Copyright (c) 1995-2007, Index Data
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Index Data nor the names of its contributors
 *       may be used to endorse or promote products derived from this
 *       software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/* $Id: tokenizer.h,v 1.2 2007/04/27 10:09:44 adam Exp $ */

/** \file tokenizer.h
    \brief Header with public definitions about YAZ' tokenizer
*/

#ifndef YAZ_TOKENIZER
#define YAZ_TOKENIZER
#include <yaz/nmem.h>

YAZ_BEGIN_CDECL

#define YAZ_TOK_EOF 0
#define YAZ_TOK_ERROR (-1)
#define YAZ_TOK_STRING (-2)
#define YAZ_TOK_QSTRING (-3)

typedef struct yaz_tok_cfg *yaz_tok_cfg_t;
typedef struct yaz_tok_parse *yaz_tok_parse_t;

typedef int (*yaz_tok_get_byte_t)(void **vp);

YAZ_EXPORT
yaz_tok_cfg_t yaz_tok_cfg_create(void);

YAZ_EXPORT
void yaz_tok_cfg_destroy(yaz_tok_cfg_t t);

YAZ_EXPORT
void yaz_tok_cfg_single_tokens(yaz_tok_cfg_t t, const char *simple);

YAZ_EXPORT
yaz_tok_parse_t yaz_tok_parse_buf(yaz_tok_cfg_t t, const char *buf);

YAZ_EXPORT
yaz_tok_parse_t yaz_tok_parse_create(yaz_tok_cfg_t t, yaz_tok_get_byte_t h,
                                     void *vp);

YAZ_EXPORT
void yaz_tok_parse_destroy(yaz_tok_parse_t tp);

YAZ_EXPORT
int yaz_tok_move(yaz_tok_parse_t tp);

YAZ_EXPORT
const char *yaz_tok_parse_string(yaz_tok_parse_t tp);

YAZ_END_CDECL

#endif

/*
 * Local variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 * vim: shiftwidth=4 tabstop=8 expandtab
 */

