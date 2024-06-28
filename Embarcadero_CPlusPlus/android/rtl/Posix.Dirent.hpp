// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.Dirent.pas' rev: 34.00 (Android)

#ifndef Posix_DirentHPP
#define Posix_DirentHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Base.hpp>
#include <Posix.SysTypes.hpp>

//-- user supplied -----------------------------------------------------------
#include <dirent.h>

namespace Posix
{
namespace Dirent
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef dirent *Pdirent;

typedef Pdirent *PPdirent;

typedef int __cdecl (*TSelectorProc)(const Pdirent p1);

typedef int __cdecl (*TCompareProc)(const Pdirent p1, const Pdirent p2);

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dirent */
}	/* namespace Posix */

//-- user supplied -----------------------------------------------------------
namespace Posix { namespace Dirent { typedef DIR *PDIR; } }

#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_DirentHPP
