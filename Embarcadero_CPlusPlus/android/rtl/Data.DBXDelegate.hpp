// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXDelegate.pas' rev: 34.00 (Android)

#ifndef Data_DbxdelegateHPP
#define Data_DbxdelegateHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXPlatform.hpp>
#include <System.Classes.hpp>
#include <Data.FmtBcd.hpp>
#include <Data.SqlTimSt.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxdelegate
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXDelegateConnection;
class DELPHICLASS TDBXDelegateCommand;
class DELPHICLASS TDBXDelegateParameterList;
class DELPHICLASS TDBXDelegateParameter;
class DELPHICLASS TDBXDelegateWritableValue;
class DELPHICLASS TDBXDelegateReader;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDelegateConnection : public Data::Dbxcommon::TDBXConnection
{
	typedef Data::Dbxcommon::TDBXConnection inherited;
	
protected:
	Data::Dbxcommon::TDBXConnection* FConnection;
	
protected:
	virtual Data::Dbxcommon::TDBXTransaction* __fastcall CreateAndBeginTransaction(const int Isolation);
	virtual void __fastcall Commit(Data::Dbxcommon::TDBXTransaction* const Transaction);
	virtual void __fastcall Rollback(Data::Dbxcommon::TDBXTransaction* const Transaction);
	virtual Data::Dbxcommon::TDBXDatabaseMetaData* __fastcall GetDatabaseMetaData();
	virtual Data::Dbxcommon::TDBXProperties* __fastcall GetConnectionProperties();
	virtual void __fastcall SetConnectionProperties(Data::Dbxcommon::TDBXProperties* const Value);
	virtual Data::Dbxcommon::TDBXTraceEvent __fastcall GetTraceInfoEvent();
	virtual void __fastcall SetTraceInfoEvent(const Data::Dbxcommon::TDBXTraceEvent TraceInfoEvent);
	virtual int __fastcall GetTraceFlags();
	virtual void __fastcall SetTraceFlags(const int TraceFlags);
	virtual Data::Dbxcommon::TDBXErrorEvent __fastcall GetErrorEvent();
	virtual void __fastcall SetErrorEvent(const Data::Dbxcommon::TDBXErrorEvent ErrorEvent);
	virtual Data::Dbxcommon::TDBXFormatter* __fastcall GetDBXFormatter();
	virtual void __fastcall SetDBXFormatter(Data::Dbxcommon::TDBXFormatter* const DBXFormatter);
	virtual bool __fastcall GetIsOpen();
	virtual void __fastcall Open();
	virtual Data::Dbxcommon::TDBXCommand* __fastcall DerivedCreateCommand()/* overload */;
	virtual void __fastcall DerivedOpen();
	virtual void __fastcall DerivedGetCommandTypes(System::Classes::TStrings* const List);
	virtual void __fastcall DerivedGetCommands(const System::UnicodeString CommandType, System::Classes::TStrings* const List);
	virtual void __fastcall DerivedClose();
	virtual Data::Dbxcommon::TDBXCommand* __fastcall CreateMorphCommand(Data::Dbxcommon::TDBXCommand* MorphicCommand);
	virtual System::UnicodeString __fastcall GetProductVersion();
	virtual System::UnicodeString __fastcall GetProductName();
	virtual System::UnicodeString __fastcall GetConnectionProperty(const System::UnicodeString Name);
	
public:
	__fastcall TDBXDelegateConnection(Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder, Data::Dbxcommon::TDBXConnection* Connection);
	__fastcall virtual ~TDBXDelegateConnection();
	virtual void __fastcall Close();
	virtual Data::Dbxcommon::TDBXTransaction* __fastcall BeginTransaction(int Isolation)/* overload */;
	virtual Data::Dbxcommon::TDBXTransaction* __fastcall BeginTransaction()/* overload */;
	virtual void __fastcall CommitFreeAndNil(Data::Dbxcommon::TDBXTransaction* &Transaction);
	virtual void __fastcall RollbackFreeAndNil(Data::Dbxcommon::TDBXTransaction* &Transaction);
	virtual void __fastcall RollbackIncompleteFreeAndNil(Data::Dbxcommon::TDBXTransaction* &Transaction);
	virtual Data::Dbxcommon::TDBXCommand* __fastcall CreateCommand()/* overload */;
	virtual System::UnicodeString __fastcall GetVendorProperty(const System::UnicodeString Name);
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDelegateCommand : public Data::Dbxcommon::TDBXCommand
{
	typedef Data::Dbxcommon::TDBXCommand inherited;
	
protected:
	Data::Dbxcommon::TDBXCommand* FCommand;
	
protected:
	virtual void __fastcall SetCommandType(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetCommandType();
	virtual System::UnicodeString __fastcall GetText();
	virtual void __fastcall SetText(const System::UnicodeString Value);
	virtual void __fastcall SetRowSetSize(const __int64 Value);
	virtual void __fastcall SetMaxBlobSize(const __int64 MaxBlobSize);
	virtual __int64 __fastcall GetRowsAffected();
	virtual void __fastcall SetCommandTimeout(const int Timeout);
	virtual int __fastcall GetCommandTimeout();
	virtual Data::Dbxcommon::TDBXErrorEvent __fastcall GetErrorEvent();
	virtual Data::Dbxcommon::TDBXRow* __fastcall CreateParameterRow();
	virtual void __fastcall CreateParameters(Data::Dbxcommon::TDBXCommand* Command);
	virtual Data::Dbxcommon::TDBXParameterList* __fastcall GetParameters();
	virtual void __fastcall Open();
	virtual Data::Dbxcommon::TDBXReader* __fastcall DerivedGetNextReader();
	virtual void __fastcall DerivedOpen();
	virtual void __fastcall DerivedClose();
	virtual void __fastcall DerivedPrepare();
	virtual Data::Dbxcommon::TDBXReader* __fastcall DerivedExecuteQuery();
	virtual void __fastcall DerivedExecuteUpdate();
	virtual void __fastcall DerivedClearParameters();
	
public:
	__fastcall TDBXDelegateCommand(Data::Dbxcommon::TDBXContext* DBXContext, Data::Dbxcommon::TDBXCommand* Command);
	__fastcall virtual ~TDBXDelegateCommand();
	virtual void __fastcall Prepare();
	virtual Data::Dbxcommon::TDBXReader* __fastcall ExecuteQuery();
	virtual void __fastcall ExecuteUpdate();
	virtual Data::Dbxcommon::TDBXReader* __fastcall GetNextReader();
	virtual Data::Dbxcommon::TDBXParameter* __fastcall CreateParameter();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDelegateParameterList : public Data::Dbxcommon::TDBXParameterList
{
	typedef Data::Dbxcommon::TDBXParameterList inherited;
	
protected:
	Data::Dbxcommon::TDBXParameterList* FParameterList;
	
protected:
	virtual Data::Dbxcommon::TDBXParameter* __fastcall GetParameterByOrdinal(const int Ordinal);
	virtual int __fastcall GetCount();
	__fastcall TDBXDelegateParameterList(Data::Dbxcommon::TDBXContext* DBXContext, Data::Dbxcommon::TDBXCommand* Command, Data::Dbxcommon::TDBXParameterList* Parameters);
	
public:
	__fastcall virtual ~TDBXDelegateParameterList();
	virtual void __fastcall SetCount(const int Count);
	virtual void __fastcall AddParameter(Data::Dbxcommon::TDBXParameter* Parameter);
	virtual void __fastcall SetParameter(const int Ordinal, Data::Dbxcommon::TDBXParameter* const Parameter);
	virtual void __fastcall InsertParameter(int Ordinal, Data::Dbxcommon::TDBXParameter* Parameter);
	virtual void __fastcall RemoveParameter(int Ordinal)/* overload */;
	virtual void __fastcall RemoveParameter(Data::Dbxcommon::TDBXParameter* Parameter)/* overload */;
	virtual void __fastcall ClearParameters()/* overload */;
	virtual void __fastcall RemoveParameters();
	virtual int __fastcall GetOrdinal(const System::UnicodeString Name);
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TDBXDelegateParameter : public Data::Dbxcommon::TDBXParameter
{
	typedef Data::Dbxcommon::TDBXParameter inherited;
	
protected:
	Data::Dbxcommon::TDBXParameter* FParameter;
	
protected:
	virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetValue();
	virtual void __fastcall SetParameter();
	virtual void __fastcall SetDbxRow(Data::Dbxcommon::TDBXRow* const DbxRow);
	virtual void __fastcall SetParameterDirection(const int ParameterDirection);
	virtual void __fastcall SetName(const System::UnicodeString Name);
	virtual void __fastcall SetDisplayName(const System::UnicodeString Caption);
	virtual void __fastcall SetOrdinal(const int Ordinal);
	virtual void __fastcall SetDataType(const int DataType);
	virtual void __fastcall SetSubType(const int SubType);
	virtual void __fastcall SetPrecision(const __int64 Precision);
	virtual void __fastcall SetScale(const int Scale);
	virtual void __fastcall SetChildPosition(const int ChildPosition);
	virtual void __fastcall SetFlags(const int Flags);
	virtual void __fastcall SetNullable(const bool NullableValue);
	virtual void __fastcall SetSize(const __int64 Size);
	virtual void __fastcall SetHidden(const System::LongBool Hidden);
	virtual void __fastcall SetValueParameter(const bool ValueParameter);
	virtual void __fastcall SetLiteral(const bool Literal);
	virtual int __fastcall GetParameterDirection();
	virtual System::UnicodeString __fastcall GetName();
	virtual System::UnicodeString __fastcall GetDisplayName();
	virtual int __fastcall GetOrdinal();
	virtual int __fastcall GetDataType();
	virtual int __fastcall GetSubType();
	virtual __int64 __fastcall GetPrecision();
	virtual int __fastcall GetScale();
	virtual int __fastcall GetChildPosition();
	virtual int __fastcall GetFlags();
	virtual __int64 __fastcall GetSize();
	virtual System::LongBool __fastcall GetHidden();
	virtual bool __fastcall GetValueParameter();
	virtual bool __fastcall GetLiteral();
	
public:
	__fastcall TDBXDelegateParameter(Data::Dbxcommon::TDBXContext* DBXContext, Data::Dbxcommon::TDBXParameter* Parameter);
	__fastcall virtual ~TDBXDelegateParameter();
	virtual void __fastcall Assign(Data::Dbxcommon::TDBXParameter* Source);
	virtual System::TObject* __fastcall Clone();
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDelegateWritableValue : public Data::Dbxcommon::TDBXWritableValue
{
	typedef Data::Dbxcommon::TDBXWritableValue inherited;
	
protected:
	Data::Dbxcommon::TDBXValue* FValue;
	Data::Dbxcommon::TDBXWritableValue* FWritableValue;
	
protected:
	__fastcall TDBXDelegateWritableValue(Data::Dbxcommon::TDBXValueType* ValueType, Data::Dbxcommon::TDBXWritableValue* Value)/* overload */;
	virtual Data::Dbxcommon::TDBXValue* __fastcall GetNonDelegate();
	virtual bool __fastcall GetAsBoolean();
	virtual System::Byte __fastcall GetAsUInt8();
	virtual System::Int8 __fastcall GetAsInt8();
	virtual System::Word __fastcall GetAsUInt16();
	virtual short __fastcall GetAsInt16();
	virtual int __fastcall GetAsInt32();
	virtual __int64 __fastcall GetAsInt64();
	virtual System::UnicodeString __fastcall GetAsString();
	virtual float __fastcall GetAsSingle();
	virtual double __fastcall GetAsDouble();
	virtual Data::Fmtbcd::TBcd __fastcall GetAsBcd();
	virtual Data::Dbxcommon::TDBXDate __fastcall GetAsDate();
	virtual Data::Dbxcommon::TDBXTime __fastcall GetAsTime();
	virtual Data::Sqltimst::TSQLTimeStamp __fastcall GetAsTimeStamp();
	virtual void __fastcall SetPendingValue();
	virtual void __fastcall SetAsBoolean(const bool Value);
	virtual void __fastcall SetAsUInt8(const System::Byte Value);
	virtual void __fastcall SetAsInt8(const System::Int8 Value);
	virtual void __fastcall SetAsUInt16(const System::Word Value);
	virtual void __fastcall SetAsInt16(const short Value);
	virtual void __fastcall SetAsInt32(const int Value);
	virtual void __fastcall SetAsInt64(const __int64 Value);
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsSingle(const float Value);
	virtual void __fastcall SetAsDouble(const double Value);
	virtual void __fastcall SetAsBcd(const Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetAsDate(const Data::Dbxcommon::TDBXDate Value);
	virtual void __fastcall SetAsTime(const Data::Dbxcommon::TDBXTime Value);
	virtual void __fastcall SetAsTimeStamp(const Data::Sqltimst::TSQLTimeStamp &Value);
	
public:
	virtual bool __fastcall IsNull();
	virtual __int64 __fastcall GetValueSize();
	virtual System::AnsiString __fastcall GetAnsiString();
	virtual Data::Dbxcommon::TDBXDate __fastcall GetDate();
	virtual bool __fastcall GetBoolean()/* overload */;
	virtual Data::Dbxcommon::TDBXTime __fastcall GetTime();
	virtual System::UnicodeString __fastcall GetWideString()/* overload */;
	virtual System::UnicodeString __fastcall GetString()/* overload */;
	virtual System::Byte __fastcall GetUInt8()/* overload */;
	virtual System::Int8 __fastcall GetInt8()/* overload */;
	virtual System::Word __fastcall GetUInt16()/* overload */;
	virtual short __fastcall GetInt16()/* overload */;
	virtual int __fastcall GetInt32()/* overload */;
	virtual __int64 __fastcall GetInt64()/* overload */;
	virtual float __fastcall GetSingle();
	virtual double __fastcall GetDouble();
	virtual __int64 __fastcall GetBytes(__int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length)/* overload */;
	virtual Data::Sqltimst::TSQLTimeStamp __fastcall GetTimeStamp();
	virtual Data::Sqltimst::TSQLTimeStampOffset __fastcall GetTimeStampOffset();
	virtual Data::Fmtbcd::TBcd __fastcall GetBcd();
	virtual Data::Dbxcommon::TDBXReader* __fastcall GetDBXReader(bool AInstanceOwner)/* overload */;
	virtual Data::Dbxcommon::TDBXConnection* __fastcall GetDBXConnection();
	virtual System::Classes::TStream* __fastcall GetStream(bool AInstanceOwner)/* overload */;
	virtual System::UnicodeString __fastcall GetWideString(System::UnicodeString defaultValue)/* overload */;
	virtual bool __fastcall GetBoolean(bool defaultValue)/* overload */;
	virtual System::Byte __fastcall GetUInt8(System::Byte defaultValue)/* overload */;
	virtual System::Int8 __fastcall GetInt8(System::Int8 defaultValue)/* overload */;
	virtual System::Word __fastcall GetUInt16(System::Word defaultValue)/* overload */;
	virtual short __fastcall GetInt16(short defaultValue)/* overload */;
	virtual int __fastcall GetInt32(int defaultValue)/* overload */;
	virtual __int64 __fastcall GetInt64(__int64 defaultValue)/* overload */;
	virtual bool __fastcall EqualsValue(Data::Dbxcommon::TDBXValue* Other);
	virtual void __fastcall SetNull();
	virtual void __fastcall SetTimeStamp(const Data::Sqltimst::TSQLTimeStamp &Value);
	virtual void __fastcall SetTimeStampOffset(const Data::Sqltimst::TSQLTimeStampOffset &Value);
	virtual void __fastcall SetBcd(const Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetAnsiString(const System::AnsiString Value);
	virtual void __fastcall SetBoolean(const bool Value);
	virtual void __fastcall SetDate(const Data::Dbxcommon::TDBXDate Value);
	virtual void __fastcall SetTime(const Data::Dbxcommon::TDBXTime Value);
	virtual void __fastcall SetWideString(const System::UnicodeString Value);
	virtual void __fastcall SetString(const System::UnicodeString Value);
	virtual void __fastcall SetUInt8(const System::Byte Value);
	virtual void __fastcall SetInt8(const System::Int8 Value);
	virtual void __fastcall SetUInt16(const System::Word Value);
	virtual void __fastcall SetInt16(const short Value);
	virtual void __fastcall SetInt32(const int Value);
	virtual void __fastcall SetInt64(const __int64 Value);
	virtual void __fastcall SetSingle(const float Value);
	virtual void __fastcall SetDouble(const double Value);
	virtual void __fastcall SetStaticBytes(__int64 Offset, const System::Byte *Buffer, const int Buffer_High, __int64 BufferOffset, __int64 Length);
	virtual void __fastcall SetDynamicBytes(__int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length);
	virtual void __fastcall SetDBXReader(Data::Dbxcommon::TDBXReader* const Value, const bool AInstanceOwner)/* overload */;
	virtual void __fastcall SetStream(System::Classes::TStream* const Stream, const bool AInstanceOwner);
	virtual void __fastcall SetDBXConnection(Data::Dbxcommon::TDBXConnection* const Value);
	virtual void __fastcall SetValue(Data::Dbxcommon::TDBXValue* const Value);
	__fastcall virtual ~TDBXDelegateWritableValue();
	/* Hoisted overloads: */
	
public:
	inline Data::Dbxcommon::TDBXReader* __fastcall  GetDBXReader(){ return Data::Dbxcommon::TDBXValue::GetDBXReader(); }
	inline System::Classes::TStream* __fastcall  GetStream(){ return Data::Dbxcommon::TDBXValue::GetStream(); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDelegateReader : public Data::Dbxcommon::TDBXReader
{
	typedef Data::Dbxcommon::TDBXReader inherited;
	
private:
	Data::Dbxcommon::TDBXReader* FReader;
	
protected:
	virtual bool __fastcall DerivedNext();
	virtual void __fastcall DerivedClose();
	virtual Data::Dbxcommon::TDBXByteReader* __fastcall GetByteReader();
	virtual int __fastcall GetReaderHandle();
	virtual bool __fastcall IsUpdateable();
	virtual int __fastcall GetRowHandle();
	virtual Data::Dbxcommon::TDBXValue* __fastcall GetValue(const int Ordinal);
	virtual Data::Dbxcommon::TDBXValue* __fastcall GetValueByName(const System::UnicodeString Name);
	virtual Data::Dbxcommon::TDBXValueType* __fastcall GetValueType(const int Ordinal);
	virtual int __fastcall GetColumnCount();
	
public:
	__fastcall TDBXDelegateReader(Data::Dbxcommon::TDBXContext* DBXContext, Data::Dbxcommon::TDBXReader* Reader);
	__fastcall virtual ~TDBXDelegateReader();
	virtual bool __fastcall Next();
	virtual bool __fastcall Reset();
	virtual System::UnicodeString __fastcall GetObjectTypeName(int Ordinal);
	virtual int __fastcall GetOrdinal(const System::UnicodeString Name)/* overload */;
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxdelegate */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXDELEGATE)
using namespace Data::Dbxdelegate;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxdelegateHPP
