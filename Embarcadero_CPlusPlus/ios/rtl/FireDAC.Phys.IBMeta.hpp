// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.IBMeta.pas' rev: 34.00 (iOS)

#ifndef Firedac_Phys_IbmetaHPP
#define Firedac_Phys_IbmetaHPP

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
#include <FireDAC.Stan.Consts.hpp>
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
namespace Ibmeta
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IFDPhysIBConnectionMetadata;
typedef System::DelphiInterface<IFDPhysIBConnectionMetadata> _di_IFDPhysIBConnectionMetadata;
class DELPHICLASS TFDPhysIBMetadata;
class DELPHICLASS TFDPhysIBCommandGenerator;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDPhysIBBrand : unsigned int { ibInterbase, ibFirebird, ibYaffil };

__interface  INTERFACE_UUID("{898D228C-56E3-4D34-9AA4-B1DC613CE57A}") IFDPhysIBConnectionMetadata  : public System::IInterface 
{
	virtual TFDPhysIBBrand __fastcall GetBrand() = 0 ;
	virtual int __fastcall GetDialect() = 0 ;
	__property TFDPhysIBBrand Brand = {read=GetBrand};
	__property int Dialect = {read=GetDialect};
};

class PASCALIMPLEMENTATION TFDPhysIBMetadata : public Firedac::Phys::Meta::TFDPhysConnectionMetadata
{
	typedef Firedac::Phys::Meta::TFDPhysConnectionMetadata inherited;
	
private:
	TFDPhysIBBrand FBrand;
	int FDialect;
	
protected:
	virtual Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetKind();
	virtual bool __fastcall GetTxMultiple();
	virtual bool __fastcall GetTxSavepoints();
	virtual bool __fastcall GetEventSupported();
	virtual System::UnicodeString __fastcall GetEventKinds();
	virtual bool __fastcall GetGeneratorSupported();
	virtual bool __fastcall GetTruncateSupported();
	virtual bool __fastcall GetIdentitySupported();
	virtual bool __fastcall GetIdentityInsertSupported();
	virtual int __fastcall GetParamNameMaxLength();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameQuotedCaseSensParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameCaseSensParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameDefLowCaseParts();
	virtual System::WideChar __fastcall GetNameQuoteChar(Firedac::Phys::Intf::TFDPhysNameQuoteLevel AQuote, Firedac::Phys::Intf::TFDPhysNameQuoteSide ASide);
	virtual bool __fastcall GetInlineRefresh();
	virtual Firedac::Phys::Intf::TFDPhysSelectOptions __fastcall GetSelectOptions();
	virtual bool __fastcall GetAsyncAbortSupported();
	virtual Firedac::Stan::Intf::TFDTextEndOfLine __fastcall GetLineSeparator();
	virtual bool __fastcall GetLockNoWait();
	virtual Firedac::Phys::Intf::TFDPhysDefaultValues __fastcall GetDefValuesSupported();
	virtual Firedac::Phys::Intf::TFDPhysArrayExecMode __fastcall GetArrayExecMode();
	virtual Firedac::Phys::Intf::TFDPhysLimitOptions __fastcall GetLimitOptions();
	virtual Firedac::Phys::Intf::TFDPhysNullLocations __fastcall GetNullLocations();
	virtual void __fastcall DefineMetadataStructure(Firedac::Dats::TFDDatSTable* ATable, Firedac::Phys::Intf::TFDPhysMetaInfoKind AKind);
	virtual Firedac::Dats::TFDDatSView* __fastcall GetResultSetFields(const System::UnicodeString ASQLKey);
	virtual System::UnicodeString __fastcall InternalEscapeBoolean(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDate(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDateTime(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFloat(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFunction(const Firedac::Phys::Intf::TFDPhysEscapeData &ASeq);
	virtual System::UnicodeString __fastcall InternalEscapeTime(const System::UnicodeString AStr);
	virtual Firedac::Phys::Intf::TFDPhysCommandKind __fastcall InternalGetSQLCommandKind(System::Classes::TStrings* const ATokens);
	TFDPhysIBBrand __fastcall GetBrand();
	int __fastcall GetDialect();
	
public:
	__fastcall TFDPhysIBMetadata(Firedac::Phys::TFDPhysConnection* const AConnection, TFDPhysIBBrand ABrand, unsigned __int64 AServerVersion, unsigned __int64 AClientVersion, int ADialect, bool AIsUnicode);
public:
	/* TFDPhysConnectionMetadata.Destroy */ inline __fastcall virtual ~TFDPhysIBMetadata() { }
	
private:
	void *__IFDPhysIBConnectionMetadata;	// IFDPhysIBConnectionMetadata 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {898D228C-56E3-4D34-9AA4-B1DC613CE57A}
	operator _di_IFDPhysIBConnectionMetadata()
	{
		_di_IFDPhysIBConnectionMetadata intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IFDPhysIBConnectionMetadata*(void) { return (IFDPhysIBConnectionMetadata*)&__IFDPhysIBConnectionMetadata; }
	#endif
	
};


class PASCALIMPLEMENTATION TFDPhysIBCommandGenerator : public Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator
{
	typedef Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator inherited;
	
private:
	int FIDUTF8;
	Firedac::Stan::Intf::TFDEncoding FEncoding;
	
protected:
	virtual System::UnicodeString __fastcall GetInlineRefresh(const System::UnicodeString AStmt, Firedac::Stan::Option::TFDUpdateRequest ARequest);
	virtual System::UnicodeString __fastcall GetPessimisticLock();
	virtual System::UnicodeString __fastcall GetSavepoint(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetRollbackToSavepoint(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetCommitSavepoint(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetReadGenerator(const System::UnicodeString AName, const System::UnicodeString AAlias, bool ANextValue, bool AFullSelect);
	virtual System::UnicodeString __fastcall GetSingleRowTable();
	virtual System::UnicodeString __fastcall GetRowId(System::UnicodeString &AAlias);
	virtual System::UnicodeString __fastcall GetCall(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetStoredProcCall(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString APackage, const System::UnicodeString AProc, System::Word AOverload, Firedac::Phys::Intf::TFDPhysCommandKind ASPUsage);
	virtual System::UnicodeString __fastcall GetSelectMetaInfo(Firedac::Phys::Intf::TFDPhysMetaInfoKind AKind, const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ABaseObject, const System::UnicodeString AObject, const System::UnicodeString AWildcard, Firedac::Phys::Intf::TFDPhysObjectScopes AObjectScopes, Firedac::Phys::Intf::TFDPhysTableKinds ATableKinds, System::Word AOverload);
	virtual System::UnicodeString __fastcall GetLimitSelect(const System::UnicodeString ASQL, int ASkip, int ARows, Firedac::Phys::Intf::TFDPhysLimitOptions &AOptions);
	virtual System::UnicodeString __fastcall GetCountSelect(const System::UnicodeString ASQL);
	virtual System::UnicodeString __fastcall GetColumnType(Firedac::Dats::TFDDatSColumn* AColumn);
	virtual System::UnicodeString __fastcall GetCreateGenerator(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetDropGenerator(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetCreateIdentityTrigger();
	virtual System::UnicodeString __fastcall GetMerge(Firedac::Phys::Intf::TFDPhysMergeAction AAction);
	
public:
	__fastcall TFDPhysIBCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand, int AIDUTF8, Firedac::Stan::Intf::TFDEncoding AEncoding)/* overload */;
	__fastcall TFDPhysIBCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysConnection AConnection, int AIDUTF8, Firedac::Stan::Intf::TFDEncoding AEncoding)/* overload */;
protected:
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysIBCommandGenerator()/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator() { }
	
public:
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysIBCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand)/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator(ACommand) { }
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysIBCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysConnection AConnection)/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator(AConnection) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDPhysIBCommandGenerator() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 csIDNone = System::Int8(0x0);
static constexpr System::Int8 csIDOctets = System::Int8(0x1);
static constexpr System::Int8 csIDUnicodeFSS = System::Int8(0x3);
static constexpr System::Int8 csIDFBUtf8 = System::Int8(0x4);
static constexpr System::Int8 csIDUnicodeBE = System::Int8(0x8);
static constexpr System::Int8 csIDIBUtf8 = System::Int8(0x3b);
static constexpr System::Int8 csIDUnicodeLE = System::Int8(0x40);
}	/* namespace Ibmeta */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_IBMETA)
using namespace Firedac::Phys::Ibmeta;
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
#endif	// Firedac_Phys_IbmetaHPP
