/*  varargs.h

    Definitions for accessing parameters in functions that accept
    a variable number of arguments.  These macros are compatible
    with UNIX System V.  Use stdarg.h for ANSI C compatibility.

*/

/*
 *      C/C++ Run Time Library - Version 28.0
 *
 *      Copyright (c) 1991, 2021 by Embarcadero Technologies, Inc.
 *      All Rights Reserved.
 *
 */

/* $Revision: 19389 $ */

#ifndef __VARARGS_H
#define __VARARGS_H

#ifdef __STDARG_H
#error Can't include both STDARG.H and VARARGS.H
#endif

#include <_stddef.h>

typedef void _FAR *va_list;

#define __size(x) ((sizeof(x)+sizeof(int)-1) & ~(sizeof(int)-1))

#define va_dcl va_list va_alist;
#define va_start(ap) ap = (va_list)&va_alist
#define va_arg(ap, type) (*(type _FAR *)(((*(char _FAR * _FAR *)&(ap))+=__size(type))-(__size(type))))
#define va_end(ap)   ap = ((void _FAR *)0)

#endif  /* __VARARGS_H */
