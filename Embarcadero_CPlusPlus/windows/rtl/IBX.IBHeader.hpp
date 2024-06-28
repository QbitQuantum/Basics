// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBHeader.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbheaderHPP
#define Ibx_IbheaderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <IBX.IBExternals.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibheader
{
//-- forward type declarations -----------------------------------------------
struct TISC_TIMESTAMP;
struct TGDS_QUAD;
struct TISC_ARRAY_BOUND;
struct TISC_ARRAY_DESC;
struct TISC_ARRAY_DESC_V2;
struct TISC_BLOB_DESC;
struct TISC_BLOB_DESC_V2;
struct TISC_DSC;
struct TISC_BLOB_CTL;
struct TBSTREAM;
struct TXSQLVAR_V1;
struct TXSQLVAR;
struct TXSQLDA_V1;
struct TXSQLDA;
struct TISC_START_TRANS;
struct TISC_TEB;
struct TUserSecData;
//-- type declarations -------------------------------------------------------
typedef Ibx::Ibexternals::PVoid TISC_ATT_HANDLE;

typedef Ibx::Ibexternals::PVoid *PISC_ATT_HANDLE;

typedef Ibx::Ibexternals::PVoid TISC_BLOB_HANDLE;

typedef Ibx::Ibexternals::PVoid *PISC_BLOB_HANDLE;

typedef Ibx::Ibexternals::PVoid TISC_DB_HANDLE;

typedef Ibx::Ibexternals::PVoid *PISC_DB_HANDLE;

typedef Ibx::Ibexternals::PVoid TISC_FORM_HANDLE;

typedef Ibx::Ibexternals::PVoid *PISC_FORM_HANDLE;

typedef Ibx::Ibexternals::PVoid TISC_REQ_HANDLE;

typedef Ibx::Ibexternals::PVoid *PISC_REQ_HANDLE;

typedef Ibx::Ibexternals::PVoid TISC_STMT_HANDLE;

typedef Ibx::Ibexternals::PVoid *PISC_STMT_HANDLE;

typedef Ibx::Ibexternals::PVoid TISC_SVC_HANDLE;

typedef Ibx::Ibexternals::PVoid *PISC_SVC_HANDLE;

typedef Ibx::Ibexternals::PVoid TISC_TR_HANDLE;

typedef Ibx::Ibexternals::PVoid *PISC_TR_HANDLE;

typedef Ibx::Ibexternals::PVoid TISC_WIN_HANDLE;

typedef Ibx::Ibexternals::PVoid *PISC_WIN_HANDLE;

typedef void __fastcall (*TISC_CALLBACK)(void);

typedef int ISC_SVC_HANDLE;

typedef int ISC_DATE;

typedef int *PISC_DATE;

typedef unsigned ISC_TIME;

typedef unsigned *PISC_TIME;

struct DECLSPEC_DRECORD TISC_TIMESTAMP
{
public:
	int timestamp_date;
	unsigned timestamp_time;
};


typedef TISC_TIMESTAMP *PISC_TIMESTAMP;

struct DECLSPEC_DRECORD TGDS_QUAD
{
public:
	int gds_quad_high;
	unsigned gds_quad_low;
};


typedef TGDS_QUAD TGDS__QUAD;

typedef TGDS_QUAD TISC_QUAD;

typedef TGDS_QUAD *PGDS_QUAD;

typedef TGDS_QUAD *PGDS__QUAD;

typedef TGDS_QUAD *PISC_QUAD;

struct DECLSPEC_DRECORD TISC_ARRAY_BOUND
{
public:
	short array_bound_lower;
	short array_bound_upper;
};


typedef TISC_ARRAY_BOUND *PISC_ARRAY_BOUND;

struct DECLSPEC_DRECORD TISC_ARRAY_DESC
{
public:
	System::Byte array_desc_dtype;
	System::Byte array_desc_scale;
	System::Word array_desc_length;
	System::StaticArray<System::Byte, 32> array_desc_field_name;
	System::StaticArray<System::Byte, 32> array_desc_relation_name;
	short array_desc_dimensions;
	short array_desc_flags;
	System::StaticArray<TISC_ARRAY_BOUND, 16> array_desc_bounds;
};


typedef TISC_ARRAY_DESC *PISC_ARRAY_DESC;

struct DECLSPEC_DRECORD TISC_ARRAY_DESC_V2
{
public:
	short array_desc_version;
	System::Byte array_desc_dtype;
	System::Byte array_desc_subtype;
	System::Byte array_desc_scale;
	System::Word array_desc_length;
	System::StaticArray<System::Byte, 68> array_desc_field_name;
	System::StaticArray<System::Byte, 68> array_desc_relation_name;
	short array_desc_dimensions;
	short array_desc_flags;
	System::StaticArray<TISC_ARRAY_BOUND, 16> array_desc_bounds;
};


typedef TISC_ARRAY_DESC_V2 *PISC_ARRAY_DESC_V2;

struct DECLSPEC_DRECORD TISC_BLOB_DESC
{
public:
	short blob_desc_subtype;
	short blob_desc_charset;
	short blob_desc_segment_size;
	System::StaticArray<System::Byte, 32> blob_desc_field_name;
	System::StaticArray<System::Byte, 32> blob_desc_relation_name;
};


typedef TISC_BLOB_DESC *PISC_BLOB_DESC;

struct DECLSPEC_DRECORD TISC_BLOB_DESC_V2
{
public:
	short blob_desc_version;
	short blob_desc_subtype;
	short blob_desc_charset;
	short blob_desc_segment_size;
	System::StaticArray<System::Byte, 68> blob_desc_field_name;
	System::StaticArray<System::Byte, 68> blob_desc_relation_name;
};


typedef TISC_BLOB_DESC_V2 *PISC_BLOB_DESC_V2;

struct DECLSPEC_DRECORD TISC_DSC
{
public:
	short dsc_version;
	short dsc_dtype;
	System::Byte dsc_scale;
	System::Byte dsc_precision;
	System::Word dsc_length;
	short dsc_sub_type;
	System::Word dsc_flags;
	short dsc_encryption;
	System::Byte *dsc_address;
};


typedef NativeInt __fastcall (*TISC_BLOB_CTL_SOURCE_FUNCTION)(void);

typedef TISC_BLOB_CTL *PISC_BLOB_CTL;

struct DECLSPEC_DRECORD TISC_BLOB_CTL
{
public:
	TISC_BLOB_CTL_SOURCE_FUNCTION ctl_source;
	TISC_BLOB_CTL *ctl_source_handle;
	short ctl_to_sub_type;
	short ctl_from_sub_type;
	System::Word ctl_buffer_length;
	System::Word ctl_segment_length;
	System::Word ctl_bpb_length;
	System::Byte *ctl_bpb;
	System::Byte *ctl_buffer;
	int ctl_max_segment;
	int ctl_number_segments;
	int ctl_total_length;
	NativeInt *ctl_status;
	System::StaticArray<NativeInt, 8> ctl_data;
};


struct DECLSPEC_DRECORD TBSTREAM
{
public:
	void * *bstr_blob;
	System::Byte *bstr_buffer;
	System::Byte *bstr_ptr;
	short bstr_length;
	short bstr_cnt;
	System::Byte bstr_mode;
};


typedef TBSTREAM *PBSTREAM;

struct DECLSPEC_DRECORD TXSQLVAR_V1
{
public:
	short sqltype;
	short sqlscale;
	short sqlsubtype;
	short sqllen;
	System::Byte *sqldata;
	short *sqlind;
	short sqlname_length;
	System::StaticArray<System::Byte, 32> sqlname;
	short relname_length;
	System::StaticArray<System::Byte, 32> relname;
	short ownname_length;
	System::StaticArray<System::Byte, 32> ownname;
	short aliasname_length;
	System::StaticArray<System::Byte, 32> aliasname;
};


typedef TXSQLVAR_V1 *PXSQLVAR_V1;

struct DECLSPEC_DRECORD TXSQLVAR
{
public:
	short sqltype;
	short sqlscale;
	short sqlprecision;
	short sqlsubtype;
	short sqllen;
	System::Byte *sqldata;
	short *sqlind;
	short sqlname_length;
	System::StaticArray<System::Byte, 68> sqlname;
	short relname_length;
	System::StaticArray<System::Byte, 68> relname;
	short ownname_length;
	System::StaticArray<System::Byte, 68> ownname;
	short aliasname_length;
	System::StaticArray<System::Byte, 68> aliasname;
};


typedef TXSQLVAR *PXSQLVAR;

typedef PXSQLVAR *PPXSQLVAR;

struct DECLSPEC_DRECORD TXSQLDA_V1
{
public:
	short version;
	System::StaticArray<System::Byte, 8> sqldaid;
	int sqldabc;
	short sqln;
	short sqld;
	System::StaticArray<TXSQLVAR_V1, 1> sqlvar;
};


typedef TXSQLDA_V1 *PXSQLDA_V1;

struct DECLSPEC_DRECORD TXSQLDA
{
public:
	short version;
	System::StaticArray<System::Byte, 8> sqldaid;
	int sqldabc;
	short sqln;
	short sqld;
	System::StaticArray<TXSQLVAR, 1> sqlvar;
};


typedef TXSQLDA *PXSQLDA;

struct DECLSPEC_DRECORD TISC_START_TRANS
{
public:
	Ibx::Ibexternals::PVoid *db_handle;
	System::Word tpb_length;
	System::Byte *tpb_address;
};


struct DECLSPEC_DRECORD TISC_TEB
{
public:
	Ibx::Ibexternals::PVoid *db_handle;
	int tpb_length;
	System::Byte *tpb_address;
};


typedef TISC_TEB *PISC_TEB;

typedef System::StaticArray<TISC_TEB, 1> TISC_TEB_ARRAY;

typedef TISC_TEB_ARRAY *PISC_TEB_ARRAY;

typedef NativeInt __stdcall (*Tisc_attach_database)(Ibx::Ibexternals::PISC_STATUS status_vector, short db_name_length, System::PByte db_name, PISC_DB_HANDLE db_handle, short parm_buffer_length, System::PByte parm_buffer);

typedef NativeInt __stdcall (*Tisc_array_gen_sdl)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_ARRAY_DESC isc_array_desc, Ibx::Ibexternals::PShort isc_arg3, System::PByte isc_arg4, Ibx::Ibexternals::PShort isc_arg5);

typedef NativeInt __stdcall (*Tisc_array_gen_sdl2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_ARRAY_DESC_V2 isc_array_desc, Ibx::Ibexternals::PShort isc_arg3, System::PByte isc_arg4, Ibx::Ibexternals::PShort isc_arg5);

typedef NativeInt __stdcall (*Tisc_array_get_slice)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE trans_handle, PISC_QUAD array_id, PISC_ARRAY_DESC descriptor, Ibx::Ibexternals::PVoid dest_array, Ibx::Ibexternals::PISC_LONG slice_length);

typedef NativeInt __stdcall (*Tisc_array_get_slice2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE trans_handle, PISC_QUAD array_id, PISC_ARRAY_DESC_V2 descriptor, Ibx::Ibexternals::PVoid dest_array, Ibx::Ibexternals::PISC_LONG slice_length);

typedef NativeInt __stdcall (*Tisc_array_lookup_bounds)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE trans_handle, System::PByte table_name, System::PByte column_name, PISC_ARRAY_DESC descriptor);

typedef NativeInt __stdcall (*Tisc_array_lookup_bounds2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE trans_handle, System::PByte table_name, System::PByte column_name, PISC_ARRAY_DESC_V2 descriptor);

typedef NativeInt __stdcall (*Tisc_array_lookup_desc)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE trans_handle, System::PByte table_name, System::PByte column_name, PISC_ARRAY_DESC descriptor);

typedef NativeInt __stdcall (*Tisc_array_lookup_desc2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE trans_handle, System::PByte table_name, System::PByte column_name, PISC_ARRAY_DESC_V2 descriptor);

typedef NativeInt __stdcall (*Tisc_array_set_desc)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte table_name, System::PByte column_name, Ibx::Ibexternals::PShort sql_dtype, Ibx::Ibexternals::PShort sql_length, Ibx::Ibexternals::PShort sql_dimensions, PISC_ARRAY_DESC descriptor);

typedef NativeInt __stdcall (*Tisc_array_set_desc2)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte table_name, System::PByte column_name, Ibx::Ibexternals::PShort sql_dtype, Ibx::Ibexternals::PShort sql_length, Ibx::Ibexternals::PShort sql_dimensions, PISC_ARRAY_DESC_V2 descriptor);

typedef NativeInt __stdcall (*Tisc_array_put_slice)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE trans_handle, PISC_QUAD array_id, PISC_ARRAY_DESC descriptor, Ibx::Ibexternals::PVoid source_array, Ibx::Ibexternals::PISC_LONG slice_length);

typedef NativeInt __stdcall (*Tisc_array_put_slice2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE trans_handle, PISC_QUAD array_id, PISC_ARRAY_DESC_V2 descriptor, Ibx::Ibexternals::PVoid source_array, Ibx::Ibexternals::PISC_LONG slice_length);

typedef void __stdcall (*Tisc_blob_default_desc)(PISC_BLOB_DESC descriptor, Ibx::Ibexternals::PUChar table_name, Ibx::Ibexternals::PUChar column_name);

typedef void __stdcall (*Tisc_blob_default_desc2)(PISC_BLOB_DESC_V2 descriptor, Ibx::Ibexternals::PUChar table_name, Ibx::Ibexternals::PUChar column_name);

typedef NativeInt __stdcall (*Tisc_blob_gen_bpb)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_BLOB_DESC to_descriptor, PISC_BLOB_DESC from_descriptor, System::Word bpb_buffer_length, Ibx::Ibexternals::PUChar bpb_buffer, Ibx::Ibexternals::PUShort bpb_length);

typedef NativeInt __stdcall (*Tisc_blob_gen_bpb2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_BLOB_DESC_V2 to_descriptor, PISC_BLOB_DESC_V2 from_descriptor, System::Word bpb_buffer_length, Ibx::Ibexternals::PUChar bpb_buffer, Ibx::Ibexternals::PUShort bpb_length);

typedef NativeInt __stdcall (*Tisc_blob_info)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_BLOB_HANDLE blob_handle, short item_list_buffer_length, System::PByte item_list_buffer, short result_buffer_length, System::PByte result_buffer);

typedef NativeInt __stdcall (*Tisc_blob_lookup_desc)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE trans_handle, System::PByte table_name, System::PByte column_name, PISC_BLOB_DESC descriptor, Ibx::Ibexternals::PUChar global);

typedef NativeInt __stdcall (*Tisc_blob_lookup_desc2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE trans_handle, System::PByte table_name, System::PByte column_name, PISC_BLOB_DESC_V2 descriptor, Ibx::Ibexternals::PUChar global);

typedef NativeInt __stdcall (*Tisc_blob_set_desc)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte table_name, System::PByte column_name, short subtype, short charset, short segment_size, PISC_BLOB_DESC descriptor);

typedef NativeInt __stdcall (*Tisc_blob_set_desc2)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte table_name, System::PByte column_name, short subtype, short charset, short segment_size, PISC_BLOB_DESC_V2 descriptor);

typedef NativeInt __stdcall (*Tisc_cancel_blob)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_BLOB_HANDLE blob_handle);

typedef NativeInt __stdcall (*Tisc_cancel_events)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, Ibx::Ibexternals::PISC_LONG event_id);

typedef NativeInt __stdcall (*Tisc_close_blob)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_BLOB_HANDLE blob_handle);

typedef NativeInt __stdcall (*Tisc_commit_retaining)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle);

typedef NativeInt __stdcall (*Tisc_commit_transaction)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle);

typedef NativeInt __stdcall (*Tisc_create_blob)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, PISC_BLOB_HANDLE blob_handle, PISC_QUAD blob_id);

typedef NativeInt __stdcall (*Tisc_create_blob2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, PISC_BLOB_HANDLE blob_handle, PISC_QUAD blob_id, short bpb_length, System::PByte bpb_address);

typedef NativeInt __stdcall (*Tisc_create_database)(Ibx::Ibexternals::PISC_STATUS status_vector, short db_name_length, System::PByte db_name, PISC_DB_HANDLE db_handle, short dpb_length, System::PByte dpb, short isc_arg7);

typedef NativeInt __stdcall (*Tisc_database_info)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, short item_list_buffer_length, System::PByte item_list_buffer, short result_buffer_length, System::PByte result_buffer);

typedef void __stdcall (*Tisc_decode_date)(PISC_QUAD ib_date, Ibx::Ibexternals::PCTimeStructure tm_date);

typedef void __stdcall (*Tisc_decode_sql_date)(PISC_DATE ib_date, Ibx::Ibexternals::PCTimeStructure tm_date);

typedef void __stdcall (*Tisc_decode_sql_time)(PISC_TIME ib_time, Ibx::Ibexternals::PCTimeStructure tm_date);

typedef void __stdcall (*Tisc_decode_timestamp)(PISC_TIMESTAMP ib_timestamp, Ibx::Ibexternals::PCTimeStructure tm_date);

typedef NativeInt __stdcall (*Tisc_detach_database)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle);

typedef NativeInt __stdcall (*Tisc_drop_database)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle);

typedef NativeInt __stdcall (*Tisc_dsql_allocate_statement)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_STMT_HANDLE stmt_handle);

typedef NativeInt __stdcall (*Tisc_dsql_alloc_statement2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_STMT_HANDLE stmt_handle);

typedef NativeInt __stdcall (*Tisc_dsql_describe)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_STMT_HANDLE stmt_handle, System::Word dialect, PXSQLDA xsqlda);

