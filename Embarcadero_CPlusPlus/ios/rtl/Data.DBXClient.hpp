// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXClient.pas' rev: 34.00 (iOS)

#ifndef Data_DbxclientHPP
#define Data_DbxclientHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXTransport.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXMessageHandlerJSonClient.hpp>
#include <Data.DBXStream.hpp>
#include <Data.DBXStreamPlatform.hpp>
#include <Data.DBXPlatform.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Data.DBXJSONReflect.hpp>
#include <System.Generics.Collections.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxclient
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXClientDriverLoader;
class DELPHICLASS TDBXClientDriver;
class DELPHICLASS TDBXClientTransaction;
class DELPHICLASS TDBXClientConnection;
class DELPHICLASS TDBXClientCommand;
class DELPHICLASS TDBXJSonByteReader;
class DELPHICLASS TDBXClientParameterRow;
//-- type declarations -------------------------------------------------------
_DECLARE_METACLASS(System::TMetaClass, TDBXClientDriverLoaderClass);

class PASCALIMPLEMENTATION TDBXClientDriverLoader : public Data::Dbxcommon::TDBXDriverLoader
{
	typedef Data::Dbxcommon::TDBXDriverLoader inherited;
	
public:
	__fastcall virtual TDBXClientDriverLoader();
	virtual Data::Dbxcommon::TDBXDriver* __fastcall Load(const Data::Dbxcommon::TDBXDriverDef &DriverDef);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXClientDriverLoader() { }
	
};


class PASCALIMPLEMENTATION TDBXClientDriver : public Data::Dbxcommon::TDBXDriver
{
	typedef Data::Dbxcommon::TDBXDriver inherited;
	
private:
	Data::Dbxcommon::TDBXCommand* __fastcall CreateClientCommand(Data::Dbxcommon::TDBXContext* DbxContext, Data::Dbxcommon::TDBXConnection* Connection, Data::Dbxcommon::TDBXCommand* MorphicCommand);
	
protected:
	virtual void __fastcall Close();
	virtual Data::Dbxcommon::TDBXConnection* __fastcall CreateConnection(Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder);
	virtual Data::Dbxtransport::TDbxChannel* __fastcall CreateChannel();
	
public:
	__fastcall virtual TDBXClientDriver(const Data::Dbxcommon::TDBXDriverDef &DriverDef)/* overload */;
	__fastcall TDBXClientDriver(const Data::Dbxcommon::TDBXDriverDef &DriverDef, Data::Dbxcommon::TDBXProperties* DriverProps)/* overload */;
	virtual System::UnicodeString __fastcall GetDriverVersion();
public:
	/* TDBXDriver.Create */ inline __fastcall TDBXClientDriver()/* overload */ : Data::Dbxcommon::TDBXDriver() { }
	/* TDBXDriver.Destroy */ inline __fastcall virtual ~TDBXClientDriver() { }
	
};


class PASCALIMPLEMENTATION TDBXClientTransaction : public Data::Dbxcommon::TDBXTransaction
{
	typedef Data::Dbxcommon::TDBXTransaction inherited;
	
private:
	int FTransactionHandle;
	
protected:
	__fastcall TDBXClientTransaction(TDBXClientConnection* Connection, int IsolationLevel, int TransactionHandle);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXClientTransaction() { }
	
};


class PASCALIMPLEMENTATION TDBXClientConnection : public Data::Dbxcommon::TDBXConnection
{
	typedef Data::Dbxcommon::TDBXConnection inherited;
	
private:
	Data::Dbxtransport::TDbxChannel* FChannel;
	
private:
	TDBXClientDriver* FDriver;
	Data::Dbxmessagehandlerjsonclient::TDBXJSonClientOutputConnectionHandler* FDBXConHandler;
	Data::Dbxstream::TDBXJSonStreamReader* FDbxReader;
	Data::Dbxstream::TDBXJSonStreamWriter* FDbxWriter;
	int FConnectionHandle;
	System::UnicodeString FProductName;
	int FProtocolVersion;
	System::Classes::TStringList* FVendorProps;
	void __fastcall updateIsolationLevel(int IsolationLevel);
	
protected:
	virtual Data::Dbxcommon::TDBXTransaction* __fastcall CreateAndBeginTransaction(const int Isolation);
	virtual void __fastcall Commit(Data::Dbxcommon::TDBXTransaction* const InTransaction);
	virtual void __fastcall Rollback(Data::Dbxcommon::TDBXTransaction* const InTransaction);
	virtual void __fastcall SetTraceInfoEvent(const Data::Dbxcommon::TDBXTraceEvent TraceInfoEvent);
	virtual void __fastcall DerivedOpen();
	virtual void __fastcall DerivedGetCommandTypes(System::Classes::TStrings* const List);
	virtual void __fastcall DerivedGetCommands(const System::UnicodeString CommandType, System::Classes::TStrings* const List);
	virtual void __fastcall DerivedClose();
	virtual System::UnicodeString __fastcall GetProductName();
	
public:
	__fastcall TDBXClientConnection(Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder);
	__fastcall virtual ~TDBXClientConnection();
	virtual System::UnicodeString __fastcall GetVendorProperty(const System::UnicodeString Name);
};


class PASCALIMPLEMENTATION TDBXClientCommand : public Data::Dbxcommon::TDBXCommand
{
	typedef Data::Dbxcommon::TDBXCommand inherited;
	
private:
	Data::Dbxstream::TDBXJSonStreamReader* FDbxReader;
	Data::Dbxstream::TDBXJSonStreamWriter* FDbxWriter;
	int FConnectionHandle;
	int FCommandHandle;
	__int64 FRowsAffected;
	bool FUpdateable;
	TDBXClientConnection* FConnection;
	Data::Dbxstream::TDBXRowBuffer* FDbxReaderBuffer;
	Data::Dbxcommontable::TDBXActiveTableReaderList* FDBXActiveTableReaderList;
	Data::Dbxcommon::TDBXReader* __fastcall Execute();
	
private:
	Data::Dbxstream::TDBXRowBuffer* FDbxParameterBuffer;
	bool FParameterTypeChange;
	Data::Dbxstreamplatform::TDBXJSonRow* FParameterRow;
	
protected:
	__fastcall TDBXClientCommand(Data::Dbxcommon::TDBXContext* DBXContext, TDBXClientConnection* Connection, int ConnectionHandle, Data::Dbxstream::TDBXJSonStreamReader* DbxReader, Data::Dbxstream::TDBXJSonStreamWriter* DbxWriter);
	virtual void __fastcall SetRowSetSize(const __int64 RowSetSize);
	virtual void __fastcall SetMaxBlobSize(const __int64 MaxBlobSize);
	virtual __int64 __fastcall GetRowsAffected();
	virtual Data::Dbxcommon::TDBXRow* __fastcall CreateParameterRow();
	virtual Data::Dbxcommon::TDBXReader* __fastcall DerivedExecuteQuery();
	virtual void __fastcall DerivedExecuteUpdate();
	virtual void __fastcall DerivedPrepare();
	virtual void __fastcall DerivedOpen();
	virtual void __fastcall DerivedClose();
	virtual Data::Dbxcommon::TDBXReader* __fastcall DerivedGetNextReader();
	virtual void __fastcall DerivedClearParameters();
	virtual void __fastcall SetText(const System::UnicodeString Value);
	
public:
	__fastcall virtual ~TDBXClientCommand();
	Data::Dbxjsonreflect::TJSONMarshal* __fastcall GetJSONMarshaler();
	Data::Dbxjsonreflect::TJSONUnMarshal* __fastcall GetJSONUnMarshaler();
	__classmethod void __fastcall AddConverter(Data::Dbxjsonreflect::TConverterEvent* event);
	__classmethod void __fastcall AddReverter(Data::Dbxjsonreflect::TReverterEvent* event);
};


class PASCALIMPLEMENTATION TDBXJSonByteReader : public Data::Dbxcommon::TDBXReaderByteReader
{
	typedef Data::Dbxcommon::TDBXReaderByteReader inherited;
	
private:
	int FReaderHandle;
	Data::Dbxstream::TDBXRowBuffer* FDbxRowBuffer;
	Data::Dbxstreamplatform::TDBXJSonReader* FDbxClientReader;
	
public:
	__fastcall TDBXJSonByteReader(Data::Dbxcommon::TDBXContext* DBXContext, int ReaderHandle, Data::Dbxstreamplatform::TDBXJSonReader* ClientReader, Data::Dbxstream::TDBXJSonStreamReader* DbxReader, Data::Dbxstream::TDBXJSonStreamWriter* DbxWriter, Data::Dbxstream::TDBXRowBuffer* DbxRowBuffer);
	virtual void __fastcall GetAnsiString(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetWideString(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetUInt8(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt8(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetUInt16(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt16(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt32(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt64(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetDouble(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXJSonByteReader() { }
	
};


class PASCALIMPLEMENTATION TDBXClientParameterRow : public Data::Dbxstreamplatform::TDBXJSonRow
{
	typedef Data::Dbxstreamplatform::TDBXJSonRow inherited;
	
private:
	TDBXClientCommand* FDbxClientCommand;
	
protected:
	__fastcall TDBXClientParameterRow(Data::Dbxcommon::TDBXContext* DBXContext, int ReaderHandle, TDBXClientCommand* DbxClientCommand, Data::Dbxstream::TDBXJSonStreamReader* DbxStreamReader, Data::Dbxstream::TDBXJSonStreamWriter* DbxStreamWriter, Data::Dbxstream::TDBXRowBuffer* DbxRowBuffer);
	virtual void __fastcall SetValueType(Data::Dbxcommon::TDBXValueType* ValueType);
	virtual void __fastcall ValueNotSet(Data::Dbxcommon::TDBXWritableValue* const Value);
	
public:
	__fastcall virtual ~TDBXClientParameterRow();
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxclient */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXCLIENT)
using namespace Data::Dbxclient;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxclientHPP
