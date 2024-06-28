// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.NetinetIn.pas' rev: 34.00 (Android)

#ifndef Posix_NetinetinHPP
#define Posix_NetinetinHPP

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
#include <netinet/in.h>

namespace Posix
{
namespace Netinetin
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef in_addr *Pin_addr;

typedef sockaddr_in *Psockaddr_in;

typedef ip_mreq *Pip_mreq;

typedef ip_mreqn *Pip_mreqn;

typedef in_pktinfo *Pin_pktinfo;

typedef in6_addr *Pin6_addr;

typedef sockaddr_in6 *Psockaddr_in6;

typedef in6_pktinfo *Pin6_pktinfo;

typedef ip6_mtuinfo *Pip6_mtuinfo;

typedef ipv6_mreq *pipv6_mreq;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Netinetin */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_NetinetinHPP
