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
 * $Id: yaz-ccl.h,v 1.9 2005/06/25 15:46:03 adam Exp $
 */
/**
 * \file yaz-ccl.h
 * \brief Header for CCL node tree to RPN converson utilities.
 */

#ifndef YAZ_CCL_H
#define YAZ_CCL_H

#include <yaz/yconfig.h>
#include <yaz/proto.h>
#include <yaz/ccl.h>
#include <yaz/odr.h>

YAZ_BEGIN_CDECL

YAZ_EXPORT Z_RPNQuery *ccl_rpn_query (ODR o, struct ccl_rpn_node *p);
YAZ_EXPORT Z_AttributesPlusTerm *ccl_scan_query (ODR o, struct ccl_rpn_node *p);
YAZ_END_CDECL

#endif
/*
 * Local variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 * vim: shiftwidth=4 tabstop=8 expandtab
 */

