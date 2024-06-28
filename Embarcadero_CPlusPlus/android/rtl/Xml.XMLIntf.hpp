// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.XMLIntf.pas' rev: 34.00 (Android)

#ifndef Xml_XmlintfHPP
#define Xml_XmlintfHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Xml.xmldom.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Xmlintf
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EXMLDocError;
__interface DELPHIINTERFACE IXMLNode;
typedef System::DelphiInterface<IXMLNode> _di_IXMLNode;
__interface DELPHIINTERFACE IXMLNodeList;
typedef System::DelphiInterface<IXMLNodeList> _di_IXMLNodeList;
__interface DELPHIINTERFACE IXMLNodeCollection;
typedef System::DelphiInterface<IXMLNodeCollection> _di_IXMLNodeCollection;
__interface DELPHIINTERFACE IXMLDocument;
typedef System::DelphiInterface<IXMLDocument> _di_IXMLDocument;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TNodeType : unsigned char { ntReserved, ntElement, ntAttribute, ntText, ntCData, ntEntityRef, ntEntity, ntProcessingInstr, ntComment, ntDocument, ntDocType, ntDocFragment, ntNotation };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EXMLDocError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EXMLDocError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EXMLDocError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EXMLDocError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EXMLDocError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EXMLDocError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EXMLDocError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EXMLDocError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EXMLDocError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXMLDocError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXMLDocError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXMLDocError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXMLDocError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EXMLDocError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{395950C0-7E5D-11D4-83DA-00C04F60B2DD}") IXMLNode  : public System::IInterface 
{
	
public:
	System::OleVariant operator[](const System::OleVariant IndexOrName) { return this->ChildValues[IndexOrName]; }
	virtual System::OleVariant __fastcall GetAttribute(const System::UnicodeString AttrName) = 0 ;
	virtual _di_IXMLNodeList __fastcall GetAttributeNodes() = 0 ;
	virtual _di_IXMLNodeList __fastcall GetChildNodes() = 0 ;
	virtual System::OleVariant __fastcall GetChildValue(const System::OleVariant &IndexOrName) = 0 ;
	virtual _di_IXMLNodeCollection __fastcall GetCollection() = 0 ;
	virtual Xml::Xmldom::_di_IDOMNode __fastcall GetDOMNode() = 0 ;
	virtual bool __fastcall GetHasChildNodes() = 0 ;
	virtual bool __fastcall GetIsTextElement() = 0 ;
	virtual System::UnicodeString __fastcall GetLocalName() = 0 ;
	virtual System::UnicodeString __fastcall GetNamespaceURI() = 0 ;
	virtual System::UnicodeString __fastcall GetNodeName() = 0 ;
	virtual TNodeType __fastcall GetNodeType() = 0 ;
	virtual System::OleVariant __fastcall GetNodeValue() = 0 ;
	virtual _di_IXMLDocument __fastcall GetOwnerDocument() = 0 ;
	virtual _di_IXMLNode __fastcall GetParentNode() = 0 ;
	virtual System::UnicodeString __fastcall GetPrefix() = 0 ;
	virtual bool __fastcall GetReadOnly() = 0 ;
	virtual System::UnicodeString __fastcall GetText() = 0 ;
	virtual System::UnicodeString __fastcall GetXML() = 0 ;
	virtual void __fastcall SetAttribute(const System::UnicodeString AttrName, const System::OleVariant &Value) = 0 ;
	virtual void __fastcall SetChildValue(const System::OleVariant &IndexOrName, const System::OleVariant &Value) = 0 ;
	virtual void __fastcall SetNodeValue(const System::OleVariant &Value) = 0 ;
	virtual void __fastcall SetReadOnly(const bool Value) = 0 ;
	virtual void __fastcall SetText(const System::UnicodeString Value) = 0 ;
	virtual _di_IXMLNode __fastcall AddChild(const System::UnicodeString TagName, int Index = 0xffffffff) = 0 /* overload */;
	virtual _di_IXMLNode __fastcall AddChild(const System::UnicodeString TagName, const System::UnicodeString NamespaceURI, bool GenPrefix = false, int Index = 0xffffffff) = 0 /* overload */;
	virtual _di_IXMLNode __fastcall CloneNode(bool Deep) = 0 ;
	virtual void __fastcall DeclareNamespace(const System::UnicodeString Prefix, const System::UnicodeString URI) = 0 ;
	virtual System::UnicodeString __fastcall FindNamespaceURI(const System::UnicodeString TagOrPrefix) = 0 ;
	virtual _di_IXMLNode __fastcall FindNamespaceDecl(const System::UnicodeString NamespaceURI) = 0 ;
	virtual System::OleVariant __fastcall GetAttributeNS(const System::UnicodeString AttrName, const System::UnicodeString NamespaceURI) = 0 ;
	virtual bool __fastcall HasAttribute(const System::UnicodeString Name) = 0 /* overload */;
	virtual bool __fastcall HasAttribute(const System::UnicodeString Name, const System::UnicodeString NamespaceURI) = 0 /* overload */;
	virtual _di_IXMLNode __fastcall NextSibling() = 0 ;
	virtual void __fastcall Normalize() = 0 ;
	virtual _di_IXMLNode __fastcall PreviousSibling() = 0 ;
	virtual void __fastcall Resync() = 0 ;
	virtual void __fastcall SetAttributeNS(const System::UnicodeString AttrName, const System::UnicodeString NamespaceURI, const System::OleVariant &Value) = 0 ;
	virtual void __fastcall TransformNode(const _di_IXMLNode stylesheet, System::WideString &output) = 0 /* overload */;
	virtual void __fastcall TransformNode(const _di_IXMLNode stylesheet, const _di_IXMLDocument output) = 0 /* overload */;
	__property System::OleVariant Attributes[const System::UnicodeString AttrName] = {read=GetAttribute, write=SetAttribute};
	__property _di_IXMLNodeList AttributeNodes = {read=GetAttributeNodes};
	__property _di_IXMLNodeList ChildNodes = {read=GetChildNodes};
	__property System::OleVariant ChildValues[const System::OleVariant IndexOrName] = {read=GetChildValue, write=SetChildValue/*, default*/};
	__property _di_IXMLNodeCollection Collection = {read=GetCollection};
	__property Xml::Xmldom::_di_IDOMNode DOMNode = {read=GetDOMNode};
	__property _di_IXMLDocument OwnerDocument = {read=GetOwnerDocument};
	__property bool HasChildNodes = {read=GetHasChildNodes};
	__property bool IsTextElement = {read=GetIsTextElement};
	__property System::UnicodeString LocalName = {read=GetLocalName};
	__property System::UnicodeString NamespaceURI = {read=GetNamespaceURI};
	__property System::UnicodeString NodeName = {read=GetNodeName};
	__property TNodeType NodeType = {read=GetNodeType};
	__property System::OleVariant NodeValue = {read=GetNodeValue, write=SetNodeValue};
	__property _di_IXMLNode ParentNode = {read=GetParentNode};
	__property System::UnicodeString Prefix = {read=GetPrefix};
	__property bool ReadOnly = {read=GetReadOnly, write=SetReadOnly};
	__property System::UnicodeString Text = {read=GetText, write=SetText};
	__property System::UnicodeString XML = {read=GetXML};
};

__interface  INTERFACE_UUID("{395950C1-7E5D-11D4-83DA-00C04F60B2DD}") IXMLNodeList  : public System::IInterface 
{
	
public:
	_di_IXMLNode operator[](const System::OleVariant IndexOrName) { return this->Nodes[IndexOrName]; }
	virtual int __fastcall GetCount() = 0 ;
	virtual _di_IXMLNode __fastcall GetNode(const System::OleVariant &IndexOrName) = 0 ;
	virtual int __fastcall GetUpdateCount() = 0 ;
	virtual int __fastcall Add(const _di_IXMLNode Node) = 0 ;
	virtual void __fastcall BeginUpdate() = 0 ;
	virtual void __fastcall Clear() = 0 ;
	virtual int __fastcall Delete(const int Index) = 0 /* overload */;
	virtual int __fastcall Delete(const System::UnicodeString Name) = 0 /* overload */;
	virtual int __fastcall Delete(const System::UnicodeString Name, const System::UnicodeString NamespaceURI) = 0 /* overload */;
	virtual void __fastcall EndUpdate() = 0 ;
	virtual _di_IXMLNode __fastcall First() = 0 ;
	virtual _di_IXMLNode __fastcall FindNode(System::UnicodeString NodeName) = 0 /* overload */;
	virtual _di_IXMLNode __fastcall FindNode(System::UnicodeString NodeName, System::UnicodeString NamespaceURI) = 0 /* overload */;
	virtual _di_IXMLNode __fastcall FindNode(const GUID &ChildNodeType) = 0 /* overload */;
	virtual _di_IXMLNode __fastcall FindSibling(const _di_IXMLNode Node, int Delta) = 0 ;
	virtual _di_IXMLNode __fastcall Get(int Index) = 0 ;
	virtual int __fastcall IndexOf(const _di_IXMLNode Node) = 0 /* overload */;
	virtual int __fastcall IndexOf(const System::UnicodeString Name) = 0 /* overload */;
	virtual int __fastcall IndexOf(const System::UnicodeString Name, const System::UnicodeString NamespaceURI) = 0 /* overload */;
	virtual void __fastcall Insert(int Index, const _di_IXMLNode Node) = 0 ;
	virtual _di_IXMLNode __fastcall Last() = 0 ;
	virtual int __fastcall Remove(const _di_IXMLNode Node) = 0 ;
	virtual _di_IXMLNode __fastcall ReplaceNode(const _di_IXMLNode OldNode, const _di_IXMLNode NewNode) = 0 ;
	__property int Count = {read=GetCount};
	__property _di_IXMLNode Nodes[const System::OleVariant IndexOrName] = {read=GetNode/*, default*/};
	__property int UpdateCount = {read=GetUpdateCount};
};

__interface  INTERFACE_UUID("{395950C2-7E5D-11D4-83DA-00C04F60B2DD}") IXMLNodeCollection  : public IXMLNode 
{
	
public:
	_di_IXMLNode operator[](int Index) { return this->Nodes[Index]; }
	virtual int __fastcall GetCount() = 0 ;
	virtual _di_IXMLNode __fastcall GetNode(int Index) = 0 ;
	virtual void __fastcall Clear() = 0 ;
	virtual void __fastcall Delete(int Index) = 0 ;
	virtual int __fastcall Remove(const _di_IXMLNode Node) = 0 ;
	__property int Count = {read=GetCount};
	__property _di_IXMLNode Nodes[int Index] = {read=GetNode/*, default*/};
};

enum DECLSPEC_DENUM TXMLDocOption : unsigned char { doNodeAutoCreate, doNodeAutoIndent, doAttrNull, doAutoPrefix, doNamespaceDecl, doAutoSave };

typedef System::Set<TXMLDocOption, TXMLDocOption::doNodeAutoCreate, TXMLDocOption::doAutoSave> TXMLDocOptions;

enum DECLSPEC_DENUM TParseOption : unsigned char { poResolveExternals, poValidateOnParse, poPreserveWhiteSpace, poAsyncLoad };

typedef System::Set<TParseOption, TParseOption::poResolveExternals, TParseOption::poAsyncLoad> TParseOptions;

enum DECLSPEC_DENUM TXMLEncodingType : unsigned char { xetUnknown, xetUCS_4BE, xetUCS_4LE, xetUCS_4Order2134, xetUCS_4Order3412, xetUTF_16BE, xetUTF_16LE, xetUTF_8, xetUCS_4Like, xetUTF_16BELike, xetUTF_16LELike, xetUTF_8Like, xetEBCDICLike };

__interface  INTERFACE_UUID("{395950C3-7E5D-11D4-83DA-00C04F60B2DD}") IXMLDocument  : public System::IInterface 
{
	virtual bool __fastcall GetActive() = 0 ;
	virtual int __fastcall GetAsyncLoadState() = 0 ;
	virtual _di_IXMLNodeList __fastcall GetChildNodes() = 0 ;
	virtual _di_IXMLNode __fastcall GetDocumentElement() = 0 ;
	virtual _di_IXMLNode __fastcall GetDocumentNode() = 0 ;
	virtual Xml::Xmldom::_di_IDOMDocument __fastcall GetDOMDocument() = 0 ;
	virtual System::UnicodeString __fastcall GetEncoding() = 0 ;
	virtual System::UnicodeString __fastcall GetFileName() = 0 ;
	virtual bool __fastcall GetModified() = 0 ;
	virtual System::UnicodeString __fastcall GetNodeIndentStr() = 0 ;
	virtual TXMLDocOptions __fastcall GetOptions() = 0 ;
	virtual TParseOptions __fastcall GetParseOptions() = 0 ;
	virtual System::UnicodeString __fastcall GetSchemaRef() = 0 ;
	virtual System::UnicodeString __fastcall GetStandAlone() = 0 ;
	virtual System::UnicodeString __fastcall GetVersion() = 0 ;
	virtual System::Classes::TStrings* __fastcall GetXML() = 0 ;
	virtual void __fastcall SetActive(const bool Value) = 0 ;
	virtual void __fastcall SetDocumentElement(const _di_IXMLNode Value) = 0 ;
	virtual void __fastcall SetDOMDocument(const Xml::Xmldom::_di_IDOMDocument Value) = 0 ;
	virtual void __fastcall SetEncoding(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetFileName(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetNodeIndentStr(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetOptions(const TXMLDocOptions Value) = 0 ;
	virtual void __fastcall SetParseOptions(const TParseOptions Value) = 0 ;
	virtual void __fastcall SetStandAlone(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetVersion(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetXML(System::Classes::TStrings* const Value) = 0 ;
	virtual _di_IXMLNode __fastcall AddChild(const System::UnicodeString TagName) = 0 /* overload */;
	virtual _di_IXMLNode __fastcall AddChild(const System::UnicodeString TagName, const System::UnicodeString NamespaceURI) = 0 /* overload */;
	virtual _di_IXMLNode __fastcall CreateElement(const System::UnicodeString TagOrData, const System::UnicodeString NamespaceURI) = 0 ;
	virtual _di_IXMLNode __fastcall CreateNode(const System::UnicodeString NameOrData, TNodeType NodeType = (TNodeType)(0x1), const System::UnicodeString AddlData = System::UnicodeString()) = 0 ;
	virtual System::UnicodeString __fastcall GeneratePrefix(const _di_IXMLNode Node) = 0 ;
	virtual _di_IXMLNode __fastcall GetDocBinding(const System::UnicodeString TagName, System::TClass DocNodeClass, System::UnicodeString NamespaceURI = System::UnicodeString()) = 0 ;
	virtual bool __fastcall IsEmptyDoc() = 0 ;
	virtual void __fastcall LoadFromFile(const System::UnicodeString AFileName) = 0 ;
	virtual void __fastcall LoadFromStream(System::Classes::TStream* const Stream, TXMLEncodingType EncodingType = (TXMLEncodingType)(0x0)) = 0 ;
	virtual void __fastcall LoadFromXML(const System::AnsiString XML) = 0 /* overload */;
	virtual void __fastcall LoadFromXML(const System::UnicodeString XML) = 0 /* overload */;
	virtual void __fastcall Refresh() = 0 ;
	virtual void __fastcall RegisterDocBinding(const System::UnicodeString TagName, System::TClass DocNodeClass, System::UnicodeString NamespaceURI = System::UnicodeString()) = 0 ;
	virtual void __fastcall Resync() = 0 ;
	virtual void __fastcall SaveToFile(const System::UnicodeString AFileName) = 0 ;
	virtual void __fastcall SaveToStream(System::Classes::TStream* const Stream) = 0 ;
	virtual void __fastcall SaveToXML(System::UnicodeString &XML) = 0 /* overload */;
	virtual void __fastcall SaveToXML(System::WideString &XML) = 0 /* overload */;
	virtual void __fastcall SaveToXML(System::UTF8String &XML) = 0 /* overload */;
	virtual void __fastcall SetOnAsyncLoad(const Xml::Xmldom::TAsyncEventHandler Value) = 0 ;
	__property bool Active = {read=GetActive, write=SetActive};
	__property int AsyncLoadState = {read=GetAsyncLoadState};
	__property _di_IXMLNodeList ChildNodes = {read=GetChildNodes};
	__property _di_IXMLNode DocumentElement = {read=GetDocumentElement, write=SetDocumentElement};
	__property Xml::Xmldom::_di_IDOMDocument DOMDocument = {read=GetDOMDocument, write=SetDOMDocument};
	__property System::UnicodeString Encoding = {read=GetEncoding, write=SetEncoding};
	__property System::UnicodeString FileName = {read=GetFileName, write=SetFileName};
	__property bool Modified = {read=GetModified};
	__property _di_IXMLNode Node = {read=GetDocumentNode};
	__property System::UnicodeString NodeIndentStr = {read=GetNodeIndentStr, write=SetNodeIndentStr};
	__property TXMLDocOptions Options = {read=GetOptions, write=SetOptions};
	__property TParseOptions ParseOptions = {read=GetParseOptions, write=SetParseOptions};
	__property System::UnicodeString SchemaRef = {read=GetSchemaRef};
	__property System::UnicodeString StandAlone = {read=GetStandAlone, write=SetStandAlone};
	__property System::UnicodeString Version = {read=GetVersion, write=SetVersion};
	__property System::Classes::TStrings* XML = {read=GetXML, write=SetXML};
};

typedef System::StaticArray<System::UnicodeString, 13> Xml_Xmlintf__2;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Xml_Xmlintf__2 NodeTypeNames;
}	/* namespace Xmlintf */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_XMLINTF)
using namespace Xml::Xmlintf;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_XmlintfHPP
