// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Iot.Family.VeraDevice.pas' rev: 34.00 (Android)

#ifndef Iot_Family_VeradeviceHPP
#define Iot_Family_VeradeviceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <IoT.Family.HttpDevice.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iot
{
namespace Family
{
namespace Veradevice
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TGeneratedVeraDevice;
class DELPHICLASS TGeneratedVeraDeviceComponent;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TGeneratedVeraDevice : public Iot::Family::Httpdevice::TGeneratedHttpDevice
{
	typedef Iot::Family::Httpdevice::TGeneratedHttpDevice inherited;
	
private:
	int FDeviceNum;
	
public:
	__fastcall TGeneratedVeraDevice(const System::UnicodeString AURL, int ADeviceNum);
	__property int DeviceNum = {read=FDeviceNum, write=FDeviceNum, nodefault};
public:
	/* TGeneratedHttpDevice.Destroy */ inline __fastcall virtual ~TGeneratedVeraDevice() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TGeneratedVeraDeviceComponent : public Iot::Family::Httpdevice::TGeneratedHttpComponent
{
	typedef Iot::Family::Httpdevice::TGeneratedHttpComponent inherited;
	
private:
	int __fastcall GetDeviceNum();
	void __fastcall SetDeviceNum(int Value);
	
__published:
	virtual void __fastcall DeviceActivated();
	__property int DeviceNum = {read=GetDeviceNum, write=SetDeviceNum, nodefault};
	__property URL = {default=0};
public:
	/* TGeneratedHttpComponent.Create */ inline __fastcall virtual TGeneratedVeraDeviceComponent(System::Classes::TComponent* AOwner) : Iot::Family::Httpdevice::TGeneratedHttpComponent(AOwner) { }
	/* TGeneratedHttpComponent.Destroy */ inline __fastcall virtual ~TGeneratedVeraDeviceComponent() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Veradevice */
}	/* namespace Family */
}	/* namespace Iot */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOT_FAMILY_VERADEVICE)
using namespace Iot::Family::Veradevice;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOT_FAMILY)
using namespace Iot::Family;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOT)
using namespace Iot;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iot_Family_VeradeviceHPP
