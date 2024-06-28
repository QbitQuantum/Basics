// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Strings.pas' rev: 34.00 (Android)

#ifndef Fmxtee_Editor_StringsHPP
#define Fmxtee_Editor_StringsHPP

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
#include <FMX.Memo.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Layouts.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Strings
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStringsEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TStringsEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TPanel* Panel1;
	Fmx::Stdctrls::TPanel* Panel2;
	Fmx::Stdctrls::TButton* Button1;
	Fmx::Stdctrls::TButton* Button2;
	Fmx::Stdctrls::TButton* Button3;
	Fmx::Stdctrls::TButton* Button4;
	Fmx::Stdctrls::TButton* Button5;
	Fmx::Memo::TMemo* Memo1;
	Fmx::Dialogs::TOpenDialog* OpenDialog1;
	Fmx::Dialogs::TSaveDialog* SaveDialog1;
	void __fastcall Button3Click(System::TObject* Sender);
	void __fastcall Button4Click(System::TObject* Sender);
	void __fastcall Button5Click(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	
private:
	System::Classes::TStrings* Strings;
	
public:
	__classmethod bool __fastcall Edit(System::Classes::TComponent* AOwner, System::Classes::TStrings* AStrings);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TStringsEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TStringsEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TStringsEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Strings */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_STRINGS)
using namespace Fmxtee::Editor::Strings;
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
#endif	// Fmxtee_Editor_StringsHPP
