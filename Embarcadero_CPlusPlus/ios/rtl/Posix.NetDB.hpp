// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.NetDB.pas' rev: 34.00 (iOS)

#ifndef Posix_NetdbHPP
#define Posix_NetdbHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Base.hpp>
#include <Posix.SysSocket.hpp>
#include <Posix.NetinetIn.hpp>

//-- user supplied -----------------------------------------------------------
#include <netdb.h>

namespace Posix
{
namespace Netdb
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef hostent *Phostent;

typedef netent *Pnetent;

typedef servent *Pservent;

typedef protoent *Pprotoent;

typedef rpcent *Prpcent;

typedef addrinfo *PAddrInfo;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Netdb */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_NetdbHPP
