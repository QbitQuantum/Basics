// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.CoreImage.pas' rev: 34.00 (iOS)

#ifndef Iosapi_CoreimageHPP
#define Iosapi_CoreimageHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.StdDef.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.OpenGLES.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Coreimage
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE CIFeatureClass;
typedef System::DelphiInterface<CIFeatureClass> _di_CIFeatureClass;
__interface DELPHIINTERFACE CIFeature;
typedef System::DelphiInterface<CIFeature> _di_CIFeature;
class DELPHICLASS TCIFeature;
__interface DELPHIINTERFACE CIFilterClass;
typedef System::DelphiInterface<CIFilterClass> _di_CIFilterClass;
__interface DELPHIINTERFACE CIFilter;
typedef System::DelphiInterface<CIFilter> _di_CIFilter;
class DELPHICLASS TCIFilter;
__interface DELPHIINTERFACE CIImageClass;
typedef System::DelphiInterface<CIImageClass> _di_CIImageClass;
__interface DELPHIINTERFACE CIImage;
typedef System::DelphiInterface<CIImage> _di_CIImage;
class DELPHICLASS TCIImage;
__interface DELPHIINTERFACE CIVectorClass;
typedef System::DelphiInterface<CIVectorClass> _di_CIVectorClass;
__interface DELPHIINTERFACE CIVector;
typedef System::DelphiInterface<CIVector> _di_CIVector;
class DELPHICLASS TCIVector;
__interface DELPHIINTERFACE CIColorClass;
typedef System::DelphiInterface<CIColorClass> _di_CIColorClass;
__interface DELPHIINTERFACE CIColor;
typedef System::DelphiInterface<CIColor> _di_CIColor;
class DELPHICLASS TCIColor;
__interface DELPHIINTERFACE CIContextClass;
typedef System::DelphiInterface<CIContextClass> _di_CIContextClass;
__interface DELPHIINTERFACE CIContext;
typedef System::DelphiInterface<CIContext> _di_CIContext;
class DELPHICLASS TCIContext;
__interface DELPHIINTERFACE CIDetectorClass;
typedef System::DelphiInterface<CIDetectorClass> _di_CIDetectorClass;
__interface DELPHIINTERFACE CIDetector;
typedef System::DelphiInterface<CIDetector> _di_CIDetector;
class DELPHICLASS TCIDetector;
__interface DELPHIINTERFACE CIFaceFeatureClass;
typedef System::DelphiInterface<CIFaceFeatureClass> _di_CIFaceFeatureClass;
__interface DELPHIINTERFACE CIFaceFeature;
typedef System::DelphiInterface<CIFaceFeature> _di_CIFaceFeature;
class DELPHICLASS TCIFaceFeature;
//-- type declarations -------------------------------------------------------
typedef int CIFormat;

typedef NativeInt CVImageBufferRef;

typedef NativeInt CVPixelBufferRef;

__interface  INTERFACE_UUID("{D8B4E972-AE4D-4357-90DA-93C5D3635BFC}") CIFeatureClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{A9AA408B-B7E4-409A-B573-3C9496FE73DB}") CIFeature  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::NSRect __cdecl bounds() = 0 ;
};

class PASCALIMPLEMENTATION TCIFeature : public Macapi::Objectivec::TOCGenericImport__2<_di_CIFeatureClass,_di_CIFeature>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CIFeatureClass,_di_CIFeature> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCIFeature(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CIFeatureClass,_di_CIFeature>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCIFeature() { }
	
};


__interface  INTERFACE_UUID("{63DC7C5A-11EF-4F75-9A57-60445EDB9735}") CIFilterClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl filterNamesInCategories(Iosapi::Foundation::_di_NSArray categories) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl filterNamesInCategory(Iosapi::Foundation::_di_NSString category) = 0 ;
	virtual void * __cdecl filterWithName(Iosapi::Foundation::_di_NSString name) = 0 /* overload */;
	virtual void * __cdecl filterWithName(Iosapi::Foundation::_di_NSString name, void * keysAndValues) = 0 /* overload */;
	virtual Iosapi::Foundation::_di_NSString __cdecl localizedDescriptionForFilterName(Iosapi::Foundation::_di_NSString filterName) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl localizedNameForCategory(Iosapi::Foundation::_di_NSString category) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl localizedNameForFilterName(Iosapi::Foundation::_di_NSString filterName) = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl localizedReferenceDocumentationForFilterName(Iosapi::Foundation::_di_NSString filterName) = 0 ;
};

__interface  INTERFACE_UUID("{1E199DAF-0472-46AE-B6E1-AC6DE7C9B48C}") CIFilter  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl attributes() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl inputKeys() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual _di_CIImage __cdecl outputImage() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl outputKeys() = 0 ;
	virtual void __cdecl setDefaults() = 0 ;
};

class PASCALIMPLEMENTATION TCIFilter : public Macapi::Objectivec::TOCGenericImport__2<_di_CIFilterClass,_di_CIFilter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CIFilterClass,_di_CIFilter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCIFilter(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CIFilterClass,_di_CIFilter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCIFilter() { }
	
};


__interface  INTERFACE_UUID("{8116FB49-A1ED-4CDA-A20E-2F41A858B265}") CIImageClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl emptyImage() = 0 ;
	virtual void * __cdecl imageWithBitmapData(Iosapi::Foundation::_di_NSData d, unsigned long bytesPerRow, Iosapi::Foundation::NSSize size, int format, void * colorSpace) = 0 ;
	virtual void * __cdecl imageWithCGImage(void * image) = 0 /* overload */;
	virtual void * __cdecl imageWithCGImage(void * image, Iosapi::Foundation::_di_NSDictionary options) = 0 /* overload */;
	virtual void * __cdecl imageWithCVPixelBuffer(NativeInt buffer) = 0 /* overload */;
	virtual void * __cdecl imageWithCVPixelBuffer(NativeInt buffer, Iosapi::Foundation::_di_NSDictionary options) = 0 /* overload */;
	virtual void * __cdecl imageWithColor(_di_CIColor color) = 0 ;
	virtual void * __cdecl imageWithContentsOfURL(Iosapi::Foundation::_di_NSURL url) = 0 /* overload */;
	virtual void * __cdecl imageWithContentsOfURL(Iosapi::Foundation::_di_NSURL url, Iosapi::Foundation::_di_NSDictionary options) = 0 /* overload */;
	virtual void * __cdecl imageWithData(Iosapi::Foundation::_di_NSData data) = 0 /* overload */;
	virtual void * __cdecl imageWithData(Iosapi::Foundation::_di_NSData data, Iosapi::Foundation::_di_NSDictionary options) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{1446FF5E-9128-4592-BDE4-2A89A22F1CA3}") CIImage  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl autoAdjustmentFilters() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl autoAdjustmentFiltersWithOptions(Iosapi::Foundation::_di_NSDictionary dict) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl extent() = 0 ;
	virtual _di_CIImage __cdecl imageByApplyingTransform(Iosapi::Coregraphics::CGAffineTransform matrix) = 0 ;
	virtual _di_CIImage __cdecl imageByCroppingToRect(Iosapi::Foundation::NSRect r) = 0 ;
	virtual void * __cdecl initWithBitmapData(Iosapi::Foundation::_di_NSData d, unsigned long bytesPerRow, Iosapi::Foundation::NSSize size, int format, void * colorSpace) = 0 ;
	virtual void * __cdecl initWithCGImage(void * image) = 0 /* overload */;
	virtual void * __cdecl initWithCGImage(void * image, Iosapi::Foundation::_di_NSDictionary options) = 0 /* overload */;
	virtual void * __cdecl initWithCVPixelBuffer(NativeInt buffer) = 0 /* overload */;
	virtual void * __cdecl initWithCVPixelBuffer(NativeInt buffer, Iosapi::Foundation::_di_NSDictionary options) = 0 /* overload */;
	virtual void * __cdecl initWithColor(_di_CIColor color) = 0 ;
	virtual void * __cdecl initWithContentsOfURL(Iosapi::Foundation::_di_NSURL url) = 0 /* overload */;
	virtual void * __cdecl initWithContentsOfURL(Iosapi::Foundation::_di_NSURL url, Iosapi::Foundation::_di_NSDictionary options) = 0 /* overload */;
	virtual void * __cdecl initWithData(Iosapi::Foundation::_di_NSData data) = 0 /* overload */;
	virtual void * __cdecl initWithData(Iosapi::Foundation::_di_NSData data, Iosapi::Foundation::_di_NSDictionary options) = 0 /* overload */;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl properties() = 0 ;
};

class PASCALIMPLEMENTATION TCIImage : public Macapi::Objectivec::TOCGenericImport__2<_di_CIImageClass,_di_CIImage>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CIImageClass,_di_CIImage> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCIImage(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CIImageClass,_di_CIImage>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCIImage() { }
	
};


