// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.EMSProvider.pas' rev: 34.00 (Android)

#ifndef Rest_Backend_EmsproviderHPP
#define Rest_Backend_EmsproviderHPP

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
#include <REST.Backend.EMSApi.hpp>
#include <REST.Client.hpp>
#include <REST.Backend.ServiceTypes.hpp>
#include <REST.Backend.MetaTypes.hpp>
#include <System.Net.URLClient.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
namespace Rest
{
namespace Backend
{
namespace Emsprovider
{
  _INIT_UNIT(Rest_Backend_Emsprovider);
}	/* namespace Emsprovider */
}	/* namespace Backend */
}	/* namespace Rest */

namespace Rest
{
namespace Backend
{
namespace Emsprovider
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomEMSConnectionInfo;
class DELPHICLASS TCustomEMSProvider;
class DELPHICLASS TEMSProvider;
class DELPHICLASS TEMSBackendService;
__interface DELPHIINTERFACE IGetEMSApi;
typedef System::DelphiInterface<IGetEMSApi> _di_IGetEMSApi;
class DELPHICLASS TEMSServiceAPI;
class DELPHICLASS TEMSServiceAPIAuth;
template<typename TAPI> class DELPHICLASS TEMSBackendService__1;
class DELPHICLASS EEMSProviderError;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomEMSConnectionInfo : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
	
public:
	class DELPHICLASS TNotifyList;
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
	
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TProtocolNames
	{
	public:
		#define TCustomEMSConnectionInfo_TProtocolNames_HTTP u"http"
		
		#define TCustomEMSConnectionInfo_TProtocolNames_HTTPS u"https"
		
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
	class DELPHICLASS TAndroidPush;
	class PASCALIMPLEMENTATION TAndroidPush : public System::Classes::TPersistent
	{
		typedef System::Classes::TPersistent inherited;
		
	private:
		TCustomEMSConnectionInfo* FOwner;
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
	
	
	
private:
	Rest::Backend::Emsapi::TEMSClientAPI::TConnectionInfo FConnectionInfo;
	TNotifyList* FNotifyOnChange;
	System::UnicodeString FURLBasePath;
	int FURLPort;
	System::UnicodeString FURLHost;
	System::UnicodeString FURLProtocol;
	TAndroidPush* FAndroidPush;
	System::Net::Urlclient::TValidateCertificateEvent FOnValidateCertificate;
	void __fastcall SetApiVersion(const System::UnicodeString Value);
	void __fastcall SetAppSecret(const System::UnicodeString Value);
	void __fastcall SetMasterSecret(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetApiVersion();
	System::UnicodeString __fastcall GetAppSecret();
	System::UnicodeString __fastcall GetMasterSecret();
	System::UnicodeString __fastcall GetPassword();
	System::UnicodeString __fastcall GetLoginResource();
	System::UnicodeString __fastcall GetUserName();
	void __fastcall SetLoginResource(const System::UnicodeString Value);
	void __fastcall SetPassword(const System::UnicodeString Value);
	void __fastcall SetUserName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetProxyPassword();
	int __fastcall GetProxyPort();
	System::UnicodeString __fastcall GetProxyServer();
	System::UnicodeString __fastcall GetProxyUsername();
	void __fastcall SetProxyPassword(const System::UnicodeString Value);
	void __fastcall SetProxyPort(const int Value);
	void __fastcall SetProxyServer(const System::UnicodeString Value);
	void __fastcall SetProxyUsername(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetBaseURL();
	bool __fastcall IsURLProtocolStored();
	void __fastcall SetURLProtocol(const System::UnicodeString Value);
	void __fastcall SetURLBasePath(const System::UnicodeString Value);
	void __fastcall SetURLHost(const System::UnicodeString Value);
	void __fastcall SetURLPort(const int Value);
	System::UnicodeString __fastcall GetApplicationId();
	void __fastcall SetApplicationId(const System::UnicodeString Value);
	void __fastcall SetAndroidPush(TAndroidPush* const Value);
	void __fastcall SetOnValidateCertificate(const System::Net::Urlclient::TValidateCertificateEvent Value);
	System::UnicodeString __fastcall GetTenantId();
	void __fastcall SetTenantId(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTenantSecret();
	void __fastcall SetTenantSecret(const System::UnicodeString Value);
	
protected:
	virtual void __fastcall DoChanged();
	__property TNotifyList* NotifyOnChange = {read=FNotifyOnChange};
	
public:
	__fastcall virtual TCustomEMSConnectionInfo(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomEMSConnectionInfo();
	void __fastcall UpdateApi(Rest::Backend::Emsapi::TEMSClientAPI* const AApi);
	void __fastcall AppHandshake(const Rest::Backend::Emsapi::TEMSClientAPI::_di_TAppHandshakeProc ACallback);
	void __fastcall CheckURL();
	__property System::UnicodeString URLProtocol = {read=FURLProtocol, write=SetURLProtocol, stored=IsURLProtocolStored};
	__property System::UnicodeString URLHost = {read=FURLHost, write=SetURLHost};
	__property int URLPort = {read=FURLPort, write=SetURLPort, nodefault};
	__property System::UnicodeString URLBasePath = {read=FURLBasePath, write=SetURLBasePath};
	__property System::Net::Urlclient::TValidateCertificateEvent OnValidateCertificate = {read=FOnValidateCertificate, write=SetOnValidateCertificate};
	__property TAndroidPush* AndroidPush = {read=FAndroidPush, write=SetAndroidPush};
	__property System::UnicodeString ApiVersion = {read=GetApiVersion, write=SetApiVersion};
	__property System::UnicodeString AppSecret = {read=GetAppSecret, write=SetAppSecret};
	__property System::UnicodeString ApplicationId = {read=GetApplicationId, write=SetApplicationId};
	__property System::UnicodeString MasterSecret = {read=GetMasterSecret, write=SetMasterSecret};
	__property System::UnicodeString BaseURL = {read=GetBaseURL};
	__property System::UnicodeString UserName = {read=GetUserName, write=SetUserName};
	__property System::UnicodeString LoginResource = {read=GetLoginResource, write=SetLoginResource};
	__property System::UnicodeString Password = {read=GetPassword, write=SetPassword};
	__property System::UnicodeString ProxyPassword = {read=GetProxyPassword, write=SetProxyPassword};
	__property int ProxyPort = {read=GetProxyPort, write=SetProxyPort, default=0};
	__property System::UnicodeString ProxyServer = {read=GetProxyServer, write=SetProxyServer};
	__property System::UnicodeString ProxyUsername = {read=GetProxyUsername, write=SetProxyUsername};
	__property System::UnicodeString TenantId = {read=GetTenantId, write=SetTenantId};
	__property System::UnicodeString TenantSecret = {read=GetTenantSecret, write=SetTenantSecret};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomEMSProvider : public TCustomEMSConnectionInfo
{
	typedef TCustomEMSConnectionInfo inherited;
	
public:
	#define TCustomEMSProvider_ProviderID u"EMS"
	
	
protected:
	System::UnicodeString __fastcall GetProviderID();
public:
	/* TCustomEMSConnectionInfo.Create */ inline __fastcall virtual TCustomEMSProvider(System::Classes::TComponent* AOwner) : TCustomEMSConnectionInfo(AOwner) { }
	/* TCustomEMSConnectionInfo.Destroy */ inline __fastcall virtual ~TCustomEMSProvider() { }
	
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSProvider : public TCustomEMSProvider
{
	typedef TCustomEMSProvider inherited;
	
__published:
	__property AndroidPush;
	__property ApiVersion = {default=0};
	__property ApplicationId = {default=0};
	__property AppSecret = {default=0};
	__property MasterSecret = {default=0};
	__property LoginResource = {default=0};
	__property URLProtocol;
	__property URLHost = {default=0};
	__property URLPort;
	__property URLBasePath = {default=0};
	__property ProxyPassword = {default=0};
	__property ProxyPort = {default=0};
	__property ProxyServer = {default=0};
	__property ProxyUsername = {default=0};
	__property TenantId = {default=0};
	__property TenantSecret = {default=0};
	__property OnValidateCertificate;
public:
	/* TCustomEMSConnectionInfo.Create */ inline __fastcall virtual TEMSProvider(System::Classes::TComponent* AOwner) : TCustomEMSProvider(AOwner) { }
	/* TCustomEMSConnectionInfo.Destroy */ inline __fastcall virtual ~TEMSProvider() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSBackendService : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	TCustomEMSConnectionInfo* FConnectionInfo;
	void __fastcall SetConnectionInfo(TCustomEMSConnectionInfo* const Value);
	void __fastcall OnConnectionChanged(System::TObject* Sender);
	
protected:
	virtual void __fastcall DoAfterConnectionChanged();
	__property TCustomEMSConnectionInfo* ConnectionInfo = {read=FConnectionInfo, write=SetConnectionInfo};
	
public:
	__fastcall virtual TEMSBackendService(const Rest::Backend::Providers::_di_IBackendProvider AProvider);
	__fastcall virtual ~TEMSBackendService();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{554D8251-5BC6-4542-AD35-0EAC3F3031DE}") IGetEMSApi  : public System::IInterface 
{
	virtual Rest::Backend::Emsapi::TEMSClientAPI* __fastcall GetEMSAPI() = 0 ;
	__property Rest::Backend::Emsapi::TEMSClientAPI* EMSAPI = {read=GetEMSAPI};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSServiceAPI : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Rest::Backend::Emsapi::TEMSClientAPI* FEMSAPI;
	Rest::Backend::Emsapi::TEMSClientAPI* __fastcall GetEMSAPI();
	
protected:
	__property Rest::Backend::Emsapi::TEMSClientAPI* EMSAPI = {read=FEMSAPI};
	
public:
	__fastcall TEMSServiceAPI();
	__fastcall virtual ~TEMSServiceAPI();
private:
	void *__IGetEMSApi;	// IGetEMSApi 
	void *__IBackendApi;	// Rest::Backend::Providers::IBackendApi 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {554D8251-5BC6-4542-AD35-0EAC3F3031DE}
	operator _di_IGetEMSApi()
	{
		_di_IGetEMSApi intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IGetEMSApi*(void) { return (IGetEMSApi*)&__IGetEMSApi; }
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSServiceAPIAuth : public TEMSServiceAPI
{
	typedef TEMSServiceAPI inherited;
	
protected:
	void __fastcall Login(const Rest::Backend::Metatypes::TBackendEntityValue &ALogin);
	void __fastcall Logout();
	void __fastcall SetDefaultAuthentication(Rest::Backend::Providers::TBackendDefaultAuthentication ADefaultAuthentication);
	Rest::Backend::Providers::TBackendDefaultAuthentication __fastcall GetDefaultAuthentication();
	void __fastcall SetAuthentication(Rest::Backend::Providers::TBackendAuthentication AAuthentication);
	Rest::Backend::Providers::TBackendAuthentication __fastcall GetAuthentication();
public:
	/* TEMSServiceAPI.Create */ inline __fastcall TEMSServiceAPIAuth() : TEMSServiceAPI() { }
	/* TEMSServiceAPI.Destroy */ inline __fastcall virtual ~TEMSServiceAPIAuth() { }
	
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename TAPI> class PASCALIMPLEMENTATION TEMSBackendService__1 : public TEMSBackendService
{
	typedef TEMSBackendService inherited;
	
private:
	TAPI FBackendAPI;
	System::_di_IInterface FBackendAPIIntf;
	Rest::Backend::Emsapi::TEMSClientAPI* __fastcall GetEMSAPI();
	
protected:
	virtual TAPI __fastcall CreateBackendApi();
	void __fastcall EnsureBackendApi();
	virtual void __fastcall DoAfterConnectionChanged();
	__property TAPI BackendAPI = {read=FBackendAPI};
public:
	/* TEMSBackendService.Create */ inline __fastcall virtual TEMSBackendService__1(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : TEMSBackendService(AProvider) { }
	/* TEMSBackendService.Destroy */ inline __fastcall virtual ~TEMSBackendService__1() { }
	
private:
	void *__IGetEMSApi;	// IGetEMSApi 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {554D8251-5BC6-4542-AD35-0EAC3F3031DE}
	operator _di_IGetEMSApi()
	{
		_di_IGetEMSApi intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IGetEMSApi*(void) { return (IGetEMSApi*)&__IGetEMSApi; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EEMSProviderError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EEMSProviderError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EEMSProviderError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSProviderError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSProviderError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSProviderError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSProviderError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSProviderError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSProviderError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSProviderError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSProviderError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSProviderError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSProviderError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSProviderError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Emsprovider */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_EMSPROVIDER)
using namespace Rest::Backend::Emsprovider;
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
#endif	// Rest_Backend_EmsproviderHPP
