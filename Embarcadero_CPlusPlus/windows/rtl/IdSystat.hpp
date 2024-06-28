// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSystat.pas' rev: 34.00 (Windows)

#ifndef IdsystatHPP
#define IdsystatHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdTCPConnection.hpp>
#include <IdTCPClient.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsystat
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSystat;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdSystat : public Idtcpclient::TIdTCPClientCustom
{
	typedef Idtcpclient::TIdTCPClientCustom inherited;
	
protected:
	virtual void __fastcall InitComponent();
	
public:
	void __fastcall GetStat(System::Classes::TStrings* ADest);
	
__published:
	__property Port = {default=11};
public:
	/* TIdTCPConnection.Destroy */ inline __fastcall virtual ~TIdSystat() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSystat(System::Classes::TComponent* AOwner)/* overload */ : Idtcpclient::TIdTCPClientCustom(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSystat()/* overload */ : Idtcpclient::TIdTCPClientCustom() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idsystat */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSYSTAT)
using namespace Idsystat;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsystatHPP
