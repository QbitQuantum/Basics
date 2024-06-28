// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DbxDataGenerator.pas' rev: 34.00 (iOS)

#ifndef DbxdatageneratorHPP
#define DbxdatageneratorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.SqlExpr.hpp>
#include <Data.DB.hpp>
#include <Data.DBXCommon.hpp>
#include <DBXCustomDataGenerator.hpp>
#include <Data.FmtBcd.hpp>
#include <System.SysUtils.hpp>
#include <Data.SqlTimSt.hpp>

//-- user supplied -----------------------------------------------------------
#ifdef USEPACKAGES
#pragma link "dbtest.bpi"
#pragma link "dbexpress.bpi"
#pragma link "DbxCommonDriver.bpi"
#pragma link "dsnap.bpi"
#pragma link "dbrtl.bpi"
#else
#pragma link "dbtest.lib"
#pragma link "dbexpress.lib"
#pragma link "DbxCommonDriver.lib"
#pragma link "dsnap.lib"
#pragma link "dbrtl.lib"
#endif

namespace Dbxdatagenerator
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDbxDataGenerator;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDbxDataGenerator : public Dbxcustomdatagenerator::TDBXCustomDataGenerator
{
	typedef Dbxcustomdatagenerator::TDBXCustomDataGenerator inherited;
	
private:
	Data::Db::TParam* FParam;
	bool __fastcall GetIsFractionsSupported();
	void __fastcall SetParameter(int Ordinal, int Row, Data::Db::TParam* Param);
	void __fastcall ValidateParam(int Ordinal, int Row, Data::Db::TParam* Param);
	
public:
	__fastcall TDbxDataGenerator();
	__fastcall virtual ~TDbxDataGenerator();
	static void __fastcall ValidateAnsiString(System::UnicodeString Value1, System::UnicodeString Value2);
	static void __fastcall ValidateWideString(System::UnicodeString Value1, System::UnicodeString Value2);
	static void __fastcall ValidateBoolean(bool Value1, bool Value2);
	static void __fastcall ValidateInt64(__int64 Value1, __int64 Value2);
	static void __fastcall ValidateSingle(float Value1, float Value2);
	static void __fastcall ValidateDouble(double Value1, double Value2);
	static void __fastcall ValidateBcd(const Data::Fmtbcd::TBcd &Value1, const Data::Fmtbcd::TBcd &Value2);
	static void __fastcall ValidateDate(Data::Dbxcommon::TDBXDate Value1, Data::Dbxcommon::TDBXDate Value2);
	static void __fastcall ValidateTime(Data::Dbxcommon::TDBXTime Value1, Data::Dbxcommon::TDBXTime Value2);
	static void __fastcall ValidateTimestamp(const Data::Sqltimst::TSQLTimeStamp &Value1, const Data::Sqltimst::TSQLTimeStamp &Value2);
	static void __fastcall ValidateTimestampOffset(const Data::Sqltimst::TSQLTimeStampOffset &Value1, const Data::Sqltimst::TSQLTimeStampOffset &Value2);
	static void __fastcall ValidateDateTime(System::TDateTime Value1, System::TDateTime Value2);
	static void __fastcall ValidateBytes(System::TArray__1<System::Byte> Value1, System::TArray__1<System::Byte> Value2);
	static bool __fastcall BytesEquals(const System::TArray__1<System::Byte> Value1, const System::TArray__1<System::Byte> Value2, int Count);
	__classmethod void __fastcall ReadBytesFromStream(Data::Dbxcommon::TDBXValue* Value, System::TArray__1<System::Byte> &Buffer);
	bool __fastcall ValidateRow(Data::Dbxcommon::TDBXReader* const Reader, int Row)/* overload */;
	bool __fastcall ValidateRow(Data::Db::TDataSet* const DataSet, int Row)/* overload */;
	void __fastcall ValidateParameters(Data::Dbxcommon::TDBXCommand* const Command, int Row);
	void __fastcall ValidateParams(Data::Db::TParams* const Params);
	void __fastcall AddParameters(Data::Dbxcommon::TDBXCommand* const Command)/* overload */;
	void __fastcall AddParameters(Data::Sqlexpr::TSQLQuery* const SQLQuery)/* overload */;
	void __fastcall SetInsertParameters(Data::Dbxcommon::TDBXCommand* const Command, int Row)/* overload */;
	void __fastcall SetInsertParameters(Data::Sqlexpr::TSQLQuery* const SQLQuery, int Row)/* overload */;
	void __fastcall PopulateParams(Data::Db::TParams* Params);
	void __fastcall PopulateDataset(Data::Db::TDataSet* DataSet, int RowCount);
	__property bool IsFractionsSupported = {read=GetIsFractionsSupported, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxdatagenerator */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DBXDATAGENERATOR)
using namespace Dbxdatagenerator;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DbxdatageneratorHPP
