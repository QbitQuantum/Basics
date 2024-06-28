// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.XMLSchema99.pas' rev: 34.00 (iOS)

#ifndef Xml_Xmlschema99HPP
#define Xml_Xmlschema99HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <Xml.XMLSchema.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.XMLIntf.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Xmlschema99
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TXMLSchema1999TranslatorFactory;
class DELPHICLASS TXMLSchema1999Translator;
class DELPHICLASS TXMLComplexTypeDef99;
class DELPHICLASS TXMLSchemaDoc99;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TXMLSchema1999TranslatorFactory : public Xml::Xmlschema::TXMLSchemaTranslatorFactory
{
	typedef Xml::Xmlschema::TXMLSchemaTranslatorFactory inherited;
	
protected:
	virtual bool __fastcall CanImportFile(const System::UnicodeString FileName);
public:
	/* TXMLSchemaTranslatorFactory.Create */ inline __fastcall TXMLSchema1999TranslatorFactory(Xml::Xmlschema::TSchemaTranslatorClass ImportClass, Xml::Xmlschema::TSchemaTranslatorClass ExportClass, const System::UnicodeString Extension, const System::UnicodeString Description) : Xml::Xmlschema::TXMLSchemaTranslatorFactory(ImportClass, ExportClass, Extension, Description) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXMLSchema1999TranslatorFactory() { }
	
};


class PASCALIMPLEMENTATION TXMLSchema1999Translator : public Xml::Xmlschema::TXMLSchemaTranslator
{
	typedef Xml::Xmlschema::TXMLSchemaTranslator inherited;
	
private:
	Xml::Xmlschema::_di_IXMLSchemaDef FOldSchema;
	
protected:
	void __fastcall CopyAttrNodes(const Xml::Xmlintf::_di_IXMLNode SourceNode, const Xml::Xmlintf::_di_IXMLNode DestNode);
	void __fastcall CopyChildNodes(const Xml::Xmlintf::_di_IXMLNode SourceNode, const Xml::Xmlintf::_di_IXMLNode DestNode);
	void __fastcall CopyComplexType(const Xml::Xmlschema::_di_IXMLComplexTypeDef ComplexTypeDef, const Xml::Xmlintf::_di_IXMLNode DestNode);
	void __fastcall CopySimpleType(const Xml::Xmlschema::_di_IXMLSimpleTypeDef SimpleTypeDef, const Xml::Xmlintf::_di_IXMLNode DestNode);
	__property Xml::Xmlschema::_di_IXMLSchemaDef OldSchema = {read=FOldSchema};
	
public:
	virtual void __fastcall Translate(const System::UnicodeString FileName, const Xml::Xmlschema::_di_IXMLSchemaDef SchemaDef);
public:
	/* TObject.Create */ inline __fastcall TXMLSchema1999Translator() : Xml::Xmlschema::TXMLSchemaTranslator() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TXMLSchema1999Translator() { }
	
};


class PASCALIMPLEMENTATION TXMLComplexTypeDef99 : public Xml::Xmlschema::TXMLComplexTypeDef
{
	typedef Xml::Xmlschema::TXMLComplexTypeDef inherited;
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLComplexTypeDef99(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmlschema::TXMLComplexTypeDef(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLComplexTypeDef99(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmlschema::TXMLComplexTypeDef(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLComplexTypeDef99() { }
	
};


class PASCALIMPLEMENTATION TXMLSchemaDoc99 : public Xml::Xmlschema::TXMLSchemaDoc
{
	typedef Xml::Xmlschema::TXMLSchemaDoc inherited;
	
protected:
	virtual Xml::Xmldoc::TXMLNodeClass __fastcall GetChildNodeClass(const Xml::Xmldom::_di_IDOMNode Node);
	virtual void __fastcall CheckSchemaVersion();
	DYNAMIC void __fastcall LoadData();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLDocument.Create */ inline __fastcall virtual TXMLSchemaDoc99(System::Classes::TComponent* AOwner)/* overload */ : Xml::Xmlschema::TXMLSchemaDoc(AOwner) { }
	/* TXMLDocument.Create */ inline __fastcall TXMLSchemaDoc99(const System::UnicodeString AFileName)/* overload */ : Xml::Xmlschema::TXMLSchemaDoc(AFileName) { }
	/* TXMLDocument.Destroy */ inline __fastcall virtual ~TXMLSchemaDoc99() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Xmlschema99 */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_XMLSCHEMA99)
using namespace Xml::Xmlschema99;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_Xmlschema99HPP
