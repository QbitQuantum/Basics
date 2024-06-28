// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMSHosting.RequestHandler.pas' rev: 34.00 (Windows)

#ifndef Emshosting_RequesthandlerHPP
#define Emshosting_RequesthandlerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <EMSHosting.RequestTypes.hpp>
#include <EMS.ResourceAPI.hpp>
#include <EMSHosting.Endpoints.hpp>

//-- user supplied -----------------------------------------------------------

namespace Emshosting
{
namespace Requesthandler
{
//-- forward type declarations -----------------------------------------------
struct TEMSHostRequestProps;
class DELPHICLASS TEMSHostRequestHandler;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TEMSHostRequestProps
{
	
public:
	struct DECLSPEC_DRECORD THeaderNames
	{
	public:
		#define TEMSHostRequestProps_THeaderNames_ApiVersion L"X-Embarcadero-Api-Version"
		
		#define TEMSHostRequestProps_THeaderNames_ApplicationId L"X-Embarcadero-Application-Id"
		
		#define TEMSHostRequestProps_THeaderNames_SessionToken L"X-Embarcadero-Session-Token"
		
		#define TEMSHostRequestProps_THeaderNames_MasterSecret L"X-Embarcadero-Master-Secret"
		
		#define TEMSHostRequestProps_THeaderNames_AppSecret L"X-Embarcadero-App-Secret"
		
		#define TEMSHostRequestProps_THeaderNames_TenantId L"X-Embarcadero-Tenant-Id"
		
		#define TEMSHostRequestProps_THeaderNames_TenantSecret L"X-Embarcadero-Tenant-Secret"
		
	};
	
	
	
private:
	System::UnicodeString FApplicationId;
	System::UnicodeString FApiVersion;
	System::UnicodeString FApiMajorVersion;
	System::UnicodeString FApiMinorVersion;
	System::UnicodeString FSessionToken;
	System::UnicodeString FResourceURL;
	System::UnicodeString FAppSecret;
	System::UnicodeString FMasterSecret;
	System::UnicodeString FTenantId;
	System::UnicodeString FTenantSecret;
	
public:
	__property System::UnicodeString ApiVersion = {read=FApiVersion};
	__property System::UnicodeString ApiMajorVersion = {read=FApiMajorVersion};
	__property System::UnicodeString ApiMinorVersion = {read=FApiMinorVersion};
	__property System::UnicodeString ApplicationID = {read=FApplicationId};
	__property System::UnicodeString ResourceURL = {read=FResourceURL};
	__property System::UnicodeString SessionToken = {read=FSessionToken};
	__property System::UnicodeString AppSecret = {read=FAppSecret};
	__property System::UnicodeString MasterSecret = {read=FMasterSecret};
	__property System::UnicodeString TenantId = {read=FTenantId};
	__property System::UnicodeString TenantSecret = {read=FTenantSecret};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSHostRequestHandler : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TEMSHostRequestProps __fastcall GetRequestProps(const Emshosting::Requesttypes::_di_IEMSHostRequest Request);
	Ems::Resourceapi::TEndpointContext::TGroups* __fastcall GetGroups(const Emshosting::Requesttypes::_di_IEMSHostContext AContext, const System::UnicodeString AUserID, const System::UnicodeString ATenantId, Ems::Resourceapi::TEndpointContext::TGroups* &AGroups);
	System::UnicodeString __fastcall GetUserID(const Emshosting::Requesttypes::_di_IEMSHostContext AContext, const System::UnicodeString ASessionToken, const System::UnicodeString ATenantId, System::UnicodeString &AUserID);
	System::UnicodeString __fastcall GetUserName(const Emshosting::Requesttypes::_di_IEMSHostContext AContext, const System::UnicodeString AUserID, const System::UnicodeString ATenantId, System::UnicodeString &AUserName);
	
protected:
	virtual bool __fastcall UserIDOfSession(const Emshosting::Requesttypes::_di_IEMSHostContext AContext, const System::UnicodeString ASessionToken, const System::UnicodeString ATenantId, /* out */ System::UnicodeString &AUserID) = 0 ;
	virtual bool __fastcall UserNameOfID(const Emshosting::Requesttypes::_di_IEMSHostContext AContext, const System::UnicodeString AUserID, const System::UnicodeString ATenantId, /* out */ System::UnicodeString &AUserName) = 0 ;
#ifndef _WIN64
	virtual System::DynamicArray<System::UnicodeString> __fastcall GetGroupsByUser(const Emshosting::Requesttypes::_di_IEMSHostContext AContext, const System::UnicodeString AUserID, const System::UnicodeString ATenantId);
#else /* _WIN64 */
	virtual System::TArray__1<System::UnicodeString> __fastcall GetGroupsByUser(const Emshosting::Requesttypes::_di_IEMSHostContext AContext, const System::UnicodeString AUserID, const System::UnicodeString ATenantId);
#endif /* _WIN64 */
	virtual void __fastcall CheckForbiddenRequest(const System::UnicodeString AResourceName, const System::UnicodeString AOriginalResourceName) = 0 ;
#ifndef _WIN64
	virtual void __fastcall AuthenticateRequest(const System::DynamicArray<Ems::Resourceapi::TEMSResource*> AResources, const TEMSHostRequestProps &AResourceRequest, Ems::Resourceapi::TEndpointContext::TAuthenticated &AAuthenticated) = 0 ;
#else /* _WIN64 */
	virtual void __fastcall AuthenticateRequest(const System::TArray__1<Ems::Resourceapi::TEMSResource*> AResources, const TEMSHostRequestProps &AResourceRequest, Ems::Resourceapi::TEndpointContext::TAuthenticated &AAuthenticated) = 0 ;
#endif /* _WIN64 */
	virtual void __fastcall LogEndpoint(const System::UnicodeString AResource, const System::UnicodeString AEndpointName, const System::UnicodeString AMethod, const System::UnicodeString AUserID, const System::UnicodeString ACustom, const System::UnicodeString ATenantId) = 0 ;
	virtual void __fastcall RedirectResource(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEMSResource* &AResource, System::UnicodeString &AEndpointName) = 0 ;
	virtual System::UnicodeString __fastcall ResourcesPath();
	virtual bool __fastcall IsUserBelongsToTenant(const System::UnicodeString AUserId, const System::UnicodeString ATenantId) = 0 ;
	virtual System::UnicodeString __fastcall GetTenantNameByTenantId(const System::UnicodeString ATenantId, const Emshosting::Requesttypes::_di_IEMSHostContext AContext = Emshosting::Requesttypes::_di_IEMSHostContext()) = 0 ;
	virtual System::UnicodeString __fastcall GetDefaultTenantId() = 0 ;
	
public:
	void __fastcall HandleRequest(const Emshosting::Requesttypes::_di_IEMSHostContext Context, const Emshosting::Requesttypes::_di_IEMSHostRequest Request, const Emshosting::Requesttypes::_di_IEMSHostResponse Response, bool &Handled);
	void __fastcall HandleException(System::Sysutils::Exception* const E, const Emshosting::Requesttypes::_di_IEMSHostResponse Response, bool &Handled);
public:
	/* TObject.Create */ inline __fastcall TEMSHostRequestHandler() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEMSHostRequestHandler() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Requesthandler */
}	/* namespace Emshosting */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING_REQUESTHANDLER)
using namespace Emshosting::Requesthandler;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING)
using namespace Emshosting;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Emshosting_RequesthandlerHPP
