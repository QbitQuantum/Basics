// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.Internal.CodecUtilsWin32.pas' rev: 34.00 (iOS)

#ifndef Xml_Internal_Codecutilswin32HPP
#define Xml_Internal_Codecutilswin32HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Xml.Internal.EncodingUtils.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Internal
{
namespace Codecutilswin32
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEncodingRepository;
class DELPHICLASS TUnicodeCodec;
class DELPHICLASS EUnicodeCodecException;
class DELPHICLASS TUTF8Codec;
class DELPHICLASS TUTF16BECodec;
class DELPHICLASS TUTF16LECodec;
class DELPHICLASS TUCS4BECodec;
class DELPHICLASS TUCS4LECodec;
class DELPHICLASS TUCS4_2143Codec;
class DELPHICLASS TUCS4_3412Codec;
class DELPHICLASS TUCS2BECodec;
class DELPHICLASS TUCS2LECodec;
class DELPHICLASS TCustomSingleByteCodec;
class DELPHICLASS TISO8859_1Codec;
class DELPHICLASS TISO8859_2Codec;
class DELPHICLASS TISO8859_3Codec;
class DELPHICLASS TISO8859_4Codec;
class DELPHICLASS TISO8859_5Codec;
class DELPHICLASS TISO8859_6Codec;
class DELPHICLASS TISO8859_7Codec;
class DELPHICLASS TISO8859_8Codec;
class DELPHICLASS TISO8859_9Codec;
class DELPHICLASS TISO8859_10Codec;
class DELPHICLASS TISO8859_13Codec;
class DELPHICLASS TISO8859_14Codec;
class DELPHICLASS TISO8859_15Codec;
class DELPHICLASS TWindows708Codec;
class DELPHICLASS TWindows737Codec;
class DELPHICLASS TWindows775Codec;
class DELPHICLASS TWindows858Codec;
class DELPHICLASS TWindows864Codec;
class DELPHICLASS TWindows869Codec;
class DELPHICLASS TWindows870Codec;
class DELPHICLASS TWindows874Codec;
class DELPHICLASS TWindows875Codec;
class DELPHICLASS TWindows1026Codec;
class DELPHICLASS TWindows1047Codec;
class DELPHICLASS TWindows1140Codec;
class DELPHICLASS TWindows1141Codec;
class DELPHICLASS TWindows1142Codec;
class DELPHICLASS TWindows1143Codec;
class DELPHICLASS TWindows1144Codec;
class DELPHICLASS TWindows1145Codec;
class DELPHICLASS TWindows1146Codec;
class DELPHICLASS TWindows1147Codec;
class DELPHICLASS TWindows1148Codec;
class DELPHICLASS TWindows1149Codec;
class DELPHICLASS TWindows1250Codec;
class DELPHICLASS TWindows1251Codec;
class DELPHICLASS TWindows1252Codec;
class DELPHICLASS TWindows1253Codec;
class DELPHICLASS TWindows1254Codec;
class DELPHICLASS TWindows1255Codec;
class DELPHICLASS TWindows1256Codec;
class DELPHICLASS TWindows1257Codec;
class DELPHICLASS TWindows1258Codec;
class DELPHICLASS TIBM037Codec;
class DELPHICLASS TIBM038Codec;
class DELPHICLASS TIBM256Codec;
class DELPHICLASS TIBM273Codec;
class DELPHICLASS TIBM274Codec;
class DELPHICLASS TIBM275Codec;
class DELPHICLASS TIBM277Codec;
class DELPHICLASS TIBM278Codec;
class DELPHICLASS TIBM280Codec;
class DELPHICLASS TIBM281Codec;
class DELPHICLASS TIBM284Codec;
class DELPHICLASS TIBM285Codec;
class DELPHICLASS TIBM290Codec;
class DELPHICLASS TIBM297Codec;
class DELPHICLASS TIBM420Codec;
class DELPHICLASS TIBM423Codec;
class DELPHICLASS TIBM424Codec;
class DELPHICLASS TIBM437Codec;
class DELPHICLASS TIBM500Codec;
class DELPHICLASS TIBM850Codec;
class DELPHICLASS TIBM851Codec;
class DELPHICLASS TIBM852Codec;
class DELPHICLASS TIBM855Codec;
class DELPHICLASS TIBM857Codec;
class DELPHICLASS TIBM860Codec;
class DELPHICLASS TIBM861Codec;
class DELPHICLASS TIBM862Codec;
class DELPHICLASS TIBM863Codec;
class DELPHICLASS TIBM864Codec;
class DELPHICLASS TIBM865Codec;
class DELPHICLASS TIBM866Codec;
class DELPHICLASS TIBM868Codec;
class DELPHICLASS TIBM869Codec;
class DELPHICLASS TIBM870Codec;
class DELPHICLASS TIBM871Codec;
class DELPHICLASS TIBM874Codec;
class DELPHICLASS TIBM875Codec;
class DELPHICLASS TIBM880Codec;
class DELPHICLASS TIBM904Codec;
class DELPHICLASS TIBM905Codec;
class DELPHICLASS TIBM918Codec;
class DELPHICLASS TIBM1004Codec;
class DELPHICLASS TIBM1026Codec;
class DELPHICLASS TIBM1047Codec;
class DELPHICLASS TMacLatin2Codec;
class DELPHICLASS TMacRomanCodec;
class DELPHICLASS TMacCyrillicCodec;
class DELPHICLASS TMacGreekCodec;
class DELPHICLASS TMacIcelandicCodec;
class DELPHICLASS TMacTurkishCodec;
class DELPHICLASS TUSASCIICodec;
class DELPHICLASS TEBCDIC_USCodec;
class DELPHICLASS TKOI8_RCodec;
class DELPHICLASS TJIS_X0201Codec;
class DELPHICLASS TNextStepCodec;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TEncodingRepository : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod virtual TUnicodeCodec* __fastcall CreateCodecByAlias(const System::UnicodeString CodecAlias);
	__classmethod virtual TUnicodeCodec* __fastcall CreateCodecForStream(System::Classes::TStream* const Stream);
	__classmethod virtual int __fastcall Count();
	__classmethod virtual System::UnicodeString __fastcall EncodingName(const int I);
public:
	/* TObject.Create */ inline __fastcall TEncodingRepository() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingRepository() { }
	
};


enum DECLSPEC_DENUM TCodecErrorAction : unsigned char { eaException, eaStop, eaIgnore, eaSkip, eaReplace };

enum DECLSPEC_DENUM TCodecReadLFOption : unsigned char { lrPass, lrNormalize };

enum DECLSPEC_DENUM TCodecWriteLFOption : unsigned char { lwLF, lwCR, lwCRLF };

typedef void __fastcall (__closure *TCodecReadEvent)(System::TObject* const Sender, void *Buf, long Count, bool &Ok);

typedef void __fastcall (__closure *TCodecWriteEvent)(System::TObject* const Sender, const void *Buf, long Count);

class PASCALIMPLEMENTATION TUnicodeCodec : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TCodecErrorAction FErrorAction;
	System::WideChar FDecodeReplaceChar;
	TCodecReadLFOption FReadLFOption;
	TCodecWriteLFOption FWriteLFOption;
	TCodecReadEvent FOnRead;
	TCodecWriteEvent FOnWrite;
	bool FReadAhead;
	unsigned FReadAheadBuffer;
	int FReadAheadByteCount;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	void __fastcall ResetReadAhead();
	void __fastcall SetDecodeReplaceChar(const System::WideChar Value);
	void __fastcall SetErrorAction(const TCodecErrorAction Value);
	virtual void __fastcall SetReadLFOption(const TCodecReadLFOption Value);
	virtual void __fastcall SetWriteLFOption(const TCodecWriteLFOption Value);
	void __fastcall SetOnRead(const TCodecReadEvent Value);
	bool __fastcall ReadBuffer(void *Buf, int Count);
	void __fastcall WriteBuffer(const void *Buf, int Count);
	virtual void __fastcall InternalReadUCS4Char(/* out */ unsigned &C, /* out */ int &ByteCount) = 0 ;
	virtual void __fastcall InternalWriteUCS4Char(const unsigned C, /* out */ int &ByteCount) = 0 ;
	
public:
	__fastcall virtual TUnicodeCodec();
	virtual void __fastcall Decode(const void * Buf, const int BufSize, const void * DestBuf, const int DestSize, /* out */ int &ProcessedBytes, /* out */ int &DestLength) = 0 ;
	virtual System::AnsiString __fastcall Encode(const System::WideChar * S, const int Length, /* out */ int &ProcessedChars) = 0 ;
	void __fastcall DecodeStr(const void * Buf, const int BufSize, System::WideString &Dest);
	System::AnsiString __fastcall EncodeStr(const System::WideString S);
	void __fastcall ReadUCS4Char(/* out */ unsigned &C, /* out */ int &ByteCount);
	virtual void __fastcall WriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual int __fastcall AliasIndexOf(const System::UnicodeString S);
	__classmethod virtual System::TArray__1<System::Byte> __fastcall GetPreamble();
	__classmethod virtual bool __fastcall HasAlias(const System::UnicodeString S);
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
	__property TCodecErrorAction ErrorAction = {read=FErrorAction, write=SetErrorAction, default=0};
	__property System::WideChar DecodeReplaceChar = {read=FDecodeReplaceChar, write=SetDecodeReplaceChar, default=65533};
	__property TCodecReadLFOption ReadLFOption = {read=FReadLFOption, write=SetReadLFOption, default=0};
	__property TCodecWriteLFOption WriteLFOption = {read=FWriteLFOption, write=SetWriteLFOption, default=0};
	__property TCodecReadEvent OnRead = {read=FOnRead, write=SetOnRead};
	__property TCodecWriteEvent OnWrite = {read=FOnWrite, write=FOnWrite};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TUnicodeCodec() { }
	
};


class PASCALIMPLEMENTATION EUnicodeCodecException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	int ProcessedBytes;
public:
	/* Exception.Create */ inline __fastcall EUnicodeCodecException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EUnicodeCodecException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EUnicodeCodecException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EUnicodeCodecException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EUnicodeCodecException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EUnicodeCodecException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EUnicodeCodecException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EUnicodeCodecException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EUnicodeCodecException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EUnicodeCodecException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EUnicodeCodecException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EUnicodeCodecException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EUnicodeCodecException() { }
	
};


class PASCALIMPLEMENTATION TUTF8Codec : public TUnicodeCodec
{
	typedef TUnicodeCodec inherited;
	
private:
	void __fastcall UCS4CharToUTF8(const unsigned Ch, const void * Dest, const int DestSize, /* out */ int &SeqSize);
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	virtual void __fastcall InternalReadUCS4Char(/* out */ unsigned &C, /* out */ int &ByteCount);
	virtual void __fastcall InternalWriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	
public:
	virtual void __fastcall Decode(const void * Buf, const int BufSize, const void * DestBuf, const int DestSize, /* out */ int &ProcessedBytes, /* out */ int &DestLength);
	virtual System::AnsiString __fastcall Encode(const System::WideChar * S, const int Length, /* out */ int &ProcessedChars);
	int __fastcall GetCharCount(const System::AnsiString S);
	virtual void __fastcall WriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	__classmethod virtual System::TArray__1<System::Byte> __fastcall GetPreamble();
public:
	/* TUnicodeCodec.Create */ inline __fastcall virtual TUTF8Codec() : TUnicodeCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TUTF8Codec() { }
	
};


class PASCALIMPLEMENTATION TUTF16BECodec : public TUnicodeCodec
{
	typedef TUnicodeCodec inherited;
	
private:
	void __fastcall UCS4CharToUTF16BE(const unsigned Ch, const void * Dest, const int DestSize, /* out */ int &SeqSize);
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	virtual void __fastcall InternalReadUCS4Char(/* out */ unsigned &C, /* out */ int &ByteCount);
	virtual void __fastcall InternalWriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	
public:
	virtual void __fastcall Decode(const void * Buf, const int BufSize, const void * DestBuf, const int DestSize, /* out */ int &ProcessedBytes, /* out */ int &DestLength);
	virtual System::AnsiString __fastcall Encode(const System::WideChar * S, const int Length, /* out */ int &ProcessedChars);
	virtual void __fastcall WriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	__classmethod virtual System::TArray__1<System::Byte> __fastcall GetPreamble();
public:
	/* TUnicodeCodec.Create */ inline __fastcall virtual TUTF16BECodec() : TUnicodeCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TUTF16BECodec() { }
	
};


class PASCALIMPLEMENTATION TUTF16LECodec : public TUnicodeCodec
{
	typedef TUnicodeCodec inherited;
	
private:
	void __fastcall UCS4CharToUTF16LE(const unsigned Ch, const void * Dest, const int DestSize, /* out */ int &SeqSize);
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	virtual void __fastcall InternalReadUCS4Char(/* out */ unsigned &C, /* out */ int &ByteCount);
	virtual void __fastcall InternalWriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	
public:
	virtual void __fastcall Decode(const void * Buf, const int BufSize, const void * DestBuf, const int DestSize, /* out */ int &ProcessedBytes, /* out */ int &DestLength);
	virtual System::AnsiString __fastcall Encode(const System::WideChar * S, const int Length, /* out */ int &ProcessedChars);
	virtual void __fastcall WriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	__classmethod virtual System::TArray__1<System::Byte> __fastcall GetPreamble();
public:
	/* TUnicodeCodec.Create */ inline __fastcall virtual TUTF16LECodec() : TUnicodeCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TUTF16LECodec() { }
	
};


class PASCALIMPLEMENTATION TUCS4BECodec : public TUnicodeCodec
{
	typedef TUnicodeCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	virtual void __fastcall InternalReadUCS4Char(/* out */ unsigned &C, /* out */ int &ByteCount);
	virtual void __fastcall InternalWriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	
public:
	virtual void __fastcall Decode(const void * Buf, const int BufSize, const void * DestBuf, const int DestSize, /* out */ int &ProcessedBytes, /* out */ int &DestLength);
	virtual System::AnsiString __fastcall Encode(const System::WideChar * S, const int Length, /* out */ int &ProcessedChars);
	virtual void __fastcall WriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	__classmethod virtual System::TArray__1<System::Byte> __fastcall GetPreamble();
public:
	/* TUnicodeCodec.Create */ inline __fastcall virtual TUCS4BECodec() : TUnicodeCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TUCS4BECodec() { }
	
};


class PASCALIMPLEMENTATION TUCS4LECodec : public TUnicodeCodec
{
	typedef TUnicodeCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	virtual void __fastcall InternalReadUCS4Char(/* out */ unsigned &C, /* out */ int &ByteCount);
	virtual void __fastcall InternalWriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	
public:
	virtual void __fastcall Decode(const void * Buf, const int BufSize, const void * DestBuf, const int DestSize, /* out */ int &ProcessedBytes, /* out */ int &DestLength);
	virtual System::AnsiString __fastcall Encode(const System::WideChar * S, const int Length, /* out */ int &ProcessedChars);
	virtual void __fastcall WriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	__classmethod virtual System::TArray__1<System::Byte> __fastcall GetPreamble();
public:
	/* TUnicodeCodec.Create */ inline __fastcall virtual TUCS4LECodec() : TUnicodeCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TUCS4LECodec() { }
	
};


class PASCALIMPLEMENTATION TUCS4_2143Codec : public TUnicodeCodec
{
	typedef TUnicodeCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	virtual void __fastcall InternalReadUCS4Char(/* out */ unsigned &C, /* out */ int &ByteCount);
	virtual void __fastcall InternalWriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	
public:
	virtual void __fastcall Decode(const void * Buf, const int BufSize, const void * DestBuf, const int DestSize, /* out */ int &ProcessedBytes, /* out */ int &DestLength);
	virtual System::AnsiString __fastcall Encode(const System::WideChar * S, const int Length, /* out */ int &ProcessedChars);
	virtual void __fastcall WriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	__classmethod virtual System::TArray__1<System::Byte> __fastcall GetPreamble();
public:
	/* TUnicodeCodec.Create */ inline __fastcall virtual TUCS4_2143Codec() : TUnicodeCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TUCS4_2143Codec() { }
	
};


class PASCALIMPLEMENTATION TUCS4_3412Codec : public TUnicodeCodec
{
	typedef TUnicodeCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	virtual void __fastcall InternalReadUCS4Char(/* out */ unsigned &C, /* out */ int &ByteCount);
	virtual void __fastcall InternalWriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	
public:
	virtual void __fastcall Decode(const void * Buf, const int BufSize, const void * DestBuf, const int DestSize, /* out */ int &ProcessedBytes, /* out */ int &DestLength);
	virtual System::AnsiString __fastcall Encode(const System::WideChar * S, const int Length, /* out */ int &ProcessedChars);
	virtual void __fastcall WriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	__classmethod virtual System::TArray__1<System::Byte> __fastcall GetPreamble();
public:
	/* TUnicodeCodec.Create */ inline __fastcall virtual TUCS4_3412Codec() : TUnicodeCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TUCS4_3412Codec() { }
	
};


class PASCALIMPLEMENTATION TUCS2BECodec : public TUnicodeCodec
{
	typedef TUnicodeCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	virtual void __fastcall InternalReadUCS4Char(/* out */ unsigned &C, /* out */ int &ByteCount);
	virtual void __fastcall InternalWriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	
public:
	virtual void __fastcall Decode(const void * Buf, const int BufSize, const void * DestBuf, const int DestSize, /* out */ int &ProcessedBytes, /* out */ int &DestLength);
	virtual System::AnsiString __fastcall Encode(const System::WideChar * S, const int Length, /* out */ int &ProcessedChars);
	virtual void __fastcall WriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
public:
	/* TUnicodeCodec.Create */ inline __fastcall virtual TUCS2BECodec() : TUnicodeCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TUCS2BECodec() { }
	
};


class PASCALIMPLEMENTATION TUCS2LECodec : public TUnicodeCodec
{
	typedef TUnicodeCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	virtual void __fastcall InternalReadUCS4Char(/* out */ unsigned &C, /* out */ int &ByteCount);
	virtual void __fastcall InternalWriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	
public:
	virtual void __fastcall Decode(const void * Buf, const int BufSize, const void * DestBuf, const int DestSize, /* out */ int &ProcessedBytes, /* out */ int &DestLength);
	virtual System::AnsiString __fastcall Encode(const System::WideChar * S, const int Length, /* out */ int &ProcessedChars);
	virtual void __fastcall WriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
public:
	/* TUnicodeCodec.Create */ inline __fastcall virtual TUCS2LECodec() : TUnicodeCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TUCS2LECodec() { }
	
};


class PASCALIMPLEMENTATION TCustomSingleByteCodec : public TUnicodeCodec
{
	typedef TUnicodeCodec inherited;
	
protected:
	char FEncodeReplaceChar;
	virtual void __fastcall InternalReadUCS4Char(/* out */ unsigned &C, /* out */ int &ByteCount);
	virtual void __fastcall InternalWriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	
public:
	__fastcall virtual TCustomSingleByteCodec();
	__property char EncodeReplaceChar = {read=FEncodeReplaceChar, write=FEncodeReplaceChar, default=32};
	virtual void __fastcall Decode(const void * Buf, const int BufSize, const void * DestBuf, const int DestSize, /* out */ int &ProcessedBytes, /* out */ int &DestLength);
	virtual System::AnsiString __fastcall Encode(const System::WideChar * S, const int Length, /* out */ int &ProcessedChars);
	virtual System::WideChar __fastcall DecodeChar(const char P) = 0 ;
	virtual char __fastcall EncodeChar(const System::WideChar Ch) = 0 ;
	virtual unsigned __fastcall DecodeUCS4Char(const char P);
	virtual char __fastcall EncodeUCS4Char(const unsigned Ch);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TCustomSingleByteCodec() { }
	
};


class PASCALIMPLEMENTATION TISO8859_1Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TISO8859_1Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TISO8859_1Codec() { }
	
};


class PASCALIMPLEMENTATION TISO8859_2Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TISO8859_2Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TISO8859_2Codec() { }
	
};


class PASCALIMPLEMENTATION TISO8859_3Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TISO8859_3Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TISO8859_3Codec() { }
	
};


class PASCALIMPLEMENTATION TISO8859_4Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TISO8859_4Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TISO8859_4Codec() { }
	
};


class PASCALIMPLEMENTATION TISO8859_5Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TISO8859_5Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TISO8859_5Codec() { }
	
};


class PASCALIMPLEMENTATION TISO8859_6Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TISO8859_6Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TISO8859_6Codec() { }
	
};


class PASCALIMPLEMENTATION TISO8859_7Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TISO8859_7Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TISO8859_7Codec() { }
	
};


class PASCALIMPLEMENTATION TISO8859_8Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TISO8859_8Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TISO8859_8Codec() { }
	
};


class PASCALIMPLEMENTATION TISO8859_9Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TISO8859_9Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TISO8859_9Codec() { }
	
};


class PASCALIMPLEMENTATION TISO8859_10Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TISO8859_10Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TISO8859_10Codec() { }
	
};


class PASCALIMPLEMENTATION TISO8859_13Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TISO8859_13Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TISO8859_13Codec() { }
	
};


class PASCALIMPLEMENTATION TISO8859_14Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TISO8859_14Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TISO8859_14Codec() { }
	
};


class PASCALIMPLEMENTATION TISO8859_15Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TISO8859_15Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TISO8859_15Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows708Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows708Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows708Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows737Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows737Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows737Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows775Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows775Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows775Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows858Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows858Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows858Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows864Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows864Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows864Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows869Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows869Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows869Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows870Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows870Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows870Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows874Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows874Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows874Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows875Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows875Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows875Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1026Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1026Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1026Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1047Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1047Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1047Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1140Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1140Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1140Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1141Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1141Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1141Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1142Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1142Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1142Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1143Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1143Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1143Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1144Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1144Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1144Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1145Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1145Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1145Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1146Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1146Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1146Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1147Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1147Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1147Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1148Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1148Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1148Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1149Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1149Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1149Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1250Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1250Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1250Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1251Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1251Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1251Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1252Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1252Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1252Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1253Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1253Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1253Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1254Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1254Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1254Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1255Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1255Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1255Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1256Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1256Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1256Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1257Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1257Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1257Codec() { }
	
};


class PASCALIMPLEMENTATION TWindows1258Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TWindows1258Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWindows1258Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM037Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM037Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM037Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM038Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM038Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM038Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM256Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM256Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM256Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM273Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM273Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM273Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM274Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM274Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM274Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM275Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM275Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM275Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM277Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM277Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM277Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM278Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM278Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM278Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM280Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM280Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM280Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM281Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM281Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM281Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM284Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM284Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM284Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM285Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM285Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM285Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM290Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM290Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM290Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM297Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM297Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM297Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM420Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM420Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM420Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM423Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM423Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM423Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM424Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM424Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM424Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM437Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM437Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM437Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM500Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM500Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM500Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM850Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM850Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM850Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM851Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM851Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM851Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM852Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM852Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM852Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM855Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM855Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM855Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM857Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM857Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM857Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM860Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM860Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM860Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM861Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM861Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM861Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM862Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM862Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM862Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM863Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM863Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM863Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM864Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM864Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM864Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM865Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM865Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM865Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM866Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM866Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM866Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM868Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM868Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM868Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM869Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM869Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM869Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM870Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM870Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM870Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM871Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM871Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM871Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM874Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM874Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM874Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM875Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM875Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM875Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM880Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM880Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM880Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM904Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM904Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM904Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM905Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM905Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM905Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM918Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM918Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM918Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM1004Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM1004Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM1004Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM1026Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM1026Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM1026Codec() { }
	
};


class PASCALIMPLEMENTATION TIBM1047Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TIBM1047Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBM1047Codec() { }
	
};


class PASCALIMPLEMENTATION TMacLatin2Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TMacLatin2Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMacLatin2Codec() { }
	
};


class PASCALIMPLEMENTATION TMacRomanCodec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TMacRomanCodec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMacRomanCodec() { }
	
};


class PASCALIMPLEMENTATION TMacCyrillicCodec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TMacCyrillicCodec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMacCyrillicCodec() { }
	
};


class PASCALIMPLEMENTATION TMacGreekCodec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TMacGreekCodec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMacGreekCodec() { }
	
};


class PASCALIMPLEMENTATION TMacIcelandicCodec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TMacIcelandicCodec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMacIcelandicCodec() { }
	
};


class PASCALIMPLEMENTATION TMacTurkishCodec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TMacTurkishCodec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMacTurkishCodec() { }
	
};


class PASCALIMPLEMENTATION TUSASCIICodec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod bool __fastcall CheckA(const System::AnsiString S);
	__classmethod bool __fastcall CheckW(const System::WideString S);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TUSASCIICodec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TUSASCIICodec() { }
	
};


class PASCALIMPLEMENTATION TEBCDIC_USCodec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TEBCDIC_USCodec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TEBCDIC_USCodec() { }
	
};


class PASCALIMPLEMENTATION TKOI8_RCodec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TKOI8_RCodec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TKOI8_RCodec() { }
	
};


class PASCALIMPLEMENTATION TJIS_X0201Codec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
protected:
	__classmethod virtual Xml::Internal::Encodingutils::TEncodingInfoClass __fastcall EncodingInfoClass();
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TJIS_X0201Codec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJIS_X0201Codec() { }
	
};


class PASCALIMPLEMENTATION TNextStepCodec : public TCustomSingleByteCodec
{
	typedef TCustomSingleByteCodec inherited;
	
public:
	virtual System::WideChar __fastcall DecodeChar(const char P);
	virtual char __fastcall EncodeChar(const System::WideChar Ch);
	__classmethod virtual System::UnicodeString __fastcall Name();
public:
	/* TCustomSingleByteCodec.Create */ inline __fastcall virtual TNextStepCodec() : TCustomSingleByteCodec() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TNextStepCodec() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Codecutilswin32 */
}	/* namespace Internal */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL_CODECUTILSWIN32)
using namespace Xml::Internal::Codecutilswin32;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL)
using namespace Xml::Internal;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_Internal_Codecutilswin32HPP
