// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Shadow.pas' rev: 34.00 (iOS)

#ifndef Fmxtee_Editor_ShadowHPP
#define Fmxtee_Editor_ShadowHPP

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
#include <FMX.Edit.hpp>
#include <FMX.Dialogs.hpp>
#include <FMXTee.Canvas.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Colors.hpp>
#include <FMX.TabControl.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Shadow
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TShadowEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TShadowEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TPanel* PanelButtons;
	Fmx::Stdctrls::TButton* BOK;
	Fmx::Tabcontrol::TTabControl* TabControl1;
	Fmx::Tabcontrol::TTabItem* TabFormat;
	Fmx::Tabcontrol::TTabItem* TabOptions;
	Fmx::Stdctrls::TCheckBox* CBSmooth;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TTrackBar* TBBlur;
	Fmx::Stdctrls::TLabel* LBlur;
	Fmx::Stdctrls::TCheckBox* CBClip;
	Fmx::Stdctrls::TCheckBox* CBVisible;
	Fmx::Stdctrls::TLabel* LTransp;
	Fmx::Colors::TComboColorBox* BShadowColor;
	Fmx::Stdctrls::TTrackBar* TBTransp;
	Fmx::Stdctrls::TGroupBox* GroupBox1;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TLabel* Label5;
	Fmx::Spinbox::TSpinBox* UDShadowSize;
	Fmx::Spinbox::TSpinBox* UDShaVert;
	Fmx::Stdctrls::TTrackBar* TBSize;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Listbox::TComboBox* CBDirection;
	Fmx::Listbox::TListBoxItem* ListBoxItem1;
	Fmx::Listbox::TListBoxItem* ListBoxItem2;
	Fmx::Listbox::TListBoxItem* ListBoxItem3;
	Fmx::Listbox::TListBoxItem* ListBoxItem4;
	Fmx::Listbox::TListBoxItem* ListBoxItem5;
	void __fastcall BOKClick(System::TObject* Sender);
	void __fastcall TBBlurChange(System::TObject* Sender);
	void __fastcall CBVisibleChange(System::TObject* Sender);
	void __fastcall CBSmoothChange(System::TObject* Sender);
	void __fastcall CBClipChange(System::TObject* Sender);
	void __fastcall UDShaVertChange(System::TObject* Sender);
	void __fastcall UDShadowSizeChange(System::TObject* Sender);
	void __fastcall BShadowColorChange(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall TBSizeChange(System::TObject* Sender);
	void __fastcall CBDirectionChange(System::TObject* Sender);
	
private:
	bool IChanging;
	Fmxtee::Canvas::TTeeShadow* Shadow;
	bool __fastcall CanChange();
	void __fastcall SetTrackBarSize();
	
public:
	__classmethod bool __fastcall Edit(System::Classes::TComponent* const AOwner, Fmxtee::Canvas::TTeeShadow* const AShadow);
	__classmethod TShadowEditor* __fastcall InsertForm(Fmxtee::Canvas::TTeeShadow* const AShadow, Fmx::Types::TFmxObject* const AParent);
	void __fastcall RefreshShadow(Fmxtee::Canvas::TTeeShadow* const AShadow);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TShadowEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TShadowEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TShadowEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Shadow */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_SHADOW)
using namespace Fmxtee::Editor::Shadow;
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
#endif	// Fmxtee_Editor_ShadowHPP
