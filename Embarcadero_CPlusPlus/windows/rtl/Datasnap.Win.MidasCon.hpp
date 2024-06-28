// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.Win.MidasCon.pas' rev: 34.00 (Windows)

#ifndef Datasnap_Win_MidasconHPP
#define Datasnap_Win_MidasconHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Datasnap.Win.MConnect.hpp>
#include <Datasnap.Win.SConnect.hpp>
#include <Datasnap.DBClient.hpp>
#include <Data.DB.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Win
{
namespace Midascon
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TRemoteServer;
class DELPHICLASS TMidasConnection;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TRemoteServer : public Datasnap::Win::Mconnect::TDCOMConnection
{
	typedef Datasnap::Win::Mconnect::TDCOMConnection inherited;
	
public:
	/* TDCOMConnection.Create */ inline __fastcall virtual TRemoteServer(System::Classes::TComponent* AOwner) : Datasnap::Win::Mconnect::TDCOMConnection(AOwner) { }
	
public:
	/* TCustomConnection.Destroy */ inline __fastcall virtual ~TRemoteServer() { }
	
};


enum DECLSPEC_DENUM TConnectType : unsigned char { ctDCOM, ctSockets, ctOLEnterprise };

class PASCALIMPLEMENTATION TMidasConnection : public Datasnap::Win::Mconnect::TDCOMConnection
{
	typedef Datasnap::Win::Mconnect::TDCOMConnection inherited;
	
private:
	Datasnap::Win::Mconnect::TDispatchConnection* FSubConnection;
	TConnectType FConnectType;
	int FServerPort;
	bool FUseBroker;
	
protected:
	virtual void __fastcall SetConnectType(TConnectType Value);
	virtual void __fastcall SetUseBroker(bool Value);
	virtual void __fastcall DoConnect();
	virtual void __fastcall DoDisconnect();
	
public:
	__fastcall virtual TMidasConnection(System::Classes::TComponent* AOwner);
	
__published:
	__property TConnectType ConnectType = {read=FConnectType, write=SetConnectType, nodefault};
	__property int ServerPort = {read=FServerPort, write=FServerPort, default=211};
	__property bool UseBroker = {read=FUseBroker, write=SetUseBroker, nodefault};
public:
	/* TCustomConnection.Destroy */ inline __fastcall virtual ~TMidasConnection() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Midascon */
}	/* namespace Win */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_WIN_MIDASCON)
using namespace Datasnap::Win::Midascon;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_WIN)
using namespace Datasnap::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_Win_MidasconHPP
