// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXOpenSSL.pas' rev: 34.00 (Android)

#ifndef Data_DbxopensslHPP
#define Data_DbxopensslHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXPlatform.hpp>
#include <Data.DBXTransport.hpp>
#include <System.SysUtils.hpp>
#include <IPPeerAPI.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxopenssl
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TRSACypher;
class DELPHICLASS TRSAFilter;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TKeyUsagePolicy : unsigned char { kupUseGlobalKey, kupUseLocalKey };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TRSACypher : /*[[sealed]]*/ public System::TObject
{
	typedef System::TObject inherited;
	
private:
	void *FLocalKey;
	void *FConfederatedKey;
	TKeyUsagePolicy FKeyUsagePolicy;
	static void *GLOBAL_RSA_KEY;
	static bool OPEN_SSL_LOADED;
	static bool OPEN_SSL_LOAD_STATUS;
	static System::UnicodeString ERR_LOAD;
	static System::TObject* KEY_MONITOR;
	static Ippeerapi::_di_IIPPeerProcs FIPPeerProcs;
	static System::UnicodeString FIPImplementationID;
	
private:
	__classmethod void __fastcall Init();
	__classmethod void __fastcall Clear();
	__classmethod Ippeerapi::_di_IIPPeerProcs __fastcall IPPeerProcs();
	__classmethod void __fastcall GenerateRSAKey(int keyLength, int Exponent, System::TObject* Monitor, void * &Key);
	void * __fastcall GetPrivateKey();
	System::TObject* __fastcall GetSynchMonitor();
	
protected:
	__classmethod System::UnicodeString __fastcall SSLErrorMessage();
	__classmethod void __fastcall ClearKey(void * &AKey);
	
public:
	void __fastcall InitSSLIPImplementationID(const System::UnicodeString AIPImplementationID);
	__classmethod bool __fastcall LoadSSL()/* overload */;
#ifndef __aarch64__
	__classmethod bool __fastcall LoadSSLAndCreateKey(int keyLength = 0x400, __int64 Exponent = 3LL)/* overload */;
#else /* __aarch64__ */
	__classmethod bool __fastcall LoadSSLAndCreateKey(int keyLength = 0x400, __int64 Exponent = (__int64)(3LL))/* overload */;
#endif /* __aarch64__ */
	__classmethod System::UnicodeString __fastcall ErrorLoad();
#ifndef __aarch64__
	__classmethod void __fastcall GenerateGlobalKey(int keyLength = 0x400, __int64 Exponent = 3LL);
#else /* __aarch64__ */
	__classmethod void __fastcall GenerateGlobalKey(int keyLength = 0x400, __int64 Exponent = (__int64)(3LL));
#endif /* __aarch64__ */
	__fastcall TRSACypher()/* overload */;
	__fastcall TRSACypher(TKeyUsagePolicy KeyUsagePolicy)/* overload */;
	__fastcall virtual ~TRSACypher();
#ifndef __aarch64__
	void __fastcall GenerateKey(int keyLength = 0x400, __int64 Exponent = 3LL);
#else /* __aarch64__ */
	void __fastcall GenerateKey(int keyLength = 0x400, __int64 Exponent = (__int64)(3LL));
#endif /* __aarch64__ */
	System::TArray__1<System::Byte> __fastcall GetPublicKey();
	void __fastcall SetConfederatePublicKey(System::TArray__1<System::Byte> publicKey);
	System::TArray__1<System::Byte> __fastcall PrivateDecrypt(System::TArray__1<System::Byte> Data);
	System::TArray__1<System::Byte> __fastcall PublicEncrypt(System::TArray__1<System::Byte> Data);
	
private:
	// __classmethod void __fastcall Create_();
	// __classmethod void __fastcall Destroy_();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION DECLSPEC_DRTTI TRSAFilter : public Data::Dbxtransport::TTransportFilter
{
	typedef Data::Dbxtransport::TTransportFilter inherited;
	
private:
	bool FUseGlobalKey;
	TRSACypher* FRSACypher;
	int FKeyLength;
	__int64 FKeyExponent;
	void __fastcall InitRSA();
	
protected:
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetParameters();
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetUserParameters();
	
public:
	__fastcall virtual TRSAFilter();
	__fastcall virtual ~TRSAFilter();
	virtual System::TArray__1<System::Byte> __fastcall ProcessInput(const System::TArray__1<System::Byte> Data);
	virtual System::TArray__1<System::Byte> __fastcall ProcessOutput(const System::TArray__1<System::Byte> Data);
	virtual System::UnicodeString __fastcall Id();
	virtual bool __fastcall SetConfederateParameter(const System::UnicodeString ParamName, const System::UnicodeString ParamValue);
	virtual System::UnicodeString __fastcall GetParameterValue(const System::UnicodeString ParamName);
	virtual bool __fastcall SetParameterValue(const System::UnicodeString ParamName, const System::UnicodeString ParamValue);
	virtual bool __fastcall IsPublicKeyCryptograph();
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word RSA_KEY_LENGTH = System::Word(0x400);
static constexpr System::Int8 RSA_KEY_EXPONENT = System::Int8(0x3);
#define USE_GLOBAL u"UseGlobalKey"
#define PUBLIC_KEY u"PublicKey"
#define KEY_LENGTH u"KeyLength"
#define KEY_EXPONENT u"KeyExponent"
}	/* namespace Dbxopenssl */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXOPENSSL)
using namespace Data::Dbxopenssl;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxopensslHPP
