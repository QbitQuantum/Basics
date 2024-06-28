// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.DSMeta.pas' rev: 34.00 (Android)

#ifndef Firedac_Phys_DsmetaHPP
#define Firedac_Phys_DsmetaHPP

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

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Dsmeta
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysDSMetadata;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysDSMetadata : public Firedac::Phys::Meta::TFDPhysConnectionMetadata
{
	typedef Firedac::Phys::Meta::TFDPhysConnectionMetadata inherited;
	
protected:
	virtual Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetKind();
	virtual bool __fastcall GetTxSupported();
	virtual bool __fastcall GetEventSupported();
	virtual System::UnicodeString __fastcall GetEventKinds();
	virtual int __fastcall GetParamNameMaxLength();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameCaseSensParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameQuotedCaseSensParts();
	virtual System::WideChar __fastcall GetNameQuoteChar(Firedac::Phys::Intf::TFDPhysNameQuoteLevel AQuote, Firedac::Phys::Intf::TFDPhysNameQuoteSide ASide);
	virtual bool __fastcall GetIdentitySupported();
	virtual Firedac::Phys::Intf::TFDPhysParamMark __fastcall GetNamedParamMark();
	virtual bool __fastcall GetAsyncAbortSupported();
	virtual Firedac::Phys::Intf::TFDPhysLimitOptions __fastcall GetLimitOptions();
	virtual bool __fastcall GetServerCursorSupported();
	virtual bool __fastcall GetColumnOriginProvided();
	virtual bool __fastcall GetTruncateSupported();
	virtual Firedac::Phys::Intf::TFDPhysDefaultValues __fastcall GetDefValuesSupported();
	virtual Firedac::Phys::Intf::TFDPhysCommandKind __fastcall InternalGetSQLCommandKind(System::Classes::TStrings* const ATokens);
	
public:
	__fastcall TFDPhysDSMetadata(Firedac::Phys::TFDPhysConnection* const AConnectionObj, unsigned __int64 AServerVersion, unsigned __int64 AClientVersion, bool AIsUnicode);
public:
	/* TFDPhysConnectionMetadata.Destroy */ inline __fastcall virtual ~TFDPhysDSMetadata() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dsmeta */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_DSMETA)
using namespace Firedac::Phys::Dsmeta;
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
#endif	// Firedac_Phys_DsmetaHPP
