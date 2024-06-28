// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.MySQLCli.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_MysqlcliHPP
#define Firedac_Phys_MysqlcliHPP

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
namespace Mysqlcli
{
//-- forward type declarations -----------------------------------------------
struct NET0800;
struct NET0510;
struct NET0506;
struct NET0500;
struct NET0410;
struct NET0400;
struct NET0323;
struct NET0320;
struct USED_MEM;
struct MEM_ROOT0600;
struct MEM_ROOT0570;
struct MEM_ROOT0410;
struct MEM_ROOT0323;
struct MEM_ROOT0320;
struct MYSQL_FIELD0510;
struct MYSQL_FIELD0410;
struct MYSQL_FIELD0401;
struct MYSQL_FIELD0400;
struct MYSQL_FIELD0320;
struct MYSQL_ROWS0410;
struct MYSQL_ROWS0320;
struct MYSQL_DATA0800;
struct MYSQL_DATA0600;
struct MYSQL_DATA0570;
struct MYSQL_DATA0510;
struct MYSQL_DATA0506;
struct MYSQL_DATA0410;
struct MYSQL_DATA0323;
struct MYSQL_DATA0320;
struct MYSQL_OPTIONS0800;
struct MYSQL_OPTIONS0510;
struct MYSQL_OPTIONS0506;
struct MYSQL_OPTIONS0410;
struct MYSQL_OPTIONS0400;
struct MYSQL_OPTIONS0320;
struct MYSQL_METHODS0510;
struct MYSQL_METHODS0506;
struct MYSQL_METHODS0410;
struct MYSQL_LIST;
struct MY_CHARSET_INFO;
struct MYSQL0800;
struct MYSQL0600;
struct MYSQL0570;
struct MYSQL0510;
struct MYSQL0506;
struct MYSQL0500;
struct MYSQL0410;
struct MYSQL0400;
struct MYSQL0323;
struct MYSQL0320;
struct MYSQL_RES0800;
struct MYSQL_RES0600;
struct MYSQL_RES0570;
struct MYSQL_RES0510;
struct MYSQL_RES0410;
struct MYSQL_RES0323;
struct MYSQL_RES0320;
struct MYSQL_TIME0800;
struct MYSQL_TIME0506;
struct MYSQL_TIME0410;
struct MYSQL_BIND0510;
struct MYSQL_BIND0506;
struct MYSQL_BIND0411;
struct MYSQL_BIND0410;
struct MYSQL_STMT0600;
struct MYSQL_STMT0570;
struct MYSQL_STMT0510;
struct MYSQL_STMT0506;
struct MYSQL_STMT0411;
struct MYSQL_STMT0410;
//-- type declarations -------------------------------------------------------
typedef int my_enum;

typedef System::Byte my_bool;

typedef System::Byte *Pmy_bool;

typedef int my_socket;

typedef char * GPtr;

typedef System::PByte *PPByte;

typedef char * my_pchar;

typedef char * *my_ppchar;

#ifndef __x86_64__
typedef unsigned my_ulong;
#else /* __x86_64__ */
typedef unsigned long my_ulong;
#endif /* __x86_64__ */

#ifndef __x86_64__
typedef int my_long;
#else /* __x86_64__ */
typedef long my_long;
#endif /* __x86_64__ */

typedef NativeUInt my_size_t;

#ifndef __x86_64__
typedef unsigned *Pmy_ulong;
#else /* __x86_64__ */
typedef unsigned long *Pmy_ulong;
#endif /* __x86_64__ */

#ifndef __x86_64__
typedef int *Pmy_long;
#else /* __x86_64__ */
typedef long *Pmy_long;
#endif /* __x86_64__ */

typedef NativeUInt *Pmy_size_t;

typedef void * PNET;

typedef void * PMEM_ROOT;

typedef void * PMYSQL_FIELD;

typedef void * PMYSQL_ROWS;

typedef void * *PPMYSQL_ROWS;

typedef void * PMYSQL_DATA;

typedef void * PMYSQL_OPTIONS;

typedef void * PMYSQL;

typedef void * PMYSQL_RES;

typedef void * PMYSQL_BIND;

typedef void * PMYSQL_STMT;

typedef void * PMYSQL_METHODS;

typedef int enum_server_command;

typedef NET0800 *PNET0800;

struct DECLSPEC_DRECORD NET0800
{
public:
	void *vio;
	char *buff;
	char *buff_end;
	char *write_pos;
	char *read_pos;
	int fd;
#ifndef __x86_64__
	unsigned remain_in_buf;
	unsigned length;
	unsigned buf_length;
	unsigned where_b;
	unsigned max_packet;
	unsigned max_packet_size;
#else /* __x86_64__ */
	unsigned long remain_in_buf;
	unsigned long length;
	unsigned long buf_length;
	unsigned long where_b;
	unsigned long max_packet;
	unsigned long max_packet_size;
#endif /* __x86_64__ */
	unsigned pkt_nr;
	unsigned compress_pkt_nr;
	unsigned write_timeout;
	unsigned read_timeout;
	unsigned retry_count;
	int fcntl;
	unsigned *return_status;
	System::Byte reading_or_writing;
	System::Byte save_char;
	System::Byte compress;
	unsigned last_errno;
	System::Byte error;
	System::StaticArray<char, 512> last_error;
	System::StaticArray<char, 6> sqlstate;
	void *extension;
};


typedef NET0510 *PNET0510;

struct DECLSPEC_DRECORD NET0510
{
public:
	void *vio;
	char *buff;
	char *buff_end;
	char *write_pos;
	char *read_pos;
	int fd;
#ifndef __x86_64__
	unsigned remain_in_buf;
	unsigned length;
	unsigned buf_length;
	unsigned where_b;
	unsigned max_packet;
	unsigned max_packet_size;
#else /* __x86_64__ */
	unsigned long remain_in_buf;
	unsigned long length;
	unsigned long buf_length;
	unsigned long where_b;
	unsigned long max_packet;
	unsigned long max_packet_size;
#endif /* __x86_64__ */
	unsigned pkt_nr;
	unsigned compress_pkt_nr;
	unsigned write_timeout;
	unsigned read_timeout;
	unsigned retry_count;
	int fcntl;
	unsigned *return_status;
	System::Byte reading_or_writing;
	char save_char;
	System::Byte unused0;
	System::Byte unused;
	System::Byte compress;
	System::Byte unused1;
	char *query_cache_query;
	unsigned last_errno;
	System::Byte error;
	System::Byte unused2;
	System::Byte return_errno;
	System::StaticArray<char, 512> last_error;
	System::StaticArray<char, 6> sqlstate;
	void *extension;
};


typedef NET0506 *PNET0506;

struct DECLSPEC_DRECORD NET0506
{
public:
	void *vio;
	char *buff;
	char *buff_end;
	char *write_pos;
	char *read_pos;
	int fd;
#ifndef __x86_64__
	unsigned max_packet;
	unsigned max_packet_size;
#else /* __x86_64__ */
	unsigned long max_packet;
	unsigned long max_packet_size;
#endif /* __x86_64__ */
	unsigned pkt_nr;
	unsigned compress_pkt_nr;
	unsigned write_timeout;
	unsigned read_timeout;
	unsigned retry_count;
	int fcntl;
	System::Byte compress;
#ifndef __x86_64__
	unsigned remain_in_buf;
	unsigned length;
	unsigned buf_length;
	unsigned where_b;
#else /* __x86_64__ */
	unsigned long remain_in_buf;
	unsigned long length;
	unsigned long buf_length;
	unsigned long where_b;
#endif /* __x86_64__ */
	unsigned *return_status;
	System::Byte reading_or_writing;
	char save_char;
	System::Byte no_send_ok;
	System::Byte no_send_eof;
	System::Byte no_send_error;
	System::StaticArray<char, 512> last_error;
	System::StaticArray<char, 6> sqlstate;
	unsigned last_errno;
	System::Byte error;
	char *query_cache_query;
	System::Byte report_error;
	System::Byte return_errno;
};


typedef NET0500 *PNET0500;

struct DECLSPEC_DRECORD NET0500
{
public:
	void *vio;
	char *buff;
	char *buff_end;
	char *write_pos;
	char *read_pos;
	int fd;
#ifndef __x86_64__
	unsigned max_packet;
	unsigned max_packet_size;
#else /* __x86_64__ */
	unsigned long max_packet;
	unsigned long max_packet_size;
#endif /* __x86_64__ */
	unsigned pkt_nr;
	unsigned compress_pkt_nr;
	unsigned write_timeout;
	unsigned read_timeout;
	unsigned retry_count;
	int fcntl;
	System::Byte compress;
#ifndef __x86_64__
	unsigned remain_in_buf;
	unsigned length;
	unsigned buf_length;
	unsigned where_b;
#else /* __x86_64__ */
	unsigned long remain_in_buf;
	unsigned long length;
	unsigned long buf_length;
	unsigned long where_b;
#endif /* __x86_64__ */
	unsigned *return_status;
	System::Byte reading_or_writing;
	char save_char;
	System::Byte no_send_ok;
	System::Byte no_send_eof;
	System::StaticArray<char, 512> last_error;
	System::StaticArray<char, 6> sqlstate;
	unsigned last_errno;
	System::Byte error;
	char *query_cache_query;
	System::Byte report_error;
	System::Byte return_errno;
};


typedef NET0410 *PNET0410;

struct DECLSPEC_DRECORD NET0410
{
public:
	void *vio;
	char *buff;
	char *buff_end;
	char *write_pos;
	char *read_pos;
	int fd;
#ifndef __x86_64__
	unsigned max_packet;
	unsigned max_packet_size;
#else /* __x86_64__ */
	unsigned long max_packet;
	unsigned long max_packet_size;
#endif /* __x86_64__ */
	unsigned pkt_nr;
	unsigned compress_pkt_nr;
	unsigned write_timeout;
	unsigned read_timeout;
	unsigned retry_count;
	int fcntl;
	System::Byte compress;
#ifndef __x86_64__
	unsigned remain_in_buf;
	unsigned length;
	unsigned buf_length;
	unsigned where_b;
#else /* __x86_64__ */
	unsigned long remain_in_buf;
	unsigned long length;
	unsigned long buf_length;
	unsigned long where_b;
#endif /* __x86_64__ */
	unsigned *return_status;
	System::Byte reading_or_writing;
	char save_char;
	System::Byte no_send_ok;
	System::StaticArray<char, 200> last_error;
	System::StaticArray<char, 6> sqlstate;
	unsigned last_errno;
	System::Byte error;
	char *query_cache_query;
	System::Byte report_error;
	System::Byte return_errno;
};


typedef NET0400 *PNET0400;

struct DECLSPEC_DRECORD NET0400
{
public:
	void *vio;
	char *buff;
	char *buff_end;
	char *write_pos;
	char *read_pos;
	int fd;
#ifndef __x86_64__
	unsigned max_packet;
	unsigned max_packet_size;
#else /* __x86_64__ */
	unsigned long max_packet;
	unsigned long max_packet_size;
#endif /* __x86_64__ */
	unsigned last_errno;
	unsigned pkt_nr;
	unsigned compress_pkt_nr;
	unsigned write_timeout;
	unsigned read_timeout;
	unsigned retry_count;
	int fcntl;
	System::StaticArray<char, 200> last_error;
	System::Byte error;
	System::Byte return_errno;
	System::Byte compress;
#ifndef __x86_64__
	unsigned remain_in_buf;
	unsigned length;
	unsigned buf_length;
	unsigned where_b;
#else /* __x86_64__ */
	unsigned long remain_in_buf;
	unsigned long length;
	unsigned long buf_length;
	unsigned long where_b;
#endif /* __x86_64__ */
	unsigned *return_status;
	System::Byte reading_or_writing;
	char save_char;
	System::Byte no_send_ok;
	char *query_cache_query;
};


typedef NET0323 *PNET0323;

struct DECLSPEC_DRECORD NET0323
{
public:
	void *vio;
	int fd;
	int fcntl;
	char *buff;
	char *buff_end;
	char *write_pos;
	char *read_pos;
	System::StaticArray<char, 200> last_error;
	unsigned last_errno;
	unsigned max_packet;
	unsigned timeout;
	unsigned pkt_nr;
	System::Byte error;
	System::Byte return_errno;
	System::Byte compress;
	System::Byte no_send_ok;
#ifndef __x86_64__
	unsigned remain_in_buf;
	unsigned length;
	unsigned buf_length;
	unsigned where_b;
#else /* __x86_64__ */
	unsigned long remain_in_buf;
	unsigned long length;
	unsigned long buf_length;
	unsigned long where_b;
#endif /* __x86_64__ */
	unsigned *return_status;
	System::Byte reading_or_writing;
	char save_char;
};


typedef NET0320 *PNET0320;

struct DECLSPEC_DRECORD NET0320
{
public:
	void *vio;
	int fd;
	int fcntl;
	char *buff;
	char *buff_end;
	char *write_pos;
	char *read_pos;
	System::StaticArray<char, 200> last_error;
	unsigned last_errno;
	unsigned max_packet;
	unsigned timeout;
	unsigned pkt_nr;
	System::Byte error;
	System::Byte return_errno;
	System::Byte compress;
#ifndef __x86_64__
	unsigned remain_in_buf;
	unsigned length;
	unsigned buf_length;
	unsigned where_b;
#else /* __x86_64__ */
	unsigned long remain_in_buf;
	unsigned long length;
	unsigned long buf_length;
	unsigned long where_b;
#endif /* __x86_64__ */
	System::Byte more;
	char save_char;
};


typedef USED_MEM *PUSED_MEM;

struct DECLSPEC_DRECORD USED_MEM
{
public:
	USED_MEM *next;
	NativeUInt left;
	NativeUInt size;
};


typedef void __fastcall (*TVoidProc)(void);

typedef TVoidProc *PVoidProc;

typedef unsigned PSI_memory_key;

typedef MEM_ROOT0600 *PMEM_ROOT0600;

struct DECLSPEC_DRECORD MEM_ROOT0600
{
public:
	USED_MEM *free;
	USED_MEM *used;
	USED_MEM *pre_alloc;
	NativeUInt min_malloc;
	NativeUInt block_size;
	unsigned block_num;
	unsigned first_block_usage;
	TVoidProc *error_handler;
	unsigned m_psi_key;
};


typedef MEM_ROOT0570 *PMEM_ROOT0570;

struct DECLSPEC_DRECORD MEM_ROOT0570
{
public:
	USED_MEM *free;
	USED_MEM *used;
	USED_MEM *pre_alloc;
	NativeUInt min_malloc;
	NativeUInt block_size;
	unsigned block_num;
	unsigned first_block_usage;
	NativeUInt max_capacity;
	NativeUInt allocated_size;
	System::Byte error_for_capacity_exceeded;
	TVoidProc *error_handler;
	unsigned m_psi_key;
};


typedef MEM_ROOT0410 *PMEM_ROOT0410;

struct DECLSPEC_DRECORD MEM_ROOT0410
{
public:
	USED_MEM *free;
	USED_MEM *used;
	USED_MEM *pre_alloc;
	NativeUInt min_malloc;
	NativeUInt block_size;
	unsigned block_num;
	unsigned first_block_usage;
	TVoidProc *error_handler;
};


typedef MEM_ROOT0323 *PMEM_ROOT0323;

struct DECLSPEC_DRECORD MEM_ROOT0323
{
public:
	USED_MEM *free;
	USED_MEM *used;
	USED_MEM *pre_alloc;
	NativeUInt min_malloc;
	NativeUInt block_size;
	TVoidProc *error_handler;
};


typedef MEM_ROOT0320 *PMEM_ROOT0320;

struct DECLSPEC_DRECORD MEM_ROOT0320
{
public:
	USED_MEM *free;
	USED_MEM *used;
	NativeUInt min_malloc;
	NativeUInt block_size;
	TVoidProc *error_handler;
};


typedef MYSQL_FIELD0510 *PMYSQL_FIELD0510;

struct DECLSPEC_DRECORD MYSQL_FIELD0510
{
public:
	char *name;
	char *org_name;
	char *table;
	char *org_table;
	char *db;
	char *catalog;
	char *def;
#ifndef __x86_64__
	unsigned length;
	unsigned max_length;
#else /* __x86_64__ */
	unsigned long length;
	unsigned long max_length;
#endif /* __x86_64__ */
	unsigned name_length;
	unsigned org_name_length;
	unsigned table_length;
	unsigned org_table_length;
	unsigned db_length;
	unsigned catalog_length;
	unsigned def_length;
	unsigned flags;
	unsigned decimals;
	unsigned charsetnr;
	System::Byte type_;
	void *extension;
};


typedef MYSQL_FIELD0410 *PMYSQL_FIELD0410;

struct DECLSPEC_DRECORD MYSQL_FIELD0410
{
public:
	char *name;
	char *org_name;
	char *table;
	char *org_table;
	char *db;
	char *catalog;
	char *def;
#ifndef __x86_64__
	unsigned length;
	unsigned max_length;
#else /* __x86_64__ */
	unsigned long length;
	unsigned long max_length;
#endif /* __x86_64__ */
	unsigned name_length;
	unsigned org_name_length;
	unsigned table_length;
	unsigned org_table_length;
	unsigned db_length;
	unsigned catalog_length;
	unsigned def_length;
	unsigned flags;
	unsigned decimals;
	unsigned charsetnr;
	System::Byte type_;
};


typedef MYSQL_FIELD0401 *PMYSQL_FIELD0401;

struct DECLSPEC_DRECORD MYSQL_FIELD0401
{
public:
	char *name;
	char *org_name;
	char *table;
	char *org_table;
	char *db;
	char *def;
#ifndef __x86_64__
	unsigned length;
	unsigned max_length;
#else /* __x86_64__ */
	unsigned long length;
	unsigned long max_length;
#endif /* __x86_64__ */
	unsigned name_length;
	unsigned org_name_length;
	unsigned table_length;
	unsigned org_table_length;
	unsigned db_length;
	unsigned def_length;
	unsigned flags;
	unsigned decimals;
	unsigned charsetnr;
	System::Byte type_;
};


typedef MYSQL_FIELD0400 *PMYSQL_FIELD0400;

struct DECLSPEC_DRECORD MYSQL_FIELD0400
{
public:
	char *name;
	char *table;
	char *org_table;
	char *db;
	char *def;
#ifndef __x86_64__
	unsigned length;
	unsigned max_length;
#else /* __x86_64__ */
	unsigned long length;
	unsigned long max_length;
#endif /* __x86_64__ */
	unsigned flags;
	unsigned decimals;
	System::Byte type_;
};


typedef MYSQL_FIELD0320 *PMYSQL_FIELD0320;

struct DECLSPEC_DRECORD MYSQL_FIELD0320
{
public:
	char *name;
	char *table;
	char *def;
	System::Byte type_;
	unsigned length;
	unsigned max_length;
	unsigned flags;
	unsigned decimals;
};


typedef PPByte MYSQL_ROW;

typedef unsigned MYSQL_FIELD_OFFSET;

typedef unsigned __int64 my_ulonglong;

typedef MYSQL_ROWS0410 *PMYSQL_ROWS0410;

struct DECLSPEC_DRECORD MYSQL_ROWS0410
{
public:
	void *next;
	System::PByte *data;
#ifndef __x86_64__
	int length;
#else /* __x86_64__ */
	long length;
#endif /* __x86_64__ */
};


typedef MYSQL_ROWS0320 *PMYSQL_ROWS0320;

struct DECLSPEC_DRECORD MYSQL_ROWS0320
{
public:
	void *next;
	System::PByte *data;
};


typedef void * MYSQL_ROW_OFFSET;

typedef MYSQL_DATA0800 *PMYSQL_DATA0800;

struct DECLSPEC_DRECORD MYSQL_DATA0800
{
public:
	void *data;
	MEM_ROOT0600 alloc;
	unsigned __int64 rows;
	unsigned fields;
};


typedef MYSQL_DATA0600 *PMYSQL_DATA0600;

struct DECLSPEC_DRECORD MYSQL_DATA0600
{
public:
	void *data;
	void *embedded_info;
	MEM_ROOT0600 alloc;
	unsigned __int64 rows;
	unsigned fields;
	void *extension;
};


typedef MYSQL_DATA0570 *PMYSQL_DATA0570;

struct DECLSPEC_DRECORD MYSQL_DATA0570
{
public:
	void *data;
	void *embedded_info;
	MEM_ROOT0570 alloc;
	unsigned __int64 rows;
	unsigned fields;
	void *extension;
};


typedef MYSQL_DATA0510 *PMYSQL_DATA0510;

struct DECLSPEC_DRECORD MYSQL_DATA0510
{
public:
	void *data;
	void *embedded_info;
	MEM_ROOT0410 alloc;
	unsigned __int64 rows;
	unsigned fields;
	void *extension;
};


typedef MYSQL_DATA0506 *PMYSQL_DATA0506;

struct DECLSPEC_DRECORD MYSQL_DATA0506
{
public:
	unsigned __int64 rows;
	unsigned fields;
	void *data;
	MEM_ROOT0410 alloc;
	void * *prev_ptr;
};


typedef MYSQL_DATA0410 *PMYSQL_DATA0410;

struct DECLSPEC_DRECORD MYSQL_DATA0410
{
public:
	unsigned __int64 rows;
	unsigned fields;
	void *data;
	MEM_ROOT0410 alloc;
};


typedef MYSQL_DATA0323 *PMYSQL_DATA0323;

struct DECLSPEC_DRECORD MYSQL_DATA0323
{
public:
	unsigned __int64 rows;
	unsigned fields;
	void *data;
	MEM_ROOT0323 alloc;
};


typedef MYSQL_DATA0320 *PMYSQL_DATA0320;

struct DECLSPEC_DRECORD MYSQL_DATA0320
{
public:
	unsigned __int64 rows;
	unsigned fields;
	void *data;
	MEM_ROOT0320 alloc;
};


typedef int mysql_option;

typedef MYSQL_OPTIONS0800 *PMYSQL_OPTIONS0800;

struct DECLSPEC_DRECORD MYSQL_OPTIONS0800
{
public:
	unsigned connect_timeout;
	unsigned read_timeout;
	unsigned write_timeout;
	unsigned port;
	unsigned protocol;
#ifndef __x86_64__
	unsigned client_flag;
#else /* __x86_64__ */
	unsigned long client_flag;
#endif /* __x86_64__ */
	char *host;
	char *user;
	char *password;
	char *unix_socket;
	char *db;
	void *init_commands;
	char *my_cnf_file;
	char *my_cnf_group;
	char *charset_dir;
	char *charset_name;
	char *ssl_key;
	char *ssl_cert;
	char *ssl_ca;
	char *ssl_capath;
	char *ssl_cipher;
	char *shared_memory_base_name;
#ifndef __x86_64__
	unsigned max_allowed_packet;
#else /* __x86_64__ */
	unsigned long max_allowed_packet;
#endif /* __x86_64__ */
	System::Byte compress;
	System::Byte named_pipe;
	char *bind_address;
	System::Byte report_data_truncation;
	void *local_infile_init;
	void *local_infile_read;
	void *local_infile_end;
	void *local_infile_error;
	void *local_infile_userdata;
	void *extension;
};


typedef MYSQL_OPTIONS0510 *PMYSQL_OPTIONS0510;

struct DECLSPEC_DRECORD MYSQL_OPTIONS0510
{
public:
	unsigned connect_timeout;
	unsigned read_timeout;
	unsigned write_timeout;
	unsigned port;
	unsigned protocol;
#ifndef __x86_64__
	unsigned client_flag;
#else /* __x86_64__ */
	unsigned long client_flag;
#endif /* __x86_64__ */
	char *host;
	char *user;
	char *password;
	char *unix_socket;
	char *db;
	void *init_commands;
	char *my_cnf_file;
	char *my_cnf_group;
	char *charset_dir;
	char *charset_name;
	char *ssl_key;
	char *ssl_cert;
	char *ssl_ca;
	char *ssl_capath;
	char *ssl_cipher;
	char *shared_memory_base_name;
#ifndef __x86_64__
	unsigned max_allowed_packet;
#else /* __x86_64__ */
	unsigned long max_allowed_packet;
#endif /* __x86_64__ */
	System::Byte use_ssl;
	System::Byte compress;
	System::Byte named_pipe;
	System::Byte rpl_probe;
	System::Byte rpl_parse;
	System::Byte no_master_reads;
	System::Byte separate_thread;
	int methods_to_use;
	char *client_ip;
	System::Byte secure_auth;
	System::Byte report_data_truncation;
	void *local_infile_init;
	void *local_infile_read;
	void *local_infile_end;
	void *local_infile_error;
	void *local_infile_userdata;
	void *extension;
};


typedef MYSQL_OPTIONS0506 *PMYSQL_OPTIONS0506;

struct DECLSPEC_DRECORD MYSQL_OPTIONS0506
{
public:
	unsigned connect_timeout;
	unsigned read_timeout;
	unsigned write_timeout;
	unsigned port;
	unsigned protocol;
	unsigned client_flag;
	char *host;
	char *user;
	char *password;
	char *unix_socket;
	char *db;
	void *init_commands;
	char *my_cnf_file;
	char *my_cnf_group;
	char *charset_dir;
	char *charset_name;
	char *ssl_key;
	char *ssl_cert;
	char *ssl_ca;
	char *ssl_capath;
	char *ssl_cipher;
	char *shared_memory_base_name;
#ifndef __x86_64__
	unsigned max_allowed_packet;
#else /* __x86_64__ */
	unsigned long max_allowed_packet;
#endif /* __x86_64__ */
	System::Byte use_ssl;
	System::Byte compress;
	System::Byte named_pipe;
	System::Byte rpl_probe;
	System::Byte rpl_parse;
	System::Byte no_master_reads;
	System::Byte separate_thread;
	int methods_to_use;
	char *client_ip;
	System::Byte secure_auth;
	System::Byte report_data_truncation;
	void *local_infile_init;
	void *local_infile_read;
	void *local_infile_end;
	void *local_infile_error;
	void *local_infile_userdata;
};


typedef MYSQL_OPTIONS0410 *PMYSQL_OPTIONS0410;

struct DECLSPEC_DRECORD MYSQL_OPTIONS0410
{
public:
	unsigned connect_timeout;
	unsigned read_timeout;
	unsigned write_timeout;
	unsigned port;
	unsigned protocol;
	unsigned client_flag;
	char *host;
	char *user;
	char *password;
	char *unix_socket;
	char *db;
	void *init_commands;
	char *my_cnf_file;
	char *my_cnf_group;
	char *charset_dir;
	char *charset_name;
	char *ssl_key;
	char *ssl_cert;
	char *ssl_ca;
	char *ssl_capath;
	char *ssl_cipher;
	char *shared_memory_base_name;
#ifndef __x86_64__
	unsigned max_allowed_packet;
#else /* __x86_64__ */
	unsigned long max_allowed_packet;
#endif /* __x86_64__ */
	System::Byte use_ssl;
	System::Byte compress;
	System::Byte named_pipe;
	System::Byte rpl_probe;
	System::Byte rpl_parse;
	System::Byte no_master_reads;
	int methods_to_use;
	char *client_ip;
	System::Byte secure_auth;
	void *local_infile_init;
	void *local_infile_read;
	void *local_infile_end;
	void *local_infile_error;
	void *local_infile_userdata;
};


typedef MYSQL_OPTIONS0400 *PMYSQL_OPTIONS0400;

struct DECLSPEC_DRECORD MYSQL_OPTIONS0400
{
public:
	unsigned connect_timeout;
	unsigned client_flag;
	unsigned port;
	char *host;
	char *init_command;
	char *user;
	char *password;
	char *unix_socket;
	char *db;
	char *my_cnf_file;
	char *my_cnf_group;
	char *charset_dir;
	char *charset_name;
	char *ssl_key;
	char *ssl_cert;
	char *ssl_ca;
	char *ssl_capath;
	char *ssl_cipher;
#ifndef __x86_64__
	unsigned max_allowed_packet;
#else /* __x86_64__ */
	unsigned long max_allowed_packet;
#endif /* __x86_64__ */
	System::Byte use_ssl;
	System::Byte compress;
	System::Byte named_pipe;
	System::Byte rpl_probe;
	System::Byte rpl_parse;
	System::Byte no_master_reads;
};


typedef MYSQL_OPTIONS0320 *PMYSQL_OPTIONS0320;

struct DECLSPEC_DRECORD MYSQL_OPTIONS0320
{
public:
	unsigned connect_timeout;
	unsigned client_flag;
	System::Byte compress;
	System::Byte named_pipe;
	unsigned port;
	char *host;
	char *init_command;
	char *user;
	char *password;
	char *unix_socket;
	char *db;
	char *my_cnf_file;
	char *my_cnf_group;
	char *charset_dir;
	char *charset_name;
	System::Byte use_ssl;
	char *ssl_key;
	char *ssl_cert;
	char *ssl_ca;
	char *ssl_capath;
};


typedef int mysql_status;

typedef int mysql_protocol_type;

typedef int mysql_ssl_mode;

typedef int mysql_ssl_fips_mode;

typedef int mysql_rpl_type;

typedef int enum_resultset_metadata;

typedef int enum_cursor_type;

typedef int enum_mysql_set_option;

typedef MYSQL_METHODS0510 *PMYSQL_METHODS0510;

struct DECLSPEC_DRECORD MYSQL_METHODS0510
{
public:
	System::Byte __fastcall (*read_query_result)(void * mysql);
#ifndef __x86_64__
	System::Byte __fastcall (*advanced_command)(void * mysql, int command, System::PByte header, unsigned header_length, System::PByte arg, unsigned arg_length, System::Byte skip_check, void * stmt);
#else /* __x86_64__ */
	System::Byte __fastcall (*advanced_command)(void * mysql, int command, System::PByte header, unsigned long header_length, System::PByte arg, unsigned long arg_length, System::Byte skip_check, void * stmt);
#endif /* __x86_64__ */
	void * __fastcall (*read_rows)(void * mysql, void * mysql_fields, unsigned fields);
	void * __fastcall (*use_result)(void * mysql);
	void __fastcall (*fetch_lengths)(Pmy_ulong _to, PPByte column, unsigned field_count);
	void __fastcall (*flush_use_result)(void * mysql);
	void * __fastcall (*list_fields)(void * mysql);
	System::Byte __fastcall (*read_prepare_result)(void * mysql, void * stmt);
	int __fastcall (*stmt_execute)(void * stmt);
	int __fastcall (*read_binary_rows)(void * stmt);
	int __fastcall (*unbuffered_fetch)(void * mysql, System::PPWideChar row);
	void __fastcall (*free_embedded_thd)(void * mysql);
	char * __fastcall (*read_statistics)(void * mysql);
	System::Byte __fastcall (*next_result)(void * mysql);
	int __fastcall (*read_change_user_result)(void * mysql, char * buff, char * passwd);
	int __fastcall (*read_rows_from_cursor)(void * stmt);
};


typedef MYSQL_METHODS0506 *PMYSQL_METHODS0506;

struct DECLSPEC_DRECORD MYSQL_METHODS0506
{
public:
	System::Byte __fastcall (*read_query_result)(void * mysql);
#ifndef __x86_64__
	System::Byte __fastcall (*advanced_command)(void * mysql, int command, char * header, unsigned header_length, char * arg, unsigned arg_length, System::Byte skip_check);
#else /* __x86_64__ */
	System::Byte __fastcall (*advanced_command)(void * mysql, int command, char * header, unsigned long header_length, char * arg, unsigned long arg_length, System::Byte skip_check);
#endif /* __x86_64__ */
	void * __fastcall (*read_rows)(void * mysql, void * mysql_fields, unsigned fields);
	void * __fastcall (*use_result)(void * mysql);
	void __fastcall (*fetch_lengths)(Pmy_ulong _to, PPByte column, unsigned field_count);
	void __fastcall (*flush_use_result)(void * mysql);
	void * __fastcall (*list_fields)(void * mysql);
	System::Byte __fastcall (*read_prepare_result)(void * mysql, void * stmt);
	int __fastcall (*stmt_execute)(void * stmt);
	int __fastcall (*read_binary_rows)(void * stmt);
	int __fastcall (*unbuffered_fetch)(void * mysql, System::PPWideChar row);
	void __fastcall (*free_embedded_thd)(void * mysql);
	char * __fastcall (*read_statistics)(void * mysql);
	System::Byte __fastcall (*next_result)(void * mysql);
	int __fastcall (*read_change_user_result)(void * mysql, char * buff, char * passwd);
};


typedef MYSQL_METHODS0410 *PMYSQL_METHODS0410;

struct DECLSPEC_DRECORD MYSQL_METHODS0410
{
public:
	System::Byte __fastcall (*read_query_result)(void * mysql);
#ifndef __x86_64__
	System::Byte __fastcall (*advanced_command)(void * mysql, int command, char * header, unsigned header_length, char * arg, unsigned arg_length, System::Byte skip_check);
#else /* __x86_64__ */
	System::Byte __fastcall (*advanced_command)(void * mysql, int command, char * header, unsigned long header_length, char * arg, unsigned long arg_length, System::Byte skip_check);
#endif /* __x86_64__ */
	void * __fastcall (*read_rows)(void * mysql, void * mysql_fields, unsigned fields);
	void * __fastcall (*use_result)(void * mysql);
	void __fastcall (*fetch_lengths)(Pmy_ulong _to, PPByte column, unsigned field_count);
	void * __fastcall (*list_fields)(void * mysql);
	System::Byte __fastcall (*read_prepare_result)(void * mysql, void * stmt);
	int __fastcall (*stmt_execute)(void * stmt);
	int __fastcall (*read_binary_rows)(void * stmt);
	int __fastcall (*unbuffered_fetch)(void * mysql, System::PPWideChar row);
	void __fastcall (*free_embedded_thd)(void * mysql);
	char * __fastcall (*read_statistics)(void * mysql);
	System::Byte __fastcall (*next_result)(void * mysql);
	int __fastcall (*read_change_user_result)(void * mysql, char * buff, char * passwd);
};


typedef MYSQL_LIST *PMYSQL_LIST;

struct DECLSPEC_DRECORD MYSQL_LIST
{
public:
	MYSQL_LIST *prev;
	MYSQL_LIST *next;
	void *data;
};


typedef MY_CHARSET_INFO *PMY_CHARSET_INFO;

struct DECLSPEC_DRECORD MY_CHARSET_INFO
{
public:
	unsigned number;
	unsigned state;
	char *csname;
	char *name;
	char *comment;
	char *dir;
	unsigned mbminlen;
	unsigned mbmaxlen;
};


typedef MYSQL0800 *PMYSQL0800;

struct DECLSPEC_DRECORD MYSQL0800
{
public:
	NET0800 net;
	char *connector_fd;
	char *host;
	char *user;
	char *passwd;
	char *unix_socket;
	char *server_version;
	char *host_info;
	char *info;
	char *db;
	MY_CHARSET_INFO *charset;
	MYSQL_FIELD0510 *fields;
	MEM_ROOT0600 *field_alloc;
	unsigned __int64 affected_rows;
	unsigned __int64 insert_id;
	unsigned __int64 extra_info;
#ifndef __x86_64__
	unsigned thread_id;
	unsigned packet_length;
#else /* __x86_64__ */
	unsigned long thread_id;
	unsigned long packet_length;
#endif /* __x86_64__ */
	unsigned port;
#ifndef __x86_64__
	unsigned client_flag;
	unsigned server_capabilities;
#else /* __x86_64__ */
	unsigned long client_flag;
	unsigned long server_capabilities;
#endif /* __x86_64__ */
	unsigned protocol_version;
	unsigned field_count;
	unsigned server_status;
	unsigned server_language;
	unsigned warning_count;
	MYSQL_OPTIONS0800 options;
	int status;
	int resultset_metadata;
	System::Byte free_me;
	System::Byte reconnect;
	System::StaticArray<char, 21> scramble;
	MYSQL_LIST *stmts;
	MYSQL_METHODS0510 *methods;
	void *thd;
	System::Byte unbuffered_fetch_owner;
	void *extension;
};


typedef MYSQL0600 *PMYSQL0600;

struct DECLSPEC_DRECORD MYSQL0600
{
public:
	NET0510 net;
	char *connector_fd;
	char *host;
	char *user;
	char *passwd;
	char *unix_socket;
	char *server_version;
	char *host_info;
	char *info;
	char *db;
	MY_CHARSET_INFO *charset;
	MYSQL_FIELD0510 *fields;
	MEM_ROOT0600 field_alloc;
	unsigned __int64 affected_rows;
	unsigned __int64 insert_id;
	unsigned __int64 extra_info;
#ifndef __x86_64__
	unsigned thread_id;
	unsigned packet_length;
#else /* __x86_64__ */
	unsigned long thread_id;
	unsigned long packet_length;
#endif /* __x86_64__ */
	unsigned port;
#ifndef __x86_64__
	unsigned client_flag;
	unsigned server_capabilities;
#else /* __x86_64__ */
	unsigned long client_flag;
	unsigned long server_capabilities;
#endif /* __x86_64__ */
	unsigned protocol_version;
	unsigned field_count;
	unsigned server_status;
	unsigned server_language;
	unsigned warning_count;
	MYSQL_OPTIONS0510 options;
	int status;
	System::Byte free_me;
	System::Byte reconnect;
	System::StaticArray<char, 21> scramble;
	System::Byte rpl_pivot;
	void *master;
	void *next_slave;
	void *last_used_slave;
	void *last_used_con;
	MYSQL_LIST *stmts;
	MYSQL_METHODS0510 *methods;
	void *thd;
	System::Byte unbuffered_fetch_owner;
	char *info_buffer;
	void *extension;
};


typedef MYSQL0570 *PMYSQL0570;

struct DECLSPEC_DRECORD MYSQL0570
{
public:
	NET0510 net;
	char *connector_fd;
	char *host;
	char *user;
	char *passwd;
	char *unix_socket;
	char *server_version;
	char *host_info;
	char *info;
	char *db;
	MY_CHARSET_INFO *charset;
	MYSQL_FIELD0510 *fields;
	MEM_ROOT0570 field_alloc;
	unsigned __int64 affected_rows;
	unsigned __int64 insert_id;
	unsigned __int64 extra_info;
#ifndef __x86_64__
	unsigned thread_id;
	unsigned packet_length;
#else /* __x86_64__ */
	unsigned long thread_id;
	unsigned long packet_length;
#endif /* __x86_64__ */
	unsigned port;
#ifndef __x86_64__
	unsigned client_flag;
	unsigned server_capabilities;
#else /* __x86_64__ */
	unsigned long client_flag;
	unsigned long server_capabilities;
#endif /* __x86_64__ */
	unsigned protocol_version;
	unsigned field_count;
	unsigned server_status;
	unsigned server_language;
	unsigned warning_count;
	MYSQL_OPTIONS0510 options;
	int status;
	System::Byte free_me;
	System::Byte reconnect;
	System::StaticArray<char, 21> scramble;
	System::Byte rpl_pivot;
	void *master;
	void *next_slave;
	void *last_used_slave;
	void *last_used_con;
	MYSQL_LIST *stmts;
	MYSQL_METHODS0510 *methods;
	void *thd;
	System::Byte unbuffered_fetch_owner;
	char *info_buffer;
	void *extension;
};


typedef MYSQL0510 *PMYSQL0510;

struct DECLSPEC_DRECORD MYSQL0510
{
public:
	NET0510 net;
	char *connector_fd;
	char *host;
	char *user;
	char *passwd;
	char *unix_socket;
	char *server_version;
	char *host_info;
	char *info;
	char *db;
	MY_CHARSET_INFO *charset;
	MYSQL_FIELD0510 *fields;
	MEM_ROOT0410 field_alloc;
	unsigned __int64 affected_rows;
	unsigned __int64 insert_id;
	unsigned __int64 extra_info;
#ifndef __x86_64__
	unsigned thread_id;
	unsigned packet_length;
#else /* __x86_64__ */
	unsigned long thread_id;
	unsigned long packet_length;
#endif /* __x86_64__ */
	unsigned port;
#ifndef __x86_64__
	unsigned client_flag;
	unsigned server_capabilities;
#else /* __x86_64__ */
	unsigned long client_flag;
	unsigned long server_capabilities;
#endif /* __x86_64__ */
	unsigned protocol_version;
	unsigned field_count;
	unsigned server_status;
	unsigned server_language;
	unsigned warning_count;
	MYSQL_OPTIONS0510 options;
	int status;
	System::Byte free_me;
	System::Byte reconnect;
	System::StaticArray<char, 21> scramble;
	System::Byte rpl_pivot;
	void *master;
	void *next_slave;
	void *last_used_slave;
	void *last_used_con;
	MYSQL_LIST *stmts;
	MYSQL_METHODS0510 *methods;
	void *thd;
	System::Byte unbuffered_fetch_owner;
	char *info_buffer;
	void *extension;
};


typedef MYSQL0506 *PMYSQL0506;

struct DECLSPEC_DRECORD MYSQL0506
{
public:
	NET0506 net;
	char *connector_fd;
	char *host;
	char *user;
	char *passwd;
	char *unix_socket;
	char *server_version;
	char *host_info;
	char *info;
	char *db;
	MY_CHARSET_INFO *charset;
	void *fields;
	MEM_ROOT0410 field_alloc;
	unsigned __int64 affected_rows;
	unsigned __int64 insert_id;
	unsigned __int64 extra_info;
#ifndef __x86_64__
	unsigned thread_id;
	unsigned packet_length;
#else /* __x86_64__ */
	unsigned long thread_id;
	unsigned long packet_length;
#endif /* __x86_64__ */
	unsigned port;
#ifndef __x86_64__
	unsigned client_flag;
	unsigned server_capabilities;
#else /* __x86_64__ */
	unsigned long client_flag;
	unsigned long server_capabilities;
#endif /* __x86_64__ */
	unsigned protocol_version;
	unsigned field_count;
	unsigned server_status;
	unsigned server_language;
	unsigned warning_count;
	MYSQL_OPTIONS0506 options;
	int status;
	System::Byte free_me;
	System::Byte reconnect;
	System::StaticArray<char, 21> scramble;
	System::Byte rpl_pivot;
	void *master;
	void *next_slave;
	void *last_used_slave;
	void *last_used_con;
	MYSQL_LIST *stmts;
	MYSQL_METHODS0506 *methods;
	void *thd;
	System::Byte unbuffered_fetch_owner;
	char *info_buffer;
};


typedef MYSQL0500 *PMYSQL0500;

struct DECLSPEC_DRECORD MYSQL0500
{
public:
	NET0500 net;
	char *connector_fd;
	char *host;
	char *user;
	char *passwd;
	char *unix_socket;
	char *server_version;
	char *host_info;
	char *info;
	char *db;
	MY_CHARSET_INFO *charset;
	void *fields;
	MEM_ROOT0410 field_alloc;
	unsigned __int64 affected_rows;
	unsigned __int64 insert_id;
	unsigned __int64 extra_info;
#ifndef __x86_64__
	unsigned thread_id;
	unsigned packet_length;
#else /* __x86_64__ */
	unsigned long thread_id;
	unsigned long packet_length;
#endif /* __x86_64__ */
	unsigned port;
#ifndef __x86_64__
	unsigned client_flag;
	unsigned server_capabilities;
#else /* __x86_64__ */
	unsigned long client_flag;
	unsigned long server_capabilities;
#endif /* __x86_64__ */
	unsigned protocol_version;
	unsigned field_count;
	unsigned server_status;
	unsigned server_language;
	unsigned warning_count;
	MYSQL_OPTIONS0410 options;
	int status;
	System::Byte free_me;
	System::Byte reconnect;
	System::StaticArray<char, 21> scramble;
	System::Byte rpl_pivot;
	void *master;
	void *next_slave;
	void *last_used_slave;
	void *last_used_con;
	MYSQL_LIST *stmts;
	void *methods;
	void *thd;
	System::Byte unbuffered_fetch_owner;
	char *info_buffer;
};


typedef MYSQL0410 *PMYSQL0410;

struct DECLSPEC_DRECORD MYSQL0410
{
public:
	NET0410 net;
	char *connector_fd;
	char *host;
	char *user;
	char *passwd;
	char *unix_socket;
	char *server_version;
	char *host_info;
	char *info;
	char *db;
	MY_CHARSET_INFO *charset;
	void *fields;
	MEM_ROOT0410 field_alloc;
	unsigned __int64 affected_rows;
	unsigned __int64 insert_id;
	unsigned __int64 extra_info;
#ifndef __x86_64__
	unsigned thread_id;
	unsigned packet_length;
#else /* __x86_64__ */
	unsigned long thread_id;
	unsigned long packet_length;
#endif /* __x86_64__ */
	unsigned port;
	unsigned client_flag;
	unsigned server_capabilities;
	unsigned protocol_version;
	unsigned field_count;
	unsigned server_status;
	unsigned server_language;
	unsigned warning_count;
	MYSQL_OPTIONS0410 options;
	int status;
	System::Byte free_me;
	System::Byte reconnect;
	System::StaticArray<char, 21> scramble;
	System::Byte rpl_pivot;
	void *master;
	void *next_slave;
	void *last_used_slave;
	void *last_used_con;
	MYSQL_LIST *stmts;
	void *methods;
	void *thd;
	System::Byte unbuffered_fetch_owner;
};


typedef MYSQL0400 *PMYSQL0400;

struct DECLSPEC_DRECORD MYSQL0400
{
public:
	NET0400 net;
	char *connector_fd;
	char *host;
	char *user;
	char *passwd;
	char *unix_socket;
	char *server_version;
	char *host_info;
	char *info;
	char *db;
	MY_CHARSET_INFO *charset;
	void *fields;
	MEM_ROOT0323 field_alloc;
	unsigned __int64 affected_rows;
	unsigned __int64 insert_id;
	unsigned __int64 extra_info;
#ifndef __x86_64__
	unsigned thread_id;
	unsigned packet_length;
#else /* __x86_64__ */
	unsigned long thread_id;
	unsigned long packet_length;
#endif /* __x86_64__ */
	unsigned port;
	unsigned client_flag;
	unsigned server_capabilities;
	unsigned protocol_version;
	unsigned field_count;
	unsigned server_status;
	unsigned server_language;
	MYSQL_OPTIONS0400 options;
	int status;
	System::Byte free_me;
	System::Byte reconnect;
	System::StaticArray<char, 9> scramble_buff;
	System::Byte rpl_pivot;
	void *master;
	void *next_slave;
	void *last_used_slave;
	void *last_used_con;
};


typedef MYSQL0323 *PMYSQL0323;

struct DECLSPEC_DRECORD MYSQL0323
{
public:
	NET0323 net;
	char *connector_fd;
	char *host;
	char *user;
	char *passwd;
	char *unix_socket;
	char *server_version;
	char *host_info;
	char *info;
	char *db;
	unsigned port;
	unsigned client_flag;
	unsigned server_capabilities;
	unsigned protocol_version;
	unsigned field_count;
	unsigned server_status;
#ifndef __x86_64__
	unsigned thread_id;
#else /* __x86_64__ */
	unsigned long thread_id;
#endif /* __x86_64__ */
	unsigned __int64 affected_rows;
	unsigned __int64 insert_id;
	unsigned __int64 extra_info;
#ifndef __x86_64__
	unsigned packet_length;
#else /* __x86_64__ */
	unsigned long packet_length;
#endif /* __x86_64__ */
	int status;
	void *fields;
	MEM_ROOT0323 field_alloc;
	System::Byte free_me;
	System::Byte reconnect;
	MYSQL_OPTIONS0320 options;
	System::StaticArray<char, 9> scramble_buff;
	MY_CHARSET_INFO *charset;
	unsigned server_language;
};


typedef MYSQL0320 *PMYSQL0320;

struct DECLSPEC_DRECORD MYSQL0320
{
public:
	NET0320 net;
	char *connector_fd;
	char *host;
	char *user;
	char *passwd;
	char *unix_socket;
	char *server_version;
	char *host_info;
	char *info;
	char *db;
	unsigned port;
	unsigned client_flag;
	unsigned server_capabilities;
	unsigned protocol_version;
	unsigned field_count;
#ifndef __x86_64__
	unsigned thread_id;
#else /* __x86_64__ */
	unsigned long thread_id;
#endif /* __x86_64__ */
	unsigned __int64 affected_rows;
	unsigned __int64 insert_id;
	unsigned __int64 extra_info;
#ifndef __x86_64__
	unsigned packet_length;
#else /* __x86_64__ */
	unsigned long packet_length;
#endif /* __x86_64__ */
	int status;
	void *fields;
	MEM_ROOT0320 field_alloc;
	System::Byte free_me;
	System::Byte reconnect;
	MYSQL_OPTIONS0320 options;
	System::StaticArray<char, 9> scramble_buff;
	MY_CHARSET_INFO *charset;
};


typedef MYSQL_RES0800 *PMYSQL_RES0800;

struct DECLSPEC_DRECORD MYSQL_RES0800
{
public:
	unsigned __int64 row_count;
	MYSQL_FIELD0510 *fields;
	MYSQL_DATA0600 *data;
	MYSQL_ROWS0410 *data_cursor;
#ifndef __x86_64__
	int *lengths;
#else /* __x86_64__ */
	long *lengths;
#endif /* __x86_64__ */
	MYSQL0600 *handle;
	MYSQL_METHODS0510 *methods;
	System::PByte *row;
	System::PByte *current_row;
	MEM_ROOT0600 field_alloc;
	unsigned field_count;
	unsigned current_field;
	System::Byte eof;
	System::Byte unbuffered_fetch_cancelled;
	int metadata;
	void *extension;
};


typedef MYSQL_RES0600 *PMYSQL_RES0600;

struct DECLSPEC_DRECORD MYSQL_RES0600
{
public:
	unsigned __int64 row_count;
	MYSQL_FIELD0510 *fields;
	MYSQL_DATA0600 *data;
	MYSQL_ROWS0410 *data_cursor;
#ifndef __x86_64__
	int *lengths;
#else /* __x86_64__ */
	long *lengths;
#endif /* __x86_64__ */
	MYSQL0600 *handle;
	MYSQL_METHODS0510 *methods;
	System::PByte *row;
	System::PByte *current_row;
	MEM_ROOT0600 field_alloc;
	unsigned field_count;
	unsigned current_field;
	System::Byte eof;
	System::Byte unbuffered_fetch_cancelled;
	void *extension;
};


typedef MYSQL_RES0570 *PMYSQL_RES0570;

struct DECLSPEC_DRECORD MYSQL_RES0570
{
public:
	unsigned __int64 row_count;
	MYSQL_FIELD0510 *fields;
	MYSQL_DATA0570 *data;
	MYSQL_ROWS0410 *data_cursor;
#ifndef __x86_64__
	int *lengths;
#else /* __x86_64__ */
	long *lengths;
#endif /* __x86_64__ */
	MYSQL0570 *handle;
	MYSQL_METHODS0510 *methods;
	System::PByte *row;
	System::PByte *current_row;
	MEM_ROOT0570 field_alloc;
	unsigned field_count;
	unsigned current_field;
	System::Byte eof;
	System::Byte unbuffered_fetch_cancelled;
	void *extension;
};


typedef MYSQL_RES0510 *PMYSQL_RES0510;

struct DECLSPEC_DRECORD MYSQL_RES0510
{
public:
	unsigned __int64 row_count;
	MYSQL_FIELD0510 *fields;
	MYSQL_DATA0510 *data;
	MYSQL_ROWS0410 *data_cursor;
#ifndef __x86_64__
	int *lengths;
#else /* __x86_64__ */
	long *lengths;
#endif /* __x86_64__ */
	MYSQL0510 *handle;
	MYSQL_METHODS0510 *methods;
	System::PByte *row;
	System::PByte *current_row;
	MEM_ROOT0410 field_alloc;
	unsigned field_count;
	unsigned current_field;
	System::Byte eof;
	System::Byte unbuffered_fetch_cancelled;
	void *extension;
};


typedef MYSQL_RES0410 *PMYSQL_RES0410;

struct DECLSPEC_DRECORD MYSQL_RES0410
{
public:
	unsigned __int64 row_count;
	void *fields;
	void *data;
	void *data_cursor;
#ifndef __x86_64__
	int *lengths;
#else /* __x86_64__ */
	long *lengths;
#endif /* __x86_64__ */
	void *handle;
	MEM_ROOT0410 field_alloc;
	unsigned field_count;
	unsigned current_field;
	System::PByte *row;
	System::PByte *current_row;
	System::Byte eof;
	System::Byte unbuffered_fetch_cancelled;
	void *methods;
};


typedef MYSQL_RES0323 *PMYSQL_RES0323;

struct DECLSPEC_DRECORD MYSQL_RES0323
{
public:
	unsigned __int64 row_count;
	unsigned field_count;
	unsigned current_field;
	void *fields;
	void *data;
	void *data_cursor;
	MEM_ROOT0323 field_alloc;
	System::PByte *row;
	System::PByte *current_row;
#ifndef __x86_64__
	int *lengths;
#else /* __x86_64__ */
	long *lengths;
#endif /* __x86_64__ */
	void *handle;
	System::Byte eof;
};


typedef MYSQL_RES0320 *PMYSQL_RES0320;

struct DECLSPEC_DRECORD MYSQL_RES0320
{
public:
	unsigned __int64 row_count;
	unsigned field_count;
	unsigned current_field;
	void *fields;
	void *data;
	void *data_cursor;
	MEM_ROOT0320 field_alloc;
	System::PByte *row;
	System::PByte *current_row;
#ifndef __x86_64__
	int *lengths;
#else /* __x86_64__ */
	long *lengths;
#endif /* __x86_64__ */
	void *handle;
	System::Byte eof;
};


typedef int enum_field_types;

typedef int PREP_STMT_STATE0410;

typedef int PREP_STMT_STATE0411;

typedef int mysql_st_timestamp_type;

typedef int enum_mysql_timestamp_type;

typedef MYSQL_TIME0800 *PMYSQL_TIME0800;

struct DECLSPEC_DRECORD MYSQL_TIME0800
{
public:
	unsigned year;
	unsigned month;
	unsigned day;
	unsigned hour;
	unsigned minute;
	unsigned second;
#ifndef __x86_64__
	unsigned second_part;
#else /* __x86_64__ */
	unsigned long second_part;
#endif /* __x86_64__ */
	System::Byte neg;
	int time_type;
	int time_zone_displacement;
};


typedef MYSQL_TIME0506 *PMYSQL_TIME0506;

struct DECLSPEC_DRECORD MYSQL_TIME0506
{
public:
	unsigned year;
	unsigned month;
	unsigned day;
	unsigned hour;
	unsigned minute;
	unsigned second;
#ifndef __x86_64__
	unsigned second_part;
#else /* __x86_64__ */
	unsigned long second_part;
#endif /* __x86_64__ */
	System::Byte neg;
	int time_type;
};


typedef MYSQL_TIME0410 *PMYSQL_TIME0410;

struct DECLSPEC_DRECORD MYSQL_TIME0410
{
public:
	unsigned year;
	unsigned month;
	unsigned day;
	unsigned hour;
	unsigned minute;
	unsigned second;
#ifndef __x86_64__
	unsigned second_part;
#else /* __x86_64__ */
	unsigned long second_part;
#endif /* __x86_64__ */
	System::Byte neg;
	int time_type;
};


typedef void __cdecl (*TMYSQL_BIND_store_param_func)(void * net, void * param);

typedef void __cdecl (*TMYSQL_BIND_fetch_result)(void * p1, PPByte row);

typedef void __cdecl (*TMYSQL_BIND_skip_result)(void * p1, void * p2, PPByte row);

typedef MYSQL_BIND0510 *PMYSQL_BIND0510;

struct DECLSPEC_DRECORD MYSQL_BIND0510
{
public:
#ifndef __x86_64__
	unsigned *length;
#else /* __x86_64__ */
	unsigned long *length;
#endif /* __x86_64__ */
	System::Byte *is_null;
	System::Byte *buffer;
	System::Byte *error;
	System::Byte *row_ptr;
	TMYSQL_BIND_store_param_func store_param_func;
	TMYSQL_BIND_fetch_result fetch_result;
	TMYSQL_BIND_skip_result skip_result;
#ifndef __x86_64__
	unsigned buffer_length;
	unsigned offset;
	unsigned length_value;
#else /* __x86_64__ */
	unsigned long buffer_length;
	unsigned long offset;
	unsigned long length_value;
#endif /* __x86_64__ */
	unsigned param_number;
	unsigned pack_length;
	int buffer_type;
	System::Byte error_value;
	System::Byte is_unsigned;
	System::Byte long_data_used;
	System::Byte is_null_value;
	void *extension;
};


typedef MYSQL_BIND0506 *PMYSQL_BIND0506;

struct DECLSPEC_DRECORD MYSQL_BIND0506
{
public:
#ifndef __x86_64__
	unsigned *length;
#else /* __x86_64__ */
	unsigned long *length;
#endif /* __x86_64__ */
	System::Byte *is_null;
	System::Byte *buffer;
	System::Byte *error;
	int buffer_type;
#ifndef __x86_64__
	unsigned buffer_length;
#else /* __x86_64__ */
	unsigned long buffer_length;
#endif /* __x86_64__ */
	System::Byte *row_ptr;
#ifndef __x86_64__
	unsigned offset;
	unsigned length_value;
#else /* __x86_64__ */
	unsigned long offset;
	unsigned long length_value;
#endif /* __x86_64__ */
	unsigned param_number;
	unsigned pack_length;
	System::Byte error_value;
	System::Byte is_unsigned;
	System::Byte long_data_used;
	System::Byte is_null_value;
	TMYSQL_BIND_store_param_func store_param_func;
	TMYSQL_BIND_fetch_result fetch_result;
	TMYSQL_BIND_skip_result skip_result;
};


typedef MYSQL_BIND0411 *PMYSQL_BIND0411;

struct DECLSPEC_DRECORD MYSQL_BIND0411
{
public:
#ifndef __x86_64__
	unsigned *length;
#else /* __x86_64__ */
	unsigned long *length;
#endif /* __x86_64__ */
	System::Byte *is_null;
	System::Byte *buffer;
	int buffer_type;
#ifndef __x86_64__
	unsigned buffer_length;
#else /* __x86_64__ */
	unsigned long buffer_length;
#endif /* __x86_64__ */
	System::Byte *inter_buffer;
#ifndef __x86_64__
	unsigned offset;
	unsigned internal_length;
#else /* __x86_64__ */
	unsigned long offset;
	unsigned long internal_length;
#endif /* __x86_64__ */
	unsigned param_number;
	unsigned pack_length;
	System::Byte is_unsigned;
	System::Byte long_data_used;
	System::Byte internal_is_null;
	TMYSQL_BIND_store_param_func store_param_func;
	TMYSQL_BIND_fetch_result fetch_result;
	TMYSQL_BIND_skip_result skip_result;
};


typedef MYSQL_BIND0410 *PMYSQL_BIND0410;

struct DECLSPEC_DRECORD MYSQL_BIND0410
{
public:
#ifndef __x86_64__
	unsigned *length;
#else /* __x86_64__ */
	unsigned long *length;
#endif /* __x86_64__ */
	System::Byte *is_null;
	System::Byte *buffer;
	int buffer_type;
	unsigned buffer_length;
	unsigned param_number;
	System::Byte long_data_used;
};


typedef int __fastcall (*TMYSQL_STMT_read_row_func)(void * stmt, System::PPWideChar row);

typedef MYSQL_STMT0600 *PMYSQL_STMT0600;

struct DECLSPEC_DRECORD MYSQL_STMT0600
{
public:
	MEM_ROOT0600 mem_root;
	MYSQL_LIST list;
	MYSQL0600 *mysql;
	MYSQL_BIND0510 *params;
	MYSQL_BIND0510 *bind;
	MYSQL_FIELD0510 *fields;
	MYSQL_RES0600 *result;
	MYSQL_ROWS0410 *data_cursor;
	TMYSQL_STMT_read_row_func read_row_func;
	unsigned __int64 affected_rows;
	unsigned __int64 insert_id;
#ifndef __x86_64__
	unsigned stmt_id;
	unsigned flags;
	unsigned prefetch_rows;
#else /* __x86_64__ */
	unsigned long stmt_id;
	unsigned long flags;
	unsigned long prefetch_rows;
#endif /* __x86_64__ */
	unsigned server_status;
	unsigned last_errno;
	unsigned param_count;
	unsigned field_count;
	int state;
	System::StaticArray<char, 512> last_error;
	System::StaticArray<char, 6> sqlstate;
	System::Byte send_types_to_server;
	System::Byte bind_param_done;
	System::Byte bind_result_done;
	System::Byte unbuffered_fetch_cancelled;
	System::Byte update_max_length;
	void *extension;
};


typedef MYSQL_STMT0570 *PMYSQL_STMT0570;

struct DECLSPEC_DRECORD MYSQL_STMT0570
{
public:
	MEM_ROOT0570 mem_root;
	MYSQL_LIST list;
	MYSQL0570 *mysql;
	MYSQL_BIND0510 *params;
	MYSQL_BIND0510 *bind;
	MYSQL_FIELD0510 *fields;
	MYSQL_RES0570 *result;
	MYSQL_ROWS0410 *data_cursor;
	TMYSQL_STMT_read_row_func read_row_func;
	unsigned __int64 affected_rows;
	unsigned __int64 insert_id;
#ifndef __x86_64__
	unsigned stmt_id;
	unsigned flags;
	unsigned prefetch_rows;
#else /* __x86_64__ */
	unsigned long stmt_id;
	unsigned long flags;
	unsigned long prefetch_rows;
#endif /* __x86_64__ */
	unsigned server_status;
	unsigned last_errno;
	unsigned param_count;
	unsigned field_count;
	int state;
	System::StaticArray<char, 512> last_error;
	System::StaticArray<char, 6> sqlstate;
	System::Byte send_types_to_server;
	System::Byte bind_param_done;
	System::Byte bind_result_done;
	System::Byte unbuffered_fetch_cancelled;
	System::Byte update_max_length;
	void *extension;
};


typedef MYSQL_STMT0510 *PMYSQL_STMT0510;

struct DECLSPEC_DRECORD MYSQL_STMT0510
{
public:
	MEM_ROOT0410 mem_root;
	MYSQL_LIST list;
	MYSQL0510 *mysql;
	MYSQL_BIND0510 *params;
	MYSQL_BIND0510 *bind;
	MYSQL_FIELD0510 *fields;
	MYSQL_RES0510 *result;
	MYSQL_ROWS0410 *data_cursor;
	TMYSQL_STMT_read_row_func read_row_func;
	unsigned __int64 affected_rows;
	unsigned __int64 insert_id;
#ifndef __x86_64__
	unsigned stmt_id;
	unsigned flags;
	unsigned prefetch_rows;
#else /* __x86_64__ */
	unsigned long stmt_id;
	unsigned long flags;
	unsigned long prefetch_rows;
#endif /* __x86_64__ */
	unsigned server_status;
	unsigned last_errno;
	unsigned param_count;
	unsigned field_count;
	int state;
	System::StaticArray<char, 512> last_error;
	System::StaticArray<char, 6> sqlstate;
	System::Byte send_types_to_server;
	System::Byte bind_param_done;
	System::Byte bind_result_done;
	System::Byte unbuffered_fetch_cancelled;
	System::Byte update_max_length;
	void *extension;
};


typedef MYSQL_STMT0506 *PMYSQL_STMT0506;

struct DECLSPEC_DRECORD MYSQL_STMT0506
{
public:
	MEM_ROOT0410 mem_root;
	MYSQL_LIST list;
	void *mysql;
	void *params;
	void *bind;
	void *fields;
	void *result;
	void *data_cursor;
	unsigned __int64 affected_rows;
	unsigned __int64 insert_id;
	TMYSQL_STMT_read_row_func read_row_func;
#ifndef __x86_64__
	unsigned stmt_id;
	unsigned flags;
	unsigned prefetch_rows;
#else /* __x86_64__ */
	unsigned long stmt_id;
	unsigned long flags;
	unsigned long prefetch_rows;
#endif /* __x86_64__ */
	unsigned server_status;
	unsigned last_errno;
	unsigned param_count;
	unsigned field_count;
	int state;
	System::StaticArray<char, 512> last_error;
	System::StaticArray<char, 6> sqlstate;
	System::Byte send_types_to_server;
	System::Byte bind_param_done;
	System::Byte bind_result_done;
	System::Byte unbuffered_fetch_cancelled;
	System::Byte update_max_length;
};


typedef MYSQL_STMT0411 *PMYSQL_STMT0411;

struct DECLSPEC_DRECORD MYSQL_STMT0411
{
public:
	MEM_ROOT0410 mem_root;
	MYSQL_LIST list;
	void *mysql;
	void *params;
	void *bind;
	void *fields;
	void *result;
	void *data_cursor;
	unsigned __int64 affected_rows;
	unsigned __int64 insert_id;
	TMYSQL_STMT_read_row_func read_row_func;
#ifndef __x86_64__
	unsigned stmt_id;
#else /* __x86_64__ */
	unsigned long stmt_id;
#endif /* __x86_64__ */
	unsigned last_errno;
	unsigned param_count;
	unsigned field_count;
	int state;
	System::StaticArray<char, 200> last_error;
	System::StaticArray<char, 6> sqlstate;
	System::Byte send_types_to_server;
	System::Byte bind_param_done;
	System::Byte bind_result_done;
	System::Byte unbuffered_fetch_cancelled;
	System::Byte update_max_length;
};


typedef MYSQL_STMT0410 *PMYSQL_STMT0410;

struct DECLSPEC_DRECORD MYSQL_STMT0410
{
public:
	void *mysql;
	void *params;
	void *result;
	void *bind;
	void *fields;
	MYSQL_LIST list;
	System::Byte *query;
	MEM_ROOT0323 mem_root;
	unsigned param_count;
	unsigned field_count;
#ifndef __x86_64__
	unsigned stmt_id;
#else /* __x86_64__ */
	unsigned long stmt_id;
#endif /* __x86_64__ */
	unsigned last_errno;
	int state;
	System::StaticArray<char, 200> last_error;
	System::Byte long_alloced;
	System::Byte send_types_to_server;
	System::Byte param_buffers;
	System::Byte res_buffers;
	System::Byte result_buffered;
};


typedef int enum_stmt_attr_type;

typedef unsigned __int64 __cdecl (*TPrcmysql_num_rows)(void * res);

typedef unsigned __cdecl (*TPrcmysql_num_fields)(void * res);

typedef System::Byte __cdecl (*TPrcmysql_eof)(void * res);

typedef void * __cdecl (*TPrcmysql_fetch_field_direct)(void * res, int fieldnr);

typedef void * __cdecl (*TPrcmysql_fetch_fields)(void * res);

typedef void * __cdecl (*TPrcmysql_row_tell)(void * res);

typedef unsigned __cdecl (*TPrcmysql_field_tell)(void * res);

typedef unsigned __cdecl (*TPrcmysql_field_count)(void * mysql);

typedef unsigned __int64 __cdecl (*TPrcmysql_affected_rows)(void * mysql);

typedef unsigned __int64 __cdecl (*TPrcmysql_insert_id)(void * mysql);

typedef unsigned __cdecl (*TPrcmysql_errno)(void * mysql);

typedef char * __cdecl (*TPrcmysql_error)(void * mysql);

typedef char * __cdecl (*TPrcmysql_sqlstate)(void * mysql);

typedef char * __cdecl (*TPrcmysql_info)(void * mysql);

#ifndef __x86_64__
typedef unsigned __cdecl (*TPrcmysql_thread_id)(void * mysql);
#else /* __x86_64__ */
typedef unsigned long __cdecl (*TPrcmysql_thread_id)(void * mysql);
#endif /* __x86_64__ */

typedef char * __cdecl (*TPrcmysql_character_set_name)(void * mysql);

typedef void __cdecl (*TPrcmysql_get_character_set_info)(void * mysql, MY_CHARSET_INFO &charset);

typedef int __cdecl (*TPrcmysql_set_character_set)(void * mysql, char * cs_name);

typedef unsigned __cdecl (*TPrcmysql_warning_count)(void * mysql);

typedef void * __cdecl (*TPrcmysql_init)(void * mysql);

typedef System::Byte __cdecl (*TPrcmysql_ssl_set)(void * mysql, const char * key, const char * cert, const char * ca, const char * capath, const char * cipher);

typedef char * __cdecl (*TPrcmysql_get_ssl_cipher)(void * mysql);

typedef System::Byte __cdecl (*TPrcmysql_change_user)(void * mysql, const char * user, const char * passwd, const char * db);

#ifndef __x86_64__
typedef void * __cdecl (*TPrcmysql_real_connect)(void * mysql, const char * host, const char * user, const char * passwd, const char * db, unsigned port, const char * unix_socket, unsigned clientflag);
#else /* __x86_64__ */
typedef void * __cdecl (*TPrcmysql_real_connect)(void * mysql, const char * host, const char * user, const char * passwd, const char * db, unsigned port, const char * unix_socket, unsigned long clientflag);
#endif /* __x86_64__ */

typedef void __cdecl (*TPrcmysql_close)(void * sock);

typedef int __cdecl (*TPrcmysql_select_db)(void * mysql, const char * db);

typedef int __cdecl (*TPrcmysql_query)(void * mysql, const char * q);

#ifndef __x86_64__
typedef int __cdecl (*TPrcmysql_send_query)(void * mysql, const char * q, unsigned length);
#else /* __x86_64__ */
typedef int __cdecl (*TPrcmysql_send_query)(void * mysql, const char * q, unsigned long length);
#endif /* __x86_64__ */

typedef int __cdecl (*TPrcmysql_read_query_result)(void * mysql);

#ifndef __x86_64__
typedef int __cdecl (*TPrcmysql_real_query)(void * mysql, const char * q, unsigned length);
#else /* __x86_64__ */
typedef int __cdecl (*TPrcmysql_real_query)(void * mysql, const char * q, unsigned long length);
#endif /* __x86_64__ */

typedef int __cdecl (*TPrcmysql_shutdown)(void * mysql);

typedef int __cdecl (*TPrcmysql_dump_debug_info)(void * mysql);

typedef int __cdecl (*TPrcmysql_refresh)(void * mysql, unsigned refresh_options);

#ifndef __x86_64__
typedef int __cdecl (*TPrcmysql_kill)(void * mysql, unsigned pid);
#else /* __x86_64__ */
typedef int __cdecl (*TPrcmysql_kill)(void * mysql, unsigned long pid);
#endif /* __x86_64__ */

typedef int __cdecl (*TPrcmysql_ping)(void * mysql);

typedef char * __cdecl (*TPrcmysql_stat)(void * mysql);

typedef char * __cdecl (*TPrcmysql_get_server_info)(void * mysql);

typedef char * __cdecl (*TPrcmysql_get_client_info)(void);

typedef char * __cdecl (*TPrcmysql_get_host_info)(void * mysql);

typedef int __cdecl (*TPrcmysql_get_proto_info)(void * mysql);

typedef void * __cdecl (*TPrcmysql_list_dbs)(void * mysql, const char * wild);

typedef void * __cdecl (*TPrcmysql_list_tables)(void * mysql, const char * wild);

typedef void * __cdecl (*TPrcmysql_list_fields)(void * mysql, const char * table, const char * wild);

typedef void * __cdecl (*TPrcmysql_list_processes)(void * mysql);

typedef void * __cdecl (*TPrcmysql_store_result)(void * mysql);

typedef void * __cdecl (*TPrcmysql_use_result)(void * mysql);

typedef int __cdecl (*TPrcmysql_options)(void * mysql, int option, const System::PByte arg);

typedef void __cdecl (*TPrcmysql_free_result)(void * res);

#ifndef __x86_64__
typedef void __cdecl (*TPrcmysql_data_seek0320)(void * res, unsigned offset);
#else /* __x86_64__ */
typedef void __cdecl (*TPrcmysql_data_seek0320)(void * res, unsigned long offset);
#endif /* __x86_64__ */

typedef void __cdecl (*TPrcmysql_data_seek0323)(void * res, unsigned __int64 offset);

typedef void * __cdecl (*TPrcmysql_row_seek)(void * res, void * Row);

typedef unsigned __cdecl (*TPrcmysql_field_seek)(void * res, unsigned offset);

typedef PPByte __cdecl (*TPrcmysql_fetch_row)(void * res);

typedef Pmy_ulong __cdecl (*TPrcmysql_fetch_lengths)(void * res);

typedef void * __cdecl (*TPrcmysql_fetch_field)(void * res);

#ifndef __x86_64__
typedef unsigned __cdecl (*TPrcmysql_escape_string)(char * szTo, const char * szFrom, unsigned from_length);
#else /* __x86_64__ */
typedef unsigned long __cdecl (*TPrcmysql_escape_string)(char * szTo, const char * szFrom, unsigned long from_length);
#endif /* __x86_64__ */

#ifndef __x86_64__
typedef unsigned __cdecl (*TPrcmysql_real_escape_string)(void * mysql, char * szTo, const char * szFrom, unsigned length);
#else /* __x86_64__ */
typedef unsigned long __cdecl (*TPrcmysql_real_escape_string)(void * mysql, char * szTo, const char * szFrom, unsigned long length);
#endif /* __x86_64__ */

typedef void __cdecl (*TPrcmysql_debug)(const char * debug);

typedef void __cdecl (*TPrcmyodbc_remove_escape)(void * mysql, char * name);

typedef int __cdecl (*TPrcmysql_thread_safe)(void);

typedef void * __cdecl (*TPrcmysql_connect)(void * mysql, const char * host, const char * user, const char * passwd);

typedef int __cdecl (*TPrcmysql_create_db)(void * mysql, const char * DB);

typedef int __cdecl (*TPrcmysql_drop_db)(void * mysql, const char * DB);

typedef System::Byte __cdecl (*TPrcmysql_autocommit)(void * mysql, System::Byte mode);

typedef System::Byte __cdecl (*TPrcmysql_commit)(void * mysql);

typedef System::Byte __cdecl (*TPrcmysql_rollback)(void * mysql);

typedef System::Byte __cdecl (*TPrcmysql_more_results)(void * mysql);

typedef int __cdecl (*TPrcmysql_next_result)(void * mysql);

typedef void * __cdecl (*TPrcmysql_stmt_init)(void * mysql);

#ifndef __x86_64__
typedef int __cdecl (*TPrcmysql_stmt_prepare)(void * stmt, const char * query, unsigned length);
#else /* __x86_64__ */
typedef int __cdecl (*TPrcmysql_stmt_prepare)(void * stmt, const char * query, unsigned long length);
#endif /* __x86_64__ */

typedef int __cdecl (*TPrcmysql_stmt_execute)(void * stmt);

typedef int __cdecl (*TPrcmysql_stmt_fetch)(void * stmt);

#ifndef __x86_64__
typedef int __cdecl (*TPrcmysql_stmt_fetch_column)(void * stmt, void * bind, unsigned column, unsigned offset);
#else /* __x86_64__ */
typedef int __cdecl (*TPrcmysql_stmt_fetch_column)(void * stmt, void * bind, unsigned column, unsigned long offset);
#endif /* __x86_64__ */

typedef int __cdecl (*TPrcmysql_stmt_store_result)(void * stmt);

#ifndef __x86_64__
typedef unsigned __cdecl (*TPrcmysql_stmt_param_count)(void * stmt);
#else /* __x86_64__ */
typedef unsigned long __cdecl (*TPrcmysql_stmt_param_count)(void * stmt);
#endif /* __x86_64__ */

typedef System::Byte __cdecl (*TPrcmysql_stmt_attr_set)(void * stmt, int attr_type, void * attr);

typedef System::Byte __cdecl (*TPrcmysql_stmt_attr_get)(void * stmt, int attr_type, void * attr);

typedef System::Byte __cdecl (*TPrcmysql_stmt_bind_param)(void * stmt, void * bnd);

typedef System::Byte __cdecl (*TPrcmysql_stmt_bind_result)(void * stmt, void * bnd);

typedef System::Byte __cdecl (*TPrcmysql_stmt_close)(void * stmt);

typedef System::Byte __cdecl (*TPrcmysql_stmt_reset)(void * stmt);

typedef System::Byte __cdecl (*TPrcmysql_stmt_free_result)(void * stmt);

#ifndef __x86_64__
typedef System::Byte __cdecl (*TPrcmysql_stmt_send_long_data)(void * stmt, unsigned param_number, const System::PByte data, unsigned length);
#else /* __x86_64__ */
typedef System::Byte __cdecl (*TPrcmysql_stmt_send_long_data)(void * stmt, unsigned param_number, const System::PByte data, unsigned long length);
#endif /* __x86_64__ */

typedef void * __cdecl (*TPrcmysql_stmt_result_metadata)(void * stmt);

typedef unsigned __cdecl (*TPrcmysql_stmt_errno)(void * stmt);

typedef char * __cdecl (*TPrcmysql_stmt_error)(void * stmt);

typedef char * __cdecl (*TPrcmysql_stmt_sqlstate)(void * stmt);

typedef void * __cdecl (*TPrcmysql_stmt_row_seek)(void * stmt, void * offset);

typedef void * __cdecl (*TPrcmysql_stmt_row_tell)(void * stmt);

typedef void __cdecl (*TPrcmysql_stmt_data_seek)(void * stmt, unsigned __int64 offset);

typedef unsigned __int64 __cdecl (*TPrcmysql_stmt_num_rows)(void * stmt);

typedef unsigned __int64 __cdecl (*TPrcmysql_stmt_affected_rows)(void * stmt);

typedef unsigned __int64 __cdecl (*TPrcmysql_stmt_insert_id)(void * stmt);

typedef unsigned __cdecl (*TPrcmysql_stmt_field_count)(void * stmt);

typedef int __cdecl (*TPrcmysql_stmt_next_result)(void * stmt);

typedef int __cdecl (*TPrcmysql_server_init)(int argc, my_ppchar argv, my_ppchar groups);

typedef void __cdecl (*TPrcmysql_server_end)(void);

typedef System::Byte __cdecl (*TPrcmysql_thread_init)(void);

typedef void __cdecl (*TPrcmysql_thread_end)(void);

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 NAME_LEN = System::Int8(0x40);
static const System::Int8 HOSTNAME_LEN = System::Int8(0x3c);
static const System::Int8 USERNAME_LEN = System::Int8(0x10);
static const System::Int8 SERVER_VERSION_LEN = System::Int8(0x3c);
static const System::Int8 SQLSTATE_LEN = System::Int8(0x5);
#define LOCAL_HOST u"localhost"
static const System::WideChar LOCAL_HOST_NAMEDPIPE = (System::WideChar)(0x2e);
static const System::Word MYSQL_PORT = System::Word(0xcea);
#define MYSQL_UNIX_ADDR u"/tmp/mysql.sock"
#define MYSQL_NAMEDPIPE u"MySQL"
#define MYSQL_SERVICENAME u"MySql"
static const System::Int8 COM_SLEEP = System::Int8(0x0);
static const System::Int8 COM_QUIT = System::Int8(0x1);
static const System::Int8 COM_INIT_DB = System::Int8(0x2);
static const System::Int8 COM_QUERY = System::Int8(0x3);
static const System::Int8 COM_FIELD_LIST = System::Int8(0x4);
static const System::Int8 COM_CREATE_DB = System::Int8(0x5);
static const System::Int8 COM_DROP_DB = System::Int8(0x6);
static const System::Int8 COM_REFRESH = System::Int8(0x7);
static const System::Int8 COM_SHUTDOWN = System::Int8(0x8);
static const System::Int8 COM_STATISTICS = System::Int8(0x9);
static const System::Int8 COM_PROCESS_INFO = System::Int8(0xa);
static const System::Int8 COM_CONNECT = System::Int8(0xb);
static const System::Int8 COM_PROCESS_KILL = System::Int8(0xc);
static const System::Int8 COM_DEBUG = System::Int8(0xd);
static const System::Int8 COM_PING = System::Int8(0xe);
static const System::Int8 COM_TIME = System::Int8(0xf);
static const System::Int8 COM_DELAYED_INSERT = System::Int8(0x10);
static const System::Int8 COM_CHANGE_USER = System::Int8(0x11);
static const System::Int8 COM_BINLOG_DUMP = System::Int8(0x12);
static const System::Int8 COM_TABLE_DUMP = System::Int8(0x13);
static const System::Int8 COM_CONNECT_OUT = System::Int8(0x14);
static const System::Int8 COM_REGISTER_SLAVE = System::Int8(0x15);
static const System::Int8 COM_STMT_PREPARE = System::Int8(0x16);
static const System::Int8 COM_STMT_EXECUTE = System::Int8(0x17);
static const System::Int8 COM_STMT_SEND_LONG_DATA = System::Int8(0x18);
static const System::Int8 COM_STMT_CLOSE = System::Int8(0x19);
static const System::Int8 COM_STMT_RESET = System::Int8(0x1a);
static const System::Int8 COM_SET_OPTION = System::Int8(0x1b);
static const System::Int8 COM_STMT_FETCH = System::Int8(0x1c);
static const System::Int8 COM_DAEMON = System::Int8(0x1d);
static const System::Int8 COM_BINLOG_DUMP_GTID = System::Int8(0x1e);
static const System::Int8 COM_RESET_CONNECTION = System::Int8(0x1f);
static const System::Int8 COM_CLONE = System::Int8(0x20);
static const System::Int8 COM_END = System::Int8(0x21);
static const System::Int8 SCRAMBLE_LENGTH = System::Int8(0x14);
static const System::Int8 SCRAMBLE_LENGTH_323 = System::Int8(0x8);
static const System::Int8 NOT_NULL_FLAG = System::Int8(0x1);
static const System::Int8 PRI_KEY_FLAG = System::Int8(0x2);
static const System::Int8 UNIQUE_KEY_FLAG = System::Int8(0x4);
static const System::Int8 MULTIPLE_KEY_FLAG = System::Int8(0x8);
static const System::Int8 BLOB_FLAG = System::Int8(0x10);
static const System::Int8 UNSIGNED_FLAG = System::Int8(0x20);
static const System::Int8 ZEROFILL_FLAG = System::Int8(0x40);
static const System::Byte BINARY_FLAG = System::Byte(0x80);
static const System::Word ENUM_FLAG = System::Word(0x100);
static const System::Word AUTO_INCREMENT_FLAG = System::Word(0x200);
static const System::Word TIMESTAMP_FLAG = System::Word(0x400);
static const System::Word SET_FLAG = System::Word(0x800);
static const System::Word NO_DEFAULT_VALUE_FLAG = System::Word(0x1000);
static const System::Word ON_UPDATE_NOW_FLAG = System::Word(0x2000);
static const System::Word NUM_FLAG = System::Word(0x8000);
static const System::Word PART_KEY_FLAG = System::Word(0x4000);
static const System::Word GROUP_FLAG = System::Word(0x8000);
static const int UNIQUE_FLAG = int(0x10000);
static const int BINCMP_FLAG = int(0x20000);
static const int GET_FIXED_FIELDS_FLAG = int(0x40000);
static const int FIELD_IN_PART_FUNC_FLAG = int(0x80000);
static const int FIELD_IN_ADD_INDEX = int(0x100000);
static const int FIELD_IS_RENAMED = int(0x200000);
static const System::Int8 FIELD_FLAGS_STORAGE_MEDIA = System::Int8(0x16);
static const int FIELD_FLAGS_STORAGE_MEDIA_MASK = int(0xc00000);
static const System::Int8 FIELD_FLAGS_COLUMN_FORMAT = System::Int8(0x18);
static const int FIELD_FLAGS_COLUMN_FORMAT_MASK = int(0x3000000);
static const int FIELD_IS_DROPPED = int(0x4000000);
static const int EXPLICIT_NULL_FLAG = int(0x8000000);
static const int FIELD_IS_MARKED = int(0x10000000);
static const int NOT_SECONDARY_FLAG = int(0x20000000);
static const System::Int8 REFRESH_GRANT = System::Int8(0x1);
static const System::Int8 REFRESH_LOG = System::Int8(0x2);
static const System::Int8 REFRESH_TABLES = System::Int8(0x4);
static const System::Int8 REFRESH_HOSTS = System::Int8(0x8);
static const System::Int8 REFRESH_STATUS = System::Int8(0x10);
static const System::Int8 REFRESH_THREADS = System::Int8(0x20);
static const System::Int8 REFRESH_SLAVE = System::Int8(0x40);
static const System::Byte REFRESH_MASTER = System::Byte(0x80);
static const System::Word REFRESH_READ_LOCK = System::Word(0x4000);
static const System::Word REFRESH_FAST = System::Word(0x8000);
static const int REFRESH_QUERY_CACHE = int(0x10000);
static const int REFRESH_QUERY_CACHE_FREE = int(0x20000);
static const int REFRESH_DES_KEY_FILE = int(0x40000);
static const int REFRESH_USER_RESOURCES = int(0x80000);
static const System::Int8 CLIENT_LONG_PASSWORD = System::Int8(0x1);
static const System::Int8 CLIENT_FOUND_ROWS = System::Int8(0x2);
static const System::Int8 CLIENT_LONG_FLAG = System::Int8(0x4);
static const System::Int8 CLIENT_CONNECT_WITH_DB = System::Int8(0x8);
static const System::Int8 CLIENT_NO_SCHEMA = System::Int8(0x10);
static const System::Int8 CLIENT_COMPRESS = System::Int8(0x20);
static const System::Int8 CLIENT_ODBC = System::Int8(0x40);
static const System::Byte CLIENT_LOCAL_FILES = System::Byte(0x80);
static const System::Word CLIENT_IGNORE_SPACE = System::Word(0x100);
static const System::Word CLIENT_CHANGE_USER = System::Word(0x200);
static const System::Word FD_50_CLIENT_PROTOCOL_41 = System::Word(0x200);
static const System::Word CLIENT_INTERACTIVE = System::Word(0x400);
static const System::Word CLIENT_SSL = System::Word(0x800);
static const System::Word CLIENT_IGNORE_SIGPIPE = System::Word(0x1000);
static const System::Word CLIENT_TRANSACTIONS = System::Word(0x2000);
static const System::Word CLIENT_PROTOCOL_41 = System::Word(0x4000);
static const System::Word FD_50_CLIENT_RESERVED = System::Word(0x4000);
static const System::Word CLIENT_SECURE_CONNECTION = System::Word(0x8000);
static const int CLIENT_MULTI_STATEMENTS = int(0x10000);
static const int CLIENT_MULTI_QUERIES = int(0x10000);
static const int CLIENT_MULTI_RESULTS = int(0x20000);
static const int CLIENT_PS_MULTI_RESULTS = int(0x40000);
static const int CLIENT_PLUGIN_AUTH = int(0x80000);
static const int CLIENT_CONNECT_ATTRS = int(0x100000);
static const int CLIENT_PLUGIN_AUTH_LENENC_CLIENT_DATA = int(0x200000);
static const int CLIENT_CAN_HANDLE_EXPIRED_PASSWORDS = int(0x400000);
static const int CLIENT_SSL_VERIFY_SERVER_CERT = int(0x40000000);
static const int CLIENT_REMEMBER_OPTIONS = int(-2147483648);
static const System::Int8 SERVER_STATUS_IN_TRANS = System::Int8(0x1);
static const System::Int8 SERVER_STATUS_AUTOCOMMIT = System::Int8(0x2);
static const System::Int8 SERVER_STATUS_MORE_RESULTS = System::Int8(0x4);
static const System::Int8 SERVER_MORE_RESULTS_EXISTS = System::Int8(0x8);
static const System::Int8 SERVER_QUERY_NO_GOOD_INDEX_USED = System::Int8(0x10);
static const System::Int8 SERVER_QUERY_NO_INDEX_USED = System::Int8(0x20);
static const System::Int8 SERVER_STATUS_CURSOR_EXISTS = System::Int8(0x40);
static const System::Byte SERVER_STATUS_LAST_ROW_SENT = System::Byte(0x80);
static const System::Word SERVER_STATUS_DB_DROPPED = System::Word(0x100);
static const System::Word SERVER_STATUS_NO_BACKSLASH_ESCAPES = System::Word(0x200);
static const System::Word SERVER_STATUS_METADATA_CHANGED = System::Word(0x400);
static const System::Word SERVER_QUERY_WAS_SLOW = System::Word(0x800);
static const System::Word SERVER_PS_OUT_PARAMS = System::Word(0x1000);
static const System::Word SERVER_STATUS_IN_TRANS_READONLY = System::Word(0x2000);
static const System::Byte MYSQL_ERRMSG_SIZE_0300 = System::Byte(0xc8);
static const System::Word MYSQL_ERRMSG_SIZE_0500 = System::Word(0x200);
static const System::Int8 NET_READ_TIMEOUT = System::Int8(0x1e);
static const System::Int8 NET_WRITE_TIMEOUT = System::Int8(0x3c);
static const System::Word NET_WAIT_TIMEOUT = System::Word(0x7080);
static const System::Int8 ONLY_KILL_QUERY = System::Int8(0x1);
extern DELPHI_PACKAGE unsigned __int64 MYSQL_COUNT_ERROR;
static const System::Int8 MYSQL_OPT_CONNECT_TIMEOUT = System::Int8(0x0);
static const System::Int8 MYSQL_OPT_COMPRESS = System::Int8(0x1);
static const System::Int8 MYSQL_OPT_NAMED_PIPE = System::Int8(0x2);
static const System::Int8 MYSQL_INIT_COMMAND = System::Int8(0x3);
static const System::Int8 MYSQL_READ_DEFAULT_FILE = System::Int8(0x4);
static const System::Int8 MYSQL_READ_DEFAULT_GROUP = System::Int8(0x5);
static const System::Int8 MYSQL_SET_CHARSET_DIR = System::Int8(0x6);
static const System::Int8 MYSQL_SET_CHARSET_NAME = System::Int8(0x7);
static const System::Int8 MYSQL_OPT_LOCAL_INFILE = System::Int8(0x8);
static const System::Int8 MYSQL_OPT_PROTOCOL = System::Int8(0x9);
static const System::Int8 MYSQL_SHARED_MEMORY_BASE_NAME = System::Int8(0xa);
static const System::Int8 MYSQL_OPT_READ_TIMEOUT = System::Int8(0xb);
static const System::Int8 MYSQL_OPT_WRITE_TIMEOUT = System::Int8(0xc);
static const System::Int8 MYSQL_OPT_USE_RESULT = System::Int8(0xd);
static const System::Int8 MYSQL_OPT_USE_REMOTE_CONNECTION = System::Int8(0xe);
static const System::Int8 MYSQL_OPT_USE_EMBEDDED_CONNECTION = System::Int8(0xf);
static const System::Int8 MYSQL_OPT_GUESS_CONNECTION = System::Int8(0x10);
static const System::Int8 MYSQL_SET_CLIENT_IP = System::Int8(0x11);
static const System::Int8 MYSQL_SECURE_AUTH = System::Int8(0x12);
static const System::Int8 MYSQL_REPORT_DATA_TRUNCATION_ = System::Int8(0x13);
static const System::Int8 MYSQL_OPT_RECONNECT_ = System::Int8(0x14);
static const System::Int8 MYSQL_OPT_SSL_VERIFY_SERVER_CERT = System::Int8(0x15);
static const System::Int8 MYSQL_REPORT_DATA_TRUNCATION = System::Int8(0xe);
static const System::Int8 MYSQL_OPT_RECONNECT = System::Int8(0xf);
static const System::Int8 MYSQL_PLUGIN_DIR = System::Int8(0x10);
static const System::Int8 MYSQL_DEFAULT_AUTH = System::Int8(0x11);
static const System::Int8 MYSQL_OPT_BIND = System::Int8(0x12);
static const System::Int8 MYSQL_OPT_SSL_KEY = System::Int8(0x13);
static const System::Int8 MYSQL_OPT_SSL_CERT = System::Int8(0x14);
static const System::Int8 MYSQL_OPT_SSL_CA = System::Int8(0x15);
static const System::Int8 MYSQL_OPT_SSL_CAPATH = System::Int8(0x16);
static const System::Int8 MYSQL_OPT_SSL_CIPHER = System::Int8(0x17);
static const System::Int8 MYSQL_OPT_SSL_CRL = System::Int8(0x18);
static const System::Int8 MYSQL_OPT_SSL_CRLPATH = System::Int8(0x19);
static const System::Int8 MYSQL_OPT_CONNECT_ATTR_RESET = System::Int8(0x1a);
static const System::Int8 MYSQL_OPT_CONNECT_ATTR_ADD = System::Int8(0x1b);
static const System::Int8 MYSQL_OPT_CONNECT_ATTR_DELETE = System::Int8(0x1c);
static const System::Int8 MYSQL_SERVER_PUBLIC_KEY = System::Int8(0x1d);
static const System::Int8 MYSQL_ENABLE_CLEARTEXT_PLUGIN = System::Int8(0x1e);
static const System::Int8 MYSQL_OPT_CAN_HANDLE_EXPIRED_PASSWORDS = System::Int8(0x1f);
static const System::Int8 MYSQL_OPT_MAX_ALLOWED_PACKET = System::Int8(0x20);
static const System::Int8 MYSQL_OPT_NET_BUFFER_LENGTH = System::Int8(0x21);
static const System::Int8 MYSQL_OPT_TLS_VERSION = System::Int8(0x22);
static const System::Int8 MYSQL_OPT_SSL_MODE = System::Int8(0x23);
static const System::Int8 MYSQL_OPT_GET_SERVER_PUBLIC_KEY = System::Int8(0x24);
static const System::Int8 MYSQL_OPT_RETRY_COUNT = System::Int8(0x25);
static const System::Int8 MYSQL_OPT_OPTIONAL_RESULTSET_METADATA = System::Int8(0x26);
static const System::Int8 MYSQL_OPT_SSL_FIPS_MODE = System::Int8(0x27);
static const System::Int8 MYSQL_OPT_TLS_CIPHERSUITES = System::Int8(0x28);
static const System::Int8 MYSQL_OPT_COMPRESSION_ALGORITHMS = System::Int8(0x29);
static const System::Int8 MYSQL_OPT_ZSTD_COMPRESSION_LEVEL = System::Int8(0x2a);
static const System::Int8 MYSQL_STATUS_READY = System::Int8(0x0);
static const System::Int8 MYSQL_STATUS_GET_RESULT = System::Int8(0x1);
static const System::Int8 MYSQL_STATUS_USE_RESULT = System::Int8(0x2);
static const System::Int8 MYSQL_STATUS_STATEMENT_GET_RESULT = System::Int8(0x3);
static const System::Int8 MYSQL_PROTOCOL_DEFAULT = System::Int8(0x0);
static const System::Int8 MYSQL_PROTOCOL_TCP = System::Int8(0x1);
static const System::Int8 MYSQL_PROTOCOL_SOCKET = System::Int8(0x2);
static const System::Int8 MYSQL_PROTOCOL_PIPE = System::Int8(0x3);
static const System::Int8 MYSQL_PROTOCOL_MEMORY = System::Int8(0x4);
static const System::Int8 SSL_MODE_DISABLED = System::Int8(0x1);
static const System::Int8 SSL_MODE_PREFERRED = System::Int8(0x2);
static const System::Int8 SSL_MODE_REQUIRED = System::Int8(0x3);
static const System::Int8 SSL_MODE_VERIFY_CA = System::Int8(0x4);
static const System::Int8 SSL_MODE_VERIFY_IDENTITY = System::Int8(0x5);
static const System::Int8 SSL_FIPS_MODE_OFF = System::Int8(0x0);
static const System::Int8 SSL_FIPS_MODE_ON = System::Int8(0x1);
static const System::Int8 SSL_FIPS_MODE_STRICT = System::Int8(0x2);
static const System::Int8 MYSQL_RPL_MASTER = System::Int8(0x0);
static const System::Int8 MYSQL_RPL_SLAVE = System::Int8(0x1);
static const System::Int8 MYSQL_RPL_ADMIN = System::Int8(0x2);
static const System::Int8 RESULTSET_METADATA_NONE = System::Int8(0x0);
static const System::Int8 RESULTSET_METADATA_FULL = System::Int8(0x1);
static const System::Int8 CURSOR_TYPE_NO_CURSOR = System::Int8(0x0);
static const System::Int8 CURSOR_TYPE_READ_ONLY = System::Int8(0x1);
static const System::Int8 CURSOR_TYPE_FOR_UPDATE = System::Int8(0x2);
static const System::Int8 CURSOR_TYPE_SCROLLABLE = System::Int8(0x4);
static const System::Int8 MYSQL_OPTION_MULTI_STATEMENTS_ON = System::Int8(0x0);
static const System::Int8 MYSQL_OPTION_MULTI_STATEMENTS_OFF = System::Int8(0x1);
static const System::Int8 MYSQL_TYPE_DECIMAL = System::Int8(0x0);
static const System::Int8 MYSQL_TYPE_TINY = System::Int8(0x1);
static const System::Int8 MYSQL_TYPE_SHORT = System::Int8(0x2);
static const System::Int8 MYSQL_TYPE_LONG = System::Int8(0x3);
static const System::Int8 MYSQL_TYPE_FLOAT = System::Int8(0x4);
static const System::Int8 MYSQL_TYPE_DOUBLE = System::Int8(0x5);
static const System::Int8 MYSQL_TYPE_NULL = System::Int8(0x6);
static const System::Int8 MYSQL_TYPE_TIMESTAMP = System::Int8(0x7);
static const System::Int8 MYSQL_TYPE_LONGLONG = System::Int8(0x8);
static const System::Int8 MYSQL_TYPE_INT24 = System::Int8(0x9);
static const System::Int8 MYSQL_TYPE_DATE = System::Int8(0xa);
static const System::Int8 MYSQL_TYPE_TIME = System::Int8(0xb);
static const System::Int8 MYSQL_TYPE_DATETIME = System::Int8(0xc);
static const System::Int8 MYSQL_TYPE_YEAR = System::Int8(0xd);
static const System::Int8 MYSQL_TYPE_NEWDATE = System::Int8(0xe);
static const System::Int8 MYSQL_TYPE_VARCHAR = System::Int8(0xf);
static const System::Int8 MYSQL_TYPE_BIT = System::Int8(0x10);
static const System::Byte MYSQL_TYPE_JSON = System::Byte(0xf5);
static const System::Byte MYSQL_TYPE_NEWDECIMAL = System::Byte(0xf6);
static const System::Byte MYSQL_TYPE_ENUM = System::Byte(0xf7);
static const System::Byte MYSQL_TYPE_SET = System::Byte(0xf8);
static const System::Byte MYSQL_TYPE_TINY_BLOB = System::Byte(0xf9);
static const System::Byte MYSQL_TYPE_MEDIUM_BLOB = System::Byte(0xfa);
static const System::Byte MYSQL_TYPE_LONG_BLOB = System::Byte(0xfb);
static const System::Byte MYSQL_TYPE_BLOB = System::Byte(0xfc);
static const System::Byte MYSQL_TYPE_VAR_STRING = System::Byte(0xfd);
static const System::Byte MYSQL_TYPE_STRING = System::Byte(0xfe);
static const System::Byte MYSQL_TYPE_GEOMETRY = System::Byte(0xff);
static const System::Int8 MY_ST_UNKNOWN = System::Int8(0x0);
static const System::Int8 MY_ST_PREPARE = System::Int8(0x1);
static const System::Int8 MY_ST_EXECUTE = System::Int8(0x2);
static const System::Int8 MYSQL_STMT_INIT_DONE = System::Int8(0x1);
static const System::Int8 MYSQL_STMT_PREPARE_DONE = System::Int8(0x2);
static const System::Int8 MYSQL_STMT_EXECUTE_DONE = System::Int8(0x3);
static const System::Int8 MYSQL_STMT_FETCH_DONE = System::Int8(0x4);
static const System::Int8 OLD_MYSQL_TIMESTAMP_NONE = System::Int8(0x0);
static const System::Int8 OLD_MYSQL_TIMESTAMP_DATE = System::Int8(0x1);
static const System::Int8 OLD_MYSQL_TIMESTAMP_FULL = System::Int8(0x2);
static const System::Int8 OLD_MYSQL_TIMESTAMP_TIME = System::Int8(0x3);
static const System::Int8 MYSQL_TIMESTAMP_NONE = System::Int8(-2);
static const System::Int8 MYSQL_TIMESTAMP_ERROR = System::Int8(-1);
static const System::Int8 MYSQL_TIMESTAMP_DATE = System::Int8(0x0);
static const System::Int8 MYSQL_TIMESTAMP_DATETIME = System::Int8(0x1);
static const System::Int8 MYSQL_TIMESTAMP_TIME = System::Int8(0x2);
static const System::Int8 MYSQL_TIMESTAMP_DATETIME_TZ = System::Int8(0x3);
static const System::Int8 STMT_ATTR_UPDATE_MAX_LENGTH = System::Int8(0x0);
static const System::Int8 STMT_ATTR_CURSOR_TYPE = System::Int8(0x1);
static const System::Int8 STMT_ATTR_PREFETCH_ROWS = System::Int8(0x2);
static const System::Int8 MYSQL_SUCCESS = System::Int8(0x0);
static const System::Int8 MYSQL_STATUS_ERROR = System::Int8(0x1);
static const System::Int8 MYSQL_NO_DATA = System::Int8(0x64);
static const System::Int8 MYSQL_DATA_TRUNCATED = System::Int8(0x65);
static const System::Int8 MYSQL_NEED_DATA = System::Int8(0x63);
static const System::Word ER_ACCESS_DENIED_ERROR = System::Word(0x415);
static const System::Word ER_BAD_TABLE_ERROR = System::Word(0x41b);
static const System::Word ER_DUP_ENTRY = System::Word(0x426);
static const System::Word ER_PARSE_ERROR = System::Word(0x428);
static const System::Word ER_NO_SUCH_TABLE = System::Word(0x47a);
static const System::Word ER_LOCK_WAIT_TIMEOUT = System::Word(0x4b5);
static const System::Word ER_NO_REFERENCED_ROW = System::Word(0x4c0);
static const System::Word ER_ROW_IS_REFERENCED = System::Word(0x4c1);
static const System::Word ER_SP_DOES_NOT_EXIST = System::Word(0x519);
static const System::Word ER_QUERY_INTERRUPTED = System::Word(0x525);
static const System::Word ER_SP_WRONG_NO_OF_ARGS = System::Word(0x526);
static const System::Word ER_TRG_DOES_NOT_EXIST = System::Word(0x550);
static const System::Word ER_SP_NOT_VAR_ARG = System::Word(0x586);
static const System::Word ER_MUST_CHANGE_PASSWORD = System::Word(0x71c);
static const System::Word ER_MUST_CHANGE_PASSWORD_LOGIN = System::Word(0x746);
static const System::Word CR_CONN_HOST_ERROR = System::Word(0x7d3);
static const System::Word ER_SERVER_GONE_ERROR = System::Word(0x7d6);
static const System::Word ER_SERVER_LOST = System::Word(0x7dd);
static const System::Word CR_NO_DATA = System::Word(0x803);
static const System::Word ER_UNKNOWN_VIEW = System::Word(0xffc);
}	/* namespace Mysqlcli */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_MYSQLCLI)
using namespace Firedac::Phys::Mysqlcli;
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
#endif	// Firedac_Phys_MysqlcliHPP
