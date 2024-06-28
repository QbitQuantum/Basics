// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeFuncEdit.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeefunceditHPP
#define Vcltee_TeefunceditHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <VCLTee.TeeSelectList.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeeEdiPeri.hpp>
#include <VCLTee.TeeSourceEdit.hpp>
#include <VCLTee.TeCanvas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teefuncedit
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTeeFuncEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TTeeFuncEditor : public Vcltee::Teesourceedit::TBaseSourceEditor
{
	typedef Vcltee::Teesourceedit::TBaseSourceEditor inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabSource;
	Vcl::Comctrls::TTabSheet* TabOptions;
	Vcl::Extctrls::TPanel* PanSingle;
	Vcl::Stdctrls::TLabel* Label1;
	Vcltee::Tecanvas::TComboFlat* CBSingle;
	Vcl::Stdctrls::TLabel* LValues;
	Vcltee::Tecanvas::TComboFlat* CBValues;
	Vcl::Stdctrls::TButton* BNone;
	Vcl::Extctrls::TTimer* Timer1;
	Vcl::Extctrls::TTimer* Timer2;
	Vcl::Buttons::TSpeedButton* SpeedButton1;
	HIDESBASE void __fastcall FormCreate(System::TObject* Sender);
	HIDESBASE void __fastcall FormShow(System::TObject* Sender);
	HIDESBASE void __fastcall CBSourcesChange(System::TObject* Sender);
	void __fastcall BApplyClick(System::TObject* Sender);
	void __fastcall CBSingleChange(System::TObject* Sender);
	void __fastcall BNoneClick(System::TObject* Sender);
	void __fastcall CBValuesChange(System::TObject* Sender);
	HIDESBASE void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall Timer1Timer(System::TObject* Sender);
	void __fastcall Timer2Timer(System::TObject* Sender);
	void __fastcall SpeedButton1Click(System::TObject* Sender);
	
private:
	bool Filling;
	Vcl::Forms::TForm* IOptions;
	Vcltee::Teeselectlist::TSelectListForm* ISources;
	void __fastcall FillSeries();
	void __fastcall TryCreateNewFunction();
	void __fastcall TeeEvent(Vcltee::Teeprocs::TTeeEvent* Event);
	
public:
	Vcltee::Teengine::TChartSeries* TheSeries;
	Vcltee::Teengine::TTeeFunctionClass __fastcall FunctionClass();
	__classmethod void __fastcall SetValueListCombo(Vcltee::Teengine::TChartSeries* Series, Vcltee::Tecanvas::TComboFlat* Combo);
	DYNAMIC void __fastcall Translate();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TTeeFuncEditor(System::Classes::TComponent* AOwner) : Vcltee::Teesourceedit::TBaseSourceEditor(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TTeeFuncEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcltee::Teesourceedit::TBaseSourceEditor(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TTeeFuncEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TTeeFuncEditor(HWND ParentWindow) : Vcltee::Teesourceedit::TBaseSourceEditor(ParentWindow) { }
	
private:
	void *__ITeeEventListener;	// Vcltee::Teeprocs::ITeeEventListener 
	
public:
	operator Vcltee::Teeprocs::ITeeEventListener*(void) { return (Vcltee::Teeprocs::ITeeEventListener*)&__ITeeEventListener; }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall FillSeriesSources(System::Classes::TStrings* const AItems, System::Classes::TStrings* const AItems2, Vcltee::Teengine::TChartSeries* const TheSeries, bool AddCurrent);
}	/* namespace Teefuncedit */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEFUNCEDIT)
using namespace Vcltee::Teefuncedit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeefunceditHPP
