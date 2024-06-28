// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Sqlite.pas' rev: 34.00 (Android)

#ifndef System_SqliteHPP
#define System_SqliteHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Sqlite
{
//-- forward type declarations -----------------------------------------------
struct sqlite3_index_constraint;
struct sqlite3_index_orderby;
struct sqlite3_index_constraint_usage;
//-- type declarations -------------------------------------------------------
typedef int __cdecl (*TSqlite3ExecCallback)(void * Param, int NumCols, System::PPWideChar ColTextStrs, System::PPWideChar ColNameStrs);

typedef void __cdecl (*TxDlSym2)(void);

typedef int __cdecl (*TSqlite3BusyHandlerCallback)(void * Ptr, int NumberOfInvocations);

typedef int __cdecl (*TxAuth)(void * UserData, int ActionCode, char * Str1, char * Str2, char * Str3, char * Str4);

typedef void __cdecl (*TxTrace)(void * Ptr, char * Text);

typedef void __cdecl (*TxProfile)(void * Ptr, char * Text, unsigned __int64 Time);

typedef int __cdecl (*TSqlite3ProgressHandlerCallback)(void * P);

typedef void * *PSqlite3_value;

typedef void __cdecl (*TBindDestructor)(void * Ptr);

typedef void * *PSqlite3_context;

typedef void __cdecl (*TxFunc)(void * Context, int Num, /* out */ void * &Value);

typedef void __cdecl (*TxStep)(void * Context, int Num, /* out */ void * &Value);

typedef void __cdecl (*TxFinal)(void * Context);

typedef void __cdecl (*TxDestroy)(void * Ptr);

typedef void __cdecl (*TSetAuxDataProc)(void * Ptr);

typedef void __cdecl (*TResultDestructor)(void * Ptr);

typedef int __cdecl (*TxCompare)(void * pArg, int Size1, void * Str1, int Size2, void * Str2);

typedef void __cdecl (*TCollationNeededCallback)(void * Ptr, void * DbConnection, int eTextRep, char * SequenceName);

typedef void __cdecl (*TCollationNeededCallback16)(void * Ptr, void * DbConnection, int eTextRep, System::WideChar * SequenceName);

typedef int __cdecl (*TCommitHook)(void * Ptr);

typedef void __cdecl (*TRollbackHook)(void * Ptr);

typedef void __cdecl (*TUpdateHook)(void * Ptr, int Operation, char * DbName, char * TableName, __int64 RowId);

typedef void * PSqlite3_module;

struct DECLSPEC_DRECORD sqlite3_index_constraint
{
public:
	int iColumn;
	System::Byte op;
	System::Byte usable;
	int iTermOffset;
};


typedef sqlite3_index_constraint *Psqlite3_index_constraint;

struct DECLSPEC_DRECORD sqlite3_index_orderby
{
public:
	int iColumn;
	System::Byte desc;
};


typedef sqlite3_index_orderby *Psqlite3_index_orderby;

struct DECLSPEC_DRECORD sqlite3_index_constraint_usage
{
public:
	int argvIndex;
	System::Byte omit;
};


typedef sqlite3_index_constraint_usage *Psqlite3_index_constraint_usage;

typedef void __cdecl (*TModulexFunc)(void * Context, int Num, void * &Value);

typedef int __cdecl (*TWalHookCallback)(void * Ptr, void * DbConnection, char * DbName, int NumPages);

typedef int __cdecl (*TRTreexGeom)(void * Geometry, int nCoord, double &aCoord, int &pRes);

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sqlite */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_SQLITE)
using namespace System::Sqlite;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_SqliteHPP
