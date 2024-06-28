// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Series.Area.pas' rev: 34.00 (Android)

#ifndef Fmxtee_Editor_Series_AreaHPP
#define Fmxtee_Editor_Series_AreaHPP

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
#include <FMXTee.Series.hpp>
#include <FMXTee.RadioGroup.hpp>
#include <FMX.Colors.hpp>
#include <FMXTee.Editor.Brush.hpp>
#include <FMXTee.Editor.Stroke.hpp>
#include <FMXTee.Editor.Series.Pointer.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Series
{
namespace Area
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAreaSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAreaSeriesEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* PageControl1;
	Fmx::Tabcontrol::TTabItem* TabSheet1;
	Fmx::Stdctrls::TGroupBox* GroupBox2;
	Fmx::Stdctrls::TCheckBox* CBStairs;
	Fmx::Stdctrls::TCheckBox* CBInvStairs;
	Fmx::Stdctrls::TCheckBox* CBSmoothed;
	Fmx::Stdctrls::TGroupBox* GroupBox5;
	Fmx::Stdctrls::TGroupBox* GroupBox1;
	Fmx::Stdctrls::TCheckBox* CBColorEach;
	Fmx::Stdctrls::TGroupBox* GroupBox4;
	Fmx::Listbox::TComboBox* CBNulls;
	Fmx::Tabcontrol::TTabItem* TabSheet2;
	Fmx::Stdctrls::TGroupBox* GroupBox3;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TCheckBox* CBUseOrigin;
	Fmx::Spinbox::TSpinBox* UDOrigin;
	Fmx::Stdctrls::TGroupBox* GroupBox6;
	Fmx::Spinbox::TSpinBox* UDGroup;
	Fmxtee::Radiogroup::TRadioGroup* RGMultiArea;
	Fmx::Tabcontrol::TTabItem* TabBorder;
	Fmx::Tabcontrol::TTabItem* TabPattern;
	Fmx::Tabcontrol::TTabItem* TabAreaLines;
	Fmx::Tabcontrol::TTabItem* TabAreaTop;
	Fmx::Stdctrls::TCheckBox* CBDefColor;
	Fmx::Colors::TComboColorBox* BAreaColor;
	Fmx::Stdctrls::TCheckBox* CBDark3D;
	Fmx::Stdctrls::TTrackBar* TBTransp;
	Fmx::Stdctrls::TGroupBox* GroupBox7;
	Fmx::Listbox::TComboBox* CBDrawStyle;
	Fmx::Tabcontrol::TTabItem* TabPointer;
	void __fastcall CBNullsChange(System::TObject* Sender);
	void __fastcall FormActivate(System::TObject* Sender);
	void __fastcall CBColorEachChange(System::TObject* Sender);
	void __fastcall CBDark3DChange(System::TObject* Sender);
	void __fastcall CBSmoothedChange(System::TObject* Sender);
	void __fastcall CBInvStairsChange(System::TObject* Sender);
	void __fastcall CBStairsChange(System::TObject* Sender);
	void __fastcall CBUseOriginChange(System::TObject* Sender);
	void __fastcall UDOriginChange(System::TObject* Sender);
	void __fastcall UDGroupChange(System::TObject* Sender);
	void __fastcall RGMultiAreaChange(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall CBDefColorChange(System::TObject* Sender);
	void __fastcall BAreaColorChange(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall CBDrawStyleChange(System::TObject* Sender);
	
private:
	Fmxtee::Series::TAreaSeries* Area;
	Fmxtee::Editor::Stroke::TStrokeEditor* IBorder;
	Fmxtee::Editor::Stroke::TStrokeEditor* ILines;
	Fmxtee::Editor::Brush::TBrushEditor* IBrush;
	Fmxtee::Editor::Brush::TBrushEditor* ITop;
	Fmxtee::Editor::Series::Pointer::TSeriesPointerEditor* IPointer;
	void __fastcall RefreshArea(Fmxtee::Series::TAreaSeries* const AArea);
	void __fastcall RefreshShape();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TAreaSeriesEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TAreaSeriesEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TAreaSeriesEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Area */
}	/* namespace Series */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_SERIES_AREA)
using namespace Fmxtee::Editor::Series::Area;
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
#endif	// Fmxtee_Editor_Series_AreaHPP
