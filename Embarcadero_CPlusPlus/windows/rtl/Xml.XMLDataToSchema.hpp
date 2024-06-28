// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.XMLDataToSchema.pas' rev: 34.00 (Windows)

#ifndef Xml_XmldatatoschemaHPP
#define Xml_XmldatatoschemaHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Variants.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.XMLSchema.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Xmldatatoschema
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TXMLDataImporter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TXMLDataImporter : public Xml::Xmlschema::TXMLSchemaTranslator
{
	typedef Xml::Xmlschema::TXMLSchemaTranslator inherited;
	
private:
	Xml::Xmlintf::_di_IXMLDocument FXMLDoc;
	
protected:
	System::UnicodeString __fastcall AddComplexType(const Xml::Xmlintf::_di_IXMLNode Node, const System::UnicodeString NameOverride = System::UnicodeString());
	System::UnicodeString __fastcall GetDataType(const Xml::Xmlintf::_di_IXMLNode Node);
	bool __fastcall IsComplexType(const Xml::Xmlintf::_di_IXMLNode Node);
	virtual void __fastcall Translate(const System::UnicodeString FileName, const Xml::Xmlschema::_di_IXMLSchemaDef SchemaDef);
	System::UnicodeString __fastcall ValidateExistingType(const Xml::Xmlschema::_di_IXMLComplexTypeDef ExistingType, const Xml::Xmlintf::_di_IXMLNode Node);
	__property Xml::Xmlintf::_di_IXMLDocument XMLDoc = {read=FXMLDoc};
public:
	/* TObject.Create */ inline __fastcall TXMLDataImporter() : Xml::Xmlschema::TXMLSchemaTranslator() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TXMLDataImporter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define SXMLDataExtension L".xml"
}	/* namespace Xmldatatoschema */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_XMLDATATOSCHEMA)
using namespace Xml::Xmldatatoschema;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_XmldatatoschemaHPP
