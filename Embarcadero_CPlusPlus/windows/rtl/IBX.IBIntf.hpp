// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBIntf.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbintfHPP
#define Ibx_IbintfHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <IBX.IBHeader.hpp>
#include <IBX.IBInstallHeader.hpp>
#include <IBX.IBExternals.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibintf
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IGDSLibrary;
typedef System::DelphiInterface<IGDSLibrary> _di_IGDSLibrary;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{BCAC76DD-25EB-4261-84FE-0CB3310435E2}") IGDSLibrary  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall LibraryName() = 0 ;
	virtual void __fastcall LoadIBLibrary() = 0 ;
	virtual void __fastcall FreeIBLibrary() = 0 ;
	virtual bool __fastcall TryIBLoad() = 0 ;
	virtual void __fastcall CheckIBLoaded() = 0 ;
	virtual System::Currency __fastcall GetIBClientVersion() = 0 ;
	virtual NativeInt __fastcall isc_attach_database(Ibx::Ibexternals::PISC_STATUS status_vector, short db_name_length, System::PByte db_name, Ibx::Ibheader::PISC_DB_HANDLE db_handle, short parm_buffer_length, System::PByte parm_buffer) = 0 ;
	virtual NativeInt __fastcall isc_array_gen_sdl(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_ARRAY_DESC isc_array_desc, Ibx::Ibexternals::PShort isc_arg3, System::PByte isc_arg4, Ibx::Ibexternals::PShort isc_arg5) = 0 ;
	virtual NativeInt __fastcall isc_array_gen_sdl2(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_ARRAY_DESC_V2 isc_array_desc, Ibx::Ibexternals::PShort isc_arg3, System::PByte isc_arg4, Ibx::Ibexternals::PShort isc_arg5) = 0 ;
	virtual NativeInt __fastcall isc_array_get_slice(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibheader::PISC_TR_HANDLE trans_handle, Ibx::Ibheader::PISC_QUAD array_id, Ibx::Ibheader::PISC_ARRAY_DESC descriptor, Ibx::Ibexternals::PVoid dest_array, Ibx::Ibexternals::PISC_LONG slice_length) = 0 ;
	virtual NativeInt __fastcall isc_array_get_slice2(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibheader::PISC_TR_HANDLE trans_handle, Ibx::Ibheader::PISC_QUAD array_id, Ibx::Ibheader::PISC_ARRAY_DESC_V2 descriptor, Ibx::Ibexternals::PVoid dest_array, Ibx::Ibexternals::PISC_LONG slice_length) = 0 ;
	virtual NativeInt __fastcall isc_array_lookup_bounds(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibheader::PISC_TR_HANDLE trans_handle, System::PByte table_name, System::PByte column_name, Ibx::Ibheader::PISC_ARRAY_DESC descriptor) = 0 ;
	virtual NativeInt __fastcall isc_array_lookup_bounds2(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibheader::PISC_TR_HANDLE trans_handle, System::PByte table_name, System::PByte column_name, Ibx::Ibheader::PISC_ARRAY_DESC_V2 descriptor) = 0 ;
	virtual NativeInt __fastcall isc_array_lookup_desc(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibheader::PISC_TR_HANDLE trans_handle, System::PByte table_name, System::PByte column_name, Ibx::Ibheader::PISC_ARRAY_DESC descriptor) = 0 ;
	virtual NativeInt __fastcall isc_array_lookup_desc2(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibheader::PISC_TR_HANDLE trans_handle, System::PByte table_name, System::PByte column_name, Ibx::Ibheader::PISC_ARRAY_DESC_V2 descriptor) = 0 ;
	virtual NativeInt __fastcall isc_array_set_desc(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte table_name, System::PByte column_name, Ibx::Ibexternals::PShort sql_dtype, Ibx::Ibexternals::PShort sql_length, Ibx::Ibexternals::PShort sql_dimensions, Ibx::Ibheader::PISC_ARRAY_DESC descriptor) = 0 ;
	virtual NativeInt __fastcall isc_array_set_desc2(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte table_name, System::PByte column_name, Ibx::Ibexternals::PShort sql_dtype, Ibx::Ibexternals::PShort sql_length, Ibx::Ibexternals::PShort sql_dimensions, Ibx::Ibheader::PISC_ARRAY_DESC_V2 descriptor) = 0 ;
	virtual NativeInt __fastcall isc_array_put_slice(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibheader::PISC_TR_HANDLE trans_handle, Ibx::Ibheader::PISC_QUAD array_id, Ibx::Ibheader::PISC_ARRAY_DESC descriptor, Ibx::Ibexternals::PVoid source_array, Ibx::Ibexternals::PISC_LONG slice_length) = 0 ;
	virtual NativeInt __fastcall isc_array_put_slice2(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibheader::PISC_TR_HANDLE trans_handle, Ibx::Ibheader::PISC_QUAD array_id, Ibx::Ibheader::PISC_ARRAY_DESC_V2 descriptor, Ibx::Ibexternals::PVoid source_array, Ibx::Ibexternals::PISC_LONG slice_length) = 0 ;
	virtual void __fastcall isc_blob_default_desc(Ibx::Ibheader::PISC_BLOB_DESC descriptor, Ibx::Ibexternals::PUChar table_name, Ibx::Ibexternals::PUChar column_name) = 0 ;
	virtual void __fastcall isc_blob_default_desc2(Ibx::Ibheader::PISC_BLOB_DESC_V2 descriptor, Ibx::Ibexternals::PUChar table_name, Ibx::Ibexternals::PUChar column_name) = 0 ;
	virtual NativeInt __fastcall isc_blob_gen_bpb(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_BLOB_DESC to_descriptor, Ibx::Ibheader::PISC_BLOB_DESC from_descriptor, System::Word bpb_buffer_length, Ibx::Ibexternals::PUChar bpb_buffer, Ibx::Ibexternals::PUShort bpb_length) = 0 ;
	virtual NativeInt __fastcall isc_blob_gen_bpb2(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_BLOB_DESC_V2 to_descriptor, Ibx::Ibheader::PISC_BLOB_DESC_V2 from_descriptor, System::Word bpb_buffer_length, Ibx::Ibexternals::PUChar bpb_buffer, Ibx::Ibexternals::PUShort bpb_length) = 0 ;
	virtual NativeInt __fastcall isc_blob_info(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_BLOB_HANDLE blob_handle, short item_list_buffer_length, System::PByte item_list_buffer, short result_buffer_length, System::PByte result_buffer) = 0 ;
	virtual NativeInt __fastcall isc_blob_lookup_desc(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibheader::PISC_TR_HANDLE trans_handle, System::PByte table_name, System::PByte column_name, Ibx::Ibheader::PISC_BLOB_DESC descriptor, Ibx::Ibexternals::PUChar global) = 0 ;
	virtual NativeInt __fastcall isc_blob_lookup_desc2(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibheader::PISC_TR_HANDLE trans_handle, System::PByte table_name, System::PByte column_name, Ibx::Ibheader::PISC_BLOB_DESC_V2 descriptor, Ibx::Ibexternals::PUChar global) = 0 ;
	virtual NativeInt __fastcall isc_blob_set_desc(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte table_name, System::PByte column_name, short subtype, short charset, short segment_size, Ibx::Ibheader::PISC_BLOB_DESC descriptor) = 0 ;
	virtual NativeInt __fastcall isc_blob_set_desc2(Ibx::Ibexternals::PISC_STATUS status_vector, System::PByte table_name, System::PByte column_name, short subtype, short charset, short segment_size, Ibx::Ibheader::PISC_BLOB_DESC_V2 descriptor) = 0 ;
	virtual NativeInt __fastcall isc_cancel_blob(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_BLOB_HANDLE blob_handle) = 0 ;
	virtual NativeInt __fastcall isc_cancel_events(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibexternals::PISC_LONG event_id) = 0 ;
	virtual NativeInt __fastcall isc_close_blob(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_BLOB_HANDLE blob_handle) = 0 ;
	virtual NativeInt __fastcall isc_commit_retaining(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_TR_HANDLE tran_handle) = 0 ;
	virtual NativeInt __fastcall isc_commit_transaction(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_TR_HANDLE tran_handle) = 0 ;
	virtual NativeInt __fastcall isc_create_blob2(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibheader::PISC_TR_HANDLE tran_handle, Ibx::Ibheader::PISC_BLOB_HANDLE blob_handle, Ibx::Ibheader::PISC_QUAD blob_id, short bpb_length, System::PByte bpb_address) = 0 ;
	virtual NativeInt __fastcall isc_create_database(Ibx::Ibexternals::PISC_STATUS status_vector, short db_name_length, System::PByte db_name, Ibx::Ibheader::PISC_DB_HANDLE db_handle, short dpb_length, System::PByte dpb, short isc_arg7) = 0 ;
	virtual NativeInt __fastcall isc_database_info(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, short item_list_buffer_length, System::PByte item_list_buffer, short result_buffer_length, System::PByte result_buffer) = 0 ;
	virtual void __fastcall isc_decode_date(Ibx::Ibheader::PISC_QUAD ib_date, Ibx::Ibexternals::PCTimeStructure tm_date) = 0 ;
	virtual void __fastcall isc_decode_sql_date(Ibx::Ibheader::PISC_DATE ib_date, Ibx::Ibexternals::PCTimeStructure tm_date) = 0 ;
	virtual void __fastcall isc_decode_sql_time(Ibx::Ibheader::PISC_TIME ib_time, Ibx::Ibexternals::PCTimeStructure tm_date) = 0 ;
	virtual void __fastcall isc_decode_timestamp(Ibx::Ibheader::PISC_TIMESTAMP ib_timestamp, Ibx::Ibexternals::PCTimeStructure tm_date) = 0 ;
	virtual NativeInt __fastcall isc_detach_database(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle) = 0 ;
	virtual NativeInt __fastcall isc_drop_database(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle) = 0 ;
	virtual NativeInt __fastcall isc_dsql_alloc_statement2(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibheader::PISC_STMT_HANDLE stmt_handle) = 0 ;
	virtual NativeInt __fastcall isc_dsql_describe(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_STMT_HANDLE stmt_handle, System::Word dialect, Ibx::Ibheader::PXSQLDA xsqlda) = 0 ;
	virtual NativeInt __fastcall isc_dsql_describe_bind(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_STMT_HANDLE stmt_handle, System::Word dialect, Ibx::Ibheader::PXSQLDA xsqlda) = 0 ;
	virtual NativeInt __fastcall isc_dsql_exec_immed2(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibheader::PISC_TR_HANDLE tran_handle, System::Word length, System::PByte statement, System::Word dialect, Ibx::Ibheader::PXSQLDA in_xsqlda, Ibx::Ibheader::PXSQLDA out_xsqlda) = 0 ;
	virtual NativeInt __fastcall isc_dsql_execute(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_TR_HANDLE tran_handle, Ibx::Ibheader::PISC_STMT_HANDLE stmt_handle, System::Word dialect, Ibx::Ibheader::PXSQLDA xsqlda) = 0 ;
	virtual NativeInt __fastcall isc_dsql_execute2(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_TR_HANDLE tran_handle, Ibx::Ibheader::PISC_STMT_HANDLE stmt_handle, System::Word dialect, Ibx::Ibheader::PXSQLDA in_xsqlda, Ibx::Ibheader::PXSQLDA out_xsqlda) = 0 ;
	virtual NativeInt __fastcall isc_dsql_execute_immediate(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibheader::PISC_TR_HANDLE tran_handle, System::Word length, System::PByte statement, System::Word dialect, Ibx::Ibheader::PXSQLDA xsqlda) = 0 ;
	virtual NativeInt __fastcall isc_dsql_fetch(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_STMT_HANDLE stmt_handle, System::Word dialect, Ibx::Ibheader::PXSQLDA xsqlda) = 0 ;
	virtual NativeInt __fastcall isc_dsql_free_statement(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_STMT_HANDLE stmt_handle, System::Word options) = 0 ;
	virtual NativeInt __fastcall isc_dsql_prepare(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_TR_HANDLE tran_handle, Ibx::Ibheader::PISC_STMT_HANDLE stmt_handle, System::Word length, System::PByte statement, System::Word dialect, Ibx::Ibheader::PXSQLDA xsqlda) = 0 ;
	virtual NativeInt __fastcall isc_dsql_set_cursor_name(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_STMT_HANDLE stmt_handle, System::PByte cursor_name, System::Word _type) = 0 ;
	virtual NativeInt __fastcall isc_dsql_sql_info(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_STMT_HANDLE stmt_handle, short item_length, System::PByte items, short buffer_length, System::PByte buffer) = 0 ;
	virtual void __fastcall isc_encode_date(Ibx::Ibexternals::PCTimeStructure tm_date, Ibx::Ibheader::PISC_QUAD ib_date) = 0 ;
	virtual void __fastcall isc_encode_sql_date(Ibx::Ibexternals::PCTimeStructure tm_date, Ibx::Ibheader::PISC_DATE ib_date) = 0 ;
	virtual void __fastcall isc_encode_sql_time(Ibx::Ibexternals::PCTimeStructure tm_date, Ibx::Ibheader::PISC_TIME ib_time) = 0 ;
	virtual void __fastcall isc_encode_timestamp(Ibx::Ibexternals::PCTimeStructure tm_date, Ibx::Ibheader::PISC_TIMESTAMP ib_timestamp) = 0 ;
	virtual int __fastcall isc_event_block(System::PByte &event_buffer, System::PByte &result_buffer, System::Word id_count, System::PByte *event_list, const int event_list_High) = 0 ;
	virtual void __fastcall isc_event_counts(Ibx::Ibexternals::PUISC_LONG status_vector, short buffer_length, System::PByte event_buffer, System::PByte result_buffer) = 0 ;
	virtual int __fastcall isc_free(System::PByte isc_arg1) = 0 ;
	virtual NativeInt __fastcall isc_get_segment(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_BLOB_HANDLE blob_handle, Ibx::Ibexternals::PUShort actual_seg_length, System::Word seg_buffer_length, System::PByte seg_buffer) = 0 ;
	virtual NativeInt __fastcall isc_interprete(System::PByte buffer, Ibx::Ibexternals::PPISC_STATUS status_vector) = 0 ;
	virtual NativeInt __fastcall isc_open_blob2(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibheader::PISC_TR_HANDLE tran_handle, Ibx::Ibheader::PISC_BLOB_HANDLE blob_handle, Ibx::Ibheader::PISC_QUAD blob_id, short bpb_length, System::PByte bpb_buffer) = 0 ;
	virtual NativeInt __fastcall isc_prepare_transaction2(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_TR_HANDLE tran_handle, short msg_length, System::PByte msg) = 0 ;
	virtual NativeInt __fastcall isc_put_segment(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_BLOB_HANDLE blob_handle, System::Word seg_buffer_len, System::PByte seg_buffer) = 0 ;
	virtual NativeInt __fastcall isc_que_events(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibexternals::PISC_LONG event_id, short length, System::PByte event_buffer, Ibx::Ibheader::TISC_CALLBACK event_function, Ibx::Ibexternals::PVoid event_function_arg) = 0 ;
	virtual NativeInt __fastcall isc_release_savepoint(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_TR_HANDLE tran_handle, System::PByte tran_name) = 0 ;
	virtual NativeInt __fastcall isc_rollback_retaining(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_TR_HANDLE tran_handle) = 0 ;
	virtual NativeInt __fastcall isc_rollback_savepoint(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_TR_HANDLE tran_handle, System::PByte tran_name, System::Word Option) = 0 ;
	virtual NativeInt __fastcall isc_rollback_transaction(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_TR_HANDLE tran_handle) = 0 ;
	virtual NativeInt __fastcall isc_start_multiple(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_TR_HANDLE tran_handle, short db_handle_count, Ibx::Ibheader::PISC_TEB teb_vector_address) = 0 ;
	virtual NativeInt __fastcall isc_start_transaction(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_TR_HANDLE tran_handle, short db_handle_count, Ibx::Ibheader::PISC_DB_HANDLE db_handle, System::Word tpb_length, System::PByte tpb_address) = 0 ;
	virtual NativeInt __fastcall isc_start_savepoint(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_TR_HANDLE tran_handle, System::PByte tran_name) = 0 ;
	virtual int __fastcall isc_sqlcode(Ibx::Ibexternals::PISC_STATUS status_vector) = 0 ;
	virtual void __fastcall isc_sql_interprete(short sqlcode, System::PByte buffer, short buffer_length) = 0 ;
	virtual int __fastcall isc_vax_integer(System::PByte buffer, short length) = 0 ;
	virtual __int64 __fastcall isc_portable_integer(System::PByte buffer, short length) = 0 ;
	virtual NativeInt __fastcall isc_dsql_batch_execute_immed(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_DB_HANDLE db_handle, Ibx::Ibheader::PISC_TR_HANDLE tran_handle, System::Word Dialect, unsigned no_of_sql, Ibx::Ibexternals::PPByte statement, Ibx::Ibexternals::PULong rows_affected) = 0 ;
	virtual NativeInt __fastcall isc_dsql_batch_execute(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_TR_HANDLE tran_handle, Ibx::Ibheader::PISC_STMT_HANDLE stmt_handle, System::Word Dialect, Ibx::Ibheader::PXSQLDA insqlda, System::Word no_of_rows, Ibx::Ibheader::PXSQLVAR batch_vars, Ibx::Ibexternals::PULong rows_affected) = 0 ;
	virtual NativeInt __fastcall isc_add_user(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PUserSecData user_sec_data) = 0 ;
	virtual NativeInt __fastcall isc_delete_user(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PUserSecData user_sec_data) = 0 ;
	virtual NativeInt __fastcall isc_modify_user(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PUserSecData user_sec_data) = 0 ;
	virtual NativeInt __fastcall isc_prepare_transaction(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_TR_HANDLE tran_handle) = 0 ;
	virtual int __fastcall BLOB_put(System::Byte isc_arg1, Ibx::Ibheader::PBSTREAM isc_arg2) = 0 ;
	virtual int __fastcall BLOB_get(Ibx::Ibheader::PBSTREAM isc_arg1) = 0 ;
	virtual NativeInt __fastcall isc_service_attach(Ibx::Ibexternals::PISC_STATUS status_vector, System::Word isc_arg2, System::PByte isc_arg3, Ibx::Ibheader::PISC_SVC_HANDLE service_handle, System::Word isc_arg5, System::PByte isc_arg6) = 0 ;
	virtual NativeInt __fastcall isc_service_detach(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_SVC_HANDLE service_handle) = 0 ;
	virtual NativeInt __fastcall isc_service_query(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_SVC_HANDLE service_handle, Ibx::Ibheader::PISC_SVC_HANDLE recv_handle, System::Word isc_arg4, System::PByte isc_arg5, System::Word isc_arg6, System::PByte isc_arg7, System::Word isc_arg8, System::PByte isc_arg9) = 0 ;
	virtual NativeInt __fastcall isc_service_start(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_SVC_HANDLE service_handle, Ibx::Ibheader::PISC_SVC_HANDLE recv_handle, System::Word isc_arg4, System::PByte isc_arg5) = 0 ;
	virtual void __fastcall isc_get_client_version(System::PByte buffer) = 0 ;
	virtual int __fastcall isc_get_client_major_version() = 0 ;
	virtual int __fastcall isc_get_client_minor_version() = 0 ;
	virtual NativeInt __fastcall isc_transaction_info(Ibx::Ibexternals::PISC_STATUS status_vector, Ibx::Ibheader::PISC_TR_HANDLE tran_handle, short item_list_buffer_length, System::PByte item_list_buffer, short result_buffer_length, System::PByte result_buffer) = 0 ;
};

typedef System::Generics::Collections::TDictionary__2<System::UnicodeString,_di_IGDSLibrary>* TIBInterface;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::Generics::Collections::TDictionary__2<System::UnicodeString,_di_IGDSLibrary>* IBClientInterface;
extern DELPHI_PACKAGE Ibx::Ibinstallheader::Tisc_install_clear_options isc_install_clear_options;
extern DELPHI_PACKAGE Ibx::Ibinstallheader::Tisc_install_execute isc_install_execute;
extern DELPHI_PACKAGE Ibx::Ibinstallheader::Tisc_install_get_info isc_install_get_info;
extern DELPHI_PACKAGE Ibx::Ibinstallheader::Tisc_install_get_message isc_install_get_message;
extern DELPHI_PACKAGE Ibx::Ibinstallheader::Tisc_install_load_external_text isc_install_load_external_text;
extern DELPHI_PACKAGE Ibx::Ibinstallheader::Tisc_install_precheck isc_install_precheck;
extern DELPHI_PACKAGE Ibx::Ibinstallheader::Tisc_install_set_option isc_install_set_option;
extern DELPHI_PACKAGE Ibx::Ibinstallheader::Tisc_uninstall_execute isc_uninstall_execute;
extern DELPHI_PACKAGE Ibx::Ibinstallheader::Tisc_uninstall_precheck isc_uninstall_precheck;
extern DELPHI_PACKAGE Ibx::Ibinstallheader::Tisc_install_unset_option isc_install_unset_option;
extern DELPHI_PACKAGE void __fastcall LoadIBInstallLibrary(void);
extern DELPHI_PACKAGE void __fastcall FreeIBInstallLibrary(void);
extern DELPHI_PACKAGE void __fastcall CheckIBInstallLoaded(void);
extern DELPHI_PACKAGE _di_IGDSLibrary __fastcall GetGDSLibrary(const System::UnicodeString ALibrary);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ValidateServerType(System::UnicodeString ALibrary);
extern DELPHI_PACKAGE void __fastcall GetAvailableLibraries(System::Classes::TStrings* LibList);
extern DELPHI_PACKAGE void __fastcall AddIBInterface(System::UnicodeString LibName, _di_IGDSLibrary IBInterface);
}	/* namespace Ibintf */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBINTF)
using namespace Ibx::Ibintf;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbintfHPP
