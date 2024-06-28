// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBInstallHeader.pas' rev: 34.00 (iOS)

#ifndef Ibx_IbinstallheaderHPP
#define Ibx_IbinstallheaderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibinstallheader
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef int OPTIONS_HANDLE;

typedef int *POPTIONS_HANDLE;

typedef long MSG_NO;

typedef long OPT;

typedef System::PByte TEXT;

typedef int __cdecl (*FP_ERROR)(long IscCode, void * UserContext, const System::PByte ActionDescription);

typedef int __cdecl (*FP_STATUS)(int Status, void * UserContext, const System::PByte ActionDescription);

typedef long __cdecl (*Tisc_install_clear_options)(POPTIONS_HANDLE hOption);

typedef long __cdecl (*Tisc_install_execute)(int hOption, System::PByte src_dir, System::PByte dest_dir, FP_STATUS status_func, void * status_data, FP_ERROR error_func, void * error_data, System::PByte uninstal_file_name);

typedef long __cdecl (*Tisc_install_get_info)(int info_type, long option, void * info_buffer, unsigned buf_len);

typedef long __cdecl (*Tisc_install_get_message)(int hOption, long message_no, void * message_txt, unsigned message_len);

typedef long __cdecl (*Tisc_install_load_external_text)(System::PByte msg_file_name);

typedef long __cdecl (*Tisc_install_precheck)(int hOption, System::PByte src_dir, System::PByte dest_dir);

typedef long __cdecl (*Tisc_install_set_option)(POPTIONS_HANDLE hOption, long option);

typedef long __cdecl (*Tisc_uninstall_execute)(System::PByte uninstall_file_name, FP_STATUS status_func, void * status_data, FP_ERROR error_func, void * error_data);

typedef long __cdecl (*Tisc_uninstall_precheck)(System::PByte uninstall_file_name);

typedef long __cdecl (*Tisc_install_unset_option)(POPTIONS_HANDLE hOption, long option);

//-- var, const, procedure ---------------------------------------------------
#define IB_INSTALL_DLL u"ibinstall.so"
static constexpr System::Int8 isc_install_fp_retry = System::Int8(-1);
static constexpr System::Int8 isc_install_fp_continue = System::Int8(0x0);
static constexpr System::Int8 isc_install_fp_abort = System::Int8(0x1);
static constexpr System::Int8 isc_install_info_destination = System::Int8(0x1);
static constexpr System::Int8 isc_install_info_opspace = System::Int8(0x2);
static constexpr System::Int8 isc_install_info_opname = System::Int8(0x3);
static constexpr System::Int8 isc_install_info_opdescription = System::Int8(0x4);
static constexpr System::Word ISC_INSTALL_MAX_MESSAGE_LEN = System::Word(0x12c);
static constexpr System::Byte ISC_INSTALL_MAX_MESSAGES = System::Byte(0xc8);
static constexpr System::Word ISC_INSTALL_MAX_PATH = System::Word(0x100);
static constexpr System::Word INTERBASE = System::Word(0x3e8);
static constexpr System::Word IB_SERVER = System::Word(0x3e9);
static constexpr System::Word IB_CLIENT = System::Word(0x3ea);
static constexpr System::Word IB_CMD_TOOLS = System::Word(0x3eb);
static constexpr System::Word IB_CMD_TOOLS_DB_MGMT = System::Word(0x3ec);
static constexpr System::Word IB_CMD_TOOLS_USR_MGMT = System::Word(0x3ed);
static constexpr System::Word IB_CMD_TOOLS_DB_QUERY = System::Word(0x3ee);
static constexpr System::Word IB_GUI_TOOLS = System::Word(0x3ef);
static constexpr System::Word IB_DOC = System::Word(0x3f3);
static constexpr System::Word IB_EXAMPLES = System::Word(0x3f4);
static constexpr System::Word IB_EXAMPLE_API = System::Word(0x3f5);
static constexpr System::Word IB_EXAMPLE_DB = System::Word(0x3f6);
static constexpr System::Word IB_DEV = System::Word(0x3f7);
static constexpr System::Word IB_CONNECTIVITY_SERVER = System::Word(0x44c);
static constexpr System::Word IB_CONNECTIVITY = System::Word(0x44d);
static constexpr System::Word IB_ODBC_CLIENT = System::Word(0x44e);
static constexpr System::Word IB_JDBC_CLIENT = System::Word(0x44f);
static constexpr System::Word IB_OLEDB_CLIENT = System::Word(0x450);
static constexpr System::Int8 isc_install_optlist_empty = System::Int8(-1);
static constexpr System::Int8 isc_install_actlist_empty = System::Int8(-2);
static constexpr System::Int8 isc_install_fp_copy_delayed = System::Int8(-3);
static constexpr System::Int8 isc_install_fp_delete_delayed = System::Int8(-4);
static constexpr System::Int8 isc_install_option_not_found = System::Int8(-5);
static constexpr System::Int8 isc_install_msg_version = System::Int8(-6);
static constexpr System::Int8 isc_install_cant_load_msg = System::Int8(-7);
static constexpr System::Int8 isc_install_invalid_msg = System::Int8(-8);
static constexpr System::Int8 isc_install_invalid_tbl = System::Int8(-9);
static constexpr System::Int8 isc_install_cant_create_msg = System::Int8(-10);
static constexpr System::Int8 isc_install_handle_not_allocated = System::Int8(-11);
static constexpr System::Int8 isc_install_odbc_comp_notfound = System::Int8(-12);
static constexpr System::Int8 isc_install_cant_delete = System::Int8(-13);
static constexpr System::Int8 isc_install_cant_rmdir = System::Int8(-14);
static constexpr System::Int8 isc_install_key_nonempty = System::Int8(-15);
static constexpr System::Int8 isc_install_success = System::Int8(0x0);
static constexpr System::Int8 isc_install_file_error = System::Int8(0x0);
static constexpr System::Int8 isc_install_path_not_valid = System::Int8(0x1);
static constexpr System::Int8 isc_install_path_not_exists = System::Int8(0x2);
static constexpr System::Int8 isc_install_cant_write = System::Int8(0x3);
static constexpr System::Int8 isc_install_type_unknown = System::Int8(0x4);
static constexpr System::Int8 isc_install_cant_move_file = System::Int8(0x5);
static constexpr System::Int8 isc_install_device_not_valid = System::Int8(0x6);
static constexpr System::Int8 isc_install_data_truncated = System::Int8(0x7);
static constexpr System::Int8 isc_install_cant_get_temp = System::Int8(0x8);
static constexpr System::Int8 isc_install_no_file = System::Int8(0x9);
static constexpr System::Int8 isc_install_cant_load_lib = System::Int8(0xa);
static constexpr System::Int8 isc_install_cant_lookup_lib = System::Int8(0xb);
static constexpr System::Int8 isc_install_file_exists = System::Int8(0xc);
static constexpr System::Int8 isc_install_cant_open_log = System::Int8(0xd);
static constexpr System::Int8 isc_install_write_error = System::Int8(0xe);
static constexpr System::Int8 isc_install_read_error = System::Int8(0xf);
static constexpr System::Int8 isc_install_invalid_log = System::Int8(0x10);
static constexpr System::Int8 isc_install_cant_read = System::Int8(0x11);
static constexpr System::Int8 isc_install_no_diskspace = System::Int8(0x12);
static constexpr System::Int8 isc_install_cant_create_dir = System::Int8(0x13);
static constexpr System::Int8 isc_install_msg_syntax = System::Int8(0x14);
static constexpr System::Int8 isc_install_fp_delete_error = System::Int8(0x15);
static constexpr System::Int8 isc_install_fp_rename_error = System::Int8(0x16);
static constexpr System::Int8 isc_install_fp_copy_error = System::Int8(0x17);
static constexpr System::Int8 isc_install_precheck_error = System::Int8(0x18);
static constexpr System::Int8 isc_install_system_not_supported = System::Int8(0x18);
static constexpr System::Int8 isc_install_server_running = System::Int8(0x19);
static constexpr System::Int8 isc_install_classic_found = System::Int8(0x1a);
static constexpr System::Int8 isc_install_no_privileges = System::Int8(0x1b);
static constexpr System::Int8 isc_install_cant_get_free_space = System::Int8(0x1c);
static constexpr System::Int8 isc_install_guardian_running = System::Int8(0x1d);
static constexpr System::Int8 isc_install_invalid_option = System::Int8(0x1e);
static constexpr System::Int8 isc_install_invalid_handle = System::Int8(0x1f);
static constexpr System::Int8 isc_install_message_not_found = System::Int8(0x20);
static constexpr System::Int8 isc_install_ip_error = System::Int8(0x21);
static constexpr System::Int8 isc_install_no_stack = System::Int8(0x21);
static constexpr System::Int8 isc_install_cant_add_service = System::Int8(0x22);
static constexpr System::Int8 isc_install_invalid_port = System::Int8(0x23);
static constexpr System::Int8 isc_install_invalid_service = System::Int8(0x24);
static constexpr System::Int8 isc_install_no_proto = System::Int8(0x25);
static constexpr System::Int8 isc_install_no_services_entry = System::Int8(0x26);
static constexpr System::Int8 isc_install_sock_error = System::Int8(0x27);
static constexpr System::Int8 isc_install_conversion_error = System::Int8(0x28);
static constexpr System::Int8 isc_install_op_error = System::Int8(0x29);
static constexpr System::Int8 isc_install_cant_copy = System::Int8(0x29);
static constexpr System::Int8 isc_install_no_mem = System::Int8(0x2a);
static constexpr System::Int8 isc_install_queue_failed = System::Int8(0x2b);
static constexpr System::Int8 isc_install_invalid_param = System::Int8(0x2c);
static constexpr System::Int8 isc_install_fp_error_exception = System::Int8(0x2d);
static constexpr System::Int8 isc_install_fp_status_exception = System::Int8(0x2e);
static constexpr System::Int8 isc_install_user_aborted = System::Int8(0x2f);
static constexpr System::Int8 isc_install_reg_error = System::Int8(0x30);
static constexpr System::Int8 isc_install_key_exists = System::Int8(0x30);
static constexpr System::Int8 isc_install_cant_create_key = System::Int8(0x31);
static constexpr System::Int8 isc_install_cant_set_value = System::Int8(0x32);
static constexpr System::Int8 isc_install_cant_open_key = System::Int8(0x33);
static constexpr System::Int8 isc_install_cant_delete_key = System::Int8(0x34);
static constexpr System::Int8 isc_install_cant_query_key = System::Int8(0x35);
static constexpr System::Int8 isc_install_cant_delete_value = System::Int8(0x36);
static constexpr System::Int8 isc_install_serv_error = System::Int8(0x37);
static constexpr System::Int8 isc_install_service_existed = System::Int8(0x37);
static constexpr System::Int8 isc_install_cant_create_service = System::Int8(0x38);
static constexpr System::Int8 isc_install_cant_open_service = System::Int8(0x39);
static constexpr System::Int8 isc_install_cant_query_service = System::Int8(0x3a);
static constexpr System::Int8 isc_install_service_running = System::Int8(0x3b);
static constexpr System::Int8 isc_install_cant_delete_service = System::Int8(0x3c);
static constexpr System::Int8 isc_install_cant_open_manager = System::Int8(0x3d);
static constexpr System::Int8 isc_install_system_error = System::Int8(0x3e);
static constexpr System::Int8 isc_install_com_regfail = System::Int8(0x3f);
static constexpr System::Int8 isc_install_dcom_required = System::Int8(0x40);
static constexpr System::Int8 isc_install_odbc_error = System::Int8(0x41);
static constexpr System::Int8 isc_install_odbc_general = System::Int8(0x41);
static constexpr System::Int8 isc_install_core_version = System::Int8(0x42);
static constexpr System::Int8 isc_install_drv_version = System::Int8(0x43);
static constexpr System::Int8 isc_install_tran_version = System::Int8(0x44);
}	/* namespace Ibinstallheader */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBINSTALLHEADER)
using namespace Ibx::Ibinstallheader;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbinstallheaderHPP
