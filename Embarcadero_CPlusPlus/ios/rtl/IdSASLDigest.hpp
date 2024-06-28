// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSASLDigest.pas' rev: 34.00 (iOS)

#ifndef IdsasldigestHPP
#define IdsasldigestHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <IdSASL.hpp>
#include <IdSASLUserPass.hpp>
#include <IdUserPassProvider.hpp>
#include <IdException.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsasldigest
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSASLDigest;
class DELPHICLASS EIdSASLDigestException;
class DELPHICLASS EIdSASLDigestChallException;
class DELPHICLASS EIdSASLDigestChallNoAlgorithm;
class DELPHICLASS EIdSASLDigestChallInvalidAlg;
class DELPHICLASS EIdSASLDigestAuthConfNotSupported;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdSASLDigest : public Idsasluserpass::TIdSASLUserPass
{
	typedef Idsasluserpass::TIdSASLUserPass inherited;
	
protected:
	System::UnicodeString Fauthzid;
	
public:
	virtual System::UnicodeString __fastcall StartAuthenticate(const System::UnicodeString AChallenge, const System::UnicodeString AHost, const System::UnicodeString AProtocolName);
	virtual System::UnicodeString __fastcall ContinueAuthenticate(const System::UnicodeString ALastResponse, const System::UnicodeString AHost, const System::UnicodeString AProtocolName);
	__classmethod virtual System::UnicodeString __fastcall ServiceName();
	virtual bool __fastcall IsReadyToStart();
	
__published:
	__property System::UnicodeString authzid = {read=Fauthzid, write=Fauthzid};
public:
	/* TIdSASL.Destroy */ inline __fastcall virtual ~TIdSASLDigest() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSASLDigest(System::Classes::TComponent* AOwner)/* overload */ : Idsasluserpass::TIdSASLUserPass(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSASLDigest()/* overload */ : Idsasluserpass::TIdSASLUserPass() { }
	
};


class PASCALIMPLEMENTATION EIdSASLDigestException : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSASLDigestException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSASLDigestException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLDigestException(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLDigestException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLDigestException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLDigestException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSASLDigestException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSASLDigestException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLDigestException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLDigestException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLDigestException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLDigestException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSASLDigestException() { }
	
};


class PASCALIMPLEMENTATION EIdSASLDigestChallException : public EIdSASLDigestException
{
	typedef EIdSASLDigestException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSASLDigestChallException(const System::UnicodeString AMsg)/* overload */ : EIdSASLDigestException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSASLDigestChallException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdSASLDigestException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLDigestChallException(NativeUInt Ident)/* overload */ : EIdSASLDigestException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLDigestChallException(System::PResStringRec ResStringRec)/* overload */ : EIdSASLDigestException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLDigestChallException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSASLDigestException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLDigestChallException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSASLDigestException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSASLDigestChallException(const System::UnicodeString Msg, int AHelpContext) : EIdSASLDigestException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSASLDigestChallException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdSASLDigestException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLDigestChallException(NativeUInt Ident, int AHelpContext)/* overload */ : EIdSASLDigestException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLDigestChallException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdSASLDigestException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLDigestChallException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSASLDigestException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLDigestChallException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSASLDigestException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSASLDigestChallException() { }
	
};


class PASCALIMPLEMENTATION EIdSASLDigestChallNoAlgorithm : public EIdSASLDigestChallException
{
	typedef EIdSASLDigestChallException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSASLDigestChallNoAlgorithm(const System::UnicodeString AMsg)/* overload */ : EIdSASLDigestChallException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSASLDigestChallNoAlgorithm(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdSASLDigestChallException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLDigestChallNoAlgorithm(NativeUInt Ident)/* overload */ : EIdSASLDigestChallException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLDigestChallNoAlgorithm(System::PResStringRec ResStringRec)/* overload */ : EIdSASLDigestChallException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLDigestChallNoAlgorithm(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSASLDigestChallException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLDigestChallNoAlgorithm(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSASLDigestChallException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSASLDigestChallNoAlgorithm(const System::UnicodeString Msg, int AHelpContext) : EIdSASLDigestChallException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSASLDigestChallNoAlgorithm(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdSASLDigestChallException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLDigestChallNoAlgorithm(NativeUInt Ident, int AHelpContext)/* overload */ : EIdSASLDigestChallException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLDigestChallNoAlgorithm(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdSASLDigestChallException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLDigestChallNoAlgorithm(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSASLDigestChallException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLDigestChallNoAlgorithm(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSASLDigestChallException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSASLDigestChallNoAlgorithm() { }
	
};


class PASCALIMPLEMENTATION EIdSASLDigestChallInvalidAlg : public EIdSASLDigestChallException
{
	typedef EIdSASLDigestChallException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSASLDigestChallInvalidAlg(const System::UnicodeString AMsg)/* overload */ : EIdSASLDigestChallException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSASLDigestChallInvalidAlg(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdSASLDigestChallException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLDigestChallInvalidAlg(NativeUInt Ident)/* overload */ : EIdSASLDigestChallException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLDigestChallInvalidAlg(System::PResStringRec ResStringRec)/* overload */ : EIdSASLDigestChallException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLDigestChallInvalidAlg(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSASLDigestChallException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLDigestChallInvalidAlg(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSASLDigestChallException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSASLDigestChallInvalidAlg(const System::UnicodeString Msg, int AHelpContext) : EIdSASLDigestChallException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSASLDigestChallInvalidAlg(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdSASLDigestChallException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLDigestChallInvalidAlg(NativeUInt Ident, int AHelpContext)/* overload */ : EIdSASLDigestChallException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLDigestChallInvalidAlg(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdSASLDigestChallException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLDigestChallInvalidAlg(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSASLDigestChallException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLDigestChallInvalidAlg(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSASLDigestChallException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSASLDigestChallInvalidAlg() { }
	
};


class PASCALIMPLEMENTATION EIdSASLDigestAuthConfNotSupported : public EIdSASLDigestException
{
	typedef EIdSASLDigestException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSASLDigestAuthConfNotSupported(const System::UnicodeString AMsg)/* overload */ : EIdSASLDigestException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSASLDigestAuthConfNotSupported(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdSASLDigestException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLDigestAuthConfNotSupported(NativeUInt Ident)/* overload */ : EIdSASLDigestException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLDigestAuthConfNotSupported(System::PResStringRec ResStringRec)/* overload */ : EIdSASLDigestException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLDigestAuthConfNotSupported(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSASLDigestException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLDigestAuthConfNotSupported(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSASLDigestException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSASLDigestAuthConfNotSupported(const System::UnicodeString Msg, int AHelpContext) : EIdSASLDigestException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSASLDigestAuthConfNotSupported(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdSASLDigestException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLDigestAuthConfNotSupported(NativeUInt Ident, int AHelpContext)/* overload */ : EIdSASLDigestException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLDigestAuthConfNotSupported(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdSASLDigestException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLDigestAuthConfNotSupported(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSASLDigestException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLDigestAuthConfNotSupported(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSASLDigestException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSASLDigestAuthConfNotSupported() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString __fastcall CalcDigestResponse(const System::UnicodeString AUserName, const System::UnicodeString APassword, const System::UnicodeString ARealm, const System::UnicodeString ANonce, const System::UnicodeString ACNonce, const int ANC, const System::UnicodeString AQop, const System::UnicodeString ADigestURI, const System::UnicodeString AAuthzid = System::UnicodeString());
}	/* namespace Idsasldigest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSASLDIGEST)
using namespace Idsasldigest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsasldigestHPP
