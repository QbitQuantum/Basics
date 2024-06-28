// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Functions.Gallery.pas' rev: 34.00 (Android)

#ifndef Fmxtee_Editor_Functions_GalleryHPP
#define Fmxtee_Editor_Functions_GalleryHPP

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
#include <System.Generics.Collections.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMXTee.Engine.hpp>
#include <FMXTee.Procs.hpp>
#include <FMXTee.Chart.hpp>
#include <FMX.Objects.hpp>
#include <FMXTee.Chart.Functions.hpp>
#include <FMX.Edit.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Functions
{
namespace Gallery
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFunctionsGallery;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFunctionsGallery : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TPanel* Panel1;
	Fmx::Listbox::TListBox* LBFuncs;
	Fmx::Stdctrls::TSplitter* Splitter1;
	Fmxtee::Chart::TChart* ChartFunctions;
	Fmx::Listbox::TComboBox* CBGroup;
	Fmx::Listbox::TListBoxItem* ListBoxItem1;
	Fmx::Stdctrls::TTrackBar* TBData;
	Fmx::Objects::TText* Text1;
	Fmx::Objects::TText* Text2;
	Fmx::Stdctrls::TPanel* PanelBottom;
	Fmx::Stdctrls::TPanel* PanelButtons;
	Fmx::Stdctrls::TButton* Button2;
	Fmx::Stdctrls::TButton* Button3;
	Fmx::Objects::TText* Text3;
	Fmx::Stdctrls::TTrackBar* TBPeriod;
	Fmx::Stdctrls::TLabel* LPeriod;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall LBFuncsChange(System::TObject* Sender);
	void __fastcall CBGroupChange(System::TObject* Sender);
	void __fastcall TBDataChange(System::TObject* Sender);
	void __fastcall TBPeriodChange(System::TObject* Sender);
	void __fastcall ChartFunctionsClickTitle(Fmxtee::Chart::TCustomChart* Sender, Fmxtee::Chart::TChartTitle* ATitle, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	
private:
	void __fastcall AddFunctionDemo(Fmxtee::Engine::TTeeSeriesType* const AType);
	void __fastcall AddFunctions(const System::UnicodeString AGroup);
	void __fastcall AddGroups();
	void __fastcall AddSampleData(Fmxtee::Engine::TTeeFunction* const AFunction, Fmxtee::Engine::TChartSeries* const ASeries, int ANum);
	Fmxtee::Engine::TTeeFunction* __fastcall CurrentFunction();
	
public:
	Fmxtee::Engine::TTeeSeriesType* __fastcall SelectedFunction();
	Fmxtee::Engine::TTeeFunctionClass __fastcall SelectedFunctionClass();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFunctionsGallery(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFunctionsGallery(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFunctionsGallery() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Gallery */
}	/* namespace Functions */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_FUNCTIONS_GALLERY)
using namespace Fmxtee::Editor::Functions::Gallery;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_FUNCTIONS)
using namespace Fmxtee::Editor::Functions;
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
#endif	// Fmxtee_Editor_Functions_GalleryHPP
