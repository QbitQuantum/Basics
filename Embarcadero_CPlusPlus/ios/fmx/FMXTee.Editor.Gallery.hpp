// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Gallery.pas' rev: 34.00 (iOS)

#ifndef Fmxtee_Editor_GalleryHPP
#define Fmxtee_Editor_GalleryHPP

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
#include <System.Generics.Collections.hpp>
#include <System.Variants.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.ComboTrackBar.hpp>
#include <FMXTee.Chart.GalleryPanel.hpp>
#include <FMXTee.Engine.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Edit.hpp>
#include <FMXTee.Editor.Functions.Gallery.hpp>
#include <FMXTee.Chart.ListBox.hpp>
#include <FMXTee.Chart.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Gallery
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TChartGallery;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TChartGallery : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TPanel* Panel1;
	Fmx::Stdctrls::TButton* BOK;
	Fmx::Stdctrls::TButton* BCancel;
	Fmx::Stdctrls::TCheckBox* CB3D;
	Fmx::Listbox::TComboBox* CBPalette;
	Fmx::Tabcontrol::TTabControl* TabTypes;
	Fmx::Tabcontrol::TTabItem* TabSeries;
	Fmx::Tabcontrol::TTabItem* TabFunctions;
	Fmx::Tabcontrol::TTabControl* TabPages;
	Fmx::Stdctrls::TPanel* PanelButtons;
	Fmx::Combotrackbar::TComboTrackBar* CBCount;
	Fmx::Layouts::TLayout* TopPanel;
	Fmx::Listbox::TComboBox* CBPage;
	Fmx::Stdctrls::TSpeedButton* SpeedButton1;
	Fmxtee::Chart::Listbox::TChartListBox* ChartListBox1;
	Fmx::Stdctrls::TSplitter* Splitter1;
	Fmxtee::Chart::Gallerypanel::TChartGalleryPanel* ChartSubGallery;
	void __fastcall CB3DChange(System::TObject* Sender);
	void __fastcall BOKClick(System::TObject* Sender);
	void __fastcall BCancelClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CBPaletteChange(System::TObject* Sender);
	void __fastcall TabTypesChange(System::TObject* Sender);
	void __fastcall CBCountChangeTracking(System::TObject* Sender);
	void __fastcall FormResize(System::TObject* Sender);
	void __fastcall TabPagesChange(System::TObject* Sender);
	void __fastcall ChartListBox1Change(System::TObject* Sender);
	void __fastcall CBPageChange(System::TObject* Sender);
	void __fastcall SpeedButton1Click(System::TObject* Sender);
	void __fastcall ChartSubGallerySelectedChart(System::TObject* Sender);
	
private:
	bool FEnableCount;
	bool OnlyFunctions;
	System::Classes::TNotifyEvent FOnChangeChart;
	Fmxtee::Engine::TChartSeriesClass OldClass;
	bool IChanging;
	Fmxtee::Chart::TChart* IChart;
	Fmxtee::Editor::Functions::Gallery::TFunctionsGallery* IFuncGallery;
	void __fastcall AddTabPages();
	void __fastcall ChangedChart(System::TObject* Sender);
	void __fastcall CreateChartList(const System::UnicodeString APage);
	void __fastcall FillGalleryPages(System::Classes::TStrings* const AItems);
	bool __fastcall GetSeriesClass(/* out */ Fmxtee::Engine::TChartSeriesClass &AClass, /* out */ Fmxtee::Engine::TTeeFunctionClass &AFunction, /* out */ int &ASubIndex);
	void __fastcall PrepareGallery(Fmxtee::Chart::Gallerypanel::TChartGalleryPanel* const AGallery);
	int __fastcall SelectedPaletteIndex();
	void __fastcall ShowSubGallery(System::TObject* Sender);
	void __fastcall SwitchAlternate();
	
protected:
	bool AlternateStyle;
	
public:
	Fmxtee::Chart::Gallerypanel::TChartGalleryPanel* __fastcall Gallery();
	__classmethod Fmxtee::Engine::TChartSeriesClass __fastcall ChangeSeries(System::Classes::TComponent* const AOwner, Fmxtee::Engine::TChartSeries* const ASeries);
	__classmethod Fmxtee::Engine::TTeeFunctionClass __fastcall ChooseFunction(System::Classes::TComponent* const AOwner);
	__classmethod Fmxtee::Engine::TChartSeriesClass __fastcall ChooseSeries(System::Classes::TComponent* const AOwner, /* out */ int &SubIndex, int DefaultPalette = 0xffffffff)/* overload */;
	__classmethod Fmxtee::Engine::TChartSeriesClass __fastcall ChooseSeries(System::Classes::TComponent* const AOwner, /* out */ Fmxtee::Engine::TTeeFunctionClass &FunctionType, /* out */ int &SubIndex, int DefaultPalette = 0xffffffff)/* overload */;
	__classmethod Fmxtee::Engine::TChartSeriesClass __fastcall ChooseSeries(System::Classes::TComponent* const AOwner, /* out */ Fmxtee::Engine::TTeeFunctionClass &FunctionType, /* out */ int &SeriesCount, /* out */ int &SubIndex, int DefaultPalette = 0xffffffff, bool AEnableCount = true)/* overload */;
	__property System::Classes::TNotifyEvent OnChangeChart = {read=FOnChangeChart, write=FOnChangeChart};
public:
	/* TCustomForm.Create */ inline __fastcall virtual TChartGallery(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TChartGallery(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TChartGallery() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Gallery */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_GALLERY)
using namespace Fmxtee::Editor::Gallery;
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
#endif	// Fmxtee_Editor_GalleryHPP
