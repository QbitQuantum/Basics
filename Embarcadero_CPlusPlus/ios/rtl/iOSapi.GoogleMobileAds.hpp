// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.GoogleMobileAds.pas' rev: 34.00 (iOS)

#ifndef Iosapi_GooglemobileadsHPP
#define Iosapi_GooglemobileadsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <Macapi.Dispatch.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <iOSapi.StoreKit.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Googlemobileads
{
//-- forward type declarations -----------------------------------------------
struct GADAdSize;
struct GADVersionNumber;
__interface DELPHIINTERFACE DFPCustomRenderedBannerViewDelegate;
typedef System::DelphiInterface<DFPCustomRenderedBannerViewDelegate> _di_DFPCustomRenderedBannerViewDelegate;
__interface DELPHIINTERFACE GADRequestErrorClass;
typedef System::DelphiInterface<GADRequestErrorClass> _di_GADRequestErrorClass;
__interface DELPHIINTERFACE GADRequestError;
typedef System::DelphiInterface<GADRequestError> _di_GADRequestError;
class DELPHICLASS TGADRequestError;
__interface DELPHIINTERFACE GADAdLoaderDelegate;
typedef System::DelphiInterface<GADAdLoaderDelegate> _di_GADAdLoaderDelegate;
__interface DELPHIINTERFACE GADAdNetworkExtras;
typedef System::DelphiInterface<GADAdNetworkExtras> _di_GADAdNetworkExtras;
__interface DELPHIINTERFACE GADRequestClass;
typedef System::DelphiInterface<GADRequestClass> _di_GADRequestClass;
__interface DELPHIINTERFACE GADRequest;
typedef System::DelphiInterface<GADRequest> _di_GADRequest;
class DELPHICLASS TGADRequest;
__interface DELPHIINTERFACE GADAdLoaderOptionsClass;
typedef System::DelphiInterface<GADAdLoaderOptionsClass> _di_GADAdLoaderOptionsClass;
__interface DELPHIINTERFACE GADAdLoaderOptions;
typedef System::DelphiInterface<GADAdLoaderOptions> _di_GADAdLoaderOptions;
class DELPHICLASS TGADAdLoaderOptions;
__interface DELPHIINTERFACE GADAdLoaderClass;
typedef System::DelphiInterface<GADAdLoaderClass> _di_GADAdLoaderClass;
__interface DELPHIINTERFACE GADAdLoader;
typedef System::DelphiInterface<GADAdLoader> _di_GADAdLoader;
class DELPHICLASS TGADAdLoader;
__interface DELPHIINTERFACE GADAppEventDelegate;
typedef System::DelphiInterface<GADAppEventDelegate> _di_GADAppEventDelegate;
__interface DELPHIINTERFACE GADAdSizeDelegate;
typedef System::DelphiInterface<GADAdSizeDelegate> _di_GADAdSizeDelegate;
__interface DELPHIINTERFACE GADAdValueClass;
typedef System::DelphiInterface<GADAdValueClass> _di_GADAdValueClass;
__interface DELPHIINTERFACE GADAdValue;
typedef System::DelphiInterface<GADAdValue> _di_GADAdValue;
class DELPHICLASS TGADAdValue;
__interface DELPHIINTERFACE GADBannerViewDelegate;
typedef System::DelphiInterface<GADBannerViewDelegate> _di_GADBannerViewDelegate;
__interface DELPHIINTERFACE GADDefaultInAppPurchaseDelegate;
typedef System::DelphiInterface<GADDefaultInAppPurchaseDelegate> _di_GADDefaultInAppPurchaseDelegate;
__interface DELPHIINTERFACE GADInAppPurchaseDelegate;
typedef System::DelphiInterface<GADInAppPurchaseDelegate> _di_GADInAppPurchaseDelegate;
__interface DELPHIINTERFACE GADResponseInfoClass;
typedef System::DelphiInterface<GADResponseInfoClass> _di_GADResponseInfoClass;
__interface DELPHIINTERFACE GADResponseInfo;
typedef System::DelphiInterface<GADResponseInfo> _di_GADResponseInfo;
class DELPHICLASS TGADResponseInfo;
__interface DELPHIINTERFACE GADBannerViewClass;
typedef System::DelphiInterface<GADBannerViewClass> _di_GADBannerViewClass;
__interface DELPHIINTERFACE GADBannerView;
typedef System::DelphiInterface<GADBannerView> _di_GADBannerView;
class DELPHICLASS TGADBannerView;
__interface DELPHIINTERFACE GADVideoControllerClass;
typedef System::DelphiInterface<GADVideoControllerClass> _di_GADVideoControllerClass;
__interface DELPHIINTERFACE GADVideoController;
typedef System::DelphiInterface<GADVideoController> _di_GADVideoController;
class DELPHICLASS TGADVideoController;
__interface DELPHIINTERFACE DFPBannerAdLoaderDelegate;
typedef System::DelphiInterface<DFPBannerAdLoaderDelegate> _di_DFPBannerAdLoaderDelegate;
__interface DELPHIINTERFACE DFPBannerViewClass;
typedef System::DelphiInterface<DFPBannerViewClass> _di_DFPBannerViewClass;
__interface DELPHIINTERFACE DFPBannerView;
typedef System::DelphiInterface<DFPBannerView> _di_DFPBannerView;
class DELPHICLASS TDFPBannerView;
__interface DELPHIINTERFACE DFPBannerViewOptionsClass;
typedef System::DelphiInterface<DFPBannerViewOptionsClass> _di_DFPBannerViewOptionsClass;
__interface DELPHIINTERFACE DFPBannerViewOptions;
typedef System::DelphiInterface<DFPBannerViewOptions> _di_DFPBannerViewOptions;
class DELPHICLASS TDFPBannerViewOptions;
__interface DELPHIINTERFACE DFPCustomRenderedAdClass;
typedef System::DelphiInterface<DFPCustomRenderedAdClass> _di_DFPCustomRenderedAdClass;
__interface DELPHIINTERFACE DFPCustomRenderedAd;
typedef System::DelphiInterface<DFPCustomRenderedAd> _di_DFPCustomRenderedAd;
class DELPHICLASS TDFPCustomRenderedAd;
__interface DELPHIINTERFACE DFPCustomRenderedInterstitialDelegate;
typedef System::DelphiInterface<DFPCustomRenderedInterstitialDelegate> _di_DFPCustomRenderedInterstitialDelegate;
__interface DELPHIINTERFACE GADInterstitialDelegate;
typedef System::DelphiInterface<GADInterstitialDelegate> _di_GADInterstitialDelegate;
__interface DELPHIINTERFACE GADInterstitialClass;
typedef System::DelphiInterface<GADInterstitialClass> _di_GADInterstitialClass;
__interface DELPHIINTERFACE GADInterstitial;
typedef System::DelphiInterface<GADInterstitial> _di_GADInterstitial;
class DELPHICLASS TGADInterstitial;
__interface DELPHIINTERFACE DFPInterstitialClass;
typedef System::DelphiInterface<DFPInterstitialClass> _di_DFPInterstitialClass;
__interface DELPHIINTERFACE DFPInterstitial;
typedef System::DelphiInterface<DFPInterstitial> _di_DFPInterstitial;
class DELPHICLASS TDFPInterstitial;
__interface DELPHIINTERFACE DFPRequestClass;
typedef System::DelphiInterface<DFPRequestClass> _di_DFPRequestClass;
__interface DELPHIINTERFACE DFPRequest;
typedef System::DelphiInterface<DFPRequest> _di_DFPRequest;
class DELPHICLASS TDFPRequest;
__interface DELPHIINTERFACE GADAdChoicesViewClass;
typedef System::DelphiInterface<GADAdChoicesViewClass> _di_GADAdChoicesViewClass;
__interface DELPHIINTERFACE GADAdChoicesView;
typedef System::DelphiInterface<GADAdChoicesView> _di_GADAdChoicesView;
class DELPHICLASS TGADAdChoicesView;
__interface DELPHIINTERFACE GADAudioVideoManagerDelegate;
typedef System::DelphiInterface<GADAudioVideoManagerDelegate> _di_GADAudioVideoManagerDelegate;
__interface DELPHIINTERFACE GADAudioVideoManagerClass;
typedef System::DelphiInterface<GADAudioVideoManagerClass> _di_GADAudioVideoManagerClass;
__interface DELPHIINTERFACE GADAudioVideoManager;
typedef System::DelphiInterface<GADAudioVideoManager> _di_GADAudioVideoManager;
class DELPHICLASS TGADAudioVideoManager;
__interface DELPHIINTERFACE GADAdapterStatusClass;
typedef System::DelphiInterface<GADAdapterStatusClass> _di_GADAdapterStatusClass;
__interface DELPHIINTERFACE GADAdapterStatus;
typedef System::DelphiInterface<GADAdapterStatus> _di_GADAdapterStatus;
class DELPHICLASS TGADAdapterStatus;
__interface DELPHIINTERFACE GADInitializationStatusClass;
typedef System::DelphiInterface<GADInitializationStatusClass> _di_GADInitializationStatusClass;
__interface DELPHIINTERFACE GADInitializationStatus;
typedef System::DelphiInterface<GADInitializationStatus> _di_GADInitializationStatus;
class DELPHICLASS TGADInitializationStatus;
__interface DELPHIINTERFACE GADRequestConfigurationClass;
typedef System::DelphiInterface<GADRequestConfigurationClass> _di_GADRequestConfigurationClass;
__interface DELPHIINTERFACE GADRequestConfiguration;
typedef System::DelphiInterface<GADRequestConfiguration> _di_GADRequestConfiguration;
class DELPHICLASS TGADRequestConfiguration;
__interface DELPHIINTERFACE GADMobileAdsClass;
typedef System::DelphiInterface<GADMobileAdsClass> _di_GADMobileAdsClass;
__interface DELPHIINTERFACE GADMobileAds;
typedef System::DelphiInterface<GADMobileAds> _di_GADMobileAds;
class DELPHICLASS TGADMobileAds;
__interface DELPHIINTERFACE GADAdRewardClass;
typedef System::DelphiInterface<GADAdRewardClass> _di_GADAdRewardClass;
__interface DELPHIINTERFACE GADAdReward;
typedef System::DelphiInterface<GADAdReward> _di_GADAdReward;
class DELPHICLASS TGADAdReward;
__interface DELPHIINTERFACE GADAppOpenAdClass;
typedef System::DelphiInterface<GADAppOpenAdClass> _di_GADAppOpenAdClass;
__interface DELPHIINTERFACE GADAppOpenAd;
typedef System::DelphiInterface<GADAppOpenAd> _di_GADAppOpenAd;
class DELPHICLASS TGADAppOpenAd;
__interface DELPHIINTERFACE GADAppOpenAdViewClass;
typedef System::DelphiInterface<GADAppOpenAdViewClass> _di_GADAppOpenAdViewClass;
__interface DELPHIINTERFACE GADAppOpenAdView;
typedef System::DelphiInterface<GADAppOpenAdView> _di_GADAppOpenAdView;
class DELPHICLASS TGADAppOpenAdView;
__interface DELPHIINTERFACE GADCustomEventBannerDelegate;
typedef System::DelphiInterface<GADCustomEventBannerDelegate> _di_GADCustomEventBannerDelegate;
__interface DELPHIINTERFACE GADCustomEventRequestClass;
typedef System::DelphiInterface<GADCustomEventRequestClass> _di_GADCustomEventRequestClass;
__interface DELPHIINTERFACE GADCustomEventRequest;
typedef System::DelphiInterface<GADCustomEventRequest> _di_GADCustomEventRequest;
class DELPHICLASS TGADCustomEventRequest;
__interface DELPHIINTERFACE GADCustomEventBanner;
typedef System::DelphiInterface<GADCustomEventBanner> _di_GADCustomEventBanner;
__interface DELPHIINTERFACE GADCustomEventExtrasClass;
typedef System::DelphiInterface<GADCustomEventExtrasClass> _di_GADCustomEventExtrasClass;
__interface DELPHIINTERFACE GADCustomEventExtras;
typedef System::DelphiInterface<GADCustomEventExtras> _di_GADCustomEventExtras;
class DELPHICLASS TGADCustomEventExtras;
__interface DELPHIINTERFACE GADCustomEventInterstitialDelegate;
typedef System::DelphiInterface<GADCustomEventInterstitialDelegate> _di_GADCustomEventInterstitialDelegate;
__interface DELPHIINTERFACE GADCustomEventInterstitial;
typedef System::DelphiInterface<GADCustomEventInterstitial> _di_GADCustomEventInterstitial;
__interface DELPHIINTERFACE GADCustomEventNativeAd;
typedef System::DelphiInterface<GADCustomEventNativeAd> _di_GADCustomEventNativeAd;
__interface DELPHIINTERFACE GADNativeAdImageClass;
typedef System::DelphiInterface<GADNativeAdImageClass> _di_GADNativeAdImageClass;
__interface DELPHIINTERFACE GADNativeAdImage;
typedef System::DelphiInterface<GADNativeAdImage> _di_GADNativeAdImage;
class DELPHICLASS TGADNativeAdImage;
__interface DELPHIINTERFACE GADMediatedUnifiedNativeAd;
typedef System::DelphiInterface<GADMediatedUnifiedNativeAd> _di_GADMediatedUnifiedNativeAd;
__interface DELPHIINTERFACE GADCustomEventNativeAdDelegate;
typedef System::DelphiInterface<GADCustomEventNativeAdDelegate> _di_GADCustomEventNativeAdDelegate;
__interface DELPHIINTERFACE GADDebugOptionsViewControllerDelegate;
typedef System::DelphiInterface<GADDebugOptionsViewControllerDelegate> _di_GADDebugOptionsViewControllerDelegate;
__interface DELPHIINTERFACE GADDebugOptionsViewControllerClass;
typedef System::DelphiInterface<GADDebugOptionsViewControllerClass> _di_GADDebugOptionsViewControllerClass;
__interface DELPHIINTERFACE GADDebugOptionsViewController;
typedef System::DelphiInterface<GADDebugOptionsViewController> _di_GADDebugOptionsViewController;
class DELPHICLASS TGADDebugOptionsViewController;
__interface DELPHIINTERFACE GADDelayedAdRenderingDelegate;
typedef System::DelphiInterface<GADDelayedAdRenderingDelegate> _di_GADDelayedAdRenderingDelegate;
__interface DELPHIINTERFACE GADDelayedAdRenderingOptionsClass;
typedef System::DelphiInterface<GADDelayedAdRenderingOptionsClass> _di_GADDelayedAdRenderingOptionsClass;
__interface DELPHIINTERFACE GADDelayedAdRenderingOptions;
typedef System::DelphiInterface<GADDelayedAdRenderingOptions> _di_GADDelayedAdRenderingOptions;
class DELPHICLASS TGADDelayedAdRenderingOptions;
__interface DELPHIINTERFACE GADDisplayAdMeasurementClass;
typedef System::DelphiInterface<GADDisplayAdMeasurementClass> _di_GADDisplayAdMeasurementClass;
__interface DELPHIINTERFACE GADDisplayAdMeasurement;
typedef System::DelphiInterface<GADDisplayAdMeasurement> _di_GADDisplayAdMeasurement;
class DELPHICLASS TGADDisplayAdMeasurement;
__interface DELPHIINTERFACE GADDynamicHeightSearchRequestClass;
typedef System::DelphiInterface<GADDynamicHeightSearchRequestClass> _di_GADDynamicHeightSearchRequestClass;
__interface DELPHIINTERFACE GADDynamicHeightSearchRequest;
typedef System::DelphiInterface<GADDynamicHeightSearchRequest> _di_GADDynamicHeightSearchRequest;
class DELPHICLASS TGADDynamicHeightSearchRequest;
__interface DELPHIINTERFACE GADExtrasClass;
typedef System::DelphiInterface<GADExtrasClass> _di_GADExtrasClass;
__interface DELPHIINTERFACE GADExtras;
typedef System::DelphiInterface<GADExtras> _di_GADExtras;
class DELPHICLASS TGADExtras;
__interface DELPHIINTERFACE GADDefaultInAppPurchaseClass;
typedef System::DelphiInterface<GADDefaultInAppPurchaseClass> _di_GADDefaultInAppPurchaseClass;
__interface DELPHIINTERFACE GADDefaultInAppPurchase;
typedef System::DelphiInterface<GADDefaultInAppPurchase> _di_GADDefaultInAppPurchase;
class DELPHICLASS TGADDefaultInAppPurchase;
__interface DELPHIINTERFACE GADInAppPurchaseClass;
typedef System::DelphiInterface<GADInAppPurchaseClass> _di_GADInAppPurchaseClass;
__interface DELPHIINTERFACE GADInAppPurchase;
typedef System::DelphiInterface<GADInAppPurchase> _di_GADInAppPurchase;
class DELPHICLASS TGADInAppPurchase;
__interface DELPHIINTERFACE GADMediaContentClass;
typedef System::DelphiInterface<GADMediaContentClass> _di_GADMediaContentClass;
__interface DELPHIINTERFACE GADMediaContent;
typedef System::DelphiInterface<GADMediaContent> _di_GADMediaContent;
class DELPHICLASS TGADMediaContent;
__interface DELPHIINTERFACE GADInstreamAdClass;
typedef System::DelphiInterface<GADInstreamAdClass> _di_GADInstreamAdClass;
__interface DELPHIINTERFACE GADInstreamAd;
typedef System::DelphiInterface<GADInstreamAd> _di_GADInstreamAd;
class DELPHICLASS TGADInstreamAd;
__interface DELPHIINTERFACE GADInstreamAdViewClass;
typedef System::DelphiInterface<GADInstreamAdViewClass> _di_GADInstreamAdViewClass;
__interface DELPHIINTERFACE GADInstreamAdView;
typedef System::DelphiInterface<GADInstreamAdView> _di_GADInstreamAdView;
class DELPHICLASS TGADInstreamAdView;
__interface DELPHIINTERFACE GADMediaViewClass;
typedef System::DelphiInterface<GADMediaViewClass> _di_GADMediaViewClass;
__interface DELPHIINTERFACE GADMediaView;
typedef System::DelphiInterface<GADMediaView> _di_GADMediaView;
class DELPHICLASS TGADMediaView;
__interface DELPHIINTERFACE GADMultipleAdsAdLoaderOptionsClass;
typedef System::DelphiInterface<GADMultipleAdsAdLoaderOptionsClass> _di_GADMultipleAdsAdLoaderOptionsClass;
__interface DELPHIINTERFACE GADMultipleAdsAdLoaderOptions;
typedef System::DelphiInterface<GADMultipleAdsAdLoaderOptions> _di_GADMultipleAdsAdLoaderOptions;
class DELPHICLASS TGADMultipleAdsAdLoaderOptions;
__interface DELPHIINTERFACE GADMuteThisAdReasonClass;
typedef System::DelphiInterface<GADMuteThisAdReasonClass> _di_GADMuteThisAdReasonClass;
__interface DELPHIINTERFACE GADMuteThisAdReason;
typedef System::DelphiInterface<GADMuteThisAdReason> _di_GADMuteThisAdReason;
class DELPHICLASS TGADMuteThisAdReason;
__interface DELPHIINTERFACE GADNativeAdClass;
typedef System::DelphiInterface<GADNativeAdClass> _di_GADNativeAdClass;
__interface DELPHIINTERFACE GADNativeAd;
typedef System::DelphiInterface<GADNativeAd> _di_GADNativeAd;
class DELPHICLASS TGADNativeAd;
__interface DELPHIINTERFACE GADNativeAdDelegate;
typedef System::DelphiInterface<GADNativeAdDelegate> _di_GADNativeAdDelegate;
__interface DELPHIINTERFACE GADNativeAdImageAdLoaderOptionsClass;
typedef System::DelphiInterface<GADNativeAdImageAdLoaderOptionsClass> _di_GADNativeAdImageAdLoaderOptionsClass;
__interface DELPHIINTERFACE GADNativeAdImageAdLoaderOptions;
typedef System::DelphiInterface<GADNativeAdImageAdLoaderOptions> _di_GADNativeAdImageAdLoaderOptions;
class DELPHICLASS TGADNativeAdImageAdLoaderOptions;
__interface DELPHIINTERFACE GADNativeAdMediaAdLoaderOptionsClass;
typedef System::DelphiInterface<GADNativeAdMediaAdLoaderOptionsClass> _di_GADNativeAdMediaAdLoaderOptionsClass;
__interface DELPHIINTERFACE GADNativeAdMediaAdLoaderOptions;
typedef System::DelphiInterface<GADNativeAdMediaAdLoaderOptions> _di_GADNativeAdMediaAdLoaderOptions;
class DELPHICLASS TGADNativeAdMediaAdLoaderOptions;
__interface DELPHIINTERFACE GADNativeAdViewAdOptionsClass;
typedef System::DelphiInterface<GADNativeAdViewAdOptionsClass> _di_GADNativeAdViewAdOptionsClass;
__interface DELPHIINTERFACE GADNativeAdViewAdOptions;
typedef System::DelphiInterface<GADNativeAdViewAdOptions> _di_GADNativeAdViewAdOptions;
class DELPHICLASS TGADNativeAdViewAdOptions;
__interface DELPHIINTERFACE GADNativeCustomTemplateAdClass;
typedef System::DelphiInterface<GADNativeCustomTemplateAdClass> _di_GADNativeCustomTemplateAdClass;
__interface DELPHIINTERFACE GADNativeCustomTemplateAd;
typedef System::DelphiInterface<GADNativeCustomTemplateAd> _di_GADNativeCustomTemplateAd;
class DELPHICLASS TGADNativeCustomTemplateAd;
__interface DELPHIINTERFACE GADNativeCustomTemplateAdLoaderDelegate;
typedef System::DelphiInterface<GADNativeCustomTemplateAdLoaderDelegate> _di_GADNativeCustomTemplateAdLoaderDelegate;
__interface DELPHIINTERFACE GADNativeExpressAdViewDelegate;
typedef System::DelphiInterface<GADNativeExpressAdViewDelegate> _di_GADNativeExpressAdViewDelegate;
__interface DELPHIINTERFACE GADNativeExpressAdViewClass;
typedef System::DelphiInterface<GADNativeExpressAdViewClass> _di_GADNativeExpressAdViewClass;
__interface DELPHIINTERFACE GADNativeExpressAdView;
typedef System::DelphiInterface<GADNativeExpressAdView> _di_GADNativeExpressAdView;
class DELPHICLASS TGADNativeExpressAdView;
__interface DELPHIINTERFACE GADNativeMuteThisAdLoaderOptionsClass;
typedef System::DelphiInterface<GADNativeMuteThisAdLoaderOptionsClass> _di_GADNativeMuteThisAdLoaderOptionsClass;
__interface DELPHIINTERFACE GADNativeMuteThisAdLoaderOptions;
typedef System::DelphiInterface<GADNativeMuteThisAdLoaderOptions> _di_GADNativeMuteThisAdLoaderOptions;
class DELPHICLASS TGADNativeMuteThisAdLoaderOptions;
__interface DELPHIINTERFACE GADRewardBasedVideoAdDelegate;
typedef System::DelphiInterface<GADRewardBasedVideoAdDelegate> _di_GADRewardBasedVideoAdDelegate;
__interface DELPHIINTERFACE GADRewardBasedVideoAdClass;
typedef System::DelphiInterface<GADRewardBasedVideoAdClass> _di_GADRewardBasedVideoAdClass;
__interface DELPHIINTERFACE GADRewardBasedVideoAd;
typedef System::DelphiInterface<GADRewardBasedVideoAd> _di_GADRewardBasedVideoAd;
class DELPHICLASS TGADRewardBasedVideoAd;
__interface DELPHIINTERFACE GADRewardedAdDelegate;
typedef System::DelphiInterface<GADRewardedAdDelegate> _di_GADRewardedAdDelegate;
__interface DELPHIINTERFACE GADRewardedAdMetadataDelegate;
typedef System::DelphiInterface<GADRewardedAdMetadataDelegate> _di_GADRewardedAdMetadataDelegate;
__interface DELPHIINTERFACE GADServerSideVerificationOptionsClass;
typedef System::DelphiInterface<GADServerSideVerificationOptionsClass> _di_GADServerSideVerificationOptionsClass;
__interface DELPHIINTERFACE GADServerSideVerificationOptions;
typedef System::DelphiInterface<GADServerSideVerificationOptions> _di_GADServerSideVerificationOptions;
class DELPHICLASS TGADServerSideVerificationOptions;
__interface DELPHIINTERFACE GADRewardedAdClass;
typedef System::DelphiInterface<GADRewardedAdClass> _di_GADRewardedAdClass;
__interface DELPHIINTERFACE GADRewardedAd;
typedef System::DelphiInterface<GADRewardedAd> _di_GADRewardedAd;
class DELPHICLASS TGADRewardedAd;
__interface DELPHIINTERFACE GADSearchBannerViewClass;
typedef System::DelphiInterface<GADSearchBannerViewClass> _di_GADSearchBannerViewClass;
__interface DELPHIINTERFACE GADSearchBannerView;
typedef System::DelphiInterface<GADSearchBannerView> _di_GADSearchBannerView;
class DELPHICLASS TGADSearchBannerView;
__interface DELPHIINTERFACE GADUnifiedNativeAdDelegate;
typedef System::DelphiInterface<GADUnifiedNativeAdDelegate> _di_GADUnifiedNativeAdDelegate;
__interface DELPHIINTERFACE GADUnifiedNativeAdClass;
typedef System::DelphiInterface<GADUnifiedNativeAdClass> _di_GADUnifiedNativeAdClass;
__interface DELPHIINTERFACE GADUnifiedNativeAd;
typedef System::DelphiInterface<GADUnifiedNativeAd> _di_GADUnifiedNativeAd;
class DELPHICLASS TGADUnifiedNativeAd;
__interface DELPHIINTERFACE GADUnifiedNativeAdLoaderDelegate;
typedef System::DelphiInterface<GADUnifiedNativeAdLoaderDelegate> _di_GADUnifiedNativeAdLoaderDelegate;
__interface DELPHIINTERFACE GADUnifiedNativeAdViewClass;
typedef System::DelphiInterface<GADUnifiedNativeAdViewClass> _di_GADUnifiedNativeAdViewClass;
__interface DELPHIINTERFACE GADUnifiedNativeAdView;
typedef System::DelphiInterface<GADUnifiedNativeAdView> _di_GADUnifiedNativeAdView;
class DELPHICLASS TGADUnifiedNativeAdView;
__interface DELPHIINTERFACE GADUnifiedNativeAdUnconfirmedClickDelegate;
typedef System::DelphiInterface<GADUnifiedNativeAdUnconfirmedClickDelegate> _di_GADUnifiedNativeAdUnconfirmedClickDelegate;
__interface DELPHIINTERFACE GADVideoControllerDelegate;
typedef System::DelphiInterface<GADVideoControllerDelegate> _di_GADVideoControllerDelegate;
__interface DELPHIINTERFACE GADVideoOptionsClass;
typedef System::DelphiInterface<GADVideoOptionsClass> _di_GADVideoOptionsClass;
__interface DELPHIINTERFACE GADVideoOptions;
typedef System::DelphiInterface<GADVideoOptions> _di_GADVideoOptions;
class DELPHICLASS TGADVideoOptions;
__interface DELPHIINTERFACE GADMediationAdRequest;
typedef System::DelphiInterface<GADMediationAdRequest> _di_GADMediationAdRequest;
__interface DELPHIINTERFACE GADMAdNetworkConnector;
typedef System::DelphiInterface<GADMAdNetworkConnector> _di_GADMAdNetworkConnector;
__interface DELPHIINTERFACE GADMAdNetworkAdapter;
typedef System::DelphiInterface<GADMAdNetworkAdapter> _di_GADMAdNetworkAdapter;
__interface DELPHIINTERFACE GADMediatedUnifiedNativeAdNotificationSourceClass;
typedef System::DelphiInterface<GADMediatedUnifiedNativeAdNotificationSourceClass> _di_GADMediatedUnifiedNativeAdNotificationSourceClass;
__interface DELPHIINTERFACE GADMediatedUnifiedNativeAdNotificationSource;
typedef System::DelphiInterface<GADMediatedUnifiedNativeAdNotificationSource> _di_GADMediatedUnifiedNativeAdNotificationSource;
class DELPHICLASS TGADMediatedUnifiedNativeAdNotificationSource;
__interface DELPHIINTERFACE GADMediationAd;
typedef System::DelphiInterface<GADMediationAd> _di_GADMediationAd;
__interface DELPHIINTERFACE GADMediationAdEventDelegate;
typedef System::DelphiInterface<GADMediationAdEventDelegate> _di_GADMediationAdEventDelegate;
__interface DELPHIINTERFACE GADMediationBannerAdEventDelegate;
typedef System::DelphiInterface<GADMediationBannerAdEventDelegate> _di_GADMediationBannerAdEventDelegate;
__interface DELPHIINTERFACE GADMediationInterstitialAdEventDelegate;
typedef System::DelphiInterface<GADMediationInterstitialAdEventDelegate> _di_GADMediationInterstitialAdEventDelegate;
__interface DELPHIINTERFACE GADMediationNativeAdEventDelegate;
typedef System::DelphiInterface<GADMediationNativeAdEventDelegate> _di_GADMediationNativeAdEventDelegate;
__interface DELPHIINTERFACE GADMediationRewardedAdEventDelegate;
typedef System::DelphiInterface<GADMediationRewardedAdEventDelegate> _di_GADMediationRewardedAdEventDelegate;
__interface DELPHIINTERFACE GADMediationCredentialsClass;
typedef System::DelphiInterface<GADMediationCredentialsClass> _di_GADMediationCredentialsClass;
__interface DELPHIINTERFACE GADMediationCredentials;
typedef System::DelphiInterface<GADMediationCredentials> _di_GADMediationCredentials;
class DELPHICLASS TGADMediationCredentials;
__interface DELPHIINTERFACE GADMediationServerConfigurationClass;
typedef System::DelphiInterface<GADMediationServerConfigurationClass> _di_GADMediationServerConfigurationClass;
__interface DELPHIINTERFACE GADMediationServerConfiguration;
typedef System::DelphiInterface<GADMediationServerConfiguration> _di_GADMediationServerConfiguration;
class DELPHICLASS TGADMediationServerConfiguration;
__interface DELPHIINTERFACE GADMediationAdConfigurationClass;
typedef System::DelphiInterface<GADMediationAdConfigurationClass> _di_GADMediationAdConfigurationClass;
__interface DELPHIINTERFACE GADMediationAdConfiguration;
typedef System::DelphiInterface<GADMediationAdConfiguration> _di_GADMediationAdConfiguration;
class DELPHICLASS TGADMediationAdConfiguration;
__interface DELPHIINTERFACE GADMediationBannerAd;
typedef System::DelphiInterface<GADMediationBannerAd> _di_GADMediationBannerAd;
__interface DELPHIINTERFACE GADMediationBannerAdConfigurationClass;
typedef System::DelphiInterface<GADMediationBannerAdConfigurationClass> _di_GADMediationBannerAdConfigurationClass;
__interface DELPHIINTERFACE GADMediationBannerAdConfiguration;
typedef System::DelphiInterface<GADMediationBannerAdConfiguration> _di_GADMediationBannerAdConfiguration;
class DELPHICLASS TGADMediationBannerAdConfiguration;
__interface DELPHIINTERFACE GADMediationInterstitialAd;
typedef System::DelphiInterface<GADMediationInterstitialAd> _di_GADMediationInterstitialAd;
__interface DELPHIINTERFACE GADMediationInterstitialAdConfigurationClass;
typedef System::DelphiInterface<GADMediationInterstitialAdConfigurationClass> _di_GADMediationInterstitialAdConfigurationClass;
__interface DELPHIINTERFACE GADMediationInterstitialAdConfiguration;
typedef System::DelphiInterface<GADMediationInterstitialAdConfiguration> _di_GADMediationInterstitialAdConfiguration;
class DELPHICLASS TGADMediationInterstitialAdConfiguration;
__interface DELPHIINTERFACE GADMediationNativeAd;
typedef System::DelphiInterface<GADMediationNativeAd> _di_GADMediationNativeAd;
__interface DELPHIINTERFACE GADMediationNativeAdConfigurationClass;
typedef System::DelphiInterface<GADMediationNativeAdConfigurationClass> _di_GADMediationNativeAdConfigurationClass;
__interface DELPHIINTERFACE GADMediationNativeAdConfiguration;
typedef System::DelphiInterface<GADMediationNativeAdConfiguration> _di_GADMediationNativeAdConfiguration;
class DELPHICLASS TGADMediationNativeAdConfiguration;
__interface DELPHIINTERFACE GADMediationRewardedAd;
typedef System::DelphiInterface<GADMediationRewardedAd> _di_GADMediationRewardedAd;
__interface DELPHIINTERFACE GADMediationRewardedAdConfigurationClass;
typedef System::DelphiInterface<GADMediationRewardedAdConfigurationClass> _di_GADMediationRewardedAdConfigurationClass;
__interface DELPHIINTERFACE GADMediationRewardedAdConfiguration;
typedef System::DelphiInterface<GADMediationRewardedAdConfiguration> _di_GADMediationRewardedAdConfiguration;
class DELPHICLASS TGADMediationRewardedAdConfiguration;
__interface DELPHIINTERFACE GADMediationAdapter;
typedef System::DelphiInterface<GADMediationAdapter> _di_GADMediationAdapter;
__interface DELPHIINTERFACE GADMRewardBasedVideoAdNetworkAdapter;
typedef System::DelphiInterface<GADMRewardBasedVideoAdNetworkAdapter> _di_GADMRewardBasedVideoAdNetworkAdapter;
__interface DELPHIINTERFACE GADMRewardBasedVideoAdNetworkConnector;
typedef System::DelphiInterface<GADMRewardBasedVideoAdNetworkConnector> _di_GADMRewardBasedVideoAdNetworkConnector;
__interface DELPHIINTERFACE GADRTBMediationSignalsConfigurationClass;
typedef System::DelphiInterface<GADRTBMediationSignalsConfigurationClass> _di_GADRTBMediationSignalsConfigurationClass;
__interface DELPHIINTERFACE GADRTBMediationSignalsConfiguration;
typedef System::DelphiInterface<GADRTBMediationSignalsConfiguration> _di_GADRTBMediationSignalsConfiguration;
class DELPHICLASS TGADRTBMediationSignalsConfiguration;
__interface DELPHIINTERFACE GADRTBRequestParametersClass;
typedef System::DelphiInterface<GADRTBRequestParametersClass> _di_GADRTBRequestParametersClass;
__interface DELPHIINTERFACE GADRTBRequestParameters;
typedef System::DelphiInterface<GADRTBRequestParameters> _di_GADRTBRequestParameters;
class DELPHICLASS TGADRTBRequestParameters;
__interface DELPHIINTERFACE GADRTBAdapter;
typedef System::DelphiInterface<GADRTBAdapter> _di_GADRTBAdapter;
//-- type declarations -------------------------------------------------------
typedef long GADAdapterInitializationState;

typedef long GADAdChoicesPosition;

typedef long GADAdFormat;

typedef Iosapi::Foundation::_di_NSString GADAdLoaderAdType;

typedef Iosapi::Foundation::_di_NSString GADAdMetadataKey;

typedef long GADAdValuePrecision;

typedef long GADErrorCode;

typedef long GADGender;

typedef long GADInAppPurchaseStatus;

typedef Iosapi::Foundation::_di_NSString GADMaxAdContentRating;

typedef long GADMBannerAnimationType;

typedef long GADMediaAspectRatio;

typedef long GADNativeAdImageAdLoaderOptionsOrientation;

typedef long GADPresentationErrorCode;

typedef Iosapi::Foundation::_di_NSString GADUnifiedNativeAssetIdentifier;

struct DECLSPEC_DRECORD GADAdSize
{
public:
	Iosapi::Foundation::NSSize size;
	unsigned long flags;
};


typedef GADAdSize *PGADAdSize;

struct DECLSPEC_DRECORD GADVersionNumber
{
public:
	long majorVersion;
	long minorVersion;
	long patchVersion;
};


typedef GADVersionNumber *PGADVersionNumber;

typedef void __fastcall (__closure *GADAppOpenAdCloseHandler)(void);

typedef void __fastcall (__closure *GADAppOpenAdLoadCompletionHandler)(_di_GADAppOpenAd appOpenAd, Iosapi::Foundation::_di_NSError error);

typedef void __fastcall (__closure *GADInitializationCompletionHandler)(_di_GADInitializationStatus status);

typedef void __fastcall (__closure *GADInstreamAdLoadCompletionHandler)(_di_GADInstreamAd instreamAd, Iosapi::Foundation::_di_NSError error);

typedef void __fastcall (__closure *GADMediationAdapterSetUpCompletionBlock)(Iosapi::Foundation::_di_NSError error);

typedef void * __fastcall (__closure *GADMediationBannerLoadCompletionHandler)(void * ad, Iosapi::Foundation::_di_NSError error);

typedef void * __fastcall (__closure *GADMediationInterstitialLoadCompletionHandler)(void * ad, Iosapi::Foundation::_di_NSError error);

typedef void * __fastcall (__closure *GADMediationNativeLoadCompletionHandler)(void * ad, Iosapi::Foundation::_di_NSError error);

typedef void * __fastcall (__closure *GADMediationRewardedLoadCompletionHandler)(void * ad, Iosapi::Foundation::_di_NSError error);

typedef void __fastcall (__closure *GADNativeAdCustomClickHandler)(Iosapi::Foundation::_di_NSString assetID);

typedef void __fastcall (__closure *GADPaidEventHandler)(_di_GADAdValue value);

typedef void __fastcall (__closure *GADRewardedAdLoadCompletionHandler)(_di_GADRequestError error);

typedef void __fastcall (__closure *GADRTBSignalCompletionHandler)(Iosapi::Foundation::_di_NSString signals, Iosapi::Foundation::_di_NSError error);

__interface  INTERFACE_UUID("{89F777D3-E359-4B3A-BD45-7D1F1229597C}") DFPCustomRenderedBannerViewDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl bannerView(_di_DFPBannerView bannerView, _di_DFPCustomRenderedAd customRenderedAd) = 0 ;
};

__interface  INTERFACE_UUID("{ABF8689E-E9B9-47F3-96A8-C3920BCBB77A}") GADRequestErrorClass  : public Iosapi::Foundation::NSErrorClass 
{
	
};

__interface  INTERFACE_UUID("{40180B03-E23E-4FC9-88F3-C50EAD9D8DD1}") GADRequestError  : public Iosapi::Foundation::NSError 
{
	
};

class PASCALIMPLEMENTATION TGADRequestError : public Macapi::Objectivec::TOCGenericImport__2<_di_GADRequestErrorClass,_di_GADRequestError>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADRequestErrorClass,_di_GADRequestError> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADRequestError(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADRequestErrorClass,_di_GADRequestError>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADRequestError() { }
	
};


__interface  INTERFACE_UUID("{67E6B2B9-EFCE-4A17-8793-26CF0F2B6267}") GADAdLoaderDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl adLoader(_di_GADAdLoader adLoader, _di_GADRequestError error) = 0 ;
	virtual void __cdecl adLoaderDidFinishLoading(_di_GADAdLoader adLoader) = 0 ;
};

__interface  INTERFACE_UUID("{AE29005B-64BE-4615-B576-E7989B4B5273}") GADAdNetworkExtras  : public Macapi::Objectivec::IObjectiveC 
{
	
};

__interface  INTERFACE_UUID("{C68BC342-D749-4763-8001-903CE1E03326}") GADRequestClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl request() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl sdkVersion() = 0 ;
};

__interface  INTERFACE_UUID("{F1F4A949-AFE9-42C1-99BF-63D619CE8414}") GADRequest  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl adNetworkExtrasFor(void * aClass) = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl birthday() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl contentURL() = 0 ;
	virtual long __cdecl gender() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl keywords() = 0 ;
	virtual void __cdecl registerAdNetworkExtras(void * extras) = 0 ;
	virtual void __cdecl removeAdNetworkExtrasFor(void * aClass) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl requestAgent() = 0 ;
	virtual Iosapi::Foundation::_di_NSObject __cdecl scene() = 0 ;
	virtual void __cdecl setBirthday(Iosapi::Foundation::_di_NSDate birthday) = 0 ;
	virtual void __cdecl setBirthdayWithMonth(long month, long day, long year) = 0 ;
	virtual void __cdecl setContentURL(Iosapi::Foundation::_di_NSString contentURL) = 0 ;
	virtual void __cdecl setGender(long gender) = 0 ;
	virtual void __cdecl setKeywords(Iosapi::Foundation::_di_NSArray keywords) = 0 ;
	virtual void __cdecl setLocationWithDescription(Iosapi::Foundation::_di_NSString locationDescription) = 0 ;
	virtual void __cdecl setLocationWithLatitude(double latitude, double longitude, double accuracyInMeters) = 0 ;
	virtual void __cdecl setRequestAgent(Iosapi::Foundation::_di_NSString requestAgent) = 0 ;
	virtual void __cdecl setScene(Iosapi::Foundation::_di_NSObject scene) = 0 ;
	virtual void __cdecl setTestDevices(Iosapi::Foundation::_di_NSArray testDevices) = 0 ;
	virtual void __cdecl tagForChildDirectedTreatment(bool childDirectedTreatment) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl testDevices() = 0 ;
};

class PASCALIMPLEMENTATION TGADRequest : public Macapi::Objectivec::TOCGenericImport__2<_di_GADRequestClass,_di_GADRequest>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADRequestClass,_di_GADRequest> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADRequest(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADRequestClass,_di_GADRequest>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADRequest() { }
	
};


__interface  INTERFACE_UUID("{CF8AA16E-456E-41D2-AF44-4006D526797C}") GADAdLoaderOptionsClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D4496760-47CB-4F8B-B669-1D40B8B2D721}") GADAdLoaderOptions  : public Iosapi::Foundation::NSObject 
{
	
};

class PASCALIMPLEMENTATION TGADAdLoaderOptions : public Macapi::Objectivec::TOCGenericImport__2<_di_GADAdLoaderOptionsClass,_di_GADAdLoaderOptions>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADAdLoaderOptionsClass,_di_GADAdLoaderOptions> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADAdLoaderOptions(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADAdLoaderOptionsClass,_di_GADAdLoaderOptions>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADAdLoaderOptions() { }
	
};


__interface  INTERFACE_UUID("{4D490BA2-011F-4632-8551-F8C6ECB96DD4}") GADAdLoaderClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{C8C2DF6F-0581-43A0-A8FC-11B3820EFCC4}") GADAdLoader  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl adUnitID() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void * __cdecl initWithAdUnitID(Iosapi::Foundation::_di_NSString adUnitID, Iosapi::Uikit::_di_UIViewController rootViewController, Iosapi::Foundation::_di_NSArray adTypes, Iosapi::Foundation::_di_NSArray options) = 0 ;
	virtual bool __cdecl isLoading() = 0 ;
	virtual void __cdecl loadRequest(_di_GADRequest request) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
};

class PASCALIMPLEMENTATION TGADAdLoader : public Macapi::Objectivec::TOCGenericImport__2<_di_GADAdLoaderClass,_di_GADAdLoader>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADAdLoaderClass,_di_GADAdLoader> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADAdLoader(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADAdLoaderClass,_di_GADAdLoader>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADAdLoader() { }
	
};


__interface  INTERFACE_UUID("{C23D7799-884E-498A-896A-5A712039E015}") GADAppEventDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl adView(_di_GADBannerView banner, Iosapi::Foundation::_di_NSString name, Iosapi::Foundation::_di_NSString info) = 0 ;
	virtual void __cdecl interstitial(_di_GADInterstitial interstitial, Iosapi::Foundation::_di_NSString name, Iosapi::Foundation::_di_NSString info) = 0 ;
};

__interface  INTERFACE_UUID("{34461A0A-956E-408D-82DB-AE7D569E49F8}") GADAdSizeDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl adView(_di_GADBannerView bannerView, GADAdSize size) = 0 ;
};

__interface  INTERFACE_UUID("{4592E0C6-7C32-465D-9A5B-3999E03BC88D}") GADAdValueClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{1B295730-CC28-471B-B0C5-FC47012D3694}") GADAdValue  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl currencyCode() = 0 ;
	virtual long __cdecl precision() = 0 ;
	virtual Iosapi::Foundation::_di_NSDecimalNumber __cdecl value() = 0 ;
};

class PASCALIMPLEMENTATION TGADAdValue : public Macapi::Objectivec::TOCGenericImport__2<_di_GADAdValueClass,_di_GADAdValue>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADAdValueClass,_di_GADAdValue> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADAdValue(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADAdValueClass,_di_GADAdValue>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADAdValue() { }
	
};


__interface  INTERFACE_UUID("{CF6B557E-58C2-4DAE-9815-B791E24B1BEF}") GADBannerViewDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl adView(_di_GADBannerView bannerView, _di_GADRequestError error) = 0 ;
	virtual void __cdecl adViewDidDismissScreen(_di_GADBannerView bannerView) = 0 ;
	virtual void __cdecl adViewDidReceiveAd(_di_GADBannerView bannerView) = 0 ;
	virtual void __cdecl adViewWillDismissScreen(_di_GADBannerView bannerView) = 0 ;
	virtual void __cdecl adViewWillLeaveApplication(_di_GADBannerView bannerView) = 0 ;
	virtual void __cdecl adViewWillPresentScreen(_di_GADBannerView bannerView) = 0 ;
};

__interface  INTERFACE_UUID("{EF970370-5B77-48DC-BBD1-CA45AD21A8DA}") GADDefaultInAppPurchaseDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl shouldStartPurchaseForProductID(Iosapi::Foundation::_di_NSString productID, long quantity) = 0 ;
	virtual void __cdecl userDidPayForPurchase(_di_GADDefaultInAppPurchase defaultInAppPurchase) = 0 ;
};

__interface  INTERFACE_UUID("{7FD5836E-7BBF-4D76-8372-93187958449E}") GADInAppPurchaseDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl didReceiveInAppPurchase(_di_GADInAppPurchase purchase) = 0 ;
};

__interface  INTERFACE_UUID("{00A5B14E-D8A6-4CCC-8A0F-A102B665026D}") GADResponseInfoClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{FE873DC2-F870-42EB-A6B2-4F0EDCCE8C41}") GADResponseInfo  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl adNetworkClassName() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl responseIdentifier() = 0 ;
};

class PASCALIMPLEMENTATION TGADResponseInfo : public Macapi::Objectivec::TOCGenericImport__2<_di_GADResponseInfoClass,_di_GADResponseInfo>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADResponseInfoClass,_di_GADResponseInfo> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADResponseInfo(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADResponseInfoClass,_di_GADResponseInfo>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADResponseInfo() { }
	
};


__interface  INTERFACE_UUID("{F560569A-4AE2-4ED1-B89F-944ECB1762CC}") GADBannerViewClass  : public Iosapi::Uikit::UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{470654FF-45A1-426C-9C4D-BDFDC0A659D7}") GADBannerView  : public Iosapi::Uikit::UIView 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl adNetworkClassName() = 0 ;
	virtual GADAdSize __cdecl adSize() = 0 ;
	virtual void * __cdecl adSizeDelegate() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl adUnitID() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual bool __cdecl hasAutoRefreshed() = 0 ;
	virtual void * __cdecl inAppPurchaseDelegate() = 0 ;
	virtual void * __cdecl initWithAdSize(GADAdSize adSize) = 0 /* overload */;
	virtual void * __cdecl initWithAdSize(GADAdSize adSize, Iosapi::Foundation::NSPoint origin) = 0 /* overload */;
	virtual bool __cdecl isAutoloadEnabled() = 0 ;
	virtual void __cdecl loadRequest(_di_GADRequest request) = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl mediatedAdView() = 0 ;
	virtual GADPaidEventHandler __cdecl paidEventHandler() = 0 ;
	virtual _di_GADResponseInfo __cdecl responseInfo() = 0 ;
	virtual Iosapi::Uikit::_di_UIViewController __cdecl rootViewController() = 0 ;
	virtual void __cdecl setAdSize(GADAdSize adSize) = 0 ;
	virtual void __cdecl setAdSizeDelegate(void * adSizeDelegate) = 0 ;
	virtual void __cdecl setAdUnitID(Iosapi::Foundation::_di_NSString adUnitID) = 0 ;
	virtual void __cdecl setAutoloadEnabled(bool autoloadEnabled) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setInAppPurchaseDelegate(void * inAppPurchaseDelegate) = 0 ;
	virtual void __cdecl setPaidEventHandler(GADPaidEventHandler paidEventHandler) = 0 ;
	virtual void __cdecl setRootViewController(Iosapi::Uikit::_di_UIViewController rootViewController) = 0 ;
};

class PASCALIMPLEMENTATION TGADBannerView : public Macapi::Objectivec::TOCGenericImport__2<_di_GADBannerViewClass,_di_GADBannerView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADBannerViewClass,_di_GADBannerView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADBannerView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADBannerViewClass,_di_GADBannerView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADBannerView() { }
	
};


__interface  INTERFACE_UUID("{2CC1D25D-E9FE-45AB-9B69-486D5F80F342}") GADVideoControllerClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{57FAFF14-FF7C-459F-BEE6-A14B5A5BF74C}") GADVideoController  : public Iosapi::Foundation::NSObject 
{
	virtual double __cdecl aspectRatio() = 0 ;
	virtual bool __cdecl clickToExpandEnabled() = 0 ;
	virtual bool __cdecl customControlsEnabled() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual bool __cdecl hasVideoContent() = 0 ;
	virtual void __cdecl pause() = 0 ;
	virtual void __cdecl play() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setMute(bool mute) = 0 ;
	virtual void __cdecl stop() = 0 ;
};

class PASCALIMPLEMENTATION TGADVideoController : public Macapi::Objectivec::TOCGenericImport__2<_di_GADVideoControllerClass,_di_GADVideoController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADVideoControllerClass,_di_GADVideoController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADVideoController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADVideoControllerClass,_di_GADVideoController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADVideoController() { }
	
};


__interface  INTERFACE_UUID("{A11F7960-977E-4473-A666-E27FE965666C}") DFPBannerAdLoaderDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl adLoader(_di_GADAdLoader adLoader, _di_DFPBannerView bannerView) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl validBannerSizesForAdLoader(_di_GADAdLoader adLoader) = 0 ;
};

__interface  INTERFACE_UUID("{52B72AEC-7AFC-48F7-9295-8263515B80EE}") DFPBannerViewClass  : public GADBannerViewClass 
{
	
};

__interface  INTERFACE_UUID("{D3859CBC-AAC7-43F7-A2DD-FAF5A2AC4304}") DFPBannerView  : public GADBannerView 
{
	HIDESBASE virtual void * __cdecl adSizeDelegate() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSString __cdecl adUnitID() = 0 ;
	virtual void * __cdecl appEventDelegate() = 0 ;
	virtual void * __cdecl customRenderedBannerViewDelegate() = 0 ;
	virtual bool __cdecl enableManualImpressions() = 0 ;
	virtual void __cdecl recordImpression() = 0 ;
	virtual void __cdecl resize(GADAdSize size) = 0 ;
	virtual void __cdecl setAdOptions(Iosapi::Foundation::_di_NSArray adOptions) = 0 ;
	HIDESBASE virtual void __cdecl setAdSizeDelegate(void * adSizeDelegate) = 0 ;
	HIDESBASE virtual void __cdecl setAdUnitID(Iosapi::Foundation::_di_NSString adUnitID) = 0 ;
	virtual void __cdecl setAppEventDelegate(void * appEventDelegate) = 0 ;
	virtual void __cdecl setCustomRenderedBannerViewDelegate(void * customRenderedBannerViewDelegate) = 0 ;
	virtual void __cdecl setEnableManualImpressions(bool enableManualImpressions) = 0 ;
	virtual void __cdecl setValidAdSizes(Iosapi::Foundation::_di_NSArray validAdSizes) = 0 ;
	virtual void __cdecl setValidAdSizesWithSizes(PGADAdSize firstSize) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl validAdSizes() = 0 ;
	virtual _di_GADVideoController __cdecl videoController() = 0 ;
};

class PASCALIMPLEMENTATION TDFPBannerView : public Macapi::Objectivec::TOCGenericImport__2<_di_DFPBannerViewClass,_di_DFPBannerView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_DFPBannerViewClass,_di_DFPBannerView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TDFPBannerView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_DFPBannerViewClass,_di_DFPBannerView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TDFPBannerView() { }
	
};


__interface  INTERFACE_UUID("{45492F7C-AEEB-4875-83A3-7973DE2944F1}") DFPBannerViewOptionsClass  : public GADAdLoaderOptionsClass 
{
	
};

__interface  INTERFACE_UUID("{CAABB91C-2F3A-4ADF-97B1-94BA0A09F15C}") DFPBannerViewOptions  : public GADAdLoaderOptions 
{
	virtual void * __cdecl adSizeDelegate() = 0 ;
	virtual void * __cdecl appEventDelegate() = 0 ;
	virtual bool __cdecl enableManualImpressions() = 0 ;
	virtual void __cdecl setAdSizeDelegate(void * adSizeDelegate) = 0 ;
	virtual void __cdecl setAppEventDelegate(void * appEventDelegate) = 0 ;
	virtual void __cdecl setEnableManualImpressions(bool enableManualImpressions) = 0 ;
};

class PASCALIMPLEMENTATION TDFPBannerViewOptions : public Macapi::Objectivec::TOCGenericImport__2<_di_DFPBannerViewOptionsClass,_di_DFPBannerViewOptions>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_DFPBannerViewOptionsClass,_di_DFPBannerViewOptions> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TDFPBannerViewOptions(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_DFPBannerViewOptionsClass,_di_DFPBannerViewOptions>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TDFPBannerViewOptions() { }
	
};


__interface  INTERFACE_UUID("{EBB49244-7A4C-4910-A840-908590B6F667}") DFPCustomRenderedAdClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{B12E0D32-15B8-42E0-AD6D-EB67437E98DD}") DFPCustomRenderedAd  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSURL __cdecl adBaseURL() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl adHTML() = 0 ;
	virtual void __cdecl finishedRenderingAdView(Iosapi::Uikit::_di_UIView view) = 0 ;
	virtual void __cdecl recordClick() = 0 ;
	virtual void __cdecl recordImpression() = 0 ;
};

class PASCALIMPLEMENTATION TDFPCustomRenderedAd : public Macapi::Objectivec::TOCGenericImport__2<_di_DFPCustomRenderedAdClass,_di_DFPCustomRenderedAd>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_DFPCustomRenderedAdClass,_di_DFPCustomRenderedAd> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TDFPCustomRenderedAd(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_DFPCustomRenderedAdClass,_di_DFPCustomRenderedAd>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TDFPCustomRenderedAd() { }
	
};


__interface  INTERFACE_UUID("{B502ACB0-4046-4446-8D7F-94D369351C22}") DFPCustomRenderedInterstitialDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl interstitial(_di_DFPInterstitial interstitial, _di_DFPCustomRenderedAd customRenderedAd) = 0 ;
};

__interface  INTERFACE_UUID("{79726360-4247-4FD8-B0B4-6CFF96F60AD8}") GADInterstitialDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl interstitial(_di_GADInterstitial ad, _di_GADRequestError error) = 0 ;
	virtual void __cdecl interstitialDidDismissScreen(_di_GADInterstitial ad) = 0 ;
	virtual void __cdecl interstitialDidFailToPresentScreen(_di_GADInterstitial ad) = 0 ;
	virtual void __cdecl interstitialDidReceiveAd(_di_GADInterstitial ad) = 0 ;
	virtual void __cdecl interstitialWillDismissScreen(_di_GADInterstitial ad) = 0 ;
	virtual void __cdecl interstitialWillLeaveApplication(_di_GADInterstitial ad) = 0 ;
	virtual void __cdecl interstitialWillPresentScreen(_di_GADInterstitial ad) = 0 ;
};

__interface  INTERFACE_UUID("{AB22715C-A80B-4FCB-898F-41852D775E0B}") GADInterstitialClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{C9B6FC27-957D-47DA-B0BD-3D643F19E474}") GADInterstitial  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl adNetworkClassName() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl adUnitID() = 0 ;
	virtual bool __cdecl canPresentFromRootViewController(Iosapi::Uikit::_di_UIViewController rootViewController, Iosapi::Foundation::PNSError error) = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual bool __cdecl hasBeenUsed() = 0 ;
	virtual void * __cdecl inAppPurchaseDelegate() = 0 ;
	virtual void * __cdecl initWithAdUnitID(Iosapi::Foundation::_di_NSString adUnitID) = 0 ;
	virtual bool __cdecl isReady() = 0 ;
	virtual void __cdecl loadRequest(_di_GADRequest request) = 0 ;
	virtual GADPaidEventHandler __cdecl paidEventHandler() = 0 ;
	virtual void __cdecl presentFromRootViewController(Iosapi::Uikit::_di_UIViewController rootViewController) = 0 ;
	virtual _di_GADResponseInfo __cdecl responseInfo() = 0 ;
	virtual void __cdecl setAdUnitID(Iosapi::Foundation::_di_NSString adUnitID) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setInAppPurchaseDelegate(void * inAppPurchaseDelegate) = 0 ;
	virtual void __cdecl setPaidEventHandler(GADPaidEventHandler paidEventHandler) = 0 ;
};

class PASCALIMPLEMENTATION TGADInterstitial : public Macapi::Objectivec::TOCGenericImport__2<_di_GADInterstitialClass,_di_GADInterstitial>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADInterstitialClass,_di_GADInterstitial> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADInterstitial(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADInterstitialClass,_di_GADInterstitial>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADInterstitial() { }
	
};


__interface  INTERFACE_UUID("{3FB46584-F78F-4120-89EB-9343A949FE31}") DFPInterstitialClass  : public GADInterstitialClass 
{
	
};

__interface  INTERFACE_UUID("{53EBA9DC-87CB-417D-850D-C300B5CC588F}") DFPInterstitial  : public GADInterstitial 
{
	virtual void * __cdecl appEventDelegate() = 0 ;
	virtual void * __cdecl customRenderedInterstitialDelegate() = 0 ;
	HIDESBASE virtual void * __cdecl initWithAdUnitID(Iosapi::Foundation::_di_NSString adUnitID) = 0 ;
	virtual void __cdecl setAppEventDelegate(void * appEventDelegate) = 0 ;
	virtual void __cdecl setCustomRenderedInterstitialDelegate(void * customRenderedInterstitialDelegate) = 0 ;
};

class PASCALIMPLEMENTATION TDFPInterstitial : public Macapi::Objectivec::TOCGenericImport__2<_di_DFPInterstitialClass,_di_DFPInterstitial>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_DFPInterstitialClass,_di_DFPInterstitial> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TDFPInterstitial(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_DFPInterstitialClass,_di_DFPInterstitial>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TDFPInterstitial() { }
	
};


__interface  INTERFACE_UUID("{856161AF-BC55-4021-948C-9E9100E0C242}") DFPRequestClass  : public GADRequestClass 
{
	
};

__interface  INTERFACE_UUID("{0569D11D-88A6-4D3E-BD27-06D8F93774D1}") DFPRequest  : public GADRequest 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl categoryExclusions() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl customTargeting() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl publisherProvidedID() = 0 ;
	virtual void __cdecl setCategoryExclusions(Iosapi::Foundation::_di_NSArray categoryExclusions) = 0 ;
	virtual void __cdecl setCustomTargeting(Iosapi::Foundation::_di_NSDictionary customTargeting) = 0 ;
	virtual void __cdecl setPublisherProvidedID(Iosapi::Foundation::_di_NSString publisherProvidedID) = 0 ;
};

class PASCALIMPLEMENTATION TDFPRequest : public Macapi::Objectivec::TOCGenericImport__2<_di_DFPRequestClass,_di_DFPRequest>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_DFPRequestClass,_di_DFPRequest> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TDFPRequest(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_DFPRequestClass,_di_DFPRequest>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TDFPRequest() { }
	
};


__interface  INTERFACE_UUID("{50F7A7B5-45CA-4986-84FB-16D446C86A41}") GADAdChoicesViewClass  : public Iosapi::Uikit::UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{021E125A-6B86-44FA-9454-D2AED4839D95}") GADAdChoicesView  : public Iosapi::Uikit::UIView 
{
	
};

class PASCALIMPLEMENTATION TGADAdChoicesView : public Macapi::Objectivec::TOCGenericImport__2<_di_GADAdChoicesViewClass,_di_GADAdChoicesView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADAdChoicesViewClass,_di_GADAdChoicesView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADAdChoicesView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADAdChoicesViewClass,_di_GADAdChoicesView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADAdChoicesView() { }
	
};


__interface  INTERFACE_UUID("{16B3A5CE-40B4-40E6-A41A-E841C38DCDBF}") GADAudioVideoManagerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl audioVideoManagerDidPauseAllVideo(_di_GADAudioVideoManager audioVideoManager) = 0 ;
	virtual void __cdecl audioVideoManagerDidStopPlayingAudio(_di_GADAudioVideoManager audioVideoManager) = 0 ;
	virtual void __cdecl audioVideoManagerWillPlayAudio(_di_GADAudioVideoManager audioVideoManager) = 0 ;
	virtual void __cdecl audioVideoManagerWillPlayVideo(_di_GADAudioVideoManager audioVideoManager) = 0 ;
};

__interface  INTERFACE_UUID("{5BBEFFB9-DC4A-4FB8-9832-66958E46EEBA}") GADAudioVideoManagerClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{865AE32A-A4A8-4166-816E-55E0B2E94536}") GADAudioVideoManager  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl audioSessionIsApplicationManaged() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl setAudioSessionIsApplicationManaged(bool audioSessionIsApplicationManaged) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
};

class PASCALIMPLEMENTATION TGADAudioVideoManager : public Macapi::Objectivec::TOCGenericImport__2<_di_GADAudioVideoManagerClass,_di_GADAudioVideoManager>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADAudioVideoManagerClass,_di_GADAudioVideoManager> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADAudioVideoManager(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADAudioVideoManagerClass,_di_GADAudioVideoManager>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADAudioVideoManager() { }
	
};


__interface  INTERFACE_UUID("{B2C5AFFF-F2A3-4D6E-9A1C-C488DEC94629}") GADAdapterStatusClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{73EB922A-4A59-46FB-8F45-AF8739603E4B}") GADAdapterStatus  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl description() = 0 ;
	virtual double __cdecl latency() = 0 ;
	virtual long __cdecl state() = 0 ;
};

class PASCALIMPLEMENTATION TGADAdapterStatus : public Macapi::Objectivec::TOCGenericImport__2<_di_GADAdapterStatusClass,_di_GADAdapterStatus>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADAdapterStatusClass,_di_GADAdapterStatus> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADAdapterStatus(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADAdapterStatusClass,_di_GADAdapterStatus>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADAdapterStatus() { }
	
};


__interface  INTERFACE_UUID("{72D1257D-6FDB-4129-92A2-867BC48166E8}") GADInitializationStatusClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{67881E70-9B87-481A-9295-F6AE917A1182}") GADInitializationStatus  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl adapterStatusesByClassName() = 0 ;
};

class PASCALIMPLEMENTATION TGADInitializationStatus : public Macapi::Objectivec::TOCGenericImport__2<_di_GADInitializationStatusClass,_di_GADInitializationStatus>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADInitializationStatusClass,_di_GADInitializationStatus> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADInitializationStatus(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADInitializationStatusClass,_di_GADInitializationStatus>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADInitializationStatus() { }
	
};


__interface  INTERFACE_UUID("{72A3EDB5-BB0E-4051-A5A4-227C5D5B6C7C}") GADRequestConfigurationClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{66DF90E0-2623-4554-AFE4-8B96E1B42A76}") GADRequestConfiguration  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl maxAdContentRating() = 0 ;
	virtual void __cdecl setMaxAdContentRating(Iosapi::Foundation::_di_NSString maxAdContentRating) = 0 ;
	virtual void __cdecl setTestDeviceIdentifiers(Iosapi::Foundation::_di_NSArray testDeviceIdentifiers) = 0 ;
	virtual void __cdecl tagForChildDirectedTreatment(bool childDirectedTreatment) = 0 ;
	virtual void __cdecl tagForUnderAgeOfConsent(bool underAgeOfConsent) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl testDeviceIdentifiers() = 0 ;
};

class PASCALIMPLEMENTATION TGADRequestConfiguration : public Macapi::Objectivec::TOCGenericImport__2<_di_GADRequestConfigurationClass,_di_GADRequestConfiguration>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADRequestConfigurationClass,_di_GADRequestConfiguration> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADRequestConfiguration(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADRequestConfigurationClass,_di_GADRequestConfiguration>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADRequestConfiguration() { }
	
};


__interface  INTERFACE_UUID("{584FD714-49BA-41D0-9A24-00CDE7881FD6}") GADMobileAdsClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void __cdecl configureWithApplicationID(Iosapi::Foundation::_di_NSString applicationID) = 0 ;
	virtual void __cdecl disableAutomatedInAppPurchaseReporting() = 0 ;
	virtual void __cdecl disableSDKCrashReporting() = 0 ;
	virtual _di_GADMobileAds __cdecl sharedInstance() = 0 ;
};

__interface  INTERFACE_UUID("{27D7E6D6-FF14-4564-9E54-CD76CAEE4A8B}") GADMobileAds  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl applicationMuted() = 0 ;
	virtual float __cdecl applicationVolume() = 0 ;
	virtual _di_GADAudioVideoManager __cdecl audioVideoManager() = 0 ;
	virtual _di_GADInitializationStatus __cdecl initializationStatus() = 0 ;
	virtual bool __cdecl isSDKVersionAtLeastMajor(long major, long minor, long patch) = 0 ;
	virtual _di_GADRequestConfiguration __cdecl requestConfiguration() = 0 ;
	virtual void __cdecl setApplicationMuted(bool applicationMuted) = 0 ;
	virtual void __cdecl setApplicationVolume(float applicationVolume) = 0 ;
	virtual void __cdecl startWithCompletionHandler(GADInitializationCompletionHandler completionHandler) = 0 ;
};

class PASCALIMPLEMENTATION TGADMobileAds : public Macapi::Objectivec::TOCGenericImport__2<_di_GADMobileAdsClass,_di_GADMobileAds>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADMobileAdsClass,_di_GADMobileAds> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADMobileAds(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADMobileAdsClass,_di_GADMobileAds>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADMobileAds() { }
	
};


__interface  INTERFACE_UUID("{A65E8ED6-E4ED-43B8-91F3-1B871F346152}") GADAdRewardClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{4D251B9B-BA77-46E8-92A7-3541A8FCC326}") GADAdReward  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl type() = 0 ;
	virtual Iosapi::Foundation::_di_NSDecimalNumber __cdecl amount() = 0 ;
	virtual void * __cdecl initWithRewardType(Iosapi::Foundation::_di_NSString rewardType, Iosapi::Foundation::_di_NSDecimalNumber rewardAmount) = 0 ;
};

class PASCALIMPLEMENTATION TGADAdReward : public Macapi::Objectivec::TOCGenericImport__2<_di_GADAdRewardClass,_di_GADAdReward>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADAdRewardClass,_di_GADAdReward> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADAdReward(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADAdRewardClass,_di_GADAdReward>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADAdReward() { }
	
};


__interface  INTERFACE_UUID("{1EFABB77-CEC1-48A9-B345-4DA7DEF6FE88}") GADAppOpenAdClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void __cdecl loadWithAdUnitID(Iosapi::Foundation::_di_NSString adUnitID, _di_GADRequest request, long orientation, GADAppOpenAdLoadCompletionHandler completionHandler) = 0 ;
};

__interface  INTERFACE_UUID("{FB4700CB-7938-4550-93F4-FB8F573B44B2}") GADAppOpenAd  : public Iosapi::Foundation::NSObject 
{
	virtual GADPaidEventHandler __cdecl paidEventHandler() = 0 ;
	virtual _di_GADResponseInfo __cdecl responseInfo() = 0 ;
	virtual void __cdecl setPaidEventHandler(GADPaidEventHandler paidEventHandler) = 0 ;
};

class PASCALIMPLEMENTATION TGADAppOpenAd : public Macapi::Objectivec::TOCGenericImport__2<_di_GADAppOpenAdClass,_di_GADAppOpenAd>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADAppOpenAdClass,_di_GADAppOpenAd> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADAppOpenAd(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADAppOpenAdClass,_di_GADAppOpenAd>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADAppOpenAd() { }
	
};


__interface  INTERFACE_UUID("{ADAD9001-DADB-4392-AB68-3917E33CF7FC}") GADAppOpenAdViewClass  : public Iosapi::Uikit::UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{87D37C0B-CF78-44EB-AD2D-44BF7FF9D8AB}") GADAppOpenAdView  : public Iosapi::Uikit::UIView 
{
	virtual GADAppOpenAdCloseHandler __cdecl adCloseHandler() = 0 ;
	virtual _di_GADAppOpenAd __cdecl appOpenAd() = 0 ;
	virtual void __cdecl setAdCloseHandler(GADAppOpenAdCloseHandler adCloseHandler) = 0 ;
	virtual void __cdecl setAppOpenAd(_di_GADAppOpenAd appOpenAd) = 0 ;
};

class PASCALIMPLEMENTATION TGADAppOpenAdView : public Macapi::Objectivec::TOCGenericImport__2<_di_GADAppOpenAdViewClass,_di_GADAppOpenAdView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADAppOpenAdViewClass,_di_GADAppOpenAdView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADAppOpenAdView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADAppOpenAdViewClass,_di_GADAppOpenAdView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADAppOpenAdView() { }
	
};


__interface  INTERFACE_UUID("{4B34EFCE-9A29-4ABB-8BDC-2843100A7512}") GADCustomEventBannerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl customEventBannerClickDidOccurInAd(void * customEvent, Iosapi::Uikit::_di_UIView view) = 0 ;
	virtual void __cdecl customEventBannerDidDismissModal(void * customEvent) = 0 ;
	virtual void __cdecl customEventBannerDidFailAd(void * customEvent, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl customEventBannerDidReceiveAd(void * customEvent, Iosapi::Uikit::_di_UIView view) = 0 ;
	virtual void __cdecl customEventBannerWasClicked(void * customEvent) = 0 ;
	virtual void __cdecl customEventBannerWillDismissModal(void * customEvent) = 0 ;
	virtual void __cdecl customEventBannerWillLeaveApplication(void * customEvent) = 0 ;
	virtual void __cdecl customEventBannerWillPresentModal(void * customEvent) = 0 ;
	virtual Iosapi::Uikit::_di_UIViewController __cdecl viewControllerForPresentingModalView() = 0 ;
};

__interface  INTERFACE_UUID("{18B27CE2-7889-467A-95A1-774DADA78C97}") GADCustomEventRequestClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{C7833651-3E8B-4527-9528-E85650899905}") GADCustomEventRequest  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl additionalParameters() = 0 ;
	virtual bool __cdecl isTesting() = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl userBirthday() = 0 ;
	virtual long __cdecl userGender() = 0 ;
	virtual bool __cdecl userHasLocation() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl userKeywords() = 0 ;
	virtual double __cdecl userLatitude() = 0 ;
	virtual double __cdecl userLocationAccuracyInMeters() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl userLocationDescription() = 0 ;
	virtual double __cdecl userLongitude() = 0 ;
};

class PASCALIMPLEMENTATION TGADCustomEventRequest : public Macapi::Objectivec::TOCGenericImport__2<_di_GADCustomEventRequestClass,_di_GADCustomEventRequest>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADCustomEventRequestClass,_di_GADCustomEventRequest> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADCustomEventRequest(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADCustomEventRequestClass,_di_GADCustomEventRequest>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADCustomEventRequest() { }
	
};


__interface  INTERFACE_UUID("{4BE4624C-190B-402A-94CE-4D4F27E25C96}") GADCustomEventBanner  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl requestBannerAd(GADAdSize adSize, Iosapi::Foundation::_di_NSString serverParameter, Iosapi::Foundation::_di_NSString serverLabel, _di_GADCustomEventRequest request) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
};

__interface  INTERFACE_UUID("{8F170E04-3BC5-4297-A163-022AB719B2D1}") GADCustomEventExtrasClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{38DA0BA5-D8AD-45C7-BA11-54543BE0E286}") GADCustomEventExtras  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl allExtras() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl extrasForLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual void __cdecl removeAllExtras() = 0 ;
	virtual void __cdecl setExtras(Iosapi::Foundation::_di_NSDictionary extras, Iosapi::Foundation::_di_NSString label) = 0 ;
};

class PASCALIMPLEMENTATION TGADCustomEventExtras : public Macapi::Objectivec::TOCGenericImport__2<_di_GADCustomEventExtrasClass,_di_GADCustomEventExtras>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADCustomEventExtrasClass,_di_GADCustomEventExtras> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADCustomEventExtras(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADCustomEventExtrasClass,_di_GADCustomEventExtras>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADCustomEventExtras() { }
	
};


__interface  INTERFACE_UUID("{15A6F037-0CD3-4A00-A826-4F826F87C598}") GADCustomEventInterstitialDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl customEventInterstitial(void * customEvent, Iosapi::Foundation::_di_NSObject ad) = 0 /* overload */;
	virtual void __cdecl customEventInterstitial(void * customEvent, Iosapi::Foundation::_di_NSError error) = 0 /* overload */;
	virtual void __cdecl customEventInterstitialDidDismiss(void * customEvent) = 0 ;
	virtual void __cdecl customEventInterstitialDidReceiveAd(void * customEvent) = 0 ;
	virtual void __cdecl customEventInterstitialWasClicked(void * customEvent) = 0 ;
	virtual void __cdecl customEventInterstitialWillDismiss(void * customEvent) = 0 ;
	virtual void __cdecl customEventInterstitialWillLeaveApplication(void * customEvent) = 0 ;
	virtual void __cdecl customEventInterstitialWillPresent(void * customEvent) = 0 ;
};

__interface  INTERFACE_UUID("{6120C0A6-2612-443C-B508-9187FB63F41E}") GADCustomEventInterstitial  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl presentFromRootViewController(Iosapi::Uikit::_di_UIViewController rootViewController) = 0 ;
	virtual void __cdecl requestInterstitialAdWithParameter(Iosapi::Foundation::_di_NSString serverParameter, Iosapi::Foundation::_di_NSString serverLabel, _di_GADCustomEventRequest request) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
};

__interface  INTERFACE_UUID("{06BB0CF4-1BA2-41B1-8303-130D7EB31BF9}") GADCustomEventNativeAd  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual bool __cdecl handlesUserClicks() = 0 ;
	virtual bool __cdecl handlesUserImpressions() = 0 ;
	virtual void __cdecl requestNativeAdWithParameter(Iosapi::Foundation::_di_NSString serverParameter, _di_GADCustomEventRequest request, Iosapi::Foundation::_di_NSArray adTypes, Iosapi::Foundation::_di_NSArray options, Iosapi::Uikit::_di_UIViewController rootViewController) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
};

__interface  INTERFACE_UUID("{FEBD08EF-2AB5-46FB-AB7C-3E7F16065ACD}") GADNativeAdImageClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{3389B185-4B62-4E16-A245-265012169E30}") GADNativeAdImage  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Uikit::_di_UIImage __cdecl image() = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl imageURL() = 0 ;
	virtual void * __cdecl initWithImage(Iosapi::Uikit::_di_UIImage image) = 0 ;
	virtual void * __cdecl initWithURL(Iosapi::Foundation::_di_NSURL URL, double scale) = 0 ;
	virtual double __cdecl scale() = 0 ;
};

class PASCALIMPLEMENTATION TGADNativeAdImage : public Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeAdImageClass,_di_GADNativeAdImage>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeAdImageClass,_di_GADNativeAdImage> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADNativeAdImage(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeAdImageClass,_di_GADNativeAdImage>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADNativeAdImage() { }
	
};


__interface  INTERFACE_UUID("{0BFA45E5-E613-4A90-B976-C0A6155C5864}") GADMediatedUnifiedNativeAd  : public Macapi::Objectivec::IObjectiveC 
{
	virtual Iosapi::Uikit::_di_UIView __cdecl adChoicesView() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl advertiser() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl body() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl callToAction() = 0 ;
	virtual double __cdecl currentTime() = 0 ;
	virtual void __cdecl didRecordClickOnAssetWithName(Iosapi::Foundation::_di_NSString assetName, Iosapi::Uikit::_di_UIView view, Iosapi::Uikit::_di_UIViewController viewController) = 0 ;
	virtual void __cdecl didRecordImpression() = 0 ;
	virtual void __cdecl didRenderInView(Iosapi::Uikit::_di_UIView view, Iosapi::Foundation::_di_NSDictionary clickableAssetViews, Iosapi::Foundation::_di_NSDictionary nonclickableAssetViews, Iosapi::Uikit::_di_UIViewController viewController) = 0 ;
	virtual void __cdecl didUntrackView(Iosapi::Uikit::_di_UIView view) = 0 ;
	virtual double __cdecl duration() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl extraAssets() = 0 ;
	virtual bool __cdecl hasVideoContent() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl headline() = 0 ;
	virtual _di_GADNativeAdImage __cdecl icon() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl images() = 0 ;
	virtual double __cdecl mediaContentAspectRatio() = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl mediaView() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl price() = 0 ;
	virtual Iosapi::Foundation::_di_NSDecimalNumber __cdecl starRating() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl store() = 0 ;
};

__interface  INTERFACE_UUID("{554DDADD-34B4-4CF0-9AE5-430022B80E09}") GADCustomEventNativeAdDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl customEventNativeAd(void * customEventNativeAd, Iosapi::Foundation::_di_NSError error) = 0 /* overload */;
	virtual void __cdecl customEventNativeAd(void * customEventNativeAd, void * mediatedUnifiedNativeAd) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{79427340-CD5A-4C9C-A4F2-C17BD4D0809C}") GADDebugOptionsViewControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl debugOptionsViewControllerDidDismiss(_di_GADDebugOptionsViewController controller) = 0 ;
};

__interface  INTERFACE_UUID("{E7909906-BEE2-4A06-A4CA-5C6D1FF67CFA}") GADDebugOptionsViewControllerClass  : public Iosapi::Uikit::UIViewControllerClass 
{
	virtual void * __cdecl debugOptionsViewControllerWithAdUnitID(Iosapi::Foundation::_di_NSString adUnitID) = 0 ;
};

__interface  INTERFACE_UUID("{F679D6A6-3834-4F03-B8E5-A10D7049B45B}") GADDebugOptionsViewController  : public Iosapi::Uikit::UIViewController 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
};

class PASCALIMPLEMENTATION TGADDebugOptionsViewController : public Macapi::Objectivec::TOCGenericImport__2<_di_GADDebugOptionsViewControllerClass,_di_GADDebugOptionsViewController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADDebugOptionsViewControllerClass,_di_GADDebugOptionsViewController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADDebugOptionsViewController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADDebugOptionsViewControllerClass,_di_GADDebugOptionsViewController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADDebugOptionsViewController() { }
	
};


__interface  INTERFACE_UUID("{E9B2FAB9-819E-4530-9C8B-93F76E975696}") GADDelayedAdRenderingDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl adLoader(_di_GADAdLoader adLoader, void * resumeHandler) = 0 ;
};

__interface  INTERFACE_UUID("{4E6A9CBC-2A54-4EB4-A853-3E36137FE8F7}") GADDelayedAdRenderingOptionsClass  : public GADAdLoaderOptionsClass 
{
	
};

__interface  INTERFACE_UUID("{261645D1-0B8F-4CBF-8336-22C816264BB0}") GADDelayedAdRenderingOptions  : public GADAdLoaderOptions 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
};

class PASCALIMPLEMENTATION TGADDelayedAdRenderingOptions : public Macapi::Objectivec::TOCGenericImport__2<_di_GADDelayedAdRenderingOptionsClass,_di_GADDelayedAdRenderingOptions>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADDelayedAdRenderingOptionsClass,_di_GADDelayedAdRenderingOptions> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADDelayedAdRenderingOptions(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADDelayedAdRenderingOptionsClass,_di_GADDelayedAdRenderingOptions>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADDelayedAdRenderingOptions() { }
	
};


__interface  INTERFACE_UUID("{01969CAC-E87D-4077-B4FA-CECBD286072B}") GADDisplayAdMeasurementClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D508706D-1211-4A55-8BA4-1BA0283DA1D8}") GADDisplayAdMeasurement  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setView(Iosapi::Uikit::_di_UIView view) = 0 ;
	virtual bool __cdecl startWithError(Iosapi::Foundation::PNSError error) = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl view() = 0 ;
};

class PASCALIMPLEMENTATION TGADDisplayAdMeasurement : public Macapi::Objectivec::TOCGenericImport__2<_di_GADDisplayAdMeasurementClass,_di_GADDisplayAdMeasurement>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADDisplayAdMeasurementClass,_di_GADDisplayAdMeasurement> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADDisplayAdMeasurement(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADDisplayAdMeasurementClass,_di_GADDisplayAdMeasurement>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADDisplayAdMeasurement() { }
	
};


__interface  INTERFACE_UUID("{08385F87-520C-4D58-840B-065DF5ECFD6D}") GADDynamicHeightSearchRequestClass  : public GADRequestClass 
{
	
};

__interface  INTERFACE_UUID("{B35CC3A4-4CC7-4AF3-8E82-290E6433ABB2}") GADDynamicHeightSearchRequest  : public GADRequest 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl adBorderColor() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl adBorderCSSSelections() = 0 ;
	virtual double __cdecl adjustableLineHeight() = 0 ;
	virtual long __cdecl adPage() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl adSeparatorColor() = 0 ;
	virtual bool __cdecl adTestEnabled() = 0 ;
	virtual double __cdecl annotationFontSize() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl annotationTextColor() = 0 ;
	virtual double __cdecl attributionBottomSpacing() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl attributionFontFamily() = 0 ;
	virtual double __cdecl attributionFontSize() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl attributionTextColor() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl backgroundColor() = 0 ;
	virtual bool __cdecl boldTitleEnabled() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl borderColor() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl borderCSSSelections() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl channel() = 0 ;
	virtual bool __cdecl clickToCallExtensionEnabled() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl CSSWidth() = 0 ;
	virtual double __cdecl descriptionFontSize() = 0 ;
	virtual bool __cdecl detailedAttributionExtensionEnabled() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl domainLinkColor() = 0 ;
	virtual double __cdecl domainLinkFontSize() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl fontFamily() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl hostLanguage() = 0 ;
	virtual bool __cdecl locationExtensionEnabled() = 0 ;
	virtual double __cdecl locationExtensionFontSize() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl locationExtensionTextColor() = 0 ;
	virtual bool __cdecl longerHeadlinesExtensionEnabled() = 0 ;
	virtual long __cdecl numberOfAds() = 0 ;
	virtual bool __cdecl plusOnesExtensionEnabled() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl query() = 0 ;
	virtual bool __cdecl sellerRatingsExtensionEnabled() = 0 ;
	virtual void __cdecl setAdBorderColor(Iosapi::Foundation::_di_NSString adBorderColor) = 0 ;
	virtual void __cdecl setAdBorderCSSSelections(Iosapi::Foundation::_di_NSString adBorderCSSSelections) = 0 ;
	virtual void __cdecl setAdjustableLineHeight(double adjustableLineHeight) = 0 ;
	virtual void __cdecl setAdPage(long adPage) = 0 ;
	virtual void __cdecl setAdSeparatorColor(Iosapi::Foundation::_di_NSString adSeparatorColor) = 0 ;
	virtual void __cdecl setAdTestEnabled(bool adTestEnabled) = 0 ;
	virtual void __cdecl setAdvancedOptionValue(void * value, Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual void __cdecl setAnnotationFontSize(double annotationFontSize) = 0 ;
	virtual void __cdecl setAnnotationTextColor(Iosapi::Foundation::_di_NSString annotationTextColor) = 0 ;
	virtual void __cdecl setAttributionBottomSpacing(double attributionBottomSpacing) = 0 ;
	virtual void __cdecl setAttributionFontFamily(Iosapi::Foundation::_di_NSString attributionFontFamily) = 0 ;
	virtual void __cdecl setAttributionFontSize(double attributionFontSize) = 0 ;
	virtual void __cdecl setAttributionTextColor(Iosapi::Foundation::_di_NSString attributionTextColor) = 0 ;
	virtual void __cdecl setBackgroundColor(Iosapi::Foundation::_di_NSString backgroundColor) = 0 ;
	virtual void __cdecl setBoldTitleEnabled(bool boldTitleEnabled) = 0 ;
	virtual void __cdecl setBorderColor(Iosapi::Foundation::_di_NSString borderColor) = 0 ;
	virtual void __cdecl setBorderCSSSelections(Iosapi::Foundation::_di_NSString borderCSSSelections) = 0 ;
	virtual void __cdecl setChannel(Iosapi::Foundation::_di_NSString channel) = 0 ;
	virtual void __cdecl setClickToCallExtensionEnabled(bool clickToCallExtensionEnabled) = 0 ;
	virtual void __cdecl setCSSWidth(Iosapi::Foundation::_di_NSString CSSWidth) = 0 ;
	virtual void __cdecl setDescriptionFontSize(double descriptionFontSize) = 0 ;
	virtual void __cdecl setDetailedAttributionExtensionEnabled(bool detailedAttributionExtensionEnabled) = 0 ;
	virtual void __cdecl setDomainLinkColor(Iosapi::Foundation::_di_NSString domainLinkColor) = 0 ;
	virtual void __cdecl setDomainLinkFontSize(double domainLinkFontSize) = 0 ;
	virtual void __cdecl setFontFamily(Iosapi::Foundation::_di_NSString fontFamily) = 0 ;
	virtual void __cdecl setHostLanguage(Iosapi::Foundation::_di_NSString hostLanguage) = 0 ;
	virtual void __cdecl setLocationExtensionEnabled(bool locationExtensionEnabled) = 0 ;
	virtual void __cdecl setLocationExtensionFontSize(double locationExtensionFontSize) = 0 ;
	virtual void __cdecl setLocationExtensionTextColor(Iosapi::Foundation::_di_NSString locationExtensionTextColor) = 0 ;
	virtual void __cdecl setLongerHeadlinesExtensionEnabled(bool longerHeadlinesExtensionEnabled) = 0 ;
	virtual void __cdecl setNumberOfAds(long numberOfAds) = 0 ;
	virtual void __cdecl setPlusOnesExtensionEnabled(bool plusOnesExtensionEnabled) = 0 ;
	virtual void __cdecl setQuery(Iosapi::Foundation::_di_NSString query) = 0 ;
	virtual void __cdecl setSellerRatingsExtensionEnabled(bool sellerRatingsExtensionEnabled) = 0 ;
	virtual void __cdecl setSiteLinksExtensionEnabled(bool siteLinksExtensionEnabled) = 0 ;
	virtual void __cdecl setTextColor(Iosapi::Foundation::_di_NSString textColor) = 0 ;
	virtual void __cdecl setTitleFontSize(double titleFontSize) = 0 ;
	virtual void __cdecl setTitleLinkColor(Iosapi::Foundation::_di_NSString titleLinkColor) = 0 ;
	virtual void __cdecl setTitleUnderlineHidden(bool titleUnderlineHidden) = 0 ;
	virtual void __cdecl setVerticalSpacing(double verticalSpacing) = 0 ;
	virtual bool __cdecl siteLinksExtensionEnabled() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl textColor() = 0 ;
	virtual double __cdecl titleFontSize() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl titleLinkColor() = 0 ;
	virtual bool __cdecl titleUnderlineHidden() = 0 ;
	virtual double __cdecl verticalSpacing() = 0 ;
};

class PASCALIMPLEMENTATION TGADDynamicHeightSearchRequest : public Macapi::Objectivec::TOCGenericImport__2<_di_GADDynamicHeightSearchRequestClass,_di_GADDynamicHeightSearchRequest>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADDynamicHeightSearchRequestClass,_di_GADDynamicHeightSearchRequest> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADDynamicHeightSearchRequest(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADDynamicHeightSearchRequestClass,_di_GADDynamicHeightSearchRequest>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADDynamicHeightSearchRequest() { }
	
};


__interface  INTERFACE_UUID("{1825824A-D34A-4522-837A-0EB47B02E80F}") GADExtrasClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{E5386B93-16FC-4CE5-B1A4-1D3D2BEE75AF}") GADExtras  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl additionalParameters() = 0 ;
	virtual void __cdecl setAdditionalParameters(Iosapi::Foundation::_di_NSDictionary additionalParameters) = 0 ;
};

class PASCALIMPLEMENTATION TGADExtras : public Macapi::Objectivec::TOCGenericImport__2<_di_GADExtrasClass,_di_GADExtras>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADExtrasClass,_di_GADExtras> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADExtras(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADExtrasClass,_di_GADExtras>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADExtras() { }
	
};


__interface  INTERFACE_UUID("{B27B2F69-B46A-4761-B79D-ADE643D9FF3C}") GADDefaultInAppPurchaseClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void __cdecl disableDefaultPurchaseFlow() = 0 ;
	virtual void __cdecl enableDefaultPurchaseFlowWithDelegate(void * delegate) = 0 ;
};

__interface  INTERFACE_UUID("{25A335AF-939C-421C-9555-BBFFC02F183E}") GADDefaultInAppPurchase  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl finishTransaction() = 0 ;
	virtual Iosapi::Storekit::_di_SKPaymentTransaction __cdecl paymentTransaction() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl productID() = 0 ;
	virtual long __cdecl quantity() = 0 ;
};

class PASCALIMPLEMENTATION TGADDefaultInAppPurchase : public Macapi::Objectivec::TOCGenericImport__2<_di_GADDefaultInAppPurchaseClass,_di_GADDefaultInAppPurchase>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADDefaultInAppPurchaseClass,_di_GADDefaultInAppPurchase> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADDefaultInAppPurchase(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADDefaultInAppPurchaseClass,_di_GADDefaultInAppPurchase>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADDefaultInAppPurchase() { }
	
};


__interface  INTERFACE_UUID("{59B4E6A7-71B7-46FE-B754-FDC76DF4D21C}") GADInAppPurchaseClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{582D1B91-021B-47B7-8152-11408A645DC6}") GADInAppPurchase  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl productID() = 0 ;
	virtual long __cdecl quantity() = 0 ;
	virtual void __cdecl reportPurchaseStatus(long purchaseStatus) = 0 ;
};

class PASCALIMPLEMENTATION TGADInAppPurchase : public Macapi::Objectivec::TOCGenericImport__2<_di_GADInAppPurchaseClass,_di_GADInAppPurchase>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADInAppPurchaseClass,_di_GADInAppPurchase> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADInAppPurchase(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADInAppPurchaseClass,_di_GADInAppPurchase>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADInAppPurchase() { }
	
};


__interface  INTERFACE_UUID("{8892078C-3A1E-405C-9F9C-1E89713C46E4}") GADMediaContentClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{C3640842-1BA8-44E7-AEEC-88009C08D679}") GADMediaContent  : public Iosapi::Foundation::NSObject 
{
	virtual double __cdecl aspectRatio() = 0 ;
	virtual double __cdecl currentTime() = 0 ;
	virtual double __cdecl duration() = 0 ;
	virtual bool __cdecl hasVideoContent() = 0 ;
	virtual Iosapi::Uikit::_di_UIImage __cdecl mainImage() = 0 ;
	virtual void __cdecl setMainImage(Iosapi::Uikit::_di_UIImage mainImage) = 0 ;
	virtual _di_GADVideoController __cdecl videoController() = 0 ;
};

class PASCALIMPLEMENTATION TGADMediaContent : public Macapi::Objectivec::TOCGenericImport__2<_di_GADMediaContentClass,_di_GADMediaContent>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADMediaContentClass,_di_GADMediaContent> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADMediaContent(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADMediaContentClass,_di_GADMediaContent>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADMediaContent() { }
	
};


__interface  INTERFACE_UUID("{3367BC2E-39B1-40EE-9393-B4A993D379A0}") GADInstreamAdClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void __cdecl loadAdWithAdTag(Iosapi::Foundation::_di_NSString adTag, GADInstreamAdLoadCompletionHandler completionHandler) = 0 ;
	virtual void __cdecl loadAdWithAdUnitID(Iosapi::Foundation::_di_NSString adUnitID, _di_GADRequest request, long mediaAspectRatio, GADInstreamAdLoadCompletionHandler completionHandler) = 0 ;
};

__interface  INTERFACE_UUID("{BEDACF81-0969-40EF-BAEC-80BEBCDE5ACC}") GADInstreamAd  : public Iosapi::Foundation::NSObject 
{
	virtual _di_GADMediaContent __cdecl mediaContent() = 0 ;
	virtual GADPaidEventHandler __cdecl paidEventHandler() = 0 ;
	virtual _di_GADResponseInfo __cdecl responseInfo() = 0 ;
	virtual void __cdecl setPaidEventHandler(GADPaidEventHandler paidEventHandler) = 0 ;
};

class PASCALIMPLEMENTATION TGADInstreamAd : public Macapi::Objectivec::TOCGenericImport__2<_di_GADInstreamAdClass,_di_GADInstreamAd>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADInstreamAdClass,_di_GADInstreamAd> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADInstreamAd(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADInstreamAdClass,_di_GADInstreamAd>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADInstreamAd() { }
	
};


__interface  INTERFACE_UUID("{A5F94520-64D4-46FE-93AB-660910F00387}") GADInstreamAdViewClass  : public Iosapi::Uikit::UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{D44646D9-EEBD-4EE9-A543-391A2D3DCFE7}") GADInstreamAdView  : public Iosapi::Uikit::UIView 
{
	virtual _di_GADInstreamAd __cdecl ad() = 0 ;
	virtual void __cdecl setAd(_di_GADInstreamAd ad) = 0 ;
};

class PASCALIMPLEMENTATION TGADInstreamAdView : public Macapi::Objectivec::TOCGenericImport__2<_di_GADInstreamAdViewClass,_di_GADInstreamAdView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADInstreamAdViewClass,_di_GADInstreamAdView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADInstreamAdView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADInstreamAdViewClass,_di_GADInstreamAdView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADInstreamAdView() { }
	
};


__interface  INTERFACE_UUID("{BEB95E06-03F7-46A7-91AF-6789E026D3BC}") GADMediaViewClass  : public Iosapi::Uikit::UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{F6DD72AB-720C-4245-9E73-AF9CC55A1347}") GADMediaView  : public Iosapi::Uikit::UIView 
{
	virtual _di_GADMediaContent __cdecl mediaContent() = 0 ;
	virtual void __cdecl setMediaContent(_di_GADMediaContent mediaContent) = 0 ;
};

class PASCALIMPLEMENTATION TGADMediaView : public Macapi::Objectivec::TOCGenericImport__2<_di_GADMediaViewClass,_di_GADMediaView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADMediaViewClass,_di_GADMediaView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADMediaView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADMediaViewClass,_di_GADMediaView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADMediaView() { }
	
};


__interface  INTERFACE_UUID("{3C7B5B82-4FE9-4AA5-8FD7-24E759AF12A9}") GADMultipleAdsAdLoaderOptionsClass  : public GADAdLoaderOptionsClass 
{
	
};

__interface  INTERFACE_UUID("{319EF936-4F4D-4800-A4AB-B2639CFB15CF}") GADMultipleAdsAdLoaderOptions  : public GADAdLoaderOptions 
{
	virtual long __cdecl numberOfAds() = 0 ;
	virtual void __cdecl setNumberOfAds(long numberOfAds) = 0 ;
};

class PASCALIMPLEMENTATION TGADMultipleAdsAdLoaderOptions : public Macapi::Objectivec::TOCGenericImport__2<_di_GADMultipleAdsAdLoaderOptionsClass,_di_GADMultipleAdsAdLoaderOptions>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADMultipleAdsAdLoaderOptionsClass,_di_GADMultipleAdsAdLoaderOptions> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADMultipleAdsAdLoaderOptions(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADMultipleAdsAdLoaderOptionsClass,_di_GADMultipleAdsAdLoaderOptions>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADMultipleAdsAdLoaderOptions() { }
	
};


__interface  INTERFACE_UUID("{CF3D21FD-F113-4EFD-8E03-F4F1DF59007F}") GADMuteThisAdReasonClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{DFF9763C-0E94-4269-9212-33C9352CC72F}") GADMuteThisAdReason  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl reasonDescription() = 0 ;
};

class PASCALIMPLEMENTATION TGADMuteThisAdReason : public Macapi::Objectivec::TOCGenericImport__2<_di_GADMuteThisAdReasonClass,_di_GADMuteThisAdReason>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADMuteThisAdReasonClass,_di_GADMuteThisAdReason> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADMuteThisAdReason(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADMuteThisAdReasonClass,_di_GADMuteThisAdReason>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADMuteThisAdReason() { }
	
};


__interface  INTERFACE_UUID("{A82DE2CB-533F-497F-9B85-F7E8FF5EC5AD}") GADNativeAdClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{5CEBA8DC-370A-4E51-BD7B-F1CBC675131A}") GADNativeAd  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl adNetworkClassName() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl extraAssets() = 0 ;
	virtual Iosapi::Uikit::_di_UIViewController __cdecl rootViewController() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setRootViewController(Iosapi::Uikit::_di_UIViewController rootViewController) = 0 ;
};

class PASCALIMPLEMENTATION TGADNativeAd : public Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeAdClass,_di_GADNativeAd>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeAdClass,_di_GADNativeAd> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADNativeAd(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeAdClass,_di_GADNativeAd>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADNativeAd() { }
	
};


__interface  INTERFACE_UUID("{5FF3D639-BB56-496B-AB07-8D4EA46545AC}") GADNativeAdDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl nativeAdDidDismissScreen(_di_GADNativeAd nativeAd) = 0 ;
	virtual void __cdecl nativeAdDidRecordClick(_di_GADNativeAd nativeAd) = 0 ;
	virtual void __cdecl nativeAdDidRecordImpression(_di_GADNativeAd nativeAd) = 0 ;
	virtual void __cdecl nativeAdWillDismissScreen(_di_GADNativeAd nativeAd) = 0 ;
	virtual void __cdecl nativeAdWillLeaveApplication(_di_GADNativeAd nativeAd) = 0 ;
	virtual void __cdecl nativeAdWillPresentScreen(_di_GADNativeAd nativeAd) = 0 ;
};

__interface  INTERFACE_UUID("{AD3DBE85-B81C-49F6-849E-9CF567BE90D8}") GADNativeAdImageAdLoaderOptionsClass  : public GADAdLoaderOptionsClass 
{
	
};

__interface  INTERFACE_UUID("{4F537345-D0E7-4A31-9D3D-109B04DF0709}") GADNativeAdImageAdLoaderOptions  : public GADAdLoaderOptions 
{
	virtual bool __cdecl disableImageLoading() = 0 ;
	virtual long __cdecl preferredImageOrientation() = 0 ;
	virtual void __cdecl setDisableImageLoading(bool disableImageLoading) = 0 ;
	virtual void __cdecl setPreferredImageOrientation(long preferredImageOrientation) = 0 ;
	virtual void __cdecl setShouldRequestMultipleImages(bool shouldRequestMultipleImages) = 0 ;
	virtual bool __cdecl shouldRequestMultipleImages() = 0 ;
};

class PASCALIMPLEMENTATION TGADNativeAdImageAdLoaderOptions : public Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeAdImageAdLoaderOptionsClass,_di_GADNativeAdImageAdLoaderOptions>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeAdImageAdLoaderOptionsClass,_di_GADNativeAdImageAdLoaderOptions> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADNativeAdImageAdLoaderOptions(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeAdImageAdLoaderOptionsClass,_di_GADNativeAdImageAdLoaderOptions>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADNativeAdImageAdLoaderOptions() { }
	
};


__interface  INTERFACE_UUID("{64F27F96-2E3B-4055-B8EB-07CE0C233FC6}") GADNativeAdMediaAdLoaderOptionsClass  : public GADAdLoaderOptionsClass 
{
	
};

__interface  INTERFACE_UUID("{C14BA0E1-ABD8-4DBE-8976-5023B67BC408}") GADNativeAdMediaAdLoaderOptions  : public GADAdLoaderOptions 
{
	virtual long __cdecl mediaAspectRatio() = 0 ;
	virtual void __cdecl setMediaAspectRatio(long mediaAspectRatio) = 0 ;
};

class PASCALIMPLEMENTATION TGADNativeAdMediaAdLoaderOptions : public Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeAdMediaAdLoaderOptionsClass,_di_GADNativeAdMediaAdLoaderOptions>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeAdMediaAdLoaderOptionsClass,_di_GADNativeAdMediaAdLoaderOptions> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADNativeAdMediaAdLoaderOptions(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeAdMediaAdLoaderOptionsClass,_di_GADNativeAdMediaAdLoaderOptions>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADNativeAdMediaAdLoaderOptions() { }
	
};


__interface  INTERFACE_UUID("{CD757401-4CED-4A16-BF8D-26C40BC5AC95}") GADNativeAdViewAdOptionsClass  : public GADAdLoaderOptionsClass 
{
	
};

__interface  INTERFACE_UUID("{8AFB9591-854A-45B4-8BEA-EE7DAD7E2D06}") GADNativeAdViewAdOptions  : public GADAdLoaderOptions 
{
	virtual long __cdecl preferredAdChoicesPosition() = 0 ;
	virtual void __cdecl setPreferredAdChoicesPosition(long preferredAdChoicesPosition) = 0 ;
};

class PASCALIMPLEMENTATION TGADNativeAdViewAdOptions : public Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeAdViewAdOptionsClass,_di_GADNativeAdViewAdOptions>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeAdViewAdOptionsClass,_di_GADNativeAdViewAdOptions> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADNativeAdViewAdOptions(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeAdViewAdOptionsClass,_di_GADNativeAdViewAdOptions>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADNativeAdViewAdOptions() { }
	
};


__interface  INTERFACE_UUID("{F80C57D5-1733-4C8D-A684-F88EA7DA3D78}") GADNativeCustomTemplateAdClass  : public GADNativeAdClass 
{
	
};

__interface  INTERFACE_UUID("{00C93915-BD80-42CE-A0D7-20B8E7FF40E9}") GADNativeCustomTemplateAd  : public GADNativeAd 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl availableAssetKeys() = 0 ;
	virtual GADNativeAdCustomClickHandler __cdecl customClickHandler() = 0 ;
	virtual _di_GADDisplayAdMeasurement __cdecl displayAdMeasurement() = 0 ;
	virtual _di_GADNativeAdImage __cdecl imageForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual _di_GADMediaView __cdecl mediaView() = 0 ;
	virtual void __cdecl performClickOnAssetWithKey(Iosapi::Foundation::_di_NSString assetKey, void * customClickHandler) = 0 /* overload */;
	virtual void __cdecl performClickOnAssetWithKey(Iosapi::Foundation::_di_NSString assetKey) = 0 /* overload */;
	virtual void __cdecl recordImpression() = 0 ;
	virtual void __cdecl setCustomClickHandler(GADNativeAdCustomClickHandler customClickHandler) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl stringForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl templateID() = 0 ;
	virtual _di_GADVideoController __cdecl videoController() = 0 ;
};

class PASCALIMPLEMENTATION TGADNativeCustomTemplateAd : public Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeCustomTemplateAdClass,_di_GADNativeCustomTemplateAd>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeCustomTemplateAdClass,_di_GADNativeCustomTemplateAd> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADNativeCustomTemplateAd(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeCustomTemplateAdClass,_di_GADNativeCustomTemplateAd>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADNativeCustomTemplateAd() { }
	
};


__interface  INTERFACE_UUID("{2D22D736-3A8A-4233-B044-BEAA512C8BA7}") GADNativeCustomTemplateAdLoaderDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl adLoader(_di_GADAdLoader adLoader, _di_GADNativeCustomTemplateAd nativeCustomTemplateAd) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl nativeCustomTemplateIDsForAdLoader(_di_GADAdLoader adLoader) = 0 ;
};

__interface  INTERFACE_UUID("{C30B6E89-0E71-444B-9E86-EACAC8AEDE4F}") GADNativeExpressAdViewDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl nativeExpressAdView(_di_GADNativeExpressAdView nativeExpressAdView, _di_GADRequestError error) = 0 ;
	virtual void __cdecl nativeExpressAdViewDidDismissScreen(_di_GADNativeExpressAdView nativeExpressAdView) = 0 ;
	virtual void __cdecl nativeExpressAdViewDidReceiveAd(_di_GADNativeExpressAdView nativeExpressAdView) = 0 ;
	virtual void __cdecl nativeExpressAdViewWillDismissScreen(_di_GADNativeExpressAdView nativeExpressAdView) = 0 ;
	virtual void __cdecl nativeExpressAdViewWillLeaveApplication(_di_GADNativeExpressAdView nativeExpressAdView) = 0 ;
	virtual void __cdecl nativeExpressAdViewWillPresentScreen(_di_GADNativeExpressAdView nativeExpressAdView) = 0 ;
};

__interface  INTERFACE_UUID("{88C19579-4C57-4ED0-9B89-BDFCC0539613}") GADNativeExpressAdViewClass  : public Iosapi::Uikit::UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{B4B7027C-7909-4D3C-93FD-266323A447D4}") GADNativeExpressAdView  : public Iosapi::Uikit::UIView 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl adNetworkClassName() = 0 ;
	virtual GADAdSize __cdecl adSize() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl adUnitID() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void * __cdecl initWithAdSize(GADAdSize adSize, Iosapi::Foundation::NSPoint origin) = 0 /* overload */;
	virtual void * __cdecl initWithAdSize(GADAdSize adSize) = 0 /* overload */;
	virtual bool __cdecl isAutoloadEnabled() = 0 ;
	virtual void __cdecl loadRequest(_di_GADRequest request) = 0 ;
	virtual Iosapi::Uikit::_di_UIViewController __cdecl rootViewController() = 0 ;
	virtual void __cdecl setAdOptions(Iosapi::Foundation::_di_NSArray adOptions) = 0 ;
	virtual void __cdecl setAdSize(GADAdSize adSize) = 0 ;
	virtual void __cdecl setAdUnitID(Iosapi::Foundation::_di_NSString adUnitID) = 0 ;
	virtual void __cdecl setAutoloadEnabled(bool autoloadEnabled) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setRootViewController(Iosapi::Uikit::_di_UIViewController rootViewController) = 0 ;
	virtual _di_GADVideoController __cdecl videoController() = 0 ;
};

class PASCALIMPLEMENTATION TGADNativeExpressAdView : public Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeExpressAdViewClass,_di_GADNativeExpressAdView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeExpressAdViewClass,_di_GADNativeExpressAdView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADNativeExpressAdView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeExpressAdViewClass,_di_GADNativeExpressAdView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADNativeExpressAdView() { }
	
};


__interface  INTERFACE_UUID("{47315F4E-066A-4509-92FE-234E9F1A661A}") GADNativeMuteThisAdLoaderOptionsClass  : public GADAdLoaderOptionsClass 
{
	
};

__interface  INTERFACE_UUID("{14990AD2-CCC2-4FBA-ADE1-7CE6D3516E13}") GADNativeMuteThisAdLoaderOptions  : public GADAdLoaderOptions 
{
	virtual bool __cdecl customMuteThisAdRequested() = 0 ;
	virtual void __cdecl setCustomMuteThisAdRequested(bool customMuteThisAdRequested) = 0 ;
};

class PASCALIMPLEMENTATION TGADNativeMuteThisAdLoaderOptions : public Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeMuteThisAdLoaderOptionsClass,_di_GADNativeMuteThisAdLoaderOptions>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeMuteThisAdLoaderOptionsClass,_di_GADNativeMuteThisAdLoaderOptions> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADNativeMuteThisAdLoaderOptions(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADNativeMuteThisAdLoaderOptionsClass,_di_GADNativeMuteThisAdLoaderOptions>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADNativeMuteThisAdLoaderOptions() { }
	
};


__interface  INTERFACE_UUID("{CE064833-DDE7-425C-858F-A5EBE9251210}") GADRewardBasedVideoAdDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl rewardBasedVideoAd(_di_GADRewardBasedVideoAd rewardBasedVideoAd, Iosapi::Foundation::_di_NSError error) = 0 /* overload */;
	virtual void __cdecl rewardBasedVideoAd(_di_GADRewardBasedVideoAd rewardBasedVideoAd, _di_GADAdReward reward) = 0 /* overload */;
	virtual void __cdecl rewardBasedVideoAdDidClose(_di_GADRewardBasedVideoAd rewardBasedVideoAd) = 0 ;
	virtual void __cdecl rewardBasedVideoAdDidCompletePlaying(_di_GADRewardBasedVideoAd rewardBasedVideoAd) = 0 ;
	virtual void __cdecl rewardBasedVideoAdDidOpen(_di_GADRewardBasedVideoAd rewardBasedVideoAd) = 0 ;
	virtual void __cdecl rewardBasedVideoAdDidReceiveAd(_di_GADRewardBasedVideoAd rewardBasedVideoAd) = 0 ;
	virtual void __cdecl rewardBasedVideoAdDidStartPlaying(_di_GADRewardBasedVideoAd rewardBasedVideoAd) = 0 ;
	virtual void __cdecl rewardBasedVideoAdMetadataDidChange(_di_GADRewardBasedVideoAd rewardBasedVideoAd) = 0 ;
	virtual void __cdecl rewardBasedVideoAdWillLeaveApplication(_di_GADRewardBasedVideoAd rewardBasedVideoAd) = 0 ;
};

__interface  INTERFACE_UUID("{76BCFD29-71C2-4FED-B1A8-C191774F3FE3}") GADRewardBasedVideoAdClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_GADRewardBasedVideoAd __cdecl sharedInstance() = 0 ;
};

__interface  INTERFACE_UUID("{ADE673C2-CA70-494A-8C7F-C041CA9AB1BD}") GADRewardBasedVideoAd  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl adMetadata() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl adNetworkClassName() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl customRewardString() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual bool __cdecl isReady() = 0 ;
	virtual void __cdecl loadRequest(_di_GADRequest request, Iosapi::Foundation::_di_NSString adUnitID) = 0 ;
	virtual void __cdecl presentFromRootViewController(Iosapi::Uikit::_di_UIViewController viewController) = 0 ;
	virtual void __cdecl setCustomRewardString(Iosapi::Foundation::_di_NSString customRewardString) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setUserIdentifier(Iosapi::Foundation::_di_NSString userIdentifier) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl userIdentifier() = 0 ;
};

class PASCALIMPLEMENTATION TGADRewardBasedVideoAd : public Macapi::Objectivec::TOCGenericImport__2<_di_GADRewardBasedVideoAdClass,_di_GADRewardBasedVideoAd>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADRewardBasedVideoAdClass,_di_GADRewardBasedVideoAd> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADRewardBasedVideoAd(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADRewardBasedVideoAdClass,_di_GADRewardBasedVideoAd>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADRewardBasedVideoAd() { }
	
};


__interface  INTERFACE_UUID("{8D866C8F-2F37-4F3C-8673-E608360F7776}") GADRewardedAdDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl rewardedAd(_di_GADRewardedAd rewardedAd, Iosapi::Foundation::_di_NSError error) = 0 /* overload */;
	virtual void __cdecl rewardedAd(_di_GADRewardedAd rewardedAd, _di_GADAdReward reward) = 0 /* overload */;
	virtual void __cdecl rewardedAdDidDismiss(_di_GADRewardedAd rewardedAd) = 0 ;
	virtual void __cdecl rewardedAdDidPresent(_di_GADRewardedAd rewardedAd) = 0 ;
};

__interface  INTERFACE_UUID("{8CB1D739-7C5C-4D38-883B-87EF144B8C43}") GADRewardedAdMetadataDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl rewardedAdMetadataDidChange(_di_GADRewardedAd rewardedAd) = 0 ;
};

__interface  INTERFACE_UUID("{733A9EFD-60E0-46FE-AD98-FD11B9BCB29B}") GADServerSideVerificationOptionsClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{CE7CA8C0-6A75-417B-9553-B8703D0AC6AC}") GADServerSideVerificationOptions  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl customRewardString() = 0 ;
	virtual void __cdecl setCustomRewardString(Iosapi::Foundation::_di_NSString customRewardString) = 0 ;
	virtual void __cdecl setUserIdentifier(Iosapi::Foundation::_di_NSString userIdentifier) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl userIdentifier() = 0 ;
};

class PASCALIMPLEMENTATION TGADServerSideVerificationOptions : public Macapi::Objectivec::TOCGenericImport__2<_di_GADServerSideVerificationOptionsClass,_di_GADServerSideVerificationOptions>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADServerSideVerificationOptionsClass,_di_GADServerSideVerificationOptions> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADServerSideVerificationOptions(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADServerSideVerificationOptionsClass,_di_GADServerSideVerificationOptions>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADServerSideVerificationOptions() { }
	
};


__interface  INTERFACE_UUID("{480CA3EA-9080-47AB-A943-DA5E794EAA88}") GADRewardedAdClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{715FA694-1A34-42BC-85D5-4FC28D7EFA79}") GADRewardedAd  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl adMetadata() = 0 ;
	virtual void * __cdecl adMetadataDelegate() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl adNetworkClassName() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl adUnitID() = 0 ;
	virtual bool __cdecl canPresentFromRootViewController(Iosapi::Uikit::_di_UIViewController rootViewController, Iosapi::Foundation::PNSError error) = 0 ;
	virtual void * __cdecl initWithAdUnitID(Iosapi::Foundation::_di_NSString adUnitID) = 0 ;
	virtual bool __cdecl isReady() = 0 ;
	virtual void __cdecl loadRequest(_di_GADRequest request, GADRewardedAdLoadCompletionHandler completionHandler) = 0 ;
	virtual GADPaidEventHandler __cdecl paidEventHandler() = 0 ;
	virtual void __cdecl presentFromRootViewController(Iosapi::Uikit::_di_UIViewController viewController, void * delegate) = 0 ;
	virtual _di_GADResponseInfo __cdecl responseInfo() = 0 ;
	virtual _di_GADAdReward __cdecl reward() = 0 ;
	virtual _di_GADServerSideVerificationOptions __cdecl serverSideVerificationOptions() = 0 ;
	virtual void __cdecl setAdMetadataDelegate(void * adMetadataDelegate) = 0 ;
	virtual void __cdecl setPaidEventHandler(GADPaidEventHandler paidEventHandler) = 0 ;
	virtual void __cdecl setServerSideVerificationOptions(_di_GADServerSideVerificationOptions serverSideVerificationOptions) = 0 ;
};

class PASCALIMPLEMENTATION TGADRewardedAd : public Macapi::Objectivec::TOCGenericImport__2<_di_GADRewardedAdClass,_di_GADRewardedAd>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADRewardedAdClass,_di_GADRewardedAd> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADRewardedAd(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADRewardedAdClass,_di_GADRewardedAd>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADRewardedAd() { }
	
};


__interface  INTERFACE_UUID("{9134D93B-3CC1-4AC7-8D6E-05BDF6949A8D}") GADSearchBannerViewClass  : public GADBannerViewClass 
{
	
};

__interface  INTERFACE_UUID("{AB3C5E96-4396-4018-8FB1-7542AA3680AA}") GADSearchBannerView  : public GADBannerView 
{
	HIDESBASE virtual void * __cdecl adSizeDelegate() = 0 ;
	HIDESBASE virtual void __cdecl setAdSizeDelegate(void * adSizeDelegate) = 0 ;
};

class PASCALIMPLEMENTATION TGADSearchBannerView : public Macapi::Objectivec::TOCGenericImport__2<_di_GADSearchBannerViewClass,_di_GADSearchBannerView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADSearchBannerViewClass,_di_GADSearchBannerView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADSearchBannerView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADSearchBannerViewClass,_di_GADSearchBannerView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADSearchBannerView() { }
	
};


__interface  INTERFACE_UUID("{95C1E044-0CDB-4C28-A04D-A25C1B510E17}") GADUnifiedNativeAdDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl nativeAdDidDismissScreen(_di_GADUnifiedNativeAd nativeAd) = 0 ;
	virtual void __cdecl nativeAdDidRecordClick(_di_GADUnifiedNativeAd nativeAd) = 0 ;
	virtual void __cdecl nativeAdDidRecordImpression(_di_GADUnifiedNativeAd nativeAd) = 0 ;
	virtual void __cdecl nativeAdIsMuted(_di_GADUnifiedNativeAd nativeAd) = 0 ;
	virtual void __cdecl nativeAdWillDismissScreen(_di_GADUnifiedNativeAd nativeAd) = 0 ;
	virtual void __cdecl nativeAdWillLeaveApplication(_di_GADUnifiedNativeAd nativeAd) = 0 ;
	virtual void __cdecl nativeAdWillPresentScreen(_di_GADUnifiedNativeAd nativeAd) = 0 ;
};

__interface  INTERFACE_UUID("{E3386CCF-33BE-48CF-AA46-5EC6AA8B8E35}") GADUnifiedNativeAdClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{5B66244F-F8FF-4650-A583-7B3AB4848DC1}") GADUnifiedNativeAd  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl adNetworkClassName() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl advertiser() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl body() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl callToAction() = 0 ;
	virtual void __cdecl cancelUnconfirmedClick() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl enableCustomClickGestures() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl extraAssets() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl headline() = 0 ;
	virtual _di_GADNativeAdImage __cdecl icon() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl images() = 0 ;
	virtual bool __cdecl isCustomClickGestureEnabled() = 0 ;
	virtual bool __cdecl isCustomMuteThisAdAvailable() = 0 ;
	virtual _di_GADMediaContent __cdecl mediaContent() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl muteThisAdReasons() = 0 ;
	virtual void __cdecl muteThisAdWithReason(_di_GADMuteThisAdReason reason) = 0 ;
	virtual GADPaidEventHandler __cdecl paidEventHandler() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl price() = 0 ;
	virtual void __cdecl recordCustomClickGesture() = 0 ;
	virtual void __cdecl registerAdView(Iosapi::Uikit::_di_UIView adView, Iosapi::Foundation::_di_NSDictionary clickableAssetViews, Iosapi::Foundation::_di_NSDictionary nonclickableAssetViews) = 0 ;
	virtual void __cdecl registerClickConfirmingView(Iosapi::Uikit::_di_UIView view) = 0 ;
	virtual _di_GADResponseInfo __cdecl responseInfo() = 0 ;
	virtual Iosapi::Uikit::_di_UIViewController __cdecl rootViewController() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setPaidEventHandler(GADPaidEventHandler paidEventHandler) = 0 ;
	virtual void __cdecl setRootViewController(Iosapi::Uikit::_di_UIViewController rootViewController) = 0 ;
	virtual void __cdecl setUnconfirmedClickDelegate(void * unconfirmedClickDelegate) = 0 ;
	virtual Iosapi::Foundation::_di_NSDecimalNumber __cdecl starRating() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl store() = 0 ;
	virtual void * __cdecl unconfirmedClickDelegate() = 0 ;
	virtual void __cdecl unregisterAdView() = 0 ;
	virtual _di_GADVideoController __cdecl videoController() = 0 ;
};

class PASCALIMPLEMENTATION TGADUnifiedNativeAd : public Macapi::Objectivec::TOCGenericImport__2<_di_GADUnifiedNativeAdClass,_di_GADUnifiedNativeAd>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADUnifiedNativeAdClass,_di_GADUnifiedNativeAd> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADUnifiedNativeAd(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADUnifiedNativeAdClass,_di_GADUnifiedNativeAd>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADUnifiedNativeAd() { }
	
};


__interface  INTERFACE_UUID("{B1A1DD05-93CE-49D8-A823-45DC7AD939D4}") GADUnifiedNativeAdLoaderDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl adLoader(_di_GADAdLoader adLoader, _di_GADUnifiedNativeAd nativeAd) = 0 ;
};

__interface  INTERFACE_UUID("{4D94DF61-9CB9-431D-9571-8AC69BD520C6}") GADUnifiedNativeAdViewClass  : public Iosapi::Uikit::UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{EAA78041-17FC-43F8-ACF3-30CF4ED54B24}") GADUnifiedNativeAdView  : public Iosapi::Uikit::UIView 
{
	virtual _di_GADAdChoicesView __cdecl adChoicesView() = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl advertiserView() = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl bodyView() = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl callToActionView() = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl headlineView() = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl iconView() = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl imageView() = 0 ;
	virtual _di_GADMediaView __cdecl mediaView() = 0 ;
	virtual _di_GADUnifiedNativeAd __cdecl nativeAd() = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl priceView() = 0 ;
	virtual void __cdecl setAdChoicesView(_di_GADAdChoicesView adChoicesView) = 0 ;
	virtual void __cdecl setAdvertiserView(Iosapi::Uikit::_di_UIView advertiserView) = 0 ;
	virtual void __cdecl setBodyView(Iosapi::Uikit::_di_UIView bodyView) = 0 ;
	virtual void __cdecl setCallToActionView(Iosapi::Uikit::_di_UIView callToActionView) = 0 ;
	virtual void __cdecl setHeadlineView(Iosapi::Uikit::_di_UIView headlineView) = 0 ;
	virtual void __cdecl setIconView(Iosapi::Uikit::_di_UIView iconView) = 0 ;
	virtual void __cdecl setImageView(Iosapi::Uikit::_di_UIView imageView) = 0 ;
	virtual void __cdecl setMediaView(_di_GADMediaView mediaView) = 0 ;
	virtual void __cdecl setNativeAd(_di_GADUnifiedNativeAd nativeAd) = 0 ;
	virtual void __cdecl setPriceView(Iosapi::Uikit::_di_UIView priceView) = 0 ;
	virtual void __cdecl setStarRatingView(Iosapi::Uikit::_di_UIView starRatingView) = 0 ;
	virtual void __cdecl setStoreView(Iosapi::Uikit::_di_UIView storeView) = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl starRatingView() = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl storeView() = 0 ;
};

class PASCALIMPLEMENTATION TGADUnifiedNativeAdView : public Macapi::Objectivec::TOCGenericImport__2<_di_GADUnifiedNativeAdViewClass,_di_GADUnifiedNativeAdView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADUnifiedNativeAdViewClass,_di_GADUnifiedNativeAdView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADUnifiedNativeAdView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADUnifiedNativeAdViewClass,_di_GADUnifiedNativeAdView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADUnifiedNativeAdView() { }
	
};


__interface  INTERFACE_UUID("{53E706AF-B573-47B9-85D9-06A8339ABA04}") GADUnifiedNativeAdUnconfirmedClickDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl nativeAd(_di_GADUnifiedNativeAd nativeAd, Iosapi::Foundation::_di_NSString assetID) = 0 ;
	virtual void __cdecl nativeAdDidCancelUnconfirmedClick(_di_GADUnifiedNativeAd nativeAd) = 0 ;
};

__interface  INTERFACE_UUID("{89DBDBC5-05AB-4237-84CF-D6760882FB2D}") GADVideoControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl videoControllerDidEndVideoPlayback(_di_GADVideoController videoController) = 0 ;
	virtual void __cdecl videoControllerDidMuteVideo(_di_GADVideoController videoController) = 0 ;
	virtual void __cdecl videoControllerDidPauseVideo(_di_GADVideoController videoController) = 0 ;
	virtual void __cdecl videoControllerDidPlayVideo(_di_GADVideoController videoController) = 0 ;
	virtual void __cdecl videoControllerDidUnmuteVideo(_di_GADVideoController videoController) = 0 ;
};

__interface  INTERFACE_UUID("{51CA7981-DD16-4522-80FB-2A94D3626DD1}") GADVideoOptionsClass  : public GADAdLoaderOptionsClass 
{
	
};

__interface  INTERFACE_UUID("{0605D4DE-BB08-4C37-BB1F-3F697AD42615}") GADVideoOptions  : public GADAdLoaderOptions 
{
	virtual bool __cdecl clickToExpandRequested() = 0 ;
	virtual bool __cdecl customControlsRequested() = 0 ;
	virtual void __cdecl setClickToExpandRequested(bool clickToExpandRequested) = 0 ;
	virtual void __cdecl setCustomControlsRequested(bool customControlsRequested) = 0 ;
	virtual void __cdecl setStartMuted(bool startMuted) = 0 ;
	virtual bool __cdecl startMuted() = 0 ;
};

class PASCALIMPLEMENTATION TGADVideoOptions : public Macapi::Objectivec::TOCGenericImport__2<_di_GADVideoOptionsClass,_di_GADVideoOptions>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADVideoOptionsClass,_di_GADVideoOptions> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADVideoOptions(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADVideoOptionsClass,_di_GADVideoOptions>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADVideoOptions() { }
	
};


__interface  INTERFACE_UUID("{7F2343DB-46D3-4C44-BC6F-5F72C1C9A052}") GADMediationAdRequest  : public Macapi::Objectivec::IObjectiveC 
{
	virtual Iosapi::Foundation::_di_NSNumber __cdecl childDirectedTreatment() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl credentials() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl maxAdContentRating() = 0 ;
	virtual void * __cdecl networkExtras() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl publisherId() = 0 ;
	virtual bool __cdecl testMode() = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl underAgeOfConsent() = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl userBirthday() = 0 ;
	virtual long __cdecl userGender() = 0 ;
	virtual bool __cdecl userHasLocation() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl userKeywords() = 0 ;
	virtual double __cdecl userLatitude() = 0 ;
	virtual double __cdecl userLocationAccuracyInMeters() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl userLocationDescription() = 0 ;
	virtual double __cdecl userLongitude() = 0 ;
};

__interface  INTERFACE_UUID("{0360B375-E36F-41FF-A8F8-C253D4090DBD}") GADMAdNetworkConnector  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl adapterClickDidOccurInBanner(void * adapter, Iosapi::Uikit::_di_UIView view) = 0 ;
	virtual void __cdecl adapterDidDismissFullScreenModal(void * adapter) = 0 ;
	virtual void __cdecl adapterDidDismissInterstitial(void * adapter) = 0 ;
	virtual void __cdecl adapterDidFailAd(void * adapter, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl adapterDidFailInterstitial(void * adapter, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl adapterDidGetAdClick(void * adapter) = 0 ;
	virtual void __cdecl adapterDidReceiveAdView(void * adapter, Iosapi::Uikit::_di_UIView view) = 0 ;
	virtual void __cdecl adapterDidReceiveInterstitial(void * adapter, Iosapi::Foundation::_di_NSObject interstitial) = 0 /* overload */;
	virtual void __cdecl adapterDidReceiveInterstitial(void * adapter) = 0 /* overload */;
	virtual void __cdecl adapterDidReceiveMediatedUnifiedNativeAd(void * adapter, void * mediatedUnifiedNativeAd) = 0 ;
	virtual void __cdecl adapterWillDismissFullScreenModal(void * adapter) = 0 ;
	virtual void __cdecl adapterWillDismissInterstitial(void * adapter) = 0 ;
	virtual void __cdecl adapterWillLeaveApplication(void * adapter) = 0 ;
	virtual void __cdecl adapterWillPresentFullScreenModal(void * adapter) = 0 ;
	virtual void __cdecl adapterWillPresentInterstitial(void * adapter) = 0 ;
	virtual bool __cdecl adMuted() = 0 ;
	virtual float __cdecl adVolume() = 0 ;
	virtual Iosapi::Uikit::_di_UIViewController __cdecl viewControllerForPresentingModalView() = 0 ;
};

__interface  INTERFACE_UUID("{7BC458BE-3686-448E-9E43-5DC7174AF994}") GADMAdNetworkAdapter  : public Macapi::Objectivec::IObjectiveC 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl adapterVersion() = 0 ;
	virtual void __cdecl changeAdSizeTo(GADAdSize adSize) = 0 ;
	virtual void __cdecl getBannerWithSize(GADAdSize adSize) = 0 ;
	virtual void __cdecl getInterstitial() = 0 ;
	virtual void __cdecl getNativeAdWithAdTypes(Iosapi::Foundation::_di_NSArray adTypes, Iosapi::Foundation::_di_NSArray options) = 0 ;
	virtual bool __cdecl handlesUserClicks() = 0 ;
	virtual bool __cdecl handlesUserImpressions() = 0 ;
	virtual void * __cdecl initWithGADMAdNetworkConnector(void * connector) = 0 ;
	virtual void * __cdecl networkExtrasClass() = 0 ;
	virtual void __cdecl presentInterstitialFromRootViewController(Iosapi::Uikit::_di_UIViewController rootViewController) = 0 ;
	virtual void __cdecl stopBeingDelegate() = 0 ;
};

__interface  INTERFACE_UUID("{7440AE80-8F38-44C3-8A42-FD431837AE97}") GADMediatedUnifiedNativeAdNotificationSourceClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void __cdecl mediatedNativeAdDidDismissScreen(void * mediatedNativeAd) = 0 ;
	virtual void __cdecl mediatedNativeAdDidEndVideoPlayback(void * mediatedNativeAd) = 0 ;
	virtual void __cdecl mediatedNativeAdDidPauseVideo(void * mediatedNativeAd) = 0 ;
	virtual void __cdecl mediatedNativeAdDidPlayVideo(void * mediatedNativeAd) = 0 ;
	virtual void __cdecl mediatedNativeAdDidRecordClick(void * mediatedNativeAd) = 0 ;
	virtual void __cdecl mediatedNativeAdDidRecordImpression(void * mediatedNativeAd) = 0 ;
	virtual void __cdecl mediatedNativeAdWillDismissScreen(void * mediatedNativeAd) = 0 ;
	virtual void __cdecl mediatedNativeAdWillLeaveApplication(void * mediatedNativeAd) = 0 ;
	virtual void __cdecl mediatedNativeAdWillPresentScreen(void * mediatedNativeAd) = 0 ;
};

__interface  INTERFACE_UUID("{93187CEA-30CD-4B0B-8F18-0810922F0266}") GADMediatedUnifiedNativeAdNotificationSource  : public Iosapi::Foundation::NSObject 
{
	
};

class PASCALIMPLEMENTATION TGADMediatedUnifiedNativeAdNotificationSource : public Macapi::Objectivec::TOCGenericImport__2<_di_GADMediatedUnifiedNativeAdNotificationSourceClass,_di_GADMediatedUnifiedNativeAdNotificationSource>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADMediatedUnifiedNativeAdNotificationSourceClass,_di_GADMediatedUnifiedNativeAdNotificationSource> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADMediatedUnifiedNativeAdNotificationSource(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADMediatedUnifiedNativeAdNotificationSourceClass,_di_GADMediatedUnifiedNativeAdNotificationSource>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADMediatedUnifiedNativeAdNotificationSource() { }
	
};


__interface  INTERFACE_UUID("{7F708A01-022A-45C0-85B3-8F26F61C1144}") GADMediationAd  : public Macapi::Objectivec::IObjectiveC 
{
	
};

__interface  INTERFACE_UUID("{E3873293-E023-4772-9B7B-8E4200E40CA3}") GADMediationAdEventDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl didDismissFullScreenView() = 0 ;
	virtual void __cdecl didFailToPresentWithError(Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl reportClick() = 0 ;
	virtual void __cdecl reportImpression() = 0 ;
	virtual void __cdecl willDismissFullScreenView() = 0 ;
	virtual void __cdecl willPresentFullScreenView() = 0 ;
};

__interface  INTERFACE_UUID("{AAB805DC-6C65-4992-9624-10327284B221}") GADMediationBannerAdEventDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl willBackgroundApplication() = 0 ;
};

__interface  INTERFACE_UUID("{EB6E4D1F-CA60-46CF-855A-09EA29042239}") GADMediationInterstitialAdEventDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl willBackgroundApplication() = 0 ;
};

__interface  INTERFACE_UUID("{D8488634-4E82-40F2-8395-BB8E6C9B2CAE}") GADMediationNativeAdEventDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl didEndVideo() = 0 ;
	virtual void __cdecl didMuteVideo() = 0 ;
	virtual void __cdecl didPauseVideo() = 0 ;
	virtual void __cdecl didPlayVideo() = 0 ;
	virtual void __cdecl didUnmuteVideo() = 0 ;
	virtual void __cdecl willBackgroundApplication() = 0 ;
};

__interface  INTERFACE_UUID("{481B52DD-396C-4113-AFDE-1E12BF5DC769}") GADMediationRewardedAdEventDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl didEndVideo() = 0 ;
	virtual void __cdecl didRewardUserWithReward(_di_GADAdReward reward) = 0 ;
	virtual void __cdecl didStartVideo() = 0 ;
};

__interface  INTERFACE_UUID("{AA3F7D3F-B494-442A-940A-805BBE5D4F5D}") GADMediationCredentialsClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{8B9BDDBA-B2FD-4677-8818-6A1302CC07AD}") GADMediationCredentials  : public Iosapi::Foundation::NSObject 
{
	virtual long __cdecl format() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl settings() = 0 ;
};

class PASCALIMPLEMENTATION TGADMediationCredentials : public Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationCredentialsClass,_di_GADMediationCredentials>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationCredentialsClass,_di_GADMediationCredentials> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADMediationCredentials(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationCredentialsClass,_di_GADMediationCredentials>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADMediationCredentials() { }
	
};


__interface  INTERFACE_UUID("{ACD12D69-432D-4E3A-9851-89933C87E7CE}") GADMediationServerConfigurationClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{A0BDC528-A319-439C-9A95-BD81E94BDD5A}") GADMediationServerConfiguration  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl credentials() = 0 ;
};

class PASCALIMPLEMENTATION TGADMediationServerConfiguration : public Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationServerConfigurationClass,_di_GADMediationServerConfiguration>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationServerConfigurationClass,_di_GADMediationServerConfiguration> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADMediationServerConfiguration(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationServerConfigurationClass,_di_GADMediationServerConfiguration>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADMediationServerConfiguration() { }
	
};


__interface  INTERFACE_UUID("{BF240130-34C4-48FA-AB54-3FFB9088A612}") GADMediationAdConfigurationClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{26486727-B559-4936-9C44-2C66DE78EC97}") GADMediationAdConfiguration  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl bidResponse() = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl childDirectedTreatment() = 0 ;
	virtual _di_GADMediationCredentials __cdecl credentials() = 0 ;
	virtual void * __cdecl extras() = 0 ;
	virtual bool __cdecl hasUserLocation() = 0 ;
	virtual bool __cdecl isTestRequest() = 0 ;
	virtual Iosapi::Uikit::_di_UIViewController __cdecl topViewController() = 0 ;
	virtual double __cdecl userLatitude() = 0 ;
	virtual double __cdecl userLocationAccuracyInMeters() = 0 ;
	virtual double __cdecl userLongitude() = 0 ;
	virtual Iosapi::Foundation::_di_NSData __cdecl watermark() = 0 ;
};

class PASCALIMPLEMENTATION TGADMediationAdConfiguration : public Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationAdConfigurationClass,_di_GADMediationAdConfiguration>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationAdConfigurationClass,_di_GADMediationAdConfiguration> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADMediationAdConfiguration(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationAdConfigurationClass,_di_GADMediationAdConfiguration>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADMediationAdConfiguration() { }
	
};


__interface  INTERFACE_UUID("{6AAAD9C6-4C4F-4122-92B1-953D1EBC929E}") GADMediationBannerAd  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl changeAdSizeTo(GADAdSize adSize) = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl view() = 0 ;
};

__interface  INTERFACE_UUID("{BDF1A673-EC57-4DDD-A830-9F4609A83D7F}") GADMediationBannerAdConfigurationClass  : public GADMediationAdConfigurationClass 
{
	
};

__interface  INTERFACE_UUID("{71F82B1A-9DFE-498B-8057-BBC91E82F515}") GADMediationBannerAdConfiguration  : public GADMediationAdConfiguration 
{
	virtual GADAdSize __cdecl adSize() = 0 ;
};

class PASCALIMPLEMENTATION TGADMediationBannerAdConfiguration : public Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationBannerAdConfigurationClass,_di_GADMediationBannerAdConfiguration>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationBannerAdConfigurationClass,_di_GADMediationBannerAdConfiguration> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADMediationBannerAdConfiguration(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationBannerAdConfigurationClass,_di_GADMediationBannerAdConfiguration>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADMediationBannerAdConfiguration() { }
	
};


__interface  INTERFACE_UUID("{B10D7AE9-4EBF-4779-B59C-B75E29C7A35E}") GADMediationInterstitialAd  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl presentFromViewController(Iosapi::Uikit::_di_UIViewController viewController) = 0 ;
};

__interface  INTERFACE_UUID("{1B8176B4-937A-4013-813B-8CA4C6A302BB}") GADMediationInterstitialAdConfigurationClass  : public GADMediationAdConfigurationClass 
{
	
};

__interface  INTERFACE_UUID("{527209CA-68AD-46D7-858E-02C22C1AD512}") GADMediationInterstitialAdConfiguration  : public GADMediationAdConfiguration 
{
	
};

class PASCALIMPLEMENTATION TGADMediationInterstitialAdConfiguration : public Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationInterstitialAdConfigurationClass,_di_GADMediationInterstitialAdConfiguration>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationInterstitialAdConfigurationClass,_di_GADMediationInterstitialAdConfiguration> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADMediationInterstitialAdConfiguration(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationInterstitialAdConfigurationClass,_di_GADMediationInterstitialAdConfiguration>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADMediationInterstitialAdConfiguration() { }
	
};


__interface  INTERFACE_UUID("{917168AA-B042-420A-8F2E-85CADE689749}") GADMediationNativeAd  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl handlesUserClicks() = 0 ;
	virtual bool __cdecl handlesUserImpressions() = 0 ;
};

__interface  INTERFACE_UUID("{0C8B0EAC-D9D6-46DF-BB70-D0E10B4C14FF}") GADMediationNativeAdConfigurationClass  : public GADMediationAdConfigurationClass 
{
	
};

__interface  INTERFACE_UUID("{DABFBD31-84DF-4C22-B658-EDA09C1782C4}") GADMediationNativeAdConfiguration  : public GADMediationAdConfiguration 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl options() = 0 ;
};

class PASCALIMPLEMENTATION TGADMediationNativeAdConfiguration : public Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationNativeAdConfigurationClass,_di_GADMediationNativeAdConfiguration>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationNativeAdConfigurationClass,_di_GADMediationNativeAdConfiguration> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADMediationNativeAdConfiguration(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationNativeAdConfigurationClass,_di_GADMediationNativeAdConfiguration>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADMediationNativeAdConfiguration() { }
	
};


__interface  INTERFACE_UUID("{18428C2D-54BA-485C-AA76-DB4BCE317CD1}") GADMediationRewardedAd  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl presentFromViewController(Iosapi::Uikit::_di_UIViewController viewController) = 0 ;
};

__interface  INTERFACE_UUID("{4285717C-FAE2-4490-8D23-6C6DFCEC0918}") GADMediationRewardedAdConfigurationClass  : public GADMediationAdConfigurationClass 
{
	
};

__interface  INTERFACE_UUID("{B9DCBAED-6338-4320-865F-7B4AB35A2D85}") GADMediationRewardedAdConfiguration  : public GADMediationAdConfiguration 
{
	
};

class PASCALIMPLEMENTATION TGADMediationRewardedAdConfiguration : public Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationRewardedAdConfigurationClass,_di_GADMediationRewardedAdConfiguration>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationRewardedAdConfigurationClass,_di_GADMediationRewardedAdConfiguration> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADMediationRewardedAdConfiguration(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADMediationRewardedAdConfigurationClass,_di_GADMediationRewardedAdConfiguration>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADMediationRewardedAdConfiguration() { }
	
};


__interface  INTERFACE_UUID("{F608666C-23B6-4E25-8876-1A835960108A}") GADMediationAdapter  : public Macapi::Objectivec::IObjectiveC 
{
	virtual GADVersionNumber __cdecl adSDKVersion() = 0 ;
	virtual void __cdecl loadBannerForAdConfiguration(_di_GADMediationBannerAdConfiguration adConfiguration, GADMediationBannerLoadCompletionHandler completionHandler) = 0 ;
	virtual void __cdecl loadInterstitialForAdConfiguration(_di_GADMediationInterstitialAdConfiguration adConfiguration, GADMediationInterstitialLoadCompletionHandler completionHandler) = 0 ;
	virtual void __cdecl loadNativeAdForAdConfiguration(_di_GADMediationNativeAdConfiguration adConfiguration, GADMediationNativeLoadCompletionHandler completionHandler) = 0 ;
	virtual void __cdecl loadRewardedAdForAdConfiguration(_di_GADMediationRewardedAdConfiguration adConfiguration, GADMediationRewardedLoadCompletionHandler completionHandler) = 0 ;
	virtual void * __cdecl networkExtrasClass() = 0 ;
	virtual void __cdecl setUpWithConfiguration(_di_GADMediationServerConfiguration configuration, GADMediationAdapterSetUpCompletionBlock completionHandler) = 0 ;
	virtual GADVersionNumber __cdecl version() = 0 ;
};

__interface  INTERFACE_UUID("{46E67DF5-20C3-469D-B654-37DC73FA0406}") GADMRewardBasedVideoAdNetworkAdapter  : public Macapi::Objectivec::IObjectiveC 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl adapterVersion() = 0 ;
	virtual void * __cdecl initWithGADMAdNetworkConnector(void * connector) = 0 ;
	virtual void * __cdecl initWithRewardBasedVideoAdNetworkConnector(void * connector, Iosapi::Foundation::_di_NSArray credentials) = 0 /* overload */;
	virtual void * __cdecl initWithRewardBasedVideoAdNetworkConnector(void * connector) = 0 /* overload */;
	virtual void * __cdecl networkExtrasClass() = 0 ;
	virtual void __cdecl presentRewardBasedVideoAdWithRootViewController(Iosapi::Uikit::_di_UIViewController viewController) = 0 ;
	virtual void __cdecl requestRewardBasedVideoAd() = 0 ;
	virtual void __cdecl setUp() = 0 ;
	virtual void __cdecl setUpWithUserID(Iosapi::Foundation::_di_NSString userID) = 0 ;
	virtual void __cdecl stopBeingDelegate() = 0 ;
};

__interface  INTERFACE_UUID("{22F3F270-CCBB-4421-8ADB-8F23B7EE687B}") GADMRewardBasedVideoAdNetworkConnector  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl adapterDidCloseRewardBasedVideoAd(void * rewardBasedVideoAdAdapter) = 0 ;
	virtual void __cdecl adapterDidCompletePlayingRewardBasedVideoAd(void * rewardBasedVideoAdAdapter) = 0 ;
	virtual void __cdecl adapterDidFailToLoadRewardBasedVideoAdwithError(void * rewardBasedVideoAdAdapter, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl adapterDidFailToSetUpRewardBasedVideoAdWithError(void * rewardBasedVideoAdAdapter, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl adapterDidGetAdClick(void * adapter) = 0 ;
	virtual void __cdecl adapterDidOpenRewardBasedVideoAd(void * rewardBasedVideoAdAdapter) = 0 ;
	virtual void __cdecl adapterDidReceiveRewardBasedVideoAd(void * rewardBasedVideoAdAdapter) = 0 ;
	virtual void __cdecl adapterDidRewardUserWithReward(void * rewardBasedVideoAd, _di_GADAdReward reward) = 0 ;
	virtual void __cdecl adapterDidSetUpRewardBasedVideoAd(void * rewardBasedVideoAdAdapter) = 0 ;
	virtual void __cdecl adapterDidStartPlayingRewardBasedVideoAd(void * rewardBasedVideoAdAdapter) = 0 ;
	virtual void __cdecl adapterWillLeaveApplication(void * rewardBasedVideoAdAdapter) = 0 ;
};

__interface  INTERFACE_UUID("{58A0CC75-9AB5-4BE1-A6C9-3DE384A795C4}") GADRTBMediationSignalsConfigurationClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{C6222D60-12DB-432C-B39E-157E1766BA4B}") GADRTBMediationSignalsConfiguration  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl credentials() = 0 ;
};

class PASCALIMPLEMENTATION TGADRTBMediationSignalsConfiguration : public Macapi::Objectivec::TOCGenericImport__2<_di_GADRTBMediationSignalsConfigurationClass,_di_GADRTBMediationSignalsConfiguration>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADRTBMediationSignalsConfigurationClass,_di_GADRTBMediationSignalsConfiguration> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADRTBMediationSignalsConfiguration(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADRTBMediationSignalsConfigurationClass,_di_GADRTBMediationSignalsConfiguration>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADRTBMediationSignalsConfiguration() { }
	
};


__interface  INTERFACE_UUID("{E339E5A0-C2BB-4AFE-8EE9-3DD4DAFDAF7B}") GADRTBRequestParametersClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{408B3D98-CFEB-4C97-A098-BE5C5CAAC402}") GADRTBRequestParameters  : public Iosapi::Foundation::NSObject 
{
	virtual GADAdSize __cdecl adSize() = 0 ;
	virtual _di_GADRTBMediationSignalsConfiguration __cdecl configuration() = 0 ;
	virtual void * __cdecl extras() = 0 ;
};

class PASCALIMPLEMENTATION TGADRTBRequestParameters : public Macapi::Objectivec::TOCGenericImport__2<_di_GADRTBRequestParametersClass,_di_GADRTBRequestParameters>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GADRTBRequestParametersClass,_di_GADRTBRequestParameters> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGADRTBRequestParameters(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GADRTBRequestParametersClass,_di_GADRTBRequestParameters>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGADRTBRequestParameters() { }
	
};


__interface  INTERFACE_UUID("{CF250129-7F8A-46A3-8D6D-EB2BE33189EC}") GADRTBAdapter  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl collectSignalsForRequestParameters(_di_GADRTBRequestParameters params, GADRTBSignalCompletionHandler completionHandler) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 kGADErrorInvalidRequest = System::Int8(0x0);
static constexpr System::Int8 kGADErrorNoFill = System::Int8(0x1);
static constexpr System::Int8 kGADErrorNetworkError = System::Int8(0x2);
static constexpr System::Int8 kGADErrorServerError = System::Int8(0x3);
static constexpr System::Int8 kGADErrorOSVersionTooLow = System::Int8(0x4);
static constexpr System::Int8 kGADErrorTimeout = System::Int8(0x5);
static constexpr System::Int8 kGADErrorInterstitialAlreadyUsed = System::Int8(0x6);
static constexpr System::Int8 kGADErrorMediationDataError = System::Int8(0x7);
static constexpr System::Int8 kGADErrorMediationAdapterError = System::Int8(0x8);
static constexpr System::Int8 kGADErrorMediationInvalidAdSize = System::Int8(0xa);
static constexpr System::Int8 kGADErrorInternalError = System::Int8(0xb);
static constexpr System::Int8 kGADErrorInvalidArgument = System::Int8(0xc);
static constexpr System::Int8 kGADErrorReceivedInvalidResponse = System::Int8(0xd);
static constexpr System::Int8 kGADErrorRewardedAdAlreadyUsed = System::Int8(0xe);
static constexpr System::Int8 kGADErrorMediationNoFill = System::Int8(0x9);
static constexpr System::Int8 kGADErrorAdAlreadyUsed = System::Int8(0x13);
static constexpr System::Int8 kGADErrorApplicationIdentifierMissing = System::Int8(0x14);
static constexpr System::Int8 kGADGenderUnknown = System::Int8(0x0);
static constexpr System::Int8 kGADGenderMale = System::Int8(0x1);
static constexpr System::Int8 kGADGenderFemale = System::Int8(0x2);
static constexpr System::Int8 GADAdValuePrecisionUnknown = System::Int8(0x0);
static constexpr System::Int8 GADAdValuePrecisionEstimated = System::Int8(0x1);
static constexpr System::Int8 GADAdValuePrecisionPublisherProvided = System::Int8(0x2);
static constexpr System::Int8 GADAdValuePrecisionPrecise = System::Int8(0x3);
static constexpr System::Int8 GADAdFormatBanner = System::Int8(0x0);
static constexpr System::Int8 GADAdFormatInterstitial = System::Int8(0x1);
static constexpr System::Int8 GADAdFormatRewarded = System::Int8(0x2);
static constexpr System::Int8 GADAdFormatNative = System::Int8(0x3);
static constexpr System::Int8 GADAdapterInitializationStateNotReady = System::Int8(0x0);
static constexpr System::Int8 GADAdapterInitializationStateReady = System::Int8(0x1);
static constexpr System::Int8 kGADInAppPurchaseStatusError = System::Int8(0x0);
static constexpr System::Int8 kGADInAppPurchaseStatusSuccessful = System::Int8(0x1);
static constexpr System::Int8 kGADInAppPurchaseStatusCancel = System::Int8(0x2);
static constexpr System::Int8 kGADInAppPurchaseStatusInvalidProduct = System::Int8(0x3);
static constexpr System::Int8 GADMediaAspectRatioUnknown = System::Int8(0x0);
static constexpr System::Int8 GADMediaAspectRatioAny = System::Int8(0x1);
static constexpr System::Int8 GADMediaAspectRatioLandscape = System::Int8(0x2);
static constexpr System::Int8 GADMediaAspectRatioPortrait = System::Int8(0x3);
static constexpr System::Int8 GADMediaAspectRatioSquare = System::Int8(0x4);
static constexpr System::Int8 GADNativeAdImageAdLoaderOptionsOrientationAny = System::Int8(0x1);
static constexpr System::Int8 GADNativeAdImageAdLoaderOptionsOrientationPortrait = System::Int8(0x2);
static constexpr System::Int8 GADNativeAdImageAdLoaderOptionsOrientationLandscape = System::Int8(0x3);
static constexpr System::Int8 GADAdChoicesPositionTopRightCorner = System::Int8(0x0);
static constexpr System::Int8 GADAdChoicesPositionTopLeftCorner = System::Int8(0x1);
static constexpr System::Int8 GADAdChoicesPositionBottomRightCorner = System::Int8(0x2);
static constexpr System::Int8 GADAdChoicesPositionBottomLeftCorner = System::Int8(0x3);
static constexpr System::Int8 GADPresentationErrorCodeAdNotReady = System::Int8(0xf);
static constexpr System::Int8 GADPresentationErrorCodeAdTooLarge = System::Int8(0x10);
static constexpr System::Int8 GADPresentationErrorCodeInternal = System::Int8(0x11);
static constexpr System::Int8 GADPresentationErrorCodeAdAlreadyUsed = System::Int8(0x12);
static constexpr System::Int8 kGADMBannerAnimationTypeNone = System::Int8(0x0);
static constexpr System::Int8 kGADMBannerAnimationTypeFlipFromLeft = System::Int8(0x1);
static constexpr System::Int8 kGADMBannerAnimationTypeFlipFromRight = System::Int8(0x2);
static constexpr System::Int8 kGADMBannerAnimationTypeCurlUp = System::Int8(0x3);
static constexpr System::Int8 kGADMBannerAnimationTypeCurlDown = System::Int8(0x4);
static constexpr System::Int8 kGADMBannerAnimationTypeSlideFromLeft = System::Int8(0x5);
static constexpr System::Int8 kGADMBannerAnimationTypeSlideFromRight = System::Int8(0x6);
static constexpr System::Int8 kGADMBannerAnimationTypeFadeIn = System::Int8(0x7);
static constexpr System::Int8 kGADMBannerAnimationTypeRandom = System::Int8(0x8);
extern "C" GADAdSize __cdecl GADPortraitAnchoredAdaptiveBannerAdSizeWithWidth(double width);
extern "C" GADAdSize __cdecl GADLandscapeAnchoredAdaptiveBannerAdSizeWithWidth(double width);
extern "C" GADAdSize __cdecl GADCurrentOrientationAnchoredAdaptiveBannerAdSizeWithWidth(double width);
extern "C" GADAdSize __cdecl GADAdSizeFromCGSize(Iosapi::Foundation::NSSize size);
extern "C" GADAdSize __cdecl GADAdSizeFullWidthPortraitWithHeight(double height);
extern "C" GADAdSize __cdecl GADAdSizeFullWidthLandscapeWithHeight(double height);
extern "C" bool __cdecl GADAdSizeEqualToSize(GADAdSize size1, GADAdSize size2);
extern "C" Iosapi::Foundation::NSSize __cdecl CGSizeFromGADAdSize(GADAdSize size);
extern "C" bool __cdecl IsGADAdSizeValid(GADAdSize size);
extern "C" bool __cdecl GADAdSizeIsFluid(GADAdSize size);
extern "C" Iosapi::Foundation::_di_NSString __cdecl NSStringFromGADAdSize(GADAdSize size);
extern "C" Iosapi::Uikit::_di_NSValue __cdecl NSValueFromGADAdSize(GADAdSize size);
extern "C" GADAdSize __cdecl GADAdSizeFromNSValue(Iosapi::Uikit::_di_NSValue value);
extern "C" GADAdSize __cdecl GADClosestValidSizeForAdSizes(GADAdSize original, Iosapi::Foundation::_di_NSArray possibleAdSizes);
extern DELPHI_PACKAGE GADAdSize __fastcall kGADAdSizeBanner(void);
extern DELPHI_PACKAGE GADAdSize __fastcall kGADAdSizeLargeBanner(void);
extern DELPHI_PACKAGE GADAdSize __fastcall kGADAdSizeMediumRectangle(void);
extern DELPHI_PACKAGE GADAdSize __fastcall kGADAdSizeFullBanner(void);
extern DELPHI_PACKAGE GADAdSize __fastcall kGADAdSizeLeaderboard(void);
}	/* namespace Googlemobileads */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_GOOGLEMOBILEADS)
using namespace Iosapi::Googlemobileads;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_GooglemobileadsHPP
