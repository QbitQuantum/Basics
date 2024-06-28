// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.ADO.Import.pas' rev: 34.00 (Windows)

#ifndef Firedac_Ado_ImportHPP
#define Firedac_Ado_ImportHPP

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
namespace Ado
{
namespace Import
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDADOUDLImporter;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TFDUDLImportOverwriteEvent)(const System::UnicodeString AName, int &AOverwrite);

typedef void __fastcall (__closure *TFDUDLImportBeforeWriteOptions)(const System::UnicodeString ADriverID, Firedac::Stan::Option::TFDFormatOptions* AFormatOptions, Firedac::Stan::Option::TFDUpdateOptions* AUpdateOptions, Firedac::Stan::Option::TFDFetchOptions* AFetchOptions, Firedac::Stan::Option::TFDResourceOptions* AResourceOptions);

typedef void __fastcall (__closure *TFDUDLImportBeforeWriteSettings)(System::Classes::TStrings* AParams);

class PASCALIMPLEMENTATION TFDADOUDLImporter : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TStrings* FSrcParams;
	System::Classes::TStrings* FDestParams;
	Firedac::Stan::Option::_di_IFDStanOptions FOpts;
	Firedac::Stan::Option::TFDFetchOptions* FFetch;
	Firedac::Stan::Option::TFDFormatOptions* FFmt;
	Firedac::Stan::Option::TFDUpdateOptions* FUpd;
	Firedac::Stan::Option::TFDResourceOptions* FRes;
	bool FOverwriteDefs;
	System::Classes::TStrings* FUDLToImport;
	TFDUDLImportOverwriteEvent FOnOverwrite;
	TFDUDLImportBeforeWriteOptions FOnBeforeWriteOptions;
	TFDUDLImportBeforeWriteSettings FOnBeforeWriteSettings;
	bool FMapDataTypes;
	bool FEnableBCD;
	bool FForceWideString;
	bool FMarkDefsPersistent;
	void __fastcall FillSrcParams(const System::UnicodeString AConnStr);
	bool __fastcall GetSrcBool(const System::UnicodeString AName, bool &AResult);
	bool __fastcall GetSrcStr(const System::UnicodeString AName, System::UnicodeString &AResult);
	void __fastcall MergeExtendedProps();
	void __fastcall ImportSQLCommon();
	void __fastcall ImportOracle(bool AImportMode);
	void __fastcall ImportIB(bool AImportMode);
	void __fastcall ImportMSSQL(bool AImportMode);
	void __fastcall ImportMSAccess(bool AImportMode);
	void __fastcall ImportDB2(bool AImportMode);
	void __fastcall ImportASA(bool AImportMode);
	void __fastcall ImportODBC(bool AImportMode);
	void __fastcall ImportOther(bool AImportMode, const System::UnicodeString AProvider);
	Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetRDBMSKind(/* out */ System::UnicodeString &AProvider, /* out */ bool &AADDirect)/* overload */;
	System::UnicodeString __fastcall GetADDirectDriverID(const System::UnicodeString AProvider);
	
public:
	__fastcall TFDADOUDLImporter();
	__fastcall virtual ~TFDADOUDLImporter();
	bool __fastcall IsADOConnectingString(const System::UnicodeString AConnStr);
	Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetRDBMSKind(const System::UnicodeString AConnStr, /* out */ System::UnicodeString &AProvider, /* out */ bool &AADDirect)/* overload */;
	void __fastcall MakeADOCompatible(const Firedac::Stan::Intf::_di_IFDStanConnectionDef AConnectionDef);
	Firedac::Stan::Intf::_di_IFDStanConnectionDef __fastcall ImportConnStr(const System::UnicodeString AConnStr, Firedac::Stan::Intf::_di_IFDStanConnectionDefs ADefs, const System::UnicodeString ADefName = System::UnicodeString());
	Firedac::Stan::Intf::_di_IFDStanConnectionDef __fastcall ImportUDL(const System::UnicodeString AFileName, Firedac::Stan::Intf::_di_IFDStanConnectionDefs ADefs, const System::UnicodeString ADefName = System::UnicodeString());
	void __fastcall ImportAllUDLs(const System::UnicodeString AUDLPath, Firedac::Stan::Intf::_di_IFDStanConnectionDefs ADefs);
	__property System::Classes::TStrings* UDLToImport = {read=FUDLToImport};
	__property bool MapDataTypes = {read=FMapDataTypes, write=FMapDataTypes, nodefault};
	__property bool EnableBCD = {read=FEnableBCD, write=FEnableBCD, nodefault};
	__property bool ForceWideString = {read=FForceWideString, write=FForceWideString, nodefault};
	__property bool OverwriteDefs = {read=FOverwriteDefs, write=FOverwriteDefs, nodefault};
	__property bool MarkDefsPersistent = {read=FMarkDefsPersistent, write=FMarkDefsPersistent, nodefault};
	__property TFDUDLImportOverwriteEvent OnOverwrite = {read=FOnOverwrite, write=FOnOverwrite};
	__property TFDUDLImportBeforeWriteOptions OnBeforeWriteOptions = {read=FOnBeforeWriteOptions, write=FOnBeforeWriteOptions};
	__property TFDUDLImportBeforeWriteSettings OnBeforeWriteSettings = {read=FOnBeforeWriteSettings, write=FOnBeforeWriteSettings};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Import */
}	/* namespace Ado */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_ADO_IMPORT)
using namespace Firedac::Ado::Import;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_ADO)
using namespace Firedac::Ado;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Ado_ImportHPP
