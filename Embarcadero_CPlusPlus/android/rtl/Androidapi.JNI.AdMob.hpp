// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.AdMob.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_AdmobHPP
#define Androidapi_Jni_AdmobHPP

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
#include <Androidapi.JNI.Location.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.JNI.Util.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Admob
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JAdActivityClass;
typedef System::DelphiInterface<JAdActivityClass> _di_JAdActivityClass;
__interface DELPHIINTERFACE JAdActivity;
typedef System::DelphiInterface<JAdActivity> _di_JAdActivity;
class DELPHICLASS TJAdActivity;
__interface DELPHIINTERFACE JAdListenerClass;
typedef System::DelphiInterface<JAdListenerClass> _di_JAdListenerClass;
__interface DELPHIINTERFACE JAdListener;
typedef System::DelphiInterface<JAdListener> _di_JAdListener;
class DELPHICLASS TJAdListener;
__interface DELPHIINTERFACE JAdRequestClass;
typedef System::DelphiInterface<JAdRequestClass> _di_JAdRequestClass;
__interface DELPHIINTERFACE JAdRequest;
typedef System::DelphiInterface<JAdRequest> _di_JAdRequest;
class DELPHICLASS TJAdRequest;
__interface DELPHIINTERFACE JAdRequest_BuilderClass;
typedef System::DelphiInterface<JAdRequest_BuilderClass> _di_JAdRequest_BuilderClass;
__interface DELPHIINTERFACE JAdRequest_Builder;
typedef System::DelphiInterface<JAdRequest_Builder> _di_JAdRequest_Builder;
class DELPHICLASS TJAdRequest_Builder;
__interface DELPHIINTERFACE JAdSizeClass;
typedef System::DelphiInterface<JAdSizeClass> _di_JAdSizeClass;
__interface DELPHIINTERFACE JAdSize;
typedef System::DelphiInterface<JAdSize> _di_JAdSize;
class DELPHICLASS TJAdSize;
__interface DELPHIINTERFACE JAdViewClass;
typedef System::DelphiInterface<JAdViewClass> _di_JAdViewClass;
__interface DELPHIINTERFACE JAdView;
typedef System::DelphiInterface<JAdView> _di_JAdView;
class DELPHICLASS TJAdView;
__interface DELPHIINTERFACE JInterstitialAdClass;
typedef System::DelphiInterface<JInterstitialAdClass> _di_JInterstitialAdClass;
__interface DELPHIINTERFACE JInterstitialAd;
typedef System::DelphiInterface<JInterstitialAd> _di_JInterstitialAd;
class DELPHICLASS TJInterstitialAd;
__interface DELPHIINTERFACE JAppEventListenerClass;
typedef System::DelphiInterface<JAppEventListenerClass> _di_JAppEventListenerClass;
__interface DELPHIINTERFACE JAppEventListener;
typedef System::DelphiInterface<JAppEventListener> _di_JAppEventListener;
class DELPHICLASS TJAppEventListener;
__interface DELPHIINTERFACE JCustomRenderedAdClass;
typedef System::DelphiInterface<JCustomRenderedAdClass> _di_JCustomRenderedAdClass;
__interface DELPHIINTERFACE JCustomRenderedAd;
typedef System::DelphiInterface<JCustomRenderedAd> _di_JCustomRenderedAd;
class DELPHICLASS TJCustomRenderedAd;
__interface DELPHIINTERFACE JOnCustomRenderedAdLoadedListenerClass;
typedef System::DelphiInterface<JOnCustomRenderedAdLoadedListenerClass> _di_JOnCustomRenderedAdLoadedListenerClass;
__interface DELPHIINTERFACE JOnCustomRenderedAdLoadedListener;
typedef System::DelphiInterface<JOnCustomRenderedAdLoadedListener> _di_JOnCustomRenderedAdLoadedListener;
class DELPHICLASS TJOnCustomRenderedAdLoadedListener;
__interface DELPHIINTERFACE JPublisherAdRequestClass;
typedef System::DelphiInterface<JPublisherAdRequestClass> _di_JPublisherAdRequestClass;
__interface DELPHIINTERFACE JPublisherAdRequest;
typedef System::DelphiInterface<JPublisherAdRequest> _di_JPublisherAdRequest;
class DELPHICLASS TJPublisherAdRequest;
__interface DELPHIINTERFACE JPublisherAdRequest_BuilderClass;
typedef System::DelphiInterface<JPublisherAdRequest_BuilderClass> _di_JPublisherAdRequest_BuilderClass;
__interface DELPHIINTERFACE JPublisherAdRequest_Builder;
typedef System::DelphiInterface<JPublisherAdRequest_Builder> _di_JPublisherAdRequest_Builder;
class DELPHICLASS TJPublisherAdRequest_Builder;
__interface DELPHIINTERFACE JPublisherAdViewClass;
typedef System::DelphiInterface<JPublisherAdViewClass> _di_JPublisherAdViewClass;
__interface DELPHIINTERFACE JPublisherAdView;
typedef System::DelphiInterface<JPublisherAdView> _di_JPublisherAdView;
class DELPHICLASS TJPublisherAdView;
__interface DELPHIINTERFACE JPublisherInterstitialAdClass;
typedef System::DelphiInterface<JPublisherInterstitialAdClass> _di_JPublisherInterstitialAdClass;
__interface DELPHIINTERFACE JPublisherInterstitialAd;
typedef System::DelphiInterface<JPublisherInterstitialAd> _di_JPublisherInterstitialAd;
class DELPHICLASS TJPublisherInterstitialAd;
__interface DELPHIINTERFACE JInAppPurchaseClass;
typedef System::DelphiInterface<JInAppPurchaseClass> _di_JInAppPurchaseClass;
__interface DELPHIINTERFACE JInAppPurchase;
typedef System::DelphiInterface<JInAppPurchase> _di_JInAppPurchase;
class DELPHICLASS TJInAppPurchase;
__interface DELPHIINTERFACE JInAppPurchaseActivityClass;
typedef System::DelphiInterface<JInAppPurchaseActivityClass> _di_JInAppPurchaseActivityClass;
__interface DELPHIINTERFACE JInAppPurchaseActivity;
typedef System::DelphiInterface<JInAppPurchaseActivity> _di_JInAppPurchaseActivity;
class DELPHICLASS TJInAppPurchaseActivity;
__interface DELPHIINTERFACE JInAppPurchaseListenerClass;
typedef System::DelphiInterface<JInAppPurchaseListenerClass> _di_JInAppPurchaseListenerClass;
__interface DELPHIINTERFACE JInAppPurchaseListener;
typedef System::DelphiInterface<JInAppPurchaseListener> _di_JInAppPurchaseListener;
class DELPHICLASS TJInAppPurchaseListener;
__interface DELPHIINTERFACE JInAppPurchaseResultClass;
typedef System::DelphiInterface<JInAppPurchaseResultClass> _di_JInAppPurchaseResultClass;
__interface DELPHIINTERFACE JInAppPurchaseResult;
typedef System::DelphiInterface<JInAppPurchaseResult> _di_JInAppPurchaseResult;
class DELPHICLASS TJInAppPurchaseResult;
__interface DELPHIINTERFACE JPlayStorePurchaseListenerClass;
typedef System::DelphiInterface<JPlayStorePurchaseListenerClass> _di_JPlayStorePurchaseListenerClass;
__interface DELPHIINTERFACE JPlayStorePurchaseListener;
typedef System::DelphiInterface<JPlayStorePurchaseListener> _di_JPlayStorePurchaseListener;
class DELPHICLASS TJPlayStorePurchaseListener;
__interface DELPHIINTERFACE JSearchAdRequestClass;
typedef System::DelphiInterface<JSearchAdRequestClass> _di_JSearchAdRequestClass;
__interface DELPHIINTERFACE JSearchAdRequest;
typedef System::DelphiInterface<JSearchAdRequest> _di_JSearchAdRequest;
class DELPHICLASS TJSearchAdRequest;
__interface DELPHIINTERFACE JSearchAdRequest_BuilderClass;
typedef System::DelphiInterface<JSearchAdRequest_BuilderClass> _di_JSearchAdRequest_BuilderClass;
__interface DELPHIINTERFACE JSearchAdRequest_Builder;
typedef System::DelphiInterface<JSearchAdRequest_Builder> _di_JSearchAdRequest_Builder;
class DELPHICLASS TJSearchAdRequest_Builder;
__interface DELPHIINTERFACE JSearchAdViewClass;
typedef System::DelphiInterface<JSearchAdViewClass> _di_JSearchAdViewClass;
__interface DELPHIINTERFACE JSearchAdView;
typedef System::DelphiInterface<JSearchAdView> _di_JSearchAdView;
class DELPHICLASS TJSearchAdView;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{439F386F-D57B-41AA-917E-392A23F51ECE}") JAdActivityClass  : public Androidapi::Jni::App::JActivityClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCLASS_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSIMPLE_CLASS_NAME() = 0 ;
	HIDESBASE virtual _di_JAdActivity __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString CLASS_NAME = {read=_GetCLASS_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString SIMPLE_CLASS_NAME = {read=_GetSIMPLE_CLASS_NAME};
};

__interface  INTERFACE_UUID("{82CE84CE-F616-41F0-88ED-D53DBE675F15}") JAdActivity  : public Androidapi::Jni::App::JActivity 
{
	HIDESBASE virtual void __cdecl setContentView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 /* overload */;
	HIDESBASE virtual void __cdecl setContentView(int layoutResID) = 0 /* overload */;
	HIDESBASE virtual void __cdecl setContentView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_LayoutParams params) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdActivity : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdActivityClass,_di_JAdActivity>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdActivityClass,_di_JAdActivity> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdActivity() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdActivityClass,_di_JAdActivity>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdActivity() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{22D3BB99-7931-49A5-B29C-893667600EFD}") JAdListenerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JAdListener __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{62EE9CD8-6B80-4046-A01D-5AFDFC095925}") JAdListener  : public Androidapi::Jni::Javatypes::JObject 
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
class PASCALIMPLEMENTATION TJAdListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdListenerClass,_di_JAdListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdListenerClass,_di_JAdListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdListenerClass,_di_JAdListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{83BBA0E5-5A1B-4C4E-8174-BF55FB897504}") JAdRequestClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDEVICE_ID_EMULATOR() = 0 ;
	virtual int __cdecl _GetERROR_CODE_INTERNAL_ERROR() = 0 ;
	virtual int __cdecl _GetERROR_CODE_INVALID_REQUEST() = 0 ;
	virtual int __cdecl _GetERROR_CODE_NETWORK_ERROR() = 0 ;
	virtual int __cdecl _GetERROR_CODE_NO_FILL() = 0 ;
	virtual int __cdecl _GetGENDER_FEMALE() = 0 ;
	virtual int __cdecl _GetGENDER_MALE() = 0 ;
	virtual int __cdecl _GetGENDER_UNKNOWN() = 0 ;
	virtual int __cdecl _GetMAX_CONTENT_URL_LENGTH() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString DEVICE_ID_EMULATOR = {read=_GetDEVICE_ID_EMULATOR};
	__property int ERROR_CODE_INTERNAL_ERROR = {read=_GetERROR_CODE_INTERNAL_ERROR};
	__property int ERROR_CODE_INVALID_REQUEST = {read=_GetERROR_CODE_INVALID_REQUEST};
	__property int ERROR_CODE_NETWORK_ERROR = {read=_GetERROR_CODE_NETWORK_ERROR};
	__property int ERROR_CODE_NO_FILL = {read=_GetERROR_CODE_NO_FILL};
	__property int GENDER_FEMALE = {read=_GetGENDER_FEMALE};
	__property int GENDER_MALE = {read=_GetGENDER_MALE};
	__property int GENDER_UNKNOWN = {read=_GetGENDER_UNKNOWN};
	__property int MAX_CONTENT_URL_LENGTH = {read=_GetMAX_CONTENT_URL_LENGTH};
};

__interface  INTERFACE_UUID("{6A952D89-493B-4EC3-9B2D-419540C3E919}") JAdRequest  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JDate __cdecl getBirthday() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getContentUrl() = 0 ;
	virtual int __cdecl getGender() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JSet __cdecl getKeywords() = 0 ;
	virtual Androidapi::Jni::Location::_di_JLocation __cdecl getLocation() = 0 ;
	virtual bool __cdecl isTestDevice(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdRequest : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdRequestClass,_di_JAdRequest>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdRequestClass,_di_JAdRequest> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdRequest() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdRequestClass,_di_JAdRequest>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdRequest() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{31A61751-C547-4A56-AB61-F867EBA5961D}") JAdRequest_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JAdRequest_Builder __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{983C6775-921E-4A57-B560-F364B7D60ADC}") JAdRequest_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JAdRequest_Builder __cdecl addKeyword(Androidapi::Jni::Javatypes::_di_JString keyword) = 0 ;
	virtual _di_JAdRequest_Builder __cdecl addTestDevice(Androidapi::Jni::Javatypes::_di_JString deviceId) = 0 ;
	virtual _di_JAdRequest __cdecl build() = 0 ;
	virtual _di_JAdRequest_Builder __cdecl setBirthday(Androidapi::Jni::Javatypes::_di_JDate birthday) = 0 ;
	virtual _di_JAdRequest_Builder __cdecl setContentUrl(Androidapi::Jni::Javatypes::_di_JString contentUrl) = 0 ;
	virtual _di_JAdRequest_Builder __cdecl setGender(int gender) = 0 ;
	virtual _di_JAdRequest_Builder __cdecl setLocation(Androidapi::Jni::Location::_di_JLocation location) = 0 ;
	virtual _di_JAdRequest_Builder __cdecl setRequestAgent(Androidapi::Jni::Javatypes::_di_JString requestAgent) = 0 ;
	virtual _di_JAdRequest_Builder __cdecl tagForChildDirectedTreatment(bool tagForChildDirectedTreatment) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdRequest_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdRequest_BuilderClass,_di_JAdRequest_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdRequest_BuilderClass,_di_JAdRequest_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdRequest_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdRequest_BuilderClass,_di_JAdRequest_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdRequest_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3A15A6B8-8EB9-49BA-9FD9-6B8D507F7707}") JAdSizeClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetAUTO_HEIGHT() = 0 ;
	virtual _di_JAdSize __cdecl _GetBANNER() = 0 ;
	virtual _di_JAdSize __cdecl _GetFULL_BANNER() = 0 ;
	virtual int __cdecl _GetFULL_WIDTH() = 0 ;
	virtual _di_JAdSize __cdecl _GetLARGE_BANNER() = 0 ;
	virtual _di_JAdSize __cdecl _GetLEADERBOARD() = 0 ;
	virtual _di_JAdSize __cdecl _GetMEDIUM_RECTANGLE() = 0 ;
	virtual _di_JAdSize __cdecl _GetSMART_BANNER() = 0 ;
	virtual _di_JAdSize __cdecl _GetWIDE_SKYSCRAPER() = 0 ;
	HIDESBASE virtual _di_JAdSize __cdecl init(int width, int height) = 0 ;
	__property int AUTO_HEIGHT = {read=_GetAUTO_HEIGHT};
	__property _di_JAdSize BANNER = {read=_GetBANNER};
	__property _di_JAdSize FULL_BANNER = {read=_GetFULL_BANNER};
	__property int FULL_WIDTH = {read=_GetFULL_WIDTH};
	__property _di_JAdSize LARGE_BANNER = {read=_GetLARGE_BANNER};
	__property _di_JAdSize LEADERBOARD = {read=_GetLEADERBOARD};
	__property _di_JAdSize MEDIUM_RECTANGLE = {read=_GetMEDIUM_RECTANGLE};
	__property _di_JAdSize SMART_BANNER = {read=_GetSMART_BANNER};
	__property _di_JAdSize WIDE_SKYSCRAPER = {read=_GetWIDE_SKYSCRAPER};
};

__interface  INTERFACE_UUID("{6A30E519-3C74-464C-B145-C0A6A02B3093}") JAdSize  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject other) = 0 ;
	virtual int __cdecl getHeight() = 0 ;
	virtual int __cdecl getHeightInPixels(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual int __cdecl getWidth() = 0 ;
	virtual int __cdecl getWidthInPixels(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isAutoHeight() = 0 ;
	virtual bool __cdecl isFullWidth() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdSize : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdSizeClass,_di_JAdSize>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdSizeClass,_di_JAdSize> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdSize() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdSizeClass,_di_JAdSize>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdSize() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D2A51E0D-437B-4F72-8826-BCCCBF315647}") JAdViewClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroupClass 
{
	HIDESBASE virtual _di_JAdView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JAdView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JAdView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyle) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{58156621-09A0-4178-81FD-9349FD929B6B}") JAdView  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup 
{
	virtual void __cdecl destroy() = 0 ;
	virtual _di_JAdListener __cdecl getAdListener() = 0 ;
	virtual _di_JAdSize __cdecl getAdSize() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAdUnitId() = 0 ;
	virtual _di_JInAppPurchaseListener __cdecl getInAppPurchaseListener() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMediationAdapterClassName() = 0 ;
	virtual void __cdecl loadAd(_di_JAdRequest adRequest) = 0 ;
	virtual void __cdecl pause() = 0 ;
	virtual void __cdecl resume() = 0 ;
	virtual void __cdecl setAdListener(_di_JAdListener adListener) = 0 ;
	virtual void __cdecl setAdSize(_di_JAdSize adSize) = 0 ;
	virtual void __cdecl setAdUnitId(Androidapi::Jni::Javatypes::_di_JString adUnitId) = 0 ;
	virtual void __cdecl setInAppPurchaseListener(_di_JInAppPurchaseListener inAppPurchaseListener) = 0 ;
	virtual void __cdecl setPlayStorePurchaseParams(_di_JPlayStorePurchaseListener playStorePurchaseListener, Androidapi::Jni::Javatypes::_di_JString publicKey) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdViewClass,_di_JAdView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdViewClass,_di_JAdView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdViewClass,_di_JAdView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8AA805B5-8169-45DD-9FAD-C70BB5569A57}") JInterstitialAdClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JInterstitialAd __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

__interface  INTERFACE_UUID("{72B51FC0-FDA8-4006-8804-C15126DE4CEA}") JInterstitialAd  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JAdListener __cdecl getAdListener() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAdUnitId() = 0 ;
	virtual _di_JInAppPurchaseListener __cdecl getInAppPurchaseListener() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMediationAdapterClassName() = 0 ;
	virtual bool __cdecl isLoaded() = 0 ;
	virtual void __cdecl loadAd(_di_JAdRequest adRequest) = 0 ;
	virtual void __cdecl setAdListener(_di_JAdListener adListener) = 0 ;
	virtual void __cdecl setAdUnitId(Androidapi::Jni::Javatypes::_di_JString adUnitId) = 0 ;
	virtual void __cdecl setInAppPurchaseListener(_di_JInAppPurchaseListener inAppPurchaseListener) = 0 ;
	virtual void __cdecl setPlayStorePurchaseParams(_di_JPlayStorePurchaseListener playStorePurchaseListener, Androidapi::Jni::Javatypes::_di_JString publicKey) = 0 ;
	virtual void __cdecl show() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInterstitialAd : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInterstitialAdClass,_di_JInterstitialAd>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInterstitialAdClass,_di_JInterstitialAd> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInterstitialAd() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInterstitialAdClass,_di_JInterstitialAd>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInterstitialAd() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F042C944-4B7A-48D2-83C0-FFC09FC1DCE7}") JAppEventListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{DEB88D3D-276B-4A03-93C1-CA9412699C9A}") JAppEventListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onAppEvent(Androidapi::Jni::Javatypes::_di_JString var1, Androidapi::Jni::Javatypes::_di_JString var2) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAppEventListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAppEventListenerClass,_di_JAppEventListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAppEventListenerClass,_di_JAppEventListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAppEventListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAppEventListenerClass,_di_JAppEventListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAppEventListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5CAC8F91-3E48-416F-98AC-064E4E170DF4}") JCustomRenderedAdClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{07845FA9-F639-4508-8837-AAF33C32C965}") JCustomRenderedAd  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getBaseUrl() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getContent() = 0 ;
	virtual void __cdecl onAdRendered(Androidapi::Jni::Graphicscontentviewtext::_di_JView var1) = 0 ;
	virtual void __cdecl recordClick() = 0 ;
	virtual void __cdecl recordImpression() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCustomRenderedAd : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCustomRenderedAdClass,_di_JCustomRenderedAd>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCustomRenderedAdClass,_di_JCustomRenderedAd> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCustomRenderedAd() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCustomRenderedAdClass,_di_JCustomRenderedAd>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCustomRenderedAd() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{31D37E94-2013-48EA-AD77-8CFCEA114133}") JOnCustomRenderedAdLoadedListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{BB54CF6D-E855-4B0D-A3B1-32D44FEA4F05}") JOnCustomRenderedAdLoadedListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCustomRenderedAdLoaded(_di_JCustomRenderedAd var1) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnCustomRenderedAdLoadedListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnCustomRenderedAdLoadedListenerClass,_di_JOnCustomRenderedAdLoadedListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnCustomRenderedAdLoadedListenerClass,_di_JOnCustomRenderedAdLoadedListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnCustomRenderedAdLoadedListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnCustomRenderedAdLoadedListenerClass,_di_JOnCustomRenderedAdLoadedListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnCustomRenderedAdLoadedListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{39D1125A-4F6A-4732-B0D0-E729502DC81D}") JPublisherAdRequestClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDEVICE_ID_EMULATOR() = 0 ;
	virtual int __cdecl _GetERROR_CODE_INTERNAL_ERROR() = 0 ;
	virtual int __cdecl _GetERROR_CODE_INVALID_REQUEST() = 0 ;
	virtual int __cdecl _GetERROR_CODE_NETWORK_ERROR() = 0 ;
	virtual int __cdecl _GetERROR_CODE_NO_FILL() = 0 ;
	virtual int __cdecl _GetGENDER_FEMALE() = 0 ;
	virtual int __cdecl _GetGENDER_MALE() = 0 ;
	virtual int __cdecl _GetGENDER_UNKNOWN() = 0 ;
	virtual void __cdecl updateCorrelator() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString DEVICE_ID_EMULATOR = {read=_GetDEVICE_ID_EMULATOR};
	__property int ERROR_CODE_INTERNAL_ERROR = {read=_GetERROR_CODE_INTERNAL_ERROR};
	__property int ERROR_CODE_INVALID_REQUEST = {read=_GetERROR_CODE_INVALID_REQUEST};
	__property int ERROR_CODE_NETWORK_ERROR = {read=_GetERROR_CODE_NETWORK_ERROR};
	__property int ERROR_CODE_NO_FILL = {read=_GetERROR_CODE_NO_FILL};
	__property int GENDER_FEMALE = {read=_GetGENDER_FEMALE};
	__property int GENDER_MALE = {read=_GetGENDER_MALE};
	__property int GENDER_UNKNOWN = {read=_GetGENDER_UNKNOWN};
};

__interface  INTERFACE_UUID("{9D3D4BD6-BAEE-47A4-983D-2109F50E56D6}") JPublisherAdRequest  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JDate __cdecl getBirthday() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getContentUrl() = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getCustomTargeting() = 0 ;
	virtual int __cdecl getGender() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JSet __cdecl getKeywords() = 0 ;
	virtual Androidapi::Jni::Location::_di_JLocation __cdecl getLocation() = 0 ;
	virtual bool __cdecl getManualImpressionsEnabled() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPublisherProvidedId() = 0 ;
	virtual bool __cdecl isTestDevice(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPublisherAdRequest : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPublisherAdRequestClass,_di_JPublisherAdRequest>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPublisherAdRequestClass,_di_JPublisherAdRequest> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPublisherAdRequest() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPublisherAdRequestClass,_di_JPublisherAdRequest>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPublisherAdRequest() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EBFAF2AC-A8B4-4A99-B6DA-25EC5547F2E8}") JPublisherAdRequest_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JPublisherAdRequest_Builder __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{D5ED5685-0497-4AC2-BD21-990B50681BF1}") JPublisherAdRequest_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JPublisherAdRequest_Builder __cdecl addCategoryExclusion(Androidapi::Jni::Javatypes::_di_JString categoryExclusion) = 0 ;
	virtual _di_JPublisherAdRequest_Builder __cdecl addCustomTargeting(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JList values) = 0 /* overload */;
	virtual _di_JPublisherAdRequest_Builder __cdecl addCustomTargeting(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JString value) = 0 /* overload */;
	virtual _di_JPublisherAdRequest_Builder __cdecl addKeyword(Androidapi::Jni::Javatypes::_di_JString keyword) = 0 ;
	virtual _di_JPublisherAdRequest_Builder __cdecl addTestDevice(Androidapi::Jni::Javatypes::_di_JString deviceId) = 0 ;
	virtual _di_JPublisherAdRequest __cdecl build() = 0 ;
	virtual _di_JPublisherAdRequest_Builder __cdecl setBirthday(Androidapi::Jni::Javatypes::_di_JDate birthday) = 0 ;
	virtual _di_JPublisherAdRequest_Builder __cdecl setContentUrl(Androidapi::Jni::Javatypes::_di_JString contentUrl) = 0 ;
	virtual _di_JPublisherAdRequest_Builder __cdecl setGender(int gender) = 0 ;
	virtual _di_JPublisherAdRequest_Builder __cdecl setLocation(Androidapi::Jni::Location::_di_JLocation location) = 0 ;
	virtual _di_JPublisherAdRequest_Builder __cdecl setManualImpressionsEnabled(bool manualImpressionsEnabled) = 0 ;
	virtual _di_JPublisherAdRequest_Builder __cdecl setPublisherProvidedId(Androidapi::Jni::Javatypes::_di_JString publisherProvidedId) = 0 ;
	virtual _di_JPublisherAdRequest_Builder __cdecl setRequestAgent(Androidapi::Jni::Javatypes::_di_JString requestAgent) = 0 ;
	virtual _di_JPublisherAdRequest_Builder __cdecl tagForChildDirectedTreatment(bool tagForChildDirectedTreatment) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPublisherAdRequest_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPublisherAdRequest_BuilderClass,_di_JPublisherAdRequest_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPublisherAdRequest_BuilderClass,_di_JPublisherAdRequest_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPublisherAdRequest_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPublisherAdRequest_BuilderClass,_di_JPublisherAdRequest_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPublisherAdRequest_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{51F802FF-7605-4151-89B3-BA90714B01D6}") JPublisherAdViewClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroupClass 
{
	HIDESBASE virtual _di_JPublisherAdView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JPublisherAdView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attr) = 0 /* overload */;
	HIDESBASE virtual _di_JPublisherAdView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attr, int defStyle) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{70C813E0-7948-4191-A891-9B2A3AA87D94}") JPublisherAdView  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup 
{
	virtual void __cdecl destroy() = 0 ;
	virtual _di_JAdListener __cdecl getAdListener() = 0 ;
	virtual _di_JAdSize __cdecl getAdSize() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JAdSize>* __cdecl getAdSizes() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAdUnitId() = 0 ;
	virtual _di_JAppEventListener __cdecl getAppEventListener() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMediationAdapterClassName() = 0 ;
	virtual _di_JOnCustomRenderedAdLoadedListener __cdecl getOnCustomRenderedAdLoadedListener() = 0 ;
	virtual void __cdecl loadAd(_di_JPublisherAdRequest publisherAdRequest) = 0 ;
	virtual void __cdecl pause() = 0 ;
	virtual void __cdecl recordManualImpression() = 0 ;
	virtual void __cdecl resume() = 0 ;
	virtual void __cdecl setAdListener(_di_JAdListener adListener) = 0 ;
	virtual void __cdecl setAdUnitId(Androidapi::Jni::Javatypes::_di_JString adUnitId) = 0 ;
	virtual void __cdecl setAppEventListener(_di_JAppEventListener appEventListener) = 0 ;
	virtual void __cdecl setOnCustomRenderedAdLoadedListener(_di_JOnCustomRenderedAdLoadedListener onCustomRenderedAdLoadedListener) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPublisherAdView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPublisherAdViewClass,_di_JPublisherAdView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPublisherAdViewClass,_di_JPublisherAdView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPublisherAdView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPublisherAdViewClass,_di_JPublisherAdView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPublisherAdView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{80459978-CFCD-4D2F-8A8A-1750BD100EC8}") JPublisherInterstitialAdClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JPublisherInterstitialAd __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

__interface  INTERFACE_UUID("{BC12B3C9-E5B3-4A05-8308-21E4A93E5EA4}") JPublisherInterstitialAd  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JAdListener __cdecl getAdListener() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAdUnitId() = 0 ;
	virtual _di_JAppEventListener __cdecl getAppEventListener() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMediationAdapterClassName() = 0 ;
	virtual _di_JOnCustomRenderedAdLoadedListener __cdecl getOnCustomRenderedAdLoadedListener() = 0 ;
	virtual bool __cdecl isLoaded() = 0 ;
	virtual void __cdecl loadAd(_di_JPublisherAdRequest publisherAdRequest) = 0 ;
	virtual void __cdecl setAdListener(_di_JAdListener adListener) = 0 ;
	virtual void __cdecl setAdUnitId(Androidapi::Jni::Javatypes::_di_JString adUnitId) = 0 ;
	virtual void __cdecl setAppEventListener(_di_JAppEventListener appEventListener) = 0 ;
	virtual void __cdecl setOnCustomRenderedAdLoadedListener(_di_JOnCustomRenderedAdLoadedListener onCustomRenderedAdLoadedListener) = 0 ;
	virtual void __cdecl show() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPublisherInterstitialAd : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPublisherInterstitialAdClass,_di_JPublisherInterstitialAd>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPublisherInterstitialAdClass,_di_JPublisherInterstitialAd> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPublisherInterstitialAd() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPublisherInterstitialAdClass,_di_JPublisherInterstitialAd>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPublisherInterstitialAd() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{50520615-A225-40F1-800C-2F30765DEC55}") JInAppPurchaseClass  : public Androidapi::Jnibridge::IJavaClass 
{
	virtual int __cdecl _GetRESOLUTION_CANCELED() = 0 ;
	virtual int __cdecl _GetRESOLUTION_FAILURE() = 0 ;
	virtual int __cdecl _GetRESOLUTION_INVALID_PRODUCT() = 0 ;
	virtual int __cdecl _GetRESOLUTION_SUCCESS() = 0 ;
	__property int RESOLUTION_CANCELED = {read=_GetRESOLUTION_CANCELED};
	__property int RESOLUTION_FAILURE = {read=_GetRESOLUTION_FAILURE};
	__property int RESOLUTION_INVALID_PRODUCT = {read=_GetRESOLUTION_INVALID_PRODUCT};
	__property int RESOLUTION_SUCCESS = {read=_GetRESOLUTION_SUCCESS};
};

__interface  INTERFACE_UUID("{2B2483F4-8783-4261-B145-70FFAA9AEF59}") JInAppPurchase  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getProductId() = 0 ;
	virtual void __cdecl recordPlayBillingResolution(int billingResponseCode) = 0 ;
	virtual void __cdecl recordResolution(int resolution) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInAppPurchase : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInAppPurchaseClass,_di_JInAppPurchase>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInAppPurchaseClass,_di_JInAppPurchase> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInAppPurchase() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInAppPurchaseClass,_di_JInAppPurchase>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInAppPurchase() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B1215D8E-E914-4354-B9EE-571190A9884F}") JInAppPurchaseActivityClass  : public Androidapi::Jni::App::JActivityClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCLASS_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSIMPLE_CLASS_NAME() = 0 ;
	HIDESBASE virtual _di_JInAppPurchaseActivity __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString CLASS_NAME = {read=_GetCLASS_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString SIMPLE_CLASS_NAME = {read=_GetSIMPLE_CLASS_NAME};
};

__interface  INTERFACE_UUID("{DCC71068-7561-4CA4-8BF4-C6A30BD342AE}") JInAppPurchaseActivity  : public Androidapi::Jni::App::JActivity 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInAppPurchaseActivity : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInAppPurchaseActivityClass,_di_JInAppPurchaseActivity>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInAppPurchaseActivityClass,_di_JInAppPurchaseActivity> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInAppPurchaseActivity() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInAppPurchaseActivityClass,_di_JInAppPurchaseActivity>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInAppPurchaseActivity() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E490D77A-D519-4EF6-A160-6C64D39B0F99}") JInAppPurchaseListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{E4A4DD68-0E57-46C7-BF31-90751737880D}") JInAppPurchaseListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onInAppPurchaseRequested(_di_JInAppPurchase inAppPurchase) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInAppPurchaseListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInAppPurchaseListenerClass,_di_JInAppPurchaseListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInAppPurchaseListenerClass,_di_JInAppPurchaseListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInAppPurchaseListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInAppPurchaseListenerClass,_di_JInAppPurchaseListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInAppPurchaseListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6D6C3D99-530B-479F-B13E-05A3C3B31B83}") JInAppPurchaseResultClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{5A2C5AFE-2ADA-4F01-BC21-86D5BC7AC10F}") JInAppPurchaseResult  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl finishPurchase() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getProductId() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JIntent __cdecl getPurchaseData() = 0 ;
	virtual int __cdecl getResultCode() = 0 ;
	virtual bool __cdecl isVerified() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInAppPurchaseResult : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInAppPurchaseResultClass,_di_JInAppPurchaseResult>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInAppPurchaseResultClass,_di_JInAppPurchaseResult> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInAppPurchaseResult() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInAppPurchaseResultClass,_di_JInAppPurchaseResult>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInAppPurchaseResult() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{02E8999B-CCBA-4049-BB73-40A74EB1D890}") JPlayStorePurchaseListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{35400957-85ED-4009-BA1F-7BC6062AE6D0}") JPlayStorePurchaseListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual bool __cdecl isValidPurchase(Androidapi::Jni::Javatypes::_di_JString productId) = 0 ;
	virtual void __cdecl onInAppPurchaseFinished(_di_JInAppPurchaseResult inAppPurchaseResult) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPlayStorePurchaseListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPlayStorePurchaseListenerClass,_di_JPlayStorePurchaseListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPlayStorePurchaseListenerClass,_di_JPlayStorePurchaseListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPlayStorePurchaseListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPlayStorePurchaseListenerClass,_di_JPlayStorePurchaseListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPlayStorePurchaseListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{31CC1220-F7EC-44D3-9805-80A0C42377CE}") JSearchAdRequestClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetBORDER_TYPE_DASHED() = 0 ;
	virtual int __cdecl _GetBORDER_TYPE_DOTTED() = 0 ;
	virtual int __cdecl _GetBORDER_TYPE_NONE() = 0 ;
	virtual int __cdecl _GetBORDER_TYPE_SOLID() = 0 ;
	virtual int __cdecl _GetCALL_BUTTON_COLOR_DARK() = 0 ;
	virtual int __cdecl _GetCALL_BUTTON_COLOR_LIGHT() = 0 ;
	virtual int __cdecl _GetCALL_BUTTON_COLOR_MEDIUM() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDEVICE_ID_EMULATOR() = 0 ;
	virtual int __cdecl _GetERROR_CODE_INTERNAL_ERROR() = 0 ;
	virtual int __cdecl _GetERROR_CODE_INVALID_REQUEST() = 0 ;
	virtual int __cdecl _GetERROR_CODE_NETWORK_ERROR() = 0 ;
	virtual int __cdecl _GetERROR_CODE_NO_FILL() = 0 ;
	__property int BORDER_TYPE_DASHED = {read=_GetBORDER_TYPE_DASHED};
	__property int BORDER_TYPE_DOTTED = {read=_GetBORDER_TYPE_DOTTED};
	__property int BORDER_TYPE_NONE = {read=_GetBORDER_TYPE_NONE};
	__property int BORDER_TYPE_SOLID = {read=_GetBORDER_TYPE_SOLID};
	__property int CALL_BUTTON_COLOR_DARK = {read=_GetCALL_BUTTON_COLOR_DARK};
	__property int CALL_BUTTON_COLOR_LIGHT = {read=_GetCALL_BUTTON_COLOR_LIGHT};
	__property int CALL_BUTTON_COLOR_MEDIUM = {read=_GetCALL_BUTTON_COLOR_MEDIUM};
	__property Androidapi::Jni::Javatypes::_di_JString DEVICE_ID_EMULATOR = {read=_GetDEVICE_ID_EMULATOR};
	__property int ERROR_CODE_INTERNAL_ERROR = {read=_GetERROR_CODE_INTERNAL_ERROR};
	__property int ERROR_CODE_INVALID_REQUEST = {read=_GetERROR_CODE_INVALID_REQUEST};
	__property int ERROR_CODE_NETWORK_ERROR = {read=_GetERROR_CODE_NETWORK_ERROR};
	__property int ERROR_CODE_NO_FILL = {read=_GetERROR_CODE_NO_FILL};
};

__interface  INTERFACE_UUID("{7105D858-7D2D-4105-A415-4B9C3B187692}") JSearchAdRequest  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl getAnchorTextColor() = 0 ;
	virtual int __cdecl getBackgroundColor() = 0 ;
	virtual int __cdecl getBackgroundGradientBottom() = 0 ;
	virtual int __cdecl getBackgroundGradientTop() = 0 ;
	virtual int __cdecl getBorderColor() = 0 ;
	virtual int __cdecl getBorderThickness() = 0 ;
	virtual int __cdecl getBorderType() = 0 ;
	virtual int __cdecl getCallButtonColor() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getCustomChannels() = 0 ;
	virtual int __cdecl getDescriptionTextColor() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getFontFace() = 0 ;
	virtual int __cdecl getHeaderTextColor() = 0 ;
	virtual int __cdecl getHeaderTextSize() = 0 ;
	virtual Androidapi::Jni::Location::_di_JLocation __cdecl getLocation() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getQuery() = 0 ;
	virtual bool __cdecl isTestDevice(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSearchAdRequest : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSearchAdRequestClass,_di_JSearchAdRequest>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSearchAdRequestClass,_di_JSearchAdRequest> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSearchAdRequest() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSearchAdRequestClass,_di_JSearchAdRequest>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSearchAdRequest() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BFC1817C-04E6-421F-95E5-CD3B30059C40}") JSearchAdRequest_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JSearchAdRequest_Builder __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{F33FB6FC-B4E7-4B4B-ACEC-9108757675C6}") JSearchAdRequest_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JSearchAdRequest_Builder __cdecl addTestDevice(Androidapi::Jni::Javatypes::_di_JString deviceId) = 0 ;
	virtual _di_JSearchAdRequest __cdecl build() = 0 ;
	virtual _di_JSearchAdRequest_Builder __cdecl setAnchorTextColor(int anchorTextColor) = 0 ;
	virtual _di_JSearchAdRequest_Builder __cdecl setBackgroundColor(int backgroundColor) = 0 ;
	virtual _di_JSearchAdRequest_Builder __cdecl setBackgroundGradient(int top, int bottom) = 0 ;
	virtual _di_JSearchAdRequest_Builder __cdecl setBorderColor(int borderColor) = 0 ;
	virtual _di_JSearchAdRequest_Builder __cdecl setBorderThickness(int borderThickness) = 0 ;
	virtual _di_JSearchAdRequest_Builder __cdecl setBorderType(int borderType) = 0 ;
	virtual _di_JSearchAdRequest_Builder __cdecl setCallButtonColor(int callButtonColor) = 0 ;
	virtual _di_JSearchAdRequest_Builder __cdecl setCustomChannels(Androidapi::Jni::Javatypes::_di_JString channelIds) = 0 ;
	virtual _di_JSearchAdRequest_Builder __cdecl setDescriptionTextColor(int descriptionTextColor) = 0 ;
	virtual _di_JSearchAdRequest_Builder __cdecl setFontFace(Androidapi::Jni::Javatypes::_di_JString fontFace) = 0 ;
	virtual _di_JSearchAdRequest_Builder __cdecl setHeaderTextColor(int headerTextColor) = 0 ;
	virtual _di_JSearchAdRequest_Builder __cdecl setHeaderTextSize(int headerTextSize) = 0 ;
	virtual _di_JSearchAdRequest_Builder __cdecl setLocation(Androidapi::Jni::Location::_di_JLocation location) = 0 ;
	virtual _di_JSearchAdRequest_Builder __cdecl setQuery(Androidapi::Jni::Javatypes::_di_JString query) = 0 ;
	virtual _di_JSearchAdRequest_Builder __cdecl setRequestAgent(Androidapi::Jni::Javatypes::_di_JString requestAgent) = 0 ;
	virtual _di_JSearchAdRequest_Builder __cdecl tagForChildDirectedTreatment(bool tagForChildDirectedTreatment) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSearchAdRequest_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSearchAdRequest_BuilderClass,_di_JSearchAdRequest_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSearchAdRequest_BuilderClass,_di_JSearchAdRequest_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSearchAdRequest_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSearchAdRequest_BuilderClass,_di_JSearchAdRequest_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSearchAdRequest_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{ECDC5A65-5618-48D3-82E7-4B06898CBBCC}") JSearchAdViewClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroupClass 
{
	HIDESBASE virtual _di_JSearchAdView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JSearchAdView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JSearchAdView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyle) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{9FB97DC2-F4F5-4E7C-AFAC-0BA46A8E9043}") JSearchAdView  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup 
{
	virtual void __cdecl destroy() = 0 ;
	virtual _di_JAdListener __cdecl getAdListener() = 0 ;
	virtual _di_JAdSize __cdecl getAdSize() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAdUnitId() = 0 ;
	virtual void __cdecl loadAd(_di_JSearchAdRequest searchAdRequest) = 0 ;
	virtual void __cdecl pause() = 0 ;
	virtual void __cdecl resume() = 0 ;
	virtual void __cdecl setAdListener(_di_JAdListener adListener) = 0 ;
	virtual void __cdecl setAdSize(_di_JAdSize adSize) = 0 ;
	virtual void __cdecl setAdUnitId(Androidapi::Jni::Javatypes::_di_JString adUnitId) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSearchAdView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSearchAdViewClass,_di_JSearchAdView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSearchAdViewClass,_di_JSearchAdView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSearchAdView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSearchAdViewClass,_di_JSearchAdView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSearchAdView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Admob */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_ADMOB)
using namespace Androidapi::Jni::Admob;
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
#endif	// Androidapi_Jni_AdmobHPP
