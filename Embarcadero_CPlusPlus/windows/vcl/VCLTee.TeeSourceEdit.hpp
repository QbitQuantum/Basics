// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeSourceEdit.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeesourceeditHPP
#define Vcltee_TeesourceeditHPP

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
#include <System.UITypes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.Chart.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teesourceedit
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBaseSourceEditor;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TAddComponentDataSource)(System::Classes::TComponent* const AComponent, System::Classes::TStrings* AItems, bool AddCurrent);

typedef void __fastcall (*TOnGetDesignerNamesEvent)(TAddComponentDataSource AProc, Vcltee::Teengine::TChartSeries* ASeries, System::Classes::TStrings* AItems, bool AddCurrent);

class PASCALIMPLEMENTATION TBaseSourceEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Stdctrls::TLabel* LLabel;
	Vcltee::Tecanvas::TComboFlat* CBSources;
	Vcl::Extctrls::TPanel* Pan;
	Vcl::Extctrls::TPanel* PanelApply;
	Vcl::Stdctrls::TButton* BApply;
	void __fastcall CBSourcesChange(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall FormCloseQuery(System::TObject* Sender, bool &CanClose);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	
protected:
	Vcltee::Chart::TCustomChart* Chart;
	Vcltee::Teengine::TChartSeries* TheSeries;
	bool SkipValidation;
	Vcltee::Teengine::TTeeSeriesSource* IDataSource;
	void __fastcall AddComponentDataSource(System::Classes::TComponent* const AComponent, System::Classes::TStrings* AItems, bool AddCurrent);
	void __fastcall CheckDataSource(Vcltee::Teengine::TTeeSeriesSourceClass SourceClass);
	void __fastcall CheckReplaceSource(Vcltee::Teengine::TTeeSeriesSource* NewSource);
	virtual bool __fastcall IsValid(System::Classes::TComponent* AComponent);
	
public:
	DYNAMIC void __fastcall Translate();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TBaseSourceEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TBaseSourceEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TBaseSourceEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TBaseSourceEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teesourceedit */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEESOURCEEDIT)
using namespace Vcltee::Teesourceedit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeesourceeditHPP
