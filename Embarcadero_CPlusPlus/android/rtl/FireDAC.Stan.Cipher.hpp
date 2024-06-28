// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Stan.Cipher.pas' rev: 34.00 (Android)

#ifndef Firedac_Stan_CipherHPP
#define Firedac_Stan_CipherHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Stan
{
namespace Cipher
{
//-- forward type declarations -----------------------------------------------
struct TFDDigest128;
class DELPHICLASS TFDMD5Hash;
class DELPHICLASS TFDBlockAESCryptor;
class DELPHICLASS TFDCipher;
class DELPHICLASS TFDCipherAESBase;
class DELPHICLASS TFDCipherAES;
class DELPHICLASS TFDCipherAESCTR;
class DELPHICLASS TFDCipherAESECB;
//-- type declarations -------------------------------------------------------
_DECLARE_METACLASS(System::TMetaClass, TFDCipherClass);

#pragma pack(push,1)
struct DECLSPEC_DRECORD TFDDigest128
{
public:
	unsigned A;
	unsigned B;
	unsigned C;
	unsigned D;
};
#pragma pack(pop)


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDMD5Hash : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod TFDDigest128 __fastcall Hash(System::Classes::TStream* AStream, int ACount = 0x0)/* overload */;
	__classmethod System::UnicodeString __fastcall Digest2String(const TFDDigest128 &AValue, bool ALowerCase = false);
public:
	/* TObject.Create */ inline __fastcall TFDMD5Hash() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TFDMD5Hash() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::StaticArray<System::Byte, 16> TAESBlock;

typedef TAESBlock *PAESBlock;

typedef System::StaticArray<System::Byte, 16> TAESKey128;

typedef System::StaticArray<System::Byte, 25> TAESKey192;

typedef System::StaticArray<System::Byte, 33> TAESKey256;

typedef System::StaticArray<unsigned, 4> TRoundKey;

typedef System::StaticArray<System::StaticArray<unsigned, 4>, 15> TKeyArray;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDBlockAESCryptor : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TKeyArray FRK;
	unsigned FRounds;
	bool FInitialized;
	
protected:
	bool __fastcall EncryptInit(const void *AKey, unsigned AKeySize);
	bool __fastcall DecryptInit(const void *AKey, unsigned AKeySize);
	
public:
	void __fastcall Encrypt(const TAESBlock &BI, TAESBlock &BO)/* overload */;
	void __fastcall Decrypt(const TAESBlock &BI, TAESBlock &BO)/* overload */;
	void __fastcall Encrypt(TAESBlock &B)/* overload */;
	void __fastcall Decrypt(TAESBlock &B)/* overload */;
	bool __fastcall Initialize(const void *AKey, unsigned AKeySize, bool AEncrypt);
public:
	/* TObject.Create */ inline __fastcall TFDBlockAESCryptor() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TFDBlockAESCryptor() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDCipher : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual void __fastcall Finalize() = 0 ;
	
public:
	__classmethod virtual unsigned __fastcall ReserveLength();
	virtual void __fastcall Initialize(System::PByte aKeyMaterial, int aKeyLength, const TAESBlock &aSalt, int aSaltLength, System::Word aKeySize) = 0 ;
	virtual int __fastcall Process(PAESBlock ApIn, PAESBlock ApOut, int ACount, unsigned APageNum, bool AEncrypt) = 0 ;
	__fastcall virtual ~TFDCipher();
public:
	/* TObject.Create */ inline __fastcall TFDCipher() : System::TObject() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDCipherAESBase : public TFDCipher
{
	typedef TFDCipher inherited;
	
private:
	TFDBlockAESCryptor* fEncryptor;
	TFDBlockAESCryptor* fMac;
	TFDBlockAESCryptor* fIV;
	TAESBlock fIVSeed;
	void __fastcall BCC(TFDBlockAESCryptor* aCryptor, System::Classes::TMemoryStream* aSrc, TAESBlock &aDst);
	void __fastcall KDF128(System::PByte aKeyMaterial, int aKeyLength, System::WideChar aLabel, const TAESBlock &aSalt, TAESKey128 &aKey);
	void __fastcall KDF192(System::PByte aKeyMaterial, int aKeyLength, System::WideChar aLabel, const TAESBlock &aSalt, TAESKey192 &aKey);
	void __fastcall KDF256(System::PByte aKeyMaterial, int aKeyLength, System::WideChar aLabel, const TAESBlock &aSalt, TAESKey256 &aKey);
	int __fastcall GenerateIV(/* out */ TAESBlock &aIV);
	
protected:
	virtual void __fastcall Finalize();
public:
	/* TFDCipher.Destroy */ inline __fastcall virtual ~TFDCipherAESBase() { }
	
public:
	/* TObject.Create */ inline __fastcall TFDCipherAESBase() : TFDCipher() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDCipherAES : public TFDCipherAESBase
{
	typedef TFDCipherAESBase inherited;
	
public:
	__classmethod virtual unsigned __fastcall ReserveLength();
	virtual void __fastcall Initialize(System::PByte aKeyMaterial, int aKeyLength, const TAESBlock &aSalt, int aSaltLength, System::Word aKeySize);
	virtual int __fastcall Process(PAESBlock ApIn, PAESBlock ApOut, int ACount, unsigned APageNum, bool AEncrypt);
public:
	/* TFDCipher.Destroy */ inline __fastcall virtual ~TFDCipherAES() { }
	
public:
	/* TObject.Create */ inline __fastcall TFDCipherAES() : TFDCipherAESBase() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDCipherAESCTR : public TFDCipherAESBase
{
	typedef TFDCipherAESBase inherited;
	
public:
	__classmethod virtual unsigned __fastcall ReserveLength();
	virtual void __fastcall Initialize(System::PByte aKeyMaterial, int aKeyLength, const TAESBlock &aSalt, int aSaltLength, System::Word aKeySize);
	virtual int __fastcall Process(PAESBlock ApIn, PAESBlock ApOut, int ACount, unsigned APageNum, bool AEncrypt);
public:
	/* TFDCipher.Destroy */ inline __fastcall virtual ~TFDCipherAESCTR() { }
	
public:
	/* TObject.Create */ inline __fastcall TFDCipherAESCTR() : TFDCipherAESBase() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDCipherAESECB : public TFDCipher
{
	typedef TFDCipher inherited;
	
private:
	TFDBlockAESCryptor* fEncryptor;
	TFDBlockAESCryptor* fDecryptor;
	
protected:
	virtual void __fastcall Finalize();
	
public:
	__classmethod virtual unsigned __fastcall ReserveLength();
	virtual void __fastcall Initialize(System::PByte aKeyMaterial, int aKeyLength, const TAESBlock &aSalt, int aSaltLength, System::Word aKeySize);
	virtual int __fastcall Process(PAESBlock ApIn, PAESBlock ApOut, int ACount, unsigned APageNum, bool AEncrypt);
public:
	/* TFDCipher.Destroy */ inline __fastcall virtual ~TFDCipherAESECB() { }
	
public:
	/* TObject.Create */ inline __fastcall TFDCipherAESECB() : TFDCipher() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 C_FD_AESBlockSize = System::Int8(0x10);
static constexpr System::Int8 C_FD_AESMaxRounds = System::Int8(0xe);
extern DELPHI_PACKAGE bool __fastcall FDCipherParsePassword(char * APwd, int APwdLen, /* out */ TFDCipherClass &ACipherClass, /* out */ int &AKeyLen, /* out */ int &ANameLen);
extern DELPHI_PACKAGE System::UnicodeString __fastcall FDCipherGetClasses(void);
extern DELPHI_PACKAGE char * __fastcall FDCipherGetName(TFDCipherClass ACipherClass, int AKeyLen);
}	/* namespace Cipher */
}	/* namespace Stan */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_STAN_CIPHER)
using namespace Firedac::Stan::Cipher;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_STAN)
using namespace Firedac::Stan;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Stan_CipherHPP
