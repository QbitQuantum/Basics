// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdConnectThroughHttpProxy.pas' rev: 34.00 (iOS)

#ifndef IdconnectthroughhttpproxyHPP
#define IdconnectthroughhttpproxyHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdCustomTransparentProxy.hpp>
#include <IdGlobal.hpp>
#include <IdIOHandler.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idconnectthroughhttpproxy
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdConnectThroughHttpProxy;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdConnectThroughHttpProxy : public Idcustomtransparentproxy::TIdCustomTransparentProxy
{
	typedef Idcustomtransparentproxy::TIdCustomTransparentProxy inherited;
	
private:
	bool FAuthorizationRequired;
	
protected:
	bool FEnabled;
	virtual bool __fastcall GetEnabled();
	virtual void __fastcall SetEnabled(bool AValue);
	virtual void __fastcall MakeConnection(Idiohandler::TIdIOHandler* AIOHandler, const System::UnicodeString AHost, const System::Word APort, const Idglobal::TIdIPVersion AIPVersion = (Idglobal::TIdIPVersion)(0x0));
	virtual void __fastcall DoMakeConnection(Idiohandler::TIdIOHandler* AIOHandler, const System::UnicodeString AHost, const System::Word APort, const bool ALogin, const Idglobal::TIdIPVersion AIPVersion = (Idglobal::TIdIPVersion)(0x0));
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* ASource);
	
__published:
	__property Enabled;
	__property Host = {default=0};
	__property Port;
	__property ChainedProxy;
	__property Username = {default=0};
	__property Password = {default=0};
public:
	/* TIdComponent.Destroy */ inline __fastcall virtual ~TIdConnectThroughHttpProxy() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdConnectThroughHttpProxy(System::Classes::TComponent* AOwner)/* overload */ : Idcustomtransparentproxy::TIdCustomTransparentProxy(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdConnectThroughHttpProxy()/* overload */ : Idcustomtransparentproxy::TIdCustomTransparentProxy() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idconnectthroughhttpproxy */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDCONNECTTHROUGHHTTPPROXY)
using namespace Idconnectthroughhttpproxy;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdconnectthroughhttpproxyHPP
