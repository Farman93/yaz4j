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
/* $Id: nmem.h,v 1.25 2007/04/17 20:26:18 adam Exp $ */

/**
 * \file nmem.h
 * \brief Header for Nibble Memory functions
 *
 * This is a simple and fairly wasteful little module for nibble memory
 * allocation. Evemtually we'll put in something better.
 */
#ifndef NMEM_H
#define NMEM_H

#include <stddef.h>
#include <yaz/yconfig.h>

YAZ_BEGIN_CDECL

/** \brief NMEM handle (an opaque pointer to memory) */
typedef struct nmem_control *NMEM;

/** \brief release all memory associaged with an NMEM handle */
YAZ_EXPORT void nmem_reset(NMEM n);
/** \brief returns size in bytes of memory for NMEM handle */
YAZ_EXPORT int nmem_total(NMEM n);

/** \brief allocates string on NMEM handle (similar strdup) */
YAZ_EXPORT char *nmem_strdup (NMEM mem, const char *src);
/** \brief allocates string on NMEM handle - allows NULL ptr buffer */
YAZ_EXPORT char *nmem_strdup_null (NMEM mem, const char *src);
/** \brief allocates string of certain size on NMEM handle */
YAZ_EXPORT char *nmem_strdupn (NMEM mem, const char *src, size_t n);

/** \brief allocates sub strings out of string using certain delimitors
    \param nmem NMEM handle
    \param delim delimitor chars (splits on each char in there) 
    \param dstr string to be split
    \param darray result string array for each sub string
    \param num number of result strings
*/
YAZ_EXPORT void nmem_strsplit(NMEM nmem, const char *delim,
                              const char *dstr,
                              char ***darray, int *num);

/** \brief splits string into sub strings delimited by blanks
    \param nmem NMEM handle
    \param dstr string to be split
    \param darray result string array for each sub string
    \param num number of result strings
*/
YAZ_EXPORT void nmem_strsplit_blank(NMEM nmem, const char *dstr,
                                    char ***darray, int *num);

/** \brief creates and allocates integer for NMEM */
YAZ_EXPORT int *nmem_intdup (NMEM mem, int v);

/** \brief transfers memory from one NMEM handle to another  */
YAZ_EXPORT void nmem_transfer (NMEM dst, NMEM src);

/** \brief returns new NMEM handle */
YAZ_EXPORT NMEM nmem_create(void);

/** \brief destroys NMEM handle and memory associated with it */
YAZ_EXPORT void nmem_destroy(NMEM n);

/** \brief allocate memory block on NMEM handle */
YAZ_EXPORT void *nmem_malloc(NMEM n, int size);

YAZ_EXPORT int yaz_errno (void);
YAZ_EXPORT void yaz_set_errno (int v);
YAZ_EXPORT void yaz_strerror(char *buf, int max);

YAZ_END_CDECL

#endif
/*
 * Local variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 * vim: shiftwidth=4 tabstop=8 expandtab
 */

