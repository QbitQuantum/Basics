// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.MSAccMeta.pas' rev: 34.00 (Android)

#ifndef Firedac_Phys_MsaccmetaHPP
#define Firedac_Phys_MsaccmetaHPP

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
namespace Msaccmeta
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysMSAccMetadata;
class DELPHICLASS TFDPhysMSAccCommandGenerator;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysMSAccMetadata : public Firedac::Phys::Meta::TFDPhysConnectionMetadata
{
	typedef Firedac::Phys::Meta::TFDPhysConnectionMetadata inherited;
	
protected:
	virtual Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetKind();
	virtual int __fastcall GetParamNameMaxLength();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameQuotedCaseSensParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameCaseSensParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameDefLowCaseParts();
	virtual System::WideChar __fastcall GetNameQuoteChar(Firedac::Phys::Intf::TFDPhysNameQuoteLevel AQuote, Firedac::Phys::Intf::TFDPhysNameQuoteSide ASide);
	virtual bool __fastcall GetTruncateSupported();
	virtual bool __fastcall GetIdentityInsertSupported();
	virtual bool __fastcall GetIdentityInWhere();
	virtual Firedac::Phys::Intf::TFDPhysDefaultValues __fastcall GetDefValuesSupported();
	virtual bool __fastcall GetAsyncAbortSupported();
	virtual Firedac::Phys::Intf::TFDPhysSelectOptions __fastcall GetSelectOptions();
	virtual System::UnicodeString __fastcall InternalEscapeBoolean(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDate(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDateTime(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFloat(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFunction(const Firedac::Phys::Intf::TFDPhysEscapeData &ASeq);
	virtual System::UnicodeString __fastcall InternalEscapeTime(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeEscape(System::WideChar AEscape, const System::UnicodeString AStr);
	virtual Firedac::Phys::Intf::TFDPhysCommandKind __fastcall InternalGetSQLCommandKind(System::Classes::TStrings* const ATokens);
	virtual bool __fastcall IsNameValid(const System::UnicodeString AName);
	
public:
	__fastcall TFDPhysMSAccMetadata(Firedac::Phys::TFDPhysConnection* const AConnectionObj, unsigned __int64 AServerVersion, unsigned __int64 AClientVersion, const System::UnicodeString ACSVKeywords);
public:
	/* TFDPhysConnectionMetadata.Destroy */ inline __fastcall virtual ~TFDPhysMSAccMetadata() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysMSAccCommandGenerator : public Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator
{
	typedef Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetStoredProcCall(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString APackage, const System::UnicodeString AProc, System::Word AOverload, Firedac::Phys::Intf::TFDPhysCommandKind ASPUsage);
	virtual System::UnicodeString __fastcall GetIdentity(bool ASessionScope);
	virtual System::UnicodeString __fastcall GetColumnType(Firedac::Dats::TFDDatSColumn* AColumn);
protected:
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysMSAccCommandGenerator()/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator() { }
	
public:
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysMSAccCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand)/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator(ACommand) { }
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysMSAccCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysConnection AConnection)/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator(AConnection) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDPhysMSAccCommandGenerator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Msaccmeta */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_MSACCMETA)
using namespace Firedac::Phys::Msaccmeta;
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
#endif	// Firedac_Phys_MsaccmetaHPP
