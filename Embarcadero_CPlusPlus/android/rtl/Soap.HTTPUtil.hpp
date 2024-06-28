// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.HTTPUtil.pas' rev: 34.00 (Android)

#ifndef Soap_HttputilHPP
#define Soap_HttputilHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <Soap.WSDLIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Httputil
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Soap::Wsdlintf::_di_IStreamLoader __fastcall GetDefaultStreamLoader(void);
extern DELPHI_PACKAGE bool __fastcall StartsWith(const System::UnicodeString str, const System::UnicodeString sub);
extern DELPHI_PACKAGE int __fastcall FirstDelimiter(const System::UnicodeString delimiters, const System::UnicodeString Str)/* overload */;
extern DELPHI_PACKAGE int __fastcall FirstDelimiter(const System::WideString delimiters, const System::WideString Str)/* overload */;
extern DELPHI_PACKAGE Soap::Wsdlintf::_di_IStringTokenizer __fastcall StringTokenizer(const System::UnicodeString str, const System::UnicodeString delim);
extern DELPHI_PACKAGE System::TArray__1<System::UnicodeString> __fastcall StringToStringArray(const System::UnicodeString str, const System::UnicodeString delim);
extern DELPHI_PACKAGE System::UnicodeString __fastcall HTMLEscape(const System::UnicodeString Str);
}	/* namespace Httputil */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_HTTPUTIL)
using namespace Soap::Httputil;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_HttputilHPP
