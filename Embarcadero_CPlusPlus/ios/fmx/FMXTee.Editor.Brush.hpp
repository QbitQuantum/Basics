// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Brush.pas' rev: 34.00 (iOS)

#ifndef Fmxtee_Editor_BrushHPP
#define Fmxtee_Editor_BrushHPP

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
#include <FMX.Dialogs.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Colors.hpp>
#include <FMXTee.Canvas.hpp>
#include <FMXTee.Editor.Picture.hpp>
#include <FMXTee.Editor.Gradient.hpp>
#include <FMX.Layouts.hpp>
#include <FMXTee.Chart.GalleryPanel.hpp>
#include <FMX.Objects.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Brush
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBrushEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBrushEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* TabControl1;
	Fmx::Tabcontrol::TTabItem* TabColor;
	Fmx::Tabcontrol::TTabItem* TabGradient;
	Fmx::Tabcontrol::TTabItem* TabBitmap;
	Fmx::Stdctrls::TPanel* PanelOk;
	Fmx::Stdctrls::TButton* Button1;
	Fmx::Stdctrls::TButton* Button2;
	Fmx::Colors::TColorPanel* ColorPanel1;
	Fmx::Tabcontrol::TTabItem* TabTexture;
	Fmxtee::Chart::Gallerypanel::TChartGalleryPanel* TextureGallery;
	Fmx::Objects::TImage* Image1;
	Fmx::Objects::TImage* Image2;
	Fmx::Objects::TImage* Image3;
	Fmx::Objects::TImage* Image4;
	void __fastcall ColorPanel1Change(System::TObject* Sender);
	void __fastcall Button2Click(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall TabControl1Change(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall TextureGallerySelectedChart(System::TObject* Sender);
	void __fastcall TextureGalleryChangeChart(System::TObject* Sender);
	
private:
	Fmxtee::Canvas::TTeeBrush* FBrush;
	Fmxtee::Canvas::TTeeBrush* IBack;
	Fmxtee::Editor::Picture::TBackImageEditor* FPictureEditor;
	Fmxtee::Editor::Gradient::TGradientEditor* FGradientEditor;
	
public:
	__classmethod bool __fastcall Edit(System::Classes::TComponent* const AOwner, Fmxtee::Canvas::TTeeBrush* const ABrush);
	__classmethod TBrushEditor* __fastcall InsertForm(Fmxtee::Canvas::TTeeBrush* const ABrush, Fmx::Controls::TControl* const AParent);
	void __fastcall RefreshBrush(Fmxtee::Canvas::TTeeBrush* const ABrush);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TBrushEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TBrushEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TBrushEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Brush */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_BRUSH)
using namespace Fmxtee::Editor::Brush;
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
#endif	// Fmxtee_Editor_BrushHPP
