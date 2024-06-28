// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.AxisMaxMin.pas' rev: 34.00 (iOS)

#ifndef Fmxtee_Editor_AxismaxminHPP
#define Fmxtee_Editor_AxismaxminHPP

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
#include <FMX.Dialogs.hpp>
#include <FMXTee.Engine.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Axismaxmin
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAxisMaxMin;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAxisMaxMin : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TLabel* LMax;
	Fmx::Stdctrls::TLabel* LMin;
	Fmx::Stdctrls::TButton* BitBtn1;
	Fmx::Stdctrls::TButton* BitBtn2;
	Fmx::Edit::TEdit* EMaximum;
	Fmx::Edit::TEdit* EMinimum;
	
private:
	Fmxtee::Engine::TChartAxis* Axis;
	bool IsMax;
	bool __fastcall IsDateTime();
	void __fastcall Prepare();
	
public:
	__classmethod bool __fastcall Edit(System::Classes::TComponent* const AOwner, Fmxtee::Engine::TChartAxis* const AAxis, Fmx::Stdctrls::TCheckBox* const ACheckBox, bool IsMaximum);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TAxisMaxMin(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TAxisMaxMin(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TAxisMaxMin() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Axismaxmin */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_AXISMAXMIN)
using namespace Fmxtee::Editor::Axismaxmin;
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
#endif	// Fmxtee_Editor_AxismaxminHPP
