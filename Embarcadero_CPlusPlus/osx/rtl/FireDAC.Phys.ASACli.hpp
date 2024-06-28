// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.ASACli.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_AsacliHPP
#define Firedac_Phys_AsacliHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <FireDAC.Stan.Consts.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Asacli
{
//-- forward type declarations -----------------------------------------------
struct a_name;
struct a_dbtools_info;
struct a_backup_db_v12;
struct a_backup_db_v11;
struct a_backup_db_v10;
struct a_backup_db_v9;
struct a_validate_db_v12;
struct a_validate_db_v11;
struct a_validate_db_v10;
struct a_validate_db_v9;
struct a_validate_db_v5;
//-- type declarations -------------------------------------------------------
typedef System::Int8 an_exit_code;

typedef unsigned a_bit_field;

typedef unsigned a_bit_short;

typedef int a_sql_int32;

typedef unsigned a_sql_uint32;

typedef System::Byte a_char;

typedef System::Byte *Pa_char;

typedef a_name *P_name;

#pragma pack(push,1)
struct DECLSPEC_DRECORD a_name
{
public:
	a_name *next;
	System::StaticArray<System::Byte, 1> name;
};
#pragma pack(pop)


typedef System::Int8 __stdcall (*MSG_CALLBACK)(Pa_char str);

typedef System::Int8 __stdcall (*STATUS_CALLBACK)(unsigned code, void * data, unsigned length);

typedef System::Int8 __stdcall (*MSG_QUEUE_CALLBACK)(unsigned code);

typedef System::Int8 __stdcall (*SET_WINDOW_TITLE_CALLBACK)(Pa_char str);

typedef System::Int8 __stdcall (*SET_TRAY_MESSAGE_CALLBACK)(Pa_char str);

typedef System::Int8 __stdcall (*SET_PROGRESS_CALLBACK)(unsigned index, unsigned max);

typedef System::Int8 __stdcall (*USAGE_CALLBACK)(Pa_char str);

typedef System::Int8 __stdcall (*SPLASH_CALLBACK)(Pa_char title, Pa_char body);

typedef a_dbtools_info *P_dbtools_info;

#pragma pack(push,1)
struct DECLSPEC_DRECORD a_dbtools_info
{
public:
	MSG_CALLBACK errorrtn;
};
#pragma pack(pop)


typedef System::Int8 __stdcall (*TDBToolsInit)(P_dbtools_info ApInfo);

typedef System::Int8 __stdcall (*TDBToolsFini)(P_dbtools_info ApInfo);

typedef System::Int8 __stdcall (*TDBToolsVersion)(void);

enum DECLSPEC_DENUM a_chkpt_log_type : unsigned int { BACKUP_CHKPT_LOG_COPY, BACKUP_CHKPT_LOG_NOCOPY, BACKUP_CHKPT_LOG_RECOVER, BACKUP_CHKPT_LOG_AUTO, BACKUP_CHKPT_LOG_DEFAULT };

typedef void * P_backup_db;

#pragma pack(push,1)
struct DECLSPEC_DRECORD a_backup_db_v12
{
public:
	System::Word version;
	MSG_CALLBACK errorrtn;
	MSG_CALLBACK msgrtn;
	MSG_CALLBACK confirmrtn;
	MSG_CALLBACK statusrtn;
	System::Byte *output_dir;
	System::Byte *connectparms;
	System::Byte *hotlog_filename;
	unsigned page_blocksize;
	System::Byte chkpt_log_type;
	System::Byte backup_interrupted;
	unsigned flags1;
};
#pragma pack(pop)


#pragma pack(push,1)
struct DECLSPEC_DRECORD a_backup_db_v11
{
public:
	System::Word version;
	System::Byte *output_dir;
	System::Byte *connectparms;
	MSG_CALLBACK confirmrtn;
	MSG_CALLBACK errorrtn;
	MSG_CALLBACK msgrtn;
	MSG_CALLBACK statusrtn;
	unsigned flags1;
	System::Byte *hotlog_filename;
	System::Byte backup_interrupted;
	unsigned flags2;
	a_chkpt_log_type chkpt_log_type;
	unsigned page_blocksize;
};
#pragma pack(pop)


#pragma pack(push,1)
struct DECLSPEC_DRECORD a_backup_db_v10
{
public:
	System::Word version;
	System::Byte *output_dir;
	System::Byte *connectparms;
	System::Byte *_unused0;
	MSG_CALLBACK confirmrtn;
	MSG_CALLBACK errorrtn;
	MSG_CALLBACK msgrtn;
	MSG_CALLBACK statusrtn;
	unsigned flags1;
	System::Byte *hotlog_filename;
	System::Byte backup_interrupted;
	unsigned flags2;
	a_chkpt_log_type chkpt_log_type;
	unsigned page_blocksize;
};
#pragma pack(pop)


#pragma pack(push,1)
struct DECLSPEC_DRECORD a_backup_db_v9
{
public:
	System::Word version;
	System::Byte *output_dir;
	System::Byte *connectparms;
	System::Byte *startline;
	MSG_CALLBACK confirmrtn;
	MSG_CALLBACK errorrtn;
	MSG_CALLBACK msgrtn;
	MSG_CALLBACK statusrtn;
	unsigned flags1;
	System::Byte *hotlog_filename;
	System::Byte backup_interrupted;
};
#pragma pack(pop)


typedef System::Int8 __stdcall (*TDBBackup)(void * ApInfo);

enum DECLSPEC_DENUM a_validate_type : unsigned int { VALIDATE_NORMAL, VALIDATE_DATA, VALIDATE_INDEX, VALIDATE_EXPRESS, VALIDATE_FULL, VALIDATE_CHECKSUM, VALIDATE_DATABASE, VALIDATE_COMPLETE };

typedef void * P_validate_db;

#pragma pack(push,1)
struct DECLSPEC_DRECORD a_validate_db_v12
{
public:
	System::Word version;
	MSG_CALLBACK errorrtn;
	MSG_CALLBACK msgrtn;
	MSG_CALLBACK statusrtn;
	System::Byte *connectparms;
	a_name *tables;
	a_validate_type _type;
	unsigned flags1;
};
#pragma pack(pop)


#pragma pack(push,1)
struct DECLSPEC_DRECORD a_validate_db_v11
{
public:
	System::Word version;
	System::Byte *connectparms;
	a_name *tables;
	MSG_CALLBACK errorrtn;
	MSG_CALLBACK msgrtn;
	MSG_CALLBACK statusrtn;
	unsigned flags1;
	a_validate_type _type;
};
#pragma pack(pop)


#pragma pack(push,1)
struct DECLSPEC_DRECORD a_validate_db_v10
{
public:
	System::Word version;
	System::Byte *connectparms;
	System::Byte *_unused1;
	a_name *tables;
	MSG_CALLBACK errorrtn;
	MSG_CALLBACK msgrtn;
	MSG_CALLBACK statusrtn;
	unsigned flags1;
	a_validate_type _type;
};
#pragma pack(pop)


#pragma pack(push,1)
struct DECLSPEC_DRECORD a_validate_db_v9
{
public:
	System::Word version;
	System::Byte *connectparms;
	System::Byte *startline;
	a_name *tables;
	MSG_CALLBACK errorrtn;
	MSG_CALLBACK msgrtn;
	MSG_CALLBACK statusrtn;
	unsigned flags1;
	a_validate_type _type;
};
#pragma pack(pop)


#pragma pack(push,1)
struct DECLSPEC_DRECORD a_validate_db_v5
{
public:
	System::Word version;
	System::Byte *connectparms;
	System::Byte *startline;
	a_name *tables;
	MSG_CALLBACK errorrtn;
	MSG_CALLBACK msgrtn;
	MSG_CALLBACK statusrtn;
	unsigned flags1;
};
#pragma pack(pop)


typedef System::Int8 __stdcall (*TDBValidate)(void * ApInfo);

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 EXIT_OKAY = System::Int8(0x0);
static const System::Int8 EXIT_FAIL = System::Int8(0x1);
static const System::Int8 EXIT_BAD_DATA = System::Int8(0x2);
static const System::Int8 EXIT_FILE_ERROR = System::Int8(0x3);
static const System::Int8 EXIT_OUT_OF_MEMORY = System::Int8(0x4);
static const System::Int8 EXIT_BREAK = System::Int8(0x5);
static const System::Int8 EXIT_COMMUNICATIONS_FAIL = System::Int8(0x6);
static const System::Int8 EXIT_MISSING_DATABASE = System::Int8(0x7);
static const System::Int8 EXIT_PROTOCOL_MISMATCH = System::Int8(0x8);
static const System::Int8 EXIT_UNABLE_TO_CONNECT = System::Int8(0x9);
static const System::Int8 EXIT_ENGINE_NOT_RUNNING = System::Int8(0xa);
static const System::Int8 EXIT_SERVER_NOT_FOUND = System::Int8(0xb);
static const System::Int8 EXIT_BAD_ENCRYPT_KEY = System::Int8(0xc);
static const System::Int8 EXIT_DB_VER_NEWER = System::Int8(0xd);
static const System::Int8 EXIT_FILE_INVALID_DB = System::Int8(0xe);
static const System::Int8 EXIT_LOG_FILE_ERROR = System::Int8(0xf);
static const System::Int8 EXIT_FILE_IN_USE = System::Int8(0x10);
static const System::Int8 EXIT_FATAL_ERROR = System::Int8(0x11);
static const System::Int8 EXIT_MISSING_LICENSE_FILE = System::Int8(0x12);
static const System::Int8 EXIT_BACKGROUND_SYNC_ABORTED = System::Int8(0x13);
static const System::Int8 EXIT_FILE_ACCESS_DENIED = System::Int8(0x14);
static const System::Byte EXIT_USAGE = System::Byte(0xff);
#define C_SQLAnywhere16Lib u"libdbodbc16_r.dylib"
#define C_DBTool u"libdbtool%d_r.dylib"
static const System::Word DB_TOOLS_VERSION_NUMBER = System::Word(0x2ee0);
static const System::Int8 CBDB_F1_backup_database = System::Int8(0x1);
static const System::Int8 CBDB_F1_backup_logfile = System::Int8(0x2);
static const System::Int8 CBDB_F1__unused1 = System::Int8(0x4);
static const System::Int8 CBDB_F1_no_confirm = System::Int8(0x8);
static const System::Int8 CBDB_F1_quiet = System::Int8(0x10);
static const System::Int8 CBDB_F1_rename_log = System::Int8(0x20);
static const System::Int8 CBDB_F1_truncate_log = System::Int8(0x40);
static const System::Byte CBDB_F1_rename_local_log = System::Byte(0x80);
static const System::Int8 CBDB_F2_server_backup = System::Int8(0x1);
static const System::Int8 CBDB_F3_backup_database = System::Int8(0x1);
static const System::Int8 CBDB_F3_backup_logfile = System::Int8(0x2);
static const System::Int8 CBDB_F3_no_confirm = System::Int8(0x4);
static const System::Int8 CBDB_F3_quiet = System::Int8(0x8);
static const System::Int8 CBDB_F3_rename_log = System::Int8(0x10);
static const System::Int8 CBDB_F3_truncate_log = System::Int8(0x20);
static const System::Int8 CBDB_F3_rename_local_log = System::Int8(0x40);
static const System::Byte CBDB_F3_server_backup = System::Byte(0x80);
static const System::Word CBDB_F3_progress_messages = System::Word(0x100);
static const System::Int8 CVDB_F1_quiet = System::Int8(0x1);
static const System::Int8 CVDB_F1_index = System::Int8(0x2);
}	/* namespace Asacli */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ASACLI)
using namespace Firedac::Phys::Asacli;
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
#endif	// Firedac_Phys_AsacliHPP
