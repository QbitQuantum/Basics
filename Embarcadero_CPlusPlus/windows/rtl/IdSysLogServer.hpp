// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSysLogServer.pas' rev: 34.00 (Windows)

#ifndef IdsyslogserverHPP
#define IdsyslogserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdGlobal.hpp>
#include <IdException.hpp>
#include <IdSocketHandle.hpp>
#include <IdStackConsts.hpp>
#include <IdThread.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPServer.hpp>
#include <IdSysLogMessage.hpp>
#include <IdSysLog.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsyslogserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSyslogServer;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TOnSyslogEvent)(System::TObject* Sender, Idsyslogmessage::TIdSysLogMessage* ASysLogMessage, Idsockethandle::TIdSocketHandle* ABinding);

class PASCALIMPLEMENTATION TIdSyslogServer : public Idudpserver::TIdUDPServer
{
	typedef Idudpserver::TIdUDPServer inherited;
	
protected:
	TOnSyslogEvent FOnSyslog;
	virtual void __fastcall DoSyslogEvent(Idsyslogmessage::TIdSysLogMessage* AMsg, Idsockethandle::TIdSocketHandle* ABinding);
	virtual void __fastcall DoUDPRead(Idudpserver::TIdUDPListenerThread* AThread, const Idglobal::TIdBytes AData, Idsockethandle::TIdSocketHandle* ABinding);
	virtual void __fastcall InitComponent();
	
__published:
	__property DefaultPort = {default=514};
	__property TOnSyslogEvent OnSyslog = {read=FOnSyslog, write=FOnSyslog};
public:
	/* TIdUDPServer.Destroy */ inline __fastcall virtual ~TIdSyslogServer() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSyslogServer(System::Classes::TComponent* AOwner)/* overload */ : Idudpserver::TIdUDPServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSyslogServer()/* overload */ : Idudpserver::TIdUDPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idsyslogserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSYSLOGSERVER)
using namespace Idsyslogserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsyslogserverHPP
