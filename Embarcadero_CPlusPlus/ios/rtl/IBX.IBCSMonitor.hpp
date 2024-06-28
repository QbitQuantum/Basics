// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBCSMonitor.pas' rev: 34.00 (iOS)

#ifndef Ibx_IbcsmonitorHPP
#define Ibx_IbcsmonitorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IBX.IBSQLMonitor.hpp>
#include <IBX.IBSQL.hpp>
#include <IBX.IBDatabase.hpp>
#include <IBX.IBServices.hpp>
#include <IBX.IB.hpp>
#include <IPPeerAPI.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SyncObjs.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibcsmonitor
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBContext;
class DELPHICLASS TIBMonitorServer;
class DELPHICLASS TIBMonitorClient;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIBContext : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Generics::Collections::TThreadList__1<System::TArray__1<System::Byte> >* FQueue;
	System::Syncobjs::TEvent* FEvent;
	Ippeerapi::_di_IIPContext FContext;
	
public:
	__fastcall TIBContext(Ippeerapi::_di_IIPContext AContext);
	__fastcall virtual ~TIBContext();
	__property Ippeerapi::_di_IIPContext Context = {read=FContext};
	void __fastcall AddMsgToQueue(const System::TArray__1<System::Byte> Msg);
	System::Generics::Collections::TList__1<System::TArray__1<System::Byte> >* __fastcall GetQueuedMsgs();
};


class PASCALIMPLEMENTATION TIBMonitorServer : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Ippeerapi::_di_IIPTCPServer FidServer;
	System::Generics::Collections::TObjectDictionary__2<Ippeerapi::_di_IIPContext,TIBContext*>* FContexts;
	bool FEnabled;
	Ibx::Ib::TTraceFlags FTraceFlags;
	bool FActive;
	int FPort;
	void __fastcall OnConnect(Ippeerapi::_di_IIPContext AContext);
	void __fastcall OnDisconnect(Ippeerapi::_di_IIPContext AContext);
	void __fastcall ServerExecute(Ippeerapi::_di_IIPContext AContext);
	bool __fastcall GetActive();
	void __fastcall SetActive(const bool Value);
	void __fastcall Start();
	void __fastcall Stop();
	
protected:
	void __fastcall WriteSQLData(System::UnicodeString Text, Ibx::Ib::TTraceFlag DataType);
	
public:
	__fastcall virtual TIBMonitorServer(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBMonitorServer();
	void __fastcall RegisterMonitor(Ibx::Ibsqlmonitor::TIBCustomSQLMonitor* SQLMonitor);
	void __fastcall UnregisterMonitor(Ibx::Ibsqlmonitor::TIBCustomSQLMonitor* SQLMonitor);
	void __fastcall ReleaseMonitor(Ibx::Ibsqlmonitor::TIBCustomSQLMonitor* Arg);
	virtual void __fastcall SQLPrepare(Ibx::Ibsql::TIBSQL* qry);
	virtual void __fastcall SQLExecute(Ibx::Ibsql::TIBSQL* qry);
	virtual void __fastcall SQLFetch(Ibx::Ibsql::TIBSQL* qry);
	virtual void __fastcall DBConnect(Ibx::Ibdatabase::TIBDatabase* db);
	virtual void __fastcall DBDisconnect(Ibx::Ibdatabase::TIBDatabase* db);
	virtual void __fastcall TRStart(Ibx::Ibdatabase::TIBTransaction* tr);
	virtual void __fastcall TRCommit(Ibx::Ibdatabase::TIBTransaction* tr);
	virtual void __fastcall TRCommitRetaining(Ibx::Ibdatabase::TIBTransaction* tr);
	virtual void __fastcall TRRollback(Ibx::Ibdatabase::TIBTransaction* tr);
	virtual void __fastcall TRRollbackRetaining(Ibx::Ibdatabase::TIBTransaction* tr);
	virtual void __fastcall ServiceAttach(Ibx::Ibservices::TIBCustomService* service);
	virtual void __fastcall ServiceDetach(Ibx::Ibservices::TIBCustomService* service);
	virtual void __fastcall ServiceQuery(Ibx::Ibservices::TIBCustomService* service);
	virtual void __fastcall ServiceStart(Ibx::Ibservices::TIBCustomService* service);
	void __fastcall SendMisc(System::UnicodeString Msg);
	void __fastcall SendError(System::UnicodeString Msg, Ibx::Ibdatabase::TIBDatabase* db)/* overload */;
	void __fastcall SendError(System::UnicodeString Msg)/* overload */;
	bool __fastcall GetEnabled();
	Ibx::Ib::TTraceFlags __fastcall GetTraceFlags();
	int __fastcall GetMonitorCount();
	void __fastcall SetEnabled(const bool Value);
	void __fastcall SetTraceFlags(const Ibx::Ib::TTraceFlags Value);
	
__published:
	__property Ibx::Ib::TTraceFlags TraceFlags = {read=GetTraceFlags, write=SetTraceFlags, nodefault};
	__property bool Enabled = {read=GetEnabled, write=SetEnabled, default=1};
	__property int Port = {read=FPort, write=FPort, default=212};
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
private:
	void *__IIBSQLMonitorHook;	// Ibx::Ibsqlmonitor::IIBSQLMonitorHook 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CF65434C-9B75-4298-BA7E-E6B85B3C769D}
	operator Ibx::Ibsqlmonitor::_di_IIBSQLMonitorHook()
	{
		Ibx::Ibsqlmonitor::_di_IIBSQLMonitorHook intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Ibx::Ibsqlmonitor::IIBSQLMonitorHook*(void) { return (Ibx::Ibsqlmonitor::IIBSQLMonitorHook*)&__IIBSQLMonitorHook; }
	#endif
	
};


class PASCALIMPLEMENTATION TIBMonitorClient : public Ibx::Ibsqlmonitor::TIBCustomSQLMonitor
{
	typedef Ibx::Ibsqlmonitor::TIBCustomSQLMonitor inherited;
	
private:
	Ippeerapi::_di_IIPTCPClient FidClient;
	System::Classes::TThread* FThread;
	bool FEnabled;
	int __fastcall GetPort();
	void __fastcall SetPort(const int Value);
	System::UnicodeString __fastcall GetHost();
	void __fastcall SetHost(const System::UnicodeString Value);
	Ippeerapi::TIPVersionPeer __fastcall GetIPVersion();
	void __fastcall SetIPVersion(const Ippeerapi::TIPVersionPeer Value);
	void __fastcall ClientConnected();
	void __fastcall FOnTerminate(System::TObject* Sender);
	void __fastcall OnData(Ibx::Ib::TTraceFlag TraceFlag, System::TDateTime EventTime, System::UnicodeString Msg);
	
protected:
	virtual bool __fastcall GetEnabled();
	virtual void __fastcall SetEnabled(const bool Value);
	
public:
	__fastcall virtual TIBMonitorClient(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBMonitorClient();
	
__published:
	__property int Port = {read=GetPort, write=SetPort, default=212};
	__property System::UnicodeString Host = {read=GetHost, write=SetHost};
	__property Ippeerapi::TIPVersionPeer IPVersion = {read=GetIPVersion, write=SetIPVersion, nodefault};
	__property OnSQL;
	__property TraceFlags;
	__property Enabled = {default=0};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibcsmonitor */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBCSMONITOR)
using namespace Ibx::Ibcsmonitor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbcsmonitorHPP
