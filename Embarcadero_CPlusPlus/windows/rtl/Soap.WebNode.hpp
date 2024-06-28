// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.WebNode.pas' rev: 34.00 (Windows)

#ifndef Soap_WebnodeHPP
#define Soap_WebnodeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Soap.IntfInfo.hpp>
#include <Soap.SOAPAttachIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Webnode
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IWebNode;
typedef System::DelphiInterface<IWebNode> _di_IWebNode;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM WebNodeOption : unsigned char { wnoSOAP12 };

typedef System::Set<WebNodeOption, WebNodeOption::wnoSOAP12, WebNodeOption::wnoSOAP12> WebNodeOptions;

__interface  INTERFACE_UUID("{77DB2644-0C12-4C0A-920E-89579DB9CC16}") IWebNode  : public System::IInterface 
{
	virtual void __fastcall Execute _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString DataMsg, System::Classes::TStream* Response) = 0 /* overload */;
	virtual void __fastcall BeforeExecute(const Soap::Intfinfo::TIntfMetaData &IntfMD, const Soap::Intfinfo::TIntfMethEntry &MethMD, int MethodIndex, Soap::Soapattachintf::_di_IMimeAttachmentHandler AttachHandler) = 0 ;
	virtual void __fastcall Execute(System::Classes::TStream* const Request, System::Classes::TStream* Response) = 0 /* overload */;
	virtual System::Classes::TStream* __fastcall Execute(System::Classes::TStream* const Request) = 0 /* overload */;
	virtual System::UnicodeString __fastcall GetMimeBoundary() = 0 ;
	virtual void __fastcall SetMimeBoundary(const System::UnicodeString Value) = 0 ;
	virtual WebNodeOptions __fastcall GetWebNodeOptions() = 0 ;
	virtual void __fastcall SetWebNodeOptions(WebNodeOptions Value) = 0 ;
	__property System::UnicodeString MimeBoundary = {read=GetMimeBoundary, write=SetMimeBoundary};
	__property WebNodeOptions Options = {read=GetWebNodeOptions, write=SetWebNodeOptions};
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Webnode */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_WEBNODE)
using namespace Soap::Webnode;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_WebnodeHPP
