// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.TypeTrans.pas' rev: 34.00 (Windows)

#ifndef Soap_TypetransHPP
#define Soap_TypetransHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.TypInfo.hpp>
#include <System.SysUtils.hpp>
#include <Soap.InvokeRegistry.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Typetrans
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTypeTranslator;
class DELPHICLASS ETypeTransException;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTypeTranslator : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall TTypeTranslator();
	__fastcall virtual ~TTypeTranslator();
	bool __fastcall CastSoapToNative(System::Typinfo::PTypeInfo Info, const System::UnicodeString SoapData, void * NatData, bool IsNull);
	void __fastcall CastNativeToSoap(System::Typinfo::PTypeInfo Info, System::UnicodeString &SoapData, void * NatData, bool &IsNull);
	void __fastcall CastSoapToVariant(System::Typinfo::PTypeInfo SoapInfo, const System::UnicodeString SoapData, void * NatData)/* overload */;
	System::Variant __fastcall CastSoapToVariant(System::Typinfo::PTypeInfo SoapInfo, const System::UnicodeString SoapData)/* overload */;
	void __fastcall Base64ToVar(void * NatData, const System::UnicodeString SoapData)/* overload */;
	void __fastcall Base64ToVar(System::Variant &V, const System::UnicodeString SoapData)/* overload */;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ETypeTransException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ETypeTransException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ETypeTransException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ETypeTransException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ETypeTransException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ETypeTransException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ETypeTransException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ETypeTransException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ETypeTransException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETypeTransException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETypeTransException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETypeTransException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETypeTransException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ETypeTransException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TTypeTranslator* TypeTranslator;
extern DELPHI_PACKAGE int __fastcall GetEnumValueEx _DEPRECATED_ATTRIBUTE0 (System::Typinfo::PTypeInfo TypInfo, const System::UnicodeString Name);
extern DELPHI_PACKAGE void __fastcall SetEnumPropEx _DEPRECATED_ATTRIBUTE0 (System::TObject* Instance, System::Typinfo::PPropInfo PropInfo, const System::UnicodeString Value);
extern DELPHI_PACKAGE int __fastcall GetEnumValueExW(System::Typinfo::PTypeInfo TypInfo, const System::UnicodeString Name);
extern DELPHI_PACKAGE void __fastcall SetEnumPropExW(System::TObject* Instance, System::Typinfo::PPropInfo PropInfo, const System::UnicodeString Value);
extern DELPHI_PACKAGE System::Extended __fastcall StrToFloatEx(const System::UnicodeString S);
extern DELPHI_PACKAGE System::UnicodeString __fastcall FloatToStrEx(System::Extended Value);
}	/* namespace Typetrans */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_TYPETRANS)
using namespace Soap::Typetrans;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_TypetransHPP
