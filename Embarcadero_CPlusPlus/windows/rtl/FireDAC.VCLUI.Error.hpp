// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.VCLUI.Error.pas' rev: 34.00 (Windows)

#ifndef Firedac_Vclui_ErrorHPP
#define Firedac_Vclui_ErrorHPP

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
#include <Vcl.Forms.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Clipbrd.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Controls.hpp>
#include <FireDAC.VCLUI.Memo.hpp>
#include <FireDAC.VCLUI.OptsBase.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FireDAC.VCLUI.Error"

namespace Firedac
{
namespace Vclui
{
namespace Error
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmFDGUIxFormsError;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TfrmFDGUIxFormsError : public Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase
{
	typedef Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase inherited;
	
__published:
	Vcl::Comctrls::TPageControl* pcAdvanced;
	Vcl::Comctrls::TTabSheet* tsAdvanced;
	Vcl::Comctrls::TTabSheet* tsQuery;
	Vcl::Extctrls::TBevel* Bevel1;
	Vcl::Stdctrls::TLabel* NativeLabel;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TEdit* edtErrorCode;
	Vcl::Stdctrls::TEdit* edtServerObject;
	Vcl::Stdctrls::TMemo* edtMessage;
	Vcl::Stdctrls::TEdit* edtErrorKind;
	Vcl::Stdctrls::TEdit* edtCommandTextOffset;
	Vcl::Stdctrls::TButton* btnPrior;
	Vcl::Stdctrls::TButton* btnNext;
	Vcl::Stdctrls::TLabel* Label9;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Comctrls::TListView* lvCommandParams;
	Vcl::Comctrls::TTabSheet* tsOther;
	Vcl::Stdctrls::TLabel* Label6;
	Vcl::Stdctrls::TLabel* Label7;
	Vcl::Stdctrls::TEdit* edtClassName;
	Vcl::Stdctrls::TEdit* edtADCode;
	Vcl::Stdctrls::TLabel* Label8;
	Vcl::Stdctrls::TLabel* Label10;
	Vcl::Stdctrls::TLabel* Label11;
	Vcl::Extctrls::TPanel* pnlMsg;
	Vcl::Stdctrls::TMemo* memMsg;
	Vcl::Extctrls::TPanel* pnlAdvanced;
	Vcl::Stdctrls::TButton* btnCopy;
	Vcl::Stdctrls::TLabel* Label12;
	Vcl::Stdctrls::TEdit* edtADObjName;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall BackClick(System::TObject* Sender);
	void __fastcall NextClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall DetailsBtnClick(System::TObject* Sender);
	void __fastcall FormResize(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall FormKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall btnCopyClick(System::TObject* Sender);
	
private:
	Firedac::Vclui::Memo::TFDGUIxFormsMemo* mmCommandText;
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
	/* TfrmFDGUIxFormsOptsBase.Create */ inline __fastcall virtual TfrmFDGUIxFormsError(System::Classes::TComponent* AOwner) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(AOwner) { }
	
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmFDGUIxFormsError(System::Classes::TComponent* AOwner, int Dummy) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFormsError() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrmFDGUIxFormsError(HWND ParentWindow) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TfrmFDGUIxFormsError* frmFDGUIxFormsError;
}	/* namespace Error */
}	/* namespace Vclui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI_ERROR)
using namespace Firedac::Vclui::Error;
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
#endif	// Firedac_Vclui_ErrorHPP
