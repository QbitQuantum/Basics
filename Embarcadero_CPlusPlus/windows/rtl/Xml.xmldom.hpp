// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.xmldom.pas' rev: 34.00 (Windows)

#ifndef Xml_XmldomHPP
#define Xml_XmldomHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.SysUtils.hpp>
#include <System.Variants.hpp>
#include <System.Classes.hpp>
#include <Xml.XMLConst.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Xmldom
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS DOMException;
class DELPHICLASS EDOMParseError;
__interface DELPHIINTERFACE IDOMImplementation;
typedef System::DelphiInterface<IDOMImplementation> _di_IDOMImplementation;
__interface DELPHIINTERFACE IDOMNode;
typedef System::DelphiInterface<IDOMNode> _di_IDOMNode;
__interface DELPHIINTERFACE IDOMNodeList;
typedef System::DelphiInterface<IDOMNodeList> _di_IDOMNodeList;
__interface DELPHIINTERFACE IDOMNamedNodeMap;
typedef System::DelphiInterface<IDOMNamedNodeMap> _di_IDOMNamedNodeMap;
__interface DELPHIINTERFACE IDOMCharacterData;
typedef System::DelphiInterface<IDOMCharacterData> _di_IDOMCharacterData;
__interface DELPHIINTERFACE IDOMAttr;
typedef System::DelphiInterface<IDOMAttr> _di_IDOMAttr;
__interface DELPHIINTERFACE IDOMElement;
typedef System::DelphiInterface<IDOMElement> _di_IDOMElement;
__interface DELPHIINTERFACE IDOMText;
typedef System::DelphiInterface<IDOMText> _di_IDOMText;
__interface DELPHIINTERFACE IDOMComment;
typedef System::DelphiInterface<IDOMComment> _di_IDOMComment;
__interface DELPHIINTERFACE IDOMCDATASection;
typedef System::DelphiInterface<IDOMCDATASection> _di_IDOMCDATASection;
__interface DELPHIINTERFACE IDOMDocumentType;
typedef System::DelphiInterface<IDOMDocumentType> _di_IDOMDocumentType;
__interface DELPHIINTERFACE IDOMNotation;
typedef System::DelphiInterface<IDOMNotation> _di_IDOMNotation;
__interface DELPHIINTERFACE IDOMEntity;
typedef System::DelphiInterface<IDOMEntity> _di_IDOMEntity;
__interface DELPHIINTERFACE IDOMEntityReference;
typedef System::DelphiInterface<IDOMEntityReference> _di_IDOMEntityReference;
__interface DELPHIINTERFACE IDOMProcessingInstruction;
typedef System::DelphiInterface<IDOMProcessingInstruction> _di_IDOMProcessingInstruction;
__interface DELPHIINTERFACE IDOMDocumentFragment;
typedef System::DelphiInterface<IDOMDocumentFragment> _di_IDOMDocumentFragment;
__interface DELPHIINTERFACE IDOMDocument;
typedef System::DelphiInterface<IDOMDocument> _di_IDOMDocument;
__interface DELPHIINTERFACE IDOMNodeEx;
typedef System::DelphiInterface<IDOMNodeEx> _di_IDOMNodeEx;
__interface DELPHIINTERFACE IDOMNodeSelect;
typedef System::DelphiInterface<IDOMNodeSelect> _di_IDOMNodeSelect;
__interface DELPHIINTERFACE IDOMXSLProcessor;
typedef System::DelphiInterface<IDOMXSLProcessor> _di_IDOMXSLProcessor;
__interface DELPHIINTERFACE IDOMPersist;
typedef System::DelphiInterface<IDOMPersist> _di_IDOMPersist;
__interface DELPHIINTERFACE IDOMParseError;
typedef System::DelphiInterface<IDOMParseError> _di_IDOMParseError;
__interface DELPHIINTERFACE IDOMParseOptions;
typedef System::DelphiInterface<IDOMParseOptions> _di_IDOMParseOptions;
__interface DELPHIINTERFACE IDOMXMLProlog;
typedef System::DelphiInterface<IDOMXMLProlog> _di_IDOMXMLProlog;
class DELPHICLASS TDOMVendor;
class DELPHICLASS TDOMVendorList;
//-- type declarations -------------------------------------------------------
typedef System::WideString XmlDomString;

typedef __int64 DOMTimeStamp;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DOMException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	System::Word code;
public:
	/* Exception.Create */ inline __fastcall DOMException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall DOMException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall DOMException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall DOMException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall DOMException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall DOMException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall DOMException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall DOMException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall DOMException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall DOMException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall DOMException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall DOMException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~DOMException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EDOMParseError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
private:
	_di_IDOMParseError FParseError;
	int __fastcall GetFilePos();
	int __fastcall GetLine();
	int __fastcall GetLinePos();
	System::UnicodeString __fastcall GetReason();
	System::UnicodeString __fastcall GetSrcText();
	System::UnicodeString __fastcall GetURL();
	int __fastcall GetErrorCode();
	
protected:
	__property _di_IDOMParseError ParseError = {read=FParseError};
	
public:
	__fastcall EDOMParseError(const _di_IDOMParseError ParseError, const System::UnicodeString Msg);
	__property int ErrorCode = {read=GetErrorCode, nodefault};
	__property System::UnicodeString URL = {read=GetURL};
	__property System::UnicodeString Reason = {read=GetReason};
	__property System::UnicodeString SrcText = {read=GetSrcText};
	__property int Line = {read=GetLine, nodefault};
	__property int LinePos = {read=GetLinePos, nodefault};
	__property int FilePos = {read=GetFilePos, nodefault};
public:
	/* Exception.CreateFmt */ inline __fastcall EDOMParseError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EDOMParseError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EDOMParseError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EDOMParseError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EDOMParseError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EDOMParseError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EDOMParseError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDOMParseError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDOMParseError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDOMParseError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDOMParseError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EDOMParseError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{2BF4C0E0-096E-11D4-83DA-00C04F60B2DD}") IDOMImplementation  : public System::IInterface 
{
	virtual System::WordBool __fastcall hasFeature(const System::UnicodeString feature, const System::UnicodeString version) = 0 ;
	virtual HRESULT __safecall createDocumentType(const System::UnicodeString qualifiedName, const System::UnicodeString publicId, const System::UnicodeString systemId, _di_IDOMDocumentType &__createDocumentType_result) = 0 ;
	virtual HRESULT __safecall createDocument(const System::UnicodeString namespaceURI, const System::UnicodeString qualifiedName, _di_IDOMDocumentType doctype, _di_IDOMDocument &__createDocument_result) = 0 ;
};

