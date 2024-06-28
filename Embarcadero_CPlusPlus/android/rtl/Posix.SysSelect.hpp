// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.SysSelect.pas' rev: 34.00 (Android)

#ifndef Posix_SysselectHPP
#define Posix_SysselectHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Base.hpp>
#include <Posix.SysTime.hpp>
#include <Posix.Time.hpp>
#include <Posix.Signal.hpp>

//-- user supplied -----------------------------------------------------------

namespace Posix
{
namespace Sysselect
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
typedef unsigned fd_mask;
#else /* __aarch64__ */
typedef unsigned long fd_mask;
#endif /* __aarch64__ */

typedef fd_set *Pfd_set;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sysselect */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_SysselectHPP
