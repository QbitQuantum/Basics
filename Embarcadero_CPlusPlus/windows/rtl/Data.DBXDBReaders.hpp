// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXDBReaders.pas' rev: 34.00 (Windows)

#ifndef Data_DbxdbreadersHPP
#define Data_DbxdbreadersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DB.hpp>
#include <System.Classes.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXPlatform.hpp>
#include <Data.DBXCommonTable.hpp>
#include <System.SysUtils.hpp>
#include <Data.SqlTimSt.hpp>
#include <Data.FmtBcd.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxdbreaders
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXParamsRow;
class DELPHICLASS TDBXMemoryTable;
class DELPHICLASS TDBXCache;
class DELPHICLASS TDBXTableStorage;
class DELPHICLASS TDBXDBTable;
class DELPHICLASS TDBXParamsTable;
class DELPHICLASS TDBXParamsReader;
class DELPHICLASS TDBXDataSetRow;
class DELPHICLASS TDBXDataSetTable;
class DELPHICLASS TDBXDataSetReader;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXParamsRow : public Data::Dbxcommon::TDBXRow
{
	typedef Data::Dbxcommon::TDBXRow inherited;
	
private:
	Data::Db::TParams* FParams;
	
public:
	__fastcall TDBXParamsRow(Data::Db::TParams* Params);
	virtual Data::Dbxcommon::TDBXValue* __fastcall CreateCustomValue(Data::Dbxcommon::TDBXValueType* const ValueType);
	virtual void __fastcall GetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::UnicodeString &Value, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall GetBoolean(Data::Dbxcommon::TDBXBooleanValue* DbxValue, System::LongBool &Value, System::LongBool &IsNull);
	virtual void __fastcall GetUInt8(Data::Dbxcommon::TDBXUInt8Value* DbxValue, System::Byte &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt8(Data::Dbxcommon::TDBXInt8Value* DbxValue, System::Int8 &Value, System::LongBool &IsNull);
	virtual void __fastcall GetUInt16(Data::Dbxcommon::TDBXUInt16Value* DbxValue, System::Word &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt16(Data::Dbxcommon::TDBXInt16Value* DbxValue, short &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt32(Data::Dbxcommon::TDBXInt32Value* DbxValue, int &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt64(Data::Dbxcommon::TDBXInt64Value* DbxValue, __int64 &Value, System::LongBool &IsNull);
	virtual void __fastcall GetSingle(Data::Dbxcommon::TDBXSingleValue* DbxValue, float &Value, System::LongBool &IsNull);
	virtual void __fastcall GetDouble(Data::Dbxcommon::TDBXDoubleValue* DbxValue, double &Value, System::LongBool &IsNull);
	virtual void __fastcall GetAnsiString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, char * &AnsiStringBuilder, System::LongBool &IsNull);
	virtual void __fastcall GetDate(Data::Dbxcommon::TDBXDateValue* DbxValue, Data::Dbxcommon::TDBXDate &Value, System::LongBool &IsNull);
#ifndef _WIN64
	virtual void __fastcall GetBytes(Data::Dbxcommon::TDBXByteArrayValue* DbxValue, __int64 Offset, const System::DynamicArray<System::Byte> Buffer, __int64 BufferOffset, __int64 Length, __int64 &ReturnLength, System::LongBool &IsNull);
#else /* _WIN64 */
	virtual void __fastcall GetBytes(Data::Dbxcommon::TDBXByteArrayValue* DbxValue, __int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length, __int64 &ReturnLength, System::LongBool &IsNull);
#endif /* _WIN64 */
	virtual void __fastcall GetByteLength(Data::Dbxcommon::TDBXByteArrayValue* DbxValue, __int64 &ByteLength, System::LongBool &IsNull);
	virtual void __fastcall GetTime(Data::Dbxcommon::TDBXTimeValue* DbxValue, Data::Dbxcommon::TDBXTime &Value, System::LongBool &IsNull);
	virtual void __fastcall GetBcd(Data::Dbxcommon::TDBXBcdValue* DbxValue, Data::Fmtbcd::TBcd &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStamp(Data::Dbxcommon::TDBXTimeStampValue* DbxValue, Data::Sqltimst::TSQLTimeStamp &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStampOffset(Data::Dbxcommon::TDBXTimeStampOffsetValue* DbxValue, Data::Sqltimst::TSQLTimeStampOffset &Value, System::LongBool &IsNull);
	virtual void __fastcall GetStream(Data::Dbxcommon::TDBXStreamValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall SetNull(Data::Dbxcommon::TDBXValue* DbxValue);
	virtual void __fastcall SetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, const System::UnicodeString Value);
	virtual void __fastcall SetBoolean(Data::Dbxcommon::TDBXBooleanValue* DbxValue, bool Value);
	virtual void __fastcall SetUInt8(Data::Dbxcommon::TDBXUInt8Value* DbxValue, System::Byte Value);
	virtual void __fastcall SetInt8(Data::Dbxcommon::TDBXInt8Value* DbxValue, System::Int8 Value);
	virtual void __fastcall SetUInt16(Data::Dbxcommon::TDBXUInt16Value* DbxValue, System::Word Value);
	virtual void __fastcall SetInt16(Data::Dbxcommon::TDBXInt16Value* DbxValue, short Value);
	virtual void __fastcall SetInt32(Data::Dbxcommon::TDBXInt32Value* DbxValue, int Value);
	virtual void __fastcall SetInt64(Data::Dbxcommon::TDBXInt64Value* DbxValue, __int64 Value);
	virtual void __fastcall SetSingle(Data::Dbxcommon::TDBXSingleValue* DbxValue, float Value);
	virtual void __fastcall SetDouble(Data::Dbxcommon::TDBXDoubleValue* DbxValue, double Value);
	virtual void __fastcall SetAnsiString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetDate(Data::Dbxcommon::TDBXDateValue* DbxValue, Data::Dbxcommon::TDBXDate Value);
	virtual void __fastcall SetTime(Data::Dbxcommon::TDBXTimeValue* DbxValue, Data::Dbxcommon::TDBXTime Value);
	virtual void __fastcall SetBCD(Data::Dbxcommon::TDBXBcdValue* DbxValue, Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetTimestamp(Data::Dbxcommon::TDBXTimeStampValue* DbxValue, Data::Sqltimst::TSQLTimeStamp &Value);
	virtual void __fastcall SetTimestampOffset(Data::Dbxcommon::TDBXTimeStampOffsetValue* DbxValue, Data::Sqltimst::TSQLTimeStampOffset &Value);
	virtual void __fastcall SetStream(Data::Dbxcommon::TDBXStreamValue* DbxValue, Data::Dbxcommon::TDBXStreamReader* StreamReader)/* overload */;
	virtual void __fastcall ValueSet(Data::Dbxcommon::TDBXWritableValue* Value);
#ifndef _WIN64
	virtual void __fastcall SetDynamicBytes(Data::Dbxcommon::TDBXValue* DbxValue, __int64 Offset, const System::DynamicArray<System::Byte> Buffer, __int64 BufferOffset, __int64 Length);
#else /* _WIN64 */
	virtual void __fastcall SetDynamicBytes(Data::Dbxcommon::TDBXValue* DbxValue, __int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length);
#endif /* _WIN64 */
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXParamsRow() { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::WideChar * &WideStringBuilder, System::LongBool &IsNull){ Data::Dbxcommon::TDBXRow::GetWideString(DbxValue, WideStringBuilder, IsNull); }
	inline void __fastcall  GetStream(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull){ Data::Dbxcommon::TDBXRow::GetStream(DbxValue, Stream, IsNull); }
	inline void __fastcall  GetStream(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull){ Data::Dbxcommon::TDBXRow::GetStream(DbxValue, Stream, IsNull); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXMemoryTable : public Data::Dbxcommontable::TDBXTable
{
	typedef Data::Dbxcommontable::TDBXTable inherited;
	
private:
	int FIndex;
	int FOrderByColumn;
	System::UnicodeString FName;
	Data::Dbxcommon::TDBXValueTypeArray FValueTypes;
	System::Generics::Collections::TList__1<Data::Dbxcommon::TDBXWritableValueArray>* FValueRows;
	Data::Dbxcommon::TDBXWritableValueArray __fastcall CreateWritableValueArray();
	HIDESBASE void __fastcall ClearValues(Data::Dbxcommon::TDBXWritableValueArray AValues);
	void __fastcall ClearValueTypes(Data::Dbxcommon::TDBXValueTypeArray AValueTypes);
	
protected:
	virtual int __fastcall GetTableCount();
	virtual void __fastcall OrderByColumn(int Column);
	
public:
	virtual void __fastcall Close();
	__fastcall TDBXMemoryTable();
	__fastcall virtual ~TDBXMemoryTable();
	virtual void __fastcall Insert();
	virtual void __fastcall Post();
	virtual void __fastcall Clear();
	virtual bool __fastcall InBounds();
	virtual bool __fastcall Next();
	virtual bool __fastcall First();
	virtual void __fastcall SetColumns(const Data::Dbxcommon::TDBXValueTypeArray Columns);
	virtual Data::Dbxcommon::TDBXValueTypeArray __fastcall GetColumns();
	virtual void __fastcall SetDBXTableName(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetDBXTableName();
	virtual void __fastcall AcceptChanges();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall CreateTableView(const System::UnicodeString OrderByColumnName);
	virtual bool __fastcall FindStringKey(const int Ordinal, const System::UnicodeString Value);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXCache : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	bool FOwnsValues;
	Data::Dbxcommon::TDBXValueTypeArray FValueTypes;
	System::Generics::Collections::TList__1<Data::Dbxcommon::TDBXWritableValueArray>* FValueRows;
	System::Generics::Collections::TList__1<Data::Dbxcommon::TDBXWritableValueArray>* FInsertedRows;
	System::Generics::Collections::TList__1<Data::Dbxcommon::TDBXWritableValueArray>* FDeletedRows;
	System::Generics::Collections::TList__1<Data::Dbxcommon::TDBXWritableValueArray>* FUpdatedRows;
	void __fastcall ClearChangeLog();
	void __fastcall ClearValues(Data::Dbxcommon::TDBXWritableValueArray AValues);
	Data::Dbxcommon::TDBXWritableValueArray __fastcall CreateWritableValueArray();
	void __fastcall ClearValueTypes(Data::Dbxcommon::TDBXValueTypeArray AValueTypes);
	
public:
	void __fastcall AcceptChanges();
	void __fastcall AddRow(Data::Dbxcommon::TDBXWritableValueArray ARow);
	void __fastcall Clear();
	__fastcall TDBXCache()/* overload */;
	__fastcall TDBXCache(bool AOwnsValues)/* overload */;
	void __fastcall DeleteRow(int AIndex);
	__fastcall virtual ~TDBXCache();
	Data::Dbxcommon::TDBXValueTypeArray __fastcall GetColumns();
	void __fastcall Insert(int AIndex);
	void __fastcall SetColumns(Data::Dbxcommon::TDBXValueTypeArray Columns);
	__property System::Generics::Collections::TList__1<Data::Dbxcommon::TDBXWritableValueArray>* DeletedRows = {read=FDeletedRows};
	__property System::Generics::Collections::TList__1<Data::Dbxcommon::TDBXWritableValueArray>* InsertedRows = {read=FInsertedRows};
	__property bool OwnsValues = {read=FOwnsValues, nodefault};
	__property System::Generics::Collections::TList__1<Data::Dbxcommon::TDBXWritableValueArray>* UpdatedRows = {read=FUpdatedRows};
	__property System::Generics::Collections::TList__1<Data::Dbxcommon::TDBXWritableValueArray>* ValueRows = {read=FValueRows};
	__property Data::Dbxcommon::TDBXValueTypeArray ValueTypes = {read=FValueTypes};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXTableStorage : public Data::Dbxcommontable::TDBXTable
{
	typedef Data::Dbxcommontable::TDBXTable inherited;
	
private:
	int FIndex;
	System::UnicodeString FName;
	TDBXCache* FCache;
	Data::Dbxcommontable::TDBXTableRow* FOriginalRow;
	Data::Dbxcommontable::TDBXTable* FDeletedTable;
	Data::Dbxcommontable::TDBXTable* FInsertedTable;
	Data::Dbxcommontable::TDBXTable* FUpdatedTable;
	HIDESBASE void __fastcall ClearValues(Data::Dbxcommon::TDBXWritableValueArray AValues);
	Data::Dbxcommon::TDBXWritableValueArray __fastcall CloneRow(const Data::Dbxcommon::TDBXWritableValueArray ARow);
	void __fastcall AddRow(Data::Dbxcommontable::TDBXTable* const ATable, const Data::Dbxcommon::TDBXWritableValueArray ARow, const bool AClone);
	void __fastcall UpdateCurrentRow();
	
protected:
	virtual Data::Dbxcommontable::TDBXTable* __fastcall GetDeletedRows();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall GetInsertedRows();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall GetUpdatedRows();
	virtual Data::Dbxcommontable::TDBXTableRow* __fastcall GetOriginalRow();
	virtual int __fastcall GetTableCount();
	virtual void __fastcall OrderByColumn(int Column);
	
public:
	virtual void __fastcall Close();
	__fastcall TDBXTableStorage()/* overload */;
	__fastcall TDBXTableStorage(const bool AOwnsValues)/* overload */;
	__fastcall virtual ~TDBXTableStorage();
	virtual void __fastcall Insert()/* overload */;
	HIDESBASE void __fastcall Insert(const int AIndex)/* overload */;
	virtual void __fastcall DeleteRow()/* overload */;
	HIDESBASE void __fastcall DeleteRow(const int AIndex)/* overload */;
	Data::Dbxcommon::TDBXWritableValueArray __fastcall GetRow(const int AIndex);
	virtual bool __fastcall Edit();
	virtual void __fastcall Cancel();
	virtual void __fastcall Post();
	virtual void __fastcall Clear();
	virtual bool __fastcall InBounds();
	virtual bool __fastcall Next();
	virtual bool __fastcall First();
	virtual void __fastcall SetColumns(const Data::Dbxcommon::TDBXValueTypeArray Columns);
	virtual Data::Dbxcommon::TDBXValueTypeArray __fastcall GetColumns();
	virtual void __fastcall SetDBXTableName(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetDBXTableName();
	virtual void __fastcall AcceptChanges();
	virtual void __fastcall CopyFrom(Data::Dbxcommontable::TDBXTable* const Source)/* overload */;
	virtual Data::Dbxcommontable::TDBXTable* __fastcall CreateTableView(const System::UnicodeString OrderByColumnName);
	virtual bool __fastcall FindStringKey(const int Ordinal, const System::UnicodeString Value);
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  CopyFrom(Data::Dbxcommon::TDBXReader* const Source){ Data::Dbxcommontable::TDBXTable::CopyFrom(Source); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDBTable : public Data::Dbxcommontable::TDBXRowTable
{
	typedef Data::Dbxcommontable::TDBXRowTable inherited;
	
private:
	System::UnicodeString FCollectionName;
	Data::Dbxcommon::TDBXValueTypeArray FValueTypes;
	static int __fastcall ToDataType(Data::Db::TFieldType FieldType);
	static int __fastcall ToDataSubType(Data::Db::TFieldType FieldType);
	static Data::Db::TFieldType __fastcall ToFieldType(Data::Dbxcommon::TDBXValueType* ValueType);
	static int __fastcall ToDBXParameterDirection(Data::Db::TParamType ParameterType);
	static Data::Db::TParamType __fastcall ToParameterType(int ParameterDirection);
	
protected:
	void __fastcall FreeValueTypes();
	__property Data::Dbxcommon::TDBXValueTypeArray ValueTypes = {read=FValueTypes, write=FValueTypes};
	__property System::UnicodeString CollectionName = {read=FCollectionName};
	virtual void __fastcall SetDBXTableName(const System::UnicodeString CollectionName);
	virtual System::UnicodeString __fastcall GetDBXTableName();
public:
	/* TDBXRowTable.Create */ inline __fastcall TDBXDBTable(Data::Dbxcommon::TDBXContext* const DbxContext, Data::Dbxcommon::TDBXRow* const Row) : Data::Dbxcommontable::TDBXRowTable(DbxContext, Row) { }
	/* TDBXRowTable.Destroy */ inline __fastcall virtual ~TDBXDBTable() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXParamsTable : public TDBXDBTable
{
	typedef TDBXDBTable inherited;
	
private:
	Data::Db::TParams* FParams;
	bool FAtEnd;
	bool FInstanceOwner;
	static void __fastcall CopyValueTypes(const Data::Dbxcommon::TDBXValueTypeArray ValueTypes, Data::Db::TParams* const Params);
	static void __fastcall CopyValueType(int Ordinal, Data::Dbxcommon::TDBXValueType* ValueType, Data::Db::TParam* Param);
	
protected:
	virtual Data::Dbxcommon::TDBXValueTypeArray __fastcall GetColumns();
	virtual void __fastcall SetColumns(const Data::Dbxcommon::TDBXValueTypeArray Columns);
	virtual System::TObject* __fastcall GetStorage();
	
public:
	__fastcall TDBXParamsTable()/* overload */;
	__fastcall TDBXParamsTable(Data::Db::TParams* Params, bool InstanceOwner)/* overload */;
	__fastcall virtual ~TDBXParamsTable();
	virtual bool __fastcall First();
	virtual bool __fastcall Next();
	virtual bool __fastcall InBounds();
	virtual void __fastcall Close();
	virtual int __fastcall GetOrdinal(const System::UnicodeString ColumnName)/* overload */;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXParamsReader : public Data::Dbxcommontable::TDBXTableReader
{
	typedef Data::Dbxcommontable::TDBXTableReader inherited;
	
public:
	__fastcall TDBXParamsReader(Data::Db::TParams* Params, bool InstanceOwner);
	static void __fastcall CopyReaderToParams(Data::Dbxcommon::TDBXReader* Reader, Data::Db::TParams* Params);
	static Data::Db::TParams* __fastcall ToParams(System::Classes::TPersistent* AOwner, Data::Dbxcommon::TDBXReader* Reader, bool AOwnsInstance);
	__fastcall virtual ~TDBXParamsReader();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDataSetRow : public Data::Dbxcommon::TDBXRow
{
	typedef Data::Dbxcommon::TDBXRow inherited;
	
private:
	Data::Db::TDataSet* FTable;
	bool __fastcall EnsureEditState();
	
public:
	__fastcall TDBXDataSetRow(Data::Db::TDataSet* Table);
	virtual void __fastcall GetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::WideChar * &WideStringBuilder, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall GetBoolean(Data::Dbxcommon::TDBXBooleanValue* DbxValue, System::LongBool &Value, System::LongBool &IsNull);
	virtual void __fastcall GetUInt8(Data::Dbxcommon::TDBXUInt8Value* DbxValue, System::Byte &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt8(Data::Dbxcommon::TDBXInt8Value* DbxValue, System::Int8 &Value, System::LongBool &IsNull);
	virtual void __fastcall GetUInt16(Data::Dbxcommon::TDBXUInt16Value* DbxValue, System::Word &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt16(Data::Dbxcommon::TDBXInt16Value* DbxValue, short &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt32(Data::Dbxcommon::TDBXInt32Value* DbxValue, int &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt64(Data::Dbxcommon::TDBXInt64Value* DbxValue, __int64 &Value, System::LongBool &IsNull);
	virtual void __fastcall GetSingle(Data::Dbxcommon::TDBXSingleValue* DbxValue, float &Value, System::LongBool &IsNull);
	virtual void __fastcall GetDouble(Data::Dbxcommon::TDBXDoubleValue* DbxValue, double &Value, System::LongBool &IsNull);
	virtual void __fastcall GetAnsiString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, char * &AnsiStringBuilder, System::LongBool &IsNull);
	virtual void __fastcall GetDate(Data::Dbxcommon::TDBXDateValue* DbxValue, Data::Dbxcommon::TDBXDate &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTime(Data::Dbxcommon::TDBXTimeValue* DbxValue, Data::Dbxcommon::TDBXTime &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStamp(Data::Dbxcommon::TDBXTimeStampValue* DbxValue, Data::Sqltimst::TSQLTimeStamp &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStampOffset(Data::Dbxcommon::TDBXTimeStampOffsetValue* DbxValue, Data::Sqltimst::TSQLTimeStampOffset &Value, System::LongBool &IsNull);
	virtual void __fastcall GetBcd(Data::Dbxcommon::TDBXBcdValue* DbxValue, Data::Fmtbcd::TBcd &Value, System::LongBool &IsNull);
#ifndef _WIN64
	virtual void __fastcall GetBytes(Data::Dbxcommon::TDBXByteArrayValue* DbxValue, __int64 Offset, const System::DynamicArray<System::Byte> Buffer, __int64 BufferOffset, __int64 Length, __int64 &ReturnLength, System::LongBool &IsNull);
#else /* _WIN64 */
	virtual void __fastcall GetBytes(Data::Dbxcommon::TDBXByteArrayValue* DbxValue, __int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length, __int64 &ReturnLength, System::LongBool &IsNull);
#endif /* _WIN64 */
	virtual void __fastcall GetByteLength(Data::Dbxcommon::TDBXByteArrayValue* DbxValue, __int64 &ByteLength, System::LongBool &IsNull);
	virtual void __fastcall GetStream(Data::Dbxcommon::TDBXStreamValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall SetNull(Data::Dbxcommon::TDBXValue* DbxValue);
	virtual void __fastcall SetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, const System::UnicodeString Value);
	virtual void __fastcall SetBoolean(Data::Dbxcommon::TDBXBooleanValue* DbxValue, bool Value);
	virtual void __fastcall SetUInt8(Data::Dbxcommon::TDBXUInt8Value* DbxValue, System::Byte Value);
	virtual void __fastcall SetInt8(Data::Dbxcommon::TDBXInt8Value* DbxValue, System::Int8 Value);
	virtual void __fastcall SetUInt16(Data::Dbxcommon::TDBXUInt16Value* DbxValue, System::Word Value);
	virtual void __fastcall SetInt16(Data::Dbxcommon::TDBXInt16Value* DbxValue, short Value);
	virtual void __fastcall SetInt32(Data::Dbxcommon::TDBXInt32Value* DbxValue, int Value);
	virtual void __fastcall SetInt64(Data::Dbxcommon::TDBXInt64Value* DbxValue, __int64 Value);
	virtual void __fastcall SetSingle(Data::Dbxcommon::TDBXSingleValue* DbxValue, float Value);
	virtual void __fastcall SetDouble(Data::Dbxcommon::TDBXDoubleValue* DbxValue, double Value);
	virtual void __fastcall SetAnsiString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetDate(Data::Dbxcommon::TDBXDateValue* DbxValue, Data::Dbxcommon::TDBXDate Value);
	virtual void __fastcall SetTime(Data::Dbxcommon::TDBXTimeValue* DbxValue, Data::Dbxcommon::TDBXTime Value);
	virtual void __fastcall SetBCD(Data::Dbxcommon::TDBXBcdValue* DbxValue, Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetStream(Data::Dbxcommon::TDBXStreamValue* DbxValue, Data::Dbxcommon::TDBXStreamReader* StreamReader)/* overload */;
#ifndef _WIN64
	virtual void __fastcall SetDynamicBytes(Data::Dbxcommon::TDBXValue* DbxValue, __int64 Offset, const System::DynamicArray<System::Byte> Buffer, __int64 BufferOffset, __int64 Length);
#else /* _WIN64 */
	virtual void __fastcall SetDynamicBytes(Data::Dbxcommon::TDBXValue* DbxValue, __int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length);
#endif /* _WIN64 */
	virtual void __fastcall SetTimestamp(Data::Dbxcommon::TDBXTimeStampValue* DbxValue, Data::Sqltimst::TSQLTimeStamp &Value);
	virtual void __fastcall SetTimestampOffset(Data::Dbxcommon::TDBXTimeStampOffsetValue* DbxValue, Data::Sqltimst::TSQLTimeStampOffset &Value);
	virtual void __fastcall ValueSet(Data::Dbxcommon::TDBXWritableValue* Value);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDataSetRow() { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::UnicodeString &Value, System::LongBool &IsNull){ Data::Dbxcommon::TDBXRow::GetWideString(DbxValue, Value, IsNull); }
	inline void __fastcall  GetStream(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull){ Data::Dbxcommon::TDBXRow::GetStream(DbxValue, Stream, IsNull); }
	inline void __fastcall  GetStream(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull){ Data::Dbxcommon::TDBXRow::GetStream(DbxValue, Stream, IsNull); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDataSetTable : public TDBXDBTable
{
	typedef TDBXDBTable inherited;
	
private:
	bool FOwnsTable;
	Data::Db::TDataSet* FTable;
	
protected:
	__fastcall TDBXDataSetTable(const System::UnicodeString CollectionName, Data::Db::TDataSet* Table, bool OwnsTable, bool ValuesNeedCreate)/* overload */;
	__property Data::Db::TDataSet* Table = {read=FTable};
	virtual void __fastcall SkipOriginalRow();
	virtual void __fastcall SetDBXTableName(const System::UnicodeString CollectionName);
	virtual System::UnicodeString __fastcall GetDBXTableName();
	virtual Data::Dbxcommon::TDBXValueTypeArray __fastcall GetColumns();
	virtual System::TObject* __fastcall GetStorage();
	int __fastcall GetDataSize(Data::Db::TFieldDef* FieldDef, Data::Db::TField* Field);
	
public:
	__fastcall TDBXDataSetTable(Data::Db::TDataSet* Dataset, bool InstanceOwner)/* overload */;
	__fastcall virtual ~TDBXDataSetTable();
	virtual bool __fastcall First();
	virtual bool __fastcall Next();
	virtual bool __fastcall InBounds();
	virtual void __fastcall Insert();
	virtual void __fastcall Post();
	virtual void __fastcall DeleteRow();
	virtual void __fastcall Close();
	virtual int __fastcall GetOrdinal(const System::UnicodeString ColumnName)/* overload */;
	void __fastcall FailIfRowIsNew();
	void __fastcall CopyValueTypeProperties(Data::Db::TFieldDef* FieldDef, Data::Dbxcommon::TDBXValueType* ValueType, int Ordinal);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDataSetReader : public Data::Dbxcommontable::TDBXTableReader
{
	typedef Data::Dbxcommontable::TDBXTableReader inherited;
	
public:
	__fastcall virtual TDBXDataSetReader(Data::Db::TDataSet* Params, bool InstanceOwner)/* overload */;
	__fastcall TDBXDataSetReader(TDBXDataSetTable* Params)/* overload */;
public:
	/* TDBXTableReader.Create */ inline __fastcall TDBXDataSetReader(Data::Dbxcommontable::TDBXTable* const DbxTable)/* overload */ : Data::Dbxcommontable::TDBXTableReader(DbxTable) { }
	/* TDBXTableReader.Create */ inline __fastcall TDBXDataSetReader(Data::Dbxcommon::TDBXContext* const Context, Data::Dbxcommontable::TDBXTable* const DbxTable)/* overload */ : Data::Dbxcommontable::TDBXTableReader(Context, DbxTable) { }
	/* TDBXTableReader.Destroy */ inline __fastcall virtual ~TDBXDataSetReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxdbreaders */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXDBREADERS)
using namespace Data::Dbxdbreaders;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxdbreadersHPP
