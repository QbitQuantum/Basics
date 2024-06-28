// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXStreamPlatform.pas' rev: 34.00 (Android)

#ifndef Data_DbxstreamplatformHPP
#define Data_DbxstreamplatformHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.JSON.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXPlatform.hpp>
#include <Data.DBXStream.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXJSON.hpp>
#include <Data.SqlTimSt.hpp>
#include <Data.FmtBcd.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxstreamplatform
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXJSonReader;
class DELPHICLASS TDBXJSonRow;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXJSonReader : public Data::Dbxcommon::TDBXReader
{
	typedef Data::Dbxcommon::TDBXReader inherited;
	
public:
	__fastcall TDBXJSonReader(Data::Dbxcommon::TDBXContext* const DbxContext, Data::Dbxcommon::TDBXRow* const ADbxRow, const int ARowHandle, const int ACommandHandle, const Data::Dbxcommon::TDBXWritableValueArray ADbxValues, Data::Dbxstream::TDBXJSonStreamReader* const ADbxReader, Data::Dbxstream::TDBXJSonStreamWriter* const ADbxWriter, Data::Dbxstream::TDBXRowBuffer* const ADbxRowBuffer, const bool Updateable);
	__fastcall virtual ~TDBXJSonReader();
	bool __fastcall ReadFirstData();
	virtual void __fastcall DerivedClose();
	virtual bool __fastcall DerivedNext();
	
protected:
	virtual int __fastcall GetRowHandle();
	virtual Data::Dbxcommon::TDBXByteReader* __fastcall GetByteReader();
	virtual bool __fastcall IsUpdateable();
	
private:
	bool __fastcall ReadData();
	__int64 FPosition;
	int FCommandHandle;
	int FRowHandle;
	Data::Dbxstream::TDBXJSonStreamReader* FDbxReader;
	Data::Dbxstream::TDBXJSonStreamWriter* FDbxWriter;
	Data::Dbxstream::TDBXRowBuffer* FDbxRowBuffer;
	bool FUpdateable;
	bool FReadLastBuffer;
	Data::Dbxcommon::TDBXByteReader* FByteReader;
	bool FInitialized;
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXJSonRow : public Data::Dbxcommontable::TDBXStreamerRow
{
	typedef Data::Dbxcommontable::TDBXStreamerRow inherited;
	
private:
	int FValueGeneration;
	System::Generics::Collections::TDictionary__2<Data::Dbxcommon::TDBXValue*,System::TObject*>* FValueDict;
	Data::Dbxstream::TDBXJSonStreamReader* FDbxStreamReader;
	Data::Dbxstream::TDBXJSonStreamWriter* FDbxStreamWriter;
	Data::Dbxstream::TDBXRowBuffer* FDbxRowBuffer;
	Data::Dbxcommon::TDBXLookAheadStreamReader* FDBXLookAheadStreamReader;
	int FBcdFormat;
	bool FOwnsRow;
	void __fastcall ProcessStringOverFlow(Data::Dbxcommon::TDBXWideStringValue* DbxValue)/* overload */;
	void __fastcall ProcessStringOverFlow(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue)/* overload */;
	void __fastcall ProcessStringOverFlow(Data::Dbxcommon::TDBXByteArrayValue* DbxValue)/* overload */;
	bool __fastcall CanRead(Data::Dbxcommon::TDBXValue* Value);
	
protected:
	virtual bool __fastcall UseExtendedTypes();
	virtual void __fastcall GetAnsiString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, char * &AnsiStringVar, System::LongBool &IsNull);
	virtual void __fastcall GetWideChars(Data::Dbxcommon::TDBXWideStringValue* DbxValue, Data::Dbxplatform::TDBXWideChars &WideChars, int &Count, System::LongBool &IsNull);
	virtual void __fastcall GetAnsiChars(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, Data::Dbxplatform::TDBXAnsiChars &AnsiChars, int &Count, System::LongBool &IsNull);
	virtual void __fastcall GetBoolean(Data::Dbxcommon::TDBXBooleanValue* DbxValue, System::LongBool &Value, System::LongBool &IsNull);
	virtual void __fastcall GetUInt8(Data::Dbxcommon::TDBXUInt8Value* DbxValue, System::Byte &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt8(Data::Dbxcommon::TDBXInt8Value* DbxValue, System::Int8 &Value, System::LongBool &IsNull);
	virtual void __fastcall GetUInt16(Data::Dbxcommon::TDBXUInt16Value* DbxValue, System::Word &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt16(Data::Dbxcommon::TDBXInt16Value* DbxValue, short &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt32(Data::Dbxcommon::TDBXInt32Value* DbxValue, int &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt64(Data::Dbxcommon::TDBXInt64Value* DbxValue, __int64 &Value, System::LongBool &IsNull);
	virtual void __fastcall GetSingle(Data::Dbxcommon::TDBXSingleValue* DbxValue, float &Value, System::LongBool &IsNull);
	virtual void __fastcall GetDouble(Data::Dbxcommon::TDBXDoubleValue* DbxValue, double &Value, System::LongBool &IsNull);
	virtual void __fastcall GetBcd(Data::Dbxcommon::TDBXBcdValue* DbxValue, Data::Fmtbcd::TBcd &Value, System::LongBool &IsNull);
	virtual void __fastcall GetDate(Data::Dbxcommon::TDBXDateValue* DbxValue, Data::Dbxcommon::TDBXDate &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTime(Data::Dbxcommon::TDBXTimeValue* DbxValue, Data::Dbxcommon::TDBXTime &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStamp(Data::Dbxcommon::TDBXTimeStampValue* DbxValue, Data::Sqltimst::TSQLTimeStamp &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStampOffset(Data::Dbxcommon::TDBXTimeStampOffsetValue* DbxValue, Data::Sqltimst::TSQLTimeStampOffset &Value, System::LongBool &IsNull);
	virtual void __fastcall GetBytes(Data::Dbxcommon::TDBXByteArrayValue* DbxValue, __int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length, __int64 &ReturnLength, System::LongBool &IsNull);
	virtual void __fastcall GetByteLength(Data::Dbxcommon::TDBXByteArrayValue* DbxValue, __int64 &ByteLength, System::LongBool &IsNull);
	virtual void __fastcall GetStream(Data::Dbxcommon::TDBXStreamValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall GetStream(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall GetStreamBytes(Data::Dbxcommon::TDBXStreamValue* DbxValue, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length, __int64 ReturnLength, System::LongBool &IsNull);
	virtual void __fastcall GetStreamLength(Data::Dbxcommon::TDBXStreamValue* DbxValue, __int64 StreamLength, System::LongBool &IsNull);
	virtual void __fastcall GetDBXReader(Data::Dbxcommon::TDBXReaderValue* DbxValue, Data::Dbxcommon::TDBXReader* &Value, System::LongBool &IsNull);
	virtual void __fastcall GetJSONValue(Data::Dbxcommon::TDBXJSONValue* DbxValue, System::Json::TJSONValue* &Value, System::LongBool &IsNull);
	virtual void __fastcall SetJSONValue(Data::Dbxcommon::TDBXJSONValue* DbxValue, System::Json::TJSONValue* Value);
	virtual void __fastcall GetCallbackValue(Data::Dbxcommon::TDBXCallbackValue* DbxValue, Data::Dbxjson::TDBXCallback* &Value, System::LongBool &IsNull);
	virtual void __fastcall SetCallbackValue(Data::Dbxcommon::TDBXCallbackValue* DbxValue, Data::Dbxjson::TDBXCallback* Value);
	virtual bool __fastcall IsStoredNull(Data::Dbxcommon::TDBXValue* DbxValue);
	virtual void __fastcall SetNull(Data::Dbxcommon::TDBXValue* DbxValue);
	virtual void __fastcall SetWideChars(Data::Dbxcommon::TDBXWideStringValue* DbxValue, const System::UnicodeString Value);
	virtual void __fastcall SetString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetAnsiChars(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetBoolean(Data::Dbxcommon::TDBXBooleanValue* DbxValue, bool Value);
	virtual void __fastcall SetUInt8(Data::Dbxcommon::TDBXUInt8Value* DbxValue, System::Byte Value);
	virtual void __fastcall SetInt8(Data::Dbxcommon::TDBXInt8Value* DbxValue, System::Int8 Value);
	virtual void __fastcall SetUInt16(Data::Dbxcommon::TDBXUInt16Value* DbxValue, System::Word Value);
	virtual void __fastcall SetInt16(Data::Dbxcommon::TDBXInt16Value* DbxValue, short Value);
	virtual void __fastcall SetInt32(Data::Dbxcommon::TDBXInt32Value* DbxValue, int Value);
	virtual void __fastcall SetInt64(Data::Dbxcommon::TDBXInt64Value* DbxValue, __int64 Value);
	virtual void __fastcall SetDouble(Data::Dbxcommon::TDBXDoubleValue* DbxValue, double Value);
	virtual void __fastcall SetSingle(Data::Dbxcommon::TDBXSingleValue* DbxValue, float Value);
	virtual void __fastcall SetBCD(Data::Dbxcommon::TDBXBcdValue* DbxValue, Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetDate(Data::Dbxcommon::TDBXDateValue* DbxValue, Data::Dbxcommon::TDBXDate Value);
	virtual void __fastcall SetTime(Data::Dbxcommon::TDBXTimeValue* DbxValue, Data::Dbxcommon::TDBXTime Value);
	virtual void __fastcall SetTimestamp(Data::Dbxcommon::TDBXTimeStampValue* DbxValue, Data::Sqltimst::TSQLTimeStamp &Value);
	virtual void __fastcall SetTimestampOffset(Data::Dbxcommon::TDBXTimeStampOffsetValue* DbxValue, Data::Sqltimst::TSQLTimeStampOffset &Value);
	virtual void __fastcall SetDynamicBytes(Data::Dbxcommon::TDBXValue* DbxValue, __int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Count);
	virtual void __fastcall SetAnsiMemo(Data::Dbxcommon::TDBXAnsiMemoValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetWideMemo(Data::Dbxcommon::TDBXWideMemoValue* DbxValue, const System::UnicodeString Value);
	virtual void __fastcall SetDBXReader(Data::Dbxcommon::TDBXReaderValue* DbxValue, Data::Dbxcommon::TDBXReader* Value);
	virtual System::UnicodeString __fastcall GetObjectTypeName(int Ordinal);
	virtual void __fastcall SetStream(Data::Dbxcommon::TDBXStreamValue* DbxValue, Data::Dbxcommon::TDBXStreamReader* StreamReader)/* overload */;
	virtual Data::Dbxcommon::TDBXValue* __fastcall CreateCustomValue(Data::Dbxcommon::TDBXValueType* const ValueType);
	virtual void __fastcall SetValueType(Data::Dbxcommon::TDBXValueType* ValueType);
	
public:
	__property Data::Dbxstream::TDBXRowBuffer* RowBuffer = {read=FDbxRowBuffer};
	__property int BcdFormat = {read=FBcdFormat, write=FBcdFormat, nodefault};
	__fastcall TDBXJSonRow(Data::Dbxcommon::TDBXContext* DBXContext, Data::Dbxstream::TDBXJSonStreamReader* DbxStreamReader, Data::Dbxstream::TDBXJSonStreamWriter* DbxStreamWriter, Data::Dbxstream::TDBXRowBuffer* DbxRowBuffer, bool AOwnsRow);
	__fastcall virtual ~TDBXJSonRow();
	virtual void __fastcall ClearParameters();
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetStream(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull){ Data::Dbxcommon::TDBXRow::GetStream(DbxValue, Stream, IsNull); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxstreamplatform */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXSTREAMPLATFORM)
using namespace Data::Dbxstreamplatform;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxstreamplatformHPP
