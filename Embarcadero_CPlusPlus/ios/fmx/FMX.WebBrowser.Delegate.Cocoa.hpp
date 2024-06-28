// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.WebBrowser.Delegate.Cocoa.pas' rev: 34.00 (iOS)

#ifndef Fmx_Webbrowser_Delegate_CocoaHPP
#define Fmx_Webbrowser_Delegate_CocoaHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.Foundation.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Webbrowser
{
namespace Delegate
{
namespace Cocoa
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE TJavaScriptConfirmationResponseProc;
typedef System::DelphiInterface<TJavaScriptConfirmationResponseProc> _di_TJavaScriptConfirmationResponseProc;
__interface DELPHIINTERFACE TJavaScriptInformationResponseProc;
typedef System::DelphiInterface<TJavaScriptInformationResponseProc> _di_TJavaScriptInformationResponseProc;
__interface DELPHIINTERFACE TJavaScriptInputQueryResponseProc;
typedef System::DelphiInterface<TJavaScriptInputQueryResponseProc> _di_TJavaScriptInputQueryResponseProc;
__interface DELPHIINTERFACE TAuthenticationResponseProc;
typedef System::DelphiInterface<TAuthenticationResponseProc> _di_TAuthenticationResponseProc;
class DELPHICLASS TBaseWebViewDelegate;
//-- type declarations -------------------------------------------------------
__interface TJavaScriptConfirmationResponseProc  : public System::IInterface 
{
	virtual void __fastcall Invoke(const bool AResponse) = 0 ;
};

__interface TJavaScriptInformationResponseProc  : public System::IInterface 
{
	virtual void __fastcall Invoke() = 0 ;
};

__interface TJavaScriptInputQueryResponseProc  : public System::IInterface 
{
	virtual void __fastcall Invoke(const Iosapi::Foundation::_di_NSString AResponse) = 0 ;
};

__interface TAuthenticationResponseProc  : public System::IInterface 
{
	virtual void __fastcall Invoke(const Iosapi::Foundation::_di_NSURLCredential ACredential) = 0 ;
};

class PASCALIMPLEMENTATION TBaseWebViewDelegate : public Macapi::Objectivec::TOCLocal
{
	typedef Macapi::Objectivec::TOCLocal inherited;
	
public:
	void __fastcall AuthenticateForHost(const Iosapi::Foundation::_di_NSString AHost, const _di_TAuthenticationResponseProc AResponseProc);
	void __fastcall JavaScriptConfirmationMessage(const Iosapi::Foundation::_di_NSString AMessage, const _di_TJavaScriptConfirmationResponseProc AResponseProc);
	void __fastcall JavaScriptInformationMessage(const Iosapi::Foundation::_di_NSString AMessage, const _di_TJavaScriptInformationResponseProc AResponseProc);
	void __fastcall JavaScriptInputQuery(const Iosapi::Foundation::_di_NSString AMessage, const Iosapi::Foundation::_di_NSString ADefaultText, const _di_TJavaScriptInputQueryResponseProc AResponseProc);
protected:
	/* TOCLocal.Create */ inline __fastcall TBaseWebViewDelegate() : Macapi::Objectivec::TOCLocal() { }
	
public:
	/* TOCLocal.Destroy */ inline __fastcall virtual ~TBaseWebViewDelegate() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Cocoa */
}	/* namespace Delegate */
}	/* namespace Webbrowser */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_WEBBROWSER_DELEGATE_COCOA)
using namespace Fmx::Webbrowser::Delegate::Cocoa;
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
#endif	// Fmx_Webbrowser_Delegate_CocoaHPP
