// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.SOAPDomConv.pas' rev: 34.00 (iOS)

#ifndef Soap_SoapdomconvHPP
#define Soap_SoapdomconvHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.XMLDoc.hpp>
#include <Soap.OPConvert.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Soapdomconv
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IDOMHeaderProcessor;
typedef System::DelphiInterface<IDOMHeaderProcessor> _di_IDOMHeaderProcessor;
struct TDOMHeaderProcessorEntry;
class DELPHICLASS TSOAPDOMProcessor;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{27F23F8F-23A2-4257-95A8-0204EEFF937B}") IDOMHeaderProcessor  : public System::IInterface 
{
	virtual void __fastcall ProcessHeader(Xml::Xmlintf::_di_IXMLNode HeaderNode, bool &Handled, bool &AbortRequest) = 0 ;
	virtual Xml::Xmlintf::_di_IXMLNode __fastcall CreateHeader(Xml::Xmlintf::_di_IXMLNode HeaderNode) = 0 ;
};

struct DECLSPEC_DRECORD TDOMHeaderProcessorEntry
{
public:
	_di_IDOMHeaderProcessor Processor;
	System::WideString NameSpace;
	System::WideString HeaderName;
	System::WideString TypeName;
};


typedef System::DynamicArray<TDOMHeaderProcessorEntry> TDOMHeaderProcessorArray;

class PASCALIMPLEMENTATION TSOAPDOMProcessor : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	int FRefCount;
	bool FOwnerIsComponent;
	
protected:
	TDOMHeaderProcessorArray FHeaderProcessors;
	virtual _di_IDOMHeaderProcessor __fastcall FindHeaderProcessor(System::WideString Namespace, System::WideString HeaderName, System::WideString TypeName);
	Xml::Xmlintf::_di_IXMLNode __fastcall MakeHeaderNodes(Xml::Xmlintf::_di_IXMLNode HeaderNode);
	HIDESBASE int __stdcall _AddRef();
	HIDESBASE int __stdcall _Release();
	
public:
	virtual void __fastcall AddHeaderProcessor(System::WideString Namespace, System::WideString HeaderName, System::WideString TypeName, _di_IDOMHeaderProcessor Processor);
	virtual void __fastcall DefaultProcessHeader(Xml::Xmlintf::_di_IXMLNode HeaderNode, bool &Handled, bool &AbortRequest);
	__classmethod virtual System::TObject* __fastcall NewInstance();
	virtual void __fastcall AfterConstruction();
	__fastcall virtual ~TSOAPDOMProcessor();
public:
	/* TComponent.Create */ inline __fastcall virtual TSOAPDOMProcessor(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	
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


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Soapdomconv */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_SOAPDOMCONV)
using namespace Soap::Soapdomconv;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_SoapdomconvHPP
