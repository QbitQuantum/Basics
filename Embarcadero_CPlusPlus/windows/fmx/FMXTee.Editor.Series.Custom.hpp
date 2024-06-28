// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Series.Custom.pas' rev: 34.00 (Windows)

#ifndef Fmxtee_Editor_Series_CustomHPP
#define Fmxtee_Editor_Series_CustomHPP

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
#include <FMX.StdCtrls.hpp>
#include <FMX.ComboTrackBar.hpp>
#include <FMX.SpinBox.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Dialogs.hpp>
#include <FMXTee.Series.hpp>
#include <FMX.TabControl.hpp>
#include <FMXTee.Canvas.hpp>
#include <FMXTee.Editor.Stroke.hpp>
#include <FMXTee.Editor.Brush.hpp>
#include <FMXTee.Engine.hpp>
#include <FMXTee.Editor.Shadow.hpp>
#include <FMXTee.Procs.hpp>
#include <FMXTee.Editor.Series.Pointer.hpp>
#include <FMX.Colors.hpp>
#include <FMX.Layouts.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Series
{
namespace Custom
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomSeriesEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* TabControl1;
	Fmx::Tabcontrol::TTabItem* TabFormat;
	Fmx::Tabcontrol::TTabItem* TabOptions;
	Fmx::Tabcontrol::TTabItem* TabBorder;
	Fmx::Tabcontrol::TTabItem* TabPattern;
	Fmx::Tabcontrol::TTabItem* TabShadow;
	Fmx::Tabcontrol::TTabItem* TabEmboss;
	Fmx::Tabcontrol::TTabItem* TabOutline;
	Fmx::Stdctrls::TCheckBox* CBDark3D;
	Fmx::Stdctrls::TCheckBox* CBColorEach;
	Fmx::Stdctrls::TCheckBox* CBColorEachLine;
	Fmx::Stdctrls::TLabel* LTransp;
	Fmx::Stdctrls::TTrackBar* TBTransp;
	Fmx::Stdctrls::TGroupBox* GBStair;
	Fmx::Stdctrls::TCheckBox* CBStairs;
	Fmx::Stdctrls::TCheckBox* CBInvStairs;
	Fmx::Stdctrls::TCheckBox* CBSmoothed;
	Fmx::Stdctrls::TCheckBox* CBClick;
	Fmx::Stdctrls::TLabel* LHeight;
	Fmx::Spinbox::TSpinBox* UDHeight;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Listbox::TComboBox* CBStack;
	Fmx::Listbox::TListBoxItem* ListBoxItem1;
	Fmx::Listbox::TListBoxItem* ListBoxItem2;
	Fmx::Listbox::TListBoxItem* ListBoxItem3;
	Fmx::Listbox::TListBoxItem* ListBoxItem4;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Listbox::TComboBox* CBNulls;
	Fmx::Listbox::TListBoxItem* ListBoxItem5;
	Fmx::Listbox::TListBoxItem* ListBoxItem6;
	Fmx::Listbox::TListBoxItem* ListBoxItem7;
	Fmx::Stdctrls::TLabel* LDrawStyle;
	Fmx::Listbox::TComboBox* CBDrawStyle;
	Fmx::Listbox::TListBoxItem* ListBoxItem8;
	Fmx::Listbox::TListBoxItem* ListBoxItem9;
	Fmx::Listbox::TListBoxItem* ListBoxItem10;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Combotrackbar::TComboTrackBar* UDTolerance;
	Fmx::Stdctrls::TCheckBox* CBDefColor;
	Fmx::Colors::TComboColorBox* BLineColor;
	Fmx::Tabcontrol::TTabItem* TabPointer;
	Fmx::Stdctrls::TCheckBox* CBPointerBehind;
	Fmx::Layouts::TLayout* Layout1;
	Fmx::Stdctrls::TCheckBox* CBInflate;
	void __fastcall CBStackChange(System::TObject* Sender);
	void __fastcall CBNullsChange(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall CBStairsChange(System::TObject* Sender);
	void __fastcall CBInvStairsChange(System::TObject* Sender);
	void __fastcall CBSmoothedChange(System::TObject* Sender);
	void __fastcall CBColorEachChange(System::TObject* Sender);
	void __fastcall CBDark3DChange(System::TObject* Sender);
	void __fastcall CBClickChange(System::TObject* Sender);
	void __fastcall CBColorEachLineChange(System::TObject* Sender);
	void __fastcall FormActivate(System::TObject* Sender);
	void __fastcall UDHeightChange(System::TObject* Sender);
	void __fastcall TabControl1Change(System::TObject* Sender);
	void __fastcall CBDrawStyleChange(System::TObject* Sender);
	void __fastcall UDToleranceChange(System::TObject* Sender);
	void __fastcall CBDefColorChange(System::TObject* Sender);
	void __fastcall BLineColorChange(System::TObject* Sender);
	void __fastcall CBPointerBehindChange(System::TObject* Sender);
	void __fastcall CBInflateChange(System::TObject* Sender);
	
private:
	Fmxtee::Series::TCustomSeries* Custom;
	Fmxtee::Editor::Stroke::TStrokeEditor* IBorderEditor;
	Fmx::Forms::TForm* IShadowEditor;
	Fmx::Forms::TForm* IEmbossEditor;
	Fmxtee::Editor::Brush::TBrushEditor* IPatternEditor;
	Fmxtee::Editor::Stroke::TStrokeEditor* IOutlineEditor;
	Fmxtee::Editor::Series::Pointer::TSeriesPointerEditor* IPointerEditor;
	void __fastcall CheckDefColor();
	void __fastcall RefreshCustom(Fmxtee::Series::TCustomSeries* const ACustom);
	
public:
	__classmethod Fmx::Forms::TForm* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Series::TCustomSeries* const ACustom);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TCustomSeriesEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TCustomSeriesEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TCustomSeriesEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Custom */
}	/* namespace Series */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_SERIES_CUSTOM)
using namespace Fmxtee::Editor::Series::Custom;
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
#endif	// Fmxtee_Editor_Series_CustomHPP
