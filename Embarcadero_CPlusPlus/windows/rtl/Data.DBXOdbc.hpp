// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DbxOdbc.pas' rev: 34.00 (Windows)

#ifndef Data_DbxodbcHPP
#define Data_DbxodbcHPP

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
#include <System.Odbc.hpp>
#include <Data.SqlTimSt.hpp>
#include <System.SysUtils.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Data.DbxOdbc"

#ifndef _WIN64
#ifndef USEPACKAGES
/* automatically link to odbc32.lib */
#pragma link "odbc32.lib"
#endif


#endif /* not _WIN64 */
namespace Data
{
namespace Dbxodbc
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXOdbcProperties;
class DELPHICLASS TDBXOdbcDriver;
class DELPHICLASS TDBXOdbcConnection;
class DELPHICLASS TDBXOdbcCommand;
class DELPHICLASS TDBXOdbcByteReader;
class DELPHICLASS TDBXOdbcReader;
class DELPHICLASS TDBXOdbcDriverLoader;
class DELPHICLASS TDBXOdbcBlockMgr;
class DELPHICLASS TDBXOdbcRow;
class DELPHICLASS TDBXOdbcTransaction;
//-- type declarations -------------------------------------------------------
typedef void * OdbcHandle;

class PASCALIMPLEMENTATION TDBXOdbcProperties : public Data::Dbxcommon::TDBXProperties
{
	typedef Data::Dbxcommon::TDBXProperties inherited;
	
public:
	__fastcall virtual TDBXOdbcProperties(Data::Dbxcommon::TDBXContext* DBXContext)/* overload */;
public:
	/* TDBXProperties.Create */ inline __fastcall virtual TDBXOdbcProperties()/* overload */ : Data::Dbxcommon::TDBXProperties() { }
	/* TDBXProperties.Destroy */ inline __fastcall virtual ~TDBXOdbcProperties() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXOdbcDriver : public Data::Dbxcommon::TDBXDriver
{
	typedef Data::Dbxcommon::TDBXDriver inherited;
	
private:
	void *FEnvironmentHandle;
	void __fastcall CheckResult(short ReturnValue);
	Data::Dbxcommon::TDBXCommand* __fastcall CreateOdbcCommand(Data::Dbxcommon::TDBXContext* DbxContext, Data::Dbxcommon::TDBXConnection* Connection, Data::Dbxcommon::TDBXCommand* MorphicCommand);
	
protected:
	virtual void __fastcall Close();
	virtual Data::Dbxcommon::TDBXConnection* __fastcall CreateConnection(Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder);
	void __fastcall LoadDriver(Data::Dbxcommon::TDBXContext* DBXContext);
	
public:
	__fastcall virtual TDBXOdbcDriver(const Data::Dbxcommon::TDBXDriverDef &DriverDef)/* overload */;
	__fastcall virtual ~TDBXOdbcDriver();
	virtual void __fastcall GetDriverPropertyNames(System::Classes::TStrings* List);
	virtual System::UnicodeString __fastcall GetDriverVersion();
public:
	/* TDBXDriver.Create */ inline __fastcall TDBXOdbcDriver()/* overload */ : Data::Dbxcommon::TDBXDriver() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXOdbcConnection : public Data::Dbxcommon::TDBXConnection
{
	typedef Data::Dbxcommon::TDBXConnection inherited;
	
private:
	void *FEnvironmentHandle;
	void *FConnectionHandle;
	int FTransactionId;
	void __fastcall CheckResult(short ReturnValue);
	
protected:
	virtual Data::Dbxcommon::TDBXTransaction* __fastcall CreateAndBeginTransaction(const int Isolation);
	virtual void __fastcall Commit(Data::Dbxcommon::TDBXTransaction* const InTransaction);
	virtual void __fastcall DerivedClose();
	virtual void __fastcall DerivedGetCommands(const System::UnicodeString CommandType, System::Classes::TStrings* const List);
	virtual void __fastcall DerivedGetCommandTypes(System::Classes::TStrings* const List);
	virtual void __fastcall DerivedOpen();
	virtual Data::Dbxcommon::TDBXDatabaseMetaData* __fastcall GetDatabaseMetaData();
	virtual System::UnicodeString __fastcall GetProductName();
	virtual System::UnicodeString __fastcall GetProductVersion();
	virtual void __fastcall Rollback(Data::Dbxcommon::TDBXTransaction* const InTransaction);
	
public:
	__fastcall TDBXOdbcConnection(Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder, void * EnvironmentHandle, void * ConnectionHandle);
	virtual TDBXOdbcCommand* __fastcall CreateOdbcCommand();
	__fastcall virtual ~TDBXOdbcConnection();
	virtual System::UnicodeString __fastcall GetVendorProperty(const System::UnicodeString Name);
	__property void * ConnectionHandle = {read=FConnectionHandle};
	__property Data::Dbxcommon::TDBXDatabaseMetaData* DatabaseMetaData = {read=GetDatabaseMetaData};
	__property void * EnvironmentHandle = {read=FEnvironmentHandle};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDBXOdbcCommand : public Data::Dbxcommon::TDBXCommand
{
	typedef Data::Dbxcommon::TDBXCommand inherited;
	
private:
	void *FEnvironmentHandle;
	void *FConnectionHandle;
	void *FCommandHandle;
	TDBXOdbcConnection* FOdbcConnection;
	__int64 FRowsAffected;
	__int64 FRowSetSize;
	TDBXOdbcRow* FParameterRow;
	void __fastcall BindParameters();
	void __fastcall CheckResult(short ReturnValue);
	void __fastcall CheckResultConnHandle(short ReturnValue);
	void __fastcall ExecuteCatalogFunction();
	__int64 __fastcall GetNumberOfColumns();
	bool __fastcall IsFunction();
	void __fastcall PutBlobs();
	void __fastcall SetParameterValues();
	void __fastcall SetRowsAffected();
	
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
	
public:
	__fastcall TDBXOdbcCommand(Data::Dbxcommon::TDBXContext* DBXContext, TDBXOdbcConnection* OdbcConnection);
	__fastcall virtual ~TDBXOdbcCommand();
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXOdbcByteReader : public Data::Dbxcommon::TDBXByteReader
{
	typedef Data::Dbxcommon::TDBXByteReader inherited;
	
private:
	void *FEnvironmentHandle;
	void *FConnectionHandle;
	void *FCommandHandle;
	__int64 __fastcall CalculateOffset(int ColNum);
	void __fastcall CheckResult(short ReturnValue);
	
protected:
	TDBXOdbcRow* FRow;
	__fastcall TDBXOdbcByteReader(Data::Dbxcommon::TDBXContext* DBXContext, void * EnvironmentHandle, void * ConnectionHandle, void * CommandHandle);
	
public:
	__fastcall virtual ~TDBXOdbcByteReader();
#ifndef _WIN64
	virtual void __fastcall GetAnsiString(int Ordinal, const System::DynamicArray<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetWideString(int Ordinal, const System::DynamicArray<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetUInt8(int Ordinal, const System::DynamicArray<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt8(int Ordinal, const System::DynamicArray<System::Byte> Value, int Offset, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall GetUInt16(int Ordinal, const System::DynamicArray<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt16(int Ordinal, const System::DynamicArray<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt32(int Ordinal, const System::DynamicArray<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt64(int Ordinal, const System::DynamicArray<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetSingle(int Ordinal, const System::DynamicArray<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetDouble(int Ordinal, const System::DynamicArray<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetBcd(int Ordinal, const System::DynamicArray<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStamp(int Ordinal, const System::DynamicArray<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStampOffset(int Ordinal, const System::DynamicArray<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetTime(int Ordinal, const System::DynamicArray<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetDate(int Ordinal, const System::DynamicArray<System::Byte> Value, int Offset, System::LongBool &IsNull);
#else /* _WIN64 */
	virtual void __fastcall GetAnsiString(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetWideString(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetUInt8(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt8(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall GetUInt16(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt16(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt32(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt64(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetSingle(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetDouble(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetBcd(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStamp(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStampOffset(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetTime(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetDate(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
#endif /* _WIN64 */
	virtual void __fastcall GetByteLength(int Ordinal, __int64 &Length, System::LongBool &IsNull);
#ifndef _WIN64
	virtual __int64 __fastcall GetBytes(int Ordinal, __int64 Offset, const System::DynamicArray<System::Byte> Value, __int64 ValueOffset, __int64 Length, System::LongBool &IsNull);
#else /* _WIN64 */
	virtual __int64 __fastcall GetBytes(int Ordinal, __int64 Offset, const System::TArray__1<System::Byte> Value, __int64 ValueOffset, __int64 Length, System::LongBool &IsNull);
#endif /* _WIN64 */
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXOdbcReader : public Data::Dbxcommon::TDBXReader
{
	typedef Data::Dbxcommon::TDBXReader inherited;
	
private:
	void *FEnvironmentHandle;
	void *FConnectionHandle;
	void *FCommandHandle;
	void __fastcall CheckResult(short ReturnValue);
	Data::Dbxcommon::TDBXWritableValue* __fastcall CreateColumn(System::Word Ordinal);
	
protected:
	__fastcall TDBXOdbcReader(Data::Dbxcommon::TDBXContext* DBXContext, void * EnvironmentHandle, void * ConnectionHandle, void * CommandHandle, TDBXOdbcByteReader* ByteReader, __int64 NumCols, __int64 RowSetSize);
	virtual void __fastcall DerivedClose();
	virtual bool __fastcall DerivedNext();
	virtual void __fastcall SetTypeInfo(Data::Dbxcommon::TDBXValueType* Column, const short SQLDataType);
public:
	/* TDBXReader.Destroy */ inline __fastcall virtual ~TDBXOdbcReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXOdbcDriverLoader : public Data::Dbxcommon::TDBXDriverLoader
{
	typedef Data::Dbxcommon::TDBXDriverLoader inherited;
	
public:
	__fastcall virtual TDBXOdbcDriverLoader();
	virtual Data::Dbxcommon::TDBXDriver* __fastcall Load(const Data::Dbxcommon::TDBXDriverDef &DriverDef);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXOdbcDriverLoader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDBXOdbcBlockMgr : public System::TObject
{
	typedef System::TObject inherited;
	
private:
#ifndef _WIN64
	System::DynamicArray<System::Byte> FBuffer;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FBuffer;
#endif /* _WIN64 */
	__int64 FCurrentRec;
	__int64 FRecCount;
	__int64 FRowLength;
	__int64 FRowsFetched;
	
public:
	__fastcall TDBXOdbcBlockMgr(__int64 RowLength, __int64 RowCount);
	__fastcall virtual ~TDBXOdbcBlockMgr();
	void __fastcall Next();
	void __fastcall Reset();
#ifndef _WIN64
	__property System::DynamicArray<System::Byte> Buffer = {read=FBuffer};
#else /* _WIN64 */
	__property System::TArray__1<System::Byte> Buffer = {read=FBuffer};
#endif /* _WIN64 */
	__property __int64 CurrentRecord = {read=FCurrentRec};
	__property __int64 RowLength = {read=FRowLength};
	__property __int64 RowsFetched = {read=FRowsFetched};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXOdbcRow : public Data::Dbxcommon::TDBXRow
{
	typedef Data::Dbxcommon::TDBXRow inherited;
	
	
private:
	typedef System::DynamicArray<short> _TDBXOdbcRow__1;
	
	typedef System::DynamicArray<__int64> _TDBXOdbcRow__2;
	
	
private:
	TDBXOdbcBlockMgr* FBlock;
	_TDBXOdbcRow__1 FColumnTypes;
	void *FCommandHandle;
	void *FConnectionHandle;
	void *FEnvironmentHandle;
	int FIndicatorSize;
	_TDBXOdbcRow__2 FOffsets;
	__int64 __fastcall CalculateOffset(int ColNum);
	
protected:
	virtual void __fastcall GetAnsiString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, char * &AnsiStringBuilder, System::LongBool &IsNull);
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
	virtual void __fastcall GetBcd(Data::Dbxcommon::TDBXBcdValue* DbxValue, Data::Fmtbcd::TBcd &Value, System::LongBool &IsNull);
	virtual void __fastcall GetDate(Data::Dbxcommon::TDBXDateValue* DbxValue, Data::Dbxcommon::TDBXDate &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTime(Data::Dbxcommon::TDBXTimeValue* DbxValue, Data::Dbxcommon::TDBXTime &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStamp(Data::Dbxcommon::TDBXTimeStampValue* DbxValue, Data::Sqltimst::TSQLTimeStamp &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStampOffset(Data::Dbxcommon::TDBXTimeStampOffsetValue* DbxValue, Data::Sqltimst::TSQLTimeStampOffset &Value, System::LongBool &IsNull);
#ifndef _WIN64
	virtual void __fastcall GetBytes(Data::Dbxcommon::TDBXByteArrayValue* DbxValue, __int64 Offset, const System::DynamicArray<System::Byte> Buffer, __int64 BufferOffset, __int64 Length, __int64 &ReturnLength, System::LongBool &IsNull);
#else /* _WIN64 */
	virtual void __fastcall GetBytes(Data::Dbxcommon::TDBXByteArrayValue* DbxValue, __int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length, __int64 &ReturnLength, System::LongBool &IsNull);
#endif /* _WIN64 */
	virtual void __fastcall GetByteLength(Data::Dbxcommon::TDBXByteArrayValue* DbxValue, __int64 &ByteLength, System::LongBool &IsNull);
	virtual void __fastcall SetNull(Data::Dbxcommon::TDBXValue* DbxValue);
	virtual void __fastcall SetString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, const System::UnicodeString Value);
	virtual void __fastcall SetAnsiString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetUInt8(Data::Dbxcommon::TDBXUInt8Value* DbxValue, System::Byte Value);
	virtual void __fastcall SetInt8(Data::Dbxcommon::TDBXInt8Value* DbxValue, System::Int8 Value);
	virtual void __fastcall SetUInt16(Data::Dbxcommon::TDBXUInt16Value* DbxValue, System::Word Value);
	virtual void __fastcall SetInt16(Data::Dbxcommon::TDBXInt16Value* DbxValue, short Value);
	virtual void __fastcall SetInt32(Data::Dbxcommon::TDBXInt32Value* DbxValue, int Value);
	virtual void __fastcall SetInt64(Data::Dbxcommon::TDBXInt64Value* DbxValue, __int64 Value);
	virtual void __fastcall SetSingle(Data::Dbxcommon::TDBXSingleValue* DbxValue, float Value);
	virtual void __fastcall SetDouble(Data::Dbxcommon::TDBXDoubleValue* DbxValue, double Value);
	virtual void __fastcall SetBCD(Data::Dbxcommon::TDBXBcdValue* DbxValue, Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetDate(Data::Dbxcommon::TDBXDateValue* DbxValue, Data::Dbxcommon::TDBXDate Value);
	virtual void __fastcall SetTime(Data::Dbxcommon::TDBXTimeValue* DbxValue, Data::Dbxcommon::TDBXTime Value);
	virtual void __fastcall SetTimestamp(Data::Dbxcommon::TDBXTimeStampValue* DbxValue, Data::Sqltimst::TSQLTimeStamp &Value);
#ifndef _WIN64
	virtual void __fastcall SetDynamicBytes(Data::Dbxcommon::TDBXValue* DbxValue, __int64 Offset, const System::DynamicArray<System::Byte> Buffer, __int64 BufferOffset, __int64 Length);
#else /* _WIN64 */
	virtual void __fastcall SetDynamicBytes(Data::Dbxcommon::TDBXValue* DbxValue, __int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length);
#endif /* _WIN64 */
	virtual void __fastcall SetValueType(Data::Dbxcommon::TDBXValueType* ValueType);
	virtual void __fastcall GetStream(Data::Dbxcommon::TDBXStreamValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall SetAnsiMemo(Data::Dbxcommon::TDBXAnsiMemoValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetWideMemo(Data::Dbxcommon::TDBXWideMemoValue* DbxValue, const System::UnicodeString Value);
	virtual void __fastcall SetBoolean(Data::Dbxcommon::TDBXBooleanValue* DbxValue, bool Value);
	virtual void __fastcall GetLength(Data::Dbxcommon::TDBXValue* DbxValue, __int64 &ByteLength, System::LongBool &IsNull);
	
public:
	__fastcall TDBXOdbcRow(Data::Dbxcommon::TDBXContext* DBXContext, void * EnvironmentHandle, void * ConnectionHandle, void * CommandHandle);
	__fastcall virtual ~TDBXOdbcRow();
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
class PASCALIMPLEMENTATION TDBXOdbcTransaction : public Data::Dbxcommon::TDBXTransaction
{
	typedef Data::Dbxcommon::TDBXTransaction inherited;
	
private:
	int FId;
	
public:
	__fastcall TDBXOdbcTransaction(Data::Dbxcommon::TDBXConnection* Connection, int IsolationLevel, int TransactionId);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXOdbcTransaction() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall OdbcRaiseError(Data::Dbxcommon::TDBXContext* DBXContext, short ReturnValue, short HandleType, void * Handle);
}	/* namespace Dbxodbc */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXODBC)
using namespace Data::Dbxodbc;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxodbcHPP
