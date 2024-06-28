// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.XDRSchema.pas' rev: 34.00 (Android)

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
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define XDRExtension u".xdr"
#define XDR_DataTypes u"urn:w3-org:xmldatatypes"
#define XDR_Schema u"urn:w3-org:xmlschema"
#define MSXDR_DataTypes u"urn:schemas-microsoft-com:datatypes"
#define MSXDR_Schema u"urn:schemas-microsoft-com:xml-data"
#define xdrElementType u"ElementType"
#define xdrAttributeType u"AttributeType"
#define xdrDescription u"Description"
#define xdrElement u"element"
#define xdrAttribute u"attribute"
#define xdrGroup u"group"
#define xdrExtends u"extends"
#define xdrName u"name"
#define xdrType u"type"
#define xdrContent u"content"
#define xdrContent_default u"mixed"
#define xdrMixed u"mixed"
#define xdrEmpty u"empty"
#define xdrTextOnly u"textOnly"
#define xdrEltOnly u"eltOnly"
#define xdrModel u"model"
#define xdrOpen u"open"
#define xdrClosed u"closed"
#define xdrOrder u"order"
#define xdrSeq u"seq"
#define xdrOne u"one"
#define xdrAll u"all"
#define xdrMany u"many"
#define xdrRequired u"required"
#define xdrRequired_default u"no"
#define xdrYes u"yes"
#define xdrNo u"no"
#define xdrDefault u"default"
#define xdrOccurs u"occurs"
#define xdrMinOccurs u"minOccurs"
#define xdrMaxOccurs u"maxOccurs"
#define xdrOptional u"optional"
#define xdrOneOrMore u"oneOrMore"
#define xdrZeroOrMore u"zeroOrMore"
#define xdrDatatype u"datatype"
#define xdrMaxLength u"maxLength"
#define xdrValues u"values"
#define xdrMax u"max"
#define xdrMin u"min"
#define xdrMinExclusive u"minExclusive"
#define xdrMaxExclusive u"maxExclusive"
#define xdrString u"string"
#define xdrId u"id"
#define xdrIdref u"idref"
#define xdrIdrefs u"idrefs"
#define xdrEntity u"entity"
#define xdrEntities u"entities"
#define xdrNmtoken u"nmtoken"
#define xdrNmtokens u"nmtokens"
#define xdrNumber u"number"
#define xdrInt u"int"
#define xdrEnumeration u"enumeration"
#define xdrNotation u"notation"
#define xdrFixed u"fixed"
#define xdrBoolean u"boolean"
#define xdrDateTime u"dateTime"
#define xdrDateTimeTz u"dateTime.tz"
#define xdrDate u"date"
#define xdrTime u"time"
#define xdrTimetz u"time.tz"
#define xdrI1 u"i1"
#define xdrByte u"byte"
#define xdrI2 u"i2"
#define xdrI4 u"i4"
#define xdrI8 u"i8"
#define xdrUi1 u"ui1"
#define xdrUi2 u"ui2"
#define xdrUi4 u"ui4"
#define xdrUi8 u"ui8"
#define xdrR4 u"r4"
#define xdrR8 u"r8"
#define xdrFloat u"float"
#define xdrChar u"char"
#define xdrUuid u"uuid"
#define xdrBinhex u"bin.hex"
#define xdrBinbase64 u"bin.base64"
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
