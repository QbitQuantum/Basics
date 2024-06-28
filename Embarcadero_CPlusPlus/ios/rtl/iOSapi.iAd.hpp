// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.iAd.pas' rev: 34.00 (iOS)

#ifndef Iosapi_IadHPP
#define Iosapi_IadHPP

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
namespace Iad
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE ADInterstitialAdDelegate;
typedef System::DelphiInterface<ADInterstitialAdDelegate> _di_ADInterstitialAdDelegate;
__interface DELPHIINTERFACE ADBannerViewDelegate;
typedef System::DelphiInterface<ADBannerViewDelegate> _di_ADBannerViewDelegate;
__interface DELPHIINTERFACE ADInterstitialAdClass;
typedef System::DelphiInterface<ADInterstitialAdClass> _di_ADInterstitialAdClass;
__interface DELPHIINTERFACE ADInterstitialAd;
typedef System::DelphiInterface<ADInterstitialAd> _di_ADInterstitialAd;
class DELPHICLASS TADInterstitialAd;
__interface DELPHIINTERFACE ADBannerViewClass;
typedef System::DelphiInterface<ADBannerViewClass> _di_ADBannerViewClass;
__interface DELPHIINTERFACE ADBannerView;
typedef System::DelphiInterface<ADBannerView> _di_ADBannerView;
class DELPHICLASS TADBannerView;
//-- type declarations -------------------------------------------------------
typedef unsigned long ADError;

enum DECLSPEC_DENUM ADAdType : unsigned char { ADAdTypeBanner, ADAdTypeMediumRectangle };

__interface  INTERFACE_UUID("{6F4355B8-6A92-4ABC-B971-513E6465BC30}") ADInterstitialAdDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl interstitialAd(_di_ADInterstitialAd interstitialAd, Iosapi::Foundation::_di_NSError didFailWithError) = 0 ;
	virtual void __cdecl interstitialAdActionDidFinish(_di_ADInterstitialAd interstitialAd) = 0 ;
	virtual bool __cdecl interstitialAdActionShouldBegin(_di_ADInterstitialAd interstitialAd, bool willLeaveApplication) = 0 ;
	virtual void __cdecl interstitialAdDidLoad(_di_ADInterstitialAd interstitialAd) = 0 ;
	virtual void __cdecl interstitialAdDidUnload(_di_ADInterstitialAd interstitialAd) = 0 ;
	virtual void __cdecl interstitialAdWillLoad(_di_ADInterstitialAd interstitialAd) = 0 ;
};

__interface  INTERFACE_UUID("{95249262-9E7D-4841-B8E4-9EBBDADF3485}") ADBannerViewDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl bannerView(_di_ADBannerView banner, Iosapi::Foundation::_di_NSError didFailToReceiveAdWithError) = 0 ;
	virtual void __cdecl bannerViewActionDidFinish(_di_ADBannerView banner) = 0 ;
	virtual bool __cdecl bannerViewActionShouldBegin(_di_ADBannerView banner, bool willLeaveApplication) = 0 ;
	virtual void __cdecl bannerViewDidLoadAd(_di_ADBannerView banner) = 0 ;
	virtual void __cdecl bannerViewWillLoadAd(_di_ADBannerView banner) = 0 ;
};

__interface  INTERFACE_UUID("{8C5ACE62-A5B6-4B0B-9D62-43D3CB0A8BD0}") ADInterstitialAdClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{31570147-4315-4616-8ECB-B4874008884B}") ADInterstitialAd  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl cancelAction() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual bool __cdecl isActionInProgress() = 0 ;
	virtual bool __cdecl isLoaded() = 0 ;
	virtual void __cdecl presentFromViewController(Iosapi::Uikit::_di_UIViewController viewController) = 0 ;
	virtual bool __cdecl presentInView(Iosapi::Uikit::_di_UIView containerView) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
};

class PASCALIMPLEMENTATION TADInterstitialAd : public Macapi::Objectivec::TOCGenericImport__2<_di_ADInterstitialAdClass,_di_ADInterstitialAd>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_ADInterstitialAdClass,_di_ADInterstitialAd> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TADInterstitialAd(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_ADInterstitialAdClass,_di_ADInterstitialAd>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TADInterstitialAd() { }
	
};


__interface  INTERFACE_UUID("{B072DCC4-3CBE-4C07-B8B2-0B9B81A51AD9}") ADBannerViewClass  : public Iosapi::Uikit::UIViewClass 
{
	virtual Iosapi::Foundation::NSSize __cdecl sizeFromBannerContentSizeIdentifier(Iosapi::Foundation::_di_NSString contentSizeIdentifier) = 0 ;
};

__interface  INTERFACE_UUID("{2FD4C4B7-1FBE-46C0-83FD-A601B2DF980A}") ADBannerView  : public Iosapi::Uikit::UIView 
{
	virtual ADAdType __cdecl adType() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl advertisingSection() = 0 ;
	virtual void __cdecl cancelBannerViewAction() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl currentContentSizeIdentifier() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void * __cdecl initWithAdType(ADAdType type_) = 0 ;
	virtual bool __cdecl isBannerLoaded() = 0 ;
	virtual bool __cdecl isBannerViewActionInProgress() = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl requiredContentSizeIdentifiers() = 0 ;
	virtual void __cdecl setAdvertisingSection(Iosapi::Foundation::_di_NSString advertisingSection) = 0 ;
	virtual void __cdecl setCurrentContentSizeIdentifier(Iosapi::Foundation::_di_NSString currentContentSizeIdentifier) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setRequiredContentSizeIdentifiers(Iosapi::Foundation::_di_NSSet requiredContentSizeIdentifiers) = 0 ;
};

class PASCALIMPLEMENTATION TADBannerView : public Macapi::Objectivec::TOCGenericImport__2<_di_ADBannerViewClass,_di_ADBannerView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_ADBannerViewClass,_di_ADBannerView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TADBannerView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_ADBannerViewClass,_di_ADBannerView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TADBannerView() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define iAdFwk u"/System/Library/Frameworks/iAd.framework/iAd"
static constexpr System::Int8 ADErrorUnknown = System::Int8(0x0);
static constexpr System::Int8 ADErrorServerFailure = System::Int8(0x1);
static constexpr System::Int8 ADErrorLoadingThrottled = System::Int8(0x2);
static constexpr System::Int8 ADErrorInventoryUnavailable = System::Int8(0x3);
static constexpr System::Int8 ADErrorConfigurationError = System::Int8(0x4);
static constexpr System::Int8 ADErrorBannerVisibleWithoutContent = System::Int8(0x5);
static constexpr System::Int8 ADErrorApplicationInactive = System::Int8(0x6);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ADBannerContentSizeIdentifierPortrait(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ADBannerContentSizeIdentifierLandscape(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ADBannerContentSizeIdentifier320x50(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ADBannerContentSizeIdentifier480x32(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ADErrorDomain(void);
}	/* namespace Iad */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_IAD)
using namespace Iosapi::Iad;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_IadHPP
