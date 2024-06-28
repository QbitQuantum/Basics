// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.InvokeRegistry.pas' rev: 34.00 (iOS)

#ifndef Soap_InvokeregistryHPP
#define Soap_InvokeregistryHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.SysTypes.hpp>
#include <System.SysUtils.hpp>
#include <System.TypInfo.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SyncObjs.hpp>
#include <Soap.IntfInfo.hpp>
#include <Soap.OpConvertOptions.hpp>
#include <Xml.XMLSchema.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.xmldom.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
#if !defined(SOAP_REMOTABLE_CLASS)
#define SOAP_REMOTABLE_CLASS __declspec(delphiclass)
#endif
                                                     
namespace Soap {
 namespace Invokeregistry {
  struct TDynToClear;
 };
};
using Soap::Invokeregistry::TDynToClear;

namespace Soap
{
namespace Invokeregistry
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IObjConverter;
typedef System::DelphiInterface<IObjConverter> _di_IObjConverter;
class DELPHICLASS TRemotable;
class DELPHICLASS TRemotableXS;
class DELPHICLASS TSOAPHeader;
class DELPHICLASS ERemotableException;
class DELPHICLASS TSOAPAttachment;
class DELPHICLASS THeaderList;
__interface DELPHIINTERFACE IHeadersSetter;
typedef System::DelphiInterface<IHeadersSetter> _di_IHeadersSetter;
__interface DELPHIINTERFACE ISOAPHeaders;
typedef System::DelphiInterface<ISOAPHeaders> _di_ISOAPHeaders;
class DELPHICLASS TSOAPHeadersBase;
class DELPHICLASS TSOAPHeaders;
class DELPHICLASS TInvokableClass;
struct InvRegClassEntry;
struct ExtNameMapItem;
struct IntfHeaderItem;
struct IntfExceptionItem;
struct ParameterMapItem;
struct MethodMapItem;
struct InterfaceMapItem;
class DELPHICLASS TInvokableClassRegistry;
struct TRemHeaderEntry;
struct TRemRegEntry;
class DELPHICLASS ETypeRegistryException;
class DELPHICLASS TRemotableTypeRegistry;
struct TDynToClear;
class DELPHICLASS TDataContext;
class DELPHICLASS TInvContext;
//-- type declarations -------------------------------------------------------
typedef System::UnicodeString InvString;

typedef System::DynamicArray<System::UnicodeString> InvStringDynArray;

typedef System::DynamicArray<System::Byte> TByteSOAPArray;

typedef System::DynamicArray<int> TIntegerSOAPArray;

typedef System::DynamicArray<unsigned> TCardinalSOAPArray;

typedef System::DynamicArray<System::Word> TWordSOAPArray;

typedef System::DynamicArray<short> TSmallIntSOAPArray;

typedef System::DynamicArray<System::Int8> TShortIntSOAPArray;

typedef System::DynamicArray<__int64> TInt64SOAPArray;

typedef System::DynamicArray<unsigned long> TLongWordSOAPArray;

typedef System::DynamicArray<float> TSingleSOAPArray;

typedef System::DynamicArray<double> TDoubleSOAPArray;

typedef System::DynamicArray<bool> TBooleanSOAPArray;

typedef System::DynamicArray<System::UnicodeString> TStringSOAPArray;

typedef System::DynamicArray<System::WideString> TWideStringSOAPArray;

enum DECLSPEC_DENUM ObjectConvertOptions : unsigned char { ocoDontPrefixNode, ocoDontSerializeProps, ocoDontPutTypeAttr };

typedef System::Set<ObjectConvertOptions, ObjectConvertOptions::ocoDontPrefixNode, ObjectConvertOptions::ocoDontPutTypeAttr> TObjectConvertOptions;

__interface  INTERFACE_UUID("{7F67EA52-A3D1-429B-B54D-49F692B6131A}") IObjConverter  : public System::IInterface 
{
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall ObjInstanceToSOAP(System::TObject* Instance, Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode ParentNode, const System::UnicodeString NodeName, const System::UnicodeString NodeNamespace, const System::UnicodeString ChildNamespace, TObjectConvertOptions ObjConvOpts, /* out */ System::UnicodeString &RefID) = 0 ;
	virtual void __fastcall InitObjectFromSOAP(System::TObject* Instance, Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode Node) = 0 ;
	virtual void __fastcall AddAttachment(TSOAPAttachment* Attachment, const System::UnicodeString AContentId) = 0 ;
	virtual TSOAPAttachment* __fastcall FindAttachment(const System::UnicodeString AContentId) = 0 ;
	virtual void __fastcall ResetMultiRef() = 0 ;
	virtual Soap::Opconvertoptions::TSOAPConvertOptions __fastcall GetOptions() = 0 ;
};

enum DECLSPEC_DENUM SerializationOptions : unsigned char { xoHolderClass, xoAttributeOnLastMember, xoInlineArrays, xoLiteralParam, xoSimpleTypeWrapper, xoOption6, xoOption7, xoOption8, xoOption9, xoOptionA, xoOptionB, xoOptionC, xoOptionD, xoOptionE, xoOptionF, xoOptionG, xoOptionH, xoOptionI };

typedef System::Set<SerializationOptions, SerializationOptions::xoHolderClass, SerializationOptions::xoOptionI> TSerializationOptions;

class PASCALIMPLEMENTATION TRemotable : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDataContext* FDataContext;
	void __fastcall SetDataContext(TDataContext* Value);
	
protected:
	TSerializationOptions FSerializationOptions;
	
public:
	__fastcall virtual TRemotable();
	__fastcall virtual ~TRemotable();
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall ObjectToSOAP(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode ParentNode, const _di_IObjConverter ObjConverter, const System::UnicodeString NodeName, const System::UnicodeString NodeNamespace, const System::UnicodeString ChildNamespace, TObjectConvertOptions ObjConvOpts, /* out */ System::UnicodeString &RefID);
	virtual void __fastcall SOAPToObject(const Xml::Xmlintf::_di_IXMLNode RootNode, const Xml::Xmlintf::_di_IXMLNode Node, const _di_IObjConverter ObjConverter);
	__property TDataContext* DataContext = {read=FDataContext, write=SetDataContext};
	__property TSerializationOptions SerializationOptions = {read=FSerializationOptions, nodefault};
};


class PASCALIMPLEMENTATION TRemotableXS : public TRemotable
{
	typedef TRemotable inherited;
	
public:
	virtual System::UnicodeString __fastcall NativeToXS() = 0 ;
	virtual void __fastcall XSToNative(const System::UnicodeString Data) = 0 ;
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall ObjectToSOAP(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode ParentNode, const _di_IObjConverter ObjConverter, const System::UnicodeString NodeName, const System::UnicodeString NodeNamespace, const System::UnicodeString ChildNamespace, TObjectConvertOptions ObjConvOpts, /* out */ System::UnicodeString &RefID);
	virtual void __fastcall SOAPToObject(const Xml::Xmlintf::_di_IXMLNode RootNode, const Xml::Xmlintf::_di_IXMLNode Node, const _di_IObjConverter ObjConverter);
public:
	/* TRemotable.Create */ inline __fastcall virtual TRemotableXS() : TRemotable() { }
	/* TRemotable.Destroy */ inline __fastcall virtual ~TRemotableXS() { }
	
};


typedef TRemotable* *PTRemotable;

_DECLARE_METACLASS(System::TMetaClass, TRemotableClass);

_DECLARE_METACLASS(System::TMetaClass, TRemotableXSClass);

class PASCALIMPLEMENTATION TSOAPHeader : public TRemotable
{
	typedef TRemotable inherited;
	
private:
	bool FMustUnderstand;
	System::UnicodeString FActor;
	
public:
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall ObjectToSOAP(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode ParentNode, const _di_IObjConverter ObjConverter, const System::UnicodeString NodeName, const System::UnicodeString NodeNamespace, const System::UnicodeString ChildNamespace, TObjectConvertOptions ObjConvOpts, /* out */ System::UnicodeString &RefID);
	virtual void __fastcall SOAPToObject(const Xml::Xmlintf::_di_IXMLNode RootNode, const Xml::Xmlintf::_di_IXMLNode Node, const _di_IObjConverter ObjConverter);
	__property bool MustUnderstand = {read=FMustUnderstand, write=FMustUnderstand, nodefault};
	__property System::UnicodeString Actor = {read=FActor, write=FActor};
public:
	/* TRemotable.Create */ inline __fastcall virtual TSOAPHeader() : TRemotable() { }
	/* TRemotable.Destroy */ inline __fastcall virtual ~TSOAPHeader() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TSOAPHeaderClass);

class PASCALIMPLEMENTATION ERemotableException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
private:
	System::UnicodeString FFaultActor;
	System::UnicodeString FFaultCode;
	System::UnicodeString FFaultDetail;
	System::UnicodeString FFaultReasonLang;
	System::UnicodeString FFaultNode;
	System::UnicodeString FFaultRole;
	void __fastcall SetFaultReason(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetFaultReason();
	
public:
	__fastcall virtual ERemotableException()/* overload */;
	__fastcall virtual ERemotableException(const System::UnicodeString Msg, const System::UnicodeString AFaultCode, const System::UnicodeString AFaultActor, const System::UnicodeString AFaultReasonLang, const System::UnicodeString AFaultNode, const System::UnicodeString AFaultRole)/* overload */;
	__property System::UnicodeString FaultActor = {read=FFaultActor, write=FFaultActor};
	__property System::UnicodeString FaultCode = {read=FFaultCode, write=FFaultCode};
	__property System::UnicodeString FaultDetail = {read=FFaultDetail, write=FFaultDetail};
	__property System::UnicodeString FaultReason = {read=GetFaultReason, write=SetFaultReason};
	__property System::UnicodeString FaultReasonLang = {read=FFaultReasonLang, write=FFaultReasonLang};
	__property System::UnicodeString FaultNode = {read=FFaultNode, write=FFaultNode};
	__property System::UnicodeString FaultRole = {read=FFaultRole, write=FFaultRole};
public:
	/* Exception.CreateFmt */ inline __fastcall ERemotableException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ERemotableException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ERemotableException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ERemotableException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ERemotableException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ERemotableException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ERemotableException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ERemotableException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ERemotableException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ERemotableException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ERemotableException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ERemotableException() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, ERemotableExceptionClass);

class PASCALIMPLEMENTATION TSOAPAttachment : public TRemotable
{
	typedef TRemotable inherited;
	
private:
	System::UnicodeString FCacheFile;
	bool FCacheFilePersist;
	System::UnicodeString FContentType;
	System::UnicodeString FEncoding;
	System::UnicodeString FFileName;
	System::Classes::TStream* FSourceStream;
	System::UnicodeString FSourceString;
	System::Classes::TStrings* FHeaders;
	System::Classes::TStreamOwnership FStreamOwnership;
	void __fastcall ClearStream();
	
protected:
	virtual System::Classes::TStream* __fastcall GetSourceStream();
	virtual void __fastcall InternalSetCacheFile(const System::UnicodeString Value);
	void __fastcall InternalSetSourceStream(System::Classes::TStream* const Value, const System::Classes::TStreamOwnership Ownership = (System::Classes::TStreamOwnership)(0x0));
	virtual void __fastcall SetSourceString(const System::UnicodeString Value);
	virtual void __fastcall SetOwnership(const System::Classes::TStreamOwnership Value);
	
public:
	__fastcall virtual TSOAPAttachment();
	__fastcall virtual ~TSOAPAttachment();
	void __fastcall Init(System::UnicodeString ATempLocation, System::Classes::TStrings* AHeaders, System::UnicodeString AContentType, System::UnicodeString AEncoding);
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall ObjectToSOAP(Xml::Xmlintf::_di_IXMLNode RootNode, Xml::Xmlintf::_di_IXMLNode ParentNode, const _di_IObjConverter ObjConverter, const System::UnicodeString NodeName, const System::UnicodeString NodeNamespace, const System::UnicodeString ChildNamespace, TObjectConvertOptions ObjConvOpts, /* out */ System::UnicodeString &RefID);
	virtual void __fastcall SOAPToObject(const Xml::Xmlintf::_di_IXMLNode RootNode, const Xml::Xmlintf::_di_IXMLNode Node, const _di_IObjConverter ObjConverter);
	__property System::UnicodeString CacheFile = {read=FCacheFile};
	__property bool CacheFilePersist = {read=FCacheFilePersist, write=FCacheFilePersist, default=0};
	__property System::UnicodeString ContentType = {read=FContentType, write=FContentType};
	__property System::UnicodeString Encoding = {read=FEncoding, write=FEncoding};
	__property System::Classes::TStrings* Headers = {read=FHeaders};
	__property System::Classes::TStreamOwnership Ownership = {read=FStreamOwnership, write=FStreamOwnership, nodefault};
	__property System::Classes::TStream* SourceStream = {read=GetSourceStream};
	__property System::UnicodeString SourceString = {read=FSourceString, write=SetSourceString};
	void __fastcall SaveToStream(System::Classes::TStream* AStream);
	void __fastcall SaveToFile(System::UnicodeString AFileName);
	virtual void __fastcall SetSourceFile(const System::UnicodeString Value);
	virtual void __fastcall SetSourceStream(System::Classes::TStream* const Value, const System::Classes::TStreamOwnership Ownership = (System::Classes::TStreamOwnership)(0x0));
};


_DECLARE_METACLASS(System::TMetaClass, TSOAPAttachmentClass);

class PASCALIMPLEMENTATION THeaderList : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::TObject* operator[](int Index) { return this->Headers[Index]; }
	
private:
	System::Generics::Collections::TObjectList__1<System::TObject*>* FObjectList;
	
protected:
	bool __fastcall GetOwnsObjects();
	void __fastcall SetOwnsObjects(bool Val);
	int __fastcall GetCount();
	System::TObject* __fastcall GetHeader(int Index);
	
public:
	__fastcall THeaderList();
	__fastcall virtual ~THeaderList();
	void __fastcall Add(TSOAPHeader* Header)/* overload */;
	void __fastcall Add(System::TObject* Header)/* overload */;
	void __fastcall Clear();
	System::TObject* __fastcall Extract(System::TObject* Obj);
	int __fastcall IndexOf(System::TObject* Obj);
	__property int Count = {read=GetCount, nodefault};
	__property bool OwnsObjects = {read=GetOwnsObjects, write=SetOwnsObjects, nodefault};
	__property System::TObject* Headers[int Index] = {read=GetHeader/*, default*/};
};


__interface  INTERFACE_UUID("{FC96447A-94AC-4C88-B724-192284E2DA34}") IHeadersSetter  : public System::IInterface 
{
	virtual void __fastcall SetHeadersInOut(THeaderList* &InHdrs, THeaderList* &OutHdrs) = 0 ;
};

__interface  INTERFACE_UUID("{E240BE0C-256F-D611-96FA-00C04FA06B45}") ISOAPHeaders  : public System::IInterface 
{
	virtual void __fastcall Send(TSOAPHeader* const Hdr) = 0 ;
	virtual int __fastcall SendCount() = 0 ;
	virtual TSOAPHeader* __fastcall SendAt(int Index) = 0 ;
	virtual void __fastcall Get(System::TClass Cls, /* out */ TSOAPHeader* &Hdr) = 0 /* overload */;
	virtual TSOAPHeader* __fastcall Get(System::TClass Cls) = 0 /* overload */;
	virtual TSOAPHeader* __fastcall Get(const System::UnicodeString Name, const System::UnicodeString URI) = 0 /* overload */;
	virtual bool __fastcall GetOwnsSentHeaders() = 0 ;
	virtual void __fastcall SetOwnsSentHeaders(bool Flag) = 0 ;
	__property bool OwnsSentHeaders = {read=GetOwnsSentHeaders, write=SetOwnsSentHeaders};
};

class PASCALIMPLEMENTATION TSOAPHeadersBase : public System::TContainedObject
{
	typedef System::TContainedObject inherited;
	
protected:
	THeaderList* FHeadersInbound;
	THeaderList* FHeadersOutBound;
	void __fastcall SetHeadersInOut(THeaderList* &InHdrs, THeaderList* &OutHdrs);
public:
	/* TAggregatedObject.Create */ inline __fastcall TSOAPHeadersBase(const System::_di_IInterface Controller) : System::TContainedObject(Controller) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TSOAPHeadersBase() { }
	
private:
	void *__IHeadersSetter;	// IHeadersSetter 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FC96447A-94AC-4C88-B724-192284E2DA34}
	operator _di_IHeadersSetter()
	{
		_di_IHeadersSetter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IHeadersSetter*(void) { return (IHeadersSetter*)&__IHeadersSetter; }
	#endif
	
};


class PASCALIMPLEMENTATION TSOAPHeaders : public TSOAPHeadersBase
{
	typedef TSOAPHeadersBase inherited;
	
public:
	void __fastcall Send(TSOAPHeader* const Hdr);
	int __fastcall SendCount();
	TSOAPHeader* __fastcall SendAt(int Index);
	void __fastcall Get(System::TClass Cls, /* out */ TSOAPHeader* &Hdr)/* overload */;
	TSOAPHeader* __fastcall Get(System::TClass Cls)/* overload */;
	TSOAPHeader* __fastcall Get(const System::UnicodeString Name, const System::UnicodeString URI)/* overload */;
	bool __fastcall GetOwnsSentHeaders();
	void __fastcall SetOwnsSentHeaders(bool Flag);
public:
	/* TAggregatedObject.Create */ inline __fastcall TSOAPHeaders(const System::_di_IInterface Controller) : TSOAPHeadersBase(Controller) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TSOAPHeaders() { }
	
private:
	void *__IHeadersSetter;	// IHeadersSetter 
	void *__ISOAPHeaders;	// ISOAPHeaders 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FC96447A-94AC-4C88-B724-192284E2DA34}
	operator _di_IHeadersSetter()
	{
		_di_IHeadersSetter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IHeadersSetter*(void) { return (IHeadersSetter*)&__IHeadersSetter; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E240BE0C-256F-D611-96FA-00C04FA06B45}
	operator _di_ISOAPHeaders()
	{
		_di_ISOAPHeaders intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ISOAPHeaders*(void) { return (ISOAPHeaders*)&__ISOAPHeaders; }
	#endif
	
};


class PASCALIMPLEMENTATION TInvokableClass : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
protected:
	TSOAPHeaders* FSOAPHeaders;
	int FRefCount;
	HIDESBASE HRESULT __stdcall QueryInterface(const GUID IID, /* out */ void *Obj);
	HIDESBASE int __stdcall _AddRef();
	HIDESBASE int __stdcall _Release();
	
public:
	__fastcall virtual TInvokableClass();
	__fastcall virtual ~TInvokableClass();
	virtual void __fastcall AfterConstruction();
	virtual void __fastcall BeforeDestruction();
	__classmethod virtual System::TObject* __fastcall NewInstance();
	__property int RefCount = {read=FRefCount, nodefault};
private:
	void *__IInterface;	// System::IInterface 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000000-0000-0000-C000-000000000046}
	operator System::_di_IInterface()
	{
		System::_di_IInterface intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::IInterface*(void) { return (System::IInterface*)&__IInterface; }
	#endif
	
};


_DECLARE_METACLASS(System::TMetaClass, TInvokableClassClass);

typedef void __fastcall (*TCreateInstanceProc)(/* out */ System::TObject* &obj);

struct DECLSPEC_DRECORD InvRegClassEntry
{
public:
	System::TClass ClassType;
	TCreateInstanceProc Proc;
	System::UnicodeString URI;
};


struct DECLSPEC_DRECORD ExtNameMapItem
{
public:
	System::UnicodeString Name;
	System::UnicodeString ExtName;
};


enum DECLSPEC_DENUM eHeaderMethodType : unsigned char { hmtAll, hmtRequest, hmtResponse };

typedef System::DynamicArray<eHeaderMethodType> THeaderMethodTypeArray;

typedef System::DynamicArray<bool> TRequiredArray;

struct DECLSPEC_DRECORD IntfHeaderItem
{
public:
	System::Typinfo::TTypeInfo *Info;
	System::TClass ClassType;
	System::UnicodeString Namespace;
	System::UnicodeString Name;
	eHeaderMethodType DefaultMethodType;
	bool DefaultRequired;
	System::UnicodeString MethodNames;
	THeaderMethodTypeArray MethodTypes;
	TRequiredArray HeaderRequired;
};


typedef System::DynamicArray<IntfHeaderItem> THeaderItemArray;

struct DECLSPEC_DRECORD IntfExceptionItem
{
public:
	System::TClass ClassType;
	System::UnicodeString MethodNames;
};


typedef System::DynamicArray<IntfExceptionItem> TExceptionItemArray;

enum DECLSPEC_DENUM TIntfInvokeOption : unsigned char { ioDefault, ioDocument, ioLiteral, ioHasDefaultSOAPAction, ioHasReturnParamNames, ioHasNamespace, ioIsAppServerSOAP, ioHasUDDIInfo, ioHasAllSOAPActions, ioSOAP12 };

typedef System::Set<TIntfInvokeOption, TIntfInvokeOption::ioDefault, TIntfInvokeOption::ioSOAP12> TIntfInvokeOptions;

struct DECLSPEC_DRECORD ParameterMapItem
{
public:
	System::UnicodeString Name;
	System::UnicodeString ExtName;
	System::UnicodeString Namespace;
	int XMLOptions;
};


struct DECLSPEC_DRECORD MethodMapItem
{
	
private:
	typedef System::DynamicArray<ParameterMapItem> _MethodMapItem__1;
	
	
public:
	System::UnicodeString Name;
	System::UnicodeString ExtName;
	System::UnicodeString ReturnName;
	int XMLOptions;
	_MethodMapItem__1 Parameters;
};


struct DECLSPEC_DRECORD InterfaceMapItem
{
	
private:
	typedef System::DynamicArray<MethodMapItem> _InterfaceMapItem__1;
	
	typedef System::DynamicArray<IntfHeaderItem> _InterfaceMapItem__2;
	
	typedef System::DynamicArray<IntfExceptionItem> _InterfaceMapItem__3;
	
	
public:
	System::UnicodeString Name;
	System::UnicodeString ExtName;
	System::UnicodeString UnitName;
	GUID GUID;
	System::Typinfo::TTypeInfo *Info;
	System::TClass DefImpl;
	System::UnicodeString Namespace;
	System::UnicodeString WSDLEncoding;
	System::UnicodeString Documentation;
	System::UnicodeString SOAPAction;
	System::UnicodeString ReturnParamNames;
	TIntfInvokeOptions InvokeOptions;
	_InterfaceMapItem__1 Methods;
	_InterfaceMapItem__2 IntfHeaders;
	_InterfaceMapItem__3 IntfExceptions;
	System::UnicodeString UDDIOperator;
	System::UnicodeString UDDIBindingKey;
};


typedef System::DynamicArray<InterfaceMapItem> TInterfaceMapItemArray;

class PASCALIMPLEMENTATION TInvokableClassRegistry : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<InvRegClassEntry> _TInvokableClassRegistry__1;
	
	typedef System::DynamicArray<InterfaceMapItem> _TInvokableClassRegistry__2;
	
	
private:
	System::Syncobjs::TCriticalSection* FCriticalSection;
	_TInvokableClassRegistry__1 FRegClasses;
	_TInvokableClassRegistry__2 FRegIntfs;
	void __fastcall DeleteFromReg(System::TClass AClass, System::Typinfo::PTypeInfo Info);
	void __fastcall InternalRegisterHeaderClass(System::Typinfo::PTypeInfo Info, System::TClass AClass, const System::UnicodeString HeaderName, const System::UnicodeString HeaderNamespace, eHeaderMethodType DefaultMethodType, const System::UnicodeString MethodName = System::UnicodeString(), eHeaderMethodType MethodType = (eHeaderMethodType)(0x0), bool Required = false);
	void __fastcall InternalRegisterException(System::Typinfo::PTypeInfo Info, System::TClass AClass, const System::UnicodeString MethodName);
	System::UnicodeString __fastcall InternalGetHeaderName(const IntfHeaderItem &Item);
	System::UnicodeString __fastcall InternalGetHeaderNamespace(const IntfHeaderItem &Item);
	
public:
	__fastcall TInvokableClassRegistry();
	__fastcall virtual ~TInvokableClassRegistry();
	void __fastcall RegisterInterface(System::Typinfo::PTypeInfo Info, const System::UnicodeString Namespace = System::UnicodeString(), const System::UnicodeString WSDLEncoding = System::UnicodeString(), const System::UnicodeString Doc = System::UnicodeString(), const System::UnicodeString ExtName = System::UnicodeString());
	void __fastcall RegisterHeaderClass(System::Typinfo::PTypeInfo Info, System::TClass AClass, const System::UnicodeString HeaderName, const System::UnicodeString HeaderNamespace, eHeaderMethodType DefaultMethodType = (eHeaderMethodType)(0x0), bool Required = false)/* overload */;
	void __fastcall RegisterHeaderClass(System::Typinfo::PTypeInfo Info, System::TClass AClass, eHeaderMethodType DefaultMethodType = (eHeaderMethodType)(0x0), bool Required = false)/* overload */;
	void __fastcall RegisterHeaderMethod(System::Typinfo::PTypeInfo Info, System::TClass AClass, const System::UnicodeString MethodName, eHeaderMethodType MethodType = (eHeaderMethodType)(0x0), bool Required = false)/* overload */;
	THeaderItemArray __fastcall GetHeaderInfoForInterface(System::Typinfo::PTypeInfo Info, eHeaderMethodType MethodType = (eHeaderMethodType)(0x0));
	THeaderItemArray __fastcall GetRequestHeaderInfoForInterface(System::Typinfo::PTypeInfo Info);
	THeaderItemArray __fastcall GetResponseHeaderInfoForInterface(System::Typinfo::PTypeInfo Info);
	System::UnicodeString __fastcall GetHeaderName(System::Typinfo::PTypeInfo Info, System::TClass AClass);
	System::UnicodeString __fastcall GetHeaderNamespace(System::Typinfo::PTypeInfo Info, System::TClass AClass)/* overload */;
	System::UnicodeString __fastcall GetHeaderNamespace(System::TClass AClass)/* overload */;
	System::TClass __fastcall GetHeaderClass(System::UnicodeString Name, System::UnicodeString Namespace);
	void __fastcall RegisterException(System::Typinfo::PTypeInfo Info, System::TClass AClass);
	void __fastcall RegisterExceptionMethod(System::Typinfo::PTypeInfo Info, System::TClass AClass, const System::UnicodeString MethodName);
	TExceptionItemArray __fastcall GetExceptionInfoForInterface(System::Typinfo::PTypeInfo Info);
	void __fastcall RegisterInvokableClass(System::TClass AClass, TCreateInstanceProc CreateProc)/* overload */;
	void __fastcall RegisterInvokableClass(System::TClass AClass)/* overload */;
	void __fastcall RegisterExternalParamName(System::Typinfo::PTypeInfo Info, const System::UnicodeString MethodName, const System::UnicodeString InternalName, const System::UnicodeString ExternalName);
	void __fastcall RegisterParamInfo(System::Typinfo::PTypeInfo Info, const System::UnicodeString MethodName, const System::UnicodeString InternalParamName, const System::UnicodeString ExternalParamName, const System::UnicodeString Namespace, int XMLOptions = 0x0);
	void __fastcall GetParamInfo(System::Typinfo::PTypeInfo Info, const System::UnicodeString MethodName, const System::UnicodeString InternalParamName, System::UnicodeString &ExternalParamName, System::UnicodeString &Namespace, int &XMLOptions);
	void __fastcall RegisterExternalMethName(System::Typinfo::PTypeInfo Info, const System::UnicodeString InternalName, const System::UnicodeString ExternalName);
	void __fastcall RegisterMethodInfo(System::Typinfo::PTypeInfo Info, const System::UnicodeString InternalName, const System::UnicodeString ExternalName, const System::UnicodeString ReturnName, int XMLOptions = 0x0);
	void __fastcall GetMethodInfo(System::Typinfo::PTypeInfo Info, const System::UnicodeString InternalName, System::UnicodeString &ExternalName, System::UnicodeString &ReturnName, int &XMLOptions);
	void __fastcall RegisterDefaultSOAPAction(System::Typinfo::PTypeInfo Info, const System::UnicodeString DefSOAPAction);
	void __fastcall RegisterAllSOAPActions(System::Typinfo::PTypeInfo Info, const System::UnicodeString AllSOAPActions);
	System::UnicodeString __fastcall GetActionURIOfInfo(const System::Typinfo::PTypeInfo IntfInfo, const System::UnicodeString MethodName, int MethodIndex);
	System::UnicodeString __fastcall GetActionURIOfIID(const GUID &AGUID);
	void __fastcall RegisterUDDIInfo(System::Typinfo::PTypeInfo Info, const System::UnicodeString Operator, const System::UnicodeString BindingKey);
	bool __fastcall GetUDDIInfo(const System::Typinfo::PTypeInfo IntfInfo, System::UnicodeString &Operator, System::UnicodeString &BindingKey)/* overload */;
	bool __fastcall GetUDDIInfo(const GUID &AGUID, System::UnicodeString &Operator, System::UnicodeString &BindingKey)/* overload */;
	void __fastcall RegisterReturnParamNames(System::Typinfo::PTypeInfo Info, const System::UnicodeString RetParamNames);
	System::UnicodeString __fastcall GetReturnParamNames(const System::Typinfo::PTypeInfo IntfInfo);
	void __fastcall RegisterInvokeOptions(System::Typinfo::PTypeInfo Info, const TIntfInvokeOption InvokeOption)/* overload */;
	void __fastcall RegisterInvokeOptions(System::Typinfo::PTypeInfo Info, const TIntfInvokeOptions InvokeOptions)/* overload */;
	
private:
	virtual void __fastcall Lock();
	virtual void __fastcall UnLock();
	int __fastcall GetIntfIndex(const System::Typinfo::PTypeInfo IntfInfo);
	
public:
	System::UnicodeString __fastcall GetNamespaceByGUID(const GUID &AGUID);
	bool __fastcall GetInfoForURI(const System::UnicodeString PathURI, const System::UnicodeString ActionURI, System::TClass &ACLass, System::Typinfo::PTypeInfo &IntfInfo, System::UnicodeString &AMeth);
	TIntfInvokeOptions __fastcall GetIntfInvokeOptions(const System::Typinfo::PTypeInfo IntfInfo)/* overload */;
	TIntfInvokeOptions __fastcall GetIntfInvokeOptions(const GUID &AGUID)/* overload */;
	void __fastcall GetInterfaceInfoFromName(const System::UnicodeString UnitName, const System::UnicodeString IntfName, System::Typinfo::PTypeInfo &Info, GUID &IID);
	void * __fastcall GetInterfaceTypeInfo(const GUID &AGUID);
	System::TObject* __fastcall GetInvokableObjectFromClass(System::TClass AClass);
	InterfaceMapItem __fastcall GetRegInterfaceEntry(int Index);
	bool __fastcall HasRegInterfaceImpl(int Index);
	void __fastcall GetClassFromIntfInfo(System::Typinfo::PTypeInfo Info, System::TClass &AClass);
	int __fastcall GetInterfaceCount();
	System::UnicodeString __fastcall GetInterfaceExternalName(System::Typinfo::PTypeInfo Info, const System::UnicodeString Namespace, const System::UnicodeString InternalIntfName)/* overload */;
	System::UnicodeString __fastcall GetInterfaceExternalName(System::Typinfo::PTypeInfo Info, const System::UnicodeString Namespace)/* overload */;
	System::UnicodeString __fastcall GetInterfaceExternalName(System::Typinfo::PTypeInfo Info)/* overload */;
	System::UnicodeString __fastcall GetWSDLEncoding(System::Typinfo::PTypeInfo Info, const System::UnicodeString Namespace, const System::UnicodeString InternalIntfName)/* overload */;
	System::UnicodeString __fastcall GetWSDLEncoding(System::Typinfo::PTypeInfo Info, const System::UnicodeString Namespace)/* overload */;
	System::UnicodeString __fastcall GetWSDLEncoding(System::Typinfo::PTypeInfo Info)/* overload */;
	void __fastcall UnRegisterInterface(System::Typinfo::PTypeInfo Info);
	void __fastcall UnRegisterInvokableClass(System::TClass AClass);
	System::UnicodeString __fastcall GetParamExternalName(System::Typinfo::PTypeInfo Info, const System::UnicodeString MethodName, const System::UnicodeString InternalParamName);
	System::UnicodeString __fastcall GetParamInternalName(System::Typinfo::PTypeInfo Info, const System::UnicodeString MethodName, const System::UnicodeString ExternalParamName);
	System::UnicodeString __fastcall GetMethExternalName(System::Typinfo::PTypeInfo Info, const System::UnicodeString MethodIntName);
	System::UnicodeString __fastcall GetMethInternalName(System::Typinfo::PTypeInfo Info, const System::UnicodeString MethodExtName);
};


struct DECLSPEC_DRECORD TRemHeaderEntry
{
public:
	System::UnicodeString Name;
	System::UnicodeString ExtName;
	System::UnicodeString URI;
};


enum DECLSPEC_DENUM TObjMultiOptions : unsigned char { ocDefault, ocMultiRef, ocNoMultiRef };

struct DECLSPEC_DRECORD TRemRegEntry
{
	
private:
	typedef System::DynamicArray<ExtNameMapItem> _TRemRegEntry__1;
	
	
public:
	System::TClass ClassType;
	System::Typinfo::TTypeInfo *Info;
	System::UnicodeString URI;
	System::UnicodeString Name;
	System::UnicodeString ExtName;
	bool IsScalar;
	TObjMultiOptions MultiRefOpt;
	TSerializationOptions SerializationOpt;
	_TRemRegEntry__1 PropNameMap;
};


typedef System::DynamicArray<TRemRegEntry> TRemRegEntryArray;

class PASCALIMPLEMENTATION ETypeRegistryException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ETypeRegistryException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ETypeRegistryException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ETypeRegistryException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ETypeRegistryException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ETypeRegistryException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ETypeRegistryException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ETypeRegistryException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ETypeRegistryException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETypeRegistryException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETypeRegistryException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETypeRegistryException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETypeRegistryException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ETypeRegistryException() { }
	
};


class PASCALIMPLEMENTATION TRemotableTypeRegistry : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<TRemRegEntry> _TRemotableTypeRegistry__1;
	
	
private:
	bool FAutoRegister;
	System::Syncobjs::TCriticalSection* FCriticalSection;
	_TRemotableTypeRegistry__1 URIMAP;
	int __fastcall GetEntry(System::Typinfo::PTypeInfo Info, bool &Found, const System::UnicodeString Name = System::UnicodeString());
	int __fastcall FindEntry(System::Typinfo::PTypeInfo Info, bool &Found, const System::UnicodeString Name = System::UnicodeString());
	void __fastcall DeleteEntryFromURIMap(System::Typinfo::PTypeInfo Info);
	System::Typinfo::PTypeInfo __fastcall GetSimpleBuiltInXSDType(const System::UnicodeString URI, const System::UnicodeString TypeName);
	System::TClass __fastcall GetRegisteredClassForBuiltInXSD(const System::UnicodeString TypeName);
	
protected:
	virtual void __fastcall Lock();
	virtual void __fastcall UnLock();
	
public:
	__fastcall TRemotableTypeRegistry();
	__fastcall virtual ~TRemotableTypeRegistry();
	void __fastcall RegisterXSClass(System::TClass AClass, const System::UnicodeString URI = System::UnicodeString(), const System::UnicodeString Name = System::UnicodeString(), const System::UnicodeString ExtName = System::UnicodeString(), bool IsScalar = false, TObjMultiOptions MultiRefOpt = (TObjMultiOptions)(0x0));
	void __fastcall RegisterXSInfo(System::Typinfo::PTypeInfo Info, const System::UnicodeString URI = System::UnicodeString(), const System::UnicodeString Name = System::UnicodeString(), const System::UnicodeString ExtName = System::UnicodeString());
	void __fastcall RegisterHolderClsMember(System::Typinfo::PTypeInfo ClsTypeInfo, const System::UnicodeString URI = System::UnicodeString(), const System::UnicodeString Name = System::UnicodeString(), const System::UnicodeString ExtName = System::UnicodeString());
	bool __fastcall ClassToURI(System::TClass AClass, System::UnicodeString &URI, System::UnicodeString &Name, bool &IsScalar, bool tryToRegister = true)/* overload */;
	bool __fastcall ClassToURI(System::TClass AClass, System::UnicodeString &URI, System::UnicodeString &Name)/* overload */;
	bool __fastcall InfoToURI(System::Typinfo::PTypeInfo Info, System::UnicodeString &URI, System::UnicodeString &Name, bool &IsScalar, bool tryToRegister = true);
	bool __fastcall TypeInfoToXSD(System::Typinfo::PTypeInfo Info, System::UnicodeString &URI, System::UnicodeString &TypeName);
	void __fastcall GetXSDInfoForClass(System::Typinfo::PTypeInfo Info, System::UnicodeString &URI, System::UnicodeString &TypeName);
	System::TClass __fastcall URIToClass(const System::UnicodeString URI, const System::UnicodeString Name, bool &IsScalar)/* overload */;
	System::TClass __fastcall URIToClass(const System::UnicodeString URI, const System::UnicodeString Name)/* overload */;
	System::Typinfo::PTypeInfo __fastcall XSDToTypeInfo(const System::UnicodeString URI, const System::UnicodeString TypeName);
	System::Typinfo::PTypeInfo __fastcall URIToInfo(const System::UnicodeString URI, const System::UnicodeString Name);
	int __fastcall GetURICount();
	TRemRegEntry __fastcall GetURIMap(int Index)/* overload */;
	bool __fastcall GetURIMap(int Index, /* out */ TRemRegEntry &RegEntry)/* overload */;
	bool __fastcall IsClassScalar(System::TClass AClass);
	TObjMultiOptions __fastcall ClassOptions(System::TClass AClass);
	System::Typinfo::PTypeInfo __fastcall VariantToInfo(const System::Variant &V, bool TryAllSchema);
	System::Word __fastcall GetVarTypeFromXSD(const System::UnicodeString URI, const System::UnicodeString TypeName);
	void __fastcall RegisterSerializeOptions(System::Typinfo::PTypeInfo Info, TSerializationOptions SerialOpt)/* overload */;
	TSerializationOptions __fastcall SerializeOptions(System::Typinfo::PTypeInfo Info)/* overload */;
	void __fastcall RegisterSerializeOptions(System::TClass AClass, TSerializationOptions SerialOpt)/* overload */;
	TSerializationOptions __fastcall SerializeOptions(System::TClass AClass)/* overload */;
	void __fastcall UnRegisterXSClass(System::TClass AClass);
	void __fastcall UnRegisterXSInfo(System::Typinfo::PTypeInfo Info);
	void __fastcall RegisterExternalPropName(System::Typinfo::PTypeInfo Info, const System::UnicodeString InternalName, const System::UnicodeString ExternalName);
	System::UnicodeString __fastcall GetExternalPropName(System::Typinfo::PTypeInfo Info, System::UnicodeString InternalName);
	System::UnicodeString __fastcall GetInternalPropName(System::Typinfo::PTypeInfo Info, const System::UnicodeString ExternalName);
	__property bool AutoRegisterNativeTypes = {read=FAutoRegister, write=FAutoRegister, nodefault};
};


typedef TRemotableTypeRegistry TRemotableClassRegistry;

typedef TRemotableTypeRegistry TPascalRemotableTypeRegistry;

typedef TRemotableTypeRegistry TPascalRemotableClassRegistry;

struct DECLSPEC_DRECORD TDynToClear
{
public:
	void *P;
	System::Typinfo::TTypeInfo *Info;
};


class PASCALIMPLEMENTATION TDataContext : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<System::TObject*> _TDataContext__1;
	
	typedef System::DynamicArray<System::Byte> _TDataContext__2;
	
	typedef System::DynamicArray<void *> _TDataContext__3;
	
	typedef System::DynamicArray<void *> _TDataContext__4;
	
	typedef System::DynamicArray<TDynToClear> _TDataContext__5;
	
	typedef System::DynamicArray<void *> _TDataContext__6;
	
	typedef System::DynamicArray<void *> _TDataContext__7;
	
	typedef System::DynamicArray<void *> _TDataContext__8;
	
	
protected:
	_TDataContext__1 FObjsToDestroy;
	int DataOffset;
	_TDataContext__2 Data;
	_TDataContext__3 DataP;
	_TDataContext__4 VarToClear;
	_TDataContext__5 DynArrayToClear;
	_TDataContext__6 StrToClear;
	_TDataContext__7 WStrToClear;
	_TDataContext__8 UStrToClear;
	
public:
	__fastcall TDataContext();
	__fastcall virtual ~TDataContext();
	void * __fastcall AllocData(int Size);
	void __fastcall SetDataPointer(int Index, void * P);
	void * __fastcall GetDataPointer(int Index);
	void __fastcall AddObjectToDestroy(System::TObject* Obj);
	void __fastcall RemoveObjectToDestroy(System::TObject* Obj);
	void __fastcall AddDynArrayToClear(void * P, System::Typinfo::PTypeInfo Info);
	void __fastcall AddVariantToClear(PVarData P);
	void __fastcall AddStrToClear(void * P);
	void __fastcall AddWStrToClear(void * P);
	void __fastcall AddUStrToClear(void * P);
};


class PASCALIMPLEMENTATION TInvContext : public TDataContext
{
	typedef TDataContext inherited;
	
private:
	void *ResultP;
	
public:
	void __fastcall SetMethodInfo(const Soap::Intfinfo::TIntfMethEntry &MD);
	void __fastcall SetParamPointer(int Param, void * P);
	void * __fastcall GetParamPointer(int Param);
	void * __fastcall GetResultPointer();
	void __fastcall SetResultPointer(void * P);
	void __fastcall AllocServerData(const Soap::Intfinfo::TIntfMethEntry &MD);
public:
	/* TDataContext.Create */ inline __fastcall TInvContext() : TDataContext() { }
	/* TDataContext.Destroy */ inline __fastcall virtual ~TInvContext() { }
	
};


typedef System::StaticArray<System::UnicodeString, 3> Soap_Invokeregistry__51;

typedef System::StaticArray<System::UnicodeString, 3> Soap_Invokeregistry__61;

typedef System::StaticArray<System::UnicodeString, 2> Soap_Invokeregistry__71;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString AppNameSpacePrefix;
extern DELPHI_PACKAGE Soap_Invokeregistry__51 XMLSchemaInstNamespaces;
extern DELPHI_PACKAGE Soap_Invokeregistry__61 XMLSchemaNamespaces;
extern DELPHI_PACKAGE Soap_Invokeregistry__71 XMLBase64Types;
static constexpr bool AS_ATTRIBUTE = false;
extern DELPHI_PACKAGE System::WideString __fastcall SubstituteStrings(const System::WideString InputString, const System::WideString SubString, const System::WideString Replacement);
extern DELPHI_PACKAGE void * __fastcall GetRemotableDataContext(void);
extern DELPHI_PACKAGE void __fastcall SetRemotableDataContext(void * Value);
extern DELPHI_PACKAGE TInvokableClassRegistry* __fastcall InvRegistry(void);
extern DELPHI_PACKAGE TRemotableTypeRegistry* __fastcall RemClassRegistry(void);
extern DELPHI_PACKAGE TRemotableTypeRegistry* __fastcall RemTypeRegistry(void);
}	/* namespace Invokeregistry */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_INVOKEREGISTRY)
using namespace Soap::Invokeregistry;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_InvokeregistryHPP
