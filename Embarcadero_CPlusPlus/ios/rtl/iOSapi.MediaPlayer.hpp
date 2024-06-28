// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.MediaPlayer.pas' rev: 34.00 (iOS)

#ifndef Iosapi_MediaplayerHPP
#define Iosapi_MediaplayerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <Macapi.ObjCRuntime.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Mediaplayer
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE MPMoviePlayerControllerClass;
typedef System::DelphiInterface<MPMoviePlayerControllerClass> _di_MPMoviePlayerControllerClass;
__interface DELPHIINTERFACE MPMoviePlayerController;
typedef System::DelphiInterface<MPMoviePlayerController> _di_MPMoviePlayerController;
class DELPHICLASS TMPMoviePlayerController;
__interface DELPHIINTERFACE MPMusicPlayerControllerClass;
typedef System::DelphiInterface<MPMusicPlayerControllerClass> _di_MPMusicPlayerControllerClass;
__interface DELPHIINTERFACE MPMusicPlayerController;
typedef System::DelphiInterface<MPMusicPlayerController> _di_MPMusicPlayerController;
class DELPHICLASS TMPMusicPlayerController;
__interface DELPHIINTERFACE MPMovieErrorLogEventClass;
typedef System::DelphiInterface<MPMovieErrorLogEventClass> _di_MPMovieErrorLogEventClass;
__interface DELPHIINTERFACE MPMovieErrorLogEvent;
typedef System::DelphiInterface<MPMovieErrorLogEvent> _di_MPMovieErrorLogEvent;
class DELPHICLASS TMPMovieErrorLogEvent;
__interface DELPHIINTERFACE MPMovieAccessLogEventClass;
typedef System::DelphiInterface<MPMovieAccessLogEventClass> _di_MPMovieAccessLogEventClass;
__interface DELPHIINTERFACE MPMovieAccessLogEvent;
typedef System::DelphiInterface<MPMovieAccessLogEvent> _di_MPMovieAccessLogEvent;
class DELPHICLASS TMPMovieAccessLogEvent;
__interface DELPHIINTERFACE MPMovieErrorLogClass;
typedef System::DelphiInterface<MPMovieErrorLogClass> _di_MPMovieErrorLogClass;
__interface DELPHIINTERFACE MPMovieErrorLog;
typedef System::DelphiInterface<MPMovieErrorLog> _di_MPMovieErrorLog;
class DELPHICLASS TMPMovieErrorLog;
__interface DELPHIINTERFACE MPVolumeViewClass;
typedef System::DelphiInterface<MPVolumeViewClass> _di_MPVolumeViewClass;
__interface DELPHIINTERFACE MPVolumeView;
typedef System::DelphiInterface<MPVolumeView> _di_MPVolumeView;
class DELPHICLASS TMPVolumeView;
__interface DELPHIINTERFACE MPNowPlayingInfoCenterClass;
typedef System::DelphiInterface<MPNowPlayingInfoCenterClass> _di_MPNowPlayingInfoCenterClass;
__interface DELPHIINTERFACE MPNowPlayingInfoCenter;
typedef System::DelphiInterface<MPNowPlayingInfoCenter> _di_MPNowPlayingInfoCenter;
class DELPHICLASS TMPNowPlayingInfoCenter;
__interface DELPHIINTERFACE MPTimedMetadataClass;
typedef System::DelphiInterface<MPTimedMetadataClass> _di_MPTimedMetadataClass;
__interface DELPHIINTERFACE MPTimedMetadata;
typedef System::DelphiInterface<MPTimedMetadata> _di_MPTimedMetadata;
class DELPHICLASS TMPTimedMetadata;
__interface DELPHIINTERFACE MPMediaEntityClass;
typedef System::DelphiInterface<MPMediaEntityClass> _di_MPMediaEntityClass;
__interface DELPHIINTERFACE MPMediaEntity;
typedef System::DelphiInterface<MPMediaEntity> _di_MPMediaEntity;
class DELPHICLASS TMPMediaEntity;
__interface DELPHIINTERFACE MPMediaLibraryClass;
typedef System::DelphiInterface<MPMediaLibraryClass> _di_MPMediaLibraryClass;
__interface DELPHIINTERFACE MPMediaLibrary;
typedef System::DelphiInterface<MPMediaLibrary> _di_MPMediaLibrary;
class DELPHICLASS TMPMediaLibrary;
__interface DELPHIINTERFACE MPMediaItemArtworkClass;
typedef System::DelphiInterface<MPMediaItemArtworkClass> _di_MPMediaItemArtworkClass;
__interface DELPHIINTERFACE MPMediaItemArtwork;
typedef System::DelphiInterface<MPMediaItemArtwork> _di_MPMediaItemArtwork;
class DELPHICLASS TMPMediaItemArtwork;
__interface DELPHIINTERFACE MPMediaPredicateClass;
typedef System::DelphiInterface<MPMediaPredicateClass> _di_MPMediaPredicateClass;
__interface DELPHIINTERFACE MPMediaPredicate;
typedef System::DelphiInterface<MPMediaPredicate> _di_MPMediaPredicate;
class DELPHICLASS TMPMediaPredicate;
__interface DELPHIINTERFACE MPMediaPropertyPredicateClass;
typedef System::DelphiInterface<MPMediaPropertyPredicateClass> _di_MPMediaPropertyPredicateClass;
__interface DELPHIINTERFACE MPMediaPropertyPredicate;
typedef System::DelphiInterface<MPMediaPropertyPredicate> _di_MPMediaPropertyPredicate;
class DELPHICLASS TMPMediaPropertyPredicate;
__interface DELPHIINTERFACE MPMediaQuerySectionClass;
typedef System::DelphiInterface<MPMediaQuerySectionClass> _di_MPMediaQuerySectionClass;
__interface DELPHIINTERFACE MPMediaQuerySection;
typedef System::DelphiInterface<MPMediaQuerySection> _di_MPMediaQuerySection;
class DELPHICLASS TMPMediaQuerySection;
__interface DELPHIINTERFACE MPMovieAccessLogClass;
typedef System::DelphiInterface<MPMovieAccessLogClass> _di_MPMovieAccessLogClass;
__interface DELPHIINTERFACE MPMovieAccessLog;
typedef System::DelphiInterface<MPMovieAccessLog> _di_MPMovieAccessLog;
class DELPHICLASS TMPMovieAccessLog;
__interface DELPHIINTERFACE MPMediaQueryClass;
typedef System::DelphiInterface<MPMediaQueryClass> _di_MPMediaQueryClass;
__interface DELPHIINTERFACE MPMediaQuery;
typedef System::DelphiInterface<MPMediaQuery> _di_MPMediaQuery;
class DELPHICLASS TMPMediaQuery;
__interface DELPHIINTERFACE MPMediaItemClass;
typedef System::DelphiInterface<MPMediaItemClass> _di_MPMediaItemClass;
__interface DELPHIINTERFACE MPMediaItem;
typedef System::DelphiInterface<MPMediaItem> _di_MPMediaItem;
class DELPHICLASS TMPMediaItem;
__interface DELPHIINTERFACE MPMoviePlayerViewControllerClass;
typedef System::DelphiInterface<MPMoviePlayerViewControllerClass> _di_MPMoviePlayerViewControllerClass;
__interface DELPHIINTERFACE MPMoviePlayerViewController;
typedef System::DelphiInterface<MPMoviePlayerViewController> _di_MPMoviePlayerViewController;
class DELPHICLASS TMPMoviePlayerViewController;
__interface DELPHIINTERFACE MPMediaPickerControllerClass;
typedef System::DelphiInterface<MPMediaPickerControllerClass> _di_MPMediaPickerControllerClass;
__interface DELPHIINTERFACE MPMediaPickerController;
typedef System::DelphiInterface<MPMediaPickerController> _di_MPMediaPickerController;
class DELPHICLASS TMPMediaPickerController;
__interface DELPHIINTERFACE MPMediaItemCollectionClass;
typedef System::DelphiInterface<MPMediaItemCollectionClass> _di_MPMediaItemCollectionClass;
__interface DELPHIINTERFACE MPMediaItemCollection;
typedef System::DelphiInterface<MPMediaItemCollection> _di_MPMediaItemCollection;
class DELPHICLASS TMPMediaItemCollection;
__interface DELPHIINTERFACE MPMediaPickerControllerDelegate;
typedef System::DelphiInterface<MPMediaPickerControllerDelegate> _di_MPMediaPickerControllerDelegate;
__interface DELPHIINTERFACE MPMediaPlayback;
typedef System::DelphiInterface<MPMediaPlayback> _di_MPMediaPlayback;
//-- type declarations -------------------------------------------------------
typedef long MPMediaGrouping;

typedef long MPMediaPredicateComparison;

typedef long MPMediaType;

typedef long MPMovieControlStyle;

typedef long MPMovieFinishReason;

typedef long MPMovieLoadState;

typedef long MPMovieMediaTypeMask;

typedef long MPMoviePlaybackState;

typedef long MPMovieRepeatMode;

typedef long MPMovieScalingMode;

typedef long MPMovieSourceType;

typedef long MPMovieTimeOption;

typedef long MPMusicPlaybackState;

typedef long MPMusicRepeatMode;

typedef long MPMusicShuffleMode;

typedef long MPMediaLibraryAuthorizationStatus;

typedef void __fastcall (__closure *TMediaPlayerHandler)(long status);

__interface  INTERFACE_UUID("{D03E6638-4E23-4E84-9F1D-77352CF215F4}") MPMoviePlayerControllerClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{8C2105E8-2B61-444D-9AC5-6370C1F06A46}") MPMoviePlayerController  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MPMovieAccessLog __cdecl accessLog() = 0 ;
	virtual bool __cdecl allowsAirPlay() = 0 ;
	virtual Iosapi::Uikit::_di_UIColor __cdecl backgroundColor() = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl backgroundView() = 0 ;
	virtual void __cdecl cancelAllThumbnailImageRequests() = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl contentURL() = 0 ;
	virtual long __cdecl controlStyle() = 0 ;
	virtual double __cdecl duration() = 0 ;
	virtual double __cdecl endPlaybackTime() = 0 ;
	virtual _di_MPMovieErrorLog __cdecl errorLog() = 0 ;
	virtual void * __cdecl initWithContentURL(Iosapi::Foundation::_di_NSURL url) = 0 ;
	virtual double __cdecl initialPlaybackTime() = 0 ;
	virtual bool __cdecl isAirPlayVideoActive() = 0 ;
	virtual bool __cdecl isFullscreen() = 0 ;
	virtual long __cdecl loadState() = 0 ;
	virtual long __cdecl movieMediaTypes() = 0 ;
	virtual long __cdecl movieSourceType() = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl naturalSize() = 0 ;
	virtual double __cdecl playableDuration() = 0 ;
	virtual long __cdecl playbackState() = 0 ;
	virtual long __cdecl repeatMode() = 0 ;
	virtual void __cdecl requestThumbnailImagesAtTimes(Iosapi::Foundation::_di_NSArray playbackTimes, long timeOption) = 0 ;
	virtual long __cdecl scalingMode() = 0 ;
	virtual void __cdecl setAllowsAirPlay(bool allowsAirPlay) = 0 ;
	virtual void __cdecl setBackgroundColor(Iosapi::Uikit::_di_UIColor backgroundColor) = 0 ;
	virtual void __cdecl setContentURL(Iosapi::Foundation::_di_NSURL contentURL) = 0 ;
	virtual void __cdecl setControlStyle(long controlStyle) = 0 ;
	virtual void __cdecl setEndPlaybackTime(double endPlaybackTime) = 0 ;
	virtual void __cdecl setFullscreen(bool fullscreen) = 0 /* overload */;
	virtual void __cdecl setFullscreen(bool fullscreen, bool animated) = 0 /* overload */;
	virtual void __cdecl setInitialPlaybackTime(double initialPlaybackTime) = 0 ;
	virtual void __cdecl setMovieSourceType(long movieSourceType) = 0 ;
	virtual void __cdecl setRepeatMode(long repeatMode) = 0 ;
	virtual void __cdecl setScalingMode(long scalingMode) = 0 ;
	virtual void __cdecl setShouldAutoplay(bool shouldAutoplay) = 0 ;
	virtual void __cdecl setUseApplicationAudioSession(bool useApplicationAudioSession) = 0 ;
	virtual bool __cdecl shouldAutoplay() = 0 ;
	virtual Iosapi::Uikit::_di_UIImage __cdecl thumbnailImageAtTime(double playbackTime, long timeOption) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl timedMetadata() = 0 ;
	virtual bool __cdecl useApplicationAudioSession() = 0 ;
	virtual Iosapi::Uikit::_di_UIView __cdecl view() = 0 ;
};

class PASCALIMPLEMENTATION TMPMoviePlayerController : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMoviePlayerControllerClass,_di_MPMoviePlayerController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMoviePlayerControllerClass,_di_MPMoviePlayerController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMoviePlayerController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMoviePlayerControllerClass,_di_MPMoviePlayerController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMoviePlayerController() { }
	
};


__interface  INTERFACE_UUID("{A8BB0A1F-CF69-43AE-A308-2515A413274A}") MPMusicPlayerControllerClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl applicationMusicPlayer() = 0 ;
	virtual void * __cdecl iPodMusicPlayer() = 0 ;
};

__interface  INTERFACE_UUID("{A37F2D41-2CF8-488A-9989-38D58DF897C0}") MPMusicPlayerController  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl beginGeneratingPlaybackNotifications() = 0 ;
	virtual void __cdecl beginSeekingBackward() = 0 ;
	virtual void __cdecl beginSeekingForward() = 0 ;
	virtual double __cdecl currentPlaybackTime() = 0 ;
	virtual void __cdecl endGeneratingPlaybackNotifications() = 0 ;
	virtual void __cdecl endSeeking() = 0 ;
	virtual unsigned long __cdecl indexOfNowPlayingItem() = 0 ;
	virtual _di_MPMediaItem __cdecl nowPlayingItem() = 0 ;
	virtual void __cdecl pause() = 0 ;
	virtual void __cdecl play() = 0 ;
	virtual long __cdecl playbackState() = 0 ;
	virtual long __cdecl repeatMode() = 0 ;
	virtual void __cdecl setCurrentPlaybackTime(double currentPlaybackTime) = 0 ;
	virtual void __cdecl setNowPlayingItem(_di_MPMediaItem nowPlayingItem) = 0 ;
	virtual void __cdecl setQueueWithItemCollection(_di_MPMediaItemCollection itemCollection) = 0 ;
	virtual void __cdecl setQueueWithQuery(_di_MPMediaQuery query) = 0 ;
	virtual void __cdecl setRepeatMode(long repeatMode) = 0 ;
	virtual void __cdecl setShuffleMode(long shuffleMode) = 0 ;
	virtual void __cdecl setVolume(float volume) = 0 ;
	virtual long __cdecl shuffleMode() = 0 ;
	virtual void __cdecl skipToBeginning() = 0 ;
	virtual void __cdecl skipToNextItem() = 0 ;
	virtual void __cdecl skipToPreviousItem() = 0 ;
	virtual void __cdecl stop() = 0 ;
	virtual float __cdecl volume() = 0 ;
};

class PASCALIMPLEMENTATION TMPMusicPlayerController : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMusicPlayerControllerClass,_di_MPMusicPlayerController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMusicPlayerControllerClass,_di_MPMusicPlayerController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMusicPlayerController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMusicPlayerControllerClass,_di_MPMusicPlayerController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMusicPlayerController() { }
	
};


__interface  INTERFACE_UUID("{CB09AAE2-B9DD-4E09-9511-D9C08AD457DB}") MPMovieErrorLogEventClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{E4EDC760-F8BB-42B2-BA3C-C9606CFAC50F}") MPMovieErrorLogEvent  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl URI() = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl date() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl errorComment() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl errorDomain() = 0 ;
	virtual long __cdecl errorStatusCode() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl playbackSessionID() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl serverAddress() = 0 ;
};

class PASCALIMPLEMENTATION TMPMovieErrorLogEvent : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMovieErrorLogEventClass,_di_MPMovieErrorLogEvent>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMovieErrorLogEventClass,_di_MPMovieErrorLogEvent> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMovieErrorLogEvent(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMovieErrorLogEventClass,_di_MPMovieErrorLogEvent>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMovieErrorLogEvent() { }
	
};


__interface  INTERFACE_UUID("{114E931A-A4D1-46B9-90EC-EF1BC2F4ECDA}") MPMovieAccessLogEventClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{7AAF41DA-D917-45A2-AAE7-856BA010DA5F}") MPMovieAccessLogEvent  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl URI() = 0 ;
	virtual double __cdecl durationWatched() = 0 ;
	virtual double __cdecl indicatedBitrate() = 0 ;
	virtual __int64 __cdecl numberOfBytesTransferred() = 0 ;
	virtual long __cdecl numberOfDroppedVideoFrames() = 0 ;
	virtual unsigned long __cdecl numberOfSegmentsDownloaded() = 0 ;
	virtual unsigned long __cdecl numberOfServerAddressChanges() = 0 ;
	virtual long __cdecl numberOfStalls() = 0 ;
	virtual double __cdecl observedBitrate() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl playbackSessionID() = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl playbackStartDate() = 0 ;
	virtual double __cdecl playbackStartOffset() = 0 ;
	virtual double __cdecl segmentsDownloadedDuration() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl serverAddress() = 0 ;
};

class PASCALIMPLEMENTATION TMPMovieAccessLogEvent : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMovieAccessLogEventClass,_di_MPMovieAccessLogEvent>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMovieAccessLogEventClass,_di_MPMovieAccessLogEvent> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMovieAccessLogEvent(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMovieAccessLogEventClass,_di_MPMovieAccessLogEvent>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMovieAccessLogEvent() { }
	
};


__interface  INTERFACE_UUID("{DB4928FF-89C7-4FC1-8130-7E2BCE3E1D08}") MPMovieErrorLogClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{A30C424C-7B0A-448B-9DB5-332B8BDD9749}") MPMovieErrorLog  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl events() = 0 ;
	virtual Iosapi::Foundation::_di_NSData __cdecl extendedLogData() = 0 ;
	virtual unsigned long __cdecl extendedLogDataStringEncoding() = 0 ;
};

class PASCALIMPLEMENTATION TMPMovieErrorLog : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMovieErrorLogClass,_di_MPMovieErrorLog>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMovieErrorLogClass,_di_MPMovieErrorLog> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMovieErrorLog(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMovieErrorLogClass,_di_MPMovieErrorLog>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMovieErrorLog() { }
	
};


__interface  INTERFACE_UUID("{77BCCDB1-6A06-43F4-B57D-965346426888}") MPVolumeViewClass  : public Iosapi::Uikit::UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{F55C8146-7D21-4607-B6E1-75B0E40D8DA3}") MPVolumeView  : public Iosapi::Uikit::UIView 
{
	virtual void __cdecl setShowsRouteButton(bool showsRouteButton) = 0 ;
	virtual void __cdecl setShowsVolumeSlider(bool showsVolumeSlider) = 0 ;
	virtual bool __cdecl showsRouteButton() = 0 ;
	virtual bool __cdecl showsVolumeSlider() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::NSSize __cdecl sizeThatFits(Iosapi::Foundation::NSSize size) = 0 ;
};

class PASCALIMPLEMENTATION TMPVolumeView : public Macapi::Objectivec::TOCGenericImport__2<_di_MPVolumeViewClass,_di_MPVolumeView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPVolumeViewClass,_di_MPVolumeView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPVolumeView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPVolumeViewClass,_di_MPVolumeView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPVolumeView() { }
	
};


__interface  INTERFACE_UUID("{0AFA71E9-2FA5-44CF-A5A2-82F0A7DC7A52}") MPNowPlayingInfoCenterClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl defaultCenter() = 0 ;
};

__interface  INTERFACE_UUID("{250A112D-7C42-4FBC-8357-CA29F387DCBE}") MPNowPlayingInfoCenter  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl nowPlayingInfo() = 0 ;
	virtual void __cdecl setNowPlayingInfo(Iosapi::Foundation::_di_NSDictionary nowPlayingInfo) = 0 ;
};

class PASCALIMPLEMENTATION TMPNowPlayingInfoCenter : public Macapi::Objectivec::TOCGenericImport__2<_di_MPNowPlayingInfoCenterClass,_di_MPNowPlayingInfoCenter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPNowPlayingInfoCenterClass,_di_MPNowPlayingInfoCenter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPNowPlayingInfoCenter(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPNowPlayingInfoCenterClass,_di_MPNowPlayingInfoCenter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPNowPlayingInfoCenter() { }
	
};


__interface  INTERFACE_UUID("{E54D9B82-D7C5-4F8F-8C59-652BCF105601}") MPTimedMetadataClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{613C0A9B-09D6-4D19-9A71-E3DE91479DCF}") MPTimedMetadata  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl allMetadata() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl key() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl keyspace() = 0 ;
	virtual double __cdecl timestamp() = 0 ;
	virtual void * __cdecl value() = 0 ;
};

class PASCALIMPLEMENTATION TMPTimedMetadata : public Macapi::Objectivec::TOCGenericImport__2<_di_MPTimedMetadataClass,_di_MPTimedMetadata>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPTimedMetadataClass,_di_MPTimedMetadata> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPTimedMetadata(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPTimedMetadataClass,_di_MPTimedMetadata>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPTimedMetadata() { }
	
};


__interface  INTERFACE_UUID("{71287020-7E31-4C94-B1BB-302EC7BCA7BC}") MPMediaEntityClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual bool __cdecl canFilterByProperty(Iosapi::Foundation::_di_NSString property_) = 0 ;
};

__interface  INTERFACE_UUID("{DEAEFF9D-1AF5-4F2D-BAE7-B2A01A78C399}") MPMediaEntity  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl valueForProperty(Iosapi::Foundation::_di_NSString property_) = 0 ;
};

class PASCALIMPLEMENTATION TMPMediaEntity : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaEntityClass,_di_MPMediaEntity>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaEntityClass,_di_MPMediaEntity> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMediaEntity(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaEntityClass,_di_MPMediaEntity>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMediaEntity() { }
	
};


__interface  INTERFACE_UUID("{9385AEC7-2001-4FA2-8BEB-1D92D3D5740E}") MPMediaLibraryClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual long __cdecl authorizationStatus() = 0 ;
	virtual void * __cdecl defaultMediaLibrary() = 0 ;
	virtual void __cdecl requestAuthorization(TMediaPlayerHandler handler) = 0 ;
};

__interface  INTERFACE_UUID("{51AC6FEB-9559-4D57-BFE4-30E8E4FFFDF7}") MPMediaLibrary  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl beginGeneratingLibraryChangeNotifications() = 0 ;
	virtual void __cdecl endGeneratingLibraryChangeNotifications() = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl lastModifiedDate() = 0 ;
};

class PASCALIMPLEMENTATION TMPMediaLibrary : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaLibraryClass,_di_MPMediaLibrary>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaLibraryClass,_di_MPMediaLibrary> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMediaLibrary(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaLibraryClass,_di_MPMediaLibrary>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMediaLibrary() { }
	
};


__interface  INTERFACE_UUID("{E745306C-DC9B-4AA5-AE2B-C5206742828D}") MPMediaItemArtworkClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{2BE234AD-D57A-407D-9164-CDB2A9334E64}") MPMediaItemArtwork  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::NSRect __cdecl bounds() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl imageCropRect() = 0 ;
	virtual Iosapi::Uikit::_di_UIImage __cdecl imageWithSize(Iosapi::Foundation::NSSize size) = 0 ;
	virtual void * __cdecl initWithImage(Iosapi::Uikit::_di_UIImage image) = 0 ;
};

class PASCALIMPLEMENTATION TMPMediaItemArtwork : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaItemArtworkClass,_di_MPMediaItemArtwork>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaItemArtworkClass,_di_MPMediaItemArtwork> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMediaItemArtwork(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaItemArtworkClass,_di_MPMediaItemArtwork>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMediaItemArtwork() { }
	
};


__interface  INTERFACE_UUID("{B2146295-4920-470C-A78F-C00C83C9513F}") MPMediaPredicateClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{32F1A9FA-BDF8-4B39-AC51-09CC67988CFD}") MPMediaPredicate  : public Iosapi::Foundation::NSObject 
{
	
};

class PASCALIMPLEMENTATION TMPMediaPredicate : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaPredicateClass,_di_MPMediaPredicate>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaPredicateClass,_di_MPMediaPredicate> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMediaPredicate(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaPredicateClass,_di_MPMediaPredicate>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMediaPredicate() { }
	
};


__interface  INTERFACE_UUID("{C73CCF7B-0708-4C25-9587-F2BFF8159DDE}") MPMediaPropertyPredicateClass  : public MPMediaPredicateClass 
{
	virtual void * __cdecl predicateWithValue(void * value, Iosapi::Foundation::_di_NSString forProperty) = 0 /* overload */;
	virtual void * __cdecl predicateWithValue(void * value, Iosapi::Foundation::_di_NSString forProperty, long comparisonType) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{66CF22E1-05F7-4248-92ED-26A218C59EEA}") MPMediaPropertyPredicate  : public MPMediaPredicate 
{
	virtual long __cdecl comparisonType() = 0 ;
	virtual void * __cdecl value() = 0 ;
};

class PASCALIMPLEMENTATION TMPMediaPropertyPredicate : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaPropertyPredicateClass,_di_MPMediaPropertyPredicate>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaPropertyPredicateClass,_di_MPMediaPropertyPredicate> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMediaPropertyPredicate(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaPropertyPredicateClass,_di_MPMediaPropertyPredicate>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMediaPropertyPredicate() { }
	
};


__interface  INTERFACE_UUID("{B6C43755-9EC6-42BE-A0FC-53D17CA17F88}") MPMediaQuerySectionClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{82C4032F-7AD6-448D-A762-B8D28FA52CDA}") MPMediaQuerySection  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::NSRange __cdecl range() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
};

class PASCALIMPLEMENTATION TMPMediaQuerySection : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaQuerySectionClass,_di_MPMediaQuerySection>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaQuerySectionClass,_di_MPMediaQuerySection> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMediaQuerySection(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaQuerySectionClass,_di_MPMediaQuerySection>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMediaQuerySection() { }
	
};


__interface  INTERFACE_UUID("{7CB52822-F8F1-42ED-93E3-B452BBBC9E05}") MPMovieAccessLogClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{6CD7F56C-1EAE-4D13-8961-7602DAD90CEF}") MPMovieAccessLog  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl events() = 0 ;
	virtual Iosapi::Foundation::_di_NSData __cdecl extendedLogData() = 0 ;
	virtual unsigned long __cdecl extendedLogDataStringEncoding() = 0 ;
};

class PASCALIMPLEMENTATION TMPMovieAccessLog : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMovieAccessLogClass,_di_MPMovieAccessLog>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMovieAccessLogClass,_di_MPMovieAccessLog> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMovieAccessLog(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMovieAccessLogClass,_di_MPMovieAccessLog>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMovieAccessLog() { }
	
};


__interface  INTERFACE_UUID("{7AAF113C-8F84-4AE1-BD0F-E0325E3B5249}") MPMediaQueryClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl albumsQuery() = 0 ;
	virtual void * __cdecl artistsQuery() = 0 ;
	virtual void * __cdecl audiobooksQuery() = 0 ;
	virtual void * __cdecl compilationsQuery() = 0 ;
	virtual void * __cdecl composersQuery() = 0 ;
	virtual void * __cdecl genresQuery() = 0 ;
	virtual void * __cdecl playlistsQuery() = 0 ;
	virtual void * __cdecl podcastsQuery() = 0 ;
	virtual void * __cdecl songsQuery() = 0 ;
};

__interface  INTERFACE_UUID("{71EEF474-F196-4594-B03B-20737789786C}") MPMediaQuery  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl addFilterPredicate(_di_MPMediaPredicate predicate) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl collectionSections() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl collections() = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl filterPredicates() = 0 ;
	virtual long __cdecl groupingType() = 0 ;
	HIDESBASE virtual void * __cdecl init() = 0 ;
	virtual void * __cdecl initWithFilterPredicates(Iosapi::Foundation::_di_NSSet filterPredicates) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl itemSections() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl items() = 0 ;
	virtual void __cdecl removeFilterPredicate(_di_MPMediaPredicate predicate) = 0 ;
	virtual void __cdecl setFilterPredicates(Iosapi::Foundation::_di_NSSet filterPredicates) = 0 ;
	virtual void __cdecl setGroupingType(long groupingType) = 0 ;
};

class PASCALIMPLEMENTATION TMPMediaQuery : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaQueryClass,_di_MPMediaQuery>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaQueryClass,_di_MPMediaQuery> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMediaQuery(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaQueryClass,_di_MPMediaQuery>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMediaQuery() { }
	
};


__interface  INTERFACE_UUID("{B91ECF7B-4F97-47A7-BC18-AFFFAE69D74F}") MPMediaItemClass  : public MPMediaEntityClass 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl persistentIDPropertyForGroupingType(long groupingType) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl titlePropertyForGroupingType(long groupingType) = 0 ;
};

__interface  INTERFACE_UUID("{E931A458-F08D-4678-B52D-6EB0C5E4A2FB}") MPMediaItem  : public MPMediaEntity 
{
	
};

class PASCALIMPLEMENTATION TMPMediaItem : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaItemClass,_di_MPMediaItem>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaItemClass,_di_MPMediaItem> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMediaItem(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaItemClass,_di_MPMediaItem>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMediaItem() { }
	
};


__interface  INTERFACE_UUID("{140CAD86-4F5C-455B-9B6C-19DBB7D2B0F9}") MPMoviePlayerViewControllerClass  : public Iosapi::Uikit::UIViewControllerClass 
{
	
};

__interface  INTERFACE_UUID("{E81DC647-B84E-43DB-8BF9-4ABB1EBFBA65}") MPMoviePlayerViewController  : public Iosapi::Uikit::UIViewController 
{
	virtual void * __cdecl initWithContentURL(Iosapi::Foundation::_di_NSURL contentURL) = 0 ;
	virtual _di_MPMoviePlayerController __cdecl moviePlayer() = 0 ;
	HIDESBASE virtual bool __cdecl shouldAutorotateToInterfaceOrientation(long toInterfaceOrientation) = 0 ;
};

class PASCALIMPLEMENTATION TMPMoviePlayerViewController : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMoviePlayerViewControllerClass,_di_MPMoviePlayerViewController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMoviePlayerViewControllerClass,_di_MPMoviePlayerViewController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMoviePlayerViewController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMoviePlayerViewControllerClass,_di_MPMoviePlayerViewController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMoviePlayerViewController() { }
	
};


__interface  INTERFACE_UUID("{B72B8461-793C-4D8B-B82C-E7B2EBD60A62}") MPMediaPickerControllerClass  : public Iosapi::Uikit::UIViewControllerClass 
{
	
};

__interface  INTERFACE_UUID("{7B8C41D2-8F50-42BC-8AA5-84A4DD6CF886}") MPMediaPickerController  : public Iosapi::Uikit::UIViewController 
{
	virtual bool __cdecl allowsPickingMultipleItems() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	HIDESBASE virtual void * __cdecl init() = 0 ;
	virtual void * __cdecl initWithMediaTypes(long mediaTypes) = 0 ;
	virtual long __cdecl mediaTypes() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl prompt() = 0 ;
	virtual void __cdecl setAllowsPickingMultipleItems(bool allowsPickingMultipleItems) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setPrompt(Iosapi::Foundation::_di_NSString prompt) = 0 ;
};

class PASCALIMPLEMENTATION TMPMediaPickerController : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaPickerControllerClass,_di_MPMediaPickerController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaPickerControllerClass,_di_MPMediaPickerController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMediaPickerController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaPickerControllerClass,_di_MPMediaPickerController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMediaPickerController() { }
	
};


__interface  INTERFACE_UUID("{46C65217-9BDD-4C23-BC0F-AD9F6F99F8DE}") MPMediaItemCollectionClass  : public MPMediaEntityClass 
{
	virtual void * __cdecl collectionWithItems(Iosapi::Foundation::_di_NSArray items) = 0 ;
};

__interface  INTERFACE_UUID("{B35D202B-C3FD-4C11-A434-76D1C796BEA2}") MPMediaItemCollection  : public MPMediaEntity 
{
	virtual unsigned long __cdecl count() = 0 ;
	virtual void * __cdecl initWithItems(Iosapi::Foundation::_di_NSArray items) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl items() = 0 ;
	virtual long __cdecl mediaTypes() = 0 ;
	virtual _di_MPMediaItem __cdecl representativeItem() = 0 ;
};

class PASCALIMPLEMENTATION TMPMediaItemCollection : public Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaItemCollectionClass,_di_MPMediaItemCollection>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaItemCollectionClass,_di_MPMediaItemCollection> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMPMediaItemCollection(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MPMediaItemCollectionClass,_di_MPMediaItemCollection>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMPMediaItemCollection() { }
	
};


__interface  INTERFACE_UUID("{EB070067-8836-47FE-A13C-3E3779C2EA47}") MPMediaPickerControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl mediaPicker(_di_MPMediaPickerController mediaPicker, _di_MPMediaItemCollection didPickMediaItems) = 0 ;
	virtual void __cdecl mediaPickerDidCancel(_di_MPMediaPickerController mediaPicker) = 0 ;
};

__interface  INTERFACE_UUID("{1E3280B8-F3ED-41D3-8C7A-65C3A2DA1306}") MPMediaPlayback  : public System::IInterface 
{
	virtual void __cdecl beginSeekingBackward() = 0 ;
	virtual void __cdecl beginSeekingForward() = 0 ;
	virtual float __cdecl currentPlaybackRate() = 0 ;
	virtual double __cdecl currentPlaybackTime() = 0 ;
	virtual void __cdecl endSeeking() = 0 ;
	virtual bool __cdecl isPreparedToPlay() = 0 ;
	virtual void __cdecl pause() = 0 ;
	virtual void __cdecl play() = 0 ;
	virtual void __cdecl prepareToPlay() = 0 ;
	virtual void __cdecl setCurrentPlaybackRate(float currentPlaybackRate) = 0 ;
	virtual void __cdecl setCurrentPlaybackTime(double currentPlaybackTime) = 0 ;
	virtual void __cdecl stop() = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 MPMediaGroupingAlbum = System::Int8(0x1);
static constexpr System::Int8 MPMediaGroupingAlbumArtist = System::Int8(0x3);
static constexpr System::Int8 MPMediaGroupingArtist = System::Int8(0x2);
static constexpr System::Int8 MPMediaGroupingComposer = System::Int8(0x4);
static constexpr System::Int8 MPMediaGroupingGenre = System::Int8(0x5);
static constexpr System::Int8 MPMediaGroupingPlaylist = System::Int8(0x6);
static constexpr System::Int8 MPMediaGroupingPodcastTitle = System::Int8(0x7);
static constexpr System::Int8 MPMediaGroupingTitle = System::Int8(0x0);
static constexpr System::Int8 MPMediaPlaylistAttributeGenius = System::Int8(0x4);
static constexpr System::Int8 MPMediaPlaylistAttributeNone = System::Int8(0x0);
static constexpr System::Int8 MPMediaPlaylistAttributeOnTheGo = System::Int8(0x1);
static constexpr System::Int8 MPMediaPlaylistAttributeSmart = System::Int8(0x2);
static constexpr System::Int8 MPMediaPredicateComparisonContains = System::Int8(0x1);
static constexpr System::Int8 MPMediaPredicateComparisonEqualTo = System::Int8(0x0);
static constexpr System::Int8 MPMediaLibraryAuthorizationStatusNotDetermined = System::Int8(0x0);
static constexpr System::Int8 MPMediaLibraryAuthorizationStatusDenied = System::Int8(0x1);
static constexpr System::Int8 MPMediaLibraryAuthorizationStatusRestricted = System::Int8(0x2);
static constexpr System::Int8 MPMediaLibraryAuthorizationStatusAuthorized = System::Int8(0x3);
static constexpr System::Int8 MPMediaTypeAny = System::Int8(-1);
static constexpr System::Byte MPMediaTypeAnyAudio = System::Byte(0xff);
static constexpr System::Word MPMediaTypeAnyVideo = System::Word(0xff00);
static constexpr System::Int8 MPMediaTypeAudioBook = System::Int8(0x4);
static constexpr System::Int8 MPMediaTypeAudioITunesU = System::Int8(0x8);
static constexpr System::Word MPMediaTypeMovie = System::Word(0x100);
static constexpr System::Int8 MPMediaTypeMusic = System::Int8(0x1);
static constexpr System::Word MPMediaTypeMusicVideo = System::Word(0x800);
static constexpr System::Int8 MPMediaTypePodcast = System::Int8(0x2);
static constexpr System::Word MPMediaTypeTVShow = System::Word(0x200);
static constexpr System::Word MPMediaTypeVideoITunesU = System::Word(0x1000);
static constexpr System::Word MPMediaTypeVideoPodcast = System::Word(0x400);
static constexpr System::Int8 MPMovieControlModeDefault = System::Int8(0x0);
static constexpr System::Int8 MPMovieControlModeHidden = System::Int8(0x2);
static constexpr System::Int8 MPMovieControlModeVolumeOnly = System::Int8(0x1);
static constexpr System::Int8 MPMovieControlStyleDefault = System::Int8(0x1);
static constexpr System::Int8 MPMovieControlStyleEmbedded = System::Int8(0x1);
static constexpr System::Int8 MPMovieControlStyleFullscreen = System::Int8(0x2);
static constexpr System::Int8 MPMovieControlStyleNone = System::Int8(0x0);
static constexpr System::Int8 MPMovieFinishReasonPlaybackEnded = System::Int8(0x0);
static constexpr System::Int8 MPMovieFinishReasonPlaybackError = System::Int8(0x1);
static constexpr System::Int8 MPMovieFinishReasonUserExited = System::Int8(0x2);
static constexpr System::Int8 MPMovieLoadStatePlayable = System::Int8(0x1);
static constexpr System::Int8 MPMovieLoadStatePlaythroughOK = System::Int8(0x2);
static constexpr System::Int8 MPMovieLoadStateStalled = System::Int8(0x4);
static constexpr System::Int8 MPMovieLoadStateUnknown = System::Int8(0x0);
static constexpr System::Int8 MPMovieMediaTypeMaskAudio = System::Int8(0x2);
static constexpr System::Int8 MPMovieMediaTypeMaskNone = System::Int8(0x0);
static constexpr System::Int8 MPMovieMediaTypeMaskVideo = System::Int8(0x1);
static constexpr System::Int8 MPMoviePlaybackStateInterrupted = System::Int8(0x3);
static constexpr System::Int8 MPMoviePlaybackStatePaused = System::Int8(0x2);
static constexpr System::Int8 MPMoviePlaybackStatePlaying = System::Int8(0x1);
static constexpr System::Int8 MPMoviePlaybackStateSeekingBackward = System::Int8(0x5);
static constexpr System::Int8 MPMoviePlaybackStateSeekingForward = System::Int8(0x4);
static constexpr System::Int8 MPMoviePlaybackStateStopped = System::Int8(0x0);
static constexpr System::Int8 MPMovieRepeatModeNone = System::Int8(0x0);
static constexpr System::Int8 MPMovieRepeatModeOne = System::Int8(0x1);
static constexpr System::Int8 MPMovieScalingModeAspectFill = System::Int8(0x2);
static constexpr System::Int8 MPMovieScalingModeAspectFit = System::Int8(0x1);
static constexpr System::Int8 MPMovieScalingModeFill = System::Int8(0x3);
static constexpr System::Int8 MPMovieScalingModeNone = System::Int8(0x0);
static constexpr System::Int8 MPMovieSourceTypeFile = System::Int8(0x1);
static constexpr System::Int8 MPMovieSourceTypeStreaming = System::Int8(0x2);
static constexpr System::Int8 MPMovieSourceTypeUnknown = System::Int8(0x0);
static constexpr System::Int8 MPMovieTimeOptionExact = System::Int8(0x1);
static constexpr System::Int8 MPMovieTimeOptionNearestKeyFrame = System::Int8(0x0);
static constexpr System::Int8 MPMusicPlaybackStateInterrupted = System::Int8(0x3);
static constexpr System::Int8 MPMusicPlaybackStatePaused = System::Int8(0x2);
static constexpr System::Int8 MPMusicPlaybackStatePlaying = System::Int8(0x1);
static constexpr System::Int8 MPMusicPlaybackStateSeekingBackward = System::Int8(0x5);
static constexpr System::Int8 MPMusicPlaybackStateSeekingForward = System::Int8(0x4);
static constexpr System::Int8 MPMusicPlaybackStateStopped = System::Int8(0x0);
static constexpr System::Int8 MPMusicRepeatModeAll = System::Int8(0x3);
static constexpr System::Int8 MPMusicRepeatModeDefault = System::Int8(0x0);
static constexpr System::Int8 MPMusicRepeatModeNone = System::Int8(0x1);
static constexpr System::Int8 MPMusicRepeatModeOne = System::Int8(0x2);
static constexpr System::Int8 MPMusicShuffleModeAlbums = System::Int8(0x3);
static constexpr System::Int8 MPMusicShuffleModeDefault = System::Int8(0x0);
static constexpr System::Int8 MPMusicShuffleModeOff = System::Int8(0x1);
static constexpr System::Int8 MPMusicShuffleModeSongs = System::Int8(0x2);
#define libMediaPlayer u"/System/Library/Frameworks/MediaPlayer.framework/MediaPlay"\
	u"er"
extern "C" void __cdecl MPVolumeSettingsAlertHide(void);
extern "C" bool __cdecl MPVolumeSettingsAlertIsVisible(void);
extern "C" void __cdecl MPVolumeSettingsAlertShow(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MPMediaItemPropertyMediaType(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MPMediaItemPropertyTitle(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MPMediaItemPropertyAlbumTitle(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MPMediaItemPropertyArtist(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MPMediaItemPropertyGenre(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MPMediaItemPropertyComposer(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MPMediaItemPropertyPlaybackDuration(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MPMediaItemPropertyArtwork(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MPMediaItemPropertyPodcastTitle(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MPMediaPlaylistPropertyName(void);
}	/* namespace Mediaplayer */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_MEDIAPLAYER)
using namespace Iosapi::Mediaplayer;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_MediaplayerHPP
