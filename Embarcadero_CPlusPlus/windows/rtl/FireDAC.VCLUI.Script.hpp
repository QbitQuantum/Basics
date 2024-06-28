// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.VCLUI.Script.pas' rev: 34.00 (Windows)

#ifndef Firedac_Vclui_ScriptHPP
#define Firedac_Vclui_ScriptHPP

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
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.OptsBase.hpp>
#include <FireDAC.VCLUI.Controls.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FireDAC.VCLUI.Script"

namespace Firedac
{
namespace Vclui
{
namespace Script
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmFDGUIxFormsfScript;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TfrmFDGUIxFormsfScript : public Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase
{
	typedef Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase inherited;
	
__published:
	Vcl::Extctrls::TPanel* pnlPrcLocation;
	Vcl::Comctrls::TTreeView* tvPrcLocation;
	Vcl::Comctrls::TProgressBar* pbPrcMain;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* lblTotalSize;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TLabel* lblTotalDone;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Stdctrls::TLabel* lblTotalPctDone;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* lblTotalErrors;
	Vcl::Extctrls::TTimer* Timer1;
	Vcl::Extctrls::TPanel* pnlPrcOutput;
	Vcl::Stdctrls::TListBox* lbPrcOutput;
	void __fastcall btnCancelClick(System::TObject* Sender);
	void __fastcall Timer1Timer(System::TObject* Sender);
	
private:
	void *FModalData;
	bool FIsRunning;
	bool FRequestStop;
	void __fastcall InternalHide(bool AImmediately);
	
protected:
	Firedac::Ui::Intf::TFDGUIxScriptProgressEvent FOnProgress;
	Firedac::Ui::Intf::TFDGUIxScriptOutputEvent FOnOutput;
	Firedac::Ui::Intf::TFDGUIxScriptInputEvent FOnInput;
	Firedac::Ui::Intf::TFDGUIxScriptPauseEvent FOnPause;
	Firedac::Ui::Intf::TFDGUIxScriptOptions FOptions;
	HIDESBASE void __fastcall Show();
	void __fastcall Progress(const Firedac::Ui::Intf::_di_IFDGUIxScriptDialogInfoProvider AInfoProvider);
	void __fastcall Output(const System::UnicodeString AStr);
	void __fastcall Input(const System::UnicodeString APrompt, System::UnicodeString &AResult);
	void __fastcall Pause(const System::UnicodeString APrompt);
	HIDESBASE void __fastcall Hide();
public:
	/* TfrmFDGUIxFormsOptsBase.Create */ inline __fastcall virtual TfrmFDGUIxFormsfScript(System::Classes::TComponent* AOwner) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(AOwner) { }
	
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmFDGUIxFormsfScript(System::Classes::TComponent* AOwner, int Dummy) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFormsfScript() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrmFDGUIxFormsfScript(HWND ParentWindow) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TfrmFDGUIxFormsfScript* frmFDGUIxFormsfScript;
}	/* namespace Script */
}	/* namespace Vclui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI_SCRIPT)
using namespace Firedac::Vclui::Script;
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
#endif	// Firedac_Vclui_ScriptHPP
