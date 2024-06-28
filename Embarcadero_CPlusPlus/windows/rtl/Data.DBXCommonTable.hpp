// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXCommonTable.pas' rev: 34.00 (Windows)

#ifndef Data_DbxcommontableHPP
#define Data_DbxcommontableHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.JSON.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXDelegate.hpp>
#include <Data.DBXPlatform.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxcommontable
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXActiveTableReaderItem;
class DELPHICLASS TDBXActiveTableReaderList;
class DELPHICLASS TDBXJSONTableReader;
class DELPHICLASS TDBXSQLColumnFlags;
class DELPHICLASS TDBXStreamerRow;
class DELPHICLASS TDBXNoOpRow;
class DELPHICLASS TDBXTableEntity;
class DELPHICLASS TDBXTableReader;
class DELPHICLASS TDBXTableRow;
class DELPHICLASS TDBXTable;
class DELPHICLASS TDBXDelegateTable;
class DELPHICLASS TDBXStringTrimTable;
class DELPHICLASS TDBXTrimStringValue;
class DELPHICLASS TDBXReaderTable;
class DELPHICLASS TDBXRowTable;
class DELPHICLASS TDBXCustomValueRow;
class DELPHICLASS TDBXSingleValueRow;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXActiveTableReaderItem : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall virtual ~TDBXActiveTableReaderItem();
	void __fastcall ResetEos();
	void __fastcall SetParameterEos(const int ParameterOrdinal, const bool Eos);
	bool __fastcall IsParameterEos(const int ParameterOrdinal);
	
protected:
	bool __fastcall IsReaderEos();
	void __fastcall SetParameterList(Data::Dbxcommon::TDBXParameterList* const AParameterList);
	void __fastcall SetReader(Data::Dbxcommon::TDBXReader* const AReader);
	virtual void __fastcall SetStreamerRow(TDBXStreamerRow* const StreamerRow);
	virtual TDBXStreamerRow* __fastcall GetStreamerRow();
	virtual void __fastcall SetReaderEos(const bool Eos);
	
private:
	void __fastcall InitEos();
	
public:
	int FStreamerRowHandle;
	TDBXActiveTableReaderItem* FNext;
	
private:
	TDBXStreamerRow* FStreamerRow;
	Data::Dbxcommon::TDBXParameterList* FParameterList;
	Data::Dbxcommon::TDBXReader* FReader;
	bool FEos;
	Data::Dbxplatform::TDBXBooleans FEosParams;
	bool FOwnsRow;
	bool FIsParameterRow;
	
public:
	__property Data::Dbxcommon::TDBXParameterList* ParameterList = {read=FParameterList, write=SetParameterList};
	__property bool ReaderEos = {read=IsReaderEos, write=SetReaderEos, nodefault};
	__property Data::Dbxcommon::TDBXReader* Reader = {read=FReader, write=SetReader};
	__property TDBXStreamerRow* StreamerRow = {read=GetStreamerRow, write=SetStreamerRow};
	__property bool OwnsRow = {write=FOwnsRow, nodefault};
	__property bool ParameterRow = {read=FIsParameterRow, write=FIsParameterRow, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDBXActiveTableReaderItem() : System::TObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXActiveTableReaderList : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall virtual ~TDBXActiveTableReaderList();
	int __fastcall AllocateRowHandle();
	TDBXActiveTableReaderItem* __fastcall AddDBXStreamerRow(TDBXStreamerRow* const Row, const int RowHandle, const bool OwnsRow, const bool IsParameterRow);
	TDBXActiveTableReaderItem* __fastcall FindStreamerRowItem(const int StreamerRowHandle);
	void __fastcall CloseAllActiveTableReaders();
	
protected:
	bool __fastcall IsEos();
	
private:
	TDBXActiveTableReaderItem* FFirst;
	int FLastRowHandle;
	
public:
	__property bool Eos = {read=IsEos, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDBXActiveTableReaderList() : System::TObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXJSONTableReader : public Data::Dbxcommon::TDBXReader
{
	typedef Data::Dbxcommon::TDBXReader inherited;
	
public:
	__fastcall TDBXJSONTableReader(Data::Dbxcommon::TDBXContext* const DbxContext, System::Json::TJSONObject* const Table, const bool OwnsJSONObject);
	__fastcall virtual ~TDBXJSONTableReader();
	virtual bool __fastcall DerivedNext();
	virtual void __fastcall DerivedClose();
	virtual Data::Dbxcommon::TDBXValueType* __fastcall GetValueType(const int Ordinal);
	virtual Data::Dbxcommon::TDBXValue* __fastcall GetValue(const int Ordinal);
	
protected:
	virtual Data::Dbxcommon::TDBXByteReader* __fastcall GetByteReader();
	virtual int __fastcall GetColumnCount();
	
private:
	void __fastcall CleanRowValues();
	void __fastcall CleanValueTypes();
	Data::Dbxcommon::TDBXWritableValue* __fastcall CreateWritableValue(const int Ordinal);
	System::Json::TJSONPair* __fastcall GetColumnDataPair(int AIndex);
	Data::Dbxcommon::TDBXByteReader* FJsonTableByteReader;
	System::Json::TJSONObject* FJsonTable;
	int FRowNb;
	Data::Dbxcommon::TDBXValueTypeArray FValueTypes;
	Data::Dbxcommon::TDBXWritableValueArray FRow;
	int FColumnCount;
	bool FOwnsJsonTable;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSQLColumnFlags : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 FlagReadonly = System::Int8(0x1);
	
	static const System::Int8 FlagSearchable = System::Int8(0x2);
	
	static const System::Int8 FlagCurrency = System::Int8(0x4);
	
	static const System::Int8 FlagNullable = System::Int8(0x8);
	
	static const System::Int8 FlagSigned = System::Int8(0x10);
	
	static const System::Int8 FlagCasesensitive = System::Int8(0x20);
	
	static const System::Int8 FlagAutoincrement = System::Int8(0x40);
	
	static const System::Byte FlagInternalrow = System::Byte(0x80);
	
public:
	/* TObject.Create */ inline __fastcall TDBXSQLColumnFlags() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSQLColumnFlags() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXStreamerRow : public Data::Dbxcommon::TDBXRow
{
	typedef Data::Dbxcommon::TDBXRow inherited;
	
public:
	__fastcall TDBXStreamerRow(Data::Dbxcommon::TDBXContext* const AContext);
	void __fastcall RecordDBXReaderSet(Data::Dbxcommon::TDBXValueType* const ValueType);
	
protected:
	virtual void __fastcall ValueNotSet(Data::Dbxcommon::TDBXWritableValue* const Value);
	
private:
	int FRowHandle;
	int FFirstDBXReaderOrdinal;
	int FLastDBXReaderOrdinal;
	bool FNeedsNext;
	
public:
	__property int RowHandle = {read=FRowHandle, write=FRowHandle, nodefault};
	__property int FirstDBXReaderOrdinal = {read=FFirstDBXReaderOrdinal, nodefault};
	__property int LastDBXReaderOrdinal = {read=FLastDBXReaderOrdinal, nodefault};
	__property bool NeedsNext = {read=FNeedsNext, write=FNeedsNext, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXStreamerRow() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXNoOpRow : public TDBXStreamerRow
{
	typedef TDBXStreamerRow inherited;
	
public:
	__fastcall TDBXNoOpRow(Data::Dbxcommon::TDBXContext* const AContext);
	virtual Data::Dbxcommon::TDBXValue* __fastcall CreateCustomValue(Data::Dbxcommon::TDBXValueType* const ValueType);
	
protected:
	virtual void __fastcall NotImplemented();
	virtual int __fastcall GetGeneration();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXNoOpRow() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXTableEntity : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall TDBXTableEntity(TDBXTable* const ATable, const bool AOwnTable);
	__fastcall virtual ~TDBXTableEntity();
	
private:
	TDBXTable* FTable;
	bool FOwnTable;
	
public:
	__property TDBXTable* Table = {read=FTable};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXTableReader : public Data::Dbxcommon::TDBXReader
{
	typedef Data::Dbxcommon::TDBXReader inherited;
	
public:
	__fastcall TDBXTableReader(TDBXTable* const DbxTable)/* overload */;
	__fastcall TDBXTableReader(Data::Dbxcommon::TDBXContext* const Context, TDBXTable* const DbxTable)/* overload */;
	__fastcall virtual ~TDBXTableReader();
	virtual Data::Dbxcommon::TDBXValue* __fastcall GetValue(const int Ordinal);
	virtual Data::Dbxcommon::TDBXValueType* __fastcall GetValueType(const int Ordinal);
	virtual Data::Dbxcommon::TDBXValue* __fastcall GetValueByName(const System::UnicodeString Name);
	virtual bool __fastcall DerivedNext();
	virtual bool __fastcall Next();
	virtual void __fastcall DerivedClose();
	
protected:
	virtual int __fastcall GetColumnCount();
	virtual Data::Dbxcommon::TDBXByteReader* __fastcall GetByteReader();
	
private:
	TDBXTable* FTable;
	bool FBeforeFirst;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXTableRow : public Data::Dbxcommon::TDBXWritableValueList
{
	typedef Data::Dbxcommon::TDBXWritableValueList inherited;
	
public:
	__fastcall TDBXTableRow(Data::Dbxcommon::TDBXContext* const DbxContext);
	virtual Data::Dbxcommon::TDBXValueTypeArray __fastcall CopyColumns() = 0 ;
	
protected:
	virtual Data::Dbxcommon::TDBXValueTypeArray __fastcall GetColumns() = 0 ;
	virtual void __fastcall SetColumns(const Data::Dbxcommon::TDBXValueTypeArray Columns) = 0 ;
	virtual void __fastcall SetDBXTableName(const System::UnicodeString Name) = 0 ;
	virtual System::UnicodeString __fastcall GetDBXTableName() = 0 ;
	virtual TDBXTableRow* __fastcall GetOriginalRow() = 0 ;
	virtual int __fastcall ColumnIndex(const System::UnicodeString ColumnName);
	
public:
	__property Data::Dbxcommon::TDBXValueTypeArray Columns = {read=GetColumns, write=SetColumns};
	__property System::UnicodeString DBXTableName = {read=GetDBXTableName, write=SetDBXTableName};
	__property TDBXTableRow* OriginalRow = {read=GetOriginalRow};
public:
	/* TDBXValueList.Destroy */ inline __fastcall virtual ~TDBXTableRow() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TDBXTableState : unsigned char { tsInactive, tsBrowsing, tsInserting, tsEditing };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXTable : public TDBXTableRow
{
	typedef TDBXTableRow inherited;
	
public:
	__fastcall TDBXTable(Data::Dbxcommon::TDBXContext* const DbxContext);
	virtual bool __fastcall InBounds() = 0 ;
	virtual bool __fastcall Next() = 0 ;
	virtual bool __fastcall First() = 0 ;
	virtual Data::Dbxcommon::TDBXValueTypeArray __fastcall CopyColumns();
	virtual void __fastcall CopyFrom(TDBXTable* const Source)/* overload */;
	virtual void __fastcall CopyFrom(Data::Dbxcommon::TDBXReader* const Source)/* overload */;
	virtual TDBXTableState __fastcall GetState();
	virtual void __fastcall Insert();
	virtual bool __fastcall Edit();
	virtual void __fastcall Cancel();
	virtual void __fastcall Post();
	virtual void __fastcall Close();
	virtual void __fastcall Clear();
	virtual void __fastcall DeleteRow();
	virtual bool __fastcall FindStringKey(const int Ordinal, const System::UnicodeString Value);
	virtual void __fastcall AcceptChanges();
	virtual TDBXTable* __fastcall CreateTableView(const System::UnicodeString OrderByColumnName);
	
protected:
	virtual void __fastcall SetDBXTableName(const System::UnicodeString Name);
	virtual System::UnicodeString __fastcall GetDBXTableName();
	virtual TDBXTableRow* __fastcall GetOriginalRow();
	virtual void __fastcall SetColumns(const Data::Dbxcommon::TDBXValueTypeArray Columns);
	virtual bool __fastcall IsUpdateable();
	virtual System::TObject* __fastcall GetStorage();
	virtual System::TObject* __fastcall GetCommand();
	virtual TDBXTable* __fastcall GetDeletedRows();
	virtual TDBXTable* __fastcall GetInsertedRows();
	virtual TDBXTable* __fastcall GetUpdatedRows();
	virtual int __fastcall GetTableId();
	virtual int __fastcall GetTableCount();
	
public:
	__property TDBXTableState State = {read=GetState, nodefault};
	__property bool Updateable = {read=IsUpdateable, nodefault};
	__property System::TObject* Storage = {read=GetStorage};
	__property System::TObject* Command = {read=GetCommand};
	__property TDBXTable* DeletedRows = {read=GetDeletedRows};
	__property TDBXTable* InsertedRows = {read=GetInsertedRows};
	__property TDBXTable* UpdatedRows = {read=GetUpdatedRows};
	__property int TableId = {read=GetTableId, nodefault};
	__property int TableCount = {read=GetTableCount, nodefault};
public:
	/* TDBXValueList.Destroy */ inline __fastcall virtual ~TDBXTable() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDelegateTable : public TDBXTable
{
	typedef TDBXTable inherited;
	
public:
	__fastcall TDBXDelegateTable();
	__fastcall virtual ~TDBXDelegateTable();
	virtual TDBXTable* __fastcall ReplaceStorage(TDBXTable* const Table);
	virtual bool __fastcall InBounds();
	virtual bool __fastcall First();
	virtual bool __fastcall Next();
	virtual void __fastcall Insert();
	virtual bool __fastcall Edit();
	virtual void __fastcall Cancel();
	virtual void __fastcall Post();
	virtual void __fastcall CopyFrom(TDBXTable* const Source)/* overload */;
	virtual void __fastcall Close();
	virtual void __fastcall Clear();
	virtual void __fastcall DeleteRow();
	virtual bool __fastcall FindStringKey(const int Ordinal, const System::UnicodeString Value);
	virtual void __fastcall AcceptChanges();
	virtual TDBXTable* __fastcall CreateTableView(const System::UnicodeString OrderByColumnName);
	virtual int __fastcall GetOrdinal(const System::UnicodeString ColumnName)/* overload */;
	
protected:
	virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
	virtual void __fastcall SetTable(TDBXTable* const Table);
	virtual bool __fastcall IsUpdateable();
	virtual System::TObject* __fastcall GetStorage();
	virtual System::TObject* __fastcall GetCommand();
	virtual TDBXTable* __fastcall GetDeletedRows();
	virtual TDBXTable* __fastcall GetInsertedRows();
	virtual TDBXTable* __fastcall GetUpdatedRows();
	virtual Data::Dbxcommon::TDBXValueTypeArray __fastcall GetColumns();
	virtual void __fastcall SetColumns(const Data::Dbxcommon::TDBXValueTypeArray Columns);
	virtual System::UnicodeString __fastcall GetDBXTableName();
	virtual TDBXTableRow* __fastcall GetOriginalRow();
	TDBXTable* FTable;
	
public:
	__property TDBXTable* Table = {write=SetTable};
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  CopyFrom(Data::Dbxcommon::TDBXReader* const Source){ TDBXTable::CopyFrom(Source); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXStringTrimTable : public TDBXDelegateTable
{
	typedef TDBXDelegateTable inherited;
	
public:
	__fastcall TDBXStringTrimTable(TDBXTable* const Table, const Data::Dbxcommon::TDBXWritableValueArray TrimValues);
	static TDBXTable* __fastcall CreateTrimTableIfNeeded(TDBXTable* const Table);
	__fastcall virtual ~TDBXStringTrimTable();
	
protected:
	virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
	
private:
	static bool __fastcall HasCharTypes(const Data::Dbxcommon::TDBXValueTypeArray Columns);
	
public:
	Data::Dbxcommon::TDBXWritableValueArray FTrimValues;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXTrimStringValue : public Data::Dbxdelegate::TDBXDelegateWritableValue
{
	typedef Data::Dbxdelegate::TDBXDelegateWritableValue inherited;
	
public:
	__fastcall TDBXTrimStringValue(Data::Dbxcommon::TDBXWritableValue* const Value);
	virtual System::UnicodeString __fastcall GetWideString()/* overload */;
	
protected:
	virtual System::UnicodeString __fastcall GetAsString();
public:
	/* TDBXDelegateWritableValue.Destroy */ inline __fastcall virtual ~TDBXTrimStringValue() { }
	
	/* Hoisted overloads: */
	
public:
	inline System::UnicodeString __fastcall  GetWideString(System::UnicodeString defaultValue){ return Data::Dbxdelegate::TDBXDelegateWritableValue::GetWideString(defaultValue); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXReaderTable : public TDBXTable
{
	typedef TDBXTable inherited;
	
public:
	__fastcall TDBXReaderTable(Data::Dbxcommon::TDBXReader* const AReader);
	virtual bool __fastcall First();
	virtual bool __fastcall InBounds();
	virtual bool __fastcall Next();
	virtual int __fastcall GetOrdinal(const System::UnicodeString ColumnName)/* overload */;
	virtual void __fastcall Close();
	
protected:
	virtual Data::Dbxcommon::TDBXValueTypeArray __fastcall GetColumns();
	virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
	
private:
	Data::Dbxcommon::TDBXReader* FReader;
	int FNextCount;
	bool FLastNext;
public:
	/* TDBXValueList.Destroy */ inline __fastcall virtual ~TDBXReaderTable() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXRowTable : public TDBXTable
{
	typedef TDBXTable inherited;
	
public:
	__fastcall TDBXRowTable(Data::Dbxcommon::TDBXContext* const DbxContext, Data::Dbxcommon::TDBXRow* const Row);
	__fastcall virtual ~TDBXRowTable();
	
protected:
	virtual void __fastcall RowNavigated();
	virtual void __fastcall CreateValues()/* overload */;
	
private:
	static Data::Dbxcommon::TDBXWritableValueArray __fastcall CreateValues(Data::Dbxcommon::TDBXContext* const Context, const Data::Dbxcommon::TDBXValueTypeArray LocalColumns, Data::Dbxcommon::TDBXRow* const Row)/* overload */;
	
protected:
	Data::Dbxcommon::TDBXRow* FRow;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXCustomValueRow : public TDBXRowTable
{
	typedef TDBXRowTable inherited;
	
public:
	__fastcall TDBXCustomValueRow(Data::Dbxcommon::TDBXContext* const DbxContext, Data::Dbxcommon::TDBXRow* const Row);
	virtual bool __fastcall InBounds();
	virtual bool __fastcall Next();
	virtual bool __fastcall First();
	virtual int __fastcall GetOrdinal(const System::UnicodeString ColumnName)/* overload */;
	
protected:
	virtual TDBXTableRow* __fastcall GetOriginalRow();
	virtual Data::Dbxcommon::TDBXValueTypeArray __fastcall GetColumns();
	virtual void __fastcall SetColumns(const Data::Dbxcommon::TDBXValueTypeArray ValueTypes);
	virtual void __fastcall SetDBXTableName(const System::UnicodeString Name);
	virtual System::UnicodeString __fastcall GetDBXTableName();
	
private:
	Data::Dbxcommon::TDBXValueTypeArray FValueTypes;
public:
	/* TDBXRowTable.Destroy */ inline __fastcall virtual ~TDBXCustomValueRow() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSingleValueRow : public TDBXCustomValueRow
{
	typedef TDBXCustomValueRow inherited;
	
public:
	__fastcall TDBXSingleValueRow();
	
protected:
	virtual void __fastcall SetColumns(const Data::Dbxcommon::TDBXValueTypeArray ValueTypes);
public:
	/* TDBXRowTable.Destroy */ inline __fastcall virtual ~TDBXSingleValueRow() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxcommontable */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXCOMMONTABLE)
using namespace Data::Dbxcommontable;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxcommontableHPP
