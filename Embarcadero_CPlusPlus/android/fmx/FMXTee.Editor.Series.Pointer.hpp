// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Series.Pointer.pas' rev: 34.00 (Android)

#ifndef Fmxtee_Editor_Series_PointerHPP
#define Fmxtee_Editor_Series_PointerHPP

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
#include <System.Variants.hpp>
#include <System.Generics.Collections.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.SpinBox.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.TabControl.hpp>
#include <FMXTee.Engine.hpp>
#include <FMXTee.Series.hpp>
#include <FMX.Layouts.hpp>
#include <FMXTee.Chart.GalleryPanel.hpp>
#include <FMXTee.Editor.Gradient.hpp>
#include <FMXTee.Editor.Stroke.hpp>
#include <FMXTee.Editor.Brush.hpp>
#include <FMXTee.Editor.Shadow.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Series
{
namespace Pointer
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSeriesPointerEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TSeriesPointerEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TPanel* PanelBottom;
	Fmx::Stdctrls::TPanel* Panel1;
	Fmx::Stdctrls::TButton* Button1;
	Fmx::Tabcontrol::TTabControl* PageControl1;
	Fmx::Tabcontrol::TTabItem* TabFormat;
	Fmx::Stdctrls::TLabel* LTransp;
	Fmx::Stdctrls::TCheckBox* CBDrawPoint;
	Fmx::Stdctrls::TCheckBox* CB3dPoint;
	Fmx::Stdctrls::TCheckBox* CBPoDark;
	Fmx::Stdctrls::TCheckBox* CBColorEach;
	Fmx::Stdctrls::TCheckBox* CBIgnoreNulls;
	Fmx::Stdctrls::TTrackBar* TBTransp;
	Fmx::Tabcontrol::TTabItem* TabSize;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Spinbox::TSpinBox* UDPointHorizSize;
	Fmx::Spinbox::TSpinBox* UDPointVertSize;
	Fmx::Spinbox::TSpinBox* UDPointDepth;
	Fmx::Stdctrls::TCheckBox* CBInflate;
	Fmx::Tabcontrol::TTabItem* TabStyle;
	Fmx::Tabcontrol::TTabItem* TabPattern;
	Fmx::Tabcontrol::TTabItem* TabBorder;
	Fmx::Tabcontrol::TTabItem* TabShadow;
	Fmx::Tabcontrol::TTabItem* TabEmboss;
	Fmx::Stdctrls::TPanel* Panel2;
	Fmx::Stdctrls::TCheckBox* CBDefBrushColor;
	Fmx::Stdctrls::TPanel* Panel3;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Listbox::TComboBox* CBStyle;
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
	Fmxtee::Chart::Gallerypanel::TChartGalleryPanel* StyleGallery;
	Fmx::Listbox::TListBoxItem* ListBoxItem15;
	Fmx::Stdctrls::TLabel* Label5;
	Fmx::Spinbox::TSpinBox* SBSize;
	Fmx::Listbox::TListBoxItem* ListBoxItem16;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CBStyleChange(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall CBDrawPointChange(System::TObject* Sender);
	void __fastcall CB3dPointChange(System::TObject* Sender);
	void __fastcall CBColorEachChange(System::TObject* Sender);
	void __fastcall CBIgnoreNullsChange(System::TObject* Sender);
	void __fastcall CBInflateChange(System::TObject* Sender);
	void __fastcall CBPoDarkChange(System::TObject* Sender);
	void __fastcall CBDefBrushColorChange(System::TObject* Sender);
	void __fastcall UDPointDepthChangeTracking(System::TObject* Sender);
	void __fastcall UDPointVertSizeChangeTracking(System::TObject* Sender);
	void __fastcall UDPointHorizSizeChangeTracking(System::TObject* Sender);
	void __fastcall FormActivate(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall StyleGalleryChangeChart(System::TObject* Sender);
	void __fastcall StyleGalleryResize(System::TObject* Sender);
	void __fastcall SBSizeChange(System::TObject* Sender);
	
private:
	Fmxtee::Engine::TSeriesPointer* Pointer;
	Fmxtee::Editor::Brush::TBrushEditor* IPatternEditor;
	Fmxtee::Editor::Stroke::TStrokeEditor* IBorderEditor;
	Fmxtee::Editor::Shadow::TShadowEditor* IShadowEditor;
	Fmxtee::Editor::Shadow::TShadowEditor* IEmbossEditor;
	bool ISelecting;
	void __fastcall CheckDefColor();
	Fmxtee::Series::TCustomLineSeries* __fastcall CustomSeries();
	void __fastcall RefreshPointer(Fmxtee::Engine::TSeriesPointer* const APointer);
	
public:
	__classmethod Fmx::Forms::TForm* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Engine::TSeriesPointer* const APointer);
	__classmethod bool __fastcall Edit(System::Classes::TComponent* const AOwner, Fmxtee::Engine::TSeriesPointer* const APointer);
	void __fastcall HideSizeOptions();
	__classmethod TSeriesPointerEditor* __fastcall InsertForm(Fmxtee::Engine::TSeriesPointer* const APointer, Fmx::Controls::TControl* const AParent);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TSeriesPointerEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TSeriesPointerEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TSeriesPointerEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Pointer */
}	/* namespace Series */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_SERIES_POINTER)
using namespace Fmxtee::Editor::Series::Pointer;
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
#endif	// Fmxtee_Editor_Series_PointerHPP
