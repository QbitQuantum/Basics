// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.FMXUI.Script.pas' rev: 34.00 (Windows)

#ifndef Firedac_Fmxui_ScriptHPP
#define Firedac_Fmxui_ScriptHPP

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
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Types.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.TreeView.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.FMXUI.OptsBase.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FireDAC.FMXUI.Script"

namespace Firedac
{
namespace Fmxui
{
namespace Script
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmFDGUIxFMXfScript;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TfrmFDGUIxFMXfScript : public Firedac::Fmxui::Optsbase::TfrmFDGUIxFMXOptsBase
{
	typedef Firedac::Fmxui::Optsbase::TfrmFDGUIxFMXOptsBase inherited;
	
__published:
	Fmx::Stdctrls::TPanel* pnlPrcLocation;
	Fmx::Treeview::TTreeView* tvPrcLocation;
	Fmx::Stdctrls::TProgressBar* pbPrcMain;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TLabel* lblTotalSize;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Stdctrls::TLabel* lblTotalDone;
	Fmx::Stdctrls::TLabel* Label5;
	Fmx::Stdctrls::TLabel* lblTotalPctDone;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TLabel* lblTotalErrors;
	Fmx::Types::TTimer* Timer1;
	Fmx::Stdctrls::TPanel* pnlPrcOutput;
	Fmx::Listbox::TListBox* lbPrcOutput;
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
	/* TCustomForm.Create */ inline __fastcall virtual TfrmFDGUIxFMXfScript(System::Classes::TComponent* AOwner) : Firedac::Fmxui::Optsbase::TfrmFDGUIxFMXOptsBase(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmFDGUIxFMXfScript(System::Classes::TComponent* AOwner, NativeInt Dummy) : Firedac::Fmxui::Optsbase::TfrmFDGUIxFMXOptsBase(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFMXfScript() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Script */
}	/* namespace Fmxui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_FMXUI_SCRIPT)
using namespace Firedac::Fmxui::Script;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_FMXUI)
using namespace Firedac::Fmxui;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Fmxui_ScriptHPP
