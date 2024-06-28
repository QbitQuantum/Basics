// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DbxSqlite.pas' rev: 34.00 (iOS)

#ifndef Data_DbxsqliteHPP
#define Data_DbxsqliteHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXCommonResStrs.hpp>
#include <Data.DBXPlatform.hpp>
#include <Data.FmtBcd.hpp>
#include <Data.SqlTimSt.hpp>
#include <System.Classes.hpp>
#include <System.Sqlite.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------
namespace Data
{
namespace Dbxsqlite
{
  _INIT_UNIT(Data_Dbxsqlite);
}	/* namespace Dbxsqlite */
}	/* namespace Data */

#ifndef USEPACKAGES
/* automatically link to libsqlite3.dylib */
#pragma link "libsqlite3.dylib"
#endif


namespace Data
{
namespace Dbxsqlite
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXSqliteProperties;
class DELPHICLASS TDBXSqliteDriverLoader;
class DELPHICLASS TDBXSqliteDriver;
class DELPHICLASS TDBXSqliteConnection;
class DELPHICLASS TDBXSqliteCommand;
class DELPHICLASS TDBXSqliteRow;
class DELPHICLASS TDBXSqliteByteReader;
class DELPHICLASS TDBXSqliteReader;
class DELPHICLASS TDBXSqliteTransaction;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXSqliteProperties : public Data::Dbxcommon::TDBXProperties
{
	typedef Data::Dbxcommon::TDBXProperties inherited;
	
public:
	__fastcall virtual TDBXSqliteProperties(Data::Dbxcommon::TDBXContext* DBXContext)/* overload */;
public:
	/* TDBXProperties.Create */ inline __fastcall virtual TDBXSqliteProperties()/* overload */ : Data::Dbxcommon::TDBXProperties() { }
	/* TDBXProperties.Destroy */ inline __fastcall virtual ~TDBXSqliteProperties() { }
	
};


class PASCALIMPLEMENTATION TDBXSqliteDriverLoader : public Data::Dbxcommon::TDBXDriverLoader
{
	typedef Data::Dbxcommon::TDBXDriverLoader inherited;
	
public:
	__fastcall virtual TDBXSqliteDriverLoader();
	virtual Data::Dbxcommon::TDBXDriver* __fastcall Load(const Data::Dbxcommon::TDBXDriverDef &DriverDef);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSqliteDriverLoader() { }
	
};


class PASCALIMPLEMENTATION TDBXSqliteDriver : public Data::Dbxcommon::TDBXDriver
{
	typedef Data::Dbxcommon::TDBXDriver inherited;
	
private:
	Data::Dbxcommon::TDBXCommand* __fastcall CreateSqliteCommand(Data::Dbxcommon::TDBXContext* DbxContext, Data::Dbxcommon::TDBXConnection* Connection, Data::Dbxcommon::TDBXCommand* MorphicCommand);
	
protected:
	virtual void __fastcall Close();
	virtual Data::Dbxcommon::TDBXConnection* __fastcall CreateConnection(Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder);
	
public:
	__fastcall virtual TDBXSqliteDriver(const Data::Dbxcommon::TDBXDriverDef &DriverDef)/* overload */;
	virtual void __fastcall GetDriverPropertyNames(System::Classes::TStrings* List);
	virtual System::UnicodeString __fastcall GetDriverVersion();
public:
	/* TDBXDriver.Create */ inline __fastcall TDBXSqliteDriver()/* overload */ : Data::Dbxcommon::TDBXDriver() { }
	/* TDBXDriver.Destroy */ inline __fastcall virtual ~TDBXSqliteDriver() { }
	
};


class PASCALIMPLEMENTATION TDBXSqliteConnection : public Data::Dbxcommon::TDBXConnection
{
	typedef Data::Dbxcommon::TDBXConnection inherited;
	
private:
	void *FConnectionHandle;
	int FTransactionId;
	NativeUInt FLibraryHandle;
	
protected:
	virtual void __fastcall Commit(Data::Dbxcommon::TDBXTransaction* const InTransaction);
	virtual Data::Dbxcommon::TDBXTransaction* __fastcall CreateAndBeginTransaction(const int Isolation);
	virtual void __fastcall DerivedClose();
	virtual void __fastcall DerivedGetCommands(const System::UnicodeString CommandType, System::Classes::TStrings* const List);
	virtual void __fastcall DerivedGetCommandTypes(System::Classes::TStrings* const List);
	virtual void __fastcall DerivedOpen();
	virtual System::UnicodeString __fastcall GetProductName();
	virtual System::UnicodeString __fastcall GetProductVersion();
	virtual void __fastcall Rollback(Data::Dbxcommon::TDBXTransaction* const InTransaction);
	
public:
	__fastcall TDBXSqliteConnection(Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder);
	__fastcall virtual ~TDBXSqliteConnection();
	virtual System::UnicodeString __fastcall GetVendorProperty(const System::UnicodeString Name);
	__property void * ConnectionHandle = {read=FConnectionHandle};
};


class PASCALIMPLEMENTATION TDBXSqliteCommand : public Data::Dbxcommon::TDBXCommand
{
	typedef Data::Dbxcommon::TDBXCommand inherited;
	
private:
	int FRowsAffected;
	TDBXSqliteRow* FParameterRow;
	TDBXSqliteConnection* FSqliteConnection;
	void *FStatementHandle;
	
protected:
	virtual Data::Dbxcommon::TDBXRow* __fastcall CreateParameterRow();
	virtual void __fastcall DerivedClose();
	virtual Data::Dbxcommon::TDBXReader* __fastcall DerivedExecuteQuery();
	virtual void __fastcall DerivedExecuteUpdate();
	virtual Data::Dbxcommon::TDBXReader* __fastcall DerivedGetNextReader();
	virtual void __fastcall DerivedOpen();
	virtual void __fastcall DerivedPrepare();
	virtual __int64 __fastcall GetRowsAffected();
	virtual void __fastcall SetMaxBlobSize(const __int64 MaxBlobSize);
	virtual void __fastcall SetRowSetSize(const __int64 RowSetSize);
	virtual void __fastcall SetText(const System::UnicodeString Value);
	
public:
	__fastcall TDBXSqliteCommand(Data::Dbxcommon::TDBXContext* DBXContext, TDBXSqliteConnection* SqliteConnection);
	__fastcall virtual ~TDBXSqliteCommand();
	__property void * StatementHandle = {read=FStatementHandle};
};


class PASCALIMPLEMENTATION TDBXSqliteRow : public Data::Dbxcommon::TDBXRow
{
	typedef Data::Dbxcommon::TDBXRow inherited;
	
private:
	TDBXSqliteConnection* FSqliteConnection;
	void *FStatementHandle;
	
protected:
	virtual void __fastcall GetAnsiString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, char * &AnsiStringBuilder, System::LongBool &IsNull);
	virtual void __fastcall GetBcd(Data::Dbxcommon::TDBXBcdValue* DbxValue, Data::Fmtbcd::TBcd &Value, System::LongBool &IsNull);
	virtual void __fastcall GetBoolean(Data::Dbxcommon::TDBXBooleanValue* DbxValue, System::LongBool &Value, System::LongBool &IsNull);
	virtual void __fastcall GetByteLength(Data::Dbxcommon::TDBXByteArrayValue* DbxValue, __int64 &ByteLength, System::LongBool &IsNull);
	virtual void __fastcall GetBytes(Data::Dbxcommon::TDBXByteArrayValue* DbxValue, __int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length, __int64 &ReturnLength, System::LongBool &IsNull);
	virtual void __fastcall GetDate(Data::Dbxcommon::TDBXDateValue* DbxValue, Data::Dbxcommon::TDBXDate &Value, System::LongBool &IsNull);
	virtual void __fastcall GetDouble(Data::Dbxcommon::TDBXDoubleValue* DbxValue, double &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt8(Data::Dbxcommon::TDBXInt8Value* DbxValue, System::Int8 &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt16(Data::Dbxcommon::TDBXInt16Value* DbxValue, short &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt32(Data::Dbxcommon::TDBXInt32Value* DbxValue, int &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt64(Data::Dbxcommon::TDBXInt64Value* DbxValue, __int64 &Value, System::LongBool &IsNull);
	virtual void __fastcall GetSingle(Data::Dbxcommon::TDBXSingleValue* DbxValue, float &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTime(Data::Dbxcommon::TDBXTimeValue* DbxValue, Data::Dbxcommon::TDBXTime &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStamp(Data::Dbxcommon::TDBXTimeStampValue* DbxValue, Data::Sqltimst::TSQLTimeStamp &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStampOffset(Data::Dbxcommon::TDBXTimeStampOffsetValue* DbxValue, Data::Sqltimst::TSQLTimeStampOffset &Value, System::LongBool &IsNull);
	virtual void __fastcall GetUInt8(Data::Dbxcommon::TDBXUInt8Value* DbxValue, System::Byte &Value, System::LongBool &IsNull);
	virtual void __fastcall GetUInt16(Data::Dbxcommon::TDBXUInt16Value* DbxValue, System::Word &Value, System::LongBool &IsNull);
	virtual void __fastcall GetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::WideChar * &WideStringBuilder, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall SetAnsiString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetBoolean(Data::Dbxcommon::TDBXBooleanValue* DbxValue, bool Value);
	virtual void __fastcall SetDouble(Data::Dbxcommon::TDBXDoubleValue* DbxValue, double Value);
	virtual void __fastcall SetDynamicBytes(Data::Dbxcommon::TDBXValue* DbxValue, __int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length);
	virtual void __fastcall SetInt8(Data::Dbxcommon::TDBXInt8Value* DbxValue, System::Int8 Value);
	virtual void __fastcall SetInt16(Data::Dbxcommon::TDBXInt16Value* DbxValue, short Value);
	virtual void __fastcall SetInt32(Data::Dbxcommon::TDBXInt32Value* DbxValue, int Value);
	virtual void __fastcall SetInt64(Data::Dbxcommon::TDBXInt64Value* DbxValue, __int64 Value);
	virtual void __fastcall SetNull(Data::Dbxcommon::TDBXValue* DbxValue);
	virtual void __fastcall SetSingle(Data::Dbxcommon::TDBXSingleValue* DbxValue, float Value);
	virtual void __fastcall SetString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetUInt8(Data::Dbxcommon::TDBXUInt8Value* DbxValue, System::Byte Value);
	virtual void __fastcall SetUInt16(Data::Dbxcommon::TDBXUInt16Value* DbxValue, System::Word Value);
	virtual void __fastcall SetValueType(Data::Dbxcommon::TDBXValueType* ValueType);
	virtual void __fastcall SetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, const System::UnicodeString Value);
	
public:
	__fastcall TDBXSqliteRow(Data::Dbxcommon::TDBXContext* DBXContext, TDBXSqliteConnection* Connection, void * StatementHandle);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSqliteRow() { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::UnicodeString &Value, System::LongBool &IsNull){ Data::Dbxcommon::TDBXRow::GetWideString(DbxValue, Value, IsNull); }
	
};


class PASCALIMPLEMENTATION TDBXSqliteByteReader : public Data::Dbxcommon::TDBXByteReader
{
	typedef Data::Dbxcommon::TDBXByteReader inherited;
	
private:
	TDBXSqliteConnection* FSqliteConnection;
	void *FStatementHandle;
	
protected:
	__fastcall TDBXSqliteByteReader(Data::Dbxcommon::TDBXContext* DBXContext, TDBXSqliteConnection* Connection, void * StatementHandle);
	
public:
	virtual void __fastcall GetAnsiString(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetBcd(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetByteLength(int Ordinal, __int64 &Length, System::LongBool &IsNull);
	virtual __int64 __fastcall GetBytes(int Ordinal, __int64 Offset, const System::TArray__1<System::Byte> Value, __int64 ValueOffset, __int64 Length, System::LongBool &IsNull);
	virtual void __fastcall GetDate(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetDouble(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt8(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt16(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt32(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt64(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetSingle(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetTime(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStamp(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStampOffset(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetUInt8(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetUInt16(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetWideString(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSqliteByteReader() { }
	
};


class PASCALIMPLEMENTATION TDBXSqliteReader : public Data::Dbxcommon::TDBXReader
{
	typedef Data::Dbxcommon::TDBXReader inherited;
	
private:
	TDBXSqliteConnection* FSqliteConnection;
	void *FStatementHandle;
	
protected:
	__fastcall TDBXSqliteReader(Data::Dbxcommon::TDBXContext* DBXContext, TDBXSqliteConnection* Connection, void * StatementHandle, TDBXSqliteByteReader* ByteReader, int NumCols);
	virtual void __fastcall DerivedClose();
	virtual bool __fastcall DerivedNext();
public:
	/* TDBXReader.Destroy */ inline __fastcall virtual ~TDBXSqliteReader() { }
	
};


class PASCALIMPLEMENTATION TDBXSqliteTransaction : public Data::Dbxcommon::TDBXTransaction
{
	typedef Data::Dbxcommon::TDBXTransaction inherited;
	
private:
	int FId;
	
public:
	__fastcall TDBXSqliteTransaction(Data::Dbxcommon::TDBXConnection* Connection, int TransactionId);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSqliteTransaction() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern "C" System::WideChar * __cdecl sqlite3_column_origin_name16(void * Statement, int ColumnNum);
extern "C" System::WideChar * __cdecl sqlite3_column_database_name16(void * Statement, int ColumnNum);
extern "C" System::WideChar * __cdecl sqlite3_column_table_name16(void * Statement, int ColumnNum);
extern "C" int __cdecl sqlite3_table_column_metadata(void * db, char * zDbName, char * zTableName, char * zColumnName, /* out */ char * &pzDataType, /* out */ char * &pzCollSeq, /* out */ int &pNotNull, /* out */ int &pPrimaryKey, /* out */ int &pAutoinc);
extern DELPHI_PACKAGE void __fastcall CheckError(int ErrorCode, void * DbConnection, Data::Dbxcommon::TDBXContext* DBXContext);
}	/* namespace Dbxsqlite */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXSQLITE)
using namespace Data::Dbxsqlite;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxsqliteHPP
