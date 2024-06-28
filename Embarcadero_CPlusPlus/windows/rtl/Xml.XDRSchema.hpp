// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.XDRSchema.pas' rev: 34.00 (Windows)

#ifndef Xml_XdrschemaHPP
#define Xml_XdrschemaHPP

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
#include <Xml.XMLDoc.hpp>
#include <Xml.XMLIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Xdrschema
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TXDRImportTranslator;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TXDRImportTranslator : public Xml::Xmlschema::TXMLSchemaTranslator
{
	typedef Xml::Xmlschema::TXMLSchemaTranslator inherited;
	
protected:
	Xml::Xmlintf::_di_IXMLDocument XDRDoc;
	System::UnicodeString SchemaPrefix;
	System::UnicodeString DataTypePrefix;
	System::UnicodeString ns;
	void __fastcall AddAttribute(Xml::Xmldom::_di_IDOMNode XdrAttributedef, Xml::Xmlschema::_di_IXMLAttributeDefs XsdAttributeDefs);
	void __fastcall AddChildElement(Xml::Xmldom::_di_IDOMNode XdrElement, Xml::Xmlschema::_di_IXMLElementDefs XsdElementDefs, System::UnicodeString Order);
	void __fastcall AddExtends(Xml::Xmldom::_di_IDOMNode Extends, Xml::Xmlschema::_di_IXMLElementDefs XsdElementDefs, System::UnicodeString Order);
	void __fastcall Parse(Xml::Xmldom::_di_IDOMDocument XdrDom);
	void __fastcall ParseAttributeDefinition(System::UnicodeString Parent, Xml::Xmldom::_di_IDOMNode XdrAttributeDef, Xml::Xmlschema::_di_IXMLAttributeDefs XsdAttributeDefs);
	void __fastcall ParseElementDefinition(System::UnicodeString Parent, Xml::Xmldom::_di_IDOMNode XdrElementDef, Xml::Xmlschema::_di_IXMLElementDefs XsdElementDefs);
	void __fastcall ParseGroup(Xml::Xmldom::_di_IDOMNode Group, Xml::Xmlschema::_di_IXMLElementCompositors XsdElementCompositors);
	virtual void __fastcall Translate(const System::UnicodeString FileName, const Xml::Xmlschema::_di_IXMLSchemaDef SchemaDef);
public:
	/* TObject.Create */ inline __fastcall TXDRImportTranslator() : Xml::Xmlschema::TXMLSchemaTranslator() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TXDRImportTranslator() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define XDRExtension L".xdr"
#define XDR_DataTypes L"urn:w3-org:xmldatatypes"
#define XDR_Schema L"urn:w3-org:xmlschema"
#define MSXDR_DataTypes L"urn:schemas-microsoft-com:datatypes"
#define MSXDR_Schema L"urn:schemas-microsoft-com:xml-data"
#define xdrElementType L"ElementType"
#define xdrAttributeType L"AttributeType"
#define xdrDescription L"Description"
#define xdrElement L"element"
#define xdrAttribute L"attribute"
#define xdrGroup L"group"
#define xdrExtends L"extends"
#define xdrName L"name"
#define xdrType L"type"
#define xdrContent L"content"
#define xdrContent_default L"mixed"
#define xdrMixed L"mixed"
#define xdrEmpty L"empty"
#define xdrTextOnly L"textOnly"
#define xdrEltOnly L"eltOnly"
#define xdrModel L"model"
#define xdrOpen L"open"
#define xdrClosed L"closed"
#define xdrOrder L"order"
#define xdrSeq L"seq"
#define xdrOne L"one"
#define xdrAll L"all"
#define xdrMany L"many"
#define xdrRequired L"required"
#define xdrRequired_default L"no"
#define xdrYes L"yes"
#define xdrNo L"no"
#define xdrDefault L"default"
#define xdrOccurs L"occurs"
#define xdrMinOccurs L"minOccurs"
#define xdrMaxOccurs L"maxOccurs"
#define xdrOptional L"optional"
#define xdrOneOrMore L"oneOrMore"
#define xdrZeroOrMore L"zeroOrMore"
#define xdrDatatype L"datatype"
#define xdrMaxLength L"maxLength"
#define xdrValues L"values"
#define xdrMax L"max"
#define xdrMin L"min"
#define xdrMinExclusive L"minExclusive"
#define xdrMaxExclusive L"maxExclusive"
#define xdrString L"string"
#define xdrId L"id"
#define xdrIdref L"idref"
#define xdrIdrefs L"idrefs"
#define xdrEntity L"entity"
#define xdrEntities L"entities"
#define xdrNmtoken L"nmtoken"
#define xdrNmtokens L"nmtokens"
#define xdrNumber L"number"
#define xdrInt L"int"
#define xdrEnumeration L"enumeration"
#define xdrNotation L"notation"
#define xdrFixed L"fixed"
#define xdrBoolean L"boolean"
#define xdrDateTime L"dateTime"
#define xdrDateTimeTz L"dateTime.tz"
#define xdrDate L"date"
#define xdrTime L"time"
#define xdrTimetz L"time.tz"
#define xdrI1 L"i1"
#define xdrByte L"byte"
#define xdrI2 L"i2"
#define xdrI4 L"i4"
#define xdrI8 L"i8"
#define xdrUi1 L"ui1"
#define xdrUi2 L"ui2"
#define xdrUi4 L"ui4"
#define xdrUi8 L"ui8"
#define xdrR4 L"r4"
#define xdrR8 L"r8"
#define xdrFloat L"float"
#define xdrChar L"char"
#define xdrUuid L"uuid"
#define xdrBinhex L"bin.hex"
#define xdrBinbase64 L"bin.base64"
}	/* namespace Xdrschema */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_XDRSCHEMA)
using namespace Xml::Xdrschema;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_XdrschemaHPP
