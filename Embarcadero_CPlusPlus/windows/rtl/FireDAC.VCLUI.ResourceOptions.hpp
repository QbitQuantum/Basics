// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.VCLUI.ResourceOptions.pas' rev: 34.00 (Windows)

#ifndef Firedac_Vclui_ResourceoptionsHPP
#define Firedac_Vclui_ResourceoptionsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Messages.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.VCLUI.Controls.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Vclui
{
namespace Resourceoptions
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmFDGUIxFormsResourceOptions;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TfrmFDGUIxFormsResourceOptions : public Vcl::Forms::TFrame
{
	typedef Vcl::Forms::TFrame inherited;
	
__published:
	Vcl::Extctrls::TPanel* ro_gbCmdTextProcess;
	Vcl::Extctrls::TPanel* ro_rbConnection;
	Vcl::Stdctrls::TCheckBox* ro_cbAutoReconnect;
	Vcl::Extctrls::TPanel* ro_gbCmdExecute;
	Vcl::Stdctrls::TCheckBox* ro_cbCreateParams;
	Vcl::Stdctrls::TCheckBox* ro_cbCreateMacros;
	Vcl::Stdctrls::TLabel* ro_Label1;
	Vcl::Stdctrls::TEdit* ro_edtMaxCursors;
	Vcl::Stdctrls::TComboBox* ro_cbxCmdExecMode;
	Vcl::Stdctrls::TLabel* ro_Label2;
	Vcl::Stdctrls::TLabel* ro_Label3;
	Vcl::Stdctrls::TEdit* ro_edtCmdExecTimeout;
	Vcl::Stdctrls::TCheckBox* ro_cbExpandParams;
	Vcl::Stdctrls::TCheckBox* ro_cbExpandMacros;
	Vcl::Stdctrls::TCheckBox* ro_cbExpandEscapes;
	Vcl::Stdctrls::TLabel* ro_Label4;
	Vcl::Stdctrls::TComboBox* ro_cbxDefaultParamType;
	Vcl::Extctrls::TPanel* ro_gbPersistance;
	Vcl::Stdctrls::TCheckBox* ro_cbPersistent;
	Vcl::Stdctrls::TCheckBox* ro_cbBackup;
	Vcl::Stdctrls::TLabel* ro_Label6;
	Vcl::Stdctrls::TEdit* ro_edtDefaultStorageFolder;
	Vcl::Stdctrls::TLabel* ro_Label7;
	Vcl::Stdctrls::TEdit* ro_edtDefaultBackupFolder;
	Vcl::Stdctrls::TLabel* ro_Label8;
	Vcl::Stdctrls::TLabel* ro_Label9;
	Vcl::Stdctrls::TEdit* ro_edtDefaultStorageExt;
	Vcl::Stdctrls::TEdit* ro_edtDefaultBackupExt;
	Vcl::Buttons::TSpeedButton* ro_btnFld1;
	Vcl::Buttons::TSpeedButton* ro_btnFld2;
	Vcl::Stdctrls::TLabel* ro_Label10;
	Vcl::Stdctrls::TEdit* ro_edtArrayDMLSize;
	Vcl::Stdctrls::TCheckBox* ro_cbShowWaitCursor;
	Vcl::Stdctrls::TCheckBox* ro_cbServerOutput;
	Vcl::Stdctrls::TLabel* ro_Label5;
	Vcl::Stdctrls::TEdit* ro_edtServerOutputSize;
	Vcl::Stdctrls::TLabel* ro_Label11;
	Vcl::Stdctrls::TComboBox* ro_cbDefaultStoreFormat;
	Vcl::Stdctrls::TCheckBox* ro_cbAutoConnect;
	Vcl::Stdctrls::TCheckBox* ro_cbKeepConnection;
	Vcl::Stdctrls::TCheckBox* ro_cbUnifyParams;
	void __fastcall ro_Change(System::TObject* Sender);
	void __fastcall ro_btnFld1Click(System::TObject* Sender);
	void __fastcall ro_btnFld2Click(System::TObject* Sender);
	
private:
	System::Classes::TNotifyEvent FOnModified;
	bool FModifiedLocked;
	
public:
	void __fastcall LoadFrom(Firedac::Stan::Option::TFDResourceOptions* AOpts);
	void __fastcall SaveTo(Firedac::Stan::Option::TFDResourceOptions* AOpts);
	
__published:
	__property System::Classes::TNotifyEvent OnModified = {read=FOnModified, write=FOnModified};
public:
	/* TCustomFrame.Create */ inline __fastcall virtual TfrmFDGUIxFormsResourceOptions(System::Classes::TComponent* AOwner) : Vcl::Forms::TFrame(AOwner) { }
	
public:
	/* TScrollingWinControl.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFormsResourceOptions() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrmFDGUIxFormsResourceOptions(HWND ParentWindow) : Vcl::Forms::TFrame(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Resourceoptions */
}	/* namespace Vclui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI_RESOURCEOPTIONS)
using namespace Firedac::Vclui::Resourceoptions;
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
#endif	// Firedac_Vclui_ResourceoptionsHPP
