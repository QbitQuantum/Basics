// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.VCLUI.UpdateOptions.pas' rev: 34.00 (Windows)

#ifndef Firedac_Vclui_UpdateoptionsHPP
#define Firedac_Vclui_UpdateoptionsHPP

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
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Buttons.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.VCLUI.Controls.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Vclui
{
namespace Updateoptions
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmFDGUIxFormsUpdateOptions;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TfrmFDGUIxFormsUpdateOptions : public Vcl::Forms::TFrame
{
	typedef Vcl::Forms::TFrame inherited;
	
__published:
	Vcl::Extctrls::TPanel* uo_GroupBox3;
	Vcl::Stdctrls::TLabel* uo_Label4;
	Vcl::Stdctrls::TLabel* uo_Label5;
	Vcl::Stdctrls::TEdit* uo_edtUpdateTableName;
	Vcl::Stdctrls::TComboBox* uo_cbxUpdateMode;
	Vcl::Stdctrls::TCheckBox* uo_cbUpdateChangedFields;
	Vcl::Stdctrls::TCheckBox* uo_cbCountUpdatedRecords;
	Vcl::Extctrls::TPanel* uo_GroupBox2;
	Vcl::Stdctrls::TLabel* uo_Label1;
	Vcl::Stdctrls::TLabel* uo_Label2;
	Vcl::Stdctrls::TComboBox* uo_cbxLockMode;
	Vcl::Stdctrls::TComboBox* uo_cbxLockPoint;
	Vcl::Stdctrls::TCheckBox* uo_cbLockWait;
	Vcl::Extctrls::TPanel* uo_GroupBox4;
	Vcl::Extctrls::TPanel* uo_Panel6;
	Vcl::Menus::TPopupMenu* uo_PopupMenu1;
	Vcl::Menus::TMenuItem* uo_ReadOnly1;
	Vcl::Menus::TMenuItem* uo_ReadWrite1;
	Vcl::Menus::TMenuItem* uo_N1;
	Vcl::Menus::TMenuItem* uo_Fastupdates1;
	Vcl::Menus::TMenuItem* uo_Standardupdates1;
	Vcl::Stdctrls::TCheckBox* uo_cbEnableInsert;
	Vcl::Stdctrls::TCheckBox* uo_cbEnableUpdate;
	Vcl::Stdctrls::TCheckBox* uo_cbEnableDelete;
	Vcl::Buttons::TSpeedButton* uo_SpeedButton1;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TComboBox* uo_cbRefreshMode;
	Vcl::Stdctrls::TLabel* uo_Label6;
	Vcl::Stdctrls::TEdit* uo_edtKeyFields;
	Vcl::Extctrls::TPanel* uo_GroupBox5;
	Vcl::Stdctrls::TLabel* uo_Label7;
	Vcl::Stdctrls::TComboBox* uo_cbxFetchGeneratorsPoint;
	Vcl::Stdctrls::TLabel* uo_Label8;
	Vcl::Stdctrls::TEdit* uo_edtGeneratorName;
	Vcl::Stdctrls::TLabel* uo_Label9;
	Vcl::Stdctrls::TEdit* uo_edtAutoIncFields;
	Vcl::Stdctrls::TCheckBox* uo_cbCheckRequired;
	Vcl::Stdctrls::TCheckBox* uo_cbCheckReadOnly;
	Vcl::Stdctrls::TCheckBox* uo_cbUpdateNonBaseFields;
	void __fastcall uo_Change(System::TObject* Sender);
	void __fastcall uo_ReadOnly1Click(System::TObject* Sender);
	void __fastcall uo_ReadWrite1Click(System::TObject* Sender);
	void __fastcall uo_Fastupdates1Click(System::TObject* Sender);
	void __fastcall uo_Standardupdates1Click(System::TObject* Sender);
	void __fastcall uo_SpeedButton1Click(System::TObject* Sender);
	
private:
	System::Classes::TNotifyEvent FOnModified;
	bool FModifiedLocked;
	bool FSQLGenerator;
	bool FTableOptions;
	void __fastcall SetSQLGenerator(const bool AValue);
	void __fastcall SetTableOptions(const bool Value);
	
public:
	__fastcall virtual TfrmFDGUIxFormsUpdateOptions(System::Classes::TComponent* AOwner);
	void __fastcall LoadFrom(Firedac::Stan::Option::TFDUpdateOptions* AOpts);
	void __fastcall SaveTo(Firedac::Stan::Option::TFDUpdateOptions* AOpts);
	
__published:
	__property bool SQLGenerator = {read=FSQLGenerator, write=SetSQLGenerator, default=0};
	__property bool TableOptions = {read=FTableOptions, write=SetTableOptions, default=1};
	__property System::Classes::TNotifyEvent OnModified = {read=FOnModified, write=FOnModified};
public:
	/* TScrollingWinControl.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFormsUpdateOptions() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrmFDGUIxFormsUpdateOptions(HWND ParentWindow) : Vcl::Forms::TFrame(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Updateoptions */
}	/* namespace Vclui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI_UPDATEOPTIONS)
using namespace Firedac::Vclui::Updateoptions;
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
#endif	// Firedac_Vclui_UpdateoptionsHPP
