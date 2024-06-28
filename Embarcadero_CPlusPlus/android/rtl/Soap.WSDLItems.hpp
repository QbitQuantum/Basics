// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.WSDLItems.pas' rev: 34.00 (Android)

#ifndef Soap_WsdlitemsHPP
#define Soap_WsdlitemsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLSchema.hpp>
#include <Soap.HTTPUtil.hpp>
#include <Soap.WSDLBind.hpp>
#include <Soap.WSDLIntf.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <Xml.XMLDoc.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Wsdlitems
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IWSDLItems;
typedef System::DelphiInterface<IWSDLItems> _di_IWSDLItems;
__interface DELPHIINTERFACE IQualifiedName;
typedef System::DelphiInterface<IQualifiedName> _di_IQualifiedName;
__interface DELPHIINTERFACE IHeaderInfo;
typedef System::DelphiInterface<IHeaderInfo> _di_IHeaderInfo;
__interface DELPHIINTERFACE IWSDLLookup;
typedef System::DelphiInterface<IWSDLLookup> _di_IWSDLLookup;
class DELPHICLASS TWSDLItems;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{F71B4B05-C5AB-4484-B994-64F3F9E805C7}") IWSDLItems  : public System::IInterface 
{
	virtual TWSDLItems* __fastcall GetWSDLItems() = 0 ;
	virtual Soap::Wsdlbind::_di_IWSDLDocument __fastcall GetWSDLDoc() = 0 ;
	virtual void __fastcall Load(const System::UnicodeString WSDLFileName) = 0 ;
};

__interface  INTERFACE_UUID("{0173ABA2-34AB-4CB1-ADF0-AA99C98FCFBD}") IQualifiedName  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual void __fastcall SetName(const System::UnicodeString name) = 0 ;
	virtual System::UnicodeString __fastcall GetNamespace() = 0 ;
	virtual void __fastcall SetNamespace(const System::UnicodeString ns) = 0 ;
	__property System::UnicodeString Name = {read=GetName, write=SetName};
	__property System::UnicodeString Namespace = {read=GetNamespace, write=SetNamespace};
};

typedef System::DynamicArray<_di_IQualifiedName> IQualifiedNameArray;

__interface  INTERFACE_UUID("{3331A5D4-BA6D-4E76-80F3-279DB879EDCB}") IHeaderInfo  : public System::IInterface 
{
	virtual Soap::Wsdlbind::_di_IPart __fastcall GetPart() = 0 ;
	virtual void __fastcall SetPart(const Soap::Wsdlbind::_di_IPart P) = 0 ;
	virtual bool __fastcall GetRequired() = 0 ;
	virtual void __fastcall SetRequired(bool Req) = 0 ;
	virtual System::UnicodeString __fastcall GetUse() = 0 ;
	virtual void __fastcall SetUse(const System::UnicodeString U) = 0 ;
	virtual System::UnicodeString __fastcall GetEncodingStyle() = 0 ;
	virtual void __fastcall SetEncodingStyle(const System::UnicodeString EncStyl) = 0 ;
	virtual System::UnicodeString __fastcall GetNamespace() = 0 ;
	virtual void __fastcall SetNamespace(const System::UnicodeString N) = 0 ;
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual void __fastcall SetName(const System::UnicodeString N) = 0 ;
	__property Soap::Wsdlbind::_di_IPart Part = {read=GetPart, write=SetPart};
	__property bool Required = {read=GetRequired, write=SetRequired};
	__property System::UnicodeString Use = {read=GetUse, write=SetUse};
	__property System::UnicodeString EncodingStyle = {read=GetEncodingStyle, write=SetEncodingStyle};
	__property System::UnicodeString Namespace = {read=GetNamespace, write=SetNamespace};
	__property System::UnicodeString Name = {read=GetName, write=SetName};
};

typedef System::DynamicArray<_di_IHeaderInfo> IHeaderInfoArray;

enum DECLSPEC_DENUM IterateImportOptions : unsigned char { ioBeforeLoad, ioLoaded };

typedef void __fastcall (__closure *TWSDLIterateProc)(const IterateImportOptions Options, const _di_IWSDLItems WSDLItems, const Xml::Xmlschema::_di_IXMLSchemaDoc XMLSchemaDoc, const System::UnicodeString Name);

__interface  INTERFACE_UUID("{0A742759-AD54-4458-AF5E-C2BC971157D2}") IWSDLLookup  : public System::IInterface 
{
	virtual void __fastcall BuildWSDLLookup(_di_IWSDLItems WSDLItems, TWSDLIterateProc IterateProc) = 0 /* overload */;
	virtual void __fastcall BuildWSDLLookup(_di_IWSDLItems WSDLItems) = 0 /* overload */;
	virtual void __fastcall ClearWSDLLookup() = 0 ;
	virtual void __fastcall Add(const System::UnicodeString URLLocation, _di_IWSDLItems WSDLItems) = 0 ;
	virtual void __fastcall AddImport(const System::UnicodeString URLLocation, const System::UnicodeString ImportURLLocation) = 0 ;
	virtual bool __fastcall Contains(const System::UnicodeString URLLocation) = 0 ;
	virtual _di_IWSDLItems __fastcall GetWSDLItems(const System::UnicodeString URLLocation) = 0 ;
	virtual System::Generics::Collections::TList__1<System::UnicodeString>* __fastcall GetWSDLImportList(const System::UnicodeString URLLocation) = 0 ;
	virtual bool __fastcall IsEmpty() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TWSDLItems : public Soap::Wsdlbind::TWSDLDocument
{
	typedef Soap::Wsdlbind::TWSDLDocument inherited;
	
private:
	Soap::Wsdlintf::_di_IStreamLoaderCustomizer FWSDLStreamLoaderCustomizer;
	Soap::Wsdlintf::_di_IStreamLoader FWSDLStreamLoader;
	_di_IWSDLLookup FWSDLLookup;
	System::UnicodeString __fastcall GetGenericBindingAttribute(const System::UnicodeString BindingName, const System::UnicodeString NodeName, const System::UnicodeString Namespace, System::UnicodeString Attribute);
	System::UnicodeString __fastcall MakeTNSName(const System::UnicodeString Name);
	void __fastcall GetBindingOfType(const System::UnicodeString BindingTypeName, const System::UnicodeString TNS, IQualifiedNameArray &BindingArray)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetName();
	System::UnicodeString __fastcall GetTargetNamespace();
	System::UnicodeString __fastcall GetTargetNamespacePrefix();
	
public:
	__fastcall virtual TWSDLItems(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual TWSDLItems(TWSDLItems* const WSDLItems, const Soap::Wsdlintf::_di_IStreamLoader StreamLoader)/* overload */;
	TWSDLItems* __fastcall GetWSDLItems();
	Soap::Wsdlbind::_di_IWSDLDocument __fastcall GetWSDLDoc();
	void __fastcall Load(const System::UnicodeString WSDLFileName);
	bool __fastcall CompareName(const System::UnicodeString NodeName, const System::UnicodeString OtherName, const System::UnicodeString TNS = System::UnicodeString());
	void __fastcall GetServices(Soap::Wsdlintf::TDOMStrings* ServiceNames, bool QualifiedNames = false);
	Xml::Xmlintf::_di_IXMLNode __fastcall GetServiceNode(const System::UnicodeString ServiceName);
	void __fastcall GetMessages(Soap::Wsdlintf::TDOMStrings* MessageNames, bool QualifiedNames = false);
	Xml::Xmlintf::_di_IXMLNode __fastcall GetMessageNode(const System::UnicodeString MessageName);
	void __fastcall GetParts(const System::UnicodeString MessageName, Soap::Wsdlintf::TDOMStrings* PartNames, bool QualifiedNames = false);
	Xml::Xmlintf::_di_IXMLNode __fastcall GetPartNode(const System::UnicodeString MessageName, const System::UnicodeString PartName);
	bool __fastcall IsPortTypeHTTPBound(const System::UnicodeString PortType);
	void __fastcall GetPortTypes(Soap::Wsdlintf::TDOMStrings* PortTypeNames, bool SkipHttpBindings = true, bool QualifiedNames = false);
	Xml::Xmlintf::_di_IXMLNode __fastcall GetPortTypeNode(const System::UnicodeString PortTypeName);
	void __fastcall GetOperations(const System::UnicodeString PortTypeName, Soap::Wsdlintf::TDOMStrings* OperationNames, bool QualifiedNames = false);
	Xml::Xmlintf::_di_IXMLNode __fastcall GetOperationNode(const System::UnicodeString PortTypeName, const System::UnicodeString OperationName);
	void __fastcall GetPortsForService(const System::UnicodeString ServiceName, Soap::Wsdlintf::TDOMStrings* PortNames, bool SkipHttpBindings = true, bool QualifiedNames = false);
	_di_IQualifiedName __fastcall GetBindingForServicePort(const System::UnicodeString ServiceName, const System::UnicodeString PortName);
	bool __fastcall GetServiceAndPortOfBinding(const _di_IQualifiedName BindingName, System::UnicodeString &ServiceName, System::UnicodeString &PortName);
	System::UnicodeString __fastcall GetSoapAddressForServicePort(const System::UnicodeString ServiceName, const System::UnicodeString PortName, Soap::Wsdlintf::TSOAPVersion &SOAPVersion);
	void __fastcall GetImports(Soap::Wsdlintf::TDOMStrings* ImportNames);
	void __fastcall IterateImports(TWSDLIterateProc IterateProc);
	System::UnicodeString __fastcall GetLocationForImport(const System::UnicodeString ImportNameSpace);
	bool __fastcall HasTypesNode();
	void __fastcall GetSchemas(Soap::Wsdlintf::TDOMStrings* SchemaNames);
	Xml::Xmlintf::_di_IXMLNode __fastcall GetSchemaNode(const System::UnicodeString SchemaTns);
	void __fastcall GetBindings(Soap::Wsdlintf::TDOMStrings* BindingNames, bool QualifiedNames = false);
	System::UnicodeString __fastcall GetBindingType(const System::UnicodeString BindingName);
	IQualifiedNameArray __fastcall GetBindingOfType(const System::UnicodeString BindingTypeName, const System::UnicodeString TNS = System::UnicodeString())/* overload */;
	System::UnicodeString __fastcall GetSoapBindingAttribute(const System::UnicodeString BindingName, System::UnicodeString Attribute, Soap::Wsdlintf::TSOAPVersion &SOAPVersion);
	System::UnicodeString __fastcall GetHttpBindingAttribute(const System::UnicodeString BindingName, System::UnicodeString Attribute)/* overload */;
	System::UnicodeString __fastcall GetHttpBindingAttribute(const _di_IQualifiedName QualifiedName, System::UnicodeString Attribute)/* overload */;
	void __fastcall GetOperationsForBinding(const System::UnicodeString BindingName, Soap::Wsdlintf::TDOMStrings* OperationNames, bool QualifiedNames = false);
	Soap::Wsdlbind::_di_IBindingOperation __fastcall GetBindingOperationNode(const System::UnicodeString BindingName, const System::UnicodeString Operation, int OverloadIndex, /* out */ _di_IWSDLItems &ResultsWSDLItems);
	System::UnicodeString __fastcall GetSoapOperationAttribute(const System::UnicodeString BindingName, const System::UnicodeString Operation, const System::UnicodeString Attribute, int OverloadIndex, Soap::Wsdlintf::TSOAPVersion &SOAPVersion);
	System::UnicodeString __fastcall GetSoapAction(const System::UnicodeString BindingName, const System::UnicodeString Operation, int OverloadIndex, Soap::Wsdlintf::TSOAPVersion &SOAPVersion);
	System::UnicodeString __fastcall GetSoapOperationStyle(const System::UnicodeString BindingName, const System::UnicodeString Operation, int OverloadIndex, Soap::Wsdlintf::TSOAPVersion &SOAPVersion);
	void __fastcall GetSoapActionList(const System::UnicodeString BindingName, Soap::Wsdlintf::TDOMStrings* ActionList, bool QualifiedNames, Soap::Wsdlintf::TSOAPVersion &SOAPVersion);
	Xml::Xmlintf::_di_IXMLNode __fastcall GetSoapBindingIONode(const System::UnicodeString BindingName, const System::UnicodeString Operation, bool Input, int OverloadIndex, /* out */ _di_IWSDLItems &ResultsWSDLItems);
	Xml::Xmlintf::_di_IXMLNode __fastcall GetSoapBindingInputNode(const System::UnicodeString BindingName, const System::UnicodeString Operation, int OverloadIndex, /* out */ _di_IWSDLItems &ResultsWSDLItems);
	Xml::Xmlintf::_di_IXMLNode __fastcall GetSoapBindingOutputNode(const System::UnicodeString BindingName, const System::UnicodeString Operation, int OverloadIndex, /* out */ _di_IWSDLItems &ResultsWSDLItems);
	System::UnicodeString __fastcall GetSoapBodyAttribute(const System::UnicodeString BindingName, const System::UnicodeString Operation, const System::UnicodeString IOType, const System::UnicodeString Attribute, int OverloadIndex, Soap::Wsdlintf::TSOAPVersion &SOAPVersion);
	System::UnicodeString __fastcall GetSoapBodyInputAttribute(const System::UnicodeString BindingName, const System::UnicodeString Operation, const System::UnicodeString Attribute, int OverloadIndex, Soap::Wsdlintf::TSOAPVersion &SOAPVersion);
	System::UnicodeString __fastcall GetSoapBodyOutputAttribute(const System::UnicodeString BindingName, const System::UnicodeString Operation, const System::UnicodeString Attribute, int OverloadIndex, Soap::Wsdlintf::TSOAPVersion &SOAPVersion);
	System::UnicodeString __fastcall GetSoapBodyNamespace(const System::UnicodeString BindingPortType, Soap::Wsdlintf::TSOAPVersion &SOAPVersion);
	IHeaderInfoArray __fastcall GetSoapHeaders(_di_IQualifiedName BindingName, const System::UnicodeString Operation, bool Input, int OverloadIndex, const System::UnicodeString MessageName, Soap::Wsdlintf::TSOAPVersion &SOAPVersion, /* out */ _di_IWSDLItems &ResultsWSDLItems);
	IHeaderInfoArray __fastcall GetSoapInputHeaders(_di_IQualifiedName BindingName, const System::UnicodeString Operation, int OverloadIndex, const System::UnicodeString MessageName, Soap::Wsdlintf::TSOAPVersion &SOAPVersion, /* out */ _di_IWSDLItems &ResultsWSDLItems);
	IHeaderInfoArray __fastcall GetSoapOutputHeaders(_di_IQualifiedName BindingName, const System::UnicodeString Operation, int OverloadIndex, const System::UnicodeString MessageName, Soap::Wsdlintf::TSOAPVersion &SOAPVersion, /* out */ _di_IWSDLItems &ResultsWSDLItems);
	bool __fastcall GetPartsForOperation(const System::UnicodeString PortTypeName, const System::UnicodeString OperationName, int OperationIndex, Soap::Wsdlintf::TDOMStrings* PartNames);
	__property Soap::Wsdlintf::_di_IStreamLoaderCustomizer StreamLoaderCustomizer = {read=FWSDLStreamLoaderCustomizer, write=FWSDLStreamLoaderCustomizer};
	__property Soap::Wsdlintf::_di_IStreamLoader StreamLoader = {read=FWSDLStreamLoader};
	__property System::UnicodeString TargetNamespace = {read=GetTargetNamespace};
	__property _di_IWSDLLookup WSDLLookup = {read=FWSDLLookup};
public:
	/* TXMLDocument.Create */ inline __fastcall TWSDLItems(const System::UnicodeString AFileName)/* overload */ : Soap::Wsdlbind::TWSDLDocument(AFileName) { }
	/* TXMLDocument.Destroy */ inline __fastcall virtual ~TWSDLItems() { }
	
private:
	void *__IWSDLItems;	// IWSDLItems 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F71B4B05-C5AB-4484-B994-64F3F9E805C7}
	operator _di_IWSDLItems()
	{
		_di_IWSDLItems intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IWSDLItems*(void) { return (IWSDLItems*)&__IWSDLItems; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE _di_IQualifiedName __fastcall NewQualifiedName(const System::UnicodeString Name = System::UnicodeString(), const System::UnicodeString Namespace = System::UnicodeString());
extern DELPHI_PACKAGE bool __fastcall HasDefinition(const Soap::Wsdlbind::_di_IWSDLDocument WSDLDoc)/* overload */;
extern DELPHI_PACKAGE bool __fastcall HasDefinition(const _di_IWSDLItems WSDLItems)/* overload */;
}	/* namespace Wsdlitems */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_WSDLITEMS)
using namespace Soap::Wsdlitems;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_WsdlitemsHPP
