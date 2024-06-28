// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMSHosting.Helpers.pas' rev: 34.00 (Windows)

#ifndef Emshosting_HelpersHPP
#define Emshosting_HelpersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.JSON.hpp>
#include <EMS.ResourceAPI.hpp>
#include <EMS.Services.hpp>
#include <EMS.ResourceTypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Emshosting
{
namespace Helpers
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEndpointHelpers;
class DELPHICLASS TLogHelpers;
class DELPHICLASS TErrorHelpers;
struct TLogCategoryNames;
struct TLogErrorTypes;
struct TLogObjectNames;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointHelpers : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TCreatorIDs
	{
	public:
		#define TEndpointHelpers_TCreatorIDs_Master L"00000000-0000-0000-0000-000000000001"
		
		#define TEndpointHelpers_TCreatorIDs_Null L"00000000-0000-0000-0000-000000000000"
		
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
	
public:
	__classmethod System::UnicodeString __fastcall IdentityFromContext(Ems::Resourceapi::TEndpointContext* const AContext);
	__classmethod bool __fastcall CreatorRequired(Ems::Resourceapi::TEndpointContext* const AContext);
	__classmethod void __fastcall SetCreatorRequired(Ems::Resourceapi::TEndpointContext* const AContext);
	__classmethod void __fastcall CheckCreator(Ems::Resourceapi::TEndpointContext* const AContext, const System::DelphiInterface<System::Sysutils::TFunc__1<System::UnicodeString> > AGetCreator)/* overload */;
	__classmethod void __fastcall CheckCreator(Ems::Resourceapi::TEndpointContext* const AContext, const System::UnicodeString ACreator)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TEndpointHelpers() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEndpointHelpers() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TLogHelpers : public System::TObject
{
	typedef System::TObject inherited;
	
	
protected:
	__interface DELPHIINTERFACE TLogCallback;
	typedef System::DelphiInterface<TLogCallback> _di_TLogCallback;
	__interface TLogCallback  : public System::IInterface 
	{
		virtual void __fastcall Invoke(System::Json::TJSONObject* const AJSON) = 0 ;
	};
	
	
private:
	static bool __fastcall GetLoggingEnabled();
	static Ems::Services::_di_IEMSLoggingService __fastcall GetService();
	
protected:
	__classmethod void __fastcall DoLog(const System::UnicodeString ACategory, const _di_TLogCallback ACallback);
	
public:
	__classmethod void __fastcall LogSetupCustomOutput(const System::DelphiInterface<System::Sysutils::TFunc__1<bool> > AEnabled, const Ems::Services::_di_TEMSLoggingOutputProc AOutput, const bool ASynchronize);
	__classmethod void __fastcall LogSetupFileOutput(const System::UnicodeString AFileName, const bool AAppend);
	static void __fastcall LogRequest(const System::UnicodeString AResourceName, const System::UnicodeString AEndpointName, const System::UnicodeString AMethod, const System::UnicodeString AUserID);
	static void __fastcall LogRedirect(const System::UnicodeString AResourceName, const System::UnicodeString AEndpointName, const System::UnicodeString ADestinationResourceName, const System::UnicodeString ADestinationEndpointName);
	__classmethod void __fastcall LogHTTPError(int ACode, const System::UnicodeString AReason, const System::UnicodeString AError, const System::UnicodeString ADescription);
	__classmethod void __fastcall LogException(System::Sysutils::Exception* const AException);
	__classmethod void __fastcall LogPackageException(const System::UnicodeString AFileName, System::Sysutils::Exception* const AException);
	static void __fastcall LogPackageLoading(const System::UnicodeString AFileName);
	static void __fastcall LogPackageLoaded(const System::UnicodeString AFileName);
	__classmethod void __fastcall LogRegisterResource(Ems::Resourceapi::TEMSResource* const AResource);
	static void __fastcall LogRegisterACL(const System::UnicodeString AName, const System::UnicodeString AValue);
	static void __fastcall LogRegisterRedirect(const System::UnicodeString AName, const System::UnicodeString AValue);
	static void __fastcall LogConfigurationLoaded(const System::UnicodeString AFileName, bool AFileExists);
	static void __fastcall LogMessage(const System::UnicodeString AMessage);
	static System::UnicodeString __fastcall Format(System::Json::TJSONObject* const AJSON);
	/* static */ __property bool LoggingEnabled = {read=GetLoggingEnabled, nodefault};
public:
	/* TObject.Create */ inline __fastcall TLogHelpers() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TLogHelpers() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TErrorHelpers : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static System::Json::TJSONObject* __fastcall CreateJSONError(const System::UnicodeString AReasonString, const System::UnicodeString AError, const System::UnicodeString ADescription);
public:
	/* TObject.Create */ inline __fastcall TErrorHelpers() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TErrorHelpers() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

struct DECLSPEC_DRECORD TLogCategoryNames
{
public:
	#define TLogCategoryNames_Request L"Request"
	
	#define TLogCategoryNames_Redirect L"Redirect"
	
	#define TLogCategoryNames_Error L"Error"
	
	#define TLogCategoryNames_Loading L"Loading"
	
	#define TLogCategoryNames_Loaded L"Loaded"
	
	#define TLogCategoryNames_Push L"Push"
	
	#define TLogCategoryNames_RegisterUnit L"RegUnit"
	
	#define TLogCategoryNames_RegisterResource L"RegResource"
	
	#define TLogCategoryNames_RegisterACL L"RegACL"
	
	#define TLogCategoryNames_RegisterRedirect L"RegRedirect"
	
	#define TLogCategoryNames_ConfigLoaded L"ConfigLoaded"
	
	#define TLogCategoryNames_DBConnection L"DBConnection"
	
	#define TLogCategoryNames_Licensing L"Licensing"
	
	#define TLogCategoryNames_TraceMessage L"Trace"
	
	#define TLogCategoryNames_PublicPath L"PublicPath"
	
};


struct DECLSPEC_DRECORD TLogErrorTypes
{
public:
	#define TLogErrorTypes_HTTP L"HTTP"
	
	#define TLogErrorTypes_Other L"Other"
	
	#define TLogErrorTypes_Package L"Package"
	
};


struct DECLSPEC_DRECORD TLogObjectNames
{
public:
	#define TLogObjectNames_Application L"Application"
	
	#define TLogObjectNames_Started L"Started"
	
	#define TLogObjectNames_Log L"Log"
	
	#define TLogObjectNames_Thread L"Thread"
	
	#define TLogObjectNames_Resource L"Resource"
	
	#define TLogObjectNames_Endpoint L"Endpoint"
	
	#define TLogObjectNames_DestinationResource L"DestinationResource"
	
	#define TLogObjectNames_DestinationEndpoint L"DestinationEndpoint"
	
	#define TLogObjectNames_Endpoints L"Endpoints"
	
	#define TLogObjectNames_Method L"Method"
	
	#define TLogObjectNames_UserID L"User"
	
	#define TLogObjectNames_Time L"Time"
	
	#define TLogObjectNames_Redirect L"Redirect"
	
	#define TLogObjectNames_Push L"Push"
	
	#define TLogObjectNames_Code L"Code"
	
	#define TLogObjectNames_Reason L"Reason"
	
	#define TLogObjectNames_Error L"Error"
	
	#define TLogObjectNames_Description L"Description"
	
	#define TLogObjectNames_FileName L"Filename"
	
	#define TLogObjectNames_FileExists L"Exists"
	
	#define TLogObjectNames_UnitName L"Unitname"
	
	#define TLogObjectNames_ExceptionClass L"Exception"
	
	#define TLogObjectNames_ExceptionMessage L"Message"
	
	#define TLogObjectNames_TraceMessage L"Message"
	
	#define TLogObjectNames_ErrorType L"Type"
	
	#define TLogObjectNames_DBInstanceName L"InstanceName"
	
	#define TLogObjectNames_DBFileName L"Filename"
	
	#define TLogObjectNames_Licensed L"Licensed"
	
	#define TLogObjectNames_LicensedMaxUsers L"LicensedMaxUsers"
	
	#define TLogObjectNames_DefaultMaxUsers L"DefaultMaxUsers"
	
	#define TLogObjectNames_PublicDirectory L"PublicDirectory"
	
	#define TLogObjectNames_LogicalPath L"LogicalPath"
	
	#define TLogObjectNames_DefaultFile L"DefaultFile"
	
	#define TLogObjectNames_Mimes L"Mimes"
	
	#define TLogObjectNames_Extensions L"Extensions"
	
	#define TLogObjectNames_Charset L"Charset"
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Helpers */
}	/* namespace Emshosting */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING_HELPERS)
using namespace Emshosting::Helpers;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING)
using namespace Emshosting;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Emshosting_HelpersHPP
