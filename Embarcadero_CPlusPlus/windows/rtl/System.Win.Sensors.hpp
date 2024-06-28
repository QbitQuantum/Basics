// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Win.Sensors.pas' rev: 34.00 (Windows)

#ifndef System_Win_SensorsHPP
#define System_Win_SensorsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Sensors.hpp>
#include <Winapi.ActiveX.hpp>
#include <Winapi.Windows.hpp>
#include <System.RTLConsts.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Win
{
namespace Sensors
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPlatformSensorManager;
class DELPHICLASS TPlatformGeocoder;
class DELPHICLASS TPlatformGpsStatus;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
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

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPlatformGeocoder : public System::Sensors::TGeocoder
{
	typedef System::Sensors::TGeocoder inherited;
	
protected:
	__classmethod virtual System::Sensors::TGeocoderClass __fastcall GetGeocoderImplementer();
public:
	/* TObject.Create */ inline __fastcall TPlatformGeocoder() : System::Sensors::TGeocoder() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPlatformGeocoder() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPlatformGpsStatus : public System::Sensors::TGpsStatus
{
	typedef System::Sensors::TGpsStatus inherited;
	
protected:
	__classmethod virtual System::Sensors::TGpsStatusClass __fastcall GetGpsStatusImplementer();
public:
	/* TObject.Create */ inline __fastcall TPlatformGpsStatus() : System::Sensors::TGpsStatus() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPlatformGpsStatus() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sensors */
}	/* namespace Win */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN_SENSORS)
using namespace System::Win::Sensors;
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
#endif	// System_Win_SensorsHPP
