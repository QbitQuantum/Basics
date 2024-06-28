// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.ADSCli.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_AdscliHPP
#define Firedac_Phys_AdscliHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <FireDAC.Stan.Consts.hpp>
#include <FireDAC.Stan.Intf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Adscli
{
//-- forward type declarations -----------------------------------------------
struct TADSTimeStamp;
struct ADS_MGMT_COMM_STATS;
struct ADS_MGMT_CONFIG_PARAMS;
struct ADS_MGMT_CONFIG_MEMORY;
struct ADS_MGMT_INSTALL_INFO;
struct ADS_MGMT_UPTIME_INFO;
struct ADS_MGMT_USAGE_INFO;
struct ADS_MGMT_ACTIVITY_INFO;
struct ADS_MGMT_USER_INFO;
struct ADS_MGMT_TABLE_INFO;
struct ADS_MGMT_INDEX_INFO;
struct ADS_MGMT_RECORD_INFO;
struct ADS_MGMT_THREAD_ACTIVITY;
struct ADS_GUID_DATA;
struct ADD_FIELD_DESC;
//-- type declarations -------------------------------------------------------
typedef unsigned __int64 UNSIGNED64;

typedef __int64 SIGNED64;

typedef unsigned UNSIGNED32;

typedef int SIGNED32;

typedef System::Word UNSIGNED16;

typedef short SIGNED16;

typedef System::Byte UNSIGNED8;

typedef System::Int8 SIGNED8;

typedef unsigned __int64 *PUNSIGNED64;

typedef __int64 *PSIGNED64;

typedef unsigned *PUNSIGNED32;

typedef int *PSIGNED32;

typedef System::Word *PUNSIGNED16;

typedef short *PSIGNED16;

typedef System::Byte *PUNSIGNED8;

typedef System::Int8 *PSIGNED8;

typedef System::WideChar * *PPWideChar;

typedef System::Int8 AceChar;

typedef System::Int8 *PAceChar;

typedef System::Byte AceBinary;

typedef System::Byte *PAceBinary;

typedef NativeUInt ADSHANDLE;

typedef NativeUInt *PADSHANDLE;

struct DECLSPEC_DRECORD TADSTimeStamp
{
public:
	int lDate;
	int lTime;
};


#pragma pack(push,1)
struct DECLSPEC_DRECORD ADS_MGMT_COMM_STATS
{
public:
	double dPercentCheckSums;
	unsigned ulTotalPackets;
	unsigned ulRcvPktOutOfSeq;
	unsigned ulNotLoggedIn;
	unsigned ulRcvReqOutOfSeq;
	unsigned ulCheckSumFailures;
	unsigned ulDisconnectedUsers;
	unsigned ulPartialConnects;
	unsigned ulInvalidPackets;
	unsigned ulRecvFromErrors;
	unsigned ulSendToErrors;
};
#pragma pack(pop)


typedef ADS_MGMT_COMM_STATS *PADS_MGMT_COMM_STATS;

#pragma pack(push,1)
struct DECLSPEC_DRECORD ADS_MGMT_CONFIG_PARAMS
{
public:
	unsigned ulNumConnections;
	unsigned ulNumWorkAreas;
	unsigned ulNumTables;
	unsigned ulNumIndexes;
	unsigned ulNumLocks;
	unsigned ulUserBufferSize;
	unsigned ulStatDumpInterval;
	unsigned ulErrorLogMax;
	unsigned ulNumTPSHeaderElems;
	unsigned ulNumTPSVisibilityElems;
	unsigned ulNumTPSMemoTransElems;
	System::Word usNumRcvECBs;
	System::Word usNumSendECBs;
	System::Word usNumBurstPackets;
	System::Word usNumWorkerThreads;
	unsigned ulSortBuffSize;
	System::StaticArray<System::Int8, 256> aucErrorLog;
	System::StaticArray<System::Int8, 256> aucSemaphore;
	System::StaticArray<System::Int8, 256> aucTransaction;
	System::Byte ucReserved3;
	System::Byte ucReserved4;
	System::Word usSendIPPort;
	System::Word usReceiveIPPort;
	System::Byte ucUseIPProtocol;
	System::Byte ucFlushEveryUpdate;
	unsigned ulGhostTimeout;
	unsigned ulFlushFrequency;
	unsigned ulKeepAliveTimeOut;
	System::Byte ucDisplayNWLoginNames;
	System::Byte ucUseSemaphoreFiles;
	System::Byte ucUseDynamicAOFs;
	System::Byte ucUseInternet;
	System::Word usInternetPort;
	System::Word usMaxConnFailures;
	unsigned ulInternetKeepAlive;
	System::Word usCompressionLevel;
	unsigned ulNumQueries;
	System::Word usReceiveSSLPort;
};
#pragma pack(pop)


typedef ADS_MGMT_CONFIG_PARAMS *PADS_MGMT_CONFIG_PARAMS;

#pragma pack(push,1)
struct DECLSPEC_DRECORD ADS_MGMT_CONFIG_MEMORY
{
public:
	unsigned ulTotalConfigMem;
	unsigned ulConnectionMem;
	unsigned ulWorkAreaMem;
	unsigned ulTableMem;
	unsigned ulIndexMem;
	unsigned ulLockMem;
	unsigned ulUserBufferMem;
	unsigned ulTPSHeaderElemMem;
	unsigned ulTPSVisibilityElemMem;
	unsigned ulTPSMemoTransElemMem;
	unsigned ulRcvEcbMem;
	unsigned ulSendEcbMem;
	unsigned ulWorkerThreadMem;
	unsigned ulQueryMem;
};
#pragma pack(pop)


typedef ADS_MGMT_CONFIG_MEMORY *PADS_MGMT_CONFIG_MEMORY;

#pragma pack(push,1)
struct DECLSPEC_DRECORD ADS_MGMT_INSTALL_INFO
{
public:
	unsigned ulUserOption;
	System::StaticArray<System::Int8, 36> aucRegisteredOwner;
	System::StaticArray<System::Int8, 16> aucVersionStr;
	System::StaticArray<System::Int8, 16> aucInstallDate;
	System::StaticArray<System::Int8, 16> aucOemCharName;
	System::StaticArray<System::Int8, 16> aucAnsiCharName;
	System::StaticArray<System::Int8, 16> aucEvalExpireDate;
	System::StaticArray<System::Int8, 16> aucSerialNumber;
	unsigned ulMaxStatefulUsers;
	unsigned ulMaxStatelessUsers;
};
#pragma pack(pop)


typedef ADS_MGMT_INSTALL_INFO *PADS_MGMT_INSTALL_INFO;

#pragma pack(push,1)
struct DECLSPEC_DRECORD ADS_MGMT_UPTIME_INFO
{
public:
	System::Word usDays;
	System::Word usHours;
	System::Word usMinutes;
	System::Word usSeconds;
};
#pragma pack(pop)


typedef ADS_MGMT_UPTIME_INFO *PADS_MGMT_UPTIME_INFO;

#pragma pack(push,1)
struct DECLSPEC_DRECORD ADS_MGMT_USAGE_INFO
{
public:
	unsigned ulInUse;
	unsigned ulMaxUsed;
	unsigned ulRejected;
};
#pragma pack(pop)


typedef ADS_MGMT_USAGE_INFO *PADS_MGMT_USAGE_INFO;

#pragma pack(push,1)
struct DECLSPEC_DRECORD ADS_MGMT_ACTIVITY_INFO
{
public:
	unsigned ulOperations;
	unsigned ulLoggedErrors;
	ADS_MGMT_UPTIME_INFO stUpTime;
	ADS_MGMT_USAGE_INFO stUsers;
	ADS_MGMT_USAGE_INFO stConnections;
	ADS_MGMT_USAGE_INFO stWorkAreas;
	ADS_MGMT_USAGE_INFO stTables;
	ADS_MGMT_USAGE_INFO stIndexes;
	ADS_MGMT_USAGE_INFO stLocks;
	ADS_MGMT_USAGE_INFO stTpsHeaderElems;
	ADS_MGMT_USAGE_INFO stTpsVisElems;
	ADS_MGMT_USAGE_INFO stTpsMemoElems;
	ADS_MGMT_USAGE_INFO stWorkerThreads;
	ADS_MGMT_USAGE_INFO stQueries;
	ADS_MGMT_USAGE_INFO stStatefulUsers;
	ADS_MGMT_USAGE_INFO stStatelessUsers;
};
#pragma pack(pop)


typedef ADS_MGMT_ACTIVITY_INFO *PADS_MGMT_ACTIVITY_INFO;

#pragma pack(push,1)
struct DECLSPEC_DRECORD ADS_MGMT_USER_INFO
{
public:
	System::StaticArray<System::Int8, 50> aucUserName;
	System::Word usConnNumber;
	System::StaticArray<System::Int8, 50> aucDictionaryName;
	System::StaticArray<System::Int8, 30> aucAddress;
	System::StaticArray<System::Int8, 50> aucOSUserLoginName;
	System::StaticArray<System::Int8, 30> aucTSAddress;
	System::StaticArray<System::Int8, 70> aucApplicationID;
	unsigned ulAveRequestCost;
	System::Word usReserved1;
};
#pragma pack(pop)


typedef ADS_MGMT_USER_INFO *PADS_MGMT_USER_INFO;

typedef System::StaticArray<ADS_MGMT_USER_INFO, 200> ADSMgUserArray;

typedef ADSMgUserArray *PADSMgUserArray;

#pragma pack(push,1)
struct DECLSPEC_DRECORD ADS_MGMT_TABLE_INFO
{
public:
	System::StaticArray<System::Int8, 260> aucTableName;
	System::Word usLockType;
};
#pragma pack(pop)


typedef ADS_MGMT_TABLE_INFO *PADS_MGMT_TABLE_INFO;

typedef System::StaticArray<ADS_MGMT_TABLE_INFO, 200> ADSMgTableArray;

typedef ADSMgTableArray *PADSMgTableArray;

#pragma pack(push,1)
struct DECLSPEC_DRECORD ADS_MGMT_INDEX_INFO
{
public:
	System::StaticArray<System::Int8, 260> aucIndexName;
};
#pragma pack(pop)


typedef ADS_MGMT_INDEX_INFO *PADS_MGMT_INDEX_INFO;

typedef System::StaticArray<ADS_MGMT_INDEX_INFO, 200> ADSMgIndexArray;

typedef ADSMgIndexArray *PADSMgIndexArray;

#pragma pack(push,1)
struct DECLSPEC_DRECORD ADS_MGMT_RECORD_INFO
{
public:
	unsigned ulRecordNumber;
};
#pragma pack(pop)


typedef ADS_MGMT_RECORD_INFO *PADS_MGMT_RECORD_INFO;

typedef System::StaticArray<ADS_MGMT_RECORD_INFO, 400> ADSMgLocksArray;

typedef ADSMgLocksArray *PADSMgLocksArray;

#pragma pack(push,1)
struct DECLSPEC_DRECORD ADS_MGMT_THREAD_ACTIVITY
{
public:
	unsigned ulThreadNumber;
	System::Word usOpCode;
	System::StaticArray<System::Int8, 50> aucUserName;
	System::Word usConnNumber;
	System::Word usReserved1;
	System::StaticArray<System::Int8, 50> aucOSUserLoginName;
};
#pragma pack(pop)


typedef ADS_MGMT_THREAD_ACTIVITY *PADS_MGMT_THREAD_ACTIVITY;

typedef System::StaticArray<ADS_MGMT_THREAD_ACTIVITY, 50> ADSMgThreadsArray;

typedef ADSMgThreadsArray *PADSMgThreadsArray;

#pragma pack(push,1)
struct DECLSPEC_DRECORD ADS_GUID_DATA
{
public:
	unsigned Data1;
	System::Word Data2;
	System::Word Data3;
	unsigned __int64 Data4;
};
#pragma pack(pop)


#pragma pack(push,1)
struct DECLSPEC_DRECORD ADD_FIELD_DESC
{
public:
	System::Word usFieldType;
	System::Word usFieldLength;
	System::Word usFieldDecimal;
};
#pragma pack(pop)


typedef ADD_FIELD_DESC *PFDD_FIELD_DESC;

#ifndef _WIN64
typedef unsigned __stdcall (*TSTORED_PROCEDURE_PTR)(unsigned ulConnectionID, PUNSIGNED8 pucUserName, PUNSIGNED8 pucPassword, PUNSIGNED8 pucProcName, PUNSIGNED32 ulRecNum, PUNSIGNED8 pucTable1, PUNSIGNED8 pucTable2);
#else /* _WIN64 */
typedef unsigned __fastcall (*TSTORED_PROCEDURE_PTR)(unsigned ulConnectionID, PUNSIGNED8 pucUserName, PUNSIGNED8 pucPassword, PUNSIGNED8 pucProcName, PUNSIGNED32 ulRecNum, PUNSIGNED8 pucTable1, PUNSIGNED8 pucTable2);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TSTARTUP_PROCEDURE_PTR)(unsigned ulConnectionID, PUNSIGNED8 pucUserName, PUNSIGNED8 pucPassword);
#else /* _WIN64 */
typedef unsigned __fastcall (*TSTARTUP_PROCEDURE_PTR)(unsigned ulConnectionID, PUNSIGNED8 pucUserName, PUNSIGNED8 pucPassword);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TSHUTDOWN_PROCEDURE_PTR)(unsigned ulConnectionID, PUNSIGNED8 pucUserName, PUNSIGNED8 pucPassword);
#else /* _WIN64 */
typedef unsigned __fastcall (*TSHUTDOWN_PROCEDURE_PTR)(unsigned ulConnectionID, PUNSIGNED8 pucUserName, PUNSIGNED8 pucPassword);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TSTORED_PROCEDURE2_PTR)(unsigned ulConnectionID, NativeUInt hConnection, PUNSIGNED32 pulNumRowsAffected);
#else /* _WIN64 */
typedef unsigned __fastcall (*TSTORED_PROCEDURE2_PTR)(unsigned ulConnectionID, NativeUInt hConnection, PUNSIGNED32 pulNumRowsAffected);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TSTARTUP_PROCEDURE2_PTR)(unsigned ulConnectionID, NativeUInt hConnection);
#else /* _WIN64 */
typedef unsigned __fastcall (*TSTARTUP_PROCEDURE2_PTR)(unsigned ulConnectionID, NativeUInt hConnection);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TSHUTDOWN_PROCEDURE2_PTR)(unsigned ulConnectionID, NativeUInt hConnection);
#else /* _WIN64 */
typedef unsigned __fastcall (*TSHUTDOWN_PROCEDURE2_PTR)(unsigned ulConnectionID, NativeUInt hConnection);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TTRIGGER_FUNCTION_PTR)(unsigned ulConnectionID, NativeUInt hConnection, PUNSIGNED8 pucTriggerName, PUNSIGNED8 pucTableName, unsigned ulEventType, unsigned ulTriggerType, unsigned ulRecNo);
#else /* _WIN64 */
typedef unsigned __fastcall (*TTRIGGER_FUNCTION_PTR)(unsigned ulConnectionID, NativeUInt hConnection, PUNSIGNED8 pucTriggerName, PUNSIGNED8 pucTableName, unsigned ulEventType, unsigned ulTriggerType, unsigned ulRecNo);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TGET_INTERFACE_VERSION_PTR)(void);
#else /* _WIN64 */
typedef unsigned __fastcall (*TGET_INTERFACE_VERSION_PTR)(void);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TCallbackFunction)(System::Word usPercent, unsigned ulCallbackID);
#else /* _WIN64 */
typedef unsigned __fastcall (*TCallbackFunction)(System::Word usPercent, unsigned ulCallbackID);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TCallbackFunction101)(System::Word usPercent, __int64 qCallbackID);
#else /* _WIN64 */
typedef unsigned __fastcall (*TCallbackFunction101)(System::Word usPercent, __int64 qCallbackID);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TProgressCallback)(System::Word usPercent);
#else /* _WIN64 */
typedef unsigned __fastcall (*TProgressCallback)(System::Word usPercent);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TSQLAbortFunc)(void);
#else /* _WIN64 */
typedef unsigned __fastcall (*TSQLAbortFunc)(void);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TUDFFunc)(void);
#else /* _WIN64 */
typedef unsigned __fastcall (*TUDFFunc)(void);
#endif /* _WIN64 */

typedef PAceChar ADSFIELD;

typedef System::StaticArray<NativeUInt, 256> ADSIndexArray;

typedef ADSIndexArray *PADSIndexArray;

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsAddCustomKey)(NativeUInt hIndex);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsAddCustomKey)(NativeUInt hIndex);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsAppendRecord)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsAppendRecord)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsApplicationExit)(void);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsApplicationExit)(void);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsAtBOF)(NativeUInt hTable, PUNSIGNED16 pbBof);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsAtBOF)(NativeUInt hTable, PUNSIGNED16 pbBof);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsAtEOF)(NativeUInt hTable, PUNSIGNED16 pbEof);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsAtEOF)(NativeUInt hTable, PUNSIGNED16 pbEof);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsBeginTransaction)(NativeUInt hConnect);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsBeginTransaction)(NativeUInt hConnect);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsBinaryToFile)(NativeUInt hTable, PAceChar pucFldName, PAceChar pucFileName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsBinaryToFile)(NativeUInt hTable, PAceChar pucFldName, PAceChar pucFileName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCacheOpenCursors)(System::Word usOpen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCacheOpenCursors)(System::Word usOpen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCacheOpenTables)(System::Word usOpen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCacheOpenTables)(System::Word usOpen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCacheRecords)(NativeUInt hTable, System::Word usNumRecords);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCacheRecords)(NativeUInt hTable, System::Word usNumRecords);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCancelUpdate)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCancelUpdate)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCancelUpdate90)(NativeUInt hTable, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCancelUpdate90)(NativeUInt hTable, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCheckExistence)(NativeUInt hConnect, PAceChar pucFileName, PUNSIGNED16 pusOnDisk);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCheckExistence)(NativeUInt hConnect, PAceChar pucFileName, PUNSIGNED16 pusOnDisk);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsClearAllScopes)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsClearAllScopes)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsClearDefault)(void);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsClearDefault)(void);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsClearFilter)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsClearFilter)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsClearRelation)(NativeUInt hTableParent);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsClearRelation)(NativeUInt hTableParent);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsClearScope)(NativeUInt hIndex, System::Word usScopeOption);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsClearScope)(NativeUInt hIndex, System::Word usScopeOption);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCloneTable)(NativeUInt hTable, PADSHANDLE phClone);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCloneTable)(NativeUInt hTable, PADSHANDLE phClone);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCloseAllIndexes)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCloseAllIndexes)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCloseAllTables)(void);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCloseAllTables)(void);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCloseIndex)(NativeUInt hIndex);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCloseIndex)(NativeUInt hIndex);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCloseTable)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCloseTable)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCloseCachedTables)(NativeUInt hConnection);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCloseCachedTables)(NativeUInt hConnection);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCommitTransaction)(NativeUInt hConnect);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCommitTransaction)(NativeUInt hConnect);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsConnect)(PAceChar pucServerName, PADSHANDLE phConnect);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsConnect)(PAceChar pucServerName, PADSHANDLE phConnect);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsConnect26)(PAceChar pucServerName, System::Word usServerTypes, PADSHANDLE phConnect);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsConnect26)(PAceChar pucServerName, System::Word usServerTypes, PADSHANDLE phConnect);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsConnect60)(PAceChar pucServerPath, System::Word usServerTypes, PAceChar pucUserName, PAceChar pucPassword, unsigned ulOptions, PADSHANDLE phConnect);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsConnect60)(PAceChar pucServerPath, System::Word usServerTypes, PAceChar pucUserName, PAceChar pucPassword, unsigned ulOptions, PADSHANDLE phConnect);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsConnect101)(PAceChar pucConnectString, PADSHANDLE phConnectionOptions, PADSHANDLE phConnect);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsConnect101)(PAceChar pucConnectString, PADSHANDLE phConnectionOptions, PADSHANDLE phConnect);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsClearCachePool)(PAceChar pucConnectString);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsClearCachePool)(PAceChar pucConnectString);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsReapUnusedConnections)(void);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsReapUnusedConnections)(void);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsConnectionAlive)(NativeUInt hConnect, PUNSIGNED16 pbConnectionIsAlive);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsConnectionAlive)(NativeUInt hConnect, PUNSIGNED16 pbConnectionIsAlive);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsContinue)(NativeUInt hTable, PUNSIGNED16 pbFound);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsContinue)(NativeUInt hTable, PUNSIGNED16 pbFound);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsConvertTable)(NativeUInt hObj, System::Word usFilterOption, PAceChar pucFile, System::Word usTableType);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsConvertTable)(NativeUInt hObj, System::Word usFilterOption, PAceChar pucFile, System::Word usTableType);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCopyTable)(NativeUInt hObj, System::Word usFilterOption, PAceChar pucFile);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCopyTable)(NativeUInt hObj, System::Word usFilterOption, PAceChar pucFile);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCopyTableContents)(NativeUInt hObjFrom, NativeUInt hTableTo, System::Word usFilterOption);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCopyTableContents)(NativeUInt hObjFrom, NativeUInt hTableTo, System::Word usFilterOption);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCopyTableStructure)(NativeUInt hTable, PAceChar pucFile);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCopyTableStructure)(NativeUInt hTable, PAceChar pucFile);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCreateIndex)(NativeUInt hObj, PAceChar pucFileName, PAceChar pucTag, PAceChar pucExpr, PAceChar pucCondition, PAceChar pucWhile, unsigned ulOptions, PADSHANDLE phIndex);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCreateIndex)(NativeUInt hObj, PAceChar pucFileName, PAceChar pucTag, PAceChar pucExpr, PAceChar pucCondition, PAceChar pucWhile, unsigned ulOptions, PADSHANDLE phIndex);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCreateIndex61)(NativeUInt hObj, PAceChar pucFileName, PAceChar pucTag, PAceChar pucExpr, PAceChar pucCondition, PAceChar pucWhile, unsigned ulOptions, unsigned ulPageSize, PADSHANDLE phIndex);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCreateIndex61)(NativeUInt hObj, PAceChar pucFileName, PAceChar pucTag, PAceChar pucExpr, PAceChar pucCondition, PAceChar pucWhile, unsigned ulOptions, unsigned ulPageSize, PADSHANDLE phIndex);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCreateIndex90)(NativeUInt hObj, PAceChar pucFileName, PAceChar pucTag, PAceChar pucExpr, PAceChar pucCondition, PAceChar pucWhile, unsigned ulOptions, unsigned ulPageSize, PAceChar pucCollation, PADSHANDLE phIndex);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCreateIndex90)(NativeUInt hObj, PAceChar pucFileName, PAceChar pucTag, PAceChar pucExpr, PAceChar pucCondition, PAceChar pucWhile, unsigned ulOptions, unsigned ulPageSize, PAceChar pucCollation, PADSHANDLE phIndex);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCreateFTSIndex)(NativeUInt hTable, PAceChar pucFileName, PAceChar pucTag, PAceChar pucField, unsigned ulPageSize, unsigned ulMinWordLen, unsigned ulMaxWordLen, System::Word usUseDefaultDelim, void * pvDelimiters, System::Word usUseDefaultNoise, void * pvNoiseWords, System::Word usUseDefaultDrop, void * pvDropChars, System::Word usUseDefaultConditionals, void * pvConditionalChars, PAceChar pucCollation, PAceChar pucReserved1, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCreateFTSIndex)(NativeUInt hTable, PAceChar pucFileName, PAceChar pucTag, PAceChar pucField, unsigned ulPageSize, unsigned ulMinWordLen, unsigned ulMaxWordLen, System::Word usUseDefaultDelim, void * pvDelimiters, System::Word usUseDefaultNoise, void * pvNoiseWords, System::Word usUseDefaultDrop, void * pvDropChars, System::Word usUseDefaultConditionals, void * pvConditionalChars, PAceChar pucCollation, PAceChar pucReserved1, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCreateTable)(NativeUInt hConnection, PAceChar pucName, PAceChar pucAlias, System::Word usTableType, System::Word usCharType, System::Word usLockType, System::Word usCheckRights, System::Word usMemoSize, PAceChar pucFields, PADSHANDLE phTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCreateTable)(NativeUInt hConnection, PAceChar pucName, PAceChar pucAlias, System::Word usTableType, System::Word usCharType, System::Word usLockType, System::Word usCheckRights, System::Word usMemoSize, PAceChar pucFields, PADSHANDLE phTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCreateTable71)(NativeUInt hConnection, PAceChar pucName, PAceChar pucDBObjName, System::Word usTableType, System::Word usCharType, System::Word usLockType, System::Word usCheckRights, System::Word usMemoSize, PAceChar pucFields, unsigned ulOptions, PADSHANDLE phTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCreateTable71)(NativeUInt hConnection, PAceChar pucName, PAceChar pucDBObjName, System::Word usTableType, System::Word usCharType, System::Word usLockType, System::Word usCheckRights, System::Word usMemoSize, PAceChar pucFields, unsigned ulOptions, PADSHANDLE phTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCreateTable90)(NativeUInt hConnection, PAceChar pucName, PAceChar pucDBObjName, System::Word usTableType, System::Word usCharType, System::Word usLockType, System::Word usCheckRights, System::Word usMemoSize, PAceChar pucFields, unsigned ulOptions, PAceChar pucCollation, PADSHANDLE phTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCreateTable90)(NativeUInt hConnection, PAceChar pucName, PAceChar pucDBObjName, System::Word usTableType, System::Word usCharType, System::Word usLockType, System::Word usCheckRights, System::Word usMemoSize, PAceChar pucFields, unsigned ulOptions, PAceChar pucCollation, PADSHANDLE phTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDCreate)(PAceChar pucDictionaryPath, System::Word usEncrypt, PAceChar pucDescription, PADSHANDLE phDictionary);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDCreate)(PAceChar pucDictionaryPath, System::Word usEncrypt, PAceChar pucDescription, PADSHANDLE phDictionary);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDCreate101)(PAceChar pucConnectString, PADSHANDLE phConnectOptions, PADSHANDLE phDictionary);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDCreate101)(PAceChar pucConnectString, PADSHANDLE phConnectOptions, PADSHANDLE phDictionary);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDCreateRefIntegrity)(NativeUInt hDictionary, PAceChar pucRIName, PAceChar pucFailTable, PAceChar pucParentTableName, PAceChar pucParentTagName, PAceChar pucChildTableName, PAceChar pucChildTagName, System::Word usUpdateRule, System::Word usDeleteRule);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDCreateRefIntegrity)(NativeUInt hDictionary, PAceChar pucRIName, PAceChar pucFailTable, PAceChar pucParentTableName, PAceChar pucParentTagName, PAceChar pucChildTableName, PAceChar pucChildTagName, System::Word usUpdateRule, System::Word usDeleteRule);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDCreateRefIntegrity62)(NativeUInt hDictionary, PAceChar pucRIName, PAceChar pucFailTable, PAceChar pucParentTableName, PAceChar pucParentTagName, PAceChar pucChildTableName, PAceChar pucChildTagName, System::Word usUpdateRule, System::Word usDeleteRule, PAceChar pucNoPrimaryError, PAceChar pucCascadeError);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDCreateRefIntegrity62)(NativeUInt hDictionary, PAceChar pucRIName, PAceChar pucFailTable, PAceChar pucParentTableName, PAceChar pucParentTagName, PAceChar pucChildTableName, PAceChar pucChildTagName, System::Word usUpdateRule, System::Word usDeleteRule, PAceChar pucNoPrimaryError, PAceChar pucCascadeError);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDRemoveRefIntegrity)(NativeUInt hDictionary, PAceChar pucRIName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDRemoveRefIntegrity)(NativeUInt hDictionary, PAceChar pucRIName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGetDatabaseProperty)(NativeUInt hObject, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGetDatabaseProperty)(NativeUInt hObject, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGetFieldProperty)(NativeUInt hObject, PAceChar pucTableName, PAceChar pucFieldName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGetFieldProperty)(NativeUInt hObject, PAceChar pucTableName, PAceChar pucFieldName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGetIndexFileProperty)(NativeUInt hObject, PAceChar pucTableName, PAceChar pucIndexFileName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGetIndexFileProperty)(NativeUInt hObject, PAceChar pucTableName, PAceChar pucIndexFileName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGetIndexProperty)(NativeUInt hObject, PAceChar pucTableName, PAceChar pucIndexName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGetIndexProperty)(NativeUInt hObject, PAceChar pucTableName, PAceChar pucIndexName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGetLinkProperty)(NativeUInt hConnect, PAceChar pucLinkName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGetLinkProperty)(NativeUInt hConnect, PAceChar pucLinkName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGetTableProperty)(NativeUInt hObject, PAceChar pucTableName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGetTableProperty)(NativeUInt hObject, PAceChar pucTableName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGetUserGroupProperty)(NativeUInt hObject, PAceChar pucUserGroupName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGetUserGroupProperty)(NativeUInt hObject, PAceChar pucUserGroupName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGetUserProperty)(NativeUInt hObject, PAceChar pucUserName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGetUserProperty)(NativeUInt hObject, PAceChar pucUserName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGetViewProperty)(NativeUInt hObject, PAceChar pucViewName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGetViewProperty)(NativeUInt hObject, PAceChar pucViewName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGetTriggerProperty)(NativeUInt hObject, PAceChar pucTriggerName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGetTriggerProperty)(NativeUInt hObject, PAceChar pucTriggerName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGetProcedureProperty)(NativeUInt hObject, PAceChar pucProcName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGetProcedureProperty)(NativeUInt hObject, PAceChar pucProcName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGetRefIntegrityProperty)(NativeUInt hObject, PAceChar pucRIName, System::Word usPropertyID, PAceChar pucProperty, PUNSIGNED16 pusPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGetRefIntegrityProperty)(NativeUInt hObject, PAceChar pucRIName, System::Word usPropertyID, PAceChar pucProperty, PUNSIGNED16 pusPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGetPermissions)(NativeUInt hDBConn, PAceChar pucGrantee, System::Word usObjectType, PAceChar pucObjectName, PAceChar pucParentName, System::Word usGetInherited, PUNSIGNED32 pulPermissions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGetPermissions)(NativeUInt hDBConn, PAceChar pucGrantee, System::Word usObjectType, PAceChar pucObjectName, PAceChar pucParentName, System::Word usGetInherited, PUNSIGNED32 pulPermissions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGrantPermission)(NativeUInt hAdminConn, System::Word usObjectType, PAceChar pucObjectName, PAceChar pucParentName, PAceChar pucGrantee, unsigned ulPermissions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGrantPermission)(NativeUInt hAdminConn, System::Word usObjectType, PAceChar pucObjectName, PAceChar pucParentName, PAceChar pucGrantee, unsigned ulPermissions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDRevokePermission)(NativeUInt hAdminConn, System::Word usObjectType, PAceChar pucObjectName, PAceChar pucParentName, PAceChar pucGrantee, unsigned ulPermissions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDRevokePermission)(NativeUInt hAdminConn, System::Word usObjectType, PAceChar pucObjectName, PAceChar pucParentName, PAceChar pucGrantee, unsigned ulPermissions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDSetDatabaseProperty)(NativeUInt hDictionary, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDSetDatabaseProperty)(NativeUInt hDictionary, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDSetFieldProperty)(NativeUInt hDictionary, PAceChar pucTableName, PAceChar pucFieldName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen, System::Word usValidateOption, PAceChar pucFailTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDSetFieldProperty)(NativeUInt hDictionary, PAceChar pucTableName, PAceChar pucFieldName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen, System::Word usValidateOption, PAceChar pucFailTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDSetProcedureProperty)(NativeUInt hDictionary, PAceChar pucProcedureName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDSetProcedureProperty)(NativeUInt hDictionary, PAceChar pucProcedureName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDSetTableProperty)(NativeUInt hDictionary, PAceChar pucTableName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen, System::Word usValidateOption, PAceChar pucFailTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDSetTableProperty)(NativeUInt hDictionary, PAceChar pucTableName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen, System::Word usValidateOption, PAceChar pucFailTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDSetUserGroupProperty)(NativeUInt hDictionary, PAceChar pucUserGroupName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDSetUserGroupProperty)(NativeUInt hDictionary, PAceChar pucUserGroupName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDSetUserProperty)(NativeUInt hDictionary, PAceChar pucUserName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDSetUserProperty)(NativeUInt hDictionary, PAceChar pucUserName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDSetViewProperty)(NativeUInt hDictionary, PAceChar pucViewName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDSetViewProperty)(NativeUInt hDictionary, PAceChar pucViewName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDSetObjectAccessRights)(NativeUInt hDictionary, PAceChar pucObjectName, PAceChar pucAccessorName, PAceChar pucAllowedAccess);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDSetObjectAccessRights)(NativeUInt hDictionary, PAceChar pucObjectName, PAceChar pucAccessorName, PAceChar pucAllowedAccess);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDAddProcedure)(NativeUInt hDictionary, PAceChar pucName, PAceChar pucContainer, PAceChar pucProcName, unsigned ulInvokeOption, PAceChar pucInParams, PAceChar pucOutParams, PAceChar pucComments);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDAddProcedure)(NativeUInt hDictionary, PAceChar pucName, PAceChar pucContainer, PAceChar pucProcName, unsigned ulInvokeOption, PAceChar pucInParams, PAceChar pucOutParams, PAceChar pucComments);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDAddProcedure100)(NativeUInt hDictionary, PAceChar pucName, System::WideChar * pwcContainer, PAceChar pucProcName, unsigned ulInvokeOption, PAceChar pucInParams, PAceChar pucOutParams, PAceChar pucComments);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDAddProcedure100)(NativeUInt hDictionary, PAceChar pucName, System::WideChar * pwcContainer, PAceChar pucProcName, unsigned ulInvokeOption, PAceChar pucInParams, PAceChar pucOutParams, PAceChar pucComments);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDAddTable)(NativeUInt hDictionary, PAceChar pucTableName, PAceChar pucTablePath, System::Word usTableType, System::Word usCharType, PAceChar pucIndexFiles, PAceChar pucComments);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDAddTable)(NativeUInt hDictionary, PAceChar pucTableName, PAceChar pucTablePath, System::Word usTableType, System::Word usCharType, PAceChar pucIndexFiles, PAceChar pucComments);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDAddTable90)(NativeUInt hDictionary, PAceChar pucTableName, PAceChar pucTablePath, System::Word usTableType, System::Word usCharType, PAceChar pucIndexFiles, PAceChar pucComments, PAceChar pucCollation);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDAddTable90)(NativeUInt hDictionary, PAceChar pucTableName, PAceChar pucTablePath, System::Word usTableType, System::Word usCharType, PAceChar pucIndexFiles, PAceChar pucComments, PAceChar pucCollation);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDAddView)(NativeUInt hDictionary, PAceChar pucName, PAceChar pucComments, PAceChar pucSQL);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDAddView)(NativeUInt hDictionary, PAceChar pucName, PAceChar pucComments, PAceChar pucSQL);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDAddView100)(NativeUInt hDictionary, PAceChar pucName, PAceChar pucComments, System::WideChar * pwcSQL);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDAddView100)(NativeUInt hDictionary, PAceChar pucName, PAceChar pucComments, System::WideChar * pwcSQL);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDCreateTrigger)(NativeUInt hDictionary, PAceChar pucName, PAceChar pucTableName, unsigned ulTriggerType, unsigned ulEventTypes, unsigned ulContainerType, PAceChar pucContainer, PAceChar pucFunctionName, unsigned ulPriority, PAceChar pucComments, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDCreateTrigger)(NativeUInt hDictionary, PAceChar pucName, PAceChar pucTableName, unsigned ulTriggerType, unsigned ulEventTypes, unsigned ulContainerType, PAceChar pucContainer, PAceChar pucFunctionName, unsigned ulPriority, PAceChar pucComments, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDCreateTrigger100)(NativeUInt hDictionary, PAceChar pucName, PAceChar pucTableName, unsigned ulTriggerType, unsigned ulEventTypes, unsigned ulContainerType, System::WideChar * pwcContainer, PAceChar pucFunctionName, unsigned ulPriority, PAceChar pucComments, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDCreateTrigger100)(NativeUInt hDictionary, PAceChar pucName, PAceChar pucTableName, unsigned ulTriggerType, unsigned ulEventTypes, unsigned ulContainerType, System::WideChar * pwcContainer, PAceChar pucFunctionName, unsigned ulPriority, PAceChar pucComments, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDRemoveTrigger)(NativeUInt hDictionary, PAceChar pucName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDRemoveTrigger)(NativeUInt hDictionary, PAceChar pucName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDAddIndexFile)(NativeUInt hDictionary, PAceChar pucTableName, PAceChar pucIndexFilePath, PAceChar pucComment);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDAddIndexFile)(NativeUInt hDictionary, PAceChar pucTableName, PAceChar pucIndexFilePath, PAceChar pucComment);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDCreateUser)(NativeUInt hDictionary, PAceChar pucGroupName, PAceChar pucUserName, PAceChar pucPassword, PAceChar pucDescription);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDCreateUser)(NativeUInt hDictionary, PAceChar pucGroupName, PAceChar pucUserName, PAceChar pucPassword, PAceChar pucDescription);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDAddUserToGroup)(NativeUInt hDictionary, PAceChar pucGroupName, PAceChar pucUserName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDAddUserToGroup)(NativeUInt hDictionary, PAceChar pucGroupName, PAceChar pucUserName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDRemoveUserFromGroup)(NativeUInt hDictionary, PAceChar pucGroupName, PAceChar pucUserName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDRemoveUserFromGroup)(NativeUInt hDictionary, PAceChar pucGroupName, PAceChar pucUserName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDDeleteUser)(NativeUInt hDictionary, PAceChar pucUserName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDDeleteUser)(NativeUInt hDictionary, PAceChar pucUserName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDCreateUserGroup)(NativeUInt hDictionary, PAceChar pucGroupName, PAceChar pucDescription);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDCreateUserGroup)(NativeUInt hDictionary, PAceChar pucGroupName, PAceChar pucDescription);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDDeleteUserGroup)(NativeUInt hDictionary, PAceChar pucGroupName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDDeleteUserGroup)(NativeUInt hDictionary, PAceChar pucGroupName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDDeleteIndex)(NativeUInt hDictionary, PAceChar pucTableName, PAceChar pucIndexName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDDeleteIndex)(NativeUInt hDictionary, PAceChar pucTableName, PAceChar pucIndexName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDRemoveIndexFile)(NativeUInt hDictionary, PAceChar pucTableName, PAceChar pucIndexFileName, System::Word usDeleteFile);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDRemoveIndexFile)(NativeUInt hDictionary, PAceChar pucTableName, PAceChar pucIndexFileName, System::Word usDeleteFile);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDRemoveProcedure)(NativeUInt hDictionary, PAceChar pucName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDRemoveProcedure)(NativeUInt hDictionary, PAceChar pucName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDRemoveTable)(NativeUInt hObject, PAceChar pucTableName, System::Word usDeleteFiles);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDRemoveTable)(NativeUInt hObject, PAceChar pucTableName, System::Word usDeleteFiles);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDRemoveView)(NativeUInt hDictionary, PAceChar pucName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDRemoveView)(NativeUInt hDictionary, PAceChar pucName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDRenameObject)(NativeUInt hDictionary, PAceChar pucObjectName, PAceChar pucNewObjectName, System::Word usObjectType, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDRenameObject)(NativeUInt hDictionary, PAceChar pucObjectName, PAceChar pucNewObjectName, System::Word usObjectType, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDMoveObjectFile)(NativeUInt hDictionary, System::Word usObjectType, PAceChar pucObjectName, PAceChar pucNewPath, PAceChar pucIndexFiles, PAceChar pucParent, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDMoveObjectFile)(NativeUInt hDictionary, System::Word usObjectType, PAceChar pucObjectName, PAceChar pucNewPath, PAceChar pucIndexFiles, PAceChar pucParent, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDFindFirstObject)(NativeUInt hObject, System::Word usFindObjectType, PAceChar pucParentName, PAceChar pucObjectName, PUNSIGNED16 pusObjectNameLen, PADSHANDLE phFindHandle);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDFindFirstObject)(NativeUInt hObject, System::Word usFindObjectType, PAceChar pucParentName, PAceChar pucObjectName, PUNSIGNED16 pusObjectNameLen, PADSHANDLE phFindHandle);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDFindNextObject)(NativeUInt hObject, NativeUInt hFindHandle, PAceChar pucObjectName, PUNSIGNED16 pusObjectNameLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDFindNextObject)(NativeUInt hObject, NativeUInt hFindHandle, PAceChar pucObjectName, PUNSIGNED16 pusObjectNameLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDFindClose)(NativeUInt hObject, NativeUInt hFindHandle);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDFindClose)(NativeUInt hObject, NativeUInt hFindHandle);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDCreateLink)(NativeUInt hDBConn, PAceChar pucLinkAlias, PAceChar pucLinkedDDPath, PAceChar pucUserName, PAceChar pucPassword, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDCreateLink)(NativeUInt hDBConn, PAceChar pucLinkAlias, PAceChar pucLinkedDDPath, PAceChar pucUserName, PAceChar pucPassword, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDModifyLink)(NativeUInt hDBConn, PAceChar pucLinkAlias, PAceChar pucLinkedDDPath, PAceChar pucUserName, PAceChar pucPassword, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDModifyLink)(NativeUInt hDBConn, PAceChar pucLinkAlias, PAceChar pucLinkedDDPath, PAceChar pucUserName, PAceChar pucPassword, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDDropLink)(NativeUInt hDBConn, PAceChar pucLinkedDD, System::Word usDropGlobal);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDDropLink)(NativeUInt hDBConn, PAceChar pucLinkedDD, System::Word usDropGlobal);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDCreatePublication)(NativeUInt hDictionary, PAceChar pucPublicationName, PAceChar pucComments, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDCreatePublication)(NativeUInt hDictionary, PAceChar pucPublicationName, PAceChar pucComments, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGetPublicationProperty)(NativeUInt hObject, PAceChar pucPublicationName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGetPublicationProperty)(NativeUInt hObject, PAceChar pucPublicationName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDSetPublicationProperty)(NativeUInt hDictionary, PAceChar pucPublicationName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDSetPublicationProperty)(NativeUInt hDictionary, PAceChar pucPublicationName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDDeletePublication)(NativeUInt hDictionary, PAceChar pucPublicationName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDDeletePublication)(NativeUInt hDictionary, PAceChar pucPublicationName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDCreateArticle)(NativeUInt hDictionary, PAceChar pucPublicationName, PAceChar pucObjectName, PAceChar pucRowIdentColumns, PAceChar pucFilter, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDCreateArticle)(NativeUInt hDictionary, PAceChar pucPublicationName, PAceChar pucObjectName, PAceChar pucRowIdentColumns, PAceChar pucFilter, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDCreateArticle100)(NativeUInt hDictionary, PAceChar pucPublicationName, PAceChar pucObjectName, PAceChar pucRowIdentColumns, System::WideChar * pwcFilter, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDCreateArticle100)(NativeUInt hDictionary, PAceChar pucPublicationName, PAceChar pucObjectName, PAceChar pucRowIdentColumns, System::WideChar * pwcFilter, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGetArticleProperty)(NativeUInt hObject, PAceChar pucPublicationName, PAceChar pucObjectName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGetArticleProperty)(NativeUInt hObject, PAceChar pucPublicationName, PAceChar pucObjectName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDSetArticleProperty)(NativeUInt hDictionary, PAceChar pucPublicationName, PAceChar pucObjectName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDSetArticleProperty)(NativeUInt hDictionary, PAceChar pucPublicationName, PAceChar pucObjectName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDDeleteArticle)(NativeUInt hDictionary, PAceChar pucPublicationName, PAceChar pucObjectName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDDeleteArticle)(NativeUInt hDictionary, PAceChar pucPublicationName, PAceChar pucObjectName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDCreateSubscription)(NativeUInt hDictionary, PAceChar pucSubscriptionName, PAceChar pucPublicationName, PAceChar pucTarget, PAceChar pucUser, PAceChar pucPassword, PAceChar pucReplicationQueue, System::Word usForward, PAceChar pucComments, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDCreateSubscription)(NativeUInt hDictionary, PAceChar pucSubscriptionName, PAceChar pucPublicationName, PAceChar pucTarget, PAceChar pucUser, PAceChar pucPassword, PAceChar pucReplicationQueue, System::Word usForward, PAceChar pucComments, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDGetSubscriptionProperty)(NativeUInt hObject, PAceChar pucSubscriptionName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDGetSubscriptionProperty)(NativeUInt hObject, PAceChar pucSubscriptionName, System::Word usPropertyID, void * pvProperty, PUNSIGNED16 pusPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDSetSubscriptionProperty)(NativeUInt hDictionary, PAceChar pucSubscriptionName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDSetSubscriptionProperty)(NativeUInt hDictionary, PAceChar pucSubscriptionName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDDeleteSubscription)(NativeUInt hDictionary, PAceChar pucSubscriptionName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDDeleteSubscription)(NativeUInt hDictionary, PAceChar pucSubscriptionName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDecryptRecord)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDecryptRecord)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDecryptTable)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDecryptTable)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDeleteCustomKey)(NativeUInt hIndex);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDeleteCustomKey)(NativeUInt hIndex);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDeleteIndex)(NativeUInt hIndex);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDeleteIndex)(NativeUInt hIndex);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDeleteRecord)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDeleteRecord)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetKeyColumn)(NativeUInt hCursor, PAceChar pucKeyColumn, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetKeyColumn)(NativeUInt hCursor, PAceChar pucKeyColumn, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetKeyFilter)(NativeUInt hTable, PUNSIGNED8 pucValuesTable, unsigned ulOptions, PUNSIGNED8 pucFilter, PUNSIGNED32 pulLength);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetKeyFilter)(NativeUInt hTable, PUNSIGNED8 pucValuesTable, unsigned ulOptions, PUNSIGNED8 pucFilter, PUNSIGNED32 pulLength);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDisableEncryption)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDisableEncryption)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDisableLocalConnections)(void);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDisableLocalConnections)(void);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDisconnect)(NativeUInt hConnect);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDisconnect)(NativeUInt hConnect);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsEnableEncryption)(NativeUInt hTable, PAceChar pucPassword);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsEnableEncryption)(NativeUInt hTable, PAceChar pucPassword);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsEncryptRecord)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsEncryptRecord)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsEncryptTable)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsEncryptTable)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsEvalLogicalExpr)(NativeUInt hTable, PAceChar pucExpr, PUNSIGNED16 pbResult);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsEvalLogicalExpr)(NativeUInt hTable, PAceChar pucExpr, PUNSIGNED16 pbResult);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsEvalLogicalExprW)(NativeUInt hTable, System::WideChar * pwcExpr, PUNSIGNED16 pbResult);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsEvalLogicalExprW)(NativeUInt hTable, System::WideChar * pwcExpr, PUNSIGNED16 pbResult);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsEvalNumericExpr)(NativeUInt hTable, PAceChar pucExpr, System::PDouble pdResult);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsEvalNumericExpr)(NativeUInt hTable, PAceChar pucExpr, System::PDouble pdResult);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsEvalStringExpr)(NativeUInt hTable, PAceChar pucExpr, PAceChar pucResult, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsEvalStringExpr)(NativeUInt hTable, PAceChar pucExpr, PAceChar pucResult, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsEvalTestExpr)(NativeUInt hTable, PAceChar pucExpr, PUNSIGNED16 pusType);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsEvalTestExpr)(NativeUInt hTable, PAceChar pucExpr, PUNSIGNED16 pusType);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsExtractKey)(NativeUInt hIndex, PAceChar pucKey, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsExtractKey)(NativeUInt hIndex, PAceChar pucKey, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsFailedTransactionRecovery)(PAceChar pucServer);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsFailedTransactionRecovery)(PAceChar pucServer);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsFileToBinary)(NativeUInt hTable, PAceChar pucFldName, System::Word usBinaryType, PAceChar pucFileName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsFileToBinary)(NativeUInt hTable, PAceChar pucFldName, System::Word usBinaryType, PAceChar pucFileName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsFindConnection)(PAceChar pucServerName, PADSHANDLE phConnect);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsFindConnection)(PAceChar pucServerName, PADSHANDLE phConnect);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsFindConnection25)(PAceChar pucFullPath, PADSHANDLE phConnect);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsFindConnection25)(PAceChar pucFullPath, PADSHANDLE phConnect);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsFindClose)(NativeUInt hConnect, NativeUInt lHandle);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsFindClose)(NativeUInt hConnect, NativeUInt lHandle);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsFindFirstTable)(NativeUInt hConnect, PAceChar pucFileMask, PAceChar pucFirstFile, PUNSIGNED16 pusFileLen, PADSHANDLE plHandle);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsFindFirstTable)(NativeUInt hConnect, PAceChar pucFileMask, PAceChar pucFirstFile, PUNSIGNED16 pusFileLen, PADSHANDLE plHandle);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsFindNextTable)(NativeUInt hConnect, NativeUInt lHandle, PAceChar pucFileName, PUNSIGNED16 pusFileLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsFindNextTable)(NativeUInt hConnect, NativeUInt lHandle, PAceChar pucFileName, PUNSIGNED16 pusFileLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsFindFirstTable62)(NativeUInt hConnect, PAceChar pucFileMask, PAceChar pucFirstDD, PUNSIGNED16 pusDDLen, PAceChar pucFirstFile, PUNSIGNED16 pusFileLen, PADSHANDLE plHandle);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsFindFirstTable62)(NativeUInt hConnect, PAceChar pucFileMask, PAceChar pucFirstDD, PUNSIGNED16 pusDDLen, PAceChar pucFirstFile, PUNSIGNED16 pusFileLen, PADSHANDLE plHandle);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsFindNextTable62)(NativeUInt hConnect, NativeUInt lHandle, PAceChar pucDDName, PUNSIGNED16 pusDDLen, PAceChar pucFileName, PUNSIGNED16 pusFileLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsFindNextTable62)(NativeUInt hConnect, NativeUInt lHandle, PAceChar pucDDName, PUNSIGNED16 pusDDLen, PAceChar pucFileName, PUNSIGNED16 pusFileLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetAllIndexes)(NativeUInt hTable, PADSIndexArray ahIndex, PUNSIGNED16 pusArrayLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetAllIndexes)(NativeUInt hTable, PADSIndexArray ahIndex, PUNSIGNED16 pusArrayLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetFTSIndexes)(NativeUInt hTable, PADSIndexArray ahIndex, PUNSIGNED16 pusArrayLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetFTSIndexes)(NativeUInt hTable, PADSIndexArray ahIndex, PUNSIGNED16 pusArrayLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetFTSIndexInfo)(NativeUInt hIndex, PAceChar pucOutput, PUNSIGNED32 pulBufLen, System::PPWideChar ppucField, PUNSIGNED32 pulMinWordLen, PUNSIGNED32 pulMaxWordLen, System::PPWideChar ppucDelimiters, System::PPWideChar ppucNoiseWords, System::PPWideChar ppucDropChars, System::PPWideChar ppucConditionalChars, System::PPWideChar ppucReserved1, System::PPWideChar ppucReserved2, PUNSIGNED32 pulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetFTSIndexInfo)(NativeUInt hIndex, PAceChar pucOutput, PUNSIGNED32 pulBufLen, System::PPWideChar ppucField, PUNSIGNED32 pulMinWordLen, PUNSIGNED32 pulMaxWordLen, System::PPWideChar ppucDelimiters, System::PPWideChar ppucNoiseWords, System::PPWideChar ppucDropChars, System::PPWideChar ppucConditionalChars, System::PPWideChar ppucReserved1, System::PPWideChar ppucReserved2, PUNSIGNED32 pulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetFTSIndexInfoW)(NativeUInt hIndex, System::WideChar * pwcOutput, PUNSIGNED32 pulBufLen, PPWideChar ppwcField, PUNSIGNED32 pulMinWordLen, PUNSIGNED32 pulMaxWordLen, PPWideChar ppwcDelimiters, PPWideChar ppwcNoiseWords, PPWideChar ppwcDropChars, PPWideChar ppwcConditionalChars, PPWideChar ppwcReserved1, PPWideChar ppwcReserved2, PUNSIGNED32 pulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetFTSIndexInfoW)(NativeUInt hIndex, System::WideChar * pwcOutput, PUNSIGNED32 pulBufLen, PPWideChar ppwcField, PUNSIGNED32 pulMinWordLen, PUNSIGNED32 pulMaxWordLen, PPWideChar ppwcDelimiters, PPWideChar ppwcNoiseWords, PPWideChar ppwcDropChars, PPWideChar ppwcConditionalChars, PPWideChar ppwcReserved1, PPWideChar ppwcReserved2, PUNSIGNED32 pulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetAllLocks)(NativeUInt hTable, void * aulLocks, PUNSIGNED16 pusArrayLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetAllLocks)(NativeUInt hTable, void * aulLocks, PUNSIGNED16 pusArrayLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetAllTables)(void * ahTable, PUNSIGNED16 pusArrayLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetAllTables)(void * ahTable, PUNSIGNED16 pusArrayLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetBinary)(NativeUInt hTable, PAceChar pucFldName, unsigned ulOffset, PAceBinary pucBuf, PUNSIGNED32 pulLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetBinary)(NativeUInt hTable, PAceChar pucFldName, unsigned ulOffset, PAceBinary pucBuf, PUNSIGNED32 pulLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetBinaryLength)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED32 pulLength);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetBinaryLength)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED32 pulLength);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetBookmark)(NativeUInt hTable, PADSHANDLE phBookmark);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetBookmark)(NativeUInt hTable, PADSHANDLE phBookmark);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetBookmark60)(NativeUInt hObj, PAceChar pucBookmark, PUNSIGNED32 pulLength);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetBookmark60)(NativeUInt hObj, PAceChar pucBookmark, PUNSIGNED32 pulLength);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetBookmarkLength)(NativeUInt hObj, PUNSIGNED32 pulLength);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetBookmarkLength)(NativeUInt hObj, PUNSIGNED32 pulLength);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCompareBookmarks)(PAceChar pucBookmark1, PAceChar pucBookmark2, PSIGNED32 plResult);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCompareBookmarks)(PAceChar pucBookmark1, PAceChar pucBookmark2, PSIGNED32 plResult);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetCollationLang)(PAceChar pucLang, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetCollationLang)(PAceChar pucLang, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetCollation)(NativeUInt hConnect, PAceChar pucCollation, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetCollation)(NativeUInt hConnect, PAceChar pucCollation, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetIntProperty)(NativeUInt hObj, unsigned ulPropertyID, PUNSIGNED32 pulProperty);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetIntProperty)(NativeUInt hObj, unsigned ulPropertyID, PUNSIGNED32 pulProperty);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetConnectionType)(NativeUInt hConnect, PUNSIGNED16 pusConnectType);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetConnectionType)(NativeUInt hConnect, PUNSIGNED16 pusConnectType);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetTransactionCount)(NativeUInt hConnect, PUNSIGNED32 pulTransactionCount);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetTransactionCount)(NativeUInt hConnect, PUNSIGNED32 pulTransactionCount);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetConnectionPath)(NativeUInt hConnect, PAceChar pucConnectionPath, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetConnectionPath)(NativeUInt hConnect, PAceChar pucConnectionPath, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetConnectionProperty)(NativeUInt hConnect, System::Word usPropertyID, void * pvProperty, PUNSIGNED32 pulPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetConnectionProperty)(NativeUInt hConnect, System::Word usPropertyID, void * pvProperty, PUNSIGNED32 pulPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetDate)(NativeUInt hTable, PAceChar pucFldName, PAceChar pucBuf, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetDate)(NativeUInt hTable, PAceChar pucFldName, PAceChar pucBuf, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetDateFormat)(PAceChar pucFormat, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetDateFormat)(PAceChar pucFormat, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetDateFormat60)(NativeUInt hConnect, PAceChar pucFormat, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetDateFormat60)(NativeUInt hConnect, PAceChar pucFormat, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetDecimals)(PUNSIGNED16 pusDecimals);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetDecimals)(PUNSIGNED16 pusDecimals);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetDefault)(PAceChar pucDefault, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetDefault)(PAceChar pucDefault, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetDeleted)(PUNSIGNED16 pbUseDeleted);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetDeleted)(PUNSIGNED16 pbUseDeleted);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetDouble)(NativeUInt hTable, PAceChar pucFldName, System::PDouble pdValue);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetDouble)(NativeUInt hTable, PAceChar pucFldName, System::PDouble pdValue);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetEpoch)(PUNSIGNED16 pusCentury);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetEpoch)(PUNSIGNED16 pusCentury);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetErrorString)(unsigned ulErrCode, PAceChar pucBuf, PUNSIGNED16 pusBufLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetErrorString)(unsigned ulErrCode, PAceChar pucBuf, PUNSIGNED16 pusBufLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetExact)(PUNSIGNED16 pbExact);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetExact)(PUNSIGNED16 pbExact);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetExact22)(NativeUInt hObj, PUNSIGNED16 pbExact);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetExact22)(NativeUInt hObj, PUNSIGNED16 pbExact);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetField)(NativeUInt hTable, PAceChar pucFldName, PAceChar pucBuf, PUNSIGNED32 pulLen, System::Word usOption);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetField)(NativeUInt hTable, PAceChar pucFldName, PAceChar pucBuf, PUNSIGNED32 pulLen, System::Word usOption);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetFieldW)(NativeUInt hObj, PAceChar pucFldName, System::WideChar * pwcBuf, PUNSIGNED32 pulLen, System::Word usOption);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetFieldW)(NativeUInt hObj, PAceChar pucFldName, System::WideChar * pwcBuf, PUNSIGNED32 pulLen, System::Word usOption);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetFieldDecimals)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pusDecimals);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetFieldDecimals)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pusDecimals);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetFieldLength)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED32 pulLength);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetFieldLength)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED32 pulLength);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetFieldName)(NativeUInt hTable, System::Word usFld, PAceChar pucName, PUNSIGNED16 pusBufLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetFieldName)(NativeUInt hTable, System::Word usFld, PAceChar pucName, PUNSIGNED16 pusBufLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetFieldNum)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pusNum);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetFieldNum)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pusNum);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetFieldOffset)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED32 pulOffset);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetFieldOffset)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED32 pulOffset);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetFieldType)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pusType);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetFieldType)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pusType);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetFilter)(NativeUInt hTable, PAceChar pucFilter, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetFilter)(NativeUInt hTable, PAceChar pucFilter, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetHandleLong)(NativeUInt hObj, PUNSIGNED32 pulVal);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetHandleLong)(NativeUInt hObj, PUNSIGNED32 pulVal);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetHandleType)(NativeUInt hObj, PUNSIGNED16 pusType);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetHandleType)(NativeUInt hObj, PUNSIGNED16 pusType);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetIndexCondition)(NativeUInt hIndex, PAceChar pucExpr, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetIndexCondition)(NativeUInt hIndex, PAceChar pucExpr, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetIndexExpr)(NativeUInt hIndex, PAceChar pucExpr, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetIndexExpr)(NativeUInt hIndex, PAceChar pucExpr, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetIndexFilename)(NativeUInt hIndex, System::Word usOption, PAceChar pucName, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetIndexFilename)(NativeUInt hIndex, System::Word usOption, PAceChar pucName, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetIndexHandle)(NativeUInt hTable, PAceChar pucIndexOrder, PADSHANDLE phIndex);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetIndexHandle)(NativeUInt hTable, PAceChar pucIndexOrder, PADSHANDLE phIndex);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetIndexHandleByOrder)(NativeUInt hTable, System::Word usOrderNum, PADSHANDLE phIndex);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetIndexHandleByOrder)(NativeUInt hTable, System::Word usOrderNum, PADSHANDLE phIndex);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetIndexHandleByExpr)(NativeUInt hTable, PAceChar pucExpr, unsigned ulDescending, PADSHANDLE phIndex);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetIndexHandleByExpr)(NativeUInt hTable, PAceChar pucExpr, unsigned ulDescending, PADSHANDLE phIndex);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetIndexName)(NativeUInt hIndex, PAceChar pucName, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetIndexName)(NativeUInt hIndex, PAceChar pucName, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetIndexOrderByHandle)(NativeUInt hIndex, PUNSIGNED16 pusIndexOrder);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetIndexOrderByHandle)(NativeUInt hIndex, PUNSIGNED16 pusIndexOrder);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetJulian)(NativeUInt hTable, PAceChar pucFldName, PSIGNED32 plDate);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetJulian)(NativeUInt hTable, PAceChar pucFldName, PSIGNED32 plDate);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetKeyCount)(NativeUInt hIndex, System::Word usFilterOption, PUNSIGNED32 pulCount);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetKeyCount)(NativeUInt hIndex, System::Word usFilterOption, PUNSIGNED32 pulCount);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetKeyNum)(NativeUInt hIndex, System::Word usFilterOption, PUNSIGNED32 pulKey);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetKeyNum)(NativeUInt hIndex, System::Word usFilterOption, PUNSIGNED32 pulKey);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetKeyLength)(NativeUInt hIndex, PUNSIGNED16 pusKeyLength);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetKeyLength)(NativeUInt hIndex, PUNSIGNED16 pusKeyLength);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetKeyType)(NativeUInt hIndex, PUNSIGNED16 usKeyType);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetKeyType)(NativeUInt hIndex, PUNSIGNED16 usKeyType);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetLastError)(PUNSIGNED32 pulErrCode, PAceChar pucBuf, PUNSIGNED16 pusBufLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetLastError)(PUNSIGNED32 pulErrCode, PAceChar pucBuf, PUNSIGNED16 pusBufLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetLastTableUpdate)(NativeUInt hTable, PAceChar pucDate, PUNSIGNED16 pusDateLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetLastTableUpdate)(NativeUInt hTable, PAceChar pucDate, PUNSIGNED16 pusDateLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetLogical)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pbValue);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetLogical)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pbValue);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetLong)(NativeUInt hTable, PAceChar pucFldName, PSIGNED32 plValue);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetLong)(NativeUInt hTable, PAceChar pucFldName, PSIGNED32 plValue);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetLongLong)(NativeUInt hTable, PAceChar pucFldName, PSIGNED64 pqValue);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetLongLong)(NativeUInt hTable, PAceChar pucFldName, PSIGNED64 pqValue);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetMemoBlockSize)(NativeUInt hTable, PUNSIGNED16 pusBlockSize);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetMemoBlockSize)(NativeUInt hTable, PUNSIGNED16 pusBlockSize);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetMemoLength)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED32 pulLength);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetMemoLength)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED32 pulLength);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetMemoDataType)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pusType);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetMemoDataType)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pusType);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetMilliseconds)(NativeUInt hTable, PAceChar pucFldName, PSIGNED32 plTime);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetMilliseconds)(NativeUInt hTable, PAceChar pucFldName, PSIGNED32 plTime);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetMoney)(NativeUInt hTbl, PAceChar pucFldName, PSIGNED64 pqValue);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetMoney)(NativeUInt hTbl, PAceChar pucFldName, PSIGNED64 pqValue);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetActiveLinkInfo)(NativeUInt hDBConn, System::Word usLinkNum, PAceChar pucLinkInfo, PUNSIGNED16 pusBufferLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetActiveLinkInfo)(NativeUInt hDBConn, System::Word usLinkNum, PAceChar pucLinkInfo, PUNSIGNED16 pusBufferLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetNumActiveLinks)(NativeUInt hDBConn, PUNSIGNED16 pusNumLinks);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetNumActiveLinks)(NativeUInt hDBConn, PUNSIGNED16 pusNumLinks);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetNumFields)(NativeUInt hTable, PUNSIGNED16 pusCount);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetNumFields)(NativeUInt hTable, PUNSIGNED16 pusCount);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetNumIndexes)(NativeUInt hTable, PUNSIGNED16 pusNum);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetNumIndexes)(NativeUInt hTable, PUNSIGNED16 pusNum);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetNumFTSIndexes)(NativeUInt hTable, PUNSIGNED16 pusNum);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetNumFTSIndexes)(NativeUInt hTable, PUNSIGNED16 pusNum);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetNumLocks)(NativeUInt hTable, PUNSIGNED16 pusNum);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetNumLocks)(NativeUInt hTable, PUNSIGNED16 pusNum);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetNumOpenTables)(PUNSIGNED16 pusNum);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetNumOpenTables)(PUNSIGNED16 pusNum);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetRecord)(NativeUInt hTable, PAceChar pucRec, PUNSIGNED32 pulLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetRecord)(NativeUInt hTable, PAceChar pucRec, PUNSIGNED32 pulLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetRecordCount)(NativeUInt hTable, System::Word usFilterOption, PUNSIGNED32 pulCount);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetRecordCount)(NativeUInt hTable, System::Word usFilterOption, PUNSIGNED32 pulCount);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetRecordNum)(NativeUInt hTable, System::Word usFilterOption, PUNSIGNED32 pulRec);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetRecordNum)(NativeUInt hTable, System::Word usFilterOption, PUNSIGNED32 pulRec);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetRecordLength)(NativeUInt hTable, PUNSIGNED32 pulLength);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetRecordLength)(NativeUInt hTable, PUNSIGNED32 pulLength);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetRecordCRC)(NativeUInt hTable, PUNSIGNED32 pulCRC, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetRecordCRC)(NativeUInt hTable, PUNSIGNED32 pulCRC, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetRelKeyPos)(NativeUInt hIndex, System::PDouble pdPos);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetRelKeyPos)(NativeUInt hIndex, System::PDouble pdPos);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetScope)(NativeUInt hIndex, System::Word usScopeOption, PAceChar pucScope, PUNSIGNED16 pusBufLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetScope)(NativeUInt hIndex, System::Word usScopeOption, PAceChar pucScope, PUNSIGNED16 pusBufLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetSearchPath)(PAceChar pucPath, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetSearchPath)(PAceChar pucPath, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetServerName)(NativeUInt hConnect, PAceChar pucName, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetServerName)(NativeUInt hConnect, PAceChar pucName, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetServerTime)(NativeUInt hConnect, PAceChar pucDateBuf, PUNSIGNED16 pusDateBufLen, PSIGNED32 plTime, PAceChar pucTimeBuf, PUNSIGNED16 pusTimeBufLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetServerTime)(NativeUInt hConnect, PAceChar pucDateBuf, PUNSIGNED16 pusDateBufLen, PSIGNED32 plTime, PAceChar pucTimeBuf, PUNSIGNED16 pusTimeBufLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetShort)(NativeUInt hTable, PAceChar pucFldName, PSIGNED16 psValue);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetShort)(NativeUInt hTable, PAceChar pucFldName, PSIGNED16 psValue);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetString)(NativeUInt hTable, PAceChar pucFldName, PAceChar pucBuf, PUNSIGNED32 pulLen, System::Word usOption);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetString)(NativeUInt hTable, PAceChar pucFldName, PAceChar pucBuf, PUNSIGNED32 pulLen, System::Word usOption);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetStringW)(NativeUInt hObj, PAceChar pucFldName, System::WideChar * pwcBuf, PUNSIGNED32 pulLen, System::Word usOption);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetStringW)(NativeUInt hObj, PAceChar pucFldName, System::WideChar * pwcBuf, PUNSIGNED32 pulLen, System::Word usOption);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetTableAlias)(NativeUInt hTable, PAceChar pucAlias, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetTableAlias)(NativeUInt hTable, PAceChar pucAlias, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetTableCharType)(NativeUInt hTable, PUNSIGNED16 pusCharType);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetTableCharType)(NativeUInt hTable, PUNSIGNED16 pusCharType);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetTableConnection)(NativeUInt hTable, PADSHANDLE phConnect);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetTableConnection)(NativeUInt hTable, PADSHANDLE phConnect);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetTableFilename)(NativeUInt hTable, System::Word usOption, PAceChar pucName, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetTableFilename)(NativeUInt hTable, System::Word usOption, PAceChar pucName, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetTableHandle)(PAceChar pucName, PADSHANDLE phTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetTableHandle)(PAceChar pucName, PADSHANDLE phTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetTableHandle25)(NativeUInt hConnect, PAceChar pucName, PADSHANDLE phTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetTableHandle25)(NativeUInt hConnect, PAceChar pucName, PADSHANDLE phTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetTableLockType)(NativeUInt hTable, PUNSIGNED16 pusLockType);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetTableLockType)(NativeUInt hTable, PUNSIGNED16 pusLockType);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetTableMemoSize)(NativeUInt hTable, PUNSIGNED16 pusMemoSize);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetTableMemoSize)(NativeUInt hTable, PUNSIGNED16 pusMemoSize);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetTableOpenOptions)(NativeUInt hTable, PUNSIGNED32 pulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetTableOpenOptions)(NativeUInt hTable, PUNSIGNED32 pulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetTableRights)(NativeUInt hTable, PUNSIGNED16 pusRights);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetTableRights)(NativeUInt hTable, PUNSIGNED16 pusRights);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetTableType)(NativeUInt hTable, PUNSIGNED16 pusType);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetTableType)(NativeUInt hTable, PUNSIGNED16 pusType);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetTime)(NativeUInt hTable, PAceChar pucFldName, PAceChar pucBuf, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetTime)(NativeUInt hTable, PAceChar pucFldName, PAceChar pucBuf, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetVersion)(PUNSIGNED32 pulMajor, PUNSIGNED32 pulMinor, PAceChar pucLetter, PAceChar pucDesc, PUNSIGNED16 pusDescLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetVersion)(PUNSIGNED32 pulMajor, PUNSIGNED32 pulMinor, PAceChar pucLetter, PAceChar pucDesc, PUNSIGNED16 pusDescLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGotoBookmark)(NativeUInt hTable, NativeUInt hBookmark);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGotoBookmark)(NativeUInt hTable, NativeUInt hBookmark);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGotoBookmark60)(NativeUInt hObj, PAceChar pucBookmark);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGotoBookmark60)(NativeUInt hObj, PAceChar pucBookmark);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGotoBottom)(NativeUInt hObj);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGotoBottom)(NativeUInt hObj);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGotoRecord)(NativeUInt hTable, unsigned ulRec);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGotoRecord)(NativeUInt hTable, unsigned ulRec);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGotoTop)(NativeUInt hObj);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGotoTop)(NativeUInt hObj);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsImageToClipboard)(NativeUInt hTable, PAceChar pucFldName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsImageToClipboard)(NativeUInt hTable, PAceChar pucFldName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsInTransaction)(NativeUInt hConnect, PUNSIGNED16 pbInTrans);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsInTransaction)(NativeUInt hConnect, PUNSIGNED16 pbInTrans);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsEmpty)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pbEmpty);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsEmpty)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pbEmpty);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsExprValid)(NativeUInt hTable, PAceChar pucExpr, PUNSIGNED16 pbValid);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsExprValid)(NativeUInt hTable, PAceChar pucExpr, PUNSIGNED16 pbValid);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsFound)(NativeUInt hObj, PUNSIGNED16 pbFound);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsFound)(NativeUInt hObj, PUNSIGNED16 pbFound);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsIndexCompound)(NativeUInt hIndex, PUNSIGNED16 pbCompound);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsIndexCompound)(NativeUInt hIndex, PUNSIGNED16 pbCompound);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsIndexCandidate)(NativeUInt hIndex, PUNSIGNED16 pbCandidate);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsIndexCandidate)(NativeUInt hIndex, PUNSIGNED16 pbCandidate);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsIndexNullable)(NativeUInt hIndex, PUNSIGNED16 pbNullable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsIndexNullable)(NativeUInt hIndex, PUNSIGNED16 pbNullable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsIndexCustom)(NativeUInt hIndex, PUNSIGNED16 pbCustom);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsIndexCustom)(NativeUInt hIndex, PUNSIGNED16 pbCustom);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsIndexDescending)(NativeUInt hIndex, PUNSIGNED16 pbDescending);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsIndexDescending)(NativeUInt hIndex, PUNSIGNED16 pbDescending);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsIndexPrimaryKey)(NativeUInt hIndex, PUNSIGNED16 pbPrimaryKey);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsIndexPrimaryKey)(NativeUInt hIndex, PUNSIGNED16 pbPrimaryKey);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsIndexFTS)(NativeUInt hIndex, PUNSIGNED16 pbFTS);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsIndexFTS)(NativeUInt hIndex, PUNSIGNED16 pbFTS);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsIndexUnique)(NativeUInt hIndex, PUNSIGNED16 pbUnique);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsIndexUnique)(NativeUInt hIndex, PUNSIGNED16 pbUnique);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsRecordDeleted)(NativeUInt hTable, PUNSIGNED16 pbDeleted);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsRecordDeleted)(NativeUInt hTable, PUNSIGNED16 pbDeleted);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsRecordEncrypted)(NativeUInt hTable, PUNSIGNED16 pbEncrypted);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsRecordEncrypted)(NativeUInt hTable, PUNSIGNED16 pbEncrypted);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsRecordLocked)(NativeUInt hTable, unsigned ulRec, PUNSIGNED16 pbLocked);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsRecordLocked)(NativeUInt hTable, unsigned ulRec, PUNSIGNED16 pbLocked);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsRecordVisible)(NativeUInt hObj, PUNSIGNED16 pbVisible);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsRecordVisible)(NativeUInt hObj, PUNSIGNED16 pbVisible);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsServerLoaded)(PAceChar pucServer, PUNSIGNED16 pbLoaded);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsServerLoaded)(PAceChar pucServer, PUNSIGNED16 pbLoaded);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsTableEncrypted)(NativeUInt hTable, PUNSIGNED16 pbEncrypted);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsTableEncrypted)(NativeUInt hTable, PUNSIGNED16 pbEncrypted);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsTableLocked)(NativeUInt hTable, PUNSIGNED16 pbLocked);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsTableLocked)(NativeUInt hTable, PUNSIGNED16 pbLocked);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsLocate)(NativeUInt hTable, PAceChar pucExpr, System::Word bForward, PUNSIGNED16 pbFound);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsLocate)(NativeUInt hTable, PAceChar pucExpr, System::Word bForward, PUNSIGNED16 pbFound);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsLockRecord)(NativeUInt hTable, unsigned ulRec);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsLockRecord)(NativeUInt hTable, unsigned ulRec);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsLockTable)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsLockTable)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsLookupKey)(NativeUInt hIndex, PAceChar pucKey, System::Word usKeyLen, System::Word usDataType, PUNSIGNED16 pbFound);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsLookupKey)(NativeUInt hIndex, PAceChar pucKey, System::Word usKeyLen, System::Word usDataType, PUNSIGNED16 pbFound);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgConnect)(PAceChar pucServerName, PAceChar pucUserName, PAceChar pucPassword, PADSHANDLE phMgmtHandle);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgConnect)(PAceChar pucServerName, PAceChar pucUserName, PAceChar pucPassword, PADSHANDLE phMgmtHandle);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgDisconnect)(NativeUInt hMgmtHandle);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgDisconnect)(NativeUInt hMgmtHandle);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgGetCommStats)(NativeUInt hMgmtHandle, PADS_MGMT_COMM_STATS pstCommStats, PUNSIGNED16 pusStructSize);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgGetCommStats)(NativeUInt hMgmtHandle, PADS_MGMT_COMM_STATS pstCommStats, PUNSIGNED16 pusStructSize);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgResetCommStats)(NativeUInt hMgmtHandle);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgResetCommStats)(NativeUInt hMgmtHandle);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgDumpInternalTables)(NativeUInt hMgmtHandle);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgDumpInternalTables)(NativeUInt hMgmtHandle);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgGetConfigInfo)(NativeUInt hMgmtHandle, PADS_MGMT_CONFIG_PARAMS pstConfigValues, PUNSIGNED16 pusConfigValuesStructSize, PADS_MGMT_CONFIG_MEMORY pstConfigMemory, PUNSIGNED16 pusConfigMemoryStructSize);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgGetConfigInfo)(NativeUInt hMgmtHandle, PADS_MGMT_CONFIG_PARAMS pstConfigValues, PUNSIGNED16 pusConfigValuesStructSize, PADS_MGMT_CONFIG_MEMORY pstConfigMemory, PUNSIGNED16 pusConfigMemoryStructSize);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgGetInstallInfo)(NativeUInt hMgmtHandle, PADS_MGMT_INSTALL_INFO pstInstallInfo, PUNSIGNED16 pusStructSize);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgGetInstallInfo)(NativeUInt hMgmtHandle, PADS_MGMT_INSTALL_INFO pstInstallInfo, PUNSIGNED16 pusStructSize);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgGetActivityInfo)(NativeUInt hMgmtHandle, PADS_MGMT_ACTIVITY_INFO pstActivityInfo, PUNSIGNED16 pusStructSize);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgGetActivityInfo)(NativeUInt hMgmtHandle, PADS_MGMT_ACTIVITY_INFO pstActivityInfo, PUNSIGNED16 pusStructSize);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgGetUserNames)(NativeUInt hMgmtHandle, PAceChar pucFileName, PADSMgUserArray astUserInfo, PUNSIGNED16 pusArrayLen, PUNSIGNED16 pusStructSize);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgGetUserNames)(NativeUInt hMgmtHandle, PAceChar pucFileName, PADSMgUserArray astUserInfo, PUNSIGNED16 pusArrayLen, PUNSIGNED16 pusStructSize);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgGetOpenTables)(NativeUInt hMgmtHandle, PAceChar pucUserName, System::Word usConnNumber, PADSMgTableArray astOpenTableInfo, PUNSIGNED16 pusArrayLen, PUNSIGNED16 pusStructSize);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgGetOpenTables)(NativeUInt hMgmtHandle, PAceChar pucUserName, System::Word usConnNumber, PADSMgTableArray astOpenTableInfo, PUNSIGNED16 pusArrayLen, PUNSIGNED16 pusStructSize);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgGetOpenIndexes)(NativeUInt hMgmtHandle, PAceChar pucTableName, PAceChar pucUserName, System::Word usConnNumber, PADSMgIndexArray astOpenIndexInfo, PUNSIGNED16 pusArrayLen, PUNSIGNED16 pusStructSize);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgGetOpenIndexes)(NativeUInt hMgmtHandle, PAceChar pucTableName, PAceChar pucUserName, System::Word usConnNumber, PADSMgIndexArray astOpenIndexInfo, PUNSIGNED16 pusArrayLen, PUNSIGNED16 pusStructSize);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgGetLocks)(NativeUInt hMgmtHandle, PAceChar pucTableName, PAceChar pucUserName, System::Word usConnNumber, PADSMgLocksArray astRecordInfo, PUNSIGNED16 pusArrayLen, PUNSIGNED16 pusStructSize);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgGetLocks)(NativeUInt hMgmtHandle, PAceChar pucTableName, PAceChar pucUserName, System::Word usConnNumber, PADSMgLocksArray astRecordInfo, PUNSIGNED16 pusArrayLen, PUNSIGNED16 pusStructSize);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgGetServerType)(NativeUInt hMgmtHandle, PUNSIGNED16 pusServerType);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgGetServerType)(NativeUInt hMgmtHandle, PUNSIGNED16 pusServerType);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgKillUser)(NativeUInt hMgmtHandle, PAceChar pucUserName, System::Word usConnNumber);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgKillUser)(NativeUInt hMgmtHandle, PAceChar pucUserName, System::Word usConnNumber);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgGetWorkerThreadActivity)(NativeUInt hMgmtHandle, PADSMgThreadsArray astWorkerThreadActivity, PUNSIGNED16 pusArrayLen, PUNSIGNED16 pusStructSize);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgGetWorkerThreadActivity)(NativeUInt hMgmtHandle, PADSMgThreadsArray astWorkerThreadActivity, PUNSIGNED16 pusArrayLen, PUNSIGNED16 pusStructSize);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgGetLockOwner)(NativeUInt hMgmtHandle, PAceChar pucTableName, unsigned ulRecordNumber, PADS_MGMT_USER_INFO pstUserInfo, PUNSIGNED16 pusStructSize, PUNSIGNED16 pusLockType);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgGetLockOwner)(NativeUInt hMgmtHandle, PAceChar pucTableName, unsigned ulRecordNumber, PADS_MGMT_USER_INFO pstUserInfo, PUNSIGNED16 pusStructSize, PUNSIGNED16 pusLockType);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsNullTerminateStrings)(System::Word bNullTerminate);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsNullTerminateStrings)(System::Word bNullTerminate);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsOpenIndex)(NativeUInt hTable, PAceChar pucName, PADSIndexArray ahIndex, PUNSIGNED16 pusArrayLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsOpenIndex)(NativeUInt hTable, PAceChar pucName, PADSIndexArray ahIndex, PUNSIGNED16 pusArrayLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsOpenTable)(NativeUInt hConnect, PAceChar pucName, PAceChar pucAlias, System::Word usTableType, System::Word usCharType, System::Word usLockType, System::Word usCheckRights, unsigned ulOptions, PADSHANDLE phTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsOpenTable)(NativeUInt hConnect, PAceChar pucName, PAceChar pucAlias, System::Word usTableType, System::Word usCharType, System::Word usLockType, System::Word usCheckRights, unsigned ulOptions, PADSHANDLE phTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsOpenTable90)(NativeUInt hConnect, PAceChar pucName, PAceChar pucAlias, System::Word usTableType, System::Word usCharType, System::Word usLockType, System::Word usCheckRights, unsigned ulOptions, PAceChar pucCollation, PADSHANDLE phTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsOpenTable90)(NativeUInt hConnect, PAceChar pucName, PAceChar pucAlias, System::Word usTableType, System::Word usCharType, System::Word usLockType, System::Word usCheckRights, unsigned ulOptions, PAceChar pucCollation, PADSHANDLE phTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsOpenTable101)(NativeUInt hConnect, PAceChar pucName, PADSHANDLE phTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsOpenTable101)(NativeUInt hConnect, PAceChar pucName, PADSHANDLE phTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsPackTable)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsPackTable)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsPackTable120)(NativeUInt hTable, unsigned ulMemoBlockSize, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsPackTable120)(NativeUInt hTable, unsigned ulMemoBlockSize, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsRecallRecord)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsRecallRecord)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsRecallAllRecords)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsRecallAllRecords)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsRefreshRecord)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsRefreshRecord)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsClearProgressCallback)(void);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsClearProgressCallback)(void);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsRegisterProgressCallback)(TProgressCallback Callback);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsRegisterProgressCallback)(TProgressCallback Callback);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsRegisterCallbackFunction)(TCallbackFunction Callback, unsigned ulCallbackID);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsRegisterCallbackFunction)(TCallbackFunction Callback, unsigned ulCallbackID);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsRegisterCallbackFunction101)(TCallbackFunction101 Callback, __int64 qCallbackID);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsRegisterCallbackFunction101)(TCallbackFunction101 Callback, __int64 qCallbackID);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsClearCallbackFunction)(void);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsClearCallbackFunction)(void);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetSQLTimeout)(NativeUInt hObj, unsigned ulTimeout);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetSQLTimeout)(NativeUInt hObj, unsigned ulTimeout);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsReindex)(NativeUInt hObject);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsReindex)(NativeUInt hObject);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsReindex61)(NativeUInt hObject, unsigned ulPageSize);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsReindex61)(NativeUInt hObject, unsigned ulPageSize);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsReindexFTS)(NativeUInt hObject, unsigned ulPageSize);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsReindexFTS)(NativeUInt hObject, unsigned ulPageSize);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsResetConnection)(NativeUInt hConnect);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsResetConnection)(NativeUInt hConnect);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsRollbackTransaction)(NativeUInt hConnect);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsRollbackTransaction)(NativeUInt hConnect);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSeek)(NativeUInt hIndex, PAceChar pucKey, System::Word usKeyLen, System::Word usDataType, System::Word usSeekType, PUNSIGNED16 pbFound);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSeek)(NativeUInt hIndex, PAceChar pucKey, System::Word usKeyLen, System::Word usDataType, System::Word usSeekType, PUNSIGNED16 pbFound);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSeekLast)(NativeUInt hIndex, PAceChar pucKey, System::Word usKeyLen, System::Word usDataType, PUNSIGNED16 pbFound);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSeekLast)(NativeUInt hIndex, PAceChar pucKey, System::Word usKeyLen, System::Word usDataType, PUNSIGNED16 pbFound);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetBinary)(NativeUInt hTable, PAceChar pucFldName, System::Word usBinaryType, unsigned ulTotalLength, unsigned ulOffset, PAceBinary pucBuf, unsigned ulLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetBinary)(NativeUInt hTable, PAceChar pucFldName, System::Word usBinaryType, unsigned ulTotalLength, unsigned ulOffset, PAceBinary pucBuf, unsigned ulLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetCollationLang)(PAceChar pucLang);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetCollationLang)(PAceChar pucLang);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetCollation)(NativeUInt hConnect, PAceChar pucCollation);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetCollation)(NativeUInt hConnect, PAceChar pucCollation);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetDate)(NativeUInt hObj, PAceChar pucFldName, PAceChar pucValue, System::Word usLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetDate)(NativeUInt hObj, PAceChar pucFldName, PAceChar pucValue, System::Word usLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetDateFormat)(PAceChar pucFormat);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetDateFormat)(PAceChar pucFormat);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetDateFormat60)(NativeUInt hConnect, PAceChar pucFormat);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetDateFormat60)(NativeUInt hConnect, PAceChar pucFormat);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetDecimals)(System::Word usDecimals);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetDecimals)(System::Word usDecimals);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetDefault)(PAceChar pucDefault);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetDefault)(PAceChar pucDefault);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsShowDeleted)(System::Word bShowDeleted);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsShowDeleted)(System::Word bShowDeleted);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetDouble)(NativeUInt hObj, PAceChar pucFldName, double dValue);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetDouble)(NativeUInt hObj, PAceChar pucFldName, double dValue);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetEmpty)(NativeUInt hObj, PAceChar pucFldName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetEmpty)(NativeUInt hObj, PAceChar pucFldName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetEpoch)(System::Word usCentury);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetEpoch)(System::Word usCentury);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetExact)(System::Word bExact);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetExact)(System::Word bExact);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetExact22)(NativeUInt hObj, System::Word bExact);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetExact22)(NativeUInt hObj, System::Word bExact);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetField)(NativeUInt hObj, PAceChar pucFldName, PAceChar pucBuf, unsigned ulLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetField)(NativeUInt hObj, PAceChar pucFldName, PAceChar pucBuf, unsigned ulLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetFieldW)(NativeUInt hObj, PAceChar pucFldName, System::WideChar * pwcBuf, unsigned ulLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetFieldW)(NativeUInt hObj, PAceChar pucFldName, System::WideChar * pwcBuf, unsigned ulLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetFilter)(NativeUInt hTable, PAceChar pucFilter);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetFilter)(NativeUInt hTable, PAceChar pucFilter);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetFilter100)(NativeUInt hTable, void * pvFilter, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetFilter100)(NativeUInt hTable, void * pvFilter, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetHandleLong)(NativeUInt hObj, unsigned ulVal);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetHandleLong)(NativeUInt hObj, unsigned ulVal);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetJulian)(NativeUInt hObj, PAceChar pucFldName, int lDate);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetJulian)(NativeUInt hObj, PAceChar pucFldName, int lDate);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetLogical)(NativeUInt hObj, PAceChar pucFldName, System::Word bValue);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetLogical)(NativeUInt hObj, PAceChar pucFldName, System::Word bValue);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetLong)(NativeUInt hObj, PAceChar pucFldName, int lValue);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetLong)(NativeUInt hObj, PAceChar pucFldName, int lValue);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetLongLong)(NativeUInt hObj, PAceChar pucFldName, __int64 qValue);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetLongLong)(NativeUInt hObj, PAceChar pucFldName, __int64 qValue);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetMilliseconds)(NativeUInt hObj, PAceChar pucFldName, int lTime);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetMilliseconds)(NativeUInt hObj, PAceChar pucFldName, int lTime);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetMoney)(NativeUInt hObj, PAceChar pucFldName, __int64 qValue);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetMoney)(NativeUInt hObj, PAceChar pucFldName, __int64 qValue);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetRecord)(NativeUInt hObj, PAceChar pucRec, unsigned ulLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetRecord)(NativeUInt hObj, PAceChar pucRec, unsigned ulLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetRelation)(NativeUInt hTableParent, NativeUInt hIndexChild, PAceChar pucExpr);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetRelation)(NativeUInt hTableParent, NativeUInt hIndexChild, PAceChar pucExpr);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetRelKeyPos)(NativeUInt hIndex, double dPos);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetRelKeyPos)(NativeUInt hIndex, double dPos);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetScope)(NativeUInt hIndex, System::Word usScopeOption, PAceChar pucScope, System::Word usScopeLen, System::Word usDataType);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetScope)(NativeUInt hIndex, System::Word usScopeOption, PAceChar pucScope, System::Word usScopeLen, System::Word usDataType);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetScopedRelation)(NativeUInt hTableParent, NativeUInt hIndexChild, PAceChar pucExpr);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetScopedRelation)(NativeUInt hTableParent, NativeUInt hIndexChild, PAceChar pucExpr);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetSearchPath)(PAceChar pucPath);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetSearchPath)(PAceChar pucPath);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetServerType)(System::Word usServerOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetServerType)(System::Word usServerOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetShort)(NativeUInt hObj, PAceChar pucFldName, short sValue);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetShort)(NativeUInt hObj, PAceChar pucFldName, short sValue);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetString)(NativeUInt hObj, PAceChar pucFldName, PAceChar pucBuf, unsigned ulLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetString)(NativeUInt hObj, PAceChar pucFldName, PAceChar pucBuf, unsigned ulLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetStringW)(NativeUInt hObj, PAceChar pucFldName, System::WideChar * pwcBuf, unsigned ulLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetStringW)(NativeUInt hObj, PAceChar pucFldName, System::WideChar * pwcBuf, unsigned ulLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetStringFromCodePage)(NativeUInt hObj, unsigned ulCodePage, PAceChar pucFldName, PAceChar pucBuf, unsigned ulLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetStringFromCodePage)(NativeUInt hObj, unsigned ulCodePage, PAceChar pucFldName, PAceChar pucBuf, unsigned ulLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetTime)(NativeUInt hObj, PAceChar pucFldName, PAceChar pucValue, System::Word usLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetTime)(NativeUInt hObj, PAceChar pucFldName, PAceChar pucValue, System::Word usLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsShowError)(PAceChar pucTitle);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsShowError)(PAceChar pucTitle);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSkip)(NativeUInt hObj, int lRecs);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSkip)(NativeUInt hObj, int lRecs);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSkipUnique)(NativeUInt hIndex, int lRecs);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSkipUnique)(NativeUInt hIndex, int lRecs);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsThreadExit)(void);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsThreadExit)(void);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsUnlockRecord)(NativeUInt hTable, unsigned ulRec);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsUnlockRecord)(NativeUInt hTable, unsigned ulRec);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsUnlockTable)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsUnlockTable)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsVerifyPassword)(NativeUInt hTable, PUNSIGNED16 pusEnabled);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsVerifyPassword)(NativeUInt hTable, PUNSIGNED16 pusEnabled);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsEncryptionEnabled)(NativeUInt hTable, PUNSIGNED16 pusEnabled);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsEncryptionEnabled)(NativeUInt hTable, PUNSIGNED16 pusEnabled);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsWriteAllRecords)(void);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsWriteAllRecords)(void);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsWriteRecord)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsWriteRecord)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsZapTable)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsZapTable)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetAOF)(NativeUInt hTable, PAceChar pucFilter, System::Word usOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetAOF)(NativeUInt hTable, PAceChar pucFilter, System::Word usOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetAOF100)(NativeUInt hTable, void * pvFilter, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetAOF100)(NativeUInt hTable, void * pvFilter, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsEvalAOF)(NativeUInt hTable, PAceChar pucFilter, PUNSIGNED16 pusOptLevel);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsEvalAOF)(NativeUInt hTable, PAceChar pucFilter, PUNSIGNED16 pusOptLevel);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsEvalAOF100)(NativeUInt hTable, void * pvFilter, unsigned ulOptions, PUNSIGNED16 pusOptLevel);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsEvalAOF100)(NativeUInt hTable, void * pvFilter, unsigned ulOptions, PUNSIGNED16 pusOptLevel);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsClearAOF)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsClearAOF)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsRefreshAOF)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsRefreshAOF)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetAOF)(NativeUInt hTable, PAceChar pucFilter, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetAOF)(NativeUInt hTable, PAceChar pucFilter, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetAOF100)(NativeUInt hTable, unsigned ulOptions, void * pvFilter, PUNSIGNED32 pulLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetAOF100)(NativeUInt hTable, unsigned ulOptions, void * pvFilter, PUNSIGNED32 pulLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetAOFOptLevel)(NativeUInt hTable, PUNSIGNED16 pusOptLevel, PAceChar pucNonOpt, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetAOFOptLevel)(NativeUInt hTable, PUNSIGNED16 pusOptLevel, PAceChar pucNonOpt, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetAOFOptLevel100)(NativeUInt hTable, PUNSIGNED16 pusOptLevel, void * pvNonOpt, PUNSIGNED32 pulExprLen, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetAOFOptLevel100)(NativeUInt hTable, PUNSIGNED16 pusOptLevel, void * pvNonOpt, PUNSIGNED32 pulExprLen, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsRecordInAOF)(NativeUInt hTable, unsigned ulRecordNum, PUNSIGNED16 pusIsInAOF);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsRecordInAOF)(NativeUInt hTable, unsigned ulRecordNum, PUNSIGNED16 pusIsInAOF);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCustomizeAOF)(NativeUInt hTable, unsigned ulNumRecords, PUNSIGNED32 pulRecords, System::Word usOption);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCustomizeAOF)(NativeUInt hTable, unsigned ulNumRecords, PUNSIGNED32 pulRecords, System::Word usOption);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsInitRawKey)(NativeUInt hIndex);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsInitRawKey)(NativeUInt hIndex);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsBuildRawKey)(NativeUInt hIndex, PAceChar pucKey, System::Word &pusKeyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsBuildRawKey)(NativeUInt hIndex, PAceChar pucKey, System::Word &pusKeyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsBuildRawKey100)(NativeUInt hIndex, PAceChar pucKey, PUNSIGNED16 pusKeyLen, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsBuildRawKey100)(NativeUInt hIndex, PAceChar pucKey, PUNSIGNED16 pusKeyLen, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCreateSQLStatement)(NativeUInt hConnect, PADSHANDLE phStatement);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCreateSQLStatement)(NativeUInt hConnect, PADSHANDLE phStatement);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsPrepareSQL)(NativeUInt hStatement, PAceChar pucSQL);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsPrepareSQL)(NativeUInt hStatement, PAceChar pucSQL);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsPrepareSQLW)(NativeUInt hStatement, System::WideChar * pwcSQL);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsPrepareSQLW)(NativeUInt hStatement, System::WideChar * pwcSQL);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCachePrepareSQL)(NativeUInt hConnect, PAceChar pucSQL, PADSHANDLE phStatement);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCachePrepareSQL)(NativeUInt hConnect, PAceChar pucSQL, PADSHANDLE phStatement);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCachePrepareSQLW)(NativeUInt hConnect, System::WideChar * pwcSQL, PADSHANDLE phStatement);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCachePrepareSQLW)(NativeUInt hConnect, System::WideChar * pwcSQL, PADSHANDLE phStatement);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsExecuteSQL)(NativeUInt hStatement, PADSHANDLE phCursor);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsExecuteSQL)(NativeUInt hStatement, PADSHANDLE phCursor);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsExecuteSQLDirect)(NativeUInt hStatement, PAceChar pucSQL, PADSHANDLE phCursor);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsExecuteSQLDirect)(NativeUInt hStatement, PAceChar pucSQL, PADSHANDLE phCursor);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsExecuteSQLDirectW)(NativeUInt hStatement, System::WideChar * pwcSQL, PADSHANDLE phCursor);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsExecuteSQLDirectW)(NativeUInt hStatement, System::WideChar * pwcSQL, PADSHANDLE phCursor);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCloseSQLStatement)(NativeUInt hStatement);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCloseSQLStatement)(NativeUInt hStatement);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsStmtSetTableRights)(NativeUInt hStatement, System::Word usCheckRights);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsStmtSetTableRights)(NativeUInt hStatement, System::Word usCheckRights);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsStmtSetTableReadOnly)(NativeUInt hStatement, System::Word usReadOnly);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsStmtSetTableReadOnly)(NativeUInt hStatement, System::Word usReadOnly);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsStmtSetTableLockType)(NativeUInt hStatement, System::Word usLockType);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsStmtSetTableLockType)(NativeUInt hStatement, System::Word usLockType);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsStmtSetTableCharType)(NativeUInt hStatement, System::Word usCharType);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsStmtSetTableCharType)(NativeUInt hStatement, System::Word usCharType);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsStmtSetTableType)(NativeUInt hStatement, System::Word usTableType);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsStmtSetTableType)(NativeUInt hStatement, System::Word usTableType);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsStmtSetTableCollation)(NativeUInt hStatement, PAceChar pucCollation);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsStmtSetTableCollation)(NativeUInt hStatement, PAceChar pucCollation);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsStmtConstrainUpdates)(NativeUInt hStatement, System::Word usConstrain);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsStmtConstrainUpdates)(NativeUInt hStatement, System::Word usConstrain);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsStmtEnableEncryption)(NativeUInt hStatement, PAceChar pucPassword);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsStmtEnableEncryption)(NativeUInt hStatement, PAceChar pucPassword);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsStmtDisableEncryption)(NativeUInt hStatement);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsStmtDisableEncryption)(NativeUInt hStatement);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsStmtSetTablePassword)(NativeUInt hStatement, PAceChar pucTableName, PAceChar pucPassword);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsStmtSetTablePassword)(NativeUInt hStatement, PAceChar pucTableName, PAceChar pucPassword);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsStmtClearTablePasswords)(NativeUInt hStatement);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsStmtClearTablePasswords)(NativeUInt hStatement);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsStmtReadAllColumns)(NativeUInt hStatement, System::Word usReadColumns);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsStmtReadAllColumns)(NativeUInt hStatement, System::Word usReadColumns);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsClearSQLParams)(NativeUInt hStatement);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsClearSQLParams)(NativeUInt hStatement);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetTimeStamp)(NativeUInt hObj, PAceChar pucFldName, PAceChar pucBuf, unsigned ulLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetTimeStamp)(NativeUInt hObj, PAceChar pucFldName, PAceChar pucBuf, unsigned ulLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsClearSQLAbortFunc)(void);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsClearSQLAbortFunc)(void);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsRegisterSQLAbortFunc)(TSQLAbortFunc Callback);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsRegisterSQLAbortFunc)(TSQLAbortFunc Callback);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsRegisterUDF)(NativeUInt hObj, System::Word usType, TUDFFunc Callback);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsRegisterUDF)(NativeUInt hObj, System::Word usType, TUDFFunc Callback);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetNumParams)(NativeUInt hStatement, PUNSIGNED16 pusNumParams);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetNumParams)(NativeUInt hStatement, PUNSIGNED16 pusNumParams);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetLastAutoinc)(NativeUInt hObj, PUNSIGNED32 pulAutoIncVal);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetLastAutoinc)(NativeUInt hObj, PUNSIGNED32 pulAutoIncVal);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsIndexUserDefined)(NativeUInt hIndex, PUNSIGNED16 pbUserDefined);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsIndexUserDefined)(NativeUInt hIndex, PUNSIGNED16 pbUserDefined);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsRestructureTable)(NativeUInt hObj, PAceChar pucName, PAceChar pucPassword, System::Word usTableType, System::Word usCharType, System::Word usLockType, System::Word usCheckRights, PAceChar pucAddFields, PAceChar pucDeleteFields, PAceChar pucChangeFields);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsRestructureTable)(NativeUInt hObj, PAceChar pucName, PAceChar pucPassword, System::Word usTableType, System::Word usCharType, System::Word usLockType, System::Word usCheckRights, PAceChar pucAddFields, PAceChar pucDeleteFields, PAceChar pucChangeFields);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsRestructureTable90)(NativeUInt hObj, PAceChar pucName, PAceChar pucPassword, System::Word usTableType, System::Word usCharType, System::Word usLockType, System::Word usCheckRights, PAceChar pucAddFields, PAceChar pucDeleteFields, PAceChar pucChangeFields, PAceChar pucCollation);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsRestructureTable90)(NativeUInt hObj, PAceChar pucName, PAceChar pucPassword, System::Word usTableType, System::Word usCharType, System::Word usLockType, System::Word usCheckRights, PAceChar pucAddFields, PAceChar pucDeleteFields, PAceChar pucChangeFields, PAceChar pucCollation);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsRestructureTable120)(NativeUInt hObj, PAceChar pucName, PAceChar pucPassword, System::Word usTableType, System::Word usCharType, System::Word usLockType, System::Word usCheckRights, PAceChar pucAddFields, PAceChar pucDeleteFields, PAceChar pucChangeFields, PAceChar pucCollation, unsigned ulMemoBlockSize, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsRestructureTable120)(NativeUInt hObj, PAceChar pucName, PAceChar pucPassword, System::Word usTableType, System::Word usCharType, System::Word usLockType, System::Word usCheckRights, PAceChar pucAddFields, PAceChar pucDeleteFields, PAceChar pucChangeFields, PAceChar pucCollation, unsigned ulMemoBlockSize, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetSQLStatementHandle)(NativeUInt hCursor, PADSHANDLE phStmt);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetSQLStatementHandle)(NativeUInt hCursor, PADSHANDLE phStmt);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetSQLStatement)(NativeUInt hStmt, PAceChar pucSQL, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetSQLStatement)(NativeUInt hStmt, PAceChar pucSQL, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsFlushFileBuffers)(NativeUInt hTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsFlushFileBuffers)(NativeUInt hTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDDeployDatabase)(PAceChar pucDestination, PAceChar pucDestinationPassword, PAceChar pucSource, PAceChar pucSourcePassword, System::Word usServerTypes, System::Word usValidateOption, System::Word usBackupFiles, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDDeployDatabase)(PAceChar pucDestination, PAceChar pucDestinationPassword, PAceChar pucSource, PAceChar pucSourcePassword, System::Word usServerTypes, System::Word usValidateOption, System::Word usBackupFiles, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsVerifySQL)(NativeUInt hStatement, PAceChar pucSQL);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsVerifySQL)(NativeUInt hStatement, PAceChar pucSQL);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsVerifySQLW)(NativeUInt hStatement, System::WideChar * pwcSQL);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsVerifySQLW)(NativeUInt hStatement, System::WideChar * pwcSQL);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDisableUniqueEnforcement)(NativeUInt hConnection);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDisableUniqueEnforcement)(NativeUInt hConnection);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsEnableUniqueEnforcement)(NativeUInt hConnection);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsEnableUniqueEnforcement)(NativeUInt hConnection);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDisableRI)(NativeUInt hConnection);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDisableRI)(NativeUInt hConnection);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsEnableRI)(NativeUInt hConnection);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsEnableRI)(NativeUInt hConnection);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDisableAutoIncEnforcement)(NativeUInt hConnection);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDisableAutoIncEnforcement)(NativeUInt hConnection);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsEnableAutoIncEnforcement)(NativeUInt hConnection);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsEnableAutoIncEnforcement)(NativeUInt hConnection);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsRollbackTransaction80)(NativeUInt hConnect, PAceChar pucSavepoint, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsRollbackTransaction80)(NativeUInt hConnect, PAceChar pucSavepoint, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsCreateSavepoint)(NativeUInt hConnect, PAceChar pucSavepoint, unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsCreateSavepoint)(NativeUInt hConnect, PAceChar pucSavepoint, unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDFreeTable)(PAceChar pucTableName, PAceChar pucPassword);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDFreeTable)(PAceChar pucTableName, PAceChar pucPassword);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDSetIndexProperty)(NativeUInt hAdminConn, PAceChar pucTableName, PAceChar pucIndexName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDSetIndexProperty)(NativeUInt hAdminConn, PAceChar pucTableName, PAceChar pucIndexName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsFieldBinary)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pbBinary);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsFieldBinary)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pbBinary);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsNull)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pbNull);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsNull)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pbNull);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsNullable)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pbNullable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsNullable)(NativeUInt hTable, PAceChar pucFldName, PUNSIGNED16 pbNullable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetNull)(NativeUInt hTable, PAceChar pucFldName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetNull)(NativeUInt hTable, PAceChar pucFldName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetTableCollation)(NativeUInt hTbl, PAceChar pucCollation, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetTableCollation)(NativeUInt hTbl, PAceChar pucCollation, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetIndexCollation)(NativeUInt hIndex, PAceChar pucCollation, PUNSIGNED16 pusLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetIndexCollation)(NativeUInt hIndex, PAceChar pucCollation, PUNSIGNED16 pusLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetDataLength)(NativeUInt hTable, PAceChar pucFldName, unsigned ulOptions, PUNSIGNED32 pulLength);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetDataLength)(NativeUInt hTable, PAceChar pucFldName, unsigned ulOptions, PUNSIGNED32 pulLength);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetIndexDirection)(NativeUInt hIndex, System::Word usReverseDirection);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetIndexDirection)(NativeUInt hIndex, System::Word usReverseDirection);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsMgKillUser90)(NativeUInt hMgmtHandle, PAceChar pucUserName, System::Word usConnNumber, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsMgKillUser90)(NativeUInt hMgmtHandle, PAceChar pucUserName, System::Word usConnNumber, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsGetFieldLength100)(NativeUInt hTable, PAceChar pucFldName, unsigned ulOptions, PUNSIGNED32 pulLength);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsGetFieldLength100)(NativeUInt hTable, PAceChar pucFldName, unsigned ulOptions, PUNSIGNED32 pulLength);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetRightsChecking)(unsigned ulOptions);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetRightsChecking)(unsigned ulOptions);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetTableTransactionFree)(NativeUInt hTable, System::Word usTransFree);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetTableTransactionFree)(NativeUInt hTable, System::Word usTransFree);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsIsTableTransactionFree)(NativeUInt hTable, PUNSIGNED16 pusTransFree);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsIsTableTransactionFree)(NativeUInt hTable, PUNSIGNED16 pusTransFree);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsFindServers)(unsigned ulOptions, PADSHANDLE phTable);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsFindServers)(unsigned ulOptions, PADSHANDLE phTable);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsDDSetTriggerProperty)(NativeUInt hDictionary, PAceChar pucTriggerName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsDDSetTriggerProperty)(NativeUInt hDictionary, PAceChar pucTriggerName, System::Word usPropertyID, void * pvProperty, System::Word usPropertyLen);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsBinaryToFileW)(NativeUInt hTable, PAceChar pucFldName, System::WideChar * pwcFileName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsBinaryToFileW)(NativeUInt hTable, PAceChar pucFldName, System::WideChar * pwcFileName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsFileToBinaryW)(NativeUInt hTable, PAceChar pucFldName, System::Word usBinaryType, System::WideChar * pwcFileName);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsFileToBinaryW)(NativeUInt hTable, PAceChar pucFldName, System::Word usBinaryType, System::WideChar * pwcFileName);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsConvertStringToJulian)(PAceChar pucJulian, System::Word usLen, System::PDouble pdJulian);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsConvertStringToJulian)(PAceChar pucJulian, System::Word usLen, System::PDouble pdJulian);
#endif /* _WIN64 */

#ifndef _WIN64
typedef unsigned __stdcall (*TAdsSetTimeStampRaw)(NativeUInt hObj, PAceChar pucFldName, PAceChar pucBuf, unsigned ulLen);
#else /* _WIN64 */
typedef unsigned __fastcall (*TAdsSetTimeStampRaw)(NativeUInt hObj, PAceChar pucFldName, PAceChar pucBuf, unsigned ulLen);
#endif /* _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString C_ADSDll;
static const System::Int8 ADS_DEFAULT_SQL_TIMEOUT = System::Int8(0x0);
static const System::Int8 ADS_FALSE = System::Int8(0x0);
static const System::Int8 ADS_TRUE = System::Int8(0x1);
static const System::Int8 ADS_DEFAULT = System::Int8(0x0);
static const System::Int8 ADS_ANSI = System::Int8(0x1);
static const System::Int8 ADS_OEM = System::Int8(0x2);
static const System::Int8 CZECH_VFP_CI_AS_1250 = System::Int8(0x3);
static const System::Int8 GENERAL_VFP_CI_AS_1250 = System::Int8(0x4);
static const System::Int8 HUNGARY_VFP_CI_AS_1250 = System::Int8(0x5);
static const System::Int8 MACHINE_VFP_BIN_1250 = System::Int8(0x6);
static const System::Int8 POLISH_VFP_CI_AS_1250 = System::Int8(0x7);
static const System::Int8 SLOVAK_VFP_CI_AS_1250 = System::Int8(0x8);
static const System::Int8 MACHINE_VFP_BIN_1251 = System::Int8(0x9);
static const System::Int8 RUSSIAN_VFP_CI_AS_1251 = System::Int8(0xa);
static const System::Int8 DUTCH_VFP_CI_AS_1252 = System::Int8(0xb);
static const System::Int8 GENERAL_VFP_CI_AS_1252 = System::Int8(0xc);
static const System::Int8 GERMAN_VFP_CI_AS_1252 = System::Int8(0xd);
static const System::Int8 ICELAND_VFP_CI_AS_1252 = System::Int8(0xe);
static const System::Int8 MACHINE_VFP_BIN_1252 = System::Int8(0xf);
static const System::Int8 NORDAN_VFP_CI_AS_1252 = System::Int8(0x10);
static const System::Int8 SPANISH_VFP_CI_AS_1252 = System::Int8(0x11);
static const System::Int8 SWEFIN_VFP_CI_AS_1252 = System::Int8(0x12);
static const System::Int8 UNIQWT_VFP_CS_AS_1252 = System::Int8(0x13);
static const System::Int8 GREEK_VFP_CI_AS_1253 = System::Int8(0x14);
static const System::Int8 MACHINE_VFP_BIN_1253 = System::Int8(0x15);
static const System::Int8 GENERAL_VFP_CI_AS_1254 = System::Int8(0x16);
static const System::Int8 MACHINE_VFP_BIN_1254 = System::Int8(0x17);
static const System::Int8 TURKISH_VFP_CI_AS_1254 = System::Int8(0x18);
static const System::Int8 DUTCH_VFP_CI_AS_437 = System::Int8(0x19);
static const System::Int8 GENERAL_VFP_CI_AS_437 = System::Int8(0x1a);
static const System::Int8 GERMAN_VFP_CI_AS_437 = System::Int8(0x1b);
static const System::Int8 ICELAND_VFP_CI_AS_437 = System::Int8(0x1c);
static const System::Int8 MACHINE_VFP_BIN_437 = System::Int8(0x1d);
static const System::Int8 NORDAN_VFP_CI_AS_437 = System::Int8(0x1e);
static const System::Int8 SPANISH_VFP_CI_AS_437 = System::Int8(0x1f);
static const System::Int8 SWEFIN_VFP_CI_AS_437 = System::Int8(0x20);
static const System::Int8 UNIQWT_VFP_CS_AS_437 = System::Int8(0x21);
static const System::Int8 GENERAL_VFP_CI_AS_620 = System::Int8(0x22);
static const System::Int8 MACHINE_VFP_BIN_620 = System::Int8(0x23);
static const System::Int8 POLISH_VFP_CI_AS_620 = System::Int8(0x24);
static const System::Int8 GREEK_VFP_CI_AS_737 = System::Int8(0x25);
static const System::Int8 MACHINE_VFP_BIN_737 = System::Int8(0x26);
static const System::Int8 DUTCH_VFP_CI_AS_850 = System::Int8(0x27);
static const System::Int8 GENERAL_VFP_CI_AS_850 = System::Int8(0x28);
static const System::Int8 ICELAND_VFP_CI_AS_850 = System::Int8(0x29);
static const System::Int8 MACHINE_VFP_BIN_850 = System::Int8(0x2a);
static const System::Int8 NORDAN_VFP_CI_AS_850 = System::Int8(0x2b);
static const System::Int8 SPANISH_VFP_CI_AS_850 = System::Int8(0x2c);
static const System::Int8 SWEFIN_VFP_CI_AS_850 = System::Int8(0x2d);
static const System::Int8 UNIQWT_VFP_CS_AS_850 = System::Int8(0x2e);
static const System::Int8 CZECH_VFP_CI_AS_852 = System::Int8(0x2f);
static const System::Int8 GENERAL_VFP_CI_AS_852 = System::Int8(0x30);
static const System::Int8 HUNGARY_VFP_CI_AS_852 = System::Int8(0x31);
static const System::Int8 MACHINE_VFP_BIN_852 = System::Int8(0x32);
static const System::Int8 POLISH_VFP_CI_AS_852 = System::Int8(0x33);
static const System::Int8 SLOVAK_VFP_CI_AS_852 = System::Int8(0x34);
static const System::Int8 GENERAL_VFP_CI_AS_857 = System::Int8(0x35);
static const System::Int8 MACHINE_VFP_BIN_857 = System::Int8(0x36);
static const System::Int8 TURKISH_VFP_CI_AS_857 = System::Int8(0x37);
static const System::Int8 GENERAL_VFP_CI_AS_861 = System::Int8(0x38);
static const System::Int8 ICELAND_VFP_CI_AS_861 = System::Int8(0x39);
static const System::Int8 MACHINE_VFP_BIN_861 = System::Int8(0x3a);
static const System::Int8 GENERAL_VFP_CI_AS_865 = System::Int8(0x3b);
static const System::Int8 MACHINE_VFP_BIN_865 = System::Int8(0x3c);
static const System::Int8 NORDAN_VFP_CI_AS_865 = System::Int8(0x3d);
static const System::Int8 SWEFIN_VFP_CI_AS_865 = System::Int8(0x3e);
static const System::Int8 MACHINE_VFP_BIN_866 = System::Int8(0x3f);
static const System::Int8 RUSSIAN_VFP_CI_AS_866 = System::Int8(0x40);
static const System::Int8 CZECH_VFP_CI_AS_895 = System::Int8(0x41);
static const System::Int8 GENERAL_VFP_CI_AS_895 = System::Int8(0x42);
static const System::Int8 MACHINE_VFP_BIN_895 = System::Int8(0x43);
static const System::Int8 SLOVAK_VFP_CI_AS_895 = System::Int8(0x44);
static const System::Int8 DANISH_ADS_CS_AS_1252 = System::Int8(0x45);
static const System::Int8 DUTCH_ADS_CS_AS_1252 = System::Int8(0x46);
static const System::Int8 ENGL_AMER_ADS_CS_AS_1252 = System::Int8(0x47);
static const System::Int8 ENGL_CAN_ADS_CS_AS_1252 = System::Int8(0x48);
static const System::Int8 ENGL_UK_ADS_CS_AS_1252 = System::Int8(0x49);
static const System::Int8 FINNISH_ADS_CS_AS_1252 = System::Int8(0x4a);
static const System::Int8 FRENCH_ADS_CS_AS_1252 = System::Int8(0x4b);
static const System::Int8 FRENCH_CAN_ADS_CS_AS_1252 = System::Int8(0x4c);
static const System::Int8 GERMAN_ADS_CS_AS_1252 = System::Int8(0x4d);
static const System::Int8 ICELANDIC_ADS_CS_AS_1252 = System::Int8(0x4e);
static const System::Int8 ITALIAN_ADS_CS_AS_1252 = System::Int8(0x4f);
static const System::Int8 NORWEGIAN_ADS_CS_AS_1252 = System::Int8(0x50);
static const System::Int8 PORTUGUESE_ADS_CS_AS_1252 = System::Int8(0x51);
static const System::Int8 SPANISH_ADS_CS_AS_1252 = System::Int8(0x52);
static const System::Int8 SPAN_MOD_ADS_CS_AS_1252 = System::Int8(0x53);
static const System::Int8 SWEDISH_ADS_CS_AS_1252 = System::Int8(0x54);
static const System::Int8 RUSSIAN_ADS_CS_AS_1251 = System::Int8(0x55);
static const System::Int8 ASCII_ADS_CS_AS_1252 = System::Int8(0x56);
static const System::Int8 TURKISH_ADS_CS_AS_1254 = System::Int8(0x57);
static const System::Int8 POLISH_ADS_CS_AS_1250 = System::Int8(0x58);
static const System::Int8 BALTIC_ADS_CS_AS_1257 = System::Int8(0x59);
static const System::Int8 UKRAINIAN_ADS_CS_AS_1251 = System::Int8(0x5a);
static const System::Int8 DUDEN_DE_ADS_CS_AS_1252 = System::Int8(0x5b);
static const System::Int8 USA_ADS_CS_AS_437 = System::Int8(0x5c);
static const System::Int8 DANISH_ADS_CS_AS_865 = System::Int8(0x5d);
static const System::Int8 DUTCH_ADS_CS_AS_850 = System::Int8(0x5e);
static const System::Int8 FINNISH_ADS_CS_AS_865 = System::Int8(0x5f);
static const System::Int8 FRENCH_ADS_CS_AS_863 = System::Int8(0x60);
static const System::Int8 GERMAN_ADS_CS_AS_850 = System::Int8(0x61);
static const System::Int8 GREEK437_ADS_CS_AS_437 = System::Int8(0x62);
static const System::Int8 GREEK851_ADS_CS_AS_851 = System::Int8(0x63);
static const System::Int8 ICELD850_ADS_CS_AS_850 = System::Int8(0x64);
static const System::Int8 ICELD861_ADS_CS_AS_861 = System::Int8(0x65);
static const System::Int8 ITALIAN_ADS_CS_AS_850 = System::Int8(0x66);
static const System::Int8 NORWEGN_ADS_CS_AS_865 = System::Int8(0x67);
static const System::Int8 PORTUGUE_ADS_CS_AS_860 = System::Int8(0x68);
static const System::Int8 SPANISH_ADS_CS_AS_852 = System::Int8(0x69);
static const System::Int8 SWEDISH_ADS_CS_AS_865 = System::Int8(0x6a);
static const System::Int8 MAZOVIA_ADS_CS_AS_852 = System::Int8(0x6b);
static const System::Int8 PC_LATIN_ADS_CS_AS_852 = System::Int8(0x6c);
static const System::Int8 ISOLATIN_ADS_CS_AS_850 = System::Int8(0x6d);
static const System::Int8 RUSSIAN_ADS_CS_AS_866 = System::Int8(0x6e);
static const System::Int8 NTXCZ852_ADS_CS_AS_852 = System::Int8(0x6f);
static const System::Int8 NTXCZ895_ADS_CS_AS_895 = System::Int8(0x70);
static const System::Int8 NTXSL852_ADS_CS_AS_852 = System::Int8(0x71);
static const System::Int8 NTXSL895_ADS_CS_AS_895 = System::Int8(0x72);
static const System::Int8 NTXHU852_ADS_CS_AS_852 = System::Int8(0x73);
static const System::Int8 NTXPL852_ADS_CS_AS_852 = System::Int8(0x74);
static const System::Int8 TURKISH_ADS_CS_AS_857 = System::Int8(0x75);
static const System::Int8 BOSNIAN_ADS_CS_AS_775 = System::Int8(0x76);
static const System::Int8 ADS_MAX_CHAR_SETS = System::Int8(0x76);
static const System::Int8 ADS_CHECKRIGHTS = System::Int8(0x1);
static const System::Int8 ADS_IGNORERIGHTS = System::Int8(0x2);
static const System::Int8 ADS_RESPECT_RIGHTS_CHECKING = System::Int8(0x1);
static const System::Int8 ADS_IGNORE_RIGHTS_CHECKING = System::Int8(0x2);
static const System::Int8 ADS_INC_USERCOUNT = System::Int8(0x1);
static const System::Int8 ADS_STORED_PROC_CONN = System::Int8(0x2);
static const System::Int8 ADS_COMPRESS_ALWAYS = System::Int8(0x4);
static const System::Int8 ADS_COMPRESS_NEVER = System::Int8(0x8);
static const System::Int8 ADS_COMPRESS_INTERNET = System::Int8(0xc);
static const System::Int8 ADS_REPLICATION_CONNECTION = System::Int8(0x10);
static const System::Int8 ADS_UDP_IP_CONNECTION = System::Int8(0x20);
static const System::Int8 ADS_IPX_CONNECTION = System::Int8(0x40);
static const System::Byte ADS_TCP_IP_CONNECTION = System::Byte(0x80);
static const System::Word ADS_TCP_IP_V6_CONNECTION = System::Word(0x100);
static const System::Word ADS_NOTIFICATION_CONNECTION = System::Word(0x200);
static const System::Word ADS_TLS_CONNECTION = System::Word(0x1000);
static const System::Word ADS_CHECK_FREE_TABLE_ACCESS = System::Word(0x2000);
static const System::Int8 ADS_EXCLUSIVE = System::Int8(0x1);
static const System::Int8 ADS_READONLY = System::Int8(0x2);
static const System::Int8 ADS_SHARED = System::Int8(0x4);
static const System::Int8 ADS_CLIPPER_MEMOS = System::Int8(0x8);
static const System::Int8 ADS_TABLE_PERM_READ = System::Int8(0x10);
static const System::Int8 ADS_TABLE_PERM_UPDATE = System::Int8(0x20);
static const System::Int8 ADS_TABLE_PERM_INSERT = System::Int8(0x40);
static const System::Byte ADS_TABLE_PERM_DELETE = System::Byte(0x80);
static const System::Word ADS_REINDEX_ON_COLLATION_MISMATCH = System::Word(0x100);
static const System::Word ADS_IGNORE_COLLATION_MISMATCH = System::Word(0x200);
static const System::Word ADS_FREE_TABLE = System::Word(0x1000);
static const System::Word ADS_TEMP_TABLE = System::Word(0x2000);
static const System::Word ADS_DICTIONARY_BOUND_TABLE = System::Word(0x4000);
static const int ADS_CACHE_READS = int(0x20000000);
static const int ADS_CACHE_WRITES = int(0x40000000);
static const System::Int8 ADS_ASCENDING = System::Int8(0x0);
static const System::Int8 ADS_UNIQUE = System::Int8(0x1);
static const System::Int8 ADS_COMPOUND = System::Int8(0x2);
static const System::Int8 ADS_CUSTOM = System::Int8(0x4);
static const System::Int8 ADS_DESCENDING = System::Int8(0x8);
static const System::Int8 ADS_USER_DEFINED = System::Int8(0x10);
static const System::Int8 ADS_FTS_INDEX = System::Int8(0x20);
static const System::Int8 ADS_FTS_FIXED = System::Int8(0x40);
static const System::Byte ADS_FTS_CASE_SENSITIVE = System::Byte(0x80);
static const System::Word ADS_FTS_KEEP_SCORE = System::Word(0x100);
static const System::Word ADS_FTS_PROTECT_NUMBERS = System::Word(0x200);
static const System::Word ADS_NOT_AUTO_OPEN = System::Word(0x400);
static const System::Word ADS_CANDIDATE = System::Word(0x800);
static const System::Word ADS_BINARY_INDEX = System::Word(0x1000);
static const System::Word ADS_FTS_ENCODE_UTF8 = System::Word(0x2000);
static const System::Word ADS_FTS_ENCODE_UTF16 = System::Word(0x4000);
static const int ADS_ONLINE = int(0x200000);
static const int ADS_UCHAR_KEY_SHORT = int(0x20000000);
static const int ADS_UCHAR_KEY_LONG = int(0x40000000);
static const int ADS_UCHAR_KEY_XLONG = int(0x60000000);
static const System::Word ADS_ALLOW_MULTIPLE_COLLATION = System::Word(0x4000);
static const System::Int8 ADS_NONE = System::Int8(0x0);
static const System::Int8 ADS_LTRIM = System::Int8(0x1);
static const System::Int8 ADS_RTRIM = System::Int8(0x2);
static const System::Int8 ADS_TRIM = System::Int8(0x3);
static const System::Int8 ADS_GET_UTF8 = System::Int8(0x4);
static const System::Int8 ADS_DONT_CHECK_CONV_ERR = System::Int8(0x8);
static const System::Int8 ADS_GET_FORMAT_ANSI = System::Int8(0x10);
static const System::Int8 ADS_GET_FORMAT_WEB = System::Int8(0x30);
static const System::Word ADS_GET_GUID_MIME = System::Word(0x100);
static const System::Word ADS_GET_GUID_FILE = System::Word(0x200);
static const System::Word ADS_GET_GUID_NUMBERS = System::Word(0x400);
static const System::Word ADS_GET_GUID_REGISTRY = System::Word(0x800);
static const System::Int8 ADS_COMPATIBLE_LOCKING = System::Int8(0x0);
static const System::Int8 ADS_PROPRIETARY_LOCKING = System::Int8(0x1);
static const System::Int8 ADS_SOFTSEEK = System::Int8(0x1);
static const System::Int8 ADS_HARDSEEK = System::Int8(0x2);
static const System::Int8 ADS_SEEKGT = System::Int8(0x4);
static const System::Int8 ADS_RAWKEY = System::Int8(0x1);
static const System::Int8 ADS_STRINGKEY = System::Int8(0x2);
static const System::Int8 ADS_DOUBLEKEY = System::Int8(0x4);
static const System::Int8 ADS_WSTRINGKEY = System::Int8(0x8);
static const System::Int8 ADS_GET_DEFAULT_KEY_LENGTH = System::Int8(0x0);
static const System::Int8 ADS_GET_PARTIAL_FULL_KEY_LENGTH = System::Int8(0x1);
static const System::Int8 ADS_GET_FULL_KEY_LENGTH = System::Int8(0x2);
static const System::Int8 ADS_GET_PRIMARY_WEIGHT_LENGTH = System::Int8(0x4);
static const System::Int8 ADS_TOP = System::Int8(0x1);
static const System::Int8 ADS_BOTTOM = System::Int8(0x2);
static const System::Int8 ADS_RESPECTFILTERS = System::Int8(0x1);
static const System::Int8 ADS_IGNOREFILTERS = System::Int8(0x2);
static const System::Int8 ADS_RESPECTSCOPES = System::Int8(0x3);
static const System::Int8 ADS_REFRESHCOUNT = System::Int8(0x4);
static const System::Int8 ADS_LOCAL_SERVER = System::Int8(0x1);
static const System::Int8 ADS_REMOTE_SERVER = System::Int8(0x2);
static const System::Int8 ADS_AIS_SERVER = System::Int8(0x4);
static const System::Int8 ADS_CONNECTION = System::Int8(0x1);
static const System::Int8 ADS_TABLE = System::Int8(0x2);
static const System::Int8 ADS_INDEX_ORDER = System::Int8(0x3);
static const System::Int8 ADS_STATEMENT = System::Int8(0x4);
static const System::Int8 ADS_CURSOR = System::Int8(0x5);
static const System::Int8 ADS_DATABASE_CONNECTION = System::Int8(0x6);
static const System::Int8 ADS_FTS_INDEX_ORDER = System::Int8(0x8);
static const System::Int8 ADS_CURSOR_READONLY = System::Int8(0x1);
static const System::Int8 ADS_CURSOR_READWRITE = System::Int8(0x2);
static const System::Int8 ADS_CONSTRAIN = System::Int8(0x1);
static const System::Int8 ADS_NO_CONSTRAIN = System::Int8(0x2);
static const System::Int8 ADS_READ_ALL_COLUMNS = System::Int8(0x1);
static const System::Int8 ADS_READ_SELECT_COLUMNS = System::Int8(0x2);
static const System::Int8 ADS_NO_VALIDATE = System::Int8(0x0);
static const System::Int8 ADS_VALIDATE_NO_SAVE = System::Int8(0x1);
static const System::Int8 ADS_VALIDATE_WRITE_FAIL = System::Int8(0x2);
static const System::Int8 ADS_VALIDATE_APPEND_FAIL = System::Int8(0x3);
static const System::Int8 ADS_VALIDATE_RETURN_ERROR = System::Int8(0x4);
static const System::Int8 ADS_CMP_LESS = System::Int8(-1);
static const System::Int8 ADS_CMP_EQUAL = System::Int8(0x0);
static const System::Int8 ADS_CMP_GREATER = System::Int8(0x1);
static const System::Int8 ADS_CONNECTIONPROP_USERNAME = System::Int8(0x0);
static const System::Int8 ADS_CONNECTIONPROP_PASSWORD = System::Int8(0x1);
static const System::Int8 ADS_CONNECTIONPROP_PROTOCOL = System::Int8(0x2);
static const System::Int8 ADS_CONNECTIONPROP_ENCRYPTION_TYPE = System::Int8(0x3);
static const System::Int8 ADS_CONNECTIONPROP_FIPS_MODE = System::Int8(0x4);
static const System::Int8 ADS_CONNECTIONPROP_CERTIFICATE_FILE = System::Int8(0x5);
static const System::Int8 ADS_CONNECTIONPROP_CIPHER_SUITE = System::Int8(0x6);
static const System::Int8 ADS_CONNECTIONPROP_COMMON_NAME = System::Int8(0x7);
static const System::Int8 ADS_CONNECTIONPROP_USING_TCP_IP = System::Int8(0x1);
static const System::Int8 ADS_CONNECTIONPROP_USING_TLC = System::Int8(0x5);
static const System::Int8 ADS_CRC_LOCALLY = System::Int8(0x1);
static const System::Int8 ADS_CRC_IGNOREMEMOPAGES = System::Int8(0x2);
static const System::Int8 ADS_EVENT_ASYNC = System::Int8(0x1);
static const System::Int8 ADS_EVENT_WITH_DATA = System::Int8(0x2);
static const System::Int8 ADS_PRESERVE_ERR = System::Int8(0x1);
static const System::Int8 ADS_CODE_PAGE = System::Int8(0x1);
static const System::Int8 AE_SUCCESS = System::Int8(0x0);
static const System::Word AE_ALLOCATION_FAILED = System::Word(0x1389);
static const System::Word AE_COMM_MISMATCH = System::Word(0x138a);
static const System::Word AE_DATA_TOO_LONG = System::Word(0x138b);
static const System::Word AE_FILE_NOT_FOUND = System::Word(0x138c);
static const System::Word AE_INSUFFICIENT_BUFFER = System::Word(0x138d);
static const System::Word AE_INVALID_BOOKMARK = System::Word(0x138e);
static const System::Word AE_INVALID_CALLBACK = System::Word(0x138f);
static const System::Word AE_INVALID_CENTURY = System::Word(0x1390);
static const System::Word AE_INVALID_DATEFORMAT = System::Word(0x1391);
static const System::Word AE_INVALID_DECIMALS = System::Word(0x1392);
static const System::Word AE_INVALID_EXPRESSION = System::Word(0x1393);
static const System::Word AE_INVALID_FIELDDEF = System::Word(0x1394);
static const System::Word AE_INVALID_FILTER_OPTION = System::Word(0x1395);
static const System::Word AE_INVALID_INDEX_HANDLE = System::Word(0x1396);
static const System::Word AE_INVALID_INDEX_NAME = System::Word(0x1397);
static const System::Word AE_INVALID_INDEX_ORDER_NAME = System::Word(0x1398);
static const System::Word AE_INVALID_INDEX_TYPE = System::Word(0x1399);
static const System::Word AE_INVALID_HANDLE = System::Word(0x139a);
static const System::Word AE_INVALID_OPTION = System::Word(0x139b);
static const System::Word AE_INVALID_PATH = System::Word(0x139c);
static const System::Word AE_INVALID_POINTER = System::Word(0x139d);
static const System::Word AE_INVALID_RECORD_NUMBER = System::Word(0x139e);
static const System::Word AE_INVALID_TABLE_HANDLE = System::Word(0x139f);
static const System::Word AE_INVALID_CONNECTION_HANDLE = System::Word(0x13a0);
static const System::Word AE_INVALID_TABLETYPE = System::Word(0x13a1);
static const System::Word AE_INVALID_WORKAREA = System::Word(0x13a2);
static const System::Word AE_INVALID_CHARSETTYPE = System::Word(0x13a3);
static const System::Word AE_INVALID_LOCKTYPE = System::Word(0x13a4);
static const System::Word AE_INVALID_RIGHTSOPTION = System::Word(0x13a5);
static const System::Word AE_INVALID_FIELDNUMBER = System::Word(0x13a6);
static const System::Word AE_INVALID_KEY_LENGTH = System::Word(0x13a7);
static const System::Word AE_INVALID_FIELDNAME = System::Word(0x13a8);
static const System::Word AE_NO_DRIVE_CONNECTION = System::Word(0x13a9);
static const System::Word AE_FILE_NOT_ON_SERVER = System::Word(0x13aa);
static const System::Word AE_LOCK_FAILED = System::Word(0x13ab);
static const System::Word AE_NO_CONNECTION = System::Word(0x13ac);
static const System::Word AE_NO_FILTER = System::Word(0x13ad);
static const System::Word AE_NO_SCOPE = System::Word(0x13ae);
static const System::Word AE_NO_TABLE = System::Word(0x13af);
static const System::Word AE_NO_WORKAREA = System::Word(0x13b0);
static const System::Word AE_NOT_FOUND = System::Word(0x13b1);
static const System::Word AE_NOT_IMPLEMENTED = System::Word(0x13b2);
static const System::Word AE_MAX_THREADS_EXCEEDED = System::Word(0x13b3);
static const System::Word AE_START_THREAD_FAIL = System::Word(0x13b4);
static const System::Word AE_TOO_MANY_INDEXES = System::Word(0x13b5);
static const System::Word AE_TOO_MANY_TAGS = System::Word(0x13b6);
static const System::Word AE_TRANS_OUT_OF_SEQUENCE = System::Word(0x13b7);
static const System::Word AE_UNKNOWN_ERRCODE = System::Word(0x13b8);
static const System::Word AE_UNSUPPORTED_COLLATION = System::Word(0x13b9);
static const System::Word AE_NAME_TOO_LONG = System::Word(0x13ba);
static const System::Word AE_DUPLICATE_ALIAS = System::Word(0x13bb);
static const System::Word AE_TABLE_CLOSED_IN_TRANSACTION = System::Word(0x13bd);
static const System::Word AE_PERMISSION_DENIED = System::Word(0x13be);
static const System::Word AE_STRING_NOT_FOUND = System::Word(0x13bf);
static const System::Word AE_UNKNOWN_CHAR_SET = System::Word(0x13c0);
static const System::Word AE_INVALID_OEM_CHAR_FILE = System::Word(0x13c1);
static const System::Word AE_INVALID_MEMO_BLOCK_SIZE = System::Word(0x13c2);
static const System::Word AE_NO_FILE_FOUND = System::Word(0x13c3);
static const System::Word AE_NO_INF_LOCK = System::Word(0x13c4);
static const System::Word AE_INF_FILE_ERROR = System::Word(0x13c5);
static const System::Word AE_RECORD_NOT_LOCKED = System::Word(0x13c6);
static const System::Word AE_ILLEGAL_COMMAND_DURING_TRANS = System::Word(0x13c7);
static const System::Word AE_TABLE_NOT_SHARED = System::Word(0x13c8);
static const System::Word AE_INDEX_ALREADY_OPEN = System::Word(0x13c9);
static const System::Word AE_INVALID_FIELD_TYPE = System::Word(0x13ca);
static const System::Word AE_TABLE_NOT_EXCLUSIVE = System::Word(0x13cb);
static const System::Word AE_NO_CURRENT_RECORD = System::Word(0x13cc);
static const System::Word AE_PRECISION_LOST = System::Word(0x13cd);
static const System::Word AE_INVALID_DATA_TYPE = System::Word(0x13ce);
static const System::Word AE_DATA_TRUNCATED = System::Word(0x13cf);
static const System::Word AE_TABLE_READONLY = System::Word(0x13d0);
static const System::Word AE_INVALID_RECORD_LENGTH = System::Word(0x13d1);
static const System::Word AE_NO_ERROR_MESSAGE = System::Word(0x13d2);
static const System::Word AE_INDEX_SHARED = System::Word(0x13d3);
static const System::Word AE_INDEX_EXISTS = System::Word(0x13d4);
static const System::Word AE_CYCLIC_RELATION = System::Word(0x13d5);
static const System::Word AE_INVALID_RELATION = System::Word(0x13d6);
static const System::Word AE_INVALID_DAY = System::Word(0x13d7);
static const System::Word AE_INVALID_MONTH = System::Word(0x13d8);
static const System::Word AE_CORRUPT_TABLE = System::Word(0x13d9);
static const System::Word AE_INVALID_BINARY_OFFSET = System::Word(0x13da);
static const System::Word AE_BINARY_FILE_ERROR = System::Word(0x13db);
static const System::Word AE_INVALID_DELETED_BYTE_VALUE = System::Word(0x13dc);
static const System::Word AE_NO_PENDING_UPDATE = System::Word(0x13dd);
static const System::Word AE_PENDING_UPDATE = System::Word(0x13de);
static const System::Word AE_TABLE_NOT_LOCKED = System::Word(0x13df);
static const System::Word AE_CORRUPT_INDEX = System::Word(0x13e0);
static const System::Word AE_AUTOOPEN_INDEX = System::Word(0x13e1);
static const System::Word AE_SAME_TABLE = System::Word(0x13e2);
static const System::Word AE_INVALID_IMAGE = System::Word(0x13e3);
static const System::Word AE_COLLATION_SEQUENCE_MISMATCH = System::Word(0x13e4);
static const System::Word AE_INVALID_INDEX_ORDER = System::Word(0x13e5);
static const System::Word AE_TABLE_CACHED = System::Word(0x13e6);
static const System::Word AE_INVALID_DATE = System::Word(0x13e7);
static const System::Word AE_ENCRYPTION_NOT_ENABLED = System::Word(0x13e8);
static const System::Word AE_INVALID_PASSWORD = System::Word(0x13e9);
static const System::Word AE_TABLE_ENCRYPTED = System::Word(0x13ea);
static const System::Word AE_SERVER_MISMATCH = System::Word(0x13eb);
static const System::Word AE_INVALID_USERNAME = System::Word(0x13ec);
static const System::Word AE_INVALID_VALUE = System::Word(0x13ed);
static const System::Word AE_INVALID_CONTINUE = System::Word(0x13ee);
static const System::Word AE_UNRECOGNIZED_VERSION = System::Word(0x13ef);
static const System::Word AE_RECORD_ENCRYPTED = System::Word(0x13f0);
static const System::Word AE_UNRECOGNIZED_ENCRYPTION = System::Word(0x13f1);
static const System::Word AE_INVALID_SQLSTATEMENT_HANDLE = System::Word(0x13f2);
static const System::Word AE_INVALID_SQLCURSOR_HANDLE = System::Word(0x13f3);
static const System::Word AE_NOT_PREPARED = System::Word(0x13f4);
static const System::Word AE_CURSOR_NOT_CLOSED = System::Word(0x13f5);
static const System::Word AE_INVALID_SQL_PARAM_NUMBER = System::Word(0x13f6);
static const System::Word AE_INVALID_SQL_PARAM_NAME = System::Word(0x13f7);
static const System::Word AE_INVALID_COLUMN_NUMBER = System::Word(0x13f8);
static const System::Word AE_INVALID_COLUMN_NAME = System::Word(0x13f9);
static const System::Word AE_INVALID_READONLY_OPTION = System::Word(0x13fa);
static const System::Word AE_IS_CURSOR_HANDLE = System::Word(0x13fb);
static const System::Word AE_INDEX_EXPR_NOT_FOUND = System::Word(0x13fc);
static const System::Word AE_NOT_DML = System::Word(0x13fd);
static const System::Word AE_INVALID_CONSTRAIN_TYPE = System::Word(0x13fe);
static const System::Word AE_INVALID_CURSORHANDLE = System::Word(0x13ff);
static const System::Word AE_OBSOLETE_FUNCTION = System::Word(0x1400);
static const System::Word AE_TADSDATASET_GENERAL = System::Word(0x1401);
static const System::Word AE_UDF_OVERWROTE_BUFFER = System::Word(0x1402);
static const System::Word AE_INDEX_UDF_NOT_SET = System::Word(0x1403);
static const System::Word AE_CONCURRENT_PROBLEM = System::Word(0x1404);
static const System::Word AE_INVALID_DICTIONARY_HANDLE = System::Word(0x1405);
static const System::Word AE_INVALID_PROPERTY_ID = System::Word(0x1406);
static const System::Word AE_INVALID_PROPERTY = System::Word(0x1407);
static const System::Word AE_DICTIONARY_ALREADY_EXISTS = System::Word(0x1408);
static const System::Word AE_INVALID_FIND_HANDLE = System::Word(0x1409);
static const System::Word AE_DD_REQUEST_NOT_COMPLETED = System::Word(0x140a);
static const System::Word AE_INVALID_OBJECT_ID = System::Word(0x140b);
static const System::Word AE_INVALID_OBJECT_NAME = System::Word(0x140c);
static const System::Word AE_INVALID_PROPERTY_LENGTH = System::Word(0x140d);
static const System::Word AE_INVALID_KEY_OPTIONS = System::Word(0x140e);
static const System::Word AE_CONSTRAINT_VALIDATION_ERROR = System::Word(0x140f);
static const System::Word AE_INVALID_OBJECT_TYPE = System::Word(0x1410);
static const System::Word AE_NO_OBJECT_FOUND = System::Word(0x1411);
static const System::Word AE_PROPERTY_NOT_SET = System::Word(0x1412);
static const System::Word AE_NO_PRIMARY_KEY_EXISTS = System::Word(0x1413);
static const System::Word AE_LOCAL_CONN_DISABLED = System::Word(0x1414);
static const System::Word AE_RI_RESTRICT = System::Word(0x1415);
static const System::Word AE_RI_CASCADE = System::Word(0x1416);
static const System::Word AE_RI_FAILED = System::Word(0x1417);
static const System::Word AE_RI_CORRUPTED = System::Word(0x1418);
static const System::Word AE_RI_UNDO_FAILED = System::Word(0x1419);
static const System::Word AE_RI_RULE_EXISTS = System::Word(0x141a);
static const System::Word AE_COLUMN_CANNOT_BE_NULL = System::Word(0x141b);
static const System::Word AE_MIN_CONSTRAINT_VIOLATION = System::Word(0x141c);
static const System::Word AE_MAX_CONSTRAINT_VIOLATION = System::Word(0x141d);
static const System::Word AE_RECORD_CONSTRAINT_VIOLATION = System::Word(0x141e);
static const System::Word AE_CANNOT_DELETE_TEMP_INDEX = System::Word(0x141f);
static const System::Word AE_RESTRUCTURE_FAILED = System::Word(0x1420);
static const System::Word AE_INVALID_STATEMENT = System::Word(0x1421);
static const System::Word AE_STORED_PROCEDURE_FAILED = System::Word(0x1422);
static const System::Word AE_INVALID_DICTIONARY_FILE = System::Word(0x1423);
static const System::Word AE_NOT_MEMBER_OF_GROUP = System::Word(0x1424);
static const System::Word AE_ALREADY_MEMBER_OF_GROUP = System::Word(0x1425);
static const System::Word AE_INVALID_OBJECT_RIGHT = System::Word(0x1426);
static const System::Word AE_INVALID_OBJECT_PERMISSION = System::Word(0x1426);
static const System::Word AE_CANNOT_OPEN_DATABASE_TABLE = System::Word(0x1427);
static const System::Word AE_INVALID_CONSTRAINT = System::Word(0x1428);
static const System::Word AE_NOT_ADMINISTRATOR = System::Word(0x1429);
static const System::Word AE_NO_TABLE_ENCRYPTION_PASSWORD = System::Word(0x142a);
static const System::Word AE_TABLE_NOT_ENCRYPTED = System::Word(0x142b);
static const System::Word AE_INVALID_ENCRYPTION_VERSION = System::Word(0x142c);
static const System::Word AE_NO_STORED_PROC_EXEC_RIGHTS = System::Word(0x142d);
static const System::Word AE_DD_UNSUPPORTED_DEPLOYMENT = System::Word(0x142e);
static const System::Word AE_INFO_AUTO_CREATION_OCCURRED = System::Word(0x1430);
static const System::Word AE_INFO_COPY_MADE_BY_CLIENT = System::Word(0x1431);
static const System::Word AE_DATABASE_REQUIRES_NEW_SERVER = System::Word(0x1432);
static const System::Word AE_COLUMN_PERMISSION_DENIED = System::Word(0x1433);
static const System::Word AE_DATABASE_REQUIRES_NEW_CLIENT = System::Word(0x1434);
static const System::Word AE_INVALID_LINK_NUMBER = System::Word(0x1435);
static const System::Word AE_LINK_ACTIVATION_FAILED = System::Word(0x1436);
static const System::Word AE_INDEX_COLLATION_MISMATCH = System::Word(0x1437);
static const System::Word AE_ILLEGAL_USER_OPERATION = System::Word(0x1438);
static const System::Word AE_TRIGGER_FAILED = System::Word(0x1439);
static const System::Word AE_NO_ASA_FUNCTION_FOUND = System::Word(0x143a);
static const System::Word AE_VALUE_OVERFLOW = System::Word(0x143b);
static const System::Word AE_UNRECOGNIZED_FTS_VERSION = System::Word(0x143c);
static const System::Word AE_TRIG_CREATION_FAILED = System::Word(0x143d);
static const System::Word AE_MEMTABLE_SIZE_EXCEEDED = System::Word(0x143e);
static const System::Word AE_OUTDATED_CLIENT_VERSION = System::Word(0x143f);
static const System::Word AE_FREE_TABLE = System::Word(0x1440);
static const System::Word AE_LOCAL_CONN_RESTRICTED = System::Word(0x1441);
static const System::Word AE_OLD_RECORD = System::Word(0x1442);
static const System::Word AE_QUERY_NOT_ACTIVE = System::Word(0x1443);
static const System::Word AE_KEY_EXCEEDS_PAGE_SIZE = System::Word(0x1444);
static const System::Word AE_TABLE_FOUND = System::Word(0x1445);
static const System::Word AE_TABLE_NOT_FOUND = System::Word(0x1446);
static const System::Word AE_LOCK_OBJECT = System::Word(0x1447);
static const System::Word AE_INVALID_REPLICATION_IDENT = System::Word(0x1448);
static const System::Word AE_ILLEGAL_COMMAND_DURING_BACKUP = System::Word(0x1449);
static const System::Word AE_NO_MEMO_FILE = System::Word(0x144a);
static const System::Word AE_SUBSCRIPTION_QUEUE_NOT_EMPTY = System::Word(0x144b);
static const System::Word AE_UNABLE_TO_DISABLE_TRIGGERS = System::Word(0x144c);
static const System::Word AE_UNABLE_TO_ENABLE_TRIGGERS = System::Word(0x144d);
static const System::Word AE_BACKUP = System::Word(0x144e);
static const System::Word AE_FREETABLEFAILED = System::Word(0x144f);
static const System::Word AE_BLURRY_SNAPSHOT = System::Word(0x1450);
static const System::Word AE_INVALID_VERTICAL_FILTER = System::Word(0x1451);
static const System::Word AE_INVALID_USE_OF_HANDLE_IN_AEP = System::Word(0x1452);
static const System::Word AE_COLLATION_NOT_RECOGNIZED = System::Word(0x1453);
static const System::Word AE_INVALID_COLLATION = System::Word(0x1454);
static const System::Word AE_NOT_VFP_NULLABLE_FIELD = System::Word(0x1455);
static const System::Word AE_NOT_VFP_VARIABLE_FIELD = System::Word(0x1456);
static const System::Word AE_ILLEGAL_EVENT_COMMAND = System::Word(0x1457);
static const System::Word AE_KEY_CANNOT_BE_NULL = System::Word(0x1458);
static const System::Word AE_COLLATIONS_DO_NOT_MATCH = System::Word(0x1459);
static const System::Word AE_INVALID_APPID = System::Word(0x145a);
static const System::Word AE_UNICODE_CONVERSION = System::Word(0x145b);
static const System::Word AE_UNICODE_COLLATION = System::Word(0x145c);
static const System::Word AE_SERVER_ENUMERATION_ERROR = System::Word(0x145d);
static const System::Word AE_UNABLE_TO_LOAD_SSL = System::Word(0x145e);
static const System::Word AE_UNABLE_TO_VERIFY_SIGNATURE = System::Word(0x145f);
static const System::Word AE_UNABLE_TO_LOAD_SSL_ENTRYPOINT = System::Word(0x1460);
static const System::Word AE_CRYPTO_ERROR = System::Word(0x1461);
static const System::Word AE_UNRECOGNIZED_CIPHER = System::Word(0x1462);
static const System::Word AE_FIPS_MODE_ENCRYPTION = System::Word(0x1463);
static const System::Word AE_FIPS_REQUIRED = System::Word(0x1464);
static const System::Word AE_FIPS_NOT_ALLOWED = System::Word(0x1465);
static const System::Word AE_FIPS_MODE_FAILED = System::Word(0x1466);
static const System::Word AE_PASSWORD_REQUIRED = System::Word(0x1467);
static const System::Word AE_CONNECTION_TIMED_OUT = System::Word(0x1468);
static const System::Word AE_DELTA_SUPPORT_NOT_POSSIBLE = System::Word(0x1469);
static const System::Word AE_QUERY_LOGGING_ERROR = System::Word(0x146a);
static const System::Word AE_COMPRESSION_FAILED = System::Word(0x146b);
static const System::Word AE_INVALID_DATA = System::Word(0x146c);
static const System::Word AE_ROWVERSION_REQUIRED = System::Word(0x146d);
static const System::Int8 ADS_DATABASE_TABLE = System::Int8(0x0);
static const System::Int8 ADS_NTX = System::Int8(0x1);
static const System::Int8 ADS_CDX = System::Int8(0x2);
static const System::Int8 ADS_ADT = System::Int8(0x3);
static const System::Int8 ADS_VFP = System::Int8(0x4);
static const System::Int8 ADS_BASENAME = System::Int8(0x1);
static const System::Int8 ADS_BASENAMEANDEXT = System::Int8(0x2);
static const System::Int8 ADS_FULLPATHNAME = System::Int8(0x3);
static const System::Int8 ADS_DATADICTIONARY_NAME = System::Int8(0x4);
static const System::Int8 ADS_TABLE_OPEN_NAME = System::Int8(0x5);
static const System::Int8 ADS_OPTIMIZED_FULL = System::Int8(0x1);
static const System::Int8 ADS_OPTIMIZED_PART = System::Int8(0x2);
static const System::Int8 ADS_OPTIMIZED_NONE = System::Int8(0x3);
static const System::Int8 ADS_DYNAMIC_AOF = System::Int8(0x0);
static const System::Int8 ADS_RESOLVE_IMMEDIATE = System::Int8(0x1);
static const System::Int8 ADS_RESOLVE_DYNAMIC = System::Int8(0x2);
static const System::Int8 ADS_KEYSET_AOF = System::Int8(0x4);
static const System::Int8 ADS_FIXED_AOF = System::Int8(0x8);
static const System::Int8 ADS_KEEP_AOF_PLAN = System::Int8(0x10);
static const System::Word ADS_ENCODE_UTF16 = System::Word(0x2000);
static const System::Word ADS_ENCODE_UTF8 = System::Word(0x4000);
static const System::Int8 ADS_AOF_ADD_RECORD = System::Int8(0x1);
static const System::Int8 ADS_AOF_REMOVE_RECORD = System::Int8(0x2);
static const System::Int8 ADS_AOF_TOGGLE_RECORD = System::Int8(0x3);
static const System::Int8 ADS_STORED_PROC = System::Int8(0x1);
static const System::Int8 ADS_COMSTORED_PROC = System::Int8(0x2);
static const System::Int8 ADS_SCRIPT_PROC = System::Int8(0x4);
static const System::Word ADS_PROC_VARYING_OUTPUT = System::Word(0x1000);
static const System::Int8 ADS_ENCRYPTION_RC4 = System::Int8(0x3);
static const System::Int8 ADS_ENCRYPTION_AES128 = System::Int8(0x5);
static const System::Int8 ADS_ENCRYPTION_AES256 = System::Int8(0x6);
static const System::Int8 ADS_MAX_DATEMASK = System::Int8(0xc);
static const System::Word ADS_MAX_ERROR_LEN = System::Word(0x258);
static const System::Word ADS_MAX_INDEX_EXPR_LEN = System::Word(0x1fe);
static const System::Word ADS_MAX_KEY_LENGTH = System::Word(0xff2);
static const System::Byte ADS_MAX_FIELD_NAME = System::Byte(0x80);
static const System::Int8 ADS_MAX_DBF_FIELD_NAME = System::Int8(0xa);
static const System::Int8 ADS_MAX_INDEXES = System::Int8(0xf);
static const System::Word ADS_MAX_PATH = System::Word(0x104);
static const System::Byte ADS_MAX_TABLE_NAME = System::Byte(0xff);
static const System::Byte ADS_MAX_TAG_NAME = System::Byte(0x80);
static const System::Word ADS_MAX_TAGS = System::Word(0x100);
static const System::Byte ADS_MAX_OBJECT_NAME = System::Byte(0xc8);
static const System::Word ADS_MAX_TABLE_AND_PATH = System::Word(0x203);
static const System::Word ADS_MIN_ADI_PAGESIZE = System::Word(0x200);
static const System::Word ADS_MAX_ADI_PAGESIZE = System::Word(0x2000);
static const System::Int8 ADS_TYPE_UNKNOWN = System::Int8(0x0);
static const System::Int8 ADS_LOGICAL = System::Int8(0x1);
static const System::Int8 ADS_NUMERIC = System::Int8(0x2);
static const System::Int8 ADS_DATE = System::Int8(0x3);
static const System::Int8 ADS_STRING = System::Int8(0x4);
static const System::Int8 ADS_MEMO = System::Int8(0x5);
static const System::Int8 ADS_BINARY = System::Int8(0x6);
static const System::Int8 ADS_IMAGE = System::Int8(0x7);
static const System::Int8 ADS_VARCHAR = System::Int8(0x8);
static const System::Int8 ADS_COMPACTDATE = System::Int8(0x9);
static const System::Int8 ADS_DOUBLE = System::Int8(0xa);
static const System::Int8 ADS_INTEGER = System::Int8(0xb);
static const System::Int8 ADS_SHORTINT = System::Int8(0xc);
static const System::Int8 ADS_TIME = System::Int8(0xd);
static const System::Int8 ADS_TIMESTAMP = System::Int8(0xe);
static const System::Int8 ADS_AUTOINC = System::Int8(0xf);
static const System::Int8 ADS_RAW = System::Int8(0x10);
static const System::Int8 ADS_CURDOUBLE = System::Int8(0x11);
static const System::Int8 ADS_MONEY = System::Int8(0x12);
static const System::Int8 ADS_LONGINT = System::Int8(0x13);
static const System::Int8 ADS_LONGLONG = System::Int8(0x13);
static const System::Int8 ADS_CISTRING = System::Int8(0x14);
static const System::Int8 ADS_ROWVERSION = System::Int8(0x15);
static const System::Int8 ADS_MODTIME = System::Int8(0x16);
static const System::Int8 ADS_VARCHAR_FOX = System::Int8(0x17);
static const System::Int8 ADS_VARBINARY_FOX = System::Int8(0x18);
static const System::Int8 ADS_SYSTEM_FIELD = System::Int8(0x19);
static const System::Int8 ADS_NCHAR = System::Int8(0x1a);
static const System::Int8 ADS_NVARCHAR = System::Int8(0x1b);
static const System::Int8 ADS_NMEMO = System::Int8(0x1c);
static const System::Int8 ADS_GUID = System::Int8(0x1d);
static const System::Int8 ADS_MAX_FIELD_TYPE = System::Int8(0x1e);
static const System::Int8 ADS_FOXGENERAL = System::Int8(0x33);
static const System::Int8 ADS_FOXPICTURE = System::Int8(0x34);
static const System::Int8 ADS_INDEX_UDF = System::Int8(0x1);
static const System::Word ADS_MAX_CFG_PATH = System::Word(0x100);
static const System::Int8 ADS_MGMT_NETWARE_SERVER = System::Int8(0x1);
static const System::Int8 ADS_MGMT_NETWARE4_OR_OLDER_SERVER = System::Int8(0x1);
static const System::Int8 ADS_MGMT_NT_SERVER = System::Int8(0x2);
static const System::Int8 ADS_MGMT_LOCAL_SERVER = System::Int8(0x3);
static const System::Int8 ADS_MGMT_WIN9X_SERVER = System::Int8(0x4);
static const System::Int8 ADS_MGMT_NETWARE5_OR_NEWER_SERVER = System::Int8(0x5);
static const System::Int8 ADS_MGMT_LINUX_SERVER = System::Int8(0x6);
static const System::Int8 ADS_MGMT_NT_SERVER_64_BIT = System::Int8(0x7);
static const System::Int8 ADS_MGMT_LINUX_SERVER_64_BIT = System::Int8(0x8);
static const System::Int8 ADS_MGMT_NO_LOCK = System::Int8(0x1);
static const System::Int8 ADS_MGMT_RECORD_LOCK = System::Int8(0x2);
static const System::Int8 ADS_MGMT_FILE_LOCK = System::Int8(0x3);
static const System::Int8 ADS_REG_OWNER_LEN = System::Int8(0x24);
static const System::Int8 ADS_REVISION_LEN = System::Int8(0x10);
static const System::Int8 ADS_INST_DATE_LEN = System::Int8(0x10);
static const System::Int8 ADS_OEM_CHAR_NAME_LEN = System::Int8(0x10);
static const System::Int8 ADS_ANSI_CHAR_NAME_LEN = System::Int8(0x10);
static const System::Int8 ADS_SERIAL_NUM_LEN = System::Int8(0x10);
static const System::Word ADS_MGMT_MAX_PATH = System::Word(0x104);
static const System::Int8 ADS_MGMT_PROPRIETARY_LOCKING = System::Int8(0x1);
static const System::Int8 ADS_MGMT_CDX_LOCKING = System::Int8(0x2);
static const System::Int8 ADS_MGMT_NTX_LOCKING = System::Int8(0x3);
static const System::Int8 ADS_MGMT_ADT_LOCKING = System::Int8(0x4);
static const System::Int8 ADS_MGMT_COMIX_LOCKING = System::Int8(0x5);
static const System::Int8 ADS_MAX_USER_NAME = System::Int8(0x32);
static const System::Int8 ADS_MAX_ADDRESS_SIZE = System::Int8(0x1e);
static const System::Int8 ADS_MAX_MGMT_APPID_SIZE = System::Int8(0x46);
static const System::Word ADS_LOCK_ARRAY_SIZE = System::Word(0x190);
static const System::Int8 ADS_THREAD_ARRAY_SIZE = System::Int8(0x32);
static const System::Byte ADS_TABLE_ARRAY_SIZE = System::Byte(0xc8);
static const System::Byte ADS_INDEX_ARRAY_SIZE = System::Byte(0xc8);
static const System::Byte ADS_USER_ARRAY_SIZE = System::Byte(0xc8);
static const System::Word ADS_DD_PROPERTY_NOT_AVAIL = System::Word(0xffff);
static const System::Word ADS_DD_MAX_PROPERTY_LEN = System::Word(0xfffe);
static const System::Byte ADS_DD_MAX_OBJECT_NAME_LEN = System::Byte(0xc8);
static const System::Word ADS_DD_MAX_LINK_INFO_SIZE = System::Word(0x297);
static const System::Int8 ADS_DD_UNKNOWN_OBJECT = System::Int8(0x0);
static const System::Int8 ADS_DD_TABLE_OBJECT = System::Int8(0x1);
static const System::Int8 ADS_DD_RELATION_OBJECT = System::Int8(0x2);
static const System::Int8 ADS_DD_INDEX_FILE_OBJECT = System::Int8(0x3);
static const System::Int8 ADS_DD_FIELD_OBJECT = System::Int8(0x4);
static const System::Int8 ADS_DD_COLUMN_OBJECT = System::Int8(0x4);
static const System::Int8 ADS_DD_INDEX_OBJECT = System::Int8(0x5);
static const System::Int8 ADS_DD_VIEW_OBJECT = System::Int8(0x6);
static const System::Int8 ADS_DD_VIEW_OR_TABLE_OBJECT = System::Int8(0x7);
static const System::Int8 ADS_DD_USER_OBJECT = System::Int8(0x8);
static const System::Int8 ADS_DD_USER_GROUP_OBJECT = System::Int8(0x9);
static const System::Int8 ADS_DD_PROCEDURE_OBJECT = System::Int8(0xa);
static const System::Int8 ADS_DD_DATABASE_OBJECT = System::Int8(0xb);
static const System::Int8 ADS_DD_LINK_OBJECT = System::Int8(0xc);
static const System::Int8 ADS_DD_TABLE_VIEW_OR_LINK_OBJECT = System::Int8(0xd);
static const System::Int8 ADS_DD_TRIGGER_OBJECT = System::Int8(0xe);
static const System::Int8 ADS_DD_PUBLICATION_OBJECT = System::Int8(0xf);
static const System::Int8 ADS_DD_ARTICLE_OBJECT = System::Int8(0x10);
static const System::Int8 ADS_DD_SUBSCRIPTION_OBJECT = System::Int8(0x11);
static const System::Int8 ADS_DD_FUNCTION_OBJECT = System::Int8(0x12);
static const System::Int8 ADS_DD_PACKAGE_OBJECT = System::Int8(0x13);
static const System::Int8 ADS_DD_QUALIFIED_TRIGGER_OBJ = System::Int8(0x14);
static const System::Int8 ADS_DD_PERMISSION_OBJECT = System::Int8(0x15);
static const System::Int8 ADS_DD_DATABASE_TRIGGER_OBJ = System::Int8(0x16);
static const System::Int8 ADS_DD_COMMENT = System::Int8(0x1);
static const System::Int8 ADS_DD_VERSION = System::Int8(0x2);
static const System::Int8 ADS_DD_USER_DEFINED_PROP = System::Int8(0x3);
static const System::Int8 ADS_DD_OBJECT_NAME = System::Int8(0x4);
static const System::Int8 ADS_DD_TRIGGERS_DISABLED = System::Int8(0x5);
static const System::Int8 ADS_DD_OBJECT_ID = System::Int8(0x6);
static const System::Int8 ADS_DD_OPTIONS = System::Int8(0x7);
static const System::Int8 ADS_DD_QVR_OPT_QUERY = System::Int8(0x1);
static const System::Int8 ADS_DD_QVR_OPT_PROCEDURE = System::Int8(0x2);
static const System::Int8 ADS_DD_DEFAULT_TABLE_PATH = System::Int8(0x64);
static const System::Int8 ADS_DD_ADMIN_PASSWORD = System::Int8(0x65);
static const System::Int8 ADS_DD_TEMP_TABLE_PATH = System::Int8(0x66);
static const System::Int8 ADS_DD_LOG_IN_REQUIRED = System::Int8(0x67);
static const System::Int8 ADS_DD_VERIFY_ACCESS_RIGHTS = System::Int8(0x68);
static const System::Int8 ADS_DD_ENCRYPT_TABLE_PASSWORD = System::Int8(0x69);
static const System::Int8 ADS_DD_ENCRYPT_NEW_TABLE = System::Int8(0x6a);
static const System::Int8 ADS_DD_ENABLE_INTERNET = System::Int8(0x6b);
static const System::Int8 ADS_DD_INTERNET_SECURITY_LEVEL = System::Int8(0x6c);
static const System::Int8 ADS_DD_MAX_FAILED_ATTEMPTS = System::Int8(0x6d);
static const System::Int8 ADS_DD_ALLOW_ADSSYS_NET_ACCESS = System::Int8(0x6e);
static const System::Int8 ADS_DD_VERSION_MAJOR = System::Int8(0x6f);
static const System::Int8 ADS_DD_VERSION_MINOR = System::Int8(0x70);
static const System::Int8 ADS_DD_LOGINS_DISABLED = System::Int8(0x71);
static const System::Int8 ADS_DD_LOGINS_DISABLED_ERRSTR = System::Int8(0x72);
static const System::Int8 ADS_DD_FTS_DELIMITERS = System::Int8(0x73);
static const System::Int8 ADS_DD_FTS_NOISE = System::Int8(0x74);
static const System::Int8 ADS_DD_FTS_DROP_CHARS = System::Int8(0x75);
static const System::Int8 ADS_DD_FTS_CONDITIONAL_CHARS = System::Int8(0x76);
static const System::Int8 ADS_DD_ENCRYPTED = System::Int8(0x77);
static const System::Int8 ADS_DD_ENCRYPT_INDEXES = System::Int8(0x78);
static const System::Int8 ADS_DD_QUERY_LOG_TABLE = System::Int8(0x79);
static const System::Int8 ADS_DD_ENCRYPT_COMMUNICATION = System::Int8(0x7a);
static const System::Int8 ADS_DD_DEFAULT_TABLE_RELATIVE_PATH = System::Int8(0x7b);
static const System::Int8 ADS_DD_TEMP_TABLE_RELATIVE_PATH = System::Int8(0x7c);
static const System::Int8 ADS_DD_DISABLE_DLL_CACHING = System::Int8(0x7d);
static const System::Int8 ADS_DD_DATA_ENCRYPTION_TYPE = System::Int8(0x7e);
static const System::Int8 ADS_DD_FTS_DELIMITERS_W = System::Int8(0x7f);
static const System::Byte ADS_DD_FTS_NOISE_W = System::Byte(0x80);
static const System::Byte ADS_DD_FTS_DROP_CHARS_W = System::Byte(0x81);
static const System::Byte ADS_DD_FTS_CONDITIONAL_CHARS_W = System::Byte(0x82);
static const System::Byte ADS_DD_QUERY_VIA_ROOT = System::Byte(0x83);
static const System::Byte ADS_DD_ENFORCE_MAX_FAILED_LOGINS = System::Byte(0x84);
static const System::Byte ADS_DD_DATABASE_TRIGGER_TYPES = System::Byte(0x85);
static const System::Byte ADS_DD_TABLE_VALIDATION_EXPR = System::Byte(0xc8);
static const System::Byte ADS_DD_TABLE_VALIDATION_MSG = System::Byte(0xc9);
static const System::Byte ADS_DD_TABLE_PRIMARY_KEY = System::Byte(0xca);
static const System::Byte ADS_DD_TABLE_AUTO_CREATE = System::Byte(0xcb);
static const System::Byte ADS_DD_TABLE_TYPE = System::Byte(0xcc);
static const System::Byte ADS_DD_TABLE_PATH = System::Byte(0xcd);
static const System::Byte ADS_DD_TABLE_FIELD_COUNT = System::Byte(0xce);
static const System::Byte ADS_DD_TABLE_RI_GRAPH = System::Byte(0xcf);
static const System::Byte ADS_DD_TABLE_OBJ_ID = System::Byte(0xd0);
static const System::Byte ADS_DD_TABLE_RI_XY = System::Byte(0xd1);
static const System::Byte ADS_DD_TABLE_IS_RI_PARENT = System::Byte(0xd2);
static const System::Byte ADS_DD_TABLE_RELATIVE_PATH = System::Byte(0xd3);
static const System::Byte ADS_DD_TABLE_CHAR_TYPE = System::Byte(0xd4);
static const System::Byte ADS_DD_TABLE_DEFAULT_INDEX = System::Byte(0xd5);
static const System::Byte ADS_DD_TABLE_ENCRYPTION = System::Byte(0xd6);
static const System::Byte ADS_DD_TABLE_MEMO_BLOCK_SIZE = System::Byte(0xd7);
static const System::Byte ADS_DD_TABLE_PERMISSION_LEVEL = System::Byte(0xd8);
static const System::Byte ADS_DD_TABLE_TRIGGER_TYPES = System::Byte(0xd9);
static const System::Byte ADS_DD_TABLE_TRIGGER_OPTIONS = System::Byte(0xda);
static const System::Byte ADS_DD_TABLE_CACHING = System::Byte(0xdb);
static const System::Byte ADS_DD_TABLE_TXN_FREE = System::Byte(0xdc);
static const System::Byte ADS_DD_TABLE_VALIDATION_EXPR_W = System::Byte(0xdd);
static const System::Byte ADS_DD_TABLE_WEB_DELTA = System::Byte(0xde);
static const System::Byte ADS_DD_TABLE_CONCURRENCY_ENABLED = System::Byte(0xdf);
static const System::Int8 ADS_DD_FIELD_OPT_VFP_BINARY = System::Int8(0x1);
static const System::Int8 ADS_DD_FIELD_OPT_VFP_NULLABLE = System::Int8(0x2);
static const int ADS_DD_FIELD_OPT_COMPRESSED = int(0x10000);
static const System::Word ADS_DD_FIELD_DEFAULT_VALUE = System::Word(0x12c);
static const System::Word ADS_DD_FIELD_CAN_NULL = System::Word(0x12d);
static const System::Word ADS_DD_FIELD_MIN_VALUE = System::Word(0x12e);
static const System::Word ADS_DD_FIELD_MAX_VALUE = System::Word(0x12f);
static const System::Word ADS_DD_FIELD_VALIDATION_MSG = System::Word(0x130);
static const System::Word ADS_DD_FIELD_DEFINITION = System::Word(0x131);
static const System::Word ADS_DD_FIELD_TYPE = System::Word(0x132);
static const System::Word ADS_DD_FIELD_LENGTH = System::Word(0x133);
static const System::Word ADS_DD_FIELD_DECIMAL = System::Word(0x134);
static const System::Word ADS_DD_FIELD_NUM = System::Word(0x135);
static const System::Word ADS_DD_FIELD_OPTIONS = System::Word(0x136);
static const System::Word ADS_DD_FIELD_DEFAULT_VALUE_W = System::Word(0x137);
static const System::Word ADS_DD_FIELD_MIN_VALUE_W = System::Word(0x138);
static const System::Word ADS_DD_FIELD_MAX_VALUE_W = System::Word(0x139);
static const System::Word ADS_DD_INDEX_FILE_NAME = System::Word(0x190);
static const System::Word ADS_DD_INDEX_EXPRESSION = System::Word(0x191);
static const System::Word ADS_DD_INDEX_CONDITION = System::Word(0x192);
static const System::Word ADS_DD_INDEX_OPTIONS = System::Word(0x193);
static const System::Word ADS_DD_INDEX_KEY_LENGTH = System::Word(0x194);
static const System::Word ADS_DD_INDEX_KEY_TYPE = System::Word(0x195);
static const System::Word ADS_DD_INDEX_FTS_MIN_LENGTH = System::Word(0x196);
static const System::Word ADS_DD_INDEX_FTS_DELIMITERS = System::Word(0x197);
static const System::Word ADS_DD_INDEX_FTS_NOISE = System::Word(0x198);
static const System::Word ADS_DD_INDEX_FTS_DROP_CHARS = System::Word(0x199);
static const System::Word ADS_DD_INDEX_FTS_CONDITIONAL_CHARS = System::Word(0x19a);
static const System::Word ADS_DD_INDEX_COLLATION = System::Word(0x19b);
static const System::Word ADS_DD_INDEX_FTS_DELIMITERS_W = System::Word(0x19c);
static const System::Word ADS_DD_INDEX_FTS_NOISE_W = System::Word(0x19d);
static const System::Word ADS_DD_INDEX_FTS_DROP_CHARS_W = System::Word(0x19e);
static const System::Word ADS_DD_INDEX_FTS_CONDITIONAL_CHARS_W = System::Word(0x19f);
static const System::Word ADS_DD_RI_PARENT_GRAPH = System::Word(0x1f4);
static const System::Word ADS_DD_RI_PRIMARY_TABLE = System::Word(0x1f5);
static const System::Word ADS_DD_RI_PRIMARY_INDEX = System::Word(0x1f6);
static const System::Word ADS_DD_RI_FOREIGN_TABLE = System::Word(0x1f7);
static const System::Word ADS_DD_RI_FOREIGN_INDEX = System::Word(0x1f8);
static const System::Word ADS_DD_RI_UPDATERULE = System::Word(0x1f9);
static const System::Word ADS_DD_RI_DELETERULE = System::Word(0x1fa);
static const System::Word ADS_DD_RI_NO_PKEY_ERROR = System::Word(0x1fb);
static const System::Word ADS_DD_RI_CASCADE_ERROR = System::Word(0x1fc);
static const System::Word ADS_DD_USER_GROUP_NAME = System::Word(0x258);
static const System::Word ADS_DD_VIEW_STMT = System::Word(0x2bc);
static const System::Word ADS_DD_VIEW_STMT_LEN = System::Word(0x2bd);
static const System::Word ADS_DD_VIEW_TRIGGER_TYPES = System::Word(0x2be);
static const System::Word ADS_DD_VIEW_TRIGGER_OPTIONS = System::Word(0x2bf);
static const System::Word ADS_DD_VIEW_STMT_W = System::Word(0x2c0);
static const System::Word ADS_DD_PROC_INPUT = System::Word(0x320);
static const System::Word ADS_DD_PROC_OUTPUT = System::Word(0x321);
static const System::Word ADS_DD_PROC_DLL_NAME = System::Word(0x322);
static const System::Word ADS_DD_PROC_DLL_FUNCTION_NAME = System::Word(0x323);
static const System::Word ADS_DD_PROC_INVOKE_OPTION = System::Word(0x324);
static const System::Word ADS_DD_PROC_SCRIPT = System::Word(0x325);
static const System::Word ADS_DD_PROC_SCRIPT_W = System::Word(0x326);
static const System::Word ADS_DD_INDEX_FILE_PATH = System::Word(0x384);
static const System::Word ADS_DD_INDEX_FILE_PAGESIZE = System::Word(0x385);
static const System::Word ADS_DD_INDEX_FILE_RELATIVE_PATH = System::Word(0x386);
static const System::Word ADS_DD_INDEX_FILE_TYPE = System::Word(0x387);
static const System::Word ADS_DD_TABLES_RIGHTS = System::Word(0x3e9);
static const System::Word ADS_DD_VIEWS_RIGHTS = System::Word(0x3ea);
static const System::Word ADS_DD_PROCS_RIGHTS = System::Word(0x3eb);
static const System::Word ADS_DD_OBJECTS_RIGHTS = System::Word(0x3ec);
static const System::Word ADS_DD_FREE_TABLES_RIGHTS = System::Word(0x3ed);
static const System::Word ADS_DD_USER_PASSWORD = System::Word(0x44d);
static const System::Word ADS_DD_USER_GROUP_MEMBERSHIP = System::Word(0x44e);
static const System::Word ADS_DD_USER_BAD_LOGINS = System::Word(0x44f);
static const System::Word ADS_DD_CURRENT_USER_PASSWORD = System::Word(0x450);
static const System::Word ADS_DD_REQUIRE_OLD_PASSWORD = System::Word(0x451);
static const System::Word ADS_DD_LINK_PATH = System::Word(0x514);
static const System::Word ADS_DD_LINK_OPTIONS = System::Word(0x515);
static const System::Word ADS_DD_LINK_USERNAME = System::Word(0x516);
static const System::Word ADS_DD_LINK_RELATIVE_PATH = System::Word(0x517);
static const System::Word ADS_DD_TRIG_TABLEID = System::Word(0x578);
static const System::Word ADS_DD_TRIG_EVENT_TYPE = System::Word(0x579);
static const System::Word ADS_DD_TRIG_TRIGGER_TYPE = System::Word(0x57a);
static const System::Word ADS_DD_TRIG_CONTAINER_TYPE = System::Word(0x57b);
static const System::Word ADS_DD_TRIG_CONTAINER = System::Word(0x57c);
static const System::Word ADS_DD_TRIG_FUNCTION_NAME = System::Word(0x57d);
static const System::Word ADS_DD_TRIG_PRIORITY = System::Word(0x57e);
static const System::Word ADS_DD_TRIG_OPTIONS = System::Word(0x57f);
static const System::Word ADS_DD_TRIG_TABLENAME = System::Word(0x580);
static const System::Word ADS_DD_TRIG_CONTAINER_W = System::Word(0x581);
static const System::Word ADS_DD_PUBLICATION_OPTIONS = System::Word(0x5dc);
static const System::Word ADS_DD_ARTICLE_FILTER = System::Word(0x640);
static const System::Word ADS_DD_ARTICLE_ID_COLUMNS = System::Word(0x641);
static const System::Word ADS_DD_ARTICLE_ID_COLUMN_NUMBERS = System::Word(0x642);
static const System::Word ADS_DD_ARTICLE_FILTER_SHORT = System::Word(0x643);
static const System::Word ADS_DD_ARTICLE_INCLUDE_COLUMNS = System::Word(0x644);
static const System::Word ADS_DD_ARTICLE_EXCLUDE_COLUMNS = System::Word(0x645);
static const System::Word ADS_DD_ARTICLE_INC_COLUMN_NUMBERS = System::Word(0x646);
static const System::Word ADS_DD_ARTICLE_INSERT_MERGE = System::Word(0x647);
static const System::Word ADS_DD_ARTICLE_UPDATE_MERGE = System::Word(0x648);
static const System::Word ADS_DD_ARTICLE_FILTER_W = System::Word(0x649);
static const System::Word ADS_DD_SUBSCR_PUBLICATION_NAME = System::Word(0x6a4);
static const System::Word ADS_DD_SUBSCR_TARGET = System::Word(0x6a5);
static const System::Word ADS_DD_SUBSCR_USERNAME = System::Word(0x6a6);
static const System::Word ADS_DD_SUBSCR_PASSWORD = System::Word(0x6a7);
static const System::Word ADS_DD_SUBSCR_FORWARD = System::Word(0x6a8);
static const System::Word ADS_DD_SUBSCR_ENABLED = System::Word(0x6a9);
static const System::Word ADS_DD_SUBSCR_QUEUE_NAME = System::Word(0x6aa);
static const System::Word ADS_DD_SUBSCR_OPTIONS = System::Word(0x6ab);
static const System::Word ADS_DD_SUBSCR_QUEUE_NAME_RELATIVE = System::Word(0x6ac);
static const System::Word ADS_DD_SUBSCR_PAUSED = System::Word(0x6ad);
static const System::Word ADS_DD_SUBSCR_COMM_TCP_IP = System::Word(0x6ae);
static const System::Word ADS_DD_SUBSCR_COMM_TCP_IP_V6 = System::Word(0x6af);
static const System::Word ADS_DD_SUBSCR_COMM_UDP_IP = System::Word(0x6b0);
static const System::Word ADS_DD_SUBSCR_COMM_IPX = System::Word(0x6b1);
static const System::Word ADS_DD_SUBSCR_OPTIONS_INTERNAL = System::Word(0x6b2);
static const System::Word ADS_DD_SUBSCR_COMM_TLS = System::Word(0x6b3);
static const System::Word ADS_DD_SUBSCR_CONNECTION_STR = System::Word(0x6b4);
static const System::Int8 ADS_PROPERTY_UNSPECIFIED = System::Int8(0x0);
static const System::Int8 ADS_DONT_KILL_APPID = System::Int8(0x1);
static const System::Int8 ADS_DD_LEVEL_0 = System::Int8(0x0);
static const System::Int8 ADS_DD_LEVEL_1 = System::Int8(0x1);
static const System::Int8 ADS_DD_LEVEL_2 = System::Int8(0x2);
static const System::Int8 ADS_DD_RI_CASCADE = System::Int8(0x1);
static const System::Int8 ADS_DD_RI_RESTRICT = System::Int8(0x2);
static const System::Int8 ADS_DD_RI_SETNULL = System::Int8(0x3);
static const System::Int8 ADS_DD_RI_SETDEFAULT = System::Int8(0x4);
static const System::Int8 ADS_DD_DFV_UNKNOWN = System::Int8(0x1);
static const System::Int8 ADS_DD_DFV_NONE = System::Int8(0x2);
static const System::Int8 ADS_DD_DFV_VALUES_STORED = System::Int8(0x3);
static const System::Int8 ADS_PERMISSION_NONE = System::Int8(0x0);
static const System::Int8 ADS_PERMISSION_READ = System::Int8(0x1);
static const System::Int8 ADS_PERMISSION_UPDATE = System::Int8(0x2);
static const System::Int8 ADS_PERMISSION_EXECUTE = System::Int8(0x4);
static const System::Int8 ADS_PERMISSION_INHERIT = System::Int8(0x8);
static const System::Int8 ADS_PERMISSION_INSERT = System::Int8(0x10);
static const System::Int8 ADS_PERMISSION_DELETE = System::Int8(0x20);
static const System::Int8 ADS_PERMISSION_LINK_ACCESS = System::Int8(0x40);
static const System::Byte ADS_PERMISSION_CREATE = System::Byte(0x80);
static const System::Word ADS_PERMISSION_ALTER = System::Word(0x100);
static const System::Word ADS_PERMISSION_DROP = System::Word(0x200);
static const unsigned ADS_PERMISSION_WITH_GRANT = unsigned(0x80000000);
static const unsigned ADS_PERMISSION_ALL_WITH_GRANT = unsigned(0x8fffffff);
static const unsigned ADS_PERMISSION_ALL = unsigned(0xffffffff);
static const unsigned ADS_GET_PERMISSIONS_WITH_GRANT = unsigned(0x8000ffff);
static const unsigned ADS_GET_PERMISSIONS_CREATE = unsigned(0xffff0080);
static const unsigned ADS_GET_PERMISSIONS_CREATE_WITH_GRANT = unsigned(0x8fffff8f);
static const System::Int8 ADS_LINK_GLOBAL = System::Int8(0x1);
static const System::Int8 ADS_LINK_AUTH_ACTIVE_USER = System::Int8(0x2);
static const System::Int8 ADS_LINK_PATH_IS_STATIC = System::Int8(0x4);
static const System::Int8 ADS_TRIGEVENT_INSERT = System::Int8(0x1);
static const System::Int8 ADS_TRIGEVENT_UPDATE = System::Int8(0x2);
static const System::Int8 ADS_TRIGEVENT_DELETE = System::Int8(0x3);
static const System::Int8 ADS_TRIGEVENT_OPEN_TABLE = System::Int8(0x4);
static const System::Int8 ADS_TRIGEVENT_CLOSE_TABLE = System::Int8(0x5);
static const System::Int8 ADS_TRIGEVENT_CONNECT = System::Int8(0x6);
static const System::Int8 ADS_TRIGEVENT_DISCONNECT = System::Int8(0x7);
static const System::Int8 ADS_TRIGTYPE_BEFORE = System::Int8(0x1);
static const System::Int8 ADS_TRIGTYPE_INSTEADOF = System::Int8(0x2);
static const System::Int8 ADS_TRIGTYPE_AFTER = System::Int8(0x4);
static const System::Int8 ADS_TRIGTYPE_CONFLICTON = System::Int8(0x8);
static const System::Int8 ADS_TRIG_WIN32DLL = System::Int8(0x1);
static const System::Int8 ADS_TRIG_COM = System::Int8(0x2);
static const System::Int8 ADS_TRIG_SCRIPT = System::Int8(0x3);
static const System::Int8 ADS_TRIGOPTIONS_NO_VALUES = System::Int8(0x0);
static const System::Int8 ADS_TRIGOPTIONS_WANT_VALUES = System::Int8(0x1);
static const System::Int8 ADS_TRIGOPTIONS_WANT_MEMOS_AND_BLOBS = System::Int8(0x2);
static const System::Int8 ADS_TRIGOPTIONS_DEFAULT = System::Int8(0x3);
static const System::Int8 ADS_TRIGOPTIONS_NO_TRANSACTION = System::Int8(0x4);
static const System::Int8 ADS_DD_TABLE_PERMISSION_LEVEL_1 = System::Int8(0x1);
static const System::Int8 ADS_DD_TABLE_PERMISSION_LEVEL_2 = System::Int8(0x2);
static const System::Int8 ADS_DD_TABLE_PERMISSION_LEVEL_3 = System::Int8(0x3);
static const System::Int8 ADS_KEEP_TABLE_FILE_NAME = System::Int8(0x1);
static const System::Int8 ADS_IDENTIFY_BY_PRIMARY = System::Int8(0x1);
static const System::Int8 ADS_IDENTIFY_BY_ALL = System::Int8(0x2);
static const System::Int8 ADS_SUBSCR_QUEUE_IS_STATIC = System::Int8(0x1);
static const System::Int8 ADS_SUBSCR_AIS_TARGET = System::Int8(0x2);
static const System::Int8 ADS_SUBSCR_IGNORE_FAILED_REP = System::Int8(0x4);
static const System::Int8 ADS_SUBSCR_LOG_FAILED_REP_DATA = System::Int8(0x8);
static const System::Int8 ADS_CODEUNIT_LENGTH = System::Int8(0x0);
static const System::Int8 ADS_BYTE_LENGTH = System::Int8(0x1);
static const System::Int8 ADS_BYTE_LENGTH_IN_BUFFER = System::Int8(0x2);
static const System::Int8 ADS_FS_MULTICAST_ONLY = System::Int8(0x1);
static const System::Int8 ADS_FS_CONNECT_ALL = System::Int8(0x2);
static const System::Int8 ADS_TABLE_CACHE_NONE = System::Int8(0x0);
static const System::Int8 ADS_TABLE_CACHE_READS = System::Int8(0x1);
static const System::Int8 ADS_TABLE_CACHE_WRITES = System::Int8(0x2);
#define ADS_ENCRYPT_STRING_RC4 L"RC4"
#define ADS_ENCRYPT_STRING_AES128 L"AES128"
#define ADS_ENCRYPT_STRING_AES256 L"AES256"
#define ADS_CIPHER_SUITE_STRING_RC4 L"RC4-MD5"
#define ADS_CIPHER_SUITE_STRING_AES128 L"AES128-SHA"
#define ADS_CIPHER_SUITE_STRING_AES256 L"AES256-SHA"
#define ADS_ROOT_DD_ALIAS L"__rootdd"
static const System::Int8 ADS_FILTER_FORMAT_ODATA = System::Int8(0x1);
static const System::Int8 ADS_FILTER_ENCODE_UTF8 = System::Int8(0x2);
}	/* namespace Adscli */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ADSCLI)
using namespace Firedac::Phys::Adscli;
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
#endif	// Firedac_Phys_AdscliHPP
