// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.BDE.Import.pas' rev: 34.00 (Windows)

#ifndef Firedac_Bde_ImportHPP
#define Firedac_Bde_ImportHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Consts.hpp>
#include <FireDAC.Stan.Option.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Bde
{
namespace Import
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDBDEAliasImporter;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TFDAliasImportOverwriteEvent)(const System::UnicodeString AName, int &AOverwrite);

class PASCALIMPLEMENTATION TFDBDEAliasImporter : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Firedac::Stan::Intf::TFDStringList* FSrcParams;
	System::Classes::TStrings* FDestParams;
	Firedac::Stan::Option::_di_IFDStanOptions FOpts;
	Firedac::Stan::Option::TFDFetchOptions* FFetch;
	Firedac::Stan::Option::TFDFormatOptions* FFmt;
	Firedac::Stan::Option::TFDUpdateOptions* FUpd;
	Firedac::Stan::Option::TFDResourceOptions* FRes;
	System::UnicodeString FConnectionDefFileName;
	bool FOverwriteDefs;
	Firedac::Stan::Intf::TFDStringList* FAliasesToImport;
	TFDAliasImportOverwriteEvent FOnOverwrite;
	bool __fastcall GetSrcBool(const System::UnicodeString AName, bool &AResult);
	bool __fastcall GetSrcInt(const System::UnicodeString AName, int &AResult);
	bool __fastcall GetSrcStr(const System::UnicodeString AName, System::UnicodeString &AResult);
	void __fastcall ImportSQLCommon();
	void __fastcall ImportOracle(bool AImportMode);
	void __fastcall ImportIB(bool AImportMode);
	void __fastcall ImportMSSQL(bool AImportMode);
	void __fastcall ImportMSAccess(bool AImportMode);
	void __fastcall ImportODBC(bool AImportMode);
	void __fastcall ImportDB2(bool AImportMode);
	void __fastcall ImportMySQL(bool AImportMode);
	
public:
	__fastcall TFDBDEAliasImporter();
	__fastcall virtual ~TFDBDEAliasImporter();
	void __fastcall Execute();
	void __fastcall MakeBDECompatible(const Firedac::Stan::Intf::_di_IFDStanConnectionDef AConnectionDef, bool AEnableBCD, bool AEnableInteger);
	__property System::UnicodeString ConnectionDefFileName = {read=FConnectionDefFileName, write=FConnectionDefFileName};
	__property Firedac::Stan::Intf::TFDStringList* AliasesToImport = {read=FAliasesToImport};
	__property bool OverwriteDefs = {read=FOverwriteDefs, write=FOverwriteDefs, nodefault};
	__property TFDAliasImportOverwriteEvent OnOverwrite = {read=FOnOverwrite, write=FOnOverwrite};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Import */
}	/* namespace Bde */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_BDE_IMPORT)
using namespace Firedac::Bde::Import;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_BDE)
using namespace Firedac::Bde;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Bde_ImportHPP
