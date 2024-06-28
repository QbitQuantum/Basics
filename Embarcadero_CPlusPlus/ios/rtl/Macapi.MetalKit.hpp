// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Macapi.MetalKit.pas' rev: 34.00 (iOS)

#ifndef Macapi_MetalkitHPP
#define Macapi_MetalkitHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.QuartzCore.hpp>
#include <iOSapi.UIKit.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <Macapi.CoreServices.hpp>
#include <Macapi.Dispatch.hpp>
#include <Macapi.Mach.hpp>
#include <Macapi.ObjCRuntime.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <Macapi.Metal.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Macapi
{
namespace Metalkit
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE CAMetalLayerClass;
typedef System::DelphiInterface<CAMetalLayerClass> _di_CAMetalLayerClass;
__interface DELPHIINTERFACE CAMetalLayer;
typedef System::DelphiInterface<CAMetalLayer> _di_CAMetalLayer;
class DELPHICLASS TCAMetalLayer;
__interface DELPHIINTERFACE CAMetalDrawable;
typedef System::DelphiInterface<CAMetalDrawable> _di_CAMetalDrawable;
__interface DELPHIINTERFACE MTKViewClass;
typedef System::DelphiInterface<MTKViewClass> _di_MTKViewClass;
__interface DELPHIINTERFACE MTKView;
typedef System::DelphiInterface<MTKView> _di_MTKView;
class DELPHICLASS TMTKView;
__interface DELPHIINTERFACE MTKTextureLoaderClass;
typedef System::DelphiInterface<MTKTextureLoaderClass> _di_MTKTextureLoaderClass;
__interface DELPHIINTERFACE MTKTextureLoader;
typedef System::DelphiInterface<MTKTextureLoader> _di_MTKTextureLoader;
class DELPHICLASS TMTKTextureLoader;
__interface DELPHIINTERFACE MTKMeshBufferAllocatorClass;
typedef System::DelphiInterface<MTKMeshBufferAllocatorClass> _di_MTKMeshBufferAllocatorClass;
__interface DELPHIINTERFACE MTKMeshBufferAllocator;
typedef System::DelphiInterface<MTKMeshBufferAllocator> _di_MTKMeshBufferAllocator;
class DELPHICLASS TMTKMeshBufferAllocator;
__interface DELPHIINTERFACE MTKMeshBufferClass;
typedef System::DelphiInterface<MTKMeshBufferClass> _di_MTKMeshBufferClass;
__interface DELPHIINTERFACE MTKMeshBuffer;
typedef System::DelphiInterface<MTKMeshBuffer> _di_MTKMeshBuffer;
class DELPHICLASS TMTKMeshBuffer;
__interface DELPHIINTERFACE MTKMeshClass;
typedef System::DelphiInterface<MTKMeshClass> _di_MTKMeshClass;
__interface DELPHIINTERFACE MTKMesh;
typedef System::DelphiInterface<MTKMesh> _di_MTKMesh;
class DELPHICLASS TMTKMesh;
__interface DELPHIINTERFACE MTKSubmeshClass;
typedef System::DelphiInterface<MTKSubmeshClass> _di_MTKSubmeshClass;
__interface DELPHIINTERFACE MTKSubmesh;
typedef System::DelphiInterface<MTKSubmesh> _di_MTKSubmesh;
class DELPHICLASS TMTKSubmesh;
__interface DELPHIINTERFACE MTKViewDelegate;
typedef System::DelphiInterface<MTKViewDelegate> _di_MTKViewDelegate;
//-- type declarations -------------------------------------------------------
typedef Iosapi::Foundation::_di_NSString MTKTextureLoaderError;

typedef Iosapi::Foundation::_di_NSString *PMTKTextureLoaderError;

typedef Iosapi::Foundation::_di_NSString MTKTextureLoaderOption;

typedef Iosapi::Foundation::_di_NSString *PMTKTextureLoaderOption;

typedef Iosapi::Foundation::_di_NSString MTKTextureLoaderCubeLayout;

typedef Iosapi::Foundation::_di_NSString *PMTKTextureLoaderCubeLayout;

typedef Iosapi::Foundation::_di_NSString MTKTextureLoaderOrigin;

typedef Iosapi::Foundation::_di_NSString *PMTKTextureLoaderOrigin;

typedef void __fastcall (__closure *MTKTextureLoaderCallback)(Macapi::Metal::_di_MTLTexture texture, Iosapi::Foundation::_di_NSError error);

typedef void __fastcall (__closure *MTKTextureLoaderArrayCallback)(Iosapi::Foundation::_di_NSArray textures, Iosapi::Foundation::_di_NSError error);

typedef Iosapi::Foundation::_di_NSString MTKModelError;

typedef Iosapi::Foundation::_di_NSString *PMTKModelError;

__interface  INTERFACE_UUID("{2307B5AA-EE64-4981-9458-D815A7678A1B}") CAMetalLayerClass  : public Iosapi::Quartzcore::CALayerClass 
{
	
};

__interface  INTERFACE_UUID("{31555584-6361-469C-962C-08E1C1BC1060}") CAMetalLayer  : public Iosapi::Quartzcore::CALayer 
{
	virtual void __cdecl setDevice(Macapi::Metal::_di_MTLDevice device) = 0 ;
	virtual Macapi::Metal::_di_MTLDevice __cdecl device() = 0 ;
	virtual void __cdecl setPixelFormat(unsigned long pixelFormat) = 0 ;
	virtual unsigned long __cdecl pixelFormat() = 0 ;
	virtual void __cdecl setFramebufferOnly(bool framebufferOnly) = 0 ;
	virtual bool __cdecl framebufferOnly() = 0 ;
	virtual void __cdecl setDrawableSize(Iosapi::Foundation::NSSize drawableSize) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl drawableSize() = 0 ;
	virtual _di_CAMetalDrawable __cdecl nextDrawable() = 0 ;
	virtual void __cdecl setMaximumDrawableCount(unsigned long maximumDrawableCount) = 0 ;
	virtual unsigned long __cdecl maximumDrawableCount() = 0 ;
	virtual void __cdecl setPresentsWithTransaction(bool presentsWithTransaction) = 0 ;
	virtual bool __cdecl presentsWithTransaction() = 0 ;
	virtual void __cdecl setAllowsNextDrawableTimeout(bool allowsNextDrawableTimeout) = 0 ;
	virtual bool __cdecl allowsNextDrawableTimeout() = 0 ;
};

class PASCALIMPLEMENTATION TCAMetalLayer : public Macapi::Objectivec::TOCGenericImport__2<_di_CAMetalLayerClass,_di_CAMetalLayer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CAMetalLayerClass,_di_CAMetalLayer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCAMetalLayer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CAMetalLayerClass,_di_CAMetalLayer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCAMetalLayer() { }
	
};


__interface  INTERFACE_UUID("{21E0F785-4690-4358-8401-787213A049BD}") CAMetalDrawable  : public Macapi::Metal::MTLDrawable 
{
	virtual Macapi::Metal::_di_MTLTexture __cdecl texture() = 0 ;
	virtual _di_CAMetalLayer __cdecl layer() = 0 ;
};

__interface  INTERFACE_UUID("{11EF065F-51D2-4B57-8700-B720B030CB27}") MTKViewClass  : public Iosapi::Uikit::UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{B1CA7942-7BD4-41C1-A928-4AA9D2229C1A}") MTKView  : public Iosapi::Uikit::UIView 
{
	HIDESBASE virtual _di_MTKView __cdecl initWithFrame(Iosapi::Foundation::NSRect frameRect, Macapi::Metal::_di_MTLDevice device) = 0 ;
	virtual _di_MTKView __cdecl initWithCoder(Iosapi::Foundation::_di_NSCoder coder) = 0 ;
	virtual void __cdecl setDelegate(_di_MTKViewDelegate delegate) = 0 ;
	virtual _di_MTKViewDelegate __cdecl delegate() = 0 ;
	virtual void __cdecl setDevice(Macapi::Metal::_di_MTLDevice device) = 0 ;
	virtual Macapi::Metal::_di_MTLDevice __cdecl device() = 0 ;
	virtual _di_CAMetalDrawable __cdecl currentDrawable() = 0 ;
	virtual void __cdecl setFramebufferOnly(bool framebufferOnly) = 0 ;
	virtual bool __cdecl framebufferOnly() = 0 ;
	virtual void __cdecl setPresentsWithTransaction(bool presentsWithTransaction) = 0 ;
	virtual bool __cdecl presentsWithTransaction() = 0 ;
	virtual void __cdecl setColorPixelFormat(unsigned long colorPixelFormat) = 0 ;
	virtual unsigned long __cdecl colorPixelFormat() = 0 ;
	virtual void __cdecl setDepthStencilPixelFormat(unsigned long depthStencilPixelFormat) = 0 ;
	virtual unsigned long __cdecl depthStencilPixelFormat() = 0 ;
	virtual void __cdecl setSampleCount(unsigned long sampleCount) = 0 ;
	virtual unsigned long __cdecl sampleCount() = 0 ;
	virtual void __cdecl setClearColor(Macapi::Metal::MTLClearColor clearColor) = 0 ;
	virtual Macapi::Metal::MTLClearColor __cdecl clearColor() = 0 ;
	virtual void __cdecl setClearDepth(double clearDepth) = 0 ;
	virtual double __cdecl clearDepth() = 0 ;
	virtual void __cdecl setClearStencil(unsigned long clearStencil) = 0 ;
	virtual unsigned long __cdecl clearStencil() = 0 ;
	virtual Macapi::Metal::_di_MTLTexture __cdecl depthStencilTexture() = 0 ;
	virtual Macapi::Metal::_di_MTLTexture __cdecl multisampleColorTexture() = 0 ;
	virtual void __cdecl releaseDrawables() = 0 ;
	virtual Macapi::Metal::_di_MTLRenderPassDescriptor __cdecl currentRenderPassDescriptor() = 0 ;
	virtual void __cdecl setPreferredFramesPerSecond(long preferredFramesPerSecond) = 0 ;
	virtual long __cdecl preferredFramesPerSecond() = 0 ;
	virtual void __cdecl setEnableSetNeedsDisplay(bool enableSetNeedsDisplay) = 0 ;
	virtual bool __cdecl enableSetNeedsDisplay() = 0 ;
	virtual void __cdecl setAutoResizeDrawable(bool autoResizeDrawable) = 0 ;
	virtual bool __cdecl autoResizeDrawable() = 0 ;
	virtual void __cdecl setDrawableSize(Iosapi::Foundation::NSSize drawableSize) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl drawableSize() = 0 ;
	virtual void __cdecl setPaused(bool paused) = 0 ;
	virtual bool __cdecl isPaused() = 0 ;
	virtual void __cdecl setColorspace(void * colorspace) = 0 ;
	virtual void * __cdecl colorspace() = 0 ;
	virtual void __cdecl draw() = 0 ;
};

class PASCALIMPLEMENTATION TMTKView : public Macapi::Objectivec::TOCGenericImport__2<_di_MTKViewClass,_di_MTKView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTKViewClass,_di_MTKView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTKView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTKViewClass,_di_MTKView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTKView() { }
	
};


typedef void * PMTKView;

__interface  INTERFACE_UUID("{026B6EB0-0189-4D90-A7B1-DE09E924E6B0}") MTKTextureLoaderClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{FF17ED92-6D41-462F-93E6-CD6BB30C31DC}") MTKTextureLoader  : public Iosapi::Foundation::NSObject 
{
	virtual Macapi::Metal::_di_MTLDevice __cdecl device() = 0 ;
	virtual _di_MTKTextureLoader __cdecl initWithDevice(Macapi::Metal::_di_MTLDevice device) = 0 ;
	virtual void __cdecl newTextureWithContentsOfURLOptionsCompletionHandler(Iosapi::Foundation::_di_NSURL URL, Iosapi::Foundation::_di_NSDictionary options, MTKTextureLoaderCallback completionHandler) = 0 ;
	virtual void __cdecl newTextureWithNameScaleFactorBundleOptionsCompletionHandler(Iosapi::Foundation::_di_NSString name, double scaleFactor, Iosapi::Foundation::_di_NSBundle bundle, Iosapi::Foundation::_di_NSDictionary options, MTKTextureLoaderCallback completionHandler) = 0 ;
	virtual void __cdecl newTexturesWithContentsOfURLsOptionsCompletionHandler(Iosapi::Foundation::_di_NSArray URLs, Iosapi::Foundation::_di_NSDictionary options, MTKTextureLoaderArrayCallback completionHandler) = 0 ;
	virtual void __cdecl newTexturesWithNames(Iosapi::Foundation::_di_NSArray names, double scaleFactor, Iosapi::Foundation::_di_NSBundle bundle, Iosapi::Foundation::_di_NSDictionary options, MTKTextureLoaderArrayCallback completionHandler) = 0 ;
	virtual void __cdecl newTextureWithDataOptionsCompletionHandler(Iosapi::Foundation::_di_NSData data, Iosapi::Foundation::_di_NSDictionary options, MTKTextureLoaderCallback completionHandler) = 0 ;
	virtual void __cdecl newTextureWithCGImageOptionsCompletionHandler(void * cgImage, Iosapi::Foundation::_di_NSDictionary options, MTKTextureLoaderCallback completionHandler) = 0 ;
	virtual Macapi::Metal::_di_MTLTexture __cdecl newTextureWithContentsOfURLOptionsError(Iosapi::Foundation::_di_NSURL URL, Iosapi::Foundation::_di_NSDictionary options, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl newTexturesWithContentsOfURLsOptionsError(Iosapi::Foundation::_di_NSArray URLs, Iosapi::Foundation::_di_NSDictionary options, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual Macapi::Metal::_di_MTLTexture __cdecl newTextureWithDataOptionsError(Iosapi::Foundation::_di_NSData data, Iosapi::Foundation::_di_NSDictionary options, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual Macapi::Metal::_di_MTLTexture __cdecl newTextureWithCGImageOptionsError(void * cgImage, Iosapi::Foundation::_di_NSDictionary options, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual Macapi::Metal::_di_MTLTexture __cdecl newTextureWithNameScaleFactorBundleOptionsError(Iosapi::Foundation::_di_NSString name, double scaleFactor, Iosapi::Foundation::_di_NSBundle bundle, Iosapi::Foundation::_di_NSDictionary options, Iosapi::Foundation::_di_NSError error) = 0 ;
};

class PASCALIMPLEMENTATION TMTKTextureLoader : public Macapi::Objectivec::TOCGenericImport__2<_di_MTKTextureLoaderClass,_di_MTKTextureLoader>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTKTextureLoaderClass,_di_MTKTextureLoader> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTKTextureLoader(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTKTextureLoaderClass,_di_MTKTextureLoader>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTKTextureLoader() { }
	
};


typedef void * PMTKTextureLoader;

__interface  INTERFACE_UUID("{D8C9C4B7-69D5-4228-831D-21297EC54825}") MTKMeshBufferAllocatorClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{6268F2C2-09C9-4EE5-B044-2AC06E70CB4B}") MTKMeshBufferAllocator  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTKMeshBufferAllocator __cdecl initWithDevice(Macapi::Metal::_di_MTLDevice device) = 0 ;
	virtual Macapi::Metal::_di_MTLDevice __cdecl device() = 0 ;
};

class PASCALIMPLEMENTATION TMTKMeshBufferAllocator : public Macapi::Objectivec::TOCGenericImport__2<_di_MTKMeshBufferAllocatorClass,_di_MTKMeshBufferAllocator>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTKMeshBufferAllocatorClass,_di_MTKMeshBufferAllocator> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTKMeshBufferAllocator(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTKMeshBufferAllocatorClass,_di_MTKMeshBufferAllocator>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTKMeshBufferAllocator() { }
	
};


typedef void * PMTKMeshBufferAllocator;

__interface  INTERFACE_UUID("{79D15C52-086C-4712-88A7-3E301CF05F2C}") MTKMeshBufferClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{C6EE4B6C-BED5-4D66-852B-6C9FE84CBCC7}") MTKMeshBuffer  : public Iosapi::Foundation::NSObject 
{
	virtual unsigned long __cdecl length() = 0 ;
	virtual _di_MTKMeshBufferAllocator __cdecl allocator() = 0 ;
	virtual Macapi::Metal::_di_MTLBuffer __cdecl buffer() = 0 ;
	virtual unsigned long __cdecl offset() = 0 ;
	virtual int __cdecl type() = 0 ;
};

class PASCALIMPLEMENTATION TMTKMeshBuffer : public Macapi::Objectivec::TOCGenericImport__2<_di_MTKMeshBufferClass,_di_MTKMeshBuffer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTKMeshBufferClass,_di_MTKMeshBuffer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTKMeshBuffer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTKMeshBufferClass,_di_MTKMeshBuffer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTKMeshBuffer() { }
	
};


typedef void * PMTKMeshBuffer;

__interface  INTERFACE_UUID("{D7BA7E0A-003F-4B22-9B80-B738A1C0C46E}") MTKMeshClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{EFD4A437-5B0E-4897-BD57-D3C854908D48}") MTKMesh  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl vertexBuffers() = 0 ;
	virtual System::PInteger __cdecl vertexDescriptor() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl submeshes() = 0 ;
	virtual unsigned long __cdecl vertexCount() = 0 ;
	virtual void __cdecl setName(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
};

class PASCALIMPLEMENTATION TMTKMesh : public Macapi::Objectivec::TOCGenericImport__2<_di_MTKMeshClass,_di_MTKMesh>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTKMeshClass,_di_MTKMesh> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTKMesh(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTKMeshClass,_di_MTKMesh>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTKMesh() { }
	
};


typedef void * PMTKMesh;

__interface  INTERFACE_UUID("{EB3325F1-09EF-437A-809A-7390B52B6816}") MTKSubmeshClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D4576A09-D9E2-4388-8F92-718A34A1A23E}") MTKSubmesh  : public Iosapi::Foundation::NSObject 
{
	virtual unsigned long __cdecl primitiveType() = 0 ;
	virtual unsigned long __cdecl indexType() = 0 ;
	virtual _di_MTKMeshBuffer __cdecl indexBuffer() = 0 ;
	virtual unsigned long __cdecl indexCount() = 0 ;
	virtual _di_MTKMesh __cdecl mesh() = 0 ;
	virtual void __cdecl setName(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
};

class PASCALIMPLEMENTATION TMTKSubmesh : public Macapi::Objectivec::TOCGenericImport__2<_di_MTKSubmeshClass,_di_MTKSubmesh>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTKSubmeshClass,_di_MTKSubmesh> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTKSubmesh(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTKSubmeshClass,_di_MTKSubmesh>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTKSubmesh() { }
	
};


typedef void * PMTKSubmesh;

__interface  INTERFACE_UUID("{5FF37054-5EAA-46DB-B278-60C97C9EDCB3}") MTKViewDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl mtkView(_di_MTKView view, Iosapi::Foundation::NSSize drawableSizeWillChange) = 0 ;
	virtual void __cdecl drawInMTKView(_di_MTKView view) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
#define libMetalKit u"/System/Library/Frameworks/MetalKit.framework/MetalKit"
extern "C" System::PInteger __cdecl MTKModelIOVertexDescriptorFromMetal(void * metalDescriptor);
extern "C" System::PInteger __cdecl MTKModelIOVertexDescriptorFromMetalWithError(void * metalDescriptor, void * error);
extern "C" void * __cdecl MTKMetalVertexDescriptorFromModelIO(System::PInteger modelIODescriptor);
extern "C" void * __cdecl MTKMetalVertexDescriptorFromModelIOWithError(System::PInteger modelIODescriptor, void * error);
extern "C" int __cdecl MTKModelIOVertexFormatFromMetal(unsigned long vertexFormat);
extern "C" unsigned long __cdecl MTKMetalVertexFormatFromModelIO(int vertexFormat);
extern DELPHI_PACKAGE void * __fastcall MTKTextureLoaderErrorDomain(void);
extern DELPHI_PACKAGE void * __fastcall MTKTextureLoaderErrorKey(void);
extern DELPHI_PACKAGE void * __fastcall MTKTextureLoaderOptionAllocateMipmaps(void);
extern DELPHI_PACKAGE void * __fastcall MTKTextureLoaderOptionGenerateMipmaps(void);
extern DELPHI_PACKAGE void * __fastcall MTKTextureLoaderOptionSRGB(void);
extern DELPHI_PACKAGE void * __fastcall MTKTextureLoaderOptionTextureUsage(void);
extern DELPHI_PACKAGE void * __fastcall MTKTextureLoaderOptionTextureCPUCacheMode(void);
extern DELPHI_PACKAGE void * __fastcall MTKTextureLoaderOptionTextureStorageMode(void);
extern DELPHI_PACKAGE void * __fastcall MTKTextureLoaderOptionCubeLayout(void);
extern DELPHI_PACKAGE void * __fastcall MTKTextureLoaderCubeLayoutVertical(void);
extern DELPHI_PACKAGE void * __fastcall MTKTextureLoaderOptionOrigin(void);
extern DELPHI_PACKAGE void * __fastcall MTKTextureLoaderOriginTopLeft(void);
extern DELPHI_PACKAGE void * __fastcall MTKTextureLoaderOriginBottomLeft(void);
extern DELPHI_PACKAGE void * __fastcall MTKTextureLoaderOriginFlippedVertically(void);
extern DELPHI_PACKAGE void * __fastcall MTKModelErrorDomain(void);
extern DELPHI_PACKAGE void * __fastcall MTKModelErrorKey(void);
}	/* namespace Metalkit */
}	/* namespace Macapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI_METALKIT)
using namespace Macapi::Metalkit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI)
using namespace Macapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Macapi_MetalkitHPP
