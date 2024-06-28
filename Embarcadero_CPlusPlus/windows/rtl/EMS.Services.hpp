// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMS.Services.pas' rev: 34.00 (Windows)

#ifndef Ems_ServicesHPP
#define Ems_ServicesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <EMS.ResourceAPI.hpp>
#include <EMS.ResourceTypes.hpp>
#include <System.JSON.hpp>
#include <System.Generics.Collections.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ems
{
namespace Services
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEMSApplicationService;
class DELPHICLASS TEMSServices;
class DELPHICLASS TEMSLoggingService;
__interface DELPHIINTERFACE IEMSServices;
typedef System::DelphiInterface<IEMSServices> _di_IEMSServices;
__interface DELPHIINTERFACE IEMSEndPointSegmentsService;
typedef System::DelphiInterface<IEMSEndPointSegmentsService> _di_IEMSEndPointSegmentsService;
__interface DELPHIINTERFACE IEMSApplicationService;
typedef System::DelphiInterface<IEMSApplicationService> _di_IEMSApplicationService;
__interface DELPHIINTERFACE TEMSLoggingOutputProc;
typedef System::DelphiInterface<TEMSLoggingOutputProc> _di_TEMSLoggingOutputProc;
__interface DELPHIINTERFACE IEMSLoggingService;
typedef System::DelphiInterface<IEMSLoggingService> _di_IEMSLoggingService;
__interface DELPHIINTERFACE IEMSResourceRequestContext;
typedef System::DelphiInterface<IEMSResourceRequestContext> _di_IEMSResourceRequestContext;
__interface DELPHIINTERFACE IEMSResourceRequestContent;
typedef System::DelphiInterface<IEMSResourceRequestContent> _di_IEMSResourceRequestContent;
__interface DELPHIINTERFACE IEMSResourceResponseContent;
typedef System::DelphiInterface<IEMSResourceResponseContent> _di_IEMSResourceResponseContent;
__interface DELPHIINTERFACE IEMSResourceRequest;
typedef System::DelphiInterface<IEMSResourceRequest> _di_IEMSResourceRequest;
__interface DELPHIINTERFACE IEMSInternalResourceRequestService;
typedef System::DelphiInterface<IEMSInternalResourceRequestService> _di_IEMSInternalResourceRequestService;
__interface DELPHIINTERFACE IEMSModuleResourceRequest;
typedef System::DelphiInterface<IEMSModuleResourceRequest> _di_IEMSModuleResourceRequest;
__interface DELPHIINTERFACE IEMSModuleResourceRequestService;
typedef System::DelphiInterface<IEMSModuleResourceRequestService> _di_IEMSModuleResourceRequestService;
class DELPHICLASS TEMSInternalAPI;
class DELPHICLASS EEMSInternalAPIError;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSApplicationService : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod void __fastcall AddStartupNotification(System::Sysutils::_di_TProc AProc);
	__classmethod void __fastcall AddShutdownNotification(System::Sysutils::_di_TProc AProc);
public:
	/* TObject.Create */ inline __fastcall TEMSApplicationService() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEMSApplicationService() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSServices : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	template<typename T> __classmethod T __fastcall GetService();
	template<typename T> __classmethod bool __fastcall TryGetService(/* out */ T &Intf);
public:
	/* TObject.Create */ inline __fastcall TEMSServices() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEMSServices() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSLoggingService : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static bool __fastcall GetLoggingEnabled();
	static _di_IEMSLoggingService __fastcall GetService();
	
public:
	__classmethod void __fastcall Log(const System::UnicodeString ACategory, System::Json::TJSONObject* const AJSON);
	/* static */ __property bool LoggingEnabled = {read=GetLoggingEnabled, nodefault};
public:
	/* TObject.Create */ inline __fastcall TEMSLoggingService() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEMSLoggingService() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{E9E681C2-3399-4D55-A294-F20E2A59BE35}") IEMSServices  : public System::IInterface 
{
	virtual bool __fastcall SupportsService(const GUID &Service) = 0 ;
	virtual System::_di_IInterface __fastcall GetService(const GUID &Service) = 0 /* overload */;
	virtual bool __fastcall TryGetService(const GUID &Service, /* out */ void *Svc) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{15ECD41C-D332-48BA-9C3E-67152EF24205}") IEMSEndPointSegmentsService  : public System::IInterface 
{
	virtual void __fastcall ExtractSegments(const System::UnicodeString AString, Ems::Resourcetypes::TEMSEndpointSegmentList* const AList) = 0 ;
	virtual int __fastcall CountSegments(const System::UnicodeString AValue) = 0 ;
};

__interface  INTERFACE_UUID("{D5D6FAF8-9AFE-4A9A-81BB-659016EDB179}") IEMSApplicationService  : public System::IInterface 
{
	virtual void __fastcall Startup() = 0 ;
	virtual void __fastcall Shutdown() = 0 ;
	virtual void __fastcall AddStartupNotification(System::Sysutils::_di_TProc AProc) = 0 ;
	virtual void __fastcall AddShutdownNotification(System::Sysutils::_di_TProc AProc) = 0 ;
};

__interface TEMSLoggingOutputProc  : public System::IInterface 
{
	virtual void __fastcall Invoke(const System::UnicodeString ACategory, System::Json::TJSONObject* const AJSON) = 0 ;
};

typedef System::DelphiInterface<System::Sysutils::TFunc__1<bool> > TEMSLoggingEnabledFunc;

__interface  INTERFACE_UUID("{261E2580-D991-4E1B-9FFF-D68EBD2DEB6F}") IEMSLoggingService  : public System::IInterface 
{
	virtual bool __fastcall GetLoggingEnabled() = 0 ;
	virtual void __fastcall Log(const System::UnicodeString ACategory, System::Json::TJSONObject* const AJSON) = 0 ;
	__property bool LoggingEnabled = {read=GetLoggingEnabled};
	virtual void __fastcall SetupCustomOutput(const System::DelphiInterface<System::Sysutils::TFunc__1<bool> > AEnabled, const _di_TEMSLoggingOutputProc AOutput, const bool ASynchronize) = 0 ;
	virtual void __fastcall SetupFileOutput(const System::UnicodeString AFileName, const bool AAppend) = 0 ;
};

typedef System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> TEMSResourceRequestQueryParam;

#ifndef _WIN64
typedef System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > TEMSResourceRequestQueryParams;
#else /* _WIN64 */
typedef System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > TEMSResourceRequestQueryParams;
#endif /* _WIN64 */

#ifndef _WIN64
typedef System::DynamicArray<System::UnicodeString> TEMSResourceRequestSegments;
#else /* _WIN64 */
typedef System::TArray__1<System::UnicodeString> TEMSResourceRequestSegments;
#endif /* _WIN64 */

__interface IEMSResourceRequestContext  : public System::IInterface 
{
	
};

__interface IEMSResourceRequestContent  : public System::IInterface 
{
	
};

__interface IEMSResourceResponseContent  : public System::IInterface 
{
	virtual int __fastcall GetStatusCode() = 0 ;
	virtual System::UnicodeString __fastcall GetContentType() = 0 ;
	virtual bool __fastcall TryGetStream(/* out */ System::Classes::TStream* &AStream) = 0 /* overload */;
	virtual bool __fastcall TryGetStream(/* out */ System::Classes::TStream* &AStream, /* out */ System::UnicodeString &AContentType) = 0 /* overload */;
	virtual bool __fastcall TryGetObject(/* out */ System::Json::TJSONObject* &AJSONObject) = 0 ;
	virtual bool __fastcall TryGetArray(/* out */ System::Json::TJSONArray* &AJSONArray) = 0 ;
	virtual bool __fastcall TryGetValue(/* out */ System::Json::TJSONValue* &AJSONValue) = 0 ;
#ifndef _WIN64
	virtual bool __fastcall TryGetBytes(/* out */ System::DynamicArray<System::Byte> &ABytes) = 0 ;
#else /* _WIN64 */
	virtual bool __fastcall TryGetBytes(/* out */ System::TArray__1<System::Byte> &ABytes) = 0 ;
#endif /* _WIN64 */
	virtual System::Classes::TStream* __fastcall GetStream() = 0 ;
	virtual System::Json::TJSONObject* __fastcall GetObject() = 0 ;
	virtual System::Json::TJSONArray* __fastcall GetArray() = 0 ;
	virtual System::Json::TJSONValue* __fastcall GetValue() = 0 ;
#ifndef _WIN64
	virtual System::DynamicArray<System::Byte> __fastcall GetBytes() = 0 ;
#else /* _WIN64 */
	virtual System::TArray__1<System::Byte> __fastcall GetBytes() = 0 ;
#endif /* _WIN64 */
	__property System::UnicodeString ContentType = {read=GetContentType};
	__property int StatusCode = {read=GetStatusCode};
};

__interface IEMSResourceRequest  : public System::IInterface 
{
	virtual _di_IEMSResourceRequestContext __fastcall CreateRequestContext(Ems::Resourceapi::TEndpointContext* const AContext) = 0 ;
	virtual _di_IEMSResourceRequestContent __fastcall CreateRequestContent(System::Json::TJSONValue* const AJSON) = 0 /* overload */;
	virtual _di_IEMSResourceRequestContent __fastcall CreateRequestContent(const System::UnicodeString AContentType, System::Classes::TStream* const AStream) = 0 /* overload */;
#ifndef _WIN64
	virtual _di_IEMSResourceRequestContent __fastcall CreateRequestContent(const System::UnicodeString AContentType, const System::DynamicArray<System::Byte> ABytes) = 0 /* overload */;
	virtual _di_IEMSResourceResponseContent __fastcall Execute(const _di_IEMSResourceRequestContext AContext, const Ems::Resourceapi::TEndpointRequest::TMethod AMethodType, const System::UnicodeString AResourceName, const System::DynamicArray<System::UnicodeString> ASegments, const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams, const _di_IEMSResourceRequestContent ARequestContent) = 0 /* overload */;
	virtual _di_IEMSResourceResponseContent __fastcall Execute(const _di_IEMSResourceRequestContext AContext, Ems::Resourceapi::TEndpointRequest::TMethod AMethodType, const System::UnicodeString AResourceName, const System::DynamicArray<System::UnicodeString> ASegments, const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams) = 0 /* overload */;
	virtual _di_IEMSResourceResponseContent __fastcall Delete(const _di_IEMSResourceRequestContext AContext, const System::UnicodeString AResourceName, const System::DynamicArray<System::UnicodeString> ASegments, const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams) = 0 ;
	virtual _di_IEMSResourceResponseContent __fastcall Get(const _di_IEMSResourceRequestContext AContext, const System::UnicodeString AResourceName, const System::DynamicArray<System::UnicodeString> ASegments, const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams) = 0 ;
	virtual _di_IEMSResourceResponseContent __fastcall Patch(const _di_IEMSResourceRequestContext AContext, const System::UnicodeString AResourceName, const System::DynamicArray<System::UnicodeString> ASegments, const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams, const _di_IEMSResourceRequestContent ARequestContent) = 0 ;
	virtual _di_IEMSResourceResponseContent __fastcall Post(const _di_IEMSResourceRequestContext AContext, const System::UnicodeString AResourceName, const System::DynamicArray<System::UnicodeString> ASegments, const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams, const _di_IEMSResourceRequestContent ARequestContent) = 0 ;
	virtual _di_IEMSResourceResponseContent __fastcall Put(const _di_IEMSResourceRequestContext AContext, const System::UnicodeString AResourceName, const System::DynamicArray<System::UnicodeString> ASegments, const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams, const _di_IEMSResourceRequestContent ARequestContent) = 0 ;
	virtual _di_IEMSResourceResponseContent __fastcall Head(const _di_IEMSResourceRequestContext AContext, const System::UnicodeString AResourceName, const System::DynamicArray<System::UnicodeString> ASegments, const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams) = 0 ;
#else /* _WIN64 */
	virtual _di_IEMSResourceRequestContent __fastcall CreateRequestContent(const System::UnicodeString AContentType, const System::TArray__1<System::Byte> ABytes) = 0 /* overload */;
	virtual _di_IEMSResourceResponseContent __fastcall Execute(const _di_IEMSResourceRequestContext AContext, const Ems::Resourceapi::TEndpointRequest::TMethod AMethodType, const System::UnicodeString AResourceName, const System::TArray__1<System::UnicodeString> ASegments, const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams, const _di_IEMSResourceRequestContent ARequestContent) = 0 /* overload */;
	virtual _di_IEMSResourceResponseContent __fastcall Execute(const _di_IEMSResourceRequestContext AContext, Ems::Resourceapi::TEndpointRequest::TMethod AMethodType, const System::UnicodeString AResourceName, const System::TArray__1<System::UnicodeString> ASegments, const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams) = 0 /* overload */;
	virtual _di_IEMSResourceResponseContent __fastcall Delete(const _di_IEMSResourceRequestContext AContext, const System::UnicodeString AResourceName, const System::TArray__1<System::UnicodeString> ASegments, const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams) = 0 ;
	virtual _di_IEMSResourceResponseContent __fastcall Get(const _di_IEMSResourceRequestContext AContext, const System::UnicodeString AResourceName, const System::TArray__1<System::UnicodeString> ASegments, const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams) = 0 ;
	virtual _di_IEMSResourceResponseContent __fastcall Patch(const _di_IEMSResourceRequestContext AContext, const System::UnicodeString AResourceName, const System::TArray__1<System::UnicodeString> ASegments, const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams, const _di_IEMSResourceRequestContent ARequestContent) = 0 ;
	virtual _di_IEMSResourceResponseContent __fastcall Post(const _di_IEMSResourceRequestContext AContext, const System::UnicodeString AResourceName, const System::TArray__1<System::UnicodeString> ASegments, const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams, const _di_IEMSResourceRequestContent ARequestContent) = 0 ;
	virtual _di_IEMSResourceResponseContent __fastcall Put(const _di_IEMSResourceRequestContext AContext, const System::UnicodeString AResourceName, const System::TArray__1<System::UnicodeString> ASegments, const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams, const _di_IEMSResourceRequestContent ARequestContent) = 0 ;
	virtual _di_IEMSResourceResponseContent __fastcall Head(const _di_IEMSResourceRequestContext AContext, const System::UnicodeString AResourceName, const System::TArray__1<System::UnicodeString> ASegments, const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams) = 0 ;
#endif /* _WIN64 */
};

__interface  INTERFACE_UUID("{0C98920E-E524-4917-8F00-AC968C0A9D13}") IEMSInternalResourceRequestService  : public IEMSResourceRequest 
{
	
};

__interface IEMSModuleResourceRequest  : public IEMSResourceRequest 
{
	virtual System::UnicodeString __fastcall GetModuleName() = 0 ;
	__property System::UnicodeString ModuleName = {read=GetModuleName};
};

__interface  INTERFACE_UUID("{24772850-762F-43FA-9B9E-0818750F0E06}") IEMSModuleResourceRequestService  : public System::IInterface 
{
	virtual _di_IEMSModuleResourceRequest __fastcall CreateRequest(const System::UnicodeString AModuleName) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSInternalAPI : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TJSONNames
	{
	public:
		#define TEMSInternalAPI_TJSONNames_UserName L"username"
		
		#define TEMSInternalAPI_TJSONNames_Password L"password"
		
		#define TEMSInternalAPI_TJSONNames_SessionToken L"sessionToken"
		
		#define TEMSInternalAPI_TJSONNames_Error L"error"
		
		#define TEMSInternalAPI_TJSONNames_Description L"description"
		
		#define TEMSInternalAPI_TJSONNames_UserID L"_id"
		
		#define TEMSInternalAPI_TJSONNames_GroupName L"groupname"
		
		#define TEMSInternalAPI_TJSONNames_InstallationID L"_id"
		
		#define TEMSInternalAPI_TJSONNames_MetaData L"_meta"
		
		#define TEMSInternalAPI_TJSONNames_MetaCreated L"created"
		
		#define TEMSInternalAPI_TJSONNames_MetaUpdated L"updated"
		
		#define TEMSInternalAPI_TJSONNames_MetaCreator L"creator"
		
		#define TEMSInternalAPI_TJSONNames_PushWhere L"where"
		
		#define TEMSInternalAPI_TJSONNames_PushChannels L"channels"
		
		#define TEMSInternalAPI_TJSONNames_PushData L"data"
		
		#define TEMSInternalAPI_TJSONNames_GroupUsers L"users"
		
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TSegmentNames
	{
	public:
		#define TEMSInternalAPI_TSegmentNames_Users L"users"
		
		#define TEMSInternalAPI_TSegmentNames_Groups L"groups"
		
		#define TEMSInternalAPI_TSegmentNames_Installations L"installations"
		
		#define TEMSInternalAPI_TSegmentNames_Edgemodules L"edgemodules"
		
		#define TEMSInternalAPI_TSegmentNames_Resources L"resources"
		
		#define TEMSInternalAPI_TSegmentNames_Login L"login"
		
		#define TEMSInternalAPI_TSegmentNames_Signup L"signup"
		
		#define TEMSInternalAPI_TSegmentNames_Logout L"_logout"
		
		#define TEMSInternalAPI_TSegmentNames_Me L"me"
		
		#define TEMSInternalAPI_TSegmentNames_Push L"push"
		
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
	typedef System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> TQueryParam;
	
#ifndef _WIN64
	typedef System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > TQueryParams;
#else /* _WIN64 */
	typedef System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > TQueryParams;
#endif /* _WIN64 */
	
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TQueryParamNames
	{
	public:
		#define TEMSInternalAPI_TQueryParamNames_Order L"order"
		
		#define TEMSInternalAPI_TQueryParamNames_Where L"where"
		
		#define TEMSInternalAPI_TQueryParamNames_Limit L"limit"
		
		#define TEMSInternalAPI_TQueryParamNames_Skip L"skip"
		
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
	
private:
	_di_IEMSResourceRequestContext FContext;
	_di_IEMSInternalResourceRequestService FService;
	
public:
	__fastcall TEMSInternalAPI(Ems::Resourceapi::TEndpointContext* const AContext);
	_di_IEMSResourceResponseContent __fastcall AddUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, System::Json::TJSONObject* const AUserFields)/* overload */;
	_di_IEMSResourceResponseContent __fastcall AddUser(System::Json::TJSONObject* const AJSONBody)/* overload */;
	bool __fastcall DeleteUser(const System::UnicodeString AObjectID, /* out */ _di_IEMSResourceResponseContent &AResponse)/* overload */;
	bool __fastcall DeleteUser(const System::UnicodeString AObjectID)/* overload */;
	_di_IEMSResourceResponseContent __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword)/* overload */;
	_di_IEMSResourceResponseContent __fastcall LoginUser(System::Json::TJSONObject* const AJSONLogin)/* overload */;
	_di_IEMSResourceResponseContent __fastcall Logout()/* overload */;
	bool __fastcall QueryUserName(const System::UnicodeString AUserName, /* out */ _di_IEMSResourceResponseContent &AResponse)/* overload */;
	bool __fastcall QueryUserName(const System::UnicodeString AUserName)/* overload */;
#ifndef _WIN64
	_di_IEMSResourceResponseContent __fastcall QueryUsers(const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQuery)/* overload */;
#else /* _WIN64 */
	_di_IEMSResourceResponseContent __fastcall QueryUsers(const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQuery)/* overload */;
#endif /* _WIN64 */
	bool __fastcall RetrieveUser(const System::UnicodeString AObjectID, /* out */ _di_IEMSResourceResponseContent &AResponse);
	_di_IEMSResourceResponseContent __fastcall SignupUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, System::Json::TJSONObject* const AUserFields)/* overload */;
	_di_IEMSResourceResponseContent __fastcall SignupUser(System::Json::TJSONObject* const AJSONBody)/* overload */;
	_di_IEMSResourceResponseContent __fastcall UpdateUser(const System::UnicodeString AObjectID, System::Json::TJSONObject* const AUserFields)/* overload */;
#ifndef _WIN64
	_di_IEMSResourceResponseContent __fastcall AddUsersToGroup(const System::UnicodeString AGroupName, const System::DynamicArray<System::UnicodeString> AUsers);
#else /* _WIN64 */
	_di_IEMSResourceResponseContent __fastcall AddUsersToGroup(const System::UnicodeString AGroupName, const System::TArray__1<System::UnicodeString> AUsers);
#endif /* _WIN64 */
	_di_IEMSResourceResponseContent __fastcall CreateGroup(const System::UnicodeString AGroupName, System::Json::TJSONObject* const AGroupFields)/* overload */;
	_di_IEMSResourceResponseContent __fastcall CreateGroup(System::Json::TJSONObject* const AJSONBody)/* overload */;
	bool __fastcall DeleteGroup(const System::UnicodeString AGroupName, /* out */ _di_IEMSResourceResponseContent &AResponse)/* overload */;
	bool __fastcall DeleteGroup(const System::UnicodeString AGroupName)/* overload */;
#ifndef _WIN64
	_di_IEMSResourceResponseContent __fastcall QueryGroups(const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQuery);
	bool __fastcall RemoveUsersFromGroup(const System::UnicodeString AGroupName, const System::DynamicArray<System::UnicodeString> AUsers, /* out */ _di_IEMSResourceResponseContent &AResponse);
#else /* _WIN64 */
	_di_IEMSResourceResponseContent __fastcall QueryGroups(const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQuery);
	bool __fastcall RemoveUsersFromGroup(const System::UnicodeString AGroupName, const System::TArray__1<System::UnicodeString> AUsers, /* out */ _di_IEMSResourceResponseContent &AResponse);
#endif /* _WIN64 */
	bool __fastcall RetrieveGroup(const System::UnicodeString AGroupName, /* out */ _di_IEMSResourceResponseContent &AResponse);
	_di_IEMSResourceResponseContent __fastcall UpdateGroup(const System::UnicodeString AGroupName, System::Json::TJSONObject* const AGroupFields)/* overload */;
	bool __fastcall DeleteInstallation(const System::UnicodeString AInstallationID, /* out */ _di_IEMSResourceResponseContent &AResponse)/* overload */;
	bool __fastcall DeleteInstallation(const System::UnicodeString AInstallationID)/* overload */;
#ifndef _WIN64
	_di_IEMSResourceResponseContent __fastcall QueryInstallations(const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQuery);
#else /* _WIN64 */
	_di_IEMSResourceResponseContent __fastcall QueryInstallations(const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQuery);
#endif /* _WIN64 */
	bool __fastcall RetrieveInstallation(const System::UnicodeString AInstallationID, /* out */ _di_IEMSResourceResponseContent &AResponse)/* overload */;
	_di_IEMSResourceResponseContent __fastcall UpdateInstallation(const System::UnicodeString AInstallationID, System::Json::TJSONObject* const AJSONObject)/* overload */;
	_di_IEMSResourceResponseContent __fastcall PushBroadcast(System::Json::TJSONObject* const AData);
	_di_IEMSResourceResponseContent __fastcall PushToTarget(System::Json::TJSONObject* const AData, System::Json::TJSONObject* const ATarget);
	_di_IEMSResourceResponseContent __fastcall PushToChannels(System::Json::TJSONObject* const AData, const System::UnicodeString *AChannels, const int AChannels_High);
	_di_IEMSResourceResponseContent __fastcall PushWhere(System::Json::TJSONObject* const AData, System::Json::TJSONObject* const AWhere);
	bool __fastcall UnregisterModule(const System::UnicodeString AModuleName, /* out */ _di_IEMSResourceResponseContent &AResponse)/* overload */;
	bool __fastcall UnregisterModule(const System::UnicodeString AModuleName)/* overload */;
	bool __fastcall UnregisterModuleResource(const System::UnicodeString AModuleName, const System::UnicodeString AResourceName, /* out */ _di_IEMSResourceResponseContent &AResponse)/* overload */;
	bool __fastcall UnregisterModuleResource(const System::UnicodeString AModuleName, const System::UnicodeString AResourceName)/* overload */;
#ifndef _WIN64
	_di_IEMSResourceResponseContent __fastcall QueryModules(const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQuery);
	_di_IEMSResourceResponseContent __fastcall QueryModuleResources(const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQuery)/* overload */;
	_di_IEMSResourceResponseContent __fastcall QueryModuleResources(const System::UnicodeString AModuleName, const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQuery)/* overload */;
#else /* _WIN64 */
	_di_IEMSResourceResponseContent __fastcall QueryModules(const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQuery);
	_di_IEMSResourceResponseContent __fastcall QueryModuleResources(const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQuery)/* overload */;
	_di_IEMSResourceResponseContent __fastcall QueryModuleResources(const System::UnicodeString AModuleName, const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQuery)/* overload */;
#endif /* _WIN64 */
	bool __fastcall RetrieveModule(const System::UnicodeString AModuleName, /* out */ _di_IEMSResourceResponseContent &AResponse)/* overload */;
	bool __fastcall RetrieveModuleResource(const System::UnicodeString AModuleName, const System::UnicodeString AResourceName, /* out */ _di_IEMSResourceResponseContent &AResponse)/* overload */;
	_di_IEMSResourceResponseContent __fastcall UpdateModule(const System::UnicodeString AModuleName, System::Json::TJSONObject* const AJSONObject)/* overload */;
	_di_IEMSResourceResponseContent __fastcall UpdateModuleResource(const System::UnicodeString AModuleName, const System::UnicodeString AResourceName, System::Json::TJSONObject* const AJSONObject)/* overload */;
#ifndef _WIN64
	_di_IEMSResourceResponseContent __fastcall ModuleResourceDelete(const System::UnicodeString AModuleName, const System::UnicodeString AResourceName, const System::DynamicArray<System::UnicodeString> ASegments, const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams);
	_di_IEMSResourceResponseContent __fastcall ModuleResourceGet(const System::UnicodeString AModuleName, const System::UnicodeString AResourceName, const System::DynamicArray<System::UnicodeString> ASegments, const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams);
	_di_IEMSResourceResponseContent __fastcall ModuleResourcePatch(const System::UnicodeString AModuleName, const System::UnicodeString AResourceName, const System::DynamicArray<System::UnicodeString> ASegments, const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams, const _di_IEMSResourceRequestContent ARequestContent);
	_di_IEMSResourceResponseContent __fastcall ModuleResourcePost(const System::UnicodeString AModuleName, const System::UnicodeString AResourceName, const System::DynamicArray<System::UnicodeString> ASegments, const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams, const _di_IEMSResourceRequestContent ARequestContent);
	_di_IEMSResourceResponseContent __fastcall ModuleResourcePut(const System::UnicodeString AModuleName, const System::UnicodeString AResourceName, const System::DynamicArray<System::UnicodeString> ASegments, const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams, const _di_IEMSResourceRequestContent ARequestContent);
#else /* _WIN64 */
	_di_IEMSResourceResponseContent __fastcall ModuleResourceDelete(const System::UnicodeString AModuleName, const System::UnicodeString AResourceName, const System::TArray__1<System::UnicodeString> ASegments, const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams);
	_di_IEMSResourceResponseContent __fastcall ModuleResourceGet(const System::UnicodeString AModuleName, const System::UnicodeString AResourceName, const System::TArray__1<System::UnicodeString> ASegments, const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams);
	_di_IEMSResourceResponseContent __fastcall ModuleResourcePatch(const System::UnicodeString AModuleName, const System::UnicodeString AResourceName, const System::TArray__1<System::UnicodeString> ASegments, const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams, const _di_IEMSResourceRequestContent ARequestContent);
	_di_IEMSResourceResponseContent __fastcall ModuleResourcePost(const System::UnicodeString AModuleName, const System::UnicodeString AResourceName, const System::TArray__1<System::UnicodeString> ASegments, const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams, const _di_IEMSResourceRequestContent ARequestContent);
	_di_IEMSResourceResponseContent __fastcall ModuleResourcePut(const System::UnicodeString AModuleName, const System::UnicodeString AResourceName, const System::TArray__1<System::UnicodeString> ASegments, const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryParams, const _di_IEMSResourceRequestContent ARequestContent);
#endif /* _WIN64 */
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TEMSInternalAPI() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSInternalAPIError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EEMSInternalAPIError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EEMSInternalAPIError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSInternalAPIError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSInternalAPIError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSInternalAPIError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSInternalAPIError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSInternalAPIError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSInternalAPIError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSInternalAPIError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSInternalAPIError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSInternalAPIError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSInternalAPIError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSInternalAPIError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE _di_IEMSServices EMSServices;
}	/* namespace Services */
}	/* namespace Ems */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMS_SERVICES)
using namespace Ems::Services;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMS)
using namespace Ems;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ems_ServicesHPP
