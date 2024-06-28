// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.XMLSchema.pas' rev: 34.00 (Android)

#ifndef Xml_XmlschemaHPP
#define Xml_XmlschemaHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Variants.hpp>
#include <System.Classes.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.XMLIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Xmlschema
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ESchemaError;
class DELPHICLASS ESchemaValidation;
class DELPHICLASS ESchemaParse;
__interface DELPHIINTERFACE IXMLElementDefList;
typedef System::DelphiInterface<IXMLElementDefList> _di_IXMLElementDefList;
__interface DELPHIINTERFACE IXMLAttributeDefList;
typedef System::DelphiInterface<IXMLAttributeDefList> _di_IXMLAttributeDefList;
__interface DELPHIINTERFACE IXMLSchemaNode;
typedef System::DelphiInterface<IXMLSchemaNode> _di_IXMLSchemaNode;
__interface DELPHIINTERFACE IXMLAnnotatedItem;
typedef System::DelphiInterface<IXMLAnnotatedItem> _di_IXMLAnnotatedItem;
__interface DELPHIINTERFACE IXMLSchemaDocRef;
typedef System::DelphiInterface<IXMLSchemaDocRef> _di_IXMLSchemaDocRef;
__interface DELPHIINTERFACE IXMLSchemaImport;
typedef System::DelphiInterface<IXMLSchemaImport> _di_IXMLSchemaImport;
__interface DELPHIINTERFACE IXMLSchemaInclude;
typedef System::DelphiInterface<IXMLSchemaInclude> _di_IXMLSchemaInclude;
__interface DELPHIINTERFACE IXMLSchemaItem;
typedef System::DelphiInterface<IXMLSchemaItem> _di_IXMLSchemaItem;
__interface DELPHIINTERFACE IXMLTypeDef;
typedef System::DelphiInterface<IXMLTypeDef> _di_IXMLTypeDef;
__interface DELPHIINTERFACE IXMLSimpleContent;
typedef System::DelphiInterface<IXMLSimpleContent> _di_IXMLSimpleContent;
__interface DELPHIINTERFACE IXMLSimpleTypeRestriction;
typedef System::DelphiInterface<IXMLSimpleTypeRestriction> _di_IXMLSimpleTypeRestriction;
__interface DELPHIINTERFACE IXMLSimpleTypeList;
typedef System::DelphiInterface<IXMLSimpleTypeList> _di_IXMLSimpleTypeList;
__interface DELPHIINTERFACE IXMLSimpleTypeUnion;
typedef System::DelphiInterface<IXMLSimpleTypeUnion> _di_IXMLSimpleTypeUnion;
__interface DELPHIINTERFACE IXMLSimpleTypeDef;
typedef System::DelphiInterface<IXMLSimpleTypeDef> _di_IXMLSimpleTypeDef;
__interface DELPHIINTERFACE IXMLBaseTypeIndicator;
typedef System::DelphiInterface<IXMLBaseTypeIndicator> _di_IXMLBaseTypeIndicator;
__interface DELPHIINTERFACE IXMLComplexTypeDef;
typedef System::DelphiInterface<IXMLComplexTypeDef> _di_IXMLComplexTypeDef;
__interface DELPHIINTERFACE IXMLSchemaRefItem;
typedef System::DelphiInterface<IXMLSchemaRefItem> _di_IXMLSchemaRefItem;
__interface DELPHIINTERFACE IXMLTypedSchemaItem;
typedef System::DelphiInterface<IXMLTypedSchemaItem> _di_IXMLTypedSchemaItem;
__interface DELPHIINTERFACE IXMLAttributeDef;
typedef System::DelphiInterface<IXMLAttributeDef> _di_IXMLAttributeDef;
__interface DELPHIINTERFACE IXMLElementDef;
typedef System::DelphiInterface<IXMLElementDef> _di_IXMLElementDef;
__interface DELPHIINTERFACE IXMLElementCompositor;
typedef System::DelphiInterface<IXMLElementCompositor> _di_IXMLElementCompositor;
__interface DELPHIINTERFACE IXMLAttributeGroup;
typedef System::DelphiInterface<IXMLAttributeGroup> _di_IXMLAttributeGroup;
__interface DELPHIINTERFACE IXMLElementGroup;
typedef System::DelphiInterface<IXMLElementGroup> _di_IXMLElementGroup;
__interface DELPHIINTERFACE IXMLNotation;
typedef System::DelphiInterface<IXMLNotation> _di_IXMLNotation;
__interface DELPHIINTERFACE IXMLAnnotation;
typedef System::DelphiInterface<IXMLAnnotation> _di_IXMLAnnotation;
__interface DELPHIINTERFACE IXMLAppInfo;
typedef System::DelphiInterface<IXMLAppInfo> _di_IXMLAppInfo;
__interface DELPHIINTERFACE IXMLDocumentation;
typedef System::DelphiInterface<IXMLDocumentation> _di_IXMLDocumentation;
__interface DELPHIINTERFACE IXMLEnumeration;
typedef System::DelphiInterface<IXMLEnumeration> _di_IXMLEnumeration;
__interface DELPHIINTERFACE IXMLSchemaDocRefs;
typedef System::DelphiInterface<IXMLSchemaDocRefs> _di_IXMLSchemaDocRefs;
__interface DELPHIINTERFACE IXMLSchemaImports;
typedef System::DelphiInterface<IXMLSchemaImports> _di_IXMLSchemaImports;
__interface DELPHIINTERFACE IXMLSchemaIncludes;
typedef System::DelphiInterface<IXMLSchemaIncludes> _di_IXMLSchemaIncludes;
__interface DELPHIINTERFACE IXMLSchemaItems;
typedef System::DelphiInterface<IXMLSchemaItems> _di_IXMLSchemaItems;
__interface DELPHIINTERFACE IXMLSimpleTypeDefs;
typedef System::DelphiInterface<IXMLSimpleTypeDefs> _di_IXMLSimpleTypeDefs;
__interface DELPHIINTERFACE IXMLComplexTypeDefs;
typedef System::DelphiInterface<IXMLComplexTypeDefs> _di_IXMLComplexTypeDefs;
__interface DELPHIINTERFACE IXMLAttributeDefs;
typedef System::DelphiInterface<IXMLAttributeDefs> _di_IXMLAttributeDefs;
__interface DELPHIINTERFACE IXMLElementDefs;
typedef System::DelphiInterface<IXMLElementDefs> _di_IXMLElementDefs;
__interface DELPHIINTERFACE IXMLAttributeGroups;
typedef System::DelphiInterface<IXMLAttributeGroups> _di_IXMLAttributeGroups;
__interface DELPHIINTERFACE IXMLElementGroups;
typedef System::DelphiInterface<IXMLElementGroups> _di_IXMLElementGroups;
__interface DELPHIINTERFACE IXMLElementCompositors;
typedef System::DelphiInterface<IXMLElementCompositors> _di_IXMLElementCompositors;
__interface DELPHIINTERFACE IXMLNotationDefs;
typedef System::DelphiInterface<IXMLNotationDefs> _di_IXMLNotationDefs;
__interface DELPHIINTERFACE IXMLAnnotationItems;
typedef System::DelphiInterface<IXMLAnnotationItems> _di_IXMLAnnotationItems;
__interface DELPHIINTERFACE IXMLAppInfoCollection;
typedef System::DelphiInterface<IXMLAppInfoCollection> _di_IXMLAppInfoCollection;
__interface DELPHIINTERFACE IXMLDocumentationCollection;
typedef System::DelphiInterface<IXMLDocumentationCollection> _di_IXMLDocumentationCollection;
__interface DELPHIINTERFACE IXMLEnumerationCollection;
typedef System::DelphiInterface<IXMLEnumerationCollection> _di_IXMLEnumerationCollection;
__interface DELPHIINTERFACE IXMLSchemaDef;
typedef System::DelphiInterface<IXMLSchemaDef> _di_IXMLSchemaDef;
__interface DELPHIINTERFACE IXMLSchemaDoc;
typedef System::DelphiInterface<IXMLSchemaDoc> _di_IXMLSchemaDoc;
__interface DELPHIINTERFACE IXMLSchemaTranslator;
typedef System::DelphiInterface<IXMLSchemaTranslator> _di_IXMLSchemaTranslator;
__interface DELPHIINTERFACE IXMLSchemaTranslatorFactory;
typedef System::DelphiInterface<IXMLSchemaTranslatorFactory> _di_IXMLSchemaTranslatorFactory;
class DELPHICLASS TXMLAttributeDefList;
class DELPHICLASS TXMLElementDefList;
class DELPHICLASS TXMLSchemaNode;
class DELPHICLASS TXMLSchemaItem;
class DELPHICLASS TXMLSchemaDocRef;
class DELPHICLASS TXMLSchemaImport;
class DELPHICLASS TXMLSchemaInclude;
class DELPHICLASS TXMLTypeDef;
class DELPHICLASS TXMLSimpleTypeContent;
class DELPHICLASS TXMLSimpleTypeRestriction;
class DELPHICLASS TXMLSimpleTypeList;
class DELPHICLASS TXMLSimpleTypeUnion;
class DELPHICLASS TXMLSimpleTypeDef;
__interface DELPHIINTERFACE IXMLComplexContent;
typedef System::DelphiInterface<IXMLComplexContent> _di_IXMLComplexContent;
class DELPHICLASS TXMLComplexContent;
class DELPHICLASS TXMLBaseTypeIndicator;
class DELPHICLASS TXMLComplexTypeDef;
class DELPHICLASS TXMLTypedSchemaItem;
class DELPHICLASS TXMLAttributeDef;
class DELPHICLASS TXMLElementDef;
class DELPHICLASS TXMLElementCompositor;
class DELPHICLASS TXMLAttributeGroup;
class DELPHICLASS TXMLElementGroup;
class DELPHICLASS TXMLNotationDef;
class DELPHICLASS TXMLAnnotationItem;
class DELPHICLASS TXMLAnnotation;
class DELPHICLASS TXMLEnumeration;
class DELPHICLASS TXMLSchemaDocRefs;
class DELPHICLASS TXMLSchemaImports;
class DELPHICLASS TXMLSchemaIncludes;
class DELPHICLASS TXMLSchemaItems;
class DELPHICLASS TXMLSimpleTypeDefs;
class DELPHICLASS TXMLBuiltInTypes;
class DELPHICLASS TXMLComplexTypeDefs;
class DELPHICLASS TXMLAttributeDefs;
class DELPHICLASS TXMLElementDefs;
class DELPHICLASS TXMLElementCompositors;
class DELPHICLASS TXMLAttributeGroups;
class DELPHICLASS TXMLElementGroups;
class DELPHICLASS TXMLNotationDefs;
class DELPHICLASS TXMLAnnotationCollection;
class DELPHICLASS TXMLAppInfoCollection;
class DELPHICLASS TXMLDocumentationCollection;
class DELPHICLASS TXMLEnumerationCollection;
struct TAppInfoClassInfo;
class DELPHICLASS TXMLSchemaDef;
class DELPHICLASS TXMLSchemaDoc;
class DELPHICLASS TXMLSchemaTranslator;
class DELPHICLASS TXMLSchemaTranslatorFactory;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ESchemaError : public Xml::Xmlintf::EXMLDocError
{
	typedef Xml::Xmlintf::EXMLDocError inherited;
	
public:
	/* Exception.Create */ inline __fastcall ESchemaError(const System::UnicodeString Msg) : Xml::Xmlintf::EXMLDocError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESchemaError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Xml::Xmlintf::EXMLDocError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESchemaError(NativeUInt Ident)/* overload */ : Xml::Xmlintf::EXMLDocError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESchemaError(System::PResStringRec ResStringRec)/* overload */ : Xml::Xmlintf::EXMLDocError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESchemaError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Xml::Xmlintf::EXMLDocError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESchemaError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Xml::Xmlintf::EXMLDocError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESchemaError(const System::UnicodeString Msg, int AHelpContext) : Xml::Xmlintf::EXMLDocError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESchemaError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Xml::Xmlintf::EXMLDocError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESchemaError(NativeUInt Ident, int AHelpContext)/* overload */ : Xml::Xmlintf::EXMLDocError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESchemaError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Xml::Xmlintf::EXMLDocError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESchemaError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Xml::Xmlintf::EXMLDocError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESchemaError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Xml::Xmlintf::EXMLDocError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESchemaError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ESchemaValidation : public ESchemaError
{
	typedef ESchemaError inherited;
	
public:
	/* Exception.Create */ inline __fastcall ESchemaValidation(const System::UnicodeString Msg) : ESchemaError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESchemaValidation(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ESchemaError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESchemaValidation(NativeUInt Ident)/* overload */ : ESchemaError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESchemaValidation(System::PResStringRec ResStringRec)/* overload */ : ESchemaError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESchemaValidation(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ESchemaError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESchemaValidation(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ESchemaError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESchemaValidation(const System::UnicodeString Msg, int AHelpContext) : ESchemaError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESchemaValidation(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ESchemaError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESchemaValidation(NativeUInt Ident, int AHelpContext)/* overload */ : ESchemaError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESchemaValidation(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ESchemaError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESchemaValidation(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESchemaError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESchemaValidation(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESchemaError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESchemaValidation() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ESchemaParse : public ESchemaError
{
	typedef ESchemaError inherited;
	
public:
	/* Exception.Create */ inline __fastcall ESchemaParse(const System::UnicodeString Msg) : ESchemaError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESchemaParse(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ESchemaError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESchemaParse(NativeUInt Ident)/* overload */ : ESchemaError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESchemaParse(System::PResStringRec ResStringRec)/* overload */ : ESchemaError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESchemaParse(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ESchemaError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESchemaParse(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ESchemaError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESchemaParse(const System::UnicodeString Msg, int AHelpContext) : ESchemaError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESchemaParse(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ESchemaError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESchemaParse(NativeUInt Ident, int AHelpContext)/* overload */ : ESchemaError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESchemaParse(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ESchemaError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESchemaParse(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESchemaError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESchemaParse(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESchemaError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESchemaParse() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TFormChoice : unsigned char { fcQualified, fcUnqualified };

enum DECLSPEC_DENUM TCompositorType : unsigned char { ctAll, ctChoice, ctSequence };

enum DECLSPEC_DENUM TContentModel : unsigned char { cmALL, cmChoice, cmSequence, cmGroupRef, cmEmpty };

enum DECLSPEC_DENUM TDerivationMethod : unsigned char { dmNone, dmComplexExtension, dmComplexRestriction, dmSimpleExtension, dmSimpleRestriction };

enum DECLSPEC_DENUM TSimpleDerivationMethod : unsigned char { sdmNone, sdmRestriction, sdmList, sdmUnion };

enum DECLSPEC_DENUM TSchemaRefType : unsigned char { srNone, srImport, srInclude };

__interface  INTERFACE_UUID("{BA009DE0-8372-11D4-8E37-00C0F056BC66}") IXMLElementDefList  : public System::Classes::IInterfaceList 
{
	
public:
	_di_IXMLElementDef operator[](const int Index) { return this->ElementDefs[Index]; }
	virtual _di_IXMLElementDef __fastcall GetElementDef(const int Index) = 0 ;
	__property _di_IXMLElementDef ElementDefs[const int Index] = {read=GetElementDef/*, default*/};
};

__interface  INTERFACE_UUID("{6C15F622-846C-11D4-8E37-00C0F056BC66}") IXMLAttributeDefList  : public System::Classes::IInterfaceList 
{
	
public:
	_di_IXMLAttributeDef operator[](const int Index) { return this->AttributeDefs[Index]; }
	virtual _di_IXMLAttributeDef __fastcall GetAttributeDef(const int Index) = 0 ;
	__property _di_IXMLAttributeDef AttributeDefs[const int Index] = {read=GetAttributeDef/*, default*/};
};

__interface  INTERFACE_UUID("{2DF0AEF7-6A69-45DB-8F4D-C00D6BE3F0AA}") IXMLSchemaNode  : public Xml::Xmlintf::IXMLNode 
{
	virtual _di_IXMLSchemaDef __fastcall GetSchemaDef() = 0 ;
	__property _di_IXMLSchemaDef SchemaDef = {read=GetSchemaDef};
};

__interface  INTERFACE_UUID("{7EDFC120-4C43-11D4-83DA-00C04F60B2DD}") IXMLAnnotatedItem  : public IXMLSchemaNode 
{
	virtual _di_IXMLAppInfoCollection __fastcall GetAppInfoCollection() = 0 ;
	virtual _di_IXMLDocumentationCollection __fastcall GetDocumentationCollection() = 0 ;
	virtual bool __fastcall HasAnnotation() = 0 ;
	virtual void __fastcall RemoveAnnotation(bool OnlyIfEmpty = true) = 0 ;
	__property _di_IXMLAppInfoCollection AppInfo = {read=GetAppInfoCollection};
	__property _di_IXMLDocumentationCollection Documentation = {read=GetDocumentationCollection};
};

__interface  INTERFACE_UUID("{501411A9-74B8-46AF-A145-12E3A46A7DA4}") IXMLSchemaDocRef  : public IXMLAnnotatedItem 
{
	virtual System::UnicodeString __fastcall GetSchemaLocation() = 0 ;
	virtual _di_IXMLSchemaDef __fastcall GetSchemaRef() = 0 ;
	virtual TSchemaRefType __fastcall GetSchemaRefType() = 0 ;
	virtual void __fastcall SetSchemaLocation(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetSchemaRefType(const TSchemaRefType Value) = 0 ;
	__property _di_IXMLSchemaDef SchemaRef = {read=GetSchemaRef};
	__property System::UnicodeString SchemaLocation = {read=GetSchemaLocation, write=SetSchemaLocation};
	__property TSchemaRefType SchemaRefType = {read=GetSchemaRefType, write=SetSchemaRefType};
};

__interface  INTERFACE_UUID("{C15D7ABA-CAB6-4230-A732-BFC3C95F7B1A}") IXMLSchemaImport  : public IXMLSchemaDocRef 
{
	
};

__interface  INTERFACE_UUID("{9C3A2E64-8CA5-403D-B557-1E28A9570720}") IXMLSchemaInclude  : public IXMLSchemaDocRef 
{
	
};

__interface  INTERFACE_UUID("{7EDFC120-4C43-11D4-83DA-00C04F60B2DD}") IXMLSchemaItem  : public IXMLAnnotatedItem 
{
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual void __fastcall SetName(const System::UnicodeString Value) = 0 ;
	virtual bool __fastcall IsGlobal() = 0 ;
	virtual System::UnicodeString __fastcall ItemLocalName() = 0 ;
	__property System::UnicodeString Name = {read=GetName, write=SetName};
};

__interface  INTERFACE_UUID("{7EDFC121-4C43-11D4-83DA-00C04F60B2DD}") IXMLTypeDef  : public IXMLSchemaItem 
{
	virtual _di_IXMLTypeDef __fastcall GetBaseType() = 0 ;
	virtual System::UnicodeString __fastcall GetBaseTypeName() = 0 ;
	virtual System::Variant __fastcall GetBounded() = 0 ;
	virtual System::Variant __fastcall GetCardinality() = 0 ;
	virtual _di_IXMLEnumerationCollection __fastcall GetEnumerations() = 0 ;
	virtual System::Variant __fastcall GetFractionalDigits() = 0 ;
	virtual System::Variant __fastcall GetLength() = 0 ;
	virtual System::Variant __fastcall GetMaxExclusive() = 0 ;
	virtual System::Variant __fastcall GetMaxInclusive() = 0 ;
	virtual System::Variant __fastcall GetMaxLength() = 0 ;
	virtual System::Variant __fastcall GetMinExclusive() = 0 ;
	virtual System::Variant __fastcall GetMinInclusive() = 0 ;
	virtual System::Variant __fastcall GetMinLength() = 0 ;
	virtual System::Variant __fastcall GetNumeric() = 0 ;
	virtual System::Variant __fastcall GetOrdered() = 0 ;
	virtual System::Variant __fastcall GetPattern() = 0 ;
	virtual System::Variant __fastcall GetTotalDigits() = 0 ;
	virtual System::Variant __fastcall GetWhitespace() = 0 ;
	virtual void __fastcall SetBaseTypeName(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetBounded(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetCardinality(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetFractionalDigits(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetLength(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetMaxExclusive(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetMaxInclusive(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetMaxLength(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetMinExclusive(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetMinInclusive(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetMinLength(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetNumeric(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetOrdered(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetPattern(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetTotalDigits(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetWhitespace(const System::Variant &Value) = 0 ;
	virtual bool __fastcall IsAnonymous() = 0 ;
	virtual bool __fastcall IsComplex() = 0 ;
	__property _di_IXMLTypeDef BaseType = {read=GetBaseType};
	__property System::UnicodeString BaseTypeName = {read=GetBaseTypeName, write=SetBaseTypeName};
	__property _di_IXMLEnumerationCollection Enumerations = {read=GetEnumerations};
	__property System::Variant Ordered = {read=GetOrdered, write=SetOrdered};
	__property System::Variant Bounded = {read=GetBounded, write=SetBounded};
	__property System::Variant Cardinality = {read=GetCardinality, write=SetCardinality};
	__property System::Variant Numeric = {read=GetNumeric, write=SetNumeric};
	__property System::Variant Length = {read=GetLength, write=SetLength};
	__property System::Variant MinLength = {read=GetMinLength, write=SetMinLength};
	__property System::Variant MaxLength = {read=GetMaxLength, write=SetMaxLength};
	__property System::Variant Pattern = {read=GetPattern, write=SetPattern};
	__property System::Variant Whitespace = {read=GetWhitespace, write=SetWhitespace};
	__property System::Variant MaxInclusive = {read=GetMaxInclusive, write=SetMaxInclusive};
	__property System::Variant MaxExclusive = {read=GetMaxExclusive, write=SetMaxExclusive};
	__property System::Variant MinInclusive = {read=GetMinInclusive, write=SetMinInclusive};
	__property System::Variant MinExclusive = {read=GetMinExclusive, write=SetMinExclusive};
	__property System::Variant TotalDigits = {read=GetTotalDigits, write=SetTotalDigits};
	__property System::Variant FractionalDigits = {read=GetFractionalDigits, write=SetFractionalDigits};
};

__interface  INTERFACE_UUID("{D355AA00-A9C9-4945-B97D-219A6E7E026F}") IXMLSimpleContent  : public IXMLSchemaNode 
{
	
};

__interface  INTERFACE_UUID("{7BE665E6-9D59-4E27-AF37-587A8CCA6306}") IXMLSimpleTypeRestriction  : public IXMLSimpleContent 
{
	virtual System::UnicodeString __fastcall GetBaseName() = 0 ;
	virtual void __fastcall SetBaseName(const System::UnicodeString Value) = 0 ;
	__property System::UnicodeString BaseName = {read=GetBaseName, write=SetBaseName};
};

__interface  INTERFACE_UUID("{0E61C20B-9773-4716-AF81-1833000F15BC}") IXMLSimpleTypeList  : public IXMLSimpleContent 
{
	virtual System::UnicodeString __fastcall GetItemType() = 0 ;
	virtual _di_IXMLSimpleTypeDef __fastcall GetSimpleTypeNode() = 0 ;
	virtual void __fastcall SetItemType(const System::UnicodeString Value) = 0 ;
	__property System::UnicodeString ItemType = {read=GetItemType, write=SetItemType};
	__property _di_IXMLSimpleTypeDef SimpleTypeNode = {read=GetSimpleTypeNode};
};

__interface  INTERFACE_UUID("{EA433957-14EE-4ACA-8B95-65060923EB56}") IXMLSimpleTypeUnion  : public IXMLSimpleContent 
{
	virtual System::UnicodeString __fastcall GetMemberTypes() = 0 ;
	virtual _di_IXMLSimpleTypeDefs __fastcall GetSimpleTypes() = 0 ;
	virtual void __fastcall SetMemberTypes(const System::UnicodeString Value) = 0 ;
	__property System::UnicodeString MemberTypes = {read=GetMemberTypes, write=SetMemberTypes};
	__property _di_IXMLSimpleTypeDefs SimpleTypes = {read=GetSimpleTypes};
};

__interface  INTERFACE_UUID("{7EDFC122-4C43-11D4-83DA-00C04F60B2DD}") IXMLSimpleTypeDef  : public IXMLTypeDef 
{
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall GetFacetParentNode(const bool Required = true) = 0 ;
	virtual System::UnicodeString __fastcall GetFinal() = 0 ;
	virtual _di_IXMLSimpleContent __fastcall GetContentNode() = 0 ;
	virtual TSimpleDerivationMethod __fastcall GetDerivationMethod() = 0 ;
	virtual _di_IXMLSimpleTypeRestriction __fastcall GetRestrictionNode() = 0 ;
	virtual void __fastcall SetFinal(const System::UnicodeString Value) = 0 ;
	virtual bool __fastcall IsBuiltInType() = 0 ;
	__property _di_IXMLSimpleContent ContentNode = {read=GetContentNode};
	__property TSimpleDerivationMethod DerivationMethod = {read=GetDerivationMethod};
	__property System::UnicodeString Final = {read=GetFinal, write=SetFinal};
	__property _di_IXMLSimpleTypeRestriction RestrictionNode = {read=GetRestrictionNode};
};

__interface  INTERFACE_UUID("{3DD57E4A-43AC-4C12-B878-B10C7BFE19D4}") IXMLBaseTypeIndicator  : public IXMLSchemaNode 
{
	virtual System::Variant __fastcall GetMixed() = 0 ;
	virtual void __fastcall SetMixed(const System::Variant &Value) = 0 ;
	__property System::Variant Mixed = {read=GetMixed, write=SetMixed};
};

__interface  INTERFACE_UUID("{7EDFC123-4C43-11D4-83DA-00C04F60B2DD}") IXMLComplexTypeDef  : public IXMLTypeDef 
{
	virtual bool __fastcall GetAbstract() = 0 ;
	virtual _di_IXMLAttributeDefList __fastcall GetAttributeDefList() = 0 ;
	virtual _di_IXMLAttributeDefs __fastcall GetAttributeDefs() = 0 ;
	virtual _di_IXMLAttributeGroups __fastcall GetAttributeGroups() = 0 ;
	virtual _di_IXMLBaseTypeIndicator __fastcall GetBaseTypeIndicator() = 0 ;
	virtual _di_IXMLElementCompositor __fastcall GetCompositorNode() = 0 ;
	virtual _di_IXMLElementCompositors __fastcall GetCompositors() = 0 ;
	virtual TContentModel __fastcall GetContentModel() = 0 ;
	virtual TDerivationMethod __fastcall GetDerivationMethod() = 0 ;
	virtual _di_IXMLElementDefList __fastcall GetElementDefList() = 0 ;
	virtual _di_IXMLElementDefs __fastcall GetElementDefs() = 0 ;
	virtual _di_IXMLElementGroups __fastcall GetElementGroups() = 0 ;
	virtual _di_IXMLElementGroup __fastcall GetGroupRef() = 0 ;
	virtual void __fastcall SetAbstract(const bool Value) = 0 ;
	virtual void __fastcall SetContentModel(const TContentModel Value) = 0 ;
	virtual void __fastcall SetDerivationMethod(const TDerivationMethod Value) = 0 ;
	__property bool AbstractType = {read=GetAbstract, write=SetAbstract};
	__property _di_IXMLAttributeDefs AttributeDefs = {read=GetAttributeDefs};
	__property _di_IXMLAttributeDefList AttributeDefList = {read=GetAttributeDefList};
	__property _di_IXMLAttributeGroups AttributeGroups = {read=GetAttributeGroups};
	__property _di_IXMLBaseTypeIndicator BaseTypeIndicator = {read=GetBaseTypeIndicator};
	__property _di_IXMLElementCompositor CompositorNode = {read=GetCompositorNode};
	__property TContentModel ContentModel = {read=GetContentModel, write=SetContentModel};
	__property TDerivationMethod DerivationMethod = {read=GetDerivationMethod, write=SetDerivationMethod};
	__property _di_IXMLElementCompositors ElementCompositors = {read=GetCompositors};
	__property _di_IXMLElementDefList ElementDefList = {read=GetElementDefList};
	__property _di_IXMLElementDefs ElementDefs = {read=GetElementDefs};
	__property _di_IXMLElementGroups ElementGroups = {read=GetElementGroups};
	__property _di_IXMLElementGroup GroupRef = {read=GetGroupRef};
};

__interface  INTERFACE_UUID("{41465201-D39A-4C39-ACBE-C3AF64F0720D}") IXMLSchemaRefItem  : public IXMLSchemaItem 
{
	virtual System::UnicodeString __fastcall GetRefName() = 0 ;
	virtual void __fastcall SetRefName(const System::UnicodeString Value) = 0 ;
	virtual _di_IXMLSchemaItems __fastcall GlobalCollection() = 0 ;
	__property System::UnicodeString RefName = {read=GetRefName, write=SetRefName};
};

__interface  INTERFACE_UUID("{75D91C7E-6DFF-44CA-91E0-34E4314AE9D4}") IXMLTypedSchemaItem  : public IXMLSchemaRefItem 
{
	virtual _di_IXMLTypeDef __fastcall GetDataType() = 0 ;
	virtual System::UnicodeString __fastcall GetDataTypeName() = 0 ;
	virtual void __fastcall SetDataType(const _di_IXMLTypeDef Value) = 0 ;
	virtual void __fastcall SetDataTypeName(const System::UnicodeString Value) = 0 ;
	__property _di_IXMLTypeDef DataType = {read=GetDataType, write=SetDataType};
	__property System::UnicodeString DataTypeName = {read=GetDataTypeName, write=SetDataTypeName};
};

__interface  INTERFACE_UUID("{7EDFC125-4C43-11D4-83DA-00C04F60B2DD}") IXMLAttributeDef  : public IXMLTypedSchemaItem 
{
	virtual _di_IXMLAttributeDef __fastcall GetRef() = 0 ;
	virtual System::Variant __fastcall GetUse() = 0 ;
	virtual System::Variant __fastcall GetDefault() = 0 ;
	virtual System::Variant __fastcall GetFixed() = 0 ;
	virtual void __fastcall SetRef(const _di_IXMLAttributeDef Value) = 0 ;
	virtual void __fastcall SetUse(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetDefault(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetFixed(const System::Variant &Value) = 0 ;
	__property _di_IXMLAttributeDef Ref = {read=GetRef, write=SetRef};
	__property System::Variant Use = {read=GetUse, write=SetUse};
	__property System::Variant Default = {read=GetDefault, write=SetDefault};
	__property System::Variant Fixed = {read=GetFixed, write=SetFixed};
};

__interface  INTERFACE_UUID("{7EDFC124-4C43-11D4-83DA-00C04F60B2DD}") IXMLElementDef  : public IXMLTypedSchemaItem 
{
	virtual _di_IXMLAttributeDefList __fastcall GetAttributeDefList() = 0 ;
	virtual _di_IXMLElementDefList __fastcall GetChildElementList() = 0 ;
	virtual System::Variant __fastcall GetMaxOccurs() = 0 ;
	virtual System::Variant __fastcall GetMinOccurs() = 0 ;
	virtual _di_IXMLElementDef __fastcall GetRef() = 0 ;
	virtual void __fastcall SetMaxOccurs(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetMinOccurs(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetRef(const _di_IXMLElementDef Value) = 0 ;
	virtual bool __fastcall IsRepeating() = 0 ;
	__property _di_IXMLAttributeDefList AttributeDefs = {read=GetAttributeDefList};
	__property _di_IXMLElementDefList ChildElements = {read=GetChildElementList};
	__property System::Variant MaxOccurs = {read=GetMaxOccurs, write=SetMaxOccurs};
	__property System::Variant MinOccurs = {read=GetMinOccurs, write=SetMinOccurs};
	__property _di_IXMLElementDef Ref = {read=GetRef, write=SetRef};
};

__interface  INTERFACE_UUID("{0B007C80-648B-11D4-83DA-00C04F60B2DD}") IXMLElementCompositor  : public IXMLAnnotatedItem 
{
	virtual _di_IXMLElementCompositors __fastcall GetCompositors() = 0 ;
	virtual TCompositorType __fastcall GetCompositorType() = 0 ;
	virtual _di_IXMLElementDefs __fastcall GetElementDefs() = 0 ;
	virtual _di_IXMLElementGroups __fastcall GetElementGroups() = 0 ;
	virtual System::Variant __fastcall GetMaxOccurs() = 0 ;
	virtual System::Variant __fastcall GetMinOccurs() = 0 ;
	virtual void __fastcall SetMaxOccurs(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetMinOccurs(const System::Variant &Value) = 0 ;
	__property _di_IXMLElementCompositors Compositors = {read=GetCompositors};
	__property TCompositorType CompositorType = {read=GetCompositorType};
	__property _di_IXMLElementDefs ElementDefs = {read=GetElementDefs};
	__property _di_IXMLElementGroups ElementGroups = {read=GetElementGroups};
	__property System::Variant MaxOccurs = {read=GetMaxOccurs, write=SetMaxOccurs};
	__property System::Variant MinOccurs = {read=GetMinOccurs, write=SetMinOccurs};
};

__interface  INTERFACE_UUID("{8E5DB500-63C5-11D4-83DA-00C04F60B2DD}") IXMLAttributeGroup  : public IXMLSchemaRefItem 
{
	virtual _di_IXMLAttributeDefs __fastcall GetAttributeDefs() = 0 ;
	virtual _di_IXMLAttributeGroups __fastcall GetAttributeGroups() = 0 ;
	virtual _di_IXMLAttributeGroup __fastcall GetRef() = 0 ;
	virtual void __fastcall SetRef(const _di_IXMLAttributeGroup Value) = 0 ;
	__property _di_IXMLAttributeDefs AttributeDefs = {read=GetAttributeDefs};
	__property _di_IXMLAttributeGroups AttributeGroups = {read=GetAttributeGroups};
	__property _di_IXMLAttributeGroup Ref = {read=GetRef, write=SetRef};
};

__interface  INTERFACE_UUID("{53F27080-4DAF-11D4-83DA-00C04F60B2DD}") IXMLElementGroup  : public IXMLSchemaRefItem 
{
	virtual _di_IXMLElementCompositor __fastcall GetCompositorNode() = 0 ;
	virtual _di_IXMLElementCompositors __fastcall GetElementCompositors() = 0 ;
	virtual _di_IXMLElementDefs __fastcall GetElementDefs() = 0 ;
	virtual _di_IXMLElementGroups __fastcall GetElementGroups() = 0 ;
	virtual _di_IXMLElementGroup __fastcall GetRef() = 0 ;
	virtual void __fastcall SetRef(const _di_IXMLElementGroup Value) = 0 ;
	__property _di_IXMLElementCompositor CompositorNode = {read=GetCompositorNode};
	__property _di_IXMLElementCompositors ElementCompositors = {read=GetElementCompositors};
	__property _di_IXMLElementDefs ElementDefs = {read=GetElementDefs};
	__property _di_IXMLElementGroups ElementGroups = {read=GetElementGroups};
	__property _di_IXMLElementGroup Ref = {read=GetRef, write=SetRef};
};

__interface  INTERFACE_UUID("{6BC9D168-3AA1-4F00-A025-DAD2CD02E5B3}") IXMLNotation  : public IXMLSchemaItem 
{
	virtual void __fastcall SetPublicID(const System::Variant &Value) = 0 ;
	virtual void __fastcall SetSystemID(const System::Variant &Value) = 0 ;
	virtual System::Variant __fastcall GetPublicID() = 0 ;
	virtual System::Variant __fastcall GetSystemID() = 0 ;
	__property System::Variant PublicID = {read=GetPublicID, write=SetPublicID};
	__property System::Variant SystemID = {read=GetSystemID, write=SetSystemID};
};

__interface  INTERFACE_UUID("{F3A9316D-4AF3-4CD7-8C5B-DBFEF236A8DA}") IXMLAnnotation  : public IXMLSchemaNode 
{
	virtual _di_IXMLAppInfoCollection __fastcall GetAppInfoCollection() = 0 ;
	virtual _di_IXMLDocumentationCollection __fastcall GetDocumentationCollection() = 0 ;
	virtual bool __fastcall HasAppInfo() = 0 ;
	virtual bool __fastcall HasDocumentation() = 0 ;
	__property _di_IXMLAppInfoCollection AppInfo = {read=GetAppInfoCollection};
	__property _di_IXMLDocumentationCollection Documentation = {read=GetDocumentationCollection};
};

__interface  INTERFACE_UUID("{FE7435C8-806F-441F-9195-A23F777D1954}") IXMLAppInfo  : public IXMLSchemaNode 
{
	virtual System::Variant __fastcall GetSource() = 0 ;
	virtual void __fastcall SetSource(const System::Variant &Value) = 0 ;
	__property System::Variant Source = {read=GetSource, write=SetSource};
};

__interface  INTERFACE_UUID("{A1562492-BC31-4727-A690-17631848C2AF}") IXMLDocumentation  : public IXMLSchemaNode 
{
	virtual System::Variant __fastcall GetSource() = 0 ;
	virtual void __fastcall SetSource(const System::Variant &Value) = 0 ;
	__property System::Variant Source = {read=GetSource, write=SetSource};
};

__interface  INTERFACE_UUID("{FBF0F414-AA54-4ADD-BD64-EA15D5AD380E}") IXMLEnumeration  : public IXMLSchemaNode 
{
	virtual System::Variant __fastcall GetValue() = 0 ;
	virtual void __fastcall SetValue(const System::Variant &Value) = 0 ;
	__property System::Variant Value = {read=GetValue, write=SetValue};
};

__interface  INTERFACE_UUID("{3C32E7BD-5CEE-4757-9C1D-266BB11983FE}") IXMLSchemaDocRefs  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IXMLSchemaDocRef operator[](int Index) { return this->SchemaDocRef[Index]; }
	virtual _di_IXMLSchemaDocRef __fastcall GetSchemaDocRef(int Index) = 0 ;
	__property _di_IXMLSchemaDocRef SchemaDocRef[int Index] = {read=GetSchemaDocRef/*, default*/};
};

__interface  INTERFACE_UUID("{7EDFC126-4C43-11D4-83DA-00C04F60B2DD}") IXMLSchemaImports  : public IXMLSchemaDocRefs 
{
	
public:
	_di_IXMLSchemaImport operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLSchemaImport __fastcall GetItem(int Index) = 0 ;
	virtual _di_IXMLSchemaImport __fastcall Add(const System::UnicodeString SchemaLocation) = 0 /* overload */;
	virtual _di_IXMLSchemaImport __fastcall Insert(int Index) = 0 ;
	__property _di_IXMLSchemaImport Items[int Index] = {read=GetItem/*, default*/};
};

__interface  INTERFACE_UUID("{7D9A30D4-007E-47C1-9BC1-AF8A1919777B}") IXMLSchemaIncludes  : public IXMLSchemaDocRefs 
{
	
public:
	_di_IXMLSchemaInclude operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLSchemaInclude __fastcall GetItem(int Index) = 0 ;
	virtual _di_IXMLSchemaInclude __fastcall Add(const System::UnicodeString SchemaLocation) = 0 /* overload */;
	virtual _di_IXMLSchemaInclude __fastcall Insert(int Index) = 0 ;
	__property _di_IXMLSchemaInclude Items[int Index] = {read=GetItem/*, default*/};
};

__interface  INTERFACE_UUID("{7EDFC126-4C43-11D4-83DA-00C04F60B2DD}") IXMLSchemaItems  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IXMLSchemaItem operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLSchemaItem __fastcall GetSchemaItem(int Index) = 0 ;
	virtual _di_IXMLSchemaItem __fastcall FindItem(const System::UnicodeString Name) = 0 ;
	virtual int __fastcall IndexOfItem(const System::UnicodeString Name) = 0 ;
	__property _di_IXMLSchemaItem Items[int Index] = {read=GetSchemaItem/*, default*/};
};

__interface  INTERFACE_UUID("{7EDFC127-4C43-11D4-83DA-00C04F60B2DD}") IXMLSimpleTypeDefs  : public IXMLSchemaItems 
{
	
public:
	_di_IXMLSimpleTypeDef operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLSimpleTypeDef __fastcall GetItem(int Index) = 0 ;
	virtual _di_IXMLSimpleTypeDef __fastcall Add(const System::UnicodeString Name, System::UnicodeString BaseTypeName = System::UnicodeString()) = 0 /* overload */;
	virtual _di_IXMLSimpleTypeDef __fastcall Find(const System::UnicodeString Name) = 0 ;
	virtual _di_IXMLSimpleTypeDef __fastcall Insert(int Index) = 0 ;
	__property _di_IXMLSimpleTypeDef Items[int Index] = {read=GetItem/*, default*/};
};

__interface  INTERFACE_UUID("{7EDFC128-4C43-11D4-83DA-00C04F60B2DD}") IXMLComplexTypeDefs  : public IXMLSchemaItems 
{
	
public:
	_di_IXMLComplexTypeDef operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLComplexTypeDef __fastcall GetItem(int Index) = 0 ;
	virtual _di_IXMLComplexTypeDef __fastcall Add(const System::UnicodeString Name, TContentModel ContentModel = (TContentModel)(0x2)) = 0 /* overload */;
	virtual _di_IXMLComplexTypeDef __fastcall Add(const System::UnicodeString Name, const System::UnicodeString BaseTypeName, TDerivationMethod DerivationMethod = (TDerivationMethod)(0x1), TContentModel ContentModel = (TContentModel)(0x2)) = 0 /* overload */;
	virtual _di_IXMLComplexTypeDef __fastcall Find(const System::UnicodeString Name) = 0 ;
	virtual _di_IXMLComplexTypeDef __fastcall Insert(int Index) = 0 ;
	__property _di_IXMLComplexTypeDef Items[int Index] = {read=GetItem/*, default*/};
};

__interface  INTERFACE_UUID("{7EDFC131-4C43-11D4-83DA-00C04F60B2DD}") IXMLAttributeDefs  : public IXMLSchemaItems 
{
	
public:
	_di_IXMLAttributeDef operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLAttributeDef __fastcall GetItem(int Index) = 0 ;
	virtual _di_IXMLAttributeDef __fastcall Add(const System::UnicodeString RefName) = 0 /* overload */;
	virtual _di_IXMLAttributeDef __fastcall Add(const System::UnicodeString Name, const System::UnicodeString DataType) = 0 /* overload */;
	virtual _di_IXMLAttributeDef __fastcall Add(const System::UnicodeString Name, bool LocalSimpleType, System::UnicodeString BaseTypeName = System::UnicodeString()) = 0 /* overload */;
	virtual _di_IXMLAttributeDef __fastcall Find(const System::UnicodeString Name) = 0 ;
	virtual _di_IXMLAttributeDef __fastcall Insert(int Index) = 0 ;
	__property _di_IXMLAttributeDef Items[int Index] = {read=GetItem/*, default*/};
};

__interface  INTERFACE_UUID("{7EDFC130-4C43-11D4-83DA-00C04F60B2DD}") IXMLElementDefs  : public IXMLSchemaItems 
{
	
public:
	_di_IXMLElementDef operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLElementDef __fastcall GetItem(int Index) = 0 ;
	virtual _di_IXMLElementDef __fastcall Add(const System::UnicodeString RefName) = 0 /* overload */;
	virtual _di_IXMLElementDef __fastcall Add(const System::UnicodeString Name, const System::UnicodeString DataType) = 0 /* overload */;
	virtual _di_IXMLElementDef __fastcall Add(const System::UnicodeString Name, bool ComplexLocalType, System::UnicodeString BaseTypeName = System::UnicodeString()) = 0 /* overload */;
	virtual _di_IXMLElementDef __fastcall Find(const System::UnicodeString Name) = 0 ;
	virtual _di_IXMLElementDef __fastcall Insert(int Index) = 0 ;
	__property _di_IXMLElementDef Items[int Index] = {read=GetItem/*, default*/};
};

__interface  INTERFACE_UUID("{8E5DB501-63C5-11D4-83DA-00C04F60B2DD}") IXMLAttributeGroups  : public IXMLSchemaItems 
{
	
public:
	_di_IXMLAttributeGroup operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLAttributeGroup __fastcall GetItem(int Index) = 0 ;
	virtual _di_IXMLAttributeGroup __fastcall Add() = 0 ;
	virtual _di_IXMLAttributeGroup __fastcall Find(const System::UnicodeString Name) = 0 ;
	virtual _di_IXMLAttributeGroup __fastcall Insert(int Index) = 0 ;
	__property _di_IXMLAttributeGroup Items[int Index] = {read=GetItem/*, default*/};
};

__interface  INTERFACE_UUID("{7EDFC129-4C43-11D4-83DA-00C04F60B2DD}") IXMLElementGroups  : public IXMLSchemaItems 
{
	
public:
	_di_IXMLElementGroup operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLElementGroup __fastcall GetItem(int Index) = 0 ;
	virtual _di_IXMLElementGroup __fastcall Add(const System::UnicodeString NameOrRef) = 0 /* overload */;
	virtual _di_IXMLElementGroup __fastcall Find(const System::UnicodeString Name) = 0 ;
	virtual _di_IXMLElementGroup __fastcall Insert(int Index) = 0 ;
	__property _di_IXMLElementGroup Items[int Index] = {read=GetItem/*, default*/};
};

__interface  INTERFACE_UUID("{0B007C81-648B-11D4-83DA-00C04F60B2DD}") IXMLElementCompositors  : public IXMLSchemaItems 
{
	
public:
	_di_IXMLElementCompositor operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLElementCompositor __fastcall GetItem(int Index) = 0 ;
	virtual _di_IXMLElementCompositor __fastcall Add(TCompositorType CompositorType = (TCompositorType)(0x2)) = 0 ;
	virtual _di_IXMLElementCompositor __fastcall Insert(int Index) = 0 ;
	__property _di_IXMLElementCompositor Items[int Index] = {read=GetItem/*, default*/};
};

__interface  INTERFACE_UUID("{6388BD4A-9E83-4249-A7F0-C8438F47D0AD}") IXMLNotationDefs  : public IXMLSchemaItems 
{
	
public:
	_di_IXMLNotation operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLNotation __fastcall GetItem(int Index) = 0 ;
	virtual _di_IXMLNotation __fastcall Add(const System::UnicodeString Name, const System::UnicodeString APublicID = System::UnicodeString(), const System::UnicodeString ASystemID = System::UnicodeString()) = 0 /* overload */;
	virtual _di_IXMLNotation __fastcall Insert(int Index) = 0 ;
	__property _di_IXMLNotation Items[int Index] = {read=GetItem/*, default*/};
};

__interface  INTERFACE_UUID("{C6414FE7-A7AD-495B-9302-2E65537FE0A1}") IXMLAnnotationItems  : public Xml::Xmlintf::IXMLNodeCollection 
{
	virtual _di_IXMLAnnotation __fastcall Add() = 0 ;
	virtual _di_IXMLAnnotation __fastcall GetItem(int Index) = 0 ;
	virtual _di_IXMLAnnotation __fastcall Insert(int Index) = 0 ;
};

__interface  INTERFACE_UUID("{6C5C9808-FE59-4A7E-A38A-A17F710C0BE7}") IXMLAppInfoCollection  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IXMLAppInfo operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLAppInfo __fastcall Add() = 0 ;
	virtual _di_IXMLAppInfo __fastcall GetAppInfo(const GUID &AppInfoType, Xml::Xmldoc::TXMLNodeClass AppInfoClassType = 0x0) = 0 ;
	virtual _di_IXMLAppInfo __fastcall GetItem(int Index) = 0 ;
	virtual _di_IXMLAppInfo __fastcall Insert(int Index) = 0 ;
	__property _di_IXMLAppInfo Items[int Index] = {read=GetItem/*, default*/};
};

__interface  INTERFACE_UUID("{F7820DA4-7C00-40D0-9F2C-AF726D8D4353}") IXMLDocumentationCollection  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IXMLDocumentation operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLDocumentation __fastcall Add() = 0 ;
	virtual _di_IXMLDocumentation __fastcall GetItem(int Index) = 0 ;
	virtual _di_IXMLDocumentation __fastcall Insert(int Index) = 0 ;
	__property _di_IXMLDocumentation Items[int Index] = {read=GetItem/*, default*/};
};

__interface  INTERFACE_UUID("{3EB8EB97-1343-40E1-9E85-5E29C4EDD8C4}") IXMLEnumerationCollection  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IXMLEnumeration operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLEnumeration __fastcall Add(const System::UnicodeString Value) = 0 ;
	virtual _di_IXMLEnumeration __fastcall GetItem(int Index) = 0 ;
	virtual _di_IXMLEnumeration __fastcall Insert(int Index) = 0 ;
	__property _di_IXMLEnumeration Items[int Index] = {read=GetItem/*, default*/};
};

__interface  INTERFACE_UUID("{7EDFC132-4C43-11D4-83DA-00C04F60B2DD}") IXMLSchemaDef  : public Xml::Xmlintf::IXMLNode 
{
	virtual _di_IXMLAnnotationItems __fastcall GetAnnotations() = 0 ;
	virtual _di_IXMLAttributeDefs __fastcall GetAttributeDefs() = 0 ;
	virtual TFormChoice __fastcall GetAttributeFormDefault() = 0 ;
	virtual _di_IXMLAttributeGroups __fastcall GetAttributeGroups() = 0 ;
	virtual _di_IXMLSimpleTypeDefs __fastcall GetBuiltInTypes() = 0 ;
	virtual _di_IXMLComplexTypeDefs __fastcall GetComplexTypes() = 0 ;
	virtual _di_IXMLElementDef __fastcall GetDocElementDef() = 0 ;
	virtual _di_IXMLElementDefs __fastcall GetElementDefs() = 0 ;
	virtual TFormChoice __fastcall GetElementFormDefault() = 0 ;
	virtual _di_IXMLElementGroups __fastcall GetElementGroups() = 0 ;
	virtual _di_IXMLNotationDefs __fastcall GetNotationDefs() = 0 ;
	virtual _di_IXMLSchemaDef __fastcall GetParentSchemaDef() = 0 ;
	virtual TSchemaRefType __fastcall GetParentRefType() = 0 ;
	virtual bool __fastcall GetQualifyAnonymousTypeNames() = 0 ;
	virtual _di_IXMLSchemaDoc __fastcall GetSchemaDoc() = 0 ;
	virtual _di_IXMLSchemaImports __fastcall GetSchemaImports() = 0 ;
	virtual _di_IXMLSchemaIncludes __fastcall GetSchemaIncludes() = 0 ;
	virtual _di_IXMLSimpleTypeDefs __fastcall GetSimpleTypes() = 0 ;
	virtual bool __fastcall GetStrictFormat() = 0 ;
	virtual System::OleVariant __fastcall GetTargetNamespace() = 0 ;
	virtual System::UnicodeString __fastcall GetTargetNSPrefix() = 0 ;
	virtual System::UnicodeString __fastcall GetVersion() = 0 ;
	virtual void __fastcall SetAttributeformDefault(const TFormChoice Value) = 0 ;
	virtual void __fastcall SetDocElementDef(const _di_IXMLElementDef Value) = 0 ;
	virtual void __fastcall SetElementformDefault(const TFormChoice Value) = 0 ;
	virtual void __fastcall SetParentSchemaDef(const _di_IXMLSchemaDef Value) = 0 ;
	virtual void __fastcall SetParentRefType(const TSchemaRefType Value) = 0 ;
	virtual void __fastcall SetQualifyAnonymousTypeNames(const bool Value) = 0 ;
	virtual void __fastcall SetStrictFormat(const bool Value) = 0 ;
	virtual void __fastcall SetVersion(const System::UnicodeString Value) = 0 ;
	virtual System::UnicodeString __fastcall FindNamespacePrefix(const System::UnicodeString NamespaceURI) = 0 ;
	virtual System::UnicodeString __fastcall PrefixedTypeName(const System::UnicodeString TypeName) = 0 ;
	virtual void __fastcall RegisterAppInfo(const System::UnicodeString NamespaceURI, const System::UnicodeString Prefix, Xml::Xmldoc::TXMLNodeClass NodeClass) = 0 ;
	virtual void __fastcall SetTargetNamespace(const System::UnicodeString NamespaceURI, const System::UnicodeString NSPrefix) = 0 ;
	__property _di_IXMLAnnotationItems Annotations = {read=GetAnnotations};
	__property _di_IXMLAttributeDefs AttributeDefs = {read=GetAttributeDefs};
	__property TFormChoice AttributeFormDefault = {read=GetAttributeFormDefault, write=SetAttributeformDefault};
	__property _di_IXMLAttributeGroups AttributeGroups = {read=GetAttributeGroups};
	__property _di_IXMLSimpleTypeDefs BuiltInTypes = {read=GetBuiltInTypes};
	__property _di_IXMLComplexTypeDefs ComplexTypes = {read=GetComplexTypes};
	__property _di_IXMLElementDef DocElementDef = {read=GetDocElementDef, write=SetDocElementDef};
	__property _di_IXMLElementDefs ElementDefs = {read=GetElementDefs};
	__property TFormChoice ElementFormDefault = {read=GetElementFormDefault, write=SetElementformDefault};
	__property _di_IXMLElementGroups ElementGroups = {read=GetElementGroups};
	__property _di_IXMLNotationDefs NotationDefs = {read=GetNotationDefs};
	__property _di_IXMLSchemaDef ParentSchema = {read=GetParentSchemaDef, write=SetParentSchemaDef};
	__property TSchemaRefType ParentRefType = {read=GetParentRefType, write=SetParentRefType};
	__property bool QualifyAnonymousTypeNames = {read=GetQualifyAnonymousTypeNames, write=SetQualifyAnonymousTypeNames};
	__property _di_IXMLSchemaDoc SchemaDoc = {read=GetSchemaDoc};
	__property _di_IXMLSchemaImports SchemaImports = {read=GetSchemaImports};
	__property _di_IXMLSchemaIncludes SchemaIncludes = {read=GetSchemaIncludes};
	__property _di_IXMLSimpleTypeDefs SimpleTypes = {read=GetSimpleTypes};
	__property bool StrictFormat = {read=GetStrictFormat, write=SetStrictFormat};
	__property System::OleVariant TargetNamespace = {read=GetTargetNamespace};
	__property System::UnicodeString TargetNSPrefix = {read=GetTargetNSPrefix};
	__property System::UnicodeString Version = {read=GetVersion, write=SetVersion};
};

__interface  INTERFACE_UUID("{4E6B683C-15F4-4F62-9B4B-DF3130420F62}") IXMLSchemaDoc  : public Xml::Xmlintf::IXMLDocument 
{
	virtual _di_IXMLSchemaDef __fastcall GetSchemaDef() = 0 ;
	virtual bool __fastcall GetWasImported() = 0 ;
	__property _di_IXMLSchemaDef SchemaDef = {read=GetSchemaDef};
	__property bool WasImported = {read=GetWasImported};
};

__interface  INTERFACE_UUID("{9C4DB79C-1D60-4BF2-95EE-63FDF98237D0}") IXMLSchemaTranslator  : public System::IInterface 
{
	virtual void __fastcall Translate(const System::UnicodeString FileName, const _di_IXMLSchemaDef SchemaDef) = 0 ;
};

__interface  INTERFACE_UUID("{AAB226EE-51C1-4902-B883-FE538EB1F27E}") IXMLSchemaTranslatorFactory  : public System::IInterface 
{
	virtual bool __fastcall CanExportFile(const System::UnicodeString FileName) = 0 ;
	virtual bool __fastcall CanImportFile(const System::UnicodeString FileName) = 0 ;
	virtual _di_IXMLSchemaTranslator __fastcall GetExportTranslator() = 0 ;
	virtual _di_IXMLSchemaTranslator __fastcall GetImportTranslator() = 0 ;
	virtual System::UnicodeString __fastcall GetTranslatorDescription() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLAttributeDefList : public System::Classes::TInterfaceList
{
	typedef System::Classes::TInterfaceList inherited;
	
public:
	_di_IXMLAttributeDef __fastcall GetAttributeDef(const int Index);
public:
	/* TInterfaceList.Create */ inline __fastcall TXMLAttributeDefList() : System::Classes::TInterfaceList() { }
	/* TInterfaceList.Destroy */ inline __fastcall virtual ~TXMLAttributeDefList() { }
	
private:
	void *__IXMLAttributeDefList;	// IXMLAttributeDefList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6C15F622-846C-11D4-8E37-00C0F056BC66}
	operator _di_IXMLAttributeDefList()
	{
		_di_IXMLAttributeDefList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLAttributeDefList*(void) { return (IXMLAttributeDefList*)&__IXMLAttributeDefList; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLElementDefList : public System::Classes::TInterfaceList
{
	typedef System::Classes::TInterfaceList inherited;
	
public:
	_di_IXMLElementDef __fastcall GetElementDef(const int Index);
public:
	/* TInterfaceList.Create */ inline __fastcall TXMLElementDefList() : System::Classes::TInterfaceList() { }
	/* TInterfaceList.Destroy */ inline __fastcall virtual ~TXMLElementDefList() { }
	
private:
	void *__IXMLElementDefList;	// IXMLElementDefList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BA009DE0-8372-11D4-8E37-00C0F056BC66}
	operator _di_IXMLElementDefList()
	{
		_di_IXMLElementDefList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLElementDefList*(void) { return (IXMLElementDefList*)&__IXMLElementDefList; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSchemaNode : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	TXMLSchemaDef* __fastcall SchemaObject();
	_di_IXMLSchemaDef __fastcall GetSchemaDef();
	__property _di_IXMLSchemaDef SchemaDef = {read=GetSchemaDef};
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSchemaNode(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSchemaNode(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSchemaNode() { }
	
private:
	void *__IXMLSchemaNode;	// IXMLSchemaNode 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2DF0AEF7-6A69-45DB-8F4D-C00D6BE3F0AA}
	operator _di_IXMLSchemaNode()
	{
		_di_IXMLSchemaNode intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSchemaNode*(void) { return (IXMLSchemaNode*)&__IXMLSchemaNode; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSchemaItem : public TXMLSchemaNode
{
	typedef TXMLSchemaNode inherited;
	
private:
	_di_IXMLSchemaRefItem FRefItem;
	_di_IXMLAnnotation FAnnotation;
	
protected:
	virtual _di_IXMLSchemaItems __fastcall GlobalCollection();
	_di_IXMLSchemaRefItem __fastcall GetRefItem();
	virtual void __fastcall SetRefItem(const _di_IXMLSchemaRefItem Value);
	bool __fastcall IsGlobal();
	_di_IXMLAnnotation __fastcall GetAnnotation();
	_di_IXMLAppInfoCollection __fastcall GetAppInfoCollection();
	_di_IXMLDocumentationCollection __fastcall GetDocumentationCollection();
	virtual System::UnicodeString __fastcall GetName();
	System::UnicodeString __fastcall GetRefName();
	virtual void __fastcall SetName(const System::UnicodeString Value);
	void __fastcall SetRefName(const System::UnicodeString Value);
	bool __fastcall HasAnnotation();
	System::UnicodeString __fastcall ItemLocalName();
	void __fastcall RemoveAnnotation(bool OnlyIfEmpty = true);
	__property _di_IXMLAnnotation Annotation = {read=GetAnnotation};
	__property _di_IXMLSchemaRefItem RefItem = {read=GetRefItem, write=SetRefItem};
	__property _di_IXMLSchemaDef SchemaDef = {read=GetSchemaDef};
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSchemaItem(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSchemaItem(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSchemaItem() { }
	
private:
	void *__IXMLSchemaRefItem;	// IXMLSchemaRefItem 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {41465201-D39A-4C39-ACBE-C3AF64F0720D}
	operator _di_IXMLSchemaRefItem()
	{
		_di_IXMLSchemaRefItem intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSchemaRefItem*(void) { return (IXMLSchemaRefItem*)&__IXMLSchemaRefItem; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EDFC120-4C43-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLSchemaItem()
	{
		_di_IXMLSchemaItem intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSchemaItem*(void) { return (IXMLSchemaItem*)&__IXMLSchemaRefItem; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EDFC120-4C43-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLAnnotatedItem()
	{
		_di_IXMLAnnotatedItem intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLAnnotatedItem*(void) { return (IXMLAnnotatedItem*)&__IXMLSchemaRefItem; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSchemaDocRef : public TXMLSchemaItem
{
	typedef TXMLSchemaItem inherited;
	
private:
	_di_IXMLSchemaDef FSchemaRef;
	TSchemaRefType FSchemaRefType;
	
protected:
	System::UnicodeString __fastcall GetSchemaLocation();
	_di_IXMLSchemaDef __fastcall GetSchemaRef();
	TSchemaRefType __fastcall GetSchemaRefType();
	void __fastcall SetSchemaLocation(const System::UnicodeString Value);
	void __fastcall SetSchemaRefType(const TSchemaRefType Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSchemaDocRef(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaItem(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSchemaDocRef(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaItem(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSchemaDocRef() { }
	
private:
	void *__IXMLSchemaDocRef;	// IXMLSchemaDocRef 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {501411A9-74B8-46AF-A145-12E3A46A7DA4}
	operator _di_IXMLSchemaDocRef()
	{
		_di_IXMLSchemaDocRef intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSchemaDocRef*(void) { return (IXMLSchemaDocRef*)&__IXMLSchemaDocRef; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSchemaImport : public TXMLSchemaDocRef
{
	typedef TXMLSchemaDocRef inherited;
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSchemaImport(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaDocRef(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSchemaImport(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaDocRef(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSchemaImport() { }
	
private:
	void *__IXMLSchemaImport;	// IXMLSchemaImport 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C15D7ABA-CAB6-4230-A732-BFC3C95F7B1A}
	operator _di_IXMLSchemaImport()
	{
		_di_IXMLSchemaImport intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSchemaImport*(void) { return (IXMLSchemaImport*)&__IXMLSchemaImport; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSchemaInclude : public TXMLSchemaDocRef
{
	typedef TXMLSchemaDocRef inherited;
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSchemaInclude(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaDocRef(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSchemaInclude(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaDocRef(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSchemaInclude() { }
	
private:
	void *__IXMLSchemaInclude;	// IXMLSchemaInclude 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9C3A2E64-8CA5-403D-B557-1E28A9570720}
	operator _di_IXMLSchemaInclude()
	{
		_di_IXMLSchemaInclude intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSchemaInclude*(void) { return (IXMLSchemaInclude*)&__IXMLSchemaInclude; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLTypeDef : public TXMLSchemaItem
{
	typedef TXMLSchemaItem inherited;
	
private:
	_di_IXMLEnumerationCollection FEnumerations;
	
protected:
	virtual System::Variant __fastcall ReadFacet(const System::UnicodeString FacetName);
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall GetFacetParentNode(const bool Required = true) = 0 ;
	virtual System::UnicodeString __fastcall GetName();
	virtual void __fastcall SetName(const System::UnicodeString Value);
	virtual _di_IXMLTypeDef __fastcall GetBaseType() = 0 ;
	System::UnicodeString __fastcall GetBaseTypeName();
	System::Variant __fastcall GetBounded();
	System::Variant __fastcall GetCardinality();
	_di_IXMLEnumerationCollection __fastcall GetEnumerations();
	System::Variant __fastcall GetFractionalDigits();
	System::Variant __fastcall GetLength();
	System::Variant __fastcall GetMaxExclusive();
	System::Variant __fastcall GetMaxInclusive();
	System::Variant __fastcall GetMaxLength();
	System::Variant __fastcall GetMinExclusive();
	System::Variant __fastcall GetMinInclusive();
	System::Variant __fastcall GetMinLength();
	System::Variant __fastcall GetNumeric();
	System::Variant __fastcall GetOrdered();
	System::Variant __fastcall GetPattern();
	System::Variant __fastcall GetTotalDigits();
	System::Variant __fastcall GetWhitespace();
	bool __fastcall IsAnonymous();
	virtual bool __fastcall IsComplex();
	virtual void __fastcall SetBaseTypeName(const System::UnicodeString Value) = 0 ;
	void __fastcall SetBounded(const System::Variant &Value);
	void __fastcall SetCardinality(const System::Variant &Value);
	void __fastcall SetFractionalDigits(const System::Variant &Value);
	void __fastcall SetLength(const System::Variant &Value);
	void __fastcall SetMaxExclusive(const System::Variant &Value);
	void __fastcall SetMaxInclusive(const System::Variant &Value);
	void __fastcall SetMaxLength(const System::Variant &Value);
	void __fastcall SetMinExclusive(const System::Variant &Value);
	void __fastcall SetMinInclusive(const System::Variant &Value);
	void __fastcall SetMinLength(const System::Variant &Value);
	void __fastcall SetNumeric(const System::Variant &Value);
	void __fastcall SetOrdered(const System::Variant &Value);
	void __fastcall SetPattern(const System::Variant &Value);
	void __fastcall SetTotalDigits(const System::Variant &Value);
	void __fastcall SetWhitespace(const System::Variant &Value);
	void __fastcall WriteFacet(const System::UnicodeString FacetName, const System::Variant &Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTypeDef(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaItem(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTypeDef(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaItem(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTypeDef() { }
	
private:
	void *__IXMLTypeDef;	// IXMLTypeDef 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EDFC121-4C43-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLTypeDef()
	{
		_di_IXMLTypeDef intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLTypeDef*(void) { return (IXMLTypeDef*)&__IXMLTypeDef; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSimpleTypeContent : public TXMLSchemaNode
{
	typedef TXMLSchemaNode inherited;
	
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSimpleTypeContent(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSimpleTypeContent(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSimpleTypeContent() { }
	
private:
	void *__IXMLSimpleContent;	// IXMLSimpleContent 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D355AA00-A9C9-4945-B97D-219A6E7E026F}
	operator _di_IXMLSimpleContent()
	{
		_di_IXMLSimpleContent intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSimpleContent*(void) { return (IXMLSimpleContent*)&__IXMLSimpleContent; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSimpleTypeRestriction : public TXMLSimpleTypeContent
{
	typedef TXMLSimpleTypeContent inherited;
	
protected:
	System::UnicodeString __fastcall GetBaseName();
	void __fastcall SetBaseName(const System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSimpleTypeRestriction(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSimpleTypeContent(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSimpleTypeRestriction(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSimpleTypeContent(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSimpleTypeRestriction() { }
	
private:
	void *__IXMLSimpleTypeRestriction;	// IXMLSimpleTypeRestriction 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7BE665E6-9D59-4E27-AF37-587A8CCA6306}
	operator _di_IXMLSimpleTypeRestriction()
	{
		_di_IXMLSimpleTypeRestriction intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSimpleTypeRestriction*(void) { return (IXMLSimpleTypeRestriction*)&__IXMLSimpleTypeRestriction; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSimpleTypeList : public TXMLSimpleTypeContent
{
	typedef TXMLSimpleTypeContent inherited;
	
protected:
	System::UnicodeString __fastcall GetItemType();
	_di_IXMLSimpleTypeDef __fastcall GetSimpleTypeNode();
	void __fastcall SetItemType(const System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSimpleTypeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSimpleTypeContent(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSimpleTypeList(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSimpleTypeContent(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSimpleTypeList() { }
	
private:
	void *__IXMLSimpleTypeList;	// IXMLSimpleTypeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0E61C20B-9773-4716-AF81-1833000F15BC}
	operator _di_IXMLSimpleTypeList()
	{
		_di_IXMLSimpleTypeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSimpleTypeList*(void) { return (IXMLSimpleTypeList*)&__IXMLSimpleTypeList; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSimpleTypeUnion : public TXMLSimpleTypeContent
{
	typedef TXMLSimpleTypeContent inherited;
	
private:
	_di_IXMLSimpleTypeDefs FSimpleTypes;
	
protected:
	System::UnicodeString __fastcall GetMemberTypes();
	_di_IXMLSimpleTypeDefs __fastcall GetSimpleTypes();
	void __fastcall SetMemberTypes(const System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSimpleTypeUnion(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSimpleTypeContent(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSimpleTypeUnion(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSimpleTypeContent(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSimpleTypeUnion() { }
	
private:
	void *__IXMLSimpleTypeUnion;	// IXMLSimpleTypeUnion 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {EA433957-14EE-4ACA-8B95-65060923EB56}
	operator _di_IXMLSimpleTypeUnion()
	{
		_di_IXMLSimpleTypeUnion intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSimpleTypeUnion*(void) { return (IXMLSimpleTypeUnion*)&__IXMLSimpleTypeUnion; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSimpleTypeDef : public TXMLTypeDef
{
	typedef TXMLTypeDef inherited;
	
protected:
	virtual _di_IXMLTypeDef __fastcall GetBaseType();
	HIDESBASE bool __fastcall IsAnonymous();
	bool __fastcall IsBuiltInType();
	virtual void __fastcall SetBaseTypeName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetFinal();
	_di_IXMLSimpleContent __fastcall GetContentNode();
	TSimpleDerivationMethod __fastcall GetDerivationMethod();
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall GetFacetParentNode(const bool Required = true);
	_di_IXMLSimpleTypeRestriction __fastcall GetRestrictionNode();
	void __fastcall SetFinal(const System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSimpleTypeDef(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLTypeDef(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSimpleTypeDef(Xml::Xmldoc::TXMLNode* HostNode) : TXMLTypeDef(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSimpleTypeDef() { }
	
private:
	void *__IXMLSimpleTypeDef;	// IXMLSimpleTypeDef 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EDFC122-4C43-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLSimpleTypeDef()
	{
		_di_IXMLSimpleTypeDef intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSimpleTypeDef*(void) { return (IXMLSimpleTypeDef*)&__IXMLSimpleTypeDef; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{33A54303-05F7-4BF3-B2BB-61F9CD3C1CBB}") IXMLComplexContent  : public IXMLSchemaNode 
{
	virtual _di_IXMLAttributeDefs __fastcall GetAttributeDefs() = 0 ;
	virtual _di_IXMLAttributeGroups __fastcall GetAttributeGroups() = 0 ;
	virtual _di_IXMLElementCompositor __fastcall GetCompositorNode() = 0 ;
	virtual _di_IXMLElementCompositors __fastcall GetCompositors() = 0 ;
	virtual TContentModel __fastcall GetContentModel() = 0 ;
	virtual _di_IXMLElementDefs __fastcall GetElementDefs() = 0 ;
	virtual _di_IXMLElementGroups __fastcall GetElementGroups() = 0 ;
	virtual _di_IXMLElementGroup __fastcall GetGroupRef() = 0 ;
	virtual void __fastcall SetContentModel(const TContentModel Value) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLComplexContent : public TXMLSchemaNode
{
	typedef TXMLSchemaNode inherited;
	
private:
	_di_IXMLAttributeDefs FAttributeDefs;
	_di_IXMLAttributeGroups FAttributeGroups;
	_di_IXMLElementCompositor FCompositorNode;
	TContentModel FContentModel;
	_di_IXMLElementGroup FGroupRef;
	
protected:
	_di_IXMLAttributeDefs __fastcall GetAttributeDefs();
	_di_IXMLAttributeGroups __fastcall GetAttributeGroups();
	_di_IXMLElementCompositor __fastcall GetCompositorNode();
	_di_IXMLElementCompositors __fastcall GetCompositors();
	TContentModel __fastcall GetContentModel();
	_di_IXMLElementDefs __fastcall GetElementDefs();
	_di_IXMLElementGroups __fastcall GetElementGroups();
	_di_IXMLElementGroup __fastcall GetGroupRef();
	void __fastcall SetContentModel(const TContentModel Value);
	
public:
	virtual void __fastcall AfterConstruction();
	__property _di_IXMLElementCompositor CompositorNode = {read=GetCompositorNode};
public:
	/* TXMLNode.Create */ inline __fastcall TXMLComplexContent(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLComplexContent(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLComplexContent() { }
	
private:
	void *__IXMLComplexContent;	// IXMLComplexContent 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {33A54303-05F7-4BF3-B2BB-61F9CD3C1CBB}
	operator _di_IXMLComplexContent()
	{
		_di_IXMLComplexContent intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLComplexContent*(void) { return (IXMLComplexContent*)&__IXMLComplexContent; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLBaseTypeIndicator : public TXMLSchemaNode
{
	typedef TXMLSchemaNode inherited;
	
protected:
	System::Variant __fastcall GetMixed();
	void __fastcall SetMixed(const System::Variant &Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLBaseTypeIndicator(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLBaseTypeIndicator(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLBaseTypeIndicator() { }
	
private:
	void *__IXMLBaseTypeIndicator;	// IXMLBaseTypeIndicator 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3DD57E4A-43AC-4C12-B878-B10C7BFE19D4}
	operator _di_IXMLBaseTypeIndicator()
	{
		_di_IXMLBaseTypeIndicator intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLBaseTypeIndicator*(void) { return (IXMLBaseTypeIndicator*)&__IXMLBaseTypeIndicator; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLComplexTypeDef : public TXMLTypeDef
{
	typedef TXMLTypeDef inherited;
	
private:
	_di_IXMLComplexContent FContentNode;
	TDerivationMethod FDerivationMethod;
	_di_IXMLAttributeDefList FAttributeDefList;
	_di_IXMLElementDefList FElementDefList;
	
protected:
	void __fastcall AttributesChanged();
	void __fastcall ChildElementsChanged();
	void __fastcall CheckContent();
	_di_IXMLComplexContent __fastcall GetContentNode();
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall GetFacetParentNode(const bool Required = true);
	bool __fastcall GetAbstract();
	_di_IXMLAttributeDefList __fastcall GetAttributeDefList();
	_di_IXMLAttributeDefs __fastcall GetAttributeDefs();
	_di_IXMLAttributeGroups __fastcall GetAttributeGroups();
	virtual _di_IXMLTypeDef __fastcall GetBaseType();
	_di_IXMLBaseTypeIndicator __fastcall GetBaseTypeIndicator();
	_di_IXMLElementCompositor __fastcall GetCompositorNode();
	_di_IXMLElementCompositors __fastcall GetCompositors();
	TContentModel __fastcall GetContentModel();
	TDerivationMethod __fastcall GetDerivationMethod();
	_di_IXMLElementDefs __fastcall GetElementDefs();
	_di_IXMLElementDefList __fastcall GetElementDefList();
	_di_IXMLElementGroups __fastcall GetElementGroups();
	_di_IXMLElementGroup __fastcall GetGroupRef();
	virtual bool __fastcall IsComplex();
	void __fastcall SetAbstract(const bool Value);
	virtual void __fastcall SetBaseTypeName(const System::UnicodeString Value);
	void __fastcall SetContentModel(const TContentModel Value);
	void __fastcall SetDerivationMethod(const TDerivationMethod Value);
	
public:
	virtual void __fastcall AfterConstruction();
	__property _di_IXMLComplexContent ContentNode = {read=GetContentNode};
public:
	/* TXMLNode.Create */ inline __fastcall TXMLComplexTypeDef(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLTypeDef(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLComplexTypeDef(Xml::Xmldoc::TXMLNode* HostNode) : TXMLTypeDef(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLComplexTypeDef() { }
	
private:
	void *__IXMLComplexTypeDef;	// IXMLComplexTypeDef 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EDFC123-4C43-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLComplexTypeDef()
	{
		_di_IXMLComplexTypeDef intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLComplexTypeDef*(void) { return (IXMLComplexTypeDef*)&__IXMLComplexTypeDef; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLTypedSchemaItem : public TXMLSchemaItem
{
	typedef TXMLSchemaItem inherited;
	
private:
	_di_IXMLTypeDef FTypeDef;
	
protected:
	void __fastcall RemoveTypeInfo();
	virtual void __fastcall SetRefItem(const _di_IXMLSchemaRefItem Value);
	_di_IXMLTypeDef __fastcall GetDataType();
	System::UnicodeString __fastcall GetDataTypeName();
	void __fastcall SetDataType(const _di_IXMLTypeDef Value);
	void __fastcall SetDataTypeName(const System::UnicodeString Value);
	__property _di_IXMLTypeDef DataType = {read=GetDataType};
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTypedSchemaItem(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaItem(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTypedSchemaItem(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaItem(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTypedSchemaItem() { }
	
private:
	void *__IXMLTypedSchemaItem;	// IXMLTypedSchemaItem 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {75D91C7E-6DFF-44CA-91E0-34E4314AE9D4}
	operator _di_IXMLTypedSchemaItem()
	{
		_di_IXMLTypedSchemaItem intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLTypedSchemaItem*(void) { return (IXMLTypedSchemaItem*)&__IXMLTypedSchemaItem; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLAttributeDef : public TXMLTypedSchemaItem
{
	typedef TXMLTypedSchemaItem inherited;
	
protected:
	virtual _di_IXMLSchemaItems __fastcall GlobalCollection();
	_di_IXMLAttributeDef __fastcall GetRef();
	System::Variant __fastcall GetUse();
	System::Variant __fastcall GetDefault();
	System::Variant __fastcall GetFixed();
	void __fastcall SetRef(const _di_IXMLAttributeDef Value);
	void __fastcall SetUse(const System::Variant &Value);
	void __fastcall SetDefault(const System::Variant &Value);
	void __fastcall SetFixed(const System::Variant &Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLAttributeDef(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLTypedSchemaItem(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLAttributeDef(Xml::Xmldoc::TXMLNode* HostNode) : TXMLTypedSchemaItem(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLAttributeDef() { }
	
private:
	void *__IXMLAttributeDef;	// IXMLAttributeDef 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EDFC125-4C43-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLAttributeDef()
	{
		_di_IXMLAttributeDef intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLAttributeDef*(void) { return (IXMLAttributeDef*)&__IXMLAttributeDef; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLElementDef : public TXMLTypedSchemaItem
{
	typedef TXMLTypedSchemaItem inherited;
	
protected:
	virtual _di_IXMLSchemaItems __fastcall GlobalCollection();
	_di_IXMLAttributeDefList __fastcall GetAttributeDefList();
	_di_IXMLElementDefList __fastcall GetChildElementList();
	System::Variant __fastcall GetMaxOccurs();
	System::Variant __fastcall GetMinOccurs();
	_di_IXMLElementDef __fastcall GetRef();
	bool __fastcall IsRepeating();
	void __fastcall SetMaxOccurs(const System::Variant &Value);
	void __fastcall SetMinOccurs(const System::Variant &Value);
	void __fastcall SetRef(const _di_IXMLElementDef Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLElementDef(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLTypedSchemaItem(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLElementDef(Xml::Xmldoc::TXMLNode* HostNode) : TXMLTypedSchemaItem(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLElementDef() { }
	
private:
	void *__IXMLElementDef;	// IXMLElementDef 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EDFC124-4C43-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLElementDef()
	{
		_di_IXMLElementDef intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLElementDef*(void) { return (IXMLElementDef*)&__IXMLElementDef; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLElementCompositor : public TXMLSchemaItem
{
	typedef TXMLSchemaItem inherited;
	
private:
	TCompositorType FCompositorType;
	_di_IXMLElementCompositors FCompositors;
	_di_IXMLElementDefs FElementDefs;
	_di_IXMLElementGroups FElementGroups;
	
protected:
	_di_IXMLElementCompositors __fastcall GetCompositors();
	TCompositorType __fastcall GetCompositorType();
	_di_IXMLElementDefs __fastcall GetElementDefs();
	_di_IXMLElementGroups __fastcall GetElementGroups();
	System::Variant __fastcall GetMaxOccurs();
	System::Variant __fastcall GetMinOccurs();
	void __fastcall SetMaxOccurs(const System::Variant &Value);
	void __fastcall SetMinOccurs(const System::Variant &Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLElementCompositor(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaItem(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLElementCompositor(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaItem(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLElementCompositor() { }
	
private:
	void *__IXMLElementCompositor;	// IXMLElementCompositor 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0B007C80-648B-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLElementCompositor()
	{
		_di_IXMLElementCompositor intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLElementCompositor*(void) { return (IXMLElementCompositor*)&__IXMLElementCompositor; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLAttributeGroup : public TXMLSchemaItem
{
	typedef TXMLSchemaItem inherited;
	
private:
	_di_IXMLAttributeDefs FAttributeDefs;
	_di_IXMLAttributeGroups FAttributeGroups;
	
protected:
	virtual _di_IXMLSchemaItems __fastcall GlobalCollection();
	_di_IXMLAttributeDefs __fastcall GetAttributeDefs();
	_di_IXMLAttributeGroups __fastcall GetAttributeGroups();
	_di_IXMLAttributeGroup __fastcall GetRef();
	void __fastcall SetRef(const _di_IXMLAttributeGroup Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLAttributeGroup(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaItem(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLAttributeGroup(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaItem(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLAttributeGroup() { }
	
private:
	void *__IXMLAttributeGroup;	// IXMLAttributeGroup 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8E5DB500-63C5-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLAttributeGroup()
	{
		_di_IXMLAttributeGroup intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLAttributeGroup*(void) { return (IXMLAttributeGroup*)&__IXMLAttributeGroup; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLElementGroup : public TXMLSchemaItem
{
	typedef TXMLSchemaItem inherited;
	
private:
	_di_IXMLElementCompositor FContentNode;
	
protected:
	virtual _di_IXMLSchemaItems __fastcall GlobalCollection();
	_di_IXMLElementCompositor __fastcall GetCompositorNode();
	_di_IXMLElementCompositors __fastcall GetElementCompositors();
	_di_IXMLElementDefs __fastcall GetElementDefs();
	_di_IXMLElementGroups __fastcall GetElementGroups();
	_di_IXMLElementGroup __fastcall GetRef();
	void __fastcall SetRef(const _di_IXMLElementGroup Value);
	
public:
	virtual void __fastcall AfterConstruction();
	__property _di_IXMLElementCompositor ContentNode = {read=GetCompositorNode};
public:
	/* TXMLNode.Create */ inline __fastcall TXMLElementGroup(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaItem(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLElementGroup(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaItem(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLElementGroup() { }
	
private:
	void *__IXMLElementGroup;	// IXMLElementGroup 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {53F27080-4DAF-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLElementGroup()
	{
		_di_IXMLElementGroup intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLElementGroup*(void) { return (IXMLElementGroup*)&__IXMLElementGroup; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLNotationDef : public TXMLSchemaItem
{
	typedef TXMLSchemaItem inherited;
	
protected:
	void __fastcall SetPublicID(const System::Variant &Value);
	void __fastcall SetSystemID(const System::Variant &Value);
	System::Variant __fastcall GetPublicID();
	System::Variant __fastcall GetSystemID();
	__property System::Variant PublicID = {read=GetPublicID, write=SetPublicID};
	__property System::Variant SystemID = {read=GetSystemID, write=SetSystemID};
public:
	/* TXMLNode.Create */ inline __fastcall TXMLNotationDef(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaItem(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLNotationDef(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaItem(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLNotationDef() { }
	
private:
	void *__IXMLNotation;	// IXMLNotation 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6BC9D168-3AA1-4F00-A025-DAD2CD02E5B3}
	operator _di_IXMLNotation()
	{
		_di_IXMLNotation intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLNotation*(void) { return (IXMLNotation*)&__IXMLNotation; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLAnnotationItem : public TXMLSchemaNode
{
	typedef TXMLSchemaNode inherited;
	
protected:
	System::Variant __fastcall GetSource();
	void __fastcall SetSource(const System::Variant &Value);
	__property System::Variant Source = {read=GetSource, write=SetSource};
public:
	/* TXMLNode.Create */ inline __fastcall TXMLAnnotationItem(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLAnnotationItem(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLAnnotationItem() { }
	
private:
	void *__IXMLDocumentation;	// IXMLDocumentation 
	void *__IXMLAppInfo;	// IXMLAppInfo 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A1562492-BC31-4727-A690-17631848C2AF}
	operator _di_IXMLDocumentation()
	{
		_di_IXMLDocumentation intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLDocumentation*(void) { return (IXMLDocumentation*)&__IXMLDocumentation; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FE7435C8-806F-441F-9195-A23F777D1954}
	operator _di_IXMLAppInfo()
	{
		_di_IXMLAppInfo intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLAppInfo*(void) { return (IXMLAppInfo*)&__IXMLAppInfo; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLAnnotation : public TXMLSchemaNode
{
	typedef TXMLSchemaNode inherited;
	
private:
	_di_IXMLAppInfoCollection FAppInfo;
	_di_IXMLDocumentationCollection FDocumentation;
	
protected:
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall CreateChildNode(const Xml::Xmldom::_di_IDOMNode ADOMNode);
	bool __fastcall HasAppInfo();
	bool __fastcall HasDocumentation();
	_di_IXMLAppInfoCollection __fastcall GetAppInfoCollection();
	_di_IXMLDocumentationCollection __fastcall GetDocumentationCollection();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLAnnotation(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLAnnotation(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLAnnotation() { }
	
private:
	void *__IXMLAnnotation;	// IXMLAnnotation 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F3A9316D-4AF3-4CD7-8C5B-DBFEF236A8DA}
	operator _di_IXMLAnnotation()
	{
		_di_IXMLAnnotation intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLAnnotation*(void) { return (IXMLAnnotation*)&__IXMLAnnotation; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLEnumeration : public TXMLSchemaNode
{
	typedef TXMLSchemaNode inherited;
	
protected:
	System::Variant __fastcall GetValue();
	void __fastcall SetValue(const System::Variant &Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLEnumeration(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLEnumeration(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLEnumeration() { }
	
private:
	void *__IXMLEnumeration;	// IXMLEnumeration 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FBF0F414-AA54-4ADD-BD64-EA15D5AD380E}
	operator _di_IXMLEnumeration()
	{
		_di_IXMLEnumeration intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLEnumeration*(void) { return (IXMLEnumeration*)&__IXMLEnumeration; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSchemaDocRefs : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IXMLSchemaDocRef __fastcall GetSchemaDocRef(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSchemaDocRefs(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSchemaDocRefs(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSchemaDocRefs() { }
	
private:
	void *__IXMLSchemaDocRefs;	// IXMLSchemaDocRefs 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3C32E7BD-5CEE-4757-9C1D-266BB11983FE}
	operator _di_IXMLSchemaDocRefs()
	{
		_di_IXMLSchemaDocRefs intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSchemaDocRefs*(void) { return (IXMLSchemaDocRefs*)&__IXMLSchemaDocRefs; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSchemaImports : public TXMLSchemaDocRefs
{
	typedef TXMLSchemaDocRefs inherited;
	
protected:
	_di_IXMLSchemaImport __fastcall Add(const System::UnicodeString SchemaLocation)/* overload */;
	_di_IXMLSchemaImport __fastcall Insert(int Index);
	_di_IXMLSchemaImport __fastcall GetItem(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSchemaImports(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaDocRefs(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSchemaImports(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaDocRefs(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSchemaImports() { }
	
private:
	void *__IXMLSchemaImports;	// IXMLSchemaImports 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EDFC126-4C43-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLSchemaImports()
	{
		_di_IXMLSchemaImports intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSchemaImports*(void) { return (IXMLSchemaImports*)&__IXMLSchemaImports; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSchemaIncludes : public TXMLSchemaDocRefs
{
	typedef TXMLSchemaDocRefs inherited;
	
protected:
	_di_IXMLSchemaInclude __fastcall Add(const System::UnicodeString SchemaLocation)/* overload */;
	_di_IXMLSchemaInclude __fastcall Insert(int Index);
	_di_IXMLSchemaInclude __fastcall GetItem(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSchemaIncludes(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaDocRefs(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSchemaIncludes(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaDocRefs(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSchemaIncludes() { }
	
private:
	void *__IXMLSchemaIncludes;	// IXMLSchemaIncludes 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7D9A30D4-007E-47C1-9BC1-AF8A1919777B}
	operator _di_IXMLSchemaIncludes()
	{
		_di_IXMLSchemaIncludes intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSchemaIncludes*(void) { return (IXMLSchemaIncludes*)&__IXMLSchemaIncludes; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSchemaItems : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
private:
	bool FIsGlobal;
	Xml::Xmldoc::TXMLNode* FSchemaDef;
	Xml::Xmldoc::TXMLNodeCollectionClass FCollectionClassType;
	
protected:
	_di_IXMLSchemaItem __fastcall GetSchemaItem(int Index);
	_di_IXMLSchemaItem __fastcall FindItem(const System::UnicodeString Name);
	int __fastcall IndexOfItem(const System::UnicodeString Name);
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall AddItem(int Index);
	_di_IXMLSchemaDef __fastcall GetSchemaDef();
	void __fastcall SetSchemaDef(const _di_IXMLSchemaDef Value);
	void __fastcall CheckParent();
	__property _di_IXMLSchemaDef SchemaDef = {read=GetSchemaDef, write=SetSchemaDef};
	__property bool IsGlobal = {read=FIsGlobal, nodefault};
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSchemaItems(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSchemaItems(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSchemaItems() { }
	
private:
	void *__IXMLSchemaItems;	// IXMLSchemaItems 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EDFC126-4C43-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLSchemaItems()
	{
		_di_IXMLSchemaItems intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSchemaItems*(void) { return (IXMLSchemaItems*)&__IXMLSchemaItems; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSimpleTypeDefs : public TXMLSchemaItems
{
	typedef TXMLSchemaItems inherited;
	
protected:
	_di_IXMLSimpleTypeDef __fastcall Add(const System::UnicodeString Name, System::UnicodeString BaseTypeName = System::UnicodeString());
	_di_IXMLSimpleTypeDef __fastcall Find(const System::UnicodeString Name);
	_di_IXMLSimpleTypeDef __fastcall GetItem(int Index);
	_di_IXMLSimpleTypeDef __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSimpleTypeDefs(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaItems(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSimpleTypeDefs(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaItems(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSimpleTypeDefs() { }
	
private:
	void *__IXMLSimpleTypeDefs;	// IXMLSimpleTypeDefs 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EDFC127-4C43-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLSimpleTypeDefs()
	{
		_di_IXMLSimpleTypeDefs intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSimpleTypeDefs*(void) { return (IXMLSimpleTypeDefs*)&__IXMLSimpleTypeDefs; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLBuiltInTypes : public TXMLSimpleTypeDefs
{
	typedef TXMLSimpleTypeDefs inherited;
	
protected:
	HIDESBASE int __fastcall IndexOfItem(const System::UnicodeString Name);
	bool __fastcall IsBuiltInTypeName(const System::UnicodeString Name);
	HIDESBASE _di_IXMLSimpleTypeDef __fastcall Add(const System::UnicodeString Name, System::UnicodeString BaseTypeName = System::UnicodeString());
	HIDESBASE _di_IXMLSimpleTypeDef __fastcall Find(const System::UnicodeString Name);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLBuiltInTypes(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSimpleTypeDefs(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLBuiltInTypes(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSimpleTypeDefs(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLBuiltInTypes() { }
	
private:
	void *__IXMLSimpleTypeDefs;	// IXMLSimpleTypeDefs 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EDFC127-4C43-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLSimpleTypeDefs()
	{
		_di_IXMLSimpleTypeDefs intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSimpleTypeDefs*(void) { return (IXMLSimpleTypeDefs*)&__IXMLSimpleTypeDefs; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLComplexTypeDefs : public TXMLSchemaItems
{
	typedef TXMLSchemaItems inherited;
	
protected:
	_di_IXMLComplexTypeDef __fastcall Add(const System::UnicodeString Name, TContentModel ContentModel = (TContentModel)(0x2))/* overload */;
	_di_IXMLComplexTypeDef __fastcall Add(const System::UnicodeString Name, const System::UnicodeString BaseTypeName, TDerivationMethod DerivationMethod = (TDerivationMethod)(0x1), TContentModel ContentModel = (TContentModel)(0x2))/* overload */;
	_di_IXMLComplexTypeDef __fastcall Find(const System::UnicodeString Name);
	_di_IXMLComplexTypeDef __fastcall GetItem(int Index);
	_di_IXMLComplexTypeDef __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLComplexTypeDefs(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaItems(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLComplexTypeDefs(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaItems(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLComplexTypeDefs() { }
	
private:
	void *__IXMLComplexTypeDefs;	// IXMLComplexTypeDefs 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EDFC128-4C43-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLComplexTypeDefs()
	{
		_di_IXMLComplexTypeDefs intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLComplexTypeDefs*(void) { return (IXMLComplexTypeDefs*)&__IXMLComplexTypeDefs; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLAttributeDefs : public TXMLSchemaItems
{
	typedef TXMLSchemaItems inherited;
	
protected:
	virtual void __fastcall ChildListNotify(Xml::Xmldoc::TNodeListOperation Operation, Xml::Xmlintf::_di_IXMLNode &Node, const System::OleVariant &IndexOrName, bool BeforeOperation);
	_di_IXMLAttributeDef __fastcall Add(const System::UnicodeString RefName)/* overload */;
	_di_IXMLAttributeDef __fastcall Add(const System::UnicodeString Name, const System::UnicodeString DataType)/* overload */;
	_di_IXMLAttributeDef __fastcall Add(const System::UnicodeString Name, bool LocalSimpleType, System::UnicodeString BaseTypeName = System::UnicodeString())/* overload */;
	_di_IXMLAttributeDef __fastcall Find(const System::UnicodeString Name);
	_di_IXMLAttributeDef __fastcall GetItem(int Index);
	_di_IXMLAttributeDef __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLAttributeDefs(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaItems(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLAttributeDefs(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaItems(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLAttributeDefs() { }
	
private:
	void *__IXMLAttributeDefs;	// IXMLAttributeDefs 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EDFC131-4C43-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLAttributeDefs()
	{
		_di_IXMLAttributeDefs intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLAttributeDefs*(void) { return (IXMLAttributeDefs*)&__IXMLAttributeDefs; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLElementDefs : public TXMLSchemaItems
{
	typedef TXMLSchemaItems inherited;
	
protected:
	virtual void __fastcall ChildListNotify(Xml::Xmldoc::TNodeListOperation Operation, Xml::Xmlintf::_di_IXMLNode &Node, const System::OleVariant &IndexOrName, bool BeforeOperation);
	void __fastcall InternalAdd(const _di_IXMLElementDef AElementDef);
	_di_IXMLElementDef __fastcall Add(const System::UnicodeString RefName)/* overload */;
	_di_IXMLElementDef __fastcall Add(const System::UnicodeString Name, const System::UnicodeString DataType)/* overload */;
	_di_IXMLElementDef __fastcall Add(const System::UnicodeString Name, bool ComplexLocalType, System::UnicodeString BaseTypeName = System::UnicodeString())/* overload */;
	_di_IXMLElementDef __fastcall Find(const System::UnicodeString Name);
	_di_IXMLElementDef __fastcall GetItem(int Index);
	_di_IXMLElementDef __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLElementDefs(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaItems(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLElementDefs(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaItems(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLElementDefs() { }
	
private:
	void *__IXMLElementDefs;	// IXMLElementDefs 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EDFC130-4C43-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLElementDefs()
	{
		_di_IXMLElementDefs intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLElementDefs*(void) { return (IXMLElementDefs*)&__IXMLElementDefs; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLElementCompositors : public TXMLSchemaItems
{
	typedef TXMLSchemaItems inherited;
	
protected:
	_di_IXMLElementCompositor __fastcall Add(TCompositorType CompositorType = (TCompositorType)(0x2));
	_di_IXMLElementCompositor __fastcall GetItem(int Index);
	_di_IXMLElementCompositor __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLElementCompositors(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaItems(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLElementCompositors(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaItems(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLElementCompositors() { }
	
private:
	void *__IXMLElementCompositors;	// IXMLElementCompositors 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0B007C81-648B-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLElementCompositors()
	{
		_di_IXMLElementCompositors intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLElementCompositors*(void) { return (IXMLElementCompositors*)&__IXMLElementCompositors; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLAttributeGroups : public TXMLSchemaItems
{
	typedef TXMLSchemaItems inherited;
	
protected:
	_di_IXMLAttributeGroup __fastcall Add();
	_di_IXMLAttributeGroup __fastcall Find(const System::UnicodeString Name);
	_di_IXMLAttributeGroup __fastcall GetItem(int Index);
	_di_IXMLAttributeGroup __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLAttributeGroups(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaItems(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLAttributeGroups(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaItems(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLAttributeGroups() { }
	
private:
	void *__IXMLAttributeGroups;	// IXMLAttributeGroups 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8E5DB501-63C5-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLAttributeGroups()
	{
		_di_IXMLAttributeGroups intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLAttributeGroups*(void) { return (IXMLAttributeGroups*)&__IXMLAttributeGroups; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLElementGroups : public TXMLSchemaItems
{
	typedef TXMLSchemaItems inherited;
	
protected:
	_di_IXMLElementGroup __fastcall Add(const System::UnicodeString NameOrRef);
	_di_IXMLElementGroup __fastcall Find(const System::UnicodeString Name);
	_di_IXMLElementGroup __fastcall GetItem(int Index);
	_di_IXMLElementGroup __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLElementGroups(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaItems(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLElementGroups(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaItems(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLElementGroups() { }
	
private:
	void *__IXMLElementGroups;	// IXMLElementGroups 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EDFC129-4C43-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLElementGroups()
	{
		_di_IXMLElementGroups intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLElementGroups*(void) { return (IXMLElementGroups*)&__IXMLElementGroups; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLNotationDefs : public TXMLSchemaItems
{
	typedef TXMLSchemaItems inherited;
	
protected:
	_di_IXMLNotation __fastcall Add(const System::UnicodeString Name, const System::UnicodeString APublicID = System::UnicodeString(), const System::UnicodeString ASystemID = System::UnicodeString());
	_di_IXMLNotation __fastcall GetItem(int Index);
	_di_IXMLNotation __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLNotationDefs(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLSchemaItems(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLNotationDefs(Xml::Xmldoc::TXMLNode* HostNode) : TXMLSchemaItems(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLNotationDefs() { }
	
private:
	void *__IXMLNotationDefs;	// IXMLNotationDefs 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6388BD4A-9E83-4249-A7F0-C8438F47D0AD}
	operator _di_IXMLNotationDefs()
	{
		_di_IXMLNotationDefs intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLNotationDefs*(void) { return (IXMLNotationDefs*)&__IXMLNotationDefs; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLAnnotationCollection : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IXMLAnnotation __fastcall Add();
	_di_IXMLAnnotation __fastcall GetItem(int Index);
	_di_IXMLAnnotation __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLAnnotationCollection(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLAnnotationCollection(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLAnnotationCollection() { }
	
private:
	void *__IXMLAnnotationItems;	// IXMLAnnotationItems 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C6414FE7-A7AD-495B-9302-2E65537FE0A1}
	operator _di_IXMLAnnotationItems()
	{
		_di_IXMLAnnotationItems intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLAnnotationItems*(void) { return (IXMLAnnotationItems*)&__IXMLAnnotationItems; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLAppInfoCollection : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IXMLAppInfo __fastcall GetAppInfo(const GUID &AppInfoType, Xml::Xmldoc::TXMLNodeClass AppInfoClassType = 0x0);
	_di_IXMLAppInfo __fastcall Add();
	_di_IXMLAppInfo __fastcall GetItem(int Index);
	_di_IXMLAppInfo __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLAppInfoCollection(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLAppInfoCollection(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLAppInfoCollection() { }
	
private:
	void *__IXMLAppInfoCollection;	// IXMLAppInfoCollection 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6C5C9808-FE59-4A7E-A38A-A17F710C0BE7}
	operator _di_IXMLAppInfoCollection()
	{
		_di_IXMLAppInfoCollection intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLAppInfoCollection*(void) { return (IXMLAppInfoCollection*)&__IXMLAppInfoCollection; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLDocumentationCollection : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IXMLDocumentation __fastcall Add();
	_di_IXMLDocumentation __fastcall GetItem(int Index);
	_di_IXMLDocumentation __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLDocumentationCollection(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLDocumentationCollection(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLDocumentationCollection() { }
	
private:
	void *__IXMLDocumentationCollection;	// IXMLDocumentationCollection 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F7820DA4-7C00-40D0-9F2C-AF726D8D4353}
	operator _di_IXMLDocumentationCollection()
	{
		_di_IXMLDocumentationCollection intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLDocumentationCollection*(void) { return (IXMLDocumentationCollection*)&__IXMLDocumentationCollection; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLEnumerationCollection : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IXMLEnumeration __fastcall Add(const System::UnicodeString Value);
	_di_IXMLEnumeration __fastcall GetItem(int Index);
	_di_IXMLEnumeration __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLEnumerationCollection(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLEnumerationCollection(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLEnumerationCollection() { }
	
private:
	void *__IXMLEnumerationCollection;	// IXMLEnumerationCollection 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3EB8EB97-1343-40E1-9E85-5E29C4EDD8C4}
	operator _di_IXMLEnumerationCollection()
	{
		_di_IXMLEnumerationCollection intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLEnumerationCollection*(void) { return (IXMLEnumerationCollection*)&__IXMLEnumerationCollection; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TAppInfoClassInfo
{
public:
	System::UnicodeString Prefix;
	System::UnicodeString NamespaceURI;
	Xml::Xmldoc::TXMLNodeClass NodeClass;
};


typedef System::DynamicArray<TAppInfoClassInfo> TAppInfoClassArray;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSchemaDef : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	_di_IXMLAnnotationItems FAnnotations;
	_di_IXMLAttributeDefs FAttributeDefs;
	_di_IXMLAttributeGroups FAttributeGroups;
	_di_IXMLSimpleTypeDefs FBuiltInTypes;
	_di_IXMLComplexTypeDefs FComplexTypes;
	_di_IXMLElementDef FDocElementDef;
	_di_IXMLElementDefs FElementDefs;
	_di_IXMLElementGroups FElementGroups;
	_di_IXMLSimpleTypeDefs FSimpleTypes;
	_di_IXMLNotationDefs FNotationDefs;
	TXMLSchemaDef* FParentSchemaDef;
	TSchemaRefType FParentRefType;
	TAppInfoClassArray FAppInfoClasses;
	_di_IXMLSchemaImports FSchemaImports;
	_di_IXMLSchemaIncludes FSchemaIncludes;
	System::UnicodeString FTargetNSPrefix;
	bool FStrictFormat;
	bool FLegacyFormat;
	bool FQualifyAnonymousTypeNames;
	
protected:
	Xml::Xmldoc::TXMLNodeClass __fastcall FindAppInfoClass(const System::UnicodeString NamespaceURI);
	TFormChoice __fastcall GetFormChoice(const System::UnicodeString ChoiceName);
	_di_IXMLSchemaDef __fastcall LoadSchemaRef(const _di_IXMLSchemaDocRef SchemaDocRef);
	bool __fastcall LocateAppInfo(const System::UnicodeString NamespaceURI, TAppInfoClassInfo &AppInfoClassInfo);
	void __fastcall SetFormChoice(const System::UnicodeString ChoiceName, const TFormChoice Value);
	_di_IXMLAnnotationItems __fastcall GetAnnotations();
	_di_IXMLAttributeDefs __fastcall GetAttributeDefs();
	TFormChoice __fastcall GetAttributeFormDefault();
	_di_IXMLAttributeGroups __fastcall GetAttributeGroups();
	_di_IXMLSimpleTypeDefs __fastcall GetBuiltInTypes();
	_di_IXMLComplexTypeDefs __fastcall GetComplexTypes();
	_di_IXMLElementDef __fastcall GetDocElementDef();
	_di_IXMLElementDefs __fastcall GetElementDefs();
	TFormChoice __fastcall GetElementFormDefault();
	_di_IXMLElementGroups __fastcall GetElementGroups();
	_di_IXMLNotationDefs __fastcall GetNotationDefs();
	_di_IXMLSchemaDef __fastcall GetParentSchemaDef();
	TSchemaRefType __fastcall GetParentRefType();
	bool __fastcall GetQualifyAnonymousTypeNames();
	_di_IXMLSchemaDoc __fastcall GetSchemaDoc();
	_di_IXMLSchemaImports __fastcall GetSchemaImports();
	_di_IXMLSchemaIncludes __fastcall GetSchemaIncludes();
	_di_IXMLSimpleTypeDefs __fastcall GetSimpleTypes();
	bool __fastcall GetStrictFormat();
	System::OleVariant __fastcall GetTargetNamespace();
	System::UnicodeString __fastcall GetTargetNSPrefix();
	System::UnicodeString __fastcall GetVersion();
	System::UnicodeString __fastcall FindNamespacePrefix(const System::UnicodeString NamespaceURI);
	System::UnicodeString __fastcall PrefixedTypeName(const System::UnicodeString TypeName);
	void __fastcall RegisterAppInfo(const System::UnicodeString NamespaceURI, const System::UnicodeString Prefix, Xml::Xmldoc::TXMLNodeClass NodeClass);
	void __fastcall SetAttributeformDefault(const TFormChoice Value);
	void __fastcall SetDocElementDef(const _di_IXMLElementDef Value);
	void __fastcall SetElementformDefault(const TFormChoice Value);
	void __fastcall SetParentSchemaDef(const _di_IXMLSchemaDef Value);
	void __fastcall SetParentRefType(const TSchemaRefType Value);
	void __fastcall SetQualifyAnonymousTypeNames(const bool Value);
	void __fastcall SetStrictFormat(const bool Value);
	void __fastcall SetTargetNamespace(const System::UnicodeString NamespaceURI, const System::UnicodeString NSPrefix);
	void __fastcall SetVersion(const System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
	__property TFormChoice AttributeFormDefault = {read=GetAttributeFormDefault, write=SetAttributeformDefault, nodefault};
	__property _di_IXMLElementDef DocElementDef = {read=GetDocElementDef, write=SetDocElementDef};
	__property TFormChoice ElementFormDefault = {read=GetElementFormDefault, write=SetElementformDefault, nodefault};
	__property bool IsLegacyFormat = {read=FLegacyFormat, nodefault};
	__property System::OleVariant TargetNamespace = {read=GetTargetNamespace};
	__property System::UnicodeString TargetNSPrefix = {read=GetTargetNSPrefix};
	__property System::UnicodeString Version = {read=GetVersion, write=SetVersion};
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSchemaDef(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSchemaDef(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSchemaDef() { }
	
private:
	void *__IXMLSchemaDef;	// IXMLSchemaDef 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EDFC132-4C43-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLSchemaDef()
	{
		_di_IXMLSchemaDef intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSchemaDef*(void) { return (IXMLSchemaDef*)&__IXMLSchemaDef; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSchemaDoc : public Xml::Xmldoc::TXMLDocument
{
	typedef Xml::Xmldoc::TXMLDocument inherited;
	
private:
	bool FWasImported;
	bool FEnableTranslation;
	
protected:
	bool __fastcall GetWasImported();
	_di_IXMLSchemaDef __fastcall GetSchemaDef();
	virtual void __fastcall CheckSchemaVersion();
	DYNAMIC void __fastcall DoAfterOpen();
	DYNAMIC void __fastcall LoadData();
	virtual void __fastcall PrepareNewSchema();
	__property bool EnableTranslation = {read=FEnableTranslation, write=FEnableTranslation, nodefault};
	
public:
	virtual void __fastcall AfterConstruction();
	DYNAMIC void __fastcall SaveToFile(const System::UnicodeString AFileName = System::UnicodeString());
public:
	/* TXMLDocument.Create */ inline __fastcall virtual TXMLSchemaDoc(System::Classes::TComponent* AOwner)/* overload */ : Xml::Xmldoc::TXMLDocument(AOwner) { }
	/* TXMLDocument.Create */ inline __fastcall TXMLSchemaDoc(const System::UnicodeString AFileName)/* overload */ : Xml::Xmldoc::TXMLDocument(AFileName) { }
	/* TXMLDocument.Destroy */ inline __fastcall virtual ~TXMLSchemaDoc() { }
	
private:
	void *__IXMLSchemaDoc;	// IXMLSchemaDoc 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {4E6B683C-15F4-4F62-9B4B-DF3130420F62}
	operator _di_IXMLSchemaDoc()
	{
		_di_IXMLSchemaDoc intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSchemaDoc*(void) { return (IXMLSchemaDoc*)&__IXMLSchemaDoc; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSchemaTranslator : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::UnicodeString FFileName;
	_di_IXMLSchemaDef FSchemaDef;
	
protected:
	virtual void __fastcall Translate(const System::UnicodeString FileName, const _di_IXMLSchemaDef SchemaDef);
	__property System::UnicodeString FileName = {read=FFileName};
	__property _di_IXMLSchemaDef SchemaDef = {read=FSchemaDef};
public:
	/* TObject.Create */ inline __fastcall TXMLSchemaTranslator() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TXMLSchemaTranslator() { }
	
private:
	void *__IXMLSchemaTranslator;	// IXMLSchemaTranslator 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9C4DB79C-1D60-4BF2-95EE-63FDF98237D0}
	operator _di_IXMLSchemaTranslator()
	{
		_di_IXMLSchemaTranslator intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSchemaTranslator*(void) { return (IXMLSchemaTranslator*)&__IXMLSchemaTranslator; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

_DECLARE_METACLASS(System::TMetaClass, TSchemaTranslatorClass);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLSchemaTranslatorFactory : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::UnicodeString FDescription;
	System::UnicodeString FExtension;
	TSchemaTranslatorClass FExportTranslatorClass;
	TSchemaTranslatorClass FImportTranslatorClass;
	
protected:
	virtual bool __fastcall CanExportFile(const System::UnicodeString FileName);
	virtual bool __fastcall CanImportFile(const System::UnicodeString FileName);
	_di_IXMLSchemaTranslator __fastcall GetExportTranslator();
	_di_IXMLSchemaTranslator __fastcall GetImportTranslator();
	System::UnicodeString __fastcall GetTranslatorDescription();
	
public:
	__fastcall TXMLSchemaTranslatorFactory(TSchemaTranslatorClass ImportClass, TSchemaTranslatorClass ExportClass, const System::UnicodeString Extension, const System::UnicodeString Description);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXMLSchemaTranslatorFactory() { }
	
private:
	void *__IXMLSchemaTranslatorFactory;	// IXMLSchemaTranslatorFactory 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {AAB226EE-51C1-4902-B883-FE538EB1F27E}
	operator _di_IXMLSchemaTranslatorFactory()
	{
		_di_IXMLSchemaTranslatorFactory intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSchemaTranslatorFactory*(void) { return (IXMLSchemaTranslatorFactory*)&__IXMLSchemaTranslatorFactory; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define SXMLSchemaExt u".xsd"
#define SXMLSchemaPrefix u"xs"
#define SXMLSchemaLocation u"schemaLocation"
#define SXMLNoNSSchemaLocation u"noNamespaceSchemaLocation"
#define SXMLSchemaURI_1999 u"http://www.w3.org/1999/XMLSchema"
#define SXMLSchemaInstURI_1999 u"http://www.w3.org/1999/XMLSchema-instance"
#define SXMLSchemaURI_2000_10 u"http://www.w3.org/2000/10/XMLSchema"
#define SXMLSchemaInstURI_2000_10 u"http://www.w3.org/2000/10/XMLSchema-instance"
#define SXMLSchemaURI_2001 u"http://www.w3.org/2001/XMLSchema"
#define SXMLSchemaInstURI u"http://www.w3.org/2001/XMLSchema-instance"
extern DELPHI_PACKAGE System::Classes::_di_IInterfaceList TranslatorList;
extern DELPHI_PACKAGE System::UnicodeString XMLSchemaURI;
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetDocumentation(_di_IXMLSchemaItem SchemaItem, bool AllEntries = false);
extern DELPHI_PACKAGE _di_IXMLSchemaDoc __fastcall GetXMLSchema(Xml::Xmldom::_di_IDOMDocument DOMDocument);
extern DELPHI_PACKAGE _di_IXMLSchemaDoc __fastcall LoadXMLSchema(const System::UnicodeString FileName);
extern DELPHI_PACKAGE _di_IXMLSchemaDoc __fastcall LoadXMLSchemaStr(const System::UnicodeString XML);
extern DELPHI_PACKAGE _di_IXMLSchemaDoc __fastcall NewXMLSchema(const System::UnicodeString TargetNamespace = System::UnicodeString(), const System::UnicodeString TNSPrefix = System::UnicodeString(), const System::UnicodeString XSDPrefix = u"xs");
extern DELPHI_PACKAGE void __fastcall SchemaValidationError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High);
extern DELPHI_PACKAGE void __fastcall SchemaParseError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High);
extern DELPHI_PACKAGE void __fastcall RegisterSchemaTranslator(const _di_IXMLSchemaTranslatorFactory TranslatorFactory);
extern DELPHI_PACKAGE void __fastcall UnRegisterSchemaTranslator(const _di_IXMLSchemaTranslatorFactory TranslatorFactory);
extern DELPHI_PACKAGE _di_IXMLSchemaTranslator __fastcall FindSchemaExporter(const System::UnicodeString FileName);
extern DELPHI_PACKAGE _di_IXMLSchemaTranslator __fastcall FindSchemaImporter(const System::UnicodeString FileName);
extern DELPHI_PACKAGE _di_IXMLSchemaItem __fastcall FindItemNS(TXMLSchemaItems* SchemaItems, const System::UnicodeString Name, const System::UnicodeString ItemNS);
}	/* namespace Xmlschema */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_XMLSCHEMA)
using namespace Xml::Xmlschema;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_XmlschemaHPP
