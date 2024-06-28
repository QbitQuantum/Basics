// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.VCLUI.Memo.pas' rev: 34.00 (Windows)

#ifndef Firedac_Vclui_MemoHPP
#define Firedac_Vclui_MemoHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.Win.Registry.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.StdCtrls.hpp>
#include <FireDAC.Stan.Intf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Vclui
{
namespace Memo
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDGUIxFormsMemo;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDGUIxFormsMemo : public Vcl::Stdctrls::TMemo
{
	typedef Vcl::Stdctrls::TMemo inherited;
	
private:
	Firedac::Stan::Intf::TFDRDBMSKind FRDBMSKind;
	
public:
	__fastcall virtual TFDGUIxFormsMemo(System::Classes::TComponent* AOwner);
	__property Firedac::Stan::Intf::TFDRDBMSKind RDBMSKind = {read=FRDBMSKind, write=FRDBMSKind, nodefault};
public:
	/* TCustomMemo.Destroy */ inline __fastcall virtual ~TFDGUIxFormsMemo() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFDGUIxFormsMemo(HWND ParentWindow) : Vcl::Stdctrls::TMemo(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Memo */
}	/* namespace Vclui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI_MEMO)
using namespace Firedac::Vclui::Memo;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI)
using namespace Firedac::Vclui;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Vclui_MemoHPP
