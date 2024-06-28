// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.ParseServices.pas' rev: 34.00 (iOS)

#ifndef Rest_Backend_ParseservicesHPP
#define Rest_Backend_ParseservicesHPP

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
#include <REST.Json.Types.hpp>
#include <REST.Backend.Providers.hpp>
#include <REST.Backend.PushTypes.hpp>
#include <REST.Backend.ServiceTypes.hpp>
#include <REST.Backend.MetaTypes.hpp>
#include <REST.Backend.ParseProvider.hpp>
#include <REST.Backend.ParseApi.hpp>

//-- user supplied -----------------------------------------------------------
namespace Rest
{
namespace Backend
{
namespace Parseservices
{
  _INIT_UNIT(Rest_Backend_Parseservices);
}	/* namespace Parseservices */
}	/* namespace Backend */
}	/* namespace Rest */

namespace Rest
{
namespace Backend
{
namespace Parseservices
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TParseFilesAPI;
class DELPHICLASS TParseFilesService;
class DELPHICLASS TParsePushAPI;
class DELPHICLASS TParsePushService;
class DELPHICLASS TParseQueryAPI;
class DELPHICLASS TParseQueryService;
class DELPHICLASS TParseLoginAPI;
class DELPHICLASS TParseLoginService;
class DELPHICLASS TParseUsersAPI;
class DELPHICLASS TParseUsersService;
class DELPHICLASS TParseStorageAPI;
class DELPHICLASS TParseStorageService;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TParseFilesAPI : public Rest::Backend::Parseprovider::TParseServiceAPIAuth
{
	typedef Rest::Backend::Parseprovider::TParseServiceAPIAuth inherited;
	
protected:
	Rest::Backend::Metatypes::_di_IBackendMetaFactory __fastcall GetMetaFactory();
	void __fastcall UploadFile(const System::UnicodeString AFileName, const System::UnicodeString AContentType, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AFile)/* overload */;
	void __fastcall UploadFile(const System::UnicodeString AFileName, System::Classes::TStream* const AStream, const System::UnicodeString AContentType, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AFile)/* overload */;
	bool __fastcall DeleteFile(const Rest::Backend::Metatypes::TBackendEntityValue &AFile);
public:
	/* TParseServiceAPI.Create */ inline __fastcall TParseFilesAPI() : Rest::Backend::Parseprovider::TParseServiceAPIAuth() { }
	/* TParseServiceAPI.Destroy */ inline __fastcall virtual ~TParseFilesAPI() { }
	
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


class PASCALIMPLEMENTATION TParseFilesService : public Rest::Backend::Parseprovider::TParseBackendService__1<TParseFilesAPI*>
{
	typedef Rest::Backend::Parseprovider::TParseBackendService__1<TParseFilesAPI*> inherited;
	
protected:
	Rest::Backend::Servicetypes::_di_IBackendFilesApi __fastcall CreateFilesApi();
	Rest::Backend::Servicetypes::_di_IBackendFilesApi __fastcall GetFilesApi();
public:
	/* TParseBackendService.Create */ inline __fastcall virtual TParseFilesService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Parseprovider::TParseBackendService__1<TParseFilesAPI*>(AProvider) { }
	/* TParseBackendService.Destroy */ inline __fastcall virtual ~TParseFilesService() { }
	
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


class PASCALIMPLEMENTATION TParsePushAPI : public Rest::Backend::Parseprovider::TParseServiceAPIAuth
{
	typedef Rest::Backend::Parseprovider::TParseServiceAPIAuth inherited;
	
protected:
	void __fastcall PushBroadcast(Rest::Backend::Pushtypes::TPushData* const AData)/* overload */;
	void __fastcall PushBroadcast(System::Json::TJSONObject* const AData)/* overload */;
	System::Json::TJSONObject* __fastcall PushDataAsJSON(Rest::Backend::Pushtypes::TPushData* const AData);
	void __fastcall PushToTarget(Rest::Backend::Pushtypes::TPushData* const AData, System::Json::TJSONObject* const ATarget)/* overload */;
	void __fastcall PushToTarget(System::Json::TJSONObject* const AData, System::Json::TJSONObject* const ATarget)/* overload */;
public:
	/* TParseServiceAPI.Create */ inline __fastcall TParsePushAPI() : Rest::Backend::Parseprovider::TParseServiceAPIAuth() { }
	/* TParseServiceAPI.Destroy */ inline __fastcall virtual ~TParsePushAPI() { }
	
private:
	void *__IBackendPushApi3;	// Rest::Backend::Pushtypes::IBackendPushApi3 
	void *__IBackendPushApi2;	// Rest::Backend::Pushtypes::IBackendPushApi2 
	void *__IBackendPushApi;	// Rest::Backend::Pushtypes::IBackendPushApi 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E0B215B3-8709-4D80-A2DE-8847A69D1773}
	operator Rest::Backend::Pushtypes::_di_IBackendPushApi3()
	{
		Rest::Backend::Pushtypes::_di_IBackendPushApi3 intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Pushtypes::IBackendPushApi3*(void) { return (Rest::Backend::Pushtypes::IBackendPushApi3*)&__IBackendPushApi3; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E9E1859D-1C35-4266-A335-490508A2C6EE}
	operator Rest::Backend::Pushtypes::_di_IBackendPushApi2()
	{
		Rest::Backend::Pushtypes::_di_IBackendPushApi2 intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Pushtypes::IBackendPushApi2*(void) { return (Rest::Backend::Pushtypes::IBackendPushApi2*)&__IBackendPushApi2; }
	#endif
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


class PASCALIMPLEMENTATION TParsePushService : public Rest::Backend::Parseprovider::TParseBackendService__1<TParsePushAPI*>
{
	typedef Rest::Backend::Parseprovider::TParseBackendService__1<TParsePushAPI*> inherited;
	
protected:
	Rest::Backend::Pushtypes::_di_IBackendPushApi __fastcall CreatePushApi();
	Rest::Backend::Pushtypes::_di_IBackendPushApi __fastcall GetPushApi();
public:
	/* TParseBackendService.Create */ inline __fastcall virtual TParsePushService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Parseprovider::TParseBackendService__1<TParsePushAPI*>(AProvider) { }
	/* TParseBackendService.Destroy */ inline __fastcall virtual ~TParsePushService() { }
	
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


class PASCALIMPLEMENTATION TParseQueryAPI : public Rest::Backend::Parseprovider::TParseServiceAPIAuth
{
	typedef Rest::Backend::Parseprovider::TParseServiceAPIAuth inherited;
	
protected:
	void __fastcall GetServiceNames(/* out */ System::TArray__1<System::UnicodeString> &ANames);
	Rest::Backend::Metatypes::_di_IBackendMetaFactory __fastcall GetMetaFactory();
	void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AObjects)/* overload */;
public:
	/* TParseServiceAPI.Create */ inline __fastcall TParseQueryAPI() : Rest::Backend::Parseprovider::TParseServiceAPIAuth() { }
	/* TParseServiceAPI.Destroy */ inline __fastcall virtual ~TParseQueryAPI() { }
	
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


class PASCALIMPLEMENTATION TParseQueryService : public Rest::Backend::Parseprovider::TParseBackendService__1<TParseQueryAPI*>
{
	typedef Rest::Backend::Parseprovider::TParseBackendService__1<TParseQueryAPI*> inherited;
	
protected:
	Rest::Backend::Servicetypes::_di_IBackendQueryApi __fastcall CreateQueryApi();
	Rest::Backend::Servicetypes::_di_IBackendQueryApi __fastcall GetQueryApi();
public:
	/* TParseBackendService.Create */ inline __fastcall virtual TParseQueryService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Parseprovider::TParseBackendService__1<TParseQueryAPI*>(AProvider) { }
	/* TParseBackendService.Destroy */ inline __fastcall virtual ~TParseQueryService() { }
	
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


class PASCALIMPLEMENTATION TParseLoginAPI : public Rest::Backend::Parseprovider::TParseServiceAPIAuth
{
	typedef Rest::Backend::Parseprovider::TParseServiceAPIAuth inherited;
	
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
	/* TParseServiceAPI.Create */ inline __fastcall TParseLoginAPI() : Rest::Backend::Parseprovider::TParseServiceAPIAuth() { }
	/* TParseServiceAPI.Destroy */ inline __fastcall virtual ~TParseLoginAPI() { }
	
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


class PASCALIMPLEMENTATION TParseLoginService : public Rest::Backend::Parseprovider::TParseBackendService__1<TParseLoginAPI*>
{
	typedef Rest::Backend::Parseprovider::TParseBackendService__1<TParseLoginAPI*> inherited;
	
protected:
	Rest::Backend::Servicetypes::_di_IBackendAuthApi __fastcall CreateAuthApi();
	Rest::Backend::Servicetypes::_di_IBackendAuthApi __fastcall GetAuthApi();
public:
	/* TParseBackendService.Create */ inline __fastcall virtual TParseLoginService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Parseprovider::TParseBackendService__1<TParseLoginAPI*>(AProvider) { }
	/* TParseBackendService.Destroy */ inline __fastcall virtual ~TParseLoginService() { }
	
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


class PASCALIMPLEMENTATION TParseUsersAPI : public TParseLoginAPI
{
	typedef TParseLoginAPI inherited;
	
protected:
	bool __fastcall DeleteUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject)/* overload */;
	bool __fastcall FindUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, Rest::Backend::Servicetypes::_di_TFindObjectProc AProc)/* overload */;
	bool __fastcall FindUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUser, System::Json::TJSONArray* const AJSON)/* overload */;
	HIDESBASE void __fastcall UpdateUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, System::Json::TJSONObject* const AUserData, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject);
	bool __fastcall QueryUserName(const System::UnicodeString AUserName, Rest::Backend::Servicetypes::_di_TFindObjectProc AProc)/* overload */;
	bool __fastcall QueryUserName(const System::UnicodeString AUserName, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUser, System::Json::TJSONArray* const AJSON)/* overload */;
	void __fastcall QueryUsers(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall QueryUsers(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AMetaArray)/* overload */;
public:
	/* TParseServiceAPI.Create */ inline __fastcall TParseUsersAPI() : TParseLoginAPI() { }
	/* TParseServiceAPI.Destroy */ inline __fastcall virtual ~TParseUsersAPI() { }
	
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


class PASCALIMPLEMENTATION TParseUsersService : public Rest::Backend::Parseprovider::TParseBackendService__1<TParseUsersAPI*>
{
	typedef Rest::Backend::Parseprovider::TParseBackendService__1<TParseUsersAPI*> inherited;
	
protected:
	Rest::Backend::Servicetypes::_di_IBackendUsersApi __fastcall CreateUsersApi();
	Rest::Backend::Servicetypes::_di_IBackendUsersApi __fastcall GetUsersApi();
public:
	/* TParseBackendService.Create */ inline __fastcall virtual TParseUsersService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Parseprovider::TParseBackendService__1<TParseUsersAPI*>(AProvider) { }
	/* TParseBackendService.Destroy */ inline __fastcall virtual ~TParseUsersService() { }
	
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


class PASCALIMPLEMENTATION TParseStorageAPI : public Rest::Backend::Parseprovider::TParseServiceAPIAuth
{
	typedef Rest::Backend::Parseprovider::TParseServiceAPIAuth inherited;
	
protected:
	Rest::Backend::Metatypes::_di_IBackendMetaFactory __fastcall GetMetaFactory();
	void __fastcall CreateObject(const Rest::Backend::Metatypes::TBackendClassValue &AClass, System::Json::TJSONObject* const AACL, System::Json::TJSONObject* const AJSON, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject)/* overload */;
	bool __fastcall DeleteObject(const Rest::Backend::Metatypes::TBackendEntityValue &AObject);
	bool __fastcall FindObject(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, Rest::Backend::Servicetypes::_di_TFindObjectProc AProc);
	void __fastcall UpdateObject(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, System::Json::TJSONObject* const AJSONObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject);
	void __fastcall QueryObjects(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall QueryObjects(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AObjects)/* overload */;
	Rest::Json::Types::TJsonDateFormat __fastcall GetJsonDateFormat();
public:
	/* TParseServiceAPI.Create */ inline __fastcall TParseStorageAPI() : Rest::Backend::Parseprovider::TParseServiceAPIAuth() { }
	/* TParseServiceAPI.Destroy */ inline __fastcall virtual ~TParseStorageAPI() { }
	
private:
	void *__IBackendStorageApi2;	// Rest::Backend::Servicetypes::IBackendStorageApi2 
	void *__IBackendStorageApi;	// Rest::Backend::Servicetypes::IBackendStorageApi 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {912DE1A0-75D5-4F79-852C-160976C6A765}
	operator Rest::Backend::Servicetypes::_di_IBackendStorageApi2()
	{
		Rest::Backend::Servicetypes::_di_IBackendStorageApi2 intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Servicetypes::IBackendStorageApi2*(void) { return (Rest::Backend::Servicetypes::IBackendStorageApi2*)&__IBackendStorageApi2; }
	#endif
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


class PASCALIMPLEMENTATION TParseStorageService : public Rest::Backend::Parseprovider::TParseBackendService__1<TParseStorageAPI*>
{
	typedef Rest::Backend::Parseprovider::TParseBackendService__1<TParseStorageAPI*> inherited;
	
protected:
	Rest::Backend::Servicetypes::_di_IBackendStorageApi __fastcall CreateStorageApi();
	Rest::Backend::Servicetypes::_di_IBackendStorageApi __fastcall GetStorageApi();
public:
	/* TParseBackendService.Create */ inline __fastcall virtual TParseStorageService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Parseprovider::TParseBackendService__1<TParseStorageAPI*>(AProvider) { }
	/* TParseBackendService.Destroy */ inline __fastcall virtual ~TParseStorageService() { }
	
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
}	/* namespace Parseservices */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_PARSESERVICES)
using namespace Rest::Backend::Parseservices;
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
#endif	// Rest_Backend_ParseservicesHPP
