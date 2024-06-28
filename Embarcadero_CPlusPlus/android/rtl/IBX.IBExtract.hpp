// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBExtract.pas' rev: 34.00 (Android)

#ifndef Ibx_IbextractHPP
#define Ibx_IbextractHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IBX.IBDatabase.hpp>
#include <IBX.IBDatabaseInfo.hpp>
#include <IBX.IBSQL.hpp>
#include <IBX.IBHeader.hpp>
#include <System.Generics.Collections.hpp>
#include <IBX.IB.hpp>
#include <IBX.IBExternals.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibextract
{
//-- forward type declarations -----------------------------------------------
struct TDescriptionRelation;
class DELPHICLASS TIBExtract;
struct TSQLType;
struct TPrivTypes;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TExtractObjectType : unsigned char { eoDatabase, eoDomain, eoTable, eoView, eoProcedure, eoFunction, eoGenerator, eoException, eoBLOBFilter, eoRole, eoTrigger, eoForeign, eoIndexes, eoChecks, eoData, eoEUAUser, eoEncryption, eoGrants, eoSubscription, eoTableSpaces, eoCollations, eoCharSets };

typedef System::Set<TExtractObjectType, TExtractObjectType::eoDatabase, TExtractObjectType::eoCharSets> TExtractObjectTypes;

enum DECLSPEC_DENUM TExtractType : unsigned char { etDomain, etTable, etRole, etTrigger, etForeign, etIndex, etData, etGrant, etCheck, etAlterProc, etEUAUser, etEncryption, etSubscriptions, etTableSpaces, etDescriptions, etCollations, etCharSets };

typedef System::Set<TExtractType, TExtractType::etDomain, TExtractType::etCharSets> TExtractTypes;

struct DECLSPEC_DRECORD TDescriptionRelation
{
public:
	System::UnicodeString RelationTable;
	System::UnicodeString BasicType;
	System::UnicodeString RelationNameCol;
	System::UnicodeString WhereClause;
	__fastcall TDescriptionRelation(System::UnicodeString aTable, System::UnicodeString aBasicType, System::UnicodeString ARelationNameCol, System::UnicodeString AWhereClause);
	TDescriptionRelation() {}
};


class PASCALIMPLEMENTATION TIBExtract : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Ibx::Ibdatabase::TIBBase* FBase;
	System::Classes::TStrings* FMetaData;
	System::Classes::TStrings* FDescriptions;
	Ibx::Ibdatabaseinfo::TIBDatabaseInfo* FDatabaseInfo;
	bool FShowSystem;
	bool FIncludeSetTerm;
	int FDefaultCharSet;
	bool FConnectAsOwner;
	int FOverrideSQLDialect;
	Ibx::Ibsql::TIBSQL* qryTables;
	Ibx::Ibsql::TIBSQL* qryConstraints;
	Ibx::Ibsql::TIBSQL* qryRelConstraints;
	Ibx::Ibsql::TIBSQL* qryEncryption;
	Ibx::Ibsql::TIBSQL* sqlMain;
	Ibx::Ibsql::TIBSQL* sqlTables;
	Ibx::Ibsql::TIBSQL* sqlColumns;
	bool FDescriptionsStarted;
	Ibx::Ibsql::TIBSQL* qryProcedures;
	Ibx::Ibsql::TIBSQL* qryDescriptions;
	int ODSMajorVersion;
	int DBSQLDialect;
	System::Extended FullODS;
	bool FIncludeComments;
	bool FIncludeDescriptions;
	Ibx::Ibdatabase::TIBDatabase* __fastcall GetDatabase();
	System::UnicodeString __fastcall GetIndexSegments(System::UnicodeString indexname);
	Ibx::Ibdatabase::TIBTransaction* __fastcall GetTransaction();
	void __fastcall SetDatabase(Ibx::Ibdatabase::TIBDatabase* const Value);
	void __fastcall SetTransaction(Ibx::Ibdatabase::TIBTransaction* const Value);
	System::UnicodeString __fastcall PrintValidation(System::UnicodeString ToValidate, bool flag);
	void __fastcall ShowGrants(System::UnicodeString MetaObject, System::UnicodeString Terminator);
	void __fastcall ShowGrantRoles(System::UnicodeString Terminator);
	void __fastcall GetProcedureArgs(System::UnicodeString Proc, System::Classes::TStrings* args);
	int __fastcall GetFieldLength(Ibx::Ibsql::TIBSQL* sql)/* overload */;
	Ibx::Ibsql::TIBSQL* __fastcall CreateIBSQL();
	void __fastcall BuildConnectString();
	int __fastcall GetDialect();
	void __fastcall SetOverrideSQLDialect(const int Value);
	
protected:
	bool __fastcall ExtractDDL(bool Flag, System::UnicodeString TableName);
	bool __fastcall ExtractListTable(System::UnicodeString RelationName, System::UnicodeString NewName, bool DomainFlag, Ibx::Ibsql::TIBSQL* aQry = (Ibx::Ibsql::TIBSQL*)(0x0));
	void __fastcall ExtractListView(System::UnicodeString ViewName);
	void __fastcall ListData(System::UnicodeString ObjectName);
	void __fastcall ListSubcriptionData(System::UnicodeString ObjectName, Ibx::Ibsql::TIBSQL* qrySelect);
	void __fastcall ListRoles(System::UnicodeString ObjectName = System::UnicodeString());
	void __fastcall ListGrants()/* overload */;
	void __fastcall ListGrants(System::UnicodeString ObjectName)/* overload */;
	void __fastcall ListProcs(System::UnicodeString ProcedureName = System::UnicodeString(), bool AlterOnly = false);
	void __fastcall ListAllTables(bool flag);
	void __fastcall ListTriggers(System::UnicodeString ObjectName = System::UnicodeString(), TExtractType ExtractType = (TExtractType)(0x3));
	void __fastcall ListCheck(System::UnicodeString ObjectName = System::UnicodeString(), TExtractType ExtractType = (TExtractType)(0x8));
	System::UnicodeString __fastcall PrintSet(bool &Used);
	void __fastcall ListCreateDb(System::UnicodeString TargetDb = System::UnicodeString());
	void __fastcall ListDomains(System::UnicodeString ObjectName = System::UnicodeString(), TExtractType ExtractType = (TExtractType)(0x0));
	void __fastcall ListException(System::UnicodeString ExceptionName = System::UnicodeString());
	void __fastcall ListFilters(System::UnicodeString FilterName = System::UnicodeString());
	void __fastcall ListForeign(System::UnicodeString ObjectName = System::UnicodeString(), TExtractType ExtractType = (TExtractType)(0x4));
	void __fastcall ListFunctions(System::UnicodeString FunctionName = System::UnicodeString());
	void __fastcall ListGenerators(System::UnicodeString GeneratorName = System::UnicodeString());
	void __fastcall ListIndex(System::UnicodeString ObjectName = System::UnicodeString(), TExtractType ExtractType = (TExtractType)(0x5));
	void __fastcall ListViews(System::UnicodeString ViewName = System::UnicodeString());
	void __fastcall ListEUAUsers();
	void __fastcall ListEncryptionsForTable(System::UnicodeString TableName = System::UnicodeString());
	void __fastcall ListEncryptions(System::UnicodeString EncryptionName = System::UnicodeString(), bool IncludeHeader = true, bool IncludeFooter = true);
	void __fastcall ListSubscriptions(System::UnicodeString SubscriptionName = System::UnicodeString());
	void __fastcall ListTableSpaces(System::UnicodeString ATablespace = System::UnicodeString());
	void __fastcall ListDescriptions(System::UnicodeString ObjectName = System::UnicodeString(), TExtractObjectType ExtractType = (TExtractObjectType)(0x0), System::UnicodeString KnownDescription = System::UnicodeString());
	void __fastcall ListCollations(System::UnicodeString ObjectName = System::UnicodeString(), TExtractType ExtractType = (TExtractType)(0xf));
	void __fastcall ListCharacterSets(System::UnicodeString ObjectName = System::UnicodeString(), TExtractType ExtractType = (TExtractType)(0x10));
	void __fastcall CheckAssigned();
	void __fastcall AddDescriptionComment(const TDescriptionRelation &RelDescription, System::UnicodeString ForRelation, TExtractObjectType ForType, System::Classes::TStrings* ToList = (System::Classes::TStrings*)(0x0));
	
public:
	__fastcall virtual TIBExtract(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBExtract();
	System::UnicodeString __fastcall GetArrayField(System::UnicodeString FieldName);
	System::UnicodeString __fastcall GetFieldType(int FieldType, int FieldSubType, int FieldScale, int FieldSize, int FieldPrec, int FieldLen);
	System::UnicodeString __fastcall GetCharacterSets(short CharSetId, short Collation, bool CollateOnly);
	void __fastcall ExtractObject(TExtractObjectType ObjectType, System::UnicodeString ObjectName = System::UnicodeString(), TExtractTypes ExtractTypes = TExtractTypes() );
	void __fastcall ExtractTable(System::UnicodeString RelationName, System::UnicodeString NewName, bool DomainFlag);
	__property Ibx::Ibdatabaseinfo::TIBDatabaseInfo* DatabaseInfo = {read=FDatabaseInfo};
	__property System::Classes::TStrings* Items = {read=FMetaData};
	
__published:
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=GetDatabase, write=SetDatabase};
	__property Ibx::Ibdatabase::TIBTransaction* Transaction = {read=GetTransaction, write=SetTransaction};
	__property bool ShowSystem = {read=FShowSystem, write=FShowSystem, default=0};
	__property bool IncludeSetTerm = {read=FIncludeSetTerm, write=FIncludeSetTerm, default=0};
	__property bool ConnectAsOwner = {read=FConnectAsOwner, write=FConnectAsOwner, default=0};
	__property int OverrideSQLDialect = {read=FOverrideSQLDialect, write=SetOverrideSQLDialect, nodefault};
	__property bool IncludeComments = {read=FIncludeComments, write=FIncludeComments, nodefault};
	__property bool IncludeDescriptions = {read=FIncludeDescriptions, write=FIncludeDescriptions, nodefault};
};


struct DECLSPEC_DRECORD TSQLType
{
public:
	int SqlType;
	System::UnicodeString TypeName;
};


struct DECLSPEC_DRECORD TPrivTypes
{
public:
	int PrivFlag;
	System::UnicodeString PrivString;
};


typedef System::StaticArray<TSQLType, 15> TSQLTypes;

typedef System::StaticArray<TPrivTypes, 8> Ibx_Ibextract__2;

typedef System::StaticArray<System::UnicodeString, 9> Ibx_Ibextract__3;

typedef System::StaticArray<System::UnicodeString, 7> Ibx_Ibextract__4;

typedef System::StaticArray<System::UnicodeString, 3> Ibx_Ibextract__5;

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 priv_UNKNOWN = System::Int8(0x1);
static constexpr System::Int8 priv_SELECT = System::Int8(0x2);
static constexpr System::Int8 priv_INSERT = System::Int8(0x4);
static constexpr System::Int8 priv_UPDATE = System::Int8(0x8);
static constexpr System::Int8 priv_DELETE = System::Int8(0x10);
static constexpr System::Int8 priv_EXECUTE = System::Int8(0x20);
static constexpr System::Int8 priv_REFERENCES = System::Int8(0x40);
static constexpr System::Byte priv_DECRYPT = System::Byte(0x80);
static constexpr System::Word priv_TRUNCATE = System::Word(0x100);
extern DELPHI_PACKAGE Ibx_Ibextract__2 PrivTypes;
extern DELPHI_PACKAGE Ibx_Ibextract__3 SubTypes;
extern DELPHI_PACKAGE Ibx_Ibextract__4 TriggerTypes;
extern DELPHI_PACKAGE Ibx_Ibextract__5 IntegralSubtypes;
static constexpr System::Int8 ODS_VERSION6 = System::Int8(0x6);
static constexpr System::Int8 ODS_VERSION7 = System::Int8(0x7);
static constexpr System::Int8 ODS_VERSION8 = System::Int8(0x8);
static constexpr System::Int8 ODS_VERSION9 = System::Int8(0x9);
static constexpr System::Int8 ODS_VERSION10 = System::Int8(0xa);
static constexpr System::Int8 ODS_VERSION16 = System::Int8(0x10);
static constexpr System::Int8 ODS_VERSION18 = System::Int8(0x12);
static constexpr System::Int8 FILE_shadow = System::Int8(0x1);
static constexpr System::Int8 FILE_inactive = System::Int8(0x2);
static constexpr System::Int8 FILE_manual = System::Int8(0x4);
static constexpr System::Int8 FILE_cache = System::Int8(0x8);
static constexpr System::Int8 FILE_conditional = System::Int8(0x10);
static constexpr System::Int8 LOG_serial = System::Int8(0x1);
static constexpr System::Int8 LOG_default = System::Int8(0x2);
static constexpr System::Int8 LOG_raw = System::Int8(0x4);
static constexpr System::Int8 LOG_overflow = System::Int8(0x8);
static constexpr System::Int8 MAX_INTSUBTYPES = System::Int8(0x2);
static constexpr System::Int8 MAXSUBTYPES = System::Int8(0x8);
static constexpr System::Int8 obj_relation = System::Int8(0x0);
static constexpr System::Int8 obj_view = System::Int8(0x1);
static constexpr System::Int8 obj_trigger = System::Int8(0x2);
static constexpr System::Int8 obj_computed = System::Int8(0x3);
static constexpr System::Int8 obj_validation = System::Int8(0x4);
static constexpr System::Int8 obj_procedure = System::Int8(0x5);
static constexpr System::Int8 obj_expression_index = System::Int8(0x6);
static constexpr System::Int8 obj_exception = System::Int8(0x7);
static constexpr System::Int8 obj_user = System::Int8(0x8);
static constexpr System::Int8 obj_field = System::Int8(0x9);
static constexpr System::Int8 obj_index = System::Int8(0xa);
static constexpr System::Int8 obj_count = System::Int8(0xb);
static constexpr System::Int8 obj_user_group = System::Int8(0xc);
static constexpr System::Int8 obj_sql_role = System::Int8(0xd);
static constexpr System::Int8 obj_subscription = System::Int8(0x10);
extern DELPHI_PACKAGE System::Generics::Collections::TDictionary__2<short,System::UnicodeString>* ColumnTypes;
}	/* namespace Ibextract */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBEXTRACT)
using namespace Ibx::Ibextract;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbextractHPP
