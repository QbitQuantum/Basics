// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMessageHandlerServer.pas' rev: 34.00 (Windows)

#ifndef Data_DbxmessagehandlerserverHPP
#define Data_DbxmessagehandlerserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXMessageHandlerCommon.hpp>
#include <Data.DBXPlatform.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmessagehandlerserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXDatabaseCommandHandler;
class DELPHICLASS TDBXDatabaseConnectionHandler;
class DELPHICLASS TDBXServerParameterList;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDatabaseCommandHandler : public Data::Dbxmessagehandlercommon::TDBXCommandHandler
{
	typedef Data::Dbxmessagehandlercommon::TDBXCommandHandler inherited;
	
public:
	__fastcall TDBXDatabaseCommandHandler(Data::Dbxcommon::TDBXContext* const ADbxContext, Data::Dbxmessagehandlercommon::TDBXCommandHandler* const ANextHandler, Data::Dbxcommon::TDBXCommand* const ACommand);
	virtual void __fastcall DbxErrorMessage(Data::Dbxmessagehandlercommon::TDBXErrorMessage* const Message);
	__fastcall virtual ~TDBXDatabaseCommandHandler();
	virtual void __fastcall DbxCommandClose(Data::Dbxmessagehandlercommon::TDBXCommandCloseMessage* const Message);
	virtual void __fastcall DbxExecute(Data::Dbxmessagehandlercommon::TDBXExecuteMessage* const Message);
	virtual void __fastcall DbxMoreBlob(Data::Dbxmessagehandlercommon::TDBXMoreBlobMessage* const Message);
	virtual void __fastcall DbxNext(Data::Dbxmessagehandlercommon::TDBXNextMessage* const Message);
	virtual void __fastcall DbxNextResult(Data::Dbxmessagehandlercommon::TDBXNextResultMessage* const Message);
	void __fastcall CreateParameterList();
	virtual void __fastcall DbxPrepare(Data::Dbxmessagehandlercommon::TDBXPrepareMessage* const Message);
	virtual void __fastcall DbxReaderClose(Data::Dbxmessagehandlercommon::TDBXReaderCloseMessage* const Message);
	
private:
	Data::Dbxcommon::TDBXCommand* FCommand;
	Data::Dbxcommon::TDBXReader* FReader;
	TDBXServerParameterList* FParameterList;
	Data::Dbxcommontable::TDBXStreamerRow* FDbxRow;
	Data::Dbxcommon::TDBXParameter* FCommandParameter;
	Data::Dbxmessagehandlercommon::TDBXCommandHandler* FNextHandler;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDatabaseConnectionHandler : public Data::Dbxmessagehandlercommon::TDBXConnectionHandler
{
	typedef Data::Dbxmessagehandlercommon::TDBXConnectionHandler inherited;
	
public:
	__fastcall TDBXDatabaseConnectionHandler(Data::Dbxcommon::TDBXContext* const ADbxContext, Data::Dbxmessagehandlercommon::TDBXConnectionHandler* const ANextHandler);
	__fastcall virtual ~TDBXDatabaseConnectionHandler();
	virtual bool __fastcall DbxBeforeRequest();
	virtual void __fastcall DbxErrorMessage(Data::Dbxmessagehandlercommon::TDBXErrorMessage* const Message);
	virtual Data::Dbxmessagehandlercommon::TDBXCommandHandler* __fastcall AcquireCommandHandler(Data::Dbxmessagehandlercommon::TDBXCommandMessage* const Message);
	virtual void __fastcall DbxConnect(Data::Dbxmessagehandlercommon::TDBXConnectMessage* const Message);
	virtual void __fastcall DbxDisconnect(Data::Dbxmessagehandlercommon::TDBXDisconnectMessage* const Message);
	virtual void __fastcall DbxTxBegin(Data::Dbxmessagehandlercommon::TDBXTxBeginMessage* const Message);
	void __fastcall EndTransaction(const int Depth, const bool Commit);
	virtual void __fastcall DbxTxEnd(Data::Dbxmessagehandlercommon::TDBXTxEndMessage* const Message);
	virtual void __fastcall DbxVendorProperty(Data::Dbxmessagehandlercommon::TDBXVendorPropertyMessage* const Message);
	virtual void __fastcall DbxOpen(Data::Dbxmessagehandlercommon::TDBXOpenMessage* const Message);
	virtual void __fastcall DbxCommandClose(Data::Dbxmessagehandlercommon::TDBXCommandCloseMessage* const Message);
	virtual void __fastcall DbxExecute(Data::Dbxmessagehandlercommon::TDBXExecuteMessage* const Message);
	virtual void __fastcall DbxMoreBlob(Data::Dbxmessagehandlercommon::TDBXMoreBlobMessage* const Message);
	virtual void __fastcall DbxNext(Data::Dbxmessagehandlercommon::TDBXNextMessage* const Message);
	virtual void __fastcall DbxNextResult(Data::Dbxmessagehandlercommon::TDBXNextResultMessage* const Message);
	virtual void __fastcall DbxPrepare(Data::Dbxmessagehandlercommon::TDBXPrepareMessage* const Message);
	virtual void __fastcall DbxReaderClose(Data::Dbxmessagehandlercommon::TDBXReaderCloseMessage* const Message);
	
protected:
	virtual System::UnicodeString __fastcall GetProductName();
	
private:
	Data::Dbxcommon::TDBXConnection* FCon;
	Data::Dbxplatform::TDBXArrayList* FTransactionStack;
	Data::Dbxmessagehandlercommon::TDBXConnectionHandler* FNextHandler;
	
public:
	__property Data::Dbxcommon::TDBXConnection* DBXConnection = {read=FCon, write=FCon};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXServerParameterList : public Data::Dbxcommon::TDBXParameterList
{
	typedef Data::Dbxcommon::TDBXParameterList inherited;
	
public:
	__fastcall TDBXServerParameterList(Data::Dbxcommon::TDBXContext* const DbxContext, Data::Dbxcommon::TDBXRow* const Row);
	void __fastcall NewRowGeneration();
	void __fastcall SetOutParameters();
public:
	/* TDBXParameterList.Destroy */ inline __fastcall virtual ~TDBXServerParameterList() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmessagehandlerserver */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMESSAGEHANDLERSERVER)
using namespace Data::Dbxmessagehandlerserver;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmessagehandlerserverHPP
