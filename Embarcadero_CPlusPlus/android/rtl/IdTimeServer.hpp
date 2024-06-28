// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdTimeServer.pas' rev: 34.00 (Android)

#ifndef IdtimeserverHPP
#define IdtimeserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdContext.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idtimeserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdCustomTimeServer;
class DELPHICLASS TIdTimeServer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdCustomTimeServer : public Idcustomtcpserver::TIdCustomTCPServer
{
	typedef Idcustomtcpserver::TIdCustomTCPServer inherited;
	
protected:
	System::TDateTime FBaseDate;
	virtual bool __fastcall DoExecute(Idcontext::TIdContext* AContext);
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdCustomTimeServer(System::Classes::TComponent* AOwner)/* overload */;
public:
	/* TIdCustomTCPServer.Destroy */ inline __fastcall virtual ~TIdCustomTimeServer() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdCustomTimeServer()/* overload */ : Idcustomtcpserver::TIdCustomTCPServer() { }
	
};


class PASCALIMPLEMENTATION TIdTimeServer : public TIdCustomTimeServer
{
	typedef TIdCustomTimeServer inherited;
	
__published:
	__property DefaultPort = {default=37};
	__property System::TDateTime BaseDate = {read=FBaseDate, write=FBaseDate};
public:
	/* TIdCustomTimeServer.Create */ inline __fastcall TIdTimeServer(System::Classes::TComponent* AOwner)/* overload */ : TIdCustomTimeServer(AOwner) { }
	
public:
	/* TIdCustomTCPServer.Destroy */ inline __fastcall virtual ~TIdTimeServer() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdTimeServer()/* overload */ : TIdCustomTimeServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idtimeserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDTIMESERVER)
using namespace Idtimeserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdtimeserverHPP
