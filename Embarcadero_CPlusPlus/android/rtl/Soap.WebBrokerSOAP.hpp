// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.WebBrokerSOAP.pas' rev: 34.00 (Android)

#ifndef Soap_WebbrokersoapHPP
#define Soap_WebbrokersoapHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Masks.hpp>
#include <Soap.SOAPAttachIntf.hpp>
#include <Soap.SOAPHTTPDisp.hpp>
#include <Web.AutoDisp.hpp>
#include <Web.HTTPApp.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Webbrokersoap
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS THTTPSoapDispatcher;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION THTTPSoapDispatcher : public Soap::Soaphttpdisp::THTTPSoapDispatchNode
{
	typedef Soap::Soaphttpdisp::THTTPSoapDispatchNode inherited;
	
private:
	Web::Autodisp::TWebDispatch* FWebDispatch;
	void __fastcall SetWebDispatch(Web::Autodisp::TWebDispatch* const Value);
	
protected:
	bool __fastcall DispatchEnabled();
	System::Masks::TMask* __fastcall DispatchMask();
	Web::Httpapp::TMethodType __fastcall DispatchMethodType();
	bool __fastcall DispatchRequest(System::TObject* Sender, Web::Httpapp::TWebRequest* Request, Web::Httpapp::TWebResponse* Response);
	
public:
	__fastcall virtual THTTPSoapDispatcher(System::Classes::TComponent* AOwner);
	__fastcall virtual ~THTTPSoapDispatcher();
	
__published:
	__property Web::Autodisp::TWebDispatch* WebDispatch = {read=FWebDispatch, write=SetWebDispatch};
private:
	void *__IWebDispatch;	// Web::Httpapp::IWebDispatch 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E6D33BE4-9FAE-D511-8D38-0050568E0E44}
	operator Web::Httpapp::_di_IWebDispatch()
	{
		Web::Httpapp::_di_IWebDispatch intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Web::Httpapp::IWebDispatch*(void) { return (Web::Httpapp::IWebDispatch*)&__IWebDispatch; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Web::Httpapp::TWebModule* __fastcall GetSOAPWebModule(void);
}	/* namespace Webbrokersoap */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_WEBBROKERSOAP)
using namespace Soap::Webbrokersoap;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_WebbrokersoapHPP
