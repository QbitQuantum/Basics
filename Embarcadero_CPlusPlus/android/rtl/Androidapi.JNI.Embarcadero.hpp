// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Embarcadero.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_EmbarcaderoHPP
#define Androidapi_Jni_EmbarcaderoHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.AdMob.hpp>
#include <Androidapi.JNI.App.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.Hardware.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Location.hpp>
#include <Androidapi.JNI.Net.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.JNI.PlayServices.Maps.hpp>
#include <Androidapi.JNI.RenderScript.hpp>
#include <Androidapi.JNI.Util.hpp>
#include <Androidapi.JNI.Webkit.hpp>
#include <Androidapi.JNI.Widget.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Embarcadero
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JFMXNativeActivityClass;
typedef System::DelphiInterface<JFMXNativeActivityClass> _di_JFMXNativeActivityClass;
__interface DELPHIINTERFACE JFMXNativeActivity;
typedef System::DelphiInterface<JFMXNativeActivity> _di_JFMXNativeActivity;
class DELPHICLASS TJFMXNativeActivity;
__interface DELPHIINTERFACE JOnActivityInsetsChangedListenerClass;
typedef System::DelphiInterface<JOnActivityInsetsChangedListenerClass> _di_JOnActivityInsetsChangedListenerClass;
__interface DELPHIINTERFACE JOnActivityInsetsChangedListener;
typedef System::DelphiInterface<JOnActivityInsetsChangedListener> _di_JOnActivityInsetsChangedListener;
class DELPHICLASS TJOnActivityInsetsChangedListener;
__interface DELPHIINTERFACE JOnActivityListenerClass;
typedef System::DelphiInterface<JOnActivityListenerClass> _di_JOnActivityListenerClass;
__interface DELPHIINTERFACE JOnActivityListener;
typedef System::DelphiInterface<JOnActivityListener> _di_JOnActivityListener;
class DELPHICLASS TJOnActivityListener;
__interface DELPHIINTERFACE JSystemServicesHelperClass;
typedef System::DelphiInterface<JSystemServicesHelperClass> _di_JSystemServicesHelperClass;
__interface DELPHIINTERFACE JSystemServicesHelper;
typedef System::DelphiInterface<JSystemServicesHelper> _di_JSystemServicesHelper;
class DELPHICLASS TJSystemServicesHelper;
__interface DELPHIINTERFACE JAddressBookObserverClass;
typedef System::DelphiInterface<JAddressBookObserverClass> _di_JAddressBookObserverClass;
__interface DELPHIINTERFACE JAddressBookObserver;
typedef System::DelphiInterface<JAddressBookObserver> _di_JAddressBookObserver;
class DELPHICLASS TJAddressBookObserver;
__interface DELPHIINTERFACE JOnAddressBookChangesListenerClass;
typedef System::DelphiInterface<JOnAddressBookChangesListenerClass> _di_JOnAddressBookChangesListenerClass;
__interface DELPHIINTERFACE JOnAddressBookChangesListener;
typedef System::DelphiInterface<JOnAddressBookChangesListener> _di_JOnAddressBookChangesListener;
class DELPHICLASS TJOnAddressBookChangesListener;
__interface DELPHIINTERFACE JAdListenerAdapterClass;
typedef System::DelphiInterface<JAdListenerAdapterClass> _di_JAdListenerAdapterClass;
__interface DELPHIINTERFACE JAdListenerAdapter;
typedef System::DelphiInterface<JAdListenerAdapter> _di_JAdListenerAdapter;
class DELPHICLASS TJAdListenerAdapter;
__interface DELPHIINTERFACE JIAdListenerClass;
typedef System::DelphiInterface<JIAdListenerClass> _di_JIAdListenerClass;
__interface DELPHIINTERFACE JIAdListener;
typedef System::DelphiInterface<JIAdListener> _di_JIAdListener;
class DELPHICLASS TJIAdListener;
__interface DELPHIINTERFACE JFMXBroadcastReceiverClass;
typedef System::DelphiInterface<JFMXBroadcastReceiverClass> _di_JFMXBroadcastReceiverClass;
__interface DELPHIINTERFACE JFMXBroadcastReceiver;
typedef System::DelphiInterface<JFMXBroadcastReceiver> _di_JFMXBroadcastReceiver;
class DELPHICLASS TJFMXBroadcastReceiver;
__interface DELPHIINTERFACE JFMXBroadcastReceiverListenerClass;
typedef System::DelphiInterface<JFMXBroadcastReceiverListenerClass> _di_JFMXBroadcastReceiverListenerClass;
__interface DELPHIINTERFACE JFMXBroadcastReceiverListener;
typedef System::DelphiInterface<JFMXBroadcastReceiverListener> _di_JFMXBroadcastReceiverListener;
class DELPHICLASS TJFMXBroadcastReceiverListener;
__interface DELPHIINTERFACE JCamPreviewClass;
typedef System::DelphiInterface<JCamPreviewClass> _di_JCamPreviewClass;
__interface DELPHIINTERFACE JCamPreview;
typedef System::DelphiInterface<JCamPreview> _di_JCamPreview;
class DELPHICLASS TJCamPreview;
__interface DELPHIINTERFACE JScriptC_YUVtoRGBAClass;
typedef System::DelphiInterface<JScriptC_YUVtoRGBAClass> _di_JScriptC_YUVtoRGBAClass;
__interface DELPHIINTERFACE JScriptC_YUVtoRGBA;
typedef System::DelphiInterface<JScriptC_YUVtoRGBA> _di_JScriptC_YUVtoRGBA;
class DELPHICLASS TJScriptC_YUVtoRGBA;
__interface DELPHIINTERFACE JDebuggerUtilsClass;
typedef System::DelphiInterface<JDebuggerUtilsClass> _di_JDebuggerUtilsClass;
__interface DELPHIINTERFACE JDebuggerUtils;
typedef System::DelphiInterface<JDebuggerUtils> _di_JDebuggerUtils;
class DELPHICLASS TJDebuggerUtils;
__interface DELPHIINTERFACE JDeviceArchitectureCheckerClass;
typedef System::DelphiInterface<JDeviceArchitectureCheckerClass> _di_JDeviceArchitectureCheckerClass;
__interface DELPHIINTERFACE JDeviceArchitectureChecker;
typedef System::DelphiInterface<JDeviceArchitectureChecker> _di_JDeviceArchitectureChecker;
class DELPHICLASS TJDeviceArchitectureChecker;
__interface DELPHIINTERFACE JFMXDialogFactoryClass;
typedef System::DelphiInterface<JFMXDialogFactoryClass> _di_JFMXDialogFactoryClass;
__interface DELPHIINTERFACE JFMXDialogFactory;
typedef System::DelphiInterface<JFMXDialogFactory> _di_JFMXDialogFactory;
class DELPHICLASS TJFMXDialogFactory;
__interface DELPHIINTERFACE JFMXDialogHelpersClass;
typedef System::DelphiInterface<JFMXDialogHelpersClass> _di_JFMXDialogHelpersClass;
__interface DELPHIINTERFACE JFMXDialogHelpers;
typedef System::DelphiInterface<JFMXDialogHelpers> _di_JFMXDialogHelpers;
class DELPHICLASS TJFMXDialogHelpers;
__interface DELPHIINTERFACE JFMXDialogListenerClass;
typedef System::DelphiInterface<JFMXDialogListenerClass> _di_JFMXDialogListenerClass;
__interface DELPHIINTERFACE JFMXDialogListener;
typedef System::DelphiInterface<JFMXDialogListener> _di_JFMXDialogListener;
class DELPHICLASS TJFMXDialogListener;
__interface DELPHIINTERFACE JFMXStandardDialogClass;
typedef System::DelphiInterface<JFMXStandardDialogClass> _di_JFMXStandardDialogClass;
__interface DELPHIINTERFACE JFMXStandardDialog;
typedef System::DelphiInterface<JFMXStandardDialog> _di_JFMXStandardDialog;
class DELPHICLASS TJFMXStandardDialog;
__interface DELPHIINTERFACE JFMXDefaultStandardDialogClass;
typedef System::DelphiInterface<JFMXDefaultStandardDialogClass> _di_JFMXDefaultStandardDialogClass;
__interface DELPHIINTERFACE JFMXDefaultStandardDialog;
typedef System::DelphiInterface<JFMXDefaultStandardDialog> _di_JFMXDefaultStandardDialog;
class DELPHICLASS TJFMXDefaultStandardDialog;
__interface DELPHIINTERFACE JFMXDefaultAlertDialogClass;
typedef System::DelphiInterface<JFMXDefaultAlertDialogClass> _di_JFMXDefaultAlertDialogClass;
__interface DELPHIINTERFACE JFMXDefaultAlertDialog;
typedef System::DelphiInterface<JFMXDefaultAlertDialog> _di_JFMXDefaultAlertDialog;
class DELPHICLASS TJFMXDefaultAlertDialog;
__interface DELPHIINTERFACE JFMXDefaultDialogFactoryClass;
typedef System::DelphiInterface<JFMXDefaultDialogFactoryClass> _di_JFMXDefaultDialogFactoryClass;
__interface DELPHIINTERFACE JFMXDefaultDialogFactory;
typedef System::DelphiInterface<JFMXDefaultDialogFactory> _di_JFMXDefaultDialogFactory;
class DELPHICLASS TJFMXDefaultDialogFactory;
__interface DELPHIINTERFACE JFMXDefaultDialogFragmentClass;
typedef System::DelphiInterface<JFMXDefaultDialogFragmentClass> _di_JFMXDefaultDialogFragmentClass;
__interface DELPHIINTERFACE JFMXDefaultDialogFragment;
typedef System::DelphiInterface<JFMXDefaultDialogFragment> _di_JFMXDefaultDialogFragment;
class DELPHICLASS TJFMXDefaultDialogFragment;
__interface DELPHIINTERFACE JFMXDefaultInputQueryDialogClass;
typedef System::DelphiInterface<JFMXDefaultInputQueryDialogClass> _di_JFMXDefaultInputQueryDialogClass;
__interface DELPHIINTERFACE JFMXDefaultInputQueryDialog;
typedef System::DelphiInterface<JFMXDefaultInputQueryDialog> _di_JFMXDefaultInputQueryDialog;
class DELPHICLASS TJFMXDefaultInputQueryDialog;
__interface DELPHIINTERFACE JFormViewClass;
typedef System::DelphiInterface<JFormViewClass> _di_JFormViewClass;
__interface DELPHIINTERFACE JFormView;
typedef System::DelphiInterface<JFormView> _di_JFormView;
class DELPHICLASS TJFormView;
__interface DELPHIINTERFACE JFormViewListenerClass;
typedef System::DelphiInterface<JFormViewListenerClass> _di_JFormViewListenerClass;
__interface DELPHIINTERFACE JFormViewListener;
typedef System::DelphiInterface<JFormViewListener> _di_JFormViewListener;
class DELPHICLASS TJFormViewListener;
__interface DELPHIINTERFACE JFullScreenManagerClass;
typedef System::DelphiInterface<JFullScreenManagerClass> _di_JFullScreenManagerClass;
__interface DELPHIINTERFACE JFullScreenManager;
typedef System::DelphiInterface<JFullScreenManager> _di_JFullScreenManager;
class DELPHICLASS TJFullScreenManager;
__interface DELPHIINTERFACE JOnFullScreenStateChangedListenerClass;
typedef System::DelphiInterface<JOnFullScreenStateChangedListenerClass> _di_JOnFullScreenStateChangedListenerClass;
__interface DELPHIINTERFACE JOnFullScreenStateChangedListener;
typedef System::DelphiInterface<JOnFullScreenStateChangedListener> _di_JOnFullScreenStateChangedListener;
class DELPHICLASS TJOnFullScreenStateChangedListener;
__interface DELPHIINTERFACE JJavaGeocoderClass;
typedef System::DelphiInterface<JJavaGeocoderClass> _di_JJavaGeocoderClass;
__interface DELPHIINTERFACE JJavaGeocoder;
typedef System::DelphiInterface<JJavaGeocoder> _di_JJavaGeocoder;
class DELPHICLASS TJJavaGeocoder;
__interface DELPHIINTERFACE JOnKeyboardStateChangedListenerClass;
typedef System::DelphiInterface<JOnKeyboardStateChangedListenerClass> _di_JOnKeyboardStateChangedListenerClass;
__interface DELPHIINTERFACE JOnKeyboardStateChangedListener;
typedef System::DelphiInterface<JOnKeyboardStateChangedListener> _di_JOnKeyboardStateChangedListener;
class DELPHICLASS TJOnKeyboardStateChangedListener;
__interface DELPHIINTERFACE JVirtualKeyboardClass;
typedef System::DelphiInterface<JVirtualKeyboardClass> _di_JVirtualKeyboardClass;
__interface DELPHIINTERFACE JVirtualKeyboard;
typedef System::DelphiInterface<JVirtualKeyboard> _di_JVirtualKeyboard;
class DELPHICLASS TJVirtualKeyboard;
__interface DELPHIINTERFACE JVirtualKeyboardFrameObserverClass;
typedef System::DelphiInterface<JVirtualKeyboardFrameObserverClass> _di_JVirtualKeyboardFrameObserverClass;
__interface DELPHIINTERFACE JVirtualKeyboardFrameObserver;
typedef System::DelphiInterface<JVirtualKeyboardFrameObserver> _di_JVirtualKeyboardFrameObserver;
class DELPHICLASS TJVirtualKeyboardFrameObserver;
__interface DELPHIINTERFACE JCameraChangeListenerClass;
typedef System::DelphiInterface<JCameraChangeListenerClass> _di_JCameraChangeListenerClass;
__interface DELPHIINTERFACE JCameraChangeListener;
typedef System::DelphiInterface<JCameraChangeListener> _di_JCameraChangeListener;
class DELPHICLASS TJCameraChangeListener;
__interface DELPHIINTERFACE JCameraChangeListener_CallbackClass;
typedef System::DelphiInterface<JCameraChangeListener_CallbackClass> _di_JCameraChangeListener_CallbackClass;
__interface DELPHIINTERFACE JCameraChangeListener_Callback;
typedef System::DelphiInterface<JCameraChangeListener_Callback> _di_JCameraChangeListener_Callback;
class DELPHICLASS TJCameraChangeListener_Callback;
__interface DELPHIINTERFACE JMapViewWithGesturesClass;
typedef System::DelphiInterface<JMapViewWithGesturesClass> _di_JMapViewWithGesturesClass;
__interface DELPHIINTERFACE JMapViewWithGestures;
typedef System::DelphiInterface<JMapViewWithGestures> _di_JMapViewWithGestures;
class DELPHICLASS TJMapViewWithGestures;
__interface DELPHIINTERFACE JFMXMediaLibraryClass;
typedef System::DelphiInterface<JFMXMediaLibraryClass> _di_JFMXMediaLibraryClass;
__interface DELPHIINTERFACE JFMXMediaLibrary;
typedef System::DelphiInterface<JFMXMediaLibrary> _di_JFMXMediaLibrary;
class DELPHICLASS TJFMXMediaLibrary;
__interface DELPHIINTERFACE JFMXMediaLibraryListenerClass;
typedef System::DelphiInterface<JFMXMediaLibraryListenerClass> _di_JFMXMediaLibraryListenerClass;
__interface DELPHIINTERFACE JFMXMediaLibraryListener;
typedef System::DelphiInterface<JFMXMediaLibraryListener> _di_JFMXMediaLibraryListener;
class DELPHICLASS TJFMXMediaLibraryListener;
__interface DELPHIINTERFACE JUtilsClass;
typedef System::DelphiInterface<JUtilsClass> _di_JUtilsClass;
__interface DELPHIINTERFACE JUtils;
typedef System::DelphiInterface<JUtils> _di_JUtils;
class DELPHICLASS TJUtils;
__interface DELPHIINTERFACE JBasePickerClass;
typedef System::DelphiInterface<JBasePickerClass> _di_JBasePickerClass;
__interface DELPHIINTERFACE JBasePicker;
typedef System::DelphiInterface<JBasePicker> _di_JBasePicker;
class DELPHICLASS TJBasePicker;
__interface DELPHIINTERFACE JBaseDateTimePickerClass;
typedef System::DelphiInterface<JBaseDateTimePickerClass> _di_JBaseDateTimePickerClass;
__interface DELPHIINTERFACE JBaseDateTimePicker;
typedef System::DelphiInterface<JBaseDateTimePicker> _di_JBaseDateTimePicker;
class DELPHICLASS TJBaseDateTimePicker;
__interface DELPHIINTERFACE JBaseListPickerClass;
typedef System::DelphiInterface<JBaseListPickerClass> _di_JBaseListPickerClass;
__interface DELPHIINTERFACE JBaseListPicker;
typedef System::DelphiInterface<JBaseListPicker> _di_JBaseListPicker;
class DELPHICLASS TJBaseListPicker;
__interface DELPHIINTERFACE JBasePickersFactoryClass;
typedef System::DelphiInterface<JBasePickersFactoryClass> _di_JBasePickersFactoryClass;
__interface DELPHIINTERFACE JBasePickersFactory;
typedef System::DelphiInterface<JBasePickersFactory> _di_JBasePickersFactory;
class DELPHICLASS TJBasePickersFactory;
__interface DELPHIINTERFACE JGeneratorPickerIDClass;
typedef System::DelphiInterface<JGeneratorPickerIDClass> _di_JGeneratorPickerIDClass;
__interface DELPHIINTERFACE JGeneratorPickerID;
typedef System::DelphiInterface<JGeneratorPickerID> _di_JGeneratorPickerID;
class DELPHICLASS TJGeneratorPickerID;
__interface DELPHIINTERFACE JOnDateTimeChangedListenerClass;
typedef System::DelphiInterface<JOnDateTimeChangedListenerClass> _di_JOnDateTimeChangedListenerClass;
__interface DELPHIINTERFACE JOnDateTimeChangedListener;
typedef System::DelphiInterface<JOnDateTimeChangedListener> _di_JOnDateTimeChangedListener;
class DELPHICLASS TJOnDateTimeChangedListener;
__interface DELPHIINTERFACE JOnItemChangedListenerClass;
typedef System::DelphiInterface<JOnItemChangedListenerClass> _di_JOnItemChangedListenerClass;
__interface DELPHIINTERFACE JOnItemChangedListener;
typedef System::DelphiInterface<JOnItemChangedListener> _di_JOnItemChangedListener;
class DELPHICLASS TJOnItemChangedListener;
__interface DELPHIINTERFACE Jdefaults_DatePickerFragmentClass;
typedef System::DelphiInterface<Jdefaults_DatePickerFragmentClass> _di_Jdefaults_DatePickerFragmentClass;
__interface DELPHIINTERFACE Jdefaults_DatePickerFragment;
typedef System::DelphiInterface<Jdefaults_DatePickerFragment> _di_Jdefaults_DatePickerFragment;
class DELPHICLASS TJdefaults_DatePickerFragment;
__interface DELPHIINTERFACE JDefaultDatePickerClass;
typedef System::DelphiInterface<JDefaultDatePickerClass> _di_JDefaultDatePickerClass;
__interface DELPHIINTERFACE JDefaultDatePicker;
typedef System::DelphiInterface<JDefaultDatePicker> _di_JDefaultDatePicker;
class DELPHICLASS TJDefaultDatePicker;
__interface DELPHIINTERFACE JDefaultListPickerClass;
typedef System::DelphiInterface<JDefaultListPickerClass> _di_JDefaultListPickerClass;
__interface DELPHIINTERFACE JDefaultListPicker;
typedef System::DelphiInterface<JDefaultListPicker> _di_JDefaultListPicker;
class DELPHICLASS TJDefaultListPicker;
__interface DELPHIINTERFACE JDefaultPickersFactoryClass;
typedef System::DelphiInterface<JDefaultPickersFactoryClass> _di_JDefaultPickersFactoryClass;
__interface DELPHIINTERFACE JDefaultPickersFactory;
typedef System::DelphiInterface<JDefaultPickersFactory> _di_JDefaultPickersFactory;
class DELPHICLASS TJDefaultPickersFactory;
__interface DELPHIINTERFACE JDefaultTimePickerClass;
typedef System::DelphiInterface<JDefaultTimePickerClass> _di_JDefaultTimePickerClass;
__interface DELPHIINTERFACE JDefaultTimePicker;
typedef System::DelphiInterface<JDefaultTimePicker> _di_JDefaultTimePicker;
class DELPHICLASS TJDefaultTimePicker;
__interface DELPHIINTERFACE Jdefaults_ListPickerFragmentClass;
typedef System::DelphiInterface<Jdefaults_ListPickerFragmentClass> _di_Jdefaults_ListPickerFragmentClass;
__interface DELPHIINTERFACE Jdefaults_ListPickerFragment;
typedef System::DelphiInterface<Jdefaults_ListPickerFragment> _di_Jdefaults_ListPickerFragment;
class DELPHICLASS TJdefaults_ListPickerFragment;
__interface DELPHIINTERFACE Jdefaults_TimePickerFragmentClass;
typedef System::DelphiInterface<Jdefaults_TimePickerFragmentClass> _di_Jdefaults_TimePickerFragmentClass;
__interface DELPHIINTERFACE Jdefaults_TimePickerFragment;
typedef System::DelphiInterface<Jdefaults_TimePickerFragment> _di_Jdefaults_TimePickerFragment;
class DELPHICLASS TJdefaults_TimePickerFragment;
__interface DELPHIINTERFACE JIAPSecurityClass;
typedef System::DelphiInterface<JIAPSecurityClass> _di_JIAPSecurityClass;
__interface DELPHIINTERFACE JIAPSecurity;
typedef System::DelphiInterface<JIAPSecurity> _di_JIAPSecurity;
class DELPHICLASS TJIAPSecurity;
__interface DELPHIINTERFACE JCharCaseClass;
typedef System::DelphiInterface<JCharCaseClass> _di_JCharCaseClass;
__interface DELPHIINTERFACE JCharCase;
typedef System::DelphiInterface<JCharCase> _di_JCharCase;
class DELPHICLASS TJCharCase;
__interface DELPHIINTERFACE JFMXEditTextClass;
typedef System::DelphiInterface<JFMXEditTextClass> _di_JFMXEditTextClass;
__interface DELPHIINTERFACE JFMXEditText;
typedef System::DelphiInterface<JFMXEditText> _di_JFMXEditText;
class DELPHICLASS TJFMXEditText;
__interface DELPHIINTERFACE JFMXTextListenerClass;
typedef System::DelphiInterface<JFMXTextListenerClass> _di_JFMXTextListenerClass;
__interface DELPHIINTERFACE JFMXTextListener;
typedef System::DelphiInterface<JFMXTextListener> _di_JFMXTextListener;
class DELPHICLASS TJFMXTextListener;
__interface DELPHIINTERFACE JReturnKeyTypeClass;
typedef System::DelphiInterface<JReturnKeyTypeClass> _di_JReturnKeyTypeClass;
__interface DELPHIINTERFACE JReturnKeyType;
typedef System::DelphiInterface<JReturnKeyType> _di_JReturnKeyType;
class DELPHICLASS TJReturnKeyType;
__interface DELPHIINTERFACE JVirtualKeyboardTypeClass;
typedef System::DelphiInterface<JVirtualKeyboardTypeClass> _di_JVirtualKeyboardTypeClass;
__interface DELPHIINTERFACE JVirtualKeyboardType;
typedef System::DelphiInterface<JVirtualKeyboardType> _di_JVirtualKeyboardType;
class DELPHICLASS TJVirtualKeyboardType;
__interface DELPHIINTERFACE JAllLowerClass;
typedef System::DelphiInterface<JAllLowerClass> _di_JAllLowerClass;
__interface DELPHIINTERFACE JAllLower;
typedef System::DelphiInterface<JAllLower> _di_JAllLower;
class DELPHICLASS TJAllLower;
__interface DELPHIINTERFACE JFilterCharClass;
typedef System::DelphiInterface<JFilterCharClass> _di_JFilterCharClass;
__interface DELPHIINTERFACE JFilterChar;
typedef System::DelphiInterface<JFilterChar> _di_JFilterChar;
class DELPHICLASS TJFilterChar;
__interface DELPHIINTERFACE JDelegatedActionModeCallbackClass;
typedef System::DelphiInterface<JDelegatedActionModeCallbackClass> _di_JDelegatedActionModeCallbackClass;
__interface DELPHIINTERFACE JDelegatedActionModeCallback;
typedef System::DelphiInterface<JDelegatedActionModeCallback> _di_JDelegatedActionModeCallback;
class DELPHICLASS TJDelegatedActionModeCallback;
__interface DELPHIINTERFACE JDelegatedActionModeCallback2Class;
typedef System::DelphiInterface<JDelegatedActionModeCallback2Class> _di_JDelegatedActionModeCallback2Class;
__interface DELPHIINTERFACE JDelegatedActionModeCallback2;
typedef System::DelphiInterface<JDelegatedActionModeCallback2> _di_JDelegatedActionModeCallback2;
class DELPHICLASS TJDelegatedActionModeCallback2;
__interface DELPHIINTERFACE JOnTextContextMenuListenerClass;
typedef System::DelphiInterface<JOnTextContextMenuListenerClass> _di_JOnTextContextMenuListenerClass;
__interface DELPHIINTERFACE JOnTextContextMenuListener;
typedef System::DelphiInterface<JOnTextContextMenuListener> _di_JOnTextContextMenuListener;
class DELPHICLASS TJOnTextContextMenuListener;
__interface DELPHIINTERFACE JOnWebViewListenerClass;
typedef System::DelphiInterface<JOnWebViewListenerClass> _di_JOnWebViewListenerClass;
__interface DELPHIINTERFACE JOnWebViewListener;
typedef System::DelphiInterface<JOnWebViewListener> _di_JOnWebViewListener;
class DELPHICLASS TJOnWebViewListener;
__interface DELPHIINTERFACE JWebBrowserClass;
typedef System::DelphiInterface<JWebBrowserClass> _di_JWebBrowserClass;
__interface DELPHIINTERFACE JWebBrowser;
typedef System::DelphiInterface<JWebBrowser> _di_JWebBrowser;
class DELPHICLASS TJWebBrowser;
__interface DELPHIINTERFACE JWebClientClass;
typedef System::DelphiInterface<JWebClientClass> _di_JWebClientClass;
__interface DELPHIINTERFACE JWebClient;
typedef System::DelphiInterface<JWebClient> _di_JWebClient;
class DELPHICLASS TJWebClient;
__interface DELPHIINTERFACE JProxyServiceClass;
typedef System::DelphiInterface<JProxyServiceClass> _di_JProxyServiceClass;
__interface DELPHIINTERFACE JProxyService;
typedef System::DelphiInterface<JProxyService> _di_JProxyService;
class DELPHICLASS TJProxyService;
__interface DELPHIINTERFACE JRTLHandlerClass;
typedef System::DelphiInterface<JRTLHandlerClass> _di_JRTLHandlerClass;
__interface DELPHIINTERFACE JRTLHandler;
typedef System::DelphiInterface<JRTLHandler> _di_JRTLHandler;
class DELPHICLASS TJRTLHandler;
__interface DELPHIINTERFACE JRTLHandler_ListenerClass;
typedef System::DelphiInterface<JRTLHandler_ListenerClass> _di_JRTLHandler_ListenerClass;
__interface DELPHIINTERFACE JRTLHandler_Listener;
typedef System::DelphiInterface<JRTLHandler_Listener> _di_JRTLHandler_Listener;
class DELPHICLASS TJRTLHandler_Listener;
__interface DELPHIINTERFACE JRTLHandler_RTLSuperHandlerClass;
typedef System::DelphiInterface<JRTLHandler_RTLSuperHandlerClass> _di_JRTLHandler_RTLSuperHandlerClass;
__interface DELPHIINTERFACE JRTLHandler_RTLSuperHandler;
typedef System::DelphiInterface<JRTLHandler_RTLSuperHandler> _di_JRTLHandler_RTLSuperHandler;
class DELPHICLASS TJRTLHandler_RTLSuperHandler;
__interface DELPHIINTERFACE JChannelsManagerClass;
typedef System::DelphiInterface<JChannelsManagerClass> _di_JChannelsManagerClass;
__interface DELPHIINTERFACE JChannelsManager;
typedef System::DelphiInterface<JChannelsManager> _di_JChannelsManager;
class DELPHICLASS TJChannelsManager;
__interface DELPHIINTERFACE JNotificationAlarmClass;
typedef System::DelphiInterface<JNotificationAlarmClass> _di_JNotificationAlarmClass;
__interface DELPHIINTERFACE JNotificationAlarm;
typedef System::DelphiInterface<JNotificationAlarm> _di_JNotificationAlarm;
class DELPHICLASS TJNotificationAlarm;
__interface DELPHIINTERFACE JNotificationInfoClass;
typedef System::DelphiInterface<JNotificationInfoClass> _di_JNotificationInfoClass;
__interface DELPHIINTERFACE JNotificationInfo;
typedef System::DelphiInterface<JNotificationInfo> _di_JNotificationInfo;
class DELPHICLASS TJNotificationInfo;
__interface DELPHIINTERFACE JRepeatIntervalClass;
typedef System::DelphiInterface<JRepeatIntervalClass> _di_JRepeatIntervalClass;
__interface DELPHIINTERFACE JRepeatInterval;
typedef System::DelphiInterface<JRepeatInterval> _di_JRepeatInterval;
class DELPHICLASS TJRepeatInterval;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{829C77FB-08F1-4D19-9782-3C58EEC12599}") JFMXNativeActivityClass  : public Androidapi::Jni::App::JNativeActivityClass 
{
	HIDESBASE virtual _di_JFMXNativeActivity __cdecl init() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_FCM_NOTIFICATION() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_FCM_NOTIFICATION = {read=_GetACTION_FCM_NOTIFICATION};
};

__interface  INTERFACE_UUID("{2FA559EC-D1D7-46AA-9C52-FEFC6B3E2DE3}") JFMXNativeActivity  : public Androidapi::Jni::App::JNativeActivity 
{
	virtual void __cdecl onMediaLibraryAccept(int requestCode) = 0 ;
	HIDESBASE virtual bool __cdecl dispatchKeyEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDeviceID() = 0 ;
	virtual _di_JFMXEditText __cdecl getEditText() = 0 ;
	virtual _di_JFMXMediaLibrary __cdecl getMediaLibrary() = 0 ;
	virtual _di_JFullScreenManager __cdecl getFullScreenManager() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent __cdecl getLastEvent() = 0 ;
	virtual _di_JOnActivityInsetsChangedListener __cdecl getOnActivityInsetsChangedListener() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JPoint __cdecl getRawDisplaySize() = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getStartupFCM() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup __cdecl getContentView() = 0 ;
	virtual _di_JVirtualKeyboard __cdecl getVirtualKeyboard() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JRect __cdecl getWindowInsets() = 0 ;
	virtual bool __cdecl isWindowInsetsDefined() = 0 ;
	virtual void __cdecl onPause() = 0 ;
	HIDESBASE virtual void __cdecl onRequestPermissionsResult(int requestCode, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* permissions, Androidapi::Jnibridge::TJavaArray__1<int>* grantResults) = 0 ;
	virtual void __cdecl onResume() = 0 ;
	HIDESBASE virtual void __cdecl onWindowFocusChanged(bool hasFocus) = 0 ;
	virtual void __cdecl registerIntentAction(Androidapi::Jni::Javatypes::_di_JString action) = 0 ;
	virtual void __cdecl setListener(_di_JOnActivityListener listener) = 0 ;
	virtual void __cdecl setOnActivityInsetsChangedListener(_di_JOnActivityInsetsChangedListener onActivityInsetsChangedListener) = 0 ;
	HIDESBASE virtual void __cdecl showDialog(int id, Androidapi::Jni::App::_di_JDialog dialog) = 0 ;
	virtual void __cdecl startJobIntentService(Androidapi::Jni::Javatypes::_di_JString serviceName, int jobId, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent workIntent) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFMXNativeActivity : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXNativeActivityClass,_di_JFMXNativeActivity>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXNativeActivityClass,_di_JFMXNativeActivity> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFMXNativeActivity() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXNativeActivityClass,_di_JFMXNativeActivity>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFMXNativeActivity() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3834D8B1-477A-4A0F-927C-1A5F3555376A}") JOnActivityInsetsChangedListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{EAEEA616-D505-45EB-90B2-88350F18DF07}") JOnActivityInsetsChangedListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl insetsChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JRect newInsets) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnActivityInsetsChangedListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnActivityInsetsChangedListenerClass,_di_JOnActivityInsetsChangedListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnActivityInsetsChangedListenerClass,_di_JOnActivityInsetsChangedListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnActivityInsetsChangedListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnActivityInsetsChangedListenerClass,_di_JOnActivityInsetsChangedListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnActivityInsetsChangedListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{168F8C7B-7FE9-4A08-87AD-51CCC3C56E43}") JOnActivityListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{D0E0FCFB-0400-4522-B51E-220FC79F92BB}") JOnActivityListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCancelReceiveImage(int requestCode) = 0 ;
	virtual void __cdecl onReceiveImagePath(int requestCode, Androidapi::Jni::Javatypes::_di_JString fileName) = 0 ;
	virtual void __cdecl onReceiveNotification(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual void __cdecl onReceiveResult(int requestCode, int resultCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual void __cdecl onRequestPermissionsResult(int requestCode, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* permissions, Androidapi::Jnibridge::TJavaArray__1<int>* grantResults) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnActivityListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnActivityListenerClass,_di_JOnActivityListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnActivityListenerClass,_di_JOnActivityListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnActivityListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnActivityListenerClass,_di_JOnActivityListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnActivityListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B256824C-1EAD-48E6-99E4-53A6CDA59FD2}") JSystemServicesHelperClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JSystemServicesHelper __cdecl init() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getServiceOrThrow(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString serviceName, Androidapi::Jni::Javatypes::_di_Jlang_Class serviceClass) = 0 ;
};

__interface  INTERFACE_UUID("{A2688E28-CF41-4E0F-99F1-7863A5BB161A}") JSystemServicesHelper  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSystemServicesHelper : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSystemServicesHelperClass,_di_JSystemServicesHelper>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSystemServicesHelperClass,_di_JSystemServicesHelper> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSystemServicesHelper() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSystemServicesHelperClass,_di_JSystemServicesHelper>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSystemServicesHelper() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6F4C5DCF-451B-484D-A8CC-AB0FBA10739B}") JAddressBookObserverClass  : public Androidapi::Jni::Graphicscontentviewtext::JContentObserverClass 
{
	HIDESBASE virtual _di_JAddressBookObserver __cdecl init(_di_JOnAddressBookChangesListener listener) = 0 ;
};

__interface  INTERFACE_UUID("{1942AB70-72D9-4305-9E13-2D8653A90595}") JAddressBookObserver  : public Androidapi::Jni::Graphicscontentviewtext::JContentObserver 
{
	HIDESBASE virtual void __cdecl onChange(bool selfChange) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAddressBookObserver : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAddressBookObserverClass,_di_JAddressBookObserver>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAddressBookObserverClass,_di_JAddressBookObserver> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAddressBookObserver() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAddressBookObserverClass,_di_JAddressBookObserver>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAddressBookObserver() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3E1F45C0-439C-492D-8573-835A12251052}") JOnAddressBookChangesListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{07FE15E5-7885-430E-B161-2E339965B549}") JOnAddressBookChangesListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onChanged(bool selfChange) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnAddressBookChangesListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnAddressBookChangesListenerClass,_di_JOnAddressBookChangesListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnAddressBookChangesListenerClass,_di_JOnAddressBookChangesListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnAddressBookChangesListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnAddressBookChangesListenerClass,_di_JOnAddressBookChangesListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnAddressBookChangesListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{CD2C5FBC-0887-4691-A942-FAEBDC43BC70}") JAdListenerAdapterClass  : public Androidapi::Jni::Admob::JAdListenerClass 
{
	HIDESBASE virtual _di_JAdListenerAdapter __cdecl init(_di_JIAdListener listener) = 0 ;
};

__interface  INTERFACE_UUID("{9711888A-C126-4ACF-9F3C-E0E946542342}") JAdListenerAdapter  : public Androidapi::Jni::Admob::JAdListener 
{
	HIDESBASE virtual void __cdecl onAdClosed() = 0 ;
	HIDESBASE virtual void __cdecl onAdFailedToLoad(int errorCode) = 0 ;
	HIDESBASE virtual void __cdecl onAdLeftApplication() = 0 ;
	HIDESBASE virtual void __cdecl onAdLoaded() = 0 ;
	HIDESBASE virtual void __cdecl onAdOpened() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdListenerAdapter : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdListenerAdapterClass,_di_JAdListenerAdapter>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdListenerAdapterClass,_di_JAdListenerAdapter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdListenerAdapter() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdListenerAdapterClass,_di_JAdListenerAdapter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdListenerAdapter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3E8BEED5-B092-42FA-96EB-E4C49A7A0E00}") JIAdListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{8E46C3D5-1846-458C-9FA4-EFC3DDCA705F}") JIAdListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onAdClosed() = 0 ;
	virtual void __cdecl onAdFailedToLoad(int errorCode) = 0 ;
	virtual void __cdecl onAdLeftApplication() = 0 ;
	virtual void __cdecl onAdLoaded() = 0 ;
	virtual void __cdecl onAdOpened() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJIAdListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIAdListenerClass,_di_JIAdListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIAdListenerClass,_di_JIAdListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJIAdListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIAdListenerClass,_di_JIAdListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJIAdListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{18E76E33-CD0C-4E7F-9DBE-F1B2EB9DEFD9}") JFMXBroadcastReceiverClass  : public Androidapi::Jni::Graphicscontentviewtext::JBroadcastReceiverClass 
{
	HIDESBASE virtual _di_JFMXBroadcastReceiver __cdecl init(_di_JFMXBroadcastReceiverListener listener) = 0 ;
};

__interface  INTERFACE_UUID("{A84605C5-6CC0-4C17-AE5A-A7065C0E3C6A}") JFMXBroadcastReceiver  : public Androidapi::Jni::Graphicscontentviewtext::JBroadcastReceiver 
{
	HIDESBASE virtual void __cdecl onReceive(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFMXBroadcastReceiver : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXBroadcastReceiverClass,_di_JFMXBroadcastReceiver>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXBroadcastReceiverClass,_di_JFMXBroadcastReceiver> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFMXBroadcastReceiver() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXBroadcastReceiverClass,_di_JFMXBroadcastReceiver>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFMXBroadcastReceiver() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9896B7DB-1D20-4C30-82BB-3B0CEF41280E}") JFMXBroadcastReceiverListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{8D356FEB-9F54-40C6-8E01-94603B4AB486}") JFMXBroadcastReceiverListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onReceive(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFMXBroadcastReceiverListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXBroadcastReceiverListenerClass,_di_JFMXBroadcastReceiverListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXBroadcastReceiverListenerClass,_di_JFMXBroadcastReceiverListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFMXBroadcastReceiverListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXBroadcastReceiverListenerClass,_di_JFMXBroadcastReceiverListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFMXBroadcastReceiverListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4A2F8A98-B8E3-4616-8E02-DA083EC4E2BA}") JCamPreviewClass  : public Androidapi::Jni::Graphicscontentviewtext::JSurfaceViewClass 
{
	HIDESBASE virtual _di_JCamPreview __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

__interface  INTERFACE_UUID("{09E012FD-099E-45F9-AC84-DDB431920646}") JCamPreview  : public Androidapi::Jni::Graphicscontentviewtext::JSurfaceView 
{
	virtual Androidapi::Jni::Hardware::_di_JCamera __cdecl _GetmCamera() = 0 ;
	virtual void __cdecl _SetmCamera(Androidapi::Jni::Hardware::_di_JCamera Value) = 0 ;
	HIDESBASE virtual void __cdecl draw(Androidapi::Jni::Graphicscontentviewtext::_di_JCanvas canvas) = 0 ;
	virtual void __cdecl surfaceChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder holder, int format, int w, int h) = 0 ;
	virtual void __cdecl surfaceCreated(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder holder) = 0 ;
	virtual void __cdecl surfaceDestroyed(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder holder) = 0 ;
	__property Androidapi::Jni::Hardware::_di_JCamera mCamera = {read=_GetmCamera, write=_SetmCamera};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCamPreview : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamPreviewClass,_di_JCamPreview>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamPreviewClass,_di_JCamPreview> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCamPreview() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamPreviewClass,_di_JCamPreview>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCamPreview() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{13550268-05B2-46BC-8C76-1094FBC8B2B2}") JScriptC_YUVtoRGBAClass  : public Androidapi::Jni::Renderscript::JScriptCClass 
{
	HIDESBASE virtual _di_JScriptC_YUVtoRGBA __cdecl init(Androidapi::Jni::Renderscript::_di_JRenderScript rs) = 0 ;
};

__interface  INTERFACE_UUID("{823106B6-B198-4956-8B88-FF6B2A6A4D00}") JScriptC_YUVtoRGBA  : public Androidapi::Jni::Renderscript::JScriptC 
{
	virtual void __cdecl forEach_ProcessFrameRotated0Degrees(Androidapi::Jni::Renderscript::_di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEach_ProcessFrameRotated0Degrees(Androidapi::Jni::Renderscript::_di_JAllocation aout, Androidapi::Jni::Renderscript::_di_JScript_LaunchOptions sc) = 0 /* overload */;
	virtual void __cdecl forEach_ProcessFrameRotated180Degrees(Androidapi::Jni::Renderscript::_di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEach_ProcessFrameRotated180Degrees(Androidapi::Jni::Renderscript::_di_JAllocation aout, Androidapi::Jni::Renderscript::_di_JScript_LaunchOptions sc) = 0 /* overload */;
	virtual void __cdecl forEach_ProcessFrameRotated270Degrees(Androidapi::Jni::Renderscript::_di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEach_ProcessFrameRotated270Degrees(Androidapi::Jni::Renderscript::_di_JAllocation aout, Androidapi::Jni::Renderscript::_di_JScript_LaunchOptions sc) = 0 /* overload */;
	virtual void __cdecl forEach_ProcessFrameRotated90Degrees(Androidapi::Jni::Renderscript::_di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEach_ProcessFrameRotated90Degrees(Androidapi::Jni::Renderscript::_di_JAllocation aout, Androidapi::Jni::Renderscript::_di_JScript_LaunchOptions sc) = 0 /* overload */;
	virtual Androidapi::Jni::Renderscript::_di_JScript_FieldID __cdecl getFieldID_Height() = 0 ;
	virtual Androidapi::Jni::Renderscript::_di_JScript_FieldID __cdecl getFieldID_Input() = 0 ;
	virtual Androidapi::Jni::Renderscript::_di_JScript_FieldID __cdecl getFieldID_Width() = 0 ;
	virtual Androidapi::Jni::Renderscript::_di_JScript_KernelID __cdecl getKernelID_ProcessFrameRotated0Degrees() = 0 ;
	virtual Androidapi::Jni::Renderscript::_di_JScript_KernelID __cdecl getKernelID_ProcessFrameRotated180Degrees() = 0 ;
	virtual Androidapi::Jni::Renderscript::_di_JScript_KernelID __cdecl getKernelID_ProcessFrameRotated270Degrees() = 0 ;
	virtual Androidapi::Jni::Renderscript::_di_JScript_KernelID __cdecl getKernelID_ProcessFrameRotated90Degrees() = 0 ;
	virtual int __cdecl get_Height() = 0 ;
	virtual Androidapi::Jni::Renderscript::_di_JAllocation __cdecl get_Input() = 0 ;
	virtual int __cdecl get_Width() = 0 ;
	virtual void __cdecl set_Height(int v) = 0 ;
	virtual void __cdecl set_Input(Androidapi::Jni::Renderscript::_di_JAllocation v) = 0 ;
	virtual void __cdecl set_Width(int v) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptC_YUVtoRGBA : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptC_YUVtoRGBAClass,_di_JScriptC_YUVtoRGBA>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptC_YUVtoRGBAClass,_di_JScriptC_YUVtoRGBA> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptC_YUVtoRGBA() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptC_YUVtoRGBAClass,_di_JScriptC_YUVtoRGBA>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptC_YUVtoRGBA() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2D7C74CD-B262-4957-A79A-B1902E086009}") JDebuggerUtilsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JDebuggerUtils __cdecl init(Androidapi::Jni::App::_di_JActivity activity) = 0 ;
};

__interface  INTERFACE_UUID("{56EE2D63-4F6E-41B4-949D-FB690E696B0D}") JDebuggerUtils  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl tryStartDebugger() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDebuggerUtils : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDebuggerUtilsClass,_di_JDebuggerUtils>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDebuggerUtilsClass,_di_JDebuggerUtils> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDebuggerUtils() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDebuggerUtilsClass,_di_JDebuggerUtils>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDebuggerUtils() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3981DBB7-CE54-4CDD-B9C5-D57D86F1084B}") JDeviceArchitectureCheckerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JDeviceArchitectureChecker __cdecl init() = 0 ;
	virtual void __cdecl check() = 0 ;
};

__interface  INTERFACE_UUID("{7CBD04BC-A051-4FE5-BDA1-BB9274840A67}") JDeviceArchitectureChecker  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDeviceArchitectureChecker : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDeviceArchitectureCheckerClass,_di_JDeviceArchitectureChecker>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDeviceArchitectureCheckerClass,_di_JDeviceArchitectureChecker> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDeviceArchitectureChecker() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDeviceArchitectureCheckerClass,_di_JDeviceArchitectureChecker>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDeviceArchitectureChecker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{03FCA454-E214-41B1-93B2-66CEA875FF35}") JFMXDialogFactoryClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JFMXDialogFactory __cdecl init() = 0 ;
	virtual _di_JFMXDialogFactory __cdecl getFactory() = 0 ;
};

__interface  INTERFACE_UUID("{F5811DCA-3A5F-4A62-A09D-0D53BB8A5814}") JFMXDialogFactory  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JFMXStandardDialog __cdecl createInputQueryDialog(_di_JFMXNativeActivity activity, int theme, Androidapi::Jni::Javatypes::_di_JString title, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* prompts, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* values, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* captions) = 0 ;
	virtual _di_JFMXStandardDialog __cdecl createMessageDialog(_di_JFMXNativeActivity activity, int theme, Androidapi::Jni::Javatypes::_di_JString msg, int dlgType, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* captions, int posButton, int negButton, int neutralButton) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFMXDialogFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDialogFactoryClass,_di_JFMXDialogFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDialogFactoryClass,_di_JFMXDialogFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFMXDialogFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDialogFactoryClass,_di_JFMXDialogFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFMXDialogFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7138130B-970C-447C-83D6-FE9A52C812A9}") JFMXDialogHelpersClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JFMXDialogHelpers __cdecl init() = 0 ;
	virtual void __cdecl generateAlertDialog(_di_JFMXNativeActivity activity, Androidapi::Jni::App::_di_JAlertDialog_Builder builder, Androidapi::Jni::Javatypes::_di_JString msg, int dlgType, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* captions, int posButton, int negButton, int neutralButton, _di_JFMXStandardDialog fmxdialog) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Widget::_di_JEditText>* __cdecl generateInputQuery(_di_JFMXNativeActivity activity, Androidapi::Jni::App::_di_JAlertDialog_Builder builder, Androidapi::Jni::Javatypes::_di_JString title, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* prompts, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* values, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* captions, _di_JFMXStandardDialog fmxdialog) = 0 ;
};

__interface  INTERFACE_UUID("{A28D79BB-09AD-4173-B82E-A1FB140FA98F}") JFMXDialogHelpers  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFMXDialogHelpers : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDialogHelpersClass,_di_JFMXDialogHelpers>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDialogHelpersClass,_di_JFMXDialogHelpers> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFMXDialogHelpers() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDialogHelpersClass,_di_JFMXDialogHelpers>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFMXDialogHelpers() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7C47781B-98A1-4A45-9F90-0B21A4A24FAC}") JFMXDialogListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{008E6099-5C9D-4FF3-9EDD-8AA87B6A52E2}") JFMXDialogListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onDialogClosed(int modalResult, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* values) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFMXDialogListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDialogListenerClass,_di_JFMXDialogListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDialogListenerClass,_di_JFMXDialogListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFMXDialogListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDialogListenerClass,_di_JFMXDialogListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFMXDialogListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1A06AAF5-F5F5-48C0-89EE-65A1F061DA95}") JFMXStandardDialogClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JFMXStandardDialog __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{30C9BF38-AE9D-486A-AAD9-885BDF3CC53E}") JFMXStandardDialog  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JFMXDialogListener __cdecl getListener() = 0 ;
	virtual int __cdecl getModalResult() = 0 ;
	virtual Androidapi::Jni::App::_di_JDialog __cdecl getRealDialog() = 0 ;
	virtual void __cdecl hide() = 0 ;
	virtual bool __cdecl isShown() = 0 ;
	virtual void __cdecl setListener(_di_JFMXDialogListener listener) = 0 ;
	virtual void __cdecl show() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFMXStandardDialog : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXStandardDialogClass,_di_JFMXStandardDialog>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXStandardDialogClass,_di_JFMXStandardDialog> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFMXStandardDialog() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXStandardDialogClass,_di_JFMXStandardDialog>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFMXStandardDialog() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D0013B08-E351-49D6-964F-829964750FCE}") JFMXDefaultStandardDialogClass  : public JFMXStandardDialogClass 
{
	HIDESBASE virtual _di_JFMXDefaultStandardDialog __cdecl init(_di_JFMXNativeActivity aActivity) = 0 ;
};

__interface  INTERFACE_UUID("{DE4F0684-2CCE-4683-8129-1A3670786BC8}") JFMXDefaultStandardDialog  : public JFMXStandardDialog 
{
	HIDESBASE virtual void __cdecl hide() = 0 ;
	HIDESBASE virtual bool __cdecl isShown() = 0 ;
	HIDESBASE virtual void __cdecl show() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFMXDefaultStandardDialog : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDefaultStandardDialogClass,_di_JFMXDefaultStandardDialog>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDefaultStandardDialogClass,_di_JFMXDefaultStandardDialog> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFMXDefaultStandardDialog() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDefaultStandardDialogClass,_di_JFMXDefaultStandardDialog>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFMXDefaultStandardDialog() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{03590861-A4BD-4AF8-AD1A-C68FE14F26EB}") JFMXDefaultAlertDialogClass  : public JFMXDefaultStandardDialogClass 
{
	HIDESBASE virtual _di_JFMXDefaultAlertDialog __cdecl init(_di_JFMXNativeActivity activity, int theme, Androidapi::Jni::Javatypes::_di_JString msg, int dlgType, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* captions, int posButton, int negButton, int neutralButton) = 0 ;
};

__interface  INTERFACE_UUID("{0A269919-5978-4AD4-BABE-6A576A886F78}") JFMXDefaultAlertDialog  : public JFMXDefaultStandardDialog 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFMXDefaultAlertDialog : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDefaultAlertDialogClass,_di_JFMXDefaultAlertDialog>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDefaultAlertDialogClass,_di_JFMXDefaultAlertDialog> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFMXDefaultAlertDialog() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDefaultAlertDialogClass,_di_JFMXDefaultAlertDialog>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFMXDefaultAlertDialog() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C4CC93D3-CEC9-4DD0-B23D-8219344FB73D}") JFMXDefaultDialogFactoryClass  : public JFMXDialogFactoryClass 
{
	HIDESBASE virtual _di_JFMXDefaultDialogFactory __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{6453A528-226B-4C72-9762-694413D677FB}") JFMXDefaultDialogFactory  : public JFMXDialogFactory 
{
	HIDESBASE virtual _di_JFMXStandardDialog __cdecl createInputQueryDialog(_di_JFMXNativeActivity activity, int theme, Androidapi::Jni::Javatypes::_di_JString title, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* prompts, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* values, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* captions) = 0 ;
	HIDESBASE virtual _di_JFMXStandardDialog __cdecl createMessageDialog(_di_JFMXNativeActivity activity, int theme, Androidapi::Jni::Javatypes::_di_JString msg, int dlgType, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* captions, int posButton, int negButton, int neutralButton) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFMXDefaultDialogFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDefaultDialogFactoryClass,_di_JFMXDefaultDialogFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDefaultDialogFactoryClass,_di_JFMXDefaultDialogFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFMXDefaultDialogFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDefaultDialogFactoryClass,_di_JFMXDefaultDialogFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFMXDefaultDialogFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EDB8636C-4BCF-4366-AA83-2D897866C3E4}") JFMXDefaultDialogFragmentClass  : public Androidapi::Jni::App::JDialogFragmentClass 
{
	HIDESBASE virtual _di_JFMXDefaultDialogFragment __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{D224B738-0D7A-4E8C-ADF3-54CE72EF6756}") JFMXDefaultDialogFragment  : public Androidapi::Jni::App::JDialogFragment 
{
	HIDESBASE virtual void __cdecl onCreate(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	HIDESBASE virtual Androidapi::Jni::App::_di_JDialog __cdecl onCreateDialog(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	HIDESBASE virtual void __cdecl onDismiss(Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface dialog) = 0 ;
	virtual void __cdecl setDialog(_di_JFMXDefaultStandardDialog dialog) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFMXDefaultDialogFragment : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDefaultDialogFragmentClass,_di_JFMXDefaultDialogFragment>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDefaultDialogFragmentClass,_di_JFMXDefaultDialogFragment> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFMXDefaultDialogFragment() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDefaultDialogFragmentClass,_di_JFMXDefaultDialogFragment>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFMXDefaultDialogFragment() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{DBDAE8E2-BDCA-4EC0-A786-9EEE6B8CFCE1}") JFMXDefaultInputQueryDialogClass  : public JFMXDefaultStandardDialogClass 
{
	HIDESBASE virtual _di_JFMXDefaultInputQueryDialog __cdecl init(_di_JFMXNativeActivity activity, int theme, Androidapi::Jni::Javatypes::_di_JString title, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* prompts, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* values, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* captions) = 0 ;
};

__interface  INTERFACE_UUID("{C041BD5B-0A58-4CF1-8A91-B2B15DF013D7}") JFMXDefaultInputQueryDialog  : public JFMXDefaultStandardDialog 
{
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getValues() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFMXDefaultInputQueryDialog : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDefaultInputQueryDialogClass,_di_JFMXDefaultInputQueryDialog>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDefaultInputQueryDialogClass,_di_JFMXDefaultInputQueryDialog> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFMXDefaultInputQueryDialog() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXDefaultInputQueryDialogClass,_di_JFMXDefaultInputQueryDialog>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFMXDefaultInputQueryDialog() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{90C7255E-64D1-4948-979C-4E7BB037AC02}") JFormViewClass  : public Androidapi::Jni::Graphicscontentviewtext::JSurfaceViewClass 
{
	HIDESBASE virtual _di_JFormView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

__interface  INTERFACE_UUID("{BCBFA123-07D3-41A6-BFAB-41D77886F589}") JFormView  : public Androidapi::Jni::Graphicscontentviewtext::JSurfaceView 
{
	HIDESBASE virtual bool __cdecl onTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	virtual void __cdecl setListener(_di_JFormViewListener listener) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFormView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFormViewClass,_di_JFormView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFormViewClass,_di_JFormView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFormView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFormViewClass,_di_JFormView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFormView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1AA438C5-4A64-4043-892F-0380FA658A09}") JFormViewListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{BF611734-2D29-4D3D-83DD-53F9D948470D}") JFormViewListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onSizeChanged(int newWidth, int newHeight, int oldWidth, int oldHeight) = 0 ;
	virtual bool __cdecl onTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFormViewListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFormViewListenerClass,_di_JFormViewListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFormViewListenerClass,_di_JFormViewListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFormViewListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFormViewListenerClass,_di_JFormViewListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFormViewListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{180320E3-73FD-456C-9F6C-83F20DCB73E1}") JFullScreenManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetSTATE_NAV() = 0 ;
	virtual int __cdecl _GetSTATE_STAT_NAV() = 0 ;
	virtual int __cdecl _GetSTATE_Z1() = 0 ;
	virtual int __cdecl _GetSTATE_Z2() = 0 ;
	HIDESBASE virtual _di_JFullScreenManager __cdecl init(Androidapi::Jni::App::_di_JActivity activity) = 0 ;
	__property int STATE_NAV = {read=_GetSTATE_NAV};
	__property int STATE_STAT_NAV = {read=_GetSTATE_STAT_NAV};
	__property int STATE_Z1 = {read=_GetSTATE_Z1};
	__property int STATE_Z2 = {read=_GetSTATE_Z2};
};

__interface  INTERFACE_UUID("{22E5507E-E778-4538-BF16-062E81ADB97F}") JFullScreenManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl callback() = 0 ;
	virtual int __cdecl changeState(int transition) = 0 ;
	virtual int __cdecl getState() = 0 ;
	virtual bool __cdecl getStatusBarVisibility() = 0 ;
	virtual bool __cdecl getSystemUIVisibility() = 0 ;
	virtual void __cdecl hideStatusBar() = 0 ;
	virtual void __cdecl hideSystemUI() = 0 ;
	virtual void __cdecl initFullScreenFSM() = 0 ;
	virtual void __cdecl setStateCallback(int state, _di_JOnFullScreenStateChangedListener callback) = 0 /* overload */;
	virtual void __cdecl setStateCallback(_di_JOnFullScreenStateChangedListener callback) = 0 /* overload */;
	virtual void __cdecl setStatusBarVisibility(bool visible) = 0 ;
	virtual void __cdecl setSystemUIVisibility(bool visible) = 0 ;
	virtual void __cdecl showStatusBar() = 0 ;
	virtual void __cdecl showSystemUI() = 0 ;
	virtual void __cdecl unInitFullScreenFSM() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFullScreenManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFullScreenManagerClass,_di_JFullScreenManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFullScreenManagerClass,_di_JFullScreenManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFullScreenManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFullScreenManagerClass,_di_JFullScreenManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFullScreenManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4D3534F2-A291-4AEC-9F71-56FE395A3927}") JOnFullScreenStateChangedListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{8EE73E7B-9BC0-4983-AFBC-9B133DB3F73B}") JOnFullScreenStateChangedListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl stateChanged(int oldState, int newState) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnFullScreenStateChangedListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnFullScreenStateChangedListenerClass,_di_JOnFullScreenStateChangedListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnFullScreenStateChangedListenerClass,_di_JOnFullScreenStateChangedListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnFullScreenStateChangedListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnFullScreenStateChangedListenerClass,_di_JOnFullScreenStateChangedListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnFullScreenStateChangedListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{DC6EC615-5DEF-4BFC-88A7-FA31017D974B}") JJavaGeocoderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JJavaGeocoder __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext Con) = 0 ;
};

__interface  INTERFACE_UUID("{A6AF9F65-04F2-4AE6-A75A-ABE841B23DD2}") JJavaGeocoder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Location::_di_JGeocoder __cdecl _GetInstanceOfGeocoder() = 0 ;
	virtual void __cdecl _SetInstanceOfGeocoder(Androidapi::Jni::Location::_di_JGeocoder Value) = 0 ;
	__property Androidapi::Jni::Location::_di_JGeocoder InstanceOfGeocoder = {read=_GetInstanceOfGeocoder, write=_SetInstanceOfGeocoder};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJJavaGeocoder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJavaGeocoderClass,_di_JJavaGeocoder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJavaGeocoderClass,_di_JJavaGeocoder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJJavaGeocoder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJavaGeocoderClass,_di_JJavaGeocoder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJJavaGeocoder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{37A38DF0-02BE-4E06-8384-6281C577BDE6}") JOnKeyboardStateChangedListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{F85EB0C6-02EB-4DF3-9E2E-B320BA607CD3}") JOnKeyboardStateChangedListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onVirtualKeyboardFrameChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JRect newFrame) = 0 ;
	virtual void __cdecl onVirtualKeyboardWillHidden() = 0 ;
	virtual void __cdecl onVirtualKeyboardWillShown() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnKeyboardStateChangedListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnKeyboardStateChangedListenerClass,_di_JOnKeyboardStateChangedListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnKeyboardStateChangedListenerClass,_di_JOnKeyboardStateChangedListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnKeyboardStateChangedListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnKeyboardStateChangedListenerClass,_di_JOnKeyboardStateChangedListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnKeyboardStateChangedListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A757779B-BA0D-4139-8D7C-54D6A06620A8}") JVirtualKeyboardClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JVirtualKeyboard __cdecl init(_di_JFMXNativeActivity activity) = 0 ;
};

__interface  INTERFACE_UUID("{51662C0B-E5A0-4519-B09F-4131541C3442}") JVirtualKeyboard  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl addOnKeyboardStateChangedListener(_di_JOnKeyboardStateChangedListener listener) = 0 ;
	virtual _di_JVirtualKeyboardFrameObserver __cdecl getVirtualKeyboardFrameObserver() = 0 ;
	virtual bool __cdecl hide() = 0 /* overload */;
	virtual bool __cdecl hide(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 /* overload */;
	virtual bool __cdecl isVirtualKeyboardShown() = 0 ;
	virtual void __cdecl onVirtualKeyboardFrameChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JRect newFrame) = 0 ;
	virtual void __cdecl removeOnKeyboardStateChangedListener(_di_JOnKeyboardStateChangedListener listener) = 0 ;
	virtual bool __cdecl showFor(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVirtualKeyboard : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVirtualKeyboardClass,_di_JVirtualKeyboard>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVirtualKeyboardClass,_di_JVirtualKeyboard> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVirtualKeyboard() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVirtualKeyboardClass,_di_JVirtualKeyboard>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVirtualKeyboard() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{66F0AE1C-C8DA-4A13-AAEA-E3A0AC1993E5}") JVirtualKeyboardFrameObserverClass  : public Androidapi::Jni::Widget::JPopupWindowClass 
{
	
};

__interface  INTERFACE_UUID("{6CF8ED4B-C6A6-433C-B6EE-6B8AC4DD94B6}") JVirtualKeyboardFrameObserver  : public Androidapi::Jni::Widget::JPopupWindow 
{
	virtual bool __cdecl isVirtualKeyboardShown() = 0 ;
	virtual void __cdecl onLayoutChange(Androidapi::Jni::Graphicscontentviewtext::_di_JView v, int left, int top, int right, int bottom, int oldLeft, int oldTop, int oldRight, int oldBottom) = 0 ;
	virtual void __cdecl setListener(Androidapi::Jni::Javatypes::_di_JObject listener) = 0 ;
	virtual void __cdecl stopObservation() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVirtualKeyboardFrameObserver : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVirtualKeyboardFrameObserverClass,_di_JVirtualKeyboardFrameObserver>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVirtualKeyboardFrameObserverClass,_di_JVirtualKeyboardFrameObserver> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVirtualKeyboardFrameObserver() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVirtualKeyboardFrameObserverClass,_di_JVirtualKeyboardFrameObserver>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVirtualKeyboardFrameObserver() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F4FEB220-69F8-42F6-B16C-8EE14637E5E8}") JCameraChangeListenerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JCameraChangeListener __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{77995FF0-3B8E-4B7E-96DB-DD36E3359227}") JCameraChangeListener  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual float __cdecl getBearing() = 0 ;
	virtual double __cdecl getLatitude() = 0 ;
	virtual double __cdecl getLongitude() = 0 ;
	virtual float __cdecl getTilt() = 0 ;
	virtual float __cdecl getZoom() = 0 ;
	virtual void __cdecl onCameraChange(Androidapi::Jni::Playservices::Maps::_di_JCameraPosition position) = 0 ;
	virtual void __cdecl setCallback(_di_JCameraChangeListener_Callback callback) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCameraChangeListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraChangeListenerClass,_di_JCameraChangeListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraChangeListenerClass,_di_JCameraChangeListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCameraChangeListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraChangeListenerClass,_di_JCameraChangeListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCameraChangeListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B967D9A3-3A71-43F2-8603-7198391440EF}") JCameraChangeListener_CallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{6EBC7047-A849-46A4-B610-B453B3876038}") JCameraChangeListener_Callback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCameraChange(_di_JCameraChangeListener listener) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCameraChangeListener_Callback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraChangeListener_CallbackClass,_di_JCameraChangeListener_Callback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraChangeListener_CallbackClass,_di_JCameraChangeListener_Callback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCameraChangeListener_Callback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraChangeListener_CallbackClass,_di_JCameraChangeListener_Callback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCameraChangeListener_Callback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1C7E8661-598A-495E-B93F-F7F8ABFDE659}") JMapViewWithGesturesClass  : public Androidapi::Jni::Playservices::Maps::JMapViewClass 
{
	HIDESBASE virtual _di_JMapViewWithGestures __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Playservices::Maps::_di_JGoogleMapOptions options) = 0 ;
};

__interface  INTERFACE_UUID("{619B12B4-6B8D-4FF0-B1E6-89E864F0C073}") JMapViewWithGestures  : public Androidapi::Jni::Playservices::Maps::JMapView 
{
	HIDESBASE virtual bool __cdecl dispatchTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent ev) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JGestureDetector __cdecl getGestureDetector() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMapViewWithGestures : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMapViewWithGesturesClass,_di_JMapViewWithGestures>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMapViewWithGesturesClass,_di_JMapViewWithGestures> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMapViewWithGestures() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMapViewWithGesturesClass,_di_JMapViewWithGestures>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMapViewWithGestures() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{66D17071-77BC-4881-9546-0F803D781E41}") JFMXMediaLibraryClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetACTION_CROP_IMAGE() = 0 ;
	virtual int __cdecl _GetACTION_TAKE_IMAGE_FROM_CAMERA() = 0 ;
	virtual int __cdecl _GetACTION_TAKE_IMAGE_FROM_LIBRARY() = 0 ;
	HIDESBASE virtual _di_JFMXMediaLibrary __cdecl init(Androidapi::Jni::App::_di_JActivity activity) = 0 ;
	virtual bool __cdecl isRequestForTakingImage(int requestCode) = 0 ;
	__property int ACTION_CROP_IMAGE = {read=_GetACTION_CROP_IMAGE};
	__property int ACTION_TAKE_IMAGE_FROM_CAMERA = {read=_GetACTION_TAKE_IMAGE_FROM_CAMERA};
	__property int ACTION_TAKE_IMAGE_FROM_LIBRARY = {read=_GetACTION_TAKE_IMAGE_FROM_LIBRARY};
};

__interface  INTERFACE_UUID("{FA55B1EF-8E7E-4D22-B835-14F0B0B4C375}") JFMXMediaLibrary  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getLastPhotoName() = 0 ;
	virtual void __cdecl handleTakingPhotoRequest(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent data, int requestCode) = 0 ;
	virtual void __cdecl onRestoreInstanceState(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onSaveInstanceState(Androidapi::Jni::Os::_di_JBundle outState) = 0 ;
	virtual void __cdecl setListener(_di_JFMXMediaLibraryListener listener) = 0 ;
	virtual void __cdecl takeImageFromCamera(int maxWidth, int maxHeight, bool editable, bool needSaveToAlbum) = 0 ;
	virtual void __cdecl takeImageFromLibrary(int maxWidth, int maxHeight, bool editable) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFMXMediaLibrary : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXMediaLibraryClass,_di_JFMXMediaLibrary>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXMediaLibraryClass,_di_JFMXMediaLibrary> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFMXMediaLibrary() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXMediaLibraryClass,_di_JFMXMediaLibrary>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFMXMediaLibrary() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A9A14D40-E569-4D87-AA19-6759376B8E85}") JFMXMediaLibraryListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{A74DD810-7822-4CD1-A67A-ED471D7F136F}") JFMXMediaLibraryListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onMediaLibraryAccept(int requestCode) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFMXMediaLibraryListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXMediaLibraryListenerClass,_di_JFMXMediaLibraryListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXMediaLibraryListenerClass,_di_JFMXMediaLibraryListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFMXMediaLibraryListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXMediaLibraryListenerClass,_di_JFMXMediaLibraryListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFMXMediaLibraryListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AA250306-1C54-4F37-BDE4-BF311C544025}") JUtilsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JUtils __cdecl init() = 0 ;
	virtual int __cdecl copyStream(Androidapi::Jni::Javatypes::_di_JInputStream input, Androidapi::Jni::Javatypes::_di_JOutputStream output) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JFile __cdecl getAlbumDir(Androidapi::Jni::Javatypes::_di_JString albumName) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JFile __cdecl getPhotosDir() = 0 ;
};

__interface  INTERFACE_UUID("{0B0C8119-2A9F-480F-AE06-E17CE12DE684}") JUtils  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJUtils : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JUtilsClass,_di_JUtils>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JUtilsClass,_di_JUtils> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJUtils() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JUtilsClass,_di_JUtils>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJUtils() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9F35AC6E-96AD-4E73-BFC2-23B3ACB3F01E}") JBasePickerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JBasePicker __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{FB1961D2-65AB-4224-B8D9-2D48AA436652}") JBasePicker  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl hide() = 0 ;
	virtual bool __cdecl isShown() = 0 ;
	virtual void __cdecl setTheme(int theme) = 0 ;
	virtual void __cdecl show() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBasePicker : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBasePickerClass,_di_JBasePicker>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBasePickerClass,_di_JBasePicker> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBasePicker() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBasePickerClass,_di_JBasePicker>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBasePicker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AEF4DB42-B726-4D97-923F-EBACCD26AE68}") JBaseDateTimePickerClass  : public JBasePickerClass 
{
	HIDESBASE virtual _di_JBaseDateTimePicker __cdecl init() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JTimeZone __cdecl getGMTTimeZone() = 0 ;
};

__interface  INTERFACE_UUID("{93D09E24-E245-43DE-B992-77C7BB27C672}") JBaseDateTimePicker  : public JBasePicker 
{
	virtual Androidapi::Jni::Javatypes::_di_JDate __cdecl getDate() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JDate __cdecl getTime() = 0 ;
	virtual bool __cdecl hasListener() = 0 ;
	virtual void __cdecl setDate(__int64 timeInMillis) = 0 ;
	virtual void __cdecl setListener(_di_JOnDateTimeChangedListener listener) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBaseDateTimePicker : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseDateTimePickerClass,_di_JBaseDateTimePicker>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseDateTimePickerClass,_di_JBaseDateTimePicker> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBaseDateTimePicker() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseDateTimePickerClass,_di_JBaseDateTimePicker>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBaseDateTimePicker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{960A0BD3-E971-4206-B089-ED555BA8F736}") JBaseListPickerClass  : public JBasePickerClass 
{
	HIDESBASE virtual _di_JBaseListPicker __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{E7D99458-E717-4FDB-8CEB-8288A81AC9B4}") JBaseListPicker  : public JBasePicker 
{
	virtual bool __cdecl hasListener() = 0 ;
	virtual void __cdecl setItemIndex(int itemIndex) = 0 ;
	virtual void __cdecl setItems(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JCharSequence>* items) = 0 ;
	virtual void __cdecl setListener(_di_JOnItemChangedListener listener) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBaseListPicker : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseListPickerClass,_di_JBaseListPicker>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseListPickerClass,_di_JBaseListPicker> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBaseListPicker() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseListPickerClass,_di_JBaseListPicker>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBaseListPicker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{235431A6-84D7-48A1-9194-9A44E118294E}") JBasePickersFactoryClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JBasePickersFactory __cdecl init() = 0 ;
	virtual _di_JBasePickersFactory __cdecl getFactory() = 0 ;
};

__interface  INTERFACE_UUID("{F192F199-A07C-41CC-A4A4-8DCC857B26EA}") JBasePickersFactory  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JBaseDateTimePicker __cdecl createDatePicker(_di_JFMXNativeActivity activity) = 0 ;
	virtual _di_JBaseListPicker __cdecl createListPicker(_di_JFMXNativeActivity activity) = 0 ;
	virtual _di_JBaseDateTimePicker __cdecl createTimePicker(_di_JFMXNativeActivity activity) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBasePickersFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBasePickersFactoryClass,_di_JBasePickersFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBasePickersFactoryClass,_di_JBasePickersFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBasePickersFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBasePickersFactoryClass,_di_JBasePickersFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBasePickersFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{311AD0A1-F9EC-484D-B7D6-AEC67E5BFC55}") JGeneratorPickerIDClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JGeneratorPickerID __cdecl init() = 0 ;
	virtual int __cdecl getUniqueID() = 0 ;
};

__interface  INTERFACE_UUID("{3FE9FE79-740A-4D21-AE66-E8C9C2F0517F}") JGeneratorPickerID  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGeneratorPickerID : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGeneratorPickerIDClass,_di_JGeneratorPickerID>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGeneratorPickerIDClass,_di_JGeneratorPickerID> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGeneratorPickerID() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGeneratorPickerIDClass,_di_JGeneratorPickerID>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGeneratorPickerID() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6253D5BE-9035-4894-B479-2B91B1496180}") JOnDateTimeChangedListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{3BE7DC7B-92F9-4B5D-BBC4-B49FAE5CE96E}") JOnDateTimeChangedListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onDateChanged(Androidapi::Jni::Javatypes::_di_JDate date) = 0 ;
	virtual void __cdecl onHide() = 0 ;
	virtual void __cdecl onShow() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnDateTimeChangedListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnDateTimeChangedListenerClass,_di_JOnDateTimeChangedListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnDateTimeChangedListenerClass,_di_JOnDateTimeChangedListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnDateTimeChangedListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnDateTimeChangedListenerClass,_di_JOnDateTimeChangedListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnDateTimeChangedListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1A8B5BC7-25C3-43B9-9E0E-B144BDC49CC5}") JOnItemChangedListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{BC0BDDA3-53FD-4BA8-9E3D-B17F647345C6}") JOnItemChangedListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onHide() = 0 ;
	virtual void __cdecl onItemChanged(int itemIndex) = 0 ;
	virtual void __cdecl onShow() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnItemChangedListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnItemChangedListenerClass,_di_JOnItemChangedListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnItemChangedListenerClass,_di_JOnItemChangedListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnItemChangedListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnItemChangedListenerClass,_di_JOnItemChangedListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnItemChangedListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BA993453-9297-45B2-B496-33DF58EC656E}") Jdefaults_DatePickerFragmentClass  : public Androidapi::Jni::App::JDialogFragmentClass 
{
	HIDESBASE virtual _di_Jdefaults_DatePickerFragment __cdecl init(int year, int month, int day) = 0 ;
};

__interface  INTERFACE_UUID("{1E90BA78-2E8D-409C-9D3E-674B9C51E129}") Jdefaults_DatePickerFragment  : public Androidapi::Jni::App::JDialogFragment 
{
	HIDESBASE virtual Androidapi::Jni::App::_di_JDialog __cdecl onCreateDialog(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onDateSet(Androidapi::Jni::Widget::_di_JDatePicker view, int year, int month, int day) = 0 ;
	HIDESBASE virtual void __cdecl onStart() = 0 ;
	HIDESBASE virtual void __cdecl onStop() = 0 ;
	virtual void __cdecl setDate(int year, int month, int day) = 0 ;
	virtual void __cdecl setHasDateConstraints(bool hasDateConstraints) = 0 ;
	virtual void __cdecl setListener(_di_JOnDateTimeChangedListener listener) = 0 ;
	virtual void __cdecl setMaxDate(Androidapi::Jni::Javatypes::_di_JDate date) = 0 ;
	virtual void __cdecl setMinDate(Androidapi::Jni::Javatypes::_di_JDate date) = 0 ;
	virtual void __cdecl setTheme(int theme) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJdefaults_DatePickerFragment : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jdefaults_DatePickerFragmentClass,_di_Jdefaults_DatePickerFragment>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jdefaults_DatePickerFragmentClass,_di_Jdefaults_DatePickerFragment> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJdefaults_DatePickerFragment() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jdefaults_DatePickerFragmentClass,_di_Jdefaults_DatePickerFragment>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJdefaults_DatePickerFragment() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4D36CFEF-1AD9-4C50-8992-32E13346574D}") JDefaultDatePickerClass  : public JBaseDateTimePickerClass 
{
	HIDESBASE virtual _di_JDefaultDatePicker __cdecl init(_di_JFMXNativeActivity activity) = 0 ;
};

__interface  INTERFACE_UUID("{E5CB7805-4603-44A2-A088-2F0D03E061ED}") JDefaultDatePicker  : public JBaseDateTimePicker 
{
	HIDESBASE virtual void __cdecl hide() = 0 ;
	HIDESBASE virtual bool __cdecl isShown() = 0 ;
	HIDESBASE virtual void __cdecl setListener(_di_JOnDateTimeChangedListener listener) = 0 ;
	HIDESBASE virtual void __cdecl setTheme(int theme) = 0 ;
	HIDESBASE virtual void __cdecl show() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDefaultDatePicker : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDefaultDatePickerClass,_di_JDefaultDatePicker>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDefaultDatePickerClass,_di_JDefaultDatePicker> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDefaultDatePicker() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDefaultDatePickerClass,_di_JDefaultDatePicker>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDefaultDatePicker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{926BA109-6E51-43DD-A672-75FB33576476}") JDefaultListPickerClass  : public JBaseListPickerClass 
{
	HIDESBASE virtual _di_JDefaultListPicker __cdecl init(_di_JFMXNativeActivity activity) = 0 ;
};

__interface  INTERFACE_UUID("{15AE1BAA-54EF-42B3-B032-BFE66A11ED01}") JDefaultListPicker  : public JBaseListPicker 
{
	HIDESBASE virtual void __cdecl hide() = 0 ;
	HIDESBASE virtual bool __cdecl isShown() = 0 ;
	HIDESBASE virtual void __cdecl setItemIndex(int itemIndex) = 0 ;
	HIDESBASE virtual void __cdecl setItems(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JCharSequence>* items) = 0 ;
	HIDESBASE virtual void __cdecl setListener(_di_JOnItemChangedListener listener) = 0 ;
	HIDESBASE virtual void __cdecl setTheme(int theme) = 0 ;
	HIDESBASE virtual void __cdecl show() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDefaultListPicker : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDefaultListPickerClass,_di_JDefaultListPicker>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDefaultListPickerClass,_di_JDefaultListPicker> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDefaultListPicker() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDefaultListPickerClass,_di_JDefaultListPicker>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDefaultListPicker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{87462100-5B6E-4DAE-B264-A8FC84E3AB3E}") JDefaultPickersFactoryClass  : public JBasePickersFactoryClass 
{
	HIDESBASE virtual _di_JDefaultPickersFactory __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{FD970141-B89F-4A1E-8781-A3D6A5C0DB67}") JDefaultPickersFactory  : public JBasePickersFactory 
{
	HIDESBASE virtual _di_JBaseDateTimePicker __cdecl createDatePicker(_di_JFMXNativeActivity activity) = 0 ;
	HIDESBASE virtual _di_JBaseListPicker __cdecl createListPicker(_di_JFMXNativeActivity activity) = 0 ;
	HIDESBASE virtual _di_JBaseDateTimePicker __cdecl createTimePicker(_di_JFMXNativeActivity activity) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDefaultPickersFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDefaultPickersFactoryClass,_di_JDefaultPickersFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDefaultPickersFactoryClass,_di_JDefaultPickersFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDefaultPickersFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDefaultPickersFactoryClass,_di_JDefaultPickersFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDefaultPickersFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F58D42AA-5303-40D1-9A50-EFA6079B6B70}") JDefaultTimePickerClass  : public JBaseDateTimePickerClass 
{
	HIDESBASE virtual _di_JDefaultTimePicker __cdecl init(_di_JFMXNativeActivity activity) = 0 ;
};

__interface  INTERFACE_UUID("{52F03A05-2EF3-4114-A5E6-D3B2FF4E4BBC}") JDefaultTimePicker  : public JBaseDateTimePicker 
{
	HIDESBASE virtual void __cdecl hide() = 0 ;
	HIDESBASE virtual bool __cdecl isShown() = 0 ;
	HIDESBASE virtual void __cdecl setListener(_di_JOnDateTimeChangedListener listener) = 0 ;
	HIDESBASE virtual void __cdecl setTheme(int theme) = 0 ;
	HIDESBASE virtual void __cdecl show() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDefaultTimePicker : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDefaultTimePickerClass,_di_JDefaultTimePicker>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDefaultTimePickerClass,_di_JDefaultTimePicker> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDefaultTimePicker() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDefaultTimePickerClass,_di_JDefaultTimePicker>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDefaultTimePicker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E96F3E38-4949-4F21-B722-AD1AA5968AEB}") Jdefaults_ListPickerFragmentClass  : public Androidapi::Jni::App::JDialogFragmentClass 
{
	HIDESBASE virtual _di_Jdefaults_ListPickerFragment __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{FBCD51E2-88FE-4962-B0A4-5CE647E66659}") Jdefaults_ListPickerFragment  : public Androidapi::Jni::App::JDialogFragment 
{
	HIDESBASE virtual Androidapi::Jni::App::_di_JDialog __cdecl onCreateDialog(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	HIDESBASE virtual void __cdecl onDismiss(Androidapi::Jni::Graphicscontentviewtext::_di_JDialogInterface dialog) = 0 ;
	HIDESBASE virtual void __cdecl onStart() = 0 ;
	virtual void __cdecl setTheme(int theme) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJdefaults_ListPickerFragment : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jdefaults_ListPickerFragmentClass,_di_Jdefaults_ListPickerFragment>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jdefaults_ListPickerFragmentClass,_di_Jdefaults_ListPickerFragment> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJdefaults_ListPickerFragment() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jdefaults_ListPickerFragmentClass,_di_Jdefaults_ListPickerFragment>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJdefaults_ListPickerFragment() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1DF31EF0-1207-48B7-8AF2-B892DD120EFB}") Jdefaults_TimePickerFragmentClass  : public Androidapi::Jni::App::JDialogFragmentClass 
{
	HIDESBASE virtual _di_Jdefaults_TimePickerFragment __cdecl init(int hour, int min) = 0 ;
};

__interface  INTERFACE_UUID("{FA22FC03-0530-463C-8612-59B2266C92EC}") Jdefaults_TimePickerFragment  : public Androidapi::Jni::App::JDialogFragment 
{
	HIDESBASE virtual Androidapi::Jni::App::_di_JDialog __cdecl onCreateDialog(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	HIDESBASE virtual void __cdecl onStart() = 0 ;
	HIDESBASE virtual void __cdecl onStop() = 0 ;
	virtual void __cdecl onTimeSet(Androidapi::Jni::Widget::_di_JTimePicker view, int hourOfDay, int minute) = 0 ;
	virtual void __cdecl setListener(_di_JOnDateTimeChangedListener listener) = 0 ;
	virtual void __cdecl setTheme(int theme) = 0 ;
	virtual void __cdecl setTime(int hour, int min) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJdefaults_TimePickerFragment : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jdefaults_TimePickerFragmentClass,_di_Jdefaults_TimePickerFragment>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jdefaults_TimePickerFragmentClass,_di_Jdefaults_TimePickerFragment> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJdefaults_TimePickerFragment() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jdefaults_TimePickerFragmentClass,_di_Jdefaults_TimePickerFragment>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJdefaults_TimePickerFragment() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D3239720-8053-483A-8E21-6B866406B512}") JIAPSecurityClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JIAPSecurity __cdecl init() = 0 ;
	virtual bool __cdecl verifyPurchase(Androidapi::Jni::Javatypes::_di_JString base64PublicKey, Androidapi::Jni::Javatypes::_di_JString signedData, Androidapi::Jni::Javatypes::_di_JString signature) = 0 ;
};

__interface  INTERFACE_UUID("{288E1DF2-92BC-4F89-808A-A3EF90C77280}") JIAPSecurity  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJIAPSecurity : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIAPSecurityClass,_di_JIAPSecurity>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIAPSecurityClass,_di_JIAPSecurity> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJIAPSecurity() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIAPSecurityClass,_di_JIAPSecurity>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJIAPSecurity() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7130BF07-0018-48B9-975B-DA5119E0B2FE}") JCharCaseClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JCharCase __cdecl _GetLOWER_CASE() = 0 ;
	virtual _di_JCharCase __cdecl _GetNORMAL() = 0 ;
	virtual _di_JCharCase __cdecl _GetUPPER_CASE() = 0 ;
	HIDESBASE virtual _di_JCharCase __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JCharCase>* __cdecl values() = 0 ;
	__property _di_JCharCase LOWER_CASE = {read=_GetLOWER_CASE};
	__property _di_JCharCase NORMAL = {read=_GetNORMAL};
	__property _di_JCharCase UPPER_CASE = {read=_GetUPPER_CASE};
};

__interface  INTERFACE_UUID("{75C5997A-7992-4083-A76E-2B7BF0E2F8CA}") JCharCase  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCharCase : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCharCaseClass,_di_JCharCase>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCharCaseClass,_di_JCharCase> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCharCase() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCharCaseClass,_di_JCharCase>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCharCase() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B9632454-D051-4E9F-B7E8-8A92EFDE2030}") JFMXEditTextClass  : public Androidapi::Jni::Widget::JEditTextClass 
{
	HIDESBASE virtual _di_JFMXEditText __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JFMXEditText __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JFMXEditText __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{FF39BA82-C7A1-4D7C-B861-513A4DE18C90}") JFMXEditText  : public Androidapi::Jni::Widget::JEditText 
{
	virtual void __cdecl addTextListener(_di_JFMXTextListener textListener) = 0 ;
	virtual _di_JCharCase __cdecl getCharCase() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getFilterChars() = 0 ;
	virtual _di_JVirtualKeyboardType __cdecl getKeyboardType() = 0 ;
	virtual int __cdecl getMaxLength() = 0 ;
	virtual _di_JReturnKeyType __cdecl getReturnKeyType() = 0 ;
	virtual bool __cdecl hasFilterChars() = 0 ;
	virtual bool __cdecl isMultiline() = 0 ;
	virtual bool __cdecl isPassword() = 0 ;
	virtual bool __cdecl isReadOnly() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JInputConnection __cdecl onCreateInputConnection(Androidapi::Jni::Graphicscontentviewtext::_di_JEditorInfo outAttrs) = 0 ;
	HIDESBASE virtual void __cdecl onEditorAction(int actionCode) = 0 ;
	HIDESBASE virtual bool __cdecl onTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	virtual void __cdecl removeTextListener(_di_JFMXTextListener textListener) = 0 ;
	virtual void __cdecl setCharCase(_di_JCharCase charCase) = 0 ;
	virtual void __cdecl setFilterChars(Androidapi::Jni::Javatypes::_di_JString filterChars) = 0 ;
	virtual void __cdecl setKeyboardType(_di_JVirtualKeyboardType keyboardType) = 0 ;
	virtual void __cdecl setMaxLength(int maxLength) = 0 ;
	virtual void __cdecl setMultiline(bool multiline) = 0 ;
	virtual void __cdecl setNeededToShowSoftKeyboardOnTouch(bool neededToShowSoftKeyboardOnTouch) = 0 ;
	virtual void __cdecl setPassword(bool password) = 0 ;
	virtual void __cdecl setReadOnly(bool readOnly) = 0 ;
	virtual void __cdecl setReturnKeyType(_di_JReturnKeyType returnKeyType) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFMXEditText : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXEditTextClass,_di_JFMXEditText>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXEditTextClass,_di_JFMXEditText> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFMXEditText() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXEditTextClass,_di_JFMXEditText>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFMXEditText() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A8C204B6-E91D-43C9-AAE6-A8F638AC8B0B}") JFMXTextListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{343503D5-CA05-4DAE-AABF-C112202B9CFA}") JFMXTextListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onComposingText(int beginPosition, int endPosition) = 0 ;
	virtual void __cdecl onEditorAction(int actionCode) = 0 ;
	virtual void __cdecl onTextUpdated(Androidapi::Jni::Javatypes::_di_JCharSequence text, int cursorPosition) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFMXTextListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXTextListenerClass,_di_JFMXTextListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXTextListenerClass,_di_JFMXTextListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFMXTextListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFMXTextListenerClass,_di_JFMXTextListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFMXTextListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B83238CE-4A71-4330-AB5C-D020E207B74E}") JReturnKeyTypeClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JReturnKeyType __cdecl _GetDONE() = 0 ;
	virtual _di_JReturnKeyType __cdecl _GetENTER() = 0 ;
	virtual _di_JReturnKeyType __cdecl _GetGO() = 0 ;
	virtual _di_JReturnKeyType __cdecl _GetNEXT() = 0 ;
	virtual _di_JReturnKeyType __cdecl _GetSEARCH() = 0 ;
	virtual _di_JReturnKeyType __cdecl _GetSEND() = 0 ;
	HIDESBASE virtual _di_JReturnKeyType __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JReturnKeyType>* __cdecl values() = 0 ;
	__property _di_JReturnKeyType DONE = {read=_GetDONE};
	__property _di_JReturnKeyType ENTER = {read=_GetENTER};
	__property _di_JReturnKeyType GO = {read=_GetGO};
	__property _di_JReturnKeyType NEXT = {read=_GetNEXT};
	__property _di_JReturnKeyType SEARCH = {read=_GetSEARCH};
	__property _di_JReturnKeyType SEND = {read=_GetSEND};
};

__interface  INTERFACE_UUID("{16AE8FAC-E2AC-4898-9A64-25C8F73E2294}") JReturnKeyType  : public Androidapi::Jni::Javatypes::JEnum 
{
	virtual int __cdecl getImeOptions() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJReturnKeyType : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JReturnKeyTypeClass,_di_JReturnKeyType>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JReturnKeyTypeClass,_di_JReturnKeyType> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJReturnKeyType() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JReturnKeyTypeClass,_di_JReturnKeyType>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJReturnKeyType() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E6DEC0E1-D886-4A5E-A07F-B50E17B8C28B}") JVirtualKeyboardTypeClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JVirtualKeyboardType __cdecl _GetALPHABET() = 0 ;
	virtual _di_JVirtualKeyboardType __cdecl _GetEMAIL_ADDRESS() = 0 ;
	virtual _di_JVirtualKeyboardType __cdecl _GetNAME_PHONE_PAD() = 0 ;
	virtual _di_JVirtualKeyboardType __cdecl _GetNUMBER() = 0 ;
	virtual _di_JVirtualKeyboardType __cdecl _GetNUMBER_AND_PUNCTUATION() = 0 ;
	virtual _di_JVirtualKeyboardType __cdecl _GetNUMBER_DECIMAL() = 0 ;
	virtual _di_JVirtualKeyboardType __cdecl _GetPHONE() = 0 ;
	virtual _di_JVirtualKeyboardType __cdecl _GetTEXT() = 0 ;
	virtual _di_JVirtualKeyboardType __cdecl _GetURL() = 0 ;
	HIDESBASE virtual _di_JVirtualKeyboardType __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JVirtualKeyboardType>* __cdecl values() = 0 ;
	__property _di_JVirtualKeyboardType ALPHABET = {read=_GetALPHABET};
	__property _di_JVirtualKeyboardType EMAIL_ADDRESS = {read=_GetEMAIL_ADDRESS};
	__property _di_JVirtualKeyboardType NAME_PHONE_PAD = {read=_GetNAME_PHONE_PAD};
	__property _di_JVirtualKeyboardType NUMBER = {read=_GetNUMBER};
	__property _di_JVirtualKeyboardType NUMBER_AND_PUNCTUATION = {read=_GetNUMBER_AND_PUNCTUATION};
	__property _di_JVirtualKeyboardType NUMBER_DECIMAL = {read=_GetNUMBER_DECIMAL};
	__property _di_JVirtualKeyboardType PHONE = {read=_GetPHONE};
	__property _di_JVirtualKeyboardType TEXT = {read=_GetTEXT};
	__property _di_JVirtualKeyboardType URL = {read=_GetURL};
};

__interface  INTERFACE_UUID("{31FBFD4B-7476-4041-A253-29D7098C1CDD}") JVirtualKeyboardType  : public Androidapi::Jni::Javatypes::JEnum 
{
	virtual int __cdecl getInputType() = 0 ;
	virtual bool __cdecl isNumberClass() = 0 ;
	virtual bool __cdecl isTextClass() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVirtualKeyboardType : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVirtualKeyboardTypeClass,_di_JVirtualKeyboardType>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVirtualKeyboardTypeClass,_di_JVirtualKeyboardType> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVirtualKeyboardType() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVirtualKeyboardTypeClass,_di_JVirtualKeyboardType>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVirtualKeyboardType() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A052D0AC-61A4-418C-AF59-0BFC82680EA7}") JAllLowerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JAllLower __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{E2429529-8F5A-4CAE-A84D-0197005858FF}") JAllLower  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl filter(Androidapi::Jni::Javatypes::_di_JCharSequence source, int start, int end_, Androidapi::Jni::Graphicscontentviewtext::_di_JSpanned dest, int dstart, int dend) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAllLower : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAllLowerClass,_di_JAllLower>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAllLowerClass,_di_JAllLower> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAllLower() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAllLowerClass,_di_JAllLower>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAllLower() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5A483B22-6173-4AB3-BEB7-2F681A1F7276}") JFilterCharClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JFilterChar __cdecl init(Androidapi::Jni::Javatypes::_di_JCharSequence filterChar) = 0 ;
};

__interface  INTERFACE_UUID("{731E295B-8E15-47BB-B896-DEAFAB7CDA3E}") JFilterChar  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl filter(Androidapi::Jni::Javatypes::_di_JCharSequence source, int start, int end_, Androidapi::Jni::Graphicscontentviewtext::_di_JSpanned dest, int dstart, int dend) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFilterChar : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFilterCharClass,_di_JFilterChar>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFilterCharClass,_di_JFilterChar> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFilterChar() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFilterCharClass,_di_JFilterChar>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFilterChar() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BC6B3C35-D160-482B-B5E0-0B3F08F8C37F}") JDelegatedActionModeCallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JDelegatedActionModeCallback __cdecl init(_di_JOnTextContextMenuListener onContextMenuListener) = 0 ;
};

__interface  INTERFACE_UUID("{A4D5C50B-B902-457D-A616-0F738B9B10F6}") JDelegatedActionModeCallback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl onActionItemClicked(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode, Androidapi::Jni::Graphicscontentviewtext::_di_JMenuItem item) = 0 ;
	virtual bool __cdecl onCreateActionMode(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onDestroyActionMode(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode) = 0 ;
	virtual bool __cdecl onPrepareActionMode(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDelegatedActionModeCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDelegatedActionModeCallbackClass,_di_JDelegatedActionModeCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDelegatedActionModeCallbackClass,_di_JDelegatedActionModeCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDelegatedActionModeCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDelegatedActionModeCallbackClass,_di_JDelegatedActionModeCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDelegatedActionModeCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AD8135E3-E944-4032-AB94-0187D73E2716}") JDelegatedActionModeCallback2Class  : public Androidapi::Jni::Graphicscontentviewtext::JActionMode_Callback2Class 
{
	HIDESBASE virtual _di_JDelegatedActionModeCallback2 __cdecl init(_di_JOnTextContextMenuListener onContextMenuListener) = 0 ;
};

__interface  INTERFACE_UUID("{37FCE89A-8BCE-498A-A3E1-92F6961A715F}") JDelegatedActionModeCallback2  : public Androidapi::Jni::Graphicscontentviewtext::JActionMode_Callback2 
{
	virtual bool __cdecl onActionItemClicked(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode, Androidapi::Jni::Graphicscontentviewtext::_di_JMenuItem item) = 0 ;
	virtual bool __cdecl onCreateActionMode(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onDestroyActionMode(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode) = 0 ;
	HIDESBASE virtual void __cdecl onGetContentRect(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode, Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Graphicscontentviewtext::_di_JRect outRect) = 0 ;
	virtual bool __cdecl onPrepareActionMode(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDelegatedActionModeCallback2 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDelegatedActionModeCallback2Class,_di_JDelegatedActionModeCallback2>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDelegatedActionModeCallback2Class,_di_JDelegatedActionModeCallback2> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDelegatedActionModeCallback2() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDelegatedActionModeCallback2Class,_di_JDelegatedActionModeCallback2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDelegatedActionModeCallback2() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{487107F4-005A-422A-B00C-D56EBC257588}") JOnTextContextMenuListenerClass  : public Androidapi::Jni::Graphicscontentviewtext::JActionMode_CallbackClass 
{
	
};

__interface  INTERFACE_UUID("{614FBEA7-BD83-4F1E-9978-423DA86E95E3}") JOnTextContextMenuListener  : public Androidapi::Jni::Graphicscontentviewtext::JActionMode_Callback 
{
	virtual void __cdecl onGetContentRect(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode, Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Graphicscontentviewtext::_di_JRect outRect) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnTextContextMenuListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnTextContextMenuListenerClass,_di_JOnTextContextMenuListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnTextContextMenuListenerClass,_di_JOnTextContextMenuListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnTextContextMenuListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnTextContextMenuListenerClass,_di_JOnTextContextMenuListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnTextContextMenuListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{01D11CF8-BF46-45EF-8090-628E2BA23A2E}") JOnWebViewListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{EF36619D-8759-4381-B638-C99B1C0A0EF8}") JOnWebViewListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl doUpdateVisitedHistory(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url, bool isReload) = 0 ;
	virtual void __cdecl onFormResubmission(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Os::_di_JMessage dontResend, Androidapi::Jni::Os::_di_JMessage resend) = 0 ;
	virtual void __cdecl onLoadResource(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual void __cdecl onPageFinished(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual void __cdecl onPageStarted(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap favicon) = 0 ;
	virtual void __cdecl onReceivedError(Androidapi::Jni::Webkit::_di_JWebView view, int errorCode, Androidapi::Jni::Javatypes::_di_JString description, Androidapi::Jni::Javatypes::_di_JString failingUrl) = 0 ;
	virtual void __cdecl onReceivedHttpAuthRequest(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Webkit::_di_JHttpAuthHandler handler, Androidapi::Jni::Javatypes::_di_JString host, Androidapi::Jni::Javatypes::_di_JString realm) = 0 ;
	virtual void __cdecl onReceivedSslError(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Webkit::_di_JSslErrorHandler handler, Androidapi::Jni::Net::_di_JSslError error) = 0 ;
	virtual void __cdecl onScaleChanged(Androidapi::Jni::Webkit::_di_JWebView view, float oldScale, float newScale) = 0 ;
	virtual void __cdecl onUnhandledKeyEvent(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl shouldOverrideKeyEvent(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl shouldOverrideUrlLoading(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnWebViewListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnWebViewListenerClass,_di_JOnWebViewListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnWebViewListenerClass,_di_JOnWebViewListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnWebViewListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnWebViewListenerClass,_di_JOnWebViewListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnWebViewListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C9D39057-C2B7-4264-8E58-52DE4CA5AE56}") JWebBrowserClass  : public Androidapi::Jni::Webkit::JWebViewClass 
{
	HIDESBASE virtual _di_JWebBrowser __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

__interface  INTERFACE_UUID("{21876269-EEA5-4130-BE15-F23BEB8ECA69}") JWebBrowser  : public Androidapi::Jni::Webkit::JWebView 
{
	virtual void __cdecl SetWebViewListener(_di_JOnWebViewListener listener) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebBrowser : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebBrowserClass,_di_JWebBrowser>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebBrowserClass,_di_JWebBrowser> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebBrowser() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebBrowserClass,_di_JWebBrowser>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebBrowser() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{424BCB34-24B0-4A4B-830B-D396C3667344}") JWebClientClass  : public Androidapi::Jni::Webkit::JWebViewClientClass 
{
	HIDESBASE virtual _di_JWebClient __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{6D32A60F-6D97-4756-95C6-AFBFE15C465F}") JWebClient  : public Androidapi::Jni::Webkit::JWebViewClient 
{
	virtual void __cdecl SetWebViewListener(_di_JOnWebViewListener listener) = 0 ;
	HIDESBASE virtual void __cdecl doUpdateVisitedHistory(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url, bool isReload) = 0 ;
	HIDESBASE virtual void __cdecl onFormResubmission(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Os::_di_JMessage dontResend, Androidapi::Jni::Os::_di_JMessage resend) = 0 ;
	HIDESBASE virtual void __cdecl onLoadResource(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	HIDESBASE virtual void __cdecl onPageFinished(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	HIDESBASE virtual void __cdecl onPageStarted(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap favicon) = 0 ;
	HIDESBASE virtual void __cdecl onReceivedError(Androidapi::Jni::Webkit::_di_JWebView view, int errorCode, Androidapi::Jni::Javatypes::_di_JString description, Androidapi::Jni::Javatypes::_di_JString failingUrl) = 0 ;
	HIDESBASE virtual void __cdecl onReceivedHttpAuthRequest(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Webkit::_di_JHttpAuthHandler handler, Androidapi::Jni::Javatypes::_di_JString host, Androidapi::Jni::Javatypes::_di_JString realm) = 0 ;
	HIDESBASE virtual void __cdecl onReceivedSslError(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Webkit::_di_JSslErrorHandler handler, Androidapi::Jni::Net::_di_JSslError error) = 0 ;
	HIDESBASE virtual void __cdecl onScaleChanged(Androidapi::Jni::Webkit::_di_JWebView view, float oldScale, float newScale) = 0 ;
	HIDESBASE virtual void __cdecl onUnhandledKeyEvent(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl shouldOverrideKeyEvent(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl shouldOverrideUrlLoading(Androidapi::Jni::Webkit::_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebClient : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebClientClass,_di_JWebClient>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebClientClass,_di_JWebClient> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebClient() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebClientClass,_di_JWebClient>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebClient() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4308F1E3-BCAB-4A59-B386-8B467479DE19}") JProxyServiceClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JProxyService __cdecl init() = 0 ;
	virtual __int64 __cdecl getService(Androidapi::Jni::Javatypes::_di_JObject service, Androidapi::Jni::Javatypes::_di_JString libraryName) = 0 ;
	virtual Androidapi::Jni::Os::_di_JIBinder __cdecl onBind(Androidapi::Jni::Javatypes::_di_JObject service, Androidapi::Jni::Javatypes::_di_JString libraryName, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual void __cdecl onConfigurationChanged(Androidapi::Jni::Javatypes::_di_JObject service, Androidapi::Jni::Javatypes::_di_JString libraryName, Androidapi::Jni::Graphicscontentviewtext::_di_JConfiguration newConfig) = 0 ;
	virtual void __cdecl onCreate(Androidapi::Jni::Javatypes::_di_JObject service, Androidapi::Jni::Javatypes::_di_JString libraryName) = 0 ;
	virtual void __cdecl onDestroy(Androidapi::Jni::Javatypes::_di_JObject service, Androidapi::Jni::Javatypes::_di_JString libraryName) = 0 ;
	virtual void __cdecl onHandleIntent(Androidapi::Jni::Javatypes::_di_JObject service, Androidapi::Jni::Javatypes::_di_JString libraryName, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual bool __cdecl onHandleMessage(Androidapi::Jni::Javatypes::_di_JObject service, Androidapi::Jni::Javatypes::_di_JString libraryName, Androidapi::Jni::Os::_di_JMessage msg) = 0 ;
	virtual void __cdecl onLowMemory(Androidapi::Jni::Javatypes::_di_JObject service, Androidapi::Jni::Javatypes::_di_JString libraryName) = 0 ;
	virtual void __cdecl onRebind(Androidapi::Jni::Javatypes::_di_JObject service, Androidapi::Jni::Javatypes::_di_JString libraryName, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual int __cdecl onStartCommand(Androidapi::Jni::Javatypes::_di_JObject service, Androidapi::Jni::Javatypes::_di_JString libraryName, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int flags, int startId) = 0 ;
	virtual void __cdecl onTaskRemoved(Androidapi::Jni::Javatypes::_di_JObject service, Androidapi::Jni::Javatypes::_di_JString libraryName, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent rootIntent) = 0 ;
	virtual void __cdecl onTrimMemory(Androidapi::Jni::Javatypes::_di_JObject service, Androidapi::Jni::Javatypes::_di_JString libraryName, int level) = 0 ;
	virtual bool __cdecl onUnbind(Androidapi::Jni::Javatypes::_di_JObject service, Androidapi::Jni::Javatypes::_di_JString libraryName, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
};

__interface  INTERFACE_UUID("{81D7A55C-F3F2-4600-BBD0-F88F0D5B01A4}") JProxyService  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJProxyService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JProxyServiceClass,_di_JProxyService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JProxyServiceClass,_di_JProxyService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJProxyService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JProxyServiceClass,_di_JProxyService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJProxyService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3417384C-A826-4CA7-B264-8728AB002B7B}") JRTLHandlerClass  : public Androidapi::Jni::Os::JHandlerClass 
{
	HIDESBASE virtual _di_JRTLHandler __cdecl init(_di_JRTLHandler_Listener paramListener) = 0 ;
};

__interface  INTERFACE_UUID("{D703B524-788D-4D2C-A84C-96AEA91C1B9B}") JRTLHandler  : public Androidapi::Jni::Os::JHandler 
{
	virtual _di_JRTLHandler_RTLSuperHandler __cdecl _GetSuper() = 0 ;
	HIDESBASE virtual void __cdecl handleMessage(Androidapi::Jni::Os::_di_JMessage paramMessage) = 0 ;
	__property _di_JRTLHandler_RTLSuperHandler Super = {read=_GetSuper};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRTLHandler : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLHandlerClass,_di_JRTLHandler>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLHandlerClass,_di_JRTLHandler> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRTLHandler() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLHandlerClass,_di_JRTLHandler>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRTLHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{49430D59-AA18-486D-94C7-04AC2EA58ADA}") JRTLHandler_ListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{D5EEE739-658B-4973-B431-F74CA8681B6E}") JRTLHandler_Listener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl handleMessage(Androidapi::Jni::Os::_di_JMessage paramMessage) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRTLHandler_Listener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLHandler_ListenerClass,_di_JRTLHandler_Listener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLHandler_ListenerClass,_di_JRTLHandler_Listener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRTLHandler_Listener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLHandler_ListenerClass,_di_JRTLHandler_Listener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRTLHandler_Listener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6B650C1B-F5D9-44EA-ACD9-CB2EDD0C3280}") JRTLHandler_RTLSuperHandlerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JRTLHandler_RTLSuperHandler __cdecl init(_di_JRTLHandler paramRTLHandler) = 0 ;
};

__interface  INTERFACE_UUID("{FF6A6138-30FC-4AE6-B6F6-3AF78E914A9E}") JRTLHandler_RTLSuperHandler  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl handleMessage(Androidapi::Jni::Os::_di_JMessage paramMessage) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRTLHandler_RTLSuperHandler : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLHandler_RTLSuperHandlerClass,_di_JRTLHandler_RTLSuperHandler>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLHandler_RTLSuperHandlerClass,_di_JRTLHandler_RTLSuperHandler> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRTLHandler_RTLSuperHandler() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRTLHandler_RTLSuperHandlerClass,_di_JRTLHandler_RTLSuperHandler>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRTLHandler_RTLSuperHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{50B333A7-5022-4475-BC2A-A39994BED8E9}") JChannelsManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JChannelsManager __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

__interface  INTERFACE_UUID("{0A0C031B-69C1-4915-BA49-2A26E4DB4A59}") JChannelsManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDefaultChannelId() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJChannelsManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JChannelsManagerClass,_di_JChannelsManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JChannelsManagerClass,_di_JChannelsManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJChannelsManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JChannelsManagerClass,_di_JChannelsManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJChannelsManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C845BD22-FDA5-4A19-84BB-2F7E8042B832}") JNotificationAlarmClass  : public Androidapi::Jni::Graphicscontentviewtext::JBroadcastReceiverClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetNOTIFICATION_CENTER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSETTINGS_NOTIFICATION_IDS() = 0 ;
	HIDESBASE virtual _di_JNotificationAlarm __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString NOTIFICATION_CENTER = {read=_GetNOTIFICATION_CENTER};
	__property Androidapi::Jni::Javatypes::_di_JString SETTINGS_NOTIFICATION_IDS = {read=_GetSETTINGS_NOTIFICATION_IDS};
};

__interface  INTERFACE_UUID("{B08E8F99-0DE7-404C-A290-0DFCFCB2DCF7}") JNotificationAlarm  : public Androidapi::Jni::Graphicscontentviewtext::JBroadcastReceiver 
{
	HIDESBASE virtual void __cdecl onReceive(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNotificationAlarm : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationAlarmClass,_di_JNotificationAlarm>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationAlarmClass,_di_JNotificationAlarm> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNotificationAlarm() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationAlarmClass,_di_JNotificationAlarm>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNotificationAlarm() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{752976D5-5009-42D5-8A32-EC531871F704}") JNotificationInfoClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_NOTIFICATION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_ACTIVITY_CLASS_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_ALERT_ACTION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_ALERT_BODY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_CHANNEL_ID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_ENABLE_SOUND() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_FIRE_DATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_FIRE_GMT_DATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_HAS_ACTION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_NUMBER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_REPEAT_INTERVAL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_SOUND_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_TITLE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_UNIQUE_ID() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_NOTIFICATION = {read=_GetACTION_NOTIFICATION};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_ACTIVITY_CLASS_NAME = {read=_GetEXTRA_ACTIVITY_CLASS_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_ALERT_ACTION = {read=_GetEXTRA_ALERT_ACTION};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_ALERT_BODY = {read=_GetEXTRA_ALERT_BODY};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_CHANNEL_ID = {read=_GetEXTRA_CHANNEL_ID};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_ENABLE_SOUND = {read=_GetEXTRA_ENABLE_SOUND};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_FIRE_DATE = {read=_GetEXTRA_FIRE_DATE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_FIRE_GMT_DATE = {read=_GetEXTRA_FIRE_GMT_DATE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_HAS_ACTION = {read=_GetEXTRA_HAS_ACTION};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_NAME = {read=_GetEXTRA_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_NUMBER = {read=_GetEXTRA_NUMBER};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_REPEAT_INTERVAL = {read=_GetEXTRA_REPEAT_INTERVAL};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_SOUND_NAME = {read=_GetEXTRA_SOUND_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_TITLE = {read=_GetEXTRA_TITLE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_UNIQUE_ID = {read=_GetEXTRA_UNIQUE_ID};
};

__interface  INTERFACE_UUID("{A9BD962E-87E0-46B6-96CB-0AEA5AA99BD9}") JNotificationInfo  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl getIntentCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getNotificationPreferencesValue() = 0 ;
	virtual int __cdecl getRepeatInterval() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNotificationInfo : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationInfoClass,_di_JNotificationInfo>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationInfoClass,_di_JNotificationInfo> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNotificationInfo() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationInfoClass,_di_JNotificationInfo>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNotificationInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9C4491C8-7BAF-4A5C-96DD-7DB579165E74}") JRepeatIntervalClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetREPEAT_INTERVAL_DAY() = 0 ;
	virtual int __cdecl _GetREPEAT_INTERVAL_ERA() = 0 ;
	virtual int __cdecl _GetREPEAT_INTERVAL_HOUR() = 0 ;
	virtual int __cdecl _GetREPEAT_INTERVAL_MINUTE() = 0 ;
	virtual int __cdecl _GetREPEAT_INTERVAL_MONTH() = 0 ;
	virtual int __cdecl _GetREPEAT_INTERVAL_NONE() = 0 ;
	virtual int __cdecl _GetREPEAT_INTERVAL_QUAERTER() = 0 ;
	virtual int __cdecl _GetREPEAT_INTERVAL_SECOND() = 0 ;
	virtual int __cdecl _GetREPEAT_INTERVAL_WEEK() = 0 ;
	virtual int __cdecl _GetREPEAT_INTERVAL_WEEKDAYS() = 0 ;
	virtual int __cdecl _GetREPEAT_INTERVAL_YEAR() = 0 ;
	HIDESBASE virtual _di_JRepeatInterval __cdecl init() = 0 ;
	virtual __int64 __cdecl getRepeatIntervalMSsec(int repeatIntervalType) = 0 ;
	__property int REPEAT_INTERVAL_DAY = {read=_GetREPEAT_INTERVAL_DAY};
	__property int REPEAT_INTERVAL_ERA = {read=_GetREPEAT_INTERVAL_ERA};
	__property int REPEAT_INTERVAL_HOUR = {read=_GetREPEAT_INTERVAL_HOUR};
	__property int REPEAT_INTERVAL_MINUTE = {read=_GetREPEAT_INTERVAL_MINUTE};
	__property int REPEAT_INTERVAL_MONTH = {read=_GetREPEAT_INTERVAL_MONTH};
	__property int REPEAT_INTERVAL_NONE = {read=_GetREPEAT_INTERVAL_NONE};
	__property int REPEAT_INTERVAL_QUAERTER = {read=_GetREPEAT_INTERVAL_QUAERTER};
	__property int REPEAT_INTERVAL_SECOND = {read=_GetREPEAT_INTERVAL_SECOND};
	__property int REPEAT_INTERVAL_WEEK = {read=_GetREPEAT_INTERVAL_WEEK};
	__property int REPEAT_INTERVAL_WEEKDAYS = {read=_GetREPEAT_INTERVAL_WEEKDAYS};
	__property int REPEAT_INTERVAL_YEAR = {read=_GetREPEAT_INTERVAL_YEAR};
};

__interface  INTERFACE_UUID("{71A87C37-FC7D-4A45-A1D4-7DE34B91336A}") JRepeatInterval  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRepeatInterval : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRepeatIntervalClass,_di_JRepeatInterval>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRepeatIntervalClass,_di_JRepeatInterval> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRepeatInterval() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRepeatIntervalClass,_di_JRepeatInterval>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRepeatInterval() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Embarcadero */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_EMBARCADERO)
using namespace Androidapi::Jni::Embarcadero;
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
#endif	// Androidapi_Jni_EmbarcaderoHPP
