// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Stan.Consts.pas' rev: 34.00 (iOS)

#ifndef Firedac_Stan_ConstsHPP
#define Firedac_Stan_ConstsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Stan
{
namespace Consts
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef System::StaticArray<System::UnicodeString, 2> Firedac_Stan_Consts__1;

//-- var, const, procedure ---------------------------------------------------
#define C_FD_Version u"27.0.0 (Build 99682)"
#define C_FD_Copyright u"\u00a9 2021 Embarcadero Technologies, Inc."
#define C_FD_Product u"FireDAC"
#define C_FD_ProductFull u"Embarcadero\u00ae FireDAC"
#define C_FD_ToolName u"RAD Studio 10.4"
#define C_FD_WinEOL u"\r\n"
static constexpr System::WideChar C_FD_PosixEOL = (System::WideChar)(0xa);
static constexpr System::WideChar C_FD_EOL = (System::WideChar)(0xa);
static constexpr System::WideChar C_FD_PathDelim = (System::WideChar)(0x2f);
#define C_FD_DLLExt u".dylib"
#define C_FD_DLLFolder u"lib"
static constexpr System::Int8 C_FD_GUIDStrLen = System::Int8(0x26);
static constexpr System::Byte C_FD_MaxNameLen = System::Byte(0x80);
static constexpr System::Int8 C_FD_StorageVer = System::Int8(0xf);
#define S_FD_LStan u"Stan"
#define S_FD_LStan_PEval u"Eval"
#define S_FD_LStan_PDef u"Def"
#define S_FD_LGUIx u"GUIx"
#define S_FD_LGUIx_PForms u"Forms"
#define S_FD_LGUIx_PSrvc u"Services"
#define S_FD_LMoni u"Moni"
#define S_FD_LMoni_PRemote u"Remote"
#define S_FD_LMoni_PFF u"FlatFile"
#define S_FD_LDatS u"DatS"
#define S_FD_LPhys u"Phys"
#define S_FD_LDApt u"DApt"
#define S_FD_LComp u"Comp"
#define S_FD_LComp_PClnt u"Clnt"
#define S_FD_LComp_PDS u"DS"
#define S_FD_LComp_PDM u"DM"
#define S_FD_LComp_PScr u"Script"
#define S_FD_LComp_Design u"Design"
#define S_FD_TDBXId u"TDBX"
#define S_FD_ODBCId u"ODBC"
#define S_FD_MSSQLId u"MSSQL"
#define S_FD_MSAccId u"MSAcc"
#define S_FD_DB2Id u"DB2"
#define S_FD_MySQLId u"MySQL"
#define S_FD_OraId u"Ora"
#define S_FD_ASAId u"ASA"
#define S_FD_ADSId u"ADS"
#define S_FD_IBId u"IB"
#define S_FD_IBLiteId u"IBLite"
#define S_FD_FBId u"FB"
#define S_FD_PGId u"PG"
#define S_FD_SQLiteId u"SQLite"
#define S_FD_NexusId u"Nexus"
#define S_FD_DSId u"DS"
#define S_FD_InfxId u"Infx"
#define S_FD_TDataId u"TData"
#define S_FD_MongoId u"Mongo"
#define S_FD_MSSQL_RDBMS u"MSSQL"
#define S_FD_MSAcc_RDBMS u"MSAccess"
#define S_FD_DB2_RDBMS u"DB2"
#define S_FD_MySQL_RDBMS u"MySQL"
#define S_FD_Ora_RDBMS u"Oracle"
#define S_FD_ASA_RDBMS u"SQLAnywhere"
#define S_FD_ADS_RDBMS u"Advantage"
#define S_FD_IB_RDBMS u"InterBase"
#define S_FD_FB_RDBMS u"Firebird"
#define S_FD_PG_RDBMS u"PostgreSQL"
#define S_FD_SQLite_RDBMS u"SQLite"
#define S_FD_Nexus_RDBMS u"NexusDB"
#define S_FD_DS_RDBMS u"DataSnap"
#define S_FD_Infx_RDBMS u"Informix"
#define S_FD_TData_RDBMS u"Teradata"
#define S_FD_Mongo_NoSQL u"MongoDB"
#define S_FD_Other_RDBMS u"Other"
#define S_FD_DefinitionParam_Common_Name u"Name"
#define S_FD_DefinitionParam_Common_Parent u"Parent"
#define S_FD_DefinitionParam_Common_ConnectionDef u"ConnectionDef"
#define C_FD_DrvBaseId u"BaseDriverID"
#define S_FD_DrvVendorLib u"VendorLib"
#define S_FD_DrvVendorHome u"VendorHome"
#define S_FD_Win32 u"Win32"
#define S_FD_Win64 u"Win64"
#define S_FD_OSX32 u"OSX32"
#define S_FD_OSX64 u"OSX64"
#define S_FD_UIX32 u"UIX32"
#define S_FD_UIX64 u"UIX64"
#define S_FD_ANDROID u"ANDROID"
#define S_FD_MoniFlatFile u"FlatFile"
#define S_FD_MoniRemote u"Remote"
#define S_FD_MoniCustom u"Custom"
#define S_FD_ConnParam_Common_DriverID u"DriverID"
#define S_FD_ConnParam_Common_Database u"Database"
#define S_FD_ConnParam_Common_Server u"Server"
#define S_FD_ConnParam_Common_Port u"Port"
#define S_FD_ConnParam_Common_UserName u"User_Name"
#define S_FD_ConnParam_Common_BDEStyleUserName u"User name"
#define S_FD_ConnParam_Common_Password u"Password"
#define S_FD_ConnParam_Common_NewPassword u"NewPassword"
#define S_FD_ConnParam_Common_OSAuthent u"OSAuthent"
#define S_FD_ConnParam_Common_Pooled u"Pooled"
#define S_FD_ConnParam_Common_Pool_CleanupTimeout u"POOL_CleanupTimeout"
#define S_FD_ConnParam_Common_Pool_ExpireTimeout u"POOL_ExpireTimeout"
#define S_FD_ConnParam_Common_Pool_MaximumItems u"POOL_MaximumItems"
#define S_FD_ConnParam_Common_MetaDefSchema u"MetaDefSchema"
#define S_FD_ConnParam_Common_MetaDefCatalog u"MetaDefCatalog"
#define S_FD_ConnParam_Common_MetaCurSchema u"MetaCurSchema"
#define S_FD_ConnParam_Common_MetaCurCatalog u"MetaCurCatalog"
#define S_FD_ConnParam_Common_MetaCaseIns u"MetaCaseIns"
#define S_FD_ConnParam_Common_RDBMS u"RDBMS"
#define S_FD_ConnParam_Common_MonitorBy u"MonitorBy"
#define S_FD_ConnParam_Common_LoginTimeout u"LoginTimeout"
#define S_FD_ConnParam_Common_CharacterSet u"CharacterSet"
#define S_FD_ConnParam_Common_GUIDEndian u"GUIDEndian"
#define S_FD_Little u"Little"
#define S_FD_Big u"Big"
#define S_FD_ConnParam_Common_ExtendedMetadata u"ExtendedMetadata"
#define S_FD_ConnParam_Common_ApplicationName u"ApplicationName"
#define S_FD_ConnParam_MySQL_Compress u"Compress"
#define S_FD_ConnParam_MySQL_UseSSL u"UseSSL"
#define S_FD_ConnParam_MySQL_SSL_key u"SSL_key"
#define S_FD_ConnParam_MySQL_SSL_cert u"SSL_cert"
#define S_FD_ConnParam_MySQL_SSL_ca u"SSL_ca"
#define S_FD_ConnParam_MySQL_SSL_capath u"SSL_capath"
#define S_FD_ConnParam_MySQL_SSL_cipher u"SSL_cipher"
#define S_FD_ConnParam_MySQL_ResultMode u"ResultMode"
#define S_FD_ConnParam_MySQL_TinyIntFormat u"TinyIntFormat"
#define S_FD_ConnParam_MySQL_EmbeddedArgs u"EmbeddedArgs"
#define S_FD_ConnParam_MySQL_EmbeddedGroups u"EmbeddedGroups"
#define S_FD_ConnParam_MySQL_ReadTimeout u"ReadTimeout"
#define S_FD_ConnParam_MySQL_WriteTimeout u"WriteTimeout"
#define S_FD_ConnParam_ODBC_ODBCAdvanced u"ODBCAdvanced"
#define S_FD_ConnParam_ODBC_ODBCDriver u"ODBCDriver"
#define S_FD_ConnParam_ODBC_DataSource u"DataSource"
#define S_FD_ConnParam_ODBC_DSN u"DSN"
#define S_FD_ConnParam_ODBC_NumericFormat u"NumericFormat"
#define S_FD_ConnParam_ODBC_ODBCVersion u"ODBCVersion"
#define S_FD_ConnParam_MSSQL_Network u"Network"
#define S_FD_ConnParam_MSSQL_Address u"Address"
#define S_FD_ConnParam_MSSQL_MARS u"MARS"
#define S_FD_ConnParam_MSSQL_Workstation u"Workstation"
#define S_FD_ConnParam_MSSQL_Language u"Language"
#define S_FD_ConnParam_MSSQL_Encrypt u"Encrypt"
#define S_FD_ConnParam_MSSQL_VariantFormat u"VariantFormat"
#define S_FD_ConnParam_MSSQL_MetaCaseInsCat u"MetaCaseInsCat"
#define S_FD_EventKind_MSSQL_Events u"QueryNotifies"
#define S_FD_ConnParam_MSAcc_SystemDB u"SystemDB"
#define S_FD_ConnParam_MSAcc_ReadOnly u"ReadOnly"
#define S_FD_ConnParam_MSAcc_StringFormat u"StringFormat"
#define S_FD_Choose u"Choose"
#define S_FD_Unicode u"Unicode"
#define S_FD_ANSI u"ANSI"
#define S_FD_ConnParam_ASA_ToolHome u"ToolHome"
#define S_FD_ConnParam_ASA_ToolLib u"ToolLib"
#define S_FD_ConnParam_ASA_DatabaseFile u"DatabaseFile"
#define S_FD_ConnParam_ASA_Compress u"Compress"
#define S_FD_ConnParam_ASA_Encrypt u"Encrypt"
#define S_FD_EventKind_ASA_Events u"Message"
#define S_FD_ConnParam_ADS_DateFormat u"DateFormat"
#define S_FD_ConnParam_ADS_Decimals u"Decimals"
#define S_FD_ConnParam_ADS_DefaultPath u"DefaultPath"
#define S_FD_ConnParam_ADS_SearchPath u"SearchPath"
#define S_FD_ConnParam_ADS_ShowDeleted u"ShowDeleted"
#define S_FD_ConnParam_ADS_Epoch u"Epoch"
#define S_FD_ConnParam_ADS_Exact u"Exact"
#define S_FD_ConnParam_ADS_Alias u"Alias"
#define S_FD_ConnParam_ADS_Protocol u"Protocol"
#define S_FD_ConnParam_ADS_Compress u"Compress"
#define S_FD_ConnParam_ADS_ServerTypes u"ServerTypes"
#define S_FD_ConnParam_ADS_Locking u"Locking"
#define S_FD_ConnParam_ADS_TableType u"TableType"
#define S_FD_ConnParam_ADS_TablePassword u"TablePassword"
#define S_FD_ConnParam_ADS_ADSAdvanced u"ADSAdvanced"
#define S_FD_EventKind_ADS_Events u"Events"
#define S_FD_ConnParam_Oracle_AuthMode u"AuthMode"
#define S_FD_ConnParam_Oracle_BooleanFormat u"BooleanFormat"
#define S_FD_ConnParam_Oracle_OracleAdvanced u"OracleAdvanced"
#define S_FD_ConnParam_Oracle_NLS_LANG u"NLSLang"
#define S_FD_ConnParam_Oracle_TNS_ADMIN u"TNSAdmin"
#define S_FD_ConnParam_Oracle_Threaded u"Threaded"
#define S_FD_ConnParam_Oracle_ReadTimeout u"ReadTimeout"
#define S_FD_ConnParam_Oracle_WriteTimeout u"WriteTimeout"
#define S_FD_EventKind_Oracle_DBMS_ALERT u"DBMS_ALERT"
#define S_FD_EventKind_Oracle_DBMS_PIPE u"DBMS_PIPE"
#define S_FD_EventKind_Oracle_CQN u"QueryNotifies"
#define S_FD_ConnParam_IB_Protocol u"Protocol"
#define S_FD_ConnParam_IB_RoleName u"RoleName"
#define S_FD_ConnParam_IB_SQLDialect u"SQLDialect"
#define S_FD_ConnParam_IB_OpenMode u"OpenMode"
#define S_FD_ConnParam_IB_DropDatabase u"DropDatabase"
#define S_FD_ConnParam_IB_PageSize u"PageSize"
#define S_FD_ConnParam_IB_IBAdvanced u"IBAdvanced"
#define S_FD_ConnParam_IB_ThreadSafe u"ThreadSafe"
#define S_FD_ConnParam_IB_Lite u"Lite"
#define S_FD_ConnParam_IB_InstanceName u"InstanceName"
#define S_FD_ConnParam_IB_SEPassword u"SEPassword"
#define S_FD_ConnParam_FB_Embedded u"Embedded"
#define S_FD_ConnParam_FB_CharLenMode u"CharLenMode"
#define S_FD_EventKind_IB_Events u"Events"
#define S_FD_ConnParam_DB2_Alias u"Alias"
#define S_FD_ConnParam_DB2_Protocol u"Protocol"
#define S_FD_ConnParam_DB2_StringFormat u"StringFormat"
#define S_FD_ConnParam_DB2_TxSupported u"TxSupported"
#define S_FD_EventKind_DB2_DBMS_ALERT u"DBMS_ALERT"
#define S_FD_EventKind_DB2_DBMS_PIPE u"DBMS_PIPE"
#define S_FD_ConnParam_PG_OidAsBlob u"OidAsBlob"
#define S_FD_ConnParam_PG_UnknownFormat u"UnknownFormat"
#define S_FD_ConnParam_PG_ArrayScanSample u"ArrayScanSample"
#define S_FD_ConnParam_PG_PGAdvanced u"PGAdvanced"
#define S_FD_EventKind_PG_Events u"Notifies"
#define S_FD_ConnParam_SQLite_EngineLinkage u"EngineLinkage"
#define S_FD_ConnParam_SQLite_SharedCache u"SharedCache"
#define S_FD_ConnParam_SQLite_OpenMode u"OpenMode"
#define S_FD_ConnParam_SQLite_Encrypt u"Encrypt"
#define S_FD_ConnParam_SQLite_BusyTimeout u"BusyTimeout"
#define S_FD_ConnParam_SQLite_CacheSize u"CacheSize"
#define S_FD_ConnParam_SQLite_LockingMode u"LockingMode"
#define S_FD_ConnParam_SQLite_Synchronous u"Synchronous"
#define S_FD_ConnParam_SQLite_JournalMode u"JournalMode"
#define S_FD_ConnParam_SQLite_ForeignKeys u"ForeignKeys"
#define S_FD_ConnParam_SQLite_StringFormat u"StringFormat"
#define S_FD_ConnParam_SQLite_GUIDFormat u"GUIDFormat"
#define S_FD_ConnParam_SQLite_DateTimeFormat u"DateTimeFormat"
#define S_FD_ConnParam_SQLite_Extensions u"Extensions"
#define S_FD_ConnParam_SQLite_SQLiteAdvanced u"SQLiteAdvanced"
#define S_FD_EventKind_SQLite_Events u"Events"
#define S_FD_ConnParam_Nexus_Protocol u"Protocol"
#define S_FD_ConnParam_Nexus_OpenMode u"OpenMode"
#define S_FD_ConnParam_Nexus_ShareMode u"ShareMode"
#define S_FD_ConnParam_TDBX_DBXAdvanced u"DBXAdvanced"
#define S_FD_ConnParam_DS_Protocol u"Protocol"
#define S_FD_EventKind_DS_Events u"Callbacks"
#define S_FD_ConnParam_Infx_DBCharacterSet u"DBCharacterSet"
#define S_FD_ConnParam_Infx_StringFormat u"StringFormat"
#define S_FD_ConnParam_Infx_ReadTimeout u"ReadTimeout"
#define S_FD_ConnParam_Infx_WriteTimeout u"WriteTimeout"
#define S_FD_ConnParam_Infx_TxSupported u"TxSupported"
#define S_FD_ConnParam_Infx_TxRetainLocks u"TxRetainLocks"
#define S_FD_ConnParam_Infx_TxLastCommitted u"TxLastCommitted"
#define S_FD_EventKind_Infx_DBMS_ALERT u"DBMS_ALERT"
#define S_FD_ConnParam_TData_Encrypt u"Encrypt"
#define S_FD_ConnParam_TData_SessionMode u"SessionMode"
#define S_FD_ConnParam_Mongo_UseSSL u"UseSSL"
#define S_FD_ConnParam_Mongo_SSL_PEMFile u"SSL_PEMFile"
#define S_FD_ConnParam_Mongo_SSL_PEMPassword u"SSL_PEMPassword"
#define S_FD_ConnParam_Mongo_SSL_CAFile u"SSL_CAFile"
#define S_FD_ConnParam_Mongo_SSL_WeakValidation u"SSL_WeakValidation"
#define S_FD_ConnParam_Mongo_SSL_AllowInvHost u"SSL_AllowInvHost"
#define S_FD_ConnParam_Mongo_ReadTimeout u"ReadTimeout"
#define S_FD_ConnParam_Mongo_MoreHosts u"MoreHosts"
#define S_FD_ConnParam_Mongo_TimeZone u"TimeZone"
#define S_FD_ConnParam_Mongo_MongoAdvanced u"MongoAdvanced"
#define S_FD_EventKind_Mongo_Tail u"Tail"
static constexpr System::Word C_FD_PoolCleanupTimeout = System::Word(0x7530);
static constexpr int C_FD_PoolExpireTimeout = int(0x15f90);
static constexpr System::Word C_FD_PoolCloseTimeout = System::Word(0x2710);
static constexpr System::Int8 C_FD_PoolMaximumItems = System::Int8(0x32);
static constexpr System::Int8 C_FD_HideCursorDelay = System::Int8(0x32);
static constexpr System::Byte C_FD_DelayBeforeFWait = System::Byte(0xc8);
static constexpr System::Word C_FD_ThreadStartupTimeout = System::Word(0x3e8);
static constexpr System::Word C_FD_ThreadIdleTimeout = System::Word(0x3e8);
static constexpr System::Word C_FD_PhysManagerShutdownTimeout = System::Word(0x2710);
static constexpr System::Word C_FD_PhysConnRetryDelay = System::Word(0xbb8);
static constexpr System::Int8 C_FD_PhysConnRetryCount = System::Int8(0x3);
#define S_FD_Main u"main"
#define S_FD_CfgFile u"fd.conf"
#define S_FD_DefCfgFileName u"FDConnectionDefs.ini"
#define S_FD_DefDrvFileName u"FDDrivers.ini"
#define S_FD_CfgValName u"ConnectionDefFile"
#define S_FD_DrvValName u"DriverFile"
#define S_FD_MoniValName u"MonitorPath"
#define S_FD_ExplValName u"ExplorerPath"
#define S_FD_ExecValName u"ExecutorPath"
#define S_FD_HelpValName u"HelpPath"
#define S_FD_Profiles u"Profiles"
#define S_FD_Drivers u"Drivers"
#define S_FD_DesignTime u"DesignTime"
#define S_FD_DTCatalog u"Catalog"
#define S_FD_DTSchema u"Schema"
#define S_FD_DTScope u"Scope"
#define S_FD_DTTableKinds u"TableKinds"
#define S_FD_DTFullName u"FullName"
#define S_FD_DTTracing u"Tracing"
#define S_FD_DTDCFieldsEditor u"DCFieldsEditor"
#define S_FD_DTMask u"Mask"
#define S_FD_True u"True"
#define S_FD_False u"False"
#define S_FD_Yes u"Yes"
#define S_FD_No u"No"
extern DELPHI_PACKAGE Firedac_Stan_Consts__1 S_FD_Bools;
#define S_FD_Local u"<LOCAL>"
#define C_FD_GUIxFormsProvider u"Forms"
#define C_FD_GUIxConsoleProvider u"Console"
#define C_FD_GUIxFMXProvider u"FMX"
#define C_FD_SysNamePrefix u"_FD_"
#define C_FD_SysSavepointPrefix u"SP_"
#define C_FD_SysColumnPrefix u"FD__"
static constexpr System::Int8 C_FD_MaxAggsPerView = System::Int8(0x40);
static constexpr System::Int8 C_FD_CrsPctClose = System::Int8(0x50);
#define S_FD_Pi u"3.141592653589"
static const double C_FD_Pi = 3.141593E+00;
static constexpr System::Int8 C_FD_CmdGenRight = System::Int8(0x3c);
static constexpr System::WideChar C_FD_CmdGenAlias = (System::WideChar)(0x41);
#define C_FD_CmdGenWindow u"FD__WN_"
#define C_FD_CmdGenRangeStart u"FD__RS_"
#define C_FD_CmdGenRangeFinish u"FD__RF_"
#define C_FD_CmdGenLocate u"FD__LC_"
static constexpr int cvOracle80000 = int(0x2faf0800);
static constexpr int cvOracle80300 = int(0x2faf7d30);
static constexpr int cvOracle80400 = int(0x2fafa440);
static constexpr int cvOracle80500 = int(0x2fafcb50);
static constexpr int cvOracle80501 = int(0x2fafcb51);
static constexpr int cvOracle81000 = int(0x2fbe4a40);
static constexpr int cvOracle81500 = int(0x2fbf0d90);
static constexpr int cvOracle81600 = int(0x2fbf34a0);
static constexpr int cvOracle90000 = int(0x35a51075);
static constexpr int cvOracle92000 = int(0x35c36d80);
static constexpr int cvOracle100000 = int(0x3b9aca00);
static constexpr int cvOracle102000 = int(0x3bb94e80);
static constexpr int cvOracle110000 = int(0x4190ab00);
static constexpr int cvOracle111000 = int(0x419fed40);
static constexpr int cvOracle112000 = int(0x41af2f80);
static constexpr int cvOracle120000 = int(0x47868c00);
static constexpr int cvOracle121000 = int(0x4795ce40);
static constexpr int cvOracle122000 = int(0x47a51080);
static constexpr int mvMySQL032000 = int(0x1312d000);
static constexpr int mvMySQL032300 = int(0x134096c0);
static constexpr int mvMySQL032306 = int(0x13418120);
static constexpr int mvMySQL032314 = int(0x1342b9a0);
static constexpr int mvMySQL032321 = int(0x1343cb10);
static constexpr int mvMySQL040000 = int(0x17d78400);
static constexpr int mvMySQL040002 = int(0x17d7d220);
static constexpr int mvMySQL040018 = int(0x17da4320);
static constexpr int mvMySQL040100 = int(0x17e6c640);
static constexpr int mvMySQL040101 = int(0x17e6ed50);
static constexpr int mvMySQL041000 = int(0x18701a80);
static constexpr int mvMySQL041100 = int(0x187f5cc0);
static constexpr int mvMySQL050000 = int(0x1dcd6500);
static constexpr int mvMySQL050002 = int(0x1dcdb320);
static constexpr int mvMySQL050006 = int(0x1dce4f60);
static constexpr int mvMySQL050007 = int(0x1dce7670);
static constexpr int mvMySQL050010 = int(0x1dceeba0);
static constexpr int mvMySQL050023 = int(0x1dd0e770);
static constexpr int mvMySQL050060 = int(0x1dd68cc0);
static constexpr int mvMySQL050100 = int(0x1ddca740);
static constexpr int mvMySQL050134 = int(0x1de1d760);
static constexpr int mvMySQL050200 = int(0x1debe980);
static constexpr int mvMySQL050500 = int(0x1e19b040);
static constexpr int mvMySQL050503 = int(0x1e1a2570);
static constexpr int mvMySQL050600 = int(0x1e28f280);
static constexpr int mvMySQL050700 = int(0x1e3834c0);
static constexpr int mvMySQL060000 = int(0x23c34600);
static constexpr int mvMySQL080000 = int(0x2faf0800);
static constexpr int mvMariaDB100300 = int(0x3bc890c0);
static constexpr int svMSSQL6 = int(0x23c34600);
static constexpr int svMSSQL7 = int(0x29b92700);
static constexpr int svMSSQL2000 = int(0x2faf0800);
static constexpr int svMSSQL2005 = int(0x35a4e900);
static constexpr int svMSSQL2008 = int(0x3b9aca00);
static constexpr int svMSSQL2012 = int(0x4190ab00);
static constexpr int svMSSQL2014 = int(0x47868c00);
static constexpr int svMSSQL2016 = int(0x4d7c6d00);
static constexpr int cvSybaseASA6 = int(0x23c34600);
static constexpr int cvSybaseASA8 = int(0x2faf0800);
static constexpr int cvSybaseASA9 = int(0x35a4e900);
static constexpr int cvSybaseASA10 = int(0x3b9aca00);
static constexpr int cvSybaseASA11 = int(0x4190ab00);
static constexpr int cvSybaseASA12 = int(0x47868c00);
static constexpr int cvSybaseASA16 = int(0x5f5e1000);
static constexpr int svSQLite030000 = int(0x11e1a300);
static constexpr int svSQLite030202 = int(0x120075a0);
static constexpr int svSQLite030304 = int(0x12100600);
static constexpr int svSQLite030313 = int(0x12116590);
static constexpr int svSQLite030400 = int(0x121eac00);
static constexpr int svSQLite030401 = int(0x121ed310);
static constexpr int svSQLite030500 = int(0x122dee40);
static constexpr int svSQLite030508 = int(0x122f26c0);
static constexpr int svSQLite030600 = int(0x123d3080);
static constexpr int svSQLite030601 = int(0x123d5790);
static constexpr int svSQLite030604 = int(0x123dccc0);
static constexpr int svSQLite030605 = int(0x123df3d0);
static constexpr int svSQLite030608 = int(0x123e6900);
static constexpr int svSQLite030611 = int(0x123ede30);
static constexpr int svSQLite030619 = int(0x124016b0);
static constexpr int svSQLite030623 = int(0x1240b2f0);
static constexpr int svSQLite030700 = int(0x124c72c0);
static constexpr int svSQLite030703 = int(0x124ce7f0);
static constexpr int svSQLite030707 = int(0x124d8430);
static constexpr int svSQLite030711 = int(0x124e2070);
static constexpr int svSQLite030715 = int(0x124ebcb0);
static constexpr int svSQLite030803 = int(0x125c2a30);
static constexpr int svSQLite030807 = int(0x125cc670);
static constexpr int svSQLite030809 = int(0x125d1490);
static constexpr int svSQLite033200 = int(0x13c9eb00);
static constexpr int svPGSQL070300 = int(0x29e6edc0);
static constexpr int svPGSQL080100 = int(0x2fbe4a40);
static constexpr int svPGSQL080200 = int(0x2fcd8c80);
static constexpr int svPGSQL080300 = int(0x2fdccec0);
static constexpr int svPGSQL090000 = int(0x35a4e900);
static constexpr int svPGSQL090100 = int(0x35b42b40);
static constexpr int svPGSQL090500 = int(0x35f13440);
static constexpr int svPGSQL100000 = int(0x3b9aca00);
static constexpr int ivFB010002 = int(0x5f62f20);
static constexpr int ivFB010003 = int(0x5f65630);
static constexpr int ivFB010500 = int(0x6422c40);
static constexpr int ivFB020000 = int(0xbebc200);
static constexpr int ivFB020100 = int(0xbfb0440);
static constexpr int ivFB020500 = int(0xc380d40);
static constexpr int ivFB030000 = int(0x11e1a300);
static constexpr int ivIB060500 = int(0x240f9140);
static constexpr int ivIB070000 = int(0x29b92700);
static constexpr int ivIB070100 = int(0x29c86940);
static constexpr int ivIB070500 = int(0x2a057240);
static constexpr int ivIB080000 = int(0x2faf0800);
static constexpr int ivIB090000 = int(0x35a4e900);
static constexpr int ivIB100000 = int(0x3b9aca00);
static constexpr int ivIB110000 = int(0x4190ab00);
static constexpr int ivIB120000 = int(0x47868c00);
static constexpr int ivIB120100 = int(0x4795ce40);
static constexpr int ivIB130000 = int(0x4d7c6d00);
static constexpr int ivYF080607 = int(0x300ba6f0);
static constexpr int ovODBC2 = int(0xbebc200);
static constexpr int ovODBC3 = int(0x11e1a300);
static constexpr int ovODBC38 = int(0x16a65700);
static constexpr int caADS8 = int(0x2faf0800);
static constexpr int caADS9 = int(0x35a4e900);
static constexpr int caADS10 = int(0x3b9aca00);
static constexpr int caADS12 = int(0x47868c00);
static constexpr int ivInfx1110 = int(0x42294180);
static constexpr int tvTData1300 = int(0x4d7c6d00);
static constexpr int tvTData1400 = int(0x53724e00);
static constexpr int tvTData1410 = int(0x540ae480);
static constexpr int avDB2_400_7 = int(0x29b92700);
static constexpr System::Int8 C_FD_DefLongSize = System::Int8(0x0);
static constexpr System::Word C_FD_MaxPLSQLDataSize = System::Word(0x7fff);
static constexpr System::Byte C_FD_DefStrSize = System::Byte(0xff);
static constexpr System::Int8 C_FD_DefNumericSize = System::Int8(0x1e);
static constexpr System::Byte C_FD_MaxFixedSize = System::Byte(0x86);
static constexpr System::Word C_FD_DefInlineDataSize = System::Word(0x3e8);
static constexpr int C_FD_DefPieceBuffLen = int(0x40000);
static constexpr System::Int8 C_FD_DefRowSetSize = System::Int8(0x32);
static constexpr System::Word C_FD_DefMaxStrSize = System::Word(0x7fff);
static constexpr System::Int8 C_FD_DefMapPrec = System::Int8(-1);
static constexpr System::Int8 C_FD_DefMapScale = System::Int8(-1);
static constexpr unsigned C_FD_DefMapSize = unsigned(0xffffffff);
static constexpr System::Int8 er_FD_DuplicatedName = System::Int8(0x1);
static constexpr System::Int8 er_FD_NameNotFound = System::Int8(0x2);
static constexpr System::Int8 er_FD_ColTypeUndefined = System::Int8(0x3);
static constexpr System::Int8 er_FD_NoColsDefined = System::Int8(0x4);
static constexpr System::Int8 er_FD_CheckViolated = System::Int8(0x5);
static constexpr System::Int8 er_FD_CantBeginEdit = System::Int8(0x6);
static constexpr System::Int8 er_FD_CantCreateChildView = System::Int8(0x7);
static constexpr System::Int8 er_FD_RowCantBeDeleted = System::Int8(0x8);
static constexpr System::Int8 er_FD_ColMBBlob = System::Int8(0x9);
static constexpr System::Int8 er_FD_FixedLenDataMismatch = System::Int8(0xa);
static constexpr System::Int8 er_FD_RowNotInEditableState = System::Int8(0xb);
static constexpr System::Int8 er_FD_ColIsReadOnly = System::Int8(0xc);
static constexpr System::Int8 er_FD_RowCantBeInserted = System::Int8(0xd);
static constexpr System::Int8 er_FD_RowColMBNotNull = System::Int8(0xe);
static constexpr System::Int8 er_FD_DuplicateRows = System::Int8(0xf);
static constexpr System::Int8 er_FD_NoMasterRow = System::Int8(0x10);
static constexpr System::Int8 er_FD_HasChildRows = System::Int8(0x11);
static constexpr System::Int8 er_FD_CantCompareRows = System::Int8(0x12);
static constexpr System::Int8 er_FD_ConvIsNotSupported = System::Int8(0x13);
static constexpr System::Int8 er_FD_ColIsNotSearchable = System::Int8(0x14);
static constexpr System::Int8 er_FD_RowMayHaveSingleParent = System::Int8(0x15);
static constexpr System::Int8 er_FD_CantOperateInvObj = System::Int8(0x16);
static constexpr System::Int8 er_FD_CantSetParentRow = System::Int8(0x17);
static constexpr System::Int8 er_FD_RowIsNotNested = System::Int8(0x18);
static constexpr System::Int8 er_FD_ColumnIsNotRef = System::Int8(0x19);
static constexpr System::Int8 er_FD_ColumnIsNotSetRef = System::Int8(0x1a);
static constexpr System::Int8 er_FD_OperCNBPerfInState = System::Int8(0x1c);
static constexpr System::Int8 er_FD_CantSetUpdReg = System::Int8(0x1d);
static constexpr System::Int8 er_FD_TooManyAggs = System::Int8(0x1e);
static constexpr System::Int8 er_FD_GrpLvlExceeds = System::Int8(0x1f);
static constexpr System::Int8 er_FD_VarLenDataMismatch = System::Int8(0x20);
static constexpr System::Int8 er_FD_BadForeignKey = System::Int8(0x21);
static constexpr System::Int8 er_FD_BadUniqueKey = System::Int8(0x22);
static constexpr System::Int8 er_FD_CantChngColType = System::Int8(0x23);
static constexpr System::Int8 er_FD_BadRelation = System::Int8(0x24);
static constexpr System::Int8 er_FD_CantCreateParentView = System::Int8(0x25);
static constexpr System::Int8 er_FD_CantChangeTableStruct = System::Int8(0x26);
static constexpr System::Int8 er_FD_FoundCascadeLoop = System::Int8(0x27);
static constexpr System::Int8 er_FD_RecLocked = System::Int8(0x28);
static constexpr System::Int8 er_FD_RecNotLocked = System::Int8(0x29);
static constexpr System::Int8 er_FD_TypeIncompat = System::Int8(0x2a);
static constexpr System::Int8 er_FD_ValueOutOfRange = System::Int8(0x2b);
static constexpr System::Int8 er_FD_CantMerge = System::Int8(0x2c);
static constexpr System::Int8 er_FD_ColumnDoesnotFound = System::Int8(0x64);
static constexpr System::Int8 er_FD_ExprTermination = System::Int8(0x65);
static constexpr System::Int8 er_FD_ExprMBAgg = System::Int8(0x66);
static constexpr System::Int8 er_FD_ExprCantAgg = System::Int8(0x67);
static constexpr System::Int8 er_FD_ExprTypeMis = System::Int8(0x68);
static constexpr System::Int8 er_FD_ExprIncorrect = System::Int8(0x69);
static constexpr System::Int8 er_FD_InvalidKeywordUse = System::Int8(0x6a);
static constexpr System::Int8 er_FD_ExprInvalidChar = System::Int8(0x6b);
static constexpr System::Int8 er_FD_ExprNameError = System::Int8(0x6c);
static constexpr System::Int8 er_FD_ExprStringError = System::Int8(0x6d);
static constexpr System::Int8 er_FD_ExprNoLParen = System::Int8(0x6e);
static constexpr System::Int8 er_FD_ExprNoRParenOrComma = System::Int8(0x6f);
static constexpr System::Int8 er_FD_ExprNoRParen = System::Int8(0x70);
static constexpr System::Int8 er_FD_ExprEmptyInList = System::Int8(0x71);
static constexpr System::Int8 er_FD_ExprExpected = System::Int8(0x72);
static constexpr System::Int8 er_FD_ExprNoArith = System::Int8(0x73);
static constexpr System::Int8 er_FD_ExprBadScope = System::Int8(0x74);
static constexpr System::Int8 er_FD_ExprEmpty = System::Int8(0x75);
static constexpr System::Int8 er_FD_ExprEvalError = System::Int8(0x76);
static constexpr System::Byte er_FD_DSNoBookmark = System::Byte(0xc8);
static constexpr System::Byte er_FD_DSViewNotSorted = System::Byte(0xc9);
static constexpr System::Byte er_FD_DSNoAdapter = System::Byte(0xca);
static constexpr System::Byte er_FD_DSNoNestedMasterSource = System::Byte(0xcb);
static constexpr System::Byte er_FD_DSCircularDataLink = System::Byte(0xcc);
static constexpr System::Byte er_FD_DSRefreshError = System::Byte(0xcd);
static constexpr System::Byte er_FD_DSNoDataTable = System::Byte(0xce);
static constexpr System::Byte er_FD_DSIndNotFound = System::Byte(0xcf);
static constexpr System::Byte er_FD_DSAggNotFound = System::Byte(0xd0);
static constexpr System::Byte er_FD_DSIndNotComplete = System::Byte(0xd1);
static constexpr System::Byte er_FD_DSAggNotComplete = System::Byte(0xd2);
static constexpr System::Byte er_FD_DSCantUnidir = System::Byte(0xd3);
static constexpr System::Byte er_FD_DSIncompatBmkFields = System::Byte(0xd4);
static constexpr System::Byte er_FD_DSCantEdit = System::Byte(0xd5);
static constexpr System::Byte er_FD_DSCantInsert = System::Byte(0xd6);
static constexpr System::Byte er_FD_DSCantDelete = System::Byte(0xd7);
static constexpr System::Byte er_FD_DSFieldNotFound = System::Byte(0xd8);
static constexpr System::Byte er_FD_DSCantOffline = System::Byte(0xd9);
static constexpr System::Byte er_FD_DSCantOffCachedUpdates = System::Byte(0xda);
static constexpr System::Byte er_FD_DefCircular = System::Byte(0xfa);
static constexpr System::Byte er_FD_DefRO = System::Byte(0xfb);
static constexpr System::Byte er_FD_DefCantMakePers = System::Byte(0xfc);
static constexpr System::Byte er_FD_DefAlreadyLoaded = System::Byte(0xfd);
static constexpr System::Byte er_FD_DefNotExists = System::Byte(0xfe);
static constexpr System::Byte er_FD_DefDupName = System::Byte(0xff);
static constexpr System::Word er_FD_AccSrvNotFound = System::Word(0x12c);
static constexpr System::Word er_FD_AccCannotReleaseDrv = System::Word(0x12d);
static constexpr System::Word er_FD_AccSrvMBConnected = System::Word(0x12e);
static constexpr System::Word er_FD_AccCapabilityNotSup = System::Word(0x12f);
static constexpr System::Word er_FD_AccTxMBActive = System::Word(0x130);
static constexpr System::Word er_FD_AccCantChngCommandState = System::Word(0x131);
static constexpr System::Word er_FD_AccCommandMBFilled = System::Word(0x132);
static constexpr System::Word er_FD_AccEscapeEmptyName = System::Word(0x133);
static constexpr System::Word er_FD_AccCmdMHRowSet = System::Word(0x134);
static constexpr System::Word er_FD_AccCmdMBPrepared = System::Word(0x135);
static constexpr System::Word er_FD_AccCantExecCmdWithRowSet = System::Word(0x136);
static constexpr System::Word er_FD_AccCmdMBOpen4Fetch = System::Word(0x137);
static constexpr System::Word er_FD_AccExactMismatch = System::Word(0x138);
static constexpr System::Word er_FD_AccMetaInfoMismatch = System::Word(0x139);
static constexpr System::Word er_FD_AccCantLoadLibrary = System::Word(0x13a);
static constexpr System::Word er_FD_AccCantGetLibraryEntry = System::Word(0x13b);
static constexpr System::Word er_FD_AccSrvMBDisConnected = System::Word(0x13c);
static constexpr System::Word er_FD_AccToManyLogins = System::Word(0x13d);
static constexpr System::Word er_FD_AccTxMBInActive = System::Word(0x13e);
static constexpr System::Word er_FD_AccDrvMngrMB = System::Word(0x140);
static constexpr System::Word er_FD_AccPrepMissed = System::Word(0x141);
static constexpr System::Word er_FD_AccPrepTooLongIdent = System::Word(0x143);
static constexpr System::Word er_FD_AccParamArrayMismatch = System::Word(0x145);
static constexpr System::Word er_FD_AccAsyncOperInProgress = System::Word(0x146);
static constexpr System::Word er_FD_AccEscapeIsnotSupported = System::Word(0x147);
static constexpr System::Word er_FD_AccMetaInfoReset = System::Word(0x148);
static constexpr System::Word er_FD_AccWhereIsEmpty = System::Word(0x149);
static constexpr System::Word er_FD_AccUpdateTabUndefined = System::Word(0x14a);
static constexpr System::Word er_FD_AccNameHasErrors = System::Word(0x14b);
static constexpr System::Word er_FD_AccEscapeBadSyntax = System::Word(0x14c);
static constexpr System::Word er_FD_AccShutdownTO = System::Word(0x14e);
static constexpr System::Word er_FD_AccParTypeUnknown = System::Word(0x14f);
static constexpr System::Word er_FD_AccParDataMapNotSup = System::Word(0x150);
static constexpr System::Word er_FD_AccParDefChanged = System::Word(0x152);
static constexpr System::Word er_FD_AccMetaInfoNotDefined = System::Word(0x153);
static constexpr System::Word er_FD_AccSrvNotDefined = System::Word(0x154);
static constexpr System::Word er_FD_AccArrayExecError = System::Word(0x155);
static constexpr System::Word er_FD_AccCantAssignTxIntf = System::Word(0x157);
static constexpr System::Word er_FD_AccParSetChanged = System::Word(0x158);
static constexpr System::Word er_FD_AccDataToLarge = System::Word(0x159);
static constexpr System::Word er_FD_AccDbNotExists = System::Word(0x15a);
static constexpr System::Word er_FD_AccClassNotRegistered = System::Word(0x15b);
static constexpr System::Word er_FD_AccSysClassNotRegistered = System::Word(0x15c);
static constexpr System::Word er_FD_AccUnrecognizedDbFormat = System::Word(0x15d);
static constexpr System::Word er_FD_AccNotValidPassword = System::Word(0x15e);
static constexpr System::Word er_FD_AccUnknownOleError = System::Word(0x15f);
static constexpr System::Word er_FD_AccUnsupParamObjValue = System::Word(0x160);
static constexpr System::Word er_FD_AccUnsupColumnType = System::Word(0x161);
static constexpr System::Word er_FD_AccLongDataStream = System::Word(0x162);
static constexpr System::Word er_FD_AccArrayDMLWithIntStr = System::Word(0x163);
static constexpr System::Word er_FD_SvcLinkMBSet = System::Word(0x172);
static constexpr System::Word er_FD_SvcMBActive = System::Word(0x173);
static constexpr System::Word er_FD_SvcCannotUninstall = System::Word(0x174);
static constexpr System::Word er_FD_DAptRecordIsDeleted = System::Word(0x190);
static constexpr System::Word er_FD_DAptNoSelectCmd = System::Word(0x192);
static constexpr System::Word er_FD_DAptRecordIsChanged = System::Word(0x193);
static constexpr System::Word er_FD_DAptApplyUpdateFailed = System::Word(0x194);
static constexpr System::Word er_FD_DAptCantEdit = System::Word(0x195);
static constexpr System::Word er_FD_DAptCantInsert = System::Word(0x196);
static constexpr System::Word er_FD_DAptCantDelete = System::Word(0x197);
static constexpr System::Word er_FD_ClntSessMBSingle = System::Word(0x1f4);
static constexpr System::Word er_FD_ClntSessMBInactive = System::Word(0x1f5);
static constexpr System::Word er_FD_ClntSessMBActive = System::Word(0x1f6);
static constexpr System::Word er_FD_ClntDbDupName = System::Word(0x1f7);
static constexpr System::Word er_FD_ClntDbMBInactive = System::Word(0x1f8);
static constexpr System::Word er_FD_ClntDbMBActive = System::Word(0x1f9);
static constexpr System::Word er_FD_ClntDbLoginAborted = System::Word(0x1fa);
static constexpr System::Word er_FD_ClntDbCantConnPooled = System::Word(0x1fb);
static constexpr System::Word er_FD_ClntDBNotFound = System::Word(0x1fc);
static constexpr System::Word er_FD_ClntAdaptMBActive = System::Word(0x1fd);
static constexpr System::Word er_FD_ClntAdaptMBInactive = System::Word(0x1fe);
static constexpr System::Word er_FD_ClntNotCachedUpdates = System::Word(0x1ff);
static constexpr System::Word er_FD_ClntDbNotDefined = System::Word(0x200);
static constexpr System::Word er_FD_ClntDbMBOnline = System::Word(0x201);
static constexpr System::Word er_FD_ClntTxMBActive = System::Word(0x202);
static constexpr System::Word er_FD_ClntCantShareAdapt = System::Word(0x203);
static constexpr System::Word er_FD_ClntConnNotMatch = System::Word(0x204);
static constexpr System::Word er_FD_ClntPKNotFound = System::Word(0x205);
static constexpr System::Word er_FD_ClntLocalSQLMisuse = System::Word(0x206);
static constexpr System::Word er_FD_ClntWrongIndex = System::Word(0x207);
static constexpr System::Word er_FD_ClntDSNameEmpty = System::Word(0x208);
static constexpr System::Word er_FD_ClntDSNameNotUnique = System::Word(0x209);
static constexpr System::Word er_FD_ClntDataSetParamIncompat = System::Word(0x20a);
static constexpr System::Word er_FD_DPNoTxtFld = System::Word(0x258);
static constexpr System::Word er_FD_DPNoSrcDS = System::Word(0x259);
static constexpr System::Word er_FD_DPNoDestDS = System::Word(0x25a);
static constexpr System::Word er_FD_DPNoTxtDest = System::Word(0x25b);
static constexpr System::Word er_FD_DPNoTxtSrc = System::Word(0x25c);
static constexpr System::Word er_FD_DPBadFixedSize = System::Word(0x25d);
static constexpr System::Word er_FD_DPTxtFldDup = System::Word(0x25e);
static constexpr System::Word er_FD_DPBadTextFmt = System::Word(0x25f);
static constexpr System::Word er_FD_DPSrcUndefined = System::Word(0x260);
static constexpr System::Word er_FD_DPDestNoKeyFields = System::Word(0x261);
static constexpr System::Word er_FD_DPNoSQLTab = System::Word(0x262);
static constexpr System::Word er_FD_DPNoSQLBatch = System::Word(0x263);
static constexpr System::Word er_FD_DPNoTxtFlds = System::Word(0x264);
static constexpr System::Word er_FD_DPNoJsonDest = System::Word(0x265);
static constexpr System::Word er_FD_DPNoJsonSrc = System::Word(0x266);
static constexpr System::Word er_FD_DPNoJsonFld = System::Word(0x267);
static constexpr System::Word er_FD_DPJsonFldDup = System::Word(0x268);
static constexpr System::Word er_FD_DPMapUndefined = System::Word(0x269);
static constexpr System::Word er_FD_StanTimeout = System::Word(0x2bc);
static constexpr System::Word er_FD_StanCantGetBlob = System::Word(0x2bd);
static constexpr System::Word er_FD_StanCantNonblocking = System::Word(0x2c1);
static constexpr System::Word er_FD_StanMacroNotFound = System::Word(0x2c2);
static constexpr System::Word er_FD_StanBadParRowIndex = System::Word(0x2c3);
static constexpr System::Word er_FD_StanPoolTooManyItems = System::Word(0x2c4);
static constexpr System::Word er_FD_StanStrgInvBinFmt = System::Word(0x2c6);
static constexpr System::Word er_FD_StanStrgCantReadProp = System::Word(0x2c7);
static constexpr System::Word er_FD_StanStrgCantReadObj = System::Word(0x2c8);
static constexpr System::Word er_FD_StanStrgCantReadCDATA = System::Word(0x2c9);
static constexpr System::Word er_FD_StanStrgDictOverflow = System::Word(0x2ca);
static constexpr System::Word er_FD_StanStrgClassUnknown = System::Word(0x2cb);
static constexpr System::Word er_FD_StanStrgUnknownFmt = System::Word(0x2cc);
static constexpr System::Word er_FD_StanStrgFileError = System::Word(0x2cd);
static constexpr System::Word er_FD_StanStrgInvDIntFmt = System::Word(0x2ce);
static constexpr System::Word er_FD_StanStrgInvJSONFmt = System::Word(0x2cf);
static constexpr System::Word er_FD_ScrCantExecHostCmd = System::Word(0x320);
static constexpr System::Word er_FD_ScrStrSize1 = System::Word(0x321);
static constexpr System::Word er_FD_ScrStrNotAlphaNum = System::Word(0x322);
static constexpr System::Word er_FD_ScrSetArgInvalid = System::Word(0x323);
static constexpr System::Word er_FD_ScrInvalidSyntax = System::Word(0x324);
static constexpr System::Word er_FD_ScrAccMustSpecVar = System::Word(0x325);
static constexpr System::Word er_FD_ScrDefReqValue = System::Word(0x326);
static constexpr System::Word er_FD_ScrVarMissedCloseBrace = System::Word(0x327);
static constexpr System::Word er_FD_ScrVarUnsupType = System::Word(0x328);
static constexpr System::Word er_FD_ScrNotLogged = System::Word(0x329);
static constexpr System::Word er_FD_ScrNoCmds = System::Word(0x32a);
static constexpr System::Word er_FD_ScrNoScript = System::Word(0x32b);
static constexpr System::Word er_FD_DBXGeneral = System::Word(0x3e8);
static constexpr System::Word er_FD_DBXParMBNotEmpty = System::Word(0x3e9);
static constexpr System::Word er_FD_DBXNoDriverCfg = System::Word(0x3ea);
static constexpr System::Word er_FD_MySQLGeneral = System::Word(0x44c);
static constexpr System::Word er_FD_MySQLBadVersion = System::Word(0x44d);
static constexpr System::Word er_FD_MySQLCantSetPort = System::Word(0x44e);
static constexpr System::Word er_FD_MySQLBadParams = System::Word(0x44f);
static constexpr System::Word er_FD_MySQLCantInitEmbeddedServer = System::Word(0x450);
static constexpr System::Word er_FD_MySQLFieldDataTypeUnsup = System::Word(0x451);
static constexpr System::Word er_FD_OdbcGeneral = System::Word(0x4b0);
static constexpr System::Word er_FD_OdbcVarDataTypeUnsup = System::Word(0x4b1);
static constexpr System::Word er_FD_OraGeneral = System::Word(0x514);
static constexpr System::Word er_FD_OraCantSetCharset = System::Word(0x515);
static constexpr System::Word er_FD_OraNoCursor = System::Word(0x519);
static constexpr System::Word er_FD_OraCantAssFILE = System::Word(0x51b);
static constexpr System::Word er_FD_OraNoCursorParams = System::Word(0x51c);
static constexpr System::Word er_FD_OraNotInstalled = System::Word(0x51d);
static constexpr System::Word er_FD_OraBadVersion = System::Word(0x51e);
static constexpr System::Word er_FD_OraBadValueType = System::Word(0x523);
static constexpr System::Word er_FD_OraBadVarType = System::Word(0x527);
static constexpr System::Word er_FD_OraTooLongGTRID = System::Word(0x52b);
static constexpr System::Word er_FD_OraTooLongBQUAL = System::Word(0x52c);
static constexpr System::Word er_FD_OraTooLongTXName = System::Word(0x52d);
static constexpr System::Word er_FD_OraDBTNManyClBraces = System::Word(0x52e);
static constexpr System::Word er_FD_OraNotPLSQLObj = System::Word(0x52f);
static constexpr System::Word er_FD_OraNotPackageProc = System::Word(0x531);
static constexpr System::Word er_FD_OraBadTableType = System::Word(0x532);
static constexpr System::Word er_FD_OraUnNamedRecParam = System::Word(0x533);
static constexpr System::Word er_FD_OraCantConvNum = System::Word(0x534);
static constexpr System::Word er_FD_OraPipeAlertToMany = System::Word(0x535);
static constexpr System::Word er_FD_IBGeneral = System::Word(0x578);
static constexpr System::Word er_FD_IBTraceIsActive = System::Word(0x579);
static constexpr System::Word er_FD_PgGeneral = System::Word(0x5dc);
static constexpr System::Word er_FD_PgProcNotFound = System::Word(0x5dd);
static constexpr System::Word er_FD_PgMultiDimArrNotSup = System::Word(0x5de);
static constexpr System::Word er_FD_PgUnsupArrValueTypeNotSup = System::Word(0x5df);
static constexpr System::Word er_FD_PgArrIndexOutOfBound = System::Word(0x5e0);
static constexpr System::Word er_FD_PgCannotDescribeType = System::Word(0x5e1);
static constexpr System::Word er_FD_PgIsNotArray = System::Word(0x5e2);
static constexpr System::Word er_FD_PgUnsupTextType = System::Word(0x5e3);
static constexpr System::Word er_FD_SQLiteGeneral = System::Word(0x640);
static constexpr System::Word er_FD_SQLiteInitFailed = System::Word(0x641);
static constexpr System::Word er_FD_SQLiteAlgFailure = System::Word(0x642);
static constexpr System::Word er_FD_SQLitePwdInvalid = System::Word(0x643);
static constexpr System::Word er_FD_SQLiteDBUnencrypted = System::Word(0x644);
static constexpr System::Word er_FD_SQLiteDBNotFound = System::Word(0x645);
static constexpr System::Word er_FD_SQLiteLinkageNotSupported = System::Word(0x646);
static constexpr System::Word er_FD_SQLiteVTabInvalidArgs = System::Word(0x672);
static constexpr System::Word er_FD_SQLiteVTabDSNotFoundOrEmpty = System::Word(0x673);
static constexpr System::Word er_FD_SQLiteVTabDSNotSupported = System::Word(0x674);
static constexpr System::Word er_FD_SQLiteVTabDSSPNotFound = System::Word(0x675);
static constexpr System::Word er_FD_SQLiteVTabDSDataModFailed = System::Word(0x676);
static constexpr System::Word er_FD_SQLiteVTabDSRowidInvalid = System::Word(0x677);
static constexpr System::Word er_FD_SQLiteVTabDSChangedOrFreed = System::Word(0x678);
static constexpr System::Word er_FD_SQLiteVTabDSNoRowExists = System::Word(0x679);
static constexpr System::Word er_FD_SQLiteVTabDSCursorInvalid = System::Word(0x67a);
static constexpr System::Word er_FD_SQLiteVTabCannotAttach = System::Word(0x67b);
static constexpr System::Word er_FD_SQLiteVTabDataSetBusy = System::Word(0x67c);
static constexpr System::Word er_FD_ASAGeneral = System::Word(0x6a4);
static constexpr System::Word er_FD_ASADBToolNotFound = System::Word(0x6a5);
static constexpr System::Word er_FD_ADSGeneral = System::Word(0x708);
static constexpr System::Word er_FD_NexusGeneral = System::Word(0x76c);
static constexpr System::Word er_FD_MSSQLGeneral = System::Word(0x7d0);
static constexpr System::Word er_FD_MSSQLFSNoTx = System::Word(0x7d1);
static constexpr System::Word er_FD_MSSQLFSNoPath = System::Word(0x7d2);
static constexpr System::Word er_FD_MSSQLFSIOError = System::Word(0x7d3);
static constexpr System::Word er_FD_MSSQLQNSubError = System::Word(0x7d4);
static constexpr System::Word er_FD_MongoGeneral = System::Word(0x834);
static constexpr System::Word er_FD_MongoError = System::Word(0x835);
static constexpr System::Word er_FD_MongoBadURI = System::Word(0x836);
static constexpr System::Word er_FD_MongoDocReadOnly = System::Word(0x837);
static constexpr System::Word er_FD_MongoFailedInitBSON = System::Word(0x838);
static constexpr System::Word er_FD_MongoBulkError = System::Word(0x839);
static constexpr System::Word er_FD_MongoCursorError = System::Word(0x83a);
static constexpr System::Word er_FD_MongoExecuteError = System::Word(0x83b);
static constexpr System::Word er_FD_MongoDBRefInvalid = System::Word(0x83c);
static constexpr System::Word er_FD_MongoDBRefNotFound = System::Word(0x83d);
static constexpr System::Word er_FD_MongoCannotOpenDataSet = System::Word(0x83e);
static constexpr System::Word er_FD_MongoFieldTypeMismatch = System::Word(0x83f);
static constexpr System::Word er_FD_MongoFieldIsNotFound = System::Word(0x840);
static constexpr System::Word er_FD_MongoAlertToMany = System::Word(0x841);
}	/* namespace Consts */
}	/* namespace Stan */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_STAN_CONSTS)
using namespace Firedac::Stan::Consts;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_STAN)
using namespace Firedac::Stan;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Stan_ConstsHPP
