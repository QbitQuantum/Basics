// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.SysUn.pas' rev: 34.00 (iOS)

#ifndef Posix_SysunHPP
#define Posix_SysunHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Base.hpp>
#include <Posix.SysSocket.hpp>

//-- user supplied -----------------------------------------------------------
#include <sys/un.h>

namespace Posix
{
namespace Sysun
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef sockaddr_un *Psockaddr_un;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sysun */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_SysunHPP
