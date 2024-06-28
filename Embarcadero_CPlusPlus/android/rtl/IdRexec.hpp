// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdRexec.pas' rev: 34.00 (Android)

#ifndef IdrexecHPP
#define IdrexecHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdRemoteCMDClient.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idrexec
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdRexec;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdRexec : public Idremotecmdclient::TIdRemoteCMDClient
{
	typedef Idremotecmdclient::TIdRemoteCMDClient inherited;
	
protected:
	virtual void __fastcall InitComponent();
	
public:
	virtual System::UnicodeString __fastcall Execute(System::UnicodeString ACommand);
	
__published:
	__property Username = {default=0};
	__property Password = {default=0};
	__property Port = {default=512};
	__property Host = {default=0};
public:
	/* TIdRemoteCMDClient.Destroy */ inline __fastcall virtual ~TIdRexec() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdRexec(System::Classes::TComponent* AOwner)/* overload */ : Idremotecmdclient::TIdRemoteCMDClient(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdRexec()/* overload */ : Idremotecmdclient::TIdRemoteCMDClient() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idrexec */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDREXEC)
using namespace Idrexec;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdrexecHPP
