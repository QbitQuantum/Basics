// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.VCLUI.Async.pas' rev: 34.00 (Windows)

#ifndef Firedac_Vclui_AsyncHPP
#define Firedac_Vclui_AsyncHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Messages.hpp>
#include <Winapi.Windows.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.StdCtrls.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.OptsBase.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FireDAC.VCLUI.Async"

namespace Firedac
{
namespace Vclui
{
namespace Async
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmFDGUIxFormsAsyncExecute;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TfrmFDGUIxFormsAsyncExecute : public Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase
{
	typedef Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase inherited;
	
__published:
	Vcl::Extctrls::TTimer* tmrDelay;
	Vcl::Buttons::TSpeedButton* btnCancel2;
	void __fastcall FormKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall btnCancelClick(System::TObject* Sender);
	void __fastcall tmrDelayTimer(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	
private:
	Firedac::Stan::Intf::_di_IFDStanAsyncExecutor FExecutor;
	bool FRequestShow;
	void *FModalData;
	int FShowDelay;
	int FHideDelay;
	
protected:
	HIDESBASE void __fastcall Show(const Firedac::Stan::Intf::_di_IFDStanAsyncExecutor AExecutor);
	HIDESBASE void __fastcall Hide();
	bool __fastcall IsFormActive();
	bool __fastcall IsFormMouseMessage(const tagMSG &AMsg);
public:
	/* TfrmFDGUIxFormsOptsBase.Create */ inline __fastcall virtual TfrmFDGUIxFormsAsyncExecute(System::Classes::TComponent* AOwner) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(AOwner) { }
	
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmFDGUIxFormsAsyncExecute(System::Classes::TComponent* AOwner, int Dummy) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFormsAsyncExecute() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrmFDGUIxFormsAsyncExecute(HWND ParentWindow) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TfrmFDGUIxFormsAsyncExecute* frmFDGUIxFormsAsyncExecute;
}	/* namespace Async */
}	/* namespace Vclui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI_ASYNC)
using namespace Firedac::Vclui::Async;
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
#endif	// Firedac_Vclui_AsyncHPP
