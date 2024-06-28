// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.CalendarEdit.pas' rev: 34.00 (iOS)

#ifndef Fmx_CalendareditHPP
#define Fmx_CalendareditHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.UITypes.hpp>
#include <System.Classes.hpp>
#include <FMX.Types.hpp>
#include <FMX.ComboEdit.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <FMX.Graphics.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Calendaredit
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCalendarEditModel;
class DELPHICLASS TCustomCalendarEdit;
class DELPHICLASS TCalendarEdit;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCalendarEditModel : public Fmx::Comboedit::TComboEditModel
{
	typedef Fmx::Comboedit::TComboEditModel inherited;
	
private:
	System::Uitypes::TCalDayOfWeek FFirstDayOfWeek;
	bool FShowWeekNumbers;
	bool FTodayDefault;
	System::TDateTime FDateTime;
	System::TDateTime FMinDate;
	System::TDateTime FMaxDate;
	bool FWeekNumbers;
	System::TDate __fastcall GetDate();
	void __fastcall SetDate(const System::TDate Value);
	void __fastcall SetDateTime(const System::TDateTime Value);
	void __fastcall SetFirstDayOfWeek(const System::Uitypes::TCalDayOfWeek Value);
	void __fastcall SetTodayDefault(const bool Value);
	void __fastcall SetWeekNumbers(const bool Value);
	
protected:
	virtual System::UnicodeString __fastcall DoValidating(const System::UnicodeString Value);
	
public:
	__fastcall virtual TCalendarEditModel()/* overload */;
	System::UnicodeString __fastcall GetFormattedDateTimeText();
	__property System::TDate Date = {read=GetDate, write=SetDate};
	__property System::TDateTime DateTime = {read=FDateTime, write=SetDateTime};
	__property System::TDateTime MinDate = {read=FMinDate, write=FMinDate};
	__property System::TDateTime MaxDate = {read=FMaxDate, write=FMaxDate};
	__property System::Uitypes::TCalDayOfWeek FirstDayOfWeek = {read=FFirstDayOfWeek, write=SetFirstDayOfWeek, nodefault};
	__property bool ShowWeekNumbers = {read=FShowWeekNumbers, write=FShowWeekNumbers, nodefault};
	__property bool TodayDefault = {read=FTodayDefault, write=SetTodayDefault, nodefault};
	__property bool WeekNumbers = {read=FWeekNumbers, write=SetWeekNumbers, nodefault};
public:
	/* TComboEditModel.Destroy */ inline __fastcall virtual ~TCalendarEditModel() { }
	
public:
	/* TDataModel.Create */ inline __fastcall virtual TCalendarEditModel(System::Classes::TComponent* const AOwner)/* overload */ : Fmx::Comboedit::TComboEditModel(AOwner) { }
	
};


class PASCALIMPLEMENTATION TCustomCalendarEdit : public Fmx::Comboedit::TComboEditBase
{
	typedef Fmx::Comboedit::TComboEditBase inherited;
	
private:
	void __fastcall SetDate(const System::TDate Value);
	System::TDate __fastcall GetDate();
	void __fastcall SetDateTime(const System::TDateTime Value);
	System::TDateTime __fastcall GetDateTime();
	void __fastcall SetDateConstraints(const int Index, const System::TDateTime Value);
	System::TDateTime __fastcall GetDateConstraints(const int Index);
	void __fastcall SetFirstDayOfWeek(const System::Uitypes::TCalDayOfWeek Value);
	System::Uitypes::TCalDayOfWeek __fastcall GetFirstDayOfWeek();
	void __fastcall SetShowWeekNumbers(const bool Value);
	bool __fastcall GetShowWeekNumbers();
	void __fastcall SetTodayDefault(const bool Value);
	bool __fastcall GetTodayDefault();
	void __fastcall SetOnPopup(const System::Classes::TNotifyEvent Value);
	System::Classes::TNotifyEvent __fastcall GetOnPopup();
	void __fastcall SetOnClosePopup(const System::Classes::TNotifyEvent Value);
	System::Classes::TNotifyEvent __fastcall GetOnClosePopup();
	HIDESBASE TCalendarEditModel* __fastcall GetModel()/* overload */;
	bool __fastcall AreDateConstraintsStored(const int Index);
	
protected:
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	virtual System::UnicodeString __fastcall DefinePresentationName();
	virtual System::UnicodeString __fastcall GetDefaultStyleLookupName();
	
public:
	__fastcall virtual TCustomCalendarEdit(System::Classes::TComponent* AOwner)/* overload */;
	void __fastcall ClosePicker();
	__property TCalendarEditModel* Model = {read=GetModel};
	__property System::TDate Date = {read=GetDate, write=SetDate};
	__property System::TDateTime DateTime = {read=GetDateTime, write=SetDateTime};
	__property System::TDateTime MinDate = {read=GetDateConstraints, write=SetDateConstraints, stored=AreDateConstraintsStored, index=1};
	__property System::TDateTime MaxDate = {read=GetDateConstraints, write=SetDateConstraints, stored=AreDateConstraintsStored, index=2};
	__property bool TodayDefault = {read=GetTodayDefault, write=SetTodayDefault, default=0};
	__property bool WeekNumbers = {read=GetShowWeekNumbers, write=SetShowWeekNumbers, default=0};
	__property System::Uitypes::TCalDayOfWeek FirstDayOfWeek = {read=GetFirstDayOfWeek, write=SetFirstDayOfWeek, default=7};
	__property System::Classes::TNotifyEvent OnClosePopup = {read=GetOnClosePopup, write=SetOnClosePopup};
	__property System::Classes::TNotifyEvent OnPopup = {read=GetOnPopup, write=SetOnPopup};
public:
	/* TCustomEdit.Destroy */ inline __fastcall virtual ~TCustomCalendarEdit() { }
	
};


