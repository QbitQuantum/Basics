// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.ADS.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_AdsHPP
#define Firedac_Phys_AdsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.ADSWrapper.hpp>

//-- user supplied -----------------------------------------------------------
#ifndef _WIN64
#pragma link "FireDAC.Phys.ADS.obj"
#else /* _WIN64 */
#pragma link "FireDAC.Phys.ADS.o"
#endif /* _WIN64 */

namespace Firedac
{
namespace Phys
{
namespace Ads
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysADSDriverLink;
class DELPHICLASS TFDADSService;
class DELPHICLASS TFDADSBackupRestore;
class DELPHICLASS TFDADSBackup;
class DELPHICLASS TFDADSRestore;
class DELPHICLASS TFDADSUtility;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysADSDriverLink : public Firedac::Phys::TFDPhysDriverLink
{
	typedef Firedac::Phys::TFDPhysDriverLink inherited;
	
private:
	System::UnicodeString FDateFormat;
	int FDecimals;
	System::UnicodeString FDefaultPath;
	System::UnicodeString FSearchPath;
	bool FShowDeleted;
	System::Word FEpoch;
	bool FExact;
	System::UnicodeString __fastcall GetDateFormat();
	System::Word __fastcall GetDecimals();
	System::UnicodeString __fastcall GetDefaultPath();
	System::Word __fastcall GetEpoch();
	bool __fastcall GetExact();
	System::UnicodeString __fastcall GetSearchPath();
	bool __fastcall GetShowDeleted();
	void __fastcall SetDateFormat(const System::UnicodeString AValue);
	void __fastcall SetDecimals(const System::Word AValue);
	void __fastcall SetDefaultPath(const System::UnicodeString AValue);
	void __fastcall SetEpoch(const System::Word AValue);
	void __fastcall SetExact(const bool AValue);
	void __fastcall SetSearchPath(const System::UnicodeString AValue);
	void __fastcall SetShowDeleted(const bool AValue);
	bool __fastcall IsDFS();
	bool __fastcall IsDS();
	bool __fastcall IsDPS();
	bool __fastcall IsEpS();
	bool __fastcall IsExS();
	bool __fastcall IsSDS();
	bool __fastcall IsSPS();
	
protected:
	virtual System::UnicodeString __fastcall GetBaseDriverID();
	virtual bool __fastcall IsConfigured();
	virtual void __fastcall ApplyTo(const Firedac::Stan::Intf::_di_IFDStanDefinition AParams);
	
public:
	__fastcall virtual TFDPhysADSDriverLink(System::Classes::TComponent* AOwner);
	
__published:
	__property System::UnicodeString DateFormat = {read=GetDateFormat, write=SetDateFormat, stored=IsDFS};
	__property System::Word Decimals = {read=GetDecimals, write=SetDecimals, stored=IsDS, nodefault};
	__property System::UnicodeString DefaultPath = {read=GetDefaultPath, write=SetDefaultPath, stored=IsDPS};
	__property System::UnicodeString SearchPath = {read=GetSearchPath, write=SetSearchPath, stored=IsSPS};
	__property bool ShowDeleted = {read=GetShowDeleted, write=SetShowDeleted, stored=IsSDS, nodefault};
	__property System::Word Epoch = {read=GetEpoch, write=SetEpoch, stored=IsEpS, nodefault};
	__property bool Exact = {read=GetExact, write=SetExact, stored=IsExS, nodefault};
public:
	/* TFDPhysDriverLink.Destroy */ inline __fastcall virtual ~TFDPhysADSDriverLink() { }
	
};


class PASCALIMPLEMENTATION TFDADSService : public Firedac::Phys::TFDPhysDriverService
{
	typedef Firedac::Phys::TFDPhysDriverService inherited;
	
private:
	System::UnicodeString FPassword;
	System::UnicodeString FUserName;
	System::UnicodeString FDatabase;
	TFDPhysADSDriverLink* __fastcall GetDriverLink();
	HIDESBASE void __fastcall SetDriverLink(TFDPhysADSDriverLink* const AValue);
	void __fastcall GetConnection(/* out */ Firedac::Phys::Intf::_di_IFDPhysConnection &AConn, /* out */ Firedac::Phys::Intf::_di_IFDPhysCommand &ACmd);
	
protected:
	virtual System::UnicodeString __fastcall GetConnectionString();
	
__published:
	__property TFDPhysADSDriverLink* DriverLink = {read=GetDriverLink, write=SetDriverLink};
	__property System::UnicodeString Database = {read=FDatabase, write=FDatabase};
	__property System::UnicodeString UserName = {read=FUserName, write=FUserName};
	__property System::UnicodeString Password = {read=FPassword, write=FPassword};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDADSService() { }
	
public:
	/* TComponent.Create */ inline __fastcall virtual TFDADSService(System::Classes::TComponent* AOwner) : Firedac::Phys::TFDPhysDriverService(AOwner) { }
	
};


class PASCALIMPLEMENTATION TFDADSBackupRestore : public TFDADSService
{
	typedef TFDADSService inherited;
	
private:
	System::Classes::TStrings* FInclude;
	System::Classes::TStrings* FExclude;
	System::Classes::TStrings* FTableTypeMap;
	Firedac::Dats::TFDDatSTable* FResults;
	System::UnicodeString FArchiveFile;
	void __fastcall SetInclude(System::Classes::TStrings* const AValue);
	void __fastcall SetExclude(System::Classes::TStrings* const AValue);
	void __fastcall SetTableTypeMap(System::Classes::TStrings* const AValue);
	static void __fastcall AddOption(System::UnicodeString &AStr, const System::UnicodeString AName, const System::UnicodeString AValue);
	
protected:
	virtual System::UnicodeString __fastcall GetOptions();
	
public:
	__fastcall virtual TFDADSBackupRestore(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDADSBackupRestore();
	__property Firedac::Dats::TFDDatSTable* Results = {read=FResults};
	
__published:
	__property System::Classes::TStrings* Include = {read=FInclude, write=SetInclude};
	__property System::Classes::TStrings* Exclude = {read=FExclude, write=SetExclude};
	__property System::Classes::TStrings* TableTypeMap = {read=FTableTypeMap, write=SetTableTypeMap};
	__property System::UnicodeString ArchiveFile = {read=FArchiveFile, write=FArchiveFile};
};


enum DECLSPEC_DENUM Firedac_Phys_Ads__4 : unsigned int { boMetaOnly, boPrepareDiff, boDiff, boCompressArchive };

typedef System::Set<Firedac_Phys_Ads__4, Firedac_Phys_Ads__4::boMetaOnly, Firedac_Phys_Ads__4::boCompressArchive> TFDADSBackupOptions;

class PASCALIMPLEMENTATION TFDADSBackup : public TFDADSBackupRestore
{
	typedef TFDADSBackupRestore inherited;
	
private:
	System::UnicodeString FBackupPath;
	TFDADSBackupOptions FOptions;
	
protected:
	virtual void __fastcall InternalExecute();
	virtual System::UnicodeString __fastcall GetOptions();
	
public:
	void __fastcall Backup();
	
__published:
	__property System::UnicodeString BackupPath = {read=FBackupPath, write=FBackupPath};
	__property TFDADSBackupOptions Options = {read=FOptions, write=FOptions, default=0};
public:
	/* TFDADSBackupRestore.Create */ inline __fastcall virtual TFDADSBackup(System::Classes::TComponent* AOwner) : TFDADSBackupRestore(AOwner) { }
	/* TFDADSBackupRestore.Destroy */ inline __fastcall virtual ~TFDADSBackup() { }
	
};


enum DECLSPEC_DENUM Firedac_Phys_Ads__6 : unsigned int { roDontOverwrite, roMetaOnly, roNoWarnings, roCompressedArchive, roForceArchiveExtract };

typedef System::Set<Firedac_Phys_Ads__6, Firedac_Phys_Ads__6::roDontOverwrite, Firedac_Phys_Ads__6::roForceArchiveExtract> TFDADSRestoreOptions;

class PASCALIMPLEMENTATION TFDADSRestore : public TFDADSBackupRestore
{
	typedef TFDADSBackupRestore inherited;
	
private:
	System::UnicodeString FSourcePath;
	System::UnicodeString FSourcePassword;
	System::UnicodeString FDestinationPath;
	System::UnicodeString FDDPassword;
	TFDADSRestoreOptions FOptions;
	
protected:
	virtual void __fastcall InternalExecute();
	virtual System::UnicodeString __fastcall GetOptions();
	
public:
	void __fastcall Restore();
	
__published:
	__property System::UnicodeString SourcePath = {read=FSourcePath, write=FSourcePath};
	__property System::UnicodeString SourcePassword = {read=FSourcePassword, write=FSourcePassword};
	__property System::UnicodeString DestinationPath = {read=FDestinationPath, write=FDestinationPath};
	__property System::UnicodeString DDPassword = {read=FDDPassword, write=FDDPassword};
	__property TFDADSRestoreOptions Options = {read=FOptions, write=FOptions, default=0};
public:
	/* TFDADSBackupRestore.Create */ inline __fastcall virtual TFDADSRestore(System::Classes::TComponent* AOwner) : TFDADSBackupRestore(AOwner) { }
	/* TFDADSBackupRestore.Destroy */ inline __fastcall virtual ~TFDADSRestore() { }
	
};


class PASCALIMPLEMENTATION TFDADSUtility : public TFDADSService
{
	typedef TFDADSService inherited;
	
	
private:
	enum DECLSPEC_DENUM TMode : unsigned int { umEncrypt, umDecrypt, umPack, umZap, umReindex, umRecall };
	
	
private:
	System::Classes::TStrings* FTables;
	TMode FMode;
	Firedac::Phys::TFDPhysServiceProgressEvent FOnProgress;
	Firedac::Phys::Adswrapper::TADSTableType FTableType;
	System::UnicodeString FTablePassword;
	void __fastcall SetTables(System::Classes::TStrings* const AValue);
	
protected:
	virtual System::UnicodeString __fastcall GetConnectionString();
	virtual void __fastcall InternalExecute();
	
public:
	__fastcall virtual TFDADSUtility(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDADSUtility();
	void __fastcall Encrypt();
	void __fastcall Decrypt();
	void __fastcall Pack();
	void __fastcall Zap();
	void __fastcall Reindex();
	void __fastcall Recall();
	
__published:
	__property System::Classes::TStrings* Tables = {read=FTables, write=SetTables};
	__property Firedac::Phys::Adswrapper::TADSTableType TableType = {read=FTableType, write=FTableType, default=0};
	__property System::UnicodeString TablePassword = {read=FTablePassword, write=FTablePassword};
	__property Firedac::Phys::TFDPhysServiceProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ads */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ADS)
using namespace Firedac::Phys::Ads;
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
#endif	// Firedac_Phys_AdsHPP
