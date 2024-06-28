// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.SQLite.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_SqliteHPP
#define Firedac_Phys_SqliteHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.SQLiteWrapper.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FireDAC.Phys.SQLite"

namespace Firedac
{
namespace Phys
{
namespace Sqlite
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysSQLiteDriverLink;
class DELPHICLASS TFDSQLiteService;
class DELPHICLASS TFDSQLiteBackup;
class DELPHICLASS TFDSQLiteValidate;
class DELPHICLASS TFDSQLiteSecurity;
class DELPHICLASS TFDSQLiteFunction;
class DELPHICLASS TFDSQLiteCollation;
class DELPHICLASS TFDSQLiteRTree;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysSQLiteDriverLink : public Firedac::Phys::TFDPhysDriverLink
{
	typedef Firedac::Phys::TFDPhysDriverLink inherited;
	
private:
	Firedac::Phys::Sqlitewrapper::TSQLiteEngineLinkage FEngineLinkage;
	
protected:
	virtual System::UnicodeString __fastcall GetBaseDriverID();
	virtual bool __fastcall IsConfigured();
	virtual void __fastcall ApplyTo(const Firedac::Stan::Intf::_di_IFDStanDefinition AParams);
	
__published:
	__property Firedac::Phys::Sqlitewrapper::TSQLiteEngineLinkage EngineLinkage = {read=FEngineLinkage, write=FEngineLinkage, default=0};
public:
	/* TFDPhysDriverLink.Create */ inline __fastcall virtual TFDPhysSQLiteDriverLink(System::Classes::TComponent* AOwner) : Firedac::Phys::TFDPhysDriverLink(AOwner) { }
	/* TFDPhysDriverLink.Destroy */ inline __fastcall virtual ~TFDPhysSQLiteDriverLink() { }
	
};


class PASCALIMPLEMENTATION TFDSQLiteService : public Firedac::Phys::TFDPhysDriverService
{
	typedef Firedac::Phys::TFDPhysDriverService inherited;
	
private:
	TFDPhysSQLiteDriverLink* __fastcall GetDriverLink();
	HIDESBASE void __fastcall SetDriverLink(TFDPhysSQLiteDriverLink* const AValue);
	
__published:
	__property TFDPhysSQLiteDriverLink* DriverLink = {read=GetDriverLink, write=SetDriverLink};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDSQLiteService() { }
	
public:
	/* TComponent.Create */ inline __fastcall virtual TFDSQLiteService(System::Classes::TComponent* AOwner) : Firedac::Phys::TFDPhysDriverService(AOwner) { }
	
};


class PASCALIMPLEMENTATION TFDSQLiteBackup : public TFDSQLiteService
{
	typedef TFDSQLiteService inherited;
	
private:
	System::UnicodeString FDestPassword;
	Firedac::Phys::TFDPhysServiceProgressEvent FOnProgress;
	System::UnicodeString FDestDatabase;
	System::UnicodeString FPassword;
	System::UnicodeString FDatabase;
	Firedac::Phys::Sqlitewrapper::TSQLiteDatabaseMode FDestMode;
	int FPagesPerStep;
	bool FWaitForLocks;
	System::UnicodeString FDestCatalog;
	System::UnicodeString FCatalog;
	Firedac::Phys::Sqlitewrapper::TSQLiteBackup* FBackup;
	int FBusyTimeout;
	Firedac::Phys::Sqlitewrapper::TSQLiteDatabase* FDestDatabaseObj;
	Firedac::Phys::Sqlitewrapper::TSQLiteDatabase* FDatabaseObj;
	void __fastcall SetDatabase(const System::UnicodeString AValue);
	void __fastcall SetDatabaseObj(Firedac::Phys::Sqlitewrapper::TSQLiteDatabase* const AValue);
	void __fastcall SetDestDatabase(const System::UnicodeString AValue);
	void __fastcall SetDestDatabaseObj(Firedac::Phys::Sqlitewrapper::TSQLiteDatabase* const AValue);
	int __fastcall GetPageCount();
	int __fastcall GetRemaining();
	
protected:
	virtual void __fastcall InternalExecute();
	
public:
	__fastcall virtual TFDSQLiteBackup(System::Classes::TComponent* AOwner);
	void __fastcall Backup();
	__property int Remaining = {read=GetRemaining, nodefault};
	__property int PageCount = {read=GetPageCount, nodefault};
	__property Firedac::Phys::Sqlitewrapper::TSQLiteDatabase* DatabaseObj = {read=FDatabaseObj, write=SetDatabaseObj};
	__property Firedac::Phys::Sqlitewrapper::TSQLiteDatabase* DestDatabaseObj = {read=FDestDatabaseObj, write=SetDestDatabaseObj};
	
__published:
	__property int PagesPerStep = {read=FPagesPerStep, write=FPagesPerStep, default=-1};
	__property bool WaitForLocks = {read=FWaitForLocks, write=FWaitForLocks, default=1};
	__property int BusyTimeout = {read=FBusyTimeout, write=FBusyTimeout, default=10000};
	__property System::UnicodeString Database = {read=FDatabase, write=SetDatabase};
	__property System::UnicodeString Catalog = {read=FCatalog, write=FCatalog};
	__property System::UnicodeString Password = {read=FPassword, write=FPassword};
	__property System::UnicodeString DestDatabase = {read=FDestDatabase, write=SetDestDatabase};
	__property System::UnicodeString DestCatalog = {read=FDestCatalog, write=FDestCatalog};
	__property Firedac::Phys::Sqlitewrapper::TSQLiteDatabaseMode DestMode = {read=FDestMode, write=FDestMode, default=0};
	__property System::UnicodeString DestPassword = {read=FDestPassword, write=FDestPassword};
	__property Firedac::Phys::TFDPhysServiceProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDSQLiteBackup() { }
	
};


enum DECLSPEC_DENUM TFDSQLiteValidateOption : unsigned int { voCheckIndexes };

typedef System::Set<TFDSQLiteValidateOption, TFDSQLiteValidateOption::voCheckIndexes, TFDSQLiteValidateOption::voCheckIndexes> TFDSQLiteValidateOptions;

class PASCALIMPLEMENTATION TFDSQLiteValidate : public TFDSQLiteService
{
	typedef TFDSQLiteService inherited;
	
	
private:
	enum DECLSPEC_DENUM TAction : unsigned int { saCheckOnly, saSweep, saAnalyze };
	
	
private:
	TAction FAction;
	System::UnicodeString FDatabase;
	int FMaxErrors;
	TFDSQLiteValidateOptions FOptions;
	System::UnicodeString FTable;
	System::UnicodeString FIndex;
	Firedac::Phys::TFDPhysServiceProgressEvent FOnProgress;
	System::UnicodeString FPassword;
	bool FLastStatus;
	
protected:
	virtual void __fastcall InternalExecute();
	
public:
	__fastcall virtual TFDSQLiteValidate(System::Classes::TComponent* AOwner);
	bool __fastcall CheckOnly();
	void __fastcall Sweep();
	void __fastcall Analyze(const System::UnicodeString ATable = System::UnicodeString(), const System::UnicodeString AIndex = System::UnicodeString());
	
__published:
	__property System::UnicodeString Database = {read=FDatabase, write=FDatabase};
	__property System::UnicodeString Password = {read=FPassword, write=FPassword};
	__property int MaxErrors = {read=FMaxErrors, write=FMaxErrors, default=-1};
	__property TFDSQLiteValidateOptions Options = {read=FOptions, write=FOptions, default=1};
	__property Firedac::Phys::TFDPhysServiceProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDSQLiteValidate() { }
	
};


enum DECLSPEC_DENUM Firedac_Phys_Sqlite__5 : unsigned int { soSetLargeCache };

typedef System::Set<Firedac_Phys_Sqlite__5, Firedac_Phys_Sqlite__5::soSetLargeCache, Firedac_Phys_Sqlite__5::soSetLargeCache> TFDSQLiteSecurityOptions;

class PASCALIMPLEMENTATION TFDSQLiteSecurity : public TFDSQLiteService
{
	typedef TFDSQLiteService inherited;
	
	
private:
	enum DECLSPEC_DENUM TAction : unsigned int { saSetPassword, saRemovePassword, saChangePassword, saCheckEncryption };
	
	
private:
	TAction FAction;
	System::UnicodeString FDatabase;
	System::UnicodeString FToPassword;
	System::UnicodeString FPassword;
	System::UnicodeString FEncryption;
	TFDSQLiteSecurityOptions FOptions;
	
protected:
	virtual void __fastcall InternalExecute();
	
public:
	void __fastcall SetPassword();
	void __fastcall RemovePassword();
	void __fastcall ChangePassword();
	System::UnicodeString __fastcall CheckEncryption();
	
__published:
	__property System::UnicodeString Database = {read=FDatabase, write=FDatabase};
	__property System::UnicodeString Password = {read=FPassword, write=FPassword};
	__property System::UnicodeString ToPassword = {read=FToPassword, write=FToPassword};
	__property TFDSQLiteSecurityOptions Options = {read=FOptions, write=FOptions, default=0};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDSQLiteSecurity() { }
	
public:
	/* TComponent.Create */ inline __fastcall virtual TFDSQLiteSecurity(System::Classes::TComponent* AOwner) : TFDSQLiteService(AOwner) { }
	
};


class PASCALIMPLEMENTATION TFDSQLiteFunction : public TFDSQLiteService
{
	typedef TFDSQLiteService inherited;
	
private:
	int FArgumentsCount;
	Firedac::Phys::Sqlitewrapper::TSQLiteFunctionFinalizeEvent FOnFinalize;
	Firedac::Phys::Sqlitewrapper::TSQLiteFunctionCalculateEvent FOnCalculate;
	bool FAggregated;
	bool FDeterministic;
	System::UnicodeString FFunctionName;
	Firedac::Phys::Sqlitewrapper::TSQLiteFunction* FFunction;
	void __fastcall SetAggregated(const bool AValue);
	void __fastcall SetDeterministic(const bool AValue);
	void __fastcall SetArgumentsCount(const int AValue);
	void __fastcall SetFunctionName(const System::UnicodeString AValue);
	void __fastcall SetOnCalculate(const Firedac::Phys::Sqlitewrapper::TSQLiteFunctionCalculateEvent AValue);
	void __fastcall SetOnFinalize(const Firedac::Phys::Sqlitewrapper::TSQLiteFunctionFinalizeEvent AValue);
	
protected:
	virtual bool __fastcall GetActualActive();
	virtual void __fastcall InternalUninstall();
	virtual void __fastcall InternalInstall();
	
public:
	__fastcall virtual TFDSQLiteFunction(System::Classes::TComponent* AOwner);
	
__published:
	__property Active = {default=0};
	__property System::UnicodeString FunctionName = {read=FFunctionName, write=SetFunctionName};
	__property int ArgumentsCount = {read=FArgumentsCount, write=SetArgumentsCount, default=0};
	__property bool Aggregated = {read=FAggregated, write=SetAggregated, default=0};
	__property bool Deterministic = {read=FDeterministic, write=SetDeterministic, default=1};
	__property Firedac::Phys::Sqlitewrapper::TSQLiteFunctionCalculateEvent OnCalculate = {read=FOnCalculate, write=SetOnCalculate};
	__property Firedac::Phys::Sqlitewrapper::TSQLiteFunctionFinalizeEvent OnFinalize = {read=FOnFinalize, write=SetOnFinalize};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDSQLiteFunction() { }
	
};


enum DECLSPEC_DENUM TFDSQLiteCollationKind : unsigned int { scCompareString, scCustomUTF8, scCustomUTF16 };

enum DECLSPEC_DENUM TFDSQLiteCollationFlag : unsigned int { sfLingIgnoreCase, sfLingIgnoreDiacritic, sfIgnoreCase, sfIgnoreKanatype, sfIgnoreNonSpace, sfIgnoreSymbols, sfIgnoreWidth, sfLingCasing, sfDigitAsNumbers, sfStringSort };

typedef System::Set<TFDSQLiteCollationFlag, TFDSQLiteCollationFlag::sfLingIgnoreCase, TFDSQLiteCollationFlag::sfStringSort> TFDSQLiteCollationFlags;

class PASCALIMPLEMENTATION TFDSQLiteCollation : public TFDSQLiteService
{
	typedef TFDSQLiteService inherited;
	
private:
	System::UnicodeString FCollationName;
	System::UnicodeString FLocaleName;
	TFDSQLiteCollationKind FCollationKind;
	TFDSQLiteCollationFlags FFlags;
	Firedac::Phys::Sqlitewrapper::TSQLiteCollation* FCollation;
	Firedac::Phys::Sqlitewrapper::TSQLiteCollationEvent FOnCompare;
	void __fastcall SetCollationKind(const TFDSQLiteCollationKind AValue);
	void __fastcall SetCollationName(const System::UnicodeString AValue);
	void __fastcall SetFlags(const TFDSQLiteCollationFlags AValue);
	void __fastcall SetLocaleName(const System::UnicodeString AValue);
	void __fastcall SetOnCompare(const Firedac::Phys::Sqlitewrapper::TSQLiteCollationEvent AValue);
	
protected:
	virtual bool __fastcall GetActualActive();
	virtual void __fastcall InternalUninstall();
	virtual void __fastcall InternalInstall();
	
public:
	__fastcall virtual TFDSQLiteCollation(System::Classes::TComponent* AOwner);
	
__published:
	__property Active = {default=0};
	__property System::UnicodeString CollationName = {read=FCollationName, write=SetCollationName};
	__property TFDSQLiteCollationKind CollationKind = {read=FCollationKind, write=SetCollationKind, default=0};
	__property System::UnicodeString LocaleName = {read=FLocaleName, write=SetLocaleName};
	__property TFDSQLiteCollationFlags Flags = {read=FFlags, write=SetFlags, default=0};
	__property Firedac::Phys::Sqlitewrapper::TSQLiteCollationEvent OnCompare = {read=FOnCompare, write=SetOnCompare};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDSQLiteCollation() { }
	
};


class PASCALIMPLEMENTATION TFDSQLiteRTree : public TFDSQLiteService
{
	typedef TFDSQLiteService inherited;
	
private:
	Firedac::Phys::Sqlitewrapper::TSQLiteRTree* FRTree;
	Firedac::Phys::Sqlitewrapper::TSQLiteRTreeFinalizeEvent FOnFinalize;
	Firedac::Phys::Sqlitewrapper::TSQLiteRTreeCalculateEvent FOnCalculate;
	System::UnicodeString FRTreeName;
	void __fastcall SetOnCalculate(const Firedac::Phys::Sqlitewrapper::TSQLiteRTreeCalculateEvent AValue);
	void __fastcall SetOnFinalize(const Firedac::Phys::Sqlitewrapper::TSQLiteRTreeFinalizeEvent AValue);
	void __fastcall SetRTreeName(const System::UnicodeString AValue);
	
protected:
	virtual bool __fastcall GetActualActive();
	virtual void __fastcall InternalUninstall();
	virtual void __fastcall InternalInstall();
	
__published:
	__property Active = {default=0};
	__property System::UnicodeString RTreeName = {read=FRTreeName, write=SetRTreeName};
	__property Firedac::Phys::Sqlitewrapper::TSQLiteRTreeCalculateEvent OnCalculate = {read=FOnCalculate, write=SetOnCalculate};
	__property Firedac::Phys::Sqlitewrapper::TSQLiteRTreeFinalizeEvent OnFinalize = {read=FOnFinalize, write=SetOnFinalize};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDSQLiteRTree() { }
	
public:
	/* TComponent.Create */ inline __fastcall virtual TFDSQLiteRTree(System::Classes::TComponent* AOwner) : TFDSQLiteService(AOwner) { }
	
};


//-- var, const, procedure ---------------------------------------------------
#ifndef __x86_64__
extern DELPHI_PACKAGE void __fastcall FDSQLiteTypeName2ADDataType(const Firedac::Stan::Option::_di_IFDStanOptions AOptions, const System::UnicodeString AColName, const System::UnicodeString ATypeName, /* out */ System::UnicodeString &ABaseColName, /* out */ System::UnicodeString &ABaseTypeName, /* out */ Firedac::Stan::Intf::TFDDataType &AType, /* out */ Firedac::Stan::Intf::TFDDataAttributes &AAttrs, /* out */ unsigned &ALen, /* out */ int &APrec, /* out */ int &AScale);
#else /* __x86_64__ */
extern DELPHI_PACKAGE void __fastcall FDSQLiteTypeName2ADDataType(const Firedac::Stan::Option::_di_IFDStanOptions AOptions, const System::UnicodeString AColName, const System::UnicodeString ATypeName, /* out */ System::UnicodeString &ABaseColName, /* out */ System::UnicodeString &ABaseTypeName, /* out */ Firedac::Stan::Intf::TFDDataType &AType, /* out */ Firedac::Stan::Intf::TFDDataAttributes &AAttrs, /* out */ unsigned long &ALen, /* out */ int &APrec, /* out */ int &AScale);
#endif /* __x86_64__ */
}	/* namespace Sqlite */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_SQLITE)
using namespace Firedac::Phys::Sqlite;
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
#endif	// Firedac_Phys_SqliteHPP
