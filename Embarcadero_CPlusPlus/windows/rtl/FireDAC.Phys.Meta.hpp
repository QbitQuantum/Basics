// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.Meta.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_MetaHPP
#define Firedac_Phys_MetaHPP

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

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Meta
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysConnectionMetadata;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysConnectionMetadata : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
private:
	typedef System::DynamicArray<System::UnicodeString> _TFDPhysConnectionMetadata__1;
	
	
private:
	Firedac::Dats::TFDDatSManager* FMetadataCache;
	int FMaximumNameParts;
	_TFDPhysConnectionMetadata__1 FNameParts;
	unsigned __int64 FServerVersion;
	unsigned __int64 FClientVersion;
	bool FIsUnicode;
	Firedac::Stan::Intf::TFDByteSet FQuoteChars;
	System::UnicodeString __fastcall UnQuoteBase(const System::UnicodeString AName, System::WideChar ACh1, System::WideChar ACh2);
	bool __fastcall IsQuotedBase(const System::UnicodeString AName, System::WideChar ACh1, System::WideChar ACh2);
	bool __fastcall IsNameQuoted(const System::UnicodeString AName);
	System::UnicodeString __fastcall NormObjName(const System::UnicodeString AName, Firedac::Phys::Intf::TFDPhysNamePart APart);
	System::UnicodeString __fastcall QuoteNameIfReq(const System::UnicodeString AName, Firedac::Phys::Intf::TFDPhysNamePart APart);
	bool __fastcall IsRDBMSKind(const System::UnicodeString AStr, /* out */ bool &ACurrent);
	Firedac::Dats::TFDDatSTable* __fastcall FetchNoCache(Firedac::Phys::Intf::TFDPhysMetaInfoKind AMetaKind, Firedac::Phys::Intf::TFDPhysObjectScopes AScope, Firedac::Phys::Intf::TFDPhysTableKinds AKinds, const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ABaseObject, const System::UnicodeString AWildCard, System::Word AOverload);
	bool __fastcall CheckFetchToCache(Firedac::Phys::Intf::TFDPhysMetaInfoKind AMetaKind, const System::UnicodeString AFilter, Firedac::Dats::TFDDatSTable* &ATable, Firedac::Dats::TFDDatSView* &AView);
	void __fastcall AddWildcard(Firedac::Dats::TFDDatSView* AView, const System::UnicodeString AColumn, const System::UnicodeString AWildcard, Firedac::Phys::Intf::TFDPhysNamePart APart);
	void __fastcall FetchToCache(Firedac::Phys::Intf::TFDPhysMetaInfoKind AMetaKind, const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ABaseObject, const System::UnicodeString AObject, System::Word AOverload, Firedac::Dats::TFDDatSTable* ADataTable);
	System::UnicodeString __fastcall DefineMetadataTableName(Firedac::Phys::Intf::TFDPhysMetaInfoKind AKind);
	System::UnicodeString __fastcall GetCacheFilter(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString AObjField, const System::UnicodeString AObj, const System::UnicodeString ASubObjField, const System::UnicodeString ASubObj);
	System::UnicodeString __fastcall ConvertNameCaseExpr(const System::UnicodeString AColumn, const System::UnicodeString AValue, Firedac::Phys::Intf::TFDPhysNamePart APart);
	System::UnicodeString __fastcall ConvertNameCaseConst(const System::UnicodeString AValue, Firedac::Phys::Intf::TFDPhysNamePart APart);
	void __fastcall ParseMetaInfoParams(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ABaseObjName, const System::UnicodeString AObjName, /* out */ Firedac::Phys::Intf::TFDPhysParsedName &AParsedName);
	Firedac::Dats::TFDDatSView* __fastcall GetTableFieldsBase(Firedac::Phys::Intf::TFDPhysMetaInfoKind AMetaKind, const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ATable, const System::UnicodeString AWildCard);
	
protected:
	Firedac::Phys::TFDPhysConnection* FConnectionObj;
	Firedac::Stan::Intf::TFDStringList* FKeywords;
	bool FCISearch;
	HIDESBASE int __stdcall _AddRef();
	HIDESBASE int __stdcall _Release();
	HIDESBASE virtual HRESULT __stdcall QueryInterface(const GUID &IID, /* out */ void *Obj);
	virtual Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetKind();
	virtual unsigned __int64 __fastcall GetClientVersion();
	virtual unsigned __int64 __fastcall GetServerVersion();
	virtual bool __fastcall GetIsUnicode();
	virtual bool __fastcall GetIsFileBased();
	virtual bool __fastcall GetTxSupported();
	virtual bool __fastcall GetTxNested();
	virtual bool __fastcall GetTxMultiple();
	virtual bool __fastcall GetTxSavepoints();
	virtual bool __fastcall GetTxAutoCommit();
	virtual bool __fastcall GetTxAtomic();
	virtual bool __fastcall GetEventSupported();
	virtual System::UnicodeString __fastcall GetEventKinds();
	virtual bool __fastcall GetGeneratorSupported();
	virtual int __fastcall GetParamNameMaxLength();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameQuotedSupportedParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameQuotedCaseSensParts();
	virtual bool __fastcall GetNameQuotedCaseSens(const System::UnicodeString AName, Firedac::Phys::Intf::TFDPhysNamePart APart);
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameCaseSensParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameDefLowCaseParts();
	virtual System::WideChar __fastcall GetNameQuoteChar(Firedac::Phys::Intf::TFDPhysNameQuoteLevel AQuote, Firedac::Phys::Intf::TFDPhysNameQuoteSide ASide);
	virtual System::WideChar __fastcall GetCatalogSeparator();
	virtual System::WideChar __fastcall GetSchemaSeparator();
	virtual Firedac::Phys::Intf::TFDPhysInsertHBlobMode __fastcall GetInsertHBlobMode();
	virtual bool __fastcall GetIdentitySupported();
	virtual bool __fastcall GetIdentityInsertSupported();
	virtual bool __fastcall GetIdentityInWhere();
	virtual Firedac::Phys::Intf::TFDPhysParamMark __fastcall GetNamedParamMark();
	virtual Firedac::Phys::Intf::TFDPhysParamMark __fastcall GetPositionedParamMark();
	virtual Firedac::Phys::Intf::TFDPhysSelectOptions __fastcall GetSelectOptions();
	virtual bool __fastcall GetLockNoWait();
	virtual bool __fastcall GetAsyncAbortSupported();
	virtual bool __fastcall GetAsyncNativeTimeout();
	virtual System::UnicodeString __fastcall GetCommandSeparator();
	virtual Firedac::Stan::Intf::TFDTextEndOfLine __fastcall GetLineSeparator();
	virtual Firedac::Phys::Intf::TFDPhysArrayExecMode __fastcall GetArrayExecMode();
	virtual Firedac::Phys::Intf::TFDPhysLimitOptions __fastcall GetLimitOptions();
	virtual Firedac::Phys::Intf::TFDPhysNullLocations __fastcall GetNullLocations();
	virtual bool __fastcall GetServerCursorSupported();
	virtual bool __fastcall GetColumnOriginProvided();
	virtual Firedac::Phys::Intf::TFDPhysCreateTableOptions __fastcall GetCreateTableOptions();
	virtual bool __fastcall GetBackslashEscSupported();
	bool __fastcall DecodeObjName(const System::UnicodeString AName, /* out */ Firedac::Phys::Intf::TFDPhysParsedName &AParsedName, const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand, Firedac::Phys::Intf::TFDPhysDecodeOptions AOpts);
	System::UnicodeString __fastcall EncodeObjName(const Firedac::Phys::Intf::TFDPhysParsedName &AParsedName, const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand, Firedac::Phys::Intf::TFDPhysEncodeOptions AOpts);
	System::UnicodeString __fastcall QuoteObjName(const System::UnicodeString AName, Firedac::Phys::Intf::TFDPhysNamePart APart);
	System::UnicodeString __fastcall UnQuoteObjName(const System::UnicodeString AName);
	bool __fastcall IsKeyword(const System::UnicodeString AName);
	virtual bool __fastcall IsNameValid(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall TranslateEscapeSequence(Firedac::Phys::Intf::TFDPhysEscapeData &ASeq);
	Firedac::Phys::Intf::TFDPhysCommandKind __fastcall GetSQLCommandKind(System::Classes::TStrings* const ATokens);
	virtual bool __fastcall GetTruncateSupported();
	virtual Firedac::Phys::Intf::TFDPhysDefaultValues __fastcall GetDefValuesSupported();
	virtual bool __fastcall GetInlineRefresh();
	virtual Firedac::Dats::TFDDatSView* __fastcall GetCatalogs(const System::UnicodeString AWildCard);
	virtual Firedac::Dats::TFDDatSView* __fastcall GetSchemas(const System::UnicodeString ACatalog, const System::UnicodeString AWildCard);
	virtual Firedac::Dats::TFDDatSView* __fastcall GetTables(Firedac::Phys::Intf::TFDPhysObjectScopes AScope, Firedac::Phys::Intf::TFDPhysTableKinds AKinds, const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString AWildCard);
	virtual Firedac::Dats::TFDDatSView* __fastcall GetTableFields(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ATable, const System::UnicodeString AWildCard);
	virtual Firedac::Dats::TFDDatSView* __fastcall GetTableIndexes(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ATable, const System::UnicodeString AWildCard);
	virtual Firedac::Dats::TFDDatSView* __fastcall GetTableIndexFields(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ATable, const System::UnicodeString AIndex, const System::UnicodeString AWildCard);
	virtual Firedac::Dats::TFDDatSView* __fastcall GetTablePrimaryKey(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ATable);
	virtual Firedac::Dats::TFDDatSView* __fastcall GetTablePrimaryKeyFields(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ATable, const System::UnicodeString AWildCard);
	Firedac::Dats::TFDDatSView* __fastcall GetTableForeignKeys(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ATable, const System::UnicodeString AWildCard);
	Firedac::Dats::TFDDatSView* __fastcall GetTableForeignKeyFields(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ATable, const System::UnicodeString AForeignKey, const System::UnicodeString AWildCard);
	virtual Firedac::Dats::TFDDatSView* __fastcall GetPackages(Firedac::Phys::Intf::TFDPhysObjectScopes AScope, const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString AWildCard);
	virtual Firedac::Dats::TFDDatSView* __fastcall GetPackageProcs(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString APackage, const System::UnicodeString AWildCard);
	virtual Firedac::Dats::TFDDatSView* __fastcall GetProcs(Firedac::Phys::Intf::TFDPhysObjectScopes AScope, const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString AWildCard);
	virtual Firedac::Dats::TFDDatSView* __fastcall GetProcArgs(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString APackage, const System::UnicodeString AProc, const System::UnicodeString AWildCard, System::Word AOverload);
	virtual Firedac::Dats::TFDDatSView* __fastcall GetGenerators(Firedac::Phys::Intf::TFDPhysObjectScopes AScope, const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString AWildCard);
	virtual Firedac::Dats::TFDDatSView* __fastcall GetResultSetFields(const System::UnicodeString ASQLKey);
	virtual Firedac::Dats::TFDDatSView* __fastcall GetTableTypeFields(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ATable, const System::UnicodeString AWildCard);
	virtual void __fastcall DefineMetadataStructure(Firedac::Dats::TFDDatSTable* ATable, Firedac::Phys::Intf::TFDPhysMetaInfoKind AKind);
	void __fastcall RefreshMetadataCache(const System::UnicodeString AObjName = System::UnicodeString());
	virtual System::UnicodeString __fastcall InternalEncodeObjName(const Firedac::Phys::Intf::TFDPhysParsedName &AParsedName, const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand);
	virtual bool __fastcall InternalDecodeObjName(const System::UnicodeString AName, /* out */ Firedac::Phys::Intf::TFDPhysParsedName &AParsedName, const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand, bool ARaise);
	virtual void __fastcall InternalOverrideNameByCommand(Firedac::Phys::Intf::TFDPhysParsedName &AParsedName, const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand);
	virtual System::UnicodeString __fastcall InternalEscapeBoolean(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDate(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeTime(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDateTime(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFloat(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFunction(const Firedac::Phys::Intf::TFDPhysEscapeData &ASeq);
	virtual System::UnicodeString __fastcall InternalEscapeEscape(System::WideChar AEscape, const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeInto(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeString(const System::UnicodeString AStr);
	virtual Firedac::Phys::Intf::TFDPhysCommandKind __fastcall InternalGetSQLCommandKind(System::Classes::TStrings* const ATokens);
	void __fastcall UnsupportedEscape(const Firedac::Phys::Intf::TFDPhysEscapeData &ASeq);
	void __fastcall EscapeFuncToID(Firedac::Phys::Intf::TFDPhysEscapeData &ASeq);
	System::UnicodeString __fastcall AddEscapeSequenceArgs(const Firedac::Phys::Intf::TFDPhysEscapeData &ASeq);
	void __fastcall ConfigNameParts();
	void __fastcall ConfigQuoteChars();
	void __fastcall AddMetadataCol(Firedac::Dats::TFDDatSTable* ATable, const System::UnicodeString AName, Firedac::Stan::Intf::TFDDataType AType);
	
public:
	__fastcall TFDPhysConnectionMetadata(Firedac::Phys::TFDPhysConnection* const AConnectionObj, unsigned __int64 AServerVersion, unsigned __int64 AClientVersion, bool AIsUnicode);
	__fastcall virtual ~TFDPhysConnectionMetadata();
private:
	void *__IFDPhysConnectionMetadata;	// Firedac::Phys::Intf::IFDPhysConnectionMetadata 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2104}
	operator Firedac::Phys::Intf::_di_IFDPhysConnectionMetadata()
	{
		Firedac::Phys::Intf::_di_IFDPhysConnectionMetadata intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Phys::Intf::IFDPhysConnectionMetadata*(void) { return (Firedac::Phys::Intf::IFDPhysConnectionMetadata*)&__IFDPhysConnectionMetadata; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000000-0000-0000-C000-000000000046}
	operator System::_di_IInterface()
	{
		System::_di_IInterface intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::IInterface*(void) { return (System::IInterface*)&__IFDPhysConnectionMetadata; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Meta */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_META)
using namespace Firedac::Phys::Meta;
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
#endif	// Firedac_Phys_MetaHPP
