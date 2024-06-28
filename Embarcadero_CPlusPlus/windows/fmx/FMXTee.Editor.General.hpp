// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.General.pas' rev: 34.00 (Windows)

#ifndef Fmxtee_Editor_GeneralHPP
#define Fmxtee_Editor_GeneralHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Variants.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.SpinBox.hpp>
#include <FMXTee.Chart.hpp>
#include <FMXTee.RadioGroup.hpp>
#include <FMXTee.Editor.Font.hpp>
#include <FMXTee.Canvas.hpp>
#include <FMX.Objects.hpp>
#include <FMXTee.Editor.Stroke.hpp>
#include <FMXTee.Editor.Brush.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace General
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TGeneralEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TGeneralEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* PageControl1;
	Fmx::Tabcontrol::TTabItem* TabZoom;
	Fmx::Tabcontrol::TTabItem* TabScroll;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Listbox::TComboBox* CBScrollMouse;
	Fmx::Stdctrls::TCheckBox* CBInsideBounds;
	Fmx::Tabcontrol::TTabItem* TabCursor;
	Fmx::Tabcontrol::TTabItem* TabFont;
	Fmx::Stdctrls::TSplitter* Splitter1;
	Fmx::Listbox::TListBox* LBFonts;
	Fmx::Stdctrls::TPanel* Panel1;
	Fmx::Stdctrls::TPanel* PanelFont;
	Fmx::Stdctrls::TPanel* Panel2;
	Fmx::Stdctrls::TLabel* LTextSize;
	Fmx::Stdctrls::TLabel* Label5;
	Fmx::Stdctrls::TCheckBox* CBAllFonts;
	Fmx::Spinbox::TSpinBox* UDTextSize;
	Fmx::Listbox::TComboBox* CBZoomText;
	Fmx::Tabcontrol::TTabItem* TabPalette;
	Fmx::Listbox::TListBox* LBPalette;
	Fmxtee::Radiogroup::TRadioGroup* RGScroll;
	Fmx::Listbox::TListBox* LBCursor;
	Fmx::Objects::TPaintBox* PaintBox1;
	Fmx::Tabcontrol::TTabItem* TabMouse;
	Fmx::Stdctrls::TGroupBox* GroupBox1;
	Fmx::Stdctrls::TLabel* Label8;
	Fmx::Stdctrls::TLabel* Label9;
	Fmx::Stdctrls::TLabel* Label10;
	Fmx::Listbox::TComboBox* CBLeftButton;
	Fmx::Listbox::TListBoxItem* ListBoxItem13;
	Fmx::Listbox::TListBoxItem* ListBoxItem14;
	Fmx::Listbox::TListBoxItem* ListBoxItem15;
	Fmx::Listbox::TComboBox* CBMidButton;
	Fmx::Listbox::TListBoxItem* ListBoxItem16;
	Fmx::Listbox::TListBoxItem* ListBoxItem17;
	Fmx::Listbox::TListBoxItem* ListBoxItem18;
	Fmx::Listbox::TComboBox* CBRightButton;
	Fmx::Listbox::TListBoxItem* ListBoxItem19;
	Fmx::Listbox::TListBoxItem* ListBoxItem20;
	Fmx::Listbox::TListBoxItem* ListBoxItem21;
	Fmx::Stdctrls::TGroupBox* GroupBox2;
	Fmx::Stdctrls::TRadioButton* RBWheelNone;
	Fmx::Stdctrls::TRadioButton* RGWheelScroll;
	Fmx::Stdctrls::TRadioButton* RGWheelData;
	Fmx::Stdctrls::TRadioButton* RGWheelChart;
	Fmx::Stdctrls::TCheckBox* CBInvWheel;
	Fmx::Tabcontrol::TTabControl* TabControlZoom;
	Fmx::Tabcontrol::TTabItem* TabItem1;
	Fmx::Tabcontrol::TTabItem* TabZoomBorder;
	Fmx::Tabcontrol::TTabItem* TabZoomPattern;
	Fmx::Stdctrls::TCheckBox* CBAllowZoom;
	Fmx::Stdctrls::TCheckBox* CBAnimatedZoom;
	Fmx::Stdctrls::TLabel* LSteps;
	Fmx::Spinbox::TSpinBox* UDAniZoomSteps;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Spinbox::TSpinBox* UDMinPix;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Listbox::TComboBox* CBDir;
	Fmx::Listbox::TListBoxItem* ListBoxItem1;
	Fmx::Listbox::TListBoxItem* ListBoxItem2;
	Fmx::Listbox::TListBoxItem* ListBoxItem3;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Listbox::TComboBox* CBZoomMouse;
	Fmx::Listbox::TListBoxItem* ListBoxItem4;
	Fmx::Listbox::TListBoxItem* ListBoxItem5;
	Fmx::Listbox::TListBoxItem* ListBoxItem6;
	Fmx::Stdctrls::TCheckBox* CBUpLeft;
	Fmx::Stdctrls::TCheckBox* CBHistory;
	Fmx::Stdctrls::TCheckBox* CBZoomAspect;
	Fmx::Layouts::TLayout* Layout1;
	Fmx::Stdctrls::TLabel* Label7;
	Fmx::Layouts::TLayout* Layout2;
	Fmx::Stdctrls::TLabel* Label11;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall CBDirChange(System::TObject* Sender);
	void __fastcall CBZoomMouseChange(System::TObject* Sender);
	void __fastcall CBScrollMouseChange(System::TObject* Sender);
	void __fastcall LBFontsKeyDown(System::TObject* Sender, System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	void __fastcall ETextSizeChange(System::TObject* Sender);
	void __fastcall CBZoomTextChange(System::TObject* Sender);
	void __fastcall CBAllowZoomChange(System::TObject* Sender);
	void __fastcall CBAnimatedZoomChange(System::TObject* Sender);
	void __fastcall UDAniZoomStepsChangeTracking(System::TObject* Sender);
	void __fastcall UDMinPixChangeTracking(System::TObject* Sender);
	void __fastcall CBUpLeftChange(System::TObject* Sender);
	void __fastcall CBHistoryChange(System::TObject* Sender);
	void __fastcall CBZoomAspectChange(System::TObject* Sender);
	void __fastcall CBInsideBoundsChange(System::TObject* Sender);
	void __fastcall CBAllFontsChange(System::TObject* Sender);
	void __fastcall LBPaletteChange(System::TObject* Sender);
	void __fastcall RGScrollChange(System::TObject* Sender);
	void __fastcall UDTextSizeChangeTracking(System::TObject* Sender);
	void __fastcall LBFontsChange(System::TObject* Sender);
	void __fastcall LBCursorChange(System::TObject* Sender);
	void __fastcall PaintBox1Paint(System::TObject* Sender, Fmx::Graphics::TCanvas* const Canvas);
	void __fastcall UDTextSizeChange(System::TObject* Sender);
	void __fastcall TabControlZoomChange(System::TObject* Sender);
	void __fastcall CBLeftButtonChange(System::TObject* Sender);
	void __fastcall CBRightButtonChange(System::TObject* Sender);
	void __fastcall CBMidButtonChange(System::TObject* Sender);
	void __fastcall RBWheelNoneChange(System::TObject* Sender);
	void __fastcall CBInvWheelChange(System::TObject* Sender);
	
private:
	Fmxtee::Chart::TCustomChart* Chart;
	Fmxtee::Canvas::TTeeFont* IFont;
	Fmxtee::Canvas::TTeeFont* IBackup;
	Fmxtee::Editor::Font::TFontEditor* IFontEditor;
	System::Classes::TNotifyEvent OldChange;
	bool Changing;
	Fmxtee::Editor::Stroke::TStrokeEditor* IZoomBorder;
	Fmxtee::Editor::Brush::TBrushEditor* IZoomPattern;
	void __fastcall FillCursors();
	void __fastcall ChangedFont(System::TObject* Sender);
	void __fastcall CheckMouseButton(Fmx::Listbox::TComboBox* const Combo1, Fmx::Listbox::TComboBox* const Combo2, const System::Uitypes::TMouseButton Button1, const System::Uitypes::TMouseButton Button2);
	void __fastcall FillFonts();
	void __fastcall FillPalette();
	__classmethod void __fastcall GetChartObjects(Fmxtee::Chart::TCustomChart* const AChart, Fmx::Listbox::TCustomListBox* const AList, bool WithFonts = false);
	void __fastcall RefreshChart(Fmxtee::Chart::TCustomChart* const AChart);
	void __fastcall ResetIFont();
	Fmxtee::Canvas::TTeeFont* __fastcall SelectedFont(int Index);
	HIDESBASE void __fastcall SetCursor();
	void __fastcall SetPalette();
	
public:
	__classmethod Fmx::Forms::TForm* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Chart::TCustomChart* const AChart);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TGeneralEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TGeneralEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TGeneralEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace General */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_GENERAL)
using namespace Fmxtee::Editor::General;
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
#endif	// Fmxtee_Editor_GeneralHPP
