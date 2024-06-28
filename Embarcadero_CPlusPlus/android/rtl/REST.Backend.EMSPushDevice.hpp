// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.EMSPushDevice.pas' rev: 34.00 (Android)

#ifndef Rest_Backend_EmspushdeviceHPP
#define Rest_Backend_EmspushdeviceHPP

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
#include <REST.Backend.EMSProvider.hpp>
#include <REST.Backend.EMSApi.hpp>
#include <REST.Backend.Exception.hpp>
#include <REST.Backend.MetaTypes.hpp>

//-- user supplied -----------------------------------------------------------
namespace Rest
{
namespace Backend
{
namespace Emspushdevice
{
  _INIT_UNIT(Rest_Backend_Emspushdevice);
}	/* namespace Emspushdevice */
}	/* namespace Backend */
}	/* namespace Rest */

namespace Rest
{
namespace Backend
{
namespace Emspushdevice
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEMSPushDeviceAPI;
class DELPHICLASS TEMSPushDeviceService;
class DELPHICLASS EEMSClientPushNotificationError;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSPushDeviceAPI : public Rest::Backend::Emsprovider::TEMSServiceAPIAuth
{
	typedef Rest::Backend::Emsprovider::TEMSServiceAPIAuth inherited;
	
private:
	#define TEMSPushDeviceAPI_sEMS u"EMS"
	
	System::UnicodeString FGCMAppID;
	System::UnicodeString FInstallationObjectID;
	
protected:
	System::Pushnotification::TPushService* __fastcall GetPushService();
	bool __fastcall HasPushService();
	void __fastcall RegisterDevice(Rest::Backend::Pushtypes::TDeviceRegisteredAtProviderEvent AOnRegistered)/* overload */;
	void __fastcall UnregisterDevice();
	void __fastcall RegisterDevice(System::Json::TJSONObject* const AProperties, Rest::Backend::Pushtypes::TDeviceRegisteredAtProviderEvent AOnRegistered)/* overload */;
	bool __fastcall TryGetInstallationValue(/* out */ Rest::Backend::Metatypes::TBackendEntityValue &AValue);
public:
	/* TEMSServiceAPI.Create */ inline __fastcall TEMSPushDeviceAPI() : Rest::Backend::Emsprovider::TEMSServiceAPIAuth() { }
	/* TEMSServiceAPI.Destroy */ inline __fastcall virtual ~TEMSPushDeviceAPI() { }
	
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSPushDeviceService : public Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSPushDeviceAPI*>
{
	typedef Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSPushDeviceAPI*> inherited;
	
protected:
	virtual void __fastcall DoAfterConnectionChanged();
	virtual TEMSPushDeviceAPI* __fastcall CreateBackendApi();
	Rest::Backend::Pushtypes::_di_IBackendPushDeviceApi __fastcall CreatePushDeviceApi();
	Rest::Backend::Pushtypes::_di_IBackendPushDeviceApi __fastcall GetPushDeviceApi();
public:
	/* TEMSBackendService.Create */ inline __fastcall virtual TEMSPushDeviceService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSPushDeviceAPI*>(AProvider) { }
	/* TEMSBackendService.Destroy */ inline __fastcall virtual ~TEMSPushDeviceService() { }
	
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EEMSClientPushNotificationError : public Rest::Backend::Exception::EBackendServiceError
{
	typedef Rest::Backend::Exception::EBackendServiceError inherited;
	
public:
	/* Exception.Create */ inline __fastcall EEMSClientPushNotificationError(const System::UnicodeString Msg) : Rest::Backend::Exception::EBackendServiceError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EEMSClientPushNotificationError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Rest::Backend::Exception::EBackendServiceError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSClientPushNotificationError(NativeUInt Ident)/* overload */ : Rest::Backend::Exception::EBackendServiceError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSClientPushNotificationError(System::PResStringRec ResStringRec)/* overload */ : Rest::Backend::Exception::EBackendServiceError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSClientPushNotificationError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Rest::Backend::Exception::EBackendServiceError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSClientPushNotificationError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Rest::Backend::Exception::EBackendServiceError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSClientPushNotificationError(const System::UnicodeString Msg, int AHelpContext) : Rest::Backend::Exception::EBackendServiceError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSClientPushNotificationError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Rest::Backend::Exception::EBackendServiceError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSClientPushNotificationError(NativeUInt Ident, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendServiceError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSClientPushNotificationError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendServiceError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSClientPushNotificationError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendServiceError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSClientPushNotificationError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendServiceError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSClientPushNotificationError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Emspushdevice */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_EMSPUSHDEVICE)
using namespace Rest::Backend::Emspushdevice;
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
#endif	// Rest_Backend_EmspushdeviceHPP