__interface  INTERFACE_UUID("{2BF4C0E1-096E-11D4-83DA-00C04F60B2DD}") IDOMNode  : public System::IInterface 
{
	virtual HRESULT __safecall get_nodeName(System::UnicodeString &__get_nodeName_result) = 0 ;
	virtual HRESULT __safecall get_nodeValue(System::UnicodeString &__get_nodeValue_result) = 0 ;
	virtual HRESULT __safecall set_nodeValue(System::UnicodeString value) = 0 ;
	virtual HRESULT __safecall get_nodeType(System::Word &__get_nodeType_result) = 0 ;
	virtual HRESULT __safecall get_parentNode(_di_IDOMNode &__get_parentNode_result) = 0 ;
	virtual HRESULT __safecall get_childNodes(_di_IDOMNodeList &__get_childNodes_result) = 0 ;
	virtual HRESULT __safecall get_firstChild(_di_IDOMNode &__get_firstChild_result) = 0 ;
	virtual HRESULT __safecall get_lastChild(_di_IDOMNode &__get_lastChild_result) = 0 ;
	virtual HRESULT __safecall get_previousSibling(_di_IDOMNode &__get_previousSibling_result) = 0 ;
	virtual HRESULT __safecall get_nextSibling(_di_IDOMNode &__get_nextSibling_result) = 0 ;
	virtual HRESULT __safecall get_attributes(_di_IDOMNamedNodeMap &__get_attributes_result) = 0 ;
	virtual HRESULT __safecall get_ownerDocument(_di_IDOMDocument &__get_ownerDocument_result) = 0 ;
	virtual HRESULT __safecall get_namespaceURI(System::UnicodeString &__get_namespaceURI_result) = 0 ;
	virtual HRESULT __safecall get_prefix(System::UnicodeString &__get_prefix_result) = 0 ;
	virtual HRESULT __safecall get_localName(System::UnicodeString &__get_localName_result) = 0 ;
	virtual HRESULT __safecall insertBefore(const _di_IDOMNode newChild, const _di_IDOMNode refChild, _di_IDOMNode &__insertBefore_result) = 0 ;
	virtual HRESULT __safecall replaceChild(const _di_IDOMNode newChild, const _di_IDOMNode oldChild, _di_IDOMNode &__replaceChild_result) = 0 ;
	virtual HRESULT __safecall removeChild(const _di_IDOMNode childNode, _di_IDOMNode &__removeChild_result) = 0 ;
	virtual HRESULT __safecall appendChild(const _di_IDOMNode newChild, _di_IDOMNode &__appendChild_result) = 0 ;
	virtual HRESULT __safecall hasChildNodes(System::WordBool &__hasChildNodes_result) = 0 ;
	virtual HRESULT __safecall cloneNode(System::WordBool deep, _di_IDOMNode &__cloneNode_result) = 0 ;
	virtual HRESULT __safecall normalize() = 0 ;
	virtual System::WordBool __fastcall supports(const System::UnicodeString feature, const System::UnicodeString version) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_nodeName() { System::UnicodeString __r; HRESULT __hr = get_nodeName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString nodeName = {read=_scw_get_nodeName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_nodeValue() { System::UnicodeString __r; HRESULT __hr = get_nodeValue(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString nodeValue = {read=_scw_get_nodeValue, write=set_nodeValue};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Word _scw_get_nodeType() { System::Word __r; HRESULT __hr = get_nodeType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Word nodeType = {read=_scw_get_nodeType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMNode _scw_get_parentNode() { _di_IDOMNode __r; HRESULT __hr = get_parentNode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMNode parentNode = {read=_scw_get_parentNode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMNodeList _scw_get_childNodes() { _di_IDOMNodeList __r; HRESULT __hr = get_childNodes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMNodeList childNodes = {read=_scw_get_childNodes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMNode _scw_get_firstChild() { _di_IDOMNode __r; HRESULT __hr = get_firstChild(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMNode firstChild = {read=_scw_get_firstChild};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMNode _scw_get_lastChild() { _di_IDOMNode __r; HRESULT __hr = get_lastChild(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMNode lastChild = {read=_scw_get_lastChild};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMNode _scw_get_previousSibling() { _di_IDOMNode __r; HRESULT __hr = get_previousSibling(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMNode previousSibling = {read=_scw_get_previousSibling};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMNode _scw_get_nextSibling() { _di_IDOMNode __r; HRESULT __hr = get_nextSibling(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMNode nextSibling = {read=_scw_get_nextSibling};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMNamedNodeMap _scw_get_attributes() { _di_IDOMNamedNodeMap __r; HRESULT __hr = get_attributes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMNamedNodeMap attributes = {read=_scw_get_attributes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMDocument _scw_get_ownerDocument() { _di_IDOMDocument __r; HRESULT __hr = get_ownerDocument(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMDocument ownerDocument = {read=_scw_get_ownerDocument};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_namespaceURI() { System::UnicodeString __r; HRESULT __hr = get_namespaceURI(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString namespaceURI = {read=_scw_get_namespaceURI};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_prefix() { System::UnicodeString __r; HRESULT __hr = get_prefix(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString prefix = {read=_scw_get_prefix};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_localName() { System::UnicodeString __r; HRESULT __hr = get_localName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString localName = {read=_scw_get_localName};
};

__interface  INTERFACE_UUID("{2BF4C0E2-096E-11D4-83DA-00C04F60B2DD}") IDOMNodeList  : public System::IInterface 
{
	
public:
	_di_IDOMNode operator[](int index) { return this->item[index]; }
	virtual HRESULT __safecall get_item(int index, _di_IDOMNode &__get_item_result) = 0 ;
	virtual HRESULT __safecall get_length(int &__get_length_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMNode _scw_get_item(int index) { _di_IDOMNode __r; HRESULT __hr = get_item(index, __r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMNode item[int index] = {read=_scw_get_item/*, default*/};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_length() { int __r; HRESULT __hr = get_length(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int length = {read=_scw_get_length};
};

__interface  INTERFACE_UUID("{2BF4C0E3-096E-11D4-83DA-00C04F60B2DD}") IDOMNamedNodeMap  : public System::IInterface 
{
	
public:
	_di_IDOMNode operator[](int index) { return this->item[index]; }
	virtual HRESULT __safecall get_item(int index, _di_IDOMNode &__get_item_result) = 0 ;
	virtual HRESULT __safecall get_length(int &__get_length_result) = 0 ;
	virtual HRESULT __safecall getNamedItem(const System::UnicodeString name, _di_IDOMNode &__getNamedItem_result) = 0 ;
	virtual HRESULT __safecall setNamedItem(const _di_IDOMNode arg, _di_IDOMNode &__setNamedItem_result) = 0 ;
	virtual HRESULT __safecall removeNamedItem(const System::UnicodeString name, _di_IDOMNode &__removeNamedItem_result) = 0 ;
	virtual HRESULT __safecall getNamedItemNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName, _di_IDOMNode &__getNamedItemNS_result) = 0 ;
	virtual HRESULT __safecall setNamedItemNS(const _di_IDOMNode arg, _di_IDOMNode &__setNamedItemNS_result) = 0 ;
	virtual HRESULT __safecall removeNamedItemNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName, _di_IDOMNode &__removeNamedItemNS_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMNode _scw_get_item(int index) { _di_IDOMNode __r; HRESULT __hr = get_item(index, __r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMNode item[int index] = {read=_scw_get_item/*, default*/};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_length() { int __r; HRESULT __hr = get_length(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int length = {read=_scw_get_length};
};

__interface  INTERFACE_UUID("{2BF4C0E4-096E-11D4-83DA-00C04F60B2DD}") IDOMCharacterData  : public IDOMNode 
{
	virtual HRESULT __safecall get_data(System::UnicodeString &__get_data_result) = 0 ;
	virtual HRESULT __safecall set_data(const System::UnicodeString data) = 0 ;
	virtual HRESULT __safecall get_length(int &__get_length_result) = 0 ;
	virtual HRESULT __safecall substringData(int offset, int count, System::UnicodeString &__substringData_result) = 0 ;
	virtual HRESULT __safecall appendData(const System::UnicodeString data) = 0 ;
	virtual HRESULT __safecall insertData(int offset, const System::UnicodeString data) = 0 ;
	virtual HRESULT __safecall deleteData(int offset, int count) = 0 ;
	virtual HRESULT __safecall replaceData(int offset, int count, const System::UnicodeString data) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_data() { System::UnicodeString __r; HRESULT __hr = get_data(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString data = {read=_scw_get_data, write=set_data};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_length() { int __r; HRESULT __hr = get_length(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int length = {read=_scw_get_length};
};

__interface  INTERFACE_UUID("{2BF4C0E5-096E-11D4-83DA-00C04F60B2DD}") IDOMAttr  : public IDOMNode 
{
	virtual HRESULT __safecall get_name(System::UnicodeString &__get_name_result) = 0 ;
	virtual HRESULT __safecall get_specified(System::WordBool &__get_specified_result) = 0 ;
	virtual HRESULT __safecall get_value(System::UnicodeString &__get_value_result) = 0 ;
	virtual HRESULT __safecall set_value(const System::UnicodeString attributeValue) = 0 ;
	virtual HRESULT __safecall get_ownerElement(_di_IDOMElement &__get_ownerElement_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_name() { System::UnicodeString __r; HRESULT __hr = get_name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString name = {read=_scw_get_name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_get_specified() { System::WordBool __r; HRESULT __hr = get_specified(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool specified = {read=_scw_get_specified};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_value() { System::UnicodeString __r; HRESULT __hr = get_value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString value = {read=_scw_get_value, write=set_value};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMElement _scw_get_ownerElement() { _di_IDOMElement __r; HRESULT __hr = get_ownerElement(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMElement ownerElement = {read=_scw_get_ownerElement};
};

__interface  INTERFACE_UUID("{2BF4C0E6-096E-11D4-83DA-00C04F60B2DD}") IDOMElement  : public IDOMNode 
{
	virtual HRESULT __safecall get_tagName(System::UnicodeString &__get_tagName_result) = 0 ;
	virtual HRESULT __safecall getAttribute(const System::UnicodeString name, System::UnicodeString &__getAttribute_result) = 0 ;
	virtual HRESULT __safecall setAttribute(const System::UnicodeString name, const System::UnicodeString value) = 0 ;
	virtual HRESULT __safecall removeAttribute(const System::UnicodeString name) = 0 ;
	virtual HRESULT __safecall getAttributeNode(const System::UnicodeString name, _di_IDOMAttr &__getAttributeNode_result) = 0 ;
	virtual HRESULT __safecall setAttributeNode(const _di_IDOMAttr newAttr, _di_IDOMAttr &__setAttributeNode_result) = 0 ;
	virtual HRESULT __safecall removeAttributeNode(const _di_IDOMAttr oldAttr, _di_IDOMAttr &__removeAttributeNode_result) = 0 ;
	virtual HRESULT __safecall getElementsByTagName(const System::UnicodeString name, _di_IDOMNodeList &__getElementsByTagName_result) = 0 ;
	virtual HRESULT __safecall getAttributeNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName, System::UnicodeString &__getAttributeNS_result) = 0 ;
	virtual HRESULT __safecall setAttributeNS(const System::UnicodeString namespaceURI, const System::UnicodeString qualifiedName, const System::UnicodeString value) = 0 ;
	virtual HRESULT __safecall removeAttributeNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName) = 0 ;
	virtual HRESULT __safecall getAttributeNodeNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName, _di_IDOMAttr &__getAttributeNodeNS_result) = 0 ;
	virtual HRESULT __safecall setAttributeNodeNS(const _di_IDOMAttr newAttr, _di_IDOMAttr &__setAttributeNodeNS_result) = 0 ;
	virtual HRESULT __safecall getElementsByTagNameNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName, _di_IDOMNodeList &__getElementsByTagNameNS_result) = 0 ;
	virtual HRESULT __safecall hasAttribute(const System::UnicodeString name, System::WordBool &__hasAttribute_result) = 0 ;
	virtual HRESULT __safecall hasAttributeNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName, System::WordBool &__hasAttributeNS_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_tagName() { System::UnicodeString __r; HRESULT __hr = get_tagName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString tagName = {read=_scw_get_tagName};
};

__interface  INTERFACE_UUID("{2BF4C0E7-096E-11D4-83DA-00C04F60B2DD}") IDOMText  : public IDOMCharacterData 
{
	virtual HRESULT __safecall splitText(int offset, _di_IDOMText &__splitText_result) = 0 ;
};

__interface  INTERFACE_UUID("{2BF4C0E8-096E-11D4-83DA-00C04F60B2DD}") IDOMComment  : public IDOMCharacterData 
{
	
};

__interface  INTERFACE_UUID("{2BF4C0E9-096E-11D4-83DA-00C04F60B2DD}") IDOMCDATASection  : public IDOMText 
{
	
};

__interface  INTERFACE_UUID("{2BF4C0EA-096E-11D4-83DA-00C04F60B2DD}") IDOMDocumentType  : public IDOMNode 
{
	virtual HRESULT __safecall get_name(System::UnicodeString &__get_name_result) = 0 ;
	virtual HRESULT __safecall get_entities(_di_IDOMNamedNodeMap &__get_entities_result) = 0 ;
	virtual HRESULT __safecall get_notations(_di_IDOMNamedNodeMap &__get_notations_result) = 0 ;
	virtual HRESULT __safecall get_publicId(System::UnicodeString &__get_publicId_result) = 0 ;
	virtual HRESULT __safecall get_systemId(System::UnicodeString &__get_systemId_result) = 0 ;
	virtual HRESULT __safecall get_internalSubset(System::UnicodeString &__get_internalSubset_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_name() { System::UnicodeString __r; HRESULT __hr = get_name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString name = {read=_scw_get_name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMNamedNodeMap _scw_get_entities() { _di_IDOMNamedNodeMap __r; HRESULT __hr = get_entities(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMNamedNodeMap entities = {read=_scw_get_entities};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMNamedNodeMap _scw_get_notations() { _di_IDOMNamedNodeMap __r; HRESULT __hr = get_notations(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMNamedNodeMap notations = {read=_scw_get_notations};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_publicId() { System::UnicodeString __r; HRESULT __hr = get_publicId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString publicId = {read=_scw_get_publicId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_systemId() { System::UnicodeString __r; HRESULT __hr = get_systemId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString systemId = {read=_scw_get_systemId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_internalSubset() { System::UnicodeString __r; HRESULT __hr = get_internalSubset(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString internalSubset = {read=_scw_get_internalSubset};
};

__interface  INTERFACE_UUID("{2BF4C0EB-096E-11D4-83DA-00C04F60B2DD}") IDOMNotation  : public IDOMNode 
{
	virtual HRESULT __safecall get_publicId(System::UnicodeString &__get_publicId_result) = 0 ;
	virtual HRESULT __safecall get_systemId(System::UnicodeString &__get_systemId_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_publicId() { System::UnicodeString __r; HRESULT __hr = get_publicId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString publicId = {read=_scw_get_publicId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_systemId() { System::UnicodeString __r; HRESULT __hr = get_systemId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString systemId = {read=_scw_get_systemId};
};

__interface  INTERFACE_UUID("{2BF4C0EC-096E-11D4-83DA-00C04F60B2DD}") IDOMEntity  : public IDOMNode 
{
	virtual HRESULT __safecall get_publicId(System::UnicodeString &__get_publicId_result) = 0 ;
	virtual HRESULT __safecall get_systemId(System::UnicodeString &__get_systemId_result) = 0 ;
	virtual HRESULT __safecall get_notationName(System::UnicodeString &__get_notationName_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_publicId() { System::UnicodeString __r; HRESULT __hr = get_publicId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString publicId = {read=_scw_get_publicId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_systemId() { System::UnicodeString __r; HRESULT __hr = get_systemId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString systemId = {read=_scw_get_systemId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_notationName() { System::UnicodeString __r; HRESULT __hr = get_notationName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString notationName = {read=_scw_get_notationName};
};

__interface  INTERFACE_UUID("{2BF4C0ED-096E-11D4-83DA-00C04F60B2DD}") IDOMEntityReference  : public IDOMNode 
{
	
};

__interface  INTERFACE_UUID("{2BF4C0EE-096E-11D4-83DA-00C04F60B2DD}") IDOMProcessingInstruction  : public IDOMNode 
{
	virtual HRESULT __safecall get_target(System::UnicodeString &__get_target_result) = 0 ;
	virtual HRESULT __safecall get_data(System::UnicodeString &__get_data_result) = 0 ;
	virtual HRESULT __safecall set_data(const System::UnicodeString value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_target() { System::UnicodeString __r; HRESULT __hr = get_target(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString target = {read=_scw_get_target};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_data() { System::UnicodeString __r; HRESULT __hr = get_data(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString data = {read=_scw_get_data, write=set_data};
};

__interface  INTERFACE_UUID("{2BF4C0EF-096E-11D4-83DA-00C04F60B2DD}") IDOMDocumentFragment  : public IDOMNode 
{
	
};

__interface  INTERFACE_UUID("{2BF4C0F0-096E-11D4-83DA-00C04F60B2DD}") IDOMDocument  : public IDOMNode 
{
	virtual HRESULT __safecall get_doctype(_di_IDOMDocumentType &__get_doctype_result) = 0 ;
	virtual HRESULT __safecall get_domImplementation(_di_IDOMImplementation &__get_domImplementation_result) = 0 ;
	virtual HRESULT __safecall get_documentElement(_di_IDOMElement &__get_documentElement_result) = 0 ;
	virtual HRESULT __safecall set_documentElement(const _di_IDOMElement Element) = 0 ;
	virtual HRESULT __safecall createElement(const System::UnicodeString tagName, _di_IDOMElement &__createElement_result) = 0 ;
	virtual HRESULT __safecall createDocumentFragment(_di_IDOMDocumentFragment &__createDocumentFragment_result) = 0 ;
	virtual HRESULT __safecall createTextNode(const System::UnicodeString data, _di_IDOMText &__createTextNode_result) = 0 ;
	virtual HRESULT __safecall createComment(const System::UnicodeString data, _di_IDOMComment &__createComment_result) = 0 ;
	virtual HRESULT __safecall createCDATASection(const System::UnicodeString data, _di_IDOMCDATASection &__createCDATASection_result) = 0 ;
	virtual HRESULT __safecall createProcessingInstruction(const System::UnicodeString target, const System::UnicodeString data, _di_IDOMProcessingInstruction &__createProcessingInstruction_result) = 0 ;
	virtual HRESULT __safecall createAttribute(const System::UnicodeString name, _di_IDOMAttr &__createAttribute_result) = 0 ;
	virtual HRESULT __safecall createEntityReference(const System::UnicodeString name, _di_IDOMEntityReference &__createEntityReference_result) = 0 ;
	virtual HRESULT __safecall getElementsByTagName(const System::UnicodeString tagName, _di_IDOMNodeList &__getElementsByTagName_result) = 0 ;
	virtual HRESULT __safecall importNode(_di_IDOMNode importedNode, System::WordBool deep, _di_IDOMNode &__importNode_result) = 0 ;
	virtual HRESULT __safecall createElementNS(const System::UnicodeString namespaceURI, const System::UnicodeString qualifiedName, _di_IDOMElement &__createElementNS_result) = 0 ;
	virtual HRESULT __safecall createAttributeNS(const System::UnicodeString namespaceURI, const System::UnicodeString qualifiedName, _di_IDOMAttr &__createAttributeNS_result) = 0 ;
	virtual HRESULT __safecall getElementsByTagNameNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName, _di_IDOMNodeList &__getElementsByTagNameNS_result) = 0 ;
	virtual HRESULT __safecall getElementById(const System::UnicodeString elementId, _di_IDOMElement &__getElementById_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMDocumentType _scw_get_doctype() { _di_IDOMDocumentType __r; HRESULT __hr = get_doctype(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMDocumentType doctype = {read=_scw_get_doctype};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMImplementation _scw_get_domImplementation() { _di_IDOMImplementation __r; HRESULT __hr = get_domImplementation(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMImplementation domImplementation = {read=_scw_get_domImplementation};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMElement _scw_get_documentElement() { _di_IDOMElement __r; HRESULT __hr = get_documentElement(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMElement documentElement = {read=_scw_get_documentElement, write=set_documentElement};
};

__interface  INTERFACE_UUID("{B06BFFDD-337B-48DA-980B-6F7AA8ADE85C}") IDOMNodeEx  : public IDOMNode 
{
	virtual HRESULT __safecall get_text(System::UnicodeString &__get_text_result) = 0 ;
	virtual HRESULT __safecall get_xml(System::UnicodeString &__get_xml_result) = 0 ;
	virtual HRESULT __safecall set_text(const System::UnicodeString Value) = 0 ;
	virtual HRESULT __safecall transformNode(const _di_IDOMNode stylesheet, System::WideString &output) = 0 /* overload */;
	virtual HRESULT __safecall transformNode(const _di_IDOMNode stylesheet, const _di_IDOMDocument output) = 0 /* overload */;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_text() { System::UnicodeString __r; HRESULT __hr = get_text(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString text = {read=_scw_get_text, write=set_text};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_xml() { System::UnicodeString __r; HRESULT __hr = get_xml(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString xml = {read=_scw_get_xml};
};

__interface  INTERFACE_UUID("{2A3602E0-2B39-11D4-83DA-00C04F60B2DD}") IDOMNodeSelect  : public System::IInterface 
{
	virtual HRESULT __safecall selectNode(const System::WideString nodePath, _di_IDOMNode &__selectNode_result) = 0 ;
	virtual HRESULT __safecall selectNodes(const System::WideString nodePath, _di_IDOMNodeList &__selectNodes_result) = 0 ;
};

__interface  INTERFACE_UUID("{2BF4C0F4-096E-11D4-83DA-00C04F60B2DD}") IDOMXSLProcessor  : public System::IInterface 
{
	virtual HRESULT __safecall Get_input(System::OleVariant &__Get_input_result) = 0 ;
	virtual HRESULT __safecall Get_output(System::OleVariant &__Get_output_result) = 0 ;
	virtual HRESULT __safecall Get_stylesheet(_di_IDOMNode &__Get_stylesheet_result) = 0 ;
	virtual HRESULT __safecall Set_input(const System::OleVariant &value) = 0 ;
	virtual HRESULT __safecall Set_output(const System::OleVariant &value) = 0 ;
	virtual HRESULT __safecall setParameter(const System::UnicodeString Name, System::OleVariant Value, const System::UnicodeString namespaceURI) = 0 ;
	virtual HRESULT __safecall reset() = 0 ;
	virtual HRESULT __safecall transform(System::WordBool &__transform_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_input() { System::OleVariant __r; HRESULT __hr = Get_input(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant input = {read=_scw_Get_input, write=Set_input};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_output() { System::OleVariant __r; HRESULT __hr = Get_output(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant output = {read=_scw_Get_output, write=Set_output};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDOMNode _scw_Get_stylesheet() { _di_IDOMNode __r; HRESULT __hr = Get_stylesheet(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDOMNode stylesheet = {read=_scw_Get_stylesheet};
};

typedef void __fastcall (__closure *TAsyncEventHandler)(System::TObject* Sender, int AsyncLoadState);

__interface  INTERFACE_UUID("{2BF4C0F1-096E-11D4-83DA-00C04F60B2DD}") IDOMPersist  : public System::IInterface 
{
	virtual HRESULT __safecall get_xml(System::UnicodeString &__get_xml_result) = 0 ;
	virtual HRESULT __safecall asyncLoadState(int &__asyncLoadState_result) = 0 ;
	virtual HRESULT __safecall load(System::OleVariant source, System::WordBool &__load_result) = 0 ;
	virtual HRESULT __safecall loadFromStream(System::Classes::TStream* const stream, System::WordBool &__loadFromStream_result) = 0 /* overload */;
	virtual HRESULT __safecall loadxml(const System::UnicodeString Value, System::WordBool &__loadxml_result) = 0 ;
	virtual HRESULT __safecall save(System::OleVariant destination) = 0 ;
	virtual HRESULT __safecall saveToStream(System::Classes::TStream* const stream) = 0 /* overload */;
	virtual HRESULT __safecall set_OnAsyncLoad(System::TObject* const Sender, TAsyncEventHandler EventHandler) = 0 ;
	virtual HRESULT __safecall loadFromStream(const _di_IStream stream, System::WordBool &__loadFromStream_result) = 0 /* overload */;
	virtual HRESULT __safecall saveToStream(const _di_IStream stream) = 0 /* overload */;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_xml() { System::UnicodeString __r; HRESULT __hr = get_xml(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString xml = {read=_scw_get_xml};
};

__interface  INTERFACE_UUID("{2BF4C0F2-096E-11D4-83DA-00C04F60B2DD}") IDOMParseError  : public System::IInterface 
{
	virtual HRESULT __safecall get_errorCode(int &__get_errorCode_result) = 0 ;
	virtual HRESULT __safecall get_url(System::UnicodeString &__get_url_result) = 0 ;
	virtual HRESULT __safecall get_reason(System::UnicodeString &__get_reason_result) = 0 ;
	virtual HRESULT __safecall get_srcText(System::UnicodeString &__get_srcText_result) = 0 ;
	virtual HRESULT __safecall get_line(int &__get_line_result) = 0 ;
	virtual HRESULT __safecall get_linepos(int &__get_linepos_result) = 0 ;
	virtual HRESULT __safecall get_filepos(int &__get_filepos_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_errorCode() { int __r; HRESULT __hr = get_errorCode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int errorCode = {read=_scw_get_errorCode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_url() { System::UnicodeString __r; HRESULT __hr = get_url(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString url = {read=_scw_get_url};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_reason() { System::UnicodeString __r; HRESULT __hr = get_reason(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString reason = {read=_scw_get_reason};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_srcText() { System::UnicodeString __r; HRESULT __hr = get_srcText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString srcText = {read=_scw_get_srcText};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_line() { int __r; HRESULT __hr = get_line(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int line = {read=_scw_get_line};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_linepos() { int __r; HRESULT __hr = get_linepos(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int linePos = {read=_scw_get_linepos};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_filepos() { int __r; HRESULT __hr = get_filepos(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int filePos = {read=_scw_get_filepos};
};

__interface  INTERFACE_UUID("{2BF4C0F3-096E-11D4-83DA-00C04F60B2DD}") IDOMParseOptions  : public System::IInterface 
{
	virtual HRESULT __safecall get_async(bool &__get_async_result) = 0 ;
	virtual HRESULT __safecall get_preserveWhiteSpace(bool &__get_preserveWhiteSpace_result) = 0 ;
	virtual HRESULT __safecall get_resolveExternals(bool &__get_resolveExternals_result) = 0 ;
	virtual HRESULT __safecall get_validate(bool &__get_validate_result) = 0 ;
	virtual HRESULT __safecall set_async(bool Value) = 0 ;
	virtual HRESULT __safecall set_preserveWhiteSpace(bool Value) = 0 ;
	virtual HRESULT __safecall set_resolveExternals(bool Value) = 0 ;
	virtual HRESULT __safecall set_validate(bool Value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_async() { bool __r; HRESULT __hr = get_async(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool async = {read=_scw_get_async, write=set_async};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_preserveWhiteSpace() { bool __r; HRESULT __hr = get_preserveWhiteSpace(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool preserveWhiteSpace = {read=_scw_get_preserveWhiteSpace, write=set_preserveWhiteSpace};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_resolveExternals() { bool __r; HRESULT __hr = get_resolveExternals(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool resolveExternals = {read=_scw_get_resolveExternals, write=set_resolveExternals};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_validate() { bool __r; HRESULT __hr = get_validate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool validate = {read=_scw_get_validate, write=set_validate};
};

__interface  INTERFACE_UUID("{7C192633-C267-483C-B0D5-89289A14D522}") IDOMXMLProlog  : public System::IInterface 
{
	virtual HRESULT __safecall get_Encoding(System::UnicodeString &__get_Encoding_result) = 0 ;
	virtual HRESULT __safecall get_Standalone(System::UnicodeString &__get_Standalone_result) = 0 ;
	virtual HRESULT __safecall get_Version(System::UnicodeString &__get_Version_result) = 0 ;
	virtual HRESULT __safecall set_Encoding(const System::UnicodeString Value) = 0 ;
	virtual HRESULT __safecall set_Standalone(const System::UnicodeString Value) = 0 ;
	virtual HRESULT __safecall set_Version(const System::UnicodeString Value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_Encoding() { System::UnicodeString __r; HRESULT __hr = get_Encoding(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString Encoding = {read=_scw_get_Encoding, write=set_Encoding};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_Standalone() { System::UnicodeString __r; HRESULT __hr = get_Standalone(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString Standalone = {read=_scw_get_Standalone, write=set_Standalone};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::UnicodeString _scw_get_Version() { System::UnicodeString __r; HRESULT __hr = get_Version(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::UnicodeString Version = {read=_scw_get_Version, write=set_Version};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDOMVendor : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual System::UnicodeString __fastcall Description() = 0 ;
	virtual _di_IDOMImplementation __fastcall DOMImplementation() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TDOMVendor() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDOMVendor() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::DynamicArray<TDOMVendor*> TDOMVendorArray;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDOMVendorList : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TDOMVendor* operator[](int Index) { return this->Vendors[Index]; }
	
private:
	TDOMVendorArray FVendors;
	
protected:
	TDOMVendor* __fastcall GetVendors(int Index);
	
public:
	void __fastcall Add(TDOMVendor* const Vendor);
	int __fastcall Count();
	TDOMVendor* __fastcall Find(const System::UnicodeString VendorDesc);
	void __fastcall Remove(TDOMVendor* const Vendor);
	__property TDOMVendor* Vendors[int Index] = {read=GetVendors/*, default*/};
public:
	/* TObject.Create */ inline __fastcall TDOMVendorList() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDOMVendorList() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define DOMWrapperVersion  (1.400000E+00)
static const System::Int8 ELEMENT_NODE = System::Int8(0x1);
static const System::Int8 ATTRIBUTE_NODE = System::Int8(0x2);
static const System::Int8 TEXT_NODE = System::Int8(0x3);
static const System::Int8 CDATA_SECTION_NODE = System::Int8(0x4);
static const System::Int8 ENTITY_REFERENCE_NODE = System::Int8(0x5);
static const System::Int8 ENTITY_NODE = System::Int8(0x6);
static const System::Int8 PROCESSING_INSTRUCTION_NODE = System::Int8(0x7);
static const System::Int8 COMMENT_NODE = System::Int8(0x8);
static const System::Int8 DOCUMENT_NODE = System::Int8(0x9);
static const System::Int8 DOCUMENT_TYPE_NODE = System::Int8(0xa);
static const System::Int8 DOCUMENT_FRAGMENT_NODE = System::Int8(0xb);
static const System::Int8 NOTATION_NODE = System::Int8(0xc);
static const System::Int8 INDEX_SIZE_ERR = System::Int8(0x1);
static const System::Int8 DOMSTRING_SIZE_ERR = System::Int8(0x2);
static const System::Int8 HIERARCHY_REQUEST_ERR = System::Int8(0x3);
static const System::Int8 WRONG_DOCUMENT_ERR = System::Int8(0x4);
static const System::Int8 INVALID_CHARACTER_ERR = System::Int8(0x5);
static const System::Int8 NO_DATA_ALLOWED_ERR = System::Int8(0x6);
static const System::Int8 NO_MODIFICATION_ALLOWED_ERR = System::Int8(0x7);
static const System::Int8 NOT_FOUND_ERR = System::Int8(0x8);
static const System::Int8 NOT_SUPPORTED_ERR = System::Int8(0x9);
static const System::Int8 INUSE_ATTRIBUTE_ERR = System::Int8(0xa);
static const System::Int8 INVALID_STATE_ERR = System::Int8(0xb);
static const System::Int8 SYNTAX_ERR = System::Int8(0xc);
static const System::Int8 INVALID_MODIFICATION_ERR = System::Int8(0xd);
static const System::Int8 NAMESPACE_ERR = System::Int8(0xe);
static const System::Int8 INVALID_ACCESS_ERR = System::Int8(0xf);
static const System::WideChar NSDelim = (System::WideChar)(0x3a);
#define SXML L"xml"
#define SVersion L"version"
#define SEncoding L"encoding"
#define SStandalone L"standalone"
#define SXMLNS L"xmlns"
#define SHttp L"http:/"
#define SXMLNamespaceURI L"http://www.w3.org/2000/xmlns/"
#define SXMLPrefixNamespaceURI L"http://www.w3.org/XML/1998/namespace"
extern DELPHI_PACKAGE System::UnicodeString DefaultDOMVendor;
extern DELPHI_PACKAGE System::UnicodeString CurrentDOMVendor;
extern DELPHI_PACKAGE TDOMVendorList* DOMVendors;
extern DELPHI_PACKAGE bool __fastcall IsPrefixed(const System::UnicodeString AName);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ExtractLocalName(const System::UnicodeString AName);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ExtractPrefix(const System::UnicodeString AName);
extern DELPHI_PACKAGE System::UnicodeString __fastcall MakeNodeName(const System::UnicodeString Prefix, const System::UnicodeString LocalName);
extern DELPHI_PACKAGE bool __fastcall SameNamespace(const _di_IDOMNode Node, const System::UnicodeString namespaceURI)/* overload */;
extern DELPHI_PACKAGE bool __fastcall SameNamespace(const System::UnicodeString URI1, const System::UnicodeString URI2)/* overload */;
extern DELPHI_PACKAGE bool __fastcall NodeMatches(const _di_IDOMNode Node, const System::UnicodeString TagName, const System::UnicodeString NamespaceURI)/* overload */;
extern DELPHI_PACKAGE _di_IDOMNodeEx __fastcall GetDOMNodeEx(const _di_IDOMNode Node);
extern DELPHI_PACKAGE void __fastcall RegisterDOMVendor(TDOMVendor* const Vendor);
extern DELPHI_PACKAGE void __fastcall UnRegisterDOMVendor(TDOMVendor* const Vendor);
extern DELPHI_PACKAGE TDOMVendor* __fastcall GetDOMVendor(System::UnicodeString VendorDesc);
extern DELPHI_PACKAGE _di_IDOMImplementation __fastcall GetDOM(const System::UnicodeString VendorDesc = System::UnicodeString());
extern DELPHI_PACKAGE void __fastcall DOMVendorNotSupported(const System::UnicodeString PropOrMethod, const System::UnicodeString VendorName);
}	/* namespace Xmldom */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_XMLDOM)
using namespace Xml::Xmldom;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_XmldomHPP
