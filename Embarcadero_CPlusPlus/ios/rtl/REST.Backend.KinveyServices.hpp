// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.KinveyServices.pas' rev: 34.00 (iOS)

#ifndef Rest_Backend_KinveyservicesHPP
#define Rest_Backend_KinveyservicesHPP

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
#include <REST.Backend.Providers.hpp>
#include <REST.Backend.PushTypes.hpp>
#include <REST.Backend.ServiceTypes.hpp>
#include <REST.Backend.MetaTypes.hpp>
#include <REST.Backend.KinveyApi.hpp>
#include <REST.Backend.KinveyProvider.hpp>

//-- user supplied -----------------------------------------------------------
namespace Rest
{
namespace Backend
{
namespace Kinveyservices
{
  _INIT_UNIT(Rest_Backend_Kinveyservices);
}	/* namespace Kinveyservices */
}	/* namespace Backend */
}	/* namespace Rest */

namespace Rest
{
namespace Backend
{
namespace Kinveyservices
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TKinveyFilesAPI;
class DELPHICLASS TKinveyFilesService;
class DELPHICLASS TKinveyPushAPI;
class DELPHICLASS TKinveyPushService;
class DELPHICLASS TKinveyQueryAPI;
class DELPHICLASS TKinveyQueryService;
class DELPHICLASS TKinveyLoginAPI;
class DELPHICLASS TKinveyLoginService;
class DELPHICLASS TKinveyUsersAPI;
class DELPHICLASS TKinveyUsersService;
class DELPHICLASS TKinveyStorageAPI;
class DELPHICLASS TKinveyStorageService;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TKinveyFilesAPI : public Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth
{
	typedef Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth inherited;
	
protected:
	Rest::Backend::Metatypes::_di_IBackendMetaFactory __fastcall GetMetaFactory();
	void __fastcall UploadFile(const System::UnicodeString AFileName, const System::UnicodeString AContentType, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AFile)/* overload */;
	void __fastcall UploadFile(const System::UnicodeString AFileName, System::Classes::TStream* const AStream, const System::UnicodeString AContentType, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AFile)/* overload */;
	bool __fastcall DeleteFile(const Rest::Backend::Metatypes::TBackendEntityValue &AFile);
public:
	/* TKinveyServiceAPI.Create */ inline __fastcall TKinveyFilesAPI() : Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth() { }
	/* TKinveyServiceAPI.Destroy */ inline __fastcall virtual ~TKinveyFilesAPI() { }
	
private:
	void *__IBackendFilesApi;	// Rest::Backend::Servicetypes::IBackendFilesApi 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {271C2472-D957-47C5-BC10-F3A15FF5261C}
	operator Rest::Backend::Servicetypes::_di_IBackendFilesApi()
	{
		Rest::Backend::Servicetypes::_di_IBackendFilesApi intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Servicetypes::IBackendFilesApi*(void) { return (Rest::Backend::Servicetypes::IBackendFilesApi*)&__IBackendFilesApi; }
	#endif
	
};


class PASCALIMPLEMENTATION TKinveyFilesService : public Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyFilesAPI*>
{
	typedef Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyFilesAPI*> inherited;
	
protected:
	Rest::Backend::Servicetypes::_di_IBackendFilesApi __fastcall CreateFilesApi();
	Rest::Backend::Servicetypes::_di_IBackendFilesApi __fastcall GetFilesApi();
public:
	/* TKinveyBackendService.Create */ inline __fastcall virtual TKinveyFilesService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyFilesAPI*>(AProvider) { }
	/* TKinveyBackendService.Destroy */ inline __fastcall virtual ~TKinveyFilesService() { }
	
private:
	void *__IBackendFilesService;	// Rest::Backend::Servicetypes::IBackendFilesService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A925E828-73A5-41C0-93A4-4E12BC7949FB}
	operator Rest::Backend::Servicetypes::_di_IBackendFilesService()
	{
		Rest::Backend::Servicetypes::_di_IBackendFilesService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Servicetypes::IBackendFilesService*(void) { return (Rest::Backend::Servicetypes::IBackendFilesService*)&__IBackendFilesService; }
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
	operator Rest::Backend::Providers::IBackendService*(void) { return (Rest::Backend::Providers::IBackendService*)&__IBackendFilesService; }
	#endif
	
};


class PASCALIMPLEMENTATION TKinveyPushAPI : public Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth
{
	typedef Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth inherited;
	
private:
	System::UnicodeString FPushEndpoint;
	
protected:
	void __fastcall PushBroadcast(Rest::Backend::Pushtypes::TPushData* const AData);
public:
	/* TKinveyServiceAPI.Create */ inline __fastcall TKinveyPushAPI() : Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth() { }
	/* TKinveyServiceAPI.Destroy */ inline __fastcall virtual ~TKinveyPushAPI() { }
	
private:
	void *__IBackendPushApi;	// Rest::Backend::Pushtypes::IBackendPushApi 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F7FAC938-CE46-42A9-B4D2-8620365A64B0}
	operator Rest::Backend::Pushtypes::_di_IBackendPushApi()
	{
		Rest::Backend::Pushtypes::_di_IBackendPushApi intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Pushtypes::IBackendPushApi*(void) { return (Rest::Backend::Pushtypes::IBackendPushApi*)&__IBackendPushApi; }
	#endif
	
};


class PASCALIMPLEMENTATION TKinveyPushService : public Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyPushAPI*>
{
	typedef Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyPushAPI*> inherited;
	
private:
	System::UnicodeString FPushEndpoint;
	
protected:
	virtual TKinveyPushAPI* __fastcall CreateBackendApi();
	Rest::Backend::Pushtypes::_di_IBackendPushApi __fastcall CreatePushApi();
	Rest::Backend::Pushtypes::_di_IBackendPushApi __fastcall GetPushApi();
	
public:
	__fastcall virtual TKinveyPushService(const Rest::Backend::Providers::_di_IBackendProvider AProvider);
public:
	/* TKinveyBackendService.Destroy */ inline __fastcall virtual ~TKinveyPushService() { }
	
private:
	void *__IBackendPushService;	// Rest::Backend::Pushtypes::IBackendPushService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {34547227-6E40-40F7-A59D-4961FDBD499B}
	operator Rest::Backend::Pushtypes::_di_IBackendPushService()
	{
		Rest::Backend::Pushtypes::_di_IBackendPushService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Pushtypes::IBackendPushService*(void) { return (Rest::Backend::Pushtypes::IBackendPushService*)&__IBackendPushService; }
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
	operator Rest::Backend::Providers::IBackendService*(void) { return (Rest::Backend::Providers::IBackendService*)&__IBackendPushService; }
	#endif
	
};


class PASCALIMPLEMENTATION TKinveyQueryAPI : public Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth
{
	typedef Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth inherited;
	
protected:
	Rest::Backend::Metatypes::_di_IBackendMetaFactory __fastcall GetMetaFactory();
	void __fastcall GetServiceNames(/* out */ System::TArray__1<System::UnicodeString> &ANames);
	void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AObjects)/* overload */;
public:
	/* TKinveyServiceAPI.Create */ inline __fastcall TKinveyQueryAPI() : Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth() { }
	/* TKinveyServiceAPI.Destroy */ inline __fastcall virtual ~TKinveyQueryAPI() { }
	
private:
	void *__IBackendQueryApi;	// Rest::Backend::Servicetypes::IBackendQueryApi 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1F54E3F6-693D-4A25-AC00-7CFFC99D6632}
	operator Rest::Backend::Servicetypes::_di_IBackendQueryApi()
	{
		Rest::Backend::Servicetypes::_di_IBackendQueryApi intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Servicetypes::IBackendQueryApi*(void) { return (Rest::Backend::Servicetypes::IBackendQueryApi*)&__IBackendQueryApi; }
	#endif
	
};


class PASCALIMPLEMENTATION TKinveyQueryService : public Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyQueryAPI*>
{
	typedef Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyQueryAPI*> inherited;
	
protected:
	Rest::Backend::Servicetypes::_di_IBackendQueryApi __fastcall CreateQueryApi();
	Rest::Backend::Servicetypes::_di_IBackendQueryApi __fastcall GetQueryApi();
public:
	/* TKinveyBackendService.Create */ inline __fastcall virtual TKinveyQueryService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyQueryAPI*>(AProvider) { }
	/* TKinveyBackendService.Destroy */ inline __fastcall virtual ~TKinveyQueryService() { }
	
private:
	void *__IBackendQueryService;	// Rest::Backend::Servicetypes::IBackendQueryService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3A22E6DA-7139-4163-B981-DEED365D92B3}
	operator Rest::Backend::Servicetypes::_di_IBackendQueryService()
	{
		Rest::Backend::Servicetypes::_di_IBackendQueryService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Servicetypes::IBackendQueryService*(void) { return (Rest::Backend::Servicetypes::IBackendQueryService*)&__IBackendQueryService; }
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
	operator Rest::Backend::Providers::IBackendService*(void) { return (Rest::Backend::Providers::IBackendService*)&__IBackendQueryService; }
	#endif
	
};


class PASCALIMPLEMENTATION TKinveyLoginAPI : public Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth
{
	typedef Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth inherited;
	
protected:
	Rest::Backend::Metatypes::_di_IBackendMetaFactory __fastcall GetMetaFactory();
	void __fastcall SignupUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, System::Json::TJSONObject* const AUserData, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject);
	void __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, Rest::Backend::Servicetypes::_di_TFindObjectProc AProc)/* overload */;
	void __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUser, System::Json::TJSONArray* const AJSON)/* overload */;
	void __fastcall LogoutUser();
	bool __fastcall FindCurrentUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, Rest::Backend::Servicetypes::_di_TFindObjectProc AProc)/* overload */;
	bool __fastcall FindCurrentUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUser, System::Json::TJSONArray* const AJSON)/* overload */;
	void __fastcall UpdateUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, System::Json::TJSONObject* const AUserData, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject);
public:
	/* TKinveyServiceAPI.Create */ inline __fastcall TKinveyLoginAPI() : Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth() { }
	/* TKinveyServiceAPI.Destroy */ inline __fastcall virtual ~TKinveyLoginAPI() { }
	
private:
	void *__IBackendAuthApi;	// Rest::Backend::Servicetypes::IBackendAuthApi 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {568A911A-B61B-45AA-8BD4-CFCAC0598CF6}
	operator Rest::Backend::Servicetypes::_di_IBackendAuthApi()
	{
		Rest::Backend::Servicetypes::_di_IBackendAuthApi intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Servicetypes::IBackendAuthApi*(void) { return (Rest::Backend::Servicetypes::IBackendAuthApi*)&__IBackendAuthApi; }
	#endif
	
};


class PASCALIMPLEMENTATION TKinveyLoginService : public Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyLoginAPI*>
{
	typedef Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyLoginAPI*> inherited;
	
protected:
	Rest::Backend::Servicetypes::_di_IBackendAuthApi __fastcall CreateAuthApi();
	Rest::Backend::Servicetypes::_di_IBackendAuthApi __fastcall GetAuthApi();
public:
	/* TKinveyBackendService.Create */ inline __fastcall virtual TKinveyLoginService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyLoginAPI*>(AProvider) { }
	/* TKinveyBackendService.Destroy */ inline __fastcall virtual ~TKinveyLoginService() { }
	
private:
	void *__IBackendAuthService;	// Rest::Backend::Servicetypes::IBackendAuthService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DB06E5A1-7261-44A3-9C3E-9805744D53C9}
	operator Rest::Backend::Servicetypes::_di_IBackendAuthService()
	{
		Rest::Backend::Servicetypes::_di_IBackendAuthService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Servicetypes::IBackendAuthService*(void) { return (Rest::Backend::Servicetypes::IBackendAuthService*)&__IBackendAuthService; }
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
	operator Rest::Backend::Providers::IBackendService*(void) { return (Rest::Backend::Providers::IBackendService*)&__IBackendAuthService; }
	#endif
	
};


class PASCALIMPLEMENTATION TKinveyUsersAPI : public TKinveyLoginAPI
{
	typedef TKinveyLoginAPI inherited;
	
protected:
	bool __fastcall DeleteUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject)/* overload */;
	bool __fastcall FindUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, Rest::Backend::Servicetypes::_di_TFindObjectProc AProc)/* overload */;
	bool __fastcall FindUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUser, System::Json::TJSONArray* const AJSON)/* overload */;
	bool __fastcall QueryUserName(const System::UnicodeString AUserName, Rest::Backend::Servicetypes::_di_TFindObjectProc AProc)/* overload */;
	bool __fastcall QueryUserName(const System::UnicodeString AUserName, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUser, System::Json::TJSONArray* const AJSON)/* overload */;
	void __fastcall QueryUsers(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall QueryUsers(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AMetaArray)/* overload */;
public:
	/* TKinveyServiceAPI.Create */ inline __fastcall TKinveyUsersAPI() : TKinveyLoginAPI() { }
	/* TKinveyServiceAPI.Destroy */ inline __fastcall virtual ~TKinveyUsersAPI() { }
	
private:
	void *__IBackendUsersApi;	// Rest::Backend::Servicetypes::IBackendUsersApi 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FD6D169C-07E8-4738-9B9A-BB50E5D423FC}
	operator Rest::Backend::Servicetypes::_di_IBackendUsersApi()
	{
		Rest::Backend::Servicetypes::_di_IBackendUsersApi intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Servicetypes::IBackendUsersApi*(void) { return (Rest::Backend::Servicetypes::IBackendUsersApi*)&__IBackendUsersApi; }
	#endif
	
};


class PASCALIMPLEMENTATION TKinveyUsersService : public Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyUsersAPI*>
{
	typedef Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyUsersAPI*> inherited;
	
protected:
	Rest::Backend::Servicetypes::_di_IBackendUsersApi __fastcall CreateUsersApi();
	Rest::Backend::Servicetypes::_di_IBackendUsersApi __fastcall GetUsersApi();
public:
	/* TKinveyBackendService.Create */ inline __fastcall virtual TKinveyUsersService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyUsersAPI*>(AProvider) { }
	/* TKinveyBackendService.Destroy */ inline __fastcall virtual ~TKinveyUsersService() { }
	
private:
	void *__IBackendUsersService;	// Rest::Backend::Servicetypes::IBackendUsersService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B6A9B066-E6C0-4A01-B70B-5A5A19C816AF}
	operator Rest::Backend::Servicetypes::_di_IBackendUsersService()
	{
		Rest::Backend::Servicetypes::_di_IBackendUsersService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Servicetypes::IBackendUsersService*(void) { return (Rest::Backend::Servicetypes::IBackendUsersService*)&__IBackendUsersService; }
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
	operator Rest::Backend::Providers::IBackendService*(void) { return (Rest::Backend::Providers::IBackendService*)&__IBackendUsersService; }
	#endif
	
};


class PASCALIMPLEMENTATION TKinveyStorageAPI : public Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth
{
	typedef Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth inherited;
	
protected:
	Rest::Backend::Metatypes::_di_IBackendMetaFactory __fastcall GetMetaFactory();
	void __fastcall CreateObject(const Rest::Backend::Metatypes::TBackendClassValue &AClass, System::Json::TJSONObject* const AACL, System::Json::TJSONObject* const AJSON, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject);
	bool __fastcall DeleteObject(const Rest::Backend::Metatypes::TBackendEntityValue &AObject);
	bool __fastcall FindObject(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, Rest::Backend::Servicetypes::_di_TFindObjectProc AProc);
	void __fastcall UpdateObject(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, System::Json::TJSONObject* const AJSONObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject);
	void __fastcall QueryObjects(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall QueryObjects(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AObjects)/* overload */;
public:
	/* TKinveyServiceAPI.Create */ inline __fastcall TKinveyStorageAPI() : Rest::Backend::Kinveyprovider::TKinveyServiceAPIAuth() { }
	/* TKinveyServiceAPI.Destroy */ inline __fastcall virtual ~TKinveyStorageAPI() { }
	
private:
	void *__IBackendStorageApi;	// Rest::Backend::Servicetypes::IBackendStorageApi 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F4CBE0D9-5AAD-49EE-9D2E-3178E5DF2425}
	operator Rest::Backend::Servicetypes::_di_IBackendStorageApi()
	{
		Rest::Backend::Servicetypes::_di_IBackendStorageApi intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Servicetypes::IBackendStorageApi*(void) { return (Rest::Backend::Servicetypes::IBackendStorageApi*)&__IBackendStorageApi; }
	#endif
	
};


class PASCALIMPLEMENTATION TKinveyStorageService : public Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyStorageAPI*>
{
	typedef Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyStorageAPI*> inherited;
	
protected:
	Rest::Backend::Servicetypes::_di_IBackendStorageApi __fastcall CreateStorageApi();
	Rest::Backend::Servicetypes::_di_IBackendStorageApi __fastcall GetStorageApi();
public:
	/* TKinveyBackendService.Create */ inline __fastcall virtual TKinveyStorageService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Kinveyprovider::TKinveyBackendService__1<TKinveyStorageAPI*>(AProvider) { }
	/* TKinveyBackendService.Destroy */ inline __fastcall virtual ~TKinveyStorageService() { }
	
private:
	void *__IBackendStorageService;	// Rest::Backend::Servicetypes::IBackendStorageService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0B60B443-8D7F-4984-8DEA-B7057AD9ED7F}
	operator Rest::Backend::Servicetypes::_di_IBackendStorageService()
	{
		Rest::Backend::Servicetypes::_di_IBackendStorageService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Servicetypes::IBackendStorageService*(void) { return (Rest::Backend::Servicetypes::IBackendStorageService*)&__IBackendStorageService; }
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
	operator Rest::Backend::Providers::IBackendService*(void) { return (Rest::Backend::Providers::IBackendService*)&__IBackendStorageService; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Kinveyservices */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_KINVEYSERVICES)
using namespace Rest::Backend::Kinveyservices;
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
#endif	// Rest_Backend_KinveyservicesHPP
