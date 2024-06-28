// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.WebBrowser.pas' rev: 34.00 (Android)

#ifndef Fmx_WebbrowserHPP
#define Fmx_WebbrowserHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Messaging.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Graphics.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Webbrowser
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EWebManagerException;
__interface DELPHIINTERFACE ICustomBrowser;
typedef System::DelphiInterface<ICustomBrowser> _di_ICustomBrowser;
__interface DELPHIINTERFACE ICustomBrowserEx;
typedef System::DelphiInterface<ICustomBrowserEx> _di_ICustomBrowserEx;
__interface DELPHIINTERFACE IFMXWBService;
typedef System::DelphiInterface<IFMXWBService> _di_IFMXWBService;
class DELPHICLASS TCustomWebBrowser;
struct TCustomWebBrowserHelper /* Helper for class 'TCustomWebBrowser*' */;
class DELPHICLASS TWBFactoryService;
class DELPHICLASS TWebBrowser;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EWebManagerException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EWebManagerException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EWebManagerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWebManagerException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWebManagerException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWebManagerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWebManagerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWebManagerException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWebManagerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWebManagerException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWebManagerException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWebManagerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWebManagerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWebManagerException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (__closure *TWebBrowserDidStartLoad)(System::TObject* ASender);

typedef void __fastcall (__closure *TWebBrowserDidFinishLoad)(System::TObject* ASender);

typedef void __fastcall (__closure *TWebBrowserDidFailLoadWithError)(System::TObject* ASender);

typedef void __fastcall (__closure *TWebBrowserShouldStartLoadWithRequest)(System::TObject* ASender, const System::UnicodeString URL);

__interface  INTERFACE_UUID("{A5BB2E8C-6D53-4FF3-BC38-2299285F07BD}") ICustomBrowser  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall GetURL() = 0 ;
	virtual Fmx::Graphics::TBitmap* __fastcall CaptureBitmap() = 0 ;
	virtual bool __fastcall GetCanGoBack() = 0 ;
	virtual bool __fastcall GetCanGoForward() = 0 ;
	virtual void __fastcall SetURL(const System::UnicodeString AValue) = 0 ;
	virtual bool __fastcall GetEnableCaching() = 0 ;
	virtual void __fastcall SetEnableCaching(const bool Value) = 0 ;
	virtual void __fastcall SetWebBrowserControl(TCustomWebBrowser* const AValue) = 0 ;
	virtual Fmx::Types::TFmxObject* __fastcall GetParent() = 0 ;
	virtual bool __fastcall GetVisible() = 0 ;
	virtual void __fastcall UpdateContentFromControl() = 0 ;
	virtual void __fastcall Navigate() = 0 ;
	virtual void __fastcall Reload() = 0 ;
	virtual void __fastcall Stop() = 0 ;
	virtual void __fastcall EvaluateJavaScript(const System::UnicodeString JavaScript) = 0 ;
	virtual void __fastcall LoadFromStrings(const System::UnicodeString Content, const System::UnicodeString BaseUrl) = 0 ;
	virtual void __fastcall GoBack() = 0 ;
	virtual void __fastcall GoForward() = 0 ;
	virtual void __fastcall GoHome() = 0 ;
	virtual void __fastcall Show() = 0 ;
	virtual void __fastcall Hide() = 0 ;
	__property System::UnicodeString URL = {read=GetURL, write=SetURL};
	__property bool EnableCaching = {read=GetEnableCaching, write=SetEnableCaching};
	__property bool CanGoBack = {read=GetCanGoBack};
	__property bool CanGoForward = {read=GetCanGoForward};
};

__interface  INTERFACE_UUID("{5F61E8E6-54B5-4305-88DD-C7F8086352FF}") ICustomBrowserEx  : public System::IInterface 
{
	virtual void __fastcall LoadFromStrings(const System::UnicodeString Content, System::Sysutils::TEncoding* const ContentEncoding, const System::UnicodeString BaseUrl) = 0 ;
};

__interface  INTERFACE_UUID("{61BC1956-BAA0-4B07-971D-EF40064FBD07}") IFMXWBService  : public System::IInterface 
{
	virtual _di_ICustomBrowser __fastcall CreateWebBrowser() = 0 ;
	virtual void __fastcall RealignBrowsers() = 0 ;
	virtual void __fastcall DestroyWebBrowser(const _di_ICustomBrowser AWebBrowser) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomWebBrowser : public Fmx::Controls::TControl
{
	typedef Fmx::Controls::TControl inherited;
	
private:
	void __fastcall FormHandleCreated(System::TObject* const Sender, System::Messaging::TMessageBase* const Msg);
	_di_ICustomBrowser FWeb;
	System::UnicodeString FURL;
	bool FEnableCaching;
	TWebBrowserDidStartLoad FOnDidStartLoad;
	TWebBrowserDidFinishLoad FOnDidFinishLoad;
	TWebBrowserDidFailLoadWithError FOnDidFailLoadWithError;
	TWebBrowserShouldStartLoadWithRequest FOnShouldStartLoadWithRequest;
	bool FSavedVisible;
	System::UnicodeString __fastcall GetURL();
	bool __fastcall GetCanGoBack();
	bool __fastcall GetCanGoForward();
	void __fastcall SetURL(const System::UnicodeString Value);
	void __fastcall UpdateContent();
	bool __fastcall GetEnableCaching();
	void __fastcall SetEnableCaching(const bool Value);
	
protected:
	virtual HRESULT __stdcall QueryInterface(const GUID IID, /* out */ void *Obj);
	virtual void __fastcall AncestorVisibleChanged(const bool Visible);
	virtual void __fastcall ParentChanged();
	virtual void __fastcall DoAbsoluteChanged();
	virtual void __fastcall Move();
	virtual void __fastcall Resize();
	virtual void __fastcall Paint();
	virtual void __fastcall Show();
	virtual void __fastcall Hide();
	virtual void __fastcall ChangeOrder();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	TWebBrowserDidStartLoad __fastcall GetOnDidStartLoad();
	void __fastcall SetOnDidStartLoad(const TWebBrowserDidStartLoad AEvent);
	TWebBrowserDidFinishLoad __fastcall GetOnDidFinishLoad();
	void __fastcall SetOnDidFinishLoad(const TWebBrowserDidFinishLoad AEvent);
	TWebBrowserShouldStartLoadWithRequest __fastcall GetOnShouldStartLoadWithRequest();
	void __fastcall SetOnShouldStartLoadWithRequest(const TWebBrowserShouldStartLoadWithRequest AEvent);
	TWebBrowserDidFailLoadWithError __fastcall GetOnDidFailLoadWithError();
	void __fastcall SetOnDidFailLoadWithError(const TWebBrowserDidFailLoadWithError AEvent);
	virtual void __fastcall SetVisible(const bool Value);
	
public:
	#define TCustomWebBrowser_FilesPref u"file://"
	
	__fastcall virtual TCustomWebBrowser(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomWebBrowser();
	void __fastcall StartLoading();
	void __fastcall FinishLoading();
	void __fastcall FailLoadingWithError();
	void __fastcall ShouldStartLoading(const System::UnicodeString URL);
	Fmx::Graphics::TBitmap* __fastcall CaptureBitmap();
	void __fastcall GoBack();
	void __fastcall GoForward();
	void __fastcall Navigate()/* overload */;
	void __fastcall Navigate(const System::UnicodeString AURL)/* overload */;
	void __fastcall Reload()/* overload */;
	void __fastcall Stop();
	void __fastcall LoadFromStrings(const System::UnicodeString Content, const System::UnicodeString BaseUrl);
	void __fastcall EvaluateJavaScript(const System::UnicodeString JavaScript);
	__property bool EnableCaching = {read=GetEnableCaching, write=SetEnableCaching, default=1};
	__property System::UnicodeString URL = {read=GetURL, write=SetURL};
	__property bool CanGoBack = {read=GetCanGoBack, default=0};
	__property bool CanGoForward = {read=GetCanGoForward, default=0};
	__property TWebBrowserDidStartLoad OnDidStartLoad = {read=GetOnDidStartLoad, write=SetOnDidStartLoad};
	__property TWebBrowserDidFinishLoad OnDidFinishLoad = {read=GetOnDidFinishLoad, write=SetOnDidFinishLoad};
	__property TWebBrowserShouldStartLoadWithRequest OnShouldStartLoadWithRequest = {read=GetOnShouldStartLoadWithRequest, write=SetOnShouldStartLoadWithRequest};
	__property TWebBrowserDidFailLoadWithError OnDidFailLoadWithError = {read=GetOnDidFailLoadWithError, write=SetOnDidFailLoadWithError};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TWBFactoryService : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	void __fastcall FormActivateHandler(System::TObject* const Sender, System::Messaging::TMessageBase* const M);
	
protected:
	System::Generics::Collections::TList__1<_di_ICustomBrowser>* FWebBrowsers;
	virtual _di_ICustomBrowser __fastcall DoCreateWebBrowser() = 0 ;
	void __fastcall DoRemoveWebBrowser(const _di_ICustomBrowser AWebBrowser);
	void __fastcall RealignBrowsers();
	
public:
	__fastcall TWBFactoryService();
	__fastcall virtual ~TWBFactoryService();
	_di_ICustomBrowser __fastcall CreateWebBrowser();
	void __fastcall DestroyWebBrowser(const _di_ICustomBrowser AWebBrowser);
private:
	void *__IFMXWBService;	// IFMXWBService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {61BC1956-BAA0-4B07-971D-EF40064FBD07}
	operator _di_IFMXWBService()
	{
		_di_IFMXWBService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IFMXWBService*(void) { return (IFMXWBService*)&__IFMXWBService; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TWebBrowser : public TCustomWebBrowser
{
	typedef TCustomWebBrowser inherited;
	
__published:
	__property EnableCaching = {default=1};
	__property Align = {default=0};
	__property Anchors;
	__property Height;
	__property Size;
	__property Margins;
	__property Position;
	__property URL = {default=0};
	__property Visible = {default=1};
	__property CanFocus = {default=1};
	__property Width;
	__property OnDidStartLoad;
	__property OnDidFinishLoad;
	__property OnDidFailLoadWithError;
	__property OnShouldStartLoadWithRequest;
public:
	/* TCustomWebBrowser.Create */ inline __fastcall virtual TWebBrowser(System::Classes::TComponent* AOwner) : TCustomWebBrowser(AOwner) { }
	/* TCustomWebBrowser.Destroy */ inline __fastcall virtual ~TWebBrowser() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Webbrowser */
}	/* namespace Fmx */
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
#endif	// Fmx_WebbrowserHPP
