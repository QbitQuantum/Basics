// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.WebBrowser.Delegate.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Webbrowser_Delegate_IosHPP
#define Fmx_Webbrowser_Delegate_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <FMX.WebBrowser.hpp>
#include <FMX.WebBrowser.Delegate.Cocoa.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.Foundation.hpp>
#include <System.Types.hpp>
#include <iOSapi.WebKit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Webbrowser
{
namespace Delegate
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE WKUIDelegateSlim;
typedef System::DelphiInterface<WKUIDelegateSlim> _di_WKUIDelegateSlim;
__interface DELPHIINTERFACE WKNavigationDelegateSlim;
typedef System::DelphiInterface<WKNavigationDelegateSlim> _di_WKNavigationDelegateSlim;
class DELPHICLASS TWebViewDelegate;
class DELPHICLASS TWebViewDelegateiOS;
class DELPHICLASS TNativeWebViewHelper;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{A0FEDEBE-6023-4FBE-897A-9C005E83934B}") WKUIDelegateSlim  : public Macapi::Objectivec::IObjectiveC 
{
	virtual Iosapi::Webkit::_di_WKWebView __cdecl webViewCreateWebViewWithConfiguration(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKWebViewConfiguration configuration, Iosapi::Webkit::_di_WKNavigationAction navigationAction, Iosapi::Webkit::_di_WKWindowFeatures windowFeatures) = 0 ;
	virtual void __cdecl webViewRunJavaScriptAlertPanelWithMessage(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Foundation::_di_NSString message, Iosapi::Webkit::_di_WKFrameInfo frame, void * completionHandler) = 0 ;
	virtual void __cdecl webViewRunJavaScriptConfirmPanelWithMessage(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Foundation::_di_NSString message, Iosapi::Webkit::_di_WKFrameInfo frame, void * completionHandler) = 0 ;
	virtual void __cdecl webViewRunJavaScriptTextInputPanelWithPrompt(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Foundation::_di_NSString prompt, Iosapi::Foundation::_di_NSString defaultText, Iosapi::Webkit::_di_WKFrameInfo frame, void * completionHandler) = 0 ;
};

__interface  INTERFACE_UUID("{7FDDD993-8024-478B-930D-334AFEF0CA16}") WKNavigationDelegateSlim  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl webViewDecidePolicyForNavigationAction(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigationAction navigationAction, void * decisionHandler) = 0 /* overload */;
	virtual void __cdecl webViewDecidePolicyForNavigationResponse(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigationResponse navigationResponse, void * decisionHandler) = 0 ;
	virtual void __cdecl webViewDidFailNavigation(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigation navigation, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl webViewDidFailProvisionalNavigation(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigation navigation, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl webViewDidFinishNavigation(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigation navigation) = 0 ;
	virtual void __cdecl webViewDidReceiveAuthenticationChallenge(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Foundation::_di_NSURLAuthenticationChallenge challenge, void * completionHandler) = 0 ;
	virtual void __cdecl webViewDidStartProvisionalNavigation(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigation navigation) = 0 ;
};

typedef Iosapi::Webkit::_di_WKWebView INativeWebView;

typedef Iosapi::Uikit::_di_UIView INativeView;

typedef Iosapi::Webkit::_di_WKWebView IMainFrame;

typedef unsigned long NativeCachePolicy;

typedef Iosapi::Webkit::_di_WKUIDelegate WebUIDelegate;

typedef Iosapi::Webkit::_di_WKNavigationDelegate WebNavigationDelegate;

typedef _di_WKUIDelegateSlim WebUIDelegateiOS;

typedef _di_WKNavigationDelegateSlim WebNavigationDelegateiOS;

class PASCALIMPLEMENTATION TWebViewDelegate : public Fmx::Webbrowser::Delegate::Cocoa::TBaseWebViewDelegate
{
	typedef Fmx::Webbrowser::Delegate::Cocoa::TBaseWebViewDelegate inherited;
	
private:
	Fmx::Webbrowser::TCustomWebBrowser* FWebBrowser;
	Fmx::Webbrowser::_di_ICustomBrowser FURLSetter;
	
public:
	void __cdecl webViewContextMenuConfigurationForElement(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKContextMenuElementInfo elementInfo, void * completionHandler);
	void __cdecl webViewContextMenuDidEndForElement(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKContextMenuElementInfo elementInfo);
	void __cdecl webViewContextMenuForElement(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKContextMenuElementInfo elementInfo, void * animator);
	void __cdecl webViewContextMenuWillPresentForElement(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKContextMenuElementInfo elementInfo);
	Iosapi::Webkit::_di_WKWebView __cdecl webViewCreateWebViewWithConfiguration(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKWebViewConfiguration configuration, Iosapi::Webkit::_di_WKNavigationAction navigationAction, Iosapi::Webkit::_di_WKWindowFeatures windowFeatures);
	void __cdecl webViewDidClose(Iosapi::Webkit::_di_WKWebView webView);
	void __cdecl webViewRunJavaScriptAlertPanelWithMessage(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Foundation::_di_NSString message, Iosapi::Webkit::_di_WKFrameInfo frame, void * completionHandler);
	void __cdecl webViewRunJavaScriptConfirmPanelWithMessage(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Foundation::_di_NSString message, Iosapi::Webkit::_di_WKFrameInfo frame, void * completionHandler);
	void __cdecl webViewRunJavaScriptTextInputPanelWithPrompt(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Foundation::_di_NSString prompt, Iosapi::Foundation::_di_NSString defaultText, Iosapi::Webkit::_di_WKFrameInfo frame, void * completionHandler);
	void __cdecl webViewDecidePolicyForNavigationAction(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigationAction navigationAction, void * decisionHandler)/* overload */;
	void __cdecl webViewDecidePolicyForNavigationResponse(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigationResponse navigationResponse, void * decisionHandler);
	void __cdecl webViewDidCommitNavigation(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigation navigation);
	void __cdecl webViewDidFailNavigation(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigation navigation, Iosapi::Foundation::_di_NSError error);
	void __cdecl webViewDidFailProvisionalNavigation(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigation navigation, Iosapi::Foundation::_di_NSError error);
	void __cdecl webViewDidFinishNavigation(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigation navigation);
	void __cdecl webViewDidReceiveAuthenticationChallenge(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Foundation::_di_NSURLAuthenticationChallenge challenge, void * completionHandler);
	void __cdecl webViewDidReceiveServerRedirectForProvisionalNavigation(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigation navigation);
	void __cdecl webViewDidStartProvisionalNavigation(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigation navigation);
	void __cdecl webViewWebContentProcessDidTerminate(Iosapi::Webkit::_di_WKWebView webView);
	__fastcall TWebViewDelegate();
	void __fastcall SetWebBrowser(Fmx::Webbrowser::TCustomWebBrowser* const AWebBrowser, const Fmx::Webbrowser::_di_ICustomBrowser AURLSetter);
public:
	/* TOCLocal.Destroy */ inline __fastcall virtual ~TWebViewDelegate() { }
	
private:
	void *__WKNavigationDelegate;	// Iosapi::Webkit::WKNavigationDelegate 
	void *__WKUIDelegate;	// Iosapi::Webkit::WKUIDelegate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FD874B6D-A9C0-4105-AB0D-56F12293565F}
	operator Iosapi::Webkit::_di_WKNavigationDelegate()
	{
		Iosapi::Webkit::_di_WKNavigationDelegate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Iosapi::Webkit::WKNavigationDelegate*(void) { return (Iosapi::Webkit::WKNavigationDelegate*)&__WKNavigationDelegate; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6F7C5692-ED85-4A65-A24D-BEB14164553D}
	operator Iosapi::Webkit::_di_WKUIDelegate()
	{
		Iosapi::Webkit::_di_WKUIDelegate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Iosapi::Webkit::WKUIDelegate*(void) { return (Iosapi::Webkit::WKUIDelegate*)&__WKUIDelegate; }
	#endif
	
};


class PASCALIMPLEMENTATION TWebViewDelegateiOS : public Fmx::Webbrowser::Delegate::Cocoa::TBaseWebViewDelegate
{
	typedef Fmx::Webbrowser::Delegate::Cocoa::TBaseWebViewDelegate inherited;
	
private:
	Fmx::Webbrowser::TCustomWebBrowser* FWebBrowser;
	Fmx::Webbrowser::_di_ICustomBrowser FURLSetter;
	
public:
	Iosapi::Webkit::_di_WKWebView __cdecl webViewCreateWebViewWithConfiguration(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKWebViewConfiguration configuration, Iosapi::Webkit::_di_WKNavigationAction navigationAction, Iosapi::Webkit::_di_WKWindowFeatures windowFeatures);
	void __cdecl webViewRunJavaScriptAlertPanelWithMessage(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Foundation::_di_NSString message, Iosapi::Webkit::_di_WKFrameInfo frame, void * completionHandler);
	void __cdecl webViewRunJavaScriptConfirmPanelWithMessage(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Foundation::_di_NSString message, Iosapi::Webkit::_di_WKFrameInfo frame, void * completionHandler);
	void __cdecl webViewRunJavaScriptTextInputPanelWithPrompt(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Foundation::_di_NSString prompt, Iosapi::Foundation::_di_NSString defaultText, Iosapi::Webkit::_di_WKFrameInfo frame, void * completionHandler);
	void __cdecl webViewDecidePolicyForNavigationAction(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigationAction navigationAction, void * decisionHandler)/* overload */;
	void __cdecl webViewDecidePolicyForNavigationResponse(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigationResponse navigationResponse, void * decisionHandler);
	void __cdecl webViewDidFailNavigation(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigation navigation, Iosapi::Foundation::_di_NSError error);
	void __cdecl webViewDidFailProvisionalNavigation(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigation navigation, Iosapi::Foundation::_di_NSError error);
	void __cdecl webViewDidFinishNavigation(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigation navigation);
	void __cdecl webViewDidReceiveAuthenticationChallenge(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Foundation::_di_NSURLAuthenticationChallenge challenge, void * completionHandler);
	void __cdecl webViewDidStartProvisionalNavigation(Iosapi::Webkit::_di_WKWebView webView, Iosapi::Webkit::_di_WKNavigation navigation);
	__fastcall TWebViewDelegateiOS();
	void __fastcall SetWebBrowser(Fmx::Webbrowser::TCustomWebBrowser* const AWebBrowser, const Fmx::Webbrowser::_di_ICustomBrowser AURLSetter);
public:
	/* TOCLocal.Destroy */ inline __fastcall virtual ~TWebViewDelegateiOS() { }
	
private:
	void *__WKNavigationDelegateSlim;	// WKNavigationDelegateSlim 
	void *__WKUIDelegateSlim;	// WKUIDelegateSlim 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7FDDD993-8024-478B-930D-334AFEF0CA16}
	operator _di_WKNavigationDelegateSlim()
	{
		_di_WKNavigationDelegateSlim intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator WKNavigationDelegateSlim*(void) { return (WKNavigationDelegateSlim*)&__WKNavigationDelegateSlim; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A0FEDEBE-6023-4FBE-897A-9C005E83934B}
	operator _di_WKUIDelegateSlim()
	{
		_di_WKUIDelegateSlim intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator WKUIDelegateSlim*(void) { return (WKUIDelegateSlim*)&__WKUIDelegateSlim; }
	#endif
	
};


class PASCALIMPLEMENTATION TNativeWebViewHelper : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod Iosapi::Webkit::_di_WKWebView __fastcall CreateAndInitWebView();
	__classmethod Iosapi::Webkit::_di_WKWebView __fastcall MainFrame(const Iosapi::Webkit::_di_WKWebView ANativeWebView);
	__classmethod void __fastcall SetBounds(const Iosapi::Webkit::_di_WKWebView ANativeWebView, const System::Types::TRectF &ABounds, const float AHeight = 0.000000E+00f);
public:
	/* TObject.Create */ inline __fastcall TNativeWebViewHelper() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TNativeWebViewHelper() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Delegate */
}	/* namespace Webbrowser */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_WEBBROWSER_DELEGATE_IOS)
using namespace Fmx::Webbrowser::Delegate::Ios;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_WEBBROWSER_DELEGATE)
using namespace Fmx::Webbrowser::Delegate;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_WEBBROWSER)
using namespace Fmx::Webbrowser;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Webbrowser_Delegate_IosHPP
