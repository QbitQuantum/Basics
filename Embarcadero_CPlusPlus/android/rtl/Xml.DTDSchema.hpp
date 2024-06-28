// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.DTDSchema.pas' rev: 34.00 (Android)

#ifndef Xml_DtdschemaHPP
#define Xml_DtdschemaHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Xml.XMLSchema.hpp>
#include <Xml.xmldom.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Dtdschema
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDTDBaseTranslator;
class DELPHICLASS TDTDImportTranslator;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDTDBaseTranslator : public Xml::Xmlschema::TXMLSchemaTranslator
{
	typedef Xml::Xmlschema::TXMLSchemaTranslator inherited;
	
private:
	System::Classes::TStrings* FDTDLines;
	
protected:
	__property System::Classes::TStrings* DTDLines = {read=FDTDLines};
	
public:
	__fastcall virtual ~TDTDBaseTranslator();
	virtual void __fastcall AfterConstruction();
public:
	/* TObject.Create */ inline __fastcall TDTDBaseTranslator() : Xml::Xmlschema::TXMLSchemaTranslator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDTDImportTranslator : public TDTDBaseTranslator
{
	typedef TDTDBaseTranslator inherited;
	
protected:
	System::UnicodeString __fastcall Expand(System::UnicodeString Dtd, System::UnicodeString &RootName, System::UnicodeString SrcPath);
	void __fastcall ExtractDtdParts(System::UnicodeString Str, System::UnicodeString StrBeg, System::UnicodeString StrEnd, System::Classes::TStrings* Parts);
	void __fastcall Parse(System::UnicodeString Dtd);
	void __fastcall ParseAttributeDefinitions(System::Classes::TStrings* AttributeList);
	void __fastcall ParseAttributeDefinition(System::UnicodeString AttrStr);
	void __fastcall ParseChildElements(Xml::Xmlschema::_di_IXMLComplexTypeDef ComplexDef, Xml::Xmlschema::_di_IXMLElementCompositors ParentCompositors, System::UnicodeString &Str);
	void __fastcall ParseElementDefinitions(System::Classes::TStrings* ElementList, System::Classes::TStrings* ElementsWithAttributes);
	void __fastcall ParseTokens(System::UnicodeString Str, System::Classes::TStrings* Tokens);
	System::UnicodeString __fastcall PreParseChildElements(System::UnicodeString Str, System::UnicodeString &Suffix, System::UnicodeString &GroupType);
	void __fastcall PreparseAttributeDefinitions(System::Classes::TStrings* AttributeList, System::Classes::TStrings* AttrDefs);
	virtual void __fastcall Translate(const System::UnicodeString FileName, const Xml::Xmlschema::_di_IXMLSchemaDef SchemaDef);
public:
	/* TDTDBaseTranslator.Destroy */ inline __fastcall virtual ~TDTDImportTranslator() { }
	
public:
	/* TObject.Create */ inline __fastcall TDTDImportTranslator() : TDTDBaseTranslator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define DTDExtension u".dtd"
}	/* namespace Dtdschema */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_DTDSCHEMA)
using namespace Xml::Dtdschema;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_DtdschemaHPP
