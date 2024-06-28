// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.FB.pas' rev: 34.00 (iOS)

#ifndef Firedac_Phys_FbHPP
#define Firedac_Phys_FbHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.IBWrapper.hpp>
#include <FireDAC.Phys.IBBase.hpp>

//-- user supplied -----------------------------------------------------------
namespace Firedac
{
namespace Phys
{
namespace Fb
{
  _INIT_UNIT(Firedac_Phys_Fb);
}	/* namespace Fb */
}	/* namespace Phys */
}	/* namespace Firedac */

namespace Firedac
{
namespace Phys
{
namespace Fb
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysFBDriverLink;
class DELPHICLASS TFDFBNBackup;
class DELPHICLASS TFDFBNRestore;
class DELPHICLASS TFDFBTrace;
class DELPHICLASS TFDFBOnlineValidate;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysFBDriverLink : public Firedac::Phys::Ibbase::TFDPhysIBBaseDriverLink
{
	typedef Firedac::Phys::Ibbase::TFDPhysIBBaseDriverLink inherited;
	
private:
	bool FEmbedded;
	
protected:
	virtual System::UnicodeString __fastcall GetBaseDriverID();
	virtual bool __fastcall IsConfigured();
	virtual void __fastcall ApplyTo(const Firedac::Stan::Intf::_di_IFDStanDefinition AParams);
	
__published:
	__property bool Embedded = {read=FEmbedded, write=FEmbedded, default=0};
public:
	/* TFDPhysDriverLink.Create */ inline __fastcall virtual TFDPhysFBDriverLink(System::Classes::TComponent* AOwner) : Firedac::Phys::Ibbase::TFDPhysIBBaseDriverLink(AOwner) { }
	/* TFDPhysDriverLink.Destroy */ inline __fastcall virtual ~TFDPhysFBDriverLink() { }
	
};


class PASCALIMPLEMENTATION TFDFBNBackup : public Firedac::Phys::Ibbase::TFDIBService
{
	typedef Firedac::Phys::Ibbase::TFDIBService inherited;
	
private:
	int FLevel;
	System::UnicodeString FBackupFile;
	System::UnicodeString FDatabase;
	Firedac::Phys::Ibwrapper::TFBNBackupOptions FOptions;
	Firedac::Phys::Ibwrapper::TFBNBackupDirect FDirect;
	
protected:
	virtual Firedac::Phys::Ibwrapper::TIBService* __fastcall CreateService(Firedac::Phys::Ibwrapper::TIBEnv* AEnv);
	virtual void __fastcall SetupService(Firedac::Phys::Ibwrapper::TIBService* AService);
	
public:
	void __fastcall Backup();
	
__published:
	__property System::UnicodeString Database = {read=FDatabase, write=FDatabase};
	__property System::UnicodeString BackupFile = {read=FBackupFile, write=FBackupFile};
	__property int Level = {read=FLevel, write=FLevel, default=0};
	__property Firedac::Phys::Ibwrapper::TFBNBackupOptions Options = {read=FOptions, write=FOptions, default=0};
	__property Firedac::Phys::Ibwrapper::TFBNBackupDirect Direct = {read=FDirect, write=FDirect, default=0};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDFBNBackup() { }
	
public:
	/* TComponent.Create */ inline __fastcall virtual TFDFBNBackup(System::Classes::TComponent* AOwner) : Firedac::Phys::Ibbase::TFDIBService(AOwner) { }
	
};


class PASCALIMPLEMENTATION TFDFBNRestore : public Firedac::Phys::Ibbase::TFDIBService
{
	typedef Firedac::Phys::Ibbase::TFDIBService inherited;
	
private:
	System::Classes::TStrings* FBackupFiles;
	System::UnicodeString FDatabase;
	Firedac::Phys::Ibwrapper::TFBNBackupOptions FOptions;
	void __fastcall SetBackupFile(System::Classes::TStrings* const AValue);
	
protected:
	virtual Firedac::Phys::Ibwrapper::TIBService* __fastcall CreateService(Firedac::Phys::Ibwrapper::TIBEnv* AEnv);
	virtual void __fastcall SetupService(Firedac::Phys::Ibwrapper::TIBService* AService);
	
public:
	__fastcall virtual TFDFBNRestore(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDFBNRestore();
	void __fastcall Restore();
	
__published:
	__property System::UnicodeString Database = {read=FDatabase, write=FDatabase};
	__property System::Classes::TStrings* BackupFiles = {read=FBackupFiles, write=SetBackupFile};
	__property Firedac::Phys::Ibwrapper::TFBNBackupOptions Options = {read=FOptions, write=FOptions, default=0};
};


class PASCALIMPLEMENTATION TFDFBTrace : public Firedac::Phys::Ibbase::TFDIBService
{
	typedef Firedac::Phys::Ibbase::TFDIBService inherited;
	
private:
	Firedac::Phys::Ibwrapper::TIBTraceAction FAction;
	System::UnicodeString FSessionName;
	System::Classes::TStrings* FConfig;
	int FSessionID;
	System::Classes::TThread* FThread;
	void __fastcall SetConfig(System::Classes::TStrings* const AValue);
	
protected:
	virtual Firedac::Phys::Ibwrapper::TIBService* __fastcall CreateService(Firedac::Phys::Ibwrapper::TIBEnv* AEnv);
	virtual void __fastcall SetupService(Firedac::Phys::Ibwrapper::TIBService* AService);
	virtual void __fastcall DoProgress(Firedac::Phys::Ibwrapper::TIBService* AService, const System::UnicodeString AMessage);
	
public:
	__fastcall virtual TFDFBTrace(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDFBTrace();
	void __fastcall Start();
	void __fastcall Stop();
	void __fastcall Suspend();
	void __fastcall Resume();
	void __fastcall List();
	
__published:
	__property System::UnicodeString SessionName = {read=FSessionName, write=FSessionName};
	__property int SessionID = {read=FSessionID, write=FSessionID, default=0};
	__property System::Classes::TStrings* Config = {read=FConfig, write=SetConfig};
};


class PASCALIMPLEMENTATION TFDFBOnlineValidate : public Firedac::Phys::Ibbase::TFDIBService
{
	typedef Firedac::Phys::Ibbase::TFDIBService inherited;
	
private:
	System::UnicodeString FDatabase;
	System::UnicodeString FIndexesInclude;
	int FLockTimeout;
	System::UnicodeString FTablesInclude;
	System::UnicodeString FIndexesExclude;
	System::UnicodeString FTablesExclude;
	
protected:
	virtual Firedac::Phys::Ibwrapper::TIBService* __fastcall CreateService(Firedac::Phys::Ibwrapper::TIBEnv* AEnv);
	virtual void __fastcall SetupService(Firedac::Phys::Ibwrapper::TIBService* AService);
	
public:
	__fastcall virtual TFDFBOnlineValidate(System::Classes::TComponent* AOwner);
	void __fastcall Validate();
	
__published:
	__property System::UnicodeString Database = {read=FDatabase, write=FDatabase};
	__property System::UnicodeString TablesInclude = {read=FTablesInclude, write=FTablesInclude};
	__property System::UnicodeString TablesExclude = {read=FTablesExclude, write=FTablesExclude};
	__property System::UnicodeString IndexesInclude = {read=FIndexesInclude, write=FIndexesInclude};
	__property System::UnicodeString IndexesExclude = {read=FIndexesExclude, write=FIndexesExclude};
	__property int LockTimeout = {read=FLockTimeout, write=FLockTimeout, default=10};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDFBOnlineValidate() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fb */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_FB)
using namespace Firedac::Phys::Fb;
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
#endif	// Firedac_Phys_FbHPP
