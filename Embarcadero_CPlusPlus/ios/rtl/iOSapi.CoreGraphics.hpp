// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.CoreGraphics.pas' rev: 34.00 (iOS)

#ifndef Iosapi_CoregraphicsHPP
#define Iosapi_CoregraphicsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <Posix.StdDef.hpp>
#include <Posix.SysTypes.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CocoaTypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Coregraphics
{
//-- forward type declarations -----------------------------------------------
struct CGVector;
struct CGAffineTransform;
struct CGDataConsumerCallbacks;
struct CGDataProviderCallbacks;
struct CGDataProviderDirectCallbacks;
struct CGDataProviderDirectAccessCallbacks;
struct CGDataProviderSequentialCallbacks;
struct CGDeviceColor;
struct CGDeviceByteColor;
struct CGFunctionCallbacks;
struct CGPathElement;
struct CGPatternCallbacks;
//-- type declarations -------------------------------------------------------
typedef unsigned CGBitmapInfo;

typedef unsigned CGBlendMode;

typedef unsigned CGButtonCount;

typedef unsigned CGCaptureOptions;

typedef System::Word CGCharCode;

typedef void * CGColorRef;

typedef unsigned CGColorRenderingIntent;

typedef int CGColorSpaceModel;

typedef void * CGColorSpaceRef;

typedef unsigned CGConfigureOption;

typedef void * CGContextRef;

typedef void * *PCGContextRef;

typedef void * CGDataConsumerRef;

typedef void * CGDataProviderRef;

typedef unsigned CGDirectDisplayID;

typedef unsigned *PCGDirectDisplayID;

typedef void * CGDirectPaletteRef;

typedef float CGDisplayBlendFraction;

typedef unsigned CGDisplayChangeSummaryFlags;

typedef void * CGDisplayConfigRef;

typedef float CGDisplayFadeInterval;

typedef unsigned CGDisplayFadeReservationToken;

typedef unsigned *PCGDisplayFadeReservationToken;

typedef void * CGDisplayModeRef;

typedef float CGDisplayReservationInterval;

typedef int CGError;

typedef unsigned CGEventField;

typedef unsigned CGEventFilterMask;

typedef unsigned __int64 CGEventFlags;

typedef unsigned __int64 CGEventMask;

typedef void * CGEventRef;

typedef unsigned CGEventSourceKeyboardType;

typedef void * CGEventSourceRef;

typedef unsigned CGEventSourceStateID;

typedef unsigned CGEventSourceSuppressionState;

typedef unsigned CGEventSuppressionState;

typedef unsigned CGEventTapLocation;

typedef unsigned CGEventTapOptions;

typedef unsigned CGEventTapPlacement;

typedef void * CGEventTapProxy;

typedef unsigned __int64 CGEventTimestamp;

typedef unsigned CGEventType;

typedef System::Word CGFontIndex;

typedef unsigned CGFontPostScriptFormat;

typedef void * CGFontRef;

typedef void * CGFunctionRef;

typedef float CGGammaValue;

typedef float *PCGGammaValue;

typedef System::Word CGGlyph;

typedef System::Word *PCGGlyph;

typedef unsigned CGGradientDrawingOptions;

typedef void * CGGradientRef;

typedef unsigned CGImageAlphaInfo;

typedef void * CGImageDestinationRef;

typedef void * CGImageRef;

typedef void * CGImageSourceRef;

typedef long CGImageSourceStatus;

typedef unsigned CGInterpolationQuality;

typedef System::Word CGKeyCode;

typedef void * CGLPBufferObj;

typedef void * PCGLPBufferObj;

typedef unsigned CGLContextEnable;

typedef void * CGLContextObj;

typedef void * PCGLContextObj;

typedef unsigned CGLContextParameter;

typedef unsigned CGLError;

typedef unsigned CGLGlobalOption;

typedef unsigned CGLineCap;

typedef unsigned CGLineJoin;

typedef void * CGLayerRef;

typedef void * CGLRendererInfoObj;

typedef void * PCGLRendererInfoObj;

typedef unsigned CGLRendererProperty;

typedef void * CGLShareGroupObj;

typedef unsigned CGMouseButton;

typedef void * CGMutablePathRef;

typedef unsigned CGOpenGLDisplayMask;

typedef float CGPaletteBlendFraction;

typedef unsigned CGPathDrawingMode;

typedef unsigned CGPathElementType;

typedef void * CGPathRef;

typedef void * CGPatternRef;

typedef unsigned CGPatternTiling;

typedef void * CGPDFArrayRef;

typedef void * *PCGPDFArrayRef;

typedef System::Byte CGPDFBoolean;

typedef System::Byte *PCGPDFBoolean;

typedef unsigned CGPDFBox;

typedef void * CGPDFContentStreamRef;

typedef unsigned CGPDFDataFormat;

typedef unsigned *PCGPDFDataFormat;

typedef void * CGPDFDictionaryRef;

typedef void * *PCGPDFDictionaryRef;

typedef void * CGPDFDocumentRef;

typedef long CGPDFInteger;

typedef long *PCGPDFInteger;

typedef void * CGPDFObjectRef;

typedef void * *PCGPDFObjectRef;

typedef unsigned CGPDFObjectType;

typedef void * CGPDFOperatorTableRef;

typedef void * CGPDFPageRef;

typedef double CGPDFReal;

typedef double *PCGPDFReal;

typedef void * CGPDFScannerRef;

typedef void * CGPDFStreamRef;

typedef void * *PCGPDFStreamRef;

typedef void * CGPDFStringRef;

typedef void * *PCGPDFStringRef;

typedef void * CGPSConverterRef;

typedef unsigned CGRectCount;

typedef unsigned CGRectEdge;

typedef double CGRefreshRate;

typedef unsigned CGScreenUpdateOperation;

typedef unsigned *PCGScreenUpdateOperation;

typedef unsigned CGScrollEventUnit;

typedef void * CGShadingRef;

typedef unsigned CGTextDrawingMode;

typedef unsigned CGTextEncoding;

typedef unsigned CGWheelCount;

typedef unsigned CGWindowID;

typedef unsigned CGWindowImageOption;

typedef int CGWindowLevel;

typedef int CGWindowLevelKey;

typedef unsigned CGWindowListOption;

typedef Iosapi::Foundation::NSPoint CGPoint;

typedef Iosapi::Foundation::NSPoint *PCGPoint;

typedef Iosapi::Foundation::NSRect CGRect;

typedef Iosapi::Foundation::NSRect *PCGRect;

typedef Iosapi::Foundation::NSSize CGSize;

typedef Iosapi::Foundation::NSSize *PCGSize;

struct DECLSPEC_DRECORD CGVector
{
public:
	double dx;
	double dy;
};


typedef CGVector *PCGVector;

struct DECLSPEC_DRECORD CGAffineTransform
{
public:
	double a;
	double b;
	double c;
	double d;
	double tx;
	double ty;
	__fastcall CGAffineTransform(const double aa, const double ab, const double ac, const double ad, const double atx, const double aty);
	CGAffineTransform() {}
};


typedef CGAffineTransform *PCGAffineTransform;

typedef void __cdecl (*CGBitmapContextReleaseDataCallback)(void * releaseInfo, void * data);

typedef unsigned long __cdecl (*CGDataConsumerPutBytesCallback)(void * info, void * buffer, unsigned long count);

typedef void __cdecl (*CGDataConsumerReleaseInfoCallback)(void * info);

struct DECLSPEC_DRECORD CGDataConsumerCallbacks
{
public:
	CGDataConsumerPutBytesCallback putBytes;
	CGDataConsumerReleaseInfoCallback releaseConsumer;
};


typedef CGDataConsumerCallbacks *PCGDataConsumerCallbacks;

typedef unsigned long __cdecl (*CGDataProviderGetBytesCallback)(void * info, void * buffer, unsigned long count);

typedef void __cdecl (*CGDataProviderSkipBytesCallback)(void * info, unsigned long count);

typedef void __cdecl (*CGDataProviderRewindCallback)(void * info);

typedef void __cdecl (*CGDataProviderReleaseInfoCallback)(void * info);

typedef void * __cdecl (*CGDataProviderGetBytePointerCallback)(void * info);

typedef void __cdecl (*CGDataProviderReleaseBytePointerCallback)(void * info, void * ptr);

typedef unsigned long __cdecl (*CGDataProviderGetBytesAtPositionCallback)(void * info, void * buffer, __int64 position, unsigned long count);

typedef unsigned long __cdecl (*CGDataProviderGetBytesAtOffsetCallback)(void * info, void * buffer, unsigned long offset, unsigned long count);

typedef __int64 __cdecl (*CGDataProviderSkipForwardCallback)(void * info, unsigned long count);

typedef void __cdecl (*CGDataProviderReleaseDataCallback)(void * info, void * data, unsigned long size);

struct DECLSPEC_DRECORD CGDataProviderCallbacks
{
public:
	CGDataProviderGetBytesCallback getBytes;
	CGDataProviderSkipBytesCallback skipBytes;
	CGDataProviderRewindCallback rewind;
	CGDataProviderReleaseInfoCallback releaseProvider;
};


typedef CGDataProviderCallbacks *PCGDataProviderCallbacks;

struct DECLSPEC_DRECORD CGDataProviderDirectCallbacks
{
public:
	unsigned version;
	CGDataProviderGetBytePointerCallback getBytePointer;
	CGDataProviderReleaseBytePointerCallback releaseBytePointer;
	CGDataProviderGetBytesAtPositionCallback getBytesAtPosition;
	CGDataProviderReleaseInfoCallback releaseProvider;
};


typedef CGDataProviderDirectCallbacks *PCGDataProviderDirectCallbacks;

struct DECLSPEC_DRECORD CGDataProviderDirectAccessCallbacks
{
public:
	CGDataProviderGetBytePointerCallback getBytePointer;
	CGDataProviderReleaseBytePointerCallback releaseBytePointer;
	CGDataProviderGetBytesAtOffsetCallback getBytes;
	CGDataProviderReleaseInfoCallback releaseProvider;
};


typedef CGDataProviderDirectAccessCallbacks *PCGDataProviderDirectAccessCallbacks;

struct DECLSPEC_DRECORD CGDataProviderSequentialCallbacks
{
public:
	unsigned version;
	CGDataProviderGetBytesCallback getBytes;
	CGDataProviderSkipForwardCallback skipForward;
	CGDataProviderRewindCallback rewind;
	CGDataProviderReleaseInfoCallback releaseInfo;
};


typedef CGDataProviderSequentialCallbacks *PCGDataProviderSequentialCallbacks;

struct DECLSPEC_DRECORD CGDeviceColor
{
public:
	float red;
	float green;
	float blue;
};


typedef CGDeviceColor *PCGDeviceColor;

struct DECLSPEC_DRECORD CGDeviceByteColor
{
public:
	System::Byte red;
	System::Byte green;
	System::Byte blue;
};


typedef CGDeviceByteColor *PCGDeviceByteColor;

typedef void __cdecl (*CGFunctionEvaluateCallback)(void * info, Iosapi::Cocoatypes::PCGFloat inData, Iosapi::Cocoatypes::PCGFloat outData);

typedef void __cdecl (*CGFunctionReleaseInfoCallback)(void * info);

struct DECLSPEC_DRECORD CGFunctionCallbacks
{
public:
	unsigned version;
	CGFunctionEvaluateCallback evaluate;
	CGFunctionReleaseInfoCallback releaseInfo;
};


typedef CGFunctionCallbacks *PCGFunctionCallbacks;

typedef void __cdecl (*CGPDFDictionaryApplierFunction)(char * key, void * value, void * info);

typedef void __cdecl (*CGPDFOperatorCallback)(void * scanner, void * info);

struct DECLSPEC_DRECORD CGPathElement
{
public:
	unsigned type_;
	Iosapi::Foundation::NSPoint *points;
};


typedef CGPathElement *PCGPathElement;

typedef void __cdecl (*CGPathApplierFunction)(void * info, const PCGPathElement element);

typedef void __cdecl (*CGPatternDrawPatternCallback)(void * info, void * context);

typedef void __cdecl (*CGPatternReleaseInfoCallback)(void * info);

struct DECLSPEC_DRECORD CGPatternCallbacks
{
public:
	unsigned version;
	CGPatternDrawPatternCallback drawPattern;
	CGPatternReleaseInfoCallback releaseInfo;
};


typedef CGPatternCallbacks *PCGPatternCallbacks;

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 CGFLOAT_DEFINED = System::Int8(0x1);
static constexpr System::Int8 CGFLOAT_IS_DOUBLE = System::Int8(0x0);
static const double CGFLOAT_MAX = 3.402823E+38;
static const double CGFLOAT_MIN = 1.175494E-38;
static constexpr System::Word CGGlyphMax = System::Word(0xfffe);
static constexpr System::Int8 CGGlyphMin = System::Int8(0x0);
static constexpr System::Int8 CGPDFDataFormatJPEG2000 = System::Int8(0x2);
static constexpr System::Int8 CGPDFDataFormatJPEGEncoded = System::Int8(0x1);
static constexpr System::Int8 CGPDFDataFormatRaw = System::Int8(0x0);
static constexpr System::Int8 CGRectMaxXEdge = System::Int8(0x2);
static constexpr System::Int8 CGRectMaxYEdge = System::Int8(0x3);
static constexpr System::Int8 CGRectMinXEdge = System::Int8(0x0);
static constexpr System::Int8 CGRectMinYEdge = System::Int8(0x1);
static constexpr System::Int8 kCGBitmapAlphaInfoMask = System::Int8(0x1f);
static constexpr System::Word kCGBitmapByteOrder16Big = System::Word(0x3000);
static constexpr System::Word kCGBitmapByteOrder16Host = System::Word(0x1000);
static constexpr System::Word kCGBitmapByteOrder16Little = System::Word(0x1000);
static constexpr System::Word kCGBitmapByteOrder32Big = System::Word(0x4000);
static constexpr System::Word kCGBitmapByteOrder32Host = System::Word(0x2000);
static constexpr System::Word kCGBitmapByteOrder32Little = System::Word(0x2000);
static constexpr System::Int8 kCGBitmapByteOrderDefault = System::Int8(0x0);
static constexpr System::Word kCGBitmapByteOrderMask = System::Word(0x7000);
static constexpr System::Word kCGBitmapFloatComponents = System::Word(0x100);
static constexpr System::Int8 kCGBlendModeClear = System::Int8(0x10);
static constexpr System::Int8 kCGBlendModeColor = System::Int8(0xe);
static constexpr System::Int8 kCGBlendModeColorBurn = System::Int8(0x7);
static constexpr System::Int8 kCGBlendModeColorDodge = System::Int8(0x6);
static constexpr System::Int8 kCGBlendModeCopy = System::Int8(0x11);
static constexpr System::Int8 kCGBlendModeDarken = System::Int8(0x4);
static constexpr System::Int8 kCGBlendModeDestinationAtop = System::Int8(0x18);
static constexpr System::Int8 kCGBlendModeDestinationIn = System::Int8(0x16);
static constexpr System::Int8 kCGBlendModeDestinationOut = System::Int8(0x17);
static constexpr System::Int8 kCGBlendModeDestinationOver = System::Int8(0x15);
static constexpr System::Int8 kCGBlendModeDifference = System::Int8(0xa);
static constexpr System::Int8 kCGBlendModeExclusion = System::Int8(0xb);
static constexpr System::Int8 kCGBlendModeHardLight = System::Int8(0x9);
static constexpr System::Int8 kCGBlendModeHue = System::Int8(0xc);
static constexpr System::Int8 kCGBlendModeLighten = System::Int8(0x5);
static constexpr System::Int8 kCGBlendModeLuminosity = System::Int8(0xf);
static constexpr System::Int8 kCGBlendModeMultiply = System::Int8(0x1);
static constexpr System::Int8 kCGBlendModeNormal = System::Int8(0x0);
static constexpr System::Int8 kCGBlendModeOverlay = System::Int8(0x3);
static constexpr System::Int8 kCGBlendModePlusDarker = System::Int8(0x1a);
static constexpr System::Int8 kCGBlendModePlusLighter = System::Int8(0x1b);
static constexpr System::Int8 kCGBlendModeSaturation = System::Int8(0xd);
static constexpr System::Int8 kCGBlendModeScreen = System::Int8(0x2);
static constexpr System::Int8 kCGBlendModeSoftLight = System::Int8(0x8);
static constexpr System::Int8 kCGBlendModeSourceAtop = System::Int8(0x14);
static constexpr System::Int8 kCGBlendModeSourceIn = System::Int8(0x12);
static constexpr System::Int8 kCGBlendModeSourceOut = System::Int8(0x13);
static constexpr System::Int8 kCGBlendModeXOR = System::Int8(0x19);
static constexpr System::Int8 kCGColorSpaceModelCMYK = System::Int8(0x2);
static constexpr System::Int8 kCGColorSpaceModelDeviceN = System::Int8(0x4);
static constexpr System::Int8 kCGColorSpaceModelIndexed = System::Int8(0x5);
static constexpr System::Int8 kCGColorSpaceModelLab = System::Int8(0x3);
static constexpr System::Int8 kCGColorSpaceModelMonochrome = System::Int8(0x0);
static constexpr System::Int8 kCGColorSpaceModelPattern = System::Int8(0x6);
static constexpr System::Int8 kCGColorSpaceModelRGB = System::Int8(0x1);
static constexpr System::Int8 kCGColorSpaceModelUnknown = System::Int8(-1);
static constexpr System::Int8 kCGEncodingFontSpecific = System::Int8(0x0);
static constexpr System::Int8 kCGEncodingMacRoman = System::Int8(0x1);
static constexpr System::Word kCGErrorApplicationAlreadyRunning = System::Word(0x401);
static constexpr System::Word kCGErrorApplicationCanOnlyBeRunInOneSessionAtATime = System::Word(0x402);
static constexpr System::Word kCGErrorApplicationIncorrectExecutableFormatFound = System::Word(0x3ff);
static constexpr System::Word kCGErrorApplicationIsLaunching = System::Word(0x400);
static constexpr System::Word kCGErrorApplicationNotPermittedToExecute = System::Word(0x3f8);
static constexpr System::Word kCGErrorApplicationRequiresNewerSystem = System::Word(0x3f7);
static constexpr System::Word kCGErrorCannotComplete = System::Word(0x3ec);
static constexpr System::Word kCGErrorClassicApplicationsMustBeLaunchedByClassic = System::Word(0x403);
static constexpr System::Word kCGErrorFailure = System::Word(0x3e8);
static constexpr System::Word kCGErrorFirst = System::Word(0x3e8);
static constexpr System::Word kCGErrorForkFailed = System::Word(0x404);
static constexpr System::Word kCGErrorIllegalArgument = System::Word(0x3e9);
static constexpr System::Word kCGErrorInvalidConnection = System::Word(0x3ea);
static constexpr System::Word kCGErrorInvalidContext = System::Word(0x3eb);
static constexpr System::Word kCGErrorInvalidOperation = System::Word(0x3f2);
static constexpr System::Word kCGErrorLast = System::Word(0x405);
static constexpr System::Word kCGErrorNameTooLong = System::Word(0x3ed);
static constexpr System::Word kCGErrorNoCurrentPoint = System::Word(0x3f1);
static constexpr System::Word kCGErrorNoneAvailable = System::Word(0x3f3);
static constexpr System::Word kCGErrorNotImplemented = System::Word(0x3ee);
static constexpr System::Word kCGErrorRangeCheck = System::Word(0x3ef);
static constexpr System::Word kCGErrorRetryRegistration = System::Word(0x405);
static constexpr System::Int8 kCGErrorSuccess = System::Int8(0x0);
static constexpr System::Word kCGErrorTypeCheck = System::Word(0x3f0);
static constexpr System::Word kCGFontIndexInvalid = System::Word(0xffff);
static constexpr System::Word kCGFontIndexMax = System::Word(0xfffe);
static constexpr System::Int8 kCGFontPostScriptFormatType1 = System::Int8(0x1);
static constexpr System::Int8 kCGFontPostScriptFormatType3 = System::Int8(0x3);
static constexpr System::Int8 kCGFontPostScriptFormatType42 = System::Int8(0x2a);
static constexpr System::Word kCGGlyphMax = System::Word(0xfffe);
static constexpr System::Int8 kCGGradientDrawsAfterEndLocation = System::Int8(0x2);
static constexpr System::Int8 kCGGradientDrawsBeforeStartLocation = System::Int8(0x1);
static constexpr System::Int8 kCGImageAlphaFirst = System::Int8(0x4);
static constexpr System::Int8 kCGImageAlphaLast = System::Int8(0x3);
static constexpr System::Int8 kCGImageAlphaNone = System::Int8(0x0);
static constexpr System::Int8 kCGImageAlphaNoneSkipFirst = System::Int8(0x6);
static constexpr System::Int8 kCGImageAlphaNoneSkipLast = System::Int8(0x5);
static constexpr System::Int8 kCGImageAlphaOnly = System::Int8(0x7);
static constexpr System::Int8 kCGImageAlphaPremultipliedFirst = System::Int8(0x2);
static constexpr System::Int8 kCGImageAlphaPremultipliedLast = System::Int8(0x1);
static constexpr System::Int8 kCGInterpolationDefault = System::Int8(0x0);
static constexpr System::Int8 kCGInterpolationHigh = System::Int8(0x3);
static constexpr System::Int8 kCGInterpolationLow = System::Int8(0x2);
static constexpr System::Int8 kCGInterpolationMedium = System::Int8(0x4);
static constexpr System::Int8 kCGInterpolationNone = System::Int8(0x1);
static constexpr System::Int8 kCGLineCapButt = System::Int8(0x0);
static constexpr System::Int8 kCGLineCapRound = System::Int8(0x1);
static constexpr System::Int8 kCGLineCapSquare = System::Int8(0x2);
static constexpr System::Int8 kCGLineJoinBevel = System::Int8(0x2);
static constexpr System::Int8 kCGLineJoinMiter = System::Int8(0x0);
static constexpr System::Int8 kCGLineJoinRound = System::Int8(0x1);
static constexpr System::Int8 kCGPDFArtBox = System::Int8(0x4);
static constexpr System::Int8 kCGPDFBleedBox = System::Int8(0x2);
static constexpr System::Int8 kCGPDFCropBox = System::Int8(0x1);
static constexpr System::Int8 kCGPDFMediaBox = System::Int8(0x0);
static constexpr System::Int8 kCGPDFObjectTypeArray = System::Int8(0x7);
static constexpr System::Int8 kCGPDFObjectTypeBoolean = System::Int8(0x2);
static constexpr System::Int8 kCGPDFObjectTypeDictionary = System::Int8(0x8);
static constexpr System::Int8 kCGPDFObjectTypeInteger = System::Int8(0x3);
static constexpr System::Int8 kCGPDFObjectTypeName = System::Int8(0x5);
static constexpr System::Int8 kCGPDFObjectTypeNull = System::Int8(0x1);
static constexpr System::Int8 kCGPDFObjectTypeReal = System::Int8(0x4);
static constexpr System::Int8 kCGPDFObjectTypeStream = System::Int8(0x9);
static constexpr System::Int8 kCGPDFObjectTypeString = System::Int8(0x6);
static constexpr System::Int8 kCGPDFTrimBox = System::Int8(0x3);
static constexpr System::Int8 kCGPathEOFill = System::Int8(0x1);
static constexpr System::Int8 kCGPathEOFillStroke = System::Int8(0x4);
static constexpr System::Int8 kCGPathElementAddCurveToPoint = System::Int8(0x3);
static constexpr System::Int8 kCGPathElementAddLineToPoint = System::Int8(0x1);
static constexpr System::Int8 kCGPathElementAddQuadCurveToPoint = System::Int8(0x2);
static constexpr System::Int8 kCGPathElementCloseSubpath = System::Int8(0x4);
static constexpr System::Int8 kCGPathElementMoveToPoint = System::Int8(0x0);
static constexpr System::Int8 kCGPathFill = System::Int8(0x0);
static constexpr System::Int8 kCGPathFillStroke = System::Int8(0x3);
static constexpr System::Int8 kCGPathStroke = System::Int8(0x2);
static constexpr System::Int8 kCGPatternTilingConstantSpacing = System::Int8(0x2);
static constexpr System::Int8 kCGPatternTilingConstantSpacingMinimalDistortion = System::Int8(0x1);
static constexpr System::Int8 kCGPatternTilingNoDistortion = System::Int8(0x0);
static constexpr System::Int8 kCGRenderingIntentAbsoluteColorimetric = System::Int8(0x1);
static constexpr System::Int8 kCGRenderingIntentDefault = System::Int8(0x0);
static constexpr System::Int8 kCGRenderingIntentPerceptual = System::Int8(0x3);
static constexpr System::Int8 kCGRenderingIntentRelativeColorimetric = System::Int8(0x2);
static constexpr System::Int8 kCGRenderingIntentSaturation = System::Int8(0x4);
static constexpr System::Int8 kCGTextClip = System::Int8(0x7);
static constexpr System::Int8 kCGTextFill = System::Int8(0x0);
static constexpr System::Int8 kCGTextFillClip = System::Int8(0x4);
static constexpr System::Int8 kCGTextFillStroke = System::Int8(0x2);
static constexpr System::Int8 kCGTextFillStrokeClip = System::Int8(0x6);
static constexpr System::Int8 kCGTextInvisible = System::Int8(0x3);
static constexpr System::Int8 kCGTextStroke = System::Int8(0x1);
static constexpr System::Int8 kCGTextStrokeClip = System::Int8(0x5);
#define libCoreGraphics u"/System/Library/Frameworks/CoreGraphics.framework/CoreGrap"\
	u"hics"
extern "C" CGAffineTransform __cdecl CGAffineTransformConcat(CGAffineTransform t1, CGAffineTransform t2);
extern "C" bool __cdecl CGAffineTransformEqualToTransform(CGAffineTransform t1, CGAffineTransform t2);
extern "C" CGAffineTransform __cdecl CGAffineTransformInvert(CGAffineTransform t);
extern "C" bool __cdecl CGAffineTransformIsIdentity(CGAffineTransform t);
extern "C" CGAffineTransform __cdecl CGAffineTransformMake(double a, double b, double c, double d, double tx, double ty);
extern "C" CGAffineTransform __cdecl CGAffineTransformMakeRotation(double angle);
extern "C" CGAffineTransform __cdecl CGAffineTransformMakeScale(double sx, double sy);
extern "C" CGAffineTransform __cdecl CGAffineTransformMakeTranslation(double tx, double ty);
extern "C" CGAffineTransform __cdecl CGAffineTransformRotate(CGAffineTransform t, double angle);
extern "C" CGAffineTransform __cdecl CGAffineTransformScale(CGAffineTransform t, double sx, double sy);
extern "C" CGAffineTransform __cdecl CGAffineTransformTranslate(CGAffineTransform t, double tx, double ty);
extern "C" void * __cdecl CGBitmapContextCreate(void * data, unsigned long width, unsigned long height, unsigned long bitsPerComponent, unsigned long bytesPerRow, void * space, unsigned bitmapInfo);
extern "C" void * __cdecl CGBitmapContextCreateImage(void * context);
extern "C" void * __cdecl CGBitmapContextCreateWithData(void * data, unsigned long width, unsigned long height, unsigned long bitsPerComponent, unsigned long bytesPerRow, void * space, unsigned bitmapInfo, CGBitmapContextReleaseDataCallback releaseCallback, void * releaseInfo);
extern "C" unsigned __cdecl CGBitmapContextGetAlphaInfo(void * context);
extern "C" unsigned __cdecl CGBitmapContextGetBitmapInfo(void * context);
extern "C" unsigned long __cdecl CGBitmapContextGetBitsPerComponent(void * context);
extern "C" unsigned long __cdecl CGBitmapContextGetBitsPerPixel(void * context);
extern "C" unsigned long __cdecl CGBitmapContextGetBytesPerRow(void * context);
extern "C" void * __cdecl CGBitmapContextGetColorSpace(void * context);
extern "C" void * __cdecl CGBitmapContextGetData(void * context);
extern "C" unsigned long __cdecl CGBitmapContextGetHeight(void * context);
extern "C" unsigned long __cdecl CGBitmapContextGetWidth(void * context);
extern "C" void * __cdecl CGColorCreate(void * space, Iosapi::Cocoatypes::PCGFloat components);
extern "C" void * __cdecl CGColorCreateCopy(void * color);
extern "C" void * __cdecl CGColorCreateCopyWithAlpha(void * color, double alpha);
extern "C" void * __cdecl CGColorCreateGenericCMYK(double cyan, double magenta, double yellow, double black, double alpha);
extern "C" void * __cdecl CGColorCreateGenericGray(double gray, double alpha);
extern "C" void * __cdecl CGColorCreateGenericRGB(double red, double green, double blue, double alpha);
extern "C" void * __cdecl CGColorCreateWithPattern(void * space, void * pattern, Iosapi::Cocoatypes::PCGFloat components);
extern "C" bool __cdecl CGColorEqualToColor(void * color1, void * color2);
extern "C" double __cdecl CGColorGetAlpha(void * color);
extern "C" void * __cdecl CGColorGetColorSpace(void * color);
extern "C" Iosapi::Cocoatypes::PCGFloat __cdecl CGColorGetComponents(void * color);
extern "C" void * __cdecl CGColorGetConstantColor(CFStringRef colorName);
extern "C" unsigned long __cdecl CGColorGetNumberOfComponents(void * color);
extern "C" void * __cdecl CGColorGetPattern(void * color);
extern "C" unsigned long __cdecl CGColorGetTypeID(void);
extern "C" void __cdecl CGColorRelease(void * color);
extern "C" void * __cdecl CGColorRetain(void * color);
extern "C" CFDataRef __cdecl CGColorSpaceCopyICCProfile(void * space);
extern "C" CFStringRef __cdecl CGColorSpaceCopyName(void * space);
extern "C" void * __cdecl CGColorSpaceCreateCalibratedGray(Iosapi::Cocoatypes::PCGFloat whitePoint, Iosapi::Cocoatypes::PCGFloat blackPoint, double gamma);
extern "C" void * __cdecl CGColorSpaceCreateCalibratedRGB(Iosapi::Cocoatypes::PCGFloat whitePoint, Iosapi::Cocoatypes::PCGFloat blackPoint, Iosapi::Cocoatypes::PCGFloat gamma, Iosapi::Cocoatypes::PCGFloat matrix);
extern "C" void * __cdecl CGColorSpaceCreateDeviceCMYK(void);
extern "C" void * __cdecl CGColorSpaceCreateDeviceGray(void);
extern "C" void * __cdecl CGColorSpaceCreateDeviceRGB(void);
extern "C" void * __cdecl CGColorSpaceCreateICCBased(unsigned long nComponents, Iosapi::Cocoatypes::PCGFloat range, void * profile, void * alternate);
extern "C" void * __cdecl CGColorSpaceCreateIndexed(void * baseSpace, unsigned long lastIndex, System::PByte colorTable);
extern "C" void * __cdecl CGColorSpaceCreateLab(Iosapi::Cocoatypes::PCGFloat whitePoint, Iosapi::Cocoatypes::PCGFloat blackPoint, Iosapi::Cocoatypes::PCGFloat range);
extern "C" void * __cdecl CGColorSpaceCreatePattern(void * baseSpace);
extern "C" void * __cdecl CGColorSpaceCreateWithICCProfile(CFDataRef data);
extern "C" void * __cdecl CGColorSpaceCreateWithName(CFStringRef name);
extern "C" void * __cdecl CGColorSpaceCreateWithPlatformColorSpace(void * ref);
extern "C" void * __cdecl CGColorSpaceGetBaseColorSpace(void * space);
extern "C" void __cdecl CGColorSpaceGetColorTable(void * space, System::PByte table);
extern "C" unsigned long __cdecl CGColorSpaceGetColorTableCount(void * space);
extern "C" int __cdecl CGColorSpaceGetModel(void * space);
extern "C" unsigned long __cdecl CGColorSpaceGetNumberOfComponents(void * space);
extern "C" unsigned long __cdecl CGColorSpaceGetTypeID(void);
extern "C" void __cdecl CGColorSpaceRelease(void * space);
extern "C" void * __cdecl CGColorSpaceRetain(void * space);
extern "C" void __cdecl CGContextAddArc(void * c, double x, double y, double radius, double startAngle, double endAngle, bool clockwise);
extern "C" void __cdecl CGContextAddArcToPoint(void * c, double x1, double y1, double x2, double y2, double radius);
extern "C" void __cdecl CGContextAddCurveToPoint(void * c, double cp1x, double cp1y, double cp2x, double cp2y, double x, double y);
extern "C" void __cdecl CGContextAddEllipseInRect(void * context, Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl CGContextAddLineToPoint(void * c, double x, double y);
extern "C" void __cdecl CGContextAddLines(void * c, PCGPoint points, unsigned long count);
extern "C" void __cdecl CGContextAddPath(void * context, void * path);
extern "C" void __cdecl CGContextAddQuadCurveToPoint(void * c, double cpx, double cpy, double x, double y);
extern "C" void __cdecl CGContextAddRect(void * c, Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl CGContextAddRects(void * c, PCGRect rects, unsigned long count);
extern "C" void __cdecl CGContextBeginPage(void * c, PCGRect mediaBox);
extern "C" void __cdecl CGContextBeginPath(void * c);
extern "C" void __cdecl CGContextBeginTransparencyLayer(void * context, CFDictionaryRef auxiliaryInfo);
extern "C" void __cdecl CGContextBeginTransparencyLayerWithRect(void * context, Iosapi::Foundation::NSRect rect, CFDictionaryRef auxiliaryInfo);
extern "C" void __cdecl CGContextClearRect(void * c, Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl CGContextClip(void * c);
extern "C" void __cdecl CGContextClipToMask(void * c, Iosapi::Foundation::NSRect rect, void * mask);
extern "C" void __cdecl CGContextClipToRect(void * c, Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl CGContextClipToRects(void * c, PCGRect rects, unsigned long count);
extern "C" void __cdecl CGContextClosePath(void * c);
extern "C" void __cdecl CGContextConcatCTM(void * c, CGAffineTransform transform);
extern "C" Iosapi::Foundation::NSPoint __cdecl CGContextConvertPointToDeviceSpace(void * context, Iosapi::Foundation::NSPoint point);
extern "C" Iosapi::Foundation::NSPoint __cdecl CGContextConvertPointToUserSpace(void * context, Iosapi::Foundation::NSPoint point);
extern "C" Iosapi::Foundation::NSRect __cdecl CGContextConvertRectToDeviceSpace(void * context, Iosapi::Foundation::NSRect rect);
extern "C" Iosapi::Foundation::NSRect __cdecl CGContextConvertRectToUserSpace(void * context, Iosapi::Foundation::NSRect rect);
extern "C" Iosapi::Foundation::NSSize __cdecl CGContextConvertSizeToDeviceSpace(void * context, Iosapi::Foundation::NSSize size);
extern "C" Iosapi::Foundation::NSSize __cdecl CGContextConvertSizeToUserSpace(void * context, Iosapi::Foundation::NSSize size);
extern "C" void * __cdecl CGContextCopyPath(void * context);
extern "C" void __cdecl CGContextDrawImage(void * c, Iosapi::Foundation::NSRect rect, void * image);
extern "C" void __cdecl CGContextDrawLayerAtPoint(void * context, Iosapi::Foundation::NSPoint point, void * layer);
extern "C" void __cdecl CGContextDrawLayerInRect(void * context, Iosapi::Foundation::NSRect rect, void * layer);
extern "C" void __cdecl CGContextDrawLinearGradient(void * context, void * gradient, Iosapi::Foundation::NSPoint startPoint, Iosapi::Foundation::NSPoint endPoint, unsigned options);
extern "C" void __cdecl CGContextDrawPDFDocument(void * c, Iosapi::Foundation::NSRect rect, void * document, int page);
extern "C" void __cdecl CGContextDrawPDFPage(void * c, void * page);
extern "C" void __cdecl CGContextDrawPath(void * c, unsigned mode);
extern "C" void __cdecl CGContextDrawRadialGradient(void * context, void * gradient, Iosapi::Foundation::NSPoint startCenter, double startRadius, Iosapi::Foundation::NSPoint endCenter, double endRadius, unsigned options);
extern "C" void __cdecl CGContextDrawShading(void * context, void * shading);
extern "C" void __cdecl CGContextDrawTiledImage(void * c, Iosapi::Foundation::NSRect rect, void * image);
extern "C" void __cdecl CGContextEOClip(void * c);
extern "C" void __cdecl CGContextEOFillPath(void * c);
extern "C" void __cdecl CGContextEndPage(void * c);
extern "C" void __cdecl CGContextEndTransparencyLayer(void * context);
extern "C" void __cdecl CGContextFillEllipseInRect(void * context, Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl CGContextFillPath(void * c);
extern "C" void __cdecl CGContextFillRect(void * c, Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl CGContextFillRects(void * c, PCGRect rects, unsigned long count);
extern "C" void __cdecl CGContextFlush(void * c);
extern "C" CGAffineTransform __cdecl CGContextGetCTM(void * c);
extern "C" Iosapi::Foundation::NSRect __cdecl CGContextGetClipBoundingBox(void * c);
extern "C" unsigned __cdecl CGContextGetInterpolationQuality(void * context);
extern "C" Iosapi::Foundation::NSRect __cdecl CGContextGetPathBoundingBox(void * context);
extern "C" Iosapi::Foundation::NSPoint __cdecl CGContextGetPathCurrentPoint(void * context);
extern "C" CGAffineTransform __cdecl CGContextGetTextMatrix(void * c);
extern "C" Iosapi::Foundation::NSPoint __cdecl CGContextGetTextPosition(void * context);
extern "C" unsigned long __cdecl CGContextGetTypeID(void);
extern "C" CGAffineTransform __cdecl CGContextGetUserSpaceToDeviceSpaceTransform(void * context);
extern "C" bool __cdecl CGContextIsPathEmpty(void * context);
extern "C" void __cdecl CGContextMoveToPoint(void * c, double x, double y);
extern "C" bool __cdecl CGContextPathContainsPoint(void * context, Iosapi::Foundation::NSPoint point, unsigned mode);
extern "C" void __cdecl CGContextRelease(void * c);
extern "C" void __cdecl CGContextReplacePathWithStrokedPath(void * c);
extern "C" void __cdecl CGContextRestoreGState(void * c);
extern "C" void * __cdecl CGContextRetain(void * c);
extern "C" void __cdecl CGContextRotateCTM(void * c, double angle);
extern "C" void __cdecl CGContextSaveGState(void * c);
extern "C" void __cdecl CGContextScaleCTM(void * c, double sx, double sy);
extern "C" void __cdecl CGContextSelectFont(void * c, char * name, double size, unsigned textEncoding);
extern "C" void __cdecl CGContextSetAllowsAntialiasing(void * context, bool allowsAntialiasing);
extern "C" void __cdecl CGContextSetAllowsFontSmoothing(void * context, bool allowsFontSmoothing);
extern "C" void __cdecl CGContextSetAllowsFontSubpixelPositioning(void * context, bool allowsFontSubpixelPositioning);
extern "C" void __cdecl CGContextSetAllowsFontSubpixelQuantization(void * context, bool allowsFontSubpixelQuantization);
extern "C" void __cdecl CGContextSetAlpha(void * c, double alpha);
extern "C" void __cdecl CGContextSetBlendMode(void * context, unsigned mode);
extern "C" void __cdecl CGContextSetCMYKFillColor(void * context, double cyan, double magenta, double yellow, double black, double alpha);
extern "C" void __cdecl CGContextSetCMYKStrokeColor(void * context, double cyan, double magenta, double yellow, double black, double alpha);
extern "C" void __cdecl CGContextSetCharacterSpacing(void * context, double spacing);
extern "C" void __cdecl CGContextSetFillColor(void * context, Iosapi::Cocoatypes::PCGFloat components);
extern "C" void __cdecl CGContextSetFillColorSpace(void * context, void * space);
extern "C" void __cdecl CGContextSetFillColorWithColor(void * c, void * color);
extern "C" void __cdecl CGContextSetFillPattern(void * context, void * pattern, Iosapi::Cocoatypes::PCGFloat components);
extern "C" void __cdecl CGContextSetFlatness(void * c, double flatness);
extern "C" void __cdecl CGContextSetFont(void * c, void * font);
extern "C" void __cdecl CGContextSetFontSize(void * c, double size);
extern "C" void __cdecl CGContextSetGrayFillColor(void * context, double gray, double alpha);
extern "C" void __cdecl CGContextSetGrayStrokeColor(void * context, double gray, double alpha);
extern "C" void __cdecl CGContextSetInterpolationQuality(void * context, unsigned quality);
extern "C" void __cdecl CGContextSetLineCap(void * c, unsigned cap);
extern "C" void __cdecl CGContextSetLineDash(void * c, double phase, Iosapi::Cocoatypes::PCGFloat lengths, unsigned long count);
extern "C" void __cdecl CGContextSetLineJoin(void * c, unsigned join);
extern "C" void __cdecl CGContextSetLineWidth(void * c, double width);
extern "C" void __cdecl CGContextSetMiterLimit(void * c, double limit);
extern "C" void __cdecl CGContextSetPatternPhase(void * context, Iosapi::Foundation::NSSize phase);
extern "C" void __cdecl CGContextSetRGBFillColor(void * context, double red, double green, double blue, double alpha);
extern "C" void __cdecl CGContextSetRGBStrokeColor(void * context, double red, double green, double blue, double alpha);
extern "C" void __cdecl CGContextSetRenderingIntent(void * context, unsigned intent);
extern "C" void __cdecl CGContextSetShadow(void * context, Iosapi::Foundation::NSSize offset, double blur);
extern "C" void __cdecl CGContextSetShadowWithColor(void * context, Iosapi::Foundation::NSSize offset, double blur, void * color);
extern "C" void __cdecl CGContextSetShouldAntialias(void * context, bool shouldAntialias);
extern "C" void __cdecl CGContextSetShouldSmoothFonts(void * context, bool shouldSmoothFonts);
extern "C" void __cdecl CGContextSetShouldSubpixelPositionFonts(void * context, bool shouldSubpixelPositionFonts);
extern "C" void __cdecl CGContextSetShouldSubpixelQuantizeFonts(void * context, bool shouldSubpixelQuantizeFonts);
extern "C" void __cdecl CGContextSetStrokeColor(void * context, Iosapi::Cocoatypes::PCGFloat components);
extern "C" void __cdecl CGContextSetStrokeColorSpace(void * context, void * space);
extern "C" void __cdecl CGContextSetStrokeColorWithColor(void * c, void * color);
extern "C" void __cdecl CGContextSetStrokePattern(void * context, void * pattern, Iosapi::Cocoatypes::PCGFloat components);
extern "C" void __cdecl CGContextSetTextDrawingMode(void * c, unsigned mode);
extern "C" void __cdecl CGContextSetTextMatrix(void * c, CGAffineTransform t);
extern "C" void __cdecl CGContextSetTextPosition(void * c, double x, double y);
extern "C" void __cdecl CGContextShowGlyphs(void * c, PCGGlyph g, unsigned long count);
extern "C" void __cdecl CGContextShowGlyphsAtPoint(void * context, double x, double y, PCGGlyph glyphs, unsigned long count);
extern "C" void __cdecl CGContextShowGlyphsAtPositions(void * context, PCGGlyph glyphs, PCGPoint positions, unsigned long count);
extern "C" void __cdecl CGContextShowGlyphsWithAdvances(void * c, PCGGlyph glyphs, PCGSize advances, unsigned long count);
extern "C" void __cdecl CGContextShowText(void * c, char * string_, unsigned long length);
extern "C" void __cdecl CGContextShowTextAtPoint(void * c, double x, double y, char * string_, unsigned long length);
extern "C" void __cdecl CGContextStrokeEllipseInRect(void * context, Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl CGContextStrokeLineSegments(void * c, PCGPoint points, unsigned long count);
extern "C" void __cdecl CGContextStrokePath(void * c);
extern "C" void __cdecl CGContextStrokeRect(void * c, Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl CGContextStrokeRectWithWidth(void * c, Iosapi::Foundation::NSRect rect, double width);
extern "C" void __cdecl CGContextSynchronize(void * c);
extern "C" void __cdecl CGContextTranslateCTM(void * c, double tx, double ty);
extern "C" void * __cdecl CGDataConsumerCreate(void * info, PCGDataConsumerCallbacks callbacks);
extern "C" void * __cdecl CGDataConsumerCreateWithCFData(CFMutableDataRef data);
extern "C" void * __cdecl CGDataConsumerCreateWithURL(CFURLRef url);
extern "C" unsigned long __cdecl CGDataConsumerGetTypeID(void);
extern "C" void __cdecl CGDataConsumerRelease(void * consumer);
extern "C" void * __cdecl CGDataConsumerRetain(void * consumer);
extern "C" CFDataRef __cdecl CGDataProviderCopyData(void * provider);
extern "C" void * __cdecl CGDataProviderCreate(void * info, PCGDataProviderCallbacks callbacks);
extern "C" void * __cdecl CGDataProviderCreateDirect(void * info, __int64 size, PCGDataProviderDirectCallbacks callbacks);
extern "C" void * __cdecl CGDataProviderCreateDirectAccess(void * info, unsigned long size, PCGDataProviderDirectAccessCallbacks callbacks);
extern "C" void * __cdecl CGDataProviderCreateSequential(void * info, PCGDataProviderSequentialCallbacks callbacks);
extern "C" void * __cdecl CGDataProviderCreateWithCFData(CFDataRef data);
extern "C" void * __cdecl CGDataProviderCreateWithData(void * info, void * data, unsigned long size, CGDataProviderReleaseDataCallback releaseData);
extern "C" void * __cdecl CGDataProviderCreateWithFilename(char * filename);
extern "C" void * __cdecl CGDataProviderCreateWithURL(CFURLRef url);
extern "C" unsigned long __cdecl CGDataProviderGetTypeID(void);
extern "C" void __cdecl CGDataProviderRelease(void * provider);
extern "C" void * __cdecl CGDataProviderRetain(void * provider);
extern "C" bool __cdecl CGFontCanCreatePostScriptSubset(void * font, unsigned format);
extern "C" CFStringRef __cdecl CGFontCopyFullName(void * font);
extern "C" CFStringRef __cdecl CGFontCopyGlyphNameForGlyph(void * font, System::Word glyph);
extern "C" CFStringRef __cdecl CGFontCopyPostScriptName(void * font);
extern "C" CFDataRef __cdecl CGFontCopyTableForTag(void * font, unsigned tag);
extern "C" CFArrayRef __cdecl CGFontCopyTableTags(void * font);
extern "C" CFArrayRef __cdecl CGFontCopyVariationAxes(void * font);
extern "C" CFDictionaryRef __cdecl CGFontCopyVariations(void * font);
extern "C" void * __cdecl CGFontCreateCopyWithVariations(void * font, CFDictionaryRef variations);
extern "C" CFDataRef __cdecl CGFontCreatePostScriptEncoding(void * font, PCGGlyph encoding);
extern "C" CFDataRef __cdecl CGFontCreatePostScriptSubset(void * font, CFStringRef subsetName, unsigned format, PCGGlyph glyphs, unsigned long count, PCGGlyph encoding);
extern "C" void * __cdecl CGFontCreateWithDataProvider(void * provider);
extern "C" void * __cdecl CGFontCreateWithFontName(CFStringRef name);
extern "C" void * __cdecl CGFontCreateWithPlatformFont(void * platformFontReference);
extern "C" int __cdecl CGFontGetAscent(void * font);
extern "C" int __cdecl CGFontGetCapHeight(void * font);
extern "C" int __cdecl CGFontGetDescent(void * font);
extern "C" Iosapi::Foundation::NSRect __cdecl CGFontGetFontBBox(void * font);
extern "C" bool __cdecl CGFontGetGlyphAdvances(void * font, PCGGlyph glyphs, unsigned long count, System::PInteger advances);
extern "C" bool __cdecl CGFontGetGlyphBBoxes(void * font, PCGGlyph glyphs, unsigned long count, PCGRect bboxes);
extern "C" System::Word __cdecl CGFontGetGlyphWithGlyphName(void * font, CFStringRef name);
extern "C" double __cdecl CGFontGetItalicAngle(void * font);
extern "C" int __cdecl CGFontGetLeading(void * font);
extern "C" unsigned long __cdecl CGFontGetNumberOfGlyphs(void * font);
extern "C" double __cdecl CGFontGetStemV(void * font);
extern "C" unsigned long __cdecl CGFontGetTypeID(void);
extern "C" int __cdecl CGFontGetUnitsPerEm(void * font);
extern "C" int __cdecl CGFontGetXHeight(void * font);
extern "C" void __cdecl CGFontRelease(void * font);
extern "C" void * __cdecl CGFontRetain(void * font);
extern "C" void * __cdecl CGFunctionCreate(void * info, unsigned long domainDimension, Iosapi::Cocoatypes::PCGFloat domain, unsigned long rangeDimension, Iosapi::Cocoatypes::PCGFloat range, PCGFunctionCallbacks callbacks);
extern "C" unsigned long __cdecl CGFunctionGetTypeID(void);
extern "C" void __cdecl CGFunctionRelease(void * function_);
extern "C" void * __cdecl CGFunctionRetain(void * function_);
extern "C" void * __cdecl CGGradientCreateWithColorComponents(void * space, Iosapi::Cocoatypes::PCGFloat components, Iosapi::Cocoatypes::PCGFloat locations, unsigned long count);
extern "C" void * __cdecl CGGradientCreateWithColors(void * space, CFArrayRef colors, Iosapi::Cocoatypes::PCGFloat locations);
extern "C" unsigned long __cdecl CGGradientGetTypeID(void);
extern "C" void __cdecl CGGradientRelease(void * gradient);
extern "C" void * __cdecl CGGradientRetain(void * gradient);
extern "C" void * __cdecl CGImageCreate(unsigned long width, unsigned long height, unsigned long bitsPerComponent, unsigned long bitsPerPixel, unsigned long bytesPerRow, void * space, unsigned bitmapInfo, void * provider, Iosapi::Cocoatypes::PCGFloat decode, bool shouldInterpolate, unsigned intent);
extern "C" void * __cdecl CGImageCreateCopy(void * image);
extern "C" void * __cdecl CGImageCreateCopyWithColorSpace(void * image, void * space);
extern "C" void * __cdecl CGImageCreateWithImageInRect(void * image, Iosapi::Foundation::NSRect rect);
extern "C" void * __cdecl CGImageCreateWithJPEGDataProvider(void * source, Iosapi::Cocoatypes::PCGFloat decode, bool shouldInterpolate, unsigned intent);
extern "C" void * __cdecl CGImageCreateWithMask(void * image, void * mask);
extern "C" void * __cdecl CGImageCreateWithMaskingColors(void * image, Iosapi::Cocoatypes::PCGFloat components);
extern "C" void * __cdecl CGImageCreateWithPNGDataProvider(void * source, Iosapi::Cocoatypes::PCGFloat decode, bool shouldInterpolate, unsigned intent);
extern "C" unsigned __cdecl CGImageGetAlphaInfo(void * image);
extern "C" unsigned __cdecl CGImageGetBitmapInfo(void * image);
extern "C" unsigned long __cdecl CGImageGetBitsPerComponent(void * image);
extern "C" unsigned long __cdecl CGImageGetBitsPerPixel(void * image);
extern "C" unsigned long __cdecl CGImageGetBytesPerRow(void * image);
extern "C" void * __cdecl CGImageGetColorSpace(void * image);
extern "C" void * __cdecl CGImageGetDataProvider(void * image);
extern "C" Iosapi::Cocoatypes::PCGFloat __cdecl CGImageGetDecode(void * image);
extern "C" unsigned long __cdecl CGImageGetHeight(void * image);
extern "C" unsigned __cdecl CGImageGetRenderingIntent(void * image);
extern "C" bool __cdecl CGImageGetShouldInterpolate(void * image);
extern "C" unsigned long __cdecl CGImageGetTypeID(void);
extern "C" unsigned long __cdecl CGImageGetWidth(void * image);
extern "C" bool __cdecl CGImageIsMask(void * image);
extern "C" void * __cdecl CGImageMaskCreate(unsigned long width, unsigned long height, unsigned long bitsPerComponent, unsigned long bitsPerPixel, unsigned long bytesPerRow, void * provider, Iosapi::Cocoatypes::PCGFloat decode, bool shouldInterpolate);
extern "C" void __cdecl CGImageRelease(void * image);
extern "C" void * __cdecl CGImageRetain(void * image);
extern "C" void * __cdecl CGLayerCreateWithContext(void * context, Iosapi::Foundation::NSSize size, CFDictionaryRef auxiliaryInfo);
extern "C" void * __cdecl CGLayerGetContext(void * layer);
extern "C" Iosapi::Foundation::NSSize __cdecl CGLayerGetSize(void * layer);
extern "C" unsigned long __cdecl CGLayerGetTypeID(void);
extern "C" void __cdecl CGLayerRelease(void * layer);
extern "C" void * __cdecl CGLayerRetain(void * layer);
extern "C" bool __cdecl CGPDFArrayGetArray(void * array_, unsigned long index, PCGPDFArrayRef value);
extern "C" bool __cdecl CGPDFArrayGetBoolean(void * array_, unsigned long index, PCGPDFBoolean value);
extern "C" unsigned long __cdecl CGPDFArrayGetCount(void * array_);
extern "C" bool __cdecl CGPDFArrayGetDictionary(void * array_, unsigned long index, PCGPDFDictionaryRef value);
extern "C" bool __cdecl CGPDFArrayGetInteger(void * array_, unsigned long index, PCGPDFInteger value);
extern "C" bool __cdecl CGPDFArrayGetName(void * array_, unsigned long index, System::WideChar * value);
extern "C" bool __cdecl CGPDFArrayGetNull(void * array_, unsigned long index);
extern "C" bool __cdecl CGPDFArrayGetNumber(void * array_, unsigned long index, PCGPDFReal value);
extern "C" bool __cdecl CGPDFArrayGetObject(void * array_, unsigned long index, PCGPDFObjectRef value);
extern "C" bool __cdecl CGPDFArrayGetStream(void * array_, unsigned long index, PCGPDFStreamRef value);
extern "C" bool __cdecl CGPDFArrayGetString(void * array_, unsigned long index, PCGPDFStringRef value);
extern "C" void * __cdecl CGPDFContentStreamCreateWithPage(void * page);
extern "C" void * __cdecl CGPDFContentStreamCreateWithStream(void * stream, void * streamResources, void * parent);
extern "C" void * __cdecl CGPDFContentStreamGetResource(void * cs, char * category, char * name);
extern "C" CFArrayRef __cdecl CGPDFContentStreamGetStreams(void * cs);
extern "C" void __cdecl CGPDFContentStreamRelease(void * cs);
extern "C" void * __cdecl CGPDFContentStreamRetain(void * cs);
extern "C" void __cdecl CGPDFContextAddDestinationAtPoint(void * context, CFStringRef name, Iosapi::Foundation::NSPoint point);
extern "C" void __cdecl CGPDFContextAddDocumentMetadata(void * context, CFDataRef metadata);
extern "C" void __cdecl CGPDFContextBeginPage(void * context, CFDictionaryRef pageInfo);
extern "C" void __cdecl CGPDFContextClose(void * context);
extern "C" void * __cdecl CGPDFContextCreate(void * consumer, PCGRect mediaBox, CFDictionaryRef auxiliaryInfo);
extern "C" void * __cdecl CGPDFContextCreateWithURL(CFURLRef url, PCGRect mediaBox, CFDictionaryRef auxiliaryInfo);
extern "C" void __cdecl CGPDFContextEndPage(void * context);
extern "C" void __cdecl CGPDFContextSetDestinationForRect(void * context, CFStringRef name, Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl CGPDFContextSetURLForRect(void * context, CFURLRef url, Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl CGPDFDictionaryApplyFunction(void * dict, CGPDFDictionaryApplierFunction function_, void * info);
extern "C" bool __cdecl CGPDFDictionaryGetArray(void * dict, char * key, PCGPDFArrayRef value);
extern "C" bool __cdecl CGPDFDictionaryGetBoolean(void * dict, char * key, PCGPDFBoolean value);
extern "C" unsigned long __cdecl CGPDFDictionaryGetCount(void * dict);
extern "C" bool __cdecl CGPDFDictionaryGetDictionary(void * dict, char * key, PCGPDFDictionaryRef value);
extern "C" bool __cdecl CGPDFDictionaryGetInteger(void * dict, char * key, PCGPDFInteger value);
extern "C" bool __cdecl CGPDFDictionaryGetName(void * dict, char * key, System::WideChar * value);
extern "C" bool __cdecl CGPDFDictionaryGetNumber(void * dict, char * key, PCGPDFReal value);
extern "C" bool __cdecl CGPDFDictionaryGetObject(void * dict, char * key, PCGPDFObjectRef value);
extern "C" bool __cdecl CGPDFDictionaryGetStream(void * dict, char * key, PCGPDFStreamRef value);
extern "C" bool __cdecl CGPDFDictionaryGetString(void * dict, char * key, PCGPDFStringRef value);
extern "C" bool __cdecl CGPDFDocumentAllowsCopying(void * document);
extern "C" bool __cdecl CGPDFDocumentAllowsPrinting(void * document);
extern "C" void * __cdecl CGPDFDocumentCreateWithProvider(void * provider);
extern "C" void * __cdecl CGPDFDocumentCreateWithURL(CFURLRef url);
extern "C" Iosapi::Foundation::NSRect __cdecl CGPDFDocumentGetArtBox(void * document, int page);
extern "C" Iosapi::Foundation::NSRect __cdecl CGPDFDocumentGetBleedBox(void * document, int page);
extern "C" void * __cdecl CGPDFDocumentGetCatalog(void * document);
extern "C" Iosapi::Foundation::NSRect __cdecl CGPDFDocumentGetCropBox(void * document, int page);
extern "C" void * __cdecl CGPDFDocumentGetID(void * document);
extern "C" void * __cdecl CGPDFDocumentGetInfo(void * document);
extern "C" Iosapi::Foundation::NSRect __cdecl CGPDFDocumentGetMediaBox(void * document, int page);
extern "C" unsigned long __cdecl CGPDFDocumentGetNumberOfPages(void * document);
extern "C" void * __cdecl CGPDFDocumentGetPage(void * document, unsigned long pageNumber);
extern "C" int __cdecl CGPDFDocumentGetRotationAngle(void * document, int page);
extern "C" Iosapi::Foundation::NSRect __cdecl CGPDFDocumentGetTrimBox(void * document, int page);
extern "C" unsigned long __cdecl CGPDFDocumentGetTypeID(void);
extern "C" void __cdecl CGPDFDocumentGetVersion(void * document, System::PInteger majorVersion, System::PInteger minorVersion);
extern "C" bool __cdecl CGPDFDocumentIsEncrypted(void * document);
extern "C" bool __cdecl CGPDFDocumentIsUnlocked(void * document);
extern "C" void __cdecl CGPDFDocumentRelease(void * document);
extern "C" void * __cdecl CGPDFDocumentRetain(void * document);
extern "C" bool __cdecl CGPDFDocumentUnlockWithPassword(void * document, char * password);
extern "C" unsigned __cdecl CGPDFObjectGetType(void * object_);
extern "C" bool __cdecl CGPDFObjectGetValue(void * object_, unsigned type_, void * value);
extern "C" void * __cdecl CGPDFOperatorTableCreate(void);
extern "C" void __cdecl CGPDFOperatorTableRelease(void * table);
extern "C" void * __cdecl CGPDFOperatorTableRetain(void * table);
extern "C" void __cdecl CGPDFOperatorTableSetCallback(void * table, char * name, CGPDFOperatorCallback callback);
extern "C" Iosapi::Foundation::NSRect __cdecl CGPDFPageGetBoxRect(void * page, unsigned box);
extern "C" void * __cdecl CGPDFPageGetDictionary(void * page);
extern "C" void * __cdecl CGPDFPageGetDocument(void * page);
extern "C" CGAffineTransform __cdecl CGPDFPageGetDrawingTransform(void * page, unsigned box, Iosapi::Foundation::NSRect rect, int rotate, bool preserveAspectRatio);
extern "C" unsigned long __cdecl CGPDFPageGetPageNumber(void * page);
extern "C" int __cdecl CGPDFPageGetRotationAngle(void * page);
extern "C" unsigned long __cdecl CGPDFPageGetTypeID(void);
extern "C" void __cdecl CGPDFPageRelease(void * page);
extern "C" void * __cdecl CGPDFPageRetain(void * page);
extern "C" void * __cdecl CGPDFScannerCreate(void * cs, void * table, void * info);
extern "C" void * __cdecl CGPDFScannerGetContentStream(void * scanner);
extern "C" bool __cdecl CGPDFScannerPopArray(void * scanner, PCGPDFArrayRef value);
extern "C" bool __cdecl CGPDFScannerPopBoolean(void * scanner, PCGPDFBoolean value);
extern "C" bool __cdecl CGPDFScannerPopDictionary(void * scanner, PCGPDFDictionaryRef value);
extern "C" bool __cdecl CGPDFScannerPopInteger(void * scanner, PCGPDFInteger value);
extern "C" bool __cdecl CGPDFScannerPopName(void * scanner, System::WideChar * value);
extern "C" bool __cdecl CGPDFScannerPopNumber(void * scanner, PCGPDFReal value);
extern "C" bool __cdecl CGPDFScannerPopObject(void * scanner, PCGPDFObjectRef value);
extern "C" bool __cdecl CGPDFScannerPopStream(void * scanner, PCGPDFStreamRef value);
extern "C" bool __cdecl CGPDFScannerPopString(void * scanner, PCGPDFStringRef value);
extern "C" void __cdecl CGPDFScannerRelease(void * scanner);
extern "C" void * __cdecl CGPDFScannerRetain(void * scanner);
extern "C" bool __cdecl CGPDFScannerScan(void * scanner);
extern "C" CFDataRef __cdecl CGPDFStreamCopyData(void * stream, PCGPDFDataFormat format);
extern "C" void * __cdecl CGPDFStreamGetDictionary(void * stream);
extern "C" CFDateRef __cdecl CGPDFStringCopyDate(void * string_);
extern "C" CFStringRef __cdecl CGPDFStringCopyTextString(void * string_);
extern "C" System::PByte __cdecl CGPDFStringGetBytePtr(void * string_);
extern "C" unsigned long __cdecl CGPDFStringGetLength(void * string_);
extern "C" void __cdecl CGPathAddArc(void * path, PCGAffineTransform m, double x, double y, double radius, double startAngle, double endAngle, int clockwise);
extern "C" void __cdecl CGPathAddArcToPoint(void * path, PCGAffineTransform m, double x1, double y1, double x2, double y2, double radius);
extern "C" void __cdecl CGPathAddCurveToPoint(void * path, PCGAffineTransform m, double cp1x, double cp1y, double cp2x, double cp2y, double x, double y);
extern "C" void __cdecl CGPathAddEllipseInRect(void * path, PCGAffineTransform m, Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl CGPathAddLineToPoint(void * path, PCGAffineTransform m, double x, double y);
extern "C" void __cdecl CGPathAddLines(void * path, PCGAffineTransform m, PCGPoint points, unsigned long count);
extern "C" void __cdecl CGPathAddPath(void * path1, PCGAffineTransform m, void * path2);
extern "C" void __cdecl CGPathAddQuadCurveToPoint(void * path, PCGAffineTransform m, double cpx, double cpy, double x, double y);
extern "C" void __cdecl CGPathAddRect(void * path, PCGAffineTransform m, Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl CGPathAddRects(void * path, PCGAffineTransform m, PCGRect rects, unsigned long count);
extern "C" void __cdecl CGPathAddRelativeArc(void * path, PCGAffineTransform matrix, double x, double y, double radius, double startAngle, double delta);
extern "C" void __cdecl CGPathApply(void * path, void * info, CGPathApplierFunction function_);
extern "C" void __cdecl CGPathCloseSubpath(void * path);
extern "C" bool __cdecl CGPathContainsPoint(void * path, PCGAffineTransform m, Iosapi::Foundation::NSPoint point, int eoFill);
extern "C" void * __cdecl CGPathCreateCopy(void * path);
extern "C" void * __cdecl CGPathCreateCopyByDashingPath(void * path, PCGAffineTransform transform, double phase, Iosapi::Cocoatypes::PCGFloat lengths, unsigned long count);
extern "C" void * __cdecl CGPathCreateCopyByStrokingPath(void * path, PCGAffineTransform transform, double lineWidth, unsigned lineCap, unsigned lineJoin, double miterLimit);
extern "C" void * __cdecl CGPathCreateCopyByTransformingPath(void * path, PCGAffineTransform transform);
extern "C" void * __cdecl CGPathCreateMutable(void);
extern "C" void * __cdecl CGPathCreateMutableCopy(void * path);
extern "C" void * __cdecl CGPathCreateMutableCopyByTransformingPath(void * path, PCGAffineTransform transform);
extern "C" void * __cdecl CGPathCreateWithEllipseInRect(Iosapi::Foundation::NSRect rect, PCGAffineTransform transform);
extern "C" void * __cdecl CGPathCreateWithRect(Iosapi::Foundation::NSRect rect, PCGAffineTransform transform);
extern "C" bool __cdecl CGPathEqualToPath(void * path1, void * path2);
extern "C" Iosapi::Foundation::NSRect __cdecl CGPathGetBoundingBox(void * path);
extern "C" Iosapi::Foundation::NSPoint __cdecl CGPathGetCurrentPoint(void * path);
extern "C" Iosapi::Foundation::NSRect __cdecl CGPathGetPathBoundingBox(void * path);
extern "C" unsigned long __cdecl CGPathGetTypeID(void);
extern "C" bool __cdecl CGPathIsEmpty(void * path);
extern "C" bool __cdecl CGPathIsRect(void * path, PCGRect rect);
extern "C" void __cdecl CGPathMoveToPoint(void * path, PCGAffineTransform m, double x, double y);
extern "C" void __cdecl CGPathRelease(void * path);
extern "C" void * __cdecl CGPathRetain(void * path);
extern "C" void * __cdecl CGPatternCreate(void * info, Iosapi::Foundation::NSRect bounds, CGAffineTransform matrix, double xStep, double yStep, unsigned tiling, bool isColored, PCGPatternCallbacks callbacks);
extern "C" unsigned long __cdecl CGPatternGetTypeID(void);
extern "C" void __cdecl CGPatternRelease(void * pattern);
extern "C" void * __cdecl CGPatternRetain(void * pattern);
extern "C" Iosapi::Foundation::NSPoint __cdecl CGPointApplyAffineTransform(Iosapi::Foundation::NSPoint point, CGAffineTransform t);
extern "C" CFDictionaryRef __cdecl CGPointCreateDictionaryRepresentation(Iosapi::Foundation::NSPoint point);
extern "C" bool __cdecl CGPointEqualToPoint(Iosapi::Foundation::NSPoint point1, Iosapi::Foundation::NSPoint point2);
extern "C" bool __cdecl CGPointMakeWithDictionaryRepresentation(CFDictionaryRef dict, PCGPoint point);
extern "C" Iosapi::Foundation::NSRect __cdecl CGRectApplyAffineTransform(Iosapi::Foundation::NSRect rect, CGAffineTransform t);
extern "C" bool __cdecl CGRectContainsPoint(Iosapi::Foundation::NSRect rect, Iosapi::Foundation::NSPoint point);
extern "C" bool __cdecl CGRectContainsRect(Iosapi::Foundation::NSRect rect1, Iosapi::Foundation::NSRect rect2);
extern "C" CFDictionaryRef __cdecl CGRectCreateDictionaryRepresentation(Iosapi::Foundation::NSRect dummy);
extern "C" void __cdecl CGRectDivide(Iosapi::Foundation::NSRect rect, PCGRect slice, PCGRect remainder, double amount, unsigned edge);
extern "C" bool __cdecl CGRectEqualToRect(Iosapi::Foundation::NSRect rect1, Iosapi::Foundation::NSRect rect2);
extern "C" double __cdecl CGRectGetHeight(Iosapi::Foundation::NSRect rect);
extern "C" double __cdecl CGRectGetMaxX(Iosapi::Foundation::NSRect rect);
extern "C" double __cdecl CGRectGetMaxY(Iosapi::Foundation::NSRect rect);
extern "C" double __cdecl CGRectGetMidX(Iosapi::Foundation::NSRect rect);
extern "C" double __cdecl CGRectGetMidY(Iosapi::Foundation::NSRect rect);
extern "C" double __cdecl CGRectGetMinX(Iosapi::Foundation::NSRect rect);
extern "C" double __cdecl CGRectGetMinY(Iosapi::Foundation::NSRect rect);
extern "C" double __cdecl CGRectGetWidth(Iosapi::Foundation::NSRect rect);
extern "C" Iosapi::Foundation::NSRect __cdecl CGRectInset(Iosapi::Foundation::NSRect rect, double dx, double dy);
extern "C" Iosapi::Foundation::NSRect __cdecl CGRectIntegral(Iosapi::Foundation::NSRect rect);
extern "C" Iosapi::Foundation::NSRect __cdecl CGRectIntersection(Iosapi::Foundation::NSRect r1, Iosapi::Foundation::NSRect r2);
extern "C" bool __cdecl CGRectIntersectsRect(Iosapi::Foundation::NSRect rect1, Iosapi::Foundation::NSRect rect2);
extern "C" bool __cdecl CGRectIsEmpty(Iosapi::Foundation::NSRect rect);
extern "C" bool __cdecl CGRectIsInfinite(Iosapi::Foundation::NSRect rect);
extern "C" bool __cdecl CGRectIsNull(Iosapi::Foundation::NSRect rect);
extern "C" bool __cdecl CGRectMakeWithDictionaryRepresentation(CFDictionaryRef dict, PCGRect rect);
extern "C" Iosapi::Foundation::NSRect __cdecl CGRectOffset(Iosapi::Foundation::NSRect rect, double dx, double dy);
extern "C" Iosapi::Foundation::NSRect __cdecl CGRectStandardize(Iosapi::Foundation::NSRect rect);
extern "C" Iosapi::Foundation::NSRect __cdecl CGRectUnion(Iosapi::Foundation::NSRect r1, Iosapi::Foundation::NSRect r2);
extern "C" void * __cdecl CGShadingCreateAxial(void * space, Iosapi::Foundation::NSPoint start, Iosapi::Foundation::NSPoint end_, void * function_, bool extendStart, bool extendEnd);
extern "C" void * __cdecl CGShadingCreateRadial(void * space, Iosapi::Foundation::NSPoint start, double startRadius, Iosapi::Foundation::NSPoint end_, double endRadius, void * function_, bool extendStart, bool extendEnd);
extern "C" unsigned long __cdecl CGShadingGetTypeID(void);
extern "C" void __cdecl CGShadingRelease(void * shading);
extern "C" void * __cdecl CGShadingRetain(void * shading);
extern "C" Iosapi::Foundation::NSSize __cdecl CGSizeApplyAffineTransform(Iosapi::Foundation::NSSize size, CGAffineTransform t);
extern "C" CFDictionaryRef __cdecl CGSizeCreateDictionaryRepresentation(Iosapi::Foundation::NSSize size);
extern "C" bool __cdecl CGSizeEqualToSize(Iosapi::Foundation::NSSize size1, Iosapi::Foundation::NSSize size2);
extern "C" bool __cdecl CGSizeMakeWithDictionaryRepresentation(CFDictionaryRef dict, PCGSize size);
extern DELPHI_PACKAGE CGAffineTransform __cdecl __CGAffineTransformMake(double a, double b, double c, double d, double tx, double ty);
extern DELPHI_PACKAGE Iosapi::Foundation::NSPoint __cdecl __CGPointApplyAffineTransform(Iosapi::Foundation::NSPoint point, CGAffineTransform t);
extern DELPHI_PACKAGE bool __cdecl __CGPointEqualToPoint(Iosapi::Foundation::NSPoint point1, Iosapi::Foundation::NSPoint point2);
extern DELPHI_PACKAGE Iosapi::Foundation::NSSize __cdecl __CGSizeApplyAffineTransform(Iosapi::Foundation::NSSize size, CGAffineTransform t);
extern DELPHI_PACKAGE bool __cdecl __CGSizeEqualToSize(Iosapi::Foundation::NSSize size1, Iosapi::Foundation::NSSize size2);
extern DELPHI_PACKAGE CGAffineTransform CGAffineTransformIdentity;
extern DELPHI_PACKAGE Iosapi::Foundation::NSPoint __fastcall CGPointMake(const double AX, const double AY)/* overload */;
extern DELPHI_PACKAGE Iosapi::Foundation::NSPoint __fastcall CGPointMake(const System::Types::TPointF &APoint)/* overload */;
extern DELPHI_PACKAGE System::Types::TPointF __fastcall CGPointToPointF(const Iosapi::Foundation::NSPoint &APoint);
extern DELPHI_PACKAGE Iosapi::Foundation::NSSize __fastcall CGSizeMake(const double AWidth, const double AHeight)/* overload */;
extern DELPHI_PACKAGE Iosapi::Foundation::NSSize __fastcall CGSizeMake(const System::Types::TSizeF &ASize)/* overload */;
extern DELPHI_PACKAGE System::Types::TSizeF __fastcall CGSizeToSizeF(const Iosapi::Foundation::NSSize &ASize);
extern DELPHI_PACKAGE Iosapi::Foundation::NSRect __fastcall CGRectMake(const double AX, const double AY, const double AWidth, const double AHeight)/* overload */;
extern DELPHI_PACKAGE Iosapi::Foundation::NSRect __fastcall CGRectMake(const System::Types::TRectF &ARect)/* overload */;
extern DELPHI_PACKAGE System::Types::TRectF __fastcall CGRectToRectF(const Iosapi::Foundation::NSRect &ARect);
}	/* namespace Coregraphics */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_COREGRAPHICS)
using namespace Iosapi::Coregraphics;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_CoregraphicsHPP
