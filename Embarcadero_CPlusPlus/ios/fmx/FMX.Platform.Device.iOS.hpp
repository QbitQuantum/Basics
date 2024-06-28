// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Platform.Device.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Platform_Device_IosHPP
#define Fmx_Platform_Device_IosHPP

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
namespace Ios
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCocoaTouchDeviceServices;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCocoaTouchDeviceServices : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
protected:
	virtual void __fastcall RegisterService();
	virtual void __fastcall UnregisterService();
	
public:
	__fastcall TCocoaTouchDeviceServices();
	__fastcall virtual ~TCocoaTouchDeviceServices();
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


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Device */
}	/* namespace Platform */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_DEVICE_IOS)
using namespace Fmx::Platform::Device::Ios;
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
#endif	// Fmx_Platform_Device_IosHPP
