// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.SOAPEnv.pas' rev: 34.00 (Android)

#ifndef Soap_SoapenvHPP
#define Soap_SoapenvHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Soap.OPConvert.hpp>
#include <Xml.XMLIntf.hpp>
#include <Soap.OpConvertOptions.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Soapenv
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSoapEnvelope;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TSoapEnvelope : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	Xml::Xmlintf::_di_IXMLNode __fastcall MakeEnvelope(Xml::Xmlintf::_di_IXMLDocument Doc, Soap::Opconvertoptions::TSOAPConvertOptions Options);
	Xml::Xmlintf::_di_IXMLNode __fastcall MakeHeader(Xml::Xmlintf::_di_IXMLNode ParentNode, Soap::Opconvertoptions::TSOAPConvertOptions Options);
	Xml::Xmlintf::_di_IXMLNode __fastcall MakeBody(Xml::Xmlintf::_di_IXMLNode ParentNode, Soap::Opconvertoptions::TSOAPConvertOptions Options);
	Xml::Xmlintf::_di_IXMLNode __fastcall MakeFault(Xml::Xmlintf::_di_IXMLNode ParentNode, Soap::Opconvertoptions::TSOAPConvertOptions Options);
public:
	/* TObject.Create */ inline __fastcall TSoapEnvelope() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSoapEnvelope() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Soapenv */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_SOAPENV)
using namespace Soap::Soapenv;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_SoapenvHPP
