// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBConnectionBroker.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbconnectionbrokerHPP
#define Ibx_IbconnectionbrokerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <IBX.IBDatabase.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibconnectionbroker
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBPooledConnection;
class DELPHICLASS TIBConnectionBroker;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TIBConnectionBrokerLogEvent)(System::TObject* Sender, System::UnicodeString LogMessage);

class PASCALIMPLEMENTATION TIBPooledConnection : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	int FConnStatus;
	System::TDateTime FConnLockTime;
	System::TDateTime FConnCreateDate;
	Ibx::Ibdatabase::TIBDatabase* FDatabase;
	
public:
	__fastcall virtual TIBPooledConnection(System::Classes::TComponent* AOwner);
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=FDatabase};
	__property int ConnStatus = {read=FConnStatus, write=FConnStatus, nodefault};
	__property System::TDateTime ConnLockTime = {read=FConnLockTime, write=FConnLockTime};
	__property System::TDateTime ConnCreateDate = {read=FConnCreateDate, write=FConnCreateDate};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIBPooledConnection() { }
	
};


class PASCALIMPLEMENTATION TIBConnectionBroker : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
	
private:
	typedef System::DynamicArray<TIBPooledConnection*> _TIBConnectionBroker__1;
	
	
private:
	_TIBConnectionBroker__1 FConnPool;
	System::UnicodeString FDatabaseName;
	int FCurrConnections;
	int FConnLast;
	int FMinConns;
	int FMaxConns;
	unsigned FIdleTimer;
	System::Classes::TStrings* FDBParams;
	unsigned FDelay;
	TIBConnectionBrokerLogEvent FOnLog;
	void __fastcall SetDBParams(System::Classes::TStrings* const Value);
	void __fastcall SetMaxConns(const int Value);
	void __fastcall SetMinConns(const int Value);
	int __fastcall GetAllocated();
	int __fastcall GetAvailable();
	
protected:
	void __fastcall CreateConn(int i);
	void __fastcall DoLog(System::UnicodeString msg);
	
public:
	System::Sysutils::TSimpleRWSync* CS1;
	Ibx::Ibdatabase::TIBDatabase* __fastcall GetConnection();
	__fastcall virtual TIBConnectionBroker(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBConnectionBroker();
	void __fastcall Init();
	void __fastcall ReleaseConnection(Ibx::Ibdatabase::TIBDatabase* db);
	__property int AllocatedConnections = {read=GetAllocated, nodefault};
	__property int AvailableConnections = {read=GetAvailable, nodefault};
	
__published:
	__property System::UnicodeString DatabaseName = {read=FDatabaseName, write=FDatabaseName};
	__property System::Classes::TStrings* Params = {read=FDBParams, write=SetDBParams};
	__property int MinConnections = {read=FMinConns, write=SetMinConns, default=10};
	__property int MaxConnections = {read=FMaxConns, write=SetMaxConns, default=20};
	__property unsigned TransactionIdleTimer = {read=FIdleTimer, write=FIdleTimer, nodefault};
	__property unsigned ExhaustedDelay = {read=FDelay, write=FDelay, default=500};
	__property TIBConnectionBrokerLogEvent OnLog = {read=FOnLog, write=FOnLog};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibconnectionbroker */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBCONNECTIONBROKER)
using namespace Ibx::Ibconnectionbroker;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbconnectionbrokerHPP
