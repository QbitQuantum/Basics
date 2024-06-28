// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Series.Bar.Stack.pas' rev: 34.00 (Android)

#ifndef Fmxtee_Editor_Series_Bar_StackHPP
#define Fmxtee_Editor_Series_Bar_StackHPP

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
#include <FMXTee.Series.hpp>
#include <FMXTee.RadioGroup.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Series
{
namespace Bar
{
namespace Stack
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStackBarSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TStackBarSeriesEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TCheckBox* CBYOrigin;
	Fmx::Edit::TEdit* EYOrigin;
	Fmx::Spinbox::TSpinBox* UDGroup;
	Fmxtee::Radiogroup::TRadioGroup* RGMultiBar;
	void __fastcall EYOriginChange(System::TObject* Sender);
	void __fastcall UDGroupChange(System::TObject* Sender);
	void __fastcall RGMultiBarChange(System::TObject* Sender);
	void __fastcall EYOriginTyping(System::TObject* Sender);
	
private:
	Fmxtee::Series::TCustomBarSeries* Bar;
	
public:
	__classmethod Fmx::Forms::TForm* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Series::TCustomBarSeries* const ABar);
	void __fastcall RefreshBar(Fmxtee::Series::TCustomBarSeries* const ABar);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TStackBarSeriesEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TStackBarSeriesEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TStackBarSeriesEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Stack */
}	/* namespace Bar */
}	/* namespace Series */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_SERIES_BAR_STACK)
using namespace Fmxtee::Editor::Series::Bar::Stack;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_SERIES_BAR)
using namespace Fmxtee::Editor::Series::Bar;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_SERIES)
using namespace Fmxtee::Editor::Series;
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
#endif	// Fmxtee_Editor_Series_Bar_StackHPP
