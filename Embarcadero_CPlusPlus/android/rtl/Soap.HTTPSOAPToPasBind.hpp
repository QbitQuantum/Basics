// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.HTTPSOAPToPasBind.pas' rev: 34.00 (Android)

#ifndef Soap_HttpsoaptopasbindHPP
#define Soap_HttpsoaptopasbindHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.TypInfo.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Httpsoaptopasbind
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IHTTPSOAPToPasBind;
typedef System::DelphiInterface<IHTTPSOAPToPasBind> _di_IHTTPSOAPToPasBind;
class DELPHICLASS THTTPSOAPToPasBind;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{FDA9957E-F8A1-4E46-9107-9DB7E90E0DBE}") IHTTPSOAPToPasBind  : public System::IInterface 
{
	virtual bool __fastcall BindToPascalByAction(const System::UnicodeString Action, System::TClass &AClass, System::Typinfo::PTypeInfo &IntfInfo, System::UnicodeString &AMeth) = 0 ;
	virtual bool __fastcall BindToPascalByPath(const System::UnicodeString Path, System::TClass &AClass, System::Typinfo::PTypeInfo &IntfInfo, System::UnicodeString &AMeth) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION THTTPSOAPToPasBind : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	virtual bool __fastcall BindToPascalByAction(const System::UnicodeString Action, System::TClass &AClass, System::Typinfo::PTypeInfo &IntfInfo, System::UnicodeString &AMeth);
	virtual bool __fastcall BindToPascalByPath(const System::UnicodeString Path, System::TClass &AClass, System::Typinfo::PTypeInfo &IntfInfo, System::UnicodeString &AMeth);
public:
	/* TObject.Create */ inline __fastcall THTTPSOAPToPasBind() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~THTTPSOAPToPasBind() { }
	
private:
	void *__IHTTPSOAPToPasBind;	// IHTTPSOAPToPasBind 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FDA9957E-F8A1-4E46-9107-9DB7E90E0DBE}
	operator _di_IHTTPSOAPToPasBind()
	{
		_di_IHTTPSOAPToPasBind intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IHTTPSOAPToPasBind*(void) { return (IHTTPSOAPToPasBind*)&__IHTTPSOAPToPasBind; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Httpsoaptopasbind */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_HTTPSOAPTOPASBIND)
using namespace Soap::Httpsoaptopasbind;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_HttpsoaptopasbindHPP