typedef NativeInt __stdcall (*Tisc_dsql_describe_bind)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_STMT_HANDLE stmt_handle, System::Word dialect, PXSQLDA xsqlda);

typedef NativeInt __stdcall (*Tisc_dsql_exec_immed2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, System::Word length, System::PByte statement, System::Word dialect, PXSQLDA in_xsqlda, PXSQLDA out_xsqlda);

typedef NativeInt __stdcall (*Tisc_dsql_execute)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, PISC_STMT_HANDLE stmt_handle, System::Word dialect, PXSQLDA xsqlda);

typedef NativeInt __stdcall (*Tisc_dsql_execute2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, PISC_STMT_HANDLE stmt_handle, System::Word dialect, PXSQLDA in_xsqlda, PXSQLDA out_xsqlda);

typedef NativeInt __stdcall (*Tisc_dsql_batch_execute_immed)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, System::Word Dialect, unsigned no_of_sql, Ibx::Ibexternals::PPByte statement, Ibx::Ibexternals::PULong rows_affected);

typedef NativeInt __stdcall (*Tisc_dsql_batch_exec_immed3_m)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, System::Word isc_var4, unsigned isc_var5, System::PByte isc_var6, System::Word isc_var7, System::PByte isc_var8);

typedef NativeInt __stdcall (*Tisc_dsql_batch_execute)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, PISC_STMT_HANDLE stmt_handle, System::Word Dialect, PXSQLDA insqlda, System::Word no_of_rows, PXSQLVAR batch_vars, Ibx::Ibexternals::PULong rows_affected);

typedef NativeInt __stdcall (*Tisc_dsql_execute_immediate)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, System::Word length, System::PByte statement, System::Word dialect, PXSQLDA xsqlda);

typedef NativeInt __stdcall (*Tisc_dsql_fetch)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_STMT_HANDLE stmt_handle, System::Word dialect, PXSQLDA xsqlda);

typedef NativeInt __stdcall (*Tisc_dsql_finish)(PISC_DB_HANDLE db_handle);

typedef NativeInt __stdcall (*Tisc_dsql_free_statement)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_STMT_HANDLE stmt_handle, System::Word options);

typedef NativeInt __stdcall (*Tisc_dsql_insert)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_STMT_HANDLE stmt_handle, System::Word arg3, PXSQLDA xsqlda);

typedef NativeInt __stdcall (*Tisc_dsql_prepare)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, PISC_STMT_HANDLE stmt_handle, System::Word length, System::PByte statement, System::Word dialect, PXSQLDA xsqlda);

typedef NativeInt __stdcall (*Tisc_dsql_set_cursor_name)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_STMT_HANDLE stmt_handle, System::PByte cursor_name, System::Word _type);

typedef NativeInt __stdcall (*Tisc_dsql_sql_info)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_STMT_HANDLE stmt_handle, short item_length, System::PByte items, short buffer_length, System::PByte buffer);

typedef void __stdcall (*Tisc_encode_date)(Ibx::Ibexternals::PCTimeStructure tm_date, PISC_QUAD ib_date);

typedef void __stdcall (*Tisc_encode_sql_date)(Ibx::Ibexternals::PCTimeStructure tm_date, PISC_DATE ib_date);

typedef void __stdcall (*Tisc_encode_sql_time)(Ibx::Ibexternals::PCTimeStructure tm_date, PISC_TIME ib_time);

typedef void __stdcall (*Tisc_encode_timestamp)(Ibx::Ibexternals::PCTimeStructure tm_date, PISC_TIMESTAMP ib_timestamp);

typedef int __cdecl (*Tisc_event_block)(System::PByte &event_buffer, System::PByte &result_buffer, System::Word id_count, System::PByte *event_list, const int event_list_High);

typedef void __stdcall (*Tisc_event_counts)(Ibx::Ibexternals::PUISC_LONG status_vector, short buffer_length, System::PByte event_buffer, System::PByte result_buffer);

typedef void __cdecl (*Tisc_expand_dpb)(Ibx::Ibexternals::PPByte dpb, Ibx::Ibexternals::PShort dpb_length, void * *item_list, const int item_list_High);

typedef int __stdcall (*Tisc_modify_dpb)(Ibx::Ibexternals::PPByte dpb, Ibx::Ibexternals::PShort isc_arg2, Ibx::Ibexternals::PShort isc_arg3, System::Word isc_arg4, System::PByte isc_arg5, short isc_arg6);

typedef int __stdcall (*Tisc_free)(System::PByte isc_arg1);

typedef NativeInt __stdcall (*Tisc_get_segment)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_BLOB_HANDLE blob_handle, Ibx::Ibexternals::PUShort actual_seg_length, System::Word seg_buffer_length, System::PByte seg_buffer);

typedef NativeInt __stdcall (*Tisc_get_slice)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, PISC_QUAD isc_arg4, short isc_arg5, System::PByte isc_arg6, short isc_arg7, Ibx::Ibexternals::PISC_LONG isc_arg8, int isc_arg9, Ibx::Ibexternals::PVoid isc_arg10, Ibx::Ibexternals::PISC_LONG isc_arg11);

typedef NativeInt __stdcall (*Tisc_interprete)(System::PByte buffer, Ibx::Ibexternals::PPISC_STATUS status_vector);

typedef NativeInt __stdcall (*Tisc_open_blob)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, PISC_BLOB_HANDLE blob_handle, PISC_QUAD blob_id);

typedef NativeInt __stdcall (*Tisc_open_blob2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, PISC_BLOB_HANDLE blob_handle, PISC_QUAD blob_id, short bpb_length, System::PByte bpb_buffer);

typedef NativeInt __stdcall (*Tisc_prepare_transaction2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, short msg_length, System::PByte msg);

typedef void __stdcall (*Tisc_print_sqlerror)(short sqlcode, Ibx::Ibexternals::PISC_STATUS status_vector);

typedef NativeInt __stdcall (*Tisc_print_status)(Ibx::Ibexternals::PISC_STATUS status_vector);

typedef NativeInt __stdcall (*Tisc_put_segment)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_BLOB_HANDLE blob_handle, System::Word seg_buffer_len, System::PByte seg_buffer);

typedef NativeInt __stdcall (*Tisc_put_slice)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, PISC_QUAD isc_arg4, short isc_arg5, System::PByte isc_arg6, short isc_arg7, Ibx::Ibexternals::PISC_LONG isc_arg8, int isc_arg9, Ibx::Ibexternals::PVoid isc_arg10);

typedef NativeInt __stdcall (*Tisc_que_events)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, Ibx::Ibexternals::PISC_LONG event_id, short length, System::PByte event_buffer, TISC_CALLBACK event_function, Ibx::Ibexternals::PVoid event_function_arg);

typedef NativeInt __stdcall (*Tisc_release_savepoint)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, System::PByte tran_name);

typedef NativeInt __stdcall (*Tisc_rollback_retaining)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle);

typedef NativeInt __stdcall (*Tisc_rollback_savepoint)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, System::PByte tran_name, System::Word Option);

typedef NativeInt __stdcall (*Tisc_rollback_transaction)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle);

typedef NativeInt __stdcall (*Tisc_start_multiple)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, short db_handle_count, PISC_TEB teb_vector_address);

typedef NativeInt __stdcall (*Tisc_start_savepoint)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, System::PByte tran_name);

typedef NativeInt __cdecl (*Tisc_start_transaction)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, short db_handle_count, PISC_DB_HANDLE db_handle, System::Word tpb_length, System::PByte tpb_address);

typedef int __stdcall (*Tisc_sqlcode)(Ibx::Ibexternals::PISC_STATUS status_vector);

typedef void __stdcall (*Tisc_sql_interprete)(short sqlcode, System::PByte buffer, short buffer_length);

typedef NativeInt __stdcall (*Tisc_transaction_info)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, short item_list_buffer_length, System::PByte item_list_buffer, short result_buffer_length, System::PByte result_buffer);

typedef NativeInt __stdcall (*Tisc_transact_request)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, System::Word isc_arg4, System::PByte isc_arg5, System::Word isc_arg6, System::PByte isc_arg7, System::Word isc_arg8, System::PByte isc_arg9);

typedef int __stdcall (*Tisc_vax_integer)(System::PByte buffer, short length);

typedef __int64 __stdcall (*Tisc_portable_integer)(System::PByte buffer, short length);

struct DECLSPEC_DRECORD TUserSecData
{
public:
	short sec_flags;
	int uid;
	int gid;
	int protocol;
	System::Byte *server;
	System::Byte *user_name;
	System::Byte *password;
	System::Byte *group_name;
	System::Byte *first_name;
	System::Byte *middle_name;
	System::Byte *last_name;
	System::Byte *dba_user_name;
	System::Byte *dba_password;
};


typedef TUserSecData *PUserSecData;

typedef NativeInt __stdcall (*Tisc_add_user)(Ibx::Ibexternals::PISC_STATUS status_vector, PUserSecData user_sec_data);

typedef NativeInt __stdcall (*Tisc_delete_user)(Ibx::Ibexternals::PISC_STATUS status_vector, PUserSecData user_sec_data);

typedef NativeInt __stdcall (*Tisc_modify_user)(Ibx::Ibexternals::PISC_STATUS status_vector, PUserSecData user_sec_data);

typedef NativeInt __stdcall (*Tisc_compile_request)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_REQ_HANDLE request_handle, short isc_arg4, System::PByte isc_arg5);

typedef NativeInt __stdcall (*Tisc_compile_request2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_REQ_HANDLE request_handle, short isc_arg4, System::PByte isc_arg5);

typedef NativeInt __stdcall (*Tisc_ddl)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, short isc_arg4, System::PByte isc_arg5);

typedef NativeInt __stdcall (*Tisc_prepare_transaction)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle);

typedef NativeInt __stdcall (*Tisc_receive)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_REQ_HANDLE request_handle, short isc_arg3, short isc_arg4, Ibx::Ibexternals::PVoid isc_arg5, short isc_arg6);

typedef NativeInt __stdcall (*Tisc_receive2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_REQ_HANDLE request_handle, short isc_arg3, short isc_arg4, Ibx::Ibexternals::PVoid isc_arg5, short isc_arg6, short isc_arg7, int isc_arg8);

typedef NativeInt __stdcall (*Tisc_reconnect_transaction)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, short isc_arg4, System::PByte isc_arg5);

typedef NativeInt __stdcall (*Tisc_release_request)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_REQ_HANDLE request_handle);

typedef NativeInt __stdcall (*Tisc_request_info)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_REQ_HANDLE request_handle, short isc_arg3, short isc_arg4, System::PByte isc_arg5, short isc_arg6, System::PByte isc_arg7);

typedef NativeInt __stdcall (*Tisc_seek_blob)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_BLOB_HANDLE blob_handle, short isc_arg3, int isc_arg4, Ibx::Ibexternals::PISC_LONG isc_arg5);

typedef NativeInt __stdcall (*Tisc_send)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_REQ_HANDLE request_handle, short isc_arg3, short isc_arg4, Ibx::Ibexternals::PVoid isc_arg5, short isc_arg6);

typedef NativeInt __stdcall (*Tisc_start_and_send)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_REQ_HANDLE request_handle, PISC_TR_HANDLE tran_handle, short isc_arg4, short isc_arg5, Ibx::Ibexternals::PVoid isc_arg6, short isc_arg7);

typedef NativeInt __stdcall (*Tisc_start_request)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_REQ_HANDLE request_handle, PISC_TR_HANDLE tran_handle, short isc_arg4);

typedef NativeInt __stdcall (*Tisc_unwind_request)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, short isc_arg3);

typedef NativeInt __stdcall (*Tisc_wait_for_event)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, short length, System::PByte event_buffer, System::PByte result_buffer);

typedef NativeInt __stdcall (*Tisc_close)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte isc_arg2);

typedef NativeInt __stdcall (*Tisc_declare)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte isc_arg2, System::PByte isc_arg3);

typedef NativeInt __stdcall (*Tisc_describe)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte isc_arg2, PXSQLDA isc_arg3);

typedef NativeInt __stdcall (*Tisc_describe_bind)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte isc_arg2, PXSQLDA isc_arg3);

typedef NativeInt __stdcall (*Tisc_execute)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, System::PByte isc_arg3, PXSQLDA isc_arg4);

typedef NativeInt __stdcall (*Tisc_execute_immediate)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, Ibx::Ibexternals::PShort isc_arg4, System::PByte isc_arg5);

typedef NativeInt __stdcall (*Tisc_fetch)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte isc_arg2, PXSQLDA isc_arg3);

typedef NativeInt __stdcall (*Tisc_open)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, System::PByte isc_arg3, PXSQLDA isc_arg4);

typedef NativeInt __stdcall (*Tisc_prepare)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, System::PByte isc_arg4, Ibx::Ibexternals::PShort isc_arg5, System::PByte isc_arg6, PXSQLDA isc_arg7);

typedef NativeInt __stdcall (*Tisc_dsql_execute_m)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, PISC_STMT_HANDLE statement_handle, System::Word isc_arg4, System::PByte isc_arg5, System::Word isc_arg6, System::Word isc_arg7, System::PByte isc_arg8);

typedef NativeInt __stdcall (*Tisc_dsql_execute2_m)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, PISC_STMT_HANDLE statement_handle, System::Word isc_arg4, System::PByte isc_arg5, System::Word isc_arg6, System::Word isc_arg7, System::PByte isc_arg8, System::Word isc_arg9, System::PByte isc_arg10, System::Word isc_arg11, System::Word isc_arg12, System::PByte isc_arg13);

typedef NativeInt __stdcall (*Tisc_dsql_batch_execute2_m)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, PISC_STMT_HANDLE statement_handle, System::Word isc_arg4, System::PByte isc_arg5, System::Word isc_arg6, System::Word isc_arg7, System::PByte isc_arg8, System::Word isc_arg9, System::PByte isc_arg10);

typedef NativeInt __stdcall (*Tisc_dsql_execute_immediate_m)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, System::Word isc_arg4, System::PByte isc_arg5, System::Word isc_arg6, System::Word isc_arg7, System::PByte isc_arg8, System::Word isc_arg9, System::Word isc_arg10, System::PByte isc_arg11);

typedef NativeInt __stdcall (*Tisc_dsql_exec_immed3_m)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, System::Word isc_arg4, System::PByte isc_arg5, System::Word isc_arg6, System::Word isc_arg7, System::PByte isc_arg8, System::Word isc_arg9, System::Word isc_arg10, System::PByte isc_arg11, System::Word isc_arg12, System::PByte isc_arg13, System::Word isc_arg14, System::Word isc_arg15, System::PByte isc_arg16);

typedef NativeInt __stdcall (*Tisc_dsql_fetch_m)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_STMT_HANDLE statement_handle, System::Word isc_arg3, System::PByte isc_arg4, System::Word isc_arg5, System::Word isc_arg6, System::PByte isc_arg7);

typedef NativeInt __stdcall (*Tisc_dsql_insert_m)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_STMT_HANDLE statement_handle, System::Word isc_arg3, System::PByte isc_arg4, System::Word isc_arg5, System::Word isc_arg6, System::PByte isc_arg7);

typedef NativeInt __stdcall (*Tisc_dsql_prepare_m)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, PISC_STMT_HANDLE statement_handle, System::Word isc_arg4, System::PByte isc_arg5, System::Word isc_arg6, System::Word isc_arg7, System::PByte isc_arg8, System::Word isc_arg9, System::PByte isc_arg10);

typedef NativeInt __stdcall (*Tisc_dsql_release)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte isc_arg2);

typedef NativeInt __stdcall (*Tisc_embed_dsql_close)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte isc_arg2);

typedef NativeInt __stdcall (*Tisc_embed_dsql_declare)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte isc_arg2, System::PByte isc_arg3);

typedef NativeInt __stdcall (*Tisc_embed_dsql_describe)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte isc_arg2, System::Word isc_arg3, PXSQLDA isc_arg4);

typedef NativeInt __stdcall (*Tisc_embed_dsql_describe_bind)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte isc_arg2, System::Word isc_arg3, PXSQLDA isc_arg4);

typedef NativeInt __stdcall (*Tisc_embed_dsql_execute)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, System::PByte isc_arg3, System::Word isc_arg4, PXSQLDA isc_arg5);

typedef NativeInt __stdcall (*Tisc_embed_dsql_execute2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, System::PByte isc_arg3, System::Word isc_arg4, PXSQLDA isc_arg5, PXSQLDA isc_arg6);

typedef NativeInt __stdcall (*Tisc_embed_dsql_execute_immed)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, System::Word isc_arg4, System::PByte isc_arg5, System::Word isc_arg6, PXSQLDA isc_arg7);

typedef NativeInt __stdcall (*Tisc_embed_dsql_fetch)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte isc_arg2, System::Word isc_arg3, PXSQLDA isc_arg4);

typedef NativeInt __stdcall (*Tisc_embed_dsql_open)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, System::PByte isc_arg3, System::Word isc_arg4, PXSQLDA isc_arg5);

typedef NativeInt __stdcall (*Tisc_embed_dsql_open2)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_TR_HANDLE tran_handle, System::PByte isc_arg3, System::Word isc_arg4, PXSQLDA isc_arg5, PXSQLDA isc_arg6);

typedef NativeInt __stdcall (*Tisc_embed_dsql_insert)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte isc_arg2, System::Word isc_arg3, PXSQLDA isc_arg4);

typedef NativeInt __stdcall (*Tisc_embed_dsql_prepare)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, System::PByte isc_arg4, System::Word isc_arg5, System::PByte isc_arg6, System::Word isc_arg7, PXSQLDA isc_arg8);

typedef NativeInt __stdcall (*Tisc_embed_dsql_release)(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte isc_arg2);

typedef PBSTREAM __stdcall (*TBLOB_open)(Ibx::Ibexternals::PVoid blob_handle, System::PByte isc_arg2, int isc_arg3);

typedef int __stdcall (*TBLOB_put)(System::Byte isc_arg1, PBSTREAM isc_arg2);

typedef int __stdcall (*TBLOB_close)(PBSTREAM isc_arg1);

typedef int __stdcall (*TBLOB_get)(PBSTREAM isc_arg1);

typedef int __stdcall (*TBLOB_display)(PISC_QUAD isc_arg1, Ibx::Ibexternals::PVoid db_handle, Ibx::Ibexternals::PVoid tran_handle, System::PByte isc_arg4);

typedef int __stdcall (*TBLOB_dump)(PISC_QUAD isc_arg1, Ibx::Ibexternals::PVoid db_handle, Ibx::Ibexternals::PVoid tran_handle, System::PByte isc_arg4);

typedef int __stdcall (*TBLOB_edit)(PISC_QUAD isc_arg1, Ibx::Ibexternals::PVoid db_handle, Ibx::Ibexternals::PVoid tran_handle, System::PByte isc_arg4);

typedef int __stdcall (*TBLOB_load)(PISC_QUAD isc_arg1, Ibx::Ibexternals::PVoid db_handle, Ibx::Ibexternals::PVoid tran_handle, System::PByte isc_arg4);

typedef int __stdcall (*TBLOB_text_dump)(PISC_QUAD isc_arg1, Ibx::Ibexternals::PVoid db_handle, Ibx::Ibexternals::PVoid tran_handle, System::PByte isc_arg4);

typedef int __stdcall (*TBLOB_text_load)(PISC_QUAD isc_arg1, Ibx::Ibexternals::PVoid db_handle, Ibx::Ibexternals::PVoid tran_handle, System::PByte isc_arg4);

typedef int __stdcall (*TBopen)(PISC_QUAD isc_arg1, Ibx::Ibexternals::PVoid db_handle, Ibx::Ibexternals::PVoid tran_handle, System::PByte isc_arg4);

typedef PBSTREAM __stdcall (*TBopen2)(PISC_QUAD isc_arg1, Ibx::Ibexternals::PVoid db_handle, Ibx::Ibexternals::PVoid tran_handle, System::PByte isc_arg4, System::Word isc_arg5);

typedef int __stdcall (*Tisc_ftof)(System::PByte isc_arg1, System::Word isc_arg2, System::PByte isc_arg3, System::Word isc_arg4);

typedef NativeInt __stdcall (*Tisc_print_blr)(System::PByte isc_arg1, TISC_CALLBACK isc_arg2, Ibx::Ibexternals::PVoid isc_arg3, short isc_arg4);

typedef void __stdcall (*Tisc_set_debug)(int isc_arg1);

typedef void __stdcall (*Tisc_qtoq)(PISC_QUAD isc_arg1, PISC_QUAD isc_arg2);

typedef void __stdcall (*Tisc_vtof)(System::PByte isc_arg1, System::PByte isc_arg2, System::Word isc_arg3);

typedef void __stdcall (*Tisc_vtov)(System::PByte isc_arg1, System::PByte isc_arg2, short isc_arg3);

typedef int __stdcall (*Tisc_version)(PISC_DB_HANDLE db_handle, TISC_CALLBACK isc_arg2, Ibx::Ibexternals::PVoid isc_arg3);

typedef int __stdcall (*Tisc_reset_fpe)(System::Word isc_arg1);

typedef NativeInt __stdcall (*Tisc_service_attach)(Ibx::Ibexternals::PISC_STATUS status_vector, System::Word isc_arg2, System::PByte isc_arg3, PISC_SVC_HANDLE service_handle, System::Word isc_arg5, System::PByte isc_arg6);

typedef NativeInt __stdcall (*Tisc_service_detach)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_SVC_HANDLE service_handle);

typedef NativeInt __stdcall (*Tisc_service_query)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_SVC_HANDLE service_handle, PISC_SVC_HANDLE recv_handle, System::Word isc_arg4, System::PByte isc_arg5, System::Word isc_arg6, System::PByte isc_arg7, System::Word isc_arg8, System::PByte isc_arg9);

typedef NativeInt __stdcall (*Tisc_service_start)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_SVC_HANDLE service_handle, PISC_SVC_HANDLE recv_handle, System::Word isc_arg4, System::PByte isc_arg5);

typedef void __stdcall (*Tisc_get_client_version)(System::PByte buffer);

typedef int __stdcall (*Tisc_get_client_major_version)(void);

typedef int __stdcall (*Tisc_get_client_minor_version)(void);

typedef NativeInt __stdcall (*Tisc_compile_map)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_FORM_HANDLE form_handle, PISC_REQ_HANDLE request_handle, Ibx::Ibexternals::PShort isc_arg4, System::PByte isc_arg5);

typedef NativeInt __stdcall (*Tisc_compile_menu)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_FORM_HANDLE form_handle, PISC_REQ_HANDLE request_handle, Ibx::Ibexternals::PShort isc_arg4, System::PByte isc_arg5);

typedef NativeInt __stdcall (*Tisc_compile_sub_map)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_WIN_HANDLE win_handle, PISC_REQ_HANDLE request_handle, Ibx::Ibexternals::PShort isc_arg4, System::PByte isc_arg5);

typedef NativeInt __stdcall (*Tisc_create_window)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_WIN_HANDLE win_handle, Ibx::Ibexternals::PShort isc_arg3, System::PByte isc_arg4, Ibx::Ibexternals::PShort isc_arg5, Ibx::Ibexternals::PShort isc_arg6);

typedef NativeInt __stdcall (*Tisc_delete_window)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_WIN_HANDLE win_handle);

typedef NativeInt __stdcall (*Tisc_drive_form)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, PISC_WIN_HANDLE win_handle, PISC_REQ_HANDLE request_handle, Ibx::Ibexternals::PUChar isc_arg6, Ibx::Ibexternals::PUChar isc_arg7);

typedef NativeInt __stdcall (*Tisc_drive_menu)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_WIN_HANDLE win_handle, PISC_REQ_HANDLE request_handle, Ibx::Ibexternals::PShort isc_arg4, System::PByte isc_arg5, Ibx::Ibexternals::PShort isc_arg6, System::PByte isc_arg7, Ibx::Ibexternals::PShort isc_arg8, Ibx::Ibexternals::PShort isc_arg9, System::PByte isc_arg10, Ibx::Ibexternals::PISC_LONG isc_arg11);

typedef NativeInt __stdcall (*Tisc_form_delete)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_FORM_HANDLE form_handle);

typedef NativeInt __stdcall (*Tisc_form_fetch)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, PISC_REQ_HANDLE request_handle, Ibx::Ibexternals::PUChar isc_arg5);

typedef NativeInt __stdcall (*Tisc_form_insert)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, PISC_REQ_HANDLE request_handle, Ibx::Ibexternals::PUChar isc_arg5);

typedef NativeInt __stdcall (*Tisc_get_entree)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_REQ_HANDLE request_handle, Ibx::Ibexternals::PShort isc_arg3, System::PByte isc_arg4, Ibx::Ibexternals::PISC_LONG isc_arg5, Ibx::Ibexternals::PShort isc_arg6);

typedef NativeInt __stdcall (*Tisc_initialize_menu)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_REQ_HANDLE request_handle);

typedef NativeInt __stdcall (*Tisc_menu)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_WIN_HANDLE win_handle, PISC_REQ_HANDLE request_handle, Ibx::Ibexternals::PShort isc_arg4, System::PByte isc_arg5);

typedef NativeInt __stdcall (*Tisc_load_form)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_DB_HANDLE db_handle, PISC_TR_HANDLE tran_handle, PISC_FORM_HANDLE form_handle, Ibx::Ibexternals::PShort isc_arg5, System::PByte isc_arg6);

typedef NativeInt __stdcall (*Tisc_pop_window)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_WIN_HANDLE win_handle);

typedef NativeInt __stdcall (*Tisc_put_entree)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_REQ_HANDLE request_handle, Ibx::Ibexternals::PShort isc_arg3, System::PByte isc_arg4, Ibx::Ibexternals::PISC_LONG isc_arg5);

typedef NativeInt __stdcall (*Tisc_reset_form)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_REQ_HANDLE request_handle);

typedef NativeInt __stdcall (*Tisc_suspend_window)(Ibx::Ibexternals::PISC_STATUS status_vector, PISC_WIN_HANDLE win_handle);

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 ISC_TRUE = System::Int8(0x1);
static const System::Int8 ISC_FALSE = System::Int8(0x0);
static const System::Int8 DSQL_close = System::Int8(0x1);
static const System::Int8 DSQL_drop = System::Int8(0x2);
static const System::Int8 DSQL_cancel = System::Int8(0x4);
static const System::Int8 METADATALENGTH = System::Int8(0x44);
#ifndef _WIN64
#define IBASE_DLL L"gds32.dll"
#define IBTOGO_DLL L"ibtogo.dll"
#define IBXML_DLL L"ibxml.dll"
#else /* _WIN64 */
#define IBASE_DLL L"ibclient64.dll"
#define IBTOGO_DLL L"ibtogo64.dll"
#define IBXML_DLL L"ibxml64.dll"
#endif /* _WIN64 */
static const System::Int8 SQLDA_VERSION1 = System::Int8(0x1);
static const System::Int8 SQLDA_VERSION2 = System::Int8(0x2);
static const System::Int8 SQLDA_CURRENT_VERSION = System::Int8(0x2);
static const System::Int8 SQL_DIALECT_V5 = System::Int8(0x1);
static const System::Int8 SQL_DIALECT_V6_TRANSITION = System::Int8(0x2);
static const System::Int8 SQL_DIALECT_V6 = System::Int8(0x3);
static const System::Int8 SQL_DIALECT_CURRENT = System::Int8(0x3);
static const System::Word SQLIND_NULL = System::Word(0x8000);
static const System::Int8 SQLIND_INSERT = System::Int8(0x1);
static const System::Int8 SQLIND_UPDATE = System::Int8(0x2);
static const System::Int8 SQLIND_DELETE = System::Int8(0x4);
static const System::Int8 SQLIND_CHANGE = System::Int8(0x8);
static const System::Int8 SQLIND_TRUNCATE = System::Int8(0x10);
static const System::Int8 SQLIND_CHANGE_VIEW = System::Int8(0x20);
static const System::Word TIME_SECONDS_PRECISION = System::Word(0x2710);
static const System::Int8 TIME_SECONDS_PRECISION_SCALE = System::Int8(-4);
static const System::Int8 ARR_DESC_VERSION2 = System::Int8(0x2);
static const System::Int8 ARR_DESC_CURRENT_VERSION = System::Int8(0x2);
static const System::Int8 BLB_DESC_VERSION2 = System::Int8(0x2);
static const System::Int8 BLB_DESC_CURRENT_VERSION = System::Int8(0x2);
static const System::Int8 DSC_VERSION2 = System::Int8(0x2);
static const System::Int8 DSC_CURRENT_VERSION = System::Int8(0x2);
static const System::Int8 DSC_VERSION1_TO_CURRENT = System::Int8(0x0);
static const System::Int8 DSC_CURRENT_TO_VERSION1 = System::Int8(0x1);
static const System::Int8 DSC_null = System::Int8(0x1);
static const System::Int8 DSC_no_subtype = System::Int8(0x2);
static const System::Int8 DSC_nullable = System::Int8(0x4);
static const System::Int8 DSC_system = System::Int8(0x8);
static const System::Int8 sec_uid_spec = System::Int8(0x1);
static const System::Int8 sec_gid_spec = System::Int8(0x2);
static const System::Int8 sec_server_spec = System::Int8(0x4);
static const System::Int8 sec_password_spec = System::Int8(0x8);
static const System::Int8 sec_group_name_spec = System::Int8(0x10);
static const System::Int8 sec_first_name_spec = System::Int8(0x20);
static const System::Int8 sec_middle_name_spec = System::Int8(0x40);
static const System::Byte sec_last_name_spec = System::Byte(0x80);
static const System::Word sec_dba_user_name_spec = System::Word(0x100);
static const System::Word sec_dba_password_spec = System::Word(0x200);
static const System::Int8 sec_protocol_tcpip = System::Int8(0x1);
static const System::Int8 sec_protocol_netbeui = System::Int8(0x2);
static const System::Int8 sec_protocol_spx = System::Int8(0x3);
static const System::Int8 sec_protocol_local = System::Int8(0x4);
static const System::Int8 isc_blob_filter_open = System::Int8(0x0);
static const System::Int8 isc_blob_filter_get_segment = System::Int8(0x1);
static const System::Int8 isc_blob_filter_close = System::Int8(0x2);
static const System::Int8 isc_blob_filter_create = System::Int8(0x3);
static const System::Int8 isc_blob_filter_put_segment = System::Int8(0x4);
static const System::Int8 isc_blob_filter_alloc = System::Int8(0x5);
static const System::Int8 isc_blob_filter_free = System::Int8(0x6);
static const System::Int8 isc_blob_filter_seek = System::Int8(0x7);
static const System::Int8 blr_text = System::Int8(0xe);
static const System::Int8 blr_text2 = System::Int8(0xf);
static const System::Int8 blr_short = System::Int8(0x7);
static const System::Int8 blr_long = System::Int8(0x8);
static const System::Int8 blr_quad = System::Int8(0x9);
static const System::Int8 blr_float = System::Int8(0xa);
static const System::Int8 blr_double = System::Int8(0x1b);
static const System::Int8 blr_d_float = System::Int8(0xb);
static const System::Int8 blr_timestamp = System::Int8(0x23);
static const System::Int8 blr_varying = System::Int8(0x25);
static const System::Int8 blr_varying2 = System::Int8(0x26);
static const System::Word blr_blob = System::Word(0x105);
static const System::Int8 blr_cstring = System::Int8(0x28);
static const System::Int8 blr_cstring2 = System::Int8(0x29);
static const System::Int8 blr_blob_id = System::Int8(0x2d);
static const System::Int8 blr_sql_date = System::Int8(0xc);
static const System::Int8 blr_sql_time = System::Int8(0xd);
static const System::Int8 blr_int64 = System::Int8(0x10);
static const System::Int8 blr_boolean_dtype = System::Int8(0x11);
static const System::Int8 blr_date = System::Int8(0x23);
static const System::Int8 blr_inner = System::Int8(0x0);
static const System::Int8 blr_left = System::Int8(0x1);
static const System::Int8 blr_right = System::Int8(0x2);
static const System::Int8 blr_full = System::Int8(0x3);
static const System::Int8 blr_gds_code = System::Int8(0x0);
static const System::Int8 blr_sql_code = System::Int8(0x1);
static const System::Int8 blr_exception = System::Int8(0x2);
static const System::Int8 blr_trigger_code = System::Int8(0x3);
static const System::Int8 blr_default_code = System::Int8(0x4);
static const System::Int8 blr_immediate = System::Int8(0x0);
static const System::Int8 blr_deferred = System::Int8(0x1);
static const System::Int8 blr_restrict = System::Int8(0x0);
static const System::Int8 blr_cascade = System::Int8(0x1);
static const System::Int8 blr_version4 = System::Int8(0x4);
static const System::Int8 blr_version5 = System::Int8(0x5);
static const System::Int8 blr_eoc = System::Int8(0x4c);
static const System::Int8 blr_end = System::Int8(-1);
static const System::Int8 blr_assignment = System::Int8(0x1);
static const System::Int8 blr_begin = System::Int8(0x2);
static const System::Int8 blr_dcl_variable = System::Int8(0x3);
static const System::Int8 blr_message = System::Int8(0x4);
static const System::Int8 blr_erase = System::Int8(0x5);
static const System::Int8 blr_fetch = System::Int8(0x6);
static const System::Int8 blr_for = System::Int8(0x7);
static const System::Int8 blr_if = System::Int8(0x8);
static const System::Int8 blr_loop = System::Int8(0x9);
static const System::Int8 blr_modify = System::Int8(0xa);
static const System::Int8 blr_handler = System::Int8(0xb);
static const System::Int8 blr_receive = System::Int8(0xc);
static const System::Int8 blr_select = System::Int8(0xd);
static const System::Int8 blr_send = System::Int8(0xe);
static const System::Int8 blr_store = System::Int8(0xf);
static const System::Int8 blr_truncate = System::Int8(0x10);
static const System::Int8 blr_label = System::Int8(0x11);
static const System::Int8 blr_leave = System::Int8(0x12);
static const System::Int8 blr_store2 = System::Int8(0x13);
static const System::Int8 blr_post = System::Int8(0x14);
static const System::Int8 blr_literal = System::Int8(0x15);
static const System::Int8 blr_dbkey = System::Int8(0x16);
static const System::Int8 blr_field = System::Int8(0x17);
static const System::Int8 blr_fid = System::Int8(0x18);
static const System::Int8 blr_parameter = System::Int8(0x19);
static const System::Int8 blr_variable = System::Int8(0x1a);
static const System::Int8 blr_average = System::Int8(0x1b);
static const System::Int8 blr_count = System::Int8(0x1c);
static const System::Int8 blr_maximum = System::Int8(0x1d);
static const System::Int8 blr_minimum = System::Int8(0x1e);
static const System::Int8 blr_total = System::Int8(0x1f);
static const System::Int8 blr_add = System::Int8(0x22);
static const System::Int8 blr_subtract = System::Int8(0x23);
static const System::Int8 blr_multiply = System::Int8(0x24);
static const System::Int8 blr_divide = System::Int8(0x25);
static const System::Int8 blr_negate = System::Int8(0x26);
static const System::Int8 blr_concatenate = System::Int8(0x27);
static const System::Int8 blr_substring = System::Int8(0x28);
static const System::Int8 blr_parameter2 = System::Int8(0x29);
static const System::Int8 blr_from = System::Int8(0x2a);
static const System::Int8 blr_via = System::Int8(0x2b);
static const System::Int8 blr_user_name = System::Int8(0x2c);
static const System::Int8 blr_null = System::Int8(0x2d);
static const System::Int8 blr_eql = System::Int8(0x2f);
static const System::Int8 blr_neq = System::Int8(0x30);
static const System::Int8 blr_gtr = System::Int8(0x31);
static const System::Int8 blr_geq = System::Int8(0x32);
static const System::Int8 blr_lss = System::Int8(0x33);
static const System::Int8 blr_leq = System::Int8(0x34);
static const System::Int8 blr_containing = System::Int8(0x35);
static const System::Int8 blr_matching = System::Int8(0x36);
static const System::Int8 blr_starting = System::Int8(0x37);
static const System::Int8 blr_between = System::Int8(0x38);
static const System::Int8 blr_or = System::Int8(0x39);
static const System::Int8 blr_and = System::Int8(0x3a);
static const System::Int8 blr_not = System::Int8(0x3b);
static const System::Int8 blr_any = System::Int8(0x3c);
static const System::Int8 blr_missing = System::Int8(0x3d);
static const System::Int8 blr_unique = System::Int8(0x3e);
static const System::Int8 blr_like = System::Int8(0x3f);
static const System::Int8 blr_with = System::Int8(0x40);
static const System::Int8 blr_stream = System::Int8(0x41);
static const System::Int8 blr_set_index = System::Int8(0x42);
static const System::Int8 blr_rse = System::Int8(0x43);
static const System::Int8 blr_first = System::Int8(0x44);
static const System::Int8 blr_project = System::Int8(0x45);
static const System::Int8 blr_sort = System::Int8(0x46);
static const System::Int8 blr_boolean = System::Int8(0x47);
static const System::Int8 blr_ascending = System::Int8(0x48);
static const System::Int8 blr_descending = System::Int8(0x49);
static const System::Int8 blr_relation = System::Int8(0x4a);
static const System::Int8 blr_rid = System::Int8(0x4b);
static const System::Int8 blr_union = System::Int8(0x4c);
static const System::Int8 blr_map = System::Int8(0x4d);
static const System::Int8 blr_group_by = System::Int8(0x4e);
static const System::Int8 blr_aggregate = System::Int8(0x4f);
static const System::Int8 blr_join_type = System::Int8(0x50);
static const System::Int8 blr_rows = System::Int8(0x51);
static const System::Int8 blr_derived_relation = System::Int8(0x52);
static const System::Int8 blr_ties = System::Int8(0x0);
static const System::Int8 blr_percent = System::Int8(0x1);
static const System::Int8 blr_agg_count = System::Int8(0x53);
static const System::Int8 blr_agg_max = System::Int8(0x54);
static const System::Int8 blr_agg_min = System::Int8(0x55);
static const System::Int8 blr_agg_total = System::Int8(0x56);
static const System::Int8 blr_agg_average = System::Int8(0x57);
static const System::Int8 blr_parameter3 = System::Int8(0x58);
static const System::Int8 blr_run_count = System::Int8(0x76);
static const System::Int8 blr_run_max = System::Int8(0x59);
static const System::Int8 blr_run_min = System::Int8(0x5a);
static const System::Int8 blr_run_total = System::Int8(0x5b);
static const System::Int8 blr_run_average = System::Int8(0x5c);
static const System::Int8 blr_agg_count2 = System::Int8(0x5d);
static const System::Int8 blr_agg_count_distinct = System::Int8(0x5e);
static const System::Int8 blr_agg_total_distinct = System::Int8(0x5f);
static const System::Int8 blr_agg_average_distinct = System::Int8(0x60);
static const System::Int8 blr_function = System::Int8(0x64);
static const System::Int8 blr_gen_id = System::Int8(0x65);
static const System::Int8 blr_prot_mask = System::Int8(0x66);
static const System::Int8 blr_upcase = System::Int8(0x67);
static const System::Int8 blr_lock_state = System::Int8(0x68);
static const System::Int8 blr_value_if = System::Int8(0x69);
static const System::Int8 blr_matching2 = System::Int8(0x6a);
static const System::Int8 blr_index = System::Int8(0x6b);
static const System::Int8 blr_ansi_like = System::Int8(0x6c);
static const System::Int8 blr_bookmark = System::Int8(0x6d);
static const System::Int8 blr_crack = System::Int8(0x6e);
static const System::Int8 blr_force_crack = System::Int8(0x6f);
static const System::Int8 blr_seek = System::Int8(0x70);
static const System::Int8 blr_find = System::Int8(0x71);
static const System::Int8 blr_continue = System::Int8(0x0);
static const System::Int8 blr_forward = System::Int8(0x1);
static const System::Int8 blr_backward = System::Int8(0x2);
static const System::Int8 blr_bof_forward = System::Int8(0x3);
static const System::Int8 blr_eof_backward = System::Int8(0x4);
static const System::Int8 blr_lock_relation = System::Int8(0x72);
static const System::Int8 blr_lock_record = System::Int8(0x73);
static const System::Int8 blr_set_bookmark = System::Int8(0x74);
static const System::Int8 blr_get_bookmark = System::Int8(0x75);
static const System::Int8 blr_rs_stream = System::Int8(0x77);
static const System::Int8 blr_exec_proc = System::Int8(0x78);
static const System::Int8 blr_begin_range = System::Int8(0x79);
static const System::Int8 blr_end_range = System::Int8(0x7a);
static const System::Int8 blr_delete_range = System::Int8(0x7b);
static const System::Int8 blr_procedure = System::Int8(0x7c);
static const System::Int8 blr_pid = System::Int8(0x7d);
static const System::Int8 blr_exec_pid = System::Int8(0x7e);
static const System::Int8 blr_singular = System::Int8(0x7f);
static const System::Byte blr_abort = System::Byte(0x80);
static const System::Byte blr_block = System::Byte(0x81);
static const System::Byte blr_error_handler = System::Byte(0x82);
static const System::Byte blr_cast = System::Byte(0x83);
static const System::Byte blr_release_lock = System::Byte(0x84);
static const System::Byte blr_release_locks = System::Byte(0x85);
static const System::Byte blr_start_savepoint = System::Byte(0x86);
static const System::Byte blr_end_savepoint = System::Byte(0x87);
static const System::Byte blr_find_dbkey = System::Byte(0x88);
static const System::Byte blr_range_relation = System::Byte(0x89);
static const System::Byte blr_delete_ranges = System::Byte(0x8a);
static const System::Byte blr_plan = System::Byte(0x8b);
static const System::Byte blr_merge = System::Byte(0x8c);
static const System::Byte blr_join = System::Byte(0x8d);
static const System::Byte blr_sequential = System::Byte(0x8e);
static const System::Byte blr_navigational = System::Byte(0x8f);
static const System::Byte blr_indices = System::Byte(0x90);
static const System::Byte blr_retrieve = System::Byte(0x91);
static const System::Byte blr_relation2 = System::Byte(0x92);
static const System::Byte blr_rid2 = System::Byte(0x93);
static const System::Byte blr_reset_stream = System::Byte(0x94);
static const System::Byte blr_release_bookmark = System::Byte(0x95);
static const System::Byte blr_set_generator = System::Byte(0x96);
static const System::Byte blr_ansi_any = System::Byte(0x97);
static const System::Byte blr_exists = System::Byte(0x98);
static const System::Byte blr_cardinality = System::Byte(0x99);
static const System::Byte blr_record_version = System::Byte(0x9a);
static const System::Byte blr_stall = System::Byte(0x9b);
static const System::Byte blr_seek_no_warn = System::Byte(0x9c);
static const System::Byte blr_find_dbkey_version = System::Byte(0x9d);
static const System::Byte blr_ansi_all = System::Byte(0x9e);
static const System::Byte blr_extract = System::Byte(0x9f);
static const System::Int8 blr_extract_year = System::Int8(0x0);
static const System::Int8 blr_extract_month = System::Int8(0x1);
static const System::Int8 blr_extract_day = System::Int8(0x2);
static const System::Int8 blr_extract_hour = System::Int8(0x3);
static const System::Int8 blr_extract_minute = System::Int8(0x4);
static const System::Int8 blr_extract_second = System::Int8(0x5);
static const System::Int8 blr_extract_weekday = System::Int8(0x6);
static const System::Int8 blr_extract_yearday = System::Int8(0x7);
static const System::Byte blr_current_date = System::Byte(0xa0);
static const System::Byte blr_current_timestamp = System::Byte(0xa1);
static const System::Byte blr_current_time = System::Byte(0xa2);
static const System::Byte blr_add2 = System::Byte(0xa3);
static const System::Byte blr_subtract2 = System::Byte(0xa4);
static const System::Byte blr_multiply2 = System::Byte(0xa5);
static const System::Byte blr_divide2 = System::Byte(0xa6);
static const System::Byte blr_agg_total2 = System::Byte(0xa7);
static const System::Byte blr_agg_total_distinct2 = System::Byte(0xa8);
static const System::Byte blr_agg_average2 = System::Byte(0xa9);
static const System::Byte blr_agg_average_distinct2 = System::Byte(0xaa);
static const System::Byte blr_average2 = System::Byte(0xab);
static const System::Byte blr_gen_id2 = System::Byte(0xac);
static const System::Byte blr_set_generator2 = System::Byte(0xad);
static const System::Byte blr_boolean_true = System::Byte(0xae);
static const System::Byte blr_boolean_false = System::Byte(0xaf);
static const System::Byte blr_start_savepoint2 = System::Byte(0xb0);
static const System::Byte blr_release_savepoint = System::Byte(0xb1);
static const System::Byte blr_rollback_savepoint = System::Byte(0xb2);
static const System::Byte blr_exec_stmt = System::Byte(0xb3);
static const System::Byte blr_exec_stmt2 = System::Byte(0xb4);
static const System::Int8 isc_dpb_version1 = System::Int8(0x1);
static const System::Int8 isc_dpb_cdd_pathname = System::Int8(0x1);
static const System::Int8 isc_dpb_allocation = System::Int8(0x2);
static const System::Int8 isc_dpb_journal = System::Int8(0x3);
static const System::Int8 isc_dpb_page_size = System::Int8(0x4);
static const System::Int8 isc_dpb_num_buffers = System::Int8(0x5);
static const System::Int8 isc_dpb_buffer_length = System::Int8(0x6);
static const System::Int8 isc_dpb_debug = System::Int8(0x7);
static const System::Int8 isc_dpb_garbage_collect = System::Int8(0x8);
static const System::Int8 isc_dpb_verify = System::Int8(0x9);
static const System::Int8 isc_dpb_sweep = System::Int8(0xa);
static const System::Int8 isc_dpb_enable_journal = System::Int8(0xb);
static const System::Int8 isc_dpb_disable_journal = System::Int8(0xc);
static const System::Int8 isc_dpb_dbkey_scope = System::Int8(0xd);
static const System::Int8 isc_dpb_number_of_users = System::Int8(0xe);
static const System::Int8 isc_dpb_trace = System::Int8(0xf);
static const System::Int8 isc_dpb_no_garbage_collect = System::Int8(0x10);
static const System::Int8 isc_dpb_damaged = System::Int8(0x11);
static const System::Int8 isc_dpb_license = System::Int8(0x12);
static const System::Int8 isc_dpb_sys_user_name = System::Int8(0x13);
static const System::Int8 isc_dpb_encrypt_key = System::Int8(0x14);
static const System::Int8 isc_dpb_activate_shadow = System::Int8(0x15);
static const System::Int8 isc_dpb_sweep_interval = System::Int8(0x16);
static const System::Int8 isc_dpb_delete_shadow = System::Int8(0x17);
static const System::Int8 isc_dpb_force_write = System::Int8(0x18);
static const System::Int8 isc_dpb_begin_log = System::Int8(0x19);
static const System::Int8 isc_dpb_quit_log = System::Int8(0x1a);
static const System::Int8 isc_dpb_no_reserve = System::Int8(0x1b);
static const System::Int8 isc_dpb_user_name = System::Int8(0x1c);
static const System::Int8 isc_dpb_password = System::Int8(0x1d);
static const System::Int8 isc_dpb_password_enc = System::Int8(0x1e);
static const System::Int8 isc_dpb_sys_user_name_enc = System::Int8(0x1f);
static const System::Int8 isc_dpb_interp = System::Int8(0x20);
static const System::Int8 isc_dpb_online_dump = System::Int8(0x21);
static const System::Int8 isc_dpb_old_file_size = System::Int8(0x22);
static const System::Int8 isc_dpb_old_num_files = System::Int8(0x23);
static const System::Int8 isc_dpb_old_file_name = System::Int8(0x24);
static const System::Int8 isc_dpb_old_start_page = System::Int8(0x25);
static const System::Int8 isc_dpb_old_start_seqno = System::Int8(0x26);
static const System::Int8 isc_dpb_old_start_file = System::Int8(0x27);
static const System::Int8 isc_dpb_drop_walfile = System::Int8(0x28);
static const System::Int8 isc_dpb_old_dump_id = System::Int8(0x29);
static const System::Int8 isc_dpb_wal_backup_dir = System::Int8(0x2a);
static const System::Int8 isc_dpb_wal_chkptlen = System::Int8(0x2b);
static const System::Int8 isc_dpb_wal_numbufs = System::Int8(0x2c);
static const System::Int8 isc_dpb_wal_bufsize = System::Int8(0x2d);
static const System::Int8 isc_dpb_wal_grp_cmt_wait = System::Int8(0x2e);
static const System::Int8 isc_dpb_lc_messages = System::Int8(0x2f);
static const System::Int8 isc_dpb_lc_ctype = System::Int8(0x30);
static const System::Int8 isc_dpb_cache_manager = System::Int8(0x31);
static const System::Int8 isc_dpb_shutdown = System::Int8(0x32);
static const System::Int8 isc_dpb_online = System::Int8(0x33);
static const System::Int8 isc_dpb_shutdown_delay = System::Int8(0x34);
static const System::Int8 isc_dpb_reserved = System::Int8(0x35);
static const System::Int8 isc_dpb_overwrite = System::Int8(0x36);
static const System::Int8 isc_dpb_sec_attach = System::Int8(0x37);
static const System::Int8 isc_dpb_disable_wal = System::Int8(0x38);
static const System::Int8 isc_dpb_connect_timeout = System::Int8(0x39);
static const System::Int8 isc_dpb_dummy_packet_interval = System::Int8(0x3a);
static const System::Int8 isc_dpb_gbak_attach = System::Int8(0x3b);
static const System::Int8 isc_dpb_sql_role_name = System::Int8(0x3c);
static const System::Int8 isc_dpb_set_page_buffers = System::Int8(0x3d);
static const System::Int8 isc_dpb_working_directory = System::Int8(0x3e);
static const System::Int8 isc_dpb_SQL_dialect = System::Int8(0x3f);
static const System::Int8 isc_dpb_set_db_readonly = System::Int8(0x40);
static const System::Int8 isc_dpb_set_db_SQL_dialect = System::Int8(0x41);
static const System::Int8 isc_dpb_gfix_attach = System::Int8(0x42);
static const System::Int8 isc_dpb_gstat_attach = System::Int8(0x43);
static const System::Int8 isc_dpb_gbak_ods_version = System::Int8(0x44);
static const System::Int8 isc_dpb_gbak_ods_minor_version = System::Int8(0x45);
static const System::Int8 isc_dpb_set_group_commit = System::Int8(0x46);
static const System::Int8 isc_dpb_gbak_validate = System::Int8(0x47);
static const System::Int8 isc_dpb_client_interbase_var = System::Int8(0x48);
static const System::Int8 isc_dpb_admin_option = System::Int8(0x49);
static const System::Int8 isc_dpb_flush_interval = System::Int8(0x4a);
static const System::Int8 isc_dpb_instance_name = System::Int8(0x4b);
static const System::Int8 isc_dpb_old_overwrite = System::Int8(0x4c);
static const System::Int8 isc_dpb_archive_database = System::Int8(0x4d);
static const System::Int8 isc_dpb_archive_journals = System::Int8(0x4e);
static const System::Int8 isc_dpb_archive_sweep = System::Int8(0x4f);
static const System::Int8 isc_dpb_archive_dumps = System::Int8(0x50);
static const System::Int8 isc_dpb_archive_recover = System::Int8(0x51);
static const System::Int8 isc_dpb_recover_until = System::Int8(0x52);
static const System::Int8 isc_dpb_force = System::Int8(0x53);
static const System::Int8 isc_dpb_preallocate = System::Int8(0x54);
static const System::Int8 isc_dpb_sys_encrypt_password = System::Int8(0x55);
static const System::Int8 isc_dpb_eua_user_name = System::Int8(0x56);
static const System::Int8 isc_dpb_transaction = System::Int8(0x57);
static const System::Int8 isc_dpb_ods_version_major = System::Int8(0x58);
static const System::Int8 isc_dpb_old_tablespace_name = System::Int8(0x59);
static const System::Int8 isc_dpb_last_dpb_constant = System::Int8(0x59);
static const System::Int8 isc_dpb_pages = System::Int8(0x1);
static const System::Int8 isc_dpb_records = System::Int8(0x2);
static const System::Int8 isc_dpb_indices = System::Int8(0x4);
static const System::Int8 isc_dpb_transactions = System::Int8(0x8);
static const System::Int8 isc_dpb_no_update = System::Int8(0x10);
static const System::Int8 isc_dpb_repair = System::Int8(0x20);
static const System::Int8 isc_dpb_ignore = System::Int8(0x40);
static const System::Int8 isc_dpb_shut_cache = System::Int8(0x1);
static const System::Int8 isc_dpb_shut_attachment = System::Int8(0x2);
static const System::Int8 isc_dpb_shut_transaction = System::Int8(0x4);
static const System::Int8 isc_dpb_shut_force = System::Int8(0x8);
static const System::Int8 RDB_system = System::Int8(0x1);
static const System::Int8 RDB_id_assigned = System::Int8(0x2);
static const System::Int8 isc_tpb_version1 = System::Int8(0x1);
static const System::Int8 isc_tpb_version3 = System::Int8(0x3);
static const System::Int8 isc_tpb_consistency = System::Int8(0x1);
static const System::Int8 isc_tpb_concurrency = System::Int8(0x2);
static const System::Int8 isc_tpb_shared = System::Int8(0x3);
static const System::Int8 isc_tpb_protected = System::Int8(0x4);
static const System::Int8 isc_tpb_exclusive = System::Int8(0x5);
static const System::Int8 isc_tpb_wait = System::Int8(0x6);
static const System::Int8 isc_tpb_nowait = System::Int8(0x7);
static const System::Int8 isc_tpb_read = System::Int8(0x8);
static const System::Int8 isc_tpb_write = System::Int8(0x9);
static const System::Int8 isc_tpb_lock_read = System::Int8(0xa);
static const System::Int8 isc_tpb_lock_write = System::Int8(0xb);
static const System::Int8 isc_tpb_verb_time = System::Int8(0xc);
static const System::Int8 isc_tpb_commit_time = System::Int8(0xd);
static const System::Int8 isc_tpb_ignore_limbo = System::Int8(0xe);
static const System::Int8 isc_tpb_read_committed = System::Int8(0xf);
static const System::Int8 isc_tpb_autocommit = System::Int8(0x10);
static const System::Int8 isc_tpb_rec_version = System::Int8(0x11);
static const System::Int8 isc_tpb_no_rec_version = System::Int8(0x12);
static const System::Int8 isc_tpb_restart_requests = System::Int8(0x13);
static const System::Int8 isc_tpb_no_auto_undo = System::Int8(0x14);
static const System::Int8 isc_tpb_no_savepoint = System::Int8(0x15);
static const System::Int8 isc_tpb_exclusivity = System::Int8(0x16);
static const System::Int8 isc_tpb_wait_time = System::Int8(0x17);
static const System::Int8 isc_tpb_last_tpb_constant = System::Int8(0x17);
static const System::Int8 isc_bpb_version1 = System::Int8(0x1);
static const System::Int8 isc_bpb_source_type = System::Int8(0x1);
static const System::Int8 isc_bpb_target_type = System::Int8(0x2);
static const System::Int8 isc_bpb_type = System::Int8(0x3);
static const System::Int8 isc_bpb_source_interp = System::Int8(0x4);
static const System::Int8 isc_bpb_target_interp = System::Int8(0x5);
static const System::Int8 isc_bpb_filter_parameter = System::Int8(0x6);
static const System::Int8 isc_bpb_target_relation_name = System::Int8(0x7);
static const System::Int8 isc_bpb_target_field_name = System::Int8(0x8);
static const System::Int8 isc_bpb_type_segmented = System::Int8(0x0);
static const System::Int8 isc_bpb_type_stream = System::Int8(0x1);
static const System::Int8 isc_spb_version1 = System::Int8(0x1);
static const System::Int8 isc_spb_current_version = System::Int8(0x2);
static const System::Int8 isc_spb_version = System::Int8(0x2);
static const System::Int8 isc_spb_last_spb_constant = System::Int8(0xf);
static const System::Int8 isc_spb_user_name = System::Int8(0x1c);
static const System::Int8 isc_spb_sys_user_name = System::Int8(0x13);
static const System::Int8 isc_spb_sys_user_name_enc = System::Int8(0x1f);
static const System::Int8 isc_spb_password = System::Int8(0x1d);
static const System::Int8 isc_spb_password_enc = System::Int8(0x1e);
static const System::Int8 isc_spb_sys_encrypt_password = System::Int8(0x55);
static const System::Int8 isc_spb_command_line = System::Int8(0x69);
static const System::Int8 isc_spb_dbname = System::Int8(0x6a);
static const System::Int8 isc_spb_verbose = System::Int8(0x6b);
static const System::Int8 isc_spb_options = System::Int8(0x6c);
static const System::Int8 isc_spb_user_dbname = System::Int8(0x6d);
static const System::Int8 isc_spb_auth_dbname = System::Int8(0x6e);
static const System::Int8 isc_spb_connect_timeout = System::Int8(0x39);
static const System::Int8 isc_spb_dummy_packet_interval = System::Int8(0x3a);
static const System::Int8 isc_spb_sql_role_name = System::Int8(0x3c);
static const System::Int8 isc_spb_instance_name = System::Int8(0x4b);
static const System::Int8 isc_info_end = System::Int8(0x1);
static const System::Int8 isc_info_truncated = System::Int8(0x2);
static const System::Int8 isc_info_error = System::Int8(0x3);
static const System::Int8 isc_info_data_not_ready = System::Int8(0x4);
static const System::Int8 isc_info_flag_end = System::Int8(0x7f);
static const System::Int8 isc_info_db_id = System::Int8(0x4);
static const System::Int8 isc_info_reads = System::Int8(0x5);
static const System::Int8 isc_info_writes = System::Int8(0x6);
static const System::Int8 isc_info_fetches = System::Int8(0x7);
static const System::Int8 isc_info_marks = System::Int8(0x8);
static const System::Int8 isc_info_implementation = System::Int8(0xb);
static const System::Int8 isc_info_version = System::Int8(0xc);
static const System::Int8 isc_info_base_level = System::Int8(0xd);
static const System::Int8 isc_info_svr_maj_ver = System::Int8(0xd);
static const System::Int8 isc_info_page_size = System::Int8(0xe);
static const System::Int8 isc_info_num_buffers = System::Int8(0xf);
static const System::Int8 isc_info_limbo = System::Int8(0x10);
static const System::Int8 isc_info_current_memory = System::Int8(0x11);
static const System::Int8 isc_info_max_memory = System::Int8(0x12);
static const System::Int8 isc_info_window_turns = System::Int8(0x13);
static const System::Int8 isc_info_license = System::Int8(0x14);
static const System::Int8 isc_info_allocation = System::Int8(0x15);
static const System::Int8 isc_info_attachment_id = System::Int8(0x16);
static const System::Int8 isc_info_read_seq_count = System::Int8(0x17);
static const System::Int8 isc_info_read_idx_count = System::Int8(0x18);
static const System::Int8 isc_info_insert_count = System::Int8(0x19);
static const System::Int8 isc_info_update_count = System::Int8(0x1a);
static const System::Int8 isc_info_delete_count = System::Int8(0x1b);
static const System::Int8 isc_info_backout_count = System::Int8(0x1c);
static const System::Int8 isc_info_purge_count = System::Int8(0x1d);
static const System::Int8 isc_info_expunge_count = System::Int8(0x1e);
static const System::Int8 isc_info_sweep_interval = System::Int8(0x1f);
static const System::Int8 isc_info_ods_version = System::Int8(0x20);
static const System::Int8 isc_info_ods_minor_version = System::Int8(0x21);
static const System::Int8 isc_info_no_reserve = System::Int8(0x22);
static const System::Int8 isc_info_logfile = System::Int8(0x23);
static const System::Int8 isc_info_cur_logfile_name = System::Int8(0x24);
static const System::Int8 isc_info_cur_log_part_offset = System::Int8(0x25);
static const System::Int8 isc_info_num_wal_buffers = System::Int8(0x26);
static const System::Int8 isc_info_wal_buffer_size = System::Int8(0x27);
static const System::Int8 isc_info_wal_ckpt_length = System::Int8(0x28);
static const System::Int8 isc_info_wal_cur_ckpt_length = System::Int8(0x29);
static const System::Int8 isc_info_wal_prv_ckpt_fname = System::Int8(0x2a);
static const System::Int8 isc_info_wal_prv_ckpt_poffset = System::Int8(0x2b);
static const System::Int8 isc_info_wal_recv_ckpt_fname = System::Int8(0x2c);
static const System::Int8 isc_info_wal_recv_ckpt_poffset = System::Int8(0x2d);
static const System::Int8 isc_info_wal_ckpt_interval = System::Int8(0x2f);
static const System::Int8 isc_info_wal_num_io = System::Int8(0x30);
static const System::Int8 isc_info_wal_avg_io_size = System::Int8(0x31);
static const System::Int8 isc_info_wal_num_commits = System::Int8(0x32);
static const System::Int8 isc_info_wal_avg_grpc_size = System::Int8(0x33);
static const System::Int8 isc_info_forced_writes = System::Int8(0x34);
static const System::Int8 isc_info_user_names = System::Int8(0x35);
static const System::Int8 isc_info_page_errors = System::Int8(0x36);
static const System::Int8 isc_info_record_errors = System::Int8(0x37);
static const System::Int8 isc_info_bpage_errors = System::Int8(0x38);
static const System::Int8 isc_info_dpage_errors = System::Int8(0x39);
static const System::Int8 isc_info_ipage_errors = System::Int8(0x3a);
static const System::Int8 isc_info_ppage_errors = System::Int8(0x3b);
static const System::Int8 isc_info_tpage_errors = System::Int8(0x3c);
static const System::Int8 isc_info_set_page_buffers = System::Int8(0x3d);
static const System::Int8 isc_info_db_SQL_dialect = System::Int8(0x3e);
static const System::Int8 isc_info_db_read_only = System::Int8(0x3f);
static const System::Int8 isc_info_db_size_in_pages = System::Int8(0x40);
static const System::Int8 isc_info_db_reads = System::Int8(0x41);
static const System::Int8 isc_info_db_writes = System::Int8(0x42);
static const System::Int8 isc_info_db_fetches = System::Int8(0x43);
static const System::Int8 isc_info_db_marks = System::Int8(0x44);
static const System::Int8 isc_info_db_group_commit = System::Int8(0x45);
static const System::Int8 isc_info_att_charset = System::Int8(0x46);
static const System::Int8 isc_info_svr_min_ver = System::Int8(0x47);
static const System::Int8 isc_info_ib_env_var = System::Int8(0x48);
static const System::Int8 isc_info_server_tcp_port = System::Int8(0x49);
static const System::Int8 isc_info_db_preallocate = System::Int8(0x4a);
static const System::Int8 isc_info_db_encrypted = System::Int8(0x4b);
static const System::Int8 isc_info_db_encryptions = System::Int8(0x4c);
static const System::Int8 isc_info_db_sep_external = System::Int8(0x4d);
static const System::Int8 isc_info_db_eua_active = System::Int8(0x4e);
static const System::Int8 isc_info_db_creation_timestamp = System::Int8(0x4f);
static const System::Int8 isc_info_db_impl_rdb_vms = System::Int8(0x1);
static const System::Int8 isc_info_db_impl_rdb_eln = System::Int8(0x2);
static const System::Int8 isc_info_db_impl_rdb_eln_dev = System::Int8(0x3);
static const System::Int8 isc_info_db_impl_rdb_vms_y = System::Int8(0x4);
static const System::Int8 isc_info_db_impl_rdb_eln_y = System::Int8(0x5);
static const System::Int8 isc_info_db_impl_jri = System::Int8(0x6);
static const System::Int8 isc_info_db_impl_jsv = System::Int8(0x7);
static const System::Int8 isc_info_db_impl_isc_a = System::Int8(0x19);
static const System::Int8 isc_info_db_impl_isc_u = System::Int8(0x1a);
static const System::Int8 isc_info_db_impl_isc_v = System::Int8(0x1b);
static const System::Int8 isc_info_db_impl_isc_s = System::Int8(0x1c);
static const System::Int8 isc_info_db_impl_isc_apl_68K = System::Int8(0x19);
static const System::Int8 isc_info_db_impl_isc_vax_ultr = System::Int8(0x1a);
static const System::Int8 isc_info_db_impl_isc_vms = System::Int8(0x1b);
static const System::Int8 isc_info_db_impl_isc_sun_68k = System::Int8(0x1c);
static const System::Int8 isc_info_db_impl_isc_os2 = System::Int8(0x1d);
static const System::Int8 isc_info_db_impl_isc_sun4 = System::Int8(0x1e);
static const System::Int8 isc_info_db_impl_isc_hp_ux = System::Int8(0x1f);
static const System::Int8 isc_info_db_impl_isc_sun_386i = System::Int8(0x20);
static const System::Int8 isc_info_db_impl_isc_vms_orcl = System::Int8(0x21);
static const System::Int8 isc_info_db_impl_isc_mac_aux = System::Int8(0x22);
static const System::Int8 isc_info_db_impl_isc_rt_aix = System::Int8(0x23);
static const System::Int8 isc_info_db_impl_isc_mips_ult = System::Int8(0x24);
static const System::Int8 isc_info_db_impl_isc_xenix = System::Int8(0x25);
static const System::Int8 isc_info_db_impl_isc_dg = System::Int8(0x26);
static const System::Int8 isc_info_db_impl_isc_hp_mpexl = System::Int8(0x27);
static const System::Int8 isc_info_db_impl_isc_hp_ux68K = System::Int8(0x28);
static const System::Int8 isc_info_db_impl_isc_sgi = System::Int8(0x29);
static const System::Int8 isc_info_db_impl_isc_sco_unix = System::Int8(0x2a);
static const System::Int8 isc_info_db_impl_isc_cray = System::Int8(0x2b);
static const System::Int8 isc_info_db_impl_isc_imp = System::Int8(0x2c);
static const System::Int8 isc_info_db_impl_isc_delta = System::Int8(0x2d);
static const System::Int8 isc_info_db_impl_isc_next = System::Int8(0x2e);
static const System::Int8 isc_info_db_impl_isc_dos = System::Int8(0x2f);
static const System::Int8 isc_info_db_impl_isc_winnt = System::Int8(0x30);
static const System::Int8 isc_info_db_impl_isc_epson = System::Int8(0x31);
static const System::Int8 isc_info_db_class_access = System::Int8(0x1);
static const System::Int8 isc_info_db_class_y_valve = System::Int8(0x2);
static const System::Int8 isc_info_db_class_rem_int = System::Int8(0x3);
static const System::Int8 isc_info_db_class_rem_srvr = System::Int8(0x4);
static const System::Int8 isc_info_db_class_pipe_int = System::Int8(0x7);
static const System::Int8 isc_info_db_class_pipe_srvr = System::Int8(0x8);
static const System::Int8 isc_info_db_class_sam_int = System::Int8(0x9);
static const System::Int8 isc_info_db_class_sam_srvr = System::Int8(0xa);
static const System::Int8 isc_info_db_class_gateway = System::Int8(0xb);
static const System::Int8 isc_info_db_class_cache = System::Int8(0xc);
static const System::Int8 isc_info_number_messages = System::Int8(0x4);
static const System::Int8 isc_info_max_message = System::Int8(0x5);
static const System::Int8 isc_info_max_send = System::Int8(0x6);
static const System::Int8 isc_info_max_receive = System::Int8(0x7);
static const System::Int8 isc_info_state = System::Int8(0x8);
static const System::Int8 isc_info_message_number = System::Int8(0x9);
static const System::Int8 isc_info_message_size = System::Int8(0xa);
static const System::Int8 isc_info_request_cost = System::Int8(0xb);
static const System::Int8 isc_info_access_path = System::Int8(0xc);
static const System::Int8 isc_info_req_select_count = System::Int8(0xd);
static const System::Int8 isc_info_req_insert_count = System::Int8(0xe);
static const System::Int8 isc_info_req_update_count = System::Int8(0xf);
static const System::Int8 isc_info_req_delete_count = System::Int8(0x10);
static const System::Int8 isc_info_rsb_end = System::Int8(0x0);
static const System::Int8 isc_info_rsb_begin = System::Int8(0x1);
static const System::Int8 isc_info_rsb_type = System::Int8(0x2);
static const System::Int8 isc_info_rsb_relation = System::Int8(0x3);
static const System::Int8 isc_info_rsb_plan = System::Int8(0x4);
static const System::Int8 isc_info_rsb_unknown = System::Int8(0x1);
static const System::Int8 isc_info_rsb_indexed = System::Int8(0x2);
static const System::Int8 isc_info_rsb_navigate = System::Int8(0x3);
static const System::Int8 isc_info_rsb_sequential = System::Int8(0x4);
static const System::Int8 isc_info_rsb_cross = System::Int8(0x5);
static const System::Int8 isc_info_rsb_sort = System::Int8(0x6);
static const System::Int8 isc_info_rsb_first = System::Int8(0x7);
static const System::Int8 isc_info_rsb_boolean = System::Int8(0x8);
static const System::Int8 isc_info_rsb_union = System::Int8(0x9);
static const System::Int8 isc_info_rsb_aggregate = System::Int8(0xa);
static const System::Int8 isc_info_rsb_merge = System::Int8(0xb);
static const System::Int8 isc_info_rsb_ext_sequential = System::Int8(0xc);
static const System::Int8 isc_info_rsb_ext_indexed = System::Int8(0xd);
static const System::Int8 isc_info_rsb_ext_dbkey = System::Int8(0xe);
static const System::Int8 isc_info_rsb_left_cross = System::Int8(0xf);
static const System::Int8 isc_info_rsb_select = System::Int8(0x10);
static const System::Int8 isc_info_rsb_sql_join = System::Int8(0x11);
static const System::Int8 isc_info_rsb_simulate = System::Int8(0x12);
static const System::Int8 isc_info_rsb_sim_cross = System::Int8(0x13);
static const System::Int8 isc_info_rsb_once = System::Int8(0x14);
static const System::Int8 isc_info_rsb_procedure = System::Int8(0x15);
static const System::Int8 isc_info_rsb_and = System::Int8(0x1);
static const System::Int8 isc_info_rsb_or = System::Int8(0x2);
static const System::Int8 isc_info_rsb_dbkey = System::Int8(0x3);
static const System::Int8 isc_info_rsb_index = System::Int8(0x4);
static const System::Int8 isc_info_req_active = System::Int8(0x2);
static const System::Int8 isc_info_req_inactive = System::Int8(0x3);
static const System::Int8 isc_info_req_send = System::Int8(0x4);
static const System::Int8 isc_info_req_receive = System::Int8(0x5);
static const System::Int8 isc_info_req_select = System::Int8(0x6);
static const System::Int8 isc_info_req_sql_stall = System::Int8(0x7);
static const System::Int8 isc_info_blob_num_segments = System::Int8(0x4);
static const System::Int8 isc_info_blob_max_segment = System::Int8(0x5);
static const System::Int8 isc_info_blob_total_length = System::Int8(0x6);
static const System::Int8 isc_info_blob_type = System::Int8(0x7);
static const System::Int8 isc_info_tra_id = System::Int8(0x4);
static const System::Int8 isc_action_min = System::Int8(0x1);
static const System::Int8 isc_action_svc_backup = System::Int8(0x1);
static const System::Int8 isc_action_svc_restore = System::Int8(0x2);
static const System::Int8 isc_action_svc_repair = System::Int8(0x3);
static const System::Int8 isc_action_svc_add_user = System::Int8(0x4);
static const System::Int8 isc_action_svc_delete_user = System::Int8(0x5);
static const System::Int8 isc_action_svc_modify_user = System::Int8(0x6);
static const System::Int8 isc_action_svc_display_user = System::Int8(0x7);
static const System::Int8 isc_action_svc_properties = System::Int8(0x8);
static const System::Int8 isc_action_svc_add_license = System::Int8(0x9);
static const System::Int8 isc_action_svc_remove_license = System::Int8(0xa);
static const System::Int8 isc_action_svc_db_stats = System::Int8(0xb);
static const System::Int8 isc_action_svc_get_ib_log = System::Int8(0xc);
static const System::Int8 isc_action_svc_add_db_alias = System::Int8(0xd);
static const System::Int8 isc_action_svc_delete_db_alias = System::Int8(0xe);
static const System::Int8 isc_action_svc_display_db_alias = System::Int8(0xf);
static const System::Int8 isc_action_svc_dump = System::Int8(0x10);
static const System::Int8 isc_action_max = System::Int8(0x11);
static const System::Int8 isc_info_svc_svr_db_info = System::Int8(0x32);
static const System::Int8 isc_info_svc_get_license = System::Int8(0x33);
static const System::Int8 isc_info_svc_get_license_mask = System::Int8(0x34);
static const System::Int8 isc_info_svc_get_config = System::Int8(0x35);
static const System::Int8 isc_info_svc_version = System::Int8(0x36);
static const System::Int8 isc_info_svc_server_version = System::Int8(0x37);
static const System::Int8 isc_info_svc_implementation = System::Int8(0x38);
static const System::Int8 isc_info_svc_capabilities = System::Int8(0x39);
static const System::Int8 isc_info_svc_user_dbpath = System::Int8(0x3a);
static const System::Int8 isc_info_svc_get_env = System::Int8(0x3b);
static const System::Int8 isc_info_svc_get_env_lock = System::Int8(0x3c);
static const System::Int8 isc_info_svc_get_env_msg = System::Int8(0x3d);
static const System::Int8 isc_info_svc_line = System::Int8(0x3e);
static const System::Int8 isc_info_svc_to_eof = System::Int8(0x3f);
static const System::Int8 isc_info_svc_timeout = System::Int8(0x40);
static const System::Int8 isc_info_svc_get_licensed_users = System::Int8(0x41);
static const System::Int8 isc_info_svc_limbo_trans = System::Int8(0x42);
static const System::Int8 isc_info_svc_running = System::Int8(0x43);
static const System::Int8 isc_info_svc_get_users = System::Int8(0x44);
static const System::Int8 isc_info_svc_get_db_alias = System::Int8(0x45);
static const System::Int8 isc_info_svc_product_identifier = System::Int8(0x46);
static const System::Int8 isc_spb_sec_userid = System::Int8(0x5);
static const System::Int8 isc_spb_sec_groupid = System::Int8(0x6);
static const System::Int8 isc_spb_sec_username = System::Int8(0x7);
static const System::Int8 isc_spb_sec_password = System::Int8(0x8);
static const System::Int8 isc_spb_sec_groupname = System::Int8(0x9);
static const System::Int8 isc_spb_sec_firstname = System::Int8(0xa);
static const System::Int8 isc_spb_sec_middlename = System::Int8(0xb);
static const System::Int8 isc_spb_sec_lastname = System::Int8(0xc);
static const System::Int8 isc_spb_sec_db_alias_name = System::Int8(0x14);
static const System::Int8 isc_spb_sec_db_alias_dbpath = System::Int8(0x15);
static const System::Int8 isc_spb_lic_key = System::Int8(0x5);
static const System::Int8 isc_spb_lic_id = System::Int8(0x6);
static const System::Int8 isc_spb_lic_desc = System::Int8(0x7);
static const System::Int8 isc_spb_prp_page_buffers = System::Int8(0x5);
static const System::Int8 isc_spb_prp_sweep_interval = System::Int8(0x6);
static const System::Int8 isc_spb_prp_shutdown_db = System::Int8(0x7);
static const System::Int8 isc_spb_prp_deny_new_attachments = System::Int8(0x9);
static const System::Int8 isc_spb_prp_deny_new_transactions = System::Int8(0xa);
static const System::Int8 isc_spb_prp_reserve_space = System::Int8(0xb);
static const System::Int8 isc_spb_prp_write_mode = System::Int8(0xc);
static const System::Int8 isc_spb_prp_access_mode = System::Int8(0xd);
static const System::Int8 isc_spb_prp_set_sql_dialect = System::Int8(0xe);
static const System::Int8 isc_spb_prp_archive_dumps = System::Int8(0x2a);
static const System::Int8 isc_spb_prp_archive_sweep = System::Int8(0x2b);
static const System::Word isc_spb_prp_activate = System::Word(0x100);
static const System::Word isc_spb_prp_db_online = System::Word(0x200);
static const System::Int8 isc_spb_prp_res_use_full = System::Int8(0x23);
static const System::Int8 isc_spb_prp_res = System::Int8(0x24);
static const System::Int8 isc_spb_prp_wm_async = System::Int8(0x25);
static const System::Int8 isc_spb_prp_wm_sync = System::Int8(0x26);
static const System::Int8 isc_spb_prp_wm_direct = System::Int8(0x29);
static const System::Int8 isc_spb_prp_am_readonly = System::Int8(0x27);
static const System::Int8 isc_spb_prp_am_readwrite = System::Int8(0x28);
static const System::Int8 isc_spb_rpr_commit_trans = System::Int8(0xf);
static const System::Int8 isc_spb_rpr_rollback_trans = System::Int8(0x22);
static const System::Int8 isc_spb_rpr_recover_two_phase = System::Int8(0x11);
static const System::Int8 isc_spb_tra_id = System::Int8(0x12);
static const System::Int8 isc_spb_single_tra_id = System::Int8(0x13);
static const System::Int8 isc_spb_multi_tra_id = System::Int8(0x14);
static const System::Int8 isc_spb_tra_state = System::Int8(0x15);
static const System::Int8 isc_spb_tra_state_limbo = System::Int8(0x16);
static const System::Int8 isc_spb_tra_state_commit = System::Int8(0x17);
static const System::Int8 isc_spb_tra_state_rollback = System::Int8(0x18);
static const System::Int8 isc_spb_tra_state_unknown = System::Int8(0x19);
static const System::Int8 isc_spb_tra_host_site = System::Int8(0x1a);
static const System::Int8 isc_spb_tra_remote_site = System::Int8(0x1b);
static const System::Int8 isc_spb_tra_db_path = System::Int8(0x1c);
static const System::Int8 isc_spb_tra_advise = System::Int8(0x1d);
static const System::Int8 isc_spb_tra_advise_commit = System::Int8(0x1e);
static const System::Int8 isc_spb_tra_advise_rollback = System::Int8(0x1f);
static const System::Int8 isc_spb_tra_advise_unknown = System::Int8(0x21);
static const System::Int8 isc_spb_rpr_validate_db = System::Int8(0x1);
static const System::Int8 isc_spb_rpr_sweep_db = System::Int8(0x2);
static const System::Int8 isc_spb_rpr_mend_db = System::Int8(0x4);
static const System::Int8 isc_spb_rpr_list_limbo_trans = System::Int8(0x8);
static const System::Int8 isc_spb_rpr_check_db = System::Int8(0x10);
static const System::Int8 isc_spb_rpr_ignore_checksum = System::Int8(0x20);
static const System::Int8 isc_spb_rpr_kill_shadows = System::Int8(0x40);
static const System::Byte isc_spb_rpr_full = System::Byte(0x80);
static const System::Int8 isc_spb_bkp_file = System::Int8(0x5);
static const System::Int8 isc_spb_bkp_factor = System::Int8(0x6);
static const System::Int8 isc_spb_bkp_length = System::Int8(0x7);
static const System::Int8 isc_spb_bkp_preallocate = System::Int8(0xd);
static const System::Int8 isc_spb_bkp_encrypt_name = System::Int8(0xe);
static const System::Int8 isc_spb_bkp_ignore_checksums = System::Int8(0x1);
static const System::Int8 isc_spb_bkp_ignore_limbo = System::Int8(0x2);
static const System::Int8 isc_spb_bkp_metadata_only = System::Int8(0x4);
static const System::Int8 isc_spb_bkp_no_garbage_collect = System::Int8(0x8);
static const System::Int8 isc_spb_bkp_old_descriptions = System::Int8(0x10);
static const System::Int8 isc_spb_bkp_non_transportable = System::Int8(0x20);
static const System::Int8 isc_spb_bkp_convert = System::Int8(0x40);
static const System::Byte isc_spb_bkp_expand = System::Byte(0x80);
static const int isc_spb_bkp_archive_database = int(0x10000);
static const int isc_spb_bkp_archive_journals = int(0x20000);
static const System::Int8 isc_spb_res_buffers = System::Int8(0x9);
static const System::Int8 isc_spb_res_page_size = System::Int8(0xa);
static const System::Int8 isc_spb_res_length = System::Int8(0xb);
static const System::Int8 isc_spb_res_access_mode = System::Int8(0xc);
static const System::Int8 isc_spb_res_preallocate = System::Int8(0xd);
static const System::Int8 isc_spb_res_decrypt_password = System::Int8(0x10);
static const System::Int8 isc_spb_res_eua_user_name = System::Int8(0x11);
static const System::Int8 isc_spb_res_eua_password = System::Int8(0x12);
static const System::Int8 isc_spb_res_write_mode = System::Int8(0x13);
static const System::Int8 isc_spb_res_starting_trans = System::Int8(0x15);
static const System::Int8 isc_spb_res_ods_version_major = System::Int8(0x16);
static const System::Int8 isc_spb_res_archive_recover_until = System::Int8(0x17);
static const System::Int8 isc_spb_res_metadata_only = System::Int8(0x4);
static const System::Word isc_spb_res_deactivate_idx = System::Word(0x100);
static const System::Word isc_spb_res_no_shadow = System::Word(0x200);
static const System::Word isc_spb_res_no_validity = System::Word(0x400);
static const System::Word isc_spb_res_one_at_a_time = System::Word(0x800);
static const System::Word isc_spb_res_replace = System::Word(0x1000);
static const System::Word isc_spb_res_create = System::Word(0x2000);
static const System::Word isc_spb_res_use_all_space = System::Word(0x4000);
static const System::Word isc_spb_res_validate = System::Word(0x8000);
static const int isc_spb_res_archive_recover = int(0x40000);
static const int isc_spb_res_create_tablespace = int(0x100000);
static const int isc_spb_res_replace_tablespace = int(0x200000);
static const System::Int8 isc_spb_tablespace_include = System::Int8(0x18);
static const System::Int8 isc_spb_tablespace_exclude = System::Int8(0x19);
static const System::Int8 isc_spb_tablespace_file = System::Int8(0x5);
static const System::Int8 isc_spb_dmp_file = System::Int8(0x5);
static const System::Int8 isc_spb_dmp_length = System::Int8(0x7);
static const System::Int8 isc_spb_dmp_overwrite = System::Int8(0x14);
static const int isc_spb_dmp_create = int(0x80000);
static const System::Int8 isc_spb_res_am_readonly = System::Int8(0x27);
static const System::Int8 isc_spb_res_am_readwrite = System::Int8(0x28);
static const System::Int8 isc_spb_res_wm_async = System::Int8(0x25);
static const System::Int8 isc_spb_res_wm_sync = System::Int8(0x26);
static const System::Int8 isc_spb_res_wm_direct = System::Int8(0x29);
static const System::Int8 isc_spb_num_att = System::Int8(0x5);
static const System::Int8 isc_spb_num_db = System::Int8(0x6);
static const System::Int8 isc_spb_sts_data_pages = System::Int8(0x1);
static const System::Int8 isc_spb_sts_db_log = System::Int8(0x2);
static const System::Int8 isc_spb_sts_hdr_pages = System::Int8(0x4);
static const System::Int8 isc_spb_sts_idx_pages = System::Int8(0x8);
static const System::Int8 isc_spb_sts_sys_relations = System::Int8(0x10);
static const System::Int8 isc_spb_sts_record_versions = System::Int8(0x20);
static const System::Int8 isc_spb_sts_table = System::Int8(0x40);
static const System::Int8 isc_info_sql_select = System::Int8(0x4);
static const System::Int8 isc_info_sql_bind = System::Int8(0x5);
static const System::Int8 isc_info_sql_num_variables = System::Int8(0x6);
static const System::Int8 isc_info_sql_describe_vars = System::Int8(0x7);
static const System::Int8 isc_info_sql_describe_end = System::Int8(0x8);
static const System::Int8 isc_info_sql_sqlda_seq = System::Int8(0x9);
static const System::Int8 isc_info_sql_message_seq = System::Int8(0xa);
static const System::Int8 isc_info_sql_type = System::Int8(0xb);
static const System::Int8 isc_info_sql_sub_type = System::Int8(0xc);
static const System::Int8 isc_info_sql_scale = System::Int8(0xd);
static const System::Int8 isc_info_sql_length = System::Int8(0xe);
static const System::Int8 isc_info_sql_null_ind = System::Int8(0xf);
static const System::Int8 isc_info_sql_field = System::Int8(0x10);
static const System::Int8 isc_info_sql_relation = System::Int8(0x11);
static const System::Int8 isc_info_sql_owner = System::Int8(0x12);
static const System::Int8 isc_info_sql_alias = System::Int8(0x13);
static const System::Int8 isc_info_sql_sqlda_start = System::Int8(0x14);
static const System::Int8 isc_info_sql_stmt_type = System::Int8(0x15);
static const System::Int8 isc_info_sql_get_plan = System::Int8(0x16);
static const System::Int8 isc_info_sql_records = System::Int8(0x17);
static const System::Int8 isc_info_sql_batch_fetch = System::Int8(0x18);
static const System::Int8 isc_info_sql_precision = System::Int8(0x19);
static const System::Int8 isc_info_sql_stmt_select = System::Int8(0x1);
static const System::Int8 isc_info_sql_stmt_insert = System::Int8(0x2);
static const System::Int8 isc_info_sql_stmt_update = System::Int8(0x3);
static const System::Int8 isc_info_sql_stmt_delete = System::Int8(0x4);
static const System::Int8 isc_info_sql_stmt_ddl = System::Int8(0x5);
static const System::Int8 isc_info_sql_stmt_get_segment = System::Int8(0x6);
static const System::Int8 isc_info_sql_stmt_put_segment = System::Int8(0x7);
static const System::Int8 isc_info_sql_stmt_exec_procedure = System::Int8(0x8);
static const System::Int8 isc_info_sql_stmt_start_trans = System::Int8(0x9);
static const System::Int8 isc_info_sql_stmt_commit = System::Int8(0xa);
static const System::Int8 isc_info_sql_stmt_rollback = System::Int8(0xb);
static const System::Int8 isc_info_sql_stmt_select_for_upd = System::Int8(0xc);
static const System::Int8 isc_info_sql_stmt_set_generator = System::Int8(0xd);
static const System::Int8 isc_info_sql_stmt_set_password = System::Int8(0xe);
static const System::Int8 isc_info_sql_stmt_set_subscription = System::Int8(0xf);
static const System::Int8 isc_info_sql_stmt_truncate = System::Int8(0x10);
static const System::Int8 ISCCFG_LOCKMEM_KEY = System::Int8(0x0);
static const System::Int8 ISCCFG_LOCKSEM_KEY = System::Int8(0x1);
static const System::Int8 ISCCFG_LOCKSIG_KEY = System::Int8(0x2);
static const System::Int8 ISCCFG_EVNTMEM_KEY = System::Int8(0x3);
static const System::Int8 ISCCFG_DBCACHE_KEY = System::Int8(0x4);
static const System::Int8 ISCCFG_PRIORITY_KEY = System::Int8(0x5);
static const System::Int8 ISCCFG_IPCMAP_KEY = System::Int8(0x6);
static const System::Int8 ISCCFG_MEMMIN_KEY = System::Int8(0x7);
static const System::Int8 ISCCFG_MEMMAX_KEY = System::Int8(0x8);
static const System::Int8 ISCCFG_LOCKORDER_KEY = System::Int8(0x9);
static const System::Int8 ISCCFG_ANYLOCKMEM_KEY = System::Int8(0xa);
static const System::Int8 ISCCFG_ANYLOCKSEM_KEY = System::Int8(0xb);
static const System::Int8 ISCCFG_ANYLOCKSIG_KEY = System::Int8(0xc);
static const System::Int8 ISCCFG_ANYEVNTMEM_KEY = System::Int8(0xd);
static const System::Int8 ISCCFG_LOCKHASH_KEY = System::Int8(0xe);
static const System::Int8 ISCCFG_DEADLOCK_KEY = System::Int8(0xf);
static const System::Int8 ISCCFG_LOCKSPIN_KEY = System::Int8(0x10);
static const System::Int8 ISCCFG_CONN_TIMEOUT_KEY = System::Int8(0x11);
static const System::Int8 ISCCFG_DUMMY_INTRVL_KEY = System::Int8(0x12);
static const System::Int8 ISCCFG_TRACE_POOLS_KEY = System::Int8(0x13);
static const System::Int8 ISCCFG_REMOTE_BUFFER_KEY = System::Int8(0x14);
static const System::Int8 ISCCFG_CPU_AFFINITY_KEY = System::Int8(0x15);
static const System::Int8 ISCCFG_SWEEP_QUANTUM_KEY = System::Int8(0x16);
static const System::Int8 ISCCFG_USER_QUANTUM_KEY = System::Int8(0x17);
static const System::Int8 ISCCFG_SLEEP_TIME_KEY = System::Int8(0x18);
static const System::Int8 ISCCFG_MAX_THREADS_KEY = System::Int8(0x19);
static const System::Int8 ISCCFG_ADMIN_DB_KEY = System::Int8(0x1a);
static const System::Int8 ISCCFG_USE_SANCTUARY_KEY = System::Int8(0x1b);
static const System::Int8 ISCCFG_ENABLE_HT_KEY = System::Int8(0x1c);
static const System::Int8 ISCCFG_USE_ROUTER_KEY = System::Int8(0x1d);
static const System::Int8 ISCCFG_SORTMEM_BUFFER_SIZE_KEY = System::Int8(0x1e);
static const System::Int8 ISCCFG_SQL_CMP_RECURSION_KEY = System::Int8(0x1f);
static const System::Int8 ISCCFG_SOL_BOUND_THREADS_KEY = System::Int8(0x20);
static const System::Int8 ISCCFG_SOL_SYNC_SCOPE_KEY = System::Int8(0x21);
static const System::Int8 ISCCFG_IDX_RECNUM_MARKER_KEY = System::Int8(0x22);
static const System::Int8 ISCCFG_IDX_GARBAGE_COLLECTION_KEY = System::Int8(0x23);
static const System::Int8 ISCCFG_WIN_LOCAL_CONNECT_RETRIES_KEY = System::Int8(0x24);
static const System::Int8 ISCCFG_EXPAND_MOUNTPOINT_KEY = System::Int8(0x25);
static const System::Int8 ISCCFG_LOOPBACK_CONNECTION_KEY = System::Int8(0x26);
static const System::Int8 ISCCFG_THREAD_STACK_SIZE_KEY = System::Int8(0x27);
static const System::Int8 ISCCFG_MAX_DB_VIRMEM_USE_KEY = System::Int8(0x28);
static const System::Int8 ISCCFG_MAX_ASSISTANTS_KEY = System::Int8(0x29);
static const System::Int8 ISCCFG_APPDATA_DIR_KEY = System::Int8(0x2a);
static const System::Int8 ISCCFG_MEMORY_RECLAMATION_KEY = System::Int8(0x2b);
static const System::Int8 ISCCFG_PAGE_CACHE_EXPANSION_KEY = System::Int8(0x2c);
static const System::Int8 ISCCFG_STARTING_TRANSACTION_ID_KEY = System::Int8(0x2d);
static const System::Int8 ISCCFG_DATABASE_ODS_VERSION_KEY = System::Int8(0x2e);
static const System::Int8 isc_facility = System::Int8(0x14);
static const int isc_err_base = int(0x14000000);
static const System::Int8 isc_err_factor = System::Int8(0x1);
static const System::Int8 isc_arg_end = System::Int8(0x0);
static const System::Int8 isc_arg_gds = System::Int8(0x1);
static const System::Int8 isc_arg_string = System::Int8(0x2);
static const System::Int8 isc_arg_cstring = System::Int8(0x3);
static const System::Int8 isc_arg_number = System::Int8(0x4);
static const System::Int8 isc_arg_interpreted = System::Int8(0x5);
static const System::Int8 isc_arg_vms = System::Int8(0x6);
static const System::Int8 isc_arg_unix = System::Int8(0x7);
static const System::Int8 isc_arg_domain = System::Int8(0x8);
static const System::Int8 isc_arg_dos = System::Int8(0x9);
static const System::Int8 isc_arg_mpexl = System::Int8(0xa);
static const System::Int8 isc_arg_mpexl_ipc = System::Int8(0xb);
static const System::Int8 isc_arg_next_mach = System::Int8(0xf);
static const System::Int8 isc_arg_netware = System::Int8(0x10);
static const System::Int8 isc_arg_win32 = System::Int8(0x11);
static const System::Int8 isc_arg_warning = System::Int8(0x12);
static const System::Int8 isc_arg_sql = System::Int8(0x13);
static const System::Int8 isc_arg_int64 = System::Int8(0x14);
static const System::Int8 isc_dyn_version_1 = System::Int8(0x1);
static const System::Int8 isc_dyn_eoc = System::Int8(-1);
static const System::Int8 isc_dyn_begin = System::Int8(0x2);
static const System::Int8 isc_dyn_end = System::Int8(0x3);
static const System::Int8 isc_dyn_if = System::Int8(0x4);
static const System::Int8 isc_dyn_def_database = System::Int8(0x5);
static const System::Int8 isc_dyn_def_global_fld = System::Int8(0x6);
static const System::Int8 isc_dyn_def_local_fld = System::Int8(0x7);
static const System::Int8 isc_dyn_def_idx = System::Int8(0x8);
static const System::Int8 isc_dyn_def_rel = System::Int8(0x9);
static const System::Int8 isc_dyn_def_sql_fld = System::Int8(0xa);
static const System::Int8 isc_dyn_mod_rel = System::Int8(0xb);
static const System::Int8 isc_dyn_def_view = System::Int8(0xc);
static const System::Int8 isc_dyn_mod_global_fld = System::Int8(0xd);
static const System::Int8 isc_dyn_mod_local_fld = System::Int8(0xe);
static const System::Int8 isc_dyn_def_trigger = System::Int8(0xf);
static const System::Int8 isc_dyn_mod_view = System::Int8(0x10);
static const System::Int8 isc_dyn_def_trigger_msg = System::Int8(0x11);
static const System::Int8 isc_dyn_delete_database = System::Int8(0x12);
static const System::Int8 isc_dyn_delete_rel = System::Int8(0x13);
static const System::Int8 isc_dyn_delete_global_fld = System::Int8(0x14);
static const System::Int8 isc_dyn_delete_local_fld = System::Int8(0x15);
static const System::Int8 isc_dyn_delete_idx = System::Int8(0x16);
static const System::Int8 isc_dyn_delete_trigger = System::Int8(0x17);
static const System::Int8 isc_dyn_def_generator = System::Int8(0x18);
static const System::Int8 isc_dyn_def_function = System::Int8(0x19);
static const System::Int8 isc_dyn_def_filter = System::Int8(0x1a);
static const System::Int8 isc_dyn_def_function_arg = System::Int8(0x1b);
static const System::Int8 isc_dyn_mod_trigger_msg = System::Int8(0x1c);
static const System::Int8 isc_dyn_delete_trigger_msg = System::Int8(0x1d);
static const System::Int8 isc_dyn_grant = System::Int8(0x1e);
static const System::Int8 isc_dyn_revoke = System::Int8(0x1f);
static const System::Int8 isc_dyn_delete_filter = System::Int8(0x20);
static const System::Int8 isc_dyn_delete_function = System::Int8(0x21);
static const System::Int8 isc_dyn_def_shadow = System::Int8(0x22);
static const System::Int8 isc_dyn_delete_shadow = System::Int8(0x23);
static const System::Int8 isc_dyn_def_file = System::Int8(0x24);
static const System::Int8 isc_dyn_def_primary_key = System::Int8(0x25);
static const System::Int8 isc_dyn_def_foreign_key = System::Int8(0x26);
static const System::Int8 isc_dyn_mod_database = System::Int8(0x27);
static const System::Int8 isc_dyn_def_unique = System::Int8(0x28);
static const System::Int8 isc_dyn_mod_filter = System::Int8(0x29);
static const System::Int8 isc_dyn_mod_function = System::Int8(0x2a);
static const System::Int8 isc_dyn_mod_generator = System::Int8(0x2b);
static const System::Int8 isc_dyn_mod_character_set = System::Int8(0x2c);
static const System::Int8 isc_dyn_mod_collation = System::Int8(0x2d);
static const System::Int8 isc_dyn_mod_idx = System::Int8(0x66);
static const System::Int8 isc_dyn_mod_trigger = System::Int8(0x71);
static const System::Int8 isc_dyn_def_security_class = System::Int8(0x78);
static const System::Int8 isc_dyn_mod_security_class = System::Int8(0x7a);
static const System::Int8 isc_dyn_delete_security_class = System::Int8(0x7b);
static const System::Byte isc_dyn_def_parameter = System::Byte(0x87);
static const System::Byte isc_dyn_delete_parameter = System::Byte(0x88);
static const System::Byte isc_dyn_def_dimension = System::Byte(0x8c);
static const System::Byte isc_dyn_delete_dimensions = System::Byte(0x8f);
static const System::Byte isc_dyn_def_encryption = System::Byte(0x96);
static const System::Byte isc_dyn_mod_encryption = System::Byte(0x97);
static const System::Byte isc_dyn_delete_encryption = System::Byte(0x98);
static const System::Byte isc_dyn_def_subscription = System::Byte(0xa0);
static const System::Byte isc_dyn_set_subscription = System::Byte(0xa1);
static const System::Byte isc_dyn_def_procedure = System::Byte(0xa4);
static const System::Byte isc_dyn_delete_procedure = System::Byte(0xa5);
static const System::Byte isc_dyn_delete_subscription = System::Byte(0xac);
static const System::Byte isc_dyn_mod_subscription = System::Byte(0xad);
static const System::Byte isc_dyn_mod_procedure = System::Byte(0xaf);
static const System::Byte isc_dyn_def_log_file = System::Byte(0xb0);
static const System::Byte isc_dyn_mod_parameter = System::Byte(0xb1);
static const System::Byte isc_dyn_def_cache_file = System::Byte(0xb4);
static const System::Byte isc_dyn_def_exception = System::Byte(0xb5);
static const System::Byte isc_dyn_mod_exception = System::Byte(0xb6);
static const System::Byte isc_dyn_del_exception = System::Byte(0xb7);
static const System::Byte isc_dyn_def_filespace = System::Byte(0xbe);
static const System::Byte isc_dyn_mod_filespace = System::Byte(0xbf);
static const System::Byte isc_dyn_delete_filespace = System::Byte(0xc0);
static const System::Byte isc_dyn_drop_log = System::Byte(0xc2);
static const System::Byte isc_dyn_drop_cache = System::Byte(0xc3);
static const System::Byte isc_dyn_sys_encrypt_passwd = System::Byte(0xc8);
static const System::Byte isc_dyn_set_password = System::Byte(0xc9);
static const System::Byte isc_dyn_def_default_log = System::Byte(0xca);
static const System::Byte isc_dyn_def_journal = System::Byte(0xcb);
static const System::Byte isc_dyn_mod_journal = System::Byte(0xcc);
static const System::Byte isc_dyn_delete_journal = System::Byte(0xcd);
static const System::Byte isc_dyn_def_archive = System::Byte(0xce);
static const System::Byte isc_dyn_mod_archive = System::Byte(0xcf);
static const System::Byte isc_dyn_delete_archive = System::Byte(0xd0);
static const System::Byte isc_dyn_def_sql_role = System::Byte(0xd3);
static const System::Byte isc_dyn_mod_sql_role = System::Byte(0xd4);
static const System::Byte isc_dyn_del_sql_role = System::Byte(0xd6);
static const System::Byte isc_dyn_mod_sql_fld = System::Byte(0xd8);
static const System::Byte isc_dyn_delete_generator = System::Byte(0xd9);
static const System::Byte isc_dyn_def_user = System::Byte(0xe1);
static const System::Byte isc_dyn_mod_user = System::Byte(0xe2);
static const System::Byte isc_dyn_delete_user = System::Byte(0xe3);
static const System::Int8 isc_dyn_view_blr = System::Int8(0x2b);
static const System::Int8 isc_dyn_view_source = System::Int8(0x2c);
static const System::Int8 isc_dyn_view_relation = System::Int8(0x2d);
static const System::Int8 isc_dyn_view_context = System::Int8(0x2e);
static const System::Int8 isc_dyn_view_context_name = System::Int8(0x2f);
static const System::Int8 isc_dyn_rel_name = System::Int8(0x32);
static const System::Int8 isc_dyn_fld_name = System::Int8(0x33);
static const System::Byte isc_dyn_new_fld_name = System::Byte(0xd7);
static const System::Int8 isc_dyn_idx_name = System::Int8(0x34);
static const System::Int8 isc_dyn_description = System::Int8(0x35);
static const System::Int8 isc_dyn_security_class = System::Int8(0x36);
static const System::Int8 isc_dyn_system_flag = System::Int8(0x37);
static const System::Int8 isc_dyn_update_flag = System::Int8(0x38);
static const System::Int8 isc_dyn_enc_name = System::Int8(0x39);
static const System::Byte isc_dyn_sub_name = System::Byte(0xa2);
static const System::Byte isc_dyn_prc_name = System::Byte(0xa6);
static const System::Byte isc_dyn_prm_name = System::Byte(0x89);
static const System::Byte isc_dyn_sql_object = System::Byte(0xc4);
static const System::Byte isc_dyn_fld_character_set_name = System::Byte(0xae);
static const System::Byte isc_dyn_reserve_space = System::Byte(0xc3);
static const System::Byte isc_dyn_restrict_or_cascade = System::Byte(0xdc);
static const System::Int8 isc_dyn_rel_dbkey_length = System::Int8(0x3d);
static const System::Int8 isc_dyn_rel_store_trig = System::Int8(0x3e);
static const System::Int8 isc_dyn_rel_modify_trig = System::Int8(0x3f);
static const System::Int8 isc_dyn_rel_erase_trig = System::Int8(0x40);
static const System::Int8 isc_dyn_rel_store_trig_source = System::Int8(0x41);
static const System::Int8 isc_dyn_rel_modify_trig_source = System::Int8(0x42);
static const System::Int8 isc_dyn_rel_erase_trig_source = System::Int8(0x43);
static const System::Int8 isc_dyn_rel_ext_file = System::Int8(0x44);
static const System::Int8 isc_dyn_rel_sql_protection = System::Int8(0x45);
static const System::Byte isc_dyn_rel_constraint = System::Byte(0xa2);
static const System::Byte isc_dyn_delete_rel_constraint = System::Byte(0xa3);
static const System::Byte isc_dyn_rel_sql_scope = System::Byte(0xda);
static const System::Byte isc_dyn_rel_sql_on_commit = System::Byte(0xdb);
static const System::Int8 isc_dyn_fld_type = System::Int8(0x46);
static const System::Int8 isc_dyn_fld_length = System::Int8(0x47);
static const System::Int8 isc_dyn_fld_scale = System::Int8(0x48);
static const System::Int8 isc_dyn_fld_sub_type = System::Int8(0x49);
static const System::Int8 isc_dyn_fld_segment_length = System::Int8(0x4a);
static const System::Int8 isc_dyn_fld_query_header = System::Int8(0x4b);
static const System::Int8 isc_dyn_fld_edit_string = System::Int8(0x4c);
static const System::Int8 isc_dyn_fld_validation_blr = System::Int8(0x4d);
static const System::Int8 isc_dyn_fld_validation_source = System::Int8(0x4e);
static const System::Int8 isc_dyn_fld_computed_blr = System::Int8(0x4f);
static const System::Int8 isc_dyn_fld_computed_source = System::Int8(0x50);
static const System::Int8 isc_dyn_fld_missing_value = System::Int8(0x51);
static const System::Int8 isc_dyn_fld_default_value = System::Int8(0x52);
static const System::Int8 isc_dyn_fld_query_name = System::Int8(0x53);
static const System::Int8 isc_dyn_fld_dimensions = System::Int8(0x54);
static const System::Int8 isc_dyn_fld_not_null = System::Int8(0x55);
static const System::Int8 isc_dyn_fld_precision = System::Int8(0x56);
static const System::Byte isc_dyn_fld_char_length = System::Byte(0xac);
static const System::Byte isc_dyn_fld_collation = System::Byte(0xad);
static const System::Byte isc_dyn_fld_default_source = System::Byte(0xc1);
static const System::Byte isc_dyn_del_default = System::Byte(0xc5);
static const System::Byte isc_dyn_del_validation = System::Byte(0xc6);
static const System::Byte isc_dyn_single_validation = System::Byte(0xc7);
static const System::Byte isc_dyn_fld_encrypt = System::Byte(0xc8);
static const System::Byte isc_dyn_fld_decrypt_dflt_value = System::Byte(0xc9);
static const System::Byte isc_dyn_fld_decrypt_dflt_source = System::Byte(0xca);
static const System::Byte isc_dyn_fld_character_set = System::Byte(0xcb);
static const System::Int8 isc_dyn_fld_derived = System::Int8(0x59);
static const System::Int8 isc_dyn_fld_source = System::Int8(0x5a);
static const System::Int8 isc_dyn_fld_base_fld = System::Int8(0x5b);
static const System::Int8 isc_dyn_fld_position = System::Int8(0x5c);
static const System::Int8 isc_dyn_fld_update_flag = System::Int8(0x5d);
static const System::Int8 isc_dyn_fld_all = System::Int8(0x5e);
static const System::Int8 isc_dyn_idx_unique = System::Int8(0x64);
static const System::Int8 isc_dyn_idx_inactive = System::Int8(0x65);
static const System::Int8 isc_dyn_idx_type = System::Int8(0x67);
static const System::Int8 isc_dyn_idx_foreign_key = System::Int8(0x68);
static const System::Int8 isc_dyn_idx_ref_column = System::Int8(0x69);
static const System::Byte isc_dyn_idx_statistic = System::Byte(0xcc);
static const System::Int8 isc_dyn_trg_type = System::Int8(0x6e);
static const System::Int8 isc_dyn_trg_blr = System::Int8(0x6f);
static const System::Int8 isc_dyn_trg_source = System::Int8(0x70);
static const System::Int8 isc_dyn_trg_name = System::Int8(0x72);
static const System::Int8 isc_dyn_trg_sequence = System::Int8(0x73);
static const System::Int8 isc_dyn_trg_inactive = System::Int8(0x74);
static const System::Int8 isc_dyn_trg_msg_number = System::Int8(0x75);
static const System::Int8 isc_dyn_trg_msg = System::Int8(0x76);
static const System::Int8 isc_dyn_scl_acl = System::Int8(0x79);
static const System::Byte isc_dyn_grant_user = System::Byte(0x82);
static const System::Byte isc_dyn_grant_proc = System::Byte(0xba);
static const System::Byte isc_dyn_grant_trig = System::Byte(0xbb);
static const System::Byte isc_dyn_grant_view = System::Byte(0xbc);
static const System::Byte isc_dyn_grant_options = System::Byte(0x84);
static const System::Byte isc_dyn_grant_user_group = System::Byte(0xcd);
static const System::Byte isc_dyn_dim_lower = System::Byte(0x8d);
static const System::Byte isc_dyn_dim_upper = System::Byte(0x8e);
static const System::Int8 isc_dyn_file_name = System::Int8(0x7d);
static const System::Int8 isc_dyn_file_start = System::Int8(0x7e);
static const System::Int8 isc_dyn_file_length = System::Int8(0x7f);
static const System::Byte isc_dyn_shadow_number = System::Byte(0x80);
static const System::Byte isc_dyn_shadow_man_auto = System::Byte(0x81);
static const System::Byte isc_dyn_shadow_conditional = System::Byte(0x82);
static const System::Byte isc_dyn_file_prealloc = System::Byte(0x83);
static const System::Byte isc_dyn_log_file_sequence = System::Byte(0xb1);
static const System::Byte isc_dyn_log_file_partitions = System::Byte(0xb2);
static const System::Byte isc_dyn_log_file_serial = System::Byte(0xb3);
static const System::Byte isc_dyn_log_file_directory = System::Byte(0xc8);
static const System::Byte isc_dyn_log_file_raw = System::Byte(0xc9);
static const System::Byte isc_dyn_log_check_point_interval = System::Byte(0xbd);
static const System::Byte isc_dyn_log_buffer_size = System::Byte(0xbe);
static const System::Byte isc_dyn_log_check_point_length = System::Byte(0xbf);
static const System::Byte isc_dyn_log_num_of_buffers = System::Byte(0xc0);
static const System::Byte isc_dyn_log_timestamp_name = System::Byte(0xc1);
static const System::Byte isc_dyn_function_name = System::Byte(0x91);
static const System::Byte isc_dyn_function_type = System::Byte(0x92);
static const System::Byte isc_dyn_func_module_name = System::Byte(0x93);
static const System::Byte isc_dyn_func_entry_point = System::Byte(0x94);
static const System::Byte isc_dyn_func_return_argument = System::Byte(0x95);
static const System::Byte isc_dyn_func_arg_position = System::Byte(0x96);
static const System::Byte isc_dyn_func_mechanism = System::Byte(0x97);
static const System::Byte isc_dyn_filter_in_subtype = System::Byte(0x98);
static const System::Byte isc_dyn_filter_out_subtype = System::Byte(0x99);
static const System::Byte isc_dyn_description2 = System::Byte(0x9a);
static const System::Byte isc_dyn_fld_computed_source2 = System::Byte(0x9b);
static const System::Byte isc_dyn_fld_edit_string2 = System::Byte(0x9c);
static const System::Byte isc_dyn_fld_query_header2 = System::Byte(0x9d);
static const System::Byte isc_dyn_fld_validation_source2 = System::Byte(0x9e);
static const System::Byte isc_dyn_trg_msg2 = System::Byte(0x9f);
static const System::Byte isc_dyn_trg_source2 = System::Byte(0xa0);
static const System::Byte isc_dyn_view_source2 = System::Byte(0xa1);
static const System::Byte isc_dyn_xcp_msg2 = System::Byte(0xb8);
static const System::Int8 isc_dyn_generator_name = System::Int8(0x5f);
static const System::Int8 isc_dyn_generator_id = System::Int8(0x60);
static const System::Byte isc_dyn_prc_inputs = System::Byte(0xa7);
static const System::Byte isc_dyn_prc_outputs = System::Byte(0xa8);
static const System::Byte isc_dyn_prc_source = System::Byte(0xa9);
static const System::Byte isc_dyn_prc_blr = System::Byte(0xaa);
static const System::Byte isc_dyn_prc_source2 = System::Byte(0xab);
static const System::Byte isc_dyn_prm_number = System::Byte(0x8a);
static const System::Byte isc_dyn_prm_type = System::Byte(0x8b);
static const System::Byte isc_dyn_xcp_msg = System::Byte(0xb9);
static const System::Byte isc_dyn_change_type = System::Byte(0xa3);
static const System::Byte isc_dyn_insert = System::Byte(0xa5);
static const System::Byte isc_dyn_update = System::Byte(0xa6);
static const System::Byte isc_dyn_delete = System::Byte(0xa7);
static const System::Byte isc_dyn_change = System::Byte(0xa8);
static const System::Byte isc_dyn_sub_active = System::Byte(0xa9);
static const System::Byte isc_dyn_sub_inactive = System::Byte(0xaa);
static const System::Byte isc_dyn_sub_dest = System::Byte(0xab);
static const System::Byte isc_dyn_foreign_key_update = System::Byte(0xcd);
static const System::Byte isc_dyn_foreign_key_delete = System::Byte(0xce);
static const System::Byte isc_dyn_foreign_key_cascade = System::Byte(0xcf);
static const System::Byte isc_dyn_foreign_key_default = System::Byte(0xd0);
static const System::Byte isc_dyn_foreign_key_null = System::Byte(0xd1);
static const System::Byte isc_dyn_foreign_key_none = System::Byte(0xd2);
static const System::Byte isc_dyn_sql_role_name = System::Byte(0xd4);
static const System::Byte isc_dyn_grant_admin_options = System::Byte(0xd5);
static const System::Byte isc_dyn_add_admin = System::Byte(0xdd);
static const System::Byte isc_dyn_drop_admin = System::Byte(0xde);
static const System::Byte isc_dyn_admin_active = System::Byte(0xdf);
static const System::Byte isc_dyn_admin_inactive = System::Byte(0xe0);
static const System::Int8 isc_dyn_user_sys_name = System::Int8(0xb);
static const System::Int8 isc_dyn_user_grp_name = System::Int8(0xc);
static const System::Int8 isc_dyn_user_uid = System::Int8(0xd);
static const System::Int8 isc_dyn_user_gid = System::Int8(0xe);
static const System::Int8 isc_dyn_user_password = System::Int8(0xf);
static const System::Int8 isc_dyn_user_active = System::Int8(0x10);
static const System::Int8 isc_dyn_user_inactive = System::Int8(0x11);
static const System::Int8 isc_dyn_user_description = System::Int8(0x12);
static const System::Int8 isc_dyn_user_first_name = System::Int8(0x13);
static const System::Int8 isc_dyn_user_middle_name = System::Int8(0x14);
static const System::Int8 isc_dyn_user_last_name = System::Int8(0x15);
static const System::Int8 isc_dyn_user_default_role = System::Int8(0x16);
static const System::Int8 isc_dyn_db_page_size = System::Int8(0x23);
static const System::Int8 isc_dyn_db_passwd_digest = System::Int8(0x25);
static const System::Int8 isc_dyn_db_page_all_checksum = System::Int8(0x26);
static const System::Int8 isc_dyn_db_page_enc_checksum = System::Int8(0x27);
static const System::Int8 isc_dyn_db_page_off_checksum = System::Int8(0x28);
static const System::Int8 isc_dyn_db_page_cache = System::Int8(0x29);
static const System::Int8 isc_dyn_db_proc_cache = System::Int8(0x2a);
static const System::Int8 isc_dyn_db_rel_cache = System::Int8(0x2b);
static const System::Int8 isc_dyn_db_trig_cache = System::Int8(0x2c);
static const System::Int8 isc_dyn_db_flush_int = System::Int8(0x2d);
static const System::Int8 isc_dyn_db_linger_int = System::Int8(0x2e);
static const System::Int8 isc_dyn_db_reclaim_int = System::Int8(0x2f);
static const System::Int8 isc_dyn_db_sweep_int = System::Int8(0x30);
static const System::Int8 isc_dyn_db_group_commit = System::Int8(0x31);
static const System::Int8 isc_dyn_enc_default = System::Int8(0x32);
static const System::Int8 isc_dyn_enc_cipher = System::Int8(0x33);
static const System::Int8 isc_dyn_enc_length = System::Int8(0x34);
static const System::Int8 isc_dyn_enc_password = System::Int8(0x36);
static const System::Int8 isc_dyn_enc_init_vector = System::Int8(0x37);
static const System::Int8 isc_dyn_enc_pad = System::Int8(0x38);
static const System::Int8 isc_dyn_encrypt = System::Int8(0x39);
static const System::Int8 isc_dyn_decrypt = System::Int8(0x3a);
static const System::Int8 isc_dyn_fsp_active = System::Int8(0x46);
static const System::Int8 isc_dyn_fsp_inactive = System::Int8(0x47);
static const System::Int8 isc_dyn_fsp_page_size = System::Int8(0x48);
static const System::Int8 isc_dyn_fsp_name = System::Int8(0x49);
static const System::Byte isc_dyn_last_dyn_value = System::Byte(0xe3);
static const System::Int8 isc_sdl_version1 = System::Int8(0x1);
static const System::Int8 isc_sdl_eoc = System::Int8(-1);
static const System::Int8 isc_sdl_relation = System::Int8(0x2);
static const System::Int8 isc_sdl_rid = System::Int8(0x3);
static const System::Int8 isc_sdl_field = System::Int8(0x4);
static const System::Int8 isc_sdl_fid = System::Int8(0x5);
static const System::Int8 isc_sdl_struct = System::Int8(0x6);
static const System::Int8 isc_sdl_variable = System::Int8(0x7);
static const System::Int8 isc_sdl_scalar = System::Int8(0x8);
static const System::Int8 isc_sdl_tiny_integer = System::Int8(0x9);
static const System::Int8 isc_sdl_short_integer = System::Int8(0xa);
static const System::Int8 isc_sdl_long_integer = System::Int8(0xb);
static const System::Int8 isc_sdl_literal = System::Int8(0xc);
static const System::Int8 isc_sdl_add = System::Int8(0xd);
static const System::Int8 isc_sdl_subtract = System::Int8(0xe);
static const System::Int8 isc_sdl_multiply = System::Int8(0xf);
static const System::Int8 isc_sdl_divide = System::Int8(0x10);
static const System::Int8 isc_sdl_negate = System::Int8(0x11);
static const System::Int8 isc_sdl_eql = System::Int8(0x12);
static const System::Int8 isc_sdl_neq = System::Int8(0x13);
static const System::Int8 isc_sdl_gtr = System::Int8(0x14);
static const System::Int8 isc_sdl_geq = System::Int8(0x15);
static const System::Int8 isc_sdl_lss = System::Int8(0x16);
static const System::Int8 isc_sdl_leq = System::Int8(0x17);
static const System::Int8 isc_sdl_and = System::Int8(0x18);
static const System::Int8 isc_sdl_or = System::Int8(0x19);
static const System::Int8 isc_sdl_not = System::Int8(0x1a);
static const System::Int8 isc_sdl_while = System::Int8(0x1b);
static const System::Int8 isc_sdl_assignment = System::Int8(0x1c);
static const System::Int8 isc_sdl_label = System::Int8(0x1d);
static const System::Int8 isc_sdl_leave = System::Int8(0x1e);
static const System::Int8 isc_sdl_begin = System::Int8(0x1f);
static const System::Int8 isc_sdl_end = System::Int8(0x20);
static const System::Int8 isc_sdl_do3 = System::Int8(0x21);
static const System::Int8 isc_sdl_do2 = System::Int8(0x22);
static const System::Int8 isc_sdl_do1 = System::Int8(0x23);
static const System::Int8 isc_sdl_element = System::Int8(0x24);
static const System::Int8 isc_interp_eng_ascii = System::Int8(0x0);
static const System::Int8 isc_interp_jpn_sjis = System::Int8(0x5);
static const System::Int8 isc_interp_jpn_euc = System::Int8(0x6);
static const System::Int8 isc_fetch_next = System::Int8(0x0);
static const System::Int8 isc_fetch_prior = System::Int8(0x1);
static const System::Int8 isc_fetch_first = System::Int8(0x2);
static const System::Int8 isc_fetch_last = System::Int8(0x3);
static const System::Int8 isc_fetch_absolute = System::Int8(0x4);
static const System::Int8 isc_fetch_relative = System::Int8(0x5);
static const System::Word SQL_VARYING = System::Word(0x1c0);
static const System::Word SQL_TEXT = System::Word(0x1c4);
static const System::Word SQL_DOUBLE = System::Word(0x1e0);
static const System::Word SQL_FLOAT = System::Word(0x1e2);
static const System::Word SQL_LONG = System::Word(0x1f0);
static const System::Word SQL_SHORT = System::Word(0x1f4);
static const System::Word SQL_TIMESTAMP = System::Word(0x1fe);
static const System::Word SQL_BLOB = System::Word(0x208);
static const System::Word SQL_D_FLOAT = System::Word(0x212);
static const System::Word SQL_ARRAY = System::Word(0x21c);
static const System::Word SQL_QUAD = System::Word(0x226);
static const System::Word SQL_TYPE_TIME = System::Word(0x230);
static const System::Word SQL_TYPE_DATE = System::Word(0x23a);
static const System::Word SQL_INT64 = System::Word(0x244);
static const System::Word SQL_DATE = System::Word(0x1fe);
static const System::Word SQL_BOOLEAN = System::Word(0x24e);
static const System::Int8 isc_blob_untyped = System::Int8(0x0);
static const System::Int8 isc_blob_text = System::Int8(0x1);
static const System::Int8 isc_blob_blr = System::Int8(0x2);
static const System::Int8 isc_blob_acl = System::Int8(0x3);
static const System::Int8 isc_blob_ranges = System::Int8(0x4);
static const System::Int8 isc_blob_summary = System::Int8(0x5);
static const System::Int8 isc_blob_format = System::Int8(0x6);
static const System::Int8 isc_blob_tra = System::Int8(0x7);
static const System::Int8 isc_blob_extfile = System::Int8(0x8);
static const System::Int8 isc_blob_formatted_memo = System::Int8(0x14);
static const System::Int8 isc_blob_paradox_ole = System::Int8(0x15);
static const System::Int8 isc_blob_graphic = System::Int8(0x16);
static const System::Int8 isc_blob_dbase_ole = System::Int8(0x17);
static const System::Int8 isc_blob_typed_binary = System::Int8(0x18);
extern DELPHI_PACKAGE int __fastcall XSQLDA_LENGTH(int n, System::Currency ClientVersion);
extern DELPHI_PACKAGE int __fastcall XSQLVAR_LENGTH(int num_rows, int num_vars);
extern DELPHI_PACKAGE int __fastcall DSC_GET_CHARSET(const TISC_DSC &dsc);
extern DELPHI_PACKAGE int __fastcall DSC_GET_COLLATE(const TISC_DSC &dsc);
extern DELPHI_PACKAGE void __fastcall add_spb_length(System::PByte &p, int length);
extern DELPHI_PACKAGE void __fastcall add_spb_numeric(System::PByte &p, int data);
}	/* namespace Ibheader */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBHEADER)
using namespace Ibx::Ibheader;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbheaderHPP
