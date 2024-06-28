// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdHeaderCoderBase.pas' rev: 34.00 (iOS)

#ifndef IdheadercoderbaseHPP
#define IdheadercoderbaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>
#include <IdException.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idheadercoderbase
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdHeaderCoder;
class DELPHICLASS EIdHeaderEncodeError;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TIdHeaderDecodingNeededEvent)(const System::UnicodeString ACharSet, const Idglobal::TIdBytes AData, System::UnicodeString &VResult, bool &VHandled);

typedef void __fastcall (__closure *TIdHeaderEncodingNeededEvent)(const System::UnicodeString ACharSet, const System::UnicodeString AData, Idglobal::TIdBytes &VResult, bool &VHandled);

class PASCALIMPLEMENTATION TIdHeaderCoder : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Decode(const System::UnicodeString ACharSet, const Idglobal::TIdBytes AData);
	__classmethod virtual Idglobal::TIdBytes __fastcall Encode(const System::UnicodeString ACharSet, const System::UnicodeString AData);
	__classmethod virtual bool __fastcall CanHandle(const System::UnicodeString ACharSet);
public:
	/* TObject.Create */ inline __fastcall TIdHeaderCoder() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHeaderCoder() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TIdHeaderCoderClass);

class PASCALIMPLEMENTATION EIdHeaderEncodeError : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdHeaderEncodeError(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdHeaderEncodeError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdHeaderEncodeError(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdHeaderEncodeError(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdHeaderEncodeError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdHeaderEncodeError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdHeaderEncodeError(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdHeaderEncodeError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdHeaderEncodeError(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdHeaderEncodeError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdHeaderEncodeError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdHeaderEncodeError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdHeaderEncodeError() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TIdHeaderEncodingNeededEvent GHeaderEncodingNeeded;
extern DELPHI_PACKAGE TIdHeaderDecodingNeededEvent GHeaderDecodingNeeded;
extern DELPHI_PACKAGE TIdHeaderCoderClass __fastcall HeaderCoderByCharSet(const System::UnicodeString ACharSet);
extern DELPHI_PACKAGE bool __fastcall DecodeHeaderData(const System::UnicodeString ACharSet, const Idglobal::TIdBytes AData, System::UnicodeString &VResult);
extern DELPHI_PACKAGE Idglobal::TIdBytes __fastcall EncodeHeaderData(const System::UnicodeString ACharSet, const System::UnicodeString AData);
extern DELPHI_PACKAGE void __fastcall RegisterHeaderCoder(const TIdHeaderCoderClass ACoder);
extern DELPHI_PACKAGE void __fastcall UnregisterHeaderCoder(const TIdHeaderCoderClass ACoder);
}	/* namespace Idheadercoderbase */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDHEADERCODERBASE)
using namespace Idheadercoderbase;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdheadercoderbaseHPP
