// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.KinveyProvider.pas' rev: 34.00 (Windows)

#ifndef Rest_Backend_KinveyproviderHPP
#define Rest_Backend_KinveyproviderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <REST.Backend.Providers.hpp>
#include <REST.Backend.KinveyApi.hpp>
#include <REST.Client.hpp>
#include <REST.Backend.ServiceTypes.hpp>
#include <REST.Backend.MetaTypes.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "REST.Backend.KinveyProvider"

namespace Rest
{
namespace Backend
{
namespace Kinveyprovider
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomKinveyConnectionInfo;
class DELPHICLASS TCustomKinveyProvider;
class DELPHICLASS TKinveyProvider;
class DELPHICLASS TKinveyBackendService;
__interface DELPHIINTERFACE IGetKinveyAPI;
typedef System::DelphiInterface<IGetKinveyAPI> _di_IGetKinveyAPI;
class DELPHICLASS TKinveyServiceAPI;
class DELPHICLASS TKinveyServiceAPIAuth;
template<typename TAPI> class DELPHICLASS TKinveyBackendService__1;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomKinveyConnectionInfo : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
	
public:
	class DELPHICLASS TNotifyList;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TNotifyList : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		System::Generics::Collections::TList__1<System::Classes::TNotifyEvent>* FList;
		void __fastcall Notify(System::TObject* Sender);
		
	public:
		__fastcall TNotifyList();
		__fastcall virtual ~TNotifyList();
		void __fastcall Add(const System::Classes::TNotifyEvent ANotify);
		void __fastcall Remove(const System::Classes::TNotifyEvent ANotify);
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	class DELPHICLASS TAndroidPush;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TAndroidPush : public System::Classes::TPersistent
	{
		typedef System::Classes::TPersistent inherited;
		
	private:
		TCustomKinveyConnectionInfo* FOwner;
		System::UnicodeString FGCMAppID;
		void __fastcall SetGCMAppID(const System::UnicodeString Value);
		
	protected:
		virtual void __fastcall AssignTo(System::Classes::TPersistent* AValue);
		
	__published:
		__property System::UnicodeString GCMAppID = {read=FGCMAppID, write=SetGCMAppID};
	public:
		/* TPersistent.Destroy */ inline __fastcall virtual ~TAndroidPush() { }
		
	public:
		/* TObject.Create */ inline __fastcall TAndroidPush() : System::Classes::TPersistent() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
private:
	Rest::Backend::Kinveyapi::TKinveyApi::TConnectionInfo FConnectionInfo;
	TNotifyList* FNotifyOnChange;
	TAndroidPush* FAndroidPush;
	System::UnicodeString FPushEndpoint;
	void __fastcall SetApiVersion(const System::UnicodeString Value);
	void __fastcall SetAppSecret(const System::UnicodeString Value);
	void __fastcall SetAppKey(const System::UnicodeString Value);
	void __fastcall SetMasterSecret(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetApiVersion();
	System::UnicodeString __fastcall GetAppKey();
	System::UnicodeString __fastcall GetAppSecret();
	System::UnicodeString __fastcall GetMasterSecret();
	void __fastcall SetAndroidPush(TAndroidPush* const Value);
	System::UnicodeString __fastcall GetPassword();
	System::UnicodeString __fastcall GetUserName();
	void __fastcall SetPassword(const System::UnicodeString Value);
	void __fastcall SetUserName(const System::UnicodeString Value);
	void __fastcall SetPushEndpoint(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetProxyPassword();
	int __fastcall GetProxyPort();
	System::UnicodeString __fastcall GetProxyServer();
	System::UnicodeString __fastcall GetProxyUsername();
	void __fastcall SetProxyPassword(const System::UnicodeString Value);
	void __fastcall SetProxyPort(const int Value);
	void __fastcall SetProxyServer(const System::UnicodeString Value);
	void __fastcall SetProxyUsername(const System::UnicodeString Value);
	
protected:
	virtual void __fastcall DoChanged();
	__property TNotifyList* NotifyOnChange = {read=FNotifyOnChange};
	
public:
	__fastcall virtual TCustomKinveyConnectionInfo(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomKinveyConnectionInfo();
	void __fastcall UpdateApi(Rest::Backend::Kinveyapi::TKinveyApi* const AApi);
	__property System::UnicodeString ApiVersion = {read=GetApiVersion, write=SetApiVersion};
	__property System::UnicodeString AppSecret = {read=GetAppSecret, write=SetAppSecret};
	__property System::UnicodeString AppKey = {read=GetAppKey, write=SetAppKey};
	__property System::UnicodeString MasterSecret = {read=GetMasterSecret, write=SetMasterSecret};
	__property System::UnicodeString UserName = {read=GetUserName, write=SetUserName};
	__property System::UnicodeString Password = {read=GetPassword, write=SetPassword};
	__property TAndroidPush* AndroidPush = {read=FAndroidPush, write=SetAndroidPush};
	__property System::UnicodeString PushEndpoint = {read=FPushEndpoint, write=SetPushEndpoint};
	__property System::UnicodeString ProxyPassword = {read=GetProxyPassword, write=SetProxyPassword};
	__property int ProxyPort = {read=GetProxyPort, write=SetProxyPort, default=0};
	__property System::UnicodeString ProxyServer = {read=GetProxyServer, write=SetProxyServer};
	__property System::UnicodeString ProxyUsername = {read=GetProxyUsername, write=SetProxyUsername};
};


class PASCALIMPLEMENTATION TCustomKinveyProvider : public TCustomKinveyConnectionInfo
{
	typedef TCustomKinveyConnectionInfo inherited;
	
public:
	#define TCustomKinveyProvider_ProviderID L"Kinvey"
	
	
protected:
	System::UnicodeString __fastcall GetProviderID();
public:
	/* TCustomKinveyConnectionInfo.Create */ inline __fastcall virtual TCustomKinveyProvider(System::Classes::TComponent* AOwner) : TCustomKinveyConnectionInfo(AOwner) { }
	/* TCustomKinveyConnectionInfo.Destroy */ inline __fastcall virtual ~TCustomKinveyProvider() { }
	
private:
	void *__IBackendProvider;	// Rest::Backend::Providers::IBackendProvider 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C563AC66-8AF4-45D8-906C-161B061B912F}
	operator Rest::Backend::Providers::_di_IBackendProvider()
	{
		Rest::Backend::Providers::_di_IBackendProvider intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Providers::IBackendProvider*(void) { return (Rest::Backend::Providers::IBackendProvider*)&__IBackendProvider; }
	#endif
	
};


class PASCALIMPLEMENTATION TKinveyProvider : public TCustomKinveyProvider
{
	typedef TCustomKinveyProvider inherited;
	
__published:
	__property ApiVersion = {default=0};
	__property AppKey = {default=0};
	__property AppSecret = {default=0};
	__property MasterSecret = {default=0};
	__property UserName = {default=0};
	__property Password = {default=0};
	__property AndroidPush;
	__property PushEndpoint = {default=0};
	__property ProxyPassword = {default=0};
	__property ProxyPort = {default=0};
	__property ProxyServer = {default=0};
	__property ProxyUsername = {default=0};
public:
	/* TCustomKinveyConnectionInfo.Create */ inline __fastcall virtual TKinveyProvider(System::Classes::TComponent* AOwner) : TCustomKinveyProvider(AOwner) { }
	/* TCustomKinveyConnectionInfo.Destroy */ inline __fastcall virtual ~TKinveyProvider() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TKinveyBackendService : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	TCustomKinveyConnectionInfo* FConnectionInfo;
	void __fastcall SetConnectionInfo(TCustomKinveyConnectionInfo* const Value);
	void __fastcall OnConnectionChanged(System::TObject* Sender);
	
protected:
	virtual void __fastcall DoAfterConnectionChanged();
	__property TCustomKinveyConnectionInfo* ConnectionInfo = {read=FConnectionInfo, write=SetConnectionInfo};
	
public:
	__fastcall virtual TKinveyBackendService(const Rest::Backend::Providers::_di_IBackendProvider AProvider);
	__fastcall virtual ~TKinveyBackendService();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{ACEF8B21-82B8-4B61-B796-DB09CDCE962C}") IGetKinveyAPI  : public System::IInterface 
{
	virtual Rest::Backend::Kinveyapi::TKinveyApi* __fastcall GetKinveyAPI() = 0 ;
	__property Rest::Backend::Kinveyapi::TKinveyApi* KinveyAPI = {read=GetKinveyAPI};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TKinveyServiceAPI : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Rest::Backend::Kinveyapi::TKinveyApi* FKinveyAPI;
	Rest::Backend::Kinveyapi::TKinveyApi* __fastcall GetKinveyAPI();
	
protected:
	__property Rest::Backend::Kinveyapi::TKinveyApi* KinveyAPI = {read=FKinveyAPI};
	
public:
	__fastcall TKinveyServiceAPI();
	__fastcall virtual ~TKinveyServiceAPI();
private:
	void *__IGetKinveyAPI;	// IGetKinveyAPI 
	void *__IBackendApi;	// Rest::Backend::Providers::IBackendApi 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {ACEF8B21-82B8-4B61-B796-DB09CDCE962C}
	operator _di_IGetKinveyAPI()
	{
		_di_IGetKinveyAPI intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IGetKinveyAPI*(void) { return (IGetKinveyAPI*)&__IGetKinveyAPI; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B2608078-946B-475D-B2DD-8523FDC1C773}
	operator Rest::Backend::Providers::_di_IBackendApi()
	{
		Rest::Backend::Providers::_di_IBackendApi intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Providers::IBackendApi*(void) { return (Rest::Backend::Providers::IBackendApi*)&__IBackendApi; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TKinveyServiceAPIAuth : public TKinveyServiceAPI
{
	typedef TKinveyServiceAPI inherited;
	
protected:
	void __fastcall Login(const Rest::Backend::Metatypes::TBackendEntityValue &ALogin);
	void __fastcall Logout();
	void __fastcall SetDefaultAuthentication(Rest::Backend::Providers::TBackendDefaultAuthentication ADefaultAuthentication);
	Rest::Backend::Providers::TBackendDefaultAuthentication __fastcall GetDefaultAuthentication();
	void __fastcall SetAuthentication(Rest::Backend::Providers::TBackendAuthentication AAuthentication);
	Rest::Backend::Providers::TBackendAuthentication __fastcall GetAuthentication();
public:
	/* TKinveyServiceAPI.Create */ inline __fastcall TKinveyServiceAPIAuth() : TKinveyServiceAPI() { }
	/* TKinveyServiceAPI.Destroy */ inline __fastcall virtual ~TKinveyServiceAPIAuth() { }
	
private:
	void *__IBackendAuthenticationApi;	// Rest::Backend::Servicetypes::IBackendAuthenticationApi 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {4C0D2ADD-B6B7-40ED-B6B5-5DB66B7ECE9D}
	operator Rest::Backend::Servicetypes::_di_IBackendAuthenticationApi()
	{
		Rest::Backend::Servicetypes::_di_IBackendAuthenticationApi intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Servicetypes::IBackendAuthenticationApi*(void) { return (Rest::Backend::Servicetypes::IBackendAuthenticationApi*)&__IBackendAuthenticationApi; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename TAPI> class PASCALIMPLEMENTATION TKinveyBackendService__1 : public TKinveyBackendService
{
	typedef TKinveyBackendService inherited;
	
private:
	TAPI FBackendAPI;
	System::_di_IInterface FBackendAPIIntf;
	void __fastcall ReleaseBackendApi();
	Rest::Backend::Kinveyapi::TKinveyApi* __fastcall GetKinveyAPI();
	
protected:
	virtual TAPI __fastcall CreateBackendApi();
	void __fastcall EnsureBackendApi();
	virtual void __fastcall DoAfterConnectionChanged();
	__property TAPI BackendAPI = {read=FBackendAPI};
public:
	/* TKinveyBackendService.Create */ inline __fastcall virtual TKinveyBackendService__1(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : TKinveyBackendService(AProvider) { }
	/* TKinveyBackendService.Destroy */ inline __fastcall virtual ~TKinveyBackendService__1() { }
	
private:
	void *__IGetKinveyAPI;	// IGetKinveyAPI 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {ACEF8B21-82B8-4B61-B796-DB09CDCE962C}
	operator _di_IGetKinveyAPI()
	{
		_di_IGetKinveyAPI intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IGetKinveyAPI*(void) { return (IGetKinveyAPI*)&__IGetKinveyAPI; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Kinveyprovider */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_KINVEYPROVIDER)
using namespace Rest::Backend::Kinveyprovider;
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
#endif	// Rest_Backend_KinveyproviderHPP
