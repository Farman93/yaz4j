/*
 * Copyright (C) 1995-2005, Index Data ApS
 * See the file LICENSE for details.
 *
 * $Id: soap.h,v 1.10 2005/06/25 15:46:03 adam Exp $
 */
/**
 * \file soap.h
 * \brief Header for SOAP
 */

#ifndef YAZ_SOAP_H
#define YAZ_SOAP_H

#include <yaz/odr.h>

YAZ_BEGIN_CDECL

typedef struct {
    char *fault_code;
    char *fault_string;
    char *details;
} Z_SOAP_Fault;

typedef struct {
    int no;
    char *ns;
    void *p;
} Z_SOAP_Generic;

#define Z_SOAP_fault 1
#define Z_SOAP_generic 2
#define Z_SOAP_error 3
typedef struct {
    int which;
    union {
        Z_SOAP_Fault   *fault;
        Z_SOAP_Generic *generic;
        Z_SOAP_Fault   *soap_error;
    } u;
    const char *ns;
} Z_SOAP;

typedef int (*Z_SOAP_fun)(ODR o, void * ptr, void **handler_data,
                         void *client_data, const char *ns);
typedef struct {
    char *ns;
    void *client_data;
    Z_SOAP_fun f;
} Z_SOAP_Handler;

YAZ_EXPORT int z_soap_codec(ODR o, Z_SOAP **pp, 
                            char **content_buf, int *content_len,
                            Z_SOAP_Handler *handlers);
YAZ_EXPORT int z_soap_codec_enc(ODR o, Z_SOAP **pp, 
                                char **content_buf, int *content_len,
                                Z_SOAP_Handler *handlers,
                                const char *encoding);
YAZ_EXPORT int z_soap_codec_enc_xsl(ODR o, Z_SOAP **pp, 
                                    char **content_buf, int *content_len,
                                    Z_SOAP_Handler *handlers,
                                    const char *encoding,
                                    const char *stylesheet);

YAZ_EXPORT int z_soap_error(ODR o, Z_SOAP *p,
                            const char *fault_code, const char *fault_string,
                            const char *details);

YAZ_END_CDECL
#endif
/*
 * Local variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 * vim: shiftwidth=4 tabstop=8 expandtab
 */

