// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.SqlConst.pas' rev: 34.00 (Windows)

#ifndef Data_SqlconstHPP
#define Data_SqlconstHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Sqlconst
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
#define DRIVERS_KEY L"Installed Drivers"
#define CONNECTIONS_KEY L"Installed Connections"
#define DRIVERNAME_KEY L"DriverName"
#define HOSTNAME_KEY L"HostName"
#define ROLENAME_KEY L"RoleName"
#define DATABASENAME_KEY L"Database"
#define MAXBLOBSIZE_KEY L"BlobSize"
#define VENDORLIB_KEY L"VendorLib"
#define DLLLIB_KEY L"LibraryName"
#define GETDRIVERFUNC_KEY L"GetDriverFunc"
#define AUTOCOMMIT_KEY L"AutoCommit"
#define BLOCKINGMODE_KEY L"BlockingMode"
#define WAITONLOCKS_KEY L"WaitOnLocks"
#define COMMITRETAIN_KEY L"CommitRetain"
#define TRANSISOLATION_KEY L"%s TransIsolation"
#define SQLDIALECT_KEY L"SqlDialect"
#define SQLLOCALE_CODE_KEY L"LocaleCode"
#define ERROR_RESOURCE_KEY L"ErrorResourceFile"
#define SQLSERVER_CHARSET_KEY L"ServerCharSet"
#define CONNECTION_STRING L"ConnectionString"
#define SREADCOMMITTED L"readcommitted"
#define SREPEATREAD L"repeatableread"
#define SDIRTYREAD L"dirtyread"
#define szPASSWORD L"PASSWORD"
#define SLocaleCode L"LCID"
#define ROWSETSIZE_KEY L"RowsetSize"
#define OSAUTHENTICATION L"OS Authentication"
#define SERVERPORT L"Server Port"
#define MULTITRANSENABLED L"Multiple Transaction"
#define TRIMCHAR L"Trim Char"
#define CUSTOM_INFO L"Custom String"
#define CONN_TIMEOUT L"Connection Timeout"
#define TDSPACKETSIZE L"TDS Packet Size"
#define CLIENTHOSTNAME L"Client HostName"
#define CLIENTAPPNAME L"Client AppName"
#define COMPRESSED L"Compressed"
#define ENCRYPTED L"Encrypted"
#define PREPARESQL L"Prepare SQL"
extern DELPHI_PACKAGE System::ResourceString _SLoginError;
#define Data_Sqlconst_SLoginError System::LoadResourceString(&Data::Sqlconst::_SLoginError)
extern DELPHI_PACKAGE System::ResourceString _SMonitorActive;
#define Data_Sqlconst_SMonitorActive System::LoadResourceString(&Data::Sqlconst::_SMonitorActive)
extern DELPHI_PACKAGE System::ResourceString _SMissingConnection;
#define Data_Sqlconst_SMissingConnection System::LoadResourceString(&Data::Sqlconst::_SMissingConnection)
extern DELPHI_PACKAGE System::ResourceString _SDatabaseOpen;
#define Data_Sqlconst_SDatabaseOpen System::LoadResourceString(&Data::Sqlconst::_SDatabaseOpen)
extern DELPHI_PACKAGE System::ResourceString _SDatabaseClosed;
#define Data_Sqlconst_SDatabaseClosed System::LoadResourceString(&Data::Sqlconst::_SDatabaseClosed)
extern DELPHI_PACKAGE System::ResourceString _SMissingSQLConnection;
#define Data_Sqlconst_SMissingSQLConnection System::LoadResourceString(&Data::Sqlconst::_SMissingSQLConnection)
extern DELPHI_PACKAGE System::ResourceString _SConnectionNameMissing;
#define Data_Sqlconst_SConnectionNameMissing System::LoadResourceString(&Data::Sqlconst::_SConnectionNameMissing)
extern DELPHI_PACKAGE System::ResourceString _SEmptySQLStatement;
#define Data_Sqlconst_SEmptySQLStatement System::LoadResourceString(&Data::Sqlconst::_SEmptySQLStatement)
extern DELPHI_PACKAGE System::ResourceString _SNoParameterValue;
#define Data_Sqlconst_SNoParameterValue System::LoadResourceString(&Data::Sqlconst::_SNoParameterValue)
extern DELPHI_PACKAGE System::ResourceString _SNoParameterType;
#define Data_Sqlconst_SNoParameterType System::LoadResourceString(&Data::Sqlconst::_SNoParameterType)
extern DELPHI_PACKAGE System::ResourceString _SParameterTypes;
#define Data_Sqlconst_SParameterTypes System::LoadResourceString(&Data::Sqlconst::_SParameterTypes)
extern DELPHI_PACKAGE System::ResourceString _SDataTypes;
#define Data_Sqlconst_SDataTypes System::LoadResourceString(&Data::Sqlconst::_SDataTypes)
extern DELPHI_PACKAGE System::ResourceString _SResultName;
#define Data_Sqlconst_SResultName System::LoadResourceString(&Data::Sqlconst::_SResultName)
extern DELPHI_PACKAGE System::ResourceString _SNoTableName;
#define Data_Sqlconst_SNoTableName System::LoadResourceString(&Data::Sqlconst::_SNoTableName)
extern DELPHI_PACKAGE System::ResourceString _SNoSqlStatement;
#define Data_Sqlconst_SNoSqlStatement System::LoadResourceString(&Data::Sqlconst::_SNoSqlStatement)
extern DELPHI_PACKAGE System::ResourceString _SNoDataSetField;
#define Data_Sqlconst_SNoDataSetField System::LoadResourceString(&Data::Sqlconst::_SNoDataSetField)
extern DELPHI_PACKAGE System::ResourceString _SNoCachedUpdates;
#define Data_Sqlconst_SNoCachedUpdates System::LoadResourceString(&Data::Sqlconst::_SNoCachedUpdates)
extern DELPHI_PACKAGE System::ResourceString _SMissingDataBaseName;
#define Data_Sqlconst_SMissingDataBaseName System::LoadResourceString(&Data::Sqlconst::_SMissingDataBaseName)
extern DELPHI_PACKAGE System::ResourceString _SMissingDataSet;
#define Data_Sqlconst_SMissingDataSet System::LoadResourceString(&Data::Sqlconst::_SMissingDataSet)
extern DELPHI_PACKAGE System::ResourceString _SMissingDriverName;
#define Data_Sqlconst_SMissingDriverName System::LoadResourceString(&Data::Sqlconst::_SMissingDriverName)
extern DELPHI_PACKAGE System::ResourceString _SPrepareError;
#define Data_Sqlconst_SPrepareError System::LoadResourceString(&Data::Sqlconst::_SPrepareError)
extern DELPHI_PACKAGE System::ResourceString _SObjectNameError;
#define Data_Sqlconst_SObjectNameError System::LoadResourceString(&Data::Sqlconst::_SObjectNameError)
extern DELPHI_PACKAGE System::ResourceString _SSQLDataSetOpen;
#define Data_Sqlconst_SSQLDataSetOpen System::LoadResourceString(&Data::Sqlconst::_SSQLDataSetOpen)
extern DELPHI_PACKAGE System::ResourceString _SNoActiveTrans;
#define Data_Sqlconst_SNoActiveTrans System::LoadResourceString(&Data::Sqlconst::_SNoActiveTrans)
extern DELPHI_PACKAGE System::ResourceString _SActiveTrans;
#define Data_Sqlconst_SActiveTrans System::LoadResourceString(&Data::Sqlconst::_SActiveTrans)
extern DELPHI_PACKAGE System::ResourceString _SDllLoadError;
#define Data_Sqlconst_SDllLoadError System::LoadResourceString(&Data::Sqlconst::_SDllLoadError)
extern DELPHI_PACKAGE System::ResourceString _SDllProcLoadError;
#define Data_Sqlconst_SDllProcLoadError System::LoadResourceString(&Data::Sqlconst::_SDllProcLoadError)
extern DELPHI_PACKAGE System::ResourceString _SConnectionEditor;
#define Data_Sqlconst_SConnectionEditor System::LoadResourceString(&Data::Sqlconst::_SConnectionEditor)
extern DELPHI_PACKAGE System::ResourceString _SAddConnectionString;
#define Data_Sqlconst_SAddConnectionString System::LoadResourceString(&Data::Sqlconst::_SAddConnectionString)
extern DELPHI_PACKAGE System::ResourceString _SRefreshConnectionString;
#define Data_Sqlconst_SRefreshConnectionString System::LoadResourceString(&Data::Sqlconst::_SRefreshConnectionString)
extern DELPHI_PACKAGE System::ResourceString _SRemoveConnectionString;
#define Data_Sqlconst_SRemoveConnectionString System::LoadResourceString(&Data::Sqlconst::_SRemoveConnectionString)
extern DELPHI_PACKAGE System::ResourceString _SCommandTextEditor;
#define Data_Sqlconst_SCommandTextEditor System::LoadResourceString(&Data::Sqlconst::_SCommandTextEditor)
extern DELPHI_PACKAGE System::ResourceString _SMissingDLLName;
#define Data_Sqlconst_SMissingDLLName System::LoadResourceString(&Data::Sqlconst::_SMissingDLLName)
extern DELPHI_PACKAGE System::ResourceString _SMissingDriverRegFile;
#define Data_Sqlconst_SMissingDriverRegFile System::LoadResourceString(&Data::Sqlconst::_SMissingDriverRegFile)
extern DELPHI_PACKAGE System::ResourceString _STableNameNotFound;
#define Data_Sqlconst_STableNameNotFound System::LoadResourceString(&Data::Sqlconst::_STableNameNotFound)
extern DELPHI_PACKAGE System::ResourceString _SNoCursor;
#define Data_Sqlconst_SNoCursor System::LoadResourceString(&Data::Sqlconst::_SNoCursor)
extern DELPHI_PACKAGE System::ResourceString _SMetaDataOpenError;
#define Data_Sqlconst_SMetaDataOpenError System::LoadResourceString(&Data::Sqlconst::_SMetaDataOpenError)
extern DELPHI_PACKAGE System::ResourceString _SErrorMappingError;
#define Data_Sqlconst_SErrorMappingError System::LoadResourceString(&Data::Sqlconst::_SErrorMappingError)
extern DELPHI_PACKAGE System::ResourceString _SStoredProcsNotSupported;
#define Data_Sqlconst_SStoredProcsNotSupported System::LoadResourceString(&Data::Sqlconst::_SStoredProcsNotSupported)
extern DELPHI_PACKAGE System::ResourceString _SPackagesNotSupported;
#define Data_Sqlconst_SPackagesNotSupported System::LoadResourceString(&Data::Sqlconst::_SPackagesNotSupported)
extern DELPHI_PACKAGE System::ResourceString _STooManyActualParam;
#define Data_Sqlconst_STooManyActualParam System::LoadResourceString(&Data::Sqlconst::_STooManyActualParam)
extern DELPHI_PACKAGE System::ResourceString _SDBXUNKNOWNERROR;
#define Data_Sqlconst_SDBXUNKNOWNERROR System::LoadResourceString(&Data::Sqlconst::_SDBXUNKNOWNERROR)
extern DELPHI_PACKAGE System::ResourceString _SNOTSUPPORTED;
#define Data_Sqlconst_SNOTSUPPORTED System::LoadResourceString(&Data::Sqlconst::_SNOTSUPPORTED)
extern DELPHI_PACKAGE System::ResourceString _SDBXError;
#define Data_Sqlconst_SDBXError System::LoadResourceString(&Data::Sqlconst::_SDBXError)
extern DELPHI_PACKAGE System::ResourceString _SSQLServerError;
#define Data_Sqlconst_SSQLServerError System::LoadResourceString(&Data::Sqlconst::_SSQLServerError)
extern DELPHI_PACKAGE System::ResourceString _SConfFileMoveError;
#define Data_Sqlconst_SConfFileMoveError System::LoadResourceString(&Data::Sqlconst::_SConfFileMoveError)
extern DELPHI_PACKAGE System::ResourceString _SMissingConfFile;
#define Data_Sqlconst_SMissingConfFile System::LoadResourceString(&Data::Sqlconst::_SMissingConfFile)
extern DELPHI_PACKAGE System::ResourceString _SObjectViewNotTrue;
#define Data_Sqlconst_SObjectViewNotTrue System::LoadResourceString(&Data::Sqlconst::_SObjectViewNotTrue)
extern DELPHI_PACKAGE System::ResourceString _SObjectTypenameRequired;
#define Data_Sqlconst_SObjectTypenameRequired System::LoadResourceString(&Data::Sqlconst::_SObjectTypenameRequired)
extern DELPHI_PACKAGE System::ResourceString _SCannotCreateFile;
#define Data_Sqlconst_SCannotCreateFile System::LoadResourceString(&Data::Sqlconst::_SCannotCreateFile)
extern DELPHI_PACKAGE System::ResourceString _SDlgOpenCaption;
#define Data_Sqlconst_SDlgOpenCaption System::LoadResourceString(&Data::Sqlconst::_SDlgOpenCaption)
extern DELPHI_PACKAGE System::ResourceString _SDlgFilterTxt;
#define Data_Sqlconst_SDlgFilterTxt System::LoadResourceString(&Data::Sqlconst::_SDlgFilterTxt)
extern DELPHI_PACKAGE System::ResourceString _SLogFileFilter;
#define Data_Sqlconst_SLogFileFilter System::LoadResourceString(&Data::Sqlconst::_SLogFileFilter)
extern DELPHI_PACKAGE System::ResourceString _SCircularProvider;
#define Data_Sqlconst_SCircularProvider System::LoadResourceString(&Data::Sqlconst::_SCircularProvider)
extern DELPHI_PACKAGE System::ResourceString _SUnknownDataType;
#define Data_Sqlconst_SUnknownDataType System::LoadResourceString(&Data::Sqlconst::_SUnknownDataType)
extern DELPHI_PACKAGE System::ResourceString _SSaveConnectionParams;
#define Data_Sqlconst_SSaveConnectionParams System::LoadResourceString(&Data::Sqlconst::_SSaveConnectionParams)
extern DELPHI_PACKAGE System::ResourceString _SReloadConnectionParams;
#define Data_Sqlconst_SReloadConnectionParams System::LoadResourceString(&Data::Sqlconst::_SReloadConnectionParams)
extern DELPHI_PACKAGE System::ResourceString _SGenerateClientClasses;
#define Data_Sqlconst_SGenerateClientClasses System::LoadResourceString(&Data::Sqlconst::_SGenerateClientClasses)
}	/* namespace Sqlconst */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_SQLCONST)
using namespace Data::Sqlconst;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_SqlconstHPP
