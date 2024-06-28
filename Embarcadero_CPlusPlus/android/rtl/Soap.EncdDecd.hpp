// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.EncdDecd.pas' rev: 34.00 (Android)

#ifndef Soap_EncddecdHPP
#define Soap_EncddecdHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Encddecd
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall EncodeStream(System::Classes::TStream* Input, System::Classes::TStream* Output);
extern DELPHI_PACKAGE void __fastcall DecodeStream(System::Classes::TStream* Input, System::Classes::TStream* Output);
extern DELPHI_PACKAGE System::UnicodeString __fastcall EncodeString(const System::UnicodeString Input);
extern DELPHI_PACKAGE System::UnicodeString __fastcall DecodeString(const System::UnicodeString Input);
extern DELPHI_PACKAGE System::TArray__1<System::Byte> __fastcall DecodeBase64(const System::AnsiString Input);
extern DELPHI_PACKAGE System::AnsiString __fastcall EncodeBase64(const void * Input, int Size);
}	/* namespace Encddecd */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_ENCDDECD)
using namespace Soap::Encddecd;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_EncddecdHPP
