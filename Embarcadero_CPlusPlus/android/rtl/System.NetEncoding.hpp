// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.NetEncoding.pas' rev: 34.00 (Android)

#ifndef System_NetencodingHPP
#define System_NetencodingHPP

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
namespace Netencoding
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TNetEncoding;
class DELPHICLASS TBase64Encoding;
class DELPHICLASS TURLEncoding;
class DELPHICLASS THTMLEncoding;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TNetEncoding : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static TNetEncoding* FBase64Encoding;
	static TNetEncoding* FHTMLEncoding;
	static TURLEncoding* FURLEncoding;
	static TNetEncoding* __fastcall GetBase64Encoding();
	static TNetEncoding* __fastcall GetHTMLEncoding();
	static TURLEncoding* __fastcall GetURLEncoding();
	
private:
	// __classmethod void __fastcall Destroy_();
	
protected:
	virtual NativeInt __fastcall DoDecode(System::Classes::TStream* const Input, System::Classes::TStream* const Output)/* overload */;
	virtual System::TArray__1<System::Byte> __fastcall DoDecode(const System::Byte *Input, const int Input_High)/* overload */;
	virtual System::UnicodeString __fastcall DoDecode(const System::UnicodeString Input) = 0 /* overload */;
	virtual NativeInt __fastcall DoEncode(System::Classes::TStream* const Input, System::Classes::TStream* const Output)/* overload */;
	virtual System::TArray__1<System::Byte> __fastcall DoEncode(const System::Byte *Input, const int Input_High)/* overload */;
	virtual System::UnicodeString __fastcall DoEncode(const System::UnicodeString Input) = 0 /* overload */;
	virtual System::TArray__1<System::Byte> __fastcall DoDecodeStringToBytes(const System::UnicodeString Input);
	virtual System::UnicodeString __fastcall DoEncodeBytesToString(const System::Byte *Input, const int Input_High)/* overload */;
	virtual System::UnicodeString __fastcall DoEncodeBytesToString(const void * Input, int Size)/* overload */;
	
public:
	int __fastcall Decode(System::Classes::TStream* const Input, System::Classes::TStream* const Output)/* overload */;
	System::TArray__1<System::Byte> __fastcall Decode(const System::Byte *Input, const int Input_High)/* overload */;
	System::UnicodeString __fastcall Decode(const System::UnicodeString Input)/* overload */;
	int __fastcall Encode(System::Classes::TStream* const Input, System::Classes::TStream* const Output)/* overload */;
	System::TArray__1<System::Byte> __fastcall Encode(const System::Byte *Input, const int Input_High)/* overload */;
	System::UnicodeString __fastcall Encode(const System::UnicodeString Input)/* overload */;
	System::TArray__1<System::Byte> __fastcall DecodeStringToBytes(const System::UnicodeString Input);
	System::UnicodeString __fastcall EncodeBytesToString(const System::Byte *Input, const int Input_High)/* overload */;
	System::UnicodeString __fastcall EncodeBytesToString(const void * Input, int Size)/* overload */;
	/* static */ __property TNetEncoding* Base64 = {read=GetBase64Encoding};
	/* static */ __property TNetEncoding* HTML = {read=GetHTMLEncoding};
	/* static */ __property TURLEncoding* URL = {read=GetURLEncoding};
	
private:
	// __classmethod void __fastcall Create_();
