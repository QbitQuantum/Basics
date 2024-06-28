// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdOTPCalculator.pas' rev: 34.00 (Android)

#ifndef IdotpcalculatorHPP
#define IdotpcalculatorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdException.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idotpcalculator
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdOTPCalculator;
class DELPHICLASS EIdOTPError;
class DELPHICLASS EIdOTPUnknownMethod;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdOTPCalculator : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod __int64 __fastcall GenerateKeyMD4(const System::UnicodeString ASeed, const System::UnicodeString APassword, const int ACount);
	__classmethod __int64 __fastcall GenerateKeyMD5(const System::UnicodeString ASeed, const System::UnicodeString APassword, const int ACount);
	__classmethod __int64 __fastcall GenerateKeySHA1(const System::UnicodeString ASeed, const System::UnicodeString APassword, const int ACount);
	__classmethod bool __fastcall GenerateSixWordKey(const System::UnicodeString AStr, const System::UnicodeString APassword, System::UnicodeString &VKey)/* overload */;
	__classmethod System::UnicodeString __fastcall GenerateSixWordKey(const System::UnicodeString AMethod, const System::UnicodeString ASeed, const System::UnicodeString APassword, const int ACount)/* overload */;
	__classmethod bool __fastcall IsValidOTPString(const System::UnicodeString AStr);
	__classmethod System::UnicodeString __fastcall ToHex(const __int64 AKey);
	__classmethod System::UnicodeString __fastcall ToSixWordFormat(const __int64 AKey);
public:
	/* TObject.Create */ inline __fastcall TIdOTPCalculator() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdOTPCalculator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdOTPError : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdOTPError(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdOTPError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdOTPError(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdOTPError(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdOTPError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdOTPError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdOTPError(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdOTPError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdOTPError(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdOTPError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdOTPError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdOTPError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdOTPError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdOTPUnknownMethod : public EIdOTPError
{
	typedef EIdOTPError inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdOTPUnknownMethod(const System::UnicodeString AMsg)/* overload */ : EIdOTPError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdOTPUnknownMethod(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdOTPError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdOTPUnknownMethod(NativeUInt Ident)/* overload */ : EIdOTPError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdOTPUnknownMethod(System::PResStringRec ResStringRec)/* overload */ : EIdOTPError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdOTPUnknownMethod(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdOTPError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdOTPUnknownMethod(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdOTPError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdOTPUnknownMethod(const System::UnicodeString Msg, int AHelpContext) : EIdOTPError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdOTPUnknownMethod(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdOTPError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdOTPUnknownMethod(NativeUInt Ident, int AHelpContext)/* overload */ : EIdOTPError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdOTPUnknownMethod(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdOTPError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdOTPUnknownMethod(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdOTPError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdOTPUnknownMethod(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdOTPError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdOTPUnknownMethod() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idotpcalculator */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDOTPCALCULATOR)
using namespace Idotpcalculator;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdotpcalculatorHPP
