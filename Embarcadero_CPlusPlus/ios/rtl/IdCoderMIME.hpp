// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdCoderMIME.pas' rev: 34.00 (iOS)

#ifndef IdcodermimeHPP
#define IdcodermimeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdCoder3to4.hpp>
#include <IdGlobal.hpp>
#include <IdBaseComponent.hpp>
#include <IdCoder.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idcodermime
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdEncoderMIME;
class DELPHICLASS TIdDecoderMIME;
class DELPHICLASS TIdDecoderMIMELineByLine;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdEncoderMIME : public Idcoder3to4::TIdEncoder3to4
{
	typedef Idcoder3to4::TIdEncoder3to4 inherited;
	
protected:
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdEncoderMIME(System::Classes::TComponent* AOwner)/* overload */;
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdEncoderMIME()/* overload */ : Idcoder3to4::TIdEncoder3to4() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdEncoderMIME() { }
	
};


class PASCALIMPLEMENTATION TIdDecoderMIME : public Idcoder3to4::TIdDecoder4to3
{
	typedef Idcoder3to4::TIdDecoder4to3 inherited;
	
protected:
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdDecoderMIME(System::Classes::TComponent* AOwner)/* overload */;
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdDecoderMIME()/* overload */ : Idcoder3to4::TIdDecoder4to3() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdDecoderMIME() { }
	
};


class PASCALIMPLEMENTATION TIdDecoderMIMELineByLine : public TIdDecoderMIME
{
	typedef TIdDecoderMIME inherited;
	
protected:
	Idglobal::TIdBytes FLeftFromLastTime;
	
public:
	virtual void __fastcall DecodeBegin(System::Classes::TStream* ADestStream);
	virtual void __fastcall DecodeEnd();
	virtual void __fastcall Decode(System::Classes::TStream* ASrcStream, const int ABytes = 0xffffffff)/* overload */;
public:
	/* TIdDecoderMIME.Create */ inline __fastcall TIdDecoderMIMELineByLine(System::Classes::TComponent* AOwner)/* overload */ : TIdDecoderMIME(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdDecoderMIMELineByLine()/* overload */ : TIdDecoderMIME() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdDecoderMIMELineByLine() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Decode(const System::UnicodeString AIn){ Idcoder::TIdDecoder::Decode(AIn); }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString GBase64CodeTable;
extern DELPHI_PACKAGE Idcoder3to4::TIdDecodeTable GBase64DecodeTable;
}	/* namespace Idcodermime */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDCODERMIME)
using namespace Idcodermime;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdcodermimeHPP
