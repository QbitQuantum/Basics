// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSASLPlain.pas' rev: 34.00 (iOS)

#ifndef IdsaslplainHPP
#define IdsaslplainHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdSASL.hpp>
#include <IdSASLUserPass.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsaslplain
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSASLPlain;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdSASLPlain : public Idsasluserpass::TIdSASLUserPass
{
	typedef Idsasluserpass::TIdSASLUserPass inherited;
	
protected:
	System::UnicodeString FLoginAs;
	
public:
	virtual bool __fastcall IsReadyToStart();
	__classmethod virtual System::UnicodeString __fastcall ServiceName();
	virtual bool __fastcall TryStartAuthenticate(const System::UnicodeString AHost, const System::UnicodeString AProtocolName, System::UnicodeString &VInitialResponse);
	virtual System::UnicodeString __fastcall StartAuthenticate(const System::UnicodeString AChallenge, const System::UnicodeString AHost, const System::UnicodeString AProtocolName);
	
__published:
	__property System::UnicodeString LoginAs = {read=FLoginAs, write=FLoginAs};
public:
	/* TIdSASL.Destroy */ inline __fastcall virtual ~TIdSASLPlain() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSASLPlain(System::Classes::TComponent* AOwner)/* overload */ : Idsasluserpass::TIdSASLUserPass(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSASLPlain()/* overload */ : Idsasluserpass::TIdSASLUserPass() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idsaslplain */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSASLPLAIN)
using namespace Idsaslplain;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsaslplainHPP
