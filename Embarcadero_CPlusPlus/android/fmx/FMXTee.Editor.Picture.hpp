// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Picture.pas' rev: 34.00 (Android)

#ifndef Fmxtee_Editor_PictureHPP
#define Fmxtee_Editor_PictureHPP

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
#include <FMX.SpinBox.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Objects.hpp>
#include <FMXTee.Canvas.hpp>
#include <FMXTee.RadioGroup.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.ListBox.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Picture
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBackImageEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBackImageEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TPanel* PanelButtons;
	Fmx::Stdctrls::TButton* Button2;
	Fmx::Stdctrls::TButton* Button3;
	Fmx::Tabcontrol::TTabControl* TabControl1;
	Fmx::Tabcontrol::TTabItem* TabOptions;
	Fmx::Tabcontrol::TTabItem* TabBounds;
	Fmxtee::Radiogroup::TRadioGroup* RGBitmap;
	Fmx::Stdctrls::TRadioButton* RadioButton1;
	Fmx::Stdctrls::TRadioButton* RadioButton2;
	Fmx::Stdctrls::TRadioButton* RadioButton3;
	Fmx::Stdctrls::TRadioButton* RadioButton4;
	Fmx::Stdctrls::TGroupBox* GBPosition;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Stdctrls::TLabel* Label5;
	Fmx::Spinbox::TSpinBox* UDLeft;
	Fmx::Spinbox::TSpinBox* UDTop;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Spinbox::TSpinBox* UDRight;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Spinbox::TSpinBox* UDBottom;
	Fmx::Objects::TRectangle* Bevel1;
	Fmx::Objects::TImage* Image1;
	Fmx::Stdctrls::TLabel* LabelSize;
	Fmx::Stdctrls::TLabel* LabelExt;
	Fmx::Stdctrls::TButton* BBrowse;
	Fmx::Stdctrls::TButton* Button1;
	Fmx::Tabcontrol::TTabItem* TabGallery;
	Fmx::Stdctrls::TLabel* LQuality;
	Fmx::Listbox::TComboBox* CBQuality;
	Fmx::Listbox::TListBoxItem* ListBoxItem1;
	Fmx::Listbox::TListBoxItem* ListBoxItem2;
	void __fastcall BBrowseClick(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall UDLeftChange(System::TObject* Sender);
	void __fastcall RGBitmapChange(System::TObject* Sender);
	void __fastcall UDTopChange(System::TObject* Sender);
	void __fastcall UDRightChange(System::TObject* Sender);
	void __fastcall UDBottomChange(System::TObject* Sender);
	void __fastcall TabControl1Change(System::TObject* Sender);
	void __fastcall CBQualityChange(System::TObject* Sender);
	
private:
	Fmxtee::Canvas::TPicture* FPicture;
	Fmx::Forms::TCommonCustomForm* IBrush;
	void __fastcall EnableImageControls();
	void __fastcall SetBrowseCaption();
	void __fastcall TextureChanged(System::TObject* Sender);
	
public:
	__classmethod System::UnicodeString __fastcall BitmapFileFilter();
	__classmethod TBackImageEditor* __fastcall InsertForm(Fmxtee::Canvas::TPicture* const APicture, Fmx::Types::TFmxObject* const AParent);
	__classmethod System::UnicodeString __fastcall GetPictureFileName(System::Classes::TComponent* const AOwner);
	void __fastcall RefreshPicture(Fmxtee::Canvas::TPicture* const APicture);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TBackImageEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TBackImageEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TBackImageEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString __fastcall StripHotKey(const System::UnicodeString S);
}	/* namespace Picture */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_PICTURE)
using namespace Fmxtee::Editor::Picture;
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
#endif	// Fmxtee_Editor_PictureHPP
