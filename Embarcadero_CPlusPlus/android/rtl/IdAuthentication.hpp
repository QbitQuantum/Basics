// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdAuthentication.pas' rev: 34.00 (Android)

#ifndef IdauthenticationHPP
#define IdauthenticationHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdHeaderList.hpp>
#include <IdGlobal.hpp>
#include <IdException.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idauthentication
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdAuthentication;
class DELPHICLASS TIdBasicAuthentication;
class DELPHICLASS EIdAlreadyRegisteredAuthenticationMethod;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIdAuthenticationSchemes : unsigned char { asBasic, asDigest, asNTLM, asUnknown };

typedef System::Set<TIdAuthenticationSchemes, TIdAuthenticationSchemes::asBasic, TIdAuthenticationSchemes::asUnknown> TIdAuthSchemeSet;

enum DECLSPEC_DENUM TIdAuthWhatsNext : unsigned char { wnAskTheProgram, wnDoRequest, wnFail };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdAuthentication : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
protected:
	int FCurrentStep;
	Idheaderlist::TIdHeaderList* FParams;
	Idheaderlist::TIdHeaderList* FAuthParams;
	System::UnicodeString FCharset;
	System::UnicodeString __fastcall ReadAuthInfo(System::UnicodeString AuthName);
	virtual TIdAuthWhatsNext __fastcall DoNext() = 0 ;
	void __fastcall SetAuthParams(Idheaderlist::TIdHeaderList* AValue);
	System::UnicodeString __fastcall GetPassword();
	System::UnicodeString __fastcall GetUserName();
	virtual int __fastcall GetSteps();
	virtual void __fastcall SetPassword(const System::UnicodeString Value);
	virtual void __fastcall SetUserName(const System::UnicodeString Value);
	
public:
	__fastcall virtual TIdAuthentication();
	__fastcall virtual ~TIdAuthentication();
	virtual void __fastcall Reset();
	virtual void __fastcall SetRequest(const System::UnicodeString AMethod, const System::UnicodeString AUri);
	virtual System::UnicodeString __fastcall Authentication() = 0 ;
	virtual bool __fastcall KeepAlive();
	TIdAuthWhatsNext __fastcall Next();
	__property Idheaderlist::TIdHeaderList* AuthParams = {read=FAuthParams, write=SetAuthParams};
	__property Idheaderlist::TIdHeaderList* Params = {read=FParams};
	__property System::UnicodeString Username = {read=GetUserName, write=SetUserName};
	__property System::UnicodeString Password = {read=GetPassword, write=SetPassword};
	__property int Steps = {read=GetSteps, nodefault};
	__property int CurrentStep = {read=FCurrentStep, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

_DECLARE_METACLASS(System::TMetaClass, TIdAuthenticationClass);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdBasicAuthentication : public TIdAuthentication
{
	typedef TIdAuthentication inherited;
	
protected:
	System::UnicodeString FRealm;
	virtual TIdAuthWhatsNext __fastcall DoNext();
	virtual int __fastcall GetSteps();
	
public:
	virtual System::UnicodeString __fastcall Authentication();
	__property System::UnicodeString Realm = {read=FRealm, write=FRealm};
public:
	/* TIdAuthentication.Create */ inline __fastcall virtual TIdBasicAuthentication() : TIdAuthentication() { }
	/* TIdAuthentication.Destroy */ inline __fastcall virtual ~TIdBasicAuthentication() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdAlreadyRegisteredAuthenticationMethod : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdAlreadyRegisteredAuthenticationMethod(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdAlreadyRegisteredAuthenticationMethod(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdAlreadyRegisteredAuthenticationMethod(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdAlreadyRegisteredAuthenticationMethod(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdAlreadyRegisteredAuthenticationMethod(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdAlreadyRegisteredAuthenticationMethod(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdAlreadyRegisteredAuthenticationMethod(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdAlreadyRegisteredAuthenticationMethod(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdAlreadyRegisteredAuthenticationMethod(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdAlreadyRegisteredAuthenticationMethod(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdAlreadyRegisteredAuthenticationMethod(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdAlreadyRegisteredAuthenticationMethod(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdAlreadyRegisteredAuthenticationMethod() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterAuthenticationMethod(const System::UnicodeString MethodName, const TIdAuthenticationClass AuthClass);
extern DELPHI_PACKAGE void __fastcall UnregisterAuthenticationMethod(const System::UnicodeString MethodName);
extern DELPHI_PACKAGE TIdAuthenticationClass __fastcall FindAuthClass(const System::UnicodeString AuthName);
}	/* namespace Idauthentication */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDAUTHENTICATION)
using namespace Idauthentication;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdauthenticationHPP
