﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.NexusMeta.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_NexusmetaHPP
#define Firedac_Phys_NexusmetaHPP

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
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Meta.hpp>
#include <FireDAC.Phys.SQLGenerator.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Nexusmeta
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysNexusMetadata;
class DELPHICLASS TFDPhysNexusCommandGenerator;
//-- type declarations -------------------------------------------------------
#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION TFDPhysNexusMetadata : public Firedac::Phys::Meta::TFDPhysConnectionMetadata
{
	typedef Firedac::Phys::Meta::TFDPhysConnectionMetadata inherited;
	
protected:
	virtual Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetKind();
	virtual bool __fastcall GetTxNested();
	virtual bool __fastcall GetTruncateSupported();
	virtual int __fastcall GetParamNameMaxLength();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameCaseSensParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameDefLowCaseParts();
	virtual System::WideChar __fastcall GetNameQuoteChar(Firedac::Phys::Intf::TFDPhysNameQuoteLevel AQuote, Firedac::Phys::Intf::TFDPhysNameQuoteSide ASide);
	virtual Firedac::Phys::Intf::TFDPhysParamMark __fastcall GetNamedParamMark();
	virtual bool __fastcall GetIdentityInsertSupported();
	virtual bool __fastcall GetInlineRefresh();
	virtual Firedac::Phys::Intf::TFDPhysParamMark __fastcall GetPositionedParamMark();
	virtual Firedac::Phys::Intf::TFDPhysSelectOptions __fastcall GetSelectOptions();
	virtual bool __fastcall GetAsyncAbortSupported();
	virtual Firedac::Phys::Intf::TFDPhysDefaultValues __fastcall GetDefValuesSupported();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameQuotedCaseSensParts();
	virtual Firedac::Phys::Intf::TFDPhysLimitOptions __fastcall GetLimitOptions();
	virtual Firedac::Phys::Intf::TFDPhysNullLocations __fastcall GetNullLocations();
	virtual System::UnicodeString __fastcall InternalEscapeDate(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDateTime(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFloat(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFunction(const Firedac::Phys::Intf::TFDPhysEscapeData &ASeq);
	virtual System::UnicodeString __fastcall InternalEscapeTime(const System::UnicodeString AStr);
	virtual Firedac::Phys::Intf::TFDPhysCommandKind __fastcall InternalGetSQLCommandKind(System::Classes::TStrings* const ATokens);
	
public:
	__fastcall TFDPhysNexusMetadata(Firedac::Phys::TFDPhysConnection* const AConnectionObj, unsigned __int64 AServerVersion, unsigned __int64 AClientVerison);
public:
	/* TFDPhysConnectionMetadata.Destroy */ inline __fastcall virtual ~TFDPhysNexusMetadata() { }
	
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION TFDPhysNexusCommandGenerator : public Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator
{
	typedef Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetInlineRefresh(const System::UnicodeString AStmt, Firedac::Stan::Option::TFDUpdateRequest ARequest);
	virtual System::UnicodeString __fastcall GetIdentity(bool ASessionScope);
	virtual System::UnicodeString __fastcall GetSingleRowTable();
	virtual System::UnicodeString __fastcall GetCall(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetStoredProcCall(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString APackage, const System::UnicodeString AProc, System::Word AOverload, Firedac::Phys::Intf::TFDPhysCommandKind ASPUsage);
	virtual System::UnicodeString __fastcall GetSelectMetaInfo(Firedac::Phys::Intf::TFDPhysMetaInfoKind AKind, const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ABaseObject, const System::UnicodeString AObject, const System::UnicodeString AWildcard, Firedac::Phys::Intf::TFDPhysObjectScopes AObjectScopes, Firedac::Phys::Intf::TFDPhysTableKinds ATableKinds, System::Word AOverload);
	virtual System::UnicodeString __fastcall GetLimitSelect(const System::UnicodeString ASQL, int ASkip, int ARows, Firedac::Phys::Intf::TFDPhysLimitOptions &AOptions);
protected:
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysNexusCommandGenerator()/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator() { }
	
public:
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysNexusCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand)/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator(ACommand) { }
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysNexusCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysConnection AConnection)/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator(AConnection) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDPhysNexusCommandGenerator() { }
	
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Nexusmeta */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_NEXUSMETA)
using namespace Firedac::Phys::Nexusmeta;
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
#endif	// Firedac_Phys_NexusmetaHPP
