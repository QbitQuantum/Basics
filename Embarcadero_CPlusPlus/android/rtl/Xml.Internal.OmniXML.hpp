// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.Internal.OmniXML.pas' rev: 34.00 (Android)

#ifndef Xml_Internal_OmnixmlHPP
#define Xml_Internal_OmnixmlHPP

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
#include <Xml.Internal.OTextReadWrite.hpp>
#include <Xml.Internal.XmlRulesUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Internal
{
namespace Omnixml
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EXMLException;
__interface DELPHIINTERFACE IUnicodeStream;
typedef System::DelphiInterface<IUnicodeStream> _di_IUnicodeStream;
class DELPHICLASS OmniTXMLTextStream;
class DELPHICLASS OmniTXMLTextStreamExt;
__interface DELPHIINTERFACE OmniIXMLParseError;
typedef System::DelphiInterface<OmniIXMLParseError> _di_OmniIXMLParseError;
__interface DELPHIINTERFACE OmniIXMLNode;
typedef System::DelphiInterface<OmniIXMLNode> _di_OmniIXMLNode;
__interface DELPHIINTERFACE OmniIXMLCustomList;
typedef System::DelphiInterface<OmniIXMLCustomList> _di_OmniIXMLCustomList;
__interface DELPHIINTERFACE OmniIXMLNodeList;
typedef System::DelphiInterface<OmniIXMLNodeList> _di_OmniIXMLNodeList;
__interface DELPHIINTERFACE OmniIXMLNamedNodeMap;
typedef System::DelphiInterface<OmniIXMLNamedNodeMap> _di_OmniIXMLNamedNodeMap;
__interface DELPHIINTERFACE OmniIXMLDocumentFragment;
typedef System::DelphiInterface<OmniIXMLDocumentFragment> _di_OmniIXMLDocumentFragment;
__interface DELPHIINTERFACE OmniIXMLCharacterData;
typedef System::DelphiInterface<OmniIXMLCharacterData> _di_OmniIXMLCharacterData;
__interface DELPHIINTERFACE OmniIXMLText;
typedef System::DelphiInterface<OmniIXMLText> _di_OmniIXMLText;
__interface DELPHIINTERFACE OmniIXMLComment;
typedef System::DelphiInterface<OmniIXMLComment> _di_OmniIXMLComment;
__interface DELPHIINTERFACE OmniIXMLCDATASection;
typedef System::DelphiInterface<OmniIXMLCDATASection> _di_OmniIXMLCDATASection;
__interface DELPHIINTERFACE OmniIXMLDocumentType;
typedef System::DelphiInterface<OmniIXMLDocumentType> _di_OmniIXMLDocumentType;
__interface DELPHIINTERFACE OmniIXMLProcessingInstruction;
typedef System::DelphiInterface<OmniIXMLProcessingInstruction> _di_OmniIXMLProcessingInstruction;
__interface DELPHIINTERFACE OmniIXMLAttr;
typedef System::DelphiInterface<OmniIXMLAttr> _di_OmniIXMLAttr;
__interface DELPHIINTERFACE OmniIXMLEntityReference;
typedef System::DelphiInterface<OmniIXMLEntityReference> _di_OmniIXMLEntityReference;
__interface DELPHIINTERFACE OmniIXMLDocument;
typedef System::DelphiInterface<OmniIXMLDocument> _di_OmniIXMLDocument;
__interface DELPHIINTERFACE OmniIXMLElement;
typedef System::DelphiInterface<OmniIXMLElement> _di_OmniIXMLElement;
class DELPHICLASS OmniTXMLParseError;
class DELPHICLASS OmniTXMLNode;
class DELPHICLASS OmniTXMLEntityReference;
class DELPHICLASS OmniTXMLDocumentFragment;
class DELPHICLASS OmniTXMLCustomList;
class DELPHICLASS OmniTXMLNodeList;
class DELPHICLASS OmniTXMLNamedNodeMap;
class DELPHICLASS OmniTXMLElement;
class DELPHICLASS OmniTXMLProcessingInstruction;
class DELPHICLASS OmniTXMLAttr;
class DELPHICLASS OmniTXMLCharacterData;
class DELPHICLASS OmniTXMLText;
class DELPHICLASS OmniTXMLComment;
class DELPHICLASS OmniTXMLCDATASection;
class DELPHICLASS OmniTXMLDocumentType;
class DELPHICLASS OmniTXMLDocument;
class DELPHICLASS TTexListDic;
//-- type declarations -------------------------------------------------------
_DECLARE_ARITH_TYPE_ALIAS(System::Int8, TNodeType);

#ifndef __aarch64__
typedef unsigned TDicId;
#else /* __aarch64__ */
typedef unsigned long TDicId;
#endif /* __aarch64__ */

#ifndef __aarch64__
typedef System::Generics::Collections::TDictionary__2<System::UnicodeString,unsigned>* TTexPosDic;
#else /* __aarch64__ */
typedef System::Generics::Collections::TDictionary__2<System::UnicodeString,unsigned long>* TTexPosDic;
#endif /* __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EXMLException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
private:
	int FDOMCode;
	int FXMLCode;
	
public:
	__property int DOMCode = {read=FDOMCode, nodefault};
	__property int XMLCode = {read=FXMLCode, nodefault};
	__fastcall EXMLException(const int DOMCode, const int XMLCode, const System::TVarRec *Args, const int Args_High);
public:
	/* Exception.Create */ inline __fastcall EXMLException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EXMLException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EXMLException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EXMLException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EXMLException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EXMLException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EXMLException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EXMLException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXMLException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXMLException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXMLException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXMLException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EXMLException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TOutputFormat : unsigned char { ofNone, ofFlat, ofIndent };

__interface  INTERFACE_UUID("{F3ECA11F-EA18-491C-B59A-4203D5DC8CCA}") IUnicodeStream  : public System::IInterface 
{
	virtual System::Sysutils::TEncoding* __fastcall GetEncoding() = 0 ;
	virtual void __fastcall SetEncoding(System::Sysutils::TEncoding* const AEncoding) = 0 ;
	virtual bool __fastcall GetBOMFound() = 0 ;
	virtual TOutputFormat __fastcall GetOutputFormat() = 0 ;
	virtual void __fastcall SetOutputFormat(const TOutputFormat Value) = 0 ;
	virtual System::UnicodeString __fastcall GetPreviousOutputBuffer() = 0 ;
	virtual void __fastcall IncreaseIndent() = 0 ;
	virtual void __fastcall DecreaseIndent() = 0 ;
	virtual void __fastcall WriteIndent(const bool ForceNextLine = false) = 0 ;
	__property TOutputFormat OutputFormat = {read=GetOutputFormat, write=SetOutputFormat};
	__property System::Sysutils::TEncoding* Encoding = {read=GetEncoding, write=SetEncoding};
	__property bool BOMFound = {read=GetBOMFound};
	virtual void __fastcall UndoRead() = 0 ;
	virtual bool __fastcall ProcessChar(System::WideChar &Char) = 0 ;
	virtual bool __fastcall GetNextString(System::UnicodeString &ReadString, const int Len) = 0 ;
	virtual void __fastcall WriteOutputChar(const System::WideChar OutChar) = 0 ;
	virtual System::UnicodeString __fastcall GetOutputBuffer() = 0 ;
	virtual int __fastcall OutputBufferLen() = 0 ;
	virtual void __fastcall ClearOutputBuffer() = 0 ;
	virtual void __fastcall WriteString(const System::UnicodeString Value) = 0 ;
};

enum DECLSPEC_DENUM TStreamMode : unsigned char { smRead, smWrite };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLTextStream : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	TStreamMode FStreamMode;
	Xml::Internal::Otextreadwrite::TOTextReader* FReader;
	Xml::Internal::Otextreadwrite::TOTextWriter* FWriter;
	System::UnicodeString FPreviousOutBuffer;
	System::WideChar *FOutBuffer;
	int FOutBufferPos;
	int FOutBufferSize;
	int FIndent;
	TOutputFormat FOutputFormat;
	bool fBOMFound;
	System::Sysutils::TEncoding* __fastcall GetEncoding();
	void __fastcall SetEncoding(System::Sysutils::TEncoding* const AEncoding);
	bool __fastcall GetBOMFound();
	TOutputFormat __fastcall GetOutputFormat();
	void __fastcall SetOutputFormat(const TOutputFormat Value);
	
protected:
	System::Classes::TStream* FStream;
	bool FEOF;
	virtual bool __fastcall ReadChar(System::WideChar &ReadChar);
	virtual bool __fastcall ProcessChar(System::WideChar &ch);
	void __fastcall IncreaseIndent();
	void __fastcall DecreaseIndent();
	void __fastcall WriteIndent(const bool ForceNextLine = false);
	System::UnicodeString __fastcall GetPreviousOutputBuffer();
	
public:
	__property TOutputFormat OutputFormat = {read=GetOutputFormat, write=SetOutputFormat, nodefault};
	__property System::Sysutils::TEncoding* Encoding = {read=GetEncoding, write=SetEncoding};
	__property bool BOMFound = {read=GetBOMFound, nodefault};
	__fastcall OmniTXMLTextStream(System::Classes::TStream* const Stream, const TStreamMode Mode, System::Sysutils::TEncoding* const Encoding, const bool WriteBOM);
	__fastcall virtual ~OmniTXMLTextStream();
	virtual void __fastcall UndoRead();
	bool __fastcall GetNextString(System::UnicodeString &ReadString, const int Len);
	void __fastcall WriteOutputChar(const System::WideChar OutChar);
	System::UnicodeString __fastcall GetOutputBuffer();
	int __fastcall OutputBufferLen();
	void __fastcall ClearOutputBuffer();
	void __fastcall WriteString(const System::UnicodeString Value);
private:
	void *__IUnicodeStream;	// IUnicodeStream 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F3ECA11F-EA18-491C-B59A-4203D5DC8CCA}
	operator _di_IUnicodeStream()
	{
		_di_IUnicodeStream intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IUnicodeStream*(void) { return (IUnicodeStream*)&__IUnicodeStream; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLTextStreamExt : public OmniTXMLTextStream
{
	typedef OmniTXMLTextStream inherited;
	
private:
	bool FIncludeXmlEnc;
	bool __fastcall GetIncludeXmlEnc();
	
public:
	__fastcall OmniTXMLTextStreamExt(System::Classes::TStream* const Stream, const TStreamMode Mode, System::Sysutils::TEncoding* const Encoding, const bool WriteBOM, const bool IncludeXmlEnc);
	__property bool IncludeXmlEnc = {read=GetIncludeXmlEnc, nodefault};
public:
	/* OmniTXMLTextStream.Destroy */ inline __fastcall virtual ~OmniTXMLTextStreamExt() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{546E9AE4-4E1E-4014-B0B8-4F024C797544}") OmniIXMLParseError  : public System::IInterface 
{
	virtual int __fastcall GetErrorCode() = 0 ;
	virtual int __fastcall GetFilePos() = 0 ;
	virtual int __fastcall GetLine() = 0 ;
	virtual int __fastcall GetLinePos() = 0 ;
	virtual int __fastcall GetSrcTextPos() = 0 ;
	virtual System::UnicodeString __fastcall GetReason() = 0 ;
	virtual System::UnicodeString __fastcall GetSrcText() = 0 ;
	virtual System::UnicodeString __fastcall GetURL() = 0 ;
	__property int ErrorCode = {read=GetErrorCode};
	__property int FilePos = {read=GetFilePos};
	__property int Line = {read=GetLine};
	__property int LinePos = {read=GetLinePos};
	__property System::UnicodeString Reason = {read=GetReason};
	__property System::UnicodeString SrcText = {read=GetSrcText};
	__property int SrcTextPos = {read=GetSrcTextPos};
	__property System::UnicodeString URL = {read=GetURL};
};

__interface  INTERFACE_UUID("{F4D7D3DE-C6EC-4191-8E35-F652C2705E81}") OmniIXMLNode  : public System::IInterface 
{
	virtual _di_OmniIXMLNamedNodeMap __fastcall GetAttributes() = 0 ;
	virtual _di_OmniIXMLNodeList __fastcall GetChildNodes() = 0 ;
	virtual _di_OmniIXMLNode __fastcall GetFirstChild() = 0 ;
	virtual _di_OmniIXMLNode __fastcall GetLastChild() = 0 ;
	virtual _di_OmniIXMLNode __fastcall GetNextSibling() = 0 ;
	virtual System::UnicodeString __fastcall GetNodeName() = 0 ;
	virtual TNodeType __fastcall GetNodeType() = 0 ;
	virtual System::UnicodeString __fastcall GetNodeValue() = 0 ;
	virtual System::UnicodeString __fastcall GetNSURI() = 0 ;
	virtual _di_OmniIXMLDocument __fastcall GetOwnerDocument() = 0 ;
	virtual _di_OmniIXMLNode __fastcall GetParentNode() = 0 ;
	virtual _di_OmniIXMLNode __fastcall GetPreviousSibling() = 0 ;
	virtual void __fastcall SetNodeValue(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetParentNode(const _di_OmniIXMLNode Parent) = 0 ;
	virtual System::UnicodeString __fastcall GetLocalName() = 0 ;
	virtual System::UnicodeString __fastcall GetPrefix() = 0 ;
	virtual _di_OmniIXMLNode __fastcall InsertBefore(const _di_OmniIXMLNode NewChild, const _di_OmniIXMLNode RefChild) = 0 ;
	virtual _di_OmniIXMLNode __fastcall ReplaceChild(const _di_OmniIXMLNode NewChild, const _di_OmniIXMLNode OldChild) = 0 ;
	virtual _di_OmniIXMLNode __fastcall RemoveChild(const _di_OmniIXMLNode OldChild) = 0 ;
	virtual _di_OmniIXMLNode __fastcall AppendChild(const _di_OmniIXMLNode NewChild) = 0 ;
	virtual bool __fastcall HasChildNodes() = 0 ;
	virtual _di_OmniIXMLNode __fastcall CloneNode(const bool Deep) = 0 ;
	__property System::UnicodeString NodeName = {read=GetNodeName};
	__property System::UnicodeString NodeValue = {read=GetNodeValue, write=SetNodeValue};
	__property System::UnicodeString NamespaceURI = {read=GetNSURI};
	__property TNodeType NodeType = {read=GetNodeType};
	__property _di_OmniIXMLNode ParentNode = {read=GetParentNode};
	__property _di_OmniIXMLNodeList ChildNodes = {read=GetChildNodes};
	__property _di_OmniIXMLNode FirstChild = {read=GetFirstChild};
	__property _di_OmniIXMLNode LastChild = {read=GetLastChild};
	__property _di_OmniIXMLNode PreviousSibling = {read=GetPreviousSibling};
	__property _di_OmniIXMLNode NextSibling = {read=GetNextSibling};
	__property _di_OmniIXMLNamedNodeMap Attributes = {read=GetAttributes};
	__property _di_OmniIXMLDocument OwnerDocument = {read=GetOwnerDocument};
	__property System::UnicodeString LocalName = {read=GetLocalName};
	__property System::UnicodeString Prefix = {read=GetPrefix};
	virtual System::UnicodeString __fastcall GetText() = 0 ;
	virtual void __fastcall SetText(const System::UnicodeString Value) = 0 ;
	__property System::UnicodeString Text = {read=GetText, write=SetText};
	virtual void __fastcall WriteToStream(const _di_IUnicodeStream OutputStream) = 0 ;
	virtual void __fastcall SelectSingleNode(System::UnicodeString Pattern, _di_OmniIXMLNode &Result) = 0 /* overload */;
	virtual _di_OmniIXMLNode __fastcall SelectSingleNode(System::UnicodeString Pattern) = 0 /* overload */;
	virtual void __fastcall SelectNodes(System::UnicodeString Pattern, _di_OmniIXMLNodeList &Result) = 0 /* overload */;
	virtual _di_OmniIXMLNodeList __fastcall SelectNodes(System::UnicodeString Pattern) = 0 /* overload */;
	virtual System::UnicodeString __fastcall GetXML() = 0 ;
	__property System::UnicodeString XML = {read=GetXML};
};

__interface  INTERFACE_UUID("{6520A0BC-8738-4E40-8CDB-33713DED32ED}") OmniIXMLCustomList  : public System::IInterface 
{
	virtual int __fastcall GetLength() = 0 ;
	virtual _di_OmniIXMLNode __fastcall GetItem(const int Index) = 0 ;
	__property _di_OmniIXMLNode Item[const int Index] = {read=GetItem};
	__property int Length = {read=GetLength};
	virtual int __fastcall Add(const _di_OmniIXMLNode XMLNode) = 0 ;
	virtual int __fastcall IndexOf(const _di_OmniIXMLNode XMLNode) = 0 ;
	virtual void __fastcall Insert(const int Index, const _di_OmniIXMLNode XMLNode) = 0 ;
	virtual int __fastcall Remove(const _di_OmniIXMLNode XMLNode) = 0 ;
	virtual void __fastcall Delete(const int Index) = 0 ;
	virtual void __fastcall Clear() = 0 ;
};

__interface  INTERFACE_UUID("{66AF674E-4697-4356-ACCC-4258DA138EA1}") OmniIXMLNodeList  : public OmniIXMLCustomList 
{
	virtual _di_OmniIXMLNode __fastcall AddNode(const _di_OmniIXMLNode Arg) = 0 ;
	virtual void __fastcall Reset() = 0 ;
	virtual _di_OmniIXMLNode __fastcall NextNode() = 0 ;
};

__interface  INTERFACE_UUID("{87964B1D-F6CC-46D2-A602-67E198C8BFF5}") OmniIXMLNamedNodeMap  : public OmniIXMLCustomList 
{
	virtual _di_OmniIXMLNode __fastcall GetNamedItem(const System::UnicodeString Name) = 0 ;
	virtual _di_OmniIXMLNode __fastcall SetNamedItem(const _di_OmniIXMLNode Arg) = 0 ;
	virtual _di_OmniIXMLNode __fastcall RemoveNamedItem(const System::UnicodeString Name) = 0 ;
	virtual _di_OmniIXMLNode __fastcall GetNamedItemNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName) = 0 ;
	virtual _di_OmniIXMLNode __fastcall SetNamedItemNS(const _di_OmniIXMLNode Arg) = 0 ;
	virtual _di_OmniIXMLNode __fastcall RemoveNamedItemNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName) = 0 ;
};

__interface  INTERFACE_UUID("{A21A11BF-E489-4416-9607-172EFA2CFE45}") OmniIXMLDocumentFragment  : public OmniIXMLNode 
{
	
};

__interface  INTERFACE_UUID("{613A6538-A0DC-49BC-AFA6-D8E611176B86}") OmniIXMLCharacterData  : public OmniIXMLNode 
{
	virtual System::UnicodeString __fastcall GetData() = 0 ;
	virtual int __fastcall GetLength() = 0 ;
	virtual void __fastcall SetData(const System::UnicodeString Value) = 0 ;
	__property System::UnicodeString Data = {read=GetData, write=SetData};
	__property int Length = {read=GetLength};
	virtual System::UnicodeString __fastcall SubstringData(const int Offset, const int Count) = 0 ;
	virtual void __fastcall AppendData(const System::UnicodeString Arg) = 0 ;
	virtual void __fastcall InsertData(const int Offset, const System::UnicodeString Arg) = 0 ;
	virtual void __fastcall DeleteData(const int Offset, const int Count) = 0 ;
	virtual void __fastcall ReplaceData(const int Offset, const int Count, const System::UnicodeString Arg) = 0 ;
};

__interface  INTERFACE_UUID("{0EC46ED2-AB58-4DC9-B964-965615248564}") OmniIXMLText  : public OmniIXMLCharacterData 
{
	virtual _di_OmniIXMLText __fastcall SplitText(const int Offset) = 0 ;
};

__interface  INTERFACE_UUID("{B094A54C-039F-4ED7-9331-F7CF5A711EDA}") OmniIXMLComment  : public OmniIXMLCharacterData 
{
	
};

__interface  INTERFACE_UUID("{CF58778D-775D-4299-884C-F1DC61925D54}") OmniIXMLCDATASection  : public OmniIXMLText 
{
	
};

__interface  INTERFACE_UUID("{E956F945-E8F6-4589-BF8D-D4DC23DE1089}") OmniIXMLDocumentType  : public OmniIXMLText 
{
	
};

__interface  INTERFACE_UUID("{AF449E32-2615-4EF7-82B6-B2E9DCCE9FC3}") OmniIXMLProcessingInstruction  : public OmniIXMLNode 
{
	virtual System::UnicodeString __fastcall GetData() = 0 ;
	virtual System::UnicodeString __fastcall GetTarget() = 0 ;
	__property System::UnicodeString Target = {read=GetTarget};
	__property System::UnicodeString Data = {read=GetData};
};

__interface  INTERFACE_UUID("{10796B8E-FBAC-4ADF-BDD8-E4BBC5A5196F}") OmniIXMLAttr  : public OmniIXMLNode 
{
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual bool __fastcall GetSpecified() = 0 ;
	virtual System::UnicodeString __fastcall GetValue() = 0 ;
	virtual void __fastcall SetValue(const System::UnicodeString Value) = 0 ;
	virtual _di_OmniIXMLElement __fastcall GetOwnerElement() = 0 ;
	__property System::UnicodeString Name = {read=GetName};
	__property bool Specified = {read=GetSpecified};
	__property System::UnicodeString Value = {read=GetValue, write=SetValue};
	__property _di_OmniIXMLElement OwnerElement = {read=GetOwnerElement};
};

__interface  INTERFACE_UUID("{4EC18B2B-BD52-464D-BAD1-1FBE2C445989}") OmniIXMLEntityReference  : public OmniIXMLNode 
{
	
};

__interface  INTERFACE_UUID("{59A76970-451C-4343-947C-242EFF17413C}") OmniIXMLDocument  : public OmniIXMLNode 
{
	virtual _di_OmniIXMLDocumentType __fastcall GetDocType() = 0 ;
	virtual _di_OmniIXMLElement __fastcall GetDocumentElement() = 0 ;
	virtual void __fastcall SetDocumentElement(const _di_OmniIXMLElement Value) = 0 ;
	virtual bool __fastcall GetPreserveWhiteSpace() = 0 ;
	virtual void __fastcall SetPreserveWhiteSpace(const bool Value) = 0 ;
	__property _di_OmniIXMLDocumentType DocType = {read=GetDocType};
	__property _di_OmniIXMLElement DocumentElement = {read=GetDocumentElement, write=SetDocumentElement};
	__property bool PreserveWhiteSpace = {read=GetPreserveWhiteSpace, write=SetPreserveWhiteSpace};
	virtual _di_OmniIXMLAttr __fastcall CreateAttribute(const System::UnicodeString Name) = 0 ;
	virtual _di_OmniIXMLCDATASection __fastcall CreateCDATASection(const System::UnicodeString Data) = 0 ;
	virtual _di_OmniIXMLComment __fastcall CreateComment(const System::UnicodeString Data) = 0 ;
	virtual _di_OmniIXMLDocumentType __fastcall CreateDocType(const System::UnicodeString Data) = 0 ;
	virtual _di_OmniIXMLDocumentFragment __fastcall CreateDocumentFragment() = 0 ;
	virtual _di_OmniIXMLElement __fastcall CreateElement(const System::UnicodeString TagName) = 0 ;
	virtual _di_OmniIXMLEntityReference __fastcall CreateEntityReference(const System::UnicodeString Name) = 0 ;
	virtual _di_OmniIXMLProcessingInstruction __fastcall CreateProcessingInstruction(const System::UnicodeString Target, const System::UnicodeString Data) = 0 ;
	virtual _di_OmniIXMLText __fastcall CreateTextNode(const System::UnicodeString Data) = 0 ;
	virtual _di_OmniIXMLNodeList __fastcall GetElementsByTagName(const System::UnicodeString TagName) = 0 ;
	virtual _di_OmniIXMLAttr __fastcall CreateAttributeNS(const System::UnicodeString namespaceURI, const System::UnicodeString qualifiedName) = 0 ;
	virtual _di_OmniIXMLElement __fastcall CreateElementNS(const System::UnicodeString namespaceURI, const System::UnicodeString qualifiedName) = 0 ;
	virtual _di_OmniIXMLNodeList __fastcall GetElementsByTagNameNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName) = 0 ;
	virtual bool __fastcall Load(const System::UnicodeString FileName) = 0 ;
	virtual bool __fastcall LoadFromStream(System::Classes::TStream* const Stream) = 0 ;
	virtual void __fastcall Save(const System::UnicodeString FileName, const TOutputFormat OutputFormat = (TOutputFormat)(0x0)) = 0 ;
	virtual void __fastcall SaveToStream(System::Classes::TStream* const OutputStream, const TOutputFormat OutputFormat = (TOutputFormat)(0x0)) = 0 ;
	virtual bool __fastcall LoadXML(const System::UnicodeString XML) = 0 ;
	virtual _di_OmniIXMLParseError __fastcall GetParseError() = 0 ;
	__property _di_OmniIXMLParseError ParseError = {read=GetParseError};
};

__interface  INTERFACE_UUID("{C858C4E1-FB3F-4C98-8BDE-671E060D17B9}") OmniIXMLElement  : public OmniIXMLNode 
{
	virtual System::UnicodeString __fastcall GetTagName() = 0 ;
	__property System::UnicodeString TagName = {read=GetTagName};
	virtual System::UnicodeString __fastcall GetAttribute(const System::UnicodeString Name) = 0 ;
	virtual void __fastcall SetAttribute(const System::UnicodeString Name, const System::UnicodeString Value) = 0 ;
	virtual void __fastcall RemoveAttribute(const System::UnicodeString Name) = 0 ;
	virtual _di_OmniIXMLAttr __fastcall GetAttributeNode(const System::UnicodeString Name) = 0 ;
	virtual _di_OmniIXMLAttr __fastcall SetAttributeNode(const _di_OmniIXMLAttr NewAttr) = 0 ;
	virtual _di_OmniIXMLAttr __fastcall RemoveAttributeNode(const _di_OmniIXMLAttr OldAttr) = 0 ;
	virtual _di_OmniIXMLNodeList __fastcall GetElementsByTagName(const System::UnicodeString Name) = 0 ;
	virtual void __fastcall Normalize() = 0 ;
	virtual void __fastcall SetAttributeNS(const System::UnicodeString qualifiedName, const System::UnicodeString Value) = 0 ;
	virtual _di_OmniIXMLNodeList __fastcall GetElementsByTagNameNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName) = 0 ;
	virtual System::UnicodeString __fastcall GetAttributeNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName) = 0 ;
	virtual _di_OmniIXMLAttr __fastcall GetAttributeNodeNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName) = 0 ;
	virtual _di_OmniIXMLAttr __fastcall SetAttributeNodeNS(const _di_OmniIXMLAttr NewAttr) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLParseError : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	int FErrorCode;
	int FFilePos;
	int FLine;
	int FLinePos;
	System::UnicodeString FReason;
	System::UnicodeString FSrcText;
	int FSrcTextPos;
	System::UnicodeString FURL;
	int __fastcall GetErrorCode();
	int __fastcall GetFilePos();
	int __fastcall GetLine();
	int __fastcall GetLinePos();
	int __fastcall GetSrcTextPos();
	System::UnicodeString __fastcall GetReason();
	System::UnicodeString __fastcall GetSrcText();
	System::UnicodeString __fastcall GetURL();
	
protected:
	void __fastcall SetErrorCode(const int ErrorCode);
	void __fastcall SetFilePos(const int FilePos);
	void __fastcall SetLine(const int Line);
	void __fastcall SetLinePos(const int LinePos);
	void __fastcall SetReason(const System::UnicodeString Reason);
	void __fastcall SetSrcText(const System::UnicodeString SrcTextBefore, const System::UnicodeString SrcTextAfter);
	void __fastcall SetURL(const System::UnicodeString URL);
	
public:
	__property int ErrorCode = {read=GetErrorCode, nodefault};
	__property int FilePos = {read=GetFilePos, nodefault};
	__property int Line = {read=GetLine, nodefault};
	__property int LinePos = {read=GetLinePos, nodefault};
	__property System::UnicodeString Reason = {read=GetReason};
	__property System::UnicodeString SrcText = {read=GetSrcText};
	__property int SrcTextPos = {read=GetSrcTextPos, nodefault};
	__property System::UnicodeString URL = {read=GetURL};
public:
	/* TObject.Create */ inline __fastcall OmniTXMLParseError() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~OmniTXMLParseError() { }
	
private:
	void *__OmniIXMLParseError;	// OmniIXMLParseError 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {546E9AE4-4E1E-4014-B0B8-4F024C797544}
	operator _di_OmniIXMLParseError()
	{
		_di_OmniIXMLParseError intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator OmniIXMLParseError*(void) { return (OmniIXMLParseError*)&__OmniIXMLParseError; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLNode : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
protected:
	OmniTXMLDocument* FOwnerDocument;
	TNodeType FNodeType;
	_di_OmniIXMLNamedNodeMap FAttributes;
	_di_OmniIXMLNodeList FChildNodes;
	_di_OmniIXMLNode FParentNode;
	_di_OmniIXMLNode FOwnerElement;
#ifndef __aarch64__
	unsigned FNodeValueId;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,unsigned>* FNSPrefixScopeDict;
#else /* __aarch64__ */
	unsigned long FNodeValueId;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,unsigned long>* FNSPrefixScopeDict;
#endif /* __aarch64__ */
	void __fastcall ClearChildNodes();
	bool __fastcall HasAttributes();
	_di_OmniIXMLNamedNodeMap __fastcall GetAttributes();
	_di_OmniIXMLNodeList __fastcall GetChildNodes();
	_di_OmniIXMLNode __fastcall GetFirstChild();
	_di_OmniIXMLNode __fastcall GetLastChild();
	_di_OmniIXMLNode __fastcall GetNextSibling();
	virtual System::UnicodeString __fastcall GetNodeName() = 0 ;
	TNodeType __fastcall GetNodeType();
	virtual System::UnicodeString __fastcall GetNodeValue();
	System::UnicodeString __fastcall GetNSURI();
	System::UnicodeString __fastcall GetPrefix();
	System::UnicodeString __fastcall GetLocalName();
	virtual _di_OmniIXMLDocument __fastcall GetOwnerDocument();
	_di_OmniIXMLNode __fastcall GetParentNode();
	_di_OmniIXMLNode __fastcall GetPreviousSibling();
	virtual void __fastcall SetNodeValue(const System::UnicodeString Value);
	virtual void __fastcall InternalWriteToStream(const _di_IUnicodeStream OutputStream);
	virtual void __fastcall ReadFromStream(OmniTXMLNode* const Parent, const _di_IUnicodeStream InputStream);
	void __fastcall SetParentNode(const _di_OmniIXMLNode Parent);
	virtual System::UnicodeString __fastcall GetText();
	virtual void __fastcall SetText(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetXML();
	virtual void __fastcall SelectNodes(System::UnicodeString Pattern, _di_OmniIXMLNodeList &Result)/* overload */;
	virtual void __fastcall SelectSingleNode(System::UnicodeString Pattern, _di_OmniIXMLNode &Result)/* overload */;
	
public:
	TTexListDic* TexListDic;
	__property System::UnicodeString NodeName = {read=GetNodeName};
	__property System::UnicodeString Prefix = {read=GetPrefix};
	__property System::UnicodeString LocalName = {read=GetLocalName};
	__property System::UnicodeString NamespaceURI = {read=GetNSURI};
	__property System::UnicodeString NodeValue = {read=GetNodeValue, write=SetNodeValue};
	__property TNodeType NodeType = {read=GetNodeType, nodefault};
	__property _di_OmniIXMLNode ParentNode = {read=GetParentNode};
	__property _di_OmniIXMLNodeList ChildNodes = {read=GetChildNodes};
	__property _di_OmniIXMLNode FirstChild = {read=GetFirstChild};
	__property _di_OmniIXMLNode LastChild = {read=GetLastChild};
	__property _di_OmniIXMLNode PreviousSibling = {read=GetPreviousSibling};
	__property _di_OmniIXMLNode NextSibling = {read=GetNextSibling};
	__property _di_OmniIXMLNamedNodeMap Attributes = {read=GetAttributes};
	__property _di_OmniIXMLDocument OwnerDocument = {read=GetOwnerDocument};
	__property System::UnicodeString Text = {read=GetText, write=SetText};
	__fastcall OmniTXMLNode(OmniTXMLDocument* const AOwnerDocument);
	__fastcall virtual ~OmniTXMLNode();
	_di_OmniIXMLNode __fastcall InsertBefore(const _di_OmniIXMLNode NewChild, const _di_OmniIXMLNode RefChild);
	_di_OmniIXMLNode __fastcall ReplaceChild(const _di_OmniIXMLNode NewChild, const _di_OmniIXMLNode OldChild);
	_di_OmniIXMLNode __fastcall RemoveChild(const _di_OmniIXMLNode OldChild);
	_di_OmniIXMLNode __fastcall AppendChild(const _di_OmniIXMLNode NewChild);
	bool __fastcall HasChildNodes();
	virtual _di_OmniIXMLNode __fastcall CloneNode(const bool Deep);
	void __fastcall WriteToStream(const _di_IUnicodeStream OutputStream);
	virtual _di_OmniIXMLNodeList __fastcall SelectNodes(System::UnicodeString Pattern)/* overload */;
	virtual _di_OmniIXMLNode __fastcall SelectSingleNode(System::UnicodeString Pattern)/* overload */;
	__property System::UnicodeString XML = {read=GetXML};
private:
	void *__OmniIXMLNode;	// OmniIXMLNode 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F4D7D3DE-C6EC-4191-8E35-F652C2705E81}
	operator _di_OmniIXMLNode()
	{
		_di_OmniIXMLNode intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator OmniIXMLNode*(void) { return (OmniIXMLNode*)&__OmniIXMLNode; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLEntityReference : public OmniTXMLNode
{
	typedef OmniTXMLNode inherited;
	
public:
	/* OmniTXMLNode.Create */ inline __fastcall OmniTXMLEntityReference(OmniTXMLDocument* const AOwnerDocument) : OmniTXMLNode(AOwnerDocument) { }
	/* OmniTXMLNode.Destroy */ inline __fastcall virtual ~OmniTXMLEntityReference() { }
	
private:
	void *__OmniIXMLEntityReference;	// OmniIXMLEntityReference 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {4EC18B2B-BD52-464D-BAD1-1FBE2C445989}
	operator _di_OmniIXMLEntityReference()
	{
		_di_OmniIXMLEntityReference intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator OmniIXMLEntityReference*(void) { return (OmniIXMLEntityReference*)&__OmniIXMLEntityReference; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLDocumentFragment : public OmniTXMLNode
{
	typedef OmniTXMLNode inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetNodeName();
	virtual void __fastcall ReadFromStream(OmniTXMLNode* const Parent, const _di_IUnicodeStream InputStream);
	
public:
	__fastcall OmniTXMLDocumentFragment(OmniTXMLDocument* const OwnerDocument);
public:
	/* OmniTXMLNode.Destroy */ inline __fastcall virtual ~OmniTXMLDocumentFragment() { }
	
private:
	void *__OmniIXMLDocumentFragment;	// OmniIXMLDocumentFragment 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A21A11BF-E489-4416-9607-172EFA2CFE45}
	operator _di_OmniIXMLDocumentFragment()
	{
		_di_OmniIXMLDocumentFragment intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator OmniIXMLDocumentFragment*(void) { return (OmniIXMLDocumentFragment*)&__OmniIXMLDocumentFragment; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLCustomList : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	_di_OmniIXMLNode operator[](const int Index) { return this->Item[Index]; }
	
private:
	System::Generics::Collections::TList__1<_di_OmniIXMLNode>* FList;
	
protected:
	int __fastcall GetLength();
	_di_OmniIXMLNode __fastcall GetItem(const int Index);
	void __fastcall Put(int Index, _di_OmniIXMLNode Item);
	
public:
	__fastcall OmniTXMLCustomList();
	__fastcall virtual ~OmniTXMLCustomList();
	__property _di_OmniIXMLNode Item[const int Index] = {read=GetItem/*, default*/};
	__property int Length = {read=GetLength, nodefault};
	int __fastcall Add(const _di_OmniIXMLNode XMLNode);
	int __fastcall IndexOf(const _di_OmniIXMLNode XMLNode);
	void __fastcall Insert(const int Index, const _di_OmniIXMLNode XMLNode);
	int __fastcall Remove(const _di_OmniIXMLNode XMLNode);
	void __fastcall Delete(const int Index);
	void __fastcall Clear();
private:
	void *__OmniIXMLCustomList;	// OmniIXMLCustomList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6520A0BC-8738-4E40-8CDB-33713DED32ED}
	operator _di_OmniIXMLCustomList()
	{
		_di_OmniIXMLCustomList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator OmniIXMLCustomList*(void) { return (OmniIXMLCustomList*)&__OmniIXMLCustomList; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLNodeList : public OmniTXMLCustomList
{
	typedef OmniTXMLCustomList inherited;
	
protected:
	int FItemNo;
	
public:
	void __fastcall Reset();
	_di_OmniIXMLNode __fastcall NextNode();
	_di_OmniIXMLNode __fastcall AddNode(const _di_OmniIXMLNode Arg);
public:
	/* OmniTXMLCustomList.Create */ inline __fastcall OmniTXMLNodeList() : OmniTXMLCustomList() { }
	/* OmniTXMLCustomList.Destroy */ inline __fastcall virtual ~OmniTXMLNodeList() { }
	
private:
	void *__OmniIXMLNodeList;	// OmniIXMLNodeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {66AF674E-4697-4356-ACCC-4258DA138EA1}
	operator _di_OmniIXMLNodeList()
	{
		_di_OmniIXMLNodeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator OmniIXMLNodeList*(void) { return (OmniIXMLNodeList*)&__OmniIXMLNodeList; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLNamedNodeMap : public OmniTXMLCustomList
{
	typedef OmniTXMLCustomList inherited;
	
public:
	_di_OmniIXMLNode __fastcall GetNamedItem(const System::UnicodeString Name);
	_di_OmniIXMLNode __fastcall SetNamedItem(const _di_OmniIXMLNode Arg);
	_di_OmniIXMLNode __fastcall RemoveNamedItem(const System::UnicodeString Name);
	_di_OmniIXMLNode __fastcall GetNamedItemNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName);
	_di_OmniIXMLNode __fastcall SetNamedItemNS(const _di_OmniIXMLNode Arg);
	_di_OmniIXMLNode __fastcall RemoveNamedItemNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName);
public:
	/* OmniTXMLCustomList.Create */ inline __fastcall OmniTXMLNamedNodeMap() : OmniTXMLCustomList() { }
	/* OmniTXMLCustomList.Destroy */ inline __fastcall virtual ~OmniTXMLNamedNodeMap() { }
	
private:
	void *__OmniIXMLNamedNodeMap;	// OmniIXMLNamedNodeMap 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {87964B1D-F6CC-46D2-A602-67E198C8BFF5}
	operator _di_OmniIXMLNamedNodeMap()
	{
		_di_OmniIXMLNamedNodeMap intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator OmniIXMLNamedNodeMap*(void) { return (OmniIXMLNamedNodeMap*)&__OmniIXMLNamedNodeMap; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLElement : public OmniTXMLNode
{
	typedef OmniTXMLNode inherited;
	
private:
#ifndef __aarch64__
	unsigned FTagNameId;
#else /* __aarch64__ */
	unsigned long FTagNameId;
#endif /* __aarch64__ */
	
protected:
	virtual System::UnicodeString __fastcall GetNodeName();
	System::UnicodeString __fastcall GetTagName();
	virtual void __fastcall InternalWriteToStream(const _di_IUnicodeStream OutputStream);
	virtual void __fastcall ReadFromStream(OmniTXMLNode* const Parent, const _di_IUnicodeStream InputStream);
	void __fastcall SetTagName(const System::UnicodeString TagName);
	
public:
	__property System::UnicodeString TagName = {read=GetTagName};
	__fastcall OmniTXMLElement(OmniTXMLDocument* const OwnerDocument, const System::UnicodeString TagName);
	System::UnicodeString __fastcall GetAttribute(const System::UnicodeString Name);
	void __fastcall SetAttribute(const System::UnicodeString Name, const System::UnicodeString Value);
	void __fastcall RemoveAttribute(const System::UnicodeString Name);
	_di_OmniIXMLAttr __fastcall GetAttributeNode(const System::UnicodeString Name);
	_di_OmniIXMLAttr __fastcall SetAttributeNode(const _di_OmniIXMLAttr NewAttr);
	_di_OmniIXMLAttr __fastcall RemoveAttributeNode(const _di_OmniIXMLAttr OldAttr);
	_di_OmniIXMLNodeList __fastcall GetElementsByTagName(const System::UnicodeString Name);
	void __fastcall Normalize();
	void __fastcall SetAttributeNS(const System::UnicodeString qualifiedName, const System::UnicodeString Value);
	_di_OmniIXMLAttr __fastcall SetAttributeNodeNS(const _di_OmniIXMLAttr NewAttr);
	_di_OmniIXMLNodeList __fastcall GetElementsByTagNameNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName);
	System::UnicodeString __fastcall GetAttributeNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName);
	_di_OmniIXMLAttr __fastcall GetAttributeNodeNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName);
public:
	/* OmniTXMLNode.Create */ inline __fastcall OmniTXMLElement(OmniTXMLDocument* const AOwnerDocument) : OmniTXMLNode(AOwnerDocument) { }
	/* OmniTXMLNode.Destroy */ inline __fastcall virtual ~OmniTXMLElement() { }
	
private:
	void *__OmniIXMLElement;	// OmniIXMLElement 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C858C4E1-FB3F-4C98-8BDE-671E060D17B9}
	operator _di_OmniIXMLElement()
	{
		_di_OmniIXMLElement intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator OmniIXMLElement*(void) { return (OmniIXMLElement*)&__OmniIXMLElement; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLProcessingInstruction : public OmniTXMLNode
{
	typedef OmniTXMLNode inherited;
	
private:
	System::UnicodeString FTarget;
	System::UnicodeString FData;
	System::UnicodeString __fastcall GetData();
	System::UnicodeString __fastcall GetTarget();
	
protected:
	virtual System::UnicodeString __fastcall GetNodeName();
	virtual void __fastcall SetData(System::UnicodeString Data);
	virtual void __fastcall InternalWriteToStream(const _di_IUnicodeStream OutputStream);
	virtual void __fastcall ReadFromStream(OmniTXMLNode* const Parent, const _di_IUnicodeStream InputStream);
	
public:
	__property System::UnicodeString Target = {read=GetTarget};
	__property System::UnicodeString Data = {read=GetData};
	__fastcall OmniTXMLProcessingInstruction(OmniTXMLDocument* const OwnerDocument, const System::UnicodeString Target, const System::UnicodeString Data);
public:
	/* OmniTXMLNode.Create */ inline __fastcall OmniTXMLProcessingInstruction(OmniTXMLDocument* const AOwnerDocument) : OmniTXMLNode(AOwnerDocument) { }
	/* OmniTXMLNode.Destroy */ inline __fastcall virtual ~OmniTXMLProcessingInstruction() { }
	
private:
	void *__OmniIXMLProcessingInstruction;	// OmniIXMLProcessingInstruction 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {AF449E32-2615-4EF7-82B6-B2E9DCCE9FC3}
	operator _di_OmniIXMLProcessingInstruction()
	{
		_di_OmniIXMLProcessingInstruction intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator OmniIXMLProcessingInstruction*(void) { return (OmniIXMLProcessingInstruction*)&__OmniIXMLProcessingInstruction; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLAttr : public OmniTXMLNode
{
	typedef OmniTXMLNode inherited;
	
private:
#ifndef __aarch64__
	unsigned FNameId;
#else /* __aarch64__ */
	unsigned long FNameId;
#endif /* __aarch64__ */
	bool FSpecified;
	System::UnicodeString __fastcall GetName();
	bool __fastcall GetSpecified();
	System::UnicodeString __fastcall GetValue();
	void __fastcall SetValue(const System::UnicodeString Value);
	void __fastcall SetName(const System::UnicodeString Value);
	
protected:
	virtual System::UnicodeString __fastcall GetNodeName();
	virtual void __fastcall SetNodeValue(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetText();
	virtual void __fastcall ReadFromStream(OmniTXMLNode* const Parent, const _di_IUnicodeStream InputStream);
	virtual void __fastcall InternalWriteToStream(const _di_IUnicodeStream OutputStream);
	_di_OmniIXMLElement __fastcall GetOwnerElement();
	
public:
	__property System::UnicodeString Name = {read=GetName};
	__property bool Specified = {read=GetSpecified, nodefault};
	__property System::UnicodeString Value = {read=GetValue, write=SetValue};
	__property _di_OmniIXMLElement OwnerElement = {read=GetOwnerElement};
	__fastcall OmniTXMLAttr(OmniTXMLDocument* const OwnerDocument, const System::UnicodeString Name);
public:
	/* OmniTXMLNode.Create */ inline __fastcall OmniTXMLAttr(OmniTXMLDocument* const AOwnerDocument) : OmniTXMLNode(AOwnerDocument) { }
	/* OmniTXMLNode.Destroy */ inline __fastcall virtual ~OmniTXMLAttr() { }
	
private:
	void *__OmniIXMLAttr;	// OmniIXMLAttr 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {10796B8E-FBAC-4ADF-BDD8-E4BBC5A5196F}
	operator _di_OmniIXMLAttr()
	{
		_di_OmniIXMLAttr intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator OmniIXMLAttr*(void) { return (OmniIXMLAttr*)&__OmniIXMLAttr; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLCharacterData : public OmniTXMLNode
{
	typedef OmniTXMLNode inherited;
	
private:
	System::UnicodeString __fastcall GetData();
	int __fastcall GetLength();
	
protected:
	System::UnicodeString FNodeValue;
	virtual void __fastcall SetData(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetNodeValue();
	virtual void __fastcall SetNodeValue(const System::UnicodeString Value);
	virtual void __fastcall InternalWriteToStream(const _di_IUnicodeStream OutputStream);
	virtual void __fastcall ReadFromStream(OmniTXMLNode* const Parent, const _di_IUnicodeStream InputStream);
	
public:
	__property System::UnicodeString Data = {read=GetData, write=SetData};
	__property int Length = {read=GetLength, nodefault};
	__fastcall OmniTXMLCharacterData(OmniTXMLDocument* const OwnerDocument, const System::UnicodeString Data);
	System::UnicodeString __fastcall SubstringData(const int Offset, const int Count);
	void __fastcall AppendData(const System::UnicodeString Arg);
	void __fastcall InsertData(const int Offset, const System::UnicodeString Arg);
	void __fastcall DeleteData(const int Offset, const int Count);
	void __fastcall ReplaceData(const int Offset, const int Count, const System::UnicodeString Arg);
public:
	/* OmniTXMLNode.Destroy */ inline __fastcall virtual ~OmniTXMLCharacterData() { }
	
private:
	void *__OmniIXMLCharacterData;	// OmniIXMLCharacterData 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {613A6538-A0DC-49BC-AFA6-D8E611176B86}
	operator _di_OmniIXMLCharacterData()
	{
		_di_OmniIXMLCharacterData intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator OmniIXMLCharacterData*(void) { return (OmniIXMLCharacterData*)&__OmniIXMLCharacterData; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLText : public OmniTXMLCharacterData
{
	typedef OmniTXMLCharacterData inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetNodeName();
	virtual void __fastcall ReadFromStream(OmniTXMLNode* const Parent, const _di_IUnicodeStream InputStream);
	
public:
	__fastcall OmniTXMLText(OmniTXMLDocument* const OwnerDocument, const System::UnicodeString Data);
	_di_OmniIXMLText __fastcall SplitText(const int Offset);
public:
	/* OmniTXMLNode.Destroy */ inline __fastcall virtual ~OmniTXMLText() { }
	
private:
	void *__OmniIXMLText;	// OmniIXMLText 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0EC46ED2-AB58-4DC9-B964-965615248564}
	operator _di_OmniIXMLText()
	{
		_di_OmniIXMLText intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator OmniIXMLText*(void) { return (OmniIXMLText*)&__OmniIXMLText; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLComment : public OmniTXMLCharacterData
{
	typedef OmniTXMLCharacterData inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetNodeName();
	virtual void __fastcall InternalWriteToStream(const _di_IUnicodeStream OutputStream);
	virtual void __fastcall ReadFromStream(OmniTXMLNode* const Parent, const _di_IUnicodeStream InputStream);
	
public:
	__fastcall OmniTXMLComment(OmniTXMLDocument* const OwnerDocument, const System::UnicodeString Data);
public:
	/* OmniTXMLNode.Destroy */ inline __fastcall virtual ~OmniTXMLComment() { }
	
private:
	void *__OmniIXMLComment;	// OmniIXMLComment 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B094A54C-039F-4ED7-9331-F7CF5A711EDA}
	operator _di_OmniIXMLComment()
	{
		_di_OmniIXMLComment intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator OmniIXMLComment*(void) { return (OmniIXMLComment*)&__OmniIXMLComment; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLCDATASection : public OmniTXMLText
{
	typedef OmniTXMLText inherited;
	
private:
	void __fastcall CheckValue(const System::UnicodeString Value);
	
protected:
	virtual System::UnicodeString __fastcall GetNodeName();
	virtual void __fastcall SetData(const System::UnicodeString Value);
	virtual void __fastcall SetNodeValue(const System::UnicodeString Value);
	virtual void __fastcall InternalWriteToStream(const _di_IUnicodeStream OutputStream);
	virtual void __fastcall ReadFromStream(OmniTXMLNode* const Parent, const _di_IUnicodeStream InputStream);
	
public:
	__fastcall OmniTXMLCDATASection(OmniTXMLDocument* const OwnerDocument, const System::UnicodeString Data);
public:
	/* OmniTXMLNode.Destroy */ inline __fastcall virtual ~OmniTXMLCDATASection() { }
	
private:
	void *__OmniIXMLCDATASection;	// OmniIXMLCDATASection 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CF58778D-775D-4299-884C-F1DC61925D54}
	operator _di_OmniIXMLCDATASection()
	{
		_di_OmniIXMLCDATASection intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator OmniIXMLCDATASection*(void) { return (OmniIXMLCDATASection*)&__OmniIXMLCDATASection; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLDocumentType : public OmniTXMLText
{
	typedef OmniTXMLText inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetNodeName();
	virtual void __fastcall InternalWriteToStream(const _di_IUnicodeStream OutputStream);
	virtual void __fastcall ReadFromStream(OmniTXMLNode* const Parent, const _di_IUnicodeStream InputStream);
	
public:
	__fastcall OmniTXMLDocumentType(OmniTXMLDocument* const OwnerDocument, const System::UnicodeString Data);
public:
	/* OmniTXMLNode.Destroy */ inline __fastcall virtual ~OmniTXMLDocumentType() { }
	
private:
	void *__OmniIXMLDocumentType;	// OmniIXMLDocumentType 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E956F945-E8F6-4589-BF8D-D4DC23DE1089}
	operator _di_OmniIXMLDocumentType()
	{
		_di_OmniIXMLDocumentType intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator OmniIXMLDocumentType*(void) { return (OmniIXMLDocumentType*)&__OmniIXMLDocumentType; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

_DECLARE_METACLASS(System::TMetaClass, OmniTXMLAttrClass);

_DECLARE_METACLASS(System::TMetaClass, OmniTXMLCDATASectionClass);

_DECLARE_METACLASS(System::TMetaClass, OmniTXMLCommentClass);

_DECLARE_METACLASS(System::TMetaClass, OmniTXMLDocumentTypeClass);

_DECLARE_METACLASS(System::TMetaClass, OmniTXMLElementClass);

_DECLARE_METACLASS(System::TMetaClass, OmniTXMLProcessingInstructionClass);

_DECLARE_METACLASS(System::TMetaClass, OmniTXMLTextClass);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OmniTXMLDocument : public OmniTXMLNode
{
	typedef OmniTXMLNode inherited;
	
private:
	_di_OmniIXMLDocumentType FDocType;
	_di_OmniIXMLParseError FIParseError;
	OmniTXMLParseError* FParseError;
	bool FPreserveWhiteSpace;
	System::UnicodeString FURL;
	bool FNSpace;
	bool StartTag;
	
protected:
	virtual System::UnicodeString __fastcall GetNodeName();
	_di_OmniIXMLParseError __fastcall GetParseError();
	_di_OmniIXMLDocumentType __fastcall GetDocType();
	_di_OmniIXMLElement __fastcall GetDocumentElement();
	void __fastcall SetDocumentElement(const _di_OmniIXMLElement Value);
	bool __fastcall GetPreserveWhiteSpace();
	void __fastcall SetPreserveWhiteSpace(const bool Value);
	virtual System::UnicodeString __fastcall GetText();
	virtual _di_OmniIXMLDocument __fastcall GetOwnerDocument();
	OmniTXMLAttrClass FXMLAttrClass;
	OmniTXMLCDATASectionClass FXMLCDATASectionClass;
	OmniTXMLCommentClass FXMLCommentClass;
	OmniTXMLDocumentTypeClass FXMLDocTypeClass;
	OmniTXMLElementClass FXMLElementClass;
	OmniTXMLProcessingInstructionClass FXMLProcessingInstructionClass;
	OmniTXMLTextClass FXMLTextClass;
	OmniTXMLAttr* __fastcall InternalCreateAttribute(const System::UnicodeString Name);
	OmniTXMLCDATASection* __fastcall InternalCreateCDATASection(const System::UnicodeString Data);
	OmniTXMLComment* __fastcall InternalCreateComment(const System::UnicodeString Data);
	OmniTXMLDocumentType* __fastcall InternalCreateDocType(const System::UnicodeString Data);
	OmniTXMLDocumentFragment* __fastcall InternalCreateDocumentFragment();
	OmniTXMLElement* __fastcall InternalCreateElement(const System::UnicodeString TagName);
	OmniTXMLEntityReference* __fastcall InternalCreateEntityReference(const System::UnicodeString Name);
	OmniTXMLProcessingInstruction* __fastcall InternalCreateProcessingInstruction(const System::UnicodeString Target, const System::UnicodeString Data);
	OmniTXMLText* __fastcall InternalCreateTextNode(const System::UnicodeString Data);
	virtual void __fastcall ReadFromStream(OmniTXMLNode* const Parent, const _di_IUnicodeStream InputStream);
	virtual void __fastcall InternalWriteToStream(const _di_IUnicodeStream OutputStream);
	
public:
	System::Classes::TInterfaceList* UnclosedElementList;
	__property _di_OmniIXMLDocumentType DocType = {read=GetDocType};
	__property _di_OmniIXMLElement DocumentElement = {read=GetDocumentElement, write=SetDocumentElement};
	__property bool PreserveWhiteSpace = {read=GetPreserveWhiteSpace, write=SetPreserveWhiteSpace, nodefault};
	__fastcall virtual OmniTXMLDocument();
	__fastcall virtual ~OmniTXMLDocument();
	_di_OmniIXMLAttr __fastcall CreateAttribute(const System::UnicodeString Name);
	_di_OmniIXMLCDATASection __fastcall CreateCDATASection(const System::UnicodeString Data);
	_di_OmniIXMLComment __fastcall CreateComment(const System::UnicodeString Data);
	_di_OmniIXMLDocumentType __fastcall CreateDocType(const System::UnicodeString Data);
	_di_OmniIXMLDocumentFragment __fastcall CreateDocumentFragment();
	_di_OmniIXMLElement __fastcall CreateElement(const System::UnicodeString TagName);
	_di_OmniIXMLEntityReference __fastcall CreateEntityReference(const System::UnicodeString Name);
	_di_OmniIXMLProcessingInstruction __fastcall CreateProcessingInstruction(const System::UnicodeString Target, const System::UnicodeString Data);
	_di_OmniIXMLText __fastcall CreateTextNode(const System::UnicodeString Data);
	_di_OmniIXMLNodeList __fastcall GetElementsByTagName(const System::UnicodeString TagName);
	_di_OmniIXMLAttr __fastcall CreateAttributeNS(const System::UnicodeString namespaceURI, const System::UnicodeString qualifiedName);
	_di_OmniIXMLElement __fastcall CreateElementNS(const System::UnicodeString namespaceURI, const System::UnicodeString qualifiedName);
	_di_OmniIXMLNodeList __fastcall GetElementsByTagNameNS(const System::UnicodeString namespaceURI, const System::UnicodeString localName);
	virtual bool __fastcall Load(const System::UnicodeString FileName);
	bool __fastcall LoadFromStream(System::Classes::TStream* const Stream);
	virtual void __fastcall Save(const System::UnicodeString FileName, const TOutputFormat OutputFormat = (TOutputFormat)(0x0));
	void __fastcall SaveToStream(System::Classes::TStream* const OutputStream, const TOutputFormat OutputFormat = (TOutputFormat)(0x0));
	virtual bool __fastcall LoadXML(const System::UnicodeString XML);
	__property _di_OmniIXMLParseError ParseError = {read=GetParseError};
private:
	void *__OmniIXMLDocument;	// OmniIXMLDocument 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {59A76970-451C-4343-947C-242EFF17413C}
	operator _di_OmniIXMLDocument()
	{
		_di_OmniIXMLDocument intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator OmniIXMLDocument*(void) { return (OmniIXMLDocument*)&__OmniIXMLDocument; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TTexListDic : public System::TObject
{
	typedef System::TObject inherited;
	
private:
#ifndef __aarch64__
	System::Generics::Collections::TDictionary__2<System::UnicodeString,unsigned>* FTexPosDic;
#else /* __aarch64__ */
	System::Generics::Collections::TDictionary__2<System::UnicodeString,unsigned long>* FTexPosDic;
#endif /* __aarch64__ */
	System::Classes::TStringList* FTextList;
	
public:
	__fastcall TTexListDic();
	__fastcall virtual ~TTexListDic();
	int __fastcall PositionOf(const System::UnicodeString Text);
#ifndef __aarch64__
	unsigned __fastcall Add(const System::UnicodeString Text);
	System::UnicodeString __fastcall Get(const unsigned Id);
#else /* __aarch64__ */
	unsigned long __fastcall Add(const System::UnicodeString Text);
	System::UnicodeString __fastcall Get(const unsigned long Id);
#endif /* __aarch64__ */
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::WideChar DEFAULT_DECIMALSEPARATOR = (System::WideChar)(0x2e);
static constexpr System::WideChar DEFAULT_TRUE = (System::WideChar)(0x31);
static constexpr System::WideChar DEFAULT_FALSE = (System::WideChar)(0x30);
static constexpr System::WideChar DEFAULT_DATETIMESEPARATOR = (System::WideChar)(0x54);
static constexpr System::WideChar DEFAULT_DATESEPARATOR = (System::WideChar)(0x2d);
static constexpr System::WideChar DEFAULT_TIMESEPARATOR = (System::WideChar)(0x3a);
static constexpr System::WideChar DEFAULT_MSSEPARATOR = (System::WideChar)(0x2e);
static constexpr System::WideChar NSDelim = (System::WideChar)(0x3a);
#define SXML u"xml"
#define SVersion u"version"
#define SEncoding u"encoding"
#define SStandalone u"standalone"
#define SXMLNS u"xmlns"
#define SHttp u"http:/"
#define SXMLNamespaceURI u"http://www.w3.org/2000/xmlns/"
#define SXMLPrefixNamespaceURI u"http://www.w3.org/XML/1998/namespace"
#ifndef __aarch64__
static constexpr unsigned CInvalidDicId = unsigned(0xffffffff);
#else /* __aarch64__ */
static constexpr unsigned __int64 CInvalidDicId = 0xffffffffffffffffULL;
#endif /* __aarch64__ */
static constexpr System::Int8 ELEMENT_NODE = System::Int8(0x1);
static constexpr System::Int8 ATTRIBUTE_NODE = System::Int8(0x2);
static constexpr System::Int8 TEXT_NODE = System::Int8(0x3);
static constexpr System::Int8 CDATA_SECTION_NODE = System::Int8(0x4);
static constexpr System::Int8 ENTITY_REFERENCE_NODE = System::Int8(0x5);
static constexpr System::Int8 ENTITY_NODE = System::Int8(0x6);
static constexpr System::Int8 PROCESSING_INSTRUCTION_NODE = System::Int8(0x7);
static constexpr System::Int8 COMMENT_NODE = System::Int8(0x8);
static constexpr System::Int8 DOCUMENT_NODE = System::Int8(0x9);
static constexpr System::Int8 DOCUMENT_TYPE_NODE = System::Int8(0xa);
static constexpr System::Int8 DOCUMENT_FRAGMENT_NODE = System::Int8(0xb);
static constexpr System::Int8 NOTATION_NODE = System::Int8(0xc);
static constexpr System::Int8 INDEX_SIZE_ERR = System::Int8(0x1);
static constexpr System::Int8 DOMSTRING_SIZE_ERR = System::Int8(0x2);
static constexpr System::Int8 HIERARCHY_REQUEST_ERR = System::Int8(0x3);
static constexpr System::Int8 WRONG_DOCUMENT_ERR = System::Int8(0x4);
static constexpr System::Int8 INVALID_CHARACTER_ERR = System::Int8(0x5);
static constexpr System::Int8 NO_DATA_ALLOWED_ERR = System::Int8(0x6);
static constexpr System::Int8 NO_MODIFICATION_ALLOWED_ERR = System::Int8(0x7);
static constexpr System::Int8 NOT_FOUND_ERR = System::Int8(0x8);
static constexpr System::Int8 NOT_SUPPORTED_ERR = System::Int8(0x9);
static constexpr System::Int8 INUSE_ATTRIBUTE_ERR = System::Int8(0xa);
static constexpr System::Int8 INVALID_STATE_ERR = System::Int8(0xb);
static constexpr System::Int8 SYNTAX_ERR = System::Int8(0xc);
static constexpr System::Int8 INVALID_MODIFICATION_ERR = System::Int8(0xd);
static constexpr System::Int8 NAMESPACE_ERR = System::Int8(0xe);
static constexpr System::Int8 INVALID_ACCESS_ERR = System::Int8(0xf);
static constexpr System::Int8 MSG_E_NOTEXT = System::Int8(0x0);
static constexpr System::Int8 MSG_E_BASE = System::Int8(0x1);
static constexpr System::Int8 MSG_E_FORMATINDEX_BADINDEX = System::Int8(0x1);
static constexpr System::Int8 MSG_E_FORMATINDEX_BADFORMAT = System::Int8(0x2);
static constexpr System::Int8 MSG_E_SYSTEM_ERROR = System::Int8(0x3);
static constexpr System::Int8 MSG_E_MISSINGEQUALS = System::Int8(0x4);
static constexpr System::Int8 MSG_E_EXPECTED_TOKEN = System::Int8(0x5);
static constexpr System::Int8 MSG_E_UNEXPECTED_TOKEN = System::Int8(0x6);
static constexpr System::Int8 MSG_E_MISSINGQUOTE = System::Int8(0x7);
static constexpr System::Int8 MSG_E_COMMENTSYNTAX = System::Int8(0x8);
static constexpr System::Int8 MSG_E_BADSTARTNAMECHAR = System::Int8(0x9);
static constexpr System::Int8 MSG_E_BADNAMECHAR = System::Int8(0xa);
static constexpr System::Int8 MSG_E_BADCHARINSTRING = System::Int8(0xb);
static constexpr System::Int8 MSG_E_XMLDECLSYNTAX = System::Int8(0xc);
static constexpr System::Int8 MSG_E_BADCHARDATA = System::Int8(0xd);
static constexpr System::Int8 MSG_E_MISSINGWHITESPACE = System::Int8(0xe);
static constexpr System::Int8 MSG_E_EXPECTINGTAGEND = System::Int8(0xf);
static constexpr System::Int8 MSG_E_BADCHARINDTD = System::Int8(0x10);
static constexpr System::Int8 MSG_E_BADCHARINDECL = System::Int8(0x11);
static constexpr System::Int8 MSG_E_MISSINGSEMICOLON = System::Int8(0x12);
static constexpr System::Int8 MSG_E_BADCHARINENTREF = System::Int8(0x13);
static constexpr System::Int8 MSG_E_UNBALANCEDPAREN = System::Int8(0x14);
static constexpr System::Int8 MSG_E_EXPECTINGOPENBRACKET = System::Int8(0x15);
static constexpr System::Int8 MSG_E_BADENDCONDSECT = System::Int8(0x16);
static constexpr System::Int8 MSG_E_INTERNALERROR = System::Int8(0x17);
static constexpr System::Int8 MSG_E_UNEXPECTED_WHITESPACE = System::Int8(0x18);
static constexpr System::Int8 MSG_E_INCOMPLETE_ENCODING = System::Int8(0x19);
static constexpr System::Int8 MSG_E_BADCHARINMIXEDMODEL = System::Int8(0x1a);
static constexpr System::Int8 MSG_E_MISSING_STAR = System::Int8(0x1b);
static constexpr System::Int8 MSG_E_BADCHARINMODEL = System::Int8(0x1c);
static constexpr System::Int8 MSG_E_MISSING_PAREN = System::Int8(0x1d);
static constexpr System::Int8 MSG_E_BADCHARINENUMERATION = System::Int8(0x1e);
static constexpr System::Int8 MSG_E_PIDECLSYNTAX = System::Int8(0x1f);
static constexpr System::Int8 MSG_E_EXPECTINGCLOSEQUOTE = System::Int8(0x20);
static constexpr System::Int8 MSG_E_MULTIPLE_COLONS = System::Int8(0x21);
static constexpr System::Int8 MSG_E_INVALID_DECIMAL = System::Int8(0x22);
static constexpr System::Int8 MSG_E_INVALID_HEXADECIMAL = System::Int8(0x23);
static constexpr System::Int8 MSG_E_INVALID_UNICODE = System::Int8(0x24);
static constexpr System::Int8 MSG_E_WHITESPACEORQUESTIONMARK = System::Int8(0x25);
static constexpr System::Int8 MSG_E_SUSPENDED = System::Int8(0x26);
static constexpr System::Int8 MSG_E_STOPPED = System::Int8(0x27);
static constexpr System::Int8 MSG_E_UNEXPECTEDENDTAG = System::Int8(0x28);
static constexpr System::Int8 MSG_E_UNCLOSEDTAG = System::Int8(0x29);
static constexpr System::Int8 MSG_E_DUPLICATEATTRIBUTE = System::Int8(0x2a);
static constexpr System::Int8 MSG_E_MULTIPLEROOTS = System::Int8(0x2b);
static constexpr System::Int8 MSG_E_INVALIDATROOTLEVEL = System::Int8(0x2c);
static constexpr System::Int8 MSG_E_BADXMLDECL = System::Int8(0x2d);
static constexpr System::Int8 MSG_E_MISSINGROOT = System::Int8(0x2e);
static constexpr System::Int8 MSG_E_UNEXPECTEDEOF = System::Int8(0x2f);
static constexpr System::Int8 MSG_E_BADPEREFINSUBSET = System::Int8(0x30);
static constexpr System::Int8 MSG_E_PE_NESTING = System::Int8(0x31);
static constexpr System::Int8 MSG_E_INVALID_CDATACLOSINGTAG = System::Int8(0x32);
static constexpr System::Int8 MSG_E_UNCLOSEDPI = System::Int8(0x33);
static constexpr System::Int8 MSG_E_UNCLOSEDSTARTTAG = System::Int8(0x34);
static constexpr System::Int8 MSG_E_UNCLOSEDENDTAG = System::Int8(0x35);
static constexpr System::Int8 MSG_E_UNCLOSEDSTRING = System::Int8(0x36);
static constexpr System::Int8 MSG_E_UNCLOSEDCOMMENT = System::Int8(0x37);
static constexpr System::Int8 MSG_E_UNCLOSEDDECL = System::Int8(0x38);
static constexpr System::Int8 MSG_E_UNCLOSEDMARKUPDECL = System::Int8(0x39);
static constexpr System::Int8 MSG_E_UNCLOSEDCDATA = System::Int8(0x3a);
static constexpr System::Int8 MSG_E_BADDECLNAME = System::Int8(0x3b);
static constexpr System::Int8 MSG_E_BADEXTERNALID = System::Int8(0x3c);
static constexpr System::Int8 MSG_E_BADELEMENTINDTD = System::Int8(0x3d);
static constexpr System::Int8 MSG_E_RESERVEDNAMESPACE = System::Int8(0x3e);
static constexpr System::Int8 MSG_E_EXPECTING_VERSION = System::Int8(0x3f);
static constexpr System::Int8 MSG_E_EXPECTING_ENCODING = System::Int8(0x40);
static constexpr System::Int8 MSG_E_EXPECTING_NAME = System::Int8(0x41);
static constexpr System::Int8 MSG_E_UNEXPECTED_ATTRIBUTE = System::Int8(0x42);
static constexpr System::Int8 MSG_E_ENDTAGMISMATCH = System::Int8(0x43);
static constexpr System::Int8 MSG_E_INVALIDENCODING = System::Int8(0x44);
static constexpr System::Int8 MSG_E_INVALIDSWITCH = System::Int8(0x45);
static constexpr System::Int8 MSG_E_EXPECTING_NDATA = System::Int8(0x46);
static constexpr System::Int8 MSG_E_INVALID_MODEL = System::Int8(0x47);
static constexpr System::Int8 MSG_E_INVALID_TYPE = System::Int8(0x48);
static constexpr System::Int8 MSG_E_INVALIDXMLSPACE = System::Int8(0x49);
static constexpr System::Int8 MSG_E_MULTI_ATTR_VALUE = System::Int8(0x4a);
static constexpr System::Int8 MSG_E_INVALID_PRESENCE = System::Int8(0x4b);
static constexpr System::Int8 MSG_E_BADXMLCASE = System::Int8(0x4c);
static constexpr System::Int8 MSG_E_CONDSECTINSUBSET = System::Int8(0x4d);
static constexpr System::Int8 MSG_E_CDATAINVALID = System::Int8(0x4e);
static constexpr System::Int8 MSG_E_INVALID_STANDALONE = System::Int8(0x4f);
static constexpr System::Int8 MSG_E_UNEXPECTED_STANDALONE = System::Int8(0x50);
static constexpr System::Int8 MSG_E_DOCTYPE_IN_DTD = System::Int8(0x51);
static constexpr System::Int8 MSG_E_MISSING_ENTITY = System::Int8(0x52);
static constexpr System::Int8 MSG_E_ENTITYREF_INNAME = System::Int8(0x53);
static constexpr System::Int8 MSG_E_DOCTYPE_OUTSIDE_PROLOG = System::Int8(0x54);
static constexpr System::Int8 MSG_E_INVALID_VERSION = System::Int8(0x55);
static constexpr System::Int8 MSG_E_DTDELEMENT_OUTSIDE_DTD = System::Int8(0x56);
static constexpr System::Int8 MSG_E_DUPLICATEDOCTYPE = System::Int8(0x57);
static constexpr System::Int8 MSG_E_RESOURCE = System::Int8(0x58);
static constexpr System::Int8 MSG_E_INVALID_OPERATION = System::Int8(0x59);
static constexpr System::Int8 MSG_E_WRONG_DOCUMENT = System::Int8(0x5a);
static constexpr System::Int8 XML_BASE = System::Int8(0x5b);
static constexpr System::Int8 XML_IOERROR = System::Int8(0x5b);
static constexpr System::Int8 XML_ENTITY_UNDEFINED = System::Int8(0x5c);
static constexpr System::Int8 XML_INFINITE_ENTITY_LOOP = System::Int8(0x5d);
static constexpr System::Int8 XML_NDATA_INVALID_PE = System::Int8(0x5e);
static constexpr System::Int8 XML_REQUIRED_NDATA = System::Int8(0x5f);
static constexpr System::Int8 XML_NDATA_INVALID_REF = System::Int8(0x60);
static constexpr System::Int8 XML_EXTENT_IN_ATTR = System::Int8(0x61);
static constexpr System::Int8 XML_STOPPED_BY_USER = System::Int8(0x62);
static constexpr System::Int8 XML_PARSING_ENTITY = System::Int8(0x63);
static constexpr System::Int8 XML_E_MISSING_PE_ENTITY = System::Int8(0x64);
static constexpr System::Int8 XML_E_MIXEDCONTENT_DUP_NAME = System::Int8(0x65);
static constexpr System::Int8 XML_NAME_COLON = System::Int8(0x66);
static constexpr System::Int8 XML_ELEMENT_UNDECLARED = System::Int8(0x67);
static constexpr System::Int8 XML_ELEMENT_ID_NOT_FOUND = System::Int8(0x68);
static constexpr System::Int8 XML_DEFAULT_ATTRIBUTE = System::Int8(0x69);
static constexpr System::Int8 XML_XMLNS_RESERVED = System::Int8(0x6a);
static constexpr System::Int8 XML_EMPTY_NOT_ALLOWED = System::Int8(0x6b);
static constexpr System::Int8 XML_ELEMENT_NOT_COMPLETE = System::Int8(0x6c);
static constexpr System::Int8 XML_ROOT_NAME_MISMATCH = System::Int8(0x6d);
static constexpr System::Int8 XML_INVALID_CONTENT = System::Int8(0x6e);
static constexpr System::Int8 XML_ATTRIBUTE_NOT_DEFINED = System::Int8(0x6f);
static constexpr System::Int8 XML_ATTRIBUTE_FIXED = System::Int8(0x70);
static constexpr System::Int8 XML_ATTRIBUTE_VALUE = System::Int8(0x71);
static constexpr System::Int8 XML_ILLEGAL_TEXT = System::Int8(0x72);
static constexpr System::Int8 XML_MULTI_FIXED_VALUES = System::Int8(0x73);
static constexpr System::Int8 XML_NOTATION_DEFINED = System::Int8(0x74);
static constexpr System::Int8 XML_ELEMENT_DEFINED = System::Int8(0x75);
static constexpr System::Int8 XML_ELEMENT_UNDEFINED = System::Int8(0x76);
static constexpr System::Int8 XML_XMLNS_UNDEFINED = System::Int8(0x77);
static constexpr System::Int8 XML_XMLNS_FIXED = System::Int8(0x78);
static constexpr System::Int8 XML_E_UNKNOWNERROR = System::Int8(0x79);
static constexpr System::Int8 XML_REQUIRED_ATTRIBUTE_MISSING = System::Int8(0x7a);
static constexpr System::Int8 XML_MISSING_NOTATION = System::Int8(0x7b);
static constexpr System::Int8 XML_ATTLIST_DUPLICATED_ID = System::Int8(0x7c);
static constexpr System::Int8 XML_ATTLIST_ID_PRESENCE = System::Int8(0x7d);
static constexpr System::Int8 XML_XMLLANG_INVALIDID = System::Int8(0x7e);
static constexpr System::Int8 XML_PUBLICID_INVALID = System::Int8(0x7f);
static constexpr System::Byte XML_DTD_EXPECTING = System::Byte(0x80);
static constexpr System::Byte XML_NAMESPACE_URI_EMPTY = System::Byte(0x81);
static constexpr System::Byte XML_LOAD_EXTERNALENTITY = System::Byte(0x82);
static constexpr System::Byte XML_BAD_ENCODING = System::Byte(0x83);
static constexpr System::Byte NS_NS_ERROR = System::Byte(0x84);
static constexpr System::Byte NS_EMPTY_NOT_ALLOWED = System::Byte(0x85);
static constexpr System::Byte NS_E_BADNAMECHAR = System::Byte(0x86);
extern DELPHI_PACKAGE _di_OmniIXMLDocument __fastcall CreateXMLDoc(void);
extern DELPHI_PACKAGE bool __fastcall CharIs_Letter(const System::WideChar ch);
extern DELPHI_PACKAGE bool __fastcall CharIs_WhiteSpace(const System::WideChar ch);
extern DELPHI_PACKAGE bool __fastcall CharIs_Char(const System::WideChar ch);
extern DELPHI_PACKAGE bool __fastcall CharIs_NameChar(const System::WideChar ch);
extern DELPHI_PACKAGE bool __fastcall CharIs_Name(const System::WideChar ch, const bool IsFirstChar);
extern DELPHI_PACKAGE System::UnicodeString __fastcall EncodeText(const System::UnicodeString Value);
extern DELPHI_PACKAGE System::UnicodeString __fastcall UniTrim(const System::UnicodeString Value);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ShrinkEol(const System::UnicodeString Value);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ExpandEol(const System::UnicodeString Value);
}	/* namespace Omnixml */
}	/* namespace Internal */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL_OMNIXML)
using namespace Xml::Internal::Omnixml;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL)
using namespace Xml::Internal;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_Internal_OmnixmlHPP
