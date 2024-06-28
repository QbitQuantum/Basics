// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Os.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_OsHPP
#define Androidapi_Jni_OsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Util.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Os
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JManifestClass;
typedef System::DelphiInterface<JManifestClass> _di_JManifestClass;
__interface DELPHIINTERFACE JManifest;
typedef System::DelphiInterface<JManifest> _di_JManifest;
class DELPHICLASS TJManifest;
__interface DELPHIINTERFACE JManifest_permissionClass;
typedef System::DelphiInterface<JManifest_permissionClass> _di_JManifest_permissionClass;
__interface DELPHIINTERFACE JManifest_permission;
typedef System::DelphiInterface<JManifest_permission> _di_JManifest_permission;
class DELPHICLASS TJManifest_permission;
__interface DELPHIINTERFACE JManifest_permission_groupClass;
typedef System::DelphiInterface<JManifest_permission_groupClass> _di_JManifest_permission_groupClass;
__interface DELPHIINTERFACE JManifest_permission_group;
typedef System::DelphiInterface<JManifest_permission_group> _di_JManifest_permission_group;
class DELPHICLASS TJManifest_permission_group;
__interface DELPHIINTERFACE JBaseBundleClass;
typedef System::DelphiInterface<JBaseBundleClass> _di_JBaseBundleClass;
__interface DELPHIINTERFACE JBaseBundle;
typedef System::DelphiInterface<JBaseBundle> _di_JBaseBundle;
class DELPHICLASS TJBaseBundle;
__interface DELPHIINTERFACE JBinderClass;
typedef System::DelphiInterface<JBinderClass> _di_JBinderClass;
__interface DELPHIINTERFACE JBinder;
typedef System::DelphiInterface<JBinder> _di_JBinder;
class DELPHICLASS TJBinder;
__interface DELPHIINTERFACE JBuildClass;
typedef System::DelphiInterface<JBuildClass> _di_JBuildClass;
__interface DELPHIINTERFACE JBuild;
typedef System::DelphiInterface<JBuild> _di_JBuild;
class DELPHICLASS TJBuild;
__interface DELPHIINTERFACE JBuild_VERSIONClass;
typedef System::DelphiInterface<JBuild_VERSIONClass> _di_JBuild_VERSIONClass;
__interface DELPHIINTERFACE JBuild_VERSION;
typedef System::DelphiInterface<JBuild_VERSION> _di_JBuild_VERSION;
class DELPHICLASS TJBuild_VERSION;
__interface DELPHIINTERFACE JBuild_VERSION_CODESClass;
typedef System::DelphiInterface<JBuild_VERSION_CODESClass> _di_JBuild_VERSION_CODESClass;
__interface DELPHIINTERFACE JBuild_VERSION_CODES;
typedef System::DelphiInterface<JBuild_VERSION_CODES> _di_JBuild_VERSION_CODES;
class DELPHICLASS TJBuild_VERSION_CODES;
__interface DELPHIINTERFACE JBundleClass;
typedef System::DelphiInterface<JBundleClass> _di_JBundleClass;
__interface DELPHIINTERFACE JBundle;
typedef System::DelphiInterface<JBundle> _di_JBundle;
class DELPHICLASS TJBundle;
__interface DELPHIINTERFACE JCancellationSignalClass;
typedef System::DelphiInterface<JCancellationSignalClass> _di_JCancellationSignalClass;
__interface DELPHIINTERFACE JCancellationSignal;
typedef System::DelphiInterface<JCancellationSignal> _di_JCancellationSignal;
class DELPHICLASS TJCancellationSignal;
__interface DELPHIINTERFACE JCancellationSignal_OnCancelListenerClass;
typedef System::DelphiInterface<JCancellationSignal_OnCancelListenerClass> _di_JCancellationSignal_OnCancelListenerClass;
__interface DELPHIINTERFACE JCancellationSignal_OnCancelListener;
typedef System::DelphiInterface<JCancellationSignal_OnCancelListener> _di_JCancellationSignal_OnCancelListener;
class DELPHICLASS TJCancellationSignal_OnCancelListener;
__interface DELPHIINTERFACE JDebug_MemoryInfoClass;
typedef System::DelphiInterface<JDebug_MemoryInfoClass> _di_JDebug_MemoryInfoClass;
__interface DELPHIINTERFACE JDebug_MemoryInfo;
typedef System::DelphiInterface<JDebug_MemoryInfo> _di_JDebug_MemoryInfo;
class DELPHICLASS TJDebug_MemoryInfo;
__interface DELPHIINTERFACE JHandlerClass;
typedef System::DelphiInterface<JHandlerClass> _di_JHandlerClass;
__interface DELPHIINTERFACE JHandler;
typedef System::DelphiInterface<JHandler> _di_JHandler;
class DELPHICLASS TJHandler;
__interface DELPHIINTERFACE JHandler_CallbackClass;
typedef System::DelphiInterface<JHandler_CallbackClass> _di_JHandler_CallbackClass;
__interface DELPHIINTERFACE JHandler_Callback;
typedef System::DelphiInterface<JHandler_Callback> _di_JHandler_Callback;
class DELPHICLASS TJHandler_Callback;
__interface DELPHIINTERFACE JHandlerThreadClass;
typedef System::DelphiInterface<JHandlerThreadClass> _di_JHandlerThreadClass;
__interface DELPHIINTERFACE JHandlerThread;
typedef System::DelphiInterface<JHandlerThread> _di_JHandlerThread;
class DELPHICLASS TJHandlerThread;
__interface DELPHIINTERFACE JIBinderClass;
typedef System::DelphiInterface<JIBinderClass> _di_JIBinderClass;
__interface DELPHIINTERFACE JIBinder;
typedef System::DelphiInterface<JIBinder> _di_JIBinder;
class DELPHICLASS TJIBinder;
__interface DELPHIINTERFACE JIBinder_DeathRecipientClass;
typedef System::DelphiInterface<JIBinder_DeathRecipientClass> _di_JIBinder_DeathRecipientClass;
__interface DELPHIINTERFACE JIBinder_DeathRecipient;
typedef System::DelphiInterface<JIBinder_DeathRecipient> _di_JIBinder_DeathRecipient;
class DELPHICLASS TJIBinder_DeathRecipient;
__interface DELPHIINTERFACE JIInterfaceClass;
typedef System::DelphiInterface<JIInterfaceClass> _di_JIInterfaceClass;
__interface DELPHIINTERFACE JIInterface;
typedef System::DelphiInterface<JIInterface> _di_JIInterface;
class DELPHICLASS TJIInterface;
__interface DELPHIINTERFACE JLocaleListClass;
typedef System::DelphiInterface<JLocaleListClass> _di_JLocaleListClass;
__interface DELPHIINTERFACE JLocaleList;
typedef System::DelphiInterface<JLocaleList> _di_JLocaleList;
class DELPHICLASS TJLocaleList;
__interface DELPHIINTERFACE JLooperClass;
typedef System::DelphiInterface<JLooperClass> _di_JLooperClass;
__interface DELPHIINTERFACE JLooper;
typedef System::DelphiInterface<JLooper> _di_JLooper;
class DELPHICLASS TJLooper;
__interface DELPHIINTERFACE JMessageClass;
typedef System::DelphiInterface<JMessageClass> _di_JMessageClass;
__interface DELPHIINTERFACE JMessage;
typedef System::DelphiInterface<JMessage> _di_JMessage;
class DELPHICLASS TJMessage;
__interface DELPHIINTERFACE JMessageQueueClass;
typedef System::DelphiInterface<JMessageQueueClass> _di_JMessageQueueClass;
__interface DELPHIINTERFACE JMessageQueue;
typedef System::DelphiInterface<JMessageQueue> _di_JMessageQueue;
class DELPHICLASS TJMessageQueue;
__interface DELPHIINTERFACE JMessageQueue_IdleHandlerClass;
typedef System::DelphiInterface<JMessageQueue_IdleHandlerClass> _di_JMessageQueue_IdleHandlerClass;
__interface DELPHIINTERFACE JMessageQueue_IdleHandler;
typedef System::DelphiInterface<JMessageQueue_IdleHandler> _di_JMessageQueue_IdleHandler;
class DELPHICLASS TJMessageQueue_IdleHandler;
__interface DELPHIINTERFACE JMessageQueue_OnFileDescriptorEventListenerClass;
typedef System::DelphiInterface<JMessageQueue_OnFileDescriptorEventListenerClass> _di_JMessageQueue_OnFileDescriptorEventListenerClass;
__interface DELPHIINTERFACE JMessageQueue_OnFileDescriptorEventListener;
typedef System::DelphiInterface<JMessageQueue_OnFileDescriptorEventListener> _di_JMessageQueue_OnFileDescriptorEventListener;
class DELPHICLASS TJMessageQueue_OnFileDescriptorEventListener;
__interface DELPHIINTERFACE JMessengerClass;
typedef System::DelphiInterface<JMessengerClass> _di_JMessengerClass;
__interface DELPHIINTERFACE JMessenger;
typedef System::DelphiInterface<JMessenger> _di_JMessenger;
class DELPHICLASS TJMessenger;
__interface DELPHIINTERFACE JParcelClass;
typedef System::DelphiInterface<JParcelClass> _di_JParcelClass;
__interface DELPHIINTERFACE JParcel;
typedef System::DelphiInterface<JParcel> _di_JParcel;
class DELPHICLASS TJParcel;
__interface DELPHIINTERFACE JParcelFileDescriptorClass;
typedef System::DelphiInterface<JParcelFileDescriptorClass> _di_JParcelFileDescriptorClass;
__interface DELPHIINTERFACE JParcelFileDescriptor;
typedef System::DelphiInterface<JParcelFileDescriptor> _di_JParcelFileDescriptor;
class DELPHICLASS TJParcelFileDescriptor;
__interface DELPHIINTERFACE JParcelFileDescriptor_AutoCloseInputStreamClass;
typedef System::DelphiInterface<JParcelFileDescriptor_AutoCloseInputStreamClass> _di_JParcelFileDescriptor_AutoCloseInputStreamClass;
__interface DELPHIINTERFACE JParcelFileDescriptor_AutoCloseInputStream;
typedef System::DelphiInterface<JParcelFileDescriptor_AutoCloseInputStream> _di_JParcelFileDescriptor_AutoCloseInputStream;
class DELPHICLASS TJParcelFileDescriptor_AutoCloseInputStream;
__interface DELPHIINTERFACE JParcelFileDescriptor_AutoCloseOutputStreamClass;
typedef System::DelphiInterface<JParcelFileDescriptor_AutoCloseOutputStreamClass> _di_JParcelFileDescriptor_AutoCloseOutputStreamClass;
__interface DELPHIINTERFACE JParcelFileDescriptor_AutoCloseOutputStream;
typedef System::DelphiInterface<JParcelFileDescriptor_AutoCloseOutputStream> _di_JParcelFileDescriptor_AutoCloseOutputStream;
class DELPHICLASS TJParcelFileDescriptor_AutoCloseOutputStream;
__interface DELPHIINTERFACE JParcelFileDescriptor_OnCloseListenerClass;
typedef System::DelphiInterface<JParcelFileDescriptor_OnCloseListenerClass> _di_JParcelFileDescriptor_OnCloseListenerClass;
__interface DELPHIINTERFACE JParcelFileDescriptor_OnCloseListener;
typedef System::DelphiInterface<JParcelFileDescriptor_OnCloseListener> _di_JParcelFileDescriptor_OnCloseListener;
class DELPHICLASS TJParcelFileDescriptor_OnCloseListener;
__interface DELPHIINTERFACE JParcelUuidClass;
typedef System::DelphiInterface<JParcelUuidClass> _di_JParcelUuidClass;
__interface DELPHIINTERFACE JParcelUuid;
typedef System::DelphiInterface<JParcelUuid> _di_JParcelUuid;
class DELPHICLASS TJParcelUuid;
__interface DELPHIINTERFACE JParcelableClass;
typedef System::DelphiInterface<JParcelableClass> _di_JParcelableClass;
__interface DELPHIINTERFACE JParcelable;
typedef System::DelphiInterface<JParcelable> _di_JParcelable;
class DELPHICLASS TJParcelable;
__interface DELPHIINTERFACE JParcelable_CreatorClass;
typedef System::DelphiInterface<JParcelable_CreatorClass> _di_JParcelable_CreatorClass;
__interface DELPHIINTERFACE JParcelable_Creator;
typedef System::DelphiInterface<JParcelable_Creator> _di_JParcelable_Creator;
class DELPHICLASS TJParcelable_Creator;
__interface DELPHIINTERFACE JParcelable_ClassLoaderCreatorClass;
typedef System::DelphiInterface<JParcelable_ClassLoaderCreatorClass> _di_JParcelable_ClassLoaderCreatorClass;
__interface DELPHIINTERFACE JParcelable_ClassLoaderCreator;
typedef System::DelphiInterface<JParcelable_ClassLoaderCreator> _di_JParcelable_ClassLoaderCreator;
class DELPHICLASS TJParcelable_ClassLoaderCreator;
__interface DELPHIINTERFACE JPatternMatcherClass;
typedef System::DelphiInterface<JPatternMatcherClass> _di_JPatternMatcherClass;
__interface DELPHIINTERFACE JPatternMatcher;
typedef System::DelphiInterface<JPatternMatcher> _di_JPatternMatcher;
class DELPHICLASS TJPatternMatcher;
__interface DELPHIINTERFACE JPersistableBundleClass;
typedef System::DelphiInterface<JPersistableBundleClass> _di_JPersistableBundleClass;
__interface DELPHIINTERFACE JPersistableBundle;
typedef System::DelphiInterface<JPersistableBundle> _di_JPersistableBundle;
class DELPHICLASS TJPersistableBundle;
__interface DELPHIINTERFACE JPowerManagerClass;
typedef System::DelphiInterface<JPowerManagerClass> _di_JPowerManagerClass;
__interface DELPHIINTERFACE JPowerManager;
typedef System::DelphiInterface<JPowerManager> _di_JPowerManager;
class DELPHICLASS TJPowerManager;
__interface DELPHIINTERFACE JPowerManager_WakeLockClass;
typedef System::DelphiInterface<JPowerManager_WakeLockClass> _di_JPowerManager_WakeLockClass;
__interface DELPHIINTERFACE JPowerManager_WakeLock;
typedef System::DelphiInterface<JPowerManager_WakeLock> _di_JPowerManager_WakeLock;
class DELPHICLASS TJPowerManager_WakeLock;
__interface DELPHIINTERFACE JRemoteExceptionClass;
typedef System::DelphiInterface<JRemoteExceptionClass> _di_JRemoteExceptionClass;
__interface DELPHIINTERFACE JRemoteException;
typedef System::DelphiInterface<JRemoteException> _di_JRemoteException;
class DELPHICLASS TJRemoteException;
__interface DELPHIINTERFACE JResultReceiverClass;
typedef System::DelphiInterface<JResultReceiverClass> _di_JResultReceiverClass;
__interface DELPHIINTERFACE JResultReceiver;
typedef System::DelphiInterface<JResultReceiver> _di_JResultReceiver;
class DELPHICLASS TJResultReceiver;
__interface DELPHIINTERFACE JUserHandleClass;
typedef System::DelphiInterface<JUserHandleClass> _di_JUserHandleClass;
__interface DELPHIINTERFACE JUserHandle;
typedef System::DelphiInterface<JUserHandle> _di_JUserHandle;
class DELPHICLASS TJUserHandle;
__interface DELPHIINTERFACE JVibrationEffectClass;
typedef System::DelphiInterface<JVibrationEffectClass> _di_JVibrationEffectClass;
__interface DELPHIINTERFACE JVibrationEffect;
typedef System::DelphiInterface<JVibrationEffect> _di_JVibrationEffect;
class DELPHICLASS TJVibrationEffect;
__interface DELPHIINTERFACE JVibratorClass;
typedef System::DelphiInterface<JVibratorClass> _di_JVibratorClass;
__interface DELPHIINTERFACE JVibrator;
typedef System::DelphiInterface<JVibrator> _di_JVibrator;
class DELPHICLASS TJVibrator;
__interface DELPHIINTERFACE JWorkSourceClass;
typedef System::DelphiInterface<JWorkSourceClass> _di_JWorkSourceClass;
__interface DELPHIINTERFACE JWorkSource;
typedef System::DelphiInterface<JWorkSource> _di_JWorkSource;
class DELPHICLASS TJWorkSource;
__interface DELPHIINTERFACE JOnObbStateChangeListenerClass;
typedef System::DelphiInterface<JOnObbStateChangeListenerClass> _di_JOnObbStateChangeListenerClass;
__interface DELPHIINTERFACE JOnObbStateChangeListener;
typedef System::DelphiInterface<JOnObbStateChangeListener> _di_JOnObbStateChangeListener;
class DELPHICLASS TJOnObbStateChangeListener;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{40E146F0-8571-43FF-86AB-1305BFCE94AE}") JManifestClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JManifest __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{177627AA-0D00-4BC4-A8A7-9EC6C8157E86}") JManifest  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJManifest : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JManifestClass,_di_JManifest>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JManifestClass,_di_JManifest> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJManifest() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JManifestClass,_di_JManifest>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJManifest() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7138C56B-F5A7-4319-8D1D-0035C5F4E01A}") JManifest_permissionClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACCESS_CHECKIN_PROPERTIES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACCESS_COARSE_LOCATION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACCESS_FINE_LOCATION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACCESS_LOCATION_EXTRA_COMMANDS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACCESS_NETWORK_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACCESS_NOTIFICATION_POLICY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACCESS_WIFI_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACCOUNT_MANAGER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetADD_VOICEMAIL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetANSWER_PHONE_CALLS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBATTERY_STATS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_ACCESSIBILITY_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_APPWIDGET() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_AUTOFILL_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_CARRIER_MESSAGING_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_CARRIER_SERVICES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_CHOOSER_TARGET_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_CONDITION_PROVIDER_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_DEVICE_ADMIN() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_DREAM_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_INCALL_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_INPUT_METHOD() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_MIDI_DEVICE_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_NFC_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_NOTIFICATION_LISTENER_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_PRINT_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_QUICK_SETTINGS_TILE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_REMOTEVIEWS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_SCREENING_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_TELECOM_CONNECTION_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_TEXT_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_TV_INPUT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_VISUAL_VOICEMAIL_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_VOICE_INTERACTION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_VPN_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_VR_LISTENER_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBIND_WALLPAPER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBLUETOOTH() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBLUETOOTH_ADMIN() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBLUETOOTH_PRIVILEGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBODY_SENSORS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBROADCAST_PACKAGE_REMOVED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBROADCAST_SMS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBROADCAST_STICKY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBROADCAST_WAP_PUSH() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCALL_PHONE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCALL_PRIVILEGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCAMERA() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCAPTURE_AUDIO_OUTPUT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCAPTURE_SECURE_VIDEO_OUTPUT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCAPTURE_VIDEO_OUTPUT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCHANGE_COMPONENT_ENABLED_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCHANGE_CONFIGURATION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCHANGE_NETWORK_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCHANGE_WIFI_MULTICAST_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCHANGE_WIFI_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCLEAR_APP_CACHE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCONTROL_LOCATION_UPDATES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDELETE_CACHE_FILES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDELETE_PACKAGES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDIAGNOSTIC() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDISABLE_KEYGUARD() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDUMP() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXPAND_STATUS_BAR() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFACTORY_TEST() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetGET_ACCOUNTS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetGET_ACCOUNTS_PRIVILEGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetGET_PACKAGE_SIZE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetGET_TASKS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetGLOBAL_SEARCH() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetINSTALL_LOCATION_PROVIDER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetINSTALL_PACKAGES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetINSTALL_SHORTCUT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetINSTANT_APP_FOREGROUND_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetINTERNET() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKILL_BACKGROUND_PROCESSES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetLOCATION_HARDWARE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMANAGE_DOCUMENTS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMANAGE_OWN_CALLS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMASTER_CLEAR() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMEDIA_CONTENT_CONTROL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMODIFY_AUDIO_SETTINGS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMODIFY_PHONE_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMOUNT_FORMAT_FILESYSTEMS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMOUNT_UNMOUNT_FILESYSTEMS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetNFC() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetPACKAGE_USAGE_STATS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetPERSISTENT_ACTIVITY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetPROCESS_OUTGOING_CALLS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREAD_CALENDAR() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREAD_CALL_LOG() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREAD_CONTACTS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREAD_EXTERNAL_STORAGE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREAD_FRAME_BUFFER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREAD_INPUT_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREAD_LOGS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREAD_PHONE_NUMBERS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREAD_PHONE_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREAD_SMS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREAD_SYNC_SETTINGS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREAD_SYNC_STATS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREAD_VOICEMAIL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREBOOT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRECEIVE_BOOT_COMPLETED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRECEIVE_MMS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRECEIVE_SMS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRECEIVE_WAP_PUSH() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRECORD_AUDIO() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREORDER_TASKS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREQUEST_COMPANION_RUN_IN_BACKGROUND() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREQUEST_COMPANION_USE_DATA_IN_BACKGROUND() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREQUEST_DELETE_PACKAGES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREQUEST_IGNORE_BATTERY_OPTIMIZATIONS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREQUEST_INSTALL_PACKAGES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRESTART_PACKAGES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSEND_RESPOND_VIA_MESSAGE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSEND_SMS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSET_ALARM() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSET_ALWAYS_FINISH() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSET_ANIMATION_SCALE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSET_DEBUG_APP() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSET_PREFERRED_APPLICATIONS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSET_PROCESS_LIMIT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSET_TIME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSET_TIME_ZONE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSET_WALLPAPER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSET_WALLPAPER_HINTS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSIGNAL_PERSISTENT_PROCESSES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSTATUS_BAR() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSYSTEM_ALERT_WINDOW() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTRANSMIT_IR() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetUNINSTALL_SHORTCUT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetUPDATE_DEVICE_STATS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetUSE_FINGERPRINT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetUSE_SIP() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetVIBRATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWAKE_LOCK() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWRITE_APN_SETTINGS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWRITE_CALENDAR() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWRITE_CALL_LOG() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWRITE_CONTACTS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWRITE_EXTERNAL_STORAGE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWRITE_GSERVICES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWRITE_SECURE_SETTINGS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWRITE_SETTINGS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWRITE_SYNC_SETTINGS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWRITE_VOICEMAIL() = 0 ;
	HIDESBASE virtual _di_JManifest_permission __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACCESS_CHECKIN_PROPERTIES = {read=_GetACCESS_CHECKIN_PROPERTIES};
	__property Androidapi::Jni::Javatypes::_di_JString ACCESS_COARSE_LOCATION = {read=_GetACCESS_COARSE_LOCATION};
	__property Androidapi::Jni::Javatypes::_di_JString ACCESS_FINE_LOCATION = {read=_GetACCESS_FINE_LOCATION};
	__property Androidapi::Jni::Javatypes::_di_JString ACCESS_LOCATION_EXTRA_COMMANDS = {read=_GetACCESS_LOCATION_EXTRA_COMMANDS};
	__property Androidapi::Jni::Javatypes::_di_JString ACCESS_NETWORK_STATE = {read=_GetACCESS_NETWORK_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString ACCESS_NOTIFICATION_POLICY = {read=_GetACCESS_NOTIFICATION_POLICY};
	__property Androidapi::Jni::Javatypes::_di_JString ACCESS_WIFI_STATE = {read=_GetACCESS_WIFI_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString ACCOUNT_MANAGER = {read=_GetACCOUNT_MANAGER};
	__property Androidapi::Jni::Javatypes::_di_JString ADD_VOICEMAIL = {read=_GetADD_VOICEMAIL};
	__property Androidapi::Jni::Javatypes::_di_JString ANSWER_PHONE_CALLS = {read=_GetANSWER_PHONE_CALLS};
	__property Androidapi::Jni::Javatypes::_di_JString BATTERY_STATS = {read=_GetBATTERY_STATS};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_ACCESSIBILITY_SERVICE = {read=_GetBIND_ACCESSIBILITY_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_APPWIDGET = {read=_GetBIND_APPWIDGET};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_AUTOFILL_SERVICE = {read=_GetBIND_AUTOFILL_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_CARRIER_MESSAGING_SERVICE = {read=_GetBIND_CARRIER_MESSAGING_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_CARRIER_SERVICES = {read=_GetBIND_CARRIER_SERVICES};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_CHOOSER_TARGET_SERVICE = {read=_GetBIND_CHOOSER_TARGET_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_CONDITION_PROVIDER_SERVICE = {read=_GetBIND_CONDITION_PROVIDER_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_DEVICE_ADMIN = {read=_GetBIND_DEVICE_ADMIN};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_DREAM_SERVICE = {read=_GetBIND_DREAM_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_INCALL_SERVICE = {read=_GetBIND_INCALL_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_INPUT_METHOD = {read=_GetBIND_INPUT_METHOD};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_MIDI_DEVICE_SERVICE = {read=_GetBIND_MIDI_DEVICE_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_NFC_SERVICE = {read=_GetBIND_NFC_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_NOTIFICATION_LISTENER_SERVICE = {read=_GetBIND_NOTIFICATION_LISTENER_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_PRINT_SERVICE = {read=_GetBIND_PRINT_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_QUICK_SETTINGS_TILE = {read=_GetBIND_QUICK_SETTINGS_TILE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_REMOTEVIEWS = {read=_GetBIND_REMOTEVIEWS};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_SCREENING_SERVICE = {read=_GetBIND_SCREENING_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_TELECOM_CONNECTION_SERVICE = {read=_GetBIND_TELECOM_CONNECTION_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_TEXT_SERVICE = {read=_GetBIND_TEXT_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_TV_INPUT = {read=_GetBIND_TV_INPUT};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_VISUAL_VOICEMAIL_SERVICE = {read=_GetBIND_VISUAL_VOICEMAIL_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_VOICE_INTERACTION = {read=_GetBIND_VOICE_INTERACTION};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_VPN_SERVICE = {read=_GetBIND_VPN_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_VR_LISTENER_SERVICE = {read=_GetBIND_VR_LISTENER_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString BIND_WALLPAPER = {read=_GetBIND_WALLPAPER};
	__property Androidapi::Jni::Javatypes::_di_JString BLUETOOTH = {read=_GetBLUETOOTH};
	__property Androidapi::Jni::Javatypes::_di_JString BLUETOOTH_ADMIN = {read=_GetBLUETOOTH_ADMIN};
	__property Androidapi::Jni::Javatypes::_di_JString BLUETOOTH_PRIVILEGED = {read=_GetBLUETOOTH_PRIVILEGED};
	__property Androidapi::Jni::Javatypes::_di_JString BODY_SENSORS = {read=_GetBODY_SENSORS};
	__property Androidapi::Jni::Javatypes::_di_JString BROADCAST_PACKAGE_REMOVED = {read=_GetBROADCAST_PACKAGE_REMOVED};
	__property Androidapi::Jni::Javatypes::_di_JString BROADCAST_SMS = {read=_GetBROADCAST_SMS};
	__property Androidapi::Jni::Javatypes::_di_JString BROADCAST_STICKY = {read=_GetBROADCAST_STICKY};
	__property Androidapi::Jni::Javatypes::_di_JString BROADCAST_WAP_PUSH = {read=_GetBROADCAST_WAP_PUSH};
	__property Androidapi::Jni::Javatypes::_di_JString CALL_PHONE = {read=_GetCALL_PHONE};
	__property Androidapi::Jni::Javatypes::_di_JString CALL_PRIVILEGED = {read=_GetCALL_PRIVILEGED};
	__property Androidapi::Jni::Javatypes::_di_JString CAMERA = {read=_GetCAMERA};
	__property Androidapi::Jni::Javatypes::_di_JString CAPTURE_AUDIO_OUTPUT = {read=_GetCAPTURE_AUDIO_OUTPUT};
	__property Androidapi::Jni::Javatypes::_di_JString CAPTURE_SECURE_VIDEO_OUTPUT = {read=_GetCAPTURE_SECURE_VIDEO_OUTPUT};
	__property Androidapi::Jni::Javatypes::_di_JString CAPTURE_VIDEO_OUTPUT = {read=_GetCAPTURE_VIDEO_OUTPUT};
	__property Androidapi::Jni::Javatypes::_di_JString CHANGE_COMPONENT_ENABLED_STATE = {read=_GetCHANGE_COMPONENT_ENABLED_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString CHANGE_CONFIGURATION = {read=_GetCHANGE_CONFIGURATION};
	__property Androidapi::Jni::Javatypes::_di_JString CHANGE_NETWORK_STATE = {read=_GetCHANGE_NETWORK_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString CHANGE_WIFI_MULTICAST_STATE = {read=_GetCHANGE_WIFI_MULTICAST_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString CHANGE_WIFI_STATE = {read=_GetCHANGE_WIFI_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString CLEAR_APP_CACHE = {read=_GetCLEAR_APP_CACHE};
	__property Androidapi::Jni::Javatypes::_di_JString CONTROL_LOCATION_UPDATES = {read=_GetCONTROL_LOCATION_UPDATES};
	__property Androidapi::Jni::Javatypes::_di_JString DELETE_CACHE_FILES = {read=_GetDELETE_CACHE_FILES};
	__property Androidapi::Jni::Javatypes::_di_JString DELETE_PACKAGES = {read=_GetDELETE_PACKAGES};
	__property Androidapi::Jni::Javatypes::_di_JString DIAGNOSTIC = {read=_GetDIAGNOSTIC};
	__property Androidapi::Jni::Javatypes::_di_JString DISABLE_KEYGUARD = {read=_GetDISABLE_KEYGUARD};
	__property Androidapi::Jni::Javatypes::_di_JString DUMP = {read=_GetDUMP};
	__property Androidapi::Jni::Javatypes::_di_JString EXPAND_STATUS_BAR = {read=_GetEXPAND_STATUS_BAR};
	__property Androidapi::Jni::Javatypes::_di_JString FACTORY_TEST = {read=_GetFACTORY_TEST};
	__property Androidapi::Jni::Javatypes::_di_JString GET_ACCOUNTS = {read=_GetGET_ACCOUNTS};
	__property Androidapi::Jni::Javatypes::_di_JString GET_ACCOUNTS_PRIVILEGED = {read=_GetGET_ACCOUNTS_PRIVILEGED};
	__property Androidapi::Jni::Javatypes::_di_JString GET_PACKAGE_SIZE = {read=_GetGET_PACKAGE_SIZE};
	__property Androidapi::Jni::Javatypes::_di_JString GET_TASKS = {read=_GetGET_TASKS};
	__property Androidapi::Jni::Javatypes::_di_JString GLOBAL_SEARCH = {read=_GetGLOBAL_SEARCH};
	__property Androidapi::Jni::Javatypes::_di_JString INSTALL_LOCATION_PROVIDER = {read=_GetINSTALL_LOCATION_PROVIDER};
	__property Androidapi::Jni::Javatypes::_di_JString INSTALL_PACKAGES = {read=_GetINSTALL_PACKAGES};
	__property Androidapi::Jni::Javatypes::_di_JString INSTALL_SHORTCUT = {read=_GetINSTALL_SHORTCUT};
	__property Androidapi::Jni::Javatypes::_di_JString INSTANT_APP_FOREGROUND_SERVICE = {read=_GetINSTANT_APP_FOREGROUND_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString INTERNET = {read=_GetINTERNET};
	__property Androidapi::Jni::Javatypes::_di_JString KILL_BACKGROUND_PROCESSES = {read=_GetKILL_BACKGROUND_PROCESSES};
	__property Androidapi::Jni::Javatypes::_di_JString LOCATION_HARDWARE = {read=_GetLOCATION_HARDWARE};
	__property Androidapi::Jni::Javatypes::_di_JString MANAGE_DOCUMENTS = {read=_GetMANAGE_DOCUMENTS};
	__property Androidapi::Jni::Javatypes::_di_JString MANAGE_OWN_CALLS = {read=_GetMANAGE_OWN_CALLS};
	__property Androidapi::Jni::Javatypes::_di_JString MASTER_CLEAR = {read=_GetMASTER_CLEAR};
	__property Androidapi::Jni::Javatypes::_di_JString MEDIA_CONTENT_CONTROL = {read=_GetMEDIA_CONTENT_CONTROL};
	__property Androidapi::Jni::Javatypes::_di_JString MODIFY_AUDIO_SETTINGS = {read=_GetMODIFY_AUDIO_SETTINGS};
	__property Androidapi::Jni::Javatypes::_di_JString MODIFY_PHONE_STATE = {read=_GetMODIFY_PHONE_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString MOUNT_FORMAT_FILESYSTEMS = {read=_GetMOUNT_FORMAT_FILESYSTEMS};
	__property Androidapi::Jni::Javatypes::_di_JString MOUNT_UNMOUNT_FILESYSTEMS = {read=_GetMOUNT_UNMOUNT_FILESYSTEMS};
	__property Androidapi::Jni::Javatypes::_di_JString NFC = {read=_GetNFC};
	__property Androidapi::Jni::Javatypes::_di_JString PACKAGE_USAGE_STATS = {read=_GetPACKAGE_USAGE_STATS};
	__property Androidapi::Jni::Javatypes::_di_JString PERSISTENT_ACTIVITY = {read=_GetPERSISTENT_ACTIVITY};
	__property Androidapi::Jni::Javatypes::_di_JString PROCESS_OUTGOING_CALLS = {read=_GetPROCESS_OUTGOING_CALLS};
	__property Androidapi::Jni::Javatypes::_di_JString READ_CALENDAR = {read=_GetREAD_CALENDAR};
	__property Androidapi::Jni::Javatypes::_di_JString READ_CALL_LOG = {read=_GetREAD_CALL_LOG};
	__property Androidapi::Jni::Javatypes::_di_JString READ_CONTACTS = {read=_GetREAD_CONTACTS};
	__property Androidapi::Jni::Javatypes::_di_JString READ_EXTERNAL_STORAGE = {read=_GetREAD_EXTERNAL_STORAGE};
	__property Androidapi::Jni::Javatypes::_di_JString READ_FRAME_BUFFER = {read=_GetREAD_FRAME_BUFFER};
	__property Androidapi::Jni::Javatypes::_di_JString READ_INPUT_STATE = {read=_GetREAD_INPUT_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString READ_LOGS = {read=_GetREAD_LOGS};
	__property Androidapi::Jni::Javatypes::_di_JString READ_PHONE_NUMBERS = {read=_GetREAD_PHONE_NUMBERS};
	__property Androidapi::Jni::Javatypes::_di_JString READ_PHONE_STATE = {read=_GetREAD_PHONE_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString READ_SMS = {read=_GetREAD_SMS};
	__property Androidapi::Jni::Javatypes::_di_JString READ_SYNC_SETTINGS = {read=_GetREAD_SYNC_SETTINGS};
	__property Androidapi::Jni::Javatypes::_di_JString READ_SYNC_STATS = {read=_GetREAD_SYNC_STATS};
	__property Androidapi::Jni::Javatypes::_di_JString READ_VOICEMAIL = {read=_GetREAD_VOICEMAIL};
	__property Androidapi::Jni::Javatypes::_di_JString REBOOT = {read=_GetREBOOT};
	__property Androidapi::Jni::Javatypes::_di_JString RECEIVE_BOOT_COMPLETED = {read=_GetRECEIVE_BOOT_COMPLETED};
	__property Androidapi::Jni::Javatypes::_di_JString RECEIVE_MMS = {read=_GetRECEIVE_MMS};
	__property Androidapi::Jni::Javatypes::_di_JString RECEIVE_SMS = {read=_GetRECEIVE_SMS};
	__property Androidapi::Jni::Javatypes::_di_JString RECEIVE_WAP_PUSH = {read=_GetRECEIVE_WAP_PUSH};
	__property Androidapi::Jni::Javatypes::_di_JString RECORD_AUDIO = {read=_GetRECORD_AUDIO};
	__property Androidapi::Jni::Javatypes::_di_JString REORDER_TASKS = {read=_GetREORDER_TASKS};
	__property Androidapi::Jni::Javatypes::_di_JString REQUEST_COMPANION_RUN_IN_BACKGROUND = {read=_GetREQUEST_COMPANION_RUN_IN_BACKGROUND};
	__property Androidapi::Jni::Javatypes::_di_JString REQUEST_COMPANION_USE_DATA_IN_BACKGROUND = {read=_GetREQUEST_COMPANION_USE_DATA_IN_BACKGROUND};
	__property Androidapi::Jni::Javatypes::_di_JString REQUEST_DELETE_PACKAGES = {read=_GetREQUEST_DELETE_PACKAGES};
	__property Androidapi::Jni::Javatypes::_di_JString REQUEST_IGNORE_BATTERY_OPTIMIZATIONS = {read=_GetREQUEST_IGNORE_BATTERY_OPTIMIZATIONS};
	__property Androidapi::Jni::Javatypes::_di_JString REQUEST_INSTALL_PACKAGES = {read=_GetREQUEST_INSTALL_PACKAGES};
	__property Androidapi::Jni::Javatypes::_di_JString RESTART_PACKAGES = {read=_GetRESTART_PACKAGES};
	__property Androidapi::Jni::Javatypes::_di_JString SEND_RESPOND_VIA_MESSAGE = {read=_GetSEND_RESPOND_VIA_MESSAGE};
	__property Androidapi::Jni::Javatypes::_di_JString SEND_SMS = {read=_GetSEND_SMS};
	__property Androidapi::Jni::Javatypes::_di_JString SET_ALARM = {read=_GetSET_ALARM};
	__property Androidapi::Jni::Javatypes::_di_JString SET_ALWAYS_FINISH = {read=_GetSET_ALWAYS_FINISH};
	__property Androidapi::Jni::Javatypes::_di_JString SET_ANIMATION_SCALE = {read=_GetSET_ANIMATION_SCALE};
	__property Androidapi::Jni::Javatypes::_di_JString SET_DEBUG_APP = {read=_GetSET_DEBUG_APP};
	__property Androidapi::Jni::Javatypes::_di_JString SET_PREFERRED_APPLICATIONS = {read=_GetSET_PREFERRED_APPLICATIONS};
	__property Androidapi::Jni::Javatypes::_di_JString SET_PROCESS_LIMIT = {read=_GetSET_PROCESS_LIMIT};
	__property Androidapi::Jni::Javatypes::_di_JString SET_TIME = {read=_GetSET_TIME};
	__property Androidapi::Jni::Javatypes::_di_JString SET_TIME_ZONE = {read=_GetSET_TIME_ZONE};
	__property Androidapi::Jni::Javatypes::_di_JString SET_WALLPAPER = {read=_GetSET_WALLPAPER};
	__property Androidapi::Jni::Javatypes::_di_JString SET_WALLPAPER_HINTS = {read=_GetSET_WALLPAPER_HINTS};
	__property Androidapi::Jni::Javatypes::_di_JString SIGNAL_PERSISTENT_PROCESSES = {read=_GetSIGNAL_PERSISTENT_PROCESSES};
	__property Androidapi::Jni::Javatypes::_di_JString STATUS_BAR = {read=_GetSTATUS_BAR};
	__property Androidapi::Jni::Javatypes::_di_JString SYSTEM_ALERT_WINDOW = {read=_GetSYSTEM_ALERT_WINDOW};
	__property Androidapi::Jni::Javatypes::_di_JString TRANSMIT_IR = {read=_GetTRANSMIT_IR};
	__property Androidapi::Jni::Javatypes::_di_JString UNINSTALL_SHORTCUT = {read=_GetUNINSTALL_SHORTCUT};
	__property Androidapi::Jni::Javatypes::_di_JString UPDATE_DEVICE_STATS = {read=_GetUPDATE_DEVICE_STATS};
	__property Androidapi::Jni::Javatypes::_di_JString USE_FINGERPRINT = {read=_GetUSE_FINGERPRINT};
	__property Androidapi::Jni::Javatypes::_di_JString USE_SIP = {read=_GetUSE_SIP};
	__property Androidapi::Jni::Javatypes::_di_JString VIBRATE = {read=_GetVIBRATE};
	__property Androidapi::Jni::Javatypes::_di_JString WAKE_LOCK = {read=_GetWAKE_LOCK};
	__property Androidapi::Jni::Javatypes::_di_JString WRITE_APN_SETTINGS = {read=_GetWRITE_APN_SETTINGS};
	__property Androidapi::Jni::Javatypes::_di_JString WRITE_CALENDAR = {read=_GetWRITE_CALENDAR};
	__property Androidapi::Jni::Javatypes::_di_JString WRITE_CALL_LOG = {read=_GetWRITE_CALL_LOG};
	__property Androidapi::Jni::Javatypes::_di_JString WRITE_CONTACTS = {read=_GetWRITE_CONTACTS};
	__property Androidapi::Jni::Javatypes::_di_JString WRITE_EXTERNAL_STORAGE = {read=_GetWRITE_EXTERNAL_STORAGE};
	__property Androidapi::Jni::Javatypes::_di_JString WRITE_GSERVICES = {read=_GetWRITE_GSERVICES};
	__property Androidapi::Jni::Javatypes::_di_JString WRITE_SECURE_SETTINGS = {read=_GetWRITE_SECURE_SETTINGS};
	__property Androidapi::Jni::Javatypes::_di_JString WRITE_SETTINGS = {read=_GetWRITE_SETTINGS};
	__property Androidapi::Jni::Javatypes::_di_JString WRITE_SYNC_SETTINGS = {read=_GetWRITE_SYNC_SETTINGS};
	__property Androidapi::Jni::Javatypes::_di_JString WRITE_VOICEMAIL = {read=_GetWRITE_VOICEMAIL};
};

__interface  INTERFACE_UUID("{85A59978-A449-472E-BD22-F0674731D240}") JManifest_permission  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJManifest_permission : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JManifest_permissionClass,_di_JManifest_permission>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JManifest_permissionClass,_di_JManifest_permission> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJManifest_permission() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JManifest_permissionClass,_di_JManifest_permission>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJManifest_permission() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{16D53E24-6ED5-42C0-A890-978B49643B1A}") JManifest_permission_groupClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCALENDAR() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCAMERA() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCONTACTS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetLOCATION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMICROPHONE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetPHONE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSENSORS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSMS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSTORAGE() = 0 ;
	HIDESBASE virtual _di_JManifest_permission_group __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString CALENDAR = {read=_GetCALENDAR};
	__property Androidapi::Jni::Javatypes::_di_JString CAMERA = {read=_GetCAMERA};
	__property Androidapi::Jni::Javatypes::_di_JString CONTACTS = {read=_GetCONTACTS};
	__property Androidapi::Jni::Javatypes::_di_JString LOCATION = {read=_GetLOCATION};
	__property Androidapi::Jni::Javatypes::_di_JString MICROPHONE = {read=_GetMICROPHONE};
	__property Androidapi::Jni::Javatypes::_di_JString PHONE = {read=_GetPHONE};
	__property Androidapi::Jni::Javatypes::_di_JString SENSORS = {read=_GetSENSORS};
	__property Androidapi::Jni::Javatypes::_di_JString SMS = {read=_GetSMS};
	__property Androidapi::Jni::Javatypes::_di_JString STORAGE = {read=_GetSTORAGE};
};

__interface  INTERFACE_UUID("{55CD45CB-F813-4B61-BD7D-F6EF3CF99D76}") JManifest_permission_group  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJManifest_permission_group : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JManifest_permission_groupClass,_di_JManifest_permission_group>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JManifest_permission_groupClass,_di_JManifest_permission_group> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJManifest_permission_group() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JManifest_permission_groupClass,_di_JManifest_permission_group>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJManifest_permission_group() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{099680A9-7573-4870-8603-6E81F97AEEF2}") JBaseBundleClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{4A1E7433-E9A8-485A-94BC-AB502A0F5820}") JBaseBundle  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl clear() = 0 ;
	virtual bool __cdecl containsKey(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl get(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual bool __cdecl getBoolean(Androidapi::Jni::Javatypes::_di_JString key) = 0 /* overload */;
	virtual bool __cdecl getBoolean(Androidapi::Jni::Javatypes::_di_JString key, bool defaultValue) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<bool>* __cdecl getBooleanArray(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual double __cdecl getDouble(Androidapi::Jni::Javatypes::_di_JString key) = 0 /* overload */;
	virtual double __cdecl getDouble(Androidapi::Jni::Javatypes::_di_JString key, double defaultValue) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<double>* __cdecl getDoubleArray(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual int __cdecl getInt(Androidapi::Jni::Javatypes::_di_JString key) = 0 /* overload */;
	virtual int __cdecl getInt(Androidapi::Jni::Javatypes::_di_JString key, int defaultValue) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<int>* __cdecl getIntArray(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual __int64 __cdecl getLong(Androidapi::Jni::Javatypes::_di_JString key) = 0 /* overload */;
	virtual __int64 __cdecl getLong(Androidapi::Jni::Javatypes::_di_JString key, __int64 defaultValue) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<__int64>* __cdecl getLongArray(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getString(Androidapi::Jni::Javatypes::_di_JString key) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getString(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JString defaultValue) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getStringArray(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual bool __cdecl isEmpty() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JSet __cdecl keySet() = 0 ;
	virtual void __cdecl putAll(_di_JPersistableBundle bundle) = 0 ;
	virtual void __cdecl putBoolean(Androidapi::Jni::Javatypes::_di_JString key, bool value) = 0 ;
	virtual void __cdecl putBooleanArray(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jnibridge::TJavaArray__1<bool>* value) = 0 ;
	virtual void __cdecl putDouble(Androidapi::Jni::Javatypes::_di_JString key, double value) = 0 ;
	virtual void __cdecl putDoubleArray(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jnibridge::TJavaArray__1<double>* value) = 0 ;
	virtual void __cdecl putInt(Androidapi::Jni::Javatypes::_di_JString key, int value) = 0 ;
	virtual void __cdecl putIntArray(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jnibridge::TJavaArray__1<int>* value) = 0 ;
	virtual void __cdecl putLong(Androidapi::Jni::Javatypes::_di_JString key, __int64 value) = 0 ;
	virtual void __cdecl putLongArray(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jnibridge::TJavaArray__1<__int64>* value) = 0 ;
	virtual void __cdecl putString(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JString value) = 0 ;
	virtual void __cdecl putStringArray(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* value) = 0 ;
	virtual void __cdecl remove(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual int __cdecl size() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBaseBundle : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseBundleClass,_di_JBaseBundle>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseBundleClass,_di_JBaseBundle> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBaseBundle() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseBundleClass,_di_JBaseBundle>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBaseBundle() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{28B153C2-C5E2-4A29-8263-9F290048E72A}") JBinderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JBinder __cdecl init() = 0 ;
	virtual __int64 __cdecl clearCallingIdentity() = 0 ;
	virtual void __cdecl flushPendingCommands() = 0 ;
	virtual int __cdecl getCallingPid() = 0 ;
	virtual int __cdecl getCallingUid() = 0 ;
	virtual _di_JUserHandle __cdecl getCallingUserHandle() = 0 ;
	virtual void __cdecl joinThreadPool() = 0 ;
	virtual void __cdecl restoreCallingIdentity(__int64 token) = 0 ;
};

__interface  INTERFACE_UUID("{0A24225C-72F2-43B3-904F-77E148717C48}") JBinder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl attachInterface(_di_JIInterface owner, Androidapi::Jni::Javatypes::_di_JString descriptor) = 0 ;
	virtual void __cdecl dump(Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* args) = 0 ;
	virtual void __cdecl dumpAsync(Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* args) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getInterfaceDescriptor() = 0 ;
	virtual bool __cdecl isBinderAlive() = 0 ;
	virtual void __cdecl linkToDeath(_di_JIBinder_DeathRecipient recipient, int flags) = 0 ;
	virtual bool __cdecl pingBinder() = 0 ;
	virtual _di_JIInterface __cdecl queryLocalInterface(Androidapi::Jni::Javatypes::_di_JString descriptor) = 0 ;
	virtual bool __cdecl transact(int code, _di_JParcel data, _di_JParcel reply, int flags) = 0 ;
	virtual bool __cdecl unlinkToDeath(_di_JIBinder_DeathRecipient recipient, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBinder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBinderClass,_di_JBinder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBinderClass,_di_JBinder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBinder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBinderClass,_di_JBinder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBinder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D90671CF-F0CF-4B07-9660-00D373289D50}") JBuildClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBOARD() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBOOTLOADER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBRAND() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCPU_ABI() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCPU_ABI2() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDEVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDISPLAY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFINGERPRINT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetHARDWARE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetHOST() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMANUFACTURER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMODEL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetPRODUCT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRADIO() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSERIAL() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl _GetSUPPORTED_32_BIT_ABIS() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl _GetSUPPORTED_64_BIT_ABIS() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl _GetSUPPORTED_ABIS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTAGS() = 0 ;
	virtual __int64 __cdecl _GetTIME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTYPE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetUNKNOWN() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetUSER() = 0 ;
	HIDESBASE virtual _di_JBuild __cdecl init() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getRadioVersion() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSerial() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString BOARD = {read=_GetBOARD};
	__property Androidapi::Jni::Javatypes::_di_JString BOOTLOADER = {read=_GetBOOTLOADER};
	__property Androidapi::Jni::Javatypes::_di_JString BRAND = {read=_GetBRAND};
	__property Androidapi::Jni::Javatypes::_di_JString CPU_ABI = {read=_GetCPU_ABI};
	__property Androidapi::Jni::Javatypes::_di_JString CPU_ABI2 = {read=_GetCPU_ABI2};
	__property Androidapi::Jni::Javatypes::_di_JString DEVICE = {read=_GetDEVICE};
	__property Androidapi::Jni::Javatypes::_di_JString DISPLAY = {read=_GetDISPLAY};
	__property Androidapi::Jni::Javatypes::_di_JString FINGERPRINT = {read=_GetFINGERPRINT};
	__property Androidapi::Jni::Javatypes::_di_JString HARDWARE = {read=_GetHARDWARE};
	__property Androidapi::Jni::Javatypes::_di_JString HOST = {read=_GetHOST};
	__property Androidapi::Jni::Javatypes::_di_JString ID = {read=_GetID};
	__property Androidapi::Jni::Javatypes::_di_JString MANUFACTURER = {read=_GetMANUFACTURER};
	__property Androidapi::Jni::Javatypes::_di_JString MODEL = {read=_GetMODEL};
	__property Androidapi::Jni::Javatypes::_di_JString PRODUCT = {read=_GetPRODUCT};
	__property Androidapi::Jni::Javatypes::_di_JString RADIO = {read=_GetRADIO};
	__property Androidapi::Jni::Javatypes::_di_JString SERIAL = {read=_GetSERIAL};
	__property Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* SUPPORTED_32_BIT_ABIS = {read=_GetSUPPORTED_32_BIT_ABIS};
	__property Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* SUPPORTED_64_BIT_ABIS = {read=_GetSUPPORTED_64_BIT_ABIS};
	__property Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* SUPPORTED_ABIS = {read=_GetSUPPORTED_ABIS};
	__property Androidapi::Jni::Javatypes::_di_JString TAGS = {read=_GetTAGS};
	__property __int64 TIME = {read=_GetTIME};
	__property Androidapi::Jni::Javatypes::_di_JString TYPE = {read=_GetTYPE};
	__property Androidapi::Jni::Javatypes::_di_JString UNKNOWN = {read=_GetUNKNOWN};
	__property Androidapi::Jni::Javatypes::_di_JString USER = {read=_GetUSER};
};

__interface  INTERFACE_UUID("{68FCB5C7-BF21-4462-AEA3-D43FBD2D2B24}") JBuild  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBuild : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBuildClass,_di_JBuild>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBuildClass,_di_JBuild> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBuild() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBuildClass,_di_JBuild>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBuild() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1CEE3318-C68B-4A45-A09A-0584BFB9FA31}") JBuild_VERSIONClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBASE_OS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCODENAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetINCREMENTAL() = 0 ;
	virtual int __cdecl _GetPREVIEW_SDK_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRELEASE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSDK() = 0 ;
	virtual int __cdecl _GetSDK_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSECURITY_PATCH() = 0 ;
	HIDESBASE virtual _di_JBuild_VERSION __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString BASE_OS = {read=_GetBASE_OS};
	__property Androidapi::Jni::Javatypes::_di_JString CODENAME = {read=_GetCODENAME};
	__property Androidapi::Jni::Javatypes::_di_JString INCREMENTAL = {read=_GetINCREMENTAL};
	__property int PREVIEW_SDK_INT = {read=_GetPREVIEW_SDK_INT};
	__property Androidapi::Jni::Javatypes::_di_JString RELEASE = {read=_GetRELEASE};
	__property Androidapi::Jni::Javatypes::_di_JString SDK = {read=_GetSDK};
	__property int SDK_INT = {read=_GetSDK_INT};
	__property Androidapi::Jni::Javatypes::_di_JString SECURITY_PATCH = {read=_GetSECURITY_PATCH};
};

__interface  INTERFACE_UUID("{364B79B2-B660-4622-BCD5-85A530549F8E}") JBuild_VERSION  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBuild_VERSION : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBuild_VERSIONClass,_di_JBuild_VERSION>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBuild_VERSIONClass,_di_JBuild_VERSION> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBuild_VERSION() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBuild_VERSIONClass,_di_JBuild_VERSION>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBuild_VERSION() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B29B57B4-E754-4491-8E21-18F8AC40121D}") JBuild_VERSION_CODESClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetBASE() = 0 ;
	virtual int __cdecl _GetBASE_1_1() = 0 ;
	virtual int __cdecl _GetCUPCAKE() = 0 ;
	virtual int __cdecl _GetCUR_DEVELOPMENT() = 0 ;
	virtual int __cdecl _GetDONUT() = 0 ;
	virtual int __cdecl _GetECLAIR() = 0 ;
	virtual int __cdecl _GetECLAIR_0_1() = 0 ;
	virtual int __cdecl _GetECLAIR_MR1() = 0 ;
	virtual int __cdecl _GetFROYO() = 0 ;
	virtual int __cdecl _GetGINGERBREAD() = 0 ;
	virtual int __cdecl _GetGINGERBREAD_MR1() = 0 ;
	virtual int __cdecl _GetHONEYCOMB() = 0 ;
	virtual int __cdecl _GetHONEYCOMB_MR1() = 0 ;
	virtual int __cdecl _GetHONEYCOMB_MR2() = 0 ;
	virtual int __cdecl _GetICE_CREAM_SANDWICH() = 0 ;
	virtual int __cdecl _GetICE_CREAM_SANDWICH_MR1() = 0 ;
	virtual int __cdecl _GetJELLY_BEAN() = 0 ;
	virtual int __cdecl _GetJELLY_BEAN_MR1() = 0 ;
	virtual int __cdecl _GetJELLY_BEAN_MR2() = 0 ;
	virtual int __cdecl _GetKITKAT() = 0 ;
	virtual int __cdecl _GetKITKAT_WATCH() = 0 ;
	virtual int __cdecl _GetLOLLIPOP() = 0 ;
	virtual int __cdecl _GetLOLLIPOP_MR1() = 0 ;
	virtual int __cdecl _GetM() = 0 ;
	virtual int __cdecl _GetN() = 0 ;
	virtual int __cdecl _GetN_MR1() = 0 ;
	virtual int __cdecl _GetO() = 0 ;
	HIDESBASE virtual _di_JBuild_VERSION_CODES __cdecl init() = 0 ;
	__property int BASE = {read=_GetBASE};
	__property int BASE_1_1 = {read=_GetBASE_1_1};
	__property int CUPCAKE = {read=_GetCUPCAKE};
	__property int CUR_DEVELOPMENT = {read=_GetCUR_DEVELOPMENT};
	__property int DONUT = {read=_GetDONUT};
	__property int ECLAIR = {read=_GetECLAIR};
	__property int ECLAIR_0_1 = {read=_GetECLAIR_0_1};
	__property int ECLAIR_MR1 = {read=_GetECLAIR_MR1};
	__property int FROYO = {read=_GetFROYO};
	__property int GINGERBREAD = {read=_GetGINGERBREAD};
	__property int GINGERBREAD_MR1 = {read=_GetGINGERBREAD_MR1};
	__property int HONEYCOMB = {read=_GetHONEYCOMB};
	__property int HONEYCOMB_MR1 = {read=_GetHONEYCOMB_MR1};
	__property int HONEYCOMB_MR2 = {read=_GetHONEYCOMB_MR2};
	__property int ICE_CREAM_SANDWICH = {read=_GetICE_CREAM_SANDWICH};
	__property int ICE_CREAM_SANDWICH_MR1 = {read=_GetICE_CREAM_SANDWICH_MR1};
	__property int JELLY_BEAN = {read=_GetJELLY_BEAN};
	__property int JELLY_BEAN_MR1 = {read=_GetJELLY_BEAN_MR1};
	__property int JELLY_BEAN_MR2 = {read=_GetJELLY_BEAN_MR2};
	__property int KITKAT = {read=_GetKITKAT};
	__property int KITKAT_WATCH = {read=_GetKITKAT_WATCH};
	__property int LOLLIPOP = {read=_GetLOLLIPOP};
	__property int LOLLIPOP_MR1 = {read=_GetLOLLIPOP_MR1};
	__property int M = {read=_GetM};
	__property int N = {read=_GetN};
	__property int N_MR1 = {read=_GetN_MR1};
	__property int O = {read=_GetO};
};

__interface  INTERFACE_UUID("{02FEBAA4-6C7B-4AA8-8415-ED410352FF64}") JBuild_VERSION_CODES  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBuild_VERSION_CODES : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBuild_VERSION_CODESClass,_di_JBuild_VERSION_CODES>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBuild_VERSION_CODESClass,_di_JBuild_VERSION_CODES> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBuild_VERSION_CODES() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBuild_VERSION_CODESClass,_di_JBuild_VERSION_CODES>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBuild_VERSION_CODES() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{35D462B0-8866-4937-B9CD-5DC0F7E9DE87}") JBundleClass  : public JBaseBundleClass 
{
	virtual _di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual _di_JBundle __cdecl _GetEMPTY() = 0 ;
	HIDESBASE virtual _di_JBundle __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JBundle __cdecl init(Androidapi::Jni::Javatypes::_di_JClassLoader loader) = 0 /* overload */;
	HIDESBASE virtual _di_JBundle __cdecl init(int capacity) = 0 /* overload */;
	HIDESBASE virtual _di_JBundle __cdecl init(_di_JBundle b) = 0 /* overload */;
	HIDESBASE virtual _di_JBundle __cdecl init(_di_JPersistableBundle b) = 0 /* overload */;
	__property _di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property _di_JBundle EMPTY = {read=_GetEMPTY};
};

__interface  INTERFACE_UUID("{7D0B7FBA-46ED-4D53-9E0C-F48362182E4F}") JBundle  : public JBaseBundle 
{
	HIDESBASE virtual void __cdecl clear() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl clone() = 0 ;
	virtual _di_JBundle __cdecl deepCopy() = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual _di_JIBinder __cdecl getBinder(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual _di_JBundle __cdecl getBundle(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual System::Byte __cdecl getByte(Androidapi::Jni::Javatypes::_di_JString key) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JByte __cdecl getByte(Androidapi::Jni::Javatypes::_di_JString key, System::Byte defaultValue) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getByteArray(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual System::WideChar __cdecl getChar(Androidapi::Jni::Javatypes::_di_JString key) = 0 /* overload */;
	virtual System::WideChar __cdecl getChar(Androidapi::Jni::Javatypes::_di_JString key, System::WideChar defaultValue) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::WideChar>* __cdecl getCharArray(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getCharSequence(Androidapi::Jni::Javatypes::_di_JString key) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getCharSequence(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JCharSequence defaultValue) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JCharSequence>* __cdecl getCharSequenceArray(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JArrayList __cdecl getCharSequenceArrayList(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JClassLoader __cdecl getClassLoader() = 0 ;
	virtual float __cdecl getFloat(Androidapi::Jni::Javatypes::_di_JString key) = 0 /* overload */;
	virtual float __cdecl getFloat(Androidapi::Jni::Javatypes::_di_JString key, float defaultValue) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<float>* __cdecl getFloatArray(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JArrayList __cdecl getIntegerArrayList(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual _di_JParcelable __cdecl getParcelable(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JParcelable>* __cdecl getParcelableArray(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JArrayList __cdecl getParcelableArrayList(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JSerializable __cdecl getSerializable(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual short __cdecl getShort(Androidapi::Jni::Javatypes::_di_JString key) = 0 /* overload */;
	virtual short __cdecl getShort(Androidapi::Jni::Javatypes::_di_JString key, short defaultValue) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<short>* __cdecl getShortArray(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Util::_di_Jutil_Size __cdecl getSize(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Util::_di_JSizeF __cdecl getSizeF(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Util::_di_JSparseArray __cdecl getSparseParcelableArray(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JArrayList __cdecl getStringArrayList(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual bool __cdecl hasFileDescriptors() = 0 ;
	HIDESBASE virtual void __cdecl putAll(_di_JBundle bundle) = 0 ;
	virtual void __cdecl putBinder(Androidapi::Jni::Javatypes::_di_JString key, _di_JIBinder value) = 0 ;
	virtual void __cdecl putBundle(Androidapi::Jni::Javatypes::_di_JString key, _di_JBundle value) = 0 ;
	virtual void __cdecl putByte(Androidapi::Jni::Javatypes::_di_JString key, System::Byte value) = 0 ;
	virtual void __cdecl putByteArray(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* value) = 0 ;
	virtual void __cdecl putChar(Androidapi::Jni::Javatypes::_di_JString key, System::WideChar value) = 0 ;
	virtual void __cdecl putCharArray(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jnibridge::TJavaArray__1<System::WideChar>* value) = 0 ;
	virtual void __cdecl putCharSequence(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JCharSequence value) = 0 ;
	virtual void __cdecl putCharSequenceArray(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JCharSequence>* value) = 0 ;
	virtual void __cdecl putCharSequenceArrayList(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JArrayList value) = 0 ;
	virtual void __cdecl putFloat(Androidapi::Jni::Javatypes::_di_JString key, float value) = 0 ;
	virtual void __cdecl putFloatArray(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jnibridge::TJavaArray__1<float>* value) = 0 ;
	virtual void __cdecl putIntegerArrayList(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JArrayList value) = 0 ;
	virtual void __cdecl putParcelable(Androidapi::Jni::Javatypes::_di_JString key, _di_JParcelable value) = 0 ;
	virtual void __cdecl putParcelableArray(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jnibridge::TJavaObjectArray__1<_di_JParcelable>* value) = 0 ;
	virtual void __cdecl putParcelableArrayList(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JArrayList value) = 0 ;
	virtual void __cdecl putSerializable(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JSerializable value) = 0 ;
	virtual void __cdecl putShort(Androidapi::Jni::Javatypes::_di_JString key, short value) = 0 ;
	virtual void __cdecl putShortArray(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jnibridge::TJavaArray__1<short>* value) = 0 ;
	virtual void __cdecl putSize(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Util::_di_Jutil_Size value) = 0 ;
	virtual void __cdecl putSizeF(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Util::_di_JSizeF value) = 0 ;
	virtual void __cdecl putSparseParcelableArray(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Util::_di_JSparseArray value) = 0 ;
	virtual void __cdecl putStringArrayList(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JArrayList value) = 0 ;
	virtual void __cdecl readFromParcel(_di_JParcel parcel) = 0 ;
	HIDESBASE virtual void __cdecl remove(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual void __cdecl setClassLoader(Androidapi::Jni::Javatypes::_di_JClassLoader loader) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(_di_JParcel parcel, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBundle : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBundleClass,_di_JBundle>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBundleClass,_di_JBundle> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBundle() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBundleClass,_di_JBundle>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBundle() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{15B2FE5D-1470-43DD-8693-45A3DC38300A}") JCancellationSignalClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JCancellationSignal __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{68D52DA5-BAFC-40CA-9CC8-083A1DC6EF2A}") JCancellationSignal  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl cancel() = 0 ;
	virtual bool __cdecl isCanceled() = 0 ;
	virtual void __cdecl setOnCancelListener(_di_JCancellationSignal_OnCancelListener listener) = 0 ;
	virtual void __cdecl throwIfCanceled() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCancellationSignal : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCancellationSignalClass,_di_JCancellationSignal>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCancellationSignalClass,_di_JCancellationSignal> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCancellationSignal() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCancellationSignalClass,_di_JCancellationSignal>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCancellationSignal() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C5DA883A-D40B-4567-93D7-B7D9EB1399EA}") JCancellationSignal_OnCancelListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{6B0E6041-7C1B-4911-8FC3-167328179B8C}") JCancellationSignal_OnCancelListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCancel() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCancellationSignal_OnCancelListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCancellationSignal_OnCancelListenerClass,_di_JCancellationSignal_OnCancelListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCancellationSignal_OnCancelListenerClass,_di_JCancellationSignal_OnCancelListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCancellationSignal_OnCancelListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCancellationSignal_OnCancelListenerClass,_di_JCancellationSignal_OnCancelListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCancellationSignal_OnCancelListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3048CDA3-574F-455F-B26C-9535F0644AF5}") JDebug_MemoryInfoClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JDebug_MemoryInfo __cdecl init() = 0 ;
	__property _di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{7D2ECE2E-A223-4DD4-8964-4E53F21B8BE2}") JDebug_MemoryInfo  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl _GetdalvikPrivateDirty() = 0 ;
	virtual void __cdecl _SetdalvikPrivateDirty(int Value) = 0 ;
	virtual int __cdecl _GetdalvikPss() = 0 ;
	virtual void __cdecl _SetdalvikPss(int Value) = 0 ;
	virtual int __cdecl _GetdalvikSharedDirty() = 0 ;
	virtual void __cdecl _SetdalvikSharedDirty(int Value) = 0 ;
	virtual int __cdecl _GetnativePrivateDirty() = 0 ;
	virtual void __cdecl _SetnativePrivateDirty(int Value) = 0 ;
	virtual int __cdecl _GetnativePss() = 0 ;
	virtual void __cdecl _SetnativePss(int Value) = 0 ;
	virtual int __cdecl _GetnativeSharedDirty() = 0 ;
	virtual void __cdecl _SetnativeSharedDirty(int Value) = 0 ;
	virtual int __cdecl _GetotherPrivateDirty() = 0 ;
	virtual void __cdecl _SetotherPrivateDirty(int Value) = 0 ;
	virtual int __cdecl _GetotherPss() = 0 ;
	virtual void __cdecl _SetotherPss(int Value) = 0 ;
	virtual int __cdecl _GetotherSharedDirty() = 0 ;
	virtual void __cdecl _SetotherSharedDirty(int Value) = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMemoryStat(Androidapi::Jni::Javatypes::_di_JString statName) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl getMemoryStats() = 0 ;
	virtual int __cdecl getTotalPrivateClean() = 0 ;
	virtual int __cdecl getTotalPrivateDirty() = 0 ;
	virtual int __cdecl getTotalPss() = 0 ;
	virtual int __cdecl getTotalSharedClean() = 0 ;
	virtual int __cdecl getTotalSharedDirty() = 0 ;
	virtual int __cdecl getTotalSwappablePss() = 0 ;
	virtual void __cdecl readFromParcel(_di_JParcel source) = 0 ;
	virtual void __cdecl writeToParcel(_di_JParcel dest, int flags) = 0 ;
	__property int dalvikPrivateDirty = {read=_GetdalvikPrivateDirty, write=_SetdalvikPrivateDirty};
	__property int dalvikPss = {read=_GetdalvikPss, write=_SetdalvikPss};
	__property int dalvikSharedDirty = {read=_GetdalvikSharedDirty, write=_SetdalvikSharedDirty};
	__property int nativePrivateDirty = {read=_GetnativePrivateDirty, write=_SetnativePrivateDirty};
	__property int nativePss = {read=_GetnativePss, write=_SetnativePss};
	__property int nativeSharedDirty = {read=_GetnativeSharedDirty, write=_SetnativeSharedDirty};
	__property int otherPrivateDirty = {read=_GetotherPrivateDirty, write=_SetotherPrivateDirty};
	__property int otherPss = {read=_GetotherPss, write=_SetotherPss};
	__property int otherSharedDirty = {read=_GetotherSharedDirty, write=_SetotherSharedDirty};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDebug_MemoryInfo : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDebug_MemoryInfoClass,_di_JDebug_MemoryInfo>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDebug_MemoryInfoClass,_di_JDebug_MemoryInfo> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDebug_MemoryInfo() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDebug_MemoryInfoClass,_di_JDebug_MemoryInfo>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDebug_MemoryInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6DFA74DD-1C38-4654-A690-215B98106A9E}") JHandlerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JHandler __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JHandler __cdecl init(_di_JHandler_Callback callback) = 0 /* overload */;
	HIDESBASE virtual _di_JHandler __cdecl init(_di_JLooper looper) = 0 /* overload */;
	HIDESBASE virtual _di_JHandler __cdecl init(_di_JLooper looper, _di_JHandler_Callback callback) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{9D5EF727-535C-41E1-8459-570107053097}") JHandler  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl dispatchMessage(_di_JMessage msg) = 0 ;
	virtual void __cdecl dump(Androidapi::Jni::Util::_di_JPrinter pw, Androidapi::Jni::Javatypes::_di_JString prefix) = 0 ;
	virtual _di_JLooper __cdecl getLooper() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMessageName(_di_JMessage message) = 0 ;
	virtual void __cdecl handleMessage(_di_JMessage msg) = 0 ;
	virtual bool __cdecl hasMessages(int what) = 0 /* overload */;
	virtual bool __cdecl hasMessages(int what, Androidapi::Jni::Javatypes::_di_JObject object_) = 0 /* overload */;
	virtual _di_JMessage __cdecl obtainMessage() = 0 /* overload */;
	virtual _di_JMessage __cdecl obtainMessage(int what) = 0 /* overload */;
	virtual _di_JMessage __cdecl obtainMessage(int what, Androidapi::Jni::Javatypes::_di_JObject obj) = 0 /* overload */;
	virtual _di_JMessage __cdecl obtainMessage(int what, int arg1, int arg2) = 0 /* overload */;
	virtual _di_JMessage __cdecl obtainMessage(int what, int arg1, int arg2, Androidapi::Jni::Javatypes::_di_JObject obj) = 0 /* overload */;
	virtual bool __cdecl post(Androidapi::Jni::Javatypes::_di_JRunnable r) = 0 ;
	virtual bool __cdecl postAtFrontOfQueue(Androidapi::Jni::Javatypes::_di_JRunnable r) = 0 ;
	virtual bool __cdecl postAtTime(Androidapi::Jni::Javatypes::_di_JRunnable r, __int64 uptimeMillis) = 0 /* overload */;
	virtual bool __cdecl postAtTime(Androidapi::Jni::Javatypes::_di_JRunnable r, Androidapi::Jni::Javatypes::_di_JObject token, __int64 uptimeMillis) = 0 /* overload */;
	virtual bool __cdecl postDelayed(Androidapi::Jni::Javatypes::_di_JRunnable r, __int64 delayMillis) = 0 ;
	virtual void __cdecl removeCallbacks(Androidapi::Jni::Javatypes::_di_JRunnable r) = 0 /* overload */;
	virtual void __cdecl removeCallbacks(Androidapi::Jni::Javatypes::_di_JRunnable r, Androidapi::Jni::Javatypes::_di_JObject token) = 0 /* overload */;
	virtual void __cdecl removeCallbacksAndMessages(Androidapi::Jni::Javatypes::_di_JObject token) = 0 ;
	virtual void __cdecl removeMessages(int what) = 0 /* overload */;
	virtual void __cdecl removeMessages(int what, Androidapi::Jni::Javatypes::_di_JObject object_) = 0 /* overload */;
	virtual bool __cdecl sendEmptyMessage(int what) = 0 ;
	virtual bool __cdecl sendEmptyMessageAtTime(int what, __int64 uptimeMillis) = 0 ;
	virtual bool __cdecl sendEmptyMessageDelayed(int what, __int64 delayMillis) = 0 ;
	virtual bool __cdecl sendMessage(_di_JMessage msg) = 0 ;
	virtual bool __cdecl sendMessageAtFrontOfQueue(_di_JMessage msg) = 0 ;
	virtual bool __cdecl sendMessageAtTime(_di_JMessage msg, __int64 uptimeMillis) = 0 ;
	virtual bool __cdecl sendMessageDelayed(_di_JMessage msg, __int64 delayMillis) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJHandler : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHandlerClass,_di_JHandler>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHandlerClass,_di_JHandler> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJHandler() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHandlerClass,_di_JHandler>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{56610FAC-0DB7-4E6C-9DE7-34BC98A7CF57}") JHandler_CallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{347B7489-1A0D-4B7E-BA98-26BF948DA15B}") JHandler_Callback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual bool __cdecl handleMessage(_di_JMessage msg) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJHandler_Callback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHandler_CallbackClass,_di_JHandler_Callback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHandler_CallbackClass,_di_JHandler_Callback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJHandler_Callback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHandler_CallbackClass,_di_JHandler_Callback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJHandler_Callback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B828015B-B3B1-4DD6-8456-4B2211BCFDF6}") JHandlerThreadClass  : public Androidapi::Jni::Javatypes::JThreadClass 
{
	HIDESBASE virtual _di_JHandlerThread __cdecl init(Androidapi::Jni::Javatypes::_di_JString name) = 0 /* overload */;
	HIDESBASE virtual _di_JHandlerThread __cdecl init(Androidapi::Jni::Javatypes::_di_JString name, int priority) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{D0282CAB-3444-4012-A806-BD4AEFEBBAA5}") JHandlerThread  : public Androidapi::Jni::Javatypes::JThread 
{
	virtual _di_JLooper __cdecl getLooper() = 0 ;
	virtual int __cdecl getThreadId() = 0 ;
	virtual bool __cdecl quit() = 0 ;
	virtual bool __cdecl quitSafely() = 0 ;
	HIDESBASE virtual void __cdecl run() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJHandlerThread : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHandlerThreadClass,_di_JHandlerThread>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHandlerThreadClass,_di_JHandlerThread> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJHandlerThread() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHandlerThreadClass,_di_JHandlerThread>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJHandlerThread() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{39FDECDD-962B-44DB-80B1-BA608C7F6F22}") JIBinderClass  : public Androidapi::Jnibridge::IJavaClass 
{
	virtual int __cdecl _GetDUMP_TRANSACTION() = 0 ;
	virtual int __cdecl _GetFIRST_CALL_TRANSACTION() = 0 ;
	virtual int __cdecl _GetFLAG_ONEWAY() = 0 ;
	virtual int __cdecl _GetINTERFACE_TRANSACTION() = 0 ;
	virtual int __cdecl _GetLAST_CALL_TRANSACTION() = 0 ;
	virtual int __cdecl _GetLIKE_TRANSACTION() = 0 ;
	virtual int __cdecl _GetPING_TRANSACTION() = 0 ;
	virtual int __cdecl _GetTWEET_TRANSACTION() = 0 ;
	__property int DUMP_TRANSACTION = {read=_GetDUMP_TRANSACTION};
	__property int FIRST_CALL_TRANSACTION = {read=_GetFIRST_CALL_TRANSACTION};
	__property int FLAG_ONEWAY = {read=_GetFLAG_ONEWAY};
	__property int INTERFACE_TRANSACTION = {read=_GetINTERFACE_TRANSACTION};
	__property int LAST_CALL_TRANSACTION = {read=_GetLAST_CALL_TRANSACTION};
	__property int LIKE_TRANSACTION = {read=_GetLIKE_TRANSACTION};
	__property int PING_TRANSACTION = {read=_GetPING_TRANSACTION};
	__property int TWEET_TRANSACTION = {read=_GetTWEET_TRANSACTION};
};

__interface  INTERFACE_UUID("{9DCFD46A-EA83-48EB-87BC-B18A3D9284E0}") JIBinder  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl dump(Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* args) = 0 ;
	virtual void __cdecl dumpAsync(Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* args) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getInterfaceDescriptor() = 0 ;
	virtual bool __cdecl isBinderAlive() = 0 ;
	virtual void __cdecl linkToDeath(_di_JIBinder_DeathRecipient recipient, int flags) = 0 ;
	virtual bool __cdecl pingBinder() = 0 ;
	virtual _di_JIInterface __cdecl queryLocalInterface(Androidapi::Jni::Javatypes::_di_JString descriptor) = 0 ;
	virtual bool __cdecl transact(int code, _di_JParcel data, _di_JParcel reply, int flags) = 0 ;
	virtual bool __cdecl unlinkToDeath(_di_JIBinder_DeathRecipient recipient, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJIBinder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIBinderClass,_di_JIBinder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIBinderClass,_di_JIBinder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJIBinder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIBinderClass,_di_JIBinder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJIBinder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0BB1DF5F-6D10-4BDE-B1FD-00479125622E}") JIBinder_DeathRecipientClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{C23CFA91-43FE-4E30-86C2-5F125D7F01E0}") JIBinder_DeathRecipient  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl binderDied() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJIBinder_DeathRecipient : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIBinder_DeathRecipientClass,_di_JIBinder_DeathRecipient>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIBinder_DeathRecipientClass,_di_JIBinder_DeathRecipient> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJIBinder_DeathRecipient() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIBinder_DeathRecipientClass,_di_JIBinder_DeathRecipient>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJIBinder_DeathRecipient() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5C536661-DE48-4AEF-B371-51FFBFB39875}") JIInterfaceClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{CCF0440C-DEDC-468C-952A-8EB7637E0E57}") JIInterface  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual _di_JIBinder __cdecl asBinder() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJIInterface : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIInterfaceClass,_di_JIInterface>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIInterfaceClass,_di_JIInterface> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJIInterface() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIInterfaceClass,_di_JIInterface>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJIInterface() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{46C8C965-7921-43D7-B7F7-272946E90586}") JLocaleListClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual _di_JLocaleList __cdecl forLanguageTags(Androidapi::Jni::Javatypes::_di_JString list) = 0 ;
	virtual _di_JLocaleList __cdecl getAdjustedDefault() = 0 ;
	virtual _di_JLocaleList __cdecl getDefault() = 0 ;
	virtual _di_JLocaleList __cdecl getEmptyLocaleList() = 0 ;
	virtual void __cdecl setDefault(_di_JLocaleList locales) = 0 ;
	__property _di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{1BF27FFB-8F03-4E68-8831-B891DE2E2312}") JLocaleList  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject other) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JLocale __cdecl get(int index) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JLocale __cdecl getFirstMatch(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* supportedLocales) = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual int __cdecl indexOf(Androidapi::Jni::Javatypes::_di_JLocale locale) = 0 ;
	virtual bool __cdecl isEmpty() = 0 ;
	virtual int __cdecl size() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toLanguageTags() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(_di_JParcel dest, int parcelableFlags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLocaleList : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocaleListClass,_di_JLocaleList>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocaleListClass,_di_JLocaleList> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLocaleList() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLocaleListClass,_di_JLocaleList>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLocaleList() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EDF411AD-10E9-46B9-851F-0BF490BEBDEA}") JLooperClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JLooper __cdecl getMainLooper() = 0 ;
	virtual void __cdecl loop() = 0 ;
	virtual _di_JLooper __cdecl myLooper() = 0 ;
	virtual _di_JMessageQueue __cdecl myQueue() = 0 ;
	virtual void __cdecl prepare() = 0 ;
	virtual void __cdecl prepareMainLooper() = 0 ;
};

__interface  INTERFACE_UUID("{C7E0949B-044A-41EB-A38F-87D18DB4750E}") JLooper  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl dump(Androidapi::Jni::Util::_di_JPrinter pw, Androidapi::Jni::Javatypes::_di_JString prefix) = 0 ;
	virtual _di_JMessageQueue __cdecl getQueue() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JThread __cdecl getThread() = 0 ;
	virtual bool __cdecl isCurrentThread() = 0 ;
	virtual void __cdecl quit() = 0 ;
	virtual void __cdecl quitSafely() = 0 ;
	virtual void __cdecl setMessageLogging(Androidapi::Jni::Util::_di_JPrinter printer) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLooper : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLooperClass,_di_JLooper>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLooperClass,_di_JLooper> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLooper() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLooperClass,_di_JLooper>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLooper() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1B2538A8-B0AD-4E06-B2E5-80EF21543420}") JMessageClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JMessage __cdecl init() = 0 ;
	virtual _di_JMessage __cdecl obtain() = 0 /* overload */;
	virtual _di_JMessage __cdecl obtain(_di_JMessage orig) = 0 /* overload */;
	virtual _di_JMessage __cdecl obtain(_di_JHandler h) = 0 /* overload */;
	virtual _di_JMessage __cdecl obtain(_di_JHandler h, Androidapi::Jni::Javatypes::_di_JRunnable callback) = 0 /* overload */;
	virtual _di_JMessage __cdecl obtain(_di_JHandler h, int what) = 0 /* overload */;
	virtual _di_JMessage __cdecl obtain(_di_JHandler h, int what, Androidapi::Jni::Javatypes::_di_JObject obj) = 0 /* overload */;
	virtual _di_JMessage __cdecl obtain(_di_JHandler h, int what, int arg1, int arg2) = 0 /* overload */;
	virtual _di_JMessage __cdecl obtain(_di_JHandler h, int what, int arg1, int arg2, Androidapi::Jni::Javatypes::_di_JObject obj) = 0 /* overload */;
	__property _di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{6BD63150-99D3-4A77-A12D-41F00022009A}") JMessage  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl _Getarg1() = 0 ;
	virtual void __cdecl _Setarg1(int Value) = 0 ;
	virtual int __cdecl _Getarg2() = 0 ;
	virtual void __cdecl _Setarg2(int Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl _Getobj() = 0 ;
	virtual void __cdecl _Setobj(Androidapi::Jni::Javatypes::_di_JObject Value) = 0 ;
	virtual _di_JMessenger __cdecl _GetreplyTo() = 0 ;
	virtual void __cdecl _SetreplyTo(_di_JMessenger Value) = 0 ;
	virtual int __cdecl _GetsendingUid() = 0 ;
	virtual void __cdecl _SetsendingUid(int Value) = 0 ;
	virtual int __cdecl _Getwhat() = 0 ;
	virtual void __cdecl _Setwhat(int Value) = 0 ;
	virtual void __cdecl copyFrom(_di_JMessage o) = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JRunnable __cdecl getCallback() = 0 ;
	virtual _di_JBundle __cdecl getData() = 0 ;
	virtual _di_JHandler __cdecl getTarget() = 0 ;
	virtual __int64 __cdecl getWhen() = 0 ;
	virtual bool __cdecl isAsynchronous() = 0 ;
	virtual _di_JBundle __cdecl peekData() = 0 ;
	virtual void __cdecl recycle() = 0 ;
	virtual void __cdecl sendToTarget() = 0 ;
	virtual void __cdecl setAsynchronous(bool async) = 0 ;
	virtual void __cdecl setData(_di_JBundle data) = 0 ;
	virtual void __cdecl setTarget(_di_JHandler target) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(_di_JParcel dest, int flags) = 0 ;
	__property int arg1 = {read=_Getarg1, write=_Setarg1};
	__property int arg2 = {read=_Getarg2, write=_Setarg2};
	__property Androidapi::Jni::Javatypes::_di_JObject obj = {read=_Getobj, write=_Setobj};
	__property _di_JMessenger replyTo = {read=_GetreplyTo, write=_SetreplyTo};
	__property int sendingUid = {read=_GetsendingUid, write=_SetsendingUid};
	__property int what = {read=_Getwhat, write=_Setwhat};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMessage : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessageClass,_di_JMessage>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessageClass,_di_JMessage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMessage() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessageClass,_di_JMessage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C3690F20-6E73-4103-B86F-02B72CC58D9E}") JMessageQueueClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{73ED03E5-98F2-49F7-970D-B96D3B54F339}") JMessageQueue  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl addIdleHandler(_di_JMessageQueue_IdleHandler handler) = 0 ;
	virtual void __cdecl addOnFileDescriptorEventListener(Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, int events, _di_JMessageQueue_OnFileDescriptorEventListener listener) = 0 ;
	virtual bool __cdecl isIdle() = 0 ;
	virtual void __cdecl removeIdleHandler(_di_JMessageQueue_IdleHandler handler) = 0 ;
	virtual void __cdecl removeOnFileDescriptorEventListener(Androidapi::Jni::Javatypes::_di_JFileDescriptor fd) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMessageQueue : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessageQueueClass,_di_JMessageQueue>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessageQueueClass,_di_JMessageQueue> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMessageQueue() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessageQueueClass,_di_JMessageQueue>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMessageQueue() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5AA2B208-7429-47C2-824A-B9A94B306B83}") JMessageQueue_IdleHandlerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{36B80D1E-6D2E-421C-A29D-E7435F3023DE}") JMessageQueue_IdleHandler  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual bool __cdecl queueIdle() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMessageQueue_IdleHandler : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessageQueue_IdleHandlerClass,_di_JMessageQueue_IdleHandler>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessageQueue_IdleHandlerClass,_di_JMessageQueue_IdleHandler> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMessageQueue_IdleHandler() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessageQueue_IdleHandlerClass,_di_JMessageQueue_IdleHandler>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMessageQueue_IdleHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2B65AB49-2C3D-4520-8259-442A93E185C8}") JMessageQueue_OnFileDescriptorEventListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	virtual int __cdecl _GetEVENT_ERROR() = 0 ;
	virtual int __cdecl _GetEVENT_INPUT() = 0 ;
	virtual int __cdecl _GetEVENT_OUTPUT() = 0 ;
	__property int EVENT_ERROR = {read=_GetEVENT_ERROR};
	__property int EVENT_INPUT = {read=_GetEVENT_INPUT};
	__property int EVENT_OUTPUT = {read=_GetEVENT_OUTPUT};
};

__interface  INTERFACE_UUID("{D23AA2CE-AE16-478A-A9D3-5EB63F3500E2}") JMessageQueue_OnFileDescriptorEventListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual int __cdecl onFileDescriptorEvents(Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, int events) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMessageQueue_OnFileDescriptorEventListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessageQueue_OnFileDescriptorEventListenerClass,_di_JMessageQueue_OnFileDescriptorEventListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessageQueue_OnFileDescriptorEventListenerClass,_di_JMessageQueue_OnFileDescriptorEventListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMessageQueue_OnFileDescriptorEventListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessageQueue_OnFileDescriptorEventListenerClass,_di_JMessageQueue_OnFileDescriptorEventListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMessageQueue_OnFileDescriptorEventListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F56C4382-C9CD-44C5-8FD9-ED57F2EB7020}") JMessengerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JMessenger __cdecl init(_di_JHandler target) = 0 /* overload */;
	HIDESBASE virtual _di_JMessenger __cdecl init(_di_JIBinder target) = 0 /* overload */;
	virtual _di_JMessenger __cdecl readMessengerOrNullFromParcel(_di_JParcel in_) = 0 ;
	virtual void __cdecl writeMessengerOrNullToParcel(_di_JMessenger messenger, _di_JParcel out_) = 0 ;
	__property _di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{5DB42D38-8B04-4E46-BB40-71E75131EE34}") JMessenger  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject otherObj) = 0 ;
	virtual _di_JIBinder __cdecl getBinder() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual void __cdecl send(_di_JMessage message) = 0 ;
	virtual void __cdecl writeToParcel(_di_JParcel out_, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMessenger : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessengerClass,_di_JMessenger>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessengerClass,_di_JMessenger> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMessenger() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessengerClass,_di_JMessenger>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMessenger() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4221C753-227D-4D4A-8F17-7897C2BD8870}") JParcelClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JParcelable_Creator __cdecl _GetSTRING_CREATOR() = 0 ;
	virtual _di_JParcel __cdecl obtain() = 0 ;
	__property _di_JParcelable_Creator STRING_CREATOR = {read=_GetSTRING_CREATOR};
};

__interface  INTERFACE_UUID("{4E777D3D-D7CB-4157-9ED0-F956FB00B18E}") JParcel  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl appendFrom(_di_JParcel parcel, int offset, int length) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JIBinder>* __cdecl createBinderArray() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JArrayList __cdecl createBinderArrayList() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<bool>* __cdecl createBooleanArray() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl createByteArray() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::WideChar>* __cdecl createCharArray() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<double>* __cdecl createDoubleArray() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<float>* __cdecl createFloatArray() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<int>* __cdecl createIntArray() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<__int64>* __cdecl createLongArray() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl createStringArray() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JArrayList __cdecl createStringArrayList() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JObject>* __cdecl createTypedArray(_di_JParcelable_Creator c) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JArrayList __cdecl createTypedArrayList(_di_JParcelable_Creator c) = 0 ;
	virtual int __cdecl dataAvail() = 0 ;
	virtual int __cdecl dataCapacity() = 0 ;
	virtual int __cdecl dataPosition() = 0 ;
	virtual int __cdecl dataSize() = 0 ;
	virtual void __cdecl enforceInterface(Androidapi::Jni::Javatypes::_di_JString interfaceName) = 0 ;
	virtual bool __cdecl hasFileDescriptors() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl marshall() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JObject>* __cdecl readArray(Androidapi::Jni::Javatypes::_di_JClassLoader loader) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JArrayList __cdecl readArrayList(Androidapi::Jni::Javatypes::_di_JClassLoader loader) = 0 ;
	virtual void __cdecl readBinderArray(Androidapi::Jnibridge::TJavaObjectArray__1<_di_JIBinder>* val) = 0 ;
	virtual void __cdecl readBinderList(Androidapi::Jni::Javatypes::_di_JList list) = 0 ;
	virtual void __cdecl readBooleanArray(Androidapi::Jnibridge::TJavaArray__1<bool>* val) = 0 ;
	virtual _di_JBundle __cdecl readBundle() = 0 /* overload */;
	virtual _di_JBundle __cdecl readBundle(Androidapi::Jni::Javatypes::_di_JClassLoader loader) = 0 /* overload */;
	virtual System::Byte __cdecl readByte() = 0 ;
	virtual void __cdecl readByteArray(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* val) = 0 ;
	virtual void __cdecl readCharArray(Androidapi::Jnibridge::TJavaArray__1<System::WideChar>* val) = 0 ;
	virtual double __cdecl readDouble() = 0 ;
	virtual void __cdecl readDoubleArray(Androidapi::Jnibridge::TJavaArray__1<double>* val) = 0 ;
	virtual void __cdecl readException() = 0 /* overload */;
	virtual void __cdecl readException(int code, Androidapi::Jni::Javatypes::_di_JString msg) = 0 /* overload */;
	virtual _di_JParcelFileDescriptor __cdecl readFileDescriptor() = 0 ;
	virtual float __cdecl readFloat() = 0 ;
	virtual void __cdecl readFloatArray(Androidapi::Jnibridge::TJavaArray__1<float>* val) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JHashMap __cdecl readHashMap(Androidapi::Jni::Javatypes::_di_JClassLoader loader) = 0 ;
	virtual int __cdecl readInt() = 0 ;
	virtual void __cdecl readIntArray(Androidapi::Jnibridge::TJavaArray__1<int>* val) = 0 ;
	virtual void __cdecl readList(Androidapi::Jni::Javatypes::_di_JList outVal, Androidapi::Jni::Javatypes::_di_JClassLoader loader) = 0 ;
	virtual __int64 __cdecl readLong() = 0 ;
	virtual void __cdecl readLongArray(Androidapi::Jnibridge::TJavaArray__1<__int64>* val) = 0 ;
	virtual void __cdecl readMap(Androidapi::Jni::Javatypes::_di_JMap outVal, Androidapi::Jni::Javatypes::_di_JClassLoader loader) = 0 ;
	virtual _di_JParcelable __cdecl readParcelable(Androidapi::Jni::Javatypes::_di_JClassLoader loader) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JParcelable>* __cdecl readParcelableArray(Androidapi::Jni::Javatypes::_di_JClassLoader loader) = 0 ;
	virtual _di_JPersistableBundle __cdecl readPersistableBundle() = 0 /* overload */;
	virtual _di_JPersistableBundle __cdecl readPersistableBundle(Androidapi::Jni::Javatypes::_di_JClassLoader loader) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JSerializable __cdecl readSerializable() = 0 ;
	virtual Androidapi::Jni::Util::_di_Jutil_Size __cdecl readSize() = 0 ;
	virtual Androidapi::Jni::Util::_di_JSizeF __cdecl readSizeF() = 0 ;
	virtual Androidapi::Jni::Util::_di_JSparseArray __cdecl readSparseArray(Androidapi::Jni::Javatypes::_di_JClassLoader loader) = 0 ;
	virtual Androidapi::Jni::Util::_di_JSparseBooleanArray __cdecl readSparseBooleanArray() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl readString() = 0 ;
	virtual void __cdecl readStringArray(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* val) = 0 ;
	virtual void __cdecl readStringList(Androidapi::Jni::Javatypes::_di_JList list) = 0 ;
	virtual _di_JIBinder __cdecl readStrongBinder() = 0 ;
	virtual void __cdecl readTypedArray(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JObject>* val, _di_JParcelable_Creator c) = 0 ;
	virtual void __cdecl readTypedList(Androidapi::Jni::Javatypes::_di_JList list, _di_JParcelable_Creator c) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl readTypedObject(_di_JParcelable_Creator c) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl readValue(Androidapi::Jni::Javatypes::_di_JClassLoader loader) = 0 ;
	virtual void __cdecl recycle() = 0 ;
	virtual void __cdecl setDataCapacity(int size) = 0 ;
	virtual void __cdecl setDataPosition(int pos) = 0 ;
	virtual void __cdecl setDataSize(int size) = 0 ;
	virtual void __cdecl unmarshall(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* data, int offset, int length) = 0 ;
	virtual void __cdecl writeArray(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JObject>* val) = 0 ;
	virtual void __cdecl writeBinderArray(Androidapi::Jnibridge::TJavaObjectArray__1<_di_JIBinder>* val) = 0 ;
	virtual void __cdecl writeBinderList(Androidapi::Jni::Javatypes::_di_JList val) = 0 ;
	virtual void __cdecl writeBooleanArray(Androidapi::Jnibridge::TJavaArray__1<bool>* val) = 0 ;
	virtual void __cdecl writeBundle(_di_JBundle val) = 0 ;
	virtual void __cdecl writeByte(System::Byte val) = 0 ;
	virtual void __cdecl writeByteArray(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* b) = 0 /* overload */;
	virtual void __cdecl writeByteArray(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* b, int offset, int len) = 0 /* overload */;
	virtual void __cdecl writeCharArray(Androidapi::Jnibridge::TJavaArray__1<System::WideChar>* val) = 0 ;
	virtual void __cdecl writeDouble(double val) = 0 ;
	virtual void __cdecl writeDoubleArray(Androidapi::Jnibridge::TJavaArray__1<double>* val) = 0 ;
	virtual void __cdecl writeException(Androidapi::Jni::Javatypes::_di_JException e) = 0 ;
	virtual void __cdecl writeFileDescriptor(Androidapi::Jni::Javatypes::_di_JFileDescriptor val) = 0 ;
	virtual void __cdecl writeFloat(float val) = 0 ;
	virtual void __cdecl writeFloatArray(Androidapi::Jnibridge::TJavaArray__1<float>* val) = 0 ;
	virtual void __cdecl writeInt(int val) = 0 ;
	virtual void __cdecl writeIntArray(Androidapi::Jnibridge::TJavaArray__1<int>* val) = 0 ;
	virtual void __cdecl writeInterfaceToken(Androidapi::Jni::Javatypes::_di_JString interfaceName) = 0 ;
	virtual void __cdecl writeList(Androidapi::Jni::Javatypes::_di_JList val) = 0 ;
	virtual void __cdecl writeLong(__int64 val) = 0 ;
	virtual void __cdecl writeLongArray(Androidapi::Jnibridge::TJavaArray__1<__int64>* val) = 0 ;
	virtual void __cdecl writeMap(Androidapi::Jni::Javatypes::_di_JMap val) = 0 ;
	virtual void __cdecl writeNoException() = 0 ;
	virtual void __cdecl writeParcelable(_di_JParcelable p, int parcelableFlags) = 0 ;
	virtual void __cdecl writeParcelableArray(Androidapi::Jnibridge::TJavaObjectArray__1<_di_JParcelable>* value, int parcelableFlags) = 0 ;
	virtual void __cdecl writePersistableBundle(_di_JPersistableBundle val) = 0 ;
	virtual void __cdecl writeSerializable(Androidapi::Jni::Javatypes::_di_JSerializable s) = 0 ;
	virtual void __cdecl writeSize(Androidapi::Jni::Util::_di_Jutil_Size val) = 0 ;
	virtual void __cdecl writeSizeF(Androidapi::Jni::Util::_di_JSizeF val) = 0 ;
	virtual void __cdecl writeSparseArray(Androidapi::Jni::Util::_di_JSparseArray val) = 0 ;
	virtual void __cdecl writeSparseBooleanArray(Androidapi::Jni::Util::_di_JSparseBooleanArray val) = 0 ;
	virtual void __cdecl writeString(Androidapi::Jni::Javatypes::_di_JString val) = 0 ;
	virtual void __cdecl writeStringArray(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* val) = 0 ;
	virtual void __cdecl writeStringList(Androidapi::Jni::Javatypes::_di_JList val) = 0 ;
	virtual void __cdecl writeStrongBinder(_di_JIBinder val) = 0 ;
	virtual void __cdecl writeStrongInterface(_di_JIInterface val) = 0 ;
	virtual void __cdecl writeTypedArray(Androidapi::Jnibridge::TJavaObjectArray__1<_di_JParcelable>* val, int parcelableFlags) = 0 ;
	virtual void __cdecl writeTypedList(Androidapi::Jni::Javatypes::_di_JList val) = 0 ;
	virtual void __cdecl writeTypedObject(_di_JParcelable val, int parcelableFlags) = 0 ;
	virtual void __cdecl writeValue(Androidapi::Jni::Javatypes::_di_JObject v) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJParcel : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelClass,_di_JParcel>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelClass,_di_JParcel> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJParcel() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelClass,_di_JParcel>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJParcel() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FFBFF8DF-F6F4-4EB2-A73D-0B2E753BD03D}") JParcelFileDescriptorClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetMODE_APPEND() = 0 ;
	virtual int __cdecl _GetMODE_CREATE() = 0 ;
	virtual int __cdecl _GetMODE_READ_ONLY() = 0 ;
	virtual int __cdecl _GetMODE_READ_WRITE() = 0 ;
	virtual int __cdecl _GetMODE_TRUNCATE() = 0 ;
	virtual int __cdecl _GetMODE_WORLD_READABLE() = 0 ;
	virtual int __cdecl _GetMODE_WORLD_WRITEABLE() = 0 ;
	virtual int __cdecl _GetMODE_WRITE_ONLY() = 0 ;
	HIDESBASE virtual _di_JParcelFileDescriptor __cdecl init(_di_JParcelFileDescriptor wrapped) = 0 ;
	virtual _di_JParcelFileDescriptor __cdecl adoptFd(int fd) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JParcelFileDescriptor>* __cdecl createPipe() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JParcelFileDescriptor>* __cdecl createReliablePipe() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JParcelFileDescriptor>* __cdecl createReliableSocketPair() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JParcelFileDescriptor>* __cdecl createSocketPair() = 0 ;
	virtual _di_JParcelFileDescriptor __cdecl dup(Androidapi::Jni::Javatypes::_di_JFileDescriptor orig) = 0 /* overload */;
	virtual _di_JParcelFileDescriptor __cdecl fromFd(int fd) = 0 ;
	virtual _di_JParcelFileDescriptor __cdecl open(Androidapi::Jni::Javatypes::_di_JFile file_, int mode) = 0 /* overload */;
	virtual _di_JParcelFileDescriptor __cdecl open(Androidapi::Jni::Javatypes::_di_JFile file_, int mode, _di_JHandler handler, _di_JParcelFileDescriptor_OnCloseListener listener) = 0 /* overload */;
	virtual int __cdecl parseMode(Androidapi::Jni::Javatypes::_di_JString mode) = 0 ;
	__property _di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int MODE_APPEND = {read=_GetMODE_APPEND};
	__property int MODE_CREATE = {read=_GetMODE_CREATE};
	__property int MODE_READ_ONLY = {read=_GetMODE_READ_ONLY};
	__property int MODE_READ_WRITE = {read=_GetMODE_READ_WRITE};
	__property int MODE_TRUNCATE = {read=_GetMODE_TRUNCATE};
	__property int MODE_WORLD_READABLE = {read=_GetMODE_WORLD_READABLE};
	__property int MODE_WORLD_WRITEABLE = {read=_GetMODE_WORLD_WRITEABLE};
	__property int MODE_WRITE_ONLY = {read=_GetMODE_WRITE_ONLY};
};

__interface  INTERFACE_UUID("{C1A682AA-6579-416E-868E-C951ED8FB338}") JParcelFileDescriptor  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl canDetectErrors() = 0 ;
	virtual void __cdecl checkError() = 0 ;
	virtual void __cdecl close() = 0 ;
	virtual void __cdecl closeWithError(Androidapi::Jni::Javatypes::_di_JString msg) = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual int __cdecl detachFd() = 0 ;
	virtual _di_JParcelFileDescriptor __cdecl dup() = 0 /* overload */;
	virtual int __cdecl getFd() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JFileDescriptor __cdecl getFileDescriptor() = 0 ;
	virtual __int64 __cdecl getStatSize() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(_di_JParcel out_, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJParcelFileDescriptor : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelFileDescriptorClass,_di_JParcelFileDescriptor>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelFileDescriptorClass,_di_JParcelFileDescriptor> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJParcelFileDescriptor() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelFileDescriptorClass,_di_JParcelFileDescriptor>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJParcelFileDescriptor() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5C32589D-9078-47EE-9BCC-B7E2C587ACEF}") JParcelFileDescriptor_AutoCloseInputStreamClass  : public Androidapi::Jni::Javatypes::JFileInputStreamClass 
{
	HIDESBASE virtual _di_JParcelFileDescriptor_AutoCloseInputStream __cdecl init(_di_JParcelFileDescriptor pfd) = 0 ;
};

__interface  INTERFACE_UUID("{28B7EEA4-CA6D-4565-AF0B-9AA87233C96B}") JParcelFileDescriptor_AutoCloseInputStream  : public Androidapi::Jni::Javatypes::JFileInputStream 
{
	HIDESBASE virtual void __cdecl close() = 0 ;
	HIDESBASE virtual int __cdecl read() = 0 /* overload */;
	HIDESBASE virtual int __cdecl read(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* b) = 0 /* overload */;
	HIDESBASE virtual int __cdecl read(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* b, int off, int len) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJParcelFileDescriptor_AutoCloseInputStream : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelFileDescriptor_AutoCloseInputStreamClass,_di_JParcelFileDescriptor_AutoCloseInputStream>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelFileDescriptor_AutoCloseInputStreamClass,_di_JParcelFileDescriptor_AutoCloseInputStream> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJParcelFileDescriptor_AutoCloseInputStream() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelFileDescriptor_AutoCloseInputStreamClass,_di_JParcelFileDescriptor_AutoCloseInputStream>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJParcelFileDescriptor_AutoCloseInputStream() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3DA3CB8C-5AF5-4ACD-915D-6BB844D37AC5}") JParcelFileDescriptor_AutoCloseOutputStreamClass  : public Androidapi::Jni::Javatypes::JFileOutputStreamClass 
{
	HIDESBASE virtual _di_JParcelFileDescriptor_AutoCloseOutputStream __cdecl init(_di_JParcelFileDescriptor pfd) = 0 ;
};

__interface  INTERFACE_UUID("{AC268DEA-CB4A-49D1-B14B-78950AD93E4F}") JParcelFileDescriptor_AutoCloseOutputStream  : public Androidapi::Jni::Javatypes::JFileOutputStream 
{
	HIDESBASE virtual void __cdecl close() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJParcelFileDescriptor_AutoCloseOutputStream : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelFileDescriptor_AutoCloseOutputStreamClass,_di_JParcelFileDescriptor_AutoCloseOutputStream>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelFileDescriptor_AutoCloseOutputStreamClass,_di_JParcelFileDescriptor_AutoCloseOutputStream> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJParcelFileDescriptor_AutoCloseOutputStream() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelFileDescriptor_AutoCloseOutputStreamClass,_di_JParcelFileDescriptor_AutoCloseOutputStream>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJParcelFileDescriptor_AutoCloseOutputStream() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F7A3B73F-80F9-4DD2-8B9D-4C0F6A3C9765}") JParcelFileDescriptor_OnCloseListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{B2ED31DD-67CA-4981-8707-B3B002F38505}") JParcelFileDescriptor_OnCloseListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onClose(Androidapi::Jni::Javatypes::_di_JIOException e) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJParcelFileDescriptor_OnCloseListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelFileDescriptor_OnCloseListenerClass,_di_JParcelFileDescriptor_OnCloseListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelFileDescriptor_OnCloseListenerClass,_di_JParcelFileDescriptor_OnCloseListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJParcelFileDescriptor_OnCloseListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelFileDescriptor_OnCloseListenerClass,_di_JParcelFileDescriptor_OnCloseListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJParcelFileDescriptor_OnCloseListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4AE7B935-7452-4EDB-B8D9-51A90A45DD54}") JParcelUuidClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JParcelUuid __cdecl init(Androidapi::Jni::Javatypes::_di_JUUID uuid) = 0 ;
	virtual _di_JParcelUuid __cdecl fromString(Androidapi::Jni::Javatypes::_di_JString uuid) = 0 ;
	__property _di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{B6E17AEC-B949-4660-820B-D09DE86EB7EA}") JParcelUuid  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JUUID __cdecl getUuid() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJParcelUuid : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelUuidClass,_di_JParcelUuid>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelUuidClass,_di_JParcelUuid> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJParcelUuid() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelUuidClass,_di_JParcelUuid>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJParcelUuid() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C4028E29-2B61-4CBE-86B0-E7AEB7DB6073}") JParcelableClass  : public Androidapi::Jnibridge::IJavaClass 
{
	virtual int __cdecl _GetCONTENTS_FILE_DESCRIPTOR() = 0 ;
	virtual int __cdecl _GetPARCELABLE_WRITE_RETURN_VALUE() = 0 ;
	__property int CONTENTS_FILE_DESCRIPTOR = {read=_GetCONTENTS_FILE_DESCRIPTOR};
	__property int PARCELABLE_WRITE_RETURN_VALUE = {read=_GetPARCELABLE_WRITE_RETURN_VALUE};
};

__interface  INTERFACE_UUID("{60865491-0B26-486B-A5EA-F137A0408CFD}") JParcelable  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual void __cdecl writeToParcel(_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJParcelable : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelableClass,_di_JParcelable>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelableClass,_di_JParcelable> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJParcelable() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelableClass,_di_JParcelable>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJParcelable() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BDBDE50C-1639-42B7-8880-F0DE45C12CE1}") JParcelable_CreatorClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{A2263E47-9FD8-4553-B31B-9EBB64A04843}") JParcelable_Creator  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl createFromParcel(_di_JParcel source) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JObject>* __cdecl newArray(int size) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJParcelable_Creator : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelable_CreatorClass,_di_JParcelable_Creator>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelable_CreatorClass,_di_JParcelable_Creator> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJParcelable_Creator() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelable_CreatorClass,_di_JParcelable_Creator>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJParcelable_Creator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AD975D2E-9776-4FED-8213-81FA6C89A7BA}") JParcelable_ClassLoaderCreatorClass  : public JParcelable_CreatorClass 
{
	
};

__interface  INTERFACE_UUID("{FCAFEC5F-1CCE-4991-B75D-9376254D7E15}") JParcelable_ClassLoaderCreator  : public JParcelable_Creator 
{
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl createFromParcel(_di_JParcel source, Androidapi::Jni::Javatypes::_di_JClassLoader loader) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJParcelable_ClassLoaderCreator : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelable_ClassLoaderCreatorClass,_di_JParcelable_ClassLoaderCreator>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelable_ClassLoaderCreatorClass,_di_JParcelable_ClassLoaderCreator> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJParcelable_ClassLoaderCreator() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JParcelable_ClassLoaderCreatorClass,_di_JParcelable_ClassLoaderCreator>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJParcelable_ClassLoaderCreator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5531BAAE-118E-44DB-8296-A24A9DCC4B84}") JPatternMatcherClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetPATTERN_ADVANCED_GLOB() = 0 ;
	virtual int __cdecl _GetPATTERN_LITERAL() = 0 ;
	virtual int __cdecl _GetPATTERN_PREFIX() = 0 ;
	virtual int __cdecl _GetPATTERN_SIMPLE_GLOB() = 0 ;
	HIDESBASE virtual _di_JPatternMatcher __cdecl init(Androidapi::Jni::Javatypes::_di_JString pattern, int type_) = 0 /* overload */;
	HIDESBASE virtual _di_JPatternMatcher __cdecl init(_di_JParcel src) = 0 /* overload */;
	__property _di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int PATTERN_ADVANCED_GLOB = {read=_GetPATTERN_ADVANCED_GLOB};
	__property int PATTERN_LITERAL = {read=_GetPATTERN_LITERAL};
	__property int PATTERN_PREFIX = {read=_GetPATTERN_PREFIX};
	__property int PATTERN_SIMPLE_GLOB = {read=_GetPATTERN_SIMPLE_GLOB};
};

__interface  INTERFACE_UUID("{FDB6AB90-AA53-4B07-A28D-9BD3FD65AF85}") JPatternMatcher  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPath() = 0 ;
	virtual int __cdecl getType() = 0 ;
	virtual bool __cdecl match(Androidapi::Jni::Javatypes::_di_JString str) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPatternMatcher : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPatternMatcherClass,_di_JPatternMatcher>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPatternMatcherClass,_di_JPatternMatcher> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPatternMatcher() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPatternMatcherClass,_di_JPatternMatcher>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPatternMatcher() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2B8F5539-AC2A-45D5-8370-6E34C5EA659E}") JPersistableBundleClass  : public JBaseBundleClass 
{
	virtual _di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual _di_JPersistableBundle __cdecl _GetEMPTY() = 0 ;
	HIDESBASE virtual _di_JPersistableBundle __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JPersistableBundle __cdecl init(int capacity) = 0 /* overload */;
	HIDESBASE virtual _di_JPersistableBundle __cdecl init(_di_JPersistableBundle b) = 0 /* overload */;
	__property _di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property _di_JPersistableBundle EMPTY = {read=_GetEMPTY};
};

__interface  INTERFACE_UUID("{077D0418-0AF5-4175-A444-A5A5D2F26924}") JPersistableBundle  : public JBaseBundle 
{
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl clone() = 0 ;
	virtual _di_JPersistableBundle __cdecl deepCopy() = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual _di_JPersistableBundle __cdecl getPersistableBundle(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual void __cdecl putPersistableBundle(Androidapi::Jni::Javatypes::_di_JString key, _di_JPersistableBundle value) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(_di_JParcel parcel, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPersistableBundle : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPersistableBundleClass,_di_JPersistableBundle>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPersistableBundleClass,_di_JPersistableBundle> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPersistableBundle() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPersistableBundleClass,_di_JPersistableBundle>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPersistableBundle() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E4AC8BDC-18D1-42AA-84A3-A1ACEAAEDAEF}") JPowerManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetACQUIRE_CAUSES_WAKEUP() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_DEVICE_IDLE_MODE_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_POWER_SAVE_MODE_CHANGED() = 0 ;
	virtual int __cdecl _GetFULL_WAKE_LOCK() = 0 ;
	virtual int __cdecl _GetON_AFTER_RELEASE() = 0 ;
	virtual int __cdecl _GetPARTIAL_WAKE_LOCK() = 0 ;
	virtual int __cdecl _GetPROXIMITY_SCREEN_OFF_WAKE_LOCK() = 0 ;
	virtual int __cdecl _GetRELEASE_FLAG_WAIT_FOR_NO_PROXIMITY() = 0 ;
	virtual int __cdecl _GetSCREEN_BRIGHT_WAKE_LOCK() = 0 ;
	virtual int __cdecl _GetSCREEN_DIM_WAKE_LOCK() = 0 ;
	__property int ACQUIRE_CAUSES_WAKEUP = {read=_GetACQUIRE_CAUSES_WAKEUP};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_DEVICE_IDLE_MODE_CHANGED = {read=_GetACTION_DEVICE_IDLE_MODE_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_POWER_SAVE_MODE_CHANGED = {read=_GetACTION_POWER_SAVE_MODE_CHANGED};
	__property int FULL_WAKE_LOCK = {read=_GetFULL_WAKE_LOCK};
	__property int ON_AFTER_RELEASE = {read=_GetON_AFTER_RELEASE};
	__property int PARTIAL_WAKE_LOCK = {read=_GetPARTIAL_WAKE_LOCK};
	__property int PROXIMITY_SCREEN_OFF_WAKE_LOCK = {read=_GetPROXIMITY_SCREEN_OFF_WAKE_LOCK};
	__property int RELEASE_FLAG_WAIT_FOR_NO_PROXIMITY = {read=_GetRELEASE_FLAG_WAIT_FOR_NO_PROXIMITY};
	__property int SCREEN_BRIGHT_WAKE_LOCK = {read=_GetSCREEN_BRIGHT_WAKE_LOCK};
	__property int SCREEN_DIM_WAKE_LOCK = {read=_GetSCREEN_DIM_WAKE_LOCK};
};

__interface  INTERFACE_UUID("{53E56DDD-6061-438E-9C19-ECDE3B32FE22}") JPowerManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl goToSleep(__int64 time) = 0 ;
	virtual bool __cdecl isDeviceIdleMode() = 0 ;
	virtual bool __cdecl isIgnoringBatteryOptimizations(Androidapi::Jni::Javatypes::_di_JString packageName) = 0 ;
	virtual bool __cdecl isInteractive() = 0 ;
	virtual bool __cdecl isPowerSaveMode() = 0 ;
	virtual bool __cdecl isScreenOn() = 0 ;
	virtual bool __cdecl isSustainedPerformanceModeSupported() = 0 ;
	virtual bool __cdecl isWakeLockLevelSupported(int level) = 0 ;
	virtual _di_JPowerManager_WakeLock __cdecl newWakeLock(int levelAndFlags, Androidapi::Jni::Javatypes::_di_JString tag) = 0 ;
	virtual void __cdecl reboot(Androidapi::Jni::Javatypes::_di_JString reason) = 0 ;
	virtual void __cdecl userActivity(__int64 when, bool noChangeLights) = 0 ;
	virtual void __cdecl wakeUp(__int64 time) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPowerManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPowerManagerClass,_di_JPowerManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPowerManagerClass,_di_JPowerManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPowerManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPowerManagerClass,_di_JPowerManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPowerManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{DA204013-460E-4CE5-B77E-772870E53853}") JPowerManager_WakeLockClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{944B58EB-1BDA-403B-AF6F-D37E07CFE914}") JPowerManager_WakeLock  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl acquire() = 0 /* overload */;
	virtual void __cdecl acquire(__int64 timeout) = 0 /* overload */;
	virtual bool __cdecl isHeld() = 0 ;
	virtual void __cdecl release() = 0 /* overload */;
	virtual void __cdecl release(int flags) = 0 /* overload */;
	virtual void __cdecl setReferenceCounted(bool value) = 0 ;
	virtual void __cdecl setWorkSource(_di_JWorkSource ws) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPowerManager_WakeLock : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPowerManager_WakeLockClass,_di_JPowerManager_WakeLock>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPowerManager_WakeLockClass,_di_JPowerManager_WakeLock> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPowerManager_WakeLock() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPowerManager_WakeLockClass,_di_JPowerManager_WakeLock>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPowerManager_WakeLock() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{51B4919C-703A-41F5-B1E4-9BA4BAA4139A}") JRemoteExceptionClass  : public Androidapi::Jni::Util::JAndroidExceptionClass 
{
	HIDESBASE virtual _di_JRemoteException __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JRemoteException __cdecl init(Androidapi::Jni::Javatypes::_di_JString message) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{D75584EB-7EF7-444D-B989-C9487675E1ED}") JRemoteException  : public Androidapi::Jni::Util::JAndroidException 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRemoteException : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRemoteExceptionClass,_di_JRemoteException>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRemoteExceptionClass,_di_JRemoteException> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRemoteException() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRemoteExceptionClass,_di_JRemoteException>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRemoteException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{590CF4A2-8625-4919-A054-77EC93C5981E}") JResultReceiverClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JResultReceiver __cdecl init(_di_JHandler handler) = 0 ;
	__property _di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{BBFBBD02-25B2-49B9-B441-CFB8DF3AA9C5}") JResultReceiver  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual void __cdecl send(int resultCode, _di_JBundle resultData) = 0 ;
	virtual void __cdecl writeToParcel(_di_JParcel out_, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJResultReceiver : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JResultReceiverClass,_di_JResultReceiver>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JResultReceiverClass,_di_JResultReceiver> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJResultReceiver() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JResultReceiverClass,_di_JResultReceiver>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJResultReceiver() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FF26D134-0260-4F44-A103-45FECCA03842}") JUserHandleClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JUserHandle __cdecl init(_di_JParcel in_) = 0 ;
	virtual _di_JUserHandle __cdecl getUserHandleForUid(int uid) = 0 ;
	virtual _di_JUserHandle __cdecl readFromParcel(_di_JParcel in_) = 0 ;
	virtual void __cdecl writeToParcel(_di_JUserHandle h, _di_JParcel out_) = 0 /* overload */;
	__property _di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{77D557B7-B984-434F-93A1-19407712B375}") JUserHandle  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(_di_JParcel out_, int flags) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJUserHandle : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JUserHandleClass,_di_JUserHandle>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JUserHandleClass,_di_JUserHandle> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJUserHandle() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JUserHandleClass,_di_JUserHandle>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJUserHandle() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9F0674B4-6A70-43B8-9BD8-B2D87E90F796}") JVibrationEffectClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetDEFAULT_AMPLITUDE() = 0 ;
	virtual _di_JVibrationEffect __cdecl createOneShot(__int64 milliseconds, int amplitude) = 0 ;
	virtual _di_JVibrationEffect __cdecl createWaveform(Androidapi::Jnibridge::TJavaArray__1<__int64>* timings, int repeat_) = 0 /* overload */;
	virtual _di_JVibrationEffect __cdecl createWaveform(Androidapi::Jnibridge::TJavaArray__1<__int64>* timings, Androidapi::Jnibridge::TJavaArray__1<int>* amplitudes, int repeat_) = 0 /* overload */;
	__property _di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int DEFAULT_AMPLITUDE = {read=_GetDEFAULT_AMPLITUDE};
};

__interface  INTERFACE_UUID("{E0D8404E-FAD6-41BF-9498-1D216E6252A6}") JVibrationEffect  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVibrationEffect : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVibrationEffectClass,_di_JVibrationEffect>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVibrationEffectClass,_di_JVibrationEffect> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVibrationEffect() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVibrationEffectClass,_di_JVibrationEffect>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVibrationEffect() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{00EEB92F-8145-441D-81C3-218E7B271F1B}") JVibratorClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{82BDC8BC-22A3-4EAD-99AF-5DA70739B086}") JVibrator  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl cancel() = 0 ;
	virtual bool __cdecl hasAmplitudeControl() = 0 ;
	virtual bool __cdecl hasVibrator() = 0 ;
	virtual void __cdecl vibrate(__int64 milliseconds) = 0 /* overload */;
	virtual void __cdecl vibrate(Androidapi::Jnibridge::TJavaArray__1<__int64>* pattern, int repeat_) = 0 /* overload */;
	virtual void __cdecl vibrate(_di_JVibrationEffect vibe) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVibrator : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVibratorClass,_di_JVibrator>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVibratorClass,_di_JVibrator> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVibrator() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVibratorClass,_di_JVibrator>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVibrator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9910D5A2-6162-4A96-B8F3-C5DC531FE31E}") JWorkSourceClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JWorkSource __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JWorkSource __cdecl init(_di_JWorkSource orig) = 0 /* overload */;
	__property _di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{04F85B42-2599-4F09-AB20-D4996613853E}") JWorkSource  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl add(_di_JWorkSource other) = 0 ;
	virtual void __cdecl clear() = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual bool __cdecl diff(_di_JWorkSource other) = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl remove(_di_JWorkSource other) = 0 ;
	virtual void __cdecl set(_di_JWorkSource other) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWorkSource : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWorkSourceClass,_di_JWorkSource>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWorkSourceClass,_di_JWorkSource> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWorkSource() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWorkSourceClass,_di_JWorkSource>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWorkSource() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3CD1E5E4-4025-43F4-9078-A0AA40F574F6}") JOnObbStateChangeListenerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetERROR_ALREADY_MOUNTED() = 0 ;
	virtual int __cdecl _GetERROR_COULD_NOT_MOUNT() = 0 ;
	virtual int __cdecl _GetERROR_COULD_NOT_UNMOUNT() = 0 ;
	virtual int __cdecl _GetERROR_INTERNAL() = 0 ;
	virtual int __cdecl _GetERROR_NOT_MOUNTED() = 0 ;
	virtual int __cdecl _GetERROR_PERMISSION_DENIED() = 0 ;
	virtual int __cdecl _GetMOUNTED() = 0 ;
	virtual int __cdecl _GetUNMOUNTED() = 0 ;
	HIDESBASE virtual _di_JOnObbStateChangeListener __cdecl init() = 0 ;
	__property int ERROR_ALREADY_MOUNTED = {read=_GetERROR_ALREADY_MOUNTED};
	__property int ERROR_COULD_NOT_MOUNT = {read=_GetERROR_COULD_NOT_MOUNT};
	__property int ERROR_COULD_NOT_UNMOUNT = {read=_GetERROR_COULD_NOT_UNMOUNT};
	__property int ERROR_INTERNAL = {read=_GetERROR_INTERNAL};
	__property int ERROR_NOT_MOUNTED = {read=_GetERROR_NOT_MOUNTED};
	__property int ERROR_PERMISSION_DENIED = {read=_GetERROR_PERMISSION_DENIED};
	__property int MOUNTED = {read=_GetMOUNTED};
	__property int UNMOUNTED = {read=_GetUNMOUNTED};
};

__interface  INTERFACE_UUID("{7B0E93C5-9C0A-445D-9CCB-6428BAE64C52}") JOnObbStateChangeListener  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onObbStateChange(Androidapi::Jni::Javatypes::_di_JString path, int state) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnObbStateChangeListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnObbStateChangeListenerClass,_di_JOnObbStateChangeListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnObbStateChangeListenerClass,_di_JOnObbStateChangeListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnObbStateChangeListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnObbStateChangeListenerClass,_di_JOnObbStateChangeListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnObbStateChangeListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Os */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_OS)
using namespace Androidapi::Jni::Os;
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
#endif	// Androidapi_Jni_OsHPP
