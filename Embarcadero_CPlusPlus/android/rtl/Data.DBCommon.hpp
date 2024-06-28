// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBCommon.pas' rev: 34.00 (Android)

#ifndef Data_DbcommonHPP
#define Data_DbcommonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Variants.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Data.SqlTimSt.hpp>
#include <System.StrUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbcommon
{
//-- forward type declarations -----------------------------------------------
struct TExprNode;
class DELPHICLASS TFilterExpr;
class DELPHICLASS TExprParser;
struct TFieldInfo;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TCANOperator : unsigned char { coNOTDEFINED, coISBLANK, coNOTBLANK, coEQ, coNE, coGT, coLT, coGE, coLE, coNOT, coAND, coOR, coTUPLE2, coFIELD2, coCONST2, coMINUS, coADD, coSUB, coMUL, coDIV, coMOD, coREM, coSUM, coCOUNT, coMIN, coMAX, coAVG, coCONT, coUDF2, coCONTINUE2, coLIKE, coIN, coLIST2, coUPPER, coLOWER, coFUNC2, coLISTELEM2, coASSIGN };

enum DECLSPEC_DENUM NODEClass : unsigned char { nodeNULL, nodeUNARY, nodeBINARY, nodeCOMPARE, nodeFIELD, nodeCONST, nodeTUPLE, nodeCONTINUE, nodeUDF, nodeLIST, nodeFUNC, nodeLISTELEM };

enum DECLSPEC_DENUM IDENTIFIEROption : unsigned char { idKeepQuotes, idMixCase, idMakeLowerCase, idMakeUpperCase };

typedef System::DynamicArray<System::Byte> TExprData;

typedef System::StaticArray<System::Byte, 52> TFieldMap;

enum DECLSPEC_DENUM TParserOption : unsigned char { poExtSyntax, poAggregate, poDefaultExpr, poUseOrigNames, poFieldNameGiven, poFieldDepend };

typedef System::Set<TParserOption, TParserOption::poExtSyntax, TParserOption::poFieldDepend> TParserOptions;

enum DECLSPEC_DENUM TExprNodeKind : unsigned char { enField, enConst, enOperator, enFunc };

enum DECLSPEC_DENUM TExprScopeKind : unsigned char { skField, skAgg, skConst };

typedef TExprNode *PExprNode;

struct DECLSPEC_DRECORD TExprNode
{
public:
	TExprNode *FNext;
	TExprNodeKind FKind;
	bool FPartial;
	TCANOperator FOperator;
	System::Variant FData;
	TExprNode *FLeft;
	TExprNode *FRight;
	Data::Db::TFieldType FDataType;
	int FDataSize;
	System::Classes::TList* FArgs;
	TExprScopeKind FScopeKind;
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFilterExpr : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Data::Db::TDataSet* FDataSet;
	TFieldMap FFieldMap;
	Data::Db::TFilterOptions FOptions;
	TParserOptions FParserOptions;
	TExprNode *FNodes;
	TExprData FExprBuffer;
	int FExprBufSize;
	int FExprNodeSize;
	int FExprDataSize;
	System::UnicodeString FFieldName;
	System::Classes::TBits* FDependentFields;
	bool FUnicodeEnabled;
	Data::Db::TField* __fastcall FieldFromNode(PExprNode Node);
	System::PByte __fastcall GetExprData(int Pos, int Size);
	int __fastcall PutConstBCD(const System::Variant &Value, int Decimals);
	int __fastcall PutConstFMTBCD(const System::Variant &Value, int Decimals);
	int __fastcall PutConstBool(const System::Variant &Value);
	int __fastcall PutConstDate(const System::Variant &Value);
	int __fastcall PutConstDateTime(const System::Variant &Value);
	int __fastcall PutConstSQLTimeStamp(const System::Variant &Value);
	int __fastcall PutConstSQLTimeStampOffset(const System::Variant &Value);
	int __fastcall PutConstSingle(const System::Variant &Value);
	int __fastcall PutConstFloat(const System::Variant &Value);
	int __fastcall PutConstInt(Data::Db::TFieldType DataType, const System::Variant &Value);
	int __fastcall PutConstInt64(Data::Db::TFieldType DataType, const System::Variant &Value);
	int __fastcall PutConstNode(Data::Db::TFieldType DataType, System::PByte Data, int Size);
	int __fastcall PutConstAnsiStr(const System::AnsiString Value);
	int __fastcall PutConstUnicodeStr(const System::UnicodeString Value);
	int __fastcall PutConstTime(const System::Variant &Value);
	int __fastcall PutData(System::PByte Data, int Size);
	int __fastcall PutExprNode(PExprNode Node, TCANOperator ParentOp);
	int __fastcall PutFieldNode(Data::Db::TField* Field, PExprNode Node);
	int __fastcall PutNode(NODEClass NodeType, TCANOperator OpType, int OpCount);
	void __fastcall SetNodeOp(int Node, int Index, NativeInt Data);
	int __fastcall PutConstant(PExprNode Node);
	Data::Db::TField* __fastcall GetFieldByName(System::UnicodeString Name);
	
public:
	__fastcall TFilterExpr(Data::Db::TDataSet* DataSet, Data::Db::TFilterOptions Options, TParserOptions ParseOptions, const System::UnicodeString FieldName, System::Classes::TBits* DepFields, const TFieldMap &FieldMap, bool UnicodeEnabled);
	__fastcall virtual ~TFilterExpr();
	PExprNode __fastcall NewCompareNode(Data::Db::TField* Field, TCANOperator Operator, const System::Variant &Value);
	PExprNode __fastcall NewNode(TExprNodeKind Kind, TCANOperator Operator, const System::Variant &Data, PExprNode Left, PExprNode Right);
	TExprData __fastcall GetFilterData(PExprNode Root);
	__property Data::Db::TDataSet* DataSet = {write=FDataSet};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TExprToken : unsigned char { etEnd, etSymbol, etName, etLiteral, etLParen, etRParen, etEQ, etNE, etGE, etLE, etGT, etLT, etADD, etSUB, etMUL, etDIV, etComma, etLIKE, etISNULL, etISNOTNULL, etIN };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TExprParser : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::WideChar FDecimalSeparator;
	TFilterExpr* FFilter;
	TFieldMap FFieldMap;
	System::UnicodeString FText;
	System::WideChar *FSourcePtr;
	System::WideChar *FTokenPtr;
	System::UnicodeString FTokenString;
	System::UnicodeString FStrTrue;
	System::UnicodeString FStrFalse;
	TExprToken FToken;
	TExprToken FPrevToken;
	TExprData FFilterData;
	bool FNumericLit;
	int FDataSize;
	TParserOptions FParserOptions;
	System::UnicodeString FFieldName;
	Data::Db::TDataSet* FDataSet;
	System::Classes::TBits* FDependentFields;
	bool FUnicodeEnabled;
	void __fastcall NextToken();
	bool __fastcall NextTokenIsLParen();
	PExprNode __fastcall ParseExpr();
	PExprNode __fastcall ParseExpr2();
	PExprNode __fastcall ParseExpr3();
	PExprNode __fastcall ParseExpr4();
	PExprNode __fastcall ParseExpr5();
	PExprNode __fastcall ParseExpr6();
	PExprNode __fastcall ParseExpr7();
	System::UnicodeString __fastcall TokenName();
	bool __fastcall TokenSymbolIs(const System::UnicodeString S);
	bool __fastcall TokenSymbolIsFunc(const System::UnicodeString S);
	void __fastcall GetFuncResultInfo(PExprNode Node);
	void __fastcall TypeCheckArithOp(PExprNode Node);
	void __fastcall GetScopeKind(PExprNode Root, PExprNode Left, PExprNode Right);
	
public:
	__fastcall TExprParser(Data::Db::TDataSet* DataSet, const System::UnicodeString Text, Data::Db::TFilterOptions Options, TParserOptions ParserOptions, const System::UnicodeString FieldName, System::Classes::TBits* DepFields, const TFieldMap &FieldMap, bool UnicodeEnabled);
	__fastcall virtual ~TExprParser();
	void __fastcall SetExprParams(const System::UnicodeString Text, Data::Db::TFilterOptions Options, TParserOptions ParserOptions, const System::UnicodeString FieldName);
	__property TExprData FilterData = {read=FFilterData};
	__property int DataSize = {read=FDataSize, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TFieldInfo
{
public:
	System::UnicodeString DatabaseName;
	System::UnicodeString TableName;
	System::UnicodeString OriginalFieldName;
};


enum DECLSPEC_DENUM TSQLToken : unsigned char { stUnknown, stTableName, stFieldName, stAscending, stDescending, stSelect, stFrom, stWhere, stGroupBy, stHaving, stUnion, stPlan, stOrderBy, stForUpdate, stEnd, stPredicate, stValue, stIsNull, stIsNotNull, stLike, stAnd, stOr, stNumber, stAllFields, stComment, stDistinct };

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 CANEXPRSIZE = System::Int8(0xa);
static constexpr System::Int8 CANHDRSIZE = System::Int8(0x8);
static constexpr System::Int8 CANEXPRVERSION = System::Int8(0x2);
#define SQLSections (System::Set<TSQLToken, TSQLToken::stUnknown, TSQLToken::stDistinct>() << TSQLToken::stSelect << TSQLToken::stFrom << TSQLToken::stWhere << TSQLToken::stGroupBy << TSQLToken::stHaving << TSQLToken::stUnion << TSQLToken::stPlan << TSQLToken::stOrderBy << TSQLToken::stForUpdate )
extern DELPHI_PACKAGE System::RawByteString __fastcall MetaDataFromUnicode(const System::UnicodeString Value);
extern DELPHI_PACKAGE System::UnicodeString __fastcall MetaDataToUnicode(const System::RawByteString Value);
extern DELPHI_PACKAGE TSQLToken __fastcall NextSQLToken(char * &p, /* out */ System::AnsiString &Token, TSQLToken CurSection)/* overload */;
extern DELPHI_PACKAGE TSQLToken __fastcall NextSQLTokenEx(System::WideChar * &p, /* out */ System::UnicodeString &Token, TSQLToken CurSection, IDENTIFIEROption IdOption)/* overload */;
extern DELPHI_PACKAGE TSQLToken __fastcall NextSQLTokenEx(char * &p, /* out */ System::AnsiString &Token, TSQLToken CurSection, IDENTIFIEROption IdOption)/* overload */;
extern DELPHI_PACKAGE TSQLToken __fastcall NextSQLToken(System::WideChar * &p, /* out */ System::UnicodeString &Token, TSQLToken CurSection)/* overload */;
extern DELPHI_PACKAGE System::UnicodeString __fastcall AddParamSQLForDetail(Data::Db::TParams* Params, System::UnicodeString SQL, bool Native, System::UnicodeString QuoteChar = System::UnicodeString());
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetTableNameFromQuery(const System::UnicodeString SQL);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetTableNameFromSQL(const System::UnicodeString SQL);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetTableNameFromSQLEx(const System::UnicodeString SQL, IDENTIFIEROption IdOption);
extern DELPHI_PACKAGE bool __fastcall IsMultiTableQuery(const System::UnicodeString SQL);
extern DELPHI_PACKAGE bool __fastcall SQLRequiresParams(const System::UnicodeString SQL);
extern DELPHI_PACKAGE Data::Db::TIndexDef* __fastcall GetIndexForOrderBy(const System::UnicodeString SQL, Data::Db::TDataSet* DataSet);
extern DELPHI_PACKAGE bool __fastcall GetFieldInfo(const System::UnicodeString Origin, TFieldInfo &FieldInfo);
}	/* namespace Dbcommon */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBCOMMON)
using namespace Data::Dbcommon;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbcommonHPP
