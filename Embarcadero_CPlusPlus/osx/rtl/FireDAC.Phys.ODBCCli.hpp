// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.ODBCCli.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_OdbccliHPP
#define Firedac_Phys_OdbccliHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <FireDAC.Stan.Consts.hpp>

//-- user supplied -----------------------------------------------------------
#if defined(_Windows)
#include <sqltypes.h>
#endif

namespace Firedac
{
namespace Phys
{
namespace Odbccli
{
//-- forward type declarations -----------------------------------------------
struct TSQLDateStruct;
struct TSQLTimeStruct;
struct TODBCTimeStamp;
struct TSQLYearMonth;
struct TSQLDaySecond;
struct TSQLInterval;
struct TSQLNumericRec;
struct TSQLSSTime2Struct;
struct TSQLSSTimeStampOffset;
//-- type declarations -------------------------------------------------------
typedef System::WideChar SQLChar;

typedef System::Int8 SQLSChar;

typedef System::Byte SQLDate;

typedef System::Byte SQLDecimal;

typedef double SQLDouble;

typedef double SQLFloat;

typedef int SQLInteger;

typedef int SQLUInteger;

typedef System::Word SQLUSmallint;

typedef System::Byte SQLByte;

#ifndef __x86_64__
typedef int SQLLen;

typedef int SQLULen;

typedef System::Word SQLSetPosiRow;

typedef int SQLRowCount;

typedef int SQLRowsetSize;
#else /* __x86_64__ */
typedef __int64 SQLLen;
#endif /* __x86_64__ */

#ifndef __x86_64__
typedef int SQLTransID;
#else /* __x86_64__ */
typedef unsigned __int64 SQLULen;
#endif /* __x86_64__ */

#ifndef __x86_64__
typedef int SQLRowOffset;
#else /* __x86_64__ */
typedef unsigned __int64 SQLSetPosiRow;
#endif /* __x86_64__ */

typedef System::Byte SQLNumeric;

typedef void * SQLPointer;

typedef float SQLReal;

typedef short SQLSmallint;

typedef System::Byte SQLTime;

typedef System::Byte SQLTimeStamp;

typedef System::Byte SQLVarchar;

typedef short SQLReturn;

typedef void * SQLHandle;

typedef void * SQLHEnv;

typedef void * SQLHDbc;

typedef void * SQLHStmt;

typedef void * SQLHDesc;

typedef System::Byte UChar;

typedef System::Int8 SChar;

typedef int SDword;

typedef unsigned Dword;

typedef short SWord;

typedef unsigned UDword;

typedef System::Word UWord;

#ifndef __x86_64__
typedef int SLong;
#else /* __x86_64__ */
typedef long SLong;
#endif /* __x86_64__ */

typedef short SShort;

#ifndef __x86_64__
typedef int ULong;
#else /* __x86_64__ */
typedef long ULong;
#endif /* __x86_64__ */

typedef System::Word UShort;

typedef double SDouble;

typedef double LDouble;

typedef float SFloat;

typedef void * Ptr;

typedef void * HEnv;

typedef void * HDbc;

typedef void * HStmt;

typedef short Retcode;

typedef NativeUInt SQLHWnd;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TSQLDateStruct
{
public:
	short Year;
	System::Word Month;
	System::Word Day;
};
#pragma pack(pop)


typedef TSQLDateStruct DATE_STRUCT;

typedef TSQLDateStruct SQL_DATE_STRUCT;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TSQLTimeStruct
{
public:
	System::Word Hour;
	System::Word Minute;
	System::Word Second;
};
#pragma pack(pop)


typedef TSQLTimeStruct TIME_STRUCT;

typedef TSQLTimeStruct SQL_TIME_STRUCT;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TODBCTimeStamp
{
public:
	short Year;
	System::Word Month;
	System::Word Day;
	System::Word Hour;
	System::Word Minute;
	System::Word Second;
	int Fraction;
};
#pragma pack(pop)


typedef TODBCTimeStamp TIMESTAMP_STRUCT;

typedef TODBCTimeStamp SQL_TIMESTAMP_STRUCT;

typedef int SQLINTERVAL;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TSQLYearMonth
{
public:
	int Year;
	int Month;
};
#pragma pack(pop)


#pragma pack(push,1)
struct DECLSPEC_DRECORD TSQLDaySecond
{
public:
	int Day;
	int Hour;
	int Minute;
	int Second;
	int Fraction;
};
#pragma pack(pop)


#pragma pack(push,1)
struct DECLSPEC_DRECORD TSQLInterval
{
public:
	int Interval_type;
	int Interval_sign;
	
public:
	union
	{
		struct 
		{
			TSQLDaySecond DaySecond;
		};
		struct 
		{
			TSQLYearMonth YearMonth;
		};
		
	};
};
#pragma pack(pop)


typedef TSQLInterval SQL_INTERVAL_STRUCT;

typedef __int64 ODBCInt64;

typedef unsigned __int64 ODBCUInt64;

typedef __int64 SQLBigInt;

typedef unsigned __int64 SQLUBigInt;

typedef TSQLNumericRec *PSQLNumericRec;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TSQLNumericRec
{
public:
	System::Int8 precision;
	System::Int8 scale;
	System::Int8 sign;
	System::StaticArray<System::Byte, 16> val;
};
#pragma pack(pop)


typedef TSQLNumericRec SQL_NUMERIC_STRUCT;

typedef GUID TSQLGuid;

#ifndef __x86_64__
typedef int Bookmark;
#else /* __x86_64__ */
typedef unsigned __int64 Bookmark;
#endif /* __x86_64__ */

typedef System::WideChar SQLWChar;

typedef System::WideChar SQLTChar;

typedef System::WordBool SQLBOOL;

typedef System::Word *PUWord;

typedef int *PSQLUInteger;

typedef void * *PSQLPointer;

typedef System::Byte *PSQLByte;

typedef System::WideChar *PSQLChar;

typedef System::Byte *PSQLVarchar;

typedef System::WideChar *PSQLWChar;

typedef System::Byte *PSQLDate;

typedef System::Byte *PSQLTime;

typedef System::Byte *PSQLTimeStamp;

typedef double *PSQLDouble;

typedef double *PSQLFloat;

typedef float *PSQLReal;

typedef System::Byte *PSQLNumeric;

typedef System::Byte *PSQLDecimal;

typedef short *PSQLSmallint;

typedef System::Word *PSQLUSmallint;

typedef int *PSQLInteger;

typedef __int64 *PSQLBigInt;

typedef unsigned __int64 *PSQLUBigInt;

#ifndef __x86_64__
typedef int *PSQLLen;

typedef int *PSQLULen;

typedef System::Word *PSQLSetPosiRow;

typedef int *PSQLRowCount;

typedef int *PSQLRowsetSize;
#else /* __x86_64__ */
typedef __int64 *PSQLLen;
#endif /* __x86_64__ */

#ifndef __x86_64__
typedef int *PSQLTransID;
#else /* __x86_64__ */
typedef unsigned __int64 *PSQLULen;
#endif /* __x86_64__ */

#ifndef __x86_64__
typedef int *PSQLRowOffset;
#else /* __x86_64__ */
typedef unsigned __int64 *PSQLSetPosiRow;
#endif /* __x86_64__ */

typedef TSQLDateStruct *PSQLDateStruct;

typedef TSQLTimeStruct *PSQLTimeStruct;

typedef TODBCTimeStamp *PODBCTimeStamp;

typedef TSQLYearMonth *PSQLYearMonth;

typedef TSQLDaySecond *PSQLDaySecond;

typedef TSQLInterval *PSQLInterval;

typedef GUID *PSQLGUID;

typedef short __cdecl (*TSQLAllocConnect)(void * EnvironmentHandle, void * &ConnectionHandle);

typedef short __cdecl (*TSQLAllocEnv)(void * &EnvironmentHandle);

typedef short __cdecl (*TSQLAllocHandle)(short HandleType, void * InputHandle, void * &OutputHandle);

typedef short __cdecl (*TSQLAllocStmt)(void * ConnectionHandle, void * &StatementHandle);

#ifndef __x86_64__
typedef short __cdecl (*TSQLBindCol)(void * StatementHandle, System::Word ColumnNumber, short TargetType, void * TargetValue, int BufferLength, PSQLLen StrLen_or_Ind);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLBindCol)(void * StatementHandle, System::Word ColumnNumber, short TargetType, void * TargetValue, __int64 BufferLength, PSQLLen StrLen_or_Ind);
#endif /* __x86_64__ */

#ifndef __x86_64__
typedef short __cdecl (*TSQLBindParam)(void * StatementHandle, System::Word ParameterNumber, short ValueType, short ParameterType, int LengthPrecision, short ParameterScale, void * ParameterValue, int &StrLen_or_Ind);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLBindParam)(void * StatementHandle, System::Word ParameterNumber, short ValueType, short ParameterType, unsigned __int64 LengthPrecision, short ParameterScale, void * ParameterValue, __int64 &StrLen_or_Ind);
#endif /* __x86_64__ */

typedef short __cdecl (*TSQLCancel)(void * StatementHandle);

typedef short __cdecl (*TSQLCancelHandle)(short HandleType, void * InputHandle);

typedef short __cdecl (*TSQLCloseCursor)(void * StatementHandle);

typedef short __cdecl (*TSQLColAttribute)(void * StatementHandle, System::Word ColumnNumber, System::Word FieldIdentifier, void * CharacterAttribute, short BufferLength, PSQLSmallint StringLength, PSQLLen NumericAttributePtr);

typedef short __cdecl (*TSQLColAttributeString)(void * StatementHandle, System::Word ColumnNumber, System::Word FieldIdentifier, void * CharacterAttribute, short BufferLength, short &StringLength, PSQLLen NumericAttribute);

#ifndef __x86_64__
typedef short __cdecl (*TSQLColAttributeInt)(void * StatementHandle, System::Word ColumnNumber, System::Word FieldIdentifier, void * CharacterAttribute, short BufferLength, PSQLSmallint StringLength, int &NumericAttribute);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLColAttributeInt)(void * StatementHandle, System::Word ColumnNumber, System::Word FieldIdentifier, void * CharacterAttribute, short BufferLength, PSQLSmallint StringLength, __int64 &NumericAttribute);
#endif /* __x86_64__ */

typedef short __cdecl (*TSQLColumns)(void * StatementHandle, PSQLChar CatalogName, short NameLength1, PSQLChar SchemaName, short NameLength2, PSQLChar TableName, short NameLength3, PSQLChar ColumnName, short NameLength4);

typedef short __cdecl (*TSQLConnect)(void * ConnectionHandle, PSQLChar ServerName, short NameLength1, PSQLChar UserName, short NameLength2, PSQLChar Authentication, short NameLength3);

typedef short __cdecl (*TSQLCopyDesc)(void * SourceDescHandle, void * TargetDescHandle);

typedef short __cdecl (*TSQLDataSources)(void * EnvironmentHandle, System::Word Direction, PSQLChar ServerName, short BufferLength1, short &NameLength1, PSQLChar Description, short BufferLength2, short &NameLength2);

#ifndef __x86_64__
typedef short __cdecl (*TSQLDescribeCol)(void * StatementHandle, System::Word ColumnNumber, PSQLChar ColumnName, short BufferLength, short &NameLength, short &DataType, int &ColumnSize, short &DecimalDigits, short &Nullable);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLDescribeCol)(void * StatementHandle, System::Word ColumnNumber, PSQLChar ColumnName, short BufferLength, short &NameLength, short &DataType, unsigned __int64 &ColumnSize, short &DecimalDigits, short &Nullable);
#endif /* __x86_64__ */

typedef short __cdecl (*TSQLDisconnect)(void * ConnectionHandle);

typedef short __cdecl (*TSQLEndTran)(short HandleType, void * Handle, short CompletionType);

typedef short __cdecl (*TSQLError)(void * EnvironmentHandle, void * ConnectionHandle, void * StatementHandle, System::WideChar &SQLstate, int &NativeError, System::WideChar &MessageText, short BufferLength, short &TextLength);

typedef short __cdecl (*TSQLExecDirect)(void * StatementHandle, PSQLChar StatementText, int TextLength);

typedef short __cdecl (*TSQLExecute)(void * StatementHandle);

typedef short __cdecl (*TSQLFetch)(void * StatementHandle);

#ifndef __x86_64__
typedef short __cdecl (*TSQLFetchScroll)(void * StatementHandle, short FetchOrientation, int FetchOffset);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLFetchScroll)(void * StatementHandle, short FetchOrientation, __int64 FetchOffset);
#endif /* __x86_64__ */

typedef short __cdecl (*TSQLFreeConnect)(void * ConnectionHandle);

typedef short __cdecl (*TSQLFreeEnv)(void * EnvironmentHandle);

typedef short __cdecl (*TSQLFreeHandle)(short HandleType, void * Handle);

typedef short __cdecl (*TSQLFreeStmt)(void * StatementHandle, System::Word Option);

typedef short __cdecl (*TSQLGetConnectAttr)(void * ConnectionHandle, int Attribute, void * ValuePtr, int BufferLength, int &StringLength);

typedef short __cdecl (*TSQLGetConnectOption)(void * ConnectionHandle, System::Word Option, void * Value);

typedef short __cdecl (*TSQLGetCursorName)(void * StatementHandle, PSQLChar CursorName, short BufferLength, short &NameLength);

#ifndef __x86_64__
typedef short __cdecl (*TSQLGetData)(void * StatementHandle, System::Word ColumnNumber, short TargetType, void * TargetValue, int BufferLength, PSQLLen StrLen_or_Ind);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLGetData)(void * StatementHandle, System::Word ColumnNumber, short TargetType, void * TargetValue, __int64 BufferLength, PSQLLen StrLen_or_Ind);
#endif /* __x86_64__ */

typedef short __cdecl (*TSQLGetDescField)(void * DescriptorHandle, short RecNumber, short FieldIdentifier, void * Value, int BufferLength, int &StringLength);

#ifndef __x86_64__
typedef short __cdecl (*TSQLGetDescRec)(void * DescriptorHandle, short RecNumber, System::WideChar &Name, short BufferLength, short &StringLength, short &_Type, short &SubType, int &Length, short &Precision, short &Scale, short &Nullable);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLGetDescRec)(void * DescriptorHandle, short RecNumber, System::WideChar &Name, short BufferLength, short &StringLength, short &_Type, short &SubType, __int64 &Length, short &Precision, short &Scale, short &Nullable);
#endif /* __x86_64__ */

typedef short __cdecl (*TSQLGetDiagField)(short HandleType, void * Handle, short RecNumber, short DiagIdentifier, void * DiagInfo, short BufferLength, short &StringLength);

typedef short __cdecl (*TSQLGetDiagRec)(short HandleType, void * Handle, short RecNumber, PSQLChar SQLstate, int &NativeError, PSQLChar MessageText, short BufferLength, short &TextLength);

typedef short __cdecl (*TSQLGetEnvAttr)(void * EnvironmentHandle, int Attribute, void * Value, int BufferLength, int &StringLength);

typedef short __cdecl (*TSQLGetFunctions)(void * ConnectionHandle, System::Word FunctionId, System::Word &Supported);

typedef short __cdecl (*TSQLGetInfo)(void * ConnectionHandle, System::Word InfoType, void * InfoValuePtr, short BufferLength, void * StringLengthPtr);

typedef short __cdecl (*TSQLGetInfoString)(void * ConnectionHandle, System::Word InfoType, PSQLChar InfoValueString, short BufferLength, short &StringLength);

typedef short __cdecl (*TSQLGetInfoSmallint)(void * ConnectionHandle, System::Word InfoType, System::Word &InfoValue, short Ignored1, void * Ignored2);

typedef short __cdecl (*TSQLGetInfoInt)(void * ConnectionHandle, System::Word InfoType, int &InfoValue, short Ignored1, void * Ignored2);

#ifndef __x86_64__
typedef short __cdecl (*TSQLGetInfoSQLLen)(void * ConnectionHandle, System::Word InfoType, int &InfoValue, short Ignored1, void * Ignored2);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLGetInfoSQLLen)(void * ConnectionHandle, System::Word InfoType, unsigned __int64 &InfoValue, short Ignored1, void * Ignored2);
#endif /* __x86_64__ */

typedef short __cdecl (*TSQLGetStmtAttr)(void * StatementHandle, int Attribute, void * Value, int BufferLength, int &StringLength);

typedef short __cdecl (*TSQLGetStmtOption)(void * StatementHandle, System::Word Option, void * Value);

typedef short __cdecl (*TSQLGetTypeInfo)(void * StatementHandle, short DataType);

typedef short __cdecl (*TSQLNumResultCols)(void * StatementHandle, short &ColumnCount);

typedef short __cdecl (*TSQLParamData)(void * StatementHandle, void * &Value);

typedef short __cdecl (*TSQLPrepare)(void * StatementHandle, PSQLChar StatementText, int TextLength);

#ifndef __x86_64__
typedef short __cdecl (*TSQLPutData)(void * StatementHandle, void * Data, int StrLen_or_Ind);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLPutData)(void * StatementHandle, void * Data, __int64 StrLen_or_Ind);
#endif /* __x86_64__ */

#ifndef __x86_64__
typedef short __cdecl (*TSQLRowCount)(void * StatementHandle, int &RowCount);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLRowCount)(void * StatementHandle, __int64 &RowCount);
#endif /* __x86_64__ */

typedef short __cdecl (*TSQLSetConnectAttr)(void * ConnectionHandle, int Attribute, void * ValuePtr, int StringLength);

#ifndef __x86_64__
typedef short __cdecl (*TSQLSetConnectOption)(void * ConnectionHandle, System::Word Option, int Value);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLSetConnectOption)(void * ConnectionHandle, System::Word Option, unsigned __int64 Value);
#endif /* __x86_64__ */

typedef short __cdecl (*TSQLSetCursorName)(void * StatementHandle, PSQLChar CursorName, short NameLength);

typedef short __cdecl (*TSQLSetDescField)(void * DescriptorHandle, short RecNumber, short FieldIdentifier, void * Value, int BufferLength);

#ifndef __x86_64__
typedef short __cdecl (*TSQLSetDescRec)(void * DescriptorHandle, short RecNumber, short _Type, short SubType, int Length, short Precision, short Scale, void * Data, int &StringLength, int &Indicator);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLSetDescRec)(void * DescriptorHandle, short RecNumber, short _Type, short SubType, __int64 Length, short Precision, short Scale, void * Data, __int64 &StringLength, __int64 &Indicator);
#endif /* __x86_64__ */

typedef short __cdecl (*TSQLSetEnvAttr)(void * EnvironmentHandle, int Attribute, void * ValuePtr, int StringLength);

#ifndef __x86_64__
typedef short __cdecl (*TSQLSetParam)(void * StatementHandle, System::Word ParameterNumber, short ValueType, short ParameterType, int LengthPrecision, short ParameterScale, void * ParameterValue, int &StrLen_or_Ind);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLSetParam)(void * StatementHandle, System::Word ParameterNumber, short ValueType, short ParameterType, unsigned __int64 LengthPrecision, short ParameterScale, void * ParameterValue, __int64 &StrLen_or_Ind);
#endif /* __x86_64__ */

typedef short __cdecl (*TSQLSetStmtAttr)(void * StatementHandle, int Attribute, void * Value, int StringLength);

#ifndef __x86_64__
typedef short __cdecl (*TSQLSetStmtOption)(void * StatementHandle, System::Word Option, int Value);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLSetStmtOption)(void * StatementHandle, System::Word Option, unsigned __int64 Value);
#endif /* __x86_64__ */

typedef short __cdecl (*TSQLSpecialColumns)(void * StatementHandle, System::Word IdentifierType, PSQLChar CatalogName, short NameLength1, PSQLChar SchemaName, short NameLength2, PSQLChar TableName, short NameLength3, System::Word Scope, System::Word Nullable);

typedef short __cdecl (*TSQLStatistics)(void * StatementHandle, PSQLChar CatalogName, short NameLength1, PSQLChar SchemaName, short NameLength2, PSQLChar TableName, short NameLength3, System::Word Unique, System::Word Reserved);

typedef short __cdecl (*TSQLTables)(void * StatementHandle, PSQLChar CatalogName, short NameLength1, PSQLChar SchemaName, short NameLength2, PSQLChar TableName, short NameLength3, PSQLChar TableType, short NameLength4);

typedef short __cdecl (*TSQLTransact)(void * EnvironmentHandle, void * ConnectionHandle, System::Word CompletionType);

typedef System::StaticArray<System::WideChar, 7> TSQLState;

typedef PSQLChar PSQLState;

typedef short __cdecl (*TSQLDriverConnect)(void * HDbc, NativeUInt hwnd, PSQLChar szConnStrIn, short cbConnStrIn, PSQLChar szConnStrOut, short cbConnStrOutMax, short &pcbConnStrOut, System::Word fDriverCompletion);

typedef short __cdecl (*TSQLBrowseConnect)(void * HDbc, PSQLChar szConnStrIn, short cbConnStrIn, PSQLChar szConnStrOut, short cbConnStrOutMax, short &pcbConnStrOut);

typedef short __cdecl (*TSQLBulkOperations)(void * StatementHandle, short Operation);

typedef short __cdecl (*TSQLColAttributes)(void * HStmt, System::Word icol, System::Word fDescType, void * rgbDesc, short cbDescMax, short &pcbDesc, int &pfDesc);

typedef short __cdecl (*TSQLColumnPrivileges)(void * HStmt, System::WideChar &szCatalogName, short cbCatalogName, System::WideChar &szSchemaName, short cbSchemaName, System::WideChar &szTableName, short cbTableName, System::WideChar &szColumnName, short cbColumnName);

#ifndef __x86_64__
typedef short __cdecl (*TSQLDescribeParam)(void * HStmt, System::Word ipar, short &pfSQLType, int &pcbParamDef, short &pibScale, short &pfNullable);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLDescribeParam)(void * HStmt, System::Word ipar, short &pfSQLType, unsigned __int64 &pcbParamDef, short &pibScale, short &pfNullable);
#endif /* __x86_64__ */

#ifndef __x86_64__
typedef short __cdecl (*TSQLExtendedFetch)(void * HStmt, System::Word fFetchType, int irow, int &pcrow, System::Word &rgfRowStatus);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLExtendedFetch)(void * HStmt, System::Word fFetchType, __int64 irow, unsigned __int64 &pcrow, System::Word &rgfRowStatus);
#endif /* __x86_64__ */

typedef short __cdecl (*TSQLForeignKeys)(void * HStmt, PSQLChar szPkCatalogName, short cbPkCatalogName, PSQLChar szPkSchemaName, short cbPkSchemaName, PSQLChar szPkTableName, short cbPkTableName, PSQLChar szFkCatalogName, short cbFkCatalogName, PSQLChar szFkSchemaName, short cbFkSchemaName, PSQLChar szFkTableName, short cbFkTableName);

typedef short __cdecl (*TSQLMoreResults)(void * HStmt);

typedef short __cdecl (*TSQLNativeSQL)(void * HDbc, System::WideChar &szSQLStrIn, int cbSQLStrIn, System::WideChar &szSQLStr, int cbSQLStrMax, int &pcbSQLStr);

typedef short __cdecl (*TSQLNumParams)(void * HStmt, short &pcpar);

#ifndef __x86_64__
typedef short __cdecl (*TSQLParamOptions)(void * HStmt, int crow, int &pirow);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLParamOptions)(void * HStmt, unsigned __int64 crow, unsigned __int64 &pirow);
#endif /* __x86_64__ */

typedef short __cdecl (*TSQLPrimaryKeys)(void * HStmt, PSQLChar szCatalogName, short cbCatalogName, PSQLChar szSchemaName, short cbSchemaName, PSQLChar szTableName, short cbTableName);

typedef short __cdecl (*TSQLProcedureColumns)(void * HStmt, PSQLChar szCatalogName, short cbCatalogName, PSQLChar szSchemaName, short cbSchemaName, PSQLChar szProcName, short cbProcName, PSQLChar szColumnName, short cbColumnName);

typedef short __cdecl (*TSQLProcedures)(void * HStmt, PSQLChar szCatalogName, short cbCatalogName, PSQLChar szSchemaName, short cbSchemaName, PSQLChar szProcName, short cbProcName);

#ifndef __x86_64__
typedef short __cdecl (*TSQLSetPos)(void * HStmt, System::Word irow, System::Word fOption, System::Word fLock);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLSetPos)(void * HStmt, unsigned __int64 irow, System::Word fOption, System::Word fLock);
#endif /* __x86_64__ */

typedef short __cdecl (*TSQLTablePrivileges)(void * HStmt, System::WideChar &szCatalogName, short cbCatalogName, System::WideChar &szSchemaName, short cbSchemaName, System::WideChar &szTableName, short cbTableName);

typedef short __cdecl (*TSQLDrivers)(void * HEnv, System::Word fDirection, PSQLChar szDriverDesc, short cbDriverDescMax, short &pcbDriverDesc, PSQLChar szDriverAttributes, short cbDrvrAttrMax, short &pcbDrvrAttr);

#ifndef __x86_64__
typedef short __cdecl (*TSQLBindParameter)(void * HStmt, System::Word ipar, short fParamType, short fCType, short fSQLType, int cbColDef, short ibScale, void * rgbValue, int cbValueMax, PSQLLen pcbValue);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLBindParameter)(void * HStmt, System::Word ipar, short fParamType, short fCType, short fSQLType, unsigned __int64 cbColDef, short ibScale, void * rgbValue, __int64 cbValueMax, PSQLLen pcbValue);
#endif /* __x86_64__ */

typedef short __cdecl (*TSQLAllocHandleStd)(short fHandleType, void * hInput, void * &phOutput);

#ifndef __x86_64__
typedef short __cdecl (*TSQLSetScrollOptions)(void * HStmt, System::Word fConcurrency, int crowKeyset, System::Word crowRowset);
#else /* __x86_64__ */
typedef short __cdecl (*TSQLSetScrollOptions)(void * HStmt, System::Word fConcurrency, __int64 crowKeyset, System::Word crowRowset);
#endif /* __x86_64__ */

typedef System::WordBool __cdecl (*TSQLConfigDataSource)(NativeUInt hwndParent, System::Word fRequest, PSQLChar lpszDriver, PSQLChar lpszAttributes);

typedef short __cdecl (*TSQLInstallerError)(System::Word iError, unsigned &pfErrorCode, PSQLChar lpszErrorMsg, System::Word cbErrorMsgMax, System::Word &pcbErrorMsg);

typedef TSQLSSTime2Struct *PSQLSSTime2Struct;

struct DECLSPEC_DRECORD TSQLSSTime2Struct
{
public:
	System::Word Hour;
	System::Word Minute;
	System::Word Second;
	int Fraction;
};


typedef TSQLSSTime2Struct SQL_SS_TIME2_STRUCT;

typedef TSQLSSTimeStampOffset *PSQLSSTimeStampOffset;

struct DECLSPEC_DRECORD TSQLSSTimeStampOffset
{
public:
	short Year;
	System::Word Month;
	System::Word Day;
	System::Word Hour;
	System::Word Minute;
	System::Word Second;
	int Fraction;
	short Timezone_Hour;
	short Timezone_Minute;
};


typedef TSQLSSTimeStampOffset SQL_SS_TIMESTAMPOFFSET_STRUCT;

#ifndef __x86_64__
typedef void __stdcall (*TASA_SQL_CALLBACK)(void * SQLCA, System::Byte msg_type, unsigned code, System::Word len, System::WideChar * msg);
#else /* __x86_64__ */
typedef void __stdcall (*TASA_SQL_CALLBACK)(void * SQLCA, System::Byte msg_type, unsigned long code, System::Word len, System::WideChar * msg);
#endif /* __x86_64__ */

typedef void * HINFX_RC;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString C_ODBC;
extern DELPHI_PACKAGE System::UnicodeString C_ODBCCP;
static const System::Int8 SQL_IS_UNKNOWN = System::Int8(0x0);
static const System::Int8 SQL_IS_YEAR = System::Int8(0x1);
static const System::Int8 SQL_IS_MONTH = System::Int8(0x2);
static const System::Int8 SQL_IS_DAY = System::Int8(0x3);
static const System::Int8 SQL_IS_HOUR = System::Int8(0x4);
static const System::Int8 SQL_IS_MINUTE = System::Int8(0x5);
static const System::Int8 SQL_IS_SECOND = System::Int8(0x6);
static const System::Int8 SQL_IS_YEAR_TO_MONTH = System::Int8(0x7);
static const System::Int8 SQL_IS_DAY_TO_HOUR = System::Int8(0x8);
static const System::Int8 SQL_IS_DAY_TO_MINUTE = System::Int8(0x9);
static const System::Int8 SQL_IS_DAY_TO_SECOND = System::Int8(0xa);
static const System::Int8 SQL_IS_HOUR_TO_MINUTE = System::Int8(0xb);
static const System::Int8 SQL_IS_HOUR_TO_SECOND = System::Int8(0xc);
static const System::Int8 SQL_IS_MINUTE_TO_SECOND = System::Int8(0xd);
#ifndef __x86_64__
static const int SQL_NULL_DATA = int(-1);
static const int SQL_DATA_AT_EXEC = int(-2);
#else /* __x86_64__ */
static const __int64 SQL_NULL_DATA = -1LL;
static const __int64 SQL_DATA_AT_EXEC = -2LL;
#endif /* __x86_64__ */
static const System::Int8 SQL_SUCCESS = System::Int8(0x0);
static const System::Int8 SQL_SUCCESS_WITH_INFO = System::Int8(0x1);
static const System::Int8 SQL_NO_DATA = System::Int8(0x64);
static const System::Int8 SQL_PARAM_DATA_AVAILABLE = System::Int8(0x65);
static const System::Int8 SQL_ERROR = System::Int8(-1);
static const System::Int8 SQL_INVALID_HANDLE = System::Int8(-2);
static const System::Int8 SQL_STILL_EXECUTING = System::Int8(0x2);
static const System::Int8 SQL_NEED_DATA = System::Int8(0x63);
static const System::Int8 SQL_NTS = System::Int8(-3);
static const System::Int8 SQL_NTSL = System::Int8(-3);
static const System::Word SQL_MAX_MESSAGE_LENGTH = System::Word(0x1000);
static const System::Int8 SQL_DATE_LEN = System::Int8(0xa);
static const System::Int8 SQL_TIME_LEN = System::Int8(0x8);
static const System::Int8 SQL_TIMESTAMP_LEN = System::Int8(0x13);
static const System::Int8 SQL_HANDLE_ENV = System::Int8(0x1);
static const System::Int8 SQL_HANDLE_DBC = System::Int8(0x2);
static const System::Int8 SQL_HANDLE_STMT = System::Int8(0x3);
static const System::Int8 SQL_HANDLE_DESC = System::Int8(0x4);
static const System::Word SQL_ATTR_OUTPUT_NTS = System::Word(0x2711);
static const System::Word SQL_ATTR_AUTO_IPD = System::Word(0x2711);
static const System::Word SQL_ATTR_METADATA_ID = System::Word(0x271e);
static const System::Word SQL_ATTR_APP_ROW_DESC = System::Word(0x271a);
static const System::Word SQL_ATTR_APP_PARAM_DESC = System::Word(0x271b);
static const System::Word SQL_ATTR_IMP_ROW_DESC = System::Word(0x271c);
static const System::Word SQL_ATTR_IMP_PARAM_DESC = System::Word(0x271d);
static const System::Int8 SQL_ATTR_CURSOR_SCROLLABLE = System::Int8(-1);
static const System::Int8 SQL_ATTR_CURSOR_SENSITIVITY = System::Int8(-2);
static const System::Int8 SQL_NONSCROLLABLE = System::Int8(0x0);
static const System::Int8 SQL_SCROLLABLE = System::Int8(0x1);
static const System::Word SQL_DESC_COUNT = System::Word(0x3e9);
static const System::Word SQL_DESC_TYPE = System::Word(0x3ea);
static const System::Word SQL_DESC_LENGTH = System::Word(0x3eb);
static const System::Word SQL_DESC_OCTET_LENGTH_PTR = System::Word(0x3ec);
static const System::Word SQL_DESC_PRECISION = System::Word(0x3ed);
static const System::Word SQL_DESC_SCALE = System::Word(0x3ee);
static const System::Word SQL_DESC_DATETIME_INTERVAL_CODE = System::Word(0x3ef);
static const System::Word SQL_DESC_NULLABLE = System::Word(0x3f0);
static const System::Word SQL_DESC_INDICATOR_PTR = System::Word(0x3f1);
static const System::Word SQL_DESC_DATA_PTR = System::Word(0x3f2);
static const System::Word SQL_DESC_NAME = System::Word(0x3f3);
static const System::Word SQL_DESC_UNNAMED = System::Word(0x3f4);
static const System::Word SQL_DESC_OCTET_LENGTH = System::Word(0x3f5);
static const System::Word SQL_DESC_ALLOC_TYPE = System::Word(0x44b);
static const System::Int8 SQL_DIAG_RETURNCODE = System::Int8(0x1);
static const System::Int8 SQL_DIAG_NUMBER = System::Int8(0x2);
static const System::Int8 SQL_DIAG_ROW_COUNT = System::Int8(0x3);
static const System::Int8 SQL_DIAG_SQLSTATE = System::Int8(0x4);
static const System::Int8 SQL_DIAG_NATIVE = System::Int8(0x5);
static const System::Int8 SQL_DIAG_MESSAGE_TEXT = System::Int8(0x6);
static const System::Int8 SQL_DIAG_DYNAMIC_FUNCTION = System::Int8(0x7);
static const System::Int8 SQL_DIAG_CLASS_ORIGIN = System::Int8(0x8);
static const System::Int8 SQL_DIAG_SUBCLASS_ORIGIN = System::Int8(0x9);
static const System::Int8 SQL_DIAG_CONNECTION_NAME = System::Int8(0xa);
static const System::Int8 SQL_DIAG_SERVER_NAME = System::Int8(0xb);
static const System::Int8 SQL_DIAG_DYNAMIC_FUNCTION_CODE = System::Int8(0xc);
static const System::Int8 SQL_DIAG_ALTER_DOMAIN = System::Int8(0x3);
static const System::Int8 SQL_DIAG_ALTER_TABLE = System::Int8(0x4);
static const System::Int8 SQL_DIAG_CALL = System::Int8(0x7);
static const System::Int8 SQL_DIAG_CREATE_ASSERTION = System::Int8(0x6);
static const System::Int8 SQL_DIAG_CREATE_CHARACTER_SET = System::Int8(0x8);
static const System::Int8 SQL_DIAG_CREATE_COLLATION = System::Int8(0xa);
static const System::Int8 SQL_DIAG_CREATE_DOMAIN = System::Int8(0x17);
static const System::Int8 SQL_DIAG_CREATE_INDEX = System::Int8(-1);
static const System::Int8 SQL_DIAG_CREATE_SCHEMA = System::Int8(0x40);
static const System::Int8 SQL_DIAG_CREATE_TABLE = System::Int8(0x4d);
static const System::Int8 SQL_DIAG_CREATE_TRANSLATION = System::Int8(0x4f);
static const System::Int8 SQL_DIAG_CREATE_VIEW = System::Int8(0x54);
static const System::Int8 SQL_DIAG_DELETE_WHERE = System::Int8(0x13);
static const System::Int8 SQL_DIAG_DROP_ASSERTION = System::Int8(0x18);
static const System::Int8 SQL_DIAG_DROP_CHARACTER_SET = System::Int8(0x19);
static const System::Int8 SQL_DIAG_DROP_COLLATION = System::Int8(0x1a);
static const System::Int8 SQL_DIAG_DROP_DOMAIN = System::Int8(0x1b);
static const System::Int8 SQL_DIAG_DROP_INDEX = System::Int8(-2);
static const System::Int8 SQL_DIAG_DROP_SCHEMA = System::Int8(0x1f);
static const System::Int8 SQL_DIAG_DROP_TABLE = System::Int8(0x20);
static const System::Int8 SQL_DIAG_DROP_TRANSLATION = System::Int8(0x21);
static const System::Int8 SQL_DIAG_DROP_VIEW = System::Int8(0x24);
static const System::Int8 SQL_DIAG_DYNAMIC_DELETE_CURSOR = System::Int8(0x26);
static const System::Int8 SQL_DIAG_DYNAMIC_UPDATE_CURSOR = System::Int8(0x51);
static const System::Int8 SQL_DIAG_GRANT = System::Int8(0x30);
static const System::Int8 SQL_DIAG_INSERT = System::Int8(0x32);
static const System::Int8 SQL_DIAG_REVOKE = System::Int8(0x3b);
static const System::Int8 SQL_DIAG_SELECT_CURSOR = System::Int8(0x55);
static const System::Int8 SQL_DIAG_UNKNOWN_STATEMENT = System::Int8(0x0);
static const System::Int8 SQL_DIAG_UPDATE_WHERE = System::Int8(0x52);
static const System::Int8 SQL_UNKNOWN_TYPE = System::Int8(0x0);
static const System::Int8 SQL_CHAR = System::Int8(0x1);
static const System::Int8 SQL_NUMERIC = System::Int8(0x2);
static const System::Int8 SQL_DECIMAL = System::Int8(0x3);
static const System::Int8 SQL_INTEGER = System::Int8(0x4);
static const System::Int8 SQL_SMALLINT = System::Int8(0x5);
static const System::Int8 SQL_FLOAT = System::Int8(0x6);
static const System::Int8 SQL_REAL = System::Int8(0x7);
static const System::Int8 SQL_DOUBLE = System::Int8(0x8);
static const System::Int8 SQL_DATETIME = System::Int8(0x9);
static const System::Int8 SQL_VARCHAR = System::Int8(0xc);
static const System::Int8 SQL_TYPE_DATE = System::Int8(0x5b);
static const System::Int8 SQL_TYPE_TIME = System::Int8(0x5c);
static const System::Int8 SQL_TYPE_TIMESTAMP = System::Int8(0x5d);
static const System::Int8 SQL_UNSPECIFIED = System::Int8(0x0);
static const System::Int8 SQL_INSENSITIVE = System::Int8(0x1);
static const System::Int8 SQL_SENSITIVE = System::Int8(0x2);
static const System::Int8 SQL_ALL_TYPES = System::Int8(0x0);
static const System::Int8 SQL_DEFAULT = System::Int8(0x63);
static const System::Int8 SQL_ARD_TYPE = System::Int8(-99);
static const System::Int8 SQL_APD_TYPE = System::Int8(-100);
static const System::Int8 SQL_CODE_DATE = System::Int8(0x1);
static const System::Int8 SQL_CODE_TIME = System::Int8(0x2);
static const System::Int8 SQL_CODE_TIMESTAMP = System::Int8(0x3);
static const System::Int8 SQL_FALSE = System::Int8(0x0);
static const System::Int8 SQL_TRUE = System::Int8(0x1);
static const System::Int8 SQL_NO_NULLS = System::Int8(0x0);
static const System::Int8 SQL_NULLABLE = System::Int8(0x1);
static const System::Int8 SQL_NULLABLE_UNKNOWN = System::Int8(0x2);
static const System::Int8 SQL_PRED_NONE = System::Int8(0x0);
static const System::Int8 SQL_PRED_CHAR = System::Int8(0x1);
static const System::Int8 SQL_PRED_BASIC = System::Int8(0x2);
static const System::Int8 SQL_NAMED = System::Int8(0x0);
static const System::Int8 SQL_UNNAMED = System::Int8(0x1);
static const System::Int8 SQL_DESC_ALLOC_AUTO = System::Int8(0x1);
static const System::Int8 SQL_DESC_ALLOC_USER = System::Int8(0x2);
static const System::Int8 SQL_CLOSE = System::Int8(0x0);
static const System::Int8 SQL_DROP = System::Int8(0x1);
static const System::Int8 SQL_UNBIND = System::Int8(0x2);
static const System::Int8 SQL_RESET_PARAMS = System::Int8(0x3);
static const System::Int8 SQL_FETCH_NEXT = System::Int8(0x1);
static const System::Int8 SQL_FETCH_FIRST = System::Int8(0x2);
static const System::Int8 SQL_FETCH_LAST = System::Int8(0x3);
static const System::Int8 SQL_FETCH_PRIOR = System::Int8(0x4);
static const System::Int8 SQL_FETCH_ABSOLUTE = System::Int8(0x5);
static const System::Int8 SQL_FETCH_RELATIVE = System::Int8(0x6);
static const System::Int8 SQL_COMMIT = System::Int8(0x0);
static const System::Int8 SQL_ROLLBACK = System::Int8(0x1);
#define SQL_NULL_HENV (void *)(0)
#define SQL_NULL_HDBC (void *)(0)
#define SQL_NULL_HSTMT (void *)(0)
#define SQL_NULL_HDESC (void *)(0)
#define SQL_NULL_HANDLE (void *)(0)
static const System::Int8 SQL_SCOPE_CURROW = System::Int8(0x0);
static const System::Int8 SQL_SCOPE_TRANSACTION = System::Int8(0x1);
static const System::Int8 SQL_SCOPE_SESSION = System::Int8(0x2);
static const System::Int8 SQL_PC_UNKNOWN = System::Int8(0x0);
static const System::Int8 SQL_PC_NON_PSEUDO = System::Int8(0x1);
static const System::Int8 SQL_PC_PSEUDO = System::Int8(0x2);
static const System::Int8 SQL_ROW_IDENTIFIER = System::Int8(0x1);
static const System::Int8 SQL_INDEX_UNIQUE = System::Int8(0x0);
static const System::Int8 SQL_INDEX_ALL = System::Int8(0x1);
static const System::Int8 SQL_INDEX_CLUSTERED = System::Int8(0x1);
static const System::Int8 SQL_INDEX_HASHED = System::Int8(0x2);
static const System::Int8 SQL_INDEX_OTHER = System::Int8(0x3);
static const System::Int8 SQL_API_SQLALLOCCONNECT = System::Int8(0x1);
static const System::Int8 SQL_API_SQLALLOCENV = System::Int8(0x2);
static const System::Word SQL_API_SQLALLOCHANDLE = System::Word(0x3e9);
static const System::Int8 SQL_API_SQLALLOCSTMT = System::Int8(0x3);
static const System::Int8 SQL_API_SQLBINDCOL = System::Int8(0x4);
static const System::Word SQL_API_SQLBINDPARAM = System::Word(0x3ea);
static const System::Int8 SQL_API_SQLCANCEL = System::Int8(0x5);
static const System::Word SQL_API_SQLCLOSECURSOR = System::Word(0x3eb);
static const System::Int8 SQL_API_SQLCOLATTRIBUTE = System::Int8(0x6);
static const System::Int8 SQL_API_SQLCOLUMNS = System::Int8(0x28);
static const System::Int8 SQL_API_SQLCONNECT = System::Int8(0x7);
static const System::Word SQL_API_SQLCOPYDESC = System::Word(0x3ec);
static const System::Int8 SQL_API_SQLDATASOURCES = System::Int8(0x39);
static const System::Int8 SQL_API_SQLDESCRIBECOL = System::Int8(0x8);
static const System::Int8 SQL_API_SQLDISCONNECT = System::Int8(0x9);
static const System::Word SQL_API_SQLENDTRAN = System::Word(0x3ed);
static const System::Int8 SQL_API_SQLERROR = System::Int8(0xa);
static const System::Int8 SQL_API_SQLEXECDIRECT = System::Int8(0xb);
static const System::Int8 SQL_API_SQLEXECUTE = System::Int8(0xc);
static const System::Int8 SQL_API_SQLFETCH = System::Int8(0xd);
static const System::Word SQL_API_SQLFETCHSCROLL = System::Word(0x3fd);
static const System::Int8 SQL_API_SQLFREECONNECT = System::Int8(0xe);
static const System::Int8 SQL_API_SQLFREEENV = System::Int8(0xf);
static const System::Word SQL_API_SQLFREEHANDLE = System::Word(0x3ee);
static const System::Int8 SQL_API_SQLFREESTMT = System::Int8(0x10);
static const System::Word SQL_API_SQLGETCONNECTATTR = System::Word(0x3ef);
static const System::Int8 SQL_API_SQLGETCONNECTOPTION = System::Int8(0x2a);
static const System::Int8 SQL_API_SQLGETCURSORNAME = System::Int8(0x11);
static const System::Int8 SQL_API_SQLGETDATA = System::Int8(0x2b);
static const System::Word SQL_API_SQLGETADSCFIELD = System::Word(0x3f0);
static const System::Word SQL_API_SQLGETADSCREC = System::Word(0x3f1);
static const System::Word SQL_API_SQLGETDIAGFIELD = System::Word(0x3f2);
static const System::Word SQL_API_SQLGETDIAGREC = System::Word(0x3f3);
static const System::Word SQL_API_SQLGETENVATTR = System::Word(0x3f4);
static const System::Int8 SQL_API_SQLGETFUNCTIONS = System::Int8(0x2c);
static const System::Int8 SQL_API_SQLGETINFO = System::Int8(0x2d);
static const System::Word SQL_API_SQLGETSTMTATTR = System::Word(0x3f6);
static const System::Int8 SQL_API_SQLGETSTMTOPTION = System::Int8(0x2e);
static const System::Int8 SQL_API_SQLGETTYPEINFO = System::Int8(0x2f);
static const System::Int8 SQL_API_SQLNUMRESULTCOLS = System::Int8(0x12);
static const System::Int8 SQL_API_SQLPARAMDATA = System::Int8(0x30);
static const System::Int8 SQL_API_SQLPREPARE = System::Int8(0x13);
static const System::Int8 SQL_API_SQLPUTDATA = System::Int8(0x31);
static const System::Int8 SQL_API_SQLROWCOUNT = System::Int8(0x14);
static const System::Word SQL_API_SQLSETCONNECTATTR = System::Word(0x3f8);
static const System::Int8 SQL_API_SQLSETCONNECTOPTION = System::Int8(0x32);
static const System::Int8 SQL_API_SQLSETCURSORNAME = System::Int8(0x15);
static const System::Word SQL_API_SQLSETADSCFIELD = System::Word(0x3f9);
static const System::Word SQL_API_SQLSETADSCREC = System::Word(0x3fa);
static const System::Word SQL_API_SQLSETENVATTR = System::Word(0x3fb);
static const System::Int8 SQL_API_SQLSETPARAM = System::Int8(0x16);
static const System::Word SQL_API_SQLSETSTMTATTR = System::Word(0x3fc);
static const System::Int8 SQL_API_SQLSETSTMTOPTION = System::Int8(0x33);
static const System::Int8 SQL_API_SQLSPECIALCOLUMNS = System::Int8(0x34);
static const System::Int8 SQL_API_SQLSTATISTICS = System::Int8(0x35);
static const System::Int8 SQL_API_SQLTABLES = System::Int8(0x36);
static const System::Int8 SQL_API_SQLTRANSACT = System::Int8(0x17);
static const System::Word SQL_API_SQLCANCELHANDLE = System::Word(0x3fe);
static const System::Int8 SQL_MAX_DRIVER_CONNECTIONS = System::Int8(0x0);
static const System::Int8 SQL_MAXIMUM_DRIVER_CONNECTIONS = System::Int8(0x0);
static const System::Int8 SQL_MAX_CONCURRENT_ACTIVITIES = System::Int8(0x1);
static const System::Int8 SQL_MAXIMUM_CONCURRENT_ACTIVITIES = System::Int8(0x1);
static const System::Int8 SQL_DATA_SOURCE_NAME = System::Int8(0x2);
static const System::Int8 SQL_FETCH_DIRECTION = System::Int8(0x8);
static const System::Int8 SQL_SERVER_NAME = System::Int8(0xd);
static const System::Int8 SQL_SEARCH_PATTERN_ESCAPE = System::Int8(0xe);
static const System::Int8 SQL_DBMS_NAME = System::Int8(0x11);
static const System::Int8 SQL_DBMS_VER = System::Int8(0x12);
static const System::Int8 SQL_ACCESSIBLE_TABLES = System::Int8(0x13);
static const System::Int8 SQL_ACCESSIBLE_PROCEDURES = System::Int8(0x14);
static const System::Int8 SQL_CURSOR_COMMIT_BEHAVIOR = System::Int8(0x17);
static const System::Int8 SQL_DATA_SOURCE_READ_ONLY = System::Int8(0x19);
static const System::Int8 SQL_DEFAULT_TXN_ISOLATION = System::Int8(0x1a);
static const System::Int8 SQL_IDENTIFIER_CASE = System::Int8(0x1c);
static const System::Int8 SQL_IDENTIFIER_QUOTE_CHAR = System::Int8(0x1d);
static const System::Int8 SQL_MAX_COLUMN_NAME_LEN = System::Int8(0x1e);
static const System::Int8 SQL_MAXIMUM_COLUMN_NAME_LENGTH = System::Int8(0x1e);
static const System::Int8 SQL_MAX_CURSOR_NAME_LEN = System::Int8(0x1f);
static const System::Int8 SQL_MAXIMUM_CURSOR_NAME_LENGTH = System::Int8(0x1f);
static const System::Int8 SQL_MAX_SCHEMA_NAME_LEN = System::Int8(0x20);
static const System::Int8 SQL_MAXIMUM_SCHEMA_NAME_LENGTH = System::Int8(0x20);
static const System::Int8 SQL_MAX_CATALOG_NAME_LEN = System::Int8(0x22);
static const System::Int8 SQL_MAXIMUM_CATALOG_NAME_LENGTH = System::Int8(0x22);
static const System::Int8 SQL_MAX_TABLE_NAME_LEN = System::Int8(0x23);
static const System::Int8 SQL_SCROLL_CONCURRENCY = System::Int8(0x2b);
static const System::Int8 SQL_TXN_CAPABLE = System::Int8(0x2e);
static const System::Int8 SQL_TRANSACTION_CAPABLE = System::Int8(0x2e);
static const System::Int8 SQL_USER_NAME = System::Int8(0x2f);
static const System::Int8 SQL_TXN_ISOLATION_OPTION = System::Int8(0x48);
static const System::Int8 SQL_TRANSACTION_ISOLATION_OPTION = System::Int8(0x48);
static const System::Int8 SQL_INTEGRITY = System::Int8(0x49);
static const System::Int8 SQL_GETDATA_EXTENSIONS = System::Int8(0x51);
static const System::Int8 SQL_NULL_COLLATION = System::Int8(0x55);
static const System::Int8 SQL_ALTER_TABLE = System::Int8(0x56);
static const System::Int8 SQL_ORDER_BY_COLUMNS_IN_SELECT = System::Int8(0x5a);
static const System::Int8 SQL_SPECIAL_CHARACTERS = System::Int8(0x5e);
static const System::Int8 SQL_MAX_COLUMNS_IN_GROUP_BY = System::Int8(0x61);
static const System::Int8 SQL_MAXIMUM_COLUMNS_IN_GROUP_BY = System::Int8(0x61);
static const System::Int8 SQL_MAX_COLUMNS_IN_INDEX = System::Int8(0x62);
static const System::Int8 SQL_MAXIMUM_COLUMNS_IN_INDEX = System::Int8(0x62);
static const System::Int8 SQL_MAX_COLUMNS_IN_ORDER_BY = System::Int8(0x63);
static const System::Int8 SQL_MAXIMUM_COLUMNS_IN_ORDER_BY = System::Int8(0x63);
static const System::Int8 SQL_MAX_COLUMNS_IN_SELECT = System::Int8(0x64);
static const System::Int8 SQL_MAXIMUM_COLUMNS_IN_SELECT = System::Int8(0x64);
static const System::Int8 SQL_MAX_COLUMNS_IN_TABLE = System::Int8(0x65);
static const System::Int8 SQL_MAX_INDEX_SIZE = System::Int8(0x66);
static const System::Int8 SQL_MAXIMUM_INDEX_SIZE = System::Int8(0x66);
static const System::Int8 SQL_MAX_ROW_SIZE = System::Int8(0x68);
static const System::Int8 SQL_MAXIMUM_ROW_SIZE = System::Int8(0x68);
static const System::Int8 SQL_MAX_STATEMENT_LEN = System::Int8(0x69);
static const System::Int8 SQL_MAXIMUM_STATEMENT_LENGTH = System::Int8(0x69);
static const System::Int8 SQL_MAX_TABLES_IN_SELECT = System::Int8(0x6a);
static const System::Int8 SQL_MAXIMUM_TABLES_IN_SELECT = System::Int8(0x6a);
static const System::Int8 SQL_MAX_USER_NAME_LEN = System::Int8(0x6b);
static const System::Int8 SQL_MAXIMUM_USER_NAME_LENGTH = System::Int8(0x6b);
static const System::Int8 SQL_OJ_CAPABILITIES = System::Int8(0x73);
static const System::Int8 SQL_OUTER_JOIN_CAPABILITIES = System::Int8(0x73);
static const System::Word SQL_XOPEN_CLI_YEAR = System::Word(0x2710);
static const System::Word SQL_CURSOR_SENSITIVITY = System::Word(0x2711);
static const System::Word SQL_DESCRIBE_PARAMETER = System::Word(0x2712);
static const System::Word SQL_CATALOG_NAME = System::Word(0x2713);
static const System::Word SQL_COLLATION_SEQ = System::Word(0x2714);
static const System::Word SQL_MAX_IDENTIFIER_LEN = System::Word(0x2715);
static const System::Word SQL_MAXIMUM_IDENTIFIER_LENGTH = System::Word(0x2715);
static const System::Int8 SQL_AT_ADD_COLUMN = System::Int8(0x1);
static const System::Int8 SQL_AT_DROP_COLUMN = System::Int8(0x2);
static const System::Int8 SQL_AT_ADD_CONSTRAINT = System::Int8(0x8);
static const System::Int8 SQL_AT_COLUMN_SINGLE = System::Int8(0x20);
static const System::Int8 SQL_AT_ADD_COLUMN_DEFAULT = System::Int8(0x40);
static const System::Byte SQL_AT_ADD_COLUMN_COLLATION = System::Byte(0x80);
static const System::Word SQL_AT_SET_COLUMN_DEFAULT = System::Word(0x100);
static const System::Word SQL_AT_DROP_COLUMN_DEFAULT = System::Word(0x200);
static const System::Word SQL_AT_DROP_COLUMN_CASCADE = System::Word(0x400);
static const System::Word SQL_AT_DROP_COLUMN_RESTRICT = System::Word(0x800);
static const System::Word SQL_AT_ADD_TABLE_CONSTRAINT = System::Word(0x1000);
static const System::Word SQL_AT_DROP_TABLE_CONSTRAINT_CASCADE = System::Word(0x2000);
static const System::Word SQL_AT_DROP_TABLE_CONSTRAINT_RESTRICT = System::Word(0x4000);
static const System::Word SQL_AT_CONSTRAINT_NAME_DEFINITION = System::Word(0x8000);
static const int SQL_AT_CONSTRAINT_INITIALLY_DEFERRED = int(0x10000);
static const int SQL_AT_CONSTRAINT_INITIALLY_IMMEDIATE = int(0x20000);
static const int SQL_AT_CONSTRAINT_DEFERRABLE = int(0x40000);
static const int SQL_AT_CONSTRAINT_NON_DEFERRABLE = int(0x80000);
static const System::Int8 SQL_AM_NONE = System::Int8(0x0);
static const System::Int8 SQL_AM_CONNECTION = System::Int8(0x1);
static const System::Int8 SQL_AM_STATEMENT = System::Int8(0x2);
static const System::Int8 SQL_CB_DELETE = System::Int8(0x0);
static const System::Int8 SQL_CB_CLOSE = System::Int8(0x1);
static const System::Int8 SQL_CB_PRESERVE = System::Int8(0x2);
static const System::Int8 SQL_FD_FETCH_NEXT = System::Int8(0x1);
static const System::Int8 SQL_FD_FETCH_FIRST = System::Int8(0x2);
static const System::Int8 SQL_FD_FETCH_LAST = System::Int8(0x4);
static const System::Int8 SQL_FD_FETCH_PRIOR = System::Int8(0x8);
static const System::Int8 SQL_FD_FETCH_ABSOLUTE = System::Int8(0x10);
static const System::Int8 SQL_FD_FETCH_RELATIVE = System::Int8(0x20);
static const System::Int8 SQL_GD_ANY_COLUMN = System::Int8(0x1);
static const System::Int8 SQL_GD_ANY_ORDER = System::Int8(0x2);
static const System::Int8 SQL_IC_UPPER = System::Int8(0x1);
static const System::Int8 SQL_IC_LOWER = System::Int8(0x2);
static const System::Int8 SQL_IC_SENSITIVE = System::Int8(0x3);
static const System::Int8 SQL_IC_MIXED = System::Int8(0x4);
static const System::Int8 SQL_OJ_LEFT = System::Int8(0x1);
static const System::Int8 SQL_OJ_RIGHT = System::Int8(0x2);
static const System::Int8 SQL_OJ_FULL = System::Int8(0x4);
static const System::Int8 SQL_OJ_NESTED = System::Int8(0x8);
static const System::Int8 SQL_OJ_NOT_ORDERED = System::Int8(0x10);
static const System::Int8 SQL_OJ_INNER = System::Int8(0x20);
static const System::Int8 SQL_OJ_ALL_COMPARISON_OPS = System::Int8(0x40);
static const System::Int8 SQL_SCCO_READ_ONLY = System::Int8(0x1);
static const System::Int8 SQL_SCCO_LOCK = System::Int8(0x2);
static const System::Int8 SQL_SCCO_OPT_ROWVER = System::Int8(0x4);
static const System::Int8 SQL_SCCO_OPT_VALUES = System::Int8(0x8);
static const System::Int8 SQL_TC_NONE = System::Int8(0x0);
static const System::Int8 SQL_TC_DML = System::Int8(0x1);
static const System::Int8 SQL_TC_ALL = System::Int8(0x2);
static const System::Int8 SQL_TC_DDL_COMMIT = System::Int8(0x3);
static const System::Int8 SQL_TC_DDL_IGNORE = System::Int8(0x4);
static const System::Int8 SQL_TXN_READ_UNCOMMITTED = System::Int8(0x1);
static const System::Int8 SQL_TRANSACTION_READ_UNCOMMITTED = System::Int8(0x1);
static const System::Int8 SQL_TXN_READ_COMMITTED = System::Int8(0x2);
static const System::Int8 SQL_TRANSACTION_READ_COMMITTED = System::Int8(0x2);
static const System::Int8 SQL_TXN_REPEATABLE_READ = System::Int8(0x4);
static const System::Int8 SQL_TRANSACTION_REPEATABLE_READ = System::Int8(0x4);
static const System::Int8 SQL_TXN_SERIALIZABLE = System::Int8(0x8);
static const System::Int8 SQL_TRANSACTION_SERIALIZABLE = System::Int8(0x8);
static const System::Int8 SQL_NC_HIGH = System::Int8(0x0);
static const System::Int8 SQL_NC_LOW = System::Int8(0x1);
static const System::Int8 SQL_INTERVAL_COLSIZE = System::Int8(0x1c);
static const System::Int8 SQL_SPEC_MAJOR = System::Int8(0x3);
static const System::Int8 SQL_SPEC_MINOR = System::Int8(0x33);
#define SQL_SPEC_STRING u"03.51"
static const System::Int8 SQL_SQLSTATE_SIZE = System::Int8(0x5);
static const System::Int8 SQL_MAX_DSN_LENGTH = System::Int8(0x20);
static const System::Word SQL_MAX_OPTION_STRING_LENGTH = System::Word(0x100);
static const System::Int8 SQL_NO_DATA_FOUND = System::Int8(0x64);
static const System::Int8 SQL_HANDLE_SENV = System::Int8(0x5);
static const System::Byte SQL_ATTR_ODBC_VERSION = System::Byte(0xc8);
static const System::Byte SQL_ATTR_CONNECTION_POOLING = System::Byte(0xc9);
static const System::Byte SQL_ATTR_CP_MATCH = System::Byte(0xca);
#ifndef __x86_64__
static const int SQL_CP_OFF = int(0);
static const int SQL_CP_ONE_PER_DRIVER = int(1);
static const int SQL_CP_ONE_PER_HENV = int(2);
static const int SQL_CP_DEFAULT = int(0);
static const int SQL_CP_STRICT_MATCH = int(0);
static const int SQL_CP_RELAXED_MATCH = int(1);
static const int SQL_CP_MATCH_DEFAULT = int(0);
static const int SQL_OV_ODBC2 = int(2);
static const int SQL_OV_ODBC3 = int(3);
static const int SQL_OV_ODBC3_80 = int(380);
#else /* __x86_64__ */
static const long SQL_CP_OFF = 0LL;
static const long SQL_CP_ONE_PER_DRIVER = 1LL;
static const long SQL_CP_ONE_PER_HENV = 2LL;
static const long SQL_CP_DEFAULT = 0LL;
static const long SQL_CP_STRICT_MATCH = 0LL;
static const long SQL_CP_RELAXED_MATCH = 1LL;
static const long SQL_CP_MATCH_DEFAULT = 0LL;
static const long SQL_OV_ODBC2 = 2LL;
static const long SQL_OV_ODBC3 = 3LL;
static const long SQL_OV_ODBC3_80 = 0x000000000000017cLL;
#endif /* __x86_64__ */
static const System::Int8 SQL_ACCESS_MODE = System::Int8(0x65);
static const System::Int8 SQL_AUTOCOMMIT = System::Int8(0x66);
static const System::Int8 SQL_LOGIN_TIMEOUT = System::Int8(0x67);
static const System::Int8 SQL_OPT_TRACE = System::Int8(0x68);
static const System::Int8 SQL_OPT_TRACEFILE = System::Int8(0x69);
static const System::Int8 SQL_TRANSLATE_DLL = System::Int8(0x6a);
static const System::Int8 SQL_TRANSLATE_OPTION = System::Int8(0x6b);
static const System::Int8 SQL_TXN_ISOLATION = System::Int8(0x6c);
static const System::Int8 SQL_CURRENT_QUALIFIER = System::Int8(0x6d);
static const System::Int8 SQL_ODBC_CURSORS = System::Int8(0x6e);
static const System::Int8 SQL_QUIET_MODE = System::Int8(0x6f);
static const System::Int8 SQL_PACKET_SIZE = System::Int8(0x70);
static const System::Int8 SQL_ATTR_ACCESS_MODE = System::Int8(0x65);
static const System::Int8 SQL_ATTR_AUTOCOMMIT = System::Int8(0x66);
static const System::Int8 SQL_ATTR_CONNECTION_TIMEOUT = System::Int8(0x71);
static const System::Int8 SQL_ATTR_CURRENT_CATALOG = System::Int8(0x6d);
static const System::Int8 SQL_ATTR_DISCONNECT_BEHAVIOR = System::Int8(0x72);
static const System::Word SQL_ATTR_ENLIST_IN_DTC = System::Word(0x4b7);
static const System::Word SQL_ATTR_ENLIST_IN_XA = System::Word(0x4b8);
static const System::Int8 SQL_ATTR_LOGIN_TIMEOUT = System::Int8(0x67);
static const System::Int8 SQL_ATTR_ODBC_CURSORS = System::Int8(0x6e);
static const System::Int8 SQL_ATTR_PACKET_SIZE = System::Int8(0x70);
static const System::Int8 SQL_ATTR_QUIET_MODE = System::Int8(0x6f);
static const System::Int8 SQL_ATTR_TRACE = System::Int8(0x68);
static const System::Int8 SQL_ATTR_TRACEFILE = System::Int8(0x69);
static const System::Int8 SQL_ATTR_TRANSLATE_LIB = System::Int8(0x6a);
static const System::Int8 SQL_ATTR_TRANSLATE_OPTION = System::Int8(0x6b);
static const System::Int8 SQL_ATTR_TXN_ISOLATION = System::Int8(0x6c);
static const System::Word SQL_ATTR_CONNECTION_DEAD = System::Word(0x4b9);
static const System::Int8 SQL_ATTR_ANSI_APP = System::Int8(0x73);
static const System::Int8 SQL_ATTR_RESET_CONNECTION = System::Int8(0x74);
static const System::Int8 SQL_ATTR_ASYNC_DBC_FUNCTIONS_ENABLE = System::Int8(0x75);
static const System::Word SQL_CONNECT_OPT_DRVR_START = System::Word(0x3e8);
static const System::Int8 SQL_CONN_OPT_MAX = System::Int8(0x70);
static const System::Int8 SQL_CONN_OPT_MIN = System::Int8(0x65);
#ifndef __x86_64__
static const int SQL_MODE_READ_WRITE = int(0);
static const int SQL_MODE_READ_ONLY = int(1);
static const int SQL_MODE_DEFAULT = int(0);
static const int SQL_AUTOCOMMIT_OFF = int(0);
static const int SQL_AUTOCOMMIT_ON = int(1);
static const int SQL_AUTOCOMMIT_DEFAULT = int(1);
static const int SQL_LOGIN_TIMEOUT_DEFAULT = int(15);
static const int SQL_OPT_TRACE_OFF = int(0);
static const int SQL_OPT_TRACE_ON = int(1);
static const int SQL_OPT_TRACE_DEFAULT = int(0);
#else /* __x86_64__ */
static const long SQL_MODE_READ_WRITE = 0LL;
static const long SQL_MODE_READ_ONLY = 1LL;
static const long SQL_MODE_DEFAULT = 0LL;
static const long SQL_AUTOCOMMIT_OFF = 0LL;
static const long SQL_AUTOCOMMIT_ON = 1LL;
static const long SQL_AUTOCOMMIT_DEFAULT = 1LL;
static const long SQL_LOGIN_TIMEOUT_DEFAULT = 0x000000000000000fLL;
static const long SQL_OPT_TRACE_OFF = 0LL;
static const long SQL_OPT_TRACE_ON = 1LL;
static const long SQL_OPT_TRACE_DEFAULT = 0LL;
#endif /* __x86_64__ */
#define SQL_OPT_TRACE_FILE_DEFAULT u"\\SQL.LOG"
#ifndef __x86_64__
static const int SQL_CUR_USE_IF_NEEDED = int(0);
static const int SQL_CUR_USE_ODBC = int(1);
static const int SQL_CUR_USE_DRIVER = int(2);
static const int SQL_CUR_DEFAULT = int(2);
static const int SQL_DB_RETURN_TO_POOL = int(0);
static const int SQL_DB_DISCONNECT = int(1);
static const int SQL_DB_DEFAULT = int(0);
#else /* __x86_64__ */
static const long SQL_CUR_USE_IF_NEEDED = 0LL;
static const long SQL_CUR_USE_ODBC = 1LL;
static const long SQL_CUR_USE_DRIVER = 2LL;
static const long SQL_CUR_DEFAULT = 2LL;
static const long SQL_DB_RETURN_TO_POOL = 0LL;
static const long SQL_DB_DISCONNECT = 1LL;
static const long SQL_DB_DEFAULT = 0LL;
#endif /* __x86_64__ */
static const System::Int8 SQL_DTC_DONE = System::Int8(0x0);
static const System::Int8 SQL_CD_TRUE = System::Int8(0x1);
static const System::Int8 SQL_CD_FALSE = System::Int8(0x0);
static const System::Int8 SQL_AA_TRUE = System::Int8(0x1);
static const System::Int8 SQL_AA_FALSE = System::Int8(0x0);
#ifndef __x86_64__
static const int SQL_RESET_CONNECTION_YES = int(1);
static const int SQL_ASYNC_DBC_ENABLE_ON = int(1);
static const int SQL_ASYNC_DBC_ENABLE_OFF = int(0);
static const int SQL_ASYNC_DBC_ENABLE_DEFAULT = int(0);
#else /* __x86_64__ */
static const long SQL_RESET_CONNECTION_YES = 1LL;
static const long SQL_ASYNC_DBC_ENABLE_ON = 1LL;
static const long SQL_ASYNC_DBC_ENABLE_OFF = 0LL;
static const long SQL_ASYNC_DBC_ENABLE_DEFAULT = 0LL;
#endif /* __x86_64__ */
static const System::Int8 SQL_QUERY_TIMEOUT = System::Int8(0x0);
static const System::Int8 SQL_MAX_ROWS = System::Int8(0x1);
static const System::Int8 SQL_NOSCAN = System::Int8(0x2);
static const System::Int8 SQL_MAX_LENGTH = System::Int8(0x3);
static const System::Int8 SQL_ASYNC_ENABLE = System::Int8(0x4);
static const System::Int8 SQL_BIND_TYPE = System::Int8(0x5);
static const System::Int8 SQL_CURSOR_TYPE = System::Int8(0x6);
static const System::Int8 SQL_CONCURRENCY = System::Int8(0x7);
static const System::Int8 SQL_KEYSET_SIZE = System::Int8(0x8);
static const System::Int8 SQL_ROWSET_SIZE = System::Int8(0x9);
static const System::Int8 SQL_SIMULATE_CURSOR = System::Int8(0xa);
static const System::Int8 SQL_RETRIEVE_DATA = System::Int8(0xb);
static const System::Int8 SQL_USE_BOOKMARKS = System::Int8(0xc);
static const System::Int8 SQL_GET_BOOKMARK = System::Int8(0xd);
static const System::Int8 SQL_ROW_NUMBER = System::Int8(0xe);
static const System::Int8 SQL_ATTR_ASYNC_ENABLE = System::Int8(0x4);
static const System::Int8 SQL_ATTR_CONCURRENCY = System::Int8(0x7);
static const System::Int8 SQL_ATTR_CURSOR_TYPE = System::Int8(0x6);
static const System::Int8 SQL_ATTR_ENABLE_AUTO_IPD = System::Int8(0xf);
static const System::Int8 SQL_ATTR_FETCH_BOOKMARK_PTR = System::Int8(0x10);
static const System::Int8 SQL_ATTR_KEYSET_SIZE = System::Int8(0x8);
static const System::Int8 SQL_ATTR_MAX_LENGTH = System::Int8(0x3);
static const System::Int8 SQL_ATTR_MAX_ROWS = System::Int8(0x1);
static const System::Int8 SQL_ATTR_NOSCAN = System::Int8(0x2);
static const System::Int8 SQL_ATTR_PARAM_BIND_OFFSET_PTR = System::Int8(0x11);
static const System::Int8 SQL_ATTR_PARAM_BIND_TYPE = System::Int8(0x12);
static const System::Int8 SQL_ATTR_PARAM_OPERATION_PTR = System::Int8(0x13);
static const System::Int8 SQL_ATTR_PARAM_STATUS_PTR = System::Int8(0x14);
static const System::Int8 SQL_ATTR_PARAMS_PROCESSED_PTR = System::Int8(0x15);
static const System::Int8 SQL_ATTR_PARAMSET_SIZE = System::Int8(0x16);
static const System::Int8 SQL_ATTR_QUERY_TIMEOUT = System::Int8(0x0);
static const System::Int8 SQL_ATTR_RETRIEVE_DATA = System::Int8(0xb);
static const System::Int8 SQL_ATTR_ROW_BIND_OFFSET_PTR = System::Int8(0x17);
static const System::Int8 SQL_ATTR_ROW_BIND_TYPE = System::Int8(0x5);
static const System::Int8 SQL_ATTR_ROW_NUMBER = System::Int8(0xe);
static const System::Int8 SQL_ATTR_ROW_OPERATION_PTR = System::Int8(0x18);
static const System::Int8 SQL_ATTR_ROW_STATUS_PTR = System::Int8(0x19);
static const System::Int8 SQL_ATTR_ROWS_FETCHED_PTR = System::Int8(0x1a);
static const System::Int8 SQL_ATTR_ROW_ARRAY_SIZE = System::Int8(0x1b);
static const System::Int8 SQL_ATTR_SIMULATE_CURSOR = System::Int8(0xa);
static const System::Int8 SQL_ATTR_USE_BOOKMARKS = System::Int8(0xc);
static const System::Int8 SQL_IS_POINTER = System::Int8(-4);
static const System::Int8 SQL_IS_UINTEGER = System::Int8(-5);
static const System::Int8 SQL_IS_INTEGER = System::Int8(-6);
static const System::Int8 SQL_IS_USMALLINT = System::Int8(-7);
static const System::Int8 SQL_IS_SMALLINT = System::Int8(-8);
#ifndef __x86_64__
static const int SQL_PARAM_BIND_BY_COLUMN = int(0);
static const int SQL_PARAM_BIND_TYPE_DEFAULT = int(0);
static const int SQL_QUERY_TIMEOUT_DEFAULT = int(0);
static const int SQL_MAX_ROWS_DEFAULT = int(0);
static const int SQL_NOSCAN_OFF = int(0);
static const int SQL_NOSCAN_ON = int(1);
static const int SQL_NOSCAN_DEFAULT = int(0);
static const int SQL_MAX_LENGTH_DEFAULT = int(0);
static const int SQL_ASYNC_ENABLE_OFF = int(0);
static const int SQL_ASYNC_ENABLE_ON = int(1);
static const int SQL_ASYNC_ENABLE_DEFAULT = int(0);
static const int SQL_BIND_BY_COLUMN = int(0);
static const int SQL_BIND_TYPE_DEFAULT = int(0);
#else /* __x86_64__ */
static const long SQL_PARAM_BIND_BY_COLUMN = 0LL;
static const long SQL_PARAM_BIND_TYPE_DEFAULT = 0LL;
static const long SQL_QUERY_TIMEOUT_DEFAULT = 0LL;
static const long SQL_MAX_ROWS_DEFAULT = 0LL;
static const long SQL_NOSCAN_OFF = 0LL;
static const long SQL_NOSCAN_ON = 1LL;
static const long SQL_NOSCAN_DEFAULT = 0LL;
static const long SQL_MAX_LENGTH_DEFAULT = 0LL;
static const long SQL_ASYNC_ENABLE_OFF = 0LL;
static const long SQL_ASYNC_ENABLE_ON = 1LL;
static const long SQL_ASYNC_ENABLE_DEFAULT = 0LL;
static const long SQL_BIND_BY_COLUMN = 0LL;
static const long SQL_BIND_TYPE_DEFAULT = 0LL;
#endif /* __x86_64__ */
static const System::Int8 SQL_CONCUR_READ_ONLY = System::Int8(0x1);
static const System::Int8 SQL_CONCUR_LOCK = System::Int8(0x2);
static const System::Int8 SQL_CONCUR_ROWVER = System::Int8(0x3);
static const System::Int8 SQL_CONCUR_VALUES = System::Int8(0x4);
static const System::Int8 SQL_CONCUR_DEFAULT = System::Int8(0x1);
#ifndef __x86_64__
static const int SQL_CURSOR_FORWARD_ONLY = int(0);
static const int SQL_CURSOR_KEYSET_DRIVEN = int(1);
static const int SQL_CURSOR_DYNAMIC = int(2);
static const int SQL_CURSOR_STATIC = int(3);
static const int SQL_CURSOR_TYPE_DEFAULT = int(0);
static const int SQL_ROWSET_SIZE_DEFAULT = int(1);
static const int SQL_KEYSET_SIZE_DEFAULT = int(0);
static const int SQL_SC_NON_UNIQUE = int(0);
static const int SQL_SC_TRY_UNIQUE = int(1);
static const int SQL_SC_UNIQUE = int(2);
static const int SQL_RD_OFF = int(0);
static const int SQL_RD_ON = int(1);
static const int SQL_RD_DEFAULT = int(1);
static const int SQL_UB_OFF = int(0);
static const int SQL_UB_ON = int(1);
static const int SQL_UB_DEFAULT = int(0);
static const int SQL_UB_FIXED = int(1);
static const int SQL_UB_VARIABLE = int(2);
#else /* __x86_64__ */
static const long SQL_CURSOR_FORWARD_ONLY = 0LL;
static const long SQL_CURSOR_KEYSET_DRIVEN = 1LL;
static const long SQL_CURSOR_DYNAMIC = 2LL;
static const long SQL_CURSOR_STATIC = 3LL;
static const long SQL_CURSOR_TYPE_DEFAULT = 0LL;
static const long SQL_ROWSET_SIZE_DEFAULT = 1LL;
static const long SQL_KEYSET_SIZE_DEFAULT = 0LL;
static const long SQL_SC_NON_UNIQUE = 0LL;
static const long SQL_SC_TRY_UNIQUE = 1LL;
static const long SQL_SC_UNIQUE = 2LL;
static const long SQL_RD_OFF = 0LL;
static const long SQL_RD_ON = 1LL;
static const long SQL_RD_DEFAULT = 1LL;
static const long SQL_UB_OFF = 0LL;
static const long SQL_UB_ON = 1LL;
static const long SQL_UB_DEFAULT = 0LL;
static const long SQL_UB_FIXED = 1LL;
static const long SQL_UB_VARIABLE = 2LL;
#endif /* __x86_64__ */
static const System::Int8 SQL_COLUMN_COUNT = System::Int8(0x0);
static const System::Int8 SQL_COLUMN_NAME = System::Int8(0x1);
static const System::Int8 SQL_COLUMN_TYPE = System::Int8(0x2);
static const System::Int8 SQL_COLUMN_LENGTH = System::Int8(0x3);
static const System::Int8 SQL_COLUMN_PRECISION = System::Int8(0x4);
static const System::Int8 SQL_COLUMN_SCALE = System::Int8(0x5);
static const System::Int8 SQL_COLUMN_DISPLAY_SIZE = System::Int8(0x6);
static const System::Int8 SQL_COLUMN_NULLABLE = System::Int8(0x7);
static const System::Int8 SQL_COLUMN_UNSIGNED = System::Int8(0x8);
static const System::Int8 SQL_COLUMN_MONEY = System::Int8(0x9);
static const System::Int8 SQL_COLUMN_UPDATABLE = System::Int8(0xa);
static const System::Int8 SQL_COLUMN_AUTO_INCREMENT = System::Int8(0xb);
static const System::Int8 SQL_COLUMN_CASE_SENSITIVE = System::Int8(0xc);
static const System::Int8 SQL_COLUMN_SEARCHABLE = System::Int8(0xd);
static const System::Int8 SQL_COLUMN_TYPE_NAME = System::Int8(0xe);
static const System::Int8 SQL_COLUMN_TABLE_NAME = System::Int8(0xf);
static const System::Int8 SQL_COLUMN_OWNER_NAME = System::Int8(0x10);
static const System::Int8 SQL_COLUMN_QUALIFIER_NAME = System::Int8(0x11);
static const System::Int8 SQL_COLUMN_LABEL = System::Int8(0x12);
static const System::Int8 SQL_DESC_ARRAY_SIZE = System::Int8(0x14);
static const System::Int8 SQL_DESC_ARRAY_STATUS_PTR = System::Int8(0x15);
static const System::Int8 SQL_DESC_AUTO_UNIQUE_VALUE = System::Int8(0xb);
static const System::Int8 SQL_DESC_BASE_COLUMN_NAME = System::Int8(0x16);
static const System::Int8 SQL_DESC_BASE_TABLE_NAME = System::Int8(0x17);
static const System::Int8 SQL_DESC_BIND_OFFSET_PTR = System::Int8(0x18);
static const System::Int8 SQL_DESC_BIND_TYPE = System::Int8(0x19);
static const System::Int8 SQL_DESC_CASE_SENSITIVE = System::Int8(0xc);
static const System::Int8 SQL_DESC_CATALOG_NAME = System::Int8(0x11);
static const System::Int8 SQL_DESC_CONCISE_TYPE = System::Int8(0x2);
static const System::Int8 SQL_DESC_DATETIME_INTERVAL_PRECISION = System::Int8(0x1a);
static const System::Int8 SQL_DESC_DISPLAY_SIZE = System::Int8(0x6);
static const System::Int8 SQL_DESC_FIXED_PREC_SCALE = System::Int8(0x9);
static const System::Int8 SQL_DESC_LABEL = System::Int8(0x12);
static const System::Int8 SQL_DESC_LITERAL_PREFIX = System::Int8(0x1b);
static const System::Int8 SQL_DESC_LITERAL_SUFFIX = System::Int8(0x1c);
static const System::Int8 SQL_DESC_LOCAL_TYPE_NAME = System::Int8(0x1d);
static const System::Int8 SQL_DESC_MAXIMUM_SCALE = System::Int8(0x1e);
static const System::Int8 SQL_DESC_MINIMUM_SCALE = System::Int8(0x1f);
static const System::Int8 SQL_DESC_NUM_PREC_RADIX = System::Int8(0x20);
static const System::Int8 SQL_DESC_PARAMETER_TYPE = System::Int8(0x21);
static const System::Int8 SQL_DESC_ROWS_PROCESSED_PTR = System::Int8(0x22);
static const System::Int8 SQL_DESC_ROWVER = System::Int8(0x23);
static const System::Int8 SQL_DESC_SCHEMA_NAME = System::Int8(0x10);
static const System::Int8 SQL_DESC_SEARCHABLE = System::Int8(0xd);
static const System::Int8 SQL_DESC_TYPE_NAME = System::Int8(0xe);
static const System::Int8 SQL_DESC_TABLE_NAME = System::Int8(0xf);
static const System::Int8 SQL_DESC_UNSIGNED = System::Int8(0x8);
static const System::Int8 SQL_DESC_UPDATABLE = System::Int8(0xa);
static const short SQL_DIAG_CURSOR_ROW_COUNT = short(-1249);
static const short SQL_DIAG_ROW_NUMBER = short(-1248);
static const short SQL_DIAG_COLUMN_NUMBER = short(-1247);
static const System::Int8 SQL_DATE = System::Int8(0x9);
static const System::Int8 SQL_INTERVAL = System::Int8(0xa);
static const System::Int8 SQL_TIME = System::Int8(0xa);
static const System::Int8 SQL_TIMESTAMP = System::Int8(0xb);
static const System::Int8 SQL_LONGVARCHAR = System::Int8(-1);
static const System::Int8 SQL_BINARY = System::Int8(-2);
static const System::Int8 SQL_VARBINARY = System::Int8(-3);
static const System::Int8 SQL_LONGVARBINARY = System::Int8(-4);
static const System::Int8 SQL_BIGINT = System::Int8(-5);
static const System::Int8 SQL_TINYINT = System::Int8(-6);
static const System::Int8 SQL_BIT = System::Int8(-7);
static const System::Int8 SQL_GUID = System::Int8(-11);
static const System::Int8 SQL_WCHAR = System::Int8(-8);
static const System::Int8 SQL_WVARCHAR = System::Int8(-9);
static const System::Int8 SQL_WLONGVARCHAR = System::Int8(-10);
static const System::Int8 SQL_CODE_YEAR = System::Int8(0x1);
static const System::Int8 SQL_CODE_MONTH = System::Int8(0x2);
static const System::Int8 SQL_CODE_DAY = System::Int8(0x3);
static const System::Int8 SQL_CODE_HOUR = System::Int8(0x4);
static const System::Int8 SQL_CODE_MINUTE = System::Int8(0x5);
static const System::Int8 SQL_CODE_SECOND = System::Int8(0x6);
static const System::Int8 SQL_CODE_YEAR_TO_MONTH = System::Int8(0x7);
static const System::Int8 SQL_CODE_DAY_TO_HOUR = System::Int8(0x8);
static const System::Int8 SQL_CODE_DAY_TO_MINUTE = System::Int8(0x9);
static const System::Int8 SQL_CODE_DAY_TO_SECOND = System::Int8(0xa);
static const System::Int8 SQL_CODE_HOUR_TO_MINUTE = System::Int8(0xb);
static const System::Int8 SQL_CODE_HOUR_TO_SECOND = System::Int8(0xc);
static const System::Int8 SQL_CODE_MINUTE_TO_SECOND = System::Int8(0xd);
static const System::Int8 SQL_INTERVAL_YEAR = System::Int8(0x65);
static const System::Int8 SQL_INTERVAL_MONTH = System::Int8(0x66);
static const System::Int8 SQL_INTERVAL_DAY = System::Int8(0x67);
static const System::Int8 SQL_INTERVAL_HOUR = System::Int8(0x68);
static const System::Int8 SQL_INTERVAL_MINUTE = System::Int8(0x69);
static const System::Int8 SQL_INTERVAL_SECOND = System::Int8(0x6a);
static const System::Int8 SQL_INTERVAL_YEAR_TO_MONTH = System::Int8(0x6b);
static const System::Int8 SQL_INTERVAL_DAY_TO_HOUR = System::Int8(0x6c);
static const System::Int8 SQL_INTERVAL_DAY_TO_MINUTE = System::Int8(0x6d);
static const System::Int8 SQL_INTERVAL_DAY_TO_SECOND = System::Int8(0x6e);
static const System::Int8 SQL_INTERVAL_HOUR_TO_MINUTE = System::Int8(0x6f);
static const System::Int8 SQL_INTERVAL_HOUR_TO_SECOND = System::Int8(0x70);
static const System::Int8 SQL_INTERVAL_MINUTE_TO_SECOND = System::Int8(0x71);
static const System::Int8 SQL_UNICODE = System::Int8(-8);
static const System::Int8 SQL_UNICODE_VARCHAR = System::Int8(-9);
static const System::Int8 SQL_UNICODE_LONGVARCHAR = System::Int8(-10);
static const System::Int8 SQL_UNICODE_CHAR = System::Int8(-8);
static const System::Int8 SQL_C_CHAR = System::Int8(0x1);
static const System::Int8 SQL_C_WCHAR = System::Int8(-8);
static const System::Int8 SQL_C_LONG = System::Int8(0x4);
static const System::Int8 SQL_C_SHORT = System::Int8(0x5);
static const System::Int8 SQL_C_FLOAT = System::Int8(0x7);
static const System::Int8 SQL_C_DOUBLE = System::Int8(0x8);
static const System::Int8 SQL_C_NUMERIC = System::Int8(0x2);
static const System::Int8 SQL_C_DEFAULT = System::Int8(0x63);
static const System::Int8 SQL_SIGNED_OFFSET = System::Int8(-20);
static const System::Int8 SQL_UNSIGNED_OFFSET = System::Int8(-22);
static const System::Int8 SQL_C_DATE = System::Int8(0x9);
static const System::Int8 SQL_C_TIME = System::Int8(0xa);
static const System::Int8 SQL_C_TIMESTAMP = System::Int8(0xb);
static const System::Int8 SQL_C_TYPE_DATE = System::Int8(0x5b);
static const System::Int8 SQL_C_TYPE_TIME = System::Int8(0x5c);
static const System::Int8 SQL_C_TYPE_TIMESTAMP = System::Int8(0x5d);
static const System::Int8 SQL_C_INTERVAL_YEAR = System::Int8(0x65);
static const System::Int8 SQL_C_INTERVAL_MONTH = System::Int8(0x66);
static const System::Int8 SQL_C_INTERVAL_DAY = System::Int8(0x67);
static const System::Int8 SQL_C_INTERVAL_HOUR = System::Int8(0x68);
static const System::Int8 SQL_C_INTERVAL_MINUTE = System::Int8(0x69);
static const System::Int8 SQL_C_INTERVAL_SECOND = System::Int8(0x6a);
static const System::Int8 SQL_C_INTERVAL_YEAR_TO_MONTH = System::Int8(0x6b);
static const System::Int8 SQL_C_INTERVAL_DAY_TO_HOUR = System::Int8(0x6c);
static const System::Int8 SQL_C_INTERVAL_DAY_TO_MINUTE = System::Int8(0x6d);
static const System::Int8 SQL_C_INTERVAL_DAY_TO_SECOND = System::Int8(0x6e);
static const System::Int8 SQL_C_INTERVAL_HOUR_TO_MINUTE = System::Int8(0x6f);
static const System::Int8 SQL_C_INTERVAL_HOUR_TO_SECOND = System::Int8(0x70);
static const System::Int8 SQL_C_INTERVAL_MINUTE_TO_SECOND = System::Int8(0x71);
static const System::Int8 SQL_C_BINARY = System::Int8(-2);
static const System::Int8 SQL_C_BIT = System::Int8(-7);
static const System::Int8 SQL_C_SBIGINT = System::Int8(-25);
static const System::Int8 SQL_C_UBIGINT = System::Int8(-27);
static const System::Int8 SQL_C_TINYINT = System::Int8(-6);
static const System::Int8 SQL_C_SLONG = System::Int8(-16);
static const System::Int8 SQL_C_SSHORT = System::Int8(-15);
static const System::Int8 SQL_C_STINYINT = System::Int8(-26);
static const System::Int8 SQL_C_ULONG = System::Int8(-18);
static const System::Int8 SQL_C_USHORT = System::Int8(-17);
static const System::Int8 SQL_C_UTINYINT = System::Int8(-28);
#ifndef __x86_64__
static const System::Int8 SQL_C_BOOKMARK = System::Int8(-18);
#else /* __x86_64__ */
static const System::Int8 SQL_C_BOOKMARK = System::Int8(-27);
#endif /* __x86_64__ */
static const System::Int8 SQL_C_GUID = System::Int8(-11);
static const System::Int8 SQL_TYPE_NULL = System::Int8(0x0);
static const System::Word SQL_DRIVER_C_TYPE_BASE = System::Word(0x4000);
static const System::Word SQL_DRIVER_SQL_TYPE_BASE = System::Word(0x4000);
static const System::Word SQL_DRIVER_DESC_FIELD_BASE = System::Word(0x4000);
static const System::Word SQL_DRIVER_DIAG_FIELD_BASE = System::Word(0x4000);
static const System::Word SQL_DRIVER_INFO_TYPE_BASE = System::Word(0x4000);
static const System::Word SQL_DRIVER_CONN_ATTR_BASE = System::Word(0x4000);
static const System::Word SQL_DRIVER_STMT_ATTR_BASE = System::Word(0x4000);
static const System::Int8 SQL_C_VARBOOKMARK = System::Int8(-2);
static const System::Int8 SQL_NO_ROW_NUMBER = System::Int8(-1);
static const System::Int8 SQL_NO_COLUMN_NUMBER = System::Int8(-1);
static const System::Int8 SQL_ROW_NUMBER_UNKNOWN = System::Int8(-2);
static const System::Int8 SQL_COLUMN_NUMBER_UNKNOWN = System::Int8(-2);
static const System::Int8 SQL_DEFAULT_PARAM = System::Int8(-5);
static const System::Int8 SQL_IGNORE = System::Int8(-6);
static const System::Int8 SQL_COLUMN_IGNORE = System::Int8(-6);
static const System::Int8 SQL_LEN_DATA_AT_EXEC_OFFSET = System::Int8(-100);
static const System::Int8 SQL_LEN_BINARY_ATTR_OFFSET = System::Int8(-100);
static const System::Int8 SQL_PARAM_TYPE_UNKNOWN = System::Int8(0x0);
static const System::Int8 SQL_PARAM_INPUT = System::Int8(0x1);
static const System::Int8 SQL_PARAM_INPUT_OUTPUT = System::Int8(0x2);
static const System::Int8 SQL_RESULT_COL = System::Int8(0x3);
static const System::Int8 SQL_PARAM_OUTPUT = System::Int8(0x4);
static const System::Int8 SQL_RETURN_VALUE = System::Int8(0x5);
static const System::Int8 SQL_PARAM_INPUT_OUTPUT_STREAM = System::Int8(0x8);
static const System::Int8 SQL_PARAM_OUTPUT_STREAM = System::Int8(0x10);
static const System::Int8 SQL_PARAM_TYPE_DEFAULT = System::Int8(0x2);
static const System::Int8 SQL_SETPARAM_VALUE_MAX = System::Int8(-1);
static const System::Int8 SQL_COLATT_OPT_MAX = System::Int8(0x12);
static const System::Int8 SQL_COLATT_OPT_MIN = System::Int8(0x0);
static const System::Int8 SQL_ATTR_READONLY = System::Int8(0x0);
static const System::Int8 SQL_ATTR_WRITE = System::Int8(0x1);
static const System::Int8 SQL_ATTR_READWRITE_UNKNOWN = System::Int8(0x2);
static const System::Int8 SQL_UNSEARCHABLE = System::Int8(0x0);
static const System::Int8 SQL_LIKE_ONLY = System::Int8(0x1);
static const System::Int8 SQL_ALL_EXCEPT_LIKE = System::Int8(0x2);
static const System::Int8 SQL_SEARCHABLE = System::Int8(0x3);
static const System::Int8 SQL_PRED_SEARCHABLE = System::Int8(0x3);
static const System::Int8 SQL_COL_PRED_CHAR = System::Int8(0x1);
static const System::Int8 SQL_COL_PRED_BASIC = System::Int8(0x2);
static const System::Int8 SQL_NO_TOTAL = System::Int8(-4);
static const System::Int8 SQL_API_SQLALLOCHANDLESTD = System::Int8(0x49);
static const System::Int8 SQL_API_SQLBULKOPERATIONS = System::Int8(0x18);
static const System::Int8 SQL_API_SQLBINDPARAMETER = System::Int8(0x48);
static const System::Int8 SQL_API_SQLBROWSECONNECT = System::Int8(0x37);
static const System::Int8 SQL_API_SQLCOLATTRIBUTES = System::Int8(0x6);
static const System::Int8 SQL_API_SQLCOLUMNPRIVILEGES = System::Int8(0x38);
static const System::Int8 SQL_API_SQLDESCRIBEPARAM = System::Int8(0x3a);
static const System::Int8 SQL_API_SQLDRIVERCONNECT = System::Int8(0x29);
static const System::Int8 SQL_API_SQLDRIVERS = System::Int8(0x47);
static const System::Int8 SQL_API_SQLEXTENDEDFETCH = System::Int8(0x3b);
static const System::Int8 SQL_API_SQLFOREIGNKEYS = System::Int8(0x3c);
static const System::Int8 SQL_API_SQLMORERESULTS = System::Int8(0x3d);
static const System::Int8 SQL_API_SQLNATIVESQL = System::Int8(0x3e);
static const System::Int8 SQL_API_SQLNUMPARAMS = System::Int8(0x3f);
static const System::Int8 SQL_API_SQLPARAMOPTIONS = System::Int8(0x40);
static const System::Int8 SQL_API_SQLPRIMARYKEYS = System::Int8(0x41);
static const System::Int8 SQL_API_SQLPROCEDURECOLUMNS = System::Int8(0x42);
static const System::Int8 SQL_API_SQLPROCEDURES = System::Int8(0x43);
static const System::Int8 SQL_API_SQLSETPOS = System::Int8(0x44);
static const System::Int8 SQL_API_SQLSETSCROLLOPTIONS = System::Int8(0x45);
static const System::Int8 SQL_API_SQLTABLEPRIVILEGES = System::Int8(0x46);
static const System::Int8 SQL_API_ALL_FUNCTIONS = System::Int8(0x0);
static const System::Byte SQL_API_LOADBYORDINAL = System::Byte(0xc7);
static const System::Word SQL_API_ODBC3_ALL_FUNCTIONS = System::Word(0x3e7);
static const System::Byte SQL_API_ODBC3_ALL_FUNCTIONS_SIZE = System::Byte(0xfa);
static const System::Int8 SQL_INFO_FIRST = System::Int8(0x0);
static const System::Int8 SQL_ACTIVE_CONNECTIONS = System::Int8(0x0);
static const System::Int8 SQL_ACTIVE_STATEMENTS = System::Int8(0x1);
static const System::Int8 SQL_DRIVER_HDBC = System::Int8(0x3);
static const System::Int8 SQL_DRIVER_HENV = System::Int8(0x4);
static const System::Int8 SQL_DRIVER_HSTMT = System::Int8(0x5);
static const System::Int8 SQL_DRIVER_NAME = System::Int8(0x6);
static const System::Int8 SQL_DRIVER_VER = System::Int8(0x7);
static const System::Int8 SQL_ODBC_API_CONFORMANCE = System::Int8(0x9);
static const System::Int8 SQL_ODBC_VER = System::Int8(0xa);
static const System::Int8 SQL_ROW_UPDATES = System::Int8(0xb);
static const System::Int8 SQL_ODBC_SAG_CLI_CONFORMANCE = System::Int8(0xc);
static const System::Int8 SQL_ODBC_SQL_CONFORMANCE = System::Int8(0xf);
static const System::Int8 SQL_PROCEDURES = System::Int8(0x15);
static const System::Int8 SQL_CONCAT_NULL_BEHAVIOR = System::Int8(0x16);
static const System::Int8 SQL_CURSOR_ROLLBACK_BEHAVIOR = System::Int8(0x18);
static const System::Int8 SQL_EXPRESSIONS_IN_ORDERBY = System::Int8(0x1b);
static const System::Int8 SQL_MAX_OWNER_NAME_LEN = System::Int8(0x20);
static const System::Int8 SQL_MAX_PROCEDURE_NAME_LEN = System::Int8(0x21);
static const System::Int8 SQL_MAX_QUALIFIER_NAME_LEN = System::Int8(0x22);
static const System::Int8 SQL_MULT_RESULT_SETS = System::Int8(0x24);
static const System::Int8 SQL_MULTIPLE_ACTIVE_TXN = System::Int8(0x25);
static const System::Int8 SQL_OUTER_JOINS = System::Int8(0x26);
static const System::Int8 SQL_OWNER_TERM = System::Int8(0x27);
static const System::Int8 SQL_PROCEDURE_TERM = System::Int8(0x28);
static const System::Int8 SQL_QUALIFIER_NAME_SEPARATOR = System::Int8(0x29);
static const System::Int8 SQL_QUALIFIER_TERM = System::Int8(0x2a);
static const System::Int8 SQL_SCROLL_OPTIONS = System::Int8(0x2c);
static const System::Int8 SQL_TABLE_TERM = System::Int8(0x2d);
static const System::Int8 SQL_CONVERT_FUNCTIONS = System::Int8(0x30);
static const System::Int8 SQL_NUMERIC_FUNCTIONS = System::Int8(0x31);
static const System::Int8 SQL_STRING_FUNCTIONS = System::Int8(0x32);
static const System::Int8 SQL_SYSTEM_FUNCTIONS = System::Int8(0x33);
static const System::Int8 SQL_TIMEDATE_FUNCTIONS = System::Int8(0x34);
static const System::Int8 SQL_CONVERT_BIGINT = System::Int8(0x35);
static const System::Int8 SQL_CONVERT_BINARY = System::Int8(0x36);
static const System::Int8 SQL_CONVERT_BIT = System::Int8(0x37);
static const System::Int8 SQL_CONVERT_CHAR = System::Int8(0x38);
static const System::Int8 SQL_CONVERT_DATE = System::Int8(0x39);
static const System::Int8 SQL_CONVERT_DECIMAL = System::Int8(0x3a);
static const System::Int8 SQL_CONVERT_DOUBLE = System::Int8(0x3b);
static const System::Int8 SQL_CONVERT_FLOAT = System::Int8(0x3c);
static const System::Int8 SQL_CONVERT_INTEGER = System::Int8(0x3d);
static const System::Int8 SQL_CONVERT_LONGVARCHAR = System::Int8(0x3e);
static const System::Int8 SQL_CONVERT_NUMERIC = System::Int8(0x3f);
static const System::Int8 SQL_CONVERT_REAL = System::Int8(0x40);
static const System::Int8 SQL_CONVERT_SMALLINT = System::Int8(0x41);
static const System::Int8 SQL_CONVERT_TIME = System::Int8(0x42);
static const System::Int8 SQL_CONVERT_TIMESTAMP = System::Int8(0x43);
static const System::Int8 SQL_CONVERT_TINYINT = System::Int8(0x44);
static const System::Int8 SQL_CONVERT_VARBINARY = System::Int8(0x45);
static const System::Int8 SQL_CONVERT_VARCHAR = System::Int8(0x46);
static const System::Int8 SQL_CONVERT_LONGVARBINARY = System::Int8(0x47);
static const System::Int8 SQL_ODBC_SQL_OPT_IEF = System::Int8(0x49);
static const System::Int8 SQL_CORRELATION_NAME = System::Int8(0x4a);
static const System::Int8 SQL_NON_NULLABLE_COLUMNS = System::Int8(0x4b);
static const System::Int8 SQL_DRIVER_HLIB = System::Int8(0x4c);
static const System::Int8 SQL_DRIVER_ODBC_VER = System::Int8(0x4d);
static const System::Int8 SQL_LOCK_TYPES = System::Int8(0x4e);
static const System::Int8 SQL_POS_OPERATIONS = System::Int8(0x4f);
static const System::Int8 SQL_POSITIONED_STATEMENTS = System::Int8(0x50);
static const System::Int8 SQL_BOOKMARK_PERSISTENCE = System::Int8(0x52);
static const System::Int8 SQL_STATIC_SENSITIVITY = System::Int8(0x53);
static const System::Int8 SQL_FILE_USAGE = System::Int8(0x54);
static const System::Int8 SQL_COLUMN_ALIAS = System::Int8(0x57);
static const System::Int8 SQL_GROUP_BY = System::Int8(0x58);
static const System::Int8 SQL_KEYWORDS = System::Int8(0x59);
static const System::Int8 SQL_OWNER_USAGE = System::Int8(0x5b);
static const System::Int8 SQL_QUALIFIER_USAGE = System::Int8(0x5c);
static const System::Int8 SQL_QUOTED_IDENTIFIER_CASE = System::Int8(0x5d);
static const System::Int8 SQL_SUBQUERIES = System::Int8(0x5f);
static const System::Int8 SQL_UNION = System::Int8(0x60);
static const System::Int8 SQL_MAX_ROW_SIZE_INCLUDES_LONG = System::Int8(0x67);
static const System::Int8 SQL_MAX_CHAR_LITERAL_LEN = System::Int8(0x6c);
static const System::Int8 SQL_TIMEDATE_ADD_INTERVALS = System::Int8(0x6d);
static const System::Int8 SQL_TIMEDATE_DIFF_INTERVALS = System::Int8(0x6e);
static const System::Int8 SQL_NEED_LONG_DATA_LEN = System::Int8(0x6f);
static const System::Int8 SQL_MAX_BINARY_LITERAL_LEN = System::Int8(0x70);
static const System::Int8 SQL_LIKE_ESCAPE_CLAUSE = System::Int8(0x71);
static const System::Int8 SQL_QUALIFIER_LOCATION = System::Int8(0x72);
static const System::Int8 SQL_ACTIVE_ENVIRONMENTS = System::Int8(0x74);
static const System::Int8 SQL_ALTER_DOMAIN = System::Int8(0x75);
static const System::Int8 SQL_SQL_CONFORMANCE = System::Int8(0x76);
static const System::Int8 SQL_DATETIME_LITERALS = System::Int8(0x77);
static const System::Word SQL_ASYNC_MODE = System::Word(0x2725);
static const System::Int8 SQL_BATCH_ROW_COUNT = System::Int8(0x78);
static const System::Int8 SQL_BATCH_SUPPORT = System::Int8(0x79);
static const System::Int8 SQL_CATALOG_LOCATION = System::Int8(0x72);
static const System::Int8 SQL_CATALOG_NAME_SEPARATOR = System::Int8(0x29);
static const System::Int8 SQL_CATALOG_TERM = System::Int8(0x2a);
static const System::Int8 SQL_CATALOG_USAGE = System::Int8(0x5c);
static const System::Int8 SQL_CONVERT_WCHAR = System::Int8(0x7a);
static const System::Int8 SQL_CONVERT_INTERVAL_DAY_TIME = System::Int8(0x7b);
static const System::Int8 SQL_CONVERT_INTERVAL_YEAR_MONTH = System::Int8(0x7c);
static const System::Int8 SQL_CONVERT_WLONGVARCHAR = System::Int8(0x7d);
static const System::Int8 SQL_CONVERT_WVARCHAR = System::Int8(0x7e);
static const System::Int8 SQL_CREATE_ASSERTION = System::Int8(0x7f);
static const System::Byte SQL_CREATE_CHARACTER_SET = System::Byte(0x80);
static const System::Byte SQL_CREATE_COLLATION = System::Byte(0x81);
static const System::Byte SQL_CREATE_DOMAIN = System::Byte(0x82);
static const System::Byte SQL_CREATE_SCHEMA = System::Byte(0x83);
static const System::Byte SQL_CREATE_TABLE = System::Byte(0x84);
static const System::Byte SQL_CREATE_TRANSLATION = System::Byte(0x85);
static const System::Byte SQL_CREATE_VIEW = System::Byte(0x86);
static const System::Byte SQL_DRIVER_HDESC = System::Byte(0x87);
static const System::Byte SQL_DROP_ASSERTION = System::Byte(0x88);
static const System::Byte SQL_DROP_CHARACTER_SET = System::Byte(0x89);
static const System::Byte SQL_DROP_COLLATION = System::Byte(0x8a);
static const System::Byte SQL_DROP_DOMAIN = System::Byte(0x8b);
static const System::Byte SQL_DROP_SCHEMA = System::Byte(0x8c);
static const System::Byte SQL_DROP_TABLE = System::Byte(0x8d);
static const System::Byte SQL_DROP_TRANSLATION = System::Byte(0x8e);
static const System::Byte SQL_DROP_VIEW = System::Byte(0x8f);
static const System::Byte SQL_DYNAMIC_CURSOR_ATTRIBUTES1 = System::Byte(0x90);
static const System::Byte SQL_DYNAMIC_CURSOR_ATTRIBUTES2 = System::Byte(0x91);
static const System::Byte SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES1 = System::Byte(0x92);
static const System::Byte SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES2 = System::Byte(0x93);
static const System::Byte SQL_INDEX_KEYWORDS = System::Byte(0x94);
static const System::Byte SQL_INFO_SCHEMA_VIEWS = System::Byte(0x95);
static const System::Byte SQL_KEYSET_CURSOR_ATTRIBUTES1 = System::Byte(0x96);
static const System::Byte SQL_KEYSET_CURSOR_ATTRIBUTES2 = System::Byte(0x97);
static const System::Word SQL_MAX_ASYNC_CONCURRENT_STATEMENTS = System::Word(0x2726);
static const System::Byte SQL_ODBC_INTERFACE_CONFORMANCE = System::Byte(0x98);
static const System::Byte SQL_PARAM_ARRAY_ROW_COUNTS = System::Byte(0x99);
static const System::Byte SQL_PARAM_ARRAY_SELECTS = System::Byte(0x9a);
static const System::Int8 SQL_SCHEMA_TERM = System::Int8(0x27);
static const System::Int8 SQL_SCHEMA_USAGE = System::Int8(0x5b);
static const System::Byte SQL_SQL92_DATETIME_FUNCTIONS = System::Byte(0x9b);
static const System::Byte SQL_SQL92_FOREIGN_KEY_DELETE_RULE = System::Byte(0x9c);
static const System::Byte SQL_SQL92_FOREIGN_KEY_UPDATE_RULE = System::Byte(0x9d);
static const System::Byte SQL_SQL92_GRANT = System::Byte(0x9e);
static const System::Byte SQL_SQL92_NUMERIC_VALUE_FUNCTIONS = System::Byte(0x9f);
static const System::Byte SQL_SQL92_PREDICATES = System::Byte(0xa0);
static const System::Byte SQL_SQL92_RELATIONAL_JOIN_OPERATORS = System::Byte(0xa1);
static const System::Byte SQL_SQL92_REVOKE = System::Byte(0xa2);
static const System::Byte SQL_SQL92_ROW_VALUE_CONSTRUCTOR = System::Byte(0xa3);
static const System::Byte SQL_SQL92_STRING_FUNCTIONS = System::Byte(0xa4);
static const System::Byte SQL_SQL92_VALUE_EXPRESSIONS = System::Byte(0xa5);
static const System::Byte SQL_STANDARD_CLI_CONFORMANCE = System::Byte(0xa6);
static const System::Byte SQL_STATIC_CURSOR_ATTRIBUTES1 = System::Byte(0xa7);
static const System::Byte SQL_STATIC_CURSOR_ATTRIBUTES2 = System::Byte(0xa8);
static const System::Byte SQL_AGGREGATE_FUNCTIONS = System::Byte(0xa9);
static const System::Byte SQL_DDL_INDEX = System::Byte(0xaa);
static const System::Byte SQL_DM_VER = System::Byte(0xab);
static const System::Byte SQL_INSERT_STATEMENT = System::Byte(0xac);
static const System::Byte SQL_CONVERT_GUID = System::Byte(0xad);
static const System::Int8 SQL_UNION_STATEMENT = System::Int8(0x60);
static const System::Word SQL_ASYNC_DBC_FUNCTIONS = System::Word(0x2727);
static const System::Word SQL_DTC_TRANSITION_COST = System::Word(0x6d6);
static const System::Int8 SQL_CVT_CHAR = System::Int8(0x1);
static const System::Int8 SQL_CVT_NUMERIC = System::Int8(0x2);
static const System::Int8 SQL_CVT_DECIMAL = System::Int8(0x4);
static const System::Int8 SQL_CVT_INTEGER = System::Int8(0x8);
static const System::Int8 SQL_CVT_SMALLINT = System::Int8(0x10);
static const System::Int8 SQL_CVT_FLOAT = System::Int8(0x20);
static const System::Int8 SQL_CVT_REAL = System::Int8(0x40);
static const System::Byte SQL_CVT_DOUBLE = System::Byte(0x80);
static const System::Word SQL_CVT_VARCHAR = System::Word(0x100);
static const System::Word SQL_CVT_LONGVARCHAR = System::Word(0x200);
static const System::Word SQL_CVT_BINARY = System::Word(0x400);
static const System::Word SQL_CVT_VARBINARY = System::Word(0x800);
static const System::Word SQL_CVT_BIT = System::Word(0x1000);
static const System::Word SQL_CVT_TINYINT = System::Word(0x2000);
static const System::Word SQL_CVT_BIGINT = System::Word(0x4000);
static const System::Word SQL_CVT_DATE = System::Word(0x8000);
static const int SQL_CVT_TIME = int(0x10000);
static const int SQL_CVT_TIMESTAMP = int(0x20000);
static const int SQL_CVT_LONGVARBINARY = int(0x40000);
static const int SQL_CVT_INTERVAL_YEAR_MONTH = int(0x80000);
static const int SQL_CVT_INTERVAL_DAY_TIME = int(0x100000);
static const int SQL_CVT_WCHAR = int(0x200000);
static const int SQL_CVT_WLONGVARCHAR = int(0x400000);
static const int SQL_CVT_WVARCHAR = int(0x800000);
static const int SQL_CVT_GUID = int(0x1000000);
static const System::Int8 SQL_FN_CVT_CONVERT = System::Int8(0x1);
static const System::Int8 SQL_FN_CVT_CAST = System::Int8(0x2);
static const System::Int8 SQL_FN_STR_CONCAT = System::Int8(0x1);
static const System::Int8 SQL_FN_STR_INSERT = System::Int8(0x2);
static const System::Int8 SQL_FN_STR_LEFT = System::Int8(0x4);
static const System::Int8 SQL_FN_STR_LTRIM = System::Int8(0x8);
static const System::Int8 SQL_FN_STR_LENGTH = System::Int8(0x10);
static const System::Int8 SQL_FN_STR_LOCATE = System::Int8(0x20);
static const System::Int8 SQL_FN_STR_LCASE = System::Int8(0x40);
static const System::Byte SQL_FN_STR_REPEAT = System::Byte(0x80);
static const System::Word SQL_FN_STR_REPLACE = System::Word(0x100);
static const System::Word SQL_FN_STR_RIGHT = System::Word(0x200);
static const System::Word SQL_FN_STR_RTRIM = System::Word(0x400);
static const System::Word SQL_FN_STR_SUBSTRING = System::Word(0x800);
static const System::Word SQL_FN_STR_UCASE = System::Word(0x1000);
static const System::Word SQL_FN_STR_ASCII = System::Word(0x2000);
static const System::Word SQL_FN_STR_CHAR = System::Word(0x4000);
static const System::Word SQL_FN_STR_DIFFERENCE = System::Word(0x8000);
static const int SQL_FN_STR_LOCATE_2 = int(0x10000);
static const int SQL_FN_STR_SOUNDEX = int(0x20000);
static const int SQL_FN_STR_SPACE = int(0x40000);
static const int SQL_FN_STR_BIT_LENGTH = int(0x80000);
static const int SQL_FN_STR_CHAR_LENGTH = int(0x100000);
static const int SQL_FN_STR_CHARACTER_LENGTH = int(0x200000);
static const int SQL_FN_STR_OCTET_LENGTH = int(0x400000);
static const int SQL_FN_STR_POSITION = int(0x800000);
static const System::Int8 SQL_SSF_CONVERT = System::Int8(0x1);
static const System::Int8 SQL_SSF_LOWER = System::Int8(0x2);
static const System::Int8 SQL_SSF_UPPER = System::Int8(0x4);
static const System::Int8 SQL_SSF_SUBSTRING = System::Int8(0x8);
static const System::Int8 SQL_SSF_TRANSLATE = System::Int8(0x10);
static const System::Int8 SQL_SSF_TRIM_BOTH = System::Int8(0x20);
static const System::Int8 SQL_SSF_TRIM_LEADING = System::Int8(0x40);
static const System::Byte SQL_SSF_TRIM_TRAILING = System::Byte(0x80);
static const System::Int8 SQL_FN_NUM_ABS = System::Int8(0x1);
static const System::Int8 SQL_FN_NUM_ACOS = System::Int8(0x2);
static const System::Int8 SQL_FN_NUM_ASIN = System::Int8(0x4);
static const System::Int8 SQL_FN_NUM_ATAN = System::Int8(0x8);
static const System::Int8 SQL_FN_NUM_ATAN2 = System::Int8(0x10);
static const System::Int8 SQL_FN_NUM_CEILING = System::Int8(0x20);
static const System::Int8 SQL_FN_NUM_COS = System::Int8(0x40);
static const System::Byte SQL_FN_NUM_COT = System::Byte(0x80);
static const System::Word SQL_FN_NUM_EXP = System::Word(0x100);
static const System::Word SQL_FN_NUM_FLOOR = System::Word(0x200);
static const System::Word SQL_FN_NUM_LOG = System::Word(0x400);
static const System::Word SQL_FN_NUM_MOD = System::Word(0x800);
static const System::Word SQL_FN_NUM_SIGN = System::Word(0x1000);
static const System::Word SQL_FN_NUM_SIN = System::Word(0x2000);
static const System::Word SQL_FN_NUM_SQRT = System::Word(0x4000);
static const System::Word SQL_FN_NUM_TAN = System::Word(0x8000);
static const int SQL_FN_NUM_PI = int(0x10000);
static const int SQL_FN_NUM_RAND = int(0x20000);
static const int SQL_FN_NUM_DEGREES = int(0x40000);
static const int SQL_FN_NUM_LOG10 = int(0x80000);
static const int SQL_FN_NUM_POWER = int(0x100000);
static const int SQL_FN_NUM_RADIANS = int(0x200000);
static const int SQL_FN_NUM_ROUND = int(0x400000);
static const int SQL_FN_NUM_TRUNCATE = int(0x800000);
static const System::Int8 SQL_SNVF_BIT_LENGTH = System::Int8(0x1);
static const System::Int8 SQL_SNVF_CHAR_LENGTH = System::Int8(0x2);
static const System::Int8 SQL_SNVF_CHARACTER_LENGTH = System::Int8(0x4);
static const System::Int8 SQL_SNVF_EXTRACT = System::Int8(0x8);
static const System::Int8 SQL_SNVF_OCTET_LENGTH = System::Int8(0x10);
static const System::Int8 SQL_SNVF_POSITION = System::Int8(0x20);
static const System::Int8 SQL_FN_TD_NOW = System::Int8(0x1);
static const System::Int8 SQL_FN_TD_CURDATE = System::Int8(0x2);
static const System::Int8 SQL_FN_TD_DAYOFMONTH = System::Int8(0x4);
static const System::Int8 SQL_FN_TD_DAYOFWEEK = System::Int8(0x8);
static const System::Int8 SQL_FN_TD_DAYOFYEAR = System::Int8(0x10);
static const System::Int8 SQL_FN_TD_MONTH = System::Int8(0x20);
static const System::Int8 SQL_FN_TD_QUARTER = System::Int8(0x40);
static const System::Byte SQL_FN_TD_WEEK = System::Byte(0x80);
static const System::Word SQL_FN_TD_YEAR = System::Word(0x100);
static const System::Word SQL_FN_TD_CURTIME = System::Word(0x200);
static const System::Word SQL_FN_TD_HOUR = System::Word(0x400);
static const System::Word SQL_FN_TD_MINUTE = System::Word(0x800);
static const System::Word SQL_FN_TD_SECOND = System::Word(0x1000);
static const System::Word SQL_FN_TD_TIMESTAMPADD = System::Word(0x2000);
static const System::Word SQL_FN_TD_TIMESTAMPDIFF = System::Word(0x4000);
static const System::Word SQL_FN_TD_DAYNAME = System::Word(0x8000);
static const int SQL_FN_TD_MONTHNAME = int(0x10000);
static const int SQL_FN_TD_CURRENT_DATE = int(0x20000);
static const int SQL_FN_TD_CURRENT_TIME = int(0x40000);
static const int SQL_FN_TD_CURRENT_TIMESTAMP = int(0x80000);
static const int SQL_FN_TD_EXTRACT = int(0x100000);
static const System::Int8 SQL_SDF_CURRENT_DATE = System::Int8(0x1);
static const System::Int8 SQL_SDF_CURRENT_TIME = System::Int8(0x2);
static const System::Int8 SQL_SDF_CURRENT_TIMESTAMP = System::Int8(0x4);
static const System::Int8 SQL_FN_SYS_USERNAME = System::Int8(0x1);
static const System::Int8 SQL_FN_SYS_DBNAME = System::Int8(0x2);
static const System::Int8 SQL_FN_SYS_IFNULL = System::Int8(0x4);
static const System::Int8 SQL_FN_TSI_FRAC_SECOND = System::Int8(0x1);
static const System::Int8 SQL_FN_TSI_SECOND = System::Int8(0x2);
static const System::Int8 SQL_FN_TSI_MINUTE = System::Int8(0x4);
static const System::Int8 SQL_FN_TSI_HOUR = System::Int8(0x8);
static const System::Int8 SQL_FN_TSI_DAY = System::Int8(0x10);
static const System::Int8 SQL_FN_TSI_WEEK = System::Int8(0x20);
static const System::Int8 SQL_FN_TSI_MONTH = System::Int8(0x40);
static const System::Byte SQL_FN_TSI_QUARTER = System::Byte(0x80);
static const System::Word SQL_FN_TSI_YEAR = System::Word(0x100);
static const System::Int8 SQL_CA1_NEXT = System::Int8(0x1);
static const System::Int8 SQL_CA1_ABSOLUTE = System::Int8(0x2);
static const System::Int8 SQL_CA1_RELATIVE = System::Int8(0x4);
static const System::Int8 SQL_CA1_BOOKMARK = System::Int8(0x8);
static const System::Int8 SQL_CA1_LOCK_NO_CHANGE = System::Int8(0x40);
static const System::Byte SQL_CA1_LOCK_EXCLUSIVE = System::Byte(0x80);
static const System::Word SQL_CA1_LOCK_UNLOCK = System::Word(0x100);
static const System::Word SQL_CA1_POS_POSITION = System::Word(0x200);
static const System::Word SQL_CA1_POS_UPDATE = System::Word(0x400);
static const System::Word SQL_CA1_POS_DELETE = System::Word(0x800);
static const System::Word SQL_CA1_POS_REFRESH = System::Word(0x1000);
static const System::Word SQL_CA1_POSITIONED_UPDATE = System::Word(0x2000);
static const System::Word SQL_CA1_POSITIONED_DELETE = System::Word(0x4000);
static const System::Word SQL_CA1_SELECT_FOR_UPDATE = System::Word(0x8000);
static const int SQL_CA1_BULK_ADD = int(0x10000);
static const int SQL_CA1_BULK_UPDATE_BY_BOOKMARK = int(0x20000);
static const int SQL_CA1_BULK_DELETE_BY_BOOKMARK = int(0x40000);
static const int SQL_CA1_BULK_FETCH_BY_BOOKMARK = int(0x80000);
static const System::Int8 SQL_CA2_READ_ONLY_CONCURRENCY = System::Int8(0x1);
static const System::Int8 SQL_CA2_LOCK_CONCURRENCY = System::Int8(0x2);
static const System::Int8 SQL_CA2_OPT_ROWVER_CONCURRENCY = System::Int8(0x4);
static const System::Int8 SQL_CA2_OPT_VALUES_CONCURRENCY = System::Int8(0x8);
static const System::Int8 SQL_CA2_SENSITIVITY_ADDITIONS = System::Int8(0x10);
static const System::Int8 SQL_CA2_SENSITIVITY_DELETIONS = System::Int8(0x20);
static const System::Int8 SQL_CA2_SENSITIVITY_UPDATES = System::Int8(0x40);
static const System::Byte SQL_CA2_MAX_ROWS_SELECT = System::Byte(0x80);
static const System::Word SQL_CA2_MAX_ROWS_INSERT = System::Word(0x100);
static const System::Word SQL_CA2_MAX_ROWS_DELETE = System::Word(0x200);
static const System::Word SQL_CA2_MAX_ROWS_UPDATE = System::Word(0x400);
static const System::Word SQL_CA2_MAX_ROWS_CATALOG = System::Word(0x800);
static const System::Word SQL_CA2_MAX_ROWS_AFFECTS_ALL = System::Word(0xf80);
static const System::Word SQL_CA2_CRC_EXACT = System::Word(0x1000);
static const System::Word SQL_CA2_CRC_APPROXIMATE = System::Word(0x2000);
static const System::Word SQL_CA2_SIMULATE_NON_UNIQUE = System::Word(0x4000);
static const System::Word SQL_CA2_SIMULATE_TRY_UNIQUE = System::Word(0x8000);
static const int SQL_CA2_SIMULATE_UNIQUE = int(0x10000);
static const System::Int8 SQL_OAC_NONE = System::Int8(0x0);
static const System::Int8 SQL_OAC_LEVEL1 = System::Int8(0x1);
static const System::Int8 SQL_OAC_LEVEL2 = System::Int8(0x2);
static const System::Int8 SQL_OSCC_NOT_COMPLIANT = System::Int8(0x0);
static const System::Int8 SQL_OSCC_COMPLIANT = System::Int8(0x1);
static const System::Int8 SQL_OSC_MINIMUM = System::Int8(0x0);
static const System::Int8 SQL_OSC_CORE = System::Int8(0x1);
static const System::Int8 SQL_OSC_EXTENDED = System::Int8(0x2);
static const System::Int8 SQL_CB_NULL = System::Int8(0x0);
static const System::Int8 SQL_CB_NON_NULL = System::Int8(0x1);
static const System::Int8 SQL_SO_FORWARD_ONLY = System::Int8(0x1);
static const System::Int8 SQL_SO_KEYSET_DRIVEN = System::Int8(0x2);
static const System::Int8 SQL_SO_DYNAMIC = System::Int8(0x4);
static const System::Int8 SQL_SO_MIXED = System::Int8(0x8);
static const System::Int8 SQL_SO_STATIC = System::Int8(0x10);
static const System::Byte SQL_FD_FETCH_BOOKMARK = System::Byte(0x80);
static const System::Int8 SQL_CN_NONE = System::Int8(0x0);
static const System::Int8 SQL_CN_DIFFERENT = System::Int8(0x1);
static const System::Int8 SQL_CN_ANY = System::Int8(0x2);
static const System::Int8 SQL_NNC_NULL = System::Int8(0x0);
static const System::Int8 SQL_NNC_NON_NULL = System::Int8(0x1);
static const System::Int8 SQL_NC_START = System::Int8(0x2);
static const System::Int8 SQL_NC_END = System::Int8(0x4);
static const System::Int8 SQL_FILE_NOT_SUPPORTED = System::Int8(0x0);
static const System::Int8 SQL_FILE_TABLE = System::Int8(0x1);
static const System::Int8 SQL_FILE_QUALIFIER = System::Int8(0x2);
static const System::Int8 SQL_FILE_CATALOG = System::Int8(0x2);
static const System::Int8 SQL_GD_BLOCK = System::Int8(0x4);
static const System::Int8 SQL_GD_BOUND = System::Int8(0x8);
static const System::Int8 SQL_GD_OUTPUT_PARAMS = System::Int8(0x10);
static const System::Int8 SQL_PS_POSITIONED_DELETE = System::Int8(0x1);
static const System::Int8 SQL_PS_POSITIONED_UPDATE = System::Int8(0x2);
static const System::Int8 SQL_PS_SELECT_FOR_UPDATE = System::Int8(0x4);
static const System::Int8 SQL_GB_NOT_SUPPORTED = System::Int8(0x0);
static const System::Int8 SQL_GB_GROUP_BY_EQUALS_SELECT = System::Int8(0x1);
static const System::Int8 SQL_GB_GROUP_BY_CONTAINS_SELECT = System::Int8(0x2);
static const System::Int8 SQL_GB_NO_RELATION = System::Int8(0x3);
static const System::Int8 SQL_GB_COLLATE = System::Int8(0x4);
static const System::Int8 SQL_OU_DML_STATEMENTS = System::Int8(0x1);
static const System::Int8 SQL_OU_PROCEDURE_INVOCATION = System::Int8(0x2);
static const System::Int8 SQL_OU_TABLE_DEFINITION = System::Int8(0x4);
static const System::Int8 SQL_OU_INDEX_DEFINITION = System::Int8(0x8);
static const System::Int8 SQL_OU_PRIVILEGE_DEFINITION = System::Int8(0x10);
static const System::Int8 SQL_SU_DML_STATEMENTS = System::Int8(0x1);
static const System::Int8 SQL_SU_PROCEDURE_INVOCATION = System::Int8(0x2);
static const System::Int8 SQL_SU_TABLE_DEFINITION = System::Int8(0x4);
static const System::Int8 SQL_SU_INDEX_DEFINITION = System::Int8(0x8);
static const System::Int8 SQL_SU_PRIVILEGE_DEFINITION = System::Int8(0x10);
static const System::Int8 SQL_QU_DML_STATEMENTS = System::Int8(0x1);
static const System::Int8 SQL_QU_PROCEDURE_INVOCATION = System::Int8(0x2);
static const System::Int8 SQL_QU_TABLE_DEFINITION = System::Int8(0x4);
static const System::Int8 SQL_QU_INDEX_DEFINITION = System::Int8(0x8);
static const System::Int8 SQL_QU_PRIVILEGE_DEFINITION = System::Int8(0x10);
static const System::Int8 SQL_CU_DML_STATEMENTS = System::Int8(0x1);
static const System::Int8 SQL_CU_PROCEDURE_INVOCATION = System::Int8(0x2);
static const System::Int8 SQL_CU_TABLE_DEFINITION = System::Int8(0x4);
static const System::Int8 SQL_CU_INDEX_DEFINITION = System::Int8(0x8);
static const System::Int8 SQL_CU_PRIVILEGE_DEFINITION = System::Int8(0x10);
static const System::Int8 SQL_SQ_COMPARISON = System::Int8(0x1);
static const System::Int8 SQL_SQ_EXISTS = System::Int8(0x2);
static const System::Int8 SQL_SQ_IN = System::Int8(0x4);
static const System::Int8 SQL_SQ_QUANTIFIED = System::Int8(0x8);
static const System::Int8 SQL_SQ_CORRELATED_SUBQUERIES = System::Int8(0x10);
static const System::Int8 SQL_U_UNION = System::Int8(0x1);
static const System::Int8 SQL_U_UNION_ALL = System::Int8(0x2);
static const System::Int8 SQL_BP_CLOSE = System::Int8(0x1);
static const System::Int8 SQL_BP_DELETE = System::Int8(0x2);
static const System::Int8 SQL_BP_DROP = System::Int8(0x4);
static const System::Int8 SQL_BP_TRANSACTION = System::Int8(0x8);
static const System::Int8 SQL_BP_UPDATE = System::Int8(0x10);
static const System::Int8 SQL_BP_OTHER_HSTMT = System::Int8(0x20);
static const System::Int8 SQL_BP_SCROLL = System::Int8(0x40);
static const System::Int8 SQL_SS_ADDITIONS = System::Int8(0x1);
static const System::Int8 SQL_SS_DELETIONS = System::Int8(0x2);
static const System::Int8 SQL_SS_UPDATES = System::Int8(0x4);
static const System::Int8 SQL_CV_CREATE_VIEW = System::Int8(0x1);
static const System::Int8 SQL_CV_CHECK_OPTION = System::Int8(0x2);
static const System::Int8 SQL_CV_CASCADED = System::Int8(0x4);
static const System::Int8 SQL_CV_LOCAL = System::Int8(0x8);
static const System::Int8 SQL_LCK_NO_CHANGE = System::Int8(0x1);
static const System::Int8 SQL_LCK_EXCLUSIVE = System::Int8(0x2);
static const System::Int8 SQL_LCK_UNLOCK = System::Int8(0x4);
static const System::Int8 SQL_POS_POSITION = System::Int8(0x1);
static const System::Int8 SQL_POS_REFRESH = System::Int8(0x2);
static const System::Int8 SQL_POS_UPDATE = System::Int8(0x4);
static const System::Int8 SQL_POS_DELETE = System::Int8(0x8);
static const System::Int8 SQL_POS_ADD = System::Int8(0x10);
static const System::Int8 SQL_QL_START = System::Int8(0x1);
static const System::Int8 SQL_QL_END = System::Int8(0x2);
static const System::Int8 SQL_AF_AVG = System::Int8(0x1);
static const System::Int8 SQL_AF_COUNT = System::Int8(0x2);
static const System::Int8 SQL_AF_MAX = System::Int8(0x4);
static const System::Int8 SQL_AF_MIN = System::Int8(0x8);
static const System::Int8 SQL_AF_SUM = System::Int8(0x10);
static const System::Int8 SQL_AF_DISTINCT = System::Int8(0x20);
static const System::Int8 SQL_AF_ALL = System::Int8(0x40);
static const System::Int8 SQL_SC_SQL92_ENTRY = System::Int8(0x1);
static const System::Int8 SQL_SC_FIPS127_2_TRANSITIONAL = System::Int8(0x2);
static const System::Int8 SQL_SC_SQL92_INTERMEDIATE = System::Int8(0x4);
static const System::Int8 SQL_SC_SQL92_FULL = System::Int8(0x8);
static const System::Int8 SQL_DL_SQL92_DATE = System::Int8(0x1);
static const System::Int8 SQL_DL_SQL92_TIME = System::Int8(0x2);
static const System::Int8 SQL_DL_SQL92_TIMESTAMP = System::Int8(0x4);
static const System::Int8 SQL_DL_SQL92_INTERVAL_YEAR = System::Int8(0x8);
static const System::Int8 SQL_DL_SQL92_INTERVAL_MONTH = System::Int8(0x10);
static const System::Int8 SQL_DL_SQL92_INTERVAL_DAY = System::Int8(0x20);
static const System::Int8 SQL_DL_SQL92_INTERVAL_HOUR = System::Int8(0x40);
static const System::Byte SQL_DL_SQL92_INTERVAL_MINUTE = System::Byte(0x80);
static const System::Word SQL_DL_SQL92_INTERVAL_SECOND = System::Word(0x100);
static const System::Word SQL_DL_SQL92_INTERVAL_YEAR_TO_MONTH = System::Word(0x200);
static const System::Word SQL_DL_SQL92_INTERVAL_DAY_TO_HOUR = System::Word(0x400);
static const System::Word SQL_DL_SQL92_INTERVAL_DAY_TO_MINUTE = System::Word(0x800);
static const System::Word SQL_DL_SQL92_INTERVAL_DAY_TO_SECOND = System::Word(0x1000);
static const System::Word SQL_DL_SQL92_INTERVAL_HOUR_TO_MINUTE = System::Word(0x2000);
static const System::Word SQL_DL_SQL92_INTERVAL_HOUR_TO_SECOND = System::Word(0x4000);
static const System::Word SQL_DL_SQL92_INTERVAL_MINUTE_TO_SECOND = System::Word(0x8000);
static const System::Int8 SQL_CL_START = System::Int8(0x1);
static const System::Int8 SQL_CL_END = System::Int8(0x2);
static const System::Int8 SQL_BRC_PROCEDURES = System::Int8(0x1);
static const System::Int8 SQL_BRC_EXPLICIT = System::Int8(0x2);
static const System::Int8 SQL_BRC_ROLLED_UP = System::Int8(0x4);
static const System::Int8 SQL_BS_SELECT_EXPLICIT = System::Int8(0x1);
static const System::Int8 SQL_BS_ROW_COUNT_EXPLICIT = System::Int8(0x2);
static const System::Int8 SQL_BS_SELECT_PROC = System::Int8(0x4);
static const System::Int8 SQL_BS_ROW_COUNT_PROC = System::Int8(0x8);
static const System::Int8 SQL_PARC_BATCH = System::Int8(0x1);
static const System::Int8 SQL_PARC_NO_BATCH = System::Int8(0x2);
static const System::Int8 SQL_PAS_BATCH = System::Int8(0x1);
static const System::Int8 SQL_PAS_NO_BATCH = System::Int8(0x2);
static const System::Int8 SQL_PAS_NO_SELECT = System::Int8(0x3);
static const System::Int8 SQL_IK_NONE = System::Int8(0x0);
static const System::Int8 SQL_IK_ASC = System::Int8(0x1);
static const System::Int8 SQL_IK_DESC = System::Int8(0x2);
static const System::Int8 SQL_IK_ALL = System::Int8(0x3);
static const System::Int8 SQL_ISV_ASSERTIONS = System::Int8(0x1);
static const System::Int8 SQL_ISV_CHARACTER_SETS = System::Int8(0x2);
static const System::Int8 SQL_ISV_CHECK_CONSTRAINTS = System::Int8(0x4);
static const System::Int8 SQL_ISV_COLLATIONS = System::Int8(0x8);
static const System::Int8 SQL_ISV_COLUMN_DOMAIN_USAGE = System::Int8(0x10);
static const System::Int8 SQL_ISV_COLUMN_PRIVILEGES = System::Int8(0x20);
static const System::Int8 SQL_ISV_COLUMNS = System::Int8(0x40);
static const System::Byte SQL_ISV_CONSTRAINT_COLUMN_USAGE = System::Byte(0x80);
static const System::Word SQL_ISV_CONSTRAINT_TABLE_USAGE = System::Word(0x100);
static const System::Word SQL_ISV_DOMAIN_CONSTRAINTS = System::Word(0x200);
static const System::Word SQL_ISV_DOMAINS = System::Word(0x400);
static const System::Word SQL_ISV_KEY_COLUMN_USAGE = System::Word(0x800);
static const System::Word SQL_ISV_REFERENTIAL_CONSTRAINTS = System::Word(0x1000);
static const System::Word SQL_ISV_SCHEMATA = System::Word(0x2000);
static const System::Word SQL_ISV_SQL_LANGUAGES = System::Word(0x4000);
static const System::Word SQL_ISV_TABLE_CONSTRAINTS = System::Word(0x8000);
static const int SQL_ISV_TABLE_PRIVILEGES = int(0x10000);
static const int SQL_ISV_TABLES = int(0x20000);
static const int SQL_ISV_TRANSLATIONS = int(0x40000);
static const int SQL_ISV_USAGE_PRIVILEGES = int(0x80000);
static const int SQL_ISV_VIEW_COLUMN_USAGE = int(0x100000);
static const int SQL_ISV_VIEW_TABLE_USAGE = int(0x200000);
static const int SQL_ISV_VIEWS = int(0x400000);
static const System::Int8 SQL_AD_CONSTRAINT_NAME_DEFINITION = System::Int8(0x1);
static const System::Int8 SQL_AD_ADD_DOMAIN_CONSTRAINT = System::Int8(0x2);
static const System::Int8 SQL_AD_DROP_DOMAIN_CONSTRAINT = System::Int8(0x4);
static const System::Int8 SQL_AD_ADD_DOMAIN_DEFAULT = System::Int8(0x8);
static const System::Int8 SQL_AD_DROP_DOMAIN_DEFAULT = System::Int8(0x10);
static const System::Int8 SQL_AD_ADD_CONSTRAINT_INITIALLY_DEFERRED = System::Int8(0x20);
static const System::Int8 SQL_AD_ADD_CONSTRAINT_INITIALLY_IMMEDIATE = System::Int8(0x40);
static const System::Byte SQL_AD_ADD_CONSTRAINT_DEFERRABLE = System::Byte(0x80);
static const System::Word SQL_AD_ADD_CONSTRAINT_NON_DEFERRABLE = System::Word(0x100);
static const System::Int8 SQL_CS_CREATE_SCHEMA = System::Int8(0x1);
static const System::Int8 SQL_CS_AUTHORIZATION = System::Int8(0x2);
static const System::Int8 SQL_CS_DEFAULT_CHARACTER_SET = System::Int8(0x4);
static const System::Int8 SQL_CTR_CREATE_TRANSLATION = System::Int8(0x1);
static const System::Int8 SQL_CA_CREATE_ASSERTION = System::Int8(0x1);
static const System::Int8 SQL_CA_CONSTRAINT_INITIALLY_DEFERRED = System::Int8(0x10);
static const System::Int8 SQL_CA_CONSTRAINT_INITIALLY_IMMEDIATE = System::Int8(0x20);
static const System::Int8 SQL_CA_CONSTRAINT_DEFERRABLE = System::Int8(0x40);
static const System::Byte SQL_CA_CONSTRAINT_NON_DEFERRABLE = System::Byte(0x80);
static const System::Int8 SQL_CCS_CREATE_CHARACTER_SET = System::Int8(0x1);
static const System::Int8 SQL_CCS_COLLATE_CLAUSE = System::Int8(0x2);
static const System::Int8 SQL_CCS_LIMITED_COLLATION = System::Int8(0x4);
static const System::Int8 SQL_CCOL_CREATE_COLLATION = System::Int8(0x1);
static const System::Int8 SQL_CDO_CREATE_DOMAIN = System::Int8(0x1);
static const System::Int8 SQL_CDO_DEFAULT = System::Int8(0x2);
static const System::Int8 SQL_CDO_CONSTRAINT = System::Int8(0x4);
static const System::Int8 SQL_CDO_COLLATION = System::Int8(0x8);
static const System::Int8 SQL_CDO_CONSTRAINT_NAME_DEFINITION = System::Int8(0x10);
static const System::Int8 SQL_CDO_CONSTRAINT_INITIALLY_DEFERRED = System::Int8(0x20);
static const System::Int8 SQL_CDO_CONSTRAINT_INITIALLY_IMMEDIATE = System::Int8(0x40);
static const System::Byte SQL_CDO_CONSTRAINT_DEFERRABLE = System::Byte(0x80);
static const System::Word SQL_CDO_CONSTRAINT_NON_DEFERRABLE = System::Word(0x100);
static const System::Int8 SQL_CT_CREATE_TABLE = System::Int8(0x1);
static const System::Int8 SQL_CT_COMMIT_PRESERVE = System::Int8(0x2);
static const System::Int8 SQL_CT_COMMIT_DELETE = System::Int8(0x4);
static const System::Int8 SQL_CT_GLOBAL_TEMPORARY = System::Int8(0x8);
static const System::Int8 SQL_CT_LOCAL_TEMPORARY = System::Int8(0x10);
static const System::Int8 SQL_CT_CONSTRAINT_INITIALLY_DEFERRED = System::Int8(0x20);
static const System::Int8 SQL_CT_CONSTRAINT_INITIALLY_IMMEDIATE = System::Int8(0x40);
static const System::Byte SQL_CT_CONSTRAINT_DEFERRABLE = System::Byte(0x80);
static const System::Word SQL_CT_CONSTRAINT_NON_DEFERRABLE = System::Word(0x100);
static const System::Word SQL_CT_COLUMN_CONSTRAINT = System::Word(0x200);
static const System::Word SQL_CT_COLUMN_DEFAULT = System::Word(0x400);
static const System::Word SQL_CT_COLUMN_COLLATION = System::Word(0x800);
static const System::Word SQL_CT_TABLE_CONSTRAINT = System::Word(0x1000);
static const System::Word SQL_CT_CONSTRAINT_NAME_DEFINITION = System::Word(0x2000);
static const System::Int8 SQL_DI_CREATE_INDEX = System::Int8(0x1);
static const System::Int8 SQL_DI_DROP_INDEX = System::Int8(0x2);
static const System::Int8 SQL_DC_DROP_COLLATION = System::Int8(0x1);
static const System::Int8 SQL_DD_DROP_DOMAIN = System::Int8(0x1);
static const System::Int8 SQL_DD_RESTRICT = System::Int8(0x2);
static const System::Int8 SQL_DD_CASCADE = System::Int8(0x4);
static const System::Int8 SQL_DS_DROP_SCHEMA = System::Int8(0x1);
static const System::Int8 SQL_DS_RESTRICT = System::Int8(0x2);
static const System::Int8 SQL_DS_CASCADE = System::Int8(0x4);
static const System::Int8 SQL_DCS_DROP_CHARACTER_SET = System::Int8(0x1);
static const System::Int8 SQL_DA_DROP_ASSERTION = System::Int8(0x1);
static const System::Int8 SQL_DT_DROP_TABLE = System::Int8(0x1);
static const System::Int8 SQL_DT_RESTRICT = System::Int8(0x2);
static const System::Int8 SQL_DT_CASCADE = System::Int8(0x4);
static const System::Int8 SQL_DTR_DROP_TRANSLATION = System::Int8(0x1);
static const System::Int8 SQL_DV_DROP_VIEW = System::Int8(0x1);
static const System::Int8 SQL_DV_RESTRICT = System::Int8(0x2);
static const System::Int8 SQL_DV_CASCADE = System::Int8(0x4);
static const System::Int8 SQL_IS_INSERT_LITERALS = System::Int8(0x1);
static const System::Int8 SQL_IS_INSERT_SEARCHED = System::Int8(0x2);
static const System::Int8 SQL_IS_SELECT_INTO = System::Int8(0x4);
#ifndef __x86_64__
static const int SQL_OIC_CORE = int(1);
static const int SQL_OIC_LEVEL1 = int(2);
static const int SQL_OIC_LEVEL2 = int(3);
#else /* __x86_64__ */
static const long SQL_OIC_CORE = 1LL;
static const long SQL_OIC_LEVEL1 = 2LL;
static const long SQL_OIC_LEVEL2 = 3LL;
#endif /* __x86_64__ */
static const System::Int8 SQL_SFKD_CASCADE = System::Int8(0x1);
static const System::Int8 SQL_SFKD_NO_ACTION = System::Int8(0x2);
static const System::Int8 SQL_SFKD_SET_DEFAULT = System::Int8(0x4);
static const System::Int8 SQL_SFKD_SET_NULL = System::Int8(0x8);
static const System::Int8 SQL_SFKU_CASCADE = System::Int8(0x1);
static const System::Int8 SQL_SFKU_NO_ACTION = System::Int8(0x2);
static const System::Int8 SQL_SFKU_SET_DEFAULT = System::Int8(0x4);
static const System::Int8 SQL_SFKU_SET_NULL = System::Int8(0x8);
static const System::Int8 SQL_SG_USAGE_ON_DOMAIN = System::Int8(0x1);
static const System::Int8 SQL_SG_USAGE_ON_CHARACTER_SET = System::Int8(0x2);
static const System::Int8 SQL_SG_USAGE_ON_COLLATION = System::Int8(0x4);
static const System::Int8 SQL_SG_USAGE_ON_TRANSLATION = System::Int8(0x8);
static const System::Int8 SQL_SG_WITH_GRANT_OPTION = System::Int8(0x10);
static const System::Int8 SQL_SG_DELETE_TABLE = System::Int8(0x20);
static const System::Int8 SQL_SG_INSERT_TABLE = System::Int8(0x40);
static const System::Byte SQL_SG_INSERT_COLUMN = System::Byte(0x80);
static const System::Word SQL_SG_REFERENCES_TABLE = System::Word(0x100);
static const System::Word SQL_SG_REFERENCES_COLUMN = System::Word(0x200);
static const System::Word SQL_SG_SELECT_TABLE = System::Word(0x400);
static const System::Word SQL_SG_UPDATE_TABLE = System::Word(0x800);
static const System::Word SQL_SG_UPDATE_COLUMN = System::Word(0x1000);
static const System::Int8 SQL_SP_EXISTS = System::Int8(0x1);
static const System::Int8 SQL_SP_ISNOTNULL = System::Int8(0x2);
static const System::Int8 SQL_SP_ISNULL = System::Int8(0x4);
static const System::Int8 SQL_SP_MATCH_FULL = System::Int8(0x8);
static const System::Int8 SQL_SP_MATCH_PARTIAL = System::Int8(0x10);
static const System::Int8 SQL_SP_MATCH_UNIQUE_FULL = System::Int8(0x20);
static const System::Int8 SQL_SP_MATCH_UNIQUE_PARTIAL = System::Int8(0x40);
static const System::Byte SQL_SP_OVERLAPS = System::Byte(0x80);
static const System::Word SQL_SP_UNIQUE = System::Word(0x100);
static const System::Word SQL_SP_LIKE = System::Word(0x200);
static const System::Word SQL_SP_IN = System::Word(0x400);
static const System::Word SQL_SP_BETWEEN = System::Word(0x800);
static const System::Word SQL_SP_COMPARISON = System::Word(0x1000);
static const System::Word SQL_SP_QUANTIFIED_COMPARISON = System::Word(0x2000);
static const System::Int8 SQL_SRJO_CORRESPONDING_CLAUSE = System::Int8(0x1);
static const System::Int8 SQL_SRJO_CROSS_JOIN = System::Int8(0x2);
static const System::Int8 SQL_SRJO_EXCEPT_JOIN = System::Int8(0x4);
static const System::Int8 SQL_SRJO_FULL_OUTER_JOIN = System::Int8(0x8);
static const System::Int8 SQL_SRJO_INNER_JOIN = System::Int8(0x10);
static const System::Int8 SQL_SRJO_INTERSECT_JOIN = System::Int8(0x20);
static const System::Int8 SQL_SRJO_LEFT_OUTER_JOIN = System::Int8(0x40);
static const System::Byte SQL_SRJO_NATURAL_JOIN = System::Byte(0x80);
static const System::Word SQL_SRJO_RIGHT_OUTER_JOIN = System::Word(0x100);
static const System::Word SQL_SRJO_UNION_JOIN = System::Word(0x200);
static const System::Int8 SQL_SR_USAGE_ON_DOMAIN = System::Int8(0x1);
static const System::Int8 SQL_SR_USAGE_ON_CHARACTER_SET = System::Int8(0x2);
static const System::Int8 SQL_SR_USAGE_ON_COLLATION = System::Int8(0x4);
static const System::Int8 SQL_SR_USAGE_ON_TRANSLATION = System::Int8(0x8);
static const System::Int8 SQL_SR_GRANT_OPTION_FOR = System::Int8(0x10);
static const System::Int8 SQL_SR_CASCADE = System::Int8(0x20);
static const System::Int8 SQL_SR_RESTRICT = System::Int8(0x40);
static const System::Byte SQL_SR_DELETE_TABLE = System::Byte(0x80);
static const System::Word SQL_SR_INSERT_TABLE = System::Word(0x100);
static const System::Word SQL_SR_INSERT_COLUMN = System::Word(0x200);
static const System::Word SQL_SR_REFERENCES_TABLE = System::Word(0x400);
static const System::Word SQL_SR_REFERENCES_COLUMN = System::Word(0x800);
static const System::Word SQL_SR_SELECT_TABLE = System::Word(0x1000);
static const System::Word SQL_SR_UPDATE_TABLE = System::Word(0x2000);
static const System::Word SQL_SR_UPDATE_COLUMN = System::Word(0x4000);
static const System::Int8 SQL_SRVC_VALUE_EXPRESSION = System::Int8(0x1);
static const System::Int8 SQL_SRVC_NULL = System::Int8(0x2);
static const System::Int8 SQL_SRVC_DEFAULT = System::Int8(0x4);
static const System::Int8 SQL_SRVC_ROW_SUBQUERY = System::Int8(0x8);
static const System::Int8 SQL_SVE_CASE = System::Int8(0x1);
static const System::Int8 SQL_SVE_CAST = System::Int8(0x2);
static const System::Int8 SQL_SVE_COALESCE = System::Int8(0x4);
static const System::Int8 SQL_SVE_NULLIF = System::Int8(0x8);
static const System::Int8 SQL_SCC_XOPEN_CLI_VERSION1 = System::Int8(0x1);
static const System::Int8 SQL_SCC_ISO92_CLI = System::Int8(0x2);
static const System::Int8 SQL_US_UNION = System::Int8(0x1);
static const System::Int8 SQL_US_UNION_ALL = System::Int8(0x2);
static const System::Int8 SQL_DTC_ENLIST_EXPENSIVE = System::Int8(0x1);
static const System::Int8 SQL_DTC_UNENLIST_EXPENSIVE = System::Int8(0x2);
static const System::Int8 SQL_ASYNC_DBC_NOT_CAPABLE = System::Int8(0x0);
static const System::Int8 SQL_ASYNC_DBC_CAPABLE = System::Int8(0x1);
static const System::Int8 SQL_FETCH_FIRST_USER = System::Int8(0x1f);
static const System::Int8 SQL_FETCH_FIRST_SYSTEM = System::Int8(0x20);
static const System::Int8 SQL_ENTIRE_ROWSET = System::Int8(0x0);
static const System::Int8 SQL_POSITION = System::Int8(0x0);
static const System::Int8 SQL_REFRESH = System::Int8(0x1);
static const System::Int8 SQL_UPDATE = System::Int8(0x2);
static const System::Int8 SQL_DELETE = System::Int8(0x3);
static const System::Int8 SQL_ADD = System::Int8(0x4);
static const System::Int8 SQL_SETPOS_MAX_OPTION_VALUE = System::Int8(0x4);
static const System::Int8 SQL_UPDATE_BY_BOOKMARK = System::Int8(0x5);
static const System::Int8 SQL_DELETE_BY_BOOKMARK = System::Int8(0x6);
static const System::Int8 SQL_FETCH_BY_BOOKMARK = System::Int8(0x7);
static const System::Int8 SQL_LOCK_NO_CHANGE = System::Int8(0x0);
static const System::Int8 SQL_LOCK_EXCLUSIVE = System::Int8(0x1);
static const System::Int8 SQL_LOCK_UNLOCK = System::Int8(0x2);
static const System::Int8 SQL_SETPOS_MAX_LOCK_VALUE = System::Int8(0x2);
static const System::Int8 SQL_BEST_ROWID = System::Int8(0x1);
static const System::Int8 SQL_ROWVER = System::Int8(0x2);
static const System::Int8 SQL_PC_NOT_PSEUDO = System::Int8(0x1);
static const System::Int8 SQL_QUICK = System::Int8(0x0);
static const System::Int8 SQL_ENSURE = System::Int8(0x1);
static const System::Int8 SQL_TABLE_STAT = System::Int8(0x0);
static const System::WideChar SQL_ALL_CATALOGS = (System::WideChar)(0x25);
static const System::WideChar SQL_ALL_SCHEMAS = (System::WideChar)(0x25);
static const System::WideChar SQL_ALL_TABLE_TYPES = (System::WideChar)(0x25);
static const System::Int8 SQL_DRIVER_NOPROMPT = System::Int8(0x0);
static const System::Int8 SQL_DRIVER_COMPLETE = System::Int8(0x1);
static const System::Int8 SQL_DRIVER_PROMPT = System::Int8(0x2);
static const System::Int8 SQL_DRIVER_COMPLETE_REQUIRED = System::Int8(0x3);
static const System::Int8 SQL_FETCH_BOOKMARK = System::Int8(0x8);
static const System::Int8 SQL_ROW_SUCCESS = System::Int8(0x0);
static const System::Int8 SQL_ROW_DELETED = System::Int8(0x1);
static const System::Int8 SQL_ROW_UPDATED = System::Int8(0x2);
static const System::Int8 SQL_ROW_NOROW = System::Int8(0x3);
static const System::Int8 SQL_ROW_ADDED = System::Int8(0x4);
static const System::Int8 SQL_ROW_ERROR = System::Int8(0x5);
static const System::Int8 SQL_ROW_SUCCESS_WITH_INFO = System::Int8(0x6);
static const System::Int8 SQL_ROW_PROCEED = System::Int8(0x0);
static const System::Int8 SQL_ROW_IGNORE = System::Int8(0x1);
static const System::Int8 SQL_PARAM_SUCCESS = System::Int8(0x0);
static const System::Int8 SQL_PARAM_SUCCESS_WITH_INFO = System::Int8(0x6);
static const System::Int8 SQL_PARAM_ERROR = System::Int8(0x5);
static const System::Int8 SQL_PARAM_UNUSED = System::Int8(0x7);
static const System::Int8 SQL_PARAM_DIAG_UNAVAILABLE = System::Int8(0x1);
static const System::Int8 SQL_PARAM_PROCEED = System::Int8(0x0);
static const System::Int8 SQL_PARAM_IGNORE = System::Int8(0x1);
static const System::Int8 SQL_CASCADE = System::Int8(0x0);
static const System::Int8 SQL_RESTRICT = System::Int8(0x1);
static const System::Int8 SQL_SET_NULL = System::Int8(0x2);
static const System::Int8 SQL_NO_ACTION = System::Int8(0x3);
static const System::Int8 SQL_SET_DEFAULT = System::Int8(0x4);
static const System::Int8 SQL_INITIALLY_DEFERRED = System::Int8(0x5);
static const System::Int8 SQL_INITIALLY_IMMEDIATE = System::Int8(0x6);
static const System::Int8 SQL_NOT_DEFERRABLE = System::Int8(0x7);
static const System::Int8 SQL_PT_UNKNOWN = System::Int8(0x0);
static const System::Int8 SQL_PT_PROCEDURE = System::Int8(0x1);
static const System::Int8 SQL_PT_FUNCTION = System::Int8(0x2);
static const System::Int8 SQL_YEAR = System::Int8(0x1);
static const System::Int8 SQL_MONTH = System::Int8(0x2);
static const System::Int8 SQL_DAY = System::Int8(0x3);
static const System::Int8 SQL_HOUR = System::Int8(0x4);
static const System::Int8 SQL_MINUTE = System::Int8(0x5);
static const System::Int8 SQL_SECOND = System::Int8(0x6);
static const System::Int8 SQL_YEAR_TO_MONTH = System::Int8(0x7);
static const System::Int8 SQL_DAY_TO_HOUR = System::Int8(0x8);
static const System::Int8 SQL_DAY_TO_MINUTE = System::Int8(0x9);
static const System::Int8 SQL_DAY_TO_SECOND = System::Int8(0xa);
static const System::Int8 SQL_HOUR_TO_MINUTE = System::Int8(0xb);
static const System::Int8 SQL_HOUR_TO_SECOND = System::Int8(0xc);
static const System::Int8 SQL_MINUTE_TO_SECOND = System::Int8(0xd);
static const System::Int8 SQL_DATABASE_NAME = System::Int8(0x10);
static const System::Int8 SQL_FD_FETCH_PREV = System::Int8(0x8);
static const System::Int8 SQL_FETCH_PREV = System::Int8(0x4);
static const System::Int8 SQL_CONCUR_TIMESTAMP = System::Int8(0x3);
static const System::Int8 SQL_SCCO_OPT_TIMESTAMP = System::Int8(0x4);
static const System::Int8 SQL_CC_DELETE = System::Int8(0x0);
static const System::Int8 SQL_CR_DELETE = System::Int8(0x0);
static const System::Int8 SQL_CC_CLOSE = System::Int8(0x1);
static const System::Int8 SQL_CR_CLOSE = System::Int8(0x1);
static const System::Int8 SQL_CC_PRESERVE = System::Int8(0x2);
static const System::Int8 SQL_CR_PRESERVE = System::Int8(0x2);
static const System::Int8 SQL_FETCH_RESUME = System::Int8(0x7);
static const System::Int8 SQL_SCROLL_FORWARD_ONLY = System::Int8(0x0);
static const System::Int8 SQL_SCROLL_KEYSET_DRIVEN = System::Int8(-1);
static const System::Int8 SQL_SCROLL_DYNAMIC = System::Int8(-2);
static const System::Int8 SQL_SCROLL_STATIC = System::Int8(-3);
static const System::Int8 ODBC_ADD_DSN = System::Int8(0x1);
static const System::Int8 ODBC_CONFIG_DSN = System::Int8(0x2);
static const System::Int8 ODBC_REMOVE_DSN = System::Int8(0x3);
static const System::Int8 ODBC_ADD_SYS_DSN = System::Int8(0x4);
static const System::Int8 ODBC_CONFIG_SYS_DSN = System::Int8(0x5);
static const System::Int8 ODBC_REMOVE_SYS_DSN = System::Int8(0x6);
static const System::Int8 ODBC_REMOVE_DEFAULT_DSN = System::Int8(0x7);
static const System::Int8 ODBC_INSTALL_INQUIRY = System::Int8(0x1);
static const System::Int8 ODBC_INSTALL_COMPLETE = System::Int8(0x2);
static const System::Int8 ODBC_INSTALL_DRIVER = System::Int8(0x1);
static const System::Int8 ODBC_REMOVE_DRIVER = System::Int8(0x2);
static const System::Int8 ODBC_CONFIG_DRIVER = System::Int8(0x3);
static const System::Int8 ODBC_CONFIG_DRIVER_MAX = System::Int8(0x64);
static const System::Int8 ODBC_BOTH_DSN = System::Int8(0x0);
static const System::Int8 ODBC_USER_DSN = System::Int8(0x1);
static const System::Int8 ODBC_SYSTEM_DSN = System::Int8(0x2);
static const System::Int8 ODBC_ERROR_GENERAL_ERR = System::Int8(0x1);
static const System::Int8 ODBC_ERROR_INVALID_BUFF_LEN = System::Int8(0x2);
static const System::Int8 ODBC_ERROR_INVALID_HWND = System::Int8(0x3);
static const System::Int8 ODBC_ERROR_INVALID_STR = System::Int8(0x4);
static const System::Int8 ODBC_ERROR_INVALID_REQUEST_TYPE = System::Int8(0x5);
static const System::Int8 ODBC_ERROR_COMPONENT_NOT_FOUND = System::Int8(0x6);
static const System::Int8 ODBC_ERROR_INVALID_NAME = System::Int8(0x7);
static const System::Int8 ODBC_ERROR_INVALID_KEYWORD_VALUE = System::Int8(0x8);
static const System::Int8 ODBC_ERROR_INVALID_DSN = System::Int8(0x9);
static const System::Int8 ODBC_ERROR_INVALID_INF = System::Int8(0xa);
static const System::Int8 ODBC_ERROR_REQUEST_FAILED = System::Int8(0xb);
static const System::Int8 ODBC_ERROR_INVALID_PATH = System::Int8(0xc);
static const System::Int8 ODBC_ERROR_LOAD_LIB_FAILED = System::Int8(0xd);
static const System::Int8 ODBC_ERROR_INVALID_PARAM_SEQUENCE = System::Int8(0xe);
static const System::Int8 ODBC_ERROR_INVALID_LOG_FILE = System::Int8(0xf);
static const System::Int8 ODBC_ERROR_USER_CANCELED = System::Int8(0x10);
static const System::Int8 ODBC_ERROR_USAGE_UPDATE_FAILED = System::Int8(0x11);
static const System::Int8 ODBC_ERROR_CREATE_DSN_FAILED = System::Int8(0x12);
static const System::Int8 ODBC_ERROR_WRITING_SYSINFO_FAILED = System::Int8(0x13);
static const System::Int8 ODBC_ERROR_REMOVE_DSN_FAILED = System::Int8(0x14);
static const System::Int8 ODBC_ERROR_OUT_OF_MEM = System::Int8(0x15);
static const System::Int8 ODBC_ERROR_OUTPUT_STRING_TRUNCATED = System::Int8(0x16);
static const System::Int8 ODBC_ERROR_NOTRANINFO = System::Int8(0x17);
static const System::Int8 ODBC_ERROR_MAX = System::Int8(0x17);
static const short SQL_SS_VARIANT = short(-150);
static const short SQL_SS_UDT = short(-151);
static const short SQL_SS_XML = short(-152);
static const short SQL_SS_TABLE = short(-153);
static const short SQL_SS_TIME2 = short(-154);
static const short SQL_SS_TIMESTAMPOFFSET = short(-155);
static const System::Word SQL_COPT_SS_BASE = System::Word(0x4b0);
static const System::Word SQL_COPT_SS_REMOTE_PWD = System::Word(0x4b1);
static const System::Word SQL_COPT_SS_USE_PROC_FOR_PREP = System::Word(0x4b2);
static const System::Word SQL_COPT_SS_INTEGRATED_SECURITY = System::Word(0x4b3);
static const System::Word SQL_COPT_SS_PRESERVE_CURSORS = System::Word(0x4b4);
static const System::Word SQL_COPT_SS_USER_DATA = System::Word(0x4b5);
static const System::Word SQL_COPT_SS_ENLIST_IN_DTC = System::Word(0x4b7);
static const System::Word SQL_COPT_SS_ENLIST_IN_XA = System::Word(0x4b8);
static const System::Word SQL_COPT_SS_FALLBACK_CONNECT = System::Word(0x4ba);
static const System::Word SQL_COPT_SS_PERF_DATA = System::Word(0x4bb);
static const System::Word SQL_COPT_SS_PERF_DATA_LOG = System::Word(0x4bc);
static const System::Word SQL_COPT_SS_PERF_QUERY_INTERVAL = System::Word(0x4bd);
static const System::Word SQL_COPT_SS_PERF_QUERY_LOG = System::Word(0x4be);
static const System::Word SQL_COPT_SS_PERF_QUERY = System::Word(0x4bf);
static const System::Word SQL_COPT_SS_PERF_DATA_LOG_NOW = System::Word(0x4c0);
static const System::Word SQL_COPT_SS_QUOTED_IDENT = System::Word(0x4c1);
static const System::Word SQL_COPT_SS_ANSI_NPW = System::Word(0x4c2);
static const System::Word SQL_COPT_SS_BCP = System::Word(0x4c3);
static const System::Word SQL_COPT_SS_TRANSLATE = System::Word(0x4c4);
static const System::Word SQL_COPT_SS_ATTACHDBFILENAME = System::Word(0x4c5);
static const System::Word SQL_COPT_SS_CONCAT_NULL = System::Word(0x4c6);
static const System::Word SQL_COPT_SS_ENCRYPT = System::Word(0x4c7);
static const System::Word SQL_COPT_SS_MARS_ENABLED = System::Word(0x4c8);
static const System::Word SQL_COPT_SS_FAILOVER_PARTNER = System::Word(0x4c9);
static const System::Word SQL_COPT_SS_OLDPWD = System::Word(0x4ca);
static const System::Word SQL_COPT_SS_TXN_ISOLATION = System::Word(0x4cb);
static const System::Word SQL_COPT_SS_TRUST_SERVER_CERTIFICATE = System::Word(0x4cc);
static const System::Word SQL_COPT_SS_SERVER_SPN = System::Word(0x4cd);
static const System::Word SQL_COPT_SS_FAILOVER_PARTNER_SPN = System::Word(0x4ce);
static const System::Word SQL_COPT_SS_INTEGRATED_AUTHENTICATION_METHOD = System::Word(0x4cf);
static const System::Word SQL_COPT_SS_MUTUALLY_AUTHENTICATED = System::Word(0x4d0);
static const System::Word SQL_COPT_SS_MAX_USED = System::Word(0x4d0);
static const System::Word SQL_SOPT_SS_BASE = System::Word(0x4c9);
static const System::Word SQL_SOPT_SS_TEXTPTR_LOGGING = System::Word(0x4c9);
static const System::Word SQL_SOPT_SS_CURRENT_COMMAND = System::Word(0x4ca);
static const System::Word SQL_SOPT_SS_HIDDEN_COLUMNS = System::Word(0x4cb);
static const System::Word SQL_SOPT_SS_NOBROWSETABLE = System::Word(0x4cc);
static const System::Word SQL_SOPT_SS_REGIONALIZE = System::Word(0x4cd);
static const System::Word SQL_SOPT_SS_CURSOR_OPTIONS = System::Word(0x4ce);
static const System::Word SQL_SOPT_SS_NOCOUNT_STATUS = System::Word(0x4cf);
static const System::Word SQL_SOPT_SS_DEFER_PREPARE = System::Word(0x4d0);
static const System::Word SQL_SOPT_SS_QUERYNOTIFICATION_TIMEOUT = System::Word(0x4d1);
static const System::Word SQL_SOPT_SS_QUERYNOTIFICATION_MSGTEXT = System::Word(0x4d2);
static const System::Word SQL_SOPT_SS_QUERYNOTIFICATION_OPTIONS = System::Word(0x4d3);
static const System::Word SQL_SOPT_SS_PARAM_FOCUS = System::Word(0x4d4);
static const System::Word SQL_SOPT_SS_NAME_SCOPE = System::Word(0x4d5);
static const System::Word SQL_SOPT_SS_MAX_USED = System::Word(0x4d5);
static const System::Word SQL_COPT_SS_BASE_EX = System::Word(0x4d8);
static const System::Word SQL_COPT_SS_BROWSE_CONNECT = System::Word(0x4d9);
static const System::Word SQL_COPT_SS_BROWSE_SERVER = System::Word(0x4da);
static const System::Word SQL_COPT_SS_WARN_ON_CP_ERROR = System::Word(0x4db);
static const System::Word SQL_COPT_SS_CONNECTION_DEAD = System::Word(0x4dc);
static const System::Word SQL_COPT_SS_BROWSE_CACHE_DATA = System::Word(0x4dd);
static const System::Word SQL_COPT_SS_RESET_CONNECTION = System::Word(0x4de);
static const System::Word SQL_COPT_SS_EX_MAX_USED = System::Word(0x4de);
static const System::Word SQL_CA_SS_BASE = System::Word(0x4b0);
static const System::Word SQL_CA_SS_COLUMN_SSTYPE = System::Word(0x4b0);
static const System::Word SQL_CA_SS_COLUMN_UTYPE = System::Word(0x4b1);
static const System::Word SQL_CA_SS_NUM_ORDERS = System::Word(0x4b2);
static const System::Word SQL_CA_SS_COLUMN_ORDER = System::Word(0x4b3);
static const System::Word SQL_CA_SS_COLUMN_VARYLEN = System::Word(0x4b4);
static const System::Word SQL_CA_SS_NUM_COMPUTES = System::Word(0x4b5);
static const System::Word SQL_CA_SS_COMPUTE_ID = System::Word(0x4b6);
static const System::Word SQL_CA_SS_COMPUTE_BYLIST = System::Word(0x4b7);
static const System::Word SQL_CA_SS_COLUMN_ID = System::Word(0x4b8);
static const System::Word SQL_CA_SS_COLUMN_OP = System::Word(0x4b9);
static const System::Word SQL_CA_SS_COLUMN_SIZE = System::Word(0x4ba);
static const System::Word SQL_CA_SS_COLUMN_HIDDEN = System::Word(0x4bb);
static const System::Word SQL_CA_SS_COLUMN_KEY = System::Word(0x4bc);
static const System::Word SQL_CA_SS_COLUMN_COLLATION = System::Word(0x4be);
static const System::Word SQL_CA_SS_VARIANT_TYPE = System::Word(0x4bf);
static const System::Word SQL_CA_SS_VARIANT_SQL_TYPE = System::Word(0x4c0);
static const System::Word SQL_CA_SS_VARIANT_SERVER_TYPE = System::Word(0x4c1);
static const System::Word SQL_CA_SS_UDT_CATALOG_NAME = System::Word(0x4c2);
static const System::Word SQL_CA_SS_UDT_SCHEMA_NAME = System::Word(0x4c3);
static const System::Word SQL_CA_SS_UDT_TYPE_NAME = System::Word(0x4c4);
static const System::Word SQL_CA_SS_UDT_ASSEMBLY_TYPE_NAME = System::Word(0x4c5);
static const System::Word SQL_CA_SS_XML_SCHEMACOLLECTION_CATALOG_NAME = System::Word(0x4c6);
static const System::Word SQL_CA_SS_XML_SCHEMACOLLECTION_SCHEMA_NAME = System::Word(0x4c7);
static const System::Word SQL_CA_SS_XML_SCHEMACOLLECTION_NAME = System::Word(0x4c8);
static const System::Word SQL_CA_SS_CATALOG_NAME = System::Word(0x4c9);
static const System::Word SQL_CA_SS_SCHEMA_NAME = System::Word(0x4ca);
static const System::Word SQL_CA_SS_TYPE_NAME = System::Word(0x4cb);
static const System::Word SQL_CA_SS_COLUMN_COMPUTED = System::Word(0x4cd);
static const System::Word SQL_CA_SS_COLUMN_IN_UNIQUE_KEY = System::Word(0x4ce);
static const System::Word SQL_CA_SS_COLUMN_SORT_ORDER = System::Word(0x4cf);
static const System::Word SQL_CA_SS_COLUMN_SORT_ORDINAL = System::Word(0x4d0);
static const System::Word SQL_CA_SS_COLUMN_HAS_DEFAULT_VALUE = System::Word(0x4d1);
static const System::Word SQL_CA_SS_IS_COLUMN_SET = System::Word(0x4d2);
static const System::Word SQL_CA_SS_SERVER_TYPE = System::Word(0x4d3);
static const System::Word SQL_CA_SS_MAX_USED = System::Word(0x4d4);
static const System::Int8 SQL_CURSOR_FAST_FORWARD_ONLY = System::Int8(0x8);
static const System::Int8 SQL_UP_OFF = System::Int8(0x0);
static const System::Int8 SQL_UP_ON = System::Int8(0x1);
static const System::Int8 SQL_UP_ON_DROP = System::Int8(0x2);
static const System::Int8 SQL_UP_DEFAULT = System::Int8(0x1);
static const System::Int8 SQL_IS_OFF = System::Int8(0x0);
static const System::Int8 SQL_IS_ON = System::Int8(0x1);
static const System::Int8 SQL_IS_DEFAULT = System::Int8(0x0);
static const System::Int8 SQL_PC_OFF = System::Int8(0x0);
static const System::Int8 SQL_PC_ON = System::Int8(0x1);
static const System::Int8 SQL_PC_DEFAULT = System::Int8(0x0);
#define SQL_UD_NOTSET (void*)(0)
static const System::Int8 SQL_XL_OFF = System::Int8(0x0);
static const System::Int8 SQL_XL_ON = System::Int8(0x1);
static const System::Int8 SQL_XL_DEFAULT = System::Int8(0x1);
static const System::Int8 SQL_FB_OFF = System::Int8(0x0);
static const System::Int8 SQL_FB_ON = System::Int8(0x1);
static const System::Int8 SQL_FB_DEFAULT = System::Int8(0x0);
static const System::Int8 SQL_BCP_OFF = System::Int8(0x0);
static const System::Int8 SQL_BCP_ON = System::Int8(0x1);
static const System::Int8 SQL_BCP_DEFAULT = System::Int8(0x0);
static const System::Int8 SQL_QI_OFF = System::Int8(0x0);
static const System::Int8 SQL_QI_ON = System::Int8(0x1);
static const System::Int8 SQL_QI_DEFAULT = System::Int8(0x1);
static const System::Int8 SQL_AD_OFF = System::Int8(0x0);
static const System::Int8 SQL_AD_ON = System::Int8(0x1);
static const System::Int8 SQL_AD_DEFAULT = System::Int8(0x1);
static const System::Int8 SQL_CN_OFF = System::Int8(0x0);
static const System::Int8 SQL_CN_ON = System::Int8(0x1);
static const System::Int8 SQL_CN_DEFAULT = System::Int8(0x1);
static const System::Int8 SQL_TL_OFF = System::Int8(0x0);
static const System::Int8 SQL_TL_ON = System::Int8(0x1);
static const System::Int8 SQL_TL_DEFAULT = System::Int8(0x1);
static const System::Int8 SQL_HC_OFF = System::Int8(0x0);
static const System::Int8 SQL_HC_ON = System::Int8(0x1);
static const System::Int8 SQL_HC_DEFAULT = System::Int8(0x0);
static const System::Int8 SQL_NB_OFF = System::Int8(0x0);
static const System::Int8 SQL_NB_ON = System::Int8(0x1);
static const System::Int8 SQL_NB_DEFAULT = System::Int8(0x0);
static const System::Int8 SQL_RE_OFF = System::Int8(0x0);
static const System::Int8 SQL_RE_ON = System::Int8(0x1);
static const System::Int8 SQL_RE_DEFAULT = System::Int8(0x0);
static const System::Int8 SQL_CO_OFF = System::Int8(0x0);
static const System::Int8 SQL_CO_FFO = System::Int8(0x1);
static const System::Int8 SQL_CO_AF = System::Int8(0x2);
static const System::Int8 SQL_CO_FFO_AF = System::Int8(0x3);
static const System::Int8 SQL_CO_FIREHOSE_AF = System::Int8(0x4);
static const System::Int8 SQL_CO_DEFAULT = System::Int8(0x0);
static const System::Int8 SQL_NC_OFF = System::Int8(0x0);
static const System::Int8 SQL_NC_ON = System::Int8(0x1);
static const System::Int8 SQL_DP_OFF = System::Int8(0x0);
static const System::Int8 SQL_DP_ON = System::Int8(0x1);
static const System::Int8 SQL_SS_NAME_SCOPE_TABLE = System::Int8(0x0);
static const System::Int8 SQL_SS_NAME_SCOPE_TABLE_TYPE = System::Int8(0x1);
static const System::Int8 SQL_SS_NAME_SCOPE_EXTENDED = System::Int8(0x2);
static const System::Int8 SQL_SS_NAME_SCOPE_SPARSE_COLUMN_SET = System::Int8(0x3);
static const System::Int8 SQL_SS_NAME_SCOPE_DEFAULT = System::Int8(0x0);
static const System::Int8 SQL_EN_OFF = System::Int8(0x0);
static const System::Int8 SQL_EN_ON = System::Int8(0x1);
static const System::Int8 SQL_TRUST_SERVER_CERTIFICATE_NO = System::Int8(0x0);
static const System::Int8 SQL_TRUST_SERVER_CERTIFICATE_YES = System::Int8(0x1);
static const System::Int8 SQL_MORE_INFO_NO = System::Int8(0x0);
static const System::Int8 SQL_MORE_INFO_YES = System::Int8(0x1);
static const System::Int8 SQL_CACHE_DATA_NO = System::Int8(0x0);
static const System::Int8 SQL_CACHE_DATA_YES = System::Int8(0x1);
static const System::Int8 SQL_RESET_YES = System::Int8(0x1);
static const System::Int8 SQL_WARN_NO = System::Int8(0x0);
static const System::Int8 SQL_WARN_YES = System::Int8(0x1);
static const System::Int8 SQL_MARS_ENABLED_NO = System::Int8(0x0);
static const System::Int8 SQL_MARS_ENABLED_YES = System::Int8(0x1);
static const System::Int8 SQL_TXN_SS_SNAPSHOT = System::Int8(0x20);
static const System::Int8 SQL_SS_ORDER_UNSPECIFIED = System::Int8(0x0);
static const System::Int8 SQL_SS_DESCENDING_ORDER = System::Int8(0x1);
static const System::Int8 SQL_SS_ASCENDING_ORDER = System::Int8(0x2);
static const System::Int8 SQL_SS_ORDER_DEFAULT = System::Int8(0x0);
static const System::Int8 SQL_SS_LENGTH_UNLIMITED = System::Int8(0x0);
static const System::Int8 SQLudtBINARY = System::Int8(0x3);
static const System::Int8 SQLudtBIT = System::Int8(0x10);
static const System::Int8 SQLudtBITN = System::Int8(0x0);
static const System::Int8 SQLudtCHAR = System::Int8(0x1);
static const System::Int8 SQLudtDATETIM4 = System::Int8(0x16);
static const System::Int8 SQLudtDATETIME = System::Int8(0xc);
static const System::Int8 SQLudtDATETIMN = System::Int8(0xf);
static const System::Int8 SQLudtDECML = System::Int8(0x18);
static const System::Int8 SQLudtDECMLN = System::Int8(0x1a);
static const System::Int8 SQLudtFLT4 = System::Int8(0x17);
static const System::Int8 SQLudtFLT8 = System::Int8(0x8);
static const System::Int8 SQLudtFLTN = System::Int8(0xe);
static const System::Int8 SQLudtIMAGE = System::Int8(0x14);
static const System::Int8 SQLudtINT1 = System::Int8(0x5);
static const System::Int8 SQLudtINT2 = System::Int8(0x6);
static const System::Int8 SQLudtINT4 = System::Int8(0x7);
static const System::Int8 SQLudtINTN = System::Int8(0xd);
static const System::Int8 SQLudtMONEY = System::Int8(0xb);
static const System::Int8 SQLudtMONEY4 = System::Int8(0x15);
static const System::Int8 SQLudtMONEYN = System::Int8(0x11);
static const System::Int8 SQLudtNUM = System::Int8(0xa);
static const System::Int8 SQLudtNUMN = System::Int8(0x19);
static const System::Int8 SQLudtSYSNAME = System::Int8(0x12);
static const System::Int8 SQLudtTEXT = System::Int8(0x13);
static const System::Int8 SQLudtTIMESTAMP = System::Int8(0x50);
static const System::Int8 SQLudtUNIQUEIDENTIFIER = System::Int8(0x0);
static const System::Int8 SQLudtVARBINARY = System::Int8(0x4);
static const System::Int8 SQLudtVARCHAR = System::Int8(0x2);
static const System::Word MIN_USER_DATATYPE = System::Word(0x100);
static const System::Int8 SQLAOPSTDEV = System::Int8(0x30);
static const System::Int8 SQLAOPSTDEVP = System::Int8(0x31);
static const System::Int8 SQLAOPVAR = System::Int8(0x32);
static const System::Int8 SQLAOPVARP = System::Int8(0x33);
static const System::Int8 SQLAOPCNT = System::Int8(0x4b);
static const System::Int8 SQLAOPSUM = System::Int8(0x4d);
static const System::Int8 SQLAOPAVG = System::Int8(0x4f);
static const System::Int8 SQLAOPMIN = System::Int8(0x51);
static const System::Int8 SQLAOPMAX = System::Int8(0x52);
static const System::Int8 SQLAOPANY = System::Int8(0x53);
static const System::Int8 SQLAOPNOOP = System::Int8(0x56);
static const short SQL_DIAG_SS_BASE = short(-1150);
static const short SQL_DIAG_SS_MSGSTATE = short(-1150);
static const short SQL_DIAG_SS_SEVERITY = short(-1151);
static const short SQL_DIAG_SS_SRVNAME = short(-1152);
static const short SQL_DIAG_SS_PROCNAME = short(-1153);
static const short SQL_DIAG_SS_LINE = short(-1154);
static const System::Word SQL_ATTR_LONGDATA_COMPAT = System::Word(0x4e5);
static const System::Int8 SQL_LD_COMPAT_NO = System::Int8(0x0);
static const System::Int8 SQL_LD_COMPAT_YES = System::Int8(0x1);
static const System::Word SQL_ATTR_MAPCHAR = System::Word(0x9f2);
static const System::Int8 SQL_MAPCHAR_DEFAULT = System::Int8(0x0);
static const System::Int8 SQL_MAPCHAR_WCHAR = System::Int8(0x1);
static const System::Word SQL_ATTR_DESCRIBE_OUTPUT_LEVEL = System::Word(0x9ca);
static const System::Word SQL_ATTR_USE_TRUSTED_CONTEXT = System::Word(0xa01);
static const System::Int8 SQL_GRAPHIC = System::Int8(-95);
static const System::Int8 SQL_VARGRAPHIC = System::Int8(-96);
static const System::Int8 SQL_LONGVARGRAPHIC = System::Int8(-97);
static const System::Int8 SQL_BLOB = System::Int8(-98);
static const System::Int8 SQL_CLOB = System::Int8(-99);
static const short SQL_DBCLOB = short(-350);
static const short SQL_XML = short(-370);
static const short SQL_DECFLOAT = short(-360);
static const short SQL_DATALINK = short(-400);
static const short SQL_USER_DEFINED_TYPE = short(-450);
static const System::Word SQL_PARAMOPT_ATOMIC = System::Word(0x4ec);
static const System::Word SQL_ATTR_PARAMOPT_ATOMIC = System::Word(0x4ec);
static const System::Int8 SQL_ATOMIC_YES = System::Int8(0x1);
static const System::Int8 SQL_ATOMIC_NO = System::Int8(0x0);
static const System::Int8 SQL_ATOMIC_DEFAULT = System::Int8(0x1);
static const short SQL_REFCURSOR = short(-403);
static const System::Word SA_UNUSED_OPTION = System::Word(0x76c);
static const System::Word SA_GET_SQLCA = System::Word(0x76d);
static const System::Word SA_GET_STATEMENT_HANDLE = System::Word(0x76e);
static const System::Word SA_SQL_COLUMN_ISKEY = System::Word(0x76f);
static const System::Word SA_REGISTER_MESSAGE_CALLBACK = System::Word(0x770);
static const System::Word SA_CONVERT_TO_UNICODE = System::Word(0x771);
static const System::Word SA_GET_MESSAGE_CALLBACK_PARM = System::Word(0x772);
static const System::Word SA_USE_ISOLATION_ON_OPEN = System::Word(0x773);
static const System::Word SA_SQL_DESC_ISKEY = System::Word(0x76f);
static const System::Word SA_SQL_ATTR_TXN_ISOLATION = System::Word(0x774);
static const System::Word SA_CLIENT_API_NAME = System::Word(0x775);
static const System::Int8 SA_SQL_TXN_SNAPSHOT = System::Int8(0x20);
static const System::Int8 SA_SQL_TXN_STATEMENT_SNAPSHOT = System::Int8(0x40);
static const System::Byte SA_SQL_TXN_READONLY_STATEMENT_SNAPSHOT = System::Byte(0x80);
static const System::Word SQL_OLEDB_GET_CHARSET_ID = System::Word(0x2775);
static const System::Word SQL_OLEDB_GET_CHARSET_WIDTH = System::Word(0x2776);
static const System::Int8 MESSAGE_TYPE_INFO = System::Int8(0x0);
static const System::Int8 MESSAGE_TYPE_WARNING = System::Int8(0x1);
static const System::Int8 MESSAGE_TYPE_ACTION = System::Int8(0x2);
static const System::Int8 MESSAGE_TYPE_STATUS = System::Int8(0x3);
static const System::Int8 SQL_TXN_LAST_COMMITTED = System::Int8(0x10);
static const System::Int8 SQL_TRANSACTION_LAST_COMMITTED = System::Int8(0x10);
static const System::Int8 SQL_TXN_TRANSACTION = System::Int8(0x20);
static const System::Int8 SQL_TRANSACTION_TRANSACTION = System::Int8(0x20);
static const System::Int8 SQL_DIAG_ISAM_ERROR = System::Int8(0xd);
static const System::Int8 SQL_DIAG_XA_ERROR = System::Int8(0xe);
static const System::Int8 SQL_INFX_PARAM_SUCCESS = System::Int8(0x4);
static const System::Word SQL_STMTOPT_START = System::Word(0x410);
static const System::Word SQL_GET_ROWID = System::Word(0x418);
static const System::Word SQL_GET_SERIAL_VALUE = System::Word(0x419);
static const System::Int8 FDNULLABLE = System::Int8(0x1);
static const System::Int8 FDDISTINCT = System::Int8(0x2);
static const System::Int8 FDDISTLVARCHAR = System::Int8(0x4);
static const System::Int8 FDDISTBOOLEAN = System::Int8(0x8);
static const System::Int8 FDDISTSIMP = System::Int8(0x10);
static const System::Int8 FDCSTTYPE = System::Int8(0x20);
static const System::Int8 FDNAMED = System::Int8(0x40);
static const System::Int8 SQL_INFX_UDT_FIXED = System::Int8(-100);
static const System::Int8 SQL_INFX_UDT_VARYING = System::Int8(-101);
static const System::Int8 SQL_INFX_UDT_BLOB = System::Int8(-102);
static const System::Int8 SQL_INFX_UDT_CLOB = System::Int8(-103);
static const System::Int8 SQL_INFX_UDT_LVARCHAR = System::Int8(-104);
static const System::Int8 SQL_INFX_RC_ROW = System::Int8(-105);
static const System::Int8 SQL_INFX_RC_COLLECTION = System::Int8(-106);
static const System::Int8 SQL_INFX_RC_LIST = System::Int8(-107);
static const System::Int8 SQL_INFX_RC_SET = System::Int8(-108);
static const System::Int8 SQL_INFX_RC_MULTISET = System::Int8(-109);
static const System::Int8 SQL_INFX_UNSUPPORTED = System::Int8(-110);
static const System::Int8 SQL_INFX_C_SMARTLOB_LOCATOR = System::Int8(-111);
static const System::Int8 SQL_INFX_UDT_BIGINT = System::Int8(-114);
static const System::Word SQL_OPT_LONGID = System::Word(0x8cb);
static const System::Word SQL_INFX_ATTR_LONGID = System::Word(0x8cb);
static const System::Word SQL_INFX_ATTR_LEAVE_TRAILING_SPACES = System::Word(0x8cc);
static const System::Word SQL_INFX_ATTR_DEFAULT_UDT_FETCH_TYPE = System::Word(0x8cd);
static const System::Word SQL_INFX_ATTR_ENABLE_SCROLL_CURSORS = System::Word(0x8ce);
static const System::Word SQL_ENABLE_INSERT_CURSOR = System::Word(0x8cf);
static const System::Word SQL_INFX_ATTR_ENABLE_INSERT_CURSORS = System::Word(0x8cf);
static const System::Word SQL_INFX_ATTR_OPTIMIZE_AUTOCOMMIT = System::Word(0x8d0);
static const System::Word SQL_INFX_ATTR_ODBC_TYPES_ONLY = System::Word(0x8d1);
static const System::Word SQL_INFX_ATTR_FETCH_BUFFER_SIZE = System::Word(0x8d2);
static const System::Word SQL_INFX_ATTR_OPTOFC = System::Word(0x8d3);
static const System::Word SQL_INFX_ATTR_OPTMSG = System::Word(0x8d4);
static const System::Word SQL_INFX_ATTR_REPORT_KEYSET_CURSORS = System::Word(0x8d5);
static const System::Word SQL_INFX_ATTR_LO_AUTOMATIC = System::Word(0x8d6);
static const System::Word SQL_INFX_ATTR_AUTO_FREE = System::Word(0x8d7);
static const System::Word SQL_INFX_ATTR_DEFERRED_PREPARE = System::Word(0x8d9);
static const System::Word SQL_INFX_ATTR_PAM_FUNCTION = System::Word(0x8da);
static const System::Word SQL_INFX_ATTR_PAM_RESPONSE_BUF = System::Word(0x8db);
static const System::Word SQL_INFX_ATTR_PAM_RESPONSE_BUF_LEN = System::Word(0x8dc);
static const System::Word SQL_INFX_ATTR_PAM_RESPONSE_LEN_PTR = System::Word(0x8dd);
static const System::Word SQL_INFX_ATTR_PAM_CHALLENGE_BUF = System::Word(0x8de);
static const System::Word SQL_INFX_ATTR_PAM_CHALLENGE_BUF_LEN = System::Word(0x8df);
static const System::Word SQL_INFX_ATTR_PAM_CHALLENGE_LEN_PTR = System::Word(0x8e0);
static const System::Word SQL_INFX_ATTR_DELIMIDENT = System::Word(0x8e1);
static const System::Word SQL_INFX_ATTR_DBLOCALE = System::Word(0x8e3);
static const System::Word SQL_INFX_ATTR_LOCALIZE_DECIMALS = System::Word(0x8e4);
static const System::Word SQL_INFX_ATTR_DEFAULT_DECIMAL = System::Word(0x8e5);
static const System::Word SQL_INFX_ATTR_SKIP_PARSING = System::Word(0x8e6);
static const System::Word SQL_INFX_ATTR_CALL_FROM_DOTNET = System::Word(0x8e7);
static const System::Word SQL_INFX_ATTR_LENGTHINCHARFORDIAGRECW = System::Word(0x8e8);
static const System::Word SQL_INFX_ATTR_SENDTIMEOUT = System::Word(0x8e9);
static const System::Word SQL_INFX_ATTR_RECVTIMEOUT = System::Word(0x8ea);
static const System::Word SQL_INFX_ATTR_IDSISAMERRMSG = System::Word(0x8eb);
static const System::Word SQL_INFX_ATTR_FLAGS = System::Word(0x76c);
static const System::Word SQL_INFX_ATTR_EXTENDED_TYPE_CODE = System::Word(0x76d);
static const System::Word SQL_INFX_ATTR_EXTENDED_TYPE_NAME = System::Word(0x76e);
static const System::Word SQL_INFX_ATTR_EXTENDED_TYPE_OWNER = System::Word(0x76f);
static const System::Word SQL_INFX_ATTR_EXTENDED_TYPE_ALIGNMENT = System::Word(0x770);
static const System::Word SQL_INFX_ATTR_SOURCE_TYPE_CODE = System::Word(0x771);
static const System::Word SQL_VMB_CHAR_LEN = System::Word(0x915);
static const System::Word SQL_INFX_ATTR_VMB_CHAR_LEN = System::Word(0x915);
static const System::Word SQL_INFX_ATTR_MAX_FET_ARR_SIZE = System::Word(0x916);
static const System::Int8 SQL_VMB_CHAR_EXACT = System::Int8(0x0);
static const System::Int8 SQL_VMB_CHAR_ESTIMATE = System::Int8(0x1);
static const System::Int8 SQL_INFX_RC_NEXT = System::Int8(0x1);
static const System::Int8 SQL_INFX_RC_PRIOR = System::Int8(0x2);
static const System::Int8 SQL_INFX_RC_FIRST = System::Int8(0x3);
static const System::Int8 SQL_INFX_RC_LAST = System::Int8(0x4);
static const System::Int8 SQL_INFX_RC_ABSOLUTE = System::Int8(0x5);
static const System::Int8 SQL_INFX_RC_RELATIVE = System::Int8(0x6);
static const System::Int8 SQL_INFX_RC_CURRENT = System::Int8(0x7);
static const System::Word SQL_INFX_LO_SPEC_LENGTH = System::Word(0x8ca);
static const System::Word SQL_INFX_LO_PTR_LENGTH = System::Word(0x8cb);
static const System::Word SQL_INFX_LO_STAT_LENGTH = System::Word(0x8cc);
static const System::Int8 LO_APPEND = System::Int8(0x1);
static const System::Int8 LO_WRONLY = System::Int8(0x2);
static const System::Int8 LO_RDONLY = System::Int8(0x4);
static const System::Int8 LO_RDWR = System::Int8(0x8);
static const System::Int8 LO_RANDOM = System::Int8(0x20);
static const System::Int8 LO_SEQUENTIAL = System::Int8(0x40);
static const System::Byte LO_FORWARD = System::Byte(0x80);
static const System::Word LO_REVERSE = System::Word(0x100);
static const System::Word LO_BUFFER = System::Word(0x200);
static const System::Word LO_NOBUFFER = System::Word(0x400);
static const System::Int8 LO_DIRTY_READ = System::Int8(0x10);
static const System::Word LO_NODIRTY_READ = System::Word(0x800);
static const System::Word LO_LOCKALL = System::Word(0x1000);
static const System::Word LO_LOCKRANGE = System::Word(0x2000);
static const System::Int8 LO_ATTR_LOG = System::Int8(0x1);
static const System::Int8 LO_ATTR_NOLOG = System::Int8(0x2);
static const System::Int8 LO_ATTR_DELAY_LOG = System::Int8(0x4);
static const System::Int8 LO_ATTR_KEEP_LASTACCESS_TIME = System::Int8(0x8);
static const System::Int8 LO_ATTR_NOKEEP_LASTACCESS_TIME = System::Int8(0x10);
static const System::Int8 LO_ATTR_HIGH_INTEG = System::Int8(0x20);
static const System::Int8 LO_ATTR_MODERATE_INTEG = System::Int8(0x40);
static const System::Int8 LO_SEEK_SET = System::Int8(0x0);
static const System::Int8 LO_SEEK_CUR = System::Int8(0x1);
static const System::Int8 LO_SEEK_END = System::Int8(0x2);
static const System::Int8 LO_SHARED_MODE = System::Int8(0x1);
static const System::Int8 LO_EXCLUSIVE_MODE = System::Int8(0x2);
static const System::Word SQL_ATTR_TDATA_HOST_ID = System::Word(0x32c9);
static const System::Word SQL_ATTR_TDATA_SESSION_NUMBER = System::Word(0x32ca);
static const System::Word SQL_ATTR_TDATA_SESSION_CHARSET = System::Word(0x32cb);
static const System::Word SQL_ATTR_AGKR = System::Word(0x32cc);
static const System::Word SQL_ATTR_DATA_ENCRYPTION = System::Word(0x32d0);
static const System::Word SQL_ATTR_TDATA_ROWCOUNT = System::Word(0x32d1);
static const System::Int8 SQL_DATA_ENCRYPTION_ON = System::Int8(0x1);
static const System::Int8 SQL_DATA_ENCRYPTION_OFF = System::Int8(0x0);
static const System::Int8 SQL_AGKR_NO = System::Int8(0x0);
static const System::Int8 SQL_AGKR_IDENTITY_COLUMN = System::Int8(0x1);
static const System::Int8 SQL_AGKR_WHOLE_ROW = System::Int8(0x2);
static const System::Word SQL_DRIVER_DESCRIPTOR_BASE = System::Word(0x4000);
static const System::Word SQL_COLUMN_TD_DRIVER_START = System::Word(0x514);
static const System::Word SQL_COLUMN_ACTIVITY_TYPE = System::Word(0x4514);
static const System::Word SQL_COLUMN_COST_ESTIMATE = System::Word(0x4515);
static const System::Word SQL_COLUMN_FORMAT = System::Word(0x4516);
static const System::Word SQL_COLUMN_TITLE = System::Word(0x4517);
static const System::Word SQL_COLUMN_ACTUAL_NAME = System::Word(0x4518);
static const System::Word SQL_COLUMN_CHARACTER_SET = System::Word(0x4519);
static const System::Word SQL_COLUMN_EXPORT_WIDTH = System::Word(0x451a);
static const System::Word SQL_COLUMN_EXPORT_WIDTH_ADJ = System::Word(0x451b);
static const System::Word SQL_COLUMN_EXPORT_BYTES = System::Word(0x451c);
static const System::Word SQL_COLUMN_TDODBC_TYPE = System::Word(0x451d);
static const System::Word SQL_COLUMN_TD_UDT_NAME = System::Word(0x451e);
static const System::Word SQL_COLUMN_TD_UDT_INDICATOR = System::Word(0x451f);
static const System::Word SQL_COLUMN_TD_DRIVER_END = System::Word(0x451f);
static const System::Word SQL_COLUMN_TD_DRIVER_MAX = System::Word(0x545);
static const System::Word SQL_DESC_TD_ACTIVITY_TYPE = System::Word(0x4514);
static const System::Word SQL_DESC_TD_COST_ESTIMATE = System::Word(0x4515);
static const System::Word SQL_DESC_TD_FORMAT = System::Word(0x4516);
static const System::Word SQL_DESC_TD_TITLE = System::Word(0x4517);
static const System::Word SQL_DESC_TD_ACTUAL_NAME = System::Word(0x4518);
static const System::Word SQL_DESC_TD_CHARACTER_SET = System::Word(0x4519);
static const System::Word SQL_DESC_TD_EXPORT_WIDTH = System::Word(0x451a);
static const System::Word SQL_DESC_TD_EXPORT_WIDTH_ADJ = System::Word(0x451b);
static const System::Word SQL_DESC_TD_EXPORT_BYTES = System::Word(0x451c);
static const System::Word SQL_DESC_TD_ODBC_TYPE = System::Word(0x451d);
static const System::Word SQL_DESC_TD_UDT_NAME = System::Word(0x451e);
static const System::Word SQL_DESC_TD_UDT_INDICATOR = System::Word(0x451f);
static const System::Word SQL_DRIVER_DESCRIPTOR_END = System::Word(0x451f);
static const System::Int8 SQL_TD_CS_UNDEFINED = System::Int8(0x0);
static const System::Int8 SQL_TD_CS_LATIN = System::Int8(0x1);
static const System::Int8 SQL_TD_CS_UNICODE = System::Int8(0x2);
static const System::Int8 SQL_TD_CS_KANJISJIS = System::Int8(0x3);
static const System::Int8 SQL_TD_CS_GRAPHIC = System::Int8(0x4);
static const System::Int8 SQL_TD_CS_KANJI1 = System::Int8(0x5);
static const System::Word SQL_TD_FIXED_NUMBER = System::Word(0x4651);
static const System::Word SQL_TD_FLOATING_NUMBER = System::Word(0x4652);
static const System::Word SQL_TD_XML = System::Word(0x4653);
static const System::Word SQL_TD_JSON = System::Word(0x4654);
static const System::Word SQL_TD_WJSON = System::Word(0x4655);
static const System::Word SQL_TD_UDT = System::Word(0x5208);
static const System::Int8 SQL_TD_UDT_BASE = System::Int8(0x0);
static const System::Int8 SQL_TD_UDT_STRUCTURED = System::Int8(0x1);
static const System::Int8 SQL_TD_UDT_DISTINCT = System::Int8(0x2);
static const System::Int8 SQL_TD_UDT_INTERNAL = System::Int8(0x3);
static const short SQL_TD_TYPE_MIN = short(-1049);
static const short SQL_TD_TYPE_MAX = short(-1045);
static const short SQL_PERIOD_DATE = short(-1049);
static const short SQL_PERIOD_TIME = short(-1048);
static const short SQL_PERIOD_TIME_WITH_TIME_ZONE = short(-1047);
static const short SQL_PERIOD_TIMESTAMP = short(-1046);
static const short SQL_PERIOD_TIMESTAMP_WITH_TIME_ZONE = short(-1045);
static const System::Int8 SQL_PERIOD_TIME_MAX_PRECISION = System::Int8(0x6);
static const System::Int8 SQL_PERIOD_TIMESTAMP_MAX_PRECISION = System::Int8(0x6);
static const System::Int8 SQL_PERIOD_DATE_LEN = System::Int8(0x1c);
static const System::Int8 SQL_PERIOD_TIME_LEN = System::Int8(0x18);
static const System::Int8 SQL_PERIOD_TIME_WITH_TIME_ZONE_LEN = System::Int8(0x24);
static const System::Int8 SQL_PERIOD_TIMESTAMP_LEN = System::Int8(0x2e);
static const System::Int8 SQL_PERIOD_TIMESTAMP_WITH_TIME_ZONE_LEN = System::Int8(0x3a);
static const System::Int8 SQL_PERIOD_DATE_OCTET_LEN = System::Int8(0x8);
static const System::Int8 SQL_PERIOD_TIME_OCTET_LEN = System::Int8(0xc);
static const System::Int8 SQL_PERIOD_TIME_WITH_TIME_ZONE_OCTET_LEN = System::Int8(0x10);
static const System::Int8 SQL_PERIOD_TIMESTAMP_OCTET_LEN = System::Int8(0x14);
static const System::Int8 SQL_PERIOD_TIMESTAMP_WITH_TIME_ZONE_OCTET_LEN = System::Int8(0x18);
static const int SQL_PERIOD_SECONDS_SCALE = int(0xf4240);
static const System::Int8 SQL_PERIOD_TZ_BASE = System::Int8(0x10);
static const System::Word SQL_CONOPT_START = System::Word(0x410);
static const System::Word SQL_ATTR_APP_WCHAR_TYPE = System::Word(0x425);
static const System::Word SQL_ATTR_APP_UNICODE_TYPE = System::Word(0x428);
static const System::Word SQL_ATTR_DRIVER_UNICODE_TYPE = System::Word(0x429);
static const System::Int8 SQL_DD_CP_ANSI = System::Int8(0x0);
static const System::Int8 SQL_DD_CP_UCS2 = System::Int8(0x1);
static const System::Int8 SQL_DD_CP_UTF8 = System::Int8(0x2);
static const System::Int8 SQL_DD_CP_UTF16 = System::Int8(0x1);
extern DELPHI_PACKAGE bool __fastcall SQL_SUCCEEDED(short rc);
extern DELPHI_PACKAGE int __fastcall SQL_LEN_BINARY_ATTR(int Length);
extern DELPHI_PACKAGE int __fastcall SQL_LEN_DATA_AT_EXEC(int Length);
extern DELPHI_PACKAGE bool __fastcall SQL_FUNC_EXISTS(void * pfExists, int uwAPI);
}	/* namespace Odbccli */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ODBCCLI)
using namespace Firedac::Phys::Odbccli;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS)
using namespace Firedac::Phys;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Phys_OdbccliHPP
