// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.omnixmldom.pas' rev: 34.00 (Windows)

#ifndef Xml_OmnixmldomHPP
#define Xml_OmnixmldomHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.Win.ComObj.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.Internal.OmniXML.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Omnixmldom
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IOXMLDOMNodeRef;
typedef System::DelphiInterface<IOXMLDOMNodeRef> _di_IOXMLDOMNodeRef;
class DELPHICLASS TODOMInterface;
class DELPHICLASS TODOMImplementation;
class DELPHICLASS TODOMNode;
class DELPHICLASS TODOMNodeList;
class DELPHICLASS TODOMNamedNodeMap;
class DELPHICLASS TODOMCharacterData;
class DELPHICLASS TODOMAttr;
class DELPHICLASS TODOMElement;
class DELPHICLASS TODOMText;
class DELPHICLASS TODOMComment;
class DELPHICLASS TODOMCDATASection;
class DELPHICLASS TODOMDocumentType;
class DELPHICLASS TODOMEntityReference;
class DELPHICLASS TODOMProcessingInstruction;
class DELPHICLASS TODOMDocumentFragment;
class DELPHICLASS TODOMDocument;
class DELPHICLASS TODOMImplementationFactory;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{D278AAEE-0F97-446A-BBF6-69470F5F188C}") IOXMLDOMNodeRef  : public System::IInterface 
{
	virtual Xml::Internal::Omnixml::_di_OmniIXMLNode __fastcall GetXMLNode() = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TODOMInterface : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	virtual HRESULT __fastcall SafeCallException(System::TObject* ExceptObject, void * ExceptAddr);
public:
	/* TObject.Create */ inline __fastcall TODOMInterface() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TODOMInterface() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TODOMImplementation : public TODOMInterface
{
	typedef TODOMInterface inherited;
	
protected:
	System::WordBool __fastcall hasFeature(const System::UnicodeString feature, const System::UnicodeString version);
	HRESULT __safecall createDocumentType(const System::UnicodeString qualifiedName, const System::UnicodeString publicId, const System::UnicodeString systemId, Xml::Xmldom::_di_IDOMDocumentType &__createDocumentType_result);
	HRESULT __safecall createDocument(const System::UnicodeString namespaceURI, const System::UnicodeString qualifiedName, Xml::Xmldom::_di_IDOMDocumentType doctype, Xml::Xmldom::_di_IDOMDocument &__createDocument_result);
	
public:
	__fastcall TODOMImplementation();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TODOMImplementation() { }
	
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
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TODOMNode : public TODOMInterface
{
	typedef TODOMInterface inherited;
	
private:
	Xml::Internal::Omnixml::_di_OmniIXMLNode FNativeNode;
	Xml::Xmldom::_di_IDOMDocument FOwnerDocument;
	Xml::Xmldom::_di_IDOMNodeList FChildNodes;
	Xml::Xmldom::_di_IDOMNamedNodeMap FAttributes;
	
protected:
	Xml::Internal::Omnixml::_di_OmniIXMLNode __fastcall GetXMLNode();
	HRESULT __safecall get_nodeName(System::UnicodeString &__get_nodeName_result);
	HRESULT __safecall get_nodeValue(System::UnicodeString &__get_nodeValue_result);
	HRESULT __safecall set_nodeValue(System::UnicodeString value)/* overload */;
	HRESULT __safecall get_nodeType(System::Word &__get_nodeType_result);
	HRESULT __safecall get_parentNode(Xml::Xmldom::_di_IDOMNode &__get_parentNode_result);
	virtual HRESULT __safecall get_childNodes(Xml::Xmldom::_di_IDOMNodeList &__get_childNodes_result);
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
	virtual HRESULT __safecall hasChildNodes(System::WordBool &__hasChildNodes_result);
	HRESULT __safecall cloneNode(System::WordBool deep, Xml::Xmldom::_di_IDOMNode &__cloneNode_result);
	HRESULT __safecall normalize();
	System::WordBool __fastcall supports(const System::UnicodeString feature, const System::UnicodeString version);
	HRESULT __safecall get_text(System::UnicodeString &__get_text_result);
	HRESULT __safecall get_xml(System::UnicodeString &__get_xml_result);
	HRESULT __safecall set_text(const System::UnicodeString Value);
	HRESULT __safecall transformNode(const Xml::Xmldom::_di_IDOMNode stylesheet, System::WideString &output)/* overload */;
	HRESULT __safecall transformNode(const Xml::Xmldom::_di_IDOMNode stylesheet, const Xml::Xmldom::_di_IDOMDocument output)/* overload */;
	HRESULT __safecall selectNode(const System::WideString nodePath, Xml::Xmldom::_di_IDOMNode &__selectNode_result);
	HRESULT __safecall selectNodes(const System::WideString nodePath, Xml::Xmldom::_di_IDOMNodeList &__selectNodes_result);
	
public:
	__fastcall virtual TODOMNode(Xml::Internal::Omnixml::_di_OmniIXMLNode ANativeNode);
	__fastcall virtual ~TODOMNode();
	__property Xml::Internal::Omnixml::_di_OmniIXMLNode NativeNode = {read=FNativeNode};
private:
	void *__IDOMNodeSelect;	// Xml::Xmldom::IDOMNodeSelect 
	void *__IDOMNodeEx;	// Xml::Xmldom::IDOMNodeEx 
	void *__IOXMLDOMNodeRef;	// IOXMLDOMNodeRef 
	
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
	// {D278AAEE-0F97-446A-BBF6-69470F5F188C}
	operator _di_IOXMLDOMNodeRef()
	{
		_di_IOXMLDOMNodeRef intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IOXMLDOMNodeRef*(void) { return (IOXMLDOMNodeRef*)&__IOXMLDOMNodeRef; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TODOMNodeClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TODOMNodeClass);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TODOMNodeList : public TODOMInterface
{
	typedef TODOMInterface inherited;
	
private:
	Xml::Internal::Omnixml::_di_OmniIXMLNodeList FNativeNodeList;
	
protected:
	HRESULT __safecall get_item(int index, Xml::Xmldom::_di_IDOMNode &__get_item_result);
	HRESULT __safecall get_length(int &__get_length_result);
	
public:
	__fastcall TODOMNodeList(const Xml::Internal::Omnixml::_di_OmniIXMLNodeList ANativeNodeList)/* overload */;
	__fastcall TODOMNodeList(const System::UnicodeString AnXpath, TODOMNode* const AWrapperOwnerNode)/* overload */;
	__fastcall virtual ~TODOMNodeList();
	__property Xml::Internal::Omnixml::_di_OmniIXMLNodeList NativeNodeList = {read=FNativeNodeList};
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
class PASCALIMPLEMENTATION TODOMNamedNodeMap : public TODOMInterface
{
	typedef TODOMInterface inherited;
	
private:
	Xml::Internal::Omnixml::_di_OmniIXMLNamedNodeMap FNativeNamedNodeMap;
	
protected:
	HRESULT __safecall get_item(int index, Xml::Xmldom::_di_IDOMNode &__get_item_result);
	HRESULT __safecall get_length(int &__get_length_result);
	HRESULT __safecall getNamedItem(const System::UnicodeString name, Xml::Xmldom::_di_IDOMNode &__getNamedItem_result);
	HRESULT __safecall setNamedItem(const Xml::Xmldom::_di_IDOMNode arg, Xml::Xmldom::_di_IDOMNode &__setNamedItem_result);
	HRESULT __safecall removeNamedItem(const System::UnicodeString name, Xml::Xmldom::_di_IDOMNode &__removeNamedItem_result);
	HRESULT __safecall getNamedItemNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName, Xml::Xmldom::_di_IDOMNode &__getNamedItemNS_result);
	HRESULT __safecall setNamedItemNS(const Xml::Xmldom::_di_IDOMNode arg, Xml::Xmldom::_di_IDOMNode &__setNamedItemNS_result);
	HRESULT __safecall removeNamedItemNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName, Xml::Xmldom::_di_IDOMNode &__removeNamedItemNS_result);
	
public:
	__fastcall TODOMNamedNodeMap(const Xml::Internal::Omnixml::_di_OmniIXMLNamedNodeMap ANativeNamedNodeMap);
	__property Xml::Internal::Omnixml::_di_OmniIXMLNamedNodeMap NativeNamedNodeMap = {read=FNativeNamedNodeMap};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TODOMNamedNodeMap() { }
	
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
class PASCALIMPLEMENTATION TODOMCharacterData : public TODOMNode
{
	typedef TODOMNode inherited;
	
private:
	Xml::Internal::Omnixml::_di_OmniIXMLCharacterData __fastcall GetNativeCharacterData();
	
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
	__property Xml::Internal::Omnixml::_di_OmniIXMLCharacterData NativeCharacterData = {read=GetNativeCharacterData};
public:
	/* TODOMNode.Create */ inline __fastcall virtual TODOMCharacterData(Xml::Internal::Omnixml::_di_OmniIXMLNode ANativeNode) : TODOMNode(ANativeNode) { }
	/* TODOMNode.Destroy */ inline __fastcall virtual ~TODOMCharacterData() { }
	
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
class PASCALIMPLEMENTATION TODOMAttr : public TODOMNode
{
	typedef TODOMNode inherited;
	
private:
	Xml::Internal::Omnixml::_di_OmniIXMLAttr __fastcall GetNativeAttribute();
	
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
	__property Xml::Internal::Omnixml::_di_OmniIXMLAttr NativeAttribute = {read=GetNativeAttribute};
public:
	/* TODOMNode.Create */ inline __fastcall virtual TODOMAttr(Xml::Internal::Omnixml::_di_OmniIXMLNode ANativeNode) : TODOMNode(ANativeNode) { }
	/* TODOMNode.Destroy */ inline __fastcall virtual ~TODOMAttr() { }
	
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
class PASCALIMPLEMENTATION TODOMElement : public TODOMNode
{
	typedef TODOMNode inherited;
	
private:
	Xml::Internal::Omnixml::_di_OmniIXMLElement __fastcall GetNativeElement();
	
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
	__property Xml::Internal::Omnixml::_di_OmniIXMLElement NativeElement = {read=GetNativeElement};
public:
	/* TODOMNode.Create */ inline __fastcall virtual TODOMElement(Xml::Internal::Omnixml::_di_OmniIXMLNode ANativeNode) : TODOMNode(ANativeNode) { }
	/* TODOMNode.Destroy */ inline __fastcall virtual ~TODOMElement() { }
	
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
class PASCALIMPLEMENTATION TODOMText : public TODOMCharacterData
{
	typedef TODOMCharacterData inherited;
	
protected:
	HRESULT __safecall splitText(int offset, Xml::Xmldom::_di_IDOMText &__splitText_result);
public:
	/* TODOMNode.Create */ inline __fastcall virtual TODOMText(Xml::Internal::Omnixml::_di_OmniIXMLNode ANativeNode) : TODOMCharacterData(ANativeNode) { }
	/* TODOMNode.Destroy */ inline __fastcall virtual ~TODOMText() { }
	
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
class PASCALIMPLEMENTATION TODOMComment : public TODOMCharacterData
{
	typedef TODOMCharacterData inherited;
	
public:
	/* TODOMNode.Create */ inline __fastcall virtual TODOMComment(Xml::Internal::Omnixml::_di_OmniIXMLNode ANativeNode) : TODOMCharacterData(ANativeNode) { }
	/* TODOMNode.Destroy */ inline __fastcall virtual ~TODOMComment() { }
	
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
class PASCALIMPLEMENTATION TODOMCDATASection : public TODOMText
{
	typedef TODOMText inherited;
	
public:
	/* TODOMNode.Create */ inline __fastcall virtual TODOMCDATASection(Xml::Internal::Omnixml::_di_OmniIXMLNode ANativeNode) : TODOMText(ANativeNode) { }
	/* TODOMNode.Destroy */ inline __fastcall virtual ~TODOMCDATASection() { }
	
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
class PASCALIMPLEMENTATION TODOMDocumentType : public TODOMNode
{
	typedef TODOMNode inherited;
	
private:
	Xml::Internal::Omnixml::_di_OmniIXMLDocumentType __fastcall GetNativeDocumentType();
	
protected:
	virtual HRESULT __safecall get_childNodes(Xml::Xmldom::_di_IDOMNodeList &__get_childNodes_result);
	virtual HRESULT __safecall hasChildNodes(System::WordBool &__hasChildNodes_result);
	HRESULT __safecall get_name(System::UnicodeString &__get_name_result);
	HRESULT __safecall get_entities(Xml::Xmldom::_di_IDOMNamedNodeMap &__get_entities_result);
	HRESULT __safecall get_notations(Xml::Xmldom::_di_IDOMNamedNodeMap &__get_notations_result);
	HRESULT __safecall get_publicId(System::UnicodeString &__get_publicId_result);
	HRESULT __safecall get_systemId(System::UnicodeString &__get_systemId_result);
	HRESULT __safecall get_internalSubset(System::UnicodeString &__get_internalSubset_result);
	
public:
	__fastcall virtual TODOMDocumentType(Xml::Internal::Omnixml::_di_OmniIXMLNode ANativeNode);
	__fastcall virtual ~TODOMDocumentType();
	__property Xml::Internal::Omnixml::_di_OmniIXMLDocumentType NativeDocumentType = {read=GetNativeDocumentType};
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
class PASCALIMPLEMENTATION TODOMEntityReference : public TODOMNode
{
	typedef TODOMNode inherited;
	
public:
	/* TODOMNode.Create */ inline __fastcall virtual TODOMEntityReference(Xml::Internal::Omnixml::_di_OmniIXMLNode ANativeNode) : TODOMNode(ANativeNode) { }
	/* TODOMNode.Destroy */ inline __fastcall virtual ~TODOMEntityReference() { }
	
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
class PASCALIMPLEMENTATION TODOMProcessingInstruction : public TODOMNode
{
	typedef TODOMNode inherited;
	
private:
	Xml::Internal::Omnixml::_di_OmniIXMLProcessingInstruction __fastcall GetNativeProcessingInstruction();
	
protected:
	HRESULT __safecall get_target(System::UnicodeString &__get_target_result);
	HRESULT __safecall get_data(System::UnicodeString &__get_data_result);
	HRESULT __safecall set_data(const System::UnicodeString value);
	
public:
	__property Xml::Internal::Omnixml::_di_OmniIXMLProcessingInstruction NativeProcessingInstruction = {read=GetNativeProcessingInstruction};
public:
	/* TODOMNode.Create */ inline __fastcall virtual TODOMProcessingInstruction(Xml::Internal::Omnixml::_di_OmniIXMLNode ANativeNode) : TODOMNode(ANativeNode) { }
	/* TODOMNode.Destroy */ inline __fastcall virtual ~TODOMProcessingInstruction() { }
	
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
class PASCALIMPLEMENTATION TODOMDocumentFragment : public TODOMNode
{
	typedef TODOMNode inherited;
	
public:
	/* TODOMNode.Create */ inline __fastcall virtual TODOMDocumentFragment(Xml::Internal::Omnixml::_di_OmniIXMLNode ANativeNode) : TODOMNode(ANativeNode) { }
	/* TODOMNode.Destroy */ inline __fastcall virtual ~TODOMDocumentFragment() { }
	
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

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TODOMDocument : public TODOMNode
{
	typedef TODOMNode inherited;
	
private:
	TODOMImplementation* FWrapperDOMImpl;
	Xml::Xmldom::_di_IDOMElement FDocumentElement;
	Xml::Internal::Omnixml::_di_OmniIXMLElement FNativeDocumentElement;
	Xml::Internal::Omnixml::_di_OmniIXMLDocument FNativeDocument;
	
protected:
	Xml::Internal::Omnixml::_di_OmniIXMLDocument __fastcall GetNativeDocument();
	void __fastcall RemoveWhiteSpaceNodes();
	HRESULT __safecall get_doctype(Xml::Xmldom::_di_IDOMDocumentType &__get_doctype_result);
	HRESULT __safecall get_domImplementation(Xml::Xmldom::_di_IDOMImplementation &__get_domImplementation_result);
	HRESULT __safecall get_documentElement(Xml::Xmldom::_di_IDOMElement &__get_documentElement_result);
	HRESULT __safecall set_documentElement(const Xml::Xmldom::_di_IDOMElement DOMElement);
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
	__fastcall TODOMDocument(TODOMImplementation* AWrapperDOMImpl, Xml::Internal::Omnixml::_di_OmniIXMLDocument ANativeDoc, bool DocIsOwned);
	__fastcall virtual ~TODOMDocument();
	__property Xml::Internal::Omnixml::_di_OmniIXMLDocument NativeDocument = {read=GetNativeDocument};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_preserveWhiteSpace() { bool __r; HRESULT __hr = get_preserveWhiteSpace(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool PreserveWhitespace = {read=_scw_get_preserveWhiteSpace, nodefault};
	__property TODOMImplementation* WrapperDOMImpl = {read=FWrapperDOMImpl};
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
class PASCALIMPLEMENTATION TODOMImplementationFactory : public Xml::Xmldom::TDOMVendor
{
	typedef Xml::Xmldom::TDOMVendor inherited;
	
private:
	Xml::Xmldom::_di_IDOMImplementation FGlobalDOMImpl;
	
public:
	virtual Xml::Xmldom::_di_IDOMImplementation __fastcall DOMImplementation();
	virtual System::UnicodeString __fastcall Description();
public:
	/* TObject.Create */ inline __fastcall TODOMImplementationFactory() : Xml::Xmldom::TDOMVendor() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TODOMImplementationFactory() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define sOmniXmlVendor L"Omni XML"
extern DELPHI_PACKAGE TODOMImplementationFactory* OmniXML4Factory;
extern DELPHI_PACKAGE void __fastcall OmniUnitInitialization(void);
}	/* namespace Omnixmldom */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_OMNIXMLDOM)
using namespace Xml::Omnixmldom;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif

//-- user supplied -----------------------------------------------------------
#pragma startup OmniUnitInitialization 65

#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_OmnixmldomHPP
