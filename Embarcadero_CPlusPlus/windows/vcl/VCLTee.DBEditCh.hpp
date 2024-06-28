// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.DBEditCh.pas' rev: 34.00 (Windows)

#ifndef Vcltee_DbeditchHPP
#define Vcltee_DbeditchHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Data.DB.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.DBChart.hpp>
#include <VCLTee.TeeDBEdit.hpp>
#include <VCLTee.TeCanvas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Dbeditch
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBChartEditor;
class DELPHICLASS TDataSetSeriesSource;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBChartEditor : public Vcltee::Teedbedit::TBaseDBChartEditor
{
	typedef Vcltee::Teedbedit::TBaseDBChartEditor inherited;
	
__published:
	Vcl::Forms::TScrollBox* GroupFields;
	Vcl::Stdctrls::TLabel* LLabels;
	Vcltee::Tecanvas::TComboFlat* CBLabelsField;
	void __fastcall CBLabelsFieldChange(System::TObject* Sender);
	HIDESBASE void __fastcall FormShow(System::TObject* Sender);
	void __fastcall BApplyClick(System::TObject* Sender);
	HIDESBASE void __fastcall CBSourcesChange(System::TObject* Sender);
	
private:
	System::StaticArray<Vcl::Stdctrls::TLabel*, 16> LabelValues;
	System::StaticArray<Vcl::Stdctrls::TCheckBox*, 16> CBDateTime;
	void __fastcall CBValuesChange(System::TObject* Sender);
	void __fastcall SetFields();
	void __fastcall SetTextItemIndex(Vcltee::Tecanvas::TComboFlat* Combo);
	
protected:
	virtual bool __fastcall IsValid(System::Classes::TComponent* AComponent);
	
public:
	System::StaticArray<Vcltee::Tecanvas::TComboFlat*, 16> CBValues;
	DYNAMIC void __fastcall Translate();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TDBChartEditor(System::Classes::TComponent* AOwner) : Vcltee::Teedbedit::TBaseDBChartEditor(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TDBChartEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcltee::Teedbedit::TBaseDBChartEditor(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TDBChartEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDBChartEditor(HWND ParentWindow) : Vcltee::Teedbedit::TBaseDBChartEditor(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TDataSetSeriesSource : public Vcltee::Dbchart::TTeeSeriesDBSource
{
	typedef Vcltee::Dbchart::TTeeSeriesDBSource inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Description();
	__classmethod virtual System::Classes::TComponentClass __fastcall Editor();
	__classmethod virtual bool __fastcall HasSeries(Vcltee::Teengine::TChartSeries* ASeries);
public:
	/* TTeeSeriesSource.Create */ inline __fastcall virtual TDataSetSeriesSource(System::Classes::TComponent* AOwner) : Vcltee::Dbchart::TTeeSeriesDBSource(AOwner) { }
	/* TTeeSeriesSource.Destroy */ inline __fastcall virtual ~TDataSetSeriesSource() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const System::Int8 MaxValueSources = System::Int8(0x10);
}	/* namespace Dbeditch */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_DBEDITCH)
using namespace Vcltee::Dbeditch;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_DbeditchHPP
