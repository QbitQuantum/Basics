// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.WSDLNode.pas' rev: 34.00 (Android)

#ifndef Soap_WsdlnodeHPP
#define Soap_WsdlnodeHPP

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
#include <Soap.SOAPAttachIntf.hpp>
#include <Soap.WebNode.hpp>
#include <Soap.WSDLItems.hpp>
#include <Soap.WSDLIntf.hpp>
#include <Xml.XMLIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Wsdlnode
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EWSDLLoadException;
class DELPHICLASS TWSDLView;
class DELPHICLASS TWSDLClientNode;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EWSDLLoadException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EWSDLLoadException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EWSDLLoadException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWSDLLoadException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWSDLLoadException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWSDLLoadException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWSDLLoadException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWSDLLoadException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWSDLLoadException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWSDLLoadException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWSDLLoadException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWSDLLoadException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWSDLLoadException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWSDLLoadException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TWSDLView : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::UnicodeString FUserName;
	System::UnicodeString FPassword;
	System::UnicodeString FProxy;
	System::UnicodeString FPortType;
	System::UnicodeString FPort;
	System::UnicodeString FOperation;
	System::UnicodeString FService;
	Soap::Wsdlitems::TWSDLItems* FWSDL;
	Xml::Xmlintf::_di_IXMLDocument FIWSDL;
	void __fastcall SetWSDL(Soap::Wsdlitems::TWSDLItems* Value);
	void __fastcall SetOperation(const System::UnicodeString Op);
	System::UnicodeString __fastcall GetService();
	System::UnicodeString __fastcall GetPort();
	
public:
	System::Typinfo::TTypeInfo *IntfInfo;
	void __fastcall Activate();
	void __fastcall SetDesignState(bool Designing);
	
__published:
	__property System::UnicodeString PortType = {read=FPortType, write=FPortType};
	__property System::UnicodeString Port = {read=GetPort, write=FPort};
	__property System::UnicodeString Operation = {read=FOperation, write=SetOperation};
	__property System::UnicodeString Service = {read=GetService, write=FService};
	__property System::UnicodeString UserName = {read=FUserName, write=FUserName};
	__property System::UnicodeString Password = {read=FPassword, write=FPassword};
	__property System::UnicodeString Proxy = {read=FProxy, write=FProxy};
	__property Soap::Wsdlitems::TWSDLItems* WSDL = {read=FWSDL, write=SetWSDL};
public:
	/* TComponent.Create */ inline __fastcall virtual TWSDLView(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TWSDLView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TWSDLClientNode : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TWSDLView* FWSDLView;
	Soap::Webnode::_di_IWebNode FTransportNode;
	void __fastcall SetTransportNode(Soap::Webnode::_di_IWebNode Value);
	
protected:
	System::UnicodeString __fastcall GetMimeBoundary();
	void __fastcall SetMimeBoundary(const System::UnicodeString Value);
	Soap::Webnode::WebNodeOptions __fastcall GetWebNodeOptions();
	void __fastcall SetWebNodeOptions(Soap::Webnode::WebNodeOptions Value);
	
public:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall Execute(const System::UnicodeString DataMsg, System::Classes::TStream* Resp)/* overload */;
	void __fastcall Execute(System::Classes::TStream* const Request, System::Classes::TStream* Response)/* overload */;
	System::Classes::TStream* __fastcall Execute(System::Classes::TStream* const Request)/* overload */;
	void __fastcall BeforeExecute(const Soap::Intfinfo::TIntfMetaData &IntfMetaData, const Soap::Intfinfo::TIntfMethEntry &MethodMetaData, int MethodIndex, Soap::Soapattachintf::_di_IMimeAttachmentHandler AttachHandler);
	
__published:
	__property TWSDLView* WSDLView = {read=FWSDLView, write=FWSDLView};
	__property Soap::Webnode::_di_IWebNode TransportNode = {read=FTransportNode, write=SetTransportNode};
public:
	/* TComponent.Create */ inline __fastcall virtual TWSDLClientNode(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TWSDLClientNode() { }
	
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

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall ActivateWSDL(Soap::Wsdlitems::TWSDLItems* WSDL, const System::UnicodeString Name, const System::UnicodeString Password, const System::UnicodeString Proxy);
}	/* namespace Wsdlnode */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_WSDLNODE)
using namespace Soap::Wsdlnode;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_WsdlnodeHPP
