// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Source.pas' rev: 34.00 (Android)

#ifndef Fmxtee_Editor_SourceHPP
#define Fmxtee_Editor_SourceHPP

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
#include <FMX.ListBox.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMXTee.Chart.hpp>
#include <FMXTee.Engine.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Source
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBaseSourceEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBaseSourceEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TPanel* Pan;
	Fmx::Stdctrls::TLabel* LLabel;
	Fmx::Listbox::TComboBox* CBSources;
	Fmx::Stdctrls::TPanel* PanelApply;
	Fmx::Stdctrls::TButton* BApply;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall CBSourcesChange(System::TObject* Sender);
	void __fastcall FormCloseQuery(System::TObject* Sender, bool &CanClose);
	void __fastcall FormActivate(System::TObject* Sender);
	
private:
	Fmxtee::Engine::TTeeSeriesSource* IDataSource;
	
protected:
	Fmxtee::Chart::TCustomChart* Chart;
	Fmxtee::Engine::TChartSeries* TheSeries;
	bool SkipValidation;
	void __fastcall AddComponentDataSource(System::Classes::TComponent* const AComponent, Fmx::Listbox::TCustomListBox* const AItems, bool AddCurrent);
	void __fastcall CheckDataSource(const Fmxtee::Engine::TTeeSeriesSourceClass SourceClass);
	void __fastcall CheckReplaceSource(Fmxtee::Engine::TTeeSeriesSource* const NewSource);
	virtual bool __fastcall IsValid(System::Classes::TComponent* AComponent);
	
public:
	DYNAMIC void __fastcall Translate();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TBaseSourceEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TBaseSourceEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TBaseSourceEditor() { }
	
};


typedef void __fastcall (__closure *TAddComponentDataSource)(System::Classes::TComponent* const AComponent, Fmx::Listbox::TCustomListBox* const AItems, bool AddCurrent);

typedef void __fastcall (__closure *TOnGetDesignerNamesEvent)(TAddComponentDataSource AProc, Fmxtee::Engine::TChartSeries* ASeries, Fmx::Listbox::TCustomListBox* AItems, bool AddCurrent);

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Source */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_SOURCE)
using namespace Fmxtee::Editor::Source;
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
#endif	// Fmxtee_Editor_SourceHPP
