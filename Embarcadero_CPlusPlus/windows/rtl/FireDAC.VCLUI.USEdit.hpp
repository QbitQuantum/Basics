// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.VCLUI.USEdit.pas' rev: 34.00 (Windows)

#ifndef Firedac_Vclui_UseditHPP
#define Firedac_Vclui_UseditHPP

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
#include <Vcl.ComCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.VCLUI.OptsBase.hpp>
#include <FireDAC.VCLUI.UpdateOptions.hpp>
#include <FireDAC.VCLUI.Controls.hpp>
#include <FireDAC.VCLUI.Memo.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Vclui
{
namespace Usedit
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmFDGUIxFormsUSEdit;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TfrmFDGUIxFormsUSEdit : public Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase
{
	typedef Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase inherited;
	
__published:
	Vcl::Comctrls::TPageControl* pcMain;
	Vcl::Comctrls::TTabSheet* tsGenerate;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TComboBox* cbxTableName;
	Vcl::Stdctrls::TButton* btnDSDefaults;
	Vcl::Stdctrls::TButton* btnGenSQL;
	Vcl::Stdctrls::TButton* btnServerInfo;
	Vcl::Stdctrls::TLabel* GroupBox2;
	Vcl::Stdctrls::TListBox* lbKeyFields;
	Vcl::Stdctrls::TLabel* GroupBox3;
	Vcl::Stdctrls::TListBox* lbUpdateFields;
	Vcl::Stdctrls::TLabel* GroupBox4;
	Vcl::Stdctrls::TListBox* lbRefetchFields;
	Vcl::Comctrls::TTabSheet* tsSQL;
	Vcl::Comctrls::TTabSheet* tsOptions;
	Firedac::Vclui::Controls::TFDGUIxFormsPanelTree* ptreeOptions;
	Vcl::Extctrls::TPanel* GroupBox5;
	Vcl::Stdctrls::TCheckBox* cbQuoteTabName;
	Vcl::Stdctrls::TCheckBox* cbQuoteColName;
	Firedac::Vclui::Updateoptions::TfrmFDGUIxFormsUpdateOptions* frmUpdateOptions;
	Vcl::Extctrls::TBevel* Bevel4;
	Vcl::Extctrls::TBevel* Bevel1;
	Vcl::Extctrls::TBevel* Bevel5;
	Vcl::Comctrls::TPageControl* pcSQL;
	Vcl::Comctrls::TTabSheet* tsInsert;
	Vcl::Comctrls::TTabSheet* tsModify;
	Vcl::Comctrls::TTabSheet* tsDelete;
	Vcl::Comctrls::TTabSheet* tsLock;
	Vcl::Comctrls::TTabSheet* tsUnlock;
	Vcl::Comctrls::TTabSheet* tsFetchRow;
	void __fastcall cbxTableNameDropDown(System::TObject* Sender);
	void __fastcall btnServerInfoClick(System::TObject* Sender);
	void __fastcall btnDSDefaultsClick(System::TObject* Sender);
	void __fastcall btnGenSQLClick(System::TObject* Sender);
	void __fastcall cbxTableNameExit(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall mmSQLExit(System::TObject* Sender);
	void __fastcall mmSQLKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall cbxTableNameChange(System::TObject* Sender);
	void __fastcall cbxTableNameClick(System::TObject* Sender);
	
private:
	Firedac::Comp::Client::TFDCustomConnection* FConnection;
	Firedac::Comp::Client::TFDAdaptedDataSet* FDataSet;
	Firedac::Comp::Client::TFDUpdateSQL* FUpdateSQL;
	Firedac::Stan::Option::_di_IFDStanOptions FOpts;
	void __fastcall UpdateExistSQLs();
	void __fastcall GenCommands();
	Firedac::Vclui::Memo::TFDGUIxFormsMemo* __fastcall GetSQL(int AIndex);
	bool __fastcall ExecuteBase(Firedac::Comp::Client::TFDUpdateSQL* AUpdSQL, const System::UnicodeString ACaption);
	bool __fastcall UseField(const System::UnicodeString AFieldName);
	
public:
	__classmethod bool __fastcall Execute(Firedac::Comp::Client::TFDUpdateSQL* AUpdSQL, const System::UnicodeString ACaption);
public:
	/* TfrmFDGUIxFormsOptsBase.Create */ inline __fastcall virtual TfrmFDGUIxFormsUSEdit(System::Classes::TComponent* AOwner) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(AOwner) { }
	
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmFDGUIxFormsUSEdit(System::Classes::TComponent* AOwner, int Dummy) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFormsUSEdit() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrmFDGUIxFormsUSEdit(HWND ParentWindow) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TfrmFDGUIxFormsUSEdit* frmFDGUIxFormsUSEdit;
}	/* namespace Usedit */
}	/* namespace Vclui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI_USEDIT)
using namespace Firedac::Vclui::Usedit;
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
#endif	// Firedac_Vclui_UseditHPP
