// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeDBSumEdit.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeedbsumeditHPP
#define Vcltee_TeedbsumeditHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeSourceEdit.hpp>
#include <VCLTee.TeeDBEdit.hpp>
#include <VCLTee.DBChart.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teedbsumedit
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBChartSumEditor;
class DELPHICLASS TDBSummarySource;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBChartSumEditor : public Vcltee::Teedbedit::TBaseDBChartEditor
{
	typedef Vcltee::Teedbedit::TBaseDBChartEditor inherited;
	
__published:
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* Label2;
	Vcltee::Tecanvas::TComboFlat* CBAgg;
	Vcltee::Tecanvas::TComboFlat* CBValue;
	Vcltee::Tecanvas::TComboFlat* CBGroup;
	Vcltee::Tecanvas::TComboFlat* CBTimeStep;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TLabel* Label4;
	Vcltee::Tecanvas::TComboFlat* CBSort;
	Vcltee::Tecanvas::TComboFlat* CBSortType;
	Vcl::Extctrls::TPanel* PanelButtons;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Stdctrls::TButton* BOK;
	void __fastcall CBAggChange(System::TObject* Sender);
	void __fastcall CBGroupChange(System::TObject* Sender);
	void __fastcall BApplyClick(System::TObject* Sender);
	HIDESBASE void __fastcall FormShow(System::TObject* Sender);
	HIDESBASE void __fastcall CBSourcesChange(System::TObject* Sender);
	void __fastcall CBSortChange(System::TObject* Sender);
	void __fastcall CBSortTypeChange(System::TObject* Sender);
	HIDESBASE void __fastcall FormCreate(System::TObject* Sender);
	
private:
	void __fastcall CheckCount();
	void __fastcall EnableCombos();
	void __fastcall EnableTimeStep();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TDBChartSumEditor(System::Classes::TComponent* AOwner) : Vcltee::Teedbedit::TBaseDBChartEditor(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TDBChartSumEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcltee::Teedbedit::TBaseDBChartEditor(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TDBChartSumEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDBChartSumEditor(HWND ParentWindow) : Vcltee::Teedbedit::TBaseDBChartEditor(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TDBSummarySource : public Vcltee::Dbchart::TTeeSeriesDBSource
{
	typedef Vcltee::Dbchart::TTeeSeriesDBSource inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Description();
	__classmethod virtual System::Classes::TComponentClass __fastcall Editor();
	__classmethod virtual bool __fastcall HasSeries(Vcltee::Teengine::TChartSeries* ASeries);
public:
	/* TTeeSeriesSource.Create */ inline __fastcall virtual TDBSummarySource(System::Classes::TComponent* AOwner) : Vcltee::Dbchart::TTeeSeriesDBSource(AOwner) { }
	/* TTeeSeriesSource.Destroy */ inline __fastcall virtual ~TDBSummarySource() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall TeeDBSummaryEditor(System::Classes::TComponent* AOwner, Vcltee::Teengine::TChartSeries* ASeries);
}	/* namespace Teedbsumedit */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEDBSUMEDIT)
using namespace Vcltee::Teedbsumedit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeedbsumeditHPP
