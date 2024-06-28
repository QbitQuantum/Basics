// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Stroke.pas' rev: 34.00 (Windows)

#ifndef Fmxtee_Editor_StrokeHPP
#define Fmxtee_Editor_StrokeHPP

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
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.SpinBox.hpp>
#include <System.UIConsts.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Colors.hpp>
#include <FMXTee.Canvas.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Layouts.hpp>
#include <FMXTee.Chart.GalleryPanel.hpp>
#include <FMXTee.Editor.Brush.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Stroke
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStrokeEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TStrokeEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Colors::TComboColorBox* ComboColorBox1;
	Fmx::Stdctrls::TCheckBox* CBVisible;
	Fmx::Listbox::TComboBox* CBPenStyle;
	Fmx::Listbox::TListBoxItem* SolidItem;
	Fmx::Listbox::TListBoxItem* DashItem;
	Fmx::Listbox::TListBoxItem* DotItem;
	Fmx::Listbox::TListBoxItem* DashDotItem;
	Fmx::Listbox::TListBoxItem* DashDotDotItem;
	Fmx::Stdctrls::TPanel* Panel1;
	Fmx::Stdctrls::TButton* Button1;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Listbox::TListBoxItem* SmallDotsItem;
	Fmx::Listbox::TComboBox* CBEnd;
	Fmx::Listbox::TListBoxItem* ListBoxItem1;
	Fmx::Listbox::TListBoxItem* ListBoxItem3;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Listbox::TComboBox* CBJoin;
	Fmx::Listbox::TListBoxItem* ListBoxItem4;
	Fmx::Listbox::TListBoxItem* ListBoxItem5;
	Fmx::Listbox::TListBoxItem* ListBoxItem6;
	Fmx::Tabcontrol::TTabControl* TabControl1;
	Fmx::Tabcontrol::TTabItem* TabFormat;
	Fmx::Tabcontrol::TTabItem* TabStyle;
	Fmx::Tabcontrol::TTabItem* TabItem3;
	Fmx::Tabcontrol::TTabItem* TabFill;
	Fmx::Stdctrls::TCheckBox* CBDefColor;
	Fmx::Stdctrls::TPanel* Panel2;
	Fmxtee::Chart::Gallerypanel::TChartGalleryPanel* Styles;
	Fmx::Layouts::TLayout* Panel3;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Stdctrls::TTrackBar* TBTransp;
	Fmx::Stdctrls::TTrackBar* TBWidth;
	Fmx::Stdctrls::TLabel* LWidth;
	Fmx::Stdctrls::TButton* Button2;
	void __fastcall ComboColorBox1Change(System::TObject* Sender);
	void __fastcall CBVisibleChange(System::TObject* Sender);
	void __fastcall CBPenStyleChange(System::TObject* Sender);
	void __fastcall CBEndChange(System::TObject* Sender);
	void __fastcall CBJoinChange(System::TObject* Sender);
	void __fastcall CBDefColorChange(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall TabControl1Change(System::TObject* Sender);
	void __fastcall StylesChangeChart(System::TObject* Sender);
	void __fastcall TBWidthTracking(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall Button2Click(System::TObject* Sender);
	
private:
	Fmxtee::Canvas::TTeePen* IBackup;
	bool ISelecting;
	Fmxtee::Editor::Brush::TBrushEditor* IFillEditor;
	void __fastcall PrepareDefColor();
	void __fastcall RefreshTransparency();
	void __fastcall SelectStyleGallery();
	void __fastcall SetLabelWidth();
	void __fastcall StyleChartDraw(System::TObject* Sender);
	
protected:
	Fmxtee::Canvas::TTeePen* Pen;
	bool IRefreshing;
	virtual System::Uitypes::TAlphaColor __fastcall GetDefaultColor();
	virtual void __fastcall SetDefaultColor();
	
public:
	__classmethod bool __fastcall Edit(System::Classes::TComponent* const AOwner, Fmxtee::Canvas::TTeePen* const APen);
	void __fastcall RefreshPen(Fmxtee::Canvas::TTeePen* const APen);
	void __fastcall RepaintButtonColor();
	__classmethod void __fastcall SetRepeatClick(Fmx::Spinbox::TSpinBox* const ASpinBox, const bool AValue);
	__classmethod TStrokeEditor* __fastcall InsertForm(Fmxtee::Canvas::TTeePen* const APen, Fmx::Controls::TControl* const AParent);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TStrokeEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TStrokeEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TStrokeEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define TeeCursorPrefix L"cr"
extern DELPHI_PACKAGE Fmx::Forms::TCommonCustomForm* __fastcall EmbeddForm(Fmx::Forms::TCommonCustomForm* const AForm, Fmx::Types::TFmxObject* const AParent);
extern DELPHI_PACKAGE System::UnicodeString __fastcall DeleteCursorPrefix(const System::UnicodeString S);
extern DELPHI_PACKAGE void __fastcall TeeFillCursors(Fmx::Listbox::TComboBox* const ACombo, const System::Uitypes::TCursor ACursor);
extern DELPHI_PACKAGE bool __fastcall TeeInputQuery(const System::UnicodeString ATitle, const System::UnicodeString ACaption, System::UnicodeString &AValue);
extern DELPHI_PACKAGE int __fastcall YesNoCancel(const System::UnicodeString AMessage);
extern DELPHI_PACKAGE bool __fastcall YesNo(const System::UnicodeString AMessage);
}	/* namespace Stroke */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_STROKE)
using namespace Fmxtee::Editor::Stroke;
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
#endif	// Fmxtee_Editor_StrokeHPP
