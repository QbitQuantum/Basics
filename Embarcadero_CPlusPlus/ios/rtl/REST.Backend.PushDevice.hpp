// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.PushDevice.pas' rev: 34.00 (iOS)

#ifndef Rest_Backend_PushdeviceHPP
#define Rest_Backend_PushdeviceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.JSON.hpp>
#include <REST.Client.hpp>
#include <REST.BindSource.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <Data.Bind.Components.hpp>
#include <REST.Backend.PushTypes.hpp>
#include <REST.Backend.BindSource.hpp>
#include <REST.Backend.Providers.hpp>
#include <REST.Backend.MetaTypes.hpp>
#include <System.PushNotification.hpp>
#include <System.SyncObjs.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Backend
{
namespace Pushdevice
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomPushEvents;
class DELPHICLASS TPushEvents;
class DELPHICLASS TPushEventsAdapter;
class DELPHICLASS TCustomPushEventsBindSource;
class DELPHICLASS TSubPushEventsBindSource;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomPushEvents : public Rest::Backend::Bindsource::TBackendBindSourceComponentAuth__2<Rest::Backend::Pushtypes::_di_IBackendPushDeviceService,Rest::Backend::Pushtypes::TBackendPushDeviceApi*>
{
	typedef Rest::Backend::Bindsource::TBackendBindSourceComponentAuth__2<Rest::Backend::Pushtypes::_di_IBackendPushDeviceService,Rest::Backend::Pushtypes::TBackendPushDeviceApi*> inherited;
	
	
public:
	typedef void __fastcall (__closure *TDeviceTokenEvent)(System::TObject* Sender);
	
	typedef void __fastcall (__closure *TPushReceivedEvent)(System::TObject* Sender, Rest::Backend::Pushtypes::TPushData* const AData);
	
	typedef void __fastcall (__closure *TDeviceTokenFailedEvent)(System::TObject* Sender, const System::UnicodeString AErrorMessage);
	
	typedef void __fastcall (__closure *TDeviceRegisteredEvent)(System::TObject* Sender);
	
	
private:
	typedef Rest::Bindsource::TRESTComponentNotify TNotify;
	
	typedef Rest::Bindsource::TRESTComponentNotifyList__1<Rest::Bindsource::TRESTComponentNotify*>* TNotifyList;
	
	enum DECLSPEC_DENUM TProviderStates : unsigned char { DeviceRegister, Updated, ConnectionError, RegistrationError };
	
	typedef System::Set<TProviderStates, TProviderStates::DeviceRegister, TProviderStates::RegistrationError> TProviderState;
	
	
private:
	Rest::Bindsource::TRESTComponentNotifyList__1<Rest::Bindsource::TRESTComponentNotify*>* FNotifyList;
	TSubPushEventsBindSource* FBindSource;
	System::Generics::Collections::TList__1<System::Classes::TNotifyEvent>* FJSONNotifyList;
	System::Json::TJSONArray* FJSONResult;
	TProviderState FProviderState;
	TPushReceivedEvent FOnPushReceived;
	TDeviceRegisteredEvent FOnDeviceRegistered;
	TDeviceTokenEvent FOnDeviceTokenReceived;
	TDeviceTokenFailedEvent FOnDeviceTokenRequestFailed;
	bool FActive;
	bool FDeferActive;
	System::Pushnotification::TPushServiceConnection* FPushServiceConnection;
	bool FAutoRegisterDevice;
	bool FAutoActivate;
	Rest::Backend::Pushtypes::TPushData* FStartupNotification;
	System::Json::TJSONObject* FDeviceProperties;
	void __fastcall PropertyValueChanged();
	void __fastcall JSONValueChanged();
	void __fastcall SetActive(const bool Value);
	bool __fastcall IsDesigning();
	void __fastcall PushServiceOnChange(System::TObject* Sender, System::Pushnotification::TPushService::TChanges AChanges);
	void __fastcall PushServiceOnReceiveNotification(System::TObject* Sender, System::Pushnotification::TPushServiceNotification* const ANotification);
	void __fastcall OnPushDeviceRegisterDevice(System::Pushnotification::TPushService* const AService);
	void __fastcall UpdateConnection();
	void __fastcall ActivatePushServiceConnection();
	bool __fastcall GetDeviceRegistered();
	void __fastcall CheckAPI();
	Rest::Backend::Pushtypes::TBackendPushDeviceApi* __fastcall GetPushDeviceApi();
	Rest::Backend::Pushtypes::TPushData* __fastcall GetStartupNotification();
	System::Pushnotification::TPushServiceConnection* __fastcall GetPushServiceConnection();
	System::UnicodeString __fastcall GetDeviceID();
	System::UnicodeString __fastcall GetDeviceToken();
	void __fastcall SetDeviceProperties(System::Json::TJSONObject* const Value);
	Rest::Backend::Metatypes::TBackendEntityValue __fastcall GetInstallationValue();
	
protected:
	void __fastcall AddJSONChangedEvent(const System::Classes::TNotifyEvent ANotify);
	void __fastcall RemoveJSONChangedEvent(const System::Classes::TNotifyEvent ANotify);
	void __fastcall GetJSONResponse(/* out */ System::Json::TJSONValue* &AJSONValue, /* out */ bool &AHasOwner);
	bool __fastcall HasJSONResponse();
	bool __fastcall HasResponseContent();
	virtual Rest::Backend::Pushtypes::TBackendPushDeviceApi* __fastcall InternalCreateBackendServiceAPI();
	virtual Rest::Backend::Pushtypes::TBackendPushDeviceApi* __fastcall InternalCreateIndependentBackendServiceAPI();
	virtual void __fastcall ProviderChanged();
	virtual void __fastcall ProcessPushNotification(System::Pushnotification::TPushServiceNotification* const ANotification);
	virtual void __fastcall DoOnDeviceRegistered();
	virtual void __fastcall DoPushReceived(Rest::Backend::Pushtypes::TPushData* const AData);
	virtual void __fastcall DoOnDeviceTokenReceived();
	virtual void __fastcall DoOnDeviceTokenRequestFailed(const System::UnicodeString AErrorMessage);
	virtual void __fastcall Loaded();
	virtual Data::Bind::Objectscope::TBaseObjectBindSource* __fastcall CreateBindSource();
	virtual Rest::Backend::Providers::_di_IAuthAccess __fastcall CreateAuthAccess();
	
public:
	__fastcall virtual TCustomPushEvents(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomPushEvents();
	__property TSubPushEventsBindSource* BindSource = {read=FBindSource};
	void __fastcall ClearResult();
	void __fastcall RegisterDevice()/* overload */;
	void __fastcall RegisterDevice(System::Json::TJSONObject* const AProperties)/* overload */;
	void __fastcall UnregisterDevice();
	Rest::Backend::Pushtypes::TBackendPushDeviceApi* __fastcall CreatePushDeviceApi();
	__property bool Active = {read=FActive, write=SetActive, nodefault};
	__property System::Json::TJSONArray* JSONResult = {read=FJSONResult};
	__property TDeviceTokenEvent OnDeviceTokenReceived = {read=FOnDeviceTokenReceived, write=FOnDeviceTokenReceived};
	__property TDeviceTokenFailedEvent OnDeviceTokenRequestFailed = {read=FOnDeviceTokenRequestFailed, write=FOnDeviceTokenRequestFailed};
	__property TDeviceRegisteredEvent OnDeviceRegistered = {read=FOnDeviceRegistered, write=FOnDeviceRegistered};
	__property TPushReceivedEvent OnPushReceived = {read=FOnPushReceived, write=FOnPushReceived};
	__property bool AutoRegisterDevice = {read=FAutoRegisterDevice, write=FAutoRegisterDevice, default=1};
	__property bool AutoActivate = {read=FAutoActivate, write=FAutoActivate, default=1};
	__property bool DeviceRegistered = {read=GetDeviceRegistered, nodefault};
	__property System::Pushnotification::TPushServiceConnection* PushConnection = {read=GetPushServiceConnection};
	__property Rest::Backend::Pushtypes::TBackendPushDeviceApi* PushDeviceApi = {read=GetPushDeviceApi};
	__property Rest::Backend::Pushtypes::TPushData* StartupNotification = {read=GetStartupNotification};
	__property System::UnicodeString DeviceToken = {read=GetDeviceToken};
	__property System::UnicodeString DeviceID = {read=GetDeviceID};
	__property Rest::Backend::Metatypes::TBackendEntityValue InstallationValue = {read=GetInstallationValue};
	__property System::Json::TJSONObject* DeviceProperties = {read=FDeviceProperties, write=SetDeviceProperties};
private:
	void *__IRESTResponseJSON;	// Rest::Client::IRESTResponseJSON 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {71F5FA19-69CC-4384-AC0A-D6E30AD5CC95}
	operator Rest::Client::_di_IRESTResponseJSON()
	{
		Rest::Client::_di_IRESTResponseJSON intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Client::IRESTResponseJSON*(void) { return (Rest::Client::IRESTResponseJSON*)&__IRESTResponseJSON; }
	#endif
	
};


class PASCALIMPLEMENTATION TPushEvents : public TCustomPushEvents
{
	typedef TCustomPushEvents inherited;
	
__published:
	__property Auth;
	__property Provider;
	__property BindSource;
	__property AutoActivate = {default=1};
	__property AutoRegisterDevice = {default=1};
	__property OnDeviceTokenReceived;
	__property OnDeviceTokenRequestFailed;
	__property OnPushReceived;
	__property OnDeviceRegistered;
public:
	/* TCustomPushEvents.Create */ inline __fastcall virtual TPushEvents(System::Classes::TComponent* AOwner) : TCustomPushEvents(AOwner) { }
	/* TCustomPushEvents.Destroy */ inline __fastcall virtual ~TPushEvents() { }
	
};


class PASCALIMPLEMENTATION TPushEventsAdapter : public Rest::Bindsource::TRESTComponentAdapter
{
	typedef Rest::Bindsource::TRESTComponentAdapter inherited;
	
	
public:
	class DELPHICLASS TNotify;
	class PASCALIMPLEMENTATION TNotify : public Rest::Bindsource::TRESTComponentNotify
	{
		typedef Rest::Bindsource::TRESTComponentNotify inherited;
		
	private:
		TPushEventsAdapter* FAdapter;
		
	protected:
		__fastcall TNotify(TPushEventsAdapter* const AAdapter);
		
	public:
		virtual void __fastcall PropertyValueChanged(System::TObject* Sender);
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TNotify() { }
		
	};
	
	
	
private:
	TCustomPushEvents* FComponent;
	TNotify* FNotify;
	void __fastcall SetPushSender(TCustomPushEvents* const APushSender);
	void __fastcall AddPropertyFields();
	
protected:
	virtual void __fastcall DoChangePosting();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual bool __fastcall GetCanActivate();
	virtual void __fastcall AddFields();
	virtual Data::Bind::Components::TBaseLinkingBindSource* __fastcall GetSource();
	
public:
	__fastcall virtual TPushEventsAdapter(System::Classes::TComponent* AComponent);
	__fastcall virtual ~TPushEventsAdapter();
	virtual void __fastcall GetMemberNames(System::Classes::TStrings* AList);
	__property TCustomPushEvents* PushSender = {read=FComponent, write=SetPushSender};
};


class PASCALIMPLEMENTATION TCustomPushEventsBindSource : public Rest::Bindsource::TRESTComponentBindSource
{
	typedef Rest::Bindsource::TRESTComponentBindSource inherited;
	
private:
	TPushEventsAdapter* FAdapter;
	HIDESBASE TCustomPushEvents* __fastcall GetComponent();
	void __fastcall SetComponent(TCustomPushEvents* const AValue);
	
protected:
	virtual Rest::Bindsource::TRESTComponentAdapter* __fastcall CreateAdapter();
	
public:
	__property TCustomPushEvents* Component = {read=GetComponent, write=SetComponent};
	__property TPushEventsAdapter* Adapter = {read=FAdapter};
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TCustomPushEventsBindSource(System::Classes::TComponent* AOwner) : Rest::Bindsource::TRESTComponentBindSource(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TCustomPushEventsBindSource() { }
	
};


class PASCALIMPLEMENTATION TSubPushEventsBindSource : public TCustomPushEventsBindSource
{
	typedef TCustomPushEventsBindSource inherited;
	
__published:
	__property AutoActivate = {default=1};
	__property AutoEdit = {default=1};
	__property AutoPost = {default=1};
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TSubPushEventsBindSource(System::Classes::TComponent* AOwner) : TCustomPushEventsBindSource(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TSubPushEventsBindSource() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Pushdevice */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_PUSHDEVICE)
using namespace Rest::Backend::Pushdevice;
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
#endif	// Rest_Backend_PushdeviceHPP
