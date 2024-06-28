// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.WSDLPub.pas' rev: 34.00 (Windows)

#ifndef Soap_WsdlpubHPP
#define Soap_WsdlpubHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Masks.hpp>
#include <Soap.InvokeRegistry.hpp>
#include <Soap.WebServExp.hpp>
#include <Web.AutoDisp.hpp>
#include <Web.HTTPApp.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Wsdlpub
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IWSDLPublish;
typedef System::DelphiInterface<IWSDLPublish> _di_IWSDLPublish;
class DELPHICLASS TWSDLPublish;
class DELPHICLASS TWSDLHTMLPublish;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{ECD820DD-F242-11D4-928A-00C04F990435}") IWSDLPublish  : public System::IInvokable 
{
	virtual Soap::Invokeregistry::InvStringDynArray __stdcall GetPortTypeList() = 0 ;
	virtual System::UnicodeString __stdcall GetWSDLForPortType(const System::UnicodeString PortType) = 0 ;
	virtual Soap::Invokeregistry::InvStringDynArray __stdcall GetTypeSystemsList() = 0 ;
	virtual System::UnicodeString __stdcall GetXSDForTypeSystem(const System::UnicodeString TypeSystem) = 0 ;
};

typedef void __fastcall (__closure *TBeforePublishingWSDLEvent)(const System::UnicodeString IntfName, System::UnicodeString &WSDL, bool &Handled);

class PASCALIMPLEMENTATION TWSDLPublish : public Soap::Invokeregistry::TInvokableClass
{
	typedef Soap::Invokeregistry::TInvokableClass inherited;
	
	
private:
	typedef System::DynamicArray<System::UnicodeString> _TWSDLPublish__1;
	
	typedef System::DynamicArray<System::UnicodeString> _TWSDLPublish__2;
	
	
private:
	_TWSDLPublish__1 Locations;
	_TWSDLPublish__2 PortNames;
	System::UnicodeString FTargetNamespace;
	TBeforePublishingWSDLEvent FOnBeforePublishingWSDL;
	Soap::Webservexp::TBeforePublishingTypesEvent FOnBeforePublishingTypes;
	Soap::Webservexp::TPublishingTypeEvent FOnPublishingType;
	Soap::Webservexp::TAfterPublishingWSDLEvent FOnAfterPublishingWSDL;
	
public:
	__property System::UnicodeString TargetNamespace = {read=FTargetNamespace, write=FTargetNamespace};
	void __fastcall GetPortTypeEntries(Soap::Invokeregistry::TInterfaceMapItemArray &Entries);
	Soap::Invokeregistry::InvStringDynArray __stdcall GetPortTypeList();
	System::UnicodeString __stdcall GetWSDLForPortType(const System::UnicodeString PortType);
	Soap::Invokeregistry::InvStringDynArray __stdcall GetTypeSystemsList();
	System::UnicodeString __stdcall GetXSDForTypeSystem(const System::UnicodeString TypeSystem);
	__property TBeforePublishingWSDLEvent OnBeforePublishingWSDL = {read=FOnBeforePublishingWSDL, write=FOnBeforePublishingWSDL};
	__property Soap::Webservexp::TBeforePublishingTypesEvent OnBeforePublishingTypes = {read=FOnBeforePublishingTypes, write=FOnBeforePublishingTypes};
	__property Soap::Webservexp::TPublishingTypeEvent OnPublishingType = {read=FOnPublishingType, write=FOnPublishingType};
	__property Soap::Webservexp::TAfterPublishingWSDLEvent OnAfterPublishingWSDL = {read=FOnAfterPublishingWSDL, write=FOnAfterPublishingWSDL};
public:
	/* TInvokableClass.Create */ inline __fastcall virtual TWSDLPublish() : Soap::Invokeregistry::TInvokableClass() { }
	/* TInvokableClass.Destroy */ inline __fastcall virtual ~TWSDLPublish() { }
	
private:
	void *__IWSDLPublish;	// IWSDLPublish 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {ECD820DD-F242-11D4-928A-00C04F990435}
	operator _di_IWSDLPublish()
	{
		_di_IWSDLPublish intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IWSDLPublish*(void) { return (IWSDLPublish*)&__IWSDLPublish; }
	#endif
	
};


enum DECLSPEC_DENUM SOAPPublishOptions : unsigned char { poDefault, poPublishLocationAsSecure, poUTF8ContentType };

typedef System::Set<SOAPPublishOptions, SOAPPublishOptions::poDefault, SOAPPublishOptions::poUTF8ContentType> TSOAPPublishOptions;

class PASCALIMPLEMENTATION TWSDLHTMLPublish : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TWSDLPublish* Pub;
	Web::Autodisp::TWebDispatch* FWebDispatch;
	bool FAdminEnabled;
	System::UnicodeString FTargetNamespace;
	TSOAPPublishOptions FPublishOptions;
	TBeforePublishingWSDLEvent FOnBeforePublishingWSDL;
	Soap::Webservexp::TBeforePublishingTypesEvent FOnBeforePublishingTypes;
	Soap::Webservexp::TPublishingTypeEvent FOnPublishingType;
	Soap::Webservexp::TAfterPublishingWSDLEvent FOnAfterPublishingWSDL;
	void __fastcall SetWebDispatch(Web::Autodisp::TWebDispatch* const Value);
	bool __fastcall GetNameSpaceIsStored();
	
protected:
	void __fastcall AddInterfaceList(System::Classes::TStringList* htmldoc, const System::UnicodeString WSDLBaseURL);
	void __fastcall AddPortList(System::Classes::TStringList* htmldoc, const System::UnicodeString PortType);
	void __fastcall UpdatePortList(System::Classes::TStrings* PortList, const System::UnicodeString PortType, const System::UnicodeString Command);
	System::UnicodeString __fastcall GetHostScriptBaseURL(Web::Httpapp::TWebRequest* Request);
	void __fastcall WSILInfo(const System::UnicodeString HostScriptBaseURL, Web::Httpapp::TWebRequest* Request, Web::Httpapp::TWebResponse* Response, bool &Handled);
	
public:
	__fastcall virtual TWSDLHTMLPublish(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWSDLHTMLPublish();
	bool __fastcall DispatchEnabled();
	System::Masks::TMask* __fastcall DispatchMask();
	Web::Httpapp::TMethodType __fastcall DispatchMethodType();
	bool __fastcall DispatchRequest(System::TObject* Sender, Web::Httpapp::TWebRequest* Request, Web::Httpapp::TWebResponse* Response);
	void __fastcall ServiceInfo(System::TObject* Sender, Web::Httpapp::TWebRequest* Request, Web::Httpapp::TWebResponse* Response, bool &Handled);
	int __fastcall HandleRequest(System::Classes::TStringList* Resp, const System::UnicodeString Path, const System::UnicodeString HostScriptBaseURL, System::UnicodeString &ContentType, Web::Httpapp::TWebRequest* Request);
	System::UnicodeString __fastcall GetTargetNamespace();
	
__published:
	__property Web::Autodisp::TWebDispatch* WebDispatch = {read=FWebDispatch, write=SetWebDispatch};
	__property bool AdminEnabled = {read=FAdminEnabled, write=FAdminEnabled, default=0};
	__property System::UnicodeString TargetNamespace = {read=GetTargetNamespace, write=FTargetNamespace, stored=GetNameSpaceIsStored};
	__property TSOAPPublishOptions PublishOptions = {read=FPublishOptions, write=FPublishOptions, default=0};
	__property TBeforePublishingWSDLEvent OnBeforePublishingWSDL = {read=FOnBeforePublishingWSDL, write=FOnBeforePublishingWSDL};
	__property Soap::Webservexp::TBeforePublishingTypesEvent OnBeforePublishingTypes = {read=FOnBeforePublishingTypes, write=FOnBeforePublishingTypes};
	__property Soap::Webservexp::TPublishingTypeEvent OnPublishingType = {read=FOnPublishingType, write=FOnPublishingType};
	__property Soap::Webservexp::TAfterPublishingWSDLEvent OnAfterPublishingWSDL = {read=FOnAfterPublishingWSDL, write=FOnAfterPublishingWSDL};
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


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall WSDLPubFactory(/* out */ System::TObject* &obj);
}	/* namespace Wsdlpub */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_WSDLPUB)
using namespace Soap::Wsdlpub;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_WsdlpubHPP
