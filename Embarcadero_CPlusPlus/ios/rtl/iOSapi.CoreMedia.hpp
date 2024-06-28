// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.CoreMedia.pas' rev: 34.00 (iOS)

#ifndef Iosapi_CoremediaHPP
#define Iosapi_CoremediaHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.StdDef.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.CoreAudio.hpp>
#include <iOSapi.CoreVideo.hpp>
#include <iOSapi.CoreGraphics.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Coremedia
{
//-- forward type declarations -----------------------------------------------
struct CMTime;
struct CMTimeRange;
struct CMTimeMapping;
struct CMSampleTimingInfo;
struct CMVideoDimensions;
//-- type declarations -------------------------------------------------------
typedef void * CMAttachmentBearerRef;

typedef unsigned CMAttachmentMode;

typedef unsigned *PCMAttachmentMode;

typedef unsigned CMAudioFormatDescriptionMask;

typedef unsigned *PCMAudioFormatDescriptionMask;

typedef unsigned CMBlockBufferFlags;

typedef NativeInt CMBlockBufferRef;

typedef NativeInt *PCMBlockBufferRef;

typedef void * CMBufferRef;

typedef NativeInt CMBufferQueueRef;

typedef NativeInt *PCMBufferQueueRef;

typedef int CMBufferQueueTriggerCondition;

typedef NativeInt CMBufferQueueTriggerToken;

typedef NativeInt *PCMBufferQueueTriggerToken;

typedef NativeInt CMFormatDescriptionRef;

typedef NativeInt *PCMFormatDescriptionRef;

typedef NativeInt CMAudioFormatDescriptionRef;

typedef NativeInt *PCMAudioFormatDescriptionRef;

typedef long CMItemCount;

typedef long *PCMItemCount;

typedef long CMItemIndex;

typedef unsigned CMMediaType;

typedef NativeInt CMMetadataFormatDescriptionRef;

typedef NativeInt *PCMMetadataFormatDescriptionRef;

typedef unsigned CMMetadataFormatType;

typedef NativeInt CMMuxedFormatDescriptionRef;

typedef NativeInt *PCMMuxedFormatDescriptionRef;

typedef unsigned CMMuxedStreamType;

typedef long CMPersistentTrackID;

typedef void * CMSampleBufferRef;

typedef void * *PCMSampleBufferRef;

typedef NativeInt CMSimpleQueueRef;

typedef NativeInt *PCMSimpleQueueRef;

typedef unsigned CMTextDisplayFlags;

typedef unsigned *PCMTextDisplayFlags;

typedef System::Int8 CMTextJustificationValue;

typedef System::Int8 *PCMTextJustificationValue;

typedef NativeInt CMTimeCodeFormatDescriptionRef;

typedef NativeInt *PCMTimeCodeFormatDescriptionRef;

typedef unsigned CMTimeCodeFormatType;

typedef __int64 CMTimeEpoch;

typedef unsigned CMTimeFlags;

typedef unsigned CMTimeRoundingMethod;

typedef int CMTimeScale;

typedef __int64 CMTimeValue;

typedef unsigned CMVideoCodecType;

typedef NativeInt CMVideoFormatDescriptionRef;

typedef NativeInt *PCMVideoFormatDescriptionRef;

typedef void * CMClockRef;

struct DECLSPEC_DRECORD CMTime
{
public:
	__int64 value;
	int timescale;
	unsigned flags;
	__int64 epoch;
};


struct DECLSPEC_DRECORD CMTimeRange
{
public:
	CMTime start;
	CMTime duration;
};


struct DECLSPEC_DRECORD CMTimeMapping
{
public:
	CMTimeRange source;
	CMTimeRange target;
};


struct DECLSPEC_DRECORD CMSampleTimingInfo
{
public:
	CMTime duration;
	CMTime presentationTimeStamp;
	CMTime decodeTimeStamp;
};


typedef CMSampleTimingInfo *PCMSampleTimingInfo;

struct DECLSPEC_DRECORD CMVideoDimensions
{
public:
	int width;
	int height;
};


typedef long __cdecl (*CMBufferCompareCallback)(void * buf1, void * buf2, void * refcon);

typedef bool __cdecl (*CMBufferGetBooleanCallback)(void * buf, void * refcon);

typedef CMTime __cdecl (*CMBufferGetTimeCallback)(void * buf, void * refcon);

typedef void __cdecl (*CMBufferQueueTriggerCallback)(void * triggerRefCon, NativeInt triggerToken);

typedef int __cdecl (*CMBufferValidationCallback)(NativeInt queue, void * buf, void * validationRefCon);

typedef void __cdecl (*CMSampleBufferInvalidateCallback)(void * sbuf, unsigned __int64 invalidateRefCon);

typedef int __cdecl (*CMSampleBufferMakeDataReadyCallback)(void * sbuf, void * makeDataReadyRefcon);

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 kCMAttachmentMode_ShouldNotPropagate = System::Int8(0x0);
static constexpr System::Int8 kCMAttachmentMode_ShouldPropagate = System::Int8(0x1);
static constexpr int kCMAudioCodecType_AAC_AudibleProtected = int(0x61616163);
static constexpr int kCMAudioCodecType_AAC_LCProtected = int(0x70616163);
static constexpr System::Int8 kCMAudioFormatDescriptionMask_All = System::Int8(0xf);
static constexpr System::Int8 kCMAudioFormatDescriptionMask_ChannelLayout = System::Int8(0x4);
static constexpr System::Int8 kCMAudioFormatDescriptionMask_Extensions = System::Int8(0x8);
static constexpr System::Int8 kCMAudioFormatDescriptionMask_MagicCookie = System::Int8(0x2);
static constexpr System::Int8 kCMAudioFormatDescriptionMask_StreamBasicDescription = System::Int8(0x1);
static constexpr System::Int8 kCMBlockBufferAlwaysCopyDataFlag = System::Int8(0x2);
static constexpr System::Int8 kCMBlockBufferAssureMemoryNowFlag = System::Int8(0x1);
static constexpr short kCMBlockBufferBadCustomBlockSourceErr = short(-12702);
static constexpr short kCMBlockBufferBadLengthParameterErr = short(-12704);
static constexpr short kCMBlockBufferBadOffsetParameterErr = short(-12703);
static constexpr short kCMBlockBufferBadPointerParameterErr = short(-12705);
static constexpr short kCMBlockBufferBlockAllocationFailedErr = short(-12701);
static constexpr System::Int8 kCMBlockBufferCustomBlockSourceVersion = System::Int8(0x0);
static constexpr System::Int8 kCMBlockBufferDontOptimizeDepthFlag = System::Int8(0x4);
static constexpr short kCMBlockBufferEmptyBBufErr = short(-12706);
static constexpr System::Int8 kCMBlockBufferNoErr = System::Int8(0x0);
static constexpr System::Int8 kCMBlockBufferPermitEmptyReferenceFlag = System::Int8(0x8);
static constexpr short kCMBlockBufferStructureAllocationFailedErr = short(-12700);
static constexpr short kCMBlockBufferUnallocatedBlockErr = short(-12707);
static constexpr short kCMBufferQueueError_AllocationFailed = short(-12760);
static constexpr short kCMBufferQueueError_BadTriggerDuration = short(-12765);
static constexpr short kCMBufferQueueError_CannotModifyQueueFromTriggerCallback = short(-12766);
static constexpr short kCMBufferQueueError_EnqueueAfterEndOfData = short(-12763);
static constexpr short kCMBufferQueueError_InvalidBuffer = short(-12769);
static constexpr short kCMBufferQueueError_InvalidCMBufferCallbacksStruct = short(-12762);
static constexpr short kCMBufferQueueError_InvalidTriggerCondition = short(-12767);
static constexpr short kCMBufferQueueError_InvalidTriggerToken = short(-12768);
static constexpr short kCMBufferQueueError_QueueIsFull = short(-12764);
static constexpr short kCMBufferQueueError_RequiredParameterMissing = short(-12761);
static constexpr System::Int8 kCMBufferQueueTrigger_WhenBufferCountBecomesGreaterThan = System::Int8(0xb);
static constexpr System::Int8 kCMBufferQueueTrigger_WhenBufferCountBecomesLessThan = System::Int8(0xa);
static constexpr System::Int8 kCMBufferQueueTrigger_WhenDataBecomesReady = System::Int8(0x7);
static constexpr System::Int8 kCMBufferQueueTrigger_WhenDurationBecomesGreaterThan = System::Int8(0x3);
static constexpr System::Int8 kCMBufferQueueTrigger_WhenDurationBecomesGreaterThanOrEqualTo = System::Int8(0x4);
static constexpr System::Int8 kCMBufferQueueTrigger_WhenDurationBecomesLessThan = System::Int8(0x1);
static constexpr System::Int8 kCMBufferQueueTrigger_WhenDurationBecomesLessThanOrEqualTo = System::Int8(0x2);
static constexpr System::Int8 kCMBufferQueueTrigger_WhenEndOfDataReached = System::Int8(0x8);
static constexpr System::Int8 kCMBufferQueueTrigger_WhenMaxPresentationTimeStampChanges = System::Int8(0x6);
static constexpr System::Int8 kCMBufferQueueTrigger_WhenMinPresentationTimeStampChanges = System::Int8(0x5);
static constexpr System::Int8 kCMBufferQueueTrigger_WhenReset = System::Int8(0x9);
static constexpr int kCMClosedCaptionFormatType_ATSC = int(0x61746363);
static constexpr int kCMClosedCaptionFormatType_CEA608 = int(0x63363038);
static constexpr int kCMClosedCaptionFormatType_CEA708 = int(0x63373038);
static constexpr short kCMFormatDescriptionError_AllocationFailed = short(-12711);
static constexpr short kCMFormatDescriptionError_InvalidParameter = short(-12710);
static constexpr int kCMMPEG2VideoProfile_HDV_1080i50 = int(0x68647633);
static constexpr int kCMMPEG2VideoProfile_HDV_1080i60 = int(0x68647632);
static constexpr int kCMMPEG2VideoProfile_HDV_1080p24 = int(0x68647636);
static constexpr int kCMMPEG2VideoProfile_HDV_1080p25 = int(0x68647637);
static constexpr int kCMMPEG2VideoProfile_HDV_1080p30 = int(0x68647638);
static constexpr int kCMMPEG2VideoProfile_HDV_720p24 = int(0x68647634);
static constexpr int kCMMPEG2VideoProfile_HDV_720p25 = int(0x68647635);
static constexpr int kCMMPEG2VideoProfile_HDV_720p30 = int(0x68647631);
static constexpr int kCMMPEG2VideoProfile_HDV_720p50 = int(0x68647661);
static constexpr int kCMMPEG2VideoProfile_HDV_720p60 = int(0x68647639);
static constexpr int kCMMPEG2VideoProfile_XDCAM_EX_1080i50_VBR35 = int(0x78647663);
static constexpr int kCMMPEG2VideoProfile_XDCAM_EX_1080i60_VBR35 = int(0x78647662);
static constexpr int kCMMPEG2VideoProfile_XDCAM_EX_1080p24_VBR35 = int(0x78647664);
static constexpr int kCMMPEG2VideoProfile_XDCAM_EX_1080p25_VBR35 = int(0x78647665);
static constexpr int kCMMPEG2VideoProfile_XDCAM_EX_1080p30_VBR35 = int(0x78647666);
static constexpr int kCMMPEG2VideoProfile_XDCAM_EX_720p24_VBR35 = int(0x78647634);
static constexpr int kCMMPEG2VideoProfile_XDCAM_EX_720p25_VBR35 = int(0x78647635);
static constexpr int kCMMPEG2VideoProfile_XDCAM_EX_720p30_VBR35 = int(0x78647631);
static constexpr int kCMMPEG2VideoProfile_XDCAM_EX_720p50_VBR35 = int(0x78647661);
static constexpr int kCMMPEG2VideoProfile_XDCAM_EX_720p60_VBR35 = int(0x78647639);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD422_1080i50_CBR50 = int(0x78643563);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD422_1080i60_CBR50 = int(0x78643562);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD422_1080p24_CBR50 = int(0x78643564);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD422_1080p25_CBR50 = int(0x78643565);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD422_1080p30_CBR50 = int(0x78643566);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD422_540p = int(0x78646832);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD422_720p24_CBR50 = int(0x78643534);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD422_720p25_CBR50 = int(0x78643535);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD422_720p30_CBR50 = int(0x78643531);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD422_720p50_CBR50 = int(0x78643561);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD422_720p60_CBR50 = int(0x78643539);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD_1080i50_VBR35 = int(0x78647633);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD_1080i60_VBR35 = int(0x78647632);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD_1080p24_VBR35 = int(0x78647636);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD_1080p25_VBR35 = int(0x78647637);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD_1080p30_VBR35 = int(0x78647638);
static constexpr int kCMMPEG2VideoProfile_XDCAM_HD_540p = int(0x78646864);
static constexpr int kCMMediaType_Audio = int(0x736f756e);
static constexpr int kCMMediaType_ClosedCaption = int(0x636c6370);
static constexpr int kCMMediaType_Muxed = int(0x6d757878);
static constexpr int kCMMediaType_Subtitle = int(0x7362746c);
static constexpr int kCMMediaType_Text = int(0x74657874);
static constexpr int kCMMediaType_TimeCode = int(0x746d6364);
static constexpr int kCMMediaType_TimedMetadata = int(0x746d6574);
static constexpr int kCMMediaType_Video = int(0x76696465);
static constexpr int kCMMuxedStreamType_DV = int(0x64762020);
static constexpr int kCMMuxedStreamType_MPEG1System = int(0x6d703173);
static constexpr int kCMMuxedStreamType_MPEG2Program = int(0x6d703270);
static constexpr int kCMMuxedStreamType_MPEG2Transport = int(0x6d703274);
static constexpr System::Int8 kCMPersistentTrackID_Invalid = System::Int8(0x0);
static constexpr System::Int8 kCMPixelFormat_16BE555 = System::Int8(0x10);
static constexpr int kCMPixelFormat_16BE565 = int(0x42353635);
static constexpr int kCMPixelFormat_16LE555 = int(0x4c353535);
static constexpr int kCMPixelFormat_16LE5551 = int(0x35353531);
static constexpr int kCMPixelFormat_16LE565 = int(0x4c353635);
static constexpr System::Int8 kCMPixelFormat_24RGB = System::Int8(0x18);
static constexpr System::Int8 kCMPixelFormat_32ARGB = System::Int8(0x20);
static constexpr int kCMPixelFormat_32BGRA = int(0x42475241);
static constexpr int kCMPixelFormat_422YpCbCr10 = int(0x76323130);
static constexpr int kCMPixelFormat_422YpCbCr16 = int(0x76323136);
static constexpr int kCMPixelFormat_422YpCbCr8 = int(0x32767579);
static constexpr int kCMPixelFormat_422YpCbCr8_yuvs = int(0x79757673);
static constexpr int kCMPixelFormat_4444YpCbCrA8 = int(0x76343038);
static constexpr int kCMPixelFormat_444YpCbCr10 = int(0x76343130);
static constexpr int kCMPixelFormat_444YpCbCr8 = int(0x76333038);
static constexpr System::Int8 kCMPixelFormat_8IndexedGray_WhiteIsZero = System::Int8(0x28);
static constexpr short kCMSampleBufferError_AllocationFailed = short(-12730);
static constexpr short kCMSampleBufferError_AlreadyHasDataBuffer = short(-12732);
static constexpr short kCMSampleBufferError_ArrayTooSmall = short(-12737);
static constexpr short kCMSampleBufferError_BufferHasNoSampleSizes = short(-12735);
static constexpr short kCMSampleBufferError_BufferHasNoSampleTimingInfo = short(-12736);
static constexpr short kCMSampleBufferError_BufferNotReady = short(-12733);
static constexpr short kCMSampleBufferError_CannotSubdivide = short(-12739);
static constexpr short kCMSampleBufferError_InvalidEntryCount = short(-12738);
static constexpr short kCMSampleBufferError_InvalidMediaFormat = short(-12743);
static constexpr short kCMSampleBufferError_InvalidMediaTypeForOperation = short(-12741);
static constexpr short kCMSampleBufferError_InvalidSampleData = short(-12742);
static constexpr short kCMSampleBufferError_Invalidated = short(-12744);
static constexpr short kCMSampleBufferError_RequiredParameterMissing = short(-12731);
static constexpr short kCMSampleBufferError_SampleIndexOutOfRange = short(-12734);
static constexpr short kCMSampleBufferError_SampleTimingInfoInvalid = short(-12740);
static constexpr System::Int8 kCMSampleBufferFlag_AudioBufferList_Assure16ByteAlignment = System::Int8(0x1);
static constexpr short kCMSimpleQueueError_AllocationFailed = short(-12770);
static constexpr short kCMSimpleQueueError_ParameterOutOfRange = short(-12772);
static constexpr short kCMSimpleQueueError_QueueIsFull = short(-12773);
static constexpr short kCMSimpleQueueError_RequiredParameterMissing = short(-12771);
static constexpr unsigned kCMTextDisplayFlag_allSubtitlesForced = unsigned(0x80000000);
static constexpr System::Word kCMTextDisplayFlag_continuousKaraoke = System::Word(0x800);
static constexpr int kCMTextDisplayFlag_fillTextRegion = int(0x40000);
static constexpr int kCMTextDisplayFlag_forcedSubtitlesPresent = int(0x40000000);
static constexpr int kCMTextDisplayFlag_obeySubtitleFormatting = int(0x20000000);
static constexpr System::Word kCMTextDisplayFlag_scrollDirectionMask = System::Word(0x180);
static constexpr System::Int8 kCMTextDisplayFlag_scrollDirection_bottomToTop = System::Int8(0x0);
static constexpr System::Word kCMTextDisplayFlag_scrollDirection_leftToRight = System::Word(0x180);
static constexpr System::Byte kCMTextDisplayFlag_scrollDirection_rightToLeft = System::Byte(0x80);
static constexpr System::Word kCMTextDisplayFlag_scrollDirection_topToBottom = System::Word(0x100);
static constexpr System::Int8 kCMTextDisplayFlag_scrollIn = System::Int8(0x20);
static constexpr System::Int8 kCMTextDisplayFlag_scrollOut = System::Int8(0x40);
static constexpr int kCMTextDisplayFlag_writeTextVertically = int(0x20000);
static constexpr int kCMTextFormatType_3GText = int(0x74783367);
static constexpr int kCMTextFormatType_QTText = int(0x74657874);
static constexpr System::Int8 kCMTextJustification_bottom_right = System::Int8(-1);
static constexpr System::Int8 kCMTextJustification_centered = System::Int8(0x1);
static constexpr System::Int8 kCMTextJustification_left_top = System::Int8(0x0);
static constexpr System::Int8 kCMTimeCodeFlag_24HourMax = System::Int8(0x2);
static constexpr System::Int8 kCMTimeCodeFlag_DropFrame = System::Int8(0x1);
static constexpr System::Int8 kCMTimeCodeFlag_NegTimesOK = System::Int8(0x4);
static constexpr int kCMTimeCodeFormatType_Counter32 = int(0x636e3332);
static constexpr int kCMTimeCodeFormatType_Counter64 = int(0x636e3634);
static constexpr int kCMTimeCodeFormatType_TimeCode32 = int(0x746d6364);
static constexpr int kCMTimeCodeFormatType_TimeCode64 = int(0x74633634);
static constexpr System::Int8 kCMTimeFlags_HasBeenRounded = System::Int8(0x2);
static constexpr System::Int8 kCMTimeFlags_ImpliedValueFlagsMask = System::Int8(0x1c);
static constexpr System::Int8 kCMTimeFlags_Indefinite = System::Int8(0x10);
static constexpr System::Int8 kCMTimeFlags_NegativeInfinity = System::Int8(0x8);
static constexpr System::Int8 kCMTimeFlags_PositiveInfinity = System::Int8(0x4);
static constexpr System::Int8 kCMTimeFlags_Valid = System::Int8(0x1);
static constexpr int kCMTimeMaxTimescale = int(0x7fffffff);
static constexpr System::Int8 kCMTimeRoundingMethod_Default = System::Int8(0x1);
static constexpr System::Int8 kCMTimeRoundingMethod_QuickTime = System::Int8(0x4);
static constexpr System::Int8 kCMTimeRoundingMethod_RoundAwayFromZero = System::Int8(0x3);
static constexpr System::Int8 kCMTimeRoundingMethod_RoundHalfAwayFromZero = System::Int8(0x1);
static constexpr System::Int8 kCMTimeRoundingMethod_RoundTowardNegativeInfinity = System::Int8(0x6);
static constexpr System::Int8 kCMTimeRoundingMethod_RoundTowardPositiveInfinity = System::Int8(0x5);
static constexpr System::Int8 kCMTimeRoundingMethod_RoundTowardZero = System::Int8(0x2);
static constexpr int kCMTimedMetadataFormatType_Boxed = int(0x6d656278);
static constexpr int kCMTimedMetadataFormatType_ICY = int(0x69637920);
static constexpr int kCMTimedMetadataFormatType_ID3 = int(0x69643320);
static constexpr int kCMVideoCodecType_422YpCbCr8 = int(0x32767579);
static constexpr int kCMVideoCodecType_Animation = int(0x726c6520);
static constexpr int kCMVideoCodecType_AppleProRes422 = int(0x6170636e);
static constexpr int kCMVideoCodecType_AppleProRes422HQ = int(0x61706368);
static constexpr int kCMVideoCodecType_AppleProRes422LT = int(0x61706373);
static constexpr int kCMVideoCodecType_AppleProRes422Proxy = int(0x6170636f);
static constexpr int kCMVideoCodecType_AppleProRes4444 = int(0x61703468);
static constexpr int kCMVideoCodecType_Cinepak = int(0x63766964);
static constexpr int kCMVideoCodecType_DVCNTSC = int(0x64766320);
static constexpr int kCMVideoCodecType_DVCPAL = int(0x64766370);
static constexpr int kCMVideoCodecType_DVCPROHD1080i50 = int(0x64766835);
static constexpr int kCMVideoCodecType_DVCPROHD1080i60 = int(0x64766836);
static constexpr int kCMVideoCodecType_DVCPROHD1080p25 = int(0x64766832);
static constexpr int kCMVideoCodecType_DVCPROHD1080p30 = int(0x64766833);
static constexpr int kCMVideoCodecType_DVCPROHD720p50 = int(0x64766871);
static constexpr int kCMVideoCodecType_DVCPROHD720p60 = int(0x64766870);
static constexpr int kCMVideoCodecType_DVCPro50NTSC = int(0x6476356e);
static constexpr int kCMVideoCodecType_DVCPro50PAL = int(0x64763570);
static constexpr int kCMVideoCodecType_DVCProPAL = int(0x64767070);
static constexpr int kCMVideoCodecType_H263 = int(0x68323633);
static constexpr int kCMVideoCodecType_H264 = int(0x61766331);
static constexpr int kCMVideoCodecType_JPEG = int(0x6a706567);
static constexpr int kCMVideoCodecType_JPEG_OpenDML = int(0x646d6231);
static constexpr int kCMVideoCodecType_MPEG1Video = int(0x6d703176);
static constexpr int kCMVideoCodecType_MPEG2Video = int(0x6d703276);
static constexpr int kCMVideoCodecType_MPEG4Video = int(0x6d703476);
static constexpr int kCMVideoCodecType_SorensonVideo = int(0x53565131);
static constexpr int kCMVideoCodecType_SorensonVideo3 = int(0x53565133);
#define libCoreMedia u"/System/Library/Frameworks/CoreMedia.framework/CoreMedia"
extern "C" int __cdecl CMAudioFormatDescriptionCreate(CFAllocatorRef allocator, Iosapi::Coreaudio::PAudioStreamBasicDescription asbd, unsigned long layoutSize, Iosapi::Coreaudio::PAudioChannelLayout layout, unsigned long magicCookieSize, void * magicCookie, CFDictionaryRef extensions, PCMAudioFormatDescriptionRef outDesc);
extern "C" int __cdecl CMAudioFormatDescriptionCreateSummary(CFAllocatorRef allocator, CFArrayRef formatDescriptionArray, unsigned flags, PCMAudioFormatDescriptionRef summaryFormatDescriptionOut);
extern "C" bool __cdecl CMAudioFormatDescriptionEqual(NativeInt desc1, NativeInt desc2, unsigned equalityMask, PCMAudioFormatDescriptionMask equalityMaskOut);
extern "C" Iosapi::Coreaudio::PAudioChannelLayout __cdecl CMAudioFormatDescriptionGetChannelLayout(NativeInt desc, Posix::Stddef::Psize_t layoutSize);
extern "C" void * __cdecl CMAudioFormatDescriptionGetMagicCookie(NativeInt desc, Posix::Stddef::Psize_t cookieSizeOut);
extern "C" Iosapi::Coreaudio::PAudioStreamBasicDescription __cdecl CMAudioFormatDescriptionGetStreamBasicDescription(NativeInt desc);
extern "C" int __cdecl CMBlockBufferAccessDataBytes(NativeInt theBuffer, unsigned long offset, unsigned long length, void * temporaryBlock, System::WideChar * returnedPointer);
extern "C" int __cdecl CMBlockBufferAppendBufferReference(NativeInt theBuffer, NativeInt targetBBuf, unsigned long offsetToData, unsigned long dataLength, unsigned flags);
extern "C" int __cdecl CMBlockBufferAssureBlockMemory(NativeInt theBuffer);
extern "C" int __cdecl CMBlockBufferCopyDataBytes(NativeInt theSourceBuffer, unsigned long offsetToData, unsigned long dataLength, void * destination);
extern "C" int __cdecl CMBlockBufferCreateEmpty(CFAllocatorRef structureAllocator, unsigned subBlockCapacity, unsigned flags, PCMBlockBufferRef newBBufOut);
extern "C" int __cdecl CMBlockBufferCreateWithBufferReference(CFAllocatorRef structureAllocator, NativeInt targetBuffer, unsigned long offsetToData, unsigned long dataLength, unsigned flags, PCMBlockBufferRef newBBufOut);
extern "C" int __cdecl CMBlockBufferFillDataBytes(System::WideChar fillByte, NativeInt destinationBuffer, unsigned long offsetIntoDestination, unsigned long dataLength);
extern "C" unsigned long __cdecl CMBlockBufferGetDataLength(NativeInt theBuffer);
extern "C" int __cdecl CMBlockBufferGetDataPointer(NativeInt theBuffer, unsigned long offset, Posix::Stddef::Psize_t lengthAtOffset, Posix::Stddef::Psize_t totalLength, System::WideChar * dataPointer);
extern "C" unsigned long __cdecl CMBlockBufferGetTypeID(void);
extern "C" bool __cdecl CMBlockBufferIsEmpty(NativeInt theBuffer);
extern "C" bool __cdecl CMBlockBufferIsRangeContiguous(NativeInt theBuffer, unsigned long offset, unsigned long length);
extern "C" int __cdecl CMBlockBufferReplaceDataBytes(void * sourceBytes, NativeInt destinationBuffer, unsigned long offsetIntoDestination, unsigned long dataLength);
extern "C" bool __cdecl CMBufferQueueContainsEndOfData(NativeInt queue);
extern "C" void * __cdecl CMBufferQueueDequeueAndRetain(NativeInt queue);
extern "C" void * __cdecl CMBufferQueueDequeueIfDataReadyAndRetain(NativeInt queue);
extern "C" int __cdecl CMBufferQueueEnqueue(NativeInt queue, void * buf);
extern "C" long __cdecl CMBufferQueueGetBufferCount(NativeInt queue);
extern "C" CMTime __cdecl CMBufferQueueGetDuration(NativeInt queue);
extern "C" CMTime __cdecl CMBufferQueueGetEndPresentationTimeStamp(NativeInt queue);
extern "C" CMTime __cdecl CMBufferQueueGetFirstDecodeTimeStamp(NativeInt queue);
extern "C" CMTime __cdecl CMBufferQueueGetFirstPresentationTimeStamp(NativeInt queue);
extern "C" void * __cdecl CMBufferQueueGetHead(NativeInt queue);
extern "C" CMTime __cdecl CMBufferQueueGetMaxPresentationTimeStamp(NativeInt queue);
extern "C" CMTime __cdecl CMBufferQueueGetMinDecodeTimeStamp(NativeInt queue);
extern "C" CMTime __cdecl CMBufferQueueGetMinPresentationTimeStamp(NativeInt queue);
extern "C" unsigned long __cdecl CMBufferQueueGetTypeID(void);
extern "C" int __cdecl CMBufferQueueInstallTrigger(NativeInt queue, CMBufferQueueTriggerCallback triggerCallback, void * triggerRefcon, int triggerCondition, CMTime triggerTime, PCMBufferQueueTriggerToken triggerTokenOut);
extern "C" int __cdecl CMBufferQueueInstallTriggerWithIntegerThreshold(NativeInt queue, CMBufferQueueTriggerCallback triggerCallback, void * triggerRefcon, int triggerCondition, long triggerThreshold, PCMBufferQueueTriggerToken triggerTokenOut);
extern "C" bool __cdecl CMBufferQueueIsAtEndOfData(NativeInt queue);
extern "C" bool __cdecl CMBufferQueueIsEmpty(NativeInt queue);
extern "C" int __cdecl CMBufferQueueMarkEndOfData(NativeInt queue);
extern "C" int __cdecl CMBufferQueueRemoveTrigger(NativeInt queue, NativeInt triggerToken);
extern "C" int __cdecl CMBufferQueueReset(NativeInt queue);
extern "C" int __cdecl CMBufferQueueSetValidationCallback(NativeInt queue, CMBufferValidationCallback validationCallback, void * validationRefCon);
extern "C" bool __cdecl CMBufferQueueTestTrigger(NativeInt queue, NativeInt triggerToken);
extern "C" CFDictionaryRef __cdecl CMCopyDictionaryOfAttachments(CFAllocatorRef allocator, void * target, unsigned attachmentMode);
extern "C" int __cdecl CMFormatDescriptionCreate(CFAllocatorRef allocator, unsigned mediaType, unsigned mediaSubtype, CFDictionaryRef extensions, PCMFormatDescriptionRef descOut);
extern "C" bool __cdecl CMFormatDescriptionEqual(NativeInt desc1, NativeInt desc2);
extern "C" bool __cdecl CMFormatDescriptionEqualIgnoringExtensionKeys(NativeInt desc1, NativeInt desc2, void * formatDescriptionExtensionKeysToIgnore, void * sampleDescriptionExtensionAtomKeysToIgnore);
extern "C" void * __cdecl CMFormatDescriptionGetExtension(NativeInt desc, CFStringRef extensionKey);
extern "C" CFDictionaryRef __cdecl CMFormatDescriptionGetExtensions(NativeInt desc);
extern "C" unsigned __cdecl CMFormatDescriptionGetMediaSubType(NativeInt desc);
extern "C" unsigned __cdecl CMFormatDescriptionGetMediaType(NativeInt desc);
extern "C" unsigned long __cdecl CMFormatDescriptionGetTypeID(void);
extern "C" void * __cdecl CMGetAttachment(void * target, CFStringRef key, PCMAttachmentMode attachmentModeOut);
extern "C" int __cdecl CMMetadataFormatDescriptionCreateWithKeys(CFAllocatorRef allocator, unsigned metadataType, CFArrayRef keys, PCMMetadataFormatDescriptionRef outDesc);
extern "C" CFDictionaryRef __cdecl CMMetadataFormatDescriptionGetKeyWithLocalID(NativeInt desc, unsigned localKeyID);
extern "C" int __cdecl CMMuxedFormatDescriptionCreate(CFAllocatorRef allocator, unsigned muxType, CFDictionaryRef extensions, PCMMuxedFormatDescriptionRef outDesc);
extern "C" void __cdecl CMPropagateAttachments(void * source, void * destination);
extern "C" void __cdecl CMRemoveAllAttachments(void * target);
extern "C" void __cdecl CMRemoveAttachment(void * target, CFStringRef key);
extern "C" int __cdecl CMSampleBufferCopySampleBufferForRange(CFAllocatorRef allocator, void * sbuf, CFRange sampleRange, PCMSampleBufferRef sBufOut);
extern "C" int __cdecl CMSampleBufferCreate(CFAllocatorRef allocator, NativeInt dataBuffer, bool dataReady, CMSampleBufferMakeDataReadyCallback makeDataReadyCallback, void * makeDataReadyRefcon, NativeInt formatDescription, long numSamples, long numSampleTimingEntries, PCMSampleTimingInfo sampleTimingArray, long numSampleSizeEntries, Posix::Stddef::Psize_t sampleSizeArray, PCMSampleBufferRef sBufOut);
extern "C" int __cdecl CMSampleBufferCreateCopy(CFAllocatorRef allocator, void * sbuf, PCMSampleBufferRef sbufCopyOut);
extern "C" int __cdecl CMSampleBufferCreateCopyWithNewTiming(CFAllocatorRef allocator, void * originalSBuf, long numSampleTimingEntries, PCMSampleTimingInfo sampleTimingArray, PCMSampleBufferRef sBufCopyOut);
extern "C" int __cdecl CMSampleBufferCreateForImageBuffer(CFAllocatorRef allocator, NativeInt imageBuffer, bool dataReady, CMSampleBufferMakeDataReadyCallback makeDataReadyCallback, void * makeDataReadyRefcon, NativeInt formatDescription, PCMSampleTimingInfo sampleTiming, PCMSampleBufferRef sBufOut);
extern "C" bool __cdecl CMSampleBufferDataIsReady(void * sbuf);
extern "C" int __cdecl CMSampleBufferGetAudioBufferListWithRetainedBlockBuffer(void * sbuf, Posix::Stddef::Psize_t bufferListSizeNeededOut, Iosapi::Coreaudio::PAudioBufferList bufferListOut, unsigned long bufferListSize, CFAllocatorRef bbufStructAllocator, CFAllocatorRef bbufMemoryAllocator, unsigned flags, PCMBlockBufferRef blockBufferOut);
extern "C" int __cdecl CMSampleBufferGetAudioStreamPacketDescriptions(void * sbuf, unsigned long packetDescriptionsSize, Iosapi::Coreaudio::PAudioStreamPacketDescription packetDescriptionsOut, Posix::Stddef::Psize_t packetDescriptionsSizeNeededOut);
extern "C" int __cdecl CMSampleBufferGetAudioStreamPacketDescriptionsPtr(void * sbuf, Iosapi::Coreaudio::PAudioStreamPacketDescription packetDescriptionsPtrOut, Posix::Stddef::Psize_t packetDescriptionsSizeOut);
extern "C" NativeInt __cdecl CMSampleBufferGetDataBuffer(void * sbuf);
extern "C" CMTime __cdecl CMSampleBufferGetDecodeTimeStamp(void * sbuf);
extern "C" CMTime __cdecl CMSampleBufferGetDuration(void * sbuf);
extern "C" NativeInt __cdecl CMSampleBufferGetFormatDescription(void * sbuf);
extern "C" NativeInt __cdecl CMSampleBufferGetImageBuffer(void * sbuf);
extern "C" long __cdecl CMSampleBufferGetNumSamples(void * sbuf);
extern "C" CMTime __cdecl CMSampleBufferGetOutputDecodeTimeStamp(void * sbuf);
extern "C" CMTime __cdecl CMSampleBufferGetOutputDuration(void * sbuf);
extern "C" CMTime __cdecl CMSampleBufferGetOutputPresentationTimeStamp(void * sbuf);
extern "C" int __cdecl CMSampleBufferGetOutputSampleTimingInfoArray(void * sbuf, long timingArrayEntries, PCMSampleTimingInfo timingArrayOut, PCMItemCount timingArrayEntriesNeededOut);
extern "C" CMTime __cdecl CMSampleBufferGetPresentationTimeStamp(void * sbuf);
extern "C" CFArrayRef __cdecl CMSampleBufferGetSampleAttachmentsArray(void * sbuf, bool createIfNecessary);
extern "C" unsigned long __cdecl CMSampleBufferGetSampleSize(void * sbuf, long sampleIndex);
extern "C" int __cdecl CMSampleBufferGetSampleSizeArray(void * sbuf, long sizeArrayEntries, Posix::Stddef::Psize_t sizeArrayOut, PCMItemCount sizeArrayEntriesNeededOut);
extern "C" int __cdecl CMSampleBufferGetSampleTimingInfo(void * sbuf, long sampleIndex, PCMSampleTimingInfo timingInfoOut);
extern "C" int __cdecl CMSampleBufferGetSampleTimingInfoArray(void * sbuf, long timingArrayEntries, PCMSampleTimingInfo timingArrayOut, PCMItemCount timingArrayEntriesNeededOut);
extern "C" unsigned long __cdecl CMSampleBufferGetTotalSampleSize(void * sbuf);
extern "C" unsigned long __cdecl CMSampleBufferGetTypeID(void);
extern "C" int __cdecl CMSampleBufferInvalidate(void * sbuf);
extern "C" bool __cdecl CMSampleBufferIsValid(void * sbuf);
extern "C" int __cdecl CMSampleBufferMakeDataReady(void * sbuf);
extern "C" int __cdecl CMSampleBufferSetDataBuffer(void * sbuf, NativeInt dataBuffer);
extern "C" int __cdecl CMSampleBufferSetDataBufferFromAudioBufferList(void * sbuf, CFAllocatorRef bbufStructAllocator, CFAllocatorRef bbufMemoryAllocator, unsigned flags, Iosapi::Coreaudio::PAudioBufferList bufferList);
extern "C" int __cdecl CMSampleBufferSetDataReady(void * sbuf);
extern "C" int __cdecl CMSampleBufferSetInvalidateCallback(void * sbuf, CMSampleBufferInvalidateCallback invalidateCallback, unsigned __int64 invalidateRefCon);
extern "C" int __cdecl CMSampleBufferSetOutputPresentationTimeStamp(void * sbuf, CMTime outputPresentationTimeStamp);
extern "C" int __cdecl CMSampleBufferTrackDataReadiness(void * sbuf, void * sbufToTrack);
extern "C" void __cdecl CMSetAttachment(void * target, CFStringRef key, void * value, unsigned attachmentMode);
extern "C" void __cdecl CMSetAttachments(void * target, CFDictionaryRef theAttachments, unsigned attachmentMode);
extern "C" int __cdecl CMSimpleQueueCreate(CFAllocatorRef allocator, int capacity, PCMSimpleQueueRef queueOut);
extern "C" void * __cdecl CMSimpleQueueDequeue(NativeInt queue);
extern "C" int __cdecl CMSimpleQueueEnqueue(NativeInt queue, void * element);
extern "C" int __cdecl CMSimpleQueueGetCapacity(NativeInt queue);
extern "C" int __cdecl CMSimpleQueueGetCount(NativeInt queue);
extern "C" void * __cdecl CMSimpleQueueGetHead(NativeInt queue);
extern "C" unsigned long __cdecl CMSimpleQueueGetTypeID(void);
extern "C" int __cdecl CMSimpleQueueReset(NativeInt queue);
extern "C" int __cdecl CMTextFormatDescriptionGetDefaultStyle(NativeInt desc, Iosapi::Cocoatypes::PUInt16 outLocalFontID, System::PBoolean outBold, System::PBoolean outItalic, System::PBoolean outUnderline, Iosapi::Cocoatypes::PCGFloat outFontSize, Iosapi::Cocoatypes::PCGFloat outColorComponents);
extern "C" int __cdecl CMTextFormatDescriptionGetDefaultTextBox(NativeInt desc, bool originIsAtTopLeft, double heightOfTextTrack, Iosapi::Coregraphics::PCGRect outDefaultTextBox);
extern "C" int __cdecl CMTextFormatDescriptionGetDisplayFlags(NativeInt desc, PCMTextDisplayFlags outDisplayFlags);
extern "C" int __cdecl CMTextFormatDescriptionGetFontName(NativeInt desc, System::Word localFontID, Macapi::Corefoundation::PCFStringRef outFontName);
extern "C" int __cdecl CMTextFormatDescriptionGetJustification(NativeInt desc, PCMTextJustificationValue outHorizontalJust, PCMTextJustificationValue outVerticalJust);
extern "C" CMTime __cdecl CMTimeAbsoluteValue(CMTime time);
extern "C" CMTime __cdecl CMTimeAdd(CMTime addend1, CMTime addend2);
extern "C" CMTime __cdecl CMTimeClampToRange(CMTime time, CMTimeRange range);
extern "C" int __cdecl CMTimeCodeFormatDescriptionCreate(CFAllocatorRef allocator, unsigned timeCodeFormatType, CMTime frameDuration, unsigned frameQuanta, unsigned tcFlags, CFDictionaryRef extensions, PCMTimeCodeFormatDescriptionRef descOut);
extern "C" CMTime __cdecl CMTimeCodeFormatDescriptionGetFrameDuration(NativeInt timeCodeFormatDescription);
extern "C" unsigned __cdecl CMTimeCodeFormatDescriptionGetFrameQuanta(NativeInt timeCodeFormatDescription);
extern "C" unsigned __cdecl CMTimeCodeFormatDescriptionGetTimeCodeFlags(NativeInt desc);
extern "C" int __cdecl CMTimeCompare(CMTime time1, CMTime time2);
extern "C" CMTime __cdecl CMTimeConvertScale(CMTime time, int newTimescale, unsigned method);
extern "C" CFDictionaryRef __cdecl CMTimeCopyAsDictionary(CMTime time, CFAllocatorRef allocator);
extern "C" CFStringRef __cdecl CMTimeCopyDescription(CFAllocatorRef allocator, CMTime time);
extern "C" double __cdecl CMTimeGetSeconds(CMTime time);
extern "C" CMTime __cdecl CMTimeMake(__int64 value, int timescale);
extern "C" CMTime __cdecl CMTimeMakeFromDictionary(CFDictionaryRef dict);
extern "C" CMTime __cdecl CMTimeMakeWithEpoch(__int64 value, int timescale, __int64 epoch);
extern "C" CMTime __cdecl CMTimeMakeWithSeconds(double seconds, int preferredTimeScale);
extern "C" CMTime __cdecl CMTimeMapDurationFromRangeToRange(CMTime dur, CMTimeRange fromRange, CMTimeRange toRange);
extern "C" CMTime __cdecl CMTimeMapTimeFromRangeToRange(CMTime t, CMTimeRange fromRange, CMTimeRange toRange);
extern "C" CMTime __cdecl CMTimeMaximum(CMTime time1, CMTime time2);
extern "C" CMTime __cdecl CMTimeMinimum(CMTime time1, CMTime time2);
extern "C" CMTime __cdecl CMTimeMultiply(CMTime time, int multiplier);
extern "C" CMTime __cdecl CMTimeMultiplyByFloat64(CMTime time, double multiplier);
extern "C" bool __cdecl CMTimeRangeContainsTime(CMTimeRange range, CMTime time);
extern "C" bool __cdecl CMTimeRangeContainsTimeRange(CMTimeRange range1, CMTimeRange range2);
extern "C" CFDictionaryRef __cdecl CMTimeRangeCopyAsDictionary(CMTimeRange range, CFAllocatorRef allocator);
extern "C" CFStringRef __cdecl CMTimeRangeCopyDescription(CFAllocatorRef allocator, CMTimeRange range);
extern "C" bool __cdecl CMTimeRangeEqual(CMTimeRange range1, CMTimeRange range2);
extern "C" CMTimeRange __cdecl CMTimeRangeFromTimeToTime(CMTime start, CMTime end_);
extern "C" CMTime __cdecl CMTimeRangeGetEnd(CMTimeRange range);
extern "C" CMTimeRange __cdecl CMTimeRangeGetIntersection(CMTimeRange range1, CMTimeRange range2);
extern "C" CMTimeRange __cdecl CMTimeRangeGetUnion(CMTimeRange range1, CMTimeRange range2);
extern "C" CMTimeRange __cdecl CMTimeRangeMake(CMTime start, CMTime duration);
extern "C" CMTimeRange __cdecl CMTimeRangeMakeFromDictionary(CFDictionaryRef dict);
extern "C" void __cdecl CMTimeRangeShow(CMTimeRange range);
extern "C" void __cdecl CMTimeShow(CMTime time);
extern "C" CMTime __cdecl CMTimeSubtract(CMTime minuend, CMTime subtrahend);
extern "C" int __cdecl CMVideoFormatDescriptionCreate(CFAllocatorRef allocator, unsigned codecType, int width, int height, CFDictionaryRef extensions, PCMVideoFormatDescriptionRef outDesc);
extern "C" int __cdecl CMVideoFormatDescriptionCreateForImageBuffer(CFAllocatorRef allocator, NativeInt imageBuffer, PCMVideoFormatDescriptionRef outDesc);
extern "C" Iosapi::Foundation::NSRect __cdecl CMVideoFormatDescriptionGetCleanAperture(NativeInt videoDesc, bool originIsAtTopLeft);
extern "C" CMVideoDimensions __cdecl CMVideoFormatDescriptionGetDimensions(NativeInt videoDesc);
extern "C" CFArrayRef __cdecl CMVideoFormatDescriptionGetExtensionKeysCommonWithImageBuffers(void);
extern "C" Iosapi::Foundation::NSSize __cdecl CMVideoFormatDescriptionGetPresentationDimensions(NativeInt videoDesc, bool usePixelAspectRatio, bool useCleanAperture);
extern "C" bool __cdecl CMVideoFormatDescriptionMatchesImageBuffer(NativeInt desc, NativeInt imageBuffer);
}	/* namespace Coremedia */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_COREMEDIA)
using namespace Iosapi::Coremedia;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_CoremediaHPP
