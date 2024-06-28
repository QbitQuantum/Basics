// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Legend.pas' rev: 34.00 (iOS)

#ifndef Fmxtee_Editor_LegendHPP
#define Fmxtee_Editor_LegendHPP

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
#include <FMX.ListBox.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Memo.hpp>
#include <FMX.SpinBox.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.TabControl.hpp>
#include <FMXTee.Chart.hpp>
#include <FMXTee.Editor.Symbol.hpp>
#include <FMXTee.Editor.TextShape.hpp>
#include <FMXTee.RadioGroup.hpp>
#include <FMXTee.Editor.CustomShape.hpp>
#include <FMXTee.Editor.Stroke.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Legend
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TLegendEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TLegendEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* PageControl1;
	Fmx::Tabcontrol::TTabItem* TabStyle;
	Fmx::Stdctrls::TLabel* L12;
	Fmx::Stdctrls::TLabel* L7;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TCheckBox* CBShow;
	Fmx::Stdctrls::TCheckBox* CBInverted;
	Fmx::Listbox::TComboBox* CBLegendStyle;
	Fmx::Listbox::TComboBox* CBLegStyle;
	Fmx::Spinbox::TSpinBox* UDVertSpacing;
	Fmx::Stdctrls::TCheckBox* CBFontColor;
	Fmx::Listbox::TComboBox* CBCheckBoxes;
	Fmx::Tabcontrol::TTabItem* TabPosition;
	Fmx::Stdctrls::TLabel* L10;
	Fmx::Stdctrls::TLabel* L1;
	Fmx::Stdctrls::TCheckBox* CBResizeChart;
	Fmx::Spinbox::TSpinBox* UDTopPos;
	Fmx::Spinbox::TSpinBox* UDMargin;
	Fmx::Stdctrls::TGroupBox* GroupBox1;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Stdctrls::TLabel* Label5;
	Fmx::Spinbox::TSpinBox* UDLeft;
	Fmx::Spinbox::TSpinBox* UDTop;
	Fmx::Stdctrls::TCheckBox* CBCustPos;
	Fmx::Stdctrls::TCheckBox* CBPosPercent;
	Fmx::Tabcontrol::TTabItem* TabSymbol;
	Fmx::Tabcontrol::TTabItem* TabTitle;
	Fmx::Tabcontrol::TTabControl* PageControl2;
	Fmx::Tabcontrol::TTabItem* TabItems;
	Fmx::Stdctrls::TPanel* Panel1;
	Fmx::Stdctrls::TButton* SBAddItem;
	Fmx::Stdctrls::TButton* SBDeleteItem;
	Fmx::Stdctrls::TCheckBox* CBCustom;
	Fmx::Stdctrls::TCheckBox* CBCustPosition;
	Fmx::Listbox::TListBox* LBItems;
	Fmx::Stdctrls::TPanel* PanelItem;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Stdctrls::TLabel* Label8;
	Fmx::Stdctrls::TLabel* LItemX;
	Fmx::Stdctrls::TLabel* LItemY;
	Fmx::Edit::TEdit* EItemText;
	Fmx::Edit::TEdit* EItemText2;
	Fmx::Listbox::TComboBox* CBItemAlign;
	Fmx::Spinbox::TSpinBox* UDItemLeft;
	Fmx::Spinbox::TSpinBox* UDItemTop;
	Fmx::Stdctrls::TButton* Button2;
	Fmx::Stdctrls::TCheckBox* CBDefItemFont;
	Fmxtee::Radiogroup::TRadioGroup* RGPosition;
	Fmx::Tabcontrol::TTabItem* TabFormat;
	Fmx::Stdctrls::TLabel* Label11;
	Fmx::Stdctrls::TTrackBar* TBTransp;
	Fmx::Stdctrls::TLabel* LTransp;
	Fmx::Stdctrls::TCheckBox* CBBehind;
	Fmx::Tabcontrol::TTabItem* TabLines;
	Fmx::Stdctrls::TLabel* Label6;
	Fmx::Listbox::TComboBox* CBJustify;
	Fmx::Listbox::TListBoxItem* ListBoxItem20;
	Fmx::Listbox::TListBoxItem* ListBoxItem21;
	Fmx::Listbox::TListBoxItem* ListBoxItem22;
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall CBLegendStyleChange(System::TObject* Sender);
	void __fastcall CBLegStyleChange(System::TObject* Sender);
	void __fastcall CBCheckBoxesChange(System::TObject* Sender);
	void __fastcall SBAddItemClick(System::TObject* Sender);
	void __fastcall SBDeleteItemClick(System::TObject* Sender);
	void __fastcall LBItemsClick(System::TObject* Sender);
	void __fastcall CBItemAlignChange(System::TObject* Sender);
	void __fastcall Button2Click(System::TObject* Sender);
	void __fastcall CBShowChange(System::TObject* Sender);
	void __fastcall CBFontColorChange(System::TObject* Sender);
	void __fastcall CBInvertedChange(System::TObject* Sender);
	void __fastcall UDVertSpacingChange(System::TObject* Sender);
	void __fastcall CBResizeChartChange(System::TObject* Sender);
	void __fastcall RGPositionChange(System::TObject* Sender);
	void __fastcall UDLeftChange(System::TObject* Sender);
	void __fastcall UDTopChange(System::TObject* Sender);
	void __fastcall UDMarginChange(System::TObject* Sender);
	void __fastcall UDTopPosChange(System::TObject* Sender);
	void __fastcall CBCustPosChange(System::TObject* Sender);
	void __fastcall CBPosPercentChange(System::TObject* Sender);
	void __fastcall CBCustomChange(System::TObject* Sender);
	void __fastcall CBCustPositionChange(System::TObject* Sender);
	void __fastcall CBDefItemFontChange(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall EItemTextTyping(System::TObject* Sender);
	void __fastcall EItemText2Typing(System::TObject* Sender);
	void __fastcall UDItemLeftChangeTracking(System::TObject* Sender);
	void __fastcall UDItemTopChangeTracking(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall CBBehindChange(System::TObject* Sender);
	void __fastcall CBJustifyChange(System::TObject* Sender);
	
private:
	Fmxtee::Chart::TChartLegend* Legend;
	Fmxtee::Editor::Symbol::TSymbolEditor* Symbol;
	Fmxtee::Editor::Textshape::TTextShapeEditor* FTitleEditor;
	Fmxtee::Editor::Customshape::TTeeShapeEditor* ITeeObject;
	Fmxtee::Editor::Stroke::TStrokeEditor* ILinesObject;
	bool IReady;
	void __fastcall AddItem(int Index);
	void __fastcall CheckCustomPosition();
	void __fastcall EnableCustItemPos();
	void __fastcall EnableCustomItems();
	Fmxtee::Chart::TLegendItem* __fastcall LegendItem();
	void __fastcall RefreshLegend(Fmxtee::Chart::TChartLegend* const ALegend);
	void __fastcall SetItems();
	
public:
	__classmethod Fmx::Forms::TForm* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Chart::TChartLegend* const ALegend);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TLegendEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TLegendEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TLegendEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Legend */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_LEGEND)
using namespace Fmxtee::Editor::Legend;
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
#endif	// Fmxtee_Editor_LegendHPP
