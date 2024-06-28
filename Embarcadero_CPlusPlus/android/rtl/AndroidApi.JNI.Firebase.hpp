// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Firebase.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_FirebaseHPP
#define Androidapi_Jni_FirebaseHPP

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
#include <Androidapi.JNI.Net.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.JNI.PlayServices.Tasks.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Firebase
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JFirebaseAppClass;
typedef System::DelphiInterface<JFirebaseAppClass> _di_JFirebaseAppClass;
__interface DELPHIINTERFACE JFirebaseApp;
typedef System::DelphiInterface<JFirebaseApp> _di_JFirebaseApp;
class DELPHICLASS TJFirebaseApp;
__interface DELPHIINTERFACE JFirebaseOptionsClass;
typedef System::DelphiInterface<JFirebaseOptionsClass> _di_JFirebaseOptionsClass;
__interface DELPHIINTERFACE JFirebaseOptions;
typedef System::DelphiInterface<JFirebaseOptions> _di_JFirebaseOptions;
class DELPHICLASS TJFirebaseOptions;
__interface DELPHIINTERFACE JFirebaseInstanceIdClass;
typedef System::DelphiInterface<JFirebaseInstanceIdClass> _di_JFirebaseInstanceIdClass;
__interface DELPHIINTERFACE JFirebaseInstanceId;
typedef System::DelphiInterface<JFirebaseInstanceId> _di_JFirebaseInstanceId;
class DELPHICLASS TJFirebaseInstanceId;
__interface DELPHIINTERFACE JInstanceIdResultClass;
typedef System::DelphiInterface<JInstanceIdResultClass> _di_JInstanceIdResultClass;
__interface DELPHIINTERFACE JInstanceIdResult;
typedef System::DelphiInterface<JInstanceIdResult> _di_JInstanceIdResult;
class DELPHICLASS TJInstanceIdResult;
__interface DELPHIINTERFACE Jiid_zzbClass;
typedef System::DelphiInterface<Jiid_zzbClass> _di_Jiid_zzbClass;
__interface DELPHIINTERFACE Jiid_zzb;
typedef System::DelphiInterface<Jiid_zzb> _di_Jiid_zzb;
class DELPHICLASS TJiid_zzb;
__interface DELPHIINTERFACE JFirebaseMessagingClass;
typedef System::DelphiInterface<JFirebaseMessagingClass> _di_JFirebaseMessagingClass;
__interface DELPHIINTERFACE JFirebaseMessaging;
typedef System::DelphiInterface<JFirebaseMessaging> _di_JFirebaseMessaging;
class DELPHICLASS TJFirebaseMessaging;
__interface DELPHIINTERFACE JFirebaseMessagingServiceClass;
typedef System::DelphiInterface<JFirebaseMessagingServiceClass> _di_JFirebaseMessagingServiceClass;
__interface DELPHIINTERFACE JFirebaseMessagingService;
typedef System::DelphiInterface<JFirebaseMessagingService> _di_JFirebaseMessagingService;
class DELPHICLASS TJFirebaseMessagingService;
__interface DELPHIINTERFACE JMessagingAnalyticsClass;
typedef System::DelphiInterface<JMessagingAnalyticsClass> _di_JMessagingAnalyticsClass;
__interface DELPHIINTERFACE JMessagingAnalytics;
typedef System::DelphiInterface<JMessagingAnalytics> _di_JMessagingAnalytics;
class DELPHICLASS TJMessagingAnalytics;
__interface DELPHIINTERFACE JRemoteMessage_MessagePriorityClass;
typedef System::DelphiInterface<JRemoteMessage_MessagePriorityClass> _di_JRemoteMessage_MessagePriorityClass;
__interface DELPHIINTERFACE JRemoteMessage_MessagePriority;
typedef System::DelphiInterface<JRemoteMessage_MessagePriority> _di_JRemoteMessage_MessagePriority;
class DELPHICLASS TJRemoteMessage_MessagePriority;
__interface DELPHIINTERFACE JRemoteMessage_NotificationClass;
typedef System::DelphiInterface<JRemoteMessage_NotificationClass> _di_JRemoteMessage_NotificationClass;
__interface DELPHIINTERFACE JRemoteMessage_Notification;
typedef System::DelphiInterface<JRemoteMessage_Notification> _di_JRemoteMessage_Notification;
class DELPHICLASS TJRemoteMessage_Notification;
__interface DELPHIINTERFACE JSendExceptionClass;
typedef System::DelphiInterface<JSendExceptionClass> _di_JSendExceptionClass;
__interface DELPHIINTERFACE JSendException;
typedef System::DelphiInterface<JSendException> _di_JSendException;
class DELPHICLASS TJSendException;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{838A377D-1D26-4E81-A4C0-8155C56B8128}") JFirebaseAppClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDEFAULT_APP_NAME() = 0 ;
	virtual void __cdecl clearInstancesForTest() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getApps(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual _di_JFirebaseApp __cdecl getInstance() = 0 /* overload */;
	virtual _di_JFirebaseApp __cdecl getInstance(Androidapi::Jni::Javatypes::_di_JString string_) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPersistenceKey(Androidapi::Jni::Javatypes::_di_JString string_, _di_JFirebaseOptions firebaseOptions) = 0 /* overload */;
	virtual _di_JFirebaseApp __cdecl initializeApp(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	virtual _di_JFirebaseApp __cdecl initializeApp(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, _di_JFirebaseOptions firebaseOptions) = 0 /* overload */;
	virtual _di_JFirebaseApp __cdecl initializeApp(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, _di_JFirebaseOptions firebaseOptions, Androidapi::Jni::Javatypes::_di_JString string_) = 0 /* overload */;
	__property Androidapi::Jni::Javatypes::_di_JString DEFAULT_APP_NAME = {read=_GetDEFAULT_APP_NAME};
};

__interface  INTERFACE_UUID("{B7D36E0E-987B-4442-BDCC-10A26FE2DA04}") JFirebaseApp  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl Delete() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl get(Androidapi::Jni::Javatypes::_di_Jlang_Class class_) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JContext __cdecl getApplicationContext() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getListeners() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
	virtual _di_JFirebaseOptions __cdecl getOptions() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPersistenceKey() = 0 /* overload */;
	virtual Androidapi::Jni::Playservices::Tasks::_di_JTask __cdecl getToken(bool b) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getUid() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isDataCollectionDefaultEnabled() = 0 ;
	virtual bool __cdecl isDefaultApp() = 0 ;
	virtual void __cdecl setAutomaticResourceManagementEnabled(bool b) = 0 ;
	virtual void __cdecl setDataCollectionDefaultEnabled(bool b) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFirebaseApp : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFirebaseAppClass,_di_JFirebaseApp>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFirebaseAppClass,_di_JFirebaseApp> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFirebaseApp() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFirebaseAppClass,_di_JFirebaseApp>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFirebaseApp() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BD98AD54-572A-4962-A9C6-16CD919D3E6E}") JFirebaseOptionsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JFirebaseOptions __cdecl fromResource(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

__interface  INTERFACE_UUID("{229D49DD-61F6-4A19-9AB8-0BB36F6BC4FF}") JFirebaseOptions  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getApiKey() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getApplicationId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDatabaseUrl() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getGaTrackingId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getGcmSenderId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getProjectId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getStorageBucket() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFirebaseOptions : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFirebaseOptionsClass,_di_JFirebaseOptions>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFirebaseOptionsClass,_di_JFirebaseOptions> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFirebaseOptions() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFirebaseOptionsClass,_di_JFirebaseOptions>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFirebaseOptions() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{30573311-D4D7-4C46-95DD-9AAC1EB376DD}") JFirebaseInstanceIdClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JFirebaseInstanceId __cdecl getInstance() = 0 /* overload */;
	virtual _di_JFirebaseInstanceId __cdecl getInstance(_di_JFirebaseApp firebaseApp) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{70302455-620F-4538-ABCB-F7D28FCA016C}") JFirebaseInstanceId  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl deleteInstanceId() = 0 ;
	virtual void __cdecl deleteToken(Androidapi::Jni::Javatypes::_di_JString string_, Androidapi::Jni::Javatypes::_di_JString string_1) = 0 ;
	virtual __int64 __cdecl getCreationTime() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getId() = 0 ;
	virtual Androidapi::Jni::Playservices::Tasks::_di_JTask __cdecl getInstanceId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getToken() = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getToken(Androidapi::Jni::Javatypes::_di_JString string_, Androidapi::Jni::Javatypes::_di_JString string_1) = 0 /* overload */;
	virtual Androidapi::Jni::Playservices::Tasks::_di_JTask __cdecl zza(Androidapi::Jni::Javatypes::_di_JString string_) = 0 /* overload */;
	virtual void __cdecl zzb(bool b) = 0 /* overload */;
	virtual bool __cdecl zzq() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFirebaseInstanceId : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFirebaseInstanceIdClass,_di_JFirebaseInstanceId>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFirebaseInstanceIdClass,_di_JFirebaseInstanceId> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFirebaseInstanceId() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFirebaseInstanceIdClass,_di_JFirebaseInstanceId>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFirebaseInstanceId() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{83BCAD12-7B4D-41E1-8169-617A5DEEEEF6}") JInstanceIdResultClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{8E4F3729-07B2-4857-B1F2-FC971E8340C7}") JInstanceIdResult  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getToken() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInstanceIdResult : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInstanceIdResultClass,_di_JInstanceIdResult>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInstanceIdResultClass,_di_JInstanceIdResult> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInstanceIdResult() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInstanceIdResultClass,_di_JInstanceIdResult>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInstanceIdResult() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7CF8197E-FA33-46B0-AA92-D9AF7B3EB719}") Jiid_zzbClass  : public Androidapi::Jni::App::JServiceClass 
{
	HIDESBASE virtual _di_Jiid_zzb __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{8AECFA88-AB9B-4943-81C5-86580FB3D7B6}") Jiid_zzb  : public Androidapi::Jni::App::JService 
{
	HIDESBASE virtual Androidapi::Jni::Os::_di_JIBinder __cdecl onBind(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	HIDESBASE virtual int __cdecl onStartCommand(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int i, int i1) = 0 ;
	virtual bool __cdecl zzc(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual void __cdecl zzd(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJiid_zzb : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jiid_zzbClass,_di_Jiid_zzb>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jiid_zzbClass,_di_Jiid_zzb> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJiid_zzb() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jiid_zzbClass,_di_Jiid_zzb>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJiid_zzb() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5E14657A-AF87-404A-8BF2-9B14D1730E90}") JFirebaseMessagingClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetINSTANCE_ID_SCOPE() = 0 ;
	virtual _di_JFirebaseMessaging __cdecl getInstance() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString INSTANCE_ID_SCOPE = {read=_GetINSTANCE_ID_SCOPE};
};

__interface  INTERFACE_UUID("{EE5EEAAC-6BB6-4401-A1A0-69E348580BD0}") JFirebaseMessaging  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl isAutoInitEnabled() = 0 ;
	virtual void __cdecl setAutoInitEnabled(bool b) = 0 ;
	virtual Androidapi::Jni::Playservices::Tasks::_di_JTask __cdecl subscribeToTopic(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
	virtual Androidapi::Jni::Playservices::Tasks::_di_JTask __cdecl unsubscribeFromTopic(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFirebaseMessaging : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFirebaseMessagingClass,_di_JFirebaseMessaging>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFirebaseMessagingClass,_di_JFirebaseMessaging> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFirebaseMessaging() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFirebaseMessagingClass,_di_JFirebaseMessaging>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFirebaseMessaging() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{77E28384-4E74-44BB-9864-C8548B690E2F}") JFirebaseMessagingServiceClass  : public Jiid_zzbClass 
{
	HIDESBASE virtual _di_JFirebaseMessagingService __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{250F778A-64D2-471C-8535-AF42C3D86975}") JFirebaseMessagingService  : public Jiid_zzb 
{
	virtual void __cdecl onDeletedMessages() = 0 ;
	virtual void __cdecl onMessageSent(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
	virtual void __cdecl onNewToken(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
	virtual void __cdecl onSendError(Androidapi::Jni::Javatypes::_di_JString string_, Androidapi::Jni::Javatypes::_di_JException exception) = 0 ;
	HIDESBASE virtual bool __cdecl zzc(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	HIDESBASE virtual void __cdecl zzd(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFirebaseMessagingService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFirebaseMessagingServiceClass,_di_JFirebaseMessagingService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFirebaseMessagingServiceClass,_di_JFirebaseMessagingService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFirebaseMessagingService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFirebaseMessagingServiceClass,_di_JFirebaseMessagingService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFirebaseMessagingService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{501E969F-132A-4840-972A-1B3F654ACEA0}") JMessagingAnalyticsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JMessagingAnalytics __cdecl init() = 0 ;
	virtual void __cdecl logNotificationDismiss(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual void __cdecl logNotificationForeground(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual void __cdecl logNotificationOpen(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual void __cdecl logNotificationReceived(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual bool __cdecl shouldUploadMetrics(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
};

__interface  INTERFACE_UUID("{801D6996-4E2E-4B99-9E3E-57E9C8C178ED}") JMessagingAnalytics  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMessagingAnalytics : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessagingAnalyticsClass,_di_JMessagingAnalytics>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessagingAnalyticsClass,_di_JMessagingAnalytics> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMessagingAnalytics() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMessagingAnalyticsClass,_di_JMessagingAnalytics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMessagingAnalytics() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{65CB1A5D-24E4-4EC8-9D38-AAFA705868B7}") JRemoteMessage_MessagePriorityClass  : public Androidapi::Jni::Javatypes::JAnnotationClass 
{
	
};

__interface  INTERFACE_UUID("{3E6EACB4-BC9F-4A69-89EF-AD5D818B3F98}") JRemoteMessage_MessagePriority  : public Androidapi::Jni::Javatypes::JAnnotation 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRemoteMessage_MessagePriority : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRemoteMessage_MessagePriorityClass,_di_JRemoteMessage_MessagePriority>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRemoteMessage_MessagePriorityClass,_di_JRemoteMessage_MessagePriority> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRemoteMessage_MessagePriority() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRemoteMessage_MessagePriorityClass,_di_JRemoteMessage_MessagePriority>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRemoteMessage_MessagePriority() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{517BD0C8-8E40-492A-87DA-FE02C48669C4}") JRemoteMessage_NotificationClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{11FA4879-22C9-4075-BCE7-9205083E60EC}") JRemoteMessage_Notification  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getBody() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getBodyLocalizationArgs() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getBodyLocalizationKey() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getChannelId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getClickAction() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getColor() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getIcon() = 0 ;
	virtual Androidapi::Jni::Net::_di_Jnet_Uri __cdecl getLink() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSound() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getTag() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getTitle() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getTitleLocalizationArgs() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getTitleLocalizationKey() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRemoteMessage_Notification : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRemoteMessage_NotificationClass,_di_JRemoteMessage_Notification>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRemoteMessage_NotificationClass,_di_JRemoteMessage_Notification> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRemoteMessage_Notification() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRemoteMessage_NotificationClass,_di_JRemoteMessage_Notification>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRemoteMessage_Notification() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{79A8A573-166C-4062-843C-3B1057AFBABD}") JSendExceptionClass  : public Androidapi::Jni::Javatypes::JExceptionClass 
{
	virtual int __cdecl _GetERROR_INVALID_PARAMETERS() = 0 ;
	virtual int __cdecl _GetERROR_SIZE() = 0 ;
	virtual int __cdecl _GetERROR_TOO_MANY_MESSAGES() = 0 ;
	virtual int __cdecl _GetERROR_TTL_EXCEEDED() = 0 ;
	virtual int __cdecl _GetERROR_UNKNOWN() = 0 ;
	__property int ERROR_INVALID_PARAMETERS = {read=_GetERROR_INVALID_PARAMETERS};
	__property int ERROR_SIZE = {read=_GetERROR_SIZE};
	__property int ERROR_TOO_MANY_MESSAGES = {read=_GetERROR_TOO_MANY_MESSAGES};
	__property int ERROR_TTL_EXCEEDED = {read=_GetERROR_TTL_EXCEEDED};
	__property int ERROR_UNKNOWN = {read=_GetERROR_UNKNOWN};
};

__interface  INTERFACE_UUID("{604C02FB-7650-4439-9E97-D4C58EE870F5}") JSendException  : public Androidapi::Jni::Javatypes::JException 
{
	virtual int __cdecl getErrorCode() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSendException : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSendExceptionClass,_di_JSendException>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSendExceptionClass,_di_JSendException> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSendException() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSendExceptionClass,_di_JSendException>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSendException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Firebase */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_FIREBASE)
using namespace Androidapi::Jni::Firebase;
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
#endif	// Androidapi_Jni_FirebaseHPP
