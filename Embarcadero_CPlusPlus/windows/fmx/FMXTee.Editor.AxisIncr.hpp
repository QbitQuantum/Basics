// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.AxisIncr.pas' rev: 34.00 (Windows)

#ifndef Fmxtee_Editor_AxisincrHPP
#define Fmxtee_Editor_AxisincrHPP

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
#include <FMX.ListBox.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Dialogs.hpp>
#include <FMXTee.Engine.hpp>
#include <FMXTee.Procs.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Axisincr
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAxisIncrement;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAxisIncrement : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Listbox::TComboBox* CBSteps;
	Fmx::Edit::TEdit* ECustom;
	Fmx::Stdctrls::TButton* BOk;
	Fmx::Stdctrls::TButton* BCancel;
	Fmx::Stdctrls::TCheckBox* CBExact;
	void __fastcall CBStepsChange(System::TObject* Sender);
	void __fastcall CBExactChange(System::TObject* Sender);
	void __fastcall ECustomTyping(System::TObject* Sender);
	
private:
	Fmxtee::Engine::TChartAxis* Axis;
	
public:
	bool IsDateTime;
	bool IsExact;
	double Increment;
	Fmxtee::Procs::TDateTimeStep IStep;
	__classmethod bool __fastcall ChangeIncrement(System::Classes::TComponent* AOwner, Fmxtee::Engine::TChartAxis* AAxis);
	__classmethod System::UnicodeString __fastcall GetIncrementText(System::Classes::TComponent* AOwner, const double Increment, bool IsDateTime, bool ExactDateTime, const System::UnicodeString AFormat);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TAxisIncrement(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TAxisIncrement(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TAxisIncrement() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Axisincr */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_AXISINCR)
using namespace Fmxtee::Editor::Axisincr;
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
#endif	// Fmxtee_Editor_AxisincrHPP
