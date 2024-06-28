// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.OPToSOAPDomCustom.pas' rev: 34.00 (Windows)

#ifndef Soap_OptosoapdomcustomHPP
#define Soap_OptosoapdomcustomHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.TypInfo.hpp>
#include <Soap.IntfInfo.hpp>
#include <Soap.InvokeRegistry.hpp>
#include <Xml.XMLIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Optosoapdomcustom
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE ICustomConvert;
typedef System::DelphiInterface<ICustomConvert> _di_ICustomConvert;
struct TConverterEntry;
class DELPHICLASS TOPToSoapDomCustomRegistry;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{96832CB3-BC12-4C45-B482-26F7160EDE51}") ICustomConvert  : public System::IInterface 
{
	virtual void __fastcall ConvertSoapParamToNative(Soap::Intfinfo::PIntfMethEntry MethMD, Soap::Invokeregistry::TInvContext* InvContext, int ArgCount, Xml::Xmlintf::_di_IXMLNode Node) = 0 ;
	virtual void __fastcall ConvertNativeParamToSoap(Xml::Xmlintf::_di_IXMLNode Node, System::UnicodeString Name, System::Typinfo::PTypeInfo Info, void * P) = 0 ;
};

struct DECLSPEC_DRECORD TConverterEntry
{
public:
	_di_ICustomConvert Converter;
	System::TClass AClass;
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOPToSoapDomCustomRegistry : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<TConverterEntry> _TOPToSoapDomCustomRegistry__1;
	
	
private:
	_TOPToSoapDomCustomRegistry__1 FConverters;
	
public:
	void __fastcall RegisterCustomConverter(System::TClass AClass, System::UnicodeString URI, System::UnicodeString TypeName, _di_ICustomConvert Converter);
	_di_ICustomConvert __fastcall GetConverter(System::TClass AClass);
public:
	/* TObject.Create */ inline __fastcall TOPToSoapDomCustomRegistry() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TOPToSoapDomCustomRegistry() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TOPToSoapDomCustomRegistry* ConverterRegistry;
}	/* namespace Optosoapdomcustom */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_OPTOSOAPDOMCUSTOM)
using namespace Soap::Optosoapdomcustom;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_OptosoapdomcustomHPP
