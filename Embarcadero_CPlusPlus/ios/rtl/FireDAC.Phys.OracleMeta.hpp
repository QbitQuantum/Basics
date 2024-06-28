// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.OracleMeta.pas' rev: 34.00 (iOS)

#ifndef Firedac_Phys_OraclemetaHPP
#define Firedac_Phys_OraclemetaHPP

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
namespace Oraclemeta
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysOraMetadata;
class DELPHICLASS TFDPhysOraCommandGenerator;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysOraMetadata : public Firedac::Phys::Meta::TFDPhysConnectionMetadata
{
	typedef Firedac::Phys::Meta::TFDPhysConnectionMetadata inherited;
	
protected:
	virtual Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetKind();
	virtual bool __fastcall GetTxSavepoints();
	virtual bool __fastcall GetEventSupported();
	virtual System::UnicodeString __fastcall GetEventKinds();
	virtual bool __fastcall GetGeneratorSupported();
	virtual bool __fastcall GetIdentitySupported();
	virtual bool __fastcall GetIdentityInsertSupported();
	virtual bool __fastcall GetIdentityInWhere();
	virtual int __fastcall GetParamNameMaxLength();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameCaseSensParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameDefLowCaseParts();
	virtual Firedac::Phys::Intf::TFDPhysInsertHBlobMode __fastcall GetInsertHBlobMode();
	virtual Firedac::Phys::Intf::TFDPhysParamMark __fastcall GetNamedParamMark();
	virtual bool __fastcall GetInlineRefresh();
	virtual Firedac::Phys::Intf::TFDPhysSelectOptions __fastcall GetSelectOptions();
	virtual bool __fastcall GetAsyncAbortSupported();
	virtual bool __fastcall GetLockNoWait();
	virtual Firedac::Phys::Intf::TFDPhysDefaultValues __fastcall GetDefValuesSupported();
	virtual Firedac::Stan::Intf::TFDTextEndOfLine __fastcall GetLineSeparator();
	virtual Firedac::Phys::Intf::TFDPhysLimitOptions __fastcall GetLimitOptions();
	virtual Firedac::Phys::Intf::TFDPhysNullLocations __fastcall GetNullLocations();
	virtual bool __fastcall GetColumnOriginProvided();
	virtual System::UnicodeString __fastcall InternalEscapeBoolean(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDate(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDateTime(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFloat(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFunction(const Firedac::Phys::Intf::TFDPhysEscapeData &ASeq);
	virtual System::UnicodeString __fastcall InternalEscapeTime(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeInto(const System::UnicodeString AStr);
	virtual Firedac::Phys::Intf::TFDPhysCommandKind __fastcall InternalGetSQLCommandKind(System::Classes::TStrings* const ATokens);
	
public:
	__fastcall TFDPhysOraMetadata(Firedac::Phys::TFDPhysConnection* const AConnection, unsigned __int64 AServerVersion, unsigned __int64 AClientVersion, bool AIsUnicode);
public:
	/* TFDPhysConnectionMetadata.Destroy */ inline __fastcall virtual ~TFDPhysOraMetadata() { }
	
};


class PASCALIMPLEMENTATION TFDPhysOraCommandGenerator : public Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator
{
	typedef Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator inherited;
	
private:
	bool FUseDBAViews;
	
protected:
	virtual System::UnicodeString __fastcall GetInlineRefresh(const System::UnicodeString AStmt, Firedac::Stan::Option::TFDUpdateRequest ARequest);
	virtual System::UnicodeString __fastcall GetPessimisticLock();
	virtual System::UnicodeString __fastcall GetSavepoint(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetRollbackToSavepoint(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetReadGenerator(const System::UnicodeString AName, const System::UnicodeString AAlias, bool ANextValue, bool AFullSelect);
	virtual System::UnicodeString __fastcall GetSingleRowTable();
	virtual System::UnicodeString __fastcall GetRowId(System::UnicodeString &AAlias);
	virtual System::UnicodeString __fastcall GetCall(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetStoredProcCall(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString APackage, const System::UnicodeString AProc, System::Word AOverload, Firedac::Phys::Intf::TFDPhysCommandKind ASPUsage);
	virtual System::UnicodeString __fastcall GetSelectMetaInfo(Firedac::Phys::Intf::TFDPhysMetaInfoKind AKind, const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ABaseObject, const System::UnicodeString AObject, const System::UnicodeString AWildcard, Firedac::Phys::Intf::TFDPhysObjectScopes AObjectScopes, Firedac::Phys::Intf::TFDPhysTableKinds ATableKinds, System::Word AOverload);
	virtual System::UnicodeString __fastcall GetLimitSelect(const System::UnicodeString ASQL, int ASkip, int ARows, Firedac::Phys::Intf::TFDPhysLimitOptions &AOptions);
	virtual System::UnicodeString __fastcall GetColumnType(Firedac::Dats::TFDDatSColumn* AColumn);
	virtual System::UnicodeString __fastcall GetCreateGenerator(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetDropGenerator(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetCreateIdentityTrigger();
	
public:
	__fastcall TFDPhysOraCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand, bool AUseDBAViews)/* overload */;
	__fastcall TFDPhysOraCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysConnection AConnection, bool AUseDBAViews)/* overload */;
protected:
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysOraCommandGenerator()/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator() { }
	
public:
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysOraCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand)/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator(ACommand) { }
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysOraCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysConnection AConnection)/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator(AConnection) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDPhysOraCommandGenerator() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Oraclemeta */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ORACLEMETA)
using namespace Firedac::Phys::Oraclemeta;
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
#endif	// Firedac_Phys_OraclemetaHPP
