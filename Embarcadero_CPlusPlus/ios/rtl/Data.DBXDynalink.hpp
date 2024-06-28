// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXDynalink.pas' rev: 34.00 (iOS)

#ifndef Data_DbxdynalinkHPP
#define Data_DbxdynalinkHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXPlatform.hpp>
#include <Data.FmtBcd.hpp>
#include <Data.SqlTimSt.hpp>
#include <Data.DBCommonTypes.hpp>
#include <Data.DBXClassRegistry.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxdynalink
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXDynalinkPropertyNames;
class DELPHICLASS TDBXMethodTable;
class DELPHICLASS TDBXDynalinkReader;
class DELPHICLASS TDBXDynalinkRow;
class DELPHICLASS TDBXDynalinkCommand;
class DELPHICLASS TDBXDynalinkByteReader;
class DELPHICLASS TDBXDynalinkTransaction;
class DELPHICLASS TDBXDynalinkConnection;
class DELPHICLASS TDBXDynalinkDriver;
class DELPHICLASS TDBXDynalinkDriverCommonLoader;
//-- type declarations -------------------------------------------------------
typedef void * TDBXHandle;

typedef void * TPointer;

typedef void * TDBXCommonHandle;

typedef void * TDBXTransactionHandle;

typedef void * TDBXDriverHandle;

typedef void * TDBXConnectionHandle;

typedef void * TDBXCommandHandle;

typedef void * TDBXMetaDataHandle;

typedef void * TDBXRowHandle;

typedef void * TDBXReaderHandle;

typedef void * TDBXWritableRowHandle;

typedef void * DBXCallbackHandle;

class PASCALIMPLEMENTATION TDBXDynalinkPropertyNames : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXDynalinkPropertyNames_BlobSize u"BlobSize"
	
	#define TDBXDynalinkPropertyNames_ErrorResourceFile u"ErrorResourceFile"
	
	#define TDBXDynalinkPropertyNames_LocaleCode u"LocaleCode"
	
	#define TDBXDynalinkPropertyNames_Compressed u"Compressed"
	
	#define TDBXDynalinkPropertyNames_Encrypted u"Encrypted"
	
public:
	/* TObject.Create */ inline __fastcall TDBXDynalinkPropertyNames() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDynalinkPropertyNames() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TDBXDynalinkDriverLoaderClass);

typedef int TInt32;

typedef Data::Dbcommontypes::CBRType __cdecl (*DBXTraceCallback)(void * Handle, long TraceCategory, System::WideChar * TraceMessage);

typedef long __cdecl (*TDBXCommon_GetErrorMessageLength)(void * Handle, long LastErrorCode, /* out */ long &ErrorLen);

typedef long __cdecl (*TDBXCommon_GetErrorMessage)(void * Handle, long LastErrorCode, System::WideChar * ErrorMessage);

typedef long __cdecl (*TDBXCommon_Close)(void * Handle);

typedef long __cdecl (*TDBXRow_GetString)(void * Handle, long Ordinal, char * Value, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetWideString)(void * Handle, long Ordinal, System::WideChar * Value, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetBoolean)(void * Handle, long Ordinal, /* out */ System::LongBool &Value, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetUInt8)(void * Handle, long Ordinal, /* out */ System::Byte &Value, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetInt8)(void * Handle, long Ordinal, /* out */ System::Int8 &Value, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetInt16)(void * Handle, long Ordinal, /* out */ short &Value, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetInt32)(void * Handle, long Ordinal, /* out */ long &Value, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetInt64)(void * Handle, long Ordinal, /* out */ __int64 &Value, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetSingle)(void * Handle, long Ordinal, /* out */ float &Value, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetDouble)(void * Handle, long Ordinal, /* out */ double &Value, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetBcd)(void * Handle, long Ordinal, /* out */ Data::Fmtbcd::TBcd &Value, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetTimeStamp)(void * Handle, long Ordinal, /* out */ Data::Sqltimst::TSQLTimeStamp &Value, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetTimeStampOffset)(void * Handle, long Ordinal, /* out */ Data::Sqltimst::TSQLTimeStampOffset &Value, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetTime)(void * Handle, long Ordinal, /* out */ Data::Dbxcommon::TDBXTime &Value, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetDate)(void * Handle, long Ordinal, /* out */ Data::Dbxcommon::TDBXDate &Value, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetBytes)(void * Handle, long Ordinal, __int64 Offset, System::Byte *Value, const int Value_High, __int64 ValueOffset, __int64 Length, /* out */ __int64 &ReturnLength, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetFixedBytes)(void * Handle, long Ordinal, const System::Byte *Value, const int Value_High, long ValueOffset, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetByteLength)(void * Handle, long Ordinal, /* out */ __int64 &Length, /* out */ System::LongBool &IsNull);

typedef long __cdecl (*TDBXRow_GetObjectTypeName)(void * Handle, long Ordinal, System::WideChar * Value, int MaxLength);

typedef long __cdecl (*TDBXWritableRow_SetNull)(void * Handle, long Ordinal);

typedef long __cdecl (*TDBXWritableRow_SetString)(void * Handle, long Ordinal, const char * Value, __int64 Length);

typedef long __cdecl (*TDBXWritableRow_SetWideString)(void * Handle, long Ordinal, const System::WideChar * Value, __int64 Length);

typedef long __cdecl (*TDBXWritableRow_SetBoolean)(void * Handle, long Ordinal, System::LongBool Value);

typedef long __cdecl (*TDBXWritableRow_SetUInt8)(void * Handle, long Ordinal, System::Byte Value);

typedef long __cdecl (*TDBXWritableRow_SetInt8)(void * Handle, long Ordinal, System::Int8 Value);

typedef long __cdecl (*TDBXWritableRow_SetInt16)(void * Handle, long Ordinal, short Value);

typedef long __cdecl (*TDBXWritableRow_SetInt32)(void * Handle, long Ordinal, long Value);

typedef long __cdecl (*TDBXWritableRow_SetInt64)(void * Handle, long Ordinal, __int64 Value);

typedef long __cdecl (*TDBXWritableRow_SetSingle)(void * Handle, long Ordinal, float Value);

typedef long __cdecl (*TDBXWritableRow_SetDouble)(void * Handle, long Ordinal, double Value);

typedef long __cdecl (*TDBXWritableRow_SetBcd)(void * Handle, long Ordinal, Data::Fmtbcd::TBcd Value);

typedef long __cdecl (*TDBXWritableRow_SetTimeStamp)(void * Handle, long Ordinal, Data::Sqltimst::TSQLTimeStamp &Value);

typedef long __cdecl (*TDBXWritableRow_SetTimeStampOffset)(void * Handle, long Ordinal, Data::Sqltimst::TSQLTimeStampOffset &Value);

typedef long __cdecl (*TDBXWritableRow_SetTime)(void * Handle, long Ordinal, Data::Dbxcommon::TDBXTime Value);

typedef long __cdecl (*TDBXWritableRow_SetDate)(void * Handle, long Ordinal, Data::Dbxcommon::TDBXDate Value);

typedef long __cdecl (*TDBXWritableRow_SetBytes)(void * Handle, long Ordinal, __int64 BlobOffset, System::TArray__1<System::Byte> Value, long LastIndex, __int64 ValueOffset, __int64 Length);

typedef long __cdecl (*TDBXLoader_GetDriver)(long Count, Data::Dbxcommon::TWideStringArray Names, Data::Dbxcommon::TWideStringArray Values, System::WideChar * ErrorMessage, /* out */ void * &pDriver);

typedef long __cdecl (*TDBXDriver_CreateConnection)(void * Handle, /* out */ void * &pConn);

typedef long __cdecl (*TDBXDriver_GetVersion)(void * Handle, System::WideChar * Version, long MaxLength);

typedef long __cdecl (*TDBXConnection_Connect)(void * Handle, long Count, Data::Dbxcommon::TWideStringArray Names, Data::Dbxcommon::TWideStringArray Values);

typedef long __cdecl (*TDBXConnection_Disconnect)(void * Handle);

typedef long __cdecl (*TDBXConnection_SetCallbackEvent)(void * Handle, void * CallbackHandle, DBXTraceCallback CallbackEvent);

typedef long __cdecl (*TDBXConnection_CreateCommand)(void * Handle, const System::WideChar * CommandType, /* out */ void * &pCommand);

typedef long __cdecl (*TDBXConnection_GetMetaData)(void * Handle, /* out */ void * &pMetaData);

typedef long __cdecl (*TDBXConnection_BeginTransaction)(void * Handle, /* out */ void * &TransactionHandle, long IsolationLevel);

typedef long __cdecl (*TDBXConnection_Commit)(void * Handle, void * TransactionHandle);

typedef long __cdecl (*TDBXConnection_Rollback)(void * Handle, void * TransactionHandle);

typedef long __cdecl (*TDBXConnection_GetIsolation)(void * Handle, /* out */ long &IsolationLevel);

typedef long __cdecl (*TDBXConnection_GetVendorProperty)(void * Handle, System::WideChar * Name, System::WideChar * Value, long MaxLength);

typedef long __cdecl (*TDBXCommand_CreateParameterRow)(void * Handle, /* out */ void * &Parameters);

typedef long __cdecl (*TDBXCommand_Prepare)(void * Handle, const System::WideChar * SQL, long Count);

typedef long __cdecl (*TDBXCommand_Execute)(void * Handle, /* out */ void * &Reader);

typedef long __cdecl (*TDBXCommand_ExecuteImmediate)(void * Handle, const System::WideChar * SQL, /* out */ void * &Reader);

typedef long __cdecl (*TDBXCommand_GetNextReader)(void * Handle, /* out */ void * &Reader);

typedef long __cdecl (*TDBXCommand_GetRowsAffected)(void * Handle, /* out */ __int64 &Rows);

typedef long __cdecl (*TDBXCommand_SetMaxBlobSize)(void * Handle, __int64 MaxBlobSize);

typedef long __cdecl (*TDBXCommand_SetRowSetSize)(void * Handle, __int64 RowSetSize);

typedef long __cdecl (*TDBXCommand_GetParameterCount)(void * Handle, /* out */ long &ParameterCount);

typedef long __cdecl (*TDBXCommand_GetParameterType)(void * Handle, long Ordinal, /* out */ long &DBXType, /* out */ long &DBXSubType, /* out */ __int64 &Size, /* out */ __int64 &Precision, /* out */ long &Scale, /* out */ System::LongBool &Nullable);

typedef long __cdecl (*TDBXParameterRow_SetParameterType)(void * Handle, long Ordinal, const System::WideChar * Name, long ChildPosition, int ParamDirection, long DBXType, long DBXSubType, __int64 Size, __int64 Precision, long Scale);

typedef long __cdecl (*TDBXReader_GetColumnCount)(void * Handle, /* out */ long &ColumnCount);

typedef long __cdecl (*TDBXReader_GetColumnMetadata)(void * Handle, long Ordinal, System::WideChar * Name, /* out */ long &ColumnType, /* out */ long &ColumnSubType, /* out */ long &Length, /* out */ long &Precision, /* out */ long &Scale, /* out */ long &flags);

typedef long __cdecl (*TDBXReader_Next)(void * Handle);

class PASCALIMPLEMENTATION TDBXMethodTable : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	void __fastcall RaiseError(Data::Dbxcommon::TDBXContext* DBXContext, long DBXResult, void * DBXHandle, System::UnicodeString AdditionalInfo)/* overload */;
	void __fastcall RaiseError(Data::Dbxcommon::TDBXContext* DBXContext, long DBXResult, void * DBXHandle)/* overload */;
	
public:
	TDBXLoader_GetDriver FDBXLoader_GetDriver;
	TDBXCommon_GetErrorMessageLength FDBXBase_GetErrorMessageLength;
	TDBXCommon_GetErrorMessage FDBXBase_GetErrorMessage;
	TDBXCommon_Close FDBXBase_Close;
	TDBXRow_GetString FDBXRow_GetString;
	TDBXRow_GetWideString FDBXRow_GetWideString;
	TDBXRow_GetBoolean FDBXRow_GetBoolean;
	TDBXRow_GetUInt8 FDBXRow_GetUInt8;
	TDBXRow_GetInt8 FDBXRow_GetInt8;
	TDBXRow_GetInt16 FDBXRow_GetInt16;
	TDBXRow_GetInt32 FDBXRow_GetInt32;
	TDBXRow_GetInt64 FDBXRow_GetInt64;
	TDBXRow_GetSingle FDBXRow_GetSingle;
	TDBXRow_GetDouble FDBXRow_GetDouble;
	TDBXRow_GetBcd FDBXRow_GetBcd;
	TDBXRow_GetTimeStamp FDBXRow_GetTimeStamp;
	TDBXRow_GetTimeStampOffset FDBXRow_GetTimeStampOffset;
	TDBXRow_GetTime FDBXRow_GetTime;
	TDBXRow_GetDate FDBXRow_GetDate;
	TDBXRow_GetFixedBytes FDBXRow_GetFixedBytes;
	TDBXRow_GetByteLength FDBXRow_GetByteLength;
	TDBXRow_GetBytes FDBXRow_GetBytes;
	TDBXRow_GetObjectTypeName FDBXRow_GetObjectTypeName;
	TDBXWritableRow_SetNull FDBXWritableRow_SetNull;
	TDBXWritableRow_SetString FDBXWritableRow_SetString;
	TDBXWritableRow_SetWideString FDBXWritableRow_SetWideString;
	TDBXWritableRow_SetBoolean FDBXWritableRow_SetBoolean;
	TDBXWritableRow_SetUInt8 FDBXWritableRow_SetUInt8;
	TDBXWritableRow_SetInt8 FDBXWritableRow_SetInt8;
	TDBXWritableRow_SetInt16 FDBXWritableRow_SetInt16;
	TDBXWritableRow_SetInt32 FDBXWritableRow_SetInt32;
	TDBXWritableRow_SetInt64 FDBXWritableRow_SetInt64;
	TDBXWritableRow_SetSingle FDBXWritableRow_SetSingle;
	TDBXWritableRow_SetDouble FDBXWritableRow_SetDouble;
	TDBXWritableRow_SetBcd FDBXWritableRow_SetBcd;
	TDBXWritableRow_SetTimeStamp FDBXWritableRow_SetTimeStamp;
	TDBXWritableRow_SetTimeStampOffset FDBXWritableRow_SetTimeStampOffset;
	TDBXWritableRow_SetTime FDBXWritableRow_SetTime;
	TDBXWritableRow_SetDate FDBXWritableRow_SetDate;
	TDBXWritableRow_SetBytes FDBXWritableRow_SetBytes;
	TDBXDriver_CreateConnection FDBXDriver_CreateConnection;
	TDBXDriver_GetVersion FDBXDriver_GetVersion;
	TDBXConnection_Connect FDBXConnection_Connect;
	TDBXConnection_Disconnect FDBXConnection_Disconnect;
	TDBXConnection_SetCallbackEvent FDBXConnection_SetCallbackEvent;
	TDBXConnection_CreateCommand FDBXConnection_CreateCommand;
	TDBXConnection_GetMetaData FDBXConnection_GetMetaData;
	TDBXConnection_BeginTransaction FDBXConnection_BeginTransaction;
	TDBXConnection_Commit FDBXConnection_Commit;
	TDBXConnection_Rollback FDBXConnection_Rollback;
	TDBXConnection_GetIsolation FDBXConnection_GetIsolation;
	TDBXConnection_GetVendorProperty FDBXConnection_GetVendorProperty;
	TDBXCommand_CreateParameterRow FDBXCommand_CreateParameterRow;
	TDBXCommand_Prepare FDBXCommand_Prepare;
	TDBXCommand_Execute FDBXCommand_Execute;
	TDBXCommand_ExecuteImmediate FDBXCommand_ExecuteImmediate;
	TDBXCommand_GetNextReader FDBXCommand_GetNextReader;
	TDBXCommand_GetRowsAffected FDBXCommand_GetRowsAffected;
	TDBXCommand_SetMaxBlobSize FDBXCommand_SetMaxBlobSize;
	TDBXCommand_SetRowSetSize FDBXCommand_SetRowSetSize;
	TDBXCommand_GetParameterCount FDBXCommand_GetParameterCount;
	TDBXCommand_GetParameterType FDBXCommand_GetParameterType;
	TDBXParameterRow_SetParameterType FDBXParameterRow_SetParameterType;
	TDBXReader_GetColumnCount FDBXReader_GetColumnCount;
	TDBXReader_GetColumnMetadata FDBXReader_GetColumnMetadata;
	TDBXReader_Next FDBXReader_Next;
	__fastcall TDBXMethodTable();
	virtual void * __fastcall LoadMethod(System::UnicodeString MethodName) = 0 ;
	virtual void __fastcall LoadMethods() = 0 ;
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMethodTable() { }
	
};


class PASCALIMPLEMENTATION TDBXDynalinkReader : public Data::Dbxcommon::TDBXReader
{
	typedef Data::Dbxcommon::TDBXReader inherited;
	
private:
	void __fastcall CheckResult(long DBXResult);
	
protected:
	__fastcall TDBXDynalinkReader(Data::Dbxcommon::TDBXContext* DBXContext, void * ReaderHandle, TDBXMethodTable* MethodTable, Data::Dbxcommon::TDBXByteReader* ByteReader);
	void *FReaderHandle;
	TDBXMethodTable* FMethodTable;
	virtual void __fastcall DerivedClose();
	virtual bool __fastcall DerivedNext();
public:
	/* TDBXReader.Destroy */ inline __fastcall virtual ~TDBXDynalinkReader() { }
	
};


class PASCALIMPLEMENTATION TDBXDynalinkRow : public Data::Dbxcommon::TDBXRow
{
	typedef Data::Dbxcommon::TDBXRow inherited;
	
private:
	void *FRowHandle;
	TDBXMethodTable* FMethodTable;
	System::TArray__1<System::Byte> FTempBuffer;
	void __fastcall CheckResult(long DBXResult);
	void __fastcall CheckParameterResult(long DBXResult, Data::Dbxcommon::TDBXValue* DbxValue);
	void __fastcall ParameterError(long DBXResult, Data::Dbxcommon::TDBXValue* DbxValue);
	
protected:
	__fastcall TDBXDynalinkRow(Data::Dbxcommon::TDBXContext* DBXContext, TDBXMethodTable* MethodTable, void * RowHandle);
	virtual void __fastcall GetAnsiString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, char * &AnsiStringVar, System::LongBool &IsNull);
	virtual void __fastcall GetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::WideChar * &WideStringBuilder, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall GetBoolean(Data::Dbxcommon::TDBXBooleanValue* DbxValue, System::LongBool &Value, System::LongBool &IsNull);
	virtual void __fastcall GetUInt8(Data::Dbxcommon::TDBXUInt8Value* DbxValue, System::Byte &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt8(Data::Dbxcommon::TDBXInt8Value* DbxValue, System::Int8 &Value, System::LongBool &IsNull);
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
	virtual void __fastcall SetStream(Data::Dbxcommon::TDBXStreamValue* DbxValue, Data::Dbxcommon::TDBXStreamReader* StreamReader)/* overload */;
	virtual void __fastcall SetNull(Data::Dbxcommon::TDBXValue* DbxValue);
	virtual void __fastcall SetString(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, const System::UnicodeString Value);
	virtual void __fastcall SetBoolean(Data::Dbxcommon::TDBXBooleanValue* DbxValue, bool Value);
	virtual void __fastcall SetUInt8(Data::Dbxcommon::TDBXUInt8Value* DbxValue, System::Byte Value);
	virtual void __fastcall SetInt8(Data::Dbxcommon::TDBXInt8Value* DbxValue, System::Int8 Value);
	virtual void __fastcall SetInt16(Data::Dbxcommon::TDBXInt16Value* DbxValue, short Value);
	virtual void __fastcall SetInt32(Data::Dbxcommon::TDBXInt32Value* DbxValue, int Value);
	virtual void __fastcall SetInt64(Data::Dbxcommon::TDBXInt64Value* DbxValue, __int64 Value);
	virtual void __fastcall SetSingle(Data::Dbxcommon::TDBXSingleValue* DbxValue, float Value);
	virtual void __fastcall SetDouble(Data::Dbxcommon::TDBXDoubleValue* DbxValue, double Value);
	virtual void __fastcall SetBCD(Data::Dbxcommon::TDBXBcdValue* DbxValue, Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetDate(Data::Dbxcommon::TDBXDateValue* DbxValue, Data::Dbxcommon::TDBXDate Value);
	virtual void __fastcall SetTime(Data::Dbxcommon::TDBXTimeValue* DbxValue, Data::Dbxcommon::TDBXTime Value);
	virtual void __fastcall SetTimestamp(Data::Dbxcommon::TDBXTimeStampValue* DbxValue, Data::Sqltimst::TSQLTimeStamp &Value);
	virtual void __fastcall SetTimestampOffset(Data::Dbxcommon::TDBXTimeStampOffsetValue* DbxValue, Data::Sqltimst::TSQLTimeStampOffset &Value);
	virtual void __fastcall SetDynamicBytes(Data::Dbxcommon::TDBXValue* DbxValue, __int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Count);
	virtual void __fastcall SetAnsiMemo(Data::Dbxcommon::TDBXAnsiMemoValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetWideMemo(Data::Dbxcommon::TDBXWideMemoValue* DbxValue, const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetObjectTypeName(int Ordinal);
	virtual void __fastcall SetValueType(Data::Dbxcommon::TDBXValueType* ValueType);
	virtual void __fastcall GetLength(Data::Dbxcommon::TDBXValue* DbxValue, __int64 &ByteLength, System::LongBool &IsNull);
	
public:
	__fastcall virtual ~TDBXDynalinkRow();
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::UnicodeString &Value, System::LongBool &IsNull){ Data::Dbxcommon::TDBXRow::GetWideString(DbxValue, Value, IsNull); }
	inline void __fastcall  GetStream(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull){ Data::Dbxcommon::TDBXRow::GetStream(DbxValue, Stream, IsNull); }
	inline void __fastcall  GetStream(Data::Dbxcommon::TDBXAnsiStringValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull){ Data::Dbxcommon::TDBXRow::GetStream(DbxValue, Stream, IsNull); }
	
};


class PASCALIMPLEMENTATION TDBXDynalinkCommand : public Data::Dbxcommon::TDBXCommand
{
	typedef Data::Dbxcommon::TDBXCommand inherited;
	
private:
	void *FConnectionHandle;
	void *FCommandHandle;
	TDBXMethodTable* FMethodTable;
	void __fastcall CheckResult(long DBXResult);
	
protected:
	__fastcall TDBXDynalinkCommand(Data::Dbxcommon::TDBXContext* DBXContext, void * ConnectionHandle, TDBXMethodTable* MethodTable);
	virtual void __fastcall SetRowSetSize(const __int64 RowSetSize);
	virtual void __fastcall SetMaxBlobSize(const __int64 MaxBlobSize);
	virtual __int64 __fastcall GetRowsAffected();
	virtual Data::Dbxcommon::TDBXRow* __fastcall CreateParameterRow();
	virtual Data::Dbxcommon::TDBXReader* __fastcall DerivedExecuteQuery();
	virtual void __fastcall DerivedExecuteUpdate();
	virtual void __fastcall DerivedPrepare();
	virtual void __fastcall DerivedOpen();
	virtual void __fastcall DerivedClose();
	
public:
	__fastcall virtual ~TDBXDynalinkCommand();
	virtual Data::Dbxcommon::TDBXReader* __fastcall DerivedGetNextReader();
};


class PASCALIMPLEMENTATION TDBXDynalinkByteReader : public Data::Dbxcommon::TDBXByteReader
{
	typedef Data::Dbxcommon::TDBXByteReader inherited;
	
private:
	void *FReaderHandle;
	TDBXMethodTable* FMethodTable;
	
protected:
	__fastcall TDBXDynalinkByteReader(Data::Dbxcommon::TDBXContext* DBXContext, void * ReaderHandle, TDBXMethodTable* MethodTable);
	
private:
	void __fastcall CheckResult(long DBXResult);
	
public:
	virtual void __fastcall GetAnsiString(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetWideString(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetUInt8(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt8(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
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
	virtual void __fastcall GetByteLength(int Ordinal, __int64 &Length, System::LongBool &IsNull);
	virtual __int64 __fastcall GetBytes(int Ordinal, __int64 Offset, const System::TArray__1<System::Byte> Value, __int64 ValueOffset, __int64 Length, System::LongBool &IsNull);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDynalinkByteReader() { }
	
};


class PASCALIMPLEMENTATION TDBXDynalinkTransaction : public Data::Dbxcommon::TDBXTransaction
{
	typedef Data::Dbxcommon::TDBXTransaction inherited;
	
private:
	void *FTransactionHandle;
	
protected:
	__fastcall TDBXDynalinkTransaction(TDBXDynalinkConnection* Connection, int IsolationLevel, void * TransactionHandle);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDynalinkTransaction() { }
	
};


class PASCALIMPLEMENTATION TDBXDynalinkConnection : public Data::Dbxcommon::TDBXConnection
{
	typedef Data::Dbxcommon::TDBXConnection inherited;
	
private:
	DBXTraceCallback FTraceCallback;
	
protected:
	void *FConnectionHandle;
	TDBXMethodTable* FMethodTable;
	void __fastcall CheckResult(long DBXResult);
	virtual Data::Dbxcommon::TDBXTransaction* __fastcall CreateAndBeginTransaction(const int Isolation);
	virtual void __fastcall Commit(Data::Dbxcommon::TDBXTransaction* const InTransaction);
	virtual void __fastcall Rollback(Data::Dbxcommon::TDBXTransaction* const InTransaction);
	Data::Dbcommontypes::CBRType __cdecl DBXCallback(void * Handle, int TraceFlag, System::WideChar * TraceMessage);
	virtual void __fastcall SetTraceInfoEvent(const Data::Dbxcommon::TDBXTraceEvent TraceInfoEvent);
	virtual void __fastcall DerivedOpen();
	virtual void __fastcall DerivedGetCommandTypes(System::Classes::TStrings* const List);
	virtual void __fastcall DerivedGetCommands(const System::UnicodeString CommandType, System::Classes::TStrings* const List);
	virtual void __fastcall DerivedClose();
	
public:
	virtual void __fastcall Close();
	virtual System::UnicodeString __fastcall GetVendorProperty(const System::UnicodeString Name);
	__fastcall TDBXDynalinkConnection(Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder, void * ConnectionHandle, TDBXMethodTable* MethodTable);
public:
	/* TDBXConnection.Destroy */ inline __fastcall virtual ~TDBXDynalinkConnection() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TDBXDynalinkDriverCommonLoaderClass);

class PASCALIMPLEMENTATION TDBXDynalinkDriver : public Data::Dbxcommon::TDBXDriver
{
	typedef Data::Dbxcommon::TDBXDriver inherited;
	
private:
	System::UnicodeString FStringVersion;
	Data::Dbxcommon::TDBXCommand* __fastcall CreateDynalinkCommand(Data::Dbxcommon::TDBXContext* DBXContext, Data::Dbxcommon::TDBXConnection* Connection, Data::Dbxcommon::TDBXCommand* MorphicCommand);
	
protected:
	void *FDriverHandle;
	TDBXMethodTable* FMethodTable;
	TDBXDynalinkDriverCommonLoaderClass FDriverLoaderClass;
	void __fastcall CheckResult(long DBXResult);
	void __fastcall LoadDriver(Data::Dbxcommon::TDBXContext* DBXContext);
	
protected:
	virtual void __fastcall Close();
	
public:
	__fastcall TDBXDynalinkDriver(Data::Dbxcommon::TDBXDriver* Driver, void * DriverHandle, TDBXMethodTable* MethodTable)/* overload */;
	__fastcall TDBXDynalinkDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef, TDBXDynalinkDriverCommonLoaderClass DBXDriverLoader)/* overload */;
	__fastcall TDBXDynalinkDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef, TDBXDynalinkDriverCommonLoaderClass DBXDriverLoader, Data::Dbxcommon::TDBXProperties* DriverProps)/* overload */;
	__fastcall virtual ~TDBXDynalinkDriver();
	virtual System::UnicodeString __fastcall GetDriverVersion();
public:
	/* TDBXDriver.Create */ inline __fastcall virtual TDBXDynalinkDriver(const Data::Dbxcommon::TDBXDriverDef &DriverDef)/* overload */ : Data::Dbxcommon::TDBXDriver(DriverDef) { }
	/* TDBXDriver.Create */ inline __fastcall TDBXDynalinkDriver()/* overload */ : Data::Dbxcommon::TDBXDriver() { }
	
};


class PASCALIMPLEMENTATION TDBXDynalinkDriverCommonLoader : public Data::Dbxcommon::TDBXDriverLoader
{
	typedef Data::Dbxcommon::TDBXDriverLoader inherited;
	
private:
	void __fastcall LoadDriverLibraryAndMethodTable(Data::Dbxcommon::TDBXContext* DBXContext, Data::Dbxcommon::TDBXProperties* Properties);
	void __fastcall FreeOldLibrary();
	
protected:
	NativeUInt FLibraryHandle;
	NativeUInt FOldLibraryHandle;
	virtual void __fastcall LoadDriverLibrary(Data::Dbxcommon::TDBXProperties* DriverProperties, Data::Dbxcommon::TDBXContext* DBXContext);
	virtual TDBXMethodTable* __fastcall CreateMethodTable() = 0 ;
	virtual TDBXDynalinkDriver* __fastcall CreateDynalinkDriver() = 0 ;
	
protected:
	TDBXMethodTable* FMethodTable;
	void *FDriverHandle;
	
public:
	__fastcall virtual TDBXDynalinkDriverCommonLoader();
	virtual Data::Dbxcommon::TDBXDriver* __fastcall Load(const Data::Dbxcommon::TDBXDriverDef &DriverDef);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDynalinkDriverCommonLoader() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Byte MAX_VERSION_STRING_LENGTH = System::Byte(0x80);
#define SDYNALINK_LOADER_NAME u"TDBXDynalinkDriverLoader"
#define SDBX_ADAPTER_NAME u"libsqladapter.dylib"
#define SDBXLoader_GetDriver u"DBXLoader_GetDriver"
#define SDBXBase_GetErrorMessageLength u"DBXBase_GetErrorMessageLength"
#define SDBXBase_GetErrorMessage u"DBXBase_GetErrorMessage"
#define SDBXBase_Close u"DBXBase_Close"
#define SDBXRow_GetString u"DBXRow_GetString"
#define SDBXRow_GetWideString u"DBXRow_GetWideString"
#define SDBXRow_GetUInt8 u"DBXRow_GetUInt8"
#define SDBXRow_GetInt8 u"DBXRow_GetInt8"
#define SDBXRow_GetInt16 u"DBXRow_GetInt16"
#define SDBXRow_GetBoolean u"DBXRow_GetBoolean"
#define SDBXRow_GetInt32 u"DBXRow_GetInt32"
#define SDBXRow_GetInt64 u"DBXRow_GetInt64"
#define SDBXRow_GetSingle u"DBXRow_GetSingle"
#define SDBXRow_GetDouble u"DBXRow_GetDouble"
#define SDBXRow_GetBcd u"DBXRow_GetBcd"
#define SDBXRow_GetTimeStamp u"DBXRow_GetTimeStamp"
#define SDBXRow_GetTimeStampOffset u"DBXRow_GetTimeStampOffset"
#define SDBXRow_GetTime u"DBXRow_GetTime"
#define SDBXRow_GetDate u"DBXRow_GetDate"
#define SDBXRow_GetFixedBytes u"DBXRow_GetFixedBytes"
#define SDBXRow_GetBytes u"DBXRow_GetBytes"
#define SDBXRow_GetByteLength u"DBXRow_GetByteLength"
#define SDBXRow_GetObjectTypeName u"DBXRow_GetObjectTypeName"
#define SDBXWritableRow_SetNull u"DBXWritableRow_SetNull"
#define SDBXWritableRow_SetString u"DBXWritableRow_SetString"
#define SDBXWritableRow_SetWideString u"DBXWritableRow_SetWideString"
#define SDBXWritableRow_SetBoolean u"DBXWritableRow_SetBoolean"
#define SDBXWritableRow_SetUInt8 u"DBXWritableRow_SetUInt8"
#define SDBXWritableRow_SetInt8 u"DBXWritableRow_SetInt8"
#define SDBXWritableRow_SetInt16 u"DBXWritableRow_SetInt16"
#define SDBXWritableRow_SetInt32 u"DBXWritableRow_SetInt32"
#define SDBXWritableRow_SetInt64 u"DBXWritableRow_SetInt64"
#define SDBXWritableRow_SetSingle u"DBXWritableRow_SetSingle"
#define SDBXWritableRow_SetDouble u"DBXWritableRow_SetDouble"
#define SDBXWritableRow_SetBcd u"DBXWritableRow_SetBcd"
#define SDBXWritableRow_SetTimeStamp u"DBXWritableRow_SetTimeStamp"
#define SDBXWritableRow_SetTimeStampOffset u"DBXWritableRow_SetTimeStampOffset"
#define SDBXWritableRow_SetTime u"DBXWritableRow_SetTime"
#define SDBXWritableRow_SetDate u"DBXWritableRow_SetDate"
#define SDBXWritableRow_SetBytes u"DBXWritableRow_SetBytes"
#define SDBXWritableRow_SetBinary u"DBXWritableRow_SetBinary"
#define SDBXDriver_CreateConnection u"DBXDriver_CreateConnection"
#define SDBXDriver_GetVersion u"DBXDriver_GetVersion"
#define SDBXConnection_Connect u"DBXConnection_Connect"
#define SDBXConnection_Disconnect u"DBXConnection_Disconnect"
#define SDBXConnection_SetCallbackEvent u"DBXConnection_SetCallbackEvent"
#define SDBXConnection_CreateCommand u"DBXConnection_CreateCommand"
#define SDBXConnection_GetMetaData u"DBXConnection_GetMetaData"
#define SDBXConnection_BeginTransaction u"DBXConnection_BeginTransaction"
#define SDBXConnection_Commit u"DBXConnection_Commit"
#define SDBXConnection_Rollback u"DBXConnection_Rollback"
#define SDBXConnection_GetIsolation u"DBXConnection_GetIsolation"
#define SDBXConnection_GetVendorProperty u"DBXConnection_GetVendorProperty"
#define SDBXCommand_CreateParameterRow u"DBXCommand_CreateParameterRow"
#define SDBXCommand_Prepare u"DBXCommand_Prepare"
#define SDBXCommand_Execute u"DBXCommand_Execute"
#define SDBXCommand_ExecuteImmediate u"DBXCommand_ExecuteImmediate"
#define SDBXCommand_GetNextReader u"DBXCommand_GetNextReader"
#define SDBXCommand_GetRowsAffected u"DBXCommand_GetRowsAffected"
#define SDBXCommand_SetMaxBlobSize u"DBXCommand_SetMaxBlobSize"
#define SDBXCommand_SetRowSetSize u"DBXCommand_SetRowSetSize"
#define SDBXCommand_GetParameterCount u"DBXCommand_GetParameterCount"
#define SDBXCommand_GetParameterType u"DBXCommand_GetParameterType"
#define SDBXParameterRow_SetParameterType u"DBXParameterRow_SetParameterType"
#define SDBXReader_GetColumnCount u"DBXReader_GetColumnCount"
#define SDBXReader_GetColumnMetaData u"DBXReader_GetColumnMetadata"
#define SDBXReader_Next u"DBXReader_Next"
#define SDBXMetaData_GetMetaData u"DBXMetaData_GetMetaData"
}	/* namespace Dbxdynalink */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXDYNALINK)
using namespace Data::Dbxdynalink;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxdynalinkHPP
