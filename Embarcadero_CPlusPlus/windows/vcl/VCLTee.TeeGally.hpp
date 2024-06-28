// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeGally.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeegallyHPP
#define Vcltee_TeegallyHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.StrUtils.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeeGalleryPanel.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeLisB.hpp>
#include <VCLTee.TeeGDIPlus.hpp>
#include <VCLTee.TeeFunci.hpp>
#include <VCLTee.TeePenDlg.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teegally
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTeeGallery;
class DELPHICLASS TTeeTemplate;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TTeeGallery : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TPanel* P1;
	Vcl::Stdctrls::TCheckBox* CB3D;
	Vcl::Comctrls::TTabControl* TabPages;
	Vcl::Comctrls::TPageControl* TabTypes;
	Vcltee::Teegallerypanel::TChartGalleryPanel* ChartGalleryPanel1;
	Vcl::Stdctrls::TCheckBox* CBSmooth;
	Vcltee::Tecanvas::TComboFlat* CBPalette;
	Vcl::Extctrls::TPanel* PanelButtons;
	Vcl::Stdctrls::TButton* BOK;
	Vcl::Stdctrls::TButton* BCancel;
	Vcl::Stdctrls::TEdit* ESearch;
	Vcl::Extctrls::TPanel* TopPanel;
	Vcltee::Tecanvas::TComboFlat* CBPage;
	Vcltee::Teelisb::TChartListBox* ChartListBox1;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcltee::Teegallerypanel::TChartGalleryPanel* ChartSubGallery;
	Vcl::Comctrls::TTabSheet* TabFunctions;
	Vcl::Comctrls::TTabSheet* TabSeries;
	Vcl::Stdctrls::TListBox* LBFuncs;
	Vcl::Extctrls::TSplitter* Splitter2;
	Vcltee::Chart::TChart* ChartFunctions;
	Vcl::Extctrls::TPanel* Panel2;
	Vcltee::Tecanvas::TComboFlat* CBFuncPage;
	Vcl::Stdctrls::TLabel* LData;
	Vcl::Comctrls::TTrackBar* TBData;
	Vcl::Stdctrls::TLabel* LPeriod;
	Vcl::Stdctrls::TEdit* EPeriod;
	Vcl::Comctrls::TUpDown* CBPeriod;
	Vcl::Buttons::TSpeedButton* SpeedButton1;
	Vcl::Comctrls::TTabSheet* TabTemplates;
	Vcltee::Teegallerypanel::TChartGalleryPanel* Templates;
	void __fastcall CB3DClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall TabPagesChange(System::TObject* Sender);
	void __fastcall TabTypesChange(System::TObject* Sender);
	void __fastcall ChartGalleryPanel1SelectedChart(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CBSmoothClick(System::TObject* Sender);
	void __fastcall CBPaletteChange(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall ESearchClick(System::TObject* Sender);
	void __fastcall ESearchChange(System::TObject* Sender);
	void __fastcall CBPageChange(System::TObject* Sender);
	void __fastcall ChartListBox1Click(System::TObject* Sender);
	void __fastcall LBFuncsClick(System::TObject* Sender);
	void __fastcall EPeriodChange(System::TObject* Sender);
	void __fastcall TBDataChange(System::TObject* Sender);
	void __fastcall CBFuncPageChange(System::TObject* Sender);
	void __fastcall SpeedButton1Click(System::TObject* Sender);
	void __fastcall ChartSubGallerySelectedChart(System::TObject* Sender);
	void __fastcall LBFuncsDblClick(System::TObject* Sender);
	void __fastcall TabTypesGetImageIndex(System::TObject* Sender, int TabIndex, int &ImageIndex);
	void __fastcall BOKClick(System::TObject* Sender);
	
private:
	bool IHideFunctions;
	bool InFunctions;
	bool OnlyFunctions;
	Vcltee::Chart::TChart* IChart;
	Vcltee::Teengine::TChartSeriesClass OldClass;
	Vcltee::Teengine::TChartSeries* IOldSeries;
	Vcltee::Chart::TCustomChart* ITargetChart;
	Vcltee::Chart::TCustomChart* IFunctionChart;
	System::Classes::TNotifyEvent FSelectedFunction;
	void __fastcall AddFunctionDemo(Vcltee::Teengine::TTeeSeriesType* const AType);
	void __fastcall AddFunctions(const System::UnicodeString APage);
	void __fastcall AddSampleData(Vcltee::Teengine::TTeeFunction* const AFunction, Vcltee::Teengine::TChartSeries* const ASeries, int ANum);
	void __fastcall CreateChartList(const System::UnicodeString APage);
	Vcltee::Teengine::TTeeFunction* __fastcall CurrentFunction();
	void __fastcall FillGalleryPages(System::Classes::TStrings* const AItems);
	void __fastcall GenerateTemplates();
	bool __fastcall GetSeriesClass(/* out */ Vcltee::Teengine::TChartSeriesClass &AClass, /* out */ Vcltee::Teengine::TTeeFunctionClass &AFunction, /* out */ int &ASubIndex);
	__classmethod void __fastcall LoadTemplateChart(Vcltee::Chart::TCustomChart* const Dest, Vcltee::Chart::TCustomChart* const Source);
	void __fastcall PrepareGallery(Vcltee::Teegallerypanel::TChartGalleryPanel* const AGallery);
	Vcltee::Teengine::TTeeSeriesType* __fastcall SelectedFunction();
	int __fastcall SelectedPaletteIndex();
	void __fastcall SetPalette(int Index);
	void __fastcall ShowSubGallery(System::TObject* Sender);
	void __fastcall SwitchAlternate();
	
public:
	int IGalleryWidth;
	int IGalleryHeight;
	bool AlternateStyle;
	void __fastcall HideButtons();
	void __fastcall HideFunctions();
	__classmethod TTeeGallery* __fastcall AddFunctionGallery(System::Classes::TComponent* const AOwner, Vcltee::Chart::TCustomChart* const AChart, const System::Classes::TNotifyEvent Selected);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TTeeGallery(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TTeeGallery(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TTeeGallery() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TTeeGallery(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


#ifndef _WIN64
typedef System::TMetaClass* TTeeTemplateClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TTeeTemplateClass);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTeeTemplate : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Vcltee::Teegallerypanel::TChartGalleryPanel* Templates;
	
protected:
	System::Classes::TComponent* Owner;
	Vcltee::Teegallerypanel::TGalleryChart* __fastcall NewTemplate(const System::UnicodeString ATitle);
	
public:
	virtual void __fastcall Add();
public:
	/* TObject.Create */ inline __fastcall TTeeTemplate() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTeeTemplate() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TTeeTemplateClass TeeTemplateClass;
#define TeeMsg_RememberGallerySize L"RememberGallerySize"
#define TeeMsg_GalleryCols L"GalleryColumns"
static const System::Int8 TeeDefaultGalleryCols = System::Int8(0x4);
extern DELPHI_PACKAGE Vcltee::Teengine::TChartSeries* __fastcall CreateNewSeriesGallery(System::Classes::TComponent* const AOwner, Vcltee::Teengine::TCustomAxisPanel* const AChart, int AGalleryWidth = 0x0, int AGalleryHeight = 0x0)/* overload */;
extern DELPHI_PACKAGE Vcltee::Teengine::TChartSeries* __fastcall CreateNewSeriesGallery(System::Classes::TComponent* const AOwner, Vcltee::Teengine::TChartSeries* const OldSeries, Vcltee::Teengine::TCustomAxisPanel* const tmpChart, bool ShowFunctions, bool CheckSeries, int &SubIndex, int AGalleryWidth = 0x0, int AGalleryHeight = 0x0)/* overload */;
extern DELPHI_PACKAGE void __fastcall ChangeSeriesTypeGallery(System::Classes::TComponent* const AOwner, Vcltee::Teengine::TChartSeries* &tmpSeries);
extern DELPHI_PACKAGE void __fastcall ChangeAllSeriesGallery(System::Classes::TComponent* const AOwner, Vcltee::Chart::TCustomChart* const AChart);
extern DELPHI_PACKAGE Vcltee::Teengine::TTeeFunctionClass __fastcall GetChartGalleryFunction(System::Classes::TComponent* const AOwner);
}	/* namespace Teegally */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEGALLY)
using namespace Vcltee::Teegally;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeegallyHPP
