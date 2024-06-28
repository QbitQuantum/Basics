// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdServerInterceptLogEvent.pas' rev: 34.00 (Android)

#ifndef IdserverinterceptlogeventHPP
#define IdserverinterceptlogeventHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdServerInterceptLogBase.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idserverinterceptlogevent
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdServerInterceptLogEvent;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TIdOnLogString)(TIdServerInterceptLogEvent* ASender, const System::UnicodeString AText);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdServerInterceptLogEvent : public Idserverinterceptlogbase::TIdServerInterceptLogBase
{
	typedef Idserverinterceptlogbase::TIdServerInterceptLogBase inherited;
	
protected:
	TIdOnLogString FOnLogString;
	
public:
	virtual void __fastcall DoLogWriteString(const System::UnicodeString AText);
	
__published:
	__property TIdOnLogString OnLogString = {read=FOnLogString, write=FOnLogString};
public:
	/* TIdServerInterceptLogBase.Destroy */ inline __fastcall virtual ~TIdServerInterceptLogEvent() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdServerInterceptLogEvent(System::Classes::TComponent* AOwner)/* overload */ : Idserverinterceptlogbase::TIdServerInterceptLogBase(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdServerInterceptLogEvent()/* overload */ : Idserverinterceptlogbase::TIdServerInterceptLogBase() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idserverinterceptlogevent */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSERVERINTERCEPTLOGEVENT)
using namespace Idserverinterceptlogevent;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdserverinterceptlogeventHPP
