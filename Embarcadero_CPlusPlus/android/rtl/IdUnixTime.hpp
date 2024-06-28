// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdUnixTime.pas' rev: 34.00 (Android)

#ifndef IdunixtimeHPP
#define IdunixtimeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdTCPClient.hpp>
#include <IdTime.hpp>
#include <IdTCPConnection.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idunixtime
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdUnixTime;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdUnixTime : public Idtime::TIdCustomTime
{
	typedef Idtime::TIdCustomTime inherited;
	
protected:
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdUnixTime(System::Classes::TComponent* AOwner)/* overload */;
	
__published:
	__property Port = {default=519};
public:
	/* TIdTCPConnection.Destroy */ inline __fastcall virtual ~TIdUnixTime() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdUnixTime()/* overload */ : Idtime::TIdCustomTime() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idunixtime */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDUNIXTIME)
using namespace Idunixtime;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdunixtimeHPP
