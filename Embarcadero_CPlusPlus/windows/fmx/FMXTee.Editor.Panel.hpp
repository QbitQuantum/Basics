// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Panel.pas' rev: 34.00 (Windows)

#ifndef Fmxtee_Editor_PanelHPP
#define Fmxtee_Editor_PanelHPP

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
#include <FMX.SpinBox.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Ani.hpp>
#include <FMXTee.Chart.hpp>
#include <FMX.Colors.hpp>
#include <FMXTee.Editor.Gradient.hpp>
#include <FMX.Layouts.hpp>
#include <FMXTee.Editor.Stroke.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Panel
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPanelEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPanelEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* PageControl1;
	Fmx::Tabcontrol::TTabItem* TabBack;
	Fmx::Colors::TComboColorBox* BPanelColor;
	Fmx::Stdctrls::TCheckBox* CBColorDef;
	Fmx::Stdctrls::TCheckBox* CBImageInside;
	Fmx::Tabcontrol::TTabItem* TabBorders;
	Fmx::Tabcontrol::TTabItem* TabMargins;
	Fmx::Stdctrls::TGroupBox* GBMargins;
	Fmx::Stdctrls::TLabel* Label5;
	Fmx::Spinbox::TSpinBox* UDTopMa;
	Fmx::Spinbox::TSpinBox* UDRightMa;
	Fmx::Spinbox::TSpinBox* UDLeftMa;
	Fmx::Spinbox::TSpinBox* UDBotMa;
	Fmx::Listbox::TComboBox* CBMarUnits;
	Fmx::Tabcontrol::TTabItem* TabGradient;
	Fmx::Tabcontrol::TTabItem* TabShadow;
	Fmx::Tabcontrol::TTabItem* TabEmboss;
	Fmx::Tabcontrol::TTabItem* TabImage;
	Fmx::Tabcontrol::TTabControl* TabControlBorders;
	Fmx::Tabcontrol::TTabItem* TabBorder;
	Fmx::Tabcontrol::TTabItem* TabBevels;
	Fmx::Layouts::TLayout* Layout1;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Spinbox::TSpinBox* UDRound;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Listbox::TComboBox* CBInner;
	Fmx::Listbox::TListBoxItem* ListBoxItem1;
	Fmx::Listbox::TListBoxItem* ListBoxItem2;
	Fmx::Listbox::TListBoxItem* ListBoxItem3;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Listbox::TComboBox* CBOuter;
	Fmx::Listbox::TListBoxItem* ListBoxItem4;
	Fmx::Listbox::TListBoxItem* ListBoxItem5;
	Fmx::Listbox::TListBoxItem* ListBoxItem6;
	Fmx::Stdctrls::TLabel* L2;
	Fmx::Spinbox::TSpinBox* UDPanelWi;
	Fmx::Stdctrls::TLabel* L19;
	Fmx::Spinbox::TSpinBox* UDPanelBor;
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall CBInnerChange(System::TObject* Sender);
	void __fastcall CBOuterChange(System::TObject* Sender);
	void __fastcall CBMarUnitsChange(System::TObject* Sender);
	void __fastcall CBImageInsideChange(System::TObject* Sender);
	void __fastcall CBColorDefChange(System::TObject* Sender);
	void __fastcall UDPanelWiChange(System::TObject* Sender);
	void __fastcall UDPanelBorChange(System::TObject* Sender);
	void __fastcall UDRoundChange(System::TObject* Sender);
	void __fastcall UDTopMaChange(System::TObject* Sender);
	void __fastcall UDBotMaChange(System::TObject* Sender);
	void __fastcall UDLeftMaChange(System::TObject* Sender);
	void __fastcall UDRightMaChange(System::TObject* Sender);
	void __fastcall BPanelColorChange(System::TObject* Sender);
	void __fastcall TabControlBordersChange(System::TObject* Sender);
	
private:
	Fmxtee::Chart::TCustomChart* Chart;
	Fmxtee::Editor::Stroke::TStrokeEditor* IBorder;
	Fmx::Forms::TForm* IPicture;
	Fmx::Forms::TForm* IShadow;
	Fmx::Forms::TForm* IEmboss;
	Fmx::Forms::TForm* IGradient;
	void __fastcall RefreshChart(Fmxtee::Chart::TCustomChart* const AChart);
	
public:
	__classmethod Fmx::Forms::TForm* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Chart::TCustomChart* const AChart);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TPanelEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TPanelEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TPanelEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Panel */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_PANEL)
using namespace Fmxtee::Editor::Panel;
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
#endif	// Fmxtee_Editor_PanelHPP
