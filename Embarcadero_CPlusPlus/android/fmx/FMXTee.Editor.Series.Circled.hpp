// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Series.Circled.pas' rev: 34.00 (Android)

#ifndef Fmxtee_Editor_Series_CircledHPP
#define Fmxtee_Editor_Series_CircledHPP

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
#include <FMX.TabControl.hpp>
#include <FMXTee.Series.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Series
{
namespace Circled
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCircledSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCircledSeriesEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* PageControl1;
	Fmx::Tabcontrol::TTabItem* TabOptions;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TCheckBox* CBCircled;
	Fmx::Stdctrls::TCheckBox* CB3D;
	Fmx::Stdctrls::TButton* BBack;
	Fmx::Stdctrls::TCheckBox* CBTransp;
	Fmx::Tabcontrol::TTabItem* TabRadius;
	Fmx::Stdctrls::TGroupBox* GroupBox2;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Stdctrls::TLabel* Label5;
	Fmx::Stdctrls::TCheckBox* CBAutoXR;
	Fmx::Stdctrls::TCheckBox* CBAutoYR;
	Fmx::Spinbox::TSpinBox* UDY;
	Fmx::Spinbox::TSpinBox* UDX;
	Fmx::Tabcontrol::TTabItem* TabShadow;
	Fmx::Tabcontrol::TTabItem* TabEmboss;
	Fmx::Tabcontrol::TTabItem* TabGradient;
	Fmx::Stdctrls::TTrackBar* TBRotation;
	Fmx::Stdctrls::TLabel* LRotation;
	void __fastcall BBackClick(System::TObject* Sender);
	void __fastcall CBCircledChange(System::TObject* Sender);
	void __fastcall CB3DChange(System::TObject* Sender);
	void __fastcall CBTranspChange(System::TObject* Sender);
	void __fastcall CBAutoXRChange(System::TObject* Sender);
	void __fastcall CBAutoYRChange(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall UDXChange(System::TObject* Sender);
	void __fastcall UDYChange(System::TObject* Sender);
	void __fastcall TBRotationChange(System::TObject* Sender);
	
private:
	Fmxtee::Series::TCircledSeries* Circled;
	Fmx::Forms::TForm* FGradientEditor;
	Fmx::Forms::TForm* FShadowEditor;
	Fmx::Forms::TForm* FEmbossEditor;
	
public:
	void __fastcall RefreshCircled(Fmxtee::Series::TCircledSeries* const ACircled);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TCircledSeriesEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TCircledSeriesEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TCircledSeriesEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Circled */
}	/* namespace Series */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_SERIES_CIRCLED)
using namespace Fmxtee::Editor::Series::Circled;
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
#endif	// Fmxtee_Editor_Series_CircledHPP
