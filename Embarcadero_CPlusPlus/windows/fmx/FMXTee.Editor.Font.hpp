// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Font.pas' rev: 34.00 (Windows)

#ifndef Fmxtee_Editor_FontHPP
#define Fmxtee_Editor_FontHPP

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
#include <FMXTee.Canvas.hpp>
#include <FMX.Colors.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.TabControl.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Font
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFontEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFontEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Colors::TComboColorBox* BColor;
	Fmx::Stdctrls::TCheckBox* CBBold;
	Fmx::Stdctrls::TCheckBox* CBItalic;
	Fmx::Listbox::TComboBox* CBFamily;
	Fmx::Stdctrls::TCheckBox* CBUnderline;
	Fmx::Stdctrls::TCheckBox* CBStrikeOut;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TTrackBar* TBSize;
	Fmx::Stdctrls::TLabel* LSize;
	Fmx::Tabcontrol::TTabControl* TabControl1;
	Fmx::Tabcontrol::TTabItem* TabFont;
	Fmx::Tabcontrol::TTabItem* TabPattern;
	Fmx::Tabcontrol::TTabItem* TabShadow;
	Fmx::Tabcontrol::TTabItem* TabEmboss;
	Fmx::Tabcontrol::TTabItem* TabOutline;
	void __fastcall CBBoldChange(System::TObject* Sender);
	void __fastcall BColorChange(System::TObject* Sender);
	void __fastcall CBItalicChange(System::TObject* Sender);
	void __fastcall CBUnderlineChange(System::TObject* Sender);
	void __fastcall TBSizeChange(System::TObject* Sender);
	void __fastcall CBStrikeOutChange(System::TObject* Sender);
	void __fastcall CBFamilyChange(System::TObject* Sender);
	void __fastcall TabControl1Change(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	
private:
	Fmxtee::Canvas::TTeeFont* IFont;
	bool ICreating;
	Fmx::Forms::TCommonCustomForm* FShadowEditor;
	Fmx::Forms::TCommonCustomForm* FEmbossEditor;
	Fmx::Forms::TCommonCustomForm* FOutlineEditor;
	Fmx::Forms::TCommonCustomForm* FBrushEditor;
	void __fastcall AddFamily();
	
public:
	__classmethod Fmx::Forms::TForm* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Canvas::TTeeFont* const AFont);
	__classmethod bool __fastcall Edit(System::Classes::TComponent* const AOwner, Fmxtee::Canvas::TTeeFont* const AFont);
	__classmethod TFontEditor* __fastcall Embedd(System::Classes::TComponent* const AOwner, Fmxtee::Canvas::TTeeFont* const AFont, Fmx::Types::TFmxObject* const AParent);
	__classmethod System::Classes::TStringList* __fastcall Fonts();
	void __fastcall RefreshFont(Fmxtee::Canvas::TTeeFont* const AFont);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFontEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFontEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFontEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Font */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_FONT)
using namespace Fmxtee::Editor::Font;
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
#endif	// Fmxtee_Editor_FontHPP
