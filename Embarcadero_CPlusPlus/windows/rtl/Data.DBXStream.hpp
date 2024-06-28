// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXStream.pas' rev: 34.00 (Windows)

#ifndef Data_DbxstreamHPP
#define Data_DbxstreamHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <System.JSON.hpp>
#include <Data.DBXPlatform.hpp>
#include <Data.DBXTransport.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxstream
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXBcdFormat;
class DELPHICLASS TDBXBinaryStream;
class DELPHICLASS TDBXCharDecoder;
class DELPHICLASS TDBXColumnFlags;
class DELPHICLASS TDBXFieldHeader;
class DELPHICLASS TDBXFieldPacker;
class DELPHICLASS TDBXJSonError;
class DELPHICLASS TDBXJSonErrorCodes;
class DELPHICLASS TDBXJSonStreamReader;
class DELPHICLASS TDBXJSonStreamWriter;
class DELPHICLASS TDBXRowBlobStreamReader;
class DELPHICLASS TDBXRowBuffer;
class DELPHICLASS TDBXStringCodes;
class DELPHICLASS TDBXStringDecoder;
class DELPHICLASS TDBXStringEncoder;
class DELPHICLASS TDBXTokens;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXBcdFormat : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 TextReadWrite = System::Int8(0x0);
	
	static const System::Int8 BinaryRead = System::Int8(0x1);
	
	static const System::Int8 BinaryWrite = System::Int8(0x2);
	
	static const System::Int8 BinaryReadWrite = System::Int8(0x3);
	
public:
	/* TObject.Create */ inline __fastcall TDBXBcdFormat() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXBcdFormat() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXBinaryStream : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall TDBXBinaryStream();
	__fastcall virtual ~TDBXBinaryStream();
	void __fastcall Growbuf(const int BytesNeeded);
	void __fastcall CheckBuf(const int BytesNeeded);
	void __fastcall TrimBuf();
	int __fastcall Skip(const int Length);
	bool __fastcall ReadBoolean();
	System::Byte __fastcall ReadByte();
	short __fastcall ReadInt8();
	int __fastcall ReadInt32();
	short __fastcall ReadInt16();
	System::Word __fastcall ReadUInt16();
	__int64 __fastcall ReadInt64();
	float __fastcall ReadSingle();
	__int64 __fastcall ReadDoubleAsInt64();
	double __fastcall ReadDouble();
	__int64 __fastcall ReadTimestamp();
	int __fastcall ReadTimestampNanos();
	void __fastcall ReadBigDecimalBuffer();
	bool __fastcall BigDecimalFitsInInt64();
	
protected:
	void __fastcall SetMinBufferSize(const int Size);
	int __fastcall SkipNullTermString();
	void __fastcall SkipField();
	__int64 __fastcall GetBigDecimalBufferAsInt64();
	int __fastcall GetBigDecimalLength();
	bool FTwoByteStringTerminator;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FBuf;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FBuf;
#endif /* _WIN64 */
	int FBufLength;
	int FOff;
	int FCurrentOrdinal;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FBigDecimalBuffer;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FBigDecimalBuffer;
#endif /* _WIN64 */
	Data::Dbxplatform::TDBXInt32s FBigDecimalLength;
	int FBigDecimalScale;
	int FBigDecimalSignum;
	
private:
	int FNanos;
	int FMinBufSize;
	
public:
	__property int MinBufferSize = {read=FMinBufSize, write=SetMinBufferSize, nodefault};
#ifndef _WIN64
	__property System::DynamicArray<System::Byte> Buffer = {read=FBuf};
#else /* _WIN64 */
	__property System::TArray__1<System::Byte> Buffer = {read=FBuf};
#endif /* _WIN64 */
	__property int BufferOffset = {read=FOff, nodefault};
#ifndef _WIN64
	__property System::DynamicArray<System::Byte> BigDecimalBuffer = {read=FBigDecimalBuffer};
#else /* _WIN64 */
	__property System::TArray__1<System::Byte> BigDecimalBuffer = {read=FBigDecimalBuffer};
#endif /* _WIN64 */
	__property __int64 BigDecimalBufferAsInt64 = {read=GetBigDecimalBufferAsInt64};
	__property int BigDecimalLength = {read=GetBigDecimalLength, nodefault};
	__property int BigDecimalSignum = {read=FBigDecimalSignum, nodefault};
	__property int BigDecimalScale = {read=FBigDecimalScale, nodefault};
	__property int CurrentOrdinal = {read=FCurrentOrdinal, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXCharDecoder : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	void __fastcall InitDecoder();
	bool __fastcall GrowDecodeBufTo(const int InNewSize);
#ifndef _WIN64
	bool __fastcall Decode(const System::DynamicArray<System::Byte> Buf, const int InBufOff, const int MaxBytes);
#else /* _WIN64 */
	bool __fastcall Decode(const System::TArray__1<System::Byte> Buf, const int InBufOff, const int MaxBytes);
#endif /* _WIN64 */
	void __fastcall AddNullChar();
	__fastcall virtual ~TDBXCharDecoder();
	
private:
#ifndef _WIN64
	bool __fastcall DecodeChars(const System::DynamicArray<System::Byte> Buf, const int InBufOff, const int InMaxOff);
#else /* _WIN64 */
	bool __fastcall DecodeChars(const System::TArray__1<System::Byte> Buf, const int InBufOff, const int InMaxOff);
#endif /* _WIN64 */
	
protected:
	bool FHitChar;
	bool FHasHalfChar;
	System::Byte FHalfChar;
	int FDecodeLength;
	bool FNullTerminated;
	int FDecodeOff;
	Data::Dbxplatform::TDBXWideChars FDecodeBuf;
	bool FAddQuotes;
	
private:
	bool FPreventGrowth;
	
public:
	__property int DecodeOff = {read=FDecodeOff, nodefault};
	__property Data::Dbxplatform::TDBXWideChars DecodeBuf = {read=FDecodeBuf};
	__property bool PreventGrowth = {write=FPreventGrowth, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDBXCharDecoder() : System::TObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXColumnFlags : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	/* TObject.Create */ inline __fastcall TDBXColumnFlags() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXColumnFlags() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXFieldHeader : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Byte FNullValue = System::Byte(0x80);
	
	static const System::Byte FAssignedNull = System::Byte(0xc0);
	
	static const System::Byte FNullMask = System::Byte(0xc0);
	
	static const System::Byte FPositive = System::Byte(0x40);
	
	static const System::Byte FNullTermStringField = System::Byte(0x0);
	
	static const System::Byte FTinyField = System::Byte(0x20);
	
	static const System::Byte FBigField = System::Byte(0x10);
	
	static const System::Byte FJSONField = System::Byte(0x40);
	
	static const System::Byte FCallbackField = System::Byte(0x2);
	
	static const System::Byte FBlobHeader = System::Byte(0x8);
	
	static const System::Byte FBlobRefHeader = System::Byte(0xc);
	
	static const System::Byte FBlobMask = System::Byte(0x78);
	
	static const System::Int8 FTinyHeaderLength = System::Int8(0x1);
	
	static const System::Int8 FNullTermLength = System::Int8(0x4);
	
	static const System::Int8 FOldNullTermLength = System::Int8(0x2);
	
	static const System::Int8 FJSONBlockLength = System::Int8(0x5);
	
	static const System::Int8 FNullTermOverHead = System::Int8(0x5);
	
	static const System::Int8 FOldNullTermOverHead = System::Int8(0x3);
	
	static const System::Int8 FTinyHeaderLengthMask = System::Int8(0x1f);
	
	static const System::Int8 FBigHeaderLength = System::Int8(0x3);
	
	static const System::Int8 FSmallBlobHeaderLength = System::Int8(0x5);
	
	static const System::Int8 FMaxHeaderLength = System::Int8(0xe);
	
public:
	/* TObject.Create */ inline __fastcall TDBXFieldHeader() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXFieldHeader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXFieldPacker : public System::TObject
{
	typedef System::TObject inherited;
	
public:
#ifndef _WIN64
	static int __fastcall UnpackInt(const System::DynamicArray<System::Byte> Buf, const int InOffset);
	static void __fastcall PackInt(const System::DynamicArray<System::Byte> Buf, const int InOffset, const int IVal);
	static int __fastcall RepackRealForIndex(const System::DynamicArray<System::Byte> SourceBuf, const int InSourceOff, const System::DynamicArray<System::Byte> DestBuf, const int InDestOff, const int aType);
	static __int64 __fastcall UnpackDoubleAsInt64(const System::DynamicArray<System::Byte> Buf, const int InOffset);
	static double __fastcall UnpackDouble(const System::DynamicArray<System::Byte> Buf, const int Offset);
	static int __fastcall PackDouble(const System::DynamicArray<System::Byte> Buf, const int InOffset, const double DValue, const bool ForIndex);
	static float __fastcall UnpackFloat(const System::DynamicArray<System::Byte> Buf, const int InOffset);
	static int __fastcall PackFloat(const System::DynamicArray<System::Byte> Buf, const int InOffset, const float FValue, const bool ForIndex);
	static int __fastcall PackAsciiShort(const System::DynamicArray<System::Byte> Buf, const int InOffset, const int InSVal, const bool Compact);
	static int __fastcall PackAsciiInt(const System::DynamicArray<System::Byte> Buf, const int InOffset, const int InIVal, const bool Compact);
	static int __fastcall PackAsciiLong(const System::DynamicArray<System::Byte> Buf, const int InOffset, const __int64 InLVal, const bool Compact);
	static int __fastcall PackStringHeader(const System::DynamicArray<System::Byte> Buffer, const int InOff, const int Count);
	static short __fastcall UnpackAsciiShort(const System::DynamicArray<System::Byte> Buf, const int InOffset);
	static int __fastcall UnpackAsciiInt(const System::DynamicArray<System::Byte> Buf, const int InOffset);
	static __int64 __fastcall UnpackAsciiLong(const System::DynamicArray<System::Byte> Buf, const int InOffset);
	static int __fastcall GetBlobHeaderLength(const System::DynamicArray<System::Byte> Buffer, const int Off);
	static int __fastcall GetBlobLength(const System::DynamicArray<System::Byte> Buffer, const int Off);
	static int __fastcall PackBigDecimal(const System::DynamicArray<System::Byte> Buf, const int InOffset, const System::DynamicArray<System::Byte> Bytes, const int InScale, const int Signum, const int InMaxWidth, const int Precision, const bool Compact);
	static System::DynamicArray<System::Byte> __fastcall UnpackBigDecimal(const System::DynamicArray<System::Byte> Buf, const int InOffset, const System::DynamicArray<System::Byte> InDest, const Data::Dbxplatform::TDBXInt32s ReturnLength);
#else /* _WIN64 */
	static int __fastcall UnpackInt(const System::TArray__1<System::Byte> Buf, const int InOffset);
	static void __fastcall PackInt(const System::TArray__1<System::Byte> Buf, const int InOffset, const int IVal);
	static int __fastcall RepackRealForIndex(const System::TArray__1<System::Byte> SourceBuf, const int InSourceOff, const System::TArray__1<System::Byte> DestBuf, const int InDestOff, const int aType);
	static __int64 __fastcall UnpackDoubleAsInt64(const System::TArray__1<System::Byte> Buf, const int InOffset);
	static double __fastcall UnpackDouble(const System::TArray__1<System::Byte> Buf, const int Offset);
	static int __fastcall PackDouble(const System::TArray__1<System::Byte> Buf, const int InOffset, const double DValue, const bool ForIndex);
	static float __fastcall UnpackFloat(const System::TArray__1<System::Byte> Buf, const int InOffset);
	static int __fastcall PackFloat(const System::TArray__1<System::Byte> Buf, const int InOffset, const float FValue, const bool ForIndex);
	static int __fastcall PackAsciiShort(const System::TArray__1<System::Byte> Buf, const int InOffset, const int InSVal, const bool Compact);
	static int __fastcall PackAsciiInt(const System::TArray__1<System::Byte> Buf, const int InOffset, const int InIVal, const bool Compact);
	static int __fastcall PackAsciiLong(const System::TArray__1<System::Byte> Buf, const int InOffset, const __int64 InLVal, const bool Compact);
	static int __fastcall PackStringHeader(const System::TArray__1<System::Byte> Buffer, const int InOff, const int Count);
	static short __fastcall UnpackAsciiShort(const System::TArray__1<System::Byte> Buf, const int InOffset);
	static int __fastcall UnpackAsciiInt(const System::TArray__1<System::Byte> Buf, const int InOffset);
	static __int64 __fastcall UnpackAsciiLong(const System::TArray__1<System::Byte> Buf, const int InOffset);
	static int __fastcall GetBlobHeaderLength(const System::TArray__1<System::Byte> Buffer, const int Off);
	static int __fastcall GetBlobLength(const System::TArray__1<System::Byte> Buffer, const int Off);
	static int __fastcall PackBigDecimal(const System::TArray__1<System::Byte> Buf, const int InOffset, const System::TArray__1<System::Byte> Bytes, const int InScale, const int Signum, const int InMaxWidth, const int Precision, const bool Compact);
	static System::TArray__1<System::Byte> __fastcall UnpackBigDecimal(const System::TArray__1<System::Byte> Buf, const int InOffset, const System::TArray__1<System::Byte> InDest, const Data::Dbxplatform::TDBXInt32s ReturnLength);
#endif /* _WIN64 */
	
protected:
#ifndef _WIN64
	static void __fastcall ComplementIntValue(const System::DynamicArray<System::Byte> Buf);
#else /* _WIN64 */
	static void __fastcall ComplementIntValue(const System::TArray__1<System::Byte> Buf);
#endif /* _WIN64 */
public:
	/* TObject.Create */ inline __fastcall TDBXFieldPacker() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXFieldPacker() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXJSonError : public Data::Dbxcommon::TDBXError
{
	typedef Data::Dbxcommon::TDBXError inherited;
	
public:
	__fastcall TDBXJSonError(const int ErrorCode, const System::UnicodeString Message, System::Sysutils::Exception* const Ex);
	
private:
	int FJSonErrorCode;
	
public:
	__property int JSonErrorCode = {read=FJSonErrorCode, nodefault};
	
private:
	static const System::Int8 FSerialVersionUID = System::Int8(0x1);
	
public:
	/* Exception.CreateFmt */ inline __fastcall TDBXJSonError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Data::Dbxcommon::TDBXError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall TDBXJSonError(NativeUInt Ident)/* overload */ : Data::Dbxcommon::TDBXError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall TDBXJSonError(System::PResStringRec ResStringRec)/* overload */ : Data::Dbxcommon::TDBXError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall TDBXJSonError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Data::Dbxcommon::TDBXError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall TDBXJSonError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Data::Dbxcommon::TDBXError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall TDBXJSonError(const System::UnicodeString Msg, int AHelpContext) : Data::Dbxcommon::TDBXError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall TDBXJSonError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Data::Dbxcommon::TDBXError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDBXJSonError(NativeUInt Ident, int AHelpContext)/* overload */ : Data::Dbxcommon::TDBXError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDBXJSonError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Data::Dbxcommon::TDBXError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDBXJSonError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Data::Dbxcommon::TDBXError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDBXJSonError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Data::Dbxcommon::TDBXError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~TDBXJSonError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXJSonErrorCodes : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 ServerError = System::Int8(0x1);
	
	static const System::Int8 ParseError = System::Int8(0x2);
	
	static const System::Int8 BadCall = System::Int8(0x3);
	
	static const System::Int8 MemberOutOfSequence = System::Int8(0x4);
	
	static const System::Int8 ServiceError = System::Int8(0x5);
	
	static const System::Int8 ProcedureNotFound = System::Int8(0x7);
	
public:
	/* TObject.Create */ inline __fastcall TDBXJSonErrorCodes() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXJSonErrorCodes() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDBXJSonStreamReader : /*[[sealed]]*/ public System::TObject
{
	typedef System::TObject inherited;
	
public:
	bool __fastcall HasMoreBytes();
	int __fastcall Next()/* overload */;
	void __fastcall SkipToEndOfObject();
	void __fastcall SkipToEndOfArray();
	int __fastcall ReadParams();
	void __fastcall UnexpectedToken(const int ExpectedToken);
	int __fastcall Next(const int ExpectedToken)/* overload */;
	int __fastcall NextValueSeparator();
	int __fastcall ReadIntResultObject();
	void __fastcall NextResultObjectStart();
	void __fastcall ReadErrorBody();
	int __fastcall ReadMethod();
#ifndef _WIN64
	void __fastcall FillBuffer(const System::DynamicArray<System::Byte> Bytes)/* overload */;
	void __fastcall ReadDataBytes(const System::DynamicArray<System::Byte> Buffer, const int InReadOff, const int InCount);
#else /* _WIN64 */
	void __fastcall FillBuffer(const System::TArray__1<System::Byte> Bytes)/* overload */;
	void __fastcall ReadDataBytes(const System::TArray__1<System::Byte> Buffer, const int InReadOff, const int InCount);
#endif /* _WIN64 */
	bool __fastcall ReadBoolean();
	int __fastcall ReadInt();
#ifndef _WIN64
	__int64 __fastcall GetBytes(const System::DynamicArray<System::Byte> Buffer, const __int64 Offset, const __int64 Count);
#else /* _WIN64 */
	__int64 __fastcall GetBytes(const System::TArray__1<System::Byte> Buffer, const __int64 Offset, const __int64 Count);
#endif /* _WIN64 */
	System::Byte __fastcall ReadByte();
	short __fastcall ReadShort();
	__int64 __fastcall ReadLong();
	float __fastcall ReadFloat();
	double __fastcall ReadDouble();
	void __fastcall Open();
	void __fastcall Close();
	System::UnicodeString __fastcall ReadString();
	int __fastcall ReadStringCode();
	bool __fastcall GetBooleanValue();
	__fastcall virtual ~TDBXJSonStreamReader();
	
protected:
	int __fastcall NextNumber();
	int __fastcall NextString()/* overload */;
	__int64 __fastcall GetByteLength();
	System::UnicodeString __fastcall GetStringValue();
	bool __fastcall IsConnectionLost();
	void __fastcall GrowCharBuffer();
	void __fastcall GrowByteBuffer();
	void __fastcall CreateBuffers();
	
private:
	void __fastcall SkipString();
	int __fastcall ReadBinaryInt();
	void __fastcall NextDataStoreHeader();
	void __fastcall UnexpectedByte(const System::Byte UnexpectedByte);
	System::UnicodeString __fastcall TokenToString(const int Token);
	void __fastcall UnexpectedString(const System::UnicodeString ExpectedString);
	int __fastcall NextMethod();
	void __fastcall ParseStringCode();
	void __fastcall ParseMetadataValue();
	int __fastcall NextColon();
	int __fastcall NextVersion();
	int __fastcall NextString(const System::UnicodeString ExpectedString, const int Offset, const int Count)/* overload */;
	int __fastcall HexToDecimal(const System::Byte Value);
	int __fastcall NextString(const int StartPosition)/* overload */;
	System::UnicodeString __fastcall BytesToString(const int Count, const int Offset = 0x0);
	void __fastcall TraceRead();
	void __fastcall ReadError();
	void __fastcall FillBuffer()/* overload */;
	
protected:
	int FToken;
	int FStringCode;
	System::UnicodeString FStringValue;
	__int64 FLongValue;
	double FDoubleValue;
	bool FBooleanValue;
	Data::Dbxplatform::TDBXWideChars FCharBuffer;
	int FCharBufferSize;
	int FCharBufferCount;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FByteBuffer;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FByteBuffer;
#endif /* _WIN64 */
	int FByteBufferSize;
	int FByteBufferCount;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FReadBuffer;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FReadBuffer;
#endif /* _WIN64 */
	int FReadPosition;
	int FReadLastPosition;
	Data::Dbxtransport::TDbxChannel* FChannel;
	
private:
	Data::Dbxcommon::TDBXContext* FContext;
	int FReadBufferSize;
	
public:
	__property __int64 ByteLength = {read=GetByteLength};
	__property Data::Dbxtransport::TDbxChannel* DbxChannel = {read=FChannel, write=FChannel};
	__property int StringCode = {read=FStringCode, nodefault};
	__property int Token = {read=FToken, nodefault};
	__property System::UnicodeString StringValue = {read=GetStringValue};
	__property __int64 LongValue = {read=FLongValue};
	__property double DoubleValue = {read=FDoubleValue};
	__property int ReadBufferSize = {read=FReadBufferSize, write=FReadBufferSize, nodefault};
	__property Data::Dbxcommon::TDBXContext* Context = {read=FContext};
	__property Data::Dbxcommon::TDBXContext* DbxContext = {read=FContext, write=FContext};
	__property bool ConnectionLost = {read=IsConnectionLost, nodefault};
	
private:
	#define TDBXJSonStreamReader_TrueString L"true"
	
	#define TDBXJSonStreamReader_FalseString L"false"
	
	#define TDBXJSonStreamReader_NullString L"null"
	
	#define TDBXJSonStreamReader_MethodString L"\"method\""
	
	#define TDBXJSonStreamReader_MetadataString L"\"metadata\""
	
	#define TDBXJSonStreamReader_ParamsString L"\"params\""
	
	#define TDBXJSonStreamReader_ResultString L"\"result\""
	
	#define TDBXJSonStreamReader_ErrorString L"\"error\""
	
public:
	/* TObject.Create */ inline __fastcall TDBXJSonStreamReader() : System::TObject() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXJSonStreamWriter : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall TDBXJSonStreamWriter();
	void __fastcall WriteConnectObjectStart();
	void __fastcall WriteHandleObject(const int Handle);
	void __fastcall WriteDisconnectObject(const int ConnectionHandle);
	void __fastcall WriteTxBegin(const int Isolation);
	void __fastcall WriteTxEnd(const bool Commit, const int Txid);
	void __fastcall WriteClientMoreBlobObject(const int CommandHandle, const int RowHandle, const int BlobHandle, const __int64 Row, const int Ordinal, const bool IsOutParameter);
	void __fastcall WriteServerMoreBlobObject(const int CommandHandle, const int RowHandle, const int IBlobHandle, const __int64 Row, const int Ordinal);
	void __fastcall WriteCommandCloseObject(const int CommandHandle);
	void __fastcall WriteReaderCloseObject(const int ReaderHandle, const int CommandHandle);
	void __fastcall WriteTableObjectStart();
	void __fastcall WriteColumnsObjectStart();
	void __fastcall WriteParameterMetadataStart();
	void __fastcall WritePrepareStart(const int CommandHandle, const bool Updateable, const System::UnicodeString CommandType, const System::UnicodeString Command);
	void __fastcall WriteExecuteStart();
	void __fastcall WriteExecuteFieldsObject(const int CommandHandle, const bool Updateable, const System::UnicodeString CommandType, const System::UnicodeString Command);
	void __fastcall WriteParametersObjectStart(const int Count);
	void __fastcall WriteParameter(const int DataType, const int SubType, const int ParameterDirection, const int Precision, const int Scale, const System::UnicodeString Name, const int ChildPosition, const int Size);
	void __fastcall WriteFieldsObjectStart();
	void __fastcall WriteExecute(const int CommandHandle);
	void __fastcall WriteResultVoidObject();
	void __fastcall WriteResultObjectStart();
	void __fastcall WriteSessionObjectStart();
	void __fastcall WriteRowsObjectStart();
	void __fastcall WriteDataObjectStart();
#ifndef _WIN64
	void __fastcall WriteDataObject(const System::DynamicArray<System::Byte> Data, const int Count)/* overload */;
#else /* _WIN64 */
	void __fastcall WriteDataObject(const System::TArray__1<System::Byte> Data, const int Count)/* overload */;
#endif /* _WIN64 */
	int __fastcall CalcRowBufferSize();
	bool __fastcall WriteDataObject(Data::Dbxcommon::TDBXStreamReader* const Reader)/* overload */;
	void __fastcall WriteClientNextObject(const int RowHandle, const __int64 Position, const int CommandHandle);
	void __fastcall WriteServerNextObject(const int RowHandle, const __int64 Position, const int CommandHandle);
	void __fastcall WriteNextResultObject(const int Handle);
	void __fastcall WriteVendorProperty(const System::UnicodeString PropertyName);
	void __fastcall WriteResultEnd();
	void __fastcall WriteResultObject(const __int64 Value);
	void __fastcall WriteRpcError(const System::UnicodeString Name, const int ErrorCode, const System::UnicodeString Message, const Data::Dbxplatform::TDBXStringArray NameValuePairs);
	void __fastcall WriteNamedString(const System::UnicodeString Name, const System::UnicodeString Value);
	void __fastcall WriteObjectStart();
	void __fastcall WriteObjectEnd();
	void __fastcall WriteArrayStart();
	void __fastcall WriteArrayEnd();
	void __fastcall WriteParamsStart();
	void __fastcall WriteValueSeparator();
	void __fastcall WriteNameSeparator();
#ifndef _WIN64
	void __fastcall WriteDataBytes(const System::DynamicArray<System::Byte> SourceBytes, const int InSourceOffset, const int InCount);
#else /* _WIN64 */
	void __fastcall WriteDataBytes(const System::TArray__1<System::Byte> SourceBytes, const int InSourceOffset, const int InCount);
#endif /* _WIN64 */
	void __fastcall WriteString(const System::UnicodeString Chars);
	void __fastcall Flush();
	void __fastcall FlushFullBuffer();
	void __fastcall WriteInt(const int InData);
	void __fastcall WriteByte(const System::Byte Data);
	void __fastcall WriteSpace();
	void __fastcall WriteShort(const short Data);
	void __fastcall WriteLong(const __int64 InData);
	void __fastcall WriteFloat(const float Data);
	void __fastcall WriteDouble(const double Data);
	void __fastcall WriteBoolean(const bool Data);
	void __fastcall WriteNull();
	void __fastcall WriteMetadata(System::Json::TJSONObject* const Data);
	void __fastcall WriteCallback(System::Json::TJSONValue* const Data);
	void __fastcall WriteCallbackResponse(System::Json::TJSONValue* const Data);
	void __fastcall WriteSignature();
	void __fastcall Open();
	void __fastcall Close();
	void __fastcall Skip(const int Count);
	__fastcall virtual ~TDBXJSonStreamWriter();
	
protected:
	bool __fastcall IsClosed();
	bool __fastcall IsConnectionLost();
	virtual void __fastcall CreateBuffers();
	
private:
	void __fastcall WriteCommandFields(const int CommandHandle, const bool Updateable, const System::UnicodeString CommandType, const System::UnicodeString Command);
#ifndef _WIN64
	void __fastcall WriteBytes(const System::DynamicArray<System::Byte> Bytes);
#else /* _WIN64 */
	void __fastcall WriteBytes(const System::TArray__1<System::Byte> Bytes);
#endif /* _WIN64 */
	void __fastcall TraceWrite(const int Count);
	
public:
	static int ProtocolVersion2;
	static int ProtocolVersion;
	
protected:
	int FWriteBufferSize;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FWriteBuffer;
	System::DynamicArray<System::Byte> FDecimalBuffer;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FWriteBuffer;
	System::TArray__1<System::Byte> FDecimalBuffer;
#endif /* _WIN64 */
	int FWriteBufferPosition;
	int FWriteCount;
	Data::Dbxtransport::TDbxChannel* FChannel;
	
private:
#ifndef _WIN64
	static System::DynamicArray<System::Byte> Hex;
	static System::DynamicArray<System::Byte> MethodStart;
	static System::DynamicArray<System::Byte> ParamsStart;
	static System::DynamicArray<System::Byte> Connect;
	static System::DynamicArray<System::Byte> Disconnect;
	static System::DynamicArray<System::Byte> Prepare;
	static System::DynamicArray<System::Byte> Parameters;
	static System::DynamicArray<System::Byte> ParameterMetadataStart;
	static System::DynamicArray<System::Byte> Execute;
	static System::DynamicArray<System::Byte> CommandClose;
	static System::DynamicArray<System::Byte> ReaderClose;
	static System::DynamicArray<System::Byte> ResultStart;
	static System::DynamicArray<System::Byte> ErrorStart;
	static System::DynamicArray<System::Byte> CodeLabel;
	static System::DynamicArray<System::Byte> MessageLabel;
	static System::DynamicArray<System::Byte> NullValue;
	static System::DynamicArray<System::Byte> TrueValue;
	static System::DynamicArray<System::Byte> FalseValue;
	static System::DynamicArray<System::Byte> ColumnsStart;
	static System::DynamicArray<System::Byte> TableStart;
	static System::DynamicArray<System::Byte> SessionStart;
	static System::DynamicArray<System::Byte> RowsStart;
	static System::DynamicArray<System::Byte> DataStart;
	static System::DynamicArray<System::Byte> Next;
	static System::DynamicArray<System::Byte> NextStart;
	static System::DynamicArray<System::Byte> HandleStart;
	static System::DynamicArray<System::Byte> FieldsStart;
	static System::DynamicArray<System::Byte> Txbegin;
	static System::DynamicArray<System::Byte> Txend;
	static System::DynamicArray<System::Byte> MoreBlob;
	static System::DynamicArray<System::Byte> MoreBlobStart;
	static System::DynamicArray<System::Byte> NextResult;
	static System::DynamicArray<System::Byte> VendorProperty;
	static System::DynamicArray<System::Byte> CallbackStart;
	static System::DynamicArray<System::Byte> MetadataStart;
#else /* _WIN64 */
	static System::TArray__1<System::Byte> Hex;
	static System::TArray__1<System::Byte> MethodStart;
	static System::TArray__1<System::Byte> ParamsStart;
	static System::TArray__1<System::Byte> Connect;
	static System::TArray__1<System::Byte> Disconnect;
	static System::TArray__1<System::Byte> Prepare;
	static System::TArray__1<System::Byte> Parameters;
	static System::TArray__1<System::Byte> ParameterMetadataStart;
	static System::TArray__1<System::Byte> Execute;
	static System::TArray__1<System::Byte> CommandClose;
	static System::TArray__1<System::Byte> ReaderClose;
	static System::TArray__1<System::Byte> ResultStart;
	static System::TArray__1<System::Byte> ErrorStart;
	static System::TArray__1<System::Byte> CodeLabel;
	static System::TArray__1<System::Byte> MessageLabel;
	static System::TArray__1<System::Byte> NullValue;
	static System::TArray__1<System::Byte> TrueValue;
	static System::TArray__1<System::Byte> FalseValue;
	static System::TArray__1<System::Byte> ColumnsStart;
	static System::TArray__1<System::Byte> TableStart;
	static System::TArray__1<System::Byte> SessionStart;
	static System::TArray__1<System::Byte> RowsStart;
	static System::TArray__1<System::Byte> DataStart;
	static System::TArray__1<System::Byte> Next;
	static System::TArray__1<System::Byte> NextStart;
	static System::TArray__1<System::Byte> HandleStart;
	static System::TArray__1<System::Byte> FieldsStart;
	static System::TArray__1<System::Byte> Txbegin;
	static System::TArray__1<System::Byte> Txend;
	static System::TArray__1<System::Byte> MoreBlob;
	static System::TArray__1<System::Byte> MoreBlobStart;
	static System::TArray__1<System::Byte> NextResult;
	static System::TArray__1<System::Byte> VendorProperty;
	static System::TArray__1<System::Byte> CallbackStart;
	static System::TArray__1<System::Byte> MetadataStart;
#endif /* _WIN64 */
	
public:
	__property bool Closed = {read=IsClosed, nodefault};
	__property Data::Dbxtransport::TDbxChannel* DbxChannel = {write=FChannel};
	__property int WriteBufferSize = {read=FWriteBufferSize, write=FWriteBufferSize, nodefault};
#ifndef _WIN64
	__property System::DynamicArray<System::Byte> Buffer = {read=FWriteBuffer};
#else /* _WIN64 */
	__property System::TArray__1<System::Byte> Buffer = {read=FWriteBuffer};
#endif /* _WIN64 */
	__property int BufferPosition = {read=FWriteBufferPosition, nodefault};
	__property bool ConnectionLost = {read=IsConnectionLost, nodefault};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDBXRowBlobStreamReader : public Data::Dbxcommon::TDBXStreamReader
{
	typedef Data::Dbxcommon::TDBXStreamReader inherited;
	
public:
	void __fastcall Init(const bool IsBlobHeader, const __int64 Size, const int BufferSize);
#ifndef _WIN64
	void __fastcall Store(const System::DynamicArray<System::Byte> InBuffer, const int InOffset, const int Count)/* overload */;
	virtual int __fastcall Read(const System::DynamicArray<System::Byte> Buf, const int InOffset, const int InSize);
#else /* _WIN64 */
	void __fastcall Store(const System::TArray__1<System::Byte> InBuffer, const int InOffset, const int Count)/* overload */;
	virtual int __fastcall Read(const System::TArray__1<System::Byte> Buf, const int InOffset, const int InSize);
#endif /* _WIN64 */
	virtual bool __fastcall Eos();
	virtual __int64 __fastcall Size();
	virtual void __fastcall Close();
	__fastcall virtual ~TDBXRowBlobStreamReader();
	
private:
	void __fastcall InitBufferTo(const int BufferSize);
	void __fastcall Store(const int Count)/* overload */;
	TDBXJSonStreamReader* FDbxStreamReader;
	TDBXJSonStreamWriter* FDbxStreamWriter;
	Data::Dbxplatform::TDBXInt32s FCommandHandle;
	int FRowHandle;
	int FBlobHandle;
	int FOrdinal;
	__int64 FRow;
	bool FClient;
	bool FParameterBuffer;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FBuffer;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FBuffer;
#endif /* _WIN64 */
	int FBufferBytes;
	int FBufferOffset;
	bool FHasMoreData;
	bool FEos;
	__int64 FKnownSize;
	
public:
#ifndef _WIN64
	__property System::DynamicArray<System::Byte> Buffer = {read=FBuffer};
#else /* _WIN64 */
	__property System::TArray__1<System::Byte> Buffer = {read=FBuffer};
#endif /* _WIN64 */
	__property TDBXJSonStreamReader* StreamReader = {write=FDbxStreamReader};
	__property TDBXJSonStreamWriter* StreamWriter = {write=FDbxStreamWriter};
	__property int BlobHandle = {write=FBlobHandle, nodefault};
	__property int Ordinal = {write=FOrdinal, nodefault};
	__property __int64 Row = {write=FRow};
	__property bool Client = {write=FClient, nodefault};
	__property bool ParameterBuffer = {read=FParameterBuffer, write=FParameterBuffer, nodefault};
	__property Data::Dbxplatform::TDBXInt32s CommandHandle = {read=FCommandHandle, write=FCommandHandle};
	
protected:
	__property int RowHandle = {read=FRowHandle, write=FRowHandle, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDBXRowBlobStreamReader() : Data::Dbxcommon::TDBXStreamReader() { }
	
};


class PASCALIMPLEMENTATION TDBXRowBuffer : public TDBXBinaryStream
{
	typedef TDBXBinaryStream inherited;
	
public:
	__fastcall TDBXRowBuffer();
	__fastcall virtual ~TDBXRowBuffer();
	bool __fastcall NextRow();
	bool __fastcall GoToRow(const int Row);
	void __fastcall GoToField(const int Ordinal);
	int __fastcall ReadParameterBlobSize();
	int __fastcall ReadReaderBlobSize();
#ifndef _WIN64
	void __fastcall ReadBytes(const System::DynamicArray<System::Byte> DestBuf, const int DestOff, const int Count);
#else /* _WIN64 */
	void __fastcall ReadBytes(const System::TArray__1<System::Byte> DestBuf, const int DestOff, const int Count);
#endif /* _WIN64 */
	bool __fastcall ReadNull();
	void __fastcall ReadCallback();
	int __fastcall ReadEncodedStringLength();
	int __fastcall ReadChars(const int RowHandle, const Data::Dbxplatform::TDBXWideChars CharBuf, const int MaxChars);
#ifndef _WIN64
	int __fastcall ReadInlineAnsiChars(const int RowHandle, const System::DynamicArray<System::Byte> ByteBuf, const int MaxChars);
#else /* _WIN64 */
	int __fastcall ReadInlineAnsiChars(const int RowHandle, const System::TArray__1<System::Byte> ByteBuf, const int MaxChars);
#endif /* _WIN64 */
	System::UnicodeString __fastcall ReadString(const int RowHandle);
#ifndef _WIN64
	int __fastcall ReadStringBytes(const int RowHandle, const System::DynamicArray<System::Byte> ByteBuf, const int Offset)/* overload */;
	int __fastcall ReadAnsiStringBytes(const int RowHandle, const System::DynamicArray<System::Byte> ByteBuf, const int Offset);
	System::DynamicArray<System::Byte> __fastcall ReadStringBytes(const int RowHandle)/* overload */;
#else /* _WIN64 */
	int __fastcall ReadStringBytes(const int RowHandle, const System::TArray__1<System::Byte> ByteBuf, const int Offset)/* overload */;
	int __fastcall ReadAnsiStringBytes(const int RowHandle, const System::TArray__1<System::Byte> ByteBuf, const int Offset);
	System::TArray__1<System::Byte> __fastcall ReadStringBytes(const int RowHandle)/* overload */;
#endif /* _WIN64 */
	void __fastcall WriteBoolean(const bool Data);
	void __fastcall WriteByte(const System::Byte Data);
	void __fastcall WriteShort(const short Data);
	void __fastcall WriteInt32(const int Data);
	void __fastcall WriteNull();
	void __fastcall WriteCallback();
	int __fastcall WriteBytes(Data::Dbxcommon::TDBXStreamReader* const Reader);
	int __fastcall PrepareJSONByteBlock(const int EstimatedSize);
	void __fastcall EncodeJSONByteBlockSize(const int Size);
	int __fastcall DecodeJSONByteBlockSize();
	int __fastcall JsonByteBlockOffset();
	void __fastcall WriteInt64(const __int64 Data);
	void __fastcall WriteDouble(const double Data);
	void __fastcall WriteSingle(const float Data);
	void __fastcall WriteTimestamp(const __int64 TimeValue, const int Nanos);
	bool __fastcall WriteString(const System::UnicodeString Data);
	void __fastcall Post();
	void __fastcall Cancel();
	void __fastcall ReadDataBytes();
	Data::Dbxcommon::TDBXStreamReader* __fastcall ReadBlobStreamReader(const int RowHandle);
	
protected:
	void __fastcall SetPreventDecoderGrowth(const bool PreventGrowth);
	virtual void __fastcall MakePositionValid();
	bool __fastcall IsNull();
	bool __fastcall IsCallback();
	bool __fastcall IsLastParameterBlobSegment();
	bool __fastcall IsBlobHeader();
	int __fastcall GetEncodedStringLength();
	int __fastcall GetStringBytesLength();
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall GetOverflowStringBytes();
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall GetOverflowStringBytes();
#endif /* _WIN64 */
	void __fastcall SetReadSize(const int Size);
	virtual void __fastcall SetDbxStreamReader(TDBXJSonStreamReader* const DbxStreamReader);
	virtual void __fastcall SetDbxStreamWriter(TDBXJSonStreamWriter* const DbxStreamWriter);
	
private:
	void __fastcall GrowRowOffsets();
	int __fastcall AvailableInline();
	void __fastcall InitRowBlobStreamReader(TDBXRowBlobStreamReader* const Reader, const int RowHandle);
	TDBXRowBlobStreamReader* __fastcall GetRowBlobStreamReader(const int RowHandle);
	TDBXRowBlobStreamReader* FBlobStreamReader;
	bool FClient;
	Data::Dbxplatform::TDBXInt32s FCommandHandle;
	int FBlobId;
	TDBXJSonStreamReader* FDbxStreamReader;
	TDBXJSonStreamWriter* FDbxStreamWriter;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FBytesOverflowBuffer;
	System::DynamicArray<System::Byte> FBlobStringBuffer;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FBytesOverflowBuffer;
	System::TArray__1<System::Byte> FBlobStringBuffer;
#endif /* _WIN64 */
	TDBXStringEncoder* FEncoder;
	TDBXStringDecoder* FDecoder;
	Data::Dbxcommon::TDBXContext* FDbxContext;
	__int64 FCurrentTotalRow;
	int FCurrentRow;
	int FColumnCount;
	int FRowCount;
	Data::Dbxplatform::TDBXInt32s FRowOffsets;
	int FReadSize;
	int FMaxInline;
	bool FParameterBuffer;
	int FLastInlinByteCount;
	bool FHeaderConsumed;
	int FLastHeaderOffset;
	int FLastOrdinal;
	
public:
	__property bool PreventDecoderGrowth = {write=SetPreventDecoderGrowth, nodefault};
	__property bool Null = {read=IsNull, nodefault};
	__property bool Callback = {read=IsCallback, nodefault};
	__property bool LastParameterBlobSegment = {read=IsLastParameterBlobSegment, nodefault};
	__property bool BlobHeader = {read=IsBlobHeader, nodefault};
	__property int EncodedStringLength = {read=GetEncodedStringLength, nodefault};
	__property int StringBytesLength = {read=GetStringBytesLength, nodefault};
#ifndef _WIN64
	__property System::DynamicArray<System::Byte> BcdBuffer = {read=FBigDecimalBuffer};
	__property System::DynamicArray<System::Byte> OverflowStringBytes = {read=GetOverflowStringBytes};
	__property System::DynamicArray<System::Byte> buf = {read=FBuf};
#else /* _WIN64 */
	__property System::TArray__1<System::Byte> BcdBuffer = {read=FBigDecimalBuffer};
	__property System::TArray__1<System::Byte> OverflowStringBytes = {read=GetOverflowStringBytes};
	__property System::TArray__1<System::Byte> buf = {read=FBuf};
#endif /* _WIN64 */
	__property int offset = {read=FOff, nodefault};
	__property int ReadSize = {read=FReadSize, write=SetReadSize, nodefault};
	__property int ColumnCount = {write=FColumnCount, nodefault};
	__property bool Client = {read=FClient, write=FClient, nodefault};
	__property TDBXJSonStreamReader* DbxStreamReader = {write=SetDbxStreamReader};
	__property TDBXJSonStreamWriter* DbxStreamWriter = {write=SetDbxStreamWriter};
	__property TDBXStringEncoder* Encoder = {read=FEncoder};
	__property int MaxInline = {read=FMaxInline, nodefault};
	__property TDBXStringDecoder* Decoder = {read=FDecoder};
	__property bool ParameterBuffer = {read=FParameterBuffer, write=FParameterBuffer, nodefault};
	__property Data::Dbxplatform::TDBXInt32s CommandHandle = {read=FCommandHandle, write=FCommandHandle};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXStringCodes : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 Unknown = System::Int8(0x1);
	
	static const System::Int8 Result = System::Int8(0x2);
	
	static const System::Int8 Error = System::Int8(0x3);
	
	static const System::Int8 Connect = System::Int8(0x4);
	
	static const System::Int8 Disconnect = System::Int8(0x5);
	
	static const System::Int8 Prepare = System::Int8(0x7);
	
	static const System::Int8 Execute = System::Int8(0x8);
	
	static const System::Int8 CommandClose = System::Int8(0x9);
	
	static const System::Int8 ReaderClose = System::Int8(0xa);
	
	static const System::Int8 Rows = System::Int8(0xb);
	
	static const System::Int8 Table = System::Int8(0xc);
	
	static const System::Int8 Columns = System::Int8(0xd);
	
	static const System::Int8 Session = System::Int8(0xe);
	
	static const System::Int8 Data = System::Int8(0xf);
	
	static const System::Int8 Next = System::Int8(0x10);
	
	static const System::Int8 Handle = System::Int8(0x11);
	
	static const System::Int8 Fields = System::Int8(0x12);
	
	static const System::Int8 Parameters = System::Int8(0x13);
	
	static const System::Int8 Txbegin = System::Int8(0x14);
	
	static const System::Int8 Txend = System::Int8(0x15);
	
	static const System::Int8 MoreBlob = System::Int8(0x16);
	
	static const System::Int8 NextResult = System::Int8(0x17);
	
	static const System::Int8 VendorProperty = System::Int8(0x18);
	
	static const System::Int8 Callback = System::Int8(0x19);
	
	static const System::Int8 Metadata = System::Int8(0x1a);
	
public:
	/* TObject.Create */ inline __fastcall TDBXStringCodes() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXStringCodes() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXStringDecoder : public TDBXCharDecoder
{
	typedef TDBXCharDecoder inherited;
	
public:
	void __fastcall InitWideCharsDecoder(const Data::Dbxplatform::TDBXWideChars OutBuf);
	void __fastcall InitByteDecoder()/* overload */;
	void __fastcall InitByteDecoder(const int ExpectedSize)/* overload */;
#ifndef _WIN64
	bool __fastcall DecodeToWideBytes(const System::DynamicArray<System::Byte> InBuf, const int InOff, const System::DynamicArray<System::Byte> OutBuf, const int MaxBytes);
	bool __fastcall DecodeBytes(const System::DynamicArray<System::Byte> InBuf, const int InOff, const int MaxBytes);
	System::DynamicArray<System::Byte> __fastcall ExtractDecodeByteBuffer();
#else /* _WIN64 */
	bool __fastcall DecodeToWideBytes(const System::TArray__1<System::Byte> InBuf, const int InOff, const System::TArray__1<System::Byte> OutBuf, const int MaxBytes);
	bool __fastcall DecodeBytes(const System::TArray__1<System::Byte> InBuf, const int InOff, const int MaxBytes);
	System::TArray__1<System::Byte> __fastcall ExtractDecodeByteBuffer();
#endif /* _WIN64 */
	__fastcall virtual ~TDBXStringDecoder();
	
private:
	void __fastcall GrowDecodeByteBuf();
#ifndef _WIN64
	bool __fastcall DecodeCharsToBytes(const System::DynamicArray<System::Byte> InBuf, const int InOff, const System::DynamicArray<System::Byte> DecodeByteBuf, const int InOutOff, const int InMaxOff);
#else /* _WIN64 */
	bool __fastcall DecodeCharsToBytes(const System::TArray__1<System::Byte> InBuf, const int InOff, const System::TArray__1<System::Byte> DecodeByteBuf, const int InOutOff, const int InMaxOff);
#endif /* _WIN64 */
	int FMaxOff;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FDecodeByteBuf;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FDecodeByteBuf;
#endif /* _WIN64 */
	int FDecodeByteOff;
	int FDecodeByteLength;
	
public:
	__property int DecodeLength = {read=FDecodeLength, nodefault};
	__property int DecodeByteOff = {read=FDecodeByteOff, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDBXStringDecoder() : TDBXCharDecoder() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXStringEncoder : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall TDBXStringEncoder();
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall ExtractEncodeBuffer();
	bool __fastcall Encode(const System::UnicodeString Source, const System::DynamicArray<System::Byte> InDest, const int DestOff, const int InMaxBytes, const bool NullTerm);
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall ExtractEncodeBuffer();
	bool __fastcall Encode(const System::UnicodeString Source, const System::TArray__1<System::Byte> InDest, const int DestOff, const int InMaxBytes, const bool NullTerm);
#endif /* _WIN64 */
	__fastcall virtual ~TDBXStringEncoder();
	
private:
#ifndef _WIN64
	void __fastcall GrowEncodeBufTo(const System::DynamicArray<System::Byte> OldBuf, const int NewLength);
#else /* _WIN64 */
	void __fastcall GrowEncodeBufTo(const System::TArray__1<System::Byte> OldBuf, const int NewLength);
#endif /* _WIN64 */
	
protected:
	int FEncodeLength;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FEncodeBuf;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FEncodeBuf;
#endif /* _WIN64 */
	int FEncodeOff;
	int FReadOff;
	
public:
#ifndef _WIN64
	__property System::DynamicArray<System::Byte> EncodeBuf = {read=FEncodeBuf};
#else /* _WIN64 */
	__property System::TArray__1<System::Byte> EncodeBuf = {read=FEncodeBuf};
#endif /* _WIN64 */
	__property int EncodeOff = {read=FEncodeOff, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXTokens : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 ErrorToken = System::Int8(0x1);
	
	static const System::Int8 ObjectStartToken = System::Int8(0x2);
	
	static const System::Int8 ObjectEndToken = System::Int8(0x3);
	
	static const System::Int8 ArrayStartToken = System::Int8(0x4);
	
	static const System::Int8 ArrayEndToken = System::Int8(0x5);
	
	static const System::Int8 TrueToken = System::Int8(0x6);
	
	static const System::Int8 FalseToken = System::Int8(0x7);
	
	static const System::Int8 NullToken = System::Int8(0x8);
	
	static const System::Int8 NumberStartToken = System::Int8(0x9);
	
	static const System::Int8 NumberEndToken = System::Int8(0x9);
	
	static const System::Int8 StringStartToken = System::Int8(0xa);
	
	static const System::Int8 StringEndToken = System::Int8(0xb);
	
	static const System::Int8 NameSeparatorToken = System::Int8(0xc);
	
	static const System::Int8 ValueSeparatorToken = System::Int8(0xd);
	
public:
	/* TObject.Create */ inline __fastcall TDBXTokens() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTokens() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxstream */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXSTREAM)
using namespace Data::Dbxstream;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxstreamHPP
