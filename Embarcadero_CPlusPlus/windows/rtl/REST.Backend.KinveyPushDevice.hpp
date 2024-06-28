// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.KinveyPushDevice.pas' rev: 34.00 (Windows)

#ifndef Rest_Backend_KinveypushdeviceHPP
#define Rest_Backend_KinveypushdeviceHPP

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
#include <REST.Backend.KinveyProvider.hpp>
#include <REST.Backend.KinveyApi.hpp>
#include <REST.Backend.Exception.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "REST.Backend.KinveyPushDevice"

namespace Rest
{
namespace Backend
{
namespace Kinveypushdevice
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TKinveyPushDeviceAPI;
class DELPHICLASS TKinveyPushDeviceService;
class DELPHICLASS EKinveyPushNotificationError;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TKinveyPushDeviceAPI : public Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth
{
	typedef Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth inherited;
	
private:
	#define TKinveyPushDeviceAPI_sKinvey L"Kinvey"
	
	System::UnicodeString FGCMAppID;
	
protected:
	System::Pushnotification::TPushService* __fastcall GetPushService();
	bool __fastcall HasPushService();
	void __fastcall RegisterDevice(Rest::Backend::Pushtypes::TDeviceRegisteredAtProviderEvent AOnRegistered);
	void __fastcall UnregisterDevice();
public:
	/* TKinveyServiceAPI.Create */ inline __fastcall TKinveyPushDeviceAPI() : Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth() { }
	/* TKinveyServiceAPI.Destroy */ inline __fastcall virtual ~TKinveyPushDeviceAPI() { }
	
private:
	void *__IBackendPushDeviceApi;	// Rest::Backend::Pushtypes::IBackendPushDeviceApi 
	
public:
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

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TKinveyPushDeviceService : public Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyPushDeviceAPI*>
{
	typedef Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyPushDeviceAPI*> inherited;
	
protected:
	virtual void __fastcall DoAfterConnectionChanged();
	virtual TKinveyPushDeviceAPI* __fastcall CreateBackendApi();
	Rest::Backend::Pushtypes::_di_IBackendPushDeviceApi __fastcall CreatePushDeviceApi();
	Rest::Backend::Pushtypes::_di_IBackendPushDeviceApi __fastcall GetPushDeviceApi();
public:
	/* TKinveyBackendService.Create */ inline __fastcall virtual TKinveyPushDeviceService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyPushDeviceAPI*>(AProvider) { }
	/* TKinveyBackendService.Destroy */ inline __fastcall virtual ~TKinveyPushDeviceService() { }
	
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

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EKinveyPushNotificationError : public Rest::Backend::Exception::EBackendServiceError
{
	typedef Rest::Backend::Exception::EBackendServiceError inherited;
	
public:
	/* Exception.Create */ inline __fastcall EKinveyPushNotificationError(const System::UnicodeString Msg) : Rest::Backend::Exception::EBackendServiceError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EKinveyPushNotificationError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Rest::Backend::Exception::EBackendServiceError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EKinveyPushNotificationError(NativeUInt Ident)/* overload */ : Rest::Backend::Exception::EBackendServiceError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EKinveyPushNotificationError(System::PResStringRec ResStringRec)/* overload */ : Rest::Backend::Exception::EBackendServiceError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EKinveyPushNotificationError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Rest::Backend::Exception::EBackendServiceError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EKinveyPushNotificationError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Rest::Backend::Exception::EBackendServiceError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EKinveyPushNotificationError(const System::UnicodeString Msg, int AHelpContext) : Rest::Backend::Exception::EBackendServiceError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EKinveyPushNotificationError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Rest::Backend::Exception::EBackendServiceError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EKinveyPushNotificationError(NativeUInt Ident, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendServiceError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EKinveyPushNotificationError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendServiceError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EKinveyPushNotificationError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendServiceError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EKinveyPushNotificationError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendServiceError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EKinveyPushNotificationError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Kinveypushdevice */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_KINVEYPUSHDEVICE)
using namespace Rest::Backend::Kinveypushdevice;
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
#endif	// Rest_Backend_KinveypushdeviceHPP
