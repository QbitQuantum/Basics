// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSysLog.pas' rev: 34.00 (Windows)

#ifndef IdsyslogHPP
#define IdsyslogHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdSocketHandle.hpp>
#include <IdSysLogMessage.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPClient.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsyslog
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSysLog;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdSysLog : public Idudpclient::TIdUDPClient
{
	typedef Idudpclient::TIdUDPClient inherited;
	
protected:
	virtual Idsockethandle::TIdSocketHandle* __fastcall GetBinding();
	virtual void __fastcall InitComponent();
	
public:
	void __fastcall SendLogMessage(Idsyslogmessage::TIdSysLogMessage* const AMsg, const bool AAutoTimeStamp = true)/* overload */;
	void __fastcall SendLogMessage(const System::UnicodeString AMsg, const Idsyslogmessage::TIdSyslogFacility AFacility, const Idsyslogmessage::TIdSyslogSeverity ASeverity)/* overload */;
	void __fastcall SendLogMessage(const System::UnicodeString AProcess, const System::UnicodeString AText, const Idsyslogmessage::TIdSyslogFacility AFacility, const Idsyslogmessage::TIdSyslogSeverity ASeverity, const bool AUsePID = false, const int APID = 0xffffffff)/* overload */;
	
__published:
	__property Port = {default=514};
public:
	/* TIdUDPClient.Destroy */ inline __fastcall virtual ~TIdSysLog() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSysLog(System::Classes::TComponent* AOwner)/* overload */ : Idudpclient::TIdUDPClient(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSysLog()/* overload */ : Idudpclient::TIdUDPClient() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idsyslog */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSYSLOG)
using namespace Idsyslog;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsyslogHPP
