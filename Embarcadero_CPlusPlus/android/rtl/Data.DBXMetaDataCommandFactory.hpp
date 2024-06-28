// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMetaDataCommandFactory.pas' rev: 34.00 (Android)

#ifndef Data_DbxmetadatacommandfactoryHPP
#define Data_DbxmetadatacommandfactoryHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXPlatform.hpp>
#include <Data.DBXSqlScanner.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXMetaDataReader.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmetadatacommandfactory
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXMetaDataCommandFactory;
class DELPHICLASS TDBXDataExpressProviderContext;
class DELPHICLASS TDBXMetaDataCommand;
class DELPHICLASS TDBXReaderTableStorage;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXMetaDataCommandFactory : public Data::Dbxcommon::TDBXCommandFactory
{
	typedef Data::Dbxcommon::TDBXCommandFactory inherited;
	
public:
	static void __fastcall RegisterMetaDataCommandFactory(const System::TClass ObjectClass);
	static void __fastcall UnRegisterMetaDataCommandFactory(const System::TClass ObjectClass);
	virtual Data::Dbxcommon::TDBXCommand* __fastcall CreateCommand(Data::Dbxcommon::TDBXContext* DbxContext, Data::Dbxcommon::TDBXConnection* Connection, Data::Dbxcommon::TDBXCommand* MorphicCommand);
	virtual Data::Dbxmetadatareader::TDBXMetaDataReader* __fastcall CreateMetaDataReader() = 0 ;
	virtual System::UnicodeString __fastcall GetProductName();
public:
	/* TObject.Create */ inline __fastcall TDBXMetaDataCommandFactory() : Data::Dbxcommon::TDBXCommandFactory() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDataCommandFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDataExpressProviderContext : public Data::Dbxmetadatareader::TDBXProviderContext
{
	typedef Data::Dbxmetadatareader::TDBXProviderContext inherited;
	
protected:
	Data::Dbxcommon::TDBXConnection* FConnection;
	Data::Dbxsqlscanner::TDBXSqlScanner* FScanner;
	System::UnicodeString FParameterMarker;
	bool FMarkerIncludedInParameterName;
	bool FUseAnsiStrings;
	bool FRemoveIsNull;
	
private:
	void __fastcall BindParametersByOrdinal(Data::Dbxcommon::TDBXCommand* Command, Data::Dbxplatform::TDBXStringArray ParameterNames, Data::Dbxplatform::TDBXStringArray ParameterValues);
	int __fastcall FindParameterByName(const System::UnicodeString ParameterName, Data::Dbxplatform::TDBXStringArray ParameterNames);
	
public:
	__fastcall TDBXDataExpressProviderContext();
	__fastcall virtual ~TDBXDataExpressProviderContext();
	virtual System::UnicodeString __fastcall GetPlatformTypeName(const int DataType, const bool IsUnsigned);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall ExecuteQuery(const System::UnicodeString Sql, const Data::Dbxplatform::TDBXStringArray ParameterNames, const Data::Dbxplatform::TDBXStringArray ParameterValues);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall CreateTableStorage(const System::UnicodeString CollectionName, const Data::Dbxcommon::TDBXValueTypeArray Columns);
	virtual Data::Dbxcommontable::TDBXTableRow* __fastcall CreateRowStorage(const System::UnicodeString CollectionName, const Data::Dbxcommon::TDBXValueTypeArray Columns);
	virtual void __fastcall StartTransaction();
	virtual void __fastcall StartSerializedTransaction();
	virtual void __fastcall Commit();
	virtual void __fastcall Rollback();
	virtual System::UnicodeString __fastcall GetVendorProperty(const System::UnicodeString name);
	
protected:
	System::UnicodeString __fastcall GetSqlParameterMarker();
	bool __fastcall GetMarkerIncludedInParameterName();
	
public:
	__property System::UnicodeString SqlParameterMarker = {read=FParameterMarker};
	__property bool IsMarkerIncludedInParameterName = {read=FMarkerIncludedInParameterName, nodefault};
	__property Data::Dbxcommon::TDBXConnection* Connection = {read=FConnection, write=FConnection};
	__property bool UseAnsiStrings = {read=FUseAnsiStrings, write=FUseAnsiStrings, nodefault};
	__property bool RemoveIsNull = {read=FRemoveIsNull, write=FRemoveIsNull, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXMetaDataCommand : public Data::Dbxcommon::TDBXCommand
{
	typedef Data::Dbxcommon::TDBXCommand inherited;
	
public:
	__fastcall TDBXMetaDataCommand(Data::Dbxcommon::TDBXContext* DBXContext, Data::Dbxcommon::TDBXCommand* MorphicCommand, Data::Dbxmetadatareader::TDBXMetaDataReader* Provider);
	__fastcall virtual ~TDBXMetaDataCommand();
	
protected:
	virtual void __fastcall SetRowSetSize(const __int64 RowSetSize);
	virtual void __fastcall SetMaxBlobSize(const __int64 MaxBlobSize);
	virtual __int64 __fastcall GetRowsAffected();
	virtual Data::Dbxcommon::TDBXReader* __fastcall DerivedGetNextReader();
	virtual void __fastcall DerivedOpen();
	virtual void __fastcall DerivedClose();
	virtual void __fastcall DerivedPrepare();
	virtual Data::Dbxcommon::TDBXReader* __fastcall DerivedExecuteQuery();
	virtual void __fastcall DerivedExecuteUpdate();
	
private:
	Data::Dbxcommon::TDBXValueType* __fastcall CreateValueType(System::UnicodeString Name, int DataType, int Size);
	Data::Dbxcommontable::TDBXTable* __fastcall FetchDatabaseColumns();
	Data::Dbxcommon::TDBXCommand* FQueryCommand;
	Data::Dbxmetadatareader::TDBXMetaDataReader* FReader;
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXReaderTableStorage : public Data::Dbxcommontable::TDBXRowTable
{
	typedef Data::Dbxcommontable::TDBXRowTable inherited;
	
private:
	bool FLastNext;
	Data::Dbxcommon::TDBXCommand* FCommand;
	Data::Dbxcommon::TDBXReader* FReader;
	Data::Dbxcommon::TDBXValueTypeArray FColumns;
	bool FNextCalled;
	
public:
	__fastcall TDBXReaderTableStorage(Data::Dbxcommon::TDBXCommand* Command, Data::Dbxcommon::TDBXReader* Reader);
	__fastcall virtual ~TDBXReaderTableStorage();
	virtual int __fastcall GetOrdinal(const System::UnicodeString ColumnName)/* overload */;
	virtual bool __fastcall First();
	virtual bool __fastcall Next();
	virtual bool __fastcall InBounds();
	virtual void __fastcall Close();
	
protected:
	virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
	virtual Data::Dbxcommon::TDBXValueTypeArray __fastcall GetColumns();
	virtual System::TObject* __fastcall GetStorage();
	virtual System::TObject* __fastcall GetCommand();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmetadatacommandfactory */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMETADATACOMMANDFACTORY)
using namespace Data::Dbxmetadatacommandfactory;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmetadatacommandfactoryHPP
