// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Win.Beacon.pas' rev: 34.00 (Windows)

#ifndef System_Win_BeaconHPP
#define System_Win_BeaconHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Beacon.hpp>
#include <System.Bluetooth.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Win
{
namespace Beacon
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPlatformBeaconAdvertiser;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPlatformBeaconAdvertiser : public System::Beacon::TBeaconAdvertiser
{
	typedef System::Beacon::TBeaconAdvertiser inherited;
	
public:
	__classmethod virtual System::Beacon::TBeaconAdvertiser* __fastcall GetInstance(System::Bluetooth::TBluetoothGattServer* const AGattServer = (System::Bluetooth::TBluetoothGattServer*)(0x0));
	__classmethod virtual System::Beacon::TBeaconAdvertiser* __fastcall GetHelperInstance();
public:
	/* TBeaconAdvertiser.Create */ inline __fastcall TPlatformBeaconAdvertiser(System::Bluetooth::TBluetoothGattServer* const AGattServer, bool AHelper) : System::Beacon::TBeaconAdvertiser(AGattServer, AHelper) { }
	/* TBeaconAdvertiser.Destroy */ inline __fastcall virtual ~TPlatformBeaconAdvertiser() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Beacon */
}	/* namespace Win */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN_BEACON)
using namespace System::Win::Beacon;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN)
using namespace System::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Win_BeaconHPP
