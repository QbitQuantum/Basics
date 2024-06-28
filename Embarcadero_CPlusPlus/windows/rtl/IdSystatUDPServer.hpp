// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSystatUDPServer.pas' rev: 34.00 (Windows)

#ifndef IdsystatudpserverHPP
#define IdsystatudpserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdGlobal.hpp>
#include <IdSocketHandle.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPServer.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsystatudpserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSystatUDPServer;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TIdUDPSystatEvent)(Idsockethandle::TIdSocketHandle* ABinding, System::Classes::TStrings* AResults);

class PASCALIMPLEMENTATION TIdSystatUDPServer : public Idudpserver::TIdUDPServer
{
	typedef Idudpserver::TIdUDPServer inherited;
	
protected:
	TIdUDPSystatEvent FOnSystat;
	virtual void __fastcall DoUDPRead(Idudpserver::TIdUDPListenerThread* AThread, const Idglobal::TIdBytes AData, Idsockethandle::TIdSocketHandle* ABinding);
	virtual void __fastcall InitComponent();
	
__published:
	__property TIdUDPSystatEvent OnSystat = {read=FOnSystat, write=FOnSystat};
	__property DefaultPort = {default=11};
public:
	/* TIdUDPServer.Destroy */ inline __fastcall virtual ~TIdSystatUDPServer() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSystatUDPServer(System::Classes::TComponent* AOwner)/* overload */ : Idudpserver::TIdUDPServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSystatUDPServer()/* overload */ : Idudpserver::TIdUDPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idsystatudpserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSYSTATUDPSERVER)
using namespace Idsystatudpserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsystatudpserverHPP
