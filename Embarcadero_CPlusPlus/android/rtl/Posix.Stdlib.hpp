// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.Stdlib.pas' rev: 34.00 (Android)

#ifndef Posix_StdlibHPP
#define Posix_StdlibHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Base.hpp>
#include <Posix.SysTypes.hpp>
#include <Posix.StdDef.hpp>

//-- user supplied -----------------------------------------------------------

namespace Posix
{
namespace Stdlib
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef div_t *Pdiv_t;

typedef ldiv_t *Pldiv_t;

typedef lldiv_t *Plldiv_t;

typedef int __cdecl (*TCompareProc)(const void * p1, const void * p2);

typedef void __fastcall (*TAtexitFunc)(void);

#ifndef __aarch64__
typedef int *Pwctype_t;
#else /* __aarch64__ */
typedef __int64 *Pwctype_t;
#endif /* __aarch64__ */

typedef unsigned *Pwint_t;

typedef mbstate_t *Pmbstate_t;

//-- var, const, procedure ---------------------------------------------------
extern "C" int __cdecl setenv(const char * Name, const char * Value, int Overwrite);
extern DELPHI_PACKAGE int __fastcall atexit(TAtexitFunc S);
extern DELPHI_PACKAGE float __fastcall strtof(const char * Nptr, System::PPAnsiChar EndPtr);
extern DELPHI_PACKAGE double __fastcall atof(const char * Nptr);
extern DELPHI_PACKAGE int __fastcall _abs(int I);
extern DELPHI_PACKAGE int __fastcall labs(int I);
extern DELPHI_PACKAGE __int64 __fastcall llabs(__int64 I);
extern DELPHI_PACKAGE int __fastcall rand(void);
extern DELPHI_PACKAGE void __fastcall srand(unsigned S);
#ifndef __aarch64__
extern DELPHI_PACKAGE int __fastcall _random(void);
#else /* __aarch64__ */
extern DELPHI_PACKAGE long __fastcall _random(void);
#endif /* __aarch64__ */
extern DELPHI_PACKAGE void __fastcall srandom(unsigned S);
extern DELPHI_PACKAGE int __fastcall grantpt(int Fildes);
}	/* namespace Stdlib */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_StdlibHPP
