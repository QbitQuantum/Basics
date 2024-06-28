// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdAuthenticationNTLM.pas' rev: 34.00 (iOS)

#ifndef IdauthenticationntlmHPP
#define IdauthenticationntlmHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAuthentication.hpp>

//-- user supplied -----------------------------------------------------------
namespace Idauthenticationntlm
{
  _INIT_UNIT(Idauthenticationntlm);
}	/* namespace Idauthenticationntlm */

namespace Idauthenticationntlm
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdNTLMAuthentication;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdNTLMAuthentication : public Idauthentication::TIdAuthentication
{
	typedef Idauthentication::TIdAuthentication inherited;
	
protected:
	System::UnicodeString FNTLMInfo;
	System::UnicodeString FHost;
	System::UnicodeString FDomain;
	System::UnicodeString FUser;
	virtual Idauthentication::TIdAuthWhatsNext __fastcall DoNext();
	virtual int __fastcall GetSteps();
	virtual void __fastcall SetUserName(const System::UnicodeString Value);
	
public:
	__fastcall virtual TIdNTLMAuthentication();
	virtual System::UnicodeString __fastcall Authentication();
	virtual bool __fastcall KeepAlive();
public:
	/* TIdAuthentication.Destroy */ inline __fastcall virtual ~TIdNTLMAuthentication() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idauthenticationntlm */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDAUTHENTICATIONNTLM)
using namespace Idauthenticationntlm;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdauthenticationntlmHPP
