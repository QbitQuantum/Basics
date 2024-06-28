// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.ASA.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_AsaHPP
#define Firedac_Phys_AsaHPP

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
#include <FireDAC.Phys.ODBCWrapper.hpp>
#include <FireDAC.Phys.ODBCBase.hpp>
#include <FireDAC.Phys.ASAWrapper.hpp>

//-- user supplied -----------------------------------------------------------
#ifndef _WIN64
#pragma link "FireDAC.Phys.ASA.obj"
#else /* _WIN64 */
#pragma link "FireDAC.Phys.ASA.o"
#endif /* _WIN64 */

namespace Firedac
{
namespace Phys
{
namespace Asa
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysASADriverLink;
class DELPHICLASS TFDASAService;
class DELPHICLASS TFDASABackup;
class DELPHICLASS TFDASAValidate;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysASADriverLink : public Firedac::Phys::Odbcbase::TFDPhysODBCBaseDriverLink
{
	typedef Firedac::Phys::Odbcbase::TFDPhysODBCBaseDriverLink inherited;
	
private:
	System::UnicodeString FToolLib;
	System::UnicodeString FToolHome;
	
protected:
	virtual System::UnicodeString __fastcall GetBaseDriverID();
	virtual bool __fastcall IsConfigured();
	virtual void __fastcall ApplyTo(const Firedac::Stan::Intf::_di_IFDStanDefinition AParams);
	
__published:
	__property System::UnicodeString ToolHome = {read=FToolHome, write=FToolHome};
	__property System::UnicodeString ToolLib = {read=FToolLib, write=FToolLib};
public:
	/* TFDPhysDriverLink.Create */ inline __fastcall virtual TFDPhysASADriverLink(System::Classes::TComponent* AOwner) : Firedac::Phys::Odbcbase::TFDPhysODBCBaseDriverLink(AOwner) { }
	/* TFDPhysDriverLink.Destroy */ inline __fastcall virtual ~TFDPhysASADriverLink() { }
	
};


typedef void __fastcall (__closure *TFDASAProgressEvent)(System::TObject* ASender, System::UnicodeString AMessage, Firedac::Phys::Asawrapper::TASAToolMessageKind AKind, int &AResult);

class PASCALIMPLEMENTATION TFDASAService : public Firedac::Phys::Odbcbase::TFDPhysODBCBaseService
{
	typedef Firedac::Phys::Odbcbase::TFDPhysODBCBaseService inherited;
	
private:
	TFDASAProgressEvent FOnProgress;
	TFDPhysASADriverLink* __fastcall GetDriverLink();
	HIDESBASE void __fastcall SetDriverLink(TFDPhysASADriverLink* const AValue);
	Firedac::Phys::Asawrapper::TASAToolLib* __fastcall GetToolLib();
	
protected:
	virtual Firedac::Phys::Odbcwrapper::TODBCEnvironment* __fastcall GetEnv();
	virtual void __fastcall CheckActive(bool AAutoActivate, bool ANeedActivation);
	
public:
	__property Firedac::Phys::Asawrapper::TASAToolLib* ToolLib = {read=GetToolLib};
	
__published:
	__property TFDPhysASADriverLink* DriverLink = {read=GetDriverLink, write=SetDriverLink};
	__property TFDASAProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDASAService() { }
	
public:
	/* TComponent.Create */ inline __fastcall virtual TFDASAService(System::Classes::TComponent* AOwner) : Firedac::Phys::Odbcbase::TFDPhysODBCBaseService(AOwner) { }
	
};


class PASCALIMPLEMENTATION TFDASABackup : public TFDASAService
{
	typedef TFDASAService inherited;
	
private:
	System::UnicodeString FConnectParams;
	Firedac::Phys::Asawrapper::TASABackupCheckpointLogType FCheckpointLogType;
	unsigned FPageBlocksize;
	System::UnicodeString FHotlogFilename;
	System::UnicodeString FOutputDir;
	Firedac::Phys::Asawrapper::TASABackupFlags FFlags;
	System::UnicodeString FStartLine;
	
protected:
	virtual void __fastcall InternalExecute();
	
public:
	__fastcall virtual TFDASABackup(System::Classes::TComponent* AOwner);
	void __fastcall Backup();
	
__published:
	__property System::UnicodeString ConnectParams = {read=FConnectParams, write=FConnectParams};
	__property System::UnicodeString StartLine = {read=FStartLine, write=FStartLine};
	__property System::UnicodeString OutputDir = {read=FOutputDir, write=FOutputDir};
	__property System::UnicodeString HotlogFilename = {read=FHotlogFilename, write=FHotlogFilename};
	__property Firedac::Phys::Asawrapper::TASABackupCheckpointLogType CheckpointLogType = {read=FCheckpointLogType, write=FCheckpointLogType, default=4};
	__property unsigned PageBlocksize = {read=FPageBlocksize, write=FPageBlocksize, default=0};
	__property Firedac::Phys::Asawrapper::TASABackupFlags Flags = {read=FFlags, write=FFlags, default=0};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDASABackup() { }
	
};


class PASCALIMPLEMENTATION TFDASAValidate : public TFDASAService
{
	typedef TFDASAService inherited;
	
private:
	System::UnicodeString FConnectParams;
	System::UnicodeString FStartLine;
	Firedac::Phys::Asawrapper::TASAValidateType FValidateType;
	System::Classes::TStrings* FTables;
	Firedac::Phys::Asawrapper::TASAValidateFlags FFlags;
	void __fastcall SetTables(System::Classes::TStrings* const AValue);
	
protected:
	virtual void __fastcall InternalExecute();
	
public:
	__fastcall virtual TFDASAValidate(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDASAValidate();
	void __fastcall Validate();
	
__published:
	__property System::UnicodeString ConnectParams = {read=FConnectParams, write=FConnectParams};
	__property System::UnicodeString StartLine = {read=FStartLine, write=FStartLine};
	__property System::Classes::TStrings* Tables = {read=FTables, write=SetTables};
	__property Firedac::Phys::Asawrapper::TASAValidateFlags Flags = {read=FFlags, write=FFlags, default=0};
	__property Firedac::Phys::Asawrapper::TASAValidateType ValidateType = {read=FValidateType, write=FValidateType, default=0};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Asa */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ASA)
using namespace Firedac::Phys::Asa;
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
#endif	// Firedac_Phys_AsaHPP
