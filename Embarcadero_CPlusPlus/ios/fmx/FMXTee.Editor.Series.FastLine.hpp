// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Series.FastLine.pas' rev: 34.00 (iOS)

#ifndef Fmxtee_Editor_Series_FastlineHPP
#define Fmxtee_Editor_Series_FastlineHPP

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
#include <FMX.Dialogs.hpp>
#include <FMXTee.Series.hpp>
#include <FMXTee.Editor.Stroke.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Colors.hpp>
#include <FMX.TabControl.hpp>
#include <FMXTee.Engine.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Series
{
namespace Fastline
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFastLineSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFastLineSeriesEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* TabControl1;
	Fmx::Tabcontrol::TTabItem* TabItem1;
	Fmx::Tabcontrol::TTabItem* TabStroke;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TCheckBox* CBDrawAll;
	Fmx::Stdctrls::TGroupBox* GBStair;
	Fmx::Stdctrls::TCheckBox* CBStairs;
	Fmx::Stdctrls::TCheckBox* CBInvStairs;
	Fmx::Listbox::TComboBox* CBNulls;
	Fmx::Listbox::TListBoxItem* ListBoxItem1;
	Fmx::Listbox::TListBoxItem* ListBoxItem2;
	Fmx::Listbox::TListBoxItem* ListBoxItem3;
	Fmx::Listbox::TComboBox* CBDrawAllStyle;
	Fmx::Listbox::TListBoxItem* ListBoxItem4;
	Fmx::Listbox::TListBoxItem* ListBoxItem5;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Listbox::TComboBox* CBDrawStyle;
	void __fastcall CBNullsChange(System::TObject* Sender);
	void __fastcall CBDrawAllStyleChange(System::TObject* Sender);
	void __fastcall CBDrawAllChange(System::TObject* Sender);
	void __fastcall CBStairsChange(System::TObject* Sender);
	void __fastcall CBInvStairsChange(System::TObject* Sender);
	void __fastcall FormActivate(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CBDrawStyleChange(System::TObject* Sender);
	
private:
	Fmxtee::Series::TFastLineSeries* Fast;
	Fmxtee::Editor::Stroke::TStrokeEditor* StrokeEditor;
	void __fastcall RefreshFast(Fmxtee::Series::TFastLineSeries* const AFast);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFastLineSeriesEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFastLineSeriesEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFastLineSeriesEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fastline */
}	/* namespace Series */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_SERIES_FASTLINE)
using namespace Fmxtee::Editor::Series::Fastline;
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
#endif	// Fmxtee_Editor_Series_FastlineHPP
