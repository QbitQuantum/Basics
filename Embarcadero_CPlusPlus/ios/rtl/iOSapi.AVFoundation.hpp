// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.AVFoundation.pas' rev: 34.00 (iOS)

#ifndef Iosapi_AvfoundationHPP
#define Iosapi_AvfoundationHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <Macapi.Dispatch.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <iOSapi.CoreMedia.hpp>
#include <iOSapi.QuartzCore.hpp>
#include <iOSapi.CoreVideo.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Avfoundation
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE AVCaptureSessionClass;
typedef System::DelphiInterface<AVCaptureSessionClass> _di_AVCaptureSessionClass;
__interface DELPHIINTERFACE AVCaptureSession;
typedef System::DelphiInterface<AVCaptureSession> _di_AVCaptureSession;
class DELPHICLASS TAVCaptureSession;
__interface DELPHIINTERFACE AVCaptureOutputClass;
typedef System::DelphiInterface<AVCaptureOutputClass> _di_AVCaptureOutputClass;
__interface DELPHIINTERFACE AVCaptureOutput;
typedef System::DelphiInterface<AVCaptureOutput> _di_AVCaptureOutput;
class DELPHICLASS TAVCaptureOutput;
__interface DELPHIINTERFACE AVTimedMetadataGroupClass;
typedef System::DelphiInterface<AVTimedMetadataGroupClass> _di_AVTimedMetadataGroupClass;
__interface DELPHIINTERFACE AVTimedMetadataGroup;
typedef System::DelphiInterface<AVTimedMetadataGroup> _di_AVTimedMetadataGroup;
class DELPHICLASS TAVTimedMetadataGroup;
__interface DELPHIINTERFACE AVSynchronizedLayerClass;
typedef System::DelphiInterface<AVSynchronizedLayerClass> _di_AVSynchronizedLayerClass;
__interface DELPHIINTERFACE AVSynchronizedLayer;
typedef System::DelphiInterface<AVSynchronizedLayer> _di_AVSynchronizedLayer;
class DELPHICLASS TAVSynchronizedLayer;
__interface DELPHIINTERFACE AVCaptureVideoPreviewLayerClass;
typedef System::DelphiInterface<AVCaptureVideoPreviewLayerClass> _di_AVCaptureVideoPreviewLayerClass;
__interface DELPHIINTERFACE AVCaptureVideoPreviewLayer;
typedef System::DelphiInterface<AVCaptureVideoPreviewLayer> _di_AVCaptureVideoPreviewLayer;
class DELPHICLASS TAVCaptureVideoPreviewLayer;
__interface DELPHIINTERFACE AVVideoCompositionCoreAnimationToolClass;
typedef System::DelphiInterface<AVVideoCompositionCoreAnimationToolClass> _di_AVVideoCompositionCoreAnimationToolClass;
__interface DELPHIINTERFACE AVVideoCompositionCoreAnimationTool;
typedef System::DelphiInterface<AVVideoCompositionCoreAnimationTool> _di_AVVideoCompositionCoreAnimationTool;
class DELPHICLASS TAVVideoCompositionCoreAnimationTool;
__interface DELPHIINTERFACE AVVideoCompositionInstructionClass;
typedef System::DelphiInterface<AVVideoCompositionInstructionClass> _di_AVVideoCompositionInstructionClass;
__interface DELPHIINTERFACE AVVideoCompositionInstruction;
typedef System::DelphiInterface<AVVideoCompositionInstruction> _di_AVVideoCompositionInstruction;
class DELPHICLASS TAVVideoCompositionInstruction;
__interface DELPHIINTERFACE AVCaptureInputClass;
typedef System::DelphiInterface<AVCaptureInputClass> _di_AVCaptureInputClass;
__interface DELPHIINTERFACE AVCaptureInput;
typedef System::DelphiInterface<AVCaptureInput> _di_AVCaptureInput;
class DELPHICLASS TAVCaptureInput;
__interface DELPHIINTERFACE AVVideoCompositionClass;
typedef System::DelphiInterface<AVVideoCompositionClass> _di_AVVideoCompositionClass;
__interface DELPHIINTERFACE AVVideoComposition;
typedef System::DelphiInterface<AVVideoComposition> _di_AVVideoComposition;
class DELPHICLASS TAVVideoComposition;
__interface DELPHIINTERFACE AVCaptureInputPortClass;
typedef System::DelphiInterface<AVCaptureInputPortClass> _di_AVCaptureInputPortClass;
__interface DELPHIINTERFACE AVCaptureInputPort;
typedef System::DelphiInterface<AVCaptureInputPort> _di_AVCaptureInputPort;
class DELPHICLASS TAVCaptureInputPort;
__interface DELPHIINTERFACE AVPlayerLayerClass;
typedef System::DelphiInterface<AVPlayerLayerClass> _di_AVPlayerLayerClass;
__interface DELPHIINTERFACE AVPlayerLayer;
typedef System::DelphiInterface<AVPlayerLayer> _di_AVPlayerLayer;
class DELPHICLASS TAVPlayerLayer;
__interface DELPHIINTERFACE AVPlayerItemAccessLogEventClass;
typedef System::DelphiInterface<AVPlayerItemAccessLogEventClass> _di_AVPlayerItemAccessLogEventClass;
__interface DELPHIINTERFACE AVPlayerItemAccessLogEvent;
typedef System::DelphiInterface<AVPlayerItemAccessLogEvent> _di_AVPlayerItemAccessLogEvent;
class DELPHICLASS TAVPlayerItemAccessLogEvent;
__interface DELPHIINTERFACE AVPlayerItemErrorLogClass;
typedef System::DelphiInterface<AVPlayerItemErrorLogClass> _di_AVPlayerItemErrorLogClass;
__interface DELPHIINTERFACE AVPlayerItemErrorLog;
typedef System::DelphiInterface<AVPlayerItemErrorLog> _di_AVPlayerItemErrorLog;
class DELPHICLASS TAVPlayerItemErrorLog;
__interface DELPHIINTERFACE AVPlayerItemAccessLogClass;
typedef System::DelphiInterface<AVPlayerItemAccessLogClass> _di_AVPlayerItemAccessLogClass;
__interface DELPHIINTERFACE AVPlayerItemAccessLog;
typedef System::DelphiInterface<AVPlayerItemAccessLog> _di_AVPlayerItemAccessLog;
class DELPHICLASS TAVPlayerItemAccessLog;
__interface DELPHIINTERFACE AVPlayerMediaSelectionCriteriaClass;
typedef System::DelphiInterface<AVPlayerMediaSelectionCriteriaClass> _di_AVPlayerMediaSelectionCriteriaClass;
__interface DELPHIINTERFACE AVPlayerMediaSelectionCriteria;
typedef System::DelphiInterface<AVPlayerMediaSelectionCriteria> _di_AVPlayerMediaSelectionCriteria;
class DELPHICLASS TAVPlayerMediaSelectionCriteria;
__interface DELPHIINTERFACE AVPlayerClass;
typedef System::DelphiInterface<AVPlayerClass> _di_AVPlayerClass;
__interface DELPHIINTERFACE AVPlayer;
typedef System::DelphiInterface<AVPlayer> _di_AVPlayer;
class DELPHICLASS TAVPlayer;
__interface DELPHIINTERFACE AVQueuePlayerClass;
typedef System::DelphiInterface<AVQueuePlayerClass> _di_AVQueuePlayerClass;
__interface DELPHIINTERFACE AVQueuePlayer;
typedef System::DelphiInterface<AVQueuePlayer> _di_AVQueuePlayer;
class DELPHICLASS TAVQueuePlayer;
__interface DELPHIINTERFACE AVPlayerItemOutputClass;
typedef System::DelphiInterface<AVPlayerItemOutputClass> _di_AVPlayerItemOutputClass;
__interface DELPHIINTERFACE AVPlayerItemOutput;
typedef System::DelphiInterface<AVPlayerItemOutput> _di_AVPlayerItemOutput;
class DELPHICLASS TAVPlayerItemOutput;
__interface DELPHIINTERFACE AVPlayerItemErrorLogEventClass;
typedef System::DelphiInterface<AVPlayerItemErrorLogEventClass> _di_AVPlayerItemErrorLogEventClass;
__interface DELPHIINTERFACE AVPlayerItemErrorLogEvent;
typedef System::DelphiInterface<AVPlayerItemErrorLogEvent> _di_AVPlayerItemErrorLogEvent;
class DELPHICLASS TAVPlayerItemErrorLogEvent;
__interface DELPHIINTERFACE AVPlayerItemVideoOutputClass;
typedef System::DelphiInterface<AVPlayerItemVideoOutputClass> _di_AVPlayerItemVideoOutputClass;
__interface DELPHIINTERFACE AVPlayerItemVideoOutput;
typedef System::DelphiInterface<AVPlayerItemVideoOutput> _di_AVPlayerItemVideoOutput;
class DELPHICLASS TAVPlayerItemVideoOutput;
__interface DELPHIINTERFACE AVPlayerItemLegibleOutputClass;
typedef System::DelphiInterface<AVPlayerItemLegibleOutputClass> _di_AVPlayerItemLegibleOutputClass;
__interface DELPHIINTERFACE AVPlayerItemLegibleOutput;
typedef System::DelphiInterface<AVPlayerItemLegibleOutput> _di_AVPlayerItemLegibleOutput;
class DELPHICLASS TAVPlayerItemLegibleOutput;
__interface DELPHIINTERFACE AVPlayerItemMetadataOutputClass;
typedef System::DelphiInterface<AVPlayerItemMetadataOutputClass> _di_AVPlayerItemMetadataOutputClass;
__interface DELPHIINTERFACE AVPlayerItemMetadataOutput;
typedef System::DelphiInterface<AVPlayerItemMetadataOutput> _di_AVPlayerItemMetadataOutput;
class DELPHICLASS TAVPlayerItemMetadataOutput;
__interface DELPHIINTERFACE AVPlayerItemClass;
typedef System::DelphiInterface<AVPlayerItemClass> _di_AVPlayerItemClass;
__interface DELPHIINTERFACE AVPlayerItem;
typedef System::DelphiInterface<AVPlayerItem> _di_AVPlayerItem;
class DELPHICLASS TAVPlayerItem;
__interface DELPHIINTERFACE AVMediaSelectionOptionClass;
typedef System::DelphiInterface<AVMediaSelectionOptionClass> _di_AVMediaSelectionOptionClass;
__interface DELPHIINTERFACE AVMediaSelectionOption;
typedef System::DelphiInterface<AVMediaSelectionOption> _di_AVMediaSelectionOption;
class DELPHICLASS TAVMediaSelectionOption;
__interface DELPHIINTERFACE AVMediaSelectionGroupClass;
typedef System::DelphiInterface<AVMediaSelectionGroupClass> _di_AVMediaSelectionGroupClass;
__interface DELPHIINTERFACE AVMediaSelectionGroup;
typedef System::DelphiInterface<AVMediaSelectionGroup> _di_AVMediaSelectionGroup;
class DELPHICLASS TAVMediaSelectionGroup;
__interface DELPHIINTERFACE AVMetadataItemClass;
typedef System::DelphiInterface<AVMetadataItemClass> _di_AVMetadataItemClass;
__interface DELPHIINTERFACE AVMetadataItem;
typedef System::DelphiInterface<AVMetadataItem> _di_AVMetadataItem;
class DELPHICLASS TAVMetadataItem;
__interface DELPHIINTERFACE AVPlayerItemTrackClass;
typedef System::DelphiInterface<AVPlayerItemTrackClass> _di_AVPlayerItemTrackClass;
__interface DELPHIINTERFACE AVPlayerItemTrack;
typedef System::DelphiInterface<AVPlayerItemTrack> _di_AVPlayerItemTrack;
class DELPHICLASS TAVPlayerItemTrack;
__interface DELPHIINTERFACE AVCaptureDeviceClass;
typedef System::DelphiInterface<AVCaptureDeviceClass> _di_AVCaptureDeviceClass;
__interface DELPHIINTERFACE AVCaptureDevice;
typedef System::DelphiInterface<AVCaptureDevice> _di_AVCaptureDevice;
class DELPHICLASS TAVCaptureDevice;
__interface DELPHIINTERFACE AVFrameRateRangeClass;
typedef System::DelphiInterface<AVFrameRateRangeClass> _di_AVFrameRateRangeClass;
__interface DELPHIINTERFACE AVFrameRateRange;
typedef System::DelphiInterface<AVFrameRateRange> _di_AVFrameRateRange;
class DELPHICLASS TAVFrameRateRange;
__interface DELPHIINTERFACE AVAssetTrackClass;
typedef System::DelphiInterface<AVAssetTrackClass> _di_AVAssetTrackClass;
__interface DELPHIINTERFACE AVAssetTrack;
typedef System::DelphiInterface<AVAssetTrack> _di_AVAssetTrack;
class DELPHICLASS TAVAssetTrack;
__interface DELPHIINTERFACE AVAssetTrackSegmentClass;
typedef System::DelphiInterface<AVAssetTrackSegmentClass> _di_AVAssetTrackSegmentClass;
__interface DELPHIINTERFACE AVAssetTrackSegment;
typedef System::DelphiInterface<AVAssetTrackSegment> _di_AVAssetTrackSegment;
class DELPHICLASS TAVAssetTrackSegment;
__interface DELPHIINTERFACE AVAssetClass;
typedef System::DelphiInterface<AVAssetClass> _di_AVAssetClass;
__interface DELPHIINTERFACE AVAsset;
typedef System::DelphiInterface<AVAsset> _di_AVAsset;
class DELPHICLASS TAVAsset;
__interface DELPHIINTERFACE AVAssetWriterClass;
typedef System::DelphiInterface<AVAssetWriterClass> _di_AVAssetWriterClass;
__interface DELPHIINTERFACE AVAssetWriter;
typedef System::DelphiInterface<AVAssetWriter> _di_AVAssetWriter;
class DELPHICLASS TAVAssetWriter;
__interface DELPHIINTERFACE AVAssetImageGeneratorClass;
typedef System::DelphiInterface<AVAssetImageGeneratorClass> _di_AVAssetImageGeneratorClass;
__interface DELPHIINTERFACE AVAssetImageGenerator;
typedef System::DelphiInterface<AVAssetImageGenerator> _di_AVAssetImageGenerator;
class DELPHICLASS TAVAssetImageGenerator;
__interface DELPHIINTERFACE AVAssetExportSessionClass;
typedef System::DelphiInterface<AVAssetExportSessionClass> _di_AVAssetExportSessionClass;
__interface DELPHIINTERFACE AVAssetExportSession;
typedef System::DelphiInterface<AVAssetExportSession> _di_AVAssetExportSession;
class DELPHICLASS TAVAssetExportSession;
__interface DELPHIINTERFACE AVAssetReaderClass;
typedef System::DelphiInterface<AVAssetReaderClass> _di_AVAssetReaderClass;
__interface DELPHIINTERFACE AVAssetReader;
typedef System::DelphiInterface<AVAssetReader> _di_AVAssetReader;
class DELPHICLASS TAVAssetReader;
__interface DELPHIINTERFACE AVAssetReaderOutputClass;
typedef System::DelphiInterface<AVAssetReaderOutputClass> _di_AVAssetReaderOutputClass;
__interface DELPHIINTERFACE AVAssetReaderOutput;
typedef System::DelphiInterface<AVAssetReaderOutput> _di_AVAssetReaderOutput;
class DELPHICLASS TAVAssetReaderOutput;
__interface DELPHIINTERFACE AVAudioSessionClass;
typedef System::DelphiInterface<AVAudioSessionClass> _di_AVAudioSessionClass;
__interface DELPHIINTERFACE AVAudioSession;
typedef System::DelphiInterface<AVAudioSession> _di_AVAudioSession;
class DELPHICLASS TAVAudioSession;
__interface DELPHIINTERFACE AVCaptureDeviceFormatClass;
typedef System::DelphiInterface<AVCaptureDeviceFormatClass> _di_AVCaptureDeviceFormatClass;
__interface DELPHIINTERFACE AVCaptureDeviceFormat;
typedef System::DelphiInterface<AVCaptureDeviceFormat> _di_AVCaptureDeviceFormat;
class DELPHICLASS TAVCaptureDeviceFormat;
__interface DELPHIINTERFACE AVAudioRecorderClass;
typedef System::DelphiInterface<AVAudioRecorderClass> _di_AVAudioRecorderClass;
__interface DELPHIINTERFACE AVAudioRecorder;
typedef System::DelphiInterface<AVAudioRecorder> _di_AVAudioRecorder;
class DELPHICLASS TAVAudioRecorder;
__interface DELPHIINTERFACE AVCaptureAudioChannelClass;
typedef System::DelphiInterface<AVCaptureAudioChannelClass> _di_AVCaptureAudioChannelClass;
__interface DELPHIINTERFACE AVCaptureAudioChannel;
typedef System::DelphiInterface<AVCaptureAudioChannel> _di_AVCaptureAudioChannel;
class DELPHICLASS TAVCaptureAudioChannel;
__interface DELPHIINTERFACE AVCaptureConnectionClass;
typedef System::DelphiInterface<AVCaptureConnectionClass> _di_AVCaptureConnectionClass;
__interface DELPHIINTERFACE AVCaptureConnection;
typedef System::DelphiInterface<AVCaptureConnection> _di_AVCaptureConnection;
class DELPHICLASS TAVCaptureConnection;
__interface DELPHIINTERFACE AVVideoCompositionLayerInstructionClass;
typedef System::DelphiInterface<AVVideoCompositionLayerInstructionClass> _di_AVVideoCompositionLayerInstructionClass;
__interface DELPHIINTERFACE AVVideoCompositionLayerInstruction;
typedef System::DelphiInterface<AVVideoCompositionLayerInstruction> _di_AVVideoCompositionLayerInstruction;
class DELPHICLASS TAVVideoCompositionLayerInstruction;
__interface DELPHIINTERFACE AVAudioPlayerClass;
typedef System::DelphiInterface<AVAudioPlayerClass> _di_AVAudioPlayerClass;
__interface DELPHIINTERFACE AVAudioPlayer;
typedef System::DelphiInterface<AVAudioPlayer> _di_AVAudioPlayer;
class DELPHICLASS TAVAudioPlayer;
__interface DELPHIINTERFACE AVAssetWriterInputPixelBufferAdaptorClass;
typedef System::DelphiInterface<AVAssetWriterInputPixelBufferAdaptorClass> _di_AVAssetWriterInputPixelBufferAdaptorClass;
__interface DELPHIINTERFACE AVAssetWriterInputPixelBufferAdaptor;
typedef System::DelphiInterface<AVAssetWriterInputPixelBufferAdaptor> _di_AVAssetWriterInputPixelBufferAdaptor;
class DELPHICLASS TAVAssetWriterInputPixelBufferAdaptor;
__interface DELPHIINTERFACE AVAssetWriterInputClass;
typedef System::DelphiInterface<AVAssetWriterInputClass> _di_AVAssetWriterInputClass;
__interface DELPHIINTERFACE AVAssetWriterInput;
typedef System::DelphiInterface<AVAssetWriterInput> _di_AVAssetWriterInput;
class DELPHICLASS TAVAssetWriterInput;
__interface DELPHIINTERFACE AVAudioMixClass;
typedef System::DelphiInterface<AVAudioMixClass> _di_AVAudioMixClass;
__interface DELPHIINTERFACE AVAudioMix;
typedef System::DelphiInterface<AVAudioMix> _di_AVAudioMix;
class DELPHICLASS TAVAudioMix;
__interface DELPHIINTERFACE AVAudioMixInputParametersClass;
typedef System::DelphiInterface<AVAudioMixInputParametersClass> _di_AVAudioMixInputParametersClass;
__interface DELPHIINTERFACE AVAudioMixInputParameters;
typedef System::DelphiInterface<AVAudioMixInputParameters> _di_AVAudioMixInputParameters;
class DELPHICLASS TAVAudioMixInputParameters;
__interface DELPHIINTERFACE AVMutableVideoCompositionLayerInstructionClass;
typedef System::DelphiInterface<AVMutableVideoCompositionLayerInstructionClass> _di_AVMutableVideoCompositionLayerInstructionClass;
__interface DELPHIINTERFACE AVMutableVideoCompositionLayerInstruction;
typedef System::DelphiInterface<AVMutableVideoCompositionLayerInstruction> _di_AVMutableVideoCompositionLayerInstruction;
class DELPHICLASS TAVMutableVideoCompositionLayerInstruction;
__interface DELPHIINTERFACE AVURLAssetClass;
typedef System::DelphiInterface<AVURLAssetClass> _di_AVURLAssetClass;
__interface DELPHIINTERFACE AVURLAsset;
typedef System::DelphiInterface<AVURLAsset> _di_AVURLAsset;
class DELPHICLASS TAVURLAsset;
__interface DELPHIINTERFACE AVCaptureStillImageOutputClass;
typedef System::DelphiInterface<AVCaptureStillImageOutputClass> _di_AVCaptureStillImageOutputClass;
__interface DELPHIINTERFACE AVCaptureStillImageOutput;
typedef System::DelphiInterface<AVCaptureStillImageOutput> _di_AVCaptureStillImageOutput;
class DELPHICLASS TAVCaptureStillImageOutput;
__interface DELPHIINTERFACE AVCaptureFileOutputClass;
typedef System::DelphiInterface<AVCaptureFileOutputClass> _di_AVCaptureFileOutputClass;
__interface DELPHIINTERFACE AVCaptureFileOutput;
typedef System::DelphiInterface<AVCaptureFileOutput> _di_AVCaptureFileOutput;
class DELPHICLASS TAVCaptureFileOutput;
__interface DELPHIINTERFACE AVCaptureFileOutputRecordingDelegate;
typedef System::DelphiInterface<AVCaptureFileOutputRecordingDelegate> _di_AVCaptureFileOutputRecordingDelegate;
__interface DELPHIINTERFACE AVCompositionClass;
typedef System::DelphiInterface<AVCompositionClass> _di_AVCompositionClass;
__interface DELPHIINTERFACE AVComposition;
typedef System::DelphiInterface<AVComposition> _di_AVComposition;
class DELPHICLASS TAVComposition;
__interface DELPHIINTERFACE AVCaptureVideoDataOutputClass;
typedef System::DelphiInterface<AVCaptureVideoDataOutputClass> _di_AVCaptureVideoDataOutputClass;
__interface DELPHIINTERFACE AVCaptureVideoDataOutput;
typedef System::DelphiInterface<AVCaptureVideoDataOutput> _di_AVCaptureVideoDataOutput;
class DELPHICLASS TAVCaptureVideoDataOutput;
__interface DELPHIINTERFACE AVCaptureVideoDataOutputSampleBufferDelegate;
typedef System::DelphiInterface<AVCaptureVideoDataOutputSampleBufferDelegate> _di_AVCaptureVideoDataOutputSampleBufferDelegate;
__interface DELPHIINTERFACE AVCaptureDeviceInputClass;
typedef System::DelphiInterface<AVCaptureDeviceInputClass> _di_AVCaptureDeviceInputClass;
__interface DELPHIINTERFACE AVCaptureDeviceInput;
typedef System::DelphiInterface<AVCaptureDeviceInput> _di_AVCaptureDeviceInput;
class DELPHICLASS TAVCaptureDeviceInput;
__interface DELPHIINTERFACE AVAssetReaderTrackOutputClass;
typedef System::DelphiInterface<AVAssetReaderTrackOutputClass> _di_AVAssetReaderTrackOutputClass;
__interface DELPHIINTERFACE AVAssetReaderTrackOutput;
typedef System::DelphiInterface<AVAssetReaderTrackOutput> _di_AVAssetReaderTrackOutput;
class DELPHICLASS TAVAssetReaderTrackOutput;
__interface DELPHIINTERFACE AVAssetReaderAudioMixOutputClass;
typedef System::DelphiInterface<AVAssetReaderAudioMixOutputClass> _di_AVAssetReaderAudioMixOutputClass;
__interface DELPHIINTERFACE AVAssetReaderAudioMixOutput;
typedef System::DelphiInterface<AVAssetReaderAudioMixOutput> _di_AVAssetReaderAudioMixOutput;
class DELPHICLASS TAVAssetReaderAudioMixOutput;
__interface DELPHIINTERFACE AVCaptureAudioDataOutputClass;
typedef System::DelphiInterface<AVCaptureAudioDataOutputClass> _di_AVCaptureAudioDataOutputClass;
__interface DELPHIINTERFACE AVCaptureAudioDataOutput;
typedef System::DelphiInterface<AVCaptureAudioDataOutput> _di_AVCaptureAudioDataOutput;
class DELPHICLASS TAVCaptureAudioDataOutput;
__interface DELPHIINTERFACE AVAssetReaderVideoCompositionOutputClass;
typedef System::DelphiInterface<AVAssetReaderVideoCompositionOutputClass> _di_AVAssetReaderVideoCompositionOutputClass;
__interface DELPHIINTERFACE AVAssetReaderVideoCompositionOutput;
typedef System::DelphiInterface<AVAssetReaderVideoCompositionOutput> _di_AVAssetReaderVideoCompositionOutput;
class DELPHICLASS TAVAssetReaderVideoCompositionOutput;
__interface DELPHIINTERFACE AVCompositionTrackClass;
typedef System::DelphiInterface<AVCompositionTrackClass> _di_AVCompositionTrackClass;
__interface DELPHIINTERFACE AVCompositionTrack;
typedef System::DelphiInterface<AVCompositionTrack> _di_AVCompositionTrack;
class DELPHICLASS TAVCompositionTrack;
__interface DELPHIINTERFACE AVMutableVideoCompositionClass;
typedef System::DelphiInterface<AVMutableVideoCompositionClass> _di_AVMutableVideoCompositionClass;
__interface DELPHIINTERFACE AVMutableVideoComposition;
typedef System::DelphiInterface<AVMutableVideoComposition> _di_AVMutableVideoComposition;
class DELPHICLASS TAVMutableVideoComposition;
__interface DELPHIINTERFACE AVMutableTimedMetadataGroupClass;
typedef System::DelphiInterface<AVMutableTimedMetadataGroupClass> _di_AVMutableTimedMetadataGroupClass;
__interface DELPHIINTERFACE AVMutableTimedMetadataGroup;
typedef System::DelphiInterface<AVMutableTimedMetadataGroup> _di_AVMutableTimedMetadataGroup;
class DELPHICLASS TAVMutableTimedMetadataGroup;
__interface DELPHIINTERFACE AVMutableMetadataItemClass;
typedef System::DelphiInterface<AVMutableMetadataItemClass> _di_AVMutableMetadataItemClass;
__interface DELPHIINTERFACE AVMutableMetadataItem;
typedef System::DelphiInterface<AVMutableMetadataItem> _di_AVMutableMetadataItem;
class DELPHICLASS TAVMutableMetadataItem;
__interface DELPHIINTERFACE AVMutableVideoCompositionInstructionClass;
typedef System::DelphiInterface<AVMutableVideoCompositionInstructionClass> _di_AVMutableVideoCompositionInstructionClass;
__interface DELPHIINTERFACE AVMutableVideoCompositionInstruction;
typedef System::DelphiInterface<AVMutableVideoCompositionInstruction> _di_AVMutableVideoCompositionInstruction;
class DELPHICLASS TAVMutableVideoCompositionInstruction;
__interface DELPHIINTERFACE AVCompositionTrackSegmentClass;
typedef System::DelphiInterface<AVCompositionTrackSegmentClass> _di_AVCompositionTrackSegmentClass;
__interface DELPHIINTERFACE AVCompositionTrackSegment;
typedef System::DelphiInterface<AVCompositionTrackSegment> _di_AVCompositionTrackSegment;
class DELPHICLASS TAVCompositionTrackSegment;
__interface DELPHIINTERFACE AVMutableAudioMixClass;
typedef System::DelphiInterface<AVMutableAudioMixClass> _di_AVMutableAudioMixClass;
__interface DELPHIINTERFACE AVMutableAudioMix;
typedef System::DelphiInterface<AVMutableAudioMix> _di_AVMutableAudioMix;
class DELPHICLASS TAVMutableAudioMix;
__interface DELPHIINTERFACE AVMutableAudioMixInputParametersClass;
typedef System::DelphiInterface<AVMutableAudioMixInputParametersClass> _di_AVMutableAudioMixInputParametersClass;
__interface DELPHIINTERFACE AVMutableAudioMixInputParameters;
typedef System::DelphiInterface<AVMutableAudioMixInputParameters> _di_AVMutableAudioMixInputParameters;
class DELPHICLASS TAVMutableAudioMixInputParameters;
__interface DELPHIINTERFACE AVCaptureMovieFileOutputClass;
typedef System::DelphiInterface<AVCaptureMovieFileOutputClass> _di_AVCaptureMovieFileOutputClass;
__interface DELPHIINTERFACE AVCaptureMovieFileOutput;
typedef System::DelphiInterface<AVCaptureMovieFileOutput> _di_AVCaptureMovieFileOutput;
class DELPHICLASS TAVCaptureMovieFileOutput;
__interface DELPHIINTERFACE AVMutableCompositionClass;
typedef System::DelphiInterface<AVMutableCompositionClass> _di_AVMutableCompositionClass;
__interface DELPHIINTERFACE AVMutableComposition;
typedef System::DelphiInterface<AVMutableComposition> _di_AVMutableComposition;
class DELPHICLASS TAVMutableComposition;
__interface DELPHIINTERFACE AVMutableCompositionTrackClass;
typedef System::DelphiInterface<AVMutableCompositionTrackClass> _di_AVMutableCompositionTrackClass;
__interface DELPHIINTERFACE AVMutableCompositionTrack;
typedef System::DelphiInterface<AVMutableCompositionTrack> _di_AVMutableCompositionTrack;
class DELPHICLASS TAVMutableCompositionTrack;
//-- type declarations -------------------------------------------------------
typedef long AVAssetExportSessionStatus;

typedef long AVAssetReaderStatus;

typedef unsigned long AVAssetReferenceRestrictions;

typedef long AVAssetWriterStatus;

typedef long AVCaptureDevicePosition;

typedef long AVCaptureExposureMode;

typedef long AVCaptureFocusMode;

typedef long AVCaptureFlashMode;

typedef long AVCaptureTorchMode;

typedef long AVCaptureVideoOrientation;

typedef long AVCaptureWhiteBalanceMode;

typedef long AVKeyValueStatus;

typedef unsigned long AVLoadingKeyStatus;

typedef long AVPlayerActionAtItemEnd;

typedef long AVPlayerItemStatus;

typedef long AVPlayerStatus;

typedef Iosapi::Foundation::_di_NSString AVMediaType;

typedef Iosapi::Foundation::_di_NSString AVCaptureDeviceType;

typedef long AVAuthorizationStatus;

typedef void __fastcall (__closure *TAVFoundationCompletionHandler)(void);

typedef void __fastcall (__closure *TAVFoundationCompletionHandler1)(bool param1);

typedef void __fastcall (__closure *TAVFoundationHandler)(Iosapi::Foundation::_di_NSArray param1);

typedef void __fastcall (__closure *TAVFoundationCompletionHandler2)(const Iosapi::Coremedia::CMTime &param1);

typedef void __fastcall (__closure *TAVFoundationCompletionHandler3)(bool granted);

__interface  INTERFACE_UUID("{A47E0D5A-2C30-49E8-98E1-F49B16BB495A}") AVCaptureSessionClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{F47F9902-C0D4-41B7-92DE-A1F358650199}") AVCaptureSession  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl addInput(_di_AVCaptureInput input) = 0 ;
	virtual void __cdecl addOutput(_di_AVCaptureOutput output) = 0 ;
	virtual void __cdecl beginConfiguration() = 0 ;
	virtual bool __cdecl canAddInput(_di_AVCaptureInput input) = 0 ;
	virtual bool __cdecl canAddOutput(_di_AVCaptureOutput output) = 0 ;
	virtual bool __cdecl canSetSessionPreset(Iosapi::Foundation::_di_NSString preset) = 0 ;
	virtual void __cdecl commitConfiguration() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl inputs() = 0 ;
	virtual bool __cdecl isInterrupted() = 0 ;
	virtual bool __cdecl isRunning() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl outputs() = 0 ;
	virtual void __cdecl removeInput(_di_AVCaptureInput input) = 0 ;
	virtual void __cdecl removeOutput(_di_AVCaptureOutput output) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl sessionPreset() = 0 ;
	virtual void __cdecl setSessionPreset(Iosapi::Foundation::_di_NSString sessionPreset) = 0 ;
	virtual void __cdecl startRunning() = 0 ;
	virtual void __cdecl stopRunning() = 0 ;
};

class PASCALIMPLEMENTATION TAVCaptureSession : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureSessionClass,_di_AVCaptureSession>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureSessionClass,_di_AVCaptureSession> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCaptureSession(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureSessionClass,_di_AVCaptureSession>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCaptureSession() { }
	
};


__interface  INTERFACE_UUID("{321DC7CF-8DF4-402D-B789-B59B0E6E91CD}") AVCaptureOutputClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{89F37BE5-4C30-46C7-85A7-B1445FAA01D7}") AVCaptureOutput  : public Iosapi::Foundation::NSObject 
{
	virtual _di_AVCaptureConnection __cdecl connectionWithMediaType(Iosapi::Foundation::_di_NSString mediaType) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl connections() = 0 ;
};

class PASCALIMPLEMENTATION TAVCaptureOutput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureOutputClass,_di_AVCaptureOutput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureOutputClass,_di_AVCaptureOutput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCaptureOutput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureOutputClass,_di_AVCaptureOutput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCaptureOutput() { }
	
};


__interface  INTERFACE_UUID("{481DE574-FF52-4FC8-BBCE-CC924F8AEF0B}") AVTimedMetadataGroupClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{1E7F7812-E586-4DC5-8B19-A44707505E75}") AVTimedMetadataGroup  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithItems(Iosapi::Foundation::_di_NSArray items, Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl items() = 0 ;
	virtual Iosapi::Coremedia::CMTimeRange __cdecl timeRange() = 0 ;
};

class PASCALIMPLEMENTATION TAVTimedMetadataGroup : public Macapi::Objectivec::TOCGenericImport__2<_di_AVTimedMetadataGroupClass,_di_AVTimedMetadataGroup>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVTimedMetadataGroupClass,_di_AVTimedMetadataGroup> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVTimedMetadataGroup(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVTimedMetadataGroupClass,_di_AVTimedMetadataGroup>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVTimedMetadataGroup() { }
	
};


__interface  INTERFACE_UUID("{7108227E-6136-44AD-81A5-F2AA6846DF1B}") AVSynchronizedLayerClass  : public Iosapi::Quartzcore::CALayerClass 
{
	virtual void * __cdecl synchronizedLayerWithPlayerItem(_di_AVPlayerItem playerItem) = 0 ;
};

__interface  INTERFACE_UUID("{1DD0B3D7-3EFA-4C3E-9C20-6FE0CBD03586}") AVSynchronizedLayer  : public Iosapi::Quartzcore::CALayer 
{
	virtual _di_AVPlayerItem __cdecl playerItem() = 0 ;
	virtual void __cdecl setPlayerItem(_di_AVPlayerItem playerItem) = 0 ;
};

class PASCALIMPLEMENTATION TAVSynchronizedLayer : public Macapi::Objectivec::TOCGenericImport__2<_di_AVSynchronizedLayerClass,_di_AVSynchronizedLayer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVSynchronizedLayerClass,_di_AVSynchronizedLayer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVSynchronizedLayer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVSynchronizedLayerClass,_di_AVSynchronizedLayer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVSynchronizedLayer() { }
	
};


__interface  INTERFACE_UUID("{0F570D38-C338-4EAB-926C-8036ABC0E991}") AVCaptureVideoPreviewLayerClass  : public Iosapi::Quartzcore::CALayerClass 
{
	virtual void * __cdecl layerWithSession(_di_AVCaptureSession session) = 0 ;
};

__interface  INTERFACE_UUID("{ADD0E96E-F021-4C6A-B77F-EFE51BFF777F}") AVCaptureVideoPreviewLayer  : public Iosapi::Quartzcore::CALayer 
{
	virtual bool __cdecl automaticallyAdjustsMirroring() = 0 ;
	virtual void * __cdecl initWithSession(_di_AVCaptureSession session) = 0 ;
	virtual bool __cdecl isMirrored() = 0 ;
	virtual bool __cdecl isMirroringSupported() = 0 ;
	virtual bool __cdecl isOrientationSupported() = 0 ;
	virtual long __cdecl orientation() = 0 ;
	virtual _di_AVCaptureSession __cdecl session() = 0 ;
	virtual void __cdecl setAutomaticallyAdjustsMirroring(bool automaticallyAdjustsMirroring) = 0 ;
	virtual void __cdecl setMirrored(bool mirrored) = 0 ;
	virtual void __cdecl setOrientation(long orientation) = 0 ;
	virtual void __cdecl setSession(_di_AVCaptureSession session) = 0 ;
	virtual void __cdecl setVideoGravity(Iosapi::Foundation::_di_NSString videoGravity) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl videoGravity() = 0 ;
};

class PASCALIMPLEMENTATION TAVCaptureVideoPreviewLayer : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureVideoPreviewLayerClass,_di_AVCaptureVideoPreviewLayer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureVideoPreviewLayerClass,_di_AVCaptureVideoPreviewLayer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCaptureVideoPreviewLayer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureVideoPreviewLayerClass,_di_AVCaptureVideoPreviewLayer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCaptureVideoPreviewLayer() { }
	
};


__interface  INTERFACE_UUID("{40C77CD2-2EB8-43D6-97DE-73C58A7A74FE}") AVVideoCompositionCoreAnimationToolClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl videoCompositionCoreAnimationToolWithAdditionalLayer(Iosapi::Quartzcore::_di_CALayer layer, long asTrackID) = 0 ;
	virtual void * __cdecl videoCompositionCoreAnimationToolWithPostProcessingAsVideoLayer(Iosapi::Quartzcore::_di_CALayer videoLayer, Iosapi::Quartzcore::_di_CALayer inLayer) = 0 ;
};

__interface  INTERFACE_UUID("{EE8882B9-1520-4CD4-81FB-AA2D829F3E87}") AVVideoCompositionCoreAnimationTool  : public Iosapi::Foundation::NSObject 
{
	
};

class PASCALIMPLEMENTATION TAVVideoCompositionCoreAnimationTool : public Macapi::Objectivec::TOCGenericImport__2<_di_AVVideoCompositionCoreAnimationToolClass,_di_AVVideoCompositionCoreAnimationTool>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVVideoCompositionCoreAnimationToolClass,_di_AVVideoCompositionCoreAnimationTool> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVVideoCompositionCoreAnimationTool(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVVideoCompositionCoreAnimationToolClass,_di_AVVideoCompositionCoreAnimationTool>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVVideoCompositionCoreAnimationTool() { }
	
};


__interface  INTERFACE_UUID("{5C524476-1E48-4CEC-AACE-CDF5ECA5D517}") AVVideoCompositionInstructionClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{4025ED48-498E-4B1F-9557-D1E6BE3926C1}") AVVideoCompositionInstruction  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl backgroundColor() = 0 ;
	virtual bool __cdecl enablePostProcessing() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl layerInstructions() = 0 ;
	virtual void __cdecl setBackgroundColor(void * backgroundColor) = 0 ;
	virtual Iosapi::Coremedia::CMTimeRange __cdecl timeRange() = 0 ;
};

class PASCALIMPLEMENTATION TAVVideoCompositionInstruction : public Macapi::Objectivec::TOCGenericImport__2<_di_AVVideoCompositionInstructionClass,_di_AVVideoCompositionInstruction>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVVideoCompositionInstructionClass,_di_AVVideoCompositionInstruction> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVVideoCompositionInstruction(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVVideoCompositionInstructionClass,_di_AVVideoCompositionInstruction>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVVideoCompositionInstruction() { }
	
};


__interface  INTERFACE_UUID("{B19E0FF3-BF17-4A64-86B3-2BEF2754B486}") AVCaptureInputClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{18C9DEDC-52B5-4719-B8F6-5535AE4AF327}") AVCaptureInput  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl ports() = 0 ;
};

class PASCALIMPLEMENTATION TAVCaptureInput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureInputClass,_di_AVCaptureInput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureInputClass,_di_AVCaptureInput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCaptureInput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureInputClass,_di_AVCaptureInput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCaptureInput() { }
	
};


__interface  INTERFACE_UUID("{9B25990E-1B68-471F-BC48-B9A73DCE493E}") AVVideoCompositionClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{7C5FB1E2-81C3-4DD6-9B02-67D24EEF819B}") AVVideoComposition  : public Iosapi::Foundation::NSObject 
{
	virtual _di_AVVideoCompositionCoreAnimationTool __cdecl animationTool() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl frameDuration() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl instructions() = 0 ;
	virtual bool __cdecl isValidForAsset(_di_AVAsset asset, Iosapi::Coremedia::CMTimeRange timeRange, void * validationDelegate) = 0 ;
	virtual float __cdecl renderScale() = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl renderSize() = 0 ;
};

class PASCALIMPLEMENTATION TAVVideoComposition : public Macapi::Objectivec::TOCGenericImport__2<_di_AVVideoCompositionClass,_di_AVVideoComposition>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVVideoCompositionClass,_di_AVVideoComposition> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVVideoComposition(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVVideoCompositionClass,_di_AVVideoComposition>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVVideoComposition() { }
	
};


__interface  INTERFACE_UUID("{D471595F-8E3E-4443-97EC-DBC39B278F98}") AVCaptureInputPortClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{BDFBC779-6E77-4931-98CF-DFFB76A4BAFE}") AVCaptureInputPort  : public Iosapi::Foundation::NSObject 
{
	virtual NativeInt __cdecl formatDescription() = 0 ;
	virtual _di_AVCaptureInput __cdecl input() = 0 ;
	virtual bool __cdecl isEnabled() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl mediaType() = 0 ;
	virtual void __cdecl setEnabled(bool enabled) = 0 ;
};

class PASCALIMPLEMENTATION TAVCaptureInputPort : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureInputPortClass,_di_AVCaptureInputPort>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureInputPortClass,_di_AVCaptureInputPort> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCaptureInputPort(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureInputPortClass,_di_AVCaptureInputPort>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCaptureInputPort() { }
	
};


__interface  INTERFACE_UUID("{4893D945-50D3-40B2-9CF9-F641C7E4AFF2}") AVPlayerLayerClass  : public Iosapi::Quartzcore::CALayerClass 
{
	virtual void * __cdecl playerLayerWithPlayer(_di_AVPlayer player) = 0 ;
};

__interface  INTERFACE_UUID("{FB68755A-2D9B-4FAE-9F8C-B2E2081D05BC}") AVPlayerLayer  : public Iosapi::Quartzcore::CALayer 
{
	virtual bool __cdecl isReadyForDisplay() = 0 ;
	virtual _di_AVPlayer __cdecl player() = 0 ;
	virtual void __cdecl setPlayer(_di_AVPlayer player) = 0 ;
	virtual void __cdecl setVideoGravity(Iosapi::Foundation::_di_NSString videoGravity) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl videoGravity() = 0 ;
};

class PASCALIMPLEMENTATION TAVPlayerLayer : public Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerLayerClass,_di_AVPlayerLayer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerLayerClass,_di_AVPlayerLayer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVPlayerLayer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerLayerClass,_di_AVPlayerLayer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVPlayerLayer() { }
	
};


__interface  INTERFACE_UUID("{D255EEA2-8BFD-49BC-92FC-F9C187A0ED69}") AVPlayerItemAccessLogEventClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{E3DBD2FF-A12B-4054-BC21-4F48D342BDEF}") AVPlayerItemAccessLogEvent  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl URI() = 0 ;
	virtual double __cdecl durationWatched() = 0 ;
	virtual double __cdecl indicatedBitrate() = 0 ;
	virtual __int64 __cdecl numberOfBytesTransferred() = 0 ;
	virtual long __cdecl numberOfDroppedVideoFrames() = 0 ;
	virtual long __cdecl numberOfSegmentsDownloaded() = 0 ;
	virtual long __cdecl numberOfServerAddressChanges() = 0 ;
	virtual long __cdecl numberOfStalls() = 0 ;
	virtual double __cdecl observedBitrate() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl playbackSessionID() = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl playbackStartDate() = 0 ;
	virtual double __cdecl playbackStartOffset() = 0 ;
	virtual double __cdecl segmentsDownloadedDuration() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl serverAddress() = 0 ;
};

class PASCALIMPLEMENTATION TAVPlayerItemAccessLogEvent : public Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemAccessLogEventClass,_di_AVPlayerItemAccessLogEvent>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemAccessLogEventClass,_di_AVPlayerItemAccessLogEvent> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVPlayerItemAccessLogEvent(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemAccessLogEventClass,_di_AVPlayerItemAccessLogEvent>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVPlayerItemAccessLogEvent() { }
	
};


__interface  INTERFACE_UUID("{4EA933AA-4705-47B9-A76C-D9109D63F9D1}") AVPlayerItemErrorLogClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{593D59EB-6740-44C0-BEF8-327EAF2F3E92}") AVPlayerItemErrorLog  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl events() = 0 ;
	virtual Iosapi::Foundation::_di_NSData __cdecl extendedLogData() = 0 ;
	virtual unsigned long __cdecl extendedLogDataStringEncoding() = 0 ;
};

class PASCALIMPLEMENTATION TAVPlayerItemErrorLog : public Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemErrorLogClass,_di_AVPlayerItemErrorLog>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemErrorLogClass,_di_AVPlayerItemErrorLog> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVPlayerItemErrorLog(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemErrorLogClass,_di_AVPlayerItemErrorLog>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVPlayerItemErrorLog() { }
	
};


__interface  INTERFACE_UUID("{986E83A4-4329-4725-A3EB-BCB554EC869C}") AVPlayerItemAccessLogClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{25D30981-935C-4912-9136-681D50505D5C}") AVPlayerItemAccessLog  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl events() = 0 ;
	virtual Iosapi::Foundation::_di_NSData __cdecl extendedLogData() = 0 ;
	virtual unsigned long __cdecl extendedLogDataStringEncoding() = 0 ;
};

class PASCALIMPLEMENTATION TAVPlayerItemAccessLog : public Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemAccessLogClass,_di_AVPlayerItemAccessLog>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemAccessLogClass,_di_AVPlayerItemAccessLog> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVPlayerItemAccessLog(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemAccessLogClass,_di_AVPlayerItemAccessLog>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVPlayerItemAccessLog() { }
	
};


__interface  INTERFACE_UUID("{7EA84D4B-DE1D-4167-AD5B-DE9314176D01}") AVPlayerMediaSelectionCriteriaClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{3C35529D-2E74-434A-BC2B-A95BDFE9CDC9}") AVPlayerMediaSelectionCriteria  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl preferredLanguages() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl preferredMediaCharacteristics() = 0 ;
	virtual void * __cdecl initWithPreferredLanguages(Iosapi::Foundation::_di_NSArray preferredLanguages, Iosapi::Foundation::_di_NSArray preferredMediaCharacteristics) = 0 ;
};

class PASCALIMPLEMENTATION TAVPlayerMediaSelectionCriteria : public Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerMediaSelectionCriteriaClass,_di_AVPlayerMediaSelectionCriteria>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerMediaSelectionCriteriaClass,_di_AVPlayerMediaSelectionCriteria> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVPlayerMediaSelectionCriteria(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerMediaSelectionCriteriaClass,_di_AVPlayerMediaSelectionCriteria>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVPlayerMediaSelectionCriteria() { }
	
};


typedef void * PAVPlayerMediaSelectionCriteria;

__interface  INTERFACE_UUID("{32B0A5BC-2657-43D6-8FFF-A5F4BDD532FC}") AVPlayerClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl playerWithPlayerItem(_di_AVPlayerItem item) = 0 ;
	virtual void * __cdecl playerWithURL(Iosapi::Foundation::_di_NSURL URL) = 0 ;
};

__interface  INTERFACE_UUID("{5A085E79-FDDB-4FFA-8663-61EB1EEEC40C}") AVPlayer  : public Iosapi::Foundation::NSObject 
{
	virtual long __cdecl actionAtItemEnd() = 0 ;
	virtual bool __cdecl allowsAirPlayVideo() = 0 ;
	virtual _di_AVPlayerItem __cdecl currentItem() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl currentTime() = 0 ;
	virtual Iosapi::Foundation::_di_NSError __cdecl error() = 0 ;
	virtual void * __cdecl initWithPlayerItem(_di_AVPlayerItem item) = 0 ;
	virtual void * __cdecl initWithURL(Iosapi::Foundation::_di_NSURL URL) = 0 ;
	virtual bool __cdecl isAirPlayVideoActive() = 0 ;
	virtual bool __cdecl isClosedCaptionDisplayEnabled() = 0 ;
	virtual void __cdecl pause() = 0 ;
	virtual void __cdecl play() = 0 ;
	virtual float __cdecl rate() = 0 ;
	virtual void __cdecl removeTimeObserver(void * observer) = 0 ;
	virtual void __cdecl replaceCurrentItemWithPlayerItem(_di_AVPlayerItem item) = 0 ;
	virtual void __cdecl seekToTime(Iosapi::Coremedia::CMTime time) = 0 /* overload */;
	virtual void __cdecl seekToTime(Iosapi::Coremedia::CMTime time, Iosapi::Coremedia::CMTime toleranceBefore, Iosapi::Coremedia::CMTime toleranceAfter) = 0 /* overload */;
	virtual void __cdecl seekToTimeCompletionHandler(Iosapi::Coremedia::CMTime time, TAVFoundationCompletionHandler1 completionHandler) = 0 ;
	virtual void __cdecl setActionAtItemEnd(long actionAtItemEnd) = 0 ;
	virtual void __cdecl setAllowsAirPlayVideo(bool allowsAirPlayVideo) = 0 ;
	virtual void __cdecl setClosedCaptionDisplayEnabled(bool closedCaptionDisplayEnabled) = 0 ;
	virtual void __cdecl setRate(float rate) = 0 ;
	virtual void __cdecl setUsesAirPlayVideoWhileAirPlayScreenIsActive(bool usesAirPlayVideoWhileAirPlayScreenIsActive) = 0 ;
	virtual long __cdecl status() = 0 ;
	virtual bool __cdecl usesAirPlayVideoWhileAirPlayScreenIsActive() = 0 ;
	virtual void __cdecl seekToDate(Iosapi::Foundation::_di_NSDate date) = 0 ;
	virtual void __cdecl seekToDateCompletionHandler(Iosapi::Foundation::_di_NSDate date, TAVFoundationCompletionHandler1 completionHandler) = 0 ;
	virtual void __cdecl seekToTimeToleranceBeforeToleranceAfterCompletionHandler(Iosapi::Coremedia::CMTime time, Iosapi::Coremedia::CMTime toleranceBefore, Iosapi::Coremedia::CMTime toleranceAfter, TAVFoundationCompletionHandler1 completionHandler) = 0 ;
	virtual void __cdecl setRateTimeAtHostTime(float rate, Iosapi::Coremedia::CMTime time, Iosapi::Coremedia::CMTime atHostTime) = 0 ;
	virtual void __cdecl prerollAtRate(float rate, TAVFoundationCompletionHandler1 completionHandler) = 0 ;
	virtual void __cdecl cancelPendingPrerolls() = 0 ;
	virtual void __cdecl setMasterClock(void * masterClock) = 0 ;
	virtual void * __cdecl masterClock() = 0 ;
	virtual void * __cdecl addPeriodicTimeObserverForInterval(Iosapi::Coremedia::CMTime interval, NativeInt queue, TAVFoundationCompletionHandler2 usingBlock) = 0 ;
	virtual void * __cdecl addBoundaryTimeObserverForTimes(Iosapi::Foundation::_di_NSArray times, NativeInt queue, TAVFoundationCompletionHandler usingBlock) = 0 ;
	virtual void __cdecl setVolume(float volume) = 0 ;
	virtual float __cdecl volume() = 0 ;
	virtual void __cdecl setMuted(bool muted) = 0 ;
	virtual bool __cdecl isMuted() = 0 ;
	virtual void __cdecl setAppliesMediaSelectionCriteriaAutomatically(bool appliesMediaSelectionCriteriaAutomatically) = 0 ;
	virtual bool __cdecl appliesMediaSelectionCriteriaAutomatically() = 0 ;
	virtual void __cdecl setMediaSelectionCriteria(_di_AVPlayerMediaSelectionCriteria criteria, Iosapi::Foundation::_di_NSString forMediaCharacteristic) = 0 ;
	virtual _di_AVPlayerMediaSelectionCriteria __cdecl mediaSelectionCriteriaForMediaCharacteristic(Iosapi::Foundation::_di_NSString mediaCharacteristic) = 0 ;
	virtual void __cdecl setAudioOutputDeviceUniqueID(Iosapi::Foundation::_di_NSString audioOutputDeviceUniqueID) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl audioOutputDeviceUniqueID() = 0 ;
	virtual void __cdecl setAllowsExternalPlayback(bool allowsExternalPlayback) = 0 ;
	virtual bool __cdecl allowsExternalPlayback() = 0 ;
	virtual bool __cdecl isExternalPlaybackActive() = 0 ;
	virtual void __cdecl setUsesExternalPlaybackWhileExternalScreenIsActive(bool usesExternalPlaybackWhileExternalScreenIsActive) = 0 ;
	virtual bool __cdecl usesExternalPlaybackWhileExternalScreenIsActive() = 0 ;
	virtual void __cdecl setExternalPlaybackVideoGravity(Iosapi::Foundation::_di_NSString externalPlaybackVideoGravity) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl externalPlaybackVideoGravity() = 0 ;
	virtual bool __cdecl outputObscuredDueToInsufficientExternalProtection() = 0 ;
};

class PASCALIMPLEMENTATION TAVPlayer : public Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerClass,_di_AVPlayer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerClass,_di_AVPlayer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVPlayer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerClass,_di_AVPlayer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVPlayer() { }
	
};


__interface  INTERFACE_UUID("{38E2EF5D-D616-4D79-9C51-EE1DBF7448D8}") AVQueuePlayerClass  : public AVPlayerClass 
{
	virtual void * __cdecl queuePlayerWithItems(Iosapi::Foundation::_di_NSArray items) = 0 ;
};

__interface  INTERFACE_UUID("{B7E4AA83-21F9-491C-9049-C10D7A7D363A}") AVQueuePlayer  : public AVPlayer 
{
	virtual void * __cdecl initWithItems(Iosapi::Foundation::_di_NSArray items) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl items() = 0 ;
	virtual void __cdecl advanceToNextItem() = 0 ;
	virtual bool __cdecl canInsertItem(_di_AVPlayerItem item, _di_AVPlayerItem afterItem) = 0 ;
	virtual void __cdecl insertItem(_di_AVPlayerItem item, _di_AVPlayerItem afterItem) = 0 ;
	virtual void __cdecl removeItem(_di_AVPlayerItem item) = 0 ;
	virtual void __cdecl removeAllItems() = 0 ;
};

class PASCALIMPLEMENTATION TAVQueuePlayer : public Macapi::Objectivec::TOCGenericImport__2<_di_AVQueuePlayerClass,_di_AVQueuePlayer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVQueuePlayerClass,_di_AVQueuePlayer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVQueuePlayer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVQueuePlayerClass,_di_AVQueuePlayer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVQueuePlayer() { }
	
};


typedef void * PAVQueuePlayer;

__interface  INTERFACE_UUID("{5A46A428-F1B0-438A-868F-6D556F864153}") AVPlayerItemOutputClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{8C4C8554-5006-4E5E-8414-1B0BF5E1468A}") AVPlayerItemOutput  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Coremedia::CMTime __cdecl itemTimeForHostTime(double hostTimeInSeconds) = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl itemTimeForMachAbsoluteTime(__int64 machAbsoluteTime) = 0 ;
	virtual void __cdecl setSuppressesPlayerRendering(bool suppressesPlayerRendering) = 0 ;
	virtual bool __cdecl suppressesPlayerRendering() = 0 ;
};

class PASCALIMPLEMENTATION TAVPlayerItemOutput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemOutputClass,_di_AVPlayerItemOutput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemOutputClass,_di_AVPlayerItemOutput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVPlayerItemOutput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemOutputClass,_di_AVPlayerItemOutput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVPlayerItemOutput() { }
	
};


typedef void * PAVPlayerItemOutput;

__interface  INTERFACE_UUID("{EEFD6908-AE3F-4343-A4E8-E0493B28F750}") AVPlayerItemErrorLogEventClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{DF2F61D3-C2D6-40D1-AA9B-01FB5175D365}") AVPlayerItemErrorLogEvent  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSDate __cdecl date() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl URI() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl serverAddress() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl playbackSessionID() = 0 ;
	virtual long __cdecl errorStatusCode() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl errorDomain() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl errorComment() = 0 ;
};

class PASCALIMPLEMENTATION TAVPlayerItemErrorLogEvent : public Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemErrorLogEventClass,_di_AVPlayerItemErrorLogEvent>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemErrorLogEventClass,_di_AVPlayerItemErrorLogEvent> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVPlayerItemErrorLogEvent(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemErrorLogEventClass,_di_AVPlayerItemErrorLogEvent>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVPlayerItemErrorLogEvent() { }
	
};


typedef void * PAVPlayerItemErrorLogEvent;

__interface  INTERFACE_UUID("{4266026D-FF43-4194-A66A-B5DCC1CDE919}") AVPlayerItemVideoOutputClass  : public AVPlayerItemOutputClass 
{
	
};

__interface  INTERFACE_UUID("{017135B2-F916-4E73-BED3-24616A4F9689}") AVPlayerItemVideoOutput  : public AVPlayerItemOutput 
{
	virtual void * __cdecl initWithPixelBufferAttributes(Iosapi::Foundation::_di_NSDictionary pixelBufferAttributes) = 0 ;
	virtual bool __cdecl hasNewPixelBufferForItemTime(Iosapi::Coremedia::CMTime itemTime) = 0 ;
	virtual NativeInt __cdecl copyPixelBufferForItemTime(Iosapi::Coremedia::CMTime itemTime, void * itemTimeForDisplay) = 0 ;
	virtual void __cdecl setDelegate(void * delegate, NativeInt queue) = 0 ;
	virtual void __cdecl requestNotificationOfMediaDataChangeWithAdvanceInterval(double interval) = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual NativeInt __cdecl delegateQueue() = 0 ;
};

class PASCALIMPLEMENTATION TAVPlayerItemVideoOutput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemVideoOutputClass,_di_AVPlayerItemVideoOutput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemVideoOutputClass,_di_AVPlayerItemVideoOutput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVPlayerItemVideoOutput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemVideoOutputClass,_di_AVPlayerItemVideoOutput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVPlayerItemVideoOutput() { }
	
};


typedef void * PAVPlayerItemVideoOutput;

__interface  INTERFACE_UUID("{3DA7DBD8-CCB8-43E9-B0BB-2FDB5DB3B9CB}") AVPlayerItemLegibleOutputClass  : public AVPlayerItemOutputClass 
{
	
};

__interface  INTERFACE_UUID("{28CF68C1-0268-46EC-9C70-2069B2EAA416}") AVPlayerItemLegibleOutput  : public AVPlayerItemOutput 
{
	virtual void __cdecl setDelegate(void * delegate, NativeInt queue) = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual NativeInt __cdecl delegateQueue() = 0 ;
	virtual void __cdecl setAdvanceIntervalForDelegateInvocation(double advanceIntervalForDelegateInvocation) = 0 ;
	virtual double __cdecl advanceIntervalForDelegateInvocation() = 0 ;
	virtual void * __cdecl initWithMediaSubtypesForNativeRepresentation(Iosapi::Foundation::_di_NSArray subtypes) = 0 ;
	virtual void __cdecl setTextStylingResolution(Iosapi::Foundation::_di_NSString textStylingResolution) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl textStylingResolution() = 0 ;
};

class PASCALIMPLEMENTATION TAVPlayerItemLegibleOutput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemLegibleOutputClass,_di_AVPlayerItemLegibleOutput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemLegibleOutputClass,_di_AVPlayerItemLegibleOutput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVPlayerItemLegibleOutput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemLegibleOutputClass,_di_AVPlayerItemLegibleOutput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVPlayerItemLegibleOutput() { }
	
};


typedef void * PAVPlayerItemLegibleOutput;

__interface  INTERFACE_UUID("{5E5A0AF6-561C-4A67-B28C-14552048DBDF}") AVPlayerItemMetadataOutputClass  : public AVPlayerItemOutputClass 
{
	
};

__interface  INTERFACE_UUID("{40F568FA-A02F-4C45-B697-653DF1E2362E}") AVPlayerItemMetadataOutput  : public AVPlayerItemOutput 
{
	virtual void * __cdecl initWithIdentifiers(Iosapi::Foundation::_di_NSArray identifiers) = 0 ;
	virtual void __cdecl setDelegate(void * delegate, NativeInt queue) = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual NativeInt __cdecl delegateQueue() = 0 ;
	virtual void __cdecl setAdvanceIntervalForDelegateInvocation(double advanceIntervalForDelegateInvocation) = 0 ;
	virtual double __cdecl advanceIntervalForDelegateInvocation() = 0 ;
};

class PASCALIMPLEMENTATION TAVPlayerItemMetadataOutput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemMetadataOutputClass,_di_AVPlayerItemMetadataOutput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemMetadataOutputClass,_di_AVPlayerItemMetadataOutput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVPlayerItemMetadataOutput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemMetadataOutputClass,_di_AVPlayerItemMetadataOutput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVPlayerItemMetadataOutput() { }
	
};


typedef void * PAVPlayerItemMetadataOutput;

__interface  INTERFACE_UUID("{C5BC57A7-59C9-4DAE-9D43-D1FD54A1CC2E}") AVPlayerItemClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl playerItemWithAsset(_di_AVAsset asset) = 0 ;
	virtual void * __cdecl playerItemWithURL(Iosapi::Foundation::_di_NSURL URL) = 0 ;
};

__interface  INTERFACE_UUID("{D6330CE2-1082-41E4-8E8E-1E696264180A}") AVPlayerItem  : public Iosapi::Foundation::NSObject 
{
	virtual _di_AVPlayerItemAccessLog __cdecl accessLog() = 0 ;
	virtual _di_AVAsset __cdecl asset() = 0 ;
	virtual _di_AVAudioMix __cdecl audioMix() = 0 ;
	virtual bool __cdecl canPlayFastForward() = 0 ;
	virtual bool __cdecl canPlayFastReverse() = 0 ;
	virtual void __cdecl cancelPendingSeeks() = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl currentDate() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl currentTime() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl duration() = 0 ;
	virtual Iosapi::Foundation::_di_NSError __cdecl error() = 0 ;
	virtual _di_AVPlayerItemErrorLog __cdecl errorLog() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl forwardPlaybackEndTime() = 0 ;
	virtual void * __cdecl initWithAsset(_di_AVAsset asset) = 0 ;
	virtual void * __cdecl initWithURL(Iosapi::Foundation::_di_NSURL URL) = 0 ;
	virtual bool __cdecl isPlaybackBufferEmpty() = 0 ;
	virtual bool __cdecl isPlaybackBufferFull() = 0 ;
	virtual bool __cdecl isPlaybackLikelyToKeepUp() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl loadedTimeRanges() = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl presentationSize() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl reversePlaybackEndTime() = 0 ;
	virtual bool __cdecl seekToDate(Iosapi::Foundation::_di_NSDate date) = 0 ;
	virtual void __cdecl seekToTime(Iosapi::Coremedia::CMTime time) = 0 /* overload */;
	virtual void __cdecl seekToTime(Iosapi::Coremedia::CMTime time, Iosapi::Coremedia::CMTime toleranceBefore, Iosapi::Coremedia::CMTime toleranceAfter) = 0 /* overload */;
	virtual Iosapi::Foundation::_di_NSArray __cdecl seekableTimeRanges() = 0 ;
	virtual void __cdecl selectMediaOption(_di_AVMediaSelectionOption mediaSelectionOption, _di_AVMediaSelectionGroup inMediaSelectionGroup) = 0 ;
	virtual _di_AVMediaSelectionOption __cdecl selectedMediaOptionInMediaSelectionGroup(_di_AVMediaSelectionGroup mediaSelectionGroup) = 0 ;
	virtual void __cdecl setAudioMix(_di_AVAudioMix audioMix) = 0 ;
	virtual void __cdecl setForwardPlaybackEndTime(Iosapi::Coremedia::CMTime forwardPlaybackEndTime) = 0 ;
	virtual void __cdecl setReversePlaybackEndTime(Iosapi::Coremedia::CMTime reversePlaybackEndTime) = 0 ;
	virtual void __cdecl setVideoComposition(_di_AVVideoComposition videoComposition) = 0 ;
	virtual long __cdecl status() = 0 ;
	virtual void __cdecl stepByCount(long stepCount) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl timedMetadata() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl tracks() = 0 ;
	virtual _di_AVVideoComposition __cdecl videoComposition() = 0 ;
};

class PASCALIMPLEMENTATION TAVPlayerItem : public Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemClass,_di_AVPlayerItem>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemClass,_di_AVPlayerItem> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVPlayerItem(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemClass,_di_AVPlayerItem>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVPlayerItem() { }
	
};


__interface  INTERFACE_UUID("{84EDCC78-4B73-4EE4-A38A-1989E8D4C681}") AVMediaSelectionOptionClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{3B90172E-C137-4EC9-94DB-CB7236698F0D}") AVMediaSelectionOption  : public Iosapi::Foundation::NSObject 
{
	virtual _di_AVMediaSelectionOption __cdecl associatedMediaSelectionOptionInMediaSelectionGroup(_di_AVMediaSelectionGroup mediaSelectionGroup) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl availableMetadataFormats() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl commonMetadata() = 0 ;
	virtual bool __cdecl hasMediaCharacteristic(Iosapi::Foundation::_di_NSString mediaCharacteristic) = 0 ;
	virtual bool __cdecl isPlayable() = 0 ;
	virtual Iosapi::Foundation::_di_NSLocale __cdecl locale() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl mediaSubTypes() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl mediaType() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl metadataForFormat(Iosapi::Foundation::_di_NSString format) = 0 ;
	virtual void * __cdecl propertyList() = 0 ;
};

class PASCALIMPLEMENTATION TAVMediaSelectionOption : public Macapi::Objectivec::TOCGenericImport__2<_di_AVMediaSelectionOptionClass,_di_AVMediaSelectionOption>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVMediaSelectionOptionClass,_di_AVMediaSelectionOption> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVMediaSelectionOption(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVMediaSelectionOptionClass,_di_AVMediaSelectionOption>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVMediaSelectionOption() { }
	
};


__interface  INTERFACE_UUID("{A1AB759B-FD5A-42CC-A7D4-8F1A7A97849A}") AVMediaSelectionGroupClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl mediaSelectionOptionsFromArray(Iosapi::Foundation::_di_NSArray array_, Iosapi::Foundation::_di_NSLocale withLocale) = 0 /* overload */;
	virtual Iosapi::Foundation::_di_NSArray __cdecl mediaSelectionOptionsFromArray(Iosapi::Foundation::_di_NSArray array_, Iosapi::Foundation::_di_NSArray withMediaCharacteristics) = 0 /* overload */;
	virtual Iosapi::Foundation::_di_NSArray __cdecl playableMediaSelectionOptionsFromArray(Iosapi::Foundation::_di_NSArray array_) = 0 ;
};

__interface  INTERFACE_UUID("{92BD2ADE-72E8-44D0-B233-8D7558FD8DE5}") AVMediaSelectionGroup  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl allowsEmptySelection() = 0 ;
	virtual _di_AVMediaSelectionOption __cdecl mediaSelectionOptionWithPropertyList(void * plist) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl options() = 0 ;
};

class PASCALIMPLEMENTATION TAVMediaSelectionGroup : public Macapi::Objectivec::TOCGenericImport__2<_di_AVMediaSelectionGroupClass,_di_AVMediaSelectionGroup>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVMediaSelectionGroupClass,_di_AVMediaSelectionGroup> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVMediaSelectionGroup(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVMediaSelectionGroupClass,_di_AVMediaSelectionGroup>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVMediaSelectionGroup() { }
	
};


__interface  INTERFACE_UUID("{130F769A-4ED7-4AC8-8304-94F07E39F173}") AVMetadataItemClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl metadataItemsFromArray(Iosapi::Foundation::_di_NSArray array_, void * withKey, Iosapi::Foundation::_di_NSString keySpace) = 0 /* overload */;
	virtual Iosapi::Foundation::_di_NSArray __cdecl metadataItemsFromArray(Iosapi::Foundation::_di_NSArray array_, Iosapi::Foundation::_di_NSLocale withLocale) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{A7A40638-4DC7-4A86-A4B2-6C47D3A0BC6D}") AVMetadataItem  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl commonKey() = 0 ;
	virtual Iosapi::Foundation::_di_NSData __cdecl dataValue() = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl dateValue() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl duration() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl extraAttributes() = 0 ;
	virtual void * __cdecl key() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl keySpace() = 0 ;
	virtual Iosapi::Foundation::_di_NSLocale __cdecl locale() = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl numberValue() = 0 ;
	virtual long __cdecl statusOfValueForKey(Iosapi::Foundation::_di_NSString key, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl stringValue() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl time() = 0 ;
	virtual void * __cdecl value() = 0 ;
};

class PASCALIMPLEMENTATION TAVMetadataItem : public Macapi::Objectivec::TOCGenericImport__2<_di_AVMetadataItemClass,_di_AVMetadataItem>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVMetadataItemClass,_di_AVMetadataItem> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVMetadataItem(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVMetadataItemClass,_di_AVMetadataItem>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVMetadataItem() { }
	
};


__interface  INTERFACE_UUID("{93725DB1-C395-43DF-A31B-398760D22150}") AVPlayerItemTrackClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{B77509C9-F47E-4CA0-BCE5-D14CA98C8549}") AVPlayerItemTrack  : public Iosapi::Foundation::NSObject 
{
	virtual _di_AVAssetTrack __cdecl assetTrack() = 0 ;
	virtual bool __cdecl isEnabled() = 0 ;
	virtual void __cdecl setEnabled(bool enabled) = 0 ;
};

class PASCALIMPLEMENTATION TAVPlayerItemTrack : public Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemTrackClass,_di_AVPlayerItemTrack>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemTrackClass,_di_AVPlayerItemTrack> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVPlayerItemTrack(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVPlayerItemTrackClass,_di_AVPlayerItemTrack>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVPlayerItemTrack() { }
	
};


__interface  INTERFACE_UUID("{D99109B5-EBAB-4DFD-85C5-5FECBDA5D43D}") AVCaptureDeviceClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual long __cdecl authorizationStatusForMediaType(Iosapi::Foundation::_di_NSString mediaType) = 0 ;
	virtual void * __cdecl defaultDeviceWithDeviceType(Iosapi::Foundation::_di_NSString deviceType, Iosapi::Foundation::_di_NSString mediaType, long position) = 0 ;
	virtual void * __cdecl defaultDeviceWithMediaType(Iosapi::Foundation::_di_NSString mediaType) = 0 ;
	virtual void * __cdecl deviceWithUniqueID(Iosapi::Foundation::_di_NSString deviceUniqueID) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl devices() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl devicesWithMediaType(Iosapi::Foundation::_di_NSString mediaType) = 0 ;
	virtual void __cdecl requestAccessForMediaType(Iosapi::Foundation::_di_NSString mediaType, TAVFoundationCompletionHandler3 handler) = 0 ;
};

__interface  INTERFACE_UUID("{A8ECC90F-6016-44A4-BB84-8FB720CF786D}") AVCaptureDevice  : public Iosapi::Foundation::NSObject 
{
	virtual long __cdecl exposureMode() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl exposurePointOfInterest() = 0 ;
	virtual long __cdecl flashMode() = 0 ;
	virtual long __cdecl focusMode() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl focusPointOfInterest() = 0 ;
	virtual bool __cdecl hasFlash() = 0 ;
	virtual bool __cdecl hasMediaType(Iosapi::Foundation::_di_NSString mediaType) = 0 ;
	virtual bool __cdecl hasTorch() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl formats() = 0 ;
	virtual void __cdecl setActiveFormat(_di_AVCaptureDeviceFormat activeFormat) = 0 ;
	virtual _di_AVCaptureDeviceFormat __cdecl activeFormat() = 0 ;
	virtual void __cdecl setActiveVideoMinFrameDuration(Iosapi::Coremedia::CMTime activeVideoMinFrameDuration) = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl activeVideoMinFrameDuration() = 0 ;
	virtual void __cdecl setActiveVideoMaxFrameDuration(Iosapi::Coremedia::CMTime activeVideoMaxFrameDuration) = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl activeVideoMaxFrameDuration() = 0 ;
	virtual bool __cdecl isAdjustingExposure() = 0 ;
	virtual bool __cdecl isAdjustingFocus() = 0 ;
	virtual bool __cdecl isAdjustingWhiteBalance() = 0 ;
	virtual bool __cdecl isConnected() = 0 ;
	virtual bool __cdecl isExposureModeSupported(long exposureMode) = 0 ;
	virtual bool __cdecl isExposurePointOfInterestSupported() = 0 ;
	virtual bool __cdecl isFlashActive() = 0 ;
	virtual bool __cdecl isFlashAvailable() = 0 ;
	virtual bool __cdecl isFlashModeSupported(long flashMode) = 0 ;
	virtual bool __cdecl isFocusModeSupported(long focusMode) = 0 ;
	virtual bool __cdecl isFocusPointOfInterestSupported() = 0 ;
	virtual bool __cdecl isSubjectAreaChangeMonitoringEnabled() = 0 ;
	virtual bool __cdecl isTorchAvailable() = 0 ;
	virtual bool __cdecl isTorchModeSupported(long torchMode) = 0 ;
	virtual bool __cdecl isWhiteBalanceModeSupported(long whiteBalanceMode) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl localizedName() = 0 ;
	virtual bool __cdecl lockForConfiguration(System::PPointer outError = (System::PPointer)(0x0)) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl modelID() = 0 ;
	virtual long __cdecl position() = 0 ;
	virtual void __cdecl setExposureMode(long exposureMode) = 0 ;
	virtual void __cdecl setExposurePointOfInterest(Iosapi::Foundation::NSPoint exposurePointOfInterest) = 0 ;
	virtual void __cdecl setFlashMode(long flashMode) = 0 ;
	virtual void __cdecl setFocusMode(long focusMode) = 0 ;
	virtual void __cdecl setFocusPointOfInterest(Iosapi::Foundation::NSPoint focusPointOfInterest) = 0 ;
	virtual void __cdecl setSubjectAreaChangeMonitoringEnabled(bool subjectAreaChangeMonitoringEnabled) = 0 ;
	virtual void __cdecl setTorchMode(long torchMode) = 0 ;
	virtual void __cdecl setWhiteBalanceMode(long whiteBalanceMode) = 0 ;
	virtual bool __cdecl supportsAVCaptureSessionPreset(Iosapi::Foundation::_di_NSString preset) = 0 ;
	virtual float __cdecl torchLevel() = 0 ;
	virtual long __cdecl torchMode() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl uniqueID() = 0 ;
	virtual void __cdecl unlockForConfiguration() = 0 ;
	virtual long __cdecl whiteBalanceMode() = 0 ;
};

class PASCALIMPLEMENTATION TAVCaptureDevice : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureDeviceClass,_di_AVCaptureDevice>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureDeviceClass,_di_AVCaptureDevice> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCaptureDevice(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureDeviceClass,_di_AVCaptureDevice>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCaptureDevice() { }
	
};


__interface  INTERFACE_UUID("{681359F1-9D28-49F5-8234-5D6451A52F3C}") AVFrameRateRangeClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{EF3E80FE-3E82-4DAE-B15D-EC9B86F3DCE7}") AVFrameRateRange  : public Iosapi::Foundation::NSObject 
{
	virtual double __cdecl minFrameRate() = 0 ;
	virtual double __cdecl maxFrameRate() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl maxFrameDuration() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl minFrameDuration() = 0 ;
};

class PASCALIMPLEMENTATION TAVFrameRateRange : public Macapi::Objectivec::TOCGenericImport__2<_di_AVFrameRateRangeClass,_di_AVFrameRateRange>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVFrameRateRangeClass,_di_AVFrameRateRange> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVFrameRateRange(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVFrameRateRangeClass,_di_AVFrameRateRange>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVFrameRateRange() { }
	
};


__interface  INTERFACE_UUID("{3117D5A1-A0E0-4037-B732-71ADCF3FEFA2}") AVAssetTrackClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{5FB20151-009C-465B-80F7-E2C90471409A}") AVAssetTrack  : public Iosapi::Foundation::NSObject 
{
	virtual _di_AVAsset __cdecl asset() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl availableMetadataFormats() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl commonMetadata() = 0 ;
	virtual float __cdecl estimatedDataRate() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl extendedLanguageTag() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl formatDescriptions() = 0 ;
	virtual bool __cdecl hasMediaCharacteristic(Iosapi::Foundation::_di_NSString mediaCharacteristic) = 0 ;
	virtual bool __cdecl isEnabled() = 0 ;
	virtual bool __cdecl isPlayable() = 0 ;
	virtual bool __cdecl isSelfContained() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl languageCode() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl mediaType() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl metadataForFormat(Iosapi::Foundation::_di_NSString format) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl naturalSize() = 0 ;
	virtual int __cdecl naturalTimeScale() = 0 ;
	virtual float __cdecl nominalFrameRate() = 0 ;
	virtual Iosapi::Coregraphics::CGAffineTransform __cdecl preferredTransform() = 0 ;
	virtual float __cdecl preferredVolume() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl samplePresentationTimeForTrackTime(Iosapi::Coremedia::CMTime trackTime) = 0 ;
	virtual _di_AVAssetTrackSegment __cdecl segmentForTrackTime(Iosapi::Coremedia::CMTime trackTime) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl segments() = 0 ;
	virtual Iosapi::Coremedia::CMTimeRange __cdecl timeRange() = 0 ;
	virtual __int64 __cdecl totalSampleDataLength() = 0 ;
	virtual long __cdecl trackID() = 0 ;
};

class PASCALIMPLEMENTATION TAVAssetTrack : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetTrackClass,_di_AVAssetTrack>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetTrackClass,_di_AVAssetTrack> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAssetTrack(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetTrackClass,_di_AVAssetTrack>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAssetTrack() { }
	
};


__interface  INTERFACE_UUID("{0F9BDB53-C283-47AA-B733-0B5D7A61DBF0}") AVAssetTrackSegmentClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{57AC9D4B-F54F-40CB-BF48-4BEA9DFBB6D3}") AVAssetTrackSegment  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl isEmpty() = 0 ;
	virtual Iosapi::Coremedia::CMTimeMapping __cdecl timeMapping() = 0 ;
};

class PASCALIMPLEMENTATION TAVAssetTrackSegment : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetTrackSegmentClass,_di_AVAssetTrackSegment>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetTrackSegmentClass,_di_AVAssetTrackSegment> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAssetTrackSegment(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetTrackSegmentClass,_di_AVAssetTrackSegment>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAssetTrackSegment() { }
	
};


__interface  INTERFACE_UUID("{5B1853CA-F40B-418F-9411-19247F629D80}") AVAssetClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl assetWithURL(Iosapi::Foundation::_di_NSURL URL) = 0 ;
};

__interface  INTERFACE_UUID("{1762072E-9F4E-478A-B37C-06FCD01ACD36}") AVAsset  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl availableChapterLocales() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl availableMediaCharacteristicsWithMediaSelectionOptions() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl availableMetadataFormats() = 0 ;
	virtual void __cdecl cancelLoading() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl chapterMetadataGroupsWithTitleLocale(Iosapi::Foundation::_di_NSLocale locale, Iosapi::Foundation::_di_NSArray containingItemsWithCommonKeys) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl commonMetadata() = 0 ;
	virtual _di_AVMetadataItem __cdecl creationDate() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl duration() = 0 ;
	virtual bool __cdecl hasProtectedContent() = 0 ;
	virtual bool __cdecl isCompatibleWithSavedPhotosAlbum() = 0 ;
	virtual bool __cdecl isComposable() = 0 ;
	virtual bool __cdecl isExportable() = 0 ;
	virtual bool __cdecl isPlayable() = 0 ;
	virtual bool __cdecl isReadable() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl lyrics() = 0 ;
	virtual _di_AVMediaSelectionGroup __cdecl mediaSelectionGroupForMediaCharacteristic(Iosapi::Foundation::_di_NSString mediaCharacteristic) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl metadataForFormat(Iosapi::Foundation::_di_NSString format) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl naturalSize() = 0 ;
	virtual float __cdecl preferredRate() = 0 ;
	virtual Iosapi::Coregraphics::CGAffineTransform __cdecl preferredTransform() = 0 ;
	virtual float __cdecl preferredVolume() = 0 ;
	virtual bool __cdecl providesPreciseDurationAndTiming() = 0 ;
	virtual unsigned long __cdecl referenceRestrictions() = 0 ;
	virtual _di_AVAssetTrack __cdecl trackWithTrackID(long trackID) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl tracks() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl tracksWithMediaCharacteristic(Iosapi::Foundation::_di_NSString mediaCharacteristic) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl tracksWithMediaType(Iosapi::Foundation::_di_NSString mediaType) = 0 ;
	virtual long __cdecl unusedTrackID() = 0 ;
};

class PASCALIMPLEMENTATION TAVAsset : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetClass,_di_AVAsset>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetClass,_di_AVAsset> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAsset(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetClass,_di_AVAsset>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAsset() { }
	
};


__interface  INTERFACE_UUID("{6D40766B-E7D4-4AB1-84C0-40854E31DBB1}") AVAssetWriterClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl assetWriterWithURL(Iosapi::Foundation::_di_NSURL outputURL, Iosapi::Foundation::_di_NSString fileType, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
};

__interface  INTERFACE_UUID("{3267019A-FB54-4919-B507-759FF0E92BEF}") AVAssetWriter  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl addInput(_di_AVAssetWriterInput input) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl availableMediaTypes() = 0 ;
	virtual bool __cdecl canAddInput(_di_AVAssetWriterInput input) = 0 ;
	virtual bool __cdecl canApplyOutputSettings(Iosapi::Foundation::_di_NSDictionary outputSettings, Iosapi::Foundation::_di_NSString forMediaType) = 0 ;
	virtual void __cdecl cancelWriting() = 0 ;
	virtual void __cdecl endSessionAtSourceTime(Iosapi::Coremedia::CMTime endTime) = 0 ;
	virtual Iosapi::Foundation::_di_NSError __cdecl error() = 0 ;
	virtual bool __cdecl finishWriting() = 0 ;
	virtual void * __cdecl initWithURL(Iosapi::Foundation::_di_NSURL outputURL, Iosapi::Foundation::_di_NSString fileType, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl inputs() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl metadata() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl movieFragmentInterval() = 0 ;
	virtual int __cdecl movieTimeScale() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl outputFileType() = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl outputURL() = 0 ;
	virtual void __cdecl setMetadata(Iosapi::Foundation::_di_NSArray metadata) = 0 ;
	virtual void __cdecl setMovieFragmentInterval(Iosapi::Coremedia::CMTime movieFragmentInterval) = 0 ;
	virtual void __cdecl setMovieTimeScale(int movieTimeScale) = 0 ;
	virtual void __cdecl setShouldOptimizeForNetworkUse(bool shouldOptimizeForNetworkUse) = 0 ;
	virtual bool __cdecl shouldOptimizeForNetworkUse() = 0 ;
	virtual void __cdecl startSessionAtSourceTime(Iosapi::Coremedia::CMTime startTime) = 0 ;
	virtual bool __cdecl startWriting() = 0 ;
	virtual long __cdecl status() = 0 ;
};

class PASCALIMPLEMENTATION TAVAssetWriter : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetWriterClass,_di_AVAssetWriter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetWriterClass,_di_AVAssetWriter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAssetWriter(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetWriterClass,_di_AVAssetWriter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAssetWriter() { }
	
};


__interface  INTERFACE_UUID("{5C7794F2-361F-4E6C-8C9F-E00CF0246A15}") AVAssetImageGeneratorClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl assetImageGeneratorWithAsset(_di_AVAsset asset) = 0 ;
};

__interface  INTERFACE_UUID("{0B8393D2-55CC-49CE-AB2C-C6B8938CC180}") AVAssetImageGenerator  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl apertureMode() = 0 ;
	virtual bool __cdecl appliesPreferredTrackTransform() = 0 ;
	virtual void __cdecl cancelAllCGImageGeneration() = 0 ;
	virtual void * __cdecl copyCGImageAtTime(Iosapi::Coremedia::CMTime requestedTime, Iosapi::Coremedia::CMTime actualTime, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual void * __cdecl initWithAsset(_di_AVAsset asset) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl maximumSize() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl requestedTimeToleranceAfter() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl requestedTimeToleranceBefore() = 0 ;
	virtual void __cdecl setApertureMode(Iosapi::Foundation::_di_NSString apertureMode) = 0 ;
	virtual void __cdecl setAppliesPreferredTrackTransform(bool appliesPreferredTrackTransform) = 0 ;
	virtual void __cdecl setMaximumSize(Iosapi::Foundation::NSSize maximumSize) = 0 ;
	virtual void __cdecl setRequestedTimeToleranceAfter(Iosapi::Coremedia::CMTime requestedTimeToleranceAfter) = 0 ;
	virtual void __cdecl setRequestedTimeToleranceBefore(Iosapi::Coremedia::CMTime requestedTimeToleranceBefore) = 0 ;
	virtual void __cdecl setVideoComposition(_di_AVVideoComposition videoComposition) = 0 ;
	virtual _di_AVVideoComposition __cdecl videoComposition() = 0 ;
};

class PASCALIMPLEMENTATION TAVAssetImageGenerator : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetImageGeneratorClass,_di_AVAssetImageGenerator>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetImageGeneratorClass,_di_AVAssetImageGenerator> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAssetImageGenerator(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetImageGeneratorClass,_di_AVAssetImageGenerator>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAssetImageGenerator() { }
	
};


__interface  INTERFACE_UUID("{46299F3E-74CC-422A-8133-F0D4D62BDD1D}") AVAssetExportSessionClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl allExportPresets() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl exportPresetsCompatibleWithAsset(_di_AVAsset asset) = 0 ;
	virtual void * __cdecl exportSessionWithAsset(_di_AVAsset asset, Iosapi::Foundation::_di_NSString presetName) = 0 ;
};

__interface  INTERFACE_UUID("{3E6C3EAA-A638-4B5C-BE76-231F684EE84F}") AVAssetExportSession  : public Iosapi::Foundation::NSObject 
{
	virtual _di_AVAsset __cdecl asset() = 0 ;
	virtual _di_AVAudioMix __cdecl audioMix() = 0 ;
	virtual void __cdecl cancelExport() = 0 ;
	virtual Iosapi::Foundation::_di_NSError __cdecl error() = 0 ;
	virtual __int64 __cdecl estimatedOutputFileLength() = 0 ;
	virtual __int64 __cdecl fileLengthLimit() = 0 ;
	virtual void * __cdecl initWithAsset(_di_AVAsset asset, Iosapi::Foundation::_di_NSString presetName) = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl maxDuration() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl metadata() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl outputFileType() = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl outputURL() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl presetName() = 0 ;
	virtual float __cdecl progress() = 0 ;
	virtual void __cdecl setAudioMix(_di_AVAudioMix audioMix) = 0 ;
	virtual void __cdecl setFileLengthLimit(__int64 fileLengthLimit) = 0 ;
	virtual void __cdecl setMetadata(Iosapi::Foundation::_di_NSArray metadata) = 0 ;
	virtual void __cdecl setOutputFileType(Iosapi::Foundation::_di_NSString outputFileType) = 0 ;
	virtual void __cdecl setOutputURL(Iosapi::Foundation::_di_NSURL outputURL) = 0 ;
	virtual void __cdecl setShouldOptimizeForNetworkUse(bool shouldOptimizeForNetworkUse) = 0 ;
	virtual void __cdecl setTimeRange(Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	virtual void __cdecl setVideoComposition(_di_AVVideoComposition videoComposition) = 0 ;
	virtual bool __cdecl shouldOptimizeForNetworkUse() = 0 ;
	virtual long __cdecl status() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl supportedFileTypes() = 0 ;
	virtual Iosapi::Coremedia::CMTimeRange __cdecl timeRange() = 0 ;
	virtual _di_AVVideoComposition __cdecl videoComposition() = 0 ;
};

class PASCALIMPLEMENTATION TAVAssetExportSession : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetExportSessionClass,_di_AVAssetExportSession>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetExportSessionClass,_di_AVAssetExportSession> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAssetExportSession(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetExportSessionClass,_di_AVAssetExportSession>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAssetExportSession() { }
	
};


__interface  INTERFACE_UUID("{9EF367AD-6B43-4496-833F-6D0CEFAC4F85}") AVAssetReaderClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl assetReaderWithAsset(_di_AVAsset asset, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
};

__interface  INTERFACE_UUID("{8F7018C5-89C3-47BA-A250-E9F0974F5FDF}") AVAssetReader  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl addOutput(_di_AVAssetReaderOutput output) = 0 ;
	virtual _di_AVAsset __cdecl asset() = 0 ;
	virtual bool __cdecl canAddOutput(_di_AVAssetReaderOutput output) = 0 ;
	virtual void __cdecl cancelReading() = 0 ;
	virtual Iosapi::Foundation::_di_NSError __cdecl error() = 0 ;
	virtual void * __cdecl initWithAsset(_di_AVAsset asset, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl outputs() = 0 ;
	virtual void __cdecl setTimeRange(Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	virtual bool __cdecl startReading() = 0 ;
	virtual long __cdecl status() = 0 ;
	virtual Iosapi::Coremedia::CMTimeRange __cdecl timeRange() = 0 ;
};

class PASCALIMPLEMENTATION TAVAssetReader : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetReaderClass,_di_AVAssetReader>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetReaderClass,_di_AVAssetReader> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAssetReader(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetReaderClass,_di_AVAssetReader>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAssetReader() { }
	
};


__interface  INTERFACE_UUID("{A18FC0FD-FB8B-47AA-AE57-A0A563C81353}") AVAssetReaderOutputClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{C784D941-58FF-417F-9234-F021DA36D4A7}") AVAssetReaderOutput  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl alwaysCopiesSampleData() = 0 ;
	virtual void * __cdecl copyNextSampleBuffer() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl mediaType() = 0 ;
	virtual void __cdecl setAlwaysCopiesSampleData(bool alwaysCopiesSampleData) = 0 ;
};

class PASCALIMPLEMENTATION TAVAssetReaderOutput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetReaderOutputClass,_di_AVAssetReaderOutput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetReaderOutputClass,_di_AVAssetReaderOutput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAssetReaderOutput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetReaderOutputClass,_di_AVAssetReaderOutput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAssetReaderOutput() { }
	
};


__interface  INTERFACE_UUID("{27750A0D-F670-4CA2-8D70-93AF033E990D}") AVAudioSessionClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl sharedInstance() = 0 ;
};

__interface  INTERFACE_UUID("{C23AE581-031A-4504-A0AF-C40F6482173A}") AVAudioSession  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl category() = 0 ;
	virtual long __cdecl currentHardwareInputNumberOfChannels() = 0 ;
	virtual long __cdecl currentHardwareOutputNumberOfChannels() = 0 ;
	virtual double __cdecl currentHardwareSampleRate() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual bool __cdecl inputIsAvailable() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl mode() = 0 ;
	virtual double __cdecl preferredHardwareSampleRate() = 0 ;
	virtual double __cdecl preferredIOBufferDuration() = 0 ;
	virtual bool __cdecl setActive(bool beActive, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual bool __cdecl setActive(bool beActive, long withFlags, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual bool __cdecl setCategory(Iosapi::Foundation::_di_NSString theCategory, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual bool __cdecl setMode(Iosapi::Foundation::_di_NSString theMode, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl setPreferredHardwareSampleRate(double sampleRate, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl setPreferredIOBufferDuration(double duration, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
};

class PASCALIMPLEMENTATION TAVAudioSession : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAudioSessionClass,_di_AVAudioSession>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAudioSessionClass,_di_AVAudioSession> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAudioSession(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAudioSessionClass,_di_AVAudioSession>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAudioSession() { }
	
};


__interface  INTERFACE_UUID("{01C5ADE2-BE0F-46E2-B5C1-DB18D9861ADC}") AVCaptureDeviceFormatClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{FE87B684-00B7-467D-A15A-9220534CD5D5}") AVCaptureDeviceFormat  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl mediaType() = 0 ;
	virtual NativeInt __cdecl formatDescription() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl videoSupportedFrameRateRanges() = 0 ;
	virtual float __cdecl videoFieldOfView() = 0 ;
	virtual bool __cdecl isVideoBinned() = 0 ;
	virtual bool __cdecl isVideoStabilizationSupported() = 0 ;
	virtual double __cdecl videoMaxZoomFactor() = 0 ;
	virtual double __cdecl videoZoomFactorUpscaleThreshold() = 0 ;
};

class PASCALIMPLEMENTATION TAVCaptureDeviceFormat : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureDeviceFormatClass,_di_AVCaptureDeviceFormat>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureDeviceFormatClass,_di_AVCaptureDeviceFormat> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCaptureDeviceFormat(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureDeviceFormatClass,_di_AVCaptureDeviceFormat>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCaptureDeviceFormat() { }
	
};


__interface  INTERFACE_UUID("{8BB1CEAF-2C49-4093-8A90-0253A9F0AA70}") AVAudioRecorderClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{DE27A761-9065-44E4-8F57-6AF044C999E9}") AVAudioRecorder  : public Iosapi::Foundation::NSObject 
{
	virtual float __cdecl averagePowerForChannel(unsigned long channelNumber) = 0 ;
	virtual double __cdecl currentTime() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual bool __cdecl deleteRecording() = 0 ;
	virtual void * __cdecl initWithURL(Iosapi::Foundation::_di_NSURL url, Iosapi::Foundation::_di_NSDictionary settings, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl isMeteringEnabled() = 0 ;
	virtual bool __cdecl isRecording() = 0 ;
	virtual void __cdecl pause() = 0 ;
	virtual float __cdecl peakPowerForChannel(unsigned long channelNumber) = 0 ;
	virtual bool __cdecl prepareToRecord() = 0 ;
	virtual bool __cdecl record() = 0 ;
	virtual bool __cdecl recordForDuration(double duration) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setMeteringEnabled(bool meteringEnabled) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl settings() = 0 ;
	virtual void __cdecl stop() = 0 ;
	virtual void __cdecl updateMeters() = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl url() = 0 ;
};

class PASCALIMPLEMENTATION TAVAudioRecorder : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAudioRecorderClass,_di_AVAudioRecorder>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAudioRecorderClass,_di_AVAudioRecorder> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAudioRecorder(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAudioRecorderClass,_di_AVAudioRecorder>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAudioRecorder() { }
	
};


__interface  INTERFACE_UUID("{E6E22267-6084-470F-A47D-1AD8FCDE3C62}") AVCaptureAudioChannelClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{CC725B0B-A5E0-447A-96FB-89ABE201480A}") AVCaptureAudioChannel  : public Iosapi::Foundation::NSObject 
{
	virtual float __cdecl averagePowerLevel() = 0 ;
	virtual float __cdecl peakHoldLevel() = 0 ;
};

class PASCALIMPLEMENTATION TAVCaptureAudioChannel : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureAudioChannelClass,_di_AVCaptureAudioChannel>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureAudioChannelClass,_di_AVCaptureAudioChannel> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCaptureAudioChannel(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureAudioChannelClass,_di_AVCaptureAudioChannel>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCaptureAudioChannel() { }
	
};


__interface  INTERFACE_UUID("{084A4608-2F20-4AC0-A31A-C22D95FEC975}") AVCaptureConnectionClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{0C2188E9-4D0E-4CE0-BBEE-717D9821BB06}") AVCaptureConnection  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl audioChannels() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl inputPorts() = 0 ;
	virtual bool __cdecl isActive() = 0 ;
	virtual bool __cdecl isEnabled() = 0 ;
	virtual bool __cdecl isVideoMaxFrameDurationSupported() = 0 ;
	virtual bool __cdecl isVideoMinFrameDurationSupported() = 0 ;
	virtual bool __cdecl isVideoMirrored() = 0 ;
	virtual bool __cdecl isVideoMirroringSupported() = 0 ;
	virtual bool __cdecl isVideoOrientationSupported() = 0 ;
	virtual _di_AVCaptureOutput __cdecl output() = 0 ;
	virtual void __cdecl setEnabled(bool enabled) = 0 ;
	virtual void __cdecl setVideoMaxFrameDuration(Iosapi::Coremedia::CMTime videoMaxFrameDuration) = 0 ;
	virtual void __cdecl setVideoMinFrameDuration(Iosapi::Coremedia::CMTime videoMinFrameDuration) = 0 ;
	virtual void __cdecl setVideoMirrored(bool videoMirrored) = 0 ;
	virtual void __cdecl setVideoOrientation(long videoOrientation) = 0 ;
	virtual void __cdecl setVideoScaleAndCropFactor(double videoScaleAndCropFactor) = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl videoMaxFrameDuration() = 0 ;
	virtual double __cdecl videoMaxScaleAndCropFactor() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl videoMinFrameDuration() = 0 ;
	virtual long __cdecl videoOrientation() = 0 ;
	virtual double __cdecl videoScaleAndCropFactor() = 0 ;
};

class PASCALIMPLEMENTATION TAVCaptureConnection : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureConnectionClass,_di_AVCaptureConnection>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureConnectionClass,_di_AVCaptureConnection> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCaptureConnection(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureConnectionClass,_di_AVCaptureConnection>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCaptureConnection() { }
	
};


__interface  INTERFACE_UUID("{908820FB-6AAE-4C48-8432-8643493942FB}") AVVideoCompositionLayerInstructionClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{439E393B-CC03-4D21-93DE-C49E8F1FD44D}") AVVideoCompositionLayerInstruction  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl getOpacityRampForTime(Iosapi::Coremedia::CMTime time, System::PSingle startOpacity, System::PSingle endOpacity, Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	virtual bool __cdecl getTransformRampForTime(Iosapi::Coremedia::CMTime time, Iosapi::Coregraphics::CGAffineTransform startTransform, Iosapi::Coregraphics::CGAffineTransform endTransform, Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	virtual long __cdecl trackID() = 0 ;
};

class PASCALIMPLEMENTATION TAVVideoCompositionLayerInstruction : public Macapi::Objectivec::TOCGenericImport__2<_di_AVVideoCompositionLayerInstructionClass,_di_AVVideoCompositionLayerInstruction>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVVideoCompositionLayerInstructionClass,_di_AVVideoCompositionLayerInstruction> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVVideoCompositionLayerInstruction(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVVideoCompositionLayerInstructionClass,_di_AVVideoCompositionLayerInstruction>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVVideoCompositionLayerInstruction() { }
	
};


__interface  INTERFACE_UUID("{4FDDB9DA-F4C6-467F-B7A7-53C19D7A8415}") AVAudioPlayerClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{682F8E33-4146-45F9-8AF5-368B633C863F}") AVAudioPlayer  : public Iosapi::Foundation::NSObject 
{
	virtual float __cdecl averagePowerForChannel(unsigned long channelNumber) = 0 ;
	virtual double __cdecl currentTime() = 0 ;
	virtual Iosapi::Foundation::_di_NSData __cdecl data() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual double __cdecl deviceCurrentTime() = 0 ;
	virtual double __cdecl duration() = 0 ;
	virtual bool __cdecl enableRate() = 0 ;
	virtual void * __cdecl initWithContentsOfURL(Iosapi::Foundation::_di_NSURL url, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual void * __cdecl initWithData(Iosapi::Foundation::_di_NSData data, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl isMeteringEnabled() = 0 ;
	virtual bool __cdecl isPlaying() = 0 ;
	virtual unsigned long __cdecl numberOfChannels() = 0 ;
	virtual long __cdecl numberOfLoops() = 0 ;
	virtual float __cdecl pan() = 0 ;
	virtual void __cdecl pause() = 0 ;
	virtual float __cdecl peakPowerForChannel(unsigned long channelNumber) = 0 ;
	virtual bool __cdecl play() = 0 ;
	virtual bool __cdecl playAtTime(double time) = 0 ;
	virtual bool __cdecl prepareToPlay() = 0 ;
	virtual float __cdecl rate() = 0 ;
	virtual void __cdecl setCurrentTime(double currentTime) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setEnableRate(bool enableRate) = 0 ;
	virtual void __cdecl setMeteringEnabled(bool meteringEnabled) = 0 ;
	virtual void __cdecl setNumberOfLoops(long numberOfLoops) = 0 ;
	virtual void __cdecl setPan(float pan) = 0 ;
	virtual void __cdecl setRate(float rate) = 0 ;
	virtual void __cdecl setVolume(float volume) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl settings() = 0 ;
	virtual void __cdecl stop() = 0 ;
	virtual void __cdecl updateMeters() = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl url() = 0 ;
	virtual float __cdecl volume() = 0 ;
};

class PASCALIMPLEMENTATION TAVAudioPlayer : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAudioPlayerClass,_di_AVAudioPlayer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAudioPlayerClass,_di_AVAudioPlayer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAudioPlayer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAudioPlayerClass,_di_AVAudioPlayer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAudioPlayer() { }
	
};


__interface  INTERFACE_UUID("{C0E289AD-73E4-4B73-BC83-38B03D28B500}") AVAssetWriterInputPixelBufferAdaptorClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl assetWriterInputPixelBufferAdaptorWithAssetWriterInput(_di_AVAssetWriterInput input, Iosapi::Foundation::_di_NSDictionary sourcePixelBufferAttributes) = 0 ;
};

__interface  INTERFACE_UUID("{CDC41D77-0DB6-4373-B23F-3E02841E9B0A}") AVAssetWriterInputPixelBufferAdaptor  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl appendPixelBuffer(NativeInt pixelBuffer, Iosapi::Coremedia::CMTime withPresentationTime) = 0 ;
	virtual _di_AVAssetWriterInput __cdecl assetWriterInput() = 0 ;
	virtual void * __cdecl initWithAssetWriterInput(_di_AVAssetWriterInput input, Iosapi::Foundation::_di_NSDictionary sourcePixelBufferAttributes) = 0 ;
	virtual NativeInt __cdecl pixelBufferPool() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl sourcePixelBufferAttributes() = 0 ;
};

class PASCALIMPLEMENTATION TAVAssetWriterInputPixelBufferAdaptor : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetWriterInputPixelBufferAdaptorClass,_di_AVAssetWriterInputPixelBufferAdaptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetWriterInputPixelBufferAdaptorClass,_di_AVAssetWriterInputPixelBufferAdaptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAssetWriterInputPixelBufferAdaptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetWriterInputPixelBufferAdaptorClass,_di_AVAssetWriterInputPixelBufferAdaptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAssetWriterInputPixelBufferAdaptor() { }
	
};


__interface  INTERFACE_UUID("{9844CB93-8E9A-463B-97CA-32B3CB3C23B7}") AVAssetWriterInputClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl assetWriterInputWithMediaType(Iosapi::Foundation::_di_NSString mediaType, Iosapi::Foundation::_di_NSDictionary outputSettings) = 0 ;
};

__interface  INTERFACE_UUID("{AB33CDB6-FB68-4CEB-BA0B-CFEB676F6B61}") AVAssetWriterInput  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl appendSampleBuffer(void * sampleBuffer) = 0 ;
	virtual bool __cdecl expectsMediaDataInRealTime() = 0 ;
	virtual void * __cdecl initWithMediaType(Iosapi::Foundation::_di_NSString mediaType, Iosapi::Foundation::_di_NSDictionary outputSettings) = 0 ;
	virtual bool __cdecl isReadyForMoreMediaData() = 0 ;
	virtual void __cdecl markAsFinished() = 0 ;
	virtual int __cdecl mediaTimeScale() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl mediaType() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl metadata() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl outputSettings() = 0 ;
	virtual void __cdecl setExpectsMediaDataInRealTime(bool expectsMediaDataInRealTime) = 0 ;
	virtual void __cdecl setMediaTimeScale(int mediaTimeScale) = 0 ;
	virtual void __cdecl setMetadata(Iosapi::Foundation::_di_NSArray metadata) = 0 ;
	virtual void __cdecl setTransform(Iosapi::Coregraphics::CGAffineTransform transform) = 0 ;
	virtual Iosapi::Coregraphics::CGAffineTransform __cdecl transform() = 0 ;
};

class PASCALIMPLEMENTATION TAVAssetWriterInput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetWriterInputClass,_di_AVAssetWriterInput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetWriterInputClass,_di_AVAssetWriterInput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAssetWriterInput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetWriterInputClass,_di_AVAssetWriterInput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAssetWriterInput() { }
	
};


__interface  INTERFACE_UUID("{69AED0FA-3E1F-48C6-9DFA-CDFBC6739A03}") AVAudioMixClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{3330D086-B8BD-485F-91A1-DAF6C3A2D66B}") AVAudioMix  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl inputParameters() = 0 ;
};

class PASCALIMPLEMENTATION TAVAudioMix : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAudioMixClass,_di_AVAudioMix>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAudioMixClass,_di_AVAudioMix> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAudioMix(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAudioMixClass,_di_AVAudioMix>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAudioMix() { }
	
};


__interface  INTERFACE_UUID("{E6A5CA72-B920-4BF5-8E48-C6AFAD87CAC2}") AVAudioMixInputParametersClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{57A0CC56-0D02-49FD-B584-A448DDA8EB18}") AVAudioMixInputParameters  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl getVolumeRampForTime(Iosapi::Coremedia::CMTime time, System::PSingle startVolume, System::PSingle endVolume, Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	virtual long __cdecl trackID() = 0 ;
};

class PASCALIMPLEMENTATION TAVAudioMixInputParameters : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAudioMixInputParametersClass,_di_AVAudioMixInputParameters>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAudioMixInputParametersClass,_di_AVAudioMixInputParameters> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAudioMixInputParameters(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAudioMixInputParametersClass,_di_AVAudioMixInputParameters>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAudioMixInputParameters() { }
	
};


__interface  INTERFACE_UUID("{9525AF18-DBB3-4B26-B671-B14DD6F34BB8}") AVMutableVideoCompositionLayerInstructionClass  : public AVVideoCompositionLayerInstructionClass 
{
	virtual void * __cdecl videoCompositionLayerInstruction() = 0 ;
	virtual void * __cdecl videoCompositionLayerInstructionWithAssetTrack(_di_AVAssetTrack track) = 0 ;
};

__interface  INTERFACE_UUID("{E4D14916-427D-48CA-B0F6-FBAD402446D6}") AVMutableVideoCompositionLayerInstruction  : public AVVideoCompositionLayerInstruction 
{
	virtual void __cdecl setOpacity(float opacity, Iosapi::Coremedia::CMTime atTime) = 0 ;
	virtual void __cdecl setOpacityRampFromStartOpacity(float startOpacity, float toEndOpacity, Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	virtual void __cdecl setTrackID(long trackID) = 0 ;
	virtual void __cdecl setTransform(Iosapi::Coregraphics::CGAffineTransform transform, Iosapi::Coremedia::CMTime atTime) = 0 ;
	virtual void __cdecl setTransformRampFromStartTransform(Iosapi::Coregraphics::CGAffineTransform startTransform, Iosapi::Coregraphics::CGAffineTransform toEndTransform, Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	HIDESBASE virtual long __cdecl trackID() = 0 ;
};

class PASCALIMPLEMENTATION TAVMutableVideoCompositionLayerInstruction : public Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableVideoCompositionLayerInstructionClass,_di_AVMutableVideoCompositionLayerInstruction>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableVideoCompositionLayerInstructionClass,_di_AVMutableVideoCompositionLayerInstruction> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVMutableVideoCompositionLayerInstruction(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableVideoCompositionLayerInstructionClass,_di_AVMutableVideoCompositionLayerInstruction>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVMutableVideoCompositionLayerInstruction() { }
	
};


__interface  INTERFACE_UUID("{BCD7DCDC-37D7-45D0-B428-49F1ACE35DCE}") AVURLAssetClass  : public AVAssetClass 
{
	virtual void * __cdecl URLAssetWithURL(Iosapi::Foundation::_di_NSURL URL, Iosapi::Foundation::_di_NSDictionary options) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl audiovisualMIMETypes() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl audiovisualTypes() = 0 ;
	virtual bool __cdecl isPlayableExtendedMIMEType(Iosapi::Foundation::_di_NSString extendedMIMEType) = 0 ;
};

__interface  INTERFACE_UUID("{6CEBF29C-C73E-4481-9F37-BA0FD0178F31}") AVURLAsset  : public AVAsset 
{
	virtual Iosapi::Foundation::_di_NSURL __cdecl URL() = 0 ;
	virtual _di_AVAssetTrack __cdecl compatibleTrackForCompositionTrack(_di_AVCompositionTrack compositionTrack) = 0 ;
	virtual void * __cdecl initWithURL(Iosapi::Foundation::_di_NSURL URL, Iosapi::Foundation::_di_NSDictionary options) = 0 ;
};

class PASCALIMPLEMENTATION TAVURLAsset : public Macapi::Objectivec::TOCGenericImport__2<_di_AVURLAssetClass,_di_AVURLAsset>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVURLAssetClass,_di_AVURLAsset> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVURLAsset(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVURLAssetClass,_di_AVURLAsset>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVURLAsset() { }
	
};


__interface  INTERFACE_UUID("{0FF39B64-E84C-4A46-A442-20E0E10F8E61}") AVCaptureStillImageOutputClass  : public AVCaptureOutputClass 
{
	virtual Iosapi::Foundation::_di_NSData __cdecl jpegStillImageNSDataRepresentation(void * jpegSampleBuffer) = 0 ;
};

__interface  INTERFACE_UUID("{E0B5F87B-AFA2-4AF2-AA36-AA4E5480A9AC}") AVCaptureStillImageOutput  : public AVCaptureOutput 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl availableImageDataCVPixelFormatTypes() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl availableImageDataCodecTypes() = 0 ;
	virtual bool __cdecl isCapturingStillImage() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl outputSettings() = 0 ;
	virtual void __cdecl setOutputSettings(Iosapi::Foundation::_di_NSDictionary outputSettings) = 0 ;
};

class PASCALIMPLEMENTATION TAVCaptureStillImageOutput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureStillImageOutputClass,_di_AVCaptureStillImageOutput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureStillImageOutputClass,_di_AVCaptureStillImageOutput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCaptureStillImageOutput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureStillImageOutputClass,_di_AVCaptureStillImageOutput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCaptureStillImageOutput() { }
	
};


__interface  INTERFACE_UUID("{CF6368B5-6B7C-4BB8-A540-C0DE16272551}") AVCaptureFileOutputClass  : public AVCaptureOutputClass 
{
	
};

__interface  INTERFACE_UUID("{F79864F4-58B8-4F95-9311-C981CD2E6B8D}") AVCaptureFileOutput  : public AVCaptureOutput 
{
	virtual bool __cdecl isRecording() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl maxRecordedDuration() = 0 ;
	virtual __int64 __cdecl maxRecordedFileSize() = 0 ;
	virtual __int64 __cdecl minFreeDiskSpaceLimit() = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl outputFileURL() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl recordedDuration() = 0 ;
	virtual __int64 __cdecl recordedFileSize() = 0 ;
	virtual void __cdecl setMaxRecordedDuration(Iosapi::Coremedia::CMTime maxRecordedDuration) = 0 ;
	virtual void __cdecl setMaxRecordedFileSize(__int64 maxRecordedFileSize) = 0 ;
	virtual void __cdecl setMinFreeDiskSpaceLimit(__int64 minFreeDiskSpaceLimit) = 0 ;
	virtual void __cdecl startRecordingToOutputFileURL(Iosapi::Foundation::_di_NSURL outputFileURL, void * recordingDelegate) = 0 ;
	virtual void __cdecl stopRecording() = 0 ;
};

