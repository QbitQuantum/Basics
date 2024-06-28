// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.SysStat.pas' rev: 34.00 (iOS)

#ifndef Posix_SysstatHPP
#define Posix_SysstatHPP

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
#include <sys/stat.h>
typedef struct stat _stat;

namespace Posix
{
namespace Sysstat
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef _stat *P_stat;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sysstat */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_SysstatHPP
