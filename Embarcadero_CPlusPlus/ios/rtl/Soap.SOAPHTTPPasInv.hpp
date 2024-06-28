// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.SOAPHTTPPasInv.pas' rev: 34.00 (iOS)

#ifndef Soap_SoaphttppasinvHPP
#define Soap_SoaphttppasinvHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Soap.SOAPPasInv.hpp>
#include <Soap.SOAPHTTPDisp.hpp>
#include <Soap.WSDLIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Soaphttppasinv
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS THTTPSoapPascalInvoker;
class DELPHICLASS THTTPSoapCppInvoker;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION THTTPSoapPascalInvoker : public Soap::Soappasinv::TSoapPascalInvoker
{
	typedef Soap::Soappasinv::TSoapPascalInvoker inherited;
	
public:
	virtual void __fastcall DispatchSOAP(const System::UnicodeString Path, const System::UnicodeString SoapAction, System::Classes::TStream* const Request, System::Classes::TStream* Response, Soap::Wsdlintf::TWebServiceBindingType &BindingType);
public:
	/* TSoapPascalInvoker.Create */ inline __fastcall virtual THTTPSoapPascalInvoker(System::Classes::TComponent* AOwner) : Soap::Soappasinv::TSoapPascalInvoker(AOwner) { }
	/* TSoapPascalInvoker.Destroy */ inline __fastcall virtual ~THTTPSoapPascalInvoker() { }
	
private:
	void *__IHTTPSoapDispatch;	// Soap::Soaphttpdisp::IHTTPSoapDispatch 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9E733EDC-7639-4DAF-96FF-BCF141F7D8F2}
	operator Soap::Soaphttpdisp::_di_IHTTPSoapDispatch()
	{
		Soap::Soaphttpdisp::_di_IHTTPSoapDispatch intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Soap::Soaphttpdisp::IHTTPSoapDispatch*(void) { return (Soap::Soaphttpdisp::IHTTPSoapDispatch*)&__IHTTPSoapDispatch; }
	#endif
	
};


class PASCALIMPLEMENTATION THTTPSoapCppInvoker : public THTTPSoapPascalInvoker
{
	typedef THTTPSoapPascalInvoker inherited;
	
public:
	/* TSoapPascalInvoker.Create */ inline __fastcall virtual THTTPSoapCppInvoker(System::Classes::TComponent* AOwner) : THTTPSoapPascalInvoker(AOwner) { }
	/* TSoapPascalInvoker.Destroy */ inline __fastcall virtual ~THTTPSoapCppInvoker() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Soaphttppasinv */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_SOAPHTTPPASINV)
using namespace Soap::Soaphttppasinv;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_SoaphttppasinvHPP
