// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMSHosting.EdgeRequestHandler.pas' rev: 34.00 (Windows)

#ifndef Emshosting_EdgerequesthandlerHPP
#define Emshosting_EdgerequesthandlerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <EMSHosting.RequestTypes.hpp>
#include <EMSHosting.RequestHandler.hpp>
#include <EMS.ResourceAPI.hpp>
#include <EMSHosting.Endpoints.hpp>

//-- user supplied -----------------------------------------------------------

namespace Emshosting
{
namespace Edgerequesthandler
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEdgeRequestHandler;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEdgeRequestHandler : public Emshosting::Requesthandler::TEMSHostRequestHandler
{
	typedef Emshosting::Requesthandler::TEMSHostRequestHandler inherited;
	
protected:
	virtual bool __fastcall UserIDOfSession(const Emshosting::Requesttypes::_di_IEMSHostContext AContext, const System::UnicodeString ASessionToken, const System::UnicodeString ATenantId, /* out */ System::UnicodeString &AUserID);
	virtual bool __fastcall UserNameOfID(const Emshosting::Requesttypes::_di_IEMSHostContext AContext, const System::UnicodeString AUserID, const System::UnicodeString ATenantId, /* out */ System::UnicodeString &AUserName);
#ifndef _WIN64
	virtual System::DynamicArray<System::UnicodeString> __fastcall GetGroupsByUser(const Emshosting::Requesttypes::_di_IEMSHostContext AContext, const System::UnicodeString AUserID, const System::UnicodeString ATenantId);
#else /* _WIN64 */
	virtual System::TArray__1<System::UnicodeString> __fastcall GetGroupsByUser(const Emshosting::Requesttypes::_di_IEMSHostContext AContext, const System::UnicodeString AUserID, const System::UnicodeString ATenantId);
#endif /* _WIN64 */
	virtual void __fastcall CheckForbiddenRequest(const System::UnicodeString AResourceName, const System::UnicodeString AOriginalResourceName);
#ifndef _WIN64
	virtual void __fastcall AuthenticateRequest(const System::DynamicArray<Ems::Resourceapi::TEMSResource*> AResources, const Emshosting::Requesthandler::TEMSHostRequestProps &ARequestProps, Ems::Resourceapi::TEndpointContext::TAuthenticated &AAuthenticated);
#else /* _WIN64 */
	virtual void __fastcall AuthenticateRequest(const System::TArray__1<Ems::Resourceapi::TEMSResource*> AResources, const Emshosting::Requesthandler::TEMSHostRequestProps &ARequestProps, Ems::Resourceapi::TEndpointContext::TAuthenticated &AAuthenticated);
#endif /* _WIN64 */
	virtual void __fastcall LogEndpoint(const System::UnicodeString AResource, const System::UnicodeString AEndpointName, const System::UnicodeString AMethod, const System::UnicodeString AUserID, const System::UnicodeString ACustom, const System::UnicodeString ATenantId);
	virtual void __fastcall RedirectResource(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEMSResource* &AResource, System::UnicodeString &AEndpointName);
	virtual System::UnicodeString __fastcall GetDefaultTenantId();
	virtual bool __fastcall IsUserBelongsToTenant(const System::UnicodeString AUserId, const System::UnicodeString ATenantId);
	virtual System::UnicodeString __fastcall GetTenantNameByTenantId(const System::UnicodeString ATenantId, const Emshosting::Requesttypes::_di_IEMSHostContext AContext = Emshosting::Requesttypes::_di_IEMSHostContext());
public:
	/* TObject.Create */ inline __fastcall TEdgeRequestHandler() : Emshosting::Requesthandler::TEMSHostRequestHandler() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEdgeRequestHandler() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Edgerequesthandler */
}	/* namespace Emshosting */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING_EDGEREQUESTHANDLER)
using namespace Emshosting::Edgerequesthandler;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING)
using namespace Emshosting;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Emshosting_EdgerequesthandlerHPP
