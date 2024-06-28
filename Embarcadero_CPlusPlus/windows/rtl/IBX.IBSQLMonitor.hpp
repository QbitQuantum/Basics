// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBSQLMonitor.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbsqlmonitorHPP
#define Ibx_IbsqlmonitorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.Classes.hpp>
#include <IBX.IB.hpp>
#include <IBX.IBUtils.hpp>
#include <IBX.IBSQL.hpp>
#include <IBX.IBCustomDataSet.hpp>
#include <IBX.IBDatabase.hpp>
#include <IBX.IBServices.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibsqlmonitor
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBCustomSQLMonitor;
class DELPHICLASS TIBSQLMonitor;
__interface DELPHIINTERFACE IIBSQLMonitorHook;
typedef System::DelphiInterface<IIBSQLMonitorHook> _di_IIBSQLMonitorHook;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TSQLEvent)(System::UnicodeString EventText, System::TDateTime EventTime);

class PASCALIMPLEMENTATION TIBCustomSQLMonitor : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TSQLEvent FOnSQLEvent;
	Ibx::Ib::TTraceFlags FTraceFlags;
	
protected:
	virtual bool __fastcall GetEnabled() = 0 ;
	virtual void __fastcall SetEnabled(const bool Value) = 0 ;
	__property TSQLEvent OnSQL = {read=FOnSQLEvent, write=FOnSQLEvent};
	__property Ibx::Ib::TTraceFlags TraceFlags = {read=FTraceFlags, write=FTraceFlags, nodefault};
	__property bool Enabled = {read=GetEnabled, write=SetEnabled, default=0};
	
public:
	__fastcall virtual TIBCustomSQLMonitor(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBCustomSQLMonitor();
};


class PASCALIMPLEMENTATION TIBSQLMonitor : public TIBCustomSQLMonitor
{
	typedef TIBCustomSQLMonitor inherited;
	
private:
	bool FEnabled;
	HWND FHWnd;
	void __fastcall MonitorWndProc(Winapi::Messages::TMessage &Message);
	
protected:
	virtual bool __fastcall GetEnabled();
	virtual void __fastcall SetEnabled(const bool Value);
	
public:
	__fastcall virtual TIBSQLMonitor(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBSQLMonitor();
	void __fastcall Release();
#ifndef _WIN64
	__property HWND Handle = {read=FHWnd, nodefault};
#else /* _WIN64 */
	__property HWND Handle = {read=FHWnd};
#endif /* _WIN64 */
	
__published:
	__property OnSQL;
	__property TraceFlags;
	__property Enabled = {default=0};
};


__interface  INTERFACE_UUID("{CF65434C-9B75-4298-BA7E-E6B85B3C769D}") IIBSQLMonitorHook  : public System::IInterface 
{
	virtual void __fastcall RegisterMonitor(TIBCustomSQLMonitor* SQLMonitor) = 0 ;
	virtual void __fastcall UnregisterMonitor(TIBCustomSQLMonitor* SQLMonitor) = 0 ;
	virtual void __fastcall ReleaseMonitor(TIBCustomSQLMonitor* Arg) = 0 ;
	virtual void __fastcall SQLPrepare(Ibx::Ibsql::TIBSQL* qry) = 0 ;
	virtual void __fastcall SQLExecute(Ibx::Ibsql::TIBSQL* qry) = 0 ;
	virtual void __fastcall SQLFetch(Ibx::Ibsql::TIBSQL* qry) = 0 ;
	virtual void __fastcall DBConnect(Ibx::Ibdatabase::TIBDatabase* db) = 0 ;
	virtual void __fastcall DBDisconnect(Ibx::Ibdatabase::TIBDatabase* db) = 0 ;
	virtual void __fastcall TRStart(Ibx::Ibdatabase::TIBTransaction* tr) = 0 ;
	virtual void __fastcall TRCommit(Ibx::Ibdatabase::TIBTransaction* tr) = 0 ;
	virtual void __fastcall TRCommitRetaining(Ibx::Ibdatabase::TIBTransaction* tr) = 0 ;
	virtual void __fastcall TRRollback(Ibx::Ibdatabase::TIBTransaction* tr) = 0 ;
	virtual void __fastcall TRRollbackRetaining(Ibx::Ibdatabase::TIBTransaction* tr) = 0 ;
	virtual void __fastcall ServiceAttach(Ibx::Ibservices::TIBCustomService* service) = 0 ;
	virtual void __fastcall ServiceDetach(Ibx::Ibservices::TIBCustomService* service) = 0 ;
	virtual void __fastcall ServiceQuery(Ibx::Ibservices::TIBCustomService* service) = 0 ;
	virtual void __fastcall ServiceStart(Ibx::Ibservices::TIBCustomService* service) = 0 ;
	virtual void __fastcall SendMisc(System::UnicodeString Msg) = 0 ;
	virtual void __fastcall SendError(System::UnicodeString Msg, Ibx::Ibdatabase::TIBDatabase* db) = 0 /* overload */;
	virtual void __fastcall SendError(System::UnicodeString Msg) = 0 /* overload */;
	virtual Ibx::Ib::TTraceFlags __fastcall GetTraceFlags() = 0 ;
	virtual int __fastcall GetMonitorCount() = 0 ;
	virtual void __fastcall SetTraceFlags(const Ibx::Ib::TTraceFlags Value) = 0 ;
	virtual bool __fastcall GetEnabled() = 0 ;
	virtual void __fastcall SetEnabled(const bool Value) = 0 ;
	__property Ibx::Ib::TTraceFlags TraceFlags = {read=GetTraceFlags, write=SetTraceFlags};
	__property bool Enabled = {read=GetEnabled, write=SetEnabled};
};

//-- var, const, procedure ---------------------------------------------------
static const System::Word WM_MIN_IBSQL_MONITOR = System::Word(0x400);
static const System::Word WM_MAX_IBSQL_MONITOR = System::Word(0x600);
static const System::Word WM_IBSQL_SQL_EVENT = System::Word(0x401);
extern DELPHI_PACKAGE _di_IIBSQLMonitorHook __fastcall MonitorHook(void);
extern DELPHI_PACKAGE void __fastcall RemoveMonitorHook(_di_IIBSQLMonitorHook OldHook);
extern DELPHI_PACKAGE void __fastcall SetMonitorHook(_di_IIBSQLMonitorHook NewHook);
extern DELPHI_PACKAGE void __fastcall EnableMonitoring(void);
extern DELPHI_PACKAGE void __fastcall DisableMonitoring(void);
extern DELPHI_PACKAGE bool __fastcall MonitoringEnabled(void);
}	/* namespace Ibsqlmonitor */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBSQLMONITOR)
using namespace Ibx::Ibsqlmonitor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbsqlmonitorHPP
