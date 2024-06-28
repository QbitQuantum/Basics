// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.ParsePushDevice.pas' rev: 34.00 (iOS)

#ifndef Rest_Backend_ParsepushdeviceHPP
#define Rest_Backend_ParsepushdeviceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.JSON.hpp>
#include <System.PushNotification.hpp>
#include <REST.Backend.Providers.hpp>
#include <REST.Backend.PushTypes.hpp>
#include <REST.Backend.ParseProvider.hpp>
#include <REST.Backend.ParseApi.hpp>
#include <REST.Backend.Exception.hpp>
#include <REST.Backend.MetaTypes.hpp>

//-- user supplied -----------------------------------------------------------
namespace Rest
{
namespace Backend
{
namespace Parsepushdevice
{
  _INIT_UNIT(Rest_Backend_Parsepushdevice);
}	/* namespace Parsepushdevice */
}	/* namespace Backend */
}	/* namespace Rest */

namespace Rest
{
namespace Backend
{
namespace Parsepushdevice
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TParsePushDeviceAPI;
class DELPHICLASS TParsePushDeviceService;
class DELPHICLASS EParsePushNotificationError;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TParsePushDeviceAPI : public Rest::Backend::Parseprovider::TParseServiceAPIAuth
{
	typedef Rest::Backend::Parseprovider::TParseServiceAPIAuth inherited;
	
private:
	#define TParsePushDeviceAPI_sParse u"Parse"
	
	System::UnicodeString FGCMAppID;
	System::UnicodeString FInstallationID;
	System::UnicodeString FInstallationObjectID;
	
protected:
	System::Pushnotification::TPushService* __fastcall GetPushService();
	bool __fastcall HasPushService();
	void __fastcall RegisterDevice(Rest::Backend::Pushtypes::TDeviceRegisteredAtProviderEvent AOnRegistered)/* overload */;
	void __fastcall UnregisterDevice();
	void __fastcall RegisterDevice(System::Json::TJSONObject* const AProperties, Rest::Backend::Pushtypes::TDeviceRegisteredAtProviderEvent AOnRegistered)/* overload */;
	bool __fastcall TryGetInstallationValue(/* out */ Rest::Backend::Metatypes::TBackendEntityValue &AValue);
public:
	/* TParseServiceAPI.Create */ inline __fastcall TParsePushDeviceAPI() : Rest::Backend::Parseprovider::TParseServiceAPIAuth() { }
	/* TParseServiceAPI.Destroy */ inline __fastcall virtual ~TParsePushDeviceAPI() { }
	
private:
	void *__IBackendPushDeviceApi2;	// Rest::Backend::Pushtypes::IBackendPushDeviceApi2 
	void *__IBackendPushDeviceApi;	// Rest::Backend::Pushtypes::IBackendPushDeviceApi 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3A78B2C1-233B-485D-9616-049A66E374B3}
	operator Rest::Backend::Pushtypes::_di_IBackendPushDeviceApi2()
	{
		Rest::Backend::Pushtypes::_di_IBackendPushDeviceApi2 intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Pushtypes::IBackendPushDeviceApi2*(void) { return (Rest::Backend::Pushtypes::IBackendPushDeviceApi2*)&__IBackendPushDeviceApi2; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2F1A3600-8C92-4C74-9D20-E800FD275482}
	operator Rest::Backend::Pushtypes::_di_IBackendPushDeviceApi()
	{
		Rest::Backend::Pushtypes::_di_IBackendPushDeviceApi intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Pushtypes::IBackendPushDeviceApi*(void) { return (Rest::Backend::Pushtypes::IBackendPushDeviceApi*)&__IBackendPushDeviceApi; }
	#endif
	
};


class PASCALIMPLEMENTATION TParsePushDeviceService : public Rest::Backend::Parseprovider::TParseBackendService__1<TParsePushDeviceAPI*>
{
	typedef Rest::Backend::Parseprovider::TParseBackendService__1<TParsePushDeviceAPI*> inherited;
	
protected:
	virtual TParsePushDeviceAPI* __fastcall CreateBackendApi();
	Rest::Backend::Pushtypes::_di_IBackendPushDeviceApi __fastcall CreatePushDeviceApi();
	Rest::Backend::Pushtypes::_di_IBackendPushDeviceApi __fastcall GetPushDeviceApi();
public:
	/* TParseBackendService.Create */ inline __fastcall virtual TParsePushDeviceService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Parseprovider::TParseBackendService__1<TParsePushDeviceAPI*>(AProvider) { }
	/* TParseBackendService.Destroy */ inline __fastcall virtual ~TParsePushDeviceService() { }
	
private:
	void *__IBackendPushDeviceService;	// Rest::Backend::Pushtypes::IBackendPushDeviceService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1810D21D-BF97-4DF0-B39A-DECA2A8A6F07}
	operator Rest::Backend::Pushtypes::_di_IBackendPushDeviceService()
	{
		Rest::Backend::Pushtypes::_di_IBackendPushDeviceService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Pushtypes::IBackendPushDeviceService*(void) { return (Rest::Backend::Pushtypes::IBackendPushDeviceService*)&__IBackendPushDeviceService; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E8BD0783-0E4D-459F-9EEC-11B5F29FE792}
	operator Rest::Backend::Providers::_di_IBackendService()
	{
		Rest::Backend::Providers::_di_IBackendService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Providers::IBackendService*(void) { return (Rest::Backend::Providers::IBackendService*)&__IBackendPushDeviceService; }
	#endif
	
};


class PASCALIMPLEMENTATION EParsePushNotificationError : public Rest::Backend::Exception::EBackendServiceError
{
	typedef Rest::Backend::Exception::EBackendServiceError inherited;
	
public:
	/* Exception.Create */ inline __fastcall EParsePushNotificationError(const System::UnicodeString Msg) : Rest::Backend::Exception::EBackendServiceError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EParsePushNotificationError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Rest::Backend::Exception::EBackendServiceError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EParsePushNotificationError(NativeUInt Ident)/* overload */ : Rest::Backend::Exception::EBackendServiceError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EParsePushNotificationError(System::PResStringRec ResStringRec)/* overload */ : Rest::Backend::Exception::EBackendServiceError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EParsePushNotificationError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Rest::Backend::Exception::EBackendServiceError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EParsePushNotificationError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Rest::Backend::Exception::EBackendServiceError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EParsePushNotificationError(const System::UnicodeString Msg, int AHelpContext) : Rest::Backend::Exception::EBackendServiceError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EParsePushNotificationError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Rest::Backend::Exception::EBackendServiceError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EParsePushNotificationError(NativeUInt Ident, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendServiceError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EParsePushNotificationError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendServiceError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EParsePushNotificationError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendServiceError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EParsePushNotificationError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendServiceError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EParsePushNotificationError() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Parsepushdevice */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_PARSEPUSHDEVICE)
using namespace Rest::Backend::Parsepushdevice;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND)
using namespace Rest::Backend;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST)
using namespace Rest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Rest_Backend_ParsepushdeviceHPP
