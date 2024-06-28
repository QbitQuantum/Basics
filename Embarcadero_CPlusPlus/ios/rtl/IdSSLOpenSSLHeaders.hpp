// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSSLOpenSSLHeaders.pas' rev: 34.00 (iOS)

#ifndef IdsslopensslheadersHPP
#define IdsslopensslheadersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdException.hpp>
#include <IdGlobal.hpp>
#include <Posix.SysSocket.hpp>
#include <Posix.SysTime.hpp>
#include <Posix.SysTypes.hpp>
#include <System.SysUtils.hpp>
#include <IdCTypes.hpp>
#include <Posix.StdDef.hpp>

//-- user supplied -----------------------------------------------------------
#include <time.h>
namespace Idsslopensslheaders
{
	struct SSL;
	typedef SSL* PSSL;
	struct SSL_CTX;
	typedef SSL_CTX* PSSL_CTX;
	struct SSL_METHOD;
	typedef SSL_METHOD* PSSL_METHOD;
	struct X509;
	typedef X509* PX509;
	struct X509_NAME;
	typedef X509_NAME* PX509_NAME;
}
struct RSA;
typedef RSA* PRSA;
struct DSA;
typedef DSA* PDSA;
struct DH;
typedef DH* PDH;
typedef void* PEC_KEY;

namespace Idsslopensslheaders
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIdOpenSSLError;
class DELPHICLASS EIdOpenSSLAPISSLError;
class DELPHICLASS EIdOpenSSLAPICryptoError;
class DELPHICLASS EIdOSSLUnderlyingCryptoError;
class DELPHICLASS EIdDigestError;
class DELPHICLASS EIdDigestFinalEx;
class DELPHICLASS EIdDigestInitEx;
class DELPHICLASS EIdDigestUpdate;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION EIdOpenSSLError : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdOpenSSLError(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdOpenSSLError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdOpenSSLError(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdOpenSSLError(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdOpenSSLError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdOpenSSLError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdOpenSSLError(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdOpenSSLError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdOpenSSLError(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdOpenSSLError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdOpenSSLError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdOpenSSLError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdOpenSSLError() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TIdOpenSSLAPISSLError);

class PASCALIMPLEMENTATION EIdOpenSSLAPISSLError : public EIdOpenSSLError
{
	typedef EIdOpenSSLError inherited;
	
protected:
	int FErrorCode;
	int FRetCode;
	
public:
	__classmethod void __fastcall RaiseException(void * ASSL, const int ARetCode, const System::UnicodeString AMsg = System::UnicodeString());
	__classmethod void __fastcall RaiseExceptionCode(const int AErrCode, const int ARetCode, const System::UnicodeString AMsg = System::UnicodeString());
	__property int ErrorCode = {read=FErrorCode, nodefault};
	__property int RetCode = {read=FRetCode, nodefault};
public:
	/* EIdException.Create */ inline __fastcall virtual EIdOpenSSLAPISSLError(const System::UnicodeString AMsg)/* overload */ : EIdOpenSSLError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdOpenSSLAPISSLError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdOpenSSLError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdOpenSSLAPISSLError(NativeUInt Ident)/* overload */ : EIdOpenSSLError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdOpenSSLAPISSLError(System::PResStringRec ResStringRec)/* overload */ : EIdOpenSSLError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdOpenSSLAPISSLError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdOpenSSLError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdOpenSSLAPISSLError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdOpenSSLError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdOpenSSLAPISSLError(const System::UnicodeString Msg, int AHelpContext) : EIdOpenSSLError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdOpenSSLAPISSLError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdOpenSSLError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdOpenSSLAPISSLError(NativeUInt Ident, int AHelpContext)/* overload */ : EIdOpenSSLError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdOpenSSLAPISSLError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdOpenSSLError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdOpenSSLAPISSLError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdOpenSSLError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdOpenSSLAPISSLError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdOpenSSLError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdOpenSSLAPISSLError() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TIdOpenSSLAPICryptoError);

class PASCALIMPLEMENTATION EIdOpenSSLAPICryptoError : public EIdOpenSSLError
{
	typedef EIdOpenSSLError inherited;
	
protected:
	unsigned long FErrorCode;
	
public:
	__classmethod void __fastcall RaiseExceptionCode(const unsigned long AErrCode, const System::UnicodeString AMsg = System::UnicodeString());
	__classmethod void __fastcall RaiseException(const System::UnicodeString AMsg = System::UnicodeString());
	__property unsigned long ErrorCode = {read=FErrorCode};
public:
	/* EIdException.Create */ inline __fastcall virtual EIdOpenSSLAPICryptoError(const System::UnicodeString AMsg)/* overload */ : EIdOpenSSLError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdOpenSSLAPICryptoError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdOpenSSLError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdOpenSSLAPICryptoError(NativeUInt Ident)/* overload */ : EIdOpenSSLError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdOpenSSLAPICryptoError(System::PResStringRec ResStringRec)/* overload */ : EIdOpenSSLError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdOpenSSLAPICryptoError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdOpenSSLError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdOpenSSLAPICryptoError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdOpenSSLError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdOpenSSLAPICryptoError(const System::UnicodeString Msg, int AHelpContext) : EIdOpenSSLError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdOpenSSLAPICryptoError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdOpenSSLError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdOpenSSLAPICryptoError(NativeUInt Ident, int AHelpContext)/* overload */ : EIdOpenSSLError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdOpenSSLAPICryptoError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdOpenSSLError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdOpenSSLAPICryptoError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdOpenSSLError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdOpenSSLAPICryptoError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdOpenSSLError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdOpenSSLAPICryptoError() { }
	
};


class PASCALIMPLEMENTATION EIdOSSLUnderlyingCryptoError : public EIdOpenSSLAPICryptoError
{
	typedef EIdOpenSSLAPICryptoError inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdOSSLUnderlyingCryptoError(const System::UnicodeString AMsg)/* overload */ : EIdOpenSSLAPICryptoError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdOSSLUnderlyingCryptoError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdOpenSSLAPICryptoError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdOSSLUnderlyingCryptoError(NativeUInt Ident)/* overload */ : EIdOpenSSLAPICryptoError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdOSSLUnderlyingCryptoError(System::PResStringRec ResStringRec)/* overload */ : EIdOpenSSLAPICryptoError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdOSSLUnderlyingCryptoError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdOpenSSLAPICryptoError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdOSSLUnderlyingCryptoError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdOpenSSLAPICryptoError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdOSSLUnderlyingCryptoError(const System::UnicodeString Msg, int AHelpContext) : EIdOpenSSLAPICryptoError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdOSSLUnderlyingCryptoError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdOpenSSLAPICryptoError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdOSSLUnderlyingCryptoError(NativeUInt Ident, int AHelpContext)/* overload */ : EIdOpenSSLAPICryptoError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdOSSLUnderlyingCryptoError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdOpenSSLAPICryptoError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdOSSLUnderlyingCryptoError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdOpenSSLAPICryptoError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdOSSLUnderlyingCryptoError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdOpenSSLAPICryptoError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdOSSLUnderlyingCryptoError() { }
	
};


class PASCALIMPLEMENTATION EIdDigestError : public EIdOpenSSLAPICryptoError
{
	typedef EIdOpenSSLAPICryptoError inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdDigestError(const System::UnicodeString AMsg)/* overload */ : EIdOpenSSLAPICryptoError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdDigestError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdOpenSSLAPICryptoError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdDigestError(NativeUInt Ident)/* overload */ : EIdOpenSSLAPICryptoError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdDigestError(System::PResStringRec ResStringRec)/* overload */ : EIdOpenSSLAPICryptoError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdDigestError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdOpenSSLAPICryptoError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdDigestError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdOpenSSLAPICryptoError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdDigestError(const System::UnicodeString Msg, int AHelpContext) : EIdOpenSSLAPICryptoError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdDigestError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdOpenSSLAPICryptoError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdDigestError(NativeUInt Ident, int AHelpContext)/* overload */ : EIdOpenSSLAPICryptoError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdDigestError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdOpenSSLAPICryptoError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdDigestError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdOpenSSLAPICryptoError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdDigestError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdOpenSSLAPICryptoError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdDigestError() { }
	
};


class PASCALIMPLEMENTATION EIdDigestFinalEx : public EIdDigestError
{
	typedef EIdDigestError inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdDigestFinalEx(const System::UnicodeString AMsg)/* overload */ : EIdDigestError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdDigestFinalEx(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdDigestError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdDigestFinalEx(NativeUInt Ident)/* overload */ : EIdDigestError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdDigestFinalEx(System::PResStringRec ResStringRec)/* overload */ : EIdDigestError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdDigestFinalEx(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdDigestError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdDigestFinalEx(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdDigestError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdDigestFinalEx(const System::UnicodeString Msg, int AHelpContext) : EIdDigestError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdDigestFinalEx(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdDigestError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdDigestFinalEx(NativeUInt Ident, int AHelpContext)/* overload */ : EIdDigestError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdDigestFinalEx(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdDigestError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdDigestFinalEx(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdDigestError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdDigestFinalEx(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdDigestError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdDigestFinalEx() { }
	
};


class PASCALIMPLEMENTATION EIdDigestInitEx : public EIdDigestError
{
	typedef EIdDigestError inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdDigestInitEx(const System::UnicodeString AMsg)/* overload */ : EIdDigestError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdDigestInitEx(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdDigestError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdDigestInitEx(NativeUInt Ident)/* overload */ : EIdDigestError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdDigestInitEx(System::PResStringRec ResStringRec)/* overload */ : EIdDigestError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdDigestInitEx(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdDigestError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdDigestInitEx(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdDigestError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdDigestInitEx(const System::UnicodeString Msg, int AHelpContext) : EIdDigestError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdDigestInitEx(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdDigestError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdDigestInitEx(NativeUInt Ident, int AHelpContext)/* overload */ : EIdDigestError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdDigestInitEx(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdDigestError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdDigestInitEx(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdDigestError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdDigestInitEx(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdDigestError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdDigestInitEx() { }
	
};


class PASCALIMPLEMENTATION EIdDigestUpdate : public EIdDigestError
{
	typedef EIdDigestError inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdDigestUpdate(const System::UnicodeString AMsg)/* overload */ : EIdDigestError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdDigestUpdate(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdDigestError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdDigestUpdate(NativeUInt Ident)/* overload */ : EIdDigestError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdDigestUpdate(System::PResStringRec ResStringRec)/* overload */ : EIdDigestError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdDigestUpdate(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdDigestError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdDigestUpdate(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdDigestError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdDigestUpdate(const System::UnicodeString Msg, int AHelpContext) : EIdDigestError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdDigestUpdate(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdDigestError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdDigestUpdate(NativeUInt Ident, int AHelpContext)/* overload */ : EIdDigestError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdDigestUpdate(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdDigestError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdDigestUpdate(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdDigestError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdDigestUpdate(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdDigestError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdDigestUpdate() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall IsOpenSSL_1x(void);
extern DELPHI_PACKAGE bool __fastcall IsOpenSSL_SSLv2_Available(void);
extern DELPHI_PACKAGE bool __fastcall IsOpenSSL_SSLv3_Available(void);
extern DELPHI_PACKAGE bool __fastcall IsOpenSSL_SSLv23_Available(void);
extern DELPHI_PACKAGE bool __fastcall IsOpenSSL_TLSv1_0_Available(void);
extern DELPHI_PACKAGE bool __fastcall IsOpenSSL_TLSv1_1_Available(void);
extern DELPHI_PACKAGE bool __fastcall IsOpenSSL_TLSv1_2_Available(void);
extern DELPHI_PACKAGE bool __fastcall IsOpenSSL_DTLSv1_Available(void);
extern DELPHI_PACKAGE bool __fastcall Load(void);
extern DELPHI_PACKAGE void __fastcall Unload(void);
extern DELPHI_PACKAGE void __fastcall InitializeRandom(void);
extern DELPHI_PACKAGE void __fastcall CleanupRandom(void);
extern DELPHI_PACKAGE void __fastcall RAND_cleanup(void);
extern DELPHI_PACKAGE int __fastcall RAND_bytes(char * buf, int num);
extern DELPHI_PACKAGE int __fastcall RAND_pseudo_bytes(char * buf, int num);
extern DELPHI_PACKAGE void __fastcall RAND_seed(char * buf, int num);
extern DELPHI_PACKAGE void __fastcall RAND_add(char * buf, int num, int entropy);
extern DELPHI_PACKAGE int __fastcall RAND_status(void);
}	/* namespace Idsslopensslheaders */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSSLOPENSSLHEADERS)
using namespace Idsslopensslheaders;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsslopensslheadersHPP
