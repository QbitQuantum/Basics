// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Symbol.pas' rev: 34.00 (iOS)

#ifndef Fmxtee_Editor_SymbolHPP
#define Fmxtee_Editor_SymbolHPP

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
#include <FMXTee.Chart.hpp>
#include <FMX.TabControl.hpp>
#include <FMXTee.Editor.Gradient.hpp>
#include <FMXTee.Editor.Stroke.hpp>
#include <FMXTee.Editor.Shadow.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Symbol
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSymbolEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TSymbolEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* TabControl1;
	Fmx::Tabcontrol::TTabItem* TabOptions;
	Fmx::Tabcontrol::TTabItem* TabBorder;
	Fmx::Tabcontrol::TTabItem* TabGradient;
	Fmx::Tabcontrol::TTabItem* TabShadow;
	Fmx::Tabcontrol::TTabItem* TabEmboss;
	Fmx::Stdctrls::TLabel* L11;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Listbox::TComboBox* CBColWUnits;
	Fmx::Listbox::TListBoxItem* ListBoxItem1;
	Fmx::Listbox::TListBoxItem* ListBoxItem2;
	Fmx::Listbox::TComboBox* CBSymbolPos;
	Fmx::Listbox::TListBoxItem* ListBoxItem3;
	Fmx::Listbox::TListBoxItem* ListBoxItem4;
	Fmx::Stdctrls::TCheckBox* CBContinuous;
	Fmx::Stdctrls::TCheckBox* CBVisible;
	Fmx::Stdctrls::TCheckBox* CBSymPen;
	Fmx::Stdctrls::TCheckBox* CBSquared;
	Fmx::Spinbox::TSpinBox* UDWidth;
	void __fastcall CBColWUnitsChange(System::TObject* Sender);
	void __fastcall CBSymbolPosChange(System::TObject* Sender);
	void __fastcall CBVisibleChange(System::TObject* Sender);
	void __fastcall CBContinuousChange(System::TObject* Sender);
	void __fastcall CBSquaredChange(System::TObject* Sender);
	void __fastcall UDWidthChange(System::TObject* Sender);
	void __fastcall CBSymPenChange(System::TObject* Sender);
	void __fastcall TabControl1Change(System::TObject* Sender);
	
private:
	Fmxtee::Chart::TLegendSymbol* Symbol;
	Fmxtee::Editor::Stroke::TStrokeEditor* IBorder;
	Fmxtee::Editor::Gradient::TGradientEditor* IGradient;
	Fmxtee::Editor::Shadow::TShadowEditor* IShadow;
	Fmxtee::Editor::Shadow::TShadowEditor* IEmboss;
	
public:
	__classmethod TSymbolEditor* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Chart::TLegendSymbol* const ASymbol);
	void __fastcall RefreshSymbol(Fmxtee::Chart::TLegendSymbol* const ASymbol);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TSymbolEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TSymbolEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TSymbolEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Symbol */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_SYMBOL)
using namespace Fmxtee::Editor::Symbol;
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
#endif	// Fmxtee_Editor_SymbolHPP
