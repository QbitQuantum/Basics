// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.IB.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_IbHPP
#define Firedac_Phys_IbHPP

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
#ifndef _WIN64
#pragma link "FireDAC.Phys.IB.obj"
#else /* _WIN64 */
#pragma link "FireDAC.Phys.IB.o"
#endif /* _WIN64 */

namespace Firedac
{
namespace Phys
{
namespace Ib
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysIBDriverLink;
class DELPHICLASS TFDIBSDump;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysIBDriverLink : public Firedac::Phys::Ibbase::TFDPhysIBBaseDriverLink
{
	typedef Firedac::Phys::Ibbase::TFDPhysIBBaseDriverLink inherited;
	
private:
	bool FLite;
	
protected:
	virtual System::UnicodeString __fastcall GetBaseDriverID();
	virtual bool __fastcall IsConfigured();
	virtual void __fastcall ApplyTo(const Firedac::Stan::Intf::_di_IFDStanDefinition AParams);
	
__published:
	__property bool Lite = {read=FLite, write=FLite, default=0};
public:
	/* TFDPhysDriverLink.Create */ inline __fastcall virtual TFDPhysIBDriverLink(System::Classes::TComponent* AOwner) : Firedac::Phys::Ibbase::TFDPhysIBBaseDriverLink(AOwner) { }
	/* TFDPhysDriverLink.Destroy */ inline __fastcall virtual ~TFDPhysIBDriverLink() { }
	
};


class PASCALIMPLEMENTATION TFDIBSDump : public Firedac::Phys::Ibbase::TFDIBService
{
	typedef Firedac::Phys::Ibbase::TFDIBService inherited;
	
private:
	System::UnicodeString FDatabase;
	System::Classes::TStrings* FBackupFiles;
	bool FOverwrite;
	Firedac::Phys::Ibwrapper::TIBSDumpOptions FOptions;
	void __fastcall SetBackupFiles(System::Classes::TStrings* const AValue);
	
protected:
	virtual Firedac::Phys::Ibwrapper::TIBService* __fastcall CreateService(Firedac::Phys::Ibwrapper::TIBEnv* AEnv);
	virtual void __fastcall SetupService(Firedac::Phys::Ibwrapper::TIBService* AService);
	
public:
	__fastcall virtual TFDIBSDump(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDIBSDump();
	void __fastcall Dump();
	
__published:
	__property System::UnicodeString Database = {read=FDatabase, write=FDatabase};
	__property System::Classes::TStrings* BackupFiles = {read=FBackupFiles, write=SetBackupFiles};
	__property bool Overwrite = {read=FOverwrite, write=FOverwrite, default=0};
	__property Firedac::Phys::Ibwrapper::TIBSDumpOptions Options = {read=FOptions, write=FOptions, default=0};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ib */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_IB)
using namespace Firedac::Phys::Ib;
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
#endif	// Firedac_Phys_IbHPP
