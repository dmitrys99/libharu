/*
 * << Haru Free PDF Library 2.0.0 >> -- utils.h
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 * Copyright (c) 2007-2009 Antony Dovgal et al.
 * Copyright (c) 2023 Dmitry Solomennikov
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 */

#ifndef __UTILS_H
#define __UTILS_H

#include "hpdf.h"
#include <setjmp.h>

#if defined(__WIN32__) || defined(__WIN64__)
#  define HPDF_snprintf _snprintf
static const char* FILE_SEPARATOR = "\\";
#else
#  define HPDF_snprintf  snprintf
static const char* FILE_SEPARATOR = "/";
#endif // defined(__WIN32__) || defined(__WIN64__)

HPDF_HANDLER(void)
demo_error_handler  (HPDF_STATUS   error_no,
                     HPDF_STATUS   detail_no,
                     void         *user_data);

// Same as ÓÔŐÖ×ŘŮ, but in ISO8859-2 codepage
static const char iso8859_2_text[7] = {0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9};
static jmp_buf env;

#endif /* __UTILS_H */
