// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Macapi.CoreServices.pas' rev: 34.00 (iOS)

#ifndef Macapi_CoreservicesHPP
#define Macapi_CoreservicesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Macapi
{
namespace Coreservices
{
//-- forward type declarations -----------------------------------------------
struct ProcessSerialNumber;
struct Point;
struct Rect;
struct FixedPoint;
struct FixedRect;
struct TimeRecord;
class DELPHICLASS HandleObject;
struct NumVersion;
struct NumVersionVariant;
struct VersRec;
struct HFSUniStr255;
struct FSSpec;
struct IOParam;
struct FileParam;
struct VolumeParam;
struct CntrlParam;
struct SlotDevParam;
struct MultiDevParam;
struct ParamBlockRec;
struct HFileInfo;
struct DirInfo;
struct CInfoPBRec;
struct XCInfoPBRec;
struct DTPBRec;
struct HIOParam;
struct HFileParam;
struct HVolumeParam;
struct XIOParam;
struct XVolumeParam;
struct AccessParam;
struct ObjParam;
struct CopyParam;
struct WDParam;
struct FIDParam;
struct FSPermissionInfo;
struct UTCDateTime;
struct FSCatalogInfo;
struct GetVolParmsInfoBuffer;
struct DECLSPEC_DRECORD dispatch_object
{
};


//-- type declarations -------------------------------------------------------
typedef __int64 wide;

typedef System::PInteger POSStatus;

typedef long __fastcall (*ProcPtr)(void);

typedef void * *PRefCon;

typedef void * *URefCon;

typedef void * *SRefCon;

typedef unsigned UnicodeScalarValue;

typedef unsigned UTF32Char;

typedef System::Word UniChar;

typedef System::Word UTF16Char;

typedef System::Word *UniCharPtr;

typedef unsigned long UniCharCount;

typedef unsigned long *UniCharCountPtr;

typedef System::StaticArray<System::Byte, 256> Str255;

typedef System::StaticArray<System::Byte, 64> Str63;

typedef System::StaticArray<System::Byte, 33> Str32;

typedef System::StaticArray<System::Byte, 32> Str31;

typedef System::StaticArray<System::Byte, 28> Str27;

typedef System::StaticArray<System::Byte, 16> Str15;

typedef System::StaticArray<System::Byte, 34> Str32Field;

typedef Str63 StrFileName;

typedef System::Byte *StringPtr;

typedef StringPtr *StringHandle;

typedef System::Byte *ConstStringPtr;

typedef System::Byte *ConstStr255Param;

typedef System::Byte *ConstStr63Param;

typedef System::Byte *ConstStr32Param;

typedef System::Byte *ConstStr31Param;

typedef System::Byte *ConstStr27Param;

typedef System::Byte *ConstStr15Param;

typedef ConstStr63Param ConstStrFileNameParam;

struct DECLSPEC_DRECORD ProcessSerialNumber
{
public:
	unsigned highLongOfPSN;
	unsigned lowLongOfPSN;
};


typedef ProcessSerialNumber *ProcessSerialNumberPtr;

struct DECLSPEC_DRECORD Point
{
public:
	short v;
	short h;
};


typedef Point *PointPtr;

struct DECLSPEC_DRECORD Rect
{
public:
	short top;
	short left;
	short bottom;
	short right;
};


typedef Rect *RectPtr;

struct DECLSPEC_DRECORD FixedPoint
{
public:
	int x;
	int y;
};


struct DECLSPEC_DRECORD FixedRect
{
public:
	int left;
	int top;
	int right;
	int bottom;
};


typedef short CharParameter;

typedef System::Byte Style;

typedef short StyleParameter;

typedef System::Byte StyleField;

typedef int TimeValue;

typedef int TimeScale;

typedef __int64 CompTimeValue;

typedef __int64 TimeValue64;

typedef void * TimeBase;

#pragma pack(push,2)
struct DECLSPEC_DRECORD TimeRecord
{
public:
	__int64 value;
	int scale;
	void *base;
};
#pragma pack(pop)


class PASCALIMPLEMENTATION HandleObject : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	/* TObject.Create */ inline __fastcall HandleObject() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~HandleObject() { }
	
};


struct DECLSPEC_DRECORD NumVersion
{
public:
	System::Byte nonRelRev;
	System::Byte stage;
	System::Byte minorAndBugRev;
	System::Byte majorRev;
};


struct DECLSPEC_DRECORD NumVersionVariant
{
	
public:
	union
	{
		struct 
		{
			unsigned whole;
		};
		struct 
		{
			NumVersion parts;
		};
		
	};
};


typedef NumVersionVariant *NumVersionVariantPtr;

typedef NumVersionVariantPtr *NumVersionVariantHandle;

struct DECLSPEC_DRECORD VersRec
{
public:
	NumVersion numericVersion;
	short countryCode;
	Str255 shortVersion;
	Str255 reserved;
};


typedef VersRec *VersRecPtr;

typedef VersRecPtr *VersRecHndl;

typedef unsigned TextEncoding;

typedef void * QElemPtr;

typedef void * FInfo;

typedef void * FXInfo;

typedef void * DInfo;

typedef void * DXInfo;

struct DECLSPEC_DRECORD HFSUniStr255
{
public:
	System::Word length;
	System::StaticArray<System::WideChar, 255> unicode;
};


typedef HFSUniStr255 *ConstHFSUniStr255Param;

typedef HFSUniStr255 *PHFSUniStr255;

typedef short FSVolumeRefNum;

typedef short FSIORefNum;

struct DECLSPEC_DRECORD FSSpec
{
public:
	short vRefNum;
	int parID;
	Str63 name;
};


typedef FSSpec *FSSpecPtr;

typedef FSSpecPtr *FSSpecHandle;

typedef FSSpecPtr FSSpecArrayPtr;

typedef FSSpec *ConstFSSpecPtr;

typedef ParamBlockRec *ParmBlkPtr;

typedef void __fastcall (*IOCompletionProcPtr)(ParmBlkPtr paramBlock);

typedef IOCompletionProcPtr IOCompletionUPP;

struct DECLSPEC_DRECORD IOParam
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	short ioRefNum;
	System::Byte ioVersNum;
	System::Byte ioPermssn;
	void * *ioMisc;
	void * *ioBuffer;
	int ioReqCount;
	int ioActCount;
	short ioPosMode;
	int ioPosOffset;
};


typedef IOParam *IOParamPtr;

struct DECLSPEC_DRECORD FileParam
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	short ioFRefNum;
	System::Byte ioFVersNum;
	System::Byte filler1;
	short ioFDirIndex;
	System::Byte ioFlAttrib;
	System::Byte ioFlVersNum;
	void *ioFlFndrInfo;
	unsigned ioFlNum;
	System::Word ioFlStBlk;
	int ioFlLgLen;
	int ioFlPyLen;
	System::Word ioFlRStBlk;
	int ioFlRLgLen;
	int ioFlRPyLen;
	unsigned ioFlCrDat;
	unsigned ioFlMdDat;
};


typedef FileParam *FileParamPtr;

struct DECLSPEC_DRECORD VolumeParam
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	unsigned filler2;
	short ioVolIndex;
	unsigned ioVCrDate;
	unsigned ioVLsBkUp;
	System::Word ioVAtrb;
	System::Word ioVNmFls;
	System::Word ioVDirSt;
	short ioVBlLn;
	System::Word ioVNmAlBlks;
	unsigned ioVAlBlkSiz;
	unsigned ioVClpSiz;
	System::Word ioAlBlSt;
	unsigned ioVNxtFNum;
	System::Word ioVFrBlk;
};


typedef VolumeParam *VolumeParamPtr;

struct DECLSPEC_DRECORD CntrlParam
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	short ioCRefNum;
	short csCode;
	System::StaticArray<short, 11> csParam;
};


typedef CntrlParam *CntrlParamPtr;

struct DECLSPEC_DRECORD SlotDevParam
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	short ioSRefNum;
	System::Byte ioSVersNum;
	System::Byte ioSPermssn;
	void * *ioSMix;
	short ioSFlags;
	System::Byte ioSlot;
	System::Byte ioID;
};


typedef SlotDevParam *SlotDevParamPtr;

struct DECLSPEC_DRECORD MultiDevParam
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	short ioMRefNum;
	System::Byte ioMVersNum;
	System::Byte ioMPermssn;
	void * *ioMMix;
	short ioMFlags;
	void * *ioSEBlkPtr;
};


typedef MultiDevParam *MultiDevParamPtr;

struct DECLSPEC_DRECORD ParamBlockRec
{
	
public:
	union
	{
		struct 
		{
			MultiDevParam multiDevParam;
		};
		struct 
		{
			SlotDevParam slotDevParam;
		};
		struct 
		{
			CntrlParam cntrlParam;
		};
		struct 
		{
			VolumeParam volumeParam;
		};
		struct 
		{
			FileParam fileParam;
		};
		struct 
		{
			IOParam ioParam;
		};
		
	};
};


struct DECLSPEC_DRECORD HFileInfo
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	short ioFRefNum;
	System::Byte ioFVersNum;
	System::Byte filler1;
	short ioFDirIndex;
	System::Byte ioFlAttrib;
	System::Byte ioACUser;
	void *ioFlFndrInfo;
	int ioDirID;
	System::Word ioFlStBlk;
	int ioFlLgLen;
	int ioFlPyLen;
	System::Word ioFlRStBlk;
	int ioFlRLgLen;
	int ioFlRPyLen;
	unsigned ioFlCrDat;
	unsigned ioFlMdDat;
	unsigned ioFlBkDat;
	void *ioFlXFndrInfo;
	int ioFlParID;
	int ioFlClpSiz;
};


struct DECLSPEC_DRECORD DirInfo
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	short ioFRefNum;
	System::Byte ioFVersNum;
	System::Byte filler1;
	short ioFDirIndex;
	System::Byte ioFlAttrib;
	System::Byte ioACUser;
	void *ioDrUsrWds;
	int ioDrDirID;
	System::Word ioDrNmFls;
	System::StaticArray<short, 9> filler3;
	unsigned ioDrCrDat;
	unsigned ioDrMdDat;
	unsigned ioDrBkDat;
	void *ioDrFndrInfo;
	int ioDrParID;
};


struct DECLSPEC_DRECORD CInfoPBRec
{
	
public:
	union
	{
		struct 
		{
			DirInfo dirInfo;
		};
		struct 
		{
			HFileInfo hFileInfo;
		};
		
	};
};


typedef CInfoPBRec *CInfoPBPtr;

struct DECLSPEC_DRECORD XCInfoPBRec
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	ProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	int filler1;
	System::Byte *ioShortNamePtr;
	short filler2;
	short ioPDType;
	int ioPDAuxType;
	System::StaticArray<int, 2> filler3;
	int ioDirID;
};


typedef XCInfoPBRec *XCInfoPBPtr;

struct DECLSPEC_DRECORD DTPBRec
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	short ioDTRefNum;
	short ioIndex;
	int ioTagInfo;
	void * *ioDTBuffer;
	int ioDTReqCount;
	int ioDTActCount;
	System::Byte ioFiller1;
	System::Byte ioIconType;
	short ioFiller2;
	int ioDirID;
	FourCharCode ioFileCreator;
	FourCharCode ioFileType;
	int ioFiller3;
	int ioDTLgLen;
	int ioDTPyLen;
	System::StaticArray<short, 14> ioFiller4;
	int ioAPPLParID;
};


typedef DTPBRec *DTPBPtr;

struct DECLSPEC_DRECORD HIOParam
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	short ioRefNum;
	System::Byte ioVersNum;
	System::Byte ioPermssn;
	void * *ioMisc;
	void * *ioBuffer;
	int ioReqCount;
	int ioActCount;
	short ioPosMode;
	int ioPosOffset;
};


typedef HIOParam *HIOParamPtr;

struct DECLSPEC_DRECORD HFileParam
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	short ioFRefNum;
	System::Byte ioFVersNum;
	System::Byte filler1;
	short ioFDirIndex;
	System::Byte ioFlAttrib;
	System::Byte ioFlVersNum;
	void *ioFlFndrInfo;
	int ioDirID;
	System::Word ioFlStBlk;
	int ioFlLgLen;
	int ioFlPyLen;
	System::Word ioFlRStBlk;
	int ioFlRLgLen;
	int ioFlRPyLen;
	unsigned ioFlCrDat;
	unsigned ioFlMdDat;
};


typedef HFileParam *HFileParamPtr;

struct DECLSPEC_DRECORD HVolumeParam
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	int filler2;
	short ioVolIndex;
	unsigned ioVCrDate;
	unsigned ioVLsMod;
	short ioVAtrb;
	System::Word ioVNmFls;
	System::Word ioVBitMap;
	System::Word ioAllocPtr;
	System::Word ioVNmAlBlks;
	unsigned ioVAlBlkSiz;
	unsigned ioVClpSiz;
	System::Word ioAlBlSt;
	unsigned ioVNxtCNID;
	System::Word ioVFrBlk;
	System::Word ioVSigWord;
	short ioVDrvInfo;
	short ioVDRefNum;
	short ioVFSID;
	unsigned ioVBkUp;
	short ioVSeqNum;
	unsigned ioVWrCnt;
	unsigned ioVFilCnt;
	unsigned ioVDirCnt;
	System::StaticArray<int, 8> ioVFndrInfo;
};


typedef HVolumeParam *HVolumeParamPtr;

#pragma pack(push,2)
struct DECLSPEC_DRECORD XIOParam
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	short ioRefNum;
	System::Byte ioVersNum;
	System::Byte ioPermssn;
	void * *ioMisc;
	void * *ioBuffer;
	int ioReqCount;
	int ioActCount;
	short ioPosMode;
	__int64 ioWPosOffset;
};
#pragma pack(pop)


typedef XIOParam *XIOParamPtr;

#pragma pack(push,2)
struct DECLSPEC_DRECORD XVolumeParam
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	unsigned ioXVersion;
	short ioVolIndex;
	unsigned ioVCrDate;
	unsigned ioVLsMod;
	short ioVAtrb;
	System::Word ioVNmFls;
	System::Word ioVBitMap;
	System::Word ioAllocPtr;
	System::Word ioVNmAlBlks;
	unsigned ioVAlBlkSiz;
	unsigned ioVClpSiz;
	System::Word ioAlBlSt;
	unsigned ioVNxtCNID;
	System::Word ioVFrBlk;
	System::Word ioVSigWord;
	short ioVDrvInfo;
	short ioVDRefNum;
	short ioVFSID;
	unsigned ioVBkUp;
	short ioVSeqNum;
	unsigned ioVWrCnt;
	unsigned ioVFilCnt;
	unsigned ioVDirCnt;
	System::StaticArray<int, 8> ioVFndrInfo;
	unsigned __int64 ioVTotalBytes;
	unsigned __int64 ioVFreeBytes;
};
#pragma pack(pop)


typedef XVolumeParam *XVolumeParamPtr;

struct DECLSPEC_DRECORD AccessParam
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	short ioRefNum;
	short ioDenyModes;
	short filler4;
	System::Byte filler5;
	System::Byte ioACUser;
	int filler6;
	int ioACOwnerID;
	int ioACGroupID;
	int ioACAccess;
	int ioDirID;
};


typedef AccessParam *AccessParamPtr;

struct DECLSPEC_DRECORD ObjParam
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	short filler7;
	short ioObjType;
	System::Byte *ioObjNamePtr;
	int ioObjID;
};


typedef ObjParam *ObjParamPtr;

struct DECLSPEC_DRECORD CopyParam
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	short ioDstVRefNum;
	short filler8;
	System::Byte *ioNewName;
	System::Byte *ioCopyName;
	int ioNewDirID;
	int filler14;
	int filler15;
	int ioDirID;
};


typedef CopyParam *CopyParamPtr;

struct DECLSPEC_DRECORD WDParam
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	short ioWDCreated;
	short ioWDIndex;
	int ioWDProcID;
	short ioWDVRefNum;
	short filler10;
	int filler11;
	int filler12;
	int filler13;
	int ioWDDirID;
};


typedef WDParam *WDParamPtr;

struct DECLSPEC_DRECORD FIDParam
{
public:
	void *qLink;
	short qType;
	short ioTrap;
	void * *ioCmdAddr;
	IOCompletionProcPtr ioCompletion;
	short ioResult;
	System::Byte *ioNamePtr;
	short ioVRefNum;
	int filler14;
	System::Byte *ioDestNamePtr;
	int filler15;
	int ioDestDirID;
	int filler16;
	int filler17;
	int ioSrcDirID;
	short filler18;
	int ioFileID;
};


typedef FIDParam *FIDParamPtr;

struct DECLSPEC_DRECORD FSPermissionInfo
{
public:
	unsigned userID;
	unsigned groupID;
	System::Byte reserved1;
	System::Byte userAccess;
	System::Word mode;
	void *fileSec;
};


typedef unsigned FSCatalogInfoBitmap;

struct DECLSPEC_DRECORD UTCDateTime
{
public:
	System::Word highSeconds;
	unsigned lowSeconds;
	System::Word fraction;
};


typedef UTCDateTime *UTCDateTimePtr;

typedef UTCDateTimePtr *UTCDateTimeHandle;

#pragma pack(push,2)
struct DECLSPEC_DRECORD FSCatalogInfo
{
public:
	System::Word nodeFlags;
	short volume;
	unsigned parentDirID;
	unsigned nodeID;
	System::Byte sharingFlags;
	System::Byte userPrivileges;
	System::Byte reserved1;
	System::Byte reserved2;
	UTCDateTime createDate;
	UTCDateTime contentModDate;
	UTCDateTime attributeModDate;
	UTCDateTime accessDate;
	UTCDateTime backupDate;
	FSPermissionInfo permissions;
	System::StaticArray<System::Byte, 16> finderInfo;
	System::StaticArray<System::Byte, 16> extFinderInfo;
	unsigned __int64 dataLogicalSize;
	unsigned __int64 dataPhysicalSize;
	unsigned __int64 rsrcLogicalSize;
	unsigned __int64 rsrcPhysicalSize;
	unsigned valence;
	unsigned textEncodingHint;
};
#pragma pack(pop)


typedef FSCatalogInfo *PFSCatalogInfo;

typedef FSCatalogInfo *FSCatalogInfoPtr;

#pragma pack(push,1)
struct DECLSPEC_DRECORD GetVolParmsInfoBuffer
{
public:
	short vMVersion;
	int vMAttrib;
	Ptr *vMLocalHand;
	int vMServerAdr;
	int vMVolumeGrade;
	short vMForeignPrivID;
	int vMExtendedAttributes;
	void *vMDeviceID;
	unsigned long vMMaxNameLength;
};
#pragma pack(pop)


typedef GetVolParmsInfoBuffer *PGetVolParmsInfoBuffer;

typedef bool *PBoolean;

typedef unsigned FNMessage;

typedef dispatch_object *dispatch_object_t;

typedef dispatch_object_t dispatch_semaphore_t;

typedef unsigned __int64 dispatch_time_t;

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 normal = System::Int8(0x0);
static constexpr System::Int8 bold = System::Int8(0x1);
static constexpr System::Int8 italic = System::Int8(0x2);
static constexpr System::Int8 underline = System::Int8(0x4);
static constexpr System::Int8 outline = System::Int8(0x8);
static constexpr System::Int8 shadow = System::Int8(0x10);
static constexpr System::Int8 condense = System::Int8(0x20);
static constexpr System::Int8 extend = System::Int8(0x40);
static constexpr System::Int8 fsCurPerm = System::Int8(0x0);
static constexpr System::Int8 fsRdPerm = System::Int8(0x1);
static constexpr System::Int8 fsWrPerm = System::Int8(0x2);
static constexpr System::Int8 fsRdWrPerm = System::Int8(0x3);
static constexpr System::Int8 fsRdWrShPerm = System::Int8(0x4);
static constexpr System::Int8 fsRdAccessPerm = System::Int8(0x1);
static constexpr System::Int8 fsWrAccessPerm = System::Int8(0x2);
static constexpr System::Int8 fsRdDenyPerm = System::Int8(0x10);
static constexpr System::Int8 fsWrDenyPerm = System::Int8(0x20);
static constexpr System::Int8 fsRtParID = System::Int8(0x1);
static constexpr System::Int8 fsRtDirID = System::Int8(0x2);
static constexpr System::Int8 fsAtMark = System::Int8(0x0);
static constexpr System::Int8 fsFromStart = System::Int8(0x1);
static constexpr System::Int8 fsFromLEOF = System::Int8(0x2);
static constexpr System::Int8 fsFromMark = System::Int8(0x3);
static constexpr System::Int8 kFSAllowConcurrentAsyncIOBit = System::Int8(0x3);
static constexpr System::Int8 kFSAllowConcurrentAsyncIOMask = System::Int8(0x8);
static constexpr System::Int8 kFSPleaseCacheBit = System::Int8(0x4);
static constexpr System::Int8 kFSPleaseCacheMask = System::Int8(0x10);
static constexpr System::Int8 kFSNoCacheBit = System::Int8(0x5);
static constexpr System::Int8 kFSNoCacheMask = System::Int8(0x20);
static constexpr System::Int8 kFSRdVerifyBit = System::Int8(0x6);
static constexpr System::Int8 kFSRdVerifyMask = System::Int8(0x40);
static constexpr System::Int8 kFSForceReadBit = System::Int8(0x6);
static constexpr System::Int8 kFSForceReadMask = System::Int8(0x40);
static constexpr System::Int8 kFSNewLineBit = System::Int8(0x7);
static constexpr System::Byte kFSNewLineMask = System::Byte(0x80);
static constexpr System::Word kFSNewLineCharMask = System::Word(0xff00);
static constexpr System::Int8 fsSBPartialName = System::Int8(0x1);
static constexpr System::Int8 fsSBFullName = System::Int8(0x2);
static constexpr System::Int8 fsSBFlAttrib = System::Int8(0x4);
static constexpr System::Int8 fsSBFlFndrInfo = System::Int8(0x8);
static constexpr System::Int8 fsSBFlLgLen = System::Int8(0x20);
static constexpr System::Int8 fsSBFlPyLen = System::Int8(0x40);
static constexpr System::Byte fsSBFlRLgLen = System::Byte(0x80);
static constexpr System::Word fsSBFlRPyLen = System::Word(0x100);
static constexpr System::Word fsSBFlCrDat = System::Word(0x200);
static constexpr System::Word fsSBFlMdDat = System::Word(0x400);
static constexpr System::Word fsSBFlBkDat = System::Word(0x800);
static constexpr System::Word fsSBFlXFndrInfo = System::Word(0x1000);
static constexpr System::Word fsSBFlParID = System::Word(0x2000);
static constexpr System::Word fsSBNegate = System::Word(0x4000);
static constexpr System::Int8 fsSBDrUsrWds = System::Int8(0x8);
static constexpr System::Int8 fsSBDrNmFls = System::Int8(0x10);
static constexpr System::Word fsSBDrCrDat = System::Word(0x200);
static constexpr System::Word fsSBDrMdDat = System::Word(0x400);
static constexpr System::Word fsSBDrBkDat = System::Word(0x800);
static constexpr System::Word fsSBDrFndrInfo = System::Word(0x1000);
static constexpr System::Word fsSBDrParID = System::Word(0x2000);
static constexpr System::Word fsSBNodeID = System::Word(0x8000);
static constexpr int fsSBAttributeModDate = int(0x10000);
static constexpr int fsSBAccessDate = int(0x20000);
static constexpr int fsSBPermissions = int(0x40000);
static constexpr int fsSBSkipPackageContents = int(0x80000);
static constexpr int fsSBSkipHiddenItems = int(0x100000);
static constexpr int fsSBUserID = int(0x200000);
static constexpr int fsSBGroupID = int(0x400000);
static constexpr System::Int8 fsSBPartialNameBit = System::Int8(0x0);
static constexpr System::Int8 fsSBFullNameBit = System::Int8(0x1);
static constexpr System::Int8 fsSBFlAttribBit = System::Int8(0x2);
static constexpr System::Int8 fsSBFlFndrInfoBit = System::Int8(0x3);
static constexpr System::Int8 fsSBFlLgLenBit = System::Int8(0x5);
static constexpr System::Int8 fsSBFlPyLenBit = System::Int8(0x6);
static constexpr System::Int8 fsSBFlRLgLenBit = System::Int8(0x7);
static constexpr System::Int8 fsSBFlRPyLenBit = System::Int8(0x8);
static constexpr System::Int8 fsSBFlCrDatBit = System::Int8(0x9);
static constexpr System::Int8 fsSBFlMdDatBit = System::Int8(0xa);
static constexpr System::Int8 fsSBFlBkDatBit = System::Int8(0xb);
static constexpr System::Int8 fsSBFlXFndrInfoBit = System::Int8(0xc);
static constexpr System::Int8 fsSBFlParIDBit = System::Int8(0xd);
static constexpr System::Int8 fsSBNegateBit = System::Int8(0xe);
static constexpr System::Int8 fsSBDrUsrWdsBit = System::Int8(0x3);
static constexpr System::Int8 fsSBDrNmFlsBit = System::Int8(0x4);
static constexpr System::Int8 fsSBDrCrDatBit = System::Int8(0x9);
static constexpr System::Int8 fsSBDrMdDatBit = System::Int8(0xa);
static constexpr System::Int8 fsSBDrBkDatBit = System::Int8(0xb);
static constexpr System::Int8 fsSBDrFndrInfoBit = System::Int8(0xc);
static constexpr System::Int8 fsSBDrParIDBit = System::Int8(0xd);
static constexpr System::Int8 fsSBNodeIDBit = System::Int8(0xf);
static constexpr System::Int8 fsSBAttributeModDateBit = System::Int8(0x10);
static constexpr System::Int8 fsSBAccessDateBit = System::Int8(0x11);
static constexpr System::Int8 fsSBPermissionsBit = System::Int8(0x12);
static constexpr System::Int8 fsSBSkipPackageContentsBit = System::Int8(0x13);
static constexpr System::Int8 fsSBSkipHiddenItemsBit = System::Int8(0x14);
static constexpr System::Int8 fsSBUserIDBit = System::Int8(0x15);
static constexpr System::Int8 fsSBGroupIDBit = System::Int8(0x16);
static constexpr System::Int8 bLimitFCBs = System::Int8(0x1f);
static constexpr System::Int8 bLocalWList = System::Int8(0x1e);
static constexpr System::Int8 bNoMiniFndr = System::Int8(0x1d);
static constexpr System::Int8 bNoVNEdit = System::Int8(0x1c);
static constexpr System::Int8 bNoLclSync = System::Int8(0x1b);
static constexpr System::Int8 bTrshOffLine = System::Int8(0x1a);
static constexpr System::Int8 bNoSwitchTo = System::Int8(0x19);
static constexpr System::Int8 bNoDeskItems = System::Int8(0x14);
static constexpr System::Int8 bNoBootBlks = System::Int8(0x13);
static constexpr System::Int8 bAccessCntl = System::Int8(0x12);
static constexpr System::Int8 bNoSysDir = System::Int8(0x11);
static constexpr System::Int8 bHasExtFSVol = System::Int8(0x10);
static constexpr System::Int8 bHasOpenDeny = System::Int8(0xf);
static constexpr System::Int8 bHasCopyFile = System::Int8(0xe);
static constexpr System::Int8 bHasMoveRename = System::Int8(0xd);
static constexpr System::Int8 bHasDesktopMgr = System::Int8(0xc);
static constexpr System::Int8 bHasShortName = System::Int8(0xb);
static constexpr System::Int8 bHasFolderLock = System::Int8(0xa);
static constexpr System::Int8 bHasPersonalAccessPrivileges = System::Int8(0x9);
static constexpr System::Int8 bHasUserGroupList = System::Int8(0x8);
static constexpr System::Int8 bHasCatSearch = System::Int8(0x7);
static constexpr System::Int8 bHasFileIDs = System::Int8(0x6);
static constexpr System::Int8 bHasBTreeMgr = System::Int8(0x5);
static constexpr System::Int8 bHasBlankAccessPrivileges = System::Int8(0x4);
static constexpr System::Int8 bSupportsAsyncRequests = System::Int8(0x3);
static constexpr System::Int8 bSupportsTrashVolumeCache = System::Int8(0x2);
static constexpr System::Int8 bHasDirectIO = System::Int8(0x1);
static constexpr System::Int8 bIsEjectable = System::Int8(0x0);
static constexpr System::Int8 bSupportsHFSPlusAPIs = System::Int8(0x1);
static constexpr System::Int8 bSupportsFSCatalogSearch = System::Int8(0x2);
static constexpr System::Int8 bSupportsFSExchangeObjects = System::Int8(0x3);
static constexpr System::Int8 bSupports2TBFiles = System::Int8(0x4);
static constexpr System::Int8 bSupportsLongNames = System::Int8(0x5);
static constexpr System::Int8 bSupportsMultiScriptNames = System::Int8(0x6);
static constexpr System::Int8 bSupportsNamedForks = System::Int8(0x7);
static constexpr System::Int8 bSupportsSubtreeIterators = System::Int8(0x8);
static constexpr System::Int8 bL2PCanMapFileBlocks = System::Int8(0x9);
static constexpr System::Int8 bParentModDateChanges = System::Int8(0xa);
static constexpr System::Int8 bAncestorModDateChanges = System::Int8(0xb);
static constexpr System::Int8 bSupportsSymbolicLinks = System::Int8(0xd);
static constexpr System::Int8 bIsAutoMounted = System::Int8(0xe);
static constexpr System::Int8 bAllowCDiDataHandler = System::Int8(0x11);
static constexpr System::Int8 bSupportsExclusiveLocks = System::Int8(0x12);
static constexpr System::Int8 bSupportsJournaling = System::Int8(0x13);
static constexpr System::Int8 bNoVolumeSizes = System::Int8(0x14);
static constexpr System::Int8 bIsOnInternalBus = System::Int8(0x15);
static constexpr System::Int8 bIsCaseSensitive = System::Int8(0x16);
static constexpr System::Int8 bIsCasePreserving = System::Int8(0x17);
static constexpr System::Int8 bDoNotDisplay = System::Int8(0x18);
static constexpr System::Int8 bIsRemovable = System::Int8(0x19);
static constexpr System::Int8 bNoRootTimes = System::Int8(0x1a);
static constexpr System::Int8 bIsOnExternalBus = System::Int8(0x1b);
static constexpr System::Int8 bSupportsExtendedFileSecurity = System::Int8(0x1c);
static constexpr System::Int8 kWidePosOffsetBit = System::Int8(0x8);
static constexpr int kMaximumBlocksIn4GB = int(0x7fffff);
static constexpr System::Int8 fsUnixPriv = System::Int8(0x1);
static constexpr System::Int8 kNoUserAuthentication = System::Int8(0x1);
static constexpr System::Int8 kPassword = System::Int8(0x2);
static constexpr System::Int8 kEncryptPassword = System::Int8(0x3);
static constexpr System::Int8 kTwoWayEncryptPassword = System::Int8(0x6);
static constexpr System::Int8 knoUser = System::Int8(0x0);
static constexpr System::Int8 kadministratorUser = System::Int8(0x1);
static constexpr System::Int8 knoGroup = System::Int8(0x0);
static constexpr System::Int8 kFSCatInfoNone = System::Int8(0x0);
static constexpr System::Int8 kFSCatInfoTextEncoding = System::Int8(0x1);
static constexpr System::Int8 kFSCatInfoNodeFlags = System::Int8(0x2);
static constexpr System::Int8 kFSCatInfoVolume = System::Int8(0x4);
static constexpr System::Int8 kFSCatInfoParentDirID = System::Int8(0x8);
static constexpr System::Int8 kFSCatInfoNodeID = System::Int8(0x10);
static constexpr System::Int8 kFSCatInfoCreateDate = System::Int8(0x20);
static constexpr System::Int8 kFSCatInfoContentMod = System::Int8(0x40);
static constexpr System::Byte kFSCatInfoAttrMod = System::Byte(0x80);
static constexpr System::Word kFSCatInfoAccessDate = System::Word(0x100);
static constexpr System::Word kFSCatInfoBackupDate = System::Word(0x200);
static constexpr System::Word kFSCatInfoPermissions = System::Word(0x400);
static constexpr System::Word kFSCatInfoFinderInfo = System::Word(0x800);
static constexpr System::Word kFSCatInfoFinderXInfo = System::Word(0x1000);
static constexpr System::Word kFSCatInfoValence = System::Word(0x2000);
static constexpr System::Word kFSCatInfoDataSizes = System::Word(0x4000);
static constexpr System::Word kFSCatInfoRsrcSizes = System::Word(0x8000);
static constexpr int kFSCatInfoSharingFlags = int(0x10000);
static constexpr int kFSCatInfoUserPrivs = int(0x20000);
static constexpr int kFSCatInfoUserAccess = int(0x80000);
static constexpr int kFSCatInfoSetOwnership = int(0x100000);
static constexpr int kFSCatInfoFSFileSecurityRef = int(0x400000);
static constexpr System::Word kFSCatInfoAllDates = System::Word(0x3e0);
static constexpr int kFSCatInfoGettableInfo = int(0x3ffff);
static constexpr System::Word kFSCatInfoSettableInfo = System::Word(0x1fe3);
static constexpr unsigned kFSCatInfoReserved = unsigned(0xfffc0000);
static constexpr System::Int8 kFSNodeLockedBit = System::Int8(0x0);
static constexpr System::Int8 kFSNodeLockedMask = System::Int8(0x1);
static constexpr System::Int8 kFSNodeResOpenBit = System::Int8(0x2);
static constexpr System::Int8 kFSNodeResOpenMask = System::Int8(0x4);
static constexpr System::Int8 kFSNodeDataOpenBit = System::Int8(0x3);
static constexpr System::Int8 kFSNodeDataOpenMask = System::Int8(0x8);
static constexpr System::Int8 kFSNodeIsDirectoryBit = System::Int8(0x4);
static constexpr System::Int8 kFSNodeIsDirectoryMask = System::Int8(0x10);
static constexpr System::Int8 kFSNodeCopyProtectBit = System::Int8(0x6);
static constexpr System::Int8 kFSNodeCopyProtectMask = System::Int8(0x40);
static constexpr System::Int8 kFSNodeForkOpenBit = System::Int8(0x7);
static constexpr System::Byte kFSNodeForkOpenMask = System::Byte(0x80);
static constexpr System::Int8 kFSNodeHardLinkBit = System::Int8(0x8);
static constexpr System::Word kFSNodeHardLinkMask = System::Word(0x100);
static constexpr System::Int8 kFSNodeInSharedBit = System::Int8(0x2);
static constexpr System::Int8 kFSNodeInSharedMask = System::Int8(0x4);
static constexpr System::Int8 kFSNodeIsMountedBit = System::Int8(0x3);
static constexpr System::Int8 kFSNodeIsMountedMask = System::Int8(0x8);
static constexpr System::Int8 kFSNodeIsSharePointBit = System::Int8(0x5);
static constexpr System::Int8 kFSNodeIsSharePointMask = System::Int8(0x20);
static constexpr System::Int8 kFSVolFlagDefaultVolumeBit = System::Int8(0x5);
static constexpr System::Int8 kFSVolFlagDefaultVolumeMask = System::Int8(0x20);
static constexpr System::Int8 kFSVolFlagFilesOpenBit = System::Int8(0x6);
static constexpr System::Int8 kFSVolFlagFilesOpenMask = System::Int8(0x40);
static constexpr System::Int8 kFSVolFlagHardwareLockedBit = System::Int8(0x7);
static constexpr System::Byte kFSVolFlagHardwareLockedMask = System::Byte(0x80);
static constexpr System::Int8 kFSVolFlagJournalingActiveBit = System::Int8(0xe);
static constexpr System::Word kFSVolFlagJournalingActiveMask = System::Word(0x4000);
static constexpr System::Int8 kFSVolFlagSoftwareLockedBit = System::Int8(0xf);
static constexpr System::Word kFSVolFlagSoftwareLockedMask = System::Word(0x8000);
static constexpr System::Int8 kFSReplaceObjectDefaultOptions = System::Int8(0x0);
static constexpr System::Int8 kFSReplaceObjectReplaceMetadata = System::Int8(0x1);
static constexpr System::Int8 kFSReplaceObjectSaveOriginalAsABackup = System::Int8(0x2);
static constexpr System::Int8 kFSReplaceObjectReplacePermissionInfo = System::Int8(0x4);
static constexpr System::Int8 kFSReplaceObjectPreservePermissionInfo = System::Int8(0x8);
static constexpr System::Int8 kFSReplaceObjectDoNotCheckObjectWriteAccess = System::Int8(0x10);
static constexpr System::Int8 kFSPathMakeRefDefaultOptions = System::Int8(0x0);
static constexpr System::Int8 kFSPathMakeRefDoNotFollowLeafSymlink = System::Int8(0x1);
static constexpr System::Int8 kFNDirectoryModifiedMessage = System::Int8(0x1);
static constexpr System::Int8 kFSFileOperationDefaultOptions = System::Int8(0x0);
static constexpr System::Int8 kFSFileOperationOverwrite = System::Int8(0x1);
static constexpr System::Int8 kFSFileOperationSkipSourcePermissionErrors = System::Int8(0x2);
static constexpr System::Int8 kFSFileOperationDoNotMoveAcrossVolumes = System::Int8(0x4);
static constexpr System::Int8 kFSFileOperationSkipPreflight = System::Int8(0x8);
static constexpr System::Int8 kFSOperationStageUndefined = System::Int8(0x0);
static constexpr System::Int8 kFSOperationStagePreflighting = System::Int8(0x1);
static constexpr System::Int8 kFSOperationStageRunning = System::Int8(0x2);
static constexpr System::Int8 kFSOperationStageComplete = System::Int8(0x3);
static constexpr System::Int8 pleaseCacheBit = System::Int8(0x4);
static constexpr System::Int8 pleaseCacheMask = System::Int8(0x10);
static constexpr System::Int8 noCacheBit = System::Int8(0x5);
static constexpr System::Int8 noCacheMask = System::Int8(0x20);
static constexpr System::Int8 rdVerifyBit = System::Int8(0x6);
static constexpr System::Int8 rdVerifyMask = System::Int8(0x40);
static constexpr System::Int8 rdVerify = System::Int8(0x40);
static constexpr System::Int8 forceReadBit = System::Int8(0x6);
static constexpr System::Int8 forceReadMask = System::Int8(0x40);
static constexpr System::Int8 newLineBit = System::Int8(0x7);
static constexpr System::Byte newLineMask = System::Byte(0x80);
static constexpr System::Word newLineCharMask = System::Word(0xff00);
static constexpr System::Int8 kOwnerID2Name = System::Int8(0x1);
static constexpr System::Int8 kGroupID2Name = System::Int8(0x2);
static constexpr System::Int8 kOwnerName2ID = System::Int8(0x3);
static constexpr System::Int8 kGroupName2ID = System::Int8(0x4);
static constexpr System::Int8 kReturnNextUser = System::Int8(0x1);
static constexpr System::Int8 kReturnNextGroup = System::Int8(0x2);
static constexpr System::Int8 kReturnNextUG = System::Int8(0x3);
static constexpr System::Int8 kVCBFlagsIdleFlushBit = System::Int8(0x3);
static constexpr System::Int8 kVCBFlagsIdleFlushMask = System::Int8(0x8);
static constexpr System::Int8 kVCBFlagsHFSPlusAPIsBit = System::Int8(0x4);
static constexpr System::Int8 kVCBFlagsHFSPlusAPIsMask = System::Int8(0x10);
static constexpr System::Int8 kVCBFlagsHardwareGoneBit = System::Int8(0x5);
static constexpr System::Int8 kVCBFlagsHardwareGoneMask = System::Int8(0x20);
static constexpr System::Int8 kVCBFlagsVolumeDirtyBit = System::Int8(0xf);
static constexpr System::Word kVCBFlagsVolumeDirtyMask = System::Word(0x8000);
static constexpr System::Int8 kioVAtrbDefaultVolumeBit = System::Int8(0x5);
static constexpr System::Int8 kioVAtrbDefaultVolumeMask = System::Int8(0x20);
static constexpr System::Int8 kioVAtrbFilesOpenBit = System::Int8(0x6);
static constexpr System::Int8 kioVAtrbFilesOpenMask = System::Int8(0x40);
static constexpr System::Int8 kioVAtrbHardwareLockedBit = System::Int8(0x7);
static constexpr System::Byte kioVAtrbHardwareLockedMask = System::Byte(0x80);
static constexpr System::Int8 kioVAtrbSoftwareLockedBit = System::Int8(0xf);
static constexpr System::Word kioVAtrbSoftwareLockedMask = System::Word(0x8000);
static constexpr System::Int8 kioFlAttribLockedBit = System::Int8(0x0);
static constexpr System::Int8 kioFlAttribLockedMask = System::Int8(0x1);
static constexpr System::Int8 kioFlAttribResOpenBit = System::Int8(0x2);
static constexpr System::Int8 kioFlAttribResOpenMask = System::Int8(0x4);
static constexpr System::Int8 kioFlAttribDataOpenBit = System::Int8(0x3);
static constexpr System::Int8 kioFlAttribDataOpenMask = System::Int8(0x8);
static constexpr System::Int8 kioFlAttribDirBit = System::Int8(0x4);
static constexpr System::Int8 kioFlAttribDirMask = System::Int8(0x10);
static constexpr System::Int8 ioDirFlg = System::Int8(0x4);
static constexpr System::Int8 ioDirMask = System::Int8(0x10);
static constexpr System::Int8 kioFlAttribCopyProtBit = System::Int8(0x6);
static constexpr System::Int8 kioFlAttribCopyProtMask = System::Int8(0x40);
static constexpr System::Int8 kioFlAttribFileOpenBit = System::Int8(0x7);
static constexpr System::Byte kioFlAttribFileOpenMask = System::Byte(0x80);
static constexpr System::Int8 kioFlAttribInSharedBit = System::Int8(0x2);
static constexpr System::Int8 kioFlAttribInSharedMask = System::Int8(0x4);
static constexpr System::Int8 kioFlAttribMountedBit = System::Int8(0x3);
static constexpr System::Int8 kioFlAttribMountedMask = System::Int8(0x8);
static constexpr System::Int8 kioFlAttribSharePointBit = System::Int8(0x5);
static constexpr System::Int8 kioFlAttribSharePointMask = System::Int8(0x20);
static constexpr System::Int8 kioFCBWriteBit = System::Int8(0x8);
static constexpr System::Word kioFCBWriteMask = System::Word(0x100);
static constexpr System::Int8 kioFCBResourceBit = System::Int8(0x9);
static constexpr System::Word kioFCBResourceMask = System::Word(0x200);
static constexpr System::Int8 kioFCBWriteLockedBit = System::Int8(0xa);
static constexpr System::Word kioFCBWriteLockedMask = System::Word(0x400);
static constexpr System::Int8 kioFCBLargeFileBit = System::Int8(0xb);
static constexpr System::Word kioFCBLargeFileMask = System::Word(0x800);
static constexpr System::Int8 kioFCBSharedWriteBit = System::Int8(0xc);
static constexpr System::Word kioFCBSharedWriteMask = System::Word(0x1000);
static constexpr System::Int8 kioFCBFileLockedBit = System::Int8(0xd);
static constexpr System::Word kioFCBFileLockedMask = System::Word(0x2000);
static constexpr System::Int8 kioFCBOwnClumpBit = System::Int8(0xe);
static constexpr System::Word kioFCBOwnClumpMask = System::Word(0x4000);
static constexpr System::Int8 kioFCBModifiedBit = System::Int8(0xf);
static constexpr System::Word kioFCBModifiedMask = System::Word(0x8000);
static constexpr System::Int8 kioACUserNoSeeFolderBit = System::Int8(0x0);
static constexpr System::Int8 kioACUserNoSeeFolderMask = System::Int8(0x1);
static constexpr System::Int8 kioACUserNoSeeFilesBit = System::Int8(0x1);
static constexpr System::Int8 kioACUserNoSeeFilesMask = System::Int8(0x2);
static constexpr System::Int8 kioACUserNoMakeChangesBit = System::Int8(0x2);
static constexpr System::Int8 kioACUserNoMakeChangesMask = System::Int8(0x4);
static constexpr System::Int8 kioACUserNotOwnerBit = System::Int8(0x7);
static constexpr System::Byte kioACUserNotOwnerMask = System::Byte(0x80);
static constexpr System::Int8 kioACAccessOwnerBit = System::Int8(0x1f);
static constexpr unsigned kioACAccessOwnerMask = unsigned(0x80000000);
static constexpr System::Int8 kioACAccessBlankAccessBit = System::Int8(0x1c);
static constexpr int kioACAccessBlankAccessMask = int(0x10000000);
static constexpr System::Int8 kioACAccessUserWriteBit = System::Int8(0x1a);
static constexpr int kioACAccessUserWriteMask = int(0x4000000);
static constexpr System::Int8 kioACAccessUserReadBit = System::Int8(0x19);
static constexpr int kioACAccessUserReadMask = int(0x2000000);
static constexpr System::Int8 kioACAccessUserSearchBit = System::Int8(0x18);
static constexpr int kioACAccessUserSearchMask = int(0x1000000);
static constexpr System::Int8 kioACAccessEveryoneWriteBit = System::Int8(0x12);
static constexpr int kioACAccessEveryoneWriteMask = int(0x40000);
static constexpr System::Int8 kioACAccessEveryoneReadBit = System::Int8(0x11);
static constexpr int kioACAccessEveryoneReadMask = int(0x20000);
static constexpr System::Int8 kioACAccessEveryoneSearchBit = System::Int8(0x10);
static constexpr int kioACAccessEveryoneSearchMask = int(0x10000);
static constexpr System::Int8 kioACAccessGroupWriteBit = System::Int8(0xa);
static constexpr System::Word kioACAccessGroupWriteMask = System::Word(0x400);
static constexpr System::Int8 kioACAccessGroupReadBit = System::Int8(0x9);
static constexpr System::Word kioACAccessGroupReadMask = System::Word(0x200);
static constexpr System::Int8 kioACAccessGroupSearchBit = System::Int8(0x8);
static constexpr System::Word kioACAccessGroupSearchMask = System::Word(0x100);
static constexpr System::Int8 kioACAccessOwnerWriteBit = System::Int8(0x2);
static constexpr System::Int8 kioACAccessOwnerWriteMask = System::Int8(0x4);
static constexpr System::Int8 kioACAccessOwnerReadBit = System::Int8(0x1);
static constexpr System::Int8 kioACAccessOwnerReadMask = System::Int8(0x2);
static constexpr System::Int8 kioACAccessOwnerSearchBit = System::Int8(0x0);
static constexpr System::Int8 kioACAccessOwnerSearchMask = System::Int8(0x1);
static constexpr int kfullPrivileges = int(0x70007);
static constexpr System::Int8 kownerPrivileges = System::Int8(0x7);
static constexpr System::Int8 kLargeIcon = System::Int8(0x1);
static constexpr System::Int8 kLarge4BitIcon = System::Int8(0x2);
static constexpr System::Int8 kLarge8BitIcon = System::Int8(0x3);
static constexpr System::Int8 kSmallIcon = System::Int8(0x4);
static constexpr System::Int8 kSmall4BitIcon = System::Int8(0x5);
static constexpr System::Int8 kSmall8BitIcon = System::Int8(0x6);
static constexpr System::Byte kicnsIconFamily = System::Byte(0xef);
extern DELPHI_PACKAGE System::Byte __fastcall StrLength(ConstStr255Param str);
extern DELPHI_PACKAGE int __fastcall kUseWidePositioning(void);
}	/* namespace Coreservices */
}	/* namespace Macapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI_CORESERVICES)
using namespace Macapi::Coreservices;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI)
using namespace Macapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Macapi_CoreservicesHPP
