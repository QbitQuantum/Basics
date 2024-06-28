// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdCoderXXE.pas' rev: 34.00 (Windows)

#ifndef IdcoderxxeHPP
#define IdcoderxxeHPP

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

namespace Idcoderxxe
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdDecoderXXE;
class DELPHICLASS TIdEncoderXXE;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdDecoderXXE : public Idcoder00e::TIdDecoder00E
{
	typedef Idcoder00e::TIdDecoder00E inherited;
	
protected:
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdDecoderXXE(System::Classes::TComponent* AOwner)/* overload */;
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdDecoderXXE()/* overload */ : Idcoder00e::TIdDecoder00E() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdDecoderXXE() { }
	
};


class PASCALIMPLEMENTATION TIdEncoderXXE : public Idcoder00e::TIdEncoder00E
{
	typedef Idcoder00e::TIdEncoder00E inherited;
	
protected:
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdEncoderXXE(System::Classes::TComponent* AOwner)/* overload */;
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdEncoderXXE()/* overload */ : Idcoder00e::TIdEncoder00E() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdEncoderXXE() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString GXXECodeTable;
extern DELPHI_PACKAGE Idcoder3to4::TIdDecodeTable GXXEDecodeTable;
}	/* namespace Idcoderxxe */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDCODERXXE)
using namespace Idcoderxxe;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdcoderxxeHPP
