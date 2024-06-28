// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.AssetsLibrary.pas' rev: 34.00 (iOS)

#ifndef Iosapi_AssetslibraryHPP
#define Iosapi_AssetslibraryHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Assetslibrary
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE ALAssetClass;
typedef System::DelphiInterface<ALAssetClass> _di_ALAssetClass;
__interface DELPHIINTERFACE ALAsset;
typedef System::DelphiInterface<ALAsset> _di_ALAsset;
class DELPHICLASS TALAsset;
__interface DELPHIINTERFACE ALAssetRepresentationClass;
typedef System::DelphiInterface<ALAssetRepresentationClass> _di_ALAssetRepresentationClass;
__interface DELPHIINTERFACE ALAssetRepresentation;
typedef System::DelphiInterface<ALAssetRepresentation> _di_ALAssetRepresentation;
class DELPHICLASS TALAssetRepresentation;
__interface DELPHIINTERFACE ALAssetsFilterClass;
typedef System::DelphiInterface<ALAssetsFilterClass> _di_ALAssetsFilterClass;
__interface DELPHIINTERFACE ALAssetsFilter;
typedef System::DelphiInterface<ALAssetsFilter> _di_ALAssetsFilter;
class DELPHICLASS TALAssetsFilterClass;
__interface DELPHIINTERFACE ALAssetsGroupClass;
typedef System::DelphiInterface<ALAssetsGroupClass> _di_ALAssetsGroupClass;
__interface DELPHIINTERFACE ALAssetsGroup;
typedef System::DelphiInterface<ALAssetsGroup> _di_ALAssetsGroup;
class DELPHICLASS TALAssetsGroup;
__interface DELPHIINTERFACE ALAssetsLibraryClass;
typedef System::DelphiInterface<ALAssetsLibraryClass> _di_ALAssetsLibraryClass;
__interface DELPHIINTERFACE ALAssetsLibrary;
typedef System::DelphiInterface<ALAssetsLibrary> _di_ALAssetsLibrary;
class DELPHICLASS TALAssetsLibrary;
//-- type declarations -------------------------------------------------------
typedef unsigned long ALAssetsGroupType;

typedef unsigned long ALAssetOrientation;

typedef unsigned long NSEnumerationOptions;

typedef void __fastcall (__closure *TALAssetsLibraryWriteImageCompletionBlock)(Iosapi::Foundation::_di_NSURL assetURL, Iosapi::Foundation::_di_NSError error);

typedef TALAssetsLibraryWriteImageCompletionBlock TALAssetsLibraryWriteVideoCompletionBlock;

__interface  INTERFACE_UUID("{CC79E0D9-CF57-4421-931A-6663290C5BB7}") ALAssetClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D4605158-C1DB-4B1A-9290-E97DB2AC8DE4}") ALAsset  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl valueForProperty(Iosapi::Foundation::_di_NSString prop) = 0 ;
	virtual _di_ALAssetRepresentation __cdecl defaultRepresentation() = 0 ;
	virtual _di_ALAssetRepresentation __cdecl representationForUTI(Iosapi::Foundation::_di_NSString representationUTI) = 0 ;
	virtual void * __cdecl thumbnail() = 0 ;
	virtual void * __cdecl aspectRatioThumbnail() = 0 ;
	virtual void __cdecl writeModifiedImageDataToSavedPhotosAlbum(Iosapi::Foundation::_di_NSData imageData, Iosapi::Foundation::_di_NSDictionary metadata, TALAssetsLibraryWriteImageCompletionBlock completionBlock) = 0 ;
	virtual void __cdecl writeModifiedVideoAtPathToSavedPhotosAlbum(Iosapi::Foundation::_di_NSURL videoPathURL, TALAssetsLibraryWriteImageCompletionBlock completionBlock) = 0 ;
	virtual _di_ALAsset __cdecl originalAsset() = 0 ;
	virtual bool __cdecl isEditable() = 0 ;
	virtual void __cdecl setImageData(Iosapi::Foundation::_di_NSData imageData, Iosapi::Foundation::_di_NSDictionary metadata, TALAssetsLibraryWriteImageCompletionBlock completionBlock) = 0 ;
	virtual void __cdecl setVideoAtPath(Iosapi::Foundation::_di_NSURL videoPathURL, TALAssetsLibraryWriteImageCompletionBlock completionBlock) = 0 ;
};

class PASCALIMPLEMENTATION TALAsset : public Macapi::Objectivec::TOCGenericImport__2<_di_ALAssetClass,_di_ALAsset>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_ALAssetClass,_di_ALAsset> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TALAsset(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_ALAssetClass,_di_ALAsset>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TALAsset() { }
	
};


__interface  INTERFACE_UUID("{1E006316-0C13-4E3B-99E1-59D6EAC567AF}") ALAssetRepresentationClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{218F152C-1746-4343-A528-BAAA35A4B876}") ALAssetRepresentation  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl UTI() = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl dimensions() = 0 ;
	virtual __int64 __cdecl size() = 0 ;
	virtual unsigned long __cdecl getBytes(System::PByte buffer, __int64 fromOffset, unsigned long length, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual void * __cdecl fullResultionImage() = 0 ;
	virtual void * __cdecl CGImageWithOptions(Iosapi::Foundation::_di_NSDictionary options) = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl url() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl metadata() = 0 ;
	virtual unsigned long __cdecl orientation() = 0 ;
	virtual float __cdecl scale() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl filename() = 0 ;
};

class PASCALIMPLEMENTATION TALAssetRepresentation : public Macapi::Objectivec::TOCGenericImport__2<_di_ALAssetRepresentationClass,_di_ALAssetRepresentation>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_ALAssetRepresentationClass,_di_ALAssetRepresentation> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TALAssetRepresentation(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_ALAssetRepresentationClass,_di_ALAssetRepresentation>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TALAssetRepresentation() { }
	
};


__interface  INTERFACE_UUID("{7A435CEA-DFC1-4D83-BD21-7C6209DFB5C4}") ALAssetsFilterClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_ALAssetsFilter __cdecl allPhotos() = 0 ;
	virtual _di_ALAssetsFilter __cdecl allVideos() = 0 ;
	virtual _di_ALAssetsFilter __cdecl allAssets() = 0 ;
};

__interface  INTERFACE_UUID("{5550DF06-FCB7-4C12-A1EA-050359A2FDA0}") ALAssetsFilter  : public Iosapi::Foundation::NSObject 
{
	
};

class PASCALIMPLEMENTATION TALAssetsFilterClass : public Macapi::Objectivec::TOCGenericImport__2<_di_ALAssetsFilterClass,_di_ALAssetsFilter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_ALAssetsFilterClass,_di_ALAssetsFilter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TALAssetsFilterClass(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_ALAssetsFilterClass,_di_ALAssetsFilter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TALAssetsFilterClass() { }
	
};


typedef void __fastcall (__closure *TALAssetsGroupEnumerationResultsBlock)(_di_ALAsset result, unsigned long index, System::PBoolean stop);

__interface  INTERFACE_UUID("{B771635F-9445-4B21-BC2E-5C6DD4DB299E}") ALAssetsGroupClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{A1DF4E3A-DC2F-4C67-9030-BDB68D11757F}") ALAssetsGroup  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl valueForProperty(Iosapi::Foundation::_di_NSString prop) = 0 ;
	virtual void * __cdecl posterImage() = 0 ;
	virtual void __cdecl setAssetsFilter(_di_ALAssetsFilter filter) = 0 ;
	virtual long __cdecl numberOfAssets() = 0 ;
	virtual void __cdecl enumerateAssetsUsingBlock(TALAssetsGroupEnumerationResultsBlock enumerationBlock) = 0 ;
	virtual void __cdecl enumerateAssetsWithOptions(unsigned long options, TALAssetsGroupEnumerationResultsBlock usingBlock) = 0 ;
	virtual void __cdecl enumerateAssetsAtIndexes(Iosapi::Foundation::_di_NSIndexSet inetsSet, unsigned long options, TALAssetsGroupEnumerationResultsBlock usingBlock) = 0 ;
	virtual bool __cdecl isEditable() = 0 ;
	virtual bool __cdecl addAsset(_di_ALAsset asset) = 0 ;
};

class PASCALIMPLEMENTATION TALAssetsGroup : public Macapi::Objectivec::TOCGenericImport__2<_di_ALAssetsGroupClass,_di_ALAssetsGroup>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_ALAssetsGroupClass,_di_ALAssetsGroup> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TALAssetsGroup(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_ALAssetsGroupClass,_di_ALAssetsGroup>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TALAssetsGroup() { }
	
};


typedef void __fastcall (__closure *TALAssetsLibraryGroupsEnumerationResultsBlock)(_di_ALAssetsGroup group, System::PBoolean stop);

typedef void __fastcall (__closure *TALAssetsLibraryAccessFailureBlock)(Iosapi::Foundation::_di_NSError error);

typedef void __fastcall (__closure *TALAssetsLibraryAssetForURLResultBlock)(_di_ALAsset asset);

typedef void __fastcall (__closure *TALAssetsLibraryGroupResultBlock)(_di_ALAssetsGroup group);

__interface  INTERFACE_UUID("{5BFDC638-76DC-456A-B9A6-BC969F7FD4FB}") ALAssetsLibraryClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{359971A2-64E4-4FAA-9FB4-4AE79B51F987}") ALAssetsLibrary  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl enumerateGroupsWithTypes(unsigned long types, TALAssetsLibraryGroupsEnumerationResultsBlock usingBlock, TALAssetsLibraryAccessFailureBlock failureBlock) = 0 ;
	virtual void __cdecl assetForURL(Iosapi::Foundation::_di_NSURL assetURL, TALAssetsLibraryAssetForURLResultBlock resultBlock, TALAssetsLibraryAccessFailureBlock failureBlock) = 0 ;
	virtual void __cdecl groupForURL(Iosapi::Foundation::_di_NSURL groupURL, TALAssetsLibraryGroupResultBlock resultBlock, TALAssetsLibraryAccessFailureBlock failureBlock) = 0 ;
	virtual void __cdecl addAssetsGroupAlbumWithName(Iosapi::Foundation::_di_NSString name, TALAssetsLibraryGroupResultBlock resultBlock, TALAssetsLibraryAccessFailureBlock failureBlock) = 0 ;
	virtual void __cdecl writeImageToSavedPhotosAlbum(void * imageRef, unsigned long orientation, TALAssetsLibraryWriteImageCompletionBlock completionBlock) = 0 /* overload */;
	virtual void __cdecl writeImageToSavedPhotosAlbum(void * imageRef, Iosapi::Foundation::_di_NSDictionary metadata, TALAssetsLibraryWriteImageCompletionBlock completionBlock) = 0 /* overload */;
	virtual void __cdecl writeImageDataToSavedPhotosAlbum(Iosapi::Foundation::_di_NSData imageData, Iosapi::Foundation::_di_NSDictionary metadata, TALAssetsLibraryWriteImageCompletionBlock completionBlock) = 0 ;
	virtual void __cdecl writeVideoAtPathToSavedPhotosAlbum(Iosapi::Foundation::_di_NSURL videoPathURL, TALAssetsLibraryWriteImageCompletionBlock completionBlock) = 0 ;
	virtual bool __cdecl videoAtPathIsCompatibleWithSavedPhotosAlbum(Iosapi::Foundation::_di_NSURL videoPathURL) = 0 ;
};

class PASCALIMPLEMENTATION TALAssetsLibrary : public Macapi::Objectivec::TOCGenericImport__2<_di_ALAssetsLibraryClass,_di_ALAssetsLibrary>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_ALAssetsLibraryClass,_di_ALAssetsLibrary> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TALAssetsLibrary(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_ALAssetsLibraryClass,_di_ALAssetsLibrary>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TALAssetsLibrary() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define libAssetsLibrary u"/System/Library/Frameworks/AssetsLibrary.framework/AssetsL"\
	u"ibrary"
static constexpr System::Int8 ALAssetOrientationUp = System::Int8(0x0);
static constexpr System::Int8 ALAssetOrientationDown = System::Int8(0x1);
static constexpr System::Int8 ALAssetOrientationLeft = System::Int8(0x2);
static constexpr System::Int8 ALAssetOrientationRight = System::Int8(0x3);
static constexpr System::Int8 ALAssetOrientationUpMirrored = System::Int8(0x4);
static constexpr System::Int8 ALAssetOrientationDownMirrored = System::Int8(0x5);
static constexpr System::Int8 ALAssetOrientationLeftMirrored = System::Int8(0x6);
static constexpr System::Int8 ALAssetOrientationRightMirrored = System::Int8(0x7);
static constexpr System::Int8 ALAssetsGroupLibrary = System::Int8(0x1);
static constexpr System::Int8 ALAssetsGroupAlbum = System::Int8(0x2);
static constexpr System::Int8 ALAssetsGroupEvent = System::Int8(0x4);
static constexpr System::Int8 ALAssetsGroupFaces = System::Int8(0x8);
static constexpr System::Int8 ALAssetsGroupSavedPhotos = System::Int8(0x10);
static constexpr System::Int8 ALAssetsGroupPhotoStream = System::Int8(0x20);
static constexpr unsigned ALAssetsGroupAll = unsigned(0xffffffff);
static constexpr System::Int8 ALAssetsLibraryUnknownError = System::Int8(-1);
static constexpr short ALAssetsLibraryWriteFailedError = short(-3300);
static constexpr short ALAssetsLibraryWriteBusyError = short(-3301);
static constexpr short ALAssetsLibraryWriteInvalidDataError = short(-3302);
static constexpr short ALAssetsLibraryWriteIncompatibleDataError = short(-3303);
static constexpr short ALAssetsLibraryWriteDataEncodingError = short(-3304);
static constexpr short ALAssetsLibraryWriteDiskSpaceError = short(-3305);
static constexpr short ALAssetsLibraryDataUnavailableError = short(-3310);
static constexpr short ALAssetsLibraryAccessUserDeniedError = short(-3311);
static constexpr short ALAssetsLibraryAccessGloballyDeniedError = short(-3312);
}	/* namespace Assetslibrary */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_ASSETSLIBRARY)
using namespace Iosapi::Assetslibrary;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_AssetslibraryHPP
