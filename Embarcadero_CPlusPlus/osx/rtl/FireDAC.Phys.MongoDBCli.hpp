// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.MongoDBCli.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_MongodbcliHPP
#define Firedac_Phys_MongodbcliHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <FireDAC.Stan.Intf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Mongodbcli
{
//-- forward type declarations -----------------------------------------------
struct bson_mem_vtable_t;
struct timeval;
struct bson_t;
struct bson_error_t;
struct bson_oid_t;
struct bson_iter_t;
struct mongoc_ssl_opt_t;
struct mongoc_index_opt_geo_t;
struct mongoc_index_opt_storage_t;
struct mongoc_index_opt_t;
struct _mongoc_collection_t;
//-- type declarations -------------------------------------------------------
typedef void * Pmongoc_handle_t;

typedef void * Pmongoc_client_t;

typedef void * Pmongoc_cursor_t;

typedef void * Pmongoc_database_t;

typedef void * Pmongoc_collection_t;

typedef void * Pmongoc_read_prefs_t;

typedef void * Pmongoc_write_concern_t;

typedef void * Pmongoc_bulk_operation_t;

typedef void * Pmongoc_matcher_t;

typedef void * Pmongoc_uri_t;

typedef void * Pbson_context_t;

typedef unsigned bson_context_flags_t;

typedef void * __cdecl (*Tbson_malloc)(NativeUInt num_bytes);

typedef void * __cdecl (*Tbson_calloc)(NativeUInt n_members, NativeUInt num_bytes);

typedef void * __cdecl (*Tbson_realloc)(void * mem, NativeUInt num_bytes);

typedef void __cdecl (*Tbson_free)(void * mem);

typedef bson_mem_vtable_t *Pbson_mem_vtable_t;

struct DECLSPEC_DRECORD bson_mem_vtable_t
{
public:
	Tbson_malloc malloc;
	Tbson_calloc calloc;
	Tbson_realloc realloc;
	Tbson_free free;
	System::StaticArray<void *, 4> padding;
};


typedef unsigned bson_type_t;

typedef unsigned bson_subtype_t;

#ifndef __x86_64__
typedef int time_t;
#else /* __x86_64__ */
typedef long time_t;
#endif /* __x86_64__ */

typedef timeval *Ptimeval;

struct DECLSPEC_DRECORD timeval
{
public:
#ifndef __x86_64__
	int tv_sec;
	int tv_usec;
#else /* __x86_64__ */
	long tv_sec;
	long tv_usec;
#endif /* __x86_64__ */
};


typedef bson_t *Pbson_t;

typedef Pbson_t *PPbson_t;

struct DECLSPEC_DRECORD bson_t
{
public:
	unsigned flags;
	unsigned len;
	System::StaticArray<System::Byte, 120> padding;
};


typedef bson_error_t *Pbson_error_t;

struct DECLSPEC_DRECORD bson_error_t
{
public:
	unsigned domain;
	unsigned code;
	System::StaticArray<char, 504> message;
};


typedef bson_oid_t *Pbson_oid_t;

struct DECLSPEC_DRECORD bson_oid_t
{
public:
	System::StaticArray<System::Byte, 12> bytes;
};


typedef bson_iter_t *Pbson_iter_t;

struct DECLSPEC_DRECORD bson_iter_t
{
public:
	System::Byte *raw;
	unsigned len;
	unsigned off;
	unsigned _type;
	unsigned key;
	unsigned d1;
	unsigned d2;
	unsigned d3;
	unsigned d4;
	unsigned next_off;
	unsigned err_off;
	System::StaticArray<System::Byte, 84> padding;
};


typedef mongoc_ssl_opt_t *Pmongoc_ssl_opt_t;

struct DECLSPEC_DRECORD mongoc_ssl_opt_t
{
public:
	char *pem_file;
	char *pem_pwd;
	char *ca_file;
	char *ca_dir;
	char *crl_file;
	bool weak_cert_validation;
	System::StaticArray<void *, 8> padding;
};


typedef unsigned mongoc_delete_flags_t;

typedef unsigned mongoc_remove_flags_t;

typedef unsigned mongoc_insert_flags_t;

typedef unsigned mongoc_query_flags_t;

typedef unsigned mongoc_reply_flags_t;

typedef unsigned mongoc_update_flags_t;

typedef unsigned mongoc_error_domain_t;

typedef unsigned mongoc_error_code_t;

typedef mongoc_index_opt_geo_t *Pmongoc_index_opt_geo_t;

struct DECLSPEC_DRECORD mongoc_index_opt_geo_t
{
public:
	System::Byte twod_sphere_version;
	System::Byte twod_bits_precision;
	double twod_location_min;
	double twod_location_max;
	double haystack_bucket_size;
	System::StaticArray<System::PByte, 32> padding;
};


typedef mongoc_index_opt_storage_t *Pmongoc_index_opt_storage_t;

struct DECLSPEC_DRECORD mongoc_index_opt_storage_t
{
public:
	int _type;
};


typedef mongoc_index_opt_t *Pmongoc_index_opt_t;

struct DECLSPEC_DRECORD mongoc_index_opt_t
{
public:
	bool is_initialized;
	bool background;
	bool unique;
	char *name;
	bool drop_dups;
	bool sparse;
	int expire_after_seconds;
	int v;
	bson_t *weights;
	char *default_language;
	char *language_override;
	mongoc_index_opt_geo_t *geo_options;
	mongoc_index_opt_storage_t *storage_options;
	System::StaticArray<void *, 6> padding;
};


typedef unsigned mongoc_log_level_t;

typedef void __cdecl (*Tmongoc_log_func_t)(unsigned log_level, char * log_domain, char * message, void * user_data);

typedef unsigned mongoc_read_mode_t;

typedef _mongoc_collection_t *P_mongoc_collection_t;

struct DECLSPEC_DRECORD _mongoc_collection_t
{
public:
	void *client;
	System::StaticArray<char, 128> ns;
	unsigned nslen;
	System::StaticArray<char, 128> db;
	System::StaticArray<char, 128> collection;
	unsigned collectionlen;
};


typedef void * __cdecl (*Tmongoc_client_new)(char * uri_string);

typedef void __cdecl (*Tmongoc_client_destroy)(void * client);

typedef void * __cdecl (*Tmongoc_client_command)(void * client, char * db_name, unsigned flags, unsigned skip, unsigned limit, unsigned batch_size, Pbson_t query, Pbson_t fields, void * read_prefs);

typedef bool __cdecl (*Tmongoc_client_command_simple)(void * client, char * db_name, Pbson_t command, void * read_prefs, Pbson_t reply, Pbson_error_t error);

typedef void __cdecl (*Tmongoc_client_kill_cursor)(void * client, __int64 cursor_id);

typedef void * __cdecl (*Tmongoc_client_get_database)(void * client, char * name);

typedef void * __cdecl (*Tmongoc_client_get_collection)(void * client, char * db, char * collection);

typedef void * __cdecl (*Tmongoc_client_find_databases)(void * client, Pbson_error_t error);

typedef bool __cdecl (*Tmongoc_client_get_server_status)(void * client, void * read_prefs, Pbson_t reply, Pbson_error_t error);

typedef int __cdecl (*Tmongoc_client_get_max_message_size)(void * client);

typedef int __cdecl (*Tmongoc_client_get_max_bson_size)(void * client);

typedef void * __cdecl (*Tmongoc_client_get_write_concern)(void * client);

typedef void __cdecl (*Tmongoc_client_set_write_concern)(void * client, void * write_concern);

typedef void * __cdecl (*Tmongoc_client_get_read_prefs)(void * client);

typedef void __cdecl (*Tmongoc_client_set_read_prefs)(void * client, void * read_prefs);

typedef void __cdecl (*Tmongoc_client_set_ssl_opts)(void * client, Pmongoc_ssl_opt_t opts);

typedef void * __cdecl (*Tmongoc_client_get_uri)(void * client);

typedef char * __cdecl (*Tmongoc_uri_get_string)(void * uri);

typedef void * __cdecl (*Tmongoc_bulk_operation_new)(bool ordered);

typedef void __cdecl (*Tmongoc_bulk_operation_destroy)(void * bulk);

typedef unsigned __cdecl (*Tmongoc_bulk_operation_execute)(void * bulk, Pbson_t reply, Pbson_error_t error);

typedef void __cdecl (*Tmongoc_bulk_operation_insert)(void * bulk, Pbson_t document);

typedef void __cdecl (*Tmongoc_bulk_operation_remove)(void * bulk, Pbson_t selector);

typedef void __cdecl (*Tmongoc_bulk_operation_remove_one)(void * bulk, Pbson_t selector);

typedef void __cdecl (*Tmongoc_bulk_operation_replace_one)(void * bulk, Pbson_t selector, Pbson_t document, bool upsert);

typedef void __cdecl (*Tmongoc_bulk_operation_update)(void * bulk, Pbson_t selector, Pbson_t document, bool upsert);

typedef void __cdecl (*Tmongoc_bulk_operation_update_one)(void * bulk, Pbson_t selector, Pbson_t document, bool upsert);

typedef void * __cdecl (*Tmongoc_collection_aggregate)(void * collection, unsigned flags, Pbson_t pipeline, Pbson_t options, void * read_prefs);

typedef void __cdecl (*Tmongoc_collection_destroy)(void * collection);

typedef void * __cdecl (*Tmongoc_collection_command)(void * collection, unsigned flags, unsigned skip, unsigned limit, unsigned batch_size, Pbson_t command, Pbson_t fields, void * read_prefs);

typedef bool __cdecl (*Tmongoc_collection_command_simple)(void * collection, Pbson_t command, void * read_prefs, Pbson_t reply, Pbson_error_t error);

typedef __int64 __cdecl (*Tmongoc_collection_count)(void * collection, unsigned flags, Pbson_t query, __int64 skip, __int64 limit, void * read_prefs, Pbson_error_t error);

typedef __int64 __cdecl (*Tmongoc_collection_count_with_opts)(void * collection, unsigned flags, Pbson_t query, __int64 skip, __int64 limit, Pbson_t opts, void * read_prefs, Pbson_error_t error);

typedef bool __cdecl (*Tmongoc_collection_drop)(void * collection, Pbson_error_t error);

typedef bool __cdecl (*Tmongoc_collection_drop_index)(void * collection, char * index_name, Pbson_error_t error);

typedef bool __cdecl (*Tmongoc_collection_create_index)(void * collection, Pbson_t keys, Pmongoc_index_opt_t opt, Pbson_error_t error);

typedef void * __cdecl (*Tmongoc_collection_find_indexes)(void * collection, Pbson_error_t error);

typedef void * __cdecl (*Tmongoc_collection_find)(void * collection, unsigned flags, unsigned skip, unsigned limit, unsigned batch_size, Pbson_t query, Pbson_t fields, void * read_prefs);

typedef bool __cdecl (*Tmongoc_collection_insert)(void * collection, unsigned flags, Pbson_t document, void * write_concern, Pbson_error_t error);

typedef bool __cdecl (*Tmongoc_collection_update)(void * collection, unsigned flags, Pbson_t selector, Pbson_t update, void * write_concern, Pbson_error_t error);

typedef bool __cdecl (*Tmongoc_collection_save)(void * collection, Pbson_t document, void * write_concern, Pbson_error_t error);

typedef bool __cdecl (*Tmongoc_collection_remove)(void * collection, unsigned flags, Pbson_t selector, void * write_concern, Pbson_error_t error);

typedef bool __cdecl (*Tmongoc_collection_rename)(void * collection, char * new_db, char * new_name, bool drop_target_before_rename, Pbson_error_t error);

typedef bool __cdecl (*Tmongoc_collection_find_and_modify)(void * collection, Pbson_t query, Pbson_t sort, Pbson_t update, Pbson_t fields, bool _remove, bool upsert, bool _new, Pbson_t reply, Pbson_error_t error);

typedef bool __cdecl (*Tmongoc_collection_stats)(void * collection, Pbson_t options, Pbson_t reply, Pbson_error_t error);

typedef void * __cdecl (*Tmongoc_collection_create_bulk_operation)(void * collection, bool ordered, void * write_concern);

typedef void * __cdecl (*Tmongoc_collection_get_read_prefs)(void * collection);

typedef void __cdecl (*Tmongoc_collection_set_read_prefs)(void * collection, void * read_prefs);

typedef void * __cdecl (*Tmongoc_collection_get_write_concern)(void * collection);

typedef void __cdecl (*Tmongoc_collection_set_write_concern)(void * collection, void * write_concern);

typedef char * __cdecl (*Tmongoc_collection_get_name)(void * collection);

typedef Pbson_t __cdecl (*Tmongoc_collection_get_last_error)(void * collection);

typedef bool __cdecl (*Tmongoc_collection_validate)(void * collection, Pbson_t options, Pbson_t reply, Pbson_error_t error);

typedef void __cdecl (*Tmongoc_cursor_destroy)(void * cursor);

typedef bool __cdecl (*Tmongoc_cursor_more)(void * cursor);

typedef bool __cdecl (*Tmongoc_cursor_next)(void * cursor, PPbson_t bson);

typedef bool __cdecl (*Tmongoc_cursor_error)(void * cursor, Pbson_error_t error);

typedef Pbson_t __cdecl (*Tmongoc_cursor_current)(void * cursor);

typedef bool __cdecl (*Tmongoc_cursor_is_alive)(void * cursor);

typedef char * __cdecl (*Tmongoc_database_get_name)(void * database);

typedef bool __cdecl (*Tmongoc_database_remove_user)(void * database, char * username, Pbson_error_t error);

typedef bool __cdecl (*Tmongoc_database_remove_all_users)(void * database, Pbson_error_t error);

typedef bool __cdecl (*Tmongoc_database_add_user)(void * database, char * username, char * password, Pbson_t roles, Pbson_t custom_data, Pbson_error_t error);

typedef void __cdecl (*Tmongoc_database_destroy)(void * database);

typedef void * __cdecl (*Tmongoc_database_command)(void * database, unsigned flags, unsigned skip, unsigned limit, unsigned batch_size, Pbson_t command, Pbson_t fields, void * read_prefs);

typedef bool __cdecl (*Tmongoc_database_command_simple)(void * database, Pbson_t command, void * read_prefs, Pbson_t reply, Pbson_error_t error);

typedef bool __cdecl (*Tmongoc_database_drop)(void * database, Pbson_error_t error);

typedef bool __cdecl (*Tmongoc_database_has_collection)(void * database, char * name, Pbson_error_t error);

typedef void * __cdecl (*Tmongoc_database_create_collection)(void * database, char * name, Pbson_t options, Pbson_error_t error);

typedef void * __cdecl (*Tmongoc_database_get_read_prefs)(void * database);

typedef void __cdecl (*Tmongoc_database_set_read_prefs)(void * database, void * read_prefs);

typedef void * __cdecl (*Tmongoc_database_get_write_concern)(void * database);

typedef void __cdecl (*Tmongoc_database_set_write_concern)(void * database, void * write_concern);

typedef void * __cdecl (*Tmongoc_database_find_collections)(void * database, Pbson_t filter, Pbson_error_t error);

typedef void * __cdecl (*Tmongoc_database_get_collection)(void * database, char * name);

typedef mongoc_index_opt_t __cdecl (*Tmongoc_index_opt_get_default)(void);

typedef void __cdecl (*Tmongoc_index_opt_init)(Pmongoc_index_opt_t opt);

typedef void __cdecl (*Tmongoc_init)(void);

typedef void __cdecl (*Tmongoc_cleanup)(void);

typedef void __cdecl (*Tmongoc_log_set_handler)(Tmongoc_log_func_t log_func, void * user_data);

typedef void __cdecl (*Tmongoc_log_default_handler)(unsigned log_level, char * log_doman, char * message, void * user_data);

typedef char * __cdecl (*Tmongoc_log_level_str)(unsigned log_level);

typedef void * __cdecl (*Tmongoc_matcher_new)(Pbson_t query, Pbson_error_t error);

typedef bool __cdecl (*Tmongoc_matcher_match)(void * matcher, Pbson_t document);

typedef void __cdecl (*Tmongoc_matcher_destroy)(void * matcher);

typedef void * __cdecl (*Tmongoc_read_prefs_new)(unsigned read_mode);

typedef void __cdecl (*Tmongoc_read_prefs_destroy)(void * read_prefs);

typedef void * __cdecl (*Tmongoc_read_prefs_copy)(void * read_prefs);

typedef unsigned __cdecl (*Tmongoc_read_prefs_get_mode)(void * read_prefs);

typedef void __cdecl (*Tmongoc_read_prefs_set_mode)(void * read_prefs, unsigned mode);

typedef Pbson_t __cdecl (*Tmongoc_read_prefs_get_tags)(void * read_prefs);

typedef void __cdecl (*Tmongoc_read_prefs_set_tags)(void * read_prefs, Pbson_t tags);

typedef void __cdecl (*Tmongoc_read_prefs_add_tag)(void * read_prefs, Pbson_t tag);

typedef bool __cdecl (*Tmongoc_read_prefs_is_valid)(void * read_prefs);

typedef void * __cdecl (*Tmongoc_write_concern_new)(void);

typedef void __cdecl (*Tmongoc_write_concern_destroy)(void * write_concern);

typedef void * __cdecl (*Tmongoc_write_concern_copy)(void * write_concern);

typedef bool __cdecl (*Tmongoc_write_concern_get_fsync)(void * write_concern);

typedef void __cdecl (*Tmongoc_write_concern_set_fsync)(void * write_concern, bool fsync_);

typedef bool __cdecl (*Tmongoc_write_concern_get_journal)(void * write_concern);

typedef void __cdecl (*Tmongoc_write_concern_set_journal)(void * write_concern, bool journal);

typedef int __cdecl (*Tmongoc_write_concern_get_w)(void * write_concern);

typedef void __cdecl (*Tmongoc_write_concern_set_w)(void * write_concern, int w);

typedef char * __cdecl (*Tmongoc_write_concern_get_wtag)(void * write_concern);

typedef void __cdecl (*Tmongoc_write_concern_set_wtag)(void * write_concern, char * tag);

typedef int __cdecl (*Tmongoc_write_concern_get_wtimeout)(void * write_concern);

typedef void __cdecl (*Tmongoc_write_concern_set_wtimeout)(void * write_concern, int wtimeout_msec);

typedef int __cdecl (*Tmongoc_write_concern_get_wmajority)(void * write_concern);

typedef void __cdecl (*Tmongoc_write_concern_set_wmajority)(void * write_concern, int wtimeout_msec);

typedef void __cdecl (*Tbson_mem_set_vtable)(Pbson_mem_vtable_t vtable);

typedef void __cdecl (*Tbson_init)(Pbson_t bson);

typedef bool __cdecl (*Tbson_init_static)(Pbson_t bson, System::PByte data, NativeUInt len);

typedef Tbson_init Tbson_reinit;

typedef Pbson_t __cdecl (*Tbson_new)(void);

typedef void __cdecl (*Tbson_destroy)(Pbson_t bson);

typedef System::PByte __cdecl (*Tbson_get_data)(Pbson_t bson);

typedef bool __cdecl (*Tbson_init_from_json)(Pbson_t bson, char * data, NativeInt len, Pbson_error_t error);

typedef char * __cdecl (*Tbson_as_json)(Pbson_t bson, Firedac::Stan::Intf::PFDsize_t length);

typedef void __cdecl (*Tbson_copy_to)(Pbson_t src, Pbson_t dst);

typedef bool __cdecl (*Tbson_concat)(Pbson_t dst, Pbson_t src);

typedef bool __cdecl (*Tbson_append_array)(Pbson_t bson, char * key, int key_length, Pbson_t _array);

typedef bool __cdecl (*Tbson_append_document)(Pbson_t bson, char * key, int key_length, Pbson_t value);

typedef bool __cdecl (*Tbson_append_binary)(Pbson_t bson, char * key, int key_length, unsigned subtype, System::PByte binary, unsigned length);

typedef bool __cdecl (*Tbson_append_bool)(Pbson_t bson, char * key, int key_length, bool value);

typedef bool __cdecl (*Tbson_append_code)(Pbson_t bson, char * key, int key_length, char * javascript);

typedef bool __cdecl (*Tbson_append_code_with_scope)(Pbson_t bson, char * key, int key_length, char * javascript, Pbson_t scope);

typedef bool __cdecl (*Tbson_append_double)(Pbson_t bson, char * key, int key_length, double value);

typedef bool __cdecl (*Tbson_append_int32)(Pbson_t bson, char * key, int key_length, int value);

typedef bool __cdecl (*Tbson_append_int64)(Pbson_t bson, char * key, int key_length, __int64 value);

typedef bool __cdecl (*Tbson_append_null)(Pbson_t bson, char * key, int key_length);

typedef bool __cdecl (*Tbson_append_oid)(Pbson_t bson, char * key, int key_length, Pbson_oid_t oid);

typedef bool __cdecl (*Tbson_append_regex)(Pbson_t bson, char * key, int key_length, char * regex, char * options);

typedef bool __cdecl (*Tbson_append_utf8)(Pbson_t bson, char * key, int key_length, char * value, int length);

#ifndef __x86_64__
typedef bool __cdecl (*Tbson_append_time_t)(Pbson_t bson, char * key, int key_length, int value);
#else /* __x86_64__ */
typedef bool __cdecl (*Tbson_append_time_t)(Pbson_t bson, char * key, int key_length, long value);
#endif /* __x86_64__ */

typedef bool __cdecl (*Tbson_append_timeval)(Pbson_t bson, char * key, int key_length, Ptimeval value);

typedef bool __cdecl (*Tbson_append_date_time)(Pbson_t bson, char * key, int key_length, __int64 value);

typedef void * __cdecl (*Tbson_context_new)(unsigned flags);

typedef void __cdecl (*Tbson_context_destroy)(void * context);

typedef void * __cdecl (*Tbson_context_get_default)(void);

typedef int __cdecl (*Tbson_oid_compare)(Pbson_oid_t oid1, Pbson_oid_t oid2);

typedef void __cdecl (*Tbson_oid_copy)(Pbson_oid_t src, Pbson_oid_t dst);

typedef void __cdecl (*Tbson_oid_init)(Pbson_oid_t oid, void * context);

typedef void __cdecl (*Tbson_oid_init_from_string)(Pbson_oid_t oid, char * str);

typedef void __cdecl (*Tbson_oid_to_string)(Pbson_oid_t oid, char * str);

#ifndef __x86_64__
typedef int __cdecl (*Tbson_oid_get_time_t)(Pbson_oid_t oid);
#else /* __x86_64__ */
typedef long __cdecl (*Tbson_oid_get_time_t)(Pbson_oid_t oid);
#endif /* __x86_64__ */

typedef bool __cdecl (*Tbson_iter_init)(Pbson_iter_t iter, Pbson_t bson);

typedef bool __cdecl (*Tbson_iter_find)(Pbson_iter_t iter, char * key);

typedef bool __cdecl (*Tbson_iter_find_descendant)(Pbson_iter_t iter, char * dotkey, Pbson_iter_t descendant);

typedef bool __cdecl (*Tbson_iter_next)(Pbson_iter_t iter);

typedef bool __cdecl (*Tbson_iter_recurse)(Pbson_iter_t iter, Pbson_iter_t child);

typedef char * __cdecl (*Tbson_iter_key)(Pbson_iter_t iter);

typedef unsigned __cdecl (*Tbson_iter_type)(Pbson_iter_t iter);

typedef void __cdecl (*Tbson_iter_binary)(Pbson_iter_t iter, unsigned &subtype, unsigned &binary_len, System::PByte &binary);

typedef bool __cdecl (*Tbson_iter_bool)(Pbson_iter_t iter);

typedef char * __cdecl (*Tbson_iter_code)(Pbson_iter_t iter, int &length);

typedef double __cdecl (*Tbson_iter_double)(Pbson_iter_t iter);

typedef int __cdecl (*Tbson_iter_int32)(Pbson_iter_t iter);

typedef __int64 __cdecl (*Tbson_iter_int64)(Pbson_iter_t iter);

typedef Pbson_oid_t __cdecl (*Tbson_iter_oid)(Pbson_iter_t iter);

typedef char * __cdecl (*Tbson_iter_regex)(Pbson_iter_t iter, char * &options);

typedef char * __cdecl (*Tbson_iter_utf8)(Pbson_iter_t iter, unsigned &length);

#ifndef __x86_64__
typedef int __cdecl (*Tbson_iter_time_t)(Pbson_iter_t iter);
#else /* __x86_64__ */
typedef long __cdecl (*Tbson_iter_time_t)(Pbson_iter_t iter);
#endif /* __x86_64__ */

typedef __int64 __cdecl (*Tbson_iter_date_time)(Pbson_iter_t iter);

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 BSON_CONTEXT_NONE = System::Int8(0x0);
static const System::Int8 BSON_CONTEXT_THREAD_SAFE = System::Int8(0x1);
static const System::Int8 BSON_CONTEXT_DISABLE_HOST_CACHE = System::Int8(0x2);
static const System::Int8 BSON_CONTEXT_DISABLE_PID_CACHE = System::Int8(0x4);
static const System::Int8 BSON_CONTEXT_USE_TASK_ID = System::Int8(0x8);
static const System::Int8 BSON_TYPE_EOD = System::Int8(0x0);
static const System::Int8 BSON_TYPE_DOUBLE = System::Int8(0x1);
static const System::Int8 BSON_TYPE_UTF8 = System::Int8(0x2);
static const System::Int8 BSON_TYPE_DOCUMENT = System::Int8(0x3);
static const System::Int8 BSON_TYPE_ARRAY = System::Int8(0x4);
static const System::Int8 BSON_TYPE_BINARY = System::Int8(0x5);
static const System::Int8 BSON_TYPE_UNDEFINED = System::Int8(0x6);
static const System::Int8 BSON_TYPE_OID = System::Int8(0x7);
static const System::Int8 BSON_TYPE_BOOL = System::Int8(0x8);
static const System::Int8 BSON_TYPE_DATE_TIME = System::Int8(0x9);
static const System::Int8 BSON_TYPE_NULL = System::Int8(0xa);
static const System::Int8 BSON_TYPE_REGEX = System::Int8(0xb);
static const System::Int8 BSON_TYPE_DBPOINTER = System::Int8(0xc);
static const System::Int8 BSON_TYPE_CODE = System::Int8(0xd);
static const System::Int8 BSON_TYPE_SYMBOL = System::Int8(0xe);
static const System::Int8 BSON_TYPE_CODEWSCOPE = System::Int8(0xf);
static const System::Int8 BSON_TYPE_INT32 = System::Int8(0x10);
static const System::Int8 BSON_TYPE_TIMESTAMP = System::Int8(0x11);
static const System::Int8 BSON_TYPE_INT64 = System::Int8(0x12);
static const System::Int8 BSON_TYPE_MAXKEY = System::Int8(0x7f);
static const System::Byte BSON_TYPE_MINKEY = System::Byte(0xff);
static const System::Int8 BSON_SUBTYPE_BINARY = System::Int8(0x0);
static const System::Int8 BSON_SUBTYPE_FUNCTION = System::Int8(0x1);
static const System::Int8 BSON_SUBTYPE_BINARY_DEPRECATED = System::Int8(0x2);
static const System::Int8 BSON_SUBTYPE_UUID_DEPRECATED = System::Int8(0x3);
static const System::Int8 BSON_SUBTYPE_UUID = System::Int8(0x4);
static const System::Int8 BSON_SUBTYPE_MD5 = System::Int8(0x5);
static const System::Byte BSON_SUBTYPE_USER = System::Byte(0x80);
static const System::Int8 MONGOC_DELETE_NONE = System::Int8(0x0);
static const System::Int8 MONGOC_DELETE_SINGLE_REMOVE = System::Int8(0x1);
static const System::Int8 MONGOC_REMOVE_NONE = System::Int8(0x0);
static const System::Int8 MONGOC_REMOVE_SINGLE_REMOVE = System::Int8(0x1);
static const System::Int8 MONGOC_INSERT_NONE = System::Int8(0x0);
static const System::Int8 MONGOC_INSERT_CONTINUE_ON_ERROR = System::Int8(0x1);
static const unsigned MONGOC_INSERT_NO_VALIDATE = unsigned(0x80000000);
static const System::Int8 MONGOC_QUERY_NONE = System::Int8(0x0);
static const System::Int8 MONGOC_QUERY_TAILABLE_CURSOR = System::Int8(0x2);
static const System::Int8 MONGOC_QUERY_SLAVE_OK = System::Int8(0x4);
static const System::Int8 MONGOC_QUERY_OPLOG_REPLAY = System::Int8(0x8);
static const System::Int8 MONGOC_QUERY_NO_CURSOR_TIMEOUT = System::Int8(0x10);
static const System::Int8 MONGOC_QUERY_AWAIT_DATA = System::Int8(0x20);
static const System::Int8 MONGOC_QUERY_EXHAUST = System::Int8(0x40);
static const System::Byte MONGOC_QUERY_PARTIAL = System::Byte(0x80);
static const System::Int8 MONGOC_REPLY_NONE = System::Int8(0x0);
static const System::Int8 MONGOC_REPLY_CURSOR_NOT_FOUND = System::Int8(0x1);
static const System::Int8 MONGOC_REPLY_QUERY_FAILURE = System::Int8(0x2);
static const System::Int8 MONGOC_REPLY_SHARD_CONFIG_STALE = System::Int8(0x4);
static const System::Int8 MONGOC_REPLY_AWAIT_CAPABLE = System::Int8(0x8);
static const System::Int8 MONGOC_UPDATE_NONE = System::Int8(0x0);
static const System::Int8 MONGOC_UPDATE_UPSERT = System::Int8(0x1);
static const System::Int8 MONGOC_UPDATE_MULTI_UPDATE = System::Int8(0x2);
static const System::Int8 MONGOC_ERROR_CLIENT = System::Int8(0x1);
static const System::Int8 MONGOC_ERROR_STREAM = System::Int8(0x2);
static const System::Int8 MONGOC_ERROR_PROTOCOL = System::Int8(0x3);
static const System::Int8 MONGOC_ERROR_CURSOR = System::Int8(0x4);
static const System::Int8 MONGOC_ERROR_QUERY = System::Int8(0x5);
static const System::Int8 MONGOC_ERROR_INSERT = System::Int8(0x6);
static const System::Int8 MONGOC_ERROR_SASL = System::Int8(0x7);
static const System::Int8 MONGOC_ERROR_BSON = System::Int8(0x8);
static const System::Int8 MONGOC_ERROR_MATCHER = System::Int8(0x9);
static const System::Int8 MONGOC_ERROR_NAMESPACE = System::Int8(0xa);
static const System::Int8 MONGOC_ERROR_COMMAND = System::Int8(0xb);
static const System::Int8 MONGOC_ERROR_COLLECTION = System::Int8(0xc);
static const System::Int8 MONGOC_ERROR_GRIDFS = System::Int8(0xd);
static const System::Int8 MONGOC_ERROR_SCRAM = System::Int8(0xe);
static const System::Int8 MONGOC_ERROR_STREAM_INVALID_TYPE = System::Int8(0x1);
static const System::Int8 MONGOC_ERROR_STREAM_INVALID_STATE = System::Int8(0x2);
static const System::Int8 MONGOC_ERROR_STREAM_NAME_RESOLUTION = System::Int8(0x3);
static const System::Int8 MONGOC_ERROR_STREAM_SOCKET = System::Int8(0x4);
static const System::Int8 MONGOC_ERROR_STREAM_CONNECT = System::Int8(0x5);
static const System::Int8 MONGOC_ERROR_STREAM_NOT_ESTABLISHED = System::Int8(0x6);
static const System::Int8 MONGOC_ERROR_CLIENT_NOT_READY = System::Int8(0x7);
static const System::Int8 MONGOC_ERROR_CLIENT_TOO_BIG = System::Int8(0x8);
static const System::Int8 MONGOC_ERROR_CLIENT_TOO_SMALL = System::Int8(0x9);
static const System::Int8 MONGOC_ERROR_CLIENT_GETNONCE = System::Int8(0xa);
static const System::Int8 MONGOC_ERROR_CLIENT_AUTHENTICATE = System::Int8(0xb);
static const System::Int8 MONGOC_ERROR_CLIENT_NO_ACCEPTABLE_PEER = System::Int8(0xc);
static const System::Int8 MONGOC_ERROR_CLIENT_IN_EXHAUST = System::Int8(0xd);
static const System::Int8 MONGOC_ERROR_PROTOCOL_INVALID_REPLY = System::Int8(0xe);
static const System::Int8 MONGOC_ERROR_PROTOCOL_BAD_WIRE_VERSION = System::Int8(0xf);
static const System::Int8 MONGOC_ERROR_CURSOR_INVALID_CURSOR = System::Int8(0x10);
static const System::Int8 MONGOC_ERROR_QUERY_FAILURE = System::Int8(0x11);
static const System::Int8 MONGOC_ERROR_BSON_INVALID = System::Int8(0x12);
static const System::Int8 MONGOC_ERROR_MATCHER_INVALID = System::Int8(0x13);
static const System::Int8 MONGOC_ERROR_NAMESPACE_INVALID = System::Int8(0x14);
static const System::Int8 MONGOC_ERROR_NAMESPACE_INVALID_FILTER_TYPE = System::Int8(0x15);
static const System::Int8 MONGOC_ERROR_COMMAND_INVALID_ARG = System::Int8(0x16);
static const System::Int8 MONGOC_ERROR_COLLECTION_INSERT_FAILED = System::Int8(0x17);
static const System::Int8 MONGOC_ERROR_COLLECTION_DOES_NOT_EXIST = System::Int8(0x1a);
static const System::Int8 MONGOC_ERROR_GRIDFS_INVALID_FILENAME = System::Int8(0x1b);
static const System::Int8 MONGOC_ERROR_SCRAM_NOT_DONE = System::Int8(0x1c);
static const System::Int8 MONGOC_ERROR_SCRAM_PROTOCOL_ERROR = System::Int8(0x1d);
static const System::Int8 MONGOC_ERROR_QUERY_COMMAND_NOT_FOUND = System::Int8(0x3b);
static const System::Word MONGOC_ERROR_QUERY_NOT_TAILABLE = System::Word(0x32fb);
static const System::Int8 MONGOC_ERROR_PROTOCOL_ERROR = System::Int8(0x11);
static const System::Int8 MONGOC_LOG_LEVEL_ERROR = System::Int8(0x0);
static const System::Int8 MONGOC_LOG_LEVEL_CRITICAL = System::Int8(0x1);
static const System::Int8 MONGOC_LOG_LEVEL_WARNING = System::Int8(0x2);
static const System::Int8 MONGOC_LOG_LEVEL_MESSAGE = System::Int8(0x3);
static const System::Int8 MONGOC_LOG_LEVEL_INFO = System::Int8(0x4);
static const System::Int8 MONGOC_LOG_LEVEL_DEBUG = System::Int8(0x5);
static const System::Int8 MONGOC_LOG_LEVEL_TRACE = System::Int8(0x6);
static const System::Int8 MONGOC_READ_PRIMARY = System::Int8(0x1);
static const System::Int8 MONGOC_READ_SECONDARY = System::Int8(0x2);
static const System::Int8 MONGOC_READ_PRIMARY_PREFERRED = System::Int8(0x5);
static const System::Int8 MONGOC_READ_SECONDARY_PREFERRED = System::Int8(0x6);
static const System::Int8 MONGOC_READ_NEAREST = System::Int8(0xa);
static const System::Int8 MONGOC_WRITE_CONCERN_W_UNACKNOWLEDGED = System::Int8(0x0);
static const System::Int8 MONGOC_WRITE_CONCERN_W_ERRORS_IGNORED = System::Int8(-1);
static const System::Int8 MONGOC_WRITE_CONCERN_W_DEFAULT = System::Int8(-2);
static const System::Int8 MONGOC_WRITE_CONCERN_W_MAJORITY = System::Int8(-3);
static const System::Int8 MONGOC_WRITE_CONCERN_W_TAG = System::Int8(-4);
}	/* namespace Mongodbcli */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_MONGODBCLI)
using namespace Firedac::Phys::Mongodbcli;
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
#endif	// Firedac_Phys_MongodbcliHPP