class PASCALIMPLEMENTATION TAVCaptureFileOutput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureFileOutputClass,_di_AVCaptureFileOutput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureFileOutputClass,_di_AVCaptureFileOutput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCaptureFileOutput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureFileOutputClass,_di_AVCaptureFileOutput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCaptureFileOutput() { }
	
};


__interface  INTERFACE_UUID("{AA628061-1E38-49A9-99AE-960C9E9D5647}") AVCaptureFileOutputRecordingDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl captureOutput(_di_AVCaptureFileOutput captureOutput, Iosapi::Foundation::_di_NSURL didFinishRecordingToOutputFileAtURL, Iosapi::Foundation::_di_NSArray fromConnections, Iosapi::Foundation::_di_NSError error) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{5DF58937-B6D5-4021-A03A-FF97737C918C}") AVCompositionClass  : public AVAssetClass 
{
	
};

__interface  INTERFACE_UUID("{44C3E72F-B677-4B28-A863-C1CF70D6A721}") AVComposition  : public AVAsset 
{
	HIDESBASE virtual Iosapi::Foundation::NSSize __cdecl naturalSize() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSArray __cdecl tracks() = 0 ;
};

class PASCALIMPLEMENTATION TAVComposition : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCompositionClass,_di_AVComposition>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCompositionClass,_di_AVComposition> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVComposition(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCompositionClass,_di_AVComposition>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVComposition() { }
	
};


__interface  INTERFACE_UUID("{4CA97D19-AE08-4A6B-B6DE-9DA91E4072C3}") AVCaptureVideoDataOutputClass  : public AVCaptureOutputClass 
{
	
};

__interface  INTERFACE_UUID("{263A3E99-CBF1-4D04-85FB-078B8C7E4670}") AVCaptureVideoDataOutput  : public AVCaptureOutput 
{
	virtual bool __cdecl alwaysDiscardsLateVideoFrames() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl availableVideoCVPixelFormatTypes() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl availableVideoCodecTypes() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl minFrameDuration() = 0 ;
	virtual NativeInt __cdecl sampleBufferCallbackQueue() = 0 ;
	virtual void * __cdecl sampleBufferDelegate() = 0 ;
	virtual void __cdecl setAlwaysDiscardsLateVideoFrames(bool alwaysDiscardsLateVideoFrames) = 0 ;
	virtual void __cdecl setMinFrameDuration(Iosapi::Coremedia::CMTime minFrameDuration) = 0 ;
	virtual void __cdecl setSampleBufferDelegate(void * sampleBufferDelegate, NativeInt queue) = 0 ;
	virtual void __cdecl setVideoSettings(Iosapi::Foundation::_di_NSDictionary videoSettings) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl videoSettings() = 0 ;
};

class PASCALIMPLEMENTATION TAVCaptureVideoDataOutput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureVideoDataOutputClass,_di_AVCaptureVideoDataOutput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureVideoDataOutputClass,_di_AVCaptureVideoDataOutput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCaptureVideoDataOutput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureVideoDataOutputClass,_di_AVCaptureVideoDataOutput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCaptureVideoDataOutput() { }
	
};


__interface  INTERFACE_UUID("{BC4EABBE-F21F-4592-93B0-0C40415E4A9A}") AVCaptureVideoDataOutputSampleBufferDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl captureOutput(_di_AVCaptureOutput captureOutput, void * didOutputSampleBuffer, _di_AVCaptureConnection fromConnection) = 0 ;
};

__interface  INTERFACE_UUID("{4AFFA0C4-F4AE-42D4-9006-B823E204C3A6}") AVCaptureDeviceInputClass  : public AVCaptureInputClass 
{
	virtual void * __cdecl deviceInputWithDevice(_di_AVCaptureDevice device, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
};

__interface  INTERFACE_UUID("{804546D7-499D-4D84-A08C-26D90C78DA42}") AVCaptureDeviceInput  : public AVCaptureInput 
{
	virtual _di_AVCaptureDevice __cdecl device() = 0 ;
	virtual void * __cdecl initWithDevice(_di_AVCaptureDevice device, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
};

class PASCALIMPLEMENTATION TAVCaptureDeviceInput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureDeviceInputClass,_di_AVCaptureDeviceInput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureDeviceInputClass,_di_AVCaptureDeviceInput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCaptureDeviceInput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureDeviceInputClass,_di_AVCaptureDeviceInput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCaptureDeviceInput() { }
	
};


__interface  INTERFACE_UUID("{9C741E36-FA2A-4298-BE33-FE66359F2034}") AVAssetReaderTrackOutputClass  : public AVAssetReaderOutputClass 
{
	virtual void * __cdecl assetReaderTrackOutputWithTrack(_di_AVAssetTrack track, Iosapi::Foundation::_di_NSDictionary outputSettings) = 0 ;
};

__interface  INTERFACE_UUID("{2D0B77A9-9AEA-491C-A7FB-AC5CC101DF23}") AVAssetReaderTrackOutput  : public AVAssetReaderOutput 
{
	virtual void * __cdecl initWithTrack(_di_AVAssetTrack track, Iosapi::Foundation::_di_NSDictionary outputSettings) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl outputSettings() = 0 ;
	virtual _di_AVAssetTrack __cdecl track() = 0 ;
};

class PASCALIMPLEMENTATION TAVAssetReaderTrackOutput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetReaderTrackOutputClass,_di_AVAssetReaderTrackOutput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetReaderTrackOutputClass,_di_AVAssetReaderTrackOutput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAssetReaderTrackOutput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetReaderTrackOutputClass,_di_AVAssetReaderTrackOutput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAssetReaderTrackOutput() { }
	
};


__interface  INTERFACE_UUID("{8FBC4B55-BDC0-48E1-AA32-17A095A6A386}") AVAssetReaderAudioMixOutputClass  : public AVAssetReaderOutputClass 
{
	virtual void * __cdecl assetReaderAudioMixOutputWithAudioTracks(Iosapi::Foundation::_di_NSArray audioTracks, Iosapi::Foundation::_di_NSDictionary audioSettings) = 0 ;
};

__interface  INTERFACE_UUID("{098148DA-AD09-47F6-95F9-B0B0344A7738}") AVAssetReaderAudioMixOutput  : public AVAssetReaderOutput 
{
	virtual _di_AVAudioMix __cdecl audioMix() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl audioSettings() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl audioTracks() = 0 ;
	virtual void * __cdecl initWithAudioTracks(Iosapi::Foundation::_di_NSArray audioTracks, Iosapi::Foundation::_di_NSDictionary audioSettings) = 0 ;
	virtual void __cdecl setAudioMix(_di_AVAudioMix audioMix) = 0 ;
};

class PASCALIMPLEMENTATION TAVAssetReaderAudioMixOutput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetReaderAudioMixOutputClass,_di_AVAssetReaderAudioMixOutput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetReaderAudioMixOutputClass,_di_AVAssetReaderAudioMixOutput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAssetReaderAudioMixOutput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetReaderAudioMixOutputClass,_di_AVAssetReaderAudioMixOutput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAssetReaderAudioMixOutput() { }
	
};


__interface  INTERFACE_UUID("{9CF6D132-301A-4ADC-B2B6-E5A5EFD3FF9B}") AVCaptureAudioDataOutputClass  : public AVCaptureOutputClass 
{
	
};

__interface  INTERFACE_UUID("{A8EFF619-2C77-4C43-89C1-E5701BF401AE}") AVCaptureAudioDataOutput  : public AVCaptureOutput 
{
	virtual NativeInt __cdecl sampleBufferCallbackQueue() = 0 ;
	virtual void * __cdecl sampleBufferDelegate() = 0 ;
	virtual void __cdecl setSampleBufferDelegate(void * sampleBufferDelegate, NativeInt queue) = 0 ;
};

class PASCALIMPLEMENTATION TAVCaptureAudioDataOutput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureAudioDataOutputClass,_di_AVCaptureAudioDataOutput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureAudioDataOutputClass,_di_AVCaptureAudioDataOutput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCaptureAudioDataOutput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureAudioDataOutputClass,_di_AVCaptureAudioDataOutput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCaptureAudioDataOutput() { }
	
};


__interface  INTERFACE_UUID("{869452E8-CE75-498B-8941-3379C56C1217}") AVAssetReaderVideoCompositionOutputClass  : public AVAssetReaderOutputClass 
{
	virtual void * __cdecl assetReaderVideoCompositionOutputWithVideoTracks(Iosapi::Foundation::_di_NSArray videoTracks, Iosapi::Foundation::_di_NSDictionary videoSettings) = 0 ;
};

__interface  INTERFACE_UUID("{9FB73616-F15C-4F19-8EC3-4AEB837AB6E8}") AVAssetReaderVideoCompositionOutput  : public AVAssetReaderOutput 
{
	virtual void * __cdecl initWithVideoTracks(Iosapi::Foundation::_di_NSArray videoTracks, Iosapi::Foundation::_di_NSDictionary videoSettings) = 0 ;
	virtual void __cdecl setVideoComposition(_di_AVVideoComposition videoComposition) = 0 ;
	virtual _di_AVVideoComposition __cdecl videoComposition() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl videoSettings() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl videoTracks() = 0 ;
};

class PASCALIMPLEMENTATION TAVAssetReaderVideoCompositionOutput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetReaderVideoCompositionOutputClass,_di_AVAssetReaderVideoCompositionOutput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetReaderVideoCompositionOutputClass,_di_AVAssetReaderVideoCompositionOutput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVAssetReaderVideoCompositionOutput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVAssetReaderVideoCompositionOutputClass,_di_AVAssetReaderVideoCompositionOutput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVAssetReaderVideoCompositionOutput() { }
	
};


__interface  INTERFACE_UUID("{8CDE195A-1BE5-42A9-856A-396B2F965E39}") AVCompositionTrackClass  : public AVAssetTrackClass 
{
	
};

__interface  INTERFACE_UUID("{C2EBC4AD-6629-4D45-9DC5-E1A6438FDCA1}") AVCompositionTrack  : public AVAssetTrack 
{
	HIDESBASE virtual Iosapi::Foundation::_di_NSArray __cdecl segments() = 0 ;
};

class PASCALIMPLEMENTATION TAVCompositionTrack : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCompositionTrackClass,_di_AVCompositionTrack>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCompositionTrackClass,_di_AVCompositionTrack> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCompositionTrack(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCompositionTrackClass,_di_AVCompositionTrack>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCompositionTrack() { }
	
};


__interface  INTERFACE_UUID("{4269E1FD-E566-4305-9E6F-6F00A09B9633}") AVMutableVideoCompositionClass  : public AVVideoCompositionClass 
{
	virtual void * __cdecl videoComposition() = 0 ;
};

__interface  INTERFACE_UUID("{3DA3DD19-7D96-4EA8-A568-BB782C9EABE9}") AVMutableVideoComposition  : public AVVideoComposition 
{
	HIDESBASE virtual _di_AVVideoCompositionCoreAnimationTool __cdecl animationTool() = 0 ;
	HIDESBASE virtual Iosapi::Coremedia::CMTime __cdecl frameDuration() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSArray __cdecl instructions() = 0 ;
	HIDESBASE virtual float __cdecl renderScale() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::NSSize __cdecl renderSize() = 0 ;
	virtual void __cdecl setAnimationTool(_di_AVVideoCompositionCoreAnimationTool animationTool) = 0 ;
	virtual void __cdecl setFrameDuration(Iosapi::Coremedia::CMTime frameDuration) = 0 ;
	virtual void __cdecl setInstructions(Iosapi::Foundation::_di_NSArray instructions) = 0 ;
	virtual void __cdecl setRenderScale(float renderScale) = 0 ;
	virtual void __cdecl setRenderSize(Iosapi::Foundation::NSSize renderSize) = 0 ;
};

class PASCALIMPLEMENTATION TAVMutableVideoComposition : public Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableVideoCompositionClass,_di_AVMutableVideoComposition>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableVideoCompositionClass,_di_AVMutableVideoComposition> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVMutableVideoComposition(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableVideoCompositionClass,_di_AVMutableVideoComposition>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVMutableVideoComposition() { }
	
};


__interface  INTERFACE_UUID("{2D6F6F7A-57FB-4ED3-9846-02C74D90A94C}") AVMutableTimedMetadataGroupClass  : public AVTimedMetadataGroupClass 
{
	
};

__interface  INTERFACE_UUID("{C3F8CA9D-26F4-413B-98C2-4578D3DAC2F1}") AVMutableTimedMetadataGroup  : public AVTimedMetadataGroup 
{
	HIDESBASE virtual Iosapi::Foundation::_di_NSArray __cdecl items() = 0 ;
	virtual void __cdecl setItems(Iosapi::Foundation::_di_NSArray items) = 0 ;
	virtual void __cdecl setTimeRange(Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	HIDESBASE virtual Iosapi::Coremedia::CMTimeRange __cdecl timeRange() = 0 ;
};

class PASCALIMPLEMENTATION TAVMutableTimedMetadataGroup : public Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableTimedMetadataGroupClass,_di_AVMutableTimedMetadataGroup>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableTimedMetadataGroupClass,_di_AVMutableTimedMetadataGroup> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVMutableTimedMetadataGroup(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableTimedMetadataGroupClass,_di_AVMutableTimedMetadataGroup>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVMutableTimedMetadataGroup() { }
	
};


__interface  INTERFACE_UUID("{1FD2B927-0ED5-40A6-A104-235F0FF9DEDD}") AVMutableMetadataItemClass  : public AVMetadataItemClass 
{
	virtual void * __cdecl metadataItem() = 0 ;
};

__interface  INTERFACE_UUID("{0B57E0FD-6591-4C6A-A8C4-B9A0A571FCB7}") AVMutableMetadataItem  : public AVMetadataItem 
{
	HIDESBASE virtual Iosapi::Coremedia::CMTime __cdecl duration() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSDictionary __cdecl extraAttributes() = 0 ;
	HIDESBASE virtual void * __cdecl key() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSString __cdecl keySpace() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSLocale __cdecl locale() = 0 ;
	virtual void __cdecl setDuration(Iosapi::Coremedia::CMTime duration) = 0 ;
	virtual void __cdecl setExtraAttributes(Iosapi::Foundation::_di_NSDictionary extraAttributes) = 0 ;
	virtual void __cdecl setKey(void * key) = 0 ;
	virtual void __cdecl setKeySpace(Iosapi::Foundation::_di_NSString keySpace) = 0 ;
	virtual void __cdecl setLocale(Iosapi::Foundation::_di_NSLocale locale) = 0 ;
	virtual void __cdecl setTime(Iosapi::Coremedia::CMTime time) = 0 ;
	virtual void __cdecl setValue(void * value) = 0 ;
	HIDESBASE virtual Iosapi::Coremedia::CMTime __cdecl time() = 0 ;
	HIDESBASE virtual void * __cdecl value() = 0 ;
};

class PASCALIMPLEMENTATION TAVMutableMetadataItem : public Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableMetadataItemClass,_di_AVMutableMetadataItem>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableMetadataItemClass,_di_AVMutableMetadataItem> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVMutableMetadataItem(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableMetadataItemClass,_di_AVMutableMetadataItem>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVMutableMetadataItem() { }
	
};


__interface  INTERFACE_UUID("{82B53FB8-7B8D-406F-9AFA-59876114874B}") AVMutableVideoCompositionInstructionClass  : public AVVideoCompositionInstructionClass 
{
	virtual void * __cdecl videoCompositionInstruction() = 0 ;
};

__interface  INTERFACE_UUID("{EC367C09-914D-484E-9FF4-610A3CC75365}") AVMutableVideoCompositionInstruction  : public AVVideoCompositionInstruction 
{
	HIDESBASE virtual void * __cdecl backgroundColor() = 0 ;
	HIDESBASE virtual bool __cdecl enablePostProcessing() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSArray __cdecl layerInstructions() = 0 ;
	HIDESBASE virtual void __cdecl setBackgroundColor(void * backgroundColor) = 0 ;
	virtual void __cdecl setEnablePostProcessing(bool enablePostProcessing) = 0 ;
	virtual void __cdecl setLayerInstructions(Iosapi::Foundation::_di_NSArray layerInstructions) = 0 ;
	virtual void __cdecl setTimeRange(Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	HIDESBASE virtual Iosapi::Coremedia::CMTimeRange __cdecl timeRange() = 0 ;
};

class PASCALIMPLEMENTATION TAVMutableVideoCompositionInstruction : public Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableVideoCompositionInstructionClass,_di_AVMutableVideoCompositionInstruction>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableVideoCompositionInstructionClass,_di_AVMutableVideoCompositionInstruction> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVMutableVideoCompositionInstruction(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableVideoCompositionInstructionClass,_di_AVMutableVideoCompositionInstruction>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVMutableVideoCompositionInstruction() { }
	
};


__interface  INTERFACE_UUID("{FE0CA707-FE80-407C-AE92-ABED9B818BBA}") AVCompositionTrackSegmentClass  : public AVAssetTrackSegmentClass 
{
	virtual void * __cdecl compositionTrackSegmentWithTimeRange(Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	virtual void * __cdecl compositionTrackSegmentWithURL(Iosapi::Foundation::_di_NSURL URL, long trackID, Iosapi::Coremedia::CMTimeRange sourceTimeRange, Iosapi::Coremedia::CMTimeRange targetTimeRange) = 0 ;
};

__interface  INTERFACE_UUID("{E4E4506A-7AA1-4FB6-8A6D-317516BEC05E}") AVCompositionTrackSegment  : public AVAssetTrackSegment 
{
	virtual void * __cdecl initWithTimeRange(Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	virtual void * __cdecl initWithURL(Iosapi::Foundation::_di_NSURL URL, long trackID, Iosapi::Coremedia::CMTimeRange sourceTimeRange, Iosapi::Coremedia::CMTimeRange targetTimeRange) = 0 ;
	HIDESBASE virtual bool __cdecl isEmpty() = 0 ;
	virtual long __cdecl sourceTrackID() = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl sourceURL() = 0 ;
};

class PASCALIMPLEMENTATION TAVCompositionTrackSegment : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCompositionTrackSegmentClass,_di_AVCompositionTrackSegment>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCompositionTrackSegmentClass,_di_AVCompositionTrackSegment> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCompositionTrackSegment(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCompositionTrackSegmentClass,_di_AVCompositionTrackSegment>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCompositionTrackSegment() { }
	
};


__interface  INTERFACE_UUID("{0B46ACE2-0232-4EF1-9070-0388CEE7FAFA}") AVMutableAudioMixClass  : public AVAudioMixClass 
{
	virtual void * __cdecl audioMix() = 0 ;
};

__interface  INTERFACE_UUID("{197E621B-9CD3-4449-9BAB-A0B147677C95}") AVMutableAudioMix  : public AVAudioMix 
{
	HIDESBASE virtual Iosapi::Foundation::_di_NSArray __cdecl inputParameters() = 0 ;
	virtual void __cdecl setInputParameters(Iosapi::Foundation::_di_NSArray inputParameters) = 0 ;
};

class PASCALIMPLEMENTATION TAVMutableAudioMix : public Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableAudioMixClass,_di_AVMutableAudioMix>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableAudioMixClass,_di_AVMutableAudioMix> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVMutableAudioMix(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableAudioMixClass,_di_AVMutableAudioMix>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVMutableAudioMix() { }
	
};


__interface  INTERFACE_UUID("{3DD9E0B8-C7B7-43A5-ABBD-9F54C0932569}") AVMutableAudioMixInputParametersClass  : public AVAudioMixInputParametersClass 
{
	virtual void * __cdecl audioMixInputParameters() = 0 ;
	virtual void * __cdecl audioMixInputParametersWithTrack(_di_AVAssetTrack track) = 0 ;
};

__interface  INTERFACE_UUID("{A2B37032-3C1D-4F9B-B6C2-30235686CFF8}") AVMutableAudioMixInputParameters  : public AVAudioMixInputParameters 
{
	virtual void __cdecl setTrackID(long trackID) = 0 ;
	virtual void __cdecl setVolume(float volume, Iosapi::Coremedia::CMTime atTime) = 0 ;
	virtual void __cdecl setVolumeRampFromStartVolume(float startVolume, float toEndVolume, Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	HIDESBASE virtual long __cdecl trackID() = 0 ;
};

class PASCALIMPLEMENTATION TAVMutableAudioMixInputParameters : public Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableAudioMixInputParametersClass,_di_AVMutableAudioMixInputParameters>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableAudioMixInputParametersClass,_di_AVMutableAudioMixInputParameters> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVMutableAudioMixInputParameters(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableAudioMixInputParametersClass,_di_AVMutableAudioMixInputParameters>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVMutableAudioMixInputParameters() { }
	
};


__interface  INTERFACE_UUID("{A26188D8-366C-4099-8076-61D74602DCE9}") AVCaptureMovieFileOutputClass  : public AVCaptureFileOutputClass 
{
	
};

__interface  INTERFACE_UUID("{7A06F5FC-3105-4DB1-BC97-D695DFBD250E}") AVCaptureMovieFileOutput  : public AVCaptureFileOutput 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl metadata() = 0 ;
	virtual Iosapi::Coremedia::CMTime __cdecl movieFragmentInterval() = 0 ;
	virtual void __cdecl setMetadata(Iosapi::Foundation::_di_NSArray metadata) = 0 ;
	virtual void __cdecl setMovieFragmentInterval(Iosapi::Coremedia::CMTime movieFragmentInterval) = 0 ;
};

class PASCALIMPLEMENTATION TAVCaptureMovieFileOutput : public Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureMovieFileOutputClass,_di_AVCaptureMovieFileOutput>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureMovieFileOutputClass,_di_AVCaptureMovieFileOutput> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVCaptureMovieFileOutput(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVCaptureMovieFileOutputClass,_di_AVCaptureMovieFileOutput>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVCaptureMovieFileOutput() { }
	
};


__interface  INTERFACE_UUID("{0A9AFAE1-587E-4BC3-84B8-628B60730380}") AVMutableCompositionClass  : public AVCompositionClass 
{
	virtual void * __cdecl composition() = 0 ;
};

__interface  INTERFACE_UUID("{03396B84-10CF-4070-91F1-5285014F163B}") AVMutableComposition  : public AVComposition 
{
	virtual _di_AVMutableCompositionTrack __cdecl addMutableTrackWithMediaType(Iosapi::Foundation::_di_NSString mediaType, long preferredTrackID) = 0 ;
	virtual void __cdecl insertEmptyTimeRange(Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	virtual bool __cdecl insertTimeRange(Iosapi::Coremedia::CMTimeRange timeRange, _di_AVAsset ofAsset, Iosapi::Coremedia::CMTime atTime, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_AVMutableCompositionTrack __cdecl mutableTrackCompatibleWithTrack(_di_AVAssetTrack track) = 0 ;
	HIDESBASE virtual Iosapi::Foundation::NSSize __cdecl naturalSize() = 0 ;
	virtual void __cdecl removeTimeRange(Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	virtual void __cdecl removeTrack(_di_AVCompositionTrack track) = 0 ;
	virtual void __cdecl scaleTimeRange(Iosapi::Coremedia::CMTimeRange timeRange, Iosapi::Coremedia::CMTime toDuration) = 0 ;
	virtual void __cdecl setNaturalSize(Iosapi::Foundation::NSSize naturalSize) = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSArray __cdecl tracks() = 0 ;
};

class PASCALIMPLEMENTATION TAVMutableComposition : public Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableCompositionClass,_di_AVMutableComposition>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableCompositionClass,_di_AVMutableComposition> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVMutableComposition(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableCompositionClass,_di_AVMutableComposition>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVMutableComposition() { }
	
};


__interface  INTERFACE_UUID("{9704C005-4995-4ECE-B575-A380FE22F4F9}") AVMutableCompositionTrackClass  : public AVCompositionTrackClass 
{
	
};

__interface  INTERFACE_UUID("{DA2D82C9-3500-42A5-8B0E-7D892689E227}") AVMutableCompositionTrack  : public AVCompositionTrack 
{
	HIDESBASE virtual Iosapi::Foundation::_di_NSString __cdecl extendedLanguageTag() = 0 ;
	virtual void __cdecl insertEmptyTimeRange(Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	virtual bool __cdecl insertTimeRange(Iosapi::Coremedia::CMTimeRange timeRange, _di_AVAssetTrack ofTrack, Iosapi::Coremedia::CMTime atTime, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl insertTimeRanges(Iosapi::Foundation::_di_NSArray timeRanges, Iosapi::Foundation::_di_NSArray ofTracks, Iosapi::Coremedia::CMTime atTime, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSString __cdecl languageCode() = 0 ;
	HIDESBASE virtual int __cdecl naturalTimeScale() = 0 ;
	HIDESBASE virtual Iosapi::Coregraphics::CGAffineTransform __cdecl preferredTransform() = 0 ;
	HIDESBASE virtual float __cdecl preferredVolume() = 0 ;
	virtual void __cdecl removeTimeRange(Iosapi::Coremedia::CMTimeRange timeRange) = 0 ;
	virtual void __cdecl scaleTimeRange(Iosapi::Coremedia::CMTimeRange timeRange, Iosapi::Coremedia::CMTime toDuration) = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSArray __cdecl segments() = 0 ;
	virtual void __cdecl setExtendedLanguageTag(Iosapi::Foundation::_di_NSString extendedLanguageTag) = 0 ;
	virtual void __cdecl setLanguageCode(Iosapi::Foundation::_di_NSString languageCode) = 0 ;
	virtual void __cdecl setNaturalTimeScale(int naturalTimeScale) = 0 ;
	virtual void __cdecl setPreferredTransform(Iosapi::Coregraphics::CGAffineTransform preferredTransform) = 0 ;
	virtual void __cdecl setPreferredVolume(float preferredVolume) = 0 ;
	virtual void __cdecl setSegments(Iosapi::Foundation::_di_NSArray segments) = 0 ;
	virtual bool __cdecl validateTrackSegments(Iosapi::Foundation::_di_NSArray trackSegments, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
};

class PASCALIMPLEMENTATION TAVMutableCompositionTrack : public Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableCompositionTrackClass,_di_AVMutableCompositionTrack>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableCompositionTrackClass,_di_AVMutableCompositionTrack> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TAVMutableCompositionTrack(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_AVMutableCompositionTrackClass,_di_AVMutableCompositionTrack>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TAVMutableCompositionTrack() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 AVAssetExportSessionStatusCancelled = System::Int8(0x5);
static constexpr System::Int8 AVAssetExportSessionStatusCompleted = System::Int8(0x3);
static constexpr System::Int8 AVAssetExportSessionStatusExporting = System::Int8(0x2);
static constexpr System::Int8 AVAssetExportSessionStatusFailed = System::Int8(0x4);
static constexpr System::Int8 AVAssetExportSessionStatusUnknown = System::Int8(0x0);
static constexpr System::Int8 AVAssetExportSessionStatusWaiting = System::Int8(0x1);
static constexpr System::Int8 AVAssetImageGeneratorCancelled = System::Int8(0x2);
static constexpr System::Int8 AVAssetImageGeneratorFailed = System::Int8(0x1);
static constexpr System::Int8 AVAssetImageGeneratorSucceeded = System::Int8(0x0);
static constexpr System::Int8 AVAssetReaderStatusCancelled = System::Int8(0x4);
static constexpr System::Int8 AVAssetReaderStatusCompleted = System::Int8(0x2);
static constexpr System::Int8 AVAssetReaderStatusFailed = System::Int8(0x3);
static constexpr System::Int8 AVAssetReaderStatusReading = System::Int8(0x1);
static constexpr System::Int8 AVAssetReaderStatusUnknown = System::Int8(0x0);
static constexpr System::Word AVAssetReferenceRestrictionForbidAll = System::Word(0xffff);
static constexpr System::Int8 AVAssetReferenceRestrictionForbidCrossSiteReference = System::Int8(0x4);
static constexpr System::Int8 AVAssetReferenceRestrictionForbidLocalReferenceToLocal = System::Int8(0x8);
static constexpr System::Int8 AVAssetReferenceRestrictionForbidLocalReferenceToRemote = System::Int8(0x2);
static constexpr System::Int8 AVAssetReferenceRestrictionForbidNone = System::Int8(0x0);
static constexpr System::Int8 AVAssetReferenceRestrictionForbidRemoteReferenceToLocal = System::Int8(0x1);
static constexpr System::Int8 AVAssetWriterStatusCancelled = System::Int8(0x4);
static constexpr System::Int8 AVAssetWriterStatusCompleted = System::Int8(0x2);
static constexpr System::Int8 AVAssetWriterStatusFailed = System::Int8(0x3);
static constexpr System::Int8 AVAssetWriterStatusUnknown = System::Int8(0x0);
static constexpr System::Int8 AVAssetWriterStatusWriting = System::Int8(0x1);
static constexpr System::Int8 AVAudioQualityHigh = System::Int8(0x60);
static constexpr System::Int8 AVAudioQualityLow = System::Int8(0x20);
static constexpr System::Int8 AVAudioQualityMax = System::Int8(0x7f);
static constexpr System::Int8 AVAudioQualityMedium = System::Int8(0x40);
static constexpr System::Int8 AVAudioQualityMin = System::Int8(0x0);
static constexpr System::Int8 AVAudioSessionInterruptionFlags_ShouldResume = System::Int8(0x1);
static constexpr System::Int8 AVAudioSessionSetActiveFlags_NotifyOthersOnDeactivation = System::Int8(0x1);
static constexpr System::Int8 AVCaptureDevicePositionBack = System::Int8(0x1);
static constexpr System::Int8 AVCaptureDevicePositionFront = System::Int8(0x2);
static constexpr System::Int8 AVCaptureExposureModeAutoExpose = System::Int8(0x1);
static constexpr System::Int8 AVCaptureExposureModeContinuousAutoExposure = System::Int8(0x2);
static constexpr System::Int8 AVCaptureExposureModeLocked = System::Int8(0x0);
static constexpr System::Int8 AVCaptureFlashModeAuto = System::Int8(0x2);
static constexpr System::Int8 AVCaptureFlashModeOff = System::Int8(0x0);
static constexpr System::Int8 AVCaptureFlashModeOn = System::Int8(0x1);
static constexpr System::Int8 AVCaptureFocusModeAutoFocus = System::Int8(0x1);
static constexpr System::Int8 AVCaptureFocusModeContinuousAutoFocus = System::Int8(0x2);
static constexpr System::Int8 AVCaptureFocusModeLocked = System::Int8(0x0);
static constexpr System::Int8 AVCaptureTorchModeAuto = System::Int8(0x2);
static constexpr System::Int8 AVCaptureTorchModeOff = System::Int8(0x0);
static constexpr System::Int8 AVCaptureTorchModeOn = System::Int8(0x1);
static constexpr System::Int8 AVCaptureVideoOrientationLandscapeLeft = System::Int8(0x4);
static constexpr System::Int8 AVCaptureVideoOrientationLandscapeRight = System::Int8(0x3);
static constexpr System::Int8 AVCaptureVideoOrientationPortrait = System::Int8(0x1);
static constexpr System::Int8 AVCaptureVideoOrientationPortraitUpsideDown = System::Int8(0x2);
static constexpr System::Int8 AVCaptureWhiteBalanceModeAutoWhiteBalance = System::Int8(0x1);
static constexpr System::Int8 AVCaptureWhiteBalanceModeContinuousAutoWhiteBalance = System::Int8(0x2);
static constexpr System::Int8 AVCaptureWhiteBalanceModeLocked = System::Int8(0x0);
static constexpr short AVErrorApplicationIsNotAuthorized = short(-11836);
static constexpr short AVErrorCompositionTrackSegmentsNotContiguous = short(-11824);
static constexpr short AVErrorContentIsNotAuthorized = short(-11835);
static constexpr short AVErrorContentIsProtected = short(-11831);
static constexpr short AVErrorDecodeFailed = short(-11821);
static constexpr short AVErrorDecoderNotFound = short(-11833);
static constexpr short AVErrorDecoderTemporarilyUnavailable = short(-11839);
static constexpr short AVErrorDeviceAlreadyUsedByAnotherSession = short(-11804);
static constexpr short AVErrorDeviceInUseByAnotherApplication = short(-11815);
static constexpr short AVErrorDeviceIsNotAvailableInBackground = short(-11837);
static constexpr short AVErrorDeviceLockedForConfigurationByAnotherProcess = short(-11817);
static constexpr short AVErrorDeviceNotConnected = short(-11814);
static constexpr short AVErrorDeviceWasDisconnected = short(-11808);
static constexpr short AVErrorDiskFull = short(-11807);
static constexpr short AVErrorEncoderNotFound = short(-11834);
static constexpr short AVErrorEncoderTemporarilyUnavailable = short(-11840);
static constexpr short AVErrorExportFailed = short(-11820);
static constexpr short AVErrorFileAlreadyExists = short(-11823);
static constexpr short AVErrorFileFailedToParse = short(-11829);
static constexpr short AVErrorFileFormatNotRecognized = short(-11828);
static constexpr short AVErrorInvalidCompositionTrackSegmentDuration = short(-11825);
static constexpr short AVErrorInvalidCompositionTrackSegmentSourceDuration = short(-11827);
static constexpr short AVErrorInvalidCompositionTrackSegmentSourceStartTime = short(-11826);
static constexpr short AVErrorInvalidSourceMedia = short(-11822);
static constexpr short AVErrorInvalidVideoComposition = short(-11841);
static constexpr short AVErrorMaximumDurationReached = short(-11810);
static constexpr short AVErrorMaximumFileSizeReached = short(-11811);
static constexpr short AVErrorMaximumNumberOfSamplesForFileFormatReached = short(-11813);
static constexpr short AVErrorMaximumStillImageCaptureRequestsExceeded = short(-11830);
static constexpr short AVErrorMediaChanged = short(-11809);
static constexpr short AVErrorMediaDiscontinuity = short(-11812);
static constexpr short AVErrorMediaServicesWereReset = short(-11819);
static constexpr short AVErrorNoDataCaptured = short(-11805);
static constexpr short AVErrorNoImageAtTime = short(-11832);
static constexpr short AVErrorOperationNotSupportedForAsset = short(-11838);
static constexpr short AVErrorOutOfMemory = short(-11801);
static constexpr short AVErrorReferenceForbiddenByReferencePolicy = short(-11842);
static constexpr short AVErrorSessionConfigurationChanged = short(-11806);
static constexpr short AVErrorSessionNotRunning = short(-11803);
static constexpr short AVErrorSessionWasInterrupted = short(-11818);
static constexpr short AVErrorUnknown = short(-11800);
static constexpr System::Int8 AVKeyValueStatusCancelled = System::Int8(0x4);
static constexpr System::Int8 AVKeyValueStatusFailed = System::Int8(0x3);
static constexpr System::Int8 AVKeyValueStatusLoaded = System::Int8(0x2);
static constexpr System::Int8 AVKeyValueStatusLoading = System::Int8(0x1);
static constexpr System::Int8 AVKeyValueStatusUnknown = System::Int8(0x0);
static constexpr System::Int8 AVPlayerActionAtItemEndAdvance = System::Int8(0x0);
static constexpr System::Int8 AVPlayerActionAtItemEndNone = System::Int8(0x2);
static constexpr System::Int8 AVPlayerActionAtItemEndPause = System::Int8(0x1);
static constexpr System::Int8 AVPlayerItemStatusFailed = System::Int8(0x2);
static constexpr System::Int8 AVPlayerItemStatusReadyToPlay = System::Int8(0x1);
static constexpr System::Int8 AVPlayerItemStatusUnknown = System::Int8(0x0);
static constexpr System::Int8 AVPlayerStatusFailed = System::Int8(0x2);
static constexpr System::Int8 AVPlayerStatusReadyToPlay = System::Int8(0x1);
static constexpr System::Int8 AVPlayerStatusUnknown = System::Int8(0x0);
static constexpr System::Int8 AVAuthorizationStatusNotDetermined = System::Int8(0x0);
static constexpr System::Int8 AVAuthorizationStatusRestricted = System::Int8(0x1);
static constexpr System::Int8 AVAuthorizationStatusDenied = System::Int8(0x2);
static constexpr System::Int8 AVAuthorizationStatusAuthorized = System::Int8(0x3);
#define libAVFoundation u"/System/Library/Frameworks/AVFoundation.framework/AVFounda"\
	u"tion"
extern "C" Iosapi::Foundation::NSRect __cdecl AVMakeRectWithAspectRatioInsideRect(Iosapi::Foundation::NSSize aspectRatio, Iosapi::Foundation::NSRect boundingRect);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVMediaTypeAudio(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVMediaTypeVideo(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVCaptureSessionPresetPhoto(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVCaptureSessionPresetHigh(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVCaptureSessionPresetMedium(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVCaptureSessionPresetLow(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVCaptureSessionPreset352x288(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVCaptureSessionPreset640x480(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVCaptureSessionPreset1280x720(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVCaptureSessionPreset1920x1080(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVCaptureSessionPresetiFrame960x540(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVCaptureSessionPresetiFrame1280x720(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVCaptureSessionPresetInputPriority(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVFileTypeWAVE(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVFormatIDKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVSampleRateKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVNumberOfChannelsKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVLinearPCMBitDepthKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVEncoderBitRateKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVAudioSessionCategoryRecord(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall AVAudioSessionCategoryPlayback(void);
}	/* namespace Avfoundation */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_AVFOUNDATION)
using namespace Iosapi::Avfoundation;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_AvfoundationHPP
