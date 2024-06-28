// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeBarEdit.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeebareditHPP
#define Vcltee_TeebareditHPP

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
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeVisualsEditor.hpp>
#include <VCLTee.TeeGalleryPanel.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teebaredit
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBarSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBarSeriesEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcl::Comctrls::TTabSheet* TabSheet2;
	Vcl::Stdctrls::TGroupBox* GroupBox2;
	Vcl::Stdctrls::TCheckBox* CBColorEach;
	Vcltee::Tecanvas::TButtonColor* BBarColor;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TEdit* SEBarwidth;
	Vcl::Stdctrls::TEdit* SEBarOffset;
	Vcl::Comctrls::TUpDown* UDBarWidth;
	Vcl::Comctrls::TUpDown* UDBarOffset;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TEdit* Edit1;
	Vcl::Comctrls::TUpDown* UDDepth;
	Vcl::Stdctrls::TCheckBox* CBBarSideMargins;
	Vcl::Stdctrls::TCheckBox* CBMarksAutoPosition;
	Vcl::Comctrls::TTabSheet* TabShadow;
	Vcl::Comctrls::TTabSheet* TabBorder;
	Vcl::Stdctrls::TLabel* LTransp;
	Vcl::Comctrls::TTrackBar* TBTransp;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcl::Stdctrls::TCheckBox* cbMarksOnBar;
	Vcl::Stdctrls::TLabel* Llocation;
	Vcltee::Tecanvas::TComboFlat* cbLocation;
	Vcl::Comctrls::TTabSheet* TabEmboss;
	Vcl::Comctrls::TTabSheet* TabVisual;
	Vcl::Stdctrls::TGroupBox* GroupBox4;
	Vcl::Comctrls::TTrackBar* TBSides;
	Vcl::Stdctrls::TCheckBox* CBDarkBar;
	Vcl::Comctrls::TTabSheet* TabBrush;
	Vcl::Stdctrls::TCheckBox* CBDefColor;
	Vcl::Comctrls::TTabSheet* TabStyle;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TLabel* LStyle;
	Vcltee::Tecanvas::TComboFlat* CBBarStyle;
	Vcltee::Teegallerypanel::TChartGalleryPanel* BarGallery;
	Vcl::Comctrls::TPageControl* PageControl2;
	Vcl::Comctrls::TTabSheet* TabBorderOptions;
	Vcl::Comctrls::TTabSheet* TabBorderFormat;
	Vcl::Stdctrls::TLabel* LBevel;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TEdit* EBevel;
	Vcl::Comctrls::TUpDown* UDBevel;
	Vcl::Stdctrls::TEdit* Edit2;
	Vcl::Comctrls::TUpDown* UDDarkPen;
	Vcl::Stdctrls::TGroupBox* GroupBox3;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Stdctrls::TLabel* Label6;
	Vcl::Stdctrls::TCheckBox* CBRound;
	Vcl::Stdctrls::TEdit* ERoundSize;
	Vcl::Comctrls::TUpDown* UDRoundSize;
	Vcltee::Tecanvas::TComboFlat* cbBarRound;
	Vcl::Stdctrls::TCheckBox* CBRelative;
	Vcl::Comctrls::TTabSheet* TabTicks;
	Vcl::Comctrls::TTrackBar* TBCone;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall SEBarwidthChange(System::TObject* Sender);
	void __fastcall CBBarStyleChange(System::TObject* Sender);
	void __fastcall CBColorEachClick(System::TObject* Sender);
	void __fastcall CBDarkBarClick(System::TObject* Sender);
	void __fastcall CBBarSideMarginsClick(System::TObject* Sender);
	void __fastcall SEBarOffsetChange(System::TObject* Sender);
	void __fastcall CBMarksAutoPositionClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall EBevelChange(System::TObject* Sender);
	void __fastcall Edit1Change(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall Edit2Change(System::TObject* Sender);
	void __fastcall CBRelativeClick(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall cbMarksOnBarClick(System::TObject* Sender);
	void __fastcall cbLocationChange(System::TObject* Sender);
	void __fastcall CBRoundClick(System::TObject* Sender);
	void __fastcall ERoundSizeChange(System::TObject* Sender);
	void __fastcall cbBarRoundChange(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall TBSidesChange(System::TObject* Sender);
	void __fastcall CBDefColorClick(System::TObject* Sender);
	void __fastcall BBarColorClick(System::TObject* Sender);
	void __fastcall BarGalleryChangeChart(System::TObject* Sender);
	void __fastcall PageControl2Change(System::TObject* Sender);
	void __fastcall TBConeChange(System::TObject* Sender);
	
private:
	bool CreatingForm;
	Vcltee::Series::TCustomBarSeries* Bar;
	Vcl::Forms::TCustomForm* FStackEditor;
	Vcltee::Teependlg::TPenDialog* IBorderEditor;
	bool ISelecting;
	Vcltee::Teevisualseditor::TVisualsEditor* IVisualEditor;
	void __fastcall AddStackBarEditor();
	void __fastcall ChangedVisual(System::TObject* Sender);
	void __fastcall CheckControls();
	void __fastcall RefreshShape();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TBarSeriesEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TBarSeriesEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TBarSeriesEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TBarSeriesEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teebaredit */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEBAREDIT)
using namespace Vcltee::Teebaredit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeebareditHPP
