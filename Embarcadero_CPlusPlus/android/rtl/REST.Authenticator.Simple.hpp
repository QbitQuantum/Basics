// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Authenticator.Simple.pas' rev: 34.00 (Android)

#ifndef Rest_Authenticator_SimpleHPP
#define Rest_Authenticator_SimpleHPP

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
#include <REST.Client.hpp>
#include <REST.Consts.hpp>
#include <REST.BindSource.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Authenticator
{
namespace Simple
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSimpleAuthenticator;
class DELPHICLASS TSubSimpleAuthenticationBindSource;
class DELPHICLASS TSimpleAuthenticatorAdapter;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TSimpleAuthenticator : public Rest::Client::TCustomAuthenticator
{
	typedef Rest::Client::TCustomAuthenticator inherited;
	
private:
	TSubSimpleAuthenticationBindSource* FBindSource;
	System::UnicodeString FUsernameKey;
	System::UnicodeString FUsername;
	System::UnicodeString FPasswordKey;
	System::UnicodeString FPassword;
	void __fastcall SetPassword(const System::UnicodeString AValue);
	void __fastcall SetPasswordKey(const System::UnicodeString AValue);
	void __fastcall SetUsername(const System::UnicodeString AValue);
	void __fastcall SetUsernameKey(const System::UnicodeString AValue);
	
protected:
	virtual void __fastcall DoAuthenticate(Rest::Client::TCustomRESTRequest* ARequest);
	virtual Data::Bind::Objectscope::TBaseObjectBindSource* __fastcall CreateBindSource();
	
public:
	__fastcall TSimpleAuthenticator(const System::UnicodeString AUsernameKey, const System::UnicodeString AUsername, const System::UnicodeString APasswordKey, const System::UnicodeString APassword)/* overload */;
	virtual void __fastcall ResetToDefaults();
	
__published:
	__property System::UnicodeString UsernameKey = {read=FUsernameKey, write=SetUsernameKey};
	__property System::UnicodeString Username = {read=FUsername, write=SetUsername};
	__property System::UnicodeString PasswordKey = {read=FPasswordKey, write=SetPasswordKey};
	__property System::UnicodeString Password = {read=FPassword, write=SetPassword};
	__property TSubSimpleAuthenticationBindSource* BindSource = {read=FBindSource};
public:
	/* TCustomAuthenticator.Destroy */ inline __fastcall virtual ~TSimpleAuthenticator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TSubSimpleAuthenticationBindSource : public Rest::Client::TRESTAuthenticatorBindSource__1<TSimpleAuthenticator*>
{
	typedef Rest::Client::TRESTAuthenticatorBindSource__1<TSimpleAuthenticator*> inherited;
	
protected:
	virtual Rest::Client::TRESTAuthenticatorAdapter__1<TSimpleAuthenticator*>* __fastcall CreateAdapterT();
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TSubSimpleAuthenticationBindSource(System::Classes::TComponent* AOwner) : Rest::Client::TRESTAuthenticatorBindSource__1<TSimpleAuthenticator*>(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TSubSimpleAuthenticationBindSource() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TSimpleAuthenticatorAdapter : public Rest::Client::TRESTAuthenticatorAdapter__1<TSimpleAuthenticator*>
{
	typedef Rest::Client::TRESTAuthenticatorAdapter__1<TSimpleAuthenticator*> inherited;
	
protected:
	virtual void __fastcall AddFields();
public:
	/* {REST_Client}TRESTAuthenticatorAdapter<REST_Authenticator_Simple_TSimpleAuthenticator>.Create */ inline __fastcall virtual TSimpleAuthenticatorAdapter(System::Classes::TComponent* AOwner) : Rest::Client::TRESTAuthenticatorAdapter__1<TSimpleAuthenticator*>(AOwner) { }
	/* {REST_Client}TRESTAuthenticatorAdapter<REST_Authenticator_Simple_TSimpleAuthenticator>.Destroy */ inline __fastcall virtual ~TSimpleAuthenticatorAdapter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Simple */
}	/* namespace Authenticator */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_AUTHENTICATOR_SIMPLE)
using namespace Rest::Authenticator::Simple;
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
#endif	// Rest_Authenticator_SimpleHPP
