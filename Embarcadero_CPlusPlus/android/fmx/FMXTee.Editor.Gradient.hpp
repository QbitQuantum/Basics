// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Gradient.pas' rev: 34.00 (Android)

#ifndef Fmxtee_Editor_GradientHPP
#define Fmxtee_Editor_GradientHPP

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
#include <FMX.Dialogs.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.TabControl.hpp>
#include <FMXTee.Canvas.hpp>
#include <FMXTee.Procs.hpp>
#include <FMX.Colors.hpp>
#include <FMX.Layouts.hpp>
#include <FMXTee.Chart.GalleryPanel.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Gradient
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TGradientEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TGradientEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TPanel* Panel1;
	Fmx::Stdctrls::TCheckBox* CBVisible;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Listbox::TComboBox* CBDirection;
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
	Fmx::Tabcontrol::TTabControl* TabControl1;
	Fmx::Tabcontrol::TTabItem* TabItem1;
	Fmx::Tabcontrol::TTabItem* TabItem2;
	Fmx::Colors::TComboColorBox* ColorButton1;
	Fmx::Colors::TComboColorBox* ColorButton2;
	Fmx::Colors::TComboColorBox* ColorButton3;
	Fmx::Stdctrls::TCheckBox* CBUseMiddle;
	Fmx::Stdctrls::TButton* Button1;
	Fmx::Colors::TGradientEdit* GradientEdit1;
	Fmx::Stdctrls::TGroupBox* GroupBox1;
	Fmx::Stdctrls::TTrackBar* TBX;
	Fmx::Stdctrls::TTrackBar* TBY;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Tabcontrol::TTabItem* TabDirections;
	Fmxtee::Chart::Gallerypanel::TChartGalleryPanel* Directions;
	Fmx::Tabcontrol::TTabItem* TabGallery;
	Fmxtee::Chart::Gallerypanel::TChartGalleryPanel* Gallery;
	Fmx::Colors::TComboColorBox* CurrentColor;
	Fmx::Stdctrls::TButton* BDeleteColor;
	Fmx::Stdctrls::TPanel* PanelButtons;
	Fmx::Layouts::TLayout* Layout1;
	Fmx::Stdctrls::TButton* Button2;
	Fmx::Stdctrls::TButton* Button3;
	void __fastcall CBVisibleChange(System::TObject* Sender);
	void __fastcall ColorButton1Change(System::TObject* Sender);
	void __fastcall ColorButton2Change(System::TObject* Sender);
	void __fastcall ColorButton3Change(System::TObject* Sender);
	void __fastcall CBDirectionChange(System::TObject* Sender);
	void __fastcall CBUseMiddleChange(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall TBXChange(System::TObject* Sender);
	void __fastcall TBYChange(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall GradientEdit1Change(System::TObject* Sender);
	void __fastcall GradientEdit1SelectPoint(System::TObject* Sender);
	void __fastcall TabControl1Change(System::TObject* Sender);
	void __fastcall GalleryChangeChart(System::TObject* Sender);
	void __fastcall DirectionsChangeChart(System::TObject* Sender);
	void __fastcall CurrentColorChange(System::TObject* Sender);
	void __fastcall BDeleteColorClick(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall Button3Click(System::TObject* Sender);
	
private:
	Fmxtee::Canvas::TCustomTeeGradient* Gradient;
	Fmxtee::Canvas::TCustomTeeGradient* IBackup;
	bool IModified;
	bool IUpdating;
	bool IChangingButtons;
	bool IChangingColor;
	void __fastcall ApplyChart(Fmxtee::Chart::Gallerypanel::TGalleryChart* const Chart);
	__classmethod void __fastcall DefaultGradient(Fmxtee::Canvas::TCustomTeeGradient* const Gradient, bool IsRectGradient, int Index);
	bool __fastcall IsRectGradient();
	void __fastcall RefreshControls();
	void __fastcall SelectDirection();
	void __fastcall SetDirectionGradients();
	void __fastcall SetGradientColorButtons();
	void __fastcall UpdateGradientEdit();
	
public:
	__classmethod TGradientEditor* __fastcall InsertForm(Fmxtee::Canvas::TCustomTeeGradient* const AGradient, Fmx::Types::TFmxObject* const AParent);
	__classmethod bool __fastcall Edit(System::Classes::TComponent* const AOwner, Fmxtee::Canvas::TCustomTeeGradient* const AGradient);
	void __fastcall RefreshGradient(Fmxtee::Canvas::TCustomTeeGradient* const AGradient);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TGradientEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TGradientEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TGradientEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Gradient */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_GRADIENT)
using namespace Fmxtee::Editor::Gradient;
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
#endif	// Fmxtee_Editor_GradientHPP
