// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeDBCrossTabEditor.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeedbcrosstabeditorHPP
#define Vcltee_TeedbcrosstabeditorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Data.DB.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.DBChart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeeSourceEdit.hpp>
#include <VCLTee.TeeDBEdit.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeDBCrossTab.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teedbcrosstabeditor
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBChartCrossTabEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBChartCrossTabEditor : public Vcltee::Teedbedit::TBaseDBChartEditor
{
	typedef Vcltee::Teedbedit::TBaseDBChartEditor inherited;
	
__published:
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* Label3;
	Vcltee::Tecanvas::TComboFlat* CBAgg;
	Vcltee::Tecanvas::TComboFlat* CBValue;
	Vcltee::Tecanvas::TComboFlat* CBGroup;
	Vcl::Stdctrls::TLabel* Label4;
	Vcltee::Tecanvas::TComboFlat* CBLabels;
	Vcl::Stdctrls::TCheckBox* CBActive;
	Vcl::Stdctrls::TCheckBox* CBCase;
	Vcl::Stdctrls::TCheckBox* CBHide;
	Vcl::Extctrls::TPanel* PanelButtons;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Stdctrls::TButton* BOK;
	Vcl::Stdctrls::TCheckBox* CBKeepData;
	HIDESBASE void __fastcall CBSourcesChange(System::TObject* Sender);
	HIDESBASE void __fastcall FormShow(System::TObject* Sender);
	void __fastcall BApplyClick(System::TObject* Sender);
	void __fastcall CBAggChange(System::TObject* Sender);
	HIDESBASE void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall CBActiveClick(System::TObject* Sender);
	void __fastcall CBCaseClick(System::TObject* Sender);
	void __fastcall CBHideClick(System::TObject* Sender);
	void __fastcall CBKeepDataClick(System::TObject* Sender);
	
private:
	Vcltee::Teedbcrosstab::TDBCrossTabSource* DataSource;
	void __fastcall EnableCombos();
	
public:
	DYNAMIC void __fastcall Translate();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TDBChartCrossTabEditor(System::Classes::TComponent* AOwner) : Vcltee::Teedbedit::TBaseDBChartEditor(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TDBChartCrossTabEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcltee::Teedbedit::TBaseDBChartEditor(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TDBChartCrossTabEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDBChartCrossTabEditor(HWND ParentWindow) : Vcltee::Teedbedit::TBaseDBChartEditor(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teedbcrosstabeditor */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEDBCROSSTABEDITOR)
using namespace Vcltee::Teedbcrosstabeditor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeedbcrosstabeditorHPP
