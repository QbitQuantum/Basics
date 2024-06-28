// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.GLKit.pas' rev: 34.00 (iOS)

#ifndef Iosapi_GlkitHPP
#define Iosapi_GlkitHPP

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
#include <Macapi.CoreFoundation.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <iOSapi.OpenGLES.hpp>
#include <iOSapi.UIKit.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Glkit
{
//-- forward type declarations -----------------------------------------------
struct GLKMatrix2;
struct GLKMatrix3;
struct GLKMatrix4;
struct GLKVector2;
struct GLKVector3;
struct GLKVector4;
struct GLKQuaternion;
__interface DELPHIINTERFACE GLKNamedEffect;
typedef System::DelphiInterface<GLKNamedEffect> _di_GLKNamedEffect;
__interface DELPHIINTERFACE GLKViewControllerDelegate;
typedef System::DelphiInterface<GLKViewControllerDelegate> _di_GLKViewControllerDelegate;
__interface DELPHIINTERFACE GLKViewDelegate;
typedef System::DelphiInterface<GLKViewDelegate> _di_GLKViewDelegate;
__interface DELPHIINTERFACE GLKTextureInfoClass;
typedef System::DelphiInterface<GLKTextureInfoClass> _di_GLKTextureInfoClass;
__interface DELPHIINTERFACE GLKTextureInfo;
typedef System::DelphiInterface<GLKTextureInfo> _di_GLKTextureInfo;
class DELPHICLASS TGLKTextureInfo;
__interface DELPHIINTERFACE GLKSkyboxEffectClass;
typedef System::DelphiInterface<GLKSkyboxEffectClass> _di_GLKSkyboxEffectClass;
__interface DELPHIINTERFACE GLKSkyboxEffect;
typedef System::DelphiInterface<GLKSkyboxEffect> _di_GLKSkyboxEffect;
class DELPHICLASS TGLKSkyboxEffect;
__interface DELPHIINTERFACE GLKViewControllerClass;
typedef System::DelphiInterface<GLKViewControllerClass> _di_GLKViewControllerClass;
__interface DELPHIINTERFACE GLKViewController;
typedef System::DelphiInterface<GLKViewController> _di_GLKViewController;
class DELPHICLASS TGLKViewController;
__interface DELPHIINTERFACE GLKViewClass;
typedef System::DelphiInterface<GLKViewClass> _di_GLKViewClass;
__interface DELPHIINTERFACE GLKView;
typedef System::DelphiInterface<GLKView> _di_GLKView;
class DELPHICLASS TGLKView;
__interface DELPHIINTERFACE GLKTextureLoaderClass;
typedef System::DelphiInterface<GLKTextureLoaderClass> _di_GLKTextureLoaderClass;
__interface DELPHIINTERFACE GLKTextureLoader;
typedef System::DelphiInterface<GLKTextureLoader> _di_GLKTextureLoader;
class DELPHICLASS TGLKTextureLoader;
__interface DELPHIINTERFACE GLKEffectPropertyClass;
typedef System::DelphiInterface<GLKEffectPropertyClass> _di_GLKEffectPropertyClass;
__interface DELPHIINTERFACE GLKEffectProperty;
typedef System::DelphiInterface<GLKEffectProperty> _di_GLKEffectProperty;
class DELPHICLASS TGLEffectProperty;
__interface DELPHIINTERFACE GLKEffectPropertyLightClass;
typedef System::DelphiInterface<GLKEffectPropertyLightClass> _di_GLKEffectPropertyLightClass;
__interface DELPHIINTERFACE GLKEffectPropertyLight;
typedef System::DelphiInterface<GLKEffectPropertyLight> _di_GLKEffectPropertyLight;
class DELPHICLASS TGLKEffectPropertyLight;
__interface DELPHIINTERFACE GLKEffectPropertyFogClass;
typedef System::DelphiInterface<GLKEffectPropertyFogClass> _di_GLKEffectPropertyFogClass;
__interface DELPHIINTERFACE GLKEffectPropertyFog;
typedef System::DelphiInterface<GLKEffectPropertyFog> _di_GLKEffectPropertyFog;
class DELPHICLASS TGLKEffectPropertyFog;
__interface DELPHIINTERFACE GLKBaseEffectClass;
typedef System::DelphiInterface<GLKBaseEffectClass> _di_GLKBaseEffectClass;
__interface DELPHIINTERFACE GLKBaseEffect;
typedef System::DelphiInterface<GLKBaseEffect> _di_GLKBaseEffect;
class DELPHICLASS TGLKBaseEffect;
__interface DELPHIINTERFACE GLKEffectPropertyTransformClass;
typedef System::DelphiInterface<GLKEffectPropertyTransformClass> _di_GLKEffectPropertyTransformClass;
__interface DELPHIINTERFACE GLKEffectPropertyTransform;
typedef System::DelphiInterface<GLKEffectPropertyTransform> _di_GLKEffectPropertyTransform;
class DELPHICLASS TGLKEffectPropertyTransform;
__interface DELPHIINTERFACE GLKEffectPropertyTextureClass;
typedef System::DelphiInterface<GLKEffectPropertyTextureClass> _di_GLKEffectPropertyTextureClass;
__interface DELPHIINTERFACE GLKEffectPropertyTexture;
typedef System::DelphiInterface<GLKEffectPropertyTexture> _di_GLKEffectPropertyTexture;
class DELPHICLASS TGLKEffectPropertyTexture;
__interface DELPHIINTERFACE GLKEffectPropertyMaterialClass;
typedef System::DelphiInterface<GLKEffectPropertyMaterialClass> _di_GLKEffectPropertyMaterialClass;
__interface DELPHIINTERFACE GLKEffectPropertyMaterial;
typedef System::DelphiInterface<GLKEffectPropertyMaterial> _di_GLKEffectPropertyMaterial;
class DELPHICLASS TGLKEffectPropertyMaterial;
__interface DELPHIINTERFACE GLKReflectionMapEffectClass;
typedef System::DelphiInterface<GLKReflectionMapEffectClass> _di_GLKReflectionMapEffectClass;
__interface DELPHIINTERFACE GLKReflectionMapEffect;
typedef System::DelphiInterface<GLKReflectionMapEffect> _di_GLKReflectionMapEffect;
class DELPHICLASS TGLKReflectionMapEffect;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD GLKMatrix2
{
	
public:
	union
	{
		struct 
		{
			System::StaticArray<float, 4> m;
		};
		struct 
		{
			System::StaticArray<System::StaticArray<float, 2>, 2> m2;
		};
		struct 
		{
			float m00;
			float m01;
			float m10;
			float m11;
		};
		
	};
};


typedef GLKMatrix2 *PGLKMatrix2;

struct DECLSPEC_DRECORD GLKMatrix3
{
	
public:
	union
	{
		struct 
		{
			System::StaticArray<float, 9> m;
		};
		struct 
		{
			float m00;
			float m01;
			float m02;
			float m10;
			float m11;
			float m12;
			float m20;
			float m21;
			float m22;
		};
		
	};
};


typedef GLKMatrix3 *PGLKMatrix3;

struct DECLSPEC_DRECORD GLKMatrix4
{
	
public:
	union
	{
		struct 
		{
			System::StaticArray<float, 16> m;
		};
		struct 
		{
			float m00;
			float m01;
			float m02;
			float m03;
			float m10;
			float m11;
			float m12;
			float m13;
			float m20;
			float m21;
			float m22;
			float m23;
			float m30;
			float m31;
			float m32;
			float m33;
		};
		
	};
};


typedef GLKMatrix4 *PGLKMatrix4;

struct DECLSPEC_DRECORD GLKVector2
{
	
public:
	union
	{
		struct 
		{
			System::StaticArray<float, 2> v;
		};
		struct 
		{
			float s;
			float t;
		};
		struct 
		{
			float x;
			float y;
		};
		
	};
};


typedef GLKVector2 *PGLKVector;

struct DECLSPEC_DRECORD GLKVector3
{
	
public:
	union
	{
		struct 
		{
			System::StaticArray<float, 3> v;
		};
		struct 
		{
			float s;
			float t;
			float p;
		};
		struct 
		{
			float r;
			float g;
			float b;
		};
		struct 
		{
			float x;
			float y;
			float z;
		};
		
	};
};


typedef GLKVector3 *PGLKVector3;

struct DECLSPEC_DRECORD GLKVector4
{
	
public:
	union
	{
		struct 
		{
			System::StaticArray<float, 4> v;
		};
		struct 
		{
			float s;
			float t;
			float p;
			float q;
		};
		struct 
		{
			float r;
			float g;
			float b;
			float a;
		};
		struct 
		{
			float x;
			float y;
			float z;
			float w;
		};
		
	};
};


typedef GLKVector4 *PGLKVector4;

struct DECLSPEC_DRECORD GLKQuaternion
{
	
public:
	union
	{
		struct 
		{
			System::StaticArray<float, 4> q;
		};
		struct 
		{
			float x;
			float y;
			float z;
			float w;
		};
		struct 
		{
			GLKVector3 v;
			float s;
		};
		
	};
};


typedef GLKQuaternion *PGLKQuaternion;

typedef unsigned long GLKLightingType;

typedef void * GLKMatrixStackRef;

typedef unsigned long GLKTextureInfoAlphaState;

typedef unsigned long GLKTextureInfoOrigin;

typedef unsigned long GLKTextureTarget;

typedef unsigned long GLKViewDrawableColorFormat;

typedef unsigned long GLKViewDrawableDepthFormat;

typedef unsigned long GLKViewDrawableStencilFormat;

typedef unsigned long GLKViewDrawableMultisample;

typedef bool *P_Bool;

__interface  INTERFACE_UUID("{0819BD68-3DB4-41B5-8FE4-1D12653231A2}") GLKNamedEffect  : public System::IInterface 
{
	virtual void __cdecl prepareToDraw() = 0 ;
};

__interface  INTERFACE_UUID("{F716096A-E94D-46FB-8E85-A9964533B1F6}") GLKViewControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl glkViewController(_di_GLKViewController controller, bool willPause) = 0 ;
	virtual void __cdecl glkViewControllerUpdate(_di_GLKViewController controller) = 0 ;
};

__interface  INTERFACE_UUID("{13D41829-A7B1-4DCD-BDE4-FB66DC64655D}") GLKViewDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl glkView(_di_GLKView view, Iosapi::Foundation::NSRect drawInRect) = 0 ;
};

__interface  INTERFACE_UUID("{44F4BC8F-A442-4EBF-A8BC-A19B19BE5301}") GLKTextureInfoClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{07470F2B-8B29-41DF-83F4-4DEB6405D568}") GLKTextureInfo  : public Iosapi::Foundation::NSObject 
{
	virtual unsigned long __cdecl alphaState() = 0 ;
	virtual bool __cdecl containsMipmaps() = 0 ;
	virtual unsigned __cdecl height() = 0 ;
	virtual unsigned __cdecl name() = 0 ;
	virtual unsigned __cdecl target() = 0 ;
	virtual unsigned long __cdecl textureOrigin() = 0 ;
	virtual unsigned __cdecl width() = 0 ;
};

class PASCALIMPLEMENTATION TGLKTextureInfo : public Macapi::Objectivec::TOCGenericImport__2<_di_GLKTextureInfoClass,_di_GLKTextureInfo>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GLKTextureInfoClass,_di_GLKTextureInfo> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGLKTextureInfo(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GLKTextureInfoClass,_di_GLKTextureInfo>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGLKTextureInfo() { }
	
};


__interface  INTERFACE_UUID("{50B752C5-C8CE-41D3-A7B9-33A3293416B2}") GLKSkyboxEffectClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{5FFDD85F-8ED1-4B2F-9F72-561B916515B3}") GLKSkyboxEffect  : public Iosapi::Foundation::NSObject 
{
	virtual GLKVector3 __cdecl center() = 0 ;
	virtual void __cdecl draw() = 0 ;
	virtual void __cdecl prepareToDraw() = 0 ;
	virtual void __cdecl setCenter(GLKVector3 center) = 0 ;
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label_) = 0 ;
	virtual void __cdecl setXSize(float xSize) = 0 ;
	virtual void __cdecl setYSize(float ySize) = 0 ;
	virtual void __cdecl setZSize(float zSize) = 0 ;
	virtual _di_GLKEffectPropertyTexture __cdecl textureCubeMap() = 0 ;
	virtual _di_GLKEffectPropertyTransform __cdecl transform() = 0 ;
	virtual float __cdecl xSize() = 0 ;
	virtual float __cdecl ySize() = 0 ;
	virtual float __cdecl zSize() = 0 ;
};

class PASCALIMPLEMENTATION TGLKSkyboxEffect : public Macapi::Objectivec::TOCGenericImport__2<_di_GLKSkyboxEffectClass,_di_GLKSkyboxEffect>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GLKSkyboxEffectClass,_di_GLKSkyboxEffect> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGLKSkyboxEffect(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GLKSkyboxEffectClass,_di_GLKSkyboxEffect>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGLKSkyboxEffect() { }
	
};


__interface  INTERFACE_UUID("{B91BC5ED-6D33-41BD-ADEA-F26BFEB2FDD2}") GLKViewControllerClass  : public Iosapi::Uikit::UIViewControllerClass 
{
	
};

__interface  INTERFACE_UUID("{823166A6-D4CB-42C5-ADB9-C4E00EB11132}") GLKViewController  : public Iosapi::Uikit::UIViewController 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual long __cdecl framesDisplayed() = 0 ;
	virtual long __cdecl framesPerSecond() = 0 ;
	virtual bool __cdecl isPaused() = 0 ;
	virtual bool __cdecl pauseOnWillResignActive() = 0 ;
	virtual long __cdecl preferredFramesPerSecond() = 0 ;
	virtual bool __cdecl resumeOnDidBecomeActive() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setPauseOnWillResignActive(bool pauseOnWillResignActive) = 0 ;
	virtual void __cdecl setPaused(bool paused) = 0 ;
	virtual void __cdecl setPreferredFramesPerSecond(long preferredFramesPerSecond) = 0 ;
	virtual void __cdecl setResumeOnDidBecomeActive(bool resumeOnDidBecomeActive) = 0 ;
	virtual double __cdecl timeSinceFirstResume() = 0 ;
	virtual double __cdecl timeSinceLastDraw() = 0 ;
	virtual double __cdecl timeSinceLastResume() = 0 ;
	virtual double __cdecl timeSinceLastUpdate() = 0 ;
};

class PASCALIMPLEMENTATION TGLKViewController : public Macapi::Objectivec::TOCGenericImport__2<_di_GLKViewControllerClass,_di_GLKViewController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GLKViewControllerClass,_di_GLKViewController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGLKViewController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GLKViewControllerClass,_di_GLKViewController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGLKViewController() { }
	
};


__interface  INTERFACE_UUID("{28B9B440-B979-4CEB-87FC-91EF1B04272F}") GLKViewClass  : public Iosapi::Uikit::UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{F81E4E34-668B-429C-A14B-F85BC87B3E7D}") GLKView  : public Iosapi::Uikit::UIView 
{
	virtual void __cdecl bindDrawable() = 0 ;
	virtual Iosapi::Opengles::_di_EAGLContext __cdecl context() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl deleteDrawable() = 0 ;
	virtual void __cdecl display() = 0 ;
	virtual unsigned long __cdecl drawableColorFormat() = 0 ;
	virtual unsigned long __cdecl drawableDepthFormat() = 0 ;
	virtual long __cdecl drawableHeight() = 0 ;
	virtual unsigned long __cdecl drawableMultisample() = 0 ;
	virtual unsigned long __cdecl drawableStencilFormat() = 0 ;
	virtual long __cdecl drawableWidth() = 0 ;
	virtual bool __cdecl enableSetNeedsDisplay() = 0 ;
	HIDESBASE virtual void * __cdecl initWithFrame(Iosapi::Foundation::NSRect frame, Iosapi::Opengles::_di_EAGLContext context) = 0 ;
	virtual void __cdecl setContext(Iosapi::Opengles::_di_EAGLContext context) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setDrawableColorFormat(unsigned long drawableColorFormat) = 0 ;
	virtual void __cdecl setDrawableDepthFormat(unsigned long drawableDepthFormat) = 0 ;
	virtual void __cdecl setDrawableMultisample(unsigned long drawableMultisample) = 0 ;
	virtual void __cdecl setDrawableStencilFormat(unsigned long drawableStencilFormat) = 0 ;
	virtual void __cdecl setEnableSetNeedsDisplay(bool enableSetNeedsDisplay) = 0 ;
	virtual Iosapi::Uikit::_di_UIImage __cdecl snapshot() = 0 ;
};

