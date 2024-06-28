// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.FMXUI.Login.pas' rev: 34.00 (iOS)

#ifndef Firedac_Fmxui_LoginHPP
#define Firedac_Fmxui_LoginHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include <FMX.Effects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.UI.hpp>
#include <FireDAC.FMXUI.OptsBase.hpp>
#include <FireDAC.Stan.Factory.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
namespace Firedac
{
namespace Fmxui
{
namespace Login
{
  _INIT_UNIT(Firedac_Fmxui_Login);
}	/* namespace Login */
}	/* namespace Fmxui */
}	/* namespace Firedac */

namespace Firedac
{
namespace Fmxui
{
namespace Login
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDGUIxFMXLoginDialogImpl;
class DELPHICLASS TfrmFDGUIxFMXLogin;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDGUIxFMXLoginDialogImpl : public Firedac::Ui::TFDGUIxLoginDialogImplBase
{
	typedef Firedac::Ui::TFDGUIxLoginDialogImplBase inherited;
	
private:
	TfrmFDGUIxFMXLogin* __fastcall CreateDlg();
	
protected:
	virtual bool __fastcall ExecuteLogin();
	virtual bool __fastcall ExecuteChngPwd();
public:
	/* TFDGUIxLoginDialogImplBase.Destroy */ inline __fastcall virtual ~TFDGUIxFMXLoginDialogImpl() { }
	
public:
	/* TFDObject.Create */ inline __fastcall virtual TFDGUIxFMXLoginDialogImpl() : Firedac::Ui::TFDGUIxLoginDialogImplBase() { }
	
};


class PASCALIMPLEMENTATION TfrmFDGUIxFMXLogin : public Firedac::Fmxui::Optsbase::TfrmFDGUIxFMXOptsBase
{
	typedef Firedac::Fmxui::Optsbase::TfrmFDGUIxFMXOptsBase inherited;
	
__published:
	Fmx::Stdctrls::TPanel* pnlLogin;
	Fmx::Stdctrls::TPanel* pnlControls;
	Fmx::Stdctrls::TPanel* pnlHistory;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Listbox::TComboBox* cbxProfiles;
	Fmx::Stdctrls::TPanel* pnlChngPwd;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Edit::TEdit* edtNewPassword;
	Fmx::Edit::TEdit* edtNewPassword2;
	Fmx::Dialogs::TOpenDialog* OpenDialog1;
	Fmx::Objects::TLine* Line5;
	Fmx::Objects::TLine* Line6;
	Fmx::Objects::TImage* imgEnabled;
	Fmx::Objects::TImage* imgDisabled;
	Fmx::Objects::TImage* imgOpen;
	Fmx::Stdctrls::TPanel* pnlButton;
	Fmx::Stdctrls::TPanel* pnlCombo;
	Fmx::Effects::TShadowEffect* ShadowEffect1;
	HIDESBASE void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall cbxProfilesClick(System::TObject* Sender);
	void __fastcall edtNewPasswordChange(System::TObject* Sender);
	void __fastcall cbxProfilesChange(System::TObject* Sender);
	void __fastcall FileEditClick(System::TObject* Sender);
	void __fastcall imgEnabledClick(System::TObject* Sender);
	
private:
	TFDGUIxFMXLoginDialogImpl* FDlg;
	int FAddToOptionsHeight;
	bool FResult;
	void __fastcall PostprocessLoginDialog(bool AOk);
	
public:
	bool __fastcall ExecuteLogin();
	bool __fastcall ExecuteChngPwd();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TfrmFDGUIxFMXLogin(System::Classes::TComponent* AOwner) : Firedac::Fmxui::Optsbase::TfrmFDGUIxFMXOptsBase(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmFDGUIxFMXLogin(System::Classes::TComponent* AOwner, NativeInt Dummy) : Firedac::Fmxui::Optsbase::TfrmFDGUIxFMXOptsBase(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFMXLogin() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TfrmFDGUIxFMXLogin* frmFDGUIxFormsLogin;
}	/* namespace Login */
}	/* namespace Fmxui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_FMXUI_LOGIN)
using namespace Firedac::Fmxui::Login;
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
#endif	// Firedac_Fmxui_LoginHPP
