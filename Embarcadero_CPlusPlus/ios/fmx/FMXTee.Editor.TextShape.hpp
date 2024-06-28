// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.TextShape.pas' rev: 34.00 (iOS)

#ifndef Fmxtee_Editor_TextshapeHPP
#define Fmxtee_Editor_TextshapeHPP

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
#include <System.Rtti.hpp>
#include <System.Classes.hpp>
#include <System.Variants.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.TabControl.hpp>
#include <FMXTee.Engine.hpp>
#include <FMXTee.Editor.Margins.hpp>
#include <FMXTee.Editor.CustomShape.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Textshape
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTextShapeEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TTextShapeEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* TabControl1;
	Fmx::Tabcontrol::TTabItem* TabOptions;
	Fmx::Tabcontrol::TTabItem* TabText;
	Fmx::Tabcontrol::TTabItem* TabMargins;
	Fmx::Tabcontrol::TTabItem* TabFormat;
	Fmx::Stdctrls::TCheckBox* CBVisible;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Listbox::TComboBox* CBAlign;
	Fmx::Listbox::TListBoxItem* ListBoxItem1;
	Fmx::Listbox::TListBoxItem* ListBoxItem2;
	Fmx::Listbox::TListBoxItem* ListBoxItem3;
	Fmx::Stdctrls::TPanel* Panel1;
	Fmx::Memo::TMemo* MemoText;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TCheckBox* CBClip;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Stdctrls::TTrackBar* TBAngle;
	Fmx::Stdctrls::TButton* Button1;
	Fmx::Listbox::TComboBox* CBTextAlign;
	Fmx::Listbox::TListBoxItem* ListBoxItem4;
	Fmx::Listbox::TListBoxItem* ListBoxItem5;
	Fmx::Listbox::TListBoxItem* ListBoxItem6;
	Fmx::Stdctrls::TLabel* LCursor;
	Fmx::Listbox::TComboBox* CBCursor;
	void __fastcall CBAlignChange(System::TObject* Sender);
	void __fastcall CBVisibleChange(System::TObject* Sender);
	void __fastcall TabControl1Change(System::TObject* Sender);
	void __fastcall MemoTextChange(System::TObject* Sender);
	void __fastcall CBTextAlignChange(System::TObject* Sender);
	void __fastcall CBCursorChange(System::TObject* Sender);
	void __fastcall CBClipChange(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall TBAngleChange(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall MemoTextChangeTracking(System::TObject* Sender);
	
private:
	Fmxtee::Engine::TCustomTextShape* Shape;
	bool AssigningText;
	bool CreatingForm;
	Fmxtee::Editor::Customshape::TTeeShapeEditor* ShapeForm;
	Fmxtee::Editor::Margins::TMarginsEditor* MarginsForm;
	
public:
	__classmethod TTextShapeEditor* __fastcall Embedd(Fmxtee::Engine::TCustomTextShape* const AShape, Fmx::Types::TFmxObject* const AParent);
	__classmethod TTextShapeEditor* __fastcall InsertForm(Fmxtee::Engine::TCustomTextShape* const AShape, Fmx::Types::TFmxObject* const AParent);
	void __fastcall RefreshShape(Fmxtee::Engine::TCustomTextShape* const AShape);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TTextShapeEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TTextShapeEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TTextShapeEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Textshape */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_TEXTSHAPE)
using namespace Fmxtee::Editor::Textshape;
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
#endif	// Fmxtee_Editor_TextshapeHPP
