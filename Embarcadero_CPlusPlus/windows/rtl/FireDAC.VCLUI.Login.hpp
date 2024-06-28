// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.VCLUI.Login.pas' rev: 34.00 (Windows)

#ifndef Firedac_Vclui_LoginHPP
#define Firedac_Vclui_LoginHPP

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
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ImgList.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.UI.hpp>
#include <FireDAC.VCLUI.OptsBase.hpp>
#include <FireDAC.Stan.Factory.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FireDAC.VCLUI.Login"

namespace Firedac
{
namespace Vclui
{
namespace Login
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDGUIxFormsLoginDialogImpl;
class DELPHICLASS TfrmFDGUIxFormsLogin;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDGUIxFormsLoginDialogImpl : public Firedac::Ui::TFDGUIxLoginDialogImplBase
{
	typedef Firedac::Ui::TFDGUIxLoginDialogImplBase inherited;
	
private:
	TfrmFDGUIxFormsLogin* __fastcall CreateDlg();
	
protected:
	virtual bool __fastcall ExecuteLogin();
	virtual bool __fastcall ExecuteChngPwd();
public:
	/* TFDGUIxLoginDialogImplBase.Destroy */ inline __fastcall virtual ~TFDGUIxFormsLoginDialogImpl() { }
	
public:
	/* TFDObject.Create */ inline __fastcall virtual TFDGUIxFormsLoginDialogImpl() : Firedac::Ui::TFDGUIxLoginDialogImplBase() { }
	
};


class PASCALIMPLEMENTATION TfrmFDGUIxFormsLogin : public Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase
{
	typedef Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase inherited;
	
__published:
	Vcl::Extctrls::TPanel* pnlLogin;
	Vcl::Extctrls::TPanel* pnlControls;
	Vcl::Extctrls::TPanel* pnlHistory;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Buttons::TSpeedButton* SpeedButton1;
	Vcl::Stdctrls::TComboBox* cbxProfiles;
	Vcl::Extctrls::TBevel* Bevel1;
	Vcl::Extctrls::TPanel* pnlChngPwd;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TEdit* edtNewPassword;
	Vcl::Stdctrls::TEdit* edtNewPassword2;
	Vcl::Dialogs::TOpenDialog* OpenDialog1;
	Vcl::Controls::TImageList* ImageList1;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall SpeedButton1Click(System::TObject* Sender);
	void __fastcall cbxProfilesClick(System::TObject* Sender);
	void __fastcall edtNewPasswordChange(System::TObject* Sender);
	void __fastcall cbxProfilesChange(System::TObject* Sender);
	void __fastcall FileEditClick(System::TObject* Sender);
	
private:
	TFDGUIxFormsLoginDialogImpl* FDlg;
	int FAddToOptionsHeight;
	
public:
	bool __fastcall ExecuteLogin();
	bool __fastcall ExecuteChngPwd();
public:
	/* TfrmFDGUIxFormsOptsBase.Create */ inline __fastcall virtual TfrmFDGUIxFormsLogin(System::Classes::TComponent* AOwner) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(AOwner) { }
	
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmFDGUIxFormsLogin(System::Classes::TComponent* AOwner, int Dummy) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFormsLogin() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrmFDGUIxFormsLogin(HWND ParentWindow) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TfrmFDGUIxFormsLogin* frmFDGUIxFormsLogin;
}	/* namespace Login */
}	/* namespace Vclui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI_LOGIN)
using namespace Firedac::Vclui::Login;
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
#endif	// Firedac_Vclui_LoginHPP
