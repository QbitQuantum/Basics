// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Authenticator.OAuth.pas' rev: 34.00 (iOS)

#ifndef Rest_Authenticator_OauthHPP
#define Rest_Authenticator_OauthHPP

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
#include <REST.Client.hpp>
#include <REST.Types.hpp>
#include <REST.Consts.hpp>
#include <REST.Utils.hpp>
#include <REST.BindSource.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------
namespace Rest
{
namespace Authenticator
{
namespace Oauth
{
  _INIT_UNIT(Rest_Authenticator_Oauth);
}	/* namespace Oauth */
}	/* namespace Authenticator */
}	/* namespace Rest */

namespace Rest
{
namespace Authenticator
{
namespace Oauth
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TOAuth1SignatureMethod;
class DELPHICLASS TOAuth1SignatureMethod_PLAINTEXT;
class DELPHICLASS TOAuth1SignatureMethod_HMAC_SHA1;
class DELPHICLASS TOAuth1Authenticator;
class DELPHICLASS TSubOAuth1AuthenticationBindSource;
class DELPHICLASS TOAuth1AuthenticatorAdapter;
class DELPHICLASS EOAuth2Exception;
class DELPHICLASS TOAuth2Authenticator;
class DELPHICLASS TSubOAuth2AuthenticationBindSource;
class DELPHICLASS TOAuth2AuthenticatorAdapter;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TOAuth1SignatureMethod : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
public:
	virtual __classmethod System::UnicodeString __fastcall GetName() = 0 ;
	virtual System::UnicodeString __fastcall BuildSignature(Rest::Client::TCustomRESTRequest* ARequest, TOAuth1Authenticator* AAuthenticator) = 0 ;
	__property System::UnicodeString Name = {read=GetName};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TOAuth1SignatureMethod() { }
	
public:
	/* TObject.Create */ inline __fastcall TOAuth1SignatureMethod() : System::Classes::TPersistent() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TOAuth1SignatureMethodClass);

class PASCALIMPLEMENTATION TOAuth1SignatureMethod_PLAINTEXT : public TOAuth1SignatureMethod
{
	typedef TOAuth1SignatureMethod inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetName();
	virtual System::UnicodeString __fastcall BuildSignature(Rest::Client::TCustomRESTRequest* ARequest, TOAuth1Authenticator* AAuthenticator);
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TOAuth1SignatureMethod_PLAINTEXT() { }
	
public:
	/* TObject.Create */ inline __fastcall TOAuth1SignatureMethod_PLAINTEXT() : TOAuth1SignatureMethod() { }
	
};


class PASCALIMPLEMENTATION TOAuth1SignatureMethod_HMAC_SHA1 : public TOAuth1SignatureMethod
{
	typedef TOAuth1SignatureMethod inherited;
	
protected:
	virtual System::UnicodeString __fastcall Hash_HMAC_SHA1(const System::UnicodeString AData, const System::UnicodeString AKey);
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetName();
	virtual System::UnicodeString __fastcall BuildSignature(Rest::Client::TCustomRESTRequest* ARequest, TOAuth1Authenticator* AAuthenticator);
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TOAuth1SignatureMethod_HMAC_SHA1() { }
	
public:
	/* TObject.Create */ inline __fastcall TOAuth1SignatureMethod_HMAC_SHA1() : TOAuth1SignatureMethod() { }
	
};


class PASCALIMPLEMENTATION TOAuth1Authenticator : public Rest::Client::TCustomAuthenticator
{
	typedef Rest::Client::TCustomAuthenticator inherited;
	
private:
	System::UnicodeString FNonce;
	TOAuth1SignatureMethod* FSigningClass;
	System::UnicodeString FSigningClassName;
	TSubOAuth1AuthenticationBindSource* FBindSource;
	System::UnicodeString FTimestamp;
	System::UnicodeString FVersion;
	System::UnicodeString FAccessToken;
	System::UnicodeString FAccessTokenSecret;
	System::UnicodeString FAccessTokenEndpoint;
	System::UnicodeString FRequestTokenEndpoint;
	System::UnicodeString FAuthenticationEndpoint;
	System::UnicodeString FCallbackEndpoint;
	System::UnicodeString FConsumerKey;
	System::UnicodeString FConsumerSecret;
	System::UnicodeString FVerifierPIN;
	System::UnicodeString FRequestToken;
	System::UnicodeString FRequestTokenSecret;
	System::UnicodeString FIPImplementationID;
	void __fastcall ReadConsumerSecret(System::Classes::TReader* Reader);
	void __fastcall SetSigningClassName(const System::UnicodeString AValue);
	void __fastcall SetSigningClass(TOAuth1SignatureMethod* const AValue);
	void __fastcall SetAccessToken(const System::UnicodeString AValue);
	void __fastcall SetAccessTokenEndpoint(const System::UnicodeString AValue);
	void __fastcall SetAccessTokenSecret(const System::UnicodeString AValue);
	void __fastcall SetAuthenticationEndpoint(const System::UnicodeString AValue);
	void __fastcall SetCallbackEndpoint(const System::UnicodeString AValue);
	void __fastcall SetConsumerSecret(const System::UnicodeString AValue);
	void __fastcall SetConsumerKey(const System::UnicodeString AValue);
	void __fastcall SetRequestToken(const System::UnicodeString AValue);
	void __fastcall SetRequestTokenEndpoint(const System::UnicodeString AValue);
	void __fastcall SetRequestTokenSecret(const System::UnicodeString AValue);
	void __fastcall SetVerifierPIN(const System::UnicodeString AValue);
	bool __fastcall SigningClassNameIsStored();
	void __fastcall WriteConsumerSecret(System::Classes::TWriter* Writer);
	void __fastcall AddCommonAuthParameters(System::Classes::TStrings* const Params, const System::UnicodeString QuoteChar);
	
protected:
	virtual Data::Bind::Objectscope::TBaseObjectBindSource* __fastcall CreateBindSource();
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall DoAuthenticate(Rest::Client::TCustomRESTRequest* ARequest);
	__classmethod virtual System::UnicodeString __fastcall GenerateNonce();
	virtual System::UnicodeString __fastcall GenerateSignature(Rest::Client::TCustomRESTRequest* ARequest);
	__classmethod virtual System::UnicodeString __fastcall GenerateTimeStamp();
	virtual System::UnicodeString __fastcall GetSignatureMethod();
	
public:
	__fastcall virtual TOAuth1Authenticator(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TOAuth1Authenticator();
	HIDESBASE void __fastcall Assign(TOAuth1Authenticator* ASource);
	virtual void __fastcall ResetToDefaults();
	__property System::UnicodeString Nonce = {read=FNonce};
	__property System::UnicodeString SignatureMethod = {read=GetSignatureMethod};
	__property System::UnicodeString Timestamp = {read=FTimestamp};
	__property System::UnicodeString Version = {read=FVersion};
	__property TOAuth1SignatureMethod* SigningClass = {read=FSigningClass, write=SetSigningClass};
	
__published:
	__property System::UnicodeString AccessToken = {read=FAccessToken, write=SetAccessToken};
	__property System::UnicodeString AccessTokenSecret = {read=FAccessTokenSecret, write=SetAccessTokenSecret};
	__property System::UnicodeString RequestToken = {read=FRequestToken, write=SetRequestToken};
	__property System::UnicodeString RequestTokenSecret = {read=FRequestTokenSecret, write=SetRequestTokenSecret};
	__property System::UnicodeString AccessTokenEndpoint = {read=FAccessTokenEndpoint, write=SetAccessTokenEndpoint};
	__property System::UnicodeString RequestTokenEndpoint = {read=FRequestTokenEndpoint, write=SetRequestTokenEndpoint};
	__property System::UnicodeString AuthenticationEndpoint = {read=FAuthenticationEndpoint, write=SetAuthenticationEndpoint};
	__property System::UnicodeString CallbackEndpoint = {read=FCallbackEndpoint, write=SetCallbackEndpoint};
	__property System::UnicodeString ConsumerKey = {read=FConsumerKey, write=SetConsumerKey};
	__property System::UnicodeString ConsumerSecret = {read=FConsumerSecret, write=SetConsumerSecret};
	__property System::UnicodeString SigningClassName = {read=FSigningClassName, write=SetSigningClassName, stored=SigningClassNameIsStored};
	__property System::UnicodeString VerifierPIN = {read=FVerifierPIN, write=SetVerifierPIN};
	__property System::UnicodeString IPImplementationID = {read=FIPImplementationID, write=FIPImplementationID};
	__property TSubOAuth1AuthenticationBindSource* BindSource = {read=FBindSource};
};


class PASCALIMPLEMENTATION TSubOAuth1AuthenticationBindSource : public Rest::Client::TRESTAuthenticatorBindSource__1<TOAuth1Authenticator*>
{
	typedef Rest::Client::TRESTAuthenticatorBindSource__1<TOAuth1Authenticator*> inherited;
	
protected:
	virtual Rest::Client::TRESTAuthenticatorAdapter__1<TOAuth1Authenticator*>* __fastcall CreateAdapterT();
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TSubOAuth1AuthenticationBindSource(System::Classes::TComponent* AOwner) : Rest::Client::TRESTAuthenticatorBindSource__1<TOAuth1Authenticator*>(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TSubOAuth1AuthenticationBindSource() { }
	
};


class PASCALIMPLEMENTATION TOAuth1AuthenticatorAdapter : public Rest::Client::TRESTAuthenticatorAdapter__1<TOAuth1Authenticator*>
{
	typedef Rest::Client::TRESTAuthenticatorAdapter__1<TOAuth1Authenticator*> inherited;
	
protected:
	virtual void __fastcall AddFields();
public:
	/* {REST_Client}TRESTAuthenticatorAdapter<REST_Authenticator_OAuth_TOAuth1Authenticator>.Create */ inline __fastcall virtual TOAuth1AuthenticatorAdapter(System::Classes::TComponent* AOwner) : Rest::Client::TRESTAuthenticatorAdapter__1<TOAuth1Authenticator*>(AOwner) { }
	/* {REST_Client}TRESTAuthenticatorAdapter<REST_Authenticator_OAuth_TOAuth1Authenticator>.Destroy */ inline __fastcall virtual ~TOAuth1AuthenticatorAdapter() { }
	
};


enum class DECLSPEC_DENUM TOAuth2ResponseType : unsigned char { rtCODE, rtTOKEN };

enum class DECLSPEC_DENUM TOAuth2TokenType : unsigned char { ttNONE, ttBEARER };

class PASCALIMPLEMENTATION EOAuth2Exception : public Rest::Types::ERESTException
{
	typedef Rest::Types::ERESTException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EOAuth2Exception(const System::UnicodeString Msg) : Rest::Types::ERESTException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EOAuth2Exception(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Rest::Types::ERESTException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EOAuth2Exception(NativeUInt Ident)/* overload */ : Rest::Types::ERESTException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EOAuth2Exception(System::PResStringRec ResStringRec)/* overload */ : Rest::Types::ERESTException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EOAuth2Exception(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Rest::Types::ERESTException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EOAuth2Exception(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Rest::Types::ERESTException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EOAuth2Exception(const System::UnicodeString Msg, int AHelpContext) : Rest::Types::ERESTException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EOAuth2Exception(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Rest::Types::ERESTException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EOAuth2Exception(NativeUInt Ident, int AHelpContext)/* overload */ : Rest::Types::ERESTException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EOAuth2Exception(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Rest::Types::ERESTException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EOAuth2Exception(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Rest::Types::ERESTException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EOAuth2Exception(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Rest::Types::ERESTException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EOAuth2Exception() { }
	
};


typedef EOAuth2Exception TOAuth2Exception _DEPRECATED_ATTRIBUTE1("use EOAuth2Exception") ;

class PASCALIMPLEMENTATION TOAuth2Authenticator : public Rest::Client::TCustomAuthenticator
{
	typedef Rest::Client::TCustomAuthenticator inherited;
	
private:
	TSubOAuth2AuthenticationBindSource* FBindSource;
	System::UnicodeString FAccessToken;
	System::UnicodeString FAccessTokenEndpoint;
	System::TDateTime FAccessTokenExpiry;
	System::UnicodeString FAccessTokenParamName;
	System::UnicodeString FAuthCode;
	System::UnicodeString FAuthorizationEndpoint;
	System::UnicodeString FClientID;
	System::UnicodeString FClientSecret;
	System::UnicodeString FLocalState;
	System::UnicodeString FRedirectionEndpoint;
	System::UnicodeString FRefreshToken;
	TOAuth2ResponseType FResponseType;
	System::UnicodeString FScope;
	TOAuth2TokenType FTokenType;
	void __fastcall SetAccessTokenEndpoint(const System::UnicodeString AValue);
	void __fastcall SetAccessTokenParamName(const System::UnicodeString AValue);
	void __fastcall SetAuthCode(const System::UnicodeString AValue);
	void __fastcall SetAuthorizationEndpoint(const System::UnicodeString AValue);
	void __fastcall SetClientID(const System::UnicodeString AValue);
	void __fastcall SetClientSecret(const System::UnicodeString AValue);
	void __fastcall SetLocalState(const System::UnicodeString AValue);
	void __fastcall SetRedirectionEndpoint(const System::UnicodeString AValue);
	void __fastcall SetRefreshToken(const System::UnicodeString AValue);
	void __fastcall SetResponseType(const TOAuth2ResponseType AValue);
	void __fastcall SetScope(const System::UnicodeString AValue);
	bool __fastcall ResponseTypeIsStored();
	bool __fastcall TokenTypeIsStored();
	bool __fastcall AccessTokenParamNameIsStored();
	void __fastcall ReadAccessTokenExpiryData(System::Classes::TReader* AReader);
	void __fastcall SetAccessToken(const System::UnicodeString AValue);
	void __fastcall SetAccessTokenExpiry(const System::TDateTime AExpiry);
	void __fastcall SetTokenType(const TOAuth2TokenType AType);
	void __fastcall WriteAccessTokenExpiryData(System::Classes::TWriter* AWriter);
	
protected:
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall DoAuthenticate(Rest::Client::TCustomRESTRequest* ARequest);
	virtual Data::Bind::Objectscope::TBaseObjectBindSource* __fastcall CreateBindSource();
	
public:
	__fastcall virtual TOAuth2Authenticator(System::Classes::TComponent* AOwner);
	HIDESBASE void __fastcall Assign(TOAuth2Authenticator* ASource);
	System::UnicodeString __fastcall AuthorizationRequestURI();
	void __fastcall ChangeAuthCodeToAccesToken();
	virtual void __fastcall ResetToDefaults();
	
__published:
	__property System::UnicodeString AccessToken = {read=FAccessToken, write=SetAccessToken};
	__property System::UnicodeString AccessTokenEndpoint = {read=FAccessTokenEndpoint, write=SetAccessTokenEndpoint};
	__property System::TDateTime AccessTokenExpiry = {read=FAccessTokenExpiry, write=SetAccessTokenExpiry};
	__property System::UnicodeString AccessTokenParamName = {read=FAccessTokenParamName, write=SetAccessTokenParamName, stored=AccessTokenParamNameIsStored};
	__property System::UnicodeString AuthCode = {read=FAuthCode, write=SetAuthCode};
	__property System::UnicodeString AuthorizationEndpoint = {read=FAuthorizationEndpoint, write=SetAuthorizationEndpoint};
	__property System::UnicodeString ClientID = {read=FClientID, write=SetClientID};
	__property System::UnicodeString ClientSecret = {read=FClientSecret, write=SetClientSecret};
	__property System::UnicodeString LocalState = {read=FLocalState, write=SetLocalState};
	__property System::UnicodeString RedirectionEndpoint = {read=FRedirectionEndpoint, write=SetRedirectionEndpoint};
	__property System::UnicodeString RefreshToken = {read=FRefreshToken, write=SetRefreshToken};
	__property TOAuth2ResponseType ResponseType = {read=FResponseType, write=SetResponseType, stored=ResponseTypeIsStored, nodefault};
	__property System::UnicodeString Scope = {read=FScope, write=SetScope};
	__property TOAuth2TokenType TokenType = {read=FTokenType, write=SetTokenType, stored=TokenTypeIsStored, nodefault};
	__property TSubOAuth2AuthenticationBindSource* BindSource = {read=FBindSource};
public:
	/* TCustomAuthenticator.Destroy */ inline __fastcall virtual ~TOAuth2Authenticator() { }
	
};


class PASCALIMPLEMENTATION TSubOAuth2AuthenticationBindSource : public Rest::Client::TRESTAuthenticatorBindSource__1<TOAuth2Authenticator*>
{
	typedef Rest::Client::TRESTAuthenticatorBindSource__1<TOAuth2Authenticator*> inherited;
	
protected:
	virtual Rest::Client::TRESTAuthenticatorAdapter__1<TOAuth2Authenticator*>* __fastcall CreateAdapterT();
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TSubOAuth2AuthenticationBindSource(System::Classes::TComponent* AOwner) : Rest::Client::TRESTAuthenticatorBindSource__1<TOAuth2Authenticator*>(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TSubOAuth2AuthenticationBindSource() { }
	
};


class PASCALIMPLEMENTATION TOAuth2AuthenticatorAdapter : public Rest::Client::TRESTAuthenticatorAdapter__1<TOAuth2Authenticator*>
{
	typedef Rest::Client::TRESTAuthenticatorAdapter__1<TOAuth2Authenticator*> inherited;
	
protected:
	virtual void __fastcall AddFields();
public:
	/* {REST_Client}TRESTAuthenticatorAdapter<REST_Authenticator_OAuth_TOAuth2Authenticator>.Create */ inline __fastcall virtual TOAuth2AuthenticatorAdapter(System::Classes::TComponent* AOwner) : Rest::Client::TRESTAuthenticatorAdapter__1<TOAuth2Authenticator*>(AOwner) { }
	/* {REST_Client}TRESTAuthenticatorAdapter<REST_Authenticator_OAuth_TOAuth2Authenticator>.Destroy */ inline __fastcall virtual ~TOAuth2AuthenticatorAdapter() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TOAuth1SignatureMethodClass DefaultOAuth1SignatureClass;
extern DELPHI_PACKAGE TOAuth2ResponseType DefaultOAuth2ResponseType;
extern DELPHI_PACKAGE TOAuth2TokenType DefaultOAuth2TokenType;
extern DELPHI_PACKAGE System::UnicodeString DefaultOAuth2AccessTokenParamName;
extern DELPHI_PACKAGE System::UnicodeString __fastcall OAuth2ResponseTypeToString(const TOAuth2ResponseType AType);
extern DELPHI_PACKAGE TOAuth2ResponseType __fastcall OAuth2ResponseTypeFromString(const System::UnicodeString ATypeString);
extern DELPHI_PACKAGE System::UnicodeString __fastcall OAuth2TokenTypeToString(const TOAuth2TokenType AType);
extern DELPHI_PACKAGE TOAuth2TokenType __fastcall OAuth2TokenTypeFromString(const System::UnicodeString ATypeString);
}	/* namespace Oauth */
}	/* namespace Authenticator */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_AUTHENTICATOR_OAUTH)
using namespace Rest::Authenticator::Oauth;
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
#endif	// Rest_Authenticator_OauthHPP
