// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Android.Sensors.pas' rev: 34.00 (Android)

#ifndef System_Android_SensorsHPP
#define System_Android_SensorsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Sensors.hpp>
#include <Androidapi.Sensor.hpp>
#include <Androidapi.JNI.Location.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Android
{
namespace Sensors
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE INDKSensor;
typedef System::DelphiInterface<INDKSensor> _di_INDKSensor;
__interface DELPHIINTERFACE ILocationListeners;
typedef System::DelphiInterface<ILocationListeners> _di_ILocationListeners;
class DELPHICLASS TPlatformSensorManager;
class DELPHICLASS TPlatformGeocoder;
class DELPHICLASS TPlatformGpsStatus;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{523B5B0F-AD54-4C1E-B9A1-978B5CD37D8B}") INDKSensor  : public System::IInterface 
{
	virtual int __fastcall SensorType() = 0 ;
	virtual Androidapi::Sensor::PASensorManager __fastcall SensorManager() = 0 ;
	virtual Androidapi::Sensor::PASensor __fastcall Sensor() = 0 ;
	virtual Androidapi::Sensor::PASensorEventQueue __fastcall NativeEventQueue() = 0 ;
	virtual ASensorEvent __fastcall LastValue() = 0 ;
};

__interface  INTERFACE_UUID("{F379C0D0-63A5-4B98-845B-09C611BE5D40}") ILocationListeners  : public System::IInterface 
{
	virtual Androidapi::Jni::Location::_di_JLocationListener __fastcall GetGPSListener() = 0 ;
	virtual Androidapi::Jni::Location::_di_JLocationListener __fastcall GetNetworkListener() = 0 ;
	virtual Androidapi::Jni::Location::_di_JLocationListener __fastcall GetPassiveListener() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TPlatformGeocoder : public System::Sensors::TGeocoder
{
	typedef System::Sensors::TGeocoder inherited;
	
protected:
	__classmethod virtual System::Sensors::TGeocoderClass __fastcall GetGeocoderImplementer();
public:
	/* TObject.Create */ inline __fastcall TPlatformGeocoder() : System::Sensors::TGeocoder() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPlatformGeocoder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TPlatformGpsStatus : public System::Sensors::TGpsStatus
{
	typedef System::Sensors::TGpsStatus inherited;
	
protected:
	__classmethod virtual System::Sensors::TGpsStatusClass __fastcall GetGpsStatusImplementer();
public:
	/* TObject.Create */ inline __fastcall TPlatformGpsStatus() : System::Sensors::TGpsStatus() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPlatformGpsStatus() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sensors */
}	/* namespace Android */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_ANDROID_SENSORS)
using namespace System::Android::Sensors;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_ANDROID)
using namespace System::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Android_SensorsHPP
