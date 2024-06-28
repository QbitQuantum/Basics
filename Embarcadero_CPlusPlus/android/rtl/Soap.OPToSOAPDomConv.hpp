// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.OPToSOAPDomConv.pas' rev: 34.00 (Android)

#ifndef Soap_OptosoapdomconvHPP
#define Soap_OptosoapdomconvHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.TypInfo.hpp>
#include <Soap.IntfInfo.hpp>
#include <Soap.InvokeRegistry.hpp>
#include <Soap.OPConvert.hpp>
#include <Soap.OpConvertOptions.hpp>
#include <Soap.SOAPAttachIntf.hpp>
#include <Soap.SOAPDomConv.hpp>
#include <Soap.SOAPEnv.hpp>
#include <Soap.WSDLNode.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.xmldom.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Optosoapdomconv
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ESOAPDomConvertError;
struct TSOAPArrayElemDesc;
struct TMultiRefNodeMapElem;
class DELPHICLASS TRefCache;
struct TMultiRefNodeElem;
class DELPHICLASS TSOAPDomConv;
class DELPHICLASS TOPToSoapDomConvert;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ESOAPDomConvertError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ESOAPDomConvertError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESOAPDomConvertError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESOAPDomConvertError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESOAPDomConvertError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESOAPDomConvertError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESOAPDomConvertError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESOAPDomConvertError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESOAPDomConvertError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESOAPDomConvertError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESOAPDomConvertError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESOAPDomConvertError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESOAPDomConvertError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESOAPDomConvertError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<NativeInt> TNativeIntDynArray;

struct DECLSPEC_DRECORD TSOAPArrayElemDesc
{
public:
	bool MultiDim;
	TNativeIntDynArray Dims;
};


typedef System::DynamicArray<TSOAPArrayElemDesc> TSOAPArrayDesc;

struct DECLSPEC_DRECORD TMultiRefNodeMapElem
{
public:
	void *Instance;
	System::UnicodeString ID;
};


typedef System::DynamicArray<TMultiRefNodeMapElem> TMultiRefNodeMap;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TRefCache : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::_di_IInterfaceList FNodes;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,int>* FHREFs;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::TObject*>* FMHREFs;
	
public:
	__fastcall TRefCache();
	__fastcall virtual ~TRefCache();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<Xml::Xmlintf::_di_IXMLNode> TXMLNodeArray;

struct DECLSPEC_DRECORD TMultiRefNodeElem
{
public:
	Xml::Xmlintf::_di_IXMLNode Node;
	TXMLNodeArray MultiRefChildren;
};


typedef System::DynamicArray<TMultiRefNodeElem> TMultiRefNodes;

enum DECLSPEC_DENUM ConvNodeState : unsigned char { nsClientSend, nsServerReceive, nsServerSend, nsClientReceive };

typedef void __fastcall (__closure *TMemberDataNotReceivedEvent)(const System::UnicodeString ClassName, const System::UnicodeString Member);

typedef void __fastcall (__closure *TUnhandledNodeEvent)(const System::UnicodeString Name, System::UnicodeString NodeXML);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TSOAPDomConv : public Soap::Soapdomconv::TSOAPDOMProcessor
{
	typedef Soap::Soapdomconv::TSOAPDOMProcessor inherited;
	
	
private:
	typedef System::DynamicArray<System::TObject*> _TSOAPDomConv__1;
	
	
private:
	int FIDs;
	Soap::Soapattachintf::TSoapDataList* FAttachments;
	TRefCache* FRefCache;
	TMultiRefNodes MultiRefNodes;
	Soap::Opconvertoptions::TSOAPConvertOptions FOptions;
	_TSOAPDomConv__1 ObjsWriting;
	TMemberDataNotReceivedEvent FOnMemberDataNotReceived;
	TUnhandledNodeEvent FOnUnhandledNode;
	void __fastcall Clear();
	void __fastcall FAttachmentsNotify(System::TObject* Sender, Soap::Invokeregistry::TSOAPAttachment* const Item, System::Generics::Collections::TCollectionNotification Action);
	
protected:
	void __fastcall AddAttachment(Soap::Invokeregistry::TSOAPAttachment* Attachment, const System::UnicodeString AContentId);
	Soap::Invokeregistry::TSOAPAttachment* __fastcall FindAttachment(const System::UnicodeString AContentId);
	void __fastcall ReadHeader(const Xml::Xmlintf::_di_IXMLNode EnvNode, const Xml::Xmlintf::_di_IXMLNode HdrNode, Soap::Invokeregistry::THeaderList* Headers);
	void __fastcall WriteHeader(System::TObject* const Header, Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode ParentNode);
	bool __fastcall NodeIsNULL(Xml::Xmlintf::_di_IXMLNode Node);
	bool __fastcall ChildNodesAreNull(Xml::Xmlintf::_di_IXMLNode Node);
	Xml::Xmlintf::_di_IXMLNode __fastcall CreateNULLNode(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode ParentNode, const System::UnicodeString Name, bool UseParentNode = false);
	System::UnicodeString __fastcall GetNewID();
	System::UnicodeString __fastcall FindPrefixForURI(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, const System::UnicodeString URI, bool DeclIfNone = false);
	System::UnicodeString __fastcall AddNamespaceDecl(Xml::Xmlintf::_di_IXMLNode Node, const System::UnicodeString URI);
	bool __fastcall GetElementType(Xml::Xmlintf::_di_IXMLNode Node, System::UnicodeString &TypeURI, System::UnicodeString &TypeName);
	Xml::Xmlintf::_di_IXMLNode __fastcall CreateScalarNodeXS(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode ParentNode, const System::UnicodeString NodeName, const System::UnicodeString NodeNamespace, const System::UnicodeString TypeName, const System::UnicodeString Value, bool GenPre = false);
	System::Variant __fastcall GetTypeBySchemaNS(Xml::Xmlintf::_di_IXMLNode Node, const System::UnicodeString URI);
	Xml::Xmlintf::_di_IXMLNode __fastcall CreateTypedNode(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode ParentNode, const System::UnicodeString NodeName, const System::UnicodeString NodeNamespace, const System::UnicodeString TypeName, bool GenPre = false);
	void __fastcall SetNodeType(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode InstNode, const System::UnicodeString ElemURI, const System::UnicodeString TypeName);
	System::UnicodeString __fastcall GetNodeAsText(Xml::Xmlintf::_di_IXMLNode Node);
	Xml::Xmlintf::_di_IXMLNode __fastcall GetDataNode(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, System::UnicodeString &ID);
	void __fastcall CheckEncodingStyle(Xml::Xmlintf::_di_IXMLNode Node);
	void __fastcall AddMultiRefNode(const System::UnicodeString ID, void * Instance);
	System::UnicodeString __fastcall FindMultiRefNodeByInstance(void * Instance);
	void * __fastcall FindMultiRefNodeByID(const System::UnicodeString ID);
	Xml::Xmlintf::_di_IXMLNode __fastcall CreateMultiRefNode(Xml::Xmlintf::_di_IXMLNode RootNode, const System::UnicodeString Name, const System::UnicodeString ID);
	void __fastcall FinalizeMultiRefNodes();
	Xml::Xmlintf::_di_IXMLNode __fastcall FindNodeByHREF(Xml::Xmlintf::_di_IXMLNode RootNode, const System::UnicodeString HREF);
	void __fastcall AddObjectAsWriting(System::TObject* Instance);
	void __fastcall RemoveObjectAsWriting(System::TObject* Instance);
	bool __fastcall IsObjectWriting(System::TObject* Instance);
	void __fastcall ResetMultiRef();
	void __fastcall ConvertVariantToSoap(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, const System::UnicodeString Name, const System::UnicodeString NodeNamespace, System::Typinfo::PTypeInfo Info, PVarData P, const System::Variant &V, bool UseVariant);
	void __fastcall ConvertSoapToVariant(Xml::Xmlintf::_di_IXMLNode Node, void * InvData);
	bool __fastcall IsNodeAVarArray(const Xml::Xmlintf::_di_IXMLNode Node, System::Word &VT);
	void __fastcall WriteVarArray(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, const System::UnicodeString Name, const System::UnicodeString NodeNamespace, const System::Variant &V);
	void __fastcall WriteVariant(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, const System::UnicodeString Name, const System::UnicodeString NodeNamespace, const System::Variant &V);
	void __fastcall ReadVariant(Xml::Xmlintf::_di_IXMLNode Node, void * P);
	System::Variant __fastcall ReadVarArrayDim(Xml::Xmlintf::_di_IXMLNode Node, bool IsVarVArray = false, System::Word VT = (System::Word)(0x0));
	void __fastcall WriteVarArrayAsB64(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, const System::UnicodeString Name, const System::Variant &V);
	Xml::Xmlintf::_di_IXMLNode __fastcall MakeArrayNode(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, const System::UnicodeString Name, const System::UnicodeString URI, const System::UnicodeString TypeName, NativeInt *Indices, const int Indices_High)/* overload */;
	Xml::Xmlintf::_di_IXMLNode __fastcall MakeArrayNode(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, const System::UnicodeString Name, const System::UnicodeString URI, const System::UnicodeString TypeName, int Dim, int Len)/* overload */;
	void __fastcall ConvertNativeArrayToSoap(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, const System::UnicodeString NodeName, const System::UnicodeString NodeNamespace, const System::UnicodeString ChildNamespace, System::Typinfo::PTypeInfo Info, void * P, bool InlineElements = false);
	void __fastcall WriteNonRectDynArray(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, const System::UnicodeString Name, System::Typinfo::PTypeInfo Info, const System::UnicodeString URI, const System::UnicodeString TypeName, void * P, int Dim);
	int __fastcall WriteNonRectDynArrayElem(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, System::Typinfo::PTypeInfo Info, const System::UnicodeString URI, const System::UnicodeString TypeName, void * P, int Dim);
	void * __fastcall ConvertSoapToNativeArray(void * DataP, System::Typinfo::PTypeInfo TypeInfo, Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, const System::UnicodeString ElementName = System::UnicodeString());
	void * __fastcall ConvertSoapToNativeArrayElem(System::Typinfo::PTypeInfo ArrayInfo, System::Typinfo::PTypeInfo ElemInfo, Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, TSOAPArrayDesc ArrayDesc, int Dims, int CurDim, void * DataP, const System::UnicodeString ElementName = System::UnicodeString());
	void __fastcall ConvertByteArrayToSoap(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, const System::UnicodeString Name, const System::UnicodeString NodeNamespace, System::Typinfo::PTypeInfo Info, void * P);
	void __fastcall WriteRectDynArrayElem(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, System::Typinfo::PTypeInfo Info, int Size, int Dim, void * P, const System::UnicodeString NodeName, const System::UnicodeString Namespace = System::UnicodeString());
	void __fastcall WriteRectDynArray _DEPRECATED_ATTRIBUTE0 (Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, System::Typinfo::PTypeInfo Info, int Dims, void * P, const System::UnicodeString NodeName);
	void __fastcall ReadRectDynArray(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, System::Typinfo::PTypeInfo Info, int Dims, void * P, int CurElem);
	void __fastcall ReadRectDynArrayElem(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, System::Typinfo::PTypeInfo Info, int Size, int Dim, void * P, int &CurElem);
	void __fastcall ReadRow(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, int &CurElem, int Size, void * P, System::Typinfo::PTypeInfo Info, const System::UnicodeString ElementName = System::UnicodeString());
	System::UnicodeString __fastcall ConvertEnumToSoap(System::Typinfo::PTypeInfo Info, void * P);
	int __fastcall ConvertSoapToEnum(System::Typinfo::PTypeInfo Info, const System::UnicodeString S, bool IsNull);
	bool __fastcall MultiRefObject(System::TClass Cls);
	Soap::Invokeregistry::TSerializationOptions __fastcall SerializationOptions(System::TClass Cls)/* overload */;
	Soap::Invokeregistry::TSerializationOptions __fastcall SerializationOptions(System::Typinfo::PTypeInfo ATypeInfo)/* overload */;
	Soap::Invokeregistry::TSerializationOptions __fastcall SerializationOptions(System::TObject* Obj)/* overload */;
	void __fastcall ConvertObjectToSOAP(const System::UnicodeString NodeName, const System::UnicodeString NodeNamespace, const System::UnicodeString ChildNamespace, void * ObjP, Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node);
	System::TObject* __fastcall ConvertSOAPToObject(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, System::TClass AClass, const System::UnicodeString URI, const System::UnicodeString TypeName, void * ObjP);
	System::UnicodeString __fastcall CreateObjectNode(System::TObject* Instance, Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode ParentNode, const System::UnicodeString NodeName, const System::UnicodeString NodeNamespace, const System::UnicodeString ChildNamespace, Soap::Invokeregistry::TObjectConvertOptions ObjConvOpts);
	Xml::Xmlintf::_di_IXMLNode __fastcall ObjInstanceToSOAP(System::TObject* Instance, Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode ParentNode, const System::UnicodeString NodeName, const System::UnicodeString NodeNamespace, const System::UnicodeString ChildNamespace, Soap::Invokeregistry::TObjectConvertOptions ObjConvOpts, /* out */ System::UnicodeString &RefID);
	void __fastcall LoadObject(System::TObject* Instance, Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node);
	void __fastcall InitObjectFromSOAP(System::TObject* Instance, Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node);
	void __fastcall ObjectMemberNoShow(const System::UnicodeString ClassName, const System::UnicodeString MemberName);
	void __fastcall UnhandledNode(const System::UnicodeString Name, System::UnicodeString NodeXML);
	void __fastcall SetObjectPropFromText(System::TObject* Instance, System::Typinfo::PPropInfo PropInfo, const System::UnicodeString SoapData);
	System::UnicodeString __fastcall GetObjectPropAsText(System::TObject* Instance, System::Typinfo::PPropInfo PropInfo);
	Soap::Opconvertoptions::TSOAPConvertOptions __fastcall GetOptions();
	void __fastcall SetOptions(const Soap::Opconvertoptions::TSOAPConvertOptions Value);
	void __fastcall SetNodeTypeEx(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode InstNode, const System::UnicodeString ElemURI, const System::UnicodeString TypeName, bool Forced);
	static bool __fastcall HasMultipleElemNamespaces(const System::TClass ClsType, /* out */ Soap::Invokeregistry::InvStringDynArray &PropNamespaces, /* out */ System::TArray__1<int> &PropNamespaceIndex);
	
public:
	__fastcall virtual TSOAPDomConv(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSOAPDomConv();
	DYNAMIC void __fastcall ConvertNativeDataToSoap(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, const System::UnicodeString NodeName, const System::UnicodeString NodeNamespace, System::Typinfo::PTypeInfo Info, void * P, int XMLOptions);
	DYNAMIC void __fastcall ConvertSoapToNativeData(void * DataP, System::Typinfo::PTypeInfo TypeInfo, Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node, bool Translate);
	
__published:
	__property Soap::Opconvertoptions::TSOAPConvertOptions Options = {read=FOptions, write=FOptions, default=10};
	__property TMemberDataNotReceivedEvent OnMemberDataNotReceived = {read=FOnMemberDataNotReceived, write=FOnMemberDataNotReceived};
	__property TUnhandledNodeEvent OnUnhandledNode = {read=FOnUnhandledNode, write=FOnUnhandledNode};
private:
	void *__IObjConverter;	// Soap::Invokeregistry::IObjConverter 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7F67EA52-A3D1-429B-B54D-49F692B6131A}
	operator Soap::Invokeregistry::_di_IObjConverter()
	{
		Soap::Invokeregistry::_di_IObjConverter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Soap::Invokeregistry::IObjConverter*(void) { return (Soap::Invokeregistry::IObjConverter*)&__IObjConverter; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TOPToSoapDomConvert : public TSOAPDomConv
{
	typedef TSOAPDomConv inherited;
	
private:
	Soap::Wsdlnode::TWSDLView* FWSDLView;
	System::UnicodeString FTempDir;
	Soap::Soapenv::TSoapEnvelope* Envelope;
	System::UnicodeString FEncoding;
	System::UnicodeString __fastcall GetSoapNS(const Soap::Intfinfo::TIntfMetaData &MD);
	void __fastcall DOMToStream(const Xml::Xmlintf::_di_IXMLDocument XMLDoc, System::Classes::TStream* Stream);
	void __fastcall ProcessFault(Xml::Xmlintf::_di_IXMLNode FaultNode);
	void __fastcall ProcessSuccess(Xml::Xmlintf::_di_IXMLNode RespNode, const Soap::Intfinfo::TIntfMetaData &IntfMD, const Soap::Intfinfo::TIntfMethEntry &MD, Soap::Invokeregistry::TInvContext* InvContext);
	System::UnicodeString __fastcall GetPartName(const Soap::Intfinfo::TIntfMetaData &MethMD, const System::UnicodeString ParamName);
	void __fastcall CheckWSDL();
	System::UnicodeString __fastcall GetBinding();
	void __fastcall SetWSDLView(Soap::Wsdlnode::TWSDLView* const WSDLView);
	virtual Soap::Soapattachintf::TSoapDataList* __fastcall GetAttachments();
	virtual void __fastcall SetAttachments(Soap::Soapattachintf::TSoapDataList* Value);
	virtual System::UnicodeString __fastcall GetTempDir();
	virtual void __fastcall SetTempDir(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetEncoding();
	void __fastcall SetEncoding(const System::UnicodeString Encoding);
	
protected:
	Xml::Xmlintf::_di_IXMLDocument __fastcall NewXMLDocument();
	
public:
	__fastcall virtual TOPToSoapDomConvert(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TOPToSoapDomConvert();
	__property Soap::Soapattachintf::TSoapDataList* Attachments = {read=GetAttachments, write=SetAttachments};
	virtual void __fastcall MsgToInvContext(const System::UnicodeString Request, const Soap::Intfinfo::TIntfMetaData &IntfMD, int &MethNum, Soap::Invokeregistry::TInvContext* Context)/* overload */;
	virtual void __fastcall MsgToInvContext(System::Classes::TStream* const Request, const Soap::Intfinfo::TIntfMetaData &IntfMD, int &MethNum, Soap::Invokeregistry::TInvContext* Context, Soap::Invokeregistry::THeaderList* Headers)/* overload */;
	virtual System::Classes::TStream* __fastcall InvContextToMsg(const Soap::Intfinfo::TIntfMetaData &IntfMD, int MethNum, Soap::Invokeregistry::TInvContext* Con, Soap::Invokeregistry::THeaderList* Headers);
	virtual void __fastcall MakeResponse(const Soap::Intfinfo::TIntfMetaData &IntfMD, const int MethNum, Soap::Invokeregistry::TInvContext* Context, System::Classes::TStream* Response, Soap::Invokeregistry::THeaderList* Headers);
	virtual void __fastcall MakeFault(System::Sysutils::Exception* const Ex, System::Classes::TStream* EStream);
	virtual void __fastcall ProcessResponse(const System::UnicodeString Resp, const Soap::Intfinfo::TIntfMetaData &IntfMD, const Soap::Intfinfo::TIntfMethEntry &MD, Soap::Invokeregistry::TInvContext* Context)/* overload */;
	virtual void __fastcall ProcessResponse(System::Classes::TStream* const Resp, const Soap::Intfinfo::TIntfMetaData &IntfMD, const Soap::Intfinfo::TIntfMethEntry &MD, Soap::Invokeregistry::TInvContext* Context, Soap::Invokeregistry::THeaderList* Headers)/* overload */;
	virtual void __fastcall ProcessResponse(const Xml::Xmlintf::_di_IXMLDocument XMLDoc, const Soap::Intfinfo::TIntfMetaData &IntfMD, const Soap::Intfinfo::TIntfMethEntry &MD, Soap::Invokeregistry::TInvContext* Context, Soap::Invokeregistry::THeaderList* Headers)/* overload */;
	
__published:
	__property Soap::Wsdlnode::TWSDLView* WSDLView = {read=FWSDLView, write=SetWSDLView};
	__property System::UnicodeString TempDir = {read=GetTempDir, write=SetTempDir};
	__property System::UnicodeString Encoding = {read=GetEncoding, write=SetEncoding};
private:
	void *__IOPConvert;	// Soap::Opconvert::IOPConvert 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1F955FE3-890B-474C-A3A4-5E072D30CC4F}
	operator Soap::Opconvert::_di_IOPConvert()
	{
		Soap::Opconvert::_di_IOPConvert intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Soap::Opconvert::IOPConvert*(void) { return (Soap::Opconvert::IOPConvert*)&__IOPConvert; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define SVarArrayType u"VarArrayType"
extern DELPHI_PACKAGE System::UnicodeString DefArrayElemName;
}	/* namespace Optosoapdomconv */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_OPTOSOAPDOMCONV)
using namespace Soap::Optosoapdomconv;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_OptosoapdomconvHPP
