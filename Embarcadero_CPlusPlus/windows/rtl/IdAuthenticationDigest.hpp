// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdAuthenticationDigest.pas' rev: 34.00 (Windows)

#ifndef IdauthenticationdigestHPP
#define IdauthenticationdigestHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAuthentication.hpp>
#include <IdException.hpp>
#include <IdGlobal.hpp>
#include <IdHashMessageDigest.hpp>
#include <IdHeaderList.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "IdAuthenticationDigest"

namespace Idauthenticationdigest
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIdInvalidAlgorithm;
class DELPHICLASS TIdDigestAuthentication;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdInvalidAlgorithm : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdInvalidAlgorithm(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdInvalidAlgorithm(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdInvalidAlgorithm(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdInvalidAlgorithm(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdInvalidAlgorithm(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdInvalidAlgorithm(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdInvalidAlgorithm(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdInvalidAlgorithm(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdInvalidAlgorithm(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdInvalidAlgorithm(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdInvalidAlgorithm(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdInvalidAlgorithm(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdInvalidAlgorithm() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdDigestAuthentication : public Idauthentication::TIdAuthentication
{
	typedef Idauthentication::TIdAuthentication inherited;
	
protected:
	System::UnicodeString FRealm;
	bool FStale;
	System::UnicodeString FOpaque;
	System::Classes::TStringList* FDomain;
	System::UnicodeString FNonce;
	int FNonceCount;
	System::UnicodeString FAlgorithm;
	System::UnicodeString FMethod;
	System::UnicodeString FUri;
	System::UnicodeString FEntityBody;
	System::Classes::TStringList* FQopOptions;
	System::Classes::TStringList* FOther;
	virtual Idauthentication::TIdAuthWhatsNext __fastcall DoNext();
	virtual int __fastcall GetSteps();
	
public:
	__fastcall virtual TIdDigestAuthentication();
	__fastcall virtual ~TIdDigestAuthentication();
	virtual System::UnicodeString __fastcall Authentication();
	virtual void __fastcall SetRequest(const System::UnicodeString AMethod, const System::UnicodeString AUri);
	__property System::UnicodeString Method = {read=FMethod, write=FMethod};
	__property System::UnicodeString Uri = {read=FUri, write=FUri};
	__property System::UnicodeString EntityBody = {read=FEntityBody, write=FEntityBody};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idauthenticationdigest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDAUTHENTICATIONDIGEST)
using namespace Idauthenticationdigest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdauthenticationdigestHPP
