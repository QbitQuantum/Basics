// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.Stdlib.pas' rev: 34.00 (iOS)

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
typedef lldiv_t *Plldiv_t;

typedef int __cdecl (*TCompareProc)(const void * p1, const void * p2);

typedef void __fastcall (*TAtexitFunc)(void);

typedef unsigned *Pwctype_t;

typedef int *Pwint_t;

typedef mbstate_t *Pmbstate_t;

//-- var, const, procedure ---------------------------------------------------
extern "C" int __cdecl setenv(const char * Name, const char * Value, int Overwrite);
}	/* namespace Stdlib */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_StdlibHPP
