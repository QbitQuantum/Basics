// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeStringsEditor.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeestringseditorHPP
#define Vcltee_TeestringseditorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Clipbrd.hpp>
#include <Vcl.Buttons.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeeConst.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teestringseditor
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStringsEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TStringsEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Stdctrls::TButton* Button1;
	Vcl::Stdctrls::TButton* Button2;
	Vcl::Stdctrls::TButton* Button3;
	Vcl::Stdctrls::TMemo* Memo1;
	Vcl::Stdctrls::TButton* Button4;
	Vcl::Stdctrls::TButton* Button5;
	Vcl::Dialogs::TOpenDialog* OpenDialog1;
	Vcl::Dialogs::TSaveDialog* SaveDialog1;
	void __fastcall Button3Click(System::TObject* Sender);
	void __fastcall Button4Click(System::TObject* Sender);
	void __fastcall Button5Click(System::TObject* Sender);
	void __fastcall FormKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall FormCreate(System::TObject* Sender);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TStringsEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TStringsEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TStringsEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TStringsEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall TeeEditStrings(System::Classes::TComponent* AOwner, System::Classes::TStrings* Strings, bool ReadOnly = false)/* overload */;
extern DELPHI_PACKAGE bool __fastcall TeeEditStrings(System::Classes::TComponent* AOwner, System::UnicodeString &Text, bool ReadOnly = false)/* overload */;
}	/* namespace Teestringseditor */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEESTRINGSEDITOR)
using namespace Vcltee::Teestringseditor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeestringseditorHPP
