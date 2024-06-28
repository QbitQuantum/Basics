// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.NetIf.pas' rev: 34.00 (iOS)

#ifndef Posix_NetifHPP
#define Posix_NetifHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Base.hpp>
#include <Posix.SysTypes.hpp>
#include <Posix.SysSocket.hpp>

//-- user supplied -----------------------------------------------------------
#include <net/if.h>
#include <ifaddrs.h>

namespace Posix
{
namespace Netif
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef ifreq *Pifreq;

typedef ifaddrs *Pifaddrs;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Netif */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_NetifHPP
