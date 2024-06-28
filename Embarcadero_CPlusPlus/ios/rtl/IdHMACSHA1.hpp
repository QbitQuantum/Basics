// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdHMACSHA1.pas' rev: 34.00 (iOS)

#ifndef Idhmacsha1HPP
#define Idhmacsha1HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdFIPS.hpp>
#include <IdGlobal.hpp>
#include <IdHash.hpp>
#include <IdHashSHA.hpp>
#include <IdHMAC.hpp>
#include <IdException.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idhmacsha1
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdHMACSHA1;
class DELPHICLASS TIdHMACSHA224;
class DELPHICLASS TIdHMACSHA256;
class DELPHICLASS TIdHMACSHA384;
class DELPHICLASS TIdHMACSHA512;
class DELPHICLASS EIdHMACHashNotAvailable;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdHMACSHA1 : public Idhmac::TIdHMAC
{
	typedef Idhmac::TIdHMAC inherited;
	
protected:
	virtual void __fastcall SetHashVars();
	virtual bool __fastcall IsIntFAvail();
	virtual void * __fastcall InitIntFInst(const Idglobal::TIdBytes AKey);
	virtual void __fastcall InitHash();
public:
	/* TIdHMAC.Create */ inline __fastcall virtual TIdHMACSHA1() : Idhmac::TIdHMAC() { }
	/* TIdHMAC.Destroy */ inline __fastcall virtual ~TIdHMACSHA1() { }
	
};


class PASCALIMPLEMENTATION TIdHMACSHA224 : public Idhmac::TIdHMAC
{
	typedef Idhmac::TIdHMAC inherited;
	
protected:
	virtual void __fastcall SetHashVars();
	virtual bool __fastcall IsIntFAvail();
	virtual void * __fastcall InitIntFInst(const Idglobal::TIdBytes AKey);
	virtual void __fastcall InitHash();
public:
	/* TIdHMAC.Create */ inline __fastcall virtual TIdHMACSHA224() : Idhmac::TIdHMAC() { }
	/* TIdHMAC.Destroy */ inline __fastcall virtual ~TIdHMACSHA224() { }
	
};


class PASCALIMPLEMENTATION TIdHMACSHA256 : public Idhmac::TIdHMAC
{
	typedef Idhmac::TIdHMAC inherited;
	
protected:
	virtual void __fastcall SetHashVars();
	virtual bool __fastcall IsIntFAvail();
	virtual void * __fastcall InitIntFInst(const Idglobal::TIdBytes AKey);
	virtual void __fastcall InitHash();
public:
	/* TIdHMAC.Create */ inline __fastcall virtual TIdHMACSHA256() : Idhmac::TIdHMAC() { }
	/* TIdHMAC.Destroy */ inline __fastcall virtual ~TIdHMACSHA256() { }
	
};


class PASCALIMPLEMENTATION TIdHMACSHA384 : public Idhmac::TIdHMAC
{
	typedef Idhmac::TIdHMAC inherited;
	
protected:
	virtual void __fastcall SetHashVars();
	virtual bool __fastcall IsIntFAvail();
	virtual void * __fastcall InitIntFInst(const Idglobal::TIdBytes AKey);
	virtual void __fastcall InitHash();
public:
	/* TIdHMAC.Create */ inline __fastcall virtual TIdHMACSHA384() : Idhmac::TIdHMAC() { }
	/* TIdHMAC.Destroy */ inline __fastcall virtual ~TIdHMACSHA384() { }
	
};


class PASCALIMPLEMENTATION TIdHMACSHA512 : public Idhmac::TIdHMAC
{
	typedef Idhmac::TIdHMAC inherited;
	
protected:
	virtual void __fastcall SetHashVars();
	virtual bool __fastcall IsIntFAvail();
	virtual void * __fastcall InitIntFInst(const Idglobal::TIdBytes AKey);
	virtual void __fastcall InitHash();
public:
	/* TIdHMAC.Create */ inline __fastcall virtual TIdHMACSHA512() : Idhmac::TIdHMAC() { }
	/* TIdHMAC.Destroy */ inline __fastcall virtual ~TIdHMACSHA512() { }
	
};


class PASCALIMPLEMENTATION EIdHMACHashNotAvailable : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdHMACHashNotAvailable(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdHMACHashNotAvailable(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdHMACHashNotAvailable(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdHMACHashNotAvailable(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdHMACHashNotAvailable(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdHMACHashNotAvailable(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdHMACHashNotAvailable(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdHMACHashNotAvailable(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdHMACHashNotAvailable(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdHMACHashNotAvailable(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdHMACHashNotAvailable(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdHMACHashNotAvailable(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdHMACHashNotAvailable() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idhmacsha1 */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDHMACSHA1)
using namespace Idhmacsha1;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Idhmacsha1HPP
