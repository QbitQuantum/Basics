// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Series.Pie.pas' rev: 34.00 (Android)

#ifndef Fmxtee_Editor_Series_PieHPP
#define Fmxtee_Editor_Series_PieHPP

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
#include <FMXTee.Editor.Series.Circled.hpp>
#include <FMX.Layouts.hpp>
#include <FMXTee.Editor.Stroke.hpp>
#include <FMXTee.Editor.Gradient.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Series
{
namespace Pie
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPieSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPieSeriesEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* PageControl1;
	Fmx::Tabcontrol::TTabItem* TabOptions;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Stdctrls::TLabel* LTransparency;
	Fmx::Stdctrls::TLabel* LEdgeStyle;
	Fmx::Stdctrls::TLabel* Label11;
	Fmx::Stdctrls::TCheckBox* CBDark3d;
	Fmx::Spinbox::TSpinBox* UDExpBig;
	Fmx::Stdctrls::TCheckBox* CBPatterns;
	Fmx::Spinbox::TSpinBox* UDAngleSize;
	Fmx::Listbox::TComboBox* CBMultiple;
	Fmx::Listbox::TComboBox* CBEdgeStyle;
	Fmx::Tabcontrol::TTabItem* TabGroup;
	Fmx::Stdctrls::TLabel* Label5;
	Fmx::Stdctrls::TLabel* Label6;
	Fmx::Stdctrls::TLabel* Label7;
	Fmx::Listbox::TComboBox* CBOther;
	Fmx::Edit::TEdit* EOtherValue;
	Fmx::Edit::TEdit* EOtherLabel;
	Fmx::Stdctrls::TButton* Button2;
	Fmx::Tabcontrol::TTabItem* TabSheet1;
	Fmx::Stdctrls::TLabel* Label9;
	Fmx::Stdctrls::TCheckBox* CBColorEach;
	Fmx::Stdctrls::TButton* BColor;
	Fmx::Listbox::TComboBox* CBPalette;
	Fmx::Tabcontrol::TTabItem* TabSheet2;
	Fmx::Stdctrls::TLabel* Label8;
	Fmx::Stdctrls::TLabel* LLegSize;
	Fmx::Stdctrls::TCheckBox* CBMarksAutoPosition;
	Fmx::Stdctrls::TCheckBox* CBVertCenter;
	Fmx::Stdctrls::TScrollBar* SBLegSize;
	Fmx::Tabcontrol::TTabItem* TabGradient;
	Fmx::Tabcontrol::TTabItem* TabItem1;
	Fmx::Stdctrls::TCheckBox* CBMarksInside;
	Fmx::Stdctrls::TTrackBar* TBTransp;
	Fmx::Stdctrls::TLabel* LTransp;
	Fmx::Tabcontrol::TTabControl* TabControl1;
	Fmx::Tabcontrol::TTabItem* TabBevel;
	Fmx::Tabcontrol::TTabItem* TabBorder;
	Fmx::Stdctrls::TLabel* LBevelPercent;
	Fmx::Spinbox::TSpinBox* UDBevelPercent;
	Fmx::Stdctrls::TLabel* Label12;
	Fmx::Stdctrls::TTrackBar* TBBevelBright;
	Fmx::Stdctrls::TLabel* LBevelBright;
	Fmx::Stdctrls::TCheckBox* CBBevelBorder;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Spinbox::TSpinBox* UDDarkPen;
	Fmx::Stdctrls::TCheckBox* CBRotated;
	Fmx::Stdctrls::TCheckBox* CBMarksEmpty;
	Fmx::Layouts::TLayout* Layout1;
	Fmx::Stdctrls::TLabel* Label10;
	Fmx::Stdctrls::TTrackBar* TBBright;
	Fmx::Stdctrls::TLabel* LBright;
	Fmx::Tabcontrol::TTabItem* TabFrame;
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall CBMultipleChange(System::TObject* Sender);
	void __fastcall CBEdgeStyleChange(System::TObject* Sender);
	void __fastcall CBOtherChange(System::TObject* Sender);
	void __fastcall Button2Click(System::TObject* Sender);
	void __fastcall SBLegSizeChange(System::TObject* Sender);
	void __fastcall TBBrightChange(System::TObject* Sender);
	void __fastcall FormActivate(System::TObject* Sender);
	void __fastcall CBDark3dChange(System::TObject* Sender);
	void __fastcall CBPatternsChange(System::TObject* Sender);
	void __fastcall CBColorEachChange(System::TObject* Sender);
	void __fastcall CBMarksAutoPositionChange(System::TObject* Sender);
	void __fastcall CBVertCenterChange(System::TObject* Sender);
	void __fastcall BColorClick(System::TObject* Sender);
	void __fastcall UDBevelPercentChange(System::TObject* Sender);
	void __fastcall UDExpBigChange(System::TObject* Sender);
	void __fastcall UDAngleSizeChange(System::TObject* Sender);
	void __fastcall UDDarkPenChange(System::TObject* Sender);
	void __fastcall CBPaletteChange(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall EOtherValueTyping(System::TObject* Sender);
	void __fastcall EOtherLabelTyping(System::TObject* Sender);
	void __fastcall TBBevelBrightChange(System::TObject* Sender);
	void __fastcall CBBevelBorderChange(System::TObject* Sender);
	void __fastcall CBMarksInsideChange(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall CBRotatedChange(System::TObject* Sender);
	void __fastcall CBMarksEmptyChange(System::TObject* Sender);
	void __fastcall TabControl1Change(System::TObject* Sender);
	
private:
	Fmxtee::Series::TPieSeries* Pie;
	Fmxtee::Editor::Stroke::TStrokeEditor* IBorder;
	Fmxtee::Editor::Gradient::TGradientEditor* IGradient;
	Fmxtee::Editor::Series::Circled::TCircledSeriesEditor* FCircledEditor;
	void __fastcall RefreshPie(Fmxtee::Series::TPieSeries* const APie);
	
public:
	__classmethod Fmx::Forms::TForm* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Series::TPieSeries* const APie);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TPieSeriesEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TPieSeriesEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TPieSeriesEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Pie */
}	/* namespace Series */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_SERIES_PIE)
using namespace Fmxtee::Editor::Series::Pie;
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
#endif	// Fmxtee_Editor_Series_PieHPP
