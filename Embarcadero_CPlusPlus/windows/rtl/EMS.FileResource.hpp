// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMS.FileResource.pas' rev: 34.00 (Windows)

#ifndef Ems_FileresourceHPP
#define Ems_FileresourceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <EMS.ResourceAPI.hpp>
#include <EMS.ResourceTypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ems
{
namespace Fileresource
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEMSFileResource;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TEMSFileResource : public Ems::Resourceapi::TEMSBaseResource
{
	typedef Ems::Resourceapi::TEMSBaseResource inherited;
	
private:
	System::UnicodeString FPathTemplate;
	System::UnicodeString FDefaultFile;
	void __fastcall PutOrPost(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEndpointRequest* const ARequest, Ems::Resourceapi::TEndpointResponse* const AResponse, Ems::Resourceapi::TEMSBaseResource::TAction AAction);
	
public:
	System::UnicodeString __fastcall GetFileName(Ems::Resourceapi::TEndpointContext* const AContext);
	virtual void __fastcall List(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEndpointRequest* const ARequest, Ems::Resourceapi::TEndpointResponse* const AResponse);
	virtual void __fastcall Get(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEndpointRequest* const ARequest, Ems::Resourceapi::TEndpointResponse* const AResponse);
	virtual void __fastcall Put(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEndpointRequest* const ARequest, Ems::Resourceapi::TEndpointResponse* const AResponse);
	virtual void __fastcall Post(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEndpointRequest* const ARequest, Ems::Resourceapi::TEndpointResponse* const AResponse);
	virtual void __fastcall Delete(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEndpointRequest* const ARequest, Ems::Resourceapi::TEndpointResponse* const AResponse);
	
__published:
	__property System::UnicodeString PathTemplate = {read=FPathTemplate, write=FPathTemplate};
	__property System::UnicodeString DefaultFile = {read=FDefaultFile, write=FDefaultFile};
public:
	/* TEMSBaseResource.Create */ inline __fastcall virtual TEMSFileResource(System::Classes::TComponent* AOwner) : Ems::Resourceapi::TEMSBaseResource(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TEMSFileResource() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fileresource */
}	/* namespace Ems */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMS_FILERESOURCE)
using namespace Ems::Fileresource;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMS)
using namespace Ems;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ems_FileresourceHPP
