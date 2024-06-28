// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeDBSourceEditor.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeedbsourceeditorHPP
#define Vcltee_TeedbsourceeditorHPP

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
#include <Data.DB.hpp>
#include <System.Types.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.DBChart.hpp>
#include <VCLTee.TeeDBEdit.hpp>
#include <VCLTee.TeeSelectList.hpp>
#include <VCLTee.TeCanvas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teedbsourceeditor
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBChartSourceEditor;
class DELPHICLASS TSingleRecordSeriesSource;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBChartSourceEditor : public Vcltee::Teedbedit::TBaseDBChartEditor
{
	typedef Vcltee::Teedbedit::TBaseDBChartEditor inherited;
	
__published:
	void __fastcall BApplyClick(System::TObject* Sender);
	HIDESBASE void __fastcall FormShow(System::TObject* Sender);
	HIDESBASE void __fastcall CBSourcesChange(System::TObject* Sender);
	HIDESBASE void __fastcall FormDestroy(System::TObject* Sender);
	
private:
	Vcltee::Teeselectlist::TSelectListForm* ISources;
	HIDESBASE void __fastcall FillFields();
	Data::Db::TDataSource* __fastcall DataSource();
	void __fastcall OnChangeSources(System::TObject* Sender);
	
protected:
	virtual bool __fastcall IsValid(System::Classes::TComponent* AComponent);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TDBChartSourceEditor(System::Classes::TComponent* AOwner) : Vcltee::Teedbedit::TBaseDBChartEditor(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TDBChartSourceEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcltee::Teedbedit::TBaseDBChartEditor(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TDBChartSourceEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDBChartSourceEditor(HWND ParentWindow) : Vcltee::Teedbedit::TBaseDBChartEditor(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TSingleRecordSeriesSource : public Vcltee::Dbchart::TTeeSeriesDBSource
{
	typedef Vcltee::Dbchart::TTeeSeriesDBSource inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Description();
	__classmethod virtual System::Classes::TComponentClass __fastcall Editor();
	__classmethod virtual bool __fastcall HasSeries(Vcltee::Teengine::TChartSeries* ASeries);
public:
	/* TTeeSeriesSource.Create */ inline __fastcall virtual TSingleRecordSeriesSource(System::Classes::TComponent* AOwner) : Vcltee::Dbchart::TTeeSeriesDBSource(AOwner) { }
	/* TTeeSeriesSource.Destroy */ inline __fastcall virtual ~TSingleRecordSeriesSource() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teedbsourceeditor */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEDBSOURCEEDITOR)
using namespace Vcltee::Teedbsourceeditor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeedbsourceeditorHPP
