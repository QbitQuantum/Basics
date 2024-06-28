// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.JSON.Readers.pas' rev: 34.00 (Windows)

#ifndef System_Json_ReadersHPP
#define System_Json_ReadersHPP

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
#include <System.Rtti.hpp>
#include <System.JSON.Types.hpp>
#include <System.JSON.Utils.hpp>
#include <System.JSON.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Json
{
namespace Readers
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TJsonReader;
class DELPHICLASS EJsonReaderException;
class DELPHICLASS TJsonTextReader;
class DELPHICLASS TJsonObjectReader;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TJsonReader : public System::Json::Types::TJsonFiler
{
	typedef System::Json::Types::TJsonFiler inherited;
	
	
public:
	enum class DECLSPEC_DENUM TState : unsigned char { Start, Complete, Property, ObjectStart, Object, ArrayStart, Array, Closed, PostValue, ConstructorStart, Constructor, Error, Finished };
	
	enum class DECLSPEC_DENUM TReadType : unsigned char { Read, ReadAsInteger, ReadAsBytes, ReadAsString, ReadAsDouble, ReadAsDateTime, ReadAsOid };
	
	
private:
	System::Json::Types::TJsonToken FTokenType;
	System::Rtti::TValue FValue;
	System::WideChar FQuoteChar;
	TReadType FReadType;
	System::Sysutils::TFormatSettings FFormatSettings;
	System::Json::Types::TJsonDateTimeZoneHandling FDateTimeZoneHandling;
	int FMaxDepth;
	bool FHasExceededMaxDepth;
	bool FCloseInput;
	bool FSupportMultipleContent;
	System::Json::Types::TJsonContainerType __fastcall GetTypeForCloseToken(System::Json::Types::TJsonToken Token);
	HIDESBASE void __fastcall Push(System::Json::Types::TJsonContainerType AValue);
	HIDESBASE System::Json::Types::TJsonContainerType __fastcall Pop();
	void __fastcall SetFinished();
	void __fastcall UpdateScopeWithFinishedValue();
	void __fastcall ValidateEnd(System::Json::Types::TJsonToken EndToken);
	int __fastcall GetDepth();
	
protected:
	TState FCurrentState;
	virtual bool __fastcall GetInsideContainer();
	void __fastcall SetStateBasedOnCurrent();
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall ReadAsBytesInternal();
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall ReadAsBytesInternal();
#endif /* _WIN64 */
	System::TDateTime __fastcall ReadAsDateTimeInternal();
	double __fastcall ReadAsDoubleInternal();
	int __fastcall ReadAsIntegerInternal();
	__int64 __fastcall ReadAsInt64Internal();
	System::UnicodeString __fastcall ReadAsStringInternal();
	virtual bool __fastcall ReadInternal() = 0 ;
	void __fastcall SetPostValueState(bool AUpdateIndex);
	void __fastcall SetToken(System::Json::Types::TJsonToken ANewToken)/* overload */;
	void __fastcall SetToken(System::Json::Types::TJsonToken ANewToken, const System::Rtti::TValue &AValue)/* overload */;
	void __fastcall SetToken(System::Json::Types::TJsonToken ANewToken, const System::Rtti::TValue &AValue, bool AUpdateIndex)/* overload */;
	
public:
	__fastcall TJsonReader();
	__fastcall virtual ~TJsonReader();
	virtual void __fastcall Close();
	virtual void __fastcall Rewind();
	virtual bool __fastcall Read();
	virtual int __fastcall ReadAsInteger();
	virtual __int64 __fastcall ReadAsInt64();
	virtual System::UnicodeString __fastcall ReadAsString();
#ifndef _WIN64
	virtual System::DynamicArray<System::Byte> __fastcall ReadAsBytes();
#else /* _WIN64 */
	virtual System::TArray__1<System::Byte> __fastcall ReadAsBytes();
#endif /* _WIN64 */
	virtual double __fastcall ReadAsDouble();
	virtual System::TDateTime __fastcall ReadAsDateTime();
	virtual void __fastcall Skip();
	__property bool CloseInput = {read=FCloseInput, write=FCloseInput, nodefault};
	__property TState CurrentState = {read=FCurrentState, nodefault};
	__property int Depth = {read=GetDepth, nodefault};
	__property System::Json::Types::TJsonToken TokenType = {read=FTokenType, nodefault};
	__property int MaxDepth = {read=FMaxDepth, write=FMaxDepth, nodefault};
	__property System::WideChar QuoteChar = {read=FQuoteChar, write=FQuoteChar, nodefault};
	__property bool SupportMultipleContent = {read=FSupportMultipleContent, write=FSupportMultipleContent, nodefault};
	__property System::Json::Types::TJsonDateTimeZoneHandling DateTimeZoneHandling = {read=FDateTimeZoneHandling, write=FDateTimeZoneHandling, nodefault};
	__property System::Sysutils::TFormatSettings FormatSettings = {read=FFormatSettings, write=FFormatSettings};
	__property System::Rtti::TValue Value = {read=FValue};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EJsonReaderException : public System::Json::EJSONException
{
	typedef System::Json::EJSONException inherited;
	
private:
	int FLineNumber;
	int FLinePosition;
	System::UnicodeString FPath;
	
public:
	__fastcall EJsonReaderException(const System::UnicodeString Msg, const System::UnicodeString APath, int ALineNumber, int ALinePosition)/* overload */;
	__fastcall EJsonReaderException(TJsonReader* const Reader, const System::UnicodeString Msg)/* overload */;
	__fastcall EJsonReaderException(System::Json::Types::TJsonLineInfo* const LineInfo, const System::UnicodeString Path, const System::UnicodeString Msg)/* overload */;
	__fastcall EJsonReaderException(TJsonReader* const Reader, const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High)/* overload */;
	__fastcall EJsonReaderException(System::Json::Types::TJsonLineInfo* const LineInfo, const System::UnicodeString Path, const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High)/* overload */;
	__property int LineNumber = {read=FLineNumber, nodefault};
	__property int LinePosition = {read=FLinePosition, nodefault};
	__property System::UnicodeString Path = {read=FPath};
public:
	/* Exception.CreateRes */ inline __fastcall EJsonReaderException(NativeUInt Ident)/* overload */ : System::Json::EJSONException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EJsonReaderException(System::PResStringRec ResStringRec)/* overload */ : System::Json::EJSONException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EJsonReaderException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Json::EJSONException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EJsonReaderException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Json::EJSONException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EJsonReaderException(const System::UnicodeString Msg, int AHelpContext) : System::Json::EJSONException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EJsonReaderException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Json::EJSONException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJsonReaderException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Json::EJSONException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJsonReaderException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Json::EJSONException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJsonReaderException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Json::EJSONException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJsonReaderException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Json::EJSONException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EJsonReaderException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TJsonTextReader : public TJsonReader
{
	typedef TJsonReader inherited;
	
	
private:
	class DELPHICLASS TStringBuffer;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TStringBuffer : public System::Sysutils::TStringBuilder
	{
		typedef System::Sysutils::TStringBuilder inherited;
		
	public:
		__property System::UnicodeString InternalBuffer = {read=FData};
	public:
		/* TStringBuilder.Create */ inline __fastcall TStringBuffer()/* overload */ : System::Sysutils::TStringBuilder() { }
		/* TStringBuilder.Create */ inline __fastcall TStringBuffer(int aCapacity)/* overload */ : System::Sysutils::TStringBuilder(aCapacity) { }
		/* TStringBuilder.Create */ inline __fastcall TStringBuffer(const System::UnicodeString Value)/* overload */ : System::Sysutils::TStringBuilder(Value) { }
		/* TStringBuilder.Create */ inline __fastcall TStringBuffer(int aCapacity, int aMaxCapacity)/* overload */ : System::Sysutils::TStringBuilder(aCapacity, aMaxCapacity) { }
		/* TStringBuilder.Create */ inline __fastcall TStringBuffer(const System::UnicodeString Value, int aCapacity)/* overload */ : System::Sysutils::TStringBuilder(Value, aCapacity) { }
		/* TStringBuilder.Create */ inline __fastcall TStringBuffer(const System::UnicodeString Value, int StartIndex, int Length, int aCapacity)/* overload */ : System::Sysutils::TStringBuilder(Value, StartIndex, Length, aCapacity) { }
		
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TStringBuffer() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	struct DECLSPEC_DRECORD TCharsReference
	{
	private:
		System::WideChar *FReference;
		int FCount;
		
	public:
		void __fastcall SetReference(System::WideChar * P, int ACount);
		System::UnicodeString __fastcall ToString();
	};
	
	
	typedef System::DynamicArray<System::WideChar> _TJsonTextReader__1;
	
	
private:
	static System::WideChar UnicodeReplacementChar;
	static int MaximumJavascriptIntegerCharacterLength;
	static int kBufferSize;
	System::Classes::TTextReader* FReader;
	_TJsonTextReader__1 FChars;
	TCharsReference FCharsReference;
	int FCharsUsed;
	int FCharPos;
	int FLineStartPos;
	int FLineNumber;
	bool FIsEndOfFile;
	TStringBuffer* FBuffer;
	System::Json::Types::TJsonDateParseHandling FDateParseHandling;
	System::Json::Types::TJsonExtendedJsonMode FExtendedJsonMode;
	void __fastcall ClearRecentString();
	bool __fastcall IsWhiteSpace(const System::WideChar AChar);
	bool __fastcall EatWhiteSpace(bool OneOrMore);
	bool __fastcall EnsureChars(int RelativePosition, bool Append);
	bool __fastcall IsSeparator(System::WideChar C);
	bool __fastcall MatchValueWithTrailingSeparator(const System::UnicodeString Value);
	bool __fastcall MatchValue(const System::UnicodeString Value);
	bool __fastcall ReadChars(int RelativePosition, bool Append);
	int __fastcall ReadData(bool Append)/* overload */;
	int __fastcall ReadData(bool Append, int CharsRequired)/* overload */;
	void __fastcall OnNewLine(int Pos);
	void __fastcall ParseString(System::WideChar Quote);
	void __fastcall ParseTrue();
	void __fastcall ParseFalse();
	void __fastcall ParseComment();
	void __fastcall ParseNumber();
	void __fastcall ParseNumberNaN();
	void __fastcall ParseNull();
	void __fastcall ParseUndefined();
	void __fastcall ParseNumberNegativeInfinity();
	void __fastcall ParseNumberPositiveInfinity();
	bool __fastcall ParseObject();
	bool __fastcall ParseProperty();
	void __fastcall ParseUnquotedProperty();
	void __fastcall ParseConstructor();
	System::WideChar __fastcall ParseUnicode();
	bool __fastcall ParseValue();
	bool __fastcall ParsePostValue();
	bool __fastcall ParseExtendedStrictModeValue();
	void __fastcall ProcessCarriageReturn(bool Append);
	void __fastcall ProcessLineFeed();
	void __fastcall ReadStringIntoBuffer(System::WideChar Quote);
	void __fastcall ReadNumberIntoBuffer();
	void __fastcall ShiftBufferIfNeeded();
	void __fastcall WriteCharToBuffer(TStringBuffer* const Buffer, System::WideChar WriteChar, int LastWritePosition, int WriteToPosition);
	bool __fastcall ValidIdentifierChar(System::WideChar AValue);
	
protected:
	virtual bool __fastcall ReadInternal();
	
public:
	__fastcall TJsonTextReader(System::Classes::TTextReader* const Reader);
	__fastcall virtual ~TJsonTextReader();
	virtual void __fastcall Close();
	virtual void __fastcall Rewind();
	virtual int __fastcall GetLineNumber();
	virtual int __fastcall GetLinePosition();
	virtual bool __fastcall HasLineInfo();
	__property System::Classes::TTextReader* Reader = {read=FReader};
	__property int LineNumber = {read=GetLineNumber, nodefault};
	__property int LinePosition = {read=GetLinePosition, nodefault};
	__property System::Json::Types::TJsonDateParseHandling DateParseHandling = {read=FDateParseHandling, write=FDateParseHandling, nodefault};
	__property System::Json::Types::TJsonExtendedJsonMode ExtendedJsonMode = {read=FExtendedJsonMode, write=FExtendedJsonMode, nodefault};
};


class PASCALIMPLEMENTATION TJsonObjectReader : public TJsonReader
{
	typedef TJsonReader inherited;
	
	
private:
	struct DECLSPEC_DRECORD TContext
	{
	public:
		System::Json::TJSONAncestor* FValue;
		int FIndex;
		__fastcall TContext(System::Json::TJSONAncestor* AValue, int AIndex);
		TContext() {}
	};
	
	
	
private:
	System::Json::TJSONAncestor* FRoot;
	System::Json::TJSONAncestor* FCurrent;
	int FCurrentIndex;
	System::Generics::Collections::TStack__1<TContext>* FStack;
	bool FFinished;
	System::Json::TJSONAncestor* __fastcall GetCurrent();
	
protected:
	virtual bool __fastcall ReadInternal();
	
public:
	__fastcall TJsonObjectReader(System::Json::TJSONAncestor* const ARoot);
	__fastcall virtual ~TJsonObjectReader();
	virtual void __fastcall Close();
	virtual void __fastcall Rewind();
	__property System::Json::TJSONAncestor* Current = {read=GetCurrent};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Readers */
}	/* namespace Json */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_JSON_READERS)
using namespace System::Json::Readers;
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
#endif	// System_Json_ReadersHPP
