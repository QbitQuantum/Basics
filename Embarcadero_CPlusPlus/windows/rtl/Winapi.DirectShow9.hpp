// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.DirectShow9.pas' rev: 34.00 (Windows)

#ifndef Winapi_Directshow9HPP
#define Winapi_Directshow9HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>
#include <Winapi.DirectDraw.hpp>
#include <Winapi.DirectSound.hpp>
#include <Winapi.Direct3D9.hpp>
#include <Winapi.MMSystem.hpp>
#include <System.SyncObjs.hpp>
#include <System.Win.ComObj.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
#if(DIRECT3D_VERSION > 0x0700)
typedef struct IDirect3D            *LPDIRECT3D;
typedef struct IDirect3DDevice      *LPDIRECT3DDEVICE;
typedef struct IDirect3D2           *LPDIRECT3D2;
typedef struct IDirect3DDevice2     *LPDIRECT3DDEVICE2;
typedef struct IDirect3DViewport    *LPDIRECT3DVIEWPORT;
#endif
#define __KS__
#define __STREAMS__
#include "comlite.h"
#include "errors.h"
#include "dv.h"
#include "strmif.h"
#include "mmstream.h"
#include "amstream.h"
#include "ddstream.h"
#include "austream.h"
#include "mpconfig.h"
#include "control.h"
#include "qnetwork.h"
#include "playlist.h"
#include "il21dec.h"
#include "amvideo.h"
#include "amaudio.h"
#include "vptype.h"
#include "vpconfig.h"
#include "vpnotify.h"
#include "mmreg.h"
#include "mpegtype.h"
#include "dvdevcod.h"
#include "dvdmedia.h"
#include "bdatypes.h"
#include "activecf.h"
#include "vfwmsgs.h"
#include "edevdefs.h"
#include "XPrtDefs.h"
#include "aviriff.h"
#include "evcode.h"
#include "DXVA.h"
#include "AMVA.h"
#include "videoacc.h"
#include "regbag.h"
#include "tuner.h"
#include "DXTrans.h"
#include "QEdit.h"
#include "dshowasf.h"
#include "amparse.h"
#include "audevcod.h"
#include "MediaErr.h"
#include "MedParam.h"
#include "mediaobj.h"
#include "dmodshow.h"
#include "dmoreg.h"
#include "DMORt.h"
#include "dmoimpl.h"
#include "uuids.h"
#include "ks.h"
#include "ksproxy.h"
#include "ksmedia.h"
#include "bdamedia.h"
#include "Bdatif.h"
#include "atsmedia.h"
#include "dmksctrl.h"
#include "Mixerocx.h"
#include "Mpeg2Data.h"
#include "Mpeg2Bits.h"
#include "Mpeg2Error.h"
#include "sbe.h"
#include "vmr9.h"
#include "iwstdec.h"
typedef System::DelphiInterface<IPin> _di_IPin;
typedef System::DelphiInterface<IEnumPins> _di_IEnumPins;
typedef System::DelphiInterface<IEnumMediaTypes> _di_IEnumMediaTypes;
typedef System::DelphiInterface<IFilterGraph> _di_IFilterGraph;
typedef System::DelphiInterface<IEnumFilters> _di_IEnumFilters;
typedef System::DelphiInterface<IMediaFilter> _di_IMediaFilter;
typedef System::DelphiInterface<IBaseFilter> _di_IBaseFilter;
typedef System::DelphiInterface<IReferenceClock2> _di_IReferenceClock2;
typedef System::DelphiInterface<IMediaSample> _di_IMediaSample;
typedef System::DelphiInterface<IMediaSample2> _di_IMediaSample2;
typedef System::DelphiInterface<IMemAllocator> _di_IMemAllocator;
typedef System::DelphiInterface<IMemAllocatorNotifyCallbackTemp> _di_IMemAllocatorNotifyCallbackTemp;
typedef System::DelphiInterface<IMemAllocatorCallbackTemp> _di_IMemAllocatorCallbackTemp;
typedef System::DelphiInterface<IMemInputPin> _di_IMemInputPin;
typedef System::DelphiInterface<IAMovieSetup> _di_IAMovieSetup;
typedef System::DelphiInterface<IMediaSeeking> _di_IMediaSeeking;
typedef System::DelphiInterface<IEnumRegFilters> _di_IEnumRegFilters;
typedef System::DelphiInterface<IFilterMapper> _di_IFilterMapper;
typedef System::DelphiInterface<IFilterMapper2> _di_IFilterMapper2;
typedef System::DelphiInterface<IQualityControl> _di_IQualityControl;
typedef System::DelphiInterface<IOverlayNotify> _di_IOverlayNotify;
typedef System::DelphiInterface<IOverlayNotify2> _di_IOverlayNotify2;
typedef System::DelphiInterface<IOverlay> _di_IOverlay;
typedef System::DelphiInterface<IMediaEventSink> _di_IMediaEventSink;
typedef System::DelphiInterface<IFileSourceFilter> _di_IFileSourceFilter;
typedef System::DelphiInterface<IFileSinkFilter> _di_IFileSinkFilter;
typedef System::DelphiInterface<IFileSinkFilter2> _di_IFileSinkFilter2;
typedef System::DelphiInterface<IGraphBuilder> _di_IGraphBuilder;
typedef System::DelphiInterface<ICaptureGraphBuilder> _di_ICaptureGraphBuilder;
typedef System::DelphiInterface<ICaptureGraphBuilder2> _di_ICaptureGraphBuilder2;
typedef System::DelphiInterface<IAMCopyCaptureFileProgress> _di_IAMCopyCaptureFileProgress;
typedef System::DelphiInterface<IFilterGraph2> _di_IFilterGraph2;
typedef System::DelphiInterface<IStreamBuilder> _di_IStreamBuilder;
typedef System::DelphiInterface<IAsyncReader> _di_IAsyncReader;
typedef System::DelphiInterface<IGraphVersion> _di_IGraphVersion;
typedef System::DelphiInterface<IResourceConsumer> _di_IResourceConsumer;
typedef System::DelphiInterface<IResourceManager> _di_IResourceManager;
typedef System::DelphiInterface<IDistributorNotify> _di_IDistributorNotify;
typedef System::DelphiInterface<IAMStreamControl> _di_IAMStreamControl;
typedef System::DelphiInterface<ISeekingPassThru> _di_ISeekingPassThru;
typedef System::DelphiInterface<IAMStreamConfig> _di_IAMStreamConfig;
typedef System::DelphiInterface<IConfigInterleaving> _di_IConfigInterleaving;
typedef System::DelphiInterface<IConfigAviMux> _di_IConfigAviMux;
typedef System::DelphiInterface<IAMVideoCompression> _di_IAMVideoCompression;
typedef System::DelphiInterface<IAMVfwCaptureDialogs> _di_IAMVfwCaptureDialogs;
typedef System::DelphiInterface<IAMVfwCompressDialogs> _di_IAMVfwCompressDialogs;
typedef System::DelphiInterface<IAMDroppedFrames> _di_IAMDroppedFrames;
typedef System::DelphiInterface<IAMAudioInputMixer> _di_IAMAudioInputMixer;
typedef System::DelphiInterface<IAMBufferNegotiation> _di_IAMBufferNegotiation;
typedef System::DelphiInterface<IAMAnalogVideoDecoder> _di_IAMAnalogVideoDecoder;
typedef System::DelphiInterface<IAMVideoProcAmp> _di_IAMVideoProcAmp;
typedef System::DelphiInterface<IAMCameraControl> _di_IAMCameraControl;
typedef System::DelphiInterface<IAMVideoControl> _di_IAMVideoControl;
typedef System::DelphiInterface<IAMCrossbar> _di_IAMCrossbar;
typedef System::DelphiInterface<IAMTuner> _di_IAMTuner;
typedef System::DelphiInterface<IAMTunerNotification> _di_IAMTunerNotification;
typedef System::DelphiInterface<IAMTVTuner> _di_IAMTVTuner;
typedef System::DelphiInterface<IBPCSatelliteTuner> _di_IBPCSatelliteTuner;
typedef System::DelphiInterface<IAMTVAudio> _di_IAMTVAudio;
typedef System::DelphiInterface<IAMTVAudioNotification> _di_IAMTVAudioNotification;
typedef System::DelphiInterface<IAMAnalogVideoEncoder> _di_IAMAnalogVideoEncoder;
typedef System::DelphiInterface<IKsPropertySet> _di_IKsPropertySet;
typedef System::DelphiInterface<IMediaPropertyBag> _di_IMediaPropertyBag;
typedef System::DelphiInterface<IPersistMediaPropertyBag> _di_IPersistMediaPropertyBag;
typedef System::DelphiInterface<IAMPhysicalPinInfo> _di_IAMPhysicalPinInfo;
typedef System::DelphiInterface<IAMExtDevice> _di_IAMExtDevice;
typedef System::DelphiInterface<IAMExtTransport> _di_IAMExtTransport;
typedef System::DelphiInterface<IAMTimecodeReader> _di_IAMTimecodeReader;
typedef System::DelphiInterface<IAMTimecodeGenerator> _di_IAMTimecodeGenerator;
typedef System::DelphiInterface<IAMTimecodeDisplay> _di_IAMTimecodeDisplay;
typedef System::DelphiInterface<IAMDevMemoryAllocator> _di_IAMDevMemoryAllocator;
typedef System::DelphiInterface<IAMDevMemoryControl> _di_IAMDevMemoryControl;
typedef System::DelphiInterface<IAMStreamSelect> _di_IAMStreamSelect;
typedef System::DelphiInterface<IAMResourceControl> _di_IAMResourceControl;
typedef System::DelphiInterface<IAMClockAdjust> _di_IAMClockAdjust;
typedef System::DelphiInterface<IAMFilterMiscFlags> _di_IAMFilterMiscFlags;
typedef System::DelphiInterface<IDrawVideoImage> _di_IDrawVideoImage;
typedef System::DelphiInterface<IDecimateVideoImage> _di_IDecimateVideoImage;
typedef System::DelphiInterface<IAMVideoDecimationProperties> _di_IAMVideoDecimationProperties;
typedef System::DelphiInterface<IAMLatency> _di_IAMLatency;
typedef System::DelphiInterface<IAMPushSource> _di_IAMPushSource;
typedef System::DelphiInterface<IAMDeviceRemoval> _di_IAMDeviceRemoval;
typedef System::DelphiInterface<IDVEnc> _di_IDVEnc;
typedef System::DelphiInterface<IIPDVDec> _di_IIPDVDec;
typedef System::DelphiInterface<IDVRGB219> _di_IDVRGB219;
typedef System::DelphiInterface<IDVSplitter> _di_IDVSplitter;
typedef System::DelphiInterface<IAMAudioRendererStats> _di_IAMAudioRendererStats;
typedef System::DelphiInterface<IAMGraphStreams> _di_IAMGraphStreams;
typedef System::DelphiInterface<IAMOverlayFX> _di_IAMOverlayFX;
typedef System::DelphiInterface<IAMOpenProgress> _di_IAMOpenProgress;
typedef System::DelphiInterface<IMpeg2Demultiplexer> _di_IMpeg2Demultiplexer;
typedef System::DelphiInterface<IEnumStreamIdMap> _di_IEnumStreamIdMap;
typedef System::DelphiInterface<IMPEG2StreamIdMap> _di_IMPEG2StreamIdMap;
typedef System::DelphiInterface<IRegisterServiceProvider> _di_IRegisterServiceProvider;
typedef System::DelphiInterface<IAMClockSlave> _di_IAMClockSlave;
typedef System::DelphiInterface<IAMGraphBuilderCallback> _di_IAMGraphBuilderCallback;
typedef System::DelphiInterface<IAMFilterGraphCallback> _di_IAMFilterGraphCallback;
typedef System::DelphiInterface<ICodecAPI> _di_ICodecAPI;
typedef System::DelphiInterface<IGetCapabilitiesKey> _di_IGetCapabilitiesKey;
typedef System::DelphiInterface<IEncoderAPI> _di_IEncoderAPI;
typedef System::DelphiInterface<IVideoEncoder> _di_IVideoEncoder;
typedef System::DelphiInterface<IAMDecoderCaps> _di_IAMDecoderCaps;
typedef System::DelphiInterface<IAMCertifiedOutputProtection> _di_IAMCertifiedOutputProtection;
typedef System::DelphiInterface<ICreateDevEnum> _di_ICreateDevEnum;
typedef System::DelphiInterface<IFilterMapper3> _di_IFilterMapper3;
typedef System::DelphiInterface<IDvdState> _di_IDvdState;
typedef System::DelphiInterface<IDvdCmd> _di_IDvdCmd;
typedef System::DelphiInterface<IDvdControl> _di_IDvdControl;
typedef System::DelphiInterface<IDvdControl2> _di_IDvdControl2;
typedef System::DelphiInterface<IDvdInfo> _di_IDvdInfo;
typedef System::DelphiInterface<IDvdInfo2> _di_IDvdInfo2;
typedef System::DelphiInterface<IVideoFrameStep> _di_IVideoFrameStep;
typedef System::DelphiInterface<IDvdGraphBuilder> _di_IDvdGraphBuilder;
typedef System::DelphiInterface<IDDrawExclModeVideoCallback> _di_IDDrawExclModeVideoCallback;
typedef System::DelphiInterface<IDDrawExclModeVideo> _di_IDDrawExclModeVideo;
typedef System::DelphiInterface<IPinConnection> _di_IPinConnection;
typedef System::DelphiInterface<IPinFlowControl> _di_IPinFlowControl;
typedef System::DelphiInterface<IGraphConfigCallback> _di_IGraphConfigCallback;
typedef System::DelphiInterface<IGraphConfig> _di_IGraphConfig;
typedef System::DelphiInterface<IFilterChain> _di_IFilterChain;
typedef System::DelphiInterface<IVMRImagePresenter> _di_IVMRImagePresenter;
typedef System::DelphiInterface<IVMRSurfaceAllocator> _di_IVMRSurfaceAllocator;
typedef System::DelphiInterface<IVMRSurfaceAllocatorNotify> _di_IVMRSurfaceAllocatorNotify;
typedef System::DelphiInterface<IVMRWindowlessControl> _di_IVMRWindowlessControl;
typedef System::DelphiInterface<IVMRMixerControl> _di_IVMRMixerControl;
typedef System::DelphiInterface<IVMRMonitorConfig> _di_IVMRMonitorConfig;
typedef System::DelphiInterface<IVMRImageCompositor> _di_IVMRImageCompositor;
typedef System::DelphiInterface<IVMRFilterConfig> _di_IVMRFilterConfig;
typedef System::DelphiInterface<IVMRAspectRatioControl> _di_IVMRAspectRatioControl;
typedef System::DelphiInterface<IVMRDeinterlaceControl> _di_IVMRDeinterlaceControl;
typedef System::DelphiInterface<IVMRMixerBitmap> _di_IVMRMixerBitmap;
typedef System::DelphiInterface<IVMRVideoStreamControl> _di_IVMRVideoStreamControl;
typedef System::DelphiInterface<IVMRSurface> _di_IVMRSurface;
typedef System::DelphiInterface<IVMRImagePresenterConfig> _di_IVMRImagePresenterConfig;
typedef System::DelphiInterface<IVMRImagePresenterExclModeConfig> _di_IVMRImagePresenterExclModeConfig;
typedef System::DelphiInterface<IVPManager> _di_IVPManager;
typedef System::DelphiInterface<IMultiMediaStream> _di_IMultiMediaStream;
typedef System::DelphiInterface<IMediaStream> _di_IMediaStream;
typedef System::DelphiInterface<IStreamSample> _di_IStreamSample;
typedef System::DelphiInterface<IDirectShowStream> _di_IDirectShowStream;
typedef System::DelphiInterface<IAMMultiMediaStream> _di_IAMMultiMediaStream;
typedef System::DelphiInterface<IAMMediaStream> _di_IAMMediaStream;
typedef System::DelphiInterface<IMediaStreamFilter> _di_IMediaStreamFilter;
typedef System::DelphiInterface<IDirectDrawMediaSampleAllocator> _di_IDirectDrawMediaSampleAllocator;
typedef System::DelphiInterface<IDirectDrawMediaSample> _di_IDirectDrawMediaSample;
typedef System::DelphiInterface<IAMMediaTypeStream> _di_IAMMediaTypeStream;
typedef System::DelphiInterface<IAMMediaTypeSample> _di_IAMMediaTypeSample;
typedef System::DelphiInterface<IDirectDrawMediaStream> _di_IDirectDrawMediaStream;
typedef System::DelphiInterface<IDirectDrawStreamSample> _di_IDirectDrawStreamSample;
typedef System::DelphiInterface<IAudioMediaStream> _di_IAudioMediaStream;
typedef System::DelphiInterface<IAudioStreamSample> _di_IAudioStreamSample;
typedef System::DelphiInterface<IMemoryData> _di_IMemoryData;
typedef System::DelphiInterface<IAudioData> _di_IAudioData;
typedef System::DelphiInterface<IMixerPinConfig> _di_IMixerPinConfig;
typedef System::DelphiInterface<IMixerPinConfig2> _di_IMixerPinConfig2;
typedef System::DelphiInterface<IAMCollection> _di_IAMCollection;
typedef System::DelphiInterface<IMediaControl> _di_IMediaControl;
typedef System::DelphiInterface<IMediaEvent> _di_IMediaEvent;
typedef System::DelphiInterface<IMediaEventEx> _di_IMediaEventEx;
typedef System::DelphiInterface<IMediaPosition> _di_IMediaPosition;
typedef System::DelphiInterface<IBasicAudio> _di_IBasicAudio;
typedef System::DelphiInterface<IVideoWindow> _di_IVideoWindow;
typedef System::DelphiInterface<IBasicVideo> _di_IBasicVideo;
typedef System::DelphiInterface<IBasicVideo2> _di_IBasicVideo2;
typedef System::DelphiInterface<IDeferredCommand> _di_IDeferredCommand;
typedef System::DelphiInterface<IQueueCommand> _di_IQueueCommand;
typedef System::DelphiInterface<IFilterInfo> _di_IFilterInfo;
typedef System::DelphiInterface<IRegFilterInfo> _di_IRegFilterInfo;
typedef System::DelphiInterface<IMediaTypeInfo> _di_IMediaTypeInfo;
typedef System::DelphiInterface<IPinInfo> _di_IPinInfo;
typedef System::DelphiInterface<IAMStats> _di_IAMStats;
typedef System::DelphiInterface<IAMNetShowConfig> _di_IAMNetShowConfig;
typedef System::DelphiInterface<IAMChannelInfo> _di_IAMChannelInfo;
typedef System::DelphiInterface<IAMNetworkStatus> _di_IAMNetworkStatus;
typedef System::DelphiInterface<IAMExtendedSeeking> _di_IAMExtendedSeeking;
typedef System::DelphiInterface<IAMNetShowExProps> _di_IAMNetShowExProps;
typedef System::DelphiInterface<IAMExtendedErrorInfo> _di_IAMExtendedErrorInfo;
typedef System::DelphiInterface<IAMMediaContent> _di_IAMMediaContent;
typedef System::DelphiInterface<IAMMediaContent2> _di_IAMMediaContent2;
typedef System::DelphiInterface<IAMNetShowPreroll> _di_IAMNetShowPreroll;
typedef System::DelphiInterface<IDShowPlugin> _di_IDShowPlugin;
typedef System::DelphiInterface<IAMPlayListItem> _di_IAMPlayListItem;
typedef System::DelphiInterface<IAMPlayList> _di_IAMPlayList;
typedef System::DelphiInterface<ISpecifyParticularPages> _di_ISpecifyParticularPages;
typedef System::DelphiInterface<IAMRebuild> _di_IAMRebuild;
typedef System::DelphiInterface<IDirectDrawVideo> _di_IDirectDrawVideo;
typedef System::DelphiInterface<IQualProp> _di_IQualProp;
typedef System::DelphiInterface<IFullScreenVideo> _di_IFullScreenVideo;
typedef System::DelphiInterface<IFullScreenVideoEx> _di_IFullScreenVideoEx;
typedef System::DelphiInterface<IBaseVideoMixer> _di_IBaseVideoMixer;
typedef System::DelphiInterface<IAMDirectSound> _di_IAMDirectSound;
typedef System::DelphiInterface<IVPBaseConfig> _di_IVPBaseConfig;
typedef System::DelphiInterface<IVPConfig> _di_IVPConfig;
typedef System::DelphiInterface<IVPVBIConfig> _di_IVPVBIConfig;
typedef System::DelphiInterface<IVPBaseNotify> _di_IVPBaseNotify;
typedef System::DelphiInterface<IVPNotify> _di_IVPNotify;
typedef System::DelphiInterface<IVPNotify2> _di_IVPNotify2;
typedef System::DelphiInterface<IVPVBINotify> _di_IVPVBINotify;
typedef System::DelphiInterface<IMpegAudioDecoder> _di_IMpegAudioDecoder;
typedef System::DelphiInterface<IAMLine21Decoder> _di_IAMLine21Decoder;
typedef System::DelphiInterface<IAMVideoAcceleratorNotify> _di_IAMVideoAcceleratorNotify;
typedef System::DelphiInterface<IAMVideoAccelerator> _di_IAMVideoAccelerator;
typedef System::DelphiInterface<ICreatePropBagOnRegKey> _di_ICreatePropBagOnRegKey;
typedef System::DelphiInterface<ITuningSpaces> _di_ITuningSpaces;
typedef System::DelphiInterface<ITuningSpaceContainer> _di_ITuningSpaceContainer;
typedef System::DelphiInterface<ITuningSpace> _di_ITuningSpace;
typedef System::DelphiInterface<IEnumTuningSpaces> _di_IEnumTuningSpaces;
typedef System::DelphiInterface<IDVBTuningSpace> _di_IDVBTuningSpace;
typedef System::DelphiInterface<IDVBTuningSpace2> _di_IDVBTuningSpace2;
typedef System::DelphiInterface<IDVBSTuningSpace> _di_IDVBSTuningSpace;
typedef System::DelphiInterface<IAuxInTuningSpace> _di_IAuxInTuningSpace;
typedef System::DelphiInterface<IAnalogTVTuningSpace> _di_IAnalogTVTuningSpace;
typedef System::DelphiInterface<IATSCTuningSpace> _di_IATSCTuningSpace;
typedef System::DelphiInterface<IAnalogRadioTuningSpace> _di_IAnalogRadioTuningSpace;
typedef System::DelphiInterface<ITuneRequest> _di_ITuneRequest;
typedef System::DelphiInterface<IChannelTuneRequest> _di_IChannelTuneRequest;
typedef System::DelphiInterface<IATSCChannelTuneRequest> _di_IATSCChannelTuneRequest;
typedef System::DelphiInterface<IDVBTuneRequest> _di_IDVBTuneRequest;
typedef System::DelphiInterface<IMPEG2TuneRequest> _di_IMPEG2TuneRequest;
typedef System::DelphiInterface<IMPEG2TuneRequestFactory> _di_IMPEG2TuneRequestFactory;
typedef System::DelphiInterface<IMPEG2TuneRequestSupport> _di_IMPEG2TuneRequestSupport;
typedef System::DelphiInterface<ITuner> _di_ITuner;
typedef System::DelphiInterface<IScanningTuner> _di_IScanningTuner;
typedef System::DelphiInterface<IComponentType> _di_IComponentType;
typedef System::DelphiInterface<ILanguageComponentType> _di_ILanguageComponentType;
typedef System::DelphiInterface<IMPEG2ComponentType> _di_IMPEG2ComponentType;
typedef System::DelphiInterface<IATSCComponentType> _di_IATSCComponentType;
typedef System::DelphiInterface<IEnumComponentTypes> _di_IEnumComponentTypes;
typedef System::DelphiInterface<IComponentTypes> _di_IComponentTypes;
typedef System::DelphiInterface<IComponent> _di_IComponent;
typedef System::DelphiInterface<IMPEG2Component> _di_IMPEG2Component;
typedef System::DelphiInterface<IEnumComponents> _di_IEnumComponents;
typedef System::DelphiInterface<IComponents> _di_IComponents;
typedef System::DelphiInterface<ILocator> _di_ILocator;
typedef System::DelphiInterface<IATSCLocator> _di_IATSCLocator;
typedef System::DelphiInterface<IDVBTLocator> _di_IDVBTLocator;
typedef System::DelphiInterface<IDVBSLocator> _di_IDVBSLocator;
typedef System::DelphiInterface<IDVBCLocator> _di_IDVBCLocator;
typedef System::DelphiInterface<IBroadcastEvent> _di_IBroadcastEvent;
typedef System::DelphiInterface<IDXBaseObject> _di_IDXBaseObject;
typedef System::DelphiInterface<IDXTransform> _di_IDXTransform;
typedef System::DelphiInterface<IDXTransformFactory> _di_IDXTransformFactory;
typedef System::DelphiInterface<IDXSurfacePick> _di_IDXSurfacePick;
typedef System::DelphiInterface<IDXTBindHost> _di_IDXTBindHost;
typedef System::DelphiInterface<IDXTaskManager> _di_IDXTaskManager;
typedef System::DelphiInterface<IDXDCLock> _di_IDXDCLock;
typedef System::DelphiInterface<IDXSurface> _di_IDXSurface;
typedef System::DelphiInterface<IDXSurfaceFactory> _di_IDXSurfaceFactory;
typedef System::DelphiInterface<IDXLookupTable> _di_IDXLookupTable;
typedef System::DelphiInterface<IDXSurfaceModifier> _di_IDXSurfaceModifier;
typedef System::DelphiInterface<IDXSurfaceInit> _di_IDXSurfaceInit;
typedef System::DelphiInterface<IDXRawSurface> _di_IDXRawSurface;
typedef System::DelphiInterface<IDXARGBSurfaceInit> _di_IDXARGBSurfaceInit;
typedef System::DelphiInterface<IDXARGBReadPtr> _di_IDXARGBReadPtr;
typedef System::DelphiInterface<IDXARGBReadWritePtr> _di_IDXARGBReadWritePtr;
typedef System::DelphiInterface<IDXTScaleOutput> _di_IDXTScaleOutput;
typedef System::DelphiInterface<IDXGradient> _di_IDXGradient;
typedef System::DelphiInterface<IDXTScale> _di_IDXTScale;
typedef System::DelphiInterface<IDXEffect> _di_IDXEffect;
typedef System::DelphiInterface<IHTMLDXTransform> _di_IHTMLDXTransform;
typedef System::DelphiInterface<IPropertySetter> _di_IPropertySetter;
typedef System::DelphiInterface<IDxtCompositor> _di_IDxtCompositor;
typedef System::DelphiInterface<IDxtAlphaSetter> _di_IDxtAlphaSetter;
typedef System::DelphiInterface<IDxtJpeg> _di_IDxtJpeg;
typedef System::DelphiInterface<IDxtKey> _di_IDxtKey;
typedef System::DelphiInterface<IMediaLocator> _di_IMediaLocator;
typedef System::DelphiInterface<IMediaDet> _di_IMediaDet;
typedef System::DelphiInterface<IGrfCache> _di_IGrfCache;
typedef System::DelphiInterface<IRenderEngine> _di_IRenderEngine;
typedef System::DelphiInterface<IRenderEngine2> _di_IRenderEngine2;
typedef System::DelphiInterface<IFindCompressorCB> _di_IFindCompressorCB;
typedef System::DelphiInterface<ISmartRenderEngine> _di_ISmartRenderEngine;
typedef System::DelphiInterface<IAMTimelineObj> _di_IAMTimelineObj;
typedef System::DelphiInterface<IAMTimelineEffectable> _di_IAMTimelineEffectable;
typedef System::DelphiInterface<IAMTimelineEffect> _di_IAMTimelineEffect;
typedef System::DelphiInterface<IAMTimelineTransable> _di_IAMTimelineTransable;
typedef System::DelphiInterface<IAMTimelineSplittable> _di_IAMTimelineSplittable;
typedef System::DelphiInterface<IAMTimelineTrans> _di_IAMTimelineTrans;
typedef System::DelphiInterface<IAMTimelineSrc> _di_IAMTimelineSrc;
typedef System::DelphiInterface<IAMTimelineTrack> _di_IAMTimelineTrack;
typedef System::DelphiInterface<IAMTimelineVirtualTrack> _di_IAMTimelineVirtualTrack;
typedef System::DelphiInterface<IAMTimelineComp> _di_IAMTimelineComp;
typedef System::DelphiInterface<IAMTimelineGroup> _di_IAMTimelineGroup;
typedef System::DelphiInterface<IAMTimeline> _di_IAMTimeline;
typedef System::DelphiInterface<IXml2Dex> _di_IXml2Dex;
typedef System::DelphiInterface<IAMErrorLog> _di_IAMErrorLog;
typedef System::DelphiInterface<IAMSetErrorLog> _di_IAMSetErrorLog;
typedef System::DelphiInterface<ISampleGrabberCB> _di_ISampleGrabberCB;
typedef System::DelphiInterface<ISampleGrabber> _di_ISampleGrabber;
typedef System::DelphiInterface<IResize> _di_IResize;
typedef System::DelphiInterface<IConfigAsfWriter> _di_IConfigAsfWriter;
typedef System::DelphiInterface<IAMParse> _di_IAMParse;
typedef System::DelphiInterface<IMediaParamInfo> _di_IMediaParamInfo;
typedef System::DelphiInterface<IMediaParams> _di_IMediaParams;
typedef System::DelphiInterface<IMediaBuffer> _di_IMediaBuffer;
typedef System::DelphiInterface<IMediaObject> _di_IMediaObject;
typedef System::DelphiInterface<IEnumDMO> _di_IEnumDMO;
typedef System::DelphiInterface<IMediaObjectInPlace> _di_IMediaObjectInPlace;
typedef System::DelphiInterface<IDMOQualityControl> _di_IDMOQualityControl;
typedef System::DelphiInterface<IDMOVideoOutputOptimizations> _di_IDMOVideoOutputOptimizations;
typedef System::DelphiInterface<IDMOWrapperFilter> _di_IDMOWrapperFilter;
typedef System::DelphiInterface<IKsClockPropertySet> _di_IKsClockPropertySet;
typedef System::DelphiInterface<IKsAllocator> _di_IKsAllocator;
typedef System::DelphiInterface<IKsAllocatorEx> _di_IKsAllocatorEx;
typedef System::DelphiInterface<IKsPin> _di_IKsPin;
typedef System::DelphiInterface<IKsPinEx> _di_IKsPinEx;
typedef System::DelphiInterface<IKsPinPipe> _di_IKsPinPipe;
typedef System::DelphiInterface<IKsPinFactory> _di_IKsPinFactory;
typedef System::DelphiInterface<IKsDataTypeHandler> _di_IKsDataTypeHandler;
typedef System::DelphiInterface<IKsDataTypeCompletion> _di_IKsDataTypeCompletion;
typedef System::DelphiInterface<IKsInterfaceHandler> _di_IKsInterfaceHandler;
typedef System::DelphiInterface<IKsObject> _di_IKsObject;
typedef System::DelphiInterface<IKsQualityForwarder> _di_IKsQualityForwarder;
typedef System::DelphiInterface<IKsNotifyEvent> _di_IKsNotifyEvent;
typedef System::DelphiInterface<IKsAggregateControl> _di_IKsAggregateControl;
typedef System::DelphiInterface<IKsTopology> _di_IKsTopology;
typedef System::DelphiInterface<IKsControl> _di_IKsControl;
typedef System::DelphiInterface<IBDA_NetworkProvider> _di_IBDA_NetworkProvider;
typedef System::DelphiInterface<IBDA_EthernetFilter> _di_IBDA_EthernetFilter;
typedef System::DelphiInterface<IBDA_IPV4Filter> _di_IBDA_IPV4Filter;
typedef System::DelphiInterface<IBDA_IPV6Filter> _di_IBDA_IPV6Filter;
typedef System::DelphiInterface<IBDA_DeviceControl> _di_IBDA_DeviceControl;
typedef System::DelphiInterface<IBDA_PinControl> _di_IBDA_PinControl;
typedef System::DelphiInterface<IBDA_SignalProperties> _di_IBDA_SignalProperties;
typedef System::DelphiInterface<IBDA_SignalStatistics> _di_IBDA_SignalStatistics;
typedef System::DelphiInterface<IBDA_Topology> _di_IBDA_Topology;
typedef System::DelphiInterface<IBDA_VoidTransform> _di_IBDA_VoidTransform;
typedef System::DelphiInterface<IBDA_NullTransform> _di_IBDA_NullTransform;
typedef System::DelphiInterface<IBDA_FrequencyFilter> _di_IBDA_FrequencyFilter;
typedef System::DelphiInterface<IBDA_LNBInfo> _di_IBDA_LNBInfo;
typedef System::DelphiInterface<IBDA_AutoDemodulate> _di_IBDA_AutoDemodulate;
typedef System::DelphiInterface<IBDA_DigitalDemodulator> _di_IBDA_DigitalDemodulator;
typedef System::DelphiInterface<IBDA_IPSinkControl> _di_IBDA_IPSinkControl;
typedef System::DelphiInterface<IBDA_IPSinkInfo> _di_IBDA_IPSinkInfo;
typedef System::DelphiInterface<IEnumPIDMap> _di_IEnumPIDMap;
typedef System::DelphiInterface<IMPEG2PIDMap> _di_IMPEG2PIDMap;
typedef System::DelphiInterface<IFrequencyMap> _di_IFrequencyMap;
typedef System::DelphiInterface<IBDA_TIF_REGISTRATION> _di_IBDA_TIF_REGISTRATION;
typedef System::DelphiInterface<IMPEG2_TIF_CONTROL> _di_IMPEG2_TIF_CONTROL;
typedef System::DelphiInterface<ITuneRequestInfo> _di_ITuneRequestInfo;
typedef System::DelphiInterface<IGuideDataEvent> _di_IGuideDataEvent;
typedef System::DelphiInterface<IGuideDataProperty> _di_IGuideDataProperty;
typedef System::DelphiInterface<IEnumGuideDataProperties> _di_IEnumGuideDataProperties;
typedef System::DelphiInterface<IEnumTuneRequests> _di_IEnumTuneRequests;
typedef System::DelphiInterface<IGuideData> _di_IGuideData;
typedef System::DelphiInterface<IGuideDataLoader> _di_IGuideDataLoader;
typedef System::DelphiInterface<IMixerOCXNotify> _di_IMixerOCXNotify;
typedef System::DelphiInterface<IMixerOCX> _di_IMixerOCX;
typedef System::DelphiInterface<IMpeg2Data> _di_IMpeg2Data;
typedef System::DelphiInterface<ISectionList> _di_ISectionList;
typedef System::DelphiInterface<IMpeg2Stream> _di_IMpeg2Stream;
typedef System::DelphiInterface<IStreamBufferInitialize> _di_IStreamBufferInitialize;
typedef System::DelphiInterface<IStreamBufferSink> _di_IStreamBufferSink;
typedef System::DelphiInterface<IStreamBufferSource> _di_IStreamBufferSource;
typedef System::DelphiInterface<IStreamBufferRecordControl> _di_IStreamBufferRecordControl;
typedef System::DelphiInterface<IStreamBufferRecComp> _di_IStreamBufferRecComp;
typedef System::DelphiInterface<IStreamBufferRecordingAttribute> _di_IStreamBufferRecordingAttribute;
typedef System::DelphiInterface<IEnumStreamBufferRecordingAttrib> _di_IEnumStreamBufferRecordingAttrib;
typedef System::DelphiInterface<IStreamBufferConfigure> _di_IStreamBufferConfigure;
typedef System::DelphiInterface<IStreamBufferMediaSeeking> _di_IStreamBufferMediaSeeking;
typedef System::DelphiInterface<IVMRImagePresenter9> _di_IVMRImagePresenter9;
typedef System::DelphiInterface<IVMRSurfaceAllocator9> _di_IVMRSurfaceAllocator9;
typedef System::DelphiInterface<IVMRSurfaceAllocatorEx9> _di_IVMRSurfaceAllocatorEx9;
typedef System::DelphiInterface<IVMRSurfaceAllocatorNotify9> _di_IVMRSurfaceAllocatorNotify9;
typedef System::DelphiInterface<IVMRWindowlessControl9> _di_IVMRWindowlessControl9;
typedef System::DelphiInterface<IVMRMixerControl9> _di_IVMRMixerControl9;
typedef System::DelphiInterface<IVMRMixerBitmap9> _di_IVMRMixerBitmap9;
typedef System::DelphiInterface<IVMRSurface9> _di_IVMRSurface9;
typedef System::DelphiInterface<IVMRImagePresenterConfig9> _di_IVMRImagePresenterConfig9;
typedef System::DelphiInterface<IVMRDeinterlaceControl9> _di_IVMRDeinterlaceControl9;
typedef System::DelphiInterface<IVMRImageCompositor9> _di_IVMRImageCompositor9;
typedef System::DelphiInterface<IVMRVideoStreamControl9> _di_IVMRVideoStreamControl9;
typedef System::DelphiInterface<IVMRFilterConfig9> _di_IVMRFilterConfig9;
typedef System::DelphiInterface<IVMRAspectRatioControl9> _di_IVMRAspectRatioControl9;
typedef System::DelphiInterface<IVMRMonitorConfig9> _di_IVMRMonitorConfig9;
typedef System::DelphiInterface<IAMWstDecoder> _di_IAMWstDecoder;

namespace Winapi
{
namespace Directshow9
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef Tag_DVAudInfo TDVAudInfo;

typedef _AMMediaType *PAMMediaType;

typedef _AMMediaType TAMMediaType;

typedef _PinDirection TPinDirection;

typedef __int64 TReferenceTime;

using Winapi::Dxtypes::PReferenceTime;

typedef double TRefTime;

typedef _AllocatorProperties *PAllocatorProperties;

typedef _AllocatorProperties TAllocatorProperties;

typedef _PinInfo TPinInfo;

typedef _FilterState TFilterState;

typedef _FilterInfo TFilterInfo;

typedef tagAM_SAMPLE2_PROPERTIES *PAMSample2Properties;

typedef tagAM_SAMPLE2_PROPERTIES TAMSample2Properties;

#ifndef _WIN64
typedef System::StaticArray<_di_IMediaSample, 536870911> TIMediaSampleArray;
#else /* _WIN64 */
typedef System::StaticArray<_di_IMediaSample, 268435455> TIMediaSampleArray;
#endif /* _WIN64 */

typedef TIMediaSampleArray *PIMediaSampleArray;

typedef REGFILTER *PRegFilter;

typedef REGFILTER TRegFilter;

typedef REGPINTYPES *PRegPinTypes;

typedef REGPINTYPES TRegPinTypes;

typedef REGFILTERPINS *PRegFilterPins;

typedef REGFILTERPINS TRegFilterPins;

typedef REGPINMEDIUM *PRegPinMedium;

typedef REGPINMEDIUM TRegPinMedium;

typedef REGFILTERPINS2 *PRegFilterPins2;

typedef REGFILTERPINS2 TRegFilterPins2;

typedef REGFILTER2 *PRegFilter2;

typedef REGFILTER2 TRegFilter2;

typedef tagQualityMessageType TQualityMessageType;

typedef tagQuality *PQuality;

typedef tagQuality TQuality;

typedef tagCOLORKEY *PColorKey;

typedef tagCOLORKEY TColorKey;

typedef AM_FILESINK_FLAGS TAMFileSinkFlags;

typedef AM_STREAM_INFO *PAMStreamInfo;

typedef AM_STREAM_INFO TAMStreamInfo;

typedef _VIDEO_STREAM_CONFIG_CAPS *PVideoStreamConfigCaps;

typedef _VIDEO_STREAM_CONFIG_CAPS TVideoStreamConfigCaps;

typedef _AUDIO_STREAM_CONFIG_CAPS *PAudioStreamConfigCaps;

typedef _AUDIO_STREAM_CONFIG_CAPS TAudioStreamConfigCaps;

typedef InterleavingMode TInterleavingMode;

typedef tagTunerInputType TTunerInputType;

typedef VideoCopyProtectionType TVideoCopyProtectionType;

typedef unsigned TPhysicalConnectorType;

typedef tagVideoProcAmpProperty TVideoProcAmpProperty;

typedef tagVideoProcAmpFlags TVideoProcAmpFlags;

typedef tagCameraControlProperty TCameraControlProperty;

typedef tagCameraControlFlags TCameraControlFlags;

typedef tagAMTunerSubChannel TAMTunerSubChannel;

typedef tagAMTunerSignalStrength TAMTunerSignalStrength;

typedef tagAMTunerModeType TAMTunerModeType;

typedef tagAMTunerEventType TAMTunerEventType;

typedef tagTVAudioMode TTVAudioMode;

typedef tagAMTVAudioEventType TAMTVAudioEventType;

typedef AMPROPERTY_PIN TAMPropertyPin;

typedef _timecode *PTimeCode;

typedef _timecode TTimeCode;

typedef tagTIMECODE_SAMPLE *PTimeCodeSample;

typedef tagTIMECODE_SAMPLE TTimeCodeSample;

typedef _DECIMATION_USAGE TDecimationUsage;

typedef DVINFO *PTDVInfo;

typedef DVINFO TDVInfo;

typedef STREAM_ID_MAP *PStreamIDMap;

typedef STREAM_ID_MAP TStreamIDMap;

typedef CodecAPIEventData TCodecAPIEventData;

typedef VIDEOENCODER_BITRATE_MODE TVideoEncoderBitrateMode;

typedef AMCOPPSignature *PAMCOPPSignature;

typedef AMCOPPSignature TAMCOPPSignature;

typedef AMCOPPCommand TAMCOPPCommand;

typedef LPAMCOPPCommand PAMCOPPCommand;

typedef AMCOPPStatusInput TAMCOPPStatusInput;

typedef LPAMCOPPStatusInput PAMCOPPStatusInput;

typedef AMCOPPStatusOutput TAMCOPPStatusOutput;

typedef LPAMCOPPStatusOutput PAMCOPPStatusOutput;

typedef DVD_TextStringType TDVDTextStringType;

typedef DVD_OPTION_FLAG TDVDOptionFlag;

typedef tagDVD_DOMAIN TDVDDomain;

typedef tagDVD_MENU_ID TDVDMenuID;

typedef tagDVD_DISC_SIDE TDVDDiscSide;

typedef tagDVD_PREFERRED_DISPLAY_MODE TDVDPreferredDisplayMode;

typedef tagDVD_VIDEO_COMPRESSION TDVDVideoCompression;

typedef tagDVD_AUDIO_APPMODE TDVDAudioAPPMode;

typedef tagDVD_AUDIO_FORMAT TDVDAudioFormat;

typedef tagDVD_AUDIO_LANG_EXT TDVDAudioLangExt;

typedef tagDVD_SUBPICTURE_TYPE TDVDSubpictureType;

typedef tagDVD_SUBPICTURE_CODING TDVDSubpictureCoding;

typedef tagDVD_SUBPICTURE_LANG_EXT TDVDSubpictureLangExt;

typedef tagDVD_KARAOKE_ASSIGNMENT TDVDKaraokeAssignment;

typedef DVD_RELATIVE_BUTTON TDVDRelativeButton;

typedef SPRMArray TSPRMArray;

typedef tagDVD_ATR TDVDAtr;

typedef tagDVD_FRAMERATE TDVDFramerate;

typedef tagDVD_TIMECODE TDVDTimeCode;

typedef tagDVD_HMSF_TIMECODE *PDVDHMSFTimeCode;

typedef tagDVD_HMSF_TIMECODE TDVDHMSFTimeCode;

typedef tagDVD_PLAYBACK_LOCATION2 TDVDPlayBackLocation2;

typedef tagDVD_PLAYBACK_LOCATION TDVDPlaybackLocation;

typedef DVD_TextCharSet TDVDTextCharSet;

typedef tagDVD_DECODER_CAPS TDVDDecoderCaps;

typedef tagDVD_VideoAttributes TDVDVideoAttributes;

typedef tagDVD_SubpictureAttributes TDVDSubpictureAttributes;

typedef tagDVD_TITLE_APPMODE TDVDTitleAPPMode;

typedef tagDVD_MUA_MixingInfo TDVDMUAMixingInfo;

typedef tagDVD_MUA_Coeff TDVDMUACoeff;

typedef tagDVD_MultichannelAudioAttributes TDVDMultichannelAudioAttributes;

typedef tagDVD_AudioAttributes TDVDAudioAttributes;

typedef tagDVD_TitleMainAttributes TDVDTitleAttributes;

typedef tagDVD_MenuAttributes TDVDMenuAttributes;

typedef tagDVD_KaraokeAttributes TDVDKaraokeAttributes;

typedef System::StaticArray<System::Byte, 2> CountryCode;

typedef AM_DVD_RENDERSTATUS TAMDVDRenderStatus;

typedef tagVMRPRESENTATIONINFO *PVMRPresentationInfo;

typedef tagVMRPRESENTATIONINFO TVMRPresentationInfo;

typedef tagVMRALLOCATIONINFO *PVMRAllocationInfo;

typedef tagVMRALLOCATIONINFO TVMRAllocationInfo;

typedef VMR_ASPECT_RATIO_MODE TVMRAspectRatioMode;

typedef _NORMALIZEDRECT *PNormalizedRect;

typedef _NORMALIZEDRECT TNormalizedRect;

typedef tagVMRGUID TVMRGuid;

typedef tagVMRMONITORINFO TVMRMonitorInfo;

typedef _VMRVIDEOSTREAMINFO *PVMRVideoStreamInfo;

typedef _VMRVIDEOSTREAMINFO TVMRVideoStreamInfo;

typedef _VMRFrequency *PVMRFrequency;

typedef _VMRFrequency TVMRFrequency;

typedef _VMRVideoDesc *PVMRVideoDesc;

typedef _VMRVideoDesc TVMRVideoDesc;

typedef _VMRDeinterlaceCaps *PVMRDeinterlaceCaps;

typedef _VMRDeinterlaceCaps TVMRDeinterlaceCaps;

typedef _VMRALPHABITMAP *PVMRAlphaBitmap;

typedef _VMRALPHABITMAP TVMRAlphaBitmap;

typedef STREAM_TYPE *PStreamType;

typedef STREAM_TYPE TStreamType;

typedef STREAM_STATE TStreamState;

typedef OUTPUT_STATE TOutputState;

typedef _AM_ASPECT_RATIO_MODE TAMAspectRatioMode;

typedef tag_TRUECOLORINFO TTrueColorInfo;

typedef tagVIDEOINFOHEADER *PVideoInfoHeader;

typedef tagVIDEOINFOHEADER TVideoInfoHeader;

typedef tagVIDEOINFO *PVideoInfo;

typedef tagVIDEOINFO TVideoInfo;

typedef tagMPEG1VIDEOINFO *PMPEG1VideoInfo;

typedef tagMPEG1VIDEOINFO TMPEG1VideoInfo;

typedef tagAnalogVideoInfo TAnalogVideoInfo;

typedef AM_PROPERTY_FRAMESTEP TAMPropertyFramesStep;

typedef _AM_FRAMESTEP_STEP TAMFramestepStep;

typedef _AMVP_SELECT_FORMAT_BY TAMVPSelectFormatBy;

typedef _AMVP_MODE TAMVPMode;

typedef _AMVPSIZE *PAMVPSize;

typedef _AMVPSIZE TAMVPSize;

typedef _AMVPDIMINFO *PAMVPDimInfo;

typedef _AMVPDIMINFO TAMVPDimInfo;

typedef _AMVPDATAINFO *PAMVPDataInfo;

typedef _AMVPDATAINFO TAMVPDataInfo;

typedef tagAM_MPEGSTREAMTYPE TAMMPEGStreamType;

typedef tagAM_MPEGSYSTEMTYPE TAMMPEGSystemType;

typedef MPEG1WAVEFORMAT TMPEG1WaveFormat;

typedef _AM_LINE21_CCLEVEL TAMLine21CCLevel;

typedef _AM_LINE21_CCSERVICE TAMLine21CCService;

typedef _AM_LINE21_CCSTATE TAMLine21CCState;

typedef _AM_LINE21_CCSTYLE TAMLine21CCStyle;

typedef _AM_LINE21_DRAWBGMODE TAMLine21DrawBGMode;

typedef _tagDVD_ERROR TDVDError;

typedef _tagDVD_WARNING TDVDWarning;

typedef _tagDVD_PB_STOPPED TDVDPBStopped;

typedef AM_PROPERTY_AC3 TAMPropertyAC3;

typedef AM_AC3_ERROR_CONCEALMENT TAMAC3ErrorConcelment;

typedef AM_AC3_ALTERNATE_AUDIO TAMAC3AlteranateAudio;

typedef AM_AC3_DOWNMIX TAMAC3DownMix;

typedef AM_AC3_BIT_STREAM_MODE TAMAC3BitStreamMode;

typedef AM_AC3_DIALOGUE_LEVEL TAMAC3DialogueLevel;

typedef AM_AC3_ROOM_TYPE TAMAC3RoomType;

typedef AM_PROPERTY_DVDSUBPIC TAM_Property_DVDSubpic;

typedef _AM_DVD_YUV TAMDVDYUV;

typedef _AM_PROPERTY_SPPAL TAMPropertySPPAL;

typedef _AM_COLCON TAMColcon;

typedef _AM_PROPERTY_SPHLI TAMPropertySPHLI;

typedef _AM_DVDCOPY_CHLGKEY TAMDVDCopyCHLGKey;

typedef _AM_DVDCOPY_BUSKEY TAMDVDCopyBusKey;

typedef _AM_DVDCOPY_DISCKEY TAMDVDCopyDiscKey;

typedef AM_DVDCOPY_TITLEKEY TAMDVDCopyTitleKey;

typedef _AM_COPY_MACROVISION TAMCopyMacroVision;

typedef AM_DVDCOPY_SET_COPY_STATE TAMDVDCopySetCopyState;

typedef AM_DVDCOPYSTATE TAMDVDCopyState;

typedef AM_COPY_MACROVISION_LEVEL TAMCopyMacroVisionLevel;

typedef _DVD_REGION TDVDRegion;

typedef AM_MPEG2Level TAMMPEG2Level;

typedef AM_MPEG2Profile TAMMPEG2Profile;

typedef tagVIDEOINFOHEADER2 *PVideoInfoHeader2;

typedef tagVIDEOINFOHEADER2 TVideoInfoHeader2;

typedef tagMPEG2VIDEOINFO *PMPEG2VideoInfo;

typedef tagMPEG2VIDEOINFO TMPEG2VideoInfo;

typedef tagAM_DvdKaraokeData TAMDvdKaraokeData;

typedef AM_PROPERTY_DVDKARAOKE TAMPropertyDVDKaraoke;

typedef AM_PROPERTY_TS_RATE_CHANGE TAMPropertyTSRateChange;

typedef AM_PROPERTY_DVD_RATE_CHANGE TAMPropertyDVDRateChange;

typedef AM_SimpleRateChange TAMSimpleRateChange;

typedef AM_QueryRate TAMQueryRate;

typedef AM_ExactRateChange TAMExactRateChange;

typedef AM_DVD_ChangeRate TAMDVDChangeRate;

typedef DVD_PLAY_DIRECTION TDVDPlayDirection;

typedef tagVFW_FILTERLIST TVFWFilterList;

typedef _riffchunk *PRIFFChunk;

typedef _riffchunk TRIFFChunk;

typedef _rifflist *PRIFFList;

typedef _rifflist TRIFFList;

typedef _avimainheader TAVIMainHeader;

typedef _aviextheader TAVIExtHeader;

typedef _avistreamheader TAVIStreamHeader;

typedef _avioldindex TAVIOldIndex;

typedef _timecodedata TTimeCodeData;

typedef _avimetaindex TAVIMetaIndex;

typedef _avisuperindex TAVISuperIndex;

typedef _avistdindex_entry TAVIStdIndexEntry;

typedef _avistdindex TAVIStdIndex;

typedef _avitimedindex_entry TAVITimedIndexEntry;

typedef _avitimedindex TAVITimedIndex;

typedef _avitimecodeindex TAviTimeCodeIndex;

typedef _avitcdlindex_entry TAVITcdlIndexEntry;

typedef _avitcdlindex TAVITcdlIndex;

typedef _avifieldindex_chunk TAVIFieldIndex;

typedef AM_WMT_EVENT_DATA *PAMWMTEventData;

typedef AM_WMT_EVENT_DATA TAMWMTEventData;

typedef _DXVA_ConnectMode *PDXVAConnectMode;

typedef _DXVA_ConnectMode TDXVAConnectMode;

typedef _DXVA_EncryptProtocolHeader *PDXVAEncryptProtocolHeader;

typedef _DXVA_EncryptProtocolHeader TDXVAEncryptProtocolHeader;

typedef _DXVA_ConfigPictureDecode *PDXVAConfigPictureDecode;

typedef _DXVA_ConfigPictureDecode TDXVAConfigPictureDecode;

typedef _DXVA_PictureParameters *PDXVAPictureParameters;

typedef _DXVA_PictureParameters TDXVAPictureParameters;

typedef _DXVA_PicResample *PDXVAPicResample;

typedef _DXVA_PicResample TDXVAPicResample;

typedef _DXVA_BufferDescription *PDXVABufferDescription;

typedef _DXVA_BufferDescription TDXVABufferDescription;

typedef _DXVA_TCoef4Group *PDXVATCoef4Group;

typedef _DXVA_TCoef4Group TDXVATCoef4Group;

typedef _DXVA_TCoefSingle *PDXVATCoefSingle;

typedef _DXVA_TCoefSingle TDXVATCoefSingle;

typedef _DXVA_MVvalue *PDXVAMVvalue;

typedef _DXVA_MVvalue TDXVAMVvalue;

typedef _DXVA_QmatrixData *PDXVAQmatrixData;

typedef _DXVA_QmatrixData TDXVAQmatrixData;

typedef _DXVA_SliceInfo *PDXVASliceInfo;

typedef _DXVA_SliceInfo TDXVASliceInfo;

typedef _DXVA_MBctrl_I_HostResidDiff_1 TDXVAMBctrlIHostResidDiff1;

typedef _DXVA_MBctrl_I_OffHostIDCT_1 TDXVAMBctrlIOffHostIDCT1;

typedef _DXVA_MBctrl_P_HostResidDiff_1 TDXVAMBctrlPHostResidDiff1;

typedef _DXVA_MBctrl_P_OffHostIDCT_1 TDXVAMBctrlPOffHostIDCT1;

typedef _DXVA_ConfigAlphaLoad *PDXVAConfigAlphaLoad;

typedef _DXVA_ConfigAlphaLoad TDXVAConfigAlphaLoad;

typedef _DXVA_ConfigAlphaCombine *PDXVAConfigAlphaCombine;

typedef _DXVA_ConfigAlphaCombine TDXVAConfigAlphaCombine;

typedef _DXVA_AYUVsample2 *PDXVAAYUVsample2;

typedef _DXVA_AYUVsample2 TDXVAAYUVsample2;

typedef _DXVA_Highlight *PDXVAHighlight;

typedef _DXVA_Highlight TDXVAHighlight;

typedef _DXVA_BlendCombination *PDXVABlendCombination;

typedef _DXVA_BlendCombination TDXVABlendCombination;

typedef DXVA_SampleFormat TDXVASampleFormat;

typedef DXVA_VideoTransferFunction TDXVAVideoTransferFunction;

typedef DXVA_VideoPrimaries TDXVAVideoPrimaries;

typedef DXVA_VideoLighting TDXVAVideoLighting;

typedef DXVA_VideoTransferMatrix TDXVAVideoTransferMatrix;

typedef DXVA_NominalRange TDXVANominalRange;

typedef _DXVA_Frequency TDXVAFrequency;

typedef _DXVA_VideoDesc *PDXVAVideoDesc;

typedef _DXVA_VideoDesc TDXVAVideoDesc;

typedef _DXVA_VideoSample *PDXVAVideoSample;

typedef _DXVA_VideoSample TDXVAVideoSample;

typedef unsigned DXVA_DestinationFlags;

typedef DXVA_VideoSample2 *PDXVAVideoSample2;

typedef DXVA_VideoSample2 TDXVAVideoSample2;

typedef _DXVA_DeinterlaceCaps *PDXVADeinterlaceCaps;

typedef _DXVA_DeinterlaceCaps TDXVADeinterlaceCaps;

typedef _DXVA_DeinterlaceBlt *PDXVADeinterlaceBlt;

typedef _DXVA_DeinterlaceBlt TDXVADeinterlaceBlt;

typedef _DXVA_DeinterlaceQueryAvailableModes *PDXVADeinterlaceQueryAvailableModes;

typedef _DXVA_DeinterlaceQueryAvailableModes TDXVADeinterlaceQueryAvailableModes;

typedef _DXVA_DeinterlaceQueryModeCaps *PDXVADeinterlaceQueryModeCaps;

typedef _DXVA_DeinterlaceQueryModeCaps TDXVADeinterlaceQueryModeCaps;

typedef _DXVA_ProcAmpControlCaps *PDXVAProcAmpControlCaps;

typedef _DXVA_ProcAmpControlCaps TDXVAProcAmpControlCaps;

typedef _DXVA_ProcAmpControlQueryRange *PDXVAProcAmpControlQueryRange;

typedef _DXVA_ProcAmpControlQueryRange TDXVAProcAmpControlQueryRange;

typedef _DXVA_VideoPropertyRange *PDXVAVideoPropertyRange;

typedef _DXVA_VideoPropertyRange TDXVAVideoPropertyRange;

typedef _DXVA_ProcAmpControlBlt *PDXVAProcAmpControlBlt;

typedef _DXVA_ProcAmpControlBlt TDXVAProcAmpControlBlt;

typedef DXVA_COPPSignature *PDXVACOPPSignature;

typedef DXVA_COPPSignature TDXVACOPPSignature;

typedef DXVA_COPPCommand *PDXVACOPPCommand;

typedef DXVA_COPPCommand TDXVACOPPCommand;

typedef DXVA_COPPSetProtectionLevelCmdData *PDXVACOPPSetProtectionLevelCmdData;

typedef DXVA_COPPSetProtectionLevelCmdData TDXVACOPPSetProtectionLevelCmdData;

typedef DXVA_COPPSetSignalingCmdData TDXVACOPPSetSignalingCmdData;

typedef COPP_ImageAspectRatio_EN300294 TCOPPImageAspectRatioEN300294;

typedef DXVA_COPPStatusInput *PDXVACOPPStatusInput;

typedef DXVA_COPPStatusInput TDXVACOPPStatusInput;

typedef DXVA_COPPStatusOutput *PDXVACOPPStatusOutput;

typedef DXVA_COPPStatusOutput TDXVACOPPStatusOutput;

typedef COPP_StatusFlags TCOPPStatusFlags;

typedef DXVA_COPPStatusData *PDXVACOPPStatusData;

typedef DXVA_COPPStatusData TDXVACOPPStatusData;

typedef DXVA_COPPStatusHDCPKeyData *PDXVACOPPStatusHDCPKeyData;

typedef DXVA_COPPStatusHDCPKeyData TDXVACOPPStatusHDCPKeyData;

typedef COPP_ConnectorType TCOPPConnectorType;

typedef COPP_BusType TCOPPBusType;

typedef DXVA_COPPStatusSignalingCmdData TDXVACOPPStatusSignalingCmdData;

typedef _tag_AMVAUncompBufferInfo *PAMVAUncompBufferInfo;

typedef _tag_AMVAUncompBufferInfo TAMVAUncompBufferInfo;

typedef _tag_AMVAUncompDataInfo *PAMVAUncompDataInfo;

typedef _tag_AMVAUncompDataInfo TAMVAUncompDataInfo;

typedef _tag_AMVAInternalMemInfo *PAMVAInternalMemInfo;

typedef _tag_AMVAInternalMemInfo TAMVAInternalMemInfo;

typedef _tag_AMVACompBufferInfo *PAMVACompBufferInfo;

typedef _tag_AMVACompBufferInfo TAMVACompBufferInfo;

typedef _tag_AMVABeginFrameInfo *PAMVABeginFrameInfo;

typedef _tag_AMVABeginFrameInfo TAMVABeginFrameInfo;

typedef _tag_AMVAEndFrameInfo *PAMVAEndFrameInfo;

typedef _tag_AMVAEndFrameInfo TAMVAEndFrameInfo;

typedef _tag_AMVABUFFERINFO *PAMVABufferInfo;

typedef _tag_AMVABUFFERINFO TAMVABufferInfo;

typedef _BDA_TEMPLATE_CONNECTION *PBDATemplateConnection;

typedef _BDA_TEMPLATE_CONNECTION TBDATemplateConnection;

typedef _BDA_TEMPLATE_PIN_JOINT *PBDATemplatePinJoint;

typedef _BDA_TEMPLATE_PIN_JOINT TBDATemplatePinJoint;

typedef BDA_EVENT_ID *PBDAEventID;

typedef BDA_EVENT_ID TBDAEventID;

typedef tagKS_BDA_FRAME_INFO *PKSBDAFrameInfo;

typedef tagKS_BDA_FRAME_INFO TKSBDAFrameInfo;

typedef _BDA_ETHERNET_ADDRESS *PBDAEthernetAddress;

typedef _BDA_ETHERNET_ADDRESS TBDAEthernetAddress;

typedef _BDA_ETHERNET_ADDRESS_LIST *PBDAEthernetAddressList;

typedef _BDA_ETHERNET_ADDRESS_LIST TBDAEthernetAddressList;

typedef BDA_MULTICAST_MODE *PBDAMulticastMode;

typedef BDA_MULTICAST_MODE TBDAMulticastMode;

typedef _BDA_IPv4_ADDRESS *PBDAIPv4Address;

typedef _BDA_IPv4_ADDRESS TBDAIPv4Address;

typedef _BDA_IPv4_ADDRESS_LIST *PBDAIPv4AddressList;

typedef _BDA_IPv4_ADDRESS_LIST TBDAIPv4AddressList;

typedef _BDA_IPv6_ADDRESS *PBDAIPv6Address;

typedef _BDA_IPv6_ADDRESS TBDAIPv6Address;

typedef _BDA_IPv6_ADDRESS_LIST *PBDAIPv6AddressList;

typedef _BDA_IPv6_ADDRESS_LIST TBDAIPv6AddressList;

typedef BDA_SIGNAL_STATE *PBDASignalState;

typedef BDA_SIGNAL_STATE TBDASignalState;

typedef BDA_CHANGE_STATE *PBDAChangeState;

typedef BDA_CHANGE_STATE *PBDA_CHANGE_STATE;

typedef BDA_CHANGE_STATE TBDAChangeState;

typedef _BDANODE_DESCRIPTOR *PBDANodeDescriptor;

typedef _BDANODE_DESCRIPTOR TBDANodeDescriptor;

typedef _BDA_TABLE_SECTION *PBDATableSection;

typedef _BDA_TABLE_SECTION TBDATableSection;

typedef MEDIA_SAMPLE_CONTENT TMediaSampleContent;

typedef PID_MAP TPIDMap;

typedef PID_MAP *PPIDMap;

typedef _BDA_PID_MAP *PBDAPIDMap;

typedef _BDA_PID_MAP *PBDA_PID_MAP;

typedef _BDA_PID_MAP TBDAPIDMap;

typedef _BDA_PID_UNMAP *PBDAPIDUnmap;

typedef _BDA_PID_UNMAP TBDAPIDUnmap;

typedef _BDA_CA_MODULE_UI *PBDACAModuleUI;

typedef _BDA_CA_MODULE_UI TBDACAModuleUI;

typedef _BDA_PROGRAM_PID_LIST *PBDAProgramPIDList;

typedef _BDA_PROGRAM_PID_LIST TBDAProgramPIDList;

typedef DVBSystemType TDVBSystemType;

typedef ComponentStatus TComponentStatus;

typedef _MPEG2_TRANSPORT_STRIDE *PMPEG2TransportStride;

typedef _MPEG2_TRANSPORT_STRIDE TMPEG2TransportStride;

typedef DXBNDID TDXBNDID;

typedef DXBNDTYPE TDXBNDType;

typedef DXDBND TDXDBND;

typedef DXDBND64 TDXDBND64;

typedef DXCBND TDXCBND;

typedef DXCBND64 TDXCBND64;

typedef DXBNDS TDXBNDS;

typedef DXVEC TDXVEC;

typedef DXTMTASKINFO TDXTMTaskInfo;

typedef DXBASESAMPLE TDXBaseSample;

typedef DXSAMPLE TDXSample;

typedef DXPMSAMPLE TDXPMSample;

typedef DXRUNTYPE TDXRunType;

typedef DXRUNINFO *PDXRunInfo;

typedef DXRUNINFO TDXRunInfo;

typedef DXRAWSURFACEINFO TDXRawSurfaceInfo;

typedef DXNATIVETYPEINFO TDXNativeTypeInfo;

typedef DXPACKEDRECTDESC TDXPackedRectDesc;

typedef DXOVERSAMPLEDESC TDXOverSampleDesc;

typedef DEXTERF TDexterF;

typedef DEXTER_PARAM *PDexterParam;

typedef DEXTER_PARAM TDexterParam;

typedef DEXTER_VALUE *PDexterValue;

typedef DEXTER_VALUE TDexterValue;

typedef DEXTER_AUDIO_VOLUMEENVELOPE TDexterAudioVolumeEnvelope;

typedef _SCompFmt0 TSCompFmt0;

typedef MPEGVideoDecoderCaps TMPEGVideoDecoderCaps;

typedef SeqHdrInfo TSeqHdrInfo;

typedef _tagSND_DEVICE_ERROR TSndDevErr;

typedef MP_DATA MPData;

typedef _MP_Type TMPTYPE;

typedef MP_CURVE_TYPE MPCurveType;

typedef MP_CAPS MPCaps;

typedef _MP_PARAMINFO TMPParamInfo;

typedef MP_TIMEDATA MPTimeData;

typedef MP_FLAGS MPFlags;

typedef _MP_ENVELOPE_SEGMENT TMPEnvelopeSegment;

typedef _AMMediaType *PDMOMediaType;

typedef _AMMediaType TDMOMediaType;

typedef _DMO_OUTPUT_DATA_BUFFER *PDMOOutputDataBuffer;

typedef _DMO_OUTPUT_DATA_BUFFER TDMOOutputDataBuffer;

typedef System::StaticArray<_DMO_OUTPUT_DATA_BUFFER, 1> TDMOOutputDataBufferArray;

typedef TDMOOutputDataBufferArray *PDMOOutputDataBufferArray;

typedef _DMO_PARTIAL_MEDIATYPE *PDMOPartialMediaType;

typedef _DMO_PARTIAL_MEDIATYPE TDMOPartialMediaType;

typedef System::StaticArray<System::WideChar, 80> TDMOName;

typedef KSRESET TKSReset;

typedef KSSTATE TKSState;

typedef KSPRIORITY TKSPriority;

typedef KSIDENTIFIER TKSIdentifier;

typedef KSP_NODE *PKSPNode;

typedef KSP_NODE TKSPNode;

typedef KSM_NODE *PKSMNode;

typedef KSM_NODE TKSMNode;

typedef KSE_NODE *PKSENode;

typedef KSE_NODE TKSENode;

typedef KSMULTIPLE_ITEM *PKSMultipleItem;

typedef KSMULTIPLE_ITEM TKSMultipleItem;

typedef KSPROPERTY_DESCRIPTION *PKSPropertyDescription;

typedef KSPROPERTY_DESCRIPTION TKSPropertyDescription;

typedef KSPROPERTY_MEMBERSHEADER *PKSPropertyMembersHeader;

typedef KSPROPERTY_MEMBERSHEADER TKSPropertyMembersHeader;

typedef KSPROPERTY_BOUNDS_LONG *PKSPropertyBoundsLong;

typedef KSPROPERTY_BOUNDS_LONG TKSPropertyBoundsLong;

typedef KSPROPERTY_BOUNDS_LONGLONG *PKSPropertyBoundsLongLong;

typedef KSPROPERTY_BOUNDS_LONGLONG TKSPropertyBoundsLongLong;

typedef KSPROPERTY_STEPPING_LONG *PKSPropertySteppingLong;

typedef KSPROPERTY_STEPPING_LONG TKSPropertySteppingLong;

typedef KSPROPERTY_STEPPING_LONGLONG *PKSPropertySteppingLongLong;

typedef KSPROPERTY_STEPPING_LONGLONG TKSPropertySteppingLongLong;

typedef KSEVENTDATA TKSEventData;

typedef KSQUERYBUFFER TKSQueryBuffer;

typedef KSRELATIVEEVENT TKSRelativeEvent;

typedef KSEVENT_TIME_MARK *PKSEventTimeMark;

typedef KSEVENT_TIME_MARK TKSEventTimeMark;

typedef KSEVENT_TIME_INTERVAL *PKSEventTimeInterval;

typedef KSEVENT_TIME_INTERVAL TKSEventTimeInterval;

typedef KSINTERVAL TKSInterval;

typedef KSPROPERTY_GENERAL TKSPropertyGeneral;

typedef KSCOMPONENTID TKSComponentID;

typedef KSMETHOD_STREAMIO TKSMethodStreamIO;

typedef KSPROPERTY_MEDIASEEKING TKSPropertyMediaSeeking;

typedef KSPROPERTY_POSITIONS *PKSPropertyPositions;

typedef KSPROPERTY_POSITIONS TKSPropertyPositions;

typedef KSPROPERTY_MEDIAAVAILABLE *PKSPropertyMediaAvailable;

typedef KSPROPERTY_MEDIAAVAILABLE TKSPropertyMediaAvailable;

typedef KSP_TIMEFORMAT *PKSPTimeFormat;

typedef KSP_TIMEFORMAT TKSPTimeFormat;

typedef KSPROPERTY_TOPOLOGY TKSPropertyTopology;

typedef KSTOPOLOGY_CONNECTION *PKSTopologyConnection;

typedef KSTOPOLOGY_CONNECTION TKSTopologyConnection;

typedef KSTOPOLOGY TKSTopology;

typedef KSNODE_CREATE *PKSNodeCreate;

typedef KSNODE_CREATE TKSNodeCreate;

typedef PKSPIN_INTERFACE PKSPinInterface;

typedef KSIDENTIFIER TKSPinInterface;

typedef KSINTERFACE_STANDARD TKSInterfaceStandard;

typedef KSINTERFACE_FILEIO TKSInterfaceFileIO;

typedef KSPROPERTY_PIN TKSPropertyPin;

typedef KSP_PIN *PKSPPin;

typedef KSP_PIN TKSPPin;

typedef KSPIN_CINSTANCES *PKSPinCInstance;

typedef KSPIN_CINSTANCES TKSPinCInstance;

typedef KSPIN_DATAFLOW *PKSPinDataFlow;

typedef KSPIN_DATAFLOW TKSPinDataFlow;

typedef KSDATAFORMAT TKSDataFormat;

typedef KSDATAFORMAT TKSDataRange;

typedef KSATTRIBUTE TKSAttribute;

typedef KSPIN_COMMUNICATION *PKSPinCommunication;

typedef KSPIN_COMMUNICATION TKSPinCommunication;

typedef PKSPIN_MEDIUM PKSPinMedium;

typedef KSIDENTIFIER TKSPinMedium;

typedef KSPIN_CONNECT *PKSPinConnect;

typedef KSPIN_CONNECT TKSPinConnect;

typedef KSPIN_PHYSICALCONNECTION *PKSPinPhysicalConnection;

typedef KSPIN_PHYSICALCONNECTION TKSPinPhysicalConnection;

typedef KSPROPERTY_QUALITY TKSPropertyQuality;

typedef KSPROPERTY_CONNECTION TKSPropertyConnection;

typedef KSALLOCATOR_FRAMING *PKSAllocatorFraming;

typedef KSALLOCATOR_FRAMING TKSAllocatorFraming;

typedef KS_FRAMING_RANGE *PKSFramingRange;

typedef KS_FRAMING_RANGE TKSFramingRange;

typedef KS_FRAMING_RANGE_WEIGHTED *PKSFramingRangeWeighted;

typedef KS_FRAMING_RANGE_WEIGHTED TKSFramingRangeWeighted;

typedef KS_COMPRESSION *PKSCompression;

typedef KS_COMPRESSION TKSCompression;

typedef KS_FRAMING_ITEM *PKSFramingItem;

typedef KS_FRAMING_ITEM TKSFramingItem;

typedef KSALLOCATOR_FRAMING_EX *PKSAllocatorFramingEx;

typedef KSALLOCATOR_FRAMING_EX TKSAllocatorFramingEx;

typedef KSEVENT_STREAMALLOCATOR TKSEventStreamAllocator;

typedef KSMETHOD_STREAMALLOCATOR TKSMethodStreamAllocation;

typedef KSSTREAMALLOCATOR_STATUS *PKSStreamAllocatorStatus;

typedef KSSTREAMALLOCATOR_STATUS TKSStreamAllocatorStatus;

typedef KSSTREAMALLOCATOR_STATUS_EX *PKSStreamAllocatorStatusEx;

typedef KSSTREAMALLOCATOR_STATUS_EX TKSStreamAllocatorStatusEx;

typedef KSTIME TKSTime;

typedef KSSTREAM_HEADER *PKSStreamHeader;

typedef KSSTREAM_HEADER TKSStreamHeader;

typedef KSPROPERTY_STREAMINTERFACE TKSPropertyStreamInterface;

typedef KSPROPERTY_STREAM TKSPropertyStream;

typedef KSQUALITY_MANAGER *PKSQualityManager;

typedef KSQUALITY_MANAGER TKSQualityManager;

typedef KSFRAMETIME TKSFrameTime;

typedef KSRATE TKSRate;

typedef KSRATE_CAPABILITY *PKSRateCapability;

typedef KSRATE_CAPABILITY TKSRateCapability;

typedef KSCLOCK_CREATE *PKSClockCreate;

typedef KSCLOCK_CREATE TKSClockCreate;

typedef KSCORRELATED_TIME *PKSCorrelatedTime;

typedef KSCORRELATED_TIME TKSCorrelatedTime;

typedef KSRESOLUTION TKSResolution;

typedef KSPROPERTY_CLOCK TKSPropertyClock;

typedef KSEVENT_CLOCK_POSITION TKSEventClockPosition;

typedef KSEVENT_CONNECTION TKSEventConnection;

typedef KSQUALITY TKSQuality;

typedef KSERROR TKSError;

typedef KSIDENTIFIER TKSDegrade;

typedef KSDEGRADE_STANDARD TKSDegradeStandard;

typedef KSPROPERTY_SERIALHDR TKSPropertySerialHDR;

typedef KSPROPERTY_SERIAL *PKSPropertySerial;

typedef KSPROPERTY_SERIAL TKSPropertySerial;

typedef KSALLOCATORMODE TKSAllocatorMode;

typedef FRAMING_PROP *PFramingProp;

typedef FRAMING_PROP TFramingProp;

typedef FRAMING_CACHE_OPS TFramingCacheOps;

typedef OPTIMAL_WEIGHT_TOTALS TOptimalWeightTotals;

typedef PIPE_STATE TPipeState;

typedef PIPE_DIMENSIONS *PPipeDimensions;

typedef PIPE_DIMENSIONS TPipeDimensions;

typedef PIPE_ALLOCATOR_PLACE *PPipeAllocatorPlace;

typedef PIPE_ALLOCATOR_PLACE TPipeAllocatorPlace;

typedef KS_LogicalMemoryType *PKSLogicalMemoryType;

typedef KS_LogicalMemoryType TKSLogicalMemoryType;

typedef PIPE_TERMINATION TPipeTermination;

typedef ALLOCATOR_PROPERTIES_EX *PAllocatorPropertiesEx;

typedef ALLOCATOR_PROPERTIES_EX TAllocatorPropertiesEx;

typedef KSPEEKOPERATION TKSPeekOperation;

typedef KSIOOPERATION TKSIOOperation;

typedef KSSTREAM_SEGMENT *PKSStreamSegment;

typedef KSSTREAM_SEGMENT TKSStreamSegment;

typedef KSMULTIPLE_DATA_PROP *PKSMultipleDataProp;

typedef KSMULTIPLE_DATA_PROP TKSMultipleDataProp;

typedef KSINTERFACE_MEDIA TKSInterfaceMedia;

typedef KSDATAFORMAT_WAVEFORMATEX *PKSDataFormatWaveFormatEx;

typedef KSDATAFORMAT_WAVEFORMATEX TKSDataFormatWaveFormatEx;

typedef WAVEFORMATEXTENSIBLE *PWaveFormatExtensible;

typedef WAVEFORMATEXTENSIBLE TWaveFormatExtensible;

typedef KSDSOUND_BUFFERDESC *PKSDSoundBufferDesc;

typedef KSDSOUND_BUFFERDESC TKSDSoundBufferDesc;

typedef KSDATAFORMAT_DSOUND *PKSDataFormatDSound;

typedef KSDATAFORMAT_DSOUND TKSDataFormatDSound;

typedef KSAUDIO_POSITION *PKSAudioPosition;

typedef KSAUDIO_POSITION TKSAudioPosition;

typedef _DS3DVECTOR TDS3DVector;

typedef KSPROPERTY_DIRECTSOUND3DLISTENER TKSPropertyDirectSound3DListener;

typedef KSDS3D_LISTENER_ALL *PKSDS3DListenerAll;

typedef KSDS3D_LISTENER_ALL TKSDS3DListenerAll;

typedef KSDS3D_LISTENER_ORIENTATION TKSDS3DListenerOrientation;

typedef KSPROPERTY_DIRECTSOUND3DBUFFER TKSPropertyDirectSound3DBuffer;

typedef KSDS3D_BUFFER_ALL TKSDS3DBufferAll;

typedef KSDS3D_BUFFER_CONE_ANGLES TKSDS3DBufferConeAngles;

typedef KSDATARANGE_AUDIO TKSDataRangeAudio;

typedef KSPROPERTY_TOPOLOGYNODE TKSPropertyTopologyNode;

typedef KSPROPERTY_DRMAUDIOSTREAM TKSPRopertyDRMAudioStream;

typedef KSPROPERTY_AUDIO TKSPropertyAudio;

typedef KSAUDIO_COPY_PROTECTION *PKSAudioCopyProtection;

typedef KSAUDIO_COPY_PROTECTION TKSAudioCopyProtection;

typedef KSAUDIO_CHANNEL_CONFIG *PKSAudioChannelConfig;

typedef KSAUDIO_CHANNEL_CONFIG TKSAudioChannelConfig;

typedef KSAUDIO_DYNAMIC_RANGE *PKSAudioDynamicRange;

typedef KSAUDIO_DYNAMIC_RANGE TKSAudioDynamicRange;

typedef KSAUDIO_MIXLEVEL *PKSAudioMixLevel;

typedef KSAUDIO_MIXLEVEL TKSAudioMixLevel;

typedef KSAUDIO_MIX_CAPS *PKSAudioMixCaps;

typedef KSAUDIO_MIX_CAPS TKSAudioMixCaps;

typedef KSAUDIO_MIXCAP_TABLE *PKSaudioMixcapTable;

typedef KSAUDIO_MIXCAP_TABLE TKSaudioMixcapTable;

typedef SE_TECHNIQUE TSETechnique;

typedef KSAUDIO_STEREO_ENHANCE *PKSAudioStereoEnhance;

typedef KSAUDIO_STEREO_ENHANCE TKSAudioStereoEnhance;

typedef KSMETHOD_WAVETABLE TKSMethodWavetable;

typedef KSWAVETABLE_WAVE_DESC *PKSWaveTableWaveDesc;

typedef KSWAVETABLE_WAVE_DESC TKSWaveTableWaveDesc;

typedef KSPROPERTY_WAVE TKSPropertyWave;

typedef KSWAVE_COMPATCAPS *PKSWaveCompatCaps;

typedef KSWAVE_COMPATCAPS TKSWaveCompatCaps;

typedef KSWAVE_INPUT_CAPABILITIES *PKSWaveInputCapabilities;

typedef KSWAVE_INPUT_CAPABILITIES TKSWaveInputCapabilities;

typedef KSWAVE_OUTPUT_CAPABILITIES *PKSWaveOutputCapabilities;

typedef KSWAVE_OUTPUT_CAPABILITIES TKSWaveOutputCapabilities;

typedef KSWAVE_VOLUME *PKSWaveVolume;

typedef KSWAVE_VOLUME TKSWaveVolume;

typedef KSWAVE_BUFFER *PKSWaveBuffer;

typedef KSWAVE_BUFFER TKSWaveBuffer;

typedef KSPROPERTY_WAVETABLE TKSPropertyWaveTable;

typedef KSDATARANGE_MUSIC *PKSDataRangeMusic;

typedef KSDATARANGE_MUSIC TKSDataRangeMusic;

typedef KSEVENT_CYCLIC_TIME TKSEventCyclicTime;

typedef KSPROPERTY_CYCLIC TKSPropertyCyclic;

typedef KSEVENT_AUDIO_CONTROL_CHANGE TKSEventAudioControlChange;

typedef KSEVENT_LOOPEDSTREAMING TKSEventLoopedStreaming;

typedef LOOPEDSTREAMING_POSITION_EVENT_DATA *PLoopedStreamingPositionEventData;

typedef LOOPEDSTREAMING_POSITION_EVENT_DATA TLoopedStreamingPositionEventData;

typedef KSEVENT_SYSAUDIO TKSEventSysAudio;

typedef KSPROPERTY_SYSAUDIO TKSPropertySysAudio;

typedef SYSAUDIO_CREATE_VIRTUAL_SOURCE *PSysAudioCreateVirtualSource;

typedef SYSAUDIO_CREATE_VIRTUAL_SOURCE TSysAudioCreateVirtualSource;

typedef SYSAUDIO_SELECT_GRAPH *PSysAudioSelectGraph;

typedef SYSAUDIO_SELECT_GRAPH TSysAudioSelectGraph;

typedef SYSAUDIO_INSTANCE_INFO *PSysAudioInstanceInfo;

typedef SYSAUDIO_INSTANCE_INFO TSysAudioInstanceInfo;

typedef SYSAUDIO_PREFERRED_DEVICE TSysAudioPreferredDevice;

typedef KSPROPERTY_SYSAUDIO_DEFAULT_TYPE TKSPropertySysAudioDefaultType;

typedef KSPROPERTY_SYSAUDIO_PIN TKSPropertySysAudioPin;

typedef SYSAUDIO_ATTACH_VIRTUAL_SOURCE *PSysAudioAttachVirtualSource;

typedef SYSAUDIO_ATTACH_VIRTUAL_SOURCE TSysAudioAttachVirtualSource;

typedef KSNODEPROPERTY TKSNodeProperty;

typedef KSNODEPROPERTY_AUDIO_CHANNEL *PKSNodePropertyAudioChannel;

typedef KSNODEPROPERTY_AUDIO_CHANNEL TKSNodePropertyAudioChannel;

typedef KSNODEPROPERTY_AUDIO_DEV_SPECIFIC *PKSNodePropertyAudioDevSpecific;

typedef KSNODEPROPERTY_AUDIO_DEV_SPECIFIC TKSNodePropertyAudioDevSpecific;

typedef KSNODEPROPERTY_AUDIO_3D_LISTENER *PKSNodePropertyAudio3DListenerp;

typedef KSNODEPROPERTY_AUDIO_3D_LISTENER TKSNodePropertyAudio3DListener;

typedef KSNODEPROPERTY_AUDIO_PROPERTY *PKSNodePropertyAudioProperty;

typedef KSNODEPROPERTY_AUDIO_PROPERTY TKSNodePropertyAudioProperty;

typedef KSPROPERTY_LINEAR TKSPropertyLinear;

typedef KSMUSICFORMAT TKSMusicFormat;

typedef KSPROPERTY_MPEG2VID TKSPropertyMPEG2Vid;

typedef _KSMPEGVID_RECT *PKSMPEGVidRect;

typedef _KSMPEGVID_RECT TKSMPEGVidRect;

typedef KSPROPERTY_AC3 TKSPropertyAC3;

typedef KSAC3_ERROR_CONCEALMENT *PKSAC3ErrorConcealment;

typedef KSAC3_ERROR_CONCEALMENT TKSAC3ErrorConcealment;

typedef KSAC3_ALTERNATE_AUDIO *PKSAC3AlternateAudio;

typedef KSAC3_ALTERNATE_AUDIO TKSAC3AlternateAudio;

typedef KSAC3_DOWNMIX *PKSAC3DownMix;

typedef KSAC3_DOWNMIX TKSAC3DownMix;

typedef KSAC3_BIT_STREAM_MODE *PKSAC3BitStreamMode;

typedef KSAC3_BIT_STREAM_MODE TKSAC3BitStreamMode;

typedef KSAC3_DIALOGUE_LEVEL *PKSAC3DialogueLevel;

typedef KSAC3_DIALOGUE_LEVEL TKSAC3DialogueLevel;

typedef KSAC3_ROOM_TYPE *PKSAC3RoomType;

typedef KSAC3_ROOM_TYPE TKSAC3RoomType;

typedef KSPROPERTY_AUDDECOUT TKSPropertyAuddecout;

typedef KSPROPERTY_DVDSUBPIC TKSPropertyDVDSubPic;

typedef _KS_DVD_YCrCb *PKSDVDYCrCb;

typedef _KS_DVD_YCrCb TKSDVDYCrCb;

typedef _KS_DVD_YUV *PKSDVDYUV;

typedef _KS_DVD_YUV TKSDVDYUV;

typedef _KSPROPERTY_SPPAL *PKSPropertySPPAL;

typedef _KSPROPERTY_SPPAL TKSPropertySPPAL;

typedef _KS_COLCON *PKSColCon;

typedef _KS_COLCON TKSColCon;

typedef _KSPROPERTY_SPHLI *PKSPropertySPHLI;

typedef _KSPROPERTY_SPHLI TKSPropertySPHLI;

typedef _KS_DVDCOPY_CHLGKEY *PKSDVDCopyCHLGKey;

typedef _KS_DVDCOPY_CHLGKEY TKSDVDCopyCHLGKey;

typedef _KS_DVDCOPY_BUSKEY *PKSDVDCopyBusKey;

typedef _KS_DVDCOPY_BUSKEY TKSDVDCopyBusKey;

typedef _KS_DVDCOPY_DISCKEY *PKSDVDCopyDiscKey;

typedef _KS_DVDCOPY_DISCKEY TKSDVDCopyDiscKey;

typedef _KS_DVDCOPY_REGION *PKSDVDCopyRegion;

typedef _KS_DVDCOPY_REGION TKSDVDCopyRegion;

typedef _KS_DVDCOPY_TITLEKEY *PKSDVDCopyTitleKey;

typedef _KS_DVDCOPY_TITLEKEY TKSDVDCopyTitleKey;

typedef _KS_COPY_MACROVISION *PKSCopyMacrovision;

typedef _KS_COPY_MACROVISION TKSCopyMacrovision;

typedef _KS_DVDCOPY_SET_COPY_STATE *PKSDVDCopySetCopyState;

typedef _KS_DVDCOPY_SET_COPY_STATE TKSDVDCopySetCopyState;

typedef KS_DVDCOPYSTATE TKSDVDCopyState;

typedef KS_COPY_MACROVISION_LEVEL *PKSCopyMacrovisionLevel;

typedef KS_COPY_MACROVISION_LEVEL TKSCopyMacrovisionLevel;

typedef tagKS_RGBQUAD *PKSRGBQuad;

typedef tagKS_RGBQUAD TKSRGBQuad;

typedef tagKS_BITMAPINFOHEADER *PKSBitmapInfoHeader;

typedef tagKS_BITMAPINFOHEADER TKSBitmapInfoHeader;

typedef tag_KS_TRUECOLORINFO *PKSTrueColorInfo;

typedef tag_KS_TRUECOLORINFO TKSTrueColorInfo;

typedef tagKS_VIDEOINFOHEADER *PKSVideoInfoHeader;

typedef tagKS_VIDEOINFOHEADER TKSVideoInfoHeader;

typedef tagKS_VIDEOINFO *PKSVideoInfo;

typedef tagKS_VIDEOINFO TKSVideoInfo;

typedef tagKS_VBIINFOHEADER *PKSVBIInfoHeader;

typedef tagKS_VBIINFOHEADER TKSVBIInfoHeader;

typedef tagKS_AnalogVideoInfo *PKSAnalogVideoInfo;

typedef tagKS_AnalogVideoInfo TKSAnalogVideoInfo;

typedef tagKS_TVTUNER_CHANGE_INFO *PKSTVTunerChangeInfo;

typedef tagKS_TVTUNER_CHANGE_INFO TKSTVTunerChangeInfo;

typedef KS_MPEG2Level TKSMPEG2Level;

typedef KS_MPEG2Profile TKSMPEG2Profile;

typedef tagKS_VIDEOINFOHEADER2 *PKSVideoInfoHeader2;

typedef tagKS_VIDEOINFOHEADER2 TKSVideoInfoHeader2;

typedef tagKS_MPEG1VIDEOINFO *PKSMPEG1VideoInfo;

typedef tagKS_MPEG1VIDEOINFO TKSMPEG1VideoInfo;

typedef tagKS_MPEGVIDEOINFO2 *PKSMPEGVideoInfo2;

typedef tagKS_MPEGVIDEOINFO2 TKSMPEGVideoInfo2;

typedef tagKS_MPEAUDIOINFO *PKSMPEGAudioInfo;

typedef tagKS_MPEAUDIOINFO TKSMPEGAudioInfo;

typedef tagKS_DATAFORMAT_VIDEOINFOHEADER *PKSDataFormatVideoInfoHeader;

typedef tagKS_DATAFORMAT_VIDEOINFOHEADER TKSDataFormatVideoInfoHeader;

typedef tagKS_DATAFORMAT_VIDEOINFOHEADER2 *PKSDataFormatVideoInfoHeader2;

typedef tagKS_DATAFORMAT_VIDEOINFOHEADER2 TKSDataFormatVideoInfoHeader2;

typedef tagKS_DATAFORMAT_VIDEOINFO_PALETTE *PKSDataFormatVideoinfoPalette;

typedef tagKS_DATAFORMAT_VIDEOINFO_PALETTE TKSDataFormatVideoinfoPalette;

typedef tagKS_DATAFORMAT_VBIINFOHEADER *PKSDataFormatVBIInfoHeader;

typedef tagKS_DATAFORMAT_VBIINFOHEADER TKSDataFormatVBIInfoHeader;

typedef _KS_VIDEO_STREAM_CONFIG_CAPS *PKSVideoStreamConfigCaps;

typedef _KS_VIDEO_STREAM_CONFIG_CAPS TKSVideoStreamConfigCaps;

typedef tagKS_DATARANGE_VIDEO *PKSDataRangeVideo;

typedef tagKS_DATARANGE_VIDEO TKSDataRangeVideo;

typedef tagKS_DATARANGE_VIDEO2 *PKSDataRangeVideo2;

typedef tagKS_DATARANGE_VIDEO2 TKSDataRangeVideo2;

typedef tagKS_DATARANGE_MPEG1_VIDEO *PKSDataRangeMPEG1Video;

typedef tagKS_DATARANGE_MPEG1_VIDEO TKSDataRangeMPEG1Video;

typedef tagKS_DATARANGE_MPEG2_VIDEO *PKSDataRangeMPEG2Video;

typedef tagKS_DATARANGE_MPEG2_VIDEO TKSDataRangeMPEG2Video;

typedef tagKS_DATARANGE_VIDEO_PALETTE *PKSDataRangeVideoPalette;

typedef tagKS_DATARANGE_VIDEO_PALETTE TKSDataRangeVideoPalette;

typedef tagKS_DATARANGE_VIDEO_VBI *PKSDataRangeVideoVBI;

typedef tagKS_DATARANGE_VIDEO_VBI TKSDataRangeVideoVBI;

typedef tagKS_DATARANGE_ANALOGVIDEO *PKSDataRangeAnalogVideo;

typedef tagKS_DATARANGE_ANALOGVIDEO TKSDataRangeAnalogVideo;

typedef KSPROPERTY_VBICAP TKSPropertyVBICap;

typedef _VBICAP_PROPERTIES_PROTECTION_S *PVBICapPropertiesProtectionS;

typedef _VBICAP_PROPERTIES_PROTECTION_S TVBICapPropertiesProtectionS;

typedef _NABTSFEC_BUFFER *PNABTSFecBuffer;

typedef _NABTSFEC_BUFFER TNABTSFecBuffer;

typedef KSPROPERTY_VBICODECFILTERING TKSPropertyVBICodecFiltering;

typedef _VBICODECFILTERING_SCANLINES *PVBICodecFilteringScanlines;

typedef _VBICODECFILTERING_SCANLINES TVBICodecFilteringScanlines;

typedef _VBICODECFILTERING_NABTS_SUBSTREAMS *PVBICodecFilteringNABTSSubStreams;

typedef _VBICODECFILTERING_NABTS_SUBSTREAMS TVBICodecFilteringNABTSSubStreams;

typedef _VBICODECFILTERING_CC_SUBSTREAMS *PVBICodecFilteringCCSubStreams;

typedef _VBICODECFILTERING_CC_SUBSTREAMS TVBICodecFilteringCCSubStreams;

typedef _CC_BYTE_PAIR *PCCBytePair;

typedef _CC_BYTE_PAIR TCCBytePair;

typedef _CC_HW_FIELD *PCCHWField;

typedef _CC_HW_FIELD TCCHWField;

typedef _NABTS_BUFFER_LINE *PNABTSBufferLine;

typedef _NABTS_BUFFER_LINE TNABTSBufferLine;

typedef _NABTS_BUFFER *PNABTSBuffer;

typedef _NABTS_BUFFER TNABTSBuffer;

typedef _WST_BUFFER_LINE *PWSTBufferLine;

typedef _WST_BUFFER_LINE TWSTBufferLine;

typedef _WST_BUFFER *PWSTBuffer;

typedef _WST_BUFFER TWSTBuffer;

typedef _VBICODECFILTERING_STATISTICS_COMMON *PVBICodecFilteringStatisticsCommon;

typedef _VBICODECFILTERING_STATISTICS_COMMON TVBICodecFilteringStatisticsCommon;

typedef _VBICODECFILTERING_STATISTICS_COMMON_PIN *PVBICodecFilteringStatisticsCommonPin;

typedef _VBICODECFILTERING_STATISTICS_COMMON_PIN TVBICodecFilteringStatisticsCommonPin;

typedef _VBICODECFILTERING_STATISTICS_NABTS *PVBICodecFilteringStatisticsNABTS;

typedef _VBICODECFILTERING_STATISTICS_NABTS TVBICodecFilteringStatisticsNABTS;

typedef _VBICODECFILTERING_STATISTICS_NABTS_PIN *PVBICodecFilteringStatisticsNABTSPin;

typedef _VBICODECFILTERING_STATISTICS_NABTS_PIN TVBICodecFilteringStatisticsNABTSPin;

typedef _VBICODECFILTERING_STATISTICS_CC *PVBICodecFilteringStatisticsCC;

typedef _VBICODECFILTERING_STATISTICS_CC TVBICodecFilteringStatisticsCC;

typedef _VBICODECFILTERING_STATISTICS_CC_PIN *PVBICodecFilteringStatisticsCCPin;

typedef _VBICODECFILTERING_STATISTICS_CC_PIN TVBICodecFilteringStatisticsCCPin;

typedef _VBICODECFILTERING_STATISTICS_TELETEXT *PVBICodecFilteringStatisticsTeletext;

typedef _VBICODECFILTERING_STATISTICS_TELETEXT TVBICodecFilteringStatisticsTeletext;

typedef _VBICODECFILTERING_STATISTICS_TELETEXT_PIN *PVBICodecFilteringStatisticsTeletextPin;

typedef _VBICODECFILTERING_STATISTICS_TELETEXT_PIN TVBICodecFilteringStatisticsTeletextPin;

typedef KSPROPERTY_VBICODECFILTERING_SCANLINES_S *PKSPropertyVBICodecFilteringScanlinesS;

typedef KSPROPERTY_VBICODECFILTERING_SCANLINES_S TKSPropertyVBICodecFilteringScanlinesS;

typedef KSPROPERTY_VBICODECFILTERING_NABTS_SUBSTREAMS_S *PKSPropertyVBICodecFilteringNABTSSubstreamsS;

typedef KSPROPERTY_VBICODECFILTERING_NABTS_SUBSTREAMS_S TKSPropertyVBICodecFilteringNABTSSubstreamsS;

typedef KSPROPERTY_VBICODECFILTERING_CC_SUBSTREAMS_S *PKSPropertyVBICodecFilteringCCSubstreamsS;

typedef KSPROPERTY_VBICODECFILTERING_CC_SUBSTREAMS_S TKSPropertyVBICodecFilteringCCSubstreamsS;

typedef KSPROPERTY_VBICODECFILTERING_STATISTICS_COMMON_S *PKSPropertyVBICodecFilteringStatisticsCommonS;

typedef KSPROPERTY_VBICODECFILTERING_STATISTICS_COMMON_S TKSPropertyVBICodecFilteringStatisticsCommonS;

typedef KSPROPERTY_VBICODECFILTERING_STATISTICS_COMMON_PIN_S *PKSPropertyVBICodecFilteringStatisticsCommonPinS;

typedef KSPROPERTY_VBICODECFILTERING_STATISTICS_COMMON_PIN_S TKSPropertyVBICodecFilteringStatisticsCommonPinS;

typedef KSPROPERTY_VBICODECFILTERING_STATISTICS_NABTS_S *PKSPropertyVBICodecFilteringStatisticsNABTSS;

typedef KSPROPERTY_VBICODECFILTERING_STATISTICS_NABTS_S TKSPropertyVBICodecFilteringStatisticsNABTSS;

typedef KSPROPERTY_VBICODECFILTERING_STATISTICS_NABTS_PIN_S *PKSPropertyVBICodecFilteringStatisticsNABTSPinS;

typedef KSPROPERTY_VBICODECFILTERING_STATISTICS_NABTS_PIN_S TKSPropertyVBICodecFilteringStatisticsNABTSPinS;

typedef KSPROPERTY_VBICODECFILTERING_STATISTICS_CC_S *PKSPropertyVBICodecFilteringStatisticsCCS;

typedef KSPROPERTY_VBICODECFILTERING_STATISTICS_CC_S TKSPropertyVBICodecFilteringStatisticsCCS;

typedef KSPROPERTY_VBICODECFILTERING_STATISTICS_CC_PIN_S *PKSPropertyVBICodecFilteringStatisticsCCPinS;

typedef KSPROPERTY_VBICODECFILTERING_STATISTICS_CC_PIN_S TKSPropertyVBICodecFilteringStatisticsCCPinS;

typedef tagKS_FRAME_INFO *PKSFrameInfo;

typedef tagKS_FRAME_INFO TKSFrameInfo;

typedef tagKS_VBI_FRAME_INFO *PKSVBIFrameInfo;

typedef tagKS_VBI_FRAME_INFO TKSVBIFrameInfo;

typedef KSPROPERTY_ALLOCATOR_CONTROL TKSPropertyAllocatorControl;

typedef KSPROPERTY_VIDCAP_VIDEOPROCAMP TKSPropertyVidcapVideoProcAmp;

typedef KSPROPERTY_VIDEOPROCAMP_S *PKSPropertyVideoProcAmpS;

typedef KSPROPERTY_VIDEOPROCAMP_S TKSPropertyVideoProcAmpS;

typedef KSPROPERTY_VIDEOPROCAMP_NODE_S *PKSPropertyVideoProcAmpNodeS;

typedef KSPROPERTY_VIDEOPROCAMP_NODE_S TKSPropertyVideoProcAmpNodeS;

typedef KSPROPERTY_VIDEOPROCAMP_S2 *PKSPropertyVideoProcAmpS2;

typedef KSPROPERTY_VIDEOPROCAMP_S2 TKSPropertyVideoProcAmpS2;

typedef KSPROPERTY_VIDEOPROCAMP_NODE_S2 *PKSPropertyVideoProcAmpNodeS2;

typedef KSPROPERTY_VIDEOPROCAMP_NODE_S2 TKSPropertyVideoProcAmpNodeS2;

typedef KSPROPERTY_VIDCAP_SELECTOR *PKSPropertyVidCapSelector;

typedef KSPROPERTY_VIDCAP_SELECTOR TKSPropertyVidCapSelector;

typedef KSPROPERTY_SELECTOR_S *PKSPropertySelectorS;

typedef KSPROPERTY_SELECTOR_S TKSPropertySelectorS;

typedef KSPROPERTY_SELECTOR_NODE_S *PKSPropertySelectorNodeS;

typedef KSPROPERTY_SELECTOR_NODE_S TKSPropertySelectorNodeS;

typedef KSPROPERTY_TUNER TKSPropertyTuner;

typedef KSPROPERTY_TUNER_CAPS_S *PKSPropertyTunerCapsS;

typedef KSPROPERTY_TUNER_CAPS_S TKSPropertyTunerCapsS;

typedef KSPROPERTY_TUNER_IF_MEDIUM_S *PKSPropertyTunerIfMediumS;

typedef KSPROPERTY_TUNER_IF_MEDIUM_S TKSPropertyTunerIfMediumS;

typedef KSPROPERTY_TUNER_MODE_CAPS_S *PKSPropertyTunerModeCapsS;

typedef KSPROPERTY_TUNER_MODE_CAPS_S TKSPropertyTunerModeCapsS;

typedef KSPROPERTY_TUNER_MODE_S *PKSPropertyTunerModeS;

typedef KSPROPERTY_TUNER_MODE_S TKSPropertyTunerModeS;

typedef KSPROPERTY_TUNER_FREQUENCY_S *PKSPropertyTunerFrequencyS;

typedef KSPROPERTY_TUNER_FREQUENCY_S TKSPropertyTunerFrequencyS;

typedef KSPROPERTY_TUNER_STANDARD_S *PKSPropertyTunerStandardS;

typedef KSPROPERTY_TUNER_STANDARD_S TKSPropertyTunerStandardS;

typedef KSPROPERTY_TUNER_INPUT_S *PKSPropertyTunerInputS;

typedef KSPROPERTY_TUNER_INPUT_S TKSPropertyTunerInputS;

typedef KSPROPERTY_TUNER_STATUS_S *PKSPropertyTunerStatusS;

typedef KSPROPERTY_TUNER_STATUS_S TKSPropertyTunerStatusS;

typedef KSEVENT_TUNER TKSEventTuner;

typedef KSPROPERTY_VIDCAP_VIDEOENCODER TKSPropertyVidCapVideoEncoder;

typedef KSPROPERTY_VIDEOENCODER_S *PKSPropertyVideoEncoderS;

typedef KSPROPERTY_VIDEOENCODER_S TKSPropertyVideoEncoderS;

typedef KSPROPERTY_VIDCAP_VIDEODECODER TKSPropertyVidCapVideoDecoder;

typedef KSPROPERTY_VIDEODECODER_CAPS_S *PKSPropertyVideoDecoderCapsS;

typedef KSPROPERTY_VIDEODECODER_CAPS_S TKSPropertyVideoDecoderCapsS;

typedef KSPROPERTY_VIDEODECODER_STATUS_S *PKSPropertyVideoDecoderStatusS;

typedef KSPROPERTY_VIDEODECODER_STATUS_S TKSPropertyVideoDecoderStatusS;

typedef KSPROPERTY_VIDEODECODER_S *PKSPropertyVideoDecoderS;

typedef KSPROPERTY_VIDEODECODER_S TKSPropertyVideoDecoderS;

typedef KSEVENT_VIDEODECODER TKSEventVideoDecoder;

typedef KSPROPERTY_VIDCAP_CAMERACONTROL TKSPropertyVidCapCameraControl;

typedef KSPROPERTY_CAMERACONTROL_S *PKSPropertyCameraControlS;

typedef KSPROPERTY_CAMERACONTROL_S TKSPropertyCameraControlS;

typedef KSPROPERTY_CAMERACONTROL_NODE_S *PKSPropertyCameraControlNodeS;

typedef KSPROPERTY_CAMERACONTROL_NODE_S TKSPropertyCameraControlNodeS;

typedef KSPROPERTY_CAMERACONTROL_S2 *PKSPropertyCameraControlS2;

typedef KSPROPERTY_CAMERACONTROL_S2 TKSPropertyCameraControlS2;

typedef KSPROPERTY_CAMERACONTROL_NODE_S2 *PKSPropertyCameraControlNodeS2;

typedef KSPROPERTY_CAMERACONTROL_NODE_S2 TKSPropertyCameraControlNodeS2;

typedef KSPROPERTY_CAMERACONTROL_FOCAL_LENGTH_S *PKSPropertyCameraControlFocalLengthS;

typedef KSPROPERTY_CAMERACONTROL_FOCAL_LENGTH_S TKSPropertyCameraControlFocalLengthS;

typedef KSPROPERTY_CAMERACONTROL_NODE_FOCAL_LENGTH_S TKSPropertyCameraControlNodeFocalLengthS;

typedef KSPROPERTY_VIDCAP_CROSSBAR TKSPropertyVidCapCrossbar;

typedef KSPROPERTY_CROSSBAR_CAPS_S *PKSPropertyCrossbarCapsS;

typedef KSPROPERTY_CROSSBAR_CAPS_S TKSPropertyCrossbarCapsS;

typedef KSPROPERTY_CROSSBAR_PININFO_S *PKSPropertyCrossbarPinInfoS;

typedef KSPROPERTY_CROSSBAR_PININFO_S TKSPropertyCrossbarPinInfoS;

typedef KSPROPERTY_CROSSBAR_ROUTE_S *PKSPropertyCrossbarRouteS;

typedef KSPROPERTY_CROSSBAR_ROUTE_S TKSPropertyCrossbarRouteS;

typedef KSEVENT_CROSSBAR TKSEventCrossbar;

typedef KSPROPERTY_VIDCAP_TVAUDIO TKSPropertyVidCapTVAudio;

typedef KSPROPERTY_TVAUDIO_CAPS_S *PKSPropertyTVAudioCapsS;

typedef KSPROPERTY_TVAUDIO_CAPS_S TKSPropertyTVAudioCapsS;

typedef KSPROPERTY_TVAUDIO_S *PKSPropertyTVAudioS;

typedef KSPROPERTY_TVAUDIO_S TKSPropertyTVAudioS;

typedef KSEVENT_TVAUDIO TKSEventTVAudio;

typedef KSPROPERTY_VIDCAP_VIDEOCOMPRESSION TKSPRopertyVidCapVideoCompression;

typedef KSPROPERTY_VIDEOCOMPRESSION_GETINFO_S *PKSPropertyVideoCompressionGetInfoS;

typedef KSPROPERTY_VIDEOCOMPRESSION_GETINFO_S TKSPropertyVideoCompressionGetInfoS;

typedef KSPROPERTY_VIDEOCOMPRESSION_S *PKSPropertyVideoCompressionS;

typedef KSPROPERTY_VIDEOCOMPRESSION_S TKSPropertyVideoCompressionS;

typedef KSDISPLAYCHANGE TKSDisplayChange;

typedef KSPROPERTY_VIDCAP_VIDEOCONTROL TKSPropertyVidCapVideoControl;

typedef KSPROPERTY_VIDEOCONTROL_CAPS_S *PKSPropertyVideoControlCapsS;

typedef KSPROPERTY_VIDEOCONTROL_CAPS_S TKSPropertyVideoControlCapsS;

typedef KSPROPERTY_VIDEOCONTROL_MODE_S *PKSPropertyVideoControlModeS;

typedef KSPROPERTY_VIDEOCONTROL_MODE_S TKSPropertyVideoControlModeS;

typedef KSPROPERTY_VIDEOCONTROL_ACTUAL_FRAME_RATE_S *PKSPropertyVideoControlActualFrameRateS;

typedef KSPROPERTY_VIDEOCONTROL_ACTUAL_FRAME_RATE_S TKSPropertyVideoControlActualFrameRateS;

typedef KSPROPERTY_VIDEOCONTROL_FRAME_RATES_S *PKSPropertyVideoControlFrameRatesS;

typedef KSPROPERTY_VIDEOCONTROL_FRAME_RATES_S TKSPropertyVideoControlFrameRatesS;

typedef KSPROPERTY_VIDCAP_DROPPEDFRAMES TKSPropertyVidCapDroppedFrames;

typedef KSPROPERTY_DROPPEDFRAMES_CURRENT_S *PKSPropertyDroppedFramesCurrentS;

typedef KSPROPERTY_DROPPEDFRAMES_CURRENT_S TKSPropertyDroppedFramesCurrentS;

typedef KSPROPERTY_VPCONFIG TKSPropertyVPConfig;

typedef KSVPMAXPIXELRATE TKSVPMaxPixelRate;

typedef KSVPSIZE_PROP *PKSVPSizeProp;

typedef KSVPSIZE_PROP TKSVPSizeProp;

typedef KSVPSURFACEPARAMS TKSVPSurfaceParams;

typedef _DDVIDEOPORTCONNECT TDDVideoPortConnect;

typedef KSEVENT_VPNOTIFY TKSEventVPNotify;

typedef KSEVENT_VIDCAPTOSTI TKSEventVidCapToSTI;

typedef KSPROPERTY_EXTENSION_UNIT *PKSPropertyExtensionUnit;

typedef KSPROPERTY_EXTENSION_UNIT TKSPropertyExtensionUnit;

typedef KSEVENT_VPVBINOTIFY TKSEventVPVBINotify;

typedef _KSGOP_USERDATA *PKSGopUserData;

typedef _KSGOP_USERDATA TKSGopUserData;

typedef KS_AM_PROPERTY_TS_RATE_CHANGE *PKSAMPropertyTSRateChange;

typedef KS_AM_PROPERTY_TS_RATE_CHANGE TKSAMPropertyTSRateChange;

typedef KS_AM_SimpleRateChange *PKSAMSimpleRateChange;

typedef KS_AM_SimpleRateChange TKSAMSimpleRateChange;

typedef KS_AM_ExactRateChange *PKSAMExactRateChange;

typedef KS_AM_ExactRateChange TKSAMExactRateChange;

typedef KSP_BDA_NODE_PIN *PKSPBDANodePin;

typedef KSP_BDA_NODE_PIN TKSPBDANodePin;

typedef KSM_BDA_PIN *PKSMBDAPin;

typedef KSM_BDA_PIN TKSMBDAPin;

typedef KSM_BDA_PIN_PAIR *PKSMBDAPinPair;

typedef KSM_BDA_PIN_PAIR TKSMBDAPinPair;

typedef KSP_NODE_ESPID *PKSPNodeESPID;

typedef KSP_NODE_ESPID TKSPNodeESPID;

typedef KS_DATARANGE_BDA_ANTENNA *PKSDataRangeBDAAntenna;

typedef KS_DATARANGE_BDA_ANTENNA TKSDataRangeBDAAntenna;

typedef BDA_TRANSPORT_INFO *PBDATransportInfo;

typedef BDA_TRANSPORT_INFO TBDATransportInfo;

typedef KS_DATARANGE_BDA_TRANSPORT *PKSDataRangeBDATransport;

typedef KS_DATARANGE_BDA_TRANSPORT TKSDataRangeBDATransport;

typedef KSPROPERTY_BDA_ETHERNET_FILTER TKSPropertyBDAEthernetFilter;

typedef KSPROPERTY_BDA_IPv4_FILTER TKSPropertyBDAIPv4Filter;

typedef KSPROPERTY_BDA_IPv6_FILTER TKSPropertyBDAIPv6Filter;

typedef KSPROPERTY_BDA_SIGNAL_STATS TKSPropertyBDASignalStats;

typedef KSMETHOD_BDA_CHANGE_SYNC TKSMethodBDAChangeSync;

typedef KSMETHOD_BDA_DEVICE_CONFIGURATION TKSMethodBDADeviceConfiguration;

typedef KSPROPERTY_BDA_TOPOLOGY TKSPropertyBDATopology;

typedef KSPROPERTY_BDA_PIN_CONTROL TKSPropertyBDAPinControl;

typedef KSPROPERTY_BDA_PIN_EVENT TKSPropertyBDAPinEvent;

typedef KSPROPERTY_BDA_VOID_TRANSFORM TKSPropertyBDAVoidTransform;

typedef KSPROPERTY_BDA_NULL_TRANSFORM TKSPropertyBDANullTransform;

typedef KSPROPERTY_BDA_FREQUENCY_FILTER TKSPropertyBDAFrequencyFilter;

typedef KSPROPERTY_BDA_LNB_INFO TKSPropertyBDALNBInfo;

typedef KSPROPERTY_BDA_DIGITAL_DEMODULATOR TKSPropertyBDADigitalDemodulator;

typedef KSPROPERTY_IDS_BDA_TABLE TKSPropertyIdsBDATable;

typedef KSPROPERTY_BDA_PIDFILTER TKSPropertyBDAPIDFilter;

typedef KSPROPERTY_BDA_CA TKSPropertyBDACA;

typedef KSPROPERTY_BDA_CA_EVENT TKSPropertyBDACAEvent;

typedef KSPROPERTY_IPSINK TKSPropertyIPSink;

typedef PID_BITS *PPIDBits;

typedef PID_BITS TPIDBits;

typedef MPEG_HEADER_BITS *PMPEGHeaderBits;

typedef MPEG_HEADER_BITS TMPEGHeaderBits;

typedef MPEG_HEADER_VERSION_BITS *PMPEGHeaderVersionBits;

typedef MPEG_HEADER_VERSION_BITS TMPEGHeaderVersionBits;

typedef MPEG_CURRENT_NEXT_BIT TMPEGCurrentNextBit;

typedef TID_EXTENSION *PTidExtension;

typedef TID_EXTENSION TTidExtension;

typedef SECTION TSection;

typedef LONG_SECTION *PLongSection;

typedef LONG_SECTION TLongSection;

typedef DSMCC_SECTION *PDSMCCSection;

typedef DSMCC_SECTION TDSMCCSection;

typedef MPEG_RQST_PACKET *PMPEGRQSTPacket;

typedef MPEG_RQST_PACKET TMPEGRQSTPacket;

typedef MPEG_PACKET_LIST *PMPEGPacketList;

typedef MPEG_PACKET_LIST TMPEGPacketList;

typedef DSMCC_FILTER_OPTIONS *PDSMCCFilterOptions;

typedef DSMCC_FILTER_OPTIONS TDSMCCFilterOptions;

typedef ATSC_FILTER_OPTIONS *PATSCFilterOptions;

typedef ATSC_FILTER_OPTIONS TATSCFilterOptions;

typedef MPEG2_FILTER *PMPEG2Filter;

typedef MPEG2_FILTER TMPEG2Filter;

typedef MPEG_STREAM_BUFFER *PMPEGStreamBuffer;

typedef MPEG_STREAM_BUFFER TMPEGStreamBuffer;

typedef MPEG_TIME *PMPEGTime;

typedef MPEG_TIME TMPEGTime;

typedef MPEG_DATE *PMPEGDate;

typedef MPEG_DATE TMPEGDate;

typedef MPEG_DATE_AND_TIME *PMPEGDateAndTime;

typedef MPEG_DATE_AND_TIME TMPEGDateAndTime;

typedef MPEG_CONTEXT_TYPE TMPEGContextType;

typedef MPEG_BCS_DEMUX TMPEGBCSDemux;

typedef MPEG_WINSOCK TMPEGWinsock;

typedef MPEG_CONTEXT *PMPEGContext;

typedef MPEG_CONTEXT TMPEGContext;

typedef MPEG_REQUEST_TYPE TMPEGRequestType;

typedef MPEG_SERVICE_REQUEST *PMPEGServiceRequest;

typedef MPEG_SERVICE_REQUEST TMPEGServiceRequest;

typedef MPEG_SERVICE_RESPONSE *PMPEGServiceResponse;

typedef MPEG_SERVICE_RESPONSE TMPEGServiceResponse;

typedef DSMCC_ELEMENT *PDSMCCElement;

typedef DSMCC_ELEMENT TDSMCCElement;

typedef MPE_ELEMENT *PMPEElement;

typedef MPE_ELEMENT TMPEElement;

typedef MPEG_STREAM_FILTER *PMPEGStreamFilter;

typedef MPEG_STREAM_FILTER TMPEGStreamFilter;

typedef tagDEVCAPS TDevCaps;

typedef tagTRANSPORTSTATUS TTransportStatus;

typedef tagTRANSPORTBASICPARMS TTransportBasicParms;

typedef tagTRANSPORTVIDEOPARMS TTransportVideoParms;

typedef tagTRANSPORTAUDIOPARMS TTransportAudioParms;

typedef KSPROPERTY_EXTDEVICE TKSPropertyExtDevice;

typedef KSPROPERTY_EXTDEVICE_S *PKSPropertyExtDeviceS;

typedef KSPROPERTY_EXTDEVICE_S TKSPropertyExtDeviceS;

typedef KSPROPERTY_EXTXPORT TKSPropertyExtXPort;

typedef MEDIUM_INFO *PMediumInfo;

typedef MEDIUM_INFO TMediumInfo;

typedef TRANSPORT_STATE *PTransportState;

typedef TRANSPORT_STATE TTransportState;

typedef KSPROPERTY_EXTXPORT_S *PKSPropertyExtXPortS;

typedef KSPROPERTY_EXTXPORT_S TKSPropertyExtXPortS;

typedef KSPROPERTY_EXTXPORT_NODE_S *PKSPropertyExtxportNodeS;

typedef KSPROPERTY_EXTXPORT_NODE_S TKSPropertyExtxportNodeS;

typedef KSPROPERTY_TIMECODE TKSPropertyTimeCode;

typedef KSPROPERTY_TIMECODE_S TKSPropertyTimeCodeS;

typedef PKSPROPERTY_TIMECODE_NODE_S *PKSPropertyTimecodeNodeS;

typedef PKSPROPERTY_TIMECODE_NODE_S TKSPropertyTimecodeNodeS;

typedef KSEVENT_DEVCMD TKSEventDevCmd;

typedef STREAMBUFFER_ATTR_DATATYPE TStreamBufferAttrDataType;

typedef STREAMBUFFER_ATTRIBUTE *PStreamBufferAttribute;

typedef STREAMBUFFER_ATTRIBUTE TStreamBufferAttribute;

typedef VMR9PresentationInfo *PVMR9PresentationInfo;

typedef VMR9PresentationInfo TVMR9PresentationInfo;

typedef _VMR9AllocationInfo *PVMR9AllocationInfo;

typedef _VMR9AllocationInfo TVMR9AllocationInfo;

typedef VMR9AspectRatioMode TVMR9AspectRatioMode;

typedef _VMR9NormalizedRect *PVMR9NormalizedRect;

typedef _VMR9NormalizedRect TVMR9NormalizedRect;

typedef _VMR9ProcAmpControl *PVMR9ProcAmpControl;

typedef _VMR9ProcAmpControl TVMR9ProcAmpControl;

typedef _VMR9ProcAmpControlRange *PVMR9ProcAmpControlRange;

typedef _VMR9ProcAmpControlRange TVMR9ProcAmpControlRange;

typedef _VMR9AlphaBitmap *PVMR9AlphaBitmap;

typedef _VMR9AlphaBitmap TVMR9AlphaBitmap;

typedef _VMR9Frequency *PVMR9Frequency;

typedef _VMR9Frequency TVMR9Frequency;

typedef _VMR9_SampleFormat TVMR9SampleFormat;

typedef _VMR9VideoDesc *PVMR9VideoDesc;

typedef _VMR9VideoDesc TVMR9VideoDesc;

typedef _VMR9DeinterlaceCaps *PVMR9DeinterlaceCaps;

typedef _VMR9DeinterlaceCaps TVMR9DeinterlaceCaps;

typedef _VMR9VideoStreamInfo *PVMR9VideoStreamInfo;

typedef _VMR9VideoStreamInfo TVMR9VideoStreamInfo;

typedef _VMR9MonitorInfo *PVMR9MonitorInfo;

typedef _VMR9MonitorInfo TVMR9MonitorInfo;

typedef _AM_WST_PAGE *PAM_WST_PAGE;

typedef _AM_WST_PAGE TAM_WST_PAGE;

enum DECLSPEC_DENUM _AM_WST_LEVEL : unsigned int { AM_WST_LEVEL_1_5 };

typedef _AM_WST_LEVEL *PAM_WST_LEVEL;

typedef _AM_WST_LEVEL TAM_WST_LEVEL;

typedef _AM_WST_SERVICE *PAM_WST_SERVICE;

typedef _AM_WST_SERVICE TAM_WST_SERVICE;

typedef _AM_WST_STATE *PAM_WST_STATE;

typedef _AM_WST_STATE TAM_WST_STATE;

typedef _AM_WST_STYLE *PAM_WST_STYLE;

typedef _AM_WST_STYLE TAM_WST_STYLE;

typedef _AM_WST_DRAWBGMODE *PAM_WST_DRAWBGMODE;

typedef _AM_WST_DRAWBGMODE TAM_WST_DRAWBGMODE;

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 AVITIMECODEINDEX_NUMINDEX = System::Int8(0x4);
static const System::Word AVITIMECODEINDEX_TOTAL_ARRAY = System::Word(0x3fe);
extern DELPHI_PACKAGE GUID GUID_NULL;
extern DELPHI_PACKAGE GUID MEDIATYPE_NULL;
extern DELPHI_PACKAGE GUID MEDIASUBTYPE_NULL;
extern DELPHI_PACKAGE GUID IID_IMpegVideoDecoder;
extern DELPHI_PACKAGE GUID CLSID_MpegAudioDecodePropertyPage;
extern DELPHI_PACKAGE GUID CLSID_MpegVideoDecodePropertyPage;
extern DELPHI_PACKAGE GUID CLSID_MMMpeg1VideoCodec;
extern DELPHI_PACKAGE GUID VIDEO_DECODER_CLSID;
extern DELPHI_PACKAGE GUID CLSID_MMMpeg1AudioCodec;
extern DELPHI_PACKAGE GUID AUDIO_DECODER_CLSID;
}	/* namespace Directshow9 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_DIRECTSHOW9)
using namespace Winapi::Directshow9;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Directshow9HPP
