// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMessageHandlerJSonServer.pas' rev: 34.00 (Windows)

#ifndef Data_DbxmessagehandlerjsonserverHPP
#define Data_DbxmessagehandlerjsonserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.JSON.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXJSON.hpp>
#include <Data.DBXMessageHandlerCommon.hpp>
#include <Data.DBXMessageHandlerJSonCommon.hpp>
#include <Data.DBXPlatform.hpp>
#include <Data.DBXStream.hpp>
#include <System.SysUtils.hpp>
#include <Datasnap.DSSession.hpp>
#include <Datasnap.DSHTTPCommon.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmessagehandlerjsonserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXJSonServerInputConnectionHandler;
class DELPHICLASS TDBXJSonServerOutputConnectionHandler;
class DELPHICLASS TDBXJSonServerProtocolHandler;
class DELPHICLASS TDBXServerCallback;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXJSonServerInputConnectionHandler : public Data::Dbxmessagehandlerjsoncommon::TDBXJSonConnectionHandler
{
	typedef Data::Dbxmessagehandlerjsoncommon::TDBXJSonConnectionHandler inherited;
	
public:
	__fastcall TDBXJSonServerInputConnectionHandler(Data::Dbxcommon::TDBXContext* const ADbxContext, const bool AUsesDbxParameters, Data::Dbxmessagehandlercommon::TDBXConnectionHandler* const ANextHandler, Data::Dbxstream::TDBXJSonStreamReader* const ADbxStreamReader, Data::Dbxstream::TDBXJSonStreamWriter* const ADbxStreamWriter, Data::Dbxstream::TDBXRowBuffer* const ARowBuffer);
	__fastcall virtual ~TDBXJSonServerInputConnectionHandler();
	virtual void __fastcall DbxOpen(Data::Dbxmessagehandlercommon::TDBXOpenMessage* const Message);
	virtual bool __fastcall DbxBeforeRequest();
	virtual Data::Dbxmessagehandlercommon::TDBXCommandHandler* __fastcall AcquireCommandHandler(Data::Dbxmessagehandlercommon::TDBXCommandMessage* const Message);
	void __fastcall HandleProtocol();
	bool __fastcall HandleNonBlockingProtocol();
	bool __fastcall HandleDbxRequest();
	virtual void __fastcall DbxConnect(Data::Dbxmessagehandlercommon::TDBXConnectMessage* const Message);
	virtual void __fastcall DbxDisconnect(Data::Dbxmessagehandlercommon::TDBXDisconnectMessage* const Message);
	virtual void __fastcall DbxExecute(Data::Dbxmessagehandlercommon::TDBXExecuteMessage* const Message);
	virtual void __fastcall DbxNextResult(Data::Dbxmessagehandlercommon::TDBXNextResultMessage* const Message);
	virtual void __fastcall DbxPrepare(Data::Dbxmessagehandlercommon::TDBXPrepareMessage* const Message);
	virtual void __fastcall DbxNext(Data::Dbxmessagehandlercommon::TDBXNextMessage* const Message);
	virtual void __fastcall DbxMoreBlob(Data::Dbxmessagehandlercommon::TDBXMoreBlobMessage* const Message);
	virtual void __fastcall DbxCommandClose(Data::Dbxmessagehandlercommon::TDBXCommandCloseMessage* const Message);
	virtual void __fastcall DbxReaderClose(Data::Dbxmessagehandlercommon::TDBXReaderCloseMessage* const Message);
	virtual void __fastcall DbxTxBegin(Data::Dbxmessagehandlercommon::TDBXTxBeginMessage* const Message);
	virtual void __fastcall DbxTxEnd(Data::Dbxmessagehandlercommon::TDBXTxEndMessage* const Message);
	virtual void __fastcall DbxVendorProperty(Data::Dbxmessagehandlercommon::TDBXVendorPropertyMessage* const Message);
	virtual void __fastcall DbxErrorMessage(Data::Dbxmessagehandlercommon::TDBXErrorMessage* const Message);
	void __fastcall Close();
	
protected:
	virtual System::UnicodeString __fastcall GetProductName();
	
private:
	void __fastcall UnexpectedError(System::Sysutils::Exception* const Ex);
	void __fastcall ProcessDisconnect(Data::Dbxmessagehandlercommon::TDBXDisconnectMessage* const Message);
	Data::Dbxplatform::TDBXInt32s __fastcall ReadDbxDataTypes();
	
protected:
	Data::Dbxmessagehandlercommon::TDBXCommandCloseMessage* FCommandCloseMessage;
	Data::Dbxmessagehandlercommon::TDBXConnectMessage* FConnectMessage;
	Data::Dbxmessagehandlercommon::TDBXDisconnectMessage* FDisconnectMessage;
	Data::Dbxmessagehandlercommon::TDBXExecuteMessage* FExecuteMessage;
	Data::Dbxmessagehandlercommon::TDBXMoreBlobMessage* FMoreBlobMessage;
	Data::Dbxmessagehandlercommon::TDBXNextMessage* FNextMessage;
	Data::Dbxmessagehandlercommon::TDBXNextResultMessage* FNextResultMessage;
	Data::Dbxmessagehandlercommon::TDBXPrepareMessage* FPrepareMessage;
	Data::Dbxmessagehandlercommon::TDBXReaderCloseMessage* FReaderCloseMessage;
	Data::Dbxmessagehandlercommon::TDBXTxBeginMessage* FTxBeginMessage;
	Data::Dbxmessagehandlercommon::TDBXTxEndMessage* FTxEndMessage;
	Data::Dbxmessagehandlercommon::TDBXVendorPropertyMessage* FVendorProperMessage;
	Data::Dbxmessagehandlercommon::TDBXErrorMessage* FErrorMessage;
	
private:
	bool FHandleRequests;
	int FMinRowBufferSize;
	Data::Dbxcommontable::TDBXActiveTableReaderList* FActiveStreamerRowList;
	Data::Dbxmessagehandlercommon::TDBXConnectionHandler* FNextHandler;
	Data::Dbxcommon::TDBXProperties* FConnectProps;
	
public:
	__property int MinRowBufferSize = {read=FMinRowBufferSize, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXJSonServerOutputConnectionHandler : public Data::Dbxmessagehandlerjsoncommon::TDBXJSonConnectionHandler
{
	typedef Data::Dbxmessagehandlerjsoncommon::TDBXJSonConnectionHandler inherited;
	
public:
	__fastcall TDBXJSonServerOutputConnectionHandler(Data::Dbxcommon::TDBXContext* const ADbxContext, Data::Dbxstream::TDBXJSonStreamReader* const ADbxStreamReader, Data::Dbxstream::TDBXJSonStreamWriter* const ADbxStreamWriter, Data::Dbxstream::TDBXRowBuffer* const ARowBuffer);
	__fastcall virtual ~TDBXJSonServerOutputConnectionHandler();
	virtual void __fastcall DbxOpen(Data::Dbxmessagehandlercommon::TDBXOpenMessage* const Message);
	virtual bool __fastcall DbxBeforeRequest();
	virtual void __fastcall DbxExecute(Data::Dbxmessagehandlercommon::TDBXExecuteMessage* const Message);
	virtual void __fastcall DbxPrepare(Data::Dbxmessagehandlercommon::TDBXPrepareMessage* const Message);
	virtual void __fastcall DbxNextResult(Data::Dbxmessagehandlercommon::TDBXNextResultMessage* const Message);
	virtual void __fastcall DbxNext(Data::Dbxmessagehandlercommon::TDBXNextMessage* const Message);
	virtual void __fastcall DbxMoreBlob(Data::Dbxmessagehandlercommon::TDBXMoreBlobMessage* const Message);
	virtual void __fastcall DbxCommandClose(Data::Dbxmessagehandlercommon::TDBXCommandCloseMessage* const Message);
	virtual void __fastcall DbxReaderClose(Data::Dbxmessagehandlercommon::TDBXReaderCloseMessage* const Message);
	virtual void __fastcall DbxErrorMessage(Data::Dbxmessagehandlercommon::TDBXErrorMessage* const Message);
	virtual void __fastcall DbxVendorProperty(Data::Dbxmessagehandlercommon::TDBXVendorPropertyMessage* const Message);
	virtual void __fastcall DbxConnect(Data::Dbxmessagehandlercommon::TDBXConnectMessage* const Message);
	virtual void __fastcall DbxDisconnect(Data::Dbxmessagehandlercommon::TDBXDisconnectMessage* const Message);
	virtual void __fastcall DbxTxBegin(Data::Dbxmessagehandlercommon::TDBXTxBeginMessage* const Message);
	virtual void __fastcall DbxTxEnd(Data::Dbxmessagehandlercommon::TDBXTxEndMessage* const Message);
	virtual Data::Dbxmessagehandlercommon::TDBXCommandHandler* __fastcall AcquireCommandHandler(Data::Dbxmessagehandlercommon::TDBXCommandMessage* const Message);
	virtual Data::Dbxcommontable::TDBXStreamerRow* __fastcall CreateDbxRow();
	void __fastcall FlushRowBuffer();
	
protected:
	virtual System::UnicodeString __fastcall GetProductName();
	void __fastcall SetDbxStreamReader(Data::Dbxstream::TDBXJSonStreamReader* const DbxStreamReader);
	void __fastcall SetDbxStreamWriter(Data::Dbxstream::TDBXJSonStreamWriter* const DbxStreamWriter);
	
private:
	int __fastcall WriteReaderFirst(Data::Dbxmessagehandlercommon::TDBXExecuteMessage* const Message, Data::Dbxcommon::TDBXReader* const ReturnTableReader, const bool SomethingWritten);
	void __fastcall WriteReaderNext(Data::Dbxmessagehandlercommon::TDBXExecuteMessage* const Message, Data::Dbxcommon::TDBXReader* const Reader, const int RowHandle);
	
public:
	__property Data::Dbxstream::TDBXJSonStreamReader* DbxStreamReader = {read=FDbxStreamReader, write=SetDbxStreamReader};
	__property Data::Dbxstream::TDBXJSonStreamWriter* DbxStreamWriter = {read=FDbxStreamWriter, write=SetDbxStreamWriter};
	__property Data::Dbxstream::TDBXRowBuffer* DbxRowBuffer = {read=FDbxRowBuffer, write=FDbxRowBuffer};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXJSonServerProtocolHandler : public Data::Dbxmessagehandlercommon::TDBXProtocolHandler
{
	typedef Data::Dbxmessagehandlercommon::TDBXProtocolHandler inherited;
	
private:
	Datasnap::Dssession::TDSSession* FDSSession;
	Datasnap::Dssession::_di_TDSSessionEvent FSessionEvent;
	
public:
	__fastcall TDBXJSonServerProtocolHandler(TDBXJSonServerInputConnectionHandler* const AConnectionHandler);
	__fastcall virtual ~TDBXJSonServerProtocolHandler();
	virtual void __fastcall HandleProtocol();
	virtual bool __fastcall HandleNonBlockingProtocol();
	virtual void __fastcall SetUp(System::TObject* const Data);
	__property Datasnap::Dssession::TDSSession* DSSession = {read=FDSSession, write=FDSSession};
	
private:
	TDBXJSonServerInputConnectionHandler* FConnectionHandler;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXServerCallback : public Data::Dbxjson::TDBXCallback
{
	typedef Data::Dbxjson::TDBXCallback inherited;
	
public:
	virtual System::Json::TJSONValue* __fastcall Execute(System::Json::TJSONValue* const Arg)/* overload */;
	virtual System::TObject* __fastcall Execute(System::TObject* Arg)/* overload */;
	
protected:
	virtual System::TObject* __fastcall GetConnectionHandler();
	virtual void __fastcall SetConnectionHandler(System::TObject* const ConnectionHandler);
	virtual int __fastcall GetOrdinal();
	virtual void __fastcall SetOrdinal(const int Ordinal);
	virtual System::TObject* __fastcall GetDsServer();
	virtual void __fastcall SetDsServer(System::TObject* const DsServer);
	virtual bool __fastcall IsConnectionLost();
	
private:
	System::TObject* FConnectionHandler;
	System::TObject* FDsServer;
	int FOrdinal;
	
public:
	__property System::TObject* ConnectionHandler = {read=GetConnectionHandler, write=SetConnectionHandler};
	__property int Ordinal = {read=GetOrdinal, write=SetOrdinal, nodefault};
	__property System::TObject* DsServer = {read=GetDsServer, write=SetDsServer};
public:
	/* TObject.Create */ inline __fastcall TDBXServerCallback() : Data::Dbxjson::TDBXCallback() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXServerCallback() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmessagehandlerjsonserver */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMESSAGEHANDLERJSONSERVER)
using namespace Data::Dbxmessagehandlerjsonserver;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmessagehandlerjsonserverHPP
