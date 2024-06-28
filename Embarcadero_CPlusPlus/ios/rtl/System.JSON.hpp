// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.JSON.pas' rev: 34.00 (iOS)

#ifndef System_JsonHPP
#define System_JsonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Rtti.hpp>
#include <System.TypInfo.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Json
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EJSONException;
class DELPHICLASS EJSONPathException;
class DELPHICLASS EJSONParseException;
struct TJSONPathParser;
class DELPHICLASS TJSONAncestor;
class DELPHICLASS TJSONByteReader;
class DELPHICLASS TJSONValue;
class DELPHICLASS TJSONString;
class DELPHICLASS TJSONNumber;
class DELPHICLASS TJSONPair;
class DELPHICLASS TJSONObject;
class DELPHICLASS TJSONPairEnumerator;
class DELPHICLASS TJSONNull;
class DELPHICLASS TJSONBool;
class DELPHICLASS TJSONTrue;
class DELPHICLASS TJSONFalse;
class DELPHICLASS TJSONArray;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION EJSONException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EJSONException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EJSONException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EJSONException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EJSONException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EJSONException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EJSONException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EJSONException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EJSONException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJSONException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJSONException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJSONException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJSONException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EJSONException() { }
	
};


class PASCALIMPLEMENTATION EJSONPathException : public EJSONException
{
	typedef EJSONException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EJSONPathException(const System::UnicodeString Msg) : EJSONException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EJSONPathException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EJSONException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EJSONPathException(NativeUInt Ident)/* overload */ : EJSONException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EJSONPathException(System::PResStringRec ResStringRec)/* overload */ : EJSONException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EJSONPathException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EJSONException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EJSONPathException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EJSONException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EJSONPathException(const System::UnicodeString Msg, int AHelpContext) : EJSONException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EJSONPathException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EJSONException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJSONPathException(NativeUInt Ident, int AHelpContext)/* overload */ : EJSONException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJSONPathException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EJSONException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJSONPathException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EJSONException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJSONPathException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EJSONException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EJSONPathException() { }
	
};


class PASCALIMPLEMENTATION EJSONParseException : public EJSONException
{
	typedef EJSONException inherited;
	
private:
	System::UnicodeString FPath;
	int FOffset;
	int FLine;
	int FPosition;
	
protected:
	__fastcall EJSONParseException(int AOffset, TJSONByteReader* ABr, TJSONValue* AValue, System::PResStringRec AIdent, const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	__fastcall EJSONParseException(int AOffset, TJSONByteReader* ABr, TJSONValue* AValue)/* overload */;
	
public:
	__property System::UnicodeString Path = {read=FPath};
	__property int Offset = {read=FOffset, nodefault};
	__property int Line = {read=FLine, nodefault};
	__property int Position = {read=FPosition, nodefault};
public:
	/* Exception.CreateFmt */ inline __fastcall EJSONParseException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EJSONException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EJSONParseException(NativeUInt Ident)/* overload */ : EJSONException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EJSONParseException(System::PResStringRec ResStringRec)/* overload */ : EJSONException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EJSONParseException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EJSONException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EJSONParseException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EJSONException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EJSONParseException(const System::UnicodeString Msg, int AHelpContext) : EJSONException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EJSONParseException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EJSONException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJSONParseException(NativeUInt Ident, int AHelpContext)/* overload */ : EJSONException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJSONParseException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EJSONException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJSONParseException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EJSONException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJSONParseException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EJSONException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EJSONParseException() { }
	
};


struct DECLSPEC_DRECORD TJSONPathParser
{
	
public:
	enum class DECLSPEC_DENUM TToken : unsigned char { Undefined, Name, ArrayIndex, Eof, Error };
	
	
private:
	System::WideChar *FPathPtr;
	System::WideChar *FPtr;
	System::WideChar *FEndPtr;
	int FTokenArrayIndex;
	System::UnicodeString FTokenName;
	TToken FToken;
	bool __fastcall GetIsEof();
	void __fastcall RaiseError(System::PResStringRec AMsg);
	void __fastcall RaiseErrorFmt(System::PResStringRec AMsg, const System::TVarRec *AParams, const int AParams_High);
	void __fastcall ParseName();
	void __fastcall ParseQuotedName(System::WideChar AQuote);
	void __fastcall ParseArrayIndex();
	void __fastcall ParseIndexer();
	bool __fastcall EnsureLength(int ALength);
	void __fastcall FrontTrim(System::WideChar * &APtr);
	void __fastcall BackTrim(System::WideChar * &APtr);
	
public:
	__fastcall TJSONPathParser(const System::UnicodeString APath)/* overload */;
	__fastcall TJSONPathParser(const System::WideChar * APathPtr, int ALen)/* overload */;
	TToken __fastcall NextToken();
	__property bool IsEof = {read=GetIsEof};
	__property TToken Token = {read=FToken};
	__property System::UnicodeString TokenName = {read=FTokenName};
	__property int TokenArrayIndex = {read=FTokenArrayIndex};
	TJSONPathParser() {}
};


class PASCALIMPLEMENTATION TJSONAncestor : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TJSONOutputOption : unsigned char { EncodeBelow32, EncodeAbove127 };
	
	typedef System::Set<TJSONOutputOption, _DELPHI_SET_ENUMERATOR(TJSONOutputOption::EncodeBelow32), _DELPHI_SET_ENUMERATOR(TJSONOutputOption::EncodeAbove127)> TJSONOutputOptions;
	
	
private:
	bool FOwned;
	
protected:
	virtual bool __fastcall IsNull();
	virtual void __fastcall AddDescendant(TJSONAncestor* const Descendent);
	virtual void __fastcall Format(System::Sysutils::TStringBuilder* Builder, const System::UnicodeString ParentIdent, const System::UnicodeString Ident)/* overload */;
	
public:
	__fastcall virtual TJSONAncestor()/* overload */;
	virtual System::UnicodeString __fastcall Value();
	virtual int __fastcall EstimatedByteSize() = 0 ;
	virtual int __fastcall ToBytes(const System::TArray__1<System::Byte> Data, int Offset) = 0 ;
	virtual void __fastcall ToChars(System::Sysutils::TStringBuilder* Builder, TJSONOutputOptions Options) = 0 /* overload */;
	System::UnicodeString __fastcall ToJSON(TJSONOutputOptions Options)/* overload */;
	System::UnicodeString __fastcall ToJSON()/* overload */;
	virtual System::UnicodeString __fastcall ToString();
	System::UnicodeString __fastcall Format(int Indentation = 0x4)/* overload */;
	virtual TJSONAncestor* __fastcall Clone() = 0 ;
	__property bool Null = {read=IsNull, nodefault};
	__property bool Owned = {read=FOwned, write=FOwned, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJSONAncestor() { }
	
};


class PASCALIMPLEMENTATION TJSONByteReader : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Byte *FData;
	System::Byte *FDataStart;
	System::Byte *FDataEnd;
	bool FIsUTF8;
	System::TArray__1<System::Byte> FUtf8data;
	int FUtf8offset;
	int FUtf8length;
	System::Generics::Collections::TDictionary__2<unsigned,System::UnicodeString>* FStringCache;
	System::TArray__1<System::WideChar> FCharData;
	int FCharPos;
	int FCharLen;
	bool FCache;
	int FLevel;
	void __fastcall Init(const System::PByte Data, const int Offset, const int Range);
	int __fastcall GetOffset();
	void __fastcall ConsumeBOM();
	void __fastcall MoveOffset();
	void __fastcall ProcessMBCS();
	void __fastcall EnterLevel();
	void __fastcall ExitLevel();
	
public:
	__fastcall TJSONByteReader(const System::PByte Data, const int Offset, const int Range)/* overload */;
	__fastcall TJSONByteReader(const System::PByte Data, const int Offset, const int Range, const bool IsUTF8)/* overload */;
	__fastcall virtual ~TJSONByteReader();
	System::Byte __fastcall ConsumeByte();
	System::Byte __fastcall PeekRawByte();
	System::Byte __fastcall PeekByte();
	void __fastcall SkipByte();
	void __fastcall SkipWhitespaces();
	bool __fastcall IsEof();
	bool __fastcall HasMore(const int Size);
	void __fastcall AddChar(System::WideChar Ch);
	void __fastcall ResetString();
	void __fastcall FlushString(System::UnicodeString &ADest, bool ACache);
	void __fastcall OffsetToPos(int AOffset, int &ALine, int &APos);
	__property int Offset = {read=GetOffset, nodefault};
};


class PASCALIMPLEMENTATION TJSONValue : public TJSONAncestor
{
	typedef TJSONAncestor inherited;
	
private:
	TJSONValue* __fastcall GetValueP(const System::UnicodeString APath);
	virtual TJSONValue* __fastcall GetValueA(const int AIndex);
	
protected:
	virtual bool __fastcall AsTValue(System::Typinfo::PTypeInfo ATypeInfo, System::Rtti::TValue &AValue);
	
public:
	TJSONValue* __fastcall FindValue(const System::UnicodeString APath);
	template<typename T> bool __fastcall TryGetValue(/* out */ T &AValue)/* overload */;
	template<typename T> bool __fastcall TryGetValue(const System::UnicodeString APath, /* out */ T &AValue)/* overload */;
	template<typename T> T __fastcall GetValue(const System::UnicodeString APath = System::UnicodeString())/* overload */;
	template<typename T> T __fastcall GetValue(const System::UnicodeString APath, T ADefaultValue)/* overload */;
	template<typename T> T __fastcall AsType()/* overload */;
	__property TJSONValue* P[const System::UnicodeString APath] = {read=GetValueP};
	__property TJSONValue* A[const int AIndex] = {read=GetValueA};
public:
	/* TJSONAncestor.Create */ inline __fastcall virtual TJSONValue()/* overload */ : TJSONAncestor() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJSONValue() { }
	
};


class PASCALIMPLEMENTATION TJSONString : public TJSONValue
{
	typedef TJSONValue inherited;
	
protected:
	System::UnicodeString FValue;
	bool FIsNull;
	virtual bool __fastcall IsNull();
	virtual bool __fastcall AsTValue(System::Typinfo::PTypeInfo ATypeInfo, System::Rtti::TValue &AValue);
	
public:
	__fastcall virtual TJSONString()/* overload */;
	__fastcall TJSONString(const System::UnicodeString Value)/* overload */;
	void __fastcall AddChar(const System::WideChar Ch);
	HIDESBASE bool __fastcall Equals(const System::UnicodeString Value);
	virtual int __fastcall EstimatedByteSize();
	virtual int __fastcall ToBytes(const System::TArray__1<System::Byte> Data, int Offset);
	virtual void __fastcall ToChars(System::Sysutils::TStringBuilder* Builder, TJSONAncestor::TJSONOutputOptions Options)/* overload */;
	virtual System::UnicodeString __fastcall Value();
	virtual TJSONAncestor* __fastcall Clone();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJSONString() { }
	
};


class PASCALIMPLEMENTATION TJSONNumber : /*[[sealed]]*/ public TJSONString
{
	typedef TJSONString inherited;
	
protected:
	__fastcall TJSONNumber(const System::UnicodeString Value)/* overload */;
	double __fastcall GetAsDouble();
	int __fastcall GetAsInt();
	__int64 __fastcall GetAsInt64();
	
public:
	__fastcall TJSONNumber(const double Value)/* overload */;
	__fastcall TJSONNumber(const int Value)/* overload */;
	__fastcall TJSONNumber(const __int64 Value)/* overload */;
	virtual int __fastcall EstimatedByteSize();
	virtual int __fastcall ToBytes(const System::TArray__1<System::Byte> Data, int Offset);
	virtual void __fastcall ToChars(System::Sysutils::TStringBuilder* Builder, TJSONAncestor::TJSONOutputOptions Options)/* overload */;
	virtual System::UnicodeString __fastcall Value();
	virtual TJSONAncestor* __fastcall Clone();
	__property double AsDouble = {read=GetAsDouble};
	__property int AsInt = {read=GetAsInt, nodefault};
	__property __int64 AsInt64 = {read=GetAsInt64};
public:
	/* TJSONString.Create */ inline __fastcall virtual TJSONNumber()/* overload */ : TJSONString() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJSONNumber() { }
	
};


class PASCALIMPLEMENTATION TJSONPair : /*[[sealed]]*/ public TJSONAncestor
{
	typedef TJSONAncestor inherited;
	
private:
	TJSONString* FJsonString;
	TJSONValue* FJsonValue;
	
protected:
	virtual void __fastcall AddDescendant(TJSONAncestor* const Descendant);
	void __fastcall SetJsonString(TJSONString* const Descendant);
	void __fastcall SetJsonValue(TJSONValue* const Val);
	bool __fastcall HasName(const System::UnicodeString Name);
	
public:
	__fastcall TJSONPair(TJSONString* const Str, TJSONValue* const Value)/* overload */;
	__fastcall TJSONPair(const System::UnicodeString Str, TJSONValue* const Value)/* overload */;
	__fastcall TJSONPair(const System::UnicodeString Str, const System::UnicodeString Value)/* overload */;
	__fastcall virtual TJSONPair()/* overload */;
	__fastcall virtual ~TJSONPair();
	virtual int __fastcall EstimatedByteSize();
	virtual int __fastcall ToBytes(const System::TArray__1<System::Byte> Data, int Offset);
	virtual void __fastcall ToChars(System::Sysutils::TStringBuilder* Builder, TJSONAncestor::TJSONOutputOptions Options)/* overload */;
	virtual TJSONAncestor* __fastcall Clone();
	__property TJSONString* JsonString = {read=FJsonString, write=SetJsonString};
	__property TJSONValue* JsonValue = {read=FJsonValue, write=SetJsonValue};
};


class PASCALIMPLEMENTATION TJSONObject : /*[[sealed]]*/ public TJSONValue
{
	typedef TJSONValue inherited;
	
	
public:
	enum class DECLSPEC_DENUM TJSONParseOption : unsigned char { IsUTF8, UseBool, RaiseExc };
	
	typedef System::Set<TJSONParseOption, _DELPHI_SET_ENUMERATOR(TJSONParseOption::IsUTF8), _DELPHI_SET_ENUMERATOR(TJSONParseOption::RaiseExc)> TJSONParseOptions;
	
	class DELPHICLASS TEnumerator;
	class PASCALIMPLEMENTATION TEnumerator : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		int FIndex;
		TJSONObject* FObject;
		
	public:
		__fastcall TEnumerator(TJSONObject* const AObject);
		TJSONPair* __fastcall GetCurrent();
		bool __fastcall MoveNext();
		__property TJSONPair* Current = {read=GetCurrent};
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TEnumerator() { }
		
	};
	
	
	
private:
	System::Generics::Collections::TList__1<TJSONPair*>* FMembers;
	int __fastcall Parse(TJSONByteReader* const Br, bool UseBool)/* overload */;
	__classmethod TJSONParseOptions __fastcall MakeParseOptions(bool IsUTF8, bool UseBool, bool RaiseExc);
	static int __fastcall ParseObject(TJSONByteReader* const Br, TJSONAncestor* const Parent, bool UseBool);
	static int __fastcall ParsePair(TJSONByteReader* const Br, TJSONObject* const Parent, bool UseBool);
	static int __fastcall ParseArray(TJSONByteReader* const Br, TJSONAncestor* const Parent, bool UseBool);
	static int __fastcall ParseValue(TJSONByteReader* const Br, TJSONAncestor* const Parent, bool UseBool);
	static int __fastcall ParseNumber(TJSONByteReader* const Br, TJSONAncestor* const Parent);
	static int __fastcall ParseString(TJSONByteReader* const Br, TJSONAncestor* const Parent);
	
protected:
	virtual void __fastcall AddDescendant(TJSONAncestor* const Descendant);
	int __fastcall GetCount();
	TJSONPair* __fastcall GetPair(const int Index);
	TJSONPair* __fastcall GetPairByName(const System::UnicodeString PairName);
	virtual void __fastcall Format(System::Sysutils::TStringBuilder* Builder, const System::UnicodeString ParentIdent, const System::UnicodeString Ident)/* overload */;
	
public:
	static TJSONValue* __fastcall ParseJSONValue(const System::PByte Data, const int Offset, const int ALength, TJSONParseOptions Options)/* overload */;
	static TJSONValue* __fastcall ParseJSONValue(const System::TArray__1<System::Byte> Data, const int Offset, bool IsUTF8 = true)/* overload */;
	static TJSONValue* __fastcall ParseJSONValue(const System::TArray__1<System::Byte> Data, const int Offset, TJSONParseOptions Options)/* overload */;
	static TJSONValue* __fastcall ParseJSONValue(const System::TArray__1<System::Byte> Data, const int Offset, const int ALength, bool IsUTF8 = true)/* overload */;
	static TJSONValue* __fastcall ParseJSONValue(const System::TArray__1<System::Byte> Data, const int Offset, const int ALength, TJSONParseOptions Options)/* overload */;
	static TJSONValue* __fastcall ParseJSONValue(const System::UnicodeString Data, bool UseBool = false, bool RaiseExc = false)/* overload */;
	static TJSONValue* __fastcall ParseJSONValue(const System::UTF8String Data, bool UseBool = false, bool RaiseExc = false)/* overload */;
	static TJSONValue* __fastcall ParseJSONFragment(const System::PByte Data, int &Offset, const int ALength, TJSONParseOptions Options)/* overload */;
	static TJSONValue* __fastcall ParseJSONFragment(const System::TArray__1<System::Byte> Data, int &Offset, TJSONParseOptions Options)/* overload */;
	static TJSONValue* __fastcall ParseJSONFragment(const System::UnicodeString Data, int &Offset, TJSONParseOptions Options)/* overload */;
	__fastcall virtual TJSONObject()/* overload */;
	__fastcall TJSONObject(TJSONPair* const Pair)/* overload */;
	TEnumerator* __fastcall GetEnumerator();
	HIDESBASE TJSONValue* __fastcall GetValue(const System::UnicodeString Name)/* overload */;
	__fastcall virtual ~TJSONObject();
	TJSONObject* __fastcall AddPair(TJSONPair* const Pair)/* overload */;
	TJSONObject* __fastcall AddPair(TJSONString* const Str, TJSONValue* const Val)/* overload */;
	TJSONObject* __fastcall AddPair(const System::UnicodeString Str, TJSONValue* const Val)/* overload */;
	TJSONObject* __fastcall AddPair(const System::UnicodeString Str, const System::UnicodeString Val)/* overload */;
	TJSONPair* __fastcall RemovePair(const System::UnicodeString PairName);
	virtual int __fastcall EstimatedByteSize();
	virtual int __fastcall ToBytes(const System::TArray__1<System::Byte> Data, int Offset);
	virtual void __fastcall ToChars(System::Sysutils::TStringBuilder* Builder, TJSONAncestor::TJSONOutputOptions Options)/* overload */;
	virtual TJSONAncestor* __fastcall Clone();
	int __fastcall Parse(const System::TArray__1<System::Byte> Data, const int Pos, bool UseBool = false)/* overload */;
	int __fastcall Parse(const System::TArray__1<System::Byte> Data, const int Pos, const int Count, bool UseBool = false)/* overload */;
	void __fastcall SetPairs(System::Generics::Collections::TList__1<TJSONPair*>* const AList);
	__property int Count = {read=GetCount, nodefault};
	__property TJSONPair* Pairs[const int Index] = {read=GetPair};
	__property TJSONValue* Values[const System::UnicodeString Name] = {read=GetValue};
	int __fastcall Size _DEPRECATED_ATTRIBUTE1("Use Count Property") ();
	TJSONPair* __fastcall Get _DEPRECATED_ATTRIBUTE1("Use Pairs property") (const int Index)/* overload */;
	TJSONPair* __fastcall Get(const System::UnicodeString Name)/* overload */;
	static TJSONValue* __fastcall ParseJSONValueUTF8 _DEPRECATED_ATTRIBUTE1("Use ParseJSONValue") (const System::TArray__1<System::Byte> Data, const int Offset, const int ACount)/* overload */;
	static TJSONValue* __fastcall ParseJSONValueUTF8 _DEPRECATED_ATTRIBUTE1("Use ParseJSONValue") (const System::TArray__1<System::Byte> Data, const int Offset)/* overload */;
	/* Hoisted overloads: */
	
public:
	inline System::UnicodeString __fastcall  Format(int Indentation = 0x4){ return TJSONAncestor::Format(Indentation); }
	
};


class PASCALIMPLEMENTATION TJSONPairEnumerator _DEPRECATED_ATTRIBUTE1("Use TJSONObject.TEnumerator")  : public TJSONObject::TEnumerator
{
	typedef TJSONObject::TEnumerator inherited;
	
public:
	/* TEnumerator.Create */ inline __fastcall TJSONPairEnumerator(TJSONObject* const AObject) : TJSONObject::TEnumerator(AObject) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJSONPairEnumerator() { }
	
};


class PASCALIMPLEMENTATION TJSONNull : /*[[sealed]]*/ public TJSONValue
{
	typedef TJSONValue inherited;
	
protected:
	static System::UnicodeString NULLString;
	
protected:
	virtual bool __fastcall AsTValue(System::Typinfo::PTypeInfo ATypeInfo, System::Rtti::TValue &AValue);
	virtual bool __fastcall IsNull();
	
public:
	virtual int __fastcall EstimatedByteSize();
	virtual int __fastcall ToBytes(const System::TArray__1<System::Byte> Data, int Offset);
	virtual void __fastcall ToChars(System::Sysutils::TStringBuilder* Builder, TJSONAncestor::TJSONOutputOptions Options)/* overload */;
	virtual System::UnicodeString __fastcall Value();
	virtual TJSONAncestor* __fastcall Clone();
public:
	/* TJSONAncestor.Create */ inline __fastcall virtual TJSONNull()/* overload */ : TJSONValue() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJSONNull() { }
	
};


class PASCALIMPLEMENTATION TJSONBool : public TJSONValue
{
	typedef TJSONValue inherited;
	
private:
	bool FValue;
	
protected:
	static System::UnicodeString FalseString;
	static System::UnicodeString TrueString;
	static System::StaticArray<System::Byte, 5> FalseBytes;
	static System::StaticArray<System::Byte, 4> TrueBytes;
	
protected:
	virtual bool __fastcall AsTValue(System::Typinfo::PTypeInfo ATypeInfo, System::Rtti::TValue &AValue);
	
public:
	__fastcall TJSONBool(bool AValue)/* overload */;
	virtual int __fastcall EstimatedByteSize();
	virtual int __fastcall ToBytes(const System::TArray__1<System::Byte> Data, int Offset);
	virtual void __fastcall ToChars(System::Sysutils::TStringBuilder* Builder, TJSONAncestor::TJSONOutputOptions Options)/* overload */;
	virtual System::UnicodeString __fastcall Value();
	virtual TJSONAncestor* __fastcall Clone();
	__property bool AsBoolean = {read=FValue, nodefault};
public:
	/* TJSONAncestor.Create */ inline __fastcall virtual TJSONBool()/* overload */ : TJSONValue() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJSONBool() { }
	
};


class PASCALIMPLEMENTATION TJSONTrue : /*[[sealed]]*/ public TJSONBool
{
	typedef TJSONBool inherited;
	
public:
	__fastcall virtual TJSONTrue()/* overload */;
	virtual TJSONAncestor* __fastcall Clone();
public:
	/* TJSONBool.Create */ inline __fastcall TJSONTrue(bool AValue)/* overload */ : TJSONBool(AValue) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJSONTrue() { }
	
};


class PASCALIMPLEMENTATION TJSONFalse : /*[[sealed]]*/ public TJSONBool
{
	typedef TJSONBool inherited;
	
public:
	__fastcall virtual TJSONFalse()/* overload */;
	virtual TJSONAncestor* __fastcall Clone();
public:
	/* TJSONBool.Create */ inline __fastcall TJSONFalse(bool AValue)/* overload */ : TJSONBool(AValue) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJSONFalse() { }
	
};


class PASCALIMPLEMENTATION TJSONArray : /*[[sealed]]*/ public TJSONValue
{
	typedef TJSONValue inherited;
	
	
public:
	class DELPHICLASS TEnumerator;
	class PASCALIMPLEMENTATION TEnumerator : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		int FIndex;
		TJSONArray* FArray;
		
	public:
		__fastcall TEnumerator(TJSONArray* const AArray);
		TJSONValue* __fastcall GetCurrent();
		bool __fastcall MoveNext();
		__property TJSONValue* Current = {read=GetCurrent};
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TEnumerator() { }
		
	};
	
	
	
public:
	TJSONValue* operator[](const int Index) { return this->Items[Index]; }
	
private:
	System::Generics::Collections::TList__1<TJSONValue*>* FElements;
	virtual TJSONValue* __fastcall GetValueA(const int Index);
	
protected:
	virtual bool __fastcall AsTValue(System::Typinfo::PTypeInfo ATypeInfo, System::Rtti::TValue &AValue);
	virtual void __fastcall AddDescendant(TJSONAncestor* const Descendant);
	TJSONValue* __fastcall Pop();
	HIDESBASE TJSONValue* __fastcall GetValue(const int Index)/* overload */;
	int __fastcall GetCount();
	virtual void __fastcall Format(System::Sysutils::TStringBuilder* Builder, const System::UnicodeString ParentIdent, const System::UnicodeString Ident)/* overload */;
	
public:
	__fastcall virtual TJSONArray()/* overload */;
	__fastcall TJSONArray(TJSONValue* const FirstElem)/* overload */;
	__fastcall TJSONArray(TJSONValue* const FirstElem, TJSONValue* const SecondElem)/* overload */;
	__fastcall TJSONArray(const System::UnicodeString FirstElem, const System::UnicodeString SecondElem)/* overload */;
	__fastcall virtual ~TJSONArray();
	__property int Count = {read=GetCount, nodefault};
	__property TJSONValue* Items[const int Index] = {read=GetValue/*, default*/};
	TJSONValue* __fastcall Remove(int Index);
	void __fastcall AddElement(TJSONValue* const Element);
	TJSONArray* __fastcall Add(const System::UnicodeString Element)/* overload */;
	TJSONArray* __fastcall Add(const int Element)/* overload */;
	TJSONArray* __fastcall Add(const double Element)/* overload */;
	TJSONArray* __fastcall Add(const bool Element)/* overload */;
	TJSONArray* __fastcall Add(TJSONObject* const Element)/* overload */;
	TJSONArray* __fastcall Add(TJSONArray* const Element)/* overload */;
	virtual int __fastcall EstimatedByteSize();
	void __fastcall SetElements(System::Generics::Collections::TList__1<TJSONValue*>* const AList);
	virtual int __fastcall ToBytes(const System::TArray__1<System::Byte> Data, int Offset);
	virtual void __fastcall ToChars(System::Sysutils::TStringBuilder* Builder, TJSONAncestor::TJSONOutputOptions Options)/* overload */;
	virtual TJSONAncestor* __fastcall Clone();
	TEnumerator* __fastcall GetEnumerator();
	int __fastcall Size _DEPRECATED_ATTRIBUTE1("Use Count Property") ();
	TJSONValue* __fastcall Get _DEPRECATED_ATTRIBUTE1("Use Items property") (const int Index);
	/* Hoisted overloads: */
	
public:
	inline System::UnicodeString __fastcall  Format(int Indentation = 0x4){ return TJSONAncestor::Format(Indentation); }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE int MaximumNestingLevel;
extern DELPHI_PACKAGE System::UnicodeString DecimalToHexMap;
extern DELPHI_PACKAGE System::StaticArray<System::Byte, 256> HexToDecimalMap;
extern DELPHI_PACKAGE System::Sysutils::TFormatSettings __fastcall GetJSONFormat(void);
extern DELPHI_PACKAGE System::UnicodeString __fastcall FloatToJson(const double Value);
extern DELPHI_PACKAGE double __fastcall JsonToFloat(const System::UnicodeString DotValue);
extern DELPHI_PACKAGE bool __fastcall TryJsonToFloat(const System::UnicodeString DotValue, double &Value);
extern DELPHI_PACKAGE System::Byte __fastcall HexToDecimal(const System::Byte AHex);
extern DELPHI_PACKAGE System::Byte __fastcall DecimalToHex(const System::Byte ADecimal);
}	/* namespace Json */
}	/* namespace System */
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
#endif	// System_JsonHPP
