// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.SOAPHTTPDisp.pas' rev: 34.00 (iOS)

#ifndef Soap_SoaphttpdispHPP
#define Soap_SoaphttpdispHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Soap.WSDLIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Soaphttpdisp
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IHTTPSoapDispatch;
typedef System::DelphiInterface<IHTTPSoapDispatch> _di_IHTTPSoapDispatch;
class DELPHICLASS THTTPSoapDispatchNode;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{9E733EDC-7639-4DAF-96FF-BCF141F7D8F2}") IHTTPSoapDispatch  : public System::IInterface 
{
	virtual void __fastcall DispatchSOAP(const System::UnicodeString Path, const System::UnicodeString SoapAction, System::Classes::TStream* const Request, System::Classes::TStream* Response, Soap::Wsdlintf::TWebServiceBindingType &BindingType) = 0 ;
};

class PASCALIMPLEMENTATION THTTPSoapDispatchNode : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	void __fastcall SetSoapDispatcher(const _di_IHTTPSoapDispatch Value);
	
protected:
	_di_IHTTPSoapDispatch FSoapDispatcher;
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	virtual void __fastcall DispatchSOAP(const System::UnicodeString Path, const System::UnicodeString SoapAction, System::Classes::TStream* const Request, System::Classes::TStream* Response);
	
__published:
	__property _di_IHTTPSoapDispatch Dispatcher = {read=FSoapDispatcher, write=SetSoapDispatcher};
public:
	/* TComponent.Create */ inline __fastcall virtual THTTPSoapDispatchNode(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~THTTPSoapDispatchNode() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Soaphttpdisp */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_SOAPHTTPDISP)
using namespace Soap::Soaphttpdisp;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_SoaphttpdispHPP
