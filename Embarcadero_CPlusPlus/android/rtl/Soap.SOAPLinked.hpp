// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.SOAPLinked.pas' rev: 34.00 (Android)

#ifndef Soap_SoaplinkedHPP
#define Soap_SoaplinkedHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.TypInfo.hpp>
#include <Soap.IntfInfo.hpp>
#include <Soap.InvokeRegistry.hpp>
#include <Soap.OPToSOAPDomConv.hpp>
#include <Soap.Rio.hpp>
#include <Soap.SOAPAttachIntf.hpp>
#include <Soap.SOAPPasInv.hpp>
#include <Soap.WebNode.hpp>
#include <Soap.WSDLIntf.hpp>
#include <Soap.SOAPDomConv.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Soaplinked
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TLinkedWebNode;
class DELPHICLASS TLogLinkedWebNode;
class DELPHICLASS TLinkedRIO;
class DELPHICLASS TLinkedOPToSoapDomConvert;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TLinkedWebNode : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Soap::Soappasinv::TSoapPascalInvoker* FInvoker;
	System::Typinfo::TTypeInfo *IntfInfo;
	System::TClass FClass;
	System::UnicodeString FMimeBoundary;
	Soap::Webnode::WebNodeOptions FWebNodeOptions;
	Soap::Intfinfo::TIntfMethEntry FMethIntf;
	System::TArray__1<System::Byte> FStaticRequest;
	System::TArray__1<System::Byte> FStaticResponse;
	
protected:
	System::UnicodeString __fastcall GetMimeBoundary();
	void __fastcall SetMimeBoundary(const System::UnicodeString Value);
	Soap::Webnode::WebNodeOptions __fastcall GetWebNodeOptions();
	void __fastcall SetWebNodeOptions(Soap::Webnode::WebNodeOptions Value);
	virtual System::Classes::TStream* __fastcall GetResponseStream();
	void __fastcall InvokeImplementation(System::Classes::TStream* const Request, System::Classes::TStream* Response);
	
public:
	__fastcall virtual TLinkedWebNode(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TLinkedWebNode();
	virtual void __fastcall BeforeExecute(const Soap::Intfinfo::TIntfMetaData &IntfMetaData, const Soap::Intfinfo::TIntfMethEntry &MethodMetaData, int MethodIndex, Soap::Soapattachintf::_di_IMimeAttachmentHandler AttachHandler);
	virtual void __fastcall Execute(const System::UnicodeString DataMsg, System::Classes::TStream* Resp)/* overload */;
	virtual void __fastcall Execute(System::Classes::TStream* const Request, System::Classes::TStream* Response)/* overload */;
	System::Classes::TStream* __fastcall Execute(System::Classes::TStream* const Request)/* overload */;
	
__published:
	__property Soap::Soappasinv::TSoapPascalInvoker* Invoker = {read=FInvoker};
	__property System::TArray__1<System::Byte> StaticRequest = {read=FStaticRequest, write=FStaticRequest};
	__property System::TArray__1<System::Byte> StaticResponse = {read=FStaticResponse, write=FStaticResponse};
	__property System::UnicodeString MimeBoundary = {read=GetMimeBoundary, write=SetMimeBoundary};
private:
	void *__IWebNode;	// Soap::Webnode::IWebNode 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {77DB2644-0C12-4C0A-920E-89579DB9CC16}
	operator Soap::Webnode::_di_IWebNode()
	{
		Soap::Webnode::_di_IWebNode intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Soap::Webnode::IWebNode*(void) { return (Soap::Webnode::IWebNode*)&__IWebNode; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TLogLinkedWebNode : public TLinkedWebNode
{
	typedef TLinkedWebNode inherited;
	
private:
	System::UnicodeString FReqFile;
	System::UnicodeString FRespFile;
	
protected:
	virtual System::Classes::TStream* __fastcall GetResponseStream();
	
public:
	__fastcall virtual TLogLinkedWebNode(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TLogLinkedWebNode();
	virtual void __fastcall Execute(System::Classes::TStream* const Request, System::Classes::TStream* Response)/* overload */;
	
__published:
	__property System::UnicodeString ReqFile = {read=FReqFile, write=FReqFile};
	__property System::UnicodeString RespFile = {read=FRespFile, write=FRespFile};
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Execute(const System::UnicodeString DataMsg, System::Classes::TStream* Resp){ TLinkedWebNode::Execute(DataMsg, Resp); }
	inline System::Classes::TStream* __fastcall  Execute(System::Classes::TStream* const Request){ return TLinkedWebNode::Execute(Request); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TLinkedRIO : public Soap::Rio::TRIO
{
	typedef Soap::Rio::TRIO inherited;
	
private:
	TLinkedWebNode* FLinkedWebNode;
	Soap::Optosoapdomconv::TOPToSoapDomConvert* FDOMConverter;
	Soap::Optosoapdomconv::TOPToSoapDomConvert* FDefaultConverter;
	Soap::Optosoapdomconv::TOPToSoapDomConvert* __fastcall GetDomConverter();
	void __fastcall SetDomConverter(Soap::Optosoapdomconv::TOPToSoapDomConvert* Value);
	Soap::Optosoapdomconv::TOPToSoapDomConvert* __fastcall GetDefaultConverter();
	
protected:
	virtual System::Classes::TStream* __fastcall GetResponseStream(Soap::Wsdlintf::TWebServiceBindingType BindingType);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	/**
	 * Template function to ease querying for a
	 * smart-Interface-object
	 */
	template <typename T>
	HRESULT __stdcall QueryInterface(::System::DelphiInterface<T>& smartIntf)
	{
	  return QueryInterface(__uuidof(T), reinterpret_cast<void*>(static_cast<T**>(&smartIntf)));
	}
	virtual HRESULT __stdcall QueryInterface(const GUID IID, /* out */ void *Obj);
	__fastcall virtual TLinkedRIO(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall TLinkedRIO(System::Classes::TComponent* AOwner, System::UnicodeString ReqFile, System::UnicodeString RespFile)/* overload */;
	__fastcall virtual ~TLinkedRIO();
	__property TLinkedWebNode* WebNode = {read=FLinkedWebNode};
	
__published:
	__property Soap::Optosoapdomconv::TOPToSoapDomConvert* Converter = {read=GetDomConverter, write=SetDomConverter};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TLinkedOPToSoapDomConvert : public Soap::Optosoapdomconv::TOPToSoapDomConvert
{
	typedef Soap::Optosoapdomconv::TOPToSoapDomConvert inherited;
	
__published:
	TLinkedRIO* FLinkedRIO;
	
public:
	__fastcall TLinkedOPToSoapDomConvert(System::Classes::TComponent* AOwner, TLinkedRIO* ALinkedRIO);
	virtual System::Classes::TStream* __fastcall InvContextToMsg(const Soap::Intfinfo::TIntfMetaData &IntfMD, int MethNum, Soap::Invokeregistry::TInvContext* Con, Soap::Invokeregistry::THeaderList* Headers);
public:
	/* TOPToSoapDomConvert.Create */ inline __fastcall virtual TLinkedOPToSoapDomConvert(System::Classes::TComponent* AOwner) : Soap::Optosoapdomconv::TOPToSoapDomConvert(AOwner) { }
	/* TOPToSoapDomConvert.Destroy */ inline __fastcall virtual ~TLinkedOPToSoapDomConvert() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::TArray__1<System::Byte> __fastcall LoadDataFromFile(const System::UnicodeString FileName);
extern DELPHI_PACKAGE void __fastcall WriteDataToFile(const System::UnicodeString FileName, const System::TArray__1<System::Byte> Data);
}	/* namespace Soaplinked */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_SOAPLINKED)
using namespace Soap::Soaplinked;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_SoaplinkedHPP
