// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMessageHandlerCommon.pas' rev: 34.00 (Android)

#ifndef Data_DbxmessagehandlercommonHPP
#define Data_DbxmessagehandlercommonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXPlatform.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmessagehandlercommon
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXCommandHandler;
class DELPHICLASS TDBXConnectionHandler;
class DELPHICLASS TDBXDisconnectHandler;
class DELPHICLASS TDBXMessage;
class DELPHICLASS TDBXErrorMessage;
class DELPHICLASS TDBXDisconnectMessage;
class DELPHICLASS TDBXConnectMessage;
class DELPHICLASS TDBXCommandMessage;
class DELPHICLASS TDBXExecuteMessage;
class DELPHICLASS TDBXCommandCloseMessage;
class DELPHICLASS TDBXMoreBlobMessage;
class DELPHICLASS TDBXNextMessage;
class DELPHICLASS TDBXNextResultMessage;
class DELPHICLASS TDBXOpenMessage;
class DELPHICLASS TDBXPrepareMessage;
class DELPHICLASS TDBXProtocolHandler;
class DELPHICLASS TDBXReaderCloseMessage;
class DELPHICLASS TDBXTxBeginMessage;
class DELPHICLASS TDBXTxEndMessage;
class DELPHICLASS TDBXVendorPropertyMessage;
//-- type declarations -------------------------------------------------------
typedef System::DynamicArray<TDBXCommandHandler*> TDBXCommandHandlerArray;

typedef System::DynamicArray<TDBXConnectionHandler*> TDBXConnectionHandlerArray;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXCommandHandler : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall TDBXCommandHandler(Data::Dbxcommon::TDBXContext* const ADbxContext);
	__fastcall virtual ~TDBXCommandHandler();
	virtual void __fastcall DbxExecute(TDBXExecuteMessage* const Message) = 0 ;
	virtual void __fastcall DbxPrepare(TDBXPrepareMessage* const Message) = 0 ;
	virtual void __fastcall DbxNextResult(TDBXNextResultMessage* const Message) = 0 ;
	virtual void __fastcall DbxNext(TDBXNextMessage* const Message) = 0 ;
	virtual void __fastcall DbxMoreBlob(TDBXMoreBlobMessage* const Message) = 0 ;
	virtual void __fastcall DbxCommandClose(TDBXCommandCloseMessage* const Message) = 0 ;
	virtual void __fastcall DbxReaderClose(TDBXReaderCloseMessage* const Message) = 0 ;
	virtual void __fastcall DbxErrorMessage(TDBXErrorMessage* const Message) = 0 ;
	virtual Data::Dbxcommontable::TDBXStreamerRow* __fastcall CreateDbxRow();
	virtual bool __fastcall ClearResources();
	
protected:
	Data::Dbxcommontable::TDBXActiveTableReaderList* __fastcall GetActiveStreamerRowList();
	virtual int __fastcall GetCommandHandle();
	virtual void __fastcall SetCommandHandle(const int Handle);
	
private:
	int FCommandHandle;
	Data::Dbxcommon::TDBXContext* FDbxContext;
	Data::Dbxcommontable::TDBXActiveTableReaderList* FActiveStreamerRowList;
	TDBXCommandHandler* FNextOwnedHandler;
	
public:
	__property TDBXCommandHandler* NextOwnedHandler = {write=FNextOwnedHandler};
	__property Data::Dbxcommontable::TDBXActiveTableReaderList* ActiveStreamerRowList = {read=GetActiveStreamerRowList};
	__property int CommandHandle = {read=GetCommandHandle, write=SetCommandHandle, nodefault};
	__property Data::Dbxcommon::TDBXContext* DBXContext = {read=FDbxContext};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXConnectionHandler : public TDBXCommandHandler
{
	typedef TDBXCommandHandler inherited;
	
public:
	__fastcall TDBXConnectionHandler(Data::Dbxcommon::TDBXContext* const ADbxContext);
	virtual void __fastcall DbxConnect(TDBXConnectMessage* const Message) = 0 ;
	virtual void __fastcall DbxDisconnect(TDBXDisconnectMessage* const Message) = 0 ;
	virtual void __fastcall DbxTxBegin(TDBXTxBeginMessage* const Message) = 0 ;
	virtual void __fastcall DbxTxEnd(TDBXTxEndMessage* const Message) = 0 ;
	virtual void __fastcall DbxVendorProperty(TDBXVendorPropertyMessage* const Message) = 0 ;
	virtual void __fastcall DbxOpen(TDBXOpenMessage* const Message) = 0 ;
	virtual TDBXCommandHandler* __fastcall AcquireCommandHandler(TDBXCommandMessage* const Message) = 0 ;
	virtual bool __fastcall DbxBeforeRequest() = 0 ;
	
protected:
	virtual System::UnicodeString __fastcall GetProductName() = 0 ;
	virtual int __fastcall GetCommandHandle();
	virtual void __fastcall SetCommandHandle(const int Handle);
	
private:
	Data::Dbxcommon::TDBXError* __fastcall InvalidOperationError();
	
public:
	__property System::UnicodeString ProductName = {read=GetProductName};
public:
	/* TDBXCommandHandler.Destroy */ inline __fastcall virtual ~TDBXConnectionHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDisconnectHandler : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual void __fastcall Disconnect(TDBXConnectionHandler* const Handler) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TDBXDisconnectHandler() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDisconnectHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXMessage : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	/* TObject.Create */ inline __fastcall TDBXMessage() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXErrorMessage : public TDBXMessage
{
	typedef TDBXMessage inherited;
	
public:
	virtual void __fastcall HandleMessage(TDBXCommandHandler* const Handler);
	
protected:
	void __fastcall SetError(System::Sysutils::Exception* const Ex);
	
private:
	System::UnicodeString __fastcall GetNestedMessage(const System::UnicodeString Message, System::Sysutils::Exception* const Ex, const int Level);
	void __fastcall InitDBXErrorMessage(TDBXErrorMessage* const Message);
	System::Sysutils::Exception* FEx;
	int FErrorCode;
	System::UnicodeString FErrorMessage;
	System::UnicodeString FErrorClassName;
	
public:
	__property System::Sysutils::Exception* Error = {read=FEx, write=SetError};
	__property int ErrorCode = {read=FErrorCode, write=FErrorCode, nodefault};
	__property System::UnicodeString ErrorClassName = {read=FErrorClassName, write=FErrorClassName};
	__property System::UnicodeString ErrorMessage = {read=FErrorMessage, write=FErrorMessage};
public:
	/* TObject.Create */ inline __fastcall TDBXErrorMessage() : TDBXMessage() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXErrorMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDisconnectMessage : public TDBXMessage
{
	typedef TDBXMessage inherited;
	
public:
	void __fastcall HandleMessage(TDBXConnectionHandler* const Handler);
public:
	/* TObject.Create */ inline __fastcall TDBXDisconnectMessage() : TDBXMessage() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDisconnectMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXConnectMessage : public TDBXMessage
{
	typedef TDBXMessage inherited;
	
public:
	void __fastcall HandleMessage(TDBXConnectionHandler* const Handler);
	
private:
	Data::Dbxcommon::TDBXProperties* FConnectProperties;
	int FConnectionHandle;
	System::UnicodeString FProductName;
	bool FSuccessfulConnect;
	
public:
	__property System::UnicodeString ProductName = {read=FProductName, write=FProductName};
	__property Data::Dbxcommon::TDBXProperties* ConnectProperties = {read=FConnectProperties, write=FConnectProperties};
	__property int ConnectionHandle = {read=FConnectionHandle, write=FConnectionHandle, nodefault};
	__property bool SuccessfulConnect = {read=FSuccessfulConnect, write=FSuccessfulConnect, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDBXConnectMessage() : TDBXMessage() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXConnectMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXCommandMessage : public TDBXMessage
{
	typedef TDBXMessage inherited;
	
public:
	__fastcall virtual ~TDBXCommandMessage();
	
protected:
	void __fastcall SetExplicitParameters(Data::Dbxcommon::TDBXParameterList* const ExplicitParameters);
	
private:
	int FCommandHandle;
	bool FUpdatable;
	System::UnicodeString FCommandType;
	System::UnicodeString FCommand;
	bool FParameterTypeChanged;
	Data::Dbxcommon::TDBXParameterList* FParameters;
	Data::Dbxcommon::TDBXParameterList* FExplicitParameters;
	Data::Dbxplatform::TDBXInt32s FParameterDbxDataTypes;
	bool FServerSideCommand;
	
public:
	__property System::UnicodeString Command = {read=FCommand, write=FCommand};
	__property int CommandHandle = {read=FCommandHandle, write=FCommandHandle, nodefault};
	__property System::UnicodeString CommandType = {read=FCommandType, write=FCommandType};
	__property bool Updatable = {read=FUpdatable, write=FUpdatable, nodefault};
	__property bool ParameterTypeChanged = {read=FParameterTypeChanged, write=FParameterTypeChanged, nodefault};
	__property Data::Dbxcommon::TDBXParameterList* Parameters = {read=FParameters, write=FParameters};
	__property Data::Dbxcommon::TDBXParameterList* ExplicitParameters = {read=FExplicitParameters, write=SetExplicitParameters};
	__property Data::Dbxplatform::TDBXInt32s ParameterDbxDataTypes = {read=FParameterDbxDataTypes, write=FParameterDbxDataTypes};
	__property bool ServerSideCommand = {read=FServerSideCommand, write=FServerSideCommand, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDBXCommandMessage() : TDBXMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TDBXExecuteMessage : public TDBXCommandMessage
{
	typedef TDBXCommandMessage inherited;
	
public:
	__fastcall virtual ~TDBXExecuteMessage();
	void __fastcall HandleMessage(TDBXCommandHandler* const Handler)/* overload */;
	void __fastcall HandleMessage(TDBXConnectionHandler* const Handler)/* overload */;
	void __fastcall Reset();
	void __fastcall AddTableReader(Data::Dbxcommon::TDBXReader* const Table);
	Data::Dbxcommon::TDBXReader* __fastcall GetTableReader(const int Ordinal);
	void __fastcall FreeTableReaders();
	
protected:
	virtual void __fastcall SetConnectionHandler(System::TObject* const ConnectionHandler);
	virtual System::TObject* __fastcall GetConnectionHandler();
	
private:
	bool FPrepared;
	int FTableCount;
	Data::Dbxcommon::TDBXReaderArray FTables;
	bool FHasParameters;
	bool FHasOutOrReturnParameters;
	bool FHasDBXTableReaderOutOrReturnParameter;
	Data::Dbxcommontable::TDBXStreamerRow* FRow;
	Data::Dbxcommon::TDBXReader* FReturnReader;
	Data::Dbxcommontable::TDBXActiveTableReaderList* FActiveStreamerRowList;
	int FIsolationLevel;
	__int64 FRowsAffected;
	System::TObject* FConnectionHandler;
	
public:
	__property __int64 RowsAffected = {read=FRowsAffected, write=FRowsAffected};
	__property int IsolationLevel = {read=FIsolationLevel, write=FIsolationLevel, nodefault};
	__property int TableReaderCount = {read=FTableCount, nodefault};
	__property bool HasParameters = {read=FHasParameters, write=FHasParameters, nodefault};
	__property bool HasDBXTableReaderOutOrReturnParameter = {read=FHasDBXTableReaderOutOrReturnParameter, write=FHasDBXTableReaderOutOrReturnParameter, nodefault};
	__property bool HasOutOrReturnParameters = {read=FHasOutOrReturnParameters, write=FHasOutOrReturnParameters, nodefault};
	__property Data::Dbxcommontable::TDBXStreamerRow* Row = {read=FRow, write=FRow};
	__property Data::Dbxcommon::TDBXReader* ReturnReader = {read=FReturnReader, write=FReturnReader};
	__property Data::Dbxcommontable::TDBXActiveTableReaderList* ActiveStreamerRowList = {read=FActiveStreamerRowList, write=FActiveStreamerRowList};
	__property bool Prepared = {read=FPrepared, write=FPrepared, nodefault};
	__property System::TObject* ConnectionHandler = {read=GetConnectionHandler, write=SetConnectionHandler};
public:
	/* TObject.Create */ inline __fastcall TDBXExecuteMessage() : TDBXCommandMessage() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXCommandCloseMessage : public TDBXMessage
{
	typedef TDBXMessage inherited;
	
public:
	void __fastcall HandleMessage(TDBXCommandHandler* const Handler);
	
private:
	int FCommandHandle;
	
public:
	__property int CommandHandle = {read=FCommandHandle, write=FCommandHandle, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDBXCommandCloseMessage() : TDBXMessage() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXCommandCloseMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TDBXMoreBlobMessage : public TDBXMessage
{
	typedef TDBXMessage inherited;
	
public:
	void __fastcall HandleMessage(TDBXConnectionHandler* const Handler)/* overload */;
	void __fastcall HandleMessage(TDBXCommandHandler* const Handler)/* overload */;
	
private:
	int FCommandHandle;
	int FRowHandle;
	int FBlobHandle;
	__int64 FRow;
	int FOrdinal;
	bool FOutParameter;
	Data::Dbxcommon::TDBXStreamReader* FStreamReader;
	bool FEos;
	
public:
	__property int CommandHandle = {read=FCommandHandle, write=FCommandHandle, nodefault};
	__property int BlobHandle = {read=FBlobHandle, write=FBlobHandle, nodefault};
	__property int Ordinal = {read=FOrdinal, write=FOrdinal, nodefault};
	__property __int64 Row = {read=FRow, write=FRow};
	__property bool OutParameter = {read=FOutParameter, write=FOutParameter, nodefault};
	__property Data::Dbxcommon::TDBXStreamReader* StreamReader = {read=FStreamReader, write=FStreamReader};
	__property int RowHandle = {read=FRowHandle, write=FRowHandle, nodefault};
	__property bool Eos = {read=FEos, write=FEos, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDBXMoreBlobMessage() : TDBXMessage() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMoreBlobMessage() { }
	
};


class PASCALIMPLEMENTATION TDBXNextMessage : public TDBXMessage
{
	typedef TDBXMessage inherited;
	
public:
	void __fastcall HandleMessage(TDBXCommandHandler* const Handler);
	
private:
	int FCommandHandle;
	int FRowHandle;
	__int64 FPosition;
	Data::Dbxcommontable::TDBXActiveTableReaderList* FActiveStreamerRowList;
	
public:
	__property int CommandHandle = {read=FCommandHandle, write=FCommandHandle, nodefault};
	__property __int64 Position = {read=FPosition, write=FPosition};
	__property int RowHandle = {read=FRowHandle, write=FRowHandle, nodefault};
	__property Data::Dbxcommontable::TDBXActiveTableReaderList* ActiveStreamerRowList = {read=FActiveStreamerRowList, write=FActiveStreamerRowList};
public:
	/* TObject.Create */ inline __fastcall TDBXNextMessage() : TDBXMessage() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXNextMessage() { }
	
};


class PASCALIMPLEMENTATION TDBXNextResultMessage : public TDBXMessage
{
	typedef TDBXMessage inherited;
	
public:
	void __fastcall HandleMessage(TDBXCommandHandler* const Handler);
	
private:
	int FCommandHandle;
	bool FUpdateable;
	__int64 FRowsAffected;
	Data::Dbxcommon::TDBXReader* FNextResult;
	
public:
	__property int CommandHandle = {read=FCommandHandle, write=FCommandHandle, nodefault};
	__property Data::Dbxcommon::TDBXReader* NextResult = {read=FNextResult, write=FNextResult};
	__property bool Updateable = {read=FUpdateable, write=FUpdateable, nodefault};
	__property __int64 RowsAffected = {read=FRowsAffected, write=FRowsAffected};
public:
	/* TObject.Create */ inline __fastcall TDBXNextResultMessage() : TDBXMessage() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXNextResultMessage() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXOpenMessage : public TDBXMessage
{
	typedef TDBXMessage inherited;
	
public:
	void __fastcall HandleMessage(TDBXConnectionHandler* const Handler);
	
private:
	int FConnectionHandle;
	
public:
	__property int ConnectionHandle = {read=FConnectionHandle, write=FConnectionHandle, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDBXOpenMessage() : TDBXMessage() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXOpenMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXPrepareMessage : public TDBXCommandMessage
{
	typedef TDBXCommandMessage inherited;
	
public:
	void __fastcall Reset();
	void __fastcall HandleMessage(TDBXCommandHandler* const Handler);
public:
	/* TDBXCommandMessage.Destroy */ inline __fastcall virtual ~TDBXPrepareMessage() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXPrepareMessage() : TDBXCommandMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXProtocolHandler : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual void __fastcall HandleProtocol() = 0 ;
	virtual bool __fastcall HandleNonBlockingProtocol() = 0 ;
	virtual void __fastcall SetUp(System::TObject* const Data) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TDBXProtocolHandler() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXProtocolHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXReaderCloseMessage : public TDBXMessage
{
	typedef TDBXMessage inherited;
	
public:
	void __fastcall HandleMessage(TDBXCommandHandler* const Handler);
	
private:
	int FReaderHandle;
	int FCommandHandle;
	
public:
	__property int CommandHandle = {read=FCommandHandle, write=FCommandHandle, nodefault};
	__property int ReaderHandle = {read=FReaderHandle, write=FReaderHandle, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDBXReaderCloseMessage() : TDBXMessage() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXReaderCloseMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTxBeginMessage : public TDBXMessage
{
	typedef TDBXMessage inherited;
	
public:
	void __fastcall HandleMessage(TDBXConnectionHandler* const Handler);
	
private:
	int FIsolationLevel;
	int FTransactionHandle;
	
public:
	__property int IsolationLevel = {read=FIsolationLevel, write=FIsolationLevel, nodefault};
	__property int TransactionHandle = {read=FTransactionHandle, write=FTransactionHandle, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDBXTxBeginMessage() : TDBXMessage() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTxBeginMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTxEndMessage : public TDBXMessage
{
	typedef TDBXMessage inherited;
	
public:
	void __fastcall HandleMessage(TDBXConnectionHandler* const Handler);
	
private:
	bool FCommit;
	int FTransactionHandle;
	
public:
	__property int TransactionHandle = {read=FTransactionHandle, write=FTransactionHandle, nodefault};
	__property bool Commit = {read=FCommit, write=FCommit, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDBXTxEndMessage() : TDBXMessage() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTxEndMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXVendorPropertyMessage : public TDBXMessage
{
	typedef TDBXMessage inherited;
	
public:
	void __fastcall HandleMessage(TDBXConnectionHandler* const Handler);
	
private:
	System::UnicodeString FPropertyName;
	System::UnicodeString FPropertyValue;
	
public:
	__property System::UnicodeString PropertyName = {read=FPropertyName, write=FPropertyName};
	__property System::UnicodeString PropertyValue = {read=FPropertyValue, write=FPropertyValue};
public:
	/* TObject.Create */ inline __fastcall TDBXVendorPropertyMessage() : TDBXMessage() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXVendorPropertyMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmessagehandlercommon */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMESSAGEHANDLERCOMMON)
using namespace Data::Dbxmessagehandlercommon;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmessagehandlercommonHPP
