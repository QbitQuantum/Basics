// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSASL_CRAM_SHA1.pas' rev: 34.00 (iOS)

#ifndef Idsasl_cram_sha1HPP
#define Idsasl_cram_sha1HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdSASL.hpp>
#include <IdSASL_CRAMBase.hpp>
#include <IdSASLUserPass.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsasl_cram_sha1
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSASLCRAMSHA1;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdSASLCRAMSHA1 : public Idsasl_crambase::TIdSASLCRAMBase
{
	typedef Idsasl_crambase::TIdSASLCRAMBase inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall BuildKeydAuth(const System::UnicodeString APassword, const System::UnicodeString AChallenge);
	__classmethod virtual System::UnicodeString __fastcall ServiceName();
public:
	/* TIdSASL.Destroy */ inline __fastcall virtual ~TIdSASLCRAMSHA1() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSASLCRAMSHA1(System::Classes::TComponent* AOwner)/* overload */ : Idsasl_crambase::TIdSASLCRAMBase(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSASLCRAMSHA1()/* overload */ : Idsasl_crambase::TIdSASLCRAMBase() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idsasl_cram_sha1 */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSASL_CRAM_SHA1)
using namespace Idsasl_cram_sha1;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Idsasl_cram_sha1HPP
