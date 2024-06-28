// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.CoreVideo.pas' rev: 34.00 (iOS)

#ifndef Iosapi_CorevideoHPP
#define Iosapi_CorevideoHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.StdDef.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <iOSapi.OpenGLES.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Corevideo
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef unsigned CVAttachmentMode;

typedef unsigned *PCVAttachmentMode;

typedef NativeInt CVBufferRef;

typedef NativeInt CVDisplayLinkRef;

typedef NativeInt *PCVDisplayLinkRef;

typedef NativeInt CVImageBufferRef;

typedef NativeInt CVOpenGLESTextureCacheRef;

typedef NativeInt *PCVOpenGLESTextureCacheRef;

typedef NativeInt CVOpenGLESTextureRef;

typedef NativeInt *PCVOpenGLESTextureRef;

typedef unsigned __int64 CVOptionFlags;

typedef unsigned __int64 *PCVOptionFlags;

typedef NativeInt CVPixelBufferPoolRef;

typedef NativeInt *PCVPixelBufferPoolRef;

typedef NativeInt CVPixelBufferRef;

typedef NativeInt *PCVPixelBufferRef;

typedef int CVReturn;

typedef void __cdecl (*CVPixelBufferReleaseBytesCallback)(void * releaseRefCon, void * baseAddress);

