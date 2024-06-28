// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Edit.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Edit_AndroidHPP
#define Fmx_Edit_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <Androidapi.JNI.Widget.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Presentation.Android.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Controls.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Edit
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidNativeEdit;
class DELPHICLASS TAndroidTextChangedListener;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAndroidNativeEdit : public Fmx::Presentation::Android::TAndroidNativeView
{
	typedef Fmx::Presentation::Android::TAndroidNativeView inherited;
	
private:
	TAndroidTextChangedListener* FTextChangesListener;
	bool FEditHasClearButton;
	bool FIsStyledFontLoaded;
	bool FSavedButtomsContentVisible;
	HIDESBASE Androidapi::Jni::Widget::_di_JEditText __fastcall GetView();
	HIDESBASE Fmx::Edit::TCustomEditModel* __fastcall GetModel();
	Androidapi::Jni::Graphicscontentviewtext::_di_JInputMethodManager __fastcall GetInputMethodManager();
	Fmx::Edit::TCustomEdit* __fastcall GetEdit();
	
protected:
	void __fastcall UpdateText();
	void __fastcall UpdateTextPrompt();
	void __fastcall UpdateTextMaxLength();
	void __fastcall UpdateTextSettings();
	void __fastcall UpdateInputType();
	void __fastcall UpdateReturnKeyType();
	void __fastcall UpdateSelection();
	void __fastcall UpdateInputFilters();
	void __fastcall UpdateVisibleOfClearButton();
	MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	HIDESBASE MESSAGE void __fastcall PMUnload(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMNeedStyleLookup(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMApplyStyleLookup(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMSelLengthChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &AMessage);
	MESSAGE void __fastcall MMSelStartChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &AMessage);
	MESSAGE void __fastcall MMPasswordChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMTextSettingsChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMEditButtonsChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMTextChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::UnicodeString> &AMessage);
	MESSAGE void __fastcall MMMaxLengthChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMPromptTextChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMKeyboardTypeChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMReturnTypeChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMCharCaseChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMReadOnlyChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMFilterCharChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMCaretPositionChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &AMessage);
	MESSAGE void __fastcall MMCheckSpellingChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	virtual bool __fastcall ProcessTouch(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event);
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __fastcall CreateView();
	virtual void __fastcall InitView();
	
public:
	__fastcall virtual TAndroidNativeEdit()/* overload */;
	__fastcall virtual ~TAndroidNativeEdit();
	void __fastcall ShowCaret();
	void __fastcall HideCaret();
	virtual void __fastcall SetFocus();
	virtual void __fastcall ResetFocus();
	__property Fmx::Edit::TCustomEdit* Edit = {read=GetEdit};
	__property Fmx::Edit::TCustomEditModel* Model = {read=GetModel};
	__property Androidapi::Jni::Widget::_di_JEditText View = {read=GetView};
public:
	/* TAndroidNativeView.Create */ inline __fastcall TAndroidNativeEdit(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Android::TAndroidNativeView(AModel, AControl) { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidTextChangedListener : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
private:
	TAndroidNativeEdit* FNativeEdit;
	
public:
	__fastcall TAndroidTextChangedListener(TAndroidNativeEdit* const ANativeEdit);
	void __cdecl afterTextChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JEditable s);
	void __cdecl beforeTextChanged(Androidapi::Jni::Javatypes::_di_JCharSequence s, int start, int count, int after);
	void __cdecl onTextChanged(Androidapi::Jni::Javatypes::_di_JCharSequence s, int start, int before, int count);
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TAndroidTextChangedListener() { }
	
private:
	void *__JTextWatcher;	// Androidapi::Jni::Graphicscontentviewtext::JTextWatcher 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {63D741B9-2232-4298-97E0-098F283B7BB6}
	operator Androidapi::Jni::Graphicscontentviewtext::_di_JTextWatcher()
	{
		Androidapi::Jni::Graphicscontentviewtext::_di_JTextWatcher intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Graphicscontentviewtext::JTextWatcher*(void) { return (Androidapi::Jni::Graphicscontentviewtext::JTextWatcher*)&__JTextWatcher; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Edit */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_EDIT_ANDROID)
using namespace Fmx::Edit::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_EDIT)
using namespace Fmx::Edit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Edit_AndroidHPP
