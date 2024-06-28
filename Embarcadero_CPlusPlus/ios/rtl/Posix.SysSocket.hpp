// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.SysSocket.pas' rev: 34.00 (iOS)

#ifndef Posix_SyssocketHPP
#define Posix_SyssocketHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Base.hpp>
#include <Posix.SysTypes.hpp>
#include <Posix.SysUio.hpp>

//-- user supplied -----------------------------------------------------------
#include <sys/socket.h>

namespace Posix
{
namespace Syssocket
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef unsigned *Psocklen_t;

typedef sockaddr *psockaddr;

typedef msghdr *Pmsghdr;

typedef cmsghdr *pcmsghdr;

typedef linger *PLinger;

typedef sockaddr_storage *Psockaddr_storage;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Syssocket */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_SyssocketHPP
