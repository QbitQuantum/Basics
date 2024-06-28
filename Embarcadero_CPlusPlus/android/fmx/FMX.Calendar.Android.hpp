// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Calendar.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Calendar_AndroidHPP
#define Fmx_Calendar_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <Androidapi.JNI.Widget.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Calendar.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Presentation.Android.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Calendar
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidNativeCalendar;
class DELPHICLASS TAndroidNativeCalendarListener;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAndroidNativeCalendar : public Fmx::Presentation::Android::TAndroidNativeView
{
	typedef Fmx::Presentation::Android::TAndroidNativeView inherited;
	
private:
	TAndroidNativeCalendarListener* FListener;
	HIDESBASE Androidapi::Jni::Widget::_di_JCalendarView __fastcall GetView();
	HIDESBASE Fmx::Calendar::TCalendarModel* __fastcall GetModel();
	void __fastcall UpdateDate();
	void __fastcall UpdateWeekNumbers();
	void __fastcall UpdateFirstDayOfWeek();
	
protected:
	MESSAGE void __fastcall MMDateChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::TDateTime> &AMessage);
	MESSAGE void __fastcall MMWeekNumbersChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall MMFirstDayOfWeekChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Uitypes::TCalDayOfWeek> &AMessage);
	MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __fastcall CreateView();
	
public:
	__fastcall virtual TAndroidNativeCalendar()/* overload */;
	__fastcall virtual ~TAndroidNativeCalendar();
	__classmethod System::Uitypes::TCalDayOfWeek __fastcall GetCurrentLocaleFirstDayOfWeek();
	__property Fmx::Calendar::TCalendarModel* Model = {read=GetModel};
	__property Androidapi::Jni::Widget::_di_JCalendarView View = {read=GetView};
public:
	/* TAndroidNativeView.Create */ inline __fastcall TAndroidNativeCalendar(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Android::TAndroidNativeView(AModel, AControl) { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidNativeCalendarListener : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
private:
	TAndroidNativeCalendar* FCalendar;
	
public:
	__fastcall TAndroidNativeCalendarListener(TAndroidNativeCalendar* const ACalendar);
	void __cdecl onSelectedDayChange(Androidapi::Jni::Widget::_di_JCalendarView view, int year, int month, int dayOfMonth);
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TAndroidNativeCalendarListener() { }
	
private:
	void *__JCalendarView_OnDateChangeListener;	// Androidapi::Jni::Widget::JCalendarView_OnDateChangeListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8BFCE3F3-F4AF-4758-A036-7C63196D41A4}
	operator Androidapi::Jni::Widget::_di_JCalendarView_OnDateChangeListener()
	{
		Androidapi::Jni::Widget::_di_JCalendarView_OnDateChangeListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Widget::JCalendarView_OnDateChangeListener*(void) { return (Androidapi::Jni::Widget::JCalendarView_OnDateChangeListener*)&__JCalendarView_OnDateChangeListener; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Calendar */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CALENDAR_ANDROID)
using namespace Fmx::Calendar::Android;
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
#endif	// Fmx_Calendar_AndroidHPP
