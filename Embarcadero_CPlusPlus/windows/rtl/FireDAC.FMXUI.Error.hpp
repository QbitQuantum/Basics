// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.FMXUI.Error.pas' rev: 34.00 (Windows)

#ifndef Firedac_Fmxui_ErrorHPP
#define Firedac_Fmxui_ErrorHPP

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
#include <FMX.Forms.hpp>
#include <FMX.Controls.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Edit.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include <FMX.ExtCtrls.hpp>
#include <FMX.Grid.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Header.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.FMXUI.OptsBase.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FireDAC.FMXUI.Error"

namespace Firedac
{
namespace Fmxui
{
namespace Error
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmFDGUIxFMXError;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TfrmFDGUIxFMXError : public Firedac::Fmxui::Optsbase::TfrmFDGUIxFMXOptsBase
{
	typedef Firedac::Fmxui::Optsbase::TfrmFDGUIxFMXOptsBase inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* pcAdvanced;
	Fmx::Tabcontrol::TTabItem* tsAdvanced;
	Fmx::Tabcontrol::TTabItem* tsQuery;
	Fmx::Stdctrls::TLabel* NativeLabel;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Edit::TEdit* edtErrorCode;
	Fmx::Edit::TEdit* edtServerObject;
	Fmx::Memo::TMemo* edtMessage;
	Fmx::Edit::TEdit* edtErrorKind;
	Fmx::Edit::TEdit* edtCommandTextOffset;
	Fmx::Stdctrls::TLabel* Label9;
	Fmx::Stdctrls::TLabel* Label5;
	Fmx::Listbox::TListBox* lvCommandParams;
	Fmx::Tabcontrol::TTabItem* tsOther;
	Fmx::Stdctrls::TLabel* Label6;
	Fmx::Stdctrls::TLabel* Label7;
	Fmx::Edit::TEdit* edtClassName;
	Fmx::Edit::TEdit* edtADCode;
	Fmx::Stdctrls::TLabel* Label8;
	Fmx::Stdctrls::TLabel* Label10;
	Fmx::Stdctrls::TLabel* Label11;
	Fmx::Stdctrls::TPanel* pnlMsg;
	Fmx::Memo::TMemo* memMsg;
	Fmx::Stdctrls::TPanel* pnlAdvanced;
	Fmx::Stdctrls::TButton* btnCopy;
	Fmx::Stdctrls::TPanel* pnlCopy;
	Fmx::Stdctrls::TPanel* Panel1;
	Fmx::Memo::TMemo* mmCommandText;
	Fmx::Stdctrls::TPanel* Panel3;
	Fmx::Header::THeader* Header1;
	Fmx::Header::THeaderItem* HeaderItem1;
	Fmx::Header::THeaderItem* HeaderItem2;
	Fmx::Stdctrls::TLabel* Label12;
	Fmx::Edit::TEdit* edtADObjName;
	Fmx::Stdctrls::TButton* btnPrior;
	Fmx::Stdctrls::TButton* btnNext;
	HIDESBASE void __fastcall FormActivate(System::TObject* Sender);
	void __fastcall BackClick(System::TObject* Sender);
	void __fastcall NextClick(System::TObject* Sender);
	HIDESBASE void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall DetailsBtnClick(System::TObject* Sender);
	void __fastcall FormResize(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall FormKeyDown(System::TObject* Sender, System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	void __fastcall btnCopyClick(System::TObject* Sender);
	
private:
	Firedac::Stan::Error::EFDDBEngineException* FError;
	int FDetailsHeight;
	int CurItem;
	System::UnicodeString FDetails;
	int FPrevWidth;
	Firedac::Ui::Intf::TFDGUIxErrorDialogEvent FOnHide;
	Firedac::Ui::Intf::TFDGUIxErrorDialogEvent FOnShow;
	void __fastcall UpdateLayout(bool ASwitching);
	void __fastcall ShowError();
	void __fastcall ShowCommand();
	
protected:
	void __fastcall Execute(Firedac::Stan::Error::EFDDBEngineException* AExc);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TfrmFDGUIxFMXError(System::Classes::TComponent* AOwner) : Firedac::Fmxui::Optsbase::TfrmFDGUIxFMXOptsBase(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmFDGUIxFMXError(System::Classes::TComponent* AOwner, NativeInt Dummy) : Firedac::Fmxui::Optsbase::TfrmFDGUIxFMXOptsBase(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFMXError() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TfrmFDGUIxFMXError* frmFDGUIxFMXError;
}	/* namespace Error */
}	/* namespace Fmxui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_FMXUI_ERROR)
using namespace Firedac::Fmxui::Error;
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
#endif	// Firedac_Fmxui_ErrorHPP
