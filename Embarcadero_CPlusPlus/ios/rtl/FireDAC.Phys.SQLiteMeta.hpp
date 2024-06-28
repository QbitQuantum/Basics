// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.SQLiteMeta.pas' rev: 34.00 (iOS)

#ifndef Firedac_Phys_SqlitemetaHPP
#define Firedac_Phys_SqlitemetaHPP

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
namespace Sqlitemeta
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IFDPhysSQLiteConnectionMetadata;
typedef System::DelphiInterface<IFDPhysSQLiteConnectionMetadata> _di_IFDPhysSQLiteConnectionMetadata;
class DELPHICLASS TFDPhysSQLiteMetadata;
class DELPHICLASS TFDPhysSQLiteCommandGenerator;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDPhysSQLiteBrand : unsigned int { sbSQLite, sbBDB };

__interface  INTERFACE_UUID("{91D454A4-327D-4ED2-8EF5-3F77BFB5B619}") IFDPhysSQLiteConnectionMetadata  : public System::IInterface 
{
	virtual TFDPhysSQLiteBrand __fastcall GetBrand() = 0 ;
	__property TFDPhysSQLiteBrand Brand = {read=GetBrand};
};

class PASCALIMPLEMENTATION TFDPhysSQLiteMetadata : public Firedac::Phys::Meta::TFDPhysConnectionMetadata
{
	typedef Firedac::Phys::Meta::TFDPhysConnectionMetadata inherited;
	
private:
	TFDPhysSQLiteBrand FBrand;
	bool FColumnOriginProvided;
	
protected:
	virtual Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetKind();
	virtual bool __fastcall GetTxSavepoints();
	virtual bool __fastcall GetEventSupported();
	virtual System::UnicodeString __fastcall GetEventKinds();
	virtual int __fastcall GetParamNameMaxLength();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameParts();
	virtual System::WideChar __fastcall GetNameQuoteChar(Firedac::Phys::Intf::TFDPhysNameQuoteLevel AQuote, Firedac::Phys::Intf::TFDPhysNameQuoteSide ASide);
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameQuotedCaseSensParts();
	virtual bool __fastcall GetNameQuotedCaseSens(const System::UnicodeString AName, Firedac::Phys::Intf::TFDPhysNamePart APart);
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameCaseSensParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameDefLowCaseParts();
	virtual bool __fastcall GetIdentityInsertSupported();
	virtual Firedac::Phys::Intf::TFDPhysParamMark __fastcall GetNamedParamMark();
	virtual Firedac::Phys::Intf::TFDPhysParamMark __fastcall GetPositionedParamMark();
	virtual Firedac::Phys::Intf::TFDPhysSelectOptions __fastcall GetSelectOptions();
	virtual bool __fastcall GetAsyncAbortSupported();
	virtual Firedac::Phys::Intf::TFDPhysArrayExecMode __fastcall GetArrayExecMode();
	virtual Firedac::Phys::Intf::TFDPhysLimitOptions __fastcall GetLimitOptions();
	virtual Firedac::Phys::Intf::TFDPhysDefaultValues __fastcall GetDefValuesSupported();
	virtual bool __fastcall GetColumnOriginProvided();
	virtual bool __fastcall GetInlineRefresh();
	virtual bool __fastcall GetTruncateSupported();
	virtual Firedac::Phys::Intf::TFDPhysCreateTableOptions __fastcall GetCreateTableOptions();
	virtual System::UnicodeString __fastcall InternalEscapeBoolean(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDate(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDateTime(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFloat(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFunction(const Firedac::Phys::Intf::TFDPhysEscapeData &ASeq);
	virtual System::UnicodeString __fastcall InternalEscapeTime(const System::UnicodeString AStr);
	virtual Firedac::Phys::Intf::TFDPhysCommandKind __fastcall InternalGetSQLCommandKind(System::Classes::TStrings* const ATokens);
	TFDPhysSQLiteBrand __fastcall GetBrand();
	
public:
	__fastcall TFDPhysSQLiteMetadata(Firedac::Phys::TFDPhysConnection* const AConnection, TFDPhysSQLiteBrand ABrand, unsigned __int64 AServerVersion, unsigned __int64 AClientVersion, bool AIsUnicode, bool AColumnOriginProvided);
public:
	/* TFDPhysConnectionMetadata.Destroy */ inline __fastcall virtual ~TFDPhysSQLiteMetadata() { }
	
private:
	void *__IFDPhysSQLiteConnectionMetadata;	// IFDPhysSQLiteConnectionMetadata 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {91D454A4-327D-4ED2-8EF5-3F77BFB5B619}
	operator _di_IFDPhysSQLiteConnectionMetadata()
	{
		_di_IFDPhysSQLiteConnectionMetadata intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IFDPhysSQLiteConnectionMetadata*(void) { return (IFDPhysSQLiteConnectionMetadata*)&__IFDPhysSQLiteConnectionMetadata; }
	#endif
	
};


class PASCALIMPLEMENTATION TFDPhysSQLiteCommandGenerator : public Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator
{
	typedef Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetIdentity(bool ASessionScope);
	virtual System::UnicodeString __fastcall GetRowId(System::UnicodeString &AAlias);
	virtual System::UnicodeString __fastcall GetReadGenerator(const System::UnicodeString AName, const System::UnicodeString AAlias, bool ANextValue, bool AFullSelect);
	virtual System::UnicodeString __fastcall GetInlineRefresh(const System::UnicodeString AStmt, Firedac::Stan::Option::TFDUpdateRequest ARequest);
	virtual System::UnicodeString __fastcall GetCommitSavepoint(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetRollbackToSavepoint(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetSavepoint(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetCall(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetSelectMetaInfo(Firedac::Phys::Intf::TFDPhysMetaInfoKind AKind, const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ABaseObject, const System::UnicodeString AObject, const System::UnicodeString AWildcard, Firedac::Phys::Intf::TFDPhysObjectScopes AObjectScopes, Firedac::Phys::Intf::TFDPhysTableKinds ATableKinds, System::Word AOverload);
	virtual System::UnicodeString __fastcall GetLimitSelect(const System::UnicodeString ASQL, int ASkip, int ARows, Firedac::Phys::Intf::TFDPhysLimitOptions &AOptions);
	virtual System::UnicodeString __fastcall GetColumnType(Firedac::Dats::TFDDatSColumn* AColumn);
	virtual System::UnicodeString __fastcall GetMerge(Firedac::Phys::Intf::TFDPhysMergeAction AAction);
protected:
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysSQLiteCommandGenerator()/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator() { }
	
public:
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysSQLiteCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand)/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator(ACommand) { }
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysSQLiteCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysConnection AConnection)/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator(AConnection) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDPhysSQLiteCommandGenerator() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sqlitemeta */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_SQLITEMETA)
using namespace Firedac::Phys::Sqlitemeta;
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
#endif	// Firedac_Phys_SqlitemetaHPP
