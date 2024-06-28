// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBSQL.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbsqlHPP
#define Ibx_IbsqlHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Variants.hpp>
#include <System.Classes.hpp>
#include <IBX.IBHeader.hpp>
#include <IBX.IBExternals.hpp>
#include <IBX.IBDatabase.hpp>
#include <IBX.IBIntf.hpp>
#include <Data.FmtBcd.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibsql
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSQLVAR;
class DELPHICLASS TSQLVAR_V1;
class DELPHICLASS TSQLVAR_V2;
class DELPHICLASS TIBXSQLVAR;
class DELPHICLASS TIBXSQLDAEnumerator;
class DELPHICLASS TIBXSQLDA;
class DELPHICLASS TIBSQL;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIBChangeState : unsigned char { csSame, csInsert, csUpdate, csDelete, csTruncate, csUnknown };

typedef System::Set<TIBChangeState, TIBChangeState::csSame, TIBChangeState::csUnknown> TIBChangeStates;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLVAR : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	short __fastcall GetSqlDef();
	
protected:
	virtual System::UnicodeString __fastcall GetAliasName() = 0 ;
	virtual System::UnicodeString __fastcall GetOwnName() = 0 ;
	virtual System::UnicodeString __fastcall GetRelName() = 0 ;
	virtual System::PByte __fastcall GetSqlData() = 0 ;
	virtual Ibx::Ibexternals::PShort __fastcall GetSqlInd() = 0 ;
	virtual short __fastcall GetSqlLen() = 0 ;
	virtual System::UnicodeString __fastcall GetSqlName() = 0 ;
	virtual short __fastcall GetSqlPrecision() = 0 ;
	virtual short __fastcall GetSqlScale() = 0 ;
	virtual short __fastcall GetSqlSubtype() = 0 ;
	virtual short __fastcall GetSqlType() = 0 ;
	virtual void * __fastcall GetSQLVAR() = 0 ;
	virtual void __fastcall SetAliasName(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetOwnName(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetRelName(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetSqlName(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetSqlData(const System::PByte Value) = 0 ;
	virtual void __fastcall SetSqlInd(const Ibx::Ibexternals::PShort Value) = 0 ;
	virtual void __fastcall SetSqlLen(const short Value) = 0 ;
	virtual void __fastcall SetSqlPrecision(const short Value) = 0 ;
	virtual void __fastcall SetSqlScale(const short Value) = 0 ;
	virtual void __fastcall SetSqlSubtype(const short Value) = 0 ;
	virtual void __fastcall SetSqlType(const short Value) = 0 ;
	virtual void __fastcall SetSQLVAR(const void * Value) = 0 ;
	
public:
	virtual void __fastcall SetDataSize(int oldsize, int newsize) = 0 ;
	virtual void __fastcall SetIndSize(int oldsize, int newsize) = 0 ;
	__property void * XSqlVar = {read=GetSQLVAR, write=SetSQLVAR};
	__property short SqlType = {read=GetSqlType, write=SetSqlType, nodefault};
	__property short SqlDef = {read=GetSqlDef, nodefault};
	__property short SqlScale = {read=GetSqlScale, write=SetSqlScale, nodefault};
	__property short SqlPrecision = {read=GetSqlPrecision, write=SetSqlPrecision, nodefault};
	__property short SqlSubtype = {read=GetSqlSubtype, write=SetSqlSubtype, nodefault};
	__property short SqlLen = {read=GetSqlLen, write=SetSqlLen, nodefault};
	__property System::PByte SqlData = {read=GetSqlData, write=SetSqlData};
	__property Ibx::Ibexternals::PShort SqlInd = {read=GetSqlInd, write=SetSqlInd};
	__property System::UnicodeString SqlName = {read=GetSqlName, write=SetSqlName};
	__property System::UnicodeString RelName = {read=GetRelName, write=SetRelName};
	__property System::UnicodeString OwnName = {read=GetOwnName, write=SetOwnName};
	__property System::UnicodeString AliasName = {read=GetAliasName, write=SetAliasName};
public:
	/* TObject.Create */ inline __fastcall TSQLVAR() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSQLVAR() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLVAR_V1 : public TSQLVAR
{
	typedef TSQLVAR inherited;
	
private:
	Ibx::Ibheader::TXSQLVAR_V1 *FXSQLVAR;
	
protected:
	virtual System::UnicodeString __fastcall GetAliasName();
	virtual System::UnicodeString __fastcall GetOwnName();
	virtual System::UnicodeString __fastcall GetRelName();
	virtual System::PByte __fastcall GetSqlData();
	virtual Ibx::Ibexternals::PShort __fastcall GetSqlInd();
	virtual short __fastcall GetSqlLen();
	virtual System::UnicodeString __fastcall GetSqlName();
	virtual short __fastcall GetSqlPrecision();
	virtual short __fastcall GetSqlScale();
	virtual short __fastcall GetSqlSubtype();
	virtual short __fastcall GetSqlType();
	virtual void * __fastcall GetSQLVAR();
	virtual void __fastcall SetAliasName(const System::UnicodeString Value);
	virtual void __fastcall SetOwnName(const System::UnicodeString Value);
	virtual void __fastcall SetRelName(const System::UnicodeString Value);
	virtual void __fastcall SetSqlName(const System::UnicodeString Value);
	virtual void __fastcall SetSqlData(const System::PByte Value);
	virtual void __fastcall SetSqlInd(const Ibx::Ibexternals::PShort Value);
	virtual void __fastcall SetSqlLen(const short Value);
	virtual void __fastcall SetSqlPrecision(const short Value);
	virtual void __fastcall SetSqlScale(const short Value);
	virtual void __fastcall SetSqlSubtype(const short Value);
	virtual void __fastcall SetSqlType(const short Value);
	virtual void __fastcall SetSQLVAR(const void * Value);
	
public:
	virtual void __fastcall SetDataSize(int oldsize, int newsize);
	virtual void __fastcall SetIndSize(int oldsize, int newsize);
public:
	/* TObject.Create */ inline __fastcall TSQLVAR_V1() : TSQLVAR() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSQLVAR_V1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSQLVAR_V2 : public TSQLVAR
{
	typedef TSQLVAR inherited;
	
private:
	Ibx::Ibheader::TXSQLVAR *FXSQLVAR;
	
protected:
	virtual System::UnicodeString __fastcall GetAliasName();
	virtual System::UnicodeString __fastcall GetOwnName();
	virtual System::UnicodeString __fastcall GetRelName();
	virtual System::PByte __fastcall GetSqlData();
	virtual Ibx::Ibexternals::PShort __fastcall GetSqlInd();
	virtual short __fastcall GetSqlLen();
	virtual System::UnicodeString __fastcall GetSqlName();
	virtual short __fastcall GetSqlPrecision();
	virtual short __fastcall GetSqlScale();
	virtual short __fastcall GetSqlSubtype();
	virtual short __fastcall GetSqlType();
	virtual void * __fastcall GetSQLVAR();
	virtual void __fastcall SetAliasName(const System::UnicodeString Value);
	virtual void __fastcall SetOwnName(const System::UnicodeString Value);
	virtual void __fastcall SetRelName(const System::UnicodeString Value);
	virtual void __fastcall SetSqlName(const System::UnicodeString Value);
	virtual void __fastcall SetSqlData(const System::PByte Value);
	virtual void __fastcall SetSqlInd(const Ibx::Ibexternals::PShort Value);
	virtual void __fastcall SetSqlLen(const short Value);
	virtual void __fastcall SetSqlPrecision(const short Value);
	virtual void __fastcall SetSqlScale(const short Value);
	virtual void __fastcall SetSqlSubtype(const short Value);
	virtual void __fastcall SetSqlType(const short Value);
	virtual void __fastcall SetSQLVAR(const void * Value);
	
public:
	virtual void __fastcall SetDataSize(int oldsize, int newsize);
	virtual void __fastcall SetIndSize(int oldsize, int newsize);
public:
	/* TObject.Create */ inline __fastcall TSQLVAR_V2() : TSQLVAR() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSQLVAR_V2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIBXSQLVAR : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TIBXSQLDA* FParent;
	TIBSQL* FSQL;
	int FIndex;
	bool FModified;
	System::UnicodeString FName;
	TSQLVAR* FXSQLVAR;
	short FMaxLen;
	double __fastcall AdjustScale(__int64 Value, int Scale);
	__int64 __fastcall AdjustScaleToInt64(__int64 Value, int Scale);
	System::Currency __fastcall AdjustScaleToCurrency(__int64 Value, int Scale);
	Data::Fmtbcd::TBcd __fastcall AdjustScaleToBCD(__int64 Value, int Scale);
	System::Currency __fastcall GetAsCurrency();
	__int64 __fastcall GetAsInt64();
	System::TDateTime __fastcall GetAsDateTime();
	double __fastcall GetAsDouble();
	float __fastcall GetAsFloat();
	int __fastcall GetAsLong();
	void * __fastcall GetAsPointer();
	Ibx::Ibheader::TGDS_QUAD __fastcall GetAsQuad();
	short __fastcall GetAsShort();
	System::Variant __fastcall GetAsVariant();
	bool __fastcall GetIsNull();
	bool __fastcall GetIsNullable();
	int __fastcall GetSize();
	int __fastcall GetSQLType();
	void __fastcall SetAsCurrency(System::Currency Value);
	void __fastcall SetAsInt64(__int64 Value);
	void __fastcall SetAsDate(System::TDateTime Value);
	void __fastcall SetAsTime(System::TDateTime Value);
	void __fastcall SetAsDateTime(System::TDateTime Value);
	void __fastcall SetAsDouble(double Value);
	void __fastcall SetAsFloat(float Value);
	void __fastcall SetAsLong(int Value);
	void __fastcall SetAsPointer(void * Value);
	void __fastcall SetAsQuad(const Ibx::Ibheader::TGDS_QUAD &Value);
	void __fastcall SetAsShort(short Value);
	void __fastcall SetAsVariant(const System::Variant &Value);
	void __fastcall SetIsNull(bool Value);
	void __fastcall SetIsNullable(bool Value);
	void __fastcall SetAsTrimString(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetAsTrimString();
	bool __fastcall GetAsBoolean();
	void __fastcall SetAsBoolean(const bool Value);
	void __fastcall SetFXSQLVAR(TSQLVAR* const Value);
	Data::Fmtbcd::TBcd __fastcall GetAsBCD();
	void __fastcall SetAsBcd(const Data::Fmtbcd::TBcd &Value);
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall GetAsBytes();
	void __fastcall SetAsBytes(const System::DynamicArray<System::Byte> Value);
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall GetAsBytes();
	void __fastcall SetAsBytes(const System::TArray__1<System::Byte> Value);
#endif /* _WIN64 */
	int __fastcall GetCharsetSize();
	System::UnicodeString __fastcall GetAsString();
	void __fastcall SetAsString(const System::UnicodeString Value);
	TIBChangeState __fastcall GetChangeState();
	short __fastcall GetSQLInd();
	
protected:
	int __fastcall GetCodePage();
	
public:
	__fastcall TIBXSQLVAR(TIBXSQLDA* Parent, TIBSQL* Query);
	__fastcall virtual ~TIBXSQLVAR();
	void __fastcall Assign(TIBXSQLVAR* Source);
	void __fastcall LoadFromFile(const System::UnicodeString FileName);
	void __fastcall LoadFromStream(System::Classes::TStream* Stream);
	void __fastcall SaveToFile(const System::UnicodeString FileName);
	void __fastcall SaveToStream(System::Classes::TStream* Stream);
	void __fastcall Clear();
	__property bool AsBoolean = {read=GetAsBoolean, write=SetAsBoolean, nodefault};
	__property System::TDateTime AsDate = {read=GetAsDateTime, write=SetAsDate};
	__property System::TDateTime AsTime = {read=GetAsDateTime, write=SetAsTime};
	__property System::TDateTime AsDateTime = {read=GetAsDateTime, write=SetAsDateTime};
	__property double AsDouble = {read=GetAsDouble, write=SetAsDouble};
	__property float AsFloat = {read=GetAsFloat, write=SetAsFloat};
	__property System::Currency AsCurrency = {read=GetAsCurrency, write=SetAsCurrency};
	__property __int64 AsInt64 = {read=GetAsInt64, write=SetAsInt64};
	__property int AsInteger = {read=GetAsLong, write=SetAsLong, nodefault};
	__property int AsLong = {read=GetAsLong, write=SetAsLong, nodefault};
	__property void * AsPointer = {read=GetAsPointer, write=SetAsPointer};
	__property Ibx::Ibheader::TGDS_QUAD AsQuad = {read=GetAsQuad, write=SetAsQuad};
	__property short AsShort = {read=GetAsShort, write=SetAsShort, nodefault};
	__property System::UnicodeString AsTrimString = {read=GetAsTrimString, write=SetAsTrimString};
	__property System::Variant AsVariant = {read=GetAsVariant, write=SetAsVariant};
	__property Data::Fmtbcd::TBcd AsBcd = {read=GetAsBCD, write=SetAsBcd};
#ifndef _WIN64
	__property System::DynamicArray<System::Byte> AsBytes = {read=GetAsBytes, write=SetAsBytes};
#else /* _WIN64 */
	__property System::TArray__1<System::Byte> AsBytes = {read=GetAsBytes, write=SetAsBytes};
#endif /* _WIN64 */
	__property System::UnicodeString AsString = {read=GetAsString, write=SetAsString};
	__property TSQLVAR* SqlVar = {read=FXSQLVAR, write=SetFXSQLVAR};
	__property TSQLVAR* Data = {read=FXSQLVAR, write=FXSQLVAR};
	__property bool IsNull = {read=GetIsNull, write=SetIsNull, nodefault};
	__property bool IsNullable = {read=GetIsNullable, write=SetIsNullable, nodefault};
	__property int Index = {read=FIndex, nodefault};
	__property bool Modified = {read=FModified, write=FModified, nodefault};
	__property System::UnicodeString Name = {read=FName};
	__property int Size = {read=GetSize, nodefault};
	__property int SQLType = {read=GetSQLType, nodefault};
	__property System::Variant Value = {read=GetAsVariant, write=SetAsVariant};
	__property int CharSetSize = {read=GetCharsetSize, nodefault};
	__property TIBChangeState ChangeState = {read=GetChangeState, nodefault};
	__property short SQLInd = {read=GetSQLInd, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::DynamicArray<TIBXSQLVAR*> TIBXSQLVARArray;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIBXSQLDAEnumerator : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	int FIndex;
	TIBXSQLDA* FIBXSQLDA;
	
public:
	__fastcall TIBXSQLDAEnumerator(TIBXSQLDA* AIBXSQLDA);
	TIBXSQLVAR* __fastcall GetCurrent();
	bool __fastcall MoveNext();
	__property TIBXSQLVAR* Current = {read=GetCurrent};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBXSQLDAEnumerator() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIBXSQLDA : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TIBXSQLVAR* operator[](int Idx) { return this->Vars[Idx]; }
	
protected:
	TIBSQL* FSQL;
	int FCount;
	System::Classes::TStrings* FNames;
	int FSize;
	Ibx::Ibheader::TXSQLDA *FXSQLDA;
	TIBXSQLVARArray FXSQLVARs;
	System::UnicodeString FUniqueRelationName;
	Ibx::Ibintf::_di_IGDSLibrary FGDSLibrary;
	bool __fastcall GetModified();
	System::UnicodeString __fastcall GetNames();
	int __fastcall GetRecordSize();
	Ibx::Ibheader::PXSQLDA __fastcall GetXSQLDA();
	TIBXSQLVAR* __fastcall GetSQLVAR(int Idx);
	TIBXSQLVAR* __fastcall GetSQLVARByName(System::UnicodeString Idx);
	void __fastcall Initialize();
	void __fastcall SetCount(int Value);
	
public:
	__fastcall TIBXSQLDA(TIBSQL* Query);
	__fastcall virtual ~TIBXSQLDA();
	void __fastcall AddName(System::UnicodeString FieldName, int Idx);
	TIBXSQLVAR* __fastcall ByName(System::UnicodeString Idx);
	TIBXSQLDAEnumerator* __fastcall GetEnumerator();
	__property Ibx::Ibheader::PXSQLDA AsXSQLDA = {read=GetXSQLDA};
	__property int Count = {read=FCount, write=SetCount, nodefault};
	__property bool Modified = {read=GetModified, nodefault};
	__property System::UnicodeString Names = {read=GetNames};
	__property int RecordSize = {read=GetRecordSize, nodefault};
	__property TIBXSQLVAR* Vars[int Idx] = {read=GetSQLVAR/*, default*/};
	__property System::UnicodeString UniqueRelationName = {read=FUniqueRelationName};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TIBSQLTypes : unsigned char { SQLUnknown, SQLSelect, SQLInsert, SQLUpdate, SQLDelete, SQLDDL, SQLGetSegment, SQLPutSegment, SQLExecProcedure, SQLStartTransaction, SQLCommit, SQLRollback, SQLSelectForUpdate, SQLSetGenerator };

class PASCALIMPLEMENTATION TIBSQL : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	bool FCanceled;
	int __fastcall GetFieldCount();
	void __fastcall InternalFreeHandle(bool RaiseException);
	void __fastcall InternalClose(bool RaiseException);
	
protected:
	Ibx::Ibdatabase::TIBBase* FBase;
	bool FBOF;
	bool FEOF;
	bool FGoToFirstRecordOnExecute;
	bool FOpen;
	bool FPrepared;
	int FRecordCount;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FCursor;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FCursor;
#endif /* _WIN64 */
	void * *FHandle;
	System::Classes::TNotifyEvent FOnSQLChanging;
	System::Classes::TStrings* FSQL;
	bool FParamCheck;
	System::Classes::TStrings* FProcessedSQL;
	TIBXSQLDA* FSQLParams;
	TIBXSQLDA* FSQLRecord;
	TIBSQLTypes FSQLType;
	bool FGenerateParamNames;
	Ibx::Ibintf::_di_IGDSLibrary FGDSLibrary;
	void __fastcall DoBeforeDatabaseDisconnect(System::TObject* Sender);
	Ibx::Ibdatabase::TIBDatabase* __fastcall GetDatabase();
	Ibx::Ibheader::PISC_DB_HANDLE __fastcall GetDBHandle();
	bool __fastcall GetEOF();
	TIBXSQLVAR* __fastcall GetFields(const int Idx);
	int __fastcall GetFieldIndex(System::UnicodeString FieldName);
	System::UnicodeString __fastcall GetPlan();
	int __fastcall GetRecordCount();
	int __fastcall GetRowsAffected();
	TIBXSQLDA* __fastcall GetSQLParams();
	Ibx::Ibdatabase::TIBTransaction* __fastcall GetTransaction();
	Ibx::Ibheader::PISC_TR_HANDLE __fastcall GetTRHandle();
	void __fastcall PreprocessSQL();
	void __fastcall SetDatabase(Ibx::Ibdatabase::TIBDatabase* Value);
	void __fastcall SetSQL(System::Classes::TStrings* Value);
	void __fastcall SetTransaction(Ibx::Ibdatabase::TIBTransaction* Value);
	void __fastcall SQLChanging(System::TObject* Sender);
	void __fastcall BeforeTransactionEnd(System::TObject* Sender);
	
public:
	__fastcall virtual TIBSQL(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBSQL();
	NativeInt __fastcall Call(NativeInt ErrCode, bool RaiseError);
	void __fastcall CheckClosed();
	void __fastcall CheckOpen();
	void __fastcall CheckValidStatement();
	void __fastcall Close();
	TIBXSQLDA* __fastcall Current();
	void __fastcall ExecQuery();
	TIBXSQLVAR* __fastcall FieldByName(System::UnicodeString FieldName);
	TIBXSQLVAR* __fastcall FindField(System::UnicodeString FieldName);
	void __fastcall FreeHandle();
	TIBXSQLDA* __fastcall Next();
	bool __fastcall IsEmpty();
	void __fastcall Prepare();
	void __fastcall Unprepare();
	System::UnicodeString __fastcall GetUniqueRelationName();
	TIBXSQLVAR* __fastcall ParamByName(System::UnicodeString Idx);
	__property bool Bof = {read=FBOF, nodefault};
	__property Ibx::Ibheader::PISC_DB_HANDLE DBHandle = {read=GetDBHandle};
	__property bool Eof = {read=GetEOF, nodefault};
	__property TIBXSQLVAR* Fields[const int Idx] = {read=GetFields};
	__property int FieldIndex[System::UnicodeString FieldName] = {read=GetFieldIndex};
	__property bool Open = {read=FOpen, nodefault};
	__property TIBXSQLDA* Params = {read=GetSQLParams};
	__property System::UnicodeString Plan = {read=GetPlan};
	__property bool Prepared = {read=FPrepared, nodefault};
	__property int RecordCount = {read=GetRecordCount, nodefault};
	__property int RowsAffected = {read=GetRowsAffected, nodefault};
	__property TIBSQLTypes SQLType = {read=FSQLType, nodefault};
	__property Ibx::Ibheader::PISC_TR_HANDLE TRHandle = {read=GetTRHandle};
	__property Ibx::Ibexternals::PVoid Handle = {read=FHandle};
	__property bool GenerateParamNames = {read=FGenerateParamNames, write=FGenerateParamNames, nodefault};
	__property System::UnicodeString UniqueRelationName = {read=GetUniqueRelationName};
	__property int FieldCount = {read=GetFieldCount, nodefault};
	__property bool Canceled = {read=FCanceled, nodefault};
	
__published:
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=GetDatabase, write=SetDatabase};
	__property bool GoToFirstRecordOnExecute = {read=FGoToFirstRecordOnExecute, write=FGoToFirstRecordOnExecute, default=1};
	__property bool ParamCheck = {read=FParamCheck, write=FParamCheck, default=1};
	__property System::Classes::TStrings* SQL = {read=FSQL, write=SetSQL};
	__property Ibx::Ibdatabase::TIBTransaction* Transaction = {read=GetTransaction, write=SetTransaction};
	__property System::Classes::TNotifyEvent OnSQLChanging = {read=FOnSQLChanging, write=FOnSQLChanging};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibsql */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBSQL)
using namespace Ibx::Ibsql;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbsqlHPP
