// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.WSDLBind.pas' rev: 34.00 (Windows)

#ifndef Soap_WsdlbindHPP
#define Soap_WsdlbindHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.XMLSchema.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

// URLMON.H defines a global IBinding which causes ambiguities
#if !defined(_DECLARE_USING_NAMESPACE_WSDLBIND)
  #define NO_USING_NAMESPACE_WSDLBIND
#endif

namespace Soap {
 namespace Wsdlbind {
  using Xml::Xmlintf::IXMLDocument;
 };
};

namespace Soap
{
namespace Wsdlbind
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IDocumentation;
typedef System::DelphiInterface<IDocumentation> _di_IDocumentation;
__interface DELPHIINTERFACE IDocumentationCollection;
typedef System::DelphiInterface<IDocumentationCollection> _di_IDocumentationCollection;
__interface DELPHIINTERFACE IDocumented;
typedef System::DelphiInterface<IDocumented> _di_IDocumented;
__interface DELPHIINTERFACE IImport;
typedef System::DelphiInterface<IImport> _di_IImport;
__interface DELPHIINTERFACE IImports;
typedef System::DelphiInterface<IImports> _di_IImports;
__interface DELPHIINTERFACE IXMLSchemaDefs;
typedef System::DelphiInterface<IXMLSchemaDefs> _di_IXMLSchemaDefs;
__interface DELPHIINTERFACE ITypes;
typedef System::DelphiInterface<ITypes> _di_ITypes;
__interface DELPHIINTERFACE IPart;
typedef System::DelphiInterface<IPart> _di_IPart;
__interface DELPHIINTERFACE IParts;
typedef System::DelphiInterface<IParts> _di_IParts;
__interface DELPHIINTERFACE IMessage;
typedef System::DelphiInterface<IMessage> _di_IMessage;
__interface DELPHIINTERFACE IMessages;
typedef System::DelphiInterface<IMessages> _di_IMessages;
__interface DELPHIINTERFACE IParam;
typedef System::DelphiInterface<IParam> _di_IParam;
__interface DELPHIINTERFACE IFault;
typedef System::DelphiInterface<IFault> _di_IFault;
__interface DELPHIINTERFACE IFaults;
typedef System::DelphiInterface<IFaults> _di_IFaults;
__interface DELPHIINTERFACE IOperation;
typedef System::DelphiInterface<IOperation> _di_IOperation;
__interface DELPHIINTERFACE IOperations;
typedef System::DelphiInterface<IOperations> _di_IOperations;
__interface DELPHIINTERFACE IPortType;
typedef System::DelphiInterface<IPortType> _di_IPortType;
__interface DELPHIINTERFACE IPortTypes;
typedef System::DelphiInterface<IPortTypes> _di_IPortTypes;
__interface DELPHIINTERFACE IBindingInput;
typedef System::DelphiInterface<IBindingInput> _di_IBindingInput;
__interface DELPHIINTERFACE IBindingOutput;
typedef System::DelphiInterface<IBindingOutput> _di_IBindingOutput;
__interface DELPHIINTERFACE IBindingOperation;
typedef System::DelphiInterface<IBindingOperation> _di_IBindingOperation;
__interface DELPHIINTERFACE IBindingOperations;
typedef System::DelphiInterface<IBindingOperations> _di_IBindingOperations;
__interface DELPHIINTERFACE IBinding;
typedef System::DelphiInterface<IBinding> _di_IBinding;
__interface DELPHIINTERFACE IBindings;
typedef System::DelphiInterface<IBindings> _di_IBindings;
__interface DELPHIINTERFACE IPort;
typedef System::DelphiInterface<IPort> _di_IPort;
__interface DELPHIINTERFACE IPorts;
typedef System::DelphiInterface<IPorts> _di_IPorts;
__interface DELPHIINTERFACE IService;
typedef System::DelphiInterface<IService> _di_IService;
__interface DELPHIINTERFACE IServices;
typedef System::DelphiInterface<IServices> _di_IServices;
__interface DELPHIINTERFACE IDefinition;
typedef System::DelphiInterface<IDefinition> _di_IDefinition;
__interface DELPHIINTERFACE IWSDLDocument;
typedef System::DelphiInterface<IWSDLDocument> _di_IWSDLDocument;
class DELPHICLASS TDocumentation;
class DELPHICLASS TDocumentationCollection;
class DELPHICLASS TDocumented;
class DELPHICLASS TImport;
class DELPHICLASS TImports;
class DELPHICLASS TXMLSchemaDefs;
class DELPHICLASS TTypes;
class DELPHICLASS TPart;
class DELPHICLASS TParts;
class DELPHICLASS TMessage;
class DELPHICLASS TMessages;
class DELPHICLASS TParam;
class DELPHICLASS TFault;
class DELPHICLASS TFaults;
class DELPHICLASS TOperation;
class DELPHICLASS TOperations;
class DELPHICLASS TPortType;
class DELPHICLASS TPortTypes;
class DELPHICLASS TBindingOperation;
class DELPHICLASS TBindingOperations;
class DELPHICLASS TBinding;
class DELPHICLASS TBindings;
class DELPHICLASS TPort;
class DELPHICLASS TPorts;
class DELPHICLASS TService;
class DELPHICLASS TServices;
class DELPHICLASS TDefinition;
class DELPHICLASS TWSDLDocument;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{22E6AC24-DEC1-4EB6-A305-C966250CD56F}") IDocumentation  : public Xml::Xmlintf::IXMLNode 
{
	
};

__interface  INTERFACE_UUID("{2BA090C5-A91E-42BA-928B-75FB816B195F}") IDocumentationCollection  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IDocumentation operator[](int Index) { return this->Documentation[Index]; }
	virtual _di_IDocumentation __fastcall GetDocumentation(int Index) = 0 ;
	virtual _di_IDocumentation __fastcall Add(const System::UnicodeString Text) = 0 ;
	virtual _di_IDocumentation __fastcall Insert(int Index) = 0 ;
	__property _di_IDocumentation Documentation[int Index] = {read=GetDocumentation/*, default*/};
};

__interface  INTERFACE_UUID("{DC197A33-3BB6-4415-A1E1-995FB3BE35A9}") IDocumented  : public Xml::Xmlintf::IXMLNode 
{
	virtual _di_IDocumentationCollection __fastcall GetDocumentationCollection() = 0 ;
	__property _di_IDocumentationCollection Documentation = {read=GetDocumentationCollection};
};

__interface  INTERFACE_UUID("{B50B5058-46EA-46CE-A737-23ECE26F5711}") IImport  : public IDocumented 
{
	virtual System::UnicodeString __fastcall GetNamespace() = 0 ;
	virtual System::UnicodeString __fastcall GetLocation() = 0 ;
	virtual void __fastcall SetNamespace(System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetLocation(System::UnicodeString Value) = 0 ;
	__property System::UnicodeString Namespace = {read=GetNamespace, write=SetNamespace};
	__property System::UnicodeString Location = {read=GetLocation, write=SetLocation};
};

__interface  INTERFACE_UUID("{2BA090C5-A91E-42BA-928B-75FB816B195F}") IImports  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IImport operator[](int Index) { return this->Import[Index]; }
	virtual _di_IImport __fastcall GetImport(int Index) = 0 ;
	virtual _di_IImport __fastcall Add(const System::UnicodeString Namespace, const System::UnicodeString Location) = 0 ;
	virtual _di_IImport __fastcall Insert(int Index) = 0 ;
	__property _di_IImport Import[int Index] = {read=GetImport/*, default*/};
};

__interface  INTERFACE_UUID("{9657EAAE-DEC2-4A79-AED1-9114578F72BC}") IXMLSchemaDefs  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	Xml::Xmlschema::_di_IXMLSchemaDef operator[](int Index) { return this->SchemaDef[Index]; }
	virtual Xml::Xmlschema::_di_IXMLSchemaDef __fastcall GetXMLSchemaDef(int Index) = 0 ;
	virtual Xml::Xmlschema::_di_IXMLSchemaDef __fastcall Add(const System::UnicodeString NamespaceURI = System::UnicodeString(), const System::UnicodeString TargetNamespace = System::UnicodeString()) = 0 ;
	__property Xml::Xmlschema::_di_IXMLSchemaDef SchemaDef[int Index] = {read=GetXMLSchemaDef/*, default*/};
};

__interface  INTERFACE_UUID("{AAB2EBF2-79E2-42AA-A3D2-5C4ADCF51B93}") ITypes  : public IDocumented 
{
	virtual _di_IXMLSchemaDefs __fastcall GetSchemaDefs() = 0 ;
	__property _di_IXMLSchemaDefs SchemaDefs = {read=GetSchemaDefs};
};

__interface  INTERFACE_UUID("{EFD70258-38DE-4BF8-B503-C17022588EAF}") IPart  : public IDocumented 
{
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual System::UnicodeString __fastcall GetType_() = 0 ;
	virtual System::UnicodeString __fastcall GetElement() = 0 ;
	virtual void __fastcall SetName(System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetType_(System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetElement(System::UnicodeString Value) = 0 ;
	__property System::UnicodeString Name = {read=GetName, write=SetName};
	__property System::UnicodeString Type_ = {read=GetType_, write=SetType_};
	__property System::UnicodeString Element = {read=GetElement, write=SetElement};
};

__interface  INTERFACE_UUID("{7D69B10B-77BA-43AE-8581-F2A5E3B36C95}") IParts  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IPart operator[](int Index) { return this->Part[Index]; }
	virtual _di_IPart __fastcall GetPart(int Index) = 0 ;
	virtual _di_IPart __fastcall Add(const System::UnicodeString Name, const System::UnicodeString Element, const System::UnicodeString AType = System::UnicodeString()) = 0 ;
	virtual _di_IPart __fastcall Insert(int Index) = 0 ;
	__property _di_IPart Part[int Index] = {read=GetPart/*, default*/};
};

__interface  INTERFACE_UUID("{6DD2446C-7E8C-4CBA-BCB0-C318EFFE722A}") IMessage  : public IDocumented 
{
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual _di_IParts __fastcall GetParts() = 0 ;
	virtual void __fastcall SetName(System::UnicodeString Value) = 0 ;
	__property System::UnicodeString Name = {read=GetName, write=SetName};
	__property _di_IParts Parts = {read=GetParts};
};

__interface  INTERFACE_UUID("{1716B6D5-6087-4DB3-B729-1003C7424C2B}") IMessages  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IMessage operator[](int Index) { return this->Message[Index]; }
	virtual _di_IMessage __fastcall GetMessage(int Index) = 0 ;
	virtual _di_IMessage __fastcall Add(const System::UnicodeString Name) = 0 ;
	virtual _di_IMessage __fastcall Insert(int Index) = 0 ;
	__property _di_IMessage Message[int Index] = {read=GetMessage/*, default*/};
};

__interface  INTERFACE_UUID("{66FF002F-6534-421F-93B8-57FDADBE23B5}") IParam  : public IDocumented 
{
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual System::UnicodeString __fastcall GetMessage() = 0 ;
	virtual void __fastcall SetName(System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetMessage(System::UnicodeString Value) = 0 ;
	__property System::UnicodeString Name = {read=GetName, write=SetName};
	__property System::UnicodeString Message = {read=GetMessage, write=SetMessage};
};

__interface  INTERFACE_UUID("{6B1A1E80-231D-4D0C-AFB9-9E2ECBC5A323}") IFault  : public IParam 
{
	
};

__interface  INTERFACE_UUID("{67FD5C06-F745-4AD1-8B12-92552EA4AB92}") IFaults  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IFault operator[](int Index) { return this->Fault[Index]; }
	virtual _di_IFault __fastcall GetFault(int Index) = 0 ;
	virtual _di_IFault __fastcall Add(const System::UnicodeString Name, const System::UnicodeString Message) = 0 ;
	virtual _di_IFault __fastcall Insert(int Index) = 0 ;
	__property _di_IFault Fault[int Index] = {read=GetFault/*, default*/};
};

__interface  INTERFACE_UUID("{84BC9B4C-019A-4614-A050-A0BB165E7CC2}") IOperation  : public IDocumented 
{
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual _di_IParam __fastcall GetInput() = 0 ;
	virtual _di_IParam __fastcall GetOutput() = 0 ;
	virtual _di_IFaults __fastcall GetFaults() = 0 ;
	virtual void __fastcall SetName(System::UnicodeString Value) = 0 ;
	__property System::UnicodeString Name = {read=GetName, write=SetName};
	__property _di_IParam Input = {read=GetInput};
	__property _di_IParam Output = {read=GetOutput};
	__property _di_IFaults Faults = {read=GetFaults};
};

__interface  INTERFACE_UUID("{52270B19-5C86-4C77-AF4F-A620655ED9E2}") IOperations  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IOperation operator[](int Index) { return this->Operation[Index]; }
	virtual _di_IOperation __fastcall GetOperation(int Index) = 0 ;
	virtual _di_IOperation __fastcall Add(const System::UnicodeString Name) = 0 /* overload */;
	virtual _di_IOperation __fastcall Add(const System::UnicodeString Name, const System::UnicodeString InputMessage, const System::UnicodeString InputName, const System::UnicodeString OutputMessage) = 0 /* overload */;
	virtual _di_IOperation __fastcall Insert(int Index) = 0 ;
	__property _di_IOperation Operation[int Index] = {read=GetOperation/*, default*/};
};

__interface  INTERFACE_UUID("{53334349-D65E-44A6-8FBA-3694418BA70A}") IPortType  : public IDocumented 
{
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual _di_IOperations __fastcall GetOperations() = 0 ;
	virtual void __fastcall SetName(System::UnicodeString Value) = 0 ;
	__property System::UnicodeString Name = {read=GetName, write=SetName};
	__property _di_IOperations Operations = {read=GetOperations};
};

__interface  INTERFACE_UUID("{5A702461-CE49-44FE-A665-74E7D3974FBE}") IPortTypes  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IPortType operator[](int Index) { return this->PortType[Index]; }
	virtual _di_IPortType __fastcall GetPortType(int Index) = 0 ;
	virtual _di_IPortType __fastcall Add(const System::UnicodeString Name) = 0 ;
	virtual _di_IPortType __fastcall Insert(int Index) = 0 ;
	__property _di_IPortType PortType[int Index] = {read=GetPortType/*, default*/};
};

__interface  INTERFACE_UUID("{B4EB7EA0-A298-4527-BF5B-DCC6DD36EE12}") IBindingInput  : public IParam 
{
	
};

__interface  INTERFACE_UUID("{EEA06E96-EF0D-409D-BBE2-DFE554C50F23}") IBindingOutput  : public IParam 
{
	
};

__interface  INTERFACE_UUID("{2A4A10F1-269F-427C-9FAC-305B53743F8B}") IBindingOperation  : public IDocumented 
{
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual _di_IBindingInput __fastcall GetInput() = 0 ;
	virtual _di_IBindingOutput __fastcall GetOutput() = 0 ;
	virtual _di_IFaults __fastcall GetFaults() = 0 ;
	virtual void __fastcall SetName(System::UnicodeString Value) = 0 ;
	__property System::UnicodeString Name = {read=GetName, write=SetName};
	__property _di_IBindingInput Input = {read=GetInput};
	__property _di_IBindingOutput Output = {read=GetOutput};
	__property _di_IFaults Faults = {read=GetFaults};
};

__interface  INTERFACE_UUID("{D579620B-8339-4271-98A4-D3FDBAF3B0A6}") IBindingOperations  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IBindingOperation operator[](int Index) { return this->BindingOperation[Index]; }
	virtual _di_IBindingOperation __fastcall GetBindingOperation(int Index) = 0 ;
	virtual _di_IBindingOperation __fastcall Add(const System::UnicodeString Name) = 0 ;
	virtual _di_IBindingOperation __fastcall Insert(int Index) = 0 ;
	__property _di_IBindingOperation BindingOperation[int Index] = {read=GetBindingOperation/*, default*/};
};

__interface  INTERFACE_UUID("{1910D8C3-7492-405E-9D9F-62311D24B603}") IBinding  : public IDocumented 
{
	virtual _di_IBindingOperations __fastcall GetBindingOperations() = 0 ;
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual System::UnicodeString __fastcall GetType_() = 0 ;
	virtual void __fastcall SetName(System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetType_(System::UnicodeString Value) = 0 ;
	__property _di_IBindingOperations BindingOperations = {read=GetBindingOperations};
	__property System::UnicodeString Name = {read=GetName, write=SetName};
	__property System::UnicodeString Type_ = {read=GetType_, write=SetType_};
};

__interface  INTERFACE_UUID("{C8FE02C7-D726-4214-9FF4-90782EB7ACCA}") IBindings  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IBinding operator[](int Index) { return this->Binding[Index]; }
	virtual _di_IBinding __fastcall GetBinding(int Index) = 0 ;
	virtual _di_IBinding __fastcall Add(const System::UnicodeString Name, const System::UnicodeString AType) = 0 ;
	virtual _di_IBinding __fastcall Insert(int Index) = 0 ;
	__property _di_IBinding Binding[int Index] = {read=GetBinding/*, default*/};
};

__interface  INTERFACE_UUID("{10D0E981-A053-4C0F-AE5A-785D2B0D97FD}") IPort  : public IDocumented 
{
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual System::UnicodeString __fastcall GetBinding() = 0 ;
	virtual void __fastcall SetName(System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetBinding(System::UnicodeString Value) = 0 ;
	__property System::UnicodeString Name = {read=GetName, write=SetName};
	__property System::UnicodeString Binding = {read=GetBinding, write=SetBinding};
};

__interface  INTERFACE_UUID("{360DDA1F-E58E-4355-8711-25140D488497}") IPorts  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IPort operator[](int Index) { return this->Port[Index]; }
	virtual _di_IPort __fastcall GetPort(int Index) = 0 ;
	virtual _di_IPort __fastcall Add(const System::UnicodeString Name, const System::UnicodeString ABinding) = 0 ;
	virtual _di_IPort __fastcall Insert(int Index) = 0 ;
	__property _di_IPort Port[int Index] = {read=GetPort/*, default*/};
};

__interface  INTERFACE_UUID("{360DDA1F-E58E-4355-8711-25140D488497}") IService  : public IDocumented 
{
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual _di_IPorts __fastcall GetPorts() = 0 ;
	virtual void __fastcall SetName(System::UnicodeString Value) = 0 ;
	__property System::UnicodeString Name = {read=GetName, write=SetName};
	__property _di_IPorts Ports = {read=GetPorts};
};

__interface  INTERFACE_UUID("{A791AA0C-C8C5-48A1-8B6A-DEF9302B7E17}") IServices  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IService operator[](int Index) { return this->Service[Index]; }
	virtual _di_IService __fastcall GetService(int Index) = 0 ;
	virtual _di_IService __fastcall Add(const System::UnicodeString Name) = 0 ;
	virtual _di_IService __fastcall Insert(int Index) = 0 ;
	__property _di_IService Service[int Index] = {read=GetService/*, default*/};
};

__interface  INTERFACE_UUID("{F3DF8F67-804A-40C4-A6C6-EDFBEA22FC47}") IDefinition  : public Xml::Xmlintf::IXMLNode 
{
	virtual System::UnicodeString __fastcall GetTargetNamespace() = 0 ;
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual _di_IImports __fastcall GetImports() = 0 ;
	virtual _di_ITypes __fastcall GetTypes() = 0 ;
	virtual _di_IMessages __fastcall GetMessages() = 0 ;
	virtual _di_IPortTypes __fastcall GetPortTypes() = 0 ;
	virtual _di_IBindings __fastcall GetBindings() = 0 ;
	virtual _di_IServices __fastcall GetServices() = 0 ;
	virtual void __fastcall SetTargetNamespace(System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetName(System::UnicodeString Value) = 0 ;
	__property System::UnicodeString Name = {read=GetName, write=SetName};
	__property System::UnicodeString TargetNamespace = {read=GetTargetNamespace, write=SetTargetNamespace};
	__property _di_IImports Imports = {read=GetImports};
	__property _di_ITypes Types = {read=GetTypes};
	__property _di_IMessages Messages = {read=GetMessages};
	__property _di_IPortTypes PortTypes = {read=GetPortTypes};
	__property _di_IBindings Bindings = {read=GetBindings};
	__property _di_IServices Services = {read=GetServices};
};

__interface IWSDLDocument  : public Xml::Xmlintf::IXMLDocument 
{
	virtual _di_IDefinition __fastcall GetDefinition() = 0 ;
	virtual void __fastcall SetDefinition(const _di_IDefinition Value) = 0 ;
	__property _di_IDefinition Definition = {read=GetDefinition, write=SetDefinition};
};

class PASCALIMPLEMENTATION TDocumentation : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
public:
	/* TXMLNode.Create */ inline __fastcall TDocumentation(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TDocumentation(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TDocumentation() { }
	
private:
	void *__IDocumentation;	// IDocumentation 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {22E6AC24-DEC1-4EB6-A305-C966250CD56F}
	operator _di_IDocumentation()
	{
		_di_IDocumentation intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDocumentation*(void) { return (IDocumentation*)&__IDocumentation; }
	#endif
	
};


class PASCALIMPLEMENTATION TDocumentationCollection : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IDocumentation __fastcall Add(const System::UnicodeString Text);
	_di_IDocumentation __fastcall Insert(int Index);
	_di_IDocumentation __fastcall GetDocumentation(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TDocumentationCollection(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TDocumentationCollection(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TDocumentationCollection() { }
	
private:
	void *__IDocumentationCollection;	// IDocumentationCollection 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BA090C5-A91E-42BA-928B-75FB816B195F}
	operator _di_IDocumentationCollection()
	{
		_di_IDocumentationCollection intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDocumentationCollection*(void) { return (IDocumentationCollection*)&__IDocumentationCollection; }
	#endif
	
};


class PASCALIMPLEMENTATION TDocumented : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	_di_IDocumentationCollection FDocumentation;
	
protected:
	_di_IDocumentationCollection __fastcall GetDocumentationCollection();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TDocumented(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TDocumented(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TDocumented() { }
	
private:
	void *__IDocumented;	// IDocumented 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DC197A33-3BB6-4415-A1E1-995FB3BE35A9}
	operator _di_IDocumented()
	{
		_di_IDocumented intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDocumented*(void) { return (IDocumented*)&__IDocumented; }
	#endif
	
};


class PASCALIMPLEMENTATION TImport : public TDocumented
{
	typedef TDocumented inherited;
	
protected:
	System::UnicodeString __fastcall GetNamespace();
	System::UnicodeString __fastcall GetLocation();
	void __fastcall SetNamespace(System::UnicodeString Value);
	void __fastcall SetLocation(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TImport(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TDocumented(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TImport(Xml::Xmldoc::TXMLNode* HostNode) : TDocumented(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TImport() { }
	
private:
	void *__IImport;	// IImport 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B50B5058-46EA-46CE-A737-23ECE26F5711}
	operator _di_IImport()
	{
		_di_IImport intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IImport*(void) { return (IImport*)&__IImport; }
	#endif
	
};


class PASCALIMPLEMENTATION TImports : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IImport __fastcall GetImport(int Index);
	_di_IImport __fastcall Add(const System::UnicodeString Namespace, const System::UnicodeString Location);
	_di_IImport __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TImports(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TImports(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TImports() { }
	
private:
	void *__IImports;	// IImports 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BA090C5-A91E-42BA-928B-75FB816B195F}
	operator _di_IImports()
	{
		_di_IImports intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IImports*(void) { return (IImports*)&__IImports; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLSchemaDefs : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Xml::Xmlschema::_di_IXMLSchemaDef __fastcall Add(const System::UnicodeString NamespaceURI = System::UnicodeString(), const System::UnicodeString TargetNamespace = System::UnicodeString());
	Xml::Xmlschema::_di_IXMLSchemaDef __fastcall GetXMLSchemaDef(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSchemaDefs(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSchemaDefs(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSchemaDefs() { }
	
private:
	void *__IXMLSchemaDefs;	// IXMLSchemaDefs 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9657EAAE-DEC2-4A79-AED1-9114578F72BC}
	operator _di_IXMLSchemaDefs()
	{
		_di_IXMLSchemaDefs intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLSchemaDefs*(void) { return (IXMLSchemaDefs*)&__IXMLSchemaDefs; }
	#endif
	
};


class PASCALIMPLEMENTATION TTypes : public TDocumented
{
	typedef TDocumented inherited;
	
private:
	_di_IXMLSchemaDefs FSchemaDefs;
	
protected:
	_di_IXMLSchemaDefs __fastcall GetSchemaDefs();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TTypes(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TDocumented(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TTypes(Xml::Xmldoc::TXMLNode* HostNode) : TDocumented(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TTypes() { }
	
private:
	void *__ITypes;	// ITypes 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {AAB2EBF2-79E2-42AA-A3D2-5C4ADCF51B93}
	operator _di_ITypes()
	{
		_di_ITypes intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ITypes*(void) { return (ITypes*)&__ITypes; }
	#endif
	
};


class PASCALIMPLEMENTATION TPart : public TDocumented
{
	typedef TDocumented inherited;
	
protected:
	System::UnicodeString __fastcall GetName();
	System::UnicodeString __fastcall GetType_();
	System::UnicodeString __fastcall GetElement();
	void __fastcall SetName(System::UnicodeString Value);
	void __fastcall SetType_(System::UnicodeString Value);
	void __fastcall SetElement(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TPart(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TDocumented(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TPart(Xml::Xmldoc::TXMLNode* HostNode) : TDocumented(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TPart() { }
	
private:
	void *__IPart;	// IPart 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {EFD70258-38DE-4BF8-B503-C17022588EAF}
	operator _di_IPart()
	{
		_di_IPart intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IPart*(void) { return (IPart*)&__IPart; }
	#endif
	
};


class PASCALIMPLEMENTATION TParts : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IPart __fastcall GetPart(int Index);
	_di_IPart __fastcall Add(const System::UnicodeString Name, const System::UnicodeString Element, const System::UnicodeString AType = System::UnicodeString());
	_di_IPart __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TParts(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TParts(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TParts() { }
	
private:
	void *__IParts;	// IParts 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7D69B10B-77BA-43AE-8581-F2A5E3B36C95}
	operator _di_IParts()
	{
		_di_IParts intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IParts*(void) { return (IParts*)&__IParts; }
	#endif
	
};


class PASCALIMPLEMENTATION TMessage : public TDocumented
{
	typedef TDocumented inherited;
	
private:
	_di_IParts FParts;
	
protected:
	System::UnicodeString __fastcall GetName();
	_di_IParts __fastcall GetParts();
	void __fastcall SetName(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TMessage(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TDocumented(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TMessage(Xml::Xmldoc::TXMLNode* HostNode) : TDocumented(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TMessage() { }
	
private:
	void *__IMessage;	// IMessage 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6DD2446C-7E8C-4CBA-BCB0-C318EFFE722A}
	operator _di_IMessage()
	{
		_di_IMessage intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IMessage*(void) { return (IMessage*)&__IMessage; }
	#endif
	
};


class PASCALIMPLEMENTATION TMessages : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IMessage __fastcall GetMessage(int Index);
	_di_IMessage __fastcall Add(const System::UnicodeString Name);
	_di_IMessage __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TMessages(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TMessages(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TMessages() { }
	
private:
	void *__IMessages;	// IMessages 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1716B6D5-6087-4DB3-B729-1003C7424C2B}
	operator _di_IMessages()
	{
		_di_IMessages intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IMessages*(void) { return (IMessages*)&__IMessages; }
	#endif
	
};


class PASCALIMPLEMENTATION TParam : public TDocumented
{
	typedef TDocumented inherited;
	
protected:
	System::UnicodeString __fastcall GetName();
	System::UnicodeString __fastcall GetMessage();
	void __fastcall SetName(System::UnicodeString Value);
	void __fastcall SetMessage(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TParam(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TDocumented(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TParam(Xml::Xmldoc::TXMLNode* HostNode) : TDocumented(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TParam() { }
	
private:
	void *__IBindingOutput;	// IBindingOutput 
	void *__IBindingInput;	// IBindingInput 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {EEA06E96-EF0D-409D-BBE2-DFE554C50F23}
	operator _di_IBindingOutput()
	{
		_di_IBindingOutput intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindingOutput*(void) { return (IBindingOutput*)&__IBindingOutput; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B4EB7EA0-A298-4527-BF5B-DCC6DD36EE12}
	operator _di_IBindingInput()
	{
		_di_IBindingInput intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindingInput*(void) { return (IBindingInput*)&__IBindingInput; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {66FF002F-6534-421F-93B8-57FDADBE23B5}
	operator _di_IParam()
	{
		_di_IParam intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IParam*(void) { return (IParam*)&__IBindingOutput; }
	#endif
	
};


class PASCALIMPLEMENTATION TFault : public TParam
{
	typedef TParam inherited;
	
public:
	/* TXMLNode.Create */ inline __fastcall TFault(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TParam(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TFault(Xml::Xmldoc::TXMLNode* HostNode) : TParam(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TFault() { }
	
private:
	void *__IBindingOutput;	// IBindingOutput 
	void *__IBindingInput;	// IBindingInput 
	void *__IFault;	// IFault 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {EEA06E96-EF0D-409D-BBE2-DFE554C50F23}
	operator _di_IBindingOutput()
	{
		_di_IBindingOutput intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindingOutput*(void) { return (IBindingOutput*)&__IBindingOutput; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B4EB7EA0-A298-4527-BF5B-DCC6DD36EE12}
	operator _di_IBindingInput()
	{
		_di_IBindingInput intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindingInput*(void) { return (IBindingInput*)&__IBindingInput; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6B1A1E80-231D-4D0C-AFB9-9E2ECBC5A323}
	operator _di_IFault()
	{
		_di_IFault intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IFault*(void) { return (IFault*)&__IFault; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {66FF002F-6534-421F-93B8-57FDADBE23B5}
	operator _di_IParam()
	{
		_di_IParam intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IParam*(void) { return (IParam*)&__IBindingOutput; }
	#endif
	
};


class PASCALIMPLEMENTATION TFaults : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IFault __fastcall GetFault(int Index);
	_di_IFault __fastcall Add(const System::UnicodeString Name, const System::UnicodeString Message);
	_di_IFault __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TFaults(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TFaults(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TFaults() { }
	
private:
	void *__IFaults;	// IFaults 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {67FD5C06-F745-4AD1-8B12-92552EA4AB92}
	operator _di_IFaults()
	{
		_di_IFaults intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IFaults*(void) { return (IFaults*)&__IFaults; }
	#endif
	
};


class PASCALIMPLEMENTATION TOperation : public TDocumented
{
	typedef TDocumented inherited;
	
private:
	_di_IFaults FFaults;
	
protected:
	System::UnicodeString __fastcall GetName();
	_di_IParam __fastcall GetInput();
	_di_IParam __fastcall GetOutput();
	_di_IFaults __fastcall GetFaults();
	void __fastcall SetName(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TOperation(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TDocumented(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TOperation(Xml::Xmldoc::TXMLNode* HostNode) : TDocumented(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TOperation() { }
	
private:
	void *__IOperation;	// IOperation 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {84BC9B4C-019A-4614-A050-A0BB165E7CC2}
	operator _di_IOperation()
	{
		_di_IOperation intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IOperation*(void) { return (IOperation*)&__IOperation; }
	#endif
	
};


class PASCALIMPLEMENTATION TOperations : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IOperation __fastcall Add(const System::UnicodeString Name)/* overload */;
	_di_IOperation __fastcall Add(const System::UnicodeString Name, const System::UnicodeString InputMessage, const System::UnicodeString InputName, const System::UnicodeString OutputMessage)/* overload */;
	_di_IOperation __fastcall GetOperation(int Index);
	_di_IOperation __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TOperations(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TOperations(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TOperations() { }
	
private:
	void *__IOperations;	// IOperations 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {52270B19-5C86-4C77-AF4F-A620655ED9E2}
	operator _di_IOperations()
	{
		_di_IOperations intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IOperations*(void) { return (IOperations*)&__IOperations; }
	#endif
	
};


class PASCALIMPLEMENTATION TPortType : public TDocumented
{
	typedef TDocumented inherited;
	
private:
	_di_IOperations FOperations;
	
protected:
	System::UnicodeString __fastcall GetName();
	_di_IOperations __fastcall GetOperations();
	void __fastcall SetName(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TPortType(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TDocumented(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TPortType(Xml::Xmldoc::TXMLNode* HostNode) : TDocumented(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TPortType() { }
	
private:
	void *__IPortType;	// IPortType 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {53334349-D65E-44A6-8FBA-3694418BA70A}
	operator _di_IPortType()
	{
		_di_IPortType intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IPortType*(void) { return (IPortType*)&__IPortType; }
	#endif
	
};


class PASCALIMPLEMENTATION TPortTypes : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IPortType __fastcall Add(const System::UnicodeString Name)/* overload */;
	_di_IPortType __fastcall Insert(int Index);
	_di_IPortType __fastcall GetPortType(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TPortTypes(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TPortTypes(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TPortTypes() { }
	
private:
	void *__IPortTypes;	// IPortTypes 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5A702461-CE49-44FE-A665-74E7D3974FBE}
	operator _di_IPortTypes()
	{
		_di_IPortTypes intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IPortTypes*(void) { return (IPortTypes*)&__IPortTypes; }
	#endif
	
};


class PASCALIMPLEMENTATION TBindingOperation : public TDocumented
{
	typedef TDocumented inherited;
	
private:
	_di_IFaults FFaults;
	
protected:
	System::UnicodeString __fastcall GetName();
	_di_IBindingInput __fastcall GetInput();
	_di_IBindingOutput __fastcall GetOutput();
	_di_IFaults __fastcall GetFaults();
	void __fastcall SetName(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TBindingOperation(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TDocumented(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TBindingOperation(Xml::Xmldoc::TXMLNode* HostNode) : TDocumented(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TBindingOperation() { }
	
private:
	void *__IBindingOperation;	// IBindingOperation 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2A4A10F1-269F-427C-9FAC-305B53743F8B}
	operator _di_IBindingOperation()
	{
		_di_IBindingOperation intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindingOperation*(void) { return (IBindingOperation*)&__IBindingOperation; }
	#endif
	
};


class PASCALIMPLEMENTATION TBindingOperations : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IBindingOperation __fastcall GetBindingOperation(int Index);
	_di_IBindingOperation __fastcall Add(const System::UnicodeString Name);
	_di_IBindingOperation __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TBindingOperations(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TBindingOperations(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TBindingOperations() { }
	
private:
	void *__IBindingOperations;	// IBindingOperations 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D579620B-8339-4271-98A4-D3FDBAF3B0A6}
	operator _di_IBindingOperations()
	{
		_di_IBindingOperations intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindingOperations*(void) { return (IBindingOperations*)&__IBindingOperations; }
	#endif
	
};


class PASCALIMPLEMENTATION TBinding : public TDocumented
{
	typedef TDocumented inherited;
	
private:
	_di_IBindingOperations FBindingOperations;
	
protected:
	_di_IBindingOperations __fastcall GetBindingOperations();
	System::UnicodeString __fastcall GetName();
	System::UnicodeString __fastcall GetType_();
	void __fastcall SetName(System::UnicodeString Value);
	void __fastcall SetType_(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TBinding(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TDocumented(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TBinding(Xml::Xmldoc::TXMLNode* HostNode) : TDocumented(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TBinding() { }
	
private:
	void *__IBinding;	// IBinding 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1910D8C3-7492-405E-9D9F-62311D24B603}
	operator _di_IBinding()
	{
		_di_IBinding intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBinding*(void) { return (IBinding*)&__IBinding; }
	#endif
	
};


class PASCALIMPLEMENTATION TBindings : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IBinding __fastcall GetBinding(int Index);
	_di_IBinding __fastcall Add(const System::UnicodeString Name, const System::UnicodeString AType);
	_di_IBinding __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TBindings(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TBindings(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TBindings() { }
	
private:
	void *__IBindings;	// IBindings 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C8FE02C7-D726-4214-9FF4-90782EB7ACCA}
	operator _di_IBindings()
	{
		_di_IBindings intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindings*(void) { return (IBindings*)&__IBindings; }
	#endif
	
};


class PASCALIMPLEMENTATION TPort : public TDocumented
{
	typedef TDocumented inherited;
	
protected:
	System::UnicodeString __fastcall GetName();
	System::UnicodeString __fastcall GetBinding();
	void __fastcall SetName(System::UnicodeString Value);
	void __fastcall SetBinding(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TPort(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TDocumented(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TPort(Xml::Xmldoc::TXMLNode* HostNode) : TDocumented(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TPort() { }
	
private:
	void *__IPort;	// IPort 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {10D0E981-A053-4C0F-AE5A-785D2B0D97FD}
	operator _di_IPort()
	{
		_di_IPort intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IPort*(void) { return (IPort*)&__IPort; }
	#endif
	
};


class PASCALIMPLEMENTATION TPorts : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IPort __fastcall GetPort(int Index);
	_di_IPort __fastcall Add(const System::UnicodeString Name, const System::UnicodeString Binding);
	_di_IPort __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TPorts(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TPorts(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TPorts() { }
	
private:
	void *__IPorts;	// IPorts 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {360DDA1F-E58E-4355-8711-25140D488497}
	operator _di_IPorts()
	{
		_di_IPorts intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IPorts*(void) { return (IPorts*)&__IPorts; }
	#endif
	
};


class PASCALIMPLEMENTATION TService : public TDocumented
{
	typedef TDocumented inherited;
	
private:
	_di_IPorts FPorts;
	
protected:
	System::UnicodeString __fastcall GetName();
	_di_IPorts __fastcall GetPorts();
	void __fastcall SetName(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TService(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TDocumented(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TService(Xml::Xmldoc::TXMLNode* HostNode) : TDocumented(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TService() { }
	
private:
	void *__IService;	// IService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {360DDA1F-E58E-4355-8711-25140D488497}
	operator _di_IService()
	{
		_di_IService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IService*(void) { return (IService*)&__IService; }
	#endif
	
};


class PASCALIMPLEMENTATION TServices : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IService __fastcall GetService(int Index);
	_di_IService __fastcall Add(const System::UnicodeString Name);
	_di_IService __fastcall Insert(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TServices(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TServices(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TServices() { }
	
private:
	void *__IServices;	// IServices 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A791AA0C-C8C5-48A1-8B6A-DEF9302B7E17}
	operator _di_IServices()
	{
		_di_IServices intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IServices*(void) { return (IServices*)&__IServices; }
	#endif
	
};


class PASCALIMPLEMENTATION TDefinition : public TDocumented
{
	typedef TDocumented inherited;
	
private:
	_di_IImports FImports;
	_di_IMessages FMessages;
	_di_IPortTypes FPortTypes;
	_di_IBindings FBindings;
	_di_IServices FServices;
	
protected:
	System::UnicodeString __fastcall GetTargetNamespace();
	System::UnicodeString __fastcall GetName();
	_di_IImports __fastcall GetImports();
	_di_ITypes __fastcall GetTypes();
	_di_IMessages __fastcall GetMessages();
	_di_IPortTypes __fastcall GetPortTypes();
	_di_IBindings __fastcall GetBindings();
	_di_IServices __fastcall GetServices();
	void __fastcall SetTargetNamespace(System::UnicodeString Value);
	void __fastcall SetName(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TDefinition(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TDocumented(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TDefinition(Xml::Xmldoc::TXMLNode* HostNode) : TDocumented(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TDefinition() { }
	
private:
	void *__IDefinition;	// IDefinition 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F3DF8F67-804A-40C4-A6C6-EDFBEA22FC47}
	operator _di_IDefinition()
	{
		_di_IDefinition intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDefinition*(void) { return (IDefinition*)&__IDefinition; }
	#endif
	
};


class PASCALIMPLEMENTATION TWSDLDocument : public Xml::Xmldoc::TXMLDocument
{
	typedef Xml::Xmldoc::TXMLDocument inherited;
	
protected:
	_di_IDefinition __fastcall GetDefinition();
	void __fastcall SetDefinition(const _di_IDefinition Value);
	DYNAMIC void __fastcall LoadData();
	
public:
	virtual void __fastcall AfterConstruction();
	__property _di_IDefinition Definition = {read=GetDefinition, write=SetDefinition};
public:
	/* TXMLDocument.Create */ inline __fastcall virtual TWSDLDocument(System::Classes::TComponent* AOwner)/* overload */ : Xml::Xmldoc::TXMLDocument(AOwner) { }
	/* TXMLDocument.Create */ inline __fastcall TWSDLDocument(const System::UnicodeString AFileName)/* overload */ : Xml::Xmldoc::TXMLDocument(AFileName) { }
	/* TXMLDocument.Destroy */ inline __fastcall virtual ~TWSDLDocument() { }
	
private:
	void *__IWSDLDocument;	// IWSDLDocument 
	
public:
	operator IWSDLDocument*(void) { return (IWSDLDocument*)&__IWSDLDocument; }
	
};


//-- var, const, procedure ---------------------------------------------------
#define SBinding L"binding"
#define SDefinitions L"definitions"
#define SFault L"fault"
#define SImport L"import"
#define SInput L"input"
#define SLocation L"location"
#define SMessage L"message"
#define SNamespace L"namespace"
#define SOperation L"operation"
#define SOutput L"output"
#define SPart L"part"
#define SPort L"port"
#define SPortType L"portType"
#define SService L"service"
#define SType L"type"
#define STypes L"types"
extern DELPHI_PACKAGE _di_IDefinition __fastcall GetDefinition(Xml::Xmldoc::TXMLDocument* Doc);
extern DELPHI_PACKAGE _di_IWSDLDocument __fastcall LoadWSDLDoc(const System::UnicodeString FileName);
extern DELPHI_PACKAGE _di_IWSDLDocument __fastcall NewWSDLDoc(void);
}	/* namespace Wsdlbind */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_WSDLBIND)
using namespace Soap::Wsdlbind;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_WsdlbindHPP
