// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBServices.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbservicesHPP
#define Ibx_IbservicesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <IBX.IBHeader.hpp>
#include <IBX.IB.hpp>
#include <IBX.IBIntf.hpp>
#include <System.Variants.hpp>
#include <IBX.IBExternals.hpp>
#include <IBX.IBDatabase.hpp>
#include <IBX.IBUtils.hpp>
#include <IBX.IBDatabaseInfo.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibservices
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBCustomService;
class DELPHICLASS TDatabaseInfo;
class DELPHICLASS TLicenseInfo;
class DELPHICLASS TLicenseMaskInfo;
class DELPHICLASS TConfigFileData;
class DELPHICLASS TConfigParams;
class DELPHICLASS TVersionInfo;
class DELPHICLASS TIBControlService;
class DELPHICLASS TIBControlAndQueryService;
class DELPHICLASS TIBAliasInfo;
class DELPHICLASS TIBServerProperties;
class DELPHICLASS TIBCustomConfigService;
struct TIBJournalFileInfo;
class DELPHICLASS TIBJournalInformation;
class DELPHICLASS TIBConfigService;
class DELPHICLASS TIBLicensingService;
class DELPHICLASS TIBLogService;
class DELPHICLASS TIBStatisticalService;
class DELPHICLASS TIBBackupRestoreService;
struct TTablespaceDumpLocation;
class DELPHICLASS TIBBackupService;
struct TIBTablespaceInfo;
struct TIBTablespaceStruct;
class DELPHICLASS TIBRestoreService;
class DELPHICLASS TLimboTransactionInfo;
class DELPHICLASS TIBValidationService;
class DELPHICLASS TUserInfo;
class DELPHICLASS TIBSecurityService;
//-- type declarations -------------------------------------------------------
typedef Ibx::Ibutils::TIBProtocol TProtocol;

typedef System::Generics::Collections::TDictionary__2<System::UnicodeString,int>* TSPBConstants;

enum DECLSPEC_DENUM TOutputBufferOption : unsigned char { ByLine, ByChunk };

typedef void __fastcall (__closure *TIBLoginEvent)(TIBCustomService* Database, System::Classes::TStrings* LoginParams);

class PASCALIMPLEMENTATION TIBCustomService : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	bool FParamsChanged;
	System::Byte *FSPB;
	System::Byte *FQuerySPB;
	short FSPBLength;
	short FQuerySPBLength;
	Ibx::Ib::TTraceFlags FTraceFlags;
	TIBLoginEvent FOnLogin;
	bool FLoginPrompt;
	int FBufferSize;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FOutputBuffer;
	System::DynamicArray<System::Byte> FQueryParams;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FOutputBuffer;
	System::TArray__1<System::Byte> FQueryParams;
#endif /* _WIN64 */
	System::UnicodeString FServerName;
	void * *FHandle;
	bool FStreamedActive;
	System::Classes::TNotifyEvent FOnAttach;
	System::Classes::TNotifyEvent FBeforeAttach;
	TOutputBufferOption FOutputBufferOption;
	Ibx::Ibutils::TIBProtocol FProtocol;
	System::Classes::TStrings* FParams;
	Ibx::Ibintf::_di_IGDSLibrary FGDSLibrary;
	System::UnicodeString FServerType;
	bool __fastcall GetActive();
	virtual System::UnicodeString __fastcall GetServiceParamBySPB(const int Idx);
	void __fastcall SetActive(const bool Value);
	void __fastcall SetBufferSize(const int Value);
	void __fastcall SetParams(System::Classes::TStrings* const Value);
	void __fastcall SetServerName(const System::UnicodeString Value);
	void __fastcall SetProtocol(const Ibx::Ibutils::TIBProtocol Value);
	virtual void __fastcall SetServiceParamBySPB(const int Idx, const System::UnicodeString Value);
	int __fastcall IndexOfSPBConst(System::UnicodeString st);
	void __fastcall ParamsChange(System::TObject* Sender);
	void __fastcall ParamsChanging(System::TObject* Sender);
	void __fastcall CheckServerName();
	NativeInt __fastcall Call(NativeInt ErrCode, bool RaiseError);
	System::UnicodeString __fastcall ParseString(int &RunLen);
	int __fastcall ParseInteger(int &RunLen);
#ifndef _WIN64
	virtual bool __fastcall GenerateCustomSPB(int SPBVal, System::UnicodeString Param_Value, System::DynamicArray<System::Byte> &SPB, short &SPBLength, int &SPBPos);
	void __fastcall GenerateSPB(System::Classes::TStrings* sl, System::DynamicArray<System::Byte> &SPB, short &SPBLength);
#else /* _WIN64 */
	virtual bool __fastcall GenerateCustomSPB(int SPBVal, System::UnicodeString Param_Value, System::TArray__1<System::Byte> &SPB, short &SPBLength, int &SPBPos);
	void __fastcall GenerateSPB(System::Classes::TStrings* sl, System::TArray__1<System::Byte> &SPB, short &SPBLength);
#endif /* _WIN64 */
	void __fastcall SetServerType(const System::UnicodeString Value);
	Ibx::Ibintf::_di_IGDSLibrary __fastcall GetGDSLibrary();
	
protected:
	virtual void __fastcall Loaded();
	bool __fastcall Login();
	void __fastcall CheckActive();
	void __fastcall CheckInactive();
	virtual void __fastcall DoServerChange();
#ifndef _WIN64
	__property System::DynamicArray<System::Byte> OutputBuffer = {read=FOutputBuffer};
#else /* _WIN64 */
	__property System::TArray__1<System::Byte> OutputBuffer = {read=FOutputBuffer};
#endif /* _WIN64 */
	__property TOutputBufferOption OutputBufferOption = {read=FOutputBufferOption, write=FOutputBufferOption, nodefault};
	__property int BufferSize = {read=FBufferSize, write=SetBufferSize, default=32000};
	void __fastcall InternalServiceQuery();
#ifndef _WIN64
	__property System::DynamicArray<System::Byte> ServiceQueryParams = {read=FQueryParams, write=FQueryParams};
#else /* _WIN64 */
	__property System::TArray__1<System::Byte> ServiceQueryParams = {read=FQueryParams, write=FQueryParams};
#endif /* _WIN64 */
	__property Ibx::Ibintf::_di_IGDSLibrary GDSLibrary = {read=GetGDSLibrary};
	void __fastcall AddQueryParam(int param);
	
public:
	__fastcall virtual TIBCustomService(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBCustomService();
	void __fastcall Attach();
	void __fastcall Detach();
	__property Ibx::Ibexternals::PVoid Handle = {read=FHandle};
	__property System::UnicodeString ServiceParamBySPB[const int Idx] = {read=GetServiceParamBySPB, write=SetServiceParamBySPB};
	
__published:
	__property bool Active = {read=GetActive, write=SetActive, default=0};
	__property System::UnicodeString ServerName = {read=FServerName, write=SetServerName};
	__property Ibx::Ibutils::TIBProtocol Protocol = {read=FProtocol, write=SetProtocol, default=3};
	__property System::Classes::TStrings* Params = {read=FParams, write=SetParams};
	__property bool LoginPrompt = {read=FLoginPrompt, write=FLoginPrompt, default=1};
	__property Ibx::Ib::TTraceFlags TraceFlags = {read=FTraceFlags, write=FTraceFlags, nodefault};
	__property System::Classes::TNotifyEvent BeforeAttach = {read=FBeforeAttach, write=FBeforeAttach};
	__property System::Classes::TNotifyEvent OnAttach = {read=FOnAttach, write=FOnAttach};
	__property TIBLoginEvent OnLogin = {read=FOnLogin, write=FOnLogin};
	__property System::UnicodeString ServerType = {read=FServerType, write=SetServerType};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDatabaseInfo : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<System::UnicodeString> _TDatabaseInfo__1;
	
	
public:
	int NoOfAttachments;
	int NoOfDatabases;
	_TDatabaseInfo__1 DbName;
	__fastcall TDatabaseInfo();
	__fastcall virtual ~TDatabaseInfo();
	void __fastcall Clear();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TLicenseInfo : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<System::UnicodeString> _TLicenseInfo__1;
	
	typedef System::DynamicArray<System::UnicodeString> _TLicenseInfo__2;
	
	typedef System::DynamicArray<System::UnicodeString> _TLicenseInfo__3;
	
	
public:
	_TLicenseInfo__1 Key;
	_TLicenseInfo__2 Id;
	_TLicenseInfo__3 Desc;
	int LicensedUsers;
	__fastcall TLicenseInfo();
	__fastcall virtual ~TLicenseInfo();
	void __fastcall Clear();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TLicenseMaskInfo : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	int LicenseMask;
	int CapabilityMask;
	void __fastcall Clear();
public:
	/* TObject.Create */ inline __fastcall TLicenseMaskInfo() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TLicenseMaskInfo() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TConfigFileData : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<int> _TConfigFileData__1;
	
	typedef System::DynamicArray<int> _TConfigFileData__2;
	
	
public:
	_TConfigFileData__1 ConfigFileValue;
	_TConfigFileData__2 ConfigFileKey;
	__fastcall TConfigFileData();
	__fastcall virtual ~TConfigFileData();
	void __fastcall Clear();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TConfigParams : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<System::UnicodeString> _TConfigParams__1;
	
	
public:
	TConfigFileData* ConfigFileData;
	_TConfigParams__1 ConfigFileParams;
	System::UnicodeString BaseLocation;
	System::UnicodeString LockFileLocation;
	System::UnicodeString MessageFileLocation;
	System::UnicodeString SecurityDatabaseLocation;
	__fastcall TConfigParams();
	__fastcall virtual ~TConfigParams();
	void __fastcall Clear();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TVersionInfo : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::UnicodeString ServerVersion;
	System::UnicodeString ServerImplementation;
	int ServiceVersion;
	bool __fastcall IsMinimumVersion(System::UnicodeString MinVersion);
	void __fastcall Clear();
public:
	/* TObject.Create */ inline __fastcall TVersionInfo() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TVersionInfo() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TIBControlService : public TIBCustomService
{
	typedef TIBCustomService inherited;
	
private:
#ifndef _WIN64
	System::DynamicArray<System::Byte> FStartParams;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FStartParams;
#endif /* _WIN64 */
	System::Byte *FStartSPB;
	int FStartSPBLength;
	bool __fastcall GetIsServiceRunning();
	
protected:
#ifndef _WIN64
	__property System::DynamicArray<System::Byte> ServiceStartParams = {read=FStartParams, write=FStartParams};
#else /* _WIN64 */
	__property System::TArray__1<System::Byte> ServiceStartParams = {read=FStartParams, write=FStartParams};
#endif /* _WIN64 */
	virtual void __fastcall SetServiceStartOptions();
	void __fastcall ServiceStartAddParam(System::UnicodeString Value, int param)/* overload */;
	void __fastcall ServiceStartAddParam(int Value, int param)/* overload */;
	void __fastcall ServiceStartAddParam(System::Int8 Value, int param)/* overload */;
	void __fastcall ServiceStartAddParam(__int64 Value, int param)/* overload */;
	void __fastcall ServiceStartAddParam(int param)/* overload */;
	void __fastcall InternalServiceStart();
	bool __fastcall IsMinimumVersion(System::UnicodeString aVer);
	
public:
	__fastcall virtual TIBControlService(System::Classes::TComponent* AOwner);
	virtual void __fastcall ServiceStart();
	__property bool IsServiceRunning = {read=GetIsServiceRunning, nodefault};
public:
	/* TIBCustomService.Destroy */ inline __fastcall virtual ~TIBControlService() { }
	
};


class PASCALIMPLEMENTATION TIBControlAndQueryService : public TIBControlService
{
	typedef TIBControlService inherited;
	
private:
	bool FEof;
	int FAction;
	void __fastcall SetAction(int Value);
	
protected:
	__property int Action = {read=FAction, write=SetAction, nodefault};
	
public:
	__fastcall virtual TIBControlAndQueryService(System::Classes::TComponent* AOwner);
	System::UnicodeString __fastcall GetNextLine();
	System::UnicodeString __fastcall GetNextChunk()/* overload */;
	int __fastcall GetNextChunk(System::PByte Bytes)/* overload */;
	__property bool Eof = {read=FEof, nodefault};
	
__published:
	__property BufferSize = {default=32000};
public:
	/* TIBCustomService.Destroy */ inline __fastcall virtual ~TIBControlAndQueryService() { }
	
};


enum DECLSPEC_DENUM TPropertyOption : unsigned char { Database, License, LicenseMask, ConfigParameters, Version, DBAlias };

typedef System::Set<TPropertyOption, TPropertyOption::Database, TPropertyOption::DBAlias> TPropertyOptions;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIBAliasInfo : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::UnicodeString Alias;
	System::UnicodeString DBPath;
public:
	/* TObject.Create */ inline __fastcall TIBAliasInfo() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIBAliasInfo() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::DynamicArray<TIBAliasInfo*> TIBAliasInfos;

class PASCALIMPLEMENTATION TIBServerProperties : public TIBControlService
{
	typedef TIBControlService inherited;
	
private:
	TPropertyOptions FOptions;
	TDatabaseInfo* FDatabaseInfo;
	TLicenseInfo* FLicenseInfo;
	TLicenseMaskInfo* FLicenseMaskInfo;
	TVersionInfo* FVersionInfo;
	TConfigParams* FConfigParams;
	TIBAliasInfos FAliasInfos;
	void __fastcall ParseConfigFileData(int &RunLen);
	int __fastcall GetAliasCount();
	TIBAliasInfo* __fastcall GetAliasInfo(int Index);
	
protected:
	virtual void __fastcall DoServerChange();
	
public:
	__fastcall virtual TIBServerProperties(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBServerProperties();
	void __fastcall Fetch();
	void __fastcall FetchDatabaseInfo();
	void __fastcall FetchLicenseInfo();
	void __fastcall FetchLicenseMaskInfo();
	void __fastcall FetchConfigParams();
	void __fastcall FetchVersionInfo();
	void __fastcall FetchAliasInfo();
	void __fastcall AddAlias(System::UnicodeString Alias, System::UnicodeString DBPath);
	void __fastcall DeleteAlias(System::UnicodeString Alias);
	__property TDatabaseInfo* DatabaseInfo = {read=FDatabaseInfo};
	__property TLicenseInfo* LicenseInfo = {read=FLicenseInfo};
	__property TLicenseMaskInfo* LicenseMaskInfo = {read=FLicenseMaskInfo};
	__property TVersionInfo* VersionInfo = {read=FVersionInfo};
	__property TConfigParams* ConfigParams = {read=FConfigParams};
	__property int AliasCount = {read=GetAliasCount, nodefault};
	__property TIBAliasInfo* AliasInfo[int Index] = {read=GetAliasInfo};
	__property TIBAliasInfos AliasInfos = {read=FAliasInfos};
	
__published:
	__property TPropertyOptions Options = {read=FOptions, write=FOptions, nodefault};
};


enum DECLSPEC_DENUM TShutdownMode : unsigned char { Forced, DenyTransaction, DenyAttachment };

class PASCALIMPLEMENTATION TIBCustomConfigService : public TIBControlService
{
	typedef TIBControlService inherited;
	
private:
	System::UnicodeString FDatabaseName;
	Ibx::Ibdatabase::TIBTransaction* FTransaction;
	Ibx::Ibdatabase::TIBDatabase* FDatabase;
	
protected:
	virtual void __fastcall SetDatabaseName(const System::UnicodeString Value);
	void __fastcall ExecuteSQL(System::UnicodeString SQL)/* overload */;
	System::Variant __fastcall ExecuteSQL(System::UnicodeString SQL, System::UnicodeString Field)/* overload */;
	Ibx::Ibdatabase::TIBDatabase* __fastcall BuildIBDatabase();
	Ibx::Ibdatabase::TIBTransaction* __fastcall BuildIBTransaction();
	
public:
	virtual void __fastcall ServiceStart();
	
__published:
	__property System::UnicodeString DatabaseName = {read=FDatabaseName, write=SetDatabaseName};
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=FDatabase, write=FDatabase};
	__property Ibx::Ibdatabase::TIBTransaction* Transaction = {read=FTransaction, write=FTransaction};
public:
	/* TIBControlService.Create */ inline __fastcall virtual TIBCustomConfigService(System::Classes::TComponent* AOwner) : TIBControlService(AOwner) { }
	
public:
	/* TIBCustomService.Destroy */ inline __fastcall virtual ~TIBCustomConfigService() { }
	
};


struct DECLSPEC_DRECORD TIBJournalFileInfo
{
public:
	System::UnicodeString FileName;
	int Sequence;
	System::TDateTime ArchiveTime;
	int DependedOnSequence;
	System::TDateTime DependedOnTime;
};


#ifndef _WIN64
typedef System::DynamicArray<TIBJournalFileInfo> TIBJournalFileInfoArray;
#else /* _WIN64 */
typedef System::TArray__1<TIBJournalFileInfo> TIBJournalFileInfoArray;
#endif /* _WIN64 */

class PASCALIMPLEMENTATION TIBJournalInformation : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::UnicodeString FDirectory;
	int FPageCache;
	int FCheckpointInterval;
	bool FTimestampName;
	int FPageSize;
	int FCheckpointLength;
	int FPageLength;
	bool FHasJournal;
	bool FHasArchive;
	int FPreallocate;
#ifndef _WIN64
	System::DynamicArray<TIBJournalFileInfo> FJournalFiles;
	System::DynamicArray<TIBJournalFileInfo> FArchiveFiles;
#else /* _WIN64 */
	System::TArray__1<TIBJournalFileInfo> FJournalFiles;
	System::TArray__1<TIBJournalFileInfo> FArchiveFiles;
#endif /* _WIN64 */
	System::UnicodeString FArchiveDirectory;
	int FArchiveDumpLimit;
	
public:
	__fastcall virtual TIBJournalInformation(System::Classes::TComponent* AOwner);
	System::UnicodeString __fastcall CreateJournalAttributes();
	System::UnicodeString __fastcall CreateJournalLength();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall AddJournalFile(const TIBJournalFileInfo &AFile);
	void __fastcall AddArchiveFile(const TIBJournalFileInfo &AFile);
	void __fastcall Clear();
	
__published:
	__property bool HasJournal = {read=FHasJournal, nodefault};
	__property int CheckpointInterval = {read=FCheckpointInterval, write=FCheckpointInterval, default=0};
	__property int CheckpointLength = {read=FCheckpointLength, write=FCheckpointLength, default=500};
	__property int PageCache = {read=FPageCache, write=FPageCache, default=100};
	__property int PageLength = {read=FPageLength, write=FPageLength, default=4000};
	__property int PageSize = {read=FPageSize, write=FPageSize, default=0};
	__property bool TimestampName = {read=FTimestampName, write=FTimestampName, default=1};
	__property int ArchiveDumpLimit = {read=FArchiveDumpLimit, nodefault};
	__property System::UnicodeString Directory = {read=FDirectory, write=FDirectory};
	__property System::UnicodeString ArchiveDirectory = {read=FArchiveDirectory, write=FArchiveDirectory};
	__property int PreAllocate = {read=FPreallocate, write=FPreallocate, default=0};
	__property bool HasArchive = {read=FHasArchive, nodefault};
#ifndef _WIN64
	__property System::DynamicArray<TIBJournalFileInfo> ArchiveFiles = {read=FArchiveFiles};
	__property System::DynamicArray<TIBJournalFileInfo> JournalFiles = {read=FJournalFiles};
#else /* _WIN64 */
	__property System::TArray__1<TIBJournalFileInfo> ArchiveFiles = {read=FArchiveFiles};
	__property System::TArray__1<TIBJournalFileInfo> JournalFiles = {read=FJournalFiles};
#endif /* _WIN64 */
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIBJournalInformation() { }
	
};


enum DECLSPEC_DENUM TIBEncryptionTypes : unsigned char { encDES, encAES };

class PASCALIMPLEMENTATION TIBConfigService : public TIBCustomConfigService
{
	typedef TIBCustomConfigService inherited;
	
private:
	TIBJournalInformation* FIBJournalInformation;
	int __fastcall GetLingerInterval();
	int __fastcall GetFlushInterval();
	int __fastcall GetReclaimInterval();
	int __fastcall GetSweepInterval();
	bool __fastcall GetGroupCommit();
	System::UnicodeString __fastcall GetDBOwner();
	
public:
	__fastcall virtual TIBConfigService(System::Classes::TComponent* AOwner);
	void __fastcall ShutdownDatabase(TShutdownMode Options, int Wait);
	void __fastcall SetSweepInterval(int Value);
	void __fastcall SetDBSqlDialect(int Value);
	void __fastcall SetPageBuffers(int Value);
	int __fastcall GetPageBuffers();
	void __fastcall ActivateShadow();
	void __fastcall BringDatabaseOnline();
	void __fastcall SetReserveSpace(bool Value);
	void __fastcall SetAsyncMode _DEPRECATED_ATTRIBUTE1("For InterBase XE2 and up use SetWriteMode") (bool Value);
	void __fastcall SetWriteMode(Ibx::Ibdatabaseinfo::TIBWriteMode Value);
	void __fastcall SetReadOnly(bool Value);
	void __fastcall SetFlushInterval(int Value);
	void __fastcall DisableFlush();
	void __fastcall SetGroupCommit(bool Value);
	void __fastcall SetLingerInterval(int Value);
	void __fastcall FlushDatabase();
	void __fastcall ReclaimMemory();
	void __fastcall SetReclaimInterval(int Value);
	void __fastcall SweepDatabase();
	void __fastcall SweepArchive(int SeqNo);
	void __fastcall DropJournal();
	void __fastcall CreateJournal();
	void __fastcall CreateJournalArchive(System::UnicodeString Directory);
	void __fastcall DropJournalArchive();
	void __fastcall GetJournalInformation();
	void __fastcall ArchiveDumpLimit(int Limit);
	void __fastcall SetSystemEncryption(System::UnicodeString Password, bool External);
	void __fastcall CreateEncryptionKey(System::UnicodeString keyname, bool Default, TIBEncryptionTypes EncryptType, int WithLength, System::UnicodeString Password, bool RandomInitvector, bool RandomPad, System::UnicodeString Description);
	void __fastcall DropEncryptionKey(System::UnicodeString keyname, bool cascade);
	void __fastcall GrantEncryptionTo(bool Grant, System::UnicodeString keyName, System::UnicodeString userName);
	void __fastcall EncryptDatabase(System::UnicodeString encryptionKey = System::UnicodeString());
	void __fastcall DecryptDatabase();
	void __fastcall EncryptColumn(System::UnicodeString tableName, System::UnicodeString columnName, System::UnicodeString encryptionKey);
	void __fastcall DefaultDecryption(System::UnicodeString tableName, System::UnicodeString ColumnName, System::UnicodeString defaultValue);
	void __fastcall ReserveSpace(bool Reserved, System::UnicodeString TableName = System::UnicodeString());
	__property int LingerInterval = {read=GetLingerInterval, write=SetLingerInterval, nodefault};
	__property int FlushInterval = {read=GetFlushInterval, write=SetFlushInterval, nodefault};
	__property int ReclaimInterval = {read=GetReclaimInterval, write=SetReclaimInterval, nodefault};
	__property int SweepInterval = {read=GetSweepInterval, write=SetSweepInterval, nodefault};
	__property bool GroupCommit = {read=GetGroupCommit, write=SetGroupCommit, nodefault};
	__property System::UnicodeString DBOwner = {read=GetDBOwner};
	
__published:
	__property TIBJournalInformation* JournalInformation = {read=FIBJournalInformation};
public:
	/* TIBCustomService.Destroy */ inline __fastcall virtual ~TIBConfigService() { }
	
};


enum DECLSPEC_DENUM TLicensingAction : unsigned char { LicenseAdd, LicenseRemove };

class PASCALIMPLEMENTATION TIBLicensingService : public TIBControlService
{
	typedef TIBControlService inherited;
	
private:
	System::UnicodeString FID;
	System::UnicodeString FKey;
	TLicensingAction FAction;
	void __fastcall SetAction(TLicensingAction Value);
	
protected:
	virtual void __fastcall SetServiceStartOptions();
	
public:
	void __fastcall AddLicense();
	void __fastcall RemoveLicense();
	
__published:
	__property TLicensingAction Action = {read=FAction, write=SetAction, default=0};
	__property System::UnicodeString Key = {read=FKey, write=FKey};
	__property System::UnicodeString ID = {read=FID, write=FID};
public:
	/* TIBControlService.Create */ inline __fastcall virtual TIBLicensingService(System::Classes::TComponent* AOwner) : TIBControlService(AOwner) { }
	
public:
	/* TIBCustomService.Destroy */ inline __fastcall virtual ~TIBLicensingService() { }
	
};


class PASCALIMPLEMENTATION TIBLogService : public TIBControlAndQueryService
{
	typedef TIBControlAndQueryService inherited;
	
protected:
	virtual void __fastcall SetServiceStartOptions();
	
public:
	System::UnicodeString __fastcall GetLogFile();
public:
	/* TIBControlAndQueryService.Create */ inline __fastcall virtual TIBLogService(System::Classes::TComponent* AOwner) : TIBControlAndQueryService(AOwner) { }
	
public:
	/* TIBCustomService.Destroy */ inline __fastcall virtual ~TIBLogService() { }
	
};


enum DECLSPEC_DENUM TStatOption : unsigned char { DataPages, DbLog, HeaderPages, IndexPages, SystemRelations, RecordVersions, StatTables };

typedef System::Set<TStatOption, TStatOption::DataPages, TStatOption::StatTables> TStatOptions;

class PASCALIMPLEMENTATION TIBStatisticalService : public TIBControlAndQueryService
{
	typedef TIBControlAndQueryService inherited;
	
private:
	System::UnicodeString FDatabaseName;
	TStatOptions FOptions;
	System::UnicodeString FTableNames;
	void __fastcall SetDatabaseName(const System::UnicodeString Value);
	
protected:
	virtual void __fastcall SetServiceStartOptions();
	
__published:
	__property System::UnicodeString DatabaseName = {read=FDatabaseName, write=SetDatabaseName};
	__property TStatOptions Options = {read=FOptions, write=FOptions, nodefault};
	__property System::UnicodeString TableNames = {read=FTableNames, write=FTableNames};
public:
	/* TIBControlAndQueryService.Create */ inline __fastcall virtual TIBStatisticalService(System::Classes::TComponent* AOwner) : TIBControlAndQueryService(AOwner) { }
	
public:
	/* TIBCustomService.Destroy */ inline __fastcall virtual ~TIBStatisticalService() { }
	
};


class PASCALIMPLEMENTATION TIBBackupRestoreService : public TIBControlAndQueryService
{
	typedef TIBControlAndQueryService inherited;
	
private:
	bool FVerbose;
	int FPreAllocate;
	System::UnicodeString FEncryptName;
	System::UnicodeString FEncryptPassword;
	System::Classes::TStrings* FExcludeTablespaces;
	System::Classes::TStrings* FIncludeTablespaces;
	void __fastcall SetExcludeTablespaces(System::Classes::TStrings* const Value);
	void __fastcall SetIncludeTablespaces(System::Classes::TStrings* const Value);
	
protected:
	void __fastcall VersionCheck(const System::UnicodeString IBVersion, const System::UnicodeString ErrorMessage);
	__property int PreAllocate = {read=FPreAllocate, write=FPreAllocate, nodefault};
	__property System::UnicodeString EncryptName = {read=FEncryptName, write=FEncryptName};
	__property System::UnicodeString EncryptPassword = {read=FEncryptPassword, write=FEncryptPassword};
	
public:
	__fastcall virtual TIBBackupRestoreService(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBBackupRestoreService();
	
__published:
	__property bool Verbose = {read=FVerbose, write=FVerbose, default=0};
	__property System::Classes::TStrings* ExcludeTablespaces = {read=FExcludeTablespaces, write=SetExcludeTablespaces};
	__property System::Classes::TStrings* IncludeTablespaces = {read=FIncludeTablespaces, write=SetIncludeTablespaces};
};


enum DECLSPEC_DENUM TBackupOption : unsigned char { IgnoreChecksums, IgnoreLimbo, MetadataOnly, NoGarbageCollection, OldMetadataDesc, NonTransportable, ConvertExtTables };

typedef System::Set<TBackupOption, TBackupOption::IgnoreChecksums, TBackupOption::ConvertExtTables> TBackupOptions;

struct DECLSPEC_DRECORD TTablespaceDumpLocation
{
public:
	System::UnicodeString TablespaceName;
	System::UnicodeString FilePath;
	int FileSetId;
	System::TDateTime FileTimestamp;
};


#ifndef _WIN64
typedef System::DynamicArray<TTablespaceDumpLocation> TTablespaceDumpLocations;
#else /* _WIN64 */
typedef System::TArray__1<TTablespaceDumpLocation> TTablespaceDumpLocations;
#endif /* _WIN64 */

class PASCALIMPLEMENTATION TIBBackupService : public TIBBackupRestoreService
{
	typedef TIBBackupRestoreService inherited;
	
private:
	System::UnicodeString FDatabaseName;
	TBackupOptions FOptions;
	System::Classes::TStrings* FBackupFile;
	int FBlockingFactor;
	System::Classes::TStrings* FExcludeTablespaces;
	System::Classes::TStrings* FIncludeTablespaces;
	void __fastcall SetBackupFile(System::Classes::TStrings* const Value);
#ifndef _WIN64
	virtual bool __fastcall GenerateCustomSPB(int SPBVal, System::UnicodeString Param_Value, System::DynamicArray<System::Byte> &SPB, short &SPBLength, int &SPBPos);
#else /* _WIN64 */
	virtual bool __fastcall GenerateCustomSPB(int SPBVal, System::UnicodeString Param_Value, System::TArray__1<System::Byte> &SPB, short &SPBLength, int &SPBPos);
#endif /* _WIN64 */
	HIDESBASE void __fastcall SetExcludeTablespaces(System::Classes::TStrings* const Value);
	HIDESBASE void __fastcall SetIncludeTablespaces(System::Classes::TStrings* const Value);
	
protected:
	virtual void __fastcall SetServiceStartOptions();
	Ibx::Ibdatabase::TIBDatabase* __fastcall BuildIBDatabase();
	
public:
	__fastcall virtual TIBBackupService(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBBackupService();
#ifndef _WIN64
	void __fastcall OnlineDump(bool Overwrite, System::DynamicArray<TTablespaceDumpLocation> DumpLocations = System::DynamicArray<TTablespaceDumpLocation>());
	void __fastcall GetKnownDumps(System::DynamicArray<TTablespaceDumpLocation> &DumpLocations);
	void __fastcall GetTablespacesForDump(const int FileSetID, System::DynamicArray<TTablespaceDumpLocation> &TablespaceLocations);
#else /* _WIN64 */
	void __fastcall OnlineDump(bool Overwrite, System::TArray__1<TTablespaceDumpLocation> DumpLocations = System::TArray__1<TTablespaceDumpLocation>());
	void __fastcall GetKnownDumps(System::TArray__1<TTablespaceDumpLocation> &DumpLocations);
	void __fastcall GetTablespacesForDump(const int FileSetID, System::TArray__1<TTablespaceDumpLocation> &TablespaceLocations);
#endif /* _WIN64 */
	void __fastcall ArchiveDatabase();
	void __fastcall ArchiveJournal();
	
__published:
	__property System::Classes::TStrings* BackupFile = {read=FBackupFile, write=SetBackupFile};
	__property int BlockingFactor = {read=FBlockingFactor, write=FBlockingFactor, nodefault};
	__property System::UnicodeString DatabaseName = {read=FDatabaseName, write=FDatabaseName};
	__property TBackupOptions Options = {read=FOptions, write=FOptions, nodefault};
	__property PreAllocate;
	__property EncryptName = {default=0};
	__property EncryptPassword = {default=0};
	__property System::Classes::TStrings* ExcludeTablespaces = {read=FExcludeTablespaces, write=SetExcludeTablespaces};
	__property System::Classes::TStrings* IncludeTablespaces = {read=FIncludeTablespaces, write=SetIncludeTablespaces};
};


enum DECLSPEC_DENUM TRestoreOption : unsigned char { DeactivateIndexes, NoShadow, NoValidityCheck, OneRelationAtATime, Replace, CreateNewDB, UseAllSpace, ValidationCheck, MetaOnlyRestore };

typedef System::Set<TRestoreOption, TRestoreOption::DeactivateIndexes, TRestoreOption::MetaOnlyRestore> TRestoreOptions;

enum DECLSPEC_DENUM TRestoreType : unsigned char { rtDatabase, rtTablespace };

struct DECLSPEC_DRECORD TIBTablespaceInfo
{
public:
	System::UnicodeString Name;
	System::UnicodeString Location;
};


#ifndef _WIN64
typedef System::DynamicArray<TIBTablespaceInfo> TIBTablespaceInfos;
#else /* _WIN64 */
typedef System::TArray__1<TIBTablespaceInfo> TIBTablespaceInfos;
#endif /* _WIN64 */

struct DECLSPEC_DRECORD TIBTablespaceStruct
{
public:
	System::UnicodeString FileName;
	TRestoreType RestoreType;
#ifndef _WIN64
	System::DynamicArray<TIBTablespaceInfo> Infos;
#else /* _WIN64 */
	System::TArray__1<TIBTablespaceInfo> Infos;
#endif /* _WIN64 */
};


class PASCALIMPLEMENTATION TIBRestoreService : public TIBBackupRestoreService
{
	typedef TIBBackupRestoreService inherited;
	
private:
	System::Classes::TStrings* FDatabaseName;
	System::Classes::TStrings* FBackupFile;
	TRestoreOptions FOptions;
	int FPageSize;
	int FPageBuffers;
	System::UnicodeString FEUAUserName;
	System::UnicodeString FEUAPassword;
	Ibx::Ibdatabaseinfo::TIBWriteMode FWriteMode;
	System::UnicodeString FDecryptPassword;
	bool FReadOnly;
	int FODSMajorVersion;
	__int64 FStartingTransactionID;
	TRestoreType FRestoreType;
	void __fastcall SetBackupFile(System::Classes::TStrings* const Value);
	void __fastcall SetDatabaseName(System::Classes::TStrings* const Value);
	void __fastcall SetODSMajorVersion(const int Value);
	void __fastcall RecoverArchive(System::UnicodeString ArchiveDBName, System::UnicodeString RestoredDBName, System::UnicodeString RestoreUntil)/* overload */;
	TIBTablespaceStruct __fastcall ParseTablespaceInfo(System::Classes::TStrings* sl);
	
protected:
	virtual void __fastcall SetServiceStartOptions();
	
public:
	__fastcall virtual TIBRestoreService(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBRestoreService();
	void __fastcall RecoverArchive(System::UnicodeString ArchiveDBName, System::UnicodeString RestoredDBName)/* overload */;
	void __fastcall RecoverArchive(System::UnicodeString ArchiveDBName, System::UnicodeString RestoredDBName, System::TDateTime RestoreUntil)/* overload */;
	TIBTablespaceStruct __fastcall TablespaceInfoFromFile(System::UnicodeString ABackupFile);
	__property __int64 StartingTransactionID = {read=FStartingTransactionID, write=FStartingTransactionID};
	
__published:
	__property System::Classes::TStrings* DatabaseName = {read=FDatabaseName, write=SetDatabaseName};
	__property System::Classes::TStrings* BackupFile = {read=FBackupFile, write=SetBackupFile};
	__property int PageSize = {read=FPageSize, write=FPageSize, default=4096};
	__property int PageBuffers = {read=FPageBuffers, write=FPageBuffers, nodefault};
	__property TRestoreOptions Options = {read=FOptions, write=FOptions, default=32};
	__property System::UnicodeString EUAUserName = {read=FEUAUserName, write=FEUAUserName};
	__property System::UnicodeString EUAPassword = {read=FEUAPassword, write=FEUAPassword};
	__property Ibx::Ibdatabaseinfo::TIBWriteMode WriteMode = {read=FWriteMode, write=FWriteMode, default=3};
	__property EncryptPassword = {default=0};
	__property PreAllocate;
	__property System::UnicodeString DecryptPassword = {read=FDecryptPassword, write=FDecryptPassword};
	__property bool ReadOnly = {read=FReadOnly, write=FReadOnly, nodefault};
	__property int ODSMajorVersion = {read=FODSMajorVersion, write=SetODSMajorVersion, nodefault};
	__property TRestoreType RestoreType = {read=FRestoreType, write=FRestoreType, nodefault};
};


enum DECLSPEC_DENUM TValidateOption : unsigned char { LimboTransactions, CheckDB, IgnoreChecksum, KillShadows, MendDB, SweepDB, ValidateDB, ValidateFull };

typedef System::Set<TValidateOption, TValidateOption::LimboTransactions, TValidateOption::ValidateFull> TValidateOptions;

enum DECLSPEC_DENUM TTransactionGlobalAction : unsigned char { CommitGlobal, RollbackGlobal, RecoverTwoPhaseGlobal, NoGlobalAction };

enum DECLSPEC_DENUM TTransactionState : unsigned char { LimboState, CommitState, RollbackState, UnknownState };

enum DECLSPEC_DENUM TTransactionAdvise : unsigned char { CommitAdvise, RollbackAdvise, UnknownAdvise };

enum DECLSPEC_DENUM TTransactionAction : unsigned char { CommitAction, RollbackAction };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TLimboTransactionInfo : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	bool MultiDatabase;
	int ID;
	System::UnicodeString HostSite;
	System::UnicodeString RemoteSite;
	System::UnicodeString RemoteDatabasePath;
	TTransactionState State;
	TTransactionAdvise Advise;
	TTransactionAction Action;
public:
	/* TObject.Create */ inline __fastcall TLimboTransactionInfo() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TLimboTransactionInfo() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::DynamicArray<TLimboTransactionInfo*> TLimboTransactionInfos;

class PASCALIMPLEMENTATION TIBValidationService : public TIBControlAndQueryService
{
	typedef TIBControlAndQueryService inherited;
	
private:
	System::UnicodeString FDatabaseName;
	TValidateOptions FOptions;
	TLimboTransactionInfos FLimboTransactionInfo;
	TTransactionGlobalAction FGlobalAction;
	void __fastcall SetDatabaseName(const System::UnicodeString Value);
	TLimboTransactionInfo* __fastcall GetLimboTransactionInfo(int index);
	int __fastcall GetLimboTransactionInfoCount();
	
protected:
	virtual void __fastcall SetServiceStartOptions();
	
public:
	__fastcall virtual TIBValidationService(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBValidationService();
	void __fastcall FetchLimboTransactionInfo();
	void __fastcall FixLimboTransactionErrors();
	__property TLimboTransactionInfo* LimboTransactionInfo[int Index] = {read=GetLimboTransactionInfo};
	__property int LimboTransactionInfoCount = {read=GetLimboTransactionInfoCount, nodefault};
	__property TLimboTransactionInfos LimboTransactionInfos = {read=FLimboTransactionInfo};
	
__published:
	__property System::UnicodeString DatabaseName = {read=FDatabaseName, write=SetDatabaseName};
	__property TValidateOptions Options = {read=FOptions, write=FOptions, nodefault};
	__property TTransactionGlobalAction GlobalAction = {read=FGlobalAction, write=FGlobalAction, nodefault};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TUserInfo : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::UnicodeString UserName;
	System::UnicodeString FirstName;
	System::UnicodeString MiddleName;
	System::UnicodeString LastName;
	int GroupID;
	int UserID;
	System::UnicodeString GroupName;
	System::UnicodeString SystemUserName;
	System::UnicodeString DefaultRole;
	System::UnicodeString Description;
	bool ActiveUser;
public:
	/* TObject.Create */ inline __fastcall TUserInfo() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TUserInfo() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::DynamicArray<TUserInfo*> TUserInfos;

enum DECLSPEC_DENUM TSecurityAction : unsigned char { ActionAddUser, ActionDeleteUser, ActionModifyUser, ActionDisplayUser };

enum DECLSPEC_DENUM TSecurityModifyParam : unsigned char { ModifyFirstName, ModifyMiddleName, ModifyLastName, ModifyUserId, ModifyGroupId, ModifyPassword, ModifySystemUserName, ModifyGroupName, ModifyDefaultRole, ModifyDescription, ModifyActiveUser };

typedef System::Set<TSecurityModifyParam, TSecurityModifyParam::ModifyFirstName, TSecurityModifyParam::ModifyActiveUser> TSecurityModifyParams;

class PASCALIMPLEMENTATION TIBSecurityService : public TIBControlAndQueryService
{
	typedef TIBControlAndQueryService inherited;
	
private:
	int FUserID;
	int FGroupID;
	System::UnicodeString FFirstName;
	System::UnicodeString FUserName;
	System::UnicodeString FPassword;
	System::UnicodeString FSQLRole;
	System::UnicodeString FLastName;
	System::UnicodeString FMiddleName;
	TUserInfos FUserInfo;
	TSecurityAction FSecurityAction;
	TSecurityModifyParams FModifyParams;
	System::UnicodeString FDefaultRole;
	System::UnicodeString FUserDatabase;
	System::UnicodeString FSystemUserName;
	System::UnicodeString FGroupName;
	System::UnicodeString FDescription;
	bool FActiveUser;
	void __fastcall ClearParams();
	void __fastcall SetSecurityAction(TSecurityAction Value);
	void __fastcall SetFirstName(System::UnicodeString Value);
	void __fastcall SetMiddleName(System::UnicodeString Value);
	void __fastcall SetLastName(System::UnicodeString Value);
	void __fastcall SetPassword(System::UnicodeString Value);
	void __fastcall SetUserId(int Value);
	void __fastcall SetGroupId(int Value);
	void __fastcall FetchUserInfo(System::UnicodeString UserName = System::UnicodeString());
	TUserInfo* __fastcall GetUserInfo(int Index);
	int __fastcall GetUserInfoCount();
	void __fastcall SetDefaultRole(const System::UnicodeString Value);
	void __fastcall SetSystemUserName(const System::UnicodeString Value);
	void __fastcall SetGroupName(const System::UnicodeString Value);
	void __fastcall SetDescription(const System::UnicodeString Value);
	void __fastcall SetActiveUser(const bool Value);
	
protected:
	virtual void __fastcall Loaded();
	virtual void __fastcall SetServiceStartOptions();
	void __fastcall ExecuteSQL(System::UnicodeString SQL);
	
public:
	__fastcall virtual TIBSecurityService(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBSecurityService();
	void __fastcall DisplayUsers();
	void __fastcall DisplayUser(System::UnicodeString UserName);
	void __fastcall AddUser();
	void __fastcall DeleteUser();
	void __fastcall ModifyUser();
	void __fastcall EnableEUA(bool Value);
	void __fastcall SuspendEUA(bool Value);
	void __fastcall CreateSYSDSOUser(System::UnicodeString Password = System::UnicodeString());
	void __fastcall ClearUser();
	__property TUserInfo* UserInfo[int Index] = {read=GetUserInfo};
	__property int UserInfoCount = {read=GetUserInfoCount, nodefault};
	__property TUserInfos UserInfos = {read=FUserInfo};
	
__published:
	__property TSecurityAction SecurityAction = {read=FSecurityAction, write=SetSecurityAction, default=0};
	__property System::UnicodeString SQLRole = {read=FSQLRole, write=FSQLRole};
	__property System::UnicodeString UserName = {read=FUserName, write=FUserName};
	__property System::UnicodeString SystemUserName = {read=FSystemUserName, write=SetSystemUserName};
	__property System::UnicodeString FirstName = {read=FFirstName, write=SetFirstName};
	__property System::UnicodeString MiddleName = {read=FMiddleName, write=SetMiddleName};
	__property System::UnicodeString LastName = {read=FLastName, write=SetLastName};
	__property int UserID = {read=FUserID, write=SetUserId, default=0};
	__property int GroupID = {read=FGroupID, write=SetGroupId, default=0};
	__property System::UnicodeString GroupName = {read=FGroupName, write=SetGroupName};
	__property System::UnicodeString Password = {read=FPassword, write=SetPassword};
	__property System::UnicodeString DefaultRole = {read=FDefaultRole, write=SetDefaultRole};
	__property System::UnicodeString Description = {read=FDescription, write=SetDescription};
	__property System::UnicodeString UserDatabase = {read=FUserDatabase, write=FUserDatabase};
	__property bool ActiveUser = {read=FActiveUser, write=SetActiveUser, default=0};
};


//-- var, const, procedure ---------------------------------------------------
static const System::Word DefaultBufferSize = System::Word(0x7d00);
#define SPBPrefix L"isc_spb_"
}	/* namespace Ibservices */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBSERVICES)
using namespace Ibx::Ibservices;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbservicesHPP
