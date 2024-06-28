// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.WebServExp.pas' rev: 34.00 (iOS)

#ifndef Soap_WebservexpHPP
#define Soap_WebservexpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.TypInfo.hpp>
#include <Soap.IntfInfo.hpp>
#include <Soap.InvokeRegistry.hpp>
#include <Soap.WSDLBind.hpp>
#include <Soap.WSDLIntf.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.XMLSchema.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Webservexp
{
//-- forward type declarations -----------------------------------------------
struct TSchemaType;
__interface DELPHIINTERFACE IWebServExp;
typedef System::DelphiInterface<IWebServExp> _di_IWebServExp;
__interface DELPHIINTERFACE IWebServExpAccess;
typedef System::DelphiInterface<IWebServExpAccess> _di_IWebServExpAccess;
class DELPHICLASS TWebServExp;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM ArgumentType : unsigned char { argIn, argOut, argInOut, argReturn };

enum DECLSPEC_DENUM MessageType : unsigned char { mtInput, mtOutput, mtHeaderInput, mtHeaderOutput, mtFault };

struct DECLSPEC_DRECORD TSchemaType
{
public:
	System::UnicodeString TypeName;
	System::UnicodeString NameSpace;
	System::Typinfo::TTypeInfo *TypeInfo;
	System::UnicodeString NSPrefix;
	bool XSGenerated;
};


typedef System::DynamicArray<TSchemaType> TSchemaTypeArray;

__interface  INTERFACE_UUID("{77099743-C063-4174-BA64-53847693FB1A}") IWebServExp  : public System::IInterface 
{
	virtual bool __fastcall FindOrAddSchema(const System::Typinfo::PTypeInfo ATypeInfo, const System::UnicodeString TnsURI) = 0 ;
	virtual void __fastcall GenerateXMLSchema(Xml::Xmlschema::_di_IXMLSchemaDef SchemaDef, const System::Typinfo::PTypeInfo ATypeInfo, const System::Typinfo::PTypeInfo ParentInfo, System::UnicodeString Namespace) = 0 ;
};

typedef void __fastcall (__closure *TBeforePublishingTypesEvent)(const _di_IWebServExp WebServ);

typedef void __fastcall (__closure *TPublishingTypeEvent)(const _di_IWebServExp WebServ, const Xml::Xmlschema::_di_IXMLSchemaDef SchemaDef, const System::Typinfo::PTypeInfo ATypeInfo, System::UnicodeString Namespace);

typedef void __fastcall (__closure *TAfterPublishingWSDLEvent)(const Soap::Wsdlbind::_di_IWSDLDocument WSDLDoc);

__interface  INTERFACE_UUID("{1BB5EB76-AC77-47EE-BCF2-99C7B54386C3}") IWebServExpAccess  : public System::IInterface 
{
	virtual TWebServExp* __fastcall GetWebServExp() = 0 ;
};

class PASCALIMPLEMENTATION TWebServExp : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Soap::Wsdlbind::_di_IDefinition Definition;
	System::Classes::TStringList* ComplexTypeList;
	bool bHasComplexTypes;
	System::UnicodeString FServiceAddress;
	Soap::Wsdlintf::TWebServiceBindingType FBindingType;
	Soap::Wsdlintf::TWSDLElements FWSDLElements;
	Soap::Wsdlintf::TDOMStrings* FImportNames;
	Soap::Wsdlintf::TDOMStrings* FImportLocation;
	bool FArrayAsComplexContent;
	TSchemaTypeArray SchemaArray;
	System::UnicodeString FTargetNameSpace;
	TBeforePublishingTypesEvent FOnBeforePublishingTypes;
	TPublishingTypeEvent FOnPublishingType;
	TAfterPublishingWSDLEvent FOnAfterPublishingWSDL;
	void __fastcall GenerateWSDL(const Soap::Intfinfo::TIntfMetaData &IntfMD, Soap::Wsdlbind::_di_IWSDLDocument WSDLDoc, System::UnicodeString *PortNames, const int PortNames_High, System::UnicodeString *Locations, const int Locations_High);
	void __fastcall GenerateNestedArraySchema(Xml::Xmlschema::_di_IXMLSchemaDef SchemaDef, Xml::Xmlschema::_di_IXMLComplexTypeDef ComplexType, const System::Typinfo::PTypeInfo ATypeInfo, int &Dimension, System::UnicodeString Namespace);
	void __fastcall AddImports(const Soap::Intfinfo::TIntfMetaData &IntfMD, Soap::Wsdlbind::_di_IWSDLDocument WSDLDoc);
	void __fastcall AddTypes(const Soap::Intfinfo::TIntfMetaData &IntfMD, Soap::Wsdlbind::_di_IWSDLDocument WSDLDoc);
	System::UnicodeString __fastcall GetMessageName(const System::UnicodeString MethName, int MethIndex, MessageType MsgType, const System::UnicodeString ASuffix = System::UnicodeString());
	Soap::Wsdlbind::_di_IMessage __fastcall AddMessage(const Soap::Wsdlbind::_di_IMessages Messages, const System::UnicodeString Name);
	void __fastcall AddMessages(const Soap::Intfinfo::TIntfMetaData &IntfMD, Soap::Wsdlbind::_di_IWSDLDocument WSDLDoc);
	void __fastcall AddHeaders(const Soap::Intfinfo::TIntfMetaData &IntfMD, int MethIndex, const Soap::Wsdlbind::_di_IMessages Messages, const System::UnicodeString MethodExtName);
	void __fastcall AddFaultMessages(const Soap::Intfinfo::TIntfMetaData &IntfMD, int MethIndex, const Soap::Wsdlbind::_di_IMessages Messages, const System::UnicodeString MethodExtName, Soap::Wsdlbind::_di_IWSDLDocument WSDLDoc);
	void __fastcall AddPortTypes(const Soap::Intfinfo::TIntfMetaData &IntfMD, Soap::Wsdlbind::_di_IWSDLDocument WSDLDoc);
	void __fastcall AddBinding(const Soap::Intfinfo::TIntfMetaData &IntfMD, Soap::Wsdlbind::_di_IWSDLDocument WSDLDoc);
	void __fastcall AddServices(const Soap::Intfinfo::TIntfMetaData &IntfMD, Soap::Wsdlbind::_di_IWSDLDocument WSDLDoc, System::UnicodeString *PortNames, const int PortNames_High, System::UnicodeString *Locations, const int Locations_High);
	System::UnicodeString __fastcall GetXMLSchemaType(const System::Typinfo::PTypeInfo ParamTypeInfo);
	System::UnicodeString __fastcall GetXMLSchemaTypeName(const System::Typinfo::PTypeInfo ParamTypeInfo);
	bool __fastcall IsComplexType(const System::TTypeKind ParamType)/* overload */;
	bool __fastcall IsComplexType(const System::Typinfo::PTypeInfo ParamTypeInfo)/* overload */;
	void __fastcall SetBindingType(const Soap::Wsdlintf::TWebServiceBindingType Value);
	void __fastcall SetServiceAddress(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetImportNamespace(const int Index);
	void __fastcall SetImportNamespace(const int Index, const System::UnicodeString Value);
	System::UnicodeString __fastcall GetImportLocation(const int Index);
	void __fastcall SetImportLocation(const int Index, const System::UnicodeString Value);
	void __fastcall SetArrayType(const bool Value);
	System::UnicodeString __fastcall GetPrefixForURI(Xml::Xmlschema::_di_IXMLSchemaDef SchemaDef, const System::UnicodeString URI)/* overload */;
	System::UnicodeString __fastcall GetPrefixForURI(Soap::Wsdlbind::_di_IDefinition Def, const System::UnicodeString URI)/* overload */;
	System::UnicodeString __fastcall GetPrefixForTypeInfo(const System::Typinfo::PTypeInfo ATypeInfo)/* overload */;
	System::UnicodeString __fastcall AddNamespaceURI(Xml::Xmlintf::_di_IXMLNode RootNode, const System::UnicodeString URI);
	System::UnicodeString __fastcall GetNodeNameForURI(Xml::Xmlschema::_di_IXMLSchemaDef SchemaDef, const System::UnicodeString URI);
	void __fastcall GenerateArraySchema(Xml::Xmlschema::_di_IXMLSchemaDef SchemaDef, const System::Typinfo::PTypeInfo ATypeInfo, const System::UnicodeString Namespace);
	void __fastcall GenerateEnumSchema(Xml::Xmlschema::_di_IXMLSchemaDef SchemaDef, const System::Typinfo::PTypeInfo ATypeInfo, const System::UnicodeString Namespace);
	void __fastcall GenerateAliasSchema(Xml::Xmlschema::_di_IXMLSchemaDef SchemaDef, const System::Typinfo::PTypeInfo ATypeInfo, const System::UnicodeString Namespace, const System::Typinfo::PTypeInfo ABaseTypeInfo = (System::Typinfo::PTypeInfo)(0x0));
	void __fastcall GenerateClassSchema(Xml::Xmlschema::_di_IXMLSchemaDef SchemaDef, const System::Typinfo::PTypeInfo ATypeInfo, const System::Typinfo::PTypeInfo ParentInfo, const System::UnicodeString Namespace);
	void __fastcall GenerateDerivedClassSchema(Xml::Xmlschema::_di_IXMLSchemaDef SchemaDef, const System::Typinfo::PTypeInfo ParentTypeInfo, const System::UnicodeString Namespace);
	void __fastcall GetAllSchemaTypes(const Soap::Intfinfo::TIntfMetaData &IntfMD);
	void __fastcall GetSchemaTypes(const System::Typinfo::PTypeInfo ATypeInfo, const System::Typinfo::PTypeInfo ParentInfo);
	bool __fastcall FindOrAddSchema(const System::Typinfo::PTypeInfo ATypeInfo, const System::UnicodeString TnsURI);
	void __fastcall GetClassSchema(const System::Typinfo::PTypeInfo ATypeInfo, const System::Typinfo::PTypeInfo ParentInfo);
	void __fastcall GetDerivedClassSchema(const System::Typinfo::PTypeInfo ParentTypeInfo);
	bool __fastcall IsSchemaGenerated(const System::Typinfo::PTypeInfo ATypeInfo, const System::UnicodeString TnsURI);
	void __fastcall GetArraySchema(const System::Typinfo::PTypeInfo ATypeInfo);
	
public:
	__fastcall TWebServExp();
	__fastcall virtual ~TWebServExp();
	void __fastcall GetWSDLForInterface(const void * IntfTypeInfo, Soap::Wsdlbind::_di_IWSDLDocument WSDLDoc, System::UnicodeString *PortNames, const int PortNames_High, System::UnicodeString *Locations, const int Locations_High);
	void __fastcall GenerateXMLSchema(Xml::Xmlschema::_di_IXMLSchemaDef SchemaDef, const System::Typinfo::PTypeInfo ATypeInfo, const System::Typinfo::PTypeInfo ParentInfo, System::UnicodeString Namespace);
	TWebServExp* __fastcall GetWebServExp();
	__property System::UnicodeString ImportNames[const int Index] = {read=GetImportNamespace, write=SetImportNamespace};
	__property System::UnicodeString ImportLocations[const int Index] = {read=GetImportLocation, write=SetImportLocation};
	__property System::UnicodeString TargetNameSpace = {read=FTargetNameSpace, write=FTargetNameSpace};
	
__published:
	__property bool ArrayAsComplexContent = {read=FArrayAsComplexContent, write=SetArrayType, nodefault};
	__property Soap::Wsdlintf::TWebServiceBindingType BindingType = {read=FBindingType, write=SetBindingType, nodefault};
	__property System::UnicodeString ServiceAddress = {read=FServiceAddress, write=SetServiceAddress};
	__property Soap::Wsdlintf::TWSDLElements WSDLElements = {read=FWSDLElements, write=FWSDLElements, default=1};
	__property TBeforePublishingTypesEvent OnBeforePublishingTypes = {read=FOnBeforePublishingTypes, write=FOnBeforePublishingTypes};
	__property TPublishingTypeEvent OnPublishingType = {read=FOnPublishingType, write=FOnPublishingType};
	__property TAfterPublishingWSDLEvent OnAfterPublishingWSDL = {read=FOnAfterPublishingWSDL, write=FOnAfterPublishingWSDL};
private:
	void *__IWebServExpAccess;	// IWebServExpAccess 
	void *__IWebServExp;	// IWebServExp 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1BB5EB76-AC77-47EE-BCF2-99C7B54386C3}
	operator _di_IWebServExpAccess()
	{
		_di_IWebServExpAccess intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IWebServExpAccess*(void) { return (IWebServExpAccess*)&__IWebServExpAccess; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {77099743-C063-4174-BA64-53847693FB1A}
	operator _di_IWebServExp()
	{
		_di_IWebServExp intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IWebServExp*(void) { return (IWebServExp*)&__IWebServExp; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall IsBaseClassTypeInfo(const System::Typinfo::PTypeInfo ATypeInfo);
extern DELPHI_PACKAGE Soap::Wsdlintf::TWebServiceBindingType __fastcall GetBindingType(const Soap::Intfinfo::TIntfMethEntry &MethEntry, bool Input)/* overload */;
extern DELPHI_PACKAGE System::Typinfo::PTypeInfo __fastcall GetAliasBaseTypeInfo(const System::TTypeKind ParamType);
}	/* namespace Webservexp */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_WEBSERVEXP)
using namespace Soap::Webservexp;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_WebservexpHPP
