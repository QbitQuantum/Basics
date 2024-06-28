// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXDataSets.pas' rev: 34.00 (iOS)

#ifndef Data_DbxdatasetsHPP
#define Data_DbxdatasetsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Data.DBCommon.hpp>
#include <Data.DBCommonTypes.hpp>
#include <Data.DBXCommon.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxdatasets
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXReaderDataSet;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXReaderDataSet : public Data::Db::TDataSet
{
	typedef Data::Db::TDataSet inherited;
	
	
public:
	class DELPHICLASS TBlobStream;
	class PASCALIMPLEMENTATION TBlobStream : public System::Classes::TMemoryStream
	{
		typedef System::Classes::TMemoryStream inherited;
		
	private:
		TDBXReaderDataSet* FDataSet;
		Data::Db::TBlobField* FField;
		int FFieldNo;
		bool FHasData;
		
	protected:
		void __fastcall ReadBlobSize();
		
	public:
		__fastcall TBlobStream(Data::Db::TBlobField* Field, Data::Db::TBlobStreamMode Mode);
		__fastcall virtual ~TBlobStream();
		void __fastcall ReadBlobData();
		virtual long __fastcall Read(System::TArray__1<System::Byte> Buffer, long Offset, long Count)/* overload */;
		virtual long __fastcall Read _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (void *Buffer, long Count)/* overload */;
	/* Hoisted overloads: */
		
	public:
		inline long __fastcall  Read(System::TArray__1<System::Byte> &Buffer, long Count){ return System::Classes::TStream::Read(Buffer, Count); }
		
	};
	
	
	class DELPHICLASS TFLDDesc;
	class PASCALIMPLEMENTATION TFLDDesc : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		System::Word FFldNum;
		System::UnicodeString FName;
		System::Word FFldType;
		System::Word FSubType;
		short FUnits1;
		short FUnits2;
		System::Word FOffset;
		unsigned long FLen;
		System::Word FNullOffset;
		Data::Dbcommontypes::FLDVchk FFLDVchk;
		Data::Dbcommontypes::FLDRights FFLDRights;
		System::WordBool FCalcField;
		
	public:
		__property System::Word iFldNum = {read=FFldNum, write=FFldNum, nodefault};
		__property System::UnicodeString szName = {read=FName, write=FName};
		__property System::Word iFldType = {read=FFldType, write=FFldType, nodefault};
		__property System::Word iSubType = {read=FSubType, write=FSubType, nodefault};
		__property short iUnits1 = {read=FUnits1, write=FUnits1, nodefault};
		__property short iUnits2 = {read=FUnits2, write=FUnits2, nodefault};
		__property System::Word iOffset = {read=FOffset, write=FOffset, nodefault};
		__property unsigned long iLen = {read=FLen, write=FLen};
		__property System::Word iNullOffset = {read=FNullOffset, write=FNullOffset, nodefault};
		__property Data::Dbcommontypes::FLDVchk efldvVchk = {read=FFLDVchk, write=FFLDVchk, nodefault};
		__property Data::Dbcommontypes::FLDRights efldrRights = {read=FFLDRights, write=FFLDRights, nodefault};
		__property System::WordBool bCalcField = {read=FCalcField, write=FCalcField, nodefault};
	public:
		/* TObject.Create */ inline __fastcall TFLDDesc() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TFLDDesc() { }
		
	};
	
	
	typedef System::DynamicArray<TFLDDesc*> TFieldDescList;
	
	
public:
	#define TDBXReaderDataSet_SOrderBy u" order by "
	
	static constexpr System::WideChar SParam = (System::WideChar)(0x3f);
	
	static constexpr System::Int8 DefaultMaxBlobSize = System::Int8(-1);
	
	static System::StaticArray<Data::Db::TFieldType, 39> DataTypeMap;
	static constexpr System::Int8 SUB_TYPE_MEMO = System::Int8(0x16);
	
	static System::StaticArray<Data::Db::TFieldType, 15> BlobTypeMap;
	
private:
	System::TArray__1<System::Byte> FFieldBuffer;
	bool FRefreshing;
	
private:
	System::TArray__1<System::Byte> FBlobBuffer;
	System::TArray__1<System::Byte> FCalcFieldsBuffer;
	bool FCheckRowsAffected;
	__int64 FCurrentBlobSize;
	System::UnicodeString FDesignerData;
	bool FProvidedDBXReader;
	bool FOwnsProvidedDBXReader;
	Data::Db::TIndexDefs* FIndexDefs;
	int FMaxBlobSize;
	unsigned long FMaxColSize;
	bool FGetMetadata;
	bool FNumericMapping;
	bool FPrepared;
	int FRecords;
	int FRowsAffected;
	System::UnicodeString FSortFieldNames;
	Data::Dbxcommon::TDBXReader* FDBXReader;
	bool __fastcall GetCalculatedField(Data::Db::TField* Field, void * Buffer);
	virtual System::UnicodeString __fastcall GetQueryFromType();
	int __fastcall GetRowsAffected();
	void __fastcall InitBuffers();
	void __fastcall LoadFieldDef(System::Word FieldID, TFLDDesc* &FldDesc)/* overload */;
	void __fastcall SetCurrentBlobSize(__int64 Value);
	void __fastcall SetPrepared(bool Value);
	
protected:
	virtual void __fastcall PSEndTransaction(bool Commit);
	virtual void __fastcall PSExecute();
	virtual int __fastcall PSExecuteStatement(const System::UnicodeString ASQL, Data::Db::TParams* AParams)/* overload */;
	virtual int __fastcall PSExecuteStatement(const System::UnicodeString ASQL, Data::Db::TParams* AParams, Data::Db::TDataSet* &ResultSet)/* overload */;
	virtual int __fastcall PSExecuteStatement _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (const System::UnicodeString ASQL, Data::Db::TParams* AParams, void * ResultSet)/* overload */;
	virtual void __fastcall PSGetAttributes(System::Classes::TList* List);
	virtual Data::Db::TIndexDef* __fastcall PSGetDefaultOrder();
	virtual System::UnicodeString __fastcall PSGetKeyFields();
	virtual System::UnicodeString __fastcall PSGetQuoteChar();
	virtual System::UnicodeString __fastcall PSGetTableName();
	virtual Data::Db::TIndexDefs* __fastcall PSGetIndexDefs(Data::Db::TIndexOptions IndexTypes);
	virtual Data::Db::TParams* __fastcall PSGetParams();
	virtual Data::Db::EUpdateError* __fastcall PSGetUpdateException(System::Sysutils::Exception* E, Data::Db::EUpdateError* Prev);
	virtual bool __fastcall PSInTransaction();
	virtual bool __fastcall PSIsSQLBased();
	virtual bool __fastcall PSIsSQLSupported();
	virtual void __fastcall PSReset();
	virtual void __fastcall PSSetCommandText(const System::UnicodeString ACommandText);
	virtual void __fastcall PSSetParams(Data::Db::TParams* AParams);
	virtual void __fastcall PSStartTransaction();
	virtual bool __fastcall PSUpdateRecord(Data::Db::TUpdateKind UpdateKind, Data::Db::TDataSet* Delta);
	virtual System::UnicodeString __fastcall PSGetCommandText();
	virtual Data::Db::TPSCommandType __fastcall PSGetCommandType();
	virtual void __fastcall InternalClose();
	virtual void __fastcall InternalHandleException();
	virtual void __fastcall InternalInitFieldDefs();
	virtual void __fastcall InternalOpen();
	virtual bool __fastcall IsCursorOpen();
	void __fastcall AddFieldDesc(TFieldDescList FieldDescs, int DescNo, int &FieldID, System::Classes::TBits* RequiredFields, Data::Db::TFieldDefs* FieldDefs);
	void __fastcall ClearIndexDefs();
	virtual void __fastcall CloseCursor();
	void __fastcall CloseStatement();
	void __fastcall FreeReader();
	void __fastcall FreeBuffers();
	void __fastcall FreeCommand();
	virtual bool __fastcall GetCanModify();
	void __fastcall GetObjectTypeNames(Data::Db::TFields* Fields);
	virtual Data::Db::TGetResult __fastcall GetRecord(NativeInt Buffer, Data::Db::TGetMode GetMode, bool DoCheck)/* overload */;
	virtual Data::Db::TGetResult __fastcall GetRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, Data::Db::TGetMode GetMode, bool DoCheck)/* overload */;
	System::UnicodeString __fastcall GetSortFieldNames();
	virtual void __fastcall InitRecord(NativeInt Buffer)/* overload */;
	virtual void __fastcall InitRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer)/* overload */;
	virtual void __fastcall InternalRefresh();
	virtual void __fastcall Loaded();
	bool __fastcall LocateRecord(const System::UnicodeString KeyFields, const System::Variant &KeyValues, Data::Db::TLocateOptions Options, bool SyncCursor);
	virtual void __fastcall OpenCursor(bool InfoQuery);
	void __fastcall PropertyChanged();
	virtual void __fastcall SetBufListSize(int Value);
	virtual void __fastcall SetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> Buffer)/* overload */;
	virtual void __fastcall SetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer)/* overload */;
	void __fastcall SetSortFieldNames(System::UnicodeString Value);
	virtual void __fastcall UpdateIndexDefs();
	__property System::TArray__1<System::Byte> BlobBuffer = {read=FBlobBuffer, write=FBlobBuffer};
	__property __int64 CurrentBlobSize = {read=FCurrentBlobSize, write=SetCurrentBlobSize};
	__property int RowsAffected = {read=GetRowsAffected, nodefault};
	void __fastcall SetMaxBlobSize(int MaxSize);
	__property int MaxBlobSize = {read=FMaxBlobSize, write=SetMaxBlobSize, default=0};
	virtual int __fastcall GetRecordCount();
	__property System::UnicodeString SortFieldNames = {read=GetSortFieldNames, write=SetSortFieldNames};
	
public:
	__fastcall virtual TDBXReaderDataSet(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall TDBXReaderDataSet(System::Classes::TComponent* AOwner, Data::Dbxcommon::TDBXReader* DBXReader, bool AOwnsInstance)/* overload */;
	__fastcall virtual ~TDBXReaderDataSet();
	virtual System::Classes::TStream* __fastcall CreateBlobStream(Data::Db::TField* Field, Data::Db::TBlobStreamMode Mode);
	virtual int __fastcall GetBlobFieldData(int FieldNo, System::TArray__1<System::Byte> &Buffer);
	virtual bool __fastcall GetFieldData(int FieldNo, System::TArray__1<System::Byte> &Buffer)/* overload */;
	virtual bool __fastcall GetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> &Buffer)/* overload */;
	virtual bool __fastcall GetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (int FieldNo, void * Buffer)/* overload */;
	virtual bool __fastcall GetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer)/* overload */;
	__property Data::Db::TIndexDefs* IndexDefs = {read=FIndexDefs, write=FIndexDefs};
	virtual bool __fastcall IsSequenced();
	virtual bool __fastcall Locate(const System::UnicodeString KeyFields, const System::Variant &KeyValues, Data::Db::TLocateOptions Options);
	virtual System::Variant __fastcall Lookup(const System::UnicodeString KeyFields, const System::Variant &KeyValues, const System::UnicodeString ResultFields);
	__property bool Prepared = {read=FPrepared, write=SetPrepared, default=0};
	__property System::UnicodeString DesignerData = {read=FDesignerData, write=FDesignerData};
	__property int RecordCount = {read=GetRecordCount, nodefault};
	__property bool GetMetadata = {read=FGetMetadata, write=FGetMetadata, default=1};
	__property bool NumericMapping = {read=FNumericMapping, write=FNumericMapping, default=0};
	__property ObjectView = {default=0};
	__property BeforeOpen;
	__property AfterOpen;
	__property BeforeClose;
	__property AfterClose;
	__property BeforeScroll;
	__property AfterScroll;
	__property BeforeRefresh;
	__property AfterRefresh;
	__property OnCalcFields;
	__property Active = {default=0};
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  SetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> Buffer, bool NativeFormat){ Data::Db::TDataSet::SetFieldData(Field, Buffer, NativeFormat); }
	inline void __fastcall  SetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer, bool NativeFormat){ Data::Db::TDataSet::SetFieldData(Field, Buffer, NativeFormat); }
	
public:
	inline bool __fastcall  GetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> &Buffer, bool NativeFormat){ return Data::Db::TDataSet::GetFieldData(Field, Buffer, NativeFormat); }
	inline bool __fastcall  GetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer, bool NativeFormat){ return Data::Db::TDataSet::GetFieldData(Field, Buffer, NativeFormat); }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxdatasets */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXDATASETS)
using namespace Data::Dbxdatasets;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxdatasetsHPP
