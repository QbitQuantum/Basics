// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Analytics.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_AnalyticsHPP
#define Androidapi_Jni_AnalyticsHPP

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

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Analytics
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JAnalyticsThread_ClientIdCallbackClass;
typedef System::DelphiInterface<JAnalyticsThread_ClientIdCallbackClass> _di_JAnalyticsThread_ClientIdCallbackClass;
__interface DELPHIINTERFACE JAnalyticsThread_ClientIdCallback;
typedef System::DelphiInterface<JAnalyticsThread_ClientIdCallback> _di_JAnalyticsThread_ClientIdCallback;
class DELPHICLASS TJAnalyticsThread_ClientIdCallback;
__interface DELPHIINTERFACE JCampaignTrackingReceiverClass;
typedef System::DelphiInterface<JCampaignTrackingReceiverClass> _di_JCampaignTrackingReceiverClass;
__interface DELPHIINTERFACE JCampaignTrackingReceiver;
typedef System::DelphiInterface<JCampaignTrackingReceiver> _di_JCampaignTrackingReceiver;
class DELPHICLASS TJCampaignTrackingReceiver;
__interface DELPHIINTERFACE JCampaignTrackingServiceClass;
typedef System::DelphiInterface<JCampaignTrackingServiceClass> _di_JCampaignTrackingServiceClass;
__interface DELPHIINTERFACE JCampaignTrackingService;
typedef System::DelphiInterface<JCampaignTrackingService> _di_JCampaignTrackingService;
class DELPHICLASS TJCampaignTrackingService;
__interface DELPHIINTERFACE JEasyTrackerClass;
typedef System::DelphiInterface<JEasyTrackerClass> _di_JEasyTrackerClass;
__interface DELPHIINTERFACE JEasyTracker;
typedef System::DelphiInterface<JEasyTracker> _di_JEasyTracker;
class DELPHICLASS TJEasyTracker;
__interface DELPHIINTERFACE JExceptionParserClass;
typedef System::DelphiInterface<JExceptionParserClass> _di_JExceptionParserClass;
__interface DELPHIINTERFACE JExceptionParser;
typedef System::DelphiInterface<JExceptionParser> _di_JExceptionParser;
class DELPHICLASS TJExceptionParser;
__interface DELPHIINTERFACE JExceptionReporterClass;
typedef System::DelphiInterface<JExceptionReporterClass> _di_JExceptionReporterClass;
__interface DELPHIINTERFACE JExceptionReporter;
typedef System::DelphiInterface<JExceptionReporter> _di_JExceptionReporter;
class DELPHICLASS TJExceptionReporter;
__interface DELPHIINTERFACE JGAServiceManagerClass;
typedef System::DelphiInterface<JGAServiceManagerClass> _di_JGAServiceManagerClass;
__interface DELPHIINTERFACE JGAServiceManager;
typedef System::DelphiInterface<JGAServiceManager> _di_JGAServiceManager;
class DELPHICLASS TJGAServiceManager;
__interface DELPHIINTERFACE JGoogleAnalyticsClass;
typedef System::DelphiInterface<JGoogleAnalyticsClass> _di_JGoogleAnalyticsClass;
__interface DELPHIINTERFACE JGoogleAnalytics;
typedef System::DelphiInterface<JGoogleAnalytics> _di_JGoogleAnalytics;
class DELPHICLASS TJGoogleAnalytics;
__interface DELPHIINTERFACE JGoogleAnalytics_AppOptOutCallbackClass;
typedef System::DelphiInterface<JGoogleAnalytics_AppOptOutCallbackClass> _di_JGoogleAnalytics_AppOptOutCallbackClass;
__interface DELPHIINTERFACE JGoogleAnalytics_AppOptOutCallback;
typedef System::DelphiInterface<JGoogleAnalytics_AppOptOutCallback> _di_JGoogleAnalytics_AppOptOutCallback;
class DELPHICLASS TJGoogleAnalytics_AppOptOutCallback;
__interface DELPHIINTERFACE Jandroid_LogClass;
typedef System::DelphiInterface<Jandroid_LogClass> _di_Jandroid_LogClass;
__interface DELPHIINTERFACE Jandroid_Log;
typedef System::DelphiInterface<Jandroid_Log> _di_Jandroid_Log;
class DELPHICLASS TJandroid_Log;
__interface DELPHIINTERFACE JModelFieldsClass;
typedef System::DelphiInterface<JModelFieldsClass> _di_JModelFieldsClass;
__interface DELPHIINTERFACE JModelFields;
typedef System::DelphiInterface<JModelFields> _di_JModelFields;
class DELPHICLASS TJModelFields;
__interface DELPHIINTERFACE JServiceManagerClass;
typedef System::DelphiInterface<JServiceManagerClass> _di_JServiceManagerClass;
__interface DELPHIINTERFACE JServiceManager;
typedef System::DelphiInterface<JServiceManager> _di_JServiceManager;
class DELPHICLASS TJServiceManager;
__interface DELPHIINTERFACE JStandardExceptionParserClass;
typedef System::DelphiInterface<JStandardExceptionParserClass> _di_JStandardExceptionParserClass;
__interface DELPHIINTERFACE JStandardExceptionParser;
typedef System::DelphiInterface<JStandardExceptionParser> _di_JStandardExceptionParser;
class DELPHICLASS TJStandardExceptionParser;
__interface DELPHIINTERFACE JTrackerClass;
typedef System::DelphiInterface<JTrackerClass> _di_JTrackerClass;
__interface DELPHIINTERFACE JTracker;
typedef System::DelphiInterface<JTracker> _di_JTracker;
class DELPHICLASS TJTracker;
__interface DELPHIINTERFACE JTransactionClass;
typedef System::DelphiInterface<JTransactionClass> _di_JTransactionClass;
__interface DELPHIINTERFACE JTransaction;
typedef System::DelphiInterface<JTransaction> _di_JTransaction;
class DELPHICLASS TJTransaction;
__interface DELPHIINTERFACE JTransaction_BuilderClass;
typedef System::DelphiInterface<JTransaction_BuilderClass> _di_JTransaction_BuilderClass;
__interface DELPHIINTERFACE JTransaction_Builder;
typedef System::DelphiInterface<JTransaction_Builder> _di_JTransaction_Builder;
class DELPHICLASS TJTransaction_Builder;
__interface DELPHIINTERFACE JTransaction_ItemClass;
typedef System::DelphiInterface<JTransaction_ItemClass> _di_JTransaction_ItemClass;
__interface DELPHIINTERFACE JTransaction_Item;
typedef System::DelphiInterface<JTransaction_Item> _di_JTransaction_Item;
class DELPHICLASS TJTransaction_Item;
__interface DELPHIINTERFACE JItem_BuilderClass;
typedef System::DelphiInterface<JItem_BuilderClass> _di_JItem_BuilderClass;
__interface DELPHIINTERFACE JItem_Builder;
typedef System::DelphiInterface<JItem_Builder> _di_JItem_Builder;
class DELPHICLASS TJItem_Builder;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{F5905273-CD1E-4B68-90FE-CD12E7E85A50}") JAnalyticsThread_ClientIdCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{56B9191B-76F9-42B3-AD76-9759A4B77883}") JAnalyticsThread_ClientIdCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl reportClientId(Androidapi::Jni::Javatypes::_di_JString paramString) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAnalyticsThread_ClientIdCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAnalyticsThread_ClientIdCallbackClass,_di_JAnalyticsThread_ClientIdCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAnalyticsThread_ClientIdCallbackClass,_di_JAnalyticsThread_ClientIdCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAnalyticsThread_ClientIdCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAnalyticsThread_ClientIdCallbackClass,_di_JAnalyticsThread_ClientIdCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAnalyticsThread_ClientIdCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9BBDCFAD-93AC-40E9-9D5C-D4A6848033D2}") JCampaignTrackingReceiverClass  : public Androidapi::Jni::Graphicscontentviewtext::JBroadcastReceiverClass 
{
	HIDESBASE virtual _di_JCampaignTrackingReceiver __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{5ABB75C6-3E3B-4B83-AA3C-ACBD240EA4E6}") JCampaignTrackingReceiver  : public Androidapi::Jni::Graphicscontentviewtext::JBroadcastReceiver 
{
	HIDESBASE virtual void __cdecl onReceive(Androidapi::Jni::Graphicscontentviewtext::_di_JContext ctx, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCampaignTrackingReceiver : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCampaignTrackingReceiverClass,_di_JCampaignTrackingReceiver>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCampaignTrackingReceiverClass,_di_JCampaignTrackingReceiver> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCampaignTrackingReceiver() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCampaignTrackingReceiverClass,_di_JCampaignTrackingReceiver>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCampaignTrackingReceiver() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{72BFE8D6-3F6D-402B-9D5D-EE14ADB67970}") JCampaignTrackingServiceClass  : public Androidapi::Jni::App::JIntentServiceClass 
{
	HIDESBASE virtual _di_JCampaignTrackingService __cdecl init(Androidapi::Jni::Javatypes::_di_JString name) = 0 /* overload */;
	HIDESBASE virtual _di_JCampaignTrackingService __cdecl init() = 0 /* overload */;
};

__interface  INTERFACE_UUID("{0AF1D352-0263-48DB-AE7B-F9D08FD54140}") JCampaignTrackingService  : public Androidapi::Jni::App::JIntentService 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCampaignTrackingService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCampaignTrackingServiceClass,_di_JCampaignTrackingService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCampaignTrackingServiceClass,_di_JCampaignTrackingService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCampaignTrackingService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCampaignTrackingServiceClass,_di_JCampaignTrackingService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCampaignTrackingService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8499D0D6-D2B3-431C-954C-7250D3ABABDD}") JEasyTrackerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JEasyTracker __cdecl getInstance() = 0 ;
	virtual _di_JTracker __cdecl getTracker() = 0 ;
};

__interface  INTERFACE_UUID("{BD4D421D-03C7-45BA-B4AA-7DBA624F5642}") JEasyTracker  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl activityStart(Androidapi::Jni::App::_di_JActivity activity) = 0 ;
	virtual void __cdecl activityStop(Androidapi::Jni::App::_di_JActivity activity) = 0 ;
	virtual void __cdecl dispatch() = 0 ;
	virtual void __cdecl setContext(Androidapi::Jni::Graphicscontentviewtext::_di_JContext ctx) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJEasyTracker : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JEasyTrackerClass,_di_JEasyTracker>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JEasyTrackerClass,_di_JEasyTracker> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJEasyTracker() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JEasyTrackerClass,_di_JEasyTracker>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJEasyTracker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{27FAA6C4-A988-4B87-B703-03A90F6BEE78}") JExceptionParserClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{427A0D60-A7AD-49A6-ADEA-8F49CE492A1D}") JExceptionParser  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDescription(Androidapi::Jni::Javatypes::_di_JString paramString, Androidapi::Jni::Javatypes::_di_JThrowable paramThrowable) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJExceptionParser : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JExceptionParserClass,_di_JExceptionParser>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JExceptionParserClass,_di_JExceptionParser> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJExceptionParser() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JExceptionParserClass,_di_JExceptionParser>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJExceptionParser() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AF7794E6-3812-4DD2-8ED6-77B29824DA3B}") JExceptionReporterClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JExceptionReporter __cdecl init(_di_JTracker tracker, _di_JServiceManager serviceManager, Androidapi::Jni::Javatypes::_di_JThread_UncaughtExceptionHandler originalHandler, Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

__interface  INTERFACE_UUID("{25437F3C-CB55-4607-9126-568AA64C8E6B}") JExceptionReporter  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JExceptionParser __cdecl getExceptionParser() = 0 ;
	virtual void __cdecl setExceptionParser(_di_JExceptionParser exceptionParser) = 0 ;
	virtual void __cdecl uncaughtException(Androidapi::Jni::Javatypes::_di_JThread t, Androidapi::Jni::Javatypes::_di_JThrowable e) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJExceptionReporter : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JExceptionReporterClass,_di_JExceptionReporter>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JExceptionReporterClass,_di_JExceptionReporter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJExceptionReporter() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JExceptionReporterClass,_di_JExceptionReporter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJExceptionReporter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{CB723915-880E-40E1-AD91-2EB757F17443}") JGAServiceManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JGAServiceManager __cdecl getInstance() = 0 ;
};

__interface  INTERFACE_UUID("{27A7DD22-6714-41C9-B78A-7DF99AE31B7F}") JGAServiceManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl dispatch() = 0 ;
	virtual void __cdecl setDispatchPeriod(int dispatchPeriodInSeconds) = 0 ;
	virtual void __cdecl updateConnectivityStatus(bool connected) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGAServiceManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGAServiceManagerClass,_di_JGAServiceManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGAServiceManagerClass,_di_JGAServiceManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGAServiceManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGAServiceManagerClass,_di_JGAServiceManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGAServiceManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{69864765-05B2-4142-8709-A377F7A47F98}") JGoogleAnalyticsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JGoogleAnalytics __cdecl getInstance(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