class PASCALIMPLEMENTATION TGLKView : public Macapi::Objectivec::TOCGenericImport__2<_di_GLKViewClass,_di_GLKView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GLKViewClass,_di_GLKView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGLKView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GLKViewClass,_di_GLKView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGLKView() { }
	
};


__interface  INTERFACE_UUID("{1ABC3371-538E-49E3-B446-25474C452F53}") GLKTextureLoaderClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_GLKTextureInfo __cdecl cubeMapWithContentsOfFile(Iosapi::Foundation::_di_NSString path, Iosapi::Foundation::_di_NSDictionary options, Iosapi::Foundation::_di_NSError error) = 0 /* overload */;
	virtual _di_GLKTextureInfo __cdecl cubeMapWithContentsOfFiles(Iosapi::Foundation::_di_NSArray paths, Iosapi::Foundation::_di_NSDictionary options, Iosapi::Foundation::_di_NSError error) = 0 /* overload */;
	virtual _di_GLKTextureInfo __cdecl cubeMapWithContentsOfURL(Iosapi::Foundation::_di_NSURL url, Iosapi::Foundation::_di_NSDictionary options, Iosapi::Foundation::_di_NSError error) = 0 /* overload */;
	virtual _di_GLKTextureInfo __cdecl textureWithCGImage(void * cgImage, Iosapi::Foundation::_di_NSDictionary options, Iosapi::Foundation::_di_NSError error) = 0 /* overload */;
	virtual _di_GLKTextureInfo __cdecl textureWithContentsOfData(Iosapi::Foundation::_di_NSData data, Iosapi::Foundation::_di_NSDictionary options, Iosapi::Foundation::_di_NSError error) = 0 /* overload */;
	virtual _di_GLKTextureInfo __cdecl textureWithContentsOfFile(Iosapi::Foundation::_di_NSString path, Iosapi::Foundation::_di_NSDictionary options, Iosapi::Foundation::_di_NSError error) = 0 /* overload */;
	virtual _di_GLKTextureInfo __cdecl textureWithContentsOfURL(Iosapi::Foundation::_di_NSURL url, Iosapi::Foundation::_di_NSDictionary options, Iosapi::Foundation::_di_NSError error) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{55813C5A-7908-4E42-BF43-713A81BFBE98}") GLKTextureLoader  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithSharegroup(Iosapi::Foundation::_di_NSObject sharegroup) = 0 ;
};

class PASCALIMPLEMENTATION TGLKTextureLoader : public Macapi::Objectivec::TOCGenericImport__2<_di_GLKTextureLoaderClass,_di_GLKTextureLoader>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GLKTextureLoaderClass,_di_GLKTextureLoader> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGLKTextureLoader(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GLKTextureLoaderClass,_di_GLKTextureLoader>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGLKTextureLoader() { }
	
};


__interface  INTERFACE_UUID("{8A72FF03-5841-4119-AE77-0D1412173280}") GLKEffectPropertyClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{2EEF7FEB-628C-4E41-9A4F-B6D0956A682C}") GLKEffectProperty  : public Iosapi::Foundation::NSObject 
{
	
};

class PASCALIMPLEMENTATION TGLEffectProperty : public Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyClass,_di_GLKEffectProperty>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyClass,_di_GLKEffectProperty> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGLEffectProperty(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyClass,_di_GLKEffectProperty>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGLEffectProperty() { }
	
};


__interface  INTERFACE_UUID("{F44FD652-CE58-48A4-ADED-D00532D2D7CA}") GLKEffectPropertyLightClass  : public GLKEffectPropertyClass 
{
	
};

__interface  INTERFACE_UUID("{420CAF92-DD2B-4884-B9BC-692831D43B2D}") GLKEffectPropertyLight  : public GLKEffectProperty 
{
	virtual GLKVector4 __cdecl ambientColor() = 0 ;
	virtual float __cdecl constantAttenuation() = 0 ;
	virtual GLKVector4 __cdecl diffuseColor() = 0 ;
	virtual System::Byte __cdecl enabled() = 0 ;
	virtual float __cdecl linearAttenuation() = 0 ;
	virtual GLKVector4 __cdecl position() = 0 ;
	virtual float __cdecl quadraticAttenuation() = 0 ;
	virtual void __cdecl setAmbientColor(GLKVector4 ambientColor) = 0 ;
	virtual void __cdecl setConstantAttenuation(float constantAttenuation) = 0 ;
	virtual void __cdecl setDiffuseColor(GLKVector4 diffuseColor) = 0 ;
	virtual void __cdecl setEnabled(System::Byte enabled) = 0 ;
	virtual void __cdecl setLinearAttenuation(float linearAttenuation) = 0 ;
	virtual void __cdecl setPosition(GLKVector4 position) = 0 ;
	virtual void __cdecl setQuadraticAttenuation(float quadraticAttenuation) = 0 ;
	virtual void __cdecl setSpecularColor(GLKVector4 specularColor) = 0 ;
	virtual void __cdecl setSpotCutoff(float spotCutoff) = 0 ;
	virtual void __cdecl setSpotDirection(GLKVector3 spotDirection) = 0 ;
	virtual void __cdecl setSpotExponent(float spotExponent) = 0 ;
	virtual void __cdecl setTransform(_di_GLKEffectPropertyTransform transform) = 0 ;
	virtual GLKVector4 __cdecl specularColor() = 0 ;
	virtual float __cdecl spotCutoff() = 0 ;
	virtual GLKVector3 __cdecl spotDirection() = 0 ;
	virtual float __cdecl spotExponent() = 0 ;
	virtual _di_GLKEffectPropertyTransform __cdecl transform() = 0 ;
};

class PASCALIMPLEMENTATION TGLKEffectPropertyLight : public Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyLightClass,_di_GLKEffectPropertyLight>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyLightClass,_di_GLKEffectPropertyLight> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGLKEffectPropertyLight(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyLightClass,_di_GLKEffectPropertyLight>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGLKEffectPropertyLight() { }
	
};


__interface  INTERFACE_UUID("{220A723B-C579-498E-BF75-A933C7484D17}") GLKEffectPropertyFogClass  : public GLKEffectPropertyClass 
{
	
};

__interface  INTERFACE_UUID("{7ADF9206-B02D-48DD-B5C0-01DB33FFE5ED}") GLKEffectPropertyFog  : public GLKEffectProperty 
{
	virtual GLKVector4 __cdecl color() = 0 ;
	virtual float __cdecl density() = 0 ;
	virtual System::Byte __cdecl enabled() = 0 ;
	virtual int __cdecl mode() = 0 ;
	virtual void __cdecl setColor(GLKVector4 color) = 0 ;
	virtual void __cdecl setDensity(float density) = 0 ;
	virtual void __cdecl setEnabled(System::Byte enabled) = 0 ;
	virtual void __cdecl setEnd(float end_) = 0 ;
	virtual void __cdecl setMode(int mode) = 0 ;
	virtual void __cdecl setStart(float start) = 0 ;
	virtual float __cdecl start() = 0 ;
};

class PASCALIMPLEMENTATION TGLKEffectPropertyFog : public Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyFogClass,_di_GLKEffectPropertyFog>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyFogClass,_di_GLKEffectPropertyFog> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGLKEffectPropertyFog(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyFogClass,_di_GLKEffectPropertyFog>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGLKEffectPropertyFog() { }
	
};


__interface  INTERFACE_UUID("{C97FCB25-126C-4D01-90BF-CE5401ECE7F9}") GLKBaseEffectClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{4164AE3C-7A4D-4140-8635-EB42B66EB923}") GLKBaseEffect  : public Iosapi::Foundation::NSObject 
{
	virtual System::Byte __cdecl colorMaterialEnabled() = 0 ;
	virtual GLKVector4 __cdecl constantColor() = 0 ;
	virtual _di_GLKEffectPropertyFog __cdecl fog() = 0 ;
	virtual _di_GLKEffectPropertyLight __cdecl light0() = 0 ;
	virtual _di_GLKEffectPropertyLight __cdecl light1() = 0 ;
	virtual _di_GLKEffectPropertyLight __cdecl light2() = 0 ;
	virtual GLKVector4 __cdecl lightModelAmbientColor() = 0 ;
	virtual System::Byte __cdecl lightModelTwoSided() = 0 ;
	virtual unsigned long __cdecl lightingType() = 0 ;
	virtual _di_GLKEffectPropertyMaterial __cdecl material() = 0 ;
	virtual void __cdecl prepareToDraw() = 0 ;
	virtual void __cdecl setColorMaterialEnabled(System::Byte colorMaterialEnabled) = 0 ;
	virtual void __cdecl setConstantColor(GLKVector4 constantColor) = 0 ;
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label_) = 0 ;
	virtual void __cdecl setLightModelAmbientColor(GLKVector4 lightModelAmbientColor) = 0 ;
	virtual void __cdecl setLightModelTwoSided(System::Byte lightModelTwoSided) = 0 ;
	virtual void __cdecl setLightingType(unsigned long lightingType) = 0 ;
	virtual void __cdecl setTextureOrder(Iosapi::Foundation::_di_NSArray textureOrder) = 0 ;
	virtual void __cdecl setUseConstantColor(System::Byte useConstantColor) = 0 ;
	virtual _di_GLKEffectPropertyTexture __cdecl texture2d0() = 0 ;
	virtual _di_GLKEffectPropertyTexture __cdecl texture2d1() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl textureOrder() = 0 ;
	virtual _di_GLKEffectPropertyTransform __cdecl transform() = 0 ;
	virtual System::Byte __cdecl useConstantColor() = 0 ;
};

class PASCALIMPLEMENTATION TGLKBaseEffect : public Macapi::Objectivec::TOCGenericImport__2<_di_GLKBaseEffectClass,_di_GLKBaseEffect>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GLKBaseEffectClass,_di_GLKBaseEffect> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGLKBaseEffect(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GLKBaseEffectClass,_di_GLKBaseEffect>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGLKBaseEffect() { }
	
};


__interface  INTERFACE_UUID("{04465087-0655-4DA3-B871-DA77572BFEF9}") GLKEffectPropertyTransformClass  : public GLKEffectPropertyClass 
{
	
};

__interface  INTERFACE_UUID("{ED7132EF-83F1-41B2-8558-41D6B784C7F8}") GLKEffectPropertyTransform  : public GLKEffectProperty 
{
	virtual GLKMatrix4 __cdecl modelviewMatrix() = 0 ;
	virtual GLKMatrix3 __cdecl normalMatrix() = 0 ;
	virtual GLKMatrix4 __cdecl projectionMatrix() = 0 ;
	virtual void __cdecl setModelviewMatrix(GLKMatrix4 modelviewMatrix) = 0 ;
	virtual void __cdecl setProjectionMatrix(GLKMatrix4 projectionMatrix) = 0 ;
};

class PASCALIMPLEMENTATION TGLKEffectPropertyTransform : public Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyTransformClass,_di_GLKEffectPropertyTransform>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyTransformClass,_di_GLKEffectPropertyTransform> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGLKEffectPropertyTransform(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyTransformClass,_di_GLKEffectPropertyTransform>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGLKEffectPropertyTransform() { }
	
};


__interface  INTERFACE_UUID("{F284E6B0-98FE-45BE-B496-D0FE3AEC0A6C}") GLKEffectPropertyTextureClass  : public GLKEffectPropertyClass 
{
	
};

__interface  INTERFACE_UUID("{9AC6CE6F-FBE8-47EF-897B-25EB72819A19}") GLKEffectPropertyTexture  : public GLKEffectProperty 
{
	virtual System::Byte __cdecl enabled() = 0 ;
	virtual int __cdecl envMode() = 0 ;
	virtual unsigned __cdecl name() = 0 ;
	virtual void __cdecl setEnabled(System::Byte enabled) = 0 ;
	virtual void __cdecl setEnvMode(int envMode) = 0 ;
	virtual void __cdecl setName(unsigned name) = 0 ;
	virtual void __cdecl setTarget(unsigned long target) = 0 ;
	virtual unsigned long __cdecl target() = 0 ;
};

class PASCALIMPLEMENTATION TGLKEffectPropertyTexture : public Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyTextureClass,_di_GLKEffectPropertyTexture>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyTextureClass,_di_GLKEffectPropertyTexture> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGLKEffectPropertyTexture(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyTextureClass,_di_GLKEffectPropertyTexture>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGLKEffectPropertyTexture() { }
	
};


__interface  INTERFACE_UUID("{95C31DE9-794B-44C1-A01E-1978900BFC57}") GLKEffectPropertyMaterialClass  : public GLKEffectPropertyClass 
{
	
};

__interface  INTERFACE_UUID("{0B9C5659-94CF-47BB-A84C-D16745ADE8DA}") GLKEffectPropertyMaterial  : public GLKEffectProperty 
{
	virtual GLKVector4 __cdecl ambientColor() = 0 ;
	virtual GLKVector4 __cdecl diffuseColor() = 0 ;
	virtual GLKVector4 __cdecl emissiveColor() = 0 ;
	virtual void __cdecl setAmbientColor(GLKVector4 ambientColor) = 0 ;
	virtual void __cdecl setDiffuseColor(GLKVector4 diffuseColor) = 0 ;
	virtual void __cdecl setEmissiveColor(GLKVector4 emissiveColor) = 0 ;
	virtual void __cdecl setShininess(float shininess) = 0 ;
	virtual void __cdecl setSpecularColor(GLKVector4 specularColor) = 0 ;
	virtual float __cdecl shininess() = 0 ;
	virtual GLKVector4 __cdecl specularColor() = 0 ;
};

class PASCALIMPLEMENTATION TGLKEffectPropertyMaterial : public Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyMaterialClass,_di_GLKEffectPropertyMaterial>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyMaterialClass,_di_GLKEffectPropertyMaterial> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGLKEffectPropertyMaterial(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GLKEffectPropertyMaterialClass,_di_GLKEffectPropertyMaterial>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGLKEffectPropertyMaterial() { }
	
};


__interface  INTERFACE_UUID("{85104CD2-15E8-4D84-BEF8-9D9DEE7BF6EB}") GLKReflectionMapEffectClass  : public GLKBaseEffectClass 
{
	
};

__interface  INTERFACE_UUID("{14D4F2D4-FACF-4F8F-940C-E52A22FF8037}") GLKReflectionMapEffect  : public GLKBaseEffect 
{
	virtual GLKMatrix3 __cdecl matrix() = 0 ;
	HIDESBASE virtual void __cdecl prepareToDraw() = 0 ;
	virtual void __cdecl setMatrix(GLKMatrix3 matrix) = 0 ;
	virtual _di_GLKEffectPropertyTexture __cdecl textureCubeMap() = 0 ;
};

class PASCALIMPLEMENTATION TGLKReflectionMapEffect : public Macapi::Objectivec::TOCGenericImport__2<_di_GLKReflectionMapEffectClass,_di_GLKReflectionMapEffect>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_GLKReflectionMapEffectClass,_di_GLKReflectionMapEffect> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TGLKReflectionMapEffect(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_GLKReflectionMapEffectClass,_di_GLKReflectionMapEffect>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TGLKReflectionMapEffect() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 GLKFogModeExp = System::Int8(0x0);
static constexpr System::Int8 GLKFogModeExp2 = System::Int8(0x1);
static constexpr System::Int8 GLKFogModeLinear = System::Int8(0x2);
static constexpr System::Int8 GLKLightingTypePerPixel = System::Int8(0x1);
static constexpr System::Int8 GLKLightingTypePerVertex = System::Int8(0x0);
static constexpr System::Int8 GLKTextureEnvModeDecal = System::Int8(0x2);
static constexpr System::Int8 GLKTextureEnvModeModulate = System::Int8(0x1);
static constexpr System::Int8 GLKTextureEnvModeReplace = System::Int8(0x0);
static constexpr System::Int8 GLKTextureInfoAlphaStateNonPremultiplied = System::Int8(0x1);
static constexpr System::Int8 GLKTextureInfoAlphaStateNone = System::Int8(0x0);
static constexpr System::Int8 GLKTextureInfoAlphaStatePremultiplied = System::Int8(0x2);
static constexpr System::Int8 GLKTextureInfoOriginBottomLeft = System::Int8(0x2);
static constexpr System::Int8 GLKTextureInfoOriginTopLeft = System::Int8(0x1);
static constexpr System::Int8 GLKTextureInfoOriginUnknown = System::Int8(0x0);
static constexpr System::Int8 GLKTextureLoaderErrorAlphaPremultiplicationFailure = System::Int8(0x10);
static constexpr System::Int8 GLKTextureLoaderErrorCompressedTextureUpload = System::Int8(0x7);
static constexpr System::Int8 GLKTextureLoaderErrorCubeMapInvalidNumFiles = System::Int8(0x6);
static constexpr System::Int8 GLKTextureLoaderErrorDataPreprocessingFailure = System::Int8(0xc);
static constexpr System::Int8 GLKTextureLoaderErrorFileOrURLNotFound = System::Int8(0x0);
static constexpr System::Int8 GLKTextureLoaderErrorInvalidCGImage = System::Int8(0x2);
static constexpr System::Int8 GLKTextureLoaderErrorInvalidEAGLContext = System::Int8(0x11);
static constexpr System::Int8 GLKTextureLoaderErrorInvalidNSData = System::Int8(0x1);
static constexpr System::Int8 GLKTextureLoaderErrorMipmapUnsupported = System::Int8(0xd);
static constexpr System::Int8 GLKTextureLoaderErrorPVRAtlasUnsupported = System::Int8(0x5);
static constexpr System::Int8 GLKTextureLoaderErrorReorientationFailure = System::Int8(0xf);
static constexpr System::Int8 GLKTextureLoaderErrorUncompressedTextureUpload = System::Int8(0x8);
static constexpr System::Int8 GLKTextureLoaderErrorUnknownFileType = System::Int8(0x4);
static constexpr System::Int8 GLKTextureLoaderErrorUnknownPathType = System::Int8(0x3);
static constexpr System::Int8 GLKTextureLoaderErrorUnsupportedBitDepth = System::Int8(0xa);
static constexpr System::Int8 GLKTextureLoaderErrorUnsupportedCubeMapDimensions = System::Int8(0x9);
static constexpr System::Int8 GLKTextureLoaderErrorUnsupportedOrientation = System::Int8(0xe);
static constexpr System::Int8 GLKTextureLoaderErrorUnsupportedPVRFormat = System::Int8(0xb);
static constexpr System::Word GLKTextureTarget2D = System::Word(0xde1);
static constexpr System::Int8 GLKTextureTargetCt = System::Int8(0x2);
static constexpr System::Word GLKTextureTargetCubeMap = System::Word(0x8513);
static constexpr System::Int8 GLKVertexAttribColor = System::Int8(0x2);
static constexpr System::Int8 GLKVertexAttribNormal = System::Int8(0x1);
static constexpr System::Int8 GLKVertexAttribPosition = System::Int8(0x0);
static constexpr System::Int8 GLKVertexAttribTexCoord0 = System::Int8(0x3);
static constexpr System::Int8 GLKVertexAttribTexCoord1 = System::Int8(0x4);
static constexpr System::Int8 GLKViewDrawableColorFormatRGB565 = System::Int8(0x1);
static constexpr System::Int8 GLKViewDrawableColorFormatRGBA8888 = System::Int8(0x0);
static constexpr System::Int8 GLKViewDrawableDepthFormat16 = System::Int8(0x1);
static constexpr System::Int8 GLKViewDrawableDepthFormat24 = System::Int8(0x2);
static constexpr System::Int8 GLKViewDrawableDepthFormatNone = System::Int8(0x0);
static constexpr System::Int8 GLKViewDrawableMultisample4X = System::Int8(0x1);
static constexpr System::Int8 GLKViewDrawableMultisampleNone = System::Int8(0x0);
static constexpr System::Int8 GLKViewDrawableStencilFormat8 = System::Int8(0x1);
static constexpr System::Int8 GLKViewDrawableStencilFormatNone = System::Int8(0x0);
#define libGLKit u"/System/Library/Frameworks/GLKit.framework/GLKit"
extern "C" float __cdecl GLKMathDegreesToRadians(float degrees);
extern "C" GLKVector3 __cdecl GLKMathProject(GLKVector3 object_, GLKMatrix4 model, GLKMatrix4 projection, System::PInteger viewport);
extern "C" float __cdecl GLKMathRadiansToDegrees(float radians);
extern "C" GLKVector3 __cdecl GLKMathUnproject(GLKVector3 window, GLKMatrix4 model, GLKMatrix4 projection, System::PInteger viewport, P_Bool success);
extern "C" GLKMatrix3 __cdecl GLKMatrix3Add(GLKMatrix3 matrixLeft, GLKMatrix3 matrixRight);
extern "C" GLKVector3 __cdecl GLKMatrix3GetColumn(GLKMatrix3 matrix, int column);
extern "C" GLKMatrix2 __cdecl GLKMatrix3GetMatrix2(GLKMatrix3 matrix);
extern "C" GLKVector3 __cdecl GLKMatrix3GetRow(GLKMatrix3 matrix, int row);
extern "C" GLKMatrix3 __cdecl GLKMatrix3Invert(GLKMatrix3 matrix, P_Bool isInvertible);
extern "C" GLKMatrix3 __cdecl GLKMatrix3InvertAndTranspose(GLKMatrix3 matrix, P_Bool isInvertible);
extern "C" GLKMatrix3 __cdecl GLKMatrix3Make(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);
extern "C" GLKMatrix3 __cdecl GLKMatrix3MakeAndTranspose(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);
extern "C" GLKMatrix3 __cdecl GLKMatrix3MakeRotation(float radians, float x, float y, float z);
extern "C" GLKMatrix3 __cdecl GLKMatrix3MakeScale(float sx, float sy, float sz);
extern "C" GLKMatrix3 __cdecl GLKMatrix3MakeWithArray(System::PSingle values);
extern "C" GLKMatrix3 __cdecl GLKMatrix3MakeWithArrayAndTranspose(System::PSingle values);
extern "C" GLKMatrix3 __cdecl GLKMatrix3MakeWithColumns(GLKVector3 column0, GLKVector3 column1, GLKVector3 column2);
extern "C" GLKMatrix3 __cdecl GLKMatrix3MakeWithQuaternion(GLKQuaternion quaternion);
extern "C" GLKMatrix3 __cdecl GLKMatrix3MakeWithRows(GLKVector3 row0, GLKVector3 row1, GLKVector3 row2);
extern "C" GLKMatrix3 __cdecl GLKMatrix3MakeXRotation(float radians);
extern "C" GLKMatrix3 __cdecl GLKMatrix3MakeYRotation(float radians);
extern "C" GLKMatrix3 __cdecl GLKMatrix3MakeZRotation(float radians);
extern "C" GLKMatrix3 __cdecl GLKMatrix3Multiply(GLKMatrix3 matrixLeft, GLKMatrix3 matrixRight);
extern "C" GLKVector3 __cdecl GLKMatrix3MultiplyVector3(GLKMatrix3 matrixLeft, GLKVector3 vectorRight);
extern "C" void __cdecl GLKMatrix3MultiplyVector3Array(GLKMatrix3 matrix, PGLKVector3 vectors, unsigned long vectorCount);
extern "C" GLKMatrix3 __cdecl GLKMatrix3Rotate(GLKMatrix3 matrix, float radians, float x, float y, float z);
extern "C" GLKMatrix3 __cdecl GLKMatrix3RotateWithVector3(GLKMatrix3 matrix, float radians, GLKVector3 axisVector);
extern "C" GLKMatrix3 __cdecl GLKMatrix3RotateWithVector4(GLKMatrix3 matrix, float radians, GLKVector4 axisVector);
extern "C" GLKMatrix3 __cdecl GLKMatrix3RotateX(GLKMatrix3 matrix, float radians);
extern "C" GLKMatrix3 __cdecl GLKMatrix3RotateY(GLKMatrix3 matrix, float radians);
extern "C" GLKMatrix3 __cdecl GLKMatrix3RotateZ(GLKMatrix3 matrix, float radians);
extern "C" GLKMatrix3 __cdecl GLKMatrix3Scale(GLKMatrix3 matrix, float sx, float sy, float sz);
extern "C" GLKMatrix3 __cdecl GLKMatrix3ScaleWithVector3(GLKMatrix3 matrix, GLKVector3 scaleVector);
extern "C" GLKMatrix3 __cdecl GLKMatrix3ScaleWithVector4(GLKMatrix3 matrix, GLKVector4 scaleVector);
extern "C" GLKMatrix3 __cdecl GLKMatrix3SetColumn(GLKMatrix3 matrix, int column, GLKVector3 vector);
extern "C" GLKMatrix3 __cdecl GLKMatrix3SetRow(GLKMatrix3 matrix, int row, GLKVector3 vector);
extern "C" GLKMatrix3 __cdecl GLKMatrix3Subtract(GLKMatrix3 matrixLeft, GLKMatrix3 matrixRight);
extern "C" GLKMatrix3 __cdecl GLKMatrix3Transpose(GLKMatrix3 matrix);
extern "C" GLKMatrix4 __cdecl GLKMatrix4Add(GLKMatrix4 matrixLeft, GLKMatrix4 matrixRight);
extern "C" GLKVector4 __cdecl GLKMatrix4GetColumn(GLKMatrix4 matrix, int column);
extern "C" GLKMatrix2 __cdecl GLKMatrix4GetMatrix2(GLKMatrix4 matrix);
extern "C" GLKMatrix3 __cdecl GLKMatrix4GetMatrix3(GLKMatrix4 matrix);
extern "C" GLKVector4 __cdecl GLKMatrix4GetRow(GLKMatrix4 matrix, int row);
extern "C" GLKMatrix4 __cdecl GLKMatrix4Invert(GLKMatrix4 matrix, P_Bool isInvertible);
extern "C" GLKMatrix4 __cdecl GLKMatrix4InvertAndTranspose(GLKMatrix4 matrix, P_Bool isInvertible);
extern "C" GLKMatrix4 __cdecl GLKMatrix4Make(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);
extern "C" GLKMatrix4 __cdecl GLKMatrix4MakeAndTranspose(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);
extern "C" GLKMatrix4 __cdecl GLKMatrix4MakeFrustum(float left, float right, float bottom, float top, float nearZ, float farZ);
extern "C" GLKMatrix4 __cdecl GLKMatrix4MakeLookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);
extern "C" GLKMatrix4 __cdecl GLKMatrix4MakeOrtho(float left, float right, float bottom, float top, float nearZ, float farZ);
extern "C" GLKMatrix4 __cdecl GLKMatrix4MakePerspective(float fovyRadians, float aspect, float nearZ, float farZ);
extern "C" GLKMatrix4 __cdecl GLKMatrix4MakeRotation(float radians, float x, float y, float z);
extern "C" GLKMatrix4 __cdecl GLKMatrix4MakeScale(float sx, float sy, float sz);
extern "C" GLKMatrix4 __cdecl GLKMatrix4MakeTranslation(float tx, float ty, float tz);
extern "C" GLKMatrix4 __cdecl GLKMatrix4MakeWithArray(System::PSingle values);
extern "C" GLKMatrix4 __cdecl GLKMatrix4MakeWithArrayAndTranspose(System::PSingle values);
extern "C" GLKMatrix4 __cdecl GLKMatrix4MakeWithColumns(GLKVector4 column0, GLKVector4 column1, GLKVector4 column2, GLKVector4 column3);
extern "C" GLKMatrix4 __cdecl GLKMatrix4MakeWithQuaternion(GLKQuaternion quaternion);
extern "C" GLKMatrix4 __cdecl GLKMatrix4MakeWithRows(GLKVector4 row0, GLKVector4 row1, GLKVector4 row2, GLKVector4 row3);
extern "C" GLKMatrix4 __cdecl GLKMatrix4MakeXRotation(float radians);
extern "C" GLKMatrix4 __cdecl GLKMatrix4MakeYRotation(float radians);
extern "C" GLKMatrix4 __cdecl GLKMatrix4MakeZRotation(float radians);
extern "C" GLKMatrix4 __cdecl GLKMatrix4Multiply(GLKMatrix4 matrixLeft, GLKMatrix4 matrixRight);
extern "C" GLKVector3 __cdecl GLKMatrix4MultiplyAndProjectVector3(GLKMatrix4 matrixLeft, GLKVector3 vectorRight);
extern "C" void __cdecl GLKMatrix4MultiplyAndProjectVector3Array(GLKMatrix4 matrix, PGLKVector3 vectors, unsigned long vectorCount);
extern "C" GLKVector3 __cdecl GLKMatrix4MultiplyVector3(GLKMatrix4 matrixLeft, GLKVector3 vectorRight);
extern "C" void __cdecl GLKMatrix4MultiplyVector3Array(GLKMatrix4 matrix, PGLKVector3 vectors, unsigned long vectorCount);
extern "C" void __cdecl GLKMatrix4MultiplyVector3ArrayWithTranslation(GLKMatrix4 matrix, PGLKVector3 vectors, unsigned long vectorCount);
extern "C" GLKVector3 __cdecl GLKMatrix4MultiplyVector3WithTranslation(GLKMatrix4 matrixLeft, GLKVector3 vectorRight);
extern "C" GLKVector4 __cdecl GLKMatrix4MultiplyVector4(GLKMatrix4 matrixLeft, GLKVector4 vectorRight);
extern "C" void __cdecl GLKMatrix4MultiplyVector4Array(GLKMatrix4 matrix, PGLKVector4 vectors, unsigned long vectorCount);
extern "C" GLKMatrix4 __cdecl GLKMatrix4Rotate(GLKMatrix4 matrix, float radians, float x, float y, float z);
extern "C" GLKMatrix4 __cdecl GLKMatrix4RotateWithVector3(GLKMatrix4 matrix, float radians, GLKVector3 axisVector);
extern "C" GLKMatrix4 __cdecl GLKMatrix4RotateWithVector4(GLKMatrix4 matrix, float radians, GLKVector4 axisVector);
extern "C" GLKMatrix4 __cdecl GLKMatrix4RotateX(GLKMatrix4 matrix, float radians);
extern "C" GLKMatrix4 __cdecl GLKMatrix4RotateY(GLKMatrix4 matrix, float radians);
extern "C" GLKMatrix4 __cdecl GLKMatrix4RotateZ(GLKMatrix4 matrix, float radians);
extern "C" GLKMatrix4 __cdecl GLKMatrix4Scale(GLKMatrix4 matrix, float sx, float sy, float sz);
extern "C" GLKMatrix4 __cdecl GLKMatrix4ScaleWithVector3(GLKMatrix4 matrix, GLKVector3 scaleVector);
extern "C" GLKMatrix4 __cdecl GLKMatrix4ScaleWithVector4(GLKMatrix4 matrix, GLKVector4 scaleVector);
extern "C" GLKMatrix4 __cdecl GLKMatrix4SetColumn(GLKMatrix4 matrix, int column, GLKVector4 vector);
extern "C" GLKMatrix4 __cdecl GLKMatrix4SetRow(GLKMatrix4 matrix, int row, GLKVector4 vector);
extern "C" GLKMatrix4 __cdecl GLKMatrix4Subtract(GLKMatrix4 matrixLeft, GLKMatrix4 matrixRight);
extern "C" GLKMatrix4 __cdecl GLKMatrix4Translate(GLKMatrix4 matrix, float tx, float ty, float tz);
extern "C" GLKMatrix4 __cdecl GLKMatrix4TranslateWithVector3(GLKMatrix4 matrix, GLKVector3 translationVector);
extern "C" GLKMatrix4 __cdecl GLKMatrix4TranslateWithVector4(GLKMatrix4 matrix, GLKVector4 translationVector);
extern "C" GLKMatrix4 __cdecl GLKMatrix4Transpose(GLKMatrix4 matrix);
extern "C" void * __cdecl GLKMatrixStackCreate(CFAllocatorRef alloc);
extern "C" GLKMatrix2 __cdecl GLKMatrixStackGetMatrix2(void * stack);
extern "C" GLKMatrix3 __cdecl GLKMatrixStackGetMatrix3(void * stack);
extern "C" GLKMatrix3 __cdecl GLKMatrixStackGetMatrix3Inverse(void * stack);
extern "C" GLKMatrix3 __cdecl GLKMatrixStackGetMatrix3InverseTranspose(void * stack);
extern "C" GLKMatrix4 __cdecl GLKMatrixStackGetMatrix4(void * stack);
extern "C" GLKMatrix4 __cdecl GLKMatrixStackGetMatrix4Inverse(void * stack);
extern "C" GLKMatrix4 __cdecl GLKMatrixStackGetMatrix4InverseTranspose(void * stack);
extern "C" unsigned long __cdecl GLKMatrixStackGetTypeID(void);
extern "C" void __cdecl GLKMatrixStackLoadMatrix4(void * stack, GLKMatrix4 matrix);
extern "C" void __cdecl GLKMatrixStackMultiplyMatrix4(void * stack, GLKMatrix4 matrix);
extern "C" void __cdecl GLKMatrixStackMultiplyMatrixStack(void * stackLeft, void * stackRight);
extern "C" void __cdecl GLKMatrixStackPop(void * stack);
extern "C" void __cdecl GLKMatrixStackPush(void * stack);
extern "C" void __cdecl GLKMatrixStackRotate(void * stack, float radians, float x, float y, float z);
extern "C" void __cdecl GLKMatrixStackRotateWithVector3(void * stack, float radians, GLKVector3 axisVector);
extern "C" void __cdecl GLKMatrixStackRotateWithVector4(void * stack, float radians, GLKVector4 axisVector);
extern "C" void __cdecl GLKMatrixStackRotateX(void * stack, float radians);
extern "C" void __cdecl GLKMatrixStackRotateY(void * stack, float radians);
extern "C" void __cdecl GLKMatrixStackRotateZ(void * stack, float radians);
extern "C" void __cdecl GLKMatrixStackScale(void * stack, float sx, float sy, float sz);
extern "C" void __cdecl GLKMatrixStackScaleWithVector3(void * stack, GLKVector3 scaleVector);
extern "C" void __cdecl GLKMatrixStackScaleWithVector4(void * stack, GLKVector4 scaleVector);
extern "C" int __cdecl GLKMatrixStackSize(void * stack);
extern "C" void __cdecl GLKMatrixStackTranslate(void * stack, float tx, float ty, float tz);
extern "C" void __cdecl GLKMatrixStackTranslateWithVector3(void * stack, GLKVector3 translationVector);
extern "C" void __cdecl GLKMatrixStackTranslateWithVector4(void * stack, GLKVector4 translationVector);
extern "C" GLKQuaternion __cdecl GLKQuaternionAdd(GLKQuaternion quaternionLeft, GLKQuaternion quaternionRight);
extern "C" float __cdecl GLKQuaternionAngle(GLKQuaternion quaternion);
extern "C" GLKVector3 __cdecl GLKQuaternionAxis(GLKQuaternion quaternion);
extern "C" GLKQuaternion __cdecl GLKQuaternionConjugate(GLKQuaternion quaternion);
extern "C" GLKQuaternion __cdecl GLKQuaternionInvert(GLKQuaternion quaternion);
extern "C" float __cdecl GLKQuaternionLength(GLKQuaternion quaternion);
extern "C" GLKQuaternion __cdecl GLKQuaternionMake(float x, float y, float z, float w);
extern "C" GLKQuaternion __cdecl GLKQuaternionMakeWithAngleAndAxis(float radians, float x, float y, float z);
extern "C" GLKQuaternion __cdecl GLKQuaternionMakeWithAngleAndVector3Axis(float radians, GLKVector3 axisVector);
extern "C" GLKQuaternion __cdecl GLKQuaternionMakeWithArray(System::PSingle values);
extern "C" GLKQuaternion __cdecl GLKQuaternionMakeWithMatrix3(GLKMatrix3 matrix);
extern "C" GLKQuaternion __cdecl GLKQuaternionMakeWithMatrix4(GLKMatrix4 matrix);
extern "C" GLKQuaternion __cdecl GLKQuaternionMakeWithVector3(GLKVector3 vector, float scalar);
extern "C" GLKQuaternion __cdecl GLKQuaternionMultiply(GLKQuaternion quaternionLeft, GLKQuaternion quaternionRight);
extern "C" GLKQuaternion __cdecl GLKQuaternionNormalize(GLKQuaternion quaternion);
extern "C" GLKVector3 __cdecl GLKQuaternionRotateVector3(GLKQuaternion quaternion, GLKVector3 vector);
extern "C" void __cdecl GLKQuaternionRotateVector3Array(GLKQuaternion quaternion, PGLKVector3 vectors, unsigned long vectorCount);
extern "C" GLKVector4 __cdecl GLKQuaternionRotateVector4(GLKQuaternion quaternion, GLKVector4 vector);
extern "C" void __cdecl GLKQuaternionRotateVector4Array(GLKQuaternion quaternion, PGLKVector4 vectors, unsigned long vectorCount);
extern "C" GLKQuaternion __cdecl GLKQuaternionSlerp(GLKQuaternion quaternionStart, GLKQuaternion quaternionEnd, float t);
extern "C" GLKQuaternion __cdecl GLKQuaternionSubtract(GLKQuaternion quaternionLeft, GLKQuaternion quaternionRight);
extern "C" GLKVector2 __cdecl GLKVector2Add(GLKVector2 vectorLeft, GLKVector2 vectorRight);
extern "C" GLKVector2 __cdecl GLKVector2AddScalar(GLKVector2 vector, float value);
extern "C" int __cdecl GLKVector2AllEqualToScalar(GLKVector2 vector, float value);
extern "C" int __cdecl GLKVector2AllEqualToVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight);
extern "C" int __cdecl GLKVector2AllGreaterThanOrEqualToScalar(GLKVector2 vector, float value);
extern "C" int __cdecl GLKVector2AllGreaterThanOrEqualToVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight);
extern "C" int __cdecl GLKVector2AllGreaterThanScalar(GLKVector2 vector, float value);
extern "C" int __cdecl GLKVector2AllGreaterThanVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight);
extern "C" float __cdecl GLKVector2Distance(GLKVector2 vectorStart, GLKVector2 vectorEnd);
extern "C" GLKVector2 __cdecl GLKVector2Divide(GLKVector2 vectorLeft, GLKVector2 vectorRight);
extern "C" GLKVector2 __cdecl GLKVector2DivideScalar(GLKVector2 vector, float value);
extern "C" float __cdecl GLKVector2DotProduct(GLKVector2 vectorLeft, GLKVector2 vectorRight);
extern "C" float __cdecl GLKVector2Length(GLKVector2 vector);
extern "C" GLKVector2 __cdecl GLKVector2Lerp(GLKVector2 vectorStart, GLKVector2 vectorEnd, float t);
extern "C" GLKVector2 __cdecl GLKVector2Make(float x, float y);
extern "C" GLKVector2 __cdecl GLKVector2MakeWithArray(System::PSingle values);
extern "C" GLKVector2 __cdecl GLKVector2Maximum(GLKVector2 vectorLeft, GLKVector2 vectorRight);
extern "C" GLKVector2 __cdecl GLKVector2Minimum(GLKVector2 vectorLeft, GLKVector2 vectorRight);
extern "C" GLKVector2 __cdecl GLKVector2Multiply(GLKVector2 vectorLeft, GLKVector2 vectorRight);
extern "C" GLKVector2 __cdecl GLKVector2MultiplyScalar(GLKVector2 vector, float value);
extern "C" GLKVector2 __cdecl GLKVector2Negate(GLKVector2 vector);
extern "C" GLKVector2 __cdecl GLKVector2Normalize(GLKVector2 vector);
extern "C" GLKVector2 __cdecl GLKVector2Project(GLKVector2 vectorToProject, GLKVector2 projectionVector);
extern "C" GLKVector2 __cdecl GLKVector2Subtract(GLKVector2 vectorLeft, GLKVector2 vectorRight);
extern "C" GLKVector2 __cdecl GLKVector2SubtractScalar(GLKVector2 vector, float value);
extern "C" GLKVector3 __cdecl GLKVector3Add(GLKVector3 vectorLeft, GLKVector3 vectorRight);
extern "C" GLKVector3 __cdecl GLKVector3AddScalar(GLKVector3 vector, float value);
extern "C" int __cdecl GLKVector3AllEqualToScalar(GLKVector3 vector, float value);
extern "C" int __cdecl GLKVector3AllEqualToVector3(GLKVector3 vectorLeft, GLKVector3 vectorRight);
extern "C" int __cdecl GLKVector3AllGreaterThanOrEqualToScalar(GLKVector3 vector, float value);
extern "C" int __cdecl GLKVector3AllGreaterThanOrEqualToVector3(GLKVector3 vectorLeft, GLKVector3 vectorRight);
extern "C" int __cdecl GLKVector3AllGreaterThanScalar(GLKVector3 vector, float value);
extern "C" int __cdecl GLKVector3AllGreaterThanVector3(GLKVector3 vectorLeft, GLKVector3 vectorRight);
extern "C" GLKVector3 __cdecl GLKVector3CrossProduct(GLKVector3 vectorLeft, GLKVector3 vectorRight);
extern "C" float __cdecl GLKVector3Distance(GLKVector3 vectorStart, GLKVector3 vectorEnd);
extern "C" GLKVector3 __cdecl GLKVector3Divide(GLKVector3 vectorLeft, GLKVector3 vectorRight);
extern "C" GLKVector3 __cdecl GLKVector3DivideScalar(GLKVector3 vector, float value);
extern "C" float __cdecl GLKVector3DotProduct(GLKVector3 vectorLeft, GLKVector3 vectorRight);
extern "C" float __cdecl GLKVector3Length(GLKVector3 vector);
extern "C" GLKVector3 __cdecl GLKVector3Lerp(GLKVector3 vectorStart, GLKVector3 vectorEnd, float t);
extern "C" GLKVector3 __cdecl GLKVector3Make(float x, float y, float z);
extern "C" GLKVector3 __cdecl GLKVector3MakeWithArray(System::PSingle values);
extern "C" GLKVector3 __cdecl GLKVector3Maximum(GLKVector3 vectorLeft, GLKVector3 vectorRight);
extern "C" GLKVector3 __cdecl GLKVector3Minimum(GLKVector3 vectorLeft, GLKVector3 vectorRight);
extern "C" GLKVector3 __cdecl GLKVector3Multiply(GLKVector3 vectorLeft, GLKVector3 vectorRight);
extern "C" GLKVector3 __cdecl GLKVector3MultiplyScalar(GLKVector3 vector, float value);
extern "C" GLKVector3 __cdecl GLKVector3Negate(GLKVector3 vector);
extern "C" GLKVector3 __cdecl GLKVector3Normalize(GLKVector3 vector);
extern "C" GLKVector3 __cdecl GLKVector3Project(GLKVector3 vectorToProject, GLKVector3 projectionVector);
extern "C" GLKVector3 __cdecl GLKVector3Subtract(GLKVector3 vectorLeft, GLKVector3 vectorRight);
extern "C" GLKVector3 __cdecl GLKVector3SubtractScalar(GLKVector3 vector, float value);
extern "C" GLKVector4 __cdecl GLKVector4Add(GLKVector4 vectorLeft, GLKVector4 vectorRight);
extern "C" GLKVector4 __cdecl GLKVector4AddScalar(GLKVector4 vector, float value);
extern "C" int __cdecl GLKVector4AllEqualToScalar(GLKVector4 vector, float value);
extern "C" int __cdecl GLKVector4AllEqualToVector4(GLKVector4 vectorLeft, GLKVector4 vectorRight);
extern "C" int __cdecl GLKVector4AllGreaterThanOrEqualToScalar(GLKVector4 vector, float value);
extern "C" int __cdecl GLKVector4AllGreaterThanOrEqualToVector4(GLKVector4 vectorLeft, GLKVector4 vectorRight);
extern "C" int __cdecl GLKVector4AllGreaterThanScalar(GLKVector4 vector, float value);
extern "C" int __cdecl GLKVector4AllGreaterThanVector4(GLKVector4 vectorLeft, GLKVector4 vectorRight);
extern "C" GLKVector4 __cdecl GLKVector4CrossProduct(GLKVector4 vectorLeft, GLKVector4 vectorRight);
extern "C" float __cdecl GLKVector4Distance(GLKVector4 vectorStart, GLKVector4 vectorEnd);
extern "C" GLKVector4 __cdecl GLKVector4Divide(GLKVector4 vectorLeft, GLKVector4 vectorRight);
extern "C" GLKVector4 __cdecl GLKVector4DivideScalar(GLKVector4 vector, float value);
extern "C" float __cdecl GLKVector4DotProduct(GLKVector4 vectorLeft, GLKVector4 vectorRight);
extern "C" float __cdecl GLKVector4Length(GLKVector4 vector);
extern "C" GLKVector4 __cdecl GLKVector4Lerp(GLKVector4 vectorStart, GLKVector4 vectorEnd, float t);
extern "C" GLKVector4 __cdecl GLKVector4Make(float x, float y, float z, float w);
extern "C" GLKVector4 __cdecl GLKVector4MakeWithArray(System::PSingle values);
extern "C" GLKVector4 __cdecl GLKVector4MakeWithVector3(GLKVector3 vector, float w);
extern "C" GLKVector4 __cdecl GLKVector4Maximum(GLKVector4 vectorLeft, GLKVector4 vectorRight);
extern "C" GLKVector4 __cdecl GLKVector4Minimum(GLKVector4 vectorLeft, GLKVector4 vectorRight);
extern "C" GLKVector4 __cdecl GLKVector4Multiply(GLKVector4 vectorLeft, GLKVector4 vectorRight);
extern "C" GLKVector4 __cdecl GLKVector4MultiplyScalar(GLKVector4 vector, float value);
extern "C" GLKVector4 __cdecl GLKVector4Negate(GLKVector4 vector);
extern "C" GLKVector4 __cdecl GLKVector4Normalize(GLKVector4 vector);
extern "C" GLKVector4 __cdecl GLKVector4Project(GLKVector4 vectorToProject, GLKVector4 projectionVector);
extern "C" GLKVector4 __cdecl GLKVector4Subtract(GLKVector4 vectorLeft, GLKVector4 vectorRight);
extern "C" GLKVector4 __cdecl GLKVector4SubtractScalar(GLKVector4 vector, float value);
extern "C" void * __cdecl NSStringFromGLKMatrix2(GLKMatrix2 matrix);
extern "C" void * __cdecl NSStringFromGLKMatrix3(GLKMatrix3 matrix);
extern "C" void * __cdecl NSStringFromGLKMatrix4(GLKMatrix4 matrix);
extern "C" void * __cdecl NSStringFromGLKQuaternion(GLKQuaternion quaternion);
extern "C" void * __cdecl NSStringFromGLKVector2(GLKVector2 vector);
extern "C" void * __cdecl NSStringFromGLKVector3(GLKVector3 vector);
extern "C" void * __cdecl NSStringFromGLKVector4(GLKVector4 vector);
}	/* namespace Glkit */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_GLKIT)
using namespace Iosapi::Glkit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_GlkitHPP
