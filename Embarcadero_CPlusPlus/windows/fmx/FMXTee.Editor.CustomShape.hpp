// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.CustomShape.pas' rev: 34.00 (Windows)

#ifndef Fmxtee_Editor_CustomshapeHPP
#define Fmxtee_Editor_CustomshapeHPP

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
#include <FMX.StdCtrls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.TabControl.hpp>
#include <FMXTee.Procs.hpp>
#include <FMXTee.Editor.Font.hpp>
#include <FMX.Ani.hpp>
#include <FMX.Colors.hpp>
#include <FMXTee.Editor.Shadow.hpp>
#include <FMXTee.Editor.Brush.hpp>
#include <FMXTee.Editor.Stroke.hpp>
#include <FMX.ComboTrackBar.hpp>
#include <FMX.SpinBox.hpp>
#include <FMXTee.Editor.Gradient.hpp>
#include <FMXTee.Editor.Picture.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Customshape
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTeeShapeEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TTeeShapeEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* PC1;
	Fmx::Tabcontrol::TTabItem* TabFormat;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Stdctrls::TCheckBox* CBTransparent;
	Fmx::Tabcontrol::TTabItem* TabBorder;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Listbox::TComboBox* CBBevel;
	Fmx::Spinbox::TSpinBox* UDBevW;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TCheckBox* CBRound;
	Fmx::Spinbox::TSpinBox* UDRoundSize;
	Fmx::Tabcontrol::TTabItem* TabFont;
	Fmx::Tabcontrol::TTabItem* TabPattern;
	Fmx::Tabcontrol::TTabItem* TabShadow;
	Fmx::Tabcontrol::TTabItem* TabEmboss;
	Fmx::Tabcontrol::TTabItem* TabImage;
	Fmx::Stdctrls::TTrackBar* TBTransp;
	Fmx::Ani::TColorAnimation* ColorAnimation1;
	Fmx::Tabcontrol::TTabControl* TabControl1;
	Fmx::Tabcontrol::TTabItem* TabCorners;
	Fmx::Tabcontrol::TTabItem* TabFrame;
	Fmx::Tabcontrol::TTabItem* TabCallout;
	Fmx::Tabcontrol::TTabItem* TabBevel;
	Fmx::Colors::TComboColorBox* BBackColor;
	Fmx::Stdctrls::TLabel* LTransp;
	Fmx::Stdctrls::TCheckBox* CBVisible;
	Fmx::Stdctrls::TGroupBox* GroupBox1;
	Fmx::Listbox::TComboBox* CBLeftTop;
	Fmx::Listbox::TComboBox* CBLeftBottom;
	Fmx::Listbox::TComboBox* CBRightTop;
	Fmx::Listbox::TComboBox* CBRightBottom;
	Fmx::Stdctrls::TLabel* Label5;
	Fmx::Listbox::TComboBox* CBSide;
	Fmx::Stdctrls::TLabel* Label6;
	Fmx::Stdctrls::TLabel* Label7;
	Fmx::Stdctrls::TLabel* Label8;
	Fmx::Combotrackbar::TComboTrackBar* TBSize;
	Fmx::Combotrackbar::TComboTrackBar* TBPosition;
	Fmx::Combotrackbar::TComboTrackBar* TBWidth;
	void __fastcall PC1Change(System::TObject* Sender);
	void __fastcall CBBevelChange(System::TObject* Sender);
	void __fastcall CBTransparentChange(System::TObject* Sender);
	void __fastcall CBRoundChange(System::TObject* Sender);
	void __fastcall UDBevWChangeTracking(System::TObject* Sender);
	void __fastcall UDRoundSizeChangeTracking(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall TabControl1Change(System::TObject* Sender);
	void __fastcall BBackColorChange(System::TObject* Sender);
	void __fastcall CBVisibleChange(System::TObject* Sender);
	void __fastcall TBWidthChangeTracking(System::TObject* Sender);
	void __fastcall TBPositionChangeTracking(System::TObject* Sender);
	void __fastcall TBSizeChangeTracking(System::TObject* Sender);
	void __fastcall CBSideChange(System::TObject* Sender);
	
private:
	Fmxtee::Procs::TTeeCustomShape* Shape;
	Fmxtee::Editor::Font::TFontEditor* FFontEditor;
	Fmxtee::Editor::Stroke::TStrokeEditor* FPenEditor;
	Fmxtee::Editor::Picture::TBackImageEditor* FPictureEditor;
	Fmxtee::Editor::Brush::TBrushEditor* FBrushEditor;
	Fmxtee::Editor::Shadow::TShadowEditor* FEmbossEditor;
	Fmxtee::Editor::Shadow::TShadowEditor* FShadowEditor;
	
public:
	__classmethod TTeeShapeEditor* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Procs::TTeeCustomShape* const AShape);
	__classmethod bool __fastcall Edit(System::Classes::TComponent* const AOwner, Fmxtee::Procs::TTeeCustomShape* const AShape);
	__classmethod TTeeShapeEditor* __fastcall Embedd(System::Classes::TComponent* const AOwner, Fmx::Types::TFmxObject* const AParent);
	__classmethod TTeeShapeEditor* __fastcall InsertForm(Fmxtee::Procs::TTeeCustomShape* const AShape, Fmx::Types::TFmxObject* const AParent);
	void __fastcall RefreshShape(Fmxtee::Procs::TTeeCustomShape* const AShape);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TTeeShapeEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TTeeShapeEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TTeeShapeEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Customshape */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_CUSTOMSHAPE)
using namespace Fmxtee::Editor::Customshape;
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
#endif	// Fmxtee_Editor_CustomshapeHPP