class PASCALIMPLEMENTATION TCalendarEdit _DEPRECATED_ATTRIBUTE1("Use TDateEdit instead")  : public TCustomCalendarEdit
{
	typedef TCustomCalendarEdit inherited;
	
public:
	__property Font _DEPRECATED_ATTRIBUTE0 ;
	__property TextAlign _DEPRECATED_ATTRIBUTE0  = {default=1};
	
__published:
	__property Anchors _DEPRECATED_ATTRIBUTE0 ;
	__property CanFocus _DEPRECATED_ATTRIBUTE0  = {default=1};
	__property CanParentFocus _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property Cursor _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property ClipChildren _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property ClipParent _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property Date _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property DisableFocusEffect _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property DragMode _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property EnableDragHighlight _DEPRECATED_ATTRIBUTE0  = {default=1};
	__property Enabled _DEPRECATED_ATTRIBUTE0  = {default=1};
	__property FirstDayOfWeek _DEPRECATED_ATTRIBUTE0  = {default=7};
	__property Height _DEPRECATED_ATTRIBUTE0 ;
	__property HelpContext _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property HelpKeyword _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property HelpType _DEPRECATED_ATTRIBUTE0  = {default=1};
	__property Hint _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property HitTest _DEPRECATED_ATTRIBUTE0  = {default=1};
	__property InputSupport _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property Locked _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property KeyboardType _DEPRECATED_ATTRIBUTE0  = {default=1};
	__property Padding _DEPRECATED_ATTRIBUTE0 ;
	__property Opacity _DEPRECATED_ATTRIBUTE0 ;
	__property Margins _DEPRECATED_ATTRIBUTE0 ;
	__property MinDate _DEPRECATED_ATTRIBUTE0  = {index=1, default=0};
	__property MaxDate _DEPRECATED_ATTRIBUTE0  = {index=2, default=0};
	__property PopupMenu _DEPRECATED_ATTRIBUTE0 ;
	__property Position _DEPRECATED_ATTRIBUTE0 ;
	__property RotationAngle _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property RotationCenter _DEPRECATED_ATTRIBUTE0 ;
	__property ReadOnly _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property Scale _DEPRECATED_ATTRIBUTE0 ;
	__property Size _DEPRECATED_ATTRIBUTE0 ;
	__property StyleLookup _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property StyledSettings _DEPRECATED_ATTRIBUTE0 ;
	__property ShowHint _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property Text _DEPRECATED_ATTRIBUTE0  = {stored=false, default=0};
	__property TextSettings _DEPRECATED_ATTRIBUTE0 ;
	__property TodayDefault _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property Visible _DEPRECATED_ATTRIBUTE0  = {default=1};
	__property WeekNumbers _DEPRECATED_ATTRIBUTE0  = {default=0};
	__property Width _DEPRECATED_ATTRIBUTE0 ;
	__property OnClosePopup _DEPRECATED_ATTRIBUTE0 ;
	__property OnPopup _DEPRECATED_ATTRIBUTE0 ;
	__property OnChange _DEPRECATED_ATTRIBUTE0 ;
	__property OnChangeTracking _DEPRECATED_ATTRIBUTE0 ;
	__property OnTyping _DEPRECATED_ATTRIBUTE0 ;
	__property OnApplyStyleLookup _DEPRECATED_ATTRIBUTE0 ;
	__property OnDragEnter _DEPRECATED_ATTRIBUTE0 ;
	__property OnDragLeave _DEPRECATED_ATTRIBUTE0 ;
	__property OnDragOver _DEPRECATED_ATTRIBUTE0 ;
	__property OnDragDrop _DEPRECATED_ATTRIBUTE0 ;
	__property OnDragEnd _DEPRECATED_ATTRIBUTE0 ;
	__property OnKeyDown _DEPRECATED_ATTRIBUTE0 ;
	__property OnKeyUp _DEPRECATED_ATTRIBUTE0 ;
	__property OnCanFocus _DEPRECATED_ATTRIBUTE0 ;
	__property OnEnter _DEPRECATED_ATTRIBUTE0 ;
	__property OnExit _DEPRECATED_ATTRIBUTE0 ;
	__property OnMouseDown _DEPRECATED_ATTRIBUTE0 ;
	__property OnMouseMove _DEPRECATED_ATTRIBUTE0 ;
	__property OnMouseUp _DEPRECATED_ATTRIBUTE0 ;
	__property OnMouseWheel _DEPRECATED_ATTRIBUTE0 ;
	__property OnMouseEnter _DEPRECATED_ATTRIBUTE0 ;
	__property OnMouseLeave _DEPRECATED_ATTRIBUTE0 ;
	__property OnPainting _DEPRECATED_ATTRIBUTE0 ;
	__property OnPaint _DEPRECATED_ATTRIBUTE0 ;
	__property OnResize _DEPRECATED_ATTRIBUTE0 ;
public:
	/* TCustomCalendarEdit.Create */ inline __fastcall virtual TCalendarEdit(System::Classes::TComponent* AOwner)/* overload */ : TCustomCalendarEdit(AOwner) { }
	
public:
	/* TCustomEdit.Destroy */ inline __fastcall virtual ~TCalendarEdit() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word MM_DATE_CHANGED = System::Word(0x1723);
static constexpr System::Word MM_WEEK_NUMBERS_CHANGED = System::Word(0x1724);
static constexpr System::Word MM_FIRST_DAY_OF_WEEK_CHANGED = System::Word(0x1725);
static constexpr System::Word MM_DATETIME_CHANGED = System::Word(0x1726);
static constexpr System::Word PM_CLOSEPICKER = System::Word(0x1009);
}	/* namespace Calendaredit */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CALENDAREDIT)
using namespace Fmx::Calendaredit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_CalendareditHPP