__interface  INTERFACE_UUID("{B57E8A70-0FCC-4784-958C-9A17EE7C2FBD}") CIVectorClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl vectorWithCGAffineTransform(Iosapi::Coregraphics::CGAffineTransform t) = 0 ;
	virtual void * __cdecl vectorWithCGPoint(Iosapi::Foundation::NSPoint p) = 0 ;
	virtual void * __cdecl vectorWithCGRect(Iosapi::Foundation::NSRect r) = 0 ;
	virtual void * __cdecl vectorWithString(Iosapi::Foundation::_di_NSString representation) = 0 ;
	virtual void * __cdecl vectorWithValues(Iosapi::Cocoatypes::PCGFloat values, unsigned long count) = 0 ;
	virtual void * __cdecl vectorWithX(double x) = 0 /* overload */;
	virtual void * __cdecl vectorWithX(double x, double Y) = 0 /* overload */;
	virtual void * __cdecl vectorWithX(double x, double Y, double Z) = 0 /* overload */;
	virtual void * __cdecl vectorWithX(double x, double Y, double Z, double W) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{12FAEF98-27A1-45E1-A0A9-5ACB6B3F9BB9}") CIVector  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Coregraphics::CGAffineTransform __cdecl CGAffineTransformValue() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl CGPointValue() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl CGRectValue() = 0 ;
	virtual double __cdecl W() = 0 ;
	virtual double __cdecl X() = 0 ;
	virtual double __cdecl Y() = 0 ;
	virtual double __cdecl Z() = 0 ;
	virtual unsigned long __cdecl count() = 0 ;
	virtual void * __cdecl initWithCGAffineTransform(Iosapi::Coregraphics::CGAffineTransform r) = 0 ;
	virtual void * __cdecl initWithCGPoint(Iosapi::Foundation::NSPoint p) = 0 ;
	virtual void * __cdecl initWithCGRect(Iosapi::Foundation::NSRect r) = 0 ;
	virtual void * __cdecl initWithString(Iosapi::Foundation::_di_NSString representation) = 0 ;
	virtual void * __cdecl initWithValues(Iosapi::Cocoatypes::PCGFloat values, unsigned long count) = 0 ;
	virtual void * __cdecl initWithX(double x) = 0 /* overload */;
	virtual void * __cdecl initWithX(double x, double Y) = 0 /* overload */;
	virtual void * __cdecl initWithX(double x, double Y, double Z) = 0 /* overload */;
	virtual void * __cdecl initWithX(double x, double Y, double Z, double W) = 0 /* overload */;
	virtual Iosapi::Foundation::_di_NSString __cdecl stringRepresentation() = 0 ;
	virtual double __cdecl valueAtIndex(unsigned long index) = 0 ;
};

class PASCALIMPLEMENTATION TCIVector : public Macapi::Objectivec::TOCGenericImport__2<_di_CIVectorClass,_di_CIVector>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CIVectorClass,_di_CIVector> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCIVector(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CIVectorClass,_di_CIVector>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCIVector() { }
	
};


__interface  INTERFACE_UUID("{77050FC9-0150-4054-8FA6-3872F5872EFE}") CIColorClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl colorWithCGColor(void * c) = 0 ;
	virtual void * __cdecl colorWithRed(double r, double green, double blue) = 0 /* overload */;
	virtual void * __cdecl colorWithRed(double r, double green, double blue, double alpha) = 0 /* overload */;
	virtual void * __cdecl colorWithString(Iosapi::Foundation::_di_NSString representation) = 0 ;
};

__interface  INTERFACE_UUID("{7982DEBA-D260-4F18-8AE9-832233CB60A1}") CIColor  : public Iosapi::Foundation::NSObject 
{
	virtual double __cdecl alpha() = 0 ;
	virtual double __cdecl blue() = 0 ;
	virtual void * __cdecl colorSpace() = 0 ;
	virtual Iosapi::Cocoatypes::PCGFloat __cdecl components() = 0 ;
	virtual double __cdecl green() = 0 ;
	virtual void * __cdecl initWithCGColor(void * c) = 0 ;
	virtual unsigned long __cdecl numberOfComponents() = 0 ;
	virtual double __cdecl red() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl stringRepresentation() = 0 ;
};

class PASCALIMPLEMENTATION TCIColor : public Macapi::Objectivec::TOCGenericImport__2<_di_CIColorClass,_di_CIColor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CIColorClass,_di_CIColor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCIColor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CIColorClass,_di_CIColor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCIColor() { }
	
};


__interface  INTERFACE_UUID("{48CA9DD6-BDDF-47F1-9615-EA0B6EAAC4D2}") CIContextClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl contextWithEAGLContext(Iosapi::Opengles::_di_EAGLContext eaglContext) = 0 /* overload */;
	virtual void * __cdecl contextWithEAGLContext(Iosapi::Opengles::_di_EAGLContext eaglContext, Iosapi::Foundation::_di_NSDictionary options) = 0 /* overload */;
	virtual void * __cdecl contextWithOptions(Iosapi::Foundation::_di_NSDictionary dict) = 0 ;
};

__interface  INTERFACE_UUID("{662F7DD8-DAA6-4771-B2E8-458528D2A757}") CIContext  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl createCGImage(_di_CIImage im, Iosapi::Foundation::NSRect fromRect) = 0 /* overload */;
	virtual void * __cdecl createCGImage(_di_CIImage im, Iosapi::Foundation::NSRect fromRect, int format, void * colorSpace) = 0 /* overload */;
	virtual void * __cdecl createCGLayerWithSize(Iosapi::Foundation::NSSize size, CFDictionaryRef info) = 0 ;
	virtual void __cdecl drawImage(_di_CIImage im, Iosapi::Foundation::NSPoint atPoint, Iosapi::Foundation::NSRect fromRect) = 0 /* overload */;
	virtual void __cdecl drawImage(_di_CIImage im, Iosapi::Foundation::NSRect inRect, Iosapi::Foundation::NSRect fromRect) = 0 /* overload */;
	virtual Iosapi::Foundation::NSSize __cdecl inputImageMaximumSize() = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl outputImageMaximumSize() = 0 ;
	virtual void __cdecl render(_di_CIImage im, void * toBitmap, __int64 rowBytes, Iosapi::Foundation::NSRect bounds, int format, void * colorSpace) = 0 /* overload */;
	virtual void __cdecl render(_di_CIImage image, NativeInt toCVPixelBuffer) = 0 /* overload */;
	virtual void __cdecl render(_di_CIImage image, NativeInt toCVPixelBuffer, Iosapi::Foundation::NSRect bounds, void * colorSpace) = 0 /* overload */;
};

class PASCALIMPLEMENTATION TCIContext : public Macapi::Objectivec::TOCGenericImport__2<_di_CIContextClass,_di_CIContext>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CIContextClass,_di_CIContext> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCIContext(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CIContextClass,_di_CIContext>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCIContext() { }
	
};


__interface  INTERFACE_UUID("{16F4A5B1-E411-429E-B309-EDD7AB08F155}") CIDetectorClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl detectorOfType(Iosapi::Foundation::_di_NSString type_, _di_CIContext context, Iosapi::Foundation::_di_NSDictionary options) = 0 ;
};

__interface  INTERFACE_UUID("{465E3620-EA4E-4090-A821-115E489735E2}") CIDetector  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl featuresInImage(_di_CIImage image) = 0 /* overload */;
	virtual Iosapi::Foundation::_di_NSArray __cdecl featuresInImage(_di_CIImage image, Iosapi::Foundation::_di_NSDictionary options) = 0 /* overload */;
};

class PASCALIMPLEMENTATION TCIDetector : public Macapi::Objectivec::TOCGenericImport__2<_di_CIDetectorClass,_di_CIDetector>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CIDetectorClass,_di_CIDetector> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCIDetector(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CIDetectorClass,_di_CIDetector>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCIDetector() { }
	
};


__interface  INTERFACE_UUID("{89F91151-B61E-4BE6-B9D7-C9259A777D0E}") CIFaceFeatureClass  : public CIFeatureClass 
{
	
};

__interface  INTERFACE_UUID("{F6D1BB62-9EEF-4883-A1C0-BC272E0DA9FB}") CIFaceFeature  : public CIFeature 
{
	virtual bool __cdecl hasLeftEyePosition() = 0 ;
	virtual bool __cdecl hasMouthPosition() = 0 ;
	virtual bool __cdecl hasRightEyePosition() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl leftEyePosition() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl mouthPosition() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl rightEyePosition() = 0 ;
};

class PASCALIMPLEMENTATION TCIFaceFeature : public Macapi::Objectivec::TOCGenericImport__2<_di_CIFaceFeatureClass,_di_CIFaceFeature>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CIFaceFeatureClass,_di_CIFaceFeature> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCIFaceFeature(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CIFaceFeatureClass,_di_CIFaceFeature>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCIFaceFeature() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define libCoreImage u"/System/Library/Frameworks/CoreImage.framework/CoreImage"
}	/* namespace Coreimage */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_COREIMAGE)
using namespace Iosapi::Coreimage;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_CoreimageHPP
