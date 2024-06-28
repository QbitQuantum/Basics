// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.MongoDBWrapper.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_MongodbwrapperHPP
#define Firedac_Phys_MongodbwrapperHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Rtti.hpp>
#include <System.JSON.Types.hpp>
#include <System.JSON.Readers.hpp>
#include <System.JSON.Writers.hpp>
#include <System.JSON.BSON.hpp>
#include <System.JSON.Builders.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Phys.MongoDBCli.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Mongodbwrapper
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMongoClientLib;
class DELPHICLASS TMongoBSONLib;
class DELPHICLASS TMongoObject;
class DELPHICLASS TFDMongoError;
class DELPHICLASS EMongoNativeException;
class DELPHICLASS TMongoError;
class DELPHICLASS TMongoEnv;
class DELPHICLASS TMongoOID;
class DELPHICLASS TMongoDocument;
class DELPHICLASS TMongoReadPreference;
class DELPHICLASS TMongoWriteConcern;
template<typename T> class DELPHICLASS TMongoExpression__1;
__interface DELPHIINTERFACE IMongoCursor;
typedef System::DelphiInterface<IMongoCursor> _di_IMongoCursor;
class DELPHICLASS TMongoPipeline;
class DELPHICLASS TMongoQuery;
class DELPHICLASS TMongoCommand;
class DELPHICLASS TMongoUpdate;
class DELPHICLASS TMongoSelector;
class DELPHICLASS TMongoInsert;
class DELPHICLASS TMongoIndex;
class DELPHICLASS TMongoCursor;
class DELPHICLASS TMongoConnection;
struct TMongoConnectionHelper /* Helper for class 'TMongoConnection*' */;
class DELPHICLASS TMongoDatabase;
class DELPHICLASS TMongoCollection;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TMongoQueryFlag : unsigned int { TailableCursors, SlaveOk, NoCursorTimeout, AwaitData, Exhaust, Partial };

typedef System::Set<TMongoQueryFlag, _DELPHI_SET_ENUMERATOR(TMongoQueryFlag::TailableCursors), _DELPHI_SET_ENUMERATOR(TMongoQueryFlag::Partial)> TMongoQueryFlags;

class PASCALIMPLEMENTATION TMongoClientLib : public Firedac::Stan::Util::TFDLibrary
{
	typedef Firedac::Stan::Util::TFDLibrary inherited;
	
protected:
	virtual void __fastcall LoadEntries();
	
public:
	Firedac::Phys::Mongodbcli::Tmongoc_client_new Fmongoc_client_new;
	Firedac::Phys::Mongodbcli::Tmongoc_client_destroy Fmongoc_client_destroy;
	Firedac::Phys::Mongodbcli::Tmongoc_client_command Fmongoc_client_command;
	Firedac::Phys::Mongodbcli::Tmongoc_client_command_simple Fmongoc_client_command_simple;
	Firedac::Phys::Mongodbcli::Tmongoc_client_kill_cursor Fmongoc_client_kill_cursor;
	Firedac::Phys::Mongodbcli::Tmongoc_client_get_database Fmongoc_client_get_database;
	Firedac::Phys::Mongodbcli::Tmongoc_client_get_collection Fmongoc_client_get_collection;
	Firedac::Phys::Mongodbcli::Tmongoc_client_find_databases Fmongoc_client_find_databases;
	Firedac::Phys::Mongodbcli::Tmongoc_client_get_server_status Fmongoc_client_get_server_status;
	Firedac::Phys::Mongodbcli::Tmongoc_client_get_max_message_size Fmongoc_client_get_max_message_size;
	Firedac::Phys::Mongodbcli::Tmongoc_client_get_max_bson_size Fmongoc_client_get_max_bson_size;
	Firedac::Phys::Mongodbcli::Tmongoc_client_get_write_concern Fmongoc_client_get_write_concern;
	Firedac::Phys::Mongodbcli::Tmongoc_client_set_write_concern Fmongoc_client_set_write_concern;
	Firedac::Phys::Mongodbcli::Tmongoc_client_get_read_prefs Fmongoc_client_get_read_prefs;
	Firedac::Phys::Mongodbcli::Tmongoc_client_set_read_prefs Fmongoc_client_set_read_prefs;
	Firedac::Phys::Mongodbcli::Tmongoc_client_set_ssl_opts Fmongoc_client_set_ssl_opts;
	Firedac::Phys::Mongodbcli::Tmongoc_client_get_uri Fmongoc_client_get_uri;
	Firedac::Phys::Mongodbcli::Tmongoc_uri_get_string Fmongoc_uri_get_string;
	Firedac::Phys::Mongodbcli::Tmongoc_bulk_operation_new Fmongoc_bulk_operation_new;
	Firedac::Phys::Mongodbcli::Tmongoc_bulk_operation_destroy Fmongoc_bulk_operation_destroy;
	Firedac::Phys::Mongodbcli::Tmongoc_bulk_operation_execute Fmongoc_bulk_operation_execute;
	Firedac::Phys::Mongodbcli::Tmongoc_bulk_operation_insert Fmongoc_bulk_operation_insert;
	Firedac::Phys::Mongodbcli::Tmongoc_bulk_operation_remove Fmongoc_bulk_operation_remove;
	Firedac::Phys::Mongodbcli::Tmongoc_bulk_operation_remove_one Fmongoc_bulk_operation_remove_one;
	Firedac::Phys::Mongodbcli::Tmongoc_bulk_operation_replace_one Fmongoc_bulk_operation_replace_one;
	Firedac::Phys::Mongodbcli::Tmongoc_bulk_operation_update Fmongoc_bulk_operation_update;
	Firedac::Phys::Mongodbcli::Tmongoc_bulk_operation_update_one Fmongoc_bulk_operation_update_one;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_aggregate Fmongoc_collection_aggregate;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_destroy Fmongoc_collection_destroy;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_command Fmongoc_collection_command;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_command_simple Fmongoc_collection_command_simple;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_count Fmongoc_collection_count;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_count_with_opts Fmongoc_collection_count_with_opts;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_drop Fmongoc_collection_drop;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_drop_index Fmongoc_collection_drop_index;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_create_index Fmongoc_collection_create_index;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_find_indexes Fmongoc_collection_find_indexes;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_find Fmongoc_collection_find;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_insert Fmongoc_collection_insert;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_update Fmongoc_collection_update;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_save Fmongoc_collection_save;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_remove Fmongoc_collection_remove;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_rename Fmongoc_collection_rename;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_find_and_modify Fmongoc_collection_find_and_modify;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_stats Fmongoc_collection_stats;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_create_bulk_operation Fmongoc_collection_create_bulk_operation;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_get_read_prefs Fmongoc_collection_get_read_prefs;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_set_read_prefs Fmongoc_collection_set_read_prefs;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_get_write_concern Fmongoc_collection_get_write_concern;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_set_write_concern Fmongoc_collection_set_write_concern;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_get_name Fmongoc_collection_get_name;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_get_last_error Fmongoc_collection_get_last_error;
	Firedac::Phys::Mongodbcli::Tmongoc_collection_validate Fmongoc_collection_validate;
	Firedac::Phys::Mongodbcli::Tmongoc_cursor_destroy Fmongoc_cursor_destroy;
	Firedac::Phys::Mongodbcli::Tmongoc_cursor_more Fmongoc_cursor_more;
	Firedac::Phys::Mongodbcli::Tmongoc_cursor_next Fmongoc_cursor_next;
	Firedac::Phys::Mongodbcli::Tmongoc_cursor_error Fmongoc_cursor_error;
	Firedac::Phys::Mongodbcli::Tmongoc_cursor_current Fmongoc_cursor_current;
	Firedac::Phys::Mongodbcli::Tmongoc_cursor_is_alive Fmongoc_cursor_is_alive;
	Firedac::Phys::Mongodbcli::Tmongoc_database_get_name Fmongoc_database_get_name;
	Firedac::Phys::Mongodbcli::Tmongoc_database_remove_user Fmongoc_database_remove_user;
	Firedac::Phys::Mongodbcli::Tmongoc_database_remove_all_users Fmongoc_database_remove_all_users;
	Firedac::Phys::Mongodbcli::Tmongoc_database_add_user Fmongoc_database_add_user;
	Firedac::Phys::Mongodbcli::Tmongoc_database_destroy Fmongoc_database_destroy;
	Firedac::Phys::Mongodbcli::Tmongoc_database_command Fmongoc_database_command;
	Firedac::Phys::Mongodbcli::Tmongoc_database_command_simple Fmongoc_database_command_simple;
	Firedac::Phys::Mongodbcli::Tmongoc_database_drop Fmongoc_database_drop;
	Firedac::Phys::Mongodbcli::Tmongoc_database_has_collection Fmongoc_database_has_collection;
	Firedac::Phys::Mongodbcli::Tmongoc_database_create_collection Fmongoc_database_create_collection;
	Firedac::Phys::Mongodbcli::Tmongoc_database_get_read_prefs Fmongoc_database_get_read_prefs;
	Firedac::Phys::Mongodbcli::Tmongoc_database_set_read_prefs Fmongoc_database_set_read_prefs;
	Firedac::Phys::Mongodbcli::Tmongoc_database_get_write_concern Fmongoc_database_get_write_concern;
	Firedac::Phys::Mongodbcli::Tmongoc_database_set_write_concern Fmongoc_database_set_write_concern;
	Firedac::Phys::Mongodbcli::Tmongoc_database_find_collections Fmongoc_database_find_collections;
	Firedac::Phys::Mongodbcli::Tmongoc_database_get_collection Fmongoc_database_get_collection;
	Firedac::Phys::Mongodbcli::Tmongoc_index_opt_get_default Fmongoc_index_opt_get_default;
	Firedac::Phys::Mongodbcli::Tmongoc_index_opt_init Fmongoc_index_opt_init;
	Firedac::Phys::Mongodbcli::Tmongoc_init Fmongoc_init;
	Firedac::Phys::Mongodbcli::Tmongoc_cleanup Fmongoc_cleanup;
	Firedac::Phys::Mongodbcli::Tmongoc_log_set_handler Fmongoc_log_set_handler;
	Firedac::Phys::Mongodbcli::Tmongoc_log_default_handler Fmongoc_log_default_handler;
	Firedac::Phys::Mongodbcli::Tmongoc_log_level_str Fmongoc_log_level_str;
	Firedac::Phys::Mongodbcli::Tmongoc_matcher_new Fmongoc_matcher_new;
	Firedac::Phys::Mongodbcli::Tmongoc_matcher_match Fmongoc_matcher_match;
	Firedac::Phys::Mongodbcli::Tmongoc_matcher_destroy Fmongoc_matcher_destroy;
	Firedac::Phys::Mongodbcli::Tmongoc_read_prefs_new Fmongoc_read_prefs_new;
	Firedac::Phys::Mongodbcli::Tmongoc_read_prefs_destroy Fmongoc_read_prefs_destroy;
	Firedac::Phys::Mongodbcli::Tmongoc_read_prefs_copy Fmongoc_read_prefs_copy;
	Firedac::Phys::Mongodbcli::Tmongoc_read_prefs_get_mode Fmongoc_read_prefs_get_mode;
	Firedac::Phys::Mongodbcli::Tmongoc_read_prefs_set_mode Fmongoc_read_prefs_set_mode;
	Firedac::Phys::Mongodbcli::Tmongoc_read_prefs_get_tags Fmongoc_read_prefs_get_tags;
	Firedac::Phys::Mongodbcli::Tmongoc_read_prefs_set_tags Fmongoc_read_prefs_set_tags;
	Firedac::Phys::Mongodbcli::Tmongoc_read_prefs_add_tag Fmongoc_read_prefs_add_tag;
	Firedac::Phys::Mongodbcli::Tmongoc_read_prefs_is_valid Fmongoc_read_prefs_is_valid;
	Firedac::Phys::Mongodbcli::Tmongoc_write_concern_new Fmongoc_write_concern_new;
	Firedac::Phys::Mongodbcli::Tmongoc_write_concern_destroy Fmongoc_write_concern_destroy;
	Firedac::Phys::Mongodbcli::Tmongoc_write_concern_copy Fmongoc_write_concern_copy;
	Firedac::Phys::Mongodbcli::Tmongoc_write_concern_get_fsync Fmongoc_write_concern_get_fsync;
	Firedac::Phys::Mongodbcli::Tmongoc_write_concern_set_fsync Fmongoc_write_concern_set_fsync;
	Firedac::Phys::Mongodbcli::Tmongoc_write_concern_get_journal Fmongoc_write_concern_get_journal;
	Firedac::Phys::Mongodbcli::Tmongoc_write_concern_set_journal Fmongoc_write_concern_set_journal;
	Firedac::Phys::Mongodbcli::Tmongoc_write_concern_get_w Fmongoc_write_concern_get_w;
	Firedac::Phys::Mongodbcli::Tmongoc_write_concern_set_w Fmongoc_write_concern_set_w;
	Firedac::Phys::Mongodbcli::Tmongoc_write_concern_get_wtag Fmongoc_write_concern_get_wtag;
	Firedac::Phys::Mongodbcli::Tmongoc_write_concern_set_wtag Fmongoc_write_concern_set_wtag;
	Firedac::Phys::Mongodbcli::Tmongoc_write_concern_get_wtimeout Fmongoc_write_concern_get_wtimeout;
	Firedac::Phys::Mongodbcli::Tmongoc_write_concern_set_wtimeout Fmongoc_write_concern_set_wtimeout;
	Firedac::Phys::Mongodbcli::Tmongoc_write_concern_get_wmajority Fmongoc_write_concern_get_wmajority;
	Firedac::Phys::Mongodbcli::Tmongoc_write_concern_set_wmajority Fmongoc_write_concern_set_wmajority;
	__fastcall TMongoClientLib(System::TObject* AOwningObj);
	HIDESBASE void __fastcall Load(const System::UnicodeString AVendorHome, const System::UnicodeString AVendorLib);
public:
	/* TFDLibrary.Destroy */ inline __fastcall virtual ~TMongoClientLib() { }
	
};


class PASCALIMPLEMENTATION TMongoBSONLib : public Firedac::Stan::Util::TFDLibrary
{
	typedef Firedac::Stan::Util::TFDLibrary inherited;
	
private:
	TMongoClientLib* FCLib;
	
protected:
	virtual void __fastcall LoadEntries();
	
public:
	Firedac::Phys::Mongodbcli::Tbson_context_new Fbson_context_new;
	Firedac::Phys::Mongodbcli::Tbson_context_destroy Fbson_context_destroy;
	Firedac::Phys::Mongodbcli::Tbson_context_get_default Fbson_context_get_default;
	Firedac::Phys::Mongodbcli::Tbson_oid_compare Fbson_oid_compare;
	Firedac::Phys::Mongodbcli::Tbson_oid_copy Fbson_oid_copy;
	Firedac::Phys::Mongodbcli::Tbson_oid_init Fbson_oid_init;
	Firedac::Phys::Mongodbcli::Tbson_oid_init_from_string Fbson_oid_init_from_string;
	Firedac::Phys::Mongodbcli::Tbson_oid_to_string Fbson_oid_to_string;
	Firedac::Phys::Mongodbcli::Tbson_oid_get_time_t Fbson_oid_get_time_t;
	Firedac::Phys::Mongodbcli::Tbson_mem_set_vtable Fbson_mem_set_vtable;
	Firedac::Phys::Mongodbcli::Tbson_init Fbson_init;
	Firedac::Phys::Mongodbcli::Tbson_init_static Fbson_init_static;
	Firedac::Phys::Mongodbcli::Tbson_init Fbson_reinit;
	Firedac::Phys::Mongodbcli::Tbson_new Fbson_new;
	Firedac::Phys::Mongodbcli::Tbson_destroy Fbson_destroy;
	Firedac::Phys::Mongodbcli::Tbson_get_data Fbson_get_data;
	Firedac::Phys::Mongodbcli::Tbson_free Fbson_free;
	Firedac::Phys::Mongodbcli::Tbson_init_from_json Fbson_init_from_json;
	Firedac::Phys::Mongodbcli::Tbson_as_json Fbson_as_json;
	Firedac::Phys::Mongodbcli::Tbson_copy_to Fbson_copy_to;
	Firedac::Phys::Mongodbcli::Tbson_concat Fbson_concat;
	Firedac::Phys::Mongodbcli::Tbson_append_array Fbson_append_array;
	Firedac::Phys::Mongodbcli::Tbson_append_document Fbson_append_document;
	Firedac::Phys::Mongodbcli::Tbson_append_bool Fbson_append_bool;
	Firedac::Phys::Mongodbcli::Tbson_append_code Fbson_append_code;
	Firedac::Phys::Mongodbcli::Tbson_append_code_with_scope Fbson_append_code_with_scope;
	Firedac::Phys::Mongodbcli::Tbson_append_double Fbson_append_double;
	Firedac::Phys::Mongodbcli::Tbson_append_int32 Fbson_append_int32;
	Firedac::Phys::Mongodbcli::Tbson_append_int64 Fbson_append_int64;
	Firedac::Phys::Mongodbcli::Tbson_append_null Fbson_append_null;
	Firedac::Phys::Mongodbcli::Tbson_append_oid Fbson_append_oid;
	Firedac::Phys::Mongodbcli::Tbson_append_regex Fbson_append_regex;
	Firedac::Phys::Mongodbcli::Tbson_append_utf8 Fbson_append_utf8;
	Firedac::Phys::Mongodbcli::Tbson_append_time_t Fbson_append_time_t;
	Firedac::Phys::Mongodbcli::Tbson_append_timeval Fbson_append_timeval;
	Firedac::Phys::Mongodbcli::Tbson_append_date_time Fbson_append_date_time;
	Firedac::Phys::Mongodbcli::Tbson_append_binary Fbson_append_binary;
	Firedac::Phys::Mongodbcli::Tbson_iter_init Fbson_iter_init;
	Firedac::Phys::Mongodbcli::Tbson_iter_find Fbson_iter_find;
	Firedac::Phys::Mongodbcli::Tbson_iter_find_descendant Fbson_iter_find_descendant;
	Firedac::Phys::Mongodbcli::Tbson_iter_next Fbson_iter_next;
	Firedac::Phys::Mongodbcli::Tbson_iter_recurse Fbson_iter_recurse;
	Firedac::Phys::Mongodbcli::Tbson_iter_key Fbson_iter_key;
	Firedac::Phys::Mongodbcli::Tbson_iter_type Fbson_iter_type;
	Firedac::Phys::Mongodbcli::Tbson_iter_binary Fbson_iter_binary;
	Firedac::Phys::Mongodbcli::Tbson_iter_bool Fbson_iter_bool;
	Firedac::Phys::Mongodbcli::Tbson_iter_code Fbson_iter_code;
	Firedac::Phys::Mongodbcli::Tbson_iter_double Fbson_iter_double;
	Firedac::Phys::Mongodbcli::Tbson_iter_int32 Fbson_iter_int32;
	Firedac::Phys::Mongodbcli::Tbson_iter_int64 Fbson_iter_int64;
	Firedac::Phys::Mongodbcli::Tbson_iter_oid Fbson_iter_oid;
	Firedac::Phys::Mongodbcli::Tbson_iter_regex Fbson_iter_regex;
	Firedac::Phys::Mongodbcli::Tbson_iter_utf8 Fbson_iter_utf8;
	Firedac::Phys::Mongodbcli::Tbson_iter_time_t Fbson_iter_time_t;
	Firedac::Phys::Mongodbcli::Tbson_iter_date_time Fbson_iter_date_time;
	__fastcall TMongoBSONLib(TMongoClientLib* ACLib);
	HIDESBASE void __fastcall Load();
	virtual void __fastcall Unload();
	__property TMongoClientLib* CLib = {read=FCLib};
public:
	/* TFDLibrary.Destroy */ inline __fastcall virtual ~TMongoBSONLib() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoObject : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TMongoEnv* FEnv;
	void *FHandle;
	bool FOwnHandle;
	System::TObject* FOwningObj;
	void * __fastcall GetHandle();
	void __fastcall SetHandle(const void * AValue);
	TMongoError* __fastcall GetError();
	TMongoClientLib* __fastcall GetCLib();
	TMongoBSONLib* __fastcall GetBLib();
	
protected:
	virtual void __fastcall InternalFreeHandle();
	virtual void __fastcall FreeHandle();
	virtual void __fastcall HandleAllocated();
	__fastcall TMongoObject(TMongoEnv* AEnv, System::TObject* AOwningObj)/* overload */;
	__fastcall TMongoObject(TMongoEnv* AEnv, System::TObject* AOwningObj, void * AHandle)/* overload */;
	
public:
	__fastcall virtual ~TMongoObject();
	__property TMongoEnv* Env = {read=FEnv};
	__property TMongoClientLib* CLib = {read=GetCLib};
	__property TMongoBSONLib* BLib = {read=GetBLib};
	__property TMongoError* Error = {read=GetError};
	__property System::TObject* OwningObj = {read=FOwningObj};
	__property void * Handle = {read=GetHandle, write=SetHandle};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFDMongoError : public Firedac::Stan::Error::TFDDBError
{
	typedef Firedac::Stan::Error::TFDDBError inherited;
	
private:
	unsigned FDomain;
	
protected:
	virtual void __fastcall Assign(Firedac::Stan::Error::TFDDBError* ASrc);
	virtual void __fastcall LoadFromStorage(const Firedac::Stan::Intf::_di_IFDStanStorage AStorage);
	virtual void __fastcall SaveToStorage(const Firedac::Stan::Intf::_di_IFDStanStorage AStorage);
	
public:
	__property unsigned Domain = {read=FDomain, nodefault};
public:
	/* TFDDBError.Create */ inline __fastcall virtual TFDMongoError()/* overload */ : Firedac::Stan::Error::TFDDBError() { }
	/* TFDDBError.Create */ inline __fastcall virtual TFDMongoError(int ALevel, int AErrorCode, const System::UnicodeString AMessage, const System::UnicodeString AObjName, Firedac::Stan::Error::TFDCommandExceptionKind AKind, int ACmdOffset, int ARowIndex)/* overload */ : Firedac::Stan::Error::TFDDBError(ALevel, AErrorCode, AMessage, AObjName, AKind, ACmdOffset, ARowIndex) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDMongoError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EMongoNativeException : public Firedac::Stan::Error::EFDDBEngineException
{
	typedef Firedac::Stan::Error::EFDDBEngineException inherited;
	
public:
	TFDMongoError* operator[](int AIndex) { return this->Errors[AIndex]; }
	
private:
	HIDESBASE TFDMongoError* __fastcall GetErrors(int AIndex);
	
protected:
	virtual Firedac::Stan::Error::TFDDBErrorClass __fastcall GetErrorClass();
	HIDESBASE TFDMongoError* __fastcall AppendError(int ALevel, int AErrorCode, unsigned ADomain, const System::UnicodeString AMessage, int ARowIndex)/* overload */;
	
public:
	__fastcall EMongoNativeException(TMongoError* AError)/* overload */;
	__property TFDMongoError* Errors[int AIndex] = {read=GetErrors/*, default*/};
public:
	/* EFDDBEngineException.Create */ inline __fastcall virtual EMongoNativeException()/* overload */ : Firedac::Stan::Error::EFDDBEngineException() { }
	/* EFDDBEngineException.Create */ inline __fastcall EMongoNativeException(int AADCode, const System::UnicodeString AMessage)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(AADCode, AMessage) { }
	/* EFDDBEngineException.Destroy */ inline __fastcall virtual ~EMongoNativeException() { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EMongoNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Firedac::Stan::Error::EFDDBEngineException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EMongoNativeException(NativeUInt Ident)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EMongoNativeException(System::PResStringRec ResStringRec)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EMongoNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EMongoNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EMongoNativeException(const System::UnicodeString Msg, int AHelpContext) : Firedac::Stan::Error::EFDDBEngineException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EMongoNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Firedac::Stan::Error::EFDDBEngineException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMongoNativeException(NativeUInt Ident, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMongoNativeException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMongoNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMongoNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, Args, Args_High, AHelpContext) { }
	
	/* Hoisted overloads: */
	
protected:
	inline Firedac::Stan::Error::TFDDBError* __fastcall  AppendError(){ return Firedac::Stan::Error::EFDDBEngineException::AppendError(); }
	
public:
	inline Firedac::Stan::Error::TFDDBError* __fastcall  AppendError(int ALevel, int AErrorCode, const System::UnicodeString AMessage, const System::UnicodeString AObjName, Firedac::Stan::Error::TFDCommandExceptionKind AKind, int ACmdOffset, int ARowIndex){ return Firedac::Stan::Error::EFDDBEngineException::AppendError(ALevel, AErrorCode, AMessage, AObjName, AKind, ACmdOffset, ARowIndex); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoError : public TMongoObject
{
	typedef TMongoObject inherited;
	
private:
	Firedac::Phys::Mongodbcli::bson_error_t FBError;
	
public:
	void __fastcall CheckError(System::TObject* AInitiator = (System::TObject*)(0x0), const System::UnicodeString AMethod = System::UnicodeString());
	__property Firedac::Phys::Mongodbcli::bson_error_t BError = {read=FBError};
protected:
	/* TMongoObject.Create */ inline __fastcall TMongoError(TMongoEnv* AEnv, System::TObject* AOwningObj)/* overload */ : TMongoObject(AEnv, AOwningObj) { }
	/* TMongoObject.Create */ inline __fastcall TMongoError(TMongoEnv* AEnv, System::TObject* AOwningObj, void * AHandle)/* overload */ : TMongoObject(AEnv, AOwningObj, AHandle) { }
	
public:
	/* TMongoObject.Destroy */ inline __fastcall virtual ~TMongoError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoEnv : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TMongoClientLib* FCLib;
	TMongoBSONLib* FBLib;
	TMongoError* FError;
	Firedac::Stan::Util::TFDBuffer* FBuffer;
	Firedac::Stan::Util::TFDEncoder* FANSI;
	Firedac::Stan::Util::TFDEncoder* FUTF8;
	System::TObject* FOwningObj;
	System::Json::Types::TJsonDateTimeZoneHandling FDateTimeZoneHandling;
	Firedac::Stan::Intf::_di_IFDMoniClient FMonitor;
	bool FTracing;
	bool __fastcall GetTracing();
	
public:
	__fastcall TMongoEnv(TMongoClientLib* ACLib, TMongoBSONLib* ABLib, System::TObject* AOwningObj);
	__fastcall virtual ~TMongoEnv();
	TMongoDocument* __fastcall NewDoc();
	void __fastcall Trace(const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	void __fastcall Trace(Firedac::Stan::Intf::TFDMoniEventKind AKind, Firedac::Stan::Intf::TFDMoniEventStep AStep, const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	__property bool Tracing = {read=GetTracing, write=FTracing, nodefault};
	__property Firedac::Stan::Intf::_di_IFDMoniClient Monitor = {read=FMonitor, write=FMonitor};
	__property TMongoClientLib* CLib = {read=FCLib};
	__property TMongoBSONLib* BLib = {read=FBLib};
	__property TMongoError* Error = {read=FError};
	__property Firedac::Stan::Util::TFDEncoder* ANSI = {read=FANSI};
	__property Firedac::Stan::Util::TFDEncoder* UTF8 = {read=FUTF8};
	__property Firedac::Stan::Util::TFDBuffer* Buffer = {read=FBuffer};
	__property System::TObject* OwningObj = {read=FOwningObj};
	__property System::Json::Types::TJsonDateTimeZoneHandling DateTimeZoneHandling = {read=FDateTimeZoneHandling, write=FDateTimeZoneHandling, default=0};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoOID : public TMongoObject
{
	typedef TMongoObject inherited;
	
private:
	System::TDateTime __fastcall GetAsDateTime();
	System::UnicodeString __fastcall GetAsString();
	void __fastcall SetAsString(const System::UnicodeString AValue);
	System::Json::Types::TJsonOid __fastcall GetAsOid();
	void __fastcall SetAsOid(const System::Json::Types::TJsonOid &AValue);
	
protected:
	virtual void __fastcall InternalFreeHandle();
	
public:
	__fastcall TMongoOID(TMongoEnv* AEnv, System::TObject* AOwningObj);
	void __fastcall Init();
	void __fastcall Clear();
	void __fastcall Assign(TMongoOID* ASource);
	__property System::TDateTime AsDateTime = {read=GetAsDateTime};
	__property System::UnicodeString AsString = {read=GetAsString, write=SetAsString};
	__property System::Json::Types::TJsonOid AsOid = {read=GetAsOid, write=SetAsOid};
public:
	/* TMongoObject.Destroy */ inline __fastcall virtual ~TMongoOID() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoDocument : public TMongoObject
{
	typedef TMongoObject inherited;
	
	
private:
	enum class DECLSPEC_DENUM THandleType : unsigned int { ReadInternal, ReadExternal, WriteExternal, RTL };
	
	class DELPHICLASS TBuilder;
	class PASCALIMPLEMENTATION TBuilder : /*[[sealed]]*/ public System::Json::Builders::TJSONObjectBuilder
	{
		typedef System::Json::Builders::TJSONObjectBuilder inherited;
		
	private:
		TMongoDocument* FDoc;
		
	protected:
		virtual void __fastcall DoResetWriter(System::Json::Writers::TJsonWriter* AWriter);
		virtual System::Json::Readers::TJsonReader* __fastcall DoGetReader(System::Json::Writers::TJsonWriter* AWriter);
		virtual void __fastcall DoReleaseReader(System::Json::Writers::TJsonWriter* AWriter, System::Json::Readers::TJsonReader* AReader);
		virtual void __fastcall DoWriteCustomVariant(System::Json::Writers::TJsonWriter* AWriter, const System::Variant &AValue);
		
	public:
		__fastcall TBuilder(System::Json::Writers::TJsonWriter* const AJSONWriter, TMongoDocument* ADoc);
	public:
		/* TJSONCollectionBuilder.Destroy */ inline __fastcall virtual ~TBuilder() { }
		
	};
	
	
	class DELPHICLASS TIterator;
	class PASCALIMPLEMENTATION TIterator : /*[[sealed]]*/ public System::Json::Builders::TJSONIterator
	{
		typedef System::Json::Builders::TJSONIterator inherited;
		
	private:
		System::Classes::TMemoryStream* FStream;
		System::Json::Bson::TBsonReader* FReader;
		
	protected:
		virtual void __fastcall DoRewindReader(System::Json::Readers::TJsonReader* AReader);
		
	public:
		__fastcall TIterator(TMongoDocument* ADoc);
		__fastcall virtual ~TIterator();
	};
	
	
	
private:
	System::TObject* FParentObj;
	System::Classes::TMemoryStream* FStream;
	System::Json::Bson::TBsonWriter* FWriter;
	System::Json::Builders::TJSONObjectBuilder* FBuilder;
	THandleType FHandleType;
	void __fastcall ErrorReadOnly();
	void __fastcall Cleanup(bool AClearBuilder);
	void __fastcall AttachToImpl(const Firedac::Phys::Mongodbcli::Pbson_t AValue);
	void __fastcall CheckClosed();
	Firedac::Phys::Mongodbcli::Pbson_t __fastcall GetAsReadHandle();
	void __fastcall SetAsReadHandle(const Firedac::Phys::Mongodbcli::Pbson_t AValue);
	Firedac::Phys::Mongodbcli::Pbson_t __fastcall GetAsWriteHandle();
	System::UnicodeString __fastcall GetAsJSON();
	void __fastcall SetAsJSON(const System::UnicodeString AValue);
	bool __fastcall GetInObject();
	System::Json::Builders::TJSONCollectionBuilder::TPairs* __fastcall GetPairs();
	bool __fastcall GetInArray();
	System::Json::Builders::TJSONCollectionBuilder::TElements* __fastcall GetElements();
	System::Json::Builders::TJSONObjectBuilder* __fastcall GetBuilder();
	
protected:
	virtual void __fastcall InternalFreeHandle();
	__fastcall TMongoDocument(TMongoEnv* AEnv, System::TObject* AOwningObj, System::TObject* AParentObj)/* overload */;
	__property System::Json::Builders::TJSONCollectionBuilder::TPairs* Pairs = {read=GetPairs};
	__property System::Json::Builders::TJSONCollectionBuilder::TElements* Elements = {read=GetElements};
	
public:
	__fastcall TMongoDocument(TMongoEnv* AEnv)/* overload */;
	__fastcall virtual ~TMongoDocument();
	void __fastcall Assign(TMongoDocument* ASource);
	TMongoDocument* __fastcall Clear();
	void __fastcall Close();
	TMongoDocument* __fastcall Add(const System::UnicodeString AKey, const System::UnicodeString AValue)/* overload */;
	TMongoDocument* __fastcall Add(const System::UnicodeString AKey, const int AValue)/* overload */;
	TMongoDocument* __fastcall Add(const System::UnicodeString AKey, const __int64 AValue)/* overload */;
	TMongoDocument* __fastcall Add(const System::UnicodeString AKey, const System::Extended AValue)/* overload */;
	TMongoDocument* __fastcall Add(const System::UnicodeString AKey, const bool AValue)/* overload */;
	TMongoDocument* __fastcall Add(const System::UnicodeString AKey, const System::TDateTime AValue)/* overload */;
#ifndef _WIN64
	TMongoDocument* __fastcall Add(const System::UnicodeString AKey, const System::DynamicArray<System::Byte> AValue, System::Json::Types::TJsonBinaryType ABinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
#else /* _WIN64 */
	TMongoDocument* __fastcall Add(const System::UnicodeString AKey, const System::TArray__1<System::Byte> AValue, System::Json::Types::TJsonBinaryType ABinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
#endif /* _WIN64 */
	TMongoDocument* __fastcall Add(const System::UnicodeString AKey, TMongoOID* const AValue)/* overload */;
	TMongoDocument* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonOid &AValue)/* overload */;
	TMongoDocument* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonRegEx &AValue)/* overload */;
	TMongoDocument* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonDBRef &AValue)/* overload */;
	TMongoDocument* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonCodeWScope &AValue)/* overload */;
	TMongoDocument* __fastcall Add(const System::UnicodeString AKey, const System::TVarRec &AValue)/* overload */;
	TMongoDocument* __fastcall Add(const System::UnicodeString AKey, const System::TVarRec *AValues, const int AValues_High)/* overload */;
	TMongoDocument* __fastcall Add(const System::UnicodeString AKey, const System::Variant &AValue)/* overload */;
	TMongoDocument* __fastcall AddNull(const System::UnicodeString AKey);
	TMongoDocument* __fastcall AddUndefined(const System::UnicodeString AKey);
	TMongoDocument* __fastcall AddMinKey(const System::UnicodeString AKey);
	TMongoDocument* __fastcall AddMaxKey(const System::UnicodeString AKey);
	TMongoDocument* __fastcall BeginArray(const System::UnicodeString AKey);
	TMongoDocument* __fastcall EndArray();
	TMongoDocument* __fastcall BeginObject(const System::UnicodeString AKey);
	TMongoDocument* __fastcall EndObject();
	TMongoDocument* __fastcall Append(TMongoDocument* const ADoc)/* overload */;
	TMongoDocument* __fastcall Append(const System::UnicodeString AJSON)/* overload */;
	TMongoDocument* __fastcall Append(const System::TVarRec *AItems, const int AItems_High)/* overload */;
	__property bool InArray = {read=GetInArray, nodefault};
	__property bool InObject = {read=GetInObject, nodefault};
	__property System::Json::Builders::TJSONObjectBuilder* Builder = {read=GetBuilder};
	System::Json::Builders::TJSONIterator* __fastcall Iterator();
	void __fastcall Iterate(System::Json::Builders::TJSONIterator::_di_TIterateFunc AFunc);
	__property System::UnicodeString AsJSON = {read=GetAsJSON, write=SetAsJSON};
	__property Firedac::Phys::Mongodbcli::Pbson_t AsReadHandle = {read=GetAsReadHandle, write=SetAsReadHandle};
	__property Firedac::Phys::Mongodbcli::Pbson_t AsWriteHandle = {read=GetAsWriteHandle};
protected:
	/* TMongoObject.Create */ inline __fastcall TMongoDocument(TMongoEnv* AEnv, System::TObject* AOwningObj)/* overload */ : TMongoObject(AEnv, AOwningObj) { }
	/* TMongoObject.Create */ inline __fastcall TMongoDocument(TMongoEnv* AEnv, System::TObject* AOwningObj, void * AHandle)/* overload */ : TMongoObject(AEnv, AOwningObj, AHandle) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoReadPreference : public TMongoObject
{
	typedef TMongoObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TReadMode : unsigned int { Primary, Secondary, PrimaryPreferred, SecondaryPreferred, Nearest };
	
	
private:
	TMongoDocument* FTags;
	TReadMode __fastcall GetMode();
	void __fastcall SetMode(const TReadMode AValue);
	TMongoDocument* __fastcall GetTags();
	void __fastcall SetTags(TMongoDocument* const AValue);
	
protected:
	virtual void __fastcall InternalFreeHandle();
	
public:
	__fastcall TMongoReadPreference(TMongoEnv* AEnv, System::TObject* AOwningObj, void * AHandle);
	__fastcall virtual ~TMongoReadPreference();
	void __fastcall Assign(TMongoReadPreference* ASource);
	void __fastcall AddTag(TMongoDocument* ATag);
	__property TReadMode Mode = {read=GetMode, write=SetMode, default=0};
	__property TMongoDocument* Tags = {read=GetTags, write=SetTags};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoWriteConcern : public TMongoObject
{
	typedef TMongoObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TWriteLevel : unsigned int { Default, ErrorsIgnored, Unacknowledged, Majority };
	
	
private:
	bool __fastcall GetFsync();
	void __fastcall SetFsync(const bool AValue);
	bool __fastcall GetJournal();
	void __fastcall SetJournal(const bool AValue);
	TWriteLevel __fastcall GetLevel();
	void __fastcall SetLevel(const TWriteLevel AValue);
	int __fastcall GetMajority();
	void __fastcall SetMajority(const int AValue);
	System::UnicodeString __fastcall GetTag();
	void __fastcall SetTag(const System::UnicodeString AValue);
	int __fastcall GetTimeout();
	void __fastcall SetTimeout(const int AValue);
	
protected:
	virtual void __fastcall InternalFreeHandle();
	
public:
	__fastcall TMongoWriteConcern(TMongoEnv* AEnv, System::TObject* AOwningObj, void * AHandle);
	void __fastcall Assign(TMongoWriteConcern* ASource);
	__property TWriteLevel Level = {read=GetLevel, write=SetLevel, default=0};
	__property bool Fsync = {read=GetFsync, write=SetFsync, nodefault};
	__property bool Journal = {read=GetJournal, write=SetJournal, nodefault};
	__property int Majority = {read=GetMajority, write=SetMajority, nodefault};
	__property System::UnicodeString Tag = {read=GetTag, write=SetTag};
	__property int Timeout = {read=GetTimeout, write=SetTimeout, nodefault};
public:
	/* TMongoObject.Destroy */ inline __fastcall virtual ~TMongoWriteConcern() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TMongoExpression__1 : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TMongoDocument* FDoc;
	System::UnicodeString __fastcall GetAsJSON();
	bool __fastcall GetInArray();
	bool __fastcall GetInObject();
	void __fastcall SetAsJSON(const System::UnicodeString AValue);
	
protected:
	__fastcall TMongoExpression__1(TMongoEnv* AEnv, System::TObject* AOwningObj, T AParentObj)/* overload */;
	
public:
	__fastcall TMongoExpression__1(TMongoEnv* AEnv)/* overload */;
	__fastcall virtual ~TMongoExpression__1();
	void __fastcall Assign(TMongoExpression__1<T>* ASource);
	TMongoExpression__1<T>* __fastcall Clear();
	void __fastcall Close();
	TMongoExpression__1<T>* __fastcall Add(const System::UnicodeString AKey, const System::UnicodeString AValue)/* overload */;
	TMongoExpression__1<T>* __fastcall Add(const System::UnicodeString AKey, const int AValue)/* overload */;
	TMongoExpression__1<T>* __fastcall Add(const System::UnicodeString AKey, const __int64 AValue)/* overload */;
	TMongoExpression__1<T>* __fastcall Add(const System::UnicodeString AKey, const System::Extended AValue)/* overload */;
	TMongoExpression__1<T>* __fastcall Add(const System::UnicodeString AKey, const bool AValue)/* overload */;
	TMongoExpression__1<T>* __fastcall Add(const System::UnicodeString AKey, const System::TDateTime AValue)/* overload */;
#ifndef _WIN64
	TMongoExpression__1<T>* __fastcall Add(const System::UnicodeString AKey, const System::DynamicArray<System::Byte> AValue, System::Json::Types::TJsonBinaryType ABinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
#else /* _WIN64 */
	TMongoExpression__1<T>* __fastcall Add(const System::UnicodeString AKey, const System::TArray__1<System::Byte> AValue, System::Json::Types::TJsonBinaryType ABinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
#endif /* _WIN64 */
	TMongoExpression__1<T>* __fastcall Add(const System::UnicodeString AKey, TMongoOID* const AValue)/* overload */;
	TMongoExpression__1<T>* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonOid &AValue)/* overload */;
	TMongoExpression__1<T>* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonRegEx &AValue)/* overload */;
	TMongoExpression__1<T>* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonDBRef &AValue)/* overload */;
	TMongoExpression__1<T>* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonCodeWScope &AValue)/* overload */;
	TMongoExpression__1<T>* __fastcall Add(const System::UnicodeString AKey, const System::TVarRec &AValue)/* overload */;
	TMongoExpression__1<T>* __fastcall Add(const System::UnicodeString AKey, const System::TVarRec *AValues, const int AValues_High)/* overload */;
	TMongoExpression__1<T>* __fastcall Add(const System::UnicodeString AKey, const System::Variant &AValue)/* overload */;
	TMongoExpression__1<T>* __fastcall AddNull(const System::UnicodeString AKey)/* overload */;
	TMongoExpression__1<T>* __fastcall AddUndefined(const System::UnicodeString AKey)/* overload */;
	TMongoExpression__1<T>* __fastcall AddMinKey(const System::UnicodeString AKey)/* overload */;
	TMongoExpression__1<T>* __fastcall AddMaxKey(const System::UnicodeString AKey)/* overload */;
	TMongoExpression__1<T>* __fastcall BeginArray(const System::UnicodeString AKey);
	TMongoExpression__1<T>* __fastcall EndArray();
	TMongoExpression__1<T>* __fastcall BeginObject(const System::UnicodeString AKey);
	TMongoExpression__1<T>* __fastcall EndObject();
	TMongoExpression__1<T>* __fastcall Append(TMongoDocument* const ADoc)/* overload */;
	TMongoExpression__1<T>* __fastcall Append(const System::UnicodeString AJSON)/* overload */;
	TMongoExpression__1<T>* __fastcall Append(const System::TVarRec *AItems, const int AItems_High)/* overload */;
	TMongoExpression__1<T>* __fastcall Exp(const System::UnicodeString AField, const System::UnicodeString AExpression);
	T __fastcall End();
	__property bool InArray = {read=GetInArray, nodefault};
	__property bool InObject = {read=GetInObject, nodefault};
	__property TMongoDocument* Doc = {read=FDoc};
	System::Json::Builders::TJSONObjectBuilder* __fastcall Builder();
	System::Json::Builders::TJSONIterator* __fastcall Iterator();
	__property System::UnicodeString AsJSON = {read=GetAsJSON, write=SetAsJSON};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{7D8AF712-3FA8-459B-BF9B-4EC7E55B7359}") IMongoCursor  : public System::IInterface 
{
	virtual TMongoDocument* __fastcall GetDoc() = 0 ;
	virtual bool __fastcall GetIsAlive() = 0 ;
	virtual bool __fastcall Next() = 0 /* overload */;
	virtual bool __fastcall Next(TMongoDocument* ADoc) = 0 /* overload */;
	__property TMongoDocument* Doc = {read=GetDoc};
	__property bool IsAlive = {read=GetIsAlive};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoPipeline : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
protected:
	__interface DELPHIINTERFACE TGetCursor;
	typedef System::DelphiInterface<TGetCursor> _di_TGetCursor;
	__interface TGetCursor  : public System::IInterface 
	{
		virtual _di_IMongoCursor __fastcall Invoke(TMongoPipeline* APipeline) = 0 ;
	};
	
	class DELPHICLASS TOperation;
	class PASCALIMPLEMENTATION TOperation : public System::TObject
	{
		typedef System::TObject inherited;
		
	protected:
		TMongoPipeline* FPipeline;
		TMongoDocument* FWriter;
		__fastcall TOperation(TMongoPipeline* APipeline);
		virtual __classmethod System::UnicodeString __fastcall GetOperator() = 0 ;
		__classmethod virtual bool __fastcall GetInline();
		
	public:
		__fastcall virtual ~TOperation();
		TMongoPipeline* __fastcall End();
		__property TMongoDocument* Writer = {read=FWriter};
	};
	
	
#ifndef _WIN64
	typedef System::TMetaClass* TOperationClass;
#else /* _WIN64 */
	_DECLARE_METACLASS(System::TMetaClass, TOperationClass);
#endif /* _WIN64 */
	
	class DELPHICLASS TInlineOperation;
	class PASCALIMPLEMENTATION TInlineOperation : public TMongoPipeline::TOperation
	{
		typedef TMongoPipeline::TOperation inherited;
		
	protected:
		__classmethod virtual bool __fastcall GetInline();
		void __fastcall SetValue(const System::Variant &AValue);
	protected:
		/* TOperation.Create */ inline __fastcall TInlineOperation(TMongoPipeline* APipeline) : TMongoPipeline::TOperation(APipeline) { }
		
	public:
		/* TOperation.Destroy */ inline __fastcall virtual ~TInlineOperation() { }
		
	};
	
	
	class DELPHICLASS TLimit;
	class PASCALIMPLEMENTATION TLimit : /*[[sealed]]*/ public TMongoPipeline::TInlineOperation
	{
		typedef TMongoPipeline::TInlineOperation inherited;
		
	protected:
		__classmethod virtual System::UnicodeString __fastcall GetOperator();
	protected:
		/* TOperation.Create */ inline __fastcall TLimit(TMongoPipeline* APipeline) : TMongoPipeline::TInlineOperation(APipeline) { }
		
	public:
		/* TOperation.Destroy */ inline __fastcall virtual ~TLimit() { }
		
	};
	
	
	class DELPHICLASS TSkip;
	class PASCALIMPLEMENTATION TSkip : /*[[sealed]]*/ public TMongoPipeline::TInlineOperation
	{
		typedef TMongoPipeline::TInlineOperation inherited;
		
	protected:
		__classmethod virtual System::UnicodeString __fastcall GetOperator();
	protected:
		/* TOperation.Create */ inline __fastcall TSkip(TMongoPipeline* APipeline) : TMongoPipeline::TInlineOperation(APipeline) { }
		
	public:
		/* TOperation.Destroy */ inline __fastcall virtual ~TSkip() { }
		
	};
	
	
	class DELPHICLASS TUnwind;
	class PASCALIMPLEMENTATION TUnwind : /*[[sealed]]*/ public TMongoPipeline::TInlineOperation
	{
		typedef TMongoPipeline::TInlineOperation inherited;
		
	protected:
		__classmethod virtual System::UnicodeString __fastcall GetOperator();
	protected:
		/* TOperation.Create */ inline __fastcall TUnwind(TMongoPipeline* APipeline) : TMongoPipeline::TInlineOperation(APipeline) { }
		
	public:
		/* TOperation.Destroy */ inline __fastcall virtual ~TUnwind() { }
		
	};
	
	
	class DELPHICLASS TSample;
	class PASCALIMPLEMENTATION TSample : /*[[sealed]]*/ public TMongoPipeline::TOperation
	{
		typedef TMongoPipeline::TOperation inherited;
		
	protected:
		__classmethod virtual System::UnicodeString __fastcall GetOperator();
		void __fastcall SetValue(const int AValue);
	protected:
		/* TOperation.Create */ inline __fastcall TSample(TMongoPipeline* APipeline) : TMongoPipeline::TOperation(APipeline) { }
		
	public:
		/* TOperation.Destroy */ inline __fastcall virtual ~TSample() { }
		
	};
	
	
	class DELPHICLASS TLookup;
	class PASCALIMPLEMENTATION TLookup : /*[[sealed]]*/ public TMongoPipeline::TOperation
	{
		typedef TMongoPipeline::TOperation inherited;
		
	protected:
		__classmethod virtual System::UnicodeString __fastcall GetOperator();
		void __fastcall Setup(const System::UnicodeString AFrom, const System::UnicodeString ALocalField, const System::UnicodeString AForeignField, const System::UnicodeString AAs);
	protected:
		/* TOperation.Create */ inline __fastcall TLookup(TMongoPipeline* APipeline) : TMongoPipeline::TOperation(APipeline) { }
		
	public:
		/* TOperation.Destroy */ inline __fastcall virtual ~TLookup() { }
		
	};
	
	
	class DELPHICLASS TOut;
	class PASCALIMPLEMENTATION TOut : /*[[sealed]]*/ public TMongoPipeline::TInlineOperation
	{
		typedef TMongoPipeline::TInlineOperation inherited;
		
	protected:
		__classmethod virtual System::UnicodeString __fastcall GetOperator();
	protected:
		/* TOperation.Create */ inline __fastcall TOut(TMongoPipeline* APipeline) : TMongoPipeline::TInlineOperation(APipeline) { }
		
	public:
		/* TOperation.Destroy */ inline __fastcall virtual ~TOut() { }
		
	};
	
	
	class DELPHICLASS TIndexStats;
	class PASCALIMPLEMENTATION TIndexStats : /*[[sealed]]*/ public TMongoPipeline::TOperation
	{
		typedef TMongoPipeline::TOperation inherited;
		
	protected:
		__classmethod virtual System::UnicodeString __fastcall GetOperator();
		void __fastcall Setup();
	protected:
		/* TOperation.Create */ inline __fastcall TIndexStats(TMongoPipeline* APipeline) : TMongoPipeline::TOperation(APipeline) { }
		
	public:
		/* TOperation.Destroy */ inline __fastcall virtual ~TIndexStats() { }
		
	};
	
	
	
public:
	class DELPHICLASS TExpression;
	class PASCALIMPLEMENTATION TExpression : /*[[sealed]]*/ public TMongoExpression__1<TMongoPipeline*>
	{
		typedef TMongoExpression__1<TMongoPipeline*> inherited;
		
	protected:
		/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoPipeline>.Create */ inline __fastcall TExpression(TMongoEnv* AEnv, System::TObject* AOwningObj, TMongoPipeline* AParentObj)/* overload */ : TMongoExpression__1<TMongoPipeline*>(AEnv, AOwningObj, AParentObj) { }
		
	public:
		/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoPipeline>.Create */ inline __fastcall TExpression(TMongoEnv* AEnv)/* overload */ : TMongoExpression__1<TMongoPipeline*>(AEnv) { }
		/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoPipeline>.Destroy */ inline __fastcall virtual ~TExpression() { }
		
	};
	
	
	class DELPHICLASS TProjection;
	class PASCALIMPLEMENTATION TProjection : /*[[sealed]]*/ public TMongoPipeline::TOperation
	{
		typedef TMongoPipeline::TOperation inherited;
		
	protected:
		__classmethod virtual System::UnicodeString __fastcall GetOperator();
		
	public:
		TMongoPipeline::TProjection* __fastcall Clear();
		TMongoPipeline::TProjection* __fastcall Append(const System::UnicodeString AJSON);
		TMongoPipeline::TProjection* __fastcall NoID();
		TMongoPipeline::TProjection* __fastcall Field(const System::UnicodeString AField);
		TMongoPipeline::TProjection* __fastcall FieldBegin(const System::UnicodeString AField);
		TMongoPipeline::TProjection* __fastcall FieldEnd();
		TMongoPipeline::TProjection* __fastcall Exp(const System::UnicodeString AField, const System::UnicodeString AExpression);
	protected:
		/* TOperation.Create */ inline __fastcall TProjection(TMongoPipeline* APipeline) : TMongoPipeline::TOperation(APipeline) { }
		
	public:
		/* TOperation.Destroy */ inline __fastcall virtual ~TProjection() { }
		
	};
	
	
	class DELPHICLASS TSort;
	class PASCALIMPLEMENTATION TSort : /*[[sealed]]*/ public TMongoPipeline::TOperation
	{
		typedef TMongoPipeline::TOperation inherited;
		
	protected:
		__classmethod virtual System::UnicodeString __fastcall GetOperator();
		
	public:
		TMongoPipeline::TSort* __fastcall Clear();
		TMongoPipeline::TSort* __fastcall Append(const System::UnicodeString AJSON);
		TMongoPipeline::TSort* __fastcall Field(const System::UnicodeString AName, bool AAscending = true);
		TMongoPipeline::TSort* __fastcall TextScore(const System::UnicodeString AName);
	protected:
		/* TOperation.Create */ inline __fastcall TSort(TMongoPipeline* APipeline) : TMongoPipeline::TOperation(APipeline) { }
		
	public:
		/* TOperation.Destroy */ inline __fastcall virtual ~TSort() { }
		
	};
	
	
	class DELPHICLASS TGeoNear;
	class PASCALIMPLEMENTATION TGeoNear : /*[[sealed]]*/ public TMongoPipeline::TOperation
	{
		typedef TMongoPipeline::TOperation inherited;
		
		
	public:
		class DELPHICLASS TQuery;
		class PASCALIMPLEMENTATION TQuery : /*[[sealed]]*/ public TMongoExpression__1<TMongoPipeline::TGeoNear*>
		{
			typedef TMongoExpression__1<TMongoPipeline::TGeoNear*> inherited;
			
		public:
			HIDESBASE TMongoPipeline::TGeoNear* __fastcall End();
		protected:
			/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoPipeline_TGeoNear>.Create */ inline __fastcall TQuery(TMongoEnv* AEnv, System::TObject* AOwningObj, TMongoPipeline::TGeoNear* AParentObj)/* overload */ : TMongoExpression__1<TMongoPipeline::TGeoNear*>(AEnv, AOwningObj, AParentObj) { }
			
		public:
			/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoPipeline_TGeoNear>.Create */ inline __fastcall TQuery(TMongoEnv* AEnv)/* overload */ : TMongoExpression__1<TMongoPipeline::TGeoNear*>(AEnv) { }
			/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoPipeline_TGeoNear>.Destroy */ inline __fastcall virtual ~TQuery() { }
			
		};
		
		
		
	private:
		TQuery* FQuery;
		
	protected:
		__classmethod virtual System::UnicodeString __fastcall GetOperator();
		
	public:
		__fastcall virtual ~TGeoNear();
		TMongoPipeline::TGeoNear* __fastcall Clear();
		TMongoPipeline::TGeoNear* __fastcall Append(const System::UnicodeString AJSON);
		TMongoPipeline::TGeoNear* __fastcall Near(System::Extended ALatitude, System::Extended ALongitude);
		TMongoPipeline::TGeoNear* __fastcall Spherical(bool AValue);
		TMongoPipeline::TGeoNear* __fastcall Limit(int AValue);
		TMongoPipeline::TGeoNear* __fastcall Distance(int AMin, int AMax);
		TMongoPipeline::TGeoNear* __fastcall Output(const System::UnicodeString ADistField, const System::UnicodeString ALocsField = System::UnicodeString());
		TQuery* __fastcall Query(const System::UnicodeString AJSON = System::UnicodeString());
	protected:
		/* TOperation.Create */ inline __fastcall TGeoNear(TMongoPipeline* APipeline) : TMongoPipeline::TOperation(APipeline) { }
		
	};
	
	
	class DELPHICLASS TOptions;
	class PASCALIMPLEMENTATION TOptions : /*[[sealed]]*/ public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		bool FExplain;
		int FBatchSize;
		bool FUseCursor;
		bool FAllowDiskUse;
		int FMaxTimeMS;
		void __fastcall Save(TMongoDocument* AWriter);
		
	public:
		void __fastcall Assign(TMongoPipeline::TOptions* AOptions);
		__property bool Explain = {read=FExplain, write=FExplain, default=0};
		__property bool AllowDiskUse = {read=FAllowDiskUse, write=FAllowDiskUse, default=0};
		__property bool UseCursor = {read=FUseCursor, write=FUseCursor, default=0};
		__property int BatchSize = {read=FBatchSize, write=FBatchSize, default=0};
		__property int MaxTimeMS = {read=FMaxTimeMS, write=FMaxTimeMS, default=0};
	public:
		/* TObject.Create */ inline __fastcall TOptions() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TOptions() { }
		
	};
	
	
	
private:
	TMongoEnv* FEnv;
	System::TObject* FOwningObj;
	_di_TGetCursor FGetCursor;
	System::Classes::TStringList* FOperations;
	TOptions* FOptions;
	TMongoDocument* FPWriter;
	TMongoDocument* FOWriter;
	_di_IMongoCursor __fastcall GetCursor();
	System::TObject* __fastcall GetOperation(TOperationClass AType, const System::UnicodeString ATypeName, const System::UnicodeString AJSON);
	TOptions* __fastcall GetOptions();
	TMongoDocument* __fastcall GetFinalPipelineBSON();
	TMongoDocument* __fastcall GetFinalOptionsBSON();
	
protected:
	__fastcall TMongoPipeline(TMongoEnv* AEnv, System::TObject* AOwningObj, _di_TGetCursor AGetCursor)/* overload */;
	__property _di_IMongoCursor Cursor = {read=GetCursor};
	
public:
	__fastcall TMongoPipeline(TMongoEnv* AEnv)/* overload */;
	__fastcall virtual ~TMongoPipeline();
	TProjection* __fastcall Project(const System::UnicodeString AJSON = System::UnicodeString());
	TExpression* __fastcall Match(const System::UnicodeString AJSON = System::UnicodeString());
	TExpression* __fastcall Redact(const System::UnicodeString AJSON = System::UnicodeString());
	TMongoPipeline* __fastcall Limit(const int AValue);
	TMongoPipeline* __fastcall Skip(const int AValue);
	TMongoPipeline* __fastcall Unwind(const System::UnicodeString APath);
	TExpression* __fastcall Group(const System::UnicodeString AJSON = System::UnicodeString());
	TMongoPipeline* __fastcall Sample(const int AValue);
	TSort* __fastcall Sort(const System::UnicodeString AJSON = System::UnicodeString());
	TGeoNear* __fastcall GeoNear(const System::UnicodeString AJSON = System::UnicodeString());
	TMongoPipeline* __fastcall Lookup(const System::UnicodeString AFrom, const System::UnicodeString ALocalField, const System::UnicodeString AForeignField, const System::UnicodeString AAs);
	TMongoPipeline* __fastcall Out(const System::UnicodeString ACollectionName);
	TMongoPipeline* __fastcall IndexStats();
	TExpression* __fastcall Stage(const System::UnicodeString AName, const System::UnicodeString AJSON = System::UnicodeString());
	_di_IMongoCursor __fastcall Open();
	__property TOptions* Options = {read=GetOptions};
	__property TMongoDocument* FinalPipelineBSON = {read=GetFinalPipelineBSON};
	__property TMongoDocument* FinalOptionsBSON = {read=GetFinalOptionsBSON};
private:
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7D8AF712-3FA8-459B-BF9B-4EC7E55B7359}
	operator _di_IMongoCursor() { return Cursor; }
	#else
	operator IMongoCursor*(void) { return (IMongoCursor*)Cursor; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoQuery : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
protected:
	__interface DELPHIINTERFACE TGetCursor;
	typedef System::DelphiInterface<TGetCursor> _di_TGetCursor;
	__interface TGetCursor  : public System::IInterface 
	{
		virtual _di_IMongoCursor __fastcall Invoke(TMongoQuery* AQuery) = 0 ;
	};
	
	__interface DELPHIINTERFACE TGetCount;
	typedef System::DelphiInterface<TGetCount> _di_TGetCount;
	__interface TGetCount  : public System::IInterface 
	{
		virtual __int64 __fastcall Invoke(TMongoQuery* AQuery) = 0 ;
	};
	
	class DELPHICLASS TOperation;
	class PASCALIMPLEMENTATION TOperation : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		TMongoQuery* FQuery;
		TMongoDocument* FWriter;
		
	protected:
		__fastcall TOperation(TMongoQuery* AQuery);
		
	public:
		__fastcall virtual ~TOperation();
		TMongoQuery* __fastcall End();
		__property TMongoDocument* Writer = {read=FWriter};
	};
	
	
	
public:
	class DELPHICLASS TExpression;
	class PASCALIMPLEMENTATION TExpression : /*[[sealed]]*/ public TMongoExpression__1<TMongoQuery*>
	{
		typedef TMongoExpression__1<TMongoQuery*> inherited;
		
	protected:
		/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoQuery>.Create */ inline __fastcall TExpression(TMongoEnv* AEnv, System::TObject* AOwningObj, TMongoQuery* AParentObj)/* overload */ : TMongoExpression__1<TMongoQuery*>(AEnv, AOwningObj, AParentObj) { }
		
	public:
		/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoQuery>.Create */ inline __fastcall TExpression(TMongoEnv* AEnv)/* overload */ : TMongoExpression__1<TMongoQuery*>(AEnv) { }
		/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoQuery>.Destroy */ inline __fastcall virtual ~TExpression() { }
		
	};
	
	
	class DELPHICLASS TProjection;
	class PASCALIMPLEMENTATION TProjection : /*[[sealed]]*/ public TMongoQuery::TOperation
	{
		typedef TMongoQuery::TOperation inherited;
		
	public:
		TMongoQuery::TProjection* __fastcall Clear();
		TMongoQuery::TProjection* __fastcall Append(const System::UnicodeString AJSON);
		TMongoQuery::TProjection* __fastcall NoID();
		TMongoQuery::TProjection* __fastcall Field(const System::UnicodeString AField, bool AInclude = true);
		TMongoQuery::TProjection* __fastcall Include(const System::UnicodeString *AFields, const int AFields_High);
		TMongoQuery::TProjection* __fastcall Exclude(const System::UnicodeString *AFields, const int AFields_High);
		TMongoQuery::TProjection* __fastcall TextScore(const System::UnicodeString AField);
		TMongoQuery::TProjection* __fastcall Slice(const System::UnicodeString AField, int ACount)/* overload */;
		TMongoQuery::TProjection* __fastcall Slice(const System::UnicodeString AField, int ASkip, int ACount)/* overload */;
	protected:
		/* TOperation.Create */ inline __fastcall TProjection(TMongoQuery* AQuery) : TMongoQuery::TOperation(AQuery) { }
		
	public:
		/* TOperation.Destroy */ inline __fastcall virtual ~TProjection() { }
		
	};
	
	
	class DELPHICLASS TSort;
	class PASCALIMPLEMENTATION TSort : /*[[sealed]]*/ public TMongoQuery::TOperation
	{
		typedef TMongoQuery::TOperation inherited;
		
	public:
		TMongoQuery::TSort* __fastcall Clear();
		TMongoQuery::TSort* __fastcall Append(const System::UnicodeString AJSON);
		TMongoQuery::TSort* __fastcall Field(const System::UnicodeString AName, bool AAscending = true);
		TMongoQuery::TSort* __fastcall Ascending(const System::UnicodeString *AFields, const int AFields_High);
		TMongoQuery::TSort* __fastcall Descending(const System::UnicodeString *AFields, const int AFields_High);
		TMongoQuery::TSort* __fastcall TextScore(const System::UnicodeString AName);
	protected:
		/* TOperation.Create */ inline __fastcall TSort(TMongoQuery* AQuery) : TMongoQuery::TOperation(AQuery) { }
		
	public:
		/* TOperation.Destroy */ inline __fastcall virtual ~TSort() { }
		
	};
	
	
	class DELPHICLASS TOptions;
	class PASCALIMPLEMENTATION TOptions : /*[[sealed]]*/ public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		System::UnicodeString FComment;
		bool FExplain;
		System::UnicodeString FHint;
		int FMaxScan;
		int FMaxTimeMS;
		bool FReturnKey;
		bool FSnapshot;
		int FBatchSize;
		void __fastcall Save(TMongoDocument* AWriter);
		
	public:
		void __fastcall Assign(TMongoQuery::TOptions* AOptions);
		__property System::UnicodeString Comment = {read=FComment, write=FComment};
		__property bool Explain = {read=FExplain, write=FExplain, default=0};
		__property System::UnicodeString Hint = {read=FHint, write=FHint};
		__property int MaxScan = {read=FMaxScan, write=FMaxScan, default=0};
		__property int MaxTimeMS = {read=FMaxTimeMS, write=FMaxTimeMS, default=0};
		__property bool ReturnKey = {read=FReturnKey, write=FReturnKey, default=0};
		__property bool Snapshot = {read=FSnapshot, write=FSnapshot, default=0};
		__property int BatchSize = {read=FBatchSize, write=FBatchSize, default=0};
	public:
		/* TObject.Create */ inline __fastcall TOptions() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TOptions() { }
		
	};
	
	
	
private:
	TMongoEnv* FEnv;
	System::TObject* FOwningObj;
	_di_TGetCursor FGetCursor;
	_di_TGetCount FGetCount;
	TProjection* FProject;
	TExpression* FMatch;
	TSort* FSort;
	TOptions* FOptions;
	int FLimit;
	int FSkip;
	TMongoDocument* FQWriter;
	TMongoDocument* FPWriter;
	_di_IMongoCursor __fastcall GetCursor();
	TMongoDocument* __fastcall GetFinalQueryBSON();
	TMongoDocument* __fastcall GetFinalCountBSON();
	TMongoDocument* __fastcall GetFinalProjectBSON();
	
protected:
	__fastcall TMongoQuery(TMongoEnv* AEnv, System::TObject* AOwningObj, _di_TGetCursor AGetCursor)/* overload */;
	__fastcall TMongoQuery(TMongoEnv* AEnv, System::TObject* AOwningObj, _di_TGetCount AGetCount)/* overload */;
	virtual void __fastcall DoGetFinalQueryBSON(TMongoDocument* AWriter);
	virtual void __fastcall DoGetFinalProjectBSON(TMongoDocument* AWriter);
	__property _di_IMongoCursor Cursor = {read=GetCursor};
	
public:
	__fastcall TMongoQuery(TMongoEnv* AEnv)/* overload */;
	__fastcall virtual ~TMongoQuery();
	TProjection* __fastcall Project(const System::UnicodeString AJSON = System::UnicodeString());
	TExpression* __fastcall Match(const System::UnicodeString AJSON = System::UnicodeString());
	TSort* __fastcall Sort(const System::UnicodeString AJSON = System::UnicodeString());
	TOptions* __fastcall Options();
	TMongoQuery* __fastcall Limit(const int AValue);
	TMongoQuery* __fastcall Skip(const int AValue);
	_di_IMongoCursor __fastcall Open();
	__int64 __fastcall Value();
	__property TMongoDocument* FinalQueryBSON = {read=GetFinalQueryBSON};
	__property TMongoDocument* FinalCountBSON = {read=GetFinalCountBSON};
	__property TMongoDocument* FinalProjectBSON = {read=GetFinalProjectBSON};
private:
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7D8AF712-3FA8-459B-BF9B-4EC7E55B7359}
	operator _di_IMongoCursor() { return Cursor; }
	#else
	operator IMongoCursor*(void) { return (IMongoCursor*)Cursor; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoCommand : public TMongoQuery
{
	typedef TMongoQuery inherited;
	
private:
	TMongoDocument* FCommand;
	
protected:
	__fastcall TMongoCommand(TMongoEnv* AEnv, System::TObject* AOwningObj)/* overload */;
	virtual void __fastcall DoGetFinalQueryBSON(TMongoDocument* AWriter);
	
public:
	__fastcall TMongoCommand(TMongoEnv* AEnv)/* overload */;
	__fastcall virtual ~TMongoCommand();
	TMongoCommand* __fastcall Command(const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	TMongoCommand* __fastcall Command(const System::UnicodeString AJSON)/* overload */;
protected:
	/* TMongoQuery.Create */ inline __fastcall TMongoCommand(TMongoEnv* AEnv, System::TObject* AOwningObj, TMongoQuery::_di_TGetCursor AGetCursor)/* overload */ : TMongoQuery(AEnv, AOwningObj, AGetCursor) { }
	/* TMongoQuery.Create */ inline __fastcall TMongoCommand(TMongoEnv* AEnv, System::TObject* AOwningObj, TMongoQuery::_di_TGetCount AGetCount)/* overload */ : TMongoQuery(AEnv, AOwningObj, AGetCount) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoUpdate : public System::TObject
{
	typedef System::TObject inherited;
	
	
protected:
	__interface DELPHIINTERFACE TRunUpdate;
	typedef System::DelphiInterface<TRunUpdate> _di_TRunUpdate;
	__interface TRunUpdate  : public System::IInterface 
	{
		virtual void __fastcall Invoke(TMongoUpdate* AUpdate) = 0 ;
	};
	
	
public:
	class DELPHICLASS TExpression;
	class PASCALIMPLEMENTATION TExpression : /*[[sealed]]*/ public TMongoExpression__1<TMongoUpdate*>
	{
		typedef TMongoExpression__1<TMongoUpdate*> inherited;
		
	protected:
		/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoUpdate>.Create */ inline __fastcall TExpression(TMongoEnv* AEnv, System::TObject* AOwningObj, TMongoUpdate* AParentObj)/* overload */ : TMongoExpression__1<TMongoUpdate*>(AEnv, AOwningObj, AParentObj) { }
		
	public:
		/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoUpdate>.Create */ inline __fastcall TExpression(TMongoEnv* AEnv)/* overload */ : TMongoExpression__1<TMongoUpdate*>(AEnv) { }
		/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoUpdate>.Destroy */ inline __fastcall virtual ~TExpression() { }
		
	};
	
	
	class DELPHICLASS TModifier;
	class PASCALIMPLEMENTATION TModifier : public System::TObject
	{
		typedef System::TObject inherited;
		
		
	protected:
		class DELPHICLASS TOperation;
		class PASCALIMPLEMENTATION TOperation : public System::TObject
		{
			typedef System::TObject inherited;
			
		private:
			TMongoUpdate::TModifier* FModifier;
			TMongoDocument* FWriter;
			
		protected:
			__fastcall TOperation(TMongoUpdate::TModifier* AModifier);
			TMongoUpdate::TModifier::TOperation* __fastcall Field(const System::UnicodeString AName, const System::Variant &AValue);
			virtual __classmethod System::UnicodeString __fastcall GetOperator() = 0 ;
			
		public:
			__fastcall virtual ~TOperation();
			TMongoUpdate::TModifier* __fastcall End();
			__property TMongoDocument* Writer = {read=FWriter};
		};
		
		
#ifndef _WIN64
		typedef System::TMetaClass* TOperationClass;
#else /* _WIN64 */
		_DECLARE_METACLASS(System::TMetaClass, TOperationClass);
#endif /* _WIN64 */
		
		
	public:
		class DELPHICLASS TInc;
		class PASCALIMPLEMENTATION TInc : /*[[sealed]]*/ public TMongoUpdate::TModifier::TOperation
		{
			typedef TMongoUpdate::TModifier::TOperation inherited;
			
		protected:
			__classmethod virtual System::UnicodeString __fastcall GetOperator();
			
		public:
			HIDESBASE TMongoUpdate::TModifier::TInc* __fastcall Field(const System::UnicodeString AName, const System::Variant &AValue);
		protected:
			/* TOperation.Create */ inline __fastcall TInc(TMongoUpdate::TModifier* AModifier) : TMongoUpdate::TModifier::TOperation(AModifier) { }
			
		public:
			/* TOperation.Destroy */ inline __fastcall virtual ~TInc() { }
			
		};
		
		
		class DELPHICLASS TMul;
		class PASCALIMPLEMENTATION TMul : /*[[sealed]]*/ public TMongoUpdate::TModifier::TOperation
		{
			typedef TMongoUpdate::TModifier::TOperation inherited;
			
		protected:
			__classmethod virtual System::UnicodeString __fastcall GetOperator();
			
		public:
			HIDESBASE TMongoUpdate::TModifier::TMul* __fastcall Field(const System::UnicodeString AName, const System::Variant &AValue);
		protected:
			/* TOperation.Create */ inline __fastcall TMul(TMongoUpdate::TModifier* AModifier) : TMongoUpdate::TModifier::TOperation(AModifier) { }
			
		public:
			/* TOperation.Destroy */ inline __fastcall virtual ~TMul() { }
			
		};
		
		
		class DELPHICLASS TRename;
		class PASCALIMPLEMENTATION TRename : /*[[sealed]]*/ public TMongoUpdate::TModifier::TOperation
		{
			typedef TMongoUpdate::TModifier::TOperation inherited;
			
		protected:
			__classmethod virtual System::UnicodeString __fastcall GetOperator();
			
		public:
			HIDESBASE TMongoUpdate::TModifier::TRename* __fastcall Field(const System::UnicodeString AOldName, const System::UnicodeString ANewName);
		protected:
			/* TOperation.Create */ inline __fastcall TRename(TMongoUpdate::TModifier* AModifier) : TMongoUpdate::TModifier::TOperation(AModifier) { }
			
		public:
			/* TOperation.Destroy */ inline __fastcall virtual ~TRename() { }
			
		};
		
		
		class DELPHICLASS TSetOnInsert;
		class PASCALIMPLEMENTATION TSetOnInsert : /*[[sealed]]*/ public TMongoUpdate::TModifier::TOperation
		{
			typedef TMongoUpdate::TModifier::TOperation inherited;
			
		protected:
			__classmethod virtual System::UnicodeString __fastcall GetOperator();
			
		public:
			HIDESBASE TMongoUpdate::TModifier::TSetOnInsert* __fastcall Field(const System::UnicodeString AName, const System::Variant &AValue);
		protected:
			/* TOperation.Create */ inline __fastcall TSetOnInsert(TMongoUpdate::TModifier* AModifier) : TMongoUpdate::TModifier::TOperation(AModifier) { }
			
		public:
			/* TOperation.Destroy */ inline __fastcall virtual ~TSetOnInsert() { }
			
		};
		
		
		class DELPHICLASS TSet;
		class PASCALIMPLEMENTATION TSet : /*[[sealed]]*/ public TMongoUpdate::TModifier::TOperation
		{
			typedef TMongoUpdate::TModifier::TOperation inherited;
			
		protected:
			__classmethod virtual System::UnicodeString __fastcall GetOperator();
			
		public:
			HIDESBASE TMongoUpdate::TModifier::TSet* __fastcall Field(const System::UnicodeString AName, const System::Variant &AValue);
		protected:
			/* TOperation.Create */ inline __fastcall TSet(TMongoUpdate::TModifier* AModifier) : TMongoUpdate::TModifier::TOperation(AModifier) { }
			
		public:
			/* TOperation.Destroy */ inline __fastcall virtual ~TSet() { }
			
		};
		
		
		class DELPHICLASS TUnset;
		class PASCALIMPLEMENTATION TUnset : /*[[sealed]]*/ public TMongoUpdate::TModifier::TOperation
		{
			typedef TMongoUpdate::TModifier::TOperation inherited;
			
		protected:
			__classmethod virtual System::UnicodeString __fastcall GetOperator();
			
		public:
			HIDESBASE TMongoUpdate::TModifier::TUnset* __fastcall Field(const System::UnicodeString AName);
		protected:
			/* TOperation.Create */ inline __fastcall TUnset(TMongoUpdate::TModifier* AModifier) : TMongoUpdate::TModifier::TOperation(AModifier) { }
			
		public:
			/* TOperation.Destroy */ inline __fastcall virtual ~TUnset() { }
			
		};
		
		
		class DELPHICLASS TMin;
		class PASCALIMPLEMENTATION TMin : /*[[sealed]]*/ public TMongoUpdate::TModifier::TOperation
		{
			typedef TMongoUpdate::TModifier::TOperation inherited;
			
		protected:
			__classmethod virtual System::UnicodeString __fastcall GetOperator();
			
		public:
			HIDESBASE TMongoUpdate::TModifier::TMin* __fastcall Field(const System::UnicodeString AName, const System::Variant &AValue);
		protected:
			/* TOperation.Create */ inline __fastcall TMin(TMongoUpdate::TModifier* AModifier) : TMongoUpdate::TModifier::TOperation(AModifier) { }
			
		public:
			/* TOperation.Destroy */ inline __fastcall virtual ~TMin() { }
			
		};
		
		
		class DELPHICLASS TMax;
		class PASCALIMPLEMENTATION TMax : /*[[sealed]]*/ public TMongoUpdate::TModifier::TOperation
		{
			typedef TMongoUpdate::TModifier::TOperation inherited;
			
		protected:
			__classmethod virtual System::UnicodeString __fastcall GetOperator();
			
		public:
			HIDESBASE TMongoUpdate::TModifier::TMax* __fastcall Field(const System::UnicodeString AName, const System::Variant &AValue);
		protected:
			/* TOperation.Create */ inline __fastcall TMax(TMongoUpdate::TModifier* AModifier) : TMongoUpdate::TModifier::TOperation(AModifier) { }
			
		public:
			/* TOperation.Destroy */ inline __fastcall virtual ~TMax() { }
			
		};
		
		
		class DELPHICLASS TCurrentDate;
		class PASCALIMPLEMENTATION TCurrentDate : /*[[sealed]]*/ public TMongoUpdate::TModifier::TOperation
		{
			typedef TMongoUpdate::TModifier::TOperation inherited;
			
		protected:
			__classmethod virtual System::UnicodeString __fastcall GetOperator();
			
		public:
			TMongoUpdate::TModifier::TCurrentDate* __fastcall AsDate(const System::UnicodeString AName);
			TMongoUpdate::TModifier::TCurrentDate* __fastcall AsTimestamp(const System::UnicodeString AName);
		protected:
			/* TOperation.Create */ inline __fastcall TCurrentDate(TMongoUpdate::TModifier* AModifier) : TMongoUpdate::TModifier::TOperation(AModifier) { }
			
		public:
			/* TOperation.Destroy */ inline __fastcall virtual ~TCurrentDate() { }
			
		};
		
		
		class DELPHICLASS TArrayOperation;
		class PASCALIMPLEMENTATION TArrayOperation : public TMongoUpdate::TModifier::TOperation
		{
			typedef TMongoUpdate::TModifier::TOperation inherited;
			
		protected:
			HIDESBASE TMongoUpdate::TModifier::TArrayOperation* __fastcall Field(const System::UnicodeString AName, const System::Variant &AValues, bool AEach, bool AClose)/* overload */;
			HIDESBASE TMongoUpdate::TModifier::TArrayOperation* __fastcall Field(const System::UnicodeString AName, const System::TVarRec *AValues, const int AValues_High, bool AEach, bool AClose)/* overload */;
		protected:
			/* TOperation.Create */ inline __fastcall TArrayOperation(TMongoUpdate::TModifier* AModifier) : TMongoUpdate::TModifier::TOperation(AModifier) { }
			
		public:
			/* TOperation.Destroy */ inline __fastcall virtual ~TArrayOperation() { }
			
		};
		
		
		class DELPHICLASS TAddToSet;
		class PASCALIMPLEMENTATION TAddToSet : /*[[sealed]]*/ public TMongoUpdate::TModifier::TArrayOperation
		{
			typedef TMongoUpdate::TModifier::TArrayOperation inherited;
			
		protected:
			__classmethod virtual System::UnicodeString __fastcall GetOperator();
			
		public:
			HIDESBASE TMongoUpdate::TModifier::TAddToSet* __fastcall Field(const System::UnicodeString AName, const System::Variant &AValues, bool AEach = true)/* overload */;
			HIDESBASE TMongoUpdate::TModifier::TAddToSet* __fastcall Field(const System::UnicodeString AName, const System::TVarRec *AValues, const int AValues_High, bool AEach = true)/* overload */;
		protected:
			/* TOperation.Create */ inline __fastcall TAddToSet(TMongoUpdate::TModifier* AModifier) : TMongoUpdate::TModifier::TArrayOperation(AModifier) { }
			
		public:
			/* TOperation.Destroy */ inline __fastcall virtual ~TAddToSet() { }
			
	/* Hoisted overloads: */
			
		protected:
			inline TMongoUpdate::TModifier::TArrayOperation* __fastcall  Field(const System::UnicodeString AName, const System::Variant &AValues, bool AEach, bool AClose){ return TMongoUpdate::TModifier::TArrayOperation::Field(AName, AValues, AEach, AClose); }
			inline TMongoUpdate::TModifier::TArrayOperation* __fastcall  Field(const System::UnicodeString AName, const System::TVarRec *AValues, const int AValues_High, bool AEach, bool AClose){ return TMongoUpdate::TModifier::TArrayOperation::Field(AName, AValues, AValues_High, AEach, AClose); }
			
		};
		
		
		class DELPHICLASS TPop;
		class PASCALIMPLEMENTATION TPop : /*[[sealed]]*/ public TMongoUpdate::TModifier::TArrayOperation
		{
			typedef TMongoUpdate::TModifier::TArrayOperation inherited;
			
		protected:
			__classmethod virtual System::UnicodeString __fastcall GetOperator();
			
		public:
			TMongoUpdate::TModifier::TPop* __fastcall First(const System::UnicodeString AName);
			TMongoUpdate::TModifier::TPop* __fastcall Last(const System::UnicodeString AName);
		protected:
			/* TOperation.Create */ inline __fastcall TPop(TMongoUpdate::TModifier* AModifier) : TMongoUpdate::TModifier::TArrayOperation(AModifier) { }
			
		public:
			/* TOperation.Destroy */ inline __fastcall virtual ~TPop() { }
			
		};
		
		
		class DELPHICLASS TPull;
		class PASCALIMPLEMENTATION TPull : /*[[sealed]]*/ public TMongoUpdate::TModifier::TArrayOperation
		{
			typedef TMongoUpdate::TModifier::TArrayOperation inherited;
			
		protected:
			__classmethod virtual System::UnicodeString __fastcall GetOperator();
			
		public:
			HIDESBASE TMongoUpdate::TModifier::TPull* __fastcall Field(const System::UnicodeString AName, const System::Variant &AValue);
			TMongoUpdate::TModifier::TPull* __fastcall Where(const System::UnicodeString AName, const System::UnicodeString AValue);
		protected:
			/* TOperation.Create */ inline __fastcall TPull(TMongoUpdate::TModifier* AModifier) : TMongoUpdate::TModifier::TArrayOperation(AModifier) { }
			
		public:
			/* TOperation.Destroy */ inline __fastcall virtual ~TPull() { }
			
		};
		
		
		class DELPHICLASS TPullAll;
		class PASCALIMPLEMENTATION TPullAll : /*[[sealed]]*/ public TMongoUpdate::TModifier::TArrayOperation
		{
			typedef TMongoUpdate::TModifier::TArrayOperation inherited;
			
		protected:
			__classmethod virtual System::UnicodeString __fastcall GetOperator();
			
		public:
			HIDESBASE TMongoUpdate::TModifier::TPullAll* __fastcall Field(const System::UnicodeString AName, const System::Variant &AValues)/* overload */;
			HIDESBASE TMongoUpdate::TModifier::TPullAll* __fastcall Field(const System::UnicodeString AName, const System::TVarRec *AValues, const int AValues_High)/* overload */;
		protected:
			/* TOperation.Create */ inline __fastcall TPullAll(TMongoUpdate::TModifier* AModifier) : TMongoUpdate::TModifier::TArrayOperation(AModifier) { }
			
		public:
			/* TOperation.Destroy */ inline __fastcall virtual ~TPullAll() { }
			
	/* Hoisted overloads: */
			
		protected:
			inline TMongoUpdate::TModifier::TArrayOperation* __fastcall  Field(const System::UnicodeString AName, const System::Variant &AValues, bool AEach, bool AClose){ return TMongoUpdate::TModifier::TArrayOperation::Field(AName, AValues, AEach, AClose); }
			inline TMongoUpdate::TModifier::TArrayOperation* __fastcall  Field(const System::UnicodeString AName, const System::TVarRec *AValues, const int AValues_High, bool AEach, bool AClose){ return TMongoUpdate::TModifier::TArrayOperation::Field(AName, AValues, AValues_High, AEach, AClose); }
			
		};
		
		
		class DELPHICLASS TPush;
		class PASCALIMPLEMENTATION TPush : /*[[sealed]]*/ public TMongoUpdate::TModifier::TArrayOperation
		{
			typedef TMongoUpdate::TModifier::TArrayOperation inherited;
			
		protected:
			__classmethod virtual System::UnicodeString __fastcall GetOperator();
			
		public:
			HIDESBASE TMongoUpdate::TModifier::TPush* __fastcall Field(const System::UnicodeString AName, const System::Variant &AValues, bool AEach = true, int ASlice = 0x7fffffff, const System::UnicodeString ASort = System::UnicodeString())/* overload */;
			HIDESBASE TMongoUpdate::TModifier::TPush* __fastcall Field(const System::UnicodeString AName, const System::TVarRec *AValues, const int AValues_High, bool AEach = true, int ASlice = 0x7fffffff, const System::UnicodeString ASort = System::UnicodeString())/* overload */;
		protected:
			/* TOperation.Create */ inline __fastcall TPush(TMongoUpdate::TModifier* AModifier) : TMongoUpdate::TModifier::TArrayOperation(AModifier) { }
			
		public:
			/* TOperation.Destroy */ inline __fastcall virtual ~TPush() { }
			
	/* Hoisted overloads: */
			
		protected:
			inline TMongoUpdate::TModifier::TArrayOperation* __fastcall  Field(const System::UnicodeString AName, const System::Variant &AValues, bool AEach, bool AClose){ return TMongoUpdate::TModifier::TArrayOperation::Field(AName, AValues, AEach, AClose); }
			inline TMongoUpdate::TModifier::TArrayOperation* __fastcall  Field(const System::UnicodeString AName, const System::TVarRec *AValues, const int AValues_High, bool AEach, bool AClose){ return TMongoUpdate::TModifier::TArrayOperation::Field(AName, AValues, AValues_High, AEach, AClose); }
			
		};
		
		
		class DELPHICLASS TPushAll;
		class PASCALIMPLEMENTATION TPushAll : /*[[sealed]]*/ public TMongoUpdate::TModifier::TArrayOperation
		{
			typedef TMongoUpdate::TModifier::TArrayOperation inherited;
			
		protected:
			__classmethod virtual System::UnicodeString __fastcall GetOperator();
			
		public:
			HIDESBASE TMongoUpdate::TModifier::TPushAll* __fastcall Field(const System::UnicodeString AName, const System::Variant &AValues)/* overload */;
			HIDESBASE TMongoUpdate::TModifier::TPushAll* __fastcall Field(const System::UnicodeString AName, const System::TVarRec *AValues, const int AValues_High)/* overload */;
		protected:
			/* TOperation.Create */ inline __fastcall TPushAll(TMongoUpdate::TModifier* AModifier) : TMongoUpdate::TModifier::TArrayOperation(AModifier) { }
			
		public:
			/* TOperation.Destroy */ inline __fastcall virtual ~TPushAll() { }
			
	/* Hoisted overloads: */
			
		protected:
			inline TMongoUpdate::TModifier::TArrayOperation* __fastcall  Field(const System::UnicodeString AName, const System::Variant &AValues, bool AEach, bool AClose){ return TMongoUpdate::TModifier::TArrayOperation::Field(AName, AValues, AEach, AClose); }
			inline TMongoUpdate::TModifier::TArrayOperation* __fastcall  Field(const System::UnicodeString AName, const System::TVarRec *AValues, const int AValues_High, bool AEach, bool AClose){ return TMongoUpdate::TModifier::TArrayOperation::Field(AName, AValues, AValues_High, AEach, AClose); }
			
		};
		
		
		
	private:
		TMongoUpdate* FUpdate;
		System::Classes::TStringList* FOperations;
		TMongoDocument* FWriter;
		System::UnicodeString FCustomJSON;
		
	protected:
		__fastcall TModifier(TMongoUpdate* AUpdate);
		
	private:
		TOperation* __fastcall GetOperation(TOperationClass AType, const System::UnicodeString AJSON);
		TMongoDocument* __fastcall GetFinalBSON();
		
	public:
		__fastcall virtual ~TModifier();
		TMongoUpdate::TModifier* __fastcall Clear();
		TInc* __fastcall Inc(const System::UnicodeString AJSON = System::UnicodeString());
		TMul* __fastcall Mul(const System::UnicodeString AJSON = System::UnicodeString());
		TRename* __fastcall Rename(const System::UnicodeString AJSON = System::UnicodeString());
		TSetOnInsert* __fastcall SetOnInsert(const System::UnicodeString AJSON = System::UnicodeString());
		TSet* __fastcall Set(const System::UnicodeString AJSON = System::UnicodeString());
		TUnset* __fastcall Unset(const System::UnicodeString AJSON = System::UnicodeString());
		TMin* __fastcall Min(const System::UnicodeString AJSON = System::UnicodeString());
		TMax* __fastcall Max(const System::UnicodeString AJSON = System::UnicodeString());
		TCurrentDate* __fastcall CurrentDate(const System::UnicodeString AJSON = System::UnicodeString());
		TAddToSet* __fastcall AddToSet(const System::UnicodeString AJSON = System::UnicodeString());
		TPop* __fastcall Pop(const System::UnicodeString AJSON = System::UnicodeString());
		TPull* __fastcall Pull(const System::UnicodeString AJSON = System::UnicodeString());
		TPullAll* __fastcall PullAll(const System::UnicodeString AJSON = System::UnicodeString());
		TPush* __fastcall Push(const System::UnicodeString AJSON = System::UnicodeString());
		TPushAll* __fastcall PushAll(const System::UnicodeString AJSON = System::UnicodeString());
		TMongoUpdate* __fastcall End();
	};
	
	
	
private:
	TMongoEnv* FEnv;
	System::TObject* FOwningObj;
	_di_TRunUpdate FRunUpdate;
	TModifier* FModifier;
	TExpression* FMatcher;
	TMongoDocument* __fastcall GetFinalModifyBSON();
	TMongoDocument* __fastcall GetFinalMatchBSON();
	
protected:
	__fastcall TMongoUpdate(TMongoEnv* AEnv, System::TObject* AOwningObj, _di_TRunUpdate ARunUpdate)/* overload */;
	virtual void __fastcall DoGetFinalModifyBSON(TMongoDocument* AWriter);
	virtual void __fastcall DoGetFinalMatchBSON(TMongoDocument* AWriter);
	
public:
	__fastcall TMongoUpdate(TMongoEnv* AEnv)/* overload */;
	__fastcall virtual ~TMongoUpdate();
	TExpression* __fastcall Match(const System::UnicodeString AJSON = System::UnicodeString());
	TModifier* __fastcall Modify(const System::UnicodeString AJSON = System::UnicodeString());
	void __fastcall Exec();
	__property TMongoDocument* FinalModifyBSON = {read=GetFinalModifyBSON};
	__property TMongoDocument* FinalMatchBSON = {read=GetFinalMatchBSON};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoSelector : public System::TObject
{
	typedef System::TObject inherited;
	
	
protected:
	__interface DELPHIINTERFACE TRunOper;
	typedef System::DelphiInterface<TRunOper> _di_TRunOper;
	__interface TRunOper  : public System::IInterface 
	{
		virtual void __fastcall Invoke(TMongoSelector* ASelector) = 0 ;
	};
	
	
public:
	class DELPHICLASS TExpression;
	class PASCALIMPLEMENTATION TExpression : /*[[sealed]]*/ public TMongoExpression__1<TMongoSelector*>
	{
		typedef TMongoExpression__1<TMongoSelector*> inherited;
		
	protected:
		/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoSelector>.Create */ inline __fastcall TExpression(TMongoEnv* AEnv, System::TObject* AOwningObj, TMongoSelector* AParentObj)/* overload */ : TMongoExpression__1<TMongoSelector*>(AEnv, AOwningObj, AParentObj) { }
		
	public:
		/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoSelector>.Create */ inline __fastcall TExpression(TMongoEnv* AEnv)/* overload */ : TMongoExpression__1<TMongoSelector*>(AEnv) { }
		/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoSelector>.Destroy */ inline __fastcall virtual ~TExpression() { }
		
	};
	
	
	
private:
	TMongoEnv* FEnv;
	System::TObject* FOwningObj;
	TExpression* FMatcher;
	_di_TRunOper FRunOper;
	TMongoDocument* __fastcall GetFinalMatchBSON();
	
protected:
	__fastcall TMongoSelector(TMongoEnv* AEnv, System::TObject* AOwningObj, _di_TRunOper ARunOper)/* overload */;
	virtual void __fastcall DoGetFinalMatchBSON(TMongoDocument* AWriter);
	
public:
	__fastcall TMongoSelector(TMongoEnv* AEnv)/* overload */;
	__fastcall virtual ~TMongoSelector();
	TExpression* __fastcall Match(const System::UnicodeString AJSON = System::UnicodeString());
	void __fastcall Exec();
	__property TMongoDocument* FinalMatchBSON = {read=GetFinalMatchBSON};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoInsert : public System::TObject
{
	typedef System::TObject inherited;
	
	
protected:
	__interface DELPHIINTERFACE TRunOper;
	typedef System::DelphiInterface<TRunOper> _di_TRunOper;
	__interface TRunOper  : public System::IInterface 
	{
		virtual void __fastcall Invoke(TMongoInsert* ASelector) = 0 ;
	};
	
	
public:
	class DELPHICLASS TExpression;
	class PASCALIMPLEMENTATION TExpression : /*[[sealed]]*/ public TMongoExpression__1<TMongoInsert*>
	{
		typedef TMongoExpression__1<TMongoInsert*> inherited;
		
	protected:
		/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoInsert>.Create */ inline __fastcall TExpression(TMongoEnv* AEnv, System::TObject* AOwningObj, TMongoInsert* AParentObj)/* overload */ : TMongoExpression__1<TMongoInsert*>(AEnv, AOwningObj, AParentObj) { }
		
	public:
		/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoInsert>.Create */ inline __fastcall TExpression(TMongoEnv* AEnv)/* overload */ : TMongoExpression__1<TMongoInsert*>(AEnv) { }
		/* {FireDAC_Phys_MongoDBWrapper}TMongoExpression<FireDAC_Phys_MongoDBWrapper_TMongoInsert>.Destroy */ inline __fastcall virtual ~TExpression() { }
		
	};
	
	
	
private:
	TMongoEnv* FEnv;
	System::TObject* FOwningObj;
	TExpression* FValues;
	_di_TRunOper FRunOper;
	TMongoDocument* __fastcall GetFinalValuesBSON();
	
protected:
	__fastcall TMongoInsert(TMongoEnv* AEnv, System::TObject* AOwningObj, _di_TRunOper ARunOper)/* overload */;
	virtual void __fastcall DoGetFinalValuesBSON(TMongoDocument* AWriter);
	
public:
	__fastcall TMongoInsert(TMongoEnv* AEnv)/* overload */;
	__fastcall virtual ~TMongoInsert();
	TExpression* __fastcall Values(const System::UnicodeString AJSON = System::UnicodeString());
	void __fastcall Exec();
	__property TMongoDocument* FinalValuesBSON = {read=GetFinalValuesBSON};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoIndex : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	class DELPHICLASS TKeys;
	class PASCALIMPLEMENTATION TKeys : /*[[sealed]]*/ public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		TMongoDocument* FWriter;
		
	protected:
		__fastcall TKeys(TMongoIndex* AIndex);
		
	public:
		__fastcall virtual ~TKeys();
		TMongoIndex::TKeys* __fastcall Field(const System::UnicodeString AName, bool AAscending = true)/* overload */;
		TMongoIndex::TKeys* __fastcall Field(const System::UnicodeString AName, const System::UnicodeString AKind)/* overload */;
		TMongoIndex::TKeys* __fastcall Ascending(const System::UnicodeString *AFields, const int AFields_High);
		TMongoIndex::TKeys* __fastcall Descending(const System::UnicodeString *AFields, const int AFields_High);
	};
	
	
	class DELPHICLASS TOptions;
	class PASCALIMPLEMENTATION TOptions : /*[[sealed]]*/ public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		TMongoIndex* FIndex;
		Firedac::Phys::Mongodbcli::mongoc_index_opt_t FOpts;
		System::UnicodeString FName;
		System::RawByteString FBName;
		void __fastcall SetName(const System::UnicodeString AValue);
		
	protected:
		__fastcall TOptions(TMongoIndex* AIndex);
		
	public:
		__property System::UnicodeString Name = {read=FName, write=SetName};
		__property bool Background = {read=FOpts.background, write=FOpts.background, default=0};
		__property bool Unique = {read=FOpts.unique, write=FOpts.unique, default=0};
		__property bool DropDups = {read=FOpts.drop_dups, write=FOpts.drop_dups, default=0};
		__property bool Sparse = {read=FOpts.sparse, write=FOpts.sparse, default=0};
		__property int ExpireAfter = {read=FOpts.expire_after_seconds, write=FOpts.expire_after_seconds, default=0};
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TOptions() { }
		
	};
	
	
	
private:
	TMongoEnv* FEnv;
	System::TObject* FOwningObj;
	TKeys* FKeys;
	TOptions* FOptions;
	
public:
	__fastcall TMongoIndex(TMongoEnv* AEnv)/* overload */;
	__fastcall virtual ~TMongoIndex();
	TKeys* __fastcall Keys(const System::UnicodeString AJSON = System::UnicodeString());
	__property TOptions* Options = {read=FOptions};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoCursor : public TMongoObject
{
	typedef TMongoObject inherited;
	
	
protected:
	class DELPHICLASS TDefault;
	class PASCALIMPLEMENTATION TDefault : public System::TInterfacedObject
	{
		typedef System::TInterfacedObject inherited;
		
	private:
		TMongoCursor* FCursor;
		System::TObject* FReleaseObj;
		
	protected:
		TMongoDocument* __fastcall GetDoc();
		bool __fastcall GetIsAlive();
		bool __fastcall Next()/* overload */;
		bool __fastcall Next(TMongoDocument* ADoc)/* overload */;
		__fastcall TDefault(TMongoEnv* AEnv, System::TObject* AOwningObj, System::TObject* AReleaseObj, void * AHandle);
		
	public:
		__fastcall virtual ~TDefault();
private:
		void *__IMongoCursor;	// IMongoCursor 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {7D8AF712-3FA8-459B-BF9B-4EC7E55B7359}
		operator _di_IMongoCursor()
		{
			_di_IMongoCursor intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator IMongoCursor*(void) { return (IMongoCursor*)&__IMongoCursor; }
		#endif
		
	};
	
	
	
private:
	TMongoDocument* FDoc;
	bool FEof;
	TMongoDocument* __fastcall GetDoc();
	bool __fastcall GetIsAlive();
	
protected:
	virtual void __fastcall InternalFreeHandle();
	
public:
	__fastcall virtual ~TMongoCursor();
	bool __fastcall Next()/* overload */;
	bool __fastcall Next(TMongoDocument* ADoc)/* overload */;
	__property TMongoDocument* Doc = {read=GetDoc};
	__property bool IsAlive = {read=GetIsAlive, nodefault};
protected:
	/* TMongoObject.Create */ inline __fastcall TMongoCursor(TMongoEnv* AEnv, System::TObject* AOwningObj)/* overload */ : TMongoObject(AEnv, AOwningObj) { }
	/* TMongoObject.Create */ inline __fastcall TMongoCursor(TMongoEnv* AEnv, System::TObject* AOwningObj, void * AHandle)/* overload */ : TMongoObject(AEnv, AOwningObj, AHandle) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoConnection : public TMongoObject
{
	typedef TMongoObject inherited;
	
public:
	TMongoDatabase* operator[](const System::UnicodeString ADBName) { return this->Databases[ADBName]; }
	
private:
	TMongoReadPreference* FReadPreference;
	TMongoWriteConcern* FWriteConcern;
	System::RawByteString FPEMFile;
	System::RawByteString FPEMPwd;
	System::RawByteString FCAFile;
	System::RawByteString FCADir;
	System::RawByteString FCRLFile;
	Firedac::Phys::Mongodbcli::mongoc_ssl_opt_t Fmongoc_ssl_opt;
	TMongoDatabase* FDatabase;
	TMongoCollection* FCollection;
	int __fastcall Getmax_bson_size();
	int __fastcall Getmax_message_size();
	TMongoDatabase* __fastcall InternalGetDatabase(const System::UnicodeString ADBName, bool ANew);
	TMongoCollection* __fastcall InternalGetCollection(const System::UnicodeString ADBName, const System::UnicodeString AColName, bool ANew);
	TMongoCollection* __fastcall GetCollectionsProp(const System::UnicodeString ADBName, const System::UnicodeString AColName);
	TMongoDatabase* __fastcall GetDatabasesProp(const System::UnicodeString ADBName);
	unsigned __int64 __fastcall GetServerVersion();
	System::UnicodeString __fastcall GetURI();
	
protected:
	virtual void __fastcall InternalFreeHandle();
	virtual void __fastcall FreeHandle();
	virtual void __fastcall HandleAllocated();
	
public:
	__fastcall TMongoConnection(TMongoEnv* AEnv, System::TObject* AOwningObj);
	__fastcall TMongoConnection(TMongoEnv* AEnv, void * AHandle, System::TObject* AOwningObj);
	__fastcall virtual ~TMongoConnection();
	void __fastcall Open(const System::UnicodeString AUri);
	void __fastcall SSLInit(const System::UnicodeString APEMFile, const System::UnicodeString APEMPwd, const System::UnicodeString ACAFile, const System::UnicodeString ACADir, const System::UnicodeString ACRLFile, bool AWeakValid);
	void __fastcall Close();
	void __fastcall Ping();
	TMongoDocument* __fastcall GetServerStatus();
	_di_IMongoCursor __fastcall ListDatabases();
	TMongoDatabase* __fastcall GetDatabase(const System::UnicodeString ADBName);
	TMongoCollection* __fastcall GetCollection(const System::UnicodeString ADBName, const System::UnicodeString AColName);
	_di_IMongoCursor __fastcall Command(const System::UnicodeString ADBName, TMongoCommand* ACommand, TMongoQueryFlags AFlags = TMongoQueryFlags() )/* overload */;
	_di_IMongoCursor __fastcall Command(const System::UnicodeString ADBName, const System::UnicodeString AJSON, TMongoQueryFlags AFlags = TMongoQueryFlags() )/* overload */;
	TMongoDocument* __fastcall CommandSimple(const System::UnicodeString ADBName, TMongoDocument* ACommand)/* overload */;
	TMongoDocument* __fastcall CommandSimple(const System::UnicodeString ADBName, const System::UnicodeString AJSON)/* overload */;
	TMongoDocument* __fastcall Dereference(const System::Json::Types::TJsonDBRef &ADBRef);
	__property System::UnicodeString URI = {read=GetURI};
	__property int max_message_size = {read=Getmax_message_size, nodefault};
	__property int max_bson_size = {read=Getmax_bson_size, nodefault};
	__property unsigned __int64 ServerVersion = {read=GetServerVersion};
	__property TMongoReadPreference* ReadPreference = {read=FReadPreference};
	__property TMongoWriteConcern* WriteConcern = {read=FWriteConcern};
	__property TMongoDatabase* Databases[const System::UnicodeString ADBName] = {read=GetDatabasesProp/*, default*/};
	__property TMongoCollection* Collections[const System::UnicodeString ADBName][const System::UnicodeString AColName] = {read=GetCollectionsProp};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMongoDatabase : public TMongoObject
{
	typedef TMongoObject inherited;
	
public:
	TMongoCollection* operator[](const System::UnicodeString AColName) { return this->Collections[AColName]; }
	
private:
	TMongoCollection* FCollection;
	TMongoReadPreference* FReadPreference;
	TMongoWriteConcern* FWriteConcern;
	System::UnicodeString __fastcall GetName();
	TMongoCollection* __fastcall InternalGetCollection(const System::UnicodeString AColName, bool ANew);
	TMongoCollection* __fastcall GetCollectionsProp(const System::UnicodeString AColName);
	
protected:
	virtual void __fastcall InternalFreeHandle();
	virtual void __fastcall FreeHandle();
	virtual void __fastcall HandleAllocated();
	__fastcall TMongoDatabase(TMongoEnv* AEnv, System::TObject* AOwningObj, void * AHandle);
	
public:
	__fastcall virtual ~TMongoDatabase();
	void __fastcall Drop();
	void __fastcall AddUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, TMongoDocument* ARoles, TMongoDocument* ACustomData);
	void __fastcall DropUser(const System::UnicodeString AUserName);
	void __fastcall DropAllUsers();
	_di_IMongoCursor __fastcall ListCollections(TMongoSelector* ASelector = (TMongoSelector*)(0x0));
	bool __fastcall HasCollection(const System::UnicodeString AName);
	void __fastcall CreateCollection(const System::UnicodeString AName, TMongoDocument* AOptions);
	void __fastcall DropCollection(const System::UnicodeString AName, bool AIgnoreObjNotExists = false);
	TMongoCollection* __fastcall GetCollection(const System::UnicodeString AColName);
	_di_IMongoCursor __fastcall Command(TMongoCommand* ACommand, TMongoQueryFlags AFlags = TMongoQueryFlags() )/* overload */;
	_di_IMongoCursor __fastcall Command(const System::UnicodeString AJSON, TMongoQueryFlags AFlags = TMongoQueryFlags() )/* overload */;
	TMongoDocument* __fastcall CommandSimple(TMongoDocument* ACommand)/* overload */;
	TMongoDocument* __fastcall CommandSimple(const System::UnicodeString AJSON)/* overload */;
	TMongoDocument* __fastcall Dereference(const System::Json::Types::TJsonDBRef &ADBRef);
	__property System::UnicodeString Name = {read=GetName};
	__property TMongoReadPreference* ReadPreference = {read=FReadPreference};
	__property TMongoWriteConcern* WriteConcern = {read=FWriteConcern};
	__property TMongoCollection* Collections[const System::UnicodeString AColName] = {read=GetCollectionsProp/*, default*/};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TMongoCollection : public TMongoObject
{
	typedef TMongoObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TInsertFlag : unsigned int { ContinueOnError, NoValidate };
	
	typedef System::Set<TInsertFlag, _DELPHI_SET_ENUMERATOR(TInsertFlag::ContinueOnError), _DELPHI_SET_ENUMERATOR(TInsertFlag::NoValidate)> TInsertFlags;
	
	enum class DECLSPEC_DENUM TRemoveFlag : unsigned int { SingleRemove };
	
	typedef System::Set<TRemoveFlag, _DELPHI_SET_ENUMERATOR(TRemoveFlag::SingleRemove), _DELPHI_SET_ENUMERATOR(TRemoveFlag::SingleRemove)> TRemoveFlags;
	
	enum class DECLSPEC_DENUM TUpdateFlag : unsigned int { Upsert, MultiUpdate };
	
	typedef System::Set<TUpdateFlag, _DELPHI_SET_ENUMERATOR(TUpdateFlag::Upsert), _DELPHI_SET_ENUMERATOR(TUpdateFlag::MultiUpdate)> TUpdateFlags;
	
	
private:
	TMongoReadPreference* FReadPreference;
	TMongoWriteConcern* FWriteConcern;
	TMongoDocument* FLastError;
	void *FBulkHandle;
	__int64 FDocsInserted;
	__int64 FDocsMatched;
	__int64 FDocsModified;
	__int64 FDocsRemoved;
	__int64 FDocsUpserted;
	TMongoOID* FLastOID;
	System::Variant FLastID;
	System::UnicodeString __fastcall GetName();
	System::UnicodeString __fastcall GetDB();
	System::UnicodeString __fastcall GetNS();
	void __fastcall ResetCounts();
	void __fastcall ProcessWriteResult(TMongoDocument* AReply, bool ABulk, bool AFailed);
	TMongoDocument* __fastcall GetLastError();
	bool __fastcall GetIsBulk();
	void __fastcall EnsureID(TMongoDocument* ADocument);
	_di_IMongoCursor __fastcall AggregateBase(TMongoPipeline* APipeline, bool AReleasePipeline, TMongoQueryFlags AFlags);
	_di_IMongoCursor __fastcall FindBase(TMongoQuery* AQuery, bool AReleaseQuery, TMongoQueryFlags AFlags);
	
protected:
	virtual void __fastcall InternalFreeHandle();
	virtual void __fastcall FreeHandle();
	virtual void __fastcall HandleAllocated();
	__fastcall TMongoCollection(TMongoEnv* AEnv, System::TObject* AOwningObj, void * AHandle);
	
public:
	__fastcall virtual ~TMongoCollection();
	void __fastcall Drop(bool AIgnoreObjNotExists = false);
	void __fastcall Rename(const System::UnicodeString ANewDB, const System::UnicodeString ANewName, bool ADropTarget = true);
	TMongoDocument* __fastcall Validate(TMongoDocument* AOptions);
	TMongoDocument* __fastcall Statistics(TMongoDocument* AOptions);
	_di_IMongoCursor __fastcall ListIndexes();
	void __fastcall CreateIndex(TMongoIndex* AIndex);
	void __fastcall DropIndex(const System::UnicodeString AName, bool AIgnoreObjNotExists = false);
	void __fastcall BeginBulk(bool AOrdered = true);
	void __fastcall EndBulk();
	void __fastcall CancelBulk();
	void __fastcall Insert(TMongoDocument* ADocument, TInsertFlags AFlags = TInsertFlags() )/* overload */;
	void __fastcall Insert(TMongoInsert* AInsert, TInsertFlags AFlags = TInsertFlags() )/* overload */;
	TMongoInsert* __fastcall Insert(TInsertFlags AFlags = TInsertFlags() )/* overload */;
	void __fastcall Remove(TMongoSelector* ASelector, TRemoveFlags AFlags = TRemoveFlags() )/* overload */;
	TMongoSelector* __fastcall Remove(TRemoveFlags AFlags = TRemoveFlags() )/* overload */;
	void __fastcall RemoveAll();
	void __fastcall Update(TMongoUpdate* AUpdate, TUpdateFlags AFlags = (TUpdateFlags() << TUpdateFlag::MultiUpdate ))/* overload */;
	TMongoUpdate* __fastcall Update(TUpdateFlags AFlags = (TUpdateFlags() << TUpdateFlag::MultiUpdate ))/* overload */;
	__int64 __fastcall Count(TMongoQuery* AQuery, TMongoQueryFlags AFlags = TMongoQueryFlags() )/* overload */;
	TMongoQuery* __fastcall Count(TMongoQueryFlags AFlags = TMongoQueryFlags() )/* overload */;
	_di_IMongoCursor __fastcall Aggregate(TMongoPipeline* APipeline, TMongoQueryFlags AFlags = TMongoQueryFlags() )/* overload */;
	TMongoPipeline* __fastcall Aggregate(TMongoQueryFlags AFlags = TMongoQueryFlags() )/* overload */;
	_di_IMongoCursor __fastcall Find(TMongoQuery* AQuery, TMongoQueryFlags AFlags = TMongoQueryFlags() )/* overload */;
	TMongoQuery* __fastcall Find(TMongoQueryFlags AFlags = TMongoQueryFlags() )/* overload */;
	_di_IMongoCursor __fastcall Command(TMongoCommand* ACommand, TMongoQueryFlags AFlags = TMongoQueryFlags() )/* overload */;
	_di_IMongoCursor __fastcall Command(const System::UnicodeString AJSON, TMongoQueryFlags AFlags = TMongoQueryFlags() )/* overload */;
	TMongoDocument* __fastcall CommandSimple(TMongoDocument* ACommand)/* overload */;
	TMongoDocument* __fastcall CommandSimple(const System::UnicodeString AJSON)/* overload */;
	TMongoDocument* __fastcall Dereference(const System::Json::Types::TJsonOid &AOid);
	__property System::UnicodeString Name = {read=GetName};
	__property System::UnicodeString DB = {read=GetDB};
	__property System::UnicodeString NS = {read=GetNS};
	__property bool IsBulk = {read=GetIsBulk, nodefault};
	__property TMongoDocument* LastError = {read=GetLastError};
	__property System::Variant LastID = {read=FLastID};
	__property __int64 DocsInserted = {read=FDocsInserted};
	__property __int64 DocsMatched = {read=FDocsMatched};
	__property __int64 DocsModified = {read=FDocsModified};
	__property __int64 DocsRemoved = {read=FDocsRemoved};
	__property __int64 DocsUpserted = {read=FDocsUpserted};
	__property TMongoReadPreference* ReadPreference = {read=FReadPreference};
	__property TMongoWriteConcern* WriteConcern = {read=FWriteConcern};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Mongodbwrapper */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_MONGODBWRAPPER)
using namespace Firedac::Phys::Mongodbwrapper;
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
#endif	// Firedac_Phys_MongodbwrapperHPP
