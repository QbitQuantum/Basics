// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMessageHandlerJSonClient.pas' rev: 34.00 (Windows)

#ifndef Data_DbxmessagehandlerjsonclientHPP
#define Data_DbxmessagehandlerjsonclientHPP

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
#include <Data.DBXMessageHandlerCommon.hpp>
#include <Data.DBXMessageHandlerJSonCommon.hpp>
#include <Data.DBXStream.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmessagehandlerjsonclient
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXJSonClientInputConnectionHandler;
class DELPHICLASS TDBXJSonClientOutputConnectionHandler;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXJSonClientInputConnectionHandler : public Data::Dbxmessagehandlerjsoncommon::TDBXJSonConnectionHandler
{
	typedef Data::Dbxmessagehandlerjsoncommon::TDBXJSonConnectionHandler inherited;
	
public:
	__fastcall TDBXJSonClientInputConnectionHandler(Data::Dbxcommon::TDBXContext* const ADbxContext, Data::Dbxstream::TDBXJSonStreamReader* const ADbxStreamReader, Data::Dbxstream::TDBXJSonStreamWriter* const ADbxStreamWriter, Data::Dbxstream::TDBXRowBuffer* const ARowBuffer);
	virtual Data::Dbxmessagehandlercommon::TDBXCommandHandler* __fastcall AcquireCommandHandler(Data::Dbxmessagehandlercommon::TDBXCommandMessage* const Message);
	virtual bool __fastcall DbxBeforeRequest();
	virtual void __fastcall DbxConnect(Data::Dbxmessagehandlercommon::TDBXConnectMessage* const Message);
	virtual void __fastcall DbxDisconnect(Data::Dbxmessagehandlercommon::TDBXDisconnectMessage* const Message);
	virtual void __fastcall DbxOpen(Data::Dbxmessagehandlercommon::TDBXOpenMessage* const Message);
	virtual void __fastcall DbxTxBegin(Data::Dbxmessagehandlercommon::TDBXTxBeginMessage* const Message);
	virtual void __fastcall DbxTxEnd(Data::Dbxmessagehandlercommon::TDBXTxEndMessage* const Message);
	virtual void __fastcall DbxVendorProperty(Data::Dbxmessagehandlercommon::TDBXVendorPropertyMessage* const Message);
	virtual void __fastcall DbxCommandClose(Data::Dbxmessagehandlercommon::TDBXCommandCloseMessage* const Message);
	virtual void __fastcall DbxErrorMessage(Data::Dbxmessagehandlercommon::TDBXErrorMessage* const Message);
	virtual void __fastcall DbxExecute(Data::Dbxmessagehandlercommon::TDBXExecuteMessage* const Message);
	virtual void __fastcall DbxMoreBlob(Data::Dbxmessagehandlercommon::TDBXMoreBlobMessage* const Message);
	virtual void __fastcall DbxNext(Data::Dbxmessagehandlercommon::TDBXNextMessage* const Message);
	virtual void __fastcall DbxNextResult(Data::Dbxmessagehandlercommon::TDBXNextResultMessage* const Message);
	virtual void __fastcall DbxPrepare(Data::Dbxmessagehandlercommon::TDBXPrepareMessage* const Message);
	virtual void __fastcall DbxReaderClose(Data::Dbxmessagehandlercommon::TDBXReaderCloseMessage* const Message);
	
protected:
	virtual System::UnicodeString __fastcall GetProductName();
	
private:
	void __fastcall HandleParameterMoreBlobRequest(Data::Dbxcommon::TDBXParameterList* const Parameters);
	void __fastcall HandleCallbackRequest(Data::Dbxcommon::TDBXParameterList* const Parameters);
	void __fastcall HandleParameterNextRequest(Data::Dbxmessagehandlercommon::TDBXExecuteMessage* const Message);
	System::Json::TJSONValue* __fastcall InvokeClientCallback(int argType, Data::Dbxcommon::TDBXParameter* Parameter, System::Json::TJSONValue* rawInput);
	int __fastcall FindNextReaderOrdinal(Data::Dbxcommon::TDBXParameterList* const Parameters, const int InLastReaderOrdinal);
public:
	/* TDBXJSonConnectionHandler.Destroy */ inline __fastcall virtual ~TDBXJSonClientInputConnectionHandler() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXJSonClientOutputConnectionHandler : public Data::Dbxmessagehandlerjsoncommon::TDBXJSonConnectionHandler
{
	typedef Data::Dbxmessagehandlerjsoncommon::TDBXJSonConnectionHandler inherited;
	
public:
	__fastcall TDBXJSonClientOutputConnectionHandler(Data::Dbxcommon::TDBXContext* const ADbxContext, Data::Dbxmessagehandlercommon::TDBXConnectionHandler* const ANextHandler, Data::Dbxstream::TDBXJSonStreamReader* const ADbxStreamReader, Data::Dbxstream::TDBXJSonStreamWriter* const ADbxStreamWriter, Data::Dbxstream::TDBXRowBuffer* const ARowBuffer);
	__fastcall virtual ~TDBXJSonClientOutputConnectionHandler();
	virtual Data::Dbxmessagehandlercommon::TDBXCommandHandler* __fastcall AcquireCommandHandler(Data::Dbxmessagehandlercommon::TDBXCommandMessage* const Message);
	virtual bool __fastcall DbxBeforeRequest();
	virtual void __fastcall DbxConnect(Data::Dbxmessagehandlercommon::TDBXConnectMessage* const Message);
	virtual void __fastcall DbxDisconnect(Data::Dbxmessagehandlercommon::TDBXDisconnectMessage* const Message);
	virtual void __fastcall DbxOpen(Data::Dbxmessagehandlercommon::TDBXOpenMessage* const Message);
	virtual void __fastcall DbxTxBegin(Data::Dbxmessagehandlercommon::TDBXTxBeginMessage* const Message);
	virtual void __fastcall DbxTxEnd(Data::Dbxmessagehandlercommon::TDBXTxEndMessage* const Message);
	virtual void __fastcall DbxVendorProperty(Data::Dbxmessagehandlercommon::TDBXVendorPropertyMessage* const Message);
	virtual void __fastcall DbxCommandClose(Data::Dbxmessagehandlercommon::TDBXCommandCloseMessage* const Message);
	virtual void __fastcall DbxErrorMessage(Data::Dbxmessagehandlercommon::TDBXErrorMessage* const Message);
	virtual void __fastcall DbxExecute(Data::Dbxmessagehandlercommon::TDBXExecuteMessage* const Message);
	virtual void __fastcall DbxMoreBlob(Data::Dbxmessagehandlercommon::TDBXMoreBlobMessage* const Message);
	virtual void __fastcall DbxNext(Data::Dbxmessagehandlercommon::TDBXNextMessage* const Message);
	virtual void __fastcall DbxNextResult(Data::Dbxmessagehandlercommon::TDBXNextResultMessage* const Message);
	virtual void __fastcall DbxPrepare(Data::Dbxmessagehandlercommon::TDBXPrepareMessage* const Message);
	virtual void __fastcall DbxReaderClose(Data::Dbxmessagehandlercommon::TDBXReaderCloseMessage* const Message);
	
protected:
	virtual System::UnicodeString __fastcall GetProductName();
	
private:
	void __fastcall WriteInputStreamerParameters(const int CommandHandle, Data::Dbxcommontable::TDBXStreamerRow* const StreamerRow, Data::Dbxcommontable::TDBXActiveTableReaderList* const ActiveStreamerList, Data::Dbxcommon::TDBXParameterList* const Parameters, const bool DataWritten);
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
	Data::Dbxmessagehandlercommon::TDBXConnectionHandler* FNextHandler;
	
public:
	__property Data::Dbxmessagehandlercommon::TDBXCommandCloseMessage* CommandCloseMessage = {read=FCommandCloseMessage, write=FCommandCloseMessage};
	__property Data::Dbxmessagehandlercommon::TDBXConnectMessage* ConnectMessage = {read=FConnectMessage, write=FConnectMessage};
	__property Data::Dbxmessagehandlercommon::TDBXDisconnectMessage* DisconnectMessage = {read=FDisconnectMessage, write=FDisconnectMessage};
	__property Data::Dbxmessagehandlercommon::TDBXExecuteMessage* ExecuteMessage = {read=FExecuteMessage, write=FExecuteMessage};
	__property Data::Dbxmessagehandlercommon::TDBXMoreBlobMessage* MoreBlobMessage = {read=FMoreBlobMessage, write=FMoreBlobMessage};
	__property Data::Dbxmessagehandlercommon::TDBXNextMessage* NextMessage = {read=FNextMessage, write=FNextMessage};
	__property Data::Dbxmessagehandlercommon::TDBXNextResultMessage* NextResultMessage = {read=FNextResultMessage, write=FNextResultMessage};
	__property Data::Dbxmessagehandlercommon::TDBXPrepareMessage* PrepareMessage = {read=FPrepareMessage, write=FPrepareMessage};
	__property Data::Dbxmessagehandlercommon::TDBXReaderCloseMessage* ReaderCloseMessage = {read=FReaderCloseMessage, write=FReaderCloseMessage};
	__property Data::Dbxmessagehandlercommon::TDBXTxBeginMessage* TxBeginMessage = {read=FTxBeginMessage, write=FTxBeginMessage};
	__property Data::Dbxmessagehandlercommon::TDBXTxEndMessage* TxEndMessage = {read=FTxEndMessage, write=FTxEndMessage};
	__property Data::Dbxmessagehandlercommon::TDBXVendorPropertyMessage* VendorProperMessage = {read=FVendorProperMessage, write=FVendorProperMessage};
	__property Data::Dbxmessagehandlercommon::TDBXErrorMessage* ErrorMessage = {read=FErrorMessage, write=FErrorMessage};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmessagehandlerjsonclient */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMESSAGEHANDLERJSONCLIENT)
using namespace Data::Dbxmessagehandlerjsonclient;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmessagehandlerjsonclientHPP
