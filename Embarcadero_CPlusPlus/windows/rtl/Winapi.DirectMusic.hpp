// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.DirectMusic.pas' rev: 34.00 (Windows)

#ifndef Winapi_DirectmusicHPP
#define Winapi_DirectmusicHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.MMSystem.hpp>
#include <Winapi.DXTypes.hpp>
#include <Winapi.DirectSound.hpp>

//-- user supplied -----------------------------------------------------------
#include "ks.h"
#include "dls1.h"
#include "dls2.h"
#include "dmdls.h"
#include "dmerror.h"
#include "dmplugin.h"
#include "dmusicc.h"
#include "dmusici.h"
#include "dmusicf.h"
#include "dmusbuff.h"
DECLARE_DINTERFACE_TYPE(IDirectMusic);
DECLARE_DINTERFACE_TYPE(IDirectMusic8);
DECLARE_DINTERFACE_TYPE(IDirectMusicBuffer);
typedef _di_IDirectMusicBuffer _di_IDirectMusicBuffer8;
DECLARE_DINTERFACE_TYPE(IDirectMusicInstrument);
typedef _di_IDirectMusicInstrument _di_IDirectMusicInstrument8;
DECLARE_DINTERFACE_TYPE(IDirectMusicDownloadedInstrument);
typedef _di_IDirectMusicDownloadedInstrument _di_IDirectMusicDownloadedInstrument8;
DECLARE_DINTERFACE_TYPE(IDirectMusicCollection);
typedef _di_IDirectMusicCollection _di_IDirectMusicCollection8;
DECLARE_DINTERFACE_TYPE(IDirectMusicDownload);
typedef _di_IDirectMusicDownload _di_IDirectMusicDownload8;
DECLARE_DINTERFACE_TYPE(IDirectMusicPortDownload);
typedef _di_IDirectMusicPortDownload _di_IDirectMusicPortDownload8;
DECLARE_DINTERFACE_TYPE(IDirectMusicPort);
typedef _di_IDirectMusicPort _di_IDirectMusicPort8;
DECLARE_DINTERFACE_TYPE(IDirectMusicThru);
typedef _di_IDirectMusicThru _di_IDirectMusicThru8;
DECLARE_DINTERFACE_TYPE(IDirectMusicBand);
typedef _di_IDirectMusicBand _di_IDirectMusicBand8;
DECLARE_DINTERFACE_TYPE(IDirectMusicObject);
typedef _di_IDirectMusicObject _di_IDirectMusicObject8;
DECLARE_DINTERFACE_TYPE(IDirectMusicLoader);
DECLARE_DINTERFACE_TYPE(IDirectMusicLoader8);
DECLARE_DINTERFACE_TYPE(IDirectMusicGetLoader);
typedef _di_IDirectMusicGetLoader _di_IDirectMusicGetLoader8;
DECLARE_DINTERFACE_TYPE(IDirectMusicSegment);
DECLARE_DINTERFACE_TYPE(IDirectMusicSegment8);
DECLARE_DINTERFACE_TYPE(IDirectMusicSegmentState);
DECLARE_DINTERFACE_TYPE(IDirectMusicSegmentState8);
DECLARE_DINTERFACE_TYPE(IDirectMusicAudioPath);
typedef _di_IDirectMusicAudioPath _di_IDirectMusicAudioPath8;
DECLARE_DINTERFACE_TYPE(IDirectMusicPerformance);
DECLARE_DINTERFACE_TYPE(IDirectMusicPerformance8);
DECLARE_DINTERFACE_TYPE(IDirectMusicGraph);
typedef _di_IDirectMusicGraph _di_IDirectMusicGraph8;
DECLARE_DINTERFACE_TYPE(IDirectMusicTool);
DECLARE_DINTERFACE_TYPE(IDirectMusicStyle);
DECLARE_DINTERFACE_TYPE(IDirectMusicStyle8);
DECLARE_DINTERFACE_TYPE(IDirectMusicChordMap);
typedef _di_IDirectMusicChordMap _di_IDirectMusicChordMap8;
DECLARE_DINTERFACE_TYPE(IDirectMusicComposer);
typedef _di_IDirectMusicComposer _di_IDirectMusicComposer8;
DECLARE_DINTERFACE_TYPE(IDirectMusicPatternTrack);
typedef _di_IDirectMusicPatternTrack _di_IDirectMusicPatternTrack8;
DECLARE_DINTERFACE_TYPE(IDirectMusicScript);
typedef _di_IDirectMusicScript _di_IDirectMusicScript8;
DECLARE_DINTERFACE_TYPE(IDirectMusicContainer);
typedef _di_IDirectMusicContainer _di_IDirectMusicContainer8;
DECLARE_DINTERFACE_TYPE(IDirectMusicTrack);
DECLARE_DINTERFACE_TYPE(IDirectMusicTool8);
DECLARE_DINTERFACE_TYPE(IDirectMusicTrack8);

namespace Winapi
{
namespace Directmusic
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef _DLSID *PDLSID;

typedef _DLSID TDLSID;

typedef _DLSVERSION *PDLSVersion;

typedef _DLSVERSION TDLSVersion;

typedef _CONNECTION *PConnection;

typedef _CONNECTION TConnection;

typedef _CONNECTIONLIST *PConnectionList;

typedef _CONNECTIONLIST TConnectionList;

typedef _RGNRANGE *PRGNRange;

typedef _RGNRANGE TRGNRange;

typedef _MIDILOCALE *PMIDILocale;

typedef _MIDILOCALE TMIDILocale;

typedef _RGNHEADER *PRGNHeader;

typedef _RGNHEADER TRGNHeader;

typedef _INSTHEADER *PInstHeader;

typedef _INSTHEADER TInstHeader;

typedef _DLSHEADER *PDLSHeader;

typedef _DLSHEADER TDLSHeader;

typedef _WAVELINK *PWaveLink;

typedef _WAVELINK TWaveLink;

typedef _POOLCUE *PPoolCUE;

typedef _POOLCUE TPoolCUE;

typedef _POOLTABLE *PPoolTable;

typedef _POOLTABLE TPoolTable;

typedef _rwsmp *PWSMPL;

typedef _rwsmp TWSMPL;

typedef _rloop *PWLoop;

typedef _rloop TWLoop;

typedef _DMUS_DOWNLOADINFO *PDMusDownloadInfo;

typedef _DMUS_DOWNLOADINFO TDMusDownloadInfo;

typedef _DMUS_OFFSETTABLE *PDMusOffsetTable;

typedef _DMUS_OFFSETTABLE TDMusOffsetTable;

typedef _DMUS_INSTRUMENT *PDMusInstrument;

typedef _DMUS_INSTRUMENT TDMusInstrument;

typedef _DMUS_REGION *PDMusRegion;

typedef _DMUS_REGION TDMusRegion;

typedef _DMUS_LFOPARAMS *PDMusLFOParams;

typedef _DMUS_LFOPARAMS TDMusLFOParams;

typedef _DMUS_VEGPARAMS *PDMusVEGParams;

typedef _DMUS_VEGPARAMS TDMusVEGParams;

typedef _DMUS_PEGPARAMS *PDMusPEGParams;

typedef _DMUS_PEGPARAMS TDMusPEGParams;

typedef _DMUS_MSCPARAMS *PDMusMSCParams;

typedef _DMUS_MSCPARAMS TDMusMSCParams;

typedef _DMUS_ARTICPARAMS *PDMusArticParams;

typedef _DMUS_ARTICPARAMS TDMusArticParams;

typedef _DMUS_ARTICULATION *PDMusArticulation;

typedef _DMUS_ARTICULATION TDMusArticulation;

typedef _DMUS_ARTICULATION2 *PDMusArticulation2;

typedef _DMUS_ARTICULATION2 TDMusArticulation2;

typedef _DMUS_EXTENSIONCHUNK *PDMusExtensionChunk;

typedef _DMUS_EXTENSIONCHUNK TDMusExtensionChunk;

typedef _DMUS_COPYRIGHT *PDMusCopyright;

typedef _DMUS_COPYRIGHT TDMusCopyright;

typedef _DMUS_WAVEDATA *PDMusWaveData;

typedef _DMUS_WAVEDATA TDMusWaveData;

typedef _DMUS_WAVE *PDMusWave;

typedef _DMUS_WAVE TDMusWave;

typedef _DMUS_NOTERANGE *PDMusNoteRange;

typedef _DMUS_NOTERANGE TDMusNoteRange;

typedef _DMUS_WAVEARTDL *PDMusWaveArtDL;

typedef _DMUS_WAVEARTDL TDMusWaveArtDL;

typedef _DMUS_WAVEDL *PDMusWaveDL;

typedef _DMUS_WAVEDL TDMusWaveDL;

typedef __int64 TSampleTime;

typedef __int64 *PSampleTime;

typedef __int64 TSamplePosition;

typedef __int64 *PSamplePosition;

typedef _DMUS_BUFFERDESC *PDMusBufferDesc;

typedef _DMUS_BUFFERDESC TDMusBufferDesc;

typedef _DMUS_PORTCAPS *PDMusPortCaps;

typedef _DMUS_PORTCAPS TDMusPortCaps;

typedef _DMUS_PORTPARAMS8 *PDMusPortParams8;

typedef _DMUS_PORTPARAMS8 TDMusPortParams8;

typedef _DMUS_PORTPARAMS8 TDMusPortParams;

typedef PDMusPortParams8 PDMusPortParams;

typedef _DMUS_SYNTHSTATS *PDMusSynthStats;

typedef _DMUS_SYNTHSTATS TDMusSynthStats;

typedef _DMUS_SYNTHSTATS8 *PDMusSynthStats8;

typedef _DMUS_SYNTHSTATS8 TDMusSynthStats8;

typedef _DMUS_WAVES_REVERB_PARAMS *PDMusWavesReverbParams;

typedef _DMUS_WAVES_REVERB_PARAMS TDMusWavesReverbParams;

typedef DMUS_CLOCKTYPE TDMusClockType;

typedef _DMUS_CLOCKINFO7 *PDMusClockInfo7;

typedef _DMUS_CLOCKINFO7 TDMusClockInfo7;

typedef _DMUS_CLOCKINFO8 *PDMusClockInfo8;

typedef _DMUS_CLOCKINFO8 TDMusClockInfo8;

typedef _DMUS_CLOCKINFO8 TDMusClockInfo;

typedef PDMusClockInfo8 PDMusClockInfo;

typedef _di_IReferenceClock *PIReferenceClock;

typedef _di_IDirectSound *PIDirectSound;

typedef _di_IDirectMusic *PIDirectMusic;

typedef int *PMusicTime;

typedef int TMusicTime;

typedef enumDMUS_STYLET_TYPES *PDMusStyletTypes;

typedef enumDMUS_STYLET_TYPES TDMusStyletTypes;

typedef enumDMUS_COMMANDT_TYPES TDMusCommandtTypes;

typedef enumDMUS_COMMANDT_TYPES *PDMusCommandtTypes;

typedef enumDMUS_SHAPET_TYPES *PDMusShapetTypes;

typedef enumDMUS_SHAPET_TYPES TDMusShapetTypes;

typedef unsigned TDMusComposefFlags;

typedef unsigned *PDMusComposefFlags;

typedef _DMUS_AUDIOPARAMS *PDMusAudioParams;

typedef _DMUS_AUDIOPARAMS TDMusAudioParams;

typedef unsigned TDMusPmsgfFlags;

typedef unsigned *PDMusPmsgfFlags;

typedef unsigned TDMusPmsgtTypes;

typedef unsigned *PDMusPmsgtTypes;

typedef unsigned enumDMUS_SEGF_FLAGS;

typedef unsigned TDMusSegfFlags;

typedef unsigned *PDMusSegfFlags;

typedef unsigned TDMusTimeResolveFlags;

typedef unsigned *PDMusTimeResolveFlags;

typedef unsigned TDMusChordkeyfFlags;

typedef unsigned *PDMusChordkeyfFlags;

typedef _DMUS_SUBCHORD *PDMusSubChord;

typedef _DMUS_SUBCHORD TDMusSubChord;

typedef _DMUS_CHORD_KEY *PDMusChordKey;

typedef _DMUS_CHORD_KEY TDMusChordKey;

typedef unsigned TDMusNotefFlags;

typedef unsigned *PDMusNotefFlags;

typedef System::Byte enumDMUS_PLAYMODE_FLAGS;

typedef System::Byte DMUS_PLAYMODE_FLAGS;

typedef _DMUS_VERSION *PDMusVersion;

typedef _DMUS_VERSION TDMusVersion;

typedef _DMUS_TIMESIGNATURE *PDMusTimeSignature;

typedef _DMUS_TIMESIGNATURE TDMusTimeSignature;

typedef _DMUS_VALID_START_PARAM *PDMusValidStartParam;

typedef _DMUS_VALID_START_PARAM TDMusValidStartParam;

typedef _DMUS_PLAY_MARKER_PARAM *PDMusPlayMarkerParam;

typedef _DMUS_PLAY_MARKER_PARAM TDMusPlayMarkerParam;

typedef _DMUS_OBJECTDESC *PDMusObjectDesc;

typedef _DMUS_OBJECTDESC TDMusObjectDesc;

typedef _DMUS_SCRIPT_ERRORINFO *PDMusScriptErrorInfo;

typedef _DMUS_SCRIPT_ERRORINFO TDMusScriptErrorInfo;

typedef _DMUS_COMMAND_PARAM *PDMusCommandParam;

typedef _DMUS_COMMAND_PARAM TDMusCommandParam;

typedef _DMUS_COMMAND_PARAM_2 *PDMusCommandParam2;

typedef _DMUS_COMMAND_PARAM_2 TDMusCommandParam2;

typedef _di_IDirectMusicSegmentState *PIDirectMusicSegmentState;

typedef _DMUS_PMSG *PDMusPMsg;

typedef _DMUS_PMSG TDMusPMsg;

typedef _DMUS_NOTE_PMSG *PDMusNotePMsg;

typedef _DMUS_NOTE_PMSG TDMusNotePMsg;

typedef _DMUS_MIDI_PMSG *PDMusMidiPMsg;

typedef _DMUS_MIDI_PMSG TDMusMidiPMsg;

typedef _DMUS_PATCH_PMSG *PDMusPatchPMsg;

typedef _DMUS_PATCH_PMSG TDMusPatchPMsg;

typedef _DMUS_TRANSPOSE_PMSG *PDMusTransposePMsg;

typedef _DMUS_TRANSPOSE_PMSG TDMusTransposePMsg;

typedef _DMUS_CHANNEL_PRIORITY_PMSG *PDMusChannelPriorityPMsg;

typedef _DMUS_CHANNEL_PRIORITY_PMSG TDMusChannelPriorityPMsg;

typedef _DMUS_TEMPO_PMSG *PDMusTempoPMsg;

typedef _DMUS_TEMPO_PMSG TDMusTempoPMsg;

typedef _DMUS_SYSEX_PMSG *PDMusSysexPMsg;

typedef _DMUS_SYSEX_PMSG TDMusSysexPMsg;

typedef _DMUS_CURVE_PMSG *PDMusCurvePMsg;

typedef _DMUS_CURVE_PMSG TDMusCurvePMsg;

typedef unsigned enumDMUS_CURVE_FLAGS;

typedef unsigned TDMusCurveFlags;

typedef unsigned *PDMusCurveFlags;

typedef _DMUS_TIMESIG_PMSG *PDMusTimeSigPMsg;

typedef _DMUS_TIMESIG_PMSG TDMusTimeSigPMsg;

typedef _DMUS_NOTIFICATION_PMSG *PDMusNotificationPMsg;

typedef _DMUS_NOTIFICATION_PMSG TDMusNotificationPMsg;

typedef _DMUS_WAVE_PMSG *PDMusWavePMsg;

typedef _DMUS_WAVE_PMSG TDMusWavePMsg;

typedef _DMUS_LYRIC_PMSG *PDMusLyricPMsg;

typedef _DMUS_LYRIC_PMSG TDMusLyricPMsg;

typedef _DMUS_BAND_PARAM TDMusBandParam;

typedef _DMUS_BAND_PARAM *PDMusBandParam;

typedef _DMUS_VARIATIONS_PARAM *PDMusVariationsParam;

typedef _DMUS_VARIATIONS_PARAM TDMusVariationsParam;

typedef _DMUS_IO_SEQ_ITEM *PDMusIoSeqItem;

typedef _DMUS_IO_SEQ_ITEM TDMusIoSeqItem;

typedef _DMUS_IO_CURVE_ITEM *PDMusIoCurveItem;

typedef _DMUS_IO_CURVE_ITEM TDMusIoCurveItem;

typedef _DMUS_IO_TEMPO_ITEM *PDMusIoTempoItem;

typedef _DMUS_IO_TEMPO_ITEM TDMusIoTempoItem;

typedef _DMUS_IO_SYSEX_ITEM *PDMusIoSysExItem;

typedef _DMUS_IO_SYSEX_ITEM TDMusIoSysExItem;

typedef _DMUS_CHORD_KEY TDMusChordParam;

typedef _DMUS_CHORD_KEY *PDMusChordParam;

typedef _DMUS_RHYTHM_PARAM TDMusRhythmParam;

typedef _DMUS_RHYTHM_PARAM *PDMusRhythmParam;

typedef _DMUS_TEMPO_PARAM *PDMusTempoParam;

typedef _DMUS_TEMPO_PARAM TDMusTempoParam;

typedef _DMUS_MUTE_PARAM *PDMusMuteParam;

typedef _DMUS_MUTE_PARAM TDMusMuteParam;

typedef System::Word enumDMUS_EMBELLISHT_TYPES;

typedef System::Word TDMusEmbellishtTypes;

typedef enumDMUS_VARIATIONT_TYPES TDMusVariationtTypes;

typedef enumDMUS_VARIATIONT_TYPES *PDMusVariationtTypes;

typedef _DMUS_IO_TIMESIG *PDMusIoTimesig;

typedef _DMUS_IO_TIMESIG TDMusIoTimesig;

typedef _DMUS_IO_STYLE *PDMusIoStyle;

typedef _DMUS_IO_STYLE TDMusIoStyle;

typedef _DMUS_IO_VERSION *PDMusIoVersion;

typedef _DMUS_IO_VERSION TDMusIoVersion;

typedef _DMUS_IO_PATTERN *PDMusIoPattern;

typedef _DMUS_IO_PATTERN TDMusIoPattern;

typedef _DMUS_IO_STYLEPART *PDMusIoStylePart;

typedef _DMUS_IO_STYLEPART TDMusIoStylePart;

typedef _DMUS_IO_PARTREF *PDMusIoPartRef;

typedef _DMUS_IO_PARTREF TDMusIoPartRef;

typedef _DMUS_IO_STYLENOTE *PDMusIoStyleNote;

typedef _DMUS_IO_STYLENOTE TDMusIoStyleNote;

typedef _DMUS_IO_STYLECURVE *PDMusIoStyleCurve;

typedef _DMUS_IO_STYLECURVE TDMusIoStyleCurve;

typedef _DMUS_IO_STYLEMARKER *PDMusIoStyleMarker;

typedef _DMUS_IO_STYLEMARKER TDMusIoStyleMarker;

typedef _DMUS_IO_STYLERESOLUTION *PDMusIoStyleResolution;

typedef _DMUS_IO_STYLERESOLUTION TDMusIoStyleResolution;

typedef _DMUS_IO_STYLE_ANTICIPATION *PDMusIoStyleAnticipation;

typedef _DMUS_IO_STYLE_ANTICIPATION TDMusIoStyleAnticipation;

typedef _DMUS_IO_MOTIFSETTINGS *PDMusIoMotifSettings;

typedef _DMUS_IO_MOTIFSETTINGS TDMusIoMotifSettings;

typedef enumDMUS_PATTERNT_TYPES TDMusPatterntTypes;

typedef _DMUS_IO_CHORD *PDMusIoChord;

typedef _DMUS_IO_CHORD TDMusIoChord;

typedef _DMUS_IO_SUBCHORD *PDMusIoSubChord;

typedef _DMUS_IO_SUBCHORD TDMusIoSubChord;

typedef _DMUS_IO_COMMAND *PDMusIoCommand;

typedef _DMUS_IO_COMMAND TDMusIoCommand;

typedef _DMUS_IO_TOOL_HEADER *PDMusIoToolHeader;

typedef _DMUS_IO_TOOL_HEADER TDMusIoToolHeader;

typedef _DMUS_IO_PORTCONFIG_HEADER *PDMusIoPortConfigHeader;

typedef _DMUS_IO_PORTCONFIG_HEADER TDMusIoPortConfigHeader;

typedef _DMUS_IO_PCHANNELTOBUFFER_HEADER *PDMusIoPChannelToBufferHeader;

typedef _DMUS_IO_PCHANNELTOBUFFER_HEADER TDMusIoPChannelToBufferHeader;

typedef _DMUS_IO_BUFFER_ATTRIBUTES_HEADER *PDMusIoBufferAttributesHeader;

typedef _DMUS_IO_BUFFER_ATTRIBUTES_HEADER TDMusIoBufferAttributesHeader;

typedef _DMUS_IO_BAND_TRACK_HEADER *PDMusIoBandTrackHeader;

typedef _DMUS_IO_BAND_TRACK_HEADER TDMusIoBandTrackHeader;

typedef _DMUS_IO_BAND_ITEM_HEADER *PDMusIoBandItemHeader;

typedef _DMUS_IO_BAND_ITEM_HEADER TDMusIoBandItemHeader;

typedef _DMUS_IO_BAND_ITEM_HEADER2 *PDMusIoBandItemHeader2;

typedef _DMUS_IO_BAND_ITEM_HEADER2 TDMusIoBandItemHeader2;

typedef _DMUS_IO_INSTRUMENT *PDMusIoInstrument;

typedef _DMUS_IO_INSTRUMENT TDMusIoInstrument;

typedef _DMUS_IO_WAVE_HEADER *PDMusIoWaveHeader;

typedef _DMUS_IO_WAVE_HEADER TDMusIoWaveHeader;

typedef _DMUS_IO_WAVE_TRACK_HEADER *PDMusIoWaveTrackHeader;

typedef _DMUS_IO_WAVE_TRACK_HEADER TDMusIoWaveTrackHeader;

typedef _DMUS_IO_WAVE_PART_HEADER *PDMusIoWavePartHeader;

typedef _DMUS_IO_WAVE_PART_HEADER TDMusIoWavePartHeader;

typedef _DMUS_IO_WAVE_ITEM_HEADER *PDMusIoWaveItemHeader;

typedef _DMUS_IO_WAVE_ITEM_HEADER TDMusIoWaveItemHeader;

typedef _DMUS_IO_CONTAINER_HEADER *PDMusIoContainerHeader;

typedef _DMUS_IO_CONTAINER_HEADER TDMusIoContainerHeader;

typedef _DMUS_IO_CONTAINED_OBJECT_HEADER *PDMusIoContainedObjectHeader;

typedef _DMUS_IO_CONTAINED_OBJECT_HEADER TDMusIoContainedObjectHeader;

typedef _DMUS_IO_SEGMENT_HEADER *PDMusIoSegmentHeader;

typedef _DMUS_IO_SEGMENT_HEADER TDMusIoSegmentHeader;

typedef _DMUS_IO_TRACK_HEADER *PDMusIoTrackHeader;

typedef _DMUS_IO_TRACK_HEADER TDMusIoTrackHeader;

typedef _DMUS_IO_TRACK_EXTRAS_HEADER *PDMusIoTrackExtrasHeader;

typedef _DMUS_IO_TRACK_EXTRAS_HEADER TDMusIoTrackExtrasHeader;

typedef _DMUS_IO_REFERENCE *PDMusIoReference;

typedef _DMUS_IO_REFERENCE TDMusIoReference;

typedef _DMUS_IO_CHORDMAP *PDMusIoChordMap;

typedef _DMUS_IO_CHORDMAP TDMusIoChordMap;

typedef _DMUS_IO_CHORDMAP_SUBCHORD *PDMusIoChordmapSubChord;

typedef _DMUS_IO_CHORDMAP_SUBCHORD TDMusIoChordmapSubChord;

typedef _DMUS_IO_CHORDENTRY *PDMusIoChordEntry;

typedef _DMUS_IO_CHORDENTRY TDMusIoChordEntry;

typedef _DMUS_IO_NEXTCHORD *PDMusIoNextChord;

typedef _DMUS_IO_NEXTCHORD TDMusIoNextChord;

typedef _DMUS_IO_CHORDMAP_SIGNPOST *PDMusIoChordMapSignPost;

typedef _DMUS_IO_CHORDMAP_SIGNPOST TDMusIoChordMapSignPost;

typedef _DMUS_IO_SCRIPT_HEADER *PDMusIoScriptHeader;

typedef _DMUS_IO_SCRIPT_HEADER TDMusIoScriptHeader;

typedef _DMUS_IO_SIGNPOST *PDMusIoSignPost;

typedef _DMUS_IO_SIGNPOST TDMusIoSignPost;

typedef _DMUS_IO_MUTE *PDMusIoMute;

typedef _DMUS_IO_MUTE TDMusIoMute;

typedef _DMUS_IO_TIMESIGNATURE_ITEM *PDMusIoTimeSignatureItem;

typedef _DMUS_IO_TIMESIGNATURE_ITEM TDMusIoTimeSignatureItem;

typedef _DMUS_IO_VALID_START *PDMusIoValidStart;

typedef _DMUS_IO_VALID_START TDMusIoValidStart;

typedef _DMUS_IO_PLAY_MARKER *PDMusIoPlayMarker;

typedef _DMUS_IO_PLAY_MARKER TDMusIoPlayMarker;

typedef _DMUS_IO_SEGMENT_TRACK_HEADER *PDMusIoSegmentTrackHeader;

typedef _DMUS_IO_SEGMENT_TRACK_HEADER TDMusIoSegmentTrackHeader;

typedef _DMUS_IO_SEGMENT_ITEM_HEADER *PDMusIoSegmentItemHeader;

typedef _DMUS_IO_SEGMENT_ITEM_HEADER TDMusIoSegmentItemHeader;

typedef _DMUS_IO_SCRIPTTRACK_EVENTHEADER *PDMusIoScriptTrackEventHeader;

typedef _DMUS_IO_SCRIPTTRACK_EVENTHEADER TDMusIoScriptTrackEventHeader;

typedef _DMUS_IO_LYRICSTRACK_EVENTHEADER *PDMusIoLyricsTrackEventHeader;

typedef _DMUS_IO_LYRICSTRACK_EVENTHEADER TDMusIoLyricsTrackEventHeader;

typedef _DMUS_IO_PARAMCONTROLTRACK_OBJECTHEADER *PDMusIoParamControlTrackObjectHeader;

typedef _DMUS_IO_PARAMCONTROLTRACK_OBJECTHEADER TDMusIoParamControlTrackObjectHeader;

typedef _DMUS_IO_PARAMCONTROLTRACK_PARAMHEADER *PDMusIoParamControlTrackParamHeader;

typedef _DMUS_IO_PARAMCONTROLTRACK_PARAMHEADER TDMusIoParamControlTrackParamHeader;

typedef _DMUS_IO_PARAMCONTROLTRACK_CURVEINFO *PDMusIoParamControlTrackCurveInfo;

typedef _DMUS_IO_PARAMCONTROLTRACK_CURVEINFO TDMusIoParamControlTrackCurveInfo;

typedef _DSOUND_IO_DSBUFFERDESC *PDSoundIoDSBufferDesc;

typedef _DSOUND_IO_DSBUFFERDESC TDSoundIoDSBufferDesc;

typedef _DSOUND_IO_DSBUSID *PDSoundIoDSBusID;

typedef _DSOUND_IO_DSBUSID TDSoundIoDSBusID;

typedef _DSOUND_IO_3D *PDSoundIo3D;

typedef _DSOUND_IO_3D TDSoundIo3D;

typedef _DSOUND_IO_DXDMO_HEADER *PDSoundIoDXDMOHeader;

typedef _DSOUND_IO_DXDMO_HEADER TDSoundIoDXDMOHeader;

typedef _DSOUND_IO_DXDMO_DATA *PDSoundIoDXDMOData;

typedef _DSOUND_IO_DXDMO_DATA TDSoundIoDXDMOData;

typedef _DMUS_EVENTHEADER *PDMusEventHeader;

typedef _DMUS_EVENTHEADER TDMusEventHeader;

typedef unsigned enumDMUS_TRACKF_FLAGS;

typedef unsigned TDMusTrackfFlags;

typedef unsigned *PDMusTrackfFlags;

//-- var, const, procedure ---------------------------------------------------
static const int MAKE_DMHRESULTSUCCESS_R = int(0x8781000);
static const int MAKE_DMHRESULTERROR_R = int(-2005397504);
}	/* namespace Directmusic */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_DIRECTMUSIC)
using namespace Winapi::Directmusic;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_DirectmusicHPP
