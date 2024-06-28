// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.WebKit.pas' rev: 34.00 (iOS)

#ifndef Iosapi_WebkitHPP
#define Iosapi_WebkitHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Webkit
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE WKBackForwardListItemClass;
typedef System::DelphiInterface<WKBackForwardListItemClass> _di_WKBackForwardListItemClass;
__interface DELPHIINTERFACE WKBackForwardListItem;
typedef System::DelphiInterface<WKBackForwardListItem> _di_WKBackForwardListItem;
class DELPHICLASS TWKBackForwardListItem;
__interface DELPHIINTERFACE WKBackForwardListClass;
typedef System::DelphiInterface<WKBackForwardListClass> _di_WKBackForwardListClass;
__interface DELPHIINTERFACE WKBackForwardList;
typedef System::DelphiInterface<WKBackForwardList> _di_WKBackForwardList;
class DELPHICLASS TWKBackForwardList;
__interface DELPHIINTERFACE WKContentRuleListClass;
typedef System::DelphiInterface<WKContentRuleListClass> _di_WKContentRuleListClass;
__interface DELPHIINTERFACE WKContentRuleList;
typedef System::DelphiInterface<WKContentRuleList> _di_WKContentRuleList;
class DELPHICLASS TWKContentRuleList;
__interface DELPHIINTERFACE WKContentRuleListStoreClass;
typedef System::DelphiInterface<WKContentRuleListStoreClass> _di_WKContentRuleListStoreClass;
__interface DELPHIINTERFACE WKContentRuleListStore;
typedef System::DelphiInterface<WKContentRuleListStore> _di_WKContentRuleListStore;
class DELPHICLASS TWKContentRuleListStore;
__interface DELPHIINTERFACE WKContextMenuElementInfoClass;
typedef System::DelphiInterface<WKContextMenuElementInfoClass> _di_WKContextMenuElementInfoClass;
__interface DELPHIINTERFACE WKContextMenuElementInfo;
typedef System::DelphiInterface<WKContextMenuElementInfo> _di_WKContextMenuElementInfo;
class DELPHICLASS TWKContextMenuElementInfo;
__interface DELPHIINTERFACE WKSecurityOriginClass;
typedef System::DelphiInterface<WKSecurityOriginClass> _di_WKSecurityOriginClass;
__interface DELPHIINTERFACE WKSecurityOrigin;
typedef System::DelphiInterface<WKSecurityOrigin> _di_WKSecurityOrigin;
class DELPHICLASS TWKSecurityOrigin;
__interface DELPHIINTERFACE WKWebViewClass;
typedef System::DelphiInterface<WKWebViewClass> _di_WKWebViewClass;
__interface DELPHIINTERFACE WKWebView;
typedef System::DelphiInterface<WKWebView> _di_WKWebView;
class DELPHICLASS TWKWebView;
__interface DELPHIINTERFACE WKFrameInfoClass;
typedef System::DelphiInterface<WKFrameInfoClass> _di_WKFrameInfoClass;
__interface DELPHIINTERFACE WKFrameInfo;
typedef System::DelphiInterface<WKFrameInfo> _di_WKFrameInfo;
class DELPHICLASS TWKFrameInfo;
__interface DELPHIINTERFACE WKHTTPCookieStoreObserver;
typedef System::DelphiInterface<WKHTTPCookieStoreObserver> _di_WKHTTPCookieStoreObserver;
__interface DELPHIINTERFACE WKHTTPCookieStoreClass;
typedef System::DelphiInterface<WKHTTPCookieStoreClass> _di_WKHTTPCookieStoreClass;
__interface DELPHIINTERFACE WKHTTPCookieStore;
typedef System::DelphiInterface<WKHTTPCookieStore> _di_WKHTTPCookieStore;
class DELPHICLASS TWKHTTPCookieStore;
__interface DELPHIINTERFACE WKWebpagePreferencesClass;
typedef System::DelphiInterface<WKWebpagePreferencesClass> _di_WKWebpagePreferencesClass;
__interface DELPHIINTERFACE WKWebpagePreferences;
typedef System::DelphiInterface<WKWebpagePreferences> _di_WKWebpagePreferences;
class DELPHICLASS TWKWebpagePreferences;
__interface DELPHIINTERFACE WKNavigationClass;
typedef System::DelphiInterface<WKNavigationClass> _di_WKNavigationClass;
__interface DELPHIINTERFACE WKNavigation;
typedef System::DelphiInterface<WKNavigation> _di_WKNavigation;
class DELPHICLASS TWKNavigation;
__interface DELPHIINTERFACE WKNavigationActionClass;
typedef System::DelphiInterface<WKNavigationActionClass> _di_WKNavigationActionClass;
__interface DELPHIINTERFACE WKNavigationAction;
typedef System::DelphiInterface<WKNavigationAction> _di_WKNavigationAction;
class DELPHICLASS TWKNavigationAction;
__interface DELPHIINTERFACE WKNavigationDelegate;
typedef System::DelphiInterface<WKNavigationDelegate> _di_WKNavigationDelegate;
__interface DELPHIINTERFACE WKNavigationResponseClass;
typedef System::DelphiInterface<WKNavigationResponseClass> _di_WKNavigationResponseClass;
__interface DELPHIINTERFACE WKNavigationResponse;
typedef System::DelphiInterface<WKNavigationResponse> _di_WKNavigationResponse;
class DELPHICLASS TWKNavigationResponse;
__interface DELPHIINTERFACE WKPreferencesClass;
typedef System::DelphiInterface<WKPreferencesClass> _di_WKPreferencesClass;
__interface DELPHIINTERFACE WKPreferences;
typedef System::DelphiInterface<WKPreferences> _di_WKPreferences;
class DELPHICLASS TWKPreferences;
__interface DELPHIINTERFACE WKPreviewActionItem;
typedef System::DelphiInterface<WKPreviewActionItem> _di_WKPreviewActionItem;
__interface DELPHIINTERFACE WKPreviewElementInfoClass;
typedef System::DelphiInterface<WKPreviewElementInfoClass> _di_WKPreviewElementInfoClass;
__interface DELPHIINTERFACE WKPreviewElementInfo;
typedef System::DelphiInterface<WKPreviewElementInfo> _di_WKPreviewElementInfo;
class DELPHICLASS TWKPreviewElementInfo;
__interface DELPHIINTERFACE WKProcessPoolClass;
typedef System::DelphiInterface<WKProcessPoolClass> _di_WKProcessPoolClass;
__interface DELPHIINTERFACE WKProcessPool;
typedef System::DelphiInterface<WKProcessPool> _di_WKProcessPool;
class DELPHICLASS TWKProcessPool;
__interface DELPHIINTERFACE WKScriptMessageClass;
typedef System::DelphiInterface<WKScriptMessageClass> _di_WKScriptMessageClass;
__interface DELPHIINTERFACE WKScriptMessage;
typedef System::DelphiInterface<WKScriptMessage> _di_WKScriptMessage;
class DELPHICLASS TWKScriptMessage;
__interface DELPHIINTERFACE WKScriptMessageHandler;
typedef System::DelphiInterface<WKScriptMessageHandler> _di_WKScriptMessageHandler;
__interface DELPHIINTERFACE WKSnapshotConfigurationClass;
typedef System::DelphiInterface<WKSnapshotConfigurationClass> _di_WKSnapshotConfigurationClass;
__interface DELPHIINTERFACE WKSnapshotConfiguration;
typedef System::DelphiInterface<WKSnapshotConfiguration> _di_WKSnapshotConfiguration;
class DELPHICLASS TWKSnapshotConfiguration;
__interface DELPHIINTERFACE WKUIDelegate;
typedef System::DelphiInterface<WKUIDelegate> _di_WKUIDelegate;
__interface DELPHIINTERFACE WKURLSchemeHandler;
typedef System::DelphiInterface<WKURLSchemeHandler> _di_WKURLSchemeHandler;
__interface DELPHIINTERFACE WKURLSchemeTask;
typedef System::DelphiInterface<WKURLSchemeTask> _di_WKURLSchemeTask;
__interface DELPHIINTERFACE WKUserContentControllerClass;
typedef System::DelphiInterface<WKUserContentControllerClass> _di_WKUserContentControllerClass;
__interface DELPHIINTERFACE WKUserContentController;
typedef System::DelphiInterface<WKUserContentController> _di_WKUserContentController;
class DELPHICLASS TWKUserContentController;
__interface DELPHIINTERFACE WKUserScriptClass;
typedef System::DelphiInterface<WKUserScriptClass> _di_WKUserScriptClass;
__interface DELPHIINTERFACE WKUserScript;
typedef System::DelphiInterface<WKUserScript> _di_WKUserScript;
class DELPHICLASS TWKUserScript;
__interface DELPHIINTERFACE WKWebViewConfigurationClass;
typedef System::DelphiInterface<WKWebViewConfigurationClass> _di_WKWebViewConfigurationClass;
__interface DELPHIINTERFACE WKWebViewConfiguration;
typedef System::DelphiInterface<WKWebViewConfiguration> _di_WKWebViewConfiguration;
class DELPHICLASS TWKWebViewConfiguration;
__interface DELPHIINTERFACE WKWebsiteDataRecordClass;
typedef System::DelphiInterface<WKWebsiteDataRecordClass> _di_WKWebsiteDataRecordClass;
__interface DELPHIINTERFACE WKWebsiteDataRecord;
typedef System::DelphiInterface<WKWebsiteDataRecord> _di_WKWebsiteDataRecord;
class DELPHICLASS TWKWebsiteDataRecord;
__interface DELPHIINTERFACE WKWebsiteDataStoreClass;
typedef System::DelphiInterface<WKWebsiteDataStoreClass> _di_WKWebsiteDataStoreClass;
__interface DELPHIINTERFACE WKWebsiteDataStore;
typedef System::DelphiInterface<WKWebsiteDataStore> _di_WKWebsiteDataStore;
class DELPHICLASS TWKWebsiteDataStore;
__interface DELPHIINTERFACE WKWindowFeaturesClass;
typedef System::DelphiInterface<WKWindowFeaturesClass> _di_WKWindowFeaturesClass;
__interface DELPHIINTERFACE WKWindowFeatures;
typedef System::DelphiInterface<WKWindowFeatures> _di_WKWindowFeatures;
class DELPHICLASS TWKWindowFeatures;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *NSAttributedStringCompletionHandler)(Iosapi::Foundation::_di_NSAttributedString p1, Iosapi::Foundation::_di_NSDictionary p2, Iosapi::Foundation::_di_NSError p3);

typedef long WKErrorCode;

typedef long WKContentMode;

typedef long WKNavigationType;

typedef long WKNavigationActionPolicy;

typedef long WKNavigationResponsePolicy;

typedef long WKUserScriptInjectionTime;

typedef long WKDataDetectorTypes;

typedef long WKSelectionGranularity;

typedef long WKAudiovisualMediaTypes;

typedef void __fastcall (__closure *TWKContentRuleListStoreBlockMethod1)(_di_WKContentRuleList param1, Iosapi::Foundation::_di_NSError param2);

typedef void __fastcall (__closure *TWKContentRuleListStoreBlockMethod2)(Iosapi::Foundation::_di_NSError param1);

typedef void __fastcall (__closure *TWKContentRuleListStoreBlockMethod3)(Iosapi::Foundation::_di_NSArray param1);

typedef void __fastcall (__closure *TWKWebViewBlockMethod1)(void * param1, Iosapi::Foundation::_di_NSError error);

typedef void __fastcall (__closure *TWKWebViewBlockMethod2)(Iosapi::Uikit::_di_UIImage snapshotImage, Iosapi::Foundation::_di_NSError error);

typedef void __fastcall (__closure *TWKHTTPCookieStoreBlockMethod1)(Iosapi::Foundation::_di_NSArray param1);

typedef void __fastcall (__closure *TWKHTTPCookieStoreBlockMethod2)(void);

typedef void __fastcall (__closure *TWKNavigationDelegateBlockMethod1)(long param1);

typedef void __fastcall (__closure *TWKNavigationDelegateBlockMethod2)(long param1, _di_WKWebpagePreferences param2);

typedef void __fastcall (__closure *TWKNavigationDelegateBlockMethod3)(long param1);

typedef void __fastcall (__closure *TWKNavigationDelegateBlockMethod4)(long disposition, Iosapi::Foundation::_di_NSURLCredential credential);

typedef void __fastcall (__closure *TWKUIDelegateBlockMethod1)(void);

typedef void __fastcall (__closure *TWKUIDelegateBlockMethod2)(bool result);

typedef void __fastcall (__closure *TWKUIDelegateBlockMethod3)(Iosapi::Foundation::_di_NSString result);

typedef void __fastcall (__closure *TWKUIDelegateBlockMethod4)(Iosapi::Uikit::_di_UIContextMenuConfiguration configuration);

typedef void __fastcall (__closure *TWKWebsiteDataStoreBlockMethod1)(Iosapi::Foundation::_di_NSArray param1);

typedef void __fastcall (__closure *TWKWebsiteDataStoreBlockMethod2)(void);

__interface  INTERFACE_UUID("{4E7E1674-03C5-4DF8-8E68-96C2786F6ED4}") WKBackForwardListItemClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{02FB445F-863F-43FA-9588-058F7FFA850D}") WKBackForwardListItem  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSURL __cdecl initialURL() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl URL() = 0 ;
};

class PASCALIMPLEMENTATION TWKBackForwardListItem : public Macapi::Objectivec::TOCGenericImport__2<_di_WKBackForwardListItemClass,_di_WKBackForwardListItem>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKBackForwardListItemClass,_di_WKBackForwardListItem> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKBackForwardListItem(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKBackForwardListItemClass,_di_WKBackForwardListItem>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKBackForwardListItem() { }
	
};


__interface  INTERFACE_UUID("{EA218791-FF4C-4E0C-9468-EB4CA5F843C4}") WKBackForwardListClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{945C8CD5-A5B9-4DB3-8B70-9D45AE928E68}") WKBackForwardList  : public Iosapi::Foundation::NSObject 
{
	virtual _di_WKBackForwardListItem __cdecl backItem() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl backList() = 0 ;
	virtual _di_WKBackForwardListItem __cdecl currentItem() = 0 ;
	virtual _di_WKBackForwardListItem __cdecl forwardItem() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl forwardList() = 0 ;
	virtual _di_WKBackForwardListItem __cdecl itemAtIndex(long index) = 0 ;
};

class PASCALIMPLEMENTATION TWKBackForwardList : public Macapi::Objectivec::TOCGenericImport__2<_di_WKBackForwardListClass,_di_WKBackForwardList>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKBackForwardListClass,_di_WKBackForwardList> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKBackForwardList(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKBackForwardListClass,_di_WKBackForwardList>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKBackForwardList() { }
	
};


__interface  INTERFACE_UUID("{4864FEDC-76EF-4D21-9D24-A4D467E2F708}") WKContentRuleListClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{4B241548-40D1-4312-B188-88C837F0FBFE}") WKContentRuleList  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl identifier() = 0 ;
};

class PASCALIMPLEMENTATION TWKContentRuleList : public Macapi::Objectivec::TOCGenericImport__2<_di_WKContentRuleListClass,_di_WKContentRuleList>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKContentRuleListClass,_di_WKContentRuleList> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKContentRuleList(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKContentRuleListClass,_di_WKContentRuleList>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKContentRuleList() { }
	
};


__interface  INTERFACE_UUID("{14CE6524-F8D7-416A-8F57-77B185902AD4}") WKContentRuleListStoreClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl defaultStore() = 0 ;
	virtual void * __cdecl storeWithURL(Iosapi::Foundation::_di_NSURL url) = 0 ;
};

__interface  INTERFACE_UUID("{F02D8647-A72D-4760-BF46-67810D17E10A}") WKContentRuleListStore  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl compileContentRuleListForIdentifier(Iosapi::Foundation::_di_NSString identifier, Iosapi::Foundation::_di_NSString encodedContentRuleList, TWKContentRuleListStoreBlockMethod1 completionHandler) = 0 ;
	virtual void __cdecl getAvailableContentRuleListIdentifiers(TWKContentRuleListStoreBlockMethod3 completionHandler) = 0 ;
	virtual void __cdecl lookUpContentRuleListForIdentifier(Iosapi::Foundation::_di_NSString identifier, TWKContentRuleListStoreBlockMethod1 completionHandler) = 0 ;
	virtual void __cdecl removeContentRuleListForIdentifier(Iosapi::Foundation::_di_NSString identifier, TWKContentRuleListStoreBlockMethod2 completionHandler) = 0 ;
};

class PASCALIMPLEMENTATION TWKContentRuleListStore : public Macapi::Objectivec::TOCGenericImport__2<_di_WKContentRuleListStoreClass,_di_WKContentRuleListStore>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKContentRuleListStoreClass,_di_WKContentRuleListStore> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKContentRuleListStore(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKContentRuleListStoreClass,_di_WKContentRuleListStore>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKContentRuleListStore() { }
	
};


__interface  INTERFACE_UUID("{40D0C71A-041C-4074-A05A-5C655F0558A7}") WKContextMenuElementInfoClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{5AAADDF5-76E1-409E-9B55-475EFC16E28A}") WKContextMenuElementInfo  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSURL __cdecl linkURL() = 0 ;
};

class PASCALIMPLEMENTATION TWKContextMenuElementInfo : public Macapi::Objectivec::TOCGenericImport__2<_di_WKContextMenuElementInfoClass,_di_WKContextMenuElementInfo>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKContextMenuElementInfoClass,_di_WKContextMenuElementInfo> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKContextMenuElementInfo(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKContextMenuElementInfoClass,_di_WKContextMenuElementInfo>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKContextMenuElementInfo() { }
	
};


__interface  INTERFACE_UUID("{81DB91C9-EAD4-4961-889F-0FC90F174AD3}") WKSecurityOriginClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{8B8FA506-19D2-41ED-B5BF-05E113231FE0}") WKSecurityOrigin  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl host() = 0 ;
	virtual long __cdecl port() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl protocol() = 0 ;
};

class PASCALIMPLEMENTATION TWKSecurityOrigin : public Macapi::Objectivec::TOCGenericImport__2<_di_WKSecurityOriginClass,_di_WKSecurityOrigin>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKSecurityOriginClass,_di_WKSecurityOrigin> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKSecurityOrigin(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKSecurityOriginClass,_di_WKSecurityOrigin>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKSecurityOrigin() { }
	
};


__interface  INTERFACE_UUID("{4AD37690-DD68-41D1-AA84-DAB6144162EF}") WKWebViewClass  : public Iosapi::Uikit::UIViewClass 
{
	virtual bool __cdecl handlesURLScheme(Iosapi::Foundation::_di_NSString urlScheme) = 0 ;
};

__interface  INTERFACE_UUID("{81680B75-DC3C-4AD6-807B-51B5C5E78EAF}") WKWebView  : public Iosapi::Uikit::UIView 
{
	virtual bool __cdecl allowsBackForwardNavigationGestures() = 0 ;
	virtual bool __cdecl allowsLinkPreview() = 0 ;
	virtual _di_WKBackForwardList __cdecl backForwardList() = 0 ;
	virtual bool __cdecl canGoBack() = 0 ;
	virtual bool __cdecl canGoForward() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl certificateChain() = 0 ;
	virtual _di_WKWebViewConfiguration __cdecl configuration() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl customUserAgent() = 0 ;
	virtual double __cdecl estimatedProgress() = 0 ;
	virtual void __cdecl evaluateJavaScript(Iosapi::Foundation::_di_NSString javaScriptString, TWKWebViewBlockMethod1 completionHandler) = 0 ;
	virtual _di_WKNavigation __cdecl goBack() = 0 ;
	virtual _di_WKNavigation __cdecl goForward() = 0 ;
	virtual _di_WKNavigation __cdecl goToBackForwardListItem(_di_WKBackForwardListItem item) = 0 ;
	virtual bool __cdecl hasOnlySecureContent() = 0 ;
	virtual void * __cdecl initWithCoder(Iosapi::Foundation::_di_NSCoder coder) = 0 ;
	HIDESBASE virtual void * __cdecl initWithFrame(Iosapi::Foundation::NSRect frame, _di_WKWebViewConfiguration configuration) = 0 ;
	virtual bool __cdecl isLoading() = 0 ;
	virtual _di_WKNavigation __cdecl loadData(Iosapi::Foundation::_di_NSData data, Iosapi::Foundation::_di_NSString MIMEType, Iosapi::Foundation::_di_NSString characterEncodingName, Iosapi::Foundation::_di_NSURL baseURL) = 0 ;
	virtual _di_WKNavigation __cdecl loadFileURL(Iosapi::Foundation::_di_NSURL URL, Iosapi::Foundation::_di_NSURL readAccessURL) = 0 ;
	virtual _di_WKNavigation __cdecl loadHTMLString(Iosapi::Foundation::_di_NSString string, Iosapi::Foundation::_di_NSURL baseURL) = 0 ;
	virtual _di_WKNavigation __cdecl loadRequest(Iosapi::Foundation::_di_NSURLRequest request) = 0 ;
	virtual void * __cdecl navigationDelegate() = 0 ;
	virtual _di_WKNavigation __cdecl reload() = 0 ;
	virtual _di_WKNavigation __cdecl reloadFromOrigin() = 0 ;
	virtual Iosapi::Uikit::_di_UIScrollView __cdecl scrollView() = 0 ;
	virtual void * __cdecl serverTrust() = 0 ;
	virtual void __cdecl setAllowsBackForwardNavigationGestures(bool allowsBackForwardNavigationGestures) = 0 ;
	virtual void __cdecl setAllowsLinkPreview(bool allowsLinkPreview) = 0 ;
	virtual void __cdecl setCustomUserAgent(Iosapi::Foundation::_di_NSString customUserAgent) = 0 ;
	virtual void __cdecl setNavigationDelegate(void * navigationDelegate) = 0 ;
	virtual void __cdecl setUIDelegate(void * UIDelegate) = 0 ;
	virtual void __cdecl stopLoading() = 0 ;
	virtual void __cdecl takeSnapshotWithConfiguration(_di_WKSnapshotConfiguration snapshotConfiguration, TWKWebViewBlockMethod2 completionHandler) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
	virtual void * __cdecl UIDelegate() = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl URL() = 0 ;
};

class PASCALIMPLEMENTATION TWKWebView : public Macapi::Objectivec::TOCGenericImport__2<_di_WKWebViewClass,_di_WKWebView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKWebViewClass,_di_WKWebView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKWebView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKWebViewClass,_di_WKWebView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKWebView() { }
	
};


__interface  INTERFACE_UUID("{90F87597-298D-40D3-84A2-4A9578463B54}") WKFrameInfoClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{225153D1-FF3E-4FFF-B184-68765D21AD85}") WKFrameInfo  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl isMainFrame() = 0 ;
	virtual Iosapi::Foundation::_di_NSURLRequest __cdecl request() = 0 ;
	virtual _di_WKSecurityOrigin __cdecl securityOrigin() = 0 ;
	virtual _di_WKWebView __cdecl webView() = 0 ;
};

class PASCALIMPLEMENTATION TWKFrameInfo : public Macapi::Objectivec::TOCGenericImport__2<_di_WKFrameInfoClass,_di_WKFrameInfo>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKFrameInfoClass,_di_WKFrameInfo> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKFrameInfo(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKFrameInfoClass,_di_WKFrameInfo>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKFrameInfo() { }
	
};


__interface  INTERFACE_UUID("{B9B076DE-F993-4C2A-8D68-F3596C279931}") WKHTTPCookieStoreObserver  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl cookiesDidChangeInCookieStore(_di_WKHTTPCookieStore cookieStore) = 0 ;
};

__interface  INTERFACE_UUID("{D5AAC178-DFD1-41D6-86AF-787F58D9A004}") WKHTTPCookieStoreClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{5A2E9297-6D69-4894-9C60-8173B4096770}") WKHTTPCookieStore  : public Iosapi::Foundation::NSObject 
{
	HIDESBASE virtual void __cdecl addObserver(void * observer) = 0 ;
	virtual void __cdecl deleteCookie(Iosapi::Foundation::_di_NSHTTPCookie cookie, TWKHTTPCookieStoreBlockMethod2 completionHandler) = 0 ;
	virtual void __cdecl getAllCookies(TWKHTTPCookieStoreBlockMethod1 completionHandler) = 0 ;
	HIDESBASE virtual void __cdecl removeObserver(void * observer) = 0 ;
	virtual void __cdecl setCookie(Iosapi::Foundation::_di_NSHTTPCookie cookie, TWKHTTPCookieStoreBlockMethod2 completionHandler) = 0 ;
};

class PASCALIMPLEMENTATION TWKHTTPCookieStore : public Macapi::Objectivec::TOCGenericImport__2<_di_WKHTTPCookieStoreClass,_di_WKHTTPCookieStore>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKHTTPCookieStoreClass,_di_WKHTTPCookieStore> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKHTTPCookieStore(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKHTTPCookieStoreClass,_di_WKHTTPCookieStore>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKHTTPCookieStore() { }
	
};


__interface  INTERFACE_UUID("{4197EBF6-4B05-4FEB-B21A-B2A00FA36ADB}") WKWebpagePreferencesClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D0D110E0-5B3D-4B3C-97CE-4DE8FEE261DD}") WKWebpagePreferences  : public Iosapi::Foundation::NSObject 
{
	virtual long __cdecl preferredContentMode() = 0 ;
	virtual void __cdecl setPreferredContentMode(long preferredContentMode) = 0 ;
};

class PASCALIMPLEMENTATION TWKWebpagePreferences : public Macapi::Objectivec::TOCGenericImport__2<_di_WKWebpagePreferencesClass,_di_WKWebpagePreferences>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKWebpagePreferencesClass,_di_WKWebpagePreferences> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKWebpagePreferences(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKWebpagePreferencesClass,_di_WKWebpagePreferences>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKWebpagePreferences() { }
	
};


__interface  INTERFACE_UUID("{BD59C6E8-0DA3-43F4-B4E8-49AD317DE9D9}") WKNavigationClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{EA8A5456-55AA-4401-BA03-EC1978F9B276}") WKNavigation  : public Iosapi::Foundation::NSObject 
{
	virtual long __cdecl effectiveContentMode() = 0 ;
};

class PASCALIMPLEMENTATION TWKNavigation : public Macapi::Objectivec::TOCGenericImport__2<_di_WKNavigationClass,_di_WKNavigation>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKNavigationClass,_di_WKNavigation> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKNavigation(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKNavigationClass,_di_WKNavigation>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKNavigation() { }
	
};


__interface  INTERFACE_UUID("{C888C99B-D534-4C5B-BEAE-6C74B61AD87C}") WKNavigationActionClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{DC43CB26-69A8-4044-869F-F3A33CA5875B}") WKNavigationAction  : public Iosapi::Foundation::NSObject 
{
	virtual long __cdecl navigationType() = 0 ;
	virtual Iosapi::Foundation::_di_NSURLRequest __cdecl request() = 0 ;
	virtual _di_WKFrameInfo __cdecl sourceFrame() = 0 ;
	virtual _di_WKFrameInfo __cdecl targetFrame() = 0 ;
};

class PASCALIMPLEMENTATION TWKNavigationAction : public Macapi::Objectivec::TOCGenericImport__2<_di_WKNavigationActionClass,_di_WKNavigationAction>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKNavigationActionClass,_di_WKNavigationAction> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKNavigationAction(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKNavigationActionClass,_di_WKNavigationAction>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKNavigationAction() { }
	
};


__interface  INTERFACE_UUID("{FD874B6D-A9C0-4105-AB0D-56F12293565F}") WKNavigationDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl webViewDecidePolicyForNavigationAction(_di_WKWebView webView, _di_WKNavigationAction navigationAction, void * decisionHandler) = 0 /* overload */;
	virtual void __cdecl webViewDecidePolicyForNavigationResponse(_di_WKWebView webView, _di_WKNavigationResponse navigationResponse, void * decisionHandler) = 0 ;
	virtual void __cdecl webViewDidCommitNavigation(_di_WKWebView webView, _di_WKNavigation navigation) = 0 ;
	virtual void __cdecl webViewDidFailNavigation(_di_WKWebView webView, _di_WKNavigation navigation, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl webViewDidFailProvisionalNavigation(_di_WKWebView webView, _di_WKNavigation navigation, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl webViewDidFinishNavigation(_di_WKWebView webView, _di_WKNavigation navigation) = 0 ;
	virtual void __cdecl webViewDidReceiveAuthenticationChallenge(_di_WKWebView webView, Iosapi::Foundation::_di_NSURLAuthenticationChallenge challenge, void * completionHandler) = 0 ;
	virtual void __cdecl webViewDidReceiveServerRedirectForProvisionalNavigation(_di_WKWebView webView, _di_WKNavigation navigation) = 0 ;
	virtual void __cdecl webViewDidStartProvisionalNavigation(_di_WKWebView webView, _di_WKNavigation navigation) = 0 ;
	virtual void __cdecl webViewWebContentProcessDidTerminate(_di_WKWebView webView) = 0 ;
};

__interface  INTERFACE_UUID("{3CBCE722-E1C3-43DE-9CDF-57C295AE041A}") WKNavigationResponseClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{7216894F-FAEB-459F-BD67-C53189FC818D}") WKNavigationResponse  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl canShowMIMEType() = 0 ;
	virtual bool __cdecl isForMainFrame() = 0 ;
	virtual Iosapi::Foundation::_di_NSURLResponse __cdecl response() = 0 ;
};

class PASCALIMPLEMENTATION TWKNavigationResponse : public Macapi::Objectivec::TOCGenericImport__2<_di_WKNavigationResponseClass,_di_WKNavigationResponse>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKNavigationResponseClass,_di_WKNavigationResponse> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKNavigationResponse(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKNavigationResponseClass,_di_WKNavigationResponse>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKNavigationResponse() { }
	
};


__interface  INTERFACE_UUID("{B5F711CB-AC02-4CF0-94F7-02A6F978B2F6}") WKPreferencesClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{996436E3-C8E2-46AF-A1A6-D4BA4AAEAD47}") WKPreferences  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl isFraudulentWebsiteWarningEnabled() = 0 ;
	virtual bool __cdecl javaEnabled() = 0 ;
	virtual bool __cdecl javaScriptCanOpenWindowsAutomatically() = 0 ;
	virtual bool __cdecl javaScriptEnabled() = 0 ;
	virtual double __cdecl minimumFontSize() = 0 ;
	virtual bool __cdecl plugInsEnabled() = 0 ;
	virtual void __cdecl setFraudulentWebsiteWarningEnabled(bool fraudulentWebsiteWarningEnabled) = 0 ;
	virtual void __cdecl setJavaEnabled(bool javaEnabled) = 0 ;
	virtual void __cdecl setJavaScriptCanOpenWindowsAutomatically(bool javaScriptCanOpenWindowsAutomatically) = 0 ;
	virtual void __cdecl setJavaScriptEnabled(bool javaScriptEnabled) = 0 ;
	virtual void __cdecl setMinimumFontSize(double minimumFontSize) = 0 ;
	virtual void __cdecl setPlugInsEnabled(bool plugInsEnabled) = 0 ;
};

class PASCALIMPLEMENTATION TWKPreferences : public Macapi::Objectivec::TOCGenericImport__2<_di_WKPreferencesClass,_di_WKPreferences>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKPreferencesClass,_di_WKPreferences> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKPreferences(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKPreferencesClass,_di_WKPreferences>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKPreferences() { }
	
};


__interface  INTERFACE_UUID("{FA424EAB-B3FA-4B89-915B-BF81829A2296}") WKPreviewActionItem  : public Macapi::Objectivec::IObjectiveC 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl identifier() = 0 ;
};

__interface  INTERFACE_UUID("{8E3B5E08-7A55-445F-92BC-DC572739C542}") WKPreviewElementInfoClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{FF56ED61-2EEF-4C71-A17E-32465AA87E11}") WKPreviewElementInfo  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSURL __cdecl linkURL() = 0 ;
};

class PASCALIMPLEMENTATION TWKPreviewElementInfo : public Macapi::Objectivec::TOCGenericImport__2<_di_WKPreviewElementInfoClass,_di_WKPreviewElementInfo>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKPreviewElementInfoClass,_di_WKPreviewElementInfo> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKPreviewElementInfo(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKPreviewElementInfoClass,_di_WKPreviewElementInfo>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKPreviewElementInfo() { }
	
};


__interface  INTERFACE_UUID("{0B25E984-01B3-4D53-BAF0-EA2A21393E0B}") WKProcessPoolClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{A45D6127-FAD0-4EA4-B4D7-6B7E54004909}") WKProcessPool  : public Iosapi::Foundation::NSObject 
{
	
};

class PASCALIMPLEMENTATION TWKProcessPool : public Macapi::Objectivec::TOCGenericImport__2<_di_WKProcessPoolClass,_di_WKProcessPool>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKProcessPoolClass,_di_WKProcessPool> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKProcessPool(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKProcessPoolClass,_di_WKProcessPool>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKProcessPool() { }
	
};


__interface  INTERFACE_UUID("{943E04FF-5A12-4291-B874-095C6B10D756}") WKScriptMessageClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{E44ECD5C-93CA-4F4B-AE6B-5DD4EBAD4E35}") WKScriptMessage  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl body() = 0 ;
	virtual _di_WKFrameInfo __cdecl frameInfo() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual _di_WKWebView __cdecl webView() = 0 ;
};

class PASCALIMPLEMENTATION TWKScriptMessage : public Macapi::Objectivec::TOCGenericImport__2<_di_WKScriptMessageClass,_di_WKScriptMessage>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKScriptMessageClass,_di_WKScriptMessage> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKScriptMessage(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKScriptMessageClass,_di_WKScriptMessage>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKScriptMessage() { }
	
};


__interface  INTERFACE_UUID("{093162DF-FC23-4C20-B36A-C0AFC7DEDF18}") WKScriptMessageHandler  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl userContentController(_di_WKUserContentController userContentController, _di_WKScriptMessage message) = 0 ;
};

__interface  INTERFACE_UUID("{A5EC3C86-A335-455A-90CF-596CC4471A3A}") WKSnapshotConfigurationClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{FAD098B9-6FAD-4A36-9131-C2E9AC7D3E8D}") WKSnapshotConfiguration  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl afterScreenUpdates() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl rect() = 0 ;
	virtual void __cdecl setAfterScreenUpdates(bool afterScreenUpdates) = 0 ;
	virtual void __cdecl setRect(Iosapi::Foundation::NSRect rect) = 0 ;
	virtual void __cdecl setSnapshotWidth(Iosapi::Foundation::_di_NSNumber snapshotWidth) = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl snapshotWidth() = 0 ;
};

class PASCALIMPLEMENTATION TWKSnapshotConfiguration : public Macapi::Objectivec::TOCGenericImport__2<_di_WKSnapshotConfigurationClass,_di_WKSnapshotConfiguration>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKSnapshotConfigurationClass,_di_WKSnapshotConfiguration> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKSnapshotConfiguration(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKSnapshotConfigurationClass,_di_WKSnapshotConfiguration>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKSnapshotConfiguration() { }
	
};


__interface  INTERFACE_UUID("{6F7C5692-ED85-4A65-A24D-BEB14164553D}") WKUIDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl webViewContextMenuConfigurationForElement(_di_WKWebView webView, _di_WKContextMenuElementInfo elementInfo, void * completionHandler) = 0 ;
	virtual void __cdecl webViewContextMenuDidEndForElement(_di_WKWebView webView, _di_WKContextMenuElementInfo elementInfo) = 0 ;
	virtual void __cdecl webViewContextMenuForElement(_di_WKWebView webView, _di_WKContextMenuElementInfo elementInfo, void * animator) = 0 ;
	virtual void __cdecl webViewContextMenuWillPresentForElement(_di_WKWebView webView, _di_WKContextMenuElementInfo elementInfo) = 0 ;
	virtual _di_WKWebView __cdecl webViewCreateWebViewWithConfiguration(_di_WKWebView webView, _di_WKWebViewConfiguration configuration, _di_WKNavigationAction navigationAction, _di_WKWindowFeatures windowFeatures) = 0 ;
	virtual void __cdecl webViewDidClose(_di_WKWebView webView) = 0 ;
	virtual void __cdecl webViewRunJavaScriptAlertPanelWithMessage(_di_WKWebView webView, Iosapi::Foundation::_di_NSString message, _di_WKFrameInfo frame, void * completionHandler) = 0 ;
	virtual void __cdecl webViewRunJavaScriptConfirmPanelWithMessage(_di_WKWebView webView, Iosapi::Foundation::_di_NSString message, _di_WKFrameInfo frame, void * completionHandler) = 0 ;
	virtual void __cdecl webViewRunJavaScriptTextInputPanelWithPrompt(_di_WKWebView webView, Iosapi::Foundation::_di_NSString prompt, Iosapi::Foundation::_di_NSString defaultText, _di_WKFrameInfo frame, void * completionHandler) = 0 ;
};

__interface  INTERFACE_UUID("{2DE0DDFD-D6B7-4DDA-935D-22622C733970}") WKURLSchemeHandler  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl webViewStartURLSchemeTask(_di_WKWebView webView, void * urlSchemeTask) = 0 ;
	virtual void __cdecl webViewStopURLSchemeTask(_di_WKWebView webView, void * urlSchemeTask) = 0 ;
};

__interface  INTERFACE_UUID("{A33B9673-DBF8-4D2A-B727-617F7973C44A}") WKURLSchemeTask  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl didFailWithError(Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl didFinish() = 0 ;
	virtual void __cdecl didReceiveData(Iosapi::Foundation::_di_NSData data) = 0 ;
	virtual void __cdecl didReceiveResponse(Iosapi::Foundation::_di_NSURLResponse response) = 0 ;
	virtual Iosapi::Foundation::_di_NSURLRequest __cdecl request() = 0 ;
};

__interface  INTERFACE_UUID("{C33C73CC-6567-429D-A83F-4E85DE933023}") WKUserContentControllerClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{A27AFE3D-0935-461F-8A5C-03ABA440C09C}") WKUserContentController  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl addContentRuleList(_di_WKContentRuleList contentRuleList) = 0 ;
	virtual void __cdecl addScriptMessageHandler(void * scriptMessageHandler, Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual void __cdecl addUserScript(_di_WKUserScript userScript) = 0 ;
	virtual void __cdecl removeAllContentRuleLists() = 0 ;
	virtual void __cdecl removeAllUserScripts() = 0 ;
	virtual void __cdecl removeContentRuleList(_di_WKContentRuleList contentRuleList) = 0 ;
	virtual void __cdecl removeScriptMessageHandlerForName(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl userScripts() = 0 ;
};

class PASCALIMPLEMENTATION TWKUserContentController : public Macapi::Objectivec::TOCGenericImport__2<_di_WKUserContentControllerClass,_di_WKUserContentController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKUserContentControllerClass,_di_WKUserContentController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKUserContentController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKUserContentControllerClass,_di_WKUserContentController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKUserContentController() { }
	
};


__interface  INTERFACE_UUID("{B53EFEFB-377C-4405-8C12-DCDA4B8DF4D7}") WKUserScriptClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{5F564C8E-B1A4-482A-BB95-B61E26DA6C9A}") WKUserScript  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithSource(Iosapi::Foundation::_di_NSString source, long injectionTime, bool forMainFrameOnly) = 0 ;
	virtual long __cdecl injectionTime() = 0 ;
	virtual bool __cdecl isForMainFrameOnly() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl source() = 0 ;
};

class PASCALIMPLEMENTATION TWKUserScript : public Macapi::Objectivec::TOCGenericImport__2<_di_WKUserScriptClass,_di_WKUserScript>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKUserScriptClass,_di_WKUserScript> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKUserScript(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKUserScriptClass,_di_WKUserScript>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKUserScript() { }
	
};


__interface  INTERFACE_UUID("{EA300DF9-D9B1-41A5-8318-AD953F932ABF}") WKWebViewConfigurationClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{CB2BBB9B-0862-4D35-9FBE-5BB738F3DB40}") WKWebViewConfiguration  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl allowsAirPlayForMediaPlayback() = 0 ;
	virtual bool __cdecl allowsInlineMediaPlayback() = 0 ;
	virtual bool __cdecl allowsPictureInPictureMediaPlayback() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl applicationNameForUserAgent() = 0 ;
	virtual long __cdecl dataDetectorTypes() = 0 ;
	virtual _di_WKWebpagePreferences __cdecl defaultWebpagePreferences() = 0 ;
	virtual bool __cdecl ignoresViewportScaleLimits() = 0 ;
	virtual long __cdecl mediaTypesRequiringUserActionForPlayback() = 0 ;
	virtual _di_WKPreferences __cdecl preferences() = 0 ;
	virtual _di_WKProcessPool __cdecl processPool() = 0 ;
	virtual long __cdecl selectionGranularity() = 0 ;
	virtual void __cdecl setAllowsAirPlayForMediaPlayback(bool allowsAirPlayForMediaPlayback) = 0 ;
	virtual void __cdecl setAllowsInlineMediaPlayback(bool allowsInlineMediaPlayback) = 0 ;
	virtual void __cdecl setAllowsPictureInPictureMediaPlayback(bool allowsPictureInPictureMediaPlayback) = 0 ;
	virtual void __cdecl setApplicationNameForUserAgent(Iosapi::Foundation::_di_NSString applicationNameForUserAgent) = 0 ;
	virtual void __cdecl setDataDetectorTypes(long dataDetectorTypes) = 0 ;
	virtual void __cdecl setDefaultWebpagePreferences(_di_WKWebpagePreferences defaultWebpagePreferences) = 0 ;
	virtual void __cdecl setIgnoresViewportScaleLimits(bool ignoresViewportScaleLimits) = 0 ;
	virtual void __cdecl setMediaTypesRequiringUserActionForPlayback(long mediaTypesRequiringUserActionForPlayback) = 0 ;
	virtual void __cdecl setPreferences(_di_WKPreferences preferences) = 0 ;
	virtual void __cdecl setProcessPool(_di_WKProcessPool processPool) = 0 ;
	virtual void __cdecl setSelectionGranularity(long selectionGranularity) = 0 ;
	virtual void __cdecl setSuppressesIncrementalRendering(bool suppressesIncrementalRendering) = 0 ;
	virtual void __cdecl setURLSchemeHandler(void * urlSchemeHandler, Iosapi::Foundation::_di_NSString urlScheme) = 0 ;
	virtual void __cdecl setUserContentController(_di_WKUserContentController userContentController) = 0 ;
	virtual void __cdecl setWebsiteDataStore(_di_WKWebsiteDataStore websiteDataStore) = 0 ;
	virtual bool __cdecl suppressesIncrementalRendering() = 0 ;
	virtual void * __cdecl urlSchemeHandlerForURLScheme(Iosapi::Foundation::_di_NSString urlScheme) = 0 ;
	virtual _di_WKUserContentController __cdecl userContentController() = 0 ;
	virtual _di_WKWebsiteDataStore __cdecl websiteDataStore() = 0 ;
};

class PASCALIMPLEMENTATION TWKWebViewConfiguration : public Macapi::Objectivec::TOCGenericImport__2<_di_WKWebViewConfigurationClass,_di_WKWebViewConfiguration>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKWebViewConfigurationClass,_di_WKWebViewConfiguration> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKWebViewConfiguration(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKWebViewConfigurationClass,_di_WKWebViewConfiguration>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKWebViewConfiguration() { }
	
};


__interface  INTERFACE_UUID("{297DD965-60EC-4AC3-9EBC-97F8E4C24140}") WKWebsiteDataRecordClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{B1B1D946-8FC7-4F92-A18B-AC3A2D10C480}") WKWebsiteDataRecord  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSSet __cdecl dataTypes() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl displayName() = 0 ;
};

class PASCALIMPLEMENTATION TWKWebsiteDataRecord : public Macapi::Objectivec::TOCGenericImport__2<_di_WKWebsiteDataRecordClass,_di_WKWebsiteDataRecord>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKWebsiteDataRecordClass,_di_WKWebsiteDataRecord> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKWebsiteDataRecord(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKWebsiteDataRecordClass,_di_WKWebsiteDataRecord>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKWebsiteDataRecord() { }
	
};


__interface  INTERFACE_UUID("{42FE87F5-4889-4C44-AD5A-E9CA068E71F0}") WKWebsiteDataStoreClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual Iosapi::Foundation::_di_NSSet __cdecl allWebsiteDataTypes() = 0 ;
	virtual _di_WKWebsiteDataStore __cdecl defaultDataStore() = 0 ;
	virtual _di_WKWebsiteDataStore __cdecl nonPersistentDataStore() = 0 ;
};

__interface  INTERFACE_UUID("{064078BE-6369-4AB6-906D-54552717210F}") WKWebsiteDataStore  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl fetchDataRecordsOfTypes(Iosapi::Foundation::_di_NSSet dataTypes, TWKWebsiteDataStoreBlockMethod1 completionHandler) = 0 ;
	virtual _di_WKHTTPCookieStore __cdecl httpCookieStore() = 0 ;
	virtual bool __cdecl isPersistent() = 0 ;
	virtual void __cdecl removeDataOfTypes(Iosapi::Foundation::_di_NSSet dataTypes, Iosapi::Foundation::_di_NSDate date, TWKWebsiteDataStoreBlockMethod2 completionHandler) = 0 /* overload */;
	virtual void __cdecl removeDataOfTypes(Iosapi::Foundation::_di_NSSet dataTypes, Iosapi::Foundation::_di_NSArray dataRecords, TWKWebsiteDataStoreBlockMethod2 completionHandler) = 0 /* overload */;
};

class PASCALIMPLEMENTATION TWKWebsiteDataStore : public Macapi::Objectivec::TOCGenericImport__2<_di_WKWebsiteDataStoreClass,_di_WKWebsiteDataStore>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKWebsiteDataStoreClass,_di_WKWebsiteDataStore> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKWebsiteDataStore(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKWebsiteDataStoreClass,_di_WKWebsiteDataStore>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKWebsiteDataStore() { }
	
};


__interface  INTERFACE_UUID("{3CDA2D44-1A43-4C9D-8A38-594D735DE40F}") WKWindowFeaturesClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{0B1B7DAE-9EA4-4359-8536-B0A804CB4155}") WKWindowFeatures  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSNumber __cdecl allowsResizing() = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl height() = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl menuBarVisibility() = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl statusBarVisibility() = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl toolbarsVisibility() = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl width() = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl x() = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl y() = 0 ;
};

class PASCALIMPLEMENTATION TWKWindowFeatures : public Macapi::Objectivec::TOCGenericImport__2<_di_WKWindowFeaturesClass,_di_WKWindowFeatures>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_WKWindowFeaturesClass,_di_WKWindowFeatures> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TWKWindowFeatures(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_WKWindowFeaturesClass,_di_WKWindowFeatures>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TWKWindowFeatures() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 WKErrorUnknown = System::Int8(0x1);
static constexpr System::Int8 WKErrorWebContentProcessTerminated = System::Int8(0x2);
static constexpr System::Int8 WKErrorWebViewInvalidated = System::Int8(0x3);
static constexpr System::Int8 WKErrorJavaScriptExceptionOccurred = System::Int8(0x4);
static constexpr System::Int8 WKErrorJavaScriptResultTypeIsUnsupported = System::Int8(0x5);
static constexpr System::Int8 WKErrorContentRuleListStoreCompileFailed = System::Int8(0x6);
static constexpr System::Int8 WKErrorContentRuleListStoreLookUpFailed = System::Int8(0x7);
static constexpr System::Int8 WKErrorContentRuleListStoreRemoveFailed = System::Int8(0x8);
static constexpr System::Int8 WKErrorContentRuleListStoreVersionMismatch = System::Int8(0x9);
static constexpr System::Int8 WKErrorAttributedStringContentFailedToLoad = System::Int8(0xa);
static constexpr System::Int8 WKErrorAttributedStringContentLoadTimedOut = System::Int8(0xb);
static constexpr System::Int8 WKContentModeRecommended = System::Int8(0x0);
static constexpr System::Int8 WKContentModeMobile = System::Int8(0x1);
static constexpr System::Int8 WKContentModeDesktop = System::Int8(0x2);
static constexpr System::Int8 WKNavigationTypeLinkActivated = System::Int8(0x0);
static constexpr System::Int8 WKNavigationTypeFormSubmitted = System::Int8(0x1);
static constexpr System::Int8 WKNavigationTypeBackForward = System::Int8(0x2);
static constexpr System::Int8 WKNavigationTypeReload = System::Int8(0x3);
static constexpr System::Int8 WKNavigationTypeFormResubmitted = System::Int8(0x4);
static constexpr System::Int8 WKNavigationTypeOther = System::Int8(-1);
static constexpr System::Int8 WKNavigationActionPolicyCancel = System::Int8(0x0);
static constexpr System::Int8 WKNavigationActionPolicyAllow = System::Int8(0x1);
static constexpr System::Int8 WKNavigationResponsePolicyCancel = System::Int8(0x0);
static constexpr System::Int8 WKNavigationResponsePolicyAllow = System::Int8(0x1);
static constexpr System::Int8 WKUserScriptInjectionTimeAtDocumentStart = System::Int8(0x0);
static constexpr System::Int8 WKUserScriptInjectionTimeAtDocumentEnd = System::Int8(0x1);
static constexpr System::Int8 WKDataDetectorTypeNone = System::Int8(0x0);
static constexpr System::Int8 WKDataDetectorTypePhoneNumber = System::Int8(0x1);
static constexpr System::Int8 WKDataDetectorTypeLink = System::Int8(0x2);
static constexpr System::Int8 WKDataDetectorTypeAddress = System::Int8(0x4);
static constexpr System::Int8 WKDataDetectorTypeCalendarEvent = System::Int8(0x8);
static constexpr System::Int8 WKDataDetectorTypeTrackingNumber = System::Int8(0x10);
static constexpr System::Int8 WKDataDetectorTypeFlightNumber = System::Int8(0x20);
static constexpr System::Int8 WKDataDetectorTypeLookupSuggestion = System::Int8(0x40);
static constexpr System::Int8 WKDataDetectorTypeAll = System::Int8(-1);
static constexpr System::Int8 WKDataDetectorTypeSpotlightSuggestion = System::Int8(0x40);
static constexpr System::Int8 WKSelectionGranularityDynamic = System::Int8(0x0);
static constexpr System::Int8 WKSelectionGranularityCharacter = System::Int8(0x1);
static constexpr System::Int8 WKAudiovisualMediaTypeNone = System::Int8(0x0);
static constexpr System::Int8 WKAudiovisualMediaTypeAudio = System::Int8(0x1);
static constexpr System::Int8 WKAudiovisualMediaTypeVideo = System::Int8(0x2);
static constexpr System::Int8 WKAudiovisualMediaTypeAll = System::Int8(-1);
#define libWebKit u"/System/Library/Frameworks/WebKit.framework/WebKit"
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSReadAccessURLDocumentOption(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall WKErrorDomain(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall WKPreviewActionItemIdentifierOpen(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall WKPreviewActionItemIdentifierAddToReadingList(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall WKPreviewActionItemIdentifierCopy(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall WKPreviewActionItemIdentifierShare(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall WKWebsiteDataTypeFetchCache(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall WKWebsiteDataTypeDiskCache(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall WKWebsiteDataTypeMemoryCache(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall WKWebsiteDataTypeOfflineWebApplicationCache(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall WKWebsiteDataTypeCookies(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall WKWebsiteDataTypeSessionStorage(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall WKWebsiteDataTypeLocalStorage(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall WKWebsiteDataTypeWebSQLDatabases(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall WKWebsiteDataTypeIndexedDBDatabases(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall WKWebsiteDataTypeServiceWorkerRegistrations(void);
}	/* namespace Webkit */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_WEBKIT)
using namespace Iosapi::Webkit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_WebkitHPP
