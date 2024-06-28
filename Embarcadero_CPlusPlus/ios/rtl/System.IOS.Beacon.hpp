// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.IOS.Beacon.pas' rev: 34.00 (iOS)

#ifndef System_Ios_BeaconHPP
#define System_Ios_BeaconHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Beacon.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Ios
{
namespace Beacon
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPlatformBeaconManager;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPlatformBeaconManager : public System::Beacon::TBeaconManager
{
	typedef System::Beacon::TBeaconManager inherited;
	
public:
	__classmethod virtual System::Beacon::TBeaconManager* __fastcall GetInstance(System::Beacon::TBeaconScanMode AMode);
public:
	/* TObject.Create */ inline __fastcall TPlatformBeaconManager() : System::Beacon::TBeaconManager() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPlatformBeaconManager() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Beacon */
}	/* namespace Ios */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_IOS_BEACON)
using namespace System::Ios::Beacon;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_IOS)
using namespace System::Ios;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Ios_BeaconHPP
