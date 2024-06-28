// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFingerServer.pas' rev: 34.00 (Windows)

#ifndef IdfingerserverHPP
#define IdfingerserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdContext.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idfingerserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdFingerServer;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TIdFingerGetEvent)(Idcontext::TIdContext* AContext, const System::UnicodeString AUserName, System::UnicodeString &VResponse);

class PASCALIMPLEMENTATION TIdFingerServer : public Idcustomtcpserver::TIdCustomTCPServer
{
	typedef Idcustomtcpserver::TIdCustomTCPServer inherited;
	
protected:
	TIdFingerGetEvent FOnCommandFinger;
	TIdFingerGetEvent FOnCommandVerboseFinger;
	virtual bool __fastcall DoExecute(Idcontext::TIdContext* AContext);
	virtual void __fastcall InitComponent();
	
__published:
	__property TIdFingerGetEvent OnCommandFinger = {read=FOnCommandFinger, write=FOnCommandFinger};
	__property TIdFingerGetEvent OnCommandVerboseFinger = {read=FOnCommandVerboseFinger, write=FOnCommandVerboseFinger};
	__property DefaultPort = {default=79};
public:
	/* TIdCustomTCPServer.Destroy */ inline __fastcall virtual ~TIdFingerServer() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdFingerServer(System::Classes::TComponent* AOwner)/* overload */ : Idcustomtcpserver::TIdCustomTCPServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdFingerServer()/* overload */ : Idcustomtcpserver::TIdCustomTCPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idfingerserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFINGERSERVER)
using namespace Idfingerserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdfingerserverHPP
