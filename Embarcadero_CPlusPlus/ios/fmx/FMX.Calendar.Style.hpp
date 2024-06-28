// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Calendar.Style.pas' rev: 34.00 (iOS)

#ifndef Fmx_Calendar_StyleHPP
#define Fmx_Calendar_StyleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.UITypes.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.ExtCtrls.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Presentation.Style.hpp>
#include <FMX.Calendar.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Calendar
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStyledCalendar;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TStyledCalendar : public Fmx::Presentation::Style::TStyledPresentation
{
	typedef Fmx::Presentation::Style::TStyledPresentation inherited;
	
public:
	static constexpr System::Int8 CountOfVisibleDays = System::Int8(0x2a);
	
	
private:
	bool FNeedChange;
	System::TDateTime FDateTime;
	int FFirstDayOfWeekNum;
	int FDisableDayChange;
	Fmx::Extctrls::TPopupBox* FMonths;
	Fmx::Extctrls::TPopupBox* FYears;
	Fmx::Layouts::TGridLayout* FWeeks;
	Fmx::Layouts::TGridLayout* FWeek;
	Fmx::Listbox::TListBox* FDays;
	Fmx::Stdctrls::TButton* FToday;
	Fmx::Stdctrls::TButton* FPrev;
	Fmx::Stdctrls::TButton* FNext;
	void __fastcall SetDate(System::TDate Value);
	void __fastcall SetDateTime(System::TDateTime Value);
	System::TDate __fastcall GetDate();
	HIDESBASE Fmx::Calendar::TCalendarModel* __fastcall GetModel();
	void __fastcall CalculateFirstDayOfWeek();
	void __fastcall UpdateWeekWidth();
	
protected:
	MESSAGE void __fastcall MMDateChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::TDateTime> &AMessage);
	MESSAGE void __fastcall MMWeekNumbersChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall MMFirstDayOfWeekChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Uitypes::TCalDayOfWeek> &AMessage);
	MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	int __fastcall DefineItemIndexOfFirstDayInCurrentMonth();
	virtual void __fastcall FillYears();
	virtual void __fastcall FillWeeksNumbers();
	virtual void __fastcall FillWeekDays();
	virtual void __fastcall FillDays();
	void __fastcall FillCalendar();
	void __fastcall UpdateWeeksDaysItemHeight();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual void __fastcall DoChange();
	virtual void __fastcall DoDateSelected();
	virtual void __fastcall DoRealign();
	void __fastcall DoPrevClick(System::TObject* Sender);
	void __fastcall DoNextClick(System::TObject* Sender);
	void __fastcall DoTodayClick(System::TObject* Sender);
	void __fastcall DoMonthChange(System::TObject* Sender);
	void __fastcall DoYearChange(System::TObject* Sender);
	void __fastcall DoDayChange(System::TObject* Sender);
	void __fastcall DoDayClick(Fmx::Listbox::TCustomListBox* const Sender, Fmx::Listbox::TListBoxItem* const Item);
	void __fastcall DoDaysMouseDown(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	void __fastcall DoDaysMouseUp(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	virtual void __fastcall MouseWheel(System::Classes::TShiftState Shift, int WheelDelta, bool &Handled);
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	__property int DisableDayChange = {read=FDisableDayChange, nodefault};
	
public:
	Fmx::Listbox::TListBoxItem* __fastcall TryFindDayItem(const System::TDateTime ADateTime);
	__property System::TDate Date = {read=GetDate, write=SetDate};
	__property int FirstDayOfWeek = {read=FFirstDayOfWeekNum, nodefault};
	__property Fmx::Calendar::TCalendarModel* Model = {read=GetModel};
	__property Fmx::Extctrls::TPopupBox* Years = {read=FYears};
	__property Fmx::Extctrls::TPopupBox* Month = {read=FMonths};
	__property Fmx::Layouts::TGridLayout* Weeks = {read=FWeeks};
	__property Fmx::Layouts::TGridLayout* Week = {read=FWeek};
	__property Fmx::Listbox::TListBox* Days = {read=FDays};
	__property Fmx::Stdctrls::TButton* Today = {read=FToday};
	__property Fmx::Stdctrls::TButton* Prev = {read=FPrev};
	__property Fmx::Stdctrls::TButton* Next = {read=FNext};
public:
	/* TStyledPresentation.Create */ inline __fastcall virtual TStyledCalendar(System::Classes::TComponent* AOwner)/* overload */ : Fmx::Presentation::Style::TStyledPresentation(AOwner) { }
	/* TStyledPresentation.Create */ inline __fastcall virtual TStyledCalendar(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Style::TStyledPresentation(AOwner, AModel, AControl) { }
	
public:
	/* TStyledControl.Destroy */ inline __fastcall virtual ~TStyledCalendar() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Style */
}	/* namespace Calendar */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CALENDAR_STYLE)
using namespace Fmx::Calendar::Style;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CALENDAR)
using namespace Fmx::Calendar;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Calendar_StyleHPP
