// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.ASAMeta.pas' rev: 34.00 (Android)

#ifndef Firedac_Phys_AsametaHPP
#define Firedac_Phys_AsametaHPP

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
#include <FireDAC.Phys.Meta.hpp>
#include <FireDAC.Phys.SQLGenerator.hpp>
#include <FireDAC.Phys.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Asameta
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysASAMetadata;
class DELPHICLASS TFDPhysASAMetadataExt;
class DELPHICLASS TFDPhysASACommandGenerator;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysASAMetadata : public Firedac::Phys::Meta::TFDPhysConnectionMetadata
{
	typedef Firedac::Phys::Meta::TFDPhysConnectionMetadata inherited;
	
protected:
	virtual Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetKind();
	virtual bool __fastcall GetTxSavepoints();
	virtual System::UnicodeString __fastcall GetEventKinds();
	virtual bool __fastcall GetEventSupported();
	virtual int __fastcall GetParamNameMaxLength();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameQuotedCaseSensParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameCaseSensParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameDefLowCaseParts();
	virtual bool __fastcall GetIdentityInsertSupported();
	virtual Firedac::Phys::Intf::TFDPhysDefaultValues __fastcall GetDefValuesSupported();
	virtual bool __fastcall GetAsyncAbortSupported();
	virtual Firedac::Phys::Intf::TFDPhysLimitOptions __fastcall GetLimitOptions();
	virtual Firedac::Phys::Intf::TFDPhysSelectOptions __fastcall GetSelectOptions();
	virtual bool __fastcall GetBackslashEscSupported();
	virtual System::UnicodeString __fastcall InternalEscapeBoolean(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDate(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDateTime(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFloat(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFunction(const Firedac::Phys::Intf::TFDPhysEscapeData &ASeq);
	virtual System::UnicodeString __fastcall InternalEscapeTime(const System::UnicodeString AStr);
	virtual Firedac::Phys::Intf::TFDPhysCommandKind __fastcall InternalGetSQLCommandKind(System::Classes::TStrings* const ATokens);
	
public:
	__fastcall TFDPhysASAMetadata(Firedac::Phys::TFDPhysConnection* const AConnectionObj, unsigned __int64 AServerVersion, unsigned __int64 AClientVerison, const System::UnicodeString ACSVKeywords);
public:
	/* TFDPhysConnectionMetadata.Destroy */ inline __fastcall virtual ~TFDPhysASAMetadata() { }
	
};


class PASCALIMPLEMENTATION TFDPhysASAMetadataExt : public TFDPhysASAMetadata
{
	typedef TFDPhysASAMetadata inherited;
	
private:
	bool FSchemaCaseSensitive;
	Firedac::Phys::Intf::TFDPhysNameParts FCaseSensParts;
	
protected:
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameQuotedCaseSensParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameCaseSensParts();
	
public:
	__fastcall TFDPhysASAMetadataExt(Firedac::Phys::TFDPhysConnection* const AConnectionObj, bool ASchemaCaseSensitive, unsigned __int64 AServerVersion, unsigned __int64 AClientVerison, const System::UnicodeString ACSVKeywords);
public:
	/* TFDPhysConnectionMetadata.Destroy */ inline __fastcall virtual ~TFDPhysASAMetadataExt() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysASACommandGenerator : public Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator
{
	typedef Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetIdentity(bool ASessionScope);
	virtual System::UnicodeString __fastcall GetPessimisticLock();
	virtual System::UnicodeString __fastcall GetSavepoint(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetRollbackToSavepoint(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetCall(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetLimitSelect(const System::UnicodeString ASQL, int ASkip, int ARows, Firedac::Phys::Intf::TFDPhysLimitOptions &AOptions);
	virtual System::UnicodeString __fastcall GetColumnType(Firedac::Dats::TFDDatSColumn* AColumn);
	virtual System::UnicodeString __fastcall GetMerge(Firedac::Phys::Intf::TFDPhysMergeAction AAction);
protected:
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysASACommandGenerator()/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator() { }
	
public:
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysASACommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand)/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator(ACommand) { }
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysASACommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysConnection AConnection)/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator(AConnection) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDPhysASACommandGenerator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Asameta */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ASAMETA)
using namespace Firedac::Phys::Asameta;
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
#endif	// Firedac_Phys_AsametaHPP
