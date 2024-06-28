// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Calendar.pas' rev: 34.00 (Android)

#ifndef Fmx_CalendarHPP
#define Fmx_CalendarHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Rtti.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Calendar
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCalendarModel;
class DELPHICLASS TCustomCalendar;
class DELPHICLASS TCalendar;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCalendarModel : public Fmx::Controls::Model::TDataModel
{
	typedef Fmx::Controls::Model::TDataModel inherited;
	
public:
	static const System::Uitypes::TCalDayOfWeek DefaultCalDayOfWeek = (System::Uitypes::TCalDayOfWeek)(7);
	
	static constexpr bool DefaultTodayDefault = false;
	
	static constexpr bool DefaultWeekNumbers = false;
	
	
private:
	System::TDate FDate;
	System::Uitypes::TCalDayOfWeek FFirstDayOfWeek;
	bool FTodayDefault;
	bool FWeekNumbers;
	System::Classes::TNotifyEvent FOnChange;
	System::Classes::TNotifyEvent FOnDateSelected;
	System::Classes::TNotifyEvent FOnDayClick;
	void __fastcall SetDate(const System::TDate Value);
	void __fastcall SetFirstDayOfWeek(const System::Uitypes::TCalDayOfWeek Value);
	void __fastcall SetTodayDefault(const bool Value);
	void __fastcall SetWeekNumbers(const bool Value);
	
public:
	__fastcall virtual TCalendarModel()/* overload */;
	__property System::TDate DateTime = {read=FDate, write=SetDate};
	__property System::Uitypes::TCalDayOfWeek FirstDayOfWeek = {read=FFirstDayOfWeek, write=SetFirstDayOfWeek, nodefault};
	__property bool TodayDefault = {read=FTodayDefault, write=SetTodayDefault, nodefault};
	__property bool WeekNumbers = {read=FWeekNumbers, write=SetWeekNumbers, nodefault};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property System::Classes::TNotifyEvent OnDateSelected = {read=FOnDateSelected, write=FOnDateSelected};
	__property System::Classes::TNotifyEvent OnDayClick = {read=FOnDayClick, write=FOnDayClick};
public:
	/* TDataModel.Create */ inline __fastcall virtual TCalendarModel(System::Classes::TComponent* const AOwner)/* overload */ : Fmx::Controls::Model::TDataModel(AOwner) { }
	/* TDataModel.Destroy */ inline __fastcall virtual ~TCalendarModel() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomCalendar : public Fmx::Controls::Presentation::TPresentedControl
{
	typedef Fmx::Controls::Presentation::TPresentedControl inherited;
	
private:
	System::TDate __fastcall GetDate();
	void __fastcall SetDate(System::TDate Value);
	System::TDateTime __fastcall GetDateTime();
	void __fastcall SetDateTime(const System::TDateTime Value);
	System::Uitypes::TCalDayOfWeek __fastcall GetFirstDayOfWeek();
	void __fastcall SetFirstDayOfWeek(const System::Uitypes::TCalDayOfWeek Value);
	bool __fastcall GetTodayDefault();
	void __fastcall SetTodayDefault(const bool Value);
	bool __fastcall GetWeekNumbers();
	void __fastcall SetWeekNumbers(const bool Value);
	System::Classes::TNotifyEvent __fastcall GetOnChange();
	void __fastcall SetOnChange(const System::Classes::TNotifyEvent Value);
	System::Classes::TNotifyEvent __fastcall GetOnDateSelected();
	void __fastcall SetOnDateSelected(const System::Classes::TNotifyEvent Value);
	System::Classes::TNotifyEvent __fastcall GetOnDayClick();
	void __fastcall SetOnDayClick(const System::Classes::TNotifyEvent Value);
	HIDESBASE TCalendarModel* __fastcall GetModel()/* overload */;
	
protected:
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	virtual System::Types::TSizeF __fastcall GetDefaultSize();
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	
public:
	__fastcall virtual TCustomCalendar(System::Classes::TComponent* AOwner)/* overload */;
	__property TCalendarModel* Model = {read=GetModel};
	__property System::TDateTime DateTime = {read=GetDateTime, write=SetDateTime};
	__property System::TDate Date = {read=GetDate, write=SetDate};
	__property System::Uitypes::TCalDayOfWeek FirstDayOfWeek = {read=GetFirstDayOfWeek, write=SetFirstDayOfWeek, nodefault};
	__property bool TodayDefault = {read=GetTodayDefault, write=SetTodayDefault, nodefault};
	__property bool WeekNumbers = {read=GetWeekNumbers, write=SetWeekNumbers, nodefault};
	__property System::Classes::TNotifyEvent OnChange = {read=GetOnChange, write=SetOnChange};
	__property System::Classes::TNotifyEvent OnDateSelected = {read=GetOnDateSelected, write=SetOnDateSelected};
	__property System::Classes::TNotifyEvent OnDayClick = {read=GetOnDayClick, write=SetOnDayClick};
public:
	/* TPresentedControl.Destroy */ inline __fastcall virtual ~TCustomCalendar() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCalendar : public TCustomCalendar
{
	typedef TCustomCalendar inherited;
	
__published:
	__property Align = {default=0};
	__property Anchors;
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property ControlType = {default=0};
	__property Cursor = {default=0};
	__property Date = {default=0};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled = {default=1};
	__property FirstDayOfWeek = {default=7};
	__property Locked = {default=0};
	__property Height;
	__property HelpContext = {default=0};
	__property HelpKeyword = {default=0};
	__property HelpType = {default=1};
	__property Hint = {default=0};
	__property HitTest = {default=1};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property Scale;
	__property Size;
	__property StyleLookup = {default=0};
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property TodayDefault = {default=0};
	__property Visible = {default=1};
	__property TouchTargetExpansion;
	__property WeekNumbers = {default=0};
	__property Width;
	__property ParentShowHint = {default=1};
	__property ShowHint;
	__property OnApplyStyleLookup;
	__property OnChange;
	__property OnDateSelected;
	__property OnDayClick;
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnCanFocus;
	__property OnEnter;
	__property OnExit;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnResized;
	__property OnPresentationNameChoosing;
public:
	/* TCustomCalendar.Create */ inline __fastcall virtual TCalendar(System::Classes::TComponent* AOwner)/* overload */ : TCustomCalendar(AOwner) { }
	
public:
	/* TPresentedControl.Destroy */ inline __fastcall virtual ~TCalendar() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word MM_DATE_CHANGED = System::Word(0x1701);
static constexpr System::Word MM_WEEKNUMBERS_CHANGED = System::Word(0x1702);
static constexpr System::Word MM_FIRSTDAYOFWEEK_CHANGED = System::Word(0x1703);
static constexpr System::Word MM_CALENDAR_USER = System::Word(0x1704);
}	/* namespace Calendar */
}	/* namespace Fmx */
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
#endif	// Fmx_CalendarHPP
