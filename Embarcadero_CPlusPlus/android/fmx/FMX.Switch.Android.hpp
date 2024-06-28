// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Switch.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Switch_AndroidHPP
#define Fmx_Switch_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.Widget.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Presentation.Android.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.StdCtrls.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Switch
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidNativeSwitch;
class DELPHICLASS TAndroidNativeSwitchListener;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAndroidNativeSwitch : public Fmx::Presentation::Android::TAndroidNativeView
{
	typedef Fmx::Presentation::Android::TAndroidNativeView inherited;
	
private:
	TAndroidNativeSwitchListener* FListener;
	HIDESBASE Androidapi::Jni::Widget::_di_JSwitch __fastcall GetView();
	HIDESBASE Fmx::Stdctrls::TSwitchModel* __fastcall GetModel();
	void __fastcall UpdateChecked();
	
protected:
	MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMValueChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __fastcall CreateView();
	virtual bool __fastcall ProcessTouch(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event);
	
public:
	__fastcall virtual TAndroidNativeSwitch()/* overload */;
	__fastcall virtual ~TAndroidNativeSwitch();
	__property Fmx::Stdctrls::TSwitchModel* Model = {read=GetModel};
	__property Androidapi::Jni::Widget::_di_JSwitch View = {read=GetView};
public:
	/* TAndroidNativeView.Create */ inline __fastcall TAndroidNativeSwitch(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Android::TAndroidNativeView(AModel, AControl) { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidNativeSwitchListener : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
private:
	TAndroidNativeSwitch* FSwitch;
	
public:
	__fastcall TAndroidNativeSwitchListener(TAndroidNativeSwitch* const ASwitch);
	void __cdecl onCheckedChanged(Androidapi::Jni::Widget::_di_JCompoundButton buttonView, bool isChecked);
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TAndroidNativeSwitchListener() { }
	
private:
	void *__JCompoundButton_OnCheckedChangeListener;	// Androidapi::Jni::Widget::JCompoundButton_OnCheckedChangeListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1B3374AF-2381-42F4-AE22-2CEB920B0C76}
	operator Androidapi::Jni::Widget::_di_JCompoundButton_OnCheckedChangeListener()
	{
		Androidapi::Jni::Widget::_di_JCompoundButton_OnCheckedChangeListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Widget::JCompoundButton_OnCheckedChangeListener*(void) { return (Androidapi::Jni::Widget::JCompoundButton_OnCheckedChangeListener*)&__JCompoundButton_OnCheckedChangeListener; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Switch */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_SWITCH_ANDROID)
using namespace Fmx::Switch::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_SWITCH)
using namespace Fmx::Switch;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Switch_AndroidHPP
