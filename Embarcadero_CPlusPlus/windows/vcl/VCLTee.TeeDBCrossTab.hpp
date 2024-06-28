// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeDBCrossTab.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeedbcrosstabHPP
#define Vcltee_TeedbcrosstabHPP

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
#include <VCLTee.Chart.hpp>
#include <VCLTee.DBChart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teedbcrosstab
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCrossTabSource;
class DELPHICLASS TDBCrossTabSource;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TGroupFormula : unsigned char { gfCount, gfSum, gfMin, gfMax };

class PASCALIMPLEMENTATION TCrossTabSource : public Vcltee::Dbchart::TTeeSeriesDBSource
{
	typedef Vcltee::Dbchart::TTeeSeriesDBSource inherited;
	
private:
	bool FCase;
	TGroupFormula FFormula;
	System::UnicodeString FGroup;
	bool FHideSeries;
	System::UnicodeString FLabel;
	System::UnicodeString FValue;
	Vcltee::Teengine::TCustomAxisPanel* IParentChart;
	Vcltee::Teengine::TCustomSeriesList* __fastcall DetailList();
	void __fastcall RemoveSeries();
	void __fastcall SetCase(const bool Value);
	void __fastcall SetFormula(const TGroupFormula Value);
	void __fastcall SetGroup(const System::UnicodeString Value);
	void __fastcall SetIParentChart(Vcltee::Teengine::TCustomAxisPanel* const Value);
	void __fastcall SetLabel(const System::UnicodeString Value);
	void __fastcall SetValue(const System::UnicodeString Value);
	
protected:
	Vcltee::Teengine::TChartSeries* __fastcall FindGroup(const System::UnicodeString AGroup);
	void __fastcall InitLoop();
	Vcltee::Teengine::TChartSeries* __fastcall LocateSeries(const System::UnicodeString ATitle);
	void __fastcall NewPoint(Vcltee::Teengine::TChartSeries* const ASeries, int AIndex, const double AValue, const System::UnicodeString ALabel);
	Vcltee::Teengine::TChartSeries* __fastcall NewSeries();
	virtual void __fastcall SetSeries(Vcltee::Teengine::TChartSeries* const Value);
	void __fastcall TeeEvent(Vcltee::Teeprocs::TTeeEvent* Event);
	
public:
	bool UseDetail;
	__fastcall virtual TCrossTabSource(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCrossTabSource();
	
__published:
	__property Active = {default=0};
	__property bool CaseSensitive = {read=FCase, write=SetCase, default=1};
	__property TGroupFormula Formula = {read=FFormula, write=SetFormula, default=1};
	__property System::UnicodeString GroupField = {read=FGroup, write=SetGroup};
	__property bool HideSeries = {read=FHideSeries, write=FHideSeries, default=1};
	__property System::UnicodeString LabelField = {read=FLabel, write=SetLabel};
	__property Series;
	__property System::UnicodeString ValueField = {read=FValue, write=SetValue};
private:
	void *__ITeeEventListener;	// Vcltee::Teeprocs::ITeeEventListener 
	
public:
	operator Vcltee::Teeprocs::ITeeEventListener*(void) { return (Vcltee::Teeprocs::ITeeEventListener*)&__ITeeEventListener; }
	
};


class PASCALIMPLEMENTATION TDBCrossTabSource : public TCrossTabSource
{
	typedef TCrossTabSource inherited;
	
private:
	Data::Db::TDataSet* FDataSet;
	bool LoadingDS;
	Vcltee::Dbchart::TDBChartDataSource* ISource;
	void __fastcall DataSourceCheckDataSet(Data::Db::TDataSet* const ADataSet);
	void __fastcall DataSourceCloseDataSet(Data::Db::TDataSet* const ADataSet);
	void __fastcall LoadDataSet();
	void __fastcall SetDataSet(Data::Db::TDataSet* const Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall SetActive(const bool Value);
	
public:
	__fastcall virtual ~TDBCrossTabSource();
	__classmethod virtual bool __fastcall Available(Vcltee::Teengine::TCustomAxisPanel* AChart);
	__classmethod virtual System::UnicodeString __fastcall Description();
	__classmethod virtual System::Classes::TComponentClass __fastcall Editor();
	__classmethod virtual bool __fastcall HasSeries(Vcltee::Teengine::TChartSeries* ASeries);
	virtual void __fastcall Load();
	
__published:
	__property Data::Db::TDataSet* DataSet = {read=FDataSet, write=SetDataSet};
public:
	/* TCrossTabSource.Create */ inline __fastcall virtual TDBCrossTabSource(System::Classes::TComponent* AOwner) : TCrossTabSource(AOwner) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall FillDataSet(Data::Db::TDataSet* const ADataSet, Vcltee::Teengine::TChartSeries* const ASeries, const System::UnicodeString AGroupField, const System::UnicodeString ALabelField, const System::UnicodeString AValueField, const TGroupFormula GroupFormula);
}	/* namespace Teedbcrosstab */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEDBCROSSTAB)
using namespace Vcltee::Teedbcrosstab;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeedbcrosstabHPP
