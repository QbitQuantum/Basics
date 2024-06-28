// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.JSON.BSON.pas' rev: 34.00 (iOS)

#ifndef System_Json_BsonHPP
#define System_Json_BsonHPP

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
#include <System.JSON.Writers.hpp>
#include <System.JSON.Readers.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Json
{
namespace Bson
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBsonWriter;
class DELPHICLASS TBsonReader;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TBsonType : unsigned char { BsonDocument, Float, String, Object, Array, Binary, Undefined, Oid, Boolean, DateTime, Null, Regex, Reference, Code, Symbol, CodeWScope, Integer, TimeStamp, Long, MinKey = 255, MaxKey = 127 };

class PASCALIMPLEMENTATION TBsonWriter : public System::Json::Writers::TJsonWriter
{
	typedef System::Json::Writers::TJsonWriter inherited;
	
	
private:
	class DELPHICLASS TBsonContainer;
	class PASCALIMPLEMENTATION TBsonContainer : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		TBsonWriter::TBsonContainer* FParent;
		int FPosition;
		int FValuesSize;
		System::Generics::Collections::TObjectList__1<TBsonWriter::TBsonContainer*>* FChildren;
		
	public:
		__fastcall TBsonContainer(TBsonWriter::TBsonContainer* AParent, int SizePos);
		__fastcall virtual ~TBsonContainer();
		__property System::Generics::Collections::TObjectList__1<TBsonWriter::TBsonContainer*>* Children = {read=FChildren};
		__property int ValuesSize = {read=FValuesSize, write=FValuesSize, nodefault};
		__property int Position = {read=FPosition, write=FPosition, nodefault};
		__property TBsonWriter::TBsonContainer* Parent = {read=FParent, write=FParent};
	};
	
	
	class DELPHICLASS TBsonObject;
	class PASCALIMPLEMENTATION TBsonObject : public TBsonWriter::TBsonContainer
	{
		typedef TBsonWriter::TBsonContainer inherited;
		
	public:
		/* TBsonContainer.Create */ inline __fastcall TBsonObject(TBsonWriter::TBsonContainer* AParent, int SizePos) : TBsonWriter::TBsonContainer(AParent, SizePos) { }
		/* TBsonContainer.Destroy */ inline __fastcall virtual ~TBsonObject() { }
		
	};
	
	
	class DELPHICLASS TBsonArray;
	class PASCALIMPLEMENTATION TBsonArray : public TBsonWriter::TBsonContainer
	{
		typedef TBsonWriter::TBsonContainer inherited;
		
	private:
		int FIndex;
		
	public:
		__property int Index = {read=FIndex, write=FIndex, nodefault};
	public:
		/* TBsonContainer.Create */ inline __fastcall TBsonArray(TBsonWriter::TBsonContainer* AParent, int SizePos) : TBsonWriter::TBsonContainer(AParent, SizePos) { }
		/* TBsonContainer.Destroy */ inline __fastcall virtual ~TBsonArray() { }
		
	};
	
	
	
private:
	System::Sysutils::TEncoding* FEncoding;
	System::Classes::TBinaryWriter* FWriter;
	bool FWriterOwner;
	TBsonContainer* FRoot;
	TBsonContainer* FParent;
	System::UnicodeString FPropertyName;
	void __fastcall AddContainer(TBsonContainer* const Token);
	void __fastcall AddSize(int Size);
	int __fastcall WriteContainerSize(TBsonContainer* Container);
	void __fastcall WriteType(TBsonType BsonType);
	void __fastcall WriteKey();
	void __fastcall WriteInteger(const int Value);
	void __fastcall WriteInt64(const __int64 Value);
	void __fastcall WriteDouble(const double Value);
	void __fastcall WriteString(const System::UnicodeString Value);
	void __fastcall WriteCString(const System::UnicodeString Value);
	void __fastcall WriteBytes(const System::TArray__1<System::Byte> Value, System::Json::Types::TJsonBinaryType BinaryType);
	void __fastcall WriteBoolean(const bool Value);
	void __fastcall WriteOid(const System::Json::Types::TJsonOid &Value);
	void __fastcall InternalWriteStartObject(bool Inlined);
	
protected:
	virtual void __fastcall WriteEnd(const System::Json::Types::TJsonToken Token)/* overload */;
	
public:
	__fastcall TBsonWriter(System::Classes::TBinaryWriter* const ABinaryWriter)/* overload */;
	__fastcall TBsonWriter(System::Classes::TStream* const Stream)/* overload */;
	__fastcall virtual ~TBsonWriter();
	virtual void __fastcall Rewind();
	virtual void __fastcall Close();
	virtual void __fastcall Flush();
	virtual void __fastcall WriteComment(const System::UnicodeString Comment);
	virtual void __fastcall WriteStartObject();
	virtual void __fastcall WriteEndObject();
	virtual void __fastcall WriteStartArray();
	virtual void __fastcall WriteEndArray();
	virtual void __fastcall WriteStartConstructor(const System::UnicodeString Name);
	virtual void __fastcall WritePropertyName(const System::UnicodeString Name)/* overload */;
	virtual void __fastcall WriteNull();
	virtual void __fastcall WriteRaw(const System::UnicodeString Json);
	virtual void __fastcall WriteRawValue(const System::UnicodeString Json);
	virtual void __fastcall WriteUndefined();
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
	virtual void __fastcall WriteValue(const System::TArray__1<System::Byte> Value, System::Json::Types::TJsonBinaryType BinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
	virtual void __fastcall WriteValue(const System::Json::Types::TJsonOid &Value)/* overload */;
	virtual void __fastcall WriteValue(const System::Json::Types::TJsonRegEx &Value)/* overload */;
	virtual void __fastcall WriteValue(const System::Json::Types::TJsonDBRef &Value)/* overload */;
	virtual void __fastcall WriteValue(const System::Json::Types::TJsonCodeWScope &Value)/* overload */;
	virtual void __fastcall WriteMinKey()/* overload */;
	virtual void __fastcall WriteMaxKey()/* overload */;
	void __fastcall WriteCode(const System::UnicodeString Code);
	__property System::Classes::TBinaryWriter* Writer = {read=FWriter};
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  WriteEnd(System::Json::Types::TJsonContainerType ContainerType){ System::Json::Writers::TJsonWriter::WriteEnd(ContainerType); }
	
public:
	inline void __fastcall  WriteEnd(){ System::Json::Writers::TJsonWriter::WriteEnd(); }
	
protected:
	inline void __fastcall  WriteValue(System::Json::Writers::TJsonWriter* const Writer, const System::Rtti::TValue &Value){ System::Json::Writers::TJsonWriter::WriteValue(Writer, Value); }
	
public:
	inline void __fastcall  WriteValue(const char * Value){ System::Json::Writers::TJsonWriter::WriteValue(Value); }
	inline void __fastcall  WriteValue(const System::WideChar * Value){ System::Json::Writers::TJsonWriter::WriteValue(Value); }
	inline void __fastcall  WriteValue(const System::Rtti::TValue &Value){ System::Json::Writers::TJsonWriter::WriteValue(Value); }
	
};


class PASCALIMPLEMENTATION TBsonReader : public System::Json::Readers::TJsonReader
{
	typedef System::Json::Readers::TJsonReader inherited;
	
	
private:
	class DELPHICLASS TContainerContext;
	class PASCALIMPLEMENTATION TContainerContext : public System::TObject
	{
		typedef System::TObject inherited;
		
	public:
		TBsonType Type;
		int Length;
		int Position;
		__fastcall TContainerContext(TBsonType AType);
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TContainerContext() { }
		
	};
	
	
	
private:
	static constexpr System::Byte MaxCharBytesSize = System::Byte(0x80);
	
	#define TBsonReader_CodeWScopeKey u"$code"
	
	System::Sysutils::TEncoding* FEncoding;
	TBsonType FCurrentElementType;
	bool FReadRootValueAsArray;
	System::Classes::TBinaryReader* FReader;
	System::Generics::Collections::TObjectStack__1<TContainerContext*>* FStack;
	TContainerContext* FCurrentContext;
	System::TArray__1<System::Byte> FByteBuffer;
	System::TArray__1<System::WideChar> FCharBuffer;
	System::UnicodeString __fastcall ReadElement();
	System::Json::Types::TJsonCodeWScope __fastcall ReadCodeWScope();
	System::Json::Types::TJsonRegEx __fastcall ReadRegEx();
	System::Json::Types::TJsonDBRef __fastcall ReadDBRef();
	double __fastcall ReadDouble();
	int __fastcall ReadInteger();
	__int64 __fastcall ReadInt64();
	System::Byte __fastcall ReadByte();
	System::UnicodeString __fastcall ReadString()/* overload */;
	System::UnicodeString __fastcall ReadString(int ALength)/* overload */;
	System::UnicodeString __fastcall ReadCString();
	TBsonType __fastcall ReadType();
	void __fastcall ReadByType(TBsonType AType);
	System::TArray__1<System::Byte> __fastcall ReadBinary(/* out */ System::Json::Types::TJsonBinaryType &BinaryType);
	System::TArray__1<System::Byte> __fastcall ReadBytes(int Count);
	void __fastcall MovePosition(int Count);
	void __fastcall PopContext(bool FreeContext);
	void __fastcall PushContext(TContainerContext* const Context);
	
protected:
	virtual bool __fastcall ReadInternal();
	
public:
	__fastcall TBsonReader(System::Classes::TStream* const AStream, bool AReadAsRootValuesArray);
	__fastcall virtual ~TBsonReader();
	virtual void __fastcall Close();
	virtual void __fastcall Skip();
	virtual void __fastcall Rewind();
	__property bool ReadRootValueAsArray = {read=FReadRootValueAsArray, write=FReadRootValueAsArray, nodefault};
	__property TBsonType CurrentElementType = {read=FCurrentElementType, nodefault};
	__property System::Classes::TBinaryReader* Reader = {read=FReader};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Bson */
}	/* namespace Json */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_JSON_BSON)
using namespace System::Json::Bson;
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
#endif	// System_Json_BsonHPP