public:
	/* TObject.Create */ inline __fastcall TNetEncoding() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TNetEncoding() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBase64Encoding : public TNetEncoding
{
	typedef TNetEncoding inherited;
	
	
protected:
	enum class DECLSPEC_DENUM TEncodeStep : unsigned char { EncodeByteStepA, EncodeByteStepB, EncodeByteStepC, EncodeWordStepA, EncodeWordStepB, EncodeWordStepC };
	
	enum class DECLSPEC_DENUM TDecodeStep : unsigned char { DecodeStepA, DecodeStepB, DecodeStepC, DecodeStepD };
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TEncodeState
	{
	public:
		TBase64Encoding::TEncodeStep Step;
		System::Byte Result;
		int StepCount;
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TDecodeState
	{
	public:
		TBase64Encoding::TDecodeStep Step;
		System::Byte Result;
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
	
protected:
	static constexpr System::Int8 kCharsPerLine = System::Int8(0x4c);
	
	#define TBase64Encoding_kLineSeparator u"\r\n"
	
	static System::StaticArray<System::Int8, 80> DecodeTable;
	static System::StaticArray<System::Byte, 64> EncodeTable;
	int FCharsPerline;
	System::UnicodeString FLineSeparator;
	void __fastcall InitEncodeState(TEncodeState &State, const int CharSize);
	void __fastcall InitDecodeState(TDecodeState &State);
	unsigned __int64 __fastcall EstimateEncodeLength(const unsigned __int64 InputLength, const int CharSize);
	unsigned __int64 __fastcall EstimateDecodeLength(const unsigned __int64 InputLength);
	int __fastcall DecodeValue(const System::Byte Code);
	System::Byte __fastcall EncodeValue(const int Code);
	int __fastcall EncodeBytes(System::PByte Input, System::PByte Output, int InputLen, System::Byte *LineSeparator, const int LineSeparator_High, TEncodeState &State);
	int __fastcall EncodeBytesEnd(System::PByte Output, TEncodeState &State);
	int __fastcall DecodeBytes(System::PByte Input, System::PByte Output, int InputLen, int CharSize, TDecodeState &State);
	virtual NativeInt __fastcall DoDecode(System::Classes::TStream* const Input, System::Classes::TStream* const Output)/* overload */;
	virtual System::TArray__1<System::Byte> __fastcall DoDecode(const System::Byte *Input, const int Input_High)/* overload */;
	virtual System::UnicodeString __fastcall DoDecode(const System::UnicodeString Input)/* overload */;
	virtual NativeInt __fastcall DoEncode(System::Classes::TStream* const Input, System::Classes::TStream* const Output)/* overload */;
	virtual System::TArray__1<System::Byte> __fastcall DoEncode(const System::Byte *Input, const int Input_High)/* overload */;
	virtual System::UnicodeString __fastcall DoEncode(const System::UnicodeString Input)/* overload */;
	virtual System::TArray__1<System::Byte> __fastcall DoDecodeStringToBytes(const System::UnicodeString Input);
	virtual System::UnicodeString __fastcall DoEncodeBytesToString(const System::Byte *Input, const int Input_High)/* overload */;
	virtual System::UnicodeString __fastcall DoEncodeBytesToString(const void * Input, int Size)/* overload */;
	
public:
	__fastcall virtual TBase64Encoding()/* overload */;
	__fastcall virtual TBase64Encoding(int CharsPerLine)/* overload */;
	__fastcall virtual TBase64Encoding(int CharsPerLine, System::UnicodeString LineSeparator)/* overload */;
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBase64Encoding() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TURLEncoding : public TNetEncoding
{
	typedef TNetEncoding inherited;
	
	
public:
	typedef System::Byte UnsafeChar;
	
	typedef System::Set<System::Byte, 0, 255> TUnsafeChars;
	
	enum class DECLSPEC_DENUM TEncodeOption : unsigned char { SpacesAsPlus, EncodePercent };
	
	typedef System::Set<TEncodeOption, _DELPHI_SET_ENUMERATOR(TEncodeOption::SpacesAsPlus), _DELPHI_SET_ENUMERATOR(TEncodeOption::EncodePercent)> TEncodeOptions;
	
	enum class DECLSPEC_DENUM TDecodeOption : unsigned char { PlusAsSpaces };
	
	typedef System::Set<TDecodeOption, _DELPHI_SET_ENUMERATOR(TDecodeOption::PlusAsSpaces), _DELPHI_SET_ENUMERATOR(TDecodeOption::PlusAsSpaces)> TDecodeOptions;
	
	
private:
	static void __fastcall AppendByte(System::Byte B, System::WideChar * &Buffer);
	static TUnsafeChars FormUnsafeChars;
	static TUnsafeChars AuthUnsafeChars;
	static TUnsafeChars PathUnsafeChars;
	static TUnsafeChars QueryUnsafeChars;
	
protected:
	virtual System::UnicodeString __fastcall DoDecode(const System::UnicodeString Input)/* overload */;
	virtual System::UnicodeString __fastcall DoEncode(const System::UnicodeString Input)/* overload */;
	virtual System::TArray__1<System::Byte> __fastcall DoDecodeStringToBytes(const System::UnicodeString Input)/* overload */;
	
public:
	System::UnicodeString __fastcall EncodePath(const System::UnicodeString APath, const TUnsafeChars &AExtraUnsafeChars = TUnsafeChars());
	System::UnicodeString __fastcall EncodeAuth(const System::UnicodeString Auth, const TUnsafeChars &AExtraUnsafeChars = TUnsafeChars());
	System::UnicodeString __fastcall EncodeQuery(const System::UnicodeString AQuery, const TUnsafeChars &AExtraUnsafeChars = TUnsafeChars());
	System::UnicodeString __fastcall EncodeForm(const System::UnicodeString AInput, const TUnsafeChars &AExtraUnsafeChars = TUnsafeChars(), System::Sysutils::TEncoding* AEncoding = (System::Sysutils::TEncoding*)(0x0));
	System::UnicodeString __fastcall URLDecode(const System::UnicodeString AValue);
	System::UnicodeString __fastcall FormDecode(const System::UnicodeString AValue, System::Sysutils::TEncoding* AEncoding = (System::Sysutils::TEncoding*)(0x0));
	HIDESBASE System::UnicodeString __fastcall Encode(const System::UnicodeString AInput, const TUnsafeChars &ASet, const TEncodeOptions AOptions, System::Sysutils::TEncoding* AEncoding = (System::Sysutils::TEncoding*)(0x0))/* overload */;
	HIDESBASE System::UnicodeString __fastcall Decode(const System::UnicodeString AValue, const TDecodeOptions AOptions, System::Sysutils::TEncoding* AEncoding = (System::Sysutils::TEncoding*)(0x0))/* overload */;
public:
	/* TObject.Create */ inline __fastcall TURLEncoding() : TNetEncoding() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TURLEncoding() { }
	
	/* Hoisted overloads: */
	
protected:
	inline NativeInt __fastcall  DoDecode(System::Classes::TStream* const Input, System::Classes::TStream* const Output){ return TNetEncoding::DoDecode(Input, Output); }
	inline System::TArray__1<System::Byte> __fastcall  DoDecode(const System::Byte *Input, const int Input_High){ return TNetEncoding::DoDecode(Input, Input_High); }
	inline NativeInt __fastcall  DoEncode(System::Classes::TStream* const Input, System::Classes::TStream* const Output){ return TNetEncoding::DoEncode(Input, Output); }
	inline System::TArray__1<System::Byte> __fastcall  DoEncode(const System::Byte *Input, const int Input_High){ return TNetEncoding::DoEncode(Input, Input_High); }
	
public:
	inline int __fastcall  Encode(System::Classes::TStream* const Input, System::Classes::TStream* const Output){ return TNetEncoding::Encode(Input, Output); }
	inline System::TArray__1<System::Byte> __fastcall  Encode(const System::Byte *Input, const int Input_High){ return TNetEncoding::Encode(Input, Input_High); }
	inline System::UnicodeString __fastcall  Encode(const System::UnicodeString Input){ return TNetEncoding::Encode(Input); }
	inline int __fastcall  Decode(System::Classes::TStream* const Input, System::Classes::TStream* const Output){ return TNetEncoding::Decode(Input, Output); }
	inline System::TArray__1<System::Byte> __fastcall  Decode(const System::Byte *Input, const int Input_High){ return TNetEncoding::Decode(Input, Input_High); }
	inline System::UnicodeString __fastcall  Decode(const System::UnicodeString Input){ return TNetEncoding::Decode(Input); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION THTMLEncoding : public TNetEncoding
{
	typedef TNetEncoding inherited;
	
protected:
	virtual System::UnicodeString __fastcall DoDecode(const System::UnicodeString AInput)/* overload */;
	virtual System::UnicodeString __fastcall DoEncode(const System::UnicodeString AInput)/* overload */;
public:
	/* TObject.Create */ inline __fastcall THTMLEncoding() : TNetEncoding() { }
	/* TObject.Destroy */ inline __fastcall virtual ~THTMLEncoding() { }
	
	/* Hoisted overloads: */
	
protected:
	inline NativeInt __fastcall  DoDecode(System::Classes::TStream* const Input, System::Classes::TStream* const Output){ return TNetEncoding::DoDecode(Input, Output); }
	inline System::TArray__1<System::Byte> __fastcall  DoDecode(const System::Byte *Input, const int Input_High){ return TNetEncoding::DoDecode(Input, Input_High); }
	inline NativeInt __fastcall  DoEncode(System::Classes::TStream* const Input, System::Classes::TStream* const Output){ return TNetEncoding::DoEncode(Input, Output); }
	inline System::TArray__1<System::Byte> __fastcall  DoEncode(const System::Byte *Input, const int Input_High){ return TNetEncoding::DoEncode(Input, Input_High); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Netencoding */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_NETENCODING)
using namespace System::Netencoding;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_NetencodingHPP
