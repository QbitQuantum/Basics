// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Moni.RemoteServer.pas' rev: 34.00 (Windows)

#ifndef Firedac_Moni_RemoteserverHPP
#define Firedac_Moni_RemoteserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.WinSock.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Win.ScktComp.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Consts.hpp>
#include <FireDAC.Moni.RemoteBase.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Moni
{
namespace Remoteserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDMoniRemoteServerQueueItem;
class DELPHICLASS TFDMoniRemoteReceiver;
class DELPHICLASS TFDMoniRemoteServerClientThread;
class DELPHICLASS TFDMoniRemoteServer;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFDMoniRemoteServerQueueItem : public Firedac::Moni::Remotebase::TFDMoniRemoteQueueItem
{
	typedef Firedac::Moni::Remotebase::TFDMoniRemoteQueueItem inherited;
	
public:
	System::UnicodeString FHost;
public:
	/* TFDMoniRemoteQueueItem.Create */ inline __fastcall TFDMoniRemoteServerQueueItem() : Firedac::Moni::Remotebase::TFDMoniRemoteQueueItem() { }
	/* TFDMoniRemoteQueueItem.Destroy */ inline __fastcall virtual ~TFDMoniRemoteServerQueueItem() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TFDMoniRemoteReceiver : public Firedac::Moni::Remotebase::TFDMoniRemoteQueueWorker
{
	typedef Firedac::Moni::Remotebase::TFDMoniRemoteQueueWorker inherited;
	
private:
	TFDMoniRemoteServer* FServer;
	void __fastcall DoMessage();
	
protected:
	virtual Firedac::Moni::Remotebase::TFDMoniRemoteQueue* __fastcall GetQueue();
	virtual void __fastcall DoAction();
	
public:
	__fastcall TFDMoniRemoteReceiver(TFDMoniRemoteServer* AServer);
	__fastcall virtual ~TFDMoniRemoteReceiver();
};


class PASCALIMPLEMENTATION TFDMoniRemoteServerClientThread : public System::Win::Scktcomp::TServerClientThread
{
	typedef System::Win::Scktcomp::TServerClientThread inherited;
	
private:
	TFDMoniRemoteServer* FServer;
	Firedac::Moni::Remotebase::TFDMoniRemoteStream* FStream;
	Firedac::Moni::Remotebase::TFDMoniRemoteAdapterList* FAdapterList;
	unsigned FProcessID;
	unsigned FMonitorID;
	unsigned FVersion;
	void __fastcall RemoveAllAdapters();
	
protected:
	virtual void __fastcall ClientExecute();
	
public:
	__fastcall TFDMoniRemoteServerClientThread(TFDMoniRemoteServer* AServer, System::Win::Scktcomp::TServerClientWinSocket* ASocket);
	__fastcall virtual ~TFDMoniRemoteServerClientThread();
	__property unsigned ProcessID = {read=FProcessID, write=FProcessID, nodefault};
	__property unsigned MonitorID = {read=FMonitorID, write=FMonitorID, nodefault};
	__property unsigned Version = {read=FVersion, write=FVersion, nodefault};
};


typedef void __fastcall (__closure *TFDMoniRemoteServerMessageEvent)(System::TObject* Sender, Firedac::Moni::Remotebase::TFDMoniRemoteQueueItem* AMessage);

class PASCALIMPLEMENTATION TFDMoniRemoteServer : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Win::Scktcomp::TServerSocket* FTCPServer;
	Firedac::Moni::Remotebase::TFDMoniRemoteQueue* FQueue;
	TFDMoniRemoteReceiver* FReceiver;
	int FPackVersion;
	Firedac::Moni::Remotebase::TFDMoniRemoteQueueEventKinds FSynchronize;
	TFDMoniRemoteServerMessageEvent FOnMessage;
	void __fastcall DoMessage(TFDMoniRemoteServerQueueItem* AMessage);
	void __fastcall DoGetThread(System::TObject* Sender, System::Win::Scktcomp::TServerClientWinSocket* ClientSocket, System::Win::Scktcomp::TServerClientThread* &SocketThread);
	void __fastcall DoExecute(TFDMoniRemoteServerClientThread* AClient);
	bool __fastcall GetTracing();
	void __fastcall SetTracing(const bool AValue);
	int __fastcall GetPort();
	void __fastcall SetPortI(const int AValue);
	TFDMoniRemoteServerQueueItem* __fastcall BuildItem(TFDMoniRemoteServerClientThread* AClient);
	
public:
	__fastcall TFDMoniRemoteServer();
	__fastcall virtual ~TFDMoniRemoteServer();
	__property Firedac::Moni::Remotebase::TFDMoniRemoteQueue* Queue = {read=FQueue};
	__property TFDMoniRemoteReceiver* Receiver = {read=FReceiver};
	__property int Port = {read=GetPort, write=SetPortI, default=8050};
	__property bool Tracing = {read=GetTracing, write=SetTracing, default=0};
	__property Firedac::Moni::Remotebase::TFDMoniRemoteQueueEventKinds Synchronize = {read=FSynchronize, write=FSynchronize, default=0};
	__property TFDMoniRemoteServerMessageEvent OnMessage = {read=FOnMessage, write=FOnMessage};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Remoteserver */
}	/* namespace Moni */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_MONI_REMOTESERVER)
using namespace Firedac::Moni::Remoteserver;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_MONI)
using namespace Firedac::Moni;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Moni_RemoteserverHPP
