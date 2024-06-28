// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Calendar.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Calendar_IosHPP
#define Fmx_Calendar_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.DateUtils.hpp>
#include <System.TypInfo.hpp>
#include <System.SysUtils.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <Macapi.Helpers.hpp>
#include <FMX.Presentation.iOS.hpp>
#include <FMX.Calendar.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.Model.hpp>
#include <Macapi.ObjectiveC.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Calendar
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IFMXUIDatePicker;
typedef System::DelphiInterface<IFMXUIDatePicker> _di_IFMXUIDatePicker;
class DELPHICLASS TiOSNativeCalendar;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{E0EA93B8-E2B2-4B02-A832-FAAC42AEA154}") IFMXUIDatePicker  : public Iosapi::Uikit::UIDatePicker 
{
	HIDESBASE virtual void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesCancelled(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesMoved(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	virtual void __cdecl ValueChanged() = 0 ;
};

class PASCALIMPLEMENTATION TiOSNativeCalendar : public Fmx::Presentation::Ios::TiOSNativeControl
{
	typedef Fmx::Presentation::Ios::TiOSNativeControl inherited;
	
private:
	void __fastcall SetDate(const System::TDateTime Value);
	System::TDateTime __fastcall GetDate();
	HIDESBASE Iosapi::Uikit::_di_UIDatePicker __fastcall GetView();
	HIDESBASE Fmx::Calendar::TCalendarModel* __fastcall GetModel();
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	virtual void __fastcall DoChange();
	virtual void __fastcall DoDateSelected();
	MESSAGE void __fastcall MMDateChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::TDateTime> &AMessage);
	MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	
public:
	__fastcall virtual TiOSNativeCalendar()/* overload */;
	void __cdecl ValueChanged();
	__property System::TDateTime Date = {read=GetDate, write=SetDate};
	__property Fmx::Calendar::TCalendarModel* Model = {read=GetModel};
	__property Iosapi::Uikit::_di_UIDatePicker View = {read=GetView};
public:
	/* TiOSNativeView.Create */ inline __fastcall virtual TiOSNativeCalendar(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Ios::TiOSNativeControl(AModel, AControl) { }
	/* TiOSNativeView.Destroy */ inline __fastcall virtual ~TiOSNativeCalendar() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Calendar */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CALENDAR_IOS)
using namespace Fmx::Calendar::Ios;
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
#endif	// Fmx_Calendar_IosHPP
