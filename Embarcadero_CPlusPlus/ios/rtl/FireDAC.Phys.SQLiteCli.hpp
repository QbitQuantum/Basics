// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.SQLiteCli.pas' rev: 34.00 (iOS)

#ifndef Firedac_Phys_SqlitecliHPP
#define Firedac_Phys_SqlitecliHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Consts.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Sqlitecli
{
//-- forward type declarations -----------------------------------------------
struct sqlite3_index_constraint;
struct sqlite3_index_orderby;
struct sqlite3_index_constraint_usage;
struct sqlite3_index_info;
struct sqlite3_module;
struct sqlite3_vtab;
struct sqlite3_vtab_cursor;
struct sqlite3_mem_methods;
struct sqlite3_file;
struct sqlite3_io_methods;
struct sqlite3_vfs;
struct sqlite3_rtree_geometry;
struct sqlite3_rtree_query_info;
//-- type declarations -------------------------------------------------------
typedef char * PUtf8;

typedef char * *PPUtf8;

typedef __int64 sqlite3_int64;

typedef unsigned __int64 sqlite3_uint64;

typedef double sqlite3_rtree_dbl;

typedef double *psqlite3_rtree_dbl;

typedef void * psqlite3;

typedef void * psqlite3_blob;

typedef void * psqlite3_context;

typedef void * psqlite3_stmt;

typedef void * psqlite3_value;

typedef void * *ppsqlite3_value;

typedef void * psqlite3_backup;

typedef sqlite3_index_info *psqlite3_index_info;

typedef sqlite3_index_constraint *psqlite3_index_constraint;

typedef sqlite3_index_orderby *psqlite3_index_orderby;

typedef sqlite3_index_constraint_usage *psqlite3_index_constraint_usage;

typedef sqlite3_module *psqlite3_module;

typedef sqlite3_vtab *psqlite3_vtab;

typedef sqlite3_vtab_cursor *psqlite3_vtab_cursor;

typedef sqlite3_mem_methods *psqlite3_mem_methods;

typedef sqlite3_file *psqlite3_file;

typedef sqlite3_io_methods *psqlite3_io_methods;

typedef sqlite3_vfs *psqlite3_vfs;

typedef sqlite3_rtree_geometry *psqlite3_rtree_geometry;

typedef sqlite3_rtree_query_info *psqlite3_rtree_query_info;

typedef int __cdecl (*Tsqlite3_busy_callback)(void * userdata, int times);

typedef void __cdecl (*Tsqlite3_func_callback)(void * context, int nargs, ppsqlite3_value args);

typedef void __cdecl (*Tsqlite3_step_callback)(void * context, int nargs, ppsqlite3_value args);

typedef void __cdecl (*Tsqlite3_final_callback)(void * context);

typedef void __cdecl (*Tsqlite3_destroy_callback)(void * value);

typedef int __cdecl (*Tsqlite3_commit_callback)(void * userdata);

typedef void __cdecl (*Tsqlite3_rollback_callback)(void * userdata);

typedef void __cdecl (*Tsqlite3_trace_callback)(void * userdata, char * zSql);

typedef void __cdecl (*Tsqlite3_profile_callback)(void * userdata, char * zSql, unsigned __int64 time);

typedef int __cdecl (*Tsqlite3_auth_callback)(void * userdata, int code, char * zArg1, char * zArg2, char * zArg3, char * zArg4);

typedef void __cdecl (*Tsqlite3_update_callback)(void * userdata, int oper, char * zDb, char * zTable, __int64 rowid);

typedef void __cdecl (*Tsqlite3_collation_callback)(void * userdata, void * db, int eTextRep, void * name);

typedef int __cdecl (*Tsqlite3_compare_callback)(void * userdata, int len1, void * str1, int len2, void * str2);

typedef int __cdecl (*Tsqlite3_progress_callback)(void * userdata);

typedef int __cdecl (*Tsqlite3_wal_callback)(void * userdata, void * db, System::PByte name, int nPages);

typedef int __cdecl (*Tsqlite3_rtree_xGeom_callback)(psqlite3_rtree_geometry geom, int nCoord, psqlite3_rtree_dbl aCoord, int &pRes);

typedef int __cdecl (*Tsqlite3_rtree_xQuery_callback)(psqlite3_rtree_query_info info);

typedef void __cdecl (*Tsqlite3_rtree_xDelUser_callback)(void * userdata);

struct DECLSPEC_DRECORD sqlite3_index_constraint
{
public:
	int iColumn;
	System::Byte op;
	System::Byte usable;
	int iTermOffset;
};


struct DECLSPEC_DRECORD sqlite3_index_orderby
{
public:
	int iColumn;
	System::Byte desc;
};


struct DECLSPEC_DRECORD sqlite3_index_constraint_usage
{
public:
	int argvIndex;
	System::Byte omit;
};


struct DECLSPEC_DRECORD sqlite3_index_info
{
public:
	int nConstraint;
	sqlite3_index_constraint *aConstraint;
	int nOrderBy;
	sqlite3_index_orderby *aOrderBy;
	sqlite3_index_constraint_usage *aConstraintUsage;
	int idxNum;
	char *idxStr;
	int needToFreeIdxStr;
	int orderByConsumed;
	double estimatedCost;
	__int64 estimatedRows;
	int idxFlags;
	unsigned __int64 colUsed;
};


struct DECLSPEC_DRECORD sqlite3_module
{
public:
	int iVersion;
	int __cdecl (*xCreate)(void * db, void * pAux, int argc, PPUtf8 argv, psqlite3_vtab &ppVTab, char * &pzErr);
	int __cdecl (*xConnect)(void * db, void * pAux, int argc, PPUtf8 argv, psqlite3_vtab &ppVTab, char * &pzErr);
	int __cdecl (*xBestIndex)(psqlite3_vtab pVTab, psqlite3_index_info info);
	int __cdecl (*xDisconnect)(psqlite3_vtab pVTab);
	int __cdecl (*xDestroy)(psqlite3_vtab pVTab);
	int __cdecl (*xOpen)(psqlite3_vtab pVTab, psqlite3_vtab_cursor &ppCursor);
	int __cdecl (*xClose)(psqlite3_vtab_cursor cursor);
	int __cdecl (*xFilter)(psqlite3_vtab_cursor cursor, int idxNum, char * idxStr, int argc, ppsqlite3_value argv);
	int __cdecl (*xNext)(psqlite3_vtab_cursor cursor);
	int __cdecl (*xEof)(psqlite3_vtab_cursor cursor);
	int __cdecl (*xColumn)(psqlite3_vtab_cursor cursor, void * context, int index);
	int __cdecl (*xRowid)(psqlite3_vtab_cursor cursor, __int64 &pRowid);
	int __cdecl (*xUpdate)(psqlite3_vtab pVTab, int nArg, ppsqlite3_value apArgs, __int64 &rowid);
	int __cdecl (*xBegin)(psqlite3_vtab pVTab);
	int __cdecl (*xSync)(psqlite3_vtab pVTab);
	int __cdecl (*xCommit)(psqlite3_vtab pVTab);
	int __cdecl (*xRollback)(psqlite3_vtab pVTab);
	int __cdecl (*xFindFunction)(psqlite3_vtab pVTab, int nArg, char * zName, Tsqlite3_func_callback &pxFunc, void * &ppArg);
	int __cdecl (*xRename)(psqlite3_vtab pVTab, char * zNew);
	int __cdecl (*xSavepoint)(psqlite3_vtab pVTab, int p);
	int __cdecl (*xRelease)(psqlite3_vtab pVTab, int p);
	int __cdecl (*xRollbackTo)(psqlite3_vtab pVTab, int p);
};


struct DECLSPEC_DRECORD sqlite3_vtab
{
public:
	sqlite3_module *pModule;
	int nRef;
	char *zErrMsg;
};


struct DECLSPEC_DRECORD sqlite3_vtab_cursor
{
public:
	sqlite3_vtab *pVtab;
};


struct DECLSPEC_DRECORD sqlite3_mem_methods
{
public:
	void * __cdecl (*xMalloc)(int size);
	void __cdecl (*xFree)(void * ptr);
	void * __cdecl (*xRealloc)(void * ptr, int size);
	int __cdecl (*xSize)(void * ptr);
	int __cdecl (*xRoundup)(int size);
	int __cdecl (*xInit)(void * data);
	void __cdecl (*xShutdown)(void * data);
	void *pAppData;
};


struct DECLSPEC_DRECORD sqlite3_file
{
public:
	sqlite3_io_methods *pMethods;
};


struct DECLSPEC_DRECORD sqlite3_io_methods
{
public:
	int iVersion;
	int __cdecl (*xClose)(psqlite3_file pFile);
	int __cdecl (*xRead)(psqlite3_file pFile, void * buf, int iAmt, __int64 iOfst);
	int __cdecl (*xWrite)(psqlite3_file pFile, void * bug, int iAmt, __int64 iOfst);
	int __cdecl (*xTruncate)(psqlite3_file pFile, __int64 size);
	int __cdecl (*xSync)(psqlite3_file pFile, int flags);
	int __cdecl (*xFileSize)(psqlite3_file pFile, __int64 &pSize);
	int __cdecl (*xLock)(psqlite3_file pFile, int mode);
	int __cdecl (*xUnlock)(psqlite3_file pFile, int mode);
	int __cdecl (*xCheckReservedLock)(psqlite3_file pFile, int &pResOut);
	int __cdecl (*xFileControl)(psqlite3_file pFile, int op, void * pArg);
	int __cdecl (*xSectorSize)(psqlite3_file pFile);
	int __cdecl (*xDeviceCharacteristics)(psqlite3_file pFile);
	int __cdecl (*xShmMap)(psqlite3_file pFile, int iPg, int pgsz, int i, System::PPointer p);
	int __cdecl (*xShmLock)(psqlite3_file pFile, int offset, int n, int flags);
	void __cdecl (*xShmBarrier)(psqlite3_file pFile);
	int __cdecl (*xShmUnmap)(psqlite3_file pFile, int deleteFlag);
	int __cdecl (*xFetch)(sqlite3_file pFile, __int64 iOfst, int iAmt, System::PPointer pp);
	int __cdecl (*xUnfetch)(sqlite3_file pFile, __int64 iOfst, void * p);
};


typedef int __cdecl (*Tsqlite3_vfs_xOpen)(psqlite3_vfs pVfs, char * zName, psqlite3_file pFile, int flags, int &pOutFlags);

typedef void __cdecl (*Tsqlite3_syscall_ptr)(void);

struct DECLSPEC_DRECORD sqlite3_vfs
{
public:
	int iVersion;
	int szOsFile;
	int mxPathname;
	sqlite3_vfs *pNext;
	char *zName;
	void *pAppData;
	Tsqlite3_vfs_xOpen xOpen;
	int __cdecl (*xDelete)(psqlite3_vfs pVfs, char * zName, int syncDir);
	int __cdecl (*xAccess)(psqlite3_vfs pVfs, char * zName, int flags, int &pResOut);
	int __cdecl (*xFullPathname)(psqlite3_vfs pVfs, char * zName, int nOut, char * zOut);
	void * __cdecl (*xDlOpen)(psqlite3_vfs pVfs, char * zFilename);
	void __cdecl (*xDlError)(psqlite3_vfs pVfs, int nByte, char * zErrMsg);
	void * __cdecl (*xDlSym)(psqlite3_vfs pVfs, void * ptr, char * zSymbol);
	void __cdecl (*xDlClose)(psqlite3_vfs pVfs, void * ptr);
	int __cdecl (*xRandomness)(psqlite3_vfs pVfs, int nByte, char * zOut);
	int __cdecl (*xSleep)(psqlite3_vfs pVfs, int microseconds);
	int __cdecl (*xCurrentTime)(psqlite3_vfs pVfs, double &tm);
	int __cdecl (*xGetLastError)(psqlite3_vfs pVfs, int l, char * v);
	int __cdecl (*xCurrentTimeInt64)(psqlite3_vfs pVfs, __int64 &tm);
	int __cdecl (*xSetSystemCall)(psqlite3_vfs pVfs, char * zName, Tsqlite3_syscall_ptr p);
	Tsqlite3_syscall_ptr __cdecl (*xGetSystemCall)(psqlite3_vfs pVfs, char * zName);
	char * __cdecl (*xNextSystemCall)(psqlite3_vfs pVfs, char * zName);
};


struct DECLSPEC_DRECORD sqlite3_rtree_geometry
{
public:
	void *pContext;
	int nParam;
	double *aParam;
	void *pUser;
	Tsqlite3_rtree_xDelUser_callback xDelUser;
};


struct DECLSPEC_DRECORD sqlite3_rtree_query_info
{
public:
	void *pContext;
	int nParam;
	double *aParam;
	void *pUser;
	Tsqlite3_rtree_xDelUser_callback xDelUser;
	double *aCoord;
	unsigned *anQueue;
	int nCoord;
	int iLevel;
	int mxLevel;
	__int64 iRowid;
	double rParentScore;
	int eParentWithin;
	int eWithin;
	double rScore;
};


typedef char * __cdecl (*Tsqlite3_libversion)(void);

typedef int __cdecl (*Tsqlite3_libversion_number)(void);

typedef int __cdecl (*Tsqlite3_compileoption_used)(char * zOptName);

typedef char * __cdecl (*Tsqlite3_compileoption_get)(int N);

typedef int __cdecl (*Tsqlite3_enable_shared_cache)(int onoff);

typedef int __cdecl (*Tsqlite3_release_memory)(int amount);

typedef void __cdecl (*Tsqlite3_soft_heap_limit)(int amount);

typedef int __cdecl (*Tsqlite3_status)(int op, int &pCurrent, int &pHighwater, int resetFlag);

typedef int __cdecl (*Tsqlite3_initialize)(void);

typedef int __cdecl (*Tsqlite3_shutdown)(void);

typedef void * __cdecl (*Tsqlite3_malloc)(int n);

typedef __int64 __cdecl (*Tsqlite3_memory_used)(void);

typedef __int64 __cdecl (*Tsqlite3_memory_highwater)(int resetFlag);

typedef void __cdecl (*Tsqlite3_free)(void * APtr);

typedef int __cdecl (*Tsqlite3_config)(int option, ...);

typedef int __cdecl (*Tsqlite3_open)(System::PByte filename, void * &ppDb);

typedef int __cdecl (*Tsqlite3_open_v2)(char * filename, void * &ppDb, int flags, char * zVfs);

typedef int __cdecl (*Tsqlite3_key)(void * db, System::PByte key, int nKey);

typedef int __cdecl (*Tsqlite3_rekey)(void * db, System::PByte key, int nKey);

typedef int __cdecl (*Tsqlite3_key_v2)(void * db, System::PByte zDbName, System::PByte zKey, int nKey);

typedef int __cdecl (*Tsqlite3_rekey_v2)(void * db, System::PByte zDbName, System::PByte zKey, int nKey);

typedef int __cdecl (*Tsqlite3_close)(void * db);

typedef int __cdecl (*Tsqlite3_busy_timeout)(void * db, int ms);

typedef int __cdecl (*Tsqlite3_busy_handler)(void * db, Tsqlite3_busy_callback callback, void * userdata);

typedef void * __cdecl (*Tsqlite3_trace)(void * db, Tsqlite3_trace_callback xTrace, void * userdata);

typedef void * __cdecl (*Tsqlite3_profile)(void * db, Tsqlite3_profile_callback xProfile, void * userdata);

typedef int __cdecl (*Tsqlite3_set_authorizer)(void * db, Tsqlite3_auth_callback xAuth, void * userdata);

typedef int __cdecl (*Tsqlite3_get_autocommit)(void * db);

typedef void * __cdecl (*Tsqlite3_commit_hook)(void * db, Tsqlite3_commit_callback callback, void * userdata);

typedef void * __cdecl (*Tsqlite3_rollback_hook)(void * db, Tsqlite3_rollback_callback callback, void * userdata);

typedef int __cdecl (*Tsqlite3_table_column_metadata)(void * db, char * zDbName, char * zTableName, char * zColumnName, char * &pzDataType, char * &pzCollSeq, int &pNotNull, int &pPrimaryKey, int &pAutoinc);

typedef void * __cdecl (*Tsqlite3_update_hook)(void * db, Tsqlite3_update_callback callback, void * userdata);

typedef int __cdecl (*Tsqlite3_limit)(void * db, int id, int newVal);

typedef int __cdecl (*Tsqlite3_collation_needed)(void * db, void * userdata, Tsqlite3_collation_callback callback);

typedef int __cdecl (*Tsqlite3_create_collation)(void * db, System::PByte zName, int eTextRep, void * userdata, Tsqlite3_compare_callback callback);

typedef void __cdecl (*Tsqlite3_progress_handler)(void * db, int nOpers, Tsqlite3_progress_callback callback, void * userdata);

typedef int __cdecl (*Tsqlite3_errcode)(void * db);

typedef System::PByte __cdecl (*Tsqlite3_errmsg)(void * db);

typedef int __cdecl (*Tsqlite3_extended_result_codes)(void * db, int onoff);

typedef System::PByte __cdecl (*Tsqlite3_errstr)(int code);

typedef int __cdecl (*Tsqlite3_changes)(void * db);

typedef int __cdecl (*Tsqlite3_total_changes)(void * db);

typedef void __cdecl (*Tsqlite3_interrupt)(void * db);

typedef __int64 __cdecl (*Tsqlite3_last_insert_rowid)(void * db);

typedef char * __cdecl (*Tsqlite3_db_filename)(void * db, char * zDbName);

typedef int __cdecl (*Tsqlite3_db_readonly)(void * db, char * zDbName);

typedef int __cdecl (*Tsqlite3_db_status)(void * db, int op, int &pCurrent, int &pHighwater, int resetFlag);

typedef int __cdecl (*Tsqlite3_exec)(void * db, System::PByte zSql, void * callback, void * data, Firedac::Stan::Intf::PPByte errmsg);

typedef int __cdecl (*Tsqlite3_prepare)(void * db, System::PByte zSql, int nByte, void * &ppStmt, System::PByte &pzTail);

typedef int __cdecl (*Tsqlite3_step)(void * stmt);

typedef int __cdecl (*Tsqlite3_reset)(void * stmt);

typedef int __cdecl (*Tsqlite3_finalize)(void * stmt);

typedef int __cdecl (*Tsqlite3_stmt_readonly)(void * stmt);

typedef int __cdecl (*Tsqlite3_stmt_busy)(void * stmt);

typedef int __cdecl (*Tsqlite3_stmt_status)(void * stmt, int op, int resetFlg);

typedef int __cdecl (*Tsqlite3_clear_bindings)(void * stmt);

typedef int __cdecl (*Tsqlite3_bind_parameter_count)(void * stmt);

typedef int __cdecl (*Tsqlite3_bind_parameter_index)(void * stmt, char * zName);

typedef char * __cdecl (*Tsqlite3_bind_parameter_name)(void * stmt, int index);

typedef int __cdecl (*Tsqlite3_bind_blob)(void * stmt, int index, void * value, int nBytes, Tsqlite3_destroy_callback destr);

typedef int __cdecl (*Tsqlite3_bind_blob64)(void * stmt, int index, void * value, unsigned __int64 nBytes, Tsqlite3_destroy_callback destr);

typedef int __cdecl (*Tsqlite3_bind_double)(void * stmt, int index, double value);

typedef int __cdecl (*Tsqlite3_bind_int)(void * stmt, int index, int value);

typedef int __cdecl (*Tsqlite3_bind_int64)(void * stmt, int index, __int64 value);

typedef int __cdecl (*Tsqlite3_bind_null)(void * stmt, int index);

typedef int __cdecl (*Tsqlite3_bind_text)(void * stmt, int index, System::PByte value, int nBytes, Tsqlite3_destroy_callback destr);

typedef int __cdecl (*Tsqlite3_bind_text64)(void * stmt, int index, System::PByte value, unsigned __int64 nBytes, Tsqlite3_destroy_callback destr, System::Byte encoding);

typedef int __cdecl (*Tsqlite3_bind_value)(void * stmt, int index, void * value);

typedef int __cdecl (*Tsqlite3_bind_zeroblob)(void * stmt, int index, int nBytes);

typedef int __cdecl (*Tsqlite3_column_count)(void * stmt);

typedef int __cdecl (*Tsqlite3_column_type)(void * stmt, int iCol);

typedef System::PByte __cdecl (*Tsqlite3_column_name)(void * stmt, int iCol);

typedef System::PByte __cdecl (*Tsqlite3_column_database_name)(void * stmt, int iCol);

typedef System::PByte __cdecl (*Tsqlite3_column_table_name)(void * stmt, int iCol);

typedef System::PByte __cdecl (*Tsqlite3_column_origin_name)(void * stmt, int iCol);

typedef System::PByte __cdecl (*Tsqlite3_column_decltype)(void * stmt, int iCol);

typedef void * __cdecl (*Tsqlite3_column_blob)(void * stmt, int iCol);

typedef int __cdecl (*Tsqlite3_column_bytes)(void * stmt, int iCol);

typedef double __cdecl (*Tsqlite3_column_double)(void * stmt, int iCol);

typedef int __cdecl (*Tsqlite3_column_int)(void * stmt, int iCol);

typedef __int64 __cdecl (*Tsqlite3_column_int64)(void * stmt, int iCol);

typedef System::PByte __cdecl (*Tsqlite3_column_text)(void * stmt, int iCol);

typedef void * __cdecl (*Tsqlite3_column_value)(void * stmt, int iCol);

typedef int __cdecl (*Tsqlite3_blob_open)(void * db, char * zDb, char * zTable, char * zColumn, __int64 iRow, int flags, void * &ppBlob);

typedef int __cdecl (*Tsqlite3_blob_close)(void * blob);

typedef int __cdecl (*Tsqlite3_blob_bytes)(void * blob);

typedef int __cdecl (*Tsqlite3_blob_read)(void * blob, void * Z, int N, int iOffset);

typedef int __cdecl (*Tsqlite3_blob_write)(void * blob, void * Z, int N, int iOffset);

typedef int __cdecl (*Tsqlite3_create_function)(void * db, System::PByte zFunctionName, int nArg, int eTextRep, void * pApp, Tsqlite3_func_callback xFunc, Tsqlite3_step_callback xStep, Tsqlite3_final_callback xFinal);

typedef void * __cdecl (*Tsqlite3_user_data)(void * context);

typedef void * __cdecl (*Tsqlite3_aggregate_context)(void * context, int nBytes);

typedef void * __cdecl (*Tsqlite3_context_db_handle)(void * context);

typedef void * __cdecl (*Tsqlite3_get_auxdata)(void * context, int N);

typedef void __cdecl (*Tsqlite3_set_auxdata)(void * context, int N, void * data, Tsqlite3_destroy_callback destr);

typedef int __cdecl (*Tsqlite3_auto_extension)(void * xEntryPoint);

typedef void __cdecl (*Tsqlite3_reset_auto_extension)(void);

typedef int __cdecl (*Tsqlite3_enable_load_extension)(void * db, int onoff);

typedef int __cdecl (*Tsqlite3_load_extension)(void * db, System::PByte zFile, System::PByte zProc, System::PByte &pzErrMsg);

typedef int __cdecl (*Tsqlite3_create_module)(void * db, char * zName, psqlite3_module module, void * userdata);

typedef int __cdecl (*Tsqlite3_create_module_v2)(void * db, char * zName, psqlite3_module module, void * userdata, Tsqlite3_destroy_callback destr);

typedef int __cdecl (*Tsqlite3_declare_vtab)(void * db, char * zCreateTable);

typedef int __cdecl (*Tsqlite3_overload_function)(void * db, char * zFuncName, int nArg);

typedef void * __cdecl (*Tsqlite3_value_blob)(void * value);

typedef int __cdecl (*Tsqlite3_value_bytes)(void * value);

typedef double __cdecl (*Tsqlite3_value_double)(void * value);

typedef int __cdecl (*Tsqlite3_value_int)(void * value);

typedef __int64 __cdecl (*Tsqlite3_value_int64)(void * value);

typedef System::PByte __cdecl (*Tsqlite3_value_text)(void * value);

typedef int __cdecl (*Tsqlite3_value_type)(void * value);

typedef int __cdecl (*Tsqlite3_value_numeric_type)(void * value);

typedef void __cdecl (*Tsqlite3_result_blob)(void * context, void * value, int nBytes, Tsqlite3_destroy_callback destr);

typedef void __cdecl (*Tsqlite3_result_blob64)(void * context, void * value, unsigned __int64 nBytes, Tsqlite3_destroy_callback destr);

typedef void __cdecl (*Tsqlite3_result_double)(void * context, double value);

typedef void __cdecl (*Tsqlite3_result_int)(void * context, int value);

typedef void __cdecl (*Tsqlite3_result_int64)(void * context, __int64 value);

typedef void __cdecl (*Tsqlite3_result_null)(void * context);

typedef void __cdecl (*Tsqlite3_result_text)(void * context, System::PByte value, int nBytes, Tsqlite3_destroy_callback destr);

typedef void __cdecl (*Tsqlite3_result_text64)(void * context, System::PByte value, unsigned __int64 nBytes, Tsqlite3_destroy_callback destr, System::Byte encoding);

typedef void __cdecl (*Tsqlite3_result_value)(void * context, void * value);

typedef void __cdecl (*Tsqlite3_result_zeroblob)(void * context, int n);

typedef void __cdecl (*Tsqlite3_result_error)(void * context, System::PByte msg, int nBytes);

typedef void __cdecl (*Tsqlite3_result_error_toobig)(void * context);

typedef void __cdecl (*Tsqlite3_result_error_nomem)(void * context);

typedef void __cdecl (*Tsqlite3_result_error_code)(void * context, int code);

typedef psqlite3_vfs __cdecl (*Tsqlite3_vfs_find)(char * zVfsName);

typedef int __cdecl (*Tsqlite3_vfs_register)(psqlite3_vfs pVfs, int makeDflt);

typedef int __cdecl (*Tsqlite3_vfs_unregister)(psqlite3_vfs pVfs);

typedef void * __cdecl (*Tsqlite3_backup_init)(void * pDest, System::PByte zDestName, void * pSource, System::PByte zSourceName);

typedef int __cdecl (*Tsqlite3_backup_step)(void * p, int nPage);

typedef int __cdecl (*Tsqlite3_backup_finish)(void * p);

typedef int __cdecl (*Tsqlite3_backup_remaining)(void * p);

typedef int __cdecl (*Tsqlite3_backup_pagecount)(void * p);

typedef void * __cdecl (*Tsqlite3_wal_hook)(void * db, Tsqlite3_wal_callback callback, void * userdata);

typedef int __cdecl (*Tsqlite3_wal_autocheckpoint)(void * db, int N);

typedef int __cdecl (*Tsqlite3_wal_checkpoint)(void * db, char * zDb);

typedef int __cdecl (*Tsqlite3_rtree_geometry_callback)(void * db, System::PByte zGeom, Tsqlite3_rtree_xGeom_callback xGeom, void * pContext);

typedef int __cdecl (*Tsqlite3_rtree_query_callback)(void * db, System::PByte zQueryFunc, Tsqlite3_rtree_xQuery_callback xQueryFunc, void * pContext, Tsqlite3_rtree_xDelUser_callback xDestructor);

typedef int __cdecl (*Tsqlite3_vtab_config)(void * db, int op, ...);

typedef int __cdecl (*Tsqlite3_vtab_on_conflict)(void * db);

typedef void __cdecl (*Tsqlite3_activate_see)(char * see);

typedef void __cdecl (*Tsqlite3CodecGetKey)(void * db, int nDb, System::PPointer zKey, System::PInteger nKey);

typedef int __cdecl (*Tsqlite3CodecAttach)(void * db, int nDb, void * zKey, int nKey);

typedef int __cdecl (*Tad_sqlite3GetCacheSize)(void * db);

typedef int __cdecl (*Tad_sqlite3GetEncoding)(void * db);

typedef int __fastcall (*Tad_sqlite3GetEncryptionMode)(void * db, char * &name, int &len);

typedef int __fastcall (*Tad_sqlite3GetEncryptionError)(void * db, char * &error, int &len, int &error_code);

typedef void __cdecl (*Tad_sqlite3Error)(void * db, int err_code, System::PByte zMessage);

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString C_CGSQLiteDll;
extern DELPHI_PACKAGE System::UnicodeString C_SQLiteDll;
extern DELPHI_PACKAGE System::UnicodeString C_BDBDll;
static constexpr System::Int8 NOT_WITHIN = System::Int8(0x0);
static constexpr System::Int8 PARTLY_WITHIN = System::Int8(0x1);
static constexpr System::Int8 FULLY_WITHIN = System::Int8(0x2);
static constexpr System::Int8 SQLITE_OPEN_READONLY = System::Int8(0x1);
static constexpr System::Int8 SQLITE_OPEN_READWRITE = System::Int8(0x2);
static constexpr System::Int8 SQLITE_OPEN_CREATE = System::Int8(0x4);
static constexpr System::Int8 SQLITE_OPEN_DELETEONCLOSE = System::Int8(0x8);
static constexpr System::Int8 SQLITE_OPEN_EXCLUSIVE = System::Int8(0x10);
static constexpr System::Word SQLITE_OPEN_MAIN_DB = System::Word(0x100);
static constexpr System::Word SQLITE_OPEN_TEMP_DB = System::Word(0x200);
static constexpr System::Word SQLITE_OPEN_TRANSIENT_DB = System::Word(0x400);
static constexpr System::Word SQLITE_OPEN_MAIN_JOURNAL = System::Word(0x800);
static constexpr System::Word SQLITE_OPEN_TEMP_JOURNAL = System::Word(0x1000);
static constexpr System::Word SQLITE_OPEN_SUBJOURNAL = System::Word(0x2000);
static constexpr System::Word SQLITE_OPEN_MASTER_JOURNAL = System::Word(0x4000);
static constexpr System::Word SQLITE_OPEN_NOMUTEX = System::Word(0x8000);
static constexpr int SQLITE_OPEN_FULLMUTEX = int(0x10000);
static constexpr int SQLITE_OPEN_SHAREDCACHE = int(0x20000);
static constexpr int SQLITE_OPEN_PRIVATECACHE = int(0x40000);
static constexpr int SQLITE_OPEN_WAL = int(0x80000);
static constexpr int SQLITE_OPEN_NOFOLLOW = int(0x1000000);
static constexpr System::Int8 SQLITE_DENY = System::Int8(0x1);
static constexpr System::Int8 SQLITE_IGNORE = System::Int8(0x2);
static constexpr System::Int8 SQLITE_STATUS_MEMORY_USED = System::Int8(0x0);
static constexpr System::Int8 SQLITE_STATUS_PAGECACHE_USED = System::Int8(0x1);
static constexpr System::Int8 SQLITE_STATUS_PAGECACHE_OVERFLOW = System::Int8(0x2);
static constexpr System::Int8 SQLITE_STATUS_SCRATCH_USED = System::Int8(0x3);
static constexpr System::Int8 SQLITE_STATUS_SCRATCH_OVERFLOW = System::Int8(0x4);
static constexpr System::Int8 SQLITE_STATUS_MALLOC_SIZE = System::Int8(0x5);
static constexpr System::Int8 SQLITE_STATUS_PARSER_STACK = System::Int8(0x6);
static constexpr System::Int8 SQLITE_STATUS_PAGECACHE_SIZE = System::Int8(0x7);
static constexpr System::Int8 SQLITE_STATUS_SCRATCH_SIZE = System::Int8(0x8);
static constexpr System::Int8 SQLITE_STATUS_MALLOC_COUNT = System::Int8(0x9);
static constexpr System::Int8 SQLITE_DBSTATUS_LOOKASIDE_USED = System::Int8(0x0);
static constexpr System::Int8 SQLITE_DBSTATUS_CACHE_USED = System::Int8(0x1);
static constexpr System::Int8 SQLITE_DBSTATUS_SCHEMA_USED = System::Int8(0x2);
static constexpr System::Int8 SQLITE_DBSTATUS_STMT_USED = System::Int8(0x3);
static constexpr System::Int8 SQLITE_DBSTATUS_LOOKASIDE_HIT = System::Int8(0x4);
static constexpr System::Int8 SQLITE_DBSTATUS_LOOKASIDE_MISS_SIZE = System::Int8(0x5);
static constexpr System::Int8 SQLITE_DBSTATUS_LOOKASIDE_MISS_FULL = System::Int8(0x6);
static constexpr System::Int8 SQLITE_DBSTATUS_CACHE_HIT = System::Int8(0x7);
static constexpr System::Int8 SQLITE_DBSTATUS_CACHE_MISS = System::Int8(0x8);
static constexpr System::Int8 SQLITE_DBSTATUS_CACHE_WRITE = System::Int8(0x9);
static constexpr System::Int8 SQLITE_DBSTATUS_DEFERRED_FKS = System::Int8(0xa);
static constexpr System::Int8 SQLITE_DBSTATUS_MAX = System::Int8(0xa);
static constexpr System::Int8 SQLITE_STMTSTATUS_FULLSCAN_STEP = System::Int8(0x1);
static constexpr System::Int8 SQLITE_STMTSTATUS_SORT = System::Int8(0x2);
static constexpr System::Int8 SQLITE_STMTSTATUS_AUTOINDEX = System::Int8(0x3);
static constexpr System::Int8 SQLITE_STMTSTATUS_VM_STEP = System::Int8(0x4);
static constexpr System::Int8 SQLITE_STMTSTATUS_REPREPARE = System::Int8(0x5);
static constexpr System::Int8 SQLITE_STMTSTATUS_RUN = System::Int8(0x6);
static constexpr System::Int8 SQLITE_STMTSTATUS_MEMUSED = System::Int8(0x63);
static constexpr System::Int8 SQLITE_OK = System::Int8(0x0);
static constexpr System::Int8 SQLITE_ERROR = System::Int8(0x1);
static constexpr System::Int8 SQLITE_INTERNAL = System::Int8(0x2);
static constexpr System::Int8 SQLITE_PERM = System::Int8(0x3);
static constexpr System::Int8 SQLITE_ABORT = System::Int8(0x4);
static constexpr System::Int8 SQLITE_BUSY = System::Int8(0x5);
static constexpr System::Int8 SQLITE_LOCKED = System::Int8(0x6);
static constexpr System::Int8 SQLITE_NOMEM = System::Int8(0x7);
static constexpr System::Int8 SQLITE_READONLY = System::Int8(0x8);
static constexpr System::Int8 SQLITE_INTERRUPT = System::Int8(0x9);
static constexpr System::Int8 SQLITE_IOERR = System::Int8(0xa);
static constexpr System::Int8 SQLITE_CORRUPT = System::Int8(0xb);
static constexpr System::Int8 SQLITE_NOTFOUND = System::Int8(0xc);
static constexpr System::Int8 SQLITE_FULL = System::Int8(0xd);
static constexpr System::Int8 SQLITE_CANTOPEN = System::Int8(0xe);
static constexpr System::Int8 SQLITE_PROTOCOL = System::Int8(0xf);
static constexpr System::Int8 SQLITE_EMPTY = System::Int8(0x10);
static constexpr System::Int8 SQLITE_SCHEMA = System::Int8(0x11);
static constexpr System::Int8 SQLITE_TOOBIG = System::Int8(0x12);
static constexpr System::Int8 SQLITE_CONSTRAINT = System::Int8(0x13);
static constexpr System::Int8 SQLITE_MISMATCH = System::Int8(0x14);
static constexpr System::Int8 SQLITE_MISUSE = System::Int8(0x15);
static constexpr System::Int8 SQLITE_NOLFS = System::Int8(0x16);
static constexpr System::Int8 SQLITE_AUTH = System::Int8(0x17);
static constexpr System::Int8 SQLITE_FORMAT = System::Int8(0x18);
static constexpr System::Int8 SQLITE_RANGE = System::Int8(0x19);
static constexpr System::Int8 SQLITE_NOTADB = System::Int8(0x1a);
static constexpr System::Int8 SQLITE_NOTICE = System::Int8(0x1b);
static constexpr System::Int8 SQLITE_WARNING = System::Int8(0x1c);
static constexpr System::Int8 SQLITE_ROW = System::Int8(0x64);
static constexpr System::Int8 SQLITE_DONE = System::Int8(0x65);
static constexpr System::Word SQLITE_IOERR_READ = System::Word(0x10a);
static constexpr System::Word SQLITE_IOERR_SHORT_READ = System::Word(0x20a);
static constexpr System::Word SQLITE_IOERR_WRITE = System::Word(0x30a);
static constexpr System::Word SQLITE_IOERR_FSYNC = System::Word(0x40a);
static constexpr System::Word SQLITE_IOERR_DIR_FSYNC = System::Word(0x50a);
static constexpr System::Word SQLITE_IOERR_TRUNCATE = System::Word(0x60a);
static constexpr System::Word SQLITE_IOERR_FSTAT = System::Word(0x70a);
static constexpr System::Word SQLITE_IOERR_UNLOCK = System::Word(0x80a);
static constexpr System::Word SQLITE_IOERR_RDLOCK = System::Word(0x90a);
static constexpr System::Word SQLITE_IOERR_DELETE = System::Word(0xa0a);
static constexpr System::Word SQLITE_IOERR_BLOCKED = System::Word(0xb0a);
static constexpr System::Word SQLITE_IOERR_NOMEM = System::Word(0xc0a);
static constexpr System::Word SQLITE_IOERR_ACCESS = System::Word(0xd0a);
static constexpr System::Word SQLITE_IOERR_CHECKRESERVEDLOCK = System::Word(0xe0a);
static constexpr System::Word SQLITE_IOERR_LOCK = System::Word(0xf0a);
static constexpr System::Word SQLITE_IOERR_CLOSE = System::Word(0x100a);
static constexpr System::Word SQLITE_IOERR_DIR_CLOSE = System::Word(0x110a);
static constexpr System::Word SQLITE_IOERR_SHMOPEN = System::Word(0x120a);
static constexpr System::Word SQLITE_IOERR_SHMSIZE = System::Word(0x130a);
static constexpr System::Word SQLITE_IOERR_SHMLOCK = System::Word(0x140a);
static constexpr System::Word SQLITE_IOERR_SHMMAP = System::Word(0x150a);
static constexpr System::Word SQLITE_IOERR_SEEK = System::Word(0x160a);
static constexpr System::Word SQLITE_IOERR_DELETE_NOENT = System::Word(0x170a);
static constexpr System::Word SQLITE_IOERR_MMAP = System::Word(0x180a);
static constexpr System::Word SQLITE_IOERR_GETTEMPPATH = System::Word(0x190a);
static constexpr System::Word SQLITE_IOERR_CONVPATH = System::Word(0x1a0a);
static constexpr System::Word SQLITE_IOERR_VNODE = System::Word(0x1b0a);
static constexpr System::Word SQLITE_LOCKED_SHAREDCACHE = System::Word(0x106);
static constexpr System::Word SQLITE_BUSY_RECOVERY = System::Word(0x105);
static constexpr System::Word SQLITE_BUSY_SNAPSHOT = System::Word(0x205);
static constexpr System::Word SQLITE_CANTOPEN_NOTEMPDIR = System::Word(0x10e);
static constexpr System::Word SQLITE_CANTOPEN_ISDIR = System::Word(0x20e);
static constexpr System::Word SQLITE_CANTOPEN_FULLPATH = System::Word(0x30e);
static constexpr System::Word SQLITE_CANTOPEN_CONVPATH = System::Word(0x40e);
static constexpr System::Word SQLITE_CORRUPT_VTAB = System::Word(0x10b);
static constexpr System::Word SQLITE_READONLY_RECOVERY = System::Word(0x108);
static constexpr System::Word SQLITE_READONLY_CANTLOCK = System::Word(0x208);
static constexpr System::Word SQLITE_READONLY_ROLLBACK = System::Word(0x308);
static constexpr System::Word SQLITE_READONLY_DBMOVED = System::Word(0x408);
static constexpr System::Word SQLITE_ABORT_ROLLBACK = System::Word(0x204);
static constexpr System::Word SQLITE_CONSTRAINT_CHECK = System::Word(0x113);
static constexpr System::Word SQLITE_CONSTRAINT_COMMITHOOK = System::Word(0x213);
static constexpr System::Word SQLITE_CONSTRAINT_FOREIGNKEY = System::Word(0x313);
static constexpr System::Word SQLITE_CONSTRAINT_FUNCTION = System::Word(0x413);
static constexpr System::Word SQLITE_CONSTRAINT_NOTNULL = System::Word(0x513);
static constexpr System::Word SQLITE_CONSTRAINT_PRIMARYKEY = System::Word(0x613);
static constexpr System::Word SQLITE_CONSTRAINT_TRIGGER = System::Word(0x713);
static constexpr System::Word SQLITE_CONSTRAINT_UNIQUE = System::Word(0x813);
static constexpr System::Word SQLITE_CONSTRAINT_VTAB = System::Word(0x913);
static constexpr System::Word SQLITE_CONSTRAINT_ROWID = System::Word(0xa13);
static constexpr System::Word SQLITE_NOTICE_RECOVER_WAL = System::Word(0x11b);
static constexpr System::Word SQLITE_NOTICE_RECOVER_ROLLBACK = System::Word(0x21b);
static constexpr System::Word SQLITE_WARNING_AUTOINDEX = System::Word(0x11c);
static constexpr System::Word SQLITE_AUTH_USER = System::Word(0x117);
static constexpr System::Int8 SQLITE_FALSE = System::Int8(0x0);
static constexpr System::Int8 SQLITE_TRUE = System::Int8(0x1);
static constexpr System::Int8 SQLITE_INTEGER = System::Int8(0x1);
static constexpr System::Int8 SQLITE_FLOAT = System::Int8(0x2);
static constexpr System::Int8 SQLITE_TEXT = System::Int8(0x3);
static constexpr System::Int8 SQLITE_BLOB = System::Int8(0x4);
static constexpr System::Int8 SQLITE_NULL = System::Int8(0x5);
static constexpr System::Int8 SQLITE_CREATE_INDEX = System::Int8(0x1);
static constexpr System::Int8 SQLITE_CREATE_TABLE = System::Int8(0x2);
static constexpr System::Int8 SQLITE_CREATE_TEMP_INDEX = System::Int8(0x3);
static constexpr System::Int8 SQLITE_CREATE_TEMP_TABLE = System::Int8(0x4);
static constexpr System::Int8 SQLITE_CREATE_TEMP_TRIGGER = System::Int8(0x5);
static constexpr System::Int8 SQLITE_CREATE_TEMP_VIEW = System::Int8(0x6);
static constexpr System::Int8 SQLITE_CREATE_TRIGGER = System::Int8(0x7);
static constexpr System::Int8 SQLITE_CREATE_VIEW = System::Int8(0x8);
static constexpr System::Int8 SQLITE_DELETE = System::Int8(0x9);
static constexpr System::Int8 SQLITE_DROP_INDEX = System::Int8(0xa);
static constexpr System::Int8 SQLITE_DROP_TABLE = System::Int8(0xb);
static constexpr System::Int8 SQLITE_DROP_TEMP_INDEX = System::Int8(0xc);
static constexpr System::Int8 SQLITE_DROP_TEMP_TABLE = System::Int8(0xd);
static constexpr System::Int8 SQLITE_DROP_TEMP_TRIGGER = System::Int8(0xe);
static constexpr System::Int8 SQLITE_DROP_TEMP_VIEW = System::Int8(0xf);
static constexpr System::Int8 SQLITE_DROP_TRIGGER = System::Int8(0x10);
static constexpr System::Int8 SQLITE_DROP_VIEW = System::Int8(0x11);
static constexpr System::Int8 SQLITE_INSERT = System::Int8(0x12);
static constexpr System::Int8 SQLITE_PRAGMA = System::Int8(0x13);
static constexpr System::Int8 SQLITE_READ = System::Int8(0x14);
static constexpr System::Int8 SQLITE_SELECT = System::Int8(0x15);
static constexpr System::Int8 SQLITE_TRANSACTION = System::Int8(0x16);
static constexpr System::Int8 SQLITE_UPDATE = System::Int8(0x17);
static constexpr System::Int8 SQLITE_ATTACH = System::Int8(0x18);
static constexpr System::Int8 SQLITE_DETACH = System::Int8(0x19);
static constexpr System::Int8 SQLITE_ALTER_TABLE = System::Int8(0x1a);
static constexpr System::Int8 SQLITE_REINDEX = System::Int8(0x1b);
static constexpr System::Int8 SQLITE_ANALYZE = System::Int8(0x1c);
static constexpr System::Int8 SQLITE_CREATE_VTABLE = System::Int8(0x1d);
static constexpr System::Int8 SQLITE_DROP_VTABLE = System::Int8(0x1e);
static constexpr System::Int8 SQLITE_FUNCTION = System::Int8(0x1f);
static constexpr System::Int8 SQLITE_SAVEPOINT = System::Int8(0x20);
static constexpr System::Int8 SQLITE_COPY = System::Int8(0x0);
static constexpr System::Int8 SQLITE_RECURSIVE = System::Int8(0x21);
static constexpr System::Int8 SQLITE_CONFIG_SINGLETHREAD = System::Int8(0x1);
static constexpr System::Int8 SQLITE_CONFIG_MULTITHREAD = System::Int8(0x2);
static constexpr System::Int8 SQLITE_CONFIG_SERIALIZED = System::Int8(0x3);
static constexpr System::Int8 SQLITE_CONFIG_MALLOC = System::Int8(0x4);
static constexpr System::Int8 SQLITE_CONFIG_GETMALLOC = System::Int8(0x5);
static constexpr System::Int8 SQLITE_CONFIG_SCRATCH = System::Int8(0x6);
static constexpr System::Int8 SQLITE_CONFIG_PAGECACHE = System::Int8(0x7);
static constexpr System::Int8 SQLITE_CONFIG_HEAP = System::Int8(0x8);
static constexpr System::Int8 SQLITE_CONFIG_MEMSTATUS = System::Int8(0x9);
static constexpr System::Int8 SQLITE_CONFIG_MUTEX = System::Int8(0xa);
static constexpr System::Int8 SQLITE_CONFIG_GETMUTEX = System::Int8(0xb);
static constexpr System::Int8 SQLITE_CONFIG_CHUNKALLOC = System::Int8(0xc);
static constexpr System::Int8 SQLITE_CONFIG_PCACHE = System::Int8(0xe);
static constexpr System::Int8 SQLITE_CONFIG_GETPCACHE = System::Int8(0xf);
static constexpr System::Int8 SQLITE_CONFIG_LOG = System::Int8(0x10);
static constexpr System::Int8 SQLITE_CONFIG_URI = System::Int8(0x11);
static constexpr System::Int8 SQLITE_CONFIG_PCACHE2 = System::Int8(0x12);
static constexpr System::Int8 SQLITE_CONFIG_GETPCACHE2 = System::Int8(0x13);
static constexpr System::Int8 SQLITE_CONFIG_COVERING_INDEX_SCAN = System::Int8(0x14);
static constexpr System::Int8 SQLITE_CONFIG_SQLLOG = System::Int8(0x15);
static constexpr System::Int8 SQLITE_CONFIG_MMAP_SIZE = System::Int8(0x16);
static constexpr System::Int8 SQLITE_CONFIG_WIN32_HEAPSIZE = System::Int8(0x17);
static constexpr System::Int8 SQLITE_CONFIG_PCACHE_HDRSZ = System::Int8(0x18);
static constexpr System::Int8 SQLITE_CONFIG_PMASZ = System::Int8(0x19);
static constexpr System::Word SQLITE_DBCONFIG_MAINDBNAME = System::Word(0x3e8);
static constexpr System::Word SQLITE_DBCONFIG_LOOKASIDE = System::Word(0x3e9);
static constexpr System::Word SQLITE_DBCONFIG_ENABLE_FKEY = System::Word(0x3ea);
static constexpr System::Word SQLITE_DBCONFIG_ENABLE_TRIGGER = System::Word(0x3eb);
static constexpr System::Word SQLITE_DBCONFIG_ENABLE_FTS3_TOKENIZER = System::Word(0x3ec);
static constexpr System::Word SQLITE_DBCONFIG_ENABLE_LOAD_EXTENSION = System::Word(0x3ed);
static constexpr System::Word SQLITE_DBCONFIG_NO_CKPT_ON_CLOSE = System::Word(0x3ee);
static constexpr System::Word SQLITE_DBCONFIG_ENABLE_QPSG = System::Word(0x3ef);
static constexpr System::Word SQLITE_DBCONFIG_TRIGGER_EQP = System::Word(0x3f0);
static constexpr System::Word SQLITE_DBCONFIG_RESET_DATABASE = System::Word(0x3f1);
static constexpr System::Word SQLITE_DBCONFIG_DEFENSIVE = System::Word(0x3f2);
static constexpr System::Word SQLITE_DBCONFIG_WRITABLE_SCHEMA = System::Word(0x3f3);
static constexpr System::Word SQLITE_DBCONFIG_LEGACY_ALTER_TABLE = System::Word(0x3f4);
static constexpr System::Word SQLITE_DBCONFIG_DQS_DML = System::Word(0x3f5);
static constexpr System::Word SQLITE_DBCONFIG_DQS_DDL = System::Word(0x3f6);
static constexpr System::Word SQLITE_DBCONFIG_ENABLE_VIEW = System::Word(0x3f7);
static constexpr System::Word SQLITE_DBCONFIG_LEGACY_FILE_FORMAT = System::Word(0x3f8);
static constexpr System::Word SQLITE_DBCONFIG_TRUSTED_SCHEMA = System::Word(0x3f9);
static constexpr System::Word SQLITE_DBCONFIG_MAX = System::Word(0x3f9);
static constexpr System::Int8 SQLITE_INDEX_CONSTRAINT_EQ = System::Int8(0x2);
static constexpr System::Int8 SQLITE_INDEX_CONSTRAINT_GT = System::Int8(0x4);
static constexpr System::Int8 SQLITE_INDEX_CONSTRAINT_LE = System::Int8(0x8);
static constexpr System::Int8 SQLITE_INDEX_CONSTRAINT_LT = System::Int8(0x10);
static constexpr System::Int8 SQLITE_INDEX_CONSTRAINT_GE = System::Int8(0x20);
static constexpr System::Int8 SQLITE_INDEX_CONSTRAINT_MATCH = System::Int8(0x40);
static constexpr System::Int8 SQLITE_INDEX_CONSTRAINT_LIKE = System::Int8(0x41);
static constexpr System::Int8 SQLITE_INDEX_CONSTRAINT_GLOB = System::Int8(0x42);
static constexpr System::Int8 SQLITE_INDEX_CONSTRAINT_REGEXP = System::Int8(0x43);
static constexpr System::Int8 SQLITE_INDEX_CONSTRAINT_NE = System::Int8(0x44);
static constexpr System::Int8 SQLITE_INDEX_CONSTRAINT_ISNOT = System::Int8(0x45);
static constexpr System::Int8 SQLITE_INDEX_CONSTRAINT_ISNOTNULL = System::Int8(0x46);
static constexpr System::Int8 SQLITE_INDEX_CONSTRAINT_ISNULL = System::Int8(0x47);
static constexpr System::Int8 SQLITE_INDEX_CONSTRAINT_IS = System::Int8(0x48);
static constexpr System::Int8 SQLITE_INDEX_SCAN_UNIQUE = System::Int8(0x1);
static constexpr HRESULT E_SQLITE_VTAB_RES = HRESULT(32768);
static constexpr System::Int8 SQLITE_LIMIT_LENGTH = System::Int8(0x0);
static constexpr System::Int8 SQLITE_LIMIT_SQL_LENGTH = System::Int8(0x1);
static constexpr System::Int8 SQLITE_LIMIT_COLUMN = System::Int8(0x2);
static constexpr System::Int8 SQLITE_LIMIT_EXPR_DEPTH = System::Int8(0x3);
static constexpr System::Int8 SQLITE_LIMIT_COMPOUND_SELECT = System::Int8(0x4);
static constexpr System::Int8 SQLITE_LIMIT_VDBE_OP = System::Int8(0x5);
static constexpr System::Int8 SQLITE_LIMIT_FUNCTION_ARG = System::Int8(0x6);
static constexpr System::Int8 SQLITE_LIMIT_ATTACHED = System::Int8(0x7);
static constexpr System::Int8 SQLITE_LIMIT_LIKE_PATTERN_LENGTH = System::Int8(0x8);
static constexpr System::Int8 SQLITE_LIMIT_VARIABLE_NUMBER = System::Int8(0x9);
static constexpr System::Int8 SQLITE_LIMIT_TRIGGER_DEPTH = System::Int8(0xa);
static constexpr System::Int8 SQLITE_LIMIT_WORKER_THREADS = System::Int8(0xb);
extern DELPHI_PACKAGE Tsqlite3_destroy_callback SQLITE_STATIC;
extern DELPHI_PACKAGE Tsqlite3_destroy_callback SQLITE_TRANSIENT;
static constexpr System::Int8 SQLITE_UTF16NATIVE = System::Int8(0x0);
static constexpr System::Int8 SQLITE_UTF8 = System::Int8(0x1);
static constexpr System::Int8 SQLITE_UTF16LE = System::Int8(0x2);
static constexpr System::Int8 SQLITE_UTF16BE = System::Int8(0x3);
static constexpr System::Int8 SQLITE_UTF16 = System::Int8(0x4);
static constexpr System::Int8 SQLITE_ANY = System::Int8(0x5);
static constexpr System::Int8 SQLITE_UTF16_ALIGNED = System::Int8(0x8);
static constexpr System::Word SQLITE_DETERMINISTIC = System::Word(0x800);
static constexpr int SQLITE_DIRECTONLY = int(0x80000);
static constexpr int SQLITE_SUBTYPE = int(0x100000);
static constexpr int SQLITE_INNOCUOUS = int(0x200000);
static constexpr System::Int8 SQLITE_VTAB_DS_ROWID_IDX = System::Int8(0x1);
static constexpr System::Int8 SQLITE_VTAB_DS_KEY_IDX = System::Int8(0x2);
static constexpr System::Int8 SQLITE_VTAB_DS_ORD_IDX = System::Int8(0x4);
static constexpr System::Int8 SQLITE_VTAB_CONSTRAINT_SUPPORT = System::Int8(0x1);
static constexpr System::Int8 SQLITE_VTAB_INNOCUOUS = System::Int8(0x2);
static constexpr System::Int8 SQLITE_VTAB_DIRECTONLY = System::Int8(0x3);
static constexpr System::Int8 SQLITE_ROLLBACK = System::Int8(0x1);
static constexpr System::Int8 SQLITE_FAIL = System::Int8(0x3);
static constexpr System::Int8 SQLITE_REPLACE = System::Int8(0x5);
}	/* namespace Sqlitecli */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_SQLITECLI)
using namespace Firedac::Phys::Sqlitecli;
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
#endif	// Firedac_Phys_SqlitecliHPP
