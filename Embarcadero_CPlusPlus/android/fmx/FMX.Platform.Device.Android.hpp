// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Platform.Device.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Platform_Device_AndroidHPP
#define Fmx_Platform_Device_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Devices.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Types.hpp>
#include <FMX.Forms.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Platform
{
namespace Device
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidDeviceServices;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidDeviceServices : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	bool FDeviceClassCached;
	System::Devices::TDeviceInfo::TDeviceClass FDeviceClass;
	
protected:
	virtual void __fastcall RegisterService();
	virtual void __fastcall UnregisterService();
	
public:
	__fastcall TAndroidDeviceServices();
	__fastcall virtual ~TAndroidDeviceServices();
	bool __fastcall SuppportsTelephony();
	System::UnicodeString __fastcall GetModel();
	Fmx::Platform::TDeviceFeatures __fastcall GetFeatures();
	System::Devices::TDeviceInfo::TDeviceClass __fastcall GetDeviceClass();
private:
	void *__IFMXDeviceService;	// Fmx::Platform::IFMXDeviceService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9419B3C0-379A-4556-B5CA-36C975462326}
	operator Fmx::Platform::_di_IFMXDeviceService()
	{
		Fmx::Platform::_di_IFMXDeviceService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXDeviceService*(void) { return (Fmx::Platform::IFMXDeviceService*)&__IFMXDeviceService; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Device */
}	/* namespace Platform */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_DEVICE_ANDROID)
using namespace Fmx::Platform::Device::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_DEVICE)
using namespace Fmx::Platform::Device;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM)
using namespace Fmx::Platform;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Platform_Device_AndroidHPP
