/* xwchar.h internal header */
#ifndef _XWCHAR
#define _XWCHAR
#include <wchar.h>
#include <wctype.h>
#include <xstate.h>
_C_STD_BEGIN
		/* DECLARATIONS */
_C_LIB_DECL

_CRTIMP2 int _Mbtowc(wchar_t *, const char *, size_t, mbstate_t *);
_CRTIMP2 size_t _Wcsftime(wchar_t *, size_t, const char *, size_t,
	const struct tm *);
_CRTIMP2 int _Wctomb(char *, wchar_t, mbstate_t *);
_CRTIMP2 long double _WStold(const wchar_t *, wchar_t **, long);
_CRTIMP2 _Longlong _WStoll(const wchar_t *, wchar_t **, int);
_CRTIMP2 unsigned long _WStoul(const wchar_t *, wchar_t **, int);
_CRTIMP2 _ULonglong _WStoull(const wchar_t *, wchar_t **, int);

_CRTIMP2 int _Mbtowcx(wchar_t *, const char *, size_t, mbstate_t *,
	_Statab *);
_CRTIMP2 int _Wctombx(char *, wchar_t, mbstate_t *,
	_Statab *, _Statab *);

_CRTIMP2 _Statab *_Getpmbstate(void);
_CRTIMP2 _Statab *_Getpwcstate(void);
_CRTIMP2 _Statab *_Getpcostate(void);
_CRTIMP2 _Statab *_Getpwcostate(void);
_END_C_LIB_DECL
_C_STD_END
#endif /* _XWCHAR */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V8.03a/17:1422 */
