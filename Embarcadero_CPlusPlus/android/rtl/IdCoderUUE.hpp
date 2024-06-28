// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdCoderUUE.pas' rev: 34.00 (Android)

#ifndef IdcoderuueHPP
#define IdcoderuueHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdCoder00E.hpp>
#include <IdCoder3to4.hpp>
#include <IdCoder.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idcoderuue
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdDecoderUUE;
class DELPHICLASS TIdEncoderUUE;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdDecoderUUE : public Idcoder00e::TIdDecoder00E
{
	typedef Idcoder00e::TIdDecoder00E inherited;
	
protected:
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdDecoderUUE(System::Classes::TComponent* AOwner)/* overload */;
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdDecoderUUE()/* overload */ : Idcoder00e::TIdDecoder00E() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdDecoderUUE() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdEncoderUUE : public Idcoder00e::TIdEncoder00E
{
	typedef Idcoder00e::TIdEncoder00E inherited;
	
protected:
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdEncoderUUE(System::Classes::TComponent* AOwner)/* overload */;
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdEncoderUUE()/* overload */ : Idcoder00e::TIdEncoder00E() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdEncoderUUE() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString GUUECodeTable;
extern DELPHI_PACKAGE Idcoder3to4::TIdDecodeTable GUUEDecodeTable;
}	/* namespace Idcoderuue */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDCODERUUE)
using namespace Idcoderuue;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdcoderuueHPP
