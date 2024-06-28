// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Title.pas' rev: 34.00 (Android)

#ifndef Fmxtee_Editor_TitleHPP
#define Fmxtee_Editor_TitleHPP

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
#include <FMX.Memo.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Edit.hpp>
#include <FMX.SpinBox.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.TabControl.hpp>
#include <FMXTee.Engine.hpp>
#include <FMXTee.Chart.hpp>
#include <FMXTee.Editor.CustomShape.hpp>
#include <FMXTee.Editor.TextShape.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Title
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTitleEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TTitleEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* PageControlTitle;
	Fmx::Tabcontrol::TTabItem* TabSheet2;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Stdctrls::TGroupBox* GroupBox1;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Stdctrls::TLabel* Label5;
	Fmx::Spinbox::TSpinBox* UDLeft;
	Fmx::Spinbox::TSpinBox* UDTop;
	Fmx::Stdctrls::TCheckBox* CBCustPos;
	Fmx::Spinbox::TSpinBox* UDMargin;
	Fmx::Stdctrls::TPanel* Panel1;
	Fmx::Listbox::TComboBox* CBTitles;
	Fmx::Stdctrls::TCheckBox* CBAdjust;
	void __fastcall CBTitlesChange(System::TObject* Sender);
	void __fastcall CBAdjustChange(System::TObject* Sender);
	void __fastcall UDLeftChange(System::TObject* Sender);
	void __fastcall UDTopChange(System::TObject* Sender);
	void __fastcall UDMarginChange(System::TObject* Sender);
	void __fastcall CBCustPosChange(System::TObject* Sender);
	void __fastcall PageControlTitleChange(System::TObject* Sender);
	
private:
	Fmxtee::Chart::TCustomChart* Chart;
	Fmxtee::Editor::Textshape::TTextShapeEditor* ITeeObject;
	bool IChanging;
	int __fastcall IndexOfTitle(Fmxtee::Chart::TChartTitle* const ATitle);
	void __fastcall RefreshChart(Fmxtee::Chart::TChartTitle* const ATitle);
	Fmxtee::Chart::TChartTitle* __fastcall Title();
	
public:
	__classmethod Fmx::Forms::TForm* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Chart::TCustomChart* const AChart)/* overload */;
	__classmethod Fmx::Forms::TForm* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Chart::TChartTitle* const ATitle)/* overload */;
	void __fastcall RefreshTitle(Fmxtee::Chart::TChartTitle* const ATitle);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TTitleEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TTitleEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TTitleEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Title */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_TITLE)
using namespace Fmxtee::Editor::Title;
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
#endif	// Fmxtee_Editor_TitleHPP
