// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.InputMethodService.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_InputmethodserviceHPP
#define Androidapi_Jni_InputmethodserviceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.App.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.JNI.Util.hpp>
#include <Androidapi.JNI.Widget.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Inputmethodservice
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JAbstractInputMethodServiceClass;
typedef System::DelphiInterface<JAbstractInputMethodServiceClass> _di_JAbstractInputMethodServiceClass;
__interface DELPHIINTERFACE JAbstractInputMethodService;
typedef System::DelphiInterface<JAbstractInputMethodService> _di_JAbstractInputMethodService;
class DELPHICLASS TJAbstractInputMethodService;
__interface DELPHIINTERFACE JAbstractInputMethodService_AbstractInputMethodImplClass;
typedef System::DelphiInterface<JAbstractInputMethodService_AbstractInputMethodImplClass> _di_JAbstractInputMethodService_AbstractInputMethodImplClass;
__interface DELPHIINTERFACE JAbstractInputMethodService_AbstractInputMethodImpl;
typedef System::DelphiInterface<JAbstractInputMethodService_AbstractInputMethodImpl> _di_JAbstractInputMethodService_AbstractInputMethodImpl;
class DELPHICLASS TJAbstractInputMethodService_AbstractInputMethodImpl;
__interface DELPHIINTERFACE JAbstractInputMethodService_AbstractInputMethodSessionImplClass;
typedef System::DelphiInterface<JAbstractInputMethodService_AbstractInputMethodSessionImplClass> _di_JAbstractInputMethodService_AbstractInputMethodSessionImplClass;
__interface DELPHIINTERFACE JAbstractInputMethodService_AbstractInputMethodSessionImpl;
typedef System::DelphiInterface<JAbstractInputMethodService_AbstractInputMethodSessionImpl> _di_JAbstractInputMethodService_AbstractInputMethodSessionImpl;
class DELPHICLASS TJAbstractInputMethodService_AbstractInputMethodSessionImpl;
__interface DELPHIINTERFACE JExtractEditTextClass;
typedef System::DelphiInterface<JExtractEditTextClass> _di_JExtractEditTextClass;
__interface DELPHIINTERFACE JExtractEditText;
typedef System::DelphiInterface<JExtractEditText> _di_JExtractEditText;
class DELPHICLASS TJExtractEditText;
__interface DELPHIINTERFACE JInputMethodServiceClass;
typedef System::DelphiInterface<JInputMethodServiceClass> _di_JInputMethodServiceClass;
__interface DELPHIINTERFACE JInputMethodService;
typedef System::DelphiInterface<JInputMethodService> _di_JInputMethodService;
class DELPHICLASS TJInputMethodService;
__interface DELPHIINTERFACE JInputMethodService_InputMethodImplClass;
typedef System::DelphiInterface<JInputMethodService_InputMethodImplClass> _di_JInputMethodService_InputMethodImplClass;
__interface DELPHIINTERFACE JInputMethodService_InputMethodImpl;
typedef System::DelphiInterface<JInputMethodService_InputMethodImpl> _di_JInputMethodService_InputMethodImpl;
class DELPHICLASS TJInputMethodService_InputMethodImpl;
__interface DELPHIINTERFACE JInputMethodService_InputMethodSessionImplClass;
typedef System::DelphiInterface<JInputMethodService_InputMethodSessionImplClass> _di_JInputMethodService_InputMethodSessionImplClass;
__interface DELPHIINTERFACE JInputMethodService_InputMethodSessionImpl;
typedef System::DelphiInterface<JInputMethodService_InputMethodSessionImpl> _di_JInputMethodService_InputMethodSessionImpl;
class DELPHICLASS TJInputMethodService_InputMethodSessionImpl;
__interface DELPHIINTERFACE JInputMethodService_InsetsClass;
typedef System::DelphiInterface<JInputMethodService_InsetsClass> _di_JInputMethodService_InsetsClass;
__interface DELPHIINTERFACE JInputMethodService_Insets;
typedef System::DelphiInterface<JInputMethodService_Insets> _di_JInputMethodService_Insets;
class DELPHICLASS TJInputMethodService_Insets;
__interface DELPHIINTERFACE JKeyboardClass;
typedef System::DelphiInterface<JKeyboardClass> _di_JKeyboardClass;
__interface DELPHIINTERFACE JKeyboard;
typedef System::DelphiInterface<JKeyboard> _di_JKeyboard;
class DELPHICLASS TJKeyboard;
__interface DELPHIINTERFACE JKeyboard_KeyClass;
typedef System::DelphiInterface<JKeyboard_KeyClass> _di_JKeyboard_KeyClass;
__interface DELPHIINTERFACE JKeyboard_Key;
typedef System::DelphiInterface<JKeyboard_Key> _di_JKeyboard_Key;
class DELPHICLASS TJKeyboard_Key;
__interface DELPHIINTERFACE JKeyboard_RowClass;
typedef System::DelphiInterface<JKeyboard_RowClass> _di_JKeyboard_RowClass;
__interface DELPHIINTERFACE JKeyboard_Row;
typedef System::DelphiInterface<JKeyboard_Row> _di_JKeyboard_Row;
class DELPHICLASS TJKeyboard_Row;
__interface DELPHIINTERFACE JKeyboardViewClass;
typedef System::DelphiInterface<JKeyboardViewClass> _di_JKeyboardViewClass;
__interface DELPHIINTERFACE JKeyboardView;
typedef System::DelphiInterface<JKeyboardView> _di_JKeyboardView;
class DELPHICLASS TJKeyboardView;
__interface DELPHIINTERFACE JKeyboardView_OnKeyboardActionListenerClass;
typedef System::DelphiInterface<JKeyboardView_OnKeyboardActionListenerClass> _di_JKeyboardView_OnKeyboardActionListenerClass;
__interface DELPHIINTERFACE JKeyboardView_OnKeyboardActionListener;
typedef System::DelphiInterface<JKeyboardView_OnKeyboardActionListener> _di_JKeyboardView_OnKeyboardActionListener;
class DELPHICLASS TJKeyboardView_OnKeyboardActionListener;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{65936083-8001-4263-B08D-AF9EB3818754}") JAbstractInputMethodServiceClass  : public Androidapi::Jni::App::JServiceClass 
{
	HIDESBASE virtual _di_JAbstractInputMethodService __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{76A44416-D321-44FE-8DC9-CA4905BA14AF}") JAbstractInputMethodService  : public Androidapi::Jni::App::JService 
{
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent_DispatcherState __cdecl getKeyDispatcherState() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Os::_di_JIBinder __cdecl onBind(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual _di_JAbstractInputMethodService_AbstractInputMethodImpl __cdecl onCreateInputMethodInterface() = 0 ;
	virtual _di_JAbstractInputMethodService_AbstractInputMethodSessionImpl __cdecl onCreateInputMethodSessionInterface() = 0 ;
	virtual bool __cdecl onGenericMotionEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	virtual bool __cdecl onTrackballEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAbstractInputMethodService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbstractInputMethodServiceClass,_di_JAbstractInputMethodService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbstractInputMethodServiceClass,_di_JAbstractInputMethodService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAbstractInputMethodService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbstractInputMethodServiceClass,_di_JAbstractInputMethodService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAbstractInputMethodService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{59CB1E26-657A-4437-B964-FE56B62FFC5B}") JAbstractInputMethodService_AbstractInputMethodImplClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JAbstractInputMethodService_AbstractInputMethodImpl __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{4BA1739F-1C71-4182-B6C8-B4884FBA7F42}") JAbstractInputMethodService_AbstractInputMethodImpl  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl createSession(Androidapi::Jni::Graphicscontentviewtext::_di_JInputMethod_SessionCallback callback) = 0 ;
	virtual void __cdecl revokeSession(Androidapi::Jni::Graphicscontentviewtext::_di_JInputMethodSession session) = 0 ;
	virtual void __cdecl setSessionEnabled(Androidapi::Jni::Graphicscontentviewtext::_di_JInputMethodSession session, bool enabled) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAbstractInputMethodService_AbstractInputMethodImpl : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbstractInputMethodService_AbstractInputMethodImplClass,_di_JAbstractInputMethodService_AbstractInputMethodImpl>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbstractInputMethodService_AbstractInputMethodImplClass,_di_JAbstractInputMethodService_AbstractInputMethodImpl> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAbstractInputMethodService_AbstractInputMethodImpl() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbstractInputMethodService_AbstractInputMethodImplClass,_di_JAbstractInputMethodService_AbstractInputMethodImpl>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAbstractInputMethodService_AbstractInputMethodImpl() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7E04E9F4-F218-4249-81A1-2A85C94750F9}") JAbstractInputMethodService_AbstractInputMethodSessionImplClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JAbstractInputMethodService_AbstractInputMethodSessionImpl __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{32455BA6-922B-4AD4-BFBC-6E1305890C3B}") JAbstractInputMethodService_AbstractInputMethodSessionImpl  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl dispatchGenericMotionEvent(int seq, Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event, Androidapi::Jni::Graphicscontentviewtext::_di_JInputMethodSession_EventCallback callback) = 0 ;
	virtual void __cdecl dispatchKeyEvent(int seq, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event, Androidapi::Jni::Graphicscontentviewtext::_di_JInputMethodSession_EventCallback callback) = 0 ;
	virtual void __cdecl dispatchTrackballEvent(int seq, Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event, Androidapi::Jni::Graphicscontentviewtext::_di_JInputMethodSession_EventCallback callback) = 0 ;
	virtual bool __cdecl isEnabled() = 0 ;
	virtual bool __cdecl isRevoked() = 0 ;
	virtual void __cdecl revokeSelf() = 0 ;
	virtual void __cdecl setEnabled(bool enabled) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAbstractInputMethodService_AbstractInputMethodSessionImpl : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbstractInputMethodService_AbstractInputMethodSessionImplClass,_di_JAbstractInputMethodService_AbstractInputMethodSessionImpl>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbstractInputMethodService_AbstractInputMethodSessionImplClass,_di_JAbstractInputMethodService_AbstractInputMethodSessionImpl> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAbstractInputMethodService_AbstractInputMethodSessionImpl() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbstractInputMethodService_AbstractInputMethodSessionImplClass,_di_JAbstractInputMethodService_AbstractInputMethodSessionImpl>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAbstractInputMethodService_AbstractInputMethodSessionImpl() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B369E49F-E699-4912-A4E6-BCBF578FFE74}") JExtractEditTextClass  : public Androidapi::Jni::Widget::JEditTextClass 
{
	HIDESBASE virtual _di_JExtractEditText __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JExtractEditText __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JExtractEditText __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JExtractEditText __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{09E89DEE-6973-47FE-8FC5-A68EB74B34F1}") JExtractEditText  : public Androidapi::Jni::Widget::JEditText 
{
	virtual void __cdecl finishInternalChanges() = 0 ;
	HIDESBASE virtual bool __cdecl hasFocus() = 0 ;
	virtual bool __cdecl hasVerticalScrollBar() = 0 ;
	HIDESBASE virtual bool __cdecl hasWindowFocus() = 0 ;
	HIDESBASE virtual bool __cdecl isFocused() = 0 ;
	HIDESBASE virtual bool __cdecl isInputMethodTarget() = 0 ;
	HIDESBASE virtual bool __cdecl onTextContextMenuItem(int id) = 0 ;
	HIDESBASE virtual bool __cdecl performClick() = 0 ;
	HIDESBASE virtual void __cdecl setExtractedText(Androidapi::Jni::Graphicscontentviewtext::_di_JExtractedText text) = 0 ;
	virtual void __cdecl startInternalChanges() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJExtractEditText : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JExtractEditTextClass,_di_JExtractEditText>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JExtractEditTextClass,_di_JExtractEditText> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJExtractEditText() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JExtractEditTextClass,_di_JExtractEditText>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJExtractEditText() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7DE4CFF2-4B59-44A3-A3CA-1870175FF807}") JInputMethodServiceClass  : public JAbstractInputMethodServiceClass 
{
	virtual int __cdecl _GetBACK_DISPOSITION_DEFAULT() = 0 ;
	virtual int __cdecl _GetBACK_DISPOSITION_WILL_DISMISS() = 0 ;
	virtual int __cdecl _GetBACK_DISPOSITION_WILL_NOT_DISMISS() = 0 ;
	HIDESBASE virtual _di_JInputMethodService __cdecl init() = 0 ;
	__property int BACK_DISPOSITION_DEFAULT = {read=_GetBACK_DISPOSITION_DEFAULT};
	__property int BACK_DISPOSITION_WILL_DISMISS = {read=_GetBACK_DISPOSITION_WILL_DISMISS};
	__property int BACK_DISPOSITION_WILL_NOT_DISMISS = {read=_GetBACK_DISPOSITION_WILL_NOT_DISMISS};
};

__interface  INTERFACE_UUID("{A0954F9A-CF37-4E9B-943F-AAA9A6828992}") JInputMethodService  : public JAbstractInputMethodService 
{
	virtual bool __cdecl enableHardwareAcceleration() = 0 ;
	virtual int __cdecl getBackDisposition() = 0 ;
	virtual int __cdecl getCandidatesHiddenVisibility() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JInputBinding __cdecl getCurrentInputBinding() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JInputConnection __cdecl getCurrentInputConnection() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JEditorInfo __cdecl getCurrentInputEditorInfo() = 0 ;
	virtual bool __cdecl getCurrentInputStarted() = 0 ;
	virtual int __cdecl getInputMethodWindowRecommendedHeight() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JLayoutInflater __cdecl getLayoutInflater() = 0 ;
	virtual int __cdecl getMaxWidth() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getTextForImeAction(int imeOptions) = 0 ;
	virtual Androidapi::Jni::App::_di_JDialog __cdecl getWindow() = 0 ;
	virtual void __cdecl hideStatusIcon() = 0 ;
	virtual void __cdecl hideWindow() = 0 ;
	virtual bool __cdecl isExtractViewShown() = 0 ;
	virtual bool __cdecl isFullscreenMode() = 0 ;
	virtual bool __cdecl isInputViewShown() = 0 ;
	virtual bool __cdecl isShowInputRequested() = 0 ;
	virtual void __cdecl onAppPrivateCommand(Androidapi::Jni::Javatypes::_di_JString action, Androidapi::Jni::Os::_di_JBundle data) = 0 ;
	virtual void __cdecl onBindInput() = 0 ;
	virtual void __cdecl onComputeInsets(_di_JInputMethodService_Insets outInsets) = 0 ;
	HIDESBASE virtual void __cdecl onConfigurationChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JConfiguration newConfig) = 0 ;
	virtual void __cdecl onConfigureWindow(Androidapi::Jni::Graphicscontentviewtext::_di_JWindow win, bool isFullscreen, bool isCandidatesOnly) = 0 ;
	HIDESBASE virtual void __cdecl onCreate() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl onCreateCandidatesView() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl onCreateExtractTextView() = 0 ;
	HIDESBASE virtual _di_JAbstractInputMethodService_AbstractInputMethodImpl __cdecl onCreateInputMethodInterface() = 0 ;
	HIDESBASE virtual _di_JAbstractInputMethodService_AbstractInputMethodSessionImpl __cdecl onCreateInputMethodSessionInterface() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl onCreateInputView() = 0 ;
	HIDESBASE virtual void __cdecl onDestroy() = 0 ;
	virtual void __cdecl onDisplayCompletions(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JCompletionInfo>* completions) = 0 ;
	virtual bool __cdecl onEvaluateFullscreenMode() = 0 ;
	virtual bool __cdecl onEvaluateInputViewShown() = 0 ;
	virtual bool __cdecl onExtractTextContextMenuItem(int id) = 0 ;
	virtual void __cdecl onExtractedCursorMovement(int dx, int dy) = 0 ;
	virtual void __cdecl onExtractedSelectionChanged(int start, int end_) = 0 ;
	virtual void __cdecl onExtractedTextClicked() = 0 ;
	virtual void __cdecl onExtractingInputChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JEditorInfo ei) = 0 ;
	virtual void __cdecl onFinishCandidatesView(bool finishingInput) = 0 ;
	virtual void __cdecl onFinishInput() = 0 ;
	virtual void __cdecl onFinishInputView(bool finishingInput) = 0 ;
	HIDESBASE virtual bool __cdecl onGenericMotionEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	virtual void __cdecl onInitializeInterface() = 0 ;
	virtual bool __cdecl onKeyDown(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl onKeyLongPress(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl onKeyMultiple(int keyCode, int count, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl onKeyUp(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl onShowInputRequested(int flags, bool configChange) = 0 ;
	virtual void __cdecl onStartCandidatesView(Androidapi::Jni::Graphicscontentviewtext::_di_JEditorInfo info, bool restarting) = 0 ;
	virtual void __cdecl onStartInput(Androidapi::Jni::Graphicscontentviewtext::_di_JEditorInfo attribute, bool restarting) = 0 ;
	virtual void __cdecl onStartInputView(Androidapi::Jni::Graphicscontentviewtext::_di_JEditorInfo info, bool restarting) = 0 ;
	HIDESBASE virtual bool __cdecl onTrackballEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	virtual void __cdecl onUnbindInput() = 0 ;
	virtual void __cdecl onUpdateCursor(Androidapi::Jni::Graphicscontentviewtext::_di_JRect newCursor) = 0 ;
	virtual void __cdecl onUpdateCursorAnchorInfo(Androidapi::Jni::Graphicscontentviewtext::_di_JCursorAnchorInfo cursorAnchorInfo) = 0 ;
	virtual void __cdecl onUpdateExtractedText(int token, Androidapi::Jni::Graphicscontentviewtext::_di_JExtractedText text) = 0 ;
	virtual void __cdecl onUpdateExtractingViews(Androidapi::Jni::Graphicscontentviewtext::_di_JEditorInfo ei) = 0 ;
	virtual void __cdecl onUpdateExtractingVisibility(Androidapi::Jni::Graphicscontentviewtext::_di_JEditorInfo ei) = 0 ;
	virtual void __cdecl onUpdateSelection(int oldSelStart, int oldSelEnd, int newSelStart, int newSelEnd, int candidatesStart, int candidatesEnd) = 0 ;
	virtual void __cdecl onViewClicked(bool focusChanged) = 0 ;
	virtual void __cdecl onWindowHidden() = 0 ;
	virtual void __cdecl onWindowShown() = 0 ;
	virtual void __cdecl requestHideSelf(int flags) = 0 ;
	virtual bool __cdecl sendDefaultEditorAction(bool fromEnterKey) = 0 ;
	virtual void __cdecl sendDownUpKeyEvents(int keyEventCode) = 0 ;
	virtual void __cdecl sendKeyChar(System::WideChar charCode) = 0 ;
	virtual void __cdecl setBackDisposition(int disposition) = 0 ;
	virtual void __cdecl setCandidatesView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
	virtual void __cdecl setCandidatesViewShown(bool shown) = 0 ;
	virtual void __cdecl setExtractView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
	virtual void __cdecl setExtractViewShown(bool shown) = 0 ;
	virtual void __cdecl setInputView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
	HIDESBASE virtual void __cdecl setTheme(int theme) = 0 ;
	virtual void __cdecl showStatusIcon(int iconResId) = 0 ;
	virtual void __cdecl showWindow(bool showInput) = 0 ;
	virtual void __cdecl switchInputMethod(Androidapi::Jni::Javatypes::_di_JString id) = 0 ;
	virtual void __cdecl updateFullscreenMode() = 0 ;
	virtual void __cdecl updateInputViewShown() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInputMethodService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInputMethodServiceClass,_di_JInputMethodService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInputMethodServiceClass,_di_JInputMethodService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInputMethodService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInputMethodServiceClass,_di_JInputMethodService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInputMethodService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BEDEA638-BFD1-4AB1-8875-09804265A5FE}") JInputMethodService_InputMethodImplClass  : public JAbstractInputMethodService_AbstractInputMethodImplClass 
{
	HIDESBASE virtual _di_JInputMethodService_InputMethodImpl __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{84058E99-B0CE-4CE8-8B41-2723E697C4A9}") JInputMethodService_InputMethodImpl  : public JAbstractInputMethodService_AbstractInputMethodImpl 
{
	virtual void __cdecl attachToken(Androidapi::Jni::Os::_di_JIBinder token) = 0 ;
	virtual void __cdecl bindInput(Androidapi::Jni::Graphicscontentviewtext::_di_JInputBinding binding) = 0 ;
	virtual void __cdecl changeInputMethodSubtype(Androidapi::Jni::Graphicscontentviewtext::_di_JInputMethodSubtype subtype) = 0 ;
	virtual void __cdecl hideSoftInput(int flags, Androidapi::Jni::Os::_di_JResultReceiver resultReceiver) = 0 ;
	virtual void __cdecl restartInput(Androidapi::Jni::Graphicscontentviewtext::_di_JInputConnection ic, Androidapi::Jni::Graphicscontentviewtext::_di_JEditorInfo attribute) = 0 ;
	virtual void __cdecl showSoftInput(int flags, Androidapi::Jni::Os::_di_JResultReceiver resultReceiver) = 0 ;
	virtual void __cdecl startInput(Androidapi::Jni::Graphicscontentviewtext::_di_JInputConnection ic, Androidapi::Jni::Graphicscontentviewtext::_di_JEditorInfo attribute) = 0 ;
	virtual void __cdecl unbindInput() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInputMethodService_InputMethodImpl : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInputMethodService_InputMethodImplClass,_di_JInputMethodService_InputMethodImpl>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInputMethodService_InputMethodImplClass,_di_JInputMethodService_InputMethodImpl> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInputMethodService_InputMethodImpl() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInputMethodService_InputMethodImplClass,_di_JInputMethodService_InputMethodImpl>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInputMethodService_InputMethodImpl() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{54A7E06B-0E98-4B57-ADFF-353732851EBF}") JInputMethodService_InputMethodSessionImplClass  : public JAbstractInputMethodService_AbstractInputMethodSessionImplClass 
{
	HIDESBASE virtual _di_JInputMethodService_InputMethodSessionImpl __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{50561A9E-9EDD-44EC-9690-3CD9EA7E11EA}") JInputMethodService_InputMethodSessionImpl  : public JAbstractInputMethodService_AbstractInputMethodSessionImpl 
{
	virtual void __cdecl appPrivateCommand(Androidapi::Jni::Javatypes::_di_JString action, Androidapi::Jni::Os::_di_JBundle data) = 0 ;
	virtual void __cdecl displayCompletions(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JCompletionInfo>* completions) = 0 ;
	virtual void __cdecl finishInput() = 0 ;
	virtual void __cdecl toggleSoftInput(int showFlags, int hideFlags) = 0 ;
	virtual void __cdecl updateCursor(Androidapi::Jni::Graphicscontentviewtext::_di_JRect newCursor) = 0 ;
	virtual void __cdecl updateCursorAnchorInfo(Androidapi::Jni::Graphicscontentviewtext::_di_JCursorAnchorInfo info) = 0 ;
	virtual void __cdecl updateExtractedText(int token, Androidapi::Jni::Graphicscontentviewtext::_di_JExtractedText text) = 0 ;
	virtual void __cdecl updateSelection(int oldSelStart, int oldSelEnd, int newSelStart, int newSelEnd, int candidatesStart, int candidatesEnd) = 0 ;
	virtual void __cdecl viewClicked(bool focusChanged) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInputMethodService_InputMethodSessionImpl : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInputMethodService_InputMethodSessionImplClass,_di_JInputMethodService_InputMethodSessionImpl>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInputMethodService_InputMethodSessionImplClass,_di_JInputMethodService_InputMethodSessionImpl> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInputMethodService_InputMethodSessionImpl() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInputMethodService_InputMethodSessionImplClass,_di_JInputMethodService_InputMethodSessionImpl>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInputMethodService_InputMethodSessionImpl() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F0ED3F1A-3152-4BCF-926B-57CBC40FCD5D}") JInputMethodService_InsetsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetTOUCHABLE_INSETS_CONTENT() = 0 ;
	virtual int __cdecl _GetTOUCHABLE_INSETS_FRAME() = 0 ;
	virtual int __cdecl _GetTOUCHABLE_INSETS_REGION() = 0 ;
	virtual int __cdecl _GetTOUCHABLE_INSETS_VISIBLE() = 0 ;
	HIDESBASE virtual _di_JInputMethodService_Insets __cdecl init() = 0 ;
	__property int TOUCHABLE_INSETS_CONTENT = {read=_GetTOUCHABLE_INSETS_CONTENT};
	__property int TOUCHABLE_INSETS_FRAME = {read=_GetTOUCHABLE_INSETS_FRAME};
	__property int TOUCHABLE_INSETS_REGION = {read=_GetTOUCHABLE_INSETS_REGION};
	__property int TOUCHABLE_INSETS_VISIBLE = {read=_GetTOUCHABLE_INSETS_VISIBLE};
};

__interface  INTERFACE_UUID("{60F3EDB8-4C1B-411B-8466-7C849D07C475}") JInputMethodService_Insets  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl _GetcontentTopInsets() = 0 ;
	virtual void __cdecl _SetcontentTopInsets(int Value) = 0 ;
	virtual int __cdecl _GettouchableInsets() = 0 ;
	virtual void __cdecl _SettouchableInsets(int Value) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JRegion __cdecl _GettouchableRegion() = 0 ;
	virtual int __cdecl _GetvisibleTopInsets() = 0 ;
	virtual void __cdecl _SetvisibleTopInsets(int Value) = 0 ;
	__property int contentTopInsets = {read=_GetcontentTopInsets, write=_SetcontentTopInsets};
	__property int touchableInsets = {read=_GettouchableInsets, write=_SettouchableInsets};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JRegion touchableRegion = {read=_GettouchableRegion};
	__property int visibleTopInsets = {read=_GetvisibleTopInsets, write=_SetvisibleTopInsets};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInputMethodService_Insets : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInputMethodService_InsetsClass,_di_JInputMethodService_Insets>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInputMethodService_InsetsClass,_di_JInputMethodService_Insets> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInputMethodService_Insets() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInputMethodService_InsetsClass,_di_JInputMethodService_Insets>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInputMethodService_Insets() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{91B42F2E-9703-4C17-AAEB-27B8D1E33E7C}") JKeyboardClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetEDGE_BOTTOM() = 0 ;
	virtual int __cdecl _GetEDGE_LEFT() = 0 ;
	virtual int __cdecl _GetEDGE_RIGHT() = 0 ;
	virtual int __cdecl _GetEDGE_TOP() = 0 ;
	virtual int __cdecl _GetKEYCODE_ALT() = 0 ;
	virtual int __cdecl _GetKEYCODE_CANCEL() = 0 ;
	virtual int __cdecl _GetKEYCODE_DELETE() = 0 ;
	virtual int __cdecl _GetKEYCODE_DONE() = 0 ;
	virtual int __cdecl _GetKEYCODE_MODE_CHANGE() = 0 ;
	virtual int __cdecl _GetKEYCODE_SHIFT() = 0 ;
	HIDESBASE virtual _di_JKeyboard __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int xmlLayoutResId) = 0 /* overload */;
	HIDESBASE virtual _di_JKeyboard __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int xmlLayoutResId, int modeId, int width, int height) = 0 /* overload */;
	HIDESBASE virtual _di_JKeyboard __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int xmlLayoutResId, int modeId) = 0 /* overload */;
	HIDESBASE virtual _di_JKeyboard __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int layoutTemplateResId, Androidapi::Jni::Javatypes::_di_JCharSequence characters, int columns, int horizontalPadding) = 0 /* overload */;
	__property int EDGE_BOTTOM = {read=_GetEDGE_BOTTOM};
	__property int EDGE_LEFT = {read=_GetEDGE_LEFT};
	__property int EDGE_RIGHT = {read=_GetEDGE_RIGHT};
	__property int EDGE_TOP = {read=_GetEDGE_TOP};
	__property int KEYCODE_ALT = {read=_GetKEYCODE_ALT};
	__property int KEYCODE_CANCEL = {read=_GetKEYCODE_CANCEL};
	__property int KEYCODE_DELETE = {read=_GetKEYCODE_DELETE};
	__property int KEYCODE_DONE = {read=_GetKEYCODE_DONE};
	__property int KEYCODE_MODE_CHANGE = {read=_GetKEYCODE_MODE_CHANGE};
	__property int KEYCODE_SHIFT = {read=_GetKEYCODE_SHIFT};
};

__interface  INTERFACE_UUID("{1E09EB21-68A8-4014-B9B5-3533B484F606}") JKeyboard  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl getHeight() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getKeys() = 0 ;
	virtual int __cdecl getMinWidth() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getModifierKeys() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<int>* __cdecl getNearestKeys(int x, int y) = 0 ;
	virtual int __cdecl getShiftKeyIndex() = 0 ;
	virtual bool __cdecl isShifted() = 0 ;
	virtual bool __cdecl setShifted(bool shiftState) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJKeyboard : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyboardClass,_di_JKeyboard>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyboardClass,_di_JKeyboard> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJKeyboard() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyboardClass,_di_JKeyboard>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJKeyboard() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{97E00498-38CE-40C5-BF50-AE916672F4EA}") JKeyboard_KeyClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JKeyboard_Key __cdecl init(_di_JKeyboard_Row parent) = 0 /* overload */;
	HIDESBASE virtual _di_JKeyboard_Key __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JResources res, _di_JKeyboard_Row parent, int x, int y, Androidapi::Jni::Graphicscontentviewtext::_di_JXmlResourceParser parser) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{244EF65E-2ECB-404B-BAB5-F2354EFFCCEB}") JKeyboard_Key  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jnibridge::TJavaArray__1<int>* __cdecl _Getcodes() = 0 ;
	virtual void __cdecl _Setcodes(Androidapi::Jnibridge::TJavaArray__1<int>* Value) = 0 ;
	virtual int __cdecl _GetedgeFlags() = 0 ;
	virtual void __cdecl _SetedgeFlags(int Value) = 0 ;
	virtual int __cdecl _Getgap() = 0 ;
	virtual void __cdecl _Setgap(int Value) = 0 ;
	virtual int __cdecl _Getheight() = 0 ;
	virtual void __cdecl _Setheight(int Value) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl _Geticon() = 0 ;
	virtual void __cdecl _Seticon(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable Value) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl _GeticonPreview() = 0 ;
	virtual void __cdecl _SeticonPreview(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl _Getlabel() = 0 ;
	virtual void __cdecl _Setlabel(Androidapi::Jni::Javatypes::_di_JCharSequence Value) = 0 ;
	virtual bool __cdecl _Getmodifier() = 0 ;
	virtual void __cdecl _Setmodifier(bool Value) = 0 ;
	virtual bool __cdecl _Geton() = 0 ;
	virtual void __cdecl _Seton(bool Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl _GetpopupCharacters() = 0 ;
	virtual void __cdecl _SetpopupCharacters(Androidapi::Jni::Javatypes::_di_JCharSequence Value) = 0 ;
	virtual int __cdecl _GetpopupResId() = 0 ;
	virtual void __cdecl _SetpopupResId(int Value) = 0 ;
	virtual bool __cdecl _Getpressed() = 0 ;
	virtual void __cdecl _Setpressed(bool Value) = 0 ;
	virtual bool __cdecl _Getrepeatable() = 0 ;
	virtual void __cdecl _Setrepeatable(bool Value) = 0 ;
	virtual bool __cdecl _Getsticky() = 0 ;
	virtual void __cdecl _Setsticky(bool Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl _Gettext() = 0 ;
	virtual void __cdecl _Settext(Androidapi::Jni::Javatypes::_di_JCharSequence Value) = 0 ;
	virtual int __cdecl _Getwidth() = 0 ;
	virtual void __cdecl _Setwidth(int Value) = 0 ;
	virtual int __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(int Value) = 0 ;
	virtual int __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(int Value) = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<int>* __cdecl getCurrentDrawableState() = 0 ;
	virtual bool __cdecl isInside(int x, int y) = 0 ;
	virtual void __cdecl onPressed() = 0 ;
	virtual void __cdecl onReleased(bool inside) = 0 ;
	virtual int __cdecl squaredDistanceFrom(int x, int y) = 0 ;
	__property Androidapi::Jnibridge::TJavaArray__1<int>* codes = {read=_Getcodes, write=_Setcodes};
	__property int edgeFlags = {read=_GetedgeFlags, write=_SetedgeFlags};
	__property int gap = {read=_Getgap, write=_Setgap};
	__property int height = {read=_Getheight, write=_Setheight};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable icon = {read=_Geticon, write=_Seticon};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable iconPreview = {read=_GeticonPreview, write=_SeticonPreview};
	__property Androidapi::Jni::Javatypes::_di_JCharSequence label = {read=_Getlabel, write=_Setlabel};
	__property bool modifier = {read=_Getmodifier, write=_Setmodifier};
	__property bool on = {read=_Geton, write=_Seton};
	__property Androidapi::Jni::Javatypes::_di_JCharSequence popupCharacters = {read=_GetpopupCharacters, write=_SetpopupCharacters};
	__property int popupResId = {read=_GetpopupResId, write=_SetpopupResId};
	__property bool pressed = {read=_Getpressed, write=_Setpressed};
	__property bool repeatable = {read=_Getrepeatable, write=_Setrepeatable};
	__property bool sticky = {read=_Getsticky, write=_Setsticky};
	__property Androidapi::Jni::Javatypes::_di_JCharSequence text = {read=_Gettext, write=_Settext};
	__property int width = {read=_Getwidth, write=_Setwidth};
	__property int x = {read=_Getx, write=_Setx};
	__property int y = {read=_Gety, write=_Sety};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJKeyboard_Key : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyboard_KeyClass,_di_JKeyboard_Key>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyboard_KeyClass,_di_JKeyboard_Key> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJKeyboard_Key() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyboard_KeyClass,_di_JKeyboard_Key>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJKeyboard_Key() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{70EFB31D-C849-4E18-B877-4FA6FF21C9C0}") JKeyboard_RowClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JKeyboard_Row __cdecl init(_di_JKeyboard parent) = 0 /* overload */;
	HIDESBASE virtual _di_JKeyboard_Row __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JResources res, _di_JKeyboard parent, Androidapi::Jni::Graphicscontentviewtext::_di_JXmlResourceParser parser) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{1D90FE86-1727-42D8-8C2A-1AF5306F4208}") JKeyboard_Row  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl _GetdefaultHeight() = 0 ;
	virtual void __cdecl _SetdefaultHeight(int Value) = 0 ;
	virtual int __cdecl _GetdefaultHorizontalGap() = 0 ;
	virtual void __cdecl _SetdefaultHorizontalGap(int Value) = 0 ;
	virtual int __cdecl _GetdefaultWidth() = 0 ;
	virtual void __cdecl _SetdefaultWidth(int Value) = 0 ;
	virtual int __cdecl _Getmode() = 0 ;
	virtual void __cdecl _Setmode(int Value) = 0 ;
	virtual int __cdecl _GetrowEdgeFlags() = 0 ;
	virtual void __cdecl _SetrowEdgeFlags(int Value) = 0 ;
	virtual int __cdecl _GetverticalGap() = 0 ;
	virtual void __cdecl _SetverticalGap(int Value) = 0 ;
	__property int defaultHeight = {read=_GetdefaultHeight, write=_SetdefaultHeight};
	__property int defaultHorizontalGap = {read=_GetdefaultHorizontalGap, write=_SetdefaultHorizontalGap};
	__property int defaultWidth = {read=_GetdefaultWidth, write=_SetdefaultWidth};
	__property int mode = {read=_Getmode, write=_Setmode};
	__property int rowEdgeFlags = {read=_GetrowEdgeFlags, write=_SetrowEdgeFlags};
	__property int verticalGap = {read=_GetverticalGap, write=_SetverticalGap};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJKeyboard_Row : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyboard_RowClass,_di_JKeyboard_Row>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyboard_RowClass,_di_JKeyboard_Row> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJKeyboard_Row() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyboard_RowClass,_di_JKeyboard_Row>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJKeyboard_Row() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{42940038-508B-45EF-A693-06F5A4FD13A7}") JKeyboardViewClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewClass 
{
	HIDESBASE virtual _di_JKeyboardView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JKeyboardView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JKeyboardView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{E1D3273B-0921-4ADA-BF8E-6CDAB5D52F52}") JKeyboardView  : public Androidapi::Jni::Graphicscontentviewtext::JView 
{
	virtual void __cdecl closing() = 0 ;
	virtual _di_JKeyboard __cdecl getKeyboard() = 0 ;
	virtual bool __cdecl handleBack() = 0 ;
	virtual void __cdecl invalidateAllKeys() = 0 ;
	virtual void __cdecl invalidateKey(int keyIndex) = 0 ;
	virtual bool __cdecl isPreviewEnabled() = 0 ;
	virtual bool __cdecl isProximityCorrectionEnabled() = 0 ;
	virtual bool __cdecl isShifted() = 0 ;
	virtual void __cdecl onDetachedFromWindow() = 0 ;
	virtual void __cdecl onDraw(Androidapi::Jni::Graphicscontentviewtext::_di_JCanvas canvas) = 0 ;
	HIDESBASE virtual bool __cdecl onHoverEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	virtual void __cdecl onMeasure(int widthMeasureSpec, int heightMeasureSpec) = 0 ;
	virtual void __cdecl onSizeChanged(int w, int h, int oldw, int oldh) = 0 ;
	HIDESBASE virtual bool __cdecl onTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent me) = 0 ;
	virtual void __cdecl setKeyboard(_di_JKeyboard keyboard) = 0 ;
	virtual void __cdecl setOnKeyboardActionListener(_di_JKeyboardView_OnKeyboardActionListener listener) = 0 ;
	virtual void __cdecl setPopupOffset(int x, int y) = 0 ;
	virtual void __cdecl setPopupParent(Androidapi::Jni::Graphicscontentviewtext::_di_JView v) = 0 ;
	virtual void __cdecl setPreviewEnabled(bool previewEnabled) = 0 ;
	virtual void __cdecl setProximityCorrectionEnabled(bool enabled) = 0 ;
	virtual bool __cdecl setShifted(bool shifted) = 0 ;
	virtual void __cdecl setVerticalCorrection(int verticalOffset) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJKeyboardView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyboardViewClass,_di_JKeyboardView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyboardViewClass,_di_JKeyboardView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJKeyboardView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyboardViewClass,_di_JKeyboardView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJKeyboardView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6236A842-C447-47FA-8A41-5EADA3BDCF4B}") JKeyboardView_OnKeyboardActionListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{5EA363D7-B77D-49A3-B54B-5DA8FAE2CD75}") JKeyboardView_OnKeyboardActionListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onKey(int primaryCode, Androidapi::Jnibridge::TJavaArray__1<int>* keyCodes) = 0 ;
	virtual void __cdecl onPress(int primaryCode) = 0 ;
	virtual void __cdecl onRelease(int primaryCode) = 0 ;
	virtual void __cdecl onText(Androidapi::Jni::Javatypes::_di_JCharSequence text) = 0 ;
	virtual void __cdecl swipeDown() = 0 ;
	virtual void __cdecl swipeLeft() = 0 ;
	virtual void __cdecl swipeRight() = 0 ;
	virtual void __cdecl swipeUp() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJKeyboardView_OnKeyboardActionListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyboardView_OnKeyboardActionListenerClass,_di_JKeyboardView_OnKeyboardActionListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyboardView_OnKeyboardActionListenerClass,_di_JKeyboardView_OnKeyboardActionListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJKeyboardView_OnKeyboardActionListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyboardView_OnKeyboardActionListenerClass,_di_JKeyboardView_OnKeyboardActionListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJKeyboardView_OnKeyboardActionListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Inputmethodservice */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_INPUTMETHODSERVICE)
using namespace Androidapi::Jni::Inputmethodservice;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI)
using namespace Androidapi::Jni;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_Jni_InputmethodserviceHPP
