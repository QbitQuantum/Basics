// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.CoreAudio.pas' rev: 34.00 (iOS)

#ifndef Iosapi_CoreaudioHPP
#define Iosapi_CoreaudioHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.CoreServices.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Coreaudio
{
//-- forward type declarations -----------------------------------------------
struct AudioBuffer;
struct AudioBufferList;
struct AudioStreamBasicDescription;
struct AudioStreamPacketDescription;
struct AudioChannelDescription;
struct AudioChannelLayout;
struct AudioClassDescription;
struct SMPTETime;
struct AudioTimeStamp;
//-- type declarations -------------------------------------------------------
typedef unsigned AudioChannelLabel;

typedef unsigned AudioChannelLayoutTag;

struct DECLSPEC_DRECORD AudioBuffer
{
public:
	unsigned mNumberChannels;
	unsigned mDataByteSize;
	void *mData;
};


typedef AudioBuffer *PAudioBuffer;

struct DECLSPEC_DRECORD AudioBufferList
{
public:
	unsigned mNumberBuffers;
	System::StaticArray<AudioBuffer, 1> mBuffers;
};


typedef AudioBufferList *PAudioBufferList;

struct DECLSPEC_DRECORD AudioStreamBasicDescription
{
public:
	double mSampleRate;
	unsigned mFormatID;
	unsigned mFormatFlags;
	unsigned mBytesPerPacket;
	unsigned mFramesPerPacket;
	unsigned mBytesPerFrame;
	unsigned mChannelsPerFrame;
	unsigned mBitsPerChannel;
	unsigned mReserved;
};


typedef AudioStreamBasicDescription *PAudioStreamBasicDescription;

struct DECLSPEC_DRECORD AudioStreamPacketDescription
{
public:
	__int64 mStartOffset;
	unsigned mVariableFramesInPackets;
	unsigned mDataByteSize;
};


typedef AudioStreamPacketDescription *PAudioStreamPacketDescription;

typedef System::StaticArray<float, 3> TAudioChannelCoordinatesArray;

struct DECLSPEC_DRECORD AudioChannelDescription
{
public:
	unsigned mChannelLabel;
	unsigned mChannelFlags;
	TAudioChannelCoordinatesArray mCoordinates;
};


typedef AudioChannelDescription *PAudioChannelDescription;

struct DECLSPEC_DRECORD AudioChannelLayout
{
public:
	unsigned mChannelLayoutTag;
	unsigned mChannelBitmap;
	unsigned mNumberChannelDescriptions;
	AudioChannelDescription mChannelDescriptions;
};


typedef AudioChannelLayout *PAudioChannelLayout;

struct DECLSPEC_DRECORD AudioClassDescription
{
public:
	FourCharCode mType;
	FourCharCode mSubType;
	FourCharCode mManufacturer;
};


typedef AudioClassDescription *PAudioClassDescription;

struct DECLSPEC_DRECORD SMPTETime
{
public:
	short mSubframes;
	short mSubframeDivisor;
	unsigned mCounter;
	unsigned mType;
	unsigned mFlags;
	short mHours;
	short mMinutes;
	short mSeconds;
	short mFrames;
};


struct DECLSPEC_DRECORD AudioTimeStamp
{
public:
	double mSampleTime;
	unsigned __int64 mHostTime;
	double mRateScalar;
	unsigned __int64 mWordClockTime;
	SMPTETime mSMPTETime;
	unsigned mFlags;
	unsigned mReserved;
};


typedef AudioTimeStamp *PAudioTimeStamp;

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 CA_PREFER_FIXED_POINT = System::Int8(0x0);
static constexpr System::Word COREAUDIOTYPES_VERSION = System::Word(0x41b);
static constexpr System::Int8 kAppleLosslessFormatFlag_16BitSourceData = System::Int8(0x1);
static constexpr System::Int8 kAppleLosslessFormatFlag_20BitSourceData = System::Int8(0x2);
static constexpr System::Int8 kAppleLosslessFormatFlag_24BitSourceData = System::Int8(0x3);
static constexpr System::Int8 kAppleLosslessFormatFlag_32BitSourceData = System::Int8(0x4);
static constexpr System::Int8 kAudioChannelBit_Center = System::Int8(0x4);
static constexpr System::Word kAudioChannelBit_CenterSurround = System::Word(0x100);
static constexpr System::Int8 kAudioChannelBit_LFEScreen = System::Int8(0x8);
static constexpr System::Int8 kAudioChannelBit_Left = System::Int8(0x1);
static constexpr System::Int8 kAudioChannelBit_LeftCenter = System::Int8(0x40);
static constexpr System::Int8 kAudioChannelBit_LeftSurround = System::Int8(0x10);
static constexpr System::Word kAudioChannelBit_LeftSurroundDirect = System::Word(0x200);
static constexpr System::Int8 kAudioChannelBit_Right = System::Int8(0x2);
static constexpr System::Byte kAudioChannelBit_RightCenter = System::Byte(0x80);
static constexpr System::Int8 kAudioChannelBit_RightSurround = System::Int8(0x20);
static constexpr System::Word kAudioChannelBit_RightSurroundDirect = System::Word(0x400);
static constexpr int kAudioChannelBit_TopBackCenter = int(0x10000);
static constexpr System::Word kAudioChannelBit_TopBackLeft = System::Word(0x8000);
static constexpr int kAudioChannelBit_TopBackRight = int(0x20000);
static constexpr System::Word kAudioChannelBit_TopCenterSurround = System::Word(0x800);
static constexpr System::Word kAudioChannelBit_VerticalHeightCenter = System::Word(0x2000);
static constexpr System::Word kAudioChannelBit_VerticalHeightLeft = System::Word(0x1000);
static constexpr System::Word kAudioChannelBit_VerticalHeightRight = System::Word(0x4000);
static constexpr System::Int8 kAudioChannelCoordinates_Azimuth = System::Int8(0x0);
static constexpr System::Int8 kAudioChannelCoordinates_BackFront = System::Int8(0x1);
static constexpr System::Int8 kAudioChannelCoordinates_Distance = System::Int8(0x2);
static constexpr System::Int8 kAudioChannelCoordinates_DownUp = System::Int8(0x2);
static constexpr System::Int8 kAudioChannelCoordinates_Elevation = System::Int8(0x1);
static constexpr System::Int8 kAudioChannelCoordinates_LeftRight = System::Int8(0x0);
static constexpr System::Int8 kAudioChannelFlags_AllOff = System::Int8(0x0);
static constexpr System::Int8 kAudioChannelFlags_Meters = System::Int8(0x4);
static constexpr System::Int8 kAudioChannelFlags_RectangularCoordinates = System::Int8(0x1);
static constexpr System::Int8 kAudioChannelFlags_SphericalCoordinates = System::Int8(0x2);
static constexpr System::Byte kAudioChannelLabel_Ambisonic_W = System::Byte(0xc8);
static constexpr System::Byte kAudioChannelLabel_Ambisonic_X = System::Byte(0xc9);
static constexpr System::Byte kAudioChannelLabel_Ambisonic_Y = System::Byte(0xca);
static constexpr System::Byte kAudioChannelLabel_Ambisonic_Z = System::Byte(0xcb);
static constexpr System::Int8 kAudioChannelLabel_Center = System::Int8(0x3);
static constexpr System::Int8 kAudioChannelLabel_CenterSurround = System::Int8(0x9);
static constexpr System::Int8 kAudioChannelLabel_CenterSurroundDirect = System::Int8(0x2c);
static constexpr System::Word kAudioChannelLabel_ClickTrack = System::Word(0x130);
static constexpr System::Int8 kAudioChannelLabel_DialogCentricMix = System::Int8(0x2b);
static constexpr System::Word kAudioChannelLabel_Discrete = System::Word(0x190);
static constexpr int kAudioChannelLabel_Discrete_0 = int(0x10000);
static constexpr int kAudioChannelLabel_Discrete_1 = int(0x10001);
static constexpr int kAudioChannelLabel_Discrete_10 = int(0x1000a);
static constexpr int kAudioChannelLabel_Discrete_11 = int(0x1000b);
static constexpr int kAudioChannelLabel_Discrete_12 = int(0x1000c);
static constexpr int kAudioChannelLabel_Discrete_13 = int(0x1000d);
static constexpr int kAudioChannelLabel_Discrete_14 = int(0x1000e);
static constexpr int kAudioChannelLabel_Discrete_15 = int(0x1000f);
static constexpr int kAudioChannelLabel_Discrete_2 = int(0x10002);
static constexpr int kAudioChannelLabel_Discrete_3 = int(0x10003);
static constexpr int kAudioChannelLabel_Discrete_4 = int(0x10004);
static constexpr int kAudioChannelLabel_Discrete_5 = int(0x10005);
static constexpr int kAudioChannelLabel_Discrete_6 = int(0x10006);
static constexpr int kAudioChannelLabel_Discrete_65535 = int(0x1ffff);
static constexpr int kAudioChannelLabel_Discrete_7 = int(0x10007);
static constexpr int kAudioChannelLabel_Discrete_8 = int(0x10008);
static constexpr int kAudioChannelLabel_Discrete_9 = int(0x10009);
static constexpr System::Word kAudioChannelLabel_ForeignLanguage = System::Word(0x131);
static constexpr System::Int8 kAudioChannelLabel_Haptic = System::Int8(0x2d);
static constexpr System::Word kAudioChannelLabel_HeadphonesLeft = System::Word(0x12d);
static constexpr System::Word kAudioChannelLabel_HeadphonesRight = System::Word(0x12e);
static constexpr System::Int8 kAudioChannelLabel_HearingImpaired = System::Int8(0x28);
static constexpr System::Int8 kAudioChannelLabel_LFE2 = System::Int8(0x25);
static constexpr System::Int8 kAudioChannelLabel_LFEScreen = System::Int8(0x4);
static constexpr System::Int8 kAudioChannelLabel_Left = System::Int8(0x1);
static constexpr System::Int8 kAudioChannelLabel_LeftCenter = System::Int8(0x7);
static constexpr System::Int8 kAudioChannelLabel_LeftSurround = System::Int8(0x5);
static constexpr System::Int8 kAudioChannelLabel_LeftSurroundDirect = System::Int8(0xa);
static constexpr System::Int8 kAudioChannelLabel_LeftTotal = System::Int8(0x26);
static constexpr System::Int8 kAudioChannelLabel_LeftWide = System::Int8(0x23);
static constexpr System::Byte kAudioChannelLabel_MS_Mid = System::Byte(0xcc);
static constexpr System::Byte kAudioChannelLabel_MS_Side = System::Byte(0xcd);
static constexpr System::Int8 kAudioChannelLabel_Mono = System::Int8(0x2a);
static constexpr System::Int8 kAudioChannelLabel_Narration = System::Int8(0x29);
static constexpr System::Int8 kAudioChannelLabel_RearSurroundLeft = System::Int8(0x21);
static constexpr System::Int8 kAudioChannelLabel_RearSurroundRight = System::Int8(0x22);
static constexpr System::Int8 kAudioChannelLabel_Right = System::Int8(0x2);
static constexpr System::Int8 kAudioChannelLabel_RightCenter = System::Int8(0x8);
static constexpr System::Int8 kAudioChannelLabel_RightSurround = System::Int8(0x6);
static constexpr System::Int8 kAudioChannelLabel_RightSurroundDirect = System::Int8(0xb);
static constexpr System::Int8 kAudioChannelLabel_RightTotal = System::Int8(0x27);
static constexpr System::Int8 kAudioChannelLabel_RightWide = System::Int8(0x24);
static constexpr System::Int8 kAudioChannelLabel_TopBackCenter = System::Int8(0x11);
static constexpr System::Int8 kAudioChannelLabel_TopBackLeft = System::Int8(0x10);
static constexpr System::Int8 kAudioChannelLabel_TopBackRight = System::Int8(0x12);
static constexpr System::Int8 kAudioChannelLabel_TopCenterSurround = System::Int8(0xc);
static constexpr unsigned kAudioChannelLabel_Unknown = unsigned(0xffffffff);
static constexpr System::Int8 kAudioChannelLabel_Unused = System::Int8(0x0);
static constexpr System::Int8 kAudioChannelLabel_UseCoordinates = System::Int8(0x64);
static constexpr System::Int8 kAudioChannelLabel_VerticalHeightCenter = System::Int8(0xe);
static constexpr System::Int8 kAudioChannelLabel_VerticalHeightLeft = System::Int8(0xd);
static constexpr System::Int8 kAudioChannelLabel_VerticalHeightRight = System::Int8(0xf);
static constexpr System::Byte kAudioChannelLabel_XY_X = System::Byte(0xce);
static constexpr System::Byte kAudioChannelLabel_XY_Y = System::Byte(0xcf);
static constexpr int kAudioChannelLayoutTag_AAC_3_0 = int(0x720003);
static constexpr int kAudioChannelLayoutTag_AAC_4_0 = int(0x740004);
static constexpr int kAudioChannelLayoutTag_AAC_5_0 = int(0x780005);
static constexpr int kAudioChannelLayoutTag_AAC_5_1 = int(0x7c0006);
static constexpr int kAudioChannelLayoutTag_AAC_6_0 = int(0x8d0006);
static constexpr int kAudioChannelLayoutTag_AAC_6_1 = int(0x8e0007);
static constexpr int kAudioChannelLayoutTag_AAC_7_0 = int(0x8f0007);
static constexpr int kAudioChannelLayoutTag_AAC_7_1 = int(0x7f0008);
static constexpr int kAudioChannelLayoutTag_AAC_Octagonal = int(0x900008);
static constexpr int kAudioChannelLayoutTag_AAC_Quadraphonic = int(0x6c0004);
static constexpr int kAudioChannelLayoutTag_AC3_1_0_1 = int(0x950002);
static constexpr int kAudioChannelLayoutTag_AC3_2_1_1 = int(0x990004);
static constexpr int kAudioChannelLayoutTag_AC3_3_0 = int(0x960003);
static constexpr int kAudioChannelLayoutTag_AC3_3_0_1 = int(0x980004);
static constexpr int kAudioChannelLayoutTag_AC3_3_1 = int(0x970004);
static constexpr int kAudioChannelLayoutTag_AC3_3_1_1 = int(0x9a0005);
static constexpr int kAudioChannelLayoutTag_Ambisonic_B_Format = int(0x6b0004);
static constexpr int kAudioChannelLayoutTag_AudioUnit_4 = int(0x6c0004);
static constexpr int kAudioChannelLayoutTag_AudioUnit_5 = int(0x6d0005);
static constexpr int kAudioChannelLayoutTag_AudioUnit_5_0 = int(0x760005);
static constexpr int kAudioChannelLayoutTag_AudioUnit_5_1 = int(0x790006);
static constexpr int kAudioChannelLayoutTag_AudioUnit_6 = int(0x6e0006);
static constexpr int kAudioChannelLayoutTag_AudioUnit_6_0 = int(0x8b0006);
static constexpr int kAudioChannelLayoutTag_AudioUnit_6_1 = int(0x7d0007);
static constexpr int kAudioChannelLayoutTag_AudioUnit_7_0 = int(0x8c0007);
static constexpr int kAudioChannelLayoutTag_AudioUnit_7_0_Front = int(0x940007);
static constexpr int kAudioChannelLayoutTag_AudioUnit_7_1 = int(0x800008);
static constexpr int kAudioChannelLayoutTag_AudioUnit_7_1_Front = int(0x7e0008);
static constexpr int kAudioChannelLayoutTag_AudioUnit_8 = int(0x6f0008);
static constexpr int kAudioChannelLayoutTag_Binaural = int(0x6a0002);
static constexpr int kAudioChannelLayoutTag_Cube = int(0x700008);
static constexpr int kAudioChannelLayoutTag_DTS_3_1 = int(0xa80004);
static constexpr int kAudioChannelLayoutTag_DTS_4_1 = int(0xa90005);
static constexpr int kAudioChannelLayoutTag_DTS_6_0_A = int(0xaa0006);
static constexpr int kAudioChannelLayoutTag_DTS_6_0_B = int(0xab0006);
static constexpr int kAudioChannelLayoutTag_DTS_6_0_C = int(0xac0006);
static constexpr int kAudioChannelLayoutTag_DTS_6_1_A = int(0xad0007);
static constexpr int kAudioChannelLayoutTag_DTS_6_1_B = int(0xae0007);
static constexpr int kAudioChannelLayoutTag_DTS_6_1_C = int(0xaf0007);
static constexpr int kAudioChannelLayoutTag_DTS_6_1_D = int(0xb60007);
static constexpr int kAudioChannelLayoutTag_DTS_7_0 = int(0xb00007);
static constexpr int kAudioChannelLayoutTag_DTS_7_1 = int(0xb10008);
static constexpr int kAudioChannelLayoutTag_DTS_8_0_A = int(0xb20008);
static constexpr int kAudioChannelLayoutTag_DTS_8_0_B = int(0xb30008);
static constexpr int kAudioChannelLayoutTag_DTS_8_1_A = int(0xb40009);
static constexpr int kAudioChannelLayoutTag_DTS_8_1_B = int(0xb50009);
static constexpr int kAudioChannelLayoutTag_DVD_0 = int(0x640001);
static constexpr int kAudioChannelLayoutTag_DVD_1 = int(0x650002);
static constexpr int kAudioChannelLayoutTag_DVD_10 = int(0x880004);
static constexpr int kAudioChannelLayoutTag_DVD_11 = int(0x890005);
static constexpr int kAudioChannelLayoutTag_DVD_12 = int(0x790006);
static constexpr int kAudioChannelLayoutTag_DVD_13 = int(0x730004);
static constexpr int kAudioChannelLayoutTag_DVD_14 = int(0x750005);
static constexpr int kAudioChannelLayoutTag_DVD_15 = int(0x880004);
static constexpr int kAudioChannelLayoutTag_DVD_16 = int(0x890005);
static constexpr int kAudioChannelLayoutTag_DVD_17 = int(0x790006);
static constexpr int kAudioChannelLayoutTag_DVD_18 = int(0x8a0005);
static constexpr int kAudioChannelLayoutTag_DVD_19 = int(0x760005);
static constexpr int kAudioChannelLayoutTag_DVD_2 = int(0x830003);
static constexpr int kAudioChannelLayoutTag_DVD_20 = int(0x7a0006);
static constexpr int kAudioChannelLayoutTag_DVD_3 = int(0x840004);
static constexpr int kAudioChannelLayoutTag_DVD_4 = int(0x850003);
static constexpr int kAudioChannelLayoutTag_DVD_5 = int(0x860004);
static constexpr int kAudioChannelLayoutTag_DVD_6 = int(0x870005);
static constexpr int kAudioChannelLayoutTag_DVD_7 = int(0x710003);
static constexpr int kAudioChannelLayoutTag_DVD_8 = int(0x730004);
static constexpr int kAudioChannelLayoutTag_DVD_9 = int(0x750005);
static constexpr int kAudioChannelLayoutTag_DiscreteInOrder = int(0x930000);
static constexpr int kAudioChannelLayoutTag_EAC3_6_1_A = int(0x9d0007);
static constexpr int kAudioChannelLayoutTag_EAC3_6_1_B = int(0x9e0007);
static constexpr int kAudioChannelLayoutTag_EAC3_6_1_C = int(0x9f0007);
static constexpr int kAudioChannelLayoutTag_EAC3_7_1_A = int(0xa00008);
static constexpr int kAudioChannelLayoutTag_EAC3_7_1_B = int(0xa10008);
static constexpr int kAudioChannelLayoutTag_EAC3_7_1_C = int(0xa20008);
static constexpr int kAudioChannelLayoutTag_EAC3_7_1_D = int(0xa30008);
static constexpr int kAudioChannelLayoutTag_EAC3_7_1_E = int(0xa40008);
static constexpr int kAudioChannelLayoutTag_EAC3_7_1_F = int(0xa50008);
static constexpr int kAudioChannelLayoutTag_EAC3_7_1_G = int(0xa60008);
static constexpr int kAudioChannelLayoutTag_EAC3_7_1_H = int(0xa70008);
static constexpr int kAudioChannelLayoutTag_EAC_6_0_A = int(0x9b0006);
static constexpr int kAudioChannelLayoutTag_EAC_7_0_A = int(0x9c0007);
static constexpr int kAudioChannelLayoutTag_Emagic_Default_7_1 = int(0x810008);
static constexpr int kAudioChannelLayoutTag_Hexagonal = int(0x6e0006);
static constexpr int kAudioChannelLayoutTag_ITU_1_0 = int(0x640001);
static constexpr int kAudioChannelLayoutTag_ITU_2_0 = int(0x650002);
static constexpr int kAudioChannelLayoutTag_ITU_2_1 = int(0x830003);
static constexpr int kAudioChannelLayoutTag_ITU_2_2 = int(0x840004);
static constexpr int kAudioChannelLayoutTag_ITU_3_0 = int(0x710003);
static constexpr int kAudioChannelLayoutTag_ITU_3_1 = int(0x730004);
static constexpr int kAudioChannelLayoutTag_ITU_3_2 = int(0x750005);
static constexpr int kAudioChannelLayoutTag_ITU_3_2_1 = int(0x790006);
static constexpr int kAudioChannelLayoutTag_ITU_3_4_1 = int(0x800008);
static constexpr int kAudioChannelLayoutTag_MPEG_1_0 = int(0x640001);
static constexpr int kAudioChannelLayoutTag_MPEG_2_0 = int(0x650002);
static constexpr int kAudioChannelLayoutTag_MPEG_3_0_A = int(0x710003);
static constexpr int kAudioChannelLayoutTag_MPEG_3_0_B = int(0x720003);
static constexpr int kAudioChannelLayoutTag_MPEG_4_0_A = int(0x730004);
static constexpr int kAudioChannelLayoutTag_MPEG_4_0_B = int(0x740004);
static constexpr int kAudioChannelLayoutTag_MPEG_5_0_A = int(0x750005);
static constexpr int kAudioChannelLayoutTag_MPEG_5_0_B = int(0x760005);
static constexpr int kAudioChannelLayoutTag_MPEG_5_0_C = int(0x770005);
static constexpr int kAudioChannelLayoutTag_MPEG_5_0_D = int(0x780005);
static constexpr int kAudioChannelLayoutTag_MPEG_5_1_A = int(0x790006);
static constexpr int kAudioChannelLayoutTag_MPEG_5_1_B = int(0x7a0006);
static constexpr int kAudioChannelLayoutTag_MPEG_5_1_C = int(0x7b0006);
static constexpr int kAudioChannelLayoutTag_MPEG_5_1_D = int(0x7c0006);
static constexpr int kAudioChannelLayoutTag_MPEG_6_1_A = int(0x7d0007);
static constexpr int kAudioChannelLayoutTag_MPEG_7_1_A = int(0x7e0008);
static constexpr int kAudioChannelLayoutTag_MPEG_7_1_B = int(0x7f0008);
static constexpr int kAudioChannelLayoutTag_MPEG_7_1_C = int(0x800008);
static constexpr int kAudioChannelLayoutTag_MatrixStereo = int(0x670002);
static constexpr int kAudioChannelLayoutTag_MidSide = int(0x680002);
static constexpr int kAudioChannelLayoutTag_Mono = int(0x640001);
static constexpr int kAudioChannelLayoutTag_Octagonal = int(0x6f0008);
static constexpr int kAudioChannelLayoutTag_Pentagonal = int(0x6d0005);
static constexpr int kAudioChannelLayoutTag_Quadraphonic = int(0x6c0004);
static constexpr int kAudioChannelLayoutTag_SMPTE_DTV = int(0x820008);
static constexpr int kAudioChannelLayoutTag_Stereo = int(0x650002);
static constexpr int kAudioChannelLayoutTag_StereoHeadphones = int(0x660002);
static constexpr int kAudioChannelLayoutTag_TMH_10_2_full = int(0x920015);
static constexpr int kAudioChannelLayoutTag_TMH_10_2_std = int(0x910010);
static constexpr unsigned kAudioChannelLayoutTag_Unknown = unsigned(0xffff0000);
static constexpr int kAudioChannelLayoutTag_UseChannelBitmap = int(0x10000);
static constexpr System::Int8 kAudioChannelLayoutTag_UseChannelDescriptions = System::Int8(0x0);
static constexpr int kAudioChannelLayoutTag_XY = int(0x690002);
static constexpr int kAudioFormat60958AC3 = int(0x63616333);
static constexpr int kAudioFormatAC3 = int(0x61632d33);
static constexpr int kAudioFormatAES3 = int(0x61657333);
static constexpr int kAudioFormatALaw = int(0x616c6177);
static constexpr int kAudioFormatAMR = int(0x73616d72);
static constexpr int kAudioFormatAppleIMA4 = int(0x696d6134);
static constexpr int kAudioFormatAppleLossless = int(0x616c6163);
static constexpr int kAudioFormatAudible = int(0x41554442);
static constexpr int kAudioFormatDVIIntelIMA = int(0x6d730011);
static constexpr System::Int8 kAudioFormatFlagIsAlignedHigh = System::Int8(0x10);
static constexpr System::Int8 kAudioFormatFlagIsBigEndian = System::Int8(0x2);
static constexpr System::Int8 kAudioFormatFlagIsFloat = System::Int8(0x1);
static constexpr System::Int8 kAudioFormatFlagIsNonInterleaved = System::Int8(0x20);
static constexpr System::Int8 kAudioFormatFlagIsNonMixable = System::Int8(0x40);
static constexpr System::Int8 kAudioFormatFlagIsPacked = System::Int8(0x8);
static constexpr System::Int8 kAudioFormatFlagIsSignedInteger = System::Int8(0x4);
static constexpr int kAudioFormatFlagsAreAllClear = int(-2147483648);
static constexpr System::Int8 kAudioFormatFlagsAudioUnitCanonical = System::Int8(0x29);
static constexpr System::Int8 kAudioFormatFlagsCanonical = System::Int8(0x9);
static constexpr System::Int8 kAudioFormatFlagsNativeEndian = System::Int8(0x0);
static constexpr System::Int8 kAudioFormatFlagsNativeFloatPacked = System::Int8(0x9);
static constexpr int kAudioFormatLinearPCM = int(0x6c70636d);
static constexpr int kAudioFormatMACE3 = int(0x4d414333);
static constexpr int kAudioFormatMACE6 = int(0x4d414336);
static constexpr int kAudioFormatMIDIStream = int(0x6d696469);
static constexpr int kAudioFormatMPEG4AAC = int(0x61616320);
static constexpr int kAudioFormatMPEG4AAC_ELD = int(0x61616365);
static constexpr int kAudioFormatMPEG4AAC_ELD_SBR = int(0x61616366);
static constexpr int kAudioFormatMPEG4AAC_HE = int(0x61616368);
static constexpr int kAudioFormatMPEG4AAC_HE_V2 = int(0x61616370);
static constexpr int kAudioFormatMPEG4AAC_LD = int(0x6161636c);
static constexpr int kAudioFormatMPEG4AAC_Spatial = int(0x61616373);
static constexpr int kAudioFormatMPEG4CELP = int(0x63656c70);
static constexpr int kAudioFormatMPEG4HVXC = int(0x68767863);
static constexpr int kAudioFormatMPEG4TwinVQ = int(0x74777671);
static constexpr int kAudioFormatMPEGLayer1 = int(0x2e6d7031);
static constexpr int kAudioFormatMPEGLayer2 = int(0x2e6d7032);
static constexpr int kAudioFormatMPEGLayer3 = int(0x2e6d7033);
static constexpr int kAudioFormatMicrosoftGSM = int(0x6d730031);
static constexpr int kAudioFormatParameterValueStream = int(0x61707673);
static constexpr int kAudioFormatQDesign = int(0x51444d43);
static constexpr int kAudioFormatQDesign2 = int(0x51444d32);
static constexpr int kAudioFormatQUALCOMM = int(0x51636c70);
static constexpr int kAudioFormatTimeCode = int(0x74696d65);
static constexpr int kAudioFormatULaw = int(0x756c6177);
static constexpr int kAudioFormatiLBC = int(0x696c6263);
static constexpr System::Int8 kAudioStreamAnyRate = System::Int8(0x0);
static constexpr System::Int8 kAudioTimeStampHostTimeValid = System::Int8(0x2);
static constexpr System::Int8 kAudioTimeStampRateScalarValid = System::Int8(0x4);
static constexpr System::Int8 kAudioTimeStampSMPTETimeValid = System::Int8(0x10);
static constexpr System::Int8 kAudioTimeStampSampleHostTimeValid = System::Int8(0x3);
static constexpr System::Int8 kAudioTimeStampSampleTimeValid = System::Int8(0x1);
static constexpr System::Int8 kAudioTimeStampWordClockTimeValid = System::Int8(0x8);
static constexpr System::Int8 kAudio_FileNotFoundError = System::Int8(-43);
static constexpr System::Int8 kAudio_MemFullError = System::Int8(-108);
static constexpr System::Int8 kAudio_ParamError = System::Int8(-50);
static constexpr System::Int8 kAudio_UnimplementedError = System::Int8(-4);
static constexpr System::Int8 kLinearPCMFormatFlagIsAlignedHigh = System::Int8(0x10);
static constexpr System::Int8 kLinearPCMFormatFlagIsBigEndian = System::Int8(0x2);
static constexpr System::Int8 kLinearPCMFormatFlagIsFloat = System::Int8(0x1);
static constexpr System::Int8 kLinearPCMFormatFlagIsNonInterleaved = System::Int8(0x20);
static constexpr System::Int8 kLinearPCMFormatFlagIsNonMixable = System::Int8(0x40);
static constexpr System::Int8 kLinearPCMFormatFlagIsPacked = System::Int8(0x8);
static constexpr System::Int8 kLinearPCMFormatFlagIsSignedInteger = System::Int8(0x4);
static constexpr int kLinearPCMFormatFlagsAreAllClear = int(-2147483648);
static constexpr System::Word kLinearPCMFormatFlagsSampleFractionMask = System::Word(0x1f80);
static constexpr System::Int8 kLinearPCMFormatFlagsSampleFractionShift = System::Int8(0x7);
static constexpr System::Int8 kMPEG4Object_AAC_LC = System::Int8(0x2);
static constexpr System::Int8 kMPEG4Object_AAC_LTP = System::Int8(0x4);
static constexpr System::Int8 kMPEG4Object_AAC_Main = System::Int8(0x1);
static constexpr System::Int8 kMPEG4Object_AAC_SBR = System::Int8(0x5);
static constexpr System::Int8 kMPEG4Object_AAC_SSR = System::Int8(0x3);
static constexpr System::Int8 kMPEG4Object_AAC_Scalable = System::Int8(0x6);
static constexpr System::Int8 kMPEG4Object_CELP = System::Int8(0x8);
static constexpr System::Int8 kMPEG4Object_HVXC = System::Int8(0x9);
static constexpr System::Int8 kMPEG4Object_TwinVQ = System::Int8(0x7);
static constexpr System::Int8 kSMPTETimeRunning = System::Int8(0x2);
static constexpr System::Int8 kSMPTETimeType2398 = System::Int8(0xb);
static constexpr System::Int8 kSMPTETimeType24 = System::Int8(0x0);
static constexpr System::Int8 kSMPTETimeType25 = System::Int8(0x1);
static constexpr System::Int8 kSMPTETimeType2997 = System::Int8(0x4);
static constexpr System::Int8 kSMPTETimeType2997Drop = System::Int8(0x5);
static constexpr System::Int8 kSMPTETimeType30 = System::Int8(0x3);
static constexpr System::Int8 kSMPTETimeType30Drop = System::Int8(0x2);
static constexpr System::Int8 kSMPTETimeType50 = System::Int8(0xa);
static constexpr System::Int8 kSMPTETimeType5994 = System::Int8(0x7);
static constexpr System::Int8 kSMPTETimeType5994Drop = System::Int8(0x9);
static constexpr System::Int8 kSMPTETimeType60 = System::Int8(0x6);
static constexpr System::Int8 kSMPTETimeType60Drop = System::Int8(0x8);
static constexpr System::Int8 kSMPTETimeValid = System::Int8(0x1);
#define libCoreAudio u"/System/Library/Frameworks/CoreAudio.framework/CoreAudio"
}	/* namespace Coreaudio */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_COREAUDIO)
using namespace Iosapi::Coreaudio;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_CoreaudioHPP
