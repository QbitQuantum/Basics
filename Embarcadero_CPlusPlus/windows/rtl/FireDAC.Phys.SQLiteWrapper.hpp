// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.SQLiteWrapper.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_SqlitewrapperHPP
#define Firedac_Phys_SqlitewrapperHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>
#include <System.Generics.Collections.hpp>
#include <Data.FmtBcd.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Expr.hpp>
#include <FireDAC.Stan.Consts.hpp>
#include <FireDAC.Phys.SQLiteCli.hpp>
#include <FireDAC.Phys.SQLiteMeta.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Sqlitewrapper
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ESQLiteNativeException;
class DELPHICLASS TSQLiteLib;
class DELPHICLASS TSQLiteLibDyn;
class DELPHICLASS TSQLiteHandle;
class DELPHICLASS TSQLiteDatabase;
class DELPHICLASS TSQLiteExtension;
class DELPHICLASS TSQLiteExtensionInstance;
class DELPHICLASS TSQLiteExtensionManager;
class DELPHICLASS TSQLiteCollation;
class DELPHICLASS TSQLiteCollationCompareString;
class DELPHICLASS TSQLiteBLOB;
class DELPHICLASS TSQLiteValueDef;
class DELPHICLASS TSQLiteValue;
class DELPHICLASS TSQLiteStmtVar;
class DELPHICLASS TSQLiteBind;
class DELPHICLASS TSQLiteColumn;
class DELPHICLASS TSQLiteVariables;
class DELPHICLASS TSQLiteStatement;
class DELPHICLASS TSQLiteFuncVar;
class DELPHICLASS TSQLiteInput;
class DELPHICLASS TSQLiteInputs;
class DELPHICLASS TSQLiteOutput;
class DELPHICLASS TSQLiteFunction;
class DELPHICLASS TSQLiteFunctionInstance;
class DELPHICLASS TSQLiteExpressionFunction;
class DELPHICLASS TSQLiteExpressionFunctionInstance;
class DELPHICLASS TFDPhysSQLiteLastAutoGenFunc;
class DELPHICLASS TSQLiteRTree;
class DELPHICLASS TSQLiteRTreeInstance;
class DELPHICLASS TSQLiteRTreeData;
class DELPHICLASS TSQLiteBackup;
struct FDsqlite3_vtab;
struct FDsqlite3_vtab_cursor;
struct TSQLiteVColDef;
struct TSQLiteVConstraint;
struct TSQLiteVOrderBy;
class DELPHICLASS TSQLiteVObject;
class DELPHICLASS TSQLiteVModule;
class DELPHICLASS TSQLiteVTableDef;
class DELPHICLASS TSQLiteVTable;
class DELPHICLASS TSQLiteVCursor;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
typedef System::TMetaClass* TSQLiteLibClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TSQLiteLibClass);
#endif /* _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TSQLiteExtensionClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TSQLiteExtensionClass);
#endif /* _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TSQLiteVModuleClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TSQLiteVModuleClass);
#endif /* _WIN64 */

enum DECLSPEC_DENUM TSQLiteDatabaseMode : unsigned int { smCreate, smReadWrite, smReadOnly };

enum DECLSPEC_DENUM TSQLiteSharedCache : unsigned int { scDefault, scPrivate, scShared };

typedef void __fastcall (__closure *TSQLiteDatabaseAuthorizeEvent)(TSQLiteDatabase* ADB, int ACode, const System::UnicodeString AArg1, const System::UnicodeString AArg2, const System::UnicodeString AArg3, const System::UnicodeString AArg4, int &AResult);

typedef void __fastcall (__closure *TSQLiteDatabaseUpdateEvent)(TSQLiteDatabase* ADB, int AOper, const System::UnicodeString ADatabase, const System::UnicodeString ATable, __int64 ARowid);

typedef void __fastcall (__closure *TSQLiteDatabaseProgressEvent)(TSQLiteDatabase* ADB, bool &ACancel);

typedef void __fastcall (__closure *TSQLiteDatabaseWalEvent)(TSQLiteDatabase* ADB, System::UnicodeString AName, int AnPages);

enum DECLSPEC_DENUM TSQLiteExtDataType : unsigned int { etUnknown, etString, etUString, etInteger, etDouble, etNumber, etCurrency, etBlob, etBoolean, etDate, etTime, etDateTime };

enum DECLSPEC_DENUM TSQLiteStatementState : unsigned int { ssInactive, ssPrepared, ssRewinded, ssExecuted, ssFirstFetch, ssNextFetch, ssEOF };

typedef void __fastcall (__closure *TSQLiteFunctionCalculateEvent)(TSQLiteFunctionInstance* AFunc, TSQLiteInputs* AInputs, TSQLiteOutput* AOutput, System::TObject* &AUserData);

typedef void __fastcall (__closure *TSQLiteFunctionFinalizeEvent)(TSQLiteFunctionInstance* AFunc, System::TObject* &AUserData);

typedef System::DynamicArray<double> TSQLiteRTreeDoubleArray;

typedef void __fastcall (__closure *TSQLiteRTreeCalculateEvent)(TSQLiteRTreeData* ARTree, const TSQLiteRTreeDoubleArray AParams, const TSQLiteRTreeDoubleArray AColumns, bool &AResult);

typedef void __fastcall (__closure *TSQLiteRTreeFinalizeEvent)(TSQLiteRTreeData* ARTree, System::TObject* &AUserData);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ESQLiteNativeException : public Firedac::Stan::Error::EFDDBEngineException
{
	typedef Firedac::Stan::Error::EFDDBEngineException inherited;
	
public:
	__fastcall ESQLiteNativeException(int ACode, TSQLiteHandle* AOwner, System::UnicodeString AMsg)/* overload */;
public:
	/* EFDDBEngineException.Create */ inline __fastcall virtual ESQLiteNativeException()/* overload */ : Firedac::Stan::Error::EFDDBEngineException() { }
	/* EFDDBEngineException.Create */ inline __fastcall ESQLiteNativeException(int AADCode, const System::UnicodeString AMessage)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(AADCode, AMessage) { }
	/* EFDDBEngineException.Destroy */ inline __fastcall virtual ~ESQLiteNativeException() { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall ESQLiteNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Firedac::Stan::Error::EFDDBEngineException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESQLiteNativeException(NativeUInt Ident)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESQLiteNativeException(System::PResStringRec ResStringRec)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESQLiteNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESQLiteNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESQLiteNativeException(const System::UnicodeString Msg, int AHelpContext) : Firedac::Stan::Error::EFDDBEngineException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESQLiteNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Firedac::Stan::Error::EFDDBEngineException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESQLiteNativeException(NativeUInt Ident, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESQLiteNativeException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESQLiteNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESQLiteNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, Args, Args_High, AHelpContext) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TSQLiteEngineLinkage : unsigned int { slDefault, slStatic, slDynamic };

class PASCALIMPLEMENTATION TSQLiteLib : public Firedac::Stan::Util::TFDLibrary
{
	typedef Firedac::Stan::Util::TFDLibrary inherited;
	
private:
	System::Classes::TList* FDatabases;
	System::Classes::TList* FExtensions;
	System::Syncobjs::TCriticalSection* FLock;
	TSQLiteDatabase* FLastDatabase;
	void *FLastDBHandle;
	void __fastcall InstallExtensions(TSQLiteDatabase* ADatabase);
	void __fastcall InstallDatabases(TSQLiteExtension* AExtension);
	void __fastcall DeinstallExtensions(TSQLiteDatabase* ADatabase);
	void __fastcall DeinstallDatabases(TSQLiteExtension* AExtension);
	void __fastcall InstallModules(TSQLiteDatabase* ADatabase);
	void __fastcall DeinstallModules(TSQLiteDatabase* ADatabase);
	void __fastcall AddDatabase(TSQLiteDatabase* ADatabase);
	void __fastcall RemoveDatabase(TSQLiteDatabase* ADatabase);
	TSQLiteDatabase* __fastcall dbH2dbObj(void * db);
	
protected:
	void __fastcall Check(int ACode);
	virtual void __fastcall GetLibraryInfo();
	void __fastcall InternalAfterLoad(bool AEnableSharedCache);
	void __fastcall InternalBeforeUnload();
	virtual int __fastcall GetDefaultSharedCacheMode() = 0 ;
	static Firedac::Phys::Sqlitecli::Tsqlite3_user_data Gsqlite3_user_data;
	
public:
	static System::StaticArray<TSQLiteLibClass, 3> GLibClasses;
	Firedac::Phys::Sqlitemeta::TFDPhysSQLiteBrand FBrand;
	Firedac::Phys::Sqlitecli::Tsqlite3_libversion Fsqlite3_libversion;
	Firedac::Phys::Sqlitecli::Tsqlite3_libversion_number Fsqlite3_libversion_number;
	Firedac::Phys::Sqlitecli::Tsqlite3_compileoption_used Fsqlite3_compileoption_used;
	Firedac::Phys::Sqlitecli::Tsqlite3_compileoption_get Fsqlite3_compileoption_get;
	Firedac::Phys::Sqlitecli::Tsqlite3_initialize Fsqlite3_initialize;
	Firedac::Phys::Sqlitecli::Tsqlite3_shutdown Fsqlite3_shutdown;
	Firedac::Phys::Sqlitecli::Tsqlite3_config Fsqlite3_config;
	Firedac::Phys::Sqlitecli::Tsqlite3_close Fsqlite3_close;
	Firedac::Phys::Sqlitecli::Tsqlite3_errcode Fsqlite3_errcode;
	Firedac::Phys::Sqlitecli::Tsqlite3_errmsg Fsqlite3_errmsg;
	Firedac::Phys::Sqlitecli::Tsqlite3_errstr Fsqlite3_errstr;
	Firedac::Phys::Sqlitecli::Tsqlite3_extended_result_codes Fsqlite3_extended_result_codes;
	Firedac::Phys::Sqlitecli::Tsqlite3_open Fsqlite3_open;
	Firedac::Phys::Sqlitecli::Tsqlite3_open_v2 Fsqlite3_open_v2;
	Firedac::Phys::Sqlitecli::Tsqlite3_key Fsqlite3_key;
	Firedac::Phys::Sqlitecli::Tsqlite3_key Fsqlite3_rekey;
	Firedac::Phys::Sqlitecli::Tsqlite3_trace Fsqlite3_trace;
	Firedac::Phys::Sqlitecli::Tsqlite3_profile Fsqlite3_profile;
	Firedac::Phys::Sqlitecli::Tsqlite3_busy_timeout Fsqlite3_busy_timeout;
	Firedac::Phys::Sqlitecli::Tsqlite3_get_autocommit Fsqlite3_get_autocommit;
	Firedac::Phys::Sqlitecli::Tsqlite3_set_authorizer Fsqlite3_set_authorizer;
	Firedac::Phys::Sqlitecli::Tsqlite3_update_hook Fsqlite3_update_hook;
	Firedac::Phys::Sqlitecli::Tsqlite3_limit Fsqlite3_limit;
	Firedac::Phys::Sqlitecli::Tsqlite3_changes Fsqlite3_changes;
	Firedac::Phys::Sqlitecli::Tsqlite3_total_changes Fsqlite3_total_changes;
	Firedac::Phys::Sqlitecli::Tsqlite3_interrupt Fsqlite3_interrupt;
	Firedac::Phys::Sqlitecli::Tsqlite3_last_insert_rowid Fsqlite3_last_insert_rowid;
	Firedac::Phys::Sqlitecli::Tsqlite3_db_status Fsqlite3_db_status;
	Firedac::Phys::Sqlitecli::Tsqlite3_exec Fsqlite3_exec;
	Firedac::Phys::Sqlitecli::Tsqlite3_enable_shared_cache Fsqlite3_enable_shared_cache;
	Firedac::Phys::Sqlitecli::Tsqlite3_release_memory Fsqlite3_release_memory;
	Firedac::Phys::Sqlitecli::Tsqlite3_soft_heap_limit Fsqlite3_soft_heap_limit;
	Firedac::Phys::Sqlitecli::Tsqlite3_status Fsqlite3_status;
	Firedac::Phys::Sqlitecli::Tsqlite3_malloc Fsqlite3_malloc;
	Firedac::Phys::Sqlitecli::Tsqlite3_memory_used Fsqlite3_memory_used;
	Firedac::Phys::Sqlitecli::Tsqlite3_memory_highwater Fsqlite3_memory_highwater;
	Firedac::Phys::Sqlitecli::Tsqlite3_prepare Fsqlite3_prepare;
	Firedac::Phys::Sqlitecli::Tsqlite3_finalize Fsqlite3_finalize;
	Firedac::Phys::Sqlitecli::Tsqlite3_step Fsqlite3_step;
	Firedac::Phys::Sqlitecli::Tsqlite3_reset Fsqlite3_reset;
	Firedac::Phys::Sqlitecli::Tsqlite3_stmt_status Fsqlite3_stmt_status;
	Firedac::Phys::Sqlitecli::Tsqlite3_column_count Fsqlite3_column_count;
	Firedac::Phys::Sqlitecli::Tsqlite3_column_type Fsqlite3_column_type;
	Firedac::Phys::Sqlitecli::Tsqlite3_column_name Fsqlite3_column_name;
	Firedac::Phys::Sqlitecli::Tsqlite3_column_database_name Fsqlite3_column_database_name;
	Firedac::Phys::Sqlitecli::Tsqlite3_column_table_name Fsqlite3_column_table_name;
	Firedac::Phys::Sqlitecli::Tsqlite3_column_origin_name Fsqlite3_column_origin_name;
	Firedac::Phys::Sqlitecli::Tsqlite3_column_decltype Fsqlite3_column_decltype;
	Firedac::Phys::Sqlitecli::Tsqlite3_column_blob Fsqlite3_column_blob;
	Firedac::Phys::Sqlitecli::Tsqlite3_column_double Fsqlite3_column_double;
	Firedac::Phys::Sqlitecli::Tsqlite3_column_int64 Fsqlite3_column_int64;
	Firedac::Phys::Sqlitecli::Tsqlite3_column_text Fsqlite3_column_text;
	Firedac::Phys::Sqlitecli::Tsqlite3_column_bytes Fsqlite3_column_bytes_row;
	Firedac::Phys::Sqlitecli::Tsqlite3_column_bytes Fsqlite3_column_bytes;
	Firedac::Phys::Sqlitecli::Tsqlite3_clear_bindings Fsqlite3_clear_bindings;
	Firedac::Phys::Sqlitecli::Tsqlite3_bind_parameter_count Fsqlite3_bind_parameter_count;
	Firedac::Phys::Sqlitecli::Tsqlite3_bind_parameter_index Fsqlite3_bind_parameter_index;
	Firedac::Phys::Sqlitecli::Tsqlite3_bind_parameter_name Fsqlite3_bind_parameter_name;
	Firedac::Phys::Sqlitecli::Tsqlite3_bind_blob Fsqlite3_bind_blob;
	Firedac::Phys::Sqlitecli::Tsqlite3_bind_blob64 Fsqlite3_bind_blob64;
	Firedac::Phys::Sqlitecli::Tsqlite3_bind_double Fsqlite3_bind_double;
	Firedac::Phys::Sqlitecli::Tsqlite3_bind_int64 Fsqlite3_bind_int64;
	Firedac::Phys::Sqlitecli::Tsqlite3_bind_null Fsqlite3_bind_null;
	Firedac::Phys::Sqlitecli::Tsqlite3_bind_text Fsqlite3_bind_text;
	Firedac::Phys::Sqlitecli::Tsqlite3_bind_text64 Fsqlite3_bind_text64;
	Firedac::Phys::Sqlitecli::Tsqlite3_bind_value Fsqlite3_bind_value;
	Firedac::Phys::Sqlitecli::Tsqlite3_bind_zeroblob Fsqlite3_bind_zeroblob;
	Firedac::Phys::Sqlitecli::Tsqlite3_value_type Fsqlite3_value_type;
	Firedac::Phys::Sqlitecli::Tsqlite3_value_blob Fsqlite3_value_blob;
	Firedac::Phys::Sqlitecli::Tsqlite3_value_bytes Fsqlite3_value_bytes;
	Firedac::Phys::Sqlitecli::Tsqlite3_value_double Fsqlite3_value_double;
	Firedac::Phys::Sqlitecli::Tsqlite3_value_int64 Fsqlite3_value_int64;
	Firedac::Phys::Sqlitecli::Tsqlite3_value_text Fsqlite3_value_text;
	Firedac::Phys::Sqlitecli::Tsqlite3_result_blob Fsqlite3_result_blob;
	Firedac::Phys::Sqlitecli::Tsqlite3_result_blob64 Fsqlite3_result_blob64;
	Firedac::Phys::Sqlitecli::Tsqlite3_result_double Fsqlite3_result_double;
	Firedac::Phys::Sqlitecli::Tsqlite3_result_error Fsqlite3_result_error;
	Firedac::Phys::Sqlitecli::Tsqlite3_result_error_code Fsqlite3_result_error_code;
	Firedac::Phys::Sqlitecli::Tsqlite3_result_int64 Fsqlite3_result_int64;
	Firedac::Phys::Sqlitecli::Tsqlite3_result_null Fsqlite3_result_null;
	Firedac::Phys::Sqlitecli::Tsqlite3_result_text Fsqlite3_result_text;
	Firedac::Phys::Sqlitecli::Tsqlite3_result_text64 Fsqlite3_result_text64;
	Firedac::Phys::Sqlitecli::Tsqlite3_result_zeroblob Fsqlite3_result_zeroblob;
	Firedac::Phys::Sqlitecli::Tsqlite3_create_collation Fsqlite3_create_collation;
	Firedac::Phys::Sqlitecli::Tsqlite3_create_function Fsqlite3_create_function;
	Firedac::Phys::Sqlitecli::Tsqlite3_user_data Fsqlite3_user_data;
	Firedac::Phys::Sqlitecli::Tsqlite3_enable_load_extension Fsqlite3_enable_load_extension;
	Firedac::Phys::Sqlitecli::Tsqlite3_load_extension Fsqlite3_load_extension;
	Firedac::Phys::Sqlitecli::Tsqlite3_free Fsqlite3_free;
	Firedac::Phys::Sqlitecli::Tsqlite3_table_column_metadata Fsqlite3_table_column_metadata;
	Firedac::Phys::Sqlitecli::Tsqlite3_progress_handler Fsqlite3_progress_handler;
	Firedac::Phys::Sqlitecli::Tsqlite3_declare_vtab Fsqlite3_declare_vtab;
	Firedac::Phys::Sqlitecli::Tsqlite3_create_module Fsqlite3_create_module;
	Firedac::Phys::Sqlitecli::Tsqlite3_create_module_v2 Fsqlite3_create_module_v2;
	Firedac::Phys::Sqlitecli::Tsqlite3_vfs_find Fsqlite3_vfs_find;
	Firedac::Phys::Sqlitecli::Tsqlite3_vfs_register Fsqlite3_vfs_register;
	Firedac::Phys::Sqlitecli::Tsqlite3_vfs_unregister Fsqlite3_vfs_unregister;
	Firedac::Phys::Sqlitecli::Tsqlite3_backup_init Fsqlite3_backup_init;
	Firedac::Phys::Sqlitecli::Tsqlite3_backup_step Fsqlite3_backup_step;
	Firedac::Phys::Sqlitecli::Tsqlite3_backup_finish Fsqlite3_backup_finish;
	Firedac::Phys::Sqlitecli::Tsqlite3_backup_remaining Fsqlite3_backup_remaining;
	Firedac::Phys::Sqlitecli::Tsqlite3_backup_pagecount Fsqlite3_backup_pagecount;
	Firedac::Phys::Sqlitecli::Tsqlite3_wal_hook Fsqlite3_wal_hook;
	Firedac::Phys::Sqlitecli::Tsqlite3_wal_autocheckpoint Fsqlite3_wal_autocheckpoint;
	Firedac::Phys::Sqlitecli::Tsqlite3_wal_checkpoint Fsqlite3_wal_checkpoint;
	Firedac::Phys::Sqlitecli::Tsqlite3_rtree_geometry_callback Fsqlite3_rtree_geometry_callback;
	Firedac::Phys::Sqlitecli::Tsqlite3_rtree_query_callback Fsqlite3_rtree_query_callback;
	Firedac::Phys::Sqlitecli::Tsqlite3_blob_open Fsqlite3_blob_open;
	Firedac::Phys::Sqlitecli::Tsqlite3_blob_close Fsqlite3_blob_close;
	Firedac::Phys::Sqlitecli::Tsqlite3_blob_bytes Fsqlite3_blob_bytes;
	Firedac::Phys::Sqlitecli::Tsqlite3_blob_read Fsqlite3_blob_read;
	Firedac::Phys::Sqlitecli::Tsqlite3_blob_write Fsqlite3_blob_write;
	Firedac::Phys::Sqlitecli::Tsqlite3_vtab_config Fsqlite3_vtab_config;
	Firedac::Phys::Sqlitecli::Tsqlite3_vtab_on_conflict Fsqlite3_vtab_on_conflict;
	Firedac::Phys::Sqlitecli::Tad_sqlite3GetCacheSize Fad_sqlite3GetCacheSize;
	Firedac::Phys::Sqlitecli::Tad_sqlite3GetEncoding Fad_sqlite3GetEncoding;
	Firedac::Phys::Sqlitecli::Tad_sqlite3GetEncryptionMode Fad_sqlite3GetEncryptionMode;
	Firedac::Phys::Sqlitecli::Tad_sqlite3GetEncryptionError Fad_sqlite3GetEncryptionError;
	Firedac::Phys::Sqlitecli::Tad_sqlite3Error Fad_sqlite3Error;
	__fastcall TSQLiteLib(System::TObject* AOwningObj);
	__fastcall virtual ~TSQLiteLib();
	HIDESBASE virtual void __fastcall Load(const System::UnicodeString AVendorHome, const System::UnicodeString AVendorLib) = 0 /* overload */;
	void __fastcall ReleaseMemory(int AAmount);
	void __fastcall SoftHeapLimit(int AAmount);
	__property Firedac::Phys::Sqlitemeta::TFDPhysSQLiteBrand Brand = {read=FBrand, nodefault};
};


class PASCALIMPLEMENTATION TSQLiteLibDyn : public TSQLiteLib
{
	typedef TSQLiteLib inherited;
	
private:
	void * __fastcall GetSQLiteProcAddress(const System::UnicodeString AProcName, bool A16 = false, int AVer = 0x0, bool ARequired = true);
	
protected:
	virtual void __fastcall LoadEntries();
	virtual int __fastcall GetDefaultSharedCacheMode();
	
public:
	virtual void __fastcall Load(const System::UnicodeString AVendorHome, const System::UnicodeString AVendorLib)/* overload */;
	virtual void __fastcall Unload();
public:
	/* TSQLiteLib.Create */ inline __fastcall TSQLiteLibDyn(System::TObject* AOwningObj) : TSQLiteLib(AOwningObj) { }
	/* TSQLiteLib.Destroy */ inline __fastcall virtual ~TSQLiteLibDyn() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteHandle : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TSQLiteLib* FLib;
	void *FHandle;
	bool FOwnHandle;
	System::TObject* FOwningObj;
	TSQLiteDatabase* FDatabase;
	bool __fastcall GetTracing();
	
public:
	__fastcall TSQLiteHandle();
	__fastcall TSQLiteHandle(void * AHandle);
	void __fastcall Check(int ACode);
	void __fastcall Trace(const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	void __fastcall Trace(Firedac::Stan::Intf::TFDMoniEventKind AKind, Firedac::Stan::Intf::TFDMoniEventStep AStep, const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	__property bool Tracing = {read=GetTracing, nodefault};
	__property void * Handle = {read=FHandle};
	__property TSQLiteLib* Lib = {read=FLib};
	__property TSQLiteDatabase* Database = {read=FDatabase};
	__property System::TObject* OwningObj = {read=FOwningObj};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TSQLiteHandle() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TSQLiteDatabase : public TSQLiteHandle
{
	typedef TSQLiteHandle inherited;
	
private:
	Firedac::Stan::Util::TFDBuffer* FBuffer;
	Firedac::Stan::Util::TFDEncoder* FEncoder;
	int FBusyTimeout;
	System::Classes::TList* FExtensionInstances;
	System::Classes::TStrings* FExtensions;
	System::Classes::TList* FVModules;
	TSQLiteExtDataType FDateTimeFormat;
	int FProgressNOpers;
	TSQLiteDatabaseAuthorizeEvent FOnAuthorize;
	TSQLiteDatabaseUpdateEvent FOnUpdate;
	TSQLiteDatabaseProgressEvent FOnProgress;
	TSQLiteDatabaseWalEvent FOnWal;
	int FAutoCheckpoint;
	TSQLiteStatement* FCurStatement;
	Firedac::Stan::Intf::TFDStringList* FVTabs;
	System::Classes::TInterfaceList* FSQLHandlerList;
	__int64 FLastAutoGenValue;
	bool FTracing;
	Firedac::Stan::Intf::_di_IFDMoniClient FMonitor;
	void __fastcall SetTracing(bool AValue);
	void __fastcall UpdateTracing();
	Firedac::Stan::Intf::TFDEncoding __fastcall GetKeyEncoding();
	void __fastcall SetBusyTimeout(const int AValue);
	void __fastcall InstallExternalExtensions();
	void __fastcall SetExtensions(System::Classes::TStrings* const AValue);
	bool __fastcall GetInTransaction();
	int __fastcall DoAuthorize(int code, char * zArg1, char * zArg2, char * zArg3, char * zArg4);
	void __fastcall SetOnAuthorize(const TSQLiteDatabaseAuthorizeEvent AValue);
	void __fastcall DoUpdate(int oper, char * zDb, char * zTable, __int64 rowid);
	void __fastcall SetOnUpdate(const TSQLiteDatabaseUpdateEvent AValue);
	int __fastcall GetTotalChanges();
	__int64 __fastcall GetLastInsertRowid();
	__int64 __fastcall GetLastAutoGenValue();
	void __fastcall SetOnProgress(const TSQLiteDatabaseProgressEvent AValue);
	int __fastcall DoProgress();
	void __fastcall SetProgressNOpers(const int AValue);
	int __fastcall GetCacheSize();
	System::UnicodeString __fastcall GetCharacterSet();
	System::UnicodeString __fastcall GetEncryption();
	void __fastcall SetOnWal(const TSQLiteDatabaseWalEvent AValue);
	int __fastcall DoWal(System::PByte name, int nPages);
	void __fastcall SetAutoCheckpoint(const int AValue);
	int __fastcall GetLimits(int AId);
	void __fastcall SetLimits(int AId, const int AValue);
	bool __fastcall IsVTab(const System::UnicodeString ATabName, const System::UnicodeString AColName, /* out */ bool &ANotNull, /* out */ bool &AInPK, /* out */ bool &AAutoInc);
	bool __fastcall DoGetTable(const System::UnicodeString AObjName);
	void __fastcall msg2putf8(const System::UnicodeString AMsg, void * &ApMsg);
	void __fastcall Init(TSQLiteLib* ALib, System::TObject* AOwningObj, const Firedac::Stan::Intf::_di_IFDMoniClient AMonitor = Firedac::Stan::Intf::_di_IFDMoniClient());
	
public:
	__fastcall TSQLiteDatabase(TSQLiteLib* ALib, System::TObject* AOwningObj, const Firedac::Stan::Intf::_di_IFDMoniClient AMonitor);
	__fastcall TSQLiteDatabase(TSQLiteLib* ALib, void * Asqlite3, System::TObject* AOwningObj, const Firedac::Stan::Intf::_di_IFDMoniClient AMonitor);
	__fastcall virtual ~TSQLiteDatabase();
	System::UnicodeString __fastcall APIStrToDlpStr(System::PByte AStr);
	void __fastcall Open(const System::UnicodeString AFilename, TSQLiteDatabaseMode AMode, TSQLiteSharedCache ASharedCache);
	void __fastcall Key(const System::UnicodeString AKey);
	void __fastcall ReKey(const System::UnicodeString AKey);
	void __fastcall Close();
	void __fastcall Interrupt();
	void __fastcall EnableExtensions(bool AValue);
	void __fastcall LoadExtension(const System::UnicodeString AExtension, const System::UnicodeString AEntry);
	bool __fastcall DescribeColumn(const System::UnicodeString ADBName, const System::UnicodeString ATabName, const System::UnicodeString AColName, /* out */ System::UnicodeString &AType, /* out */ System::UnicodeString &ACollation, /* out */ bool &ANotNull, /* out */ bool &AInPK, /* out */ bool &AAutoInc, bool ARaiseError = true);
	void __fastcall Checkpoint(const System::UnicodeString ADb);
	__classmethod void __fastcall ParseObjName(const System::UnicodeString AObjName, System::UnicodeString &ASchema, System::UnicodeString &AName);
	void __fastcall SetLastAutoGenValue(const __int64 AValue);
	__property Firedac::Stan::Intf::_di_IFDMoniClient Monitor = {read=FMonitor, write=FMonitor};
	__property bool Tracing = {read=FTracing, write=SetTracing, nodefault};
	__property Firedac::Stan::Util::TFDBuffer* Buffer = {read=FBuffer};
	__property Firedac::Stan::Util::TFDEncoder* Encoder = {read=FEncoder};
	__property bool InTransaction = {read=GetInTransaction, nodefault};
	__property int TotalChanges = {read=GetTotalChanges, nodefault};
	__property System::UnicodeString CharacterSet = {read=GetCharacterSet};
	__property int CacheSize = {read=GetCacheSize, nodefault};
	__property System::UnicodeString Encryption = {read=GetEncryption};
	__property System::Classes::TInterfaceList* SQLHandlerList = {read=FSQLHandlerList};
	__property TSQLiteStatement* CurStatement = {read=FCurStatement};
	__property __int64 LastInsertRowid = {read=GetLastInsertRowid};
	__property __int64 LastAutoGenValue = {read=GetLastAutoGenValue};
	__property int BusyTimeout = {read=FBusyTimeout, write=SetBusyTimeout, nodefault};
	__property System::Classes::TStrings* Extensions = {read=FExtensions, write=SetExtensions};
	__property TSQLiteExtDataType DateTimeFormat = {read=FDateTimeFormat, write=FDateTimeFormat, nodefault};
	__property int ProgressNOpers = {read=FProgressNOpers, write=SetProgressNOpers, nodefault};
	__property int AutoCheckpoint = {read=FAutoCheckpoint, write=SetAutoCheckpoint, nodefault};
	__property int Limits[int AId] = {read=GetLimits, write=SetLimits};
	__property TSQLiteDatabaseAuthorizeEvent OnAutorize = {read=FOnAuthorize, write=SetOnAuthorize};
	__property TSQLiteDatabaseUpdateEvent OnUpdate = {read=FOnUpdate, write=SetOnUpdate};
	__property TSQLiteDatabaseProgressEvent OnProgress = {read=FOnProgress, write=SetOnProgress};
	__property TSQLiteDatabaseWalEvent OnWal = {read=FOnWal, write=SetOnWal};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteExtension : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TSQLiteLib* FLib;
	System::UnicodeString FName;
	
protected:
	__classmethod virtual void __fastcall Register(TSQLiteLib* ALib);
	virtual void __fastcall InternalInstall(TSQLiteDatabase* ADatabase) = 0 ;
	virtual void __fastcall InternalDeinstall(TSQLiteDatabase* ADatabase);
	
public:
	__fastcall virtual TSQLiteExtension(TSQLiteLib* ALib);
	__fastcall virtual ~TSQLiteExtension();
	void __fastcall InstallAll();
	void __fastcall DeinstallAll();
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property TSQLiteLib* Lib = {read=FLib};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteExtensionInstance : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TSQLiteDatabase* FDatabase;
	TSQLiteExtension* FExtension;
	
public:
	__fastcall TSQLiteExtensionInstance(TSQLiteDatabase* ADB, TSQLiteExtension* AExt);
	__fastcall virtual ~TSQLiteExtensionInstance();
	__property TSQLiteDatabase* Database = {read=FDatabase};
	__property TSQLiteExtension* Extension = {read=FExtension};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteExtensionManager : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Firedac::Stan::Intf::TFDStringList* FModules;
	System::Classes::TList* FExtensions;
	void __fastcall RegisterAll(TSQLiteLib* ALib);
	
public:
	__fastcall TSQLiteExtensionManager();
	__fastcall virtual ~TSQLiteExtensionManager();
	void __fastcall AddModule(const System::UnicodeString AName, TSQLiteVModuleClass AClass);
	void __fastcall AddExtension(TSQLiteExtensionClass const *AClasses, const int AClasses_High);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TSQLiteCollationEvent)(System::TObject* ASender, int len1, void * str1, int len2, void * str2, int &AResult);

class PASCALIMPLEMENTATION TSQLiteCollation : public TSQLiteExtension
{
	typedef TSQLiteExtension inherited;
	
private:
	int FEncoding;
	TSQLiteCollationEvent FOnCompare;
	System::TObject* FOwningObj;
	
protected:
	virtual int __fastcall Compare(int len1, void * str1, int len2, void * str2);
	virtual void __fastcall InternalInstall(TSQLiteDatabase* ADatabase);
	virtual void __fastcall InternalDeinstall(TSQLiteDatabase* ADatabase);
	
public:
	__property int Encoding = {read=FEncoding, write=FEncoding, nodefault};
	__property TSQLiteCollationEvent OnCompare = {read=FOnCompare, write=FOnCompare};
	__property System::TObject* OwningObj = {read=FOwningObj, write=FOwningObj};
public:
	/* TSQLiteExtension.Create */ inline __fastcall virtual TSQLiteCollation(TSQLiteLib* ALib) : TSQLiteExtension(ALib) { }
	/* TSQLiteExtension.Destroy */ inline __fastcall virtual ~TSQLiteCollation() { }
	
};


class PASCALIMPLEMENTATION TSQLiteCollationCompareString : public TSQLiteCollation
{
	typedef TSQLiteCollation inherited;
	
private:
	unsigned FLocaleID;
	unsigned FFlags;
	unsigned __fastcall GetLocaleID();
	void __fastcall SetLocaleID(const unsigned AValue);
	
protected:
	virtual int __fastcall Compare(int len1, void * str1, int len2, void * str2);
	
public:
	__fastcall virtual TSQLiteCollationCompareString(TSQLiteLib* ALib);
	__property unsigned LocaleID = {read=GetLocaleID, write=SetLocaleID, nodefault};
	__property unsigned Flags = {read=FFlags, write=FFlags, nodefault};
public:
	/* TSQLiteExtension.Destroy */ inline __fastcall virtual ~TSQLiteCollationCompareString() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteBLOB : public TSQLiteHandle
{
	typedef TSQLiteHandle inherited;
	
private:
	int FPosition;
	int __fastcall GetSize();
	
public:
	__fastcall TSQLiteBLOB(TSQLiteDatabase* ADB, const System::UnicodeString ADBAlias, const System::UnicodeString ATable, const System::UnicodeString AColumn, __int64 ARowID, bool AReadWrite)/* overload */;
	__fastcall virtual ~TSQLiteBLOB();
	void __fastcall Write(const void *AData, int ASize);
	void __fastcall Read(void *AData, int ASize);
	__property int Position = {read=FPosition, write=FPosition, nodefault};
	__property int Size = {read=GetSize, nodefault};
public:
	/* TSQLiteHandle.CreateUsingHandle */ inline __fastcall TSQLiteBLOB(void * AHandle) : TSQLiteHandle(AHandle) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteValueDef : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TSQLiteStatement* FStmt;
	int FIndex;
	System::UnicodeString FName;
	System::UnicodeString FTabName;
	System::UnicodeString FColName;
	System::UnicodeString FDBName;
	System::UnicodeString FTypeName;
	int FIntDataType;
	System::UnicodeString FCollationName;
	bool FNotNull;
	bool FInPrimaryKey;
	bool FAutoInc;
	
public:
	__fastcall TSQLiteValueDef(TSQLiteStatement* AStmt, int AIndex);
	__fastcall TSQLiteValueDef(TSQLiteStatement* AStmt, int AIndex, int ADummy);
	__property int Index = {read=FIndex, nodefault};
	__property System::UnicodeString Name = {read=FName};
	__property System::UnicodeString DBName = {read=FDBName};
	__property System::UnicodeString TabName = {read=FTabName};
	__property System::UnicodeString ColName = {read=FColName};
	__property System::UnicodeString TypeName = {read=FTypeName};
	__property System::UnicodeString CollationName = {read=FCollationName};
	__property bool NotNull = {read=FNotNull, nodefault};
	__property bool InPrimaryKey = {read=FInPrimaryKey, nodefault};
	__property bool AutoInc = {read=FAutoInc, nodefault};
	__property int IntDataType = {read=FIntDataType, nodefault};
public:
	/* TObject.Create */ inline __fastcall TSQLiteValueDef() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSQLiteValueDef() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteValue : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TSQLiteDatabase* FDatabase;
	TSQLiteExtDataType FExtDataType;
	System::AnsiString __fastcall GetAnsiString();
	System::WordBool __fastcall GetBoolean();
	System::Currency __fastcall GetCurrency();
	System::TDateTime __fastcall GetDate();
	System::TDateTime __fastcall GetDateTime();
	double __fastcall GetFloat();
	__int64 __fastcall GetInteger();
	Data::Fmtbcd::TBcd __fastcall GetNumber();
	System::TDateTime __fastcall GetTime();
	System::UnicodeString __fastcall GetWideString();
	System::UnicodeString __fastcall GetAsString();
	void __fastcall SetAnsiString(const System::AnsiString AValue);
	void __fastcall SetBoolean(const System::WordBool AValue);
	void __fastcall SetCurrency(const System::Currency AValue);
	void __fastcall SetDate(const System::TDateTime AValue);
	void __fastcall SetDateTime(const System::TDateTime AValue);
	void __fastcall SetFloat(const double AValue);
	void __fastcall SetInteger(const __int64 AValue);
	void __fastcall SetNumber(const Data::Fmtbcd::TBcd &AValue);
	void __fastcall SetTime(const System::TDateTime AValue);
	void __fastcall SetWideString(const System::UnicodeString AValue);
	void __fastcall SetAsString(const System::UnicodeString AValue);
	bool __fastcall GetIsNull();
	
protected:
	virtual bool __fastcall InternalGetData(void * &AValue, int &ASize, int &AIntDataType);
	virtual void __fastcall InternalSetData(void * AValue, int ASize, int AIntDataType);
	
public:
	__fastcall TSQLiteValue(TSQLiteDatabase* ADatabase);
	bool __fastcall GetData(void * &AValue, int &ASize, bool AByRef = false, TSQLiteExtDataType AExtDataType = (TSQLiteExtDataType)(0x0));
	void __fastcall SetData(void * AValue, int ASize, TSQLiteExtDataType AExtDataType = (TSQLiteExtDataType)(0x0));
	void __fastcall Clear();
	__property TSQLiteDatabase* Database = {read=FDatabase};
	__property TSQLiteExtDataType ExtDataType = {read=FExtDataType, write=FExtDataType, nodefault};
	__property System::UnicodeString AsString = {read=GetAsString, write=SetAsString};
	__property System::AnsiString AsAnsiString = {read=GetAnsiString, write=SetAnsiString};
	__property System::UnicodeString AsWideString = {read=GetWideString, write=SetWideString};
	__property __int64 AsInteger = {read=GetInteger, write=SetInteger};
	__property double AsFloat = {read=GetFloat, write=SetFloat};
	__property System::Currency AsCurrency = {read=GetCurrency, write=SetCurrency};
	__property Data::Fmtbcd::TBcd AsNumber = {read=GetNumber, write=SetNumber};
	__property System::WordBool AsBoolean = {read=GetBoolean, write=SetBoolean, nodefault};
	__property System::TDateTime AsDate = {read=GetDate, write=SetDate};
	__property System::TDateTime AsTime = {read=GetTime, write=SetTime};
	__property System::TDateTime AsDateTime = {read=GetDateTime, write=SetDateTime};
	__property bool IsNull = {read=GetIsNull, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TSQLiteValue() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteStmtVar : public TSQLiteValue
{
	typedef TSQLiteValue inherited;
	
private:
	TSQLiteStatement* FStmt;
	int FIndex;
	
public:
	__fastcall TSQLiteStmtVar(TSQLiteVariables* AVars);
	__property TSQLiteStatement* Stmt = {read=FStmt};
	__property int Index = {read=FIndex, write=FIndex, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TSQLiteStmtVar() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteBind : public TSQLiteStmtVar
{
	typedef TSQLiteStmtVar inherited;
	
protected:
	virtual void __fastcall InternalSetData(void * AValue, int ASize, int AIntDataType);
public:
	/* TSQLiteStmtVar.Create */ inline __fastcall TSQLiteBind(TSQLiteVariables* AVars) : TSQLiteStmtVar(AVars) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TSQLiteBind() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteColumn : public TSQLiteStmtVar
{
	typedef TSQLiteStmtVar inherited;
	
protected:
	virtual bool __fastcall InternalGetData(void * &AValue, int &ASize, int &AIntDataType);
public:
	/* TSQLiteStmtVar.Create */ inline __fastcall TSQLiteColumn(TSQLiteVariables* AVars) : TSQLiteStmtVar(AVars) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TSQLiteColumn() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteVariables : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TSQLiteStmtVar* operator[](int AIndex) { return this->Items[AIndex]; }
	
private:
	TSQLiteStatement* FStmt;
	System::Classes::TList* FList;
	TSQLiteStmtVar* __fastcall GetItems(int AIndex);
	int __fastcall GetCount();
	
public:
	__fastcall TSQLiteVariables(TSQLiteStatement* AStmt);
	__fastcall virtual ~TSQLiteVariables();
	void __fastcall Clear(int ACount = 0x0);
	void __fastcall Add(TSQLiteStmtVar* AVar);
	__property int Count = {read=GetCount, nodefault};
	__property TSQLiteStmtVar* Items[int AIndex] = {read=GetItems/*, default*/};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteStatement : public TSQLiteHandle
{
	typedef TSQLiteHandle inherited;
	
private:
	System::RawByteString FCmdText;
	System::Byte *FCmdCurr;
	int FCmdTailLen;
	System::Byte *FCmdTail;
	int FLastStepError;
	TSQLiteStatementState FState;
	TSQLiteVariables* FParams;
	TSQLiteVariables* FColumns;
	int FBaseParamIndex;
	int FParamDefsCount;
	int FColumnDefsCount;
	bool FUseColumnMetadata;
	bool FStrsTrim;
	bool FStrsEmpty2Null;
	int FMaxStringSize;
	void __fastcall PrepareBase();
	void __fastcall Prepare()/* overload */;
	void __fastcall ExecuteBase();
	TSQLiteValueDef* __fastcall GetColumnDefs(int AIndex);
	int __fastcall GetChanges();
	TSQLiteValueDef* __fastcall GetParamDefs(int AIndex);
	bool __fastcall GetIsDrop();
	
public:
	__fastcall TSQLiteStatement(TSQLiteDatabase* ADB, System::TObject* AOwningObj);
	__fastcall virtual ~TSQLiteStatement();
	void __fastcall Prepare(const System::UnicodeString ACmd)/* overload */;
	void __fastcall Unprepare();
	void __fastcall Execute();
	void __fastcall Reset();
	void __fastcall Rewind();
	void __fastcall Clear();
	bool __fastcall Fetch();
	bool __fastcall FirstCommand();
	bool __fastcall MoreCommands();
	bool __fastcall PrepareNextCommand();
	__property TSQLiteStatementState State = {read=FState, nodefault};
	__property int Changes = {read=GetChanges, nodefault};
	__property int ColumnDefsCount = {read=FColumnDefsCount, nodefault};
	__property TSQLiteValueDef* ColumnDefs[int AIndex] = {read=GetColumnDefs};
	__property int ParamDefsCount = {read=FParamDefsCount, nodefault};
	__property TSQLiteValueDef* ParamDefs[int AIndex] = {read=GetParamDefs};
	__property TSQLiteVariables* Columns = {read=FColumns};
	__property TSQLiteVariables* Params = {read=FParams};
	__property int BaseParamIndex = {read=FBaseParamIndex, nodefault};
	__property bool IsDrop = {read=GetIsDrop, nodefault};
	__property bool UseColumnMetadata = {read=FUseColumnMetadata, write=FUseColumnMetadata, default=1};
	__property bool StrsTrim = {read=FStrsTrim, write=FStrsTrim, default=1};
	__property bool StrsEmpty2Null = {read=FStrsEmpty2Null, write=FStrsEmpty2Null, default=1};
	__property int MaxStringSize = {read=FMaxStringSize, write=FMaxStringSize, default=32767};
public:
	/* TSQLiteHandle.CreateUsingHandle */ inline __fastcall TSQLiteStatement(void * AHandle) : TSQLiteHandle(AHandle) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteFuncVar : public TSQLiteValue
{
	typedef TSQLiteValue inherited;
	
public:
	/* TSQLiteValue.Create */ inline __fastcall TSQLiteFuncVar(TSQLiteDatabase* ADatabase) : TSQLiteValue(ADatabase) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TSQLiteFuncVar() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteInput : public TSQLiteFuncVar
{
	typedef TSQLiteFuncVar inherited;
	
private:
	void *FHandle;
	int FIntDataType;
	void __fastcall SetHandle(const void * AValue);
	
protected:
	virtual bool __fastcall InternalGetData(void * &AValue, int &ASize, int &AIntDataType);
	
public:
	__property void * Handle = {read=FHandle, write=SetHandle};
	__property int IntDataType = {read=FIntDataType, nodefault};
public:
	/* TSQLiteValue.Create */ inline __fastcall TSQLiteInput(TSQLiteDatabase* ADatabase) : TSQLiteFuncVar(ADatabase) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TSQLiteInput() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteInputs : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TSQLiteInput* operator[](int AIndex) { return this->Inputs[AIndex]; }
	
private:
	System::Classes::TList* FList;
	TSQLiteInput* __fastcall GetItems(int AIndex);
	int __fastcall GetCount();
	
public:
	__fastcall TSQLiteInputs();
	__fastcall virtual ~TSQLiteInputs();
	__property int Count = {read=GetCount, nodefault};
	__property TSQLiteInput* Inputs[int AIndex] = {read=GetItems/*, default*/};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteOutput : public TSQLiteFuncVar
{
	typedef TSQLiteFuncVar inherited;
	
private:
	void *FHandle;
	System::UnicodeString FErrorText;
	int FErrorCode;
	void __fastcall SetErrorCode(const int AValue);
	void __fastcall SetErrorText(const System::UnicodeString AValue);
	
protected:
	virtual void __fastcall InternalSetData(void * AValue, int ASize, int AIntDataType);
	virtual bool __fastcall InternalGetData(void * &AValue, int &ASize, int &AIntDataType);
	
public:
	__property void * Handle = {read=FHandle, write=FHandle};
	__property int ErrorCode = {read=FErrorCode, write=SetErrorCode, nodefault};
	__property System::UnicodeString ErrorText = {read=FErrorText, write=SetErrorText};
public:
	/* TSQLiteValue.Create */ inline __fastcall TSQLiteOutput(TSQLiteDatabase* ADatabase) : TSQLiteFuncVar(ADatabase) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TSQLiteOutput() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TSQLiteFunction : public TSQLiteExtension
{
	typedef TSQLiteExtension inherited;
	
private:
	int FArgs;
	bool FAggregate;
	bool FDeterministic;
	TSQLiteFunctionCalculateEvent FOnCalculate;
	TSQLiteFunctionFinalizeEvent FOnFinalize;
	
protected:
	virtual void __fastcall InternalInstall(TSQLiteDatabase* ADatabase);
	virtual void __fastcall DoCalculate(TSQLiteFunctionInstance* AData);
	virtual void __fastcall DoFinalize(TSQLiteFunctionInstance* AData);
	
public:
	__property int Args = {read=FArgs, write=FArgs, nodefault};
	__property bool Aggregate = {read=FAggregate, write=FAggregate, nodefault};
	__property bool Deterministic = {read=FDeterministic, write=FDeterministic, nodefault};
	__property TSQLiteFunctionCalculateEvent OnCalculate = {read=FOnCalculate, write=FOnCalculate};
	__property TSQLiteFunctionFinalizeEvent OnFinalize = {read=FOnFinalize, write=FOnFinalize};
public:
	/* TSQLiteExtension.Create */ inline __fastcall virtual TSQLiteFunction(TSQLiteLib* ALib) : TSQLiteExtension(ALib) { }
	/* TSQLiteExtension.Destroy */ inline __fastcall virtual ~TSQLiteFunction() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteFunctionInstance : public TSQLiteExtensionInstance
{
	typedef TSQLiteExtensionInstance inherited;
	
private:
	TSQLiteInputs* FInputs;
	TSQLiteOutput* FOutput;
	System::TObject* FUserData;
	TSQLiteFunction* __fastcall GetFunc();
	
protected:
	void __fastcall DoCalculate(void * context, int nargs, Firedac::Phys::Sqlitecli::ppsqlite3_value args);
	void __fastcall DoFinalize(void * context);
	
public:
	__fastcall virtual TSQLiteFunctionInstance(TSQLiteDatabase* ADB, TSQLiteFunction* AFunc);
	__fastcall virtual ~TSQLiteFunctionInstance();
	__property TSQLiteFunction* Func = {read=GetFunc};
	__property TSQLiteInputs* Inputs = {read=FInputs};
	__property TSQLiteOutput* Output = {read=FOutput};
	__property System::TObject* UserData = {read=FUserData, write=FUserData};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TSQLiteExpressionFunction : public TSQLiteFunction
{
	typedef TSQLiteFunction inherited;
	
private:
	Firedac::Stan::Expr::TFDExpressionFunctionDesc* FDesc;
	
protected:
	__classmethod virtual void __fastcall Register(TSQLiteLib* ALib);
	virtual void __fastcall InternalInstall(TSQLiteDatabase* ADatabase);
	virtual void __fastcall DoCalculate(TSQLiteFunctionInstance* AData);
	
public:
	__fastcall TSQLiteExpressionFunction(TSQLiteLib* ALib, Firedac::Stan::Expr::TFDExpressionFunctionDesc* ADesc, int AArgs);
	__property Firedac::Stan::Expr::TFDExpressionFunctionDesc* Desc = {read=FDesc};
public:
	/* TSQLiteExtension.Create */ inline __fastcall virtual TSQLiteExpressionFunction(TSQLiteLib* ALib) : TSQLiteFunction(ALib) { }
	/* TSQLiteExtension.Destroy */ inline __fastcall virtual ~TSQLiteExpressionFunction() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteExpressionFunctionInstance : public TSQLiteFunctionInstance
{
	typedef TSQLiteFunctionInstance inherited;
	
	
private:
	typedef System::DynamicArray<System::Variant> _TSQLiteExpressionFunctionInstance__1;
	
	
private:
	_TSQLiteExpressionFunctionInstance__1 FFuncArgs;
	void __fastcall InternalCalculate();
	
public:
	__fastcall virtual TSQLiteExpressionFunctionInstance(TSQLiteDatabase* ADatabase, TSQLiteFunction* AFunc);
public:
	/* TSQLiteFunctionInstance.Destroy */ inline __fastcall virtual ~TSQLiteExpressionFunctionInstance() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TFDPhysSQLiteLastAutoGenFunc : public TSQLiteFunction
{
	typedef TSQLiteFunction inherited;
	
protected:
	virtual void __fastcall DoCalculate(TSQLiteFunctionInstance* AData);
	
public:
	__fastcall virtual TFDPhysSQLiteLastAutoGenFunc(TSQLiteLib* ALib);
public:
	/* TSQLiteExtension.Destroy */ inline __fastcall virtual ~TFDPhysSQLiteLastAutoGenFunc() { }
	
};


class PASCALIMPLEMENTATION TSQLiteRTree : public TSQLiteExtension
{
	typedef TSQLiteExtension inherited;
	
private:
	TSQLiteRTreeCalculateEvent FOnCalculate;
	TSQLiteRTreeFinalizeEvent FOnFinalize;
	
protected:
	virtual void __fastcall InternalInstall(TSQLiteDatabase* ADatabase);
	virtual bool __fastcall DoCalculate(TSQLiteRTreeData* AData);
	virtual void __fastcall DoFinalize(TSQLiteRTreeData* AData);
	
public:
	__property TSQLiteRTreeCalculateEvent OnCalculate = {read=FOnCalculate, write=FOnCalculate};
	__property TSQLiteRTreeFinalizeEvent OnFinalize = {read=FOnFinalize, write=FOnFinalize};
public:
	/* TSQLiteExtension.Create */ inline __fastcall virtual TSQLiteRTree(TSQLiteLib* ALib) : TSQLiteExtension(ALib) { }
	/* TSQLiteExtension.Destroy */ inline __fastcall virtual ~TSQLiteRTree() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteRTreeInstance : public TSQLiteExtensionInstance
{
	typedef TSQLiteExtensionInstance inherited;
	
private:
	int __fastcall DoCalculate(Firedac::Phys::Sqlitecli::psqlite3_rtree_geometry geom, int nCoord, Firedac::Phys::Sqlitecli::psqlite3_rtree_dbl aCoord, int &pRes);
	void __fastcall DoFinalize(TSQLiteRTreeData* AData);
	TSQLiteRTree* __fastcall GetRTree();
	
public:
	__fastcall TSQLiteRTreeInstance(TSQLiteDatabase* ADB, TSQLiteRTree* ARTree);
	__fastcall virtual ~TSQLiteRTreeInstance();
	__property TSQLiteRTree* RTree = {read=GetRTree};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteRTreeData : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TSQLiteRTreeInstance* FRTreeInst;
	TSQLiteRTreeDoubleArray FParams;
	TSQLiteRTreeDoubleArray FColumns;
	System::TObject* FUserData;
	
public:
	__property TSQLiteRTreeInstance* RTreeInst = {read=FRTreeInst};
	__property TSQLiteRTreeDoubleArray Params = {read=FParams};
	__property TSQLiteRTreeDoubleArray Columns = {read=FColumns};
	__property System::TObject* UserData = {read=FUserData, write=FUserData};
public:
	/* TObject.Create */ inline __fastcall TSQLiteRTreeData() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSQLiteRTreeData() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteBackup : public TSQLiteHandle
{
	typedef TSQLiteHandle inherited;
	
private:
	TSQLiteDatabase* FDestinationDatabase;
	TSQLiteDatabase* FSourceDatabase;
	System::UnicodeString FDestinationDBName;
	System::UnicodeString FSourceDBName;
	int FPagesPerStep;
	bool FWaitForLocks;
	int __fastcall GetPageCount();
	int __fastcall GetRemaining();
	
public:
	__fastcall TSQLiteBackup(TSQLiteLib* ALib, TSQLiteDatabase* ADestDatabase);
	void __fastcall Init();
	bool __fastcall Step();
	void __fastcall Finish();
	__property int Remaining = {read=GetRemaining, nodefault};
	__property int PageCount = {read=GetPageCount, nodefault};
	__property int PagesPerStep = {read=FPagesPerStep, write=FPagesPerStep, default=-1};
	__property bool WaitForLocks = {read=FWaitForLocks, write=FWaitForLocks, default=1};
	__property TSQLiteDatabase* SourceDatabase = {read=FSourceDatabase, write=FSourceDatabase};
	__property System::UnicodeString SourceDBName = {read=FSourceDBName, write=FSourceDBName};
	__property TSQLiteDatabase* DestinationDatabase = {read=FDestinationDatabase, write=FDestinationDatabase};
	__property System::UnicodeString DestinationDBName = {read=FDestinationDBName, write=FDestinationDBName};
public:
	/* TSQLiteHandle.CreateUsingHandle */ inline __fastcall TSQLiteBackup(void * AHandle) : TSQLiteHandle(AHandle) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TSQLiteBackup() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#pragma pack(push,1)
struct DECLSPEC_DRECORD FDsqlite3_vtab
{
public:
	Firedac::Phys::Sqlitecli::sqlite3_vtab pVTab;
	TSQLiteVModule* pFDModule;
	TSQLiteVTable* pFDTable;
};
#pragma pack(pop)


typedef FDsqlite3_vtab *PFDsqlite3_vtab;

typedef System::DynamicArray<System::UnicodeString> TSQLiteVArgs;

#pragma pack(push,1)
struct DECLSPEC_DRECORD FDsqlite3_vtab_cursor
{
public:
	Firedac::Phys::Sqlitecli::sqlite3_vtab pVTab;
	TSQLiteVModule* pFDModule;
	TSQLiteVTable* pFDTable;
	TSQLiteVCursor* pFDCursor;
};
#pragma pack(pop)


typedef FDsqlite3_vtab_cursor *PFDsqlite3_vtab_cursor;

struct DECLSPEC_DRECORD TSQLiteVColDef
{
public:
	System::UnicodeString FName;
	System::UnicodeString FDataType;
	bool FHidden;
};


typedef System::DynamicArray<TSQLiteVColDef> TSQLiteVColDefs;

enum DECLSPEC_DENUM TSQLiteVConstraintOp : unsigned int { coEqual, coGreater, coLess, coLessOrEqual, coGreaterOrEqual, coMatch, coLike, coGLOB, coRegExp, coNotEqual, coIsNot, coIsNotNull, coIsNull, coIs };

typedef TSQLiteVConstraint *PSQLiteVConstraint;

struct DECLSPEC_DRECORD TSQLiteVConstraint
{
public:
	int FColumn;
	TSQLiteVConstraintOp FOp;
	int FArgvIndex;
	bool FOmit;
};


typedef TSQLiteVOrderBy *PSQLiteVOrderBy;

struct DECLSPEC_DRECORD TSQLiteVOrderBy
{
public:
	int FColumn;
	bool FDesc;
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteVObject : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	int FResult;
	
protected:
	virtual void __fastcall Error(const System::UnicodeString AMsg) = 0 ;
	
public:
	virtual HRESULT __fastcall SafeCallException(System::TObject* ExceptObject, void * ExceptAddr);
public:
	/* TObject.Create */ inline __fastcall TSQLiteVObject() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSQLiteVObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteVModule : public TSQLiteVObject
{
	typedef TSQLiteVObject inherited;
	
private:
	TSQLiteLib* FLib;
	TSQLiteDatabase* FDatabase;
	Firedac::Phys::Sqlitecli::sqlite3_module FModule;
	FDsqlite3_vtab FDummyVTab;
	System::UnicodeString __fastcall BuildCreateTableStr(TSQLiteDatabase* ADatabase, const TSQLiteVColDef *ACols, const int ACols_High);
	HRESULT __safecall xCreateConnect(void * db, int argc, Firedac::Phys::Sqlitecli::PPUtf8 argv, Firedac::Phys::Sqlitecli::psqlite3_vtab &ppVTab, char * &pzErr, const bool AConnect);
	
protected:
	virtual void __fastcall Error(const System::UnicodeString AMsg);
	virtual TSQLiteVTable* __fastcall VTabCreate(const TSQLiteVArgs AArgs) = 0 ;
	virtual TSQLiteVTable* __fastcall VTabConnect(const TSQLiteVArgs AArgs) = 0 ;
	
public:
	__fastcall virtual TSQLiteVModule(const System::UnicodeString AName, TSQLiteDatabase* ADatabase);
	__fastcall virtual ~TSQLiteVModule();
	__property TSQLiteLib* Lib = {read=FLib};
	__property TSQLiteDatabase* Database = {read=FDatabase};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteVTableDef : public TSQLiteVObject
{
	typedef TSQLiteVObject inherited;
	
private:
	TSQLiteInputs* FInputs;
	System::Classes::TList* FOutputs;
	TSQLiteOutput* __fastcall GetColsOUT(int AIndex);
	
protected:
	TSQLiteDatabase* FDatabase;
	virtual TSQLiteInput* __fastcall GetColsIN(int AIndex);
	virtual int __fastcall GetCount();
	virtual void __fastcall AllocColumns(const int ACount);
	
public:
	__fastcall TSQLiteVTableDef(TSQLiteDatabase* ADatabase);
	__fastcall virtual ~TSQLiteVTableDef();
	__property TSQLiteInput* ColsIN[int AIndex] = {read=GetColsIN};
	__property TSQLiteOutput* ColsOUT[int AIndex] = {read=GetColsOUT};
	__property int Count = {read=GetCount, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteVTable : public TSQLiteVTableDef
{
	typedef TSQLiteVTableDef inherited;
	
	
private:
	typedef System::DynamicArray<TSQLiteVConstraint> _TSQLiteVTable__1;
	
	typedef System::DynamicArray<TSQLiteVOrderBy> _TSQLiteVTable__2;
	
	
private:
	FDsqlite3_vtab FrTab;
	void __fastcall CloseCursors();
	void __fastcall xDisconnect(Firedac::Phys::Sqlitecli::psqlite3_vtab pVTab);
	void __fastcall xDestroy(Firedac::Phys::Sqlitecli::psqlite3_vtab pVTab);
	HRESULT __safecall xRename(Firedac::Phys::Sqlitecli::psqlite3_vtab pVTab, char * zNew);
	HRESULT __safecall xSync(Firedac::Phys::Sqlitecli::psqlite3_vtab pVTab);
	HRESULT __safecall xBegin(Firedac::Phys::Sqlitecli::psqlite3_vtab pVTab);
	HRESULT __safecall xCommit(Firedac::Phys::Sqlitecli::psqlite3_vtab pVTab);
	HRESULT __safecall xRollback(Firedac::Phys::Sqlitecli::psqlite3_vtab pVTab);
	HRESULT __safecall xSavepoint(Firedac::Phys::Sqlitecli::psqlite3_vtab pVTab, int p);
	HRESULT __safecall xRelease(Firedac::Phys::Sqlitecli::psqlite3_vtab pVTab, int p);
	HRESULT __safecall xRollbackTo(Firedac::Phys::Sqlitecli::psqlite3_vtab pVTab, int p);
	HRESULT __safecall xFindFunction(Firedac::Phys::Sqlitecli::psqlite3_vtab pVTab, int nArg, char * zName, Firedac::Phys::Sqlitecli::Tsqlite3_func_callback &pxFunc, void * &ppArg, int &__xFindFunction_result);
	HRESULT __safecall xBestIndex(Firedac::Phys::Sqlitecli::psqlite3_vtab pVTab, Firedac::Phys::Sqlitecli::psqlite3_index_info info);
	HRESULT __safecall xUpdate(Firedac::Phys::Sqlitecli::psqlite3_vtab pVTab, int nArg, Firedac::Phys::Sqlitecli::ppsqlite3_value apArgs, __int64 &rowid);
	void __fastcall xOpen(Firedac::Phys::Sqlitecli::psqlite3_vtab pVTab, Firedac::Phys::Sqlitecli::psqlite3_vtab_cursor &ppCursor);
	void __fastcall xClose(Firedac::Phys::Sqlitecli::psqlite3_vtab_cursor cursor);
	
protected:
	TSQLiteVModule* FModule;
	System::UnicodeString FName;
	_TSQLiteVTable__1 FConstraints;
	_TSQLiteVTable__2 FOrderBys;
	System::Classes::TList* FCursors;
	virtual TSQLiteInput* __fastcall GetColsIN(int AIndex);
	virtual int __fastcall GetCount();
	virtual void __fastcall AllocColumns(const int ACount);
	virtual void __fastcall Error(const System::UnicodeString AMsg);
	virtual void __fastcall DescribeColumn(const System::UnicodeString AColName, /* out */ bool &ANotNull, /* out */ bool &AInPK, /* out */ bool &AAutoInc) = 0 ;
	virtual TSQLiteVColDefs __fastcall DescribeColumns() = 0 ;
	virtual void __fastcall VTabDisconnect() = 0 ;
	virtual void __fastcall VTabDestroy() = 0 ;
	virtual void __fastcall VTabRename(const System::UnicodeString ANewName) = 0 ;
	virtual void __fastcall VTabSync() = 0 ;
	virtual void __fastcall VTabBegin() = 0 ;
	virtual void __fastcall VTabCommit() = 0 ;
	virtual void __fastcall VTabRollback() = 0 ;
	virtual void __fastcall VTabSavepoint(const int AVIndex) = 0 ;
	virtual void __fastcall VTabRelease(const int AVIndex) = 0 ;
	virtual void __fastcall VTabRollbackTo(const int AVIndex) = 0 ;
	virtual bool __fastcall VTabFindFunction(int ACount, const System::UnicodeString AName, Firedac::Phys::Sqlitecli::Tsqlite3_func_callback &AFunc, void * &AArg) = 0 ;
	virtual void __fastcall VTabBestIndex(int &AIdxNum, System::UnicodeString &AIdxStr, bool &AOrdered, bool &AFiltered, double &ACost) = 0 ;
	virtual void __fastcall VTabInsert(__int64 &ARowid, bool AOrUpdate) = 0 ;
	virtual void __fastcall VTabUpdate(const __int64 AUpdRowid, const __int64 ANewRowid) = 0 ;
	virtual void __fastcall VTabDelete(const __int64 ARowid) = 0 ;
	virtual TSQLiteVCursor* __fastcall VTabOpen() = 0 ;
	virtual void __fastcall VTabClose(TSQLiteVCursor* ACursor);
	
public:
	__fastcall TSQLiteVTable(TSQLiteVModule* AModule, const System::UnicodeString AName);
	__fastcall virtual ~TSQLiteVTable();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLiteVCursor : public TSQLiteVTableDef
{
	typedef TSQLiteVTableDef inherited;
	
private:
	FDsqlite3_vtab_cursor FrCursor;
	HRESULT __safecall xFilter(Firedac::Phys::Sqlitecli::psqlite3_vtab_cursor cursor, int idxNum, char * idxStr, int argc, Firedac::Phys::Sqlitecli::ppsqlite3_value argv);
	HRESULT __safecall xNext(Firedac::Phys::Sqlitecli::psqlite3_vtab_cursor cursor);
	HRESULT __safecall xEof(Firedac::Phys::Sqlitecli::psqlite3_vtab_cursor cursor, int &__xEof_result);
	HRESULT __safecall xColumn(Firedac::Phys::Sqlitecli::psqlite3_vtab_cursor cursor, void * context, int index);
	HRESULT __safecall xRowid(Firedac::Phys::Sqlitecli::psqlite3_vtab_cursor cursor, __int64 &pRowid);
	
protected:
	TSQLiteVTable* FTable;
	bool FActive;
	virtual void __fastcall Error(const System::UnicodeString AMsg);
	virtual void __fastcall VTabFilter(const int AIndex, const System::UnicodeString AIndexStr) = 0 ;
	virtual void __fastcall VTabNext() = 0 ;
	virtual bool __fastcall VTabEof() = 0 ;
	virtual void __fastcall VTabColumn(const int AIndex) = 0 ;
	virtual void __fastcall VTabRowid(__int64 &ARowid) = 0 ;
	virtual void __fastcall VTabClose() = 0 ;
	
public:
	__fastcall TSQLiteVCursor(TSQLiteVTable* ATable);
	__fastcall virtual ~TSQLiteVCursor();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE int C_FD_SQLiteUndefRowid;
extern DELPHI_PACKAGE TSQLiteExtensionManager* __fastcall FDExtensionManager(void);
}	/* namespace Sqlitewrapper */
}	/* namespace Phys */
}	/* namespace Firedac */
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
#endif	// Firedac_Phys_SqlitewrapperHPP
