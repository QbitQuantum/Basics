// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSASLAnonymous.pas' rev: 34.00 (Android)

#ifndef IdsaslanonymousHPP
#define IdsaslanonymousHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdSASL.hpp>
#include <IdTCPConnection.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsaslanonymous
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSASLAnonymous;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdSASLAnonymous : public Idsasl::TIdSASL
{
	typedef Idsasl::TIdSASL inherited;
	
protected:
	System::UnicodeString FTraceInfo;
	virtual void __fastcall InitComponent();
	
public:
	virtual bool __fastcall IsReadyToStart();
	__classmethod virtual System::UnicodeString __fastcall ServiceName();
	virtual bool __fastcall TryStartAuthenticate(const System::UnicodeString AHost, const System::UnicodeString AProtocolName, System::UnicodeString &VInitialResponse);
	virtual System::UnicodeString __fastcall StartAuthenticate(const System::UnicodeString AChallenge, const System::UnicodeString AHost, const System::UnicodeString AProtocolName);
	
__published:
	__property System::UnicodeString TraceInfo = {read=FTraceInfo, write=FTraceInfo};
public:
	/* TIdSASL.Destroy */ inline __fastcall virtual ~TIdSASLAnonymous() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSASLAnonymous(System::Classes::TComponent* AOwner)/* overload */ : Idsasl::TIdSASL(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSASLAnonymous()/* overload */ : Idsasl::TIdSASL() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idsaslanonymous */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSASLANONYMOUS)
using namespace Idsaslanonymous;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsaslanonymousHPP
