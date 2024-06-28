// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.ODBCMeta.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_OdbcmetaHPP
#define Firedac_Phys_OdbcmetaHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Meta.hpp>
#include <FireDAC.Phys.ODBCBase.hpp>
#include <FireDAC.Phys.ODBCCli.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Odbcmeta
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysODBCMetadata;
class DELPHICLASS TFDPhysODBCMetadataExt;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysODBCMetadata : public Firedac::Phys::Meta::TFDPhysConnectionMetadata
{
	typedef Firedac::Phys::Meta::TFDPhysConnectionMetadata inherited;
	
	
private:
	class DELPHICLASS __TFDPhysConnectionMetadata;
	class PASCALIMPLEMENTATION __TFDPhysConnectionMetadata : public Firedac::Phys::Meta::TFDPhysConnectionMetadata
	{
		typedef Firedac::Phys::Meta::TFDPhysConnectionMetadata inherited;
		
	public:
		/* TFDPhysConnectionMetadata.Create */ inline __fastcall __TFDPhysConnectionMetadata(Firedac::Phys::TFDPhysConnection* const AConnectionObj, unsigned __int64 AServerVersion, unsigned __int64 AClientVersion, bool AIsUnicode) : Firedac::Phys::Meta::TFDPhysConnectionMetadata(AConnectionObj, AServerVersion, AClientVersion, AIsUnicode) { }
		/* TFDPhysConnectionMetadata.Destroy */ inline __fastcall virtual ~__TFDPhysConnectionMetadata() { }
		
	};
	
	
	
private:
	int FNameMaxLength;
	System::WideChar FNameQuoteChar;
	System::WideChar FNameQuoteChar1;
	System::WideChar FNameQuoteChar2;
	bool FTxNested;
	bool FTxSupported;
	bool FQuotedCatSchSupported;
	System::Word FQuotedIdentifierCase;
	System::Word FIdentifierCase;
	int FCatalogUsage;
	int FSchemaUsage;
	bool FCancelSupported;
	System::WideChar FCatalogSeparator;
	Firedac::Phys::Intf::TFDPhysNullLocations FNullLocations;
	bool FIsFileBased;
	__TFDPhysConnectionMetadata* FParentMeta;
	
protected:
	virtual HRESULT __stdcall QueryInterface(const GUID &IID, /* out */ void *Obj);
	virtual bool __fastcall GetAsyncAbortSupported();
	virtual bool __fastcall GetAsyncNativeTimeout();
	virtual System::UnicodeString __fastcall GetCommandSeparator();
	virtual Firedac::Phys::Intf::TFDPhysDefaultValues __fastcall GetDefValuesSupported();
	virtual bool __fastcall GetIdentityInsertSupported();
	virtual bool __fastcall GetInlineRefresh();
	virtual Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetKind();
	virtual bool __fastcall GetIsFileBased();
	virtual bool __fastcall GetLockNoWait();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameCaseSensParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameDefLowCaseParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameParts();
	virtual System::WideChar __fastcall GetNameQuoteChar(Firedac::Phys::Intf::TFDPhysNameQuoteLevel AQuote, Firedac::Phys::Intf::TFDPhysNameQuoteSide ASide);
	virtual System::WideChar __fastcall GetCatalogSeparator();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameQuotedSupportedParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameQuotedCaseSensParts();
	virtual int __fastcall GetParamNameMaxLength();
	virtual Firedac::Phys::Intf::TFDPhysSelectOptions __fastcall GetSelectOptions();
	virtual bool __fastcall GetTruncateSupported();
	virtual bool __fastcall GetTxAutoCommit();
	virtual bool __fastcall GetTxNested();
	virtual bool __fastcall GetTxSavepoints();
	virtual bool __fastcall GetTxSupported();
	virtual Firedac::Phys::Intf::TFDPhysLimitOptions __fastcall GetLimitOptions();
	virtual Firedac::Phys::Intf::TFDPhysNullLocations __fastcall GetNullLocations();
	virtual bool __fastcall GetColumnOriginProvided();
	virtual bool __fastcall InternalDecodeObjName(const System::UnicodeString AName, /* out */ Firedac::Phys::Intf::TFDPhysParsedName &AParsedName, const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand, bool ARaise);
	virtual System::UnicodeString __fastcall InternalEncodeObjName(const Firedac::Phys::Intf::TFDPhysParsedName &AParsedName, const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand);
	virtual Firedac::Phys::Intf::TFDPhysCommandKind __fastcall InternalGetSQLCommandKind(System::Classes::TStrings* const ATokens);
	virtual System::UnicodeString __fastcall InternalEscapeDate(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDateTime(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeTime(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFunction(const Firedac::Phys::Intf::TFDPhysEscapeData &ASeq);
	virtual System::UnicodeString __fastcall TranslateEscapeSequence(Firedac::Phys::Intf::TFDPhysEscapeData &ASeq);
	
public:
	__fastcall TFDPhysODBCMetadata(Firedac::Phys::TFDPhysConnection* const AConnection, unsigned __int64 AServerVersion, unsigned __int64 AClientVersion, Firedac::Phys::Meta::TFDPhysConnectionMetadata* AParentMeta);
	__fastcall virtual ~TFDPhysODBCMetadata();
};


class PASCALIMPLEMENTATION TFDPhysODBCMetadataExt : public TFDPhysODBCMetadata
{
	typedef TFDPhysODBCMetadata inherited;
	
protected:
	virtual bool __fastcall IsNameValid(const System::UnicodeString AName);
public:
	/* TFDPhysODBCMetadata.Create */ inline __fastcall TFDPhysODBCMetadataExt(Firedac::Phys::TFDPhysConnection* const AConnection, unsigned __int64 AServerVersion, unsigned __int64 AClientVersion, Firedac::Phys::Meta::TFDPhysConnectionMetadata* AParentMeta) : TFDPhysODBCMetadata(AConnection, AServerVersion, AClientVersion, AParentMeta) { }
	/* TFDPhysODBCMetadata.Destroy */ inline __fastcall virtual ~TFDPhysODBCMetadataExt() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Odbcmeta */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ODBCMETA)
using namespace Firedac::Phys::Odbcmeta;
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
#endif	// Firedac_Phys_OdbcmetaHPP
