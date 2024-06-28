// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSASLOTP.pas' rev: 34.00 (iOS)

#ifndef IdsaslotpHPP
#define IdsaslotpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdException.hpp>
#include <IdSASL.hpp>
#include <IdSASLUserPass.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsaslotp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSASLOTP;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdSASLOTP : public Idsasluserpass::TIdSASLUserPass
{
	typedef Idsasluserpass::TIdSASLUserPass inherited;
	
protected:
	System::UnicodeString __fastcall GenerateOTP(const System::UnicodeString AResponse, const System::UnicodeString APassword);
	virtual void __fastcall InitComponent();
	
public:
	__classmethod virtual System::UnicodeString __fastcall ServiceName();
	virtual bool __fastcall TryStartAuthenticate(const System::UnicodeString AHost, const System::UnicodeString AProtocolName, System::UnicodeString &VInitialResponse);
	virtual System::UnicodeString __fastcall StartAuthenticate(const System::UnicodeString AChallenge, const System::UnicodeString AHost, const System::UnicodeString AProtocolName);
	virtual System::UnicodeString __fastcall ContinueAuthenticate(const System::UnicodeString ALastResponse, const System::UnicodeString AHost, const System::UnicodeString AProtocolName);
public:
	/* TIdSASL.Destroy */ inline __fastcall virtual ~TIdSASLOTP() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSASLOTP(System::Classes::TComponent* AOwner)/* overload */ : Idsasluserpass::TIdSASLUserPass(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSASLOTP()/* overload */ : Idsasluserpass::TIdSASLUserPass() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idsaslotp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSASLOTP)
using namespace Idsaslotp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsaslotpHPP
