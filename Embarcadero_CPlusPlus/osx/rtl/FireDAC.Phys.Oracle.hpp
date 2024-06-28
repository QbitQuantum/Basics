// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.Oracle.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_OracleHPP
#define Firedac_Phys_OracleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.OracleWrapper.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FireDAC.Phys.Oracle"

namespace Firedac
{
namespace Phys
{
namespace Oracle
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysOracleDriverLink;
class DELPHICLASS TFDOracleAdmin;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysOracleDriverLink : public Firedac::Phys::TFDPhysDriverLink
{
	typedef Firedac::Phys::TFDPhysDriverLink inherited;
	
private:
	System::UnicodeString FTNSAdmin;
	System::UnicodeString FNLSLang;
	bool FThreaded;
	
protected:
	virtual System::UnicodeString __fastcall GetBaseDriverID();
	virtual bool __fastcall IsConfigured();
	virtual void __fastcall ApplyTo(const Firedac::Stan::Intf::_di_IFDStanDefinition AParams);
	
public:
	__fastcall virtual TFDPhysOracleDriverLink(System::Classes::TComponent* AOwner);
	static void __fastcall GetOracleHomes(System::Classes::TStrings* AList);
	void __fastcall GetTNSServices(System::Classes::TStrings* AList);
	
__published:
	__property System::UnicodeString NLSLang = {read=FNLSLang, write=FNLSLang};
	__property System::UnicodeString TNSAdmin = {read=FTNSAdmin, write=FTNSAdmin};
	__property bool Threaded = {read=FThreaded, write=FThreaded, default=1};
public:
	/* TFDPhysDriverLink.Destroy */ inline __fastcall virtual ~TFDPhysOracleDriverLink() { }
	
};


enum DECLSPEC_DENUM Firedac_Phys_Oracle__2 : unsigned int { stoStart, stoMount, stoOpen, stoOpenPDB };

typedef System::Set<Firedac_Phys_Oracle__2, Firedac_Phys_Oracle__2::stoStart, Firedac_Phys_Oracle__2::stoOpenPDB> TFDOracleStartupOperations;

enum DECLSPEC_DENUM Firedac_Phys_Oracle__3 : unsigned int { shoShutdown, shoClose, shoDismount, shoClosePDB };

typedef System::Set<Firedac_Phys_Oracle__3, Firedac_Phys_Oracle__3::shoShutdown, Firedac_Phys_Oracle__3::shoClosePDB> TFDOracleShutdownOperations;

class PASCALIMPLEMENTATION TFDOracleAdmin : public Firedac::Phys::TFDPhysDriverService
{
	typedef Firedac::Phys::TFDPhysDriverService inherited;
	
	
private:
	enum DECLSPEC_DENUM TAction : unsigned int { aaStartup, aaShutdown };
	
	
private:
	TAction FAction;
	TFDOracleStartupOperations FStartupOperations;
	Firedac::Phys::Oraclewrapper::TOCIStartupFlags FStartupFlags;
	Firedac::Phys::Oraclewrapper::TOCIShutdownMode FShutdownMode;
	TFDOracleShutdownOperations FShutdownOperations;
	System::UnicodeString FServer;
	System::UnicodeString FUserName;
	System::UnicodeString FPassword;
	System::UnicodeString FPFile;
	System::UnicodeString FPluggableDB;
	TFDPhysOracleDriverLink* __fastcall GetDriverLink();
	HIDESBASE void __fastcall SetDriverLink(TFDPhysOracleDriverLink* const AValue);
	void __fastcall InternalStartup();
	void __fastcall InternalShutdown();
	
protected:
	virtual void __fastcall InternalExecute();
	
public:
	__fastcall virtual TFDOracleAdmin(System::Classes::TComponent* AOwner);
	void __fastcall Startup();
	void __fastcall Shutdown();
	
__published:
	__property TFDPhysOracleDriverLink* DriverLink = {read=GetDriverLink, write=SetDriverLink};
	__property TFDOracleStartupOperations StartupOperations = {read=FStartupOperations, write=FStartupOperations, default=7};
	__property Firedac::Phys::Oraclewrapper::TOCIStartupFlags StartupFlags = {read=FStartupFlags, write=FStartupFlags, default=0};
	__property TFDOracleShutdownOperations ShutdownOperations = {read=FShutdownOperations, write=FShutdownOperations, default=7};
	__property Firedac::Phys::Oraclewrapper::TOCIShutdownMode ShutdownMode = {read=FShutdownMode, write=FShutdownMode, default=0};
	__property System::UnicodeString Server = {read=FServer, write=FServer};
	__property System::UnicodeString UserName = {read=FUserName, write=FUserName};
	__property System::UnicodeString Password = {read=FPassword, write=FPassword};
	__property System::UnicodeString PFile = {read=FPFile, write=FPFile};
	__property System::UnicodeString PluggableDB = {read=FPluggableDB, write=FPluggableDB};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDOracleAdmin() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Oracle */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ORACLE)
using namespace Firedac::Phys::Oracle;
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
#endif	// Firedac_Phys_OracleHPP
