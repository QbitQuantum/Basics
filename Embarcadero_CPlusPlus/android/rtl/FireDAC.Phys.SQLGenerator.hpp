// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.SQLGenerator.pas' rev: 34.00 (Android)

#ifndef Firedac_Phys_SqlgeneratorHPP
#define Firedac_Phys_SqlgeneratorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Sqlgenerator
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysCommandGenerator;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDPhysCommandPart : unsigned int { cpSELECT, cpFROM, cpWHERE, cpORDERBY, cpVALUES, cpSET, cpRETURNING };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysCommandGenerator : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Firedac::Dats::TFDDatSColumn* FColumn;
	System::UnicodeString FTabAlias;
	Firedac::Stan::Option::TFDUpdateRowOptions FUpdateRowOptions;
	Firedac::Phys::Intf::TFDPhysFillRowOptions FFillRowOptions;
	Firedac::Phys::Intf::TFDPhysCommandGeneratorOptions FGenOptions;
	Firedac::Phys::Intf::_di_IFDPhysMappingHandler FMappingHandler;
	Firedac::Dats::TFDDatSColumn* FLastColumn;
	Firedac::Stan::Intf::TFDDataAttributes FLastColumnAttrs;
	Firedac::Stan::Intf::TFDDataOptions FLastColumnOptions;
	System::UnicodeString FLastColumnObjName;
	System::UnicodeString FLastColumnAliasName;
	int FSQLOrderByPos;
	System::UnicodeString FCommandText;
	
protected:
	__fastcall TFDPhysCommandGenerator()/* overload */;
	
private:
	System::UnicodeString __fastcall NormalizeName(const System::UnicodeString AName, bool ASubObj, bool AForceNoQuote, bool AForceQuote);
	System::UnicodeString __fastcall GenerateInlineRefresh(const System::UnicodeString AStmt, Firedac::Stan::Option::TFDUpdateRequest ARequest);
	System::UnicodeString __fastcall GenerateIdentityInsert(const System::UnicodeString ATable, const System::UnicodeString AStmt, Firedac::Stan::Option::TFDUpdateRequest ARequest);
	bool __fastcall ColumnIdentityAssigned(Firedac::Dats::TFDDatSRow* ARow, Firedac::Dats::TFDDatSColumn* AColumn, bool AAlready);
	Firedac::Dats::TFDDatSRow* __fastcall GetNestedRow(Firedac::Dats::TFDDatSRow* ARow, int AColIndex);
	System::UnicodeString __fastcall GetStoredProcODBCCall(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString APackage, const System::UnicodeString AProc, System::Word AOverload, Firedac::Phys::Intf::TFDPhysCommandKind ASPUsage);
	
protected:
	Firedac::Dats::TFDDatSTable* FTable;
	Firedac::Dats::TFDDatSRow* FRow;
	Firedac::Stan::Param::TFDParams* FParams;
	Firedac::Phys::Intf::_di_IFDPhysConnectionMetadata FConnMeta;
	Firedac::Phys::Intf::_di_IFDPhysCommand FCommand;
	Firedac::Stan::Option::_di_IFDStanOptions FOptions;
	Firedac::Phys::Intf::TFDPhysCommandKind FCommandKind;
	TFDPhysCommandPart FCommandPart;
	Firedac::Phys::Intf::TFDPhysCommandGeneratorFlags FFlags;
	System::UnicodeString __fastcall GetSelectList(bool AAllowIdentityExp, bool AFlatFieldList, /* out */ bool &ANeedFrom);
	System::UnicodeString __fastcall GetFrom();
	System::UnicodeString __fastcall GetWhere(bool AInInsert, bool ARequired, bool ANotNull);
	System::UnicodeString __fastcall GetColumn(const System::UnicodeString AParentField, int ARowIndex, Firedac::Dats::TFDDatSColumn* AColumn);
	bool __fastcall ColumnChanged(Firedac::Dats::TFDDatSRow* ARow, Firedac::Dats::TFDDatSColumn* AColumn);
	System::UnicodeString __fastcall ColumnGenerator(Firedac::Dats::TFDDatSColumn* AColumn);
	bool __fastcall ColumnInKey(Firedac::Dats::TFDDatSColumn* AColumn);
	bool __fastcall ColumnSearchable(Firedac::Dats::TFDDatSColumn* AColumn);
	bool __fastcall ColumnStorable(Firedac::Dats::TFDDatSColumn* AColumn);
	bool __fastcall ColumnReqRefresh(Firedac::Stan::Option::TFDUpdateRequest ARequest, Firedac::Dats::TFDDatSColumn* AColumn);
	bool __fastcall ColumnIsHBLOB(Firedac::Dats::TFDDatSColumn* AColumn);
	System::UnicodeString __fastcall AddColumnParam(Firedac::Dats::TFDDatSColumn* AColumn, int AValueAge, Data::Db::TParamType AType);
	bool __fastcall ColumnUpdatable(Firedac::Dats::TFDDatSColumn* AColumn, bool AInInsert);
	System::UnicodeString __fastcall NormalizeColName(const System::UnicodeString AName);
	System::UnicodeString __fastcall NormalizeTabName(const System::UnicodeString AName);
	void __fastcall GetColumnAttributes(Firedac::Dats::TFDDatSColumn* AColumn, Firedac::Stan::Intf::TFDDataAttributes &AAttrs, Firedac::Stan::Intf::TFDDataOptions &AOptions, System::UnicodeString &AObjName, System::UnicodeString &AAliasName);
	System::UnicodeString __fastcall BRK();
	System::UnicodeString __fastcall IND();
	System::UnicodeString __fastcall GetReturning(Firedac::Stan::Option::TFDUpdateRequest ARequest, bool AWithInto);
	System::UnicodeString __fastcall GetColumnDim(int ASize, int APrec, int AScale, int ADefSize, int ADefPrec, int ADefScale);
	Firedac::Phys::Intf::TFDPhysFillRowOptions __fastcall GetFillRowOptions();
	Firedac::Phys::Intf::TFDPhysCommandGeneratorOptions __fastcall GetGenOptions();
	Firedac::Phys::Intf::TFDPhysCommandGeneratorFlags __fastcall GetFlags();
	Firedac::Stan::Param::TFDParams* __fastcall GetParams();
	Firedac::Dats::TFDDatSRow* __fastcall GetRow();
	Firedac::Dats::TFDDatSTable* __fastcall GetTable();
	Firedac::Stan::Option::TFDUpdateRowOptions __fastcall GetUpdateRowOptions();
	void __fastcall SetParams(Firedac::Stan::Param::TFDParams* const AValue);
	void __fastcall SetRow(Firedac::Dats::TFDDatSRow* const AValue);
	void __fastcall SetTable(Firedac::Dats::TFDDatSTable* const AValue);
	void __fastcall SetUpdateRowOptions(const Firedac::Stan::Option::TFDUpdateRowOptions AValue);
	Firedac::Dats::TFDDatSColumn* __fastcall GetCol();
	void __fastcall SetCol(Firedac::Dats::TFDDatSColumn* const AValue);
	void __fastcall SetFillRowOptions(const Firedac::Phys::Intf::TFDPhysFillRowOptions AValue);
	void __fastcall SetGenOptions(const Firedac::Phys::Intf::TFDPhysCommandGeneratorOptions AValue);
	Firedac::Phys::Intf::TFDPhysCommandKind __fastcall GetCommandKind();
	int __fastcall GetSQLOrderByPos();
	Firedac::Stan::Option::_di_IFDStanOptions __fastcall GetOptions();
	void __fastcall SetOptions(const Firedac::Stan::Option::_di_IFDStanOptions AValue);
	Firedac::Phys::Intf::_di_IFDPhysMappingHandler __fastcall GetMappingHandler();
	void __fastcall SetMappingHandler(const Firedac::Phys::Intf::_di_IFDPhysMappingHandler AValue);
	virtual System::UnicodeString __fastcall GenerateSelect(bool ARequired);
	System::UnicodeString __fastcall GenerateInsert();
	System::UnicodeString __fastcall GenerateMerge(Firedac::Phys::Intf::TFDPhysMergeAction AAction);
	System::UnicodeString __fastcall GenerateUpdateHBlobs();
	System::UnicodeString __fastcall GenerateUpdate();
	System::UnicodeString __fastcall GenerateDelete();
	System::UnicodeString __fastcall GenerateDeleteAll(bool ANoUndo);
	System::UnicodeString __fastcall GenerateLock();
	System::UnicodeString __fastcall GenerateUnLock();
	System::UnicodeString __fastcall GenerateSavepoint(const System::UnicodeString AName);
	System::UnicodeString __fastcall GenerateRollbackToSavepoint(const System::UnicodeString AName);
	System::UnicodeString __fastcall GenerateCommitSavepoint(const System::UnicodeString AName);
	System::UnicodeString __fastcall GenerateFetchGenerators();
	System::UnicodeString __fastcall GenerateReadGenerator(const System::UnicodeString AName, const System::UnicodeString AAlias, bool ANextValue, bool AFullSelect);
	System::UnicodeString __fastcall GenerateCall(const System::UnicodeString AName);
	System::UnicodeString __fastcall GenerateEval(const System::UnicodeString AExpr);
	System::UnicodeString __fastcall GeneratePing();
	System::UnicodeString __fastcall GenerateSelectTable(const Firedac::Phys::Intf::TFDPhysTableParams &ATableParams);
	System::UnicodeString __fastcall GenerateStoredProcParams(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString APackage, const System::UnicodeString AProc, System::Word AOverload);
	System::UnicodeString __fastcall GenerateStoredProcCall(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString APackage, const System::UnicodeString AProc, System::Word AOverload, Firedac::Phys::Intf::TFDPhysCommandKind ASPUsage);
	System::UnicodeString __fastcall GenerateSelectMetaInfo(Firedac::Phys::Intf::TFDPhysMetaInfoKind AKind, const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ABaseObject, const System::UnicodeString AObject, const System::UnicodeString AWildcard, Firedac::Phys::Intf::TFDPhysObjectScopes AObjectScopes, Firedac::Phys::Intf::TFDPhysTableKinds ATableKinds, System::Word AOverload);
	System::UnicodeString __fastcall GenerateLimitSelect(int ASkip, int ARows, bool AOneMore, Firedac::Phys::Intf::TFDPhysLimitOptions &AOptions);
	System::UnicodeString __fastcall GenerateCountSelect();
	System::UnicodeString __fastcall GenerateRowId(/* out */ System::UnicodeString &AAlias);
	System::Classes::TStrings* __fastcall GenerateCreateTable(Firedac::Phys::Intf::TFDPhysCreateTableParts AParts);
	System::Classes::TStrings* __fastcall GenerateDropTable(Firedac::Phys::Intf::TFDPhysCreateTableParts AParts);
	virtual System::UnicodeString __fastcall GetSubColumn(const System::UnicodeString AParentField, const System::UnicodeString ASubField);
	virtual System::UnicodeString __fastcall GetRowConstructor(const System::UnicodeString AValues, Firedac::Dats::TFDDatSColumn* ARowCol);
	virtual System::UnicodeString __fastcall GetCastColumn(const System::UnicodeString AValue, Firedac::Dats::TFDDatSColumn* ACol);
	virtual System::UnicodeString __fastcall GetInlineRefresh(const System::UnicodeString AStmt, Firedac::Stan::Option::TFDUpdateRequest ARequest);
	virtual System::UnicodeString __fastcall GetIdentityInsert(const System::UnicodeString ATable, const System::UnicodeString AStmt, Firedac::Stan::Option::TFDUpdateRequest ARequest);
	virtual System::UnicodeString __fastcall GetIdentity(bool ASessionScope);
	virtual System::UnicodeString __fastcall GetRowId(System::UnicodeString &AAlias);
	virtual System::UnicodeString __fastcall GetSingleRowTable();
	virtual System::UnicodeString __fastcall GetPessimisticLock();
	virtual System::UnicodeString __fastcall GetPessimisticUnLock();
	virtual System::UnicodeString __fastcall GetTruncate();
	virtual System::UnicodeString __fastcall GetSavepoint(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetRollbackToSavepoint(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetCommitSavepoint(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetReadGenerator(const System::UnicodeString AName, const System::UnicodeString AAlias, bool ANextValue, bool AFullSelect);
	virtual System::UnicodeString __fastcall GetCall(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetPing();
	virtual System::UnicodeString __fastcall GetStoredProcParams(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString APackage, const System::UnicodeString AProc, System::Word AOverload);
	virtual System::UnicodeString __fastcall GetStoredProcCall(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString APackage, const System::UnicodeString AProc, System::Word AOverload, Firedac::Phys::Intf::TFDPhysCommandKind ASPUsage);
	virtual System::UnicodeString __fastcall GetSelectMetaInfo(Firedac::Phys::Intf::TFDPhysMetaInfoKind AKind, const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ABaseObject, const System::UnicodeString AObject, const System::UnicodeString AWildcard, Firedac::Phys::Intf::TFDPhysObjectScopes AObjectScopes, Firedac::Phys::Intf::TFDPhysTableKinds ATableKinds, System::Word AOverload);
	virtual System::UnicodeString __fastcall GetLimitSelect(const System::UnicodeString ASQL, int ASkip, int ARows, Firedac::Phys::Intf::TFDPhysLimitOptions &AOptions);
	virtual System::UnicodeString __fastcall GetCountSelect(const System::UnicodeString ASQL);
	virtual System::UnicodeString __fastcall GetColumnType(Firedac::Dats::TFDDatSColumn* AColumn);
	virtual System::UnicodeString __fastcall GetColumnDef(Firedac::Dats::TFDDatSColumn* AColumn);
	virtual System::UnicodeString __fastcall GetCreateTable(const System::UnicodeString ATab, const System::UnicodeString ACols);
	virtual System::UnicodeString __fastcall GetCreateGenerator(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetDropGenerator(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetCreateIdentityTrigger();
	virtual System::UnicodeString __fastcall GetCreatePrimaryKey(const System::UnicodeString ACols);
	virtual System::UnicodeString __fastcall GetCreateIndex(const System::UnicodeString AName, const System::UnicodeString ACols, bool AUnique);
	virtual System::UnicodeString __fastcall GetInsert(const System::UnicodeString AOption);
	virtual System::UnicodeString __fastcall GetUpdate();
	virtual System::UnicodeString __fastcall GetMerge(Firedac::Phys::Intf::TFDPhysMergeAction AAction);
	
public:
	__fastcall TFDPhysCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand)/* overload */;
	__fastcall TFDPhysCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysConnection AConnection)/* overload */;
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDPhysCommandGenerator() { }
	
private:
	void *__IFDPhysCommandGenerator;	// Firedac::Phys::Intf::IFDPhysCommandGenerator 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2107}
	operator Firedac::Phys::Intf::_di_IFDPhysCommandGenerator()
	{
		Firedac::Phys::Intf::_di_IFDPhysCommandGenerator intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Phys::Intf::IFDPhysCommandGenerator*(void) { return (Firedac::Phys::Intf::IFDPhysCommandGenerator*)&__IFDPhysCommandGenerator; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sqlgenerator */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_SQLGENERATOR)
using namespace Firedac::Phys::Sqlgenerator;
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
#endif	// Firedac_Phys_SqlgeneratorHPP
