// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.App.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_AppHPP
#define Androidapi_Jni_AppHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
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
namespace App
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JActionBarClass;
typedef System::DelphiInterface<JActionBarClass> _di_JActionBarClass;
__interface DELPHIINTERFACE JActionBar;
typedef System::DelphiInterface<JActionBar> _di_JActionBar;
class DELPHICLASS TJActionBar;
__interface DELPHIINTERFACE JActionBar_LayoutParamsClass;
typedef System::DelphiInterface<JActionBar_LayoutParamsClass> _di_JActionBar_LayoutParamsClass;
__interface DELPHIINTERFACE JActionBar_LayoutParams;
typedef System::DelphiInterface<JActionBar_LayoutParams> _di_JActionBar_LayoutParams;
class DELPHICLASS TJActionBar_LayoutParams;
__interface DELPHIINTERFACE JActionBar_OnMenuVisibilityListenerClass;
typedef System::DelphiInterface<JActionBar_OnMenuVisibilityListenerClass> _di_JActionBar_OnMenuVisibilityListenerClass;
__interface DELPHIINTERFACE JActionBar_OnMenuVisibilityListener;
typedef System::DelphiInterface<JActionBar_OnMenuVisibilityListener> _di_JActionBar_OnMenuVisibilityListener;
class DELPHICLASS TJActionBar_OnMenuVisibilityListener;
__interface DELPHIINTERFACE JActionBar_OnNavigationListenerClass;
typedef System::DelphiInterface<JActionBar_OnNavigationListenerClass> _di_JActionBar_OnNavigationListenerClass;
__interface DELPHIINTERFACE JActionBar_OnNavigationListener;
typedef System::DelphiInterface<JActionBar_OnNavigationListener> _di_JActionBar_OnNavigationListener;
class DELPHICLASS TJActionBar_OnNavigationListener;
__interface DELPHIINTERFACE JActionBar_TabClass;
typedef System::DelphiInterface<JActionBar_TabClass> _di_JActionBar_TabClass;
__interface DELPHIINTERFACE JActionBar_Tab;
typedef System::DelphiInterface<JActionBar_Tab> _di_JActionBar_Tab;
class DELPHICLASS TJActionBar_Tab;
__interface DELPHIINTERFACE JActionBar_TabListenerClass;
typedef System::DelphiInterface<JActionBar_TabListenerClass> _di_JActionBar_TabListenerClass;
__interface DELPHIINTERFACE JActionBar_TabListener;
typedef System::DelphiInterface<JActionBar_TabListener> _di_JActionBar_TabListener;
class DELPHICLASS TJActionBar_TabListener;
__interface DELPHIINTERFACE JActivityClass;
typedef System::DelphiInterface<JActivityClass> _di_JActivityClass;
__interface DELPHIINTERFACE JActivity;
typedef System::DelphiInterface<JActivity> _di_JActivity;
class DELPHICLASS TJActivity;
__interface DELPHIINTERFACE JActivityManagerClass;
typedef System::DelphiInterface<JActivityManagerClass> _di_JActivityManagerClass;
__interface DELPHIINTERFACE JActivityManager;
typedef System::DelphiInterface<JActivityManager> _di_JActivityManager;
class DELPHICLASS TJActivityManager;
__interface DELPHIINTERFACE JActivityManager_MemoryInfoClass;
typedef System::DelphiInterface<JActivityManager_MemoryInfoClass> _di_JActivityManager_MemoryInfoClass;
__interface DELPHIINTERFACE JActivityManager_MemoryInfo;
typedef System::DelphiInterface<JActivityManager_MemoryInfo> _di_JActivityManager_MemoryInfo;
class DELPHICLASS TJActivityManager_MemoryInfo;
__interface DELPHIINTERFACE JActivityManager_RunningAppProcessInfoClass;
typedef System::DelphiInterface<JActivityManager_RunningAppProcessInfoClass> _di_JActivityManager_RunningAppProcessInfoClass;
__interface DELPHIINTERFACE JActivityManager_RunningAppProcessInfo;
typedef System::DelphiInterface<JActivityManager_RunningAppProcessInfo> _di_JActivityManager_RunningAppProcessInfo;
class DELPHICLASS TJActivityManager_RunningAppProcessInfo;
__interface DELPHIINTERFACE JActivityManager_TaskDescriptionClass;
typedef System::DelphiInterface<JActivityManager_TaskDescriptionClass> _di_JActivityManager_TaskDescriptionClass;
__interface DELPHIINTERFACE JActivityManager_TaskDescription;
typedef System::DelphiInterface<JActivityManager_TaskDescription> _di_JActivityManager_TaskDescription;
class DELPHICLASS TJActivityManager_TaskDescription;
__interface DELPHIINTERFACE JAlarmManagerClass;
typedef System::DelphiInterface<JAlarmManagerClass> _di_JAlarmManagerClass;
__interface DELPHIINTERFACE JAlarmManager;
typedef System::DelphiInterface<JAlarmManager> _di_JAlarmManager;
class DELPHICLASS TJAlarmManager;
__interface DELPHIINTERFACE JAlarmManager_AlarmClockInfoClass;
typedef System::DelphiInterface<JAlarmManager_AlarmClockInfoClass> _di_JAlarmManager_AlarmClockInfoClass;
__interface DELPHIINTERFACE JAlarmManager_AlarmClockInfo;
typedef System::DelphiInterface<JAlarmManager_AlarmClockInfo> _di_JAlarmManager_AlarmClockInfo;
class DELPHICLASS TJAlarmManager_AlarmClockInfo;
__interface DELPHIINTERFACE JAlarmManager_OnAlarmListenerClass;
typedef System::DelphiInterface<JAlarmManager_OnAlarmListenerClass> _di_JAlarmManager_OnAlarmListenerClass;
__interface DELPHIINTERFACE JAlarmManager_OnAlarmListener;
typedef System::DelphiInterface<JAlarmManager_OnAlarmListener> _di_JAlarmManager_OnAlarmListener;
class DELPHICLASS TJAlarmManager_OnAlarmListener;
__interface DELPHIINTERFACE JDialogClass;
typedef System::DelphiInterface<JDialogClass> _di_JDialogClass;
__interface DELPHIINTERFACE JDialog;
typedef System::DelphiInterface<JDialog> _di_JDialog;
class DELPHICLASS TJDialog;
__interface DELPHIINTERFACE JAlertDialogClass;
typedef System::DelphiInterface<JAlertDialogClass> _di_JAlertDialogClass;
__interface DELPHIINTERFACE JAlertDialog;
typedef System::DelphiInterface<JAlertDialog> _di_JAlertDialog;
class DELPHICLASS TJAlertDialog;
__interface DELPHIINTERFACE JAlertDialog_BuilderClass;
typedef System::DelphiInterface<JAlertDialog_BuilderClass> _di_JAlertDialog_BuilderClass;
__interface DELPHIINTERFACE JAlertDialog_Builder;
typedef System::DelphiInterface<JAlertDialog_Builder> _di_JAlertDialog_Builder;
class DELPHICLASS TJAlertDialog_Builder;
__interface DELPHIINTERFACE JApplicationClass;
typedef System::DelphiInterface<JApplicationClass> _di_JApplicationClass;
__interface DELPHIINTERFACE JApplication;
typedef System::DelphiInterface<JApplication> _di_JApplication;
class DELPHICLASS TJApplication;
__interface DELPHIINTERFACE JApplication_ActivityLifecycleCallbacksClass;
typedef System::DelphiInterface<JApplication_ActivityLifecycleCallbacksClass> _di_JApplication_ActivityLifecycleCallbacksClass;
__interface DELPHIINTERFACE JApplication_ActivityLifecycleCallbacks;
typedef System::DelphiInterface<JApplication_ActivityLifecycleCallbacks> _di_JApplication_ActivityLifecycleCallbacks;
class DELPHICLASS TJApplication_ActivityLifecycleCallbacks;
__interface DELPHIINTERFACE JApplication_OnProvideAssistDataListenerClass;
typedef System::DelphiInterface<JApplication_OnProvideAssistDataListenerClass> _di_JApplication_OnProvideAssistDataListenerClass;
__interface DELPHIINTERFACE JApplication_OnProvideAssistDataListener;
typedef System::DelphiInterface<JApplication_OnProvideAssistDataListener> _di_JApplication_OnProvideAssistDataListener;
class DELPHICLASS TJApplication_OnProvideAssistDataListener;
__interface DELPHIINTERFACE JAutomaticZenRuleClass;
typedef System::DelphiInterface<JAutomaticZenRuleClass> _di_JAutomaticZenRuleClass;
__interface DELPHIINTERFACE JAutomaticZenRule;
typedef System::DelphiInterface<JAutomaticZenRule> _di_JAutomaticZenRule;
class DELPHICLASS TJAutomaticZenRule;
__interface DELPHIINTERFACE JFragmentClass;
typedef System::DelphiInterface<JFragmentClass> _di_JFragmentClass;
__interface DELPHIINTERFACE JFragment;
typedef System::DelphiInterface<JFragment> _di_JFragment;
class DELPHICLASS TJFragment;
__interface DELPHIINTERFACE JDialogFragmentClass;
typedef System::DelphiInterface<JDialogFragmentClass> _di_JDialogFragmentClass;
__interface DELPHIINTERFACE JDialogFragment;
typedef System::DelphiInterface<JDialogFragment> _di_JDialogFragment;
class DELPHICLASS TJDialogFragment;
__interface DELPHIINTERFACE JFragment_SavedStateClass;
typedef System::DelphiInterface<JFragment_SavedStateClass> _di_JFragment_SavedStateClass;
__interface DELPHIINTERFACE JFragment_SavedState;
typedef System::DelphiInterface<JFragment_SavedState> _di_JFragment_SavedState;
class DELPHICLASS TJFragment_SavedState;
__interface DELPHIINTERFACE JFragmentManagerClass;
typedef System::DelphiInterface<JFragmentManagerClass> _di_JFragmentManagerClass;
__interface DELPHIINTERFACE JFragmentManager;
typedef System::DelphiInterface<JFragmentManager> _di_JFragmentManager;
class DELPHICLASS TJFragmentManager;
__interface DELPHIINTERFACE JFragmentManager_BackStackEntryClass;
typedef System::DelphiInterface<JFragmentManager_BackStackEntryClass> _di_JFragmentManager_BackStackEntryClass;
__interface DELPHIINTERFACE JFragmentManager_BackStackEntry;
typedef System::DelphiInterface<JFragmentManager_BackStackEntry> _di_JFragmentManager_BackStackEntry;
class DELPHICLASS TJFragmentManager_BackStackEntry;
__interface DELPHIINTERFACE JFragmentManager_FragmentLifecycleCallbacksClass;
typedef System::DelphiInterface<JFragmentManager_FragmentLifecycleCallbacksClass> _di_JFragmentManager_FragmentLifecycleCallbacksClass;
__interface DELPHIINTERFACE JFragmentManager_FragmentLifecycleCallbacks;
typedef System::DelphiInterface<JFragmentManager_FragmentLifecycleCallbacks> _di_JFragmentManager_FragmentLifecycleCallbacks;
class DELPHICLASS TJFragmentManager_FragmentLifecycleCallbacks;
__interface DELPHIINTERFACE JFragmentManager_OnBackStackChangedListenerClass;
typedef System::DelphiInterface<JFragmentManager_OnBackStackChangedListenerClass> _di_JFragmentManager_OnBackStackChangedListenerClass;
__interface DELPHIINTERFACE JFragmentManager_OnBackStackChangedListener;
typedef System::DelphiInterface<JFragmentManager_OnBackStackChangedListener> _di_JFragmentManager_OnBackStackChangedListener;
class DELPHICLASS TJFragmentManager_OnBackStackChangedListener;
__interface DELPHIINTERFACE JFragmentTransactionClass;
typedef System::DelphiInterface<JFragmentTransactionClass> _di_JFragmentTransactionClass;
__interface DELPHIINTERFACE JFragmentTransaction;
typedef System::DelphiInterface<JFragmentTransaction> _di_JFragmentTransaction;
class DELPHICLASS TJFragmentTransaction;
__interface DELPHIINTERFACE JServiceClass;
typedef System::DelphiInterface<JServiceClass> _di_JServiceClass;
__interface DELPHIINTERFACE JService;
typedef System::DelphiInterface<JService> _di_JService;
class DELPHICLASS TJService;
__interface DELPHIINTERFACE JIntentServiceClass;
typedef System::DelphiInterface<JIntentServiceClass> _di_JIntentServiceClass;
__interface DELPHIINTERFACE JIntentService;
typedef System::DelphiInterface<JIntentService> _di_JIntentService;
class DELPHICLASS TJIntentService;
__interface DELPHIINTERFACE JLoaderManagerClass;
typedef System::DelphiInterface<JLoaderManagerClass> _di_JLoaderManagerClass;
__interface DELPHIINTERFACE JLoaderManager;
typedef System::DelphiInterface<JLoaderManager> _di_JLoaderManager;
class DELPHICLASS TJLoaderManager;
__interface DELPHIINTERFACE JLoaderManager_LoaderCallbacksClass;
typedef System::DelphiInterface<JLoaderManager_LoaderCallbacksClass> _di_JLoaderManager_LoaderCallbacksClass;
__interface DELPHIINTERFACE JLoaderManager_LoaderCallbacks;
typedef System::DelphiInterface<JLoaderManager_LoaderCallbacks> _di_JLoaderManager_LoaderCallbacks;
class DELPHICLASS TJLoaderManager_LoaderCallbacks;
__interface DELPHIINTERFACE JNativeActivityClass;
typedef System::DelphiInterface<JNativeActivityClass> _di_JNativeActivityClass;
__interface DELPHIINTERFACE JNativeActivity;
typedef System::DelphiInterface<JNativeActivity> _di_JNativeActivity;
class DELPHICLASS TJNativeActivity;
__interface DELPHIINTERFACE JNotificationClass;
typedef System::DelphiInterface<JNotificationClass> _di_JNotificationClass;
__interface DELPHIINTERFACE JNotification;
typedef System::DelphiInterface<JNotification> _di_JNotification;
class DELPHICLASS TJNotification;
__interface DELPHIINTERFACE JNotification_ActionClass;
typedef System::DelphiInterface<JNotification_ActionClass> _di_JNotification_ActionClass;
__interface DELPHIINTERFACE JNotification_Action;
typedef System::DelphiInterface<JNotification_Action> _di_JNotification_Action;
class DELPHICLASS TJNotification_Action;
__interface DELPHIINTERFACE JNotificationChannelClass;
typedef System::DelphiInterface<JNotificationChannelClass> _di_JNotificationChannelClass;
__interface DELPHIINTERFACE JNotificationChannel;
typedef System::DelphiInterface<JNotificationChannel> _di_JNotificationChannel;
class DELPHICLASS TJNotificationChannel;
__interface DELPHIINTERFACE JNotificationChannelGroupClass;
typedef System::DelphiInterface<JNotificationChannelGroupClass> _di_JNotificationChannelGroupClass;
__interface DELPHIINTERFACE JNotificationChannelGroup;
typedef System::DelphiInterface<JNotificationChannelGroup> _di_JNotificationChannelGroup;
class DELPHICLASS TJNotificationChannelGroup;
__interface DELPHIINTERFACE JNotificationManagerClass;
typedef System::DelphiInterface<JNotificationManagerClass> _di_JNotificationManagerClass;
__interface DELPHIINTERFACE JNotificationManager;
typedef System::DelphiInterface<JNotificationManager> _di_JNotificationManager;
class DELPHICLASS TJNotificationManager;
__interface DELPHIINTERFACE JNotificationManager_PolicyClass;
typedef System::DelphiInterface<JNotificationManager_PolicyClass> _di_JNotificationManager_PolicyClass;
__interface DELPHIINTERFACE JNotificationManager_Policy;
typedef System::DelphiInterface<JNotificationManager_Policy> _di_JNotificationManager_Policy;
class DELPHICLASS TJNotificationManager_Policy;
__interface DELPHIINTERFACE JPendingIntentClass;
typedef System::DelphiInterface<JPendingIntentClass> _di_JPendingIntentClass;
__interface DELPHIINTERFACE JPendingIntent;
typedef System::DelphiInterface<JPendingIntent> _di_JPendingIntent;
class DELPHICLASS TJPendingIntent;
__interface DELPHIINTERFACE JPendingIntent_OnFinishedClass;
typedef System::DelphiInterface<JPendingIntent_OnFinishedClass> _di_JPendingIntent_OnFinishedClass;
__interface DELPHIINTERFACE JPendingIntent_OnFinished;
typedef System::DelphiInterface<JPendingIntent_OnFinished> _di_JPendingIntent_OnFinished;
class DELPHICLASS TJPendingIntent_OnFinished;
__interface DELPHIINTERFACE JPictureInPictureArgsClass;
typedef System::DelphiInterface<JPictureInPictureArgsClass> _di_JPictureInPictureArgsClass;
__interface DELPHIINTERFACE JPictureInPictureArgs;
typedef System::DelphiInterface<JPictureInPictureArgs> _di_JPictureInPictureArgs;
class DELPHICLASS TJPictureInPictureArgs;
__interface DELPHIINTERFACE JPictureInPictureParamsClass;
typedef System::DelphiInterface<JPictureInPictureParamsClass> _di_JPictureInPictureParamsClass;
__interface DELPHIINTERFACE JPictureInPictureParams;
typedef System::DelphiInterface<JPictureInPictureParams> _di_JPictureInPictureParams;
class DELPHICLASS TJPictureInPictureParams;
__interface DELPHIINTERFACE JRemoteInputClass;
typedef System::DelphiInterface<JRemoteInputClass> _di_JRemoteInputClass;
__interface DELPHIINTERFACE JRemoteInput;
typedef System::DelphiInterface<JRemoteInput> _di_JRemoteInput;
class DELPHICLASS TJRemoteInput;
__interface DELPHIINTERFACE JSharedElementCallbackClass;
typedef System::DelphiInterface<JSharedElementCallbackClass> _di_JSharedElementCallbackClass;
__interface DELPHIINTERFACE JSharedElementCallback;
typedef System::DelphiInterface<JSharedElementCallback> _di_JSharedElementCallback;
class DELPHICLASS TJSharedElementCallback;
__interface DELPHIINTERFACE JSharedElementCallback_OnSharedElementsReadyListenerClass;
typedef System::DelphiInterface<JSharedElementCallback_OnSharedElementsReadyListenerClass> _di_JSharedElementCallback_OnSharedElementsReadyListenerClass;
__interface DELPHIINTERFACE JSharedElementCallback_OnSharedElementsReadyListener;
typedef System::DelphiInterface<JSharedElementCallback_OnSharedElementsReadyListener> _di_JSharedElementCallback_OnSharedElementsReadyListener;
class DELPHICLASS TJSharedElementCallback_OnSharedElementsReadyListener;
__interface DELPHIINTERFACE JTaskStackBuilderClass;
typedef System::DelphiInterface<JTaskStackBuilderClass> _di_JTaskStackBuilderClass;
__interface DELPHIINTERFACE JTaskStackBuilder;
typedef System::DelphiInterface<JTaskStackBuilder> _di_JTaskStackBuilder;
class DELPHICLASS TJTaskStackBuilder;
__interface DELPHIINTERFACE JVoiceInteractorClass;
typedef System::DelphiInterface<JVoiceInteractorClass> _di_JVoiceInteractorClass;
__interface DELPHIINTERFACE JVoiceInteractor;
typedef System::DelphiInterface<JVoiceInteractor> _di_JVoiceInteractor;
class DELPHICLASS TJVoiceInteractor;
__interface DELPHIINTERFACE JVoiceInteractor_RequestClass;
typedef System::DelphiInterface<JVoiceInteractor_RequestClass> _di_JVoiceInteractor_RequestClass;
__interface DELPHIINTERFACE JVoiceInteractor_Request;
typedef System::DelphiInterface<JVoiceInteractor_Request> _di_JVoiceInteractor_Request;
class DELPHICLASS TJVoiceInteractor_Request;
__interface DELPHIINTERFACE JAssistContentClass;
typedef System::DelphiInterface<JAssistContentClass> _di_JAssistContentClass;
__interface DELPHIINTERFACE JAssistContent;
typedef System::DelphiInterface<JAssistContent> _di_JAssistContent;
class DELPHICLASS TJAssistContent;
__interface DELPHIINTERFACE JAppWidgetProviderInfoClass;
typedef System::DelphiInterface<JAppWidgetProviderInfoClass> _di_JAppWidgetProviderInfoClass;
__interface DELPHIINTERFACE JAppWidgetProviderInfo;
typedef System::DelphiInterface<JAppWidgetProviderInfo> _di_JAppWidgetProviderInfo;
class DELPHICLASS TJAppWidgetProviderInfo;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{C1A41981-8687-4794-91A5-AA384F60A546}") JActionBarClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetDISPLAY_HOME_AS_UP() = 0 ;
	virtual int __cdecl _GetDISPLAY_SHOW_CUSTOM() = 0 ;
	virtual int __cdecl _GetDISPLAY_SHOW_HOME() = 0 ;
	virtual int __cdecl _GetDISPLAY_SHOW_TITLE() = 0 ;
	virtual int __cdecl _GetDISPLAY_USE_LOGO() = 0 ;
	virtual int __cdecl _GetNAVIGATION_MODE_LIST() = 0 ;
	virtual int __cdecl _GetNAVIGATION_MODE_STANDARD() = 0 ;
	virtual int __cdecl _GetNAVIGATION_MODE_TABS() = 0 ;
	HIDESBASE virtual _di_JActionBar __cdecl init() = 0 ;
	__property int DISPLAY_HOME_AS_UP = {read=_GetDISPLAY_HOME_AS_UP};
	__property int DISPLAY_SHOW_CUSTOM = {read=_GetDISPLAY_SHOW_CUSTOM};
	__property int DISPLAY_SHOW_HOME = {read=_GetDISPLAY_SHOW_HOME};
	__property int DISPLAY_SHOW_TITLE = {read=_GetDISPLAY_SHOW_TITLE};
	__property int DISPLAY_USE_LOGO = {read=_GetDISPLAY_USE_LOGO};
	__property int NAVIGATION_MODE_LIST = {read=_GetNAVIGATION_MODE_LIST};
	__property int NAVIGATION_MODE_STANDARD = {read=_GetNAVIGATION_MODE_STANDARD};
	__property int NAVIGATION_MODE_TABS = {read=_GetNAVIGATION_MODE_TABS};
};

__interface  INTERFACE_UUID("{607E590E-509A-40CB-A31C-448056752FAB}") JActionBar  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl addOnMenuVisibilityListener(_di_JActionBar_OnMenuVisibilityListener listener) = 0 ;
	virtual void __cdecl addTab(_di_JActionBar_Tab tab) = 0 /* overload */;
	virtual void __cdecl addTab(_di_JActionBar_Tab tab, bool setSelected) = 0 /* overload */;
	virtual void __cdecl addTab(_di_JActionBar_Tab tab, int position) = 0 /* overload */;
	virtual void __cdecl addTab(_di_JActionBar_Tab tab, int position, bool setSelected) = 0 /* overload */;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getCustomView() = 0 ;
	virtual int __cdecl getDisplayOptions() = 0 ;
	virtual float __cdecl getElevation() = 0 ;
	virtual int __cdecl getHeight() = 0 ;
	virtual int __cdecl getHideOffset() = 0 ;
	virtual int __cdecl getNavigationItemCount() = 0 ;
	virtual int __cdecl getNavigationMode() = 0 ;
	virtual int __cdecl getSelectedNavigationIndex() = 0 ;
	virtual _di_JActionBar_Tab __cdecl getSelectedTab() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getSubtitle() = 0 ;
	virtual _di_JActionBar_Tab __cdecl getTabAt(int index) = 0 ;
	virtual int __cdecl getTabCount() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JContext __cdecl getThemedContext() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getTitle() = 0 ;
	virtual void __cdecl hide() = 0 ;
	virtual bool __cdecl isHideOnContentScrollEnabled() = 0 ;
	virtual bool __cdecl isShowing() = 0 ;
	virtual _di_JActionBar_Tab __cdecl newTab() = 0 ;
	virtual void __cdecl removeAllTabs() = 0 ;
	virtual void __cdecl removeOnMenuVisibilityListener(_di_JActionBar_OnMenuVisibilityListener listener) = 0 ;
	virtual void __cdecl removeTab(_di_JActionBar_Tab tab) = 0 ;
	virtual void __cdecl removeTabAt(int position) = 0 ;
	virtual void __cdecl selectTab(_di_JActionBar_Tab tab) = 0 ;
	virtual void __cdecl setBackgroundDrawable(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable d) = 0 ;
	virtual void __cdecl setCustomView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 /* overload */;
	virtual void __cdecl setCustomView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, _di_JActionBar_LayoutParams layoutParams) = 0 /* overload */;
	virtual void __cdecl setCustomView(int resId) = 0 /* overload */;
	virtual void __cdecl setDisplayHomeAsUpEnabled(bool showHomeAsUp) = 0 ;
	virtual void __cdecl setDisplayOptions(int options) = 0 /* overload */;
	virtual void __cdecl setDisplayOptions(int options, int mask) = 0 /* overload */;
	virtual void __cdecl setDisplayShowCustomEnabled(bool showCustom) = 0 ;
	virtual void __cdecl setDisplayShowHomeEnabled(bool showHome) = 0 ;
	virtual void __cdecl setDisplayShowTitleEnabled(bool showTitle) = 0 ;
	virtual void __cdecl setDisplayUseLogoEnabled(bool useLogo) = 0 ;
	virtual void __cdecl setElevation(float elevation) = 0 ;
	virtual void __cdecl setHideOffset(int offset) = 0 ;
	virtual void __cdecl setHideOnContentScrollEnabled(bool hideOnContentScroll) = 0 ;
	virtual void __cdecl setHomeActionContentDescription(Androidapi::Jni::Javatypes::_di_JCharSequence description) = 0 /* overload */;
	virtual void __cdecl setHomeActionContentDescription(int resId) = 0 /* overload */;
	virtual void __cdecl setHomeAsUpIndicator(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable indicator) = 0 /* overload */;
	virtual void __cdecl setHomeAsUpIndicator(int resId) = 0 /* overload */;
	virtual void __cdecl setHomeButtonEnabled(bool enabled) = 0 ;
	virtual void __cdecl setIcon(int resId) = 0 /* overload */;
	virtual void __cdecl setIcon(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable icon) = 0 /* overload */;
	virtual void __cdecl setListNavigationCallbacks(Androidapi::Jni::Widget::_di_JSpinnerAdapter adapter, _di_JActionBar_OnNavigationListener callback) = 0 ;
	virtual void __cdecl setLogo(int resId) = 0 /* overload */;
	virtual void __cdecl setLogo(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable logo) = 0 /* overload */;
	virtual void __cdecl setNavigationMode(int mode) = 0 ;
	virtual void __cdecl setSelectedNavigationItem(int position) = 0 ;
	virtual void __cdecl setSplitBackgroundDrawable(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable d) = 0 ;
	virtual void __cdecl setStackedBackgroundDrawable(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable d) = 0 ;
	virtual void __cdecl setSubtitle(Androidapi::Jni::Javatypes::_di_JCharSequence subtitle) = 0 /* overload */;
	virtual void __cdecl setSubtitle(int resId) = 0 /* overload */;
	virtual void __cdecl setTitle(Androidapi::Jni::Javatypes::_di_JCharSequence title) = 0 /* overload */;
	virtual void __cdecl setTitle(int resId) = 0 /* overload */;
	virtual void __cdecl show() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJActionBar : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBarClass,_di_JActionBar>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBarClass,_di_JActionBar> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJActionBar() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBarClass,_di_JActionBar>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJActionBar() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EE4F0254-72CB-4FAC-8827-660F24B0EE45}") JActionBar_LayoutParamsClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup_MarginLayoutParamsClass 
{
	HIDESBASE virtual _di_JActionBar_LayoutParams __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JActionBar_LayoutParams __cdecl init(int width, int height) = 0 /* overload */;
	HIDESBASE virtual _di_JActionBar_LayoutParams __cdecl init(int width, int height, int gravity) = 0 /* overload */;
	HIDESBASE virtual _di_JActionBar_LayoutParams __cdecl init(int gravity) = 0 /* overload */;
	HIDESBASE virtual _di_JActionBar_LayoutParams __cdecl init(_di_JActionBar_LayoutParams source) = 0 /* overload */;
	HIDESBASE virtual _di_JActionBar_LayoutParams __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_LayoutParams source) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{A6E6BC68-48E8-4FCC-8011-66834CDEC359}") JActionBar_LayoutParams  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup_MarginLayoutParams 
{
	virtual int __cdecl _Getgravity() = 0 ;
	virtual void __cdecl _Setgravity(int Value) = 0 ;
	__property int gravity = {read=_Getgravity, write=_Setgravity};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJActionBar_LayoutParams : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBar_LayoutParamsClass,_di_JActionBar_LayoutParams>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBar_LayoutParamsClass,_di_JActionBar_LayoutParams> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJActionBar_LayoutParams() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBar_LayoutParamsClass,_di_JActionBar_LayoutParams>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJActionBar_LayoutParams() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1E888E42-9D09-452B-9B44-2ABBB5BF0C1E}") JActionBar_OnMenuVisibilityListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{3BBAA971-1B13-4420-937F-D4DFEA9100FF}") JActionBar_OnMenuVisibilityListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onMenuVisibilityChanged(bool isVisible) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJActionBar_OnMenuVisibilityListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBar_OnMenuVisibilityListenerClass,_di_JActionBar_OnMenuVisibilityListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBar_OnMenuVisibilityListenerClass,_di_JActionBar_OnMenuVisibilityListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJActionBar_OnMenuVisibilityListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBar_OnMenuVisibilityListenerClass,_di_JActionBar_OnMenuVisibilityListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJActionBar_OnMenuVisibilityListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AE55F295-D4A1-4ED2-989C-83DCA6409D2A}") JActionBar_OnNavigationListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{E16E1F51-1909-4712-B76A-0CB4F3BC178E}") JActionBar_OnNavigationListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual bool __cdecl onNavigationItemSelected(int itemPosition, __int64 itemId) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJActionBar_OnNavigationListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBar_OnNavigationListenerClass,_di_JActionBar_OnNavigationListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBar_OnNavigationListenerClass,_di_JActionBar_OnNavigationListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJActionBar_OnNavigationListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBar_OnNavigationListenerClass,_di_JActionBar_OnNavigationListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJActionBar_OnNavigationListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{142282F8-609C-42B5-8953-9BD4E01A9412}") JActionBar_TabClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetINVALID_POSITION() = 0 ;
	HIDESBASE virtual _di_JActionBar_Tab __cdecl init() = 0 ;
	__property int INVALID_POSITION = {read=_GetINVALID_POSITION};
};

__interface  INTERFACE_UUID("{75064B3A-7834-47BD-9C0E-5FCBE4668F27}") JActionBar_Tab  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getContentDescription() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getCustomView() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl getIcon() = 0 ;
	virtual int __cdecl getPosition() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getTag() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getText() = 0 ;
	virtual void __cdecl select() = 0 ;
	virtual _di_JActionBar_Tab __cdecl setContentDescription(int resId) = 0 /* overload */;
	virtual _di_JActionBar_Tab __cdecl setContentDescription(Androidapi::Jni::Javatypes::_di_JCharSequence contentDesc) = 0 /* overload */;
	virtual _di_JActionBar_Tab __cdecl setCustomView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 /* overload */;
	virtual _di_JActionBar_Tab __cdecl setCustomView(int layoutResId) = 0 /* overload */;
	virtual _di_JActionBar_Tab __cdecl setIcon(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable icon) = 0 /* overload */;
	virtual _di_JActionBar_Tab __cdecl setIcon(int resId) = 0 /* overload */;
	virtual _di_JActionBar_Tab __cdecl setTabListener(_di_JActionBar_TabListener listener) = 0 ;
	virtual _di_JActionBar_Tab __cdecl setTag(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual _di_JActionBar_Tab __cdecl setText(Androidapi::Jni::Javatypes::_di_JCharSequence text) = 0 /* overload */;
	virtual _di_JActionBar_Tab __cdecl setText(int resId) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJActionBar_Tab : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBar_TabClass,_di_JActionBar_Tab>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBar_TabClass,_di_JActionBar_Tab> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJActionBar_Tab() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBar_TabClass,_di_JActionBar_Tab>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJActionBar_Tab() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3F89E13F-E7E0-45A7-9A8F-D64422BA7B0E}") JActionBar_TabListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{C7B5769A-4307-4E57-8F73-31E022332836}") JActionBar_TabListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onTabReselected(_di_JActionBar_Tab tab, _di_JFragmentTransaction ft) = 0 ;
	virtual void __cdecl onTabSelected(_di_JActionBar_Tab tab, _di_JFragmentTransaction ft) = 0 ;
	virtual void __cdecl onTabUnselected(_di_JActionBar_Tab tab, _di_JFragmentTransaction ft) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJActionBar_TabListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBar_TabListenerClass,_di_JActionBar_TabListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBar_TabListenerClass,_di_JActionBar_TabListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJActionBar_TabListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActionBar_TabListenerClass,_di_JActionBar_TabListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJActionBar_TabListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5269A525-12C7-4E15-AE63-4BD764EB357D}") JActivityClass  : public Androidapi::Jni::Graphicscontentviewtext::JContextThemeWrapperClass 
{
	virtual int __cdecl _GetDEFAULT_KEYS_DIALER() = 0 ;
	virtual int __cdecl _GetDEFAULT_KEYS_DISABLE() = 0 ;
	virtual int __cdecl _GetDEFAULT_KEYS_SEARCH_GLOBAL() = 0 ;
	virtual int __cdecl _GetDEFAULT_KEYS_SEARCH_LOCAL() = 0 ;
	virtual int __cdecl _GetDEFAULT_KEYS_SHORTCUT() = 0 ;
	virtual int __cdecl _GetRESULT_CANCELED() = 0 ;
	virtual int __cdecl _GetRESULT_FIRST_USER() = 0 ;
	virtual int __cdecl _GetRESULT_OK() = 0 ;
	HIDESBASE virtual _di_JActivity __cdecl init() = 0 ;
	__property int DEFAULT_KEYS_DIALER = {read=_GetDEFAULT_KEYS_DIALER};
	__property int DEFAULT_KEYS_DISABLE = {read=_GetDEFAULT_KEYS_DISABLE};
	__property int DEFAULT_KEYS_SEARCH_GLOBAL = {read=_GetDEFAULT_KEYS_SEARCH_GLOBAL};
	__property int DEFAULT_KEYS_SEARCH_LOCAL = {read=_GetDEFAULT_KEYS_SEARCH_LOCAL};
	__property int DEFAULT_KEYS_SHORTCUT = {read=_GetDEFAULT_KEYS_SHORTCUT};
	__property int RESULT_CANCELED = {read=_GetRESULT_CANCELED};
	__property int RESULT_FIRST_USER = {read=_GetRESULT_FIRST_USER};
	__property int RESULT_OK = {read=_GetRESULT_OK};
};

__interface  INTERFACE_UUID("{A91E133E-CBAB-48EB-99A8-AA047E90D3B8}") JActivity  : public Androidapi::Jni::Graphicscontentviewtext::JContextThemeWrapper 
{
	virtual void __cdecl addContentView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_LayoutParams params) = 0 ;
	virtual void __cdecl closeContextMenu() = 0 ;
	virtual void __cdecl closeOptionsMenu() = 0 ;
	virtual _di_JPendingIntent __cdecl createPendingResult(int requestCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent data, int flags) = 0 ;
	virtual void __cdecl dismissDialog(int id) = 0 ;
	virtual void __cdecl dismissKeyboardShortcutsHelper() = 0 ;
	virtual bool __cdecl dispatchGenericMotionEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent ev) = 0 ;
	virtual bool __cdecl dispatchKeyEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl dispatchKeyShortcutEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl dispatchPopulateAccessibilityEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JAccessibilityEvent event) = 0 ;
	virtual bool __cdecl dispatchTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent ev) = 0 ;
	virtual bool __cdecl dispatchTrackballEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent ev) = 0 ;
	virtual void __cdecl dump(Androidapi::Jni::Javatypes::_di_JString prefix, Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, Androidapi::Jni::Javatypes::_di_JPrintWriter writer, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* args) = 0 ;
	virtual void __cdecl enterPictureInPictureMode() = 0 /* overload */;
	virtual bool __cdecl enterPictureInPictureMode(_di_JPictureInPictureArgs args) = 0 /* overload */;
	virtual bool __cdecl enterPictureInPictureMode(_di_JPictureInPictureParams params) = 0 /* overload */;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl findViewById(int id) = 0 ;
	virtual void __cdecl finish() = 0 ;
	virtual void __cdecl finishActivity(int requestCode) = 0 ;
	virtual void __cdecl finishActivityFromChild(_di_JActivity child, int requestCode) = 0 ;
	virtual void __cdecl finishAffinity() = 0 ;
	virtual void __cdecl finishAfterTransition() = 0 ;
	virtual void __cdecl finishAndRemoveTask() = 0 ;
	virtual void __cdecl finishFromChild(_di_JActivity child) = 0 ;
	virtual _di_JActionBar __cdecl getActionBar() = 0 ;
	virtual _di_JApplication __cdecl getApplication() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName __cdecl getCallingActivity() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getCallingPackage() = 0 ;
	virtual int __cdecl getChangingConfigurations() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName __cdecl getComponentName() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getCurrentFocus() = 0 ;
	virtual _di_JFragmentManager __cdecl getFragmentManager() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JIntent __cdecl getIntent() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getLastNonConfigurationInstance() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JLayoutInflater __cdecl getLayoutInflater() = 0 ;
	virtual _di_JLoaderManager __cdecl getLoaderManager() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getLocalClassName() = 0 ;
	virtual int __cdecl getMaxNumPictureInPictureActions() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JMenuInflater __cdecl getMenuInflater() = 0 ;
	virtual _di_JActivity __cdecl getParent() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JIntent __cdecl getParentActivityIntent() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JSharedPreferences __cdecl getPreferences(int mode) = 0 ;
	virtual int __cdecl getRequestedOrientation() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JSearchEvent __cdecl getSearchEvent() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getSystemService(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual int __cdecl getTaskId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getTitle() = 0 ;
	virtual int __cdecl getTitleColor() = 0 ;
	virtual _di_JVoiceInteractor __cdecl getVoiceInteractor() = 0 ;
	virtual int __cdecl getVolumeControlStream() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JWindow __cdecl getWindow() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JWindowManager __cdecl getWindowManager() = 0 ;
	virtual bool __cdecl hasWindowFocus() = 0 ;
	virtual void __cdecl invalidateOptionsMenu() = 0 ;
	virtual bool __cdecl isActivityTransitionRunning() = 0 ;
	virtual bool __cdecl isChangingConfigurations() = 0 ;
	virtual bool __cdecl isChild() = 0 ;
	virtual bool __cdecl isDestroyed() = 0 ;
	virtual bool __cdecl isFinishing() = 0 ;
	virtual bool __cdecl isImmersive() = 0 ;
	virtual bool __cdecl isInMultiWindowMode() = 0 ;
	virtual bool __cdecl isInPictureInPictureMode() = 0 ;
	virtual bool __cdecl isLocalVoiceInteractionSupported() = 0 ;
	virtual bool __cdecl isTaskRoot() = 0 ;
	virtual bool __cdecl isVoiceInteraction() = 0 ;
	virtual bool __cdecl isVoiceInteractionRoot() = 0 ;
	virtual bool __cdecl moveTaskToBack(bool nonRoot) = 0 ;
	virtual bool __cdecl navigateUpTo(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent upIntent) = 0 ;
	virtual bool __cdecl navigateUpToFromChild(_di_JActivity child, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent upIntent) = 0 ;
	virtual void __cdecl onActionModeFinished(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode) = 0 ;
	virtual void __cdecl onActionModeStarted(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode) = 0 ;
	virtual void __cdecl onActivityReenter(int resultCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent data) = 0 ;
	virtual void __cdecl onAttachFragment(_di_JFragment fragment) = 0 ;
	virtual void __cdecl onAttachedToWindow() = 0 ;
	virtual void __cdecl onBackPressed() = 0 ;
	virtual void __cdecl onConfigurationChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JConfiguration newConfig) = 0 ;
	virtual void __cdecl onContentChanged() = 0 ;
	virtual bool __cdecl onContextItemSelected(Androidapi::Jni::Graphicscontentviewtext::_di_JMenuItem item) = 0 ;
	virtual void __cdecl onContextMenuClosed(Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onCreate(Androidapi::Jni::Os::_di_JBundle savedInstanceState, Androidapi::Jni::Os::_di_JPersistableBundle persistentState) = 0 ;
	virtual void __cdecl onCreateContextMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JContextMenu menu, Androidapi::Jni::Graphicscontentviewtext::_di_JView v, Androidapi::Jni::Graphicscontentviewtext::_di_JContextMenu_ContextMenuInfo menuInfo) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl onCreateDescription() = 0 ;
	virtual void __cdecl onCreateNavigateUpTaskStack(_di_JTaskStackBuilder builder) = 0 ;
	virtual bool __cdecl onCreateOptionsMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual bool __cdecl onCreatePanelMenu(int featureId, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl onCreatePanelView(int featureId) = 0 ;
	virtual bool __cdecl onCreateThumbnail(Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap outBitmap, Androidapi::Jni::Graphicscontentviewtext::_di_JCanvas canvas) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl onCreateView(Androidapi::Jni::Javatypes::_di_JString name, Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl onCreateView(Androidapi::Jni::Graphicscontentviewtext::_di_JView parent, Androidapi::Jni::Javatypes::_di_JString name, Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	virtual void __cdecl onDetachedFromWindow() = 0 ;
	virtual void __cdecl onEnterAnimationComplete() = 0 ;
	virtual bool __cdecl onGenericMotionEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	virtual bool __cdecl onKeyDown(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl onKeyLongPress(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl onKeyMultiple(int keyCode, int repeatCount, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl onKeyShortcut(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl onKeyUp(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual void __cdecl onLocalVoiceInteractionStarted() = 0 ;
	virtual void __cdecl onLocalVoiceInteractionStopped() = 0 ;
	virtual void __cdecl onLowMemory() = 0 ;
	virtual bool __cdecl onMenuItemSelected(int featureId, Androidapi::Jni::Graphicscontentviewtext::_di_JMenuItem item) = 0 ;
	virtual bool __cdecl onMenuOpened(int featureId, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onMultiWindowModeChanged(bool isInMultiWindowMode, Androidapi::Jni::Graphicscontentviewtext::_di_JConfiguration newConfig) = 0 /* overload */;
	virtual void __cdecl onMultiWindowModeChanged(bool isInMultiWindowMode) = 0 /* overload */;
	virtual bool __cdecl onNavigateUp() = 0 ;
	virtual bool __cdecl onNavigateUpFromChild(_di_JActivity child) = 0 ;
	virtual bool __cdecl onOptionsItemSelected(Androidapi::Jni::Graphicscontentviewtext::_di_JMenuItem item) = 0 ;
	virtual void __cdecl onOptionsMenuClosed(Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onPanelClosed(int featureId, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onPictureInPictureModeChanged(bool isInPictureInPictureMode, Androidapi::Jni::Graphicscontentviewtext::_di_JConfiguration newConfig) = 0 /* overload */;
	virtual void __cdecl onPictureInPictureModeChanged(bool isInPictureInPictureMode) = 0 /* overload */;
	virtual void __cdecl onPostCreate(Androidapi::Jni::Os::_di_JBundle savedInstanceState, Androidapi::Jni::Os::_di_JPersistableBundle persistentState) = 0 ;
	virtual void __cdecl onPrepareNavigateUpTaskStack(_di_JTaskStackBuilder builder) = 0 ;
	virtual bool __cdecl onPrepareOptionsMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual bool __cdecl onPreparePanel(int featureId, Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onProvideAssistContent(_di_JAssistContent outContent) = 0 ;
	virtual void __cdecl onProvideAssistData(Androidapi::Jni::Os::_di_JBundle data) = 0 ;
	virtual void __cdecl onProvideKeyboardShortcuts(Androidapi::Jni::Javatypes::_di_JList data, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu, int deviceId) = 0 ;
	virtual void __cdecl onRequestPermissionsResult(int requestCode, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* permissions, Androidapi::Jnibridge::TJavaArray__1<int>* grantResults) = 0 ;
	virtual void __cdecl onRestoreInstanceState(Androidapi::Jni::Os::_di_JBundle savedInstanceState, Androidapi::Jni::Os::_di_JPersistableBundle persistentState) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl onRetainNonConfigurationInstance() = 0 ;
	virtual void __cdecl onSaveInstanceState(Androidapi::Jni::Os::_di_JBundle outState, Androidapi::Jni::Os::_di_JPersistableBundle outPersistentState) = 0 ;
	virtual bool __cdecl onSearchRequested(Androidapi::Jni::Graphicscontentviewtext::_di_JSearchEvent searchEvent) = 0 /* overload */;
	virtual bool __cdecl onSearchRequested() = 0 /* overload */;
	virtual void __cdecl onStateNotSaved() = 0 ;
	virtual bool __cdecl onTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	virtual bool __cdecl onTrackballEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	virtual void __cdecl onTrimMemory(int level) = 0 ;
	virtual void __cdecl onUserInteraction() = 0 ;
	virtual void __cdecl onVisibleBehindCanceled() = 0 ;
	virtual void __cdecl onWindowAttributesChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JWindowManager_LayoutParams params) = 0 ;
	virtual void __cdecl onWindowFocusChanged(bool hasFocus) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode __cdecl onWindowStartingActionMode(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode_Callback callback) = 0 /* overload */;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode __cdecl onWindowStartingActionMode(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode_Callback callback, int type_) = 0 /* overload */;
	virtual void __cdecl openContextMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
	virtual void __cdecl openOptionsMenu() = 0 ;
	virtual void __cdecl overridePendingTransition(int enterAnim, int exitAnim) = 0 ;
	virtual void __cdecl postponeEnterTransition() = 0 ;
	virtual void __cdecl recreate() = 0 ;
	virtual void __cdecl registerForContextMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
	virtual bool __cdecl releaseInstance() = 0 ;
	virtual void __cdecl removeDialog(int id) = 0 ;
	virtual void __cdecl reportFullyDrawn() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDragAndDropPermissions __cdecl requestDragAndDropPermissions(Androidapi::Jni::Graphicscontentviewtext::_di_JDragEvent event) = 0 ;
	virtual void __cdecl requestPermissions(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* permissions, int requestCode) = 0 ;
	virtual void __cdecl requestShowKeyboardShortcuts() = 0 ;
	virtual bool __cdecl requestVisibleBehind(bool visible) = 0 ;
	virtual bool __cdecl requestWindowFeature(int featureId) = 0 ;
	virtual void __cdecl runOnUiThread(Androidapi::Jni::Javatypes::_di_JRunnable action) = 0 ;
	virtual void __cdecl setActionBar(Androidapi::Jni::Widget::_di_JToolbar toolbar) = 0 ;
	virtual void __cdecl setContentView(int layoutResID) = 0 /* overload */;
	virtual void __cdecl setContentView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 /* overload */;
	virtual void __cdecl setContentView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_LayoutParams params) = 0 /* overload */;
	virtual void __cdecl setDefaultKeyMode(int mode) = 0 ;
	virtual void __cdecl setEnterSharedElementCallback(_di_JSharedElementCallback callback) = 0 ;
	virtual void __cdecl setExitSharedElementCallback(_di_JSharedElementCallback callback) = 0 ;
	virtual void __cdecl setFeatureDrawable(int featureId, Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable drawable) = 0 ;
	virtual void __cdecl setFeatureDrawableAlpha(int featureId, int alpha) = 0 ;
	virtual void __cdecl setFeatureDrawableResource(int featureId, int resId) = 0 ;
	virtual void __cdecl setFinishOnTouchOutside(bool finish) = 0 ;
	virtual void __cdecl setImmersive(bool i) = 0 ;
	virtual void __cdecl setIntent(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent newIntent) = 0 ;
	virtual void __cdecl setPictureInPictureArgs(_di_JPictureInPictureArgs args) = 0 ;
	virtual void __cdecl setPictureInPictureParams(_di_JPictureInPictureParams params) = 0 ;
	virtual void __cdecl setProgress(int progress) = 0 ;
	virtual void __cdecl setProgressBarIndeterminate(bool indeterminate) = 0 ;
	virtual void __cdecl setProgressBarIndeterminateVisibility(bool visible) = 0 ;
	virtual void __cdecl setProgressBarVisibility(bool visible) = 0 ;
	virtual void __cdecl setRequestedOrientation(int requestedOrientation) = 0 ;
	virtual void __cdecl setResult(int resultCode) = 0 /* overload */;
	virtual void __cdecl setResult(int resultCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent data) = 0 /* overload */;
	virtual void __cdecl setSecondaryProgress(int secondaryProgress) = 0 ;
	virtual void __cdecl setTaskDescription(_di_JActivityManager_TaskDescription taskDescription) = 0 ;
	HIDESBASE virtual void __cdecl setTheme(int resid) = 0 ;
	virtual void __cdecl setTitle(Androidapi::Jni::Javatypes::_di_JCharSequence title) = 0 /* overload */;
	virtual void __cdecl setTitle(int titleId) = 0 /* overload */;
	virtual void __cdecl setTitleColor(int textColor) = 0 ;
	virtual void __cdecl setVisible(bool visible) = 0 ;
	virtual void __cdecl setVolumeControlStream(int streamType) = 0 ;
	virtual void __cdecl setVrModeEnabled(bool enabled, Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName requestedComponent) = 0 ;
	virtual bool __cdecl shouldShowRequestPermissionRationale(Androidapi::Jni::Javatypes::_di_JString permission) = 0 ;
	virtual bool __cdecl shouldUpRecreateTask(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent targetIntent) = 0 ;
	virtual bool __cdecl showAssist(Androidapi::Jni::Os::_di_JBundle args) = 0 ;
	virtual void __cdecl showDialog(int id) = 0 /* overload */;
	virtual bool __cdecl showDialog(int id, Androidapi::Jni::Os::_di_JBundle args) = 0 /* overload */;
	virtual void __cdecl showLockTaskEscapeMessage() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode __cdecl startActionMode(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode_Callback callback) = 0 /* overload */;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode __cdecl startActionMode(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode_Callback callback, int type_) = 0 /* overload */;
	HIDESBASE virtual void __cdecl startActivities(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JIntent>* intents) = 0 /* overload */;
	HIDESBASE virtual void __cdecl startActivities(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JIntent>* intents, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	HIDESBASE virtual void __cdecl startActivity(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 /* overload */;
	HIDESBASE virtual void __cdecl startActivity(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual void __cdecl startActivityForResult(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int requestCode) = 0 /* overload */;
	virtual void __cdecl startActivityForResult(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int requestCode, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual void __cdecl startActivityFromChild(_di_JActivity child, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int requestCode) = 0 /* overload */;
	virtual void __cdecl startActivityFromChild(_di_JActivity child, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int requestCode, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual void __cdecl startActivityFromFragment(_di_JFragment fragment, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int requestCode) = 0 /* overload */;
	virtual void __cdecl startActivityFromFragment(_di_JFragment fragment, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int requestCode, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual bool __cdecl startActivityIfNeeded(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int requestCode) = 0 /* overload */;
	virtual bool __cdecl startActivityIfNeeded(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int requestCode, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	HIDESBASE virtual void __cdecl startIntentSender(Androidapi::Jni::Graphicscontentviewtext::_di_JIntentSender intent, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent fillInIntent, int flagsMask, int flagsValues, int extraFlags) = 0 /* overload */;
	HIDESBASE virtual void __cdecl startIntentSender(Androidapi::Jni::Graphicscontentviewtext::_di_JIntentSender intent, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent fillInIntent, int flagsMask, int flagsValues, int extraFlags, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual void __cdecl startIntentSenderForResult(Androidapi::Jni::Graphicscontentviewtext::_di_JIntentSender intent, int requestCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent fillInIntent, int flagsMask, int flagsValues, int extraFlags) = 0 /* overload */;
	virtual void __cdecl startIntentSenderForResult(Androidapi::Jni::Graphicscontentviewtext::_di_JIntentSender intent, int requestCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent fillInIntent, int flagsMask, int flagsValues, int extraFlags, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual void __cdecl startIntentSenderFromChild(_di_JActivity child, Androidapi::Jni::Graphicscontentviewtext::_di_JIntentSender intent, int requestCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent fillInIntent, int flagsMask, int flagsValues, int extraFlags) = 0 /* overload */;
	virtual void __cdecl startIntentSenderFromChild(_di_JActivity child, Androidapi::Jni::Graphicscontentviewtext::_di_JIntentSender intent, int requestCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent fillInIntent, int flagsMask, int flagsValues, int extraFlags, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual void __cdecl startLocalVoiceInteraction(Androidapi::Jni::Os::_di_JBundle privateOptions) = 0 ;
	virtual void __cdecl startLockTask() = 0 ;
	virtual void __cdecl startManagingCursor(Androidapi::Jni::Graphicscontentviewtext::_di_JCursor c) = 0 ;
	virtual bool __cdecl startNextMatchingActivity(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 /* overload */;
	virtual bool __cdecl startNextMatchingActivity(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual void __cdecl startPostponedEnterTransition() = 0 ;
	virtual void __cdecl startSearch(Androidapi::Jni::Javatypes::_di_JString initialQuery, bool selectInitialQuery, Androidapi::Jni::Os::_di_JBundle appSearchData, bool globalSearch) = 0 ;
	virtual void __cdecl stopLocalVoiceInteraction() = 0 ;
	virtual void __cdecl stopLockTask() = 0 ;
	virtual void __cdecl stopManagingCursor(Androidapi::Jni::Graphicscontentviewtext::_di_JCursor c) = 0 ;
	virtual void __cdecl takeKeyEvents(bool get_) = 0 ;
	virtual void __cdecl triggerSearch(Androidapi::Jni::Javatypes::_di_JString query, Androidapi::Jni::Os::_di_JBundle appSearchData) = 0 ;
	virtual void __cdecl unregisterForContextMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJActivity : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityClass,_di_JActivity>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityClass,_di_JActivity> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJActivity() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityClass,_di_JActivity>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJActivity() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4C501FA2-A977-439E-A82A-538A3A87BCBE}") JActivityManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_REPORT_HEAP_LIMIT() = 0 ;
	virtual int __cdecl _GetLOCK_TASK_MODE_LOCKED() = 0 ;
	virtual int __cdecl _GetLOCK_TASK_MODE_NONE() = 0 ;
	virtual int __cdecl _GetLOCK_TASK_MODE_PINNED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMETA_HOME_ALTERNATE() = 0 ;
	virtual int __cdecl _GetMOVE_TASK_NO_USER_ACTION() = 0 ;
	virtual int __cdecl _GetMOVE_TASK_WITH_HOME() = 0 ;
	virtual int __cdecl _GetRECENT_IGNORE_UNAVAILABLE() = 0 ;
	virtual int __cdecl _GetRECENT_WITH_EXCLUDED() = 0 ;
	virtual int __cdecl getMaxNumPictureInPictureActions() = 0 ;
	virtual void __cdecl getMyMemoryState(_di_JActivityManager_RunningAppProcessInfo outState) = 0 ;
	virtual bool __cdecl isRunningInTestHarness() = 0 ;
	virtual bool __cdecl isUserAMonkey() = 0 ;
	virtual void __cdecl setVrThread(int tid) = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_REPORT_HEAP_LIMIT = {read=_GetACTION_REPORT_HEAP_LIMIT};
	__property int LOCK_TASK_MODE_LOCKED = {read=_GetLOCK_TASK_MODE_LOCKED};
	__property int LOCK_TASK_MODE_NONE = {read=_GetLOCK_TASK_MODE_NONE};
	__property int LOCK_TASK_MODE_PINNED = {read=_GetLOCK_TASK_MODE_PINNED};
	__property Androidapi::Jni::Javatypes::_di_JString META_HOME_ALTERNATE = {read=_GetMETA_HOME_ALTERNATE};
	__property int MOVE_TASK_NO_USER_ACTION = {read=_GetMOVE_TASK_NO_USER_ACTION};
	__property int MOVE_TASK_WITH_HOME = {read=_GetMOVE_TASK_WITH_HOME};
	__property int RECENT_IGNORE_UNAVAILABLE = {read=_GetRECENT_IGNORE_UNAVAILABLE};
	__property int RECENT_WITH_EXCLUDED = {read=_GetRECENT_WITH_EXCLUDED};
};

__interface  INTERFACE_UUID("{F4D6753D-F28A-4E3E-87A0-64B46C89C6EB}") JActivityManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl addAppTask(_di_JActivity activity, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, _di_JActivityManager_TaskDescription description, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap thumbnail) = 0 ;
	virtual bool __cdecl clearApplicationUserData() = 0 ;
	virtual void __cdecl clearWatchHeapLimit() = 0 ;
	virtual void __cdecl dumpPackageState(Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, Androidapi::Jni::Javatypes::_di_JString packageName) = 0 ;
	virtual Androidapi::Jni::Util::_di_Jutil_Size __cdecl getAppTaskThumbnailSize() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getAppTasks() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JConfigurationInfo __cdecl getDeviceConfigurationInfo() = 0 ;
	virtual int __cdecl getLargeMemoryClass() = 0 ;
	virtual int __cdecl getLauncherLargeIconDensity() = 0 ;
	virtual int __cdecl getLauncherLargeIconSize() = 0 ;
	virtual int __cdecl getLockTaskModeState() = 0 ;
	virtual int __cdecl getMemoryClass() = 0 ;
	virtual void __cdecl getMemoryInfo(_di_JActivityManager_MemoryInfo outInfo) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Os::_di_JDebug_MemoryInfo>* __cdecl getProcessMemoryInfo(Androidapi::Jnibridge::TJavaArray__1<int>* pids) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getProcessesInErrorState() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getRecentTasks(int maxNum, int flags) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getRunningAppProcesses() = 0 ;
	virtual _di_JPendingIntent __cdecl getRunningServiceControlPanel(Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName service) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getRunningServices(int maxNum) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getRunningTasks(int maxNum) = 0 ;
	virtual bool __cdecl isInLockTaskMode() = 0 ;
	virtual bool __cdecl isLowRamDevice() = 0 ;
	virtual void __cdecl killBackgroundProcesses(Androidapi::Jni::Javatypes::_di_JString packageName) = 0 ;
	virtual void __cdecl moveTaskToFront(int taskId, int flags) = 0 /* overload */;
	virtual void __cdecl moveTaskToFront(int taskId, int flags, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual void __cdecl restartPackage(Androidapi::Jni::Javatypes::_di_JString packageName) = 0 ;
	virtual void __cdecl setWatchHeapLimit(__int64 pssSize) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJActivityManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityManagerClass,_di_JActivityManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityManagerClass,_di_JActivityManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJActivityManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityManagerClass,_di_JActivityManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJActivityManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{647AEED3-4AE3-48B7-88F1-ADD7DA84EA6E}") JActivityManager_MemoryInfoClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JActivityManager_MemoryInfo __cdecl init() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{1A52DA44-8A7A-4C46-BE08-20C6190D593C}") JActivityManager_MemoryInfo  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual __int64 __cdecl _GetavailMem() = 0 ;
	virtual void __cdecl _SetavailMem(__int64 Value) = 0 ;
	virtual bool __cdecl _GetlowMemory() = 0 ;
	virtual void __cdecl _SetlowMemory(bool Value) = 0 ;
	virtual __int64 __cdecl _Getthreshold() = 0 ;
	virtual void __cdecl _Setthreshold(__int64 Value) = 0 ;
	virtual __int64 __cdecl _GettotalMem() = 0 ;
	virtual void __cdecl _SettotalMem(__int64 Value) = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual void __cdecl readFromParcel(Androidapi::Jni::Os::_di_JParcel source) = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
	__property __int64 availMem = {read=_GetavailMem, write=_SetavailMem};
	__property bool lowMemory = {read=_GetlowMemory, write=_SetlowMemory};
	__property __int64 threshold = {read=_Getthreshold, write=_Setthreshold};
	__property __int64 totalMem = {read=_GettotalMem, write=_SettotalMem};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJActivityManager_MemoryInfo : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityManager_MemoryInfoClass,_di_JActivityManager_MemoryInfo>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityManager_MemoryInfoClass,_di_JActivityManager_MemoryInfo> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJActivityManager_MemoryInfo() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityManager_MemoryInfoClass,_di_JActivityManager_MemoryInfo>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJActivityManager_MemoryInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{92E3280A-D655-40EA-99A4-08FFEC6BD1C1}") JActivityManager_RunningAppProcessInfoClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_BACKGROUND() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_CACHED() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_EMPTY() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_FOREGROUND() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_FOREGROUND_SERVICE() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_GONE() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_PERCEPTIBLE() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_PERCEPTIBLE_PRE_26() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_SERVICE() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_TOP_SLEEPING() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_VISIBLE() = 0 ;
	virtual int __cdecl _GetREASON_PROVIDER_IN_USE() = 0 ;
	virtual int __cdecl _GetREASON_SERVICE_IN_USE() = 0 ;
	virtual int __cdecl _GetREASON_UNKNOWN() = 0 ;
	HIDESBASE virtual _di_JActivityManager_RunningAppProcessInfo __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JActivityManager_RunningAppProcessInfo __cdecl init(Androidapi::Jni::Javatypes::_di_JString pProcessName, int pPid, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* pArr) = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int IMPORTANCE_BACKGROUND = {read=_GetIMPORTANCE_BACKGROUND};
	__property int IMPORTANCE_CACHED = {read=_GetIMPORTANCE_CACHED};
	__property int IMPORTANCE_EMPTY = {read=_GetIMPORTANCE_EMPTY};
	__property int IMPORTANCE_FOREGROUND = {read=_GetIMPORTANCE_FOREGROUND};
	__property int IMPORTANCE_FOREGROUND_SERVICE = {read=_GetIMPORTANCE_FOREGROUND_SERVICE};
	__property int IMPORTANCE_GONE = {read=_GetIMPORTANCE_GONE};
	__property int IMPORTANCE_PERCEPTIBLE = {read=_GetIMPORTANCE_PERCEPTIBLE};
	__property int IMPORTANCE_PERCEPTIBLE_PRE_26 = {read=_GetIMPORTANCE_PERCEPTIBLE_PRE_26};
	__property int IMPORTANCE_SERVICE = {read=_GetIMPORTANCE_SERVICE};
	__property int IMPORTANCE_TOP_SLEEPING = {read=_GetIMPORTANCE_TOP_SLEEPING};
	__property int IMPORTANCE_VISIBLE = {read=_GetIMPORTANCE_VISIBLE};
	__property int REASON_PROVIDER_IN_USE = {read=_GetREASON_PROVIDER_IN_USE};
	__property int REASON_SERVICE_IN_USE = {read=_GetREASON_SERVICE_IN_USE};
	__property int REASON_UNKNOWN = {read=_GetREASON_UNKNOWN};
};

__interface  INTERFACE_UUID("{247C91D3-5F45-4EA5-8D68-3392FB0D96C2}") JActivityManager_RunningAppProcessInfo  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl _Getimportance() = 0 ;
	virtual void __cdecl _Setimportance(int Value) = 0 ;
	virtual int __cdecl _GetimportanceReasonCode() = 0 ;
	virtual void __cdecl _SetimportanceReasonCode(int Value) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName __cdecl _GetimportanceReasonComponent() = 0 ;
	virtual void __cdecl _SetimportanceReasonComponent(Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName Value) = 0 ;
	virtual int __cdecl _GetimportanceReasonPid() = 0 ;
	virtual void __cdecl _SetimportanceReasonPid(int Value) = 0 ;
	virtual int __cdecl _GetlastTrimLevel() = 0 ;
	virtual void __cdecl _SetlastTrimLevel(int Value) = 0 ;
	virtual int __cdecl _Getlru() = 0 ;
	virtual void __cdecl _Setlru(int Value) = 0 ;
	virtual int __cdecl _Getpid() = 0 ;
	virtual void __cdecl _Setpid(int Value) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl _GetpkgList() = 0 ;
	virtual void __cdecl _SetpkgList(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetprocessName() = 0 ;
	virtual void __cdecl _SetprocessName(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual int __cdecl _Getuid() = 0 ;
	virtual void __cdecl _Setuid(int Value) = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual void __cdecl readFromParcel(Androidapi::Jni::Os::_di_JParcel source) = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
	__property int importance = {read=_Getimportance, write=_Setimportance};
	__property int importanceReasonCode = {read=_GetimportanceReasonCode, write=_SetimportanceReasonCode};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName importanceReasonComponent = {read=_GetimportanceReasonComponent, write=_SetimportanceReasonComponent};
	__property int importanceReasonPid = {read=_GetimportanceReasonPid, write=_SetimportanceReasonPid};
	__property int lastTrimLevel = {read=_GetlastTrimLevel, write=_SetlastTrimLevel};
	__property int lru = {read=_Getlru, write=_Setlru};
	__property int pid = {read=_Getpid, write=_Setpid};
	__property Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* pkgList = {read=_GetpkgList, write=_SetpkgList};
	__property Androidapi::Jni::Javatypes::_di_JString processName = {read=_GetprocessName, write=_SetprocessName};
	__property int uid = {read=_Getuid, write=_Setuid};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJActivityManager_RunningAppProcessInfo : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityManager_RunningAppProcessInfoClass,_di_JActivityManager_RunningAppProcessInfo>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityManager_RunningAppProcessInfoClass,_di_JActivityManager_RunningAppProcessInfo> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJActivityManager_RunningAppProcessInfo() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityManager_RunningAppProcessInfoClass,_di_JActivityManager_RunningAppProcessInfo>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJActivityManager_RunningAppProcessInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{CD8A19ED-7D7A-442C-90DE-2AF76B691643}") JActivityManager_TaskDescriptionClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JActivityManager_TaskDescription __cdecl init(Androidapi::Jni::Javatypes::_di_JString label_, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap icon, int colorPrimary) = 0 /* overload */;
	HIDESBASE virtual _di_JActivityManager_TaskDescription __cdecl init(Androidapi::Jni::Javatypes::_di_JString label_, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap icon) = 0 /* overload */;
	HIDESBASE virtual _di_JActivityManager_TaskDescription __cdecl init(Androidapi::Jni::Javatypes::_di_JString label_) = 0 /* overload */;
	HIDESBASE virtual _di_JActivityManager_TaskDescription __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JActivityManager_TaskDescription __cdecl init(_di_JActivityManager_TaskDescription td) = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{132EDB47-BAFB-4AF0-A3CD-4B6743FB2BAB}") JActivityManager_TaskDescription  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap __cdecl getIcon() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getLabel() = 0 ;
	virtual int __cdecl getPrimaryColor() = 0 ;
	virtual void __cdecl readFromParcel(Androidapi::Jni::Os::_di_JParcel source) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJActivityManager_TaskDescription : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityManager_TaskDescriptionClass,_di_JActivityManager_TaskDescription>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityManager_TaskDescriptionClass,_di_JActivityManager_TaskDescription> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJActivityManager_TaskDescription() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityManager_TaskDescriptionClass,_di_JActivityManager_TaskDescription>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJActivityManager_TaskDescription() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B26537D0-A769-4DD1-A5C3-2E2D9344193B}") JAlarmManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_NEXT_ALARM_CLOCK_CHANGED() = 0 ;
	virtual int __cdecl _GetELAPSED_REALTIME() = 0 ;
	virtual int __cdecl _GetELAPSED_REALTIME_WAKEUP() = 0 ;
	virtual __int64 __cdecl _GetINTERVAL_DAY() = 0 ;
	virtual __int64 __cdecl _GetINTERVAL_FIFTEEN_MINUTES() = 0 ;
	virtual __int64 __cdecl _GetINTERVAL_HALF_DAY() = 0 ;
	virtual __int64 __cdecl _GetINTERVAL_HALF_HOUR() = 0 ;
	virtual __int64 __cdecl _GetINTERVAL_HOUR() = 0 ;
	virtual int __cdecl _GetRTC() = 0 ;
	virtual int __cdecl _GetRTC_WAKEUP() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_NEXT_ALARM_CLOCK_CHANGED = {read=_GetACTION_NEXT_ALARM_CLOCK_CHANGED};
	__property int ELAPSED_REALTIME = {read=_GetELAPSED_REALTIME};
	__property int ELAPSED_REALTIME_WAKEUP = {read=_GetELAPSED_REALTIME_WAKEUP};
	__property __int64 INTERVAL_DAY = {read=_GetINTERVAL_DAY};
	__property __int64 INTERVAL_FIFTEEN_MINUTES = {read=_GetINTERVAL_FIFTEEN_MINUTES};
	__property __int64 INTERVAL_HALF_DAY = {read=_GetINTERVAL_HALF_DAY};
	__property __int64 INTERVAL_HALF_HOUR = {read=_GetINTERVAL_HALF_HOUR};
	__property __int64 INTERVAL_HOUR = {read=_GetINTERVAL_HOUR};
	__property int RTC = {read=_GetRTC};
	__property int RTC_WAKEUP = {read=_GetRTC_WAKEUP};
};

__interface  INTERFACE_UUID("{D4B2A2E3-48AD-491C-823B-DC301F6DA456}") JAlarmManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl cancel(_di_JPendingIntent operation) = 0 /* overload */;
	virtual void __cdecl cancel(_di_JAlarmManager_OnAlarmListener listener) = 0 /* overload */;
	virtual _di_JAlarmManager_AlarmClockInfo __cdecl getNextAlarmClock() = 0 ;
	virtual void __cdecl set(int type_, __int64 triggerAtMillis, _di_JPendingIntent operation) = 0 /* overload */;
	virtual void __cdecl set(int type_, __int64 triggerAtMillis, Androidapi::Jni::Javatypes::_di_JString tag, _di_JAlarmManager_OnAlarmListener listener, Androidapi::Jni::Os::_di_JHandler targetHandler) = 0 /* overload */;
	virtual void __cdecl setAlarmClock(_di_JAlarmManager_AlarmClockInfo info, _di_JPendingIntent operation) = 0 ;
	virtual void __cdecl setAndAllowWhileIdle(int type_, __int64 triggerAtMillis, _di_JPendingIntent operation) = 0 ;
	virtual void __cdecl setExact(int type_, __int64 triggerAtMillis, _di_JPendingIntent operation) = 0 /* overload */;
	virtual void __cdecl setExact(int type_, __int64 triggerAtMillis, Androidapi::Jni::Javatypes::_di_JString tag, _di_JAlarmManager_OnAlarmListener listener, Androidapi::Jni::Os::_di_JHandler targetHandler) = 0 /* overload */;
	virtual void __cdecl setExactAndAllowWhileIdle(int type_, __int64 triggerAtMillis, _di_JPendingIntent operation) = 0 ;
	virtual void __cdecl setInexactRepeating(int type_, __int64 triggerAtMillis, __int64 intervalMillis, _di_JPendingIntent operation) = 0 ;
	virtual void __cdecl setRepeating(int type_, __int64 triggerAtMillis, __int64 intervalMillis, _di_JPendingIntent operation) = 0 ;
	virtual void __cdecl setTime(__int64 millis) = 0 ;
	virtual void __cdecl setTimeZone(Androidapi::Jni::Javatypes::_di_JString timeZone) = 0 ;
	virtual void __cdecl setWindow(int type_, __int64 windowStartMillis, __int64 windowLengthMillis, _di_JPendingIntent operation) = 0 /* overload */;
	virtual void __cdecl setWindow(int type_, __int64 windowStartMillis, __int64 windowLengthMillis, Androidapi::Jni::Javatypes::_di_JString tag, _di_JAlarmManager_OnAlarmListener listener, Androidapi::Jni::Os::_di_JHandler targetHandler) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAlarmManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAlarmManagerClass,_di_JAlarmManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAlarmManagerClass,_di_JAlarmManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAlarmManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAlarmManagerClass,_di_JAlarmManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAlarmManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{39D4619E-2EDE-4B79-8BF2-C3086B93CAED}") JAlarmManager_AlarmClockInfoClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JAlarmManager_AlarmClockInfo __cdecl init(__int64 triggerTime, _di_JPendingIntent showIntent) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{8111AA00-8405-46AC-AA53-EB6B2180F109}") JAlarmManager_AlarmClockInfo  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual _di_JPendingIntent __cdecl getShowIntent() = 0 ;
	virtual __int64 __cdecl getTriggerTime() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAlarmManager_AlarmClockInfo : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAlarmManager_AlarmClockInfoClass,_di_JAlarmManager_AlarmClockInfo>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAlarmManager_AlarmClockInfoClass,_di_JAlarmManager_AlarmClockInfo> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAlarmManager_AlarmClockInfo() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAlarmManager_AlarmClockInfoClass,_di_JAlarmManager_AlarmClockInfo>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAlarmManager_AlarmClockInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9250883C-E848-4F85-A019-1698209522A6}") JAlarmManager_OnAlarmListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{77AB3FF1-DF96-4CD9-A8AA-D0922DA74926}") JAlarmManager_OnAlarmListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onAlarm() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAlarmManager_OnAlarmListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAlarmManager_OnAlarmListenerClass,_di_JAlarmManager_OnAlarmListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAlarmManager_OnAlarmListenerClass,_di_JAlarmManager_OnAlarmListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAlarmManager_OnAlarmListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAlarmManager_OnAlarmListenerClass,_di_JAlarmManager_OnAlarmListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAlarmManager_OnAlarmListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{92218268-7592-4242-B041-BE3C84FFC844}") JDialogClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JDialog __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JDialog __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int themeResId) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{71959C70-0CB3-42B3-9654-30005BAEB3F5}") JDialog  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl addContentView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_LayoutParams params) = 0 ;
	virtual void __cdecl cancel() = 0 ;
	virtual void __cdecl closeOptionsMenu() = 0 ;
	virtual void __cdecl create() = 0 ;
	virtual void __cdecl dismiss() = 0 ;
	virtual bool __cdecl dispatchGenericMotionEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent ev) = 0 ;
	virtual bool __cdecl dispatchKeyEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl dispatchKeyShortcutEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl dispatchPopulateAccessibilityEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JAccessibilityEvent event) = 0 ;
	virtual bool __cdecl dispatchTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent ev) = 0 ;
	virtual bool __cdecl dispatchTrackballEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent ev) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl findViewById(int id) = 0 ;
	virtual _di_JActionBar __cdecl getActionBar() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JContext __cdecl getContext() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getCurrentFocus() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JLayoutInflater __cdecl getLayoutInflater() = 0 ;
	virtual _di_JActivity __cdecl getOwnerActivity() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JSearchEvent __cdecl getSearchEvent() = 0 ;
	virtual int __cdecl getVolumeControlStream() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JWindow __cdecl getWindow() = 0 ;
	virtual void __cdecl hide() = 0 ;
	virtual void __cdecl invalidateOptionsMenu() = 0 ;
	virtual bool __cdecl isShowing() = 0 ;
	virtual void __cdecl onActionModeFinished(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode) = 0 ;
	virtual void __cdecl onActionModeStarted(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode) = 0 ;
	virtual void __cdecl onAttachedToWindow() = 0 ;
	virtual void __cdecl onBackPressed() = 0 ;
	virtual void __cdecl onContentChanged() = 0 ;
	virtual bool __cdecl onContextItemSelected(Androidapi::Jni::Graphicscontentviewtext::_di_JMenuItem item) = 0 ;
	virtual void __cdecl onContextMenuClosed(Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onCreateContextMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JContextMenu menu, Androidapi::Jni::Graphicscontentviewtext::_di_JView v, Androidapi::Jni::Graphicscontentviewtext::_di_JContextMenu_ContextMenuInfo menuInfo) = 0 ;
	virtual bool __cdecl onCreateOptionsMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual bool __cdecl onCreatePanelMenu(int featureId, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl onCreatePanelView(int featureId) = 0 ;
	virtual void __cdecl onDetachedFromWindow() = 0 ;
	virtual bool __cdecl onGenericMotionEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	virtual bool __cdecl onKeyDown(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl onKeyLongPress(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl onKeyMultiple(int keyCode, int repeatCount, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl onKeyShortcut(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl onKeyUp(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl onMenuItemSelected(int featureId, Androidapi::Jni::Graphicscontentviewtext::_di_JMenuItem item) = 0 ;
	virtual bool __cdecl onMenuOpened(int featureId, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual bool __cdecl onOptionsItemSelected(Androidapi::Jni::Graphicscontentviewtext::_di_JMenuItem item) = 0 ;
	virtual void __cdecl onOptionsMenuClosed(Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onPanelClosed(int featureId, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual bool __cdecl onPrepareOptionsMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual bool __cdecl onPreparePanel(int featureId, Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onRestoreInstanceState(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl onSaveInstanceState() = 0 ;
	virtual bool __cdecl onSearchRequested(Androidapi::Jni::Graphicscontentviewtext::_di_JSearchEvent searchEvent) = 0 /* overload */;
	virtual bool __cdecl onSearchRequested() = 0 /* overload */;
	virtual bool __cdecl onTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	virtual bool __cdecl onTrackballEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	virtual void __cdecl onWindowAttributesChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JWindowManager_LayoutParams params) = 0 ;
	virtual void __cdecl onWindowFocusChanged(bool hasFocus) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode __cdecl onWindowStartingActionMode(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode_Callback callback) = 0 /* overload */;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode __cdecl onWindowStartingActionMode(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode_Callback callback, int type_) = 0 /* overload */;
	virtual void __cdecl openContextMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
	virtual void __cdecl openOptionsMenu() = 0 ;
	virtual void __cdecl registerForContextMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
	virtual bool __cdecl requestWindowFeature(int featureId) = 0 ;
	virtual void __cdecl setCancelMessage(Androidapi::Jni::Os::_di_JMessage msg) = 0 ;
	virtual void __cdecl setCancelable(bool flag) = 0 ;
	virtual void __cdecl setCanceledOnTouchOutside(bool cancel) = 0 ;
	virtual void __cdecl setContentView(int layoutResID) = 0 /* overload */;
	virtual void __cdecl setContentView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 /* overload */;
	virtual void __cdecl setContentView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_LayoutParams params) = 0 /* overload */;
	virtual void __cdecl setDismissMessage(Androidapi::Jni::Os::_di_JMessage msg) = 0 ;
	virtual void __cdecl setFeatureDrawable(int featureId, Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable drawable) = 0 ;
	virtual void __cdecl setFeatureDrawableAlpha(int featureId, int alpha) = 0 ;
	virtual void __cdecl setFeatureDrawableResource(int featureId, int resId) = 0 ;
	virtual void __cdecl setOnCancelListener(Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnCancelListener listener) = 0 ;
	virtual void __cdecl setOnDismissListener(Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnDismissListener listener) = 0 ;
	virtual void __cdecl setOnKeyListener(Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnKeyListener onKeyListener) = 0 ;
	virtual void __cdecl setOnShowListener(Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnShowListener listener) = 0 ;
	virtual void __cdecl setOwnerActivity(_di_JActivity activity) = 0 ;
	virtual void __cdecl setTitle(Androidapi::Jni::Javatypes::_di_JCharSequence title) = 0 /* overload */;
	virtual void __cdecl setTitle(int titleId) = 0 /* overload */;
	virtual void __cdecl setVolumeControlStream(int streamType) = 0 ;
	virtual void __cdecl show() = 0 ;
	virtual void __cdecl takeKeyEvents(bool get_) = 0 ;
	virtual void __cdecl unregisterForContextMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDialog : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDialogClass,_di_JDialog>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDialogClass,_di_JDialog> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDialog() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDialogClass,_di_JDialog>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDialog() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{36BE871D-2AD4-4CA9-8524-C14BEB73AC56}") JAlertDialogClass  : public JDialogClass 
{
	virtual int __cdecl _GetTHEME_DEVICE_DEFAULT_DARK() = 0 ;
	virtual int __cdecl _GetTHEME_DEVICE_DEFAULT_LIGHT() = 0 ;
	virtual int __cdecl _GetTHEME_HOLO_DARK() = 0 ;
	virtual int __cdecl _GetTHEME_HOLO_LIGHT() = 0 ;
	virtual int __cdecl _GetTHEME_TRADITIONAL() = 0 ;
	__property int THEME_DEVICE_DEFAULT_DARK = {read=_GetTHEME_DEVICE_DEFAULT_DARK};
	__property int THEME_DEVICE_DEFAULT_LIGHT = {read=_GetTHEME_DEVICE_DEFAULT_LIGHT};
	__property int THEME_HOLO_DARK = {read=_GetTHEME_HOLO_DARK};
	__property int THEME_HOLO_LIGHT = {read=_GetTHEME_HOLO_LIGHT};
	__property int THEME_TRADITIONAL = {read=_GetTHEME_TRADITIONAL};
};

__interface  INTERFACE_UUID("{53DA68C7-828A-4527-8A92-1BC09462F4E2}") JAlertDialog  : public JDialog 
{
	virtual Androidapi::Jni::Widget::_di_JButton __cdecl getButton(int whichButton) = 0 ;
	virtual Androidapi::Jni::Widget::_di_JListView __cdecl getListView() = 0 ;
	HIDESBASE virtual bool __cdecl onKeyDown(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onKeyUp(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual void __cdecl setButton(int whichButton, Androidapi::Jni::Javatypes::_di_JCharSequence text, Androidapi::Jni::Os::_di_JMessage msg) = 0 /* overload */;
	virtual void __cdecl setButton(int whichButton, Androidapi::Jni::Javatypes::_di_JCharSequence text, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 /* overload */;
	virtual void __cdecl setButton(Androidapi::Jni::Javatypes::_di_JCharSequence text, Androidapi::Jni::Os::_di_JMessage msg) = 0 /* overload */;
	virtual void __cdecl setButton(Androidapi::Jni::Javatypes::_di_JCharSequence text, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 /* overload */;
	virtual void __cdecl setButton2(Androidapi::Jni::Javatypes::_di_JCharSequence text, Androidapi::Jni::Os::_di_JMessage msg) = 0 /* overload */;
	virtual void __cdecl setButton2(Androidapi::Jni::Javatypes::_di_JCharSequence text, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 /* overload */;
	virtual void __cdecl setButton3(Androidapi::Jni::Javatypes::_di_JCharSequence text, Androidapi::Jni::Os::_di_JMessage msg) = 0 /* overload */;
	virtual void __cdecl setButton3(Androidapi::Jni::Javatypes::_di_JCharSequence text, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 /* overload */;
	virtual void __cdecl setCustomTitle(Androidapi::Jni::Graphicscontentviewtext::_di_JView customTitleView) = 0 ;
	virtual void __cdecl setIcon(int resId) = 0 /* overload */;
	virtual void __cdecl setIcon(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable icon) = 0 /* overload */;
	virtual void __cdecl setIconAttribute(int attrId) = 0 ;
	virtual void __cdecl setInverseBackgroundForced(bool forceInverseBackground) = 0 ;
	virtual void __cdecl setMessage(Androidapi::Jni::Javatypes::_di_JCharSequence message) = 0 ;
	HIDESBASE virtual void __cdecl setTitle(Androidapi::Jni::Javatypes::_di_JCharSequence title) = 0 ;
	virtual void __cdecl setView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 /* overload */;
	virtual void __cdecl setView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, int viewSpacingLeft, int viewSpacingTop, int viewSpacingRight, int viewSpacingBottom) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAlertDialog : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAlertDialogClass,_di_JAlertDialog>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAlertDialogClass,_di_JAlertDialog> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAlertDialog() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAlertDialogClass,_di_JAlertDialog>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAlertDialog() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{69C77054-20E9-4492-BCBB-FB1F9F062BFD}") JAlertDialog_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JAlertDialog_Builder __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JAlertDialog_Builder __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int themeResId) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{25BC41E2-CA0A-4EA8-A854-993A0E86087C}") JAlertDialog_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JAlertDialog __cdecl create() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JContext __cdecl getContext() = 0 ;
	virtual _di_JAlertDialog_Builder __cdecl setAdapter(Androidapi::Jni::Widget::_di_JListAdapter adapter, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 ;
	virtual _di_JAlertDialog_Builder __cdecl setCancelable(bool cancelable) = 0 ;
	virtual _di_JAlertDialog_Builder __cdecl setCursor(Androidapi::Jni::Graphicscontentviewtext::_di_JCursor cursor, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener, Androidapi::Jni::Javatypes::_di_JString labelColumn) = 0 ;
	virtual _di_JAlertDialog_Builder __cdecl setCustomTitle(Androidapi::Jni::Graphicscontentviewtext::_di_JView customTitleView) = 0 ;
	virtual _di_JAlertDialog_Builder __cdecl setIcon(int iconId) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setIcon(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable icon) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setIconAttribute(int attrId) = 0 ;
	virtual _di_JAlertDialog_Builder __cdecl setInverseBackgroundForced(bool useInverseBackground) = 0 ;
	virtual _di_JAlertDialog_Builder __cdecl setItems(int itemsId, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setItems(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JCharSequence>* items, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setMessage(int messageId) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setMessage(Androidapi::Jni::Javatypes::_di_JCharSequence message) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setMultiChoiceItems(int itemsId, Androidapi::Jnibridge::TJavaArray__1<bool>* checkedItems, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnMultiChoiceClickListener listener) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setMultiChoiceItems(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JCharSequence>* items, Androidapi::Jnibridge::TJavaArray__1<bool>* checkedItems, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnMultiChoiceClickListener listener) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setMultiChoiceItems(Androidapi::Jni::Graphicscontentviewtext::_di_JCursor cursor, Androidapi::Jni::Javatypes::_di_JString isCheckedColumn, Androidapi::Jni::Javatypes::_di_JString labelColumn, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnMultiChoiceClickListener listener) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setNegativeButton(int textId, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setNegativeButton(Androidapi::Jni::Javatypes::_di_JCharSequence text, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setNeutralButton(int textId, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setNeutralButton(Androidapi::Jni::Javatypes::_di_JCharSequence text, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setOnCancelListener(Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnCancelListener onCancelListener) = 0 ;
	virtual _di_JAlertDialog_Builder __cdecl setOnDismissListener(Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnDismissListener onDismissListener) = 0 ;
	virtual _di_JAlertDialog_Builder __cdecl setOnItemSelectedListener(Androidapi::Jni::Widget::_di_JAdapterView_OnItemSelectedListener listener) = 0 ;
	virtual _di_JAlertDialog_Builder __cdecl setOnKeyListener(Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnKeyListener onKeyListener) = 0 ;
	virtual _di_JAlertDialog_Builder __cdecl setPositiveButton(int textId, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setPositiveButton(Androidapi::Jni::Javatypes::_di_JCharSequence text, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setSingleChoiceItems(int itemsId, int checkedItem, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setSingleChoiceItems(Androidapi::Jni::Graphicscontentviewtext::_di_JCursor cursor, int checkedItem, Androidapi::Jni::Javatypes::_di_JString labelColumn, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setSingleChoiceItems(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JCharSequence>* items, int checkedItem, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setSingleChoiceItems(Androidapi::Jni::Widget::_di_JListAdapter adapter, int checkedItem, Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface_OnClickListener listener) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setTitle(int titleId) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setTitle(Androidapi::Jni::Javatypes::_di_JCharSequence title) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setView(int layoutResId) = 0 /* overload */;
	virtual _di_JAlertDialog_Builder __cdecl setView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 /* overload */;
	virtual _di_JAlertDialog __cdecl show() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAlertDialog_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAlertDialog_BuilderClass,_di_JAlertDialog_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAlertDialog_BuilderClass,_di_JAlertDialog_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAlertDialog_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAlertDialog_BuilderClass,_di_JAlertDialog_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAlertDialog_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B2E72B31-70E4-4B3A-A067-F11C002F8275}") JApplicationClass  : public Androidapi::Jni::Graphicscontentviewtext::JContextWrapperClass 
{
	HIDESBASE virtual _di_JApplication __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{28FC188F-36BA-4C06-843B-22F715AC831D}") JApplication  : public Androidapi::Jni::Graphicscontentviewtext::JContextWrapper 
{
	virtual void __cdecl onConfigurationChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JConfiguration newConfig) = 0 ;
	virtual void __cdecl onCreate() = 0 ;
	virtual void __cdecl onLowMemory() = 0 ;
	virtual void __cdecl onTerminate() = 0 ;
	virtual void __cdecl onTrimMemory(int level) = 0 ;
	virtual void __cdecl registerActivityLifecycleCallbacks(_di_JApplication_ActivityLifecycleCallbacks callback) = 0 ;
	HIDESBASE virtual void __cdecl registerComponentCallbacks(Androidapi::Jni::Graphicscontentviewtext::_di_JComponentCallbacks callback) = 0 ;
	virtual void __cdecl registerOnProvideAssistDataListener(_di_JApplication_OnProvideAssistDataListener callback) = 0 ;
	virtual void __cdecl unregisterActivityLifecycleCallbacks(_di_JApplication_ActivityLifecycleCallbacks callback) = 0 ;
	HIDESBASE virtual void __cdecl unregisterComponentCallbacks(Androidapi::Jni::Graphicscontentviewtext::_di_JComponentCallbacks callback) = 0 ;
	virtual void __cdecl unregisterOnProvideAssistDataListener(_di_JApplication_OnProvideAssistDataListener callback) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJApplication : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApplicationClass,_di_JApplication>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApplicationClass,_di_JApplication> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJApplication() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApplicationClass,_di_JApplication>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJApplication() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{82C4F2D1-0E03-4C87-940A-E2EE997EAC0C}") JApplication_ActivityLifecycleCallbacksClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{45381B4E-F44D-4BB9-883F-CB7DC2EC4AE3}") JApplication_ActivityLifecycleCallbacks  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onActivityCreated(_di_JActivity activity, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onActivityDestroyed(_di_JActivity activity) = 0 ;
	virtual void __cdecl onActivityPaused(_di_JActivity activity) = 0 ;
	virtual void __cdecl onActivityResumed(_di_JActivity activity) = 0 ;
	virtual void __cdecl onActivitySaveInstanceState(_di_JActivity activity, Androidapi::Jni::Os::_di_JBundle outState) = 0 ;
	virtual void __cdecl onActivityStarted(_di_JActivity activity) = 0 ;
	virtual void __cdecl onActivityStopped(_di_JActivity activity) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJApplication_ActivityLifecycleCallbacks : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApplication_ActivityLifecycleCallbacksClass,_di_JApplication_ActivityLifecycleCallbacks>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApplication_ActivityLifecycleCallbacksClass,_di_JApplication_ActivityLifecycleCallbacks> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJApplication_ActivityLifecycleCallbacks() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApplication_ActivityLifecycleCallbacksClass,_di_JApplication_ActivityLifecycleCallbacks>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJApplication_ActivityLifecycleCallbacks() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E7660DEF-A22F-4C70-AB39-F3B68B072D1A}") JApplication_OnProvideAssistDataListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{53921961-9D0B-4BF4-A841-C690812FADDC}") JApplication_OnProvideAssistDataListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onProvideAssistData(_di_JActivity activity, Androidapi::Jni::Os::_di_JBundle data) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJApplication_OnProvideAssistDataListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApplication_OnProvideAssistDataListenerClass,_di_JApplication_OnProvideAssistDataListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApplication_OnProvideAssistDataListenerClass,_di_JApplication_OnProvideAssistDataListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJApplication_OnProvideAssistDataListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApplication_OnProvideAssistDataListenerClass,_di_JApplication_OnProvideAssistDataListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJApplication_OnProvideAssistDataListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6F7058E7-BAD7-40DC-91FA-A5FEC86F8BED}") JAutomaticZenRuleClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JAutomaticZenRule __cdecl init(Androidapi::Jni::Os::_di_JParcel source) = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{8D31FD86-EC63-4902-9D99-2078956CA676}") JAutomaticZenRule  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	virtual __int64 __cdecl getCreationTime() = 0 ;
	virtual int __cdecl getInterruptionFilter() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName __cdecl getOwner() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isEnabled() = 0 ;
	virtual void __cdecl setEnabled(bool enabled) = 0 ;
	virtual void __cdecl setInterruptionFilter(int interruptionFilter) = 0 ;
	virtual void __cdecl setName(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAutomaticZenRule : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAutomaticZenRuleClass,_di_JAutomaticZenRule>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAutomaticZenRuleClass,_di_JAutomaticZenRule> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAutomaticZenRule() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAutomaticZenRuleClass,_di_JAutomaticZenRule>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAutomaticZenRule() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3C54B094-6ECA-4E7F-9A49-E8B77FE2B156}") JFragmentClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JFragment __cdecl init() = 0 ;
	virtual _di_JFragment __cdecl instantiate(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString fname) = 0 /* overload */;
	virtual _di_JFragment __cdecl instantiate(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString fname, Androidapi::Jni::Os::_di_JBundle args) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{A17DB3FE-8968-475D-988E-0CB75BE207CF}") JFragment  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl dump(Androidapi::Jni::Javatypes::_di_JString prefix, Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, Androidapi::Jni::Javatypes::_di_JPrintWriter writer, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* args) = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	virtual _di_JActivity __cdecl getActivity() = 0 ;
	virtual bool __cdecl getAllowEnterTransitionOverlap() = 0 ;
	virtual bool __cdecl getAllowReturnTransitionOverlap() = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getArguments() = 0 ;
	virtual _di_JFragmentManager __cdecl getChildFragmentManager() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JContext __cdecl getContext() = 0 ;
	virtual _di_JFragmentManager __cdecl getFragmentManager() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getHost() = 0 ;
	virtual int __cdecl getId() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JLayoutInflater __cdecl getLayoutInflater() = 0 ;
	virtual _di_JLoaderManager __cdecl getLoaderManager() = 0 ;
	virtual _di_JFragment __cdecl getParentFragment() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JResources __cdecl getResources() = 0 ;
	virtual bool __cdecl getRetainInstance() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getString(int resId) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getTag() = 0 ;
	virtual _di_JFragment __cdecl getTargetFragment() = 0 ;
	virtual int __cdecl getTargetRequestCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getText(int resId) = 0 ;
	virtual bool __cdecl getUserVisibleHint() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getView() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isAdded() = 0 ;
	virtual bool __cdecl isDetached() = 0 ;
	virtual bool __cdecl isHidden() = 0 ;
	virtual bool __cdecl isInLayout() = 0 ;
	virtual bool __cdecl isRemoving() = 0 ;
	virtual bool __cdecl isResumed() = 0 ;
	virtual bool __cdecl isStateSaved() = 0 ;
	virtual bool __cdecl isVisible() = 0 ;
	virtual void __cdecl onActivityCreated(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onActivityResult(int requestCode, int resultCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent data) = 0 ;
	virtual void __cdecl onAttach(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	virtual void __cdecl onAttach(_di_JActivity activity) = 0 /* overload */;
	virtual void __cdecl onAttachFragment(_di_JFragment childFragment) = 0 ;
	virtual void __cdecl onConfigurationChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JConfiguration newConfig) = 0 ;
	virtual bool __cdecl onContextItemSelected(Androidapi::Jni::Graphicscontentviewtext::_di_JMenuItem item) = 0 ;
	virtual void __cdecl onCreate(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onCreateContextMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JContextMenu menu, Androidapi::Jni::Graphicscontentviewtext::_di_JView v, Androidapi::Jni::Graphicscontentviewtext::_di_JContextMenu_ContextMenuInfo menuInfo) = 0 ;
	virtual void __cdecl onCreateOptionsMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu, Androidapi::Jni::Graphicscontentviewtext::_di_JMenuInflater inflater) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl onCreateView(Androidapi::Jni::Graphicscontentviewtext::_di_JLayoutInflater inflater, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup container, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onDestroy() = 0 ;
	virtual void __cdecl onDestroyOptionsMenu() = 0 ;
	virtual void __cdecl onDestroyView() = 0 ;
	virtual void __cdecl onDetach() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JLayoutInflater __cdecl onGetLayoutInflater(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onHiddenChanged(bool hidden) = 0 ;
	virtual void __cdecl onInflate(Androidapi::Jni::Util::_di_JAttributeSet attrs, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 /* overload */;
	virtual void __cdecl onInflate(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 /* overload */;
	virtual void __cdecl onInflate(_di_JActivity activity, Androidapi::Jni::Util::_di_JAttributeSet attrs, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 /* overload */;
	virtual void __cdecl onLowMemory() = 0 ;
	virtual void __cdecl onMultiWindowModeChanged(bool isInMultiWindowMode, Androidapi::Jni::Graphicscontentviewtext::_di_JConfiguration newConfig) = 0 /* overload */;
	virtual void __cdecl onMultiWindowModeChanged(bool isInMultiWindowMode) = 0 /* overload */;
	virtual bool __cdecl onOptionsItemSelected(Androidapi::Jni::Graphicscontentviewtext::_di_JMenuItem item) = 0 ;
	virtual void __cdecl onOptionsMenuClosed(Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onPause() = 0 ;
	virtual void __cdecl onPictureInPictureModeChanged(bool isInPictureInPictureMode, Androidapi::Jni::Graphicscontentviewtext::_di_JConfiguration newConfig) = 0 /* overload */;
	virtual void __cdecl onPictureInPictureModeChanged(bool isInPictureInPictureMode) = 0 /* overload */;
	virtual void __cdecl onPrepareOptionsMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onRequestPermissionsResult(int requestCode, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* permissions, Androidapi::Jnibridge::TJavaArray__1<int>* grantResults) = 0 ;
	virtual void __cdecl onResume() = 0 ;
	virtual void __cdecl onSaveInstanceState(Androidapi::Jni::Os::_di_JBundle outState) = 0 ;
	virtual void __cdecl onStart() = 0 ;
	virtual void __cdecl onStop() = 0 ;
	virtual void __cdecl onTrimMemory(int level) = 0 ;
	virtual void __cdecl onViewCreated(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onViewStateRestored(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl postponeEnterTransition() = 0 ;
	virtual void __cdecl registerForContextMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
	virtual void __cdecl requestPermissions(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* permissions, int requestCode) = 0 ;
	virtual void __cdecl setAllowEnterTransitionOverlap(bool allow) = 0 ;
	virtual void __cdecl setAllowReturnTransitionOverlap(bool allow) = 0 ;
	virtual void __cdecl setArguments(Androidapi::Jni::Os::_di_JBundle args) = 0 ;
	virtual void __cdecl setEnterSharedElementCallback(_di_JSharedElementCallback callback) = 0 ;
	virtual void __cdecl setExitSharedElementCallback(_di_JSharedElementCallback callback) = 0 ;
	virtual void __cdecl setHasOptionsMenu(bool hasMenu) = 0 ;
	virtual void __cdecl setInitialSavedState(_di_JFragment_SavedState state) = 0 ;
	virtual void __cdecl setMenuVisibility(bool menuVisible) = 0 ;
	virtual void __cdecl setRetainInstance(bool retain) = 0 ;
	virtual void __cdecl setTargetFragment(_di_JFragment fragment, int requestCode) = 0 ;
	virtual void __cdecl setUserVisibleHint(bool isVisibleToUser) = 0 ;
	virtual bool __cdecl shouldShowRequestPermissionRationale(Androidapi::Jni::Javatypes::_di_JString permission) = 0 ;
	virtual void __cdecl startActivity(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 /* overload */;
	virtual void __cdecl startActivity(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual void __cdecl startActivityForResult(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int requestCode) = 0 /* overload */;
	virtual void __cdecl startActivityForResult(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int requestCode, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual void __cdecl startIntentSenderForResult(Androidapi::Jni::Graphicscontentviewtext::_di_JIntentSender intent, int requestCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent fillInIntent, int flagsMask, int flagsValues, int extraFlags, Androidapi::Jni::Os::_di_JBundle options) = 0 ;
	virtual void __cdecl startPostponedEnterTransition() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl unregisterForContextMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFragment : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentClass,_di_JFragment>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentClass,_di_JFragment> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFragment() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentClass,_di_JFragment>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFragment() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0BA4C933-9BC4-4D8B-9757-C02740EBC511}") JDialogFragmentClass  : public JFragmentClass 
{
	virtual int __cdecl _GetSTYLE_NORMAL() = 0 ;
	virtual int __cdecl _GetSTYLE_NO_FRAME() = 0 ;
	virtual int __cdecl _GetSTYLE_NO_INPUT() = 0 ;
	virtual int __cdecl _GetSTYLE_NO_TITLE() = 0 ;
	HIDESBASE virtual _di_JDialogFragment __cdecl init() = 0 ;
	__property int STYLE_NORMAL = {read=_GetSTYLE_NORMAL};
	__property int STYLE_NO_FRAME = {read=_GetSTYLE_NO_FRAME};
	__property int STYLE_NO_INPUT = {read=_GetSTYLE_NO_INPUT};
	__property int STYLE_NO_TITLE = {read=_GetSTYLE_NO_TITLE};
};

__interface  INTERFACE_UUID("{D5B8C228-5BCF-43DF-B26A-18A3EB4C893E}") JDialogFragment  : public JFragment 
{
	virtual void __cdecl dismiss() = 0 ;
	virtual void __cdecl dismissAllowingStateLoss() = 0 ;
	HIDESBASE virtual void __cdecl dump(Androidapi::Jni::Javatypes::_di_JString prefix, Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, Androidapi::Jni::Javatypes::_di_JPrintWriter writer, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* args) = 0 ;
	virtual _di_JDialog __cdecl getDialog() = 0 ;
	virtual bool __cdecl getShowsDialog() = 0 ;
	virtual int __cdecl getTheme() = 0 ;
	virtual bool __cdecl isCancelable() = 0 ;
	HIDESBASE virtual void __cdecl onActivityCreated(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	HIDESBASE virtual void __cdecl onAttach(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual void __cdecl onCancel(Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface dialog) = 0 ;
	HIDESBASE virtual void __cdecl onCreate(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual _di_JDialog __cdecl onCreateDialog(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	HIDESBASE virtual void __cdecl onDestroyView() = 0 ;
	HIDESBASE virtual void __cdecl onDetach() = 0 ;
	virtual void __cdecl onDismiss(Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface dialog) = 0 ;
	HIDESBASE virtual void __cdecl onSaveInstanceState(Androidapi::Jni::Os::_di_JBundle outState) = 0 ;
	HIDESBASE virtual void __cdecl onStart() = 0 ;
	HIDESBASE virtual void __cdecl onStop() = 0 ;
	virtual void __cdecl setCancelable(bool cancelable) = 0 ;
	virtual void __cdecl setShowsDialog(bool showsDialog) = 0 ;
	virtual void __cdecl setStyle(int style, int theme) = 0 ;
	virtual void __cdecl show(_di_JFragmentManager manager, Androidapi::Jni::Javatypes::_di_JString tag) = 0 /* overload */;
	virtual int __cdecl show(_di_JFragmentTransaction transaction, Androidapi::Jni::Javatypes::_di_JString tag) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDialogFragment : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDialogFragmentClass,_di_JDialogFragment>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDialogFragmentClass,_di_JDialogFragment> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDialogFragment() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDialogFragmentClass,_di_JDialogFragment>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDialogFragment() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5BA60ED2-A67D-4A23-8B92-E4F26A4799D9}") JFragment_SavedStateClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_ClassLoaderCreator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_ClassLoaderCreator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{76BE11A9-82B9-4AC9-8C54-80BAFBD3A578}") JFragment_SavedState  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFragment_SavedState : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragment_SavedStateClass,_di_JFragment_SavedState>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragment_SavedStateClass,_di_JFragment_SavedState> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFragment_SavedState() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragment_SavedStateClass,_di_JFragment_SavedState>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFragment_SavedState() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AF70B1C7-BC2A-4F71-83F4-BCB987DC7F04}") JFragmentManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetPOP_BACK_STACK_INCLUSIVE() = 0 ;
	HIDESBASE virtual _di_JFragmentManager __cdecl init() = 0 ;
	virtual void __cdecl enableDebugLogging(bool enabled) = 0 ;
	__property int POP_BACK_STACK_INCLUSIVE = {read=_GetPOP_BACK_STACK_INCLUSIVE};
};

__interface  INTERFACE_UUID("{4B06A33C-C4AF-4BE8-82E2-82E3B8BCBFCF}") JFragmentManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl addOnBackStackChangedListener(_di_JFragmentManager_OnBackStackChangedListener listener) = 0 ;
	virtual _di_JFragmentTransaction __cdecl beginTransaction() = 0 ;
	virtual void __cdecl dump(Androidapi::Jni::Javatypes::_di_JString prefix, Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, Androidapi::Jni::Javatypes::_di_JPrintWriter writer, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* args) = 0 ;
	virtual bool __cdecl executePendingTransactions() = 0 ;
	virtual _di_JFragment __cdecl findFragmentById(int id) = 0 ;
	virtual _di_JFragment __cdecl findFragmentByTag(Androidapi::Jni::Javatypes::_di_JString tag) = 0 ;
	virtual _di_JFragmentManager_BackStackEntry __cdecl getBackStackEntryAt(int index) = 0 ;
	virtual int __cdecl getBackStackEntryCount() = 0 ;
	virtual _di_JFragment __cdecl getFragment(Androidapi::Jni::Os::_di_JBundle bundle, Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getFragments() = 0 ;
	virtual _di_JFragment __cdecl getPrimaryNavigationFragment() = 0 ;
	virtual void __cdecl invalidateOptionsMenu() = 0 ;
	virtual bool __cdecl isDestroyed() = 0 ;
	virtual bool __cdecl isStateSaved() = 0 ;
	virtual void __cdecl popBackStack() = 0 /* overload */;
	virtual void __cdecl popBackStack(Androidapi::Jni::Javatypes::_di_JString name, int flags) = 0 /* overload */;
	virtual void __cdecl popBackStack(int id, int flags) = 0 /* overload */;
	virtual bool __cdecl popBackStackImmediate() = 0 /* overload */;
	virtual bool __cdecl popBackStackImmediate(Androidapi::Jni::Javatypes::_di_JString name, int flags) = 0 /* overload */;
	virtual bool __cdecl popBackStackImmediate(int id, int flags) = 0 /* overload */;
	virtual void __cdecl putFragment(Androidapi::Jni::Os::_di_JBundle bundle, Androidapi::Jni::Javatypes::_di_JString key, _di_JFragment fragment) = 0 ;
	virtual void __cdecl registerFragmentLifecycleCallbacks(_di_JFragmentManager_FragmentLifecycleCallbacks cb, bool recursive) = 0 ;
	virtual void __cdecl removeOnBackStackChangedListener(_di_JFragmentManager_OnBackStackChangedListener listener) = 0 ;
	virtual _di_JFragment_SavedState __cdecl saveFragmentInstanceState(_di_JFragment f) = 0 ;
	virtual void __cdecl unregisterFragmentLifecycleCallbacks(_di_JFragmentManager_FragmentLifecycleCallbacks cb) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFragmentManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentManagerClass,_di_JFragmentManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentManagerClass,_di_JFragmentManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFragmentManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentManagerClass,_di_JFragmentManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFragmentManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8B736CA5-FB98-4A84-8BDE-7A43FEE35224}") JFragmentManager_BackStackEntryClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{F5CD98DC-3473-4D0E-B189-93124ABAFDCD}") JFragmentManager_BackStackEntry  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getBreadCrumbShortTitle() = 0 ;
	virtual int __cdecl getBreadCrumbShortTitleRes() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getBreadCrumbTitle() = 0 ;
	virtual int __cdecl getBreadCrumbTitleRes() = 0 ;
	virtual int __cdecl getId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFragmentManager_BackStackEntry : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentManager_BackStackEntryClass,_di_JFragmentManager_BackStackEntry>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentManager_BackStackEntryClass,_di_JFragmentManager_BackStackEntry> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFragmentManager_BackStackEntry() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentManager_BackStackEntryClass,_di_JFragmentManager_BackStackEntry>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFragmentManager_BackStackEntry() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D8A87D2A-B9E9-4E27-8F33-8FA717AD2EC7}") JFragmentManager_FragmentLifecycleCallbacksClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JFragmentManager_FragmentLifecycleCallbacks __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{FEEF51BF-5BBA-4592-9DC6-E5A739296FEE}") JFragmentManager_FragmentLifecycleCallbacks  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onFragmentActivityCreated(_di_JFragmentManager fm, _di_JFragment f, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onFragmentAttached(_di_JFragmentManager fm, _di_JFragment f, Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual void __cdecl onFragmentCreated(_di_JFragmentManager fm, _di_JFragment f, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onFragmentDestroyed(_di_JFragmentManager fm, _di_JFragment f) = 0 ;
	virtual void __cdecl onFragmentDetached(_di_JFragmentManager fm, _di_JFragment f) = 0 ;
	virtual void __cdecl onFragmentPaused(_di_JFragmentManager fm, _di_JFragment f) = 0 ;
	virtual void __cdecl onFragmentPreAttached(_di_JFragmentManager fm, _di_JFragment f, Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual void __cdecl onFragmentPreCreated(_di_JFragmentManager fm, _di_JFragment f, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onFragmentResumed(_di_JFragmentManager fm, _di_JFragment f) = 0 ;
	virtual void __cdecl onFragmentSaveInstanceState(_di_JFragmentManager fm, _di_JFragment f, Androidapi::Jni::Os::_di_JBundle outState) = 0 ;
	virtual void __cdecl onFragmentStarted(_di_JFragmentManager fm, _di_JFragment f) = 0 ;
	virtual void __cdecl onFragmentStopped(_di_JFragmentManager fm, _di_JFragment f) = 0 ;
	virtual void __cdecl onFragmentViewCreated(_di_JFragmentManager fm, _di_JFragment f, Androidapi::Jni::Graphicscontentviewtext::_di_JView v, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onFragmentViewDestroyed(_di_JFragmentManager fm, _di_JFragment f) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFragmentManager_FragmentLifecycleCallbacks : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentManager_FragmentLifecycleCallbacksClass,_di_JFragmentManager_FragmentLifecycleCallbacks>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentManager_FragmentLifecycleCallbacksClass,_di_JFragmentManager_FragmentLifecycleCallbacks> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFragmentManager_FragmentLifecycleCallbacks() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentManager_FragmentLifecycleCallbacksClass,_di_JFragmentManager_FragmentLifecycleCallbacks>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFragmentManager_FragmentLifecycleCallbacks() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7255BA0C-3B6C-4C55-B7EB-50A193BC8186}") JFragmentManager_OnBackStackChangedListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{B3418C11-9DEC-46E8-B17D-262F80649BC8}") JFragmentManager_OnBackStackChangedListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onBackStackChanged() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFragmentManager_OnBackStackChangedListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentManager_OnBackStackChangedListenerClass,_di_JFragmentManager_OnBackStackChangedListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentManager_OnBackStackChangedListenerClass,_di_JFragmentManager_OnBackStackChangedListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFragmentManager_OnBackStackChangedListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentManager_OnBackStackChangedListenerClass,_di_JFragmentManager_OnBackStackChangedListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFragmentManager_OnBackStackChangedListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F09CC327-C48D-46CD-AE7A-4E7036F3C90E}") JFragmentTransactionClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetTRANSIT_ENTER_MASK() = 0 ;
	virtual int __cdecl _GetTRANSIT_EXIT_MASK() = 0 ;
	virtual int __cdecl _GetTRANSIT_FRAGMENT_CLOSE() = 0 ;
	virtual int __cdecl _GetTRANSIT_FRAGMENT_FADE() = 0 ;
	virtual int __cdecl _GetTRANSIT_FRAGMENT_OPEN() = 0 ;
	virtual int __cdecl _GetTRANSIT_NONE() = 0 ;
	virtual int __cdecl _GetTRANSIT_UNSET() = 0 ;
	HIDESBASE virtual _di_JFragmentTransaction __cdecl init() = 0 ;
	__property int TRANSIT_ENTER_MASK = {read=_GetTRANSIT_ENTER_MASK};
	__property int TRANSIT_EXIT_MASK = {read=_GetTRANSIT_EXIT_MASK};
	__property int TRANSIT_FRAGMENT_CLOSE = {read=_GetTRANSIT_FRAGMENT_CLOSE};
	__property int TRANSIT_FRAGMENT_FADE = {read=_GetTRANSIT_FRAGMENT_FADE};
	__property int TRANSIT_FRAGMENT_OPEN = {read=_GetTRANSIT_FRAGMENT_OPEN};
	__property int TRANSIT_NONE = {read=_GetTRANSIT_NONE};
	__property int TRANSIT_UNSET = {read=_GetTRANSIT_UNSET};
};

__interface  INTERFACE_UUID("{A55DB157-F3A6-4F55-AD4C-6BC7A21C6FD8}") JFragmentTransaction  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JFragmentTransaction __cdecl add(_di_JFragment fragment, Androidapi::Jni::Javatypes::_di_JString tag) = 0 /* overload */;
	virtual _di_JFragmentTransaction __cdecl add(int containerViewId, _di_JFragment fragment) = 0 /* overload */;
	virtual _di_JFragmentTransaction __cdecl add(int containerViewId, _di_JFragment fragment, Androidapi::Jni::Javatypes::_di_JString tag) = 0 /* overload */;
	virtual _di_JFragmentTransaction __cdecl addSharedElement(Androidapi::Jni::Graphicscontentviewtext::_di_JView sharedElement, Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual _di_JFragmentTransaction __cdecl addToBackStack(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual _di_JFragmentTransaction __cdecl attach(_di_JFragment fragment) = 0 ;
	virtual int __cdecl commit() = 0 ;
	virtual int __cdecl commitAllowingStateLoss() = 0 ;
	virtual void __cdecl commitNow() = 0 ;
	virtual void __cdecl commitNowAllowingStateLoss() = 0 ;
	virtual _di_JFragmentTransaction __cdecl detach(_di_JFragment fragment) = 0 ;
	virtual _di_JFragmentTransaction __cdecl disallowAddToBackStack() = 0 ;
	virtual _di_JFragmentTransaction __cdecl hide(_di_JFragment fragment) = 0 ;
	virtual bool __cdecl isAddToBackStackAllowed() = 0 ;
	virtual bool __cdecl isEmpty() = 0 ;
	virtual _di_JFragmentTransaction __cdecl remove(_di_JFragment fragment) = 0 ;
	virtual _di_JFragmentTransaction __cdecl replace(int containerViewId, _di_JFragment fragment) = 0 /* overload */;
	virtual _di_JFragmentTransaction __cdecl replace(int containerViewId, _di_JFragment fragment, Androidapi::Jni::Javatypes::_di_JString tag) = 0 /* overload */;
	virtual _di_JFragmentTransaction __cdecl runOnCommit(Androidapi::Jni::Javatypes::_di_JRunnable runnable) = 0 ;
	virtual _di_JFragmentTransaction __cdecl setBreadCrumbShortTitle(int res) = 0 /* overload */;
	virtual _di_JFragmentTransaction __cdecl setBreadCrumbShortTitle(Androidapi::Jni::Javatypes::_di_JCharSequence text) = 0 /* overload */;
	virtual _di_JFragmentTransaction __cdecl setBreadCrumbTitle(int res) = 0 /* overload */;
	virtual _di_JFragmentTransaction __cdecl setBreadCrumbTitle(Androidapi::Jni::Javatypes::_di_JCharSequence text) = 0 /* overload */;
	virtual _di_JFragmentTransaction __cdecl setCustomAnimations(int enter, int exit) = 0 /* overload */;
	virtual _di_JFragmentTransaction __cdecl setCustomAnimations(int enter, int exit, int popEnter, int popExit) = 0 /* overload */;
	virtual _di_JFragmentTransaction __cdecl setPrimaryNavigationFragment(_di_JFragment fragment) = 0 ;
	virtual _di_JFragmentTransaction __cdecl setReorderingAllowed(bool reorderingAllowed) = 0 ;
	virtual _di_JFragmentTransaction __cdecl setTransition(int transit) = 0 ;
	virtual _di_JFragmentTransaction __cdecl setTransitionStyle(int styleRes) = 0 ;
	virtual _di_JFragmentTransaction __cdecl show(_di_JFragment fragment) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFragmentTransaction : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentTransactionClass,_di_JFragmentTransaction>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentTransactionClass,_di_JFragmentTransaction> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFragmentTransaction() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFragmentTransactionClass,_di_JFragmentTransaction>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFragmentTransaction() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{50459866-E20A-4564-B22B-9A8AB2716406}") JServiceClass  : public Androidapi::Jni::Graphicscontentviewtext::JContextWrapperClass 
{
	virtual int __cdecl _GetSTART_CONTINUATION_MASK() = 0 ;
	virtual int __cdecl _GetSTART_FLAG_REDELIVERY() = 0 ;
	virtual int __cdecl _GetSTART_FLAG_RETRY() = 0 ;
	virtual int __cdecl _GetSTART_NOT_STICKY() = 0 ;
	virtual int __cdecl _GetSTART_REDELIVER_INTENT() = 0 ;
	virtual int __cdecl _GetSTART_STICKY() = 0 ;
	virtual int __cdecl _GetSTART_STICKY_COMPATIBILITY() = 0 ;
	virtual int __cdecl _GetSTOP_FOREGROUND_DETACH() = 0 ;
	virtual int __cdecl _GetSTOP_FOREGROUND_REMOVE() = 0 ;
	HIDESBASE virtual _di_JService __cdecl init() = 0 ;
	__property int START_CONTINUATION_MASK = {read=_GetSTART_CONTINUATION_MASK};
	__property int START_FLAG_REDELIVERY = {read=_GetSTART_FLAG_REDELIVERY};
	__property int START_FLAG_RETRY = {read=_GetSTART_FLAG_RETRY};
	__property int START_NOT_STICKY = {read=_GetSTART_NOT_STICKY};
	__property int START_REDELIVER_INTENT = {read=_GetSTART_REDELIVER_INTENT};
	__property int START_STICKY = {read=_GetSTART_STICKY};
	__property int START_STICKY_COMPATIBILITY = {read=_GetSTART_STICKY_COMPATIBILITY};
	__property int STOP_FOREGROUND_DETACH = {read=_GetSTOP_FOREGROUND_DETACH};
	__property int STOP_FOREGROUND_REMOVE = {read=_GetSTOP_FOREGROUND_REMOVE};
};

__interface  INTERFACE_UUID("{C1C969BF-8725-4920-9691-4981E4892C1F}") JService  : public Androidapi::Jni::Graphicscontentviewtext::JContextWrapper 
{
	virtual _di_JApplication __cdecl getApplication() = 0 ;
	virtual Androidapi::Jni::Os::_di_JIBinder __cdecl onBind(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual void __cdecl onConfigurationChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JConfiguration newConfig) = 0 ;
	virtual void __cdecl onCreate() = 0 ;
	virtual void __cdecl onDestroy() = 0 ;
	virtual void __cdecl onLowMemory() = 0 ;
	virtual void __cdecl onRebind(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual void __cdecl onStart(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int startId) = 0 ;
	virtual int __cdecl onStartCommand(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int flags, int startId) = 0 ;
	virtual void __cdecl onTaskRemoved(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent rootIntent) = 0 ;
	virtual void __cdecl onTrimMemory(int level) = 0 ;
	virtual bool __cdecl onUnbind(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual void __cdecl startForeground(int id, _di_JNotification notification) = 0 ;
	virtual void __cdecl stopForeground(bool removeNotification) = 0 /* overload */;
	virtual void __cdecl stopForeground(int flags) = 0 /* overload */;
	virtual void __cdecl stopSelf() = 0 /* overload */;
	virtual void __cdecl stopSelf(int startId) = 0 /* overload */;
	virtual bool __cdecl stopSelfResult(int startId) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceClass,_di_JService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceClass,_di_JService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceClass,_di_JService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{46298ACB-D39D-4C26-B9BB-90888D68848F}") JIntentServiceClass  : public JServiceClass 
{
	HIDESBASE virtual _di_JIntentService __cdecl init(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
};

__interface  INTERFACE_UUID("{E5F9EDF4-5A96-49F9-A1FF-F69868B5946D}") JIntentService  : public JService 
{
	HIDESBASE virtual Androidapi::Jni::Os::_di_JIBinder __cdecl onBind(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	HIDESBASE virtual void __cdecl onCreate() = 0 ;
	HIDESBASE virtual void __cdecl onDestroy() = 0 ;
	HIDESBASE virtual void __cdecl onStart(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int startId) = 0 ;
	HIDESBASE virtual int __cdecl onStartCommand(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int flags, int startId) = 0 ;
	virtual void __cdecl setIntentRedelivery(bool enabled) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJIntentService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIntentServiceClass,_di_JIntentService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIntentServiceClass,_di_JIntentService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJIntentService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIntentServiceClass,_di_JIntentService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJIntentService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{50FB82E8-7ED8-409E-BC2D-0A385DFE7B94}") JLoaderManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JLoaderManager __cdecl init() = 0 ;
	virtual void __cdecl enableDebugLogging(bool enabled) = 0 ;
};

__interface  INTERFACE_UUID("{D45E200D-E969-42B8-9537-22C62850C7C5}") JLoaderManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl destroyLoader(int id) = 0 ;
	virtual void __cdecl dump(Androidapi::Jni::Javatypes::_di_JString prefix, Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, Androidapi::Jni::Javatypes::_di_JPrintWriter writer, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* args) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JLoader __cdecl getLoader(int id) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JLoader __cdecl initLoader(int id, Androidapi::Jni::Os::_di_JBundle args, _di_JLoaderManager_LoaderCallbacks callback) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JLoader __cdecl restartLoader(int id, Androidapi::Jni::Os::_di_JBundle args, _di_JLoaderManager_LoaderCallbacks callback) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLoaderManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLoaderManagerClass,_di_JLoaderManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLoaderManagerClass,_di_JLoaderManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLoaderManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLoaderManagerClass,_di_JLoaderManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLoaderManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5143414F-8245-45AA-A70D-DB8CA12DC90C}") JLoaderManager_LoaderCallbacksClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{F28327C2-3A34-4296-997C-F69AEDE35ECF}") JLoaderManager_LoaderCallbacks  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JLoader __cdecl onCreateLoader(int id, Androidapi::Jni::Os::_di_JBundle args) = 0 ;
	virtual void __cdecl onLoadFinished(Androidapi::Jni::Graphicscontentviewtext::_di_JLoader loader, Androidapi::Jni::Javatypes::_di_JObject data) = 0 ;
	virtual void __cdecl onLoaderReset(Androidapi::Jni::Graphicscontentviewtext::_di_JLoader loader) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLoaderManager_LoaderCallbacks : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLoaderManager_LoaderCallbacksClass,_di_JLoaderManager_LoaderCallbacks>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLoaderManager_LoaderCallbacksClass,_di_JLoaderManager_LoaderCallbacks> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLoaderManager_LoaderCallbacks() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLoaderManager_LoaderCallbacksClass,_di_JLoaderManager_LoaderCallbacks>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLoaderManager_LoaderCallbacks() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F54B4BFD-1C6B-4CD6-88E7-68ACDD301C01}") JNativeActivityClass  : public JActivityClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMETA_DATA_FUNC_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMETA_DATA_LIB_NAME() = 0 ;
	HIDESBASE virtual _di_JNativeActivity __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString META_DATA_FUNC_NAME = {read=_GetMETA_DATA_FUNC_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString META_DATA_LIB_NAME = {read=_GetMETA_DATA_LIB_NAME};
};

__interface  INTERFACE_UUID("{DFE875A8-A174-41E7-91C0-D959852DE56D}") JNativeActivity  : public JActivity 
{
	HIDESBASE virtual void __cdecl onConfigurationChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JConfiguration newConfig) = 0 ;
	virtual void __cdecl onGlobalLayout() = 0 ;
	virtual void __cdecl onInputQueueCreated(Androidapi::Jni::Graphicscontentviewtext::_di_JInputQueue queue) = 0 ;
	virtual void __cdecl onInputQueueDestroyed(Androidapi::Jni::Graphicscontentviewtext::_di_JInputQueue queue) = 0 ;
	HIDESBASE virtual void __cdecl onLowMemory() = 0 ;
	HIDESBASE virtual void __cdecl onWindowFocusChanged(bool hasFocus) = 0 ;
	virtual void __cdecl surfaceChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder holder, int format, int width, int height) = 0 ;
	virtual void __cdecl surfaceCreated(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder holder) = 0 ;
	virtual void __cdecl surfaceDestroyed(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder holder) = 0 ;
	virtual void __cdecl surfaceRedrawNeeded(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder holder) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNativeActivity : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNativeActivityClass,_di_JNativeActivity>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNativeActivityClass,_di_JNativeActivity> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNativeActivity() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNativeActivityClass,_di_JNativeActivity>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNativeActivity() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4584515F-7E22-49A9-A55B-A6DE3BFD7E1C}") JNotificationClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetBADGE_ICON_LARGE() = 0 ;
	virtual int __cdecl _GetBADGE_ICON_NONE() = 0 ;
	virtual int __cdecl _GetBADGE_ICON_SMALL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCATEGORY_ALARM() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCATEGORY_CALL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCATEGORY_EMAIL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCATEGORY_ERROR() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCATEGORY_EVENT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCATEGORY_MESSAGE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCATEGORY_PROGRESS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCATEGORY_PROMO() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCATEGORY_RECOMMENDATION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCATEGORY_REMINDER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCATEGORY_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCATEGORY_SOCIAL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCATEGORY_STATUS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCATEGORY_SYSTEM() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCATEGORY_TRANSPORT() = 0 ;
	virtual int __cdecl _GetCOLOR_DEFAULT() = 0 ;
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetDEFAULT_ALL() = 0 ;
	virtual int __cdecl _GetDEFAULT_LIGHTS() = 0 ;
	virtual int __cdecl _GetDEFAULT_SOUND() = 0 ;
	virtual int __cdecl _GetDEFAULT_VIBRATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_AUDIO_CONTENTS_URI() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_BACKGROUND_IMAGE_URI() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_BIG_TEXT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_CHANNEL_ID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_CHRONOMETER_COUNT_DOWN() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_COLORIZED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_COMPACT_ACTIONS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_CONVERSATION_TITLE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_HISTORIC_MESSAGES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_INFO_TEXT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_LARGE_ICON() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_LARGE_ICON_BIG() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_MEDIA_SESSION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_MESSAGES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_NOTIFICATION_ID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_NOTIFICATION_TAG() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PEOPLE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PICTURE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PROGRESS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PROGRESS_INDETERMINATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PROGRESS_MAX() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_REMOTE_INPUT_HISTORY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_SELF_DISPLAY_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_SHOW_CHRONOMETER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_SHOW_WHEN() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_SMALL_ICON() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_SUB_TEXT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_SUMMARY_TEXT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_TEMPLATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_TEXT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_TEXT_LINES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_TITLE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_TITLE_BIG() = 0 ;
	virtual int __cdecl _GetFLAG_AUTO_CANCEL() = 0 ;
	virtual int __cdecl _GetFLAG_FOREGROUND_SERVICE() = 0 ;
	virtual int __cdecl _GetFLAG_GROUP_SUMMARY() = 0 ;
	virtual int __cdecl _GetFLAG_HIGH_PRIORITY() = 0 ;
	virtual int __cdecl _GetFLAG_INSISTENT() = 0 ;
	virtual int __cdecl _GetFLAG_LOCAL_ONLY() = 0 ;
	virtual int __cdecl _GetFLAG_NO_CLEAR() = 0 ;
	virtual int __cdecl _GetFLAG_ONGOING_EVENT() = 0 ;
	virtual int __cdecl _GetFLAG_ONLY_ALERT_ONCE() = 0 ;
	virtual int __cdecl _GetFLAG_SHOW_LIGHTS() = 0 ;
	virtual int __cdecl _GetGROUP_ALERT_ALL() = 0 ;
	virtual int __cdecl _GetGROUP_ALERT_CHILDREN() = 0 ;
	virtual int __cdecl _GetGROUP_ALERT_SUMMARY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetINTENT_CATEGORY_NOTIFICATION_PREFERENCES() = 0 ;
	virtual int __cdecl _GetPRIORITY_DEFAULT() = 0 ;
	virtual int __cdecl _GetPRIORITY_HIGH() = 0 ;
	virtual int __cdecl _GetPRIORITY_LOW() = 0 ;
	virtual int __cdecl _GetPRIORITY_MAX() = 0 ;
	virtual int __cdecl _GetPRIORITY_MIN() = 0 ;
	virtual int __cdecl _GetSTREAM_DEFAULT() = 0 ;
	virtual int __cdecl _GetVISIBILITY_PRIVATE() = 0 ;
	virtual int __cdecl _GetVISIBILITY_PUBLIC() = 0 ;
	virtual int __cdecl _GetVISIBILITY_SECRET() = 0 ;
	HIDESBASE virtual _di_JNotification __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JNotification __cdecl init(int icon, Androidapi::Jni::Javatypes::_di_JCharSequence tickerText, __int64 when) = 0 /* overload */;
	HIDESBASE virtual _di_JNotification __cdecl init(Androidapi::Jni::Os::_di_JParcel parcel) = 0 /* overload */;
	__property int BADGE_ICON_LARGE = {read=_GetBADGE_ICON_LARGE};
	__property int BADGE_ICON_NONE = {read=_GetBADGE_ICON_NONE};
	__property int BADGE_ICON_SMALL = {read=_GetBADGE_ICON_SMALL};
	__property Androidapi::Jni::Javatypes::_di_JString CATEGORY_ALARM = {read=_GetCATEGORY_ALARM};
	__property Androidapi::Jni::Javatypes::_di_JString CATEGORY_CALL = {read=_GetCATEGORY_CALL};
	__property Androidapi::Jni::Javatypes::_di_JString CATEGORY_EMAIL = {read=_GetCATEGORY_EMAIL};
	__property Androidapi::Jni::Javatypes::_di_JString CATEGORY_ERROR = {read=_GetCATEGORY_ERROR};
	__property Androidapi::Jni::Javatypes::_di_JString CATEGORY_EVENT = {read=_GetCATEGORY_EVENT};
	__property Androidapi::Jni::Javatypes::_di_JString CATEGORY_MESSAGE = {read=_GetCATEGORY_MESSAGE};
	__property Androidapi::Jni::Javatypes::_di_JString CATEGORY_PROGRESS = {read=_GetCATEGORY_PROGRESS};
	__property Androidapi::Jni::Javatypes::_di_JString CATEGORY_PROMO = {read=_GetCATEGORY_PROMO};
	__property Androidapi::Jni::Javatypes::_di_JString CATEGORY_RECOMMENDATION = {read=_GetCATEGORY_RECOMMENDATION};
	__property Androidapi::Jni::Javatypes::_di_JString CATEGORY_REMINDER = {read=_GetCATEGORY_REMINDER};
	__property Androidapi::Jni::Javatypes::_di_JString CATEGORY_SERVICE = {read=_GetCATEGORY_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString CATEGORY_SOCIAL = {read=_GetCATEGORY_SOCIAL};
	__property Androidapi::Jni::Javatypes::_di_JString CATEGORY_STATUS = {read=_GetCATEGORY_STATUS};
	__property Androidapi::Jni::Javatypes::_di_JString CATEGORY_SYSTEM = {read=_GetCATEGORY_SYSTEM};
	__property Androidapi::Jni::Javatypes::_di_JString CATEGORY_TRANSPORT = {read=_GetCATEGORY_TRANSPORT};
	__property int COLOR_DEFAULT = {read=_GetCOLOR_DEFAULT};
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int DEFAULT_ALL = {read=_GetDEFAULT_ALL};
	__property int DEFAULT_LIGHTS = {read=_GetDEFAULT_LIGHTS};
	__property int DEFAULT_SOUND = {read=_GetDEFAULT_SOUND};
	__property int DEFAULT_VIBRATE = {read=_GetDEFAULT_VIBRATE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_AUDIO_CONTENTS_URI = {read=_GetEXTRA_AUDIO_CONTENTS_URI};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_BACKGROUND_IMAGE_URI = {read=_GetEXTRA_BACKGROUND_IMAGE_URI};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_BIG_TEXT = {read=_GetEXTRA_BIG_TEXT};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_CHANNEL_ID = {read=_GetEXTRA_CHANNEL_ID};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_CHRONOMETER_COUNT_DOWN = {read=_GetEXTRA_CHRONOMETER_COUNT_DOWN};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_COLORIZED = {read=_GetEXTRA_COLORIZED};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_COMPACT_ACTIONS = {read=_GetEXTRA_COMPACT_ACTIONS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_CONVERSATION_TITLE = {read=_GetEXTRA_CONVERSATION_TITLE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_HISTORIC_MESSAGES = {read=_GetEXTRA_HISTORIC_MESSAGES};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_INFO_TEXT = {read=_GetEXTRA_INFO_TEXT};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_LARGE_ICON = {read=_GetEXTRA_LARGE_ICON};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_LARGE_ICON_BIG = {read=_GetEXTRA_LARGE_ICON_BIG};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_MEDIA_SESSION = {read=_GetEXTRA_MEDIA_SESSION};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_MESSAGES = {read=_GetEXTRA_MESSAGES};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_NOTIFICATION_ID = {read=_GetEXTRA_NOTIFICATION_ID};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_NOTIFICATION_TAG = {read=_GetEXTRA_NOTIFICATION_TAG};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PEOPLE = {read=_GetEXTRA_PEOPLE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PICTURE = {read=_GetEXTRA_PICTURE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PROGRESS = {read=_GetEXTRA_PROGRESS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PROGRESS_INDETERMINATE = {read=_GetEXTRA_PROGRESS_INDETERMINATE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PROGRESS_MAX = {read=_GetEXTRA_PROGRESS_MAX};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_REMOTE_INPUT_HISTORY = {read=_GetEXTRA_REMOTE_INPUT_HISTORY};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_SELF_DISPLAY_NAME = {read=_GetEXTRA_SELF_DISPLAY_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_SHOW_CHRONOMETER = {read=_GetEXTRA_SHOW_CHRONOMETER};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_SHOW_WHEN = {read=_GetEXTRA_SHOW_WHEN};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_SMALL_ICON = {read=_GetEXTRA_SMALL_ICON};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_SUB_TEXT = {read=_GetEXTRA_SUB_TEXT};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_SUMMARY_TEXT = {read=_GetEXTRA_SUMMARY_TEXT};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_TEMPLATE = {read=_GetEXTRA_TEMPLATE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_TEXT = {read=_GetEXTRA_TEXT};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_TEXT_LINES = {read=_GetEXTRA_TEXT_LINES};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_TITLE = {read=_GetEXTRA_TITLE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_TITLE_BIG = {read=_GetEXTRA_TITLE_BIG};
	__property int FLAG_AUTO_CANCEL = {read=_GetFLAG_AUTO_CANCEL};
	__property int FLAG_FOREGROUND_SERVICE = {read=_GetFLAG_FOREGROUND_SERVICE};
	__property int FLAG_GROUP_SUMMARY = {read=_GetFLAG_GROUP_SUMMARY};
	__property int FLAG_HIGH_PRIORITY = {read=_GetFLAG_HIGH_PRIORITY};
	__property int FLAG_INSISTENT = {read=_GetFLAG_INSISTENT};
	__property int FLAG_LOCAL_ONLY = {read=_GetFLAG_LOCAL_ONLY};
	__property int FLAG_NO_CLEAR = {read=_GetFLAG_NO_CLEAR};
	__property int FLAG_ONGOING_EVENT = {read=_GetFLAG_ONGOING_EVENT};
	__property int FLAG_ONLY_ALERT_ONCE = {read=_GetFLAG_ONLY_ALERT_ONCE};
	__property int FLAG_SHOW_LIGHTS = {read=_GetFLAG_SHOW_LIGHTS};
	__property int GROUP_ALERT_ALL = {read=_GetGROUP_ALERT_ALL};
	__property int GROUP_ALERT_CHILDREN = {read=_GetGROUP_ALERT_CHILDREN};
	__property int GROUP_ALERT_SUMMARY = {read=_GetGROUP_ALERT_SUMMARY};
	__property Androidapi::Jni::Javatypes::_di_JString INTENT_CATEGORY_NOTIFICATION_PREFERENCES = {read=_GetINTENT_CATEGORY_NOTIFICATION_PREFERENCES};
	__property int PRIORITY_DEFAULT = {read=_GetPRIORITY_DEFAULT};
	__property int PRIORITY_HIGH = {read=_GetPRIORITY_HIGH};
	__property int PRIORITY_LOW = {read=_GetPRIORITY_LOW};
	__property int PRIORITY_MAX = {read=_GetPRIORITY_MAX};
	__property int PRIORITY_MIN = {read=_GetPRIORITY_MIN};
	__property int STREAM_DEFAULT = {read=_GetSTREAM_DEFAULT};
	__property int VISIBILITY_PRIVATE = {read=_GetVISIBILITY_PRIVATE};
	__property int VISIBILITY_PUBLIC = {read=_GetVISIBILITY_PUBLIC};
	__property int VISIBILITY_SECRET = {read=_GetVISIBILITY_SECRET};
};

__interface  INTERFACE_UUID("{4BCE0ADE-6C94-464C-806C-115E4F4DAFF3}") JNotification  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JNotification_Action>* __cdecl _Getactions() = 0 ;
	virtual void __cdecl _Setactions(Androidapi::Jnibridge::TJavaObjectArray__1<_di_JNotification_Action>* Value) = 0 ;
	virtual int __cdecl _GetaudioStreamType() = 0 ;
	virtual void __cdecl _SetaudioStreamType(int Value) = 0 ;
	virtual Androidapi::Jni::Widget::_di_JRemoteViews __cdecl _GetbigContentView() = 0 ;
	virtual void __cdecl _SetbigContentView(Androidapi::Jni::Widget::_di_JRemoteViews Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getcategory() = 0 ;
	virtual void __cdecl _Setcategory(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual int __cdecl _Getcolor() = 0 ;
	virtual void __cdecl _Setcolor(int Value) = 0 ;
	virtual _di_JPendingIntent __cdecl _GetcontentIntent() = 0 ;
	virtual void __cdecl _SetcontentIntent(_di_JPendingIntent Value) = 0 ;
	virtual Androidapi::Jni::Widget::_di_JRemoteViews __cdecl _GetcontentView() = 0 ;
	virtual void __cdecl _SetcontentView(Androidapi::Jni::Widget::_di_JRemoteViews Value) = 0 ;
	virtual int __cdecl _Getdefaults() = 0 ;
	virtual void __cdecl _Setdefaults(int Value) = 0 ;
	virtual _di_JPendingIntent __cdecl _GetdeleteIntent() = 0 ;
	virtual void __cdecl _SetdeleteIntent(_di_JPendingIntent Value) = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl _Getextras() = 0 ;
	virtual void __cdecl _Setextras(Androidapi::Jni::Os::_di_JBundle Value) = 0 ;
	virtual int __cdecl _Getflags() = 0 ;
	virtual void __cdecl _Setflags(int Value) = 0 ;
	virtual _di_JPendingIntent __cdecl _GetfullScreenIntent() = 0 ;
	virtual void __cdecl _SetfullScreenIntent(_di_JPendingIntent Value) = 0 ;
	virtual Androidapi::Jni::Widget::_di_JRemoteViews __cdecl _GetheadsUpContentView() = 0 ;
	virtual void __cdecl _SetheadsUpContentView(Androidapi::Jni::Widget::_di_JRemoteViews Value) = 0 ;
	virtual int __cdecl _Geticon() = 0 ;
	virtual void __cdecl _Seticon(int Value) = 0 ;
	virtual int __cdecl _GeticonLevel() = 0 ;
	virtual void __cdecl _SeticonLevel(int Value) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap __cdecl _GetlargeIcon() = 0 ;
	virtual void __cdecl _SetlargeIcon(Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap Value) = 0 ;
	virtual int __cdecl _GetledARGB() = 0 ;
	virtual void __cdecl _SetledARGB(int Value) = 0 ;
	virtual int __cdecl _GetledOffMS() = 0 ;
	virtual void __cdecl _SetledOffMS(int Value) = 0 ;
	virtual int __cdecl _GetledOnMS() = 0 ;
	virtual void __cdecl _SetledOnMS(int Value) = 0 ;
	virtual int __cdecl _Getnumber() = 0 ;
	virtual void __cdecl _Setnumber(int Value) = 0 ;
	virtual int __cdecl _Getpriority() = 0 ;
	virtual void __cdecl _Setpriority(int Value) = 0 ;
	virtual _di_JNotification __cdecl _GetpublicVersion() = 0 ;
	virtual void __cdecl _SetpublicVersion(_di_JNotification Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl _GettickerText() = 0 ;
	virtual void __cdecl _SettickerText(Androidapi::Jni::Javatypes::_di_JCharSequence Value) = 0 ;
	virtual Androidapi::Jni::Widget::_di_JRemoteViews __cdecl _GettickerView() = 0 ;
	virtual void __cdecl _SettickerView(Androidapi::Jni::Widget::_di_JRemoteViews Value) = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<__int64>* __cdecl _Getvibrate() = 0 ;
	virtual void __cdecl _Setvibrate(Androidapi::Jnibridge::TJavaArray__1<__int64>* Value) = 0 ;
	virtual int __cdecl _Getvisibility() = 0 ;
	virtual void __cdecl _Setvisibility(int Value) = 0 ;
	virtual __int64 __cdecl _Getwhen() = 0 ;
	virtual void __cdecl _Setwhen(__int64 Value) = 0 ;
	virtual _di_JNotification __cdecl clone() = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual int __cdecl getBadgeIconType() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getChannel() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getChannelId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getGroup() = 0 ;
	virtual int __cdecl getGroupAlertBehavior() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JIcon __cdecl getLargeIcon() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getSettingsText() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getShortcutId() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JIcon __cdecl getSmallIcon() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSortKey() = 0 ;
	virtual __int64 __cdecl getTimeout() = 0 ;
	virtual __int64 __cdecl getTimeoutAfter() = 0 ;
	virtual void __cdecl setLatestEventInfo(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JCharSequence contentTitle, Androidapi::Jni::Javatypes::_di_JCharSequence contentText, _di_JPendingIntent contentIntent) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int flags) = 0 ;
	__property Androidapi::Jnibridge::TJavaObjectArray__1<_di_JNotification_Action>* actions = {read=_Getactions, write=_Setactions};
	__property int audioStreamType = {read=_GetaudioStreamType, write=_SetaudioStreamType};
	__property Androidapi::Jni::Widget::_di_JRemoteViews bigContentView = {read=_GetbigContentView, write=_SetbigContentView};
	__property Androidapi::Jni::Javatypes::_di_JString category = {read=_Getcategory, write=_Setcategory};
	__property int color = {read=_Getcolor, write=_Setcolor};
	__property _di_JPendingIntent contentIntent = {read=_GetcontentIntent, write=_SetcontentIntent};
	__property Androidapi::Jni::Widget::_di_JRemoteViews contentView = {read=_GetcontentView, write=_SetcontentView};
	__property int defaults = {read=_Getdefaults, write=_Setdefaults};
	__property _di_JPendingIntent deleteIntent = {read=_GetdeleteIntent, write=_SetdeleteIntent};
	__property Androidapi::Jni::Os::_di_JBundle extras = {read=_Getextras, write=_Setextras};
	__property int flags = {read=_Getflags, write=_Setflags};
	__property _di_JPendingIntent fullScreenIntent = {read=_GetfullScreenIntent, write=_SetfullScreenIntent};
	__property Androidapi::Jni::Widget::_di_JRemoteViews headsUpContentView = {read=_GetheadsUpContentView, write=_SetheadsUpContentView};
	__property int icon = {read=_Geticon, write=_Seticon};
	__property int iconLevel = {read=_GeticonLevel, write=_SeticonLevel};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap largeIcon = {read=_GetlargeIcon, write=_SetlargeIcon};
	__property int ledARGB = {read=_GetledARGB, write=_SetledARGB};
	__property int ledOffMS = {read=_GetledOffMS, write=_SetledOffMS};
	__property int ledOnMS = {read=_GetledOnMS, write=_SetledOnMS};
	__property int number = {read=_Getnumber, write=_Setnumber};
	__property int priority = {read=_Getpriority, write=_Setpriority};
	__property _di_JNotification publicVersion = {read=_GetpublicVersion, write=_SetpublicVersion};
	__property Androidapi::Jni::Javatypes::_di_JCharSequence tickerText = {read=_GettickerText, write=_SettickerText};
	__property Androidapi::Jni::Widget::_di_JRemoteViews tickerView = {read=_GettickerView, write=_SettickerView};
	__property Androidapi::Jnibridge::TJavaArray__1<__int64>* vibrate = {read=_Getvibrate, write=_Setvibrate};
	__property int visibility = {read=_Getvisibility, write=_Setvisibility};
	__property __int64 when = {read=_Getwhen, write=_Setwhen};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNotification : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationClass,_di_JNotification>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationClass,_di_JNotification> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNotification() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationClass,_di_JNotification>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNotification() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B148F977-2DDA-434E-A8D3-E742AB22F8EC}") JNotification_ActionClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JNotification_Action __cdecl init(int icon, Androidapi::Jni::Javatypes::_di_JCharSequence title, _di_JPendingIntent intent) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{673AFCAA-5D84-4B7F-B972-8BA0170EE184}") JNotification_Action  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JPendingIntent __cdecl _GetactionIntent() = 0 ;
	virtual void __cdecl _SetactionIntent(_di_JPendingIntent Value) = 0 ;
	virtual int __cdecl _Geticon() = 0 ;
	virtual void __cdecl _Seticon(int Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl _Gettitle() = 0 ;
	virtual void __cdecl _Settitle(Androidapi::Jni::Javatypes::_di_JCharSequence Value) = 0 ;
	virtual _di_JNotification_Action __cdecl clone() = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual bool __cdecl getAllowGeneratedReplies() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JRemoteInput>* __cdecl getDataOnlyRemoteInputs() = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getExtras() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JIcon __cdecl getIcon() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JRemoteInput>* __cdecl getRemoteInputs() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel out_, int flags) = 0 ;
	__property _di_JPendingIntent actionIntent = {read=_GetactionIntent, write=_SetactionIntent};
	__property int icon = {read=_Geticon, write=_Seticon};
	__property Androidapi::Jni::Javatypes::_di_JCharSequence title = {read=_Gettitle, write=_Settitle};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNotification_Action : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotification_ActionClass,_di_JNotification_Action>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotification_ActionClass,_di_JNotification_Action> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNotification_Action() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotification_ActionClass,_di_JNotification_Action>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNotification_Action() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6A1CADA7-9A73-4D5D-8A23-4A054FF0D388}") JNotificationChannelClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDEFAULT_CHANNEL_ID() = 0 ;
	HIDESBASE virtual _di_JNotificationChannel __cdecl init(Androidapi::Jni::Javatypes::_di_JString id, Androidapi::Jni::Javatypes::_di_JCharSequence name, int importance) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property Androidapi::Jni::Javatypes::_di_JString DEFAULT_CHANNEL_ID = {read=_GetDEFAULT_CHANNEL_ID};
};

__interface  INTERFACE_UUID("{717B07CA-7843-4334-97A7-DD51210E263E}") JNotificationChannel  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl canBypassDnd() = 0 ;
	virtual bool __cdecl canShowBadge() = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual void __cdecl enableLights(bool lights) = 0 ;
	virtual void __cdecl enableVibration(bool vibration) = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDescription() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getGroup() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getId() = 0 ;
	virtual int __cdecl getImportance() = 0 ;
	virtual int __cdecl getLightColor() = 0 ;
	virtual int __cdecl getLockscreenVisibility() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getName() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<__int64>* __cdecl getVibrationPattern() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual void __cdecl setBypassDnd(bool bypassDnd) = 0 ;
	virtual void __cdecl setDescription(Androidapi::Jni::Javatypes::_di_JString description) = 0 ;
	virtual void __cdecl setGroup(Androidapi::Jni::Javatypes::_di_JString groupId) = 0 ;
	virtual void __cdecl setImportance(int importance) = 0 ;
	virtual void __cdecl setLightColor(int argb) = 0 ;
	virtual void __cdecl setLockscreenVisibility(int lockscreenVisibility) = 0 ;
	virtual void __cdecl setName(Androidapi::Jni::Javatypes::_di_JCharSequence name) = 0 ;
	virtual void __cdecl setShowBadge(bool showBadge) = 0 ;
	virtual void __cdecl setVibrationPattern(Androidapi::Jnibridge::TJavaArray__1<__int64>* vibrationPattern) = 0 ;
	virtual bool __cdecl shouldShowLights() = 0 ;
	virtual bool __cdecl shouldVibrate() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNotificationChannel : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationChannelClass,_di_JNotificationChannel>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationChannelClass,_di_JNotificationChannel> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNotificationChannel() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationChannelClass,_di_JNotificationChannel>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNotificationChannel() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FB06B823-E876-440D-A9EE-399ED2173A61}") JNotificationChannelGroupClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JNotificationChannelGroup __cdecl init(Androidapi::Jni::Javatypes::_di_JString id, Androidapi::Jni::Javatypes::_di_JCharSequence name) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{62A94A65-A75E-4351-8FEB-CCAAD6ED5E2D}") JNotificationChannelGroup  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JNotificationChannelGroup __cdecl clone() = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getChannels() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getName() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNotificationChannelGroup : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationChannelGroupClass,_di_JNotificationChannelGroup>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationChannelGroupClass,_di_JNotificationChannelGroup> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNotificationChannelGroup() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationChannelGroupClass,_di_JNotificationChannelGroup>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNotificationChannelGroup() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{66101C50-DAE9-4C81-8186-81A0A43A73BD}") JNotificationManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_INTERRUPTION_FILTER_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_NOTIFICATION_POLICY_ACCESS_GRANTED_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_NOTIFICATION_POLICY_CHANGED() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_DEFAULT() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_HIGH() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_LOW() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_MAX() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_MIN() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_NONE() = 0 ;
	virtual int __cdecl _GetIMPORTANCE_UNSPECIFIED() = 0 ;
	virtual int __cdecl _GetINTERRUPTION_FILTER_ALARMS() = 0 ;
	virtual int __cdecl _GetINTERRUPTION_FILTER_ALL() = 0 ;
	virtual int __cdecl _GetINTERRUPTION_FILTER_NONE() = 0 ;
	virtual int __cdecl _GetINTERRUPTION_FILTER_PRIORITY() = 0 ;
	virtual int __cdecl _GetINTERRUPTION_FILTER_UNKNOWN() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_INTERRUPTION_FILTER_CHANGED = {read=_GetACTION_INTERRUPTION_FILTER_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_NOTIFICATION_POLICY_ACCESS_GRANTED_CHANGED = {read=_GetACTION_NOTIFICATION_POLICY_ACCESS_GRANTED_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_NOTIFICATION_POLICY_CHANGED = {read=_GetACTION_NOTIFICATION_POLICY_CHANGED};
	__property int IMPORTANCE_DEFAULT = {read=_GetIMPORTANCE_DEFAULT};
	__property int IMPORTANCE_HIGH = {read=_GetIMPORTANCE_HIGH};
	__property int IMPORTANCE_LOW = {read=_GetIMPORTANCE_LOW};
	__property int IMPORTANCE_MAX = {read=_GetIMPORTANCE_MAX};
	__property int IMPORTANCE_MIN = {read=_GetIMPORTANCE_MIN};
	__property int IMPORTANCE_NONE = {read=_GetIMPORTANCE_NONE};
	__property int IMPORTANCE_UNSPECIFIED = {read=_GetIMPORTANCE_UNSPECIFIED};
	__property int INTERRUPTION_FILTER_ALARMS = {read=_GetINTERRUPTION_FILTER_ALARMS};
	__property int INTERRUPTION_FILTER_ALL = {read=_GetINTERRUPTION_FILTER_ALL};
	__property int INTERRUPTION_FILTER_NONE = {read=_GetINTERRUPTION_FILTER_NONE};
	__property int INTERRUPTION_FILTER_PRIORITY = {read=_GetINTERRUPTION_FILTER_PRIORITY};
	__property int INTERRUPTION_FILTER_UNKNOWN = {read=_GetINTERRUPTION_FILTER_UNKNOWN};
};

__interface  INTERFACE_UUID("{C3E111F8-A16B-4E14-AEDA-C4E38AF03C49}") JNotificationManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl addAutomaticZenRule(_di_JAutomaticZenRule automaticZenRule) = 0 ;
	virtual bool __cdecl areNotificationsEnabled() = 0 ;
	virtual void __cdecl cancel(int id) = 0 /* overload */;
	virtual void __cdecl cancel(Androidapi::Jni::Javatypes::_di_JString tag, int id) = 0 /* overload */;
	virtual void __cdecl cancelAll() = 0 ;
	virtual void __cdecl createNotificationChannel(_di_JNotificationChannel channel) = 0 ;
	virtual void __cdecl createNotificationChannelGroup(_di_JNotificationChannelGroup group) = 0 ;
	virtual void __cdecl createNotificationChannelGroups(Androidapi::Jni::Javatypes::_di_JList groups) = 0 ;
	virtual void __cdecl createNotificationChannels(Androidapi::Jni::Javatypes::_di_JList channels) = 0 ;
	virtual void __cdecl deleteNotificationChannel(Androidapi::Jni::Javatypes::_di_JString channelId) = 0 ;
	virtual void __cdecl deleteNotificationChannelGroup(Androidapi::Jni::Javatypes::_di_JString groupId) = 0 ;
	virtual _di_JAutomaticZenRule __cdecl getAutomaticZenRule(Androidapi::Jni::Javatypes::_di_JString id) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl getAutomaticZenRules() = 0 ;
	virtual int __cdecl getCurrentInterruptionFilter() = 0 ;
	virtual int __cdecl getImportance() = 0 ;
	virtual _di_JNotificationChannel __cdecl getNotificationChannel(Androidapi::Jni::Javatypes::_di_JString channelId) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getNotificationChannelGroups() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getNotificationChannels() = 0 ;
	virtual _di_JNotificationManager_Policy __cdecl getNotificationPolicy() = 0 ;
	virtual bool __cdecl isNotificationPolicyAccessGranted() = 0 ;
	HIDESBASE virtual void __cdecl notify(int id, _di_JNotification notification) = 0 /* overload */;
	HIDESBASE virtual void __cdecl notify(Androidapi::Jni::Javatypes::_di_JString tag, int id, _di_JNotification notification) = 0 /* overload */;
	virtual bool __cdecl removeAutomaticZenRule(Androidapi::Jni::Javatypes::_di_JString id) = 0 ;
	virtual void __cdecl setInterruptionFilter(int interruptionFilter) = 0 ;
	virtual void __cdecl setNotificationPolicy(_di_JNotificationManager_Policy policy) = 0 ;
	virtual bool __cdecl updateAutomaticZenRule(Androidapi::Jni::Javatypes::_di_JString id, _di_JAutomaticZenRule automaticZenRule) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNotificationManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationManagerClass,_di_JNotificationManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationManagerClass,_di_JNotificationManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNotificationManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationManagerClass,_di_JNotificationManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNotificationManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4943DA07-3DCB-4AB1-9E33-4BE16146172F}") JNotificationManager_PolicyClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetPRIORITY_CATEGORY_CALLS() = 0 ;
	virtual int __cdecl _GetPRIORITY_CATEGORY_EVENTS() = 0 ;
	virtual int __cdecl _GetPRIORITY_CATEGORY_MESSAGES() = 0 ;
	virtual int __cdecl _GetPRIORITY_CATEGORY_REMINDERS() = 0 ;
	virtual int __cdecl _GetPRIORITY_CATEGORY_REPEAT_CALLERS() = 0 ;
	virtual int __cdecl _GetPRIORITY_SENDERS_ANY() = 0 ;
	virtual int __cdecl _GetPRIORITY_SENDERS_CONTACTS() = 0 ;
	virtual int __cdecl _GetPRIORITY_SENDERS_STARRED() = 0 ;
	virtual int __cdecl _GetSUPPRESSED_EFFECT_SCREEN_OFF() = 0 ;
	virtual int __cdecl _GetSUPPRESSED_EFFECT_SCREEN_ON() = 0 ;
	HIDESBASE virtual _di_JNotificationManager_Policy __cdecl init(int priorityCategories, int priorityCallSenders, int priorityMessageSenders) = 0 /* overload */;
	HIDESBASE virtual _di_JNotificationManager_Policy __cdecl init(int priorityCategories, int priorityCallSenders, int priorityMessageSenders, int suppressedVisualEffects) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl priorityCategoriesToString(int priorityCategories) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl prioritySendersToString(int prioritySenders) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl suppressedEffectsToString(int effects) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int PRIORITY_CATEGORY_CALLS = {read=_GetPRIORITY_CATEGORY_CALLS};
	__property int PRIORITY_CATEGORY_EVENTS = {read=_GetPRIORITY_CATEGORY_EVENTS};
	__property int PRIORITY_CATEGORY_MESSAGES = {read=_GetPRIORITY_CATEGORY_MESSAGES};
	__property int PRIORITY_CATEGORY_REMINDERS = {read=_GetPRIORITY_CATEGORY_REMINDERS};
	__property int PRIORITY_CATEGORY_REPEAT_CALLERS = {read=_GetPRIORITY_CATEGORY_REPEAT_CALLERS};
	__property int PRIORITY_SENDERS_ANY = {read=_GetPRIORITY_SENDERS_ANY};
	__property int PRIORITY_SENDERS_CONTACTS = {read=_GetPRIORITY_SENDERS_CONTACTS};
	__property int PRIORITY_SENDERS_STARRED = {read=_GetPRIORITY_SENDERS_STARRED};
	__property int SUPPRESSED_EFFECT_SCREEN_OFF = {read=_GetSUPPRESSED_EFFECT_SCREEN_OFF};
	__property int SUPPRESSED_EFFECT_SCREEN_ON = {read=_GetSUPPRESSED_EFFECT_SCREEN_ON};
};

__interface  INTERFACE_UUID("{D3E4D12A-9CA9-40B2-8130-58F9A19DF9D2}") JNotificationManager_Policy  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl _GetpriorityCallSenders() = 0 ;
	virtual int __cdecl _GetpriorityCategories() = 0 ;
	virtual int __cdecl _GetpriorityMessageSenders() = 0 ;
	virtual int __cdecl _GetsuppressedVisualEffects() = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
	__property int priorityCallSenders = {read=_GetpriorityCallSenders};
	__property int priorityCategories = {read=_GetpriorityCategories};
	__property int priorityMessageSenders = {read=_GetpriorityMessageSenders};
	__property int suppressedVisualEffects = {read=_GetsuppressedVisualEffects};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNotificationManager_Policy : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationManager_PolicyClass,_di_JNotificationManager_Policy>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationManager_PolicyClass,_di_JNotificationManager_Policy> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNotificationManager_Policy() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationManager_PolicyClass,_di_JNotificationManager_Policy>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNotificationManager_Policy() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3C96E145-86EE-487F-9068-C48BA32D0E89}") JPendingIntentClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetFLAG_CANCEL_CURRENT() = 0 ;
	virtual int __cdecl _GetFLAG_IMMUTABLE() = 0 ;
	virtual int __cdecl _GetFLAG_NO_CREATE() = 0 ;
	virtual int __cdecl _GetFLAG_ONE_SHOT() = 0 ;
	virtual int __cdecl _GetFLAG_UPDATE_CURRENT() = 0 ;
	virtual _di_JPendingIntent __cdecl getActivities(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int requestCode, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JIntent>* intents, int flags) = 0 /* overload */;
	virtual _di_JPendingIntent __cdecl getActivities(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int requestCode, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JIntent>* intents, int flags, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual _di_JPendingIntent __cdecl getActivity(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int requestCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int flags) = 0 /* overload */;
	virtual _di_JPendingIntent __cdecl getActivity(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int requestCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int flags, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual _di_JPendingIntent __cdecl getBroadcast(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int requestCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int flags) = 0 ;
	virtual _di_JPendingIntent __cdecl getForegroundService(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int requestCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int flags) = 0 ;
	virtual _di_JPendingIntent __cdecl getService(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int requestCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int flags) = 0 ;
	virtual _di_JPendingIntent __cdecl readPendingIntentOrNullFromParcel(Androidapi::Jni::Os::_di_JParcel in_) = 0 ;
	virtual void __cdecl writePendingIntentOrNullToParcel(_di_JPendingIntent sender, Androidapi::Jni::Os::_di_JParcel out_) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int FLAG_CANCEL_CURRENT = {read=_GetFLAG_CANCEL_CURRENT};
	__property int FLAG_IMMUTABLE = {read=_GetFLAG_IMMUTABLE};
	__property int FLAG_NO_CREATE = {read=_GetFLAG_NO_CREATE};
	__property int FLAG_ONE_SHOT = {read=_GetFLAG_ONE_SHOT};
	__property int FLAG_UPDATE_CURRENT = {read=_GetFLAG_UPDATE_CURRENT};
};

__interface  INTERFACE_UUID("{6475B1E1-B04F-4269-B4EE-33EED669FDDD}") JPendingIntent  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl cancel() = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject otherObj) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getCreatorPackage() = 0 ;
	virtual int __cdecl getCreatorUid() = 0 ;
	virtual Androidapi::Jni::Os::_di_JUserHandle __cdecl getCreatorUserHandle() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JIntentSender __cdecl getIntentSender() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getTargetPackage() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual void __cdecl send() = 0 /* overload */;
	virtual void __cdecl send(int code) = 0 /* overload */;
	virtual void __cdecl send(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int code, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 /* overload */;
	virtual void __cdecl send(int code, _di_JPendingIntent_OnFinished onFinished, Androidapi::Jni::Os::_di_JHandler handler) = 0 /* overload */;
	virtual void __cdecl send(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int code, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, _di_JPendingIntent_OnFinished onFinished, Androidapi::Jni::Os::_di_JHandler handler) = 0 /* overload */;
	virtual void __cdecl send(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int code, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, _di_JPendingIntent_OnFinished onFinished, Androidapi::Jni::Os::_di_JHandler handler, Androidapi::Jni::Javatypes::_di_JString requiredPermission) = 0 /* overload */;
	virtual void __cdecl send(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int code, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, _di_JPendingIntent_OnFinished onFinished, Androidapi::Jni::Os::_di_JHandler handler, Androidapi::Jni::Javatypes::_di_JString requiredPermission, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel out_, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPendingIntent : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPendingIntentClass,_di_JPendingIntent>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPendingIntentClass,_di_JPendingIntent> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPendingIntent() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPendingIntentClass,_di_JPendingIntent>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPendingIntent() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{CA268228-C808-4F93-AF5A-F9B15D8A480C}") JPendingIntent_OnFinishedClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{7420C1F1-8701-4496-B2EB-20C427D3FC50}") JPendingIntent_OnFinished  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onSendFinished(_di_JPendingIntent pendingIntent, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int resultCode, Androidapi::Jni::Javatypes::_di_JString resultData, Androidapi::Jni::Os::_di_JBundle resultExtras) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPendingIntent_OnFinished : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPendingIntent_OnFinishedClass,_di_JPendingIntent_OnFinished>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPendingIntent_OnFinishedClass,_di_JPendingIntent_OnFinished> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPendingIntent_OnFinished() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPendingIntent_OnFinishedClass,_di_JPendingIntent_OnFinished>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPendingIntent_OnFinished() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EC161415-177E-4D89-8AB2-9AB761219D70}") JPictureInPictureArgsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual _di_JPictureInPictureArgs __cdecl convert(_di_JPictureInPictureParams params) = 0 /* overload */;
	virtual _di_JPictureInPictureParams __cdecl convert(_di_JPictureInPictureArgs args) = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{641C62E3-E159-4A8F-9DBF-62A16C8B22F7}") JPictureInPictureArgs  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel out_, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPictureInPictureArgs : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPictureInPictureArgsClass,_di_JPictureInPictureArgs>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPictureInPictureArgsClass,_di_JPictureInPictureArgs> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPictureInPictureArgs() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPictureInPictureArgsClass,_di_JPictureInPictureArgs>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPictureInPictureArgs() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B7630B29-BF9E-4B7B-B429-09CB1FC45170}") JPictureInPictureParamsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{F8BAC3CF-E8D5-4D65-853F-050837FD4B2C}") JPictureInPictureParams  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel out_, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPictureInPictureParams : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPictureInPictureParamsClass,_di_JPictureInPictureParams>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPictureInPictureParamsClass,_di_JPictureInPictureParams> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPictureInPictureParams() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPictureInPictureParamsClass,_di_JPictureInPictureParams>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPictureInPictureParams() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C6208158-16A4-43A6-A8EE-65EACD620921}") JRemoteInputClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_RESULTS_DATA() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRESULTS_CLIP_LABEL() = 0 ;
	virtual void __cdecl addDataResultToIntent(_di_JRemoteInput remoteInput, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, Androidapi::Jni::Javatypes::_di_JMap results) = 0 ;
	virtual void __cdecl addResultsToIntent(Androidapi::Jnibridge::TJavaObjectArray__1<_di_JRemoteInput>* remoteInputs, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, Androidapi::Jni::Os::_di_JBundle results) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl getDataResultsFromIntent(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, Androidapi::Jni::Javatypes::_di_JString remoteInputResultKey) = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getResultsFromIntent(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_RESULTS_DATA = {read=_GetEXTRA_RESULTS_DATA};
	__property Androidapi::Jni::Javatypes::_di_JString RESULTS_CLIP_LABEL = {read=_GetRESULTS_CLIP_LABEL};
};

__interface  INTERFACE_UUID("{1B83290E-C8F7-4F27-B5FE-E6E58EB14C44}") JRemoteInput  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual bool __cdecl getAllowFreeFormInput() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JSet __cdecl getAllowedDataTypes() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JCharSequence>* __cdecl getChoices() = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getExtras() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getLabel() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getResultKey() = 0 ;
	virtual bool __cdecl isDataOnly() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel out_, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRemoteInput : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRemoteInputClass,_di_JRemoteInput>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRemoteInputClass,_di_JRemoteInput> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRemoteInput() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRemoteInputClass,_di_JRemoteInput>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRemoteInput() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F1C6F8CE-732A-4B37-A24F-C2BB1AA5AABB}") JSharedElementCallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JSharedElementCallback __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{1A8B6AC8-E66F-4832-AC50-A9A7941026C7}") JSharedElementCallback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Os::_di_JParcelable __cdecl onCaptureSharedElementSnapshot(Androidapi::Jni::Graphicscontentviewtext::_di_JView sharedElement, Androidapi::Jni::Graphicscontentviewtext::_di_JMatrix viewToGlobalMatrix, Androidapi::Jni::Graphicscontentviewtext::_di_JRectF screenBounds) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl onCreateSnapshotView(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Os::_di_JParcelable snapshot) = 0 ;
	virtual void __cdecl onMapSharedElements(Androidapi::Jni::Javatypes::_di_JList names, Androidapi::Jni::Javatypes::_di_JMap sharedElements) = 0 ;
	virtual void __cdecl onRejectSharedElements(Androidapi::Jni::Javatypes::_di_JList rejectedSharedElements) = 0 ;
	virtual void __cdecl onSharedElementEnd(Androidapi::Jni::Javatypes::_di_JList sharedElementNames, Androidapi::Jni::Javatypes::_di_JList sharedElements, Androidapi::Jni::Javatypes::_di_JList sharedElementSnapshots) = 0 ;
	virtual void __cdecl onSharedElementStart(Androidapi::Jni::Javatypes::_di_JList sharedElementNames, Androidapi::Jni::Javatypes::_di_JList sharedElements, Androidapi::Jni::Javatypes::_di_JList sharedElementSnapshots) = 0 ;
	virtual void __cdecl onSharedElementsArrived(Androidapi::Jni::Javatypes::_di_JList sharedElementNames, Androidapi::Jni::Javatypes::_di_JList sharedElements, _di_JSharedElementCallback_OnSharedElementsReadyListener listener) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSharedElementCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSharedElementCallbackClass,_di_JSharedElementCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSharedElementCallbackClass,_di_JSharedElementCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSharedElementCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSharedElementCallbackClass,_di_JSharedElementCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSharedElementCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{683B85EE-34A2-4CFC-B8E3-73597DD63505}") JSharedElementCallback_OnSharedElementsReadyListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{CF94CD8E-B75D-4BF5-899D-C338B6A1FA0F}") JSharedElementCallback_OnSharedElementsReadyListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onSharedElementsReady() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSharedElementCallback_OnSharedElementsReadyListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSharedElementCallback_OnSharedElementsReadyListenerClass,_di_JSharedElementCallback_OnSharedElementsReadyListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSharedElementCallback_OnSharedElementsReadyListenerClass,_di_JSharedElementCallback_OnSharedElementsReadyListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSharedElementCallback_OnSharedElementsReadyListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSharedElementCallback_OnSharedElementsReadyListenerClass,_di_JSharedElementCallback_OnSharedElementsReadyListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSharedElementCallback_OnSharedElementsReadyListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{CBF458C4-738C-4F67-BCF1-C94E8A1DA3FE}") JTaskStackBuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JTaskStackBuilder __cdecl create(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

__interface  INTERFACE_UUID("{53D84177-E954-404C-A9C9-ED6578A29492}") JTaskStackBuilder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JTaskStackBuilder __cdecl addNextIntent(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent nextIntent) = 0 ;
	virtual _di_JTaskStackBuilder __cdecl addNextIntentWithParentStack(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent nextIntent) = 0 ;
	virtual _di_JTaskStackBuilder __cdecl addParentStack(_di_JActivity sourceActivity) = 0 /* overload */;
	virtual _di_JTaskStackBuilder __cdecl addParentStack(Androidapi::Jni::Javatypes::_di_Jlang_Class sourceActivityClass) = 0 /* overload */;
	virtual _di_JTaskStackBuilder __cdecl addParentStack(Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName sourceActivityName) = 0 /* overload */;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JIntent __cdecl editIntentAt(int index) = 0 ;
	virtual int __cdecl getIntentCount() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JIntent>* __cdecl getIntents() = 0 ;
	virtual _di_JPendingIntent __cdecl getPendingIntent(int requestCode, int flags) = 0 /* overload */;
	virtual _di_JPendingIntent __cdecl getPendingIntent(int requestCode, int flags, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual void __cdecl startActivities() = 0 /* overload */;
	virtual void __cdecl startActivities(Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTaskStackBuilder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTaskStackBuilderClass,_di_JTaskStackBuilder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTaskStackBuilderClass,_di_JTaskStackBuilder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTaskStackBuilder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTaskStackBuilderClass,_di_JTaskStackBuilder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTaskStackBuilder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AD10DB7A-5114-46EC-87FD-2092621052F1}") JVoiceInteractorClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{11EB56F4-1B91-408F-A7B1-E38D5D2FD1DC}") JVoiceInteractor  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JVoiceInteractor_Request __cdecl getActiveRequest(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JVoiceInteractor_Request>* __cdecl getActiveRequests() = 0 ;
	virtual bool __cdecl submitRequest(_di_JVoiceInteractor_Request request) = 0 /* overload */;
	virtual bool __cdecl submitRequest(_di_JVoiceInteractor_Request request, Androidapi::Jni::Javatypes::_di_JString name) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<bool>* __cdecl supportsCommands(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* commands) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVoiceInteractor : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVoiceInteractorClass,_di_JVoiceInteractor>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVoiceInteractorClass,_di_JVoiceInteractor> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVoiceInteractor() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVoiceInteractorClass,_di_JVoiceInteractor>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVoiceInteractor() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0D89D94A-0D69-4050-BAC4-1E912A60A72B}") JVoiceInteractor_RequestClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{96811C7A-4003-4F43-9914-75DA30B0914E}") JVoiceInteractor_Request  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl cancel() = 0 ;
	virtual _di_JActivity __cdecl getActivity() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JContext __cdecl getContext() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
	virtual void __cdecl onAttached(_di_JActivity activity) = 0 ;
	virtual void __cdecl onCancel() = 0 ;
	virtual void __cdecl onDetached() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVoiceInteractor_Request : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVoiceInteractor_RequestClass,_di_JVoiceInteractor_Request>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVoiceInteractor_RequestClass,_di_JVoiceInteractor_Request> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVoiceInteractor_Request() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVoiceInteractor_RequestClass,_di_JVoiceInteractor_Request>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVoiceInteractor_Request() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C6C2FEE4-0A35-4D12-AD42-C718B4B98962}") JAssistContentClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JAssistContent __cdecl init() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{0422FFD0-CE51-4315-981B-55EE11692512}") JAssistContent  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JClipData __cdecl getClipData() = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getExtras() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JIntent __cdecl getIntent() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getStructuredData() = 0 ;
	virtual bool __cdecl isAppProvidedIntent() = 0 ;
	virtual bool __cdecl isAppProvidedWebUri() = 0 ;
	virtual void __cdecl setClipData(Androidapi::Jni::Graphicscontentviewtext::_di_JClipData clip) = 0 ;
	virtual void __cdecl setIntent(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual void __cdecl setStructuredData(Androidapi::Jni::Javatypes::_di_JString structuredData) = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAssistContent : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAssistContentClass,_di_JAssistContent>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAssistContentClass,_di_JAssistContent> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAssistContent() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAssistContentClass,_di_JAssistContent>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAssistContent() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EEE7161A-CC7D-498F-871A-DCD837668C6C}") JAppWidgetProviderInfoClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetRESIZE_BOTH() = 0 ;
	virtual int __cdecl _GetRESIZE_HORIZONTAL() = 0 ;
	virtual int __cdecl _GetRESIZE_NONE() = 0 ;
	virtual int __cdecl _GetRESIZE_VERTICAL() = 0 ;
	virtual int __cdecl _GetWIDGET_CATEGORY_HOME_SCREEN() = 0 ;
	virtual int __cdecl _GetWIDGET_CATEGORY_KEYGUARD() = 0 ;
	virtual int __cdecl _GetWIDGET_CATEGORY_SEARCHBOX() = 0 ;
	HIDESBASE virtual _di_JAppWidgetProviderInfo __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JAppWidgetProviderInfo __cdecl init(Androidapi::Jni::Os::_di_JParcel in_) = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int RESIZE_BOTH = {read=_GetRESIZE_BOTH};
	__property int RESIZE_HORIZONTAL = {read=_GetRESIZE_HORIZONTAL};
	__property int RESIZE_NONE = {read=_GetRESIZE_NONE};
	__property int RESIZE_VERTICAL = {read=_GetRESIZE_VERTICAL};
	__property int WIDGET_CATEGORY_HOME_SCREEN = {read=_GetWIDGET_CATEGORY_HOME_SCREEN};
	__property int WIDGET_CATEGORY_KEYGUARD = {read=_GetWIDGET_CATEGORY_KEYGUARD};
	__property int WIDGET_CATEGORY_SEARCHBOX = {read=_GetWIDGET_CATEGORY_SEARCHBOX};
};

__interface  INTERFACE_UUID("{42141953-BFF9-4343-8F8A-84550E4F3A85}") JAppWidgetProviderInfo  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl _GetautoAdvanceViewId() = 0 ;
	virtual void __cdecl _SetautoAdvanceViewId(int Value) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName __cdecl _Getconfigure() = 0 ;
	virtual void __cdecl _Setconfigure(Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName Value) = 0 ;
	virtual int __cdecl _Geticon() = 0 ;
	virtual void __cdecl _Seticon(int Value) = 0 ;
	virtual int __cdecl _GetinitialKeyguardLayout() = 0 ;
	virtual void __cdecl _SetinitialKeyguardLayout(int Value) = 0 ;
	virtual int __cdecl _GetinitialLayout() = 0 ;
	virtual void __cdecl _SetinitialLayout(int Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getlabel() = 0 ;
	virtual void __cdecl _Setlabel(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual int __cdecl _GetminHeight() = 0 ;
	virtual void __cdecl _SetminHeight(int Value) = 0 ;
	virtual int __cdecl _GetminResizeHeight() = 0 ;
	virtual void __cdecl _SetminResizeHeight(int Value) = 0 ;
	virtual int __cdecl _GetminResizeWidth() = 0 ;
	virtual void __cdecl _SetminResizeWidth(int Value) = 0 ;
	virtual int __cdecl _GetminWidth() = 0 ;
	virtual void __cdecl _SetminWidth(int Value) = 0 ;
	virtual int __cdecl _GetpreviewImage() = 0 ;
	virtual void __cdecl _SetpreviewImage(int Value) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName __cdecl _Getprovider() = 0 ;
	virtual void __cdecl _Setprovider(Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName Value) = 0 ;
	virtual int __cdecl _GetresizeMode() = 0 ;
	virtual void __cdecl _SetresizeMode(int Value) = 0 ;
	virtual int __cdecl _GetupdatePeriodMillis() = 0 ;
	virtual void __cdecl _SetupdatePeriodMillis(int Value) = 0 ;
	virtual int __cdecl _GetwidgetCategory() = 0 ;
	virtual void __cdecl _SetwidgetCategory(int Value) = 0 ;
	virtual _di_JAppWidgetProviderInfo __cdecl clone() = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual Androidapi::Jni::Os::_di_JUserHandle __cdecl getProfile() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl loadIcon(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int density) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl loadLabel(Androidapi::Jni::Graphicscontentviewtext::_di_JPackageManager packageManager) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl loadPreviewImage(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int density) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel out_, int flags) = 0 ;
	__property int autoAdvanceViewId = {read=_GetautoAdvanceViewId, write=_SetautoAdvanceViewId};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName configure = {read=_Getconfigure, write=_Setconfigure};
	__property int icon = {read=_Geticon, write=_Seticon};
	__property int initialKeyguardLayout = {read=_GetinitialKeyguardLayout, write=_SetinitialKeyguardLayout};
	__property int initialLayout = {read=_GetinitialLayout, write=_SetinitialLayout};
	__property Androidapi::Jni::Javatypes::_di_JString label = {read=_Getlabel, write=_Setlabel};
	__property int minHeight = {read=_GetminHeight, write=_SetminHeight};
	__property int minResizeHeight = {read=_GetminResizeHeight, write=_SetminResizeHeight};
	__property int minResizeWidth = {read=_GetminResizeWidth, write=_SetminResizeWidth};
	__property int minWidth = {read=_GetminWidth, write=_SetminWidth};
	__property int previewImage = {read=_GetpreviewImage, write=_SetpreviewImage};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName provider = {read=_Getprovider, write=_Setprovider};
	__property int resizeMode = {read=_GetresizeMode, write=_SetresizeMode};
	__property int updatePeriodMillis = {read=_GetupdatePeriodMillis, write=_SetupdatePeriodMillis};
	__property int widgetCategory = {read=_GetwidgetCategory, write=_SetwidgetCategory};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAppWidgetProviderInfo : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAppWidgetProviderInfoClass,_di_JAppWidgetProviderInfo>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAppWidgetProviderInfoClass,_di_JAppWidgetProviderInfo> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAppWidgetProviderInfo() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAppWidgetProviderInfoClass,_di_JAppWidgetProviderInfo>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAppWidgetProviderInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace App */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_APP)
using namespace Androidapi::Jni::App;
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
#endif	// Androidapi_Jni_AppHPP
