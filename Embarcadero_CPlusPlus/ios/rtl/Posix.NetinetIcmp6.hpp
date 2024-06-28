// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.NetinetIcmp6.pas' rev: 34.00 (iOS)

#ifndef Posix_Netineticmp6HPP
#define Posix_Netineticmp6HPP

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

namespace Posix
{
namespace Netineticmp6
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
static constexpr System::Byte _ND_ROUTER_SOLICIT = System::Byte(0x85);
static constexpr System::Byte _ND_ROUTER_ADVERT = System::Byte(0x86);
static constexpr System::Byte _ND_NEIGHBOR_SOLICIT = System::Byte(0x87);
static constexpr System::Byte _ND_NEIGHBOR_ADVERT = System::Byte(0x88);
static constexpr System::Byte _ND_REDIRECT = System::Byte(0x89);
}	/* namespace Netineticmp6 */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_Netineticmp6HPP
