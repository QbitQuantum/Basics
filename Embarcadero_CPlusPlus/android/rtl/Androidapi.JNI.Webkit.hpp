// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Webkit.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_WebkitHPP
#define Androidapi_Jni_WebkitHPP

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
#include <Androidapi.JNI.Java.Security.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Net.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.JNI.Print.hpp>
#include <Androidapi.JNI.Util.hpp>
#include <Androidapi.JNI.Widget.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Webkit
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JClientCertRequestClass;
typedef System::DelphiInterface<JClientCertRequestClass> _di_JClientCertRequestClass;
__interface DELPHIINTERFACE JClientCertRequest;
typedef System::DelphiInterface<JClientCertRequest> _di_JClientCertRequest;
class DELPHICLASS TJClientCertRequest;
__interface DELPHIINTERFACE JConsoleMessageClass;
typedef System::DelphiInterface<JConsoleMessageClass> _di_JConsoleMessageClass;
__interface DELPHIINTERFACE JConsoleMessage;
typedef System::DelphiInterface<JConsoleMessage> _di_JConsoleMessage;
class DELPHICLASS TJConsoleMessage;
__interface DELPHIINTERFACE JConsoleMessage_MessageLevelClass;
typedef System::DelphiInterface<JConsoleMessage_MessageLevelClass> _di_JConsoleMessage_MessageLevelClass;
__interface DELPHIINTERFACE JConsoleMessage_MessageLevel;
typedef System::DelphiInterface<JConsoleMessage_MessageLevel> _di_JConsoleMessage_MessageLevel;
class DELPHICLASS TJConsoleMessage_MessageLevel;
__interface DELPHIINTERFACE JCookieManagerClass;
typedef System::DelphiInterface<JCookieManagerClass> _di_JCookieManagerClass;
__interface DELPHIINTERFACE JCookieManager;
typedef System::DelphiInterface<JCookieManager> _di_JCookieManager;
class DELPHICLASS TJCookieManager;
__interface DELPHIINTERFACE JCookieSyncManagerClass;
typedef System::DelphiInterface<JCookieSyncManagerClass> _di_JCookieSyncManagerClass;
__interface DELPHIINTERFACE JCookieSyncManager;
typedef System::DelphiInterface<JCookieSyncManager> _di_JCookieSyncManager;
class DELPHICLASS TJCookieSyncManager;
__interface DELPHIINTERFACE JDateSorterClass;
typedef System::DelphiInterface<JDateSorterClass> _di_JDateSorterClass;
__interface DELPHIINTERFACE JDateSorter;
typedef System::DelphiInterface<JDateSorter> _di_JDateSorter;
class DELPHICLASS TJDateSorter;
__interface DELPHIINTERFACE JDownloadListenerClass;
typedef System::DelphiInterface<JDownloadListenerClass> _di_JDownloadListenerClass;
__interface DELPHIINTERFACE JDownloadListener;
typedef System::DelphiInterface<JDownloadListener> _di_JDownloadListener;
class DELPHICLASS TJDownloadListener;
__interface DELPHIINTERFACE JGeolocationPermissionsClass;
typedef System::DelphiInterface<JGeolocationPermissionsClass> _di_JGeolocationPermissionsClass;
__interface DELPHIINTERFACE JGeolocationPermissions;
typedef System::DelphiInterface<JGeolocationPermissions> _di_JGeolocationPermissions;
class DELPHICLASS TJGeolocationPermissions;
__interface DELPHIINTERFACE JGeolocationPermissions_CallbackClass;
typedef System::DelphiInterface<JGeolocationPermissions_CallbackClass> _di_JGeolocationPermissions_CallbackClass;
__interface DELPHIINTERFACE JGeolocationPermissions_Callback;
typedef System::DelphiInterface<JGeolocationPermissions_Callback> _di_JGeolocationPermissions_Callback;
class DELPHICLASS TJGeolocationPermissions_Callback;
__interface DELPHIINTERFACE JHttpAuthHandlerClass;
typedef System::DelphiInterface<JHttpAuthHandlerClass> _di_JHttpAuthHandlerClass;
__interface DELPHIINTERFACE JHttpAuthHandler;
typedef System::DelphiInterface<JHttpAuthHandler> _di_JHttpAuthHandler;
class DELPHICLASS TJHttpAuthHandler;
__interface DELPHIINTERFACE JJavascriptInterfaceClass;
typedef System::DelphiInterface<JJavascriptInterfaceClass> _di_JJavascriptInterfaceClass;
__interface DELPHIINTERFACE JJavascriptInterface;
typedef System::DelphiInterface<JJavascriptInterface> _di_JJavascriptInterface;
class DELPHICLASS TJJavascriptInterface;
__interface DELPHIINTERFACE JJsResultClass;
typedef System::DelphiInterface<JJsResultClass> _di_JJsResultClass;
__interface DELPHIINTERFACE JJsResult;
typedef System::DelphiInterface<JJsResult> _di_JJsResult;
class DELPHICLASS TJJsResult;
__interface DELPHIINTERFACE JJsPromptResultClass;
typedef System::DelphiInterface<JJsPromptResultClass> _di_JJsPromptResultClass;
__interface DELPHIINTERFACE JJsPromptResult;
typedef System::DelphiInterface<JJsPromptResult> _di_JJsPromptResult;
class DELPHICLASS TJJsPromptResult;
__interface DELPHIINTERFACE JMimeTypeMapClass;
typedef System::DelphiInterface<JMimeTypeMapClass> _di_JMimeTypeMapClass;
__interface DELPHIINTERFACE JMimeTypeMap;
typedef System::DelphiInterface<JMimeTypeMap> _di_JMimeTypeMap;
class DELPHICLASS TJMimeTypeMap;
__interface DELPHIINTERFACE JPermissionRequestClass;
typedef System::DelphiInterface<JPermissionRequestClass> _di_JPermissionRequestClass;
__interface DELPHIINTERFACE JPermissionRequest;
typedef System::DelphiInterface<JPermissionRequest> _di_JPermissionRequest;
class DELPHICLASS TJPermissionRequest;
__interface DELPHIINTERFACE JPluginStubClass;
typedef System::DelphiInterface<JPluginStubClass> _di_JPluginStubClass;
__interface DELPHIINTERFACE JPluginStub;
typedef System::DelphiInterface<JPluginStub> _di_JPluginStub;
class DELPHICLASS TJPluginStub;
__interface DELPHIINTERFACE JRenderProcessGoneDetailClass;
typedef System::DelphiInterface<JRenderProcessGoneDetailClass> _di_JRenderProcessGoneDetailClass;
__interface DELPHIINTERFACE JRenderProcessGoneDetail;
typedef System::DelphiInterface<JRenderProcessGoneDetail> _di_JRenderProcessGoneDetail;
class DELPHICLASS TJRenderProcessGoneDetail;
__interface DELPHIINTERFACE JServiceWorkerClientClass;
typedef System::DelphiInterface<JServiceWorkerClientClass> _di_JServiceWorkerClientClass;
__interface DELPHIINTERFACE JServiceWorkerClient;
typedef System::DelphiInterface<JServiceWorkerClient> _di_JServiceWorkerClient;
class DELPHICLASS TJServiceWorkerClient;
__interface DELPHIINTERFACE JServiceWorkerControllerClass;
typedef System::DelphiInterface<JServiceWorkerControllerClass> _di_JServiceWorkerControllerClass;
__interface DELPHIINTERFACE JServiceWorkerController;
typedef System::DelphiInterface<JServiceWorkerController> _di_JServiceWorkerController;
class DELPHICLASS TJServiceWorkerController;
__interface DELPHIINTERFACE JServiceWorkerWebSettingsClass;
typedef System::DelphiInterface<JServiceWorkerWebSettingsClass> _di_JServiceWorkerWebSettingsClass;
__interface DELPHIINTERFACE JServiceWorkerWebSettings;
typedef System::DelphiInterface<JServiceWorkerWebSettings> _di_JServiceWorkerWebSettings;
class DELPHICLASS TJServiceWorkerWebSettings;
__interface DELPHIINTERFACE JSslErrorHandlerClass;
typedef System::DelphiInterface<JSslErrorHandlerClass> _di_JSslErrorHandlerClass;
__interface DELPHIINTERFACE JSslErrorHandler;
typedef System::DelphiInterface<JSslErrorHandler> _di_JSslErrorHandler;
class DELPHICLASS TJSslErrorHandler;
__interface DELPHIINTERFACE JURLUtilClass;
typedef System::DelphiInterface<JURLUtilClass> _di_JURLUtilClass;
__interface DELPHIINTERFACE JURLUtil;
typedef System::DelphiInterface<JURLUtil> _di_JURLUtil;
class DELPHICLASS TJURLUtil;
__interface DELPHIINTERFACE JValueCallbackClass;
typedef System::DelphiInterface<JValueCallbackClass> _di_JValueCallbackClass;
__interface DELPHIINTERFACE JValueCallback;
typedef System::DelphiInterface<JValueCallback> _di_JValueCallback;
class DELPHICLASS TJValueCallback;
__interface DELPHIINTERFACE JWebBackForwardListClass;
typedef System::DelphiInterface<JWebBackForwardListClass> _di_JWebBackForwardListClass;
__interface DELPHIINTERFACE JWebBackForwardList;
typedef System::DelphiInterface<JWebBackForwardList> _di_JWebBackForwardList;
class DELPHICLASS TJWebBackForwardList;
__interface DELPHIINTERFACE JWebChromeClientClass;
typedef System::DelphiInterface<JWebChromeClientClass> _di_JWebChromeClientClass;
__interface DELPHIINTERFACE JWebChromeClient;
typedef System::DelphiInterface<JWebChromeClient> _di_JWebChromeClient;
class DELPHICLASS TJWebChromeClient;
__interface DELPHIINTERFACE JWebChromeClient_CustomViewCallbackClass;
typedef System::DelphiInterface<JWebChromeClient_CustomViewCallbackClass> _di_JWebChromeClient_CustomViewCallbackClass;
__interface DELPHIINTERFACE JWebChromeClient_CustomViewCallback;
typedef System::DelphiInterface<JWebChromeClient_CustomViewCallback> _di_JWebChromeClient_CustomViewCallback;
class DELPHICLASS TJWebChromeClient_CustomViewCallback;
__interface DELPHIINTERFACE JWebChromeClient_FileChooserParamsClass;
typedef System::DelphiInterface<JWebChromeClient_FileChooserParamsClass> _di_JWebChromeClient_FileChooserParamsClass;
__interface DELPHIINTERFACE JWebChromeClient_FileChooserParams;
typedef System::DelphiInterface<JWebChromeClient_FileChooserParams> _di_JWebChromeClient_FileChooserParams;
class DELPHICLASS TJWebChromeClient_FileChooserParams;
__interface DELPHIINTERFACE JWebHistoryItemClass;
typedef System::DelphiInterface<JWebHistoryItemClass> _di_JWebHistoryItemClass;
__interface DELPHIINTERFACE JWebHistoryItem;
typedef System::DelphiInterface<JWebHistoryItem> _di_JWebHistoryItem;
class DELPHICLASS TJWebHistoryItem;
__interface DELPHIINTERFACE JWebIconDatabaseClass;
typedef System::DelphiInterface<JWebIconDatabaseClass> _di_JWebIconDatabaseClass;
__interface DELPHIINTERFACE JWebIconDatabase;
typedef System::DelphiInterface<JWebIconDatabase> _di_JWebIconDatabase;
class DELPHICLASS TJWebIconDatabase;
__interface DELPHIINTERFACE JWebIconDatabase_IconListenerClass;
typedef System::DelphiInterface<JWebIconDatabase_IconListenerClass> _di_JWebIconDatabase_IconListenerClass;
__interface DELPHIINTERFACE JWebIconDatabase_IconListener;
typedef System::DelphiInterface<JWebIconDatabase_IconListener> _di_JWebIconDatabase_IconListener;
class DELPHICLASS TJWebIconDatabase_IconListener;
__interface DELPHIINTERFACE JWebMessageClass;
typedef System::DelphiInterface<JWebMessageClass> _di_JWebMessageClass;
__interface DELPHIINTERFACE JWebMessage;
typedef System::DelphiInterface<JWebMessage> _di_JWebMessage;
class DELPHICLASS TJWebMessage;
__interface DELPHIINTERFACE JWebMessagePortClass;
typedef System::DelphiInterface<JWebMessagePortClass> _di_JWebMessagePortClass;
__interface DELPHIINTERFACE JWebMessagePort;
typedef System::DelphiInterface<JWebMessagePort> _di_JWebMessagePort;
class DELPHICLASS TJWebMessagePort;
__interface DELPHIINTERFACE JWebMessagePort_WebMessageCallbackClass;
typedef System::DelphiInterface<JWebMessagePort_WebMessageCallbackClass> _di_JWebMessagePort_WebMessageCallbackClass;
__interface DELPHIINTERFACE JWebMessagePort_WebMessageCallback;
typedef System::DelphiInterface<JWebMessagePort_WebMessageCallback> _di_JWebMessagePort_WebMessageCallback;
class DELPHICLASS TJWebMessagePort_WebMessageCallback;
__interface DELPHIINTERFACE JWebResourceErrorClass;
typedef System::DelphiInterface<JWebResourceErrorClass> _di_JWebResourceErrorClass;
__interface DELPHIINTERFACE JWebResourceError;
typedef System::DelphiInterface<JWebResourceError> _di_JWebResourceError;
class DELPHICLASS TJWebResourceError;
__interface DELPHIINTERFACE JWebResourceRequestClass;
typedef System::DelphiInterface<JWebResourceRequestClass> _di_JWebResourceRequestClass;
__interface DELPHIINTERFACE JWebResourceRequest;
typedef System::DelphiInterface<JWebResourceRequest> _di_JWebResourceRequest;
class DELPHICLASS TJWebResourceRequest;
__interface DELPHIINTERFACE JWebResourceResponseClass;
typedef System::DelphiInterface<JWebResourceResponseClass> _di_JWebResourceResponseClass;
__interface DELPHIINTERFACE JWebResourceResponse;
typedef System::DelphiInterface<JWebResourceResponse> _di_JWebResourceResponse;
class DELPHICLASS TJWebResourceResponse;
__interface DELPHIINTERFACE JWebSettingsClass;
typedef System::DelphiInterface<JWebSettingsClass> _di_JWebSettingsClass;
__interface DELPHIINTERFACE JWebSettings;
typedef System::DelphiInterface<JWebSettings> _di_JWebSettings;
class DELPHICLASS TJWebSettings;
__interface DELPHIINTERFACE JWebSettings_LayoutAlgorithmClass;
typedef System::DelphiInterface<JWebSettings_LayoutAlgorithmClass> _di_JWebSettings_LayoutAlgorithmClass;
__interface DELPHIINTERFACE JWebSettings_LayoutAlgorithm;
typedef System::DelphiInterface<JWebSettings_LayoutAlgorithm> _di_JWebSettings_LayoutAlgorithm;
class DELPHICLASS TJWebSettings_LayoutAlgorithm;
__interface DELPHIINTERFACE JWebSettings_PluginStateClass;
typedef System::DelphiInterface<JWebSettings_PluginStateClass> _di_JWebSettings_PluginStateClass;
__interface DELPHIINTERFACE JWebSettings_PluginState;
typedef System::DelphiInterface<JWebSettings_PluginState> _di_JWebSettings_PluginState;
class DELPHICLASS TJWebSettings_PluginState;
__interface DELPHIINTERFACE JWebSettings_RenderPriorityClass;
typedef System::DelphiInterface<JWebSettings_RenderPriorityClass> _di_JWebSettings_RenderPriorityClass;
__interface DELPHIINTERFACE JWebSettings_RenderPriority;
typedef System::DelphiInterface<JWebSettings_RenderPriority> _di_JWebSettings_RenderPriority;
class DELPHICLASS TJWebSettings_RenderPriority;
__interface DELPHIINTERFACE JWebSettings_TextSizeClass;
typedef System::DelphiInterface<JWebSettings_TextSizeClass> _di_JWebSettings_TextSizeClass;
__interface DELPHIINTERFACE JWebSettings_TextSize;
typedef System::DelphiInterface<JWebSettings_TextSize> _di_JWebSettings_TextSize;
class DELPHICLASS TJWebSettings_TextSize;
__interface DELPHIINTERFACE JWebSettings_ZoomDensityClass;
typedef System::DelphiInterface<JWebSettings_ZoomDensityClass> _di_JWebSettings_ZoomDensityClass;
__interface DELPHIINTERFACE JWebSettings_ZoomDensity;
typedef System::DelphiInterface<JWebSettings_ZoomDensity> _di_JWebSettings_ZoomDensity;
class DELPHICLASS TJWebSettings_ZoomDensity;
__interface DELPHIINTERFACE JWebStorageClass;
typedef System::DelphiInterface<JWebStorageClass> _di_JWebStorageClass;
__interface DELPHIINTERFACE JWebStorage;
typedef System::DelphiInterface<JWebStorage> _di_JWebStorage;
class DELPHICLASS TJWebStorage;
__interface DELPHIINTERFACE JWebStorage_OriginClass;
typedef System::DelphiInterface<JWebStorage_OriginClass> _di_JWebStorage_OriginClass;
__interface DELPHIINTERFACE JWebStorage_Origin;
typedef System::DelphiInterface<JWebStorage_Origin> _di_JWebStorage_Origin;
class DELPHICLASS TJWebStorage_Origin;
__interface DELPHIINTERFACE JWebStorage_QuotaUpdaterClass;
typedef System::DelphiInterface<JWebStorage_QuotaUpdaterClass> _di_JWebStorage_QuotaUpdaterClass;
__interface DELPHIINTERFACE JWebStorage_QuotaUpdater;
typedef System::DelphiInterface<JWebStorage_QuotaUpdater> _di_JWebStorage_QuotaUpdater;
class DELPHICLASS TJWebStorage_QuotaUpdater;
__interface DELPHIINTERFACE JWebViewClass;
typedef System::DelphiInterface<JWebViewClass> _di_JWebViewClass;
__interface DELPHIINTERFACE JWebView;
typedef System::DelphiInterface<JWebView> _di_JWebView;
class DELPHICLASS TJWebView;
__interface DELPHIINTERFACE JWebView_FindListenerClass;
typedef System::DelphiInterface<JWebView_FindListenerClass> _di_JWebView_FindListenerClass;
__interface DELPHIINTERFACE JWebView_FindListener;
typedef System::DelphiInterface<JWebView_FindListener> _di_JWebView_FindListener;
class DELPHICLASS TJWebView_FindListener;
__interface DELPHIINTERFACE JWebView_HitTestResultClass;
typedef System::DelphiInterface<JWebView_HitTestResultClass> _di_JWebView_HitTestResultClass;
__interface DELPHIINTERFACE JWebView_HitTestResult;
typedef System::DelphiInterface<JWebView_HitTestResult> _di_JWebView_HitTestResult;
class DELPHICLASS TJWebView_HitTestResult;
__interface DELPHIINTERFACE JWebView_PictureListenerClass;
typedef System::DelphiInterface<JWebView_PictureListenerClass> _di_JWebView_PictureListenerClass;
__interface DELPHIINTERFACE JWebView_PictureListener;
typedef System::DelphiInterface<JWebView_PictureListener> _di_JWebView_PictureListener;
class DELPHICLASS TJWebView_PictureListener;
__interface DELPHIINTERFACE JWebView_VisualStateCallbackClass;
typedef System::DelphiInterface<JWebView_VisualStateCallbackClass> _di_JWebView_VisualStateCallbackClass;
__interface DELPHIINTERFACE JWebView_VisualStateCallback;
typedef System::DelphiInterface<JWebView_VisualStateCallback> _di_JWebView_VisualStateCallback;
class DELPHICLASS TJWebView_VisualStateCallback;
__interface DELPHIINTERFACE JWebView_WebViewTransportClass;
typedef System::DelphiInterface<JWebView_WebViewTransportClass> _di_JWebView_WebViewTransportClass;
__interface DELPHIINTERFACE JWebView_WebViewTransport;
typedef System::DelphiInterface<JWebView_WebViewTransport> _di_JWebView_WebViewTransport;
class DELPHICLASS TJWebView_WebViewTransport;
__interface DELPHIINTERFACE JWebViewClientClass;
typedef System::DelphiInterface<JWebViewClientClass> _di_JWebViewClientClass;
__interface DELPHIINTERFACE JWebViewClient;
typedef System::DelphiInterface<JWebViewClient> _di_JWebViewClient;
class DELPHICLASS TJWebViewClient;
__interface DELPHIINTERFACE JWebViewDatabaseClass;
typedef System::DelphiInterface<JWebViewDatabaseClass> _di_JWebViewDatabaseClass;
__interface DELPHIINTERFACE JWebViewDatabase;
typedef System::DelphiInterface<JWebViewDatabase> _di_JWebViewDatabase;
class DELPHICLASS TJWebViewDatabase;
__interface DELPHIINTERFACE JWebViewFragmentClass;
typedef System::DelphiInterface<JWebViewFragmentClass> _di_JWebViewFragmentClass;
__interface DELPHIINTERFACE JWebViewFragment;
typedef System::DelphiInterface<JWebViewFragment> _di_JWebViewFragment;
class DELPHICLASS TJWebViewFragment;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{91624F2C-4EB1-48F2-91DD-A792988486B3}") JClientCertRequestClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JClientCertRequest __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{8BF18830-4FB6-4F4B-8351-9CFA03362E2A}") JClientCertRequest  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl cancel() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getHost() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getKeyTypes() = 0 ;
	virtual int __cdecl getPort() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JPrincipal>* __cdecl getPrincipals() = 0 ;
	virtual void __cdecl ignore() = 0 ;
	virtual void __cdecl proceed(Androidapi::Jni::Java::Security::_di_JPrivateKey privateKey, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JX509Certificate>* chain) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJClientCertRequest : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JClientCertRequestClass,_di_JClientCertRequest>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JClientCertRequestClass,_di_JClientCertRequest> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJClientCertRequest() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JClientCertRequestClass,_di_JClientCertRequest>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJClientCertRequest() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{CBB5BC88-0DE7-4587-8D99-B2F2B69BD91C}") JConsoleMessageClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JConsoleMessage __cdecl init(Androidapi::Jni::Javatypes::_di_JString message, Androidapi::Jni::Javatypes::_di_JString sourceId, int lineNumber, _di_JConsoleMessage_MessageLevel msgLevel) = 0 ;
};

__interface  INTERFACE_UUID("{08638DAF-1309-4F99-9B6D-8998BF31A730}") JConsoleMessage  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl lineNumber() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl message() = 0 ;
	virtual _di_JConsoleMessage_MessageLevel __cdecl messageLevel() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl sourceId() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJConsoleMessage : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JConsoleMessageClass,_di_JConsoleMessage>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JConsoleMessageClass,_di_JConsoleMessage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJConsoleMessage() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JConsoleMessageClass,_di_JConsoleMessage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJConsoleMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EBA1E801-E409-4FD2-B5D0-A21E3D73C05A}") JConsoleMessage_MessageLevelClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JConsoleMessage_MessageLevel __cdecl _GetDEBUG() = 0 ;
	virtual _di_JConsoleMessage_MessageLevel __cdecl _GetERROR() = 0 ;
	virtual _di_JConsoleMessage_MessageLevel __cdecl _GetLOG() = 0 ;
	virtual _di_JConsoleMessage_MessageLevel __cdecl _GetTIP() = 0 ;
	virtual _di_JConsoleMessage_MessageLevel __cdecl _GetWARNING() = 0 ;
	HIDESBASE virtual _di_JConsoleMessage_MessageLevel __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JConsoleMessage_MessageLevel>* __cdecl values() = 0 ;
	__property _di_JConsoleMessage_MessageLevel DEBUG = {read=_GetDEBUG};
	__property _di_JConsoleMessage_MessageLevel ERROR = {read=_GetERROR};
	__property _di_JConsoleMessage_MessageLevel LOG = {read=_GetLOG};
	__property _di_JConsoleMessage_MessageLevel TIP = {read=_GetTIP};
	__property _di_JConsoleMessage_MessageLevel WARNING = {read=_GetWARNING};
};

__interface  INTERFACE_UUID("{D2D9F689-DB98-41EE-A319-0BE781C70A98}") JConsoleMessage_MessageLevel  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJConsoleMessage_MessageLevel : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JConsoleMessage_MessageLevelClass,_di_JConsoleMessage_MessageLevel>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JConsoleMessage_MessageLevelClass,_di_JConsoleMessage_MessageLevel> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJConsoleMessage_MessageLevel() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JConsoleMessage_MessageLevelClass,_di_JConsoleMessage_MessageLevel>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJConsoleMessage_MessageLevel() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AA56EEB3-9124-4EA5-9C2D-F2A34B85A746}") JCookieManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JCookieManager __cdecl init() = 0 ;
	virtual bool __cdecl allowFileSchemeCookies() = 0 ;
	virtual _di_JCookieManager __cdecl getInstance() = 0 ;
	virtual void __cdecl setAcceptFileSchemeCookies(bool accept) = 0 ;
};

__interface  INTERFACE_UUID("{D034D488-20B0-40B1-B8E8-DBA885920119}") JCookieManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl acceptCookie() = 0 ;
	virtual bool __cdecl acceptThirdPartyCookies(_di_JWebView webview) = 0 ;
	virtual void __cdecl flush() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getCookie(Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual bool __cdecl hasCookies() = 0 ;
	virtual void __cdecl removeAllCookie() = 0 ;
	virtual void __cdecl removeAllCookies(_di_JValueCallback callback) = 0 ;
	virtual void __cdecl removeExpiredCookie() = 0 ;
	virtual void __cdecl removeSessionCookie() = 0 ;
	virtual void __cdecl removeSessionCookies(_di_JValueCallback callback) = 0 ;
	virtual void __cdecl setAcceptCookie(bool accept) = 0 ;
	virtual void __cdecl setAcceptThirdPartyCookies(_di_JWebView webview, bool accept) = 0 ;
	virtual void __cdecl setCookie(Androidapi::Jni::Javatypes::_di_JString url, Androidapi::Jni::Javatypes::_di_JString value) = 0 /* overload */;
	virtual void __cdecl setCookie(Androidapi::Jni::Javatypes::_di_JString url, Androidapi::Jni::Javatypes::_di_JString value, _di_JValueCallback callback) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCookieManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCookieManagerClass,_di_JCookieManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCookieManagerClass,_di_JCookieManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCookieManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCookieManagerClass,_di_JCookieManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCookieManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{96CCECF6-1D55-49E3-9DB6-A260AFD605BF}") JCookieSyncManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JCookieSyncManager __cdecl createInstance(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual _di_JCookieSyncManager __cdecl getInstance() = 0 ;
};

__interface  INTERFACE_UUID("{A548B195-9703-456F-9ACB-26DF88014690}") JCookieSyncManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl resetSync() = 0 ;
	virtual void __cdecl startSync() = 0 ;
	virtual void __cdecl stopSync() = 0 ;
	virtual void __cdecl sync() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCookieSyncManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCookieSyncManagerClass,_di_JCookieSyncManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCookieSyncManagerClass,_di_JCookieSyncManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCookieSyncManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCookieSyncManagerClass,_di_JCookieSyncManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCookieSyncManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E5ED8EFC-3CB5-4650-A9B3-6B09646B0C50}") JDateSorterClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetDAY_COUNT() = 0 ;
	HIDESBASE virtual _di_JDateSorter __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	__property int DAY_COUNT = {read=_GetDAY_COUNT};
};

__interface  INTERFACE_UUID("{566DE920-3B0F-4AF9-A8EF-BC81E5E3499B}") JDateSorter  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual __int64 __cdecl getBoundary(int index) = 0 ;
	virtual int __cdecl getIndex(__int64 time) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getLabel(int index) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDateSorter : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDateSorterClass,_di_JDateSorter>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDateSorterClass,_di_JDateSorter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDateSorter() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDateSorterClass,_di_JDateSorter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDateSorter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{DAFCF031-2702-4450-A30A-8CBB59C687FA}") JDownloadListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{BB9F3B4B-B375-4870-AE50-66DDCB0253F8}") JDownloadListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onDownloadStart(Androidapi::Jni::Javatypes::_di_JString url, Androidapi::Jni::Javatypes::_di_JString userAgent, Androidapi::Jni::Javatypes::_di_JString contentDisposition, Androidapi::Jni::Javatypes::_di_JString mimetype, __int64 contentLength) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDownloadListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadListenerClass,_di_JDownloadListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadListenerClass,_di_JDownloadListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDownloadListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadListenerClass,_di_JDownloadListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDownloadListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0EDFDB2D-5AA5-4B9F-AFF1-48B33D4DB768}") JGeolocationPermissionsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JGeolocationPermissions __cdecl getInstance() = 0 ;
};

__interface  INTERFACE_UUID("{3DB62872-CE2B-441A-880F-61853F0D1429}") JGeolocationPermissions  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl allow(Androidapi::Jni::Javatypes::_di_JString origin) = 0 ;
	virtual void __cdecl clear(Androidapi::Jni::Javatypes::_di_JString origin) = 0 ;
	virtual void __cdecl clearAll() = 0 ;
	virtual void __cdecl getAllowed(Androidapi::Jni::Javatypes::_di_JString origin, _di_JValueCallback callback) = 0 ;
	virtual void __cdecl getOrigins(_di_JValueCallback callback) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGeolocationPermissions : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGeolocationPermissionsClass,_di_JGeolocationPermissions>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGeolocationPermissionsClass,_di_JGeolocationPermissions> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGeolocationPermissions() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGeolocationPermissionsClass,_di_JGeolocationPermissions>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGeolocationPermissions() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{38C6FDC6-38D6-4C2E-A2DA-2F548B75F1EA}") JGeolocationPermissions_CallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{A8E62A13-B89F-4680-94F1-FAC7FC900D31}") JGeolocationPermissions_Callback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl invoke(Androidapi::Jni::Javatypes::_di_JString origin, bool allow, bool retain) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGeolocationPermissions_Callback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGeolocationPermissions_CallbackClass,_di_JGeolocationPermissions_Callback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGeolocationPermissions_CallbackClass,_di_JGeolocationPermissions_Callback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGeolocationPermissions_Callback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGeolocationPermissions_CallbackClass,_di_JGeolocationPermissions_Callback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGeolocationPermissions_Callback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F4F240E8-5AD8-4E01-A7F6-3F014FC5ED61}") JHttpAuthHandlerClass  : public Androidapi::Jni::Os::JHandlerClass 
{
	
};

__interface  INTERFACE_UUID("{0E61C17C-91B0-4DF0-B85E-E270B4F69B4B}") JHttpAuthHandler  : public Androidapi::Jni::Os::JHandler 
{
	virtual void __cdecl cancel() = 0 ;
	virtual void __cdecl proceed(Androidapi::Jni::Javatypes::_di_JString username, Androidapi::Jni::Javatypes::_di_JString password) = 0 ;
	virtual bool __cdecl useHttpAuthUsernamePassword() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJHttpAuthHandler : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHttpAuthHandlerClass,_di_JHttpAuthHandler>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHttpAuthHandlerClass,_di_JHttpAuthHandler> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJHttpAuthHandler() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHttpAuthHandlerClass,_di_JHttpAuthHandler>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJHttpAuthHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7D851A79-CBFE-4C5B-A5DC-44A4877FCF7B}") JJavascriptInterfaceClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{4F64688D-578A-4D9A-9FD3-1014C2FDFE50}") JJavascriptInterface  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJJavascriptInterface : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJavascriptInterfaceClass,_di_JJavascriptInterface>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJavascriptInterfaceClass,_di_JJavascriptInterface> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJJavascriptInterface() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJavascriptInterfaceClass,_di_JJavascriptInterface>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJJavascriptInterface() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EC8170B1-2E48-4399-8F0B-690249282CD8}") JJsResultClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{FB00569F-6419-40C9-AFE2-97632E5CB25B}") JJsResult  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl cancel() = 0 ;
	virtual void __cdecl confirm() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJJsResult : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJsResultClass,_di_JJsResult>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJsResultClass,_di_JJsResult> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJJsResult() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJsResultClass,_di_JJsResult>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJJsResult() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{87DB5C55-9E24-4E97-AEB9-5175CE44962F}") JJsPromptResultClass  : public JJsResultClass 
{
	
};

__interface  INTERFACE_UUID("{D88E5DFB-C1B1-444D-AA87-E71D6A50ED21}") JJsPromptResult  : public JJsResult 
{
	HIDESBASE virtual void __cdecl confirm(Androidapi::Jni::Javatypes::_di_JString result) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJJsPromptResult : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJsPromptResultClass,_di_JJsPromptResult>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJsPromptResultClass,_di_JJsPromptResult> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJJsPromptResult() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJsPromptResultClass,_di_JJsPromptResult>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJJsPromptResult() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{590CAE2F-22DD-48BB-8A6A-4B73936BA71C}") JMimeTypeMapClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getFileExtensionFromUrl(Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual _di_JMimeTypeMap __cdecl getSingleton() = 0 ;
};

__interface  INTERFACE_UUID("{40155926-B3E3-4365-99C5-A928F3EB30C7}") JMimeTypeMap  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getExtensionFromMimeType(Androidapi::Jni::Javatypes::_di_JString mimeType) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMimeTypeFromExtension(Androidapi::Jni::Javatypes::_di_JString extension) = 0 ;
	virtual bool __cdecl hasExtension(Androidapi::Jni::Javatypes::_di_JString extension) = 0 ;
	virtual bool __cdecl hasMimeType(Androidapi::Jni::Javatypes::_di_JString mimeType) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMimeTypeMap : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMimeTypeMapClass,_di_JMimeTypeMap>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMimeTypeMapClass,_di_JMimeTypeMap> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMimeTypeMap() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMimeTypeMapClass,_di_JMimeTypeMap>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMimeTypeMap() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4F6758BC-07C6-481E-A18F-9605EB4E911A}") JPermissionRequestClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRESOURCE_AUDIO_CAPTURE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRESOURCE_MIDI_SYSEX() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRESOURCE_PROTECTED_MEDIA_ID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRESOURCE_VIDEO_CAPTURE() = 0 ;
	HIDESBASE virtual _di_JPermissionRequest __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString RESOURCE_AUDIO_CAPTURE = {read=_GetRESOURCE_AUDIO_CAPTURE};
	__property Androidapi::Jni::Javatypes::_di_JString RESOURCE_MIDI_SYSEX = {read=_GetRESOURCE_MIDI_SYSEX};
	__property Androidapi::Jni::Javatypes::_di_JString RESOURCE_PROTECTED_MEDIA_ID = {read=_GetRESOURCE_PROTECTED_MEDIA_ID};
	__property Androidapi::Jni::Javatypes::_di_JString RESOURCE_VIDEO_CAPTURE = {read=_GetRESOURCE_VIDEO_CAPTURE};
};

__interface  INTERFACE_UUID("{89C3D143-C210-4D87-B945-373AEEE139BD}") JPermissionRequest  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl deny() = 0 ;
	virtual Androidapi::Jni::Net::_di_Jnet_Uri __cdecl getOrigin() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getResources() = 0 ;
	virtual void __cdecl grant(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* resources) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPermissionRequest : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPermissionRequestClass,_di_JPermissionRequest>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPermissionRequestClass,_di_JPermissionRequest> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPermissionRequest() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPermissionRequestClass,_di_JPermissionRequest>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPermissionRequest() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{91084F0F-96A4-45B7-B49C-DD7FC6559594}") JPluginStubClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{243F5981-F358-4C6C-AB67-08F1B0C2D706}") JPluginStub  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getEmbeddedView(int NPP, Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getFullScreenView(int NPP, Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPluginStub : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPluginStubClass,_di_JPluginStub>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPluginStubClass,_di_JPluginStub> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPluginStub() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPluginStubClass,_di_JPluginStub>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPluginStub() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AD82E7AF-70FB-419E-9A3C-49E0E0D76303}") JRenderProcessGoneDetailClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JRenderProcessGoneDetail __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{7E085013-B1F9-432D-976D-E028A4941AA0}") JRenderProcessGoneDetail  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl didCrash() = 0 ;
	virtual int __cdecl rendererPriorityAtExit() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRenderProcessGoneDetail : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderProcessGoneDetailClass,_di_JRenderProcessGoneDetail>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderProcessGoneDetailClass,_di_JRenderProcessGoneDetail> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRenderProcessGoneDetail() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderProcessGoneDetailClass,_di_JRenderProcessGoneDetail>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRenderProcessGoneDetail() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3CD102BA-6EE3-4495-A3B4-BF779AD47B44}") JServiceWorkerClientClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JServiceWorkerClient __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{7D0D0BCD-CDAC-4D10-B5F3-B8F689611753}") JServiceWorkerClient  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JWebResourceResponse __cdecl shouldInterceptRequest(_di_JWebResourceRequest request) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJServiceWorkerClient : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceWorkerClientClass,_di_JServiceWorkerClient>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceWorkerClientClass,_di_JServiceWorkerClient> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJServiceWorkerClient() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceWorkerClientClass,_di_JServiceWorkerClient>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJServiceWorkerClient() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4CA0F16A-85E7-4211-9861-4D8B7CF4CD88}") JServiceWorkerControllerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JServiceWorkerController __cdecl init() = 0 ;
	virtual _di_JServiceWorkerController __cdecl getInstance() = 0 ;
};

__interface  INTERFACE_UUID("{E462448D-9665-481D-8E58-B8EB3A4C0B8D}") JServiceWorkerController  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JServiceWorkerWebSettings __cdecl getServiceWorkerWebSettings() = 0 ;
	virtual void __cdecl setServiceWorkerClient(_di_JServiceWorkerClient client) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJServiceWorkerController : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceWorkerControllerClass,_di_JServiceWorkerController>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceWorkerControllerClass,_di_JServiceWorkerController> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJServiceWorkerController() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceWorkerControllerClass,_di_JServiceWorkerController>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJServiceWorkerController() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{175D6281-AE76-4F25-9C91-8913A9570B39}") JServiceWorkerWebSettingsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JServiceWorkerWebSettings __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{87A253E0-8EBE-4F48-88C1-B72620311EFB}") JServiceWorkerWebSettings  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl getAllowContentAccess() = 0 ;
	virtual bool __cdecl getAllowFileAccess() = 0 ;
	virtual bool __cdecl getBlockNetworkLoads() = 0 ;
	virtual int __cdecl getCacheMode() = 0 ;
	virtual void __cdecl setAllowContentAccess(bool allow) = 0 ;
	virtual void __cdecl setAllowFileAccess(bool allow) = 0 ;
	virtual void __cdecl setBlockNetworkLoads(bool flag) = 0 ;
	virtual void __cdecl setCacheMode(int mode) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJServiceWorkerWebSettings : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceWorkerWebSettingsClass,_di_JServiceWorkerWebSettings>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceWorkerWebSettingsClass,_di_JServiceWorkerWebSettings> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJServiceWorkerWebSettings() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceWorkerWebSettingsClass,_di_JServiceWorkerWebSettings>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJServiceWorkerWebSettings() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9C90D0D5-1B1D-4969-979F-CA60801EE6BD}") JSslErrorHandlerClass  : public Androidapi::Jni::Os::JHandlerClass 
{
	
};

__interface  INTERFACE_UUID("{03C0743D-557A-4B5D-942C-8C2B15F645C3}") JSslErrorHandler  : public Androidapi::Jni::Os::JHandler 
{
	virtual void __cdecl cancel() = 0 ;
	virtual void __cdecl proceed() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSslErrorHandler : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSslErrorHandlerClass,_di_JSslErrorHandler>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSslErrorHandlerClass,_di_JSslErrorHandler> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSslErrorHandler() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSslErrorHandlerClass,_di_JSslErrorHandler>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSslErrorHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F338F90A-949B-4324-ABB8-FEAE849ED7C9}") JURLUtilClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JURLUtil __cdecl init() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl composeSearchUrl(Androidapi::Jni::Javatypes::_di_JString inQuery, Androidapi::Jni::Javatypes::_di_JString Template, Androidapi::Jni::Javatypes::_di_JString queryPlaceHolder) = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl decode(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* url) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl guessFileName(Androidapi::Jni::Javatypes::_di_JString url, Androidapi::Jni::Javatypes::_di_JString contentDisposition, Androidapi::Jni::Javatypes::_di_JString mimeType) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl guessUrl(Androidapi::Jni::Javatypes::_di_JString inUrl) = 0 ;
	virtual bool __cdecl isAboutUrl(Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual bool __cdecl isAssetUrl(Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual bool __cdecl isContentUrl(Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual bool __cdecl isCookielessProxyUrl(Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual bool __cdecl isDataUrl(Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual bool __cdecl isFileUrl(Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual bool __cdecl isHttpUrl(Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual bool __cdecl isHttpsUrl(Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual bool __cdecl isJavaScriptUrl(Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual bool __cdecl isNetworkUrl(Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual bool __cdecl isValidUrl(Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl stripAnchor(Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
};

__interface  INTERFACE_UUID("{C40526A5-9EB7-414D-90AC-36D4F2B55993}") JURLUtil  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJURLUtil : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURLUtilClass,_di_JURLUtil>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURLUtilClass,_di_JURLUtil> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJURLUtil() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURLUtilClass,_di_JURLUtil>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJURLUtil() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5CE4D0B0-6C4F-43BD-B57F-A06401A5FB2F}") JValueCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{3B24779A-3678-4AD8-B421-A8A9C6F3E742}") JValueCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onReceiveValue(Androidapi::Jni::Javatypes::_di_JObject value) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJValueCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JValueCallbackClass,_di_JValueCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JValueCallbackClass,_di_JValueCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJValueCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JValueCallbackClass,_di_JValueCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJValueCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A07CD657-C6A4-4BB3-9DE1-5FAD34D2FAB3}") JWebBackForwardListClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JWebBackForwardList __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{CA2E0F5D-8FD8-4DDC-BDB4-73EB780AE1B9}") JWebBackForwardList  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl getCurrentIndex() = 0 ;
	virtual _di_JWebHistoryItem __cdecl getCurrentItem() = 0 ;
	virtual _di_JWebHistoryItem __cdecl getItemAtIndex(int index) = 0 ;
	virtual int __cdecl getSize() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebBackForwardList : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebBackForwardListClass,_di_JWebBackForwardList>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebBackForwardListClass,_di_JWebBackForwardList> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebBackForwardList() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebBackForwardListClass,_di_JWebBackForwardList>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebBackForwardList() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0DEC9AF7-FCC8-4616-86FD-4974D4FCB026}") JWebChromeClientClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JWebChromeClient __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{B8E15ECA-8A1A-4321-8E4D-5881F6D8F9EF}") JWebChromeClient  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap __cdecl getDefaultVideoPoster() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getVideoLoadingProgressView() = 0 ;
	virtual void __cdecl getVisitedHistory(Androidapi::Jnibridge::TJavaObjectArray__1<_di_JValueCallback>* callback) = 0 ;
	virtual void __cdecl onCloseWindow(_di_JWebView window) = 0 ;
	virtual void __cdecl onConsoleMessage(Androidapi::Jni::Javatypes::_di_JString message, int lineNumber, Androidapi::Jni::Javatypes::_di_JString sourceID) = 0 /* overload */;
	virtual bool __cdecl onConsoleMessage(_di_JConsoleMessage consoleMessage) = 0 /* overload */;
	virtual bool __cdecl onCreateWindow(_di_JWebView view, bool isDialog, bool isUserGesture, Androidapi::Jni::Os::_di_JMessage resultMsg) = 0 ;
	virtual void __cdecl onExceededDatabaseQuota(Androidapi::Jni::Javatypes::_di_JString url, Androidapi::Jni::Javatypes::_di_JString databaseIdentifier, __int64 quota, __int64 estimatedDatabaseSize, __int64 totalQuota, _di_JWebStorage_QuotaUpdater quotaUpdater) = 0 ;
	virtual void __cdecl onGeolocationPermissionsHidePrompt() = 0 ;
	virtual void __cdecl onGeolocationPermissionsShowPrompt(Androidapi::Jni::Javatypes::_di_JString origin, _di_JGeolocationPermissions_Callback callback) = 0 ;
	virtual void __cdecl onHideCustomView() = 0 ;
	virtual bool __cdecl onJsAlert(_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url, Androidapi::Jni::Javatypes::_di_JString message, _di_JJsResult result) = 0 ;
	virtual bool __cdecl onJsBeforeUnload(_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url, Androidapi::Jni::Javatypes::_di_JString message, _di_JJsResult result) = 0 ;
	virtual bool __cdecl onJsConfirm(_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url, Androidapi::Jni::Javatypes::_di_JString message, _di_JJsResult result) = 0 ;
	virtual bool __cdecl onJsPrompt(_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url, Androidapi::Jni::Javatypes::_di_JString message, Androidapi::Jni::Javatypes::_di_JString defaultValue, _di_JJsPromptResult result) = 0 ;
	virtual bool __cdecl onJsTimeout() = 0 ;
	virtual void __cdecl onPermissionRequest(_di_JPermissionRequest request) = 0 ;
	virtual void __cdecl onPermissionRequestCanceled(_di_JPermissionRequest request) = 0 ;
	virtual void __cdecl onProgressChanged(_di_JWebView view, int newProgress) = 0 ;
	virtual void __cdecl onReachedMaxAppCacheSize(__int64 requiredStorage, __int64 quota, _di_JWebStorage_QuotaUpdater quotaUpdater) = 0 ;
	virtual void __cdecl onReceivedIcon(_di_JWebView view, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap icon) = 0 ;
	virtual void __cdecl onReceivedTitle(_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString title) = 0 ;
	virtual void __cdecl onReceivedTouchIconUrl(_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url, bool precomposed) = 0 ;
	virtual void __cdecl onRequestFocus(_di_JWebView view) = 0 ;
	virtual void __cdecl onShowCustomView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, _di_JWebChromeClient_CustomViewCallback callback) = 0 /* overload */;
	virtual void __cdecl onShowCustomView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, int requestedOrientation, _di_JWebChromeClient_CustomViewCallback callback) = 0 /* overload */;
	virtual bool __cdecl onShowFileChooser(_di_JWebView webView, Androidapi::Jnibridge::TJavaObjectArray__1<_di_JValueCallback>* filePathCallback, _di_JWebChromeClient_FileChooserParams fileChooserParams) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebChromeClient : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebChromeClientClass,_di_JWebChromeClient>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebChromeClientClass,_di_JWebChromeClient> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebChromeClient() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebChromeClientClass,_di_JWebChromeClient>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebChromeClient() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4B9AF0A9-F503-4054-B3BF-498AD5CD50F8}") JWebChromeClient_CustomViewCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{2C042439-AB81-4675-9E99-CA4E3C8D84E1}") JWebChromeClient_CustomViewCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCustomViewHidden() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebChromeClient_CustomViewCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebChromeClient_CustomViewCallbackClass,_di_JWebChromeClient_CustomViewCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebChromeClient_CustomViewCallbackClass,_di_JWebChromeClient_CustomViewCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebChromeClient_CustomViewCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebChromeClient_CustomViewCallbackClass,_di_JWebChromeClient_CustomViewCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebChromeClient_CustomViewCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{58CF8E81-BB27-4084-9AFA-3186883B7E1C}") JWebChromeClient_FileChooserParamsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetMODE_OPEN() = 0 ;
	virtual int __cdecl _GetMODE_OPEN_MULTIPLE() = 0 ;
	virtual int __cdecl _GetMODE_SAVE() = 0 ;
	HIDESBASE virtual _di_JWebChromeClient_FileChooserParams __cdecl init() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Net::_di_Jnet_Uri>* __cdecl parseResult(int resultCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent data) = 0 ;
	__property int MODE_OPEN = {read=_GetMODE_OPEN};
	__property int MODE_OPEN_MULTIPLE = {read=_GetMODE_OPEN_MULTIPLE};
	__property int MODE_SAVE = {read=_GetMODE_SAVE};
};

__interface  INTERFACE_UUID("{9D8E1736-3779-4E8A-BCCD-95DC4E1F5BF9}") JWebChromeClient_FileChooserParams  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JIntent __cdecl createIntent() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getAcceptTypes() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getFilenameHint() = 0 ;
	virtual int __cdecl getMode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getTitle() = 0 ;
	virtual bool __cdecl isCaptureEnabled() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebChromeClient_FileChooserParams : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebChromeClient_FileChooserParamsClass,_di_JWebChromeClient_FileChooserParams>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebChromeClient_FileChooserParamsClass,_di_JWebChromeClient_FileChooserParams> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebChromeClient_FileChooserParams() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebChromeClient_FileChooserParamsClass,_di_JWebChromeClient_FileChooserParams>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebChromeClient_FileChooserParams() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{58FE1F44-7620-49B7-BA50-CF97126D6C75}") JWebHistoryItemClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JWebHistoryItem __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{B4724762-EFAC-4E05-962A-0D3E7684730D}") JWebHistoryItem  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap __cdecl getFavicon() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getOriginalUrl() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getTitle() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getUrl() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebHistoryItem : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebHistoryItemClass,_di_JWebHistoryItem>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebHistoryItemClass,_di_JWebHistoryItem> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebHistoryItem() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebHistoryItemClass,_di_JWebHistoryItem>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebHistoryItem() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1D432D65-2ABB-4EFD-A989-7D0DF89F8868}") JWebIconDatabaseClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JWebIconDatabase __cdecl init() = 0 ;
	virtual _di_JWebIconDatabase __cdecl getInstance() = 0 ;
};

__interface  INTERFACE_UUID("{C036A43D-DD31-4FFF-8CAD-0ED5844378B6}") JWebIconDatabase  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl close() = 0 ;
	virtual void __cdecl open(Androidapi::Jni::Javatypes::_di_JString path) = 0 ;
	virtual void __cdecl releaseIconForPageUrl(Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual void __cdecl removeAllIcons() = 0 ;
	virtual void __cdecl requestIconForPageUrl(Androidapi::Jni::Javatypes::_di_JString url, _di_JWebIconDatabase_IconListener listener) = 0 ;
	virtual void __cdecl retainIconForPageUrl(Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebIconDatabase : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebIconDatabaseClass,_di_JWebIconDatabase>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebIconDatabaseClass,_di_JWebIconDatabase> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebIconDatabase() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebIconDatabaseClass,_di_JWebIconDatabase>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebIconDatabase() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9C2AE70A-59E2-4133-9A2D-794B6288C89F}") JWebIconDatabase_IconListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{9030BE72-BB1D-4A40-A452-7133B9C166B3}") JWebIconDatabase_IconListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onReceivedIcon(Androidapi::Jni::Javatypes::_di_JString url, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap icon) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebIconDatabase_IconListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebIconDatabase_IconListenerClass,_di_JWebIconDatabase_IconListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebIconDatabase_IconListenerClass,_di_JWebIconDatabase_IconListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebIconDatabase_IconListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebIconDatabase_IconListenerClass,_di_JWebIconDatabase_IconListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebIconDatabase_IconListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3E4E6BEF-5261-4B5F-9EA5-61622B9C60BD}") JWebMessageClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JWebMessage __cdecl init(Androidapi::Jni::Javatypes::_di_JString data) = 0 /* overload */;
	HIDESBASE virtual _di_JWebMessage __cdecl init(Androidapi::Jni::Javatypes::_di_JString data, Androidapi::Jnibridge::TJavaObjectArray__1<_di_JWebMessagePort>* ports) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{3BAE79BA-181D-4C03-812C-593313A52FE8}") JWebMessage  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getData() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JWebMessagePort>* __cdecl getPorts() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebMessage : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebMessageClass,_di_JWebMessage>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebMessageClass,_di_JWebMessage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebMessage() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebMessageClass,_di_JWebMessage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D2AD0E95-15FA-41AA-A49B-B0DEDB614602}") JWebMessagePortClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{040782A9-B4B1-47EC-84DB-2AC7870E8732}") JWebMessagePort  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl close() = 0 ;
	virtual void __cdecl postMessage(_di_JWebMessage message) = 0 ;
	virtual void __cdecl setWebMessageCallback(_di_JWebMessagePort_WebMessageCallback callback) = 0 /* overload */;
	virtual void __cdecl setWebMessageCallback(_di_JWebMessagePort_WebMessageCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebMessagePort : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebMessagePortClass,_di_JWebMessagePort>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebMessagePortClass,_di_JWebMessagePort> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebMessagePort() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebMessagePortClass,_di_JWebMessagePort>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebMessagePort() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F92724EB-BD77-4105-A1D5-93D9F79C8D61}") JWebMessagePort_WebMessageCallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JWebMessagePort_WebMessageCallback __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{17D28349-57BE-454E-AF4D-224BB847D4B9}") JWebMessagePort_WebMessageCallback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onMessage(_di_JWebMessagePort port, _di_JWebMessage message) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebMessagePort_WebMessageCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebMessagePort_WebMessageCallbackClass,_di_JWebMessagePort_WebMessageCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebMessagePort_WebMessageCallbackClass,_di_JWebMessagePort_WebMessageCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebMessagePort_WebMessageCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebMessagePort_WebMessageCallbackClass,_di_JWebMessagePort_WebMessageCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebMessagePort_WebMessageCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A29C41A0-DDFC-4182-8F0C-70C7E9AA377B}") JWebResourceErrorClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{788DAB8E-BE04-409E-9202-10DCF4C3EE5C}") JWebResourceError  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getDescription() = 0 ;
	virtual int __cdecl getErrorCode() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebResourceError : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebResourceErrorClass,_di_JWebResourceError>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebResourceErrorClass,_di_JWebResourceError> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebResourceError() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebResourceErrorClass,_di_JWebResourceError>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebResourceError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{227EDBE7-EF39-48FF-AEB3-858336A022E0}") JWebResourceRequestClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{59DD3D63-E2EA-483E-BC4B-2A8FCB84DA47}") JWebResourceRequest  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMethod() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl getRequestHeaders() = 0 ;
	virtual Androidapi::Jni::Net::_di_Jnet_Uri __cdecl getUrl() = 0 ;
	virtual bool __cdecl hasGesture() = 0 ;
	virtual bool __cdecl isForMainFrame() = 0 ;
	virtual bool __cdecl isRedirect() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebResourceRequest : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebResourceRequestClass,_di_JWebResourceRequest>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebResourceRequestClass,_di_JWebResourceRequest> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebResourceRequest() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebResourceRequestClass,_di_JWebResourceRequest>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebResourceRequest() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E3E5D0F5-A281-4D60-8941-A07A10D9151E}") JWebResourceResponseClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JWebResourceResponse __cdecl init(Androidapi::Jni::Javatypes::_di_JString mimeType, Androidapi::Jni::Javatypes::_di_JString encoding, Androidapi::Jni::Javatypes::_di_JInputStream data) = 0 /* overload */;
	HIDESBASE virtual _di_JWebResourceResponse __cdecl init(Androidapi::Jni::Javatypes::_di_JString mimeType, Androidapi::Jni::Javatypes::_di_JString encoding, int statusCode, Androidapi::Jni::Javatypes::_di_JString reasonPhrase, Androidapi::Jni::Javatypes::_di_JMap responseHeaders, Androidapi::Jni::Javatypes::_di_JInputStream data) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{00365ED2-0D7C-4CF5-99AB-D8057E8322F2}") JWebResourceResponse  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JInputStream __cdecl getData() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getEncoding() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMimeType() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getReasonPhrase() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl getResponseHeaders() = 0 ;
	virtual int __cdecl getStatusCode() = 0 ;
	virtual void __cdecl setData(Androidapi::Jni::Javatypes::_di_JInputStream data) = 0 ;
	virtual void __cdecl setEncoding(Androidapi::Jni::Javatypes::_di_JString encoding) = 0 ;
	virtual void __cdecl setMimeType(Androidapi::Jni::Javatypes::_di_JString mimeType) = 0 ;
	virtual void __cdecl setResponseHeaders(Androidapi::Jni::Javatypes::_di_JMap headers) = 0 ;
	virtual void __cdecl setStatusCodeAndReasonPhrase(int statusCode, Androidapi::Jni::Javatypes::_di_JString reasonPhrase) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebResourceResponse : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebResourceResponseClass,_di_JWebResourceResponse>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebResourceResponseClass,_di_JWebResourceResponse> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebResourceResponse() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebResourceResponseClass,_di_JWebResourceResponse>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebResourceResponse() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{602E6B04-981D-4A05-BA19-6ED02ADF24CA}") JWebSettingsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetLOAD_CACHE_ELSE_NETWORK() = 0 ;
	virtual int __cdecl _GetLOAD_CACHE_ONLY() = 0 ;
	virtual int __cdecl _GetLOAD_DEFAULT() = 0 ;
	virtual int __cdecl _GetLOAD_NORMAL() = 0 ;
	virtual int __cdecl _GetLOAD_NO_CACHE() = 0 ;
	virtual int __cdecl _GetMENU_ITEM_NONE() = 0 ;
	virtual int __cdecl _GetMENU_ITEM_PROCESS_TEXT() = 0 ;
	virtual int __cdecl _GetMENU_ITEM_SHARE() = 0 ;
	virtual int __cdecl _GetMENU_ITEM_WEB_SEARCH() = 0 ;
	virtual int __cdecl _GetMIXED_CONTENT_ALWAYS_ALLOW() = 0 ;
	virtual int __cdecl _GetMIXED_CONTENT_COMPATIBILITY_MODE() = 0 ;
	virtual int __cdecl _GetMIXED_CONTENT_NEVER_ALLOW() = 0 ;
	HIDESBASE virtual _di_JWebSettings __cdecl init() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDefaultUserAgent(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	__property int LOAD_CACHE_ELSE_NETWORK = {read=_GetLOAD_CACHE_ELSE_NETWORK};
	__property int LOAD_CACHE_ONLY = {read=_GetLOAD_CACHE_ONLY};
	__property int LOAD_DEFAULT = {read=_GetLOAD_DEFAULT};
	__property int LOAD_NORMAL = {read=_GetLOAD_NORMAL};
	__property int LOAD_NO_CACHE = {read=_GetLOAD_NO_CACHE};
	__property int MENU_ITEM_NONE = {read=_GetMENU_ITEM_NONE};
	__property int MENU_ITEM_PROCESS_TEXT = {read=_GetMENU_ITEM_PROCESS_TEXT};
	__property int MENU_ITEM_SHARE = {read=_GetMENU_ITEM_SHARE};
	__property int MENU_ITEM_WEB_SEARCH = {read=_GetMENU_ITEM_WEB_SEARCH};
	__property int MIXED_CONTENT_ALWAYS_ALLOW = {read=_GetMIXED_CONTENT_ALWAYS_ALLOW};
	__property int MIXED_CONTENT_COMPATIBILITY_MODE = {read=_GetMIXED_CONTENT_COMPATIBILITY_MODE};
	__property int MIXED_CONTENT_NEVER_ALLOW = {read=_GetMIXED_CONTENT_NEVER_ALLOW};
};

__interface  INTERFACE_UUID("{6F9320FD-C646-45CB-90A3-7985E5A1BAE8}") JWebSettings  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl enableSmoothTransition() = 0 ;
	virtual bool __cdecl getAllowContentAccess() = 0 ;
	virtual bool __cdecl getAllowFileAccess() = 0 ;
	virtual bool __cdecl getAllowFileAccessFromFileURLs() = 0 ;
	virtual bool __cdecl getAllowUniversalAccessFromFileURLs() = 0 ;
	virtual bool __cdecl getBlockNetworkImage() = 0 ;
	virtual bool __cdecl getBlockNetworkLoads() = 0 ;
	virtual bool __cdecl getBuiltInZoomControls() = 0 ;
	virtual int __cdecl getCacheMode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getCursiveFontFamily() = 0 ;
	virtual bool __cdecl getDatabaseEnabled() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDatabasePath() = 0 ;
	virtual int __cdecl getDefaultFixedFontSize() = 0 ;
	virtual int __cdecl getDefaultFontSize() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDefaultTextEncodingName() = 0 ;
	virtual _di_JWebSettings_ZoomDensity __cdecl getDefaultZoom() = 0 ;
	virtual int __cdecl getDisabledActionModeMenuItems() = 0 ;
	virtual bool __cdecl getDisplayZoomControls() = 0 ;
	virtual bool __cdecl getDomStorageEnabled() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getFantasyFontFamily() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getFixedFontFamily() = 0 ;
	virtual bool __cdecl getJavaScriptCanOpenWindowsAutomatically() = 0 ;
	virtual bool __cdecl getJavaScriptEnabled() = 0 ;
	virtual _di_JWebSettings_LayoutAlgorithm __cdecl getLayoutAlgorithm() = 0 ;
	virtual bool __cdecl getLightTouchEnabled() = 0 ;
	virtual bool __cdecl getLoadWithOverviewMode() = 0 ;
	virtual bool __cdecl getLoadsImagesAutomatically() = 0 ;
	virtual bool __cdecl getMediaPlaybackRequiresUserGesture() = 0 ;
	virtual int __cdecl getMinimumFontSize() = 0 ;
	virtual int __cdecl getMinimumLogicalFontSize() = 0 ;
	virtual int __cdecl getMixedContentMode() = 0 ;
	virtual bool __cdecl getOffscreenPreRaster() = 0 ;
	virtual _di_JWebSettings_PluginState __cdecl getPluginState() = 0 ;
	virtual bool __cdecl getSafeBrowsingEnabled() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSansSerifFontFamily() = 0 ;
	virtual bool __cdecl getSaveFormData() = 0 ;
	virtual bool __cdecl getSavePassword() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSerifFontFamily() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getStandardFontFamily() = 0 ;
	virtual _di_JWebSettings_TextSize __cdecl getTextSize() = 0 ;
	virtual int __cdecl getTextZoom() = 0 ;
	virtual bool __cdecl getUseWideViewPort() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getUserAgentString() = 0 ;
	virtual void __cdecl setAllowContentAccess(bool allow) = 0 ;
	virtual void __cdecl setAllowFileAccess(bool allow) = 0 ;
	virtual void __cdecl setAllowFileAccessFromFileURLs(bool flag) = 0 ;
	virtual void __cdecl setAllowUniversalAccessFromFileURLs(bool flag) = 0 ;
	virtual void __cdecl setAppCacheEnabled(bool flag) = 0 ;
	virtual void __cdecl setAppCacheMaxSize(__int64 appCacheMaxSize) = 0 ;
	virtual void __cdecl setAppCachePath(Androidapi::Jni::Javatypes::_di_JString appCachePath) = 0 ;
	virtual void __cdecl setBlockNetworkImage(bool flag) = 0 ;
	virtual void __cdecl setBlockNetworkLoads(bool flag) = 0 ;
	virtual void __cdecl setBuiltInZoomControls(bool enabled) = 0 ;
	virtual void __cdecl setCacheMode(int mode) = 0 ;
	virtual void __cdecl setCursiveFontFamily(Androidapi::Jni::Javatypes::_di_JString font) = 0 ;
	virtual void __cdecl setDatabaseEnabled(bool flag) = 0 ;
	virtual void __cdecl setDatabasePath(Androidapi::Jni::Javatypes::_di_JString databasePath) = 0 ;
	virtual void __cdecl setDefaultFixedFontSize(int size) = 0 ;
	virtual void __cdecl setDefaultFontSize(int size) = 0 ;
	virtual void __cdecl setDefaultTextEncodingName(Androidapi::Jni::Javatypes::_di_JString encoding) = 0 ;
	virtual void __cdecl setDefaultZoom(_di_JWebSettings_ZoomDensity zoom) = 0 ;
	virtual void __cdecl setDisabledActionModeMenuItems(int menuItems) = 0 ;
	virtual void __cdecl setDisplayZoomControls(bool enabled) = 0 ;
	virtual void __cdecl setDomStorageEnabled(bool flag) = 0 ;
	virtual void __cdecl setEnableSmoothTransition(bool enable) = 0 ;
	virtual void __cdecl setFantasyFontFamily(Androidapi::Jni::Javatypes::_di_JString font) = 0 ;
	virtual void __cdecl setFixedFontFamily(Androidapi::Jni::Javatypes::_di_JString font) = 0 ;
	virtual void __cdecl setGeolocationDatabasePath(Androidapi::Jni::Javatypes::_di_JString databasePath) = 0 ;
	virtual void __cdecl setGeolocationEnabled(bool flag) = 0 ;
	virtual void __cdecl setJavaScriptCanOpenWindowsAutomatically(bool flag) = 0 ;
	virtual void __cdecl setJavaScriptEnabled(bool flag) = 0 ;
	virtual void __cdecl setLayoutAlgorithm(_di_JWebSettings_LayoutAlgorithm l) = 0 ;
	virtual void __cdecl setLightTouchEnabled(bool enabled) = 0 ;
	virtual void __cdecl setLoadWithOverviewMode(bool overview) = 0 ;
	virtual void __cdecl setLoadsImagesAutomatically(bool flag) = 0 ;
	virtual void __cdecl setMediaPlaybackRequiresUserGesture(bool require) = 0 ;
	virtual void __cdecl setMinimumFontSize(int size) = 0 ;
	virtual void __cdecl setMinimumLogicalFontSize(int size) = 0 ;
	virtual void __cdecl setMixedContentMode(int mode) = 0 ;
	virtual void __cdecl setNeedInitialFocus(bool flag) = 0 ;
	virtual void __cdecl setOffscreenPreRaster(bool enabled) = 0 ;
	virtual void __cdecl setPluginState(_di_JWebSettings_PluginState state) = 0 ;
	virtual void __cdecl setRenderPriority(_di_JWebSettings_RenderPriority priority) = 0 ;
	virtual void __cdecl setSafeBrowsingEnabled(bool enabled) = 0 ;
	virtual void __cdecl setSansSerifFontFamily(Androidapi::Jni::Javatypes::_di_JString font) = 0 ;
	virtual void __cdecl setSaveFormData(bool save) = 0 ;
	virtual void __cdecl setSavePassword(bool save) = 0 ;
	virtual void __cdecl setSerifFontFamily(Androidapi::Jni::Javatypes::_di_JString font) = 0 ;
	virtual void __cdecl setStandardFontFamily(Androidapi::Jni::Javatypes::_di_JString font) = 0 ;
	virtual void __cdecl setSupportMultipleWindows(bool support) = 0 ;
	virtual void __cdecl setSupportZoom(bool support) = 0 ;
	virtual void __cdecl setTextSize(_di_JWebSettings_TextSize t) = 0 ;
	virtual void __cdecl setTextZoom(int textZoom) = 0 ;
	virtual void __cdecl setUseWideViewPort(bool use) = 0 ;
	virtual void __cdecl setUserAgentString(Androidapi::Jni::Javatypes::_di_JString ua) = 0 ;
	virtual bool __cdecl supportMultipleWindows() = 0 ;
	virtual bool __cdecl supportZoom() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebSettings : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettingsClass,_di_JWebSettings>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettingsClass,_di_JWebSettings> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebSettings() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettingsClass,_di_JWebSettings>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebSettings() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6D48AC59-3F0B-4CE1-B9E3-C7A0894915A2}") JWebSettings_LayoutAlgorithmClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JWebSettings_LayoutAlgorithm __cdecl _GetNARROW_COLUMNS() = 0 ;
	virtual _di_JWebSettings_LayoutAlgorithm __cdecl _GetNORMAL() = 0 ;
	virtual _di_JWebSettings_LayoutAlgorithm __cdecl _GetSINGLE_COLUMN() = 0 ;
	virtual _di_JWebSettings_LayoutAlgorithm __cdecl _GetTEXT_AUTOSIZING() = 0 ;
	HIDESBASE virtual _di_JWebSettings_LayoutAlgorithm __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JWebSettings_LayoutAlgorithm>* __cdecl values() = 0 ;
	__property _di_JWebSettings_LayoutAlgorithm NARROW_COLUMNS = {read=_GetNARROW_COLUMNS};
	__property _di_JWebSettings_LayoutAlgorithm NORMAL = {read=_GetNORMAL};
	__property _di_JWebSettings_LayoutAlgorithm SINGLE_COLUMN = {read=_GetSINGLE_COLUMN};
	__property _di_JWebSettings_LayoutAlgorithm TEXT_AUTOSIZING = {read=_GetTEXT_AUTOSIZING};
};

__interface  INTERFACE_UUID("{907CB7D6-3ECB-449F-9BE5-D3E4FAF0A877}") JWebSettings_LayoutAlgorithm  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebSettings_LayoutAlgorithm : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettings_LayoutAlgorithmClass,_di_JWebSettings_LayoutAlgorithm>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettings_LayoutAlgorithmClass,_di_JWebSettings_LayoutAlgorithm> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebSettings_LayoutAlgorithm() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettings_LayoutAlgorithmClass,_di_JWebSettings_LayoutAlgorithm>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebSettings_LayoutAlgorithm() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3EEEE1A8-1A1C-4273-8FDA-795F1EC37C77}") JWebSettings_PluginStateClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JWebSettings_PluginState __cdecl _GetOFF() = 0 ;
	virtual _di_JWebSettings_PluginState __cdecl _GetON() = 0 ;
	virtual _di_JWebSettings_PluginState __cdecl _GetON_DEMAND() = 0 ;
	HIDESBASE virtual _di_JWebSettings_PluginState __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JWebSettings_PluginState>* __cdecl values() = 0 ;
	__property _di_JWebSettings_PluginState OFF = {read=_GetOFF};
	__property _di_JWebSettings_PluginState ON = {read=_GetON};
	__property _di_JWebSettings_PluginState ON_DEMAND = {read=_GetON_DEMAND};
};

__interface  INTERFACE_UUID("{9E1FE39E-6E4B-41B5-A4F5-117A32289576}") JWebSettings_PluginState  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebSettings_PluginState : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettings_PluginStateClass,_di_JWebSettings_PluginState>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettings_PluginStateClass,_di_JWebSettings_PluginState> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebSettings_PluginState() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettings_PluginStateClass,_di_JWebSettings_PluginState>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebSettings_PluginState() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{ABDCE7A7-56D3-4DAE-BD5E-6D8F882C652F}") JWebSettings_RenderPriorityClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JWebSettings_RenderPriority __cdecl _GetHIGH() = 0 ;
	virtual _di_JWebSettings_RenderPriority __cdecl _GetLOW() = 0 ;
	virtual _di_JWebSettings_RenderPriority __cdecl _GetNORMAL() = 0 ;
	HIDESBASE virtual _di_JWebSettings_RenderPriority __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JWebSettings_RenderPriority>* __cdecl values() = 0 ;
	__property _di_JWebSettings_RenderPriority HIGH = {read=_GetHIGH};
	__property _di_JWebSettings_RenderPriority LOW = {read=_GetLOW};
	__property _di_JWebSettings_RenderPriority NORMAL = {read=_GetNORMAL};
};

__interface  INTERFACE_UUID("{00AA47AC-5C9B-4C40-9266-3DCCDB4E849B}") JWebSettings_RenderPriority  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebSettings_RenderPriority : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettings_RenderPriorityClass,_di_JWebSettings_RenderPriority>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettings_RenderPriorityClass,_di_JWebSettings_RenderPriority> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebSettings_RenderPriority() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettings_RenderPriorityClass,_di_JWebSettings_RenderPriority>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebSettings_RenderPriority() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{ED845FF6-09FA-41C4-B3CD-81718A39E35D}") JWebSettings_TextSizeClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JWebSettings_TextSize __cdecl _GetLARGER() = 0 ;
	virtual _di_JWebSettings_TextSize __cdecl _GetLARGEST() = 0 ;
	virtual _di_JWebSettings_TextSize __cdecl _GetNORMAL() = 0 ;
	virtual _di_JWebSettings_TextSize __cdecl _GetSMALLER() = 0 ;
	virtual _di_JWebSettings_TextSize __cdecl _GetSMALLEST() = 0 ;
	HIDESBASE virtual _di_JWebSettings_TextSize __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JWebSettings_TextSize>* __cdecl values() = 0 ;
	__property _di_JWebSettings_TextSize LARGER = {read=_GetLARGER};
	__property _di_JWebSettings_TextSize LARGEST = {read=_GetLARGEST};
	__property _di_JWebSettings_TextSize NORMAL = {read=_GetNORMAL};
	__property _di_JWebSettings_TextSize SMALLER = {read=_GetSMALLER};
	__property _di_JWebSettings_TextSize SMALLEST = {read=_GetSMALLEST};
};

__interface  INTERFACE_UUID("{416C0F01-FDDA-4159-9491-92F0241FFA7D}") JWebSettings_TextSize  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebSettings_TextSize : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettings_TextSizeClass,_di_JWebSettings_TextSize>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettings_TextSizeClass,_di_JWebSettings_TextSize> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebSettings_TextSize() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettings_TextSizeClass,_di_JWebSettings_TextSize>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebSettings_TextSize() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{CF1B1626-5547-47A4-98A4-6CCFA10457DC}") JWebSettings_ZoomDensityClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JWebSettings_ZoomDensity __cdecl _GetCLOSE() = 0 ;
	virtual _di_JWebSettings_ZoomDensity __cdecl _GetFAR() = 0 ;
	virtual _di_JWebSettings_ZoomDensity __cdecl _GetMEDIUM() = 0 ;
	HIDESBASE virtual _di_JWebSettings_ZoomDensity __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JWebSettings_ZoomDensity>* __cdecl values() = 0 ;
	__property _di_JWebSettings_ZoomDensity CLOSE = {read=_GetCLOSE};
	__property _di_JWebSettings_ZoomDensity FAR = {read=_GetFAR};
	__property _di_JWebSettings_ZoomDensity MEDIUM = {read=_GetMEDIUM};
};

__interface  INTERFACE_UUID("{99F8B33F-ADFF-4C54-9151-F0DC57EFF989}") JWebSettings_ZoomDensity  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebSettings_ZoomDensity : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettings_ZoomDensityClass,_di_JWebSettings_ZoomDensity>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettings_ZoomDensityClass,_di_JWebSettings_ZoomDensity> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebSettings_ZoomDensity() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebSettings_ZoomDensityClass,_di_JWebSettings_ZoomDensity>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebSettings_ZoomDensity() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{98C06137-20FC-44E2-B2F0-2D72D0FC3010}") JWebStorageClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JWebStorage __cdecl getInstance() = 0 ;
};

__interface  INTERFACE_UUID("{702F2A6D-0A1E-4916-B16D-8F8C492A03C5}") JWebStorage  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl deleteAllData() = 0 ;
	virtual void __cdecl deleteOrigin(Androidapi::Jni::Javatypes::_di_JString origin) = 0 ;
	virtual void __cdecl getOrigins(_di_JValueCallback callback) = 0 ;
	virtual void __cdecl getQuotaForOrigin(Androidapi::Jni::Javatypes::_di_JString origin, _di_JValueCallback callback) = 0 ;
	virtual void __cdecl getUsageForOrigin(Androidapi::Jni::Javatypes::_di_JString origin, _di_JValueCallback callback) = 0 ;
	virtual void __cdecl setQuotaForOrigin(Androidapi::Jni::Javatypes::_di_JString origin, __int64 quota) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebStorage : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebStorageClass,_di_JWebStorage>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebStorageClass,_di_JWebStorage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebStorage() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebStorageClass,_di_JWebStorage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebStorage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2EBC8D88-82DC-40C6-86D1-F5F8407B9DB1}") JWebStorage_OriginClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{EF23BA1B-CC0C-46D4-960F-DDB999281541}") JWebStorage_Origin  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getOrigin() = 0 ;
	virtual __int64 __cdecl getQuota() = 0 ;
	virtual __int64 __cdecl getUsage() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebStorage_Origin : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebStorage_OriginClass,_di_JWebStorage_Origin>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebStorage_OriginClass,_di_JWebStorage_Origin> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebStorage_Origin() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebStorage_OriginClass,_di_JWebStorage_Origin>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebStorage_Origin() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C5E7DCCF-EBD2-466F-9916-D3C4F092EA21}") JWebStorage_QuotaUpdaterClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{D6DE6F2C-845A-45FD-BC3E-10286ABF0E01}") JWebStorage_QuotaUpdater  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl updateQuota(__int64 newQuota) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebStorage_QuotaUpdater : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebStorage_QuotaUpdaterClass,_di_JWebStorage_QuotaUpdater>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebStorage_QuotaUpdaterClass,_di_JWebStorage_QuotaUpdater> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebStorage_QuotaUpdater() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebStorage_QuotaUpdaterClass,_di_JWebStorage_QuotaUpdater>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebStorage_QuotaUpdater() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{57C30F7F-F8C7-4C19-859E-073DC4DA4250}") JWebViewClass  : public Androidapi::Jni::Widget::JAbsoluteLayoutClass 
{
	virtual int __cdecl _GetRENDERER_PRIORITY_BOUND() = 0 ;
	virtual int __cdecl _GetRENDERER_PRIORITY_IMPORTANT() = 0 ;
	virtual int __cdecl _GetRENDERER_PRIORITY_WAIVED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCHEME_GEO() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCHEME_MAILTO() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCHEME_TEL() = 0 ;
	HIDESBASE virtual _di_JWebView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JWebView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JWebView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JWebView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
	HIDESBASE virtual _di_JWebView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, bool privateBrowsing) = 0 /* overload */;
	virtual void __cdecl clearClientCertPreferences(Androidapi::Jni::Javatypes::_di_JRunnable onCleared) = 0 ;
	virtual void __cdecl enableSlowWholeDocumentDraw() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl findAddress(Androidapi::Jni::Javatypes::_di_JString addr) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JPackageInfo __cdecl getCurrentWebViewPackage() = 0 ;
	virtual void __cdecl setWebContentsDebuggingEnabled(bool enabled) = 0 ;
	__property int RENDERER_PRIORITY_BOUND = {read=_GetRENDERER_PRIORITY_BOUND};
	__property int RENDERER_PRIORITY_IMPORTANT = {read=_GetRENDERER_PRIORITY_IMPORTANT};
	__property int RENDERER_PRIORITY_WAIVED = {read=_GetRENDERER_PRIORITY_WAIVED};
	__property Androidapi::Jni::Javatypes::_di_JString SCHEME_GEO = {read=_GetSCHEME_GEO};
	__property Androidapi::Jni::Javatypes::_di_JString SCHEME_MAILTO = {read=_GetSCHEME_MAILTO};
	__property Androidapi::Jni::Javatypes::_di_JString SCHEME_TEL = {read=_GetSCHEME_TEL};
};

__interface  INTERFACE_UUID("{0001776D-86A0-43B3-A64C-C6FEA095AD91}") JWebView  : public Androidapi::Jni::Widget::JAbsoluteLayout 
{
	virtual void __cdecl addJavascriptInterface(Androidapi::Jni::Javatypes::_di_JObject object_, Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	HIDESBASE virtual void __cdecl autofill(Androidapi::Jni::Util::_di_JSparseArray values) = 0 ;
	virtual bool __cdecl canGoBack() = 0 ;
	virtual bool __cdecl canGoBackOrForward(int steps) = 0 ;
	virtual bool __cdecl canGoForward() = 0 ;
	virtual bool __cdecl canZoomIn() = 0 ;
	virtual bool __cdecl canZoomOut() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JPicture __cdecl capturePicture() = 0 ;
	virtual void __cdecl clearCache(bool includeDiskFiles) = 0 ;
	virtual void __cdecl clearFormData() = 0 ;
	virtual void __cdecl clearHistory() = 0 ;
	virtual void __cdecl clearMatches() = 0 ;
	virtual void __cdecl clearSslPreferences() = 0 ;
	virtual void __cdecl clearView() = 0 ;
	HIDESBASE virtual void __cdecl computeScroll() = 0 ;
	virtual _di_JWebBackForwardList __cdecl copyBackForwardList() = 0 ;
	virtual Androidapi::Jni::Print::_di_JPrintDocumentAdapter __cdecl createPrintDocumentAdapter() = 0 /* overload */;
	virtual Androidapi::Jni::Print::_di_JPrintDocumentAdapter __cdecl createPrintDocumentAdapter(Androidapi::Jni::Javatypes::_di_JString documentName) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JWebMessagePort>* __cdecl createWebMessageChannel() = 0 ;
	virtual void __cdecl destroy() = 0 ;
	HIDESBASE virtual bool __cdecl dispatchKeyEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual void __cdecl documentHasImages(Androidapi::Jni::Os::_di_JMessage response) = 0 ;
	virtual void __cdecl evaluateJavascript(Androidapi::Jni::Javatypes::_di_JString script, _di_JValueCallback resultCallback) = 0 ;
	virtual int __cdecl findAll(Androidapi::Jni::Javatypes::_di_JString find) = 0 ;
	virtual void __cdecl findAllAsync(Androidapi::Jni::Javatypes::_di_JString find) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl findFocus() = 0 ;
	virtual void __cdecl findNext(bool forward) = 0 ;
	virtual void __cdecl flingScroll(int vx, int vy) = 0 ;
	virtual void __cdecl freeMemory() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JAccessibilityNodeProvider __cdecl getAccessibilityNodeProvider() = 0 ;
	virtual Androidapi::Jni::Net::_di_JSslCertificate __cdecl getCertificate() = 0 ;
	virtual int __cdecl getContentHeight() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap __cdecl getFavicon() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Os::_di_JHandler __cdecl getHandler() = 0 ;
	virtual _di_JWebView_HitTestResult __cdecl getHitTestResult() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getHttpAuthUsernamePassword(Androidapi::Jni::Javatypes::_di_JString host, Androidapi::Jni::Javatypes::_di_JString realm) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getOriginalUrl() = 0 ;
	virtual int __cdecl getProgress() = 0 ;
	virtual bool __cdecl getRendererPriorityWaivedWhenNotVisible() = 0 ;
	virtual int __cdecl getRendererRequestedPriority() = 0 ;
	virtual float __cdecl getScale() = 0 ;
	virtual _di_JWebSettings __cdecl getSettings() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getTitle() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getUrl() = 0 ;
	virtual _di_JWebChromeClient __cdecl getWebChromeClient() = 0 ;
	virtual _di_JWebViewClient __cdecl getWebViewClient() = 0 ;
	virtual void __cdecl goBack() = 0 ;
	virtual void __cdecl goBackOrForward(int steps) = 0 ;
	virtual void __cdecl goForward() = 0 ;
	virtual void __cdecl invokeZoomPicker() = 0 ;
	virtual bool __cdecl isPrivateBrowsingEnabled() = 0 ;
	virtual void __cdecl loadData(Androidapi::Jni::Javatypes::_di_JString data, Androidapi::Jni::Javatypes::_di_JString mimeType, Androidapi::Jni::Javatypes::_di_JString encoding) = 0 ;
	virtual void __cdecl loadDataWithBaseURL(Androidapi::Jni::Javatypes::_di_JString baseUrl, Androidapi::Jni::Javatypes::_di_JString data, Androidapi::Jni::Javatypes::_di_JString mimeType, Androidapi::Jni::Javatypes::_di_JString encoding, Androidapi::Jni::Javatypes::_di_JString historyUrl) = 0 ;
	virtual void __cdecl loadUrl(Androidapi::Jni::Javatypes::_di_JString url, Androidapi::Jni::Javatypes::_di_JMap additionalHttpHeaders) = 0 /* overload */;
	virtual void __cdecl loadUrl(Androidapi::Jni::Javatypes::_di_JString url) = 0 /* overload */;
	virtual void __cdecl onChildViewAdded(Androidapi::Jni::Graphicscontentviewtext::_di_JView parent, Androidapi::Jni::Graphicscontentviewtext::_di_JView child) = 0 ;
	virtual void __cdecl onChildViewRemoved(Androidapi::Jni::Graphicscontentviewtext::_di_JView p, Androidapi::Jni::Graphicscontentviewtext::_di_JView child) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JInputConnection __cdecl onCreateInputConnection(Androidapi::Jni::Graphicscontentviewtext::_di_JEditorInfo outAttrs) = 0 ;
	HIDESBASE virtual bool __cdecl onDragEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JDragEvent event) = 0 ;
	HIDESBASE virtual void __cdecl onFinishTemporaryDetach() = 0 ;
	HIDESBASE virtual bool __cdecl onGenericMotionEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	virtual void __cdecl onGlobalFocusChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JView oldFocus, Androidapi::Jni::Graphicscontentviewtext::_di_JView newFocus) = 0 ;
	HIDESBASE virtual bool __cdecl onHoverEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onKeyDown(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onKeyMultiple(int keyCode, int repeatCount, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onKeyUp(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual void __cdecl onPause() = 0 ;
	HIDESBASE virtual void __cdecl onProvideAutofillVirtualStructure(Androidapi::Jni::Graphicscontentviewtext::_di_JViewStructure structure, int flags) = 0 ;
	HIDESBASE virtual void __cdecl onProvideVirtualStructure(Androidapi::Jni::Graphicscontentviewtext::_di_JViewStructure structure) = 0 ;
	virtual void __cdecl onResume() = 0 ;
	HIDESBASE virtual void __cdecl onStartTemporaryDetach() = 0 ;
	HIDESBASE virtual bool __cdecl onTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onTrackballEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	HIDESBASE virtual void __cdecl onWindowFocusChanged(bool hasWindowFocus) = 0 ;
	virtual bool __cdecl overlayHorizontalScrollbar() = 0 ;
	virtual bool __cdecl overlayVerticalScrollbar() = 0 ;
	virtual bool __cdecl pageDown(bool bottom) = 0 ;
	virtual bool __cdecl pageUp(bool top) = 0 ;
	virtual void __cdecl pauseTimers() = 0 ;
	HIDESBASE virtual bool __cdecl performLongClick() = 0 ;
	virtual void __cdecl postUrl(Androidapi::Jni::Javatypes::_di_JString url, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* postData) = 0 ;
	virtual void __cdecl postVisualStateCallback(__int64 requestId, _di_JWebView_VisualStateCallback callback) = 0 ;
	virtual void __cdecl postWebMessage(_di_JWebMessage message, Androidapi::Jni::Net::_di_Jnet_Uri targetOrigin) = 0 ;
	virtual void __cdecl reload() = 0 ;
	virtual void __cdecl removeJavascriptInterface(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	HIDESBASE virtual bool __cdecl requestChildRectangleOnScreen(Androidapi::Jni::Graphicscontentviewtext::_di_JView child, Androidapi::Jni::Graphicscontentviewtext::_di_JRect rect, bool immediate) = 0 ;
	HIDESBASE virtual bool __cdecl requestFocus(int direction, Androidapi::Jni::Graphicscontentviewtext::_di_JRect previouslyFocusedRect) = 0 ;
	virtual void __cdecl requestFocusNodeHref(Androidapi::Jni::Os::_di_JMessage hrefMsg) = 0 ;
	virtual void __cdecl requestImageRef(Androidapi::Jni::Os::_di_JMessage msg) = 0 ;
	virtual _di_JWebBackForwardList __cdecl restoreState(Androidapi::Jni::Os::_di_JBundle inState) = 0 ;
	virtual void __cdecl resumeTimers() = 0 ;
	virtual void __cdecl savePassword(Androidapi::Jni::Javatypes::_di_JString host, Androidapi::Jni::Javatypes::_di_JString username, Androidapi::Jni::Javatypes::_di_JString password) = 0 ;
	virtual _di_JWebBackForwardList __cdecl saveState(Androidapi::Jni::Os::_di_JBundle outState) = 0 ;
	virtual void __cdecl saveWebArchive(Androidapi::Jni::Javatypes::_di_JString filename) = 0 /* overload */;
	virtual void __cdecl saveWebArchive(Androidapi::Jni::Javatypes::_di_JString basename, bool autoname, _di_JValueCallback callback) = 0 /* overload */;
	HIDESBASE virtual void __cdecl setBackgroundColor(int color) = 0 ;
	virtual void __cdecl setCertificate(Androidapi::Jni::Net::_di_JSslCertificate certificate) = 0 ;
	virtual void __cdecl setDownloadListener(_di_JDownloadListener listener) = 0 ;
	virtual void __cdecl setFindListener(_di_JWebView_FindListener listener) = 0 ;
	virtual void __cdecl setHorizontalScrollbarOverlay(bool overlay) = 0 ;
	virtual void __cdecl setHttpAuthUsernamePassword(Androidapi::Jni::Javatypes::_di_JString host, Androidapi::Jni::Javatypes::_di_JString realm, Androidapi::Jni::Javatypes::_di_JString username, Androidapi::Jni::Javatypes::_di_JString password) = 0 ;
	virtual void __cdecl setInitialScale(int scaleInPercent) = 0 ;
	HIDESBASE virtual void __cdecl setLayerType(int layerType, Androidapi::Jni::Graphicscontentviewtext::_di_JPaint paint) = 0 ;
	HIDESBASE virtual void __cdecl setLayoutParams(Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_LayoutParams params) = 0 ;
	virtual void __cdecl setMapTrackballToArrowKeys(bool setMap) = 0 ;
	virtual void __cdecl setNetworkAvailable(bool networkUp) = 0 ;
	HIDESBASE virtual void __cdecl setOverScrollMode(int mode) = 0 ;
	virtual void __cdecl setPictureListener(_di_JWebView_PictureListener listener) = 0 ;
	virtual void __cdecl setRendererPriorityPolicy(int rendererRequestedPriority, bool waivedWhenNotVisible) = 0 ;
	HIDESBASE virtual void __cdecl setScrollBarStyle(int style) = 0 ;
	virtual void __cdecl setVerticalScrollbarOverlay(bool overlay) = 0 ;
	virtual void __cdecl setWebChromeClient(_di_JWebChromeClient client) = 0 ;
	virtual void __cdecl setWebViewClient(_di_JWebViewClient client) = 0 ;
	HIDESBASE virtual bool __cdecl shouldDelayChildPressedState() = 0 ;
	virtual bool __cdecl showFindDialog(Androidapi::Jni::Javatypes::_di_JString text, bool showIme) = 0 ;
	virtual void __cdecl stopLoading() = 0 ;
	virtual void __cdecl zoomBy(float zoomFactor) = 0 ;
	virtual bool __cdecl zoomIn() = 0 ;
	virtual bool __cdecl zoomOut() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebViewClass,_di_JWebView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebViewClass,_di_JWebView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebViewClass,_di_JWebView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{41A75C2A-7028-4424-B3FD-A06BECE9A089}") JWebView_FindListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{4DFED237-9B2D-41ED-8DBB-A5EBF5B36A6C}") JWebView_FindListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onFindResultReceived(int activeMatchOrdinal, int numberOfMatches, bool isDoneCounting) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebView_FindListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebView_FindListenerClass,_di_JWebView_FindListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebView_FindListenerClass,_di_JWebView_FindListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebView_FindListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebView_FindListenerClass,_di_JWebView_FindListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebView_FindListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5AE29C91-64C1-4694-B2E3-A5C4077ABBA5}") JWebView_HitTestResultClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetANCHOR_TYPE() = 0 ;
	virtual int __cdecl _GetEDIT_TEXT_TYPE() = 0 ;
	virtual int __cdecl _GetEMAIL_TYPE() = 0 ;
	virtual int __cdecl _GetGEO_TYPE() = 0 ;
	virtual int __cdecl _GetIMAGE_ANCHOR_TYPE() = 0 ;
	virtual int __cdecl _GetIMAGE_TYPE() = 0 ;
	virtual int __cdecl _GetPHONE_TYPE() = 0 ;
	virtual int __cdecl _GetSRC_ANCHOR_TYPE() = 0 ;
	virtual int __cdecl _GetSRC_IMAGE_ANCHOR_TYPE() = 0 ;
	virtual int __cdecl _GetUNKNOWN_TYPE() = 0 ;
	__property int ANCHOR_TYPE = {read=_GetANCHOR_TYPE};
	__property int EDIT_TEXT_TYPE = {read=_GetEDIT_TEXT_TYPE};
	__property int EMAIL_TYPE = {read=_GetEMAIL_TYPE};
	__property int GEO_TYPE = {read=_GetGEO_TYPE};
	__property int IMAGE_ANCHOR_TYPE = {read=_GetIMAGE_ANCHOR_TYPE};
	__property int IMAGE_TYPE = {read=_GetIMAGE_TYPE};
	__property int PHONE_TYPE = {read=_GetPHONE_TYPE};
	__property int SRC_ANCHOR_TYPE = {read=_GetSRC_ANCHOR_TYPE};
	__property int SRC_IMAGE_ANCHOR_TYPE = {read=_GetSRC_IMAGE_ANCHOR_TYPE};
	__property int UNKNOWN_TYPE = {read=_GetUNKNOWN_TYPE};
};

__interface  INTERFACE_UUID("{5350D51E-FE08-48D8-A771-CA8ABEC70D95}") JWebView_HitTestResult  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getExtra() = 0 ;
	virtual int __cdecl getType() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebView_HitTestResult : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebView_HitTestResultClass,_di_JWebView_HitTestResult>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebView_HitTestResultClass,_di_JWebView_HitTestResult> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebView_HitTestResult() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebView_HitTestResultClass,_di_JWebView_HitTestResult>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebView_HitTestResult() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{126AE669-1AF8-4472-9CA6-67D139C407BD}") JWebView_PictureListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{C19F2468-28E4-4DE6-818D-BFCEFD4716E8}") JWebView_PictureListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onNewPicture(_di_JWebView view, Androidapi::Jni::Graphicscontentviewtext::_di_JPicture picture) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebView_PictureListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebView_PictureListenerClass,_di_JWebView_PictureListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebView_PictureListenerClass,_di_JWebView_PictureListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebView_PictureListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebView_PictureListenerClass,_di_JWebView_PictureListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebView_PictureListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{CCD72A26-11BC-4810-AA6B-E11AFC713AD3}") JWebView_VisualStateCallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JWebView_VisualStateCallback __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{29FF2F0D-EC40-48CC-9CDC-348B61A96CF5}") JWebView_VisualStateCallback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onComplete(__int64 requestId) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebView_VisualStateCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebView_VisualStateCallbackClass,_di_JWebView_VisualStateCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebView_VisualStateCallbackClass,_di_JWebView_VisualStateCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebView_VisualStateCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebView_VisualStateCallbackClass,_di_JWebView_VisualStateCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebView_VisualStateCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8CFEE3EF-625F-4465-8EF9-2ED5CEF3FBCB}") JWebView_WebViewTransportClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JWebView_WebViewTransport __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{4AA5F44F-DDEE-4DDB-8FAD-58C0C20F0A9B}") JWebView_WebViewTransport  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JWebView __cdecl getWebView() = 0 ;
	virtual void __cdecl setWebView(_di_JWebView webview) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebView_WebViewTransport : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebView_WebViewTransportClass,_di_JWebView_WebViewTransport>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebView_WebViewTransportClass,_di_JWebView_WebViewTransport> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebView_WebViewTransport() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebView_WebViewTransportClass,_di_JWebView_WebViewTransport>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebView_WebViewTransport() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A5B717AB-A760-4941-A8D5-5BBBB610EE9C}") JWebViewClientClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetERROR_AUTHENTICATION() = 0 ;
	virtual int __cdecl _GetERROR_BAD_URL() = 0 ;
	virtual int __cdecl _GetERROR_CONNECT() = 0 ;
	virtual int __cdecl _GetERROR_FAILED_SSL_HANDSHAKE() = 0 ;
	virtual int __cdecl _GetERROR_FILE() = 0 ;
	virtual int __cdecl _GetERROR_FILE_NOT_FOUND() = 0 ;
	virtual int __cdecl _GetERROR_HOST_LOOKUP() = 0 ;
	virtual int __cdecl _GetERROR_IO() = 0 ;
	virtual int __cdecl _GetERROR_PROXY_AUTHENTICATION() = 0 ;
	virtual int __cdecl _GetERROR_REDIRECT_LOOP() = 0 ;
	virtual int __cdecl _GetERROR_TIMEOUT() = 0 ;
	virtual int __cdecl _GetERROR_TOO_MANY_REQUESTS() = 0 ;
	virtual int __cdecl _GetERROR_UNKNOWN() = 0 ;
	virtual int __cdecl _GetERROR_UNSAFE_RESOURCE() = 0 ;
	virtual int __cdecl _GetERROR_UNSUPPORTED_AUTH_SCHEME() = 0 ;
	virtual int __cdecl _GetERROR_UNSUPPORTED_SCHEME() = 0 ;
	HIDESBASE virtual _di_JWebViewClient __cdecl init() = 0 ;
	__property int ERROR_AUTHENTICATION = {read=_GetERROR_AUTHENTICATION};
	__property int ERROR_BAD_URL = {read=_GetERROR_BAD_URL};
	__property int ERROR_CONNECT = {read=_GetERROR_CONNECT};
	__property int ERROR_FAILED_SSL_HANDSHAKE = {read=_GetERROR_FAILED_SSL_HANDSHAKE};
	__property int ERROR_FILE = {read=_GetERROR_FILE};
	__property int ERROR_FILE_NOT_FOUND = {read=_GetERROR_FILE_NOT_FOUND};
	__property int ERROR_HOST_LOOKUP = {read=_GetERROR_HOST_LOOKUP};
	__property int ERROR_IO = {read=_GetERROR_IO};
	__property int ERROR_PROXY_AUTHENTICATION = {read=_GetERROR_PROXY_AUTHENTICATION};
	__property int ERROR_REDIRECT_LOOP = {read=_GetERROR_REDIRECT_LOOP};
	__property int ERROR_TIMEOUT = {read=_GetERROR_TIMEOUT};
	__property int ERROR_TOO_MANY_REQUESTS = {read=_GetERROR_TOO_MANY_REQUESTS};
	__property int ERROR_UNKNOWN = {read=_GetERROR_UNKNOWN};
	__property int ERROR_UNSAFE_RESOURCE = {read=_GetERROR_UNSAFE_RESOURCE};
	__property int ERROR_UNSUPPORTED_AUTH_SCHEME = {read=_GetERROR_UNSUPPORTED_AUTH_SCHEME};
	__property int ERROR_UNSUPPORTED_SCHEME = {read=_GetERROR_UNSUPPORTED_SCHEME};
};

__interface  INTERFACE_UUID("{04427D5F-0978-486C-9ABC-14621B34FB9D}") JWebViewClient  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl doUpdateVisitedHistory(_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url, bool isReload) = 0 ;
	virtual void __cdecl onFormResubmission(_di_JWebView view, Androidapi::Jni::Os::_di_JMessage dontResend, Androidapi::Jni::Os::_di_JMessage resend) = 0 ;
	virtual void __cdecl onLoadResource(_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual void __cdecl onPageCommitVisible(_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual void __cdecl onPageFinished(_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual void __cdecl onPageStarted(_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap favicon) = 0 ;
	virtual void __cdecl onReceivedClientCertRequest(_di_JWebView view, _di_JClientCertRequest request) = 0 ;
	virtual void __cdecl onReceivedError(_di_JWebView view, int errorCode, Androidapi::Jni::Javatypes::_di_JString description, Androidapi::Jni::Javatypes::_di_JString failingUrl) = 0 /* overload */;
	virtual void __cdecl onReceivedError(_di_JWebView view, _di_JWebResourceRequest request, _di_JWebResourceError error) = 0 /* overload */;
	virtual void __cdecl onReceivedHttpAuthRequest(_di_JWebView view, _di_JHttpAuthHandler handler, Androidapi::Jni::Javatypes::_di_JString host, Androidapi::Jni::Javatypes::_di_JString realm) = 0 ;
	virtual void __cdecl onReceivedHttpError(_di_JWebView view, _di_JWebResourceRequest request, _di_JWebResourceResponse errorResponse) = 0 ;
	virtual void __cdecl onReceivedLoginRequest(_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString realm, Androidapi::Jni::Javatypes::_di_JString account, Androidapi::Jni::Javatypes::_di_JString args) = 0 ;
	virtual void __cdecl onReceivedSslError(_di_JWebView view, _di_JSslErrorHandler handler, Androidapi::Jni::Net::_di_JSslError error) = 0 ;
	virtual bool __cdecl onRenderProcessGone(_di_JWebView view, _di_JRenderProcessGoneDetail detail) = 0 ;
	virtual void __cdecl onScaleChanged(_di_JWebView view, float oldScale, float newScale) = 0 ;
	virtual void __cdecl onTooManyRedirects(_di_JWebView view, Androidapi::Jni::Os::_di_JMessage cancelMsg, Androidapi::Jni::Os::_di_JMessage continueMsg) = 0 ;
	virtual void __cdecl onUnhandledInputEvent(_di_JWebView view, Androidapi::Jni::Graphicscontentviewtext::_di_JInputEvent event) = 0 ;
	virtual void __cdecl onUnhandledKeyEvent(_di_JWebView view, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual _di_JWebResourceResponse __cdecl shouldInterceptRequest(_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url) = 0 /* overload */;
	virtual _di_JWebResourceResponse __cdecl shouldInterceptRequest(_di_JWebView view, _di_JWebResourceRequest request) = 0 /* overload */;
	virtual bool __cdecl shouldOverrideKeyEvent(_di_JWebView view, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl shouldOverrideUrlLoading(_di_JWebView view, Androidapi::Jni::Javatypes::_di_JString url) = 0 /* overload */;
	virtual bool __cdecl shouldOverrideUrlLoading(_di_JWebView view, _di_JWebResourceRequest request) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebViewClient : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebViewClientClass,_di_JWebViewClient>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebViewClientClass,_di_JWebViewClient> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebViewClient() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebViewClientClass,_di_JWebViewClient>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebViewClient() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{DEA27CB2-E5C8-497E-9A3E-D9491479FFD9}") JWebViewDatabaseClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JWebViewDatabase __cdecl init() = 0 ;
	virtual _di_JWebViewDatabase __cdecl getInstance(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

__interface  INTERFACE_UUID("{CDF3B654-354D-4CA9-A8ED-C6295AAABC7C}") JWebViewDatabase  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl clearFormData() = 0 ;
	virtual void __cdecl clearHttpAuthUsernamePassword() = 0 ;
	virtual void __cdecl clearUsernamePassword() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getHttpAuthUsernamePassword(Androidapi::Jni::Javatypes::_di_JString host, Androidapi::Jni::Javatypes::_di_JString realm) = 0 ;
	virtual bool __cdecl hasFormData() = 0 ;
	virtual bool __cdecl hasHttpAuthUsernamePassword() = 0 ;
	virtual bool __cdecl hasUsernamePassword() = 0 ;
	virtual void __cdecl setHttpAuthUsernamePassword(Androidapi::Jni::Javatypes::_di_JString host, Androidapi::Jni::Javatypes::_di_JString realm, Androidapi::Jni::Javatypes::_di_JString username, Androidapi::Jni::Javatypes::_di_JString password) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebViewDatabase : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebViewDatabaseClass,_di_JWebViewDatabase>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebViewDatabaseClass,_di_JWebViewDatabase> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebViewDatabase() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebViewDatabaseClass,_di_JWebViewDatabase>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebViewDatabase() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{75DB2D86-E8B2-40D6-94D0-253CDADCD376}") JWebViewFragmentClass  : public Androidapi::Jni::App::JFragmentClass 
{
	HIDESBASE virtual _di_JWebViewFragment __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{65D4F5A5-7470-429E-8544-CE88856852D8}") JWebViewFragment  : public Androidapi::Jni::App::JFragment 
{
	virtual _di_JWebView __cdecl getWebView() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl onCreateView(Androidapi::Jni::Graphicscontentviewtext::_di_JLayoutInflater inflater, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup container, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	HIDESBASE virtual void __cdecl onDestroy() = 0 ;
	HIDESBASE virtual void __cdecl onDestroyView() = 0 ;
	HIDESBASE virtual void __cdecl onPause() = 0 ;
	HIDESBASE virtual void __cdecl onResume() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWebViewFragment : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebViewFragmentClass,_di_JWebViewFragment>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebViewFragmentClass,_di_JWebViewFragment> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWebViewFragment() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWebViewFragmentClass,_di_JWebViewFragment>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWebViewFragment() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Webkit */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_WEBKIT)
using namespace Androidapi::Jni::Webkit;
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
#endif	// Androidapi_Jni_WebkitHPP
