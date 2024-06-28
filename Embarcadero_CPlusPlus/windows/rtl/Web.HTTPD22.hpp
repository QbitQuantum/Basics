// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.HTTPD22.pas' rev: 34.00 (Windows)

#ifndef Web_Httpd22HPP
#define Web_Httpd22HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.WinSock.hpp>

//-- user supplied -----------------------------------------------------------
#if defined(__WIN32__) && defined(USE_APACHE_LIBS)
#pragma link "libhttpd.lib"
#pragma link "libapr.lib"
#endif
struct ap_method_list_t;
struct server_rec;
struct command_rec;
struct ap_conf_vector_t;
struct process_rec;
struct conn_rec;
struct apr_table_t;
struct apr_file_t;
struct ap_filter_t;
struct request_rec;
struct apr_socket_t;
struct apr_hash_t;

namespace Web
{
namespace Httpd22
{
//-- forward type declarations -----------------------------------------------
struct ap_directive_t;
struct DECLSPEC_DRECORD apr_pool_t
{
};


struct apr_array_header_t;
struct apr_table_entry_t;
struct command_struct;
struct ap_configfile_t;
struct cmd_parms_struct;
struct module;
struct apr_sockaddr_t;
struct DECLSPEC_DRECORD apr_bucket_alloc_t
{
};


struct htaccess_result;
struct ap_filter_func;
struct ap_filter_rec_t;
struct server_addr_rec;
//-- type declarations -------------------------------------------------------
typedef int uid_t;

typedef int gid_t;

typedef System::Word apr_uint16_t;

typedef unsigned apr_uint32_t;

typedef __int64 apr_int64_t;

typedef __int64 apr_interval_time_t;

typedef __int64 apr_uint64_t;

typedef System::Word apr_port_t;

typedef int apr_status_t;

typedef int apr_socklen_t;

typedef __int64 apr_time_t;

typedef ap_directive_t *Pap_directive_t;

struct DECLSPEC_DRECORD ap_directive_t
{
public:
	char *directive;
	char *args;
	ap_directive_t *next;
	ap_directive_t *first_child;
	ap_directive_t *parent;
	void *data;
	char *filename;
	int line_num;
};


typedef apr_pool_t *Papr_pool_t;

struct DECLSPEC_DRECORD apr_array_header_t
{
public:
	apr_pool_t *pool;
	int elt_size;
	int nelts;
	int nalloc;
	char *elts;
};


typedef apr_array_header_t *Papr_array_header_t;

struct DECLSPEC_DRECORD apr_table_entry_t
{
public:
	char *key;
	char *val;
	unsigned key_checksum;
};


enum DECLSPEC_DENUM cmd_how : unsigned char { RAW_ARGS, TAKE1, TAKE2, ITERATE, ITERATE2, FLAG, NO_ARGS, TAKE12, TAKE3, TAKE23, TAKE123, TAKE13 };

typedef char * __cdecl (*cmd_func)();

struct DECLSPEC_DRECORD command_struct
{
public:
	char *name;
	cmd_func func;
	void *cmd_data;
	int req_override;
	cmd_how args_how;
	char *errmsg;
};


typedef command_struct *Pcommand_struct;

typedef command_struct command_rec;

typedef ap_method_list_t *Pap_method_list_t;

typedef server_rec *Pserver_rec;

typedef command_struct *Pcommand_rec;

typedef ap_conf_vector_t *Pap_conf_vector_t;

typedef process_rec *Pprocess_rec;

typedef conn_rec *Pconn_rec;

typedef apr_table_t *Papr_table_t;

typedef apr_file_t *Papr_file_t;

typedef ap_filter_t *Pap_filter_t;

typedef request_rec *Prequest_rec;

typedef apr_socket_t *Papr_socket_t;

typedef apr_hash_t *Papr_hash_t;

struct DECLSPEC_DRECORD ap_configfile_t
{
public:
	int __fastcall (*getch)(void * param);
	void * __fastcall (*getstr)(void * buf, int bufsiz, void * param);
	int __fastcall (*close)(void * param);
	void *param;
	char *name;
	unsigned line_number;
};


typedef ap_configfile_t *Pap_configfile_t;

struct DECLSPEC_DRECORD cmd_parms_struct
{
public:
	void *info;
	int override;
	__int64 limited;
	apr_array_header_t *limited_xmethods;
	ap_method_list_t *xlimited;
	ap_configfile_t *config_file;
	ap_directive_t *directive;
	apr_pool_t *pool;
	apr_pool_t *temp_pool;
	server_rec *server;
	char *path;
	command_struct *cmd;
	ap_conf_vector_t *context;
	ap_directive_t *err_directive;
};


typedef cmd_parms_struct cmd_parms;

typedef cmd_parms_struct *Pcmd_parms;

typedef module *PModule;

struct DECLSPEC_DRECORD module
{
public:
	int version;
	int minor_version;
	int module_index;
	char *name;
	void *dynamic_load_handle;
	module *next;
	unsigned magic;
	void __cdecl (*rewrite_args)(Pprocess_rec process);
	void * __cdecl (*create_dir_config)(Papr_pool_t p, char * dir);
	void * __cdecl (*merge_dir_config)(Papr_pool_t p, void * base_conf, void * new_conf);
	void * __cdecl (*create_server_config)(Papr_pool_t p, Pserver_rec s);
	void * __cdecl (*merge_server_config)(Papr_pool_t p, void * base_conf, void * new_conf);
	command_struct *cmds;
	void __cdecl (*register_hooks)(Papr_pool_t p);
};


typedef apr_sockaddr_t *Papr_sockaddr_t;

struct DECLSPEC_DRECORD apr_sockaddr_t
{
public:
	apr_pool_t *pool;
	char *hostname;
	char *servname;
	System::Word port;
	int family;
	sockaddr_in sin;
	int salen;
	int ipaddr_len;
	int addr_str_len;
	void *ipaddr_ptr;
	apr_sockaddr_t *next;
};


typedef apr_bucket_alloc_t *Papr_bucket_alloc_t;

enum DECLSPEC_DENUM ap_conn_keepalive_e : unsigned char { AP_CONN_UNKNOWN, AP_CONN_CLOSE, AP_CONN_KEEPALIVE };

typedef htaccess_result *Phtaccess_result;

struct DECLSPEC_DRECORD htaccess_result
{
public:
	char *dir;
	int override;
	ap_conf_vector_t *htaccess;
	htaccess_result *next;
};


typedef void * *Papr_bucket_brigade;

enum DECLSPEC_DENUM apr_read_type_e : unsigned char { APR_BLOCK_READ, APR_NONBLOCK_READ };

enum DECLSPEC_DENUM ap_input_mode_t : unsigned char { AP_MODE_READBYTES, AP_MODE_GETLINE, AP_MODE_EATCRLF, AP_MODE_SPECULATIVE, AP_MODE_EXHAUSTIVE, AP_MODE_INIT };

typedef int __cdecl (*ap_out_filter_func)(Pap_filter_t f, Papr_bucket_brigade b);

typedef int __cdecl (*ap_in_filter_func)(Pap_filter_t f, Papr_bucket_brigade b, ap_input_mode_t mode, apr_read_type_e block, __int64 readbytes);

typedef ap_filter_func *Pap_filter_func;

struct DECLSPEC_DRECORD ap_filter_func
{
	
public:
	union
	{
		struct 
		{
			ap_in_filter_func in_func;
		};
		struct 
		{
			ap_out_filter_func out_func;
		};
		
	};
};


enum DECLSPEC_DENUM ap_filter_type : unsigned char { AP_FTYPE_RESOURCE = 10, AP_FTYPE_CONTENT_SET = 20, AP_FTYPE_PROTOCOL = 30, AP_FTYPE_TRANSCODE = 40, AP_FTYPE_CONNECTION = 50, AP_FTYPE_NETWORK = 60 };

typedef ap_filter_rec_t *Pap_filter_rec_t;

struct DECLSPEC_DRECORD ap_filter_rec_t
{
public:
	char *name;
	ap_filter_func filter_func;
	ap_filter_type ftype;
	ap_filter_rec_t *next;
};


typedef server_addr_rec *Pserver_addr_rec;

struct DECLSPEC_DRECORD server_addr_rec
{
public:
	server_addr_rec *next;
	apr_sockaddr_t *host_addr;
	System::Word host_port;
	char *virthost;
};


typedef int __cdecl (*TCompFunc)(void * P, char * PC, char * PC2);

//-- var, const, procedure ---------------------------------------------------
#define LibHTTPD L"libhttpd.dll"
#define LibAPR L"libapr-1.dll"
#ifndef _WIN64
extern DELPHI_PACKAGE int __stdcall ap_run_quick_handler(Prequest_rec r, int lookup_uri);
#else /* _WIN64 */
extern "C" int __stdcall ap_run_quick_handler(Prequest_rec r, int lookup_uri);
#endif /* _WIN64 */
}	/* namespace Httpd22 */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_HTTPD22)
using namespace Web::Httpd22;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_Httpd22HPP
