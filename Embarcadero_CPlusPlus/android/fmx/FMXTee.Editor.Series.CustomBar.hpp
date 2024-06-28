// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Series.CustomBar.pas' rev: 34.00 (Android)

#ifndef Fmxtee_Editor_Series_CustombarHPP
#define Fmxtee_Editor_Series_CustombarHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.Variants.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <System.Generics.Collections.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.SpinBox.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.TabControl.hpp>
#include <FMXTee.Series.hpp>
#include <FMXTee.Editor.Series.Bar.Stack.hpp>
#include <FMX.Colors.hpp>
#include <FMX.Layouts.hpp>
#include <FMXTee.Editor.Shadow.hpp>
#include <FMXTee.Editor.Brush.hpp>
#include <FMXTee.Editor.Stroke.hpp>
#include <FMXTee.Chart.GalleryPanel.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Series
{
namespace Custombar
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBarSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBarSeriesEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* PageControl1;
	Fmx::Tabcontrol::TTabItem* TabFormat;
	Fmx::Stdctrls::TLabel* LTransp;
	Fmx::Stdctrls::TGroupBox* GroupBox2;
	Fmx::Stdctrls::TCheckBox* CBColorEach;
	Fmx::Stdctrls::TCheckBox* CBRelative;
	Fmx::Stdctrls::TTrackBar* TBTransp;
	Fmx::Tabcontrol::TTabItem* TabSize;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Spinbox::TSpinBox* UDBarWidth;
	Fmx::Spinbox::TSpinBox* UDBarOffset;
	Fmx::Spinbox::TSpinBox* UDDepth;
	Fmx::Stdctrls::TCheckBox* CBBarSideMargins;
	Fmx::Stdctrls::TCheckBox* CBMarksAutoPosition;
	Fmx::Stdctrls::TGroupBox* GroupBox1;
	Fmx::Stdctrls::TLabel* Llocation;
	Fmx::Stdctrls::TCheckBox* cbMarksOnBar;
	Fmx::Listbox::TComboBox* CBLocation;
	Fmx::Tabcontrol::TTabItem* TabShadow;
	Fmx::Tabcontrol::TTabItem* TabEmboss;
	Fmx::Tabcontrol::TTabItem* TabBorder;
	Fmx::Colors::TComboColorBox* BColor;
	Fmx::Stdctrls::TGroupBox* GroupBox4;
	Fmx::Stdctrls::TTrackBar* TBSides;
	Fmx::Stdctrls::TCheckBox* CBDarkBar;
	Fmx::Stdctrls::TCheckBox* CBDefColor;
	Fmx::Tabcontrol::TTabItem* TabStyle;
	Fmx::Tabcontrol::TTabItem* TabPattern;
	Fmx::Tabcontrol::TTabItem* TabTickLines;
	Fmx::Stdctrls::TPanel* Panel1;
	Fmx::Stdctrls::TLabel* LStyle;
	Fmx::Listbox::TComboBox* CBBarStyle;
	Fmx::Listbox::TListBoxItem* ListBoxItem1;
	Fmx::Listbox::TListBoxItem* ListBoxItem2;
	Fmx::Listbox::TListBoxItem* ListBoxItem3;
	Fmx::Listbox::TListBoxItem* ListBoxItem4;
	Fmx::Listbox::TListBoxItem* ListBoxItem5;
	Fmx::Listbox::TListBoxItem* ListBoxItem6;
	Fmx::Listbox::TListBoxItem* ListBoxItem7;
	Fmx::Listbox::TListBoxItem* ListBoxItem8;
	Fmx::Listbox::TListBoxItem* ListBoxItem9;
	Fmx::Listbox::TListBoxItem* ListBoxItem10;
	Fmx::Listbox::TListBoxItem* ListBoxItem11;
	Fmx::Listbox::TListBoxItem* ListBoxItem12;
	Fmx::Listbox::TListBoxItem* ListBoxItem13;
	Fmx::Listbox::TListBoxItem* ListBoxItem14;
	Fmx::Listbox::TListBoxItem* ListBoxItem15;
	Fmxtee::Chart::Gallerypanel::TChartGalleryPanel* BarGallery;
	Fmx::Tabcontrol::TTabControl* TabControl1;
	Fmx::Tabcontrol::TTabItem* TabItem1;
	Fmx::Tabcontrol::TTabItem* TabPen;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Spinbox::TSpinBox* UDDarkPen;
	Fmx::Stdctrls::TLabel* LBevel;
	Fmx::Spinbox::TSpinBox* UDBevel;
	Fmx::Stdctrls::TGroupBox* GroupBox3;
	Fmx::Stdctrls::TLabel* Label5;
	Fmx::Stdctrls::TLabel* Label6;
	Fmx::Stdctrls::TCheckBox* CBRound;
	Fmx::Spinbox::TSpinBox* UDRoundSize;
	Fmx::Listbox::TComboBox* CBBarRound;
	Fmx::Listbox::TListBoxItem* ListBoxItem19;
	Fmx::Listbox::TListBoxItem* ListBoxItem20;
	Fmx::Listbox::TListBoxItem* ListBoxItem21;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall CBBarStyleChange(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall CBLocationChange(System::TObject* Sender);
	void __fastcall CBBarRoundChange(System::TObject* Sender);
	void __fastcall CBColorEachChange(System::TObject* Sender);
	void __fastcall CBDarkBarChange(System::TObject* Sender);
	void __fastcall CBBarSideMarginsChange(System::TObject* Sender);
	void __fastcall CBMarksAutoPositionChange(System::TObject* Sender);
	void __fastcall cbMarksOnBarChange(System::TObject* Sender);
	void __fastcall FormActivate(System::TObject* Sender);
	void __fastcall CBRelativeChange(System::TObject* Sender);
	void __fastcall CBRoundChange(System::TObject* Sender);
	void __fastcall BColorChange(System::TObject* Sender);
	void __fastcall UDDepthChange(System::TObject* Sender);
	void __fastcall UDBarWidthChange(System::TObject* Sender);
	void __fastcall UDBarOffsetChange(System::TObject* Sender);
	void __fastcall UDDarkPenChange(System::TObject* Sender);
	void __fastcall UDBevelChange(System::TObject* Sender);
	void __fastcall UDRoundSizeChange(System::TObject* Sender);
	void __fastcall TBSidesChange(System::TObject* Sender);
	void __fastcall TabControl1Change(System::TObject* Sender);
	void __fastcall BarGalleryChangeChart(System::TObject* Sender);
	void __fastcall CBDefColorChange(System::TObject* Sender);
	
private:
	Fmxtee::Series::TCustomBarSeries* Bar;
	bool CreatingForm;
	bool ISelecting;
	Fmxtee::Editor::Stroke::TStrokeEditor* IBorderEditor;
	Fmxtee::Editor::Series::Bar::Stack::TStackBarSeriesEditor* IStackEditor;
	Fmxtee::Editor::Brush::TBrushEditor* IPatternEditor;
	Fmxtee::Editor::Stroke::TStrokeEditor* ITicksEditor;
	Fmxtee::Editor::Shadow::TShadowEditor* IShadowEditor;
	Fmxtee::Editor::Shadow::TShadowEditor* IEmbossEditor;
	void __fastcall RefreshBar(Fmxtee::Series::TCustomBarSeries* const ABar);
	
public:
	__classmethod Fmx::Forms::TForm* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Series::TCustomBarSeries* const ABar);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TBarSeriesEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TBarSeriesEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TBarSeriesEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Custombar */
}	/* namespace Series */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_SERIES_CUSTOMBAR)
using namespace Fmxtee::Editor::Series::Custombar;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_SERIES)
using namespace Fmxtee::Editor::Series;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR)
using namespace Fmxtee::Editor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE)
using namespace Fmxtee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmxtee_Editor_Series_CustombarHPP
