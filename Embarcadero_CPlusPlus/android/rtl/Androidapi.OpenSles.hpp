// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.OpenSles.pas' rev: 34.00 (Android)

#ifndef Androidapi_OpenslesHPP
#define Androidapi_OpenslesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <SLES/OpenSLES_Platform.h>
#include <SLES/OpenSLES_AndroidConfiguration.h>

namespace Androidapi
{
namespace Opensles
{
//-- forward type declarations -----------------------------------------------
struct SLMetadataExtractionItf_;
struct SLEngineItf_;
//-- type declarations -------------------------------------------------------
typedef unsigned __int64 sl_uint64_t;

typedef System::Int8 *PSLint8;

typedef System::Byte *PSLuint8;

typedef short *PSLint16;

typedef System::Word *PSLuint16;

typedef int *PSLint32;

typedef unsigned *PSLuint32;

typedef unsigned *PSLboolean;

typedef char * PSLchar;

typedef char * *PPSLchar;

typedef short *PSLmillibel;

typedef unsigned *PSLmillisecond;

typedef unsigned *PSLmilliHertz;

typedef int *PSLmillimeter;

typedef int *PSLmillidegree;

typedef short *PSLpermille;

typedef unsigned *PSLmicrosecond;

typedef unsigned *PSLresult;

typedef SLInterfaceID *PSLInterfaceID;

typedef SLObjectItf_ *PSLObjectItf_;

typedef void __cdecl (*slObjectCallback)(SLObjectItf caller, const void * pContext, unsigned event, unsigned result, unsigned param, void * pInterface);

typedef SLObjectItf *PSLObjectItf;

typedef SLDataLocator_URI *PSLDataLocator_URI;

typedef SLDataLocator_Address *PSLDataLocator_Address;

typedef SLDataLocator_IODevice *PSLDataLocator_IODevice;

typedef SLDataLocator_OutputMix *PSLDataLocator_OutputMix;

typedef SLDataLocator_BufferQueue *PSLDataLocator_BufferQueue;

typedef SLDataLocator_MIDIBufferQueue *PSLDataLocator_MIDIBufferQueue;

typedef SLDataFormat_MIME *PSLDataFormat_MIME;

typedef SLDataFormat_PCM *PSLDataFormat_PCM;

typedef SLDataSource *PSLDataSource;

typedef SLDataSink *PSLDataSink;

typedef SLAudioInputDescriptor *PSLAudioInputDescriptor;

typedef SLAudioOutputDescriptor *PSLAudioOutputDescriptor;

typedef SLAudioIODeviceCapabilitiesItf_ *PSLAudioIODeviceCapabilitiesItf_;

typedef void __cdecl (*slAvailableAudioInputsChangedCallback)(SLAudioIODeviceCapabilitiesItf caller, void * pContext, unsigned deviceID, int numInputs, unsigned isNew);

typedef void __cdecl (*slAvailableAudioOutputsChangedCallback)(SLAudioIODeviceCapabilitiesItf caller, void * pContext, unsigned deviceID, int numOutputs, unsigned isNew);

typedef void __cdecl (*slDefaultDeviceIDMapChangedCallback)(SLAudioIODeviceCapabilitiesItf caller, void * pContext, unsigned isOutput, int numDevices);

typedef SLLEDDescriptor *PSLLEDDescriptor;

typedef SLHSL *PSLHSL;

typedef SLLEDArrayItf_ *PSLLEDArrayItf_;

typedef SLVibraDescriptor *PSLVibraDescriptor;

typedef SLVibraItf_ *PSLVibraItf_;

typedef SLMetadataInfo *PSLMetadataInfo;

typedef SLMetadataExtractionItf_ *PSLMetadataExtractionItf_;

struct DECLSPEC_DRECORD SLMetadataExtractionItf_
{
public:
	unsigned __fastcall (*GetItemCount)(SLMetadataExtractionItf self, PSLuint32 pItemCount);
	unsigned __cdecl (*GetKeySize)(SLMetadataExtractionItf self, unsigned index, PSLuint32 pKeySize);
	unsigned __cdecl (*GetKey)(SLMetadataExtractionItf self, unsigned index, unsigned keySize, PSLMetadataInfo pKey);
	unsigned __cdecl (*GetValueSize)(SLMetadataExtractionItf self, unsigned index, PSLuint32 pValueSize);
	unsigned __cdecl (*GetValue)(SLMetadataExtractionItf self, unsigned index, unsigned valueSize, PSLMetadataInfo pValue);
	unsigned __cdecl (*AddKeyFilter)(SLMetadataExtractionItf self, unsigned keySize, void * pKey, unsigned keyEncoding, const char * pValueLangCountry, unsigned valueEncoding, System::Byte filterMask);
	unsigned __cdecl (*ClearKeyFilter)(SLMetadataExtractionItf self);
};


typedef SLMetadataTraversalItf_ *PSLMetadataTraversalItf_;

typedef SLDynamicSourceItf_ *PSLDynamicSourceItf_;

typedef SLOutputMixItf_ *PSLOutputMixItf_;

typedef void __cdecl (*slMixDeviceChangeCallback)(SLOutputMixItf caller, void * pContext);

typedef SLPlayItf_ *PSLPlayItf_;

typedef void __cdecl (*slPlayCallback)(SLPlayItf caller, void * pContext, unsigned event);

typedef SLPrefetchStatusItf_ *PSLPrefetchStatusItf_;

typedef void __cdecl (*slPrefetchCallback)(SLPrefetchStatusItf caller, void * pContext, unsigned event);

typedef SLPlaybackRateItf_ *PSLPlaybackRateItf_;

typedef SLSeekItf_ *PSLSeekItf_;

typedef SLRecordItf_ *PSLRecordItf_;

typedef void __cdecl (*slRecordCallback)(SLRecordItf caller, void * pContext, unsigned event);

typedef SLEqualizerItf_ *PSLEqualizerItf_;

typedef SLVolumeItf *PSLVolumeItf_;

typedef SLDeviceVolumeItf *PSLDeviceVolumeItf_;

typedef SLBufferQueueState *PSLBufferQueueState;

typedef SLBufferQueueItf *PSLBufferQueueItf_;

typedef void __cdecl (*slBufferQueueCallback)(SLBufferQueueItf caller, void * pContext);

typedef SLPresetReverbItf *PSLPresetReverbItf_;

typedef SLEnvironmentalReverbSettings *PSLEnvironmentalReverbSettings;

typedef SLEnvironmentalReverbItf_ *PSLEnvironmentalReverbItf_;

typedef SLEffectSendItf *PSLEffectSendItf_;

typedef SL3DGroupingItf *PSL3DGroupingItf_;

typedef SL3DCommitItf *PSL3DCommitItf_;

typedef SLVec3D *PSLVec3D;

typedef SL3DLocationItf *PSL3DLocationItf_;

typedef SL3DDopplerItf *PSL3DDopplerItf_;

typedef SL3DSourceItf *PSL3DSourceItf_;

typedef SL3DMacroscopicItf *PSL3DMacroscopicItf_;

typedef SLMuteSoloItf *PSLMuteSoloItf_;

typedef SLDynamicInterfaceManagementItf *PSLDynamicInterfaceManagementItf_;

typedef void __cdecl (*slDynamicInterfaceManagementCallback)(SLDynamicInterfaceManagementItf caller, void * pContext, unsigned event, unsigned result, SLInterfaceID iid);

typedef SLMIDIMessageItf *PSLMIDIMessageItf_;

typedef void __cdecl (*slMetaEventCallback)(SLMIDIMessageItf caller, void * pContext, System::Byte _type, unsigned length, PSLuint8 pData, unsigned tick, System::Word track);

typedef void __cdecl (*slMIDIMessageCallback)(SLMIDIMessageItf caller, void * pContext, System::Byte statusByte, unsigned length, PSLuint8 pData, unsigned tick, System::Word track);

typedef SLMIDIMuteSoloItf *PSLMIDIMuteSoloItf_;

typedef SLMIDITempoItf *PSLMIDITempoItf_;

typedef SLMIDITimeItf *PSLMIDITimeItf_;

typedef SLAudioCodecDescriptor *PSLAudioCodecDescriptor;

typedef SLAudioCodecProfileMode *PSLAudioCodecProfileMode;

typedef SLAudioDecoderCapabilitiesItf_ *PSLAudioDecoderCapabilitiesItf_;

typedef SLAudioEncoderSettings *PSLAudioEncoderSettings;

typedef SLAudioEncoderCapabilitiesItf *PSLAudioEncoderCapabilitiesItf_;

typedef SLAudioEncoderItf *PSLAudioEncoderItf_;

typedef SLBassBoostItf *PSLBassBoostItf_;

typedef SLPitchItf *PSLPitchItf_;

typedef SLRatePitchItf *PSLRatePitchItf_;

typedef SLVirtualizerItf *PSLVirtualizerItf_;

typedef SLVisualizationItf *PSLVisualizationItf_;

typedef void __cdecl (*slVisualizationCallback)(void * pContext, PSLuint8 waveform, PSLuint8 fft, unsigned sampleRate);

typedef SLEngineItf *PSLEngineItf_;

struct DECLSPEC_DRECORD SLEngineItf_
{
public:
	unsigned __fastcall (*CreateLEDDevice)(SLEngineItf self, PSLObjectItf pDevice, unsigned deviceID, unsigned numInterfaces, PSLInterfaceID pInterfaceIDs, PSLboolean pInterfaceRequired);
	unsigned __fastcall (*CreateVibraDevice)(SLEngineItf self, PSLObjectItf pDevice, unsigned deviceID, unsigned numInterfaces, PSLInterfaceID pInterfaceIDs, PSLboolean pInterfaceRequired);
	unsigned __fastcall (*CreateAudioPlayer)(SLEngineItf self, PSLObjectItf pPlayer, PSLDataSource pAudioSrc, PSLDataSink pAudioSnk, unsigned numInterfaces, PSLInterfaceID pInterfaceIDs, PSLboolean pInterfaceRequired);
	unsigned __fastcall (*CreateAudioRecorder)(SLEngineItf self, PSLObjectItf pRecorder, PSLDataSource pAudioSrc, PSLDataSink pAudioSnk, unsigned numInterfaces, PSLInterfaceID pInterfaceIDs, PSLboolean pInterfaceRequired);
	unsigned __cdecl (*CreateMidiPlayer)(SLEngineItf self, PSLObjectItf pPlayer, PSLDataSource pMIDISrc, PSLDataSource pBankSrc, PSLDataSink pAudioOutput, PSLDataSink pVibra, PSLDataSink pLEDArray, unsigned numInterfaces, PSLInterfaceID pInterfaceIDs, PSLboolean pInterfaceRequired);
	unsigned __cdecl (*CreateListener)(SLEngineItf self, PSLObjectItf pListener, unsigned numInterfaces, PSLInterfaceID pInterfaceIDs, PSLboolean pInterfaceRequired);
	unsigned __cdecl (*Create3DGroup)(SLEngineItf self, PSLObjectItf pGroup, unsigned numInterfaces, PSLInterfaceID pInterfaceIDs, PSLboolean pInterfaceRequired);
	unsigned __cdecl (*CreateOutputMix)(SLEngineItf self, PSLObjectItf pMix, unsigned numInterfaces, PSLInterfaceID pInterfaceIDs, PSLboolean pInterfaceRequired);
	unsigned __cdecl (*CreateMetadataExtractor)(SLEngineItf self, PSLObjectItf pMetadataExtractor, PSLDataSource pDataSource, unsigned numInterfaces, PSLInterfaceID pInterfaceIDs, PSLboolean pInterfaceRequired);
	unsigned __fastcall (*CreateExtensionObject)(SLEngineItf self, PSLObjectItf pObject, void * pParameters, unsigned objectID, unsigned numInterfaces, PSLInterfaceID pInterfaceIDs, PSLboolean pInterfaceRequired);
	unsigned __cdecl (*QueryNumSupportedInterfaces)(SLEngineItf self, unsigned objectID, PSLuint32 pNumSupportedInterfaces);
	unsigned __cdecl (*QuerySupportedInterfaces)(SLEngineItf self, unsigned objectID, unsigned index, PSLInterfaceID pInterfaceId);
	unsigned __cdecl (*QueryNumSupportedExtensions)(SLEngineItf self, PSLuint32 pNumExtensions);
	unsigned __cdecl (*QuerySupportedExtension)(SLEngineItf self, unsigned index, char * pExtensionName, PSLint16 pNameLength);
	unsigned __cdecl (*IsExtensionSupported)(SLEngineItf self, char * pExtensionName, PSLboolean pSupported);
};


typedef SLEngineCapabilitiesItf *PSLEngineCapabilitiesItf_;

typedef SLThreadSyncItf *PSLThreadSyncItf_;

typedef SLEngineOption *PSLEngineOption;

typedef __int64 SLAint64;

typedef unsigned __int64 SLAuint64;

typedef SLAndroidEffectItf_ *PSLAndroidEffectItf_;

typedef SLAndroidEffectSendItf_ *PSLAndroidEffectSendItf_;

typedef SLAndroidEffectCapabilitiesItf_ *PSLAndroidEffectCapabilitiesItf_;

typedef SLAndroidConfigurationItf_ *PSLAndroidConfigurationItf_;

typedef SLAndroidSimpleBufferQueueState *PSLAndroidSimpleBufferQueueState;

typedef SLAndroidSimpleBufferQueueItf_ *PSLAndroidSimpleBufferQueueItf_;

typedef void __cdecl (*slAndroidSimpleBufferQueueCallback)(SLAndroidSimpleBufferQueueItf caller, void * pContext);

typedef SLDataLocator_AndroidFD *PSLDataLocator_AndroidFD;

typedef SLDataLocator_AndroidSimpleBufferQueue *PSLDataLocator_AndroidSimpleBufferQueue;

//-- var, const, procedure ---------------------------------------------------
#define AndroidLib u"/usr/lib/libandroid.so"
#define AndroidJniGraphicsLib u"/usr/lib/libjnigraphics.so"
#define AndroidEglLib u"/usr/lib/libEGL.so"
#define AndroidGlesLib u"/usr/lib/libGLESv1_CM.so"
#define AndroidGles2Lib u"/usr/lib/libGLESv2.so"
#define AndroidLogLib u"/usr/lib/liblog.so"
#define AndroidOpenSlesLib u"/usr/lib/libOpenSLES.so"
#define AndroidNativeWindowLib u"/usr/lib/libnativewindow.so"
}	/* namespace Opensles */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_OPENSLES)
using namespace Androidapi::Opensles;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_OpenslesHPP
