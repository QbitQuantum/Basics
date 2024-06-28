// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXCDSReaders.pas' rev: 34.00 (Android)

#ifndef Data_DbxcdsreadersHPP
#define Data_DbxcdsreadersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Datasnap.DBClient.hpp>
#include <Data.DB.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXPlatform.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXDBReaders.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxcdsreaders
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXCDSOriginalRow;
class DELPHICLASS TDBXClientDataSetTable;
class DELPHICLASS TDBXClientDataSetReader;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXCDSOriginalRow : public Data::Dbxdbreaders::TDBXDBTable
{
	typedef Data::Dbxdbreaders::TDBXDBTable inherited;
	
private:
	bool FAtEnd;
	TDBXClientDataSetTable* FClonedTable;
	TDBXClientDataSetTable* FClientTable;
	
protected:
	virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
	
public:
	__fastcall TDBXCDSOriginalRow(TDBXClientDataSetTable* ClientTable);
	virtual int __fastcall GetOrdinal(const System::UnicodeString ColumnName)/* overload */;
	virtual bool __fastcall First();
	virtual bool __fastcall Next();
	virtual bool __fastcall InBounds();
	virtual Data::Dbxcommon::TDBXValueTypeArray __fastcall GetColumns();
public:
	/* TDBXRowTable.Destroy */ inline __fastcall virtual ~TDBXCDSOriginalRow() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXClientDataSetTable : public Data::Dbxdbreaders::TDBXDataSetTable
{
	typedef Data::Dbxdbreaders::TDBXDataSetTable inherited;
	
private:
	TDBXCDSOriginalRow* FOriginal;
	Datasnap::Dbclient::TClientDataSet* FClientDataset;
	
protected:
	__fastcall TDBXClientDataSetTable(const System::UnicodeString CollectionName, Data::Dbxcommon::TDBXValueTypeArray TableColumns, Datasnap::Dbclient::TClientDataSet* Table, bool OwnsTable)/* overload */;
	virtual void __fastcall SkipOriginalRow();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall GetDeletedRows();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall GetInsertedRows();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall GetUpdatedRows();
	virtual Data::Dbxcommontable::TDBXTableRow* __fastcall GetOriginalRow();
	
public:
	__fastcall TDBXClientDataSetTable()/* overload */;
	__fastcall TDBXClientDataSetTable(Datasnap::Dbclient::TClientDataSet* ClientDataSet, bool OwnsTable)/* overload */;
	__fastcall virtual ~TDBXClientDataSetTable();
	virtual void __fastcall AcceptChanges();
	virtual void __fastcall Clear();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall CreateTableView(const System::UnicodeString OrderByColumnName);
	virtual bool __fastcall FindStringKey(const int Ordinal, const System::UnicodeString Value);
	virtual void __fastcall SetColumns(const Data::Dbxcommon::TDBXValueTypeArray Columns);
protected:
	/* TDBXDataSetTable.Create */ inline __fastcall TDBXClientDataSetTable(const System::UnicodeString CollectionName, Data::Db::TDataSet* Table, bool OwnsTable, bool ValuesNeedCreate)/* overload */ : Data::Dbxdbreaders::TDBXDataSetTable(CollectionName, Table, OwnsTable, ValuesNeedCreate) { }
	
public:
	/* TDBXDataSetTable.Create */ inline __fastcall TDBXClientDataSetTable(Data::Db::TDataSet* Dataset, bool InstanceOwner)/* overload */ : Data::Dbxdbreaders::TDBXDataSetTable(Dataset, InstanceOwner) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXClientDataSetReader : public Data::Dbxdbreaders::TDBXDataSetReader
{
	typedef Data::Dbxdbreaders::TDBXDataSetReader inherited;
	
public:
	__fastcall virtual TDBXClientDataSetReader(Data::Db::TDataSet* Params, bool InstanceOwner)/* overload */;
	static void __fastcall CopyReaderToClientDataSet(Data::Dbxcommon::TDBXReader* Reader, Datasnap::Dbclient::TClientDataSet* Dataset);
	static Datasnap::Dbclient::TClientDataSet* __fastcall ToClientDataSet(System::Classes::TComponent* AOwner, Data::Dbxcommon::TDBXReader* Reader, bool AOwnsInstance);
public:
	/* TDBXDataSetReader.Create */ inline __fastcall TDBXClientDataSetReader(Data::Dbxdbreaders::TDBXDataSetTable* Params)/* overload */ : Data::Dbxdbreaders::TDBXDataSetReader(Params) { }
	
public:
	/* TDBXTableReader.Create */ inline __fastcall TDBXClientDataSetReader(Data::Dbxcommontable::TDBXTable* const DbxTable)/* overload */ : Data::Dbxdbreaders::TDBXDataSetReader(DbxTable) { }
	/* TDBXTableReader.Create */ inline __fastcall TDBXClientDataSetReader(Data::Dbxcommon::TDBXContext* const Context, Data::Dbxcommontable::TDBXTable* const DbxTable)/* overload */ : Data::Dbxdbreaders::TDBXDataSetReader(Context, DbxTable) { }
	/* TDBXTableReader.Destroy */ inline __fastcall virtual ~TDBXClientDataSetReader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxcdsreaders */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXCDSREADERS)
using namespace Data::Dbxcdsreaders;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxcdsreadersHPP
