// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMSHosting.APIDocResource.pas' rev: 34.00 (Windows)

#ifndef Emshosting_ApidocresourceHPP
#define Emshosting_ApidocresourceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.JSON.hpp>
#include <EMS.ResourceAPI.hpp>
#include <EMS.ResourceTypes.hpp>
#include <System.JSON.Writers.hpp>
#include <EMSHosting.APIDocConsts.hpp>

//-- user supplied -----------------------------------------------------------

namespace Emshosting
{
namespace Apidocresource
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAPIDocResource;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TAPIDocResource : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	void __fastcall GetAPIDoc(Ems::Resourcetypes::TAPIDoc* const AAPIDoc, const bool LoadJSONDefinitions, const System::UnicodeString ASegmentPath = System::UnicodeString());
	
__published:
	void __fastcall GetDoc(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEndpointRequest* const ARequest, Ems::Resourceapi::TEndpointResponse* const AResponse);
	void __fastcall GetDocYamlItem(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEndpointRequest* const ARequest, Ems::Resourceapi::TEndpointResponse* const AResponse);
	void __fastcall GetYamlDoc(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEndpointRequest* const ARequest, Ems::Resourceapi::TEndpointResponse* const AResponse);
	void __fastcall GetJSONDoc(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEndpointRequest* const ARequest, Ems::Resourceapi::TEndpointResponse* const AResponse);
public:
	/* TObject.Create */ inline __fastcall TAPIDocResource() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAPIDocResource() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define sAPIDoc L"API"
#define sAPIDocYAML L"GetAPIYAMLFormat"
#define sAPIDocJSON L"GetAPIJSONFormat"
#define sYAMLSuffix L"apidoc.yaml"
#define sJSONSuffix L"apidoc.json"
extern DELPHI_PACKAGE void __fastcall RegisterAPIDocResource(void);
}	/* namespace Apidocresource */
}	/* namespace Emshosting */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING_APIDOCRESOURCE)
using namespace Emshosting::Apidocresource;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING)
using namespace Emshosting;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Emshosting_ApidocresourceHPP
