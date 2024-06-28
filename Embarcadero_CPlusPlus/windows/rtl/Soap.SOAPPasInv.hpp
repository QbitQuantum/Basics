// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.SOAPPasInv.pas' rev: 34.00 (Windows)

#ifndef Soap_SoappasinvHPP
#define Soap_SoappasinvHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.TypInfo.hpp>
#include <Soap.InvokeRegistry.hpp>
#include <Soap.OPConvert.hpp>
#include <Soap.OPToSOAPDomConv.hpp>
#include <Soap.SOAPAttachIntf.hpp>
#include <Soap.WSDLIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Soappasinv
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IAdapterConverter;
typedef System::DelphiInterface<IAdapterConverter> _di_IAdapterConverter;
__interface DELPHIINTERFACE IInvokerConverter;
typedef System::DelphiInterface<IInvokerConverter> _di_IInvokerConverter;
class DELPHICLASS TSoapPascalInvoker;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TBeforeDispatchEvent)(const System::UnicodeString MethodName, System::Classes::TStream* const Request);

typedef void __fastcall (__closure *TBeforeDispatchEvent2)(const System::UnicodeString MethodName, System::Classes::TStream* const Request, System::Classes::TStream* Response, Soap::Wsdlintf::TWebServiceBindingType &BindingType, bool &Handled);

typedef void __fastcall (__closure *TAfterDispatchEvent)(const System::UnicodeString MethodName, System::Classes::TStream* SOAPResponse);

typedef void __fastcall (__closure *TOnExceptionEvent)(const System::UnicodeString MethodName, System::Classes::TStream* const Request, System::Classes::TStream* const Response);

__interface  INTERFACE_UUID("{82165DF4-B1B9-D511-9561-00C04FA06B45}") IAdapterConverter  : public System::IInterface 
{
	virtual Soap::Optosoapdomconv::TOPToSoapDomConvert* __fastcall GetDomConverter() = 0 ;
};

__interface  INTERFACE_UUID("{367A2E38-0539-D611-97F2-00C04FA06B45}") IInvokerConverter  : public System::IInterface 
{
	virtual TSoapPascalInvoker* __fastcall GetInvoker() = 0 ;
};

class PASCALIMPLEMENTATION TSoapPascalInvoker : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TBeforeDispatchEvent FBeforeDispatchEvent;
	TBeforeDispatchEvent2 FBeforeDispatchEvent2;
	TAfterDispatchEvent FAfterDispatchEvent;
	Soap::Soapattachintf::TOnSendAttachmentEvent FOnSendAttachment;
	Soap::Soapattachintf::TOnGetAttachmentEvent FOnGetAttachment;
	TOnExceptionEvent FOnExceptionEvent;
	void __fastcall SetDomConverter(Soap::Optosoapdomconv::TOPToSoapDomConvert* Value);
	
protected:
	Soap::Invokeregistry::THeaderList* FHeadersIn;
	Soap::Invokeregistry::THeaderList* FHeadersOut;
	Soap::Opconvert::_di_IOPConvert FConverter;
	Soap::Invokeregistry::TSOAPHeaders* FSOAPHeaders;
	Soap::Optosoapdomconv::TOPToSoapDomConvert* FDomConverter;
	Soap::Optosoapdomconv::TOPToSoapDomConvert* __fastcall GetDomConverter();
	TSoapPascalInvoker* __fastcall GetInvoker();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TSoapPascalInvoker(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSoapPascalInvoker();
	HIDESBASE virtual void __fastcall Invoke(System::TClass AClass, System::Typinfo::PTypeInfo IntfInfo, System::UnicodeString MethName, System::Classes::TStream* const Request, System::Classes::TStream* Response, Soap::Wsdlintf::TWebServiceBindingType &BindingType);
	
__published:
	__property TBeforeDispatchEvent BeforeDispatchEvent = {read=FBeforeDispatchEvent, write=FBeforeDispatchEvent};
	__property TAfterDispatchEvent AfterDispatchEvent = {read=FAfterDispatchEvent, write=FAfterDispatchEvent};
	__property Soap::Soapattachintf::TOnSendAttachmentEvent OnSendAttachment = {read=FOnSendAttachment, write=FOnSendAttachment};
	__property Soap::Soapattachintf::TOnGetAttachmentEvent OnGetAttachment = {read=FOnGetAttachment, write=FOnGetAttachment};
	__property TOnExceptionEvent OnExceptionEvent = {read=FOnExceptionEvent, write=FOnExceptionEvent};
	__property TBeforeDispatchEvent2 BeforeDispatchEvent2 = {read=FBeforeDispatchEvent2, write=FBeforeDispatchEvent2};
	__property Soap::Optosoapdomconv::TOPToSoapDomConvert* Converter = {read=GetDomConverter, write=SetDomConverter};
private:
	void *__IInvokerConverter;	// IInvokerConverter 
	void *__IAdapterConverter;	// IAdapterConverter 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {367A2E38-0539-D611-97F2-00C04FA06B45}
	operator _di_IInvokerConverter()
	{
		_di_IInvokerConverter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IInvokerConverter*(void) { return (IInvokerConverter*)&__IInvokerConverter; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {82165DF4-B1B9-D511-9561-00C04FA06B45}
	operator _di_IAdapterConverter()
	{
		_di_IAdapterConverter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IAdapterConverter*(void) { return (IAdapterConverter*)&__IAdapterConverter; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Soap::Invokeregistry::_di_ISOAPHeaders __fastcall GetSOAPHeaders(void);
}	/* namespace Soappasinv */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_SOAPPASINV)
using namespace Soap::Soappasinv;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_SoappasinvHPP
