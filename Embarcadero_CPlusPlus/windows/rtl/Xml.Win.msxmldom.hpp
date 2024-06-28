// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.Win.msxmldom.pas' rev: 34.00 (Windows)

#ifndef Xml_Win_MsxmldomHPP
#define Xml_Win_MsxmldomHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Winapi.ActiveX.hpp>
#include <Winapi.msxml.hpp>
#include <Xml.xmldom.hpp>
#include <Winapi.MSXMLIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Win
{
namespace Msxmldom
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IXMLDOMNodeRef;
typedef System::DelphiInterface<IXMLDOMNodeRef> _di_IXMLDOMNodeRef;
class DELPHICLASS TMSDOMInterface;
class DELPHICLASS TMSDOMImplementation;
class DELPHICLASS TMSDOMNode;
class DELPHICLASS TMSDOMNodeList;
class DELPHICLASS TMSDOMNamedNodeMap;
class DELPHICLASS TMSDOMCharacterData;
class DELPHICLASS TMSDOMAttr;
class DELPHICLASS TMSDOMElement;
class DELPHICLASS TMSDOMText;
class DELPHICLASS TMSDOMComment;
class DELPHICLASS TMSDOMCDATASection;
class DELPHICLASS TMSDOMDocumentType;
class DELPHICLASS TMSDOMNotation;
class DELPHICLASS TMSDOMEntity;
class DELPHICLASS TMSDOMEntityReference;
class DELPHICLASS TMSDOMProcessingInstruction;
class DELPHICLASS TMSDOMDocumentFragment;
class DELPHICLASS TMSDOMEventHandler;
class DELPHICLASS TMSDOMDocument;
class DELPHICLASS TMSDOMImplementationFactory;
class DELPHICLASS TMSXMLDOMDocumentFactory;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{5EF5DAA1-2729-11D4-83DA-00C04F60B2DD}") IXMLDOMNodeRef  : public System::IInterface 
{
	virtual _di_IXMLDOMNode __fastcall GetXMLDOMNode() = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMInterface : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	virtual HRESULT __fastcall SafeCallException(System::TObject* ExceptObject, void * ExceptAddr);
public:
	/* TObject.Create */ inline __fastcall TMSDOMInterface() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMInterface() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMImplementation : public TMSDOMInterface
{
	typedef TMSDOMInterface inherited;
	
private:
	_di_IXMLDOMImplementation FMSDOMImpl;
	
protected:
	System::WordBool __fastcall hasFeature(const System::UnicodeString feature, const System::UnicodeString version);
	HRESULT __safecall createDocumentType(const System::UnicodeString qualifiedName, const System::UnicodeString publicId, const System::UnicodeString systemId, Xml::Xmldom::_di_IDOMDocumentType &__createDocumentType_result);
	HRESULT __safecall createDocument(const System::UnicodeString namespaceURI, const System::UnicodeString qualifiedName, Xml::Xmldom::_di_IDOMDocumentType doctype, Xml::Xmldom::_di_IDOMDocument &__createDocument_result);
	
public:
	__fastcall TMSDOMImplementation(_di_IXMLDOMImplementation DOMImpl);
	__property _di_IXMLDOMImplementation MSDOMImpl = {read=FMSDOMImpl};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMImplementation() { }
	
private:
	void *__IDOMImplementation;	// Xml::Xmldom::IDOMImplementation 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0E0-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMImplementation()
	{
		Xml::Xmldom::_di_IDOMImplementation intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMImplementation*(void) { return (Xml::Xmldom::IDOMImplementation*)&__IDOMImplementation; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TMSDOMNodeClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TMSDOMNodeClass);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMNode : public TMSDOMInterface
{
	typedef TMSDOMInterface inherited;
	
private:
	_di_IXMLDOMNode FMSNode;
	Xml::Xmldom::_di_IDOMNodeList FChildNodes;
	Xml::Xmldom::_di_IDOMNamedNodeMap FAttributes;
	Xml::Xmldom::_di_IDOMDocument FOwnerDocument;
	
protected:
	_di_IXMLDOMNode __fastcall GetXMLDOMNode();
	HRESULT __safecall get_nodeName(System::UnicodeString &__get_nodeName_result);
	HRESULT __safecall get_nodeValue(System::UnicodeString &__get_nodeValue_result);
	HRESULT __safecall set_nodeValue(System::UnicodeString value);
	HRESULT __safecall get_nodeType(System::Word &__get_nodeType_result);
	HRESULT __safecall get_parentNode(Xml::Xmldom::_di_IDOMNode &__get_parentNode_result);
	HRESULT __safecall get_childNodes(Xml::Xmldom::_di_IDOMNodeList &__get_childNodes_result);
	HRESULT __safecall get_firstChild(Xml::Xmldom::_di_IDOMNode &__get_firstChild_result);
	HRESULT __safecall get_lastChild(Xml::Xmldom::_di_IDOMNode &__get_lastChild_result);
	HRESULT __safecall get_previousSibling(Xml::Xmldom::_di_IDOMNode &__get_previousSibling_result);
	HRESULT __safecall get_nextSibling(Xml::Xmldom::_di_IDOMNode &__get_nextSibling_result);
	HRESULT __safecall get_attributes(Xml::Xmldom::_di_IDOMNamedNodeMap &__get_attributes_result);
	HRESULT __safecall get_ownerDocument(Xml::Xmldom::_di_IDOMDocument &__get_ownerDocument_result);
	HRESULT __safecall get_namespaceURI(System::UnicodeString &__get_namespaceURI_result);
	HRESULT __safecall get_prefix(System::UnicodeString &__get_prefix_result);
	HRESULT __safecall get_localName(System::UnicodeString &__get_localName_result);
	HRESULT __safecall insertBefore(const Xml::Xmldom::_di_IDOMNode newChild, const Xml::Xmldom::_di_IDOMNode refChild, Xml::Xmldom::_di_IDOMNode &__insertBefore_result);
	HRESULT __safecall replaceChild(const Xml::Xmldom::_di_IDOMNode newChild, const Xml::Xmldom::_di_IDOMNode oldChild, Xml::Xmldom::_di_IDOMNode &__replaceChild_result);
	HRESULT __safecall removeChild(const Xml::Xmldom::_di_IDOMNode childNode, Xml::Xmldom::_di_IDOMNode &__removeChild_result);
	HRESULT __safecall appendChild(const Xml::Xmldom::_di_IDOMNode newChild, Xml::Xmldom::_di_IDOMNode &__appendChild_result);
	HRESULT __safecall hasChildNodes(System::WordBool &__hasChildNodes_result);
	HRESULT __safecall cloneNode(System::WordBool deep, Xml::Xmldom::_di_IDOMNode &__cloneNode_result);
	HRESULT __safecall normalize();
	System::WordBool __fastcall supports(const System::UnicodeString feature, const System::UnicodeString version);
	HRESULT __safecall get_text(System::UnicodeString &__get_text_result);
	HRESULT __safecall get_xml(System::UnicodeString &__get_xml_result);
	HRESULT __safecall transformNode(const Xml::Xmldom::_di_IDOMNode stylesheet, System::WideString &output)/* overload */;
	HRESULT __safecall transformNode(const Xml::Xmldom::_di_IDOMNode stylesheet, const Xml::Xmldom::_di_IDOMDocument output)/* overload */;
	HRESULT __safecall selectNode(const System::WideString nodePath, Xml::Xmldom::_di_IDOMNode &__selectNode_result);
	HRESULT __safecall selectNodes(const System::WideString nodePath, Xml::Xmldom::_di_IDOMNodeList &__selectNodes_result);
	HRESULT __safecall set_text(const System::UnicodeString Value);
	
public:
	__fastcall TMSDOMNode(_di_IXMLDOMNode ANode);
	__property _di_IXMLDOMNode MSNode = {read=FMSNode};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMNode() { }
	
private:
	void *__IDOMNodeSelect;	// Xml::Xmldom::IDOMNodeSelect 
	void *__IDOMNodeEx;	// Xml::Xmldom::IDOMNodeEx 
	void *__IXMLDOMNodeRef;	// IXMLDOMNodeRef 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2A3602E0-2B39-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMNodeSelect()
	{
		Xml::Xmldom::_di_IDOMNodeSelect intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMNodeSelect*(void) { return (Xml::Xmldom::IDOMNodeSelect*)&__IDOMNodeSelect; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B06BFFDD-337B-48DA-980B-6F7AA8ADE85C}
	operator Xml::Xmldom::_di_IDOMNodeEx()
	{
		Xml::Xmldom::_di_IDOMNodeEx intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMNodeEx*(void) { return (Xml::Xmldom::IDOMNodeEx*)&__IDOMNodeEx; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0E1-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMNode()
	{
		Xml::Xmldom::_di_IDOMNode intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMNode*(void) { return (Xml::Xmldom::IDOMNode*)&__IDOMNodeEx; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5EF5DAA1-2729-11D4-83DA-00C04F60B2DD}
	operator _di_IXMLDOMNodeRef()
	{
		_di_IXMLDOMNodeRef intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLDOMNodeRef*(void) { return (IXMLDOMNodeRef*)&__IXMLDOMNodeRef; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMNodeList : public TMSDOMInterface
{
	typedef TMSDOMInterface inherited;
	
private:
	_di_IXMLDOMNodeList FMSNodeList;
	
protected:
	HRESULT __safecall get_item(int index, Xml::Xmldom::_di_IDOMNode &__get_item_result);
	HRESULT __safecall get_length(int &__get_length_result);
	
public:
	__fastcall TMSDOMNodeList(_di_IXMLDOMNodeList ANodeList);
	__property _di_IXMLDOMNodeList MSNodeList = {read=FMSNodeList};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMNodeList() { }
	
private:
	void *__IDOMNodeList;	// Xml::Xmldom::IDOMNodeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0E2-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMNodeList()
	{
		Xml::Xmldom::_di_IDOMNodeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMNodeList*(void) { return (Xml::Xmldom::IDOMNodeList*)&__IDOMNodeList; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMNamedNodeMap : public TMSDOMInterface
{
	typedef TMSDOMInterface inherited;
	
private:
	_di_IXMLDOMNamedNodeMap FMSNamedNodeMap;
	
protected:
	HRESULT __safecall get_item(int index, Xml::Xmldom::_di_IDOMNode &__get_item_result);
	HRESULT __safecall get_length(int &__get_length_result);
	HRESULT __safecall getNamedItem(const System::UnicodeString name, Xml::Xmldom::_di_IDOMNode &__getNamedItem_result);
	HRESULT __safecall setNamedItem(const Xml::Xmldom::_di_IDOMNode newItem, Xml::Xmldom::_di_IDOMNode &__setNamedItem_result);
	HRESULT __safecall removeNamedItem(const System::UnicodeString name, Xml::Xmldom::_di_IDOMNode &__removeNamedItem_result);
	HRESULT __safecall getNamedItemNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName, Xml::Xmldom::_di_IDOMNode &__getNamedItemNS_result);
	HRESULT __safecall setNamedItemNS(const Xml::Xmldom::_di_IDOMNode arg, Xml::Xmldom::_di_IDOMNode &__setNamedItemNS_result);
	HRESULT __safecall removeNamedItemNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName, Xml::Xmldom::_di_IDOMNode &__removeNamedItemNS_result);
	
public:
	__fastcall TMSDOMNamedNodeMap(_di_IXMLDOMNamedNodeMap ANamedNodeMap);
	__property _di_IXMLDOMNamedNodeMap MSNamedNodeMap = {read=FMSNamedNodeMap};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMNamedNodeMap() { }
	
private:
	void *__IDOMNamedNodeMap;	// Xml::Xmldom::IDOMNamedNodeMap 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0E3-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMNamedNodeMap()
	{
		Xml::Xmldom::_di_IDOMNamedNodeMap intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMNamedNodeMap*(void) { return (Xml::Xmldom::IDOMNamedNodeMap*)&__IDOMNamedNodeMap; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMCharacterData : public TMSDOMNode
{
	typedef TMSDOMNode inherited;
	
private:
	_di_IXMLDOMCharacterData __fastcall GetMSCharacterData();
	
protected:
	HRESULT __safecall get_data(System::UnicodeString &__get_data_result);
	HRESULT __safecall set_data(const System::UnicodeString data);
	HRESULT __safecall get_length(int &__get_length_result);
	HRESULT __safecall substringData(int offset, int count, System::UnicodeString &__substringData_result);
	HRESULT __safecall appendData(const System::UnicodeString data);
	HRESULT __safecall insertData(int offset, const System::UnicodeString data);
	HRESULT __safecall deleteData(int offset, int count);
	HRESULT __safecall replaceData(int offset, int count, const System::UnicodeString data);
	
public:
	__property _di_IXMLDOMCharacterData MSCharacterData = {read=GetMSCharacterData};
public:
	/* TMSDOMNode.Create */ inline __fastcall TMSDOMCharacterData(_di_IXMLDOMNode ANode) : TMSDOMNode(ANode) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMCharacterData() { }
	
private:
	void *__IDOMCharacterData;	// Xml::Xmldom::IDOMCharacterData 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0E4-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMCharacterData()
	{
		Xml::Xmldom::_di_IDOMCharacterData intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMCharacterData*(void) { return (Xml::Xmldom::IDOMCharacterData*)&__IDOMCharacterData; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMAttr : public TMSDOMNode
{
	typedef TMSDOMNode inherited;
	
private:
	_di_IXMLDOMAttribute __fastcall GetMSAttribute();
	
protected:
	HRESULT __safecall get_name(System::UnicodeString &__get_name_result);
	HRESULT __safecall get_specified(System::WordBool &__get_specified_result);
	HRESULT __safecall get_value(System::UnicodeString &__get_value_result);
	HRESULT __safecall set_value(const System::UnicodeString attributeValue);
	HRESULT __safecall get_ownerElement(Xml::Xmldom::_di_IDOMElement &__get_ownerElement_result);
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_name() { System::UnicodeString __r; HRESULT __hr = get_name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString name = {read=_scw_get_name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_get_specified() { System::WordBool __r; HRESULT __hr = get_specified(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool specified = {read=_scw_get_specified, nodefault};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_value() { System::UnicodeString __r; HRESULT __hr = get_value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString value = {read=_scw_get_value, write=set_value};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Xml::Xmldom::_di_IDOMElement _scw_get_ownerElement() { Xml::Xmldom::_di_IDOMElement __r; HRESULT __hr = get_ownerElement(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Xml::Xmldom::_di_IDOMElement ownerElement = {read=_scw_get_ownerElement};
	
public:
	__property _di_IXMLDOMAttribute MSAttribute = {read=GetMSAttribute};
public:
	/* TMSDOMNode.Create */ inline __fastcall TMSDOMAttr(_di_IXMLDOMNode ANode) : TMSDOMNode(ANode) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMAttr() { }
	
private:
	void *__IDOMAttr;	// Xml::Xmldom::IDOMAttr 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0E5-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMAttr()
	{
		Xml::Xmldom::_di_IDOMAttr intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMAttr*(void) { return (Xml::Xmldom::IDOMAttr*)&__IDOMAttr; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMElement : public TMSDOMNode
{
	typedef TMSDOMNode inherited;
	
private:
	_di_IXMLDOMElement __fastcall GetMSElement();
	
protected:
	HRESULT __safecall get_tagName(System::UnicodeString &__get_tagName_result);
	HRESULT __safecall getAttribute(const System::UnicodeString name, System::UnicodeString &__getAttribute_result);
	HRESULT __safecall setAttribute(const System::UnicodeString name, const System::UnicodeString value);
	HRESULT __safecall removeAttribute(const System::UnicodeString name);
	HRESULT __safecall getAttributeNode(const System::UnicodeString name, Xml::Xmldom::_di_IDOMAttr &__getAttributeNode_result);
	HRESULT __safecall setAttributeNode(const Xml::Xmldom::_di_IDOMAttr newAttr, Xml::Xmldom::_di_IDOMAttr &__setAttributeNode_result);
	HRESULT __safecall removeAttributeNode(const Xml::Xmldom::_di_IDOMAttr oldAttr, Xml::Xmldom::_di_IDOMAttr &__removeAttributeNode_result);
	HRESULT __safecall getElementsByTagName(const System::UnicodeString name, Xml::Xmldom::_di_IDOMNodeList &__getElementsByTagName_result);
	HRESULT __safecall getAttributeNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName, System::UnicodeString &__getAttributeNS_result);
	HRESULT __safecall setAttributeNS(const System::UnicodeString namespaceURI, const System::UnicodeString qualifiedName, const System::UnicodeString value);
	HRESULT __safecall removeAttributeNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName);
	HRESULT __safecall getAttributeNodeNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName, Xml::Xmldom::_di_IDOMAttr &__getAttributeNodeNS_result);
	HRESULT __safecall setAttributeNodeNS(const Xml::Xmldom::_di_IDOMAttr newAttr, Xml::Xmldom::_di_IDOMAttr &__setAttributeNodeNS_result);
	HRESULT __safecall getElementsByTagNameNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName, Xml::Xmldom::_di_IDOMNodeList &__getElementsByTagNameNS_result);
	HRESULT __safecall hasAttribute(const System::UnicodeString name, System::WordBool &__hasAttribute_result);
	HRESULT __safecall hasAttributeNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName, System::WordBool &__hasAttributeNS_result);
	HIDESBASE HRESULT __safecall normalize();
	
public:
	__property _di_IXMLDOMElement MSElement = {read=GetMSElement};
public:
	/* TMSDOMNode.Create */ inline __fastcall TMSDOMElement(_di_IXMLDOMNode ANode) : TMSDOMNode(ANode) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMElement() { }
	
private:
	void *__IDOMElement;	// Xml::Xmldom::IDOMElement 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0E6-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMElement()
	{
		Xml::Xmldom::_di_IDOMElement intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMElement*(void) { return (Xml::Xmldom::IDOMElement*)&__IDOMElement; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMText : public TMSDOMCharacterData
{
	typedef TMSDOMCharacterData inherited;
	
protected:
	HRESULT __safecall splitText(int offset, Xml::Xmldom::_di_IDOMText &__splitText_result);
public:
	/* TMSDOMNode.Create */ inline __fastcall TMSDOMText(_di_IXMLDOMNode ANode) : TMSDOMCharacterData(ANode) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMText() { }
	
private:
	void *__IDOMText;	// Xml::Xmldom::IDOMText 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0E7-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMText()
	{
		Xml::Xmldom::_di_IDOMText intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMText*(void) { return (Xml::Xmldom::IDOMText*)&__IDOMText; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMComment : public TMSDOMCharacterData
{
	typedef TMSDOMCharacterData inherited;
	
public:
	/* TMSDOMNode.Create */ inline __fastcall TMSDOMComment(_di_IXMLDOMNode ANode) : TMSDOMCharacterData(ANode) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMComment() { }
	
private:
	void *__IDOMComment;	// Xml::Xmldom::IDOMComment 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0E8-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMComment()
	{
		Xml::Xmldom::_di_IDOMComment intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMComment*(void) { return (Xml::Xmldom::IDOMComment*)&__IDOMComment; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMCDATASection : public TMSDOMText
{
	typedef TMSDOMText inherited;
	
public:
	/* TMSDOMNode.Create */ inline __fastcall TMSDOMCDATASection(_di_IXMLDOMNode ANode) : TMSDOMText(ANode) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMCDATASection() { }
	
private:
	void *__IDOMCDATASection;	// Xml::Xmldom::IDOMCDATASection 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0E9-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMCDATASection()
	{
		Xml::Xmldom::_di_IDOMCDATASection intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMCDATASection*(void) { return (Xml::Xmldom::IDOMCDATASection*)&__IDOMCDATASection; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMDocumentType : public TMSDOMNode
{
	typedef TMSDOMNode inherited;
	
private:
	Xml::Xmldom::_di_IDOMNamedNodeMap FEntities;
	Xml::Xmldom::_di_IDOMNamedNodeMap FNotations;
	_di_IXMLDOMDocumentType __fastcall GetMSDocumentType();
	
protected:
	HRESULT __safecall get_name(System::UnicodeString &__get_name_result);
	HRESULT __safecall get_entities(Xml::Xmldom::_di_IDOMNamedNodeMap &__get_entities_result);
	HRESULT __safecall get_notations(Xml::Xmldom::_di_IDOMNamedNodeMap &__get_notations_result);
	HRESULT __safecall get_publicId(System::UnicodeString &__get_publicId_result);
	HRESULT __safecall get_systemId(System::UnicodeString &__get_systemId_result);
	HRESULT __safecall get_internalSubset(System::UnicodeString &__get_internalSubset_result);
	
public:
	__property _di_IXMLDOMDocumentType MSDocumentType = {read=GetMSDocumentType};
public:
	/* TMSDOMNode.Create */ inline __fastcall TMSDOMDocumentType(_di_IXMLDOMNode ANode) : TMSDOMNode(ANode) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMDocumentType() { }
	
private:
	void *__IDOMDocumentType;	// Xml::Xmldom::IDOMDocumentType 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0EA-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMDocumentType()
	{
		Xml::Xmldom::_di_IDOMDocumentType intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMDocumentType*(void) { return (Xml::Xmldom::IDOMDocumentType*)&__IDOMDocumentType; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMNotation : public TMSDOMNode
{
	typedef TMSDOMNode inherited;
	
private:
	_di_IXMLDOMNotation __fastcall GetMSNotation();
	
protected:
	HRESULT __safecall get_publicId(System::UnicodeString &__get_publicId_result);
	HRESULT __safecall get_systemId(System::UnicodeString &__get_systemId_result);
	
public:
	__property _di_IXMLDOMNotation MSNotation = {read=GetMSNotation};
public:
	/* TMSDOMNode.Create */ inline __fastcall TMSDOMNotation(_di_IXMLDOMNode ANode) : TMSDOMNode(ANode) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMNotation() { }
	
private:
	void *__IDOMNotation;	// Xml::Xmldom::IDOMNotation 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0EB-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMNotation()
	{
		Xml::Xmldom::_di_IDOMNotation intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMNotation*(void) { return (Xml::Xmldom::IDOMNotation*)&__IDOMNotation; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMEntity : public TMSDOMNode
{
	typedef TMSDOMNode inherited;
	
private:
	_di_IXMLDOMEntity __fastcall GetMSEntity();
	
protected:
	HRESULT __safecall get_publicId(System::UnicodeString &__get_publicId_result);
	HRESULT __safecall get_systemId(System::UnicodeString &__get_systemId_result);
	HRESULT __safecall get_notationName(System::UnicodeString &__get_notationName_result);
	
public:
	__property _di_IXMLDOMEntity MSEntity = {read=GetMSEntity};
public:
	/* TMSDOMNode.Create */ inline __fastcall TMSDOMEntity(_di_IXMLDOMNode ANode) : TMSDOMNode(ANode) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMEntity() { }
	
private:
	void *__IDOMEntity;	// Xml::Xmldom::IDOMEntity 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0EC-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMEntity()
	{
		Xml::Xmldom::_di_IDOMEntity intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMEntity*(void) { return (Xml::Xmldom::IDOMEntity*)&__IDOMEntity; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMEntityReference : public TMSDOMNode
{
	typedef TMSDOMNode inherited;
	
public:
	/* TMSDOMNode.Create */ inline __fastcall TMSDOMEntityReference(_di_IXMLDOMNode ANode) : TMSDOMNode(ANode) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMEntityReference() { }
	
private:
	void *__IDOMEntityReference;	// Xml::Xmldom::IDOMEntityReference 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0ED-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMEntityReference()
	{
		Xml::Xmldom::_di_IDOMEntityReference intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMEntityReference*(void) { return (Xml::Xmldom::IDOMEntityReference*)&__IDOMEntityReference; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMProcessingInstruction : public TMSDOMNode
{
	typedef TMSDOMNode inherited;
	
private:
	_di_IXMLDOMProcessingInstruction __fastcall GetMSProcessingInstruction();
	
protected:
	HRESULT __safecall get_target(System::UnicodeString &__get_target_result);
	HRESULT __safecall get_data(System::UnicodeString &__get_data_result);
	HRESULT __safecall set_data(const System::UnicodeString value);
	
public:
	__property _di_IXMLDOMProcessingInstruction MSProcessingInstruction = {read=GetMSProcessingInstruction};
public:
	/* TMSDOMNode.Create */ inline __fastcall TMSDOMProcessingInstruction(_di_IXMLDOMNode ANode) : TMSDOMNode(ANode) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMProcessingInstruction() { }
	
private:
	void *__IDOMProcessingInstruction;	// Xml::Xmldom::IDOMProcessingInstruction 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0EE-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMProcessingInstruction()
	{
		Xml::Xmldom::_di_IDOMProcessingInstruction intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMProcessingInstruction*(void) { return (Xml::Xmldom::IDOMProcessingInstruction*)&__IDOMProcessingInstruction; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMDocumentFragment : public TMSDOMNode
{
	typedef TMSDOMNode inherited;
	
public:
	/* TMSDOMNode.Create */ inline __fastcall TMSDOMDocumentFragment(_di_IXMLDOMNode ANode) : TMSDOMNode(ANode) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMDocumentFragment() { }
	
private:
	void *__IDOMDocumentFragment;	// Xml::Xmldom::IDOMDocumentFragment 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0EF-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMDocumentFragment()
	{
		Xml::Xmldom::_di_IDOMDocumentFragment intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMDocumentFragment*(void) { return (Xml::Xmldom::IDOMDocumentFragment*)&__IDOMDocumentFragment; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TMSDOMEventHandler : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::TObject* FSender;
	TMSDOMDocument* FDocument;
	Xml::Xmldom::TAsyncEventHandler FEventHandler;
	
protected:
	virtual HRESULT __stdcall GetIDsOfNames(const GUID &IID, void * Names, int NameCount, int LocaleID, void * DispIDs);
	virtual HRESULT __stdcall GetTypeInfo(int Index, int LocaleID, /* out */ void *TypeInfo);
	virtual HRESULT __stdcall GetTypeInfoCount(/* out */ int &Count);
	virtual HRESULT __stdcall Invoke(int DispID, const GUID &IID, int LocaleID, System::Word Flags, void *Params, void * VarResult, void * ExcepInfo, void * ArgErr);
	
public:
	__fastcall TMSDOMEventHandler(TMSDOMDocument* const Document, Xml::Xmldom::TAsyncEventHandler AsyncEventHandler, System::TObject* Sender);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMEventHandler() { }
	
private:
	void *__IDispatch;	// IDispatch 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00020400-0000-0000-C000-000000000046}
	operator _di_IDispatch()
	{
		_di_IDispatch intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDispatch*(void) { return (IDispatch*)&__IDispatch; }
	#endif
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMDocument : public TMSDOMNode
{
	typedef TMSDOMNode inherited;
	
private:
	_di_IXMLDOMDocument __fastcall GetMSDocument();
	
protected:
	HRESULT __safecall get_doctype(Xml::Xmldom::_di_IDOMDocumentType &__get_doctype_result);
	HRESULT __safecall get_domImplementation(Xml::Xmldom::_di_IDOMImplementation &__get_domImplementation_result);
	HRESULT __safecall get_documentElement(Xml::Xmldom::_di_IDOMElement &__get_documentElement_result);
	HRESULT __safecall set_documentElement(const Xml::Xmldom::_di_IDOMElement IDOMElement);
	HRESULT __safecall createElement(const System::UnicodeString tagName, Xml::Xmldom::_di_IDOMElement &__createElement_result);
	HRESULT __safecall createDocumentFragment(Xml::Xmldom::_di_IDOMDocumentFragment &__createDocumentFragment_result);
	HRESULT __safecall createTextNode(const System::UnicodeString data, Xml::Xmldom::_di_IDOMText &__createTextNode_result);
	HRESULT __safecall createComment(const System::UnicodeString data, Xml::Xmldom::_di_IDOMComment &__createComment_result);
	HRESULT __safecall createCDATASection(const System::UnicodeString data, Xml::Xmldom::_di_IDOMCDATASection &__createCDATASection_result);
	HRESULT __safecall createProcessingInstruction(const System::UnicodeString target, const System::UnicodeString data, Xml::Xmldom::_di_IDOMProcessingInstruction &__createProcessingInstruction_result);
	HRESULT __safecall createAttribute(const System::UnicodeString name, Xml::Xmldom::_di_IDOMAttr &__createAttribute_result);
	HRESULT __safecall createEntityReference(const System::UnicodeString name, Xml::Xmldom::_di_IDOMEntityReference &__createEntityReference_result);
	HRESULT __safecall getElementsByTagName(const System::UnicodeString tagName, Xml::Xmldom::_di_IDOMNodeList &__getElementsByTagName_result);
	HRESULT __safecall importNode(Xml::Xmldom::_di_IDOMNode importedNode, System::WordBool deep, Xml::Xmldom::_di_IDOMNode &__importNode_result);
	HRESULT __safecall createElementNS(const System::UnicodeString namespaceURI, const System::UnicodeString qualifiedName, Xml::Xmldom::_di_IDOMElement &__createElementNS_result);
	HRESULT __safecall createAttributeNS(const System::UnicodeString namespaceURI, const System::UnicodeString qualifiedName, Xml::Xmldom::_di_IDOMAttr &__createAttributeNS_result);
	HRESULT __safecall getElementsByTagNameNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName, Xml::Xmldom::_di_IDOMNodeList &__getElementsByTagNameNS_result);
	HRESULT __safecall getElementById(const System::UnicodeString elementId, Xml::Xmldom::_di_IDOMElement &__getElementById_result);
	HRESULT __safecall get_async(bool &__get_async_result);
	HRESULT __safecall get_preserveWhiteSpace(bool &__get_preserveWhiteSpace_result);
	HRESULT __safecall get_resolveExternals(bool &__get_resolveExternals_result);
	HRESULT __safecall get_validate(bool &__get_validate_result);
	HRESULT __safecall set_async(bool Value);
	HRESULT __safecall set_preserveWhiteSpace(bool Value);
	HRESULT __safecall set_resolveExternals(bool Value);
	HRESULT __safecall set_validate(bool Value);
	HIDESBASE HRESULT __safecall get_xml(System::UnicodeString &__get_xml_result);
	HRESULT __safecall asyncLoadState(int &__asyncLoadState_result);
	HRESULT __safecall load(System::OleVariant source, System::WordBool &__load_result);
	HRESULT __safecall loadFromStream(System::Classes::TStream* const stream, System::WordBool &__loadFromStream_result)/* overload */;
	HRESULT __safecall loadxml(const System::UnicodeString Value, System::WordBool &__loadxml_result);
	HRESULT __safecall save(System::OleVariant destination);
	HRESULT __safecall saveToStream(System::Classes::TStream* const stream)/* overload */;
	HRESULT __safecall set_OnAsyncLoad(System::TObject* const Sender, Xml::Xmldom::TAsyncEventHandler EventHandler);
	HRESULT __safecall loadFromStream(const _di_IStream stream, System::WordBool &__loadFromStream_result)/* overload */;
	HRESULT __safecall saveToStream(const _di_IStream stream)/* overload */;
	HRESULT __safecall get_errorCode(int &__get_errorCode_result);
	HRESULT __safecall get_url(System::UnicodeString &__get_url_result);
	HRESULT __safecall get_reason(System::UnicodeString &__get_reason_result);
	HRESULT __safecall get_srcText(System::UnicodeString &__get_srcText_result);
	HRESULT __safecall get_line(int &__get_line_result);
	HRESULT __safecall get_linepos(int &__get_linepos_result);
	HRESULT __safecall get_filepos(int &__get_filepos_result);
	
public:
	__property _di_IXMLDOMDocument MSDocument = {read=GetMSDocument};
public:
	/* TMSDOMNode.Create */ inline __fastcall TMSDOMDocument(_di_IXMLDOMNode ANode) : TMSDOMNode(ANode) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMDocument() { }
	
private:
	void *__IDOMParseError;	// Xml::Xmldom::IDOMParseError 
	void *__IDOMPersist;	// Xml::Xmldom::IDOMPersist 
	void *__IDOMParseOptions;	// Xml::Xmldom::IDOMParseOptions 
	void *__IDOMDocument;	// Xml::Xmldom::IDOMDocument 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0F2-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMParseError()
	{
		Xml::Xmldom::_di_IDOMParseError intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMParseError*(void) { return (Xml::Xmldom::IDOMParseError*)&__IDOMParseError; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0F1-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMPersist()
	{
		Xml::Xmldom::_di_IDOMPersist intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMPersist*(void) { return (Xml::Xmldom::IDOMPersist*)&__IDOMPersist; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0F3-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMParseOptions()
	{
		Xml::Xmldom::_di_IDOMParseOptions intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMParseOptions*(void) { return (Xml::Xmldom::IDOMParseOptions*)&__IDOMParseOptions; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2BF4C0F0-096E-11D4-83DA-00C04F60B2DD}
	operator Xml::Xmldom::_di_IDOMDocument()
	{
		Xml::Xmldom::_di_IDOMDocument intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Xml::Xmldom::IDOMDocument*(void) { return (Xml::Xmldom::IDOMDocument*)&__IDOMDocument; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSDOMImplementationFactory : public Xml::Xmldom::TDOMVendor
{
	typedef Xml::Xmldom::TDOMVendor inherited;
	
public:
	virtual Xml::Xmldom::_di_IDOMImplementation __fastcall DOMImplementation();
	virtual System::UnicodeString __fastcall Description();
public:
	/* TObject.Create */ inline __fastcall TMSDOMImplementationFactory() : Xml::Xmldom::TDOMVendor() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMSDOMImplementationFactory() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSXMLDOMDocumentFactory : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TDOMProperty
	{
	public:
		System::UnicodeString Name;
		System::OleVariant Value;
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
	typedef System::DynamicArray<TDOMProperty> TDOMPropertyList;
	
	
private:
	typedef System::DynamicArray<GUID> _TMSXMLDOMDocumentFactory__1;
	
	
private:
	static TDOMPropertyList FDOMProperties;
	static _TMSXMLDOMDocumentFactory__1 FDOMDocumentCoClasses;
	// __classmethod void __fastcall Create@();
	
protected:
	__classmethod virtual void __fastcall SetDOMProperties(_di_IXMLDOMDocument2 DOMDocument);
	__classmethod virtual System::_di_IInterface __fastcall TryCoCreateInstance(const GUID *GuidList, const int GuidList_High);
	
public:
	__classmethod virtual _di_IXMLDOMDocument __fastcall CreateDOMDocument();
	__classmethod void __fastcall SetDOMDocumentCoClasses(GUID *GuidList, const int GuidList_High);
	__classmethod void __fastcall AddDOMProperty(const System::UnicodeString PropName, const System::OleVariant &PropValue, bool UpdateExisting = true);
	/* static */ __property TDOMPropertyList DOMProperties = {read=FDOMProperties, write=FDOMProperties};
	
private:
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TMSXMLDOMDocumentFactory() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMSXMLDOMDocumentFactory() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TMSXMLDOMDocumentFactoryClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TMSXMLDOMDocumentFactoryClass);
#endif /* _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define SMSXML L"MSXML"
extern DELPHI_PACKAGE TMSDOMImplementationFactory* MSXML_DOM;
extern DELPHI_PACKAGE TMSXMLDOMDocumentFactoryClass MSXMLDOMDocumentFactory;
extern DELPHI_PACKAGE _di_IXMLDOMDocument __fastcall (*MSXMLDOMDocumentCreate _DEPRECATED_ATTRIBUTE1("Subclass and override TMSXMLDOMDocumentFactory.CreateDOMDocument") )(void);
extern DELPHI_PACKAGE bool MSXML6_ProhibitDTD _DEPRECATED_ATTRIBUTE1("Use: Xml.Win.msxmldom.MSXMLDOMDocumentFactory.AddDOMProp"
	"erty('ProhibitDTD', False);") ;
extern DELPHI_PACKAGE bool __fastcall LoadFromXMLString(const _di_IXMLDOMDocument Doc, const System::UnicodeString XML);
extern DELPHI_PACKAGE _di_IXMLDOMDocument __fastcall CreateDOMDocument _DEPRECATED_ATTRIBUTE1("Use MSXMLDOMDocumentFactory.CreateDOMDocument") (void);
}	/* namespace Msxmldom */
}	/* namespace Win */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_WIN_MSXMLDOM)
using namespace Xml::Win::Msxmldom;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_WIN)
using namespace Xml::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_Win_MsxmldomHPP
