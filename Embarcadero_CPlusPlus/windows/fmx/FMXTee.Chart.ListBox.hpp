// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Chart.ListBox.pas' rev: 34.00 (Windows)

#ifndef Fmxtee_Chart_ListboxHPP
#define Fmxtee_Chart_ListboxHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <FMX.Types.hpp>
#include <System.UITypes.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Menus.hpp>
#include <FMXTee.Procs.hpp>
#include <FMXTee.Engine.hpp>
#include <FMXTee.Chart.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Controls.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Chart
{
namespace Listbox
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TChartListBox;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TChartListBox : public Fmx::Listbox::TListBox
{
	typedef Fmx::Listbox::TListBox inherited;
	
private:
	Fmxtee::Chart::TCustomChart* FChart;
	Fmxtee::Engine::TSeriesGroup* FGroup;
	bool FColors;
	bool FIcons;
	bool FNames;
	void __fastcall ChangeSeriesColor(System::TObject* Sender);
	void __fastcall CheckActiveCheck(Fmx::Listbox::TListBoxItem* const AItem);
	void __fastcall CheckColor(Fmx::Listbox::TListBoxItem* const AItem);
	void __fastcall CheckIcon(Fmx::Listbox::TListBoxItem* const AItem);
	void __fastcall FillSeries(Fmxtee::Engine::TChartSeries* const OldSeries);
	bool __fastcall GetChecks();
	Fmxtee::Engine::TChartSeries* __fastcall GetSelectedSeries();
	Fmxtee::Engine::TChartSeries* __fastcall GetSeries(int Index);
	Fmxtee::Engine::TCustomSeriesList* __fastcall GetSeriesGroup();
	void __fastcall SelectSeries(int AIndex);
	void __fastcall SetChecks(const bool Value);
	void __fastcall SetColors(const bool Value);
	void __fastcall SetGroup(Fmxtee::Engine::TSeriesGroup* const Value);
	void __fastcall SetIcons(const bool Value);
	void __fastcall SetSelectedSeries(Fmxtee::Engine::TChartSeries* const Value);
	System::UnicodeString __fastcall SeriesItemText(Fmxtee::Engine::TChartSeries* const ASeries);
	void __fastcall SetChart(Fmxtee::Chart::TCustomChart* const Value);
	void __fastcall SetNames(const bool Value);
	void __fastcall UpdateSeries();
	
protected:
	Fmx::Listbox::TListBoxItem* __fastcall AddSeries(Fmxtee::Engine::TChartSeries* const ASeries);
	bool __fastcall AnySelected();
	int __fastcall SelectionCount();
	void __fastcall TeeEvent(Fmxtee::Procs::TTeeEvent* Event);
	
public:
	__fastcall virtual TChartListBox(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TChartListBox();
	bool __fastcall DeleteSeries();
	bool __fastcall RenameSeries();
	__property Fmxtee::Engine::TChartSeries* Series[int Index] = {read=GetSeries};
	
__published:
	__property Fmxtee::Chart::TCustomChart* Chart = {read=FChart, write=SetChart};
	__property Fmxtee::Engine::TChartSeries* SelectedSeries = {read=GetSelectedSeries, write=SetSelectedSeries};
	__property Fmxtee::Engine::TSeriesGroup* SeriesGroup = {read=FGroup, write=SetGroup};
	__property bool ShowActiveCheck = {read=GetChecks, write=SetChecks, default=1};
	__property bool ShowSeriesColor = {read=FColors, write=SetColors, default=1};
	__property bool ShowSeriesIcon = {read=FIcons, write=SetIcons, default=1};
	__property bool ShowSeriesNames = {read=FNames, write=SetNames, default=0};
private:
	void *__ITeeEventListener;	// Fmxtee::Procs::ITeeEventListener 
	
public:
	operator Fmxtee::Procs::ITeeEventListener*(void) { return (Fmxtee::Procs::ITeeEventListener*)&__ITeeEventListener; }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Listbox */
}	/* namespace Chart */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_CHART_LISTBOX)
using namespace Fmxtee::Chart::Listbox;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_CHART)
using namespace Fmxtee::Chart;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE)
using namespace Fmxtee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmxtee_Chart_ListboxHPP
