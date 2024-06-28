// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMemoryRow.pas' rev: 34.00 (iOS)

#ifndef Data_DbxmemoryrowHPP
#define Data_DbxmemoryrowHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.JSON.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXPlatform.hpp>
#include <Data.FmtBcd.hpp>
#include <Data.SqlTimSt.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmemoryrow
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXMemoryRow;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXMemoryRow : public Data::Dbxcommon::TDBXRow
{
	typedef Data::Dbxcommon::TDBXRow inherited;
	
private:
	Data::Dbxcommon::TDBXWritableValueArray FValueRow;
	void __fastcall ClearValues(Data::Dbxcommon::TDBXWritableValueArray AValues);
	
protected:
	virtual void __fastcall SetAnsiString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall GetAnsiString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, char * &AnsiStringBuilder, System::LongBool &IsNull);
	virtual void __fastcall GetJSONValue(Data::Dbxcommon::TDBXJSONValue* DbxValue, System::Json::TJSONValue* &Value, System::LongBool &IsNull);
	virtual void __fastcall SetJSONValue(Data::Dbxcommon::TDBXJSONValue* DbxValue, System::Json::TJSONValue* Value);
	virtual void __fastcall SetTimestamp(Data::Dbxcommon::TDBXTimeStampValue* DbxValue, Data::Sqltimst::TSQLTimeStamp &Value);
	virtual void __fastcall GetTimeStamp(Data::Dbxcommon::TDBXTimeStampValue* DbxValue, Data::Sqltimst::TSQLTimeStamp &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTime(Data::Dbxcommon::TDBXTimeValue* DbxValue, Data::Dbxcommon::TDBXTime &Value, System::LongBool &IsNull);
	virtual void __fastcall SetTime(Data::Dbxcommon::TDBXTimeValue* DbxValue, Data::Dbxcommon::TDBXTime Value);
	virtual void __fastcall SetDate(Data::Dbxcommon::TDBXDateValue* DbxValue, Data::Dbxcommon::TDBXDate Value);
	virtual void __fastcall GetDate(Data::Dbxcommon::TDBXDateValue* DbxValue, Data::Dbxcommon::TDBXDate &Value, System::LongBool &IsNull);
	virtual void __fastcall GetBoolean(Data::Dbxcommon::TDBXBooleanValue* DbxValue, System::LongBool &Value, System::LongBool &IsNull);
	virtual void __fastcall SetBoolean(Data::Dbxcommon::TDBXBooleanValue* DbxValue, bool Value);
	virtual void __fastcall GetInt16(Data::Dbxcommon::TDBXInt16Value* DbxValue, short &Value, System::LongBool &IsNull);
	virtual void __fastcall SetInt16(Data::Dbxcommon::TDBXInt16Value* DbxValue, short Value);
	virtual void __fastcall GetInt32(Data::Dbxcommon::TDBXInt32Value* DbxValue, int &Value, System::LongBool &IsNull);
	virtual void __fastcall SetInt32(Data::Dbxcommon::TDBXInt32Value* DbxValue, int Value);
	virtual void __fastcall GetInt64(Data::Dbxcommon::TDBXInt64Value* DbxValue, __int64 &Value, System::LongBool &IsNull);
	virtual void __fastcall SetInt64(Data::Dbxcommon::TDBXInt64Value* DbxValue, __int64 Value);
	virtual void __fastcall GetInt8(Data::Dbxcommon::TDBXInt8Value* DbxValue, System::Int8 &Value, System::LongBool &IsNull);
	virtual void __fastcall SetInt8(Data::Dbxcommon::TDBXInt8Value* DbxValue, System::Int8 Value);
	virtual void __fastcall SetUInt8(Data::Dbxcommon::TDBXUInt8Value* DbxValue, System::Byte Value);
	virtual void __fastcall GetUInt8(Data::Dbxcommon::TDBXUInt8Value* DbxValue, System::Byte &Value, System::LongBool &IsNull);
	virtual void __fastcall GetUInt16(Data::Dbxcommon::TDBXUInt16Value* DbxValue, System::Word &Value, System::LongBool &IsNull);
	virtual void __fastcall SetUInt16(Data::Dbxcommon::TDBXUInt16Value* DbxValue, System::Word Value);
	virtual void __fastcall GetBcd(Data::Dbxcommon::TDBXBcdValue* DbxValue, Data::Fmtbcd::TBcd &Value, System::LongBool &IsNull);
	virtual void __fastcall SetBCD(Data::Dbxcommon::TDBXBcdValue* DbxValue, Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall GetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::WideChar * &WideStringBuilder, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall SetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, const System::UnicodeString Value);
	virtual void __fastcall SetValueType(Data::Dbxcommon::TDBXValueType* ValueType);
	virtual void __fastcall GetDBXReader(Data::Dbxcommon::TDBXReaderValue* DbxValue, Data::Dbxcommon::TDBXReader* &Value, System::LongBool &IsNull);
	virtual void __fastcall SetDBXReader(Data::Dbxcommon::TDBXReaderValue* DbxValue, Data::Dbxcommon::TDBXReader* Value);
	virtual void __fastcall GetSingle(Data::Dbxcommon::TDBXSingleValue* DbxValue, float &Value, System::LongBool &IsNull);
	virtual void __fastcall SetSingle(Data::Dbxcommon::TDBXSingleValue* DbxValue, float Value);
	virtual void __fastcall GetDouble(Data::Dbxcommon::TDBXDoubleValue* DbxValue, double &Value, System::LongBool &IsNull);
	virtual void __fastcall SetDouble(Data::Dbxcommon::TDBXDoubleValue* DbxValue, double Value);
	virtual void __fastcall SetStream(Data::Dbxcommon::TDBXStreamValue* DbxValue, Data::Dbxcommon::TDBXStreamReader* StreamReader)/* overload */;
	virtual void __fastcall GetStream(Data::Dbxcommon::TDBXStreamValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull)/* overload */;
	
public:
	__fastcall TDBXMemoryRow(Data::Dbxcommon::TDBXContext* DBXContext, Data::Dbxcommon::TDBXValueTypeArray Values);
	__fastcall virtual ~TDBXMemoryRow();
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::UnicodeString &Value, System::LongBool &IsNull){ Data::Dbxcommon::TDBXRow::GetWideString(DbxValue, Value, IsNull); }
	inline void __fastcall  GetStream(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull){ Data::Dbxcommon::TDBXRow::GetStream(DbxValue, Stream, IsNull); }
	inline void __fastcall  GetStream(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull){ Data::Dbxcommon::TDBXRow::GetStream(DbxValue, Stream, IsNull); }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmemoryrow */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMEMORYROW)
using namespace Data::Dbxmemoryrow;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmemoryrowHPP
