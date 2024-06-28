// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMSHosting.EdgeService.pas' rev: 34.00 (Windows)

#ifndef Emshosting_EdgeserviceHPP
#define Emshosting_EdgeserviceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <REST.Backend.EMSProvider.hpp>
#include <REST.Backend.EMSApi.hpp>
#include <REST.Backend.ServiceComponents.hpp>
#include <REST.Backend.Providers.hpp>
#include <REST.Backend.ServiceTypes.hpp>
#include <System.JSON.hpp>
#include <EMSHosting.RequestTypes.hpp>
#include <System.SyncObjs.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "EMSHosting.EdgeService"

namespace Emshosting
{
namespace Edgeservice
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBackendEdgemoduleApi;
__interface DELPHIINTERFACE IBackendEdgemoduleAPI;
typedef System::DelphiInterface<IBackendEdgemoduleAPI> _di_IBackendEdgemoduleAPI;
__interface DELPHIINTERFACE IBackendEdgemoduleService;
typedef System::DelphiInterface<IBackendEdgemoduleService> _di_IBackendEdgemoduleService;
class DELPHICLASS TCustomEMSEdgeService;
class DELPHICLASS TEMSEdgeService;
class DELPHICLASS TEMSEdgeListener;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBackendEdgemoduleApi : public Rest::Backend::Servicetypes::TBackendAuthenticationApi
{
	typedef Rest::Backend::Servicetypes::TBackendAuthenticationApi inherited;
	
private:
	_di_IBackendEdgemoduleAPI FServiceApi;
	_di_IBackendEdgemoduleService FService;
	_di_IBackendEdgemoduleAPI __fastcall GetServiceAPI();
	System::UnicodeString __fastcall GetModuleID();
	
protected:
	virtual Rest::Backend::Servicetypes::_di_IBackendAuthenticationApi __fastcall GetAuthenticationApi();
	
public:
	__fastcall TBackendEdgemoduleApi(const _di_IBackendEdgemoduleAPI AApi)/* overload */;
	__fastcall TBackendEdgemoduleApi(const _di_IBackendEdgemoduleService AService)/* overload */;
	void __fastcall RegisterModule(const System::UnicodeString AName, System::Json::TJSONObject* const AModuleDetails, const System::UnicodeString AProtocolName, const System::UnicodeString AProtocolProperties, System::Json::TJSONArray* const AResources);
	void __fastcall UnregisterModule();
	__property _di_IBackendEdgemoduleAPI ProviderAPI = {read=FServiceApi};
	__property System::UnicodeString ModuleID = {read=GetModuleID};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBackendEdgemoduleApi() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{DF5C4F53-5058-4E75-A33B-ABC5D07139B2}") IBackendEdgemoduleAPI  : public System::IInterface 
{
	virtual void __fastcall RegisterModule(const System::UnicodeString AName, System::Json::TJSONObject* const AModuleDetails, const System::UnicodeString AProtocolName, const System::UnicodeString AProtocolProperties, System::Json::TJSONArray* const AResources) = 0 ;
	virtual void __fastcall UnregisterModule() = 0 ;
	virtual System::UnicodeString __fastcall GetModuleID() = 0 ;
	__property System::UnicodeString ModuleID = {read=GetModuleID};
};

__interface  INTERFACE_UUID("{80409801-58DB-4DEF-8207-EA0E28773C89}") IBackendEdgemoduleService  : public Rest::Backend::Providers::IBackendService 
{
	virtual _di_IBackendEdgemoduleAPI __fastcall GetModuleAPI() = 0 ;
	virtual _di_IBackendEdgemoduleAPI __fastcall CreateModuleApi() = 0 ;
	__property _di_IBackendEdgemoduleAPI ModuleAPI = {read=GetModuleAPI};
};

class PASCALIMPLEMENTATION TCustomEMSEdgeService : public Rest::Backend::Providers::TBackendServiceComponentAuth__2<_di_IBackendEdgemoduleService,TBackendEdgemoduleApi*>
{
	typedef Rest::Backend::Providers::TBackendServiceComponentAuth__2<_di_IBackendEdgemoduleService,TBackendEdgemoduleApi*> inherited;
	
	
public:
	typedef void __fastcall (__closure *THandledEvent)(System::TObject* Sender, bool &AHandled);
	
	typedef void __fastcall (__closure *TRegisteringEvent)(System::TObject* Sender, System::Json::TJSONObject* const AModuleDetail, System::Json::TJSONArray* const AResources, bool &AHandled);
	
	
private:
	System::UnicodeString FModuleName;
	bool FAutoActivate;
	bool FAutoRegister;
	bool FAutoUnRegister;
	bool FDeferActive;
	System::UnicodeString FListenerProtocol;
	TEMSEdgeListener* FListenerService;
	THandledEvent FOnUnregistering;
	System::Classes::TNotifyEvent FOnRegistered;
	System::Classes::TNotifyEvent FOnUnregistered;
	TRegisteringEvent FOnRegistering;
	System::UnicodeString FModuleVersion;
	TBackendEdgemoduleApi* __fastcall GetModuleAPI();
	_di_IBackendEdgemoduleService __fastcall GetProviderService();
	void __fastcall SetModuleName(const System::UnicodeString Value);
	void __fastcall CheckModuleName();
	bool __fastcall GetActive();
	void __fastcall SetActive(const bool Value);
	void __fastcall SetListenerProtocol(const System::UnicodeString Value);
	void __fastcall CheckListenerProtocol();
	void __fastcall SetModuleVersion(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetModuleID();
	
protected:
	virtual void __fastcall Loaded();
	virtual TBackendEdgemoduleApi* __fastcall InternalCreateBackendServiceAPI();
	virtual TBackendEdgemoduleApi* __fastcall InternalCreateIndependentBackendServiceAPI();
	virtual Rest::Backend::Providers::_di_IAuthAccess __fastcall CreateAuthAccess();
	virtual void __fastcall DoOnRegistering(System::Json::TJSONObject* const AModuleDetails, System::Json::TJSONArray* const AResources, bool &AHandled);
	virtual void __fastcall DoOnRegistered();
	virtual void __fastcall DoOnUnregistering(bool &AHandled);
	virtual void __fastcall DoOnUnregistered();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall ProviderChanged();
	
public:
	__fastcall virtual TCustomEMSEdgeService(System::Classes::TComponent* AOwner);
	void __fastcall UnregisterModule();
	void __fastcall RegisterModule(System::Json::TJSONObject* const ADetails = (System::Json::TJSONObject*)(0x0));
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	__property System::UnicodeString ListenerProtocol = {read=FListenerProtocol, write=SetListenerProtocol};
	__property TEMSEdgeListener* ListenerService = {read=FListenerService};
	__property bool AutoActivate = {read=FAutoActivate, write=FAutoActivate, default=1};
	__property bool AutoRegister = {read=FAutoRegister, write=FAutoRegister, default=1};
	__property bool AutoUnRegister = {read=FAutoUnRegister, write=FAutoUnRegister, default=1};
	__property System::UnicodeString ModuleName = {read=FModuleName, write=SetModuleName};
	__property System::UnicodeString ModuleVersion = {read=FModuleVersion, write=SetModuleVersion};
	__property TBackendEdgemoduleApi* ModuleAPI = {read=GetModuleAPI};
	__property System::UnicodeString ModuleID = {read=GetModuleID};
	__property _di_IBackendEdgemoduleService ProviderService = {read=GetProviderService};
	__property TRegisteringEvent OnRegistering = {read=FOnRegistering, write=FOnRegistering};
	__property System::Classes::TNotifyEvent OnRegistered = {read=FOnRegistered, write=FOnRegistered};
	__property THandledEvent OnUnregistering = {read=FOnUnregistering, write=FOnUnregistering};
	__property System::Classes::TNotifyEvent OnUnregistered = {read=FOnUnregistered, write=FOnUnregistered};
	TBackendEdgemoduleApi* __fastcall CreateModuleAPI();
public:
	/* {REST_Backend_Providers}TBackendServiceComponentAuth<EMSHosting_EdgeService_IBackendEdgemoduleService,EMSHosting_EdgeService_TBackendEdgemoduleApi>.Destroy */ inline __fastcall virtual ~TCustomEMSEdgeService() { }
	
};


class PASCALIMPLEMENTATION TEMSEdgeService : public TCustomEMSEdgeService
{
	typedef TCustomEMSEdgeService inherited;
	
__published:
	__property AutoActivate = {default=1};
	__property AutoRegister = {default=1};
	__property AutoUnRegister = {default=1};
	__property ModuleName = {default=0};
	__property ModuleVersion = {default=0};
	__property Provider;
	__property Auth;
	__property ListenerProtocol = {default=0};
	__property ListenerService;
	__property OnRegistering;
	__property OnUnregistering;
	__property OnRegistered;
	__property OnUnregistered;
public:
	/* TCustomEMSEdgeService.Create */ inline __fastcall virtual TEMSEdgeService(System::Classes::TComponent* AOwner) : TCustomEMSEdgeService(AOwner) { }
	
public:
	/* {REST_Backend_Providers}TBackendServiceComponentAuth<EMSHosting_EdgeService_IBackendEdgemoduleService,EMSHosting_EdgeService_TBackendEdgemoduleApi>.Destroy */ inline __fastcall virtual ~TEMSEdgeService() { }
	
};


class PASCALIMPLEMENTATION TEMSEdgeListener : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
	
public:
	class DELPHICLASS TModule;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TModule : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		System::UnicodeString FModuleName;
		System::UnicodeString FModuleVersion;
		
	public:
		__fastcall TModule(const System::UnicodeString AModuleName, const System::UnicodeString AModuleVersion);
#ifndef _WIN64
		virtual System::DynamicArray<System::UnicodeString> __fastcall GetGroupsByUser(const System::UnicodeString AUserID, const System::UnicodeString ATenantId) = 0 ;
#else /* _WIN64 */
		virtual System::TArray__1<System::UnicodeString> __fastcall GetGroupsByUser(const System::UnicodeString AUserID, const System::UnicodeString ATenantId) = 0 ;
#endif /* _WIN64 */
		virtual bool __fastcall UserIDOfSession(const System::UnicodeString ASessionToken, /* out */ System::UnicodeString &AUserID) = 0 ;
		virtual bool __fastcall UserNameOfID(const System::UnicodeString AUserID, /* out */ System::UnicodeString &AUserName) = 0 ;
		virtual System::UnicodeString __fastcall GetTenantNameByTenantId(const System::UnicodeString ATenantId) = 0 ;
		__property System::UnicodeString ModuleName = {read=FModuleName};
		__property System::UnicodeString ModuleVersion = {read=FModuleVersion};
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TModule() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	class DELPHICLASS TModuleContext;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TModuleContext : public Emshosting::Requesttypes::TEMSEdgeHostContext
	{
		typedef Emshosting::Requesttypes::TEMSEdgeHostContext inherited;
		
	private:
		TEMSEdgeListener::TModule* FModule;
		
	protected:
		virtual System::UnicodeString __fastcall GetModuleName();
		virtual System::UnicodeString __fastcall GetModuleVersion();
#ifndef _WIN64
		virtual System::DynamicArray<System::UnicodeString> __fastcall GetGroupsByUser(const System::UnicodeString AUserID, const System::UnicodeString ATenantId);
#else /* _WIN64 */
		virtual System::TArray__1<System::UnicodeString> __fastcall GetGroupsByUser(const System::UnicodeString AUserID, const System::UnicodeString ATenantId);
#endif /* _WIN64 */
		virtual bool __fastcall UserIDOfSession(const System::UnicodeString ASessionID, /* out */ System::UnicodeString &AUserID);
		virtual bool __fastcall UserNameOfID(const System::UnicodeString AUserID, /* out */ System::UnicodeString &AUserName);
		virtual System::UnicodeString __fastcall GetTenantNameByTenantId(const System::UnicodeString ATenantId);
		
	public:
		__fastcall TModuleContext(TEMSEdgeListener::TModule* const AModule);
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TModuleContext() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	__interface DELPHIINTERFACE TCreateModuleEvent;
	typedef System::DelphiInterface<TCreateModuleEvent> _di_TCreateModuleEvent;
	__interface TCreateModuleEvent  : public System::IInterface 
	{
		virtual TEMSEdgeListener::TModule* __fastcall Invoke() = 0 ;
	};
	
	
private:
	System::Json::TJSONObject* FProtocolProps;
	_di_TCreateModuleEvent FOnCreateModule;
	System::Json::TJSONObject* __fastcall GetProtocolProps();
	
protected:
	TModule* __fastcall CreateModule();
	virtual bool __fastcall GetActive() = 0 ;
	virtual void __fastcall SetActive(const bool Value) = 0 ;
	virtual void __fastcall AddProtocolProps(System::Json::TJSONObject* const AProperties) = 0 ;
	virtual TModule* __fastcall GetModule() = 0 ;
	
public:
	__fastcall virtual ~TEMSEdgeListener();
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	__property TModule* Module = {read=GetModule};
	__property System::Json::TJSONObject* ProtocolProps = {read=GetProtocolProps};
	__property _di_TCreateModuleEvent OnCreateModule = {read=FOnCreateModule, write=FOnCreateModule};
public:
	/* TComponent.Create */ inline __fastcall virtual TEMSEdgeListener(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Edgeservice */
}	/* namespace Emshosting */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING_EDGESERVICE)
using namespace Emshosting::Edgeservice;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING)
using namespace Emshosting;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Emshosting_EdgeserviceHPP
