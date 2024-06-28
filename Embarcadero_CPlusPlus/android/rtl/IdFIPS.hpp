// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFIPS.pas' rev: 34.00 (Android)

#ifndef IdfipsHPP
#define IdfipsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdException.hpp>
#include <IdGlobal.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idfips
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIdFIPSAlgorithmNotAllowed;
//-- type declarations -------------------------------------------------------
typedef void * TIdHashIntCtx;

typedef void * TIdHMACIntCtx;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdFIPSAlgorithmNotAllowed : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFIPSAlgorithmNotAllowed(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFIPSAlgorithmNotAllowed(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFIPSAlgorithmNotAllowed(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFIPSAlgorithmNotAllowed(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFIPSAlgorithmNotAllowed(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFIPSAlgorithmNotAllowed(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFIPSAlgorithmNotAllowed(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFIPSAlgorithmNotAllowed(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFIPSAlgorithmNotAllowed(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFIPSAlgorithmNotAllowed(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFIPSAlgorithmNotAllowed(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFIPSAlgorithmNotAllowed(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFIPSAlgorithmNotAllowed() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef bool __fastcall (*TGetFIPSMode)(void);

typedef bool __fastcall (*TSetFIPSMode)(const bool AMode);

typedef bool __fastcall (*TIsHashingIntfAvail)(void);

typedef void * __fastcall (*TGetHashInst)(void);

typedef void __fastcall (*TUpdateHashInst)(void * ACtx, const Idglobal::TIdBytes AIn);

typedef Idglobal::TIdBytes __fastcall (*TFinalHashInst)(void * ACtx);

typedef bool __fastcall (*TIsHMACAvail)(void);

typedef bool __fastcall (*TIsHMACIntfAvail)(void);

typedef void * __fastcall (*TGetHMACInst)(const Idglobal::TIdBytes AKey);

typedef void __fastcall (*TUpdateHMACInst)(void * ACtx, const Idglobal::TIdBytes AIn);

typedef Idglobal::TIdBytes __fastcall (*TFinalHMACInst)(void * ACtx);

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TGetFIPSMode GetFIPSMode;
extern DELPHI_PACKAGE TSetFIPSMode SetFIPSMode;
extern DELPHI_PACKAGE TIsHashingIntfAvail IsHashingIntfAvail;
extern DELPHI_PACKAGE TGetHashInst GetMD2HashInst;
extern DELPHI_PACKAGE TIsHashingIntfAvail IsMD2HashIntfAvail;
extern DELPHI_PACKAGE TGetHashInst GetMD4HashInst;
extern DELPHI_PACKAGE TIsHashingIntfAvail IsMD4HashIntfAvail;
extern DELPHI_PACKAGE TGetHashInst GetMD5HashInst;
extern DELPHI_PACKAGE TIsHashingIntfAvail IsMD5HashIntfAvail;
extern DELPHI_PACKAGE TGetHashInst GetSHA1HashInst;
extern DELPHI_PACKAGE TIsHashingIntfAvail IsSHA1HashIntfAvail;
extern DELPHI_PACKAGE TGetHashInst GetSHA224HashInst;
extern DELPHI_PACKAGE TIsHashingIntfAvail IsSHA224HashIntfAvail;
extern DELPHI_PACKAGE TGetHashInst GetSHA256HashInst;
extern DELPHI_PACKAGE TIsHashingIntfAvail IsSHA256HashIntfAvail;
extern DELPHI_PACKAGE TGetHashInst GetSHA384HashInst;
extern DELPHI_PACKAGE TIsHashingIntfAvail IsSHA384HashIntfAvail;
extern DELPHI_PACKAGE TGetHashInst GetSHA512HashInst;
extern DELPHI_PACKAGE TIsHashingIntfAvail IsSHA512HashIntfAvail;
extern DELPHI_PACKAGE TUpdateHashInst UpdateHashInst;
extern DELPHI_PACKAGE TFinalHashInst FinalHashInst;
extern DELPHI_PACKAGE TIsHMACAvail IsHMACAvail;
extern DELPHI_PACKAGE TIsHMACIntfAvail IsHMACMD5Avail;
extern DELPHI_PACKAGE TGetHMACInst GetHMACMD5HashInst;
extern DELPHI_PACKAGE TIsHMACIntfAvail IsHMACSHA1Avail;
extern DELPHI_PACKAGE TGetHMACInst GetHMACSHA1HashInst;
extern DELPHI_PACKAGE TIsHMACIntfAvail IsHMACSHA224Avail;
extern DELPHI_PACKAGE TGetHMACInst GetHMACSHA224HashInst;
extern DELPHI_PACKAGE TIsHMACIntfAvail IsHMACSHA256Avail;
extern DELPHI_PACKAGE TGetHMACInst GetHMACSHA256HashInst;
extern DELPHI_PACKAGE TIsHMACIntfAvail IsHMACSHA384Avail;
extern DELPHI_PACKAGE TGetHMACInst GetHMACSHA384HashInst;
extern DELPHI_PACKAGE TIsHMACIntfAvail IsHMACSHA512Avail;
extern DELPHI_PACKAGE TGetHMACInst GetHMACSHA512HashInst;
extern DELPHI_PACKAGE TUpdateHMACInst UpdateHMACInst;
extern DELPHI_PACKAGE TFinalHMACInst FinalHMACInst;
extern DELPHI_PACKAGE void __fastcall CheckMD2Permitted(void);
extern DELPHI_PACKAGE void __fastcall CheckMD4Permitted(void);
extern DELPHI_PACKAGE void __fastcall CheckMD5Permitted(void);
extern DELPHI_PACKAGE void __fastcall FIPSAlgorithmNotAllowed(const System::UnicodeString AAlgorithm);
}	/* namespace Idfips */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFIPS)
using namespace Idfips;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdfipsHPP
