// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Authenticator.Basic.pas' rev: 34.00 (Android)

#ifndef Rest_Authenticator_BasicHPP
#define Rest_Authenticator_BasicHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <Data.Bind.Components.hpp>
#include <REST.Types.hpp>
#include <REST.Consts.hpp>
#include <REST.Client.hpp>
#include <REST.Utils.hpp>
#include <REST.BindSource.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Authenticator
{
namespace Basic
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS THTTPBasicAuthenticator;
class DELPHICLASS TSubHTTPBasicAuthenticationBindSource;
class DELPHICLASS THTTPBasicAuthenticatorAdapter;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION THTTPBasicAuthenticator : public Rest::Client::TCustomAuthenticator
{
	typedef Rest::Client::TCustomAuthenticator inherited;
	
protected:
	TSubHTTPBasicAuthenticationBindSource* FBindSource;
	virtual Data::Bind::Objectscope::TBaseObjectBindSource* __fastcall CreateBindSource();
	
private:
	System::UnicodeString FUsername;
	System::UnicodeString FPassword;
	
protected:
	virtual void __fastcall SetPassword(const System::UnicodeString AValue);
	virtual void __fastcall SetUsername(const System::UnicodeString AValue);
	virtual void __fastcall DoAuthenticate(Rest::Client::TCustomRESTRequest* ARequest);
	
public:
	__fastcall THTTPBasicAuthenticator(const System::UnicodeString AUsername, const System::UnicodeString APassword)/* overload */;
	virtual void __fastcall ResetToDefaults();
	
__published:
	__property System::UnicodeString Username = {read=FUsername, write=SetUsername};
	__property System::UnicodeString Password = {read=FPassword, write=SetPassword};
	__property TSubHTTPBasicAuthenticationBindSource* BindSource = {read=FBindSource};
public:
	/* TCustomAuthenticator.Destroy */ inline __fastcall virtual ~THTTPBasicAuthenticator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TSubHTTPBasicAuthenticationBindSource : public Rest::Client::TRESTAuthenticatorBindSource__1<THTTPBasicAuthenticator*>
{
	typedef Rest::Client::TRESTAuthenticatorBindSource__1<THTTPBasicAuthenticator*> inherited;
	
protected:
	virtual Rest::Client::TRESTAuthenticatorAdapter__1<THTTPBasicAuthenticator*>* __fastcall CreateAdapterT();
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TSubHTTPBasicAuthenticationBindSource(System::Classes::TComponent* AOwner) : Rest::Client::TRESTAuthenticatorBindSource__1<THTTPBasicAuthenticator*>(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TSubHTTPBasicAuthenticationBindSource() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION THTTPBasicAuthenticatorAdapter : public Rest::Client::TRESTAuthenticatorAdapter__1<THTTPBasicAuthenticator*>
{
	typedef Rest::Client::TRESTAuthenticatorAdapter__1<THTTPBasicAuthenticator*> inherited;
	
protected:
	virtual void __fastcall AddFields();
public:
	/* {REST_Client}TRESTAuthenticatorAdapter<REST_Authenticator_Basic_THTTPBasicAuthenticator>.Create */ inline __fastcall virtual THTTPBasicAuthenticatorAdapter(System::Classes::TComponent* AOwner) : Rest::Client::TRESTAuthenticatorAdapter__1<THTTPBasicAuthenticator*>(AOwner) { }
	/* {REST_Client}TRESTAuthenticatorAdapter<REST_Authenticator_Basic_THTTPBasicAuthenticator>.Destroy */ inline __fastcall virtual ~THTTPBasicAuthenticatorAdapter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Basic */
}	/* namespace Authenticator */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_AUTHENTICATOR_BASIC)
using namespace Rest::Authenticator::Basic;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_AUTHENTICATOR)
using namespace Rest::Authenticator;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST)
using namespace Rest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Rest_Authenticator_BasicHPP
