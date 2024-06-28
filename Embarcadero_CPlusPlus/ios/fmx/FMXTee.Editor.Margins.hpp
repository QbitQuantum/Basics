// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Margins.pas' rev: 34.00 (iOS)

#ifndef Fmxtee_Editor_MarginsHPP
#define Fmxtee_Editor_MarginsHPP

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
#include <FMXTee.Engine.hpp>
#include <FMXTee.RadioGroup.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Margins
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMarginsEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TMarginsEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Spinbox::TSpinBox* UDLeft;
	Fmx::Spinbox::TSpinBox* UDTop;
	Fmx::Spinbox::TSpinBox* UDRight;
	Fmx::Spinbox::TSpinBox* UDBottom;
	Fmxtee::Radiogroup::TRadioGroup* RGUnits;
	void __fastcall RGUnitsChange(System::TObject* Sender);
	void __fastcall UDLeftChange(System::TObject* Sender);
	void __fastcall UDTopChange(System::TObject* Sender);
	void __fastcall UDRightChange(System::TObject* Sender);
	void __fastcall UDBottomChange(System::TObject* Sender);
	
private:
	Fmxtee::Engine::TMargins* FMargins;
	
public:
	__classmethod TMarginsEditor* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Engine::TMargins* const AMargins);
	void __fastcall RefreshMargins(Fmxtee::Engine::TMargins* const AMargins);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TMarginsEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TMarginsEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TMarginsEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Margins */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_MARGINS)
using namespace Fmxtee::Editor::Margins;
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
#endif	// Fmxtee_Editor_MarginsHPP
