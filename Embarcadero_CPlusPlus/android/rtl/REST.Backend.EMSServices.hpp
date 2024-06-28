// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.EMSServices.pas' rev: 34.00 (Android)

#ifndef Rest_Backend_EmsservicesHPP
#define Rest_Backend_EmsservicesHPP

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
#include <REST.Client.hpp>
#include <REST.Backend.Providers.hpp>
#include <REST.Backend.PushTypes.hpp>
#include <REST.Backend.ServiceTypes.hpp>
#include <REST.Backend.MetaTypes.hpp>
#include <REST.Backend.EMSApi.hpp>
#include <REST.Backend.EMSProvider.hpp>
#include <REST.Backend.ServiceFactory.hpp>

//-- user supplied -----------------------------------------------------------
namespace Rest
{
namespace Backend
{
namespace Emsservices
{
  _INIT_UNIT(Rest_Backend_Emsservices);
}	/* namespace Emsservices */
}	/* namespace Backend */
}	/* namespace Rest */

namespace Rest
{
namespace Backend
{
namespace Emsservices
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEMSPushAPI;
class DELPHICLASS TEMSPushService;
class DELPHICLASS TEMSQueryAPI;
class DELPHICLASS TEMSQueryService;
class DELPHICLASS TEMSLoginAPI;
class DELPHICLASS TEMSLoginService;
class DELPHICLASS TEMSUsersAPI;
class DELPHICLASS TEMSUsersService;
class DELPHICLASS TEMSGroupsAPI;
class DELPHICLASS TEMSGroupsService;
class DELPHICLASS TEMSCustomEndpointAPI;
class DELPHICLASS TEMSCustomEndpointService;
template<typename T> class DELPHICLASS TEMSProviderServiceFactory__1;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSPushAPI : public Rest::Backend::Emsprovider::TEMSServiceAPIAuth
{
	typedef Rest::Backend::Emsprovider::TEMSServiceAPIAuth inherited;
	
protected:
	void __fastcall PushBroadcast(Rest::Backend::Pushtypes::TPushData* const AData)/* overload */;
	void __fastcall PushBroadcast(System::Json::TJSONObject* const AData)/* overload */;
	System::Json::TJSONObject* __fastcall PushDataAsJSON(Rest::Backend::Pushtypes::TPushData* const AData);
	void __fastcall PushToTarget(Rest::Backend::Pushtypes::TPushData* const AData, System::Json::TJSONObject* const ATarget)/* overload */;
	void __fastcall PushToTarget(System::Json::TJSONObject* const AData, System::Json::TJSONObject* const ATarget)/* overload */;
public:
	/* TEMSServiceAPI.Create */ inline __fastcall TEMSPushAPI() : Rest::Backend::Emsprovider::TEMSServiceAPIAuth() { }
	/* TEMSServiceAPI.Destroy */ inline __fastcall virtual ~TEMSPushAPI() { }
	
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSPushService : public Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSPushAPI*>
{
	typedef Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSPushAPI*> inherited;
	
protected:
	Rest::Backend::Pushtypes::_di_IBackendPushApi __fastcall CreatePushApi();
	Rest::Backend::Pushtypes::_di_IBackendPushApi __fastcall GetPushApi();
public:
	/* TEMSBackendService.Create */ inline __fastcall virtual TEMSPushService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSPushAPI*>(AProvider) { }
	/* TEMSBackendService.Destroy */ inline __fastcall virtual ~TEMSPushService() { }
	
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSQueryAPI : public Rest::Backend::Emsprovider::TEMSServiceAPIAuth
{
	typedef Rest::Backend::Emsprovider::TEMSServiceAPIAuth inherited;
	
protected:
	Rest::Backend::Metatypes::_di_IBackendMetaFactory __fastcall GetMetaFactory();
	void __fastcall GetServiceNames(/* out */ System::TArray__1<System::UnicodeString> &ANames);
#ifndef __aarch64__
	void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AObjects)/* overload */;
#else /* __aarch64__ */
	void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AObjects)/* overload */;
#endif /* __aarch64__ */
public:
	/* TEMSServiceAPI.Create */ inline __fastcall TEMSQueryAPI() : Rest::Backend::Emsprovider::TEMSServiceAPIAuth() { }
	/* TEMSServiceAPI.Destroy */ inline __fastcall virtual ~TEMSQueryAPI() { }
	
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSQueryService : public Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSQueryAPI*>
{
	typedef Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSQueryAPI*> inherited;
	
protected:
	Rest::Backend::Servicetypes::_di_IBackendQueryApi __fastcall CreateQueryApi();
	Rest::Backend::Servicetypes::_di_IBackendQueryApi __fastcall GetQueryApi();
public:
	/* TEMSBackendService.Create */ inline __fastcall virtual TEMSQueryService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSQueryAPI*>(AProvider) { }
	/* TEMSBackendService.Destroy */ inline __fastcall virtual ~TEMSQueryService() { }
	
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSLoginAPI : public Rest::Backend::Emsprovider::TEMSServiceAPIAuth
{
	typedef Rest::Backend::Emsprovider::TEMSServiceAPIAuth inherited;
	
protected:
	Rest::Backend::Metatypes::_di_IBackendMetaFactory __fastcall GetMetaFactory();
	void __fastcall SignupUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, System::Json::TJSONObject* const AUserData, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject);
	void __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, Rest::Backend::Servicetypes::_di_TFindObjectProc AProc)/* overload */;
	void __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUser, System::Json::TJSONArray* const AJSON)/* overload */;
	bool __fastcall FindCurrentUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, Rest::Backend::Servicetypes::_di_TFindObjectProc AProc)/* overload */;
	bool __fastcall FindCurrentUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUser, System::Json::TJSONArray* const AJSON)/* overload */;
	void __fastcall UpdateUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, System::Json::TJSONObject* const AUserData, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject);
	void __fastcall LogoutUser();
public:
	/* TEMSServiceAPI.Create */ inline __fastcall TEMSLoginAPI() : Rest::Backend::Emsprovider::TEMSServiceAPIAuth() { }
	/* TEMSServiceAPI.Destroy */ inline __fastcall virtual ~TEMSLoginAPI() { }
	
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSLoginService : public Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSLoginAPI*>
{
	typedef Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSLoginAPI*> inherited;
	
protected:
	Rest::Backend::Servicetypes::_di_IBackendAuthApi __fastcall CreateAuthApi();
	Rest::Backend::Servicetypes::_di_IBackendAuthApi __fastcall GetAuthApi();
public:
	/* TEMSBackendService.Create */ inline __fastcall virtual TEMSLoginService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSLoginAPI*>(AProvider) { }
	/* TEMSBackendService.Destroy */ inline __fastcall virtual ~TEMSLoginService() { }
	
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSUsersAPI : public TEMSLoginAPI
{
	typedef TEMSLoginAPI inherited;
	
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
	/* TEMSServiceAPI.Create */ inline __fastcall TEMSUsersAPI() : TEMSLoginAPI() { }
	/* TEMSServiceAPI.Destroy */ inline __fastcall virtual ~TEMSUsersAPI() { }
	
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSUsersService : public Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSUsersAPI*>
{
	typedef Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSUsersAPI*> inherited;
	
protected:
	Rest::Backend::Servicetypes::_di_IBackendUsersApi __fastcall CreateUsersApi();
	Rest::Backend::Servicetypes::_di_IBackendUsersApi __fastcall GetUsersApi();
public:
	/* TEMSBackendService.Create */ inline __fastcall virtual TEMSUsersService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSUsersAPI*>(AProvider) { }
	/* TEMSBackendService.Destroy */ inline __fastcall virtual ~TEMSUsersService() { }
	
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSGroupsAPI : public Rest::Backend::Emsprovider::TEMSServiceAPIAuth
{
	typedef Rest::Backend::Emsprovider::TEMSServiceAPIAuth inherited;
	
protected:
	Rest::Backend::Metatypes::_di_IBackendMetaFactory __fastcall GetMetaFactory();
	void __fastcall AddUsers(const System::UnicodeString AGroupName, const System::TArray__1<System::UnicodeString> AUsers, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject);
	bool __fastcall RemoveUsers(const System::UnicodeString AGroupName, const System::TArray__1<System::UnicodeString> AUsers, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject);
	void __fastcall CreateGroup(const System::UnicodeString AGroup, System::Json::TJSONObject* AJSON, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject)/* overload */;
	bool __fastcall DeleteGroup(const Rest::Backend::Metatypes::TBackendEntityValue &AObject)/* overload */;
	bool __fastcall FindGroup(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, Rest::Backend::Servicetypes::_di_TFindObjectProc AProc);
	void __fastcall UpdateGroup(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, System::Json::TJSONObject* const AJSONObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject);
public:
	/* TEMSServiceAPI.Create */ inline __fastcall TEMSGroupsAPI() : Rest::Backend::Emsprovider::TEMSServiceAPIAuth() { }
	/* TEMSServiceAPI.Destroy */ inline __fastcall virtual ~TEMSGroupsAPI() { }
	
private:
	void *__IBackendGroupsApi;	// Rest::Backend::Servicetypes::IBackendGroupsApi 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3FF2A6F6-490E-4896-B482-CD361A8C6705}
	operator Rest::Backend::Servicetypes::_di_IBackendGroupsApi()
	{
		Rest::Backend::Servicetypes::_di_IBackendGroupsApi intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Servicetypes::IBackendGroupsApi*(void) { return (Rest::Backend::Servicetypes::IBackendGroupsApi*)&__IBackendGroupsApi; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSGroupsService : public Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSGroupsAPI*>
{
	typedef Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSGroupsAPI*> inherited;
	
protected:
	Rest::Backend::Servicetypes::_di_IBackendGroupsApi __fastcall CreateGroupsApi();
	Rest::Backend::Servicetypes::_di_IBackendGroupsApi __fastcall GetGroupsApi();
public:
	/* TEMSBackendService.Create */ inline __fastcall virtual TEMSGroupsService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSGroupsAPI*>(AProvider) { }
	/* TEMSBackendService.Destroy */ inline __fastcall virtual ~TEMSGroupsService() { }
	
private:
	void *__IBackendGroupsService;	// Rest::Backend::Servicetypes::IBackendGroupsService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D40C0565-5165-4280-9625-5593FB77FA36}
	operator Rest::Backend::Servicetypes::_di_IBackendGroupsService()
	{
		Rest::Backend::Servicetypes::_di_IBackendGroupsService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Servicetypes::IBackendGroupsService*(void) { return (Rest::Backend::Servicetypes::IBackendGroupsService*)&__IBackendGroupsService; }
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
	operator Rest::Backend::Providers::IBackendService*(void) { return (Rest::Backend::Providers::IBackendService*)&__IBackendGroupsService; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSCustomEndpointAPI : public Rest::Backend::Emsprovider::TEMSServiceAPIAuth
{
	typedef Rest::Backend::Emsprovider::TEMSServiceAPIAuth inherited;
	
protected:
	void __fastcall PrepareClient(Rest::Client::TCustomRESTClient* const AClient);
	void __fastcall PrepareRequest(Rest::Client::TCustomRESTRequest* const ARequest);
	void __fastcall CheckForResponseErrors(Rest::Client::TCustomRESTResponse* const AResponse, int *AValidStatusCodes, const int AValidStatusCodes_High);
public:
	/* TEMSServiceAPI.Create */ inline __fastcall TEMSCustomEndpointAPI() : Rest::Backend::Emsprovider::TEMSServiceAPIAuth() { }
	/* TEMSServiceAPI.Destroy */ inline __fastcall virtual ~TEMSCustomEndpointAPI() { }
	
private:
	void *__IBackendCustomEndpointApi;	// Rest::Backend::Servicetypes::IBackendCustomEndpointApi 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {974BD7BB-C39C-4C75-8056-148026839A38}
	operator Rest::Backend::Servicetypes::_di_IBackendCustomEndpointApi()
	{
		Rest::Backend::Servicetypes::_di_IBackendCustomEndpointApi intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Servicetypes::IBackendCustomEndpointApi*(void) { return (Rest::Backend::Servicetypes::IBackendCustomEndpointApi*)&__IBackendCustomEndpointApi; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEMSCustomEndpointService : public Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSCustomEndpointAPI*>
{
	typedef Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSCustomEndpointAPI*> inherited;
	
protected:
	Rest::Backend::Servicetypes::_di_IBackendCustomEndpointApi __fastcall GetCustomEndpointAPI();
	Rest::Backend::Servicetypes::_di_IBackendCustomEndpointApi __fastcall CreateCustomEndpointApi();
public:
	/* TEMSBackendService.Create */ inline __fastcall virtual TEMSCustomEndpointService(const Rest::Backend::Providers::_di_IBackendProvider AProvider) : Rest::Backend::Emsprovider::TEMSBackendService__1<TEMSCustomEndpointAPI*>(AProvider) { }
	/* TEMSBackendService.Destroy */ inline __fastcall virtual ~TEMSCustomEndpointService() { }
	
private:
	void *__IBackendCustomEndpointService;	// Rest::Backend::Servicetypes::IBackendCustomEndpointService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BF37269F-BBDE-4110-BAFA-A1CC725BC5D0}
	operator Rest::Backend::Servicetypes::_di_IBackendCustomEndpointService()
	{
		Rest::Backend::Servicetypes::_di_IBackendCustomEndpointService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Servicetypes::IBackendCustomEndpointService*(void) { return (Rest::Backend::Servicetypes::IBackendCustomEndpointService*)&__IBackendCustomEndpointService; }
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
	operator Rest::Backend::Providers::IBackendService*(void) { return (Rest::Backend::Providers::IBackendService*)&__IBackendCustomEndpointService; }
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
template<typename T> class PASCALIMPLEMENTATION TEMSProviderServiceFactory__1 : public Rest::Backend::Servicefactory::TProviderServiceFactory__1<T>
{
	typedef Rest::Backend::Servicefactory::TProviderServiceFactory__1<T> inherited;
	
public:
	System::DelphiInterface<System::Sysutils::TFunc__2<Rest::Backend::Providers::_di_IBackendProvider,Rest::Backend::Providers::_di_IBackendService> > FMethod;
	
protected:
	virtual Rest::Backend::Providers::_di_IBackendService __fastcall CreateService(const Rest::Backend::Providers::_di_IBackendProvider AProvider, const GUID &IID);
	
public:
	__fastcall TEMSProviderServiceFactory__1(const System::DelphiInterface<System::Sysutils::TFunc__2<Rest::Backend::Providers::_di_IBackendProvider,Rest::Backend::Providers::_di_IBackendService> > AMethod);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TEMSProviderServiceFactory__1() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Emsservices */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_EMSSERVICES)
using namespace Rest::Backend::Emsservices;
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
#endif	// Rest_Backend_EmsservicesHPP