typedef void __cdecl (*CVPixelBufferReleasePlanarBytesCallback)(void * releaseRefCon, void * dataPtr, unsigned long dataSize, unsigned long numberOfPlanes, System::PPointer planeAddresses);

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 COREVIDEO_SUPPORTS_COLORSPACE = System::Int8(0x0);
static constexpr System::Int8 COREVIDEO_SUPPORTS_DIRECT3D = System::Int8(0x0);
static constexpr System::Int8 COREVIDEO_SUPPORTS_DISPLAYLINK = System::Int8(0x0);
static constexpr System::Int8 COREVIDEO_SUPPORTS_IOSURFACE = System::Int8(0x0);
static constexpr System::Int8 COREVIDEO_SUPPORTS_OPENGL = System::Int8(0x0);
static constexpr System::Int8 COREVIDEO_SUPPORTS_OPENGLES = System::Int8(0x1);
static constexpr System::Int8 kCVAttachmentMode_ShouldNotPropagate = System::Int8(0x0);
static constexpr System::Int8 kCVAttachmentMode_ShouldPropagate = System::Int8(0x1);
static constexpr System::Int8 kCVPixelBufferLock_ReadOnly = System::Int8(0x1);
static constexpr System::Int8 kCVPixelFormatType_16BE555 = System::Int8(0x10);
static constexpr int kCVPixelFormatType_16BE565 = int(0x42353635);
static constexpr int kCVPixelFormatType_16Gray = int(0x62313667);
static constexpr int kCVPixelFormatType_16LE555 = int(0x4c353535);
static constexpr int kCVPixelFormatType_16LE5551 = int(0x35353531);
static constexpr int kCVPixelFormatType_16LE565 = int(0x4c353635);
static constexpr System::Int8 kCVPixelFormatType_1IndexedGray_WhiteIsZero = System::Int8(0x21);
static constexpr System::Int8 kCVPixelFormatType_1Monochrome = System::Int8(0x1);
static constexpr int kCVPixelFormatType_24BGR = int(0x32344247);
static constexpr System::Int8 kCVPixelFormatType_24RGB = System::Int8(0x18);
static constexpr System::Int8 kCVPixelFormatType_2Indexed = System::Int8(0x2);
static constexpr System::Int8 kCVPixelFormatType_2IndexedGray_WhiteIsZero = System::Int8(0x22);
static constexpr int kCVPixelFormatType_30RGB = int(0x5231306b);
static constexpr int kCVPixelFormatType_32ABGR = int(0x41424752);
static constexpr System::Int8 kCVPixelFormatType_32ARGB = System::Int8(0x20);
static constexpr int kCVPixelFormatType_32AlphaGray = int(0x62333261);
static constexpr int kCVPixelFormatType_32BGRA = int(0x42475241);
static constexpr int kCVPixelFormatType_32RGBA = int(0x52474241);
static constexpr int kCVPixelFormatType_420YpCbCr8BiPlanarFullRange = int(0x34323066);
static constexpr int kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange = int(0x34323076);
static constexpr int kCVPixelFormatType_420YpCbCr8Planar = int(0x79343230);
static constexpr int kCVPixelFormatType_420YpCbCr8PlanarFullRange = int(0x66343230);
static constexpr int kCVPixelFormatType_422YpCbCr10 = int(0x76323130);
static constexpr int kCVPixelFormatType_422YpCbCr16 = int(0x76323136);
static constexpr int kCVPixelFormatType_422YpCbCr8 = int(0x32767579);
static constexpr int kCVPixelFormatType_422YpCbCr8FullRange = int(0x79757666);
static constexpr int kCVPixelFormatType_422YpCbCr8_yuvs = int(0x79757673);
static constexpr int kCVPixelFormatType_422YpCbCr_4A_8BiPlanar = int(0x61327679);
static constexpr int kCVPixelFormatType_4444AYpCbCr16 = int(0x79343136);
static constexpr int kCVPixelFormatType_4444AYpCbCr8 = int(0x79343038);
static constexpr int kCVPixelFormatType_4444YpCbCrA8 = int(0x76343038);
static constexpr int kCVPixelFormatType_4444YpCbCrA8R = int(0x72343038);
static constexpr int kCVPixelFormatType_444YpCbCr10 = int(0x76343130);
static constexpr int kCVPixelFormatType_444YpCbCr8 = int(0x76333038);
static constexpr int kCVPixelFormatType_48RGB = int(0x62343872);
static constexpr System::Int8 kCVPixelFormatType_4Indexed = System::Int8(0x4);
static constexpr System::Int8 kCVPixelFormatType_4IndexedGray_WhiteIsZero = System::Int8(0x24);
static constexpr int kCVPixelFormatType_64ARGB = int(0x62363461);
static constexpr System::Int8 kCVPixelFormatType_8Indexed = System::Int8(0x8);
static constexpr System::Int8 kCVPixelFormatType_8IndexedGray_WhiteIsZero = System::Int8(0x28);
static constexpr short kCVReturnAllocationFailed = short(-6662);
static constexpr short kCVReturnDisplayLinkAlreadyRunning = short(-6671);
static constexpr short kCVReturnDisplayLinkCallbacksNotSet = short(-6673);
static constexpr short kCVReturnDisplayLinkNotRunning = short(-6672);
static constexpr short kCVReturnError = short(-6660);
static constexpr short kCVReturnFirst = short(-6660);
static constexpr short kCVReturnInvalidArgument = short(-6661);
static constexpr short kCVReturnInvalidDisplay = short(-6670);
static constexpr short kCVReturnInvalidPixelBufferAttributes = short(-6682);
static constexpr short kCVReturnInvalidPixelFormat = short(-6680);
static constexpr short kCVReturnInvalidPoolAttributes = short(-6691);
static constexpr short kCVReturnInvalidSize = short(-6681);
static constexpr short kCVReturnLast = short(-6699);
static constexpr short kCVReturnPixelBufferNotOpenGLCompatible = short(-6683);
static constexpr short kCVReturnPoolAllocationFailed = short(-6690);
static constexpr System::Int8 kCVReturnSuccess = System::Int8(0x0);
static constexpr short kCVReturnWouldExceedAllocationThreshold = short(-6689);
static constexpr System::Int8 kCVSMPTETimeRunning = System::Int8(0x2);
static constexpr System::Int8 kCVSMPTETimeType24 = System::Int8(0x0);
static constexpr System::Int8 kCVSMPTETimeType25 = System::Int8(0x1);
static constexpr System::Int8 kCVSMPTETimeType2997 = System::Int8(0x4);
static constexpr System::Int8 kCVSMPTETimeType2997Drop = System::Int8(0x5);
static constexpr System::Int8 kCVSMPTETimeType30 = System::Int8(0x3);
static constexpr System::Int8 kCVSMPTETimeType30Drop = System::Int8(0x2);
static constexpr System::Int8 kCVSMPTETimeType5994 = System::Int8(0x7);
static constexpr System::Int8 kCVSMPTETimeType60 = System::Int8(0x6);
static constexpr System::Int8 kCVSMPTETimeValid = System::Int8(0x1);
static constexpr System::Int8 kCVTimeIsIndefinite = System::Int8(0x1);
static constexpr int kCVTimeStampBottomField = int(0x20000);
static constexpr System::Int8 kCVTimeStampHostTimeValid = System::Int8(0x2);
static constexpr int kCVTimeStampIsInterlaced = int(0x30000);
static constexpr System::Int8 kCVTimeStampRateScalarValid = System::Int8(0x10);
static constexpr System::Int8 kCVTimeStampSMPTETimeValid = System::Int8(0x4);
static constexpr int kCVTimeStampTopField = int(0x10000);
static constexpr System::Int8 kCVTimeStampVideoHostTimeValid = System::Int8(0x3);
static constexpr System::Int8 kCVTimeStampVideoRefreshPeriodValid = System::Int8(0x8);
static constexpr System::Int8 kCVTimeStampVideoTimeValid = System::Int8(0x1);
#define libCoreVideo u"/System/Library/Frameworks/CoreVideo.framework/CoreVideo"
extern "C" void * __cdecl CVBufferGetAttachment(NativeInt buffer, CFStringRef key, PCVAttachmentMode attachmentMode);
extern "C" CFDictionaryRef __cdecl CVBufferGetAttachments(NativeInt buffer, unsigned attachmentMode);
extern "C" void __cdecl CVBufferPropagateAttachments(NativeInt sourceBuffer, NativeInt destinationBuffer);
extern "C" void __cdecl CVBufferRelease(NativeInt buffer);
extern "C" void __cdecl CVBufferRemoveAllAttachments(NativeInt buffer);
extern "C" void __cdecl CVBufferRemoveAttachment(NativeInt buffer, CFStringRef key);
extern "C" NativeInt __cdecl CVBufferRetain(NativeInt buffer);
extern "C" void __cdecl CVBufferSetAttachment(NativeInt buffer, CFStringRef key, void * value, unsigned attachmentMode);
extern "C" void __cdecl CVBufferSetAttachments(NativeInt buffer, CFDictionaryRef theAttachments, unsigned attachmentMode);
extern "C" unsigned __int64 __cdecl CVGetCurrentHostTime(void);
extern "C" double __cdecl CVGetHostClockFrequency(void);
extern "C" unsigned __cdecl CVGetHostClockMinimumTimeDelta(void);
extern "C" Iosapi::Foundation::NSRect __cdecl CVImageBufferGetCleanRect(NativeInt imageBuffer);
extern "C" Iosapi::Foundation::NSSize __cdecl CVImageBufferGetDisplaySize(NativeInt imageBuffer);
extern "C" Iosapi::Foundation::NSSize __cdecl CVImageBufferGetEncodedSize(NativeInt imageBuffer);
extern "C" int __cdecl CVOpenGLESTextureCacheCreate(CFAllocatorRef allocator, CFDictionaryRef cacheAttributes, void * eaglContext, CFDictionaryRef textureAttributes, PCVOpenGLESTextureCacheRef cacheOut);
extern "C" int __cdecl CVOpenGLESTextureCacheCreateTextureFromImage(CFAllocatorRef allocator, NativeInt textureCache, NativeInt sourceImage, CFDictionaryRef textureAttributes, unsigned target, int internalFormat, int width, int height, unsigned format, unsigned type_, unsigned long planeIndex, PCVOpenGLESTextureRef textureOut);
extern "C" void __cdecl CVOpenGLESTextureCacheFlush(NativeInt textureCache, unsigned __int64 options);
extern "C" unsigned long __cdecl CVOpenGLESTextureCacheGetTypeID(void);
extern "C" void __cdecl CVOpenGLESTextureGetCleanTexCoords(NativeInt image, Iosapi::Opengles::PGLfloat lowerLeft, Iosapi::Opengles::PGLfloat lowerRight, Iosapi::Opengles::PGLfloat upperRight, Iosapi::Opengles::PGLfloat upperLeft);
extern "C" unsigned __cdecl CVOpenGLESTextureGetName(NativeInt image);
extern "C" unsigned __cdecl CVOpenGLESTextureGetTarget(NativeInt image);
extern "C" unsigned long __cdecl CVOpenGLESTextureGetTypeID(void);
extern "C" bool __cdecl CVOpenGLESTextureIsFlipped(NativeInt image);
extern "C" int __cdecl CVPixelBufferCreate(CFAllocatorRef allocator, unsigned long width, unsigned long height, unsigned pixelFormatType, CFDictionaryRef pixelBufferAttributes, PCVPixelBufferRef pixelBufferOut);
extern "C" int __cdecl CVPixelBufferCreateResolvedAttributesDictionary(CFAllocatorRef allocator, CFArrayRef attributes, Macapi::Corefoundation::PCFDictionaryRef resolvedDictionaryOut);
extern "C" int __cdecl CVPixelBufferCreateWithBytes(CFAllocatorRef allocator, unsigned long width, unsigned long height, unsigned pixelFormatType, void * baseAddress, unsigned long bytesPerRow, CVPixelBufferReleaseBytesCallback releaseCallback, void * releaseRefCon, CFDictionaryRef pixelBufferAttributes, PCVPixelBufferRef pixelBufferOut);
extern "C" int __cdecl CVPixelBufferCreateWithPlanarBytes(CFAllocatorRef allocator, unsigned long width, unsigned long height, unsigned pixelFormatType, void * dataPtr, unsigned long dataSize, unsigned long numberOfPlanes, void * planeBaseAddress, Posix::Stddef::Psize_t planeWidth, Posix::Stddef::Psize_t planeHeight, Posix::Stddef::Psize_t planeBytesPerRow, CVPixelBufferReleasePlanarBytesCallback releaseCallback, void * releaseRefCon, CFDictionaryRef pixelBufferAttributes, PCVPixelBufferRef pixelBufferOut);
extern "C" int __cdecl CVPixelBufferFillExtendedPixels(NativeInt pixelBuffer);
extern "C" void * __cdecl CVPixelBufferGetBaseAddress(NativeInt pixelBuffer);
extern "C" void * __cdecl CVPixelBufferGetBaseAddressOfPlane(NativeInt pixelBuffer, unsigned long planeIndex);
extern "C" unsigned long __cdecl CVPixelBufferGetBytesPerRow(NativeInt pixelBuffer);
extern "C" unsigned long __cdecl CVPixelBufferGetBytesPerRowOfPlane(NativeInt pixelBuffer, unsigned long planeIndex);
extern "C" unsigned long __cdecl CVPixelBufferGetDataSize(NativeInt pixelBuffer);
extern "C" void __cdecl CVPixelBufferGetExtendedPixels(NativeInt pixelBuffer, Posix::Stddef::Psize_t extraColumnsOnLeft, Posix::Stddef::Psize_t extraColumnsOnRight, Posix::Stddef::Psize_t extraRowsOnTop, Posix::Stddef::Psize_t extraRowsOnBottom);
extern "C" unsigned long __cdecl CVPixelBufferGetHeight(NativeInt pixelBuffer);
extern "C" unsigned long __cdecl CVPixelBufferGetHeightOfPlane(NativeInt pixelBuffer, unsigned long planeIndex);
extern "C" unsigned __cdecl CVPixelBufferGetPixelFormatType(NativeInt pixelBuffer);
extern "C" unsigned long __cdecl CVPixelBufferGetPlaneCount(NativeInt pixelBuffer);
extern "C" unsigned long __cdecl CVPixelBufferGetTypeID(void);
extern "C" unsigned long __cdecl CVPixelBufferGetWidth(NativeInt pixelBuffer);
extern "C" unsigned long __cdecl CVPixelBufferGetWidthOfPlane(NativeInt pixelBuffer, unsigned long planeIndex);
extern "C" bool __cdecl CVPixelBufferIsPlanar(NativeInt pixelBuffer);
extern "C" int __cdecl CVPixelBufferLockBaseAddress(NativeInt pixelBuffer, unsigned __int64 lockFlags);
extern "C" int __cdecl CVPixelBufferPoolCreate(CFAllocatorRef allocator, CFDictionaryRef poolAttributes, CFDictionaryRef pixelBufferAttributes, PCVPixelBufferPoolRef poolOut);
extern "C" int __cdecl CVPixelBufferPoolCreatePixelBuffer(CFAllocatorRef allocator, NativeInt pixelBufferPool, PCVPixelBufferRef pixelBufferOut);
extern "C" int __cdecl CVPixelBufferPoolCreatePixelBufferWithAuxAttributes(CFAllocatorRef allocator, NativeInt pixelBufferPool, CFDictionaryRef auxAttributes, PCVPixelBufferRef pixelBufferOut);
extern "C" CFDictionaryRef __cdecl CVPixelBufferPoolGetAttributes(NativeInt pool);
extern "C" CFDictionaryRef __cdecl CVPixelBufferPoolGetPixelBufferAttributes(NativeInt pool);
extern "C" unsigned long __cdecl CVPixelBufferPoolGetTypeID(void);
extern "C" void __cdecl CVPixelBufferPoolRelease(NativeInt pixelBufferPool);
extern "C" NativeInt __cdecl CVPixelBufferPoolRetain(NativeInt pixelBufferPool);
extern "C" void __cdecl CVPixelBufferRelease(NativeInt texture);
extern "C" NativeInt __cdecl CVPixelBufferRetain(NativeInt texture);
extern "C" int __cdecl CVPixelBufferUnlockBaseAddress(NativeInt pixelBuffer, unsigned __int64 unlockFlags);
extern "C" CFArrayRef __cdecl CVPixelFormatDescriptionArrayCreateWithAllPixelFormatTypes(CFAllocatorRef allocator);
extern "C" CFDictionaryRef __cdecl CVPixelFormatDescriptionCreateWithPixelFormatType(CFAllocatorRef allocator, unsigned pixelFormat);
extern "C" void __cdecl CVPixelFormatDescriptionRegisterDescriptionWithPixelFormatType(CFDictionaryRef description, unsigned pixelFormat);
extern DELPHI_PACKAGE CFStringRef __fastcall kCVPixelBufferPixelFormatTypeKey(void);
}	/* namespace Corevideo */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_COREVIDEO)
using namespace Iosapi::Corevideo;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_CorevideoHPP
