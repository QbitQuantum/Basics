// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.iOS.Sensors.pas' rev: 34.00 (iOS)

#ifndef System_Ios_SensorsHPP
#define System_Ios_SensorsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Sensors.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Ios
{
namespace Sensors
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPlatformSensorManager;
class DELPHICLASS TPlatformGeocoder;
class DELPHICLASS TPlatformGpsStatus;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPlatformSensorManager : public System::Sensors::TSensorManager
{
	typedef System::Sensors::TSensorManager inherited;
	
protected:
	__classmethod virtual System::Sensors::TSensorManager* __fastcall GetSensorManager();
protected:
	/* TSensorManager.Create */ inline __fastcall TPlatformSensorManager() : System::Sensors::TSensorManager() { }
	
public:
	/* TSensorManager.Destroy */ inline __fastcall virtual ~TPlatformSensorManager() { }
	
};


class PASCALIMPLEMENTATION TPlatformGeocoder : public System::Sensors::TGeocoder
{
	typedef System::Sensors::TGeocoder inherited;
	
protected:
	__classmethod virtual System::Sensors::TGeocoderClass __fastcall GetGeocoderImplementer();
public:
	/* TObject.Create */ inline __fastcall TPlatformGeocoder() : System::Sensors::TGeocoder() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPlatformGeocoder() { }
	
};


class PASCALIMPLEMENTATION TPlatformGpsStatus : public System::Sensors::TGpsStatus
{
	typedef System::Sensors::TGpsStatus inherited;
	
protected:
	__classmethod virtual System::Sensors::TGpsStatusClass __fastcall GetGpsStatusImplementer();
public:
	/* TObject.Create */ inline __fastcall TPlatformGpsStatus() : System::Sensors::TGpsStatus() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPlatformGpsStatus() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sensors */
}	/* namespace Ios */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_IOS_SENSORS)
using namespace System::Ios::Sensors;
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
#endif	// System_Ios_SensorsHPP
