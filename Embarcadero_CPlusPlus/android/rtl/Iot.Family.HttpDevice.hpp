// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IoT.Family.HttpDevice.pas' rev: 34.00 (Android)

#ifndef Iot_Family_HttpdeviceHPP
#define Iot_Family_HttpdeviceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Net.HttpClient.hpp>
#include <System.JSON.hpp>
#include <Iot.Consts.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iot
{
namespace Family
{
namespace Httpdevice
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIoTHttpException;
class DELPHICLASS TGeneratedHttpDevice;
class DELPHICLASS TGeneratedHttpComponent;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIoTHttpException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EIoTHttpException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EIoTHttpException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIoTHttpException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIoTHttpException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIoTHttpException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIoTHttpException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIoTHttpException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIoTHttpException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIoTHttpException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIoTHttpException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIoTHttpException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIoTHttpException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIoTHttpException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TGeneratedHttpDevice : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FURL;
	System::Net::Httpclient::THTTPClient* FHttpClient;
	
protected:
	__property System::Net::Httpclient::THTTPClient* HttpClient = {read=FHttpClient};
	
public:
	__fastcall TGeneratedHttpDevice(const System::UnicodeString AURL);
	__fastcall virtual ~TGeneratedHttpDevice();
	__property System::UnicodeString URL = {read=FURL, write=FURL};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TGeneratedHttpComponent : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	bool FActive;
	TGeneratedHttpDevice* FDevice;
	TGeneratedHttpDevice* __fastcall GetDevice();
	
protected:
	System::UnicodeString FURL;
	void __fastcall CheckActive();
	virtual TGeneratedHttpDevice* __fastcall CreateDevice(const System::UnicodeString AURL) = 0 ;
	virtual void __fastcall DeviceActivated() = 0 ;
	bool __fastcall GetActive();
	System::UnicodeString __fastcall GetURL();
	virtual void __fastcall Loaded();
	void __fastcall SetActive(bool Value);
	void __fastcall SetURL(const System::UnicodeString AURL);
	__property TGeneratedHttpDevice* Device = {read=GetDevice};
	
public:
	__fastcall virtual TGeneratedHttpComponent(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TGeneratedHttpComponent();
	
__published:
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	__property System::UnicodeString URL = {read=FURL, write=SetURL};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Httpdevice */
}	/* namespace Family */
}	/* namespace Iot */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOT_FAMILY_HTTPDEVICE)
using namespace Iot::Family::Httpdevice;
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
#endif	// Iot_Family_HttpdeviceHPP
