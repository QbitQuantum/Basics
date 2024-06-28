﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.EndPoint.pas' rev: 34.00 (Android)

#ifndef Rest_Backend_EndpointHPP
#define Rest_Backend_EndpointHPP

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
#include <REST.Backend.Providers.hpp>
#include <REST.Client.hpp>
#include <REST.Backend.ServiceTypes.hpp>
#include <System.JSON.hpp>
#include <System.SyncObjs.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <Data.Bind.Components.hpp>
#include <REST.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Backend
{
namespace Endpoint
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBackendRequestComponent;
template<typename TI, typename T> class DELPHICLASS TBackendRequestComponent__2;
template<typename TI, typename T> class DELPHICLASS TBackendRequestComponentAuth__2;
class DELPHICLASS TCustomBackendEndpoint;
class DELPHICLASS TBackendEndpoint;
template<typename TI, typename T> class DELPHICLASS _TBackendRequestComponent__2_Create_ActRec;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBackendRequestComponent : public Rest::Client::TCustomRESTRequest
{
	typedef Rest::Client::TCustomRESTRequest inherited;
	
private:
	Rest::Backend::Providers::_di_IBackendProvider FProvider;
	Rest::Client::TRESTClient* FRESTClient;
	Rest::Backend::Providers::_di_IBackendProvider __fastcall GetProvider();
	
protected:
	virtual void __fastcall ProviderChanged();
	Rest::Backend::Providers::_di_IBackendService __fastcall CreateService(const Rest::Backend::Providers::_di_IBackendProvider AProvider);
	void __fastcall SetProvider(const Rest::Backend::Providers::_di_IBackendProvider Value);
	virtual GUID __fastcall GetBackendServiceIID() = 0 ;
	virtual void __fastcall UpdateProvider(const Rest::Backend::Providers::_di_IBackendProvider AProvider) = 0 ;
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall ClearProvider();
	
public:
	__fastcall virtual TBackendRequestComponent(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBackendRequestComponent();
	__property GUID ServiceIID = {read=GetBackendServiceIID};
	__property Rest::Backend::Providers::_di_IBackendProvider Provider = {read=GetProvider, write=SetProvider};
private:
	void *__IBackendServiceComponent;	// Rest::Backend::Providers::IBackendServiceComponent 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {085164DF-FCA7-45CD-BAC3-42C6B0B08170}
	operator Rest::Backend::Providers::_di_IBackendServiceComponent()
	{
		Rest::Backend::Providers::_di_IBackendServiceComponent intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Providers::IBackendServiceComponent*(void) { return (Rest::Backend::Providers::IBackendServiceComponent*)&__IBackendServiceComponent; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename TI, typename T> class PASCALIMPLEMENTATION TBackendRequestComponent__2 : public TBackendRequestComponent
{
	typedef TBackendRequestComponent inherited;
	
	
public:
	/* [Template Alias] */
	#if defined(__clang__)
	using TExecuteEvent = void __fastcall (__closure *)(System::TObject* Sender, T AAPI);
	#endif
	
	
private:
	TI FBackendService;
	T FBackendServiceAPI;
	Rest::Backend::Providers::TBackendAPIThread__1<T>* FAPIThread;
	HIDESBASE TI __fastcall CreateService(const Rest::Backend::Providers::_di_IBackendProvider AProvider);
	void __fastcall SetAPIThread(Rest::Backend::Providers::TBackendAPIThread__1<T>* const AValue);
	
protected:
	T __fastcall GetBackendServiceAPI();
	TI __fastcall GetBackendService();
	virtual void __fastcall ClearProvider();
	virtual GUID __fastcall GetBackendServiceIID();
	virtual void __fastcall UpdateProvider(const Rest::Backend::Providers::_di_IBackendProvider AValue);
	virtual T __fastcall InternalCreateBackendServiceAPI() = 0 ;
	virtual T __fastcall InternalCreateIndependentBackendServiceAPI();
	
public:
	__fastcall virtual TBackendRequestComponent__2(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBackendRequestComponent__2();
	__property Rest::Backend::Providers::TBackendAPIThread__1<T>* APIThread = {read=FAPIThread, write=SetAPIThread};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename TI, typename T> class PASCALIMPLEMENTATION TBackendRequestComponentAuth__2 : public TBackendRequestComponent__2<TI,T>
{
	typedef TBackendRequestComponent__2<TI,T> inherited;
	
private:
	Rest::Backend::Providers::_di_IBackendAuthReg FAuth;
	Rest::Backend::Providers::_di_IAuthAccess FAuthAccess;
	void __fastcall SetAuth(const Rest::Backend::Providers::_di_IBackendAuthReg Value);
	
protected:
	virtual Rest::Backend::Providers::_di_IAuthAccess __fastcall CreateAuthAccess();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual ~TBackendRequestComponentAuth__2();
	__property Rest::Backend::Providers::_di_IBackendAuthReg Auth = {read=FAuth, write=SetAuth};
public:
	/* {REST_Backend_EndPoint}TBackendRequestComponent<REST_Backend_EndPoint_TBackendRequestComponentAuth<TI,T>_TI,REST_Backend_EndPoint_TBackendRequestComponentAuth<TI,T>_T>.Create */ inline __fastcall virtual TBackendRequestComponentAuth__2(System::Classes::TComponent* AOwner) : TBackendRequestComponent__2<TI,T>(AOwner) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomBackendEndpoint : public TBackendRequestComponentAuth__2<Rest::Backend::Servicetypes::_di_IBackendCustomEndpointService,Rest::Backend::Servicetypes::TBackendCustomEndPointApi*>
{
	typedef TBackendRequestComponentAuth__2<Rest::Backend::Servicetypes::_di_IBackendCustomEndpointService,Rest::Backend::Servicetypes::TBackendCustomEndPointApi*> inherited;
	
	
public:
	enum DECLSPEC_DENUM TAllowHTTPErrors : unsigned char { None, Any, ClientErrors, ClientErrorNotFound_404 };
	
	
private:
	System::Generics::Collections::TList__1<System::Classes::TNotifyEvent>* FJSONNotifyList;
	TAllowHTTPErrors FAllowHTTPErrors;
	Rest::Backend::Servicetypes::TBackendCustomEndPointApi* __fastcall GetEndpointAPI();
	void __fastcall JSONValueChanged(System::TObject* Sender);
	
protected:
	void __fastcall AddJSONChangedEvent(const System::Classes::TNotifyEvent ANotify);
	void __fastcall RemoveJSONChangedEvent(const System::Classes::TNotifyEvent ANotify);
	void __fastcall GetJSONResponse(/* out */ System::Json::TJSONValue* &AJSONValue, /* out */ bool &AHasOwner);
	bool __fastcall HasJSONResponse();
	bool __fastcall HasResponseContent();
	virtual void __fastcall DoResponseChanged();
	virtual void __fastcall DoResponseChanging();
	virtual Rest::Backend::Servicetypes::TBackendCustomEndPointApi* __fastcall InternalCreateBackendServiceAPI();
	virtual Rest::Backend::Servicetypes::TBackendCustomEndPointApi* __fastcall InternalCreateIndependentBackendServiceAPI();
	virtual void __fastcall DoBeforeExecute();
	virtual void __fastcall DoAfterExecute();
	virtual Rest::Backend::Providers::_di_IAuthAccess __fastcall CreateAuthAccess();
	virtual Rest::Client::TSubRESTRequestBindSource* __fastcall CreateRequestBindSource();
	
public:
	__fastcall virtual TCustomBackendEndpoint(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBackendEndpoint();
	__property Rest::Backend::Servicetypes::TBackendCustomEndPointApi* EndpointApi = {read=GetEndpointAPI};
	__property TAllowHTTPErrors AllowHTTPErrors = {read=FAllowHTTPErrors, write=FAllowHTTPErrors, default=0};
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBackendEndpoint : public TCustomBackendEndpoint
{
	typedef TCustomBackendEndpoint inherited;
	
__published:
	__property Provider;
	__property Auth;
	__property AutoCreateParams = {default=1};
	__property Method;
	__property Params;
	__property Resource = {default=0};
	__property ResourceSuffix = {default=0};
	__property Response;
	__property Timeout = {default=30000};
	__property OnAfterExecute;
	__property BindSource;
	__property AllowHTTPErrors = {default=0};
public:
	/* TCustomBackendEndpoint.Create */ inline __fastcall virtual TBackendEndpoint(System::Classes::TComponent* AOwner) : TCustomBackendEndpoint(AOwner) { }
	/* TCustomBackendEndpoint.Destroy */ inline __fastcall virtual ~TBackendEndpoint() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Endpoint */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_ENDPOINT)
using namespace Rest::Backend::Endpoint;
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
#endif	// Rest_Backend_EndpointHPP
