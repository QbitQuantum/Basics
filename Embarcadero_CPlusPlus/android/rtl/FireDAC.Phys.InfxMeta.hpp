// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.InfxMeta.pas' rev: 34.00 (Android)

#ifndef Firedac_Phys_InfxmetaHPP
#define Firedac_Phys_InfxmetaHPP

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
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Meta.hpp>
#include <FireDAC.Phys.SQLGenerator.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Infxmeta
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysInfxMetadata;
class DELPHICLASS TFDPhysInfxCommandGenerator;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysInfxMetadata : public Firedac::Phys::Meta::TFDPhysConnectionMetadata
{
	typedef Firedac::Phys::Meta::TFDPhysConnectionMetadata inherited;
	
private:
	bool FTxSupported;
	
protected:
	virtual Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetKind();
	virtual bool __fastcall GetIdentityInsertSupported();
	virtual System::WideChar __fastcall GetCatalogSeparator();
	virtual bool __fastcall GetGeneratorSupported();
	virtual bool __fastcall GetTxSupported();
	virtual bool __fastcall GetTxSavepoints();
	virtual bool __fastcall GetEventSupported();
	virtual System::UnicodeString __fastcall GetEventKinds();
	virtual int __fastcall GetParamNameMaxLength();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameDefLowCaseParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameCaseSensParts();
	virtual Firedac::Phys::Intf::TFDPhysDefaultValues __fastcall GetDefValuesSupported();
	virtual Firedac::Phys::Intf::TFDPhysSelectOptions __fastcall GetSelectOptions();
	virtual bool __fastcall GetAsyncAbortSupported();
	virtual bool __fastcall GetAsyncNativeTimeout();
	virtual Firedac::Phys::Intf::TFDPhysArrayExecMode __fastcall GetArrayExecMode();
	virtual Firedac::Phys::Intf::TFDPhysLimitOptions __fastcall GetLimitOptions();
	virtual bool __fastcall GetColumnOriginProvided();
	virtual System::UnicodeString __fastcall InternalEscapeBoolean(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDate(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDateTime(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFloat(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFunction(const Firedac::Phys::Intf::TFDPhysEscapeData &ASeq);
	virtual System::UnicodeString __fastcall InternalEscapeTime(const System::UnicodeString AStr);
	virtual Firedac::Phys::Intf::TFDPhysCommandKind __fastcall InternalGetSQLCommandKind(System::Classes::TStrings* const ATokens);
	
public:
	__fastcall TFDPhysInfxMetadata(Firedac::Phys::TFDPhysConnection* const AConnectionObj, unsigned __int64 AServerVersion, unsigned __int64 AClientVersion, const System::UnicodeString ACSVKeywords, bool AIsUnicode, bool ATxSupported);
public:
	/* TFDPhysConnectionMetadata.Destroy */ inline __fastcall virtual ~TFDPhysInfxMetadata() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysInfxCommandGenerator : public Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator
{
	typedef Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetIdentity(bool ASessionScope);
	virtual System::UnicodeString __fastcall GetReadGenerator(const System::UnicodeString AName, const System::UnicodeString AAlias, bool ANextValue, bool AFullSelect);
	virtual System::UnicodeString __fastcall GetSingleRowTable();
	virtual System::UnicodeString __fastcall GetRowId(System::UnicodeString &AAlias);
	virtual System::UnicodeString __fastcall GetPessimisticLock();
	virtual System::UnicodeString __fastcall GetSavepoint(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetRollbackToSavepoint(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetCommitSavepoint(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetCall(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetLimitSelect(const System::UnicodeString ASQL, int ASkip, int ARows, Firedac::Phys::Intf::TFDPhysLimitOptions &AOptions);
	virtual System::UnicodeString __fastcall GetColumnType(Firedac::Dats::TFDDatSColumn* AColumn);
protected:
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysInfxCommandGenerator()/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator() { }
	
public:
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysInfxCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand)/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator(ACommand) { }
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysInfxCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysConnection AConnection)/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator(AConnection) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDPhysInfxCommandGenerator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Infxmeta */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_INFXMETA)
using namespace Firedac::Phys::Infxmeta;
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
#endif	// Firedac_Phys_InfxmetaHPP
