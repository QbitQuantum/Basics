// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.ServiceTypes.pas' rev: 34.00 (Android)

#ifndef Rest_Backend_ServicetypesHPP
#define Rest_Backend_ServicetypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Classes.hpp>
#include <System.JSON.hpp>
#include <REST.Backend.Providers.hpp>
#include <REST.Backend.MetaTypes.hpp>
#include <REST.Client.hpp>
#include <REST.Json.hpp>
#include <REST.Json.Types.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------
namespace Rest
{
namespace Backend
{
namespace Servicetypes
{
template<typename T> class DELPHICLASS TBackendObjectList__1;
}	/* namespace Servicetypes */
}	/* namespace Backend */
}	/* namespace Rest */

namespace Rest
{
namespace Backend
{
namespace Servicetypes
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IBackendGetMetaFactory;
typedef System::DelphiInterface<IBackendGetMetaFactory> _di_IBackendGetMetaFactory;
__interface DELPHIINTERFACE IBackendQueryService;
typedef System::DelphiInterface<IBackendQueryService> _di_IBackendQueryService;
struct TBackendQueryServiceNames;
__interface DELPHIINTERFACE IBackendQueryApi;
typedef System::DelphiInterface<IBackendQueryApi> _di_IBackendQueryApi;
class DELPHICLASS TBackendAuthenticationApi;
class DELPHICLASS TBackendQueryApi;
__interface DELPHIINTERFACE IBackendStorageService;
typedef System::DelphiInterface<IBackendStorageService> _di_IBackendStorageService;
__interface DELPHIINTERFACE TFindObjectProc;
typedef System::DelphiInterface<TFindObjectProc> _di_TFindObjectProc;
template<typename T> __interface DELPHIINTERFACE TFindObjectProc__1;
#ifdef __clang__
template<typename T> using _di_TFindObjectProc__1 = System::DelphiInterface<TFindObjectProc__1<T>>;
#endif
__interface DELPHIINTERFACE IBackendStorageApi;
typedef System::DelphiInterface<IBackendStorageApi> _di_IBackendStorageApi;
__interface DELPHIINTERFACE IBackendStorageApi2;
typedef System::DelphiInterface<IBackendStorageApi2> _di_IBackendStorageApi2;
class DELPHICLASS TBackendStorageApi;
__interface DELPHIINTERFACE IBackendAuthenticationApi;
typedef System::DelphiInterface<IBackendAuthenticationApi> _di_IBackendAuthenticationApi;
__interface DELPHIINTERFACE IBackendAuthService;
typedef System::DelphiInterface<IBackendAuthService> _di_IBackendAuthService;
__interface DELPHIINTERFACE IBackendAuthApi;
typedef System::DelphiInterface<IBackendAuthApi> _di_IBackendAuthApi;
class DELPHICLASS TBackendAuthApi;
__interface DELPHIINTERFACE IBackendUsersService;
typedef System::DelphiInterface<IBackendUsersService> _di_IBackendUsersService;
__interface DELPHIINTERFACE IBackendUsersApi;
typedef System::DelphiInterface<IBackendUsersApi> _di_IBackendUsersApi;
class DELPHICLASS TBackendUsersApi;
__interface DELPHIINTERFACE IBackendGroupsService;
typedef System::DelphiInterface<IBackendGroupsService> _di_IBackendGroupsService;
__interface DELPHIINTERFACE IBackendGroupsApi;
typedef System::DelphiInterface<IBackendGroupsApi> _di_IBackendGroupsApi;
class DELPHICLASS TBackendGroupsApi;
__interface DELPHIINTERFACE IBackendFilesService;
typedef System::DelphiInterface<IBackendFilesService> _di_IBackendFilesService;
__interface DELPHIINTERFACE IBackendFilesApi;
typedef System::DelphiInterface<IBackendFilesApi> _di_IBackendFilesApi;
class DELPHICLASS TBackendFilesApi;
template<typename T> class DELPHICLASS TBackendObjectList__1;
__interface DELPHIINTERFACE IBackendCustomEndpointService;
typedef System::DelphiInterface<IBackendCustomEndpointService> _di_IBackendCustomEndpointService;
__interface DELPHIINTERFACE IBackendCustomEndpointApi;
typedef System::DelphiInterface<IBackendCustomEndpointApi> _di_IBackendCustomEndpointApi;
class DELPHICLASS TBackendCustomEndPointApi;
template<typename T> class DELPHICLASS _TBackendStorageApi_FindObject_1__ActRec__1;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{65BB9847-DF2D-4888-8B2F-36EDE51FE20A}") IBackendGetMetaFactory  : public Rest::Backend::Providers::IBackendService 
{
	virtual Rest::Backend::Metatypes::_di_IBackendMetaFactory __fastcall GetMetaFactory() = 0 ;
};

__interface  INTERFACE_UUID("{3A22E6DA-7139-4163-B981-DEED365D92B3}") IBackendQueryService  : public Rest::Backend::Providers::IBackendService 
{
	virtual _di_IBackendQueryApi __fastcall GetQueryAPI() = 0 ;
	virtual _di_IBackendQueryApi __fastcall CreateQueryApi() = 0 ;
	__property _di_IBackendQueryApi QueryAPI = {read=GetQueryAPI};
};

struct DECLSPEC_DRECORD TBackendQueryServiceNames
{
public:
	#define TBackendQueryServiceNames_Storage u"Storage"
	
	#define TBackendQueryServiceNames_Users u"Users"
	
	#define TBackendQueryServiceNames_Installations u"Installations"
	
	#define TBackendQueryServiceNames_Groups u"Groups"
	
	#define TBackendQueryServiceNames_Modules u"Edgemodules"
	
	#define TBackendQueryServiceNames_ModulesResources u"Edgeresources"
	
	#define TBackendQueryServiceNames_Files u"Files"
	
};


__interface  INTERFACE_UUID("{1F54E3F6-693D-4A25-AC00-7CFFC99D6632}") IBackendQueryApi  : public IBackendGetMetaFactory 
{
#ifndef __aarch64__
	virtual void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray) = 0 /* overload */;
	virtual void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AObjects) = 0 /* overload */;
#else /* __aarch64__ */
	virtual void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray) = 0 /* overload */;
	virtual void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AObjects) = 0 /* overload */;
#endif /* __aarch64__ */
	virtual void __fastcall GetServiceNames(/* out */ System::TArray__1<System::UnicodeString> &ANames) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBackendAuthenticationApi : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Rest::Backend::Providers::TBackendAuthentication __fastcall GetAuthentication();
	Rest::Backend::Providers::TBackendDefaultAuthentication __fastcall GetDefaultAuthentication();
	void __fastcall SetAuthentication(const Rest::Backend::Providers::TBackendAuthentication Value);
	void __fastcall SetDefaultAuthentication(const Rest::Backend::Providers::TBackendDefaultAuthentication Value);
	
protected:
	virtual _di_IBackendAuthenticationApi __fastcall GetAuthenticationApi() = 0 ;
	
public:
	void __fastcall Login(const Rest::Backend::Metatypes::TBackendEntityValue &ALogin);
	void __fastcall Logout();
	__property Rest::Backend::Providers::TBackendAuthentication Authentication = {read=GetAuthentication, write=SetAuthentication, nodefault};
	__property Rest::Backend::Providers::TBackendDefaultAuthentication DefaultAuthentication = {read=GetDefaultAuthentication, write=SetDefaultAuthentication, nodefault};
	__property _di_IBackendAuthenticationApi AuthenticationApi = {read=GetAuthenticationApi};
public:
	/* TObject.Create */ inline __fastcall TBackendAuthenticationApi() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBackendAuthenticationApi() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBackendQueryApi : public TBackendAuthenticationApi
{
	typedef TBackendAuthenticationApi inherited;
	
private:
	_di_IBackendQueryApi FServiceApi;
	_di_IBackendQueryService FService;
	_di_IBackendQueryApi __fastcall GetServiceAPI();
	Rest::Backend::Metatypes::TBackendClassValue __fastcall CreateMetaDataType(const System::UnicodeString ADataType, const System::UnicodeString AClassName);
#ifndef __aarch64__
	void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AMetaArray)/* overload */;
	template<typename T> void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue ADataType, const System::UnicodeString *AQuery, const int AQuery_High, TBackendObjectList__1<T>* const AResultList)/* overload */;
#else /* __aarch64__ */
	void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AMetaArray)/* overload */;
	template<typename T> void __fastcall Query(const Rest::Backend::Metatypes::TBackendClassValue &ADataType, const System::UnicodeString *AQuery, const int AQuery_High, TBackendObjectList__1<T>* const AResultList)/* overload */;
#endif /* __aarch64__ */
	
protected:
	virtual _di_IBackendAuthenticationApi __fastcall GetAuthenticationApi();
	
public:
	__fastcall TBackendQueryApi(const _di_IBackendQueryApi AApi)/* overload */;
	__fastcall TBackendQueryApi(const _di_IBackendQueryService AService)/* overload */;
	void __fastcall GetServiceNames(/* out */ System::TArray__1<System::UnicodeString> &ANames);
	void __fastcall Query(const System::UnicodeString ADataType, const System::UnicodeString ABackendClassName, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall Query(const System::UnicodeString ADataType, const System::UnicodeString ABackendClassName, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AMetaArray)/* overload */;
	template<typename T> void __fastcall Query(const System::UnicodeString ADataType, const System::UnicodeString ABackendClassName, const System::UnicodeString *AQuery, const int AQuery_High, TBackendObjectList__1<T>* const AResultList)/* overload */;
	__property _di_IBackendQueryApi ProviderAPI = {read=GetServiceAPI};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBackendQueryApi() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0B60B443-8D7F-4984-8DEA-B7057AD9ED7F}") IBackendStorageService  : public Rest::Backend::Providers::IBackendService 
{
	virtual _di_IBackendStorageApi __fastcall GetStorageApi() = 0 ;
	virtual _di_IBackendStorageApi __fastcall CreateStorageApi() = 0 ;
	__property _di_IBackendStorageApi StorageAPI = {read=GetStorageApi};
};

__interface TFindObjectProc  : public System::IInterface 
{
	virtual void __fastcall Invoke(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, System::Json::TJSONObject* const AJSON) = 0 ;
};

// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> __interface TFindObjectProc__1  : public System::IInterface 
{
	virtual void __fastcall Invoke(const Rest::Backend::Metatypes::TBackendEntityValue &AMetaObject, const T AObject) = 0 ;
};

__interface  INTERFACE_UUID("{F4CBE0D9-5AAD-49EE-9D2E-3178E5DF2425}") IBackendStorageApi  : public IBackendGetMetaFactory 
{
	HIDESBASE virtual Rest::Backend::Metatypes::_di_IBackendMetaFactory __fastcall GetMetaFactory() = 0 ;
#ifndef __aarch64__
	virtual void __fastcall CreateObject(const Rest::Backend::Metatypes::TBackendClassValue AClass, System::Json::TJSONObject* const AACL, System::Json::TJSONObject* const AJSON, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject) = 0 /* overload */;
#else /* __aarch64__ */
	virtual void __fastcall CreateObject(const Rest::Backend::Metatypes::TBackendClassValue &AClass, System::Json::TJSONObject* const AACL, System::Json::TJSONObject* const AJSON, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject) = 0 /* overload */;
#endif /* __aarch64__ */
	virtual bool __fastcall DeleteObject(const Rest::Backend::Metatypes::TBackendEntityValue &AObject) = 0 /* overload */;
	virtual bool __fastcall FindObject(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, _di_TFindObjectProc AProc) = 0 ;
	virtual void __fastcall UpdateObject(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, System::Json::TJSONObject* const AJSONObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject) = 0 ;
#ifndef __aarch64__
	virtual void __fastcall QueryObjects(const Rest::Backend::Metatypes::TBackendClassValue AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray) = 0 /* overload */;
	virtual void __fastcall QueryObjects(const Rest::Backend::Metatypes::TBackendClassValue AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AObjects) = 0 /* overload */;
#else /* __aarch64__ */
	virtual void __fastcall QueryObjects(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray) = 0 /* overload */;
	virtual void __fastcall QueryObjects(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AObjects) = 0 /* overload */;
#endif /* __aarch64__ */
};

__interface  INTERFACE_UUID("{912DE1A0-75D5-4F79-852C-160976C6A765}") IBackendStorageApi2  : public IBackendGetMetaFactory 
{
	virtual Rest::Json::Types::TJsonDateFormat __fastcall GetJsonDateFormat() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBackendStorageApi : public TBackendAuthenticationApi
{
	typedef TBackendAuthenticationApi inherited;
	
private:
	_di_IBackendStorageService FService;
	_di_IBackendStorageApi FServiceApi;
	Rest::Backend::Metatypes::TBackendClassValue __fastcall CreateMetaClass(const System::UnicodeString AClassName);
	Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaClassObject(const System::UnicodeString AClassName, const System::UnicodeString AObjectID);
#ifndef __aarch64__
	void __fastcall CreateObject(const Rest::Backend::Metatypes::TBackendClassValue AClass, System::Json::TJSONObject* const AJSON, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject)/* overload */;
	void __fastcall CreateObject(const Rest::Backend::Metatypes::TBackendClassValue AClass, System::Json::TJSONObject* const AACL, System::Json::TJSONObject* const AJSON, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject)/* overload */;
	template<typename T> void __fastcall CreateObject(const Rest::Backend::Metatypes::TBackendClassValue AClass, const T AObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject)/* overload */;
#else /* __aarch64__ */
	void __fastcall CreateObject(const Rest::Backend::Metatypes::TBackendClassValue &AClass, System::Json::TJSONObject* const AJSON, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject)/* overload */;
	void __fastcall CreateObject(const Rest::Backend::Metatypes::TBackendClassValue &AClass, System::Json::TJSONObject* const AACL, System::Json::TJSONObject* const AJSON, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject)/* overload */;
	template<typename T> void __fastcall CreateObject(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const T AObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject)/* overload */;
#endif /* __aarch64__ */
	_di_IBackendStorageApi __fastcall GetServiceAPI();
#ifndef __aarch64__
	template<typename T> void __fastcall QueryObjects(const Rest::Backend::Metatypes::TBackendClassValue AClass, const System::UnicodeString *AQuery, const int AQuery_High, TBackendObjectList__1<T>* const AResultList)/* overload */;
	void __fastcall QueryObjects(const Rest::Backend::Metatypes::TBackendClassValue AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AMetaArray)/* overload */;
	void __fastcall QueryObjects(const Rest::Backend::Metatypes::TBackendClassValue AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
#else /* __aarch64__ */
	template<typename T> void __fastcall QueryObjects(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, TBackendObjectList__1<T>* const AResultList)/* overload */;
	void __fastcall QueryObjects(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AMetaArray)/* overload */;
	void __fastcall QueryObjects(const Rest::Backend::Metatypes::TBackendClassValue &AClass, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
#endif /* __aarch64__ */
	
protected:
	virtual _di_IBackendAuthenticationApi __fastcall GetAuthenticationApi();
	
public:
	__fastcall TBackendStorageApi(const _di_IBackendStorageApi AApi)/* overload */;
	__fastcall TBackendStorageApi(const _di_IBackendStorageService AService)/* overload */;
	void __fastcall CreateObject(const System::UnicodeString AClassName, System::Json::TJSONObject* const AJSON, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject)/* overload */;
	void __fastcall CreateObject(const System::UnicodeString AClassName, System::Json::TJSONObject* const AACL, System::Json::TJSONObject* const AJSON, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject)/* overload */;
	bool __fastcall DeleteObject(const System::UnicodeString AClassName, const System::UnicodeString AObjectID)/* overload */;
	bool __fastcall DeleteObject(const Rest::Backend::Metatypes::TBackendEntityValue &AObject)/* overload */;
	bool __fastcall FindObject(const Rest::Backend::Metatypes::TBackendEntityValue &AMetaObject, _di_TFindObjectProc AProc)/* overload */;
	bool __fastcall FindObject(const System::UnicodeString AClassName, const System::UnicodeString AObjectID, _di_TFindObjectProc AProc)/* overload */;
	void __fastcall QueryObjects(const System::UnicodeString AClassName, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall QueryObjects(const System::UnicodeString AClassName, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AMetaArray)/* overload */;
	void __fastcall UpdateObject(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, System::Json::TJSONObject* const AJSONObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject)/* overload */;
	void __fastcall UpdateObject(const System::UnicodeString AClassName, const System::UnicodeString AObjectID, System::Json::TJSONObject* const AJSONObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject)/* overload */;
	template<typename T> void __fastcall CreateObject(const System::UnicodeString AClassName, const T AObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject)/* overload */;
	template<typename T> void __fastcall CreateObject(const System::UnicodeString AClassName, const T AObject)/* overload */;
	template<typename T> bool __fastcall FindObject(const Rest::Backend::Metatypes::TBackendEntityValue &AMetaObject, System::DelphiInterface<TFindObjectProc__1<T> > AProc)/* overload */;
	template<typename T> void __fastcall UpdateObject(const Rest::Backend::Metatypes::TBackendEntityValue &AMetaObject, const T AObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject)/* overload */;
	template<typename T> void __fastcall QueryObjects(const System::UnicodeString AClassName, const System::UnicodeString *AQuery, const int AQuery_High, TBackendObjectList__1<T>* const AResultList)/* overload */;
	Rest::Json::TJsonOptions __fastcall AddDateOption(Rest::Json::Types::TJsonDateFormat ADateFormat, Rest::Json::TJsonOptions AOptions);
	__property _di_IBackendStorageApi ProviderAPI = {read=GetServiceAPI};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBackendStorageApi() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4C0D2ADD-B6B7-40ED-B6B5-5DB66B7ECE9D}") IBackendAuthenticationApi  : public System::IInterface 
{
	virtual void __fastcall Login(const Rest::Backend::Metatypes::TBackendEntityValue &ALogin) = 0 ;
	virtual void __fastcall Logout() = 0 ;
	virtual void __fastcall SetDefaultAuthentication(Rest::Backend::Providers::TBackendDefaultAuthentication ADefaultAuthentication) = 0 ;
	virtual Rest::Backend::Providers::TBackendDefaultAuthentication __fastcall GetDefaultAuthentication() = 0 ;
	virtual void __fastcall SetAuthentication(Rest::Backend::Providers::TBackendAuthentication AAuthentication) = 0 ;
	virtual Rest::Backend::Providers::TBackendAuthentication __fastcall GetAuthentication() = 0 ;
	__property Rest::Backend::Providers::TBackendAuthentication Authentication = {read=GetAuthentication, write=SetAuthentication};
	__property Rest::Backend::Providers::TBackendDefaultAuthentication DefaultAuthentication = {read=GetDefaultAuthentication, write=SetDefaultAuthentication};
};

__interface  INTERFACE_UUID("{DB06E5A1-7261-44A3-9C3E-9805744D53C9}") IBackendAuthService  : public Rest::Backend::Providers::IBackendService 
{
	virtual _di_IBackendAuthApi __fastcall GetAuthAPI() = 0 ;
	virtual _di_IBackendAuthApi __fastcall CreateAuthApi() = 0 ;
	__property _di_IBackendAuthApi AuthAPI = {read=GetAuthAPI};
};

__interface  INTERFACE_UUID("{568A911A-B61B-45AA-8BD4-CFCAC0598CF6}") IBackendAuthApi  : public IBackendGetMetaFactory 
{
	virtual void __fastcall SignupUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, System::Json::TJSONObject* const AUserData, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject) = 0 ;
	virtual void __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, _di_TFindObjectProc AProc) = 0 /* overload */;
	virtual void __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUser, System::Json::TJSONArray* const AJSON) = 0 /* overload */;
	virtual void __fastcall LogoutUser() = 0 ;
	virtual bool __fastcall FindCurrentUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, _di_TFindObjectProc AProc) = 0 /* overload */;
	virtual bool __fastcall FindCurrentUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUser, System::Json::TJSONArray* const AJSON) = 0 /* overload */;
	virtual void __fastcall UpdateUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, System::Json::TJSONObject* const AUserData, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBackendAuthApi : public TBackendAuthenticationApi
{
	typedef TBackendAuthenticationApi inherited;
	
private:
	_di_IBackendAuthService FService;
	_di_IBackendAuthApi FServiceApi;
	Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaUserObject(const System::UnicodeString AObjectID);
	_di_IBackendAuthApi __fastcall GetServiceAPI();
	
protected:
	virtual _di_IBackendAuthenticationApi __fastcall GetAuthenticationApi();
	virtual _di_IBackendAuthApi __fastcall GetAuthApi();
	
public:
	__fastcall TBackendAuthApi(const _di_IBackendAuthApi AApi)/* overload */;
	__fastcall TBackendAuthApi(const _di_IBackendAuthService AService)/* overload */;
	void __fastcall SignupUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, System::Json::TJSONObject* const AUserData, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject);
	void __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, _di_TFindObjectProc AProc)/* overload */;
	void __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ALogin, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	void __fastcall LogoutUser();
	bool __fastcall FindCurrentUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, _di_TFindObjectProc AProc);
	void __fastcall UpdateUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, System::Json::TJSONObject* const AUserData, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject)/* overload */;
	__property _di_IBackendAuthApi ProviderAPI = {read=GetServiceAPI};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBackendAuthApi() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B6A9B066-E6C0-4A01-B70B-5A5A19C816AF}") IBackendUsersService  : public Rest::Backend::Providers::IBackendService 
{
	virtual _di_IBackendUsersApi __fastcall GetUsersAPI() = 0 ;
	virtual _di_IBackendUsersApi __fastcall CreateUsersApi() = 0 ;
	__property _di_IBackendUsersApi UsersAPI = {read=GetUsersAPI};
};

__interface  INTERFACE_UUID("{FD6D169C-07E8-4738-9B9A-BB50E5D423FC}") IBackendUsersApi  : public IBackendAuthApi 
{
	virtual bool __fastcall DeleteUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject) = 0 /* overload */;
	virtual bool __fastcall FindUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, _di_TFindObjectProc AProc) = 0 /* overload */;
	virtual bool __fastcall FindUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUser, System::Json::TJSONArray* const AJSON) = 0 /* overload */;
	virtual bool __fastcall QueryUserName(const System::UnicodeString AUserName, _di_TFindObjectProc AProc) = 0 /* overload */;
	virtual bool __fastcall QueryUserName(const System::UnicodeString AUserName, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUser, System::Json::TJSONArray* const AJSON) = 0 /* overload */;
	virtual void __fastcall QueryUsers(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray) = 0 /* overload */;
	virtual void __fastcall QueryUsers(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AMetaArray) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBackendUsersApi : public TBackendAuthApi
{
	typedef TBackendAuthApi inherited;
	
private:
	_di_IBackendUsersService FService;
	_di_IBackendUsersApi FServiceApi;
	HIDESBASE Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaUserObject(const System::UnicodeString AObjectID);
	HIDESBASE _di_IBackendUsersApi __fastcall GetServiceAPI();
	
protected:
	virtual _di_IBackendAuthenticationApi __fastcall GetAuthenticationApi();
	virtual _di_IBackendAuthApi __fastcall GetAuthApi();
	
public:
	__fastcall TBackendUsersApi(const _di_IBackendUsersApi AApi)/* overload */;
	__fastcall TBackendUsersApi(const _di_IBackendUsersService AService)/* overload */;
	bool __fastcall DeleteUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject)/* overload */;
	bool __fastcall DeleteUser(const System::UnicodeString AObjectID)/* overload */;
	bool __fastcall FindUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, _di_TFindObjectProc AProc)/* overload */;
	bool __fastcall FindUser(const System::UnicodeString AObjectID, _di_TFindObjectProc AProc)/* overload */;
	bool __fastcall FindUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUser, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall FindUser(const System::UnicodeString AObjectID, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUser, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	HIDESBASE void __fastcall UpdateUser(const System::UnicodeString AObjectID, System::Json::TJSONObject* const AUserData, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject)/* overload */;
	bool __fastcall QueryUserName(const System::UnicodeString AUserName, _di_TFindObjectProc AProc)/* overload */;
	bool __fastcall QueryUserName(const System::UnicodeString AUserName, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUser, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	void __fastcall QueryUsers(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall QueryUsers(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<Rest::Backend::Metatypes::TBackendEntityValue> &AMetaArray)/* overload */;
	__property _di_IBackendUsersApi ProviderAPI = {read=GetServiceAPI};
public:
	/* TBackendAuthApi.Create */ inline __fastcall TBackendUsersApi(const _di_IBackendAuthApi AApi)/* overload */ : TBackendAuthApi(AApi) { }
	/* TBackendAuthApi.Create */ inline __fastcall TBackendUsersApi(const _di_IBackendAuthService AService)/* overload */ : TBackendAuthApi(AService) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBackendUsersApi() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  UpdateUser(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, System::Json::TJSONObject* const AUserData, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject){ TBackendAuthApi::UpdateUser(AObject, AUserData, AUpdatedObject); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D40C0565-5165-4280-9625-5593FB77FA36}") IBackendGroupsService  : public Rest::Backend::Providers::IBackendService 
{
	virtual _di_IBackendGroupsApi __fastcall GetGroupsAPI() = 0 ;
	virtual _di_IBackendGroupsApi __fastcall CreateGroupsApi() = 0 ;
	__property _di_IBackendGroupsApi GroupsAPI = {read=GetGroupsAPI};
};

__interface  INTERFACE_UUID("{3FF2A6F6-490E-4896-B482-CD361A8C6705}") IBackendGroupsApi  : public IBackendGetMetaFactory 
{
	virtual void __fastcall AddUsers(const System::UnicodeString AGroupName, const System::TArray__1<System::UnicodeString> AUsers, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject) = 0 ;
	virtual bool __fastcall RemoveUsers(const System::UnicodeString AGroupName, const System::TArray__1<System::UnicodeString> AUsers, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject) = 0 ;
	virtual void __fastcall CreateGroup(const System::UnicodeString AGroup, System::Json::TJSONObject* AJSON, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject) = 0 /* overload */;
	virtual bool __fastcall DeleteGroup(const Rest::Backend::Metatypes::TBackendEntityValue &AObject) = 0 /* overload */;
	virtual bool __fastcall FindGroup(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, _di_TFindObjectProc AProc) = 0 ;
	virtual void __fastcall UpdateGroup(const Rest::Backend::Metatypes::TBackendEntityValue &AObject, System::Json::TJSONObject* const AJSONObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBackendGroupsApi : public TBackendAuthenticationApi
{
	typedef TBackendAuthenticationApi inherited;
	
private:
	_di_IBackendGroupsService FService;
	_di_IBackendGroupsApi FServiceApi;
	_di_IBackendGroupsApi __fastcall GetServiceAPI();
	
protected:
	virtual _di_IBackendAuthenticationApi __fastcall GetAuthenticationApi();
	
public:
	Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaGroupObject(const System::UnicodeString AGroupName);
	__fastcall TBackendGroupsApi(const _di_IBackendGroupsApi AApi)/* overload */;
	__fastcall TBackendGroupsApi(const _di_IBackendGroupsService AService)/* overload */;
	void __fastcall AddUsers(const System::UnicodeString AGroupName, const System::TArray__1<System::UnicodeString> AUsers, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject);
	void __fastcall AddUser(const System::UnicodeString AGroupName, const System::UnicodeString AUser, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject);
	bool __fastcall RemoveUser(const System::UnicodeString AGroupName, const System::UnicodeString AUser, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject);
	bool __fastcall RemoveUsers(const System::UnicodeString AGroupName, const System::TArray__1<System::UnicodeString> AUsers, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject);
	void __fastcall CreateGroup(const System::UnicodeString AGroupName, System::Json::TJSONObject* const AJSON, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &ACreatedObject)/* overload */;
	bool __fastcall DeleteGroup(const System::UnicodeString AGroupName)/* overload */;
	bool __fastcall DeleteGroup(const Rest::Backend::Metatypes::TBackendEntityValue &AGroup)/* overload */;
	bool __fastcall FindGroup(const Rest::Backend::Metatypes::TBackendEntityValue &AMetaObject, _di_TFindObjectProc AProc)/* overload */;
	bool __fastcall FindGroup(const System::UnicodeString AGroupName, _di_TFindObjectProc AProc)/* overload */;
	void __fastcall UpdateGroup(const Rest::Backend::Metatypes::TBackendEntityValue &AGroup, System::Json::TJSONObject* const AJSONObject, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AUpdatedObject)/* overload */;
	__property _di_IBackendGroupsApi ProviderAPI = {read=GetServiceAPI};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBackendGroupsApi() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A925E828-73A5-41C0-93A4-4E12BC7949FB}") IBackendFilesService  : public Rest::Backend::Providers::IBackendService 
{
	virtual _di_IBackendFilesApi __fastcall GetFilesAPI() = 0 ;
	virtual _di_IBackendFilesApi __fastcall CreateFilesApi() = 0 ;
	__property _di_IBackendFilesApi FilesAPI = {read=GetFilesAPI};
};

__interface  INTERFACE_UUID("{271C2472-D957-47C5-BC10-F3A15FF5261C}") IBackendFilesApi  : public IBackendGetMetaFactory 
{
	virtual void __fastcall UploadFile(const System::UnicodeString AFileName, const System::UnicodeString AContentType, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AFile) = 0 /* overload */;
	virtual void __fastcall UploadFile(const System::UnicodeString AFileName, System::Classes::TStream* const AStream, const System::UnicodeString AContentType, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AFile) = 0 /* overload */;
	virtual bool __fastcall DeleteFile(const Rest::Backend::Metatypes::TBackendEntityValue &AFile) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBackendFilesApi : public TBackendAuthenticationApi
{
	typedef TBackendAuthenticationApi inherited;
	
private:
	_di_IBackendFilesService FService;
	_di_IBackendFilesApi FServiceApi;
	_di_IBackendFilesApi __fastcall GetServiceAPI();
	
protected:
	virtual _di_IBackendAuthenticationApi __fastcall GetAuthenticationApi();
	
public:
	Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaFileObject(const System::UnicodeString AFileID);
	__fastcall TBackendFilesApi(const _di_IBackendFilesApi AApi)/* overload */;
	__fastcall TBackendFilesApi(const _di_IBackendFilesService AService)/* overload */;
	void __fastcall UploadFile(const System::UnicodeString AFileName, const System::UnicodeString AContentType, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AFile)/* overload */;
	void __fastcall UploadFile(const System::UnicodeString AFileName, System::Classes::TStream* const AStream, const System::UnicodeString AContentType, /* out */ Rest::Backend::Metatypes::TBackendEntityValue &AFile)/* overload */;
	bool __fastcall DeleteFile(const Rest::Backend::Metatypes::TBackendEntityValue &AFile)/* overload */;
	bool __fastcall DeleteFile(const System::UnicodeString AFileID)/* overload */;
	__property _di_IBackendFilesApi ProviderAPI = {read=GetServiceAPI};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBackendFilesApi() { }
	
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
template<typename T> class PASCALIMPLEMENTATION TBackendObjectList__1 : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	class DELPHICLASS TEnumerator;
	// Template declaration generated by Delphi parameterized types is
	// used only for accessing Delphi variables and fields.
	// Don't instantiate with new type parameters in user code.
	class PASCALIMPLEMENTATION TEnumerator : public System::Generics::Collections::TEnumerator__1<T>
	{
		typedef System::Generics::Collections::TEnumerator__1<T> inherited;
		
	private:
		System::Generics::Collections::TList__1<T>* FList;
		int FIndex;
		
	protected:
		__fastcall TEnumerator(System::Generics::Collections::TList__1<T>* const AList);
		virtual T __fastcall DoGetCurrent();
		virtual bool __fastcall DoMoveNext();
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TEnumerator() { }
		
	};
	
	
	
public:
	T operator[](int I) { return this->Items[I]; }
	
private:
	System::Generics::Collections::TList__1<T>* FList;
	System::Generics::Collections::TDictionary__2<T,Rest::Backend::Metatypes::TBackendEntityValue>* FDictionary;
	int __fastcall GetCount();
	T __fastcall GetItem(int I);
	void __fastcall Clear();
	Rest::Backend::Metatypes::TBackendEntityValue __fastcall GetEntityValue(T I);
	
public:
	__fastcall TBackendObjectList__1();
	__fastcall virtual ~TBackendObjectList__1();
	System::Generics::Collections::TEnumerator__1<T>* __fastcall GetEnumerator();
	T __fastcall Extract(const T Value);
	System::TArray__1<T> __fastcall ExtractArray();
	void __fastcall Add(const T AValue, const Rest::Backend::Metatypes::TBackendEntityValue &AMetaObject);
	int __fastcall IndexOf(T I);
	__property int Count = {read=GetCount, nodefault};
	__property T Items[int I] = {read=GetItem/*, default*/};
	__property Rest::Backend::Metatypes::TBackendEntityValue EntityValues[T I] = {read=GetEntityValue};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BF37269F-BBDE-4110-BAFA-A1CC725BC5D0}") IBackendCustomEndpointService  : public Rest::Backend::Providers::IBackendService 
{
	virtual _di_IBackendCustomEndpointApi __fastcall GetCustomEndpointAPI() = 0 ;
	virtual _di_IBackendCustomEndpointApi __fastcall CreateCustomEndpointApi() = 0 ;
	__property _di_IBackendCustomEndpointApi CustomEndpointAPI = {read=GetCustomEndpointAPI};
};

__interface  INTERFACE_UUID("{974BD7BB-C39C-4C75-8056-148026839A38}") IBackendCustomEndpointApi  : public Rest::Backend::Providers::IBackendService 
{
	virtual void __fastcall PrepareClient(Rest::Client::TCustomRESTClient* const AClient) = 0 ;
	virtual void __fastcall PrepareRequest(Rest::Client::TCustomRESTRequest* const ARequest) = 0 ;
	virtual void __fastcall CheckForResponseErrors(Rest::Client::TCustomRESTResponse* const AResponse, int *AValidStatusCodes, const int AValidStatusCodes_High) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBackendCustomEndPointApi : public TBackendAuthenticationApi
{
	typedef TBackendAuthenticationApi inherited;
	
private:
	_di_IBackendCustomEndpointService FService;
	_di_IBackendCustomEndpointApi FServiceApi;
	_di_IBackendCustomEndpointApi __fastcall GetServiceAPI();
	
protected:
	virtual _di_IBackendAuthenticationApi __fastcall GetAuthenticationApi();
	
public:
	__fastcall TBackendCustomEndPointApi(const _di_IBackendCustomEndpointApi AApi)/* overload */;
	__fastcall TBackendCustomEndPointApi(const _di_IBackendCustomEndpointService AService)/* overload */;
	void __fastcall PrepareClient(Rest::Client::TCustomRESTClient* const AClient);
	void __fastcall PrepareRequest(Rest::Client::TCustomRESTRequest* const ARequest);
	void __fastcall CheckForResponseErrors(Rest::Client::TCustomRESTResponse* const AResponse, int *AValidStatusCodes, const int AValidStatusCodes_High);
	__property _di_IBackendCustomEndpointApi ProviderAPI = {read=GetServiceAPI};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBackendCustomEndPointApi() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Servicetypes */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_SERVICETYPES)
using namespace Rest::Backend::Servicetypes;
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
#endif	// Rest_Backend_ServicetypesHPP
