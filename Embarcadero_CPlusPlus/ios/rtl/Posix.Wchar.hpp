// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.Wchar.pas' rev: 34.00 (iOS)

#ifndef Posix_WcharHPP
#define Posix_WcharHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Base.hpp>
#include <Posix.Locale.hpp>
#include <Posix.StdDef.hpp>

//-- user supplied -----------------------------------------------------------
#include <wchar.h>

namespace Posix
{
namespace Wchar
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef unsigned *Pwctype_t;

typedef int *Pwint_t;

typedef mbstate_t *Pmbstate_t;

using Posix::Stddef::Psize_t;

using Posix::Stddef::Pwchar_t;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Wchar */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_WcharHPP
