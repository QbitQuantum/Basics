// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.WMF9.pas' rev: 34.00 (Windows)

#ifndef Winapi_Wmf9HPP
#define Winapi_Wmf9HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>
#include <Winapi.DirectShow9.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
#include "asferr.h"
#include "drmexternals.h"
#include "dshowasf.h"
#include "nserror.h"
#include "wmdxva.h"
#include "wmnetsourcecreator.h"
#include "wmsbuffer.h"
#include "wmsdk.h"
#include "wmsdkidl.h"
#include "wmsdkvalidate.h"
#include "wmsinternaladminnetsource.h"
#include "wmsysprf.h"
typedef System::DelphiInterface<IWMPlayerTimestampHook> _di_IWMPlayerTimestampHook;
typedef System::DelphiInterface<IWMCodecAMVideoAccelerator> _di_IWMCodecAMVideoAccelerator;
typedef System::DelphiInterface<IWMCodecVideoAccelerator> _di_IWMCodecVideoAccelerator;
typedef System::DelphiInterface<INSNetSourceCreator> _di_INSNetSourceCreator;
typedef System::DelphiInterface<INSSBuffer> _di_INSSBuffer;
typedef System::DelphiInterface<INSSBuffer2> _di_INSSBuffer2;
typedef System::DelphiInterface<INSSBuffer3> _di_INSSBuffer3;
typedef System::DelphiInterface<INSSBuffer4> _di_INSSBuffer4;
typedef System::DelphiInterface<IWMSBufferAllocator> _di_IWMSBufferAllocator;
typedef System::DelphiInterface<IWMSInternalAdminNetSource> _di_IWMSInternalAdminNetSource;
typedef System::DelphiInterface<IWMSInternalAdminNetSource2> _di_IWMSInternalAdminNetSource2;
typedef System::DelphiInterface<IWMSInternalAdminNetSource3> _di_IWMSInternalAdminNetSource3;
typedef System::DelphiInterface<IWMMediaProps> _di_IWMMediaProps;
typedef System::DelphiInterface<IWMVideoMediaProps> _di_IWMVideoMediaProps;
typedef System::DelphiInterface<IWMWriter> _di_IWMWriter;
typedef System::DelphiInterface<IWMDRMWriter> _di_IWMDRMWriter;
typedef System::DelphiInterface<IWMInputMediaProps> _di_IWMInputMediaProps;
typedef System::DelphiInterface<IWMPropertyVault> _di_IWMPropertyVault;
typedef System::DelphiInterface<IWMIStreamProps> _di_IWMIStreamProps;
typedef System::DelphiInterface<IWMReader> _di_IWMReader;
typedef System::DelphiInterface<IWMSyncReader> _di_IWMSyncReader;
typedef System::DelphiInterface<IWMSyncReader2> _di_IWMSyncReader2;
typedef System::DelphiInterface<IWMOutputMediaProps> _di_IWMOutputMediaProps;
typedef System::DelphiInterface<IWMStatusCallback> _di_IWMStatusCallback;
typedef System::DelphiInterface<IWMReaderCallback> _di_IWMReaderCallback;
typedef System::DelphiInterface<IWMCredentialCallback> _di_IWMCredentialCallback;
typedef System::DelphiInterface<IWMMetadataEditor> _di_IWMMetadataEditor;
typedef System::DelphiInterface<IWMMetadataEditor2> _di_IWMMetadataEditor2;
typedef System::DelphiInterface<IWMDRMEditor> _di_IWMDRMEditor;
typedef System::DelphiInterface<IWMHeaderInfo> _di_IWMHeaderInfo;
typedef System::DelphiInterface<IWMHeaderInfo2> _di_IWMHeaderInfo2;
typedef System::DelphiInterface<IWMHeaderInfo3> _di_IWMHeaderInfo3;
typedef System::DelphiInterface<IWMProfileManager> _di_IWMProfileManager;
typedef System::DelphiInterface<IWMProfileManager2> _di_IWMProfileManager2;
typedef System::DelphiInterface<IWMProfileManagerLanguage> _di_IWMProfileManagerLanguage;
typedef System::DelphiInterface<IWMProfile> _di_IWMProfile;
typedef System::DelphiInterface<IWMProfile2> _di_IWMProfile2;
typedef System::DelphiInterface<IWMProfile3> _di_IWMProfile3;
typedef System::DelphiInterface<IWMStreamConfig> _di_IWMStreamConfig;
typedef System::DelphiInterface<IWMStreamConfig2> _di_IWMStreamConfig2;
typedef System::DelphiInterface<IWMStreamConfig3> _di_IWMStreamConfig3;
typedef System::DelphiInterface<IWMPacketSize> _di_IWMPacketSize;
typedef System::DelphiInterface<IWMPacketSize2> _di_IWMPacketSize2;
typedef System::DelphiInterface<IWMStreamList> _di_IWMStreamList;
typedef System::DelphiInterface<IWMMutualExclusion> _di_IWMMutualExclusion;
typedef System::DelphiInterface<IWMMutualExclusion2> _di_IWMMutualExclusion2;
typedef System::DelphiInterface<IWMBandwidthSharing> _di_IWMBandwidthSharing;
typedef System::DelphiInterface<IWMStreamPrioritization> _di_IWMStreamPrioritization;
typedef System::DelphiInterface<IWMWriterAdvanced> _di_IWMWriterAdvanced;
typedef System::DelphiInterface<IWMWriterAdvanced2> _di_IWMWriterAdvanced2;
typedef System::DelphiInterface<IWMWriterAdvanced3> _di_IWMWriterAdvanced3;
typedef System::DelphiInterface<IWMWriterPreprocess> _di_IWMWriterPreprocess;
typedef System::DelphiInterface<IWMWriterPostViewCallback> _di_IWMWriterPostViewCallback;
typedef System::DelphiInterface<IWMWriterPostView> _di_IWMWriterPostView;
typedef System::DelphiInterface<IWMWriterSink> _di_IWMWriterSink;
typedef System::DelphiInterface<IWMRegisterCallback> _di_IWMRegisterCallback;
typedef System::DelphiInterface<IWMWriterFileSink> _di_IWMWriterFileSink;
typedef System::DelphiInterface<IWMWriterFileSink2> _di_IWMWriterFileSink2;
typedef System::DelphiInterface<IWMWriterFileSink3> _di_IWMWriterFileSink3;
typedef System::DelphiInterface<IWMWriterNetworkSink> _di_IWMWriterNetworkSink;
typedef System::DelphiInterface<IWMClientConnections> _di_IWMClientConnections;
typedef System::DelphiInterface<IWMClientConnections2> _di_IWMClientConnections2;
typedef System::DelphiInterface<IWMReaderAdvanced> _di_IWMReaderAdvanced;
typedef System::DelphiInterface<IWMReaderAdvanced2> _di_IWMReaderAdvanced2;
typedef System::DelphiInterface<IWMReaderAdvanced3> _di_IWMReaderAdvanced3;
typedef System::DelphiInterface<IWMReaderAdvanced4> _di_IWMReaderAdvanced4;
typedef System::DelphiInterface<IWMReaderAllocatorEx> _di_IWMReaderAllocatorEx;
typedef System::DelphiInterface<IWMReaderTypeNegotiation> _di_IWMReaderTypeNegotiation;
typedef System::DelphiInterface<IWMReaderCallbackAdvanced> _di_IWMReaderCallbackAdvanced;
typedef System::DelphiInterface<IWMDRMReader> _di_IWMDRMReader;
typedef System::DelphiInterface<IWMReaderNetworkConfig> _di_IWMReaderNetworkConfig;
typedef System::DelphiInterface<IWMReaderNetworkConfig2> _di_IWMReaderNetworkConfig2;
typedef System::DelphiInterface<IWMReaderStreamClock> _di_IWMReaderStreamClock;
typedef System::DelphiInterface<IWMIndexer> _di_IWMIndexer;
typedef System::DelphiInterface<IWMIndexer2> _di_IWMIndexer2;
typedef System::DelphiInterface<IWMLicenseBackup> _di_IWMLicenseBackup;
typedef System::DelphiInterface<IWMLicenseRestore> _di_IWMLicenseRestore;
typedef System::DelphiInterface<IWMBackupRestoreProps> _di_IWMBackupRestoreProps;
typedef System::DelphiInterface<IWMCodecInfo> _di_IWMCodecInfo;
typedef System::DelphiInterface<IWMCodecInfo2> _di_IWMCodecInfo2;
typedef System::DelphiInterface<IWMCodecInfo3> _di_IWMCodecInfo3;
typedef System::DelphiInterface<IWMLanguageList> _di_IWMLanguageList;
typedef System::DelphiInterface<IWMWriterPushSink> _di_IWMWriterPushSink;
typedef System::DelphiInterface<IWMWatermarkInfo> _di_IWMWatermarkInfo;
typedef System::DelphiInterface<IWMReaderAccelerator> _di_IWMReaderAccelerator;
typedef System::DelphiInterface<IWMReaderTimecode> _di_IWMReaderTimecode;
typedef System::DelphiInterface<IWMAddressAccess> _di_IWMAddressAccess;
typedef System::DelphiInterface<IWMAddressAccess2> _di_IWMAddressAccess2;
typedef System::DelphiInterface<IWMImageInfo> _di_IWMImageInfo;
typedef System::DelphiInterface<IAMWMBufferPass> _di_IAMWMBufferPass;
typedef System::DelphiInterface<IAMWMBufferPassCallback> _di_IAMWMBufferPassCallback;
typedef System::DelphiInterface<IConfigAsfWriter2> _di_IConfigAsfWriter2;
typedef System::DelphiInterface<IConfigAsfWriter> _di_IConfigAsfWriter;

namespace Winapi
{
namespace Wmf9
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef DRM_LICENSE_STATE_CATEGORY TDRMLicenseStateCategory;

typedef _DRM_LICENSE_STATE_DATA *PDRMLicenseStateData;

typedef _DRM_LICENSE_STATE_DATA TDRMLicenseStateData;

typedef DRM_HTTP_STATUS TDRMHTTPStatus;

typedef DRM_INDIVIDUALIZATION_STATUS TDRMIndividualizationStatus;

typedef _WMIndividualizeStatus *PWMIndividualizeStatus;

typedef _WMIndividualizeStatus TWMIndividualizeStatus;

typedef _WMGetLicenseData *PWMGetLicenseData;

typedef _WMGetLicenseData TWMGetLicenseData;

typedef NETSOURCE_URLCREDPOLICY_SETTINGS TNetSourceURLCredpolicySettings;

typedef WMT_STATUS TWMTStatus;

typedef WMT_STREAM_SELECTION *PWMTStreamSelection;

typedef WMT_STREAM_SELECTION TWMTStreamSelection;

typedef WMT_IMAGE_TYPE TWMTImageType;

typedef WMT_ATTR_DATATYPE TWMTAttrDataType;

typedef WMT_ATTR_IMAGETYPE TWMTAttrImageType;

typedef tagWMT_STORAGE_FORMAT TWMTStorageFormat;

typedef tagWMT_DRMLA_TRUST TWMTDRMLATrust;

typedef tagWMT_TRANSPORT_TYPE TWMTTransportType;

typedef WMT_NET_PROTOCOL TWMTNetProtocol;

typedef WMT_PLAY_MODE TWMTPlayMode;

typedef WMT_PROXY_SETTINGS TWMTProxySettings;

typedef tagWMT_OFFSET_FORMAT TWMTOffsetFormat;

typedef tagWMT_INDEXER_TYPE TWMTIndexerType;

typedef tagWMT_INDEX_TYPE TWMTIndexType;

typedef tagWMT_MUSICSPEECH_CLASS_MODE TWMTMusicSpeechClassMode;

typedef tagWMT_WATERMARK_ENTRY_TYPE TWMTWatermarkEntryType;

typedef _WMStreamPrioritizationRecord *PWMStreamPrioritizationRecord;

typedef _WMStreamPrioritizationRecord TWMStreamPrioritizationRecord;

typedef _WMWriterStatistics *PWMWriterStatistics;

typedef _WMWriterStatistics TWMWriterStatistics;

typedef _WMWriterStatisticsEx *PWMWriterStatisticsEx;

typedef _WMWriterStatisticsEx TWMWriterStatisticsEx;

typedef _WMReaderStatistics *PWMReaderStatistics;

typedef _WMReaderStatistics TWMReaderStatistics;

typedef _WMReaderClientInfo *PWMReaderClientInfo;

typedef _WMReaderClientInfo TWMReaderClientInfo;

typedef _WMClientProperties *PWMClientProperties;

typedef _WMClientProperties TWMClientProperties;

typedef _WMClientPropertiesEx *PWMClientPropertiesEx;

typedef _WMClientPropertiesEx TWMClientPropertiesEx;

typedef _WMPortNumberRange *PWMPortNumberRange;

typedef _WMPortNumberRange TWMPortNumberRange;

typedef _WMT_BUFFER_SEGMENT *PWMTBufferSegment;

typedef _WMT_BUFFER_SEGMENT TWMTBufferSegment;

typedef _WMT_PAYLOAD_FRAGMENT *PWMTPayloadFragment;

typedef _WMT_PAYLOAD_FRAGMENT TWMTPayloadFragment;

typedef _WMT_FILESINK_DATA_UNIT *PWMTFileSinkDataUnit;

typedef _WMT_FILESINK_DATA_UNIT TWMTFileSinkDataUnit;

typedef _WMT_WEBSTREAM_FORMAT *PWMTWebStreamFormat;

typedef _WMT_WEBSTREAM_FORMAT TWMTWebStreamFormat;

typedef _WMT_WEBSTREAM_SAMPLE_HEADER *PWMTWebStreamSampleHeader;

typedef _WMT_WEBSTREAM_SAMPLE_HEADER TWMTWebStreamSampleHeader;

typedef _WMAddressAccessEntry *PWMAddressAccessEntry;

typedef _WMAddressAccessEntry TWMAddressAccessEntry;

typedef _WMPicture *PWMPicture;

typedef _WMPicture TWMPicture;

typedef _WMSynchronisedLyrics *PWMSynchronisedLyrics;

typedef _WMSynchronisedLyrics TWMSynchronisedLyrics;

typedef _WMUserWebURL *PWMUserWebURL;

typedef _WMUserWebURL TWMUserWebURL;

typedef _WMUserText *PWMUserText;

typedef _WMUserText TWMUserText;

typedef _WMLeakyBucketPair *PWMLeakyBucketPair;

typedef _WMLeakyBucketPair TWMLeakyBucketPair;

typedef _WM_LICENSE_STATE_DATA *PWMLicenseStateData;

typedef _WM_LICENSE_STATE_DATA TWMLicenseStateData;

typedef __WMT_WATERMARK_ENTRY *PWMTWatermarkEntry;

typedef __WMT_WATERMARK_ENTRY TWMTWatermarkEntry;

typedef __WMT_VIDEOIMAGE_SAMPLE *PWMTVideoImageSample;

typedef __WMT_VIDEOIMAGE_SAMPLE TWMTVideoImageSample;

typedef _WMMediaType *PWMMediaType;

typedef _WMMediaType TWMMediaType;

typedef tagWMVIDEOINFOHEADER *PWMVideoInfoHeader;

typedef tagWMVIDEOINFOHEADER TWMVideoInfoHeader;

typedef tagWMVIDEOINFOHEADER2 *PWMVideoInfoHeader2;

typedef tagWMVIDEOINFOHEADER2 TWMVideoInfoHeader2;

typedef tagWMMPEG2VIDEOINFO *PWMMPEG2VideoInfo;

typedef tagWMMPEG2VIDEOINFO TWMMPEG2VideoInfo;

typedef tagWMSCRIPTFORMAT *PWMScriptFormat;

typedef tagWMSCRIPTFORMAT TWMScriptFormat;

typedef _WMT_TIMECODE_EXTENSION_DATA *PWMTTimeCodeExtensionData;

typedef _WMT_TIMECODE_EXTENSION_DATA TWMTTimeCodeExtensionData;

typedef _AM_ASFWRITERCONFIG_PARAM TAMASFWriterConfigParam;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Wmf9 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_WMF9)
using namespace Winapi::Wmf9;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Wmf9HPP
