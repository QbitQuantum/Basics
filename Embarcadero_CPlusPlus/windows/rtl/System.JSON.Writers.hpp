// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.JSON.Writers.pas' rev: 34.00 (Windows)

#ifndef System_Json_WritersHPP
#define System_Json_WritersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Types.hpp>
#include <System.Rtti.hpp>
#include <System.JSON.hpp>
#include <System.JSON.Types.hpp>
#include <System.JSON.Readers.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Json
{
namespace Writers
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TJsonWriter;
class DELPHICLASS EJsonWriterException;
class DELPHICLASS TASCIIStreamWriter;
class DELPHICLASS TJsonTextWriter;
class DELPHICLASS TJsonObjectWriter;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TJsonWriteState : unsigned char { Error, Closed, Object, Array, Constructor, Property, Start };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonWriter : public System::Json::Types::TJsonFiler
{
	typedef System::Json::Types::TJsonFiler inherited;
	
	
protected:
	enum class DECLSPEC_DENUM TState : unsigned char { Start, Property, ObjectStart, Object, ArrayStart, Array, ConstructorStart, Constructor, Closed, Error };
	
	
private:
	typedef System::DynamicArray<TState> _TJsonWriter__1;
	
	typedef System::DynamicArray<System::DynamicArray<TState> > _TJsonWriter__2;
	
	
protected:
	static System::StaticArray<System::StaticArray<TState, 10>, 8> StateArrayTemplate;
	
private:
	bool FCloseOutput;
	System::Json::Types::TJsonEmptyValueHandling FEmptyValueHandling;
	System::Json::Types::TJsonDateTimeZoneHandling FDateTimeZoneHandling;
	static _TJsonWriter__2 StateArray;
	static System::Rtti::TRttiContext FRttiCtx;
	void __fastcall AutoCompleteAll();
	void __fastcall AutoCompleteClose(System::Json::Types::TJsonContainerType ContainerType);
	System::Json::Types::TJsonToken __fastcall GetCloseTokenForType(System::Json::Types::TJsonContainerType ContainerType);
	void __fastcall WriteConstructorDate(System::Json::Readers::TJsonReader* const Reader);
	System::UnicodeString __fastcall GetContainerPath();
	TJsonWriteState __fastcall GetWriteState();
	__classmethod void __fastcall BuildStateArray();
	
protected:
	TState FCurrentState;
	void __fastcall AutoComplete(System::Json::Types::TJsonToken TokenBeingWritten);
	virtual bool __fastcall GetInsideContainer();
	int __fastcall GetTop();
	System::Json::Types::TJsonContainerType __fastcall GetTopContainer();
	void __fastcall UpdateScopeWithFinishedValue();
	void __fastcall InternalWriteEnd(System::Json::Types::TJsonContainerType Container);
	void __fastcall InternalWritePropertyName(const System::UnicodeString Name);
	void __fastcall InternalWriteStart(System::Json::Types::TJsonToken Token, System::Json::Types::TJsonContainerType Container);
	void __fastcall InternalWriteValue(System::Json::Types::TJsonToken Token);
	void __fastcall InternalWriteComment();
	void __fastcall SetWriteState(System::Json::Types::TJsonToken Token, const System::Rtti::TValue &Value);
	void __fastcall WriteEnd(System::Json::Types::TJsonContainerType ContainerType)/* overload */;
	virtual void __fastcall WriteEnd(const System::Json::Types::TJsonToken Token)/* overload */;
	void __fastcall WriteToken(System::Json::Readers::TJsonReader* const Reader, bool WriteChildren, bool WriteDateConstructorAsDate)/* overload */;
	void __fastcall WriteToken(System::Json::Readers::TJsonReader* const Reader, int InitialDepth, bool WriteChildren, bool WriteDateConstructorAsDate)/* overload */;
	__classmethod void __fastcall WriteValue(TJsonWriter* const Writer, const System::Rtti::TValue &Value)/* overload */;
	virtual void __fastcall OnBeforeWriteToken(System::Json::Types::TJsonToken TokenBeginWriten);
	__fastcall TJsonWriter();
	
private:
	// __classmethod void __fastcall Create@();
	
public:
	__fastcall virtual ~TJsonWriter();
	virtual void __fastcall Rewind();
	virtual void __fastcall Close();
	virtual void __fastcall Flush();
	virtual void __fastcall WriteComment(const System::UnicodeString Comment);
	virtual void __fastcall WriteStartObject();
	virtual void __fastcall WriteEndObject();
	virtual void __fastcall WriteStartArray();
	virtual void __fastcall WriteEndArray();
	virtual void __fastcall WriteStartConstructor(const System::UnicodeString Name);
	virtual void __fastcall WriteEndConstructor();
	virtual void __fastcall WritePropertyName(const System::UnicodeString Name)/* overload */;
	virtual void __fastcall WriteEnd()/* overload */;
	virtual void __fastcall WriteNull();
	virtual void __fastcall WriteRaw(const System::UnicodeString Json);
	virtual void __fastcall WriteRawValue(const System::UnicodeString Json);
	virtual void __fastcall WriteUndefined();
	void __fastcall WriteToken(System::Json::Readers::TJsonReader* const Reader)/* overload */;
	void __fastcall WriteToken(System::Json::Readers::TJsonReader* const Reader, bool WriteChildren)/* overload */;
	virtual void __fastcall WriteValue(const System::UnicodeString Value)/* overload */;
	void __fastcall WriteValue(const char * Value)/* overload */;
	void __fastcall WriteValue(const System::WideChar * Value)/* overload */;
	virtual void __fastcall WriteValue(int Value)/* overload */;
	virtual void __fastcall WriteValue(unsigned Value)/* overload */;
	virtual void __fastcall WriteValue(__int64 Value)/* overload */;
	virtual void __fastcall WriteValue(unsigned __int64 Value)/* overload */;
	virtual void __fastcall WriteValue(float Value)/* overload */;
	virtual void __fastcall WriteValue(double Value)/* overload */;
	virtual void __fastcall WriteValue(System::Extended Value)/* overload */;
	virtual void __fastcall WriteValue(bool Value)/* overload */;
	virtual void __fastcall WriteValue(System::WideChar Value)/* overload */;
	virtual void __fastcall WriteValue(System::Byte Value)/* overload */;
	virtual void __fastcall WriteValue(System::TDateTime Value)/* overload */;
	virtual void __fastcall WriteValue(const GUID &Value)/* overload */;
#ifndef _WIN64
	virtual void __fastcall WriteValue(const System::DynamicArray<System::Byte> Value, System::Json::Types::TJsonBinaryType BinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
#else /* _WIN64 */
	virtual void __fastcall WriteValue(const System::TArray__1<System::Byte> Value, System::Json::Types::TJsonBinaryType BinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall WriteValue(const System::Json::Types::TJsonOid &Value)/* overload */;
	virtual void __fastcall WriteValue(const System::Json::Types::TJsonRegEx &Value)/* overload */;
	virtual void __fastcall WriteValue(const System::Json::Types::TJsonDBRef &Value)/* overload */;
	virtual void __fastcall WriteValue(const System::Json::Types::TJsonCodeWScope &Value)/* overload */;
	virtual void __fastcall WriteMinKey()/* overload */;
	virtual void __fastcall WriteMaxKey()/* overload */;
	virtual void __fastcall WriteValue(const System::Rtti::TValue &Value)/* overload */;
	__property bool CloseOutput = {read=FCloseOutput, write=FCloseOutput, nodefault};
	__property System::UnicodeString ContainerPath = {read=GetContainerPath};
	__property int Top = {read=GetTop, nodefault};
	__property System::Json::Types::TJsonContainerType TopContainer = {read=GetTopContainer, nodefault};
	__property TJsonWriteState WriteState = {read=GetWriteState, nodefault};
	__property System::Json::Types::TJsonEmptyValueHandling EmptyValueHandling = {read=FEmptyValueHandling, write=FEmptyValueHandling, nodefault};
	__property System::Json::Types::TJsonDateTimeZoneHandling DateTimeZoneHandling = {read=FDateTimeZoneHandling, write=FDateTimeZoneHandling, nodefault};
	
private:
	// __classmethod void __fastcall Destroy@();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EJsonWriterException : public System::Json::Types::EJsonException
{
	typedef System::Json::Types::EJsonException inherited;
	
private:
	System::UnicodeString FPath;
	
public:
	__fastcall EJsonWriterException(const System::UnicodeString Msg, System::Sysutils::Exception* const Ex, const System::UnicodeString APath)/* overload */;
	__fastcall EJsonWriterException(TJsonWriter* const Writer, const System::UnicodeString Msg, System::Sysutils::Exception* const Ex)/* overload */;
	__fastcall EJsonWriterException(const System::UnicodeString APath, const System::UnicodeString Msg, System::Sysutils::Exception* const Ex)/* overload */;
	__property System::UnicodeString Path = {read=FPath};
public:
	/* EJsonException.Create */ inline __fastcall EJsonWriterException(const System::UnicodeString Msg, System::Sysutils::Exception* const InnerException)/* overload */ : System::Json::Types::EJsonException(Msg, InnerException) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EJsonWriterException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Json::Types::EJsonException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EJsonWriterException(NativeUInt Ident)/* overload */ : System::Json::Types::EJsonException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EJsonWriterException(System::PResStringRec ResStringRec)/* overload */ : System::Json::Types::EJsonException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EJsonWriterException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Json::Types::EJsonException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EJsonWriterException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Json::Types::EJsonException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EJsonWriterException(const System::UnicodeString Msg, int AHelpContext) : System::Json::Types::EJsonException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EJsonWriterException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Json::Types::EJsonException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJsonWriterException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Json::Types::EJsonException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJsonWriterException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Json::Types::EJsonException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJsonWriterException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Json::Types::EJsonException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJsonWriterException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Json::Types::EJsonException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EJsonWriterException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TASCIIStreamWriter : public System::Classes::TStreamWriter
{
	typedef System::Classes::TStreamWriter inherited;
	
private:
	HIDESBASE void __fastcall Write(System::WideChar * ASrc, int ACount)/* overload */;
	
public:
	__fastcall TASCIIStreamWriter(System::Classes::TStream* Stream, int BufferSize)/* overload */;
	__fastcall TASCIIStreamWriter(const System::UnicodeString Filename, bool Append, int BufferSize)/* overload */;
	virtual void __fastcall Write(bool Value)/* overload */;
	virtual void __fastcall Write(System::WideChar Value)/* overload */;
#ifndef _WIN64
	virtual void __fastcall Write(const System::DynamicArray<System::WideChar> Value)/* overload */;
#else /* _WIN64 */
	virtual void __fastcall Write(const System::TArray__1<System::WideChar> Value)/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall Write(double Value)/* overload */;
	virtual void __fastcall Write(int Value)/* overload */;
	virtual void __fastcall Write(__int64 Value)/* overload */;
	virtual void __fastcall Write(System::TObject* Value)/* overload */;
	virtual void __fastcall Write(float Value)/* overload */;
	virtual void __fastcall Write(const System::UnicodeString Value)/* overload */;
	virtual void __fastcall Write(unsigned Value)/* overload */;
	virtual void __fastcall Write(unsigned __int64 Value)/* overload */;
	virtual void __fastcall Write(const System::UnicodeString Format, System::TVarRec *Args, const int Args_High)/* overload */;
#ifndef _WIN64
	virtual void __fastcall Write(const System::DynamicArray<System::WideChar> Value, int Index, int Count)/* overload */;
#else /* _WIN64 */
	virtual void __fastcall Write(const System::TArray__1<System::WideChar> Value, int Index, int Count)/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall WriteLine()/* overload */;
	virtual void __fastcall WriteLine(bool Value)/* overload */;
	virtual void __fastcall WriteLine(System::WideChar Value)/* overload */;
#ifndef _WIN64
	virtual void __fastcall WriteLine(const System::DynamicArray<System::WideChar> Value)/* overload */;
#else /* _WIN64 */
	virtual void __fastcall WriteLine(const System::TArray__1<System::WideChar> Value)/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall WriteLine(double Value)/* overload */;
	virtual void __fastcall WriteLine(int Value)/* overload */;
	virtual void __fastcall WriteLine(__int64 Value)/* overload */;
	virtual void __fastcall WriteLine(System::TObject* Value)/* overload */;
	virtual void __fastcall WriteLine(float Value)/* overload */;
	virtual void __fastcall WriteLine(const System::UnicodeString Value)/* overload */;
	virtual void __fastcall WriteLine(unsigned Value)/* overload */;
	virtual void __fastcall WriteLine(unsigned __int64 Value)/* overload */;
	virtual void __fastcall WriteLine(const System::UnicodeString Format, System::TVarRec *Args, const int Args_High)/* overload */;
#ifndef _WIN64
	virtual void __fastcall WriteLine(const System::DynamicArray<System::WideChar> Value, int Index, int Count)/* overload */;
#else /* _WIN64 */
	virtual void __fastcall WriteLine(const System::TArray__1<System::WideChar> Value, int Index, int Count)/* overload */;
#endif /* _WIN64 */
public:
	/* TStreamWriter.Create */ inline __fastcall TASCIIStreamWriter(System::Classes::TStream* Stream)/* overload */ : System::Classes::TStreamWriter(Stream) { }
	/* TStreamWriter.Create */ inline __fastcall TASCIIStreamWriter(System::Classes::TStream* Stream, System::Sysutils::TEncoding* Encoding, int BufferSize)/* overload */ : System::Classes::TStreamWriter(Stream, Encoding, BufferSize) { }
	/* TStreamWriter.Create */ inline __fastcall TASCIIStreamWriter(const System::UnicodeString Filename, bool Append)/* overload */ : System::Classes::TStreamWriter(Filename, Append) { }
	/* TStreamWriter.Create */ inline __fastcall TASCIIStreamWriter(const System::UnicodeString Filename, bool Append, System::Sysutils::TEncoding* Encoding, int BufferSize)/* overload */ : System::Classes::TStreamWriter(Filename, Append, Encoding, BufferSize) { }
	/* TStreamWriter.Destroy */ inline __fastcall virtual ~TASCIIStreamWriter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Write(System::WideChar Value, int Count){ System::Classes::TTextWriter::Write(Value, Count); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonTextWriter : public TJsonWriter
{
	typedef TJsonWriter inherited;
	
	
private:
	typedef System::DynamicArray<System::WideChar> _TJsonTextWriter__1;
	
	
private:
	System::Json::Types::TJsonDateFormatHandling FDateFormatHandling;
	System::Sysutils::TFormatSettings FFormatSettings;
	System::Json::Types::TJsonStringEscapeHandling FStringEscapeHandling;
	System::Json::Types::TJsonFloatFormatHandling FFloatFormatHandling;
	System::Json::Types::TJsonFormatting FFormatting;
	System::Classes::TTextWriter* FWriter;
	System::WideChar FIndentChar;
	int FIndentation;
	System::WideChar FQuoteChar;
	bool FQuoteName;
	System::Json::Types::TJsonExtendedJsonMode FExtendedJsonMode;
#ifndef _WIN64
	System::DynamicArray<bool> FCharEscapeFlags;
#else /* _WIN64 */
	System::TArray__1<bool> FCharEscapeFlags;
#endif /* _WIN64 */
	_TJsonTextWriter__1 FWriterBuffer;
	bool FOwnsWriter;
	void __fastcall EnsureBufferSize();
	void __fastcall UpdateCharEscapeFlags();
	void __fastcall WriteValueInternal(const System::UnicodeString Value, System::Json::Types::TJsonToken Token);
	void __fastcall WriteEscapedString(const System::UnicodeString Value, bool Quote);
	void __fastcall SetIndentation(int Value);
	void __fastcall SetQuoteChar(System::WideChar Value);
	void __fastcall SetStringEscapeHandling(System::Json::Types::TJsonStringEscapeHandling Value);
	void __fastcall WriteNumberLong(const System::UnicodeString ANum);
	
protected:
	void __fastcall WriteIndent();
	void __fastcall WriteValueDelimiter();
	void __fastcall WriteIndentSpace();
	virtual void __fastcall WriteEnd(const System::Json::Types::TJsonToken Token)/* overload */;
	virtual void __fastcall OnBeforeWriteToken(System::Json::Types::TJsonToken TokenBeginWritten);
	
public:
	__fastcall TJsonTextWriter(System::Classes::TTextWriter* const TextWriter, bool OwnsWriter)/* overload */;
	__fastcall TJsonTextWriter(System::Classes::TTextWriter* const TextWriter)/* overload */;
	__fastcall TJsonTextWriter(System::Classes::TStream* const Stream)/* overload */;
	__fastcall virtual ~TJsonTextWriter();
	virtual void __fastcall Close();
	virtual void __fastcall Flush();
	virtual void __fastcall WriteComment(const System::UnicodeString Comment);
	virtual void __fastcall WriteNull();
	virtual void __fastcall WritePropertyName(const System::UnicodeString Name)/* overload */;
	HIDESBASE void __fastcall WritePropertyName(const System::UnicodeString Name, bool Escape)/* overload */;
	virtual void __fastcall WriteRaw(const System::UnicodeString Json);
	virtual void __fastcall WriteStartConstructor(const System::UnicodeString Name);
	virtual void __fastcall WriteStartObject();
	virtual void __fastcall WriteStartArray();
	virtual void __fastcall WriteValue(const System::UnicodeString Value)/* overload */;
	virtual void __fastcall WriteValue(int Value)/* overload */;
	virtual void __fastcall WriteValue(unsigned Value)/* overload */;
	virtual void __fastcall WriteValue(__int64 Value)/* overload */;
	virtual void __fastcall WriteValue(unsigned __int64 Value)/* overload */;
	virtual void __fastcall WriteValue(float Value)/* overload */;
	virtual void __fastcall WriteValue(double Value)/* overload */;
	virtual void __fastcall WriteValue(System::Extended Value)/* overload */;
	virtual void __fastcall WriteValue(bool Value)/* overload */;
	virtual void __fastcall WriteValue(System::WideChar Value)/* overload */;
	virtual void __fastcall WriteValue(System::Byte Value)/* overload */;
	virtual void __fastcall WriteValue(System::TDateTime Value)/* overload */;
	virtual void __fastcall WriteValue(const GUID &Value)/* overload */;
#ifndef _WIN64
	virtual void __fastcall WriteValue(const System::DynamicArray<System::Byte> Value, System::Json::Types::TJsonBinaryType BinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
#else /* _WIN64 */
	virtual void __fastcall WriteValue(const System::TArray__1<System::Byte> Value, System::Json::Types::TJsonBinaryType BinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall WriteValue(const System::Json::Types::TJsonOid &Value)/* overload */;
	virtual void __fastcall WriteValue(const System::Json::Types::TJsonRegEx &Value)/* overload */;
	virtual void __fastcall WriteValue(const System::Json::Types::TJsonDBRef &Value)/* overload */;
	virtual void __fastcall WriteValue(const System::Json::Types::TJsonCodeWScope &Value)/* overload */;
	virtual void __fastcall WriteMinKey()/* overload */;
	virtual void __fastcall WriteMaxKey()/* overload */;
	virtual void __fastcall WriteValue(const System::Rtti::TValue &Value)/* overload */;
	virtual void __fastcall WriteUndefined();
	void __fastcall WriteWhitespace(const System::UnicodeString Ws);
	__property System::Classes::TTextWriter* Writer = {read=FWriter};
	__property int Indentation = {read=FIndentation, write=SetIndentation, nodefault};
	__property System::WideChar IndentChar = {read=FIndentChar, write=FIndentChar, nodefault};
	__property System::WideChar QuoteChar = {read=FQuoteChar, write=SetQuoteChar, nodefault};
	__property bool QuoteName = {read=FQuoteName, write=FQuoteName, nodefault};
	__property System::Json::Types::TJsonFormatting Formatting = {read=FFormatting, write=FFormatting, nodefault};
	__property System::Sysutils::TFormatSettings FormatSettings = {read=FFormatSettings, write=FFormatSettings};
	__property System::Json::Types::TJsonStringEscapeHandling StringEscapeHandling = {read=FStringEscapeHandling, write=SetStringEscapeHandling, nodefault};
	__property System::Json::Types::TJsonDateFormatHandling DateFormatHandling = {read=FDateFormatHandling, write=FDateFormatHandling, nodefault};
	__property System::Json::Types::TJsonFloatFormatHandling FloatFormatHandling = {read=FFloatFormatHandling, write=FFloatFormatHandling, nodefault};
	__property System::Json::Types::TJsonExtendedJsonMode ExtendedJsonMode = {read=FExtendedJsonMode, write=FExtendedJsonMode, nodefault};
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  WriteEnd(System::Json::Types::TJsonContainerType ContainerType){ TJsonWriter::WriteEnd(ContainerType); }
	
public:
	inline void __fastcall  WriteEnd(){ TJsonWriter::WriteEnd(); }
	
protected:
	inline void __fastcall  WriteValue(TJsonWriter* const Writer, const System::Rtti::TValue &Value){ TJsonWriter::WriteValue(Writer, Value); }
	
public:
	inline void __fastcall  WriteValue(const char * Value){ TJsonWriter::WriteValue(Value); }
	inline void __fastcall  WriteValue(const System::WideChar * Value){ TJsonWriter::WriteValue(Value); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonObjectWriter : public TJsonWriter
{
	typedef TJsonWriter inherited;
	
private:
	System::Json::Types::TJsonDateFormatHandling FDateFormatHandling;
	System::Json::TJSONAncestor* FRoot;
	System::Generics::Collections::TStack__1<System::Json::TJSONAncestor*>* FContainerStack;
	bool FOwnValue;
	void __fastcall AppendContainer(System::Json::TJSONValue* const JSONValue);
	void __fastcall AppendValue(System::Json::TJSONValue* const JsonValue);
	System::Json::TJSONValue* __fastcall GetContainer();
	void __fastcall SetContainer(System::Json::TJSONValue* const Value);
	
protected:
	virtual void __fastcall WriteEnd(const System::Json::Types::TJsonToken Token)/* overload */;
	
public:
	__fastcall TJsonObjectWriter(bool OwnValue);
	__fastcall virtual ~TJsonObjectWriter();
	virtual void __fastcall Rewind();
	virtual void __fastcall WriteNull();
	virtual void __fastcall WritePropertyName(const System::UnicodeString Name)/* overload */;
	virtual void __fastcall WriteStartConstructor(const System::UnicodeString Name);
	virtual void __fastcall WriteStartObject();
	virtual void __fastcall WriteStartArray();
	virtual void __fastcall WriteRaw(const System::UnicodeString Json);
	virtual void __fastcall WriteRawValue(const System::UnicodeString Json);
	virtual void __fastcall WriteValue(const System::UnicodeString Value)/* overload */;
	virtual void __fastcall WriteValue(int Value)/* overload */;
	virtual void __fastcall WriteValue(unsigned Value)/* overload */;
	virtual void __fastcall WriteValue(__int64 Value)/* overload */;
	virtual void __fastcall WriteValue(unsigned __int64 Value)/* overload */;
	virtual void __fastcall WriteValue(float Value)/* overload */;
	virtual void __fastcall WriteValue(double Value)/* overload */;
	virtual void __fastcall WriteValue(System::Extended Value)/* overload */;
	virtual void __fastcall WriteValue(bool Value)/* overload */;
	virtual void __fastcall WriteValue(System::WideChar Value)/* overload */;
	virtual void __fastcall WriteValue(System::Byte Value)/* overload */;
	virtual void __fastcall WriteValue(System::TDateTime Value)/* overload */;
	virtual void __fastcall WriteValue(const GUID &Value)/* overload */;
#ifndef _WIN64
	virtual void __fastcall WriteValue(const System::DynamicArray<System::Byte> Value, System::Json::Types::TJsonBinaryType BinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
#else /* _WIN64 */
	virtual void __fastcall WriteValue(const System::TArray__1<System::Byte> Value, System::Json::Types::TJsonBinaryType BinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall WriteValue(const System::Json::Types::TJsonOid &Value)/* overload */;
	virtual void __fastcall WriteValue(const System::Json::Types::TJsonRegEx &Value)/* overload */;
	virtual void __fastcall WriteValue(const System::Json::Types::TJsonDBRef &Value)/* overload */;
	virtual void __fastcall WriteValue(const System::Json::Types::TJsonCodeWScope &Value)/* overload */;
	virtual void __fastcall WriteMinKey()/* overload */;
	virtual void __fastcall WriteMaxKey()/* overload */;
	virtual void __fastcall WriteUndefined();
	__property System::Json::TJSONAncestor* JSON = {read=FRoot};
	__property System::Json::TJSONValue* Container = {read=GetContainer, write=SetContainer};
	__property System::Json::Types::TJsonDateFormatHandling DateFormatHandling = {read=FDateFormatHandling, write=FDateFormatHandling, nodefault};
	__property bool OwnValue = {read=FOwnValue, write=FOwnValue, nodefault};
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  WriteEnd(System::Json::Types::TJsonContainerType ContainerType){ TJsonWriter::WriteEnd(ContainerType); }
	
public:
	inline void __fastcall  WriteEnd(){ TJsonWriter::WriteEnd(); }
	
protected:
	inline void __fastcall  WriteValue(TJsonWriter* const Writer, const System::Rtti::TValue &Value){ TJsonWriter::WriteValue(Writer, Value); }
	
public:
	inline void __fastcall  WriteValue(const char * Value){ TJsonWriter::WriteValue(Value); }
	inline void __fastcall  WriteValue(const System::WideChar * Value){ TJsonWriter::WriteValue(Value); }
	inline void __fastcall  WriteValue(const System::Rtti::TValue &Value){ TJsonWriter::WriteValue(Value); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Writers */
}	/* namespace Json */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_JSON_WRITERS)
using namespace System::Json::Writers;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_JSON)
using namespace System::Json;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Json_WritersHPP
