// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Hash.pas' rev: 34.00 (Android)

#ifndef System_HashHPP
#define System_HashHPP

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

namespace System
{
namespace Hash
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EHashException;
struct THash;
struct THashMD5;
struct THashSHA1;
struct THashSHA2;
struct THashBobJenkins;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EHashException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EHashException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EHashException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EHashException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EHashException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EHashException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EHashException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EHashException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EHashException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EHashException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EHashException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EHashException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EHashException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EHashException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD THash
{
public:
	static int __fastcall DigestAsInteger(const System::TArray__1<System::Byte> ADigest);
	static System::UnicodeString __fastcall DigestAsString(const System::TArray__1<System::Byte> ADigest);
	static System::UnicodeString __fastcall DigestAsStringGUID(const System::TArray__1<System::Byte> ADigest);
	static System::UnicodeString __fastcall GetRandomString(const int ALen = 0xa);
	static unsigned __fastcall ToBigEndian(unsigned AValue)/* overload */;
	static unsigned __int64 __fastcall ToBigEndian(unsigned __int64 AValue)/* overload */;
};


struct DECLSPEC_DRECORD THashMD5
{
	
private:
	typedef System::StaticArray<unsigned, 16> TContextState;
	
	typedef System::StaticArray<System::Byte, 64> TContextBuffer;
	
	
private:
	TContextBuffer FPadding;
	System::StaticArray<unsigned, 4> FContextState;
	System::StaticArray<unsigned, 2> FContextCount;
	TContextBuffer FContextBuffer;
	bool FFinalized;
	void __fastcall Transform(const System::PByte ABlock, int AShift);
	void __fastcall Decode(const System::PCardinal Dst, const System::PByte Src, int Len, int AShift);
	void __fastcall Encode(const System::PByte Dst, const System::PCardinal Src, int Len);
	void __fastcall FinalizeHash();
	void __fastcall Update(const System::PByte AData, unsigned ALength)/* overload */;
	System::TArray__1<System::Byte> __fastcall GetDigest();
	
public:
	static THashMD5 __fastcall Create();
	void __fastcall Reset();
	void __fastcall Update(const void *AData, unsigned ALength)/* overload */;
	void __fastcall Update(const System::TArray__1<System::Byte> AData, unsigned ALength = (unsigned)(0x0))/* overload */;
	void __fastcall Update(const System::UnicodeString Input)/* overload */;
	int __fastcall GetBlockSize();
	int __fastcall GetHashSize();
	System::TArray__1<System::Byte> __fastcall HashAsBytes();
	System::UnicodeString __fastcall HashAsString();
	static System::TArray__1<System::Byte> __fastcall GetHashBytes(const System::UnicodeString AData)/* overload */;
	static System::UnicodeString __fastcall GetHashString(const System::UnicodeString AString)/* overload */;
	static System::TArray__1<System::Byte> __fastcall GetHashBytes(System::Classes::TStream* const AStream)/* overload */;
	static System::UnicodeString __fastcall GetHashString(System::Classes::TStream* const AStream)/* overload */;
	static System::TArray__1<System::Byte> __fastcall GetHashBytesFromFile(const System::Sysutils::TFileName AFileName);
	static System::UnicodeString __fastcall GetHashStringFromFile(const System::Sysutils::TFileName AFileName);
	static System::UnicodeString __fastcall GetHMAC(const System::UnicodeString AData, const System::UnicodeString AKey);
	static System::TArray__1<System::Byte> __fastcall GetHMACAsBytes(const System::UnicodeString AData, const System::UnicodeString AKey)/* overload */;
	static System::TArray__1<System::Byte> __fastcall GetHMACAsBytes(const System::UnicodeString AData, const System::TArray__1<System::Byte> AKey)/* overload */;
	static System::TArray__1<System::Byte> __fastcall GetHMACAsBytes(const System::TArray__1<System::Byte> AData, const System::UnicodeString AKey)/* overload */;
	static System::TArray__1<System::Byte> __fastcall GetHMACAsBytes(const System::TArray__1<System::Byte> AData, const System::TArray__1<System::Byte> AKey)/* overload */;
};


struct DECLSPEC_DRECORD THashSHA1
{
private:
	System::StaticArray<unsigned, 5> FHash;
	__int64 FBitLength;
	System::StaticArray<System::Byte, 64> FBuffer;
	int FIndex;
	bool FFinalized;
	void __fastcall Initialize();
	void __fastcall CheckFinalized();
	void __fastcall Compress();
	void __fastcall Finalize();
	System::TArray__1<System::Byte> __fastcall GetDigest();
	void __fastcall Update(const System::PByte AData, unsigned ALength)/* overload */;
	
public:
	static THashSHA1 __fastcall Create();
	void __fastcall Reset();
	void __fastcall Update(const void *AData, unsigned ALength)/* overload */;
	void __fastcall Update(const System::TArray__1<System::Byte> AData, unsigned ALength = (unsigned)(0x0))/* overload */;
	void __fastcall Update(const System::UnicodeString Input)/* overload */;
	int __fastcall GetBlockSize();
	int __fastcall GetHashSize();
	System::TArray__1<System::Byte> __fastcall HashAsBytes();
	System::UnicodeString __fastcall HashAsString();
	static System::TArray__1<System::Byte> __fastcall GetHashBytes(const System::UnicodeString AData)/* overload */;
	static System::UnicodeString __fastcall GetHashString(const System::UnicodeString AString)/* overload */;
	static System::TArray__1<System::Byte> __fastcall GetHashBytes(System::Classes::TStream* const AStream)/* overload */;
	static System::UnicodeString __fastcall GetHashString(System::Classes::TStream* const AStream)/* overload */;
	static System::TArray__1<System::Byte> __fastcall GetHashBytesFromFile(const System::Sysutils::TFileName AFileName);
	static System::UnicodeString __fastcall GetHashStringFromFile(const System::Sysutils::TFileName AFileName);
	static System::UnicodeString __fastcall GetHMAC(const System::UnicodeString AData, const System::UnicodeString AKey);
	static System::TArray__1<System::Byte> __fastcall GetHMACAsBytes(const System::UnicodeString AData, const System::UnicodeString AKey)/* overload */;
	static System::TArray__1<System::Byte> __fastcall GetHMACAsBytes(const System::UnicodeString AData, const System::TArray__1<System::Byte> AKey)/* overload */;
	static System::TArray__1<System::Byte> __fastcall GetHMACAsBytes(const System::TArray__1<System::Byte> AData, const System::UnicodeString AKey)/* overload */;
	static System::TArray__1<System::Byte> __fastcall GetHMACAsBytes(const System::TArray__1<System::Byte> AData, const System::TArray__1<System::Byte> AKey)/* overload */;
};


struct DECLSPEC_DRECORD THashSHA2
{
	
public:
	enum DECLSPEC_DENUM TSHA2Version : unsigned char { SHA224, SHA256, SHA384, SHA512, SHA512_224, SHA512_256 };
	
	
private:
	static constexpr System::Int8 CBuffer32Length = System::Int8(0x40);
	
	static constexpr System::Byte CBuffer64Length = System::Byte(0x80);
	
	System::StaticArray<System::Byte, 128> FBuffer;
	unsigned __int64 FBitLength;
	unsigned FIndex;
	bool FFinalized;
	void __fastcall Initialize(TSHA2Version AVersion);
	void __fastcall CheckFinalized();
	void __fastcall Compress();
	void __fastcall Compress32();
	void __fastcall Compress64();
	void __fastcall Finalize();
	void __fastcall Finalize32();
	void __fastcall Finalize64();
	System::TArray__1<System::Byte> __fastcall GetDigest();
	void __fastcall Update(const System::PByte AData, unsigned ALength)/* overload */;
	
public:
	static THashSHA2 __fastcall Create(TSHA2Version AHashVersion = (TSHA2Version)(0x1));
	void __fastcall Reset();
	void __fastcall Update(const void *AData, unsigned ALength)/* overload */;
	void __fastcall Update(const System::TArray__1<System::Byte> AData, unsigned ALength = (unsigned)(0x0))/* overload */;
	void __fastcall Update(const System::UnicodeString Input)/* overload */;
	int __fastcall GetBlockSize();
	int __fastcall GetHashSize();
	System::TArray__1<System::Byte> __fastcall HashAsBytes();
	System::UnicodeString __fastcall HashAsString();
	static System::TArray__1<System::Byte> __fastcall GetHashBytes(const System::UnicodeString AData, TSHA2Version AHashVersion = (TSHA2Version)(0x1))/* overload */;
	static System::UnicodeString __fastcall GetHashString(const System::UnicodeString AString, TSHA2Version AHashVersion = (TSHA2Version)(0x1))/* overload */;
	static System::TArray__1<System::Byte> __fastcall GetHashBytes(System::Classes::TStream* const AStream, TSHA2Version AHashVersion = (TSHA2Version)(0x1))/* overload */;
	static System::UnicodeString __fastcall GetHashString(System::Classes::TStream* const AStream, TSHA2Version AHashVersion = (TSHA2Version)(0x1))/* overload */;
	static System::TArray__1<System::Byte> __fastcall GetHashBytesFromFile(const System::Sysutils::TFileName AFileName, TSHA2Version AHashVersion = (TSHA2Version)(0x1));
	static System::UnicodeString __fastcall GetHashStringFromFile(const System::Sysutils::TFileName AFileName, TSHA2Version AHashVersion = (TSHA2Version)(0x1));
	static System::UnicodeString __fastcall GetHMAC(const System::UnicodeString AData, const System::UnicodeString AKey, TSHA2Version AHashVersion = (TSHA2Version)(0x1));
	static System::TArray__1<System::Byte> __fastcall GetHMACAsBytes(const System::UnicodeString AData, const System::UnicodeString AKey, TSHA2Version AHashVersion = (TSHA2Version)(0x1))/* overload */;
	static System::TArray__1<System::Byte> __fastcall GetHMACAsBytes(const System::UnicodeString AData, const System::TArray__1<System::Byte> AKey, TSHA2Version AHashVersion = (TSHA2Version)(0x1))/* overload */;
	static System::TArray__1<System::Byte> __fastcall GetHMACAsBytes(const System::TArray__1<System::Byte> AData, const System::UnicodeString AKey, TSHA2Version AHashVersion = (TSHA2Version)(0x1))/* overload */;
	static System::TArray__1<System::Byte> __fastcall GetHMACAsBytes(const System::TArray__1<System::Byte> AData, const System::TArray__1<System::Byte> AKey, TSHA2Version AHashVersion = (TSHA2Version)(0x1))/* overload */;
	
private:
	TSHA2Version FVersion;
	union
	{
		struct 
		{
			System::StaticArray<unsigned __int64, 8> FHash64;
		};
		struct 
		{
			System::StaticArray<unsigned, 8> FHash;
		};
		
	};
};


struct DECLSPEC_DRECORD THashBobJenkins
{
private:
	int FHash;
	System::TArray__1<System::Byte> __fastcall GetDigest();
	static int __fastcall HashLittle(const void *Data, int Len, int InitVal);
	
public:
	static THashBobJenkins __fastcall Create();
	void __fastcall Reset(int AInitialValue = 0x0);
	void __fastcall Update(const void *AData, unsigned ALength)/* overload */;
	void __fastcall Update(const System::TArray__1<System::Byte> AData, unsigned ALength = (unsigned)(0x0))/* overload */;
	void __fastcall Update(const System::UnicodeString Input)/* overload */;
	System::TArray__1<System::Byte> __fastcall HashAsBytes();
	int __fastcall HashAsInteger();
	System::UnicodeString __fastcall HashAsString();
	static System::TArray__1<System::Byte> __fastcall GetHashBytes(const System::UnicodeString AData);
	static System::UnicodeString __fastcall GetHashString(const System::UnicodeString AString);
	static int __fastcall GetHashValue(const System::UnicodeString AData)/* overload */;
	static int __fastcall GetHashValue(const void *AData, int ALength, int AInitialValue = 0x0)/* overload */;
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Hash */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_HASH)
using namespace System::Hash;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_HashHPP
