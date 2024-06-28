// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.SOAPHTTPClient.pas' rev: 34.00 (iOS)

#ifndef Soap_SoaphttpclientHPP
#define Soap_SoaphttpclientHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Soap.OPToSOAPDomConv.hpp>
#include <Soap.Rio.hpp>
#include <Soap.SOAPHTTPTrans.hpp>
#include <Soap.WSDLItems.hpp>
#include <Soap.WSDLNode.hpp>
#include <Xml.XMLIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Soaphttpclient
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS THTTPRIO;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION THTTPRIO : public Soap::Rio::TRIO
{
	typedef Soap::Rio::TRIO inherited;
	
private:
	Soap::Wsdlitems::TWSDLItems* FWSDLItems;
	Xml::Xmlintf::_di_IXMLDocument WSDLItemDoc;
	Soap::Wsdlnode::TWSDLView* FWSDLView;
	System::UnicodeString FWSDLLocation;
	Soap::Optosoapdomconv::TOPToSoapDomConvert* FDOMConverter;
	Soap::Soaphttptrans::THTTPReqResp* FHTTPWebNode;
	Soap::Optosoapdomconv::TOPToSoapDomConvert* FDefaultConverter;
	Soap::Soaphttptrans::THTTPReqResp* FDefaultWebNode;
	void __fastcall ClearDependentWSDLView();
	void __fastcall SetWSDLLocation(System::UnicodeString Value);
	System::UnicodeString __fastcall GetPort();
	void __fastcall SetPortValue(System::UnicodeString Value);
	System::UnicodeString __fastcall GetService();
	void __fastcall SetService(System::UnicodeString Value);
	void __fastcall CheckWSDLView();
	void __fastcall SetURL(System::UnicodeString Value);
	Soap::Optosoapdomconv::TOPToSoapDomConvert* __fastcall GetDomConverter();
	void __fastcall SetDomConverter(Soap::Optosoapdomconv::TOPToSoapDomConvert* Value);
	Soap::Soaphttptrans::THTTPReqResp* __fastcall GetHTTPWebNode();
	void __fastcall SetHTTPWebNode(Soap::Soaphttptrans::THTTPReqResp* Value);
	System::UnicodeString __fastcall GetURL();
	Soap::Soaphttptrans::THTTPReqResp* __fastcall GetDefaultWebNode();
	Soap::Optosoapdomconv::TOPToSoapDomConvert* __fastcall GetDefaultConverter();
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual THTTPRIO(System::Classes::TComponent* AOwner);
	__fastcall virtual ~THTTPRIO();
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
	__property Soap::Wsdlitems::TWSDLItems* WSDLItems = {read=FWSDLItems};
	
__published:
	__property System::UnicodeString WSDLLocation = {read=FWSDLLocation, write=SetWSDLLocation};
	__property System::UnicodeString Service = {read=GetService, write=SetService};
	__property System::UnicodeString Port = {read=GetPort, write=SetPortValue};
	__property System::UnicodeString URL = {read=GetURL, write=SetURL};
	__property Soap::Soaphttptrans::THTTPReqResp* HTTPWebNode = {read=GetHTTPWebNode, write=SetHTTPWebNode};
	__property Soap::Optosoapdomconv::TOPToSoapDomConvert* Converter = {read=GetDomConverter, write=SetDomConverter};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Soaphttpclient */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_SOAPHTTPCLIENT)
using namespace Soap::Soaphttpclient;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_SoaphttpclientHPP
