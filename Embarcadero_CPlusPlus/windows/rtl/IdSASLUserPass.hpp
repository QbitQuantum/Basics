// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSASLUserPass.pas' rev: 34.00 (Windows)

#ifndef IdsasluserpassHPP
#define IdsasluserpassHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdSASL.hpp>
#include <IdUserPassProvider.hpp>
#include <IdBaseComponent.hpp>
#include <IdException.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsasluserpass
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSASLUserPass;
class DELPHICLASS EIdUserPassProviderUnassigned;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdSASLUserPass : public Idsasl::TIdSASL
{
	typedef Idsasl::TIdSASL inherited;
	
protected:
	Iduserpassprovider::TIdUserPassProvider* FUserPassProvider;
	void __fastcall SetUserPassProvider(Iduserpassprovider::TIdUserPassProvider* const Value);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	System::UnicodeString __fastcall GetUsername();
	System::UnicodeString __fastcall GetPassword();
	
public:
	virtual bool __fastcall IsReadyToStart();
	
__published:
	__property Iduserpassprovider::TIdUserPassProvider* UserPassProvider = {read=FUserPassProvider, write=SetUserPassProvider};
public:
	/* TIdSASL.Destroy */ inline __fastcall virtual ~TIdSASLUserPass() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSASLUserPass(System::Classes::TComponent* AOwner)/* overload */ : Idsasl::TIdSASL(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSASLUserPass()/* overload */ : Idsasl::TIdSASL() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdUserPassProviderUnassigned : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdUserPassProviderUnassigned(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdUserPassProviderUnassigned(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdUserPassProviderUnassigned(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdUserPassProviderUnassigned(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdUserPassProviderUnassigned(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdUserPassProviderUnassigned(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdUserPassProviderUnassigned(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdUserPassProviderUnassigned(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdUserPassProviderUnassigned(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdUserPassProviderUnassigned(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdUserPassProviderUnassigned(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdUserPassProviderUnassigned(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdUserPassProviderUnassigned() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idsasluserpass */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSASLUSERPASS)
using namespace Idsasluserpass;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsasluserpassHPP
