// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSASL.pas' rev: 34.00 (Android)

#ifndef IdsaslHPP
#define IdsaslHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>
#include <IdBaseComponent.hpp>
#include <IdTCPConnection.hpp>
#include <IdException.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsasl
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSASL;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIdSASLResult : unsigned char { srSuccess, srFailure, srAborted };

typedef System::UnicodeString TIdSASLServiceName;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdSASL : public Idbasecomponent::TIdBaseComponent
{
	typedef Idbasecomponent::TIdBaseComponent inherited;
	
protected:
	unsigned FSecurityLevel;
	unsigned __fastcall GetSecurityLevel();
	virtual void __fastcall InitComponent();
	
public:
	__fastcall virtual ~TIdSASL();
	virtual bool __fastcall TryStartAuthenticate(const System::UnicodeString AHost, const System::UnicodeString AProtocolName, System::UnicodeString &VInitialResponse);
	virtual System::UnicodeString __fastcall StartAuthenticate(const System::UnicodeString AChallenge, const System::UnicodeString AHost, const System::UnicodeString AProtocolName) = 0 ;
	virtual System::UnicodeString __fastcall ContinueAuthenticate(const System::UnicodeString ALastResponse, const System::UnicodeString AHost, const System::UnicodeString AProtocolName);
	virtual void __fastcall FinishAuthenticate();
	virtual bool __fastcall IsReadyToStart();
	virtual bool __fastcall IsAuthProtocolAvailable(System::Classes::TStrings* AFeatStrings);
	__property unsigned SecurityLevel = {read=GetSecurityLevel, nodefault};
	__classmethod virtual System::UnicodeString __fastcall ServiceName();
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSASL(System::Classes::TComponent* AOwner)/* overload */ : Idbasecomponent::TIdBaseComponent(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSASL()/* overload */ : Idbasecomponent::TIdBaseComponent() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::Classes::TThreadList* GlobalSASLList;
}	/* namespace Idsasl */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSASL)
using namespace Idsasl;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsaslHPP
