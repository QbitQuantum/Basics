// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.IBCli.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_IbcliHPP
#define Firedac_Phys_IbcliHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <FireDAC.Stan.Intf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Ibcli
{
//-- forward type declarations -----------------------------------------------
struct SQUAD;
struct GDS_QUAD;
struct vary;
struct lstring;
struct ISC_TIMESTAMP;
struct TCTimeStructure;
struct ISC_ARRAY_BOUND;
struct ISC_ARRAY_DESC_V1;
struct ISC_BLOB_DESC_V1;
struct ISC_ARRAY_DESC_V2;
struct ISC_BLOB_DESC_V2;
struct ISC_BLOB_CTL;
struct BSTREAM;
struct BLOBCALLBACK;
struct PARAMDSC_V1;
struct PARAMDSC_V2;
struct PARAMVARY;
struct XSQLVAR_V1;
struct XSQLDA_V1;
struct XSQLVAR_V2;
struct XSQLDA_V2;
struct TISCTEB;
struct USER_SEC_DATA;
//-- type declarations -------------------------------------------------------
typedef NativeInt intptr_t;

typedef NativeUInt uintptr_t;

typedef void * api_handle_t;

typedef System::Byte ISC_UCHAR;

typedef System::Int8 ISC_SCHAR;

typedef short ISC_SHORT;

typedef System::Word ISC_USHORT;

typedef short ISC_SSHORT;

typedef int ISC_LONG;

typedef unsigned ISC_ULONG;

typedef int ISC_SLONG;

typedef __int64 ISC_INT64;

typedef unsigned __int64 ISC_UINT64;

typedef System::WordBool ISC_BOOLEAN;

typedef NativeInt ISC_STATUS;

typedef System::StaticArray<NativeInt, 20> TISCStatusVector;

typedef System::StaticArray<unsigned, 20> TISCEventCounts;

struct DECLSPEC_DRECORD SQUAD
{
public:
	int high;
	unsigned low;
};


struct DECLSPEC_DRECORD GDS_QUAD
{
public:
	int gds_quad_high;
	unsigned gds_quad_low;
};


typedef GDS_QUAD ISC_QUAD;

struct DECLSPEC_DRECORD vary
{
public:
	System::Word vary_length;
	System::StaticArray<System::Byte, 1> vary_string;
};


struct DECLSPEC_DRECORD lstring
{
public:
	unsigned lstr_length;
	unsigned lstr_allocated;
	System::Byte *lstr_address;
};


typedef System::Byte *PISC_UCHAR;

typedef System::Int8 *PISC_SCHAR;

typedef PISC_SCHAR *PPISC_SCHAR;

typedef short *PISC_SHORT;

typedef int *PISC_LONG;

typedef unsigned *PISC_ULONG;

typedef System::WordBool *PISC_BOOLEAN;

typedef NativeInt *PISC_STATUS;

typedef GDS_QUAD *PGDS_QUAD;

typedef GDS_QUAD *PISC_QUAD;

typedef vary *Pvary;

typedef lstring *Plstring;

typedef System::StaticArray<System::Int8, 6> FB_SQLSTATE_STRING;

typedef int ISC_DATE;

typedef int *PISC_DATE;

typedef unsigned ISC_TIME;

typedef unsigned *PISC_TIME;

typedef ISC_TIMESTAMP *PISC_TIMESTAMP;

struct DECLSPEC_DRECORD ISC_TIMESTAMP
{
public:
	int timestamp_date;
	unsigned timestamp_time;
};


struct DECLSPEC_DRECORD TCTimeStructure
{
public:
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
#ifndef __x86_64__
	int tm_gmtoff;
#else /* __x86_64__ */
	long tm_gmtoff;
#endif /* __x86_64__ */
	System::Byte *rm_zone;
};


typedef TCTimeStructure *PCTimeStructure;

typedef ISC_ARRAY_BOUND *PISC_ARRAY_BOUND;

struct DECLSPEC_DRECORD ISC_ARRAY_BOUND
{
public:
	short array_bound_lower;
	short array_bound_upper;
};


typedef System::StaticArray<ISC_ARRAY_BOUND, 16> TISC_ARRAY_BOUNDs;

typedef TISC_ARRAY_BOUNDs *PISC_ARRAY_BOUNDs;

typedef void * PISC_ARRAY_DESC;

typedef void * PISC_BLOB_DESC;

typedef ISC_ARRAY_DESC_V1 *PISC_ARRAY_DESC_V1;

struct DECLSPEC_DRECORD ISC_ARRAY_DESC_V1
{
public:
	System::Byte array_desc_dtype;
	System::Int8 array_desc_scale;
	System::Word array_desc_length;
	System::StaticArray<System::Int8, 32> array_desc_field_name;
	System::StaticArray<System::Int8, 32> array_desc_relation_name;
	short array_desc_dimensions;
	short array_desc_flags;
	TISC_ARRAY_BOUNDs array_desc_bounds;
};


typedef ISC_BLOB_DESC_V1 *PISC_BLOB_DESC_V1;

struct DECLSPEC_DRECORD ISC_BLOB_DESC_V1
{
public:
	short blob_desc_subtype;
	short blob_desc_charset;
	short blob_desc_segment_size;
	System::StaticArray<System::Byte, 32> blob_desc_field_name;
	System::StaticArray<System::Byte, 32> blob_desc_relation_name;
};


typedef ISC_ARRAY_DESC_V2 *PISC_ARRAY_DESC_V2;

struct DECLSPEC_DRECORD ISC_ARRAY_DESC_V2
{
public:
	short array_desc_version;
	System::Byte array_desc_dtype;
	System::Byte array_desc_subtype;
	System::Int8 array_desc_scale;
	System::Word array_desc_length;
	System::StaticArray<System::Int8, 68> array_desc_field_name;
	System::StaticArray<System::Int8, 68> array_desc_relation_name;
	short array_desc_dimensions;
	short array_desc_flags;
	TISC_ARRAY_BOUNDs array_desc_bounds;
};


typedef ISC_BLOB_DESC_V2 *PISC_BLOB_DESC_V2;

struct DECLSPEC_DRECORD ISC_BLOB_DESC_V2
{
public:
	short blob_desc_version;
	short blob_desc_subtype;
	short blob_desc_charset;
	short blob_desc_segment_size;
	System::StaticArray<System::Byte, 68> blob_desc_field_name;
	System::StaticArray<System::Byte, 68> blob_desc_relation_name;
};


typedef ISC_BLOB_CTL *PISC_BLOB_CTL;

typedef NativeInt __cdecl (*TISCStatusFn)(System::Word Action, PISC_BLOB_CTL Control);

struct DECLSPEC_DRECORD ISC_BLOB_CTL
{
public:
	TISCStatusFn ctl_source;
	ISC_BLOB_CTL *ctl_source_handle;
	short ctl_to_sub_type;
	short ctl_from_sub_type;
	System::Word ctl_buffer_length;
	System::Word ctl_segment_length;
	System::Word ctl_bpb_length;
	System::Int8 *ctl_bpb;
	System::Byte *ctl_buffer;
	int ctl_max_segment;
	int ctl_number_segments;
	int ctl_total_length;
	NativeInt *ctl_status;
	System::StaticArray<NativeInt, 8> ctl_data;
};


typedef BSTREAM *PBSTREAM;

struct DECLSPEC_DRECORD BSTREAM
{
public:
	void *bstr_blob;
	System::Int8 *bstr_buffer;
	System::Int8 *bstr_ptr;
	short bstr_length;
	short bstr_cnt;
	System::Int8 bstr_mode;
};


typedef short __stdcall (*TBlobGetSegmentFn)(void * hnd, PISC_UCHAR buffer, System::Word buf_size, System::Word &result_len);

typedef void __stdcall (*TBlobPutSegmentFn)(void * hnd, PISC_UCHAR buffer, System::Word buf_size);

typedef int __stdcall (*TBlobLSeekFn)(void * hnd, System::Word mode, int offset);

typedef BLOBCALLBACK *PBLOBCALLBACK;

struct DECLSPEC_DRECORD BLOBCALLBACK
{
public:
	TBlobGetSegmentFn blob_get_segment;
	void *blob_handle;
	int blob_number_segments;
	int blob_max_segment;
	int blob_total_length;
	TBlobPutSegmentFn blob_put_segment;
	TBlobLSeekFn blob_lseek;
};


typedef PARAMDSC_V1 *PPARAMDSC_V1;

struct DECLSPEC_DRECORD PARAMDSC_V1
{
public:
	System::Byte dsc_dtype;
	System::Int8 dsc_scale;
	System::Word dsc_length;
	short dsc_sub_type;
	System::Word dsc_flags;
	System::Byte *dsc_address;
};


typedef PARAMDSC_V2 *PPARAMDSC_V2;

struct DECLSPEC_DRECORD PARAMDSC_V2
{
public:
	System::Byte dsc_version;
	System::Byte dsc_dtype;
	System::Int8 dsc_scale;
	System::Int8 dsc_precision;
	System::Word dsc_length;
	short dsc_sub_type;
	System::Word dsc_flags;
	System::Byte *dsc_address;
};


typedef PARAMVARY *PPARAMVARY;

struct DECLSPEC_DRECORD PARAMVARY
{
public:
	System::Word vary_length;
	System::StaticArray<System::Byte, 1> vary_string;
};


typedef XSQLVAR_V1 *PXSQLVAR_V1;

struct DECLSPEC_DRECORD XSQLVAR_V1
{
public:
	short sqltype;
	short sqlscale;
	short sqlsubtype;
	short sqllen;
	System::Int8 *sqldata;
	short *sqlind;
	short sqlname_length;
	System::StaticArray<System::Int8, 32> sqlname;
	short relname_length;
	System::StaticArray<System::Int8, 32> relname;
	short ownname_length;
	System::StaticArray<System::Int8, 32> ownname;
	short aliasname_length;
	System::StaticArray<System::Int8, 32> aliasname;
};


typedef XSQLDA_V1 *PXSQLDA_V1;

struct DECLSPEC_DRECORD XSQLDA_V1
{
public:
	short version;
	System::StaticArray<System::Int8, 8> sqldaid;
	int sqldabc;
	short sqln;
	short sqld;
	System::StaticArray<XSQLVAR_V1, 1> sqlvar;
};


typedef XSQLVAR_V2 *PXSQLVAR_V2;

typedef PXSQLVAR_V2 *PPXSQLVAR_V2;

struct DECLSPEC_DRECORD XSQLVAR_V2
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
	System::StaticArray<System::Int8, 68> sqlname;
	short relname_length;
	System::StaticArray<System::Int8, 68> relname;
	short ownname_length;
	System::StaticArray<System::Int8, 68> ownname;
	short aliasname_length;
	System::StaticArray<System::Int8, 68> aliasname;
};


typedef XSQLDA_V2 *PXSQLDA_V2;

struct DECLSPEC_DRECORD XSQLDA_V2
{
public:
	short version;
	System::StaticArray<System::Int8, 8> sqldaid;
	int sqldabc;
	short sqln;
	short sqld;
	System::StaticArray<XSQLVAR_V2, 1> sqlvar;
};


typedef void * PXSQLDA;

typedef void * PXSQLVar;

typedef void * isc_att_handle;

typedef void * *Pisc_att_handle;

typedef void * isc_blob_handle;

typedef void * *Pisc_blob_handle;

typedef void * isc_db_handle;

typedef void * *Pisc_db_handle;

typedef void * isc_form_handle;

typedef void * *Pisc_form_handle;

typedef void * isc_req_handle;

typedef void * *Pisc_req_handle;

typedef void * isc_stmt_handle;

typedef void * *Pisc_stmt_handle;

typedef void * isc_svc_handle;

typedef void * *Pisc_svc_handle;

typedef void * isc_tr_handle;

typedef void * *Pisc_tr_handle;

typedef void __fastcall (*isc_callback)(void);

typedef int isc_resv_handle;

typedef int *Pisc_resv_handle;

typedef TISCTEB *PISCTEB;

struct DECLSPEC_DRECORD TISCTEB
{
public:
	void * *Handle;
	int Len;
	System::Byte *Address;
};


struct DECLSPEC_DRECORD USER_SEC_DATA
{
public:
	short sec_flags;
	int uid;
	int gid;
	int protocol;
	System::Int8 *server;
	System::Int8 *user_name;
	System::Int8 *password;
	System::Int8 *group_name;
	System::Int8 *first_name;
	System::Int8 *middle_name;
	System::Int8 *last_name;
	System::Int8 *dba_user_name;
	System::Int8 *dba_password;
};


typedef USER_SEC_DATA *PUSER_SEC_DATA;

typedef int __cdecl (*FB_SHUTDOWN_CALLBACK_FUNC)(int reason, int mask, void * arg);

typedef int __cdecl (*TBLOB_close)(PBSTREAM Stream);

typedef int __cdecl (*TBLOB_display)(PISC_QUAD blob_id, void * database, void * transaction, PISC_SCHAR field_name);

typedef int __cdecl (*TBLOB_dump)(PISC_QUAD blob_id, void * database, void * transaction, PISC_SCHAR file_name);

typedef int __cdecl (*TBLOB_edit)(PISC_QUAD blob_id, void * database, void * transaction, PISC_SCHAR field_name);

typedef int __cdecl (*TBLOB_get)(PBSTREAM Stream);

typedef int __cdecl (*TBLOB_load)(PISC_QUAD blob_id, void * database, void * transaction, PISC_SCHAR file_name);

typedef PBSTREAM __cdecl (*TBLOB_open)(void * blob, PISC_SCHAR buffer, int length);

typedef int __cdecl (*TBLOB_put)(System::Int8 x, PBSTREAM Stream);

typedef int __cdecl (*TBLOB_text_dump)(PISC_QUAD blob_id, void * database, void * transaction, PISC_SCHAR file_name);

typedef int __cdecl (*TBLOB_text_load)(PISC_QUAD blob_id, void * database, void * transaction, PISC_SCHAR file_name);

typedef PBSTREAM __cdecl (*TBopen)(PISC_QUAD blob_id, void * database, void * transaction, PISC_SCHAR mode);

typedef NativeInt __cdecl (*Tisc_add_user)(PISC_STATUS status, PUSER_SEC_DATA user_data);

typedef NativeInt __cdecl (*Tisc_array_gen_sdl)(PISC_STATUS status, PISC_ARRAY_DESC_V1 desc, PISC_SHORT sdl_buffer_length, PISC_UCHAR sdl_buffer, PISC_SHORT sdl_length);

typedef NativeInt __cdecl (*Tisc_array_get_slice)(PISC_STATUS status, Pisc_db_handle db_handle, Pisc_tr_handle trans_handle, PISC_QUAD array_id, PISC_ARRAY_DESC_V1 desc, void * array_, PISC_LONG slice_length);

typedef NativeInt __cdecl (*Tisc_array_lookup_bounds)(PISC_STATUS status, Pisc_db_handle db_handle, Pisc_tr_handle trans_handle, PISC_SCHAR relation_name, PISC_SCHAR field_name, PISC_ARRAY_DESC_V1 desc);

typedef NativeInt __cdecl (*Tisc_array_lookup_desc)(PISC_STATUS status, Pisc_db_handle db_handle, Pisc_tr_handle trans_handle, PISC_SCHAR relation_name, PISC_SCHAR field_name, PISC_ARRAY_DESC_V1 desc);

typedef NativeInt __cdecl (*Tisc_array_put_slice)(PISC_STATUS status, Pisc_db_handle db_handle, Pisc_tr_handle trans_handle, PISC_QUAD array_id, PISC_ARRAY_DESC_V1 desc, void * array_, PISC_LONG slice_length);

typedef NativeInt __cdecl (*Tisc_array_set_desc)(PISC_STATUS status, PISC_SCHAR relation_name, PISC_SCHAR field_name, System::PSmallInt sql_dtype, System::PSmallInt sql_length, System::PSmallInt dimensions, PISC_ARRAY_DESC_V1 desc);

typedef NativeInt __cdecl (*Tisc_array_gen_sdl2)(PISC_STATUS status, PISC_ARRAY_DESC_V2 desc, PISC_SHORT sdl_buffer_length, PISC_UCHAR sdl_buffer, PISC_SHORT sdl_length);

typedef NativeInt __cdecl (*Tisc_array_get_slice2)(PISC_STATUS status, Pisc_db_handle db_handle, Pisc_tr_handle trans_handle, PISC_QUAD array_id, PISC_ARRAY_DESC_V2 desc, void * array_, PISC_LONG slice_length);

typedef NativeInt __cdecl (*Tisc_array_lookup_bounds2)(PISC_STATUS status, Pisc_db_handle db_handle, Pisc_tr_handle trans_handle, PISC_SCHAR relation_name, PISC_SCHAR field_name, PISC_ARRAY_DESC_V2 desc);

typedef NativeInt __cdecl (*Tisc_array_lookup_desc2)(PISC_STATUS status, Pisc_db_handle db_handle, Pisc_tr_handle trans_handle, PISC_SCHAR relation_name, PISC_SCHAR field_name, PISC_ARRAY_DESC_V2 desc);

typedef NativeInt __cdecl (*Tisc_array_put_slice2)(PISC_STATUS status, Pisc_db_handle db_handle, Pisc_tr_handle trans_handle, PISC_QUAD array_id, PISC_ARRAY_DESC_V2 desc, void * array_, PISC_LONG slice_length);

typedef NativeInt __cdecl (*Tisc_array_set_desc2)(PISC_STATUS status, PISC_SCHAR relation_name, PISC_SCHAR field_name, System::PSmallInt sql_dtype, System::PSmallInt sql_length, System::PSmallInt dimensions, PISC_ARRAY_DESC_V2 desc);

typedef NativeInt __cdecl (*Tisc_attach_database)(PISC_STATUS user_status, short file_length, PISC_SCHAR file_name, Pisc_db_handle handle, short dpb_length, PISC_SCHAR dpb);

typedef void __cdecl (*Tisc_blob_default_desc)(void * desc, PISC_UCHAR relation_name, PISC_UCHAR field_name);

typedef NativeInt __cdecl (*Tisc_blob_gen_bpb)(PISC_STATUS status, void * to_desc, void * from_desc, System::Word bpb_buffer_length, PISC_UCHAR bpb_buffer, System::Word &bpb_length);

typedef NativeInt __cdecl (*Tisc_blob_info)(PISC_STATUS user_status, Pisc_blob_handle blob_handle, short item_length, PISC_SCHAR items, short buffer_length, PISC_SCHAR buffer);

typedef NativeInt __cdecl (*Tisc_blob_lookup_desc)(PISC_STATUS status, Pisc_db_handle db_handle, Pisc_tr_handle trans_handle, PISC_UCHAR relation_name, PISC_UCHAR field_name, void * desc, PISC_UCHAR global);

typedef NativeInt __cdecl (*Tisc_blob_set_desc)(PISC_STATUS status, PISC_UCHAR relation_name, PISC_UCHAR field_name, short subtype, short charset, short segment_size, void * desc);

typedef NativeInt __cdecl (*Tisc_cancel_blob)(PISC_STATUS user_status, Pisc_blob_handle blob_handle);

typedef NativeInt __cdecl (*Tisc_cancel_events)(PISC_STATUS user_status, Pisc_db_handle handle, PISC_LONG id);

typedef NativeInt __cdecl (*Tisc_close)(PISC_STATUS user_status, PISC_SCHAR name);

typedef NativeInt __cdecl (*Tisc_close_blob)(PISC_STATUS user_status, Pisc_blob_handle blob_handle);

typedef NativeInt __cdecl (*Tisc_commit_retaining)(PISC_STATUS user_status, Pisc_tr_handle tra_handle);

typedef NativeInt __cdecl (*Tisc_commit_transaction)(PISC_STATUS user_status, Pisc_tr_handle tra_handle);

typedef NativeInt __cdecl (*Tisc_compile_request)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_req_handle req_handle, short blr_length, PISC_SCHAR blr);

typedef NativeInt __cdecl (*Tisc_compile_request2)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_req_handle req_handle, short blr_length, PISC_SCHAR blr);

typedef NativeInt __cdecl (*Tisc_create_blob)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle tra_handle, Pisc_blob_handle blob_handle, PISC_QUAD blob_id);

typedef NativeInt __cdecl (*Tisc_create_blob2)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle tra_handle, Pisc_blob_handle blob_handle, PISC_QUAD blob_id, short bpb_length, PISC_SCHAR bpb);

typedef NativeInt __cdecl (*Tisc_create_database)(PISC_STATUS user_status, short file_length, PISC_SCHAR file_name, Pisc_db_handle handle, short dpb_length, PISC_SCHAR dpb, short db_type);

typedef NativeInt __cdecl (*Tisc_database_info)(PISC_STATUS user_status, Pisc_db_handle handle, short item_length, PISC_SCHAR items, short buffer_length, PISC_SCHAR buffer);

typedef NativeInt __cdecl (*Tisc_ddl)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle tra_handle, short length, PISC_SCHAR ddl);

typedef NativeInt __cdecl (*Tisc_declare)(PISC_STATUS user_status, PISC_SCHAR statement, PISC_SCHAR cursor);

typedef void __cdecl (*Tisc_decode_date)(PISC_QUAD date, PCTimeStructure times_arg);

typedef void __cdecl (*Tisc_decode_sql_date)(PISC_DATE date, PCTimeStructure times_arg);

typedef void __cdecl (*Tisc_decode_sql_time)(PISC_TIME sql_time, PCTimeStructure times_arg);

typedef void __cdecl (*Tisc_decode_timestamp)(PISC_TIMESTAMP date, PCTimeStructure times_arg);

typedef NativeInt __cdecl (*Tisc_delete_user)(PISC_STATUS status, PUSER_SEC_DATA user_data);

typedef NativeInt __cdecl (*Tisc_describe)(PISC_STATUS user_status, PISC_SCHAR name, void * sqlda);

typedef NativeInt __cdecl (*Tisc_describe_bind)(PISC_STATUS user_status, PISC_SCHAR name, void * sqlda);

typedef NativeInt __cdecl (*Tisc_detach_database)(PISC_STATUS user_status, Pisc_db_handle handle);

typedef NativeInt __cdecl (*Tisc_drop_database)(PISC_STATUS user_status, Pisc_db_handle handle);

typedef NativeInt __cdecl (*Tisc_dsql_alloc_statement2)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_stmt_handle stmt_handle);

typedef NativeInt __cdecl (*Tisc_dsql_allocate_statement)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_stmt_handle stmt_handle);

typedef NativeInt __cdecl (*Tisc_dsql_describe)(PISC_STATUS user_status, Pisc_stmt_handle stmt_handle, System::Word dialect, void * sqlda);

typedef NativeInt __cdecl (*Tisc_dsql_describe_bind)(PISC_STATUS user_status, Pisc_stmt_handle stmt_handle, System::Word dialect, void * sqlda);

typedef NativeInt __cdecl (*Tisc_dsql_exec_immed2)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle tra_handle, System::Word length, PISC_SCHAR statement, System::Word dialect, void * in_sqlda, void * out_sqlda);

typedef NativeInt __cdecl (*Tisc_dsql_exec_immed3_m)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle tra_handle, System::Word Length, PISC_SCHAR statement, System::Word dialect, System::Word in_blr_length, PISC_SCHAR in_blr, System::Word in_msg_type, System::Word in_msg_length, PISC_SCHAR in_msg, System::Word out_blr_length, PISC_SCHAR out_blr, System::Word out_msg_type, System::Word out_msg_length, PISC_SCHAR out_msg);

typedef NativeInt __cdecl (*Tisc_dsql_execute)(PISC_STATUS user_status, Pisc_tr_handle tra_handle, Pisc_stmt_handle stmt_handle, System::Word dialect, void * sqlda);

typedef NativeInt __cdecl (*Tisc_dsql_execute_immediate)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle tra_handle, System::Word length, PISC_SCHAR statement, System::Word dialect, void * sqlda);

typedef NativeInt __cdecl (*Tisc_dsql_execute_immediate_m)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle tra_handle, System::Word length, PISC_SCHAR statement, System::Word dialect, System::Word blr_length, PISC_SCHAR blr, System::Word msg_type, System::Word msg_length, PISC_SCHAR msg);

typedef NativeInt __cdecl (*Tisc_dsql_execute_m)(PISC_STATUS user_status, Pisc_tr_handle tra_handle, Pisc_stmt_handle stmt_handle, System::Word blr_length, PISC_SCHAR blr, System::Word msg_type, System::Word msg_length, PISC_SCHAR msg);

typedef NativeInt __cdecl (*Tisc_dsql_execute2)(PISC_STATUS user_status, Pisc_tr_handle tra_handle, Pisc_stmt_handle stmt_handle, System::Word dialect, void * in_sqlda, void * out_sqlda);

typedef NativeInt __cdecl (*Tisc_dsql_execute2_m)(PISC_STATUS user_status, Pisc_tr_handle tra_handle, Pisc_stmt_handle stmt_handle, System::Word in_blr_length, PISC_SCHAR in_blr, System::Word in_msg_type, System::Word in_msg_length, PISC_SCHAR in_msg, System::Word out_blr_length, PISC_SCHAR out_blr, System::Word out_msg_type, System::Word out_msg_length, PISC_SCHAR out_msg);

typedef NativeInt __cdecl (*Tisc_dsql_fetch)(PISC_STATUS user_status, Pisc_stmt_handle stmt_handle, System::Word dialect, void * sqlda);

typedef NativeInt __cdecl (*Tisc_dsql_fetch_m)(PISC_STATUS user_status, Pisc_stmt_handle stmt_handle, System::Word blr_length, PISC_SCHAR blr, System::Word msg_type, System::Word msg_length, PISC_SCHAR msg);

typedef NativeInt __cdecl (*Tisc_dsql_finish)(Pisc_db_handle db_handle);

typedef NativeInt __cdecl (*Tisc_dsql_free_statement)(PISC_STATUS user_status, Pisc_stmt_handle stmt_handle, System::Word option);

typedef NativeInt __cdecl (*Tisc_dsql_insert)(PISC_STATUS user_status, Pisc_stmt_handle stmt_handle, System::Word dialect, void * sqlda);

typedef NativeInt __cdecl (*Tisc_dsql_insert_m)(PISC_STATUS user_status, Pisc_stmt_handle stmt_handle, System::Word blr_length, PISC_SCHAR blr, System::Word msg_type, System::Word msg_length, PISC_SCHAR msg);

typedef NativeInt __cdecl (*Tisc_dsql_prepare)(PISC_STATUS user_status, Pisc_tr_handle tra_handle, Pisc_stmt_handle stmt_handle, System::Word length, PISC_SCHAR string_, System::Word dialect, void * sqlda);

typedef NativeInt __cdecl (*Tisc_dsql_prepare_m)(PISC_STATUS user_status, Pisc_tr_handle tra_handle, Pisc_stmt_handle stmt_handle, System::Word length, PISC_SCHAR string_, System::Word dialect, System::Word item_length, PISC_SCHAR items, System::Word buffer_length, PISC_SCHAR buffer);

typedef NativeInt __cdecl (*Tisc_dsql_release)(PISC_STATUS user_status, PISC_SCHAR name);

typedef NativeInt __cdecl (*Tisc_dsql_set_cursor_name)(PISC_STATUS user_status, Pisc_stmt_handle stmt_handle, PISC_SCHAR cursor, System::Word type_);

typedef NativeInt __cdecl (*Tisc_dsql_sql_info)(PISC_STATUS user_status, Pisc_stmt_handle stmt_handle, short item_length, PISC_SCHAR items, short buffer_length, PISC_SCHAR buffer);

typedef NativeInt __cdecl (*Tisc_embed_dsql_close)(PISC_STATUS user_status, PISC_SCHAR name);

typedef NativeInt __cdecl (*Tisc_embed_dsql_declare)(PISC_STATUS user_status, PISC_SCHAR stmt_name, PISC_SCHAR cursor);

typedef NativeInt __cdecl (*Tisc_embed_dsql_describe)(PISC_STATUS user_status, PISC_SCHAR stmt_name, System::Word dialect, void * sqlda);

typedef NativeInt __cdecl (*Tisc_embed_dsql_describe_bind)(PISC_STATUS user_status, PISC_SCHAR stmt_name, System::Word dialect, void * sqlda);

typedef NativeInt __cdecl (*Tisc_embed_dsql_execute)(PISC_STATUS user_status, Pisc_tr_handle trans_handle, PISC_SCHAR stmt_name, System::Word dialect, void * sqlda);

typedef NativeInt __cdecl (*Tisc_embed_dsql_execute_immed)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle trans_handle, System::Word length, PISC_SCHAR string_, System::Word dialect, void * sqlda);

typedef NativeInt __cdecl (*Tisc_embed_dsql_execute2)(PISC_STATUS user_status, Pisc_tr_handle trans_handle, PISC_SCHAR stmt_name, System::Word dialect, void * in_sqlda, void * out_sqlda);

typedef NativeInt __cdecl (*Tisc_embed_dsql_fetch)(PISC_STATUS user_status, PISC_SCHAR cursor_name, System::Word dialect, void * sqlda);

typedef NativeInt __cdecl (*Tisc_embed_dsql_insert)(PISC_STATUS user_status, PISC_SCHAR cursor_name, System::Word dialect, void * sqlda);

typedef NativeInt __cdecl (*Tisc_embed_dsql_open)(PISC_STATUS user_status, Pisc_tr_handle trans_handle, PISC_SCHAR cursor_name, System::Word dialect, void * sqlda);

typedef NativeInt __cdecl (*Tisc_embed_dsql_open2)(PISC_STATUS user_status, Pisc_tr_handle trans_handle, PISC_SCHAR cursor_name, System::Word dialect, void * in_sqlda, void * out_sqlda);

typedef NativeInt __cdecl (*Tisc_embed_dsql_prepare)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle trans_handle, PISC_SCHAR stmt_name, System::Word length, PISC_SCHAR string_, System::Word dialect, void * sqlda);

typedef NativeInt __cdecl (*Tisc_embed_dsql_release)(PISC_STATUS user_status, PISC_SCHAR stmt_name);

typedef void __cdecl (*Tisc_encode_date)(PCTimeStructure times_arg, PISC_QUAD date);

typedef void __cdecl (*Tisc_encode_sql_date)(PCTimeStructure times_arg, PISC_DATE date);

typedef void __cdecl (*Tisc_encode_sql_time)(PCTimeStructure times_arg, PISC_TIME time);

typedef void __cdecl (*Tisc_encode_timestamp)(PCTimeStructure times_arg, PISC_TIMESTAMP timestamp);

typedef int __cdecl (*Tisc_event_block)(PISC_UCHAR &event_buffer, PISC_UCHAR &result_buffer, System::Word count, ...);

typedef void __cdecl (*Tisc_event_counts)(PISC_STATUS ser_status, short buffer_length, PISC_UCHAR event_buffer, PISC_UCHAR result_buffer);

typedef NativeInt __cdecl (*Tisc_execute)(PISC_STATUS user_status, Pisc_tr_handle trans_handle, PISC_SCHAR name, void * sqlda);

typedef NativeInt __cdecl (*Tisc_execute_immediate)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle trans_handle, System::PSmallInt length, PISC_SCHAR string_);

typedef void __cdecl (*Tisc_expand_dpb)(PPISC_SCHAR dpb, System::PSmallInt dpb_size, PPISC_SCHAR name_buffer);

typedef NativeInt __cdecl (*Tisc_fetch)(PISC_STATUS user_status, PISC_SCHAR name, void * sqlda);

typedef int __cdecl (*Tisc_free)(void * blk);

typedef int __cdecl (*Tisc_ftof)(PISC_SCHAR string_, System::Word length1, PISC_SCHAR field, System::Word length2);

typedef NativeInt __cdecl (*Tisc_get_segment)(PISC_STATUS user_status, Pisc_blob_handle blob_handle, System::Word &length, System::Word buffer_length, PISC_SCHAR buffer);

typedef NativeInt __cdecl (*Tisc_get_slice)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle tra_handle, PISC_QUAD array_id, short sdl_length, PISC_SCHAR sdl, short param_length, PISC_LONG param, int slice_length, void * slice, PISC_LONG return_length);

typedef NativeInt __cdecl (*Tisc_interprete)(PISC_SCHAR buffer, PISC_STATUS &status_vector);

typedef int __cdecl (*Tfb_interpret)(PISC_SCHAR buffer, unsigned v, PISC_STATUS &status_vector);

typedef int __cdecl (*Tisc_modify_dpb)(PPISC_SCHAR dpb, System::PSmallInt dpb_length, System::Word type_, PISC_SCHAR str, short str_len);

typedef NativeInt __cdecl (*Tisc_modify_user)(PISC_STATUS status, PUSER_SEC_DATA user_data);

typedef NativeInt __cdecl (*Tisc_open)(PISC_STATUS user_status, Pisc_tr_handle trans_handle, PISC_SCHAR name, void * sqlda);

typedef NativeInt __cdecl (*Tisc_open_blob)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle tra_handle, Pisc_blob_handle blob_handle, PISC_QUAD blob_id);

typedef NativeInt __cdecl (*Tisc_open_blob2)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle tra_handle, Pisc_blob_handle blob_handle, PISC_QUAD blob_id, System::Word bpb_length, PISC_UCHAR bpb);

typedef __int64 __cdecl (*Tisc_portable_integer)(PISC_UCHAR ptr, short length);

typedef NativeInt __cdecl (*Tisc_prepare)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle trans_handle, PISC_SCHAR name, System::PSmallInt length, PISC_SCHAR string_, void * sqlda);

typedef NativeInt __cdecl (*Tisc_prepare_transaction)(PISC_STATUS user_status, Pisc_tr_handle tra_handle);

typedef NativeInt __cdecl (*Tisc_prepare_transaction2)(PISC_STATUS user_status, Pisc_tr_handle tra_handle, System::Word msg_length, PISC_UCHAR msg);

typedef NativeInt __cdecl (*Tisc_print_blr)(PISC_SCHAR blr, isc_callback callback, void * callback_argument, short language);

typedef void __cdecl (*Tisc_print_sqlerror)(short sqlcode, PISC_STATUS status_vector);

typedef NativeInt __cdecl (*Tisc_print_status)(PISC_STATUS status_vector);

typedef NativeInt __cdecl (*Tisc_put_segment)(PISC_STATUS user_status, Pisc_blob_handle blob_handle, System::Word buffer_length, PISC_SCHAR buffer);

typedef NativeInt __cdecl (*Tisc_put_slice)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle tra_handle, PISC_QUAD array_id, short sdl_length, PISC_SCHAR sdl, short param_length, PISC_LONG param, int slice_length, void * slice);

typedef void __cdecl (*Tisc_qtoq)(PISC_QUAD quad1, PISC_QUAD quad2);

typedef NativeInt __cdecl (*Tisc_que_events)(PISC_STATUS user_status, Pisc_db_handle handle, PISC_LONG id, short length, PISC_UCHAR events, isc_callback ast, void * arg);

typedef NativeInt __cdecl (*Tisc_receive)(PISC_STATUS user_status, Pisc_req_handle req_handle, short msg_type, short msg_length, void * msg, short level);

typedef NativeInt __cdecl (*Tisc_reconnect_transaction)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle tra_handle, short length, PISC_SHORT id);

typedef NativeInt __cdecl (*Tisc_release_request)(PISC_STATUS user_status, Pisc_req_handle req_handle);

typedef NativeInt __cdecl (*Tisc_request_info)(PISC_STATUS user_status, Pisc_req_handle req_handle, short level, short item_length, PISC_SCHAR items, short buffer_length, PISC_SCHAR buffer);

typedef NativeInt __cdecl (*Tisc_rollback_retaining)(PISC_STATUS status_vector, Pisc_tr_handle trans_handle);

typedef NativeInt __cdecl (*Tisc_rollback_transaction)(PISC_STATUS user_status, Pisc_tr_handle tra_handle);

typedef NativeInt __cdecl (*Tisc_seek_blob)(PISC_STATUS user_status, Pisc_blob_handle blob_handle, short mode, int offset, PISC_LONG Result_);

typedef NativeInt __cdecl (*Tisc_send)(PISC_STATUS user_status, Pisc_req_handle req_handle, short msg_type, short msg_length, void * msg, short level);

typedef NativeInt __cdecl (*Tisc_service_attach)(PISC_STATUS status_vector, System::Word service_length, PISC_SCHAR service_name, Pisc_svc_handle handle, System::Word spb_length, PISC_SCHAR spb);

typedef NativeInt __cdecl (*Tisc_service_detach)(PISC_STATUS status_vector, Pisc_svc_handle handle);

typedef NativeInt __cdecl (*Tisc_service_query)(PISC_STATUS status_vector, Pisc_svc_handle svc_handle, Pisc_resv_handle reserved, System::Word send_spb_length, PISC_SCHAR send_spb, System::Word request_spb_length, PISC_SCHAR request_spb, System::Word buffer_length, PISC_SCHAR buffer);

typedef NativeInt __cdecl (*Tisc_service_start)(PISC_STATUS status_vector, Pisc_svc_handle svc_handle, Pisc_resv_handle reserved, System::Word spb_length, PISC_SCHAR spb);

typedef void __cdecl (*Tisc_set_debug)(int flag);

typedef void __cdecl (*Tisc_sql_interprete)(short SQLCODE, PISC_SCHAR buffer, short buffer_length);

typedef int __cdecl (*Tisc_sqlcode)(PISC_STATUS user_status);

typedef NativeInt __cdecl (*Tisc_start_and_send)(PISC_STATUS user_status, Pisc_req_handle req_handle, Pisc_tr_handle tra_handle, short msg_type, short msg_length, void * msg, short level);

typedef NativeInt __cdecl (*Tisc_start_multiple)(PISC_STATUS user_status, Pisc_tr_handle tra_handle, short count, PISCTEB vector);

typedef NativeInt __cdecl (*Tisc_start_request)(PISC_STATUS user_status, Pisc_req_handle req_handle, Pisc_tr_handle tra_handle, short level);

typedef NativeInt __cdecl (*Tisc_start_transaction)(PISC_STATUS user_status, Pisc_tr_handle tra_handle, short count, Pisc_db_handle db_handle, System::Word tpb_length, PISC_SCHAR tpb_ad);

typedef NativeInt __cdecl (*Tisc_transact_request)(PISC_STATUS user_status, Pisc_db_handle db_handle, Pisc_tr_handle tra_handle, System::Word blr_length, PISC_SCHAR blr, System::Word in_msg_length, PISC_SCHAR in_msg, System::Word out_msg_length, PISC_SCHAR out_msg);

typedef NativeInt __cdecl (*Tisc_transaction_info)(PISC_STATUS user_status, Pisc_tr_handle tra_handle, short item_length, PISC_SCHAR items, short buffer_length, PISC_SCHAR buffer);

typedef NativeInt __cdecl (*Tisc_unwind_request)(PISC_STATUS user_status, Pisc_tr_handle req_handle, short level);

typedef int __cdecl (*Tisc_vax_integer)(PISC_SCHAR ptr, short length);

typedef int __cdecl (*Tisc_version)(Pisc_db_handle db_handle, isc_callback callback, void * callback_argument);

typedef void __cdecl (*Tisc_vtof)(PISC_SCHAR string1, PISC_SCHAR string2, System::Word length);

typedef void __cdecl (*Tisc_vtov)(PISC_SCHAR string1, PISC_SCHAR string2, short length);

typedef NativeInt __cdecl (*Tisc_wait_for_event)(PISC_STATUS user_status, Pisc_db_handle handle, short length, PISC_UCHAR events, PISC_UCHAR buffer);

typedef int __cdecl (*Tisc_reset_fpe)(System::Word fpe_status);

typedef void __cdecl (*Tisc_get_client_version)(PISC_SCHAR version);

typedef int __cdecl (*Tisc_get_client_major_version)(void);

typedef int __cdecl (*Tisc_get_client_minor_version)(void);

typedef NativeInt __cdecl (*Tisc_release_savepoint)(PISC_STATUS status, Pisc_tr_handle TrHandle, PISC_SCHAR name);

typedef NativeInt __cdecl (*Tisc_rollback_savepoint)(PISC_STATUS status, Pisc_tr_handle TrHandle, PISC_SCHAR name, System::Word Option);

typedef NativeInt __cdecl (*Tisc_start_savepoint)(PISC_STATUS status, Pisc_tr_handle TrHandle, PISC_SCHAR name);

typedef NativeInt __cdecl (*Tisc_dsql_batch_execute)(PISC_STATUS status, Pisc_tr_handle TrHandle, Pisc_stmt_handle stmt_handle, System::Word dialect, void * insqlda, System::Word number_of_rows, PXSQLVAR_V2 batch_vars, PISC_ULONG rows_affected);

typedef void __cdecl (*Tfb_sqlstate)(PISC_SCHAR sqlstate, PISC_STATUS status_vector);

typedef NativeInt __cdecl (*Tfb_cancel_operation)(PISC_STATUS status, Pisc_db_handle db_handle, System::Word options);

typedef int __cdecl (*Tfb_shutdown)(unsigned timeout, int reason);

typedef NativeInt __cdecl (*Tfb_shutdown_callback)(PISC_STATUS status, FB_SHUTDOWN_CALLBACK_FUNC callback_function, int mask, void * arg);

typedef NativeInt __cdecl (*Tfb_ping)(PISC_STATUS status, Pisc_db_handle db_handle);

typedef NativeInt __cdecl (*Tfb_get_database_handle)(PISC_STATUS status, Pisc_db_handle db_handle, void * data);

typedef NativeInt __cdecl (*Tfb_get_transaction_handle)(PISC_STATUS status, Pisc_tr_handle tr_handle, void * data);

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 ISC_TRUE = System::Int8(0x1);
static const System::Int8 ISC_FALSE = System::Int8(0x0);
static const System::Int8 DSQL_close = System::Int8(0x1);
static const System::Int8 DSQL_drop = System::Int8(0x2);
static const System::Int8 DSQL_cancel = System::Int8(0x4);
static const System::Int8 DSQL_unprepare = System::Int8(0x4);
static const System::Int8 METADATALENGTH_V2 = System::Int8(0x44);
static const System::Int8 METADATALENGTH_V1 = System::Int8(0x20);
static const System::Int8 FB_SQLSTATE_SIZE = System::Int8(0x6);
static const System::Word ISC_TIME_SECONDS_PRECISION = System::Word(0x2710);
static const System::Int8 ISC_TIME_SECONDS_PRECISION_SCALE = System::Int8(-4);
static const System::Int8 ARR_DESC_VERSION2 = System::Int8(0x2);
static const System::Int8 BLB_DESC_VERSION2 = System::Int8(0x2);
static const System::Int8 ARR_DESC_VERSION1 = System::Int8(0x1);
static const System::Int8 BLB_DESC_VERSION1 = System::Int8(0x1);
static const System::Int8 blb_seek_relative = System::Int8(0x1);
static const System::Int8 blb_seek_from_tail = System::Int8(0x2);
static const System::Int8 blb_got_fragment = System::Int8(-1);
static const System::Int8 blb_got_eof = System::Int8(0x0);
static const System::Int8 blb_got_full_segment = System::Int8(0x1);
static const System::Int8 DSC_null = System::Int8(0x1);
static const System::Int8 DSC_no_subtype = System::Int8(0x2);
static const System::Int8 DSC_nullable = System::Int8(0x4);
static const System::Int8 dtype_unknown = System::Int8(0x0);
static const System::Int8 dtype_null = System::Int8(0x0);
static const System::Int8 dtype_text = System::Int8(0x1);
static const System::Int8 dtype_cstring = System::Int8(0x2);
static const System::Int8 dtype_varying = System::Int8(0x3);
static const System::Int8 dtype_packed = System::Int8(0x6);
static const System::Int8 dtype_byte = System::Int8(0x7);
static const System::Int8 dtype_short = System::Int8(0x8);
static const System::Int8 dtype_long = System::Int8(0x9);
static const System::Int8 dtype_quad = System::Int8(0xa);
static const System::Int8 dtype_real = System::Int8(0xb);
static const System::Int8 dtype_double = System::Int8(0xc);
static const System::Int8 dtype_d_float = System::Int8(0xd);
static const System::Int8 dtype_sql_date = System::Int8(0xe);
static const System::Int8 dtype_sql_time = System::Int8(0xf);
static const System::Int8 dtype_timestamp = System::Int8(0x10);
static const System::Int8 dtype_blob = System::Int8(0x11);
static const System::Int8 dtype_array = System::Int8(0x12);
static const System::Int8 dtype_int64 = System::Int8(0x13);
static const System::Int8 dtype_dbkey = System::Int8(0x14);
static const System::Int8 dtype_boolean = System::Int8(0x15);
static const System::Int8 DTYPE_TYPE_MAX = System::Int8(0x16);
static const System::Int8 SQLDA_VERSION1 = System::Int8(0x1);
static const System::Int8 SQLDA_VERSION2 = System::Int8(0x2);
static const System::Int8 SQL_DIALECT_V5 = System::Int8(0x1);
static const System::Int8 SQL_DIALECT_V6_TRANSITION = System::Int8(0x2);
static const System::Int8 SQL_DIALECT_V6 = System::Int8(0x3);
static const System::Word SQLIND_NULL = System::Word(0x8000);
static const System::Int8 SQLIND_INSERT = System::Int8(0x1);
static const System::Int8 SQLIND_UPDATE = System::Int8(0x2);
static const System::Int8 SQLIND_DELETE = System::Int8(0x4);
static const System::Int8 SQLIND_CHANGE = System::Int8(0x8);
static const System::Int8 SQLIND_TRUNCATE = System::Int8(0x10);
static const System::Int8 SQLIND_CHANGE_VIEW = System::Int8(0x20);
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
static const System::Int8 blr_int64 = System::Int8(0x10);
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
static const System::Int8 blr_boolean_dtype_ib = System::Int8(0x11);
static const System::Int8 blr_blob2 = System::Int8(0x11);
static const System::Int8 blr_domain_name = System::Int8(0x12);
static const System::Int8 blr_domain_name2 = System::Int8(0x13);
static const System::Int8 blr_not_nullable = System::Int8(0x14);
static const System::Int8 blr_column_name = System::Int8(0x15);
static const System::Int8 blr_column_name2 = System::Int8(0x16);
static const System::Int8 blr_bool_fb = System::Int8(0x17);
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
static const System::Int8 blr_raise = System::Int8(0x5);
static const System::Int8 blr_exception_msg = System::Int8(0x6);
static const System::Int8 blr_exception_params = System::Int8(0x7);
static const System::Int8 blr_version4 = System::Int8(0x4);
static const System::Int8 blr_version5 = System::Int8(0x5);
static const System::Int8 blr_eoc = System::Int8(0x4c);
static const System::Byte blr_end = System::Byte(0xff);
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
static const System::Int8 blr_parameter2_old = System::Int8(0x2c);
static const System::Int8 blr_user_name = System::Int8(0x2c);
static const System::Int8 blr_null = System::Int8(0x2d);
static const System::Int8 blr_equiv = System::Int8(0x2e);
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
static const System::Int8 blr_ties = System::Int8(0x0);
static const System::Int8 blr_percent = System::Int8(0x1);
static const System::Int8 blr_agg_count = System::Int8(0x53);
static const System::Int8 blr_agg_max = System::Int8(0x54);
static const System::Int8 blr_agg_min = System::Int8(0x55);
static const System::Int8 blr_agg_total = System::Int8(0x56);
static const System::Int8 blr_agg_average = System::Int8(0x57);
static const System::Int8 blr_parameter3 = System::Int8(0x58);
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
static const System::Int8 blr_scrollable = System::Int8(0x6d);
static const System::Int8 blr_continue = System::Int8(0x0);
static const System::Int8 blr_forward = System::Int8(0x1);
static const System::Int8 blr_backward = System::Int8(0x2);
static const System::Int8 blr_bof_forward = System::Int8(0x3);
static const System::Int8 blr_eof_backward = System::Int8(0x4);
static const System::Int8 blr_lock_relation = System::Int8(0x72);
static const System::Int8 blr_lock_record = System::Int8(0x73);
static const System::Int8 blr_set_bookmark = System::Int8(0x74);
static const System::Int8 blr_get_bookmark = System::Int8(0x75);
static const System::Int8 blr_run_count = System::Int8(0x76);
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
static const System::Byte blr_pid2 = System::Byte(0x84);
static const System::Byte blr_procedure2 = System::Byte(0x85);
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
static const System::Byte blr_current_role = System::Byte(0xae);
static const System::Byte blr_skip = System::Byte(0xaf);
static const System::Byte blr_boolean_true = System::Byte(0xae);
static const System::Byte blr_boolean_false = System::Byte(0xaf);
static const System::Byte blr_start_savepoint2 = System::Byte(0xb0);
static const System::Byte blr_release_savepoint = System::Byte(0xb1);
static const System::Byte blr_rollback_savepoint = System::Byte(0xb2);
static const System::Byte blr_exec_sql = System::Byte(0xb0);
static const System::Byte blr_internal_info = System::Byte(0xb1);
static const System::Byte blr_nullsfirst = System::Byte(0xb2);
static const System::Byte blr_writelock = System::Byte(0xb3);
static const System::Byte blr_nullslast = System::Byte(0xb4);
static const System::Byte blr_post_arg = System::Byte(0xa3);
static const System::Byte blr_exec_into = System::Byte(0xa4);
static const System::Byte blr_user_savepoint = System::Byte(0xa5);
static const System::Byte blr_lowcase = System::Byte(0xb5);
static const System::Byte blr_strlen = System::Byte(0xb6);
static const System::Int8 blr_strlen_bit = System::Int8(0x0);
static const System::Int8 blr_strlen_char = System::Int8(0x1);
static const System::Int8 blr_strlen_octet = System::Int8(0x2);
static const System::Byte blr_trim = System::Byte(0xb7);
static const System::Int8 blr_trim_both = System::Int8(0x0);
static const System::Int8 blr_trim_leading = System::Int8(0x1);
static const System::Int8 blr_trim_trailing = System::Int8(0x2);
static const System::Int8 blr_trim_spaces = System::Int8(0x0);
static const System::Int8 blr_trim_characters = System::Int8(0x1);
static const System::Byte blr_dcl_cursor = System::Byte(0xa6);
static const System::Byte blr_cursor_stmt = System::Byte(0xa7);
static const System::Byte blr_current_timestamp2 = System::Byte(0xa8);
static const System::Byte blr_current_time2 = System::Byte(0xa9);
static const System::Byte blr_agg_list = System::Byte(0xaa);
static const System::Byte blr_agg_list_distinct = System::Byte(0xab);
static const System::Byte blr_modify2 = System::Byte(0xac);
static const System::Int8 blr_savepoint_set = System::Int8(0x0);
static const System::Int8 blr_savepoint_release = System::Int8(0x1);
static const System::Int8 blr_savepoint_undo = System::Int8(0x2);
static const System::Int8 blr_savepoint_release_single = System::Int8(0x3);
static const System::Int8 blr_cursor_open = System::Int8(0x0);
static const System::Int8 blr_cursor_close = System::Int8(0x1);
static const System::Int8 blr_cursor_fetch = System::Int8(0x2);
static const System::Int8 blr_cursor_fetch_scroll = System::Int8(0x3);
static const System::Int8 blr_scroll_forward = System::Int8(0x0);
static const System::Int8 blr_scroll_backward = System::Int8(0x1);
static const System::Int8 blr_scroll_bof = System::Int8(0x2);
static const System::Int8 blr_scroll_eof = System::Int8(0x3);
static const System::Int8 blr_scroll_absolute = System::Int8(0x4);
static const System::Int8 blr_scroll_relative = System::Int8(0x5);
static const System::Byte blr_procedure3 = System::Byte(0xc0);
static const System::Byte blr_exec_proc2 = System::Byte(0xc1);
static const System::Byte blr_function2 = System::Byte(0xc2);
static const System::Byte blr_window = System::Byte(0xc3);
static const System::Byte blr_partition_by = System::Byte(0xc4);
static const System::Byte blr_continue_loop = System::Byte(0xc5);
static const System::Byte blr_procedure4 = System::Byte(0xc6);
static const System::Byte blr_agg_function = System::Byte(0xc7);
static const System::Byte blr_substring_similar = System::Byte(0xc8);
static const System::Byte blr_bool_as_value = System::Byte(0xc9);
static const System::Byte blr_coalesce = System::Byte(0xca);
static const System::Byte blr_decode = System::Byte(0xcb);
static const System::Int8 isc_dpb_version1 = System::Int8(0x1);
static const System::Int8 isc_dpb_version2 = System::Int8(0x2);
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
static const System::Int8 isc_dpb_old_file = System::Int8(0x24);
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
static const System::Int8 isc_dpb_sql_dialect = System::Int8(0x3f);
static const System::Int8 isc_dpb_set_db_readonly = System::Int8(0x40);
static const System::Int8 isc_dpb_set_db_sql_dialect = System::Int8(0x41);
static const System::Int8 isc_dpb_gfix_attach = System::Int8(0x42);
static const System::Int8 isc_dpb_gstat_attach = System::Int8(0x43);
static const System::Int8 isc_dpb_gbak_ods_version = System::Int8(0x44);
static const System::Int8 isc_dpb_gbak_ods_minor_version = System::Int8(0x45);
static const System::Int8 isc_dpb_numeric_scale_reduction = System::Int8(0x46);
static const System::Int8 isc_dpb_sec_flags = System::Int8(0x5b);
static const System::Int8 isc_dpb_sec_type = System::Int8(0x5c);
static const System::Int8 isc_dpb_sec_principal = System::Int8(0x5d);
static const System::Int8 isc_dpb_sec_srv_name = System::Int8(0x5e);
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
static const System::Int8 isc_dpb_set_db_charset = System::Int8(0x44);
static const System::Int8 isc_dpb_gsec_attach = System::Int8(0x45);
static const System::Int8 isc_dpb_address_path = System::Int8(0x46);
static const System::Int8 isc_dpb_process_id = System::Int8(0x47);
static const System::Int8 isc_dpb_no_db_triggers = System::Int8(0x48);
static const System::Int8 isc_dpb_trusted_auth = System::Int8(0x49);
static const System::Int8 isc_dpb_process_name = System::Int8(0x4a);
static const System::Int8 isc_dpb_trusted_role = System::Int8(0x4b);
static const System::Int8 isc_dpb_org_filename = System::Int8(0x4c);
static const System::Int8 isc_dpb_utf8_filename = System::Int8(0x4d);
static const System::Int8 isc_dpb_ext_call_depth = System::Int8(0x4e);
static const System::Int8 isc_dpb_auth_block = System::Int8(0x4f);
static const System::Int8 isc_dpb_client_version = System::Int8(0x50);
static const System::Int8 isc_dpb_remote_protocol = System::Int8(0x51);
static const System::Int8 isc_dpb_host_name = System::Int8(0x52);
static const System::Int8 isc_dpb_os_user = System::Int8(0x53);
static const System::Int8 isc_dpb_specific_auth_data = System::Int8(0x54);
static const System::Int8 isc_dpb_auth_plugin_list = System::Int8(0x55);
static const System::Int8 isc_dpb_auth_plugin_name = System::Int8(0x56);
static const System::Int8 isc_dpb_config = System::Int8(0x57);
static const System::Int8 isc_dpb_nolinger = System::Int8(0x58);
static const System::Int8 isc_dpb_reset_icu = System::Int8(0x59);
static const System::Int8 isc_dpb_map_attach = System::Int8(0x5a);
static const System::Int8 isc_dpb_Max_Value_IB650 = System::Int8(0x45);
static const System::Int8 isc_dpb_Max_Value_IB700 = System::Int8(0x46);
static const System::Int8 isc_dpb_Max_Value_IB710 = System::Int8(0x47);
static const System::Int8 isc_dpb_Max_Value_IB750 = System::Int8(0x4a);
static const System::Int8 isc_dpb_Max_Value_IB2007 = System::Int8(0x53);
static const System::Int8 isc_dpb_Max_Value_IBXE = System::Int8(0x55);
static const System::Int8 isc_dpb_Max_Value_IBXE3 = System::Int8(0x56);
static const System::Int8 isc_dpb_Max_Value_FB103 = System::Int8(0x44);
static const System::Int8 isc_dpb_Max_Value_FB150 = System::Int8(0x44);
static const System::Int8 isc_dpb_Max_Value_FB200 = System::Int8(0x46);
static const System::Int8 isc_dpb_Max_Value_FB210 = System::Int8(0x4a);
static const System::Int8 isc_dpb_Max_Value_FB250 = System::Int8(0x4e);
static const System::Int8 isc_dpb_Max_Value_FB300 = System::Int8(0x4f);
static const System::Int8 isc_dpb_Max_Value_FB30x = System::Int8(0x5a);
static const System::Int8 isc_dpb_Max_Value_YF867 = System::Int8(0x46);
static const System::Int8 isc_dpb_address = System::Int8(0x1);
static const System::Int8 isc_dpb_addr_protocol = System::Int8(0x1);
static const System::Int8 isc_dpb_addr_endpoint = System::Int8(0x2);
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
static const System::Int8 isc_dpb_shut_mode_mask = System::Int8(0x70);
static const System::Int8 isc_dpb_shut_default = System::Int8(0x0);
static const System::Int8 isc_dpb_shut_normal = System::Int8(0x10);
static const System::Int8 isc_dpb_shut_multi = System::Int8(0x20);
static const System::Int8 isc_dpb_shut_single = System::Int8(0x30);
static const System::Int8 isc_dpb_shut_full = System::Int8(0x40);
static const System::Int8 isc_dpb_sec_delegation = System::Int8(0x1);
static const System::Int8 isc_dpb_sec_mutual_auth = System::Int8(0x2);
static const System::Int8 isc_dpb_sec_replay = System::Int8(0x4);
static const System::Int8 isc_dpb_sec_sequence = System::Int8(0x8);
static const System::Int8 isc_dpb_sec_confidentiality = System::Int8(0x10);
static const System::Int8 isc_dpb_sec_integrity = System::Int8(0x20);
static const System::Int8 isc_dpb_sec_anonymous = System::Int8(0x40);
static const int isc_dpb_sec_transport = int(0x8000000);
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
static const System::Int8 isc_tpb_lock_timeout = System::Int8(0x15);
static const System::Int8 isc_tpb_exclusivity = System::Int8(0x16);
static const System::Int8 isc_tpb_wait_time = System::Int8(0x17);
static const System::Int8 isc_bpb_Max_Value = System::Int8(0x6);
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
static const System::Int8 isc_spb_version3 = System::Int8(0x3);
static const System::Int8 isc_spb_current_version = System::Int8(0x2);
static const System::Int8 isc_spb_version = System::Int8(0x2);
static const System::Int8 isc_spb_user_name = System::Int8(0x1c);
static const System::Int8 isc_spb_sys_user_name = System::Int8(0x13);
static const System::Int8 isc_spb_sys_user_name_enc = System::Int8(0x1f);
static const System::Int8 isc_spb_password = System::Int8(0x1d);
static const System::Int8 isc_spb_password_enc = System::Int8(0x1e);
static const System::Int8 isc_spb_connect_timeout = System::Int8(0x39);
static const System::Int8 isc_spb_dummy_packet_interval = System::Int8(0x3a);
static const System::Int8 isc_spb_sql_role_name = System::Int8(0x3c);
static const System::Int8 isc_spb_instance_name = System::Int8(0x4b);
static const System::Int8 isc_spb_command_line = System::Int8(0x69);
static const System::Int8 isc_spb_dbname = System::Int8(0x6a);
static const System::Int8 isc_spb_verbose = System::Int8(0x6b);
static const System::Int8 isc_spb_options = System::Int8(0x6c);
static const System::Int8 isc_spb_user_dbname = System::Int8(0x6d);
static const System::Int8 isc_spb_auth_dbname = System::Int8(0x6e);
static const System::Int8 isc_spb_sys_encrypt_password = System::Int8(0x55);
static const System::Int8 isc_spb_address_path = System::Int8(0x6d);
static const System::Int8 isc_spb_process_id = System::Int8(0x6e);
static const System::Int8 isc_spb_trusted_auth = System::Int8(0x6f);
static const System::Int8 isc_spb_process_name = System::Int8(0x70);
static const System::Int8 isc_spb_trusted_role = System::Int8(0x71);
static const System::Int8 isc_spb_verbint = System::Int8(0x72);
static const System::Int8 isc_spb_auth_block = System::Int8(0x73);
static const System::Int8 isc_spb_auth_plugin_name = System::Int8(0x74);
static const System::Int8 isc_spb_auth_plugin_list = System::Int8(0x75);
static const System::Int8 isc_spb_utf8_filename = System::Int8(0x76);
static const System::Int8 isc_spb_client_version = System::Int8(0x77);
static const System::Int8 isc_spb_remote_protocol = System::Int8(0x78);
static const System::Int8 isc_spb_host_name = System::Int8(0x79);
static const System::Int8 isc_spb_os_user = System::Int8(0x7a);
static const System::Int8 isc_spb_config = System::Int8(0x7b);
static const System::Int8 isc_spb_expected_db = System::Int8(0x7c);
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
static const System::Int8 isc_info_isc_version = System::Int8(0xc);
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
static const System::Int8 isc_info_wal_cur_ckpt_interval = System::Int8(0x29);
static const System::Int8 isc_info_wal_prv_ckpt_fname = System::Int8(0x2a);
static const System::Int8 isc_info_wal_prv_ckpt_poffset = System::Int8(0x2b);
static const System::Int8 isc_info_wal_recv_ckpt_fname = System::Int8(0x2c);
static const System::Int8 isc_info_wal_recv_ckpt_poffset = System::Int8(0x2d);
static const System::Int8 isc_info_wal_grpc_wait_usecs = System::Int8(0x2f);
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
static const System::Int8 isc_info_db_sql_dialect = System::Int8(0x3e);
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
static const System::Int8 frb_info_att_charset = System::Int8(0x65);
static const System::Int8 isc_info_db_class = System::Int8(0x66);
static const System::Int8 isc_info_firebird_version = System::Int8(0x67);
static const System::Int8 isc_info_oldest_transaction = System::Int8(0x68);
static const System::Int8 isc_info_oldest_active = System::Int8(0x69);
static const System::Int8 isc_info_oldest_snapshot = System::Int8(0x6a);
static const System::Int8 isc_info_next_transaction = System::Int8(0x6b);
static const System::Int8 isc_info_db_provider = System::Int8(0x6c);
static const System::Int8 isc_info_active_transactions = System::Int8(0x6d);
static const System::Int8 isc_info_active_tran_count = System::Int8(0x6e);
static const System::Int8 isc_info_creation_date = System::Int8(0x6f);
static const System::Int8 isc_info_db_file_size = System::Int8(0x70);
static const System::Int8 fb_info_page_contents = System::Int8(0x71);
static const System::Int8 fb_info_implementation = System::Int8(0x72);
static const System::Int8 fb_info_pages_used = System::Int8(0x7c);
static const System::Int8 fb_info_pages_free = System::Int8(0x7d);
static const System::Int8 fb_info_crypt_state = System::Int8(0x7e);
static const System::Int8 isc_info_version = System::Int8(0xc);
static const System::Int8 isc_info_db_impl_rdb_vms = System::Int8(0x1);
static const System::Int8 isc_info_db_impl_rdb_eln = System::Int8(0x2);
static const System::Int8 isc_info_db_impl_rdb_eln_dev = System::Int8(0x3);
static const System::Int8 isc_info_db_impl_rdb_vms_y = System::Int8(0x4);
static const System::Int8 isc_info_db_impl_rdb_eln_y = System::Int8(0x5);
static const System::Int8 isc_info_db_impl_jri = System::Int8(0x6);
static const System::Int8 isc_info_db_impl_jsv = System::Int8(0x7);
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
static const System::Int8 isc_info_db_impl_isc_epson_IB65 = System::Int8(0x31);
static const System::Int8 isc_info_db_impl_m88K = System::Int8(0x30);
static const System::Int8 isc_info_db_impl_unixware = System::Int8(0x31);
static const System::Int8 isc_info_db_impl_isc_winnt_x86 = System::Int8(0x32);
static const System::Int8 isc_info_db_impl_isc_epson_FB102 = System::Int8(0x33);
static const System::Int8 isc_info_db_impl_alpha_osf = System::Int8(0x34);
static const System::Int8 isc_info_db_impl_alpha_vms = System::Int8(0x35);
static const System::Int8 isc_info_db_impl_netware_386 = System::Int8(0x36);
static const System::Int8 isc_info_db_impl_win_only = System::Int8(0x37);
static const System::Int8 isc_info_db_impl_ncr_3000 = System::Int8(0x38);
static const System::Int8 isc_info_db_impl_winnt_ppc = System::Int8(0x39);
static const System::Int8 isc_info_db_impl_dg_x86 = System::Int8(0x3a);
static const System::Int8 isc_info_db_impl_sco_ev = System::Int8(0x3b);
static const System::Int8 isc_info_db_impl_i386 = System::Int8(0x3c);
static const System::Int8 isc_info_db_impl_freebsd = System::Int8(0x3d);
static const System::Int8 isc_info_db_impl_netbsd = System::Int8(0x3e);
static const System::Int8 isc_info_db_impl_darwin = System::Int8(0x3f);
static const System::Int8 isc_info_db_impl_sinixz = System::Int8(0x40);
static const System::Int8 isc_info_db_impl_linux_sparc = System::Int8(0x41);
static const System::Int8 isc_info_db_impl_linux_amd64 = System::Int8(0x42);
static const System::Int8 isc_info_db_impl_freebsd_amd64 = System::Int8(0x43);
static const System::Int8 isc_info_db_impl_winnt_amd64 = System::Int8(0x44);
static const System::Int8 isc_info_db_impl_linux_ppc = System::Int8(0x45);
static const System::Int8 isc_info_db_impl_darwin_x86 = System::Int8(0x46);
static const System::Int8 isc_info_db_impl_linux_mipsel = System::Int8(0x47);
static const System::Int8 isc_info_db_impl_linux_mips = System::Int8(0x48);
static const System::Int8 isc_info_db_impl_darwin_x64 = System::Int8(0x49);
static const System::Int8 isc_info_db_impl_sun_amd64 = System::Int8(0x4a);
static const System::Int8 isc_info_db_impl_linux_arm = System::Int8(0x4b);
static const System::Int8 isc_info_db_impl_linux_ia64 = System::Int8(0x4c);
static const System::Int8 isc_info_db_impl_darwin_ppc64 = System::Int8(0x4d);
static const System::Int8 isc_info_db_impl_linux_s390x = System::Int8(0x4e);
static const System::Int8 isc_info_db_impl_linux_s390 = System::Int8(0x4f);
static const System::Int8 isc_info_db_impl_linux_sh = System::Int8(0x50);
static const System::Int8 isc_info_db_impl_linux_sheb = System::Int8(0x51);
static const System::Int8 isc_info_db_impl_isc_a = System::Int8(0x19);
static const System::Int8 isc_info_db_impl_isc_u = System::Int8(0x1a);
static const System::Int8 isc_info_db_impl_isc_v = System::Int8(0x1b);
static const System::Int8 isc_info_db_impl_isc_s = System::Int8(0x1c);
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
static const System::Int8 isc_info_db_class_classic_access = System::Int8(0xd);
static const System::Int8 isc_info_db_class_server_access = System::Int8(0xe);
static const System::Int8 isc_info_db_code_rdb_eln = System::Int8(0x1);
static const System::Int8 isc_info_db_code_rdb_vms = System::Int8(0x2);
static const System::Int8 isc_info_db_code_interbase = System::Int8(0x3);
static const System::Int8 isc_info_db_code_firebird = System::Int8(0x4);
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
static const System::Int8 isc_info_rsb_skip = System::Int8(0x16);
static const System::Int8 isc_info_rsb_virt_sequential = System::Int8(0x17);
static const System::Int8 isc_info_rsb_recursive = System::Int8(0x18);
static const System::Int8 isc_info_rsb_window = System::Int8(0x19);
static const System::Int8 isc_info_rsb_singular = System::Int8(0x1a);
static const System::Int8 isc_info_rsb_writelock = System::Int8(0x1b);
static const System::Int8 isc_info_rsb_buffer = System::Int8(0x1c);
static const System::Int8 isc_info_rsb_hash = System::Int8(0x1d);
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
static const System::Int8 isc_info_tra_oldest_interesting = System::Int8(0x5);
static const System::Int8 isc_info_tra_oldest_snapshot = System::Int8(0x6);
static const System::Int8 isc_info_tra_oldest_active = System::Int8(0x7);
static const System::Int8 isc_info_tra_isolation = System::Int8(0x8);
static const System::Int8 isc_info_tra_access = System::Int8(0x9);
static const System::Int8 isc_info_tra_lock_timeout = System::Int8(0xa);
static const System::Int8 fb_info_tra_dbpath = System::Int8(0xb);
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
static const System::Int8 isc_action_svc_nbak = System::Int8(0x14);
static const System::Int8 isc_action_svc_nrest = System::Int8(0x15);
static const System::Int8 isc_action_svc_trace_start = System::Int8(0x16);
static const System::Int8 isc_action_svc_trace_stop = System::Int8(0x17);
static const System::Int8 isc_action_svc_trace_suspend = System::Int8(0x18);
static const System::Int8 isc_action_svc_trace_resume = System::Int8(0x19);
static const System::Int8 isc_action_svc_trace_list = System::Int8(0x1a);
static const System::Int8 isc_action_svc_set_mapping = System::Int8(0x1b);
static const System::Int8 isc_action_svc_drop_mapping = System::Int8(0x1c);
static const System::Int8 isc_action_svc_display_user_adm = System::Int8(0x1d);
static const System::Int8 isc_action_svc_validate = System::Int8(0x1e);
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
static const System::Int8 isc_spb_bkp_skip_data = System::Int8(0x8);
static const System::Int8 isc_spb_bkp_stat = System::Int8(0xf);
static const System::Int8 isc_spb_bkp_keyholder = System::Int8(0x10);
static const System::Int8 isc_spb_bkp_keyname = System::Int8(0x11);
static const System::Int8 isc_spb_bkp_crypt = System::Int8(0x12);
static const System::Int8 isc_spb_bkp_ignore_checksums = System::Int8(0x1);
static const System::Int8 isc_spb_bkp_ignore_limbo = System::Int8(0x2);
static const System::Int8 isc_spb_bkp_metadata_only = System::Int8(0x4);
static const System::Int8 isc_spb_bkp_no_garbage_collect = System::Int8(0x8);
static const System::Int8 isc_spb_bkp_old_descriptions = System::Int8(0x10);
static const System::Int8 isc_spb_bkp_non_transportable = System::Int8(0x20);
static const System::Int8 isc_spb_bkp_convert = System::Int8(0x40);
static const System::Byte isc_spb_bkp_expand = System::Byte(0x80);
static const System::Word isc_spb_bkp_no_triggers = System::Word(0x8000);
static const int isc_spb_bkp_zip = int(0x10000);
static const int isc_spb_bkp_archive_database = int(0x10000);
static const int isc_spb_bkp_archive_journals = int(0x20000);
static const System::Int8 isc_spb_nbk_level = System::Int8(0x5);
static const System::Int8 isc_spb_nbk_file = System::Int8(0x6);
static const System::Int8 isc_spb_nbk_direct = System::Int8(0x7);
static const System::Int8 isc_spb_nbk_no_triggers = System::Int8(0x1);
static const System::Int8 isc_spb_res_buffers = System::Int8(0x9);
static const System::Int8 isc_spb_res_page_size = System::Int8(0xa);
static const System::Int8 isc_spb_res_length = System::Int8(0xb);
static const System::Int8 isc_spb_res_access_mode = System::Int8(0xc);
static const System::Int8 isc_spb_res_fix_fss_data = System::Int8(0xd);
static const System::Int8 isc_spb_res_fix_fss_metadata = System::Int8(0xe);
static const System::Int8 isc_spb_res_metadata_only = System::Int8(0x4);
static const System::Int8 isc_spb_res_stat = System::Int8(0xf);
static const System::Int8 isc_spb_res_decrypt_password = System::Int8(0x10);
static const System::Int8 isc_spb_res_eua_user_name = System::Int8(0x11);
static const System::Int8 isc_spb_res_eua_password = System::Int8(0x12);
static const System::Int8 isc_spb_res_write_mode = System::Int8(0x13);
static const System::Int8 isc_spb_res_starting_trans = System::Int8(0x15);
static const System::Int8 isc_spb_res_ods_version_major = System::Int8(0x16);
static const System::Int8 isc_spb_res_archive_recover_until = System::Int8(0x17);
static const System::Word isc_spb_res_deactivate_idx = System::Word(0x100);
static const System::Word isc_spb_res_no_shadow = System::Word(0x200);
static const System::Word isc_spb_res_no_validity = System::Word(0x400);
static const System::Word isc_spb_res_one_at_a_time = System::Word(0x800);
static const System::Word isc_spb_res_replace = System::Word(0x1000);
static const System::Word isc_spb_res_create = System::Word(0x2000);
static const System::Word isc_spb_res_use_all_space = System::Word(0x4000);
static const System::Word isc_spb_res_validate = System::Word(0x8000);
static const int isc_spb_res_archive_recover = int(0x40000);
static const System::Int8 isc_spb_val_tab_incl = System::Int8(0x1);
static const System::Int8 isc_spb_val_tab_excl = System::Int8(0x2);
static const System::Int8 isc_spb_val_idx_incl = System::Int8(0x3);
static const System::Int8 isc_spb_val_idx_excl = System::Int8(0x4);
static const System::Int8 isc_spb_val_lock_timeout = System::Int8(0x5);
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
static const System::Int8 isc_spb_sts_record_versions_IB70 = System::Int8(0x20);
static const System::Int8 isc_spb_sts_table_IB70 = System::Int8(0x40);
static const System::Int8 isc_spb_sts_record_versions_IB65 = System::Int8(0x12);
static const System::Int8 isc_spb_sts_table_IB65 = System::Int8(0x14);
static const System::Int8 isc_spb_sts_record_versions_FB15 = System::Int8(0x20);
static const System::Int8 isc_spb_sts_table_FB15 = System::Int8(0x40);
static const System::Byte isc_spb_sts_nocreation = System::Byte(0x80);
static const System::Int8 isc_spb_trc_id = System::Int8(0x1);
static const System::Int8 isc_spb_trc_name = System::Int8(0x2);
static const System::Int8 isc_spb_trc_cfg = System::Int8(0x3);
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
static const System::Int8 isc_info_sql_relation_alias = System::Int8(0x19);
static const System::Int8 isc_info_sql_precision = System::Int8(0x19);
static const System::Int8 isc_info_sql_explain_plan = System::Int8(0x1a);
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
static const System::Int8 isc_info_sql_stmt_savepoint = System::Int8(0xe);
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
static const System::Int8 ISCCFG_REJECT_AMBIGUITY_KEY = System::Int8(0x18);
static const System::Int8 ISCCFG_SQZ_BLOCK_KEY = System::Int8(0x19);
static const System::Int8 ISCCFG_LOCK_TIMEOUT_KEY = System::Int8(0x1a);
static const System::Int8 ISCCFG_YAFFIL_ODS_KEY = System::Int8(0x1b);
static const System::Int8 ISCCFG_CONSTRAINT_INDEX_NAME_KEY = System::Int8(0x1c);
static const System::Int8 ISCCFG_NO_NAGLE_KEY = System::Int8(0x1d);
static const System::Int8 ISCCFG_WIN32_DISABLEFILECACHE_KEY = System::Int8(0x1e);
static const System::Int8 ISCCFG_LOCKMEM_RES_KEY = System::Int8(0x1f);
static const System::Int8 ISCCFG_FORCERESHEDULE_KEY = System::Int8(0x20);
static const System::Int8 ISCCFG_LEGACY_DIALECT1_KEY = System::Int8(0x21);
static const System::Int8 isc_dyn_version_1 = System::Int8(0x1);
static const System::Byte isc_dyn_eoc = System::Byte(0xff);
static const System::Int8 isc_dyn_begin = System::Int8(0x2);
static const System::Int8 isc_dyn_end = System::Int8(0x3);
static const System::Int8 isc_dyn_if = System::Int8(0x4);
static const System::Int8 isc_dyn_def_database = System::Int8(0x5);
static const System::Int8 isc_dyn_def_global_fld = System::Int8(0x6);
static const System::Int8 isc_dyn_def_local_fld = System::Int8(0x7);
static const System::Int8 isc_dyn_def_idx = System::Int8(0x8);
static const System::Int8 isc_dyn_def_rel = System::Int8(0x9);
static const System::Int8 isc_dyn_def_sql_fld = System::Int8(0xa);
static const System::Int8 isc_dyn_def_view = System::Int8(0xc);
static const System::Int8 isc_dyn_def_trigger = System::Int8(0xf);
static const System::Int8 isc_dyn_def_security_class = System::Int8(0x78);
static const System::Byte isc_dyn_def_dimension = System::Byte(0x8c);
static const System::Int8 isc_dyn_def_generator = System::Int8(0x18);
static const System::Int8 isc_dyn_def_function = System::Int8(0x19);
static const System::Int8 isc_dyn_def_filter = System::Int8(0x1a);
static const System::Int8 isc_dyn_def_function_arg = System::Int8(0x1b);
static const System::Int8 isc_dyn_def_shadow = System::Int8(0x22);
static const System::Int8 isc_dyn_def_trigger_msg = System::Int8(0x11);
static const System::Int8 isc_dyn_def_file = System::Int8(0x24);
static const System::Byte isc_dyn_def_user = System::Byte(0xe1);
static const System::Int8 isc_dyn_mod_database = System::Int8(0x27);
static const System::Int8 isc_dyn_mod_rel = System::Int8(0xb);
static const System::Int8 isc_dyn_mod_global_fld = System::Int8(0xd);
static const System::Int8 isc_dyn_mod_idx = System::Int8(0x66);
static const System::Int8 isc_dyn_mod_local_fld = System::Int8(0xe);
static const System::Byte isc_dyn_mod_sql_fld = System::Byte(0xd8);
static const System::Int8 isc_dyn_mod_view = System::Int8(0x10);
static const System::Int8 isc_dyn_mod_security_class = System::Int8(0x7a);
static const System::Int8 isc_dyn_mod_trigger = System::Int8(0x71);
static const System::Int8 isc_dyn_mod_trigger_msg = System::Int8(0x1c);
static const System::Byte isc_dyn_mod_user = System::Byte(0xe2);
static const System::Int8 isc_dyn_delete_database = System::Int8(0x12);
static const System::Int8 isc_dyn_delete_rel = System::Int8(0x13);
static const System::Int8 isc_dyn_delete_global_fld = System::Int8(0x14);
static const System::Int8 isc_dyn_delete_local_fld = System::Int8(0x15);
static const System::Int8 isc_dyn_delete_idx = System::Int8(0x16);
static const System::Int8 isc_dyn_delete_security_class = System::Int8(0x7b);
static const System::Byte isc_dyn_delete_dimensions = System::Byte(0x8f);
static const System::Int8 isc_dyn_delete_trigger = System::Int8(0x17);
static const System::Int8 isc_dyn_delete_trigger_msg = System::Int8(0x1d);
static const System::Int8 isc_dyn_delete_filter = System::Int8(0x20);
static const System::Int8 isc_dyn_delete_function = System::Int8(0x21);
static const System::Byte isc_dyn_delete_generator = System::Byte(0xd9);
static const System::Byte isc_dyn_mod_function = System::Byte(0xe0);
static const System::Byte isc_dyn_mod_filter = System::Byte(0xe1);
static const System::Byte isc_dyn_mod_generator = System::Byte(0xe2);
static const System::Byte isc_dyn_mod_sql_role = System::Byte(0xe3);
static const System::Byte isc_dyn_mod_charset = System::Byte(0xe4);
static const System::Byte isc_dyn_mod_collation = System::Byte(0xe5);
static const System::Byte isc_dyn_mod_prc_parameter = System::Byte(0xe6);
static const System::Byte isc_dyn_def_collation = System::Byte(0xe7);
static const System::Byte isc_dyn_coll_for_charset = System::Byte(0xe8);
static const System::Byte isc_dyn_coll_from = System::Byte(0xe9);
static const System::Byte isc_dyn_coll_attribute = System::Byte(0xea);
static const System::Byte isc_dyn_coll_specific_attributes_charset = System::Byte(0xeb);
static const System::Byte isc_dyn_coll_specific_attributes = System::Byte(0xec);
static const System::Byte isc_dyn_del_collation = System::Byte(0xed);
static const System::Int8 isc_dyn_delete_shadow = System::Int8(0x23);
static const System::Byte isc_dyn_delete_user = System::Byte(0xe3);
static const System::Int8 isc_dyn_grant = System::Int8(0x1e);
static const System::Int8 isc_dyn_revoke = System::Int8(0x1f);
static const System::Int8 isc_dyn_def_primary_key = System::Int8(0x25);
static const System::Int8 isc_dyn_def_foreign_key = System::Int8(0x26);
static const System::Int8 isc_dyn_def_unique = System::Int8(0x28);
static const System::Byte isc_dyn_def_procedure = System::Byte(0xa4);
static const System::Byte isc_dyn_delete_procedure = System::Byte(0xa5);
static const System::Byte isc_dyn_def_parameter = System::Byte(0x87);
static const System::Byte isc_dyn_delete_parameter = System::Byte(0x88);
static const System::Byte isc_dyn_mod_procedure = System::Byte(0xaf);
static const System::Byte isc_dyn_def_log_file = System::Byte(0xb0);
static const System::Byte isc_dyn_def_cache_file = System::Byte(0xb4);
static const System::Byte isc_dyn_def_exception = System::Byte(0xb5);
static const System::Byte isc_dyn_mod_exception = System::Byte(0xb6);
static const System::Byte isc_dyn_del_exception = System::Byte(0xb7);
static const System::Byte isc_dyn_drop_log = System::Byte(0xc2);
static const System::Byte isc_dyn_drop_cache = System::Byte(0xc3);
static const System::Byte isc_dyn_def_default_log = System::Byte(0xca);
static const System::Byte isc_dyn_def_difference = System::Byte(0xdc);
static const System::Byte isc_dyn_drop_difference = System::Byte(0xdd);
static const System::Byte isc_dyn_begin_backup = System::Byte(0xde);
static const System::Byte isc_dyn_end_backup = System::Byte(0xdf);
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
static const System::Byte isc_dyn_prc_name = System::Byte(0xa6);
static const System::Byte isc_dyn_prm_name = System::Byte(0x89);
static const System::Byte isc_dyn_sql_object = System::Byte(0xc4);
static const System::Byte isc_dyn_fld_character_set_name = System::Byte(0xae);
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
static const System::Byte isc_dyn_fld_character_set = System::Byte(0xcb);
static const System::Int8 isc_dyn_fld_source = System::Int8(0x5a);
static const System::Int8 isc_dyn_fld_base_fld = System::Int8(0x5b);
static const System::Int8 isc_dyn_fld_position = System::Int8(0x5c);
static const System::Int8 isc_dyn_fld_update_flag = System::Int8(0x5d);
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
static const System::Byte isc_dyn_grant_role = System::Byte(0xda);
static const System::Byte isc_dyn_grant_user_explicit = System::Byte(0xdb);
static const System::Byte isc_dyn_dim_lower = System::Byte(0x8d);
static const System::Byte isc_dyn_dim_upper = System::Byte(0x8e);
static const System::Int8 isc_dyn_file_name = System::Int8(0x7d);
static const System::Int8 isc_dyn_file_start = System::Int8(0x7e);
static const System::Int8 isc_dyn_file_length = System::Int8(0x7f);
static const System::Byte isc_dyn_shadow_number = System::Byte(0x80);
static const System::Byte isc_dyn_shadow_man_auto = System::Byte(0x81);
static const System::Byte isc_dyn_shadow_conditional = System::Byte(0x82);
static const System::Byte isc_dyn_log_file_sequence = System::Byte(0xb1);
static const System::Byte isc_dyn_log_file_partitions = System::Byte(0xb2);
static const System::Byte isc_dyn_log_file_serial = System::Byte(0xb3);
static const System::Byte isc_dyn_log_file_overflow = System::Byte(0xc8);
static const System::Byte isc_dyn_log_file_raw = System::Byte(0xc9);
static const System::Byte isc_dyn_log_group_commit_wait = System::Byte(0xbd);
static const System::Byte isc_dyn_log_buffer_size = System::Byte(0xbe);
static const System::Byte isc_dyn_log_check_point_length = System::Byte(0xbf);
static const System::Byte isc_dyn_log_num_of_buffers = System::Byte(0xc0);
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
static const System::Byte isc_dyn_foreign_key_update = System::Byte(0xcd);
static const System::Byte isc_dyn_foreign_key_delete = System::Byte(0xce);
static const System::Byte isc_dyn_foreign_key_cascade = System::Byte(0xcf);
static const System::Byte isc_dyn_foreign_key_default = System::Byte(0xd0);
static const System::Byte isc_dyn_foreign_key_null = System::Byte(0xd1);
static const System::Byte isc_dyn_foreign_key_none = System::Byte(0xd2);
static const System::Byte isc_dyn_def_sql_role = System::Byte(0xd3);
static const System::Byte isc_dyn_sql_role_name = System::Byte(0xd4);
static const System::Byte isc_dyn_grant_admin_options = System::Byte(0xd5);
static const System::Byte isc_dyn_del_sql_role = System::Byte(0xd6);
static const System::Byte gds_dyn_delete_generator = System::Byte(0xd9);
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
static const System::Int8 isc_dyn_db_page_cache = System::Int8(0x29);
static const System::Int8 isc_dyn_db_proc_cache = System::Int8(0x2a);
static const System::Int8 isc_dyn_db_rel_cache = System::Int8(0x2b);
static const System::Int8 isc_dyn_db_trig_cache = System::Int8(0x2c);
static const System::Int8 isc_dyn_db_flush_int = System::Int8(0x2d);
static const System::Int8 isc_dyn_db_linger_int = System::Int8(0x2e);
static const System::Int8 isc_dyn_db_reclaim_int = System::Int8(0x2f);
static const System::Int8 isc_dyn_db_sweep_int = System::Int8(0x30);
static const System::Int8 isc_dyn_db_group_commit = System::Int8(0x31);
static const System::Byte isc_dyn_last_dyn_value_FB102 = System::Byte(0xdb);
static const System::Byte isc_dyn_last_dyn_value_FB103 = System::Byte(0xdb);
static const System::Byte isc_dyn_last_dyn_value_FB150 = System::Byte(0xdb);
static const System::Byte isc_dyn_last_dyn_value_FB200 = System::Byte(0xdf);
static const System::Byte isc_dyn_last_dyn_value_IB650 = System::Byte(0xd8);
static const System::Byte isc_dyn_last_dyn_value_IB710 = System::Byte(0xd9);
static const System::Byte isc_dyn_last_dyn_value_IB750 = System::Byte(0xe3);
static const System::Int8 isc_sdl_version1 = System::Int8(0x1);
static const System::Byte isc_sdl_eoc = System::Byte(0xff);
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
static const System::Word SQL_TEXT = System::Word(0x1c4);
static const System::Word SQL_VARYING = System::Word(0x1c0);
static const System::Word SQL_SHORT = System::Word(0x1f4);
static const System::Word SQL_LONG = System::Word(0x1f0);
static const System::Word SQL_INT64 = System::Word(0x244);
static const System::Word SQL_FLOAT = System::Word(0x1e2);
static const System::Word SQL_DOUBLE = System::Word(0x1e0);
static const System::Word SQL_D_FLOAT = System::Word(0x212);
static const System::Word SQL_TYPE_TIME = System::Word(0x230);
static const System::Word SQL_TYPE_DATE = System::Word(0x23a);
static const System::Word SQL_TIMESTAMP = System::Word(0x1fe);
static const System::Word SQL_BLOB = System::Word(0x208);
static const System::Word SQL_ARRAY = System::Word(0x21c);
static const System::Word SQL_QUAD = System::Word(0x226);
static const System::Word SQL_BOOLEAN_IB = System::Word(0x24e);
static const System::Word SQL_NULL = System::Word(0x7ffe);
static const System::Word SQL_BOOLEAN_FB = System::Word(0x7ffc);
static const System::Word SQL_DATE = System::Word(0x1fe);
static const System::Int8 isc_blob_untyped = System::Int8(0x0);
static const System::Int8 isc_blob_text = System::Int8(0x1);
static const System::Int8 isc_blob_blr = System::Int8(0x2);
static const System::Int8 isc_blob_acl = System::Int8(0x3);
static const System::Int8 isc_blob_ranges = System::Int8(0x4);
static const System::Int8 isc_blob_summary = System::Int8(0x5);
static const System::Int8 isc_blob_format = System::Int8(0x6);
static const System::Int8 isc_blob_tra = System::Int8(0x7);
static const System::Int8 isc_blob_extfile = System::Int8(0x8);
static const System::Int8 isc_blob_max_predefined_subtype = System::Int8(0x9);
static const System::Int8 isc_blob_formatted_memo = System::Int8(0x14);
static const System::Int8 isc_blob_paradox_ole = System::Int8(0x15);
static const System::Int8 isc_blob_graphic = System::Int8(0x16);
static const System::Int8 isc_blob_dbase_ole = System::Int8(0x17);
static const System::Int8 isc_blob_typed_binary = System::Int8(0x18);
static const System::Int8 fb_shutrsn_svc_stopped = System::Int8(-1);
static const System::Int8 fb_shutrsn_no_connection = System::Int8(-2);
static const System::Int8 fb_shutrsn_app_stopped = System::Int8(-3);
static const System::Int8 fb_shutrsn_device_removed = System::Int8(-4);
static const System::Int8 fb_shutrsn_signal = System::Int8(-5);
static const System::Int8 fb_shutrsn_services = System::Int8(-6);
static const System::Int8 fb_shutrsn_exit_called = System::Int8(-7);
static const System::Int8 fb_cancel_disable = System::Int8(0x1);
static const System::Int8 fb_cancel_enable = System::Int8(0x2);
static const System::Int8 fb_cancel_raise = System::Int8(0x3);
static const System::Int8 fb_cancel_abort = System::Int8(0x4);
static const int ISC_MASK = int(0x14000000);
static const int FAC_MASK = int(0xff0000);
static const System::Word CODE_MASK = System::Word(0xffff);
static const unsigned CLASS_MASK = unsigned(0xf0000000);
static const System::Int8 CLASS_ERROR = System::Int8(0x0);
static const System::Int8 CLASS_WARNING = System::Int8(0x1);
static const System::Int8 CLASS_INFO = System::Int8(0x2);
static const System::Int8 FAC_JRD = System::Int8(0x0);
static const System::Int8 FAC_QLI = System::Int8(0x1);
static const System::Int8 FAC_GDEF = System::Int8(0x2);
static const System::Int8 FAC_GFIX = System::Int8(0x3);
static const System::Int8 FAC_GPRE = System::Int8(0x4);
static const System::Int8 FAC_GLTJ = System::Int8(0x5);
static const System::Int8 FAC_GRST = System::Int8(0x6);
static const System::Int8 FAC_DSQL = System::Int8(0x7);
static const System::Int8 FAC_DYN = System::Int8(0x8);
static const System::Int8 FAC_FRED = System::Int8(0x9);
static const System::Int8 FAC_INSTALL = System::Int8(0xa);
static const System::Int8 FAC_TEST = System::Int8(0xb);
static const System::Int8 FAC_GBAK = System::Int8(0xc);
static const System::Int8 FAC_SQLERR = System::Int8(0xd);
static const System::Int8 FAC_SQLWARN = System::Int8(0xe);
static const System::Int8 FAC_JRD_BUGCHK = System::Int8(0xf);
static const System::Int8 FAC_GJRN = System::Int8(0x10);
static const System::Int8 FAC_ISQL = System::Int8(0x11);
static const System::Int8 FAC_GSEC = System::Int8(0x12);
static const System::Int8 FAC_LICENSE = System::Int8(0x13);
static const System::Int8 FAC_DOS = System::Int8(0x14);
static const System::Int8 FAC_GSTAT = System::Int8(0x15);
static const System::Int8 isc_facility = System::Int8(0x14);
static const int isc_base = int(0x14000000);
static const System::Int8 isc_factor = System::Int8(0x1);
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
static const int isc_arith_except = int(0x14000001);
static const int isc_bad_dbkey = int(0x14000002);
static const int isc_bad_db_format = int(0x14000003);
static const int isc_bad_db_handle = int(0x14000004);
static const int isc_bad_dpb_content = int(0x14000005);
static const int isc_bad_dpb_form = int(0x14000006);
static const int isc_bad_req_handle = int(0x14000007);
static const int isc_bad_segstr_handle = int(0x14000008);
static const int isc_bad_segstr_id = int(0x14000009);
static const int isc_bad_tpb_content = int(0x1400000a);
static const int isc_bad_tpb_form = int(0x1400000b);
static const int isc_bad_trans_handle = int(0x1400000c);
static const int isc_bug_check = int(0x1400000d);
static const int isc_convert_error = int(0x1400000e);
static const int isc_db_corrupt = int(0x1400000f);
static const int isc_deadlock = int(0x14000010);
static const int isc_excess_trans = int(0x14000011);
static const int isc_from_no_match = int(0x14000012);
static const int isc_infinap = int(0x14000013);
static const int isc_infona = int(0x14000014);
static const int isc_infunk = int(0x14000015);
static const int isc_integ_fail = int(0x14000016);
static const int isc_invalid_blr = int(0x14000017);
static const int isc_io_error = int(0x14000018);
static const int isc_lock_conflict = int(0x14000019);
static const int isc_metadata_corrupt = int(0x1400001a);
static const int isc_not_valid = int(0x1400001b);
static const int isc_no_cur_rec = int(0x1400001c);
static const int isc_no_dup = int(0x1400001d);
static const int isc_no_finish = int(0x1400001e);
static const int isc_no_meta_update = int(0x1400001f);
static const int isc_no_priv = int(0x14000020);
static const int isc_no_recon = int(0x14000021);
static const int isc_no_record = int(0x14000022);
static const int isc_no_segstr_close = int(0x14000023);
static const int isc_obsolete_metadata = int(0x14000024);
static const int isc_open_trans = int(0x14000025);
static const int isc_port_len = int(0x14000026);
static const int isc_read_only_field = int(0x14000027);
static const int isc_read_only_rel = int(0x14000028);
static const int isc_read_only_trans = int(0x14000029);
static const int isc_read_only_view = int(0x1400002a);
static const int isc_req_no_trans = int(0x1400002b);
static const int isc_req_sync = int(0x1400002c);
static const int isc_req_wrong_db = int(0x1400002d);
static const int isc_segment = int(0x1400002e);
static const int isc_segstr_eof = int(0x1400002f);
static const int isc_segstr_no_op = int(0x14000030);
static const int isc_segstr_no_read = int(0x14000031);
static const int isc_segstr_no_trans = int(0x14000032);
static const int isc_segstr_no_write = int(0x14000033);
static const int isc_segstr_wrong_db = int(0x14000034);
static const int isc_sys_request = int(0x14000035);
static const int isc_stream_eof = int(0x14000036);
static const int isc_unavailable = int(0x14000037);
static const int isc_unres_rel = int(0x14000038);
static const int isc_uns_ext = int(0x14000039);
static const int isc_wish_list = int(0x1400003a);
static const int isc_wrong_ods = int(0x1400003b);
static const int isc_wronumarg = int(0x1400003c);
static const int isc_imp_exc = int(0x1400003d);
static const int isc_random = int(0x1400003e);
static const int isc_fatal_conflict = int(0x1400003f);
static const int isc_badblk = int(0x14000040);
static const int isc_invpoolcl = int(0x14000041);
static const int isc_nopoolids = int(0x14000042);
static const int isc_relbadblk = int(0x14000043);
static const int isc_blktoobig = int(0x14000044);
static const int isc_bufexh = int(0x14000045);
static const int isc_syntaxerr = int(0x14000046);
static const int isc_bufinuse = int(0x14000047);
static const int isc_bdbincon = int(0x14000048);
static const int isc_reqinuse = int(0x14000049);
static const int isc_badodsver = int(0x1400004a);
static const int isc_relnotdef = int(0x1400004b);
static const int isc_fldnotdef = int(0x1400004c);
static const int isc_dirtypage = int(0x1400004d);
static const int isc_waifortra = int(0x1400004e);
static const int isc_doubleloc = int(0x1400004f);
static const int isc_nodnotfnd = int(0x14000050);
static const int isc_dupnodfnd = int(0x14000051);
static const int isc_locnotmar = int(0x14000052);
static const int isc_badpagtyp = int(0x14000053);
static const int isc_corrupt = int(0x14000054);
static const int isc_badpage = int(0x14000055);
static const int isc_badindex = int(0x14000056);
static const int isc_dbbnotzer = int(0x14000057);
static const int isc_tranotzer = int(0x14000058);
static const int isc_trareqmis = int(0x14000059);
static const int isc_badhndcnt = int(0x1400005a);
static const int isc_wrotpbver = int(0x1400005b);
static const int isc_wroblrver = int(0x1400005c);
static const int isc_wrodpbver = int(0x1400005d);
static const int isc_blobnotsup = int(0x1400005e);
static const int isc_badrelation = int(0x1400005f);
static const int isc_nodetach = int(0x14000060);
static const int isc_notremote = int(0x14000061);
static const int isc_trainlim = int(0x14000062);
static const int isc_notinlim = int(0x14000063);
static const int isc_traoutsta = int(0x14000064);
static const int isc_connect_reject = int(0x14000065);
static const int isc_dbfile = int(0x14000066);
static const int isc_orphan = int(0x14000067);
static const int isc_no_lock_mgr = int(0x14000068);
static const int isc_ctxinuse = int(0x14000069);
static const int isc_ctxnotdef = int(0x1400006a);
static const int isc_datnotsup = int(0x1400006b);
static const int isc_badmsgnum = int(0x1400006c);
static const int isc_badparnum = int(0x1400006d);
static const int isc_virmemexh = int(0x1400006e);
static const int isc_blocking_signal = int(0x1400006f);
static const int isc_lockmanerr = int(0x14000070);
static const int isc_journerr = int(0x14000071);
static const int isc_keytoobig = int(0x14000072);
static const int isc_nullsegkey = int(0x14000073);
static const int isc_sqlerr = int(0x14000074);
static const int isc_wrodynver = int(0x14000075);
static const int isc_funnotdef = int(0x14000076);
static const int isc_funmismat = int(0x14000077);
static const int isc_bad_msg_vec = int(0x14000078);
static const int isc_bad_detach = int(0x14000079);
static const int isc_noargacc_read = int(0x1400007a);
static const int isc_noargacc_write = int(0x1400007b);
static const int isc_read_only = int(0x1400007c);
static const int isc_ext_err = int(0x1400007d);
static const int isc_non_updatable = int(0x1400007e);
static const int isc_no_rollback = int(0x1400007f);
static const int isc_bad_sec_info = int(0x14000080);
static const int isc_invalid_sec_info = int(0x14000081);
static const int isc_misc_interpreted = int(0x14000082);
static const int isc_update_conflict = int(0x14000083);
static const int isc_unlicensed = int(0x14000084);
static const int isc_obj_in_use = int(0x14000085);
static const int isc_nofilter = int(0x14000086);
static const int isc_shadow_accessed = int(0x14000087);
static const int isc_invalid_sdl = int(0x14000088);
static const int isc_out_of_bounds = int(0x14000089);
static const int isc_invalid_dimension = int(0x1400008a);
static const int isc_rec_in_limbo = int(0x1400008b);
static const int isc_shadow_missing = int(0x1400008c);
static const int isc_cant_validate = int(0x1400008d);
static const int isc_cant_start_journal = int(0x1400008e);
static const int isc_gennotdef = int(0x1400008f);
static const int isc_cant_start_logging = int(0x14000090);
static const int isc_bad_segstr_type = int(0x14000091);
static const int isc_foreign_key = int(0x14000092);
static const int isc_high_minor = int(0x14000093);
static const int isc_tra_state = int(0x14000094);
static const int isc_trans_invalid = int(0x14000095);
static const int isc_buf_invalid = int(0x14000096);
static const int isc_indexnotdefined = int(0x14000097);
static const int isc_login = int(0x14000098);
static const int isc_invalid_bookmark = int(0x14000099);
static const int isc_bad_lock_level = int(0x1400009a);
static const int isc_relation_lock = int(0x1400009b);
static const int isc_record_lock = int(0x1400009c);
static const int isc_max_idx = int(0x1400009d);
static const int isc_jrn_enable = int(0x1400009e);
static const int isc_old_failure = int(0x1400009f);
static const int isc_old_in_progress = int(0x140000a0);
static const int isc_old_no_space = int(0x140000a1);
static const int isc_no_wal_no_jrn = int(0x140000a2);
static const int isc_num_old_files = int(0x140000a3);
static const int isc_wal_file_open = int(0x140000a4);
static const int isc_bad_stmt_handle = int(0x140000a5);
static const int isc_wal_failure = int(0x140000a6);
static const int isc_walw_err = int(0x140000a7);
static const int isc_logh_small = int(0x140000a8);
static const int isc_logh_inv_version = int(0x140000a9);
static const int isc_logh_open_flag = int(0x140000aa);
static const int isc_logh_open_flag2 = int(0x140000ab);
static const int isc_logh_diff_dbname = int(0x140000ac);
static const int isc_logf_unexpected_eof = int(0x140000ad);
static const int isc_logr_incomplete = int(0x140000ae);
static const int isc_logr_header_small = int(0x140000af);
static const int isc_logb_small = int(0x140000b0);
static const int isc_wal_illegal_attach = int(0x140000b1);
static const int isc_wal_invalid_wpb = int(0x140000b2);
static const int isc_wal_err_rollover = int(0x140000b3);
static const int isc_no_wal = int(0x140000b4);
static const int isc_drop_wal = int(0x140000b5);
static const int isc_stream_not_defined = int(0x140000b6);
static const int isc_wal_subsys_error = int(0x140000b7);
static const int isc_wal_subsys_corrupt = int(0x140000b8);
static const int isc_no_archive = int(0x140000b9);
static const int isc_shutinprog = int(0x140000ba);
static const int isc_range_in_use = int(0x140000bb);
static const int isc_range_not_found = int(0x140000bc);
static const int isc_charset_not_found = int(0x140000bd);
static const int isc_lock_timeout = int(0x140000be);
static const int isc_prcnotdef = int(0x140000bf);
static const int isc_prcmismat = int(0x140000c0);
static const int isc_wal_bugcheck = int(0x140000c1);
static const int isc_wal_cant_expand = int(0x140000c2);
static const int isc_codnotdef = int(0x140000c3);
static const int isc_xcpnotdef = int(0x140000c4);
static const int isc_except = int(0x140000c5);
static const int isc_cache_restart = int(0x140000c6);
static const int isc_bad_lock_handle = int(0x140000c7);
static const int isc_jrn_present = int(0x140000c8);
static const int isc_wal_err_rollover2 = int(0x140000c9);
static const int isc_wal_err_logwrite = int(0x140000ca);
static const int isc_wal_err_jrn_comm = int(0x140000cb);
static const int isc_wal_err_expansion = int(0x140000cc);
static const int isc_wal_err_setup = int(0x140000cd);
static const int isc_wal_err_ww_sync = int(0x140000ce);
static const int isc_wal_err_ww_start = int(0x140000cf);
static const int isc_shutdown = int(0x140000d0);
static const int isc_existing_priv_mod = int(0x140000d1);
static const int isc_primary_key_ref = int(0x140000d2);
static const int isc_primary_key_notnull = int(0x140000d3);
static const int isc_ref_cnstrnt_notfound = int(0x140000d4);
static const int isc_foreign_key_notfound = int(0x140000d5);
static const int isc_ref_cnstrnt_update = int(0x140000d6);
static const int isc_check_cnstrnt_update = int(0x140000d7);
static const int isc_check_cnstrnt_del = int(0x140000d8);
static const int isc_integ_index_seg_del = int(0x140000d9);
static const int isc_integ_index_seg_mod = int(0x140000da);
static const int isc_integ_index_del = int(0x140000db);
static const int isc_integ_index_mod = int(0x140000dc);
static const int isc_check_trig_del = int(0x140000dd);
static const int isc_check_trig_update = int(0x140000de);
static const int isc_cnstrnt_fld_del = int(0x140000df);
static const int isc_cnstrnt_fld_rename = int(0x140000e0);
static const int isc_rel_cnstrnt_update = int(0x140000e1);
static const int isc_constaint_on_view = int(0x140000e2);
static const int isc_invld_cnstrnt_type = int(0x140000e3);
static const int isc_primary_key_exists = int(0x140000e4);
static const int isc_systrig_update = int(0x140000e5);
static const int isc_not_rel_owner = int(0x140000e6);
static const int isc_grant_obj_notfound = int(0x140000e7);
static const int isc_grant_fld_notfound = int(0x140000e8);
static const int isc_grant_nopriv = int(0x140000e9);
static const int isc_nonsql_security_rel = int(0x140000ea);
static const int isc_nonsql_security_fld = int(0x140000eb);
static const int isc_wal_cache_err = int(0x140000ec);
static const int isc_shutfail = int(0x140000ed);
static const int isc_check_constraint = int(0x140000ee);
static const int isc_bad_svc_handle = int(0x140000ef);
static const int isc_shutwarn = int(0x140000f0);
static const int isc_wrospbver = int(0x140000f1);
static const int isc_bad_spb_form = int(0x140000f2);
static const int isc_svcnotdef = int(0x140000f3);
static const int isc_no_jrn = int(0x140000f4);
static const int isc_transliteration_failed = int(0x140000f5);
static const int isc_start_cm_for_wal = int(0x140000f6);
static const int isc_wal_ovflow_log_required = int(0x140000f7);
static const int isc_text_subtype = int(0x140000f8);
static const int isc_dsql_error = int(0x140000f9);
static const int isc_dsql_command_err = int(0x140000fa);
static const int isc_dsql_constant_err = int(0x140000fb);
static const int isc_dsql_cursor_err = int(0x140000fc);
static const int isc_dsql_datatype_err = int(0x140000fd);
static const int isc_dsql_decl_err = int(0x140000fe);
static const int isc_dsql_cursor_update_err = int(0x140000ff);
static const int isc_dsql_cursor_open_err = int(0x14000100);
static const int isc_dsql_cursor_close_err = int(0x14000101);
static const int isc_dsql_field_err = int(0x14000102);
static const int isc_dsql_internal_err = int(0x14000103);
static const int isc_dsql_relation_err = int(0x14000104);
static const int isc_dsql_procedure_err = int(0x14000105);
static const int isc_dsql_request_err = int(0x14000106);
static const int isc_dsql_sqlda_err = int(0x14000107);
static const int isc_dsql_var_count_err = int(0x14000108);
static const int isc_dsql_stmt_handle = int(0x14000109);
static const int isc_dsql_function_err = int(0x1400010a);
static const int isc_dsql_blob_err = int(0x1400010b);
static const int isc_collation_not_found = int(0x1400010c);
static const int isc_collation_not_for_charset = int(0x1400010d);
static const int isc_dsql_dup_option = int(0x1400010e);
static const int isc_dsql_tran_err = int(0x1400010f);
static const int isc_dsql_invalid_array = int(0x14000110);
static const int isc_dsql_max_arr_dim_exceeded = int(0x14000111);
static const int isc_dsql_arr_range_error = int(0x14000112);
static const int isc_dsql_trigger_err = int(0x14000113);
static const int isc_dsql_subselect_err = int(0x14000114);
static const int isc_dsql_crdb_prepare_err = int(0x14000115);
static const int isc_specify_field_err = int(0x14000116);
static const int isc_num_field_err = int(0x14000117);
static const int isc_col_name_err = int(0x14000118);
static const int isc_where_err = int(0x14000119);
static const int isc_table_view_err = int(0x1400011a);
static const int isc_distinct_err = int(0x1400011b);
static const int isc_key_field_count_err = int(0x1400011c);
static const int isc_subquery_err = int(0x1400011d);
static const int isc_expression_eval_err = int(0x1400011e);
static const int isc_node_err = int(0x1400011f);
static const int isc_command_end_err = int(0x14000120);
static const int isc_index_name = int(0x14000121);
static const int isc_exception_name = int(0x14000122);
static const int isc_field_name = int(0x14000123);
static const int isc_token_err = int(0x14000124);
static const int isc_union_err = int(0x14000125);
static const int isc_dsql_construct_err = int(0x14000126);
static const int isc_field_aggregate_err = int(0x14000127);
static const int isc_field_ref_err = int(0x14000128);
static const int isc_order_by_err = int(0x14000129);
static const int isc_return_mode_err = int(0x1400012a);
static const int isc_extern_func_err = int(0x1400012b);
static const int isc_alias_conflict_err = int(0x1400012c);
static const int isc_procedure_conflict_error = int(0x1400012d);
static const int isc_relation_conflict_err = int(0x1400012e);
static const int isc_dsql_domain_err = int(0x1400012f);
static const int isc_idx_seg_err = int(0x14000130);
static const int isc_node_name_err = int(0x14000131);
static const int isc_table_name = int(0x14000132);
static const int isc_proc_name = int(0x14000133);
static const int isc_idx_create_err = int(0x14000134);
static const int isc_wal_shadow_err = int(0x14000135);
static const int isc_dependency = int(0x14000136);
static const int isc_idx_key_err = int(0x14000137);
static const int isc_dsql_file_length_err = int(0x14000138);
static const int isc_dsql_shadow_number_err = int(0x14000139);
static const int isc_dsql_token_unk_err = int(0x1400013a);
static const int isc_dsql_no_relation_alias = int(0x1400013b);
static const int isc_indexname = int(0x1400013c);
static const int isc_no_stream_plan = int(0x1400013d);
static const int isc_stream_twice = int(0x1400013e);
static const int isc_stream_not_found = int(0x1400013f);
static const int isc_collation_requires_text = int(0x14000140);
static const int isc_dsql_domain_not_found = int(0x14000141);
static const int isc_index_unused = int(0x14000142);
static const int isc_dsql_self_join = int(0x14000143);
static const int isc_stream_bof = int(0x14000144);
static const int isc_stream_crack = int(0x14000145);
static const int isc_db_or_file_exists = int(0x14000146);
static const int isc_invalid_operator = int(0x14000147);
static const int isc_conn_lost = int(0x14000148);
static const int isc_bad_checksum = int(0x14000149);
static const int isc_page_type_err = int(0x1400014a);
static const int isc_ext_readonly_err = int(0x1400014b);
static const int isc_sing_select_err = int(0x1400014c);
static const int isc_psw_attach = int(0x1400014d);
static const int isc_psw_start_trans = int(0x1400014e);
static const int isc_invalid_direction = int(0x1400014f);
static const int isc_dsql_var_conflict = int(0x14000150);
static const int isc_dsql_no_blob_array = int(0x14000151);
static const int isc_dsql_base_table = int(0x14000152);
static const int isc_duplicate_base_table = int(0x14000153);
static const int isc_view_alias = int(0x14000154);
static const int isc_index_root_page_full = int(0x14000155);
static const int isc_dsql_blob_type_unknown = int(0x14000156);
static const int isc_req_max_clones_exceeded = int(0x14000157);
static const int isc_dsql_duplicate_spec = int(0x14000158);
static const int isc_unique_key_violation = int(0x14000159);
static const int isc_srvr_version_too_old = int(0x1400015a);
static const int isc_drdb_completed_with_errs = int(0x1400015b);
static const int isc_dsql_procedure_use_err = int(0x1400015c);
static const int isc_dsql_count_mismatch = int(0x1400015d);
static const int isc_blob_idx_err = int(0x1400015e);
static const int isc_array_idx_err = int(0x1400015f);
static const int isc_key_field_err = int(0x14000160);
static const int isc_no_delete = int(0x14000161);
static const int isc_del_last_field = int(0x14000162);
static const int isc_sort_err = int(0x14000163);
static const int isc_sort_mem_err = int(0x14000164);
static const int isc_version_err = int(0x14000165);
static const int isc_inval_key_posn = int(0x14000166);
static const int isc_no_segments_err = int(0x14000167);
static const int isc_crrp_data_err = int(0x14000168);
static const int isc_rec_size_err = int(0x14000169);
static const int isc_dsql_field_ref = int(0x1400016a);
static const int isc_req_depth_exceeded = int(0x1400016b);
static const int isc_no_field_access = int(0x1400016c);
static const int isc_no_dbkey = int(0x1400016d);
static const int isc_jrn_format_err = int(0x1400016e);
static const int isc_jrn_file_full = int(0x1400016f);
static const int isc_dsql_open_cursor_request = int(0x14000170);
static const int isc_ib_error = int(0x14000171);
static const int isc_cache_redef = int(0x14000172);
static const int isc_cache_too_small = int(0x14000173);
static const int isc_log_redef = int(0x14000174);
static const int isc_log_too_small = int(0x14000175);
static const int isc_partition_too_small = int(0x14000176);
static const int isc_partition_not_supp = int(0x14000177);
static const int isc_log_length_spec = int(0x14000178);
static const int isc_precision_err = int(0x14000179);
static const int isc_scale_nogt = int(0x1400017a);
static const int isc_expec_short = int(0x1400017b);
static const int isc_expec_long = int(0x1400017c);
static const int isc_expec_ushort = int(0x1400017d);
static const int isc_like_escape_invalid = int(0x1400017e);
static const int isc_svcnoexe = int(0x1400017f);
static const int isc_net_lookup_err = int(0x14000180);
static const int isc_service_unknown = int(0x14000181);
static const int isc_host_unknown = int(0x14000182);
static const int isc_grant_nopriv_on_base = int(0x14000183);
static const int isc_dyn_fld_ambiguous = int(0x14000184);
static const int isc_dsql_agg_ref_err = int(0x14000185);
static const int isc_complex_view = int(0x14000186);
static const int isc_unprepared_stmt = int(0x14000187);
static const int isc_expec_positive = int(0x14000188);
static const int isc_dsql_sqlda_value_err = int(0x14000189);
static const int isc_invalid_array_id = int(0x1400018a);
static const int isc_extfile_uns_op = int(0x1400018b);
static const int isc_svc_in_use = int(0x1400018c);
static const int isc_err_stack_limit = int(0x1400018d);
static const int isc_invalid_key = int(0x1400018e);
static const int isc_net_init_error = int(0x1400018f);
static const int isc_loadlib_failure = int(0x14000190);
static const int isc_network_error = int(0x14000191);
static const int isc_net_connect_err = int(0x14000192);
static const int isc_net_connect_listen_err = int(0x14000193);
static const int isc_net_event_connect_err = int(0x14000194);
static const int isc_net_event_listen_err = int(0x14000195);
static const int isc_net_read_err = int(0x14000196);
static const int isc_net_write_err = int(0x14000197);
static const int isc_integ_index_deactivate = int(0x14000198);
static const int isc_integ_deactivate_primary = int(0x14000199);
static const int isc_cse_not_supported = int(0x1400019a);
static const int isc_tra_must_sweep = int(0x1400019b);
static const int isc_unsupported_network_drive = int(0x1400019c);
static const int isc_io_create_err = int(0x1400019d);
static const int isc_io_open_err = int(0x1400019e);
static const int isc_io_close_err = int(0x1400019f);
static const int isc_io_read_err = int(0x140001a0);
static const int isc_io_write_err = int(0x140001a1);
static const int isc_io_delete_err = int(0x140001a2);
static const int isc_io_access_err = int(0x140001a3);
static const int isc_udf_exception = int(0x140001a4);
static const int isc_lost_db_connection = int(0x140001a5);
static const int isc_no_write_user_priv = int(0x140001a6);
static const int isc_token_too_long = int(0x140001a7);
static const int isc_max_att_exceeded = int(0x140001a8);
static const int isc_login_same_as_role_name = int(0x140001a9);
static const int isc_reftable_requires_pk = int(0x140001aa);
static const int isc_usrname_too_long = int(0x140001ab);
static const int isc_password_too_long = int(0x140001ac);
static const int isc_usrname_required = int(0x140001ad);
static const int isc_password_required = int(0x140001ae);
static const int isc_bad_protocol = int(0x140001af);
static const int isc_dup_usrname_found = int(0x140001b0);
static const int isc_usrname_not_found = int(0x140001b1);
static const int isc_error_adding_sec_record = int(0x140001b2);
static const int isc_error_modifying_sec_record = int(0x140001b3);
static const int isc_error_deleting_sec_record = int(0x140001b4);
static const int isc_error_updating_sec_db = int(0x140001b5);
static const int isc_sort_rec_size_err = int(0x140001b6);
static const int isc_bad_default_value = int(0x140001b7);
static const int isc_invalid_clause = int(0x140001b8);
static const int isc_too_many_handles = int(0x140001b9);
static const int isc_optimizer_blk_exc = int(0x140001ba);
static const int isc_invalid_string_constant = int(0x140001bb);
static const int isc_transitional_date = int(0x140001bc);
static const int isc_read_only_database = int(0x140001bd);
static const int isc_must_be_dialect_2_and_up = int(0x140001be);
static const int isc_blob_filter_exception = int(0x140001bf);
static const int isc_exception_access_violation = int(0x140001c0);
static const int isc_exception_datatype_missalignment = int(0x140001c1);
static const int isc_exception_array_bounds_exceeded = int(0x140001c2);
static const int isc_exception_float_denormal_operand = int(0x140001c3);
static const int isc_exception_float_divide_by_zero = int(0x140001c4);
static const int isc_exception_float_inexact_result = int(0x140001c5);
static const int isc_exception_float_invalid_operand = int(0x140001c6);
static const int isc_exception_float_overflow = int(0x140001c7);
static const int isc_exception_float_stack_check = int(0x140001c8);
static const int isc_exception_float_underflow = int(0x140001c9);
static const int isc_exception_integer_divide_by_zero = int(0x140001ca);
static const int isc_exception_integer_overflow = int(0x140001cb);
static const int isc_exception_unknown = int(0x140001cc);
static const int isc_exception_stack_overflow = int(0x140001cd);
static const int isc_exception_sigsegv = int(0x140001ce);
static const int isc_exception_sigill = int(0x140001cf);
static const int isc_exception_sigbus = int(0x140001d0);
static const int isc_exception_sigfpe = int(0x140001d1);
static const int isc_ext_file_delete = int(0x140001d2);
static const int isc_ext_file_modify = int(0x140001d3);
static const int isc_adm_task_denied = int(0x140001d4);
static const int isc_extract_input_mismatch = int(0x140001d5);
static const int isc_insufficient_svc_privileges = int(0x140001d6);
static const int isc_file_in_use = int(0x140001d7);
static const int isc_service_att_err = int(0x140001d8);
static const int isc_ddl_not_allowed_by_db_sql_dial = int(0x140001d9);
static const int isc_cancelled = int(0x140001da);
static const int isc_unexp_spb_form = int(0x140001db);
static const int isc_sql_dialect_datatype_unsupport = int(0x140001dc);
static const int isc_svcnouser = int(0x140001dd);
static const int isc_depend_on_uncommitted_rel = int(0x140001de);
static const int isc_svc_name_missing = int(0x140001df);
static const int isc_too_many_contexts = int(0x140001e0);
static const int isc_datype_notsup = int(0x140001e1);
static const int isc_dialect_reset_warning = int(0x140001e2);
static const int isc_dialect_not_changed = int(0x140001e3);
static const int isc_database_create_failed = int(0x140001e4);
static const int isc_inv_dialect_specified = int(0x140001e5);
static const int isc_valid_db_dialects = int(0x140001e6);
static const int isc_sqlwarn = int(0x140001e7);
static const int isc_dtype_renamed = int(0x140001e8);
static const int isc_extern_func_dir_error = int(0x140001e9);
static const int isc_date_range_exceeded = int(0x140001ea);
static const int isc_inv_client_dialect_specified = int(0x140001eb);
static const int isc_valid_client_dialects = int(0x140001ec);
static const int isc_optimizer_between_err = int(0x140001ed);
static const int isc_service_not_supported = int(0x140001ee);
static const int isc_generator_name = int(0x140001ef);
static const int isc_udf_name = int(0x140001f0);
static const int isc_bad_limit_param = int(0x140001f1);
static const int isc_bad_skip_param = int(0x140001f2);
static const int isc_io_32bit_exceeded_err = int(0x140001f3);
static const int isc_invalid_savepoint = int(0x140001f4);
static const int isc_dsql_column_pos_err = int(0x140001f5);
static const int isc_dsql_agg_where_err = int(0x140001f6);
static const int isc_dsql_agg_group_err = int(0x140001f7);
static const int isc_dsql_agg_column_err = int(0x140001f8);
static const int isc_dsql_agg_having_err = int(0x140001f9);
static const int isc_dsql_agg_nested_err = int(0x140001fa);
static const int isc_exec_sql_invalid_arg = int(0x140001fb);
static const int isc_exec_sql_invalid_req = int(0x140001fc);
static const int isc_exec_sql_invalid_var = int(0x140001fd);
static const int isc_exec_sql_max_call_exceeded = int(0x140001fe);
static const int isc_conf_access_denied = int(0x140001ff);
static const int isc_wrong_backup_state = int(0x14000200);
static const int isc_wal_backup_err = int(0x14000201);
static const int isc_cursor_not_open = int(0x14000202);
static const int isc_bad_shutdown_mode = int(0x14000203);
static const int isc_concat_overflow = int(0x14000204);
static const int isc_bad_substring_offset = int(0x14000205);
static const int isc_foreign_key_target_doesnt_exist = int(0x14000206);
static const int isc_foreign_key_references_present = int(0x14000207);
static const int isc_no_update = int(0x14000208);
static const int isc_cursor_already_open = int(0x14000209);
static const int isc_stack_trace = int(0x1400020a);
static const int isc_ctx_var_not_found = int(0x1400020b);
static const int isc_ctx_namespace_invalid = int(0x1400020c);
static const int isc_ctx_too_big = int(0x1400020d);
static const int isc_ctx_bad_argument = int(0x1400020e);
static const int isc_identifier_too_long = int(0x1400020f);
static const int isc_except2 = int(0x14000210);
static const int isc_malformed_string = int(0x14000211);
static const int isc_prc_out_param_mismatch = int(0x14000212);
static const int isc_command_end_err2 = int(0x14000213);
static const int isc_partner_idx_incompat_type = int(0x14000214);
static const int isc_bad_substring_length = int(0x14000215);
static const int isc_charset_not_installed = int(0x14000216);
static const int isc_collation_not_installed = int(0x14000217);
static const int isc_att_shutdown = int(0x14000218);
static const int isc_blobtoobig = int(0x14000219);
static const int isc_must_have_phys_field = int(0x1400021a);
static const int isc_invalid_time_precision = int(0x1400021b);
static const int isc_blob_convert_error = int(0x1400021c);
static const int isc_array_convert_error = int(0x1400021d);
static const int isc_record_lock_not_supp = int(0x1400021e);
static const int isc_partner_idx_not_found = int(0x1400021f);
static const int isc_savepoint_err = int(0x140001ef);
static const int isc_generator_name_2 = int(0x140001f0);
static const int isc_udf_name_2 = int(0x140001f1);
static const int isc_table_truncated = int(0x1400021c);
static const int isc_dyn_delete_subscribers_failed = int(0x14080105);
static const int isc_dyn_subscribers_exist = int(0x14080106);
static const int isc_dyn_delete_subscription_failed = int(0x14080107);
static const int isc_gfix_db_name = int(0x14030001);
static const int isc_gfix_invalid_sw = int(0x14030002);
static const int isc_gfix_incmp_sw = int(0x14030004);
static const int isc_gfix_replay_req = int(0x14030005);
static const int isc_gfix_pgbuf_req = int(0x14030006);
static const int isc_gfix_val_req = int(0x14030007);
static const int isc_gfix_pval_req = int(0x14030008);
static const int isc_gfix_trn_req = int(0x14030009);
static const int isc_gfix_full_req = int(0x1403000c);
static const int isc_gfix_usrname_req = int(0x1403000d);
static const int isc_gfix_pass_req = int(0x1403000e);
static const int isc_gfix_subs_name = int(0x1403000f);
static const int isc_gfix_wal_req = int(0x14030010);
static const int isc_gfix_sec_req = int(0x14030011);
static const int isc_gfix_nval_req = int(0x14030012);
static const int isc_gfix_type_shut = int(0x14030013);
static const int isc_gfix_retry = int(0x14030014);
static const int isc_gfix_retry_db = int(0x14030017);
static const int isc_gfix_exceed_max = int(0x1403003f);
static const int isc_gfix_corrupt_pool = int(0x14030040);
static const int isc_gfix_mem_exhausted = int(0x14030041);
static const int isc_gfix_bad_pool = int(0x14030042);
static const int isc_gfix_trn_not_valid = int(0x14030043);
static const int isc_gfix_unexp_eoi = int(0x14030054);
static const int isc_gfix_recon_fail = int(0x1403005a);
static const int isc_gfix_trn_unknown = int(0x1403006c);
static const int isc_gfix_mode_req = int(0x1403006e);
static const int isc_gfix_opt_SQL_dialect = int(0x1403006f);
static const int isc_gfix_pzval_req = int(0x14030072);
static const int isc_gfix_commits_opt = int(0x14030071);
static const int isc_dsql_dbkey_from_non_table = int(0x14070002);
static const int isc_dsql_transitional_numeric = int(0x14070003);
static const int isc_dsql_dialect_warning_expr = int(0x14070004);
static const int isc_sql_db_dialect_dtype_unsupport = int(0x14070005);
static const int isc_isc_sql_dialect_conflict_num = int(0x14070007);
static const int isc_dsql_warning_number_ambiguous = int(0x14070008);
static const int isc_dsql_warning_number_ambiguous1 = int(0x14070009);
static const int isc_dsql_warn_precision_ambiguous = int(0x1407000a);
static const int isc_dsql_warn_precision_ambiguous1 = int(0x1407000b);
static const int isc_dsql_warn_precision_ambiguous2 = int(0x1407000c);
static const int isc_dsql_ambiguous_field_name = int(0x1407000d);
static const int isc_dsql_udf_return_pos_err = int(0x1407000e);
static const int isc_dsql_invalid_label = int(0x1407000f);
static const int isc_dsql_datatypes_not_comparable = int(0x14070010);
static const int isc_dsql_cursor_invalid = int(0x14070011);
static const int isc_dsql_cursor_redefined = int(0x14070012);
static const int isc_dsql_cursor_not_found = int(0x14070013);
static const int isc_dsql_cursor_exists = int(0x14070014);
static const int isc_dsql_cursor_rel_ambiguous = int(0x14070015);
static const int isc_dsql_cursor_rel_not_found = int(0x14070016);
static const int isc_dsql_cursor_not_open = int(0x14070017);
static const int isc_dsql_type_not_supp_ext_tab = int(0x14070018);
static const int isc_dsql_rows_ties_err = int(0x1407000d);
static const int isc_dsql_cursor_stmt_err = int(0x1407000e);
static const int isc_dsql_on_commit_invalid = int(0x1407000f);
static const int isc_dsql_gen_cnstrnt_ref_temp = int(0x14070010);
static const int isc_dsql_persist_cnstrnt_ref_temp = int(0x14070011);
static const int isc_dsql_temp_cnstrnt_ref_persist = int(0x14070012);
static const int isc_dsql_persist_refs_temp = int(0x14070013);
static const int isc_dsql_temp_refs_persist = int(0x14070014);
static const int isc_dsql_temp_refs_mismatch = int(0x14070015);
static const int isc_dsql_usrname_lower = int(0x14070016);
static const int isc_dyn_filter_not_found = int(0x14080025);
static const int isc_dyn_func_not_found = int(0x14080029);
static const int isc_dyn_index_not_found = int(0x14080030);
static const int isc_dyn_view_not_found = int(0x14080036);
static const int isc_dyn_domain_not_found = int(0x14080059);
static const int isc_dyn_cant_modify_auto_trig = int(0x1408006d);
static const int isc_dyn_proc_not_found = int(0x1408008c);
static const int isc_dyn_exception_not_found = int(0x14080090);
static const int isc_dyn_proc_param_not_found = int(0x14080092);
static const int isc_dyn_trig_not_found = int(0x14080093);
static const int isc_dyn_charset_not_found = int(0x14080097);
static const int isc_dyn_collation_not_found = int(0x14080098);
static const int isc_dyn_role_not_found = int(0x1408009b);
static const int isc_dyn_name_longer = int(0x1408009f);
static const int isc_dyn_gen_not_found = int(0x140800d6);
static const int isc_dyn_coll_used_table = int(0x140800eb);
static const int isc_dyn_coll_used_domain = int(0x140800ec);
static const int isc_dyn_cannot_del_syscoll = int(0x140800ed);
static const int isc_dyn_cannot_del_def_coll = int(0x140800ee);
static const int isc_dyn_table_not_found = int(0x140800f1);
static const int isc_dyn_coll_used_procedure = int(0x140800f3);
static const int isc_dyn_package_not_found = int(0x14080100);
static const int isc_dyn_schema_not_found = int(0x14080101);
static const int isc_dyn_cannot_mod_sysproc = int(0x14080102);
static const int isc_dyn_cannot_mod_systrig = int(0x14080103);
static const int isc_dyn_cannot_mod_sysfunc = int(0x14080104);
static const int isc_dyn_invalid_ddl_proc = int(0x14080105);
static const int isc_dyn_invalid_ddl_trig = int(0x14080106);
static const int isc_dyn_funcnotdef_package = int(0x14080107);
static const int isc_dyn_procnotdef_package = int(0x14080108);
static const int isc_dyn_funcsignat_package = int(0x14080109);
static const int isc_dyn_procsignat_package = int(0x1408010a);
static const int isc_dyn_defvaldecl_package = int(0x1408010b);
static const int isc_dyn_package_body_exists = int(0x1408010d);
static const int isc_dyn_invalid_ddl_func = int(0x1408010e);
static const int isc_dyn_newfc_oldsyntax = int(0x1408010f);
static const int isc_dyn_func_param_not_found = int(0x14080116);
static const int isc_dyn_routine_param_not_found = int(0x14080117);
static const int isc_dyn_routine_param_ambiguous = int(0x14080118);
static const int isc_dyn_coll_used_function = int(0x14080119);
static const int isc_dyn_domain_used_function = int(0x1408011a);
static const int isc_dsql_alter_charset_failed = int(0x140d03ca);
static const int isc_dsql_comment_on_failed = int(0x140d03cb);
static const int isc_dsql_create_func_failed = int(0x140d03cc);
static const int isc_dsql_alter_func_failed = int(0x140d03cd);
static const int isc_dsql_create_alter_func_failed = int(0x140d03ce);
static const int isc_dsql_drop_func_failed = int(0x140d03cf);
static const int isc_dsql_recreate_func_failed = int(0x140d03d0);
static const int isc_dsql_create_proc_failed = int(0x140d03d1);
static const int isc_dsql_alter_proc_failed = int(0x140d03d2);
static const int isc_dsql_create_alter_proc_failed = int(0x140d03d3);
static const int isc_dsql_drop_proc_failed = int(0x140d03d4);
static const int isc_dsql_recreate_proc_failed = int(0x140d03d5);
static const int isc_dsql_create_trigger_failed = int(0x140d03d6);
static const int isc_dsql_alter_trigger_failed = int(0x140d03d7);
static const int isc_dsql_create_alter_trigger_failed = int(0x140d03d8);
static const int isc_dsql_drop_trigger_failed = int(0x140d03d9);
static const int isc_dsql_recreate_trigger_failed = int(0x140d03da);
static const int isc_dsql_create_collation_failed = int(0x140d03db);
static const int isc_dsql_drop_collation_failed = int(0x140d03dc);
static const int isc_dsql_create_domain_failed = int(0x140d03dd);
static const int isc_dsql_alter_domain_failed = int(0x140d03de);
static const int isc_dsql_drop_domain_failed = int(0x140d03df);
static const int isc_dsql_create_except_failed = int(0x140d03e0);
static const int isc_dsql_alter_except_failed = int(0x140d03e1);
static const int isc_dsql_create_alter_except_failed = int(0x140d03e2);
static const int isc_dsql_recreate_except_failed = int(0x140d03e3);
static const int isc_dsql_drop_except_failed = int(0x140d03e4);
static const int isc_dsql_create_sequence_failed = int(0x140d03e5);
static const int isc_dsql_create_table_failed = int(0x140d03e6);
static const int isc_dsql_alter_table_failed = int(0x140d03e7);
static const int isc_dsql_drop_table_failed = int(0x140d03e8);
static const int isc_dsql_recreate_table_failed = int(0x140d03e9);
static const int isc_dsql_create_pack_failed = int(0x140d03ea);
static const int isc_dsql_alter_pack_failed = int(0x140d03eb);
static const int isc_dsql_create_alter_pack_failed = int(0x140d03ec);
static const int isc_dsql_drop_pack_failed = int(0x140d03ed);
static const int isc_dsql_recreate_pack_failed = int(0x140d03ee);
static const int isc_dsql_create_pack_body_failed = int(0x140d03ef);
static const int isc_dsql_drop_pack_body_failed = int(0x140d03f0);
static const int isc_dsql_recreate_pack_body_failed = int(0x140d03f1);
static const int isc_dsql_create_view_failed = int(0x140d03f2);
static const int isc_dsql_alter_view_failed = int(0x140d03f3);
static const int isc_dsql_create_alter_view_failed = int(0x140d03f4);
static const int isc_dsql_recreate_view_failed = int(0x140d03f5);
static const int isc_dsql_drop_view_failed = int(0x140d03f6);
static const int isc_dyn_role_does_not_exist = int(0x140800bc);
static const int isc_dyn_no_grant_admin_opt = int(0x140800bd);
static const int isc_dyn_user_not_role_member = int(0x140800be);
static const int isc_dyn_delete_role_failed = int(0x140800bf);
static const int isc_dyn_grant_role_to_user = int(0x140800c0);
static const int isc_dyn_inv_sql_role_name = int(0x140800c1);
static const int isc_dyn_dup_sql_role = int(0x140800c2);
static const int isc_dyn_kywd_spec_for_role = int(0x140800c3);
static const int isc_dyn_roles_not_supported = int(0x140800c4);
static const int isc_dyn_domain_name_exists = int(0x140800cc);
static const int isc_dyn_field_name_exists = int(0x140800cd);
static const int isc_dyn_dependency_exists = int(0x140800ce);
static const int isc_dyn_dtype_invalid = int(0x140800cf);
static const int isc_dyn_char_fld_too_small = int(0x140800d0);
static const int isc_dyn_invalid_dtype_conversion = int(0x140800d1);
static const int isc_dyn_dtype_conv_invalid = int(0x140800d2);
static const int isc_dyn_zero_len_id = int(0x140800d4);
static const int isc_dyn_gen_does_not_exist = int(0x140800d4);
static const int isc_dyn_delete_generator_failed = int(0x140800d5);
static const int isc_dyn_drop_db_owner = int(0x140800e4);
static const int isc_gbak_unknown_switch = int(0x140c0001);
static const int isc_gbak_page_size_missing = int(0x140c0002);
static const int isc_gbak_page_size_toobig = int(0x140c0003);
static const int isc_gbak_redir_ouput_missing = int(0x140c0004);
static const int isc_gbak_switches_conflict = int(0x140c0005);
static const int isc_gbak_unknown_device = int(0x140c0006);
static const int isc_gbak_no_protection = int(0x140c0007);
static const int isc_gbak_page_size_not_allowed = int(0x140c0008);
static const int isc_gbak_multi_source_dest = int(0x140c0009);
static const int isc_gbak_filename_missing = int(0x140c000a);
static const int isc_gbak_dup_inout_names = int(0x140c000b);
static const int isc_gbak_inv_page_size = int(0x140c000c);
static const int isc_gbak_db_specified = int(0x140c000d);
static const int isc_gbak_db_exists = int(0x140c000e);
static const int isc_gbak_unk_device = int(0x140c000f);
static const int isc_gbak_blob_info_failed = int(0x140c0014);
static const int isc_gbak_unk_blob_item = int(0x140c0015);
static const int isc_gbak_get_seg_failed = int(0x140c0016);
static const int isc_gbak_close_blob_failed = int(0x140c0017);
static const int isc_gbak_open_blob_failed = int(0x140c0018);
static const int isc_gbak_put_blr_gen_id_failed = int(0x140c0019);
static const int isc_gbak_unk_type = int(0x140c001a);
static const int isc_gbak_comp_req_failed = int(0x140c001b);
static const int isc_gbak_start_req_failed = int(0x140c001c);
static const int isc_gbak_rec_failed = int(0x140c001d);
static const int isc_gbak_rel_req_failed = int(0x140c001e);
static const int isc_gbak_db_info_failed = int(0x140c001f);
static const int isc_gbak_no_db_desc = int(0x140c0020);
static const int isc_gbak_db_create_failed = int(0x140c0021);
static const int isc_gbak_decomp_len_error = int(0x140c0022);
static const int isc_gbak_tbl_missing = int(0x140c0023);
static const int isc_gbak_blob_col_missing = int(0x140c0024);
static const int isc_gbak_create_blob_failed = int(0x140c0025);
static const int isc_gbak_put_seg_failed = int(0x140c0026);
static const int isc_gbak_rec_len_exp = int(0x140c0027);
static const int isc_gbak_inv_rec_len = int(0x140c0028);
static const int isc_gbak_exp_data_type = int(0x140c0029);
static const int isc_gbak_gen_id_failed = int(0x140c002a);
static const int isc_gbak_unk_rec_type = int(0x140c002b);
static const int isc_gbak_inv_bkup_ver = int(0x140c002c);
static const int isc_gbak_missing_bkup_desc = int(0x140c002d);
static const int isc_gbak_string_trunc = int(0x140c002e);
static const int isc_gbak_cant_rest_record = int(0x140c002f);
static const int isc_gbak_send_failed = int(0x140c0030);
static const int isc_gbak_no_tbl_name = int(0x140c0031);
static const int isc_gbak_unexp_eof = int(0x140c0032);
static const int isc_gbak_db_format_too_old = int(0x140c0033);
static const int isc_gbak_inv_array_dim = int(0x140c0034);
static const int isc_gbak_xdr_len_expected = int(0x140c0037);
static const int isc_gbak_open_bkup_error = int(0x140c0041);
static const int isc_gbak_open_error = int(0x140c0042);
static const int isc_gbak_missing_block_fac = int(0x140c00b6);
static const int isc_gbak_inv_block_fac = int(0x140c00b7);
static const int isc_gbak_block_fac_specified = int(0x140c00b8);
static const int isc_gbak_missing_username = int(0x140c00bc);
static const int isc_gbak_missing_password = int(0x140c00bd);
static const int isc_gbak_missing_skipped_bytes = int(0x140c00c8);
static const int isc_gbak_inv_skipped_bytes = int(0x140c00c9);
static const int isc_gbak_err_restore_charset = int(0x140c00d5);
static const int isc_gbak_err_restore_collation = int(0x140c00d7);
static const int isc_gbak_read_error = int(0x140c00dc);
static const int isc_gbak_write_error = int(0x140c00dd);
static const int isc_gbak_db_in_use = int(0x140c00e9);
static const int isc_gbak_sysmemex = int(0x140c00ee);
static const int isc_gbak_restore_role_failed = int(0x140c00fa);
static const int isc_gbak_role_op_missing = int(0x140c00fd);
static const int isc_gbak_page_buffers_missing = int(0x140c0102);
static const int isc_gbak_page_buffers_wrong_param = int(0x140c0103);
static const int isc_gbak_page_buffers_restore = int(0x140c0104);
static const int isc_gbak_inv_size = int(0x140c0106);
static const int isc_gbak_file_outof_sequence = int(0x140c0107);
static const int isc_gbak_join_file_missing = int(0x140c0108);
static const int isc_gbak_stdin_not_supptd = int(0x140c0109);
static const int isc_gbak_stdout_not_supptd = int(0x140c010a);
static const int isc_gbak_bkup_corrupt = int(0x140c010b);
static const int isc_gbak_unk_db_file_spec = int(0x140c010c);
static const int isc_gbak_hdr_write_failed = int(0x140c010d);
static const int isc_gbak_disk_space_ex = int(0x140c010e);
static const int isc_gbak_size_lt_min = int(0x140c010f);
static const int isc_gbak_svc_name_missing = int(0x140c0111);
static const int isc_gbak_not_ownr = int(0x140c0112);
static const int isc_gbak_mode_req = int(0x140c0117);
static const int isc_gbak_just_data = int(0x140c0119);
static const int isc_gbak_data_only = int(0x140c011a);
static const int isc_dsql_tableview_not_found = int(0x140800af);
static const int isc_dsql_too_old_ods = int(0x140d0395);
static const int isc_dsql_table_not_found = int(0x140d0396);
static const int isc_dsql_view_not_found = int(0x140d0397);
static const int isc_dsql_line_col_error = int(0x140d0398);
static const int isc_dsql_unknown_pos = int(0x140d0399);
static const int isc_dsql_no_dup_name = int(0x140d039a);
static const int isc_dsql_too_many_values = int(0x140d039b);
static const int isc_gbak_validate_restore = int(0x140c011a);
static const int isc_gsec_cant_open_db = int(0x1412000f);
static const int isc_gsec_switches_error = int(0x14120010);
static const int isc_gsec_no_op_spec = int(0x14120011);
static const int isc_gsec_no_usr_name = int(0x14120012);
static const int isc_gsec_err_add = int(0x14120013);
static const int isc_gsec_err_modify = int(0x14120014);
static const int isc_gsec_err_find_mod = int(0x14120015);
static const int isc_gsec_err_rec_not_found = int(0x14120016);
static const int isc_gsec_err_delete = int(0x14120017);
static const int isc_gsec_err_find_del = int(0x14120018);
static const int isc_gsec_err_find_disp = int(0x1412001c);
static const int isc_gsec_inv_param = int(0x1412001d);
static const int isc_gsec_op_specified = int(0x1412001e);
static const int isc_gsec_pw_specified = int(0x1412001f);
static const int isc_gsec_uid_specified = int(0x14120020);
static const int isc_gsec_gid_specified = int(0x14120021);
static const int isc_gsec_proj_specified = int(0x14120022);
static const int isc_gsec_org_specified = int(0x14120023);
static const int isc_gsec_fname_specified = int(0x14120024);
static const int isc_gsec_mname_specified = int(0x14120025);
static const int isc_gsec_lname_specified = int(0x14120026);
static const int isc_gsec_inv_switch = int(0x14120028);
static const int isc_gsec_amb_switch = int(0x14120029);
static const int isc_gsec_no_op_specified = int(0x1412002a);
static const int isc_gsec_params_not_allowed = int(0x1412002b);
static const int isc_gsec_incompat_switch = int(0x1412002c);
static const int isc_gsec_inv_username = int(0x1412004c);
static const int isc_gsec_inv_pw_length = int(0x1412004d);
static const int isc_gsec_db_specified = int(0x1412004e);
static const int isc_gsec_db_admin_specified = int(0x1412004f);
static const int isc_gsec_db_admin_pw_specified = int(0x14120050);
static const int isc_gsec_sql_role_specified = int(0x14120051);
static const int isc_license_no_file = int(0x14130000);
static const int isc_license_op_specified = int(0x14130013);
static const int isc_license_op_missing = int(0x14130014);
static const int isc_license_inv_switch = int(0x14130015);
static const int isc_license_inv_switch_combo = int(0x14130016);
static const int isc_license_inv_op_combo = int(0x14130017);
static const int isc_license_amb_switch = int(0x14130018);
static const int isc_license_inv_parameter = int(0x14130019);
static const int isc_license_param_specified = int(0x1413001a);
static const int isc_license_param_req = int(0x1413001b);
static const int isc_license_syntx_error = int(0x1413001c);
static const int isc_license_dup_id = int(0x1413001e);
static const int isc_license_inv_id_key = int(0x1413001f);
static const int isc_license_err_remove = int(0x14130020);
static const int isc_license_err_update = int(0x14130021);
static const int isc_license_err_convert = int(0x14130022);
static const int isc_license_err_unk = int(0x14130023);
static const int isc_license_svc_err_add = int(0x14130024);
static const int isc_license_svc_err_remove = int(0x14130025);
static const int isc_license_eval_exists = int(0x1413003b);
static const int isc_smp_cpu_license = int(0x14130042);
static const int isc_node_locked_full_unlimited_serve = int(0x14130043);
static const int isc_dev_only_full_server_licenses = int(0x14130044);
static const int isc_license_not_registered = int(0x14130045);
static const int isc_license_library_unloadable = int(0x14130046);
static const int isc_license_registration_file = int(0x14130047);
static const int isc_license_expire_limit = int(0x14130048);
static const int isc_license_bad_reg_file = int(0x14130049);
static const int isc_license_bad_lic_file = int(0x1413004a);
static const int isc_gstat_unknown_switch = int(0x14150001);
static const int isc_gstat_retry = int(0x14150002);
static const int isc_gstat_wrong_ods = int(0x14150003);
static const int isc_gstat_unexpected_eof = int(0x14150004);
static const int isc_gstat_open_err = int(0x1415001d);
static const int isc_gstat_read_err = int(0x1415001e);
static const int isc_gstat_sysmemex = int(0x1415001f);
extern DELPHI_PACKAGE int __fastcall XSQLDA_LENGTH_V1(int n);
extern DELPHI_PACKAGE int __fastcall XSQLDA_LENGTH_V2(int n);
extern DELPHI_PACKAGE int __fastcall XSQLVAR_LENGTH(int num_rows, int num_vars);
extern DELPHI_PACKAGE void __fastcall ADD_SPB_LENGTH(PISC_UCHAR &p, int length);
extern DELPHI_PACKAGE void __fastcall ADD_SPB_NUMERIC(PISC_UCHAR &p, int data);
extern DELPHI_PACKAGE System::Int8 __fastcall GETB(PBSTREAM p, TBLOB_get bg);
extern DELPHI_PACKAGE int __fastcall PUTB(System::Int8 x, PBSTREAM p, TBLOB_put bp);
extern DELPHI_PACKAGE int __fastcall PUTBX(System::Int8 x, PBSTREAM p, TBLOB_put bp);
}	/* namespace Ibcli */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_IBCLI)
using namespace Firedac::Phys::Ibcli;
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
#endif	// Firedac_Phys_IbcliHPP
