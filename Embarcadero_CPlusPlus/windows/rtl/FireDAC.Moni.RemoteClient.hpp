// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Moni.RemoteClient.pas' rev: 34.00 (Windows)

#ifndef Firedac_Moni_RemoteclientHPP
#define Firedac_Moni_RemoteclientHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Consts.hpp>
#include <FireDAC.Moni.Base.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FireDAC.Moni.RemoteClient"

namespace Firedac
{
namespace Moni
{
namespace Remoteclient
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDMoniRemoteClientLink;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDMoniRemoteClientLink : public Firedac::Moni::Base::TFDMoniClientLinkBase
{
	typedef Firedac::Moni::Base::TFDMoniClientLinkBase inherited;
	
private:
	Firedac::Stan::Intf::_di_IFDMoniRemoteClient FRemoteClient;
	bool __fastcall IsHS();
	System::UnicodeString __fastcall GetHost();
	void __fastcall SetHost(const System::UnicodeString AValue);
	int __fastcall GetPort();
	void __fastcall SetPortI(const int AValue);
	int __fastcall GetTimeout();
	void __fastcall SetTimeout(const int AValue);
	
protected:
	virtual Firedac::Stan::Intf::_di_IFDMoniClient __fastcall GetMoniClient();
	
public:
	__fastcall virtual TFDMoniRemoteClientLink(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDMoniRemoteClientLink();
	__property Firedac::Stan::Intf::_di_IFDMoniRemoteClient RemoteClient = {read=FRemoteClient};
	
__published:
	__property System::UnicodeString Host = {read=GetHost, write=SetHost, stored=IsHS};
	__property int Port = {read=GetPort, write=SetPortI, default=8050};
	__property int Timeout = {read=GetTimeout, write=SetTimeout, default=3000};
	__property Tracing = {default=0};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Remoteclient */
}	/* namespace Moni */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_MONI_REMOTECLIENT)
using namespace Firedac::Moni::Remoteclient;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_MONI)
using namespace Firedac::Moni;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Moni_RemoteclientHPP
