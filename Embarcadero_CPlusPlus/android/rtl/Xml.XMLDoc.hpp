// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.XMLDoc.pas' rev: 34.00 (Android)

#ifndef Xml_XmldocHPP
#define Xml_XmldocHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>

//-- user supplied -----------------------------------------------------------
namespace Xml    {
namespace Xmldoc {
struct TNodeClassInfo;
__interface IXMLDocumentAccess;
__interface IXMLNodeAccess;
};
};
using Xml::Xmldoc::TNodeClassInfo;

namespace Xml
{
namespace Xmldoc
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TXMLNodeList;
struct TNodeClassInfo;
__interface DELPHIINTERFACE IXMLNodeAccess;
typedef System::DelphiInterface<IXMLNodeAccess> _di_IXMLNodeAccess;
class DELPHICLASS TXMLNode;
class DELPHICLASS TXMLNodeCollection;
__interface DELPHIINTERFACE IXMLDocumentAccess;
typedef System::DelphiInterface<IXMLDocumentAccess> _di_IXMLDocumentAccess;
class DELPHICLASS TXMLDocument;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TNodeListOperation : unsigned char { nlInsert, nlRemove, nlCreateNode };

typedef void __fastcall (__closure *TNodeListNotification)(TNodeListOperation Operation, Xml::Xmlintf::_di_IXMLNode &Node, const System::OleVariant &IndexOrName, bool BeforeOperation);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLNodeList : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Classes::_di_IInterfaceList FList;
	TNodeListNotification FNotificationProc;
	TXMLNode* FOwner;
	int FUpdateCount;
	System::UnicodeString FDefaultNamespaceURI;
	
protected:
	int __fastcall Add(const Xml::Xmlintf::_di_IXMLNode Node);
	void __fastcall BeginUpdate();
	void __fastcall Clear();
	int __fastcall Delete(const int Index)/* overload */;
	int __fastcall Delete(const System::UnicodeString Name)/* overload */;
	int __fastcall Delete(const System::UnicodeString Name, const System::UnicodeString NamespaceURI)/* overload */;
	void __fastcall EndUpdate();
	Xml::Xmlintf::_di_IXMLNode __fastcall First();
	Xml::Xmlintf::_di_IXMLNode __fastcall FindNode(System::UnicodeString NodeName)/* overload */;
	Xml::Xmlintf::_di_IXMLNode __fastcall FindNode(System::UnicodeString NodeName, System::UnicodeString NamespaceURI)/* overload */;
	Xml::Xmlintf::_di_IXMLNode __fastcall FindNode(const GUID &ChildNodeType)/* overload */;
	Xml::Xmlintf::_di_IXMLNode __fastcall FindSibling(const Xml::Xmlintf::_di_IXMLNode Node, int Delta);
	Xml::Xmlintf::_di_IXMLNode __fastcall Get(int Index);
	int __fastcall GetCount();
	Xml::Xmlintf::_di_IXMLNode __fastcall GetNode(const System::OleVariant &IndexOrName);
	int __fastcall GetUpdateCount();
	int __fastcall IndexOf(const Xml::Xmlintf::_di_IXMLNode Node)/* overload */;
	int __fastcall IndexOf(const System::UnicodeString Name)/* overload */;
	int __fastcall IndexOf(const System::UnicodeString Name, const System::UnicodeString NamespaceURI)/* overload */;
	void __fastcall Insert(int Index, const Xml::Xmlintf::_di_IXMLNode Node);
	Xml::Xmlintf::_di_IXMLNode __fastcall Last();
	int __fastcall Remove(const Xml::Xmlintf::_di_IXMLNode Node);
	Xml::Xmlintf::_di_IXMLNode __fastcall ReplaceNode(const Xml::Xmlintf::_di_IXMLNode OldNode, const Xml::Xmlintf::_di_IXMLNode NewNode);
	__property int Count = {read=GetCount, nodefault};
	__property int UpdateCount = {read=GetUpdateCount, nodefault};
	Xml::Xmlintf::_di_IXMLNode __fastcall DoNotify(TNodeListOperation Operation, const Xml::Xmlintf::_di_IXMLNode Node, const System::OleVariant &IndexOrName, bool BeforeOperation);
	__property System::UnicodeString DefaultNamespaceURI = {read=FDefaultNamespaceURI};
	int __fastcall InternalInsert(int Index, const Xml::Xmlintf::_di_IXMLNode Node);
	__property System::Classes::_di_IInterfaceList List = {read=FList};
	__property TNodeListNotification NotificationProc = {read=FNotificationProc};
	__property TXMLNode* Owner = {read=FOwner};
	
public:
	__fastcall TXMLNodeList(TXMLNode* Owner, const System::UnicodeString DefaultNamespaceURI, TNodeListNotification NotificationProc);
	__fastcall virtual ~TXMLNodeList();
private:
	void *__IXMLNodeList;	// Xml::Xmlintf::IXMLNodeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {395950C1-7E5D-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmlintf::_di_IXMLNodeList()
	{
		Xml::Xmlintf::_di_IXMLNodeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmlintf::IXMLNodeList*(void) { return (Xml::Xmlintf::IXMLNodeList*)&__IXMLNodeList; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

_DECLARE_METACLASS(System::TMetaClass, TXMLNodeClass);

typedef System::DynamicArray<TXMLNode*> TXMLNodeArray;

struct DECLSPEC_DRECORD TNodeClassInfo
{
public:
	System::UnicodeString NodeName;
	System::UnicodeString NamespaceURI;
	TXMLNodeClass NodeClass;
};


typedef System::DynamicArray<TNodeClassInfo> TNodeClassArray;

_DECLARE_METACLASS(System::TMetaClass, TXMLNodeCollectionClass);

enum DECLSPEC_DENUM TNodeChange : unsigned char { ncUpdateValue, ncInsertChild, ncRemoveChild, ncAddAttribute, ncRemoveAttribute };

__interface  INTERFACE_UUID("{6C819037-AB66-4AA8-B2A5-958EDA8627B7}") IXMLNodeAccess  : public Xml::Xmlintf::IXMLNode 
{
	HIDESBASE virtual Xml::Xmlintf::_di_IXMLNode __fastcall AddChild(const System::UnicodeString TagName, const System::UnicodeString NamespaceURI, TXMLNodeClass NodeClass, int Index = 0xffffffff) = 0 /* overload */;
	virtual void __fastcall CheckTextNode() = 0 ;
	virtual void __fastcall ClearDocumentRef() = 0 ;
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall CreateAttributeNode(const Xml::Xmldom::_di_IDOMNode ADOMNode) = 0 ;
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall CreateChildNode(const Xml::Xmldom::_di_IDOMNode ADOMNode) = 0 ;
	virtual TXMLNodeCollection* __fastcall CreateCollection(const TXMLNodeCollectionClass CollectionClass, const GUID &ItemIterface, const System::UnicodeString ItemTag, System::UnicodeString ItemNS = System::UnicodeString()) = 0 ;
	virtual Xml::Xmldom::_di_IDOMElement __fastcall DOMElement() = 0 ;
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall FindHostedNode(const TXMLNodeClass NodeClass) = 0 ;
	virtual TNodeClassArray __fastcall GetChildNodeClasses() = 0 ;
	virtual TXMLNode* __fastcall GetHostNode() = 0 ;
	virtual TXMLNode* __fastcall GetNodeObject() = 0 ;
	virtual bool __fastcall HasChildNode(const System::UnicodeString ChildTag) = 0 /* overload */;
	virtual bool __fastcall HasChildNode(const System::UnicodeString ChildTag, const System::UnicodeString NamespaceURI) = 0 /* overload */;
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall InternalAddChild(TXMLNodeClass NodeClass, const System::UnicodeString NodeName, const System::UnicodeString NamespaceURI, int Index) = 0 ;
	virtual int __fastcall NestingLevel() = 0 ;
	virtual void __fastcall RegisterChildNode(const System::UnicodeString TagName, TXMLNodeClass ChildNodeClass, System::UnicodeString NamespaceURI = System::UnicodeString()) = 0 ;
	virtual void __fastcall RegisterChildNodes(const System::UnicodeString *TagNames, const int TagNames_High, TXMLNodeClass const *NodeClasses, const int NodeClasses_High) = 0 ;
	virtual void __fastcall SetCollection(TXMLNodeCollection* const Value) = 0 ;
	virtual void __fastcall SetParentNode(TXMLNode* const Value) = 0 ;
	__property TNodeClassArray ChildNodeClasses = {read=GetChildNodeClasses};
	__property TXMLNode* HostNode = {read=GetHostNode};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLNode : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Xml::Xmlintf::_di_IXMLNodeList FAttributeNodes;
	Xml::Xmlintf::_di_IXMLNodeList FChildNodes;
	TNodeClassArray FChildNodeClasses;
	TXMLNodeCollection* FCollection;
	TXMLDocument* FDocument;
	Xml::Xmldom::_di_IDOMNode FDOMNode;
	TXMLNode* FHostNode;
	TXMLNode* FParentNode;
	TXMLNodeArray FHostedNodes;
	bool FIsDocElement;
	bool FReadOnly;
	TNodeListNotification FOnHostChildNotify;
	TNodeListNotification FOnHostAttrNotify;
	
protected:
	HIDESBASE int __stdcall _AddRef();
	HIDESBASE int __stdcall _Release();
	System::OleVariant __fastcall GetAttribute(const System::UnicodeString AttrName);
	Xml::Xmlintf::_di_IXMLNodeList __fastcall GetAttributeNodes();
	System::OleVariant __fastcall GetAttributeNS(const System::UnicodeString AttrName, const System::UnicodeString NamespaceURI);
	Xml::Xmlintf::_di_IXMLNodeList __fastcall GetChildNodes();
	System::OleVariant __fastcall GetChildValue(const System::OleVariant &IndexOrName);
	Xml::Xmlintf::_di_IXMLNodeCollection __fastcall GetCollection();
	Xml::Xmldom::_di_IDOMNode __fastcall GetDOMNode();
	bool __fastcall GetHasChildNodes();
	bool __fastcall GetIsTextElement();
	System::UnicodeString __fastcall GetLocalName();
	System::UnicodeString __fastcall GetNamespaceURI();
	System::UnicodeString __fastcall GetNodeName();
	Xml::Xmlintf::TNodeType __fastcall GetNodeType();
	System::OleVariant __fastcall GetNodeValue();
	Xml::Xmlintf::_di_IXMLDocument __fastcall GetOwnerDocument();
	Xml::Xmlintf::_di_IXMLNode __fastcall GetParentNode();
	System::UnicodeString __fastcall GetPrefix();
	bool __fastcall GetReadOnly();
	System::UnicodeString __fastcall GetText();
	System::UnicodeString __fastcall GetXML();
	void __fastcall SetAttribute(const System::UnicodeString AttrName, const System::OleVariant &Value);
	void __fastcall SetChildValue(const System::OleVariant &IndexOrName, const System::OleVariant &Value);
	void __fastcall SetNodeValue(const System::OleVariant &Value);
	void __fastcall SetReadOnly(const bool Value);
	void __fastcall SetText(const System::UnicodeString Value);
	Xml::Xmlintf::_di_IXMLNode __fastcall AddChild(const System::UnicodeString TagName, int Index = 0xffffffff)/* overload */;
	Xml::Xmlintf::_di_IXMLNode __fastcall AddChild(const System::UnicodeString TagName, const System::UnicodeString NamespaceURI, bool GenPrefix = false, int Index = 0xffffffff)/* overload */;
	Xml::Xmlintf::_di_IXMLNode __fastcall CloneNode(bool Deep);
	void __fastcall DeclareNamespace(const System::UnicodeString Prefix, const System::UnicodeString URI);
	Xml::Xmlintf::_di_IXMLNode __fastcall FindNamespaceDecl(const System::UnicodeString NamespaceURI);
	System::UnicodeString __fastcall FindNamespaceURI(const System::UnicodeString TagOrPrefix);
	bool __fastcall HasAttribute(const System::UnicodeString Name)/* overload */;
	bool __fastcall HasAttribute(const System::UnicodeString Name, const System::UnicodeString NamespaceURI)/* overload */;
	Xml::Xmlintf::_di_IXMLNode __fastcall NextSibling();
	void __fastcall Normalize();
	Xml::Xmlintf::_di_IXMLNode __fastcall PreviousSibling();
	void __fastcall Resync();
	void __fastcall SetAttributeNS(const System::UnicodeString AttrName, const System::UnicodeString NamespaceURI, const System::OleVariant &Value);
	void __fastcall TransformNode(const Xml::Xmlintf::_di_IXMLNode stylesheet, System::WideString &output)/* overload */;
	void __fastcall TransformNode(const Xml::Xmlintf::_di_IXMLNode stylesheet, const Xml::Xmlintf::_di_IXMLDocument output)/* overload */;
	Xml::Xmlintf::_di_IXMLNode __fastcall AddChild(const System::UnicodeString TagName, const System::UnicodeString NamespaceURI, TXMLNodeClass NodeClass, int Index = 0xffffffff)/* overload */;
	void __fastcall CheckTextNode();
	void __fastcall ClearDocumentRef();
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall CreateAttributeNode(const Xml::Xmldom::_di_IDOMNode ADOMNode);
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall CreateChildNode(const Xml::Xmldom::_di_IDOMNode ADOMNode);
	TXMLNodeCollection* __fastcall CreateCollection(const TXMLNodeCollectionClass CollectionClass, const GUID &ItemInterface, const System::UnicodeString ItemTag, System::UnicodeString ItemNS = System::UnicodeString());
	Xml::Xmldom::_di_IDOMElement __fastcall DOMElement();
	Xml::Xmlintf::_di_IXMLNode __fastcall FindHostedNode(const TXMLNodeClass NodeClass);
	TNodeClassArray __fastcall GetChildNodeClasses();
	TXMLNodeArray __fastcall GetHostedNodes();
	TXMLNode* __fastcall GetHostNode();
	TXMLNode* __fastcall GetNodeObject();
	bool __fastcall HasChildNode(const System::UnicodeString ChildTag)/* overload */;
	bool __fastcall HasChildNode(const System::UnicodeString ChildTag, const System::UnicodeString NamespaceURI)/* overload */;
	Xml::Xmlintf::_di_IXMLNode __fastcall InternalAddChild(TXMLNodeClass NodeClass, const System::UnicodeString NodeName, const System::UnicodeString NamespaceURI, int Index);
	int __fastcall NestingLevel();
	void __fastcall RegisterChildNode(const System::UnicodeString TagName, TXMLNodeClass ChildNodeClass, System::UnicodeString NamespaceURI = System::UnicodeString());
	void __fastcall RegisterChildNodes(const System::UnicodeString *TagNames, const int TagNames_High, TXMLNodeClass const *NodeClasses, const int NodeClasses_High);
	void __fastcall SetCollection(TXMLNodeCollection* const Value);
	virtual void __fastcall SetParentNode(TXMLNode* const Value);
	__property TNodeListNotification OnHostChildNotify = {read=FOnHostChildNotify, write=FOnHostChildNotify};
	__property TNodeListNotification OnHostAttrNotify = {read=FOnHostAttrNotify, write=FOnHostAttrNotify};
	void __fastcall AddHostedNode(TXMLNode* Node);
	void __fastcall AttributeListNotify(TNodeListOperation Operation, Xml::Xmlintf::_di_IXMLNode &Node, const System::OleVariant &IndexOrName, bool BeforeOperation);
	void __fastcall CheckReadOnly();
	virtual void __fastcall ChildListNotify(TNodeListOperation Operation, Xml::Xmlintf::_di_IXMLNode &Node, const System::OleVariant &IndexOrName, bool BeforeOperation);
	void __fastcall CheckNotHosted();
	DYNAMIC Xml::Xmlintf::_di_IXMLNodeList __fastcall CreateAttributeList();
	DYNAMIC Xml::Xmlintf::_di_IXMLNodeList __fastcall CreateChildList();
	virtual void __fastcall DoNodeChange(TNodeChange ChangeType, bool BeforeOperation);
	System::UnicodeString __fastcall GetPrefixedName(const System::UnicodeString Name, const System::UnicodeString NamespaceURI);
	void __fastcall RemoveHostedNode(TXMLNode* Node);
	virtual void __fastcall SetAttributeNodes(const Xml::Xmlintf::_di_IXMLNodeList Value);
	virtual void __fastcall SetChildNodes(const Xml::Xmlintf::_di_IXMLNodeList Value);
	__property Xml::Xmlintf::_di_IXMLNodeList AttributeNodes = {read=GetAttributeNodes};
	__property Xml::Xmlintf::_di_IXMLNodeList ChildNodes = {read=GetChildNodes, write=SetChildNodes};
	__property TNodeClassArray ChildNodeClasses = {read=GetChildNodeClasses};
	__property TXMLNodeCollection* Collection = {read=FCollection, write=FCollection};
	__property Xml::Xmldom::_di_IDOMNode DOMNode = {read=FDOMNode};
	__property TXMLNodeArray HostedNodes = {read=GetHostedNodes};
	__property TXMLNode* HostNode = {read=FHostNode, write=FHostNode};
	__property TXMLDocument* OwnerDocument = {read=FDocument};
	__property TXMLNode* ParentNode = {read=FParentNode};
	
public:
	__fastcall TXMLNode(const Xml::Xmldom::_di_IDOMNode ADOMNode, TXMLNode* const AParentNode, TXMLDocument* const OwnerDoc);
	__fastcall TXMLNode(TXMLNode* HostNode);
	__fastcall virtual ~TXMLNode();
private:
	void *__IXMLNodeAccess;	// IXMLNodeAccess 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6C819037-AB66-4AA8-B2A5-958EDA8627B7}
	operator _di_IXMLNodeAccess()
	{
		_di_IXMLNodeAccess intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLNodeAccess*(void) { return (IXMLNodeAccess*)&__IXMLNodeAccess; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {395950C0-7E5D-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmlintf::_di_IXMLNode()
	{
		Xml::Xmlintf::_di_IXMLNode intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmlintf::IXMLNode*(void) { return (Xml::Xmlintf::IXMLNode*)&__IXMLNodeAccess; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLNodeCollection : public TXMLNode
{
	typedef TXMLNode inherited;
	
private:
	GUID FItemInterface;
	System::UnicodeString FItemNS;
	System::UnicodeString FItemTag;
	Xml::Xmlintf::_di_IXMLNodeList FList;
	
protected:
	void __fastcall Clear();
	int __fastcall GetCount();
	virtual Xml::Xmlintf::_di_IXMLNodeList __fastcall GetList();
	Xml::Xmlintf::_di_IXMLNode __fastcall GetNode(int Index);
	void __fastcall Delete(int Index);
	int __fastcall Remove(const Xml::Xmlintf::_di_IXMLNode AItem);
	virtual void __fastcall ChildListNotify(TNodeListOperation Operation, Xml::Xmlintf::_di_IXMLNode &Node, const System::OleVariant &IndexOrName, bool BeforeOperation);
	void __fastcall UpdateCollectionList(TNodeListOperation Operation, Xml::Xmlintf::_di_IXMLNode &Node, const System::OleVariant &IndexOrName, bool BeforeOperation);
	__property int Count = {read=GetCount, nodefault};
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall AddItem(int Index);
	void __fastcall CreateItemList(bool CheckFirst = false);
	void __fastcall InsertInCollection(Xml::Xmlintf::_di_IXMLNode Node, int Index);
	bool __fastcall IsCollectionItem(const Xml::Xmlintf::_di_IXMLNode Node);
	virtual void __fastcall SetChildNodes(const Xml::Xmlintf::_di_IXMLNodeList Value);
	__property GUID ItemInterface = {read=FItemInterface, write=FItemInterface};
	__property System::UnicodeString ItemNS = {read=FItemNS, write=FItemNS};
	__property System::UnicodeString ItemTag = {read=FItemTag, write=FItemTag};
	__property Xml::Xmlintf::_di_IXMLNodeList List = {read=GetList};
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLNodeCollection(const Xml::Xmldom::_di_IDOMNode ADOMNode, TXMLNode* const AParentNode, TXMLDocument* const OwnerDoc) : TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLNodeCollection(TXMLNode* HostNode) : TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLNodeCollection() { }
	
private:
	void *__IXMLNodeCollection;	// Xml::Xmlintf::IXMLNodeCollection 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {395950C2-7E5D-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmlintf::_di_IXMLNodeCollection()
	{
		Xml::Xmlintf::_di_IXMLNodeCollection intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmlintf::IXMLNodeCollection*(void) { return (Xml::Xmlintf::IXMLNodeCollection*)&__IXMLNodeCollection; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (__closure *TNodeChangeEvent)(const Xml::Xmlintf::_di_IXMLNode Node, TNodeChange ChangeType);

enum DECLSPEC_DENUM TXMLPrologItem : unsigned char { xpVersion, xpEncoding, xpStandalone };

enum DECLSPEC_DENUM TXMLDocumentSource : unsigned char { xdsNone, xdsXMLProperty, xdsXMLData, xdsFile, xdsStream };

__interface  INTERFACE_UUID("{933FDA52-B0D0-440C-B3E9-C37FFB4B906B}") IXMLDocumentAccess  : public System::IInterface 
{
	virtual TXMLDocument* __fastcall GetDocumentObject() = 0 ;
	virtual Xml::Xmldom::_di_IDOMPersist __fastcall GetDOMPersist() = 0 ;
	__property TXMLDocument* DocumentObject = {read=GetDocumentObject};
	__property Xml::Xmldom::_di_IDOMPersist DOMPersist = {read=GetDOMPersist};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXMLDocument : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::UnicodeString FXMLData;
	System::Classes::TStream* FSrcStream;
	System::Classes::TStringList* FXMLStrings;
	Xml::Xmldom::TDOMVendor* FDOMVendor;
	int FRefCount;
	TNodeClassArray FDocBindingInfo;
	Xml::Xmldom::_di_IDOMPersist FDOMPersist;
	Xml::Xmldom::_di_IDOMDocument FDOMDocument;
	Xml::Xmldom::_di_IDOMImplementation FDOMImplementation;
	Xml::Xmldom::_di_IDOMParseOptions FDOMParseOptions;
	Xml::Xmlintf::TParseOptions FParseOptions;
	Xml::Xmlintf::_di_IXMLNode FDocumentNode;
	System::UnicodeString FFileName;
	Xml::Xmlintf::TXMLDocOptions FOptions;
	int FPrefixID;
	System::UnicodeString FNSPrefixBase;
	System::UnicodeString FNodeIndentStr;
	bool FStreamedActive;
	int FModified;
	int FXMLStrRead;
	TXMLDocumentSource FDocSource;
	System::Classes::TNotifyEvent FAfterClose;
	System::Classes::TNotifyEvent FBeforeOpen;
	System::Classes::TNotifyEvent FBeforeClose;
	System::Classes::TNotifyEvent FAfterOpen;
	bool FOwnerIsComponent;
	TNodeChangeEvent FBeforeNodeChange;
	TNodeChangeEvent FAfterNodeChange;
	Xml::Xmldom::TAsyncEventHandler FOnAsyncLoad;
	Xml::Xmldom::_di_IDOMParseOptions __fastcall GetDOMParseOptions();
	bool __fastcall IsXMLStored();
	bool __fastcall NodeIndentStored();
	void __fastcall SetDOMImplementation(const Xml::Xmldom::_di_IDOMImplementation Value);
	void __fastcall SetDOMVendor(Xml::Xmldom::TDOMVendor* const Value);
	
protected:
	HIDESBASE int __stdcall _AddRef();
	HIDESBASE int __stdcall _Release();
	virtual bool __fastcall GetActive();
	int __fastcall GetAsyncLoadState();
	Xml::Xmlintf::_di_IXMLNodeList __fastcall GetChildNodes();
	Xml::Xmlintf::_di_IXMLNode __fastcall GetDocumentElement();
	System::UnicodeString __fastcall GetEncoding();
	Xml::Xmldom::_di_IDOMDocument __fastcall GetDOMDocument();
	Xml::Xmlintf::_di_IXMLNode __fastcall GetDocumentNode();
	System::UnicodeString __fastcall GetFileName();
	bool __fastcall GetModified();
	System::UnicodeString __fastcall GetNodeIndentStr();
	Xml::Xmlintf::TXMLDocOptions __fastcall GetOptions();
	Xml::Xmlintf::TParseOptions __fastcall GetParseOptions();
	System::UnicodeString __fastcall GetSchemaRef();
	System::UnicodeString __fastcall GetStandAlone();
	System::UnicodeString __fastcall GetVersion();
	System::Classes::TStrings* __fastcall GetXML();
	virtual void __fastcall SetActive(const bool Value);
	void __fastcall SetDocumentElement(const Xml::Xmlintf::_di_IXMLNode Value);
	void __fastcall SetDOMDocument(const Xml::Xmldom::_di_IDOMDocument Value);
	void __fastcall SetEncoding(const System::UnicodeString Value);
	void __fastcall SetNodeIndentStr(const System::UnicodeString Value);
	void __fastcall SetOnAsyncLoad(const Xml::Xmldom::TAsyncEventHandler Value);
	void __fastcall SetOptions(const Xml::Xmlintf::TXMLDocOptions Value);
	void __fastcall SetParseOptions(const Xml::Xmlintf::TParseOptions Value);
	void __fastcall SetStandAlone(const System::UnicodeString Value);
	void __fastcall SetVersion(const System::UnicodeString Value);
	void __fastcall SetXML(System::Classes::TStrings* const Value);
	TXMLDocument* __fastcall GetDocumentObject();
	Xml::Xmldom::_di_IDOMPersist __fastcall GetDOMPersist();
	void __fastcall AssignParseOptions();
	void __fastcall CheckActive();
	DYNAMIC void __fastcall CheckAutoSave();
	DYNAMIC void __fastcall CheckDOM();
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	DYNAMIC void __fastcall DoAfterClose();
	DYNAMIC void __fastcall DoAfterOpen();
	DYNAMIC void __fastcall DoBeforeClose();
	DYNAMIC void __fastcall DoBeforeOpen();
	void __fastcall DoNodeChange(const Xml::Xmlintf::_di_IXMLNode Node, TNodeChange ChangeType, bool BeforeOperation);
	Xml::Xmlintf::_di_IXMLNode __fastcall GetPrologNode();
	System::UnicodeString __fastcall GetPrologValue(TXMLPrologItem PrologItem, const System::UnicodeString Default = System::UnicodeString());
	virtual TXMLNodeClass __fastcall GetChildNodeClass(const Xml::Xmldom::_di_IDOMNode Node);
	System::UnicodeString __fastcall InternalSetPrologValue(const Xml::Xmlintf::_di_IXMLNode PrologNode, const System::Variant &Value, TXMLPrologItem PrologItem);
	DYNAMIC void __fastcall LoadData();
	virtual void __fastcall Loaded();
	void __fastcall ReadDOMVendor(System::Classes::TReader* Reader);
	DYNAMIC void __fastcall ReleaseDoc(const bool CheckSave = true);
	void __fastcall SaveToXMLStrings();
	void __fastcall SaveToUTF8String(System::UTF8String &XML);
	void __fastcall SetFileName(const System::UnicodeString Value);
	void __fastcall SetModified(const bool Value);
	void __fastcall SetPrologValue(const System::Variant &Value, TXMLPrologItem PrologItem);
	void __fastcall SetXMLStrings(const System::UnicodeString Value);
	void __fastcall WriteDOMVendor(System::Classes::TWriter* Writer);
	void __fastcall XMLStringsChanging(System::TObject* Sender);
	__property TNodeClassArray DocBindingInfo = {read=FDocBindingInfo};
	__property TXMLDocumentSource DocSource = {read=FDocSource, write=FDocSource, nodefault};
	__property Xml::Xmldom::_di_IDOMParseOptions DOMParseOptions = {read=GetDOMParseOptions};
	__property Xml::Xmldom::_di_IDOMPersist DOMPersist = {read=GetDOMPersist};
	__property int PrefixID = {read=FPrefixID, write=FPrefixID, nodefault};
	
public:
	__fastcall virtual TXMLDocument(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall TXMLDocument(const System::UnicodeString AFileName)/* overload */;
	__classmethod virtual System::TObject* __fastcall NewInstance();
	virtual void __fastcall AfterConstruction();
	__fastcall virtual ~TXMLDocument();
	Xml::Xmlintf::_di_IXMLNode __fastcall AddChild(const System::UnicodeString TagName)/* overload */;
	Xml::Xmlintf::_di_IXMLNode __fastcall AddChild(const System::UnicodeString TagName, const System::UnicodeString NamespaceURI)/* overload */;
	Xml::Xmlintf::_di_IXMLNode __fastcall CreateElement(const System::UnicodeString TagOrData, const System::UnicodeString NamespaceURI);
	Xml::Xmlintf::_di_IXMLNode __fastcall CreateNode(const System::UnicodeString NameOrData, Xml::Xmlintf::TNodeType NodeType = (Xml::Xmlintf::TNodeType)(0x1), const System::UnicodeString AddlData = System::UnicodeString());
	Xml::Xmlintf::_di_IXMLNode __fastcall GetDocBinding(const System::UnicodeString TagName, System::TClass DocNodeClass, System::UnicodeString NamespaceURI = System::UnicodeString());
	bool __fastcall IsEmptyDoc();
	void __fastcall LoadFromFile(const System::UnicodeString AFileName = System::UnicodeString());
	void __fastcall LoadFromStream(System::Classes::TStream* const Stream, Xml::Xmlintf::TXMLEncodingType EncodingType = (Xml::Xmlintf::TXMLEncodingType)(0x0));
	void __fastcall LoadFromXML(const System::AnsiString XML)/* overload */;
	void __fastcall LoadFromXML(const System::UnicodeString XML)/* overload */;
	void __fastcall Refresh();
	void __fastcall RegisterDocBinding(const System::UnicodeString TagName, System::TClass DocNodeClass, System::UnicodeString NamespaceURI = System::UnicodeString());
	void __fastcall Resync();
	DYNAMIC void __fastcall SaveToFile(const System::UnicodeString AFileName = System::UnicodeString());
	void __fastcall SaveToStream(System::Classes::TStream* const Stream);
	void __fastcall SaveToXML(System::UnicodeString &XML)/* overload */;
	void __fastcall SaveToXML(System::WideString &XML)/* overload */;
	void __fastcall SaveToXML(System::UTF8String &XML)/* overload */;
	__property int AsyncLoadState = {read=GetAsyncLoadState, nodefault};
	__property Xml::Xmlintf::_di_IXMLNodeList ChildNodes = {read=GetChildNodes};
	__property Xml::Xmldom::_di_IDOMDocument DOMDocument = {read=GetDOMDocument, write=SetDOMDocument};
	__property Xml::Xmldom::_di_IDOMImplementation DOMImplementation = {read=FDOMImplementation, write=SetDOMImplementation};
	__property Xml::Xmlintf::_di_IXMLNode DocumentElement = {read=GetDocumentElement, write=SetDocumentElement};
	__property System::UnicodeString Encoding = {read=GetEncoding, write=SetEncoding};
	System::UnicodeString __fastcall GeneratePrefix(const Xml::Xmlintf::_di_IXMLNode Node);
	__property bool Modified = {read=GetModified, nodefault};
	__property Xml::Xmlintf::_di_IXMLNode Node = {read=GetDocumentNode};
	__property System::UnicodeString NSPrefixBase = {read=FNSPrefixBase, write=FNSPrefixBase};
	__property System::UnicodeString SchemaRef = {read=GetSchemaRef};
	__property System::UnicodeString StandAlone = {read=GetStandAlone, write=SetStandAlone};
	__property System::UnicodeString Version = {read=GetVersion, write=SetVersion};
	
__published:
	__property bool Active = {read=GetActive, write=SetActive, default=0};
	__property System::UnicodeString FileName = {read=GetFileName, write=SetFileName};
	__property Xml::Xmldom::TDOMVendor* DOMVendor = {read=FDOMVendor, write=SetDOMVendor};
	__property System::UnicodeString NodeIndentStr = {read=GetNodeIndentStr, write=SetNodeIndentStr, stored=NodeIndentStored};
	__property Xml::Xmlintf::TXMLDocOptions Options = {read=GetOptions, write=SetOptions, default=29};
	__property Xml::Xmlintf::TParseOptions ParseOptions = {read=GetParseOptions, write=SetParseOptions, default=0};
	__property System::Classes::TStrings* XML = {read=GetXML, write=SetXML, stored=IsXMLStored};
	__property System::Classes::TNotifyEvent BeforeOpen = {read=FBeforeOpen, write=FBeforeOpen};
	__property System::Classes::TNotifyEvent AfterOpen = {read=FAfterOpen, write=FAfterOpen};
	__property System::Classes::TNotifyEvent BeforeClose = {read=FBeforeClose, write=FBeforeClose};
	__property System::Classes::TNotifyEvent AfterClose = {read=FAfterClose, write=FAfterClose};
	__property TNodeChangeEvent BeforeNodeChange = {read=FBeforeNodeChange, write=FBeforeNodeChange};
	__property TNodeChangeEvent AfterNodeChange = {read=FAfterNodeChange, write=FAfterNodeChange};
	__property Xml::Xmldom::TAsyncEventHandler OnAsyncLoad = {read=FOnAsyncLoad, write=SetOnAsyncLoad};
private:
	void *__IXMLDocumentAccess;	// IXMLDocumentAccess 
	void *__IXMLDocument;	// Xml::Xmlintf::IXMLDocument 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {933FDA52-B0D0-440C-B3E9-C37FFB4B906B}
	operator _di_IXMLDocumentAccess()
	{
		_di_IXMLDocumentAccess intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLDocumentAccess*(void) { return (IXMLDocumentAccess*)&__IXMLDocumentAccess; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {395950C3-7E5D-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmlintf::_di_IXMLDocument()
	{
		Xml::Xmlintf::_di_IXMLDocument intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmlintf::IXMLDocument*(void) { return (Xml::Xmlintf::IXMLDocument*)&__IXMLDocument; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000000-0000-0000-C000-000000000046}
	operator System::_di_IInterface()
	{
		System::_di_IInterface intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::IInterface*(void) { return (System::IInterface*)&__IXMLDocumentAccess; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool UseXSDBooleanStrings;
extern DELPHI_PACKAGE void __fastcall XMLDocError(const System::UnicodeString Msg)/* overload */;
extern DELPHI_PACKAGE void __fastcall XMLDocError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High)/* overload */;
extern DELPHI_PACKAGE Xml::Xmldom::_di_IDOMNode __fastcall CreateDOMNode(Xml::Xmldom::_di_IDOMDocument Doc, const System::UnicodeString NameOrData, Xml::Xmlintf::TNodeType NodeType = (Xml::Xmlintf::TNodeType)(0x1), const System::UnicodeString AddlData = System::UnicodeString());
extern DELPHI_PACKAGE System::UnicodeString __fastcall FormatXMLData(const System::UnicodeString XMLData);
extern DELPHI_PACKAGE Xml::Xmlintf::_di_IXMLDocument __fastcall LoadXMLDocument(const System::UnicodeString FileName);
extern DELPHI_PACKAGE Xml::Xmlintf::_di_IXMLDocument __fastcall LoadXMLData(const System::UnicodeString XMLData)/* overload */;
extern DELPHI_PACKAGE Xml::Xmlintf::_di_IXMLDocument __fastcall LoadXMLData(const System::AnsiString XMLData)/* overload */;
extern DELPHI_PACKAGE Xml::Xmlintf::_di_IXMLDocument __fastcall NewXMLDocument(System::UnicodeString Version = u"1.0");
extern DELPHI_PACKAGE Xml::Xmlintf::TXMLEncodingType __fastcall DetectCharEncoding(System::Classes::TStream* S);
extern DELPHI_PACKAGE void __fastcall CheckEncoding(System::UnicodeString &XMLData, const System::UnicodeString *ValidEncodings, const int ValidEncodings_High);
extern DELPHI_PACKAGE System::UnicodeString __fastcall XMLStringToUnicodeString(const System::AnsiString XMLString);
extern DELPHI_PACKAGE System::WideString __fastcall XMLStringToWideString _DEPRECATED_ATTRIBUTE0 (const System::AnsiString XMLString);
}	/* namespace Xmldoc */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_XMLDOC)
using namespace Xml::Xmldoc;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_XmldocHPP
