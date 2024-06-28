// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.ParseProvider.pas' rev: 34.00 (Windows)

#ifndef Rest_Backend_ParseproviderHPP
#define Rest_Backend_ParseproviderHPP

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
#include <REST.Backend.ParseApi.hpp>
#include <REST.Client.hpp>
#include <REST.Backend.ServiceTypes.hpp>
#include <REST.Backend.MetaTypes.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "REST.Backend.ParseProvider"

namespace Rest
{
namespace Backend
{
namespace Parseprovider
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomParseConnectionInfo;
class DELPHICLASS TCustomParseProvider;
class DELPHICLASS TParseProvider;
class DELPHICLASS TParseBackendService;
__interface DELPHIINTERFACE IGetParseAPI;
typedef System::DelphiInterface<IGetParseAPI> _di_IGetParseAPI;
class DELPHICLASS TParseServiceAPI;
class DELPHICLASS TParseServiceAPIAuth;
template<typename TAPI> class DELPHICLASS TParseBackendService__1;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomParseConnectionInfo : public System::Classes::TComponent
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
		#define TCustomParseConnectionInfo_TAndroidPush_cDefaultGCMAppID L"1076345567071"
		
		System::UnicodeString FGCMAppID;
		System::UnicodeString FInstallationID;
		bool FHaveID;
		void __fastcall ReadBlank(System::Classes::TReader* Reader);
		void __fastcall WriteBlank(System::Classes::TWriter* Writer);
		System::UnicodeString __fastcall GetGCMAppID();
		void __fastcall SetGCMAppID(const System::UnicodeString Value);
		System::UnicodeString __fastcall GetInstallationID();
		void __fastcall SetInstallationID(const System::UnicodeString Value);
		bool __fastcall IsGCMAppIDStored();
		
	protected:
		virtual void __fastcall AssignTo(System::Classes::TPersistent* AValue);
		virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
		
	public:
		__fastcall TAndroidPush();
		__classmethod System::UnicodeString __fastcall NewInstallationID();
		
	__published:
		__property System::UnicodeString GCMAppID = {read=GetGCMAppID, write=SetGCMAppID, stored=IsGCMAppIDStored};
		__property System::UnicodeString InstallationID = {read=GetInstallationID, write=SetInstallationID, stored=true};
	public:
		/* TPersistent.Destroy */ inline __fastcall virtual ~TAndroidPush() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
private:
	System::UnicodeString FBaseURL;
	Rest::Backend::Parseapi::TParseApi::TConnectionInfo FConnectionInfo;
	TNotifyList* FNotifyOnChange;
	TAndroidPush* FAndroidPush;
	void __fastcall SetApiVersion(const System::UnicodeString Value);
	void __fastcall SetApplicationID(const System::UnicodeString Value);
	void __fastcall SetRestApiKey(const System::UnicodeString Value);
	void __fastcall SetMasterKey(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetApiVersion();
	System::UnicodeString __fastcall GetRestApiKey();
	System::UnicodeString __fastcall GetMasterKey();
	System::UnicodeString __fastcall GetApplicationID();
	void __fastcall SetAndroidPush(TAndroidPush* const Value);
	System::UnicodeString __fastcall GetProxyPassword();
	int __fastcall GetProxyPort();
	System::UnicodeString __fastcall GetProxyServer();
	System::UnicodeString __fastcall GetProxyUsername();
	void __fastcall SetProxyPassword(const System::UnicodeString Value);
	void __fastcall SetProxyPort(const int Value);
	void __fastcall SetProxyServer(const System::UnicodeString Value);
	void __fastcall SetProxyUsername(const System::UnicodeString Value);
	void __fastcall SetBaseURL(const System::UnicodeString Value);
	
protected:
	virtual void __fastcall DoChanged();
	__property TNotifyList* NotifyOnChange = {read=FNotifyOnChange};
	
public:
	__fastcall virtual TCustomParseConnectionInfo(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomParseConnectionInfo();
	void __fastcall UpdateApi(Rest::Backend::Parseapi::TParseApi* const AParseApi);
	__property System::UnicodeString BaseURL = {read=FBaseURL, write=SetBaseURL};
	__property System::UnicodeString ApiVersion = {read=GetApiVersion, write=SetApiVersion};
	__property System::UnicodeString ApplicationID = {read=GetApplicationID, write=SetApplicationID};
	__property System::UnicodeString RestApiKey = {read=GetRestApiKey, write=SetRestApiKey};
	__property System::UnicodeString MasterKey = {read=GetMasterKey, write=SetMasterKey};
	__property TAndroidPush* AndroidPush = {read=FAndroidPush, write=SetAndroidPush};
	__property System::UnicodeString ProxyPassword = {read=GetProxyPassword, write=SetProxyPassword};
	__property int ProxyPort = {read=GetProxyPort, write=SetProxyPort, default=0};
	__property System::UnicodeString ProxyServer = {read=GetProxyServer, write=SetProxyServer};
	__property System::UnicodeString ProxyUsername = {read=GetProxyUsername, write=SetProxyUsername};
};


class PASCALIMPLEMENTATION TCustomParseProvider : public TCustomParseConnectionInfo
{
	typedef TCustomParseConnectionInfo inherited;
	
public:
	#define TCustomParseProvider_ProviderID L"Parse"
	
	
protected:
	System::UnicodeString __fastcall GetProviderID();
public:
	/* TCustomParseConnectionInfo.Create */ inline __fastcall virtual TCustomParseProvider(System::Classes::TComponent* AOwner) : TCustomParseConnectionInfo(AOwner) { }
	/* TCustomParseConnectionInfo.Destroy */ inline __fastcall virtual ~TCustomParseProvider() { }
	
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


class PASCALIMPLEMENTATION TParseProvider : public TCustomParseProvider
{
	typedef TCustomParseProvider inherited;
	
__published:
	__property BaseURL = {default=0};
	__property ApiVersion = {default=0};
	__property ApplicationID = {default=0};
	__property RestApiKey = {default=0};
	__property MasterKey = {default=0};
	__property AndroidPush;
	__property ProxyPassword = {default=0};
	__property ProxyPort = {default=0};
	__property ProxyServer = {default=0};
	__property ProxyUsername = {default=0};
public:
	/* TCustomParseConnectionInfo.Create */ inline __fastcall virtual TParseProvider(System::Classes::TComponent* AOwner) : TCustomParseProvider(AOwner) { }
	/* TCustomParseConnectionInfo.Destroy */ inline __fastcall virtual ~TParseProvider() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TParseBackendService : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	TCustomParseConnectionInfo* FConnectionInfo;
	void __fastcall SetConnectionInfo(TCustomParseConnectionInfo* const Value);
	void __fastcall OnConnectionChanged(System::TObject* Sender);
	
protected:
	virtual void __fastcall DoAfterConnectionChanged();
	__property TCustomParseConnectionInfo* ConnectionInfo = {read=FConnectionInfo, write=SetConnectionInfo};
	
public:
	__fastcall virtual TParseBackendService(const Rest::Backend::Providers::_di_IBackendProvider AProvider);
	__fastcall virtual ~TParseBackendService();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{9EFB309D-6A53-4F3B-8B7F-D9E7D92998E8}") IGetParseAPI  : public System::IInterface 
{
	virtual Rest::Backend::Parseapi::TParseApi* __fastcall GetParseAPI() = 0 ;
	__property Rest::Backend::Parseapi::TParseApi* ParseAPI = {read=GetParseAPI};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TParseServiceAPI : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Rest::Backend::Parseapi::TParseApi* FParseAPI;
	Rest::Backend::Parseapi::TParseApi* __fastcall GetParseAPI();
	
protected:
	__property Rest::Backend::Parseapi::TParseApi* ParseAPI = {read=FParseAPI};
	
public:
	__fastcall TParseServiceAPI();
	__fastcall virtual ~TParseServiceAPI();
private:
	void *__IGetParseAPI;	// IGetParseAPI 
	void *__IBackendApi;	// Rest::Backend::Providers::IBackendApi 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9EFB309D-6A53-4F3B-8B7F-D9E7D92998E8}
	operator _di_IGetParseAPI()
	{
		_di_IGetParseAPI intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IGetParseAPI*(void) { return (IGetParseAPI*)&__IGetParseAPI; }
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
class PASCALIMPLEMENTATION TParseServiceAPIAuth : public TParseServiceAPI
{
	typedef TParseServiceAPI inherited;
	
protected:
	void __fastcall Login(const Rest::Backend::Metatypes::TBackendEntityValue &ALogin);
	void __fastcall Logout();
	void __fastcall SetDefaultAuthentication(Rest::Backend::Providers::TBackendDefaultAuthentication ADefaultAuthentication);
	Rest::Backend::Providers::TBackendDefaultAuthentication __fastcall GetDefaultAuthentication();
	void __fastcall SetAuthentication(Rest::Backend::Providers::TBackendAuthentication AAuthentication);
	Rest::Backend::Providers::TBackendAuthentication __fastcall GetAuthentication();
public:
	/* TParseServiceAPI.Create */ inline __fastcall TParseServiceAPIAuth() : TParseServiceAPI() { }
	/* TParseServiceAPI.Destroy */ inline __fastcall virtual ~TParseServiceAPIAuth() { }
	
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
template<typename TAPI> class PASCALIMPLEMENTATION TParseBackendService__1 : public TParseBackendService
{
	typedef TParseBackendService inherited;
	
private:
	TAPI FBackendAPI;
	System::_di_IInterface FBackendAPIIntf;
	void __fastcall ReleaseBackendApi();
	Rest::Backend::Parseapi::TParseApi* __fastcall GetParseAPI();
	
protected:
	virtual TAPI __fastcall CreateBackendApi();
	void __fastcall EnsureBackendApi();
	virtual void __fastcall DoAfterConnectionChanged();
	__property TAPI BackendAPI = {read=FBackendAPI};
public:
	/* TParseBackendService.Create */ inline __fastcall virtual TParseBackendService__1(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : TParseBackendService(AProvider) { }
	/* TParseBackendService.Destroy */ inline __fastcall virtual ~TParseBackendService__1() { }
	
private:
	void *__IGetParseAPI;	// IGetParseAPI 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9EFB309D-6A53-4F3B-8B7F-D9E7D92998E8}
	operator _di_IGetParseAPI()
	{
		_di_IGetParseAPI intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IGetParseAPI*(void) { return (IGetParseAPI*)&__IGetParseAPI; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Parseprovider */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_PARSEPROVIDER)
using namespace Rest::Backend::Parseprovider;
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
#endif	// Rest_Backend_ParseproviderHPP
