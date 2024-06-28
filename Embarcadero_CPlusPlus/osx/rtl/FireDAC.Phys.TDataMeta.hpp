// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.TDataMeta.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_TdatametaHPP
#define Firedac_Phys_TdatametaHPP

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
namespace Tdatameta
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IFDPhysTDataConnectionMetadata;
typedef System::DelphiInterface<IFDPhysTDataConnectionMetadata> _di_IFDPhysTDataConnectionMetadata;
class DELPHICLASS TFDPhysTDataMetadata;
class DELPHICLASS TFDPhysTDataCommandGenerator;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDTDataSessionMode : unsigned int { tmTeradata, tmANSI };

__interface  INTERFACE_UUID("{CB231063-11DB-4E0D-A8FF-C25795997A1C}") IFDPhysTDataConnectionMetadata  : public System::IInterface 
{
	virtual TFDTDataSessionMode __fastcall GetSessionMode() = 0 ;
	__property TFDTDataSessionMode SessionMode = {read=GetSessionMode};
};

#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION TFDPhysTDataMetadata : public Firedac::Phys::Meta::TFDPhysConnectionMetadata
{
	typedef Firedac::Phys::Meta::TFDPhysConnectionMetadata inherited;
	
private:
	bool FColumnOriginProvided;
	TFDTDataSessionMode FSessionMode;
	System::UnicodeString FCharacterSet;
	
protected:
	virtual Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetKind();
	virtual bool __fastcall GetTxAtomic();
	virtual bool __fastcall GetIdentityInsertSupported();
	virtual bool __fastcall GetInlineRefresh();
	virtual bool __fastcall GetIdentityInWhere();
	virtual int __fastcall GetParamNameMaxLength();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameParts();
	virtual Firedac::Phys::Intf::TFDPhysNameParts __fastcall GetNameQuotedCaseSensParts();
	virtual Firedac::Phys::Intf::TFDPhysDefaultValues __fastcall GetDefValuesSupported();
	virtual Firedac::Phys::Intf::TFDPhysSelectOptions __fastcall GetSelectOptions();
	virtual bool __fastcall GetAsyncAbortSupported();
	virtual bool __fastcall GetAsyncNativeTimeout();
	virtual Firedac::Phys::Intf::TFDPhysArrayExecMode __fastcall GetArrayExecMode();
	virtual bool __fastcall GetColumnOriginProvided();
	virtual void __fastcall DefineMetadataStructure(Firedac::Dats::TFDDatSTable* ATable, Firedac::Phys::Intf::TFDPhysMetaInfoKind AKind);
	virtual Firedac::Dats::TFDDatSView* __fastcall GetResultSetFields(const System::UnicodeString ASQLKey);
	virtual System::UnicodeString __fastcall InternalEscapeBoolean(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDate(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeDateTime(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFloat(const System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall InternalEscapeFunction(const Firedac::Phys::Intf::TFDPhysEscapeData &ASeq);
	virtual System::UnicodeString __fastcall InternalEscapeTime(const System::UnicodeString AStr);
	virtual Firedac::Phys::Intf::TFDPhysCommandKind __fastcall InternalGetSQLCommandKind(System::Classes::TStrings* const ATokens);
	TFDTDataSessionMode __fastcall GetSessionMode();
	
public:
	__fastcall TFDPhysTDataMetadata(Firedac::Phys::TFDPhysConnection* const AConnectionObj, unsigned __int64 AServerVersion, unsigned __int64 AClientVersion, const System::UnicodeString ACSVKeywords, bool AColumnOriginProvided, TFDTDataSessionMode ASessionMode, const System::UnicodeString ACharacterSet);
public:
	/* TFDPhysConnectionMetadata.Destroy */ inline __fastcall virtual ~TFDPhysTDataMetadata() { }
	
private:
	void *__IFDPhysTDataConnectionMetadata;	// IFDPhysTDataConnectionMetadata 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CB231063-11DB-4E0D-A8FF-C25795997A1C}
	operator _di_IFDPhysTDataConnectionMetadata()
	{
		_di_IFDPhysTDataConnectionMetadata intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IFDPhysTDataConnectionMetadata*(void) { return (IFDPhysTDataConnectionMetadata*)&__IFDPhysTDataConnectionMetadata; }
	#endif
	
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION TFDPhysTDataCommandGenerator : public Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator
{
	typedef Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetInlineRefresh(const System::UnicodeString AStmt, Firedac::Stan::Option::TFDUpdateRequest ARequest);
	virtual System::UnicodeString __fastcall GetPessimisticLock();
	virtual System::UnicodeString __fastcall GetTruncate();
	virtual System::UnicodeString __fastcall GetCall(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetSelectMetaInfo(Firedac::Phys::Intf::TFDPhysMetaInfoKind AKind, const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ABaseObject, const System::UnicodeString AObject, const System::UnicodeString AWildcard, Firedac::Phys::Intf::TFDPhysObjectScopes AObjectScopes, Firedac::Phys::Intf::TFDPhysTableKinds ATableKinds, System::Word AOverload);
	virtual System::UnicodeString __fastcall GetLimitSelect(const System::UnicodeString ASQL, int ASkip, int ARows, Firedac::Phys::Intf::TFDPhysLimitOptions &AOptions);
	virtual System::UnicodeString __fastcall GetColumnType(Firedac::Dats::TFDDatSColumn* AColumn);
	virtual System::UnicodeString __fastcall GetColumnDef(Firedac::Dats::TFDDatSColumn* AColumn);
	virtual System::UnicodeString __fastcall GetCreateTable(const System::UnicodeString ATab, const System::UnicodeString ACols);
	virtual System::UnicodeString __fastcall GetMerge(Firedac::Phys::Intf::TFDPhysMergeAction AAction);
protected:
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysTDataCommandGenerator()/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator() { }
	
public:
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysTDataCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand)/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator(ACommand) { }
	/* TFDPhysCommandGenerator.Create */ inline __fastcall TFDPhysTDataCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysConnection AConnection)/* overload */ : Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator(AConnection) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDPhysTDataCommandGenerator() { }
	
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString C_FD_TDataINTO;
}	/* namespace Tdatameta */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_TDATAMETA)
using namespace Firedac::Phys::Tdatameta;
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
#endif	// Firedac_Phys_TdatametaHPP
