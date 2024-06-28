// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DBXCustomDataGenerator.pas' rev: 34.00 (iOS)

#ifndef DbxcustomdatageneratorHPP
#define DbxcustomdatageneratorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXMetaDataProvider.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Dbxcustomdatagenerator
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXCustomDataGenerator;
class DELPHICLASS TDBXDataGeneratedReader;
class DELPHICLASS TDBXDataGeneratedRow;
class DELPHICLASS TDBXDataGeneratorColumn;
class DELPHICLASS TDBXBooleanSequenceGenerator;
class DELPHICLASS TDBXBlobSequenceGenerator;
class DELPHICLASS TDBXAnsiStringSequenceGenerator;
class DELPHICLASS TDBXDataGeneratorException;
class DELPHICLASS TDBXDateSequenceGenerator;
class DELPHICLASS TDBXDecimalSequenceGenerator;
class DELPHICLASS TDBXDoubleSequenceGenerator;
class DELPHICLASS TDBXInt16SequenceGenerator;
class DELPHICLASS TDBXInt32SequenceGenerator;
class DELPHICLASS TDBXInt64SequenceGenerator;
class DELPHICLASS TDBXInt8SequenceGenerator;
class DELPHICLASS TDBXTimeSequenceGenerator;
class DELPHICLASS TDBXTimestampSequenceGenerator;
class DELPHICLASS TDBXWideStringSequenceGenerator;
//-- type declarations -------------------------------------------------------
typedef System::DynamicArray<TDBXDataGeneratorColumn*> TDBXDataGeneratorColumnArray;

class PASCALIMPLEMENTATION TDBXCustomDataGenerator : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual void __fastcall AddColumn(TDBXDataGeneratorColumn* const Column);
	__fastcall virtual ~TDBXCustomDataGenerator();
	virtual TDBXDataGeneratorColumn* __fastcall GetColumn(const int Ordinal);
	virtual void __fastcall Open();
	virtual System::UnicodeString __fastcall CreateInsertStatement(const int Row)/* overload */;
	virtual System::UnicodeString __fastcall CreateInsertStatement(const TDBXDataGeneratorColumnArray InsertColumns, const int Row)/* overload */;
	virtual System::UnicodeString __fastcall CreateParameterizedInsertStatement()/* overload */;
	virtual System::UnicodeString __fastcall CreateParameterizedInsertStatement(const TDBXDataGeneratorColumnArray InsertColumns)/* overload */;
	virtual void __fastcall Next();
	
protected:
	virtual int __fastcall GetColumnCount();
	virtual System::UnicodeString __fastcall GetTableName();
	virtual void __fastcall SetTableName(const System::UnicodeString TableName);
	virtual Data::Dbxmetadataprovider::TDBXMetaDataProvider* __fastcall GetMetaDataProvider();
	virtual void __fastcall SetMetaDataProvider(Data::Dbxmetadataprovider::TDBXMetaDataProvider* const MetaDataProvider);
	
private:
	System::UnicodeString __fastcall ColumnNameString(const TDBXDataGeneratorColumnArray Columns);
	System::UnicodeString __fastcall ValueString(const TDBXDataGeneratorColumnArray Columns, const int Row);
	System::UnicodeString __fastcall MarkerString();
	System::UnicodeString __fastcall CreateInsertStatement(const TDBXDataGeneratorColumnArray InsertColumns, const int Row, const bool Prepare)/* overload */;
	System::UnicodeString FTableName;
	int FRow;
	TDBXDataGeneratorColumnArray FColumns;
	Data::Dbxmetadataprovider::TDBXMetaDataProvider* FMetaDataProvider;
	
public:
	__property int ColumnCount = {read=GetColumnCount, nodefault};
	__property System::UnicodeString TableName = {read=GetTableName, write=SetTableName};
	__property Data::Dbxmetadataprovider::TDBXMetaDataProvider* MetaDataProvider = {read=GetMetaDataProvider, write=SetMetaDataProvider};
public:
	/* TObject.Create */ inline __fastcall TDBXCustomDataGenerator() : System::TObject() { }
	
};


class PASCALIMPLEMENTATION TDBXDataGeneratedReader : public Data::Dbxcommon::TDBXReader
{
	typedef Data::Dbxcommon::TDBXReader inherited;
	
public:
	__fastcall TDBXDataGeneratedReader(const __int64 ARowCount, const TDBXDataGeneratorColumnArray AGeneratorColumns);
	__fastcall virtual ~TDBXDataGeneratedReader();
	virtual bool __fastcall Reset();
	virtual bool __fastcall DerivedNext();
	virtual bool __fastcall CompareReader(Data::Dbxcommon::TDBXReader* const Reader);
	virtual void __fastcall DerivedClose();
	
protected:
	virtual Data::Dbxcommon::TDBXByteReader* __fastcall GetByteReader();
	virtual __int64 __fastcall GetPosition();
	
private:
	void __fastcall CreateValues();
	void __fastcall GenerateValues();
	__int64 FPosition;
	__int64 FRowCount;
	int FLastOrdinalCompared;
	TDBXDataGeneratorColumnArray FGeneratorColumns;
	
public:
	__property __int64 Position = {read=GetPosition};
	__property int LastOrdinalCompared = {read=FLastOrdinalCompared, nodefault};
};


class PASCALIMPLEMENTATION TDBXDataGeneratedRow : public Data::Dbxcommon::TDBXRow
{
	typedef Data::Dbxcommon::TDBXRow inherited;
	
public:
	__fastcall TDBXDataGeneratedRow(Data::Dbxcommon::TDBXContext* const Context);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDataGeneratedRow() { }
	
};


class PASCALIMPLEMENTATION TDBXDataGeneratorColumn : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall TDBXDataGeneratorColumn(Data::Dbxmetadataprovider::TDBXMetaDataColumn* const InMetaDataColumn);
	virtual void __fastcall Open();
	__fastcall virtual ~TDBXDataGeneratorColumn();
	virtual System::UnicodeString __fastcall GetString(const __int64 Row) = 0 ;
	virtual bool __fastcall GetBoolean(const __int64 Row);
	virtual System::Byte __fastcall GetInt8(const __int64 Row);
	virtual short __fastcall GetInt16(const __int64 Row);
	virtual int __fastcall GetInt32(const __int64 Row);
	virtual __int64 __fastcall GetInt64(const __int64 Row);
	virtual double __fastcall GetDouble(const __int64 Row);
	virtual float __fastcall GetSingle(const __int64 Row);
	virtual System::TArray__1<System::Byte> __fastcall GetBytes(const __int64 Row);
	virtual System::UnicodeString __fastcall GetDecimal(const __int64 Row);
	virtual int __fastcall GetYear(const __int64 Row);
	virtual int __fastcall GetMonth(const __int64 Row);
	virtual int __fastcall GetDay(const __int64 Row);
	virtual int __fastcall GetHour(const __int64 Row);
	virtual int __fastcall GetMinute(const __int64 Row);
	virtual int __fastcall GetSeconds(const __int64 Row);
	virtual int __fastcall GetMilliseconds(const __int64 Row);
	virtual void __fastcall SetValue(const __int64 Row, Data::Dbxcommon::TDBXWritableValue* const Value) = 0 ;
	
protected:
	virtual void __fastcall SetDataGenerator(TDBXCustomDataGenerator* const DataGenerator);
	virtual System::UnicodeString __fastcall GetColumnName();
	virtual int __fastcall GetDataType();
	virtual Data::Dbxmetadataprovider::TDBXMetaDataColumn* __fastcall GetMetaDataColumn();
	
private:
	TDBXDataGeneratorException* __fastcall TypeNotSupported();
	
protected:
	Data::Dbxmetadataprovider::TDBXMetaDataColumn* FMetaDataColumn;
	TDBXCustomDataGenerator* FDataGenerator;
	
public:
	__property TDBXCustomDataGenerator* DataGenerator = {write=SetDataGenerator};
	__property System::UnicodeString ColumnName = {read=GetColumnName};
	__property int DataType = {read=GetDataType, nodefault};
	__property Data::Dbxmetadataprovider::TDBXMetaDataColumn* MetaDataColumn = {read=GetMetaDataColumn};
};


class PASCALIMPLEMENTATION TDBXBooleanSequenceGenerator : public TDBXDataGeneratorColumn
{
	typedef TDBXDataGeneratorColumn inherited;
	
public:
	__fastcall TDBXBooleanSequenceGenerator(Data::Dbxmetadataprovider::TDBXMetaDataColumn* const MetaData);
	virtual void __fastcall Open();
	virtual bool __fastcall GetBoolean(const __int64 Row);
	virtual System::UnicodeString __fastcall GetString(const __int64 Row);
	virtual System::Byte __fastcall GetInt8(const __int64 Row);
	virtual void __fastcall SetValue(const __int64 Row, Data::Dbxcommon::TDBXWritableValue* const Value);
public:
	/* TDBXDataGeneratorColumn.Destroy */ inline __fastcall virtual ~TDBXBooleanSequenceGenerator() { }
	
};


class PASCALIMPLEMENTATION TDBXBlobSequenceGenerator : public TDBXDataGeneratorColumn
{
	typedef TDBXDataGeneratorColumn inherited;
	
public:
	__fastcall TDBXBlobSequenceGenerator(Data::Dbxmetadataprovider::TDBXMetaDataColumn* const MetaData);
	virtual void __fastcall Open();
	virtual System::UnicodeString __fastcall GetString(const __int64 Row);
	virtual System::TArray__1<System::Byte> __fastcall GetBytes(const __int64 Row);
	virtual void __fastcall SetValue(const __int64 Row, Data::Dbxcommon::TDBXWritableValue* const Value);
public:
	/* TDBXDataGeneratorColumn.Destroy */ inline __fastcall virtual ~TDBXBlobSequenceGenerator() { }
	
};


class PASCALIMPLEMENTATION TDBXAnsiStringSequenceGenerator : public TDBXDataGeneratorColumn
{
	typedef TDBXDataGeneratorColumn inherited;
	
public:
	__fastcall TDBXAnsiStringSequenceGenerator(Data::Dbxmetadataprovider::TDBXMetaDataColumn* const MetaData);
	virtual void __fastcall Open();
	virtual System::UnicodeString __fastcall GetString(const __int64 Row);
	virtual void __fastcall SetValue(const __int64 Row, Data::Dbxcommon::TDBXWritableValue* const Value);
public:
	/* TDBXDataGeneratorColumn.Destroy */ inline __fastcall virtual ~TDBXAnsiStringSequenceGenerator() { }
	
};


class PASCALIMPLEMENTATION TDBXDataGeneratorException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	__fastcall TDBXDataGeneratorException(const System::UnicodeString Message);
public:
	/* Exception.CreateFmt */ inline __fastcall TDBXDataGeneratorException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall TDBXDataGeneratorException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall TDBXDataGeneratorException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall TDBXDataGeneratorException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall TDBXDataGeneratorException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall TDBXDataGeneratorException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall TDBXDataGeneratorException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDBXDataGeneratorException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDBXDataGeneratorException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDBXDataGeneratorException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDBXDataGeneratorException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~TDBXDataGeneratorException() { }
	
};


class PASCALIMPLEMENTATION TDBXDateSequenceGenerator : public TDBXDataGeneratorColumn
{
	typedef TDBXDataGeneratorColumn inherited;
	
public:
	__fastcall TDBXDateSequenceGenerator(Data::Dbxmetadataprovider::TDBXMetaDataColumn* const MetaData);
	virtual void __fastcall Open();
	virtual int __fastcall GetYear(const __int64 Row);
	virtual int __fastcall GetMonth(const __int64 Row);
	virtual int __fastcall GetDay(const __int64 Row);
	virtual System::UnicodeString __fastcall GetString(const __int64 Row);
	virtual void __fastcall SetValue(const __int64 Row, Data::Dbxcommon::TDBXWritableValue* const Value);
public:
	/* TDBXDataGeneratorColumn.Destroy */ inline __fastcall virtual ~TDBXDateSequenceGenerator() { }
	
};


class PASCALIMPLEMENTATION TDBXDecimalSequenceGenerator : public TDBXDataGeneratorColumn
{
	typedef TDBXDataGeneratorColumn inherited;
	
public:
	__fastcall TDBXDecimalSequenceGenerator(Data::Dbxmetadataprovider::TDBXMetaDataColumn* const MetaData);
	virtual void __fastcall Open();
	virtual System::UnicodeString __fastcall GetDecimal(const __int64 Row);
	virtual System::UnicodeString __fastcall GetString(const __int64 Row);
	virtual void __fastcall SetValue(const __int64 Row, Data::Dbxcommon::TDBXWritableValue* const Value);
public:
	/* TDBXDataGeneratorColumn.Destroy */ inline __fastcall virtual ~TDBXDecimalSequenceGenerator() { }
	
};


class PASCALIMPLEMENTATION TDBXDoubleSequenceGenerator : public TDBXDataGeneratorColumn
{
	typedef TDBXDataGeneratorColumn inherited;
	
public:
	__fastcall TDBXDoubleSequenceGenerator(Data::Dbxmetadataprovider::TDBXMetaDataColumn* const MetaData);
	virtual void __fastcall Open();
	virtual double __fastcall GetDouble(const __int64 Row);
	virtual System::UnicodeString __fastcall GetString(const __int64 Row);
	virtual void __fastcall SetValue(const __int64 Row, Data::Dbxcommon::TDBXWritableValue* const Value);
public:
	/* TDBXDataGeneratorColumn.Destroy */ inline __fastcall virtual ~TDBXDoubleSequenceGenerator() { }
	
};


class PASCALIMPLEMENTATION TDBXInt16SequenceGenerator : public TDBXDataGeneratorColumn
{
	typedef TDBXDataGeneratorColumn inherited;
	
public:
	__fastcall TDBXInt16SequenceGenerator(Data::Dbxmetadataprovider::TDBXMetaDataColumn* const MetaData);
	virtual void __fastcall Open();
	virtual short __fastcall GetInt16(const __int64 Row);
	virtual System::UnicodeString __fastcall GetString(const __int64 Row);
	virtual void __fastcall SetValue(const __int64 Row, Data::Dbxcommon::TDBXWritableValue* const Value);
public:
	/* TDBXDataGeneratorColumn.Destroy */ inline __fastcall virtual ~TDBXInt16SequenceGenerator() { }
	
};


class PASCALIMPLEMENTATION TDBXInt32SequenceGenerator : public TDBXDataGeneratorColumn
{
	typedef TDBXDataGeneratorColumn inherited;
	
public:
	__fastcall TDBXInt32SequenceGenerator(Data::Dbxmetadataprovider::TDBXMetaDataColumn* const MetaData);
	virtual void __fastcall Open();
	virtual int __fastcall GetInt32(const __int64 Row);
	virtual System::UnicodeString __fastcall GetString(const __int64 Row);
	virtual void __fastcall SetValue(const __int64 Row, Data::Dbxcommon::TDBXWritableValue* const Value);
public:
	/* TDBXDataGeneratorColumn.Destroy */ inline __fastcall virtual ~TDBXInt32SequenceGenerator() { }
	
};


class PASCALIMPLEMENTATION TDBXInt64SequenceGenerator : public TDBXDataGeneratorColumn
{
	typedef TDBXDataGeneratorColumn inherited;
	
public:
	__fastcall TDBXInt64SequenceGenerator(Data::Dbxmetadataprovider::TDBXMetaDataColumn* const MetaData);
	virtual void __fastcall Open();
	virtual __int64 __fastcall GetInt64(const __int64 Row);
	virtual System::UnicodeString __fastcall GetString(const __int64 Row);
	virtual void __fastcall SetValue(const __int64 Row, Data::Dbxcommon::TDBXWritableValue* const Value);
public:
	/* TDBXDataGeneratorColumn.Destroy */ inline __fastcall virtual ~TDBXInt64SequenceGenerator() { }
	
};


class PASCALIMPLEMENTATION TDBXInt8SequenceGenerator : public TDBXDataGeneratorColumn
{
	typedef TDBXDataGeneratorColumn inherited;
	
public:
	__fastcall TDBXInt8SequenceGenerator(Data::Dbxmetadataprovider::TDBXMetaDataColumn* const MetaData);
	virtual void __fastcall Open();
	virtual System::Byte __fastcall GetInt8(const __int64 Row);
	virtual System::UnicodeString __fastcall GetString(const __int64 Row);
	virtual void __fastcall SetValue(const __int64 Row, Data::Dbxcommon::TDBXWritableValue* const Value);
public:
	/* TDBXDataGeneratorColumn.Destroy */ inline __fastcall virtual ~TDBXInt8SequenceGenerator() { }
	
};


class PASCALIMPLEMENTATION TDBXTimeSequenceGenerator : public TDBXDataGeneratorColumn
{
	typedef TDBXDataGeneratorColumn inherited;
	
public:
	__fastcall TDBXTimeSequenceGenerator(Data::Dbxmetadataprovider::TDBXMetaDataColumn* const MetaData);
	virtual void __fastcall Open();
	virtual int __fastcall GetHour(const __int64 Row);
	virtual int __fastcall GetMinute(const __int64 Row);
	virtual int __fastcall GetSeconds(const __int64 Row);
	virtual System::UnicodeString __fastcall GetString(const __int64 Row);
	virtual void __fastcall SetValue(const __int64 Row, Data::Dbxcommon::TDBXWritableValue* const Value);
public:
	/* TDBXDataGeneratorColumn.Destroy */ inline __fastcall virtual ~TDBXTimeSequenceGenerator() { }
	
};


class PASCALIMPLEMENTATION TDBXTimestampSequenceGenerator : public TDBXDataGeneratorColumn
{
	typedef TDBXDataGeneratorColumn inherited;
	
public:
	__fastcall TDBXTimestampSequenceGenerator(Data::Dbxmetadataprovider::TDBXMetaDataColumn* const MetaData);
	virtual void __fastcall Open();
	virtual int __fastcall GetYear(const __int64 Row);
	virtual int __fastcall GetMonth(const __int64 Row);
	virtual int __fastcall GetDay(const __int64 Row);
	virtual int __fastcall GetHour(const __int64 Row);
	virtual int __fastcall GetMinute(const __int64 Row);
	virtual int __fastcall GetSeconds(const __int64 Row);
	virtual int __fastcall GetMilliseconds(const __int64 Row);
	virtual System::UnicodeString __fastcall GetString(const __int64 Row);
	virtual void __fastcall SetValue(const __int64 Row, Data::Dbxcommon::TDBXWritableValue* const Value);
public:
	/* TDBXDataGeneratorColumn.Destroy */ inline __fastcall virtual ~TDBXTimestampSequenceGenerator() { }
	
};


class PASCALIMPLEMENTATION TDBXWideStringSequenceGenerator : public TDBXDataGeneratorColumn
{
	typedef TDBXDataGeneratorColumn inherited;
	
public:
	__fastcall TDBXWideStringSequenceGenerator(Data::Dbxmetadataprovider::TDBXMetaDataColumn* const MetaData);
	virtual void __fastcall Open();
	virtual System::UnicodeString __fastcall GetString(const __int64 Row);
	virtual void __fastcall SetValue(const __int64 Row, Data::Dbxcommon::TDBXWritableValue* const Value);
public:
	/* TDBXDataGeneratorColumn.Destroy */ inline __fastcall virtual ~TDBXWideStringSequenceGenerator() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxcustomdatagenerator */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DBXCUSTOMDATAGENERATOR)
using namespace Dbxcustomdatagenerator;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DbxcustomdatageneratorHPP
