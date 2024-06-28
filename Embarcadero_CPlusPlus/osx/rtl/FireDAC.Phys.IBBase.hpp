// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.IBBase.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_IbbaseHPP
#define Firedac_Phys_IbbaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.SQLGenerator.hpp>
#include <FireDAC.Phys.IBCli.hpp>
#include <FireDAC.Phys.IBWrapper.hpp>
#include <FireDAC.Phys.IBMeta.hpp>
#include <FireDAC.Phys.IBDef.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Ibbase
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysIBBaseDriverLink;
class DELPHICLASS TFDIBService;
class DELPHICLASS TFDIBBackup;
class DELPHICLASS TFDIBRestore;
class DELPHICLASS TFDIBValidate;
class DELPHICLASS TFDIBSecurity;
class DELPHICLASS TFDIBConfig;
class DELPHICLASS TFDIBInfo;
class DELPHICLASS TFDPhysIBDriverBase;
class DELPHICLASS TFDPhysIBConnectionBase;
class DELPHICLASS TFDPhysIBTransactionBase;
class DELPHICLASS TFDPhysIBEventAlerterBase;
struct TFDIBColInfoRec;
struct TFDIBParInfoRec;
class DELPHICLASS TFDPhysIBCommandBase;
//-- type declarations -------------------------------------------------------
typedef System::StaticArray<System::PPointer, 2> TFDPhysIBCliHandles;

typedef TFDPhysIBCliHandles *PFDPhysIBCliHandles;

class PASCALIMPLEMENTATION TFDPhysIBBaseDriverLink : public Firedac::Phys::TFDPhysDriverLink
{
	typedef Firedac::Phys::TFDPhysDriverLink inherited;
	
private:
	bool FThreadSafe;
	
protected:
	virtual bool __fastcall IsConfigured();
	virtual void __fastcall ApplyTo(const Firedac::Stan::Intf::_di_IFDStanDefinition AParams);
	
__published:
	__property bool ThreadSafe = {read=FThreadSafe, write=FThreadSafe, default=0};
public:
	/* TFDPhysDriverLink.Create */ inline __fastcall virtual TFDPhysIBBaseDriverLink(System::Classes::TComponent* AOwner) : Firedac::Phys::TFDPhysDriverLink(AOwner) { }
	/* TFDPhysDriverLink.Destroy */ inline __fastcall virtual ~TFDPhysIBBaseDriverLink() { }
	
};


class PASCALIMPLEMENTATION TFDIBService : public Firedac::Phys::TFDPhysDriverService
{
	typedef Firedac::Phys::TFDPhysDriverService inherited;
	
private:
#ifndef __x86_64__
	unsigned FConnectTimeout;
	unsigned FQueryTimeout;
#else /* __x86_64__ */
	unsigned long FConnectTimeout;
	unsigned long FQueryTimeout;
#endif /* __x86_64__ */
	Firedac::Phys::Ibwrapper::TIBProtocol FProtocol;
	System::UnicodeString FPassword;
	System::UnicodeString FSEPassword;
	System::UnicodeString FHost;
	int FPort;
	System::UnicodeString FUserName;
	Firedac::Phys::TFDPhysServiceProgressEvent FOnProgress;
	System::UnicodeString FSqlRoleName;
	System::UnicodeString FInstanceName;
	TFDPhysIBBaseDriverLink* __fastcall GetDriverLink();
	HIDESBASE void __fastcall SetDriverLink(TFDPhysIBBaseDriverLink* const AValue);
	void __fastcall SetHost(const System::UnicodeString AValue);
	
protected:
	virtual void __fastcall InternalExecute();
	virtual Firedac::Phys::Ibwrapper::TIBService* __fastcall CreateService(Firedac::Phys::Ibwrapper::TIBEnv* AEnv) = 0 ;
	virtual void __fastcall SetupService(Firedac::Phys::Ibwrapper::TIBService* AService);
	virtual void __fastcall QueryService(Firedac::Phys::Ibwrapper::TIBService* AService);
	virtual void __fastcall DeleteService(Firedac::Phys::Ibwrapper::TIBService* &AService);
	virtual void __fastcall DoProgress(Firedac::Phys::Ibwrapper::TIBService* AService, const System::UnicodeString AMessage);
	Firedac::Phys::Intf::_di_IFDPhysConnection __fastcall GetConnection(const System::UnicodeString ADatabase);
	Firedac::Dats::TFDDatSTable* __fastcall ExecSQL(const System::UnicodeString ADatabase, const System::UnicodeString ASQL)/* overload */;
	Firedac::Dats::TFDDatSTable* __fastcall ExecSQL(const Firedac::Phys::Intf::_di_IFDPhysConnection AConn, const System::UnicodeString ASQL)/* overload */;
	
__published:
	__property TFDPhysIBBaseDriverLink* DriverLink = {read=GetDriverLink, write=SetDriverLink};
	__property Firedac::Phys::Ibwrapper::TIBProtocol Protocol = {read=FProtocol, write=FProtocol, default=0};
	__property System::UnicodeString Host = {read=FHost, write=SetHost};
	__property int Port = {read=FPort, write=FPort, default=0};
	__property System::UnicodeString InstanceName = {read=FInstanceName, write=FInstanceName};
	__property System::UnicodeString UserName = {read=FUserName, write=FUserName};
	__property System::UnicodeString Password = {read=FPassword, write=FPassword};
	__property System::UnicodeString SqlRoleName = {read=FSqlRoleName, write=FSqlRoleName};
#ifndef __x86_64__
	__property unsigned ConnectTimeout = {read=FConnectTimeout, write=FConnectTimeout, default=0};
	__property unsigned QueryTimeout = {read=FQueryTimeout, write=FQueryTimeout, default=0};
#else /* __x86_64__ */
	__property unsigned long ConnectTimeout = {read=FConnectTimeout, write=FConnectTimeout, default=0};
	__property unsigned long QueryTimeout = {read=FQueryTimeout, write=FQueryTimeout, default=0};
#endif /* __x86_64__ */
	__property Firedac::Phys::TFDPhysServiceProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};
	__property System::UnicodeString SEPassword = {read=FSEPassword, write=FSEPassword};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDIBService() { }
	
public:
	/* TComponent.Create */ inline __fastcall virtual TFDIBService(System::Classes::TComponent* AOwner) : Firedac::Phys::TFDPhysDriverService(AOwner) { }
	
};


class PASCALIMPLEMENTATION TFDIBBackup : public TFDIBService
{
	typedef TFDIBService inherited;
	
private:
	Firedac::Phys::Ibwrapper::TIBBackupMode FMode;
	System::Classes::TStrings* FBackupFiles;
	bool FVerbose;
	System::UnicodeString FDatabase;
	Firedac::Phys::Ibwrapper::TIBBackupOptions FOptions;
	System::UnicodeString FEncryptKeyName;
	Firedac::Phys::Ibwrapper::TIBBackupStatistics FStatistics;
	System::UnicodeString FSkipData;
	void __fastcall SetBackupFiles(System::Classes::TStrings* const AValue);
	
protected:
	virtual Firedac::Phys::Ibwrapper::TIBService* __fastcall CreateService(Firedac::Phys::Ibwrapper::TIBEnv* AEnv);
	virtual void __fastcall SetupService(Firedac::Phys::Ibwrapper::TIBService* AService);
	
public:
	__fastcall virtual TFDIBBackup(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDIBBackup();
	void __fastcall Backup();
	void __fastcall ArchiveDatabase();
	void __fastcall ArchiveJournals();
	
__published:
	__property System::UnicodeString Database = {read=FDatabase, write=FDatabase};
	__property System::Classes::TStrings* BackupFiles = {read=FBackupFiles, write=SetBackupFiles};
	__property bool Verbose = {read=FVerbose, write=FVerbose, default=0};
	__property Firedac::Phys::Ibwrapper::TIBBackupOptions Options = {read=FOptions, write=FOptions, default=0};
	__property System::UnicodeString EncryptKeyName = {read=FEncryptKeyName, write=FEncryptKeyName};
	__property Firedac::Phys::Ibwrapper::TIBBackupStatistics Statistics = {read=FStatistics, write=FStatistics, default=0};
	__property System::UnicodeString SkipData = {read=FSkipData, write=FSkipData};
};


class PASCALIMPLEMENTATION TFDIBRestore : public TFDIBService
{
	typedef TFDIBService inherited;
	
private:
	Firedac::Phys::Ibwrapper::TIBRestoreMode FMode;
	System::Classes::TStrings* FBackupFiles;
	bool FVerbose;
#ifndef __x86_64__
	unsigned FPageSize;
#else /* __x86_64__ */
	unsigned long FPageSize;
#endif /* __x86_64__ */
	System::UnicodeString FDatabase;
	Firedac::Phys::Ibwrapper::TIBRestoreOptions FOptions;
#ifndef __x86_64__
	unsigned FPageBuffers;
#else /* __x86_64__ */
	unsigned long FPageBuffers;
#endif /* __x86_64__ */
	System::UnicodeString FEUAPassword;
	System::UnicodeString FEUAUserName;
	System::UnicodeString FFixCharSet;
	System::UnicodeString FDecryptPassword;
	System::TDateTime FUntilTimestamp;
	Firedac::Phys::Ibwrapper::TIBBackupStatistics FStatistics;
	void __fastcall SetBackupFiles(System::Classes::TStrings* const AValue);
	
protected:
	virtual Firedac::Phys::Ibwrapper::TIBService* __fastcall CreateService(Firedac::Phys::Ibwrapper::TIBEnv* AEnv);
	virtual void __fastcall SetupService(Firedac::Phys::Ibwrapper::TIBService* AService);
	
public:
	__fastcall virtual TFDIBRestore(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDIBRestore();
	void __fastcall Restore();
	void __fastcall ArchiveRecover();
	
__published:
	__property System::UnicodeString Database = {read=FDatabase, write=FDatabase};
	__property System::Classes::TStrings* BackupFiles = {read=FBackupFiles, write=SetBackupFiles};
	__property bool Verbose = {read=FVerbose, write=FVerbose, default=0};
	__property Firedac::Phys::Ibwrapper::TIBRestoreOptions Options = {read=FOptions, write=FOptions, default=0};
#ifndef __x86_64__
	__property unsigned PageSize = {read=FPageSize, write=FPageSize, default=0};
	__property unsigned PageBuffers = {read=FPageBuffers, write=FPageBuffers, default=0};
#else /* __x86_64__ */
	__property unsigned long PageSize = {read=FPageSize, write=FPageSize, default=0};
	__property unsigned long PageBuffers = {read=FPageBuffers, write=FPageBuffers, default=0};
#endif /* __x86_64__ */
	__property System::UnicodeString FixCharSet = {read=FFixCharSet, write=FFixCharSet};
	__property System::UnicodeString EUAUserName = {read=FEUAUserName, write=FEUAUserName};
	__property System::UnicodeString EUAPassword = {read=FEUAPassword, write=FEUAPassword};
	__property System::UnicodeString DecryptPassword = {read=FDecryptPassword, write=FDecryptPassword};
	__property System::TDateTime UntilTimestamp = {read=FUntilTimestamp, write=FUntilTimestamp};
	__property Firedac::Phys::Ibwrapper::TIBBackupStatistics Statistics = {read=FStatistics, write=FStatistics, default=0};
};


class PASCALIMPLEMENTATION TFDIBValidate : public TFDIBService
{
	typedef TFDIBService inherited;
	
private:
	Firedac::Phys::Ibwrapper::TIBRepairMode FMode;
	System::UnicodeString FDatabase;
	Firedac::Phys::Ibwrapper::TIBRepairOptions FOptions;
	
protected:
	virtual Firedac::Phys::Ibwrapper::TIBService* __fastcall CreateService(Firedac::Phys::Ibwrapper::TIBEnv* AEnv);
	virtual void __fastcall SetupService(Firedac::Phys::Ibwrapper::TIBService* AService);
	
public:
	void __fastcall CheckOnly();
	void __fastcall Repair();
	void __fastcall Sweep();
	void __fastcall Analyze(const System::UnicodeString ATable = System::UnicodeString(), const System::UnicodeString AIndex = System::UnicodeString());
	
__published:
	__property System::UnicodeString Database = {read=FDatabase, write=FDatabase};
	__property Firedac::Phys::Ibwrapper::TIBRepairOptions Options = {read=FOptions, write=FOptions, default=0};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDIBValidate() { }
	
public:
	/* TComponent.Create */ inline __fastcall virtual TFDIBValidate(System::Classes::TComponent* AOwner) : TFDIBService(AOwner) { }
	
};


enum DECLSPEC_DENUM TIBEncryptionType : unsigned int { ecDES, ecAES };

class PASCALIMPLEMENTATION TFDIBSecurity : public TFDIBService
{
	typedef TFDIBService inherited;
	
	
private:
	typedef System::StaticArray<System::UnicodeString, 9> _TFDIBSecurity__1;
	
	
private:
	Firedac::Phys::Ibwrapper::TIBSecurityAction FAction;
	_TFDIBSecurity__1 FValues;
	Firedac::Phys::Ibwrapper::TIBSecurityValues FModified;
	Firedac::Dats::TFDDatSTable* FUsers;
	System::UnicodeString FEUADatabase;
	System::UnicodeString FKeyName;
	int __fastcall GetInt(const int AIndex);
	System::UnicodeString __fastcall GetStr(const int AIndex);
	void __fastcall SetInt(const int AIndex, const int AValue);
	void __fastcall SetStr(const int AIndex, const System::UnicodeString AValue);
	bool __fastcall IsStored(const int AIndex);
	bool __fastcall GetEUAActive();
	void __fastcall SetEUAActive(const bool AValue);
	bool __fastcall GetDBEncrypted();
	void __fastcall SetDBEncrypted(const bool AValue);
	
protected:
	virtual Firedac::Phys::Ibwrapper::TIBService* __fastcall CreateService(Firedac::Phys::Ibwrapper::TIBEnv* AEnv);
	virtual void __fastcall SetupService(Firedac::Phys::Ibwrapper::TIBService* AService);
	virtual void __fastcall QueryService(Firedac::Phys::Ibwrapper::TIBService* AService);
	virtual void __fastcall DeleteService(Firedac::Phys::Ibwrapper::TIBService* &AService);
	
public:
	__fastcall virtual ~TFDIBSecurity();
	void __fastcall AddUser();
	void __fastcall DeleteUser();
	void __fastcall ModifyUser();
	void __fastcall DisplayUser();
	void __fastcall DisplayUsers();
	__property Firedac::Dats::TFDDatSTable* Users = {read=FUsers};
	void __fastcall CreateSYSDSO(const System::UnicodeString APassword);
	void __fastcall CreateSEPassword(const System::UnicodeString APassword, bool AExternal);
	void __fastcall CreateKey(bool ADefault, TIBEncryptionType AType, int ALength, const System::UnicodeString APassword, bool ARandomVect, bool ARandomPad, const System::UnicodeString ADesc);
	void __fastcall DropKey(bool ACascade);
	void __fastcall GrantKey(const System::UnicodeString AUserName);
	void __fastcall RevokeKey(const System::UnicodeString AUserName);
	void __fastcall EncryptColumn(const System::UnicodeString ATableName, const System::UnicodeString AColumnName);
	void __fastcall DecryptColumn(const System::UnicodeString ATableName, const System::UnicodeString AColumnName);
	void __fastcall SetEncryption(const System::UnicodeString ADSOPassword, const System::UnicodeString ASEPassword, bool AAlwaysUseSEP, TIBEncryptionType AType, int ALength);
	void __fastcall RemoveEncryption(const System::UnicodeString ADSOPassword);
	void __fastcall ChangeEncryption(const System::UnicodeString ADSOPassword, const System::UnicodeString ASEPassword, const System::UnicodeString ANewSEPassword, bool ANewAlwaysUseSEP);
	__property bool EUAActive = {read=GetEUAActive, write=SetEUAActive, nodefault};
	__property bool DBEncrypted = {read=GetDBEncrypted, write=SetDBEncrypted, nodefault};
	
__published:
	__property Firedac::Phys::Ibwrapper::TIBSecurityValues Modified = {read=FModified, write=FModified, default=0};
	__property System::UnicodeString AUserName = {read=GetStr, write=SetStr, stored=IsStored, index=0};
	__property System::UnicodeString APassword = {read=GetStr, write=SetStr, stored=IsStored, index=1};
	__property System::UnicodeString AFirstName = {read=GetStr, write=SetStr, stored=IsStored, index=2};
	__property System::UnicodeString AMiddleName = {read=GetStr, write=SetStr, stored=IsStored, index=3};
	__property System::UnicodeString ALastName = {read=GetStr, write=SetStr, stored=IsStored, index=4};
	__property int AUserID = {read=GetInt, write=SetInt, stored=IsStored, index=5, nodefault};
	__property int AGroupID = {read=GetInt, write=SetInt, stored=IsStored, index=6, nodefault};
	__property System::UnicodeString AGroupName = {read=GetStr, write=SetStr, stored=IsStored, index=7};
	__property System::UnicodeString ARoleName = {read=GetStr, write=SetStr, stored=IsStored, index=8};
	__property System::UnicodeString EUADatabase = {read=FEUADatabase, write=FEUADatabase};
	__property System::UnicodeString KeyName = {read=FKeyName, write=FKeyName};
public:
	/* TComponent.Create */ inline __fastcall virtual TFDIBSecurity(System::Classes::TComponent* AOwner) : TFDIBService(AOwner) { }
	
};


class PASCALIMPLEMENTATION TFDIBConfig : public TFDIBService
{
	typedef TFDIBService inherited;
	
	
private:
	enum DECLSPEC_DENUM TMode : unsigned int { cmPageBuffers, cmSQLDialect, cmSweepInterval, cmReserveSpace, cmWriteMode, cmAccessMode, cmShutdown, cmOnline, cmActivateShadow, cmArchiveDumps, cmArchiveSweep };
	
	
private:
	System::UnicodeString FDatabase;
	TMode FMode;
#ifndef __x86_64__
	unsigned FValue;
#else /* __x86_64__ */
	unsigned long FValue;
#endif /* __x86_64__ */
	Firedac::Phys::Ibwrapper::TIBShutdownMode FShutdownMode;
	
protected:
	virtual Firedac::Phys::Ibwrapper::TIBService* __fastcall CreateService(Firedac::Phys::Ibwrapper::TIBEnv* AEnv);
	virtual void __fastcall SetupService(Firedac::Phys::Ibwrapper::TIBService* AService);
	
public:
#ifndef __x86_64__
	void __fastcall SetPageBuffers(const unsigned AValue);
	void __fastcall SetSQLDialect(const unsigned AValue);
	void __fastcall SetSweepInterval(const unsigned AValue);
#else /* __x86_64__ */
	void __fastcall SetPageBuffers(const unsigned long AValue);
	void __fastcall SetSQLDialect(const unsigned long AValue);
	void __fastcall SetSweepInterval(const unsigned long AValue);
#endif /* __x86_64__ */
	void __fastcall SetReserveSpace(const Firedac::Phys::Ibwrapper::TIBReserveSpace AValue);
	void __fastcall SetWriteMode(const Firedac::Phys::Ibwrapper::TIBWriteMode AValue);
	void __fastcall SetAccessMode(const Firedac::Phys::Ibwrapper::TIBAccessMode AValue);
#ifndef __x86_64__
	void __fastcall SetArchiveDumps(const unsigned AValue);
	void __fastcall SetArchiveSweep(const unsigned AValue);
	void __fastcall ShutdownDB(Firedac::Phys::Ibwrapper::TIBShutdownMode AMode, unsigned ATimeout);
#else /* __x86_64__ */
	void __fastcall SetArchiveDumps(const unsigned long AValue);
	void __fastcall SetArchiveSweep(const unsigned long AValue);
	void __fastcall ShutdownDB(Firedac::Phys::Ibwrapper::TIBShutdownMode AMode, unsigned long ATimeout);
#endif /* __x86_64__ */
	void __fastcall OnlineDB();
	void __fastcall ActivateShadow();
	
__published:
	__property System::UnicodeString Database = {read=FDatabase, write=FDatabase};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDIBConfig() { }
	
public:
	/* TComponent.Create */ inline __fastcall virtual TFDIBConfig(System::Classes::TComponent* AOwner) : TFDIBService(AOwner) { }
	
};


class PASCALIMPLEMENTATION TFDIBInfo : public TFDIBService
{
	typedef TFDIBService inherited;
	
	
private:
	enum DECLSPEC_DENUM TMode : unsigned int { imVersion, imLicense, imConfig, imUsage };
	
	
private:
	TMode FMode;
	void *FpData;
	
protected:
	virtual Firedac::Phys::Ibwrapper::TIBService* __fastcall CreateService(Firedac::Phys::Ibwrapper::TIBEnv* AEnv);
	virtual void __fastcall QueryService(Firedac::Phys::Ibwrapper::TIBService* AService);
	
public:
	void __fastcall GetVersion(/* out */ Firedac::Phys::Ibwrapper::TIBInfo::TVersion &AVersion);
	void __fastcall GetLicense(/* out */ Firedac::Phys::Ibwrapper::TIBInfo::TLicense &ALicenses);
	void __fastcall GetConfig(/* out */ Firedac::Phys::Ibwrapper::TIBInfo::TConfig &AConfig);
	void __fastcall GetUsage(/* out */ Firedac::Phys::Ibwrapper::TIBInfo::TUsage &AUsage);
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDIBInfo() { }
	
public:
	/* TComponent.Create */ inline __fastcall virtual TFDIBInfo(System::Classes::TComponent* AOwner) : TFDIBService(AOwner) { }
	
};


#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION TFDPhysIBDriverBase : public Firedac::Phys::TFDPhysDriver
{
	typedef Firedac::Phys::TFDPhysDriver inherited;
	
protected:
	Firedac::Phys::Ibwrapper::TIBLib* FLib;
	virtual void __fastcall InternalUnload();
	bool __fastcall GetThreadSafe();
	virtual void * __fastcall GetCliObj();
	virtual Firedac::Dats::TFDDatSTable* __fastcall GetConnParams(System::Classes::TStrings* AKeys, Firedac::Dats::TFDDatSTable* AParams);
	
public:
	__fastcall virtual TFDPhysIBDriverBase(Firedac::Phys::TFDPhysManager* AManager, const Firedac::Stan::Intf::_di_IFDStanDefinition ADriverDef);
	__fastcall virtual ~TFDPhysIBDriverBase();
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

class PASCALIMPLEMENTATION TFDPhysIBConnectionBase : public Firedac::Phys::TFDPhysConnection
{
	typedef Firedac::Phys::TFDPhysConnection inherited;
	
private:
	Firedac::Phys::Ibwrapper::TIBEnv* FEnv;
	Firedac::Phys::Ibwrapper::TIBDatabase* FDatabase;
	unsigned __int64 FServerVersion;
	Firedac::Phys::Ibmeta::TFDPhysIBBrand FServerBrand;
	System::Word FDialect;
	System::Types::TEndian FGUIDEndian;
	TFDPhysIBCliHandles FCliHandles;
	void *FSharedTxHandle;
	Firedac::Phys::Intf::_di_IFDPhysTransaction FMetaTransaction;
	bool FExtendedMetadata;
	
protected:
	virtual void __fastcall InternalConnect();
	virtual void __fastcall InternalDisconnect();
	virtual void __fastcall InternalPing();
	virtual Firedac::Phys::TFDPhysTransaction* __fastcall InternalCreateTransaction();
	virtual Firedac::Phys::TFDPhysEventAlerter* __fastcall InternalCreateEvent(const System::UnicodeString AEventKind);
	virtual Firedac::Phys::TFDPhysCommand* __fastcall InternalCreateMetaInfoCommand();
	virtual System::TObject* __fastcall InternalCreateMetadata();
	virtual Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator* __fastcall InternalCreateCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand);
	virtual void __fastcall InternalTracingChanged();
	virtual void __fastcall InternalExecuteDirect(const System::UnicodeString ASQL, Firedac::Phys::TFDPhysTransaction* ATransaction);
	virtual void __fastcall GetItem(int AIndex, /* out */ System::UnicodeString &AName, /* out */ System::Variant &AValue, /* out */ Firedac::Stan::Intf::TFDMoniAdapterItemKind &AKind);
	virtual int __fastcall GetItemCount();
	virtual Firedac::Stan::Error::EFDDBEngineException* __fastcall GetMessages();
	virtual void * __fastcall GetCliObj();
	virtual void * __fastcall InternalGetCliHandle();
	virtual void __fastcall InternalAnalyzeSession(System::Classes::TStrings* AMessages);
	virtual void __fastcall BuildIBConnectParams(System::Classes::TStrings* AParams, const Firedac::Stan::Intf::_di_IFDStanConnectionDef AConnectionDef);
	
public:
	__fastcall virtual TFDPhysIBConnectionBase(Firedac::Phys::TFDPhysDriver* ADriverObj, Firedac::Phys::TFDPhysConnectionHost* AConnHost);
	__fastcall virtual ~TFDPhysIBConnectionBase();
	__property Firedac::Phys::Ibwrapper::TIBEnv* IBEnv = {read=FEnv};
	__property Firedac::Phys::Ibwrapper::TIBDatabase* IBDatabase = {read=FDatabase};
	__property unsigned __int64 ServerVersion = {read=FServerVersion};
	__property Firedac::Phys::Ibmeta::TFDPhysIBBrand ServerBrand = {read=FServerBrand, nodefault};
};


#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION TFDPhysIBTransactionBase : public Firedac::Phys::TFDPhysTransaction
{
	typedef Firedac::Phys::TFDPhysTransaction inherited;
	
private:
	System::Classes::TStrings* FParams;
	Firedac::Phys::Ibwrapper::TIBTransaction* FTransaction;
	TFDPhysIBConnectionBase* __fastcall GetIBConnection();
	
protected:
	virtual int __fastcall GetItemCount();
	virtual void __fastcall GetItem(int AIndex, /* out */ System::UnicodeString &AName, /* out */ System::Variant &AValue, /* out */ Firedac::Stan::Intf::TFDMoniAdapterItemKind &AKind);
#ifndef __x86_64__
	virtual void __fastcall InternalStartTransaction(unsigned AID);
	virtual void __fastcall InternalCommit(unsigned AID);
	virtual void __fastcall InternalRollback(unsigned AID);
#else /* __x86_64__ */
	virtual void __fastcall InternalStartTransaction(unsigned long AID);
	virtual void __fastcall InternalCommit(unsigned long AID);
	virtual void __fastcall InternalRollback(unsigned long AID);
#endif /* __x86_64__ */
	virtual void __fastcall InternalChanged();
	virtual void __fastcall InternalAllocHandle();
	virtual void __fastcall InternalReleaseHandle();
	virtual void __fastcall InternalNotify(Firedac::Phys::TFDPhysTxNotification ANotification, Firedac::Phys::TFDPhysCommand* ACommandObj);
	virtual void * __fastcall GetCliObj();
	
public:
	__property TFDPhysIBConnectionBase* IBConnection = {read=GetIBConnection};
	__property Firedac::Phys::Ibwrapper::TIBTransaction* IBTransaction = {read=FTransaction};
public:
	/* TFDPhysTransaction.Create */ inline __fastcall virtual TFDPhysIBTransactionBase(Firedac::Phys::TFDPhysConnection* AConnection) : Firedac::Phys::TFDPhysTransaction(AConnection) { }
	/* TFDPhysTransaction.Destroy */ inline __fastcall virtual ~TFDPhysIBTransactionBase() { }
	
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION TFDPhysIBEventAlerterBase : public Firedac::Phys::TFDPhysEventAlerter
{
	typedef Firedac::Phys::TFDPhysEventAlerter inherited;
	
private:
	Firedac::Phys::Ibwrapper::TIBEvents* FEvents;
	Firedac::Phys::Intf::_di_IFDPhysConnection FEventsConnection;
	void __fastcall DoFired(Firedac::Phys::Ibwrapper::TIBEvents* AEvents, int ABaseIndex, const Firedac::Phys::Ibcli::TISCEventCounts &ACounts);
	
protected:
	virtual void __fastcall InternalAllocHandle();
	virtual void __fastcall InternalRegister();
	virtual void __fastcall InternalHandle(Firedac::Phys::TFDPhysEventMessage* AEventMessage);
	virtual void __fastcall InternalUnregister();
	virtual void __fastcall InternalReleaseHandle();
	virtual void __fastcall InternalSignal(const System::UnicodeString AEvent, const System::Variant &AArgument);
public:
	/* TFDPhysEventAlerter.Create */ inline __fastcall virtual TFDPhysIBEventAlerterBase(Firedac::Phys::TFDPhysConnection* AConnection, const System::UnicodeString AKind) : Firedac::Phys::TFDPhysEventAlerter(AConnection, AKind) { }
	/* TFDPhysEventAlerter.Destroy */ inline __fastcall virtual ~TFDPhysIBEventAlerterBase() { }
	
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

typedef TFDIBColInfoRec *PFDIBColInfoRec;

struct DECLSPEC_DRECORD TFDIBColInfoRec
{
	
private:
	typedef System::DynamicArray<TFDIBColInfoRec> _TFDIBColInfoRec__1;
	
	
public:
	Firedac::Phys::Ibwrapper::TIBVariable* FVar;
	System::UnicodeString FName;
	System::UnicodeString FOriginTabName;
	System::UnicodeString FOriginColName;
	int FPos;
	short FLen;
	short FPrec;
	short FScale;
	short FSrcSQLDataType;
	short FSrcSQLSubType;
	Firedac::Stan::Intf::TFDDataType FSrcDataType;
	Firedac::Stan::Intf::TFDDataType FDestDataType;
	System::UnicodeString FSrcTypeName;
	Firedac::Stan::Intf::TFDDataAttributes FAttrs;
#ifndef __x86_64__
	unsigned FFDLen;
#else /* __x86_64__ */
	unsigned long FFDLen;
#endif /* __x86_64__ */
	bool FInPK;
	_TFDIBColInfoRec__1 FItemInfos;
};


typedef TFDIBParInfoRec *PFDIBParInfoRec;

struct DECLSPEC_DRECORD TFDIBParInfoRec
{
public:
	Firedac::Phys::Ibwrapper::TIBVariable* FVar;
	int FParamIndex;
	short FLen;
	short FPrec;
	short FScale;
	short FDestSQLDataType;
	short FDestSQLSubType;
	Firedac::Stan::Intf::TFDDataType FDestDataType;
	Firedac::Stan::Intf::TFDDataType FSrcDataType;
	System::UnicodeString FDestTypeName;
#ifndef __x86_64__
	unsigned FFDLen;
#else /* __x86_64__ */
	unsigned long FFDLen;
#endif /* __x86_64__ */
	Data::Db::TFieldType FSrcFieldType;
#ifndef __x86_64__
	unsigned FSrcSize;
#else /* __x86_64__ */
	unsigned long FSrcSize;
#endif /* __x86_64__ */
	int FSrcPrec;
	int FSrcScale;
	Data::Db::TParamType FParamType;
};


#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION TFDPhysIBCommandBase : public Firedac::Phys::TFDPhysCommand
{
	typedef Firedac::Phys::TFDPhysCommand inherited;
	
	
private:
	typedef System::DynamicArray<TFDIBColInfoRec> _TFDPhysIBCommandBase__1;
	
	typedef System::DynamicArray<TFDIBParInfoRec> _TFDPhysIBCommandBase__2;
	
	
private:
	int FColumnIndex;
	TFDIBColInfoRec *FCurrentArrInfo;
	Firedac::Phys::Intf::TFDPhysParsedName FSPParsedName;
	bool FCursorCanceled;
	int FMaxInputPos;
	bool FRetWithOut;
	HIDESBASE TFDPhysIBConnectionBase* __fastcall GetConnection();
	void __fastcall CreateColInfos();
	void __fastcall DestroyColInfos();
	void __fastcall CreateParamInfos(Firedac::Phys::Ibwrapper::TIBVariables* AVars, bool AInput, bool AFB2Batch);
	void __fastcall DestroyParamInfos();
#ifndef __x86_64__
	void __fastcall SQL2FDDataType(short ASQLDataType, short ASQLSubType, short ASQLLen, short ASQLPrec, short ASQLScale, /* out */ Firedac::Stan::Intf::TFDDataType &AType, Firedac::Stan::Intf::TFDDataAttributes &AAttrs, /* out */ unsigned &ALen, /* out */ int &APrec, /* out */ int &AScale, Firedac::Stan::Option::TFDFormatOptions* AFmtOpts);
	void __fastcall FD2SQLDataType(Firedac::Stan::Intf::TFDDataType AType, unsigned ALen, int APrec, int AScale, /* out */ short &ASQLDataType, /* out */ short &ASQLSubType, /* out */ short &ASQLLen, /* out */ short &ASQLPrec, /* out */ short &ASQLScale, Firedac::Stan::Option::TFDFormatOptions* AFmtOpts);
#else /* __x86_64__ */
	void __fastcall SQL2FDDataType(short ASQLDataType, short ASQLSubType, short ASQLLen, short ASQLPrec, short ASQLScale, /* out */ Firedac::Stan::Intf::TFDDataType &AType, Firedac::Stan::Intf::TFDDataAttributes &AAttrs, /* out */ unsigned long &ALen, /* out */ int &APrec, /* out */ int &AScale, Firedac::Stan::Option::TFDFormatOptions* AFmtOpts);
	void __fastcall FD2SQLDataType(Firedac::Stan::Intf::TFDDataType AType, unsigned long ALen, int APrec, int AScale, /* out */ short &ASQLDataType, /* out */ short &ASQLSubType, /* out */ short &ASQLLen, /* out */ short &ASQLPrec, /* out */ short &ASQLScale, Firedac::Stan::Option::TFDFormatOptions* AFmtOpts);
#endif /* __x86_64__ */
	void __fastcall FetchRow(Firedac::Dats::TFDDatSTable* ATable, Firedac::Dats::TFDDatSRow* AParentRow);
	bool __fastcall UseExecDirect();
	bool __fastcall IsReturning();
	void __fastcall CheckColInfos();
	void __fastcall PrepareBase();
	
protected:
	Firedac::Phys::Ibwrapper::TIBStatement* FStmt;
	_TFDPhysIBCommandBase__1 FColInfos;
	_TFDPhysIBCommandBase__2 FParInfos;
	bool FHasIntStreams;
	virtual void __fastcall InternalAbort();
	virtual void __fastcall InternalClose();
#ifndef __x86_64__
	virtual unsigned __fastcall InternalFetchRowSet(Firedac::Dats::TFDDatSTable* ATable, Firedac::Dats::TFDDatSRow* AParentRow, unsigned ARowsetSize);
	virtual bool __fastcall InternalOpen(int &ACount);
#else /* __x86_64__ */
	virtual unsigned long __fastcall InternalFetchRowSet(Firedac::Dats::TFDDatSTable* ATable, Firedac::Dats::TFDDatSRow* AParentRow, unsigned long ARowsetSize);
	virtual bool __fastcall InternalOpen(__int64 &ACount);
#endif /* __x86_64__ */
	virtual bool __fastcall InternalNextRecordSet();
	virtual void __fastcall InternalPrepare();
	virtual bool __fastcall InternalUseStandardMetadata();
	virtual bool __fastcall InternalColInfoStart(Firedac::Phys::TFDPhysDataTableInfo &ATabInfo);
	virtual bool __fastcall InternalColInfoGet(Firedac::Phys::TFDPhysDataColumnInfo &AColInfo);
	virtual void __fastcall InternalCloseStreams();
	virtual void __fastcall InternalUnprepare();
	virtual void * __fastcall GetCliObj();
	virtual int __fastcall GetItemCount();
	virtual void __fastcall GetItem(int AIndex, /* out */ System::UnicodeString &AName, /* out */ System::Variant &AValue, /* out */ Firedac::Stan::Intf::TFDMoniAdapterItemKind &AKind);
	virtual void __fastcall ProcessColumn(Firedac::Dats::TFDDatSTable* ATable, Firedac::Stan::Option::TFDFormatOptions* AFmtOpts, int AColIndex, Firedac::Dats::TFDDatSRow* ARow, PFDIBColInfoRec ApInfo, int ARowIndex, Firedac::Phys::Ibwrapper::TIBUpdateStatus &AUpdates);
	virtual void __fastcall ProcessMetaColumn(Firedac::Dats::TFDDatSTable* ATable, Firedac::Stan::Option::TFDFormatOptions* AFmtOpts, int AColIndex, Firedac::Dats::TFDDatSRow* ARow, PFDIBColInfoRec ApInfo, int ARowIndex);
	virtual bool __fastcall CharLenInBytes();
	void __fastcall SetupStatement(Firedac::Phys::Ibwrapper::TIBStatement* AStmt);
	void __fastcall CheckSPPrepared(Firedac::Phys::Intf::TFDPhysCommandKind ASPUsage);
	void __fastcall CheckParamInfos();
#ifndef __x86_64__
	void __fastcall DoExecute(int ATimes, int AOffset, int &ACount, bool AFlush);
#else /* __x86_64__ */
	void __fastcall DoExecute(int ATimes, int AOffset, __int64 &ACount, bool AFlush);
#endif /* __x86_64__ */
	void __fastcall SetParamValue(Firedac::Stan::Option::TFDFormatOptions* AFmtOpts, Firedac::Stan::Param::TFDParam* AParam, Firedac::Phys::Ibwrapper::TIBVariable* AVar, PFDIBParInfoRec ApInfo, int AVarIndex, int AParIndex);
	void __fastcall GetParamValue(Firedac::Stan::Option::TFDFormatOptions* AFmtOpts, Firedac::Stan::Param::TFDParam* AParam, Firedac::Phys::Ibwrapper::TIBVariable* AVar, PFDIBParInfoRec ApInfo, int AVarIndex, int AParIndex);
	void __fastcall SetParamValues(int ATimes, int AOffset);
	void __fastcall GetParamValues(int ATimes, int AOffset);
	
public:
	__property TFDPhysIBConnectionBase* IBConnection = {read=GetConnection};
	__property Firedac::Phys::Ibwrapper::TIBStatement* IBStatement = {read=FStmt};
public:
	/* TFDPhysCommand.Create */ inline __fastcall TFDPhysIBCommandBase(Firedac::Phys::TFDPhysConnection* AConnection) : Firedac::Phys::TFDPhysCommand(AConnection) { }
	/* TFDPhysCommand.Destroy */ inline __fastcall virtual ~TFDPhysIBCommandBase() { }
	
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibbase */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_IBBASE)
using namespace Firedac::Phys::Ibbase;
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
#endif	// Firedac_Phys_IbbaseHPP
