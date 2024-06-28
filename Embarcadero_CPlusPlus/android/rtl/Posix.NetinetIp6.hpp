// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.NetinetIp6.pas' rev: 34.00 (Android)

#ifndef Posix_Netinetip6HPP
#define Posix_Netinetip6HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Base.hpp>
#include <Posix.SysTypes.hpp>
#include <Posix.NetinetIn.hpp>

//-- user supplied -----------------------------------------------------------
#include <netinet/ip6.h>

namespace Posix
{
namespace Netinetip6
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef ip6_hdr *Pip6_hdr;

typedef ip6_ext *Pip6_ext;

typedef ip6_hbh *Pip6_hbh;

typedef ip6_dest *Pip6_dest;

typedef ip6_rthdr *Pip6_rthdr;

typedef ip6_rthdr0 *Pip6_rthdr0;

typedef ip6_frag *Pip6_frag;

typedef ip6_opt *Pip6_opt;

typedef ip6_opt_jumbo *Pip6_opt_jumbo;

typedef ip6_opt_nsap *Pip6_opt_nsap;

typedef ip6_opt_tunnel *Pip6_opt_tunnel;

typedef ip6_opt_router *Pip6_opt_router;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Netinetip6 */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_Netinetip6HPP