__interface  INTERFACE_UUID("{2D7EB39C-3279-41C5-B6BA-0B42DF6C613D}") JGoogleAnalytics  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl closeTracker(_di_JTracker tracker) = 0 ;
	virtual _di_JTracker __cdecl getDefaultTracker() = 0 ;
	virtual _di_JTracker __cdecl getTracker(Androidapi::Jni::Javatypes::_di_JString trackingId) = 0 ;
	virtual bool __cdecl isDebugEnabled() = 0 ;
	virtual void __cdecl requestAppOptOut(_di_JGoogleAnalytics_AppOptOutCallback callback) = 0 ;
	virtual void __cdecl sendHit(Androidapi::Jni::Javatypes::_di_JMap hit) = 0 ;
	virtual void __cdecl setAppOptOut(bool optOut) = 0 ;
	virtual void __cdecl setDebug(bool debug) = 0 ;
	virtual void __cdecl setDefaultTracker(_di_JTracker tracker) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleAnalytics : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleAnalyticsClass,_di_JGoogleAnalytics>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleAnalyticsClass,_di_JGoogleAnalytics> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleAnalytics() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleAnalyticsClass,_di_JGoogleAnalytics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleAnalytics() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0D3DAF93-8A52-4EED-8F9A-9F986495BA4D}") JGoogleAnalytics_AppOptOutCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{DB8992E3-FEFA-4BB1-98B9-F44BB465F278}") JGoogleAnalytics_AppOptOutCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl reportAppOptOut(bool paramBoolean) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGoogleAnalytics_AppOptOutCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleAnalytics_AppOptOutCallbackClass,_di_JGoogleAnalytics_AppOptOutCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleAnalytics_AppOptOutCallbackClass,_di_JGoogleAnalytics_AppOptOutCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGoogleAnalytics_AppOptOutCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGoogleAnalytics_AppOptOutCallbackClass,_di_JGoogleAnalytics_AppOptOutCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGoogleAnalytics_AppOptOutCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3042F41F-E9CB-4B25-8731-D36CC6C53B36}") Jandroid_LogClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_Jandroid_Log __cdecl init() = 0 ;
	virtual int __cdecl d(Androidapi::Jni::Javatypes::_di_JString msg) = 0 ;
	virtual int __cdecl dDebug(Androidapi::Jni::Javatypes::_di_JString msg) = 0 ;
	virtual int __cdecl e(Androidapi::Jni::Javatypes::_di_JString msg) = 0 ;
	virtual int __cdecl eDebug(Androidapi::Jni::Javatypes::_di_JString msg) = 0 ;
	virtual int __cdecl i(Androidapi::Jni::Javatypes::_di_JString msg) = 0 ;
	virtual int __cdecl iDebug(Androidapi::Jni::Javatypes::_di_JString msg) = 0 ;
	virtual bool __cdecl isDebugEnabled() = 0 ;
	virtual void __cdecl setDebug(bool debug) = 0 ;
	virtual int __cdecl v(Androidapi::Jni::Javatypes::_di_JString msg) = 0 ;
	virtual int __cdecl vDebug(Androidapi::Jni::Javatypes::_di_JString msg) = 0 ;
	virtual int __cdecl w(Androidapi::Jni::Javatypes::_di_JString msg) = 0 ;
	virtual int __cdecl wDebug(Androidapi::Jni::Javatypes::_di_JString msg) = 0 ;
};

__interface  INTERFACE_UUID("{E246D977-8DBD-4CDB-BD16-8D4AB1F84DCE}") Jandroid_Log  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJandroid_Log : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jandroid_LogClass,_di_Jandroid_Log>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jandroid_LogClass,_di_Jandroid_Log> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJandroid_Log() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jandroid_LogClass,_di_Jandroid_Log>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJandroid_Log() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{87CD99C9-E1DB-4D40-BBBB-67ED070AAE4D}") JModelFieldsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetANDROID_APP_UID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetANONYMIZE_IP() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetAPI_VERSION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetAPP_ID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetAPP_INSTALLER_ID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetAPP_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetAPP_SCREEN() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetAPP_VERSION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetAPP_VIEW() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCACHE_BUSTER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCAMPAIGN() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCAMPAIGN_CONTENT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCAMPAIGN_ID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCAMPAIGN_KEYWORD() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCAMPAIGN_MEDIUM() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCAMPAIGN_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCAMPAIGN_SOURCE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCLIENT_ID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCONTENT_GROUPING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCUSTOM_DIMENSION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCUSTOM_METRIC() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDCLID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDESCRIPTION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetENCODING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEVENT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEVENT_ACTION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEVENT_CATEGORY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEVENT_LABEL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEVENT_VALUE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXCEPTION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXCEPTION_THREAD_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEX_DESCRIPTION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEX_FATAL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFLASH_VERSION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetGCLID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetGMOB_T() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetHIT_TYPE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetITEM() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetITEM_CATEGORY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetITEM_CODE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetITEM_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetITEM_PRICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetITEM_QUANTITY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetJAVA_ENABLED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetLANGUAGE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetNON_INTERACTION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetPAGE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetQUEUE_TIME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRAW_EXCEPTION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREFERRER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSAMPLE_RATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCREEN_COLORS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCREEN_RESOLUTION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSESSION_CONTROL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSOCIAL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSOCIAL_ACTION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSOCIAL_NETWORK() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSOCIAL_TARGET() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTIMING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTIMING_CATEGORY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTIMING_LABEL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTIMING_VALUE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTIMING_VAR() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTITLE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTRACKING_ID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTRANSACTION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTRANSACTION_AFFILIATION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTRANSACTION_ID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTRANSACTION_SHIPPING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTRANSACTION_TAX() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTRANSACTION_TOTAL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetUSE_SECURE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetVIEWPORT_SIZE() = 0 ;
	HIDESBASE virtual _di_JModelFields __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ANDROID_APP_UID = {read=_GetANDROID_APP_UID};
	__property Androidapi::Jni::Javatypes::_di_JString ANONYMIZE_IP = {read=_GetANONYMIZE_IP};
	__property Androidapi::Jni::Javatypes::_di_JString API_VERSION = {read=_GetAPI_VERSION};
	__property Androidapi::Jni::Javatypes::_di_JString APP_ID = {read=_GetAPP_ID};
	__property Androidapi::Jni::Javatypes::_di_JString APP_INSTALLER_ID = {read=_GetAPP_INSTALLER_ID};
	__property Androidapi::Jni::Javatypes::_di_JString APP_NAME = {read=_GetAPP_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString APP_SCREEN = {read=_GetAPP_SCREEN};
	__property Androidapi::Jni::Javatypes::_di_JString APP_VERSION = {read=_GetAPP_VERSION};
	__property Androidapi::Jni::Javatypes::_di_JString APP_VIEW = {read=_GetAPP_VIEW};
	__property Androidapi::Jni::Javatypes::_di_JString CACHE_BUSTER = {read=_GetCACHE_BUSTER};
	__property Androidapi::Jni::Javatypes::_di_JString CAMPAIGN = {read=_GetCAMPAIGN};
	__property Androidapi::Jni::Javatypes::_di_JString CAMPAIGN_CONTENT = {read=_GetCAMPAIGN_CONTENT};
	__property Androidapi::Jni::Javatypes::_di_JString CAMPAIGN_ID = {read=_GetCAMPAIGN_ID};
	__property Androidapi::Jni::Javatypes::_di_JString CAMPAIGN_KEYWORD = {read=_GetCAMPAIGN_KEYWORD};
	__property Androidapi::Jni::Javatypes::_di_JString CAMPAIGN_MEDIUM = {read=_GetCAMPAIGN_MEDIUM};
	__property Androidapi::Jni::Javatypes::_di_JString CAMPAIGN_NAME = {read=_GetCAMPAIGN_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString CAMPAIGN_SOURCE = {read=_GetCAMPAIGN_SOURCE};
	__property Androidapi::Jni::Javatypes::_di_JString CLIENT_ID = {read=_GetCLIENT_ID};
	__property Androidapi::Jni::Javatypes::_di_JString CONTENT_GROUPING = {read=_GetCONTENT_GROUPING};
	__property Androidapi::Jni::Javatypes::_di_JString CUSTOM_DIMENSION = {read=_GetCUSTOM_DIMENSION};
	__property Androidapi::Jni::Javatypes::_di_JString CUSTOM_METRIC = {read=_GetCUSTOM_METRIC};
	__property Androidapi::Jni::Javatypes::_di_JString DCLID = {read=_GetDCLID};
	__property Androidapi::Jni::Javatypes::_di_JString DESCRIPTION = {read=_GetDESCRIPTION};
	__property Androidapi::Jni::Javatypes::_di_JString ENCODING = {read=_GetENCODING};
	__property Androidapi::Jni::Javatypes::_di_JString EVENT = {read=_GetEVENT};
	__property Androidapi::Jni::Javatypes::_di_JString EVENT_ACTION = {read=_GetEVENT_ACTION};
	__property Androidapi::Jni::Javatypes::_di_JString EVENT_CATEGORY = {read=_GetEVENT_CATEGORY};
	__property Androidapi::Jni::Javatypes::_di_JString EVENT_LABEL = {read=_GetEVENT_LABEL};
	__property Androidapi::Jni::Javatypes::_di_JString EVENT_VALUE = {read=_GetEVENT_VALUE};
	__property Androidapi::Jni::Javatypes::_di_JString EXCEPTION = {read=_GetEXCEPTION};
	__property Androidapi::Jni::Javatypes::_di_JString EXCEPTION_THREAD_NAME = {read=_GetEXCEPTION_THREAD_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString EX_DESCRIPTION = {read=_GetEX_DESCRIPTION};
	__property Androidapi::Jni::Javatypes::_di_JString EX_FATAL = {read=_GetEX_FATAL};
	__property Androidapi::Jni::Javatypes::_di_JString FLASH_VERSION = {read=_GetFLASH_VERSION};
	__property Androidapi::Jni::Javatypes::_di_JString GCLID = {read=_GetGCLID};
	__property Androidapi::Jni::Javatypes::_di_JString GMOB_T = {read=_GetGMOB_T};
	__property Androidapi::Jni::Javatypes::_di_JString HIT_TYPE = {read=_GetHIT_TYPE};
	__property Androidapi::Jni::Javatypes::_di_JString ITEM = {read=_GetITEM};
	__property Androidapi::Jni::Javatypes::_di_JString ITEM_CATEGORY = {read=_GetITEM_CATEGORY};
	__property Androidapi::Jni::Javatypes::_di_JString ITEM_CODE = {read=_GetITEM_CODE};
	__property Androidapi::Jni::Javatypes::_di_JString ITEM_NAME = {read=_GetITEM_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString ITEM_PRICE = {read=_GetITEM_PRICE};
	__property Androidapi::Jni::Javatypes::_di_JString ITEM_QUANTITY = {read=_GetITEM_QUANTITY};
	__property Androidapi::Jni::Javatypes::_di_JString JAVA_ENABLED = {read=_GetJAVA_ENABLED};
	__property Androidapi::Jni::Javatypes::_di_JString LANGUAGE = {read=_GetLANGUAGE};
	__property Androidapi::Jni::Javatypes::_di_JString NON_INTERACTION = {read=_GetNON_INTERACTION};
	__property Androidapi::Jni::Javatypes::_di_JString PAGE = {read=_GetPAGE};
	__property Androidapi::Jni::Javatypes::_di_JString QUEUE_TIME = {read=_GetQUEUE_TIME};
	__property Androidapi::Jni::Javatypes::_di_JString RAW_EXCEPTION = {read=_GetRAW_EXCEPTION};
	__property Androidapi::Jni::Javatypes::_di_JString REFERRER = {read=_GetREFERRER};
	__property Androidapi::Jni::Javatypes::_di_JString SAMPLE_RATE = {read=_GetSAMPLE_RATE};
	__property Androidapi::Jni::Javatypes::_di_JString SCREEN_COLORS = {read=_GetSCREEN_COLORS};
	__property Androidapi::Jni::Javatypes::_di_JString SCREEN_RESOLUTION = {read=_GetSCREEN_RESOLUTION};
	__property Androidapi::Jni::Javatypes::_di_JString SESSION_CONTROL = {read=_GetSESSION_CONTROL};
	__property Androidapi::Jni::Javatypes::_di_JString SOCIAL = {read=_GetSOCIAL};
	__property Androidapi::Jni::Javatypes::_di_JString SOCIAL_ACTION = {read=_GetSOCIAL_ACTION};
	__property Androidapi::Jni::Javatypes::_di_JString SOCIAL_NETWORK = {read=_GetSOCIAL_NETWORK};
	__property Androidapi::Jni::Javatypes::_di_JString SOCIAL_TARGET = {read=_GetSOCIAL_TARGET};
	__property Androidapi::Jni::Javatypes::_di_JString TIMING = {read=_GetTIMING};
	__property Androidapi::Jni::Javatypes::_di_JString TIMING_CATEGORY = {read=_GetTIMING_CATEGORY};
	__property Androidapi::Jni::Javatypes::_di_JString TIMING_LABEL = {read=_GetTIMING_LABEL};
	__property Androidapi::Jni::Javatypes::_di_JString TIMING_VALUE = {read=_GetTIMING_VALUE};
	__property Androidapi::Jni::Javatypes::_di_JString TIMING_VAR = {read=_GetTIMING_VAR};
	__property Androidapi::Jni::Javatypes::_di_JString TITLE = {read=_GetTITLE};
	__property Androidapi::Jni::Javatypes::_di_JString TRACKING_ID = {read=_GetTRACKING_ID};
	__property Androidapi::Jni::Javatypes::_di_JString TRANSACTION = {read=_GetTRANSACTION};
	__property Androidapi::Jni::Javatypes::_di_JString TRANSACTION_AFFILIATION = {read=_GetTRANSACTION_AFFILIATION};
	__property Androidapi::Jni::Javatypes::_di_JString TRANSACTION_ID = {read=_GetTRANSACTION_ID};
	__property Androidapi::Jni::Javatypes::_di_JString TRANSACTION_SHIPPING = {read=_GetTRANSACTION_SHIPPING};
	__property Androidapi::Jni::Javatypes::_di_JString TRANSACTION_TAX = {read=_GetTRANSACTION_TAX};
	__property Androidapi::Jni::Javatypes::_di_JString TRANSACTION_TOTAL = {read=_GetTRANSACTION_TOTAL};
	__property Androidapi::Jni::Javatypes::_di_JString USE_SECURE = {read=_GetUSE_SECURE};
	__property Androidapi::Jni::Javatypes::_di_JString VIEWPORT_SIZE = {read=_GetVIEWPORT_SIZE};
};

__interface  INTERFACE_UUID("{B50F6065-F244-4D64-9CCB-4095FF443D0D}") JModelFields  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJModelFields : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JModelFieldsClass,_di_JModelFields>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JModelFieldsClass,_di_JModelFields> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJModelFields() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JModelFieldsClass,_di_JModelFields>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJModelFields() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B7235021-91AE-4B45-B235-65E57379A58F}") JServiceManagerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{38258C12-E458-47CE-A63E-12782C752B1C}") JServiceManager  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl dispatch() = 0 ;
	virtual void __cdecl setDispatchPeriod(int paramInt) = 0 ;
	virtual void __cdecl updateConnectivityStatus(bool paramBoolean) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJServiceManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceManagerClass,_di_JServiceManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceManagerClass,_di_JServiceManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJServiceManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceManagerClass,_di_JServiceManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJServiceManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B1126ECF-50B9-442F-BEAF-ED15D973DBCD}") JStandardExceptionParserClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JStandardExceptionParser __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JCollection additionalPackages) = 0 ;
};

__interface  INTERFACE_UUID("{87DE064D-2FE7-46C0-A45F-77387B2A1A98}") JStandardExceptionParser  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDescription(Androidapi::Jni::Javatypes::_di_JString threadName, Androidapi::Jni::Javatypes::_di_JThrowable t) = 0 ;
	virtual void __cdecl setIncludedPackages(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JCollection additionalPackages) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStandardExceptionParser : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStandardExceptionParserClass,_di_JStandardExceptionParser>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStandardExceptionParserClass,_di_JStandardExceptionParser> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStandardExceptionParser() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStandardExceptionParserClass,_di_JStandardExceptionParser>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStandardExceptionParser() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B2627961-C102-411C-9B33-CE86DC1CBDC7}") JTrackerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{2AE4F241-3111-4159-A659-40955A45B7E3}") JTracker  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl close() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl constructEvent(Androidapi::Jni::Javatypes::_di_JString category, Androidapi::Jni::Javatypes::_di_JString action, Androidapi::Jni::Javatypes::_di_JString label_, Androidapi::Jni::Javatypes::_di_JLong value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl constructException(Androidapi::Jni::Javatypes::_di_JString exceptionDescription, bool fatal) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl constructRawException(Androidapi::Jni::Javatypes::_di_JString threadName, Androidapi::Jni::Javatypes::_di_JThrowable exception, bool fatal) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl constructSocial(Androidapi::Jni::Javatypes::_di_JString network, Androidapi::Jni::Javatypes::_di_JString action, Androidapi::Jni::Javatypes::_di_JString target) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl constructTiming(Androidapi::Jni::Javatypes::_di_JString category, __int64 intervalInMilliseconds, Androidapi::Jni::Javatypes::_di_JString name, Androidapi::Jni::Javatypes::_di_JString label_) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl constructTransaction(_di_JTransaction trans) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl get(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAppId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAppInstallerId() = 0 ;
	virtual _di_JExceptionParser __cdecl getExceptionParser() = 0 ;
	virtual double __cdecl getSampleRate() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getTrackingId() = 0 ;
	virtual bool __cdecl isAnonymizeIpEnabled() = 0 ;
	virtual bool __cdecl isUseSecure() = 0 ;
	virtual void __cdecl send(Androidapi::Jni::Javatypes::_di_JString hitType, Androidapi::Jni::Javatypes::_di_JMap params) = 0 ;
	virtual void __cdecl sendEvent(Androidapi::Jni::Javatypes::_di_JString category, Androidapi::Jni::Javatypes::_di_JString action, Androidapi::Jni::Javatypes::_di_JString label_, Androidapi::Jni::Javatypes::_di_JLong value) = 0 ;
	virtual void __cdecl sendException(Androidapi::Jni::Javatypes::_di_JString description, bool fatal) = 0 /* overload */;
	virtual void __cdecl sendException(Androidapi::Jni::Javatypes::_di_JString threadName, Androidapi::Jni::Javatypes::_di_JThrowable exception, bool fatal) = 0 /* overload */;
	virtual void __cdecl sendSocial(Androidapi::Jni::Javatypes::_di_JString network, Androidapi::Jni::Javatypes::_di_JString action, Androidapi::Jni::Javatypes::_di_JString target) = 0 ;
	virtual void __cdecl sendTiming(Androidapi::Jni::Javatypes::_di_JString category, __int64 intervalInMilliseconds, Androidapi::Jni::Javatypes::_di_JString name, Androidapi::Jni::Javatypes::_di_JString label_) = 0 ;
	virtual void __cdecl sendTransaction(_di_JTransaction transaction) = 0 ;
	virtual void __cdecl sendView() = 0 /* overload */;
	virtual void __cdecl sendView(Androidapi::Jni::Javatypes::_di_JString appScreen) = 0 /* overload */;
	virtual void __cdecl set(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JString value) = 0 ;
	virtual void __cdecl setAnonymizeIp(bool anonymizeIp) = 0 ;
	virtual void __cdecl setAppId(Androidapi::Jni::Javatypes::_di_JString appId) = 0 ;
	virtual void __cdecl setAppInstallerId(Androidapi::Jni::Javatypes::_di_JString appInstallerId) = 0 ;
	virtual void __cdecl setAppName(Androidapi::Jni::Javatypes::_di_JString appName) = 0 ;
	virtual void __cdecl setAppScreen(Androidapi::Jni::Javatypes::_di_JString appScreen) = 0 ;
	virtual void __cdecl setAppVersion(Androidapi::Jni::Javatypes::_di_JString appVersion) = 0 ;
	virtual void __cdecl setCampaign(Androidapi::Jni::Javatypes::_di_JString campaign) = 0 ;
	virtual void __cdecl setCustomDimension(int index, Androidapi::Jni::Javatypes::_di_JString value) = 0 ;
	virtual void __cdecl setCustomDimensionsAndMetrics(Androidapi::Jni::Javatypes::_di_JMap dimensions, Androidapi::Jni::Javatypes::_di_JMap metrics) = 0 ;
	virtual void __cdecl setCustomMetric(int index, Androidapi::Jni::Javatypes::_di_JLong value) = 0 ;
	virtual void __cdecl setExceptionParser(_di_JExceptionParser exceptionParser) = 0 ;
	virtual void __cdecl setReferrer(Androidapi::Jni::Javatypes::_di_JString referrer) = 0 ;
	virtual void __cdecl setSampleRate(double sampleRate) = 0 ;
	virtual void __cdecl setStartSession(bool startSession) = 0 ;
	virtual void __cdecl setThrottlingEnabled(bool throttlingEnabled) = 0 ;
	virtual void __cdecl setUseSecure(bool useSecure) = 0 ;
	virtual void __cdecl trackEvent(Androidapi::Jni::Javatypes::_di_JString category, Androidapi::Jni::Javatypes::_di_JString action, Androidapi::Jni::Javatypes::_di_JString label_, Androidapi::Jni::Javatypes::_di_JLong value) = 0 ;
	virtual void __cdecl trackException(Androidapi::Jni::Javatypes::_di_JString description, bool fatal) = 0 /* overload */;
	virtual void __cdecl trackException(Androidapi::Jni::Javatypes::_di_JString threadName, Androidapi::Jni::Javatypes::_di_JThrowable exception, bool fatal) = 0 /* overload */;
	virtual void __cdecl trackSocial(Androidapi::Jni::Javatypes::_di_JString network, Androidapi::Jni::Javatypes::_di_JString action, Androidapi::Jni::Javatypes::_di_JString target) = 0 ;
	virtual void __cdecl trackTiming(Androidapi::Jni::Javatypes::_di_JString category, __int64 intervalInMilliseconds, Androidapi::Jni::Javatypes::_di_JString name, Androidapi::Jni::Javatypes::_di_JString label_) = 0 ;
	virtual void __cdecl trackTransaction(_di_JTransaction transaction) = 0 ;
	virtual void __cdecl trackView() = 0 /* overload */;
	virtual void __cdecl trackView(Androidapi::Jni::Javatypes::_di_JString appScreen) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTracker : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTrackerClass,_di_JTracker>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTrackerClass,_di_JTracker> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTracker() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTrackerClass,_di_JTracker>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTracker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{28763069-CEB0-4D82-9B5F-023427DB6153}") JTransactionClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{90F8AAE4-659D-4A92-91F5-FEF97EEECEA0}") JTransaction  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl addItem(_di_JTransaction_Item item) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAffiliation() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getCurrencyCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getItems() = 0 ;
	virtual __int64 __cdecl getShippingCostInMicros() = 0 ;
	virtual __int64 __cdecl getTotalCostInMicros() = 0 ;
	virtual __int64 __cdecl getTotalTaxInMicros() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getTransactionId() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTransaction : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTransactionClass,_di_JTransaction>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTransactionClass,_di_JTransaction> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTransaction() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTransactionClass,_di_JTransaction>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTransaction() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{042AF3D5-7D57-4656-8A94-A8D5938BE96F}") JTransaction_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JTransaction_Builder __cdecl init(Androidapi::Jni::Javatypes::_di_JString transactionId, __int64 totalCostInMicros) = 0 ;
};

__interface  INTERFACE_UUID("{AAFE40C1-0964-4EB7-B035-983C84BE1F13}") JTransaction_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JTransaction __cdecl build() = 0 ;
	virtual _di_JTransaction_Builder __cdecl setAffiliation(Androidapi::Jni::Javatypes::_di_JString affiliation) = 0 ;
	virtual _di_JTransaction_Builder __cdecl setCurrencyCode(Androidapi::Jni::Javatypes::_di_JString currencyCode) = 0 ;
	virtual _di_JTransaction_Builder __cdecl setShippingCostInMicros(__int64 shippingCostInMicros) = 0 ;
	virtual _di_JTransaction_Builder __cdecl setTotalTaxInMicros(__int64 totalTaxInMicros) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTransaction_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTransaction_BuilderClass,_di_JTransaction_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTransaction_BuilderClass,_di_JTransaction_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTransaction_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTransaction_BuilderClass,_di_JTransaction_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTransaction_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2A64E0A4-BF0B-4DFA-9658-0682CE2AD6AA}") JTransaction_ItemClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{A9B5E013-D50F-4BAB-BECA-0E443060C755}") JTransaction_Item  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getCategory() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
	virtual __int64 __cdecl getPriceInMicros() = 0 ;
	virtual __int64 __cdecl getQuantity() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSKU() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTransaction_Item : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTransaction_ItemClass,_di_JTransaction_Item>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTransaction_ItemClass,_di_JTransaction_Item> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTransaction_Item() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTransaction_ItemClass,_di_JTransaction_Item>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTransaction_Item() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0934FF65-7A08-434E-B03F-695732A0E409}") JItem_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JItem_Builder __cdecl init(Androidapi::Jni::Javatypes::_di_JString SKU, Androidapi::Jni::Javatypes::_di_JString name, __int64 priceInMicros, __int64 quantity) = 0 ;
};

__interface  INTERFACE_UUID("{2F7E85FE-FA41-4F65-91DD-055211F20FC4}") JItem_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JTransaction_Item __cdecl build() = 0 ;
	virtual _di_JItem_Builder __cdecl setProductCategory(Androidapi::Jni::Javatypes::_di_JString productCategory) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJItem_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JItem_BuilderClass,_di_JItem_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JItem_BuilderClass,_di_JItem_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJItem_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JItem_BuilderClass,_di_JItem_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJItem_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Analytics */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_ANALYTICS)
using namespace Androidapi::Jni::Analytics;
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
#endif	// Androidapi_Jni_AnalyticsHPP
