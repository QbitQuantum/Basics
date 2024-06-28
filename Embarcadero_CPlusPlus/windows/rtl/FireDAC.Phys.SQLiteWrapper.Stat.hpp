// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.SQLiteWrapper.Stat.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_Sqlitewrapper_StatHPP
#define Firedac_Phys_Sqlitewrapper_StatHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Phys.SQLiteCli.hpp>
#include <FireDAC.Phys.SQLiteWrapper.hpp>
#include <FireDAC.Stan.Util.hpp>

//-- user supplied -----------------------------------------------------------
#ifndef _WIN64
#pragma link "FireDAC.Phys.SQLiteWrapper.Stat.obj"
#else /* _WIN64 */
#pragma link "FireDAC.Phys.SQLiteWrapper.Stat.o"
#endif /* _WIN64 */

namespace Firedac
{
namespace Phys
{
namespace Sqlitewrapper
{
namespace Stat
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSQLiteLibStat;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TSQLiteLibStat : public Firedac::Phys::Sqlitewrapper::TSQLiteLib
{
	typedef Firedac::Phys::Sqlitewrapper::TSQLiteLib inherited;
	
protected:
	virtual int __fastcall GetDefaultSharedCacheMode();
	virtual void __fastcall LoadEntries();
	
public:
	virtual void __fastcall Load(const System::UnicodeString AVendorHome, const System::UnicodeString AVendorLib)/* overload */;
	virtual void __fastcall Unload();
public:
	/* TSQLiteLib.Create */ inline __fastcall TSQLiteLibStat(System::TObject* AOwningObj) : Firedac::Phys::Sqlitewrapper::TSQLiteLib(AOwningObj) { }
	/* TSQLiteLib.Destroy */ inline __fastcall virtual ~TSQLiteLibStat() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#ifndef _WIN64
#define C_FD_SQLiteLib L"sqlite3_x86.obj"
#else /* _WIN64 */
#define C_FD_SQLiteLib L"sqlite3_x64.obj"
#endif /* _WIN64 */
extern DELPHI_PACKAGE int __cdecl sqlite3CodecAttach(void * db, int nDb, void * zKey, int nKey);
extern DELPHI_PACKAGE int __cdecl sqlite3_key(void * db, System::PByte zKey, int nKey);
extern DELPHI_PACKAGE int __cdecl sqlite3_key_v2(void * db, System::PByte zDbName, System::PByte zKey, int nKey);
extern DELPHI_PACKAGE int __cdecl sqlite3_rekey(void * db, System::PByte zKey, int nKey);
extern DELPHI_PACKAGE int __cdecl sqlite3_rekey_v2(void * db, System::PByte zDbName, System::PByte zKey, int nKey);
extern DELPHI_PACKAGE void __cdecl sqlite3_activate_see(char * see);
extern DELPHI_PACKAGE void __cdecl sqlite3CodecGetKey(void * db, int nDb, System::PPointer zKey, System::PInteger nKey);
extern DELPHI_PACKAGE int __fastcall ad_sqlite3GetEncryptionMode(void * db, char * &name, int &len);
extern DELPHI_PACKAGE int __fastcall ad_sqlite3GetEncryptionError(void * db, char * &error, int &len, int &error_code);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_status(int op, int &pCurrent, int &pHighwater, int resetFlag);
extern DELPHI_PACKAGE int __cdecl sqlite3_db_status(void * db, int op, int &pCurrent, int &pHighwater, int resetFlag);
extern DELPHI_PACKAGE Firedac::Phys::Sqlitecli::psqlite3_vfs __cdecl sqlite3_vfs_find(char * zVfsName);
extern DELPHI_PACKAGE int __cdecl sqlite3_vfs_register(Firedac::Phys::Sqlitecli::psqlite3_vfs pVfs, int makeDflt);
extern DELPHI_PACKAGE int __cdecl sqlite3_vfs_unregister(Firedac::Phys::Sqlitecli::psqlite3_vfs pVfs);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE int __cdecl sqlite3_release_memory(int amount);
#ifndef _WIN64
extern DELPHI_PACKAGE void __cdecl sqlite3_soft_heap_limit(int amount);
extern DELPHI_PACKAGE __int64 __cdecl sqlite3_memory_used(void);
extern DELPHI_PACKAGE __int64 __cdecl sqlite3_memory_highwater(int resetFlag);
extern DELPHI_PACKAGE void * __cdecl sqlite3_malloc(int n);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE void __cdecl sqlite3_free(void * APtr);
extern DELPHI_PACKAGE int __cdecl sqlite3_enable_shared_cache(int onoff);
#ifndef _WIN64
extern DELPHI_PACKAGE void * __cdecl sqlite3_backup_init(void * pDest, System::PByte zDestName, void * pSource, System::PByte zSourceName);
extern DELPHI_PACKAGE int __cdecl sqlite3_backup_step(void * p, int nPage);
extern DELPHI_PACKAGE int __cdecl sqlite3_backup_finish(void * p);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE int __cdecl sqlite3_backup_remaining(void * p);
extern DELPHI_PACKAGE int __cdecl sqlite3_backup_pagecount(void * p);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_finalize(void * stmt);
extern DELPHI_PACKAGE int __cdecl sqlite3_reset(void * stmt);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE int __cdecl sqlite3_clear_bindings(void * stmt);
#ifndef _WIN64
extern DELPHI_PACKAGE void * __cdecl sqlite3_value_blob(void * value);
extern DELPHI_PACKAGE int __cdecl sqlite3_value_bytes(void * value);
extern DELPHI_PACKAGE int __cdecl sqlite3_value_bytes16(void * value);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE double __cdecl sqlite3_value_double(void * value);
extern DELPHI_PACKAGE int __cdecl sqlite3_value_int(void * value);
extern DELPHI_PACKAGE __int64 __cdecl sqlite3_value_int64(void * value);
#ifndef _WIN64
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_value_text(void * value);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_value_text16(void * value);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE int __cdecl sqlite3_value_type(void * value);
#ifndef _WIN64
extern DELPHI_PACKAGE void __cdecl sqlite3_result_blob(void * context, void * value, int nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_blob64(void * context, void * value, unsigned __int64 nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE void __cdecl sqlite3_result_double(void * context, double value);
#ifndef _WIN64
extern DELPHI_PACKAGE void __cdecl sqlite3_result_error(void * context, System::PByte msg, int nBytes);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_error16(void * context, System::PByte msg, int nBytes);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE void __cdecl sqlite3_result_int(void * context, int value);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_int64(void * context, __int64 value);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_null(void * context);
#ifndef _WIN64
extern DELPHI_PACKAGE void __cdecl sqlite3_result_text(void * context, System::PByte value, int nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_text64(void * context, System::PByte value, unsigned __int64 nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr, System::Byte encoding);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_text16(void * context, System::PByte value, int nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_value(void * context, void * value);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE void __cdecl sqlite3_result_zeroblob(void * context, int n);
#ifndef _WIN64
extern DELPHI_PACKAGE void __cdecl sqlite3_result_error_code(void * context, int code);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_error_toobig(void * context);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE void __cdecl sqlite3_result_error_nomem(void * context);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_step(void * stmt);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE void * __cdecl sqlite3_user_data(void * context);
extern DELPHI_PACKAGE void * __cdecl sqlite3_context_db_handle(void * context);
#ifndef _WIN64
extern DELPHI_PACKAGE void * __cdecl sqlite3_aggregate_context(void * context, int nBytes);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE void * __cdecl sqlite3_get_auxdata(void * context, int N);
#ifndef _WIN64
extern DELPHI_PACKAGE void __cdecl sqlite3_set_auxdata(void * context, int N, void * data, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE int __cdecl sqlite3_column_count(void * stmt);
#ifndef _WIN64
extern DELPHI_PACKAGE void * __cdecl sqlite3_column_blob(void * stmt, int iCol);
extern DELPHI_PACKAGE int __cdecl sqlite3_column_bytes(void * stmt, int iCol);
extern DELPHI_PACKAGE int __cdecl sqlite3_column_bytes16(void * stmt, int iCol);
extern DELPHI_PACKAGE double __cdecl sqlite3_column_double(void * stmt, int iCol);
extern DELPHI_PACKAGE int __cdecl sqlite3_column_int(void * stmt, int iCol);
extern DELPHI_PACKAGE __int64 __cdecl sqlite3_column_int64(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_text(void * stmt, int iCol);
extern DELPHI_PACKAGE void * __cdecl sqlite3_column_value(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_text16(void * stmt, int iCol);
extern DELPHI_PACKAGE int __cdecl sqlite3_column_type(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_name(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_name16(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_decltype(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_decltype16(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_database_name(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_database_name16(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_table_name(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_table_name16(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_origin_name(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_origin_name16(void * stmt, int iCol);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_blob(void * stmt, int index, void * value, int nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_blob64(void * stmt, int index, void * value, unsigned __int64 nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_double(void * stmt, int index, double value);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_int(void * stmt, int index, int value);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_int64(void * stmt, int index, __int64 value);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_null(void * stmt, int index);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_text(void * stmt, int index, System::PByte value, int nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_text64(void * stmt, int index, System::PByte value, unsigned __int64 nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr, System::Byte encoding);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_text16(void * stmt, int index, System::PByte value, int nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_value(void * stmt, int index, void * value);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_zeroblob(void * stmt, int index, int nBytes);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_parameter_count(void * stmt);
extern DELPHI_PACKAGE char * __cdecl sqlite3_bind_parameter_name(void * stmt, int index);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_parameter_index(void * stmt, char * zName);
extern DELPHI_PACKAGE int __cdecl sqlite3_stmt_readonly(void * stmt);
extern DELPHI_PACKAGE int __cdecl sqlite3_stmt_busy(void * stmt);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_stmt_status(void * stmt, int op, int resetFlg);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE int __cdecl sqlite3_value_numeric_type(void * value);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_blob_open(void * db, char * zDb, char * zTable, char * zColumn, __int64 iRow, int flags, void * &ppBlob);
extern DELPHI_PACKAGE int __cdecl sqlite3_blob_close(void * blob);
extern DELPHI_PACKAGE int __cdecl sqlite3_blob_read(void * blob, void * Z, int N, int iOffset);
extern DELPHI_PACKAGE int __cdecl sqlite3_blob_write(void * blob, void * Z, int N, int iOffset);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE int __cdecl sqlite3_blob_bytes(void * blob);
extern DELPHI_PACKAGE int __cdecl sqlite3_set_authorizer(void * db, Firedac::Phys::Sqlitecli::Tsqlite3_auth_callback xAuth, void * userdata);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_exec(void * db, System::PByte zSql, void * callback, void * data, Firedac::Stan::Intf::PPByte errmsg);
extern DELPHI_PACKAGE int __cdecl sqlite3_load_extension(void * db, System::PByte zFile, System::PByte zProc, System::PByte &pzErrMsg);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE int __cdecl sqlite3_enable_load_extension(void * db, int onoff);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_auto_extension(void * xEntryPoint);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE void __cdecl sqlite3_reset_auto_extension(void);
extern DELPHI_PACKAGE int __cdecl sqlite3_prepare(void * db, System::PByte zSql, int nByte, void * &ppStmt, System::PByte &pzTail);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_prepare_v2(void * db, System::PByte zSql, int nByte, void * &ppStmt, System::PByte &pzTail);
extern DELPHI_PACKAGE int __cdecl sqlite3_prepare16(void * db, System::PByte zSql, int nByte, void * &ppStmt, System::PByte &pzTail);
extern DELPHI_PACKAGE int __cdecl sqlite3_prepare16_v2(void * db, System::PByte zSql, int nByte, void * &ppStmt, System::PByte &pzTail);
extern DELPHI_PACKAGE int __cdecl sqlite3_create_module(void * db, char * zName, Firedac::Phys::Sqlitecli::psqlite3_module module, void * userdata);
extern DELPHI_PACKAGE int __cdecl sqlite3_create_module_v2(void * db, char * zName, Firedac::Phys::Sqlitecli::psqlite3_module module, void * userdata, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE int __cdecl sqlite3_declare_vtab(void * db, char * zCreateTable);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE int __cdecl sqlite3_vtab_on_conflict(void * db);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_vtab_config(void * db, int op, ...);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE char * __cdecl sqlite3_libversion(void);
extern DELPHI_PACKAGE int __cdecl sqlite3_libversion_number(void);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_initialize(void);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE int __cdecl sqlite3_shutdown(void);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_config(int option, ...);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE __int64 __cdecl sqlite3_last_insert_rowid(void * db);
extern DELPHI_PACKAGE int __cdecl sqlite3_changes(void * db);
extern DELPHI_PACKAGE int __cdecl sqlite3_total_changes(void * db);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_close(void * db);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE int __cdecl sqlite3_busy_handler(void * db, Firedac::Phys::Sqlitecli::Tsqlite3_busy_callback callback, void * userdata);
extern DELPHI_PACKAGE void __cdecl sqlite3_progress_handler(void * db, int nOpers, Firedac::Phys::Sqlitecli::Tsqlite3_progress_callback callback, void * userdata);
extern DELPHI_PACKAGE int __cdecl sqlite3_busy_timeout(void * db, int ms);
extern DELPHI_PACKAGE void __cdecl sqlite3_interrupt(void * db);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_create_function(void * db, System::PByte zFunctionName, int nArg, int eTextRep, void * pApp, Firedac::Phys::Sqlitecli::Tsqlite3_func_callback xFunc, Firedac::Phys::Sqlitecli::Tsqlite3_step_callback xStep, Firedac::Phys::Sqlitecli::Tsqlite3_final_callback xFinal);
extern DELPHI_PACKAGE int __cdecl sqlite3_create_function16(void * db, System::PByte zFunctionName, int nArg, int eTextRep, void * pApp, Firedac::Phys::Sqlitecli::Tsqlite3_func_callback xFunc, Firedac::Phys::Sqlitecli::Tsqlite3_step_callback xStep, Firedac::Phys::Sqlitecli::Tsqlite3_final_callback xFinal);
extern DELPHI_PACKAGE int __cdecl sqlite3_overload_function(void * db, char * zFuncName, int nArg);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE void * __cdecl sqlite3_trace(void * db, Firedac::Phys::Sqlitecli::Tsqlite3_trace_callback xTrace, void * userdata);
extern DELPHI_PACKAGE void * __cdecl sqlite3_profile(void * db, Firedac::Phys::Sqlitecli::Tsqlite3_profile_callback xProfile, void * userdata);
extern DELPHI_PACKAGE void * __cdecl sqlite3_commit_hook(void * db, Firedac::Phys::Sqlitecli::Tsqlite3_commit_callback callback, void * userdata);
extern DELPHI_PACKAGE void * __cdecl sqlite3_update_hook(void * db, Firedac::Phys::Sqlitecli::Tsqlite3_update_callback callback, void * userdata);
extern DELPHI_PACKAGE void * __cdecl sqlite3_rollback_hook(void * db, Firedac::Phys::Sqlitecli::Tsqlite3_rollback_callback callback, void * userdata);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_wal_autocheckpoint(void * db, int N);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE void * __cdecl sqlite3_wal_hook(void * db, Firedac::Phys::Sqlitecli::Tsqlite3_wal_callback callback, void * userdata);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_wal_checkpoint(void * db, char * zDb);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_errmsg(void * db);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_errmsg16(void * db);
extern DELPHI_PACKAGE int __cdecl sqlite3_errcode(void * db);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_errstr(int code);
extern DELPHI_PACKAGE int __cdecl sqlite3_limit(void * db, int id, int newVal);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_open(System::PByte filename, void * &ppDb);
extern DELPHI_PACKAGE int __cdecl sqlite3_open_v2(char * filename, void * &ppDb, int flags, char * zVfs);
extern DELPHI_PACKAGE int __cdecl sqlite3_open16(System::PByte filename, void * &ppDb);
extern DELPHI_PACKAGE int __cdecl sqlite3_create_collation(void * db, System::PByte zName, int eTextRep, void * userdata, Firedac::Phys::Sqlitecli::Tsqlite3_compare_callback callback);
extern DELPHI_PACKAGE int __cdecl sqlite3_create_collation16(void * db, System::PByte zName, int eTextRep, void * userdata, Firedac::Phys::Sqlitecli::Tsqlite3_compare_callback callback);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE int __cdecl sqlite3_collation_needed(void * db, void * userdata, Firedac::Phys::Sqlitecli::Tsqlite3_collation_callback callback);
extern DELPHI_PACKAGE int __cdecl sqlite3_collation_needed16(void * db, void * userdata, Firedac::Phys::Sqlitecli::Tsqlite3_collation_callback callback);
extern DELPHI_PACKAGE int __cdecl sqlite3_get_autocommit(void * db);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_table_column_metadata(void * db, char * zDbName, char * zTableName, char * zColumnName, char * &pzDataType, char * &pzCollSeq, int &pNotNull, int &pPrimaryKey, int &pAutoinc);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE int __cdecl sqlite3_extended_result_codes(void * db, int onoff);
#ifndef _WIN64
extern DELPHI_PACKAGE char * __cdecl sqlite3_db_filename(void * db, char * zDbName);
extern DELPHI_PACKAGE int __cdecl sqlite3_db_readonly(void * db, char * zDbName);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE int __cdecl sqlite3_compileoption_used(char * zOptName);
extern DELPHI_PACKAGE char * __cdecl sqlite3_compileoption_get(int N);
#ifndef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_rtree_geometry_callback(void * db, System::PByte zGeom, Firedac::Phys::Sqlitecli::Tsqlite3_rtree_xGeom_callback xGeom, void * pContext);
extern DELPHI_PACKAGE int __cdecl sqlite3_rtree_query_callback(void * db, System::PByte zQueryFunc, Firedac::Phys::Sqlitecli::Tsqlite3_rtree_xQuery_callback xQueryFunc, void * pContext, Firedac::Phys::Sqlitecli::Tsqlite3_rtree_xDelUser_callback xDestructor);
#endif /* not _WIN64 */
extern DELPHI_PACKAGE int __cdecl ad_sqlite3GetCacheSize(void * db);
extern DELPHI_PACKAGE int __cdecl ad_sqlite3GetEncoding(void * db);
#ifdef _WIN64
extern DELPHI_PACKAGE Firedac::Phys::Sqlitecli::psqlite3_vfs __cdecl sqlite3_vfs_find(char * zVfsName);
extern DELPHI_PACKAGE int __cdecl sqlite3_vfs_register(Firedac::Phys::Sqlitecli::psqlite3_vfs pVfs, int makeDflt);
extern DELPHI_PACKAGE int __cdecl sqlite3_vfs_unregister(Firedac::Phys::Sqlitecli::psqlite3_vfs pVfs);
extern DELPHI_PACKAGE void * __cdecl sqlite3_malloc(int n);
extern DELPHI_PACKAGE int __cdecl sqlite3_stmt_status(void * stmt, int op, int resetFlg);
extern DELPHI_PACKAGE int __cdecl sqlite3_auto_extension(void * xEntryPoint);
extern DELPHI_PACKAGE char * __cdecl sqlite3_db_filename(void * db, char * zDbName);
extern DELPHI_PACKAGE int __cdecl sqlite3_db_readonly(void * db, char * zDbName);
extern DELPHI_PACKAGE void * __cdecl sqlite3_aggregate_context(void * context, int nBytes);
extern DELPHI_PACKAGE double __cdecl sqlite3_column_double(void * stmt, int iCol);
extern DELPHI_PACKAGE int __cdecl sqlite3_column_int(void * stmt, int iCol);
extern DELPHI_PACKAGE __int64 __cdecl sqlite3_column_int64(void * stmt, int iCol);
extern DELPHI_PACKAGE void * __cdecl sqlite3_column_value(void * stmt, int iCol);
extern DELPHI_PACKAGE int __cdecl sqlite3_column_type(void * stmt, int iCol);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_value(void * context, void * value);
extern DELPHI_PACKAGE void __cdecl sqlite3_set_auxdata(void * context, int N, void * data, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE int __cdecl sqlite3_db_status(void * db, int op, int &pCurrent, int &pHighwater, int resetFlag);
extern DELPHI_PACKAGE int __cdecl sqlite3_value_bytes(void * value);
extern DELPHI_PACKAGE int __cdecl sqlite3_value_bytes16(void * value);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_value_text(void * value);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_value_text16(void * value);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_error(void * context, System::PByte msg, int nBytes);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_error16(void * context, System::PByte msg, int nBytes);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_error_code(void * context, int code);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_error_toobig(void * context);
extern DELPHI_PACKAGE int __cdecl sqlite3_column_bytes(void * stmt, int iCol);
extern DELPHI_PACKAGE int __cdecl sqlite3_column_bytes16(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_text(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_text16(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_name(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_name16(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_decltype(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_decltype16(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_database_name(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_database_name16(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_table_name(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_table_name16(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_origin_name(void * stmt, int iCol);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_column_origin_name16(void * stmt, int iCol);
extern DELPHI_PACKAGE int __cdecl sqlite3_create_module(void * db, char * zName, Firedac::Phys::Sqlitecli::psqlite3_module module, void * userdata);
extern DELPHI_PACKAGE int __cdecl sqlite3_create_module_v2(void * db, char * zName, Firedac::Phys::Sqlitecli::psqlite3_module module, void * userdata, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE void * __cdecl sqlite3_value_blob(void * value);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_blob(void * context, void * value, int nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_blob64(void * context, void * value, unsigned __int64 nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_text(void * context, System::PByte value, int nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_text64(void * context, System::PByte value, unsigned __int64 nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr, System::Byte encoding);
extern DELPHI_PACKAGE void __cdecl sqlite3_result_text16(void * context, System::PByte value, int nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE void * __cdecl sqlite3_column_blob(void * stmt, int iCol);
extern DELPHI_PACKAGE int __cdecl sqlite3_load_extension(void * db, System::PByte zFile, System::PByte zProc, System::PByte &pzErrMsg);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_errmsg16(void * db);
#endif /* _WIN64 */
extern DELPHI_PACKAGE void __cdecl ad_sqlite3Error(void * db, int err_code, System::PByte zMessage);
#ifdef _WIN64
extern DELPHI_PACKAGE int __cdecl sqlite3_status(int op, int &pCurrent, int &pHighwater, int resetFlag);
extern DELPHI_PACKAGE __int64 __cdecl sqlite3_memory_used(void);
extern DELPHI_PACKAGE __int64 __cdecl sqlite3_memory_highwater(int resetFlag);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_blob(void * stmt, int index, void * value, int nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_blob64(void * stmt, int index, void * value, unsigned __int64 nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_double(void * stmt, int index, double value);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_int64(void * stmt, int index, __int64 value);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_null(void * stmt, int index);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_text(void * stmt, int index, System::PByte value, int nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_text64(void * stmt, int index, System::PByte value, unsigned __int64 nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr, System::Byte encoding);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_text16(void * stmt, int index, System::PByte value, int nBytes, Firedac::Phys::Sqlitecli::Tsqlite3_destroy_callback destr);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_zeroblob(void * stmt, int index, int nBytes);
extern DELPHI_PACKAGE int __cdecl sqlite3_vtab_config(void * db, int op, ...);
extern DELPHI_PACKAGE int __cdecl sqlite3_config(int option, ...);
extern DELPHI_PACKAGE int __cdecl sqlite3_create_function(void * db, System::PByte zFunctionName, int nArg, int eTextRep, void * pApp, Firedac::Phys::Sqlitecli::Tsqlite3_func_callback xFunc, Firedac::Phys::Sqlitecli::Tsqlite3_step_callback xStep, Firedac::Phys::Sqlitecli::Tsqlite3_final_callback xFinal);
extern DELPHI_PACKAGE int __cdecl sqlite3_create_function16(void * db, System::PByte zFunctionName, int nArg, int eTextRep, void * pApp, Firedac::Phys::Sqlitecli::Tsqlite3_func_callback xFunc, Firedac::Phys::Sqlitecli::Tsqlite3_step_callback xStep, Firedac::Phys::Sqlitecli::Tsqlite3_final_callback xFinal);
extern DELPHI_PACKAGE int __cdecl sqlite3_overload_function(void * db, char * zFuncName, int nArg);
extern DELPHI_PACKAGE System::PByte __cdecl sqlite3_errmsg(void * db);
extern DELPHI_PACKAGE int __cdecl sqlite3_errcode(void * db);
extern DELPHI_PACKAGE int __cdecl sqlite3_create_collation16(void * db, System::PByte zName, int eTextRep, void * userdata, Firedac::Phys::Sqlitecli::Tsqlite3_compare_callback callback);
extern DELPHI_PACKAGE int __cdecl sqlite3_rtree_geometry_callback(void * db, System::PByte zGeom, Firedac::Phys::Sqlitecli::Tsqlite3_rtree_xGeom_callback xGeom, void * pContext);
extern DELPHI_PACKAGE int __cdecl sqlite3_rtree_query_callback(void * db, System::PByte zQueryFunc, Firedac::Phys::Sqlitecli::Tsqlite3_rtree_xQuery_callback xQueryFunc, void * pContext, Firedac::Phys::Sqlitecli::Tsqlite3_rtree_xDelUser_callback xDestructor);
extern DELPHI_PACKAGE void __cdecl sqlite3_soft_heap_limit(int amount);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_int(void * stmt, int index, int value);
extern DELPHI_PACKAGE int __cdecl sqlite3_bind_value(void * stmt, int index, void * value);
extern DELPHI_PACKAGE int __cdecl sqlite3_create_collation(void * db, System::PByte zName, int eTextRep, void * userdata, Firedac::Phys::Sqlitecli::Tsqlite3_compare_callback callback);
extern DELPHI_PACKAGE int __cdecl sqlite3_wal_checkpoint(void * db, char * zDb);
extern DELPHI_PACKAGE int __cdecl sqlite3_wal_autocheckpoint(void * db, int N);
extern DELPHI_PACKAGE void * __cdecl sqlite3_backup_init(void * pDest, System::PByte zDestName, void * pSource, System::PByte zSourceName);
extern DELPHI_PACKAGE int __cdecl sqlite3_backup_step(void * p, int nPage);
extern DELPHI_PACKAGE int __cdecl sqlite3_backup_finish(void * p);
extern DELPHI_PACKAGE int __cdecl sqlite3_finalize(void * stmt);
extern DELPHI_PACKAGE int __cdecl sqlite3_reset(void * stmt);
extern DELPHI_PACKAGE int __cdecl sqlite3_blob_close(void * blob);
extern DELPHI_PACKAGE int __cdecl sqlite3_blob_read(void * blob, void * Z, int N, int iOffset);
extern DELPHI_PACKAGE int __cdecl sqlite3_blob_write(void * blob, void * Z, int N, int iOffset);
extern DELPHI_PACKAGE int __cdecl sqlite3_close(void * db);
extern DELPHI_PACKAGE int __cdecl sqlite3_step(void * stmt);
extern DELPHI_PACKAGE int __cdecl sqlite3_exec(void * db, System::PByte zSql, void * callback, void * data, Firedac::Stan::Intf::PPByte errmsg);
extern DELPHI_PACKAGE int __cdecl sqlite3_table_column_metadata(void * db, char * zDbName, char * zTableName, char * zColumnName, char * &pzDataType, char * &pzCollSeq, int &pNotNull, int &pPrimaryKey, int &pAutoinc);
extern DELPHI_PACKAGE int __cdecl sqlite3_blob_open(void * db, char * zDb, char * zTable, char * zColumn, __int64 iRow, int flags, void * &ppBlob);
extern DELPHI_PACKAGE int __cdecl sqlite3_prepare_v2(void * db, System::PByte zSql, int nByte, void * &ppStmt, System::PByte &pzTail);
extern DELPHI_PACKAGE int __cdecl sqlite3_prepare16(void * db, System::PByte zSql, int nByte, void * &ppStmt, System::PByte &pzTail);
extern DELPHI_PACKAGE int __cdecl sqlite3_prepare16_v2(void * db, System::PByte zSql, int nByte, void * &ppStmt, System::PByte &pzTail);
extern DELPHI_PACKAGE int __cdecl sqlite3_declare_vtab(void * db, char * zCreateTable);
extern DELPHI_PACKAGE int __cdecl sqlite3_initialize(void);
extern DELPHI_PACKAGE int __cdecl sqlite3_open(System::PByte filename, void * &ppDb);
extern DELPHI_PACKAGE int __cdecl sqlite3_open_v2(char * filename, void * &ppDb, int flags, char * zVfs);
extern DELPHI_PACKAGE int __cdecl sqlite3_open16(System::PByte filename, void * &ppDb);
#endif /* _WIN64 */
}	/* namespace Stat */
}	/* namespace Sqlitewrapper */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_SQLITEWRAPPER_STAT)
using namespace Firedac::Phys::Sqlitewrapper::Stat;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_SQLITEWRAPPER)
using namespace Firedac::Phys::Sqlitewrapper;
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
#endif	// Firedac_Phys_Sqlitewrapper_StatHPP
