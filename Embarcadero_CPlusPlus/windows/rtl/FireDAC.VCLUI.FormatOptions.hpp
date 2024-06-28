// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.VCLUI.FormatOptions.pas' rev: 34.00 (Windows)

#ifndef Firedac_Vclui_FormatoptionsHPP
#define Firedac_Vclui_FormatoptionsHPP

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
#include <Vcl.Grids.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.VCLUI.Controls.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Vclui
{
namespace Formatoptions
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmFDGUIxFormsFormatOptions;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TfrmFDGUIxFormsFormatOptions : public Vcl::Forms::TFrame
{
	typedef Vcl::Forms::TFrame inherited;
	
__published:
	Vcl::Extctrls::TPanel* mo_GroupBox1;
	Vcl::Extctrls::TPanel* mo_Panel3;
	Vcl::Grids::TStringGrid* mo_sgMapRules;
	Vcl::Stdctrls::TComboBox* mo_cbxDataType;
	Vcl::Extctrls::TPanel* mo_Panel2;
	Vcl::Extctrls::TPanel* mo_Panel5;
	Vcl::Stdctrls::TCheckBox* mo_cbOwnMapRules;
	Vcl::Extctrls::TPanel* mo_gb1;
	Vcl::Stdctrls::TLabel* mo_Label2;
	Vcl::Stdctrls::TLabel* mo_Label3;
	Vcl::Stdctrls::TEdit* mo_edtMaxBcdPrecision;
	Vcl::Stdctrls::TEdit* mo_edtMaxBcdScale;
	Vcl::Extctrls::TPanel* mo_gb2;
	Vcl::Stdctrls::TLabel* mo_Label1;
	Vcl::Stdctrls::TLabel* mo_Label10;
	Vcl::Stdctrls::TCheckBox* mo_cbStrsEmpty2Null;
	Vcl::Stdctrls::TCheckBox* mo_cbStrsTrim;
	Vcl::Stdctrls::TEdit* mo_edtMaxStringSize;
	Vcl::Stdctrls::TEdit* mo_edtInlineDataSize;
	Vcl::Buttons::TSpeedButton* mo_btnAddRule;
	Vcl::Buttons::TSpeedButton* mo_btnRemRule;
	Vcl::Extctrls::TPanel* mo_Panel6;
	Vcl::Stdctrls::TLabel* mo_Label6;
	Vcl::Stdctrls::TComboBox* mo_cbDefaultParamDataType;
	Vcl::Extctrls::TPanel* mo_Panel7;
	Vcl::Stdctrls::TCheckBox* mo_cbRound2Scale;
	Vcl::Stdctrls::TCheckBox* mo_cbDataSnapCompatibility;
	Vcl::Extctrls::TPanel* mo_Panel1;
	Vcl::Stdctrls::TLabel* mo_Label15;
	Vcl::Stdctrls::TEdit* mo_edtFmtDisplayDate;
	Vcl::Stdctrls::TLabel* mo_Label16;
	Vcl::Stdctrls::TEdit* mo_edtFmtDisplayTime;
	Vcl::Stdctrls::TLabel* mo_Label17;
	Vcl::Stdctrls::TEdit* mo_edtFmtDisplayDateTime;
	Vcl::Stdctrls::TLabel* mo_Label18;
	Vcl::Stdctrls::TEdit* mo_edtFmtDisplayNum;
	Vcl::Stdctrls::TLabel* mo_Label19;
	Vcl::Stdctrls::TEdit* mo_edtFmtEditNum;
	Vcl::Stdctrls::TCheckBox* mo_cbStrsTrim2Len;
	Vcl::Stdctrls::TCheckBox* mo_cbCheckPrecision;
	Vcl::Stdctrls::TCheckBox* mo_cbADOCompatibility;
	void __fastcall mo_cbOwnMapRulesClick(System::TObject* Sender);
	void __fastcall mo_btnAddRuleClick(System::TObject* Sender);
	void __fastcall mo_btnRemRuleClick(System::TObject* Sender);
	void __fastcall mo_sgMapRulesKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall mo_sgMapRulesSelectCell(System::TObject* Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall mo_sgMapRulesTopLeftChanged(System::TObject* Sender);
	void __fastcall mo_cbxDataTypeExit(System::TObject* Sender);
	void __fastcall mo_cbxDataTypeKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall mo_sgMapRulesEnter(System::TObject* Sender);
	void __fastcall mo_Change(System::TObject* Sender);
	
private:
	System::Classes::TNotifyEvent FOnModified;
	bool FLockModified;
	void __fastcall AdjustComboBox(Vcl::Stdctrls::TComboBox* ABox, int ACol, int ARow, Vcl::Grids::TStringGrid* AGrid);
	
public:
	void __fastcall LoadFrom(Firedac::Stan::Option::TFDFormatOptions* AOpts);
	void __fastcall SaveTo(Firedac::Stan::Option::TFDFormatOptions* AOpts);
	
__published:
	__property System::Classes::TNotifyEvent OnModified = {read=FOnModified, write=FOnModified};
public:
	/* TCustomFrame.Create */ inline __fastcall virtual TfrmFDGUIxFormsFormatOptions(System::Classes::TComponent* AOwner) : Vcl::Forms::TFrame(AOwner) { }
	
public:
	/* TScrollingWinControl.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFormsFormatOptions() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrmFDGUIxFormsFormatOptions(HWND ParentWindow) : Vcl::Forms::TFrame(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Formatoptions */
}	/* namespace Vclui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI_FORMATOPTIONS)
using namespace Firedac::Vclui::Formatoptions;
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
#endif	// Firedac_Vclui_FormatoptionsHPP
